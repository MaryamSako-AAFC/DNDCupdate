# Microsoft Developer Studio Generated NMAKE File, Based on DNDCgo.dsp
!IF "$(CFG)" == ""
CFG=DNDCgo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DNDCgo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DNDCgo - Win32 Release" && "$(CFG)" != "DNDCgo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DNDCgo.mak" CFG="DNDCgo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DNDCgo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DNDCgo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DNDCgo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DNDCgo.dll"

!ELSE 

ALL : "dndc71 - Win32 Release" "$(OUTDIR)\DNDCgo.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"dndc71 - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Dndc_balance.obj"
	-@erase "$(INTDIR)\Dndc_balloon.obj"
	-@erase "$(INTDIR)\Dndc_CH4.obj"
	-@erase "$(INTDIR)\Dndc_crop0.obj"
	-@erase "$(INTDIR)\Dndc_crop1.obj"
	-@erase "$(INTDIR)\Dndc_crop2.obj"
	-@erase "$(INTDIR)\Dndc_crop3.obj"
	-@erase "$(INTDIR)\Dndc_crop4.obj"
	-@erase "$(INTDIR)\Dndc_crop5.obj"
	-@erase "$(INTDIR)\Dndc_data.obj"
	-@erase "$(INTDIR)\Dndc_Eh.obj"
	-@erase "$(INTDIR)\Dndc_farming.obj"
	-@erase "$(INTDIR)\Dndc_main.obj"
	-@erase "$(INTDIR)\Dndc_mapping.obj"
	-@erase "$(INTDIR)\Dndc_output.obj"
	-@erase "$(INTDIR)\Dndc_paint.obj"
	-@erase "$(INTDIR)\Dndc_regiondaily.obj"
	-@erase "$(INTDIR)\Dndc_RegionOutput.obj"
	-@erase "$(INTDIR)\Dndc_SoilChemistry.obj"
	-@erase "$(INTDIR)\Dndc_SoilPhysics.obj"
	-@erase "$(INTDIR)\Dndc_summary.obj"
	-@erase "$(INTDIR)\Dndc_tool.obj"
	-@erase "$(INTDIR)\DNDCgo.obj"
	-@erase "$(INTDIR)\DNDCgo.pch"
	-@erase "$(INTDIR)\DNDCgo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DNDCgo.dll"
	-@erase "$(OUTDIR)\DNDCgo.exp"
	-@erase "$(OUTDIR)\DNDCgo.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DNDCgo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DNDCgo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DNDCgo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\DNDCgo.pdb" /machine:I386 /def:".\DNDCgo.def" /out:"$(OUTDIR)\DNDCgo.dll" /implib:"$(OUTDIR)\DNDCgo.lib" 
DEF_FILE= \
	".\DNDCgo.def"
LINK32_OBJS= \
	"$(INTDIR)\Dndc_balance.obj" \
	"$(INTDIR)\Dndc_balloon.obj" \
	"$(INTDIR)\Dndc_CH4.obj" \
	"$(INTDIR)\Dndc_crop0.obj" \
	"$(INTDIR)\Dndc_crop1.obj" \
	"$(INTDIR)\Dndc_crop2.obj" \
	"$(INTDIR)\Dndc_crop3.obj" \
	"$(INTDIR)\Dndc_crop4.obj" \
	"$(INTDIR)\Dndc_crop5.obj" \
	"$(INTDIR)\Dndc_data.obj" \
	"$(INTDIR)\Dndc_Eh.obj" \
	"$(INTDIR)\Dndc_farming.obj" \
	"$(INTDIR)\Dndc_main.obj" \
	"$(INTDIR)\Dndc_mapping.obj" \
	"$(INTDIR)\Dndc_output.obj" \
	"$(INTDIR)\Dndc_paint.obj" \
	"$(INTDIR)\Dndc_regiondaily.obj" \
	"$(INTDIR)\Dndc_RegionOutput.obj" \
	"$(INTDIR)\Dndc_SoilChemistry.obj" \
	"$(INTDIR)\Dndc_SoilPhysics.obj" \
	"$(INTDIR)\Dndc_summary.obj" \
	"$(INTDIR)\Dndc_tool.obj" \
	"$(INTDIR)\DNDCgo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DNDCgo.res"

