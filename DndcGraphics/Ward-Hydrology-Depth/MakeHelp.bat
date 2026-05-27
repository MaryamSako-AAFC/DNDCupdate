@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DNDC71.HPJ. >"hlp\dndc71.hm"
echo. >>"hlp\dndc71.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\dndc71.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\dndc71.hm"
echo. >>"hlp\dndc71.hm"
echo // Prompts (IDP_*) >>"hlp\dndc71.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\dndc71.hm"
echo. >>"hlp\dndc71.hm"
echo // Resources (IDR_*) >>"hlp\dndc71.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\dndc71.hm"
echo. >>"hlp\dndc71.hm"
echo // Dialogs (IDD_*) >>"hlp\dndc71.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\dndc71.hm"
echo. >>"hlp\dndc71.hm"
echo // Frame Controls (IDW_*) >>"hlp\dndc71.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\dndc71.hm"
REM -- Make help for Project DNDC71


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\dndc71.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\dndc71.hlp" goto :Error
if not exist "hlp\dndc71.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\dndc71.hlp" Debug
if exist Debug\nul copy "hlp\dndc71.cnt" Debug
if exist Release\nul copy "hlp\dndc71.hlp" Release
if exist Release\nul copy "hlp\dndc71.cnt" Release
echo.
goto :done

:Error
echo hlp\dndc71.hpj(1) : error: Problem encountered creating help file

:done
echo.
