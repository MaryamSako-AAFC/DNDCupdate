# Microsoft Developer Studio Project File - Name="dndc71" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dndc71 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dndc71.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/dndc71", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dndc71 - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./map" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "./map" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /profile /map /debug /machine:I386 /out:"C:\DNDC95\Debug\DNDC95.exe"

!ENDIF 

# Begin Target

# Name "dndc71 - Win32 Release"
# Name "dndc71 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BatchRun.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateInputFile.cpp
# End Source File
# Begin Source File

SOURCE=.\data_set.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc71.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\dndc71.hpj

!IF  "$(CFG)" == "dndc71 - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__DNDC7="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=dndc71
InputPath=.\hlp\dndc71.hpj
InputName=dndc71

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__DNDC7="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=DNDC95
InputPath=.\hlp\dndc71.hpj
InputName=dndc71

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dndc71.rc
# End Source File
# Begin Source File

SOURCE=.\dndc_climate.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_InputFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManningChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManningLand.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure11.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure12.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_ManureFarmCrops.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_map.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_region.cpp
# End Source File
# Begin Source File

SOURCE=..\dndc95\Dndc_regiondaily.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_RegionFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_save.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_site.cpp
# End Source File
# Begin Source File

SOURCE=.\DNDC_SoilProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_tool.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_uncertainty.cpp
# End Source File
# Begin Source File

SOURCE=.\dndc_wizard.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_YieldPredict.cpp
# End Source File
# Begin Source File

SOURCE=.\DNDCgoing.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawDrought.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtractData.cpp
# End Source File
# Begin Source File

SOURCE=.\FarmCompost.cpp
# End Source File
# Begin Source File

SOURCE=.\FarmLagoon.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobeData.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobeDataExtract.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobeMap.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobeResult.cpp
# End Source File
# Begin Source File

SOURCE=.\graph_maker.cpp
# End Source File
# Begin Source File

SOURCE=.\graphexDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\graphexView.cpp
# End Source File
# Begin Source File

SOURCE=.\Help_AutoFert.cpp
# End Source File
# Begin Source File

SOURCE=.\ListFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureCompost.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureCycle.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureDigester.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureField.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureGrazing.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureHousing.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureLagoon.cpp
# End Source File
# Begin Source File

SOURCE=.\ManureSilo.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MapSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\MonteCarlo.cpp
# End Source File
# Begin Source File

SOURCE=.\MonteCarloNote.cpp
# End Source File
# Begin Source File

SOURCE=.\MonteCarloParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\MonteCarloRegionSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\msado15.cpp
# End Source File
# Begin Source File

SOURCE=.\NewCrop.cpp
# End Source File
# Begin Source File

SOURCE=.\ombineFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadDNDfile.cpp
# End Source File
# Begin Source File

SOURCE=.\region_Shangrila.cpp
# End Source File
# Begin Source File

SOURCE=.\RegionInput.cpp
# End Source File
# Begin Source File

SOURCE=.\RegionMap.cpp
# End Source File
# Begin Source File

SOURCE=.\RegionSelectCrops.cpp
# End Source File
# Begin Source File

SOURCE=.\RegionYear.cpp
# End Source File
# Begin Source File

SOURCE=.\RunoffCN.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveDNDfile.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveSoilYear.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\SCSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectIrriFile.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectRegionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectShapeMap.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage1.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage10.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage11.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage15.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage2.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage3.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage4.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage5.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage6.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage7.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage8.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePage9.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePara.cpp
# End Source File
# Begin Source File

SOURCE=.\SitePSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WizardCrops.cpp
# End Source File
# Begin Source File

SOURCE=.\WizardResult.cpp
# End Source File
# Begin Source File

SOURCE=.\WizardUncertainty.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BatchRun.h
# End Source File
# Begin Source File

SOURCE=.\CreateInputFile.h
# End Source File
# Begin Source File

SOURCE=.\data_set.h
# End Source File
# Begin Source File

