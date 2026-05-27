# Microsoft Developer Studio Generated NMAKE File, Based on dndc71.dsp
!IF "$(CFG)" == ""
CFG=dndc71 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to dndc71 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "dndc71 - Win32 Release" && "$(CFG)" != "dndc71 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dndc71.mak" CFG="dndc71 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dndc71 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dndc71 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "dndc71 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\Release\dndc71.hlp" ".\Release\dndc71.cnt" "$(OUTDIR)\dndc71.exe"


CLEAN :
	-@erase "$(INTDIR)\Asia.obj"
	-@erase "$(INTDIR)\data_set.obj"
	-@erase "$(INTDIR)\dndc71.obj"
	-@erase "$(INTDIR)\dndc71.pch"
	-@erase "$(INTDIR)\dndc71.res"
	-@erase "$(INTDIR)\dndc_climate.obj"
	-@erase "$(INTDIR)\dndc_desktop.obj"
	-@erase "$(INTDIR)\dndc_map.obj"
	-@erase "$(INTDIR)\dndc_region.obj"
	-@erase "$(INTDIR)\dndc_site.obj"
	-@erase "$(INTDIR)\dndc_tool.obj"
	-@erase "$(INTDIR)\dndc_uncertainty.obj"
	-@erase "$(INTDIR)\dndc_wizard.obj"
	-@erase "$(INTDIR)\Europe.obj"
	-@erase "$(INTDIR)\ExtractData.obj"
	-@erase "$(INTDIR)\GasFlux.obj"
	-@erase "$(INTDIR)\graph_maker.obj"
	-@erase "$(INTDIR)\graphexDoc.obj"
	-@erase "$(INTDIR)\graphexView.obj"
	-@erase "$(INTDIR)\hinaProvince.obj"
	-@erase "$(INTDIR)\IndiaState.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MonteCarlo.obj"
	-@erase "$(INTDIR)\NewCrop.obj"
	-@erase "$(INTDIR)\NewZealand.obj"
	-@erase "$(INTDIR)\NorthAmerica.obj"
	-@erase "$(INTDIR)\Oceania.obj"
	-@erase "$(INTDIR)\ountyCrops.obj"
	-@erase "$(INTDIR)\ountySave.obj"
	-@erase "$(INTDIR)\parse_data.obj"
	-@erase "$(INTDIR)\Region.obj"
	-@erase "$(INTDIR)\region_clim.obj"
	-@erase "$(INTDIR)\region_ES.obj"
	-@erase "$(INTDIR)\region_farm.obj"
	-@erase "$(INTDIR)\region_Shangrila.obj"
	-@erase "$(INTDIR)\region_site.obj"
	-@erase "$(INTDIR)\region_soil.obj"
	-@erase "$(INTDIR)\RegionMap.obj"
	-@erase "$(INTDIR)\RegionSelectCrops.obj"
	-@erase "$(INTDIR)\RegionYear.obj"
	-@erase "$(INTDIR)\SelectCrop.obj"
	-@erase "$(INTDIR)\SelectObsWT.obj"
	-@erase "$(INTDIR)\SitePage1.obj"
	-@erase "$(INTDIR)\SitePage10.obj"
	-@erase "$(INTDIR)\SitePage11.obj"
	-@erase "$(INTDIR)\SitePage12.obj"
	-@erase "$(INTDIR)\SitePage13.obj"
	-@erase "$(INTDIR)\SitePage14.obj"
	-@erase "$(INTDIR)\SitePage2.obj"
	-@erase "$(INTDIR)\SitePage3.obj"
	-@erase "$(INTDIR)\SitePage4.obj"
	-@erase "$(INTDIR)\SitePage5.obj"
	-@erase "$(INTDIR)\SitePage6.obj"
	-@erase "$(INTDIR)\SitePage7.obj"
	-@erase "$(INTDIR)\SitePage8.obj"
	-@erase "$(INTDIR)\SitePage9.obj"
	-@erase "$(INTDIR)\SitePara.obj"
	-@erase "$(INTDIR)\SitePSheet.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UncertaintyInput.obj"
	-@erase "$(INTDIR)\USAstate.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WizardCrops.obj"
	-@erase "$(INTDIR)\WizardResult.obj"
	-@erase "$(INTDIR)\WizardUncertainty.obj"
	-@erase "$(OUTDIR)\dndc71.exe"
	-@erase ".\Release\dndc71.cnt"
	-@erase ".\Release\dndc71.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\dndc71.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dndc71.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dndc71.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\dndc71.pdb" /machine:I386 /out:"$(OUTDIR)\dndc71.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Asia.obj" \
	"$(INTDIR)\data_set.obj" \
	"$(INTDIR)\dndc71.obj" \
	"$(INTDIR)\dndc_climate.obj" \
	"$(INTDIR)\dndc_desktop.obj" \
	"$(INTDIR)\dndc_map.obj" \
	"$(INTDIR)\dndc_region.obj" \
	"$(INTDIR)\dndc_site.obj" \
	"$(INTDIR)\dndc_tool.obj" \
	"$(INTDIR)\dndc_uncertainty.obj" \
	"$(INTDIR)\dndc_wizard.obj" \
	"$(INTDIR)\Europe.obj" \
	"$(INTDIR)\ExtractData.obj" \
	"$(INTDIR)\GasFlux.obj" \
	"$(INTDIR)\graph_maker.obj" \
	"$(INTDIR)\graphexDoc.obj" \
	"$(INTDIR)\graphexView.obj" \
	"$(INTDIR)\hinaProvince.obj" \
	"$(INTDIR)\IndiaState.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MonteCarlo.obj" \
	"$(INTDIR)\NewCrop.obj" \
	"$(INTDIR)\NewZealand.obj" \
	"$(INTDIR)\NorthAmerica.obj" \
	"$(INTDIR)\Oceania.obj" \
	"$(INTDIR)\ountyCrops.obj" \
	"$(INTDIR)\ountySave.obj" \
	"$(INTDIR)\parse_data.obj" \
	"$(INTDIR)\Region.obj" \
	"$(INTDIR)\region_clim.obj" \
	"$(INTDIR)\region_ES.obj" \
	"$(INTDIR)\region_farm.obj" \
	"$(INTDIR)\region_Shangrila.obj" \
	"$(INTDIR)\region_site.obj" \
	"$(INTDIR)\region_soil.obj" \
	"$(INTDIR)\RegionMap.obj" \
	"$(INTDIR)\RegionSelectCrops.obj" \
	"$(INTDIR)\RegionYear.obj" \
	"$(INTDIR)\SelectCrop.obj" \
	"$(INTDIR)\SelectObsWT.obj" \
	"$(INTDIR)\SitePage1.obj" \
	"$(INTDIR)\SitePage10.obj" \
	"$(INTDIR)\SitePage11.obj" \
	"$(INTDIR)\SitePage12.obj" \
	"$(INTDIR)\SitePage13.obj" \
	"$(INTDIR)\SitePage14.obj" \
	"$(INTDIR)\SitePage2.obj" \
	"$(INTDIR)\SitePage3.obj" \
	"$(INTDIR)\SitePage4.obj" \
	"$(INTDIR)\SitePage5.obj" \
	"$(INTDIR)\SitePage6.obj" \
	"$(INTDIR)\SitePage7.obj" \
	"$(INTDIR)\SitePage8.obj" \
	"$(INTDIR)\SitePage9.obj" \
	"$(INTDIR)\SitePara.obj" \
	"$(INTDIR)\SitePSheet.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UncertaintyInput.obj" \
	"$(INTDIR)\USAstate.obj" \
	"$(INTDIR)\WizardCrops.obj" \
	"$(INTDIR)\WizardResult.obj" \
	"$(INTDIR)\WizardUncertainty.obj" \
	"$(INTDIR)\dndc71.res"

