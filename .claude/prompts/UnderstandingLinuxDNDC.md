<!-- RECOMMENDED: READ ALONGSIDE CODE\
main.cpp starts with including header files and defining globals from SitePara.h header file\
function create_result_dirs() makes directories for where all the results will go.\
function ## setup_paths() sets up paths like ROOTDIR, LIBRARY, OUTPUT, INTER, INPUTS, and INTERMANAGE\
the main function starts with creating a variable containing path of the txt file that has paths of dnd files.\
Then a pointer for dndc_jobs is initialized (currently empty).\
Since it is empty, dndc_jobs is false so the if statement is skipped.\
since max_jobs variable is less than 1 (as it is currently == 0), then all the if statements are performed.
* slurm_cpus initialized (still empty).\
* slurm_ntasks initialized (still empty).\
    *max_jobs finally assigned a value by _SC_NPROCESSORS_ONLN which assigns it to the number of CPUs available.\
for loop started that iterates from 1 to number of command line arguments.\
    *if command line argument contain a -j flag and the command line argument is at least 2 positions behind last command line argument then assign max_jobs to the value of the next command line argument. So basically assign max_jobs to whatever follows the j flag. And if max_jobs is less than 1, then assign 1 to it.\
    *else assign the command line arguments to BatchFileName variable.\
create region variable (FILE type) for BatchFileName.\
    *if region is empty then it prints an error message saying it cannot find file and ends the program by returning 1.\
