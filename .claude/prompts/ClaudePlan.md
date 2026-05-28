# Cross-Platform Linux Build Plan for DNDCgo Core Simulation Engine

## Context

DNDCgo is a Windows-only MSVC DLL for biogeochemical simulation. A headless mode (`DEGUI` define) already exists that strips out MFC GUI code and exposes `OpenSesame()` in `Dndc_shell.cpp` as the console entry point. The project has never compiled on Linux due to residual Windows-specific constructs even within the DEGUI code paths: MFC headers, `CString`, `AfxMessageBox`, `_mkdir`, `WINAPI`, `__declspec(dllexport)`, and Windows-only system headers.

**Goal:** Make the core engine compile as `libDNDCgo.so` (and a `dndc_batch` executable) on Linux using the existing DEGUI mode. `DndcGraphics/` (the GUI, ~200 MFC files) stays Windows-only.

---

## Files to Create

### 1. `platform.h` — cross-platform compatibility shim

Injected via `StdAfx.h` on non-Windows. Provides everything needed so **no individual call sites need changing**: `CString`, `AfxMessageBox`, `WINAPI`, and `_mkdir` are all defined here.

```cpp
#ifndef PLATFORM_H
#define PLATFORM_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>

// ---- Calling convention ----
#define WINAPI
#define PASCAL
#define DEBUG_NEW new

// ---- mkdir: Windows single-arg -> Linux two-arg ----
inline int _mkdir(const char* path) { return mkdir(path, 0755); }

// ---- min/max ----
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

// ---- Minimal CString compatibility class ----
// Supports: Format(), implicit const char* conversion, operator=, Find(), IsEmpty()
class CString {
public:
    char buf[512];
    CString()                            { buf[0] = '\0'; }
    CString(const char* s)               { if(s) strncpy(buf,s,511); else buf[0]='\0'; buf[511]='\0'; }
    CString(const CString& o)            { strncpy(buf,o.buf,511); buf[511]='\0'; }
    CString& operator=(const char* s)    { if(s) strncpy(buf,s,511); else buf[0]='\0'; buf[511]='\0'; return *this; }
    CString& operator=(const CString& o) { strncpy(buf,o.buf,511); buf[511]='\0'; return *this; }
    operator const char*() const         { return buf; }
    operator char*()                     { return buf; }  // needed for fopen(cstring, mode)
    void Format(const char* fmt, ...) {
        va_list a; va_start(a,fmt); vsnprintf(buf,sizeof(buf),fmt,a); va_end(a);
    }
    int  Find(char c) const { const char* p=strchr(buf,c); return p?(int)(p-buf):-1; }
    int  GetLength() const  { return (int)strlen(buf); }
    bool IsEmpty()   const  { return buf[0]=='\0'; }
};

// ---- AfxMessageBox / MessageBox -> stderr + exit ----
// All existing call sites are fatal-error paths, so exit() matches intended behavior.
inline int AfxMessageBox(const char* msg, unsigned=0, unsigned=0) {
    fprintf(stderr,"FATAL: %s\n",msg); exit(1); return 0;
}
inline int AfxMessageBox(const CString& msg, unsigned t=0, unsigned h=0) {
    return AfxMessageBox((const char*)msg,t,h);
}
inline int MessageBox(void*, const char* msg, const char*, unsigned) {
    fprintf(stderr,"FATAL: %s\n",msg); exit(1); return 0;
}

#endif // PLATFORM_H
```

### 2. `main_linux.cpp` — standalone Linux entry point

Defines `root_lib` (referenced by `Dndc_shell.cpp` but supplied by DndcGraphics on Windows) and initializes the path globals before calling `OpenSesame()`.

