#include "stdafx.h"
#include "dndc71.h"
#include "RunPaths.h"
#include "SitePara.h"
#include "dndc_main.h"
#include "dndc_RegionFiles.h"
#include "dndc_tool.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float Soil_Litter, Soil_humads, Soil_humus, PassiveC;
float socA[6]={0.0,0.2,0.2,0.08,0.05,0.2};
float socB[6]={10.0,2.0,2.0,1.4,4.0,2.0};
int MCflag, IC;
float MC_Soil_Litter, MC_Soil_humads, MC_Soil_humus,MC_NO3, MC_NH4, MC_WRL;
char notee[120];
/////////////////0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10 ,11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29
float RCYA1[30]={1.0,0.3,0.3,0.3,1.0,1.0,0.3,1.0,0.3,0.3,1.0,1.0,1.0,0.3,0.3,1.0,1.0,1.0,0.3,1.0,0.3,1.0,1.0,1.0,1.0,0.3,1.0,0.3,1.0,0.3};//Africa
float RCYA2[30]={1.0,0.5,0.5,0.6,1.0,1.0,0.5,1.0,0.5,0.4,1.0,1.0,1.0,0.4,0.8,1.0,1.0,1.0,0.4,1.0,0.8,1.0,1.0,1.0,1.0,0.5,1.0,0.9,1.0,0.4};//Asia
float RCYA3[30]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.7,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};//Europe
float RCYA4[30]={1.0,0.9,0.4,1.0,1.0,1.0,0.4,1.0,0.5,0.4,1.0,1.0,1.0,0.6,0.5,1.0,1.0,1.0,0.9,1.0,0.9,1.0,1.0,1.0,1.0,0.5,1.0,0.8,1.0,0.6};//NorthAmerica
float RCYA5[30]={1.0,0.5,0.3,0.7,1.0,1.0,0.3,1.0,0.3,0.3,1.0,1.0,1.0,0.6,1.0,1.0,1.0,1.0,0.6,1.0,1.0,1.0,1.0,1.0,1.0,0.4,1.0,0.9,1.0,0.4};//Oceania
float RCYA6[30]={1.0,0.5,0.5,1.0,1.0,1.0,0.5,1.0,0.4,0.3,1.0,1.0,1.0,0.5,0.7,1.0,1.0,1.0,0.5,1.0,0.6,1.0,1.0,1.0,1.0,0.5,1.0,0.8,1.0,0.3};//SouthAmerica
float RCYA7[30]={1.0,0.3,0.3,0.4,1.0,1.0,0.3,1.0,0.3,0.3,1.0,1.0,1.0,0.2,1.0,1.0,1.0,1.0,0.3,1.0,0.4,1.0,1.0,1.0,1.0,0.3,1.0,0.7,1.0,0.5};//Russia

void MakeDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, 
							float lat, int IfCheck, float NO3NH4_Rainfall,float NH3_Atmosphere,
							float BaseCO2, float CO2IncreaseRate, int YieldSite, int YieldYear, 
							int YieldToday, char *climfile_ID, int DMW, int DryYear, int MidYear, 
							int WetYear, char *r_Country);