"$(OUTDIR)\dndc71.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\Debug\dndc71.hlp" ".\Debug\dndc71.cnt" "..\DNDC95\Debug\DNDC95.exe" "$(OUTDIR)\dndc71.bsc"


CLEAN :
	-@erase "$(INTDIR)\Asia.obj"
	-@erase "$(INTDIR)\Asia.sbr"
	-@erase "$(INTDIR)\data_set.obj"
	-@erase "$(INTDIR)\data_set.sbr"
	-@erase "$(INTDIR)\dndc71.obj"
	-@erase "$(INTDIR)\dndc71.pch"
	-@erase "$(INTDIR)\dndc71.res"
	-@erase "$(INTDIR)\dndc71.sbr"
	-@erase "$(INTDIR)\dndc_climate.obj"
	-@erase "$(INTDIR)\dndc_climate.sbr"
	-@erase "$(INTDIR)\dndc_desktop.obj"
	-@erase "$(INTDIR)\dndc_desktop.sbr"
	-@erase "$(INTDIR)\dndc_map.obj"
	-@erase "$(INTDIR)\dndc_map.sbr"
	-@erase "$(INTDIR)\dndc_region.obj"
	-@erase "$(INTDIR)\dndc_region.sbr"
	-@erase "$(INTDIR)\dndc_site.obj"
	-@erase "$(INTDIR)\dndc_site.sbr"
	-@erase "$(INTDIR)\dndc_tool.obj"
	-@erase "$(INTDIR)\dndc_tool.sbr"
	-@erase "$(INTDIR)\dndc_uncertainty.obj"
	-@erase "$(INTDIR)\dndc_uncertainty.sbr"
	-@erase "$(INTDIR)\dndc_wizard.obj"
	-@erase "$(INTDIR)\dndc_wizard.sbr"
	-@erase "$(INTDIR)\Europe.obj"
	-@erase "$(INTDIR)\Europe.sbr"
	-@erase "$(INTDIR)\ExtractData.obj"
	-@erase "$(INTDIR)\ExtractData.sbr"
	-@erase "$(INTDIR)\GasFlux.obj"
	-@erase "$(INTDIR)\GasFlux.sbr"
	-@erase "$(INTDIR)\graph_maker.obj"
	-@erase "$(INTDIR)\graph_maker.sbr"
	-@erase "$(INTDIR)\graphexDoc.obj"
	-@erase "$(INTDIR)\graphexDoc.sbr"
	-@erase "$(INTDIR)\graphexView.obj"
	-@erase "$(INTDIR)\graphexView.sbr"
	-@erase "$(INTDIR)\hinaProvince.obj"
	-@erase "$(INTDIR)\hinaProvince.sbr"
	-@erase "$(INTDIR)\IndiaState.obj"
	-@erase "$(INTDIR)\IndiaState.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MonteCarlo.obj"
	-@erase "$(INTDIR)\MonteCarlo.sbr"
	-@erase "$(INTDIR)\NewCrop.obj"
	-@erase "$(INTDIR)\NewCrop.sbr"
	-@erase "$(INTDIR)\NewZealand.obj"
	-@erase "$(INTDIR)\NewZealand.sbr"
	-@erase "$(INTDIR)\NorthAmerica.obj"
	-@erase "$(INTDIR)\NorthAmerica.sbr"
	-@erase "$(INTDIR)\Oceania.obj"
	-@erase "$(INTDIR)\Oceania.sbr"
	-@erase "$(INTDIR)\ountyCrops.obj"
	-@erase "$(INTDIR)\ountyCrops.sbr"
	-@erase "$(INTDIR)\ountySave.obj"
	-@erase "$(INTDIR)\ountySave.sbr"
	-@erase "$(INTDIR)\parse_data.obj"
	-@erase "$(INTDIR)\parse_data.sbr"
	-@erase "$(INTDIR)\Region.obj"
	-@erase "$(INTDIR)\Region.sbr"
	-@erase "$(INTDIR)\region_clim.obj"
	-@erase "$(INTDIR)\region_clim.sbr"
	-@erase "$(INTDIR)\region_ES.obj"
	-@erase "$(INTDIR)\region_ES.sbr"
	-@erase "$(INTDIR)\region_farm.obj"
	-@erase "$(INTDIR)\region_farm.sbr"
	-@erase "$(INTDIR)\region_Shangrila.obj"
	-@erase "$(INTDIR)\region_Shangrila.sbr"
	-@erase "$(INTDIR)\region_site.obj"
	-@erase "$(INTDIR)\region_site.sbr"
	-@erase "$(INTDIR)\region_soil.obj"
	-@erase "$(INTDIR)\region_soil.sbr"
	-@erase "$(INTDIR)\RegionMap.obj"
	-@erase "$(INTDIR)\RegionMap.sbr"
	-@erase "$(INTDIR)\RegionSelectCrops.obj"
	-@erase "$(INTDIR)\RegionSelectCrops.sbr"
	-@erase "$(INTDIR)\RegionYear.obj"
	-@erase "$(INTDIR)\RegionYear.sbr"
	-@erase "$(INTDIR)\SelectCrop.obj"
	-@erase "$(INTDIR)\SelectCrop.sbr"
	-@erase "$(INTDIR)\SelectObsWT.obj"
	-@erase "$(INTDIR)\SelectObsWT.sbr"
	-@erase "$(INTDIR)\SitePage1.obj"
	-@erase "$(INTDIR)\SitePage1.sbr"
	-@erase "$(INTDIR)\SitePage10.obj"
	-@erase "$(INTDIR)\SitePage10.sbr"
	-@erase "$(INTDIR)\SitePage11.obj"
	-@erase "$(INTDIR)\SitePage11.sbr"
	-@erase "$(INTDIR)\SitePage12.obj"
	-@erase "$(INTDIR)\SitePage12.sbr"
	-@erase "$(INTDIR)\SitePage13.obj"
	-@erase "$(INTDIR)\SitePage13.sbr"
	-@erase "$(INTDIR)\SitePage14.obj"
	-@erase "$(INTDIR)\SitePage14.sbr"
	-@erase "$(INTDIR)\SitePage2.obj"
	-@erase "$(INTDIR)\SitePage2.sbr"
	-@erase "$(INTDIR)\SitePage3.obj"
	-@erase "$(INTDIR)\SitePage3.sbr"
	-@erase "$(INTDIR)\SitePage4.obj"
	-@erase "$(INTDIR)\SitePage4.sbr"
	-@erase "$(INTDIR)\SitePage5.obj"
	-@erase "$(INTDIR)\SitePage5.sbr"
	-@erase "$(INTDIR)\SitePage6.obj"
	-@erase "$(INTDIR)\SitePage6.sbr"
	-@erase "$(INTDIR)\SitePage7.obj"
	-@erase "$(INTDIR)\SitePage7.sbr"
	-@erase "$(INTDIR)\SitePage8.obj"
	-@erase "$(INTDIR)\SitePage8.sbr"
	-@erase "$(INTDIR)\SitePage9.obj"
	-@erase "$(INTDIR)\SitePage9.sbr"
	-@erase "$(INTDIR)\SitePara.obj"
	-@erase "$(INTDIR)\SitePara.sbr"
	-@erase "$(INTDIR)\SitePSheet.obj"
	-@erase "$(INTDIR)\SitePSheet.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UncertaintyInput.obj"
	-@erase "$(INTDIR)\UncertaintyInput.sbr"
	-@erase "$(INTDIR)\USAstate.obj"
	-@erase "$(INTDIR)\USAstate.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WizardCrops.obj"
	-@erase "$(INTDIR)\WizardCrops.sbr"
	-@erase "$(INTDIR)\WizardResult.obj"
	-@erase "$(INTDIR)\WizardResult.sbr"
	-@erase "$(INTDIR)\WizardUncertainty.obj"
	-@erase "$(INTDIR)\WizardUncertainty.sbr"
	-@erase "$(OUTDIR)\dndc71.bsc"
	-@erase "$(OUTDIR)\DNDC95.pdb"
	-@erase "..\DNDC95\Debug\DNDC95.exe"
	-@erase "..\DNDC95\Debug\DNDC95.ilk"
	-@erase ".\Debug\dndc71.cnt"
	-@erase ".\Debug\dndc71.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\dndc71.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dndc71.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dndc71.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Asia.sbr" \
	"$(INTDIR)\data_set.sbr" \
	"$(INTDIR)\dndc71.sbr" \
	"$(INTDIR)\dndc_climate.sbr" \
	"$(INTDIR)\dndc_desktop.sbr" \
	"$(INTDIR)\dndc_map.sbr" \
	"$(INTDIR)\dndc_region.sbr" \
	"$(INTDIR)\dndc_site.sbr" \
	"$(INTDIR)\dndc_tool.sbr" \
	"$(INTDIR)\dndc_uncertainty.sbr" \
	"$(INTDIR)\dndc_wizard.sbr" \
	"$(INTDIR)\Europe.sbr" \
	"$(INTDIR)\ExtractData.sbr" \
	"$(INTDIR)\GasFlux.sbr" \
	"$(INTDIR)\graph_maker.sbr" \
	"$(INTDIR)\graphexDoc.sbr" \
	"$(INTDIR)\graphexView.sbr" \
	"$(INTDIR)\hinaProvince.sbr" \
	"$(INTDIR)\IndiaState.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MonteCarlo.sbr" \
	"$(INTDIR)\NewCrop.sbr" \
	"$(INTDIR)\NewZealand.sbr" \
	"$(INTDIR)\NorthAmerica.sbr" \
	"$(INTDIR)\Oceania.sbr" \
	"$(INTDIR)\ountyCrops.sbr" \
	"$(INTDIR)\ountySave.sbr" \
	"$(INTDIR)\parse_data.sbr" \
	"$(INTDIR)\Region.sbr" \
	"$(INTDIR)\region_clim.sbr" \
	"$(INTDIR)\region_ES.sbr" \
	"$(INTDIR)\region_farm.sbr" \
	"$(INTDIR)\region_Shangrila.sbr" \
	"$(INTDIR)\region_site.sbr" \
	"$(INTDIR)\region_soil.sbr" \
	"$(INTDIR)\RegionMap.sbr" \
	"$(INTDIR)\RegionSelectCrops.sbr" \
	"$(INTDIR)\RegionYear.sbr" \
	"$(INTDIR)\SelectCrop.sbr" \
	"$(INTDIR)\SelectObsWT.sbr" \
	"$(INTDIR)\SitePage1.sbr" \
	"$(INTDIR)\SitePage10.sbr" \
	"$(INTDIR)\SitePage11.sbr" \
	"$(INTDIR)\SitePage12.sbr" \
	"$(INTDIR)\SitePage13.sbr" \
	"$(INTDIR)\SitePage14.sbr" \
	"$(INTDIR)\SitePage2.sbr" \
	"$(INTDIR)\SitePage3.sbr" \
	"$(INTDIR)\SitePage4.sbr" \
	"$(INTDIR)\SitePage5.sbr" \
	"$(INTDIR)\SitePage6.sbr" \
	"$(INTDIR)\SitePage7.sbr" \
	"$(INTDIR)\SitePage8.sbr" \
	"$(INTDIR)\SitePage9.sbr" \
	"$(INTDIR)\SitePara.sbr" \
	"$(INTDIR)\SitePSheet.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UncertaintyInput.sbr" \
	"$(INTDIR)\USAstate.sbr" \
	"$(INTDIR)\WizardCrops.sbr" \
	"$(INTDIR)\WizardResult.sbr" \
	"$(INTDIR)\WizardUncertainty.sbr"

