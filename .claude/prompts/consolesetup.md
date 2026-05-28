# Console Setup

Follow "DNDC_2026May_MS_Setup_Instructions.md" before this one.

Have Visual Studio open

In the Solution Explorer:

- Navigate to `dndc95` -> Header Files -> `dndc_main.h` line 18
- Navigate to `DNDCgo` -> Header Files -> `Source_main.h` line 13
- change line from: `//#define CONSOLE`
- to: `#define CONSOLE`

Then go to dndc95 project, right click on it and manoeuver to Properties

In property pages window navigate to **Configuration Properties -> Debugging**
and set **Command Arguments** to `-s C:\Path\to\Batchfile.txt`

> do not include quotations for the path as it gets included again through the code

Then set **working directory** to `C:\DNDC`

Results should be in `C:\DNDC\Result\Record\Batch\BatchSummary.csv`

---

**Troubleshooting:** 
- If the build fails, try building DNDCgo first then build dndc95
- If no results show up, make sure to check your Batchfilename.txt and the dnd files for proper paths.