void region_farm_files(char* cropping_system, char *CountryName, int province, int junk, 
							   int MonteCarlo, int RegionCode, char* country_ID, int StateCode, 
							   char *FarmFileName, char* region_name, char* county_name, 
							   float ManureN, char* PlantHarvDates,
							   char* FertDates, float* animal, float CountyHa, char* ManureRate,
							   float S_latitude, char* TillDates, char* ResidueData, 
							   char* FloodDate, char* CropPara, int DroughtID, int* CropID, int CropNumber,
							   float* DMaxYield, float* DTDD, float* DWaterDemand)
{

	int FarmFile;
	char Fsource[300], Ftarget[300], WW[300];	
	int till_number, till_month, till_day, till_date[10], till_method[10], i;	
	float till_depth[10];
	int fert_number, fert_month, fert_day, fert_date[10], cut_number, cut_part[10];	
	int manu_number, manu_month=0, manu_day=0, manu_date[10], cut_month, cut_day, cut_date[10], manu_method[10];	
	float manu_rate=0.0, manu_CN=15.0, cut_amount[10];		
	float irri_index;
	int flood_number, flood_month1, flood_day1, flood_date1[10], flood_month2, flood_day2, flood_date2[10];	
	int F_SimuYears, yr, CropFertDate[50];
	char Fcrop[120], InCrop[120], R_CropName[8][120], F_INI[80];
	FILE *cropff, *cropin, *fcropini;
	int R_CropCode[6]; 
	int R_LeftDays[6], R_GrowDays[6], CoverCrop[6]={0,0};
	float R_MaxBioC[6], R_GrainFra[6],  R_LeafFra[6], R_ShootFra[6], R_RootFra[6];
	float R_PlantCN[6], R_MaxYield[6], R_MaxPlantN[6], MaxBioC[6];
	
	int cropping_number, cropping_number2, crop_ID[5]={0,0};
	int plant_jday[5], harvest_jday[5], wwheat_flag, HarvYr[6], fert_jday[5][10];	

	int R_perennial[6];  //for Peter
	float R_graincn[6], R_rootcn[6], R_leafcn[6], R_strawcn[6], R_wreq[6], R_max_lai[6], R_cropht[6];
	float R_max_TDD[6], R_N_fix[6], R_vascularity[6], R_TreeAge[6];
	float R_PLEI[6], R_PLMX[6], R_DRCV[6], R_DRCR[6], R_FEPSO, R_SLC, R_SSC, R_FIEC, R_ZRTMC, R_GZRTZ;
	int EndFlag[6];
	char r_Country[200], DatabaseName[240], ScenarioName[240];
	float r_CO2, r_AirTemp, r_YieldIncrease;
	int c_ViewMode, DataType, WinterFlag[3]={0,0};
	int Manage, F_major_target, F_DailyItem, F_StartYear, F_ViewMode;
	float fert_rate[100];
	int fert_type[100];
	char r_Root1[240], r_Root2[240];
	float RY_AtmoCO2[100]={0.0,0.0}, RY_AirTemp[100]={0.0,0.0}, RY_RainTimes[100]={1.0,1.0}, RY_YieldIncrease[100]={0.0,0.0};	
	float RY_LitterBackField[100]={0.0,0.0}, RY_AnimalManure[100]={0.0,0.0}, RY_CropCN[100]={0.0,0.0};
	float RY_FertilizerRate[100]={0.0,0.0}, RY_IrriIndex[100]={1.0,1.0}, RY_WaterDemand[100]={0.0,0.0}, RY_MaxTemp[100]={0.0,0.0};
	int RY_Tillage[100]={0,0}, RY_Drainage[100]={0,0}, RY_ShallowWater[100]={0,0}, RY_FilmCover[100]={0,0};
	int RY_AutoFert[100]={0,0}, RY_FloodAlter[100]={0,0}, RY_TillAlter[100]={0,0}, RY_IrriAlter[100]={0,0};
	int RY_SlowReleaseDays[100]={0,0}, RY_RicePlantAlter[100]={0,0};
	float SlowReleaseFert[100]={0.0,0.0};
	float NitriInhibitEff[100]={0.0,0.0};
	float NitriInhibitDur[100]={0.0,0.0};
	float UreaInhibitEff[100]={0.0,0.0};
	float UreaInhibitDur[100]={0.0,0.0};
	float RY_NitrificationInhibit[100]={0.0,0.0};
	int RY_IniGridID[100]={0,0};
	int graze_number, graze_month1, graze_day1, graze_month2, graze_day2, graze_date1[10], graze_date2[10];
	float cattle[10], horse[10], sheep[10], graze_hrs[10];
	int RainfedFlag = 0, FloodFlag=0, FertRate[50]={0,0}, CropFertType[50]={0,0}, TotalFertApplications;
	int GlobeData=0, StartGridID, TotalCells, SimulatedCells, CountryCode, WinterCrop=0, WCN=0;
	float ManureCCC[100], ManureNNN[100], ManureCNCN[100];
	int TillDate[20], TillDepth[20], TotalTillApplications, CropFertTYPES[50], jd;
	float CFertRate[50][5]={0.0,0.0}, jf;

	//Determine region ID
/*	int RegionID;
	if(strcmp(region_name, "Africa")==0) RegionID = 1;
	else if(strcmp(region_name, "Asia")==0) RegionID = 2;
	else if(strcmp(region_name, "Europe")==0) RegionID = 3;
	else if(strcmp(region_name, "NorthAmerica")==0) RegionID = 4;
	else if(strcmp(region_name, "Oceania")==0) RegionID = 5;
	else if(strcmp(region_name, "SouthAmerica")==0) RegionID = 6;
	else if(strcmp(region_name, "China")==0) RegionID = 2;
	else if(strcmp(region_name, "India")==0) RegionID = 2;
	else if(strcmp(region_name, "UnitedStates")==0) RegionID = 4;
	else 
	{
		RegionID = 3;
	}
*/

	FindCrops(cropping_system, crop_ID, &cropping_number);

	if(MonteCarlo==0)
	{
		char Fregion[120];
		FILE *region;
		sprintf(Fregion, "%s\\region_input", INTER);
		region = fopen(Fregion, "r");

		fscanf(region, "%d %d %d", &RegionCode, &CountryCode, &StateCode);
		fscanf(region, "%s", r_Country);
		fscanf(region, "%s %s", r_Root1, r_Root2);
		fscanf(region, "%s", DatabaseName);
		fscanf(region, "%s", ScenarioName);
		fscanf(region, "%d", &DataType);
		fscanf(region, "%f %f %f", &r_CO2, &r_AirTemp, &r_YieldIncrease);
		fscanf(region, "%d", &F_major_target);
		fscanf(region, "%d", &F_DailyItem);
		fscanf(region, "%d", &F_SimuYears);
		fscanf(region, "%d", &F_StartYear);
		fscanf(region, "%d", &F_ViewMode); 
		fscanf(region, "%d", &FarmFile);
		fscanf(region, "%d", &GlobeData);
		fscanf(region, "%d", &StartGridID);
		fscanf(region, "%d", &TotalCells);
		fscanf(region, "%d", &SimulatedCells);
		fclose(region);

		if(FarmFile==1)
		{
			for(int yy=1; yy<=F_SimuYears; yy++)
			{
				sprintf(Fregion, "%s\\region_yr%d", INTER, yy);
				region = fopen(Fregion, "r");	
				
				fscanf(region, "%f %f %f", &RY_AtmoCO2[yy], &RY_AirTemp[yy], &RY_RainTimes[yy]);
				fscanf(region, "%f %f %f", &RY_LitterBackField[yy], &RY_FertilizerRate[yy], &RY_AnimalManure[yy]);
				fscanf(region, "%d %d %d", &RY_AutoFert[yy], &RY_FloodAlter[yy], &RY_TillAlter[yy]);	
				fscanf(region, "%f %f %f", &RY_YieldIncrease[yy], &RY_WaterDemand[yy], &RY_MaxTemp[yy]);
				fscanf(region, "%f %f %f %f %f", &RY_CropCN[yy], &RY_IrriIndex[yy], &jf, &jf, &jf);
				fscanf(region, "%d %d %d %d %d", &RY_IrriAlter[yy], &RY_RicePlantAlter[yy], &jd, &jd, &jd);
				
				fclose(region);						
			}
		}
		
		if(FarmFile==0) Manage = 0;
		else Manage = 1;
	}
	else//MonteCarlo==1
	{
		sprintf(r_Country, "%s", CountryName);
		sprintf(DatabaseName, "%s", CountryName);		
		FarmFile = 0;
		c_ViewMode = 1;
		F_SimuYears = 1;		
		Manage = 0;

		RY_AtmoCO2[1]=350.0;
		RY_AirTemp[1]=0.0;
		RY_YieldIncrease[1]=1.0;
		RY_LitterBackField[1]=1.0;
		RY_AnimalManure[1]=1.0;
		RY_FertilizerRate[1]=1.0;
		RY_IrriIndex[1]=1.0;
		//RY_Tillage[1]=0;
		RY_TillAlter[1]=1;
		RY_FloodAlter[1]=1;
		RY_Drainage[1]=0;	
		RY_ShallowWater[1]=0;
		RY_FilmCover[1]=0;
		RY_AutoFert[1]=1;
		RY_SlowReleaseDays[1]=0;
		RY_RainTimes[1]=1.0;
		RY_NitrificationInhibit[1]=0.0;
		RY_CropCN[1]=1.0;
		RY_IrriAlter[1]=1;
		RY_RicePlantAlter[1]=0;
		//sprintf(farming, "%s", FarmFileName);
	}
	
	wwheat_flag = 0;

	//Define farming management dates/rates
	int TotalManureApplications=0, CManureDate[50]={0,0}, TotalResidueApplications=0;
	int FloodIni[20]={0,0}, FloodEnd[20]={0,0}, FloodMethod[20]={0,0}, TotalFloodApplications=0;	
	float CManureN[50]={0.0,0.0}, CManureCN[50]={0.0,0.0}, ResidueRate[10]={0.0,0.0};
	//int CropFertDate[50]={0,0}, CropFertType[50]={0,0};
	float CropFertRate[50]={0.0,0.0};

	DefinePHDates(PlantHarvDates, plant_jday, harvest_jday, &cropping_number, &WinterCrop, &WCN); 
	
	DefineTillDates(TillDates, TillDate, TillDepth, &TotalTillApplications);

	DefineManureDates(ManureRate, &TotalManureApplications, CManureDate, CManureN, CManureCN);

	DefineResidueDates(ResidueData, &TotalResidueApplications, ResidueRate);

	DefineFloodDates(FloodDate, FloodIni, FloodEnd, FloodMethod, &TotalFloodApplications);

	DefineFertDates(FertDates, CropFertDate, CropFertType, CropFertRate, &TotalFertApplications);//, CropFertTYPES, crop_ID, cropping_number);

	IC=1;
	if(WinterCrop==1) IC=0;
	for(int n=IC; n<=cropping_number; n++)
	{
		if(n==0)
		{
			crop_ID[n] = crop_ID[WCN];
			harvest_jday[n] = harvest_jday[WCN];
			plant_jday[n] = plant_jday[WCN];
			ResidueRate[n]=ResidueRate[WCN];
		}

		//ResidueRate[n] = RY_LitterBackField[1];
		//if(ResidueRate[n]>1.0) ResidueRate[n]=1.0;

		if(crop_ID[n]==46)//rainfed rice
		{
			RainfedFlag=1;
			//crop_ID[n]=20;
		}
		
		if(crop_ID[n]==20)//paddy rice
		{
			FloodFlag=1;
		}

		if(crop_ID[n]==7)
		{
			ResidueRate[n]=0.0;
		}

		R_GrowDays[n] = harvest_jday[n] - plant_jday[n];

		if(plant_jday[n] >= harvest_jday[n]) 
		{
			HarvYr[n] = 2; 
			WinterFlag[n] = 1;
			wwheat_flag = 1;
			R_GrowDays[n] = 365 - plant_jday[n] + harvest_jday[n] + (HarvYr[n] - 2) * 365;
			R_LeftDays[n] = R_GrowDays[n] - (365 - plant_jday[n]);
			//ResidueRate[0]=ResidueRate[n+1];
		}
	}
	
	//if(Manage==1) fclose(Ffarming);

	//write file cropini
    sprintf(F_INI, "%s\\Inputs\\cropini_1", OUTPUT);    
    fcropini = fopen(F_INI, "w");
    if ( fcropini == NULL ) 
	{
		CString err;
		err.Format("cannot create %s", F_INI);
		AfxMessageBox(err);
		exit(0);
	}

	if(wwheat_flag == 1)
	{
		/*fprintf(fcropini, "1 78 16.10 15.7 0.16\n");
		fprintf(fcropini, "92.17 27.72 4.95 47.71 416.2\n");
		fprintf(fcropini, "0.45 49.23 157.57 1233.67 400.35 833.32 20.81 0.38\n");
		fprintf(fcropini, "1405.38 2053.77 0.00 -0.35 -0.18 -0.16\n");
		fprintf(fcropini, "7.78 2.61 4.44 0.24 12.22\n");
		fprintf(fcropini, "6.15 0.00 0.00 6.15\n");
		fprintf(fcropini, "12.39 2.49 0.96 0.24\n");
		fprintf(fcropini, "0.00 0.00 10.16 0.00 0.00 0.00 4.91 3.32\n");
		fprintf(fcropini, "1.00 0.72 0.14 4.92 2.0 0.00 0.00 0.00\n");
		fprintf(fcropini, "-0.45 0.033 0.36 0.19 0.00 0.00 1.00\n");
		fprintf(fcropini, "0.41 0.43 0.43 0.48 15.53 0.000045 0.90 0.006\n");
		fprintf(fcropini, "0.0\n");*/

		fprintf(fcropini, "1 78 98.782234 141.296143 3.370028\n");
		fprintf(fcropini, "396.762939 791.093994 272.596741 60.061760 928.299866\n");
		fprintf(fcropini, "0.3 260.431610 1222.437012 10054.463867 5001.835449 5052.628906 593.914429 0.456428\n");
		fprintf(fcropini, "388.150146 425.000000 45.241417 16.600092 54.701843 0.000000\n");
		fprintf(fcropini, "134.906097 59.428238 0.000000 57.709061 134.906097\n");
		fprintf(fcropini, "6.000000 0.000000 0.000000 6.000000\n");
		fprintf(fcropini, "41.017162 51.416466 1.178264 0.0\n");
		

	}
	else
	{
		fprintf(fcropini, "0 0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0\n");
		fprintf(fcropini, "0.0\n");

	}
	fclose(fcropini);


	//write file crop-yr
	for(yr=1; yr<=F_SimuYears; yr++)
	{
	
		{
			for(int n=IC; n<=cropping_number; n++)
			{	
				//int ChangeCropFlag=0;//, DCID=crop_ID[n];

				if(crop_ID[n]==46)//rainfed rice 
				{
					//crop_ID[n]=20;
					RainfedFlag=1;
					//ChangeCropFlag=1;
				}

				
				{
					EndFlag[n]=111;

					if(n==cropping_number) EndFlag[n] = 999;

					///////////////////////////////////////////////////////////////////////////////////////////
					int v_CropID[95], v_Perennial[95];
					float v_max_biomass_C[95], v_grain_fraction[95], v_leaf_fraction[95], v_leafstem_fraction[95], v_root_fraction[95];
					float v_GrainCN[95], v_LeafCN[95], v_ShootCN[95], v_RootCN[95], v_TreeAge[95];
					float v_WaterDemand[95], v_OptimumT[95], v_TDD[95], v_Nfixation[95], v_Vascularity[95];
					float v_Root1[95], v_Root2[95],v_AGResp1[95],v_AGResp2[95];//new Root respiration code.
					float v_Kext1[95], v_Kext2[95],v_CMaxH[95];
					float v_cropGRate[95], v_cropTime[95], v_RUEHI[95], v_DelayP[95];
					//CString v_CropName[95];
					char v_CropName[95][100]={"NONE","NONE"};

					ReadCropPara1(v_CropID, v_CropName, v_max_biomass_C, v_grain_fraction, v_leaf_fraction,
					  v_leafstem_fraction, v_root_fraction, v_GrainCN, 
					  v_LeafCN, v_ShootCN, v_RootCN, v_WaterDemand, v_OptimumT, 
					  v_TDD, v_Nfixation, v_Vascularity, v_Perennial, v_TreeAge,v_Root1,v_Root2,v_AGResp1,v_AGResp2,v_Kext1,v_Kext2,v_CMaxH,v_cropGRate,v_cropTime,v_RUEHI,v_DelayP);

					////////////////////////////////////////////////////////////////////////////////////////
					int CropType;
					if(crop_ID[n]==20&&RY_FloodAlter[n]==4)//turn paddy rice to upland rice
						CropType = 24;
					else						
						CropType = crop_ID[n];
						
					sprintf(R_CropName[n], "%s", v_CropName[CropType]);
									
					R_GrainFra[n] = v_grain_fraction[CropType];
					R_LeafFra[n] = v_leaf_fraction[CropType];
					R_ShootFra[n] = v_leafstem_fraction[CropType];
					R_RootFra[n] = v_root_fraction[CropType];					
					R_PlantCN[n] = 1.0 / (v_grain_fraction[CropType]/v_GrainCN[CropType] + 
						v_leaf_fraction[CropType]/v_LeafCN[CropType] + 
						v_leafstem_fraction[CropType]/v_ShootCN[CropType] + 
						v_root_fraction[CropType]/v_RootCN[CropType]);
					R_graincn[n] = v_GrainCN[CropType];
					R_rootcn[n] = v_RootCN[CropType];
					R_leafcn[n] = v_LeafCN[CropType];	
					R_strawcn[n] = v_ShootCN[CropType];											
					R_max_lai[n] = v_OptimumT[CropType];
					R_cropht[n] = 1.0;														
					R_N_fix[n] = v_Nfixation[CropType];
					R_vascularity[n] = v_Vascularity[CropType];//aerokima
					R_perennial[n] = v_Perennial[CropType];	
					R_TreeAge[n] = v_TreeAge[CropType];	

					R_MaxBioC[n] = DMaxYield[CropType] / R_GrainFra[n];//kg C/ha	
					R_max_TDD[n] = DTDD[CropType];	
					R_wreq[n] = DWaterDemand[CropType]; //g H2O for producing 1 g dry matter
										
					/*if(abs(S_latitude)>40.0) 
						R_max_TDD[n] *= (40.0/abs(S_latitude));
					else if(abs(S_latitude)>35.0)
						R_max_TDD[n] *= (-0.0646*abs(S_latitude) + 3.2263);
					else {}*/

					//R_max_TDD[n] = -65.151 * abs(S_latitude) + 4199.7;

					/*if(ChangeCropFlag==0)
					{
						R_MaxBioC[n] = DMaxYield[crop_ID[n]] / R_GrainFra[n];//????????????????
						R_max_TDD[n] = DTDD[crop_ID[n]];
						R_wreq[n] = DWaterDemand[crop_ID[n]];
					}*/

					//Regional crop yield adjustment
					/*if(RegionID==1) R_MaxBioC[n] *= RCYA1[crop_ID[n]];
					else if(RegionID==2) R_MaxBioC[n] *= RCYA2[crop_ID[n]];
					else if(RegionID==3) 
					{
						if(strcmp("Russia", CountryName)==0) R_MaxBioC[n] *= RCYA7[crop_ID[n]];
						else R_MaxBioC[n] *= RCYA3[crop_ID[n]];
					}
					else if(RegionID==4) R_MaxBioC[n] *= RCYA4[crop_ID[n]];
					else if(RegionID==5) R_MaxBioC[n] *= RCYA5[crop_ID[n]];
					else if(RegionID==6) R_MaxBioC[n] *= RCYA6[crop_ID[n]];
					else {};*/


					//if(R_GrainFra==0.0&&R_ShootFra==0.0)
					if(crop_ID[n]==0)
					{
						MaxBioC[n] = 0.0;
						R_MaxYield[n] = 0.0;
						R_MaxPlantN[n] = 0.0;
					}
					else
					{
						if(RY_YieldIncrease[yr]!=1.0) MaxBioC[n] = R_MaxBioC[n] * RY_YieldIncrease[yr];
						else MaxBioC[n] = R_MaxBioC[n];
						//MaxBioC = R_MaxYield[n] / R_GrainFra;//kg C of total plant/ha	
						R_MaxYield[n] = MaxBioC[n] * R_GrainFra[n]; //grain yield[n]; kg C/ha
						
						R_MaxPlantN[n] = CropTN(MaxBioC[n], R_graincn[n], R_leafcn[n], R_strawcn[n], R_rootcn[n], R_GrainFra[n], 
							R_LeafFra[n], R_ShootFra[n], R_RootFra[n]);
						if(R_MaxPlantN[n]<0.0) R_MaxPlantN[n] = 0.0;
						
						//R_MaxPlantN[n] = MaxBioC[n] / R_PlantCN[n];
					}

					if(WinterFlag[n] == 1) HarvYr[n] = 2;
					else HarvYr[n] = 1;
				
				}
			}
				
			sprintf(Fcrop, "%s\\Inputs\\crop-%d", OUTPUT, yr);
			cropff = fopen(Fcrop, "w");
			if ( cropff == NULL ) note(1, Fcrop);
			
			if(WinterCrop==1) fprintf(cropff, "%d\n", cropping_number+1);
			else fprintf(cropff, "%d\n", cropping_number);

			for(int n=IC; n<=cropping_number; n++)
			{
				float ResiRate;
				if(FarmFile==1) ResiRate = ResidueRate[n] * RY_LitterBackField[yr]; 
				else ResiRate = ResidueRate[n];
				if(ResiRate>1.0) ResiRate=1.0;

				//if(WinterFlag[n] == 1)
				if(n==0)
				{
					fprintf(cropff, "%d %s %d %d %f %d\n", crop_ID[n], R_CropName[n], WinterFlag[n], R_LeftDays[n], R_MaxYield[n], HarvYr[n]);
					fprintf(cropff, "%d %d %f %f %d\n", 0, R_GrowDays[n], ResiRate, R_MaxPlantN[n], 111);
					//fprintf(cropff, "%f %f %f %f %f\n", 12.5, R_DRCV[n], R_DRCR[n], R_PLEI[n], R_PLMX[n]);
					fprintf(cropff, "%f %d %f %f %f\n", 12.5, 0, 0.0, 0.0, 0.0);
					fprintf(cropff, "%d\n", CoverCrop[n]);
					fprintf(cropff, "%d\n", 0);
					fprintf(cropff, "%f %f %f %f\n", R_GrainFra[n], R_LeafFra[n], R_ShootFra[n], R_RootFra[n]);
					fprintf(cropff, "%f %f %f %f\n", R_graincn[n], R_leafcn[n], R_strawcn[n], R_rootcn[n]);
					fprintf(cropff, "%f %f %f %f %f\n", R_max_TDD[n], R_wreq[n], R_max_lai[n], R_N_fix[n], R_vascularity[n]);
					fprintf(cropff, "%f %f %f %f\n\n", 0.0, 0.0, 0.0, 0.0);//tree parameters
					
				}
			}

				for(int n=1; n<=cropping_number; n++)
				{
					if(n==cropping_number) EndFlag[n] = 999;
					else EndFlag[n] = 111;

					float ResiRate;
					if(FarmFile==1) ResiRate = ResidueRate[n] * RY_LitterBackField[yr]; 
					else ResiRate = ResidueRate[n];
					if(ResiRate>1.0) ResiRate=1.0;

											
					if(crop_ID[n]==7) 
					{
						ResiRate = 0.0;
						if(cropping_number==1) 
						{
							plant_jday[n] = 5;
							R_GrowDays[n] = 350;
						}
					}

					fprintf(cropff, "%d %s %d %d %f %d\n", crop_ID[n], R_CropName[n], WinterFlag[n], 0, R_MaxYield[n], HarvYr[n]);
					fprintf(cropff, "%d %d %f %f %d\n", plant_jday[n], R_GrowDays[n], ResiRate, R_MaxPlantN[n], EndFlag[n]);
					//fprintf(cropff, "%f %f %f %f %f\n", 12.5, R_DRCV[n], R_DRCR[n], R_PLEI[n], R_PLMX[n]);
					fprintf(cropff, "%f %d %f %f %f\n", 12.5, 0, 0.0, 0.0, 0.0);
					fprintf(cropff, "%d\n", CoverCrop[n]);
					fprintf(cropff, "%d\n", 0);
					fprintf(cropff, "%f %f %f %f\n", R_GrainFra[n], R_LeafFra[n], R_ShootFra[n], R_RootFra[n]);
					fprintf(cropff, "%f %f %f %f\n", R_graincn[n], R_leafcn[n], R_strawcn[n], R_rootcn[n]);
					fprintf(cropff, "%f %f %f %f %f\n", R_max_TDD[n], R_wreq[n], R_max_lai[n], R_N_fix[n], R_vascularity[n]);
					fprintf(cropff, "%f %f %f %f\n\n", 0.0, 0.0, 0.0, 0.0);//tree parameters
					
				}
				fclose(cropff);
		}

	}

	
	//tilling
	char Ftill[120];
	FILE *till;

	for(yr=1; yr<=F_SimuYears; yr++)
	{
		if(yr==1)
		{
			//TillDate, TillDepth, TotalTillApplications
			till_number = TotalTillApplications;
					
			for(i=1; i<=till_number; i++)
			{
				till_date[i] = TillDate[i];
				till_method[i] = TillDepth[i];

				if(RY_TillAlter[yr]==0) till_method[i] = till_method[i];//baseline 
				else if(RY_TillAlter[yr]==1) till_method[i] = 4;//20cm, till
				else if(RY_TillAlter[yr]==2) till_method[i] = 3;//10cm, reduced till
				else if(RY_TillAlter[yr]==3) till_method[i] = 1;//0cm, no-till
				else 
				{
					AfxMessageBox("Tillage method is not correctly defined");
					exit(0);
				}
			}			
		}
				
		sprintf(Ftill, "%s\\Inputs\\till-%d", OUTPUT, yr);
		till = fopen(Ftill, "w");
		if(till==NULL) note(1, Ftill);
			
		fprintf(till, "%d\n", till_number);
		for(i=1; i<=till_number; i++)
			fprintf(till, "%d  %d\n", till_date[i], till_method[i]);
		fclose(till);
	}
	

	//Fertilizing
	//RY_AutoFert[yr]: 1- conventional, 2- Slow-release, 3- Nitrification inhibitor, 4- Soil-N-adjusted rate, 
	//5- Precision fertilization, 6- usease inhibitor, 7-NH4SO4
		
	float dFertN, dManuN=0.0;
	for(yr=1; yr<=F_SimuYears; yr++)
	{
		if(yr==1)
		{	
			//CropFertDate, CropFertType, CropFertRate, &TotalFertApplications

			fert_number = TotalFertApplications;
			/*fert_number = cropping_number;
					
			for(int zx=1; zx<=cropping_number; zx++)
			{
				if(crop_ID[zx]==2) fert_date[zx] = 30;
				else fert_date[zx] = plant_jday[zx];

				if(RY_AutoFert[yr]==7) 
				{
					fert_type[zx] = 6;//ammonium sulfate
					
				}
				else 
				{
					fert_type[zx] = 3;//urea

				}

				///////////////////////////////////////////////////////// Swap between fertilizer and manure
				//dFertN = CropFertRate[crop_ID[zx]]*0.5;
				//dManuN += dFertN;
				//CropFertRate[crop_ID[zx]] -= dFertN;				
				////////////////////////////////////////////////////////

				fert_rate[zx] = CropFertRate[crop_ID[zx]];				
			}*/
			

		}

		sprintf(Ftill, "%s\\Inputs\\fert-%d", OUTPUT, yr);
		till = fopen(Ftill, "w");
		if(till==NULL) note(1, Ftill);

		fprintf(till, "%d\n", fert_number);

		for(i=1; i<=fert_number; i++)
		{
			fprintf(till, "%d %f\n", CropFertDate[i], 0.002);
			for(int vv=1; vv<=7; vv++)
			{	
				float NewFert;
				if(CropFertType[i]==vv)
				{
					NewFert = CropFertRate[i] * RY_FertilizerRate[yr];
					fprintf(till, "%f ", NewFert);
				}
				else fprintf(till, "%f ", 0.0);				
			}
			fprintf(till, "\n");
			fprintf(till, "%d %f %f %f %f %f\n", 
				RY_AutoFert[yr], 0.0, 0.0, 0.0, 0.0, 0.0);//SlowReleaseFert[yr], NitriInhibitEff[yr], NitriInhibitDur[yr], UreaInhibitEff[yr], UreaInhibitDur[yr]);
		}
		fclose(till);

/*		for(i=1; i<=fert_number; i++)
		{
			float NewFert;
			int NewFertDate;

			if(S_latitude>50.0) NewFertDate = fert_date[i] + 30;
			else NewFertDate = fert_date[i];

			fprintf(till, "%d %f\n", NewFertDate, 0.002);
				
			if(fert_type[i]==6)//ammonium sulfate
			{
				NewFert = fert_rate[i] * RY_FertilizerRate[yr];
				float Sfert = 1.143 * NewFert;
				fprintf(till, "%f %f %f %f %f %f %f ", 0.0, 0.0, NewFert, 0.0, 0.0, Sfert, 0.0);
			}
			else
			{
				for(int vv=1; vv<=7; vv++)
				{						
					if(fert_type[i]==vv)
					{
						NewFert = fert_rate[i] * RY_FertilizerRate[yr];
						fprintf(till, "%f ", NewFert);
					}
					else fprintf(till, "%f ", 0.0);				
				}
			}
			fprintf(till, "\n");
			fprintf(till, "%d %f %f %f %f %f\n", 
				RY_AutoFert[yr], 0.0, 0.0, 0.0, 0.0, 0.0);//SlowReleaseFert[yr], NitriInhibitEff[yr], NitriInhibitDur[yr], UreaInhibitEff[yr], UreaInhibitDur[yr]);
		}

		fclose(till);
*/
	}
	

//-- Create manure file ------------
	//float TotalManureC = animal[1]*1100.0 + animal[2]*96.0 + animal[3]*144.0;
	//float TotalManureN = animal[1]*72.0 + animal[2]*6.8 + animal[3]*13.6; 
	//manu_CN = TotalManureC / TotalManureN;
	
	for(yr=1; yr<=F_SimuYears; yr++)
	{
		
		sprintf(Ftill, "%s\\Inputs\\manu-%d", OUTPUT, yr);
		till = fopen(Ftill, "w");
		if(till==NULL) note(1, Ftill);

		fprintf(till, "%d\n", TotalManureApplications);

		for(int zy=1; zy<=TotalManureApplications; zy++)
		{
			fprintf(till, "%d %f %f %d %d %f\n", CManureDate[zy], CManureN[zy]*RY_AnimalManure[yr]*CManureCN[zy], CManureCN[zy], 0, 0, 0.0);
			fprintf(till, "%f %f %f\n", CManureN[zy], 0.0, 0.0);
		}
		fclose(till);
	}


	//---- irrigating -----------------
	for(yr=1; yr<=F_SimuYears; yr++)
	{
		if(yr==1)
		{   
			//fscanf(Ffarming, "%f  %s", &irri_index, notee);
			irri_index = RY_IrriIndex[yr];
		}
		
		sprintf(Ftill, "%s\\Inputs\\irri-%d", OUTPUT, yr);
		till = fopen(Ftill, "w");
		if(till==NULL)
		{
			AfxMessageBox("Can not open irri-1");
			exit(0);
		}

		if(FarmFile==1)
		{
			if(GlobeData==1&&(crop_ID[1]==12||crop_ID[1]==11)) irri_index = 0.0; //grassland or pasture
			else irri_index = RY_IrriIndex[yr];
		}

		int IrriMethod = RY_IrriAlter[yr] - 1;
		//IrriMethod: 0 flood; 2 sprinkler; 3 dripping; 4 dripping + film mulch; 5 film mulch
				
		fprintf(till, "%d %f %d\n", 0, irri_index, IrriMethod);
		fclose(till);
	}

	///////////////////////////////////////////////////////////////////////////////////
	//---- flooding -----------------
	//0 as baseline in database
	//1 Continuous flooding
	//2 Midseason drainage
	//3 Marginal flooding
	//4 Dryland rice	
	
	for(yr=1; yr<=F_SimuYears; yr++)
	{
		if(yr==1)
		{
			flood_number = TotalFloodApplications;
			for(int ww=1; ww<=flood_number; ww++)
			{
				flood_date1[ww] = FloodIni[ww];
				flood_date2[ww] = FloodEnd[ww];
			}			
		}

		sprintf(Ftill, "%s\\Inputs\\flood-%d", OUTPUT, yr);
		till = fopen(Ftill, "w");
		if(till==NULL) note(1, Ftill);

		int DelayDays = 40;

		if(RY_FloodAlter[yr]==0)//baseline
		{	
			if(flood_number==0) fprintf(till, "%d\n", flood_number);
			else
			{
				int FloodPeriod = 0;
				for(i=1; i<=flood_number; i++)
				{
					if(FloodMethod[i]==1||FloodMethod[i]==3) FloodPeriod += 1;
					else if(FloodMethod[i]==2) FloodPeriod += 3;
					else {};
				}				
				
				fprintf(till, "%d\n", FloodPeriod);
				for(i=1; i<=flood_number; i++)
				{
					if(FloodMethod[i]==1)//countinuous flood
					{
						int FloodDate1 = flood_date1[i];
						if(RY_RicePlantAlter[yr]==1) FloodDate1 = flood_date1[i] + DelayDays;

						//if(i==1) fprintf(till, "%d\n", flood_number);						
						fprintf(till, "%d %d %f %d\n", FloodDate1, flood_date2[i], 2.0, 0);
					}
					else if(FloodMethod[i]==2)//midseason drainage
					{
						int jgd = (int)((flood_date2[i]-flood_date1[i])/3.0);
						for(int yyy=1; yyy<=3; yyy++)
						{
							int date1[20], date2[20];
							date1[yyy] = flood_date1[i] + (yyy - 1) * jgd;
							if(yyy<3) date2[yyy] = date1[yyy] + (jgd - 8);
							else date2[yyy] = date1[yyy] + jgd;
							if(RY_RicePlantAlter[yr]==1&&yyy==1) date1[yyy] += DelayDays;
							fprintf(till, "%d %d %f %d\n", date1[yyy], date2[yyy], 2.0, 0);
						}
					}
					else if(FloodMethod[i]==3)//marginal flood	
					{
						int FloodDate1 = flood_date1[i];
						if(RY_RicePlantAlter[yr]==1) FloodDate1 = flood_date1[i] + DelayDays;

						//if(i==1) fprintf(till, "%d\n", flood_number);
						//if(RY_RicePlantAlter[yr]==1) flood_date1[i] += DelayDays;
						fprintf(till, "%d %d %f %d\n", FloodDate1, flood_date2[i], 2.0, 1);
					}
					
				}
			}
		}
		else if(RY_FloodAlter[yr]==1)//countinuous flood
		{
			fprintf(till, "%d\n", flood_number);
			for(i=1; i<=flood_number; i++)
			{
				int FloodDate1 = flood_date1[i];
				if(RY_RicePlantAlter[yr]==1) FloodDate1 = flood_date1[i] + DelayDays;
				
				fprintf(till, "%d %d %f %d\n", FloodDate1, flood_date2[i], 2.0, 0);
			}

			FloodMethod[1];
		}
		else if(RY_FloodAlter[yr]==2)//midseason drainage
		{
			fprintf(till, "%d\n", flood_number * 3);
			for(i=1; i<=flood_number; i++)
			{
				int jgd = (int)((flood_date2[i]-flood_date1[i])/3.0);
				for(int yyy=1; yyy<=3; yyy++)
				{
					int date1[20], date2[20];
					date1[yyy] = flood_date1[i] + (yyy - 1) * jgd;
					if(yyy<3) date2[yyy] = date1[yyy] + (jgd - 8);
					else date2[yyy] = date1[yyy] + jgd;
					if(RY_RicePlantAlter[yr]==1&&yyy==1) date1[yyy] += DelayDays;
					fprintf(till, "%d %d %f %d\n", date1[yyy], date2[yyy], 2.0, 0);
				}
			}
		}
		else if(RY_FloodAlter[yr]==3)//marginal flood	
		{
			fprintf(till, "%d\n", flood_number);
			for(i=1; i<=flood_number; i++)
			{
				int FloodDate1 = flood_date1[i];
				if(RY_RicePlantAlter[yr]==1) FloodDate1 = flood_date1[i] + DelayDays;
				//if(RY_RicePlantAlter[yr]==1) flood_date1[i] += DelayDays;
				fprintf(till, "%d %d %f %d\n", FloodDate1, flood_date2[i], 2.0, 1);
			}
		}
		else if(RY_FloodAlter[yr]==4)//dryland rice
		{
			fprintf(till, "%d\n", 0);
		}
		
		if(RainfedFlag==0)
		{
			fprintf(till, "%d %f %f\n", 0, 1.0, 1.0);//WaterControl, WaterLeakRate, WaterGetherIndex
		}
		else
		{
			fprintf(till, "%d %f %f\n", 1, 1.0, 1.5);//WaterControl, WaterLeakRate, WaterGetherIndex
		}

		fprintf(till, "%s\n", "None");//observed WT data file name
		fprintf(till, "%f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); //Empirical data for calcu;ating WT

		fclose(till);	
	}
	

		//---- grass cutting -----------------
	for(yr=1; yr<=F_SimuYears; yr++)
	{
		if(yr==1)
		{   
			//fscanf(Ffarming, "%d  %s", &cut_number, notee);
			if(crop_ID[1]==11||crop_ID[1]==12) cut_number = 3; 
			else cut_number = 0;

			cut_date[1] = 180;
			cut_date[2] = 230;
			cut_date[3] = 300;

			for(i=1; i<=cut_number; i++)
			{
				//fscanf(Ffarming, "%d  %s", &cut_month, notee);
				//fscanf(Ffarming, "%d  %s", &cut_day, notee);				
				//cut_date[i] = JulianDay(cut_month, cut_day);
				//fscanf(Ffarming, "%f  %s", &cut_amount[i], notee);
				cut_amount[i]=0.6;//cut fraction of total above-ground biomass
				cut_part[i]=1;
			}
		}

			sprintf(Ftill, "%s\\Inputs\\cut-%d", OUTPUT, yr);
			till = fopen(Ftill, "w");
			if(till==NULL) note(1, Ftill);
			
			fprintf(till, "%d\n", cut_number);
			for(i=1; i<=cut_number; i++)
			{
				fprintf(till, "%d  %f\n", cut_date[i], cut_amount[i]);
				fprintf(till, "%d\n", cut_part[i]);
			}
			fclose(till);
			
	}

	//---- grazing -----------------
	for(yr=1; yr<=F_SimuYears; yr++)
	{
		if(yr==1)
		{   
			//fscanf(Ffarming, "%d  %s", &graze_number, notee);
			graze_number = 0;

			for(i=1; i<=graze_number; i++)
			{
				/*fscanf(Ffarming, "%d  %s", &graze_month1, notee);
				fscanf(Ffarming, "%d  %s", &graze_day1, notee);
				fscanf(Ffarming, "%d  %s", &graze_month2, notee);
				fscanf(Ffarming, "%d  %s", &graze_day2, notee);
				graze_date1[i] = JulianDay(graze_month1, graze_day1);
				graze_date2[i] = JulianDay(graze_month2, graze_day2);

				fscanf(Ffarming, "%f  %s", &cattle[i], notee);
				fscanf(Ffarming, "%f  %s", &horse[i], notee);
				fscanf(Ffarming, "%f  %s", &sheep[i], notee);
				fscanf(Ffarming, "%f  %s", &graze_hrs[i], notee);*/

				graze_date1[i] = 0;
				graze_date2[i] = 0;					
				cattle[i] = 0.0;
				horse[i] = 0.0;
				sheep[i] = 0.0;
				graze_hrs[i] = 0.0;	
			}
		}

		sprintf(Ftill, "%s\\Inputs\\graz-%d", OUTPUT, yr);
			till = fopen(Ftill, "w");
			if(till==NULL) note(1, Ftill);
			
			fprintf(till, "%d\n", graze_number);
			for(i=1; i<=graze_number; i++)
			{
				fprintf(till, "%d %d\n", graze_date1[i], graze_date2[i]);
				fprintf(till, "%f %f %f\n", cattle[i], horse[i], sheep[i]);
				fprintf(till, "%f\n", graze_hrs[i]);
			}
			fclose(till);		
	}

	//---- plastic film cover -----------------
	for(yr=1; yr<=F_SimuYears; yr++)
	{
		if(yr==1)
		{
			sprintf(Ftill, "%s\\Inputs\\plastic-1", OUTPUT);
			till = fopen(Ftill, "w");
			if(till==NULL) note(1, Ftill);
			
			if(RY_FilmCover[yr]==1||RY_IrriAlter[yr]==5) 
			{
				fprintf(till, "%d %d\n", cropping_number, 1);
				for(i=1; i<=cropping_number; i++)
				{
					if(plant_jday[i]<=harvest_jday[i])
						fprintf(till, "%d %d\n", plant_jday[i], harvest_jday[i]);
					else
						fprintf(till, "%d %d\n", 1, harvest_jday[i]);

					fprintf(till, "%f\n", 1.0);
				}
			}
			else
			{
				fprintf(till, "%d %d\n",0, 0);
			}
			fclose(till);
		}
		else
		{
			sprintf(Fsource, "%s\\Inputs\\plastic-1", OUTPUT);
			sprintf(Ftarget, "%s\\Inputs\\plastic-%d", OUTPUT, yr);
			FileCopy(Fsource, Ftarget);		
		}
	}

	//char F_INI[200];
	FILE *fpp;
	sprintf(F_INI, "%s\\Inputs\\cropini-1", OUTPUT);    
	fpp = fopen(F_INI, "w");
	if (fpp == NULL) note(1, F_INI); 
	fprintf(fpp, "%d\n", 0);
	fclose( fpp );
}


void region_soil_files(int soil_yr, float max_SOC, float min_SOC, float max_clay, float min_clay, 
					float max_pH, float min_pH, float max_BD, float min_BD, int landtype,
					int OnlyRice, char* CROPID, float WRL, char* county_name, int GlobeData,
					float S_latitude, float IniSnow, int MonteCarlo, float slope, float SoilQuality)
{
    int i, ave_ST, Q, n;
	
	double dt;
	FILE *fpi;
    char fname[255],SoilName[120];
	float Soil_Clay, Sts, Sks, Fldcap, Wiltpt, LateralInflux, PassiveCCN, Psisat, Beta, H;
	float ave_clay, ave_pH, ave_BD, ave_SOC, TTOO;
	float AcWater, SurfWater, SnowPack, Qstar;
	int Idc = 0;
	float rBypassF=0.0, BypassF; //corrected on 7/24/2001
	float TH = SOILDEPTH;//total depth of simulated soil profile (0-50 cm)
	float Soil_NO3, Soil_NH4, Soil_moisture;
	
	float m, V, CEC;
	double RCVL[2], RCL[2], RCR[2];
	double Urea[2], NH3[2];
	double Tranr[2], OCini[2], Dphum[2], CharC[2];
	double s_NO3[2], s_NH4[2], ClayNH4[2];
	double s_NO[2], s_N2O[2];
	double s_N2[2], s_NO2[2], s_IniNH4[2];
    
	double PS, FLDCAPw, Wiltptw, TravelTime, ClayF1, ClayF2;
	float RCNRVL, RCNRL, RCNRR, RCNB, RCNH, RCNM;
	double stub1, stub2, stub3;

	char A_country[80], r_Root1[240], r_Root2[240], DatabaseName[240];
	float r_ResidueLeft, r_AnimalManure, r_WRL;
	float r_FertRate, r_Irri, r_CO2, r_AirTemp, r_YieldIncrease;
	int r_NoTill, DataType;
	char ScenarioName[120];
	int A_RegionCode, A_CountryCode, A_StateCode, A_major_target, A_DailyItem, A_SimuYears, A_StartYear, A_jd;
	int A_FarmFile, A_OnlyRice, A_InterDrain;

	float RY_AtmoCO2[100], RY_AirTemp[100], RY_RainTimes[100], RY_YieldIncrease[100], RY_WaterDemand[100]={0.0,0.0}, RY_MaxTemp[100]={0.0,0.0};	
	float RY_LitterBackField[100], RY_AnimalManure[100];
	float RY_FertilizerRate[100], RY_IrriIndex[100], RY_NitrificationInhibit[100], RY_CropCN[100], jf;
	int RY_Tillage[100], RY_Drainage[100], RY_ShallowWater[100], RY_FilmCover[100], RY_AutoFert[100];
	int RY_FloodAlter[100], RY_TillAlter[100], RY_IrriAlter[100], RY_RicePlantAlter[100];
	int RY_SlowReleaseDays[100], RY_IniGridID[100], jd;

	char Fregion[120];
	FILE *region;

	RY_NitrificationInhibit[1] = 0.0;
	
	if(MonteCarlo==0)
	{
		sprintf(Fregion, "%s\\region_input", INTER);
		region = fopen(Fregion, "r");
		
		fscanf(region, "%d %d %d", &A_RegionCode, &A_CountryCode, &A_StateCode);
		fscanf(region, "%s", A_country);
		fscanf(region, "%s %s", r_Root1, r_Root2);
		fscanf(region, "%s", DatabaseName);
		fscanf(region, "%s", ScenarioName);

		fscanf(region, "%d", &DataType);
		fscanf(region, "%f %f %f", &r_CO2, &r_AirTemp, &r_YieldIncrease);
		fscanf(region, "%d", &A_major_target);
		fscanf(region, "%d", &A_DailyItem);
		fscanf(region, "%d", &A_SimuYears);
		fscanf(region, "%d", &A_StartYear);
		fscanf(region, "%d", &A_jd); 

		fscanf(region, "%d", &A_FarmFile);

		fclose(region);

		if(A_FarmFile==1)
		{
			for(int yy=1; yy<=A_SimuYears; yy++)
			{
					sprintf(Fregion, "%s\\region_yr%d", INTER, yy);
					region = fopen(Fregion, "r");	
										
					fscanf(region, "%f %f %f", &RY_AtmoCO2[yy], &RY_AirTemp[yy], &RY_RainTimes[yy]);
					fscanf(region, "%f %f %f", &RY_LitterBackField[yy], &RY_FertilizerRate[yy], &RY_AnimalManure[yy]);
					fscanf(region, "%d %d %d", &RY_AutoFert[yy], &RY_FloodAlter[yy], &RY_TillAlter[yy]);	
					fscanf(region, "%f %f %f", &RY_YieldIncrease[yy], &RY_WaterDemand[yy], &RY_MaxTemp[yy]);
					fscanf(region, "%f %f %f %f %f", &RY_CropCN[yy], &RY_IrriIndex[yy], &jf, &jf, &jf);
					fscanf(region, "%d %d %d %d %d", &RY_IrriAlter[yy], &RY_RicePlantAlter[yy], &jd, &jd, &jd);				
					fclose(region);				
			}
		}
	}
	else //MonteCarlo==1
	{

	}

	//average values
	ave_SOC   = (float)((max_SOC + min_SOC) * 0.5);
    ave_clay = (float)((max_clay + min_clay) * 0.5);
    ave_pH   = (float)((max_pH + min_pH) * 0.5);
    ave_BD   = (float)((max_BD + min_BD) * 0.5);

	if(MonteCarlo==0)
	{
		if(soil_yr==1) TTOO = max_SOC;
		else TTOO = min_SOC;
		
		if(A_major_target==4)//NH3
		{
			if(soil_yr==1) 
			{
				ave_pH = max_pH;
			}
			else
			{
				ave_pH = min_pH;
			}
		}
		else if(A_major_target==3)//CH4
		{
			if(soil_yr==1) ave_clay = min_clay;				
			else ave_clay = max_clay;				
		}
		else if(A_major_target==5)//N leaching
		{
			if(soil_yr==1) ave_clay = min_clay;				
			else ave_clay = max_clay;
		}
		else{}//0-dSOC, 1-CO2, 2-N2O, 
	}
	else
	{
		TTOO = ave_SOC;
	}

	if (TTOO >= .2) ave_ST = 12;
	else if (ave_clay <= .03) ave_ST = 1;
	else if (ave_clay <=  .06) ave_ST = 2;
	else if (ave_clay <= .09) ave_ST = 3;
	else if (ave_clay <= .14) ave_ST = 4;
	else if (ave_clay <= .19) ave_ST = 5;
	else if (ave_clay <= .27) ave_ST = 6;
	else if (ave_clay <= .34) ave_ST = 7;
	else if (ave_clay <= .41) ave_ST = 8;
	else if (ave_clay <= .43) ave_ST = 9;
	else if (ave_clay <= .49) ave_ST = 10;
	else ave_ST = 11;//if (ave_clay <= .63)	

	if (ave_ST<1 && ave_ST>13) AfxMessageBox("Error for soil texture number");
    sprintf(fname,"%s\\Library\\lib_soil\\soil_%d", ROOTDIR, ave_ST);
	
    if ((fpi=sopen(fname, 1)) == NULL) AfxMessageBox("Can not open lib_soil file");

    fscanf(fpi,"%s %s", SoilName,notee);
	fscanf(fpi,"%f %s", &Soil_Clay,notee);
    fscanf(fpi,"%f %s", &Sts, notee);
    fscanf(fpi,"%f %s", &Sks, notee);
    fscanf(fpi,"%f %s", &Fldcap, notee);
    fscanf(fpi,"%f %s", &Wiltpt, notee);
    fscanf(fpi,"%f %s", &jf, notee);
    fscanf(fpi,"%f %s", &Psisat, notee);
    fscanf(fpi,"%f %s", &Beta, notee);
    fclose (fpi);
   
	LateralInflux = 1.0;
	PassiveCCN = 500.0;
	//layer thickness
	AcWater   = 0.0;
	SurfWater = 0.0;
	SnowPack  = IniSnow;
	Idc = 1 + rBypassF;

		/*if (ave_ST != 12) { //'If Soiltexture.ListIndex <> 11 Then
			 Sts = float(1 - ave_BD * (TTOO / 1.3 + (1 - TTOO) / 2.6));
		}
		if (Sts<=0) //safety check
		{
			//MessageBox(NULL,"Soil-Density or Soil Organic may be wrong! Please input a smaller one.","Inputed Error:",NULL);
			Sts = 1;
			//return -1;
		}*/

		if (ave_ST < 10) Sks = Sks * (float)0.6; //cm/min -> m/hr

		Qstar = (float)(6.45 * (Soil_Clay - 0.01) + 1);

		BypassF = 0.1 * ((float)Idc - 1);
    
		float T01 = 1;
		
		if (BypassF > 0.0) T01 = BypassF * 10.0 + 1.0;
		
		Sks = Sks * T01;
    
		//float dt;
		dt = (2.0 * 0.005 / Sts);
		if (dt < Sks) {
			H = dt;
		}
		else {
			H = Sks;
		}
    
		if (H*190.0 < TH )
			H = TH / 190.0;//total layer number is <=50
		Q = (int)(TH / H);

		if (Q > 190) 
		{
			Q = 190;
			H = TH / 190.0;
		}

		//////////////////////////////

		// define partitioning of SOC 
		SocProfile(landtype, TTOO, S_latitude, &Soil_Litter, &Soil_humads, &Soil_humus, &PassiveC);

		Soil_NO3 = SOCtoNO3(TTOO, S_latitude);
		Soil_NH4 = 0.1 * Soil_NO3;	

		Soil_moisture = (Fldcap+Wiltpt)*0.5;

		//////////////////////////////////////////////////////////////////

		CEC= (float)(Soil_Clay * 46.0);
		
		m  = (float)(ave_BD * 1000. * H * 10000.);
		V  = (float)(H * 10000. * Sts);	// m^3/layer/ha
		
		n = Q;	
    
		PS		= H * Sts;	// porosity  (m/layer)
		FLDCAPw = PS * Fldcap;	// m water/layer
		Wiltptw = PS * Wiltpt;	// m water/layer
		TravelTime = 20.0 * (PS - FLDCAPw) / Sks;	// hr/layer
			// fraction of soil water available for plants, can be tuned
		ClayF1 = pow(10.0,-Soil_Clay / 0.75 - 0.2);
		ClayF2 = Soil_Clay * 6.;

		CN_ratios(&RCNRVL, &RCNRL, &RCNRR, &RCNB, &RCNH, &RCNM, &PassiveCCN);
		    
		Tranr[1] = TTOO * Soil_Litter * m;
		OCini[1] = TTOO * Soil_humads * m;
		Dphum[1] = TTOO * Soil_humus * m;
		CharC[1] = TTOO * PassiveC * m;
   
		s_NO3[1] = Soil_NO3 * m / 1000000.;
		s_IniNH4[1] = Soil_NH4 * m / 1000000.;
    
		RCVL[1] = 0.0 * Tranr[1];
		RCL[1]  = 0.0 * Tranr[1];
		RCR[1]  = 1.0 * Tranr[1];
     
		s_NH4[1]   = s_IniNH4[1] * 0.7;
		ClayNH4[1] = s_IniNH4[1] * 0.3;
		
		float F_soc = TTOO/0.058;
		if(F_soc>1.0) F_soc = 1.0;

		//ClayNH4[1] = F_soc * CEC * 0.4;
		Urea[1]= 0.;
		NH3[1] = 0.;
		stub1  = 0.;
		stub2  = 0.;
		stub3  = 0.;
		//WeedN  = 0.;
   		s_NO[1] = 0.;
		s_N2O[1]= 0.;
		s_N2[1] = 0.;
		s_NO2[1]= 0.;

		float IniFrostN2O=0.0, IniFrostN2=0.0,ice=0.0,tt[290];
		int Retard=1;
    
			//check data
		if (ave_ST<=0) {
			AfxMessageBox("No soil type data");
			exit(0);
		}
		if (Soil_Clay<=0.0) {
			AfxMessageBox("Soil clay = 0");
			exit(0);
			
		}
		if (ave_BD<=0.0) {
			AfxMessageBox("Soil bulk density = 0");
			exit(0);
		}
		if (TTOO<=0.0) {
			AfxMessageBox("Soil organic C = 0");
			exit(0);
		}
		if (Soil_NO3<0.0) {
			AfxMessageBox("Initial NO3- < 0");
			exit(0);
		}
		if (Soil_NH4<0.0) {
			AfxMessageBox("Initial NH4+ < 0");
			exit(0);	
		}
		if (Soil_Litter<0.0 || Soil_humads<0.0 || Soil_humus<0.0) {
			AfxMessageBox("Initial litter < 0");
			exit(0);	
		}

		char climf[80], ClimFileName[300], ClimYrName[300];
		FILE* fClim;
		int jday;
		float ave_T, ave_YrT;

		sprintf(climf, "%s\\Inputs\\clim-1", OUTPUT);
		fClim = fopen(climf, "r");
		if(fClim==NULL)
		{
			AfxMessageBox("Can not find file clim-1");
			exit(0);
		}
		else
		{
			fscanf(fClim, "%s", ClimFileName);
			fscanf(fClim, "%s", ClimYrName);
		}
		fclose(fClim);

		sprintf(climf, "%s\\Inputs\\%s", OUTPUT, ClimFileName);
		fClim = fopen(climf, "r");
		if(fClim==NULL) note(0, climf);
		else
		{
			fscanf(fClim, "%d  %f", &jday, &ave_T);
		}
		fclose(fClim);

		sprintf(climf, "%s\\Inputs\\%s", OUTPUT, ClimYrName);
		fClim = fopen(climf, "r");
		if(fClim==NULL)
		{
			AfxMessageBox("Can not find file clim.yr");
			exit(0);
		}
		else
		{
			for(i=1; i<=13; i++)
				fscanf(fClim, "%f", &ave_YrT);
		}
		fclose(fClim);



		for (i=1; i<=Q; i++)
		{
			tt[i] = ave_YrT + (ave_T - ave_YrT) / (float)powf(i*H*100, 0.5);
			if (ave_T<0.0 && tt[i] < ave_T) tt[i] = ave_T;
		}

		char fsoila[255];
		FILE *fpo;

		if(MonteCarlo==0)
		{
			if(soil_yr==1) sprintf(fsoila,"%s\\Inputs\\soil-A1", OUTPUT);
			else sprintf(fsoila,"%s\\Inputs\\soil-B1",OUTPUT);
		}
		else sprintf(fsoila,"%s\\Inputs\\soil-1",OUTPUT);

		fpo=fopen(fsoila,"w");
		if (fpo==NULL) 
		{
			CString err;
			err.Format("can not create file %s", fsoila);
			AfxMessageBox(err);
			exit(0);
		}

		fprintf(fpo,"%3d\n", ave_ST);
		fprintf(fpo,"%s\n", SoilName);
		fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
			Soil_Clay, Sts, Sks, Fldcap, Wiltpt, LateralInflux);
		fprintf(fpo,"%.2f %.2f %.2f %.2f %d  %f\n",
			Psisat, Beta, ave_BD, ave_pH, Idc, TTOO);
		fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
			Soil_NO3, Soil_NH4, Soil_Litter, 
			Soil_humads, Soil_humus, 0.0);
		fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %d\n",
			H, TH, m, V, Q);
		fprintf(fpo,"%.4f  %.4f\n",//%.4f  %.4f  %.4f  %.4f  
			ClayF1, ClayF2);//PS, FLDCAPw, Wiltptw, TravelTime, 
		fprintf(fpo,"%.4f  %.4f  %d  %.4f  %.4f  %.4f  %.4f\n",
			Qstar, BypassF, Retard, RCNB, RCNH, RCNM, RCNRVL);
		fprintf(fpo,"%.4f  %.4f %.4f  %.4f  %.4f  %.4f\n",
			RCNRL, RCNRR, AcWater, SurfWater, 
			SnowPack, stub1);
		fprintf(fpo,"%.4f  %.4f\n", stub2, stub3);
		fprintf(fpo, "%.4f  %.4f  %.4f\n",
			PassiveCCN, IniFrostN2O, IniFrostN2);
    

		/*for (i = 1;i<=Q;i++) {
			fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f\n",
				RCVL[i], RCL[i], RCR[i], OCini[i], Dphum[i]);
			fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
				s_NO2[i], s_NO3[i], s_NH4[i], ClayNH4[i], Urea[i], NH3[i]);
			fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
				s_NO[i], s_N2O[i], s_N2[i], tt[i], Fldcap, ice);
		}*/
		
		if(WRL == 0.0) r_WRL = 9.9;
		else if(WRL == 1.0) r_WRL = 0.05;
		else if(MonteCarlo==0)
		{
			if(soil_yr==1) r_WRL = 0.05;
			else r_WRL = 9.9;
		}
		else r_WRL = 9.9;

		fprintf(fpo, "%f\n", 1.0); //microbial activity
		fprintf(fpo, "%f\n", r_WRL); //soil water-retention layer depth, m
		fprintf(fpo, "%f %f\n", slope, SoilQuality);
		fprintf(fpo, "%f %f\n", Fldcap, Wiltpt);
		fprintf(fpo, "%f %f\n", socA[landtype], socB[landtype]);
		fprintf(fpo, "%f %f %f %f %f %f %f %f %f\n", RCVL[1], RCL[1], RCR[1], OCini[1], 
			Dphum[1], s_NO2[1], s_NO3[1], s_NH4[1], ClayNH4[1]);
		fprintf(fpo, "%f\n", tt[1]);
		fprintf(fpo, "%f\n", 9.99);//highest WT depth
		fprintf(fpo, "%d\n", 0);//use observed SIN profile
		fprintf(fpo, "%f\n", CharC[1]);//Inorganic C
		fprintf(fpo, "%f\n", 1.0);//litter decomposition factor
		fprintf(fpo, "%f\n", 1.0);//humads decomposition factor
		fprintf(fpo, "%f\n", 1.0);//humus decomposition factor

		fclose (fpo);

		//livestock operation system
