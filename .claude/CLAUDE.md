# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**DNDCgo** is the DNDC (DeNitrification-DeComposition) biogeochemical model, originally coded by Changsheng Li at the University of New Hampshire (1989–2015). It simulates soil carbon and nitrogen cycling, greenhouse gas emissions (CO₂, N₂O, CH₄, NO, NH₃), crop growth, and hydrology. The project compiles as a Windows MFC DLL (`DNDCgo.dll`) consumed by a separate GUI application (in `DndcGraphics/`).

## Build System

The project uses Visual Studio (`.sln` / `.vcxproj`, toolset v143 for Debug, v142 for Release). Build configurations:

- **Debug|Win32**, **Debug|x64** — with debug info and runtime checks
- **Debug-console|Win32**, **Debug-console|x64** — same as Debug but for headless mode
- **Release|Win32** → `./Release/DNDCgo.dll`
- **Release|x64** → `./x64/Release/DNDCgo.dll`

Build via Visual Studio IDE or MSBuild. There is no cross-platform build system; this requires MSVC with MFC installed.

Precompiled headers: `StdAfx.h` / `StdAfx.cpp`.

## Compile-Time Feature Flags

Feature modules are toggled via `#define` in **`Source_main.h`** (and mirrored in `dndc_main.h` for GUI mode). The active set controls which `.cpp` files are compiled in:

| Flag | Effect |
|------|--------|
| `BASE` | Always defined — core model |
| `DEGUI` | Headless/console mode — removes MFC GUI dependency |
| `MANURE` | Enables ManureDNDC paths and `class_manure` |
| `BALANCE` | Carbon/nitrogen mass balance tracking (currently ON) |
| `HYDRO` | Extended hydrology module |
| `DROUGHT` | Drought simulation mode |
| `VOC` | Volatile organic compound emissions |
| `HOURLY` | Hourly time-step calculations |
| `PHOSPHOROUS` | Phosphorus cycling submodel |
| `ISOTOPE` | Isotope tracking |
| `DEBUG_CBALANCE` | Extra DOC/CO₂ balance debug columns in `class_model` (currently ON) |

## Switching Between GUI and Console Mode

**To enable headless/console mode (DEGUI):**
1. Define `#define DEGUI` in both `Source_main.h` and `dndc_main.h`
2. In `DNDCgo.def`: comment out `Model_link @1`, uncomment `OpenSesame @3`

**To restore GUI mode:**
1. Comment out `#define DEGUI` in both header files
2. In `DNDCgo.def`: uncomment `Model_link @1`, comment out `OpenSesame @3`

## Architecture

### DLL Exports (`DNDCgo.def`)
- `Model_link @1` — GUI entry point; called per simulation cell per year with full `MODEL_LINK_INFO` (window/DC pointers)
- `Cell_end @2` — post-simulation aggregation, called once per cell after all years complete
- `OpenSesame @3` — console/DEGUI entry point (replaces `Model_link` in headless builds)

### Core Simulation Loop (`DNDCgo.cpp`)
`Model_link` / `Model_linux` (depending on `DEGUI`) dispatches into an outer year loop. Each simulation year allocates a fresh `class_model` instance, calls `DNDC100go` (GUI) or `DNDClinuxgo` (DEGUI), then deletes it. Livestock runs use `DNDC101go`. The `MANURE` define adds an outer FarmField loop around the year loop.

### `class_model` (`Source_main.h` + `Dndc_main.cpp`)
The monolithic simulation class. All per-cell state — soil physics (`clay[]`, `theta[]`, `temp[]`, `soc[]`, `no3[]`, `nh4[]`, etc.), crop state (`Root_Wt[]`, `Leaf_Wt[]`, `GrainYield[]`, up to 8 concurrent crops), daily flux accumulators, climate inputs — lives here as public members. `MAXSOILLAYER = 280`, `MAXYEARS = 100`.

### Runtime File Paths (`RunPaths.h` / `RunPaths.cpp`)
Path constants (`ROOTDIR`, `OUTPUT`, `INTER`, `INPUTS`, `INTERMANAGE`, `LIBRARY`) are exported from the DLL. Default paths:
- `\DNDC\` (ROOTDIR) or `\ManureDNDC\` when `MANURE` is defined
- `\DNDC\RESULT\` (OUTPUT), `\DNDC\RESULT\INTER\` (INTER), etc.

### Submodels by File
| File(s) | Submodel |
|---------|----------|
| `Dndc_crop.cpp` | Crop growth (8-species polycrop) |
| `Dndc_manure0–10.cpp` | Manure decomposition & emissions |
| `Dndc_ManureComponent.cpp`, `Dndc_ManureRemoval.cpp`, `Dndc_ManureFeedlot.cpp`, `Dndc_ManureTreatment.cpp` | Manure system components |
| `Dndc_SoilChemistry.cpp` | Nitrification, denitrification, decomposition |
| `Dndc_SoilPhysics.cpp` | Soil thermal/hydraulic properties |
| `Dndc_CH4.cpp`, `Dndc_CH4peat.cpp` | Methane production/oxidation |
| `Dndc_Eh.cpp` | Redox potential |
| `Dndc_hydrology.cpp`, `Dndc_WT.cpp` | Water table and hydrology |
| `Dndc_balance.cpp` | Mass balance verification |
| `Dndc_balloon.cpp` | Gas diffusion/emission ("balloon" transport) |
| `Dndc_farming.cpp`, `Dndc_farmAgent.cpp` | Farm management operations |
| `Dndc_output.cpp`, `Dndc_RegionOutput.cpp`, `Dndc_regiondaily.cpp` | Output file writing |
| `Dndc_P.cpp` | Phosphorus submodel |
| `Dndc_VOCs.cpp` | VOC emissions |
| `Dndc_mapping.cpp`, `Dndc_paint.cpp`, `Dndc_shell.cpp` | GUI/graphics (inactive in DEGUI mode) |
| `Swine.cpp` / `Swine.h` | Swine livestock submodel |
| `SiteParaGo.cpp` / `SiteParaGo.h` | Site-level parameter management |
| `CreateInputFiles.cpp` / `CreateInputFile.h` | Input file generation utilities |
| `Dndc_tool.cpp` / `Dndc_tool.h` | Utility functions (file I/O, `note()`, `Penman_PET()`, etc.) |

### `DndcGraphics/` — GUI Host Application
A separate companion project containing the MFC GUI that loads `DNDCgo.dll`. Key components:
- `BatchRun.cpp/h` — batch simulation dialog (reads `batch_list.txt`)
- `CommandLine.cpp/h` — command-line argument parsing for headless invocation
- `CreateInputFile.cpp/h` — site/scenario input file generator

### `CDN-MANURE/` — Alternate Manure Build
Contains a prebuilt `DNDC95.exe` + `DNDCgo.dll` for Canadian manure study runs.

## Batch Run Input
`batch_list.txt` (and `Batch_list1.txt`) list `.dnd` site input files (one per line, full Windows paths) for batch simulations run through the GUI's BatchRun dialog.