SOURCE=K:\include\dirent.h
# End Source File
# Begin Source File

SOURCE=.\dndc71.h
# End Source File
# Begin Source File

SOURCE=.\dndc_main.h
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManningChannel.h
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManningLand.h
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure11.h
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure12.h
# End Source File
# Begin Source File

SOURCE=.\dndc_ManureFarmCrops.h
# End Source File
# Begin Source File

SOURCE=.\dndc_map.h
# End Source File
# Begin Source File

SOURCE=.\dndc_RegionFiles.h
# End Source File
# Begin Source File

SOURCE=.\dndc_save.h
# End Source File
# Begin Source File

SOURCE=.\DNDC_SoilProfile.h
# End Source File
# Begin Source File

SOURCE=.\dndc_tool.h
# End Source File
# Begin Source File

SOURCE=.\Dndc_YieldPredict.h
# End Source File
# Begin Source File

SOURCE=.\DNDCgoing.h
# End Source File
# Begin Source File

SOURCE=.\dprintf.h
# End Source File
# Begin Source File

SOURCE=.\DrawDrought.h
# End Source File
# Begin Source File

SOURCE=.\ExtractData.h
# End Source File
# Begin Source File

SOURCE=.\FarmCompost.h
# End Source File
# Begin Source File

SOURCE=.\FarmLagoon.h
# End Source File
# Begin Source File

SOURCE=.\gd.h
# End Source File
# Begin Source File

SOURCE=.\gd_io.h
# End Source File
# Begin Source File

SOURCE=.\gdcache.h
# End Source File
# Begin Source File

SOURCE=.\gdfontg.h
# End Source File
# Begin Source File

SOURCE=.\gdfontl.h
# End Source File
# Begin Source File

SOURCE=.\gdfontmb.h
# End Source File
# Begin Source File

SOURCE=.\gdfonts.h
# End Source File
# Begin Source File

SOURCE=.\gdfontt.h
# End Source File
# Begin Source File

SOURCE=.\gdfx.h
# End Source File
# Begin Source File

SOURCE=.\gdhelpers.h
# End Source File
# Begin Source File

SOURCE=.\GlobeData.h
# End Source File
# Begin Source File

SOURCE=.\GlobeDataExtract.h
# End Source File
# Begin Source File

SOURCE=.\GlobeMap.h
# End Source File
# Begin Source File

SOURCE=.\GlobeResult.h
# End Source File
# Begin Source File

SOURCE=.\graph_maker.h
# End Source File
# Begin Source File

SOURCE=.\graphexDoc.h
# End Source File
# Begin Source File

SOURCE=.\graphexView.h
# End Source File
# Begin Source File

SOURCE=.\Help_AutoFert.h
# End Source File
# Begin Source File

SOURCE=.\ListFile.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ManureApplication.h
# End Source File
# Begin Source File

SOURCE=.\ManureCompost.h
# End Source File
# Begin Source File

SOURCE=.\ManureCycle.h
# End Source File
# Begin Source File

SOURCE=.\ManureDigester.h
# End Source File
# Begin Source File

SOURCE=.\ManureField.h
# End Source File
# Begin Source File

SOURCE=.\ManureGrazing.h
# End Source File
# Begin Source File

SOURCE=.\ManureHousing.h
# End Source File
# Begin Source File

SOURCE=.\ManureLagoon.h
# End Source File
# Begin Source File

SOURCE=.\ManurePen.h
# End Source File
# Begin Source File

SOURCE=.\ManureSilo.h
# End Source File
# Begin Source File

SOURCE=.\MapLayer.h
# End Source File
# Begin Source File

SOURCE=.\MapObjects2.h
# End Source File
# Begin Source File

SOURCE=.\MapSelect.h
# End Source File
# Begin Source File

SOURCE=.\MonteCarlo.h
# End Source File
# Begin Source File

SOURCE=.\MonteCarloNote.h
# End Source File
# Begin Source File

SOURCE=.\MonteCarloParameters.h
# End Source File
# Begin Source File