"$(OUTDIR)\dndc71.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\DNDC95.pdb" /debug /machine:I386 /out:"C:/DNDC95/Debug/DNDC95.exe" /pdbtype:sept /out:"/DNDC95/Debug/DNDC95.exe" /out:"/DNDC95/Debug/DNDC95.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Asia.obj" \
	"$(INTDIR)\data_set.obj" \
	"$(INTDIR)\dndc71.obj" \
	"$(INTDIR)\dndc_climate.obj" \
	"$(INTDIR)\dndc_desktop.obj" \
	"$(INTDIR)\dndc_map.obj" \
	"$(INTDIR)\dndc_region.obj" \
	"$(INTDIR)\dndc_site.obj" \
	"$(INTDIR)\dndc_tool.obj" \
	"$(INTDIR)\dndc_uncertainty.obj" \
	"$(INTDIR)\dndc_wizard.obj" \
	"$(INTDIR)\Europe.obj" \
	"$(INTDIR)\ExtractData.obj" \
	"$(INTDIR)\GasFlux.obj" \
	"$(INTDIR)\graph_maker.obj" \
	"$(INTDIR)\graphexDoc.obj" \
	"$(INTDIR)\graphexView.obj" \
	"$(INTDIR)\hinaProvince.obj" \
	"$(INTDIR)\IndiaState.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MonteCarlo.obj" \
	"$(INTDIR)\NewCrop.obj" \
	"$(INTDIR)\NewZealand.obj" \
	"$(INTDIR)\NorthAmerica.obj" \
	"$(INTDIR)\Oceania.obj" \
	"$(INTDIR)\ountyCrops.obj" \
	"$(INTDIR)\ountySave.obj" \
	"$(INTDIR)\parse_data.obj" \
	"$(INTDIR)\Region.obj" \
	"$(INTDIR)\region_clim.obj" \
	"$(INTDIR)\region_ES.obj" \
	"$(INTDIR)\region_farm.obj" \
	"$(INTDIR)\region_Shangrila.obj" \
	"$(INTDIR)\region_site.obj" \
	"$(INTDIR)\region_soil.obj" \
	"$(INTDIR)\RegionMap.obj" \
	"$(INTDIR)\RegionSelectCrops.obj" \
	"$(INTDIR)\RegionYear.obj" \
	"$(INTDIR)\SelectCrop.obj" \
	"$(INTDIR)\SelectObsWT.obj" \
	"$(INTDIR)\SitePage1.obj" \
	"$(INTDIR)\SitePage10.obj" \
	"$(INTDIR)\SitePage11.obj" \
	"$(INTDIR)\SitePage12.obj" \
	"$(INTDIR)\SitePage13.obj" \
	"$(INTDIR)\SitePage14.obj" \
	"$(INTDIR)\SitePage2.obj" \
	"$(INTDIR)\SitePage3.obj" \
	"$(INTDIR)\SitePage4.obj" \
	"$(INTDIR)\SitePage5.obj" \
	"$(INTDIR)\SitePage6.obj" \
	"$(INTDIR)\SitePage7.obj" \
	"$(INTDIR)\SitePage8.obj" \
	"$(INTDIR)\SitePage9.obj" \
	"$(INTDIR)\SitePara.obj" \
	"$(INTDIR)\SitePSheet.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UncertaintyInput.obj" \
	"$(INTDIR)\USAstate.obj" \
	"$(INTDIR)\WizardCrops.obj" \
	"$(INTDIR)\WizardResult.obj" \
	"$(INTDIR)\WizardUncertainty.obj" \
	"$(INTDIR)\dndc71.res"

