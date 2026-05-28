// DNDCgo.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "DNDCgo.h"
#include "Source_main.h"
#include "RunPaths.h"
#include <direct.h>
#include <iostream>

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CDNDCgoApp

BEGIN_MESSAGE_MAP(CDNDCgoApp, CWinApp)
	//{{AFX_MSG_MAP(CDNDCgoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDNDCgoApp construction

CDNDCgoApp::CDNDCgoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDNDCgoApp object

CDNDCgoApp theApp;


// added by liujm
#ifdef DEGUI
int Model_linux(  int scale, char* cropping_system, int S_SoilYear, int S_ThisYear, 
						int S_SimuYears, char* DatabaseName, char* r_Province, char* ScenarioName, 
						float ha, int ProvinceOrder, int S_county, int CountyIDX, int landuse,
						int StartYear, int ifdaily, int MonteCarlo, int ZXH, int Batch, 
						int GlobeData, char* DirRoot, int sample, int RRRRR, int IrriType, 
						char* country_ID, int livestock, int Monitor, int DroughtID, 
						char f_region[6][150], char* DroughtYield, int FFN, char* BatchName)
#else
int WINAPI Model_link(MODEL_LINK_INFO* pLinkInfo,
					    int scale, char* cropping_system, int S_SoilYear, int S_ThisYear, 
						int S_SimuYears, char* DatabaseName, char* r_Province, char* ScenarioName, 
						float ha, int ProvinceOrder, int S_county, int CountyIDX, int landuse,
						int StartYear, int ifdaily, int MonteCarlo, int ZXH, int Batch, 
						int GlobeData, char* DirRoot, int sample, int RRRRR, int IrriType, 
						char* country_ID, int livestock, int Monitor, int DroughtID, 
						char f_region[6][150], char* DroughtYield, int FFN, char *BatchPass)
#endif
{
	
	int ThisYear, DroughtCycle=1, drc=1;
	int FarmField=-99;

#ifdef DEGUI

#else
	pLinkInfo->StopRun = -1;		
	pLinkInfo->DNDC_or_Other = 1;
#endif

	if(DroughtID==1) 
	{
		DroughtCycle=9;
		S_SimuYears=2;
	}
	else DroughtCycle=1;
	
	if(livestock>=1&&scale == 1)//Livestock run
	{
		scale = 1;
		ThisYear=1;

		class_model *DNDC; 

		if(!(DNDC = new class_model() )) 
				AfxMessageBox("No enough memory to run modelClass()");
		else
		{
			DNDC->year = ThisYear;

			int FSF=0;
			char SYF[200];
			FILE* sni;
			sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
			sni=fopen(SYF, "r");
			if(sni==NULL) note(0, SYF);
			fscanf(sni, "%d", &FSF);
			fclose(sni);
	
			if(FSF==3||FSF==4)
			{
				//was trying to turn this part off for DEGUI to compile
				
				DNDC->DNDC101go(pLinkInfo, scale, S_SoilYear, ha, cropping_system, ProvinceOrder, 
					S_county, CountyIDX, landuse, MonteCarlo, scale, ThisYear, 
					r_Province, ZXH, Batch, sample, RRRRR, IrriType, country_ID, livestock, 
					Monitor, drc, DroughtID, f_region, DroughtYield, FFN, FarmField); 
					
			}
			else
			{			
			/*	DNDC->DNDC100go(pLinkInfo, scale, S_SoilYear, ha, cropping_system, ProvinceOrder, 
						S_county, CountyIDX, landuse, MonteCarlo, scale, ThisYear, 
						r_Province, ZXH, Batch, sample, RRRRR, IrriType, country_ID, livestock, 
						Monitor, drc, DroughtID, f_region, DroughtYield, FFN, FarmField); */
			}

			delete DNDC; 
		}	
					
		//if (pLinkInfo->StopRun==1) break;

	}
	else// cropland run
	{	
	  for(drc=1; drc<=DroughtCycle; drc++)
	  {
		if(scale==0 || (scale==1&&ha>0.0))
		{
#ifdef MANURE
			char WZX[200];
			FILE *wzx;
			int TotalFarmFields, TotalFarmYears;
			float TotalFarmLandArea;
			sprintf(WZX, "%s\\ManureFieldCrops", INTER);
			wzx=fopen(WZX, "r");
			if(wzx==NULL) note(0, WZX);
			fscanf(wzx, "%d %d", &TotalFarmFields, &TotalFarmYears);//&TotalFarmLandArea, 
			fclose(wzx);

			for(FarmField=1; FarmField<=TotalFarmFields; FarmField++)
			{
				S_SimuYears = TotalFarmYears;

#endif
			for(ThisYear=1; ThisYear<=S_SimuYears; ThisYear++)
			{
				if(DroughtID==1)
				{
					if(drc==1) {}
					else if(drc==2||drc==3) 
					{
						if(ThisYear==1) goto DroughtScape;
					}
					else
					{
						if(IrriType==1||ThisYear==1) goto DroughtScape;
					}
				}

				class_model *DNDC; 

				if(!(DNDC = new class_model() )) 
					AfxMessageBox("No enough memory to run modelClass()");
				else
				{
					DNDC->year = ThisYear;
#ifdef DEGUI
					DNDC->DNDClinuxgo(scale, S_SoilYear, ha, cropping_system, ProvinceOrder, 
							S_county, CountyIDX, landuse, MonteCarlo, scale, ThisYear, 
							r_Province, ZXH, Batch, sample, RRRRR, IrriType, country_ID, livestock,
							Monitor, drc, DroughtID, f_region, DroughtYield, FFN, BatchName, FarmField);
#else
					DNDC->DNDC100go(pLinkInfo, scale, S_SoilYear, ha, cropping_system, ProvinceOrder, 
							S_county, CountyIDX, landuse, MonteCarlo, scale, ThisYear, 
							r_Province, ZXH, Batch, sample, RRRRR, IrriType, country_ID, livestock,
							Monitor, drc, DroughtID, f_region, DroughtYield, FFN, FarmField, BatchPass); 
#endif					
					delete DNDC; 

					
					
					
					

				}	
					
				//if (pLinkInfo->StopRun==1) break;
DroughtScape:;
			}//end of years loop
#ifdef MANURE
			}//end of FarmField loop
#endif
		}//end of scale
	  }//end of grought test loop
	}

	//pLinkInfo->DNDC_or_Other = 0;

	return(1);//return(1);
}

void  WINAPI Cell_end(int S_SimuYears, int ii_ha, char* DatabaseName, char* ScenarioName,
					int cell_ID1, int crop_number, char* r_Province, int IrriType, int SoilDataUse)
{
	
	class_model *DNDC;

	if(!(DNDC = new class_model() )) 
			AfxMessageBox("No enough memory to run modelClass()");
	else
	{
		//DNDC->Daily_record2(S_SimuYears, ii_ha, DatabaseName, ScenarioName,  cell_ID1, crop_number, r_Province, IrriType, SoilDataUse);
#ifdef HYDRO//===Record month result;dengjia===	
		//DNDC->Month_record(S_SimuYears, ii_ha, DatabaseName, ScenarioName, cell_ID1, crop_number, r_Province, IrriType);
#endif
	}
	delete DNDC;
	
}