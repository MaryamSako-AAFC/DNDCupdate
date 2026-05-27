# Microsoft Developer Studio Project File - Name="DNDCgo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DNDCgo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DNDCgo.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DNDCgo - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "DNDCgo - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\DNDCgo.def" /out:"C:\DNDC95\Debug\DNDCgo.dll" /pdbtype:sept /out:"/dndc95/debug/DNDCgo.dll"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "DNDCgo - Win32 Release"
# Name "DNDCgo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CreateInputFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_balance.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_balloon.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_CH4.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_CH4peat.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_crop.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_data.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_Eh.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_farmAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_farming.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_hydrology.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_main.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure0.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure1.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure10.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure2.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure3.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure5.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure6.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure7.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_manure9.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManureComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManureFeedlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManureRemoval.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_ManureTreatment.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_mapping.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_output.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_P.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_paint.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_regiondaily.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_RegionOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_shell.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_SoilChemistry.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_SoilPhysics.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_summary.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_tool.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_VOCs.cpp
# End Source File
# Begin Source File

SOURCE=.\Dndc_WT.cpp
# End Source File
# Begin Source File

SOURCE=.\DNDCgo.cpp
# End Source File
# Begin Source File

SOURCE=.\DNDCgo.def

!IF  "$(CFG)" == "DNDCgo - Win32 Release"

!ELSEIF  "$(CFG)" == "DNDCgo - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DNDCgo.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CreateInputFile.h
# End Source File
# Begin Source File

SOURCE=.\Dndc_shell.h
# End Source File
# Begin Source File

SOURCE=.\Dndc_tool.h
# End Source File
# Begin Source File

SOURCE=.\DNDCgo.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Source_main.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