"$(OUTDIR)\DNDCgo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DNDCgo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DNDCgo.dll"

!ELSE 

ALL : "dndc71 - Win32 Debug" "$(OUTDIR)\DNDCgo.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"dndc71 - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Dndc_balance.obj"
	-@erase "$(INTDIR)\Dndc_balloon.obj"
	-@erase "$(INTDIR)\Dndc_CH4.obj"
	-@erase "$(INTDIR)\Dndc_crop0.obj"
	-@erase "$(INTDIR)\Dndc_crop1.obj"
	-@erase "$(INTDIR)\Dndc_crop2.obj"
	-@erase "$(INTDIR)\Dndc_crop3.obj"
	-@erase "$(INTDIR)\Dndc_crop4.obj"
	-@erase "$(INTDIR)\Dndc_crop5.obj"
	-@erase "$(INTDIR)\Dndc_data.obj"
	-@erase "$(INTDIR)\Dndc_Eh.obj"
	-@erase "$(INTDIR)\Dndc_farming.obj"
	-@erase "$(INTDIR)\Dndc_main.obj"
	-@erase "$(INTDIR)\Dndc_mapping.obj"
	-@erase "$(INTDIR)\Dndc_output.obj"
	-@erase "$(INTDIR)\Dndc_paint.obj"
	-@erase "$(INTDIR)\Dndc_regiondaily.obj"
	-@erase "$(INTDIR)\Dndc_RegionOutput.obj"
	-@erase "$(INTDIR)\Dndc_SoilChemistry.obj"
	-@erase "$(INTDIR)\Dndc_SoilPhysics.obj"
	-@erase "$(INTDIR)\Dndc_summary.obj"
	-@erase "$(INTDIR)\Dndc_tool.obj"
	-@erase "$(INTDIR)\DNDCgo.obj"
	-@erase "$(INTDIR)\DNDCgo.pch"
	-@erase "$(INTDIR)\DNDCgo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DNDCgo.dll"
	-@erase "$(OUTDIR)\DNDCgo.exp"
	-@erase "$(OUTDIR)\DNDCgo.ilk"
	-@erase "$(OUTDIR)\DNDCgo.lib"
	-@erase "$(OUTDIR)\DNDCgo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DNDCgo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DNDCgo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DNDCgo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\DNDCgo.pdb" /debug /machine:I386 /def:".\DNDCgo.def" /out:"$(OUTDIR)\DNDCgo.dll" /implib:"$(OUTDIR)\DNDCgo.lib" /pdbtype:sept /out:"DNDC95/Debug/DNDCgo.dll" /out:"DNDC95/Debug/DNDCgo.dll" 
DEF_FILE= \
	".\DNDCgo.def"
LINK32_OBJS= \
	"$(INTDIR)\Dndc_balance.obj" \
	"$(INTDIR)\Dndc_balloon.obj" \
	"$(INTDIR)\Dndc_CH4.obj" \
	"$(INTDIR)\Dndc_crop0.obj" \
	"$(INTDIR)\Dndc_crop1.obj" \
	"$(INTDIR)\Dndc_crop2.obj" \
	"$(INTDIR)\Dndc_crop3.obj" \
	"$(INTDIR)\Dndc_crop4.obj" \
	"$(INTDIR)\Dndc_crop5.obj" \
	"$(INTDIR)\Dndc_data.obj" \
	"$(INTDIR)\Dndc_Eh.obj" \
	"$(INTDIR)\Dndc_farming.obj" \
	"$(INTDIR)\Dndc_main.obj" \
	"$(INTDIR)\Dndc_mapping.obj" \
	"$(INTDIR)\Dndc_output.obj" \
	"$(INTDIR)\Dndc_paint.obj" \
	"$(INTDIR)\Dndc_regiondaily.obj" \
	"$(INTDIR)\Dndc_RegionOutput.obj" \
	"$(INTDIR)\Dndc_SoilChemistry.obj" \
	"$(INTDIR)\Dndc_SoilPhysics.obj" \
	"$(INTDIR)\Dndc_summary.obj" \
	"$(INTDIR)\Dndc_tool.obj" \
	"$(INTDIR)\DNDCgo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DNDCgo.res"

