#include "stdafx.h"
#include "Dndcgo.h"
#include "RunPaths.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "CreateInputFile.h"
#include <io.h>
#include <direct.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float day_par2(int Jday, float LATITUDE, float* Day_Hrs);
int JulianDay(int month, int day);
int FileCopy_1(char *source, char *dest);

float nnSoca[6]={0.0,0.2,0.2,0.08,0.05,0.2};
float nnSocb[6]={10.0,2.0,2.0,1.4,4.0,2.0};
int MonthDay[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

NewCropofEachYear CYr[2];

////////////////////////////////////////////////////////////////////////////////////////////
char  notes[255],tmp[255],ffname[300], sitename[200], r_Country[200]="NULL";
char  ClimateFilename[300][200]={NULL,NULL};
char  SoilName[100], NameNote[100], m_ProfileName[250];
char  fname[356],Pname[356],cn[356], FCT0[300], FCT100[300];
int   Soil_Texture, Soil_landuse, SoilRetardation, UseION, PerennialCrop, Idc, Q;
int	  m_SPlayers, m_SPso[11], layer[11], SCSuse, cropn, years, ifdaily;
int	  ClimateFileType, ClimateFileNumber, if1File, UseID=0;
float NO3NH4_Rainfall, NH3_Atmosphere, BaseCO2, CO2IncreaseRate;
float Soil_Density, Soil_pH, Flood_pH, Soil_OCatSurface, Soil_Clay;
float Soil_BypassFlow, Soil_Litter, Soil_humads, Soil_humus, PassiveC, PassiveCCN;
float Soil_NO3, Soil_NH4, Soil_moiture, Soil_T;
float LateralInflux, Soil_MicrobioIndex, Soil_WaterObstructLayer, slope, Soil_Quality;
float HighestWT, Soil_Porosity, DClitter, DChumads, DChumus, HumadCN, HumusCN;
float WaterPool, H, Topr, Toph, CEC, TH, m, V, Qstar, AcWater, SurfWater, SnowPack;
float BypassF, Sks, Fldcap, Wiltpt, Psisat, Beta, m_SPthickness;	
//float m_SPth[11], m_SPd[11], m_SPsoc[11], m_SPph[11], m_SPfc[11], m_SPwp[11], m_SPpo[11], m_SPhy[11], m_SPc[11];
float SOCa, nSoca[10], SOCb, nSocb[10], latitude;
int   Mday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

float Day_Hrs,temp=0.0,Rainfall=0.0,maxT=0.0,minT=0.0,solrad,wind_speed=2.0;
float AveMonthT[13],AveYrT, TotalYrRain, humidity=30.0, CloudIndex=1.0;
int   jday=0,jday0=0,Aday, TotalManureCropss;


////////////////////////////////////////////////////////////////////////////////////////////////
void CreateBlankFiles(void);
void ReadInputDatafromDND(char *InputFileName);
void CreateInputFiles(int DaymetFlag, int UseID, char *r_Country, char *BatchPass);
////////////////////////////////////////////////////////////////////////////////////////////////

void SaveClimateFileOfAYear(int id,char *ch, float lat, int ClimateFileType, float NO3NH4_Rainfall,
float NH3_Atmosphere, float BaseCO2, int mode, float CO2IncreaseRate, int UseID, char *r_Country);
void CreateDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, float lat,
							float NO3NH4_Rainfall,float NH3_Atmosphere,float BaseCO2,
							float CO2IncreaseRate, char *LocaName, int YieldYear, int YieldToday,
							int DMW, char *r_Country);
void ReadCropPara_2(int* v_CropID, char v_CropName[95][100], float* v_max_biomass_C, float* v_grain_fraction, float* v_leaf_fraction,
	float* v_leafstem_fraction, float* v_root_fraction, float* v_GrainCN,
	float* v_LeafCN, float* v_ShootCN, float* v_RootCN, float* v_WaterDemand, float* v_OptimumT,
	float* v_TDD, float* v_Nfixation, float* v_Vascularity, int* v_Perennial, float* v_TreeAge, float* v_Root1, float* v_Root2,
	float* v_VE, float* v_V1, float* v_VT, float* v_R1, float* v_R3, float* v_R5, float* v_R7, float* v_R8, float* v_PVE, float* v_PV1, float* v_PVT, float* v_PR1, float* v_PR3, float* v_PR5, float* v_PR7, float* v_PR8,
	float* v_Kext1, float* v_Kext2, float* v_cropHeight);