"..\DNDC95\Debug\DNDC95.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("dndc71.dep")
!INCLUDE "dndc71.dep"
!ELSE 
!MESSAGE Warning: cannot find "dndc71.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dndc71 - Win32 Release" || "$(CFG)" == "dndc71 - Win32 Debug"
SOURCE=.\Asia.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\Asia.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\Asia.obj"	"$(INTDIR)\Asia.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\data_set.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\data_set.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\data_set.obj"	"$(INTDIR)\data_set.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc71.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc71.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc71.obj"	"$(INTDIR)\dndc71.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\hlp\dndc71.hpj

!IF  "$(CFG)" == "dndc71 - Win32 Release"

OutDir=.\Release
TargetName=dndc71
InputPath=.\hlp\dndc71.hpj
InputName=dndc71
USERDEP__DNDC7="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	

"$(INTDIR)\dndc71.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__DNDC7)
	<<tempfile.bat 
	@echo off 
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
<< 
	

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

OutDir=.\Debug
TargetName=DNDC95
InputPath=.\hlp\dndc71.hpj
InputName=dndc71
USERDEP__DNDC7="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	

"$(INTDIR)\dndc71.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__DNDC7)
	<<tempfile.bat 
	@echo off 
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
<< 
	

!ENDIF 

SOURCE=.\dndc71.rc

