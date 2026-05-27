#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "Dndc_shell.h"
#include "CreateInputFile.h"
//#include "SiteParaGo.h"
#include "RunPaths.h"
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


#ifdef DEGUI

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char Pass[300];

// was trying to pass this the proper directory structure but this isn't a great solution.
//#define ROOTDIR "\\DNDC\\"


int WINAPI OpenSesame(void)
{
	//liz - needs to be fixed to match what was done in onbatch()
	// library
	sprintf(ssLIBRARY, "%s", root_lib.c_str());
	LIBRARY = ssLIBRARY;
	
	// Output nur den link herstellen
	sprintf(ssOUTPUT, "%s", "\\DNDC_Output\\");
	OUTPUT = ssOUTPUT;
	
	//create sub-directories
	CString DIR0;
	DIR0.Format("%s", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult\\Inputs", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult\\Inter", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult\\Inter\\Management_1", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult\\Inter\\RegionFiles", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult\\Record", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult\\Record\\Region", ROOTDIR);
	_mkdir(DIR0);
	DIR0.Format("%sResult\\Record\\Site", ROOTDIR);
	_mkdir(DIR0);
	
	DIR0.Format("%sResult\\Record\\MonteCarlo", ROOTDIR);
	_mkdir(DIR0);

	DIR0.Format("%sResult\\Record\\Batch", ROOTDIR);
	_mkdir(DIR0);

	///////////////////////////////////////////////////////////////////////
	//define path/name of batch file
	char BatchFileName[400], DndFileName[500][200], Site[160], junkc[160], FfFf[6][150]={"",""};
	char BatchName[300];
	int FileNumber, i, MonteCarlo = 0, sample=0, years=0, livestock=0, DroughtID=0;
	int option=0, Monitor=0;
	CString Fregion;
	FILE *region, *FileRun;
	
	sprintf(BatchFileName, "Batch_list.txt");
		
	Fregion.Format("%s", BatchFileName);
	region = fopen(Fregion, "r");
	if(region==NULL)
	{
		char err[120];
		sprintf(err, "Cannot find %s", Fregion);
		AfxMessageBox(err);
		exit(0); 
	}
	fscanf(region, "%d", &FileNumber);

	for(int ia=1; ia<=FileNumber; ia++) fscanf(region, "%s", DndFileName[ia]);
	fclose(region);

	for(int ib=1; ib<=FileNumber; ib++)
	{
		DIR0.Format("%sResult\\Record\\Batch\\Case%d", ROOTDIR, ib);
		_mkdir(DIR0);

		sprintf(BatchName, "%s", DIR0); 

		sprintf(Pass, "%s", BatchName);

		//years = ReadInputDatafromDND(DndFileName[i], 0);
		
		
		//ReadInputDatafromDND(DndFileName[ib], 0);

		//ReadSoilFeature("UnDefault");//reads props from library
		//int DayRecord = 1;
		//CreateInputFiles(0, 0, "r_Country", DayRecord);//Batch run

	 CreateDndcInputFiles(DndFileName[ib], "NULL");

		if(option>1000000) 
			option=0;
		else if(option>100)
		{
			MonteCarlo = 1;
			sample = option - 100;
		}

		if(Monitor>1000000) Monitor=0;			

#ifdef MANURE
	livestock = 1;
#else
	livestock = 0;
#endif

		int DroughtID=0;
		char FfFf[6][150]={"",""};

		if(option==10) DroughtID = 1;

		///////////////////////////
		char site_file[80], site[200];
		FILE *fp;

		sprintf(site_file, "%s\\Inputs\\SITE", OUTPUT);
		fp = fopen(site_file, "r");
		if (fp==NULL) note(0, site_file);		 
		fscanf(fp, "%s", site);
		fscanf(fp, "%d", &years);
		fclose( fp );
		//////////////////////



#ifdef DEGUI
		Model_linux(0, "0", 0, 0, years, "None", "None","None", 0.0, 0, 0, 0, 0, 0, 1, 
			MonteCarlo, 0, 1, 1, "None", sample, 0, 0, "0", livestock, Monitor, DroughtID, FfFf, "0", 4, BatchName);
#else
		Model_link(link, 0, "0", 0, 0, years, "None", "None","None", 0.0, 0, 0, 0, 0, 0, 1, 
			MonteCarlo, 0, option, 1, "None", sample, 0, 0, "0", livestock, Monitor, DroughtID, FfFf, "0", 4);
#endif		
		
	}//end of batch file loop

/*#ifdef DEGUI
	AfxMessageBox("The simulation is accomplished");
#else
	AfxMessageBox("The simulation is accomplished");
#endif*/
	return 0;
}
#endif