/////////////////////////////////////////////////////////////////////////////////////////////
void SaveSite(void);
void RecordClimateFile(int mode, int DaymetFlag, int UseID, char *r_Country);
int SaveSoilParas(int id);
int SaveInterFarmParas(void);
int SaveCropParas(char *BatchPass);
void RecordManureFiles(void);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void CreateDndcInputFiles(char *InputFileName, char *BatchPass)
{
	//Create blank files
	CreateBlankFiles();

	//Read in DND file
	ReadInputDatafromDND(InputFileName);

	//Create input files
	CreateInputFiles(0, UseID, r_Country, BatchPass);
	
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void CreateBlankFiles(void)
{
	int i;
	char SF[200], MP[200];
	FILE* sf, *mp;

#ifdef MANURE
	for(int m_FeedlotYear=0; m_FeedlotYear<=10; m_FeedlotYear++)
	{
		for(i=0; i<=10; i++)
		{
			sprintf(SF, "%s\\ManureHouse_%d_%d.txt", INTER, m_FeedlotYear, i);
			sf=fopen(SF, "w");
			if(sf==NULL) note(1, SF);
			
			fprintf(sf, "%d  %d\n", 0, 1);  
			fprintf(sf, "%3d  %8.2f  %8.2f  %8.4f  %8.4f\n", 0, 0.0, 0.0, 0.0, 0.0);	
			fprintf(sf, "%f  %d\n", 0.0, 0);//0 slatted floor; 1 conrete floor
			fprintf(sf, "%d  %f  %d  %f\n", 0, 0.0, 0, 0.0);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			fprintf(sf, "%d  %f  %s\n", 0, 0.0, "None");// 0 natural, 1 fan
			fprintf(sf, "%f\n", 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%d\n", -1);

			fclose(sf);
		}

		char TotalFeedlots[200];
		FILE *TFL;
		sprintf(TotalFeedlots, "%s\\TotalFeedLots_%d", INTER, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", 1);
		fclose(TFL);
	}

	sprintf(SF, "%s\\ManureGraze.txt", INTER);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d  %d  %d  %f\n", 0, 8, 0, 0.0);  
	
	fclose(sf);

	sprintf(SF, "%s\\ManureLagoon.txt", INTER);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %f  %d  %d  %d\n", 0.0, 0.0, 0, 0, 0);  
	fprintf(sf, "%d %d %f  %f  %f\n", 0, 0, 0.0, 0.0, 0.0); 
	fclose(sf);

	sprintf(SF, "%s\\ManureCompost.txt", INTER);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %d  %d  %f  %f\n", 0.0, 0, 0, 0.0, 0.0);  
	//fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);

	sprintf(SF, "%s\\ManureDigester.txt", INTER);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d  %f  %f\n", 0, 0.0, 0.0);    
	fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);

	sprintf(SF, "%s\\ManureField.txt", INTER);
	sf=fopen(SF, "w");

	if(sf==NULL) note(1, SF);
	fprintf(sf, "%f", 0.0);    
	fclose(sf);

	char XFF[200];
	FILE *xff;
/*	XFF.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);		
	xff=fopen(XFF, "w");
	fprintf(xff, "%d\n", 0);
	fclose(xff);*/

	sprintf(XFF, "%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", 0, 0, 0);
	fclose(xff);
#endif

	FILE *db;
	char DCB[200];
	for(int k=1; k<=10; k++)
	{
		sprintf(DCB, "%s_1\\CropRotation_%d.txt", INTERMANAGE, k);
		db=fopen(DCB, "w");
		if(db==NULL) note(1,DCB);
		fprintf(db, "%d %d %d", k, 1, 1);
		fclose(db);
	}

	sprintf(DCB, "%s\\SPAN", INPUTS);
	db=fopen(DCB, "w");
	if (db==NULL) note(1, DCB);
	fprintf(db, "%d\n", 1);
	fclose(db);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void ReadInputDatafromDND(char *InputFileName)
{
	int  i, j, k;
	int floon, ShallowFlood, WaterControl, FlooMonth1, FlooDay1, FlooMonth2, FlooDay2;
	float FlooN, WaterGetherIndex, WaterLeakRate;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex,m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	float FloodWaterN;
	
    FILE *fp;

	sprintf(ffname, "%s", InputFileName);

	fp=fopen(ffname, "r");
	if(fp==NULL) note(0, ffname);	

	fscanf(fp,"%s", notes);	//"Input_Parameters:" 
	fscanf(fp,"%s",notes); //"--------------------"
	fscanf(fp,"%s",notes); //"Site_info:"
	fscanf(fp,"%s",notes); //"Site_name:"
	fscanf(fp,"%s",sitename);
	fscanf(fp,"%s %d",notes, &years); //"Simulated_Year:"
	fscanf(fp,"%s", notes); //"Latitude:"
	fscanf(fp, "%f", &latitude);
	fscanf(fp,"%s %d", notes, &ifdaily); //"Daily_Record:"*/

	int US;
	fscanf(fp, "%s %d", notes, &US);

	if (US == 0 || US == 1) US = US;
	else US = 0;

	/*
	char LB1[200];
	FILE* ddb1;
	sprintf(LB1, "%s\\Inter\\UnitSystem", OUTPUT);
	ddb1 = fopen(LB1, "w");
	if (ddb1 == NULL) note(1, LB1);
	fprintf(ddb1, "%d", US);
	fclose(ddb1);
	*/

#ifdef MANURE

	int HouseInputFormat, AnimalTypes, AnimalType[10];
	char HouseInputFileName[200], IndoorClimateFile[300];
	float AnimalHeads[10],FeedRate[10],FeedProtein[10],FeedTP[10];
	float m_FloorArea,m_BedCN, m_VentRate, m_BedRate, m_BedFrequency,PenBedFrequency;
	int m_FloorSurface, m_BedType, m_Ventilation;
	int PenInputFormat, PenAnimalTypes, PenAnimalType[15],PenSurface,PenBedMaterial; 
	char PenInputFileName[200];
	float PenAnimalHeads[15],PenFeedRate[15],PenFeedProtein[15],PenFeedTP[15],PenArea,PenBedCN,PenBedAmount;
	int GrazeInputFormat, GrazeAnimalType, GrazeTimes, IniMonth[366],IniDay[366],EndMonth[366],EndDay[366];
	char GrazeInputFileName[200];
	float GrazeAnimalHeads[366],GrazeAnimalHrs[366], GrazeArea;
	float m_LagoonCapacity, m_LagoonSurfaceArea, LagoonToField[30], LagoonToMarket[30], LagoonRemain[30];
	int m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes, LagoonDrainMonth[30], LagoonDrainDay[30];
	float m_CompostDensity, m_LitterAmount, m_LitterCN, CompostToField, CompostToMarket, CompostRemain;
	float m_DigesterCapacity,m_DigesterCH4,m_DigesterDays, DigesterToField;
	int m_Temp, m_Flash, HouseID, m_CompostCover, m_CompostRemoveTimes, CompostRemoveMonth, CompostRemoveDay;
	float DigesterToMarket, DigesterRemain;
	float HouseManureOutDays,m_UC, m_UL, m_UD, m_UF, m_UR, m_FC, m_FL, m_FD, m_FF, m_FR;
	float PenManureOutDays, PenUC, PenUL,PenUD,PenUR,PenFC, PenFL,PenFD,PenFR;
	float GrazeManureOutDays, GrazeUF, GrazeUR, GrazeFF, GrazeFR, FieldArea, jf;
	
	char MP[200], SF[200];
	FILE *mp, *sf;

	int m_FeedLots, m_FeedlotYears, NutritionModelX;

	fscanf(fp,"%s", notes);//--------------------------------------
	fscanf(fp,"%s", notes);//Livestock_data:
	fscanf(fp,"%s %d",notes, &m_FeedlotYears);//SimulatedYears

	for(int m_FeedlotYear=1; m_FeedlotYear<=m_FeedlotYears; m_FeedlotYear++)
	{
		fscanf(fp,"%s %d",notes, &m_FeedLots);//TotalFeedlots
	
		char TotalFeedlots[50];
		FILE *TFL;
		sprintf(TotalFeedlots, "%s\\TotalFeedLots_%d", INTER, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", m_FeedLots);
		fclose(TFL);

		for(int i=1; i<=m_FeedLots; i++)
		{
			fscanf(fp,"%s %d",notes,&HouseID);//Feedlot
			fscanf(fp,"%s %d",notes,&HouseInputFormat);//FeedlotInputFormat
						
			if(HouseInputFormat==1||HouseInputFormat==2)
				fscanf(fp,"%s %s",notes,HouseInputFileName);
			else if(HouseInputFormat==3)
				fscanf(fp,"%s %d",notes,&NutritionModelX);
			else
			{
				fscanf(fp,"%s %d",notes,&AnimalTypes);//LivestockType
				fscanf(fp,"%s %d",notes,&AnimalType[1]);//LivestockType_ID
				fscanf(fp,"%s %f",notes,&AnimalHeads[1]);//Herd_heads
				fscanf(fp,"%s",notes);//feed
				fscanf(fp,"%s %f",notes,&FeedRate[1]);//Rate
				fscanf(fp,"%s %f",notes,&FeedProtein[1]);//CrudeProtein_percent
				fscanf(fp,"%s %f",notes,&FeedTP[1]);//Phosphorus_percent			
			}
			fscanf(fp,"%s",notes);//floor
			fscanf(fp,"%s %f",notes,&m_FloorArea);//SurfaceArea
			fscanf(fp,"%s %d",notes,&m_FloorSurface);//SurfaceType
			fscanf(fp,"%s",notes);//Bedding			
			fscanf(fp,"%s %d",notes,&m_BedType);//MaterialType
			fscanf(fp,"%s %f",notes,&m_BedCN);//Material_C/N
			fscanf(fp,"%s %f",notes,&m_BedFrequency);//ApplyFrequency
			fscanf(fp,"%s %f",notes,&m_BedRate);//Amount
			fscanf(fp,"%s",notes);//ventilation			
			fscanf(fp,"%s %d",notes,&m_Ventilation);//Type
			fscanf(fp,"%s %f",notes,&m_VentRate);//Ven_rate
			fscanf(fp,"%s %s",notes,IndoorClimateFile);//IndoorClimateFile	
			fscanf(fp,"%s",notes);//ManureRemoval:			
			fscanf(fp,"%s %f", notes, &HouseManureOutDays);//Frequency
			fscanf(fp,"%s %f", notes, &m_UC);//Liquid_to_compost
			fscanf(fp,"%s %f", notes, &m_UL);//Liquid_to_lagoon	
			fscanf(fp,"%s %f", notes, &m_UD);//Liquid_to_digester
			fscanf(fp,"%s %f", notes, &m_UF);//Liquid_to_field
			fscanf(fp,"%s %f", notes, &m_UR);//Liquid_remain			
			fscanf(fp,"%s %f", notes, &m_FC);//Solid_to_compost	
			fscanf(fp,"%s %f", notes, &m_FL);//Solid_to_lagoon	
			fscanf(fp,"%s %f", notes, &m_FD);//Solid_to_digester	
			fscanf(fp,"%s %f", notes, &m_FF);//Solid_to_field
			fscanf(fp,"%s %f", notes, &m_FR);//Solid_remain 
			fscanf(fp,"%s", notes);//flushing
			fscanf(fp,"%s %d", notes, &m_Flash);

			sprintf(SF, "%s\\ManureHouse_%d_%d.txt", INTER, m_FeedlotYear, i);//FlushingLiquidType
			sf=fopen(SF, "w");
			fprintf(sf, "%d\n", HouseInputFormat);  

			if(HouseInputFormat==1||HouseInputFormat==2)//use a input file name
				fprintf(sf, "%s\n", HouseInputFileName);
			else if(HouseInputFormat==3)				//use nutrition model
				fprintf(sf, "%d\n", NutritionModelX);
			else										//use average input data
			{
				//Type: 1 dairy, 2 beef, 3 veal, 4 swine, 5 sheep, 6 goat, 7 horse, 8 layer, 9 brolier, 10 turkey, 11 duck
				fprintf(sf, "%d\n", AnimalTypes);
				//for(int j=1; j<=AnimalTypes; j++)
				fprintf(sf, "%3d  %8.2f  %8.2f  %8.4f  %8.4f\n", AnimalType[1], AnimalHeads[1], FeedRate[1], FeedProtein[1], FeedTP[1]);
			}
					
			fprintf(sf, "%f  %d\n", m_FloorArea, m_FloorSurface);//0 slatted floor; 1 conrete floor	
			fprintf(sf, "%d  %f  %f  %f\n", m_BedType, m_BedCN, m_BedFrequency, m_BedRate);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			fprintf(sf, "%d  %f  %s\n", m_Ventilation, m_VentRate, IndoorClimateFile);// 0 natural, 1 fan, -1 IndoorClimateFile
			fprintf(sf, "%f\n", HouseManureOutDays);
			fprintf(sf, "%f %f %f %f %f\n", m_UC, m_UL, m_UD, m_UF, m_UR);
			fprintf(sf, "%f %f %f %f %f\n", m_FC, m_FL, m_FD, m_FF, m_FR);
			fprintf(sf, "%d\n", m_Flash);
			fclose(sf);
		}//end of feedlots loop
	}//end of year loop
	
	fscanf(fp,"%s", notes);//lagoon
	fscanf(fp,"%s %f",notes, &m_LagoonCapacity);//Capacity
	fscanf(fp,"%s %f",notes, &m_LagoonSurfaceArea);//SurfaceArea	
	fscanf(fp,"%s %d",notes, &m_LagoonCover);//Coverage
	fscanf(fp,"%s %d",notes, &m_LagoonRain);//RainfallReceival

	fscanf(fp,"%s",notes);//SlurryRemovalTimes	
	fscanf(fp,"%d",&m_LagoonDrainTimes);
	{
	for(int i=1; i<=m_LagoonDrainTimes; i++)
	{
		fscanf(fp,"%s %d",notes, &LagoonDrainMonth[i]);//Slurry_drain_month
		fscanf(fp,"%s %d",notes, &LagoonDrainDay[i]);//Slurry_drain_day
		fscanf(fp,"%s %f",notes, &LagoonToField[i]);//Slurry_to_field
		fscanf(fp,"%s %f",notes, &LagoonToMarket[i]);//Slurry_to_digester
		fscanf(fp,"%s %f",notes, &LagoonRemain[i]);//Slurry_remain
	}
	}
	
	sprintf(SF, "%s\\ManureLagoon.txt", INTER);
	sf=fopen(SF, "w");
	fprintf(sf, "%f  %f  %d  %d  %d\n", m_LagoonCapacity, m_LagoonSurfaceArea, m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes); 
	{
	for(int i=1; i<=m_LagoonDrainTimes; i++)
	{
		fprintf(sf, "%d  %d  %f  %f  %f\n", LagoonDrainMonth[i], LagoonDrainDay[i], LagoonToField[i], LagoonToMarket[i], LagoonRemain[i]);
	}
	}
	fclose(sf);
	
	fscanf(fp,"%s", notes);//compost
	fscanf(fp,"%s %f",notes,&m_CompostDensity);//Porosity
	fscanf(fp,"%s %d",notes,&m_CompostCover);//Coverage	
	fscanf(fp,"%s %d",notes,&m_CompostRemoveTimes);//RemovalTimes	
	fscanf(fp,"%s %f",notes,&m_LitterAmount);//AdditiveAmount
	fscanf(fp,"%s %f",notes,&m_LitterCN);//Additive_C/N	

	if(m_CompostDensity>0.0)
	{
		sprintf(SF, "%s\\ManureCompost.txt", INTER);
		sf=fopen(SF, "w");
		fprintf(sf, "%f  %d  %d  %f  %f\n", m_CompostDensity, m_CompostCover, m_CompostRemoveTimes, m_LitterAmount, m_LitterCN);  
		for(int i=1;i<=m_CompostRemoveTimes;i++)
		{	
			fscanf(fp,"%s %d",notes, &CompostRemoveMonth);
			fscanf(fp,"%s %d",notes, &CompostRemoveDay);
			fscanf(fp,"%s %f",notes, &CompostToField);
			fscanf(fp,"%s %f",notes, &CompostToMarket);
			fscanf(fp,"%s %f",notes, &CompostRemain);
			fprintf(sf, "%d %d %f %f %f\n", CompostRemoveMonth, CompostRemoveDay, CompostToField, CompostToMarket, CompostRemain);
		}
		fclose(sf);
	}
	
	fscanf(fp,"%s", notes);//AnaerobicDigester
	fscanf(fp,"%s %d",notes, &m_Temp);//Thermo_type	
	fscanf(fp,"%s %f",notes, &m_DigesterCH4);//MethaneProductivity
	fscanf(fp,"%s %f",notes, &m_DigesterDays);//RetentionDays
	fscanf(fp,"%s %f",notes, &DigesterToField);//Manure_to_field
	fscanf(fp,"%s %f",notes, &DigesterToMarket);//Manure_to_lagoon			
	fscanf(fp,"%s %f",notes, &DigesterRemain);//Manure_remain

	if(m_Temp==0) m_DigesterCH4 = 0.1;
	else if(m_Temp==1) m_DigesterCH4 = 0.12;
	else if(m_Temp==2) m_DigesterCH4 = 0.15;
	else m_DigesterCH4 = 0.0;
	
	if(m_DigesterDays>0.0)
	{
		sprintf(SF, "%s\\ManureDigester.txt", INTER);
		sf=fopen(SF, "w");
		fprintf(sf, "%d  %f  %f\n", m_Temp,m_DigesterCH4,m_DigesterDays);  
		fprintf(sf, "%f  %f  %f\n", DigesterToField,  DigesterToMarket, DigesterRemain);
		fclose(sf);

		
	}

	//Land application
	int CropOrder, FarmCropType, FarmFields;
	float FarmCropHa, ManuFraction;
	char XFF[200];
	FILE *xff;

	char XXX[300];
	FILE *xxx;		
	sprintf(XXX, "%s\\ManureFieldCrops", INTER);		
	xxx=fopen(XXX, "w");
	if(xxx==NULL) note(1,XXX);

	fscanf(fp,"%s", notes);//LandApplication	
	fscanf(fp,"%s %f",notes, &FieldArea);//Land_area
	fscanf(fp,"%s %d",notes, &FarmFields);//Fields in farm
	fprintf(xxx, "%d\n", FarmFields);

	{
	for(int i=1;i<=FarmFields;i++)
	{
		fscanf(fp,"%s %d",notes, &CropOrder);//CroppingSystem
		fscanf(fp,"%s %d",notes, &FarmCropType);//CropType
		fscanf(fp,"%s %f",notes, &FarmCropHa);//FieldArea	
		fscanf(fp,"%s %f",notes, &ManuFraction);//ManureShareFraction

		sprintf(XFF, "%s\\ManureField_%d", INTER, i);		
		xff=fopen(XFF, "w");	
		fprintf(xff, "%d  %d  %f  %f\n", i, FarmCropType, FarmCropHa, ManuFraction);
		fclose(xff);

		fprintf(xxx, "%d %d %f %f\n", i, FarmCropType, FarmCropHa, ManuFraction);
	}	
	}

	fclose(xxx);

/*	if(FieldArea>0.0)
	{
		sprintf(MP, "%s\\FarmFieldManureFractionSum", INTER);
		mp=fopen(MP, "w");
		fprintf(mp, "%d %f %f\n", FarmFields, FieldArea, ManuFraction);
		fclose(mp);
	}	
*/
#endif

	//climate data
	int jd;
	for (int x = 1; x <= 5; x++) fscanf(fp, "%s %d", notes, &jd);

	fscanf(fp,"%s",notes);//"--------------------"	
	fscanf(fp,"%s",notes);//"Climate data:"	
	fscanf(fp,"%s %d", notes,&ClimateFileType);//"Climate_Data_Type:"	
	fscanf(fp,"%s %f", notes,&NO3NH4_Rainfall);	//"NO3NH4_in_Rainfall"
	fscanf(fp,"%s %f", notes,&NH3_Atmosphere);	//"NH3_of_Atmosphere:"
	fscanf(fp,"%s %f", notes,&BaseCO2);		//"BaseCO2_of_Atmosphere"
	fscanf(fp,"%s %d", notes,&ClimateFileNumber);	 //"Climate_file_count="	

	k=ClimateFileType;
	int nn=ClimateFileNumber;
	
	//reads climate files
	for(int w=1; w<=ClimateFileNumber; w++) 
	{
		fscanf(fp,"%d", &j);		
		fscanf(fp,"%s", ClimateFilename[w]);	
	}



	fscanf(fp,"%s", notes);
	fscanf(fp,"%d", &if1File);
	fscanf(fp,"%s %f", notes,&CO2IncreaseRate);

	int CO2file;

	fscanf(fp, "%s %d", notes, &CO2file);

	//if there is a CO2 file then it scans the file name and saves 
	if (CO2file == 1)
	{
		fscanf(fp, "%s", notes);//scan the ProfileFileName
		fgets(tmp, 230, fp);//copied the code for the climate Name reading don't fully understand.
		EraseFBSpace(tmp);
	//	CO2FileName = tmp;//set the file name to IData.ProfileFileName

	}
	else
	{
		fscanf(fp, "%s", notes);//probably should be %s fscanf(fp,"%s %d", notes, &jd)
	}


	// Read Soil parameter	
	
	fscanf(fp,"%s",notes);//"-------------------------------"	
	fscanf(fp,"%s",notes);//"Soil data:"	
	fscanf(fp, "%s %d", notes, &Soil_landuse);//"Landuse_Type"
	fscanf(fp,"%s %d", notes,&Soil_Texture);//"Soil_Texture"
	fscanf(fp,"%s %f", notes,&Soil_Density);//"Density"
	fscanf(fp,"%s %f", notes,&Soil_pH);	 // "Soil_pH"
	fscanf(fp, "%s %f", notes, &Soil_Clay);	// "Clay_fraction"
	fscanf(fp, "%s %f", notes, &Soil_Porosity);
	fscanf(fp, "%s %f", notes, &Soil_BypassFlow);	//"BypassFlow"
	fscanf(fp, "%s", notes);
	fscanf(fp, "%f", &Fldcap);
	fscanf(fp, "%s %f", notes, &Wiltpt);
	fscanf(fp, "%s %f", notes, &Sks);//conductivity

	fscanf(fp,"%s %f", notes,&Soil_OCatSurface);//"SOC_at_Surface"
	
	
    fscanf(fp,"%s %f", notes,&Soil_Litter);	//"Litter_SOC"
    fscanf(fp,"%s %f", notes,&Soil_humads);	//"Humads_SOC"
	fscanf(fp,"%s %f", notes,&Soil_humus);	//"Humus_SOC"
	fscanf(fp, "%s %f", notes, &DClitter);
	fscanf(fp, "%s %f", notes, &DChumads);
	fscanf(fp, "%s %f", notes, &DChumus);
	fscanf(fp, "%s %f", notes, &HumadCN);
	fscanf(fp, "%s %f", notes, &HumusCN);
	fscanf(fp, "%s %f", notes, &PassiveC);
	fscanf(fp, "%s %f", notes, &PassiveCCN);//"Soil_PassiveCN"
	Soil_moiture = 0.5;
	PassiveCCN = 500.0;
	fscanf(fp, "%s %f", notes, &SOCa);
	fscanf(fp, "%s %f", notes, &SOCb);


	fscanf(fp,"%s %f", notes,&Soil_NO3);	//"Soil_NO3(-)(mgN/kg)"
	fscanf(fp,"%s %f", notes,&Soil_NH4);	//"Soil_NH4(+)(mgN/kg)"
	fscanf(fp, "%s %f", notes, &Soil_MicrobioIndex);
	fscanf(fp, "%s %f", notes, &slope);
	fscanf(fp,"%s %f", notes,&LateralInflux);//"Lateral_influx_index"
	if(LateralInflux<1.0) LateralInflux = 1.0;
	fscanf(fp, "%s %f", notes, &HighestWT);
	fscanf(fp, "%s %f", notes, &Soil_WaterObstructLayer);

	fscanf(fp, "%s", notes);
	fscanf(fp, "%f", &Soil_Quality);
	fscanf(fp, "%s %d", notes, &SCSuse);

	
	if (SCSuse == 1)
	{
		float m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage;

		fscanf(fp, "%s %f", notes, &m_CN);
		fscanf(fp, "%s %f", notes, &m_RoughLand);
		fscanf(fp, "%s %f", notes, &m_RoughChannel);
		fscanf(fp, "%s %f", notes, &m_ChannelSlope);
		fscanf(fp, "%s %f", notes, &m_ChannelLength);
		fscanf(fp, "%s %f", notes, &m_LandManage);

		char scs[120];
		FILE* scspara;
		sprintf(scs, "%s\\Inputs\\scspara", OUTPUT);
		scspara = fopen(scs, "w");
		if (scspara == NULL) note(1, scs);
		fprintf(scspara, "%f %f %f %f %f %f\n", m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage);
		fclose(scspara);
	}



	

	
	if(Sks<0.015) Sks = 0.015;
	if(HighestWT>2.0) HighestWT = 2.0;//Highest Water Table Depth??? Was 1.0.

	// Read crop parameter
    int ri, temp, yc, db_CycleYear[20], FCTT=0;
	int db_Rotation_Number, FarmMode=0, FarmCropNumber;
	char DB[200], FCT60[200], CropDB[200];
	FILE *db, *cropdb;

	FCTT++;
	sprintf(FCT60, "%s_%d", INTERMANAGE, FCTT);
	_mkdir(FCT60);
	
	fscanf(fp,"%s",notes);//"--------------------------------"
	fscanf(fp,"%s", notes);// "Crop_data"
	fscanf(fp,"%s %d", notes,&db_Rotation_Number);// "Rotation_number"
		
	sprintf(DB, "%s\\CropRotation.txt", FCT60);
	db=fopen(DB, "w");
	fprintf(db, "%d\n", db_Rotation_Number);
	fclose(db);
	
	for (i=1;i<=db_Rotation_Number;i++)
	{
		int db_TotalYear;
		int tilln, TillMonth, TillDay, TillMethod;
		int manun, ManuMonth, ManuDay, ManuType, ManuMethod;
		float ManuAmount, ManuCN, ManuN;

		fscanf(fp,"%s %d", notes, &ri);// "Rotation_ID"
		fscanf(fp,"%s %d", notes, &db_TotalYear);//Totalyear=	
		fscanf(fp,"%s %d", notes, &db_CycleYear[i]);//Years_Of_A_Cycle=
				
		sprintf(DB, "%s\\CropRotation_%d.txt", FCT60, i);
		db=fopen(DB, "w");
		fprintf(db, "%d\n", i);
		fprintf(db, "%d\n", db_TotalYear);			
		fprintf(db, "%d\n", db_CycleYear[i]);
		fclose(db);	
			
		for (j=1;j<=db_CycleYear[i];j++)
		{
			char WT_file[200];
			int db_Type, db_Pmonth, db_Pday, db_Hmonth , db_Hday, db_Hyear, db_CoverCrop, db_PerennialCrop;
			float db_Yield, db_Residue;
			float db_GrowthReproductive, db_GrowthVegetative, db_PsnEfficiency, db_PsnMax, db_TreeAge;
			float db_GrainFraction, db_LeafFraction, db_ShootFraction, db_RootFraction;
			float db_GrainCN, db_LeafCN, db_ShootCN, db_RootCN;
			float db_TDD, db_Water, db_OptT, db_Nfix, db_Vascularity;

			sprintf(CropDB, "%s\\CropRotation_%d_%d.txt", FCT60, i, j);
			cropdb=fopen(CropDB, "w");
			if(cropdb==NULL) note(0, CropDB);
			
			fscanf(fp,"%s",notes);//YearID_of_a_cycle=
			fscanf(fp,"%d",&yc);	
			fscanf(fp,"%s %d", notes,&cropn);//Crop_total_Number=
								
			fprintf(cropdb, "%d\n", cropn);
			
			for (k=1;k<=cropn;k++) //crop type loop
			{
				fscanf(fp,"%s",notes);//Crop_ID= 
				fscanf(fp,"%d",&temp);					
				fscanf(fp,"%s %d",notes,&db_Type);//Crop_Type= 
				fscanf(fp,"%s %d %d",notes, &db_Pmonth , &db_Pday);//Plant_time=
				fscanf(fp,"%s %d %d",notes,&db_Hmonth , &db_Hday);//Harvest_time=
				fscanf(fp,"%s %d",notes,&db_Hyear);//Year_of_harvest=
				fscanf(fp,"%s %f",notes,&db_Residue);//Ground_Residue=
				fscanf(fp,"%s %f",notes,&db_Yield);// Yield=  
				fscanf(fp,"%s",notes);//Leaf_fraction= 
				fscanf(fp,"%f", &db_LeafFraction);
				fscanf(fp,"%s",notes);//Leaf_CN= 
				fscanf(fp,"%f", &db_LeafCN);
				fscanf(fp,"%s %f",notes,&db_PsnEfficiency);//Psn_efficiency=
				fscanf(fp,"%s %f",notes,&db_PsnMax);//Psn_maximum= 
				fscanf(fp,"%s %f",notes,&db_TreeAge);//TreeAge= 
				fscanf(fp,"%s %d",notes,&db_CoverCrop);//Cover_crop=
				fscanf(fp,"%s", notes);//Perennial_crop=
				fscanf(fp,"%d",&db_PerennialCrop);
				fscanf(fp,"%s %f",notes,&db_GrainFraction);//Grain_fraction=
				fscanf(fp,"%s %f",notes,&db_ShootFraction);//Stem_fraction=
				fscanf(fp,"%s %f",notes,&db_RootFraction);//Root_fraction=
				fscanf(fp,"%s %f",notes,&db_GrainCN);//Grain_CN= 
				fscanf(fp,"%s %f",notes,&db_ShootCN);//Stem_CN=
				fscanf(fp,"%s %f",notes,&db_RootCN);//Root_CN= 
				fscanf(fp,"%s %f",notes,&db_TDD);//TDD=  
				fscanf(fp,"%s %f",notes,&db_Water);//Water_requirement=
				fscanf(fp,"%s %f",notes,&db_OptT);//Optimum_temp=
				fscanf(fp,"%s %f",notes,&db_Nfix);//N_fixation=
				fscanf(fp,"%s",notes);//Vascularity= 
				fscanf(fp,"%f",&db_Vascularity);
					
			} //end of crop type loop

			fprintf(cropdb, "%d\n", k);
			fprintf(cropdb, "%d\n", db_Type);
			fprintf(cropdb, "%d  %d\n", db_Pmonth , db_Pday);
			fprintf(cropdb, "%d  %d\n", db_Hmonth , db_Hday);
			fprintf(cropdb, "%d\n", db_Hyear);
			fprintf(cropdb, "%f\n", db_Residue);
			fprintf(cropdb, "%f\n", db_Yield);
			fprintf(cropdb, "%f %f %f %f %f\n", db_GrowthReproductive, db_GrowthVegetative, db_PsnEfficiency, db_PsnMax, db_TreeAge);
			fprintf(cropdb, "%d\n", db_CoverCrop);
			fprintf(cropdb, "%d\n", db_PerennialCrop);
			fprintf(cropdb, "%f %f %f %f\n", db_GrainFraction, db_LeafFraction, db_ShootFraction, db_RootFraction);
			fprintf(cropdb, "%f %f %f %f\n", db_GrainCN, db_LeafCN, db_ShootCN, db_RootCN);
			fprintf(cropdb, "%f %f %f %f %f\n", db_TDD, db_Water, db_OptT, db_Nfix, db_Vascularity);					
			fclose(cropdb);

			//Tillage
			sprintf(DB, "%s\\CropTill_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);
			
			fscanf(fp,"%s", notes);// Tillage_number= 
			fscanf(fp,"%d", &tilln);
			
			fprintf(db, "%d\n", tilln);

			for (k=1;k<=tilln;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);// Tillage_ID= 
				fscanf(fp,"%s %d %d %d", notes,&TillMonth, &TillDay, &TillMethod);//Month/Day/method=
				
				fprintf(db, "%d  %d  %d\n", TillMonth, TillDay, TillMethod);	
			}			
			fclose(db);

			//Fertilization
			int fertn, FertMonth, FertDay, FertMethod, FertOption;
			float FertNitrate, FertAbi, FertUrea, FertAnh, FertNH4NO3, FertNH42SO4, FertNH42HPO4, FertDepth;
			float DayRelease, NIefficiency, NIduration, UreaseEfficiency, UreaseDuration;

			sprintf(DB, "%s\\CropFert_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);			
		
			fscanf(fp,"%s %d", notes,&fertn);// Fertil_number=
		
			fprintf(db, "%d\n", fertn);

			if(fertn!=-1)
			{
				for (k=1;k<=fertn;k++) 
				{
					fscanf(fp,"%s %d", notes,&temp);
					
					fscanf(fp,"%s %d %d %d", notes,&FertMonth, &FertDay, &FertMethod);
					fscanf(fp,"%s %f", notes,&FertDepth);
					fscanf(fp,"%s %f", notes,&FertNitrate);
					fscanf(fp,"%s %f", notes,&FertAbi);
					fscanf(fp,"%s %f", notes,&FertUrea);
					fscanf(fp,"%s %f", notes,&FertAnh);
					fscanf(fp,"%s %f", notes,&FertNH4NO3);
					fscanf(fp,"%s %f", notes,&FertNH42SO4);
					fscanf(fp,"%s %f", notes,&FertNH42HPO4);
					
					fprintf(db, "%d %d %d\n", FertMonth, FertDay, FertMethod);
					fprintf(db, "%f %f %f %f %f %f %f %f\n", FertNitrate, FertAbi, FertUrea, FertAnh, FertNH4NO3, FertNH42SO4, FertNH42HPO4, FertDepth);
					
					fscanf(fp,"%s %f", notes,&DayRelease);
					fscanf(fp,"%s %f", notes,&NIefficiency);
					fscanf(fp,"%s %f", notes,&NIduration);
					fscanf(fp,"%s", notes);
					fscanf(fp,"%f", &UreaseEfficiency);
					fscanf(fp,"%s %f", notes, &UreaseDuration);
					
					fprintf(db, "%f %f %f %f %f\n", DayRelease, NIefficiency, NIduration, 
						UreaseEfficiency, UreaseDuration);
				}

				fscanf(fp,"%s",notes);//FertilizationOption=
				fscanf(fp,"%d",&FertOption);
				
				fprintf(db, "%d\n", FertOption);
			}
			else
			{
				char Fertigation[200];
				
				fscanf(fp,"%s %s", notes, Fertigation);
				fprintf(db, "%s\n", Fertigation);
			}
			fclose(db);

			//Manure APPLICATION
			sprintf(DB, "%s\\CropManu_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);
			
			fscanf(fp,"%s %d", notes,&manun);//Manure_number= 
						
			fprintf(db, "%d\n", manun);

			for (k=1;k<=manun;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);
				fscanf(fp,"%s %d %d", notes,&ManuMonth, &ManuDay);
				fscanf(fp,"%s %f %f", notes,&ManuAmount, &ManuCN);
				fscanf(fp,"%s %d", notes, &ManuType);
				fscanf(fp,"%s", notes);
				fscanf(fp,"%d",&ManuMethod);

				fprintf(db, "%d %d\n", ManuMonth, ManuDay);
				fprintf(db, "%f %f %d %d\n", ManuAmount, ManuCN, ManuType, ManuMethod);
			}
			fclose(db);

			//Plastic film	
			int Filmn, FilmOption, FilmMonth1, FilmDay1, FilmMonth2, FilmDay2;
			float CoverFraction;

			sprintf(DB, "%s\\CropPlastic_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);
			
			fscanf(fp,"%s %d", notes,&Filmn);// Plastic_film=
			fscanf(fp,"%s %d", notes,&FilmOption);// Ventilation=
			
			fprintf(db, "%d %d\n", Filmn, FilmOption);

			for (k=1;k<=Filmn;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);// 
				fscanf(fp,"%s %d %d", notes,&FilmMonth1, &FilmDay1);
				fscanf(fp,"%s %d %d", notes,&FilmMonth2, &FilmDay2);
				fscanf(fp,"%s %f", notes,&CoverFraction);
				fscanf(fp,"%f", &CoverFraction);

				fprintf(db, "%d %d\n", FilmMonth1, FilmDay1);
				fprintf(db, "%d %d\n", FilmMonth2, FilmDay2);
				fprintf(db, "%f\n", CoverFraction);				
			}
			fclose(db);

			//Flooding
			sprintf(DB, "%s\\CropFloo_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);
			
			fscanf(fp,"%s %d", notes,&floon);// "Flood_number=
			fscanf(fp,"%s %f", notes,&FloodWaterN);// FloodWaterN=
			fscanf(fp,"%s %d", notes,&WaterControl);// Water_control=
			fscanf(fp,"%s %f", notes, &WaterLeakRate);//Leak_rate=
			
			fprintf(db, "%d %f %d %f\n", floon, FloodWaterN, WaterControl, WaterLeakRate);

			for (k=1;k<=floon;k++) 
			{ 
				fscanf(fp,"%s %d", notes,&temp);// "th Flooding:"			
				fscanf(fp,"%s %d %d", notes,&FlooMonth1, &FlooDay1);
				fscanf(fp,"%s %d %d", notes,&FlooMonth2, &FlooDay2);
				fscanf(fp,"%s %f", notes,&FlooN);
				fscanf(fp,"%s %d", notes,&ShallowFlood);
				
				fprintf(db, "%d %d\n", FlooMonth1, FlooDay1);
				fprintf(db, "%d %d\n", FlooMonth2, FlooDay2);
				fprintf(db, "%f\n", FlooN);
				fprintf(db, "%d\n", ShallowFlood);
			}
			
			fscanf(fp,"%s", notes);//Water_gather=
			fscanf(fp,"%f", &WaterGetherIndex);
				
			fprintf(db, "%f\n", WaterGetherIndex);				
			
			fscanf(fp,"%s", notes);//WT_file=
			fscanf(fp,"%s", WT_file);
			
			fprintf(db, "%s\n", WT_file);

			fscanf(fp,"%s", notes);
			fscanf(fp,"%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
													&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);

			fprintf(db, "%f %f %f %f %f %f\n", m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, 
												m_SurfOutflowIntensity, m_GroundOutflowIntensity);
			
			fclose(db);

			//Irrigation
			int irrin, IrriMode, IrriMonth, IrriDay, IrriMethod, jd;
			float IrriIndex, IrriAmount;

			sprintf(DB, "%s\\CropIrri_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);
		
			fscanf(fp,"%s %d", notes, &irrin);// "Irrigation_number="
			fscanf(fp,"%s %d", notes, &IrriMode);// Irrigation_type="
			fscanf(fp,"%s %f", notes, &IrriIndex);// Irrigation_index="
			fscanf(fp,"%s", notes);//Irrigation_Method=
			fscanf(fp,"%d", &IrriMethod);

			fprintf(db, "%d %d %f %d\n", irrin, IrriMode, IrriIndex, IrriMethod);

			for (k=1;k<=irrin;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);
				fscanf(fp,"%s %d %d", notes,&IrriMonth, &IrriDay);
				fscanf(fp,"%s %f %d", notes,&IrriAmount, &jd);
				if(jd!=0&&jd!=1&&jd!=2) IrriMethod=0;
				else IrriMethod=jd;				

				fprintf(db, "%d %d\n", IrriMonth, IrriDay);
				fprintf(db, "%f %d\n", IrriAmount, IrriMethod);
			}
			fclose(db);

			//Grazing
			int grazn, GrazMonth1, GrazDay1, GrazMonth2, GrazDay2, Excreta;
			float GrazHour, Dairy, Beef, Pig, Horse, Sheep, AddFeed, FeedCN,GrazBiomass,GrazCConsume,GrazCExcrete;

			sprintf(DB, "%s\\CropGraz_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);
			
			fscanf(fp,"%s %d", notes, &grazn);// "Grazing_number="
			
			fprintf(db, "%d\n", grazn);

			for (k=1;k<=grazn;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);
				fscanf(fp,"%s %d %d", notes,&GrazMonth1, &GrazDay1);
				fscanf(fp,"%s %d %d", notes,&GrazMonth2, &GrazDay2);
				fscanf(fp,"%s", notes);
				fscanf(fp,"%f", &Dairy);
				fscanf(fp,"%s %f", notes,&Beef);
				fscanf(fp,"%s %f", notes,&Pig);
				fscanf(fp,"%s %f", notes,&Sheep);
				fscanf(fp,"%s %f", notes,&Horse);
				fscanf(fp,"%s %f", notes,&GrazHour);
				fscanf(fp,"%s", notes);
				fscanf(fp,"%f", &AddFeed);
				fscanf(fp,"%s", notes);
				fscanf(fp,"%f", &FeedCN);
				fscanf(fp,"%s", notes);
				fscanf(fp,"%d", &Excreta);
				fscanf(fp, "%f", &GrazBiomass);
				fscanf(fp, "%f", &GrazCConsume);
				fscanf(fp, "%f", &GrazCExcrete);
			
				fprintf(db, "%d %d\n", GrazMonth1, GrazDay1);
				fprintf(db, "%d %d\n", GrazMonth2, GrazDay2);
				fprintf(db, "%f\n", GrazHour);
				fprintf(db, "%f %f %f %f %f %f %f %d %f %f %f\n", Dairy, Beef, Pig, Sheep, Horse, AddFeed, FeedCN, Excreta, GrazBiomass, GrazCConsume, GrazCExcrete);
			}
			fclose(db);				

			//Grass cutting
			int cutn, CutMonth, CutDay, CutPart;
			float CutAmount;

			sprintf(DB, "%s\\GrassCut_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);			
		
			fscanf(fp,"%s %d", notes,&cutn);// "Cutting_number="			

			fprintf(db, "%d\n", cutn);

			for (k=1;k<=cutn;k++) 
			{
				fscanf(fp,"%s %d", notes, &temp);//Cut_ID=
				fscanf(fp,"%s %d %d", notes,&CutMonth, &CutDay);//Cut_Month/Day=
				fscanf(fp,"%s %f", notes, &CutAmount);//Cut_amount=
				fscanf(fp,"%s", notes);//Cut_part=
				fscanf(fp,"%d", &CutPart);
						
				fprintf(db, "%d %d\n", CutMonth, CutDay);
				fprintf(db, "%f %d\n", CutAmount, CutPart);		
			}
			fclose(db);	
		}//end of a cycle
	}//end of Rotation_numbe 

	int CropModel, Unit;

	fscanf(fp,"%s", notes);//Crop_model_approach
	fscanf(fp,"%d", &CropModel);

	fscanf(fp,"%s", notes);//Unit
	fscanf(fp,"%d", &Unit);

	fclose(fp);

	if(SCSuse==1)
	{
		float m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage;
		
		fscanf(fp, "%f %f %f %f %f %f\n", &m_CN, &m_RoughLand, &m_RoughChannel, &m_ChannelSlope, &m_ChannelLength, &m_LandManage);
		
		char scs[120];
		FILE *scspara;
		sprintf(scs,"%s\\Inputs\\scspara", OUTPUT);
		scspara = fopen(scs, "w");
		if(scspara==NULL) note(1, scs);
		fprintf(scspara, "%f %f %f %f %f %f\n", m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage);	
		fclose(scspara);
		
	}
	
	if(Unit==0||Unit==1) Unit = Unit;
	else Unit = 0;

	char LB[200], CM[200];
	FILE* ddb, *cm;

	sprintf(LB,"%s\\UnitSystem", INTER);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", Unit);
	fclose(ddb);

	sprintf(CM, "%s\\CropModel", INTER);
	cm=fopen(CM, "w");
	if(cm==NULL) note(0, CM);
	fprintf(cm, "%d\n", CropModel);
	fclose(cm);
	
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CreateInputFiles(int DaymetFlag, int UseID, char *r_Country, char *BatchPass) 
{
    SaveSite();
      
    RecordClimateFile(1, DaymetFlag, UseID, r_Country);
    
    SaveSoilParas(1);
    
    SaveInterFarmParas();

    SaveCropParas(BatchPass);

#ifdef MANURE	
	RecordManureFiles();
#endif
	
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void SaveSite(void)
{
    char fname[255];
	FILE *fpo;

    sprintf(fname,"%s\\site", INPUTS);
	fpo=fopen(fname, "w");
	if(fpo==NULL) note(1, fname);

	fprintf(fpo,"%s\n", sitename);
	fprintf(fpo,"%d %d %f %ld %f\n", years, ifdaily, latitude, 365, 100.0);
    fprintf(fpo,"%d\n", Soil_landuse);
    fclose (fpo);	
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void RecordClimateFile(int mode, int DaymetFlag, int UseID, char *r_Country)
{
    int i, yn;	    
    char fname[255], ch[255];
	FILE *fpo;
    	
    for (i=1; i<=years; i++) 
	{		
		if(if1File==0)
			sprintf(ch, "%s", ClimateFilename[i]);
		else
			sprintf(ch,"%s",ClimateFilename[1]);
		
		SaveClimateFileOfAYear(i,ch,latitude, ClimateFileType, NO3NH4_Rainfall, NH3_Atmosphere,BaseCO2,
			mode, CO2IncreaseRate, UseID, r_Country);
    }
}

void SaveClimateFileOfAYear(int id,char *ch, float lat, int ClimateFileType, float NO3NH4_Rainfall,
	float NH3_Atmosphere, float BaseCO2, int mode, float CO2IncreaseRate, int UseID, char *r_Country)
{
	
	FILE *fpo,*fpi;

	sprintf(Pname,"%s",ch);
	sprintf(cn, "%s", "WeatherData");

	//////////////////////////
	char Dname[300], Yname[300], LocationName[300];
	char Dname1[300],Dname2[300],Dname3[300],Yname1[300],Yname2[300],Yname3[300];
	int Site, YieldYear, YieldToday, YieldCrop,YieldMonth, YieldDay;
	if(UseID==10)//drought option
	{
		//////////////////////////////////////////////////////////////////////////
			char YF[200];
			FILE* yf;
			sprintf(YF, "%s\\YieldPrediction", INTER);
			yf=fopen(YF, "r");
			if(yf==NULL) note(0,YF);

			fscanf(yf, "%d %d %d %d %s %d %d", &Site, &YieldCrop, &YieldYear, &YieldToday, LocationName,&YieldMonth, &YieldDay);
			fclose(yf);
		///////////////////////////////////////////////////////////////////////////
	
		if(id==1)
		{
			sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,id);
			if ((fpo=fopen(fname,"w"))==NULL) note(1, fname);
			
			sprintf(Dname,"%s-%d.day",LocationName, id);
			sprintf(Yname,"%s-%d.yr",LocationName, id);	
			fprintf(fpo,"%s\n",Dname);		
			fprintf(fpo,"%s\n",Yname);
			fclose(fpo);
		}
		else
		{
			sprintf(Pname,"%s",LocationName);

			sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,id);
			if ((fpo=fopen(fname,"w"))==NULL) note(1, fname);		
			sprintf(Dname1,"%s-%d-dry.day",LocationName, id);
			sprintf(Dname2,"%s-%d-mid.day",LocationName, id);
			sprintf(Dname3,"%s-%d-wet.day",LocationName, id);
			sprintf(Yname1,"%s-%d-dry.yr",LocationName, id);
			sprintf(Yname2,"%s-%d-mid.yr",LocationName, id);
			sprintf(Yname3,"%s-%d-wet.yr",LocationName, id);
			fprintf(fpo,"%s %s %s\n",Dname1,Dname2,Dname3);		
			fprintf(fpo,"%s %s %s\n",Yname1,Yname2,Yname3);
			fclose(fpo);
		}
	}
	else
	{
		sprintf(fname,"%s\\clim-%d", INPUTS,id);
		if ((fpo=fopen(fname,"w"))==NULL) note(1, fname);
		
		sprintf(Dname,"%s-%d.day",cn, id);
		sprintf(Yname,"%s-%d.yr",cn, id);	
		fprintf(fpo,"%s\n",Dname);		
		fprintf(fpo,"%s\n",Yname);
		fclose(fpo);
	}

	//Create daily climate files
	if(UseID==10)//drought option
	{
		if(id==1)
		{
			CreateDailyClimateFile(Pname, Dname, Yname, UseID, ClimateFileType, lat, 
				NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 0, r_Country);
		}
		else
		{
			CreateDailyClimateFile(Pname, Dname1, Yname1, UseID, ClimateFileType, lat, 
				NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 1, r_Country);
			CreateDailyClimateFile(Pname, Dname2, Yname2, UseID, ClimateFileType, lat, 
				NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 2, r_Country);
			CreateDailyClimateFile(Pname, Dname3, Yname3, UseID, ClimateFileType, lat, 
				NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 3, r_Country);
		}
	}
	else
	{
		CreateDailyClimateFile(Pname, Dname, Yname, UseID, ClimateFileType, lat, 
			NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2,CO2IncreaseRate,
			"None", 0, 0, 0, r_Country);
	}

}

void CreateDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, float lat,
							float NO3NH4_Rainfall,float NH3_Atmosphere,float BaseCO2,
							float CO2IncreaseRate, char *LocaName, int YieldYear, int YieldToday,
							int DMW, char *r_Country)
{
	int tn, j, k;
	char fname[256],cn[256], cjunk[200], junkcc[300], ch[256];
	char CurrentClim[300], junkc[200];
	
	FILE* fpo, *fpi, *fcc;
	sprintf(fname,"%s\\%s", INPUTS, Dname);
	fpo=fopen(fname,"w");
	if(fpo==NULL) note(1,fname);
        
	if(UseID==0)
	{
		fpi=fopen(Pname,"r");
		if (fpi==NULL) note(0, Pname);
		
		if (ClimateFileType!=4) fscanf(fpi,"%s", cjunk);	// read climate file dataname
	}
	else
	{
		if(DMW==0)//year 1
		{
			sprintf(Pname, "%sDatabase\\%s\\%s\\Lib_clim\\%s_%d", ROOTDIR, r_Country, LocaName, LocaName, YieldYear-1);
		}
		else if(DMW==1)//dry year
		{
			sprintf(Pname, "%sDatabase\\DroughtPrediction\\%s\\%s\\%s_dry", ROOTDIR, r_Country, LocaName, LocaName);
		}
		else if(DMW==2)//medium
		{
			sprintf(Pname, "%sDatabase\\DroughtPrediction\\%s\\%s\\%s_mid", ROOTDIR, r_Country, LocaName, LocaName);
		}
		else
		{
			sprintf(Pname, "%sDatabase\\DroughtPrediction\\%s\\%s\\%s_wet", ROOTDIR, r_Country, LocaName, LocaName);
		}

		fpi=fopen(Pname,"r");
		if (fpi==NULL) note(0, Pname);
		 
		if (ClimateFileType!=4) 
		{
			fscanf(fpi,"%s", cjunk);	// read climate file dataname
		}

		sprintf(CurrentClim, "%sDatabase\\DroughtPrediction\\%s\\%s\\%s_%d", ROOTDIR, r_Country, LocaName, LocaName, YieldYear);
		fcc=fopen(CurrentClim, "r");
		if(fcc==NULL) note(0, CurrentClim);
		fscanf(fcc,"%s", cjunk);
	}    
   
	tn = 0;
    AveYrT = 0.0;
	TotalYrRain = 0.0;

	wind_speed = 2.0;//m/s
	humidity = 60.0;//%
	int djunk=0, dflag=0;
	char www[100];

	for(j=1; j<=12; j++) 
	{
		AveMonthT[j] = 0;
        for(k=1; k<=Mday[j]; k++) 
		{	
			dflag=0;

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
			}

			tn++;
			Day_Hrs = 0.0;

			if(lat<0.0)
			{
				Aday = tn - 182;//for southern semisphere
				if(Aday<=0) Aday = 365 + Aday;

				solrad = day_par2(Aday, -lat, &Day_Hrs);
			}
			else
				solrad = day_par2(tn, lat, &Day_Hrs);//extre-terrestrial radiation, MJ/m2/day

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
					
					if(UseID==10&&DMW>0&&YieldToday>=jday)//drought effect
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
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &wind_speed);//wind speed, m/second
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
				char notee[200];
				sprintf(notee, "Error at day %d in climate data file %s", tn, Pname);
				printf(notee);
			}
	
            jday0 = jday;
			
			// Output climate data of 365 days
			fprintf(fpo, "%3d %5.2f  %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f\n",
					jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs, wind_speed, humidity);

			if(jday==1) Soil_T = temp;

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
	fpo=fopen(fname,"w");
	if (fpo==NULL) note(1, fname);
    for(j=1;j<=12;j++) fprintf(fpo,"%.2f	", AveMonthT[j]);
    fprintf(fpo,"\n%.2f\n", AveYrT);
    fprintf(fpo,"%.2f\n", TotalYrRain);
    fprintf(fpo,"%.3f\n", NO3NH4_Rainfall);
    fprintf(fpo,"%.2f\n", NH3_Atmosphere);
	fprintf(fpo,"%.2f\n", BaseCO2);//
	fprintf(fpo,"%.2f\n", CO2IncreaseRate);
	fprintf(fpo,"%d\n", ClimateFileType);
    fclose (fpo);
  
}

float day_par2(int Jday, float LATITUDE, float* Day_Hrs)
{
	/*
	   daylength and horizontal potential insolation for day
		  from Swift (1976) Water Resour Res 12:108 and Sellers (1965) Physical Climatology
	   Jday     day of the year
	   Lat      latitude, radians
	   I0       potential insolation (horizontal) J/m2
	   DECL     declination of the sun, radians
	   R        radius vector of the sun, dimensionless
	   h        half daylength
	   isc      solar constant, W/m2, Lean 1991 Rev. Geophysics 29:
	   Half daylength and declination equations from:
		   Swift, L.W.Jr.(1976). Algorithm for solar radiation on mountain
		   slopes. Water Resources Research, 12(1) 118-112.
	*/
	float pi, isc, lat, r, Z, decl, z2, H, TA, AC, acos, psolrad, solrad;
	float DayPAR, PARc, cloud;

	pi = 3.1416;
	isc = 1367.0;     //solar max Lean 1991 Rev. Geophysics 29
	cloud = 0.75;//.48;

	lat = LATITUDE * (2.0 * 3.1416) / 360.0; //latitude in radians

	r = 1.0 - .0167 * (float)cos(.0172 * (Jday - 3)); //radius vector of the sun

	Z = .398 * (float)sin(4.869 + .0172 * Jday + .0334 * (float)sin(6.224 + .0172 * Jday)); //temporary variable

	if (fabs(Z) < .7)
	   decl = (float)atan(Z / (powf((1 - Z * Z), 0.5)));
	else
	   decl = pi / 2 - (float)atan(powf((1 - Z * Z), 0.5) / Z);

	if (fabs(lat) >= pi / 2) lat = (pi / 2 - .01);

	z2 = -(float)tan(decl) * (float)tan(lat); //temporary variable

	if (z2 >= 1)            //sun stays below horizon
	  H = 0;
	else if (z2 <= -1)      //sun stays above the horizon
	  H = pi;
	else
	{
	  TA = fabs(z2);
	  if (TA < .7) AC = 1.571 - (float)atan(TA / powf((1 - TA * TA), 0.5));
	  else	AC = (float)atan(powf((1 - TA * TA), 0.5) / TA);

	  if (z2 < 0) acos = 3.1416 - AC;
	  else acos = AC;

	  H = acos;
	}

	*Day_Hrs = 2 * (H * 24) / (2 * 3.1416); //Length of day (hr)

	psolrad = isc * (86400 / (3.1416 * r*r)) *
		  (H * (float)sin(lat) * (float)sin(decl) +
		  (float)cos(lat) * (float)cos(decl) * (float)sin(H));
		  //potential insolation, J/m2/day

	solrad = psolrad * cloud / 1000000.0; // million J/m2/day

	DayPAR = solrad * 2.05; //PAR, moles/m2/day

	PARc = DayPAR / (*Day_Hrs * .0036); //daily instantaneous PAR, u moles/m2/second

	return (solrad);

}

int SaveSoilParas(int id)//1
{
	//set soil H
	AcWater   = 0.0;
	SurfWater = 0.0;
	SnowPack  = 0.0;
	Idc = 1 + (int)Soil_BypassFlow;
	Qstar = (float)(6.45 * (Soil_Clay - 0.01) + 1);
    BypassF = Soil_BypassFlow;
    
    float dt;
	int max_layers=280-10;
	TH = SOILDEPTH;//1.0 m, total depth of simulated soil profile 
    dt = 0.01 / Soil_Porosity;
    if (dt < Sks) H = dt;
    else H = Sks;
    	
	if (H*max_layers < TH )
		H = TH / max_layers;

	Q = (int)(TH / H);

	if (Q > max_layers) 
	{
		Q = max_layers;
		H = TH / max_layers;
	}

	////////////////////////////////////
    CEC= Soil_Clay * 46.0;
    m  = Soil_Density * 1000. * H * 10000.0;
    V  = H * 10000. * Soil_Porosity;	// m^3/layer/ha
    
    int n;
    n = Q;
    double RCVL[2], RCL[2], RCR[2];
    double Urea[2], NH3[2];
    double Tranr[2], OCini[2], Dphum[2], CharC[2];
    double s_NO3[2], s_NH4[2], ClayNH4[2];
    double s_NO[2], s_N2O[2];
    double s_N2[2], s_NO2[2], s_IniNH4[2];
    
    double PS, FLDCAPw, Wiltptw, TravelTime, ClayF1, ClayF2;//, ePS;
    float RCNRVL, RCNRL, RCNRR, RCNB, RCNH, RCNM, PassiveCCN;
    double stub1, stub2, stub3, Dbm;
    
    PS		= H * Soil_Porosity;	// porosity  (m/layer)
    FLDCAPw = PS * Fldcap;	// m water/layer FieldCapacity
    Wiltptw = PS * Wiltpt;	// m water/layer
    TravelTime = 20.0 * (PS - FLDCAPw) / Sks;	// hr/layer
        // fraction of soil water available for plants, can be tuned
    ClayF1 = pow(10.0,-Soil_Clay / 0.75 - 0.2);
    ClayF2 = Soil_Clay * 6.;

	RCNRVL = 5.;
	RCNRL  = 25.;
	RCNRR  = 100.;
    RCNB   = 10.0;
	RCNH   = 10.0;
	RCNM   = 10.0;
	PassiveCCN = 500.0;
      
    Tranr[1] = Soil_OCatSurface * Soil_Litter * m;
    OCini[1] = Soil_OCatSurface * Soil_humads * m;
    Dphum[1] = Soil_OCatSurface * Soil_humus * m;
	CharC[1] = Soil_OCatSurface * PassiveC * m;
    
    s_NO3[1] = Soil_NO3 * m / 1000000.;
    s_IniNH4[1] = Soil_NH4 * m / 1000000.;
    
    RCVL[1] = 0.0 * Tranr[1];
    RCL[1]  = 0.0 * Tranr[1];
    RCR[1]  = 1.0 * Tranr[1];

	Dbm = Soil_Density;
     
    s_NH4[1]   = s_IniNH4[1] * 0.7;
    ClayNH4[1] = s_IniNH4[1] * 0.3;

	float F_soc = Soil_OCatSurface/0.058;
	if(F_soc>1.0) F_soc = 1.0;

	//ClayNH4[1] = F_soc * CEC * 0.4; 
	//ClayNH4[1] = CEC * 0.4; //NewChange

    Urea[1]= 0.;
    NH3[1] = 0.;
    stub1  = 0.;
    stub2  = 0.;
    stub3  = 0.;
     
   	int i;
	float TCN=0.0;

    s_NO[1] = 0.;
    s_N2O[1]= 0.;
    s_N2[1] = 0.;
    s_NO2[1]= 0.;
            
//#define INPUTS "\\DNDC\\INPUTS"
    char fname[255];
	FILE *fpo;
    sprintf(fname,"%s\\soil-%d", INPUTS, abs(id));
	fpo=fopen(fname,"w");
	if(fpo==NULL) note(1, fname);

	float IniFrostN2O=0, IniFrostN2=0,ice=0,tt[120];
	int Retard=1;
	if (SoilRetardation==1) Retard=3;
    
	for (i=1; i<=Q; i++)
	{
		tt[i] = AveYrT + (Soil_T - AveYrT)/ powf(i*H*100, 0.5);
		if (Soil_T<0.0 && tt[i] < Soil_T) tt[i] = Soil_T;		
	}

	fprintf(fpo,"%3d\n", Soil_Texture);
    fprintf(fpo,"%s\n\n", SoilName);

    fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
		Soil_Clay, Soil_Porosity, Sks, Fldcap,
		Wiltpt, LateralInflux); 
    fprintf(fpo,"%f %f %f %f %d  %f\n",
		Psisat, Beta, Dbm, Soil_pH, 
		Idc, Soil_OCatSurface);
    fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
		Soil_NO3, Soil_NH4, Soil_Litter, 
		Soil_humads, Soil_humus, 0.0);//Byp
    fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %d\n",
		H, TH, m, V, Q);
    fprintf(fpo,"%.4f  %.4f\n", ClayF1, ClayF2);
    fprintf(fpo,"%.4f  %.4f  %d  %.4f  %.4f  %.4f  %.4f\n",
		Qstar, BypassF, Retard, RCNB, RCNH, RCNM, RCNRVL);
    fprintf(fpo,"%.4f  %.4f %.4f  %.4f  %.4f  %.4f\n",
		RCNRL, RCNRR, AcWater, SurfWater, SnowPack, stub1);
    fprintf(fpo,"%.4f  %.4f\n", stub2, stub3);
    fprintf(fpo, "%.4f  %.4f  %.4f\n\n", PassiveCCN, IniFrostN2O, IniFrostN2);
    
	int WRL = (int)(Soil_WaterObstructLayer*0.01/H);
    
	fprintf(fpo, "%f\n", Soil_MicrobioIndex); 
	fprintf(fpo, "%f\n", Soil_WaterObstructLayer);//m
	fprintf(fpo, "%f %f\n", slope, Soil_Quality); 
	fprintf(fpo, "%f\n", Fldcap); 
	fprintf(fpo, "%f\n", Wiltpt); 
	fprintf(fpo, "%f %f\n", SOCa, SOCb);
	fprintf(fpo, "%f %f %f %f %f %f %f %f %f\n", RCVL[1], RCL[1], RCR[1], OCini[1], Dphum[1],
		s_NO2[1], s_NO3[1], s_NH4[1], ClayNH4[1]);
	fprintf(fpo, "%f\n", tt[1]);
	fprintf(fpo, "%f\n", HighestWT);
	fprintf(fpo, "%d\n", SCSuse);
	fprintf(fpo, "%f\n", CharC[1]);
	fprintf(fpo, "%f\n", DClitter);
	fprintf(fpo, "%f\n", DChumads);
	fprintf(fpo, "%f\n", DChumus);
	fprintf(fpo, "%f\n", HumadCN);
	fprintf(fpo, "%f\n", HumusCN);
	
    fclose (fpo);

	//if (id<0) return 0;

	char SYF[200];
	FILE* sni;
	sprintf(SYF, "%s\\SoilNewIni", INPUTS);
	sni=fopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 1);
	fclose(sni);

	return 0;

}

int SaveInterFarmParas()
{
	int rrr, yyy ;
    char fname[255];
	FILE *fp;
    int i, n, day, db_Rotation_Number, db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20];
		
	int TillID[300], TillMonth[300], TillDay[300], TillMethod[300];
	int FertMonth[300], FertDay[300], FertMethod[300];
	float FertNitrate[300], FertAbi[300], FertUrea[300], FertAnh[300], FertAmNi[300], NH42SO4[300], NH42HPO4[300], FertDepth[300];
	int ManuMonth[300], ManuDay[300], ManuType[300], ManuMethod[300], FertOption;
	float ManuAmount[300], ManuCN[300], ManuN[300];
	float DayRelease[300], NIefficiency[300], NIduration[300];
	float UreaseEfficiency[300], UreaseDuration[300];
	int WeedMonth1[300], WeedDay1[300], WeedMonth2[300], WeedDay2[300];
	float CoverFraction[300];
	int FlooID[300], FlooMonth1[300], FlooDay1[300], FlooMonth2[300], FlooDay2[300];
	float FlooN[300];
	int ShallowFlood[300];
	int IrriMonth[366], IrriDay[366], irrimethod[366];
	float IrriAmount[366];
	int GrazMonth1[300], GrazDay1[300], GrazMonth2[300], GrazDay2[300];
	float GrazHour[300], Dairy[300], Beef[300], Pig[300], Horse[300], Sheep[300], AddFeed[300], FeedCN[300],GrazBiomass[300],GrazCConsume[300],GrazCExcrete[300];
	int CutMonth[300], CutDay[300], CutPart[300], Excreta[300];
	float CutAmount[300];
	char Fertigation[200];
	float WaterGetherIndex, WaterLeakRate;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex,m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	int FarmCrops;
	float FieldArea;

#ifdef MANURE
	//int CropIDID, ManureCropOrder;
	char XFF[200];
	FILE *xff;		
	sprintf(XFF, "%s\\ManureFieldAll.txt", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %f", &FarmCrops, &FieldArea);
	fclose(xff);
#else
	TotalManureCropss = 1;
#endif

for(int MFFC=1; MFFC<=FarmCrops; MFFC++)
{
#ifdef MANURE
	sprintf(FCT0, "%s_%d", INTERMANAGE, MFFC);
#else 
	sprintf(FCT0, "%s_1", INTERMANAGE);
#endif

	char DB[200];
	FILE *db;

	sprintf(DB, "%s\\CropRotation.txt", FCT0);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	
	fscanf(db, "%d", &db_Rotation_Number);
	fclose(db);

	for(rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		sprintf(DB, "%s\\CropRotation_%d.txt", FCT0, rrr);//read: SaveInterFarmParas
		db=fopen(DB, "r");
		if(db==NULL) note(0, DB);
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);

		for(yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
		{    
			// Save tillage
			sprintf(DB, "%s\\CropTill_%d_%d.txt", FCT0, rrr, yyy);
			db=fopen(DB, "r");
			if(db==NULL) note(0, DB);
			fscanf(db, "%d", &n);
			for(int i=1; i<=n; i++)
			{
				TillID[i] = i;
				fscanf(db, "%d %d %d", &TillMonth[i], &TillDay[i], &TillMethod[i]);
			}
			fclose(db);
	
			sprintf(fname,"%s\\ti-%d_%d",FCT0,rrr,yyy);
			fp=fopen(fname, "w");
			if (fp == NULL) note(1, fname);
    
   			fprintf(fp,"%d\n", n);
			for(int iy1=1; iy1<=n; iy1++) 
			{		
				day = JulianDay(TillMonth[iy1], TillDay[iy1]);
				fprintf(fp,"%d %d\n",day,TillMethod[iy1]);
			}
			fclose (fp);
    
    // Save fertilization
	sprintf(DB, "%s\\CropFert_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &n);
	if(n==-1)
	{
		fscanf(db, "%s", Fertigation);
	}
	else
	{
		for(int i=1; i<=n; i++)
		{
			fscanf(db, "%d %d %d", &FertMonth[i], &FertDay[i], &FertMethod[i]);
			fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[i], &FertAbi[i], &FertUrea[i], &FertAnh[i], &FertAmNi[i], 
				&NH42SO4[i], &NH42HPO4[i], &FertDepth[i]);
			fscanf(db, "%f %f %f %f %f", &DayRelease[i], &NIefficiency[i], &NIduration[i],&UreaseEfficiency[i], &UreaseDuration[i]);
		}
		fscanf(db, "%d", &FertOption);
		
	}
	fclose(db);

	sprintf(fname,"%s\\fe-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(1, fname);
    
    fprintf(fp,"%d\n", n);
	if(n==-1)
	{
		fprintf(fp,"%s\n", Fertigation);
	}
	else
	{
		for (int i=1; i<=n;i++) 
		{
			day = JulianDay(FertMonth[i], FertDay[i]);
			fprintf(fp,"%d %f\n", day, FertDepth[i]*0.01);			
			fprintf(fp,"%f %f %f %f %f %f %f\n", FertNitrate[i], FertAbi[i], FertUrea[i], FertAnh[i], FertAmNi[i], NH42SO4[i], NH42HPO4[i]); 
			fprintf(fp,"%d %f %f %f %f %f\n", FertOption, DayRelease[i], NIefficiency[i], NIduration[i],UreaseEfficiency[i], UreaseDuration[i]);
		}		
	}
    fclose (fp);
    
    // Save Manuring file
	
	sprintf(DB, "%s\\CropManu_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &n);
	for(int i2=1; i2<=n; i2++)
		{
			fscanf(db, "%d %d", &ManuMonth[i], &ManuDay[i2]);
			fscanf(db, "%f %f %d %d", &ManuAmount[i2], &ManuCN[i2], &ManuType[i2], &ManuMethod[i2]);
		}
	fclose(db);

	sprintf(fname,"%s\\ma-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(1, fname);
    
    fprintf(fp,"%d\n", n);
    for (int i3=1; i3<=n;i3++) 
	{
        day = JulianDay(ManuMonth[i3], ManuDay[i3]);
		
        fprintf(fp,"%d %f %f %d %d\n", day, ManuAmount[i3], ManuCN[i3], ManuType[i3], ManuMethod[i3]);
    }
    fclose (fp);
        
    // Save plastic file
	int WeedOption;
	
	sprintf(DB, "%s\\CropPlastic_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d %d", &n, &WeedOption);
	for(int i4=1; i4<=n; i4++)
	{
		fscanf(db, "%d %d", &WeedMonth1[i4], &WeedDay1[i4]);
		fscanf(db, "%d %d", &WeedMonth2[i4], &WeedDay2[i4]);
		fscanf(db, "%f", &CoverFraction[i4]);
	}
	fclose(db);

	sprintf(fname,"%s\\pl-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(1, fname);
    
    fprintf(fp, "%d %d\n",n, WeedOption);
    for (int i5=1; i5<=n;i5++) 
	{
        int day1 = JulianDay(WeedMonth1[i5], WeedDay1[i5]);
		int day2 = JulianDay(WeedMonth2[i5], WeedDay2[i5]);
        fprintf(fp,"%d %d\n",day1, day2);
		fprintf(fp,"%f\n",CoverFraction[i5]);
    }
    fclose (fp);
    
    // Save Flooding file
	int WaterControl;
	float FloodWaterN;
	char WT_file[200];
	
	sprintf(DB, "%s\\CropFloo_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d %f %d %f", &n, &FloodWaterN, &WaterControl, &WaterLeakRate);
	for(int i6=1; i6<=n; i6++)
		{
			FlooID[i] = i;
			fscanf(db, "%d %d", &FlooMonth1[i6], &FlooDay1[i6]);
			fscanf(db, "%d %d", &FlooMonth2[i6], &FlooDay2[i6]);
			fscanf(db, "%f", &FlooN[i6]);
			fscanf(db, "%d", &ShallowFlood[i6]);
		}

	fscanf(db, "%f", &WaterGetherIndex);
	fscanf(db, "%s", WT_file);

	fscanf(db, "%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
												&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);
	
	fclose(db);
    
	sprintf(fname,"%s\\fl-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(1, fname);

	fprintf(fp,"%d\n", n);
    for (int i7=1; i7<=n;i7++) 
	{
        day = JulianDay(FlooMonth1[i7], FlooDay1[i7]);		
        fprintf(fp, "%d ",day);
        day = JulianDay(FlooMonth2[i7], FlooDay2[i7])+1;	
        fprintf(fp, "%d\n",day);
		fprintf(fp, "%f %d\n", FlooN[i7], ShallowFlood[i7]);
    }
	
    fprintf(fp, "%d %f %f %f\n", WaterControl, WaterLeakRate, WaterGetherIndex, FloodWaterN);
	fprintf(fp, "%s\n",WT_file);
	fprintf(fp, "%f %f %f %f %f %f\n",m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, m_SurfOutflowIntensity, m_GroundOutflowIntensity);
    fclose (fp);
	     
    // Save Irrigation file
	int IrrMode;
	float IrrIndex;
	
	sprintf(DB, "%s\\CropIrri_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d %d %f %d", &n, &IrrMode, &IrrIndex, &irrimethod[0]);
	for(int i8=1; i8<=n; i8++)
		{
			fscanf(db, "%d %d", &IrriMonth[i8], &IrriDay[i8]);
			fscanf(db, "%f %d", &IrriAmount[i8], &irrimethod[i8]);
		}
	fclose(db);

	sprintf(fname,"%s\\ir-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(1, fname);

    fprintf(fp,"%d %f %d\n", n, IrrIndex, irrimethod[0]);    
	for (int i9=1; i9<=n;i9++) 
	{
        day = JulianDay(IrriMonth[i9], IrriDay[i9]);
		
        fprintf(fp,"%d %f %d\n", day, IrriAmount[i9], irrimethod[i9]);
    }
    fclose (fp);    

    // Save Grazing file
	sprintf(DB, "%s\\CropGraz_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &n);
	for(int i10=1; i10<=n; i10++)
	{
		fscanf(db, "%d %d", &GrazMonth1[i10], &GrazDay1[i10]);
		fscanf(db, "%d %d", &GrazMonth2[i10], &GrazDay2[i10]);
		fscanf(db, "%f", &GrazHour[i10]);
		fscanf(db, "%f %f %f %f %f", &Dairy[i10], &Beef[i10], &Pig[i10], &Sheep[i10], &Horse[i10]);
		fscanf(db, "%f %f %d", &AddFeed[i10], &FeedCN[i10], &Excreta[i10]);
		fscanf(db, "%f %f %f", &GrazBiomass[i10], &GrazCConsume[i10], &GrazCExcrete[i10]);
	}
	fclose(db);

	sprintf(fname,"%s\\gr-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(1, fname);

    fprintf(fp, "%d\n", n);
	int bt,et;
    for (int i11=1; i11<=n; i11++)
    {
		bt=JulianDay(GrazMonth1[i11], GrazDay1[i11]);
		et=JulianDay(GrazMonth2[i11], GrazDay2[i11]);
		fprintf(fp, "%d %d %f %f %f %f %f %f %f %f %d %f %f %f\n",bt,et,Dairy[i11], Beef[i11], Pig[i11], Sheep[i11],Horse[i11],
			GrazHour[i11], AddFeed[i11], FeedCN[i11], Excreta[i11],GrazBiomass[i11], GrazCConsume[i11],GrazCExcrete[i11]);
			
    }
    fclose(fp);

	// Save garss cutting file
	sprintf(DB, "%s\\GrassCut_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &n);
		for(int i12=1; i12<=n; i12++)
		{
			fscanf(db, "%d %d", &CutMonth[i12], &CutDay[i12]);
			fscanf(db, "%f", &CutAmount[i12]);
			fscanf(db, "%d", &CutPart[i12]);
		}
	fclose(db);

	sprintf(fname,"%s\\cut-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(1, fname);

    fprintf(fp, "%d\n", n);
    for (int i13=1; i13<=n; i13++)
    {
		bt=JulianDay(CutMonth[i13], CutDay[i13]);
		fprintf(fp, "%d %f\n",bt, CutAmount[i13]);
		fprintf(fp, "%d\n", CutPart[i13]);
    }
    fclose(fp);
	}
	}
}
    return (0);
}

int SaveCropParas(char *BatchPass)
{
	int FarmCrops;
	float FieldArea;
	
#ifdef MANURE	
	char XFF[300];
	FILE *xff;		
	
	sprintf(XFF, "%s\\ManureFieldAll.txt", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %f", &FarmCrops, &FieldArea);
	fclose(xff);	
#else	
	TotalManureCropss = 1;
#endif

    char fname[255],outname[255];
    int  i, j, k, kkk, yr;//, hyr=0;
	FILE *fcrop, *fpi;

	int db_Rotation_Number;
	int db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20],db_PerennialCrop[20][20][5];
	int db_YrCrops[20][20], db_YrCropOrder[20][20][5], db_YrCropType[20][20][5], db_CoverCrop[20][20][5];
	int db_PMonth[20][20][5], db_PDay[20][20][5], db_HMonth[20][20][5], db_HDay[20][20][5], db_HYr[20][20][5];
	float db_Residue[20][20][5], db_Yield[20][20][5], db_RepRate[20][20][5], db_VegRate[20][20][5];
	float db_PsnEff[20][20][5], db_PsnMax[20][20][5], db_TreeAge[20][20][5];
	float db_GrainFraction[20][20][5], db_LeafFraction[20][20][5], db_ShootFraction[20][20][5], db_RootFraction[20][20][5];
	float db_GrainCN[20][20][5], db_LeafCN[20][20][5], db_ShootCN[20][20][5], db_RootCN[20][20][5];
	float db_TDD[20][20][5], db_Water[20][20][5], db_OptT[20][20][5], db_Nfix[20][20][5], db_Vascularity[20][20][5];
	float db_Root1[20][20][5], db_AGResp1[20][20][5], db_AGResp2[20][20][5], db_Root2[20][20][5], db_VE[20][20][5], db_V1[20][20][5], db_VT[20][20][5], db_R1[20][20][5], db_R3[20][20][5], db_R5[20][20][5], db_R7[20][20][5], db_R8[20][20][5], db_PVE[20][20][5], db_PV1[20][20][5], db_PVT[20][20][5], db_PR1[20][20][5], db_PR3[20][20][5], db_PR5[20][20][5], db_PR7[20][20][5], db_PR8[20][20][5];
	float db_Kext1[20][20][5], db_Kext2[20][20][5], db_cropHeight[20][20][5];//Theo db_cropHeight,db_Kext2,db_Kext1
	float db_cropGRate[20][20][5], db_cropTime[20][20][5], db_RUEHI[20][20][5], db_DelayP[20][20][5];
	char DB[200];
	FILE *db;

for(int MFFC=1; MFFC<=FarmCrops; MFFC++)
{
#ifdef MANURE
	sprintf(FCT0, "%s_%d", INTERMANAGE, MFFC);
	sprintf(FCT100, "%s\\FarmCrop_%d", BatchPass, MFFC);
	_mkdir(FCT100);
#else
	sprintf(FCT0, "%s_1", INTERMANAGE);
	sprintf(FCT100, "%s", INPUTS);
#endif

	sprintf(DB, "%s\\CropRotation.txt", FCT0);
	db=fopen(DB, "r");
	if(db==NULL) note(0,DB);
	
	fscanf(db, "%d", &db_Rotation_Number);
	fclose(db);

	int ccc;
	for(int rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		sprintf(DB, "%s\\CropRotation_%d.txt", FCT0, rrr);//read: SaveCropParas()
		db=fopen(DB, "r");
		if(db==NULL) note(0,DB);
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);

		for(int yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
		{
			sprintf(DB, "%s\\CropRotation_%d_%d.txt", FCT0, rrr, yyy);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &db_YrCrops[rrr][yyy]);

			for(ccc=1; ccc<=db_YrCrops[rrr][yyy]; ccc++)
			{
				fscanf(db, "%d %d", &db_YrCropOrder[rrr][yyy][ccc], &db_YrCropType[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_PMonth[rrr][yyy][ccc], &db_PDay[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_HMonth[rrr][yyy][ccc], &db_HDay[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_HYr[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_Residue[rrr][yyy][ccc], &db_Yield[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_RepRate[rrr][yyy][ccc], &db_VegRate[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_PsnEff[rrr][yyy][ccc], &db_PsnMax[rrr][yyy][ccc]);
				fscanf(db, "%f", &db_TreeAge[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_CoverCrop[rrr][yyy][ccc]);	
				fscanf(db, "%d", &db_PerennialCrop[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_GrainFraction[rrr][yyy][ccc], &db_LeafFraction[rrr][yyy][ccc], &db_ShootFraction[rrr][yyy][ccc], &db_RootFraction[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_GrainCN[rrr][yyy][ccc], &db_LeafCN[rrr][yyy][ccc], &db_ShootCN[rrr][yyy][ccc], &db_RootCN[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f %f", &db_TDD[rrr][yyy][ccc], &db_Water[rrr][yyy][ccc], &db_OptT[rrr][yyy][ccc], &db_Nfix[rrr][yyy][ccc], &db_Vascularity[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &db_Root1[rrr][yyy][ccc], &db_Root2[rrr][yyy][ccc], &db_AGResp1[rrr][yyy][ccc], &db_AGResp2[rrr][yyy][ccc], &db_VE[rrr][yyy][ccc], &db_V1[rrr][yyy][ccc], &db_VT[rrr][yyy][ccc], &db_R1[rrr][yyy][ccc], &db_R3[rrr][yyy][ccc], &db_R5[rrr][yyy][ccc], &db_R7[rrr][yyy][ccc], &db_R8[rrr][yyy][ccc], &db_PVE[rrr][yyy][ccc], &db_PV1[rrr][yyy][ccc], &db_PVT[rrr][yyy][ccc], &db_PR1[rrr][yyy][ccc], &db_PR3[rrr][yyy][ccc], &db_PR5[rrr][yyy][ccc], &db_PR7[rrr][yyy][ccc], &db_PR8[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f", &db_Kext1[rrr][yyy][ccc], &db_Kext2[rrr][yyy][ccc], &db_cropHeight[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_cropGRate[rrr][yyy][ccc], &db_cropTime[rrr][yyy][ccc], &db_RUEHI[rrr][yyy][ccc], &db_DelayP[rrr][yyy][ccc]);
			}			
			fclose(db);

			///////////////////////////////////////////////////////////
			char fname[255];
			FILE *fp;
			int WinterCropFlag=0, LeftDays=0;
    
			sprintf(fname, "%s\\cyc-%d_%d", FCT0,rrr, yyy);
			fp=fopen(fname, "w");
			if(fp==NULL) note(1, fname);

			if (db_YrCrops[rrr][yyy]==0) //no crop
			{
				fprintf(fp, "%d\n", 0);
				fprintf(fp, "%d  %s  %d  %d  %f  %d\n", 0, "None", 0, 0, 0.0, 10);
				fprintf(fp, "%d  %d  %f  %f  %d\n", 0, 0, 0.0, 0.0, 999);
				fprintf(fp, "%f  %f  %f  %f  %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
				fprintf(fp, "%d\n", 0);
				//fprintf(fp, "%d\n", 0);

				// CropCode, WinterCropFlag, WinterCropLeftDays, OptimumYield, HarvestYear;
				  // PalntingJday, GrowingDays, ResidueIncorporation, MaxNDemand, EndCropFlag;
				  // IniCropBiomass, GRvege, GRreprod, PsnEfficiency, PsnMax 
				//cover_crp
			}
			else
			{
				fprintf(fp, "%d\n", db_YrCrops[rrr][yyy]);
				for (int i=1;i<=db_YrCrops[rrr][yyy];i++) 
				{
					int SeedDay = JulianDay(db_PMonth[rrr][yyy][i], db_PDay[rrr][yyy][i]);
					int HarvDay = JulianDay(db_HMonth[rrr][yyy][i], db_HDay[rrr][yyy][i]);
					int GrowDays;
					if(db_HYr[rrr][yyy][i]==1)//SeedDay<HarvDay)
					{
						GrowDays = HarvDay - SeedDay;
						WinterCropFlag = 0;
						LeftDays = 0;
					}
					else
					{
						GrowDays = 365 - SeedDay + HarvDay + (db_HYr[rrr][yyy][i] - 2) * 365;
						WinterCropFlag = db_HYr[rrr][yyy][i] - 1;//yyy-1;
						if(WinterCropFlag==1) LeftDays = GrowDays;
						else LeftDays = GrowDays - (365*(db_HYr[rrr][yyy][i] - 1) - SeedDay);
					}

					int wwww=111, jd;
					if(i==db_YrCrops[rrr][yyy]) wwww = 999;

					
					int CropType = db_YrCropType[rrr][yyy][i];
					char CropNameX[100];

					///////////////////////////////////////////////////////////////////////////////////////////
					int v_CropID[95], v_Perennial[95];
					float v_max_biomass_C[95], v_grain_fraction[95], v_leaf_fraction[95], v_leafstem_fraction[95], v_root_fraction[95];
					float v_GrainCN[95], v_LeafCN[95], v_ShootCN[95], v_RootCN[95], v_TreeAge[95];
					float v_WaterDemand[95], v_OptimumT[95], v_TDD[95], v_Nfixation[95], v_Vascularity[95];
					float v_Root1[95], v_Root2[95], v_VE[95], v_V1[95], v_VT[95], v_R1[95], v_R3[95], v_R5[95], v_R7[95], v_R8[95], v_PVE[95], v_PV1[95], v_PVT[95], v_PR1[95], v_PR3[95], v_PR5[95], v_PR7[95], v_PR8[95];//new parameters for root respiration, plant growth routine
					float v_Kext1[95], v_Kext2[95], v_cropHeight[95];
					//CString v_CropName[95];
					char v_CropName[95][100]={"NONE","NONE"};

					ReadCropPara_2(v_CropID, v_CropName, v_max_biomass_C, v_grain_fraction, v_leaf_fraction,
					  v_leafstem_fraction, v_root_fraction, v_GrainCN, 
					  v_LeafCN, v_ShootCN, v_RootCN, v_WaterDemand, v_OptimumT, 
					  v_TDD, v_Nfixation, v_Vascularity, v_Perennial, v_TreeAge,v_Root1,v_Root2,v_VE,v_V1,v_VT,v_R1,v_R3,v_R5,v_R7,v_R8,v_PVE,v_PV1,v_PVT,v_PR1,v_PR3,v_PR5,v_PR7,v_PR8,v_Kext1,v_Kext2,v_cropHeight);

					///////////////////////////////////////////////////////////////////////////////////////////
				   //write out to temporary file in arrays
					char Crop_Name[100];
					sprintf(Crop_Name, "%s", v_CropName[CropType]);

					////////////////////////////////////////////////////////////////////////////////////////////

    				float PlantC = db_Yield[rrr][yyy][i] / db_GrainFraction[rrr][yyy][i];
					float LeafC = PlantC * db_LeafFraction[rrr][yyy][i];
					float ShootC = PlantC * db_ShootFraction[rrr][yyy][i];
					float RootC = PlantC * db_RootFraction[rrr][yyy][i];
					float PlantCN = 1.0 / (db_GrainFraction[rrr][yyy][i]/db_GrainCN[rrr][yyy][i] + 
						db_LeafFraction[rrr][yyy][i]/db_LeafCN[rrr][yyy][i] + 
						db_ShootFraction[rrr][yyy][i]/db_ShootCN[rrr][yyy][i] + 
						db_RootFraction[rrr][yyy][i]/db_RootCN[rrr][yyy][i]);
					float MaxPlantN = PlantC / PlantCN;					
					if(db_YrCropType[rrr][yyy][i]==0) MaxPlantN = 0.0;
					
					fprintf(fp, "%d  %s  %d  %d  %f  %d\n", db_YrCropType[rrr][yyy][i], Crop_Name, WinterCropFlag, LeftDays, db_Yield[rrr][yyy][i], db_HYr[rrr][yyy][i]);
					fprintf(fp, "%d  %d  %f  %f  %d\n", SeedDay, GrowDays, db_Residue[rrr][yyy][i], MaxPlantN, wwww);
					fprintf(fp, "%f  %f  %f  %f  %f\n", db_TreeAge[rrr][yyy][i], db_VegRate[rrr][yyy][i], 
						db_RepRate[rrr][yyy][i], db_PsnEff[rrr][yyy][i], db_PsnMax[rrr][yyy][i]);
					fprintf(fp, "%d\n", db_CoverCrop[rrr][yyy][i]);
					fprintf(fp, "%d\n", db_PerennialCrop[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f\n", db_GrainFraction[rrr][yyy][i], db_LeafFraction[rrr][yyy][i], db_ShootFraction[rrr][yyy][i], db_RootFraction[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f\n", db_GrainCN[rrr][yyy][i], db_LeafCN[rrr][yyy][i], db_ShootCN[rrr][yyy][i], db_RootCN[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f %f\n", db_TDD[rrr][yyy][i], db_Water[rrr][yyy][i], db_OptT[rrr][yyy][i], db_Nfix[rrr][yyy][i], db_Vascularity[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", db_Root1[rrr][yyy][i], db_Root2[rrr][yyy][i], db_AGResp1[rrr][yyy][i], db_AGResp2[rrr][yyy][i], db_VE[rrr][yyy][i], db_V1[rrr][yyy][i], db_VT[rrr][yyy][i], db_R1[rrr][yyy][i], db_R3[rrr][yyy][i], db_R5[rrr][yyy][i], db_R7[rrr][yyy][i], db_R8[rrr][yyy][i], db_PVE[rrr][yyy][i], db_PV1[rrr][yyy][i], db_PVT[rrr][yyy][i], db_PR1[rrr][yyy][i], db_PR3[rrr][yyy][i], db_PR5[rrr][yyy][i], db_PR7[rrr][yyy][i], db_PR8[rrr][yyy][i]);
					fprintf(fp, "%f %f %f\n", db_Kext1[rrr][yyy][i], db_Kext2[rrr][yyy][i], db_cropHeight[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f\n", db_cropGRate[rrr][yyy][i], db_Kext2[rrr][yyy][i], db_cropHeight[rrr][yyy][i]);
				}				
			}
			fclose (fp);
		///////////////////////////////////////////////////////////
		}
	}

    int CropNumbers;
	char Crop_Name[100];
    yr = 0;
    for (int i=1;i<=db_Rotation_Number;i++) 
	{
        kkk = 0;
        for (j = 1;j<=db_RotateSpan[i];j++) //total years within a rotation
		{
            yr++;
			kkk++;
        
            // Open output crop file---for linux compile
			
			sprintf(outname,"%s\\crop-%d",FCT100,yr);
			fcrop=fopen(outname, "w");
			if(fcrop==NULL) note(1, outname);            

			sprintf(fname,"%s\\cyc-%d_%d",FCT0,i,kkk);
			fpi=fopen(fname, "r");
			if (fpi==NULL) note(0, fname);
			            
			fscanf(fpi, "%d", &CropNumbers);
			fprintf(fcrop, "%d\n", CropNumbers);
	
            for (k = 1;k<=CropNumbers;k++) 
			{
				fscanf(fpi, "%d  %s  %d  %d  %f  %d", 
					&CYr[1].CropID, Crop_Name, &CYr[1].WCFlag, &CYr[1].Left, &CYr[1].Yield, 
					&CYr[1].HarYr);
				fscanf(fpi, "%d  %d  %f  %f  %d", 
					&CYr[1].SeedDay, &CYr[1].GrowDays, &CYr[1].LeftPrec, 
					&CYr[1].MaxPlanN, &CYr[1].CropOrder);
				fscanf(fpi, "%f  %f  %f  %f  %f", 
					&CYr[1].TreeAge, &CYr[1].GrowthVegetative, &CYr[1].GrowthReproductive, 
					&CYr[1].PsnEfficiency, &CYr[1].PsnMax);
				fscanf(fpi, "%d", &CYr[1].CoverCrop);
				fscanf(fpi, "%d", &CYr[1].PerennialCrop);

				fscanf(fpi, "%f %f %f %f", &CYr[1].Grain, &CYr[1].Leaf, &CYr[1].Straw, &CYr[1].Root);
				fscanf(fpi, "%f %f %f %f", &CYr[1].GrainCN, &CYr[1].LeafCN, &CYr[1].ShootCN, &CYr[1].RootCN);
				fscanf(fpi, "%f %f %f %f %f", &CYr[1].CropTDD, &CYr[1].WRuq, &CYr[1].OptT, 
					&CYr[1].CropNFix, &CYr[1].Vascularity);

				if(CYr[1].CropID==0) CYr[1].HarYr=1;

				CYr[1].WCFlag = 0;
				CYr[1].Left = 0;

				fprintf(fcrop, "%d  %s  %d  %d  %f  %d\n", 
				CYr[1].CropID, Crop_Name, CYr[1].WCFlag, CYr[1].Left, CYr[1].Yield, CYr[1].HarYr);
				fprintf(fcrop, "%d  %d  %f  %f  %d\n", 
				CYr[1].SeedDay, CYr[1].GrowDays, CYr[1].LeftPrec, 
				CYr[1].MaxPlanN, CYr[1].CropOrder);
				fprintf(fcrop, "%f  %f  %f  %f  %f\n", 
				CYr[1].TreeAge, CYr[1].GrowthVegetative, CYr[1].GrowthReproductive, 
				CYr[1].PsnEfficiency, CYr[1].PsnMax);
				fprintf(fcrop, "%d\n", CYr[1].CoverCrop);
				fprintf(fcrop, "%d\n", CYr[1].PerennialCrop);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].Grain, CYr[1].Leaf, CYr[1].Straw, CYr[1].Root);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].GrainCN, CYr[1].LeafCN, CYr[1].ShootCN, CYr[1].RootCN);
				fprintf(fcrop, "%f %f %f %f %f\n", CYr[1].CropTDD, CYr[1].WRuq, CYr[1].OptT, CYr[1].CropNFix, CYr[1].Vascularity);			
			}

            fclose (fpi);
            fclose (fcrop);
                        
            sprintf(fname,"%s\\ti-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\till-%d",FCT100,yr);
			FileCopy_1(fname,outname);

			sprintf(fname,"%s\\fe-%d_%d",FCT0,i,kkk);			
			sprintf(outname,"%s\\fert-%d",FCT100,yr);
			FileCopy_1(fname,outname);
      
			sprintf(fname,"%s\\ma-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\manu-%d",FCT100,yr);
			FileCopy_1(fname,outname);
           
           	sprintf(fname,"%s\\fl-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\flood-%d",FCT100,yr);
			FileCopy_1(fname,outname);
            
        	sprintf(fname,"%s\\ir-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\irri-%d",FCT100,yr);
			FileCopy_1(fname,outname);
            
            sprintf(fname,"%s\\pl-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\plastic-%d",FCT100,yr);
			FileCopy_1(fname,outname);

            sprintf(fname,"%s\\gr-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\graz-%d",FCT100,yr);
			FileCopy_1(fname,outname);

			sprintf(fname,"%s\\cut-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\cut-%d",FCT100,yr);
			FileCopy_1(fname,outname);

            if (kkk == db_CycleSpan[i]) kkk = 0;
        }
    }
    
	char F_INI[200];
	FILE *fpp;
	sprintf(F_INI, "%s\\Inputs\\cropini-1", OUTPUT);    
	fpp = fopen(F_INI, "w");
	if (fpp == NULL) note(1, F_INI); 
	fprintf(fpp, "%d\n", 0);
	fclose( fpp );
}

    return 0;
    
}

void ReadCropPara_2(int* v_CropID, char v_CropName[95][100], float* v_max_biomass_C, float* v_grain_fraction, float* v_leaf_fraction,
	float* v_leafstem_fraction, float* v_root_fraction, float* v_GrainCN,
	float* v_LeafCN, float* v_ShootCN, float* v_RootCN, float* v_WaterDemand, float* v_OptimumT,
	float* v_TDD, float* v_Nfixation, float* v_Vascularity, int* v_Perennial, float* v_TreeAge, float* v_Root1, float* v_Root2,
	float* v_VE, float* v_V1, float* v_VT, float* v_R1, float* v_R3, float* v_R5, float* v_R7, float* v_R8, float* v_PVE, float* v_PV1, float* v_PVT, float* v_PR1, float* v_PR3, float* v_PR5, float* v_PR7, float* v_PR8,
	float* v_Kext1, float* v_Kext2, float* v_cropHeight)
{//ReadCropPara1 is the sister function of this that is used for the tool side of code?
	char text[300];
	char CCrop[300];
	FILE *fCrop;
#ifdef CONSOLE
	sprintf(CCrop, "%s\\lib_crop\\Crop_parameters.txt", LIBRARY);//, CropType);
#else
	sprintf(CCrop, "%s\\Library\\lib_crop\\Crop_parameters.txt", ROOTDIR);//, CropType);
#endif
	//read in crop library names and parameters.
	fCrop = fopen(CCrop, "r");
	if(fCrop==NULL) note(0, CCrop);
	else
	{
		fgets(text, 300, fCrop);
		fgets(text, 300, fCrop);
		for(int i=0; i<=90; i++)
		{
			fscanf(fCrop, "%d %s", &v_CropID[i], v_CropName[i]);
			fscanf(fCrop, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f", &v_max_biomass_C[i], 
				&v_grain_fraction[i], &v_leaf_fraction[i], &v_leafstem_fraction[i], &v_root_fraction[i], 
				&v_GrainCN[i], &v_LeafCN[i], &v_ShootCN[i], &v_RootCN[i],
				&v_WaterDemand[i], &v_OptimumT[i], &v_TDD[i], &v_Nfixation[i], &v_Vascularity[i]);
			fscanf(fCrop, "%d", &v_Perennial[i]);//, &v_TreeAge[i]);
			if (v_Vascularity[i] == 0.0) v_Vascularity[i] = 1.5;//rooting depth
		}
		fclose(fCrop);
	}	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RecordManureFiles(void)
{
	char SF[300], TF[300];
	int m_FeedLots, i;
	char TotalFeedlots[300];
	FILE *TFL;

	for(int m_FeedlotYear=1; m_FeedlotYear<=years; m_FeedlotYear++)
	{
		sprintf(TotalFeedlots, "%s\\Inter\\TotalFeedLots_%d", OUTPUT, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "r");
		if(TFL==NULL) note(0, TotalFeedlots);
		fscanf(TFL, "%d", &m_FeedLots);
		fclose(TFL);

		sprintf(TF, "%s\\Inputs\\TotalFeedLots_%d", OUTPUT, m_FeedlotYear);
		FileCopy_1(TotalFeedlots, TF);

		for(i=0; i<=m_FeedLots; i++)
		{
			sprintf(SF, "%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
			sprintf(TF, "%s\\Inputs\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
			FileCopy_1(SF, TF);
		}
	}

	sprintf(SF, "%s\\Inter\\ManureLagoon.txt", OUTPUT);//
	sprintf(TF, "%s\\Inputs\\ManureLagoon.txt", OUTPUT);
	FileCopy_1(SF, TF);
	sprintf(SF, "%s\\Inter\\ManureCompost.txt", OUTPUT);
	sprintf(TF, "%s\\Inputs\\ManureCompost.txt", OUTPUT);
	FileCopy_1(SF, TF);
	sprintf(SF, "%s\\Inter\\ManureDigester.txt", OUTPUT);
	sprintf(TF, "%s\\Inputs\\ManureDigester.txt", OUTPUT);
	FileCopy_1(SF, TF);
	sprintf(SF, "%s\\Inter\\ManureField.txt", OUTPUT);
	sprintf(TF, "%s\\Inputs\\ManureField.txt", OUTPUT);
	FileCopy_1(SF, TF);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




int JulianDay(int month, int day)
{
    int i, JDay;
	int   Mday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if (month<1 ||month>12 || day<1 ||day>31) return -1;

    JDay = 0;
    for (int i14=1; i14< month; i14++)
	{
        JDay += Mday[i14];
	}
    JDay += day;
	return JDay;
}


int FileCopy_1(char *source, char *dest)
{
	FILE *fpi,*fpo;
	long flen,rt,num,adr;
	char *p;

	p=(char*)malloc(4096);
	if (p==NULL) {
		MessageBox(NULL,"No enough memory!","Running Error:",0);
		return -1;
	}

	fpi=fopen(source,"rb");
	if (fpi==NULL) 
	{
		CString note;
		note.Format("1. Source file does not exist: %s", source);
		AfxMessageBox(note);
		exit(0);
	}

	fpo=fopen(dest,"wb");
	if (fpo==NULL) {
		CString note;
		note.Format("2. Target file does not exist! %s", dest);
		AfxMessageBox(note);
		return -1;
	}
	
	flen=_filelength(_fileno(fpi));
	num=4096;
	adr=0;
	for (;;) {
		fseek(fpi,adr,SEEK_SET);
		fseek(fpo,adr,SEEK_SET);
		if (adr+num>flen) num=flen-adr;
		rt=fread(p,sizeof(char),num,fpi);
		rt=fwrite(p,sizeof(char),num,fpo);
		adr+=num;
		if (adr==flen) break;
	}
	fclose(fpi);
	fclose(fpo);
	free(p);
	return 0;
}

