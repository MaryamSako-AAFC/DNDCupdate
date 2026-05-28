<!-- 
## Setup Instructions for DNDC on Windows ##

What you need:\
Visual Studio (+ required components will be mentioned afterwards)\
DNDC_Folders.zip

#### Visual Studio Setup ####

Open Visual Studio Installer\
Install the latest Visual Studio available. Both Professional and Community have been tested to work for this.\
After installation, click on Modify.\
     Under Workloads, checkmark Desktop development with C++\
     Under Individual components, checkmark the following:
* Git for Windows
* NuGet package manager
* Text Template Transformation
* vcpkg package manager
* C# and Visual Basic Roslyn compilers
* C++ Build Insights
* C++ CMake tools for Windows
* MSBuild
* MSVC Build Tools for x64/x86 (Latest)
* MSVC v142 - VS 2019 C++ x64/x86 build tools (v14.29-16.11)
* MSVC v143 - VS 2022 ARM build tools (v14.44-17.14)
* MSVC v143 - VS 2022 C++ x64/x86 build tools (v14.44-17.14)
* Visual C++ v14 Redistributable MSMs
* Visual C++ v14 Redistributable Update
* .NET profiling tools
* C++ profiling tools
* Just-In-Time debugger
* MSVC AddressSanitizer
* Test Adapter for Boost.Test
* Test Adapter for Google Test
* C# and Visual Basic
* C++ core features
* intelliCode
* Graphics debugger and GPU profiler for DirectX
* C++ ATL for x64/x86 (Latest MSVC)
* C++ MFC for x64/x86 (Latest MSVC)
* C++ v14.29 (16.11) ATL for v142 build tools (x86 & x64)
* C++ v14.29 (16.11) MFC for v142 build tools (x86 & x64)
* C++ v14.44 (17.14) ATL for v143 build tools (x86 & x64)
* C++ v14.44 (17.14) MFC for v143 build tools (x86 & x64)
* Windows 11 SDK (10.0.22621.0)
* Windows 11 SDK (10.0.26100.8249)
* Windows Performance Toolkit
    Press Modify and wait for downloads
* You can also get to the Modifying tab by going to Visual Studio -> Tools (top bar) -> Get Tools and Features...


#### Moving DNDC Folders to the appropriate directory ####

Once you download the DNDC_Folders.zip (most commonly to the downloads folder on your computer) Follow the steps below:
Cut the zip file (With Ctrl+X) and navigate to your root directory (typically (C:) Drive)\
Open the root directory and move your zip file here (With Ctrl+V)\
OR Extract your zip file to the root directory by right clicking on the zip file -> Extract All... -> Browse (In pop up window) -> and navigate to root directory -> Select Folder -> Extract.\
After this you are welcome to delete the zip file as you no longer need it.\
Once DNDC_Folders is in root directory, navigate to it and open it.\
In DNDC_Folders you will find two folders: ApplicationStarter and DNDC\
Move both folders to the root directory. You can do this with Ctrl+X, navigate back to the root directory, and Ctrl+V\
Delete DNDC_Folders folder with delete keyboard button\
Open ApplicationStarter folder and find Release folder\
Rename Release to anything of preference. For these instructions I will rename it to Release2.\

#### Opening the project and Configuring Visual Studio Project Settings ####

find DNDCgo.sln file in ApplicationStarter folder
either double click on file to open in Visual Studio OR\
open Visual Studio 
click "open a rroject or solution"
* Navigate to DNDCgo.sln and open the file
* Click trust project/folder/directory button
On Solution Explorer (usually at the right) navigate to project dndc95\
Right click on the project and click on the "Set as Startup Project" option\
Right click on on the project again and click on "Properties"\ 
In the pop up window called "dndc95 Property Pages", set the settings as such:
* In the top bar, set as follows:
  `Configuration: Release` amd `Platform: Active(Win32)`