SOURCE=.\MonteCarloRegionSelect.h
# End Source File
# Begin Source File

SOURCE=.\msado15.h
# End Source File
# Begin Source File

SOURCE=.\NewCrop.h
# End Source File
# Begin Source File

SOURCE=.\NewDBase.h
# End Source File
# Begin Source File

SOURCE=.\ombineFiles.h
# End Source File
# Begin Source File

SOURCE=.\RegionInput.h
# End Source File
# Begin Source File

SOURCE=.\RegionMap.h
# End Source File
# Begin Source File

SOURCE=.\RegionSelectCrops.h
# End Source File
# Begin Source File

SOURCE=.\RegionYear.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "dndc71 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=dndc71
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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
	
# End Custom Build

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=DNDC95
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RunoffCN.h
# End Source File
# Begin Source File

SOURCE=.\SaveSoilYear.h
# End Source File
# Begin Source File

SOURCE=.\ScreenMonitor.h
# End Source File
# Begin Source File

SOURCE=.\SCSDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectIrriFile.h
# End Source File
# Begin Source File

SOURCE=.\SelectRegionDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectShapeMap.h
# End Source File
# Begin Source File

SOURCE=.\SitePage1.h
# End Source File
# Begin Source File

SOURCE=.\SitePage10.h
# End Source File
# Begin Source File

SOURCE=.\SitePage11.h
# End Source File
# Begin Source File

SOURCE=.\SitePage15.h
# End Source File
# Begin Source File

SOURCE=.\SitePage2.h
# End Source File
# Begin Source File

SOURCE=.\SitePage3.h
# End Source File
# Begin Source File

SOURCE=.\SitePage4.h
# End Source File
# Begin Source File

SOURCE=.\SitePage5.h
# End Source File
# Begin Source File

SOURCE=.\SitePage6.h
# End Source File
# Begin Source File

SOURCE=.\SitePage7.h
# End Source File
# Begin Source File

SOURCE=.\SitePage8.h
# End Source File
# Begin Source File

SOURCE=.\SitePage9.h
# End Source File
# Begin Source File

SOURCE=.\SitePara.h
# End Source File
# Begin Source File

SOURCE=.\SitePSheet.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\WizardCrops.h
# End Source File
# Begin Source File

SOURCE=.\WizardResult.h
# End Source File
# Begin Source File

SOURCE=.\WizardUncertainty.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\BITMAP1.BMP
# End Source File
# Begin Source File

SOURCE=.\res\dndc71.ico
# End Source File
# Begin Source File

SOURCE=.\res\dndc71.rc2
# End Source File
# Begin Source File

SOURCE=.\res\graphexDoc.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Hand.cur
# End Source File
# Begin Source File

SOURCE=.\RES\menu2.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Pan.cur
# End Source File
# Begin Source File

SOURCE=.\sdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\ZoomIn.cur
# End Source File
# Begin Source File

SOURCE=.\RES\ZoomOut.cur
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\dndc71.cnt

!IF  "$(CFG)" == "dndc71 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\dndc71.cnt
InputName=dndc71

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "dndc71 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\dndc71.cnt
InputName=dndc71

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Group "Map"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Map\font.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\font.h
# End Source File
# Begin Source File

SOURCE=.\Map\map.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\map.h
# End Source File
# Begin Source File

SOURCE=.\Map\moaddresslocation.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moaddresslocation.h
# End Source File
# Begin Source File

SOURCE=.\Map\mochartrenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mochartrenderer.h
# End Source File
# Begin Source File

SOURCE=.\Map\moclassbreaksrenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moclassbreaksrenderer.h
# End Source File
# Begin Source File

SOURCE=.\Map\modataconnection.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\modataconnection.h
# End Source File
# Begin Source File

SOURCE=.\Map\modatum.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\modatum.h
# End Source File
# Begin Source File

SOURCE=.\Map\modotdensityrenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\modotdensityrenderer.h
# End Source File
# Begin Source File