```cpp
// Linux entry point for DNDCgo simulation engine.
// Calls OpenSesame() defined in Dndc_shell.cpp (DEGUI mode).

#include "platform.h"
#include "RunPaths.h"
#include <string>
#include <cstring>

std::string root_lib;   // extern-declared in Dndc_shell.cpp DEGUI block

int OpenSesame(void);

int main(int argc, char* argv[]) {
    root_lib = (argc > 1) ? argv[1] : "./Library";

    snprintf(ssROOTDIR,     sizeof(ssROOTDIR),    "./");
    snprintf(ssOUTPUT,      sizeof(ssOUTPUT),      "./Result");
    snprintf(ssINTER,       sizeof(ssINTER),        "./Result/Inter");
    snprintf(ssINPUTS,      sizeof(ssINPUTS),       "./Result/Inputs");
    snprintf(ssINTERMANAGE, sizeof(ssINTERMANAGE),  "./Result/Inter/Management");
    snprintf(ssLIBRARY,     sizeof(ssLIBRARY),      "%s", root_lib.c_str());

    ROOTDIR=ssROOTDIR; OUTPUT=ssOUTPUT; INTER=ssINTER;
    INPUTS=ssINPUTS; INTERMANAGE=ssINTERMANAGE; LIBRARY=ssLIBRARY;

    return OpenSesame();
}
```

### 3. `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.16)
project(DNDCgo CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_SOURCES
    RunPaths.cpp DNDCgo.cpp Dndc_main.cpp Dndc_shell.cpp Dndc_tool.cpp
    Dndc_SoilPhysics.cpp Dndc_SoilChemistry.cpp Dndc_crop.cpp Dndc_data.cpp
    Dndc_farming.cpp Dndc_farmAgent.cpp Dndc_output.cpp Dndc_balance.cpp
    Dndc_balloon.cpp Dndc_CH4.cpp Dndc_CH4peat.cpp Dndc_Eh.cpp
    Dndc_hydrology.cpp Dndc_WT.cpp Dndc_summary.cpp Dndc_P.cpp Dndc_VOCs.cpp
    Dndc_regiondaily.cpp Dndc_RegionOutput.cpp
    Dndc_manure0.cpp Dndc_manure1.cpp Dndc_manure2.cpp Dndc_manure3.cpp
    Dndc_manure5.cpp Dndc_manure6.cpp Dndc_manure7.cpp Dndc_manure9.cpp
    Dndc_manure10.cpp Dndc_ManureComponent.cpp Dndc_ManureFeedlot.cpp
    Dndc_ManureRemoval.cpp Dndc_ManureTreatment.cpp
    CreateInputFiles.cpp SiteParaGo.cpp
    # EXCLUDED: StdAfx.cpp (MSVC PCH only), Dndc_mapping.cpp, Dndc_paint.cpp, Swine.cpp
)

add_library(DNDCgo SHARED ${CORE_SOURCES})
target_compile_definitions(DNDCgo PRIVATE DEGUI BALANCE _CRT_SECURE_NO_WARNINGS)
target_include_directories(DNDCgo PRIVATE ${CMAKE_SOURCE_DIR})
target_compile_options(DNDCgo PRIVATE
    -fvisibility=hidden
    -Wno-write-strings
    -Wno-unused-variable
    -Wno-unused-result
    -Wno-format-security
)

add_executable(dndc_batch main_linux.cpp)
target_link_libraries(dndc_batch PRIVATE DNDCgo dl m)
```

---

## Files to Modify

### `StdAfx.h` — single injection point for platform.h

Wrap all MFC includes with `#ifdef _WIN32` and inject `platform.h` in the `#else` branch. This one change makes `CString`, `AfxMessageBox`, `WINAPI`, and `_mkdir` available in every translation unit without touching individual call sites.

```cpp
#ifdef _WIN32
  #define VC_EXTRALEAN
  #include <afxwin.h>
  #include <afxext.h>
  // ... all existing MFC includes unchanged ...
#else
  #include "platform.h"
#endif
```

### `RunPaths.h` — export macro

```cpp
#ifdef _WIN32
  #define RUNPATHS_API extern "C" __declspec(dllexport)
#else
  #define RUNPATHS_API extern "C" __attribute__((visibility("default")))
#endif
```

### `DNDCgo.cpp` — 3 fixes

1. Guard `#include <direct.h>` with `#ifdef _WIN32`.

2. Wrap the MFC app boilerplate (lines 47–66: `BEGIN_MESSAGE_MAP` … `CDNDCgoApp theApp`) in `#ifndef DEGUI`. Without this, the compiler looks for `CDNDCgoApp` which is defined in `DNDCgo.h` that is itself `#ifndef DEGUI`-guarded — causing a compile error.