* Then in Configuration Properties -> General, set or keep as the following:
`Output Directory     ..\Release`, `Intermediate Directory     .\Release\`, `Target Name     $(ProjectName)`, `Configuration Type:     Application(.exe)`
* Then in Linker -> General, set or keep as the following:
`Output File     ../Release/DNDC95.exe`
* Then click on any empty space in the Property pages window, so that the Apply button is not greyed out anymore. 
* Click on Apply, then OK.
Back in the Visual Studio window, locate the configuration selection at the top of the window (Right after the undo/redo arrow buttons) 
Change or keep as `Release` and `x86`\
Navigate to Build in the top bar options
* Find Configuration Manager in the options
* In the Configuration Manager window check that everything is set up as such:
  * `Active Solution Configuration: Release`
  * `Active Solution Platform: x86`
  * under Configuration and Platform for each project:
    * `Release` and `Win32` must be chosen
run the program (by clicking hollow green triangle button on the top bar)\
THE END
-->

## Setup Instructions for DNDC on Windows ##

What you need:  
Visual Studio (+ required components will be mentioned afterwards)  
DNDC_2026May_MS.zip  

#### Visual Studio Setup ####

Open Visual Studio Installer  
Install the latest Visual Studio available. Both Professional and Community have been tested to work for this.  
After installation, click on Modify.  

Under Workloads, checkmark Desktop development with C++  

Under Individual components, checkmark the following:  
* Git for Windows  
* NuGet package manager  
* Text Template Transformation  
* vcpkg package manager  
* C# and Visual Basic Roslyn compilers  
* C++ Build Insights  
* C++ CMake tools for Windows  
* MSBuild  
* MSVC Build Tools for x64/x86 (Latest)  
* MSVC v142 - VS 2019 C++ x64/x86 build tools (v14.29-16.11)  
* MSVC v143 - VS 2022 ARM build tools (v14.44-17.14)  
* MSVC v143 - VS 2022 C++ x64/x86 build tools (v14.44-17.14)  
* Visual C++ v14 Redistributable MSMs  
* Visual C++ v14 Redistributable Update  
* .NET profiling tools  
* C++ profiling tools  
* Just-In-Time debugger  
* MSVC AddressSanitizer  
* Test Adapter for Boost.Test  
* Test Adapter for Google Test  
* C# and Visual Basic  
* C++ core features  
* IntelliCode  
* Graphics debugger and GPU profiler for DirectX  
* C++ ATL for x64/x86 (Latest MSVC)  
* C++ MFC for x64/x86 (Latest MSVC)  
* C++ v14.29 (16.11) ATL for v142 build tools (x86 & x64)  
* C++ v14.29 (16.11) MFC for v142 build tools (x86 & x64)  
* C++ v14.44 (17.14) ATL for v143 build tools (x86 & x64)  
* C++ v14.44 (17.14) MFC for v143 build tools (x86 & x64)  
* Windows 11 SDK (10.0.22621.0)  
* Windows 11 SDK (10.0.26100.8249)  
* Windows Performance Toolkit  

Press Modify and wait for downloads  

You can also get to the Modifying tab by going to:  
Visual Studio → Tools (top bar) → Get Tools and Features...  

---

#### Moving DNDC Folders to the appropriate directory ####

Once you download the DNDC_2026May_MS.zip (most commonly to the downloads folder on your computer) follow the steps below:  

Cut the zip file (with Ctrl+X) and navigate to your root directory (typically (C:) Drive)  
Open the root directory and move your zip file here (with Ctrl+V)  

OR  

Extract your zip file to the root directory by right clicking on the zip file → Extract All... → Browse (in pop up window) → navigate to root directory → Select Folder → Extract.  

After this you are welcome to delete the zip file as you no longer need it.  

Once DNDC_2026May_MS is in root directory, navigate to it and open it.  

In DNDC_2026May_MS you will find two folders: ApplicationStarter and DNDC  

Move both folders to the root directory. You can do this with Ctrl+X, navigate back to the root directory, and Ctrl+V  

Delete DNDC_2026May_MS folder with delete keyboard button  

Open ApplicationStarter folder and find Release folder  

Rename Release to anything of preference. For these instructions I will rename it to Release2.  

---

#### Opening the project and Configuring Visual Studio Project Settings ####

Find DNDCgo.sln file in ApplicationStarter folder  

Either double click on file to open in Visual Studio OR  
Open Visual Studio  
Click "open a project or solution"  

Navigate to DNDCgo.sln and open the file  
Click Trust and Continue button  

On Solution Explorer (usually at the right) navigate to project dndc95  

Right click on the project and click on the "Set as Startup Project" option  

Right click on the project again and click on "Properties"  

In the pop up window called "dndc95 Property Pages", set the settings as such:  

In the top bar, set as follows:  
`Configuration: Release` and `Platform: Active(Win32) or Win32`  

Then in Configuration Properties → General, set or keep as the following:  
`Output Directory:     ..\Release`  
`Intermediate Directory:     .\Release\`  
`Target Name:     $(ProjectName)`  
`Configuration Type:     Application(.exe)`  

Then in Linker → General, set or keep as the following:  
`Output File:     ../Release/DNDC95.exe`  

Then click on any empty space in the Property pages window, so that the Apply button is not greyed out anymore.  

Click on Apply, then OK.  

Back in the Visual Studio window, locate the configuration selection at the top of the window (right after the undo/redo arrow buttons)  

Change or keep as `Release` and `x86`  

Navigate to Build in the top bar options  

Find Configuration Manager in the options  

In the Configuration Manager window check that everything is set up as such:  
* `Active Solution Configuration: Release`  
* `Active Solution Platform: x86`  
* Under Configuration and Platform for each project:  
  * `Release` and `Win32` must be chosen  

Run the program (by clicking hollow green triangle button on the top bar. It will take a minute)






        