"$(INTDIR)\dndc71.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\dndc_climate.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_climate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_climate.obj"	"$(INTDIR)\dndc_climate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc_desktop.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_desktop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_desktop.obj"	"$(INTDIR)\dndc_desktop.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc_map.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_map.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_map.obj"	"$(INTDIR)\dndc_map.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc_region.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_region.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_region.obj"	"$(INTDIR)\dndc_region.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc_site.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_site.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_site.obj"	"$(INTDIR)\dndc_site.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc_tool.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_tool.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_tool.obj"	"$(INTDIR)\dndc_tool.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc_uncertainty.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_uncertainty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_uncertainty.obj"	"$(INTDIR)\dndc_uncertainty.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\dndc_wizard.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\dndc_wizard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\dndc_wizard.obj"	"$(INTDIR)\dndc_wizard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\Europe.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\Europe.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\Europe.obj"	"$(INTDIR)\Europe.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\ExtractData.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\ExtractData.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\ExtractData.obj"	"$(INTDIR)\ExtractData.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\GasFlux.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\GasFlux.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\GasFlux.obj"	"$(INTDIR)\GasFlux.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\graph_maker.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\graph_maker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\graph_maker.obj"	"$(INTDIR)\graph_maker.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\graphexDoc.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\graphexDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\graphexDoc.obj"	"$(INTDIR)\graphexDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\graphexView.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\graphexView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\graphexView.obj"	"$(INTDIR)\graphexView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\hinaProvince.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\hinaProvince.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\hinaProvince.obj"	"$(INTDIR)\hinaProvince.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\IndiaState.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\IndiaState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\IndiaState.obj"	"$(INTDIR)\IndiaState.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\MonteCarlo.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\MonteCarlo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\MonteCarlo.obj"	"$(INTDIR)\MonteCarlo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\NewCrop.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\NewCrop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\NewCrop.obj"	"$(INTDIR)\NewCrop.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\NewZealand.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\NewZealand.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\NewZealand.obj"	"$(INTDIR)\NewZealand.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\NorthAmerica.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\NorthAmerica.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\NorthAmerica.obj"	"$(INTDIR)\NorthAmerica.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\Oceania.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\Oceania.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\Oceania.obj"	"$(INTDIR)\Oceania.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\ountyCrops.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\ountyCrops.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\ountyCrops.obj"	"$(INTDIR)\ountyCrops.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\ountySave.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\ountySave.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\ountySave.obj"	"$(INTDIR)\ountySave.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\parse_data.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\parse_data.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\parse_data.obj"	"$(INTDIR)\parse_data.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\Region.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\Region.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\Region.obj"	"$(INTDIR)\Region.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\region_clim.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\region_clim.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\region_clim.obj"	"$(INTDIR)\region_clim.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\region_ES.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\region_ES.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\region_ES.obj"	"$(INTDIR)\region_ES.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\region_farm.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\region_farm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\region_farm.obj"	"$(INTDIR)\region_farm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\region_Shangrila.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\region_Shangrila.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\region_Shangrila.obj"	"$(INTDIR)\region_Shangrila.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\region_site.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\region_site.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\region_site.obj"	"$(INTDIR)\region_site.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\region_soil.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\region_soil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\region_soil.obj"	"$(INTDIR)\region_soil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\RegionMap.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\RegionMap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\RegionMap.obj"	"$(INTDIR)\RegionMap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\RegionSelectCrops.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\RegionSelectCrops.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\RegionSelectCrops.obj"	"$(INTDIR)\RegionSelectCrops.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\RegionYear.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\RegionYear.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\RegionYear.obj"	"$(INTDIR)\RegionYear.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SelectCrop.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SelectCrop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SelectCrop.obj"	"$(INTDIR)\SelectCrop.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SelectObsWT.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SelectObsWT.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SelectObsWT.obj"	"$(INTDIR)\SelectObsWT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage1.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage1.obj"	"$(INTDIR)\SitePage1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage10.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage10.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage10.obj"	"$(INTDIR)\SitePage10.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage11.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage11.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage11.obj"	"$(INTDIR)\SitePage11.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage12.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage12.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage12.obj"	"$(INTDIR)\SitePage12.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage13.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage13.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage13.obj"	"$(INTDIR)\SitePage13.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage14.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage14.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage14.obj"	"$(INTDIR)\SitePage14.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage2.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage2.obj"	"$(INTDIR)\SitePage2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage3.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage3.obj"	"$(INTDIR)\SitePage3.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage4.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage4.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage4.obj"	"$(INTDIR)\SitePage4.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage5.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage5.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage5.obj"	"$(INTDIR)\SitePage5.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage6.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage6.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage6.obj"	"$(INTDIR)\SitePage6.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage7.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage7.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage7.obj"	"$(INTDIR)\SitePage7.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage8.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage8.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage8.obj"	"$(INTDIR)\SitePage8.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePage9.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePage9.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePage9.obj"	"$(INTDIR)\SitePage9.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePara.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePara.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePara.obj"	"$(INTDIR)\SitePara.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\SitePSheet.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\SitePSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\SitePSheet.obj"	"$(INTDIR)\SitePSheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\dndc71.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\dndc71.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\dndc71.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\dndc71.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\UncertaintyInput.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\UncertaintyInput.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\UncertaintyInput.obj"	"$(INTDIR)\UncertaintyInput.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\USAstate.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\USAstate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\USAstate.obj"	"$(INTDIR)\USAstate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\WizardCrops.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\WizardCrops.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\WizardCrops.obj"	"$(INTDIR)\WizardCrops.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\WizardResult.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\WizardResult.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\WizardResult.obj"	"$(INTDIR)\WizardResult.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\WizardUncertainty.cpp

!IF  "$(CFG)" == "dndc71 - Win32 Release"


"$(INTDIR)\WizardUncertainty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"


"$(INTDIR)\WizardUncertainty.obj"	"$(INTDIR)\WizardUncertainty.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\dndc71.pch"


!ENDIF 

SOURCE=.\Resource.h

!IF  "$(CFG)" == "dndc71 - Win32 Release"

TargetName=dndc71
InputPath=.\Resource.h

".\hlp\dndc71.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

TargetName=DNDC95
InputPath=.\Resource.h

".\hlp\DNDC95.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ENDIF 

SOURCE=.\hlp\dndc71.cnt

!IF  "$(CFG)" == "dndc71 - Win32 Release"

OutDir=.\Release
InputPath=.\hlp\dndc71.cnt
InputName=dndc71

"$(INTDIR)\dndc71.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "hlp\$(InputName).cnt" $(OutDir)
<< 
	

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

OutDir=.\Debug
InputPath=.\hlp\dndc71.cnt
InputName=dndc71

"$(INTDIR)\dndc71.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "hlp\$(InputName).cnt" $(OutDir)
<< 
	

!ENDIF 


!ENDIF 