/*		CString SF;
		FILE* sf;
		SF.Format("%s\\Inputs\\ManureHouse_%d.txt", OUTPUT, i);
		sf=fopen(SF, "w");
		if(sf==NULL) note(1, SF);
*/
/*		fprintf(sf, "%d\n", m_Stock1);  
		
		//if(m_Stock1==1)								//use a input file name
		//	fprintf(sf, "%s\n", StockFileName);
		//else										//use average input data
		{
			int AnimalType = m_AnimalType.GetCurSel()+1;			
			fprintf(sf, "%d\n", 1);
			fprintf(sf, "%d  %f  %f  %f\n", AnimalType, m_AnimalHeads, m_FeedRate, m_ProteinPercent);
		}
		
		fprintf(sf, "%f  %d\n", m_FloorArea, m_FloorSurfaceType);//0 slatted floor; 1 conrete floor
		fprintf(sf, "%d  %f  %f  %f\n", m_BedType, m_BedCN, m_BedFrequency, m_BedAmount);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
		fprintf(sf, "%d  %f\n", m_Ventilation, m_VentRate);// 0 natural, 1 fan
		fprintf(sf, "%f\n", m_RemovalFrequency);
		fprintf(sf, "%f %f %f %f\n", m_UC, m_UL, m_UD, m_UR);
		fprintf(sf, "%f %f %f %f\n", m_FC, m_FL, m_FD, m_FR);
*/
//		fclose(sf);


}