fscanf then assigns the number of files from BatchFileName to variable FileNumber as usually the batch file has the number of files written on the first line.\
Then dynamic allocation is used (due to size flexibility and variability) as batch files can be large to create a DndFileName char array for the number of files.\
Then a for statement goes through every DndFileName path and if it is empty then nothing (so if it is == to '/') but if it is not empty (!= '/') then assigns new variable abs (=="absolute path") to orig_cwd + DndFileName and the realpath function is used to construct the path properly and if the constructed path (on variable resolved) is not empty then assign to DndFileName and if empty then assign abs to DndFileName. \
Next is processing the dnd jobs:\
    1. If only one job at a time: (max_job == 1 OR File_Number == 1)\
        Then setup_paths() function called. Explained in line 4\
        Then create_result_dirs() function called. Explained in line 3\
        Then a for loop goes through each job with the run_single_job function.\
        run_single_job function: Input is dnd file (the element in the DndFileName array reached) and job_id (usually the iteration)\
                                 Create variables like BatchName, site_file, site, years, MonteCarlo, sample, Monitor, DroughtID, livestock, FfFf (char array), with almost all either initialized to empty (NULL) or 0.\
                                Then CreateDndcInputFiles function called with dnd_file as the input. Skipping this function for now due to its length.\
                                Then site_file is assigned the directory to it leading with the OUTPUT file path created with create_result_dirs function.\
                                The site_file is attempted to open\
                                    *if can't open then error printed and program ended\
                                    *Otherwise fp file (the site_file) has the site and years written from it to the variables. Then the file is closed.\
                                    *Then a variable, CaseDir, is made and "./Result/Record/Batch/Case # and site" path string assigned to it.\
                                    *Then a directory is made for it. Then BatchName is assigned with CaseDir values.\
                                    *Then Model_linux function is called (go through this function later).\
                                    *Then run_single_job function is exited.\
                                    *Then DndFileName is freed and program is done.\
    2. If parallel mode\ 
        If max_jobs (# of CPUs) is more than the File_Number (# of dnd files) then max_jobs is made equal to File_Number.\
        Create some directories again (Why?) + a new work directory.\
        Create active and a failures integer type variables.\
        Create a children variable (pid_t type so process identifier type) and allocate space to it using calloc (so initialize to 0 and then allocate space).\
        Children variable has File_Number elements in count.\
        Then a for loop is started that iterates through File_Number count (so 1 to File_Number).\
            A work directory is created using orig_cwd and iteration number.\
            Then fork is used to run multiple processes.\
                If the pid is invalid then an error is printed and failures incremented. The program still continues, just skipping to the next iteration of the for loop.\
                In child process, workdir is checked to be empty. If not then error is printed with perror and child process is exited.\
                    Then symlink_shared_resources function is called.\
                        symlink_shared resources function: function takes parent directory for input and open that directory within the function with DIR *d assignment.\
                                                           If the directory doesn't open, then the function exits early.\
                                                           While directory is not empty, read it (go through every file/subdirectory).\
                                                            Skips hidden files and directories including current and parent directory (., .., .filename.filetype)\
                                                            Skips directory if d_name = "Result"\
                                                            Skips directory if d_name = "work"\
                                                            Two variables for paths then created: src (source) and dst (destination)\
                                                            Source is assigned the parent_dir + d_name (of d)\
                                                            Destination is assigned as such "./d_name" (where d_name is that of d)\
                                                            Now a "struct stat st;" is created and a stat struct basically holds information about a file or directory like size, permissions, last modification time, etc. \
                                                            We use lstat to check if we got info from src then check if it is a Symbolic link or not. \
                                                                If it is a symbolic link, it recreated the symbolic link with symlink function.\
                                                                If it is not a symbolic link (it is a directory), then it creates a symbolic link with the symlink function with source as target and destination as path.\
                                                                Then directory is closed.\
                                                                End of symlink_shared_resources function.\
                    Then setup_paths function and create_result_dirs are called.\
                    Then run_single_job function is called on DndFileName\[iteration] and job_id set to 1.\
                    exit child process with run_single_job returned value.\
                Next, we go to parent process.\
                    Children is assigned the parent pid for that iteration.\
                    Active is incremented and the process is printed with index/interation, pid, and DndFileName.\
                    Now on the next iteration this all repeats until we reach an iteration where active >= max_jobs. \
                    When that is reached then go through while loop.\
                        Create status variable (integer type).\
                        Then call wait_pid function and wait till process ends.\
                        If the process is done then decrement active.\
                        If exit status is not 0 then increment failures. \
                        Then go through the children (child processes) with a for loop and print which of them failed.\
                        Exit for loop.\
                        Then after we are done with this for loop and its while loop, there is another while loop that basically does the same thing as the while loop described.\
                        The only difference is this one decrements active down to 0.\
                        Exit loops.\
                Lastly, we reach the merge results section.\
                    A variable called merged_path is created and it is assigned orig_cwd + Result/Record/Batch/BatchSummary.csv.\
                    Then merge_batch_summaries function is called:\
                        Inputs are merged_path and File_Number.\
                        A file variable *out is created and assigned merged_path and is opened with write permission as well.\
                        If out is empty then error is printed and function is exited. Otherwise\
                            A new variable with boolean data type named header_written is created and set to false.\
                            A for loop that goes through the jobs is started.\
                                A variable named path is created and assigned "./work/iteration/Result/Record/Batch/BatchSummary.csv".\ 
                                Then a file variable named `in` is created and assigned to open the path variable content (so BatchSummary.csv) with read permission.\
                                If the file failed to open then skip this iteration of the for loop.\
                                Then a variable named line is created with a big size (8192 chars) and assigned whatever is in `in` (so whatever is in BatchSummary.csv) and it keeps doing that unitl there is nothing left to read.\
                                During that, fputs function writes `line` to `out` (which is the merged_path file). It skips any lines that start with '-', ' ', header_written set to false, or a character between 0 and 9 inclusive.\
                                Then the for loop closes `in` (which are the inidividual BatchSummary.csv's) and sets header_written to true.\
                                For loop ends.\
                            The function closes `out` (Merged BatchSummary.csv file).\
                            Function ends.\
                    Then main.cpp ends with printing results and completed status including failures and successes. It also frees pointers (children, and DndFileName) and returns based on if any failures exist.\
main.cpp ends.\
-->
<sub> markdown generated with the help of Copilot </sub>
***

# **Understanding Linux DNDC**

## **RECOMMENDED: READ ALONGSIDE CODE**

`main.cpp` starts with including header files and defining globals from `SitePara.h` header file

*   function `create_result_dirs()` makes directories for where all the results will go.
*   function `setup_paths()` sets up paths like `ROOTDIR`, `LIBRARY`, `OUTPUT`, `INTER`, `INPUTS`, and `INTERMANAGE`

***

## **Main Flow**

The main function starts with creating a variable containing path of the txt file that has paths of dnd files.

Then a pointer for `dndc_jobs` is initialized (currently empty).

Since it is empty, `dndc_jobs` is false so the if statement is skipped.

Since `max_jobs` variable is less than 1 (as it is currently == 0), then all the if statements are performed:

*   *`slurm_cpus` initialized (still empty)*
*   *`slurm_ntasks` initialized (still empty)*
*   *`max_jobs` finally assigned a value by `_SC_NPROCESSORS_ONLN` which assigns it to the number of CPUs available*

***

## **Command Line Parsing**

for loop started that iterates from 1 to number of command line arguments

*   *if command line argument contain a `-j` flag and the command line argument is at least 2 positions behind last command line argument then assign `max_jobs` to the value of the next command line argument. So basically assign `max_jobs` to whatever follows the j flag. And if `max_jobs` is less than 1, then assign 1 to it.*

*   *else assign the command line arguments to `BatchFileName` variable*

***

## **Batch File Handling**

create region variable (`FILE` type) for `BatchFileName`

*   *if `region` is empty then it prints an error message saying it cannot find file and ends the program by returning 1*

`fscanf` then reads the number of files from inside `BatchFileName` into variable `FileNumber` as usually the batch file has the number of files written on the first line

Then dynamic allocation is used (due to size flexibility and variability) as batch files can be large to create a `DndFileName` char array for the number of files

***

## **Path Processing**

Then a for statement goes through every `DndFileName` path

*   *if it is empty (i.e., string is actually empty, not equal to `/`) then nothing*
*   *but if it is not empty then assigns new variable `abs` (=="absolute path") to `orig_cwd + DndFileName` and the `realpath` function is used to construct the path properly and if the constructed path (on variable `resolved`) is not `NULL` then assign to `DndFileName` and if `NULL` then assign `abs` to `DndFileName`*

***

# **Processing the dnd jobs**

## **1. If only one job at a time**

*(`max_jobs == 1` OR `FileNumber == 1`)*

Then `setup_paths()` function called (explained earlier)  
Then `create_result_dirs()` function called

Then a for loop goes through each job with the `run_single_job` function

***

## **run\_single\_job function**

Input is dnd file (the element in the `DndFileName` array reached) and `job_id` (usually the iteration)

Create variables like:

*   `BatchName`, `site_file`, `site`, `years`, `MonteCarlo`, `sample`, `Monitor`, `DroughtID`, `livestock`, `FfFf`
*   with almost all either initialized to empty (`NULL`) or `0`

Then `CreateDndcInputFiles` function called with `dnd_file` as the input (skipping explanation)

Then `site_file` is assigned the directory to it leading with the OUTPUT file path created with `create_result_dirs` function

The `site_file` is attempted to open

*   *if can't open then error printed and program ended*
*   *otherwise `fp` file (the `site_file`) has the `site` and `years` read from it into the variables. Then the file is closed*

Then a variable `CaseDir` is made and `"./Result/Record/Batch/Case # and site"` path string assigned to it

Then a directory is made for it  
Then `BatchName` is assigned with `CaseDir` values

Then `Model_linux` function is called

Then `run_single_job` function is exited

*(Note: freeing of `DndFileName` happens after all jobs, not immediately here)*

***

## **2. If parallel mode**

If `max_jobs` (# of CPUs) is more than the `FileNumber` (# of dnd files) then `max_jobs` is made equal to `FileNumber`

Create some directories again (Why?) + a new `work` directory

Create `active` and `failures` integer type variables

Create a `children` variable (`pid_t` type so process identifier type) and allocate space to it using `calloc` (allocates memory and initializes it to 0)

`children` variable has `FileNumber` elements in count

***

## **Parallel Loop**

Then a for loop is started that iterates through `FileNumber` count (so 1 to `FileNumber`)

A work directory is created using `orig_cwd` and iteration number

Then `fork()` is used to create multiple processes (both parent and child continue execution)

*   If the pid is invalid then an error is printed and `failures` incremented. The program still continues, just skipping to the next iteration

***

## **Child process**

In child process (`pid == 0`):

*   `workdir` is checked
    *   if error then error is printed with `perror` and child process is exited

Then `symlink_shared_resources` function is called

***

## **symlink\_shared\_resources function**

function takes parent directory for input and open that directory within the function with `DIR *d` assignment

*   if the directory doesn't open, then the function exits early

While directory is not empty, read it (go through every file/subdirectory):

*   Skips hidden files and directories including current and parent directory (`.`, `..`, `.filename.filetype`)
*   Skips directory if `d_name = "Result"`
*   Skips directory if `d_name = "work"`

Two variables for paths then created:

*   `src` (source)

*   `dst` (destination)

*   Source = `parent_dir + d_name`

*   Destination = `"./d_name"`

Now a:

```c
struct stat st;
```

We use `lstat` to check if we got info from `src` then check if it is a symbolic link or not

*   If it is a symbolic link → recreate the symbolic link with `symlink`
*   If it is not a symbolic link (could be directory or file), then it creates a symbolic link with `src` as target and `dst` as path

Then directory is closed

End of `symlink_shared_resources` function

***

## **Back to child process**

Then:

*   `setup_paths()`
*   `create_result_dirs()`
*   `run_single_job(DndFileName[iteration], job_id = 1)`

Exit child process with `run_single_job` returned value

***

## **Parent process**

`children` is assigned the child pid for that iteration

`active` is incremented and the process is printed with index/iteration, pid, and `DndFileName`

***

## **Max jobs control**

Now on the next iteration this all repeats until we reach an iteration where  
`active >= max_jobs`

When that is reached then go through while loop:

*   Create `status` variable (integer type)

*   Call `waitpid()` function and wait till process ends

*   If process is done → decrement `active`

*   If exit status is not 0 → increment `failures`

Then go through the `children` (child processes) with a for loop and print which failed

***

## **Final wait loop**

After the main loop, there is another while loop

*   Basically same as above
*   Only difference: this one decrements `active` down to 0

***

# **Merge results section**

A variable called `merged_path` is created

*   assigned `orig_cwd + Result/Record/Batch/BatchSummary.csv`

Then `merge_batch_summaries` function is called

Inputs:

*   `merged_path`
*   `FileNumber`

***

## **merge\_batch\_summaries function**

*   Create file variable `*out`

*   Open `merged_path` with write permission

*   If `out` is empty → error + exit

Else:

*   Create boolean `header_written = false`

Loop through jobs:

*   Create variable `path`:
        ./work/iteration/Result/Record/Batch/BatchSummary.csv

*   Open file `in` (read mode)
    *   If file failed to open → skip iteration

*   Create `line` buffer (8192 chars)

*   Read lines from `in`

*   Use `fputs` to write to `out`

*   Skip lines based on conditions (e.g., filtering headers or unwanted lines; exact conditions depend on first character checks)

Then:

*   Close `in`
*   Set `header_written = true`

***

*   Close `out`

***

# **End of Program**

`main.cpp` ends with:

*   printing results and completed status including `failures` and successes
*   freeing pointers (`children`, and `DndFileName`)
*   returning based on if any failures exist

***

CreateInputFiles() Function:\
Input is dnd file(name)(s)\
create variables for crop_model_approach (jjd), string filename (SF), Manure Field file (MP), file type variables for former variables including sf and mp to handle writing files, DB and db for handling DB-related intermediate files, and DCB for Crop Rotation file paths.\
for loop (iterating from 1 to 10) writes initial Crop Rotation files\
     CropRotation file paths are read into DCB variables with INTERMANAGE file path + Crop Rotation iteration
     If file does not open with write permissions then an error is printed
     to the file, the iteration and 1 and 1 are written
     Then the file is closed
     