3. Wrap the livestock/`DNDC101go` branch (~lines 107–152) in `#ifndef DEGUI`. The variable `pLinkInfo` does not exist in the `Model_linux` DEGUI function signature, and this branch is never reached via `OpenSesame` (always called with `scale=0`):
   ```cpp
   #ifndef DEGUI
   if(livestock>=1 && scale==1) {
       // ... existing DNDC101go block ...
   }
   else
   #endif
   { // cropland run ...
   ```

### `Dndc_shell.cpp` — 4 fixes

1. Add `#include <string>` and `extern std::string root_lib;` near the top of the `#ifdef DEGUI` block.
2. Change hardcoded `"\\DNDC_Output\\"` (line 37) to `"./DNDC_Output/"`.
3. Change all `\\` in `DIR0.Format(...)` and `sprintf(...)` calls to `/`.
4. `_mkdir` calls require no changes — handled by the `platform.h` shim.

### `Source_main.h`

- Guard `#include <conio.h>`, `<dos.h>`, `<io.h>` with `#ifdef _WIN32`.
- Change path macros (lines 46–58): `"\\DNDC\\"` → `"/DNDC/"`, `"\\ManureDNDC\\"` → `"/ManureDNDC/"`, etc.

### `dndc_main.h`

Same two changes as `Source_main.h`.

### `Dndc_tool.h` / `Dndc_shell.h` / `CreateInputFile.h`

Guard `#include <conio.h>`, `<dos.h>`, `<io.h>` with `#ifdef _WIN32` in each file.

### `Dndc_main.cpp`

- Change `#include "direct.h"` to a `#ifdef _WIN32` guard.
- Change all `\\` in sprintf format strings to `/` (~80 occurrences: `\\Inter\\` → `/Inter/`, `\\RECORD\\` → `/RECORD/`, `\\Inputs\\` → `/Inputs/`, etc.).
- `_mkdir` and `CString` call sites require no changes.

### `SiteParaGo.cpp`

- Guard `#include <io.h>` and `#include <direct.h>` with `#ifdef _WIN32`.
- Change all `\\` in path format strings to `/` (~82 occurrences).

### `Dndc_output.cpp` / `CreateInputFiles.cpp` / `Dndc_regiondaily.cpp` / `Dndc_RegionOutput.cpp` / `Dndc_farmAgent.cpp` / `Dndc_WT.cpp`

- Guard any `<direct.h>` / `<io.h>` includes with `#ifdef _WIN32`.
- Change all `\\` in sprintf format strings to `/`.

### `Dndc_ManureFeedlot.cpp`

Wrap `#include "Swine.h"` in `#ifdef _WIN32`. `Swine` uses `HMODULE` and `LoadLibrary` which have no Linux equivalent; the `Swine` object is only instantiated inside `#ifdef MANURE` blocks, which are inactive for this build.

---

## Path Separator Note

Windows MSVC CRT's `fopen`, `sprintf`, etc. all accept `/` as a path separator for local paths. Changing `\\` → `/` in all format strings is safe on both platforms and avoids any runtime substitution logic.

---

## Files Excluded from the Linux Build

| File | Reason |
|------|--------|
| `StdAfx.cpp` | MSVC precompiled header generator only; no content |
| `Dndc_mapping.cpp` | Dense GDI/CDC/MFC drawing code, no DEGUI guard, no Linux equivalent |
| `Dndc_paint.cpp` | Same as above |
| `Swine.cpp` | Uses `LoadLibrary`, `GetProcAddress`, `HMODULE` — Windows DLL loading; Swine is only used under `#ifdef MANURE` |
| `DndcGraphics/` | Entire GUI host application — stays Windows-only |

---

## Verification

```bash
# 1. Configure and build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build 2>&1 | head -80

# 2. Confirm outputs exist
ls build/libDNDCgo.so build/dndc_batch

# 3. Create required directory structure
mkdir -p ./Result/Inputs ./Result/Inter/Management ./Result/Record/Site

# 4. Run with a valid batch list
echo "1"           > Batch_list.txt
echo "/path/to/site.dnd" >> Batch_list.txt
./build/dndc_batch ./Library

# 5. Verify output files are created
ls ./Result/Inter/UnitSystem
ls ./Result/Record/Site/
```