void region_site_files(char *county_name, float r_longitude, float r_latitude, 
							  char *ClimName, char *region_name)
{
		char p_name[256];
		FILE *fsite;

		//site
		sprintf(p_name,"%s\\Inputs\\site",OUTPUT);
		fsite = fopen(p_name, "w");
		if ( fsite == NULL ) 
		{
			AfxMessageBox("Can not create file site");
			exit(0);
		}
		fprintf(fsite, "%s\n", county_name);
		fprintf(fsite, "%d  %d  %f  %d  %f %d %d\n", 1, 0, r_latitude, 0, r_longitude, 1, 0);
		fprintf(fsite, "%s\n", region_name);
		fprintf(fsite, "%s\n", county_name);
		fprintf(fsite, "%s\n", ClimName);

		fclose( fsite );

		//span
		sprintf(p_name,"%s\\Inputs\\span", OUTPUT);
		fsite = fopen(p_name, "w");
		if ( fsite == NULL ) 
		{
			AfxMessageBox("Can not create file span");
			exit(0);
		}
		fprintf(fsite, "%d\n", 1);
		fclose( fsite );
}

int region_climate_files(char *climfile_ID, float r_latitude, float RainN, float BaseCO2, 
		int county_ID1, float CO2IncreaseRate, int GlobeData, int MonteCarlo, int StartYear,
		int DroughtID, int DryYear, int MidYear, int WetYear)
{
	char Fregion[120], r_Root1[220], r_Root2[240];
	char CountryName[120], ScenarioName[120], DatabaseName[240];
	int C_RegionCode, C_CountryCode, C_StateCode, miss_clim=0;
	char r_Country[80], jks[50];
	int DataType, C_major_target, C_DailyItem, C_SimuYears, C_StartYear, C_ViewMode, C_FarmFile, C_jd;
	float C_BaseCO2, C_AirTempRate, C_YieldIncrease, C_jf, C_CO2IncreaseRate;
	float WindSpeed, Humidity;

#ifdef HYDRO
	float MuslemaxRain;
#endif

	float RY_AtmoCO2[100], RY_AirTemp[100], RY_RainTimes[100], RY_YieldIncrease[100],RY_WaterDemand[100]={0.0,0.0}, RY_MaxTemp[100]={0.0,0.0};	
	float RY_LitterBackField[100], RY_AnimalManure[100], RY_CropCN[100];
	float RY_FertilizerRate[100], RY_IrriIndex[100], RY_NitrificationInhibit[100];
	int RY_Tillage[100], RY_Drainage[100], RY_ShallowWater[100], RY_FilmCover[100], RY_AutoFert[100], RY_IniGridID[100];
	int RY_SlowReleaseDays[100], RY_FloodAlter[100]={0,0}, RY_TillAlter[100]={0,0}, RY_IrriAlter[100]={0,0};
	int RY_RicePlantAlter[100]={0,0};

	float Day_Hrs,temp=0,Rainfall=0,maxT=0,minT=0,solrad,jf;
	int   jday=0,jday0=0,tn,j,k, Mday[13], yr,jd;
	char fname[120], Pname[120], Dname[120];
	
	float MonAveT[13];
	float air_NH3 = 0.06;
	char NNM[300];

	FILE *fpo, *fpii,*fday;

	if(MonteCarlo==0)
	{
		FILE *region;

		sprintf(Fregion, "%s\\region_input", INTER);
		region = fopen(Fregion, "r");
		if(region==NULL) note(0, Fregion);
				
		fscanf(region, "%d %d %d", &C_RegionCode, &C_CountryCode, &C_StateCode);
		fscanf(region, "%s", CountryName);
		fscanf(region, "%s %s", r_Root1, r_Root2);
		fscanf(region, "%s", DatabaseName);
		fscanf(region, "%s", ScenarioName);
		fscanf(region, "%d", &DataType);
		fscanf(region, "%f %f %f", &C_BaseCO2, &C_AirTempRate, &C_YieldIncrease);
		fscanf(region, "%d", &C_major_target);
		fscanf(region, "%d", &C_DailyItem);
		fscanf(region, "%d", &C_SimuYears);
		fscanf(region, "%d", &C_StartYear);
		fscanf(region, "%d", &C_ViewMode); 
		fscanf(region, "%d", &C_FarmFile);
		fclose(region);
		sprintf(r_Country, "%s", CountryName); 

		if(DroughtID==1) C_SimuYears = 2;

		if(C_FarmFile==1)
		{
			for(int yy=1; yy<=C_SimuYears; yy++)
			{
				sprintf(Fregion, "%s\\region_yr%d", INTER, yy);
				region = fopen(Fregion, "r");	
				if(region==NULL) note(0, Fregion);
								
				fscanf(region, "%f %f %f", &RY_AtmoCO2[yy], &RY_AirTemp[yy], &RY_RainTimes[yy]);
				fscanf(region, "%f %f %f", &RY_LitterBackField[yy], &RY_FertilizerRate[yy], &RY_AnimalManure[yy]);
				fscanf(region, "%d %d %d", &RY_AutoFert[yy], &RY_FloodAlter[yy], &RY_TillAlter[yy]);	
				fscanf(region, "%f %f %f", &RY_YieldIncrease[yy], &RY_WaterDemand[yy], &RY_MaxTemp[yy]);
				fscanf(region, "%f %f %f %f %f", &RY_CropCN[yy], &RY_IrriIndex[yy], &jf, &jf, &jf);
				fscanf(region, "%d %d %d %d %d", &RY_IrriAlter[yy], &RY_RicePlantAlter[yy], &jd, &jd, &jd);
				
				fclose(region);
			}
		}
	}
	else //MonteCarlo==1
	{
		C_SimuYears = 1;
		C_StartYear = StartYear;
		C_FarmFile = 0;
		C_BaseCO2 = BaseCO2;
	}	

	C_CO2IncreaseRate = CO2IncreaseRate;
	
	CString message;

	int YR;

	////////////////////////////////////////////////////////////////////////////////////////////////
	if(DroughtID==1)
	{
		char LocationName[300];//Dname[300], Yname[300], 
		char DDname[4][300], DYname[4][300];
		int YieldSite, YieldYear, YieldToday, YieldCrop,YieldMonth, YieldDay;
	
			CString YF;
			FILE* yf;
			YF.Format("%s\\YieldPrediction", INTER);
			yf=fopen(YF, "r");
			if(yf==NULL) note(0,YF);

			fscanf(yf, "%d %d %d %d %s %d %d", &YieldSite, &YieldCrop, &YieldYear, &YieldToday, LocationName,&YieldMonth, &YieldDay);
			fclose(yf);

			//First year climate name
			sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,1);
			if ((fpo=sopen(fname,0))==NULL) note(1, fname);			
			sprintf(DDname[0],"%d-%d.day",county_ID1, 1);
			sprintf(DYname[0],"%d-%d.yr",county_ID1, 1);	
			fprintf(fpo,"%s\n",DDname[0]);		
			fprintf(fpo,"%s\n",DYname[0]);
			fclose(fpo);
		
			//Second year climate names
			sprintf(Pname,"%d",YieldSite);
			sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,2);
			if ((fpo=sopen(fname,0))==NULL) note(1, fname);		
			sprintf(DDname[1],"%d-%d-dry.day",county_ID1, 2);
			sprintf(DDname[2],"%d-%d-mid.day",county_ID1, 2);
			sprintf(DDname[3],"%d-%d-wet.day",county_ID1, 2);
			sprintf(DYname[1],"%d-%d-dry.yr",county_ID1, 2);
			sprintf(DYname[2],"%d-%d-mid.yr",county_ID1, 2);
			sprintf(DYname[3],"%d-%d-wet.yr",county_ID1, 2);
			fprintf(fpo,"%s %s %s\n",DDname[1],DDname[2],DDname[3]);		
			fprintf(fpo,"%s %s %s\n",DYname[1],DYname[2],DYname[3]);
			fclose(fpo);
	
			int UseID=10;
			int ClimateFileType=1;
			float lat = r_latitude;
			int IfCheck=0;

			for(int yrr=0; yrr<=3; yrr++)
			{
				MakeDailyClimateFile(Pname, DDname[yrr], DYname[yrr], UseID, ClimateFileType, lat, IfCheck,
					RainN,air_NH3,C_BaseCO2, C_CO2IncreaseRate,	YieldSite, YieldYear, YieldToday, 
					climfile_ID, yrr, DryYear, MidYear, WetYear, CountryName);
			}	
	}
	else
	{
	////////////////////////////////////////////////////////////////////////////////////////////////
	for(yr=1; yr<=C_SimuYears; yr++)
	{
		float YrAveT = 0.0;
		float YrRain = 0.0;

		YR = C_StartYear + (yr-1); //normal 
		//YR = C_StartYear; //only for CA Rangeland project

		sprintf(fname,"%s\\Inputs\\clim-%d", OUTPUT, yr);
		if ((fpo=fopen(fname,"w"))==NULL) 
		{
			AfxMessageBox("Can not create file clim-1");
			exit(0);
		}
		fprintf(fpo,"clim_%d.day\n", YR);
		fprintf(fpo,"clim_%d.yr\n", YR);
		fclose(fpo);
				
		sprintf(Dname,"%s\\Inputs\\clim_%d.day", OUTPUT, YR);
		fday=fopen(Dname,"w");
		if (fday==NULL) 
		{
			AfxMessageBox("Can not create file clim.day");
			exit(0);
		}
        
		// Open climate datafile as input
/*		int LLL=strlen(CountryName);
		int uu;
		for(uu=0;uu<=LLL-1;uu++)
		{
			if(CountryName[uu]=='_') break; 
		}

		char NewContName[200];
		Glean_String(CountryName, 0, uu-1, NewContName);		
*/
ReTry:
		if(MonteCarlo==1) sprintf(NNM, "%s", climfile_ID);
		else
		{
			if(GlobeData==0)
			{
				sprintf(NNM, "%slib_clim\\%d\\%s", r_Root1, YR, climfile_ID);
				fpii=fopen(NNM,"r");
				if(fpii==NULL) 
				{
					sprintf(NNM, "%slib_clim\\%d\\%s_%d.txt", r_Root1, YR, climfile_ID, YR);
					fpii=fopen(NNM,"r");
					if(fpii==NULL) 
					{
						sprintf(NNM, "%slib_clim\\%d\\%s_%d", r_Root1, YR, climfile_ID, YR);
						fpii=fopen(NNM,"r");
						if(fpii==NULL) 
						{
							sprintf(NNM, "%slib_clim\\%d\\%s.txt", r_Root1, YR, climfile_ID);
							fpii=fopen(NNM,"r");
							if(fpii==NULL) 
							{
									CString msg;
									msg.Format("Climate file %s is missing.", NNM);
									AfxMessageBox(msg);
									miss_clim = 1;
									break;
							}
						}
					}
				}
			}
			else
			{
				sprintf(NNM, "%s\\Lib_clim\\%d\\%s_%d.txt", r_Root2, YR, climfile_ID, YR);
					fpii=fopen(NNM,"r");
					if(fpii==NULL) 
					{
						CString msg;
						msg.Format("Climate file %s is missing.", NNM);
						AfxMessageBox(msg);
						miss_clim = 1;
						break;
					}

			}

		}
/*			else
			{
				sprintf(NNM, "%slib_clim\\%d\\%s_%d.txt", r_Root2, YR, climfile_ID, YR);//NewContName

				fpii=fopen(NNM,"r");
				if(fpii==NULL) 
				{
					CString msg;
					msg.Format("Climate file %s is missing.", NNM);
					AfxMessageBox(msg);
					miss_clim = 1;
					break;
				}
			}
		}
*/
		

/*		{
			if(MonteCarlo==0) sprintf(NNM, "%slib_clim\\%d\\%s_%d.txt", r_Root1, YR, climfile_ID, YR);
			else sprintf(NNM, "%s.txt", NNM);
			fpii=fopen(NNM,"r");
			if (fpii==NULL) 
			{
				sprintf(NNM, "%s.txt", NNM);
				fpii=fopen(NNM,"r");
				if (fpii==NULL) 
				{
					message.Format("clim: Can not find file %s", NNM);
					AfxMessageBox(message);
					goto ReTry;
				}
			}
		} 
*/
		char www[200];
		int Day1Flag=0;

		for(;;)
		{
			fscanf(fpii, "%s", jks);
			if(strcmp("1",jks)==0) 
			{
				Day1Flag=1;
				break;
			}
		}

/*		fscanf(fpii, "%s", jks);
		if(strcmp("1",jks)==0)
		{
			fclose(fpii);
			fpii=fopen(NNM,"r");
		}

		fscanf(fpii, "%s", jks);
		if(strcmp("1",jks)==0)
		{
			fclose(fpii);
			fpii=fopen(NNM,"r");
			fscanf(fpii, "%s", jks);
		}
		else
		{
			fgets(www, 300, fpii);
			//fgets(www, 300, fpii);
		}
*/		
		tn = 0;
    
		Mday[2] = 28;
		Mday[4] = Mday[6] = Mday[9] = Mday[11] = 30;
		Mday[1] = Mday[3] = Mday[5] = Mday[7] = Mday[8] = Mday[10] = Mday[12] = 31;
     			
		//fprintf(fpi0, "%s\n", climfile_ID);
		for (j = 1;j<=12;j++) 
		{
			MonAveT[j] = 0;
			for (k = 1;k<=Mday[j];k++) 
			{
				float lat;
				if(r_latitude>=0.0) lat = r_latitude;
				else lat = -r_latitude;

				tn++;

				Day_Hrs = 0.0;

				solrad = day_par(tn, lat, &Day_Hrs);
				WindSpeed = 2.0;
				Humidity = 60.0;

				//if(GlobeData==0)//Shangrila
				//{
				if(Day1Flag==1) 
				{
					jday = 1;
					fscanf(fpii, "%f %f %f", &maxT, &minT, &Rainfall);
					Day1Flag = 0;
				}
				else
					fscanf(fpii, "%d %f %f %f", &jday, &maxT, &minT, &Rainfall);//regional data format

				fgets(www, 200, fpii);

#ifdef HYDRO//===Read max half hour rainfall; dengjia
					//fscanf(fpii, "%f", &MuslemaxRain);
					MuslemaxRain = Rainfall / 3.0;
#endif					
					
					//fgets(jks, 100, fpii);
				//}
				//else if(GlobeData==1)//Global 
				//{
				//	fscanf(fpii, "%d %f %f %f %f %f", &jday, &maxT, &minT, &Rainfall);//, &WindSpeed, &solrad);//global data format
				//}	
				/*else if(GlobeData==2)//USA county 
				{
					fscanf(fpii, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &jf);//USA county data format
					WindSpeed = 0.0;
				}
				else if(GlobeData==3)//China county 
				{
					fscanf(fpii, "%d %f %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &WindSpeed, &solrad);//global data format
					WindSpeed = 0.0;
				}*/
				//else{}

				if(tn!=jday)
				{
					sprintf(notee, "Error at day %d in climate data file %s", tn, NNM);
					AfxMessageBox(notee);
					exit(0);
				}

				//climate change
				if(C_FarmFile==1)
				{
					maxT += RY_AirTemp[yr];
					minT += RY_AirTemp[yr];
					Rainfall *= RY_RainTimes[yr];
				}

				temp =float( (maxT + minT) *0.5);
				
				fprintf(fday, "%3d %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f",
					jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs, WindSpeed, Humidity);

#ifdef HYDRO//===Write max half hour rainfall; dengjia===
				fprintf(fday, "%8.2f", MuslemaxRain);
#endif
                fprintf(fday,"\n");			
				MonAveT[j] += temp / Mday[j];
				YrAveT += (temp / 365.0);
				YrRain += Rainfall*10.0; //cm -> mm				
			}
		}
		fclose (fpii);
		fclose (fday);
		//fclose (fpi0);
        
		// create file clim.yr 
		if(C_FarmFile==1) C_BaseCO2 = RY_AtmoCO2[yr];

		sprintf(fname,"%s\\Inputs\\clim_%d.yr", OUTPUT, YR);
		fpo=fopen(fname,"w");

		for (j=1;j<=12;j++) fprintf(fpo,"%.2f  ", MonAveT[j]);
		
		fprintf(fpo,"\n%8.2f\n", YrAveT);
		fprintf(fpo,"%8.2f\n", YrRain);
		fprintf(fpo,"%8.3f\n", RainN);
		fprintf(fpo,"%8.2f\n", air_NH3);
		fprintf(fpo,"%8.2f\n", C_BaseCO2);
		fprintf(fpo,"%8.2f\n", C_CO2IncreaseRate);
		fclose (fpo);

		//*yr_temp=YrAveT;
		//*yr_prec=YrRain;

		///Convert dates for southern hemisphere
		if(r_latitude<0.0&&GlobeData==1)
		{
			float wtemp[366], wmaxT[366], wminT[366], wRainfall[366], wsolrad[366], wDay_Hrs[366], wHumidity[366], wwind_speed[366];
			int i;

			sprintf(Dname,"%s\\Inputs\\clim_%d.day", OUTPUT, YR);
			fday=fopen(Dname,"r");
			if (fday==NULL) 
			{
				AfxMessageBox("Can not open file clim.day");
				exit(0);
			}

			for(i=1; i<=365; i++)
			{
				fscanf(fday, "%d %f %f %f %f %f %f %f %f",
					&jday, &wtemp[i], &wmaxT[i], &wminT[i], &wRainfall[i], &wsolrad[i], &wDay_Hrs[i], &wwind_speed[i], &wHumidity[i]);
					
			}
			fclose (fday);

			sprintf(Dname,"%s\\Inputs\\clim_%d.day", OUTPUT, YR);
			fday=fopen(Dname,"w");
			if (fday==NULL) 
			{
				AfxMessageBox("Can not create file clim.day");
				exit(0);
			}

			for(i=183; i<=365; i++)
			{
				fprintf(fday, "%3d %8.2f  %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n",
					i-182, wtemp[i], wmaxT[i], wminT[i], wRainfall[i], wsolrad[i], wDay_Hrs[i], wwind_speed[i], wHumidity[i]);
			}

			for(i=1; i<=182; i++)
			{
				fprintf(fday, "%3d %8.2f  %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n",
					i+183, wtemp[i], wmaxT[i], wminT[i], wRainfall[i], wsolrad[i], wDay_Hrs[i], wwind_speed[i], wHumidity[i]);
			}
			fclose (fday);
		}
	}	
	}

	return(miss_clim);
}