SOURCE=.\Map\moellipse.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moellipse.h
# End Source File
# Begin Source File

SOURCE=.\Map\moeventrenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moeventrenderer.h
# End Source File
# Begin Source File

SOURCE=.\Map\mofield.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mofield.h
# End Source File
# Begin Source File

SOURCE=.\Map\mofields.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mofields.h
# End Source File
# Begin Source File

SOURCE=.\Map\mogeocoder.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mogeocoder.h
# End Source File
# Begin Source File

SOURCE=.\Map\mogeocoordsys.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mogeocoordsys.h
# End Source File
# Begin Source File

SOURCE=.\Map\mogeodataset.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mogeodataset.h
# End Source File
# Begin Source File

SOURCE=.\Map\mogeodatasets.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mogeodatasets.h
# End Source File
# Begin Source File

SOURCE=.\Map\mogeoevent.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mogeoevent.h
# End Source File
# Begin Source File

SOURCE=.\Map\mogeotransformation.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mogeotransformation.h
# End Source File
# Begin Source File

SOURCE=.\Map\mogrouprenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mogrouprenderer.h
# End Source File
# Begin Source File

SOURCE=.\Map\moimagelayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moimagelayer.h
# End Source File
# Begin Source File

SOURCE=.\Map\molabelplacer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\molabelplacer.h
# End Source File
# Begin Source File

SOURCE=.\Map\molabelrenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\molabelrenderer.h
# End Source File
# Begin Source File

SOURCE=.\Map\molayers.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\molayers.h
# End Source File
# Begin Source File

SOURCE=.\Map\moline.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moline.h
# End Source File
# Begin Source File

SOURCE=.\Map\momaplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\momaplayer.h
# End Source File
# Begin Source File

SOURCE=.\Map\moparts.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moparts.h
# End Source File
# Begin Source File

SOURCE=.\Map\moplacelocator.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moplacelocator.h
# End Source File
# Begin Source File

SOURCE=.\Map\mopoint.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mopoint.h
# End Source File
# Begin Source File

SOURCE=.\Map\mopoints.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mopoints.h
# End Source File
# Begin Source File

SOURCE=.\Map\mopolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mopolygon.h
# End Source File
# Begin Source File

SOURCE=.\Map\moprimemeridian.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moprimemeridian.h
# End Source File
# Begin Source File

SOURCE=.\Map\moprojcoordsys.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moprojcoordsys.h
# End Source File
# Begin Source File

SOURCE=.\Map\moprojection.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\moprojection.h
# End Source File
# Begin Source File

SOURCE=.\Map\morecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\morecordset.h
# End Source File
# Begin Source File

SOURCE=.\Map\morectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\morectangle.h
# End Source File
# Begin Source File

SOURCE=.\Map\mospheroid.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mospheroid.h
# End Source File
# Begin Source File

SOURCE=.\Map\mostandardizer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mostandardizer.h
# End Source File
# Begin Source File

SOURCE=.\Map\mostatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mostatistics.h
# End Source File
# Begin Source File

SOURCE=.\Map\mostrings.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mostrings.h
# End Source File
# Begin Source File

SOURCE=.\Map\mosymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mosymbol.h
# End Source File
# Begin Source File

SOURCE=.\Map\motable.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\motable.h
# End Source File
# Begin Source File

SOURCE=.\Map\motabledesc.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\motabledesc.h
# End Source File
# Begin Source File

SOURCE=.\Map\motextsymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\motextsymbol.h
# End Source File
# Begin Source File

SOURCE=.\Map\motrackinglayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\motrackinglayer.h
# End Source File
# Begin Source File

SOURCE=.\Map\mounit.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mounit.h
# End Source File
# Begin Source File

SOURCE=.\Map\movaluemaprenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\movaluemaprenderer.h
# End Source File
# Begin Source File

SOURCE=.\Map\mozrenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Map\mozrenderer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section dndc71 : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
# Section dndc71 : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid1.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section dndc71 : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section dndc71 : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid1.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section dndc71 : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
