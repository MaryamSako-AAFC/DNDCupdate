<!-- # Linux Development Environment

This is a guide on how to set up your the linux development environment that will be used to work on DNDC.

## Steps:

### 1. WSL
> 1. Open WSL on your computer
> 2. Login using username and password which will be your organization's credentials. Password will be invisible when typing. 

### 2. Necessary downloads
> 1. Update packages with `sudo apt update` to check for updates and not have any issues while installing new software
> 2. install compiler with `sudo apt install gcc` where gcc is a compiler for C/C++. Check gcc is installed with `gcc --version`.\
>     The reason we choose GCC as the compiler versus options like Clang and MSVC is due to its reliability and stability.
> 3. install g++ with `sudo apt install g++` where g++ is a also a compiler for C++ specifically and adds extra features over gcc. Check g++ is installed with `g++ --version`.
> 4. install cmake with `sudo apt install cmake` where cmake is the a tool that builds and packages software across platforms (different operating systems). 
> 5. install debugger with `sudo apt install gdb` where gdb is the GNU debugger used to inspect programs, set breakpoints, and analyze crashes durin runtime. A debugger is essential for development. Check gbd is installed with `gdb --version`.
> 6. install IDE (Integrated Development Environment) for organized workflow and development. The chosen IDE is Qt Creator due to it being free and having integrated GUI development according to this [source](https://linux.how2shout.com/c-c-programming-software-linux/#ubuntu-debian). To install qtcreator write `sudo apt install qt6-*{dev,doc}* qtcreator`. We must install qt6 as can be seen in the command due to open Qt Creator. However it is not required to use Qt and Qt Creator can be used and excels at general C++ development. Check Qt Creator is installed with `qtcreator --version`.
> 7. To launch Qt Creator write `qtcreator` and then enter. A window of the program should pop up in a few seconds. 

### 2(b). Quicker method for necessary downloads
> 1. Update packages with `sudo apt update`.
> 2. install compiler, g++, cmake, debugger, and IDE with `sudo apt install gcc g++ cmake gdb qt6-*{dev,doc}* qtcreator`.
> 3. Check installation with `[program name] --version`. This would be `gcc --version`, `g++ v--version`, `cmake --version`, `gdb --version`, `gtcreator --version`.
> 4. launch Qt Creator with `qtcreator`.

### Possible errors and warnings:
* libEGL warning: failed to get driver name for fd -1 Explanation: 
* libEGL warning: MESA-LOADER: failed to retrieve device information Explanation: 
* libEGL warning: failed to get driver name for fd -1 Explanation: 
* MESA: error: ZINK: failed to choose pdev Explanation: 
* libEGL warning: egl: failed to create dri2 screen Explanation: 

Detailed steps\
quicker way\
Explanation of error\
Explanation of why download anything\
Sources for explanations\
-->

# Linux Development Environment

This guide explains how to set up the Linux development environment used for working on DNDC.

---

## Steps

### 1. WSL (Windows Subsystem for Linux)

1. Open WSL on your computer  
2. Log in using your organization credentials (Username and password)
   * Note: Your password will not be visible while typing  

---

### 2. Necessary Downloads

1. **Update package lists**

```bash
sudo apt update
````

You will be asked to retype your password. This command ensures your system has the latest package information and avoids issues during installation.

***

2.  **Install GCC (C Compiler)**

```bash
sudo apt install gcc
```

*   GCC is the GNU compiler primarily used for C (and partial C++)
*   Verify installation:

```bash
gcc --version
```

*   GCC is chosen for its reliability and stability

***

3.  **Install G++ (C++ Compiler)**

```bash
sudo apt install g++
```

*   `g++` is specifically designed for compiling C++ programs
*   It includes full C++ support beyond what `gcc` provides

Verify installation:

```bash
g++ --version
```

***

4.  **Install CMake (Build System)**

```bash
sudo apt install cmake
```

*   CMake is used to configure and build software across different platforms

***

5.  **Install GDB (Debugger)**

```bash
sudo apt install gdb
```

*   GDB is the GNU debugger used to:
    *   Inspect programs during execution
    *   Set breakpoints
    *   Analyze crashes at runtime

Verify installation:

```bash
gdb --version
```

***

6.  **Install Qt Creator (IDE)** and core libraries and headers

```bash
sudo apt install qtcreator build-essential
```

*   Qt Creator is a free Integrated Development Environment (IDE) which supports:
    *   C++ development
    *   GUI development with Qt (if installed optionally)

Note:

*   Using Qt is **not required**; Qt Creator can and excels at general C++ development

Verify installation:

```bash
qtcreator --version
```
***

## 2(b). Quicker Installation Method

1.  Update packages:

```bash
sudo apt update
```

2.  Install all required tools at once:

```bash
sudo apt install gcc g++ cmake gdb build-essential qtcreator
```

3.  Verify installations:

```bash
gcc --version
g++ --version
cmake --version
gdb --version
qtcreator --version
```
***

## Possible Errors and Warnings

These warnings are common when running GUI applications (like Qt Creator) in WSL without full graphics support.

*   **`libEGL warning: failed to get driver name for fd -1`**
    *   Explanation: Graphics driver access failed. This is common in WSL and usually harmless.

*   **`libEGL warning: MESA-LOADER: failed to retrieve device information`**
    *   Explanation: The Mesa graphics library cannot detect GPU information. Typically not critical.

*   **`MESA: error: ZINK: failed to choose pdev`**
    *   Explanation: The Zink (OpenGL-over-Vulkan) driver failed to initialize. This often occurs in virtualized environments.

*   **`libEGL warning: egl: failed to create dri2 screen`**
    *   Explanation: The system cannot create a direct rendering interface. Usually due to limited graphics support in WSL.\

These warnings should not affect Qt Creator from working and can generally be ignored

<!-- # DNDC Installation and Launching

First install DNDC zip into local folders. To copy files to wsl, unzip is needed. To install unzip you will need `sudo apt-get install unzip` where you will be prompted to enter your password. Then to move the folder we can use the command `cp '/mnt/c/Users/.../DNDC-Guelph-linux-port.zip' /home/username` where the first path is the path to the DNDC zip folder in your computer. Be aware that `/mnt/c/` replaces `C:\` part of your path as well as all `\` need to be changed to `/` for linux path. The second path is where your folder will end up. If you would like to copy the folder to your current working directory, you can use the result for `pwd` for the second path in the command. check that you have the folder in the intended location with `ls secondpath`. Now we can use the unzip program with `unzip DNDC-Guelph-linux-port.zip`. Now to run the program there are two ways:

Through Qt Creator:
open qtcreator with `qtcreator`
click `Open Project` button 
find `DNDC-Guelph-linux-port` folder which will be unzipped and open it (by double clicking on it)
find `CMakeLists.txt` file and click (choose) it
Click the `Open` button that contains a folder logo in the button
Now the project will open. Find run button (green triangle) and click it 

Through command line:
```
cd DNDC-Guelph-linux-port
mkdir build
cd build
cmake ..
cmake --build .
ls
dndc
```
-->
# DNDC Installation and Launching

This guide explains how to install and run the DNDC project using WSL.

---

## 1. Copy the DNDC Files into WSL

### Install `unzip`

```bash
sudo apt install unzip
````

*   Installs the `unzip` tool required to extract `.zip` files
*   You will be prompted to enter your password

***

### Copy the DNDC zip file into WSL

```bash
cp '/mnt/c/Users/.../DNDC-Guelph-linux-port.zip' /home/username
```

**Explanation:**

*   `cp` copies a file from one location to another
*   `/mnt/c/Users/...` is the path to your file on Windows
*   `/home/username` is the destination inside WSL

**Important:**

*   `C:\` → `/mnt/c/` in WSL
*   Replace all `\` with `/`

***

### Optional: copy to your current directory

```bash
pwd
```

*   Displays your current working directory

Use the output as the destination path in the `cp` command.

***

### Verify the file was copied

```bash
ls /home/username
```

*   Lists files in the directory
*   You should see `DNDC-Guelph-linux-port.zip`

***

## 2. Extract the Project

```bash
unzip DNDC-Guelph-linux-port.zip
```

*   Extracts the zip file
*   Creates the folder: `DNDC-Guelph-linux-port`

***
<!--
## 3. Download and Configure Missing files & folders
* Download example folder that contains Batch_list.txt file
* move example folder to DNDC folder with `cp '/mnt/c/Users/.../Example.zip' /home/<username>/DNDC-Guelph-linux-port` where the first path is where the example folder is in your C drive and the second path is where your DNDC folder is in linux. Change linux path accordingly to match your path, which you can find if you're in the intended target directory with `pwd`.
* Check that the file is in your linux DNDC directory with `ls` (or install `tree` command for a tree view of your file structure with `sudo apt install tree`) 
* unzip example folder with `unzip Example.zip`
* move into the Example folder with `cd Example`
* if Batch_list.txt has the wrong name then rename it with `mv previous_name.txt Batch_list.txt`
* open Batch_list.txt with vim to edit it with `vim Batch_list.txt`
* To edit in vim press I for Insert. Now you can type in the text file.
* to exit press the ESC key and type ":wq" to save your changes and quit vim or just ":q" if you want to quit without saving your changes
* Now that you're back in the command line, within your Example folder, move into your dnd folder with `cd dnd`
* You will see your dnd files. Copy down the file names and copy your path with `pwd` then copying the result of the command with Ctrl+C
* move back to your Example folder with `cd ..` and open Batch_list.txt again with `vim Batch_list.txt`
* Edit the file by replacing the paths to the dnd files with the pwd results (you can paste with Ctrl+V in INSERT mode) that you got earlier followed by the filename.dnd for each one. Example: change C:\dndc\Example\dnd\2014_nd_amenia_1.dnd to /home/sakom/DNDC/Example/dnd/2014_nd_amenia_1.dnd. After changing all the paths, save and quit. 
* Back at the command line, move to the climate folder with `cd climate`
* Get the path of the folder with `pwd` and copy the result with Ctrl+C. Also copy the filenames in the climate folder.
* Move back to the Example folder with `cd ..`
* Move into the dnd folder with `cd dnd`
* Open each file in the dnd folder with `vim filename.dnd`
* Locate the Climate files paths and, just like previously, change the windows paths into the linux paths with your pwd results and copied down filenames
* After editing each dnd file, make sure to save then quit vim. Do the same for all dnd files in the folder. 
* Get "Library" folder that contains "Lib_crop", "Lib_livestock", and "Lib_soil" subfolders with corresponding files.
* Move Library folder from windows to linux with `cp '/mnt/c/Users/.../Library/' /home/<username>/DNDC-Guelph-linux-port/` where the first path is where the example folder is in your C drive and the second path is where your DNDC folder is in linux. 
* Check that the file is in your DNDC directory with `ls` or `tree`.

## 4. Edit program code
    *  Launch Qt Creator:

```bash
qtcreator
```

*  In the Qt Creator interface:
    *   Click **Open Project**
    *   Navigate to `DNDC-Guelph-linux-port`
    *   Select `CMakeLists.txt`
    *   Click **Open**

* Navigate to main.cpp (DNDC -> dndc -> Source Files -> main.cpp) and open file (by double clicking on it)
* Change the following lines:
    * line 46: Change "./" into your DNDC directory path "/home/<username>/DNDC-Guelph-linux-port/" which you can find by going to the Terminal section of Qt Creator (Bottom bar #5) and typing the `pwd` command to get the path. Make sure it is the correct path as it should look similar to the example "/home/<username>/DNDC-Guelph-linux-port/". FYI the terminal window in Qt Creator is equivalent to the WSL command line. Then line 46 should look like this: snprintf(ssROOTDIR, sizeof(ssROOTDIR), "/home/<username>/DNDC-Guelph-linux-port/");
    * line 156: Change `char BatchFileName[400] = "Batch_list.txt";` to `char BatchFileName[400] = "/home/<username>/DNDC-Guelph-linux-port/Batch_list.txt";` where in the changed one write in the path to Batch_list.txt which you can also find with `pwd` command. 
    * 
    * Save your changes with Ctrl+S 
* Navigate to Search Results bar at the bottom, which should be the second one. In the window that pops up, do the following:
        *Change your scope to "Project DNDC"
        *Search for "\\". do not type the quotations marks in the actual search
        *Click the "Search and Replace" button
        *In the new highlighted window that pops up, type "/" in the "Replace with" field. Do not type the quotation marks in the field
        *You can see under the window where all instances of "\\" are found with checkmarks before them. 
        *Optionally: Remove the checkmark for "/home/<username>/DNDC-Guelph-linux-port/CreateInputFiles.cpp" 
        *Click the Replace button. The window should close.
        *Save your changes with Ctrl+S
        *Exit the program by pressing the "x" button at the top right
        *Return to the WSL command line interface
-->
# 3. Download and Configure Missing Files & Folders

This section prepares the Example files, updates file paths, and adds required library folder.

---

## 3.1 Copy the Example Folder into WSL

### Copy the Example zip file

```bash
cp '/mnt/c/Users/.../Example.zip' /home/<username>/DNDC-Guelph-linux-port
```

**Explanation:**

- `cp` copies files from Windows into WSL  
- Windows paths (`C:\...`) become `/mnt/c/...` in WSL  
- Replace all `\` with `/`  
- Adjust the Linux destination path as needed

### Verify the file was copied

```bash
ls /home/<username>/DNDC-Guelph-linux-port
```

You should see `Example.zip`.

---

## 3.2 Extract the Example Folder

```bash
unzip Example.zip
```

This creates a folder named `Example`.

Move into it:

```bash
cd Example
```

If `Batch_list.txt` has the wrong name, rename it:

```bash
mv previous_name.txt Batch_list.txt
```

---

## 3.3 Edit Batch_list.txt

Open the file in vim:

```bash
vim Batch_list.txt
```

- Press **I** to enter INSERT mode  
- Edit the file  
- Press **ESC**, then:
  - `:wq` to save and quit  
  - `:q` to quit without saving

---

## 3.4 Update Paths to .dnd Files

### Enter the `dnd` folder

```bash
cd dnd
```

List the files:

```bash
ls
```

Get the full path using `pwd`:

```bash
pwd
```

Copy the output (Ctrl+C).

### Return to the Example folder

```bash
cd ..
```

Reopen `Batch_list.txt`:

```bash
vim Batch_list.txt
```

Replace each Windows-style path, for example:

```
C:\dndc\Example\dnd\2014_nd_amenia_1.dnd
```

with a Linux-style path:

```
/home/<username>/DNDC-Guelph-linux-port/Example/dnd/2014_nd_amenia_1.dnd
```

Save and quit.

---

## 3.5 Update Climate File Paths

### Enter the climate folder

```bash
cd climate
```

Record the filenames and copy the folder path:

```bash
pwd
```

Return to Example:

```bash
cd ..
```

Enter the dnd folder:

```bash
cd dnd
```

Open each `.dnd` file:

```bash
vim filename.dnd
```

Inside each file:

- Locate the climate file paths  
- Replace Windows paths with Linux paths using the `pwd` result and correct filenames  
- Save and quit

Repeat for all `.dnd` files.

---

## 3.6 Add the Library Folder

Copy the Library folder (contains `Lib_crop`, `Lib_livestock`, `Lib_soil`) from Windows to Linux:

```bash
cp -r '/mnt/c/Users/.../Library/' /home/<username>/DNDC-Guelph-linux-port/
```

Verify the folder exists:

```bash
ls /home/<username>/DNDC-Guelph-linux-port
```

---

# 4. Edit Program Code

This section updates hardcoded paths inside the DNDC source code.

---

## 4.1 Launch Qt Creator

Open Qt Creator:

```bash
qtcreator
```

---

## 4.2 Open the DNDC Project

- Click **Open Project**
- Navigate to `DNDC-Guelph-linux-port`
- Select `CMakeLists.txt`
- Click **Open**

---

## 4.3 Edit `main.cpp`

Navigate to:

```
DNDC → dndc → Source Files → main.cpp
```

### Update Line 46

Change:

```cpp
"./"
```

to your DNDC directory path, for example:

```cpp
snprintf(ssROOTDIR, sizeof(ssROOTDIR), "/home/<username>/DNDC-Guelph-linux-port/");
```

Use the Qt Creator terminal to run `pwd` and confirm the correct path.

### Update Line 156

Change:

```cpp
char BatchFileName[400] = "Batch_list.txt";
```

to:

```cpp
char BatchFileName[400] = "/home/<username>/DNDC-Guelph-linux-port/Batch_list.txt";
```

Save with **Ctrl+S**.

---

## 4.4 Replace Windows Backslashes in the Project

- Open the **Search Results** panel (bottom bar usually second option)
- Set **Scope** to *Project DNDC*
- Search for:

```
\\
```

- Click **Search and Replace**
- Replace with:

```
/
```

- Optionally uncheck:

```
/home/<username>/DNDC-Guelph-linux-port/CreateInputFiles.cpp
```

- Click **Replace**
- Save with **Ctrl+S**
- Close Qt Creator with top right "x" button

---

## 4.5 Return to WSL

You can now continue with the next steps in the DNDC workflow.

## 5. Run the Project

You can run DNDC in two ways:

***

## Option A: Using Qt Creator 

### Steps

1.  Launch Qt Creator:

```bash
qtcreator
```

2.  In the Qt Creator interface:
    *   Click **Open Project**
    *   Navigate to `DNDC-Guelph-linux-port`
    *   Select `CMakeLists.txt`
    *   Click **Open**

3.  Build and run:
    *   Qt Creator configures the project automatically
    *   Make sure it is in Debug Mode. Check Bottom Left Computer Icon button has Debug written under it (Not release or other modes)
    *   Click the **Run** button (green triangle)

***

## Option B: Using the Command Line (Preferred Method)

### Build and run

```bash
cd DNDC-Guelph-linux-port
```

*   Move into the project folder

```bash
mkdir build
```

*   Create a separate build directory

```bash
cd build
```

*   Enter the build directory

```bash
cmake ..
```

*   Generate build files from the parent directory

```bash
cmake --build .
```

*   Compile the project

```bash
ls
```

*   Verify that the executable was created

```bash
./dndc
```

*   Run the program
*   `./` tells Linux to execute a file in the current directory

***

<!-- 6. Check Results
*If the program ran with no errors then a BatchSummary.csv file would have been generated. 
*Move to the file with `cd filepath` where the filepath will be the path part of the output in the terminal "Merged results: /home/<username>...".
*once in the directory, open the file with `vim BatchSummary.csv` or you can also see the file content in the command line with `cat BatchSummary.csv`. The file should have content. If it is empty then you have an error. You have likely skipped a previous step. Go through Step 3 and 4 again. 
-Done
-->
# 6. Check Results

This section verifies that DNDC produced output correctly.

---

## 6.1 Confirm That Output Was Generated

If the program completed without errors, it will generate a file named:

```
BatchSummary.csv
```

This file contains the merged results of the batch run.

---

## 6.2 Navigate to the Output Directory

When DNDC finishes, the terminal prints a line similar to:

```
Merged results: /home/<username>/DNDC-Guelph-linux-port/Example/Results
```

Move to that directory:

```bash
cd /home/<username>/DNDC-Guelph-linux-port/Example/Results
```

If you are unsure of the exact path, you can always run `pwd` to confirm your current location.

---

## 6.3 Inspect the Output File

You can open the file in vim:

```bash
vim BatchSummary.csv
```

Or view it directly in the terminal using `cat`:

```bash
cat BatchSummary.csv
```

**What you should see:**

- The file should contain data  
- If the file is **empty**, DNDC did not run correctly

---

## 6.4 If the File Is Empty

An empty `BatchSummary.csv` indicates that a previous configuration step was missed.

Most commonly, the issue is:

- Incorrect file paths in `Batch_list.txt`
- Incorrect climate file paths inside `.dnd` files
- Incorrect root directory paths in `main.cpp`

**Solution:**  
Repeat **Step 3** (file configuration) and **Step 4** (code edits), ensuring all paths match your WSL environment.

---