"$(OUTDIR)\DNDCgo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("DNDCgo.dep")
!INCLUDE "DNDCgo.dep"
!ELSE 
!MESSAGE Warning: cannot find "DNDCgo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DNDCgo - Win32 Release" || "$(CFG)" == "DNDCgo - Win32 Debug"
SOURCE=.\Dndc_balance.cpp

"$(INTDIR)\Dndc_balance.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_balloon.cpp

"$(INTDIR)\Dndc_balloon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_CH4.cpp

"$(INTDIR)\Dndc_CH4.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_crop0.cpp

"$(INTDIR)\Dndc_crop0.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_crop1.cpp

"$(INTDIR)\Dndc_crop1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_crop2.cpp

"$(INTDIR)\Dndc_crop2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_crop3.cpp

"$(INTDIR)\Dndc_crop3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_crop4.cpp

"$(INTDIR)\Dndc_crop4.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_crop5.cpp

"$(INTDIR)\Dndc_crop5.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_data.cpp

"$(INTDIR)\Dndc_data.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_Eh.cpp

"$(INTDIR)\Dndc_Eh.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_farming.cpp

"$(INTDIR)\Dndc_farming.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_main.cpp

"$(INTDIR)\Dndc_main.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_mapping.cpp

"$(INTDIR)\Dndc_mapping.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_output.cpp

"$(INTDIR)\Dndc_output.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_paint.cpp

"$(INTDIR)\Dndc_paint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_regiondaily.cpp

"$(INTDIR)\Dndc_regiondaily.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_RegionOutput.cpp

"$(INTDIR)\Dndc_RegionOutput.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_SoilChemistry.cpp

"$(INTDIR)\Dndc_SoilChemistry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_SoilPhysics.cpp

"$(INTDIR)\Dndc_SoilPhysics.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_summary.cpp

"$(INTDIR)\Dndc_summary.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\Dndc_tool.cpp

"$(INTDIR)\Dndc_tool.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\DNDCgo.cpp

"$(INTDIR)\DNDCgo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DNDCgo.pch"


SOURCE=.\DNDCgo.rc

"$(INTDIR)\DNDCgo.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DNDCgo - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DNDCgo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DNDCgo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DNDCgo - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DNDCgo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DNDCgo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "DNDCgo - Win32 Release"

"dndc71 - Win32 Release" : 
   cd "\DndcGraphics"
   $(MAKE) /$(MAKEFLAGS) /F .\dndc71.mak CFG="dndc71 - Win32 Release" 
   cd "..\DNDC95"

"dndc71 - Win32 ReleaseCLEAN" : 
   cd "\DndcGraphics"
   $(MAKE) /$(MAKEFLAGS) /F .\dndc71.mak CFG="dndc71 - Win32 Release" RECURSE=1 CLEAN 
   cd "..\DNDC95"

!ELSEIF  "$(CFG)" == "DNDCgo - Win32 Debug"

"dndc71 - Win32 Debug" : 
   cd "\DndcGraphics"
   $(MAKE) /$(MAKEFLAGS) /F .\dndc71.mak CFG="dndc71 - Win32 Debug" 
   cd "..\DNDC95"

"dndc71 - Win32 DebugCLEAN" : 
   cd "\DndcGraphics"
   $(MAKE) /$(MAKEFLAGS) /F .\dndc71.mak CFG="dndc71 - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\DNDC95"

!ENDIF 


!ENDIF 

