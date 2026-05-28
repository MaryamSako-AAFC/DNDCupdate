#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "dndc_main.h"
//#include "region.h"
#include "direct.h"

//dailyrecord drd;

float Crop_ha[100]={0.0, 0.0};

void dndc74::dndc_region(MODEL_LINK_INFO* pLinkInfo, CGraphexDoc *pDoc, int Monitor)
{
	int FarmFile, RegionCode, CountryCode, StateCode, SC[150], SelectedCrops, RegionDataFormat, i;
	int StartGridID, TotalCells, SimulatedCells,SoilDataUse,DroughtID;
	char CountryName[120], ScenarioName[120], DatabaseName[240], r_Root1[240], r_Root2[240];
	float CO2_increase, FertRate, IrriRate;
	
	if (pDoc->DNDC_or_Other == 1) return;
	pDoc->ClearAct();
	//pDoc->StopRun = -1;		
	pDoc->DNDC_or_Other = 1; 
	
	
	databaseType = DBType;

	CString DIR0;
	DIR0.Format("%s", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s", OUTPUT);
	mkdir(DIR0);

	CString DIR1;
	DIR1.Format("%s\\Inputs", DIR0);
	mkdir(DIR1);

	CString DIR2;
	DIR2.Format("%s\\Inter", DIR0);
	mkdir(DIR2);

	DIR2.Format("%s\\Inter\\Management_1", DIR0);
	mkdir(DIR2);

	DIR2.Format("%s\\Inter\\Region", DIR0);
	mkdir(DIR2);

	CString DIR3;
	DIR3.Format("%s\\Record", DIR0);
	mkdir(DIR3);

	DIR3.Format("%s\\Record\\Region", DIR0);
	mkdir(DIR3);

	FILE *gion; 	
	int ifdaily;
	CString Fregion;
	
	Fregion.Format("%s\\region_input", INTER);
	gion = fopen(Fregion, "r");	
	if ( gion == NULL )
    {
		CString mess;
		mess.Format("Can not open %s.",Fregion);
		AfxMessageBox(mess);
		exit(0);
    }
	fscanf(gion, "%d %d %d", &RegionCode, &CountryCode, &StateCode);
	fscanf(gion, "%s", CountryName);
	fscanf(gion, "%s %s", r_Root1, r_Root2);
	fscanf(gion, "%s", DatabaseName);
	fscanf(gion, "%s", ScenarioName);

	fscanf(gion, "%d", &DBType);
	fscanf(gion, "%f %f %f", &BaseCO2, &AirTempRate, &RainRate);
	fscanf(gion, "%d", &major_target);
	fscanf(gion, "%d", &ifdaily);//&DailyItem
	fscanf(gion, "%d", &SimuYears);
	fscanf(gion, "%d", &StartYear);
	fscanf(gion, "%d", &c_ViewMode); 
	fscanf(gion, "%d", &FarmFile);
	fscanf(gion, "%d", &RegionDataFormat);//0-Shangrila; 1-Globe; 2-USA; 3-China
	fscanf(gion, "%d", &StartGridID);
	fscanf(gion, "%d", &TotalCells);
	fscanf(gion, "%d", &SimulatedCells);
	fscanf(gion, "%d", &SoilDataUse);
	fscanf(gion, "%d", &DroughtID);

	fclose(gion);

	CString DIR4;
	DIR4.Format("%s\\Record\\Region\\%s", DIR0, CountryName);
	mkdir(DIR4);

	/*if(StateCode!=0)
{
	CString DIR5;
	DIR5.Format("%s\\%s", DIR4, r_Province);
	mkdir(DIR5);
	
	CString DIR6;
	DIR6.Format("%s\\%s", DIR5, ScenarioName);
	mkdir(DIR6);
}
else*/
{
	CString DIR5;
	DIR5.Format("%s\\%s", DIR4, ScenarioName);
	mkdir(DIR5);
}

	DIR0.Format("%s\\Record\\Site", OUTPUT);
	mkdir(DIR0);
	//DIR0.Format("%s\\Record\\RegionSummary", OUTPUT);
	//mkdir(DIR0);
	//DIR0.Format("%s\\Record\\SiteSummary", OUTPUT);
	//mkdir(DIR0);
	DIR0.Format("%s\\Record\\MonteCarlo", OUTPUT);
	mkdir(DIR0);

/*	FILE* GGG;
	Fregion.Format("%s\\CropModel", INTER);
	GGG = fopen(Fregion, "w");
	if(GGG==NULL)
	{
		CString note;
		note.Format("Can xreate open file %s", Fregion);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(GGG, "%d", 0);
	fclose(GGG);
*/
	//if(c_ViewMode==0&&StateCode==0) MAP->map_state(pDoc, DatabaseName, databaseType, RegionCode, CountryCode, StateCode); 

	Shangrila(pLinkInfo, pDoc, RegionDataFormat, Monitor);//USA(pDoc, &drd);
}

void dndc74::PaintGrid(char *grid_ID, CGraphexDoc *pDoc, int SelectID)
{
	int j;
	CString County_ID[4000];
	int mm, pairs=0;
	float Da, Db;
	float center_x[2200], center_y[2200];
	int Xa = 122.0;
	int Xb = 3500;
	int Xc = -600;
	int Ya = 37.0;
	int Yb = Xb;		
	int Yc = -230;
	

	//read_coor();

	//Graphics
	POSITION canves = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( canves );
	CClientDC art(pDC);

	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);

	art.SetBkMode(TRANSPARENT);
	
	art.SetViewportOrg (0,0); 
	art.SetViewportExt(1500, 3000);

	CPoint map_data[50000];
	CString junk;

	CString StateName;
	FILE *Fcounty;
		
	StateName.Format("%s\\Database\\Elkhorn\\Lib_map\\Elkhorn_landuse_boundary.txt", ROOTDIR);
	Fcounty = fopen(StateName, "r");
	if(Fcounty==NULL)
	{
		CString note;
		note.Format("Can not open file %s", StateName);
		AfxMessageBox(note);
		exit(0); 
	}

	for(j=1; j<=1000; j++)
	{
		if(fscanf(Fcounty, "%s", County_ID[j])!=1)
		{			
			break;
		}
		else
		{
			fscanf(Fcounty, "%f  %f", &center_x[j], &center_y[j]);

			pairs = 0;

			for(mm=0;mm<50000;mm++)
			{		
				if(fscanf(Fcounty, "%f", &Da) != 1) 
				{
					fscanf(Fcounty, "%s", junk);
					break; 
				}
				else
				{
					fscanf(Fcounty, "%f", &Db); 
					pairs++;
					map_data[mm].x  = (int)((Xa + Da) * Xb) + Xc;
					map_data[mm].y = (int)((Ya - Db) * Yb) + Yc;			
				}
			}

			CPen *pOldPen = NULL;				//create a point for pen
			CPen Pen1(PS_SOLID, 1, RGB(0,0,0));
			pOldPen = art.SelectObject(&Pen1);	//select the pen into pen point
				
			if(County_ID[j]==grid_ID)
			{
				int c1, c2, c3;
			 switch  (SelectID)
			 {
			  case 0: //cropland
				 c1=239;
				 c2=138;
				 c3=63;
				 break;
			  case 1: //urban
				 c1=180;
				 c2=188;
				 c3=142;
				 break;
			  case 2: //natural vege
				 c1=119;
				 c2=136;
				 c3=39;
				 break;
			  case 3: //wetland
				 c1=130;
				 c2=174;
				 c3=227;
				 break;
			  case 4: //water
				 c1=54;
				 c2=89;
				 c3=167;
				 break;
			  case 5: //bared land
				 c1=215;
				 c2=222;
				 c3=0;
				 break;
			  case 6:  //livestock
				 c1=179;
				 c2=235;
				 c3=173;
				 break;
			  case 10: //selected grid
				 c1=255;
				 c2=255;
				 c3=0;
			  }

				
				CBrush *pOldBrush = NULL;			//create a point for brush
				CBrush Brush2(RGB(c1,c2,c3));
				pOldBrush = art.SelectObject(&Brush2);  //select the brush into brush point
				
				art.Polygon(map_data, pairs);				//draw poligon with the pen and brush

				art.SelectObject(pOldBrush);		//return original brush into brush point	
				Brush2.DeleteObject();

				CString note;
				note.Format("%d", pairs);
				//AfxMessageBox(note);
				break;
			}

			art.SelectObject(pOldPen);			//return original pen into oen point
			Pen1.DeleteObject();				//delete object
			
		}
	}


	fclose(Fcounty);

}