void region_livestock_files(int LOS, char *Live_ID, int *BarnType, int *BarnFloorType,
					int *BarnBedMaterial, int *BarnVentType, float *BarnHeads, float *BarnFeedRate,
					float *BarnCP,float *BarnFloorArea,float *BarnBedRate,float *BarnBedCN,
					float *BarnBedFrequency,float *BarnRemoveFrequency, float *BarnToCompost,
					float *BarnToLagoon, float *BarnToDigester,	int *PenType, int *PenFloorType,
					int *PenBedMaterial, int *PenVentType,float *PenHeads, float *PenFeedRate, 
					float *PenCP, float *PenFloorArea, float *PenBedRate, float *PenBedCN, 
					float *PenBedFrequency, float *PenRemoveFrequency, float *PenToCompost, 
					float *PenToLagoon, float *PenToDigester, float *ComDensity, int *ComCover, int *ComRemoveTimes, 
					float *ComLitterRate, float *ComLitterCN, float ComToField[100][10], float ComDToMarket[100][10], 
					float ComRemain[100][10], float *LagCapacity, float *LagArea, int *LagDrainTimes, 
					float LagToField[100][30], float LagToMarket[100][30], float LagRemain[100][30], int *LagCover, int *DigTemp,
					float *DigRetentionDays, float *DigToField, float *DigToMarket, float *FieldArea,
					float *BarnTP, float *PenTP, int *FlashType, int LagDrainMonth[100][30], int LagDrainDay[100][30],
					float *DigToRemain, int ComRemoveMonth[100][10], int ComRemoveDay[100][10], float *FlushWater)
{
	//House
	CString SF;
	FILE* sf;

	SF.Format("%s\\Inputs\\ManureHouse_1_1.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d\n", 0);  
	fprintf(sf, "%d\n", 1);
	fprintf(sf, "%d  %f  %f  %f %f\n", BarnType[LOS], BarnHeads[LOS], BarnFeedRate[LOS], BarnCP[LOS], BarnTP[LOS]);	
	fprintf(sf, "%f  %d\n", BarnFloorArea[LOS], BarnFloorType[LOS]);//0 slatted floor; 1 conrete floor
	fprintf(sf, "%d  %f  %f  %f\n", BarnBedMaterial[LOS], BarnBedCN[LOS], BarnBedFrequency[LOS], BarnBedRate[LOS]);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
	fprintf(sf, "%d  %f  %s\n", BarnVentType[LOS], 0.0, "None");// 0 natural, 1 fan, -1 IndoorClimateFile
	fprintf(sf, "%f\n", BarnRemoveFrequency[LOS]);
	fprintf(sf, "%f %f %f %f\n", BarnToCompost[LOS], BarnToLagoon[LOS], BarnToDigester[LOS], 0.0);
	fprintf(sf, "%f %f %f %f\n", BarnToCompost[LOS], BarnToLagoon[LOS], BarnToDigester[LOS], 0.0);
	fprintf(sf, "%d %f\n", FlashType, FlushWater);

	fclose(sf);

/*	SF.Format("%s\\Inputs\\ManurePen.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d\n", 0);  
	fprintf(sf, "%d\n", 1);
	fprintf(sf, "%d  %f  %f  %f %f\n", PenType[LOS], PenHeads[LOS], PenFeedRate[LOS], PenCP[LOS], PenTP[LOS]);
		
	fprintf(sf, "%f  %d\n", PenFloorArea[LOS], PenFloorType[LOS]);//0 slatted floor; 1 conrete floor
	fprintf(sf, "%d  %f  %f  %f\n", PenBedMaterial[LOS], PenBedCN[LOS], PenBedFrequency[LOS], PenBedRate[LOS]);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
	fprintf(sf, "%f\n", PenRemoveFrequency[LOS]);
	fprintf(sf, "%f %f %f %f\n", PenToCompost[LOS], PenToLagoon[LOS], PenToDigester[LOS], 0.0);
	fprintf(sf, "%f %f %f %f\n", PenToCompost[LOS], PenToLagoon[LOS], PenToDigester[LOS], 0.0);
	fprintf(sf, "%d\n", FlashType);
	fclose(sf);
*/
	SF.Format("%s\\Inputs\\ManureGraze.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	
	fprintf(sf, "%d\n", 0);  
	fprintf(sf, "%d  %d\n", 0, 0);//Type: 1 dairy, 2 beef, 3 veal, 4 swine, 5 sheep, 6 poultry 
	for(int i=1; i<0; i++)
	{
		fprintf(sf, "%d  %d  %d  %d  %f  %f\n", 0, 0, 0, 0, 0.0, 0.0); 
	}
	fprintf(sf, "%f\n", 0.0); 
	fclose(sf);

	SF.Format("%s\\Inputs\\ManureCompost.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	fprintf(sf, "%f  %d  %d  %f  %f\n", ComDensity[LOS], ComCover[LOS], ComRemoveTimes[LOS], ComLitterRate[LOS], ComLitterCN[LOS]);  
	for(int i=1;i<=ComRemoveTimes[LOS];i++)
	{
		fprintf(sf, "%d %d %f %f %f\n", ComRemoveMonth[LOS][i], ComRemoveDay[LOS][i], ComToField[LOS][i], ComDToMarket[LOS][i], ComRemain[LOS][i]);
	}
	fclose(sf);

	SF.Format("%s\\Inputs\\ManureLagoon.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	fprintf(sf, "%f  %f  %d  %d  %d\n", LagCapacity[LOS], LagArea[LOS], LagCover[LOS], 0, LagDrainTimes[LOS]); 
	for(int i=1; i<=LagDrainTimes[LOS]; i++)
	{
		fprintf(sf, "%d  %d  %f  %f  %f\n", LagDrainMonth[LOS][i], LagDrainDay[LOS][i], LagToField[LOS][i], LagToMarket[LOS][i], LagRemain[LOS][i]);
	}
	fclose(sf);

	SF.Format("%s\\Inputs\\ManureDigester.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
		
	fprintf(sf, "%d  %f  %f\n", DigTemp[LOS], 0.0, DigRetentionDays[LOS]);  
	fprintf(sf, "%f  %f  %f\n", DigToField[LOS], DigToMarket[LOS], DigToRemain[LOS]);
	fclose(sf);

	SF.Format("%s\\Inputs\\ManureField.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
		
	fprintf(sf, "%f", FieldArea[LOS]);    
	fclose(sf);


}

void MakeDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, float lat,
							int IfCheck, float NO3NH4_Rainfall,float NH3_Atmosphere,float BaseCO2,
							float CO2IncreaseRate, int YieldSite, int YieldYear, int YieldToday,
							char *climfile_ID, int DMW, int DryYear, int MidYear, int WetYear, char *r_Country)//change int IfCheck from CString IfCheck
{
	int tn, j, k;
	float Day_Hrs,temp=0.0,Rainfall=0.0,maxT=0.0,minT=0.0,solrad,wind_speed=2.0;
	float AveMonthT[13],AveYrT, TotalYrRain, humidity=30.0, CloudIndex=1.0;
	int   jday=0,jday0=0,Aday;
	char fname[256],cn[256], cjunk[200], junkcc[300], ch[256];
	char CurrentClim[300], junkc[200];
	
	FILE* fpo, *fpi, *fcc;
	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,Dname);
	fpo=sopen(fname,"w");
	if(fpo==NULL) note(1,fname);
        
	if(UseID==0)
	{
		fpi=sopen(Pname,"r");
		if (fpi==NULL) 
		{
			CString NCF;
			NCF.Format("%s.txt", Pname);
			fpi=fopen(NCF,"r");
			if (fpi==NULL) note(0, Pname);
		}   
		if (ClimateFileType!=4) 
		fscanf(fpi,"%s", cjunk);	// read climate file dataname
		if(strcmp(cjunk, "1")==0)
		{
			fclose(fpi);
			fpi=sopen(Pname,"r");
		} 
	}
	else if(UseID==10)
	{
		if(DMW==0)//year 1
		{
			sprintf(Pname, "%s\\Database\\%s\\lib_clim\\%d\\%s", ROOTDIR, r_Country, YieldYear-1, climfile_ID);//, YieldYear-1);
		}
		else if(DMW==1)//dry year 2
		{
			sprintf(Pname, "%s\\Database\\%s\\lib_clim\\%d\\%s", ROOTDIR, r_Country, DryYear, climfile_ID);//, DryYear);
		}
		else if(DMW==2)//medium year 2
		{
			sprintf(Pname, "%s\\Database\\%s\\lib_clim\\%d\\%s", ROOTDIR, r_Country, MidYear, climfile_ID);//, MidYear);
		}
		else//wet year 2
		{
			sprintf(Pname, "%s\\Database\\%s\\lib_clim\\%d\\%s", ROOTDIR, r_Country, WetYear, climfile_ID);//, WetYear);
		}

		fpi=sopen(Pname,"r");
		if (fpi==NULL) note(0, Pname);
		 
		char www[200];
		fgets(www, 200, fpi);
///		fgets(www, 200, fpi);  //chenhan
		
		/*if (ClimateFileType!=4) 
		{
			fscanf(fpi,"%s", cjunk);	// read climate file dataname
			if(strcmp(cjunk, "1")==0)
			{
				fclose(fpi);
				fpi=sopen(Pname,"r");
			} 
		}*/

		//climate of year 2
		if(DMW>0)
		{
			//actual climate data for year 2
			sprintf(CurrentClim, "%s\\Database\\%s\\lib_clim\\%d\\%s", ROOTDIR, r_Country, YieldYear, climfile_ID);//, YieldYear);
			fcc=fopen(CurrentClim, "r");
			if(fcc==NULL) note(0, CurrentClim);
			fgets(www, 200, fcc);
			//fgets(www, 200, fcc);//chenhan
			
			/*fscanf(fcc,"%s", cjunk);
			if(strcmp(cjunk, "1")==0)
			{
				fclose(fcc);
				fcc=sopen(Pname,"r");
			} */
		}
	}    
    
	tn = 0;
    AveYrT = 0.0;
	TotalYrRain = 0.0;
	int Mday[13]={0,0};
	Mday[2] = 28;
    Mday[4] = Mday[6] = Mday[9] = Mday[11] = 30;
    Mday[1] = Mday[3] = Mday[5] = Mday[7] = Mday[8] = Mday[10] = Mday[12] = 31;

	//default data
	wind_speed = 2.0;//m/s
	humidity = 60.0;//%
	int djunk, djunk2;
	char www[100];

	for (j=1;j<=12;j++) 
	{
		AveMonthT[j] = 0;
        for (k = 1;k<=Mday[j];k++) 
		{	
			int dflag=0, dflag2=0;

			if(j==1&&k==1)
			{
				fscanf(fpi,"%d", &djunk);	// read climate file dataname
				if(djunk!=1)
				{
					fgets(www, 300, fpi);
					dflag=0;
				} 
				else
				{
					jday = djunk;
					dflag = 1;
				}

				if(DMW>0)
				{
					fscanf(fcc,"%d", &djunk2);	// read climate file dataname
					if(djunk2!=1)
					{
						fgets(www, 300, fcc);
						dflag=0;
					} 
					else
					{
						jday = djunk2;
						dflag = 1;
					}
				}
			}

			tn++;
			Day_Hrs = 0.0;

			if(lat<0.0)
			{
				Aday = tn - 182;//for southern semisphere
				if(Aday<=0) Aday = 365 + Aday;

				solrad = day_par(Aday, -lat, &Day_Hrs);
			}
			else
				solrad = day_par(tn, lat, &Day_Hrs);//extre-terrestrial radiation, MJ/m2/day

			if(Day_Hrs<=0.0) Day_Hrs=0.01;

			if (ClimateFileType ==0) //aveT, prec
				{
					if(dflag==1) fscanf(fpi, "%f %f", &temp, &Rainfall);
					else fscanf(fpi, "%d %f %f", &jday, &temp, &Rainfall);
					fgets(junkcc, 200, fpi);
					maxT = temp + (float)4.5;
					minT = temp - (float)4.5;
					
				}
				else if (ClimateFileType ==1) //maxT, minT, prec
				{
					if(dflag==1) fscanf(fpi, "%f %f %f", &maxT, &minT, &Rainfall);
					else fscanf(fpi, "%d %f %f %f", &jday, &maxT, &minT, &Rainfall);
					
					if(UseID==10&&DMW>0&&YieldToday>=jday)//read actual climate data for yr 2
					{
						if(dflag==1) fscanf(fcc, "%f %f %f", &maxT, &minT, &Rainfall);
						else fscanf(fcc, "%d %f %f %f", &jday, &maxT, &minT, &Rainfall);
					}

					fgets(junkcc, 200, fpi);
					temp = (maxT + minT) * 0.5;
			
					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}
				else if (ClimateFileType ==2) //maxT, minT, prec, radiation
				{					
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &solrad);
					else fscanf(fpi, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &solrad);
					fgets(junkcc, 200, fpi);
					temp =float( (maxT + minT) *0.5);
				}
				else if (ClimateFileType ==3) //maxT, minT, prec, wind speed (m/s)
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &wind_speed);
					else fscanf(fpi, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &wind_speed);//wind speed, m/second
					temp =float( (maxT + minT) *0.5);

					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;

				}
				if(ClimateFileType ==4)
				{					
					int yr_ID, month_ID, day_ID;
					float radiation, ave_T;
					char polygon_ID[100];

					fscanf(fpi, "%s %d %d %d %f %f %f %f %f", 
							polygon_ID, &yr_ID, &month_ID, &day_ID, &radiation, &maxT, &minT, &ave_T, &Rainfall);
					fgets(junkc, 200, fpi);
					temp =float( (maxT + minT) *0.5);
					Rainfall *= 0.1;
					jday = tn;

					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}
				else if(ClimateFileType==5) //maxT, minT, prec, wind speed, radiation, relative humidity
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f %f %f", &maxT, &minT, &Rainfall, &wind_speed, &solrad, &humidity);
					else fscanf(fpi, "%d %f %f %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &wind_speed, &solrad, &humidity);//wind speed, m/second
					temp =float( (maxT + minT) *0.5);
				}
				else if(ClimateFileType==6) //maxT, minT, prec, wind speed, relative humidity
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f %f", &maxT, &minT, &Rainfall, &wind_speed, &humidity);
					else fscanf(fpi, "%d %f %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &wind_speed, &humidity);
					temp =float( (maxT + minT) *0.5);

					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}
				else if(ClimateFileType==7) //maxT, minT, prec, relative humidity
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &humidity);
					else fscanf(fpi, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &humidity);
					temp =float( (maxT + minT) *0.5);

					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}

			if(tn!=jday)
			{
				CString note;
				note.Format("Error at day %d in climate data file %s", tn, Pname);
				AfxMessageBox(note);
				exit(0);
			}

		//	if (IfCheck=="Check")
			{

			// Check whether or not if Julian day is continous
				if (tn > 1) {
					if (jday0 != jday - 1) {
						sprintf(ch,"Julian day of %dth line of <%s>",tn,fname);
						MessageBox(NULL,ch,"Climate Data Error:",0);
						fclose (fpi); fclose (fpo);
						goto outerr;
					}
				}
					
				// Check if rainfall is bigger than 0
				if (Rainfall < 0.0) {
					sprintf(ch,"Rainfall in %dth line of <%s>",tn,fname);
					MessageBox(NULL,ch,"Climate Data Error:",0);
					fclose (fpi); fclose (fpo);

					goto outerr;
				}
            
				// check if  -50<T<70
				if (temp < -50.0 || temp > 70.0) {
					sprintf(ch,"Temperature in %dth line of <%s>",tn,fname);
					MessageBox(NULL,ch,"Climate Data Error:",0);
					fclose (fpi); fclose (fpo);

					goto outerr;
				}
			}
            jday0 = jday;
			//if (tn==1)//(mode==0) 
			//{
			//	IData.Soil_T = temp;
			//}

			// Output climate data of 365 days
			
			fprintf(fpo, "%3d %5.2f  %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f\n",
					jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs, wind_speed, humidity);

			//if (ClimateFileType ==3)
			//{
			//	fprintf(fpo, "%3d %5.2f  %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f\n",
			//		jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs, wind_speed);
			//}
			//else
			//{
			//	fprintf(fpo, "%3d %5.2f  %5.2f %5.2f %5.2f %5.2f %5.2f\n",
			//		jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs);
			//}
                
            // Calculate the average T and rainfall for month, year
            AveMonthT[j] += temp / Mday[j];
            AveYrT += (temp / 365.0);
            TotalYrRain += Rainfall;
		}
	}
    fclose (fpi);
    fclose (fpo);
	if(DMW>0) fclose (fcc);

	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,Yname);
	fpo=sopen(fname,"w");
	if (fpo==NULL) note(1, fname);
    for (j=1;j<=12;j++) 
	{
		fprintf(fpo,"%.2f	", AveMonthT[j]);
	}
    fprintf(fpo,"\n%.2f\n", AveYrT);
    fprintf(fpo,"%.2f\n", TotalYrRain);
    fprintf(fpo,"%.3f\n", NO3NH4_Rainfall);//IData.
    fprintf(fpo,"%.2f\n", NH3_Atmosphere);//IData.
	fprintf(fpo,"%.2f\n", BaseCO2);//IData.
	fprintf(fpo,"%.2f\n", CO2IncreaseRate);
	fprintf(fpo,"%d\n", ClimateFileType);
    fclose (fpo);
	
outerr:;
    
}