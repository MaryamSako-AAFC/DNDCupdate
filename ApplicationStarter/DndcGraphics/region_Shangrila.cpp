#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include "dndc_RegionFiles.h"
#include "direct.h"
#include <io.h>
#include "../DNDCgo.h"
#include "DNDCgoing.h"

int miss_clim=0;

void dndc74::Shangrila(MODEL_LINK_INFO* pLinkInfo, CGraphexDoc *pDoc, int GlobeData, int Monitor)
{
	CString Pname;
	int i, FarmFile, CropSystemNumber, CropNumber, S_RegionCode, S_CountryCode, S_StateCode, StartCell=1;
	int cell_ID1, cell_ID2, cell_ID3, ii_ha=0, CropID[60];
	char KK[500], CropSystemName[160][150], r_Root1[150], r_Root2[140], CropSystemID[160][150];
	char climfileID[150], CountryName[150], RegionName[120], ScenarioName[120], DatabaseName[120];
	char PlantHarvDates[160][150], TillDates[160][150], ManureRate[160][150];
	char ResidueData[160][150], FloodDates[160][150], CropName[160][150], FertDates[160][150];
	char country_ID[150];
	float S_BaseCO2;
	int S_ThisYear, S_ViewMode;
	float S_longitude, S_latitude, S_RainN, CropSystemArea[150];
	float Kmax_SOC[5], Kmin_SOC[5],Kmax_clay[5], Kmin_clay[5];
	float Kmax_pH[5], Kmin_pH[5], Kmax_BD[5], Kmin_BD[5];	
	float max_SOC, min_SOC,	max_clay, min_clay, max_pH, min_pH, max_BD, min_BD;
	int S_InterDrain, S_OnlyRice, S_NoTill, S_SoilType, S_IrriType, S_SimuYears;
	float ManureN, IrriRate, SCS[100], CropFertRate;
	int landtype, GDB, TotalCells, SimulatedCells, SoilDataUse;
	float CountyHa, SnowPack, FertNormalizationIndex;
	int ifdaily, landuse, ii, qq, jd, id, column, raw, continent_ID;
	int DroughtID, DryYear, MidYear, WetYear;
	float animal[10], slope, SoilQuality;
	float DMaxYield[100], DTDD[100], DWaterDemand[100];
	char CropPara[160][100];

	CString CropCode;
	FILE *f1, *f2, *f3, *f4, *CC;
	char File4[250];
	CString Fregion;
	FILE *region;

	Fregion.Format("%s\\region_input", INTER);
	region = fopen(Fregion, "r");
	if (region==NULL)
	{
		char err[120];
		sprintf(err, "Can not open file %s", Fregion);
		AfxMessageBox(err);
		exit(0); 
	}

	fscanf(region, "%d %d %d", &S_RegionCode, &S_CountryCode, &S_StateCode);
	fscanf(region, "%s", RegionName);
	fscanf(region, "%s %s", r_Root1, r_Root2);
	fscanf(region, "%s", DatabaseName);
	fscanf(region, "%s", ScenarioName);
	fscanf(region, "%d", &DBType);
	fscanf(region, "%f %f %f", &S_BaseCO2, &AirTempRate, &RainRate);
	fscanf(region, "%d", &major_target);
	fscanf(region, "%d", &ifdaily);
	fscanf(region, "%d", &S_SimuYears);
	fscanf(region, "%d", &StartYear);
	fscanf(region, "%d", &S_ViewMode); 
	fscanf(region, "%d", &FarmFile);
	fscanf(region, "%d", &GDB);
	fscanf(region, "%d", &StartCell);
	fscanf(region, "%d", &TotalCells);
	fscanf(region, "%d", &SimulatedCells);
	fscanf(region, "%d", &SoilDataUse);//0: FullIrr/NoIrri + SoilMax/min; 1: FullIrr/NoIrri + Soil ave; 2: NoIrri + Soil max/min; 3: NoIrri + Soil ave
	fscanf(region, "%d", &DroughtID);
	fclose(region);	
	
	if(DroughtID==1) SoilDataUse = 3;

	CString RP;
	char f_region[6][150]={"NULL","NULL"};
	FILE* FfFf;	

	RP.Format("%s\\RECORD\\REGION\\%s", OUTPUT, RegionName);
	//_mkdir(RP);
	RP.Format("%s\\RECORD\\REGION\\%s\\%s", OUTPUT, RegionName, ScenarioName);
	//_mkdir(RP);

	dndc74 *MAP; 
	if(!(MAP = new dndc74() )) 
	{
		AfxMessageBox("No enough memory to run dndc74()");
		exit(0);
	}

	CString MaMi[3]={"ave","max","min"};
	CString IrCode[2]={"ZeroIrri", "FullIrri"};

	///////////////////////////////////////////////////////Grid cell loop
	CWnd* pDC = pLinkInfo->pWnd;
	CDC& dc = *(pLinkInfo->pDC);
	//pDC->EnableWindow;
	if(Monitor==1) 
	{
		CRect rectClient;
		pDC->GetClientRect(rectClient);

		dc.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
		dc.SetWindowExt(1500, 3000);

		dc.SetMapMode(MM_ANISOTROPIC);
		dc.SetWindowExt(1500, 3000);	

		CBrush *pOldBrush = dc.GetCurrentBrush(); 
		CBrush brush0;								
		brush0.CreateSolidBrush(RGB(200,0,0));	
		pOldBrush = dc.SelectObject(&brush0);

		dc.SetViewportOrg (0, 0); //profile note
		dc.SetViewportExt(1500, 1500);
		//dc.FillSolidRect(100, 50, 850, 55, RGB(0,50,50)); //background
	}

	int RRRRR=0;

	for(ii=StartCell; ii<=TotalCells; ii++)
	{

		if(Monitor==1)
		{
			int GoFar = (int)(850.0*(float)ii/(float)TotalCells);
			dc.FillSolidRect(100, 250, 850, 21, RGB(230,220,180)); //background
			dc.FillSolidRect(100, 250, GoFar, 20, RGB(155,160,64));
		}

		int SSID1=1, SSID2=2, FFN=0;
		int YieldSite=0, YieldYear=0, YieldToday=0, YieldCrop=0, DroughtSite=0, YieldMonth, YieldDay;
		char CountyName[100];
		char DroughtYield[100];
		if(DroughtID==1) 
		{
			SSID1=0;
			SSID2=0;

			char YieldCropType[50];
			char YieldCropID[50];

			CString YF;
			FILE* yf;
			YF.Format("%s\\YieldPrediction", INTER);
			yf=fopen(YF, "r");
			if(yf==NULL) note(0,YF);
			fscanf(yf, "%d %d %d %d %s %d %d", &YieldSite, &YieldCrop, &YieldYear, &YieldToday, CountyName,&YieldMonth, &YieldDay);
			fscanf(yf, "%s %s", YieldCropType, YieldCropID);

			fclose(yf);

			if(ii==StartCell)
			{
				//CString YieldCropType[5]={"","corn","s_wheat", "rice","soybean"};				

				FILE *DYY;

				sprintf(DroughtYield, "%s\\%s_%s_yield_Year%d_Day%d.csv", RP, RegionName, YieldCropType, YieldYear, YieldToday);	
				DYY = fopen(DroughtYield, "w"); 
				if(DYY==NULL) note(1, DroughtYield);
				fprintf(DYY, "DNDC-predicted yields for %s in %s\n", YieldCropType, RegionName);					
				fprintf(DYY, "%-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s\n",
						"Grid_ID", "DryYr_yield", "MidYr_yield", "WetYr_yield", "NoRain_0days", "NoRain_5days", "NoRain_10days", "NoRain_20days", "NoRain_30days", "NoRain_50days", "DryYr_rain", "DryYr_WaterDeficit", "MidYr_rain", "MidYr_WaterDeficit", "WetYr_rain", "WetYr_WaterDeficit");
				fprintf(DYY, "%-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s\n",
						"Unit", "kg DM/ha", "kg DM/ha", "kg DM/ha", "kg DM/ha", "kg DM/ha", "kg DM/ha", "kg DM/ha", "kg DM/ha", "kg DM/ha", "mm", "mm", "mm", "mm", "mm", "mm");

				fclose(DYY);
			}
		}

		int IrriAA1, IrriAA2, SoilAA1, SoilAA2;

		if(SoilDataUse==0) 
		{
			IrriAA1=0;
			IrriAA2=1;
			SoilAA1=1;
			SoilAA2=2;
		}
		else if(SoilDataUse==1) 
		{
			IrriAA1=0;
			IrriAA2=1;
			SoilAA1=0;
			SoilAA2=0;
		}
		else if(SoilDataUse==2) 
		{
			IrriAA1=0;
			IrriAA2=0;
			SoilAA1=1;
			SoilAA2=2;
		}
		else if(SoilDataUse==3) 
		{
			IrriAA1=0;
			IrriAA2=0;
			SoilAA1=0;
			SoilAA2=0;
		}
		else
		{
			AfxMessageBox("Wrong irrigation-soil type combination");
			exit;
		}	

		if(DroughtID==1) IrriAA2=1;

		for(i=SoilAA1; i<=SoilAA2; i++)//1, 2
		{
			for(int yy=IrriAA1; yy<=IrriAA2; yy++)//0, 1
			{
				FFN++;

				sprintf(f_region[FFN], "%s\\%s_%s_%s_flux.csv", RP, RegionName, IrCode[yy], MaMi[i]);//MaMi[3]={"ave","max","min"};
				
				int RRR=ii-StartCell;
				
				if(RRR==0)
				{
					RRRRR = ii;
					//sprintf(f_region[FFN], "%s\\%s_%s_%s_flux.csv", RP, RegionName, IrCode[yy], MaMi[i]);	
					FfFf = fopen(f_region[FFN], "w"); 
					if(FfFf==NULL) note(1, f_region[FFN]);
								
					fprintf(FfFf, "%-8s , %-8s , %-11s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , ",
						"Grid_ID", "System_ID", "SystemName", "Area", "Year", 
						"Stub", "SOC0-10cm", "SOC10-20cm","SOC20-30cm","SOC30-40cm","SOC40-50cm", "Total-SOC", "ManureC", "LitterC", "Soil-CO2", "dSOC", 
						"CropID_1", "CropID_2", "CropID_3", "GrainC_1", "GrainC_2", "GrainC_3",	"ShootC_1", "ShootC_2", "ShootC_3",	"RootC_1", "RootC_2", "RootC_3", 						
						"CH4", "N2O", "NO", "N2", "NH3", "IndirectN2O", "IndirectN2", "CropN", "LeachN", "RunoffN", "DepositN", "FixedN", "Miner_N", 
						"FertilizerN", "ManureN", "LitterN", "dSON", "dSIN","H2Otran", "H2Oevap", "H2Orunof", "H2Oleach", 
						"H2Oirri", "H2Oprec", "dSoilH2O", "MeanT","CountryID","WaterStress","N_Stress","T_stress");

//dengjia
#ifdef MANURE
					fprintf(FfFf, "%-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , ",
						"LOS_CH4", "LOS_N2O", "LOS_NH3", "Manure_Runoff_IN", "Manure_Runoff_ON",
						"Manure_to_field_C", "Manure_to_field_N");
#endif
#ifdef HYDRO
					fprintf(FfFf, "%-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , ",
						"MUSLERUNOFF", "MUSLESEDYLD", "MUSLESOC", "MUSLESON", "MUSLENH4", 
						"MUSLENO3", "MUSLENH3", "MUSLEUREA", "MUSLECLAYN");
#endif 
					fprintf(FfFf, "\n");
					fprintf(FfFf, "%-8s , %-8s , %-8s , %-11s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , ",
						"Grid_ID", "System_ID", "SystemName", "ha", "Year", 
						"kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", 
						"CropID_1", "CropID_2", "CropID_3", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", 
						"kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", 
						"kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "mm", "mm", "mm", "mm", "mm", "mm", "mm", "DegreeC","CountryID","WaterStress","N_Stress","T_stress");
#ifdef MANURE
					fprintf(FfFf, "%-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , ",
						"kgC/LOS", "kgN/LOS", "kgN/LOS", "kgN/LOS", "kgN/LOS", "kgC/LOS", "kgN/LOS");
#endif
#ifdef HYDRO
					fprintf(FfFf, "%-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , %-8s , ",
						"mm", "ton", "kgC/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha","kgN/ha", "kgN/ha");
#endif
					fprintf(FfFf, "\n");
					fclose(FfFf);
				}
			}
		}
		//}
		//////////////////////////////////////////////////////////////////////////////

		sprintf(File4, "%s\\Inter\\RegionFiles\\%s\\%s_%d", OUTPUT, RegionName, RegionName, ii);//new files
		f4=fopen(File4, "r");
		if (f4==NULL) note(0, File4);

		fscanf(f4, "%d %s %s %f %f   %s %f %f    %f %f %f %f %f %f %f %f %d %d %d %f %f", 
					&cell_ID1, country_ID, CountryName, &S_longitude, &S_latitude, 
					climfileID, &S_RainN, &SnowPack, &Kmax_SOC[0], &Kmin_SOC[0], 
					&Kmax_clay[0], &Kmin_clay[0], &Kmax_pH[0],  &Kmin_pH[0], &Kmax_BD[0], 
					&Kmin_BD[0], &column, &raw, &continent_ID, &slope, &SoilQuality);
		if(DroughtID==1)
		{
			fscanf(f4, "%d %d %d", &DryYear, &MidYear, &WetYear);
		}

		fscanf(f4, "%d", &CropSystemNumber);
		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", CropSystemName[i]);	
		fscanf(f4, "%d", &jd);
		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", CropSystemID[i]);
		
		fscanf(f4, "%d", &CropNumber);
		for(i=1; i<=CropNumber; i++) 
			fscanf(f4, "%s", CropName[i]);	
		fscanf(f4, "%d", &jd);
		for(i=1; i<=CropNumber; i++) 
			fscanf(f4, "%d", &CropID[i]);

		
		CountyHa=0.0;
		for(i=1; i<=CropSystemNumber; i++) 
		{
			fscanf(f4, "%f", &CropSystemArea[i]);
			CountyHa += CropSystemArea[i];
		}

		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", PlantHarvDates[i]);

		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", ResidueData[i]);

		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", TillDates[i]);

		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", &FertDates[i]);

		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", ManureRate[i]);

		for(i=1; i<=CropSystemNumber; i++) 
			fscanf(f4, "%s", FloodDates[i]);

		for(i=1; i<=CropNumber; i++) 
		{
			fscanf(f4, "%s", CropPara[CropID[i]]);
			FindCropPara(CropPara[CropID[i]], DMaxYield, DTDD, DWaterDemand, CropID[i]);
		}

#ifdef MANURE
		int FarmNumber;
		char Live_ID[100][50], notee[100];
		int BarnType[100],BarnFloorType[100],BarnBedMaterial[100],BarnVentType[100];
		float BarnHeads[100],BarnFeedRate[100],BarnCP[100],BarnTP[100],BarnFloorArea[100],BarnBedRate[100],BarnBedCN[100],BarnBedFrequency[100],BarnRemoveFrequency[100];
		float BarnToCompost[100],BarnToLagoon[100],BarnToDigester[100];
		int PenType[100],PenFloorType[100],PenBedMaterial[100],PenVentType[100];
		float PenHeads[100],PenFeedRate[100],PenCP[100],PenTP[100],PenFloorArea[100],PenBedRate[100],PenBedCN[100],PenBedFrequency[100],PenRemoveFrequency[100];
		float PenToCompost[100],PenToLagoon[100],PenToDigester[100];
		float ComDensity[100],ComLitterRate[100],ComLitterCN[100],ComToField[100][10],ComDToMarket[100][10],ComRemain[100][10];
		float LagCapacity[100],LagArea[100],LagToField[100][30],LagToMarket[100][30],LagRemain[100][30];
		int LagCover[100],DigTemp[100], FlashType[100],LagDrainTimes[100],LagDrainMonth[100][30],LagDrainDay[100][30];
		float DigRetentionDays[100],DigToField[100],DigToMarket[100],DigToRemain[100],FieldArea[100], FlushWater[100];
		int ComCover[100], ComRemoveTimes[100], ComRemoveMonth[100][10], ComRemoveDay[100][10];
		
		fscanf(f4, "%d", &FarmNumber);

		/////////////////////////////////
		char FTF[200];
		FILE *ftf;
		sprintf(FTF, "%s\\Inter\\FarmNumber_%d", OUTPUT, cell_ID1);
		ftf=fopen(FTF, "w");
		if(ftf==NULL) note(1, FTF);
		fprintf(ftf, "%d %f\n", FarmNumber, CountyHa);
		fclose(ftf);
		/////////////////////////////////

		for(i=1;i<=FarmNumber;i++)
		{					
			fscanf(f4, "%s", Live_ID[i]);
			fscanf(f4, "%d %f %f %f %f %f ", &BarnType[i],&BarnHeads[i],&BarnFeedRate[i],&BarnCP[i],&BarnTP[i],&BarnFloorArea[i]);
			fscanf(f4, "%d %d %f %f %f %d ",&BarnFloorType[i],&BarnBedMaterial[i],&BarnBedRate[i],&BarnBedCN[i],&BarnBedFrequency[i],&BarnVentType[i]);
			fscanf(f4, "%f %f %f %f",&BarnRemoveFrequency[i],&BarnToCompost[i],&BarnToLagoon[i],&BarnToDigester[i]);
			fscanf(f4, "%d %f", &FlashType[i], &FlushWater[i]);
			
			fscanf(f4, "%d %f %f %f %f %f ",& PenType[i],&PenHeads[i],&PenFeedRate[i],&PenCP[i],&PenTP[i],&PenFloorArea[i]);
			fscanf(f4, "%d %d %f %f %f ",& PenFloorType[i],&PenBedMaterial[i],&PenBedRate[i],&PenBedCN[i],&PenBedFrequency[i]);
			fscanf(f4, "%f %f %f %f",&PenRemoveFrequency[i],&PenToCompost[i],&PenToLagoon[i],&PenToDigester[i]);

			fscanf(f4, "%f %d %d %f %f",&ComDensity[i],&ComCover[i],&ComRemoveTimes[i],&ComLitterRate[i],&ComLitterCN[i]);
		
			for(int w=1;w<=ComRemoveTimes[i];w++)
			{
				fscanf(f4, "%d %d %f %f %f", &ComRemoveMonth[i][w], &ComRemoveDay[i][w],&ComToField[i][w],&ComDToMarket[i][w],&ComRemain[i][w]);
			}

			fscanf(f4, "%f %f %d %d",&LagCapacity[i],&LagArea[i],&LagCover[i],&LagDrainTimes[i]);
		
		
			for(int j=1; j<=LagDrainTimes[i]; j++)
			{
				fscanf(f4, "%d %d %f %f %f",&LagDrainMonth[i][j],&LagDrainDay[i][j],&LagToField[i][j],&LagToMarket[i][j],&LagRemain[i][j]);
			}
			fscanf(f4, "%d %f %f %f %f %f",&DigTemp[i],&DigRetentionDays[i],&DigToField[i],&DigToMarket,&DigToRemain,&FieldArea[i]);
		}

		//fscanf(f4, "%f %f %f %f %f", &animal[1], &animal[2], &animal[3], &animal[4], &animal[5]);
#endif

#ifdef HYDRO //===dengjia===
		for(i=1; i<=18; i++) 
			fscanf(f4, "%f", &SCS[i]);

        char muslesite[120];
		FILE *fmuslesite;

   		char muslesoil[120];
		FILE *fmuslesoil;
			   
		sprintf(muslesite,"%s\\Inputs\\muslesite",OUTPUT);
		fmuslesite = fopen(muslesite, "w");
		if ( fmuslesite == NULL ) 
		{
			 AfxMessageBox("Can not create file muslesite");
			 exit(0);
		}

		sprintf(muslesoil,"%s\\Inputs\\muslesoil",OUTPUT);
        fmuslesoil = fopen(muslesoil, "w");
		if ( fmuslesoil == NULL ) 
		{
			  AfxMessageBox("Can not create file muslesoil");
			  exit(0);
		}		
        for(i=1; i<=10; i++)
             fprintf(fmuslesite, "%f\n", SCS[i]);

		for(i=11; i<=18; i++)
	         fprintf(fmuslesoil, "%f\n", SCS[i]);
	        
		     fclose(fmuslesite);
             fclose(fmuslesoil);
#endif
		

		fclose(f4);
	
		if(Kmin_SOC[0]<=0.0) Kmin_SOC[0] = Kmax_SOC[0] * 0.5;
		if(Kmin_clay[0]<=0.0) Kmin_clay[0] = Kmax_clay[0] * 0.5;
		if(Kmin_pH[0]<=0.0) Kmin_pH[0] = Kmax_pH[0] * 0.8;
		if(Kmin_BD[0]<=0.0) Kmin_BD[0] = Kmax_BD[0] * 0.8; 
		if(Kmax_SOC[0]<=0.0) Kmax_SOC[0]=0.002;
		if(Kmin_SOC[0]<=0.0) Kmin_SOC[0]=0.001;
		if(Kmax_clay[0]<=0.0) Kmax_clay[0]=0.02;
		if(Kmin_clay[0]<=0.0) Kmin_clay[0]=0.01;
		if(Kmax_pH[0]<=0.0) Kmax_pH[0]=7.0;
		if(Kmin_pH[0]<=0.0) Kmin_pH[0]=6.5;
		if(Kmax_BD[0]<=0.0) Kmax_BD[0]=1.5;
		if(Kmin_BD[0]<=0.0) Kmin_BD[0]=1.4;
		max_SOC=Kmax_SOC[0];
		min_SOC=Kmin_SOC[0];
		max_clay=Kmax_clay[0];
		min_clay=Kmin_clay[0]; 
		max_pH=Kmax_pH[0];
		min_pH=Kmin_pH[0];
		max_BD=Kmax_BD[0]; 
		min_BD=Kmin_BD[0];
		if(max_SOC>0.4) max_SOC=0.4;
		if(max_clay>0.8) max_clay=0.8;
		float mmm;
		if(min_SOC>max_SOC)
		{
			mmm=min_SOC;
			min_SOC=max_SOC;
			max_SOC=mmm;
		}
		if(min_SOC<=0.0) min_SOC = 0.0001;
		if(min_clay>max_clay)
		{
			mmm=min_clay;
			min_clay=max_clay;
			max_clay=mmm;
		}
		if(min_clay<=0.0) min_SOC = 0.001;
		if(min_pH>max_pH)
		{
			mmm=min_pH;
			min_pH=max_pH;
			max_pH=mmm;
		}
		if(min_pH<=0.0||max_pH<=0.0)
		{
			CString note;
			note.Format("Error for soil pH");
			AfxMessageBox(note);
			exit(0);
		}
		if(min_BD>max_BD)
		{
			mmm=min_BD;
			min_BD=max_BD;
			max_BD=mmm;
		}
		if(min_BD<=0.0||max_BD<=0.0)
		{
			CString note;
			note.Format("Error for soil bulk density");
			AfxMessageBox(note);
			exit(0);
		}
		
		
		if(CountyHa>0.0)
		{
			if(DroughtID==1)
			{
				if(YieldSite==10000)//Whole China
				{
					DroughtSite = cell_ID1;
				}
				else
				{
					DroughtSite = YieldSite;
				}

				if(DroughtSite!=cell_ID1&&DroughtSite!=0) 
					goto DroughtSkip;
			}

			ii_ha++;

			region_site_files(CountryName, S_longitude, S_latitude, RegionName, CountryName);//+

			miss_clim = region_climate_files(climfileID, S_latitude, S_RainN, S_BaseCO2, cell_ID1, 0.0, GlobeData, 0, 
				StartYear, DroughtID, DryYear, MidYear, WetYear);//+
if(miss_clim==1) 
	goto ClimateMissSkip;

#ifdef MANURE
			int LOS;
			float Llat;
			landuse = 1;
			S_SoilType = 1;
			S_IrriType = 1;
			
			if(S_latitude>=0.0) Llat = S_latitude;
			else Llat = -S_latitude;
			region_soil_files(1, max_SOC, min_SOC, max_clay, min_clay, max_pH, min_pH, 
							max_BD, min_BD, 1, 0, "1", 0.0, CountryName, GlobeData, Llat, SnowPack, 0, 0.0, 0.0);//+
		
			//?????????????????????????
			region_farm_files(CropSystemID[landuse], CountryName, 1, S_InterDrain, 0, S_RegionCode, 
						country_ID, S_StateCode, "WWW", CountryName, CountryName, ManureN,
						PlantHarvDates[landuse], FertDates[landuse], animal, CountyHa, ManureRate[landuse],
						S_latitude, TillDates[landuse], ResidueData[landuse], FloodDates[landuse], 
						CropPara[1], DroughtID, CropID, CropNumber, DMaxYield, DTDD, DWaterDemand);//+
				
			for(LOS=1;LOS<=FarmNumber;LOS++)
			{
				char LIVEID[100];
				sprintf(LIVEID, "%s", Live_ID[LOS]);
				region_livestock_files(LOS, LIVEID, BarnType, BarnFloorType,
					BarnBedMaterial, BarnVentType, BarnHeads, BarnFeedRate,
					BarnCP,BarnFloorArea,BarnBedRate,BarnBedCN,
					BarnBedFrequency,BarnRemoveFrequency, BarnToCompost,
					BarnToLagoon, BarnToDigester,	PenType, PenFloorType,
					PenBedMaterial, PenVentType,PenHeads, PenFeedRate, 
					PenCP, PenFloorArea, PenBedRate, PenBedCN, 
					PenBedFrequency, PenRemoveFrequency, PenToCompost, 
					PenToLagoon, PenToDigester, ComDensity, ComCover, ComRemoveTimes, 
					ComLitterRate, ComLitterCN, ComToField, ComDToMarket, 
					ComRemain, LagCapacity, LagArea, LagDrainTimes, 
					LagToField, LagToMarket, LagRemain, LagCover, DigTemp,
					DigRetentionDays, DigToField, DigToMarket, FieldArea, BarnTP, PenTP,
					FlashType, LagDrainMonth, LagDrainDay, DigToRemain, ComRemoveMonth, 
					ComRemoveDay, FlushWater);
			
#ifdef DEGUI
#else
				char BatchPass[300]="NULL";
				Model_link(pLinkInfo, 1, CropSystemID[landuse], 
								S_SoilType, S_ThisYear, S_SimuYears, RegionName, "", ScenarioName, 
								CropSystemArea[landuse], 0, ii, cell_ID1, landuse, StartYear,
								ifdaily, 0, 0, 0, GlobeData, r_Root1, 0, RRRRR, S_IrriType, country_ID,
								LOS, Monitor, DroughtID, f_region, DroughtYield, 1, BatchPass);	
#endif
			}


#endif
			for(landuse=1; landuse<=CropSystemNumber; landuse++)
			{

				if(DroughtID==0)
				{
				}
				else if(YieldCrop==landuse)
				{
				}
				else
				{
					goto YieldCropSkip;
				}

				if(CropSystemArea[landuse]>0.0)
				{
					if(strcmp(CropSystemID[landuse], "11")==0)
						landtype = 3;//grassland
					else 
						landtype = 1;//upland crops
					
					int SoilUse, IrriUse;
					float ave_SOC, ave_clay, ave_pH, ave_BD;
					if(SoilDataUse==0)
					{
						SoilUse=2;
						IrriUse=2;
					}
					else if(SoilDataUse==1)
					{
						SoilUse=1;
						IrriUse=2;
						ave_SOC=(max_SOC+min_SOC)*0.5;
						ave_clay=(max_clay+min_clay)*0.5;
						ave_pH=(max_pH+min_pH)*0.5;
						ave_BD=(max_BD+min_BD)*0.5;
						max_SOC=ave_SOC;
						min_SOC=ave_SOC;
						max_clay=ave_clay;
						min_clay=ave_clay;
						max_pH=ave_pH;
						min_pH=ave_pH;
						max_BD=ave_BD;
						min_BD=ave_BD;
					}
					else if(SoilDataUse==2)
					{
						SoilUse=2;
						IrriUse=1;
					}
					else 
					{
						SoilUse=1;
						IrriUse=1;
						ave_SOC=(max_SOC+min_SOC)*0.5;
						ave_clay=(max_clay+min_clay)*0.5;
						ave_pH=(max_pH+min_pH)*0.5;
						ave_BD=(max_BD+min_BD)*0.5;
						max_SOC=ave_SOC;
						min_SOC=ave_SOC;
						max_clay=ave_clay;
						min_clay=ave_clay;
						max_pH=ave_pH;
						min_pH=ave_pH;
						max_BD=ave_BD;
						min_BD=ave_BD;
					}

					CString XFF;
					FILE *xff;
					XFF.Format("%s\\ManureCropNumber", INTER);		
					xff=fopen(XFF, "w");
					if(xff==NULL) note(1,XFF);
					fprintf(xff, "%d  %d  %d\n", CropSystemNumber, landuse, CropSystemID[landuse]);
					fclose(xff);

					for(int soil_yr=1; soil_yr<=SoilUse; soil_yr++)
					{
						float Llat;
						if(S_latitude>=0.0) Llat = S_latitude;
						else Llat = -S_latitude;
						region_soil_files(soil_yr, max_SOC, min_SOC, max_clay, min_clay, max_pH, min_pH, 
							max_BD, min_BD, landtype, 0, "1", 0.0, CountryName, GlobeData, Llat, SnowPack, 
							0, slope, SoilQuality);//+
					}

					region_farm_files(CropSystemID[landuse], CountryName, 1, S_InterDrain, 0, S_RegionCode, 
						country_ID, S_StateCode, "WWW", RegionName, CountryName, ManureN,
						PlantHarvDates[landuse], FertDates[landuse], animal, CountyHa, ManureRate[landuse],
						S_latitude, TillDates[landuse], ResidueData[landuse], FloodDates[landuse],
						CropPara[1], DroughtID, CropID, CropNumber, DMaxYield, DTDD, DWaterDemand);//+
					
					int FFFNN=0;
					for(S_SoilType=SoilAA1; S_SoilType<=SoilAA2; S_SoilType++)
					{	
						for(S_IrriType=IrriAA1; S_IrriType<=IrriAA2; S_IrriType++)
						{
							FFFNN++;
#ifdef DEGUI
#else
							Model_link(pLinkInfo, 1, CropSystemID[landuse], 
								S_SoilType, S_ThisYear, S_SimuYears, RegionName, "", ScenarioName, 
								CropSystemArea[landuse], 0, ii, cell_ID1, landuse, StartYear,
								ifdaily, 0, 0, 0, GlobeData, r_Root1, 0, RRRRR, S_IrriType, country_ID,
								0, Monitor, DroughtID, f_region, DroughtYield, FFFNN, "NULL");	
#endif
						}
						if (pDoc->StopRun==1) break;
					}//end of soil year loop
					if (pDoc->StopRun==1) break;
				}//end of if(CropSystemArea[landuse]>0.0
				if (pDoc->StopRun==1) break;

YieldCropSkip:;

			}//end of landuse loop
			if (pDoc->StopRun==1) break;

			if(ifdaily==1) 
			Cell_end(S_SimuYears, ii_ha, RegionName, ScenarioName, cell_ID1, CropSystemNumber, RegionName, S_IrriType, SoilDataUse);
			//SoilDataUse//0: FullIrr/NoIrri + SoilMax/min; 1: FullIrr/NoIrri + Soil ave; 2: NoIrri + Soil max/min; 3: NoIrri + Soil ave

DroughtSkip:;

		}//end of if(CountyHa>0.0)
		if (pDoc->StopRun==1) break;

		//if(ifdaily==1) 
		//	County_end(S_SimuYears, ii, RegionName, ScenarioName, County_IDX, CropSystemNumber, r_Province);
ClimateMissSkip:;
	}//end of for(ii=1; ii<=SimulatedCells; ii++)												
	
	if (pDoc->StopRun==1)
		AfxMessageBox("The simulation is interrupted");
	else
		AfxMessageBox("The simulation is accomplished");

	if (pDoc->StopRun==0) return;
	pDoc->StopRun = 0;
	pDoc->DNDC_or_Other = 0;//Show DNDC end

}
