#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "dndc_main.h"
#include <io.h>
#include <direct.h>
#include <math.h>
#include "dndc_tool.h"

extern Site_BaseInformation	IData;
extern StringArray	ClimateFilename;

void Toend(char *notes, char *FN);
float nSoca[6]={0.0,0.2,0.2,0.08,0.05,0.2};
float nSocb[6]={10.0,2.0,2.0,1.4,4.0,2.0};
int NutritionModelX, AllFarmFields=0;

void SaveDatatoFile(char *fname, int mode)
{
    int i, j, k, n, jjd, rrr;
	FILE *fpo;
	char Oname[255];
	
	int NNN, TillID[300], TillMonth[300], TillDay[300], TillMethod[300];
	int FertMonth[300], FertDay[300], FertMethod[300];
	float FertNitrate[300], FertAbi[300], FertUrea[300], FertAnh[300], FertAmNi[300], NH42SO4[300], NH42HPO4[300], FertDepth[300];
	int ManuMonth[300], ManuDay[300], ManuType[300], manu_method[300],ManureAppHour[300];
	float ManuAmount[300], ManuCN[300], ManuN[300], ManureDepth[300], ManureNH4[300], ManureNO3[300],ManureDM[300],ManurePH[300];
	int WeedMonth1[300], WeedDay1[300],WeedMonth2[300], WeedDay2[300];
	float CoverFraction[300];
	int FlooMonth1[300], FlooDay1[300], FlooMonth2[300], FlooDay2[300];
	float FlooN[300];
	int ShallowFlood[300];
	int IrrMode, IrriMonth[366], IrriDay[366];
	float IrrIndex, IrriAmount[366];
	int IrriMethod[366],CDrainA[366],DrainMonth[366],DrainDay[366],DrainMonth2[366],DrainDay2[366],TileIrriDays[366];
	float CDrainDepth[366];
	int GrazMonth1[300], GrazDay1[300], GrazMonth2[300], GrazDay2[300], Excreta[300];
	float GrazHour[300], Dairy[300], Beef[300], Pig[300], Horse[300], Sheep[300], AddFeed[300], FeedCN[300];
	char FertigationFile[200], m_ProfileName[250];
	int CutMonth[300], CutDay[300], CutPart[300], FertOption=0;
	float CutAmount[300], WaterGetherIndex, WaterLeakRate;
	float DayRelease[300], NIefficiency[300], NIduration[300];
	float UreaseEfficiency[300], UreaseDuration[300];
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	CString WT_file;
	int WaterControl;
	CString XFF;
	FILE *xff;

/*	CString CM;
	FILE *cm;
	CM.Format("%s\\Inter\\CropModel", OUTPUT);
	cm=fopen(CM, "r");
	if(cm==NULL)
	{
		CString notes;
		notes.Format("Can not open file %s", CM);
		AfxMessageBox(notes);
		exit(0);
	}
	else
	{
		fscanf(cm, "%d", &CropModel);
		fclose(cm);
		IData.CropModel = CropModel;
	}
*/
	if(IData.Sks<0.008) IData.Sks = 0.008;//sks default 0.015 was being set to 0.08
    
    sprintf(Oname,"%s.fn",fname);
    
    if ((fpo=sopen(fname,0))==NULL) return;//write
    
        // Save site
    fprintf(fpo,"Input_Parameters:\n");
    fprintf(fpo,"----------------------------------------\n");
	fprintf(fpo,"Site_info:\n");
    fprintf(fpo,"	Site_name:                  %s\n", IData.sitename);
    fprintf(fpo,"	Simulated_Year:             %d\n",IData.years);
    fprintf(fpo,"	Latitude:                   %6.3f\n",IData.latitude);
    fprintf(fpo,"	Daily_Record:               %6d\n",IData.ifdaily); 
	//fprintf(fpo,"Climate_file_mode           %6d\n",IData.if1File); 

#ifdef MANURE

	char ManureHouseName[300], ManurePenName[300], IndoorClimateFile[300];
	int AnimalType, m_ProductionOption, m_GroundSurface, m_Ventilation, m_Bedding, InputFormat, AnimalTypes;
	int m_BedType, BedMonth[366], BedDay[366];
	float m_BedApplications, m_BedCN, m_BedAmount, m_VentRate, m_AnimalHeads, m_FeedRate, m_FeedProtein, m_FeedTP, m_GroundArea;

	int PenAnimalType, PenGroundSurface, PenInputFormat, PenAnimalTypes;
	int PenBedType, PenBedApplications, PenBedMonth[366], PenBedDay[366];
	float PenAnimalHeads, PenBedCN, PenBedAmount, PenFeedRate, PenFeedProtein, PenFeedTP, PenGroundArea;
	
	CString ManureFieldName;
	int FieldInputFormat, FieldAnimalType, FieldGrazeTimes, IniMonth[366], IniDay[366], EndMonth[366], EndDay[366];
	float FieldHeads, FieldHrs, FieldArea;

	float LagoonCapacity, LagoonSurfaceArea, LagoonDays;
	float LagoonToField[10]={0.0,0.0}, LagoonToMarket[10]={0.0,0.0}, LagoonToRemain[10]={0.0,0.0}, LagoonManureAplDepth[10]={0.0,0.0};
	int LagoonCover, LagoonRain, LagoonDrainTimes, LagoonDrainMonth[10]={0,0}, LagoonDrainDay[10]={0,0}, LagoonManureAplMethod[10]={0,0}; 

	float m_CompostDensity, m_LitterAmount, m_LitterCN, m_ToField, m_ToMarket, m_Remain;
	float m_DigesterCH4, m_DigesterDays, m_DigesterToField, m_DigesterToMarket, m_DigesterRemain;
	int m_Temp, m_Flash, m_CompostCover, m_CompostRemoveTimes;
	int m_CompostRemoveMonth, m_CompostRemoveDay;
	float m_FlushWater, LiquidFraction;

	float m_Frequency, m_UC, m_UL, m_UD, m_UF, m_UR, m_FC, m_FL, m_FD, m_FF, m_FR;
	float m_Frequencyp, m_UCp, m_ULp, m_UDp, m_URp, m_FCp, m_FLp, m_FDp, m_FRp;
	float m_Frequencyf, m_USf, m_URf, m_FSf, m_FRf, m_FieldArea;
	
	fprintf(fpo,"----------------------------------------\n");
	fprintf(fpo,"Livestock_data:\n");		
	fprintf(fpo,"SimulatedYears				%d\n",IData.years);

	for(int m_FeedlotYear=1; m_FeedlotYear<=IData.years; m_FeedlotYear++)
	{

		int m_FeedLots;
		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Result\\inter\\TotalFeedLots_%d", ROOTDIR, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "r");
		if(TFL==NULL) note(0, TotalFeedlots);
		fscanf(TFL, "%d", &m_FeedLots);
		fclose(TFL);

		fprintf(fpo,"TotalFeedlots				%d\n",m_FeedLots);

		for(i=1; i<=m_FeedLots; i++)
		{
			CString CM;
			FILE* cm;

			fprintf(fpo,"Feedlot					%d\n", i);

			CM.Format("%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
			cm=fopen(CM, "r");
			if(cm==NULL) note(0, CM);
		
			fscanf(cm, "%d", &InputFormat);
			fprintf(fpo,"   FeedlotInputFormat			%d\n",InputFormat);
			if(InputFormat==1)
			{
				//Open a file to read ferd, feed data
				fscanf(cm, "%s", ManureHouseName);
				fprintf(fpo,"   HouseInputFileName			%s\n",ManureHouseName);
			}
			else if(InputFormat==2)
			{
				//Open a file to read ferd, feed data
				fscanf(cm, "%s", ManureHouseName);
				fprintf(fpo,"   HouseInputFileName			%s\n",ManureHouseName);
			}
			else if(InputFormat==3)
			{
				//Open a nutrition model
				fscanf(cm, "%d", &NutritionModelX);
				fprintf(fpo,"   HouseInputFileName			%d\n",NutritionModelX);
			}
			else
			{
				fscanf(cm, "%d", &AnimalTypes);
				fprintf(fpo,"   LivestockType			%d\n",AnimalTypes);
				
				fscanf(cm, "%d %f %f %f %f", &AnimalType, &m_AnimalHeads, &m_FeedRate, &m_FeedProtein, &m_FeedTP);
				fprintf(fpo,"   LivestockType_ID			%d\n",AnimalType);
				fprintf(fpo,"   Herd_heads				%f\n", m_AnimalHeads);
				fprintf(fpo,"   Feed:	\n");
				fprintf(fpo,"      Rate				%f\n", m_FeedRate);
				fprintf(fpo,"      CrudeProtein_percent		%f\n", m_FeedProtein);
				fprintf(fpo,"      Phosphorus_percent		%f\n", m_FeedTP);			
			}
			
			fscanf(cm, "%f %d", &m_GroundArea, &m_GroundSurface);//0 slatted floor; 1 conrete floor
			fscanf(cm, "%d  %f  %f %f", &m_BedType, &m_BedCN, &m_BedApplications, &m_BedAmount);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			fprintf(fpo,"   Floor:	\n");
			fprintf(fpo,"      SurfaceArea			%f\n", m_GroundArea);
			fprintf(fpo,"      SurfaceType			%d\n", m_GroundSurface);
			fprintf(fpo,"   Bedding:	\n");
			fprintf(fpo,"      MaterialType			%d\n", m_BedType);
			fprintf(fpo,"      Material_C/N			%f\n", m_BedCN);
			fprintf(fpo,"      ApplyFrequency			%f\n", m_BedApplications);
			fprintf(fpo,"      Amount				%f\n", m_BedAmount);			
				
			fscanf(cm, "%d  %f  %s", &m_Ventilation, &m_VentRate, IndoorClimateFile);// 0 natural, 1 fan, -1 IndoorClimateFile
			fprintf(fpo,"   Ventilation:	\n");
			fprintf(fpo,"      Type				%d\n", m_Ventilation);
			fprintf(fpo,"      Ven_rate				%f\n", m_VentRate);
			fprintf(fpo,"      IndoorClimateFile			%s\n", IndoorClimateFile);

			fscanf(cm, "%f", &m_Frequency);
			fscanf(cm, "%f %f %f %f %f", &m_UC, &m_UL, &m_UD, &m_UF, &m_UR);
			fscanf(cm, "%f %f %f %f %f", &m_FC, &m_FL, &m_FD, &m_FF, &m_FR);
			fscanf(cm, "%d %f %f", &m_Flash, &m_FlushWater, &LiquidFraction);

			fprintf(fpo,"   ManureRemoval:	\n");
			fprintf(fpo,"      Frequency				%f\n", m_Frequency);
			fprintf(fpo,"      Liquid_to_compost			%f\n", m_UC);
			fprintf(fpo,"      Liquid_to_lagoon			%f\n", m_UL);
			fprintf(fpo,"      Liquid_to_digester		%f\n", m_UD);
			fprintf(fpo,"      Liquid_to_field			%f\n", m_UF);
			fprintf(fpo,"      Liquid_remain			%f\n", m_UR);
			fprintf(fpo,"      Solid_to_compost			%f\n", m_FC);
			fprintf(fpo,"      Solid_to_lagoon			%f\n", m_FL);
			fprintf(fpo,"      Solid_to_digester			%f\n", m_FD);
			fprintf(fpo,"      Solid_to_field			%f\n", m_FF);
			fprintf(fpo,"      Solid_remain 			%f\n", m_FR);

			fprintf(fpo,"   Flushing:	\n");
			fprintf(fpo,"      FlushingLiquidType		%d\n",  m_Flash);
			fprintf(fpo,"      FlushingWaterVolume		%f\n",  m_FlushWater);
			fprintf(fpo,"   ManureLiquidFraction		%f\n",  LiquidFraction);
			
			fclose(cm);
		}

	}

	CString CM;
	FILE* cm;

	CM.Format("%s\\Inter\\ManureLagoon.txt", OUTPUT);
	cm=fopen(CM, "r");
	if(cm==NULL) note(0, CM);
	
	fscanf(cm, "%f %f %d %d %d", &LagoonCapacity, &LagoonSurfaceArea, &LagoonCover,	&LagoonRain, &LagoonDrainTimes);
	
	fprintf(fpo,"Lagoon				\n");
	fprintf(fpo,"   Capacity				%f\n", LagoonCapacity);
	fprintf(fpo,"   SurfaceArea				%f\n", LagoonSurfaceArea);
	fprintf(fpo,"   Coverage				%d\n", LagoonCover);
	fprintf(fpo,"   RainfallReceival		%d\n", LagoonRain);
	fprintf(fpo,"   SlurryRemovalTimes		%d\n", LagoonDrainTimes);

	for(i=1; i<=LagoonDrainTimes; i++)
	{
		fscanf(cm, "%d %d %f %f %f", &LagoonDrainMonth[i], &LagoonDrainDay[i], &LagoonToField[i], &LagoonToMarket[i], &LagoonToRemain[i]);
		fscanf(cm, "%d %f\n", &LagoonManureAplMethod[i], LagoonManureAplDepth[i]);
	
		fprintf(fpo,"   Slurry_drain_month		%d\n", LagoonDrainMonth[i]);
		fprintf(fpo,"   Slurry_drain_day		%d\n", LagoonDrainDay[i]);
		fprintf(fpo,"   Slurry_to_field			%f\n", LagoonToField[i]);
		fprintf(fpo,"   Slurry_to_digester		%f\n", LagoonToMarket[i]);
		fprintf(fpo,"   Slurry_remain			%f\n", LagoonToRemain[i]);
		fprintf(fpo,"   SlurryApplicationMethod		%d\n", LagoonManureAplMethod[i]);
		fprintf(fpo,"   SlurryApplicationDepth		%f\n", LagoonManureAplDepth[i]);
		
	}	
	
	fclose(cm);

	CString SF;
	FILE* sf;
	SF.Format("%s\\Inter\\ManureCompost.txt", OUTPUT);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);
	fscanf(sf, "%f  %d  %d  %f  %f", &m_CompostDensity, &m_CompostCover, &m_CompostRemoveTimes, &m_LitterAmount, &m_LitterCN);    
		
	fprintf(fpo,"Compost				\n");
	fprintf(fpo,"   Porosity				%f\n", m_CompostDensity); 
	fprintf(fpo,"   Coverage				%d\n", m_CompostCover);
	fprintf(fpo,"   RemovalTimes			%d\n", m_CompostRemoveTimes); 
	fprintf(fpo,"   AdditiveAmount			%f\n", m_LitterAmount); 
	fprintf(fpo,"   Additive_C/N				%f\n", m_LitterCN);
	
	for(i=1;i<=m_CompostRemoveTimes;i++)
	{
		fscanf(sf, "%d %d %f  %f  %f", &m_CompostRemoveMonth, &m_CompostRemoveDay, &m_ToField, &m_ToMarket, &m_Remain);
		fprintf(fpo,"   Remove_month			%d\n", m_CompostRemoveMonth);
		fprintf(fpo,"   Remove_Day				%d\n", m_CompostRemoveDay);		
		fprintf(fpo,"   Manure_to_field			%f\n", m_ToField);
		fprintf(fpo,"   Manure_to_market		%f\n", m_ToMarket);
		fprintf(fpo,"   Manure_remain			%f\n", m_Remain);
	}
	fclose(sf);
	
	SF.Format("%s\\Inter\\ManureDigester.txt", OUTPUT);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0,SF);
	fscanf(sf, "%d  %f  %f", &m_Temp, &m_DigesterCH4, &m_DigesterDays);    
	fscanf(sf, "%f  %f  %f", &m_ToField, &m_ToMarket, &m_Remain);	
	
	fprintf(fpo,"AnaerobicDigester				\n");
	fprintf(fpo,"   Thermo_type				%d\n", m_Temp); 
	fprintf(fpo,"   MethaneProductivity			%f\n", m_DigesterCH4);
	fprintf(fpo,"   RetentionDays			%f\n", m_DigesterDays);
	fprintf(fpo,"   Manure_to_field			%f\n", m_ToField);
	fprintf(fpo,"   Manure_to_lagoon			%f\n", m_ToMarket);
	fprintf(fpo,"   Manure_remain			%f\n", m_Remain);
	fclose(sf);

	CM.Format("%s\\Inter\\ManureField.txt", OUTPUT);
	sf=fopen(CM, "r");
	if(sf==NULL) note(0,CM);
	fscanf(sf, "%f", &m_FieldArea);
	fclose(sf);

	if(m_FieldArea<=0.0) m_FieldArea = 1.0;
	
	fprintf(fpo,"LandApplication				\n");
	fprintf(fpo,"   Land_area				%f\n", m_FieldArea);

	int ManuCropType, jd, TotalFarmYears;
	float ManuCropArea, ManuFraction;
	
	XFF.Format("%s\\inter\\ManureFieldCrops", OUTPUT);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(1,XFF);
	fscanf(xff, "%d %d", &AllFarmFields, &TotalFarmYears);
	fprintf(fpo,"   CroppingSystems			%d\n", AllFarmFields);
	for(i=1;i<=AllFarmFields;i++)
	{
		fscanf(xff, "%d  %d  %f  %f", &jd, &ManuCropType, &ManuCropArea, &ManuFraction);
		fprintf(fpo,"      CroppingSystem			%d\n", i);
		fprintf(fpo,"      CropType				%d\n", ManuCropType);
		fprintf(fpo,"      FieldArea				%f\n", ManuCropArea);
		fprintf(fpo,"      ManureShareFraction		%f\n", ManuFraction);
	}
	fclose(xff);

/*	if(FieldArea>0.0)
	{
		CM.Format("%s\\ManureFieldAll.txt", INTER);
		sf=fopen(CM, "w");
		if(sf==NULL) note(1, CM);
		fprintf(sf, "%d %f\n", AllFarmFields, m_FieldArea);
		fclose(sf);
	}*/
	
#endif
        // Climate data
    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Climate_data:\n");
	fprintf(fpo,"	Climate_Data_Type:          %d\n",IData.ClimateFileType);
    fprintf(fpo,"	NO3NH4_in_Rainfall          %8.4f\n",IData.NO3NH4_Rainfall);
    fprintf(fpo,"	NH3_of_Atmosphere           %8.4f\n",IData.NH3_Atmosphere);
	fprintf(fpo,"	BaseCO2_of_Atmosphere       %8.4f\n",IData.BaseCO2);
    fprintf(fpo,"	Climate_file_count=         %d\n",IData.ClimateFileNumber);
    for (i = 0; i<IData.ClimateFileNumber;i++) {
        fprintf(fpo,"    %d   %s\n",i + 1, ClimateFilename.get(i + 1));;
    }
	fprintf(fpo,"	Climate_file_mode           %6d\n",IData.if1File);//new
	fprintf(fpo,"	CO2_increase_rate           %f\n",IData.CO2IncreaseRate);//new
    
        // Soil parameter
    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Soil_data:\n");
    fprintf(fpo,"	Soil_Texture             %2d\n",IData.Soil_Texture);
    fprintf(fpo,"	Landuse_Type             %2d\n",IData.Soil_landuse);
    fprintf(fpo,"	Density                  %8.5f\n",IData.Soil_Density);
    fprintf(fpo,"	Soil_pH                  %8.5f\n",IData.Soil_pH);
    fprintf(fpo,"	SOC_at_Surface           %8.5f\n",IData.Soil_OCatSurface); 
    fprintf(fpo,"	Clay_fraction            %8.5f\n",IData.Soil_Clay);
    fprintf(fpo,"	BypassFlow               %8.5f\n",IData.Soil_BypassFlow);
    fprintf(fpo,"	Litter_SOC               %8.5f\n",IData.Soil_Litter);
    fprintf(fpo,"	Humads_SOC               %8.5f\n",IData.Soil_humads);
    fprintf(fpo,"	Humus_SOC                %8.5f\n",IData.Soil_humus);
    fprintf(fpo,"	Soil_NO3(-)(mgN/kg)      %8.5f\n",IData.Soil_NO3);
    fprintf(fpo,"	Soil_NH4(+)(mgN/kg)      %8.5f\n",IData.Soil_NH4);
    fprintf(fpo,"	Soil_PassiveCN           %8.5f\n",IData.PassiveCCN);
    fprintf(fpo,"	Lateral_influx_index     %8.5f\n",IData.LateralInflux);
	fprintf(fpo,"	Field_capacity           %f\n",IData.Fldcap); 
	fprintf(fpo,"	Wilting_point            %f\n",IData.Wiltpt); 	
	fprintf(fpo,"	Hydro_conductivity       %f\n",IData.Sks);
	fprintf(fpo,"	Soil_porosity            %f\n",IData.Soil_Porosity);	
	fprintf(fpo,"	SOC_profile_A            %f\n",IData.SOCa);
	fprintf(fpo,"	SOC_profile_B            %f\n",IData.SOCb);
	fprintf(fpo,"	DC_litter_factor         %f\n",IData.DClitter);
	fprintf(fpo,"	DC_humads_factor         %f\n",IData.DChumads);
	fprintf(fpo,"	DC_humus_factor          %f\n",IData.DChumus);
	fprintf(fpo,"	Humad_CN                 %f\n",IData.HumadCN);
	fprintf(fpo,"	Humus_CN                 %f\n",IData.HumusCN);
	fprintf(fpo,"	Soil_PassiveC            %f\n",IData.PassiveC);
	fprintf(fpo,"	Soil_microbial_index     %f\n",IData.Soil_MicrobioIndex);	
	fprintf(fpo,"	Highest_WT_depth         %f\n",IData.HighestWT);
	fprintf(fpo,"	Depth_WRL_m              %f\n",IData.Soil_WaterObstructLayer);
    fprintf(fpo,"	Slope                    %f\n",IData.slope);  
	fprintf(fpo,"	Salinity                    %f\n",IData.Soil_Quality);  
	fprintf(fpo,"	SCS_curve_use               %d\n",IData.SCSuse);
	fprintf(fpo,"	Deep_WaterPoolBD            %f\n",IData.WaterPoolBD);
	fprintf(fpo,"	Profile_Type             %f\n",IData.ProfileType);//prints out soil profile type
	fprintf(fpo,"	Profile_File_Name             %f\n",IData.ProfileFileName);//prints out soil profileName

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CString FCT30;
	 
#ifdef MANURE	
			
/*	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d", &AllFarmFields);
	fclose(xff);
*/
	//fprintf(fpo,"Farm_mode					%d %d\n",1, AllFarmFields);
#else
	AllFarmFields = 1;		
	//fprintf(fpo,"Farm_mode					%d %d\n",0, 1);
#endif

for(int CSL=1; CSL<=AllFarmFields; CSL++)
{
#ifdef MANURE
	FCT30.Format("%s_%d", INTERMANAGE, CSL);
#else
	FCT30.Format("%s_1", INTERMANAGE);
#endif

	int yyy;
	char DB[300];
	FILE *db;

	sprintf(DB, "%s\\CropRotation.txt", FCT30);
	db=fopen(DB, "r");
	if(db==NULL) note(0,DB);
	fscanf(db, "%d", &IData.db_Rotation_Number);
	fclose(db);
	
	for(rrr=1; rrr<=IData.db_Rotation_Number; rrr++)
	{
		
		sprintf(DB, "%s\\CropRotation_%d.txt", FCT30, rrr);//read: SaveDatatoFile
		db=fopen(DB, "r");
		if(db==NULL) note(0,DB);
		fscanf(db, "%d %d %d", &IData.db_RotationID[rrr], &IData.db_RotateSpan[rrr], &IData.db_CycleSpan[rrr]);
		fclose(db);
		
		for(yyy=1; yyy<=IData.db_CycleSpan[rrr]; yyy++)
		{
			//DB.Format("%s\\inter\\CropRotation_%d_%d.txt", OUTPUT, rrr, yyy);
			sprintf(DB, "%s\\CropRotation_%d_%d.txt", FCT30, rrr, yyy);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &IData.db_YrCrops[rrr][yyy]);

			for(int ccc=1; ccc<=IData.db_YrCrops[rrr][yyy]; ccc++)
			{
					fscanf(db, "%d %d", &IData.db_YrCropOrder[rrr][yyy][ccc], &IData.db_YrCropType[rrr][yyy][ccc]);
					fscanf(db, "%d %d", &IData.db_PMonth[rrr][yyy][ccc], &IData.db_PDay[rrr][yyy][ccc]);
					fscanf(db, "%d %d", &IData.db_HMonth[rrr][yyy][ccc], &IData.db_HDay[rrr][yyy][ccc]);
					fscanf(db, "%d", &IData.db_HYr[rrr][yyy][ccc]);
					fscanf(db, "%f %f", &IData.db_Residue[rrr][yyy][ccc], &IData.db_Yield[rrr][yyy][ccc]);
					fscanf(db, "%f %d", &IData.db_RepRate[rrr][yyy][ccc], &IData.db_Transplant[rrr][yyy][ccc]);
					fscanf(db, "%f %f", &IData.db_PsnEff[rrr][yyy][ccc], &IData.db_PsnMax[rrr][yyy][ccc]);
					fscanf(db, "%f", &IData.db_TreeAge[rrr][yyy][ccc]);
					fscanf(db, "%d", &IData.db_CoverCrop[rrr][yyy][ccc]);
					fscanf(db, "%d", &IData.db_PerennialCrop[rrr][yyy][ccc]);

					fscanf(db, "%f %f %f %f", &IData.db_GrainFraction[rrr][yyy][ccc], &IData.db_LeafFraction[rrr][yyy][ccc], &IData.db_ShootFraction[rrr][yyy][ccc], &IData.db_RootFraction[rrr][yyy][ccc]);
					fscanf(db, "%f %f %f %f", &IData.db_GrainCN[rrr][yyy][ccc], &IData.db_LeafCN[rrr][yyy][ccc], &IData.db_ShootCN[rrr][yyy][ccc], &IData.db_RootCN[rrr][yyy][ccc]);
					fscanf(db, "%f %f %f %f %f", &IData.db_TDD[rrr][yyy][ccc], &IData.db_Water[rrr][yyy][ccc], &IData.db_OptT[rrr][yyy][ccc], &IData.db_Nfix[rrr][yyy][ccc], &IData.db_Vascularity[rrr][yyy][ccc]);
					fscanf(db, "%f %f %f %f", &IData.db_TreeAge[rrr][yyy][ccc], &IData.db_TreeCurrentAge[rrr][yyy][ccc], &IData.db_TreeLeafMax[rrr][yyy][ccc], &IData.db_TreeLeafMin[rrr][yyy][ccc]);
					fscanf(db, "%d %f", &IData.db_RootShape[rrr][yyy][ccc], &IData.db_GrainFill[rrr][yyy][ccc]);
			}
			fclose(db);
		}
	}

    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Crop_data:\n");
    fprintf(fpo,"Rotation_Number=            %d\n",IData.db_Rotation_Number);
    for (rrr = 1; rrr<=IData.db_Rotation_Number;rrr++) 
	{
		fprintf(fpo,"  Rotation_ID=              %d\n",rrr);
        fprintf(fpo,"  Totalyear=                %d\n",	IData.db_RotateSpan[rrr]);
        fprintf(fpo,"  Years_Of_A_Cycle=         %d\n", IData.db_CycleSpan[rrr]);
        for (j = 1; j<=IData.db_CycleSpan[rrr];j++) 
		{
			fprintf(fpo,"    YearID_of_a_cycle=      %d\n",j);

            //n = IData.db_YrCrops[i][j];

            fprintf(fpo,"    Crop_total_Number=      %d\n",IData.db_YrCrops[rrr][j]); 
            for (k = 1; k<= IData.db_YrCrops[rrr][j];k++)
			{
				fprintf(fpo,"      Crop_ID=              %d\n",k);
                fprintf(fpo,"        Crop_Type=          %d\n",IData.db_YrCropType[rrr][j][k]);
                fprintf(fpo,"        Plant_time=         %d %d\n", IData.db_PMonth[rrr][j][k], IData.db_PDay[rrr][j][k]);
				fprintf(fpo,"        Harvest_time=       %d %d\n",IData.db_HMonth[rrr][j][k], IData.db_HDay[rrr][j][k]);
                fprintf(fpo,"        Year_of_harvest=    %d\n",IData.db_HYr[rrr][j][k]);
                fprintf(fpo,"        Ground_Residue=     %f\n",IData.db_Residue[rrr][j][k]); 
                fprintf(fpo,"        Yield=              %f\n",IData.db_Yield[rrr][j][k]);

				fprintf(fpo,"        Leaf_fraction=      %f\n",IData.db_LeafFraction[rrr][j][k]);
				fprintf(fpo,"        Leaf_CN=            %f\n",IData.db_LeafCN[rrr][j][k]);
				fprintf(fpo,"        Psn_efficiency=     %f\n",IData.db_PsnEff[rrr][j][k]);
				fprintf(fpo,"        Transplant=         %d\n",IData.db_Transplant[rrr][j][k]);
				fprintf(fpo,"        TreeAge=            %f\n",IData.db_TreeAge[rrr][j][k]);
				fprintf(fpo,"        Cover_crop=         %d\n",IData.db_CoverCrop[rrr][j][k]);
				fprintf(fpo,"        Perennial_crop=     %d\n",IData.db_PerennialCrop[rrr][j][k]);

				fprintf(fpo,"        Grain_fraction=     %f\n",IData.db_GrainFraction[rrr][j][k]);
				fprintf(fpo,"        Stem_fraction=      %f\n",IData.db_ShootFraction[rrr][j][k]);
				fprintf(fpo,"        Root_fraction=      %f\n",IData.db_RootFraction[rrr][j][k]);
				fprintf(fpo,"        Grain_CN=           %f\n",IData.db_GrainCN[rrr][j][k]);
				fprintf(fpo,"        Stem_CN=            %f\n",IData.db_ShootCN[rrr][j][k]);
				fprintf(fpo,"        Root_CN=            %f\n",IData.db_RootCN[rrr][j][k]);
				fprintf(fpo,"        TDD=                %f\n",IData.db_TDD[rrr][j][k]);
				fprintf(fpo,"        Water_requirement=  %f\n",IData.db_Water[rrr][j][k]);
				fprintf(fpo,"        Optimum_temp=       %f\n",IData.db_OptT[rrr][j][k]);
				fprintf(fpo,"        N_fixation=         %f\n",IData.db_Nfix[rrr][j][k]);
				fprintf(fpo,"        Vascularity=        %f\n",IData.db_Vascularity[rrr][j][k]);

				fprintf(fpo,"        TreeAge=            %f\n",IData.db_TreeAge[rrr][j][k]);
				fprintf(fpo,"        TreeCurrentAge=     %f\n",IData.db_TreeCurrentAge[rrr][j][k]);
				fprintf(fpo,"        TreeLeafMax=        %f\n",IData.db_TreeLeafMax[rrr][j][k]);
				fprintf(fpo,"        TreeLeafMin=        %f\n",IData.db_TreeLeafMin[rrr][j][k]);
				fprintf(fpo,"        RootShape=        %d\n",IData.db_RootShape[rrr][j][k]);
				fprintf(fpo,"        GrainFill=        %f\n",IData.db_GrainFill[rrr][j][k]);
            }
            

			//DB.Format("%s\\inter\\CropTill_%d_%d.txt", OUTPUT, rrr, j);
			sprintf(DB, "%s\\CropTill_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &NNN);
			for(k=1; k<=NNN; k++)
			{
				TillID[k] = k;
				fscanf(db, "%d %d %d", &TillMonth[k], &TillDay[k], &TillMethod[k]);
			}
			fclose(db);

            fprintf(fpo,"    Tillage_number=         %d\n",NNN); 
            for (k = 1; k<= NNN; k++) 
			{
                fprintf(fpo,"      Tillage_ID=           %d\n",k); 
                fprintf(fpo,"        Month/Day/method=   %d %d %d\n",TillMonth[k], TillDay[k], TillMethod[k]); 
            }
            
			//DB.Format("%s\\inter\\CropFert_%d_%d.txt", OUTPUT, rrr, j);
			sprintf(DB, "%s\\CropFert_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &n);
			if(n==-1)
			{
				fscanf(db, "%s", FertigationFile);
			}
			else
			{
				for(i=1; i<=n; i++)
				{
					fscanf(db, "%d %d %d", &FertMonth[i], &FertDay[i], &FertMethod[i]);
					fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[i], &FertAbi[i], &FertUrea[i], &FertAnh[i], 
						&FertAmNi[i], &NH42SO4[i], &NH42HPO4[i], &FertDepth[i]);
					fscanf(db, "%f %f %f %f %f", &DayRelease[i], &NIefficiency[i], &NIduration[i],
						&UreaseEfficiency[i], &UreaseDuration[i]);
				}
				fscanf(db, "%d", &FertOption);
			}
			fclose(db);

            fprintf(fpo,"    Fertil_number=          %d\n",n);
			if(n==-1)
			{
				fprintf(fpo,"      fertigation_file=     %s\n",FertigationFile); 
			}
			else
			{
				for (k = 1; k<=n;k++) 
				{
					fprintf(fpo,"      fertilization_ID=     %d\n",k); 
					fprintf(fpo,"        Month/Day/method=   %d %d %d\n",FertMonth[k], FertDay[k], FertMethod[k]); 
					fprintf(fpo,"        Depth=              %f\n",FertDepth[k]); 
					fprintf(fpo,"        Nitrate=            %f\n",FertNitrate[k]); 
					fprintf(fpo,"        AmmBic=             %f\n",FertAbi[k]); 
					fprintf(fpo,"        Urea=               %f\n",FertUrea[k]); 
					fprintf(fpo,"        Anh=                %f\n",FertAnh[k]); 
					fprintf(fpo,"        NH4NO3=             %f\n",FertAmNi[k]);
					fprintf(fpo,"        NH42SO4=            %f\n",NH42SO4[k]); 
					fprintf(fpo,"        NH4HPO4=            %f\n",NH42HPO4[k]); 
					fprintf(fpo,"      Release_rate=         %f\n",DayRelease[k]); 
					fprintf(fpo,"      Inhibitor_efficiency= %f\n",NIefficiency[k]); 
					fprintf(fpo,"      Inhibitor_duration=   %f\n",NIduration[k]); 
					fprintf(fpo,"      Urease_efficiency= %f\n",UreaseEfficiency[k]); 
					fprintf(fpo,"      Urease_duration=   %f\n",UreaseDuration[k]); 

					
					
				}
				fprintf(fpo,"      FertilizationOption=  %d\n",FertOption); 
				
			}

			//DB.Format("%s\\inter\\CropManu_%d_%d.txt", OUTPUT, rrr, j);
			sprintf(DB, "%s\\CropManu_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &n);
			for(i=1; i<=n; i++)
				{
					fscanf(db, "%d %d", &ManuMonth[i], &ManuDay[i]);
					fscanf(db, "%f %f %d %d %f", &ManuAmount[i], &ManuCN[i], &ManuType[i], &manu_method[i], &ManureDepth[i]);
					fscanf(db, "%f %f %f %d %f %f", &ManuN[i], &ManureNH4[i], &ManureNO3[i], &ManureAppHour[i], &ManureDM[i], &ManurePH[i]);
				}
			fclose(db);

            fprintf(fpo,"    Manure_number=          %d\n",n);
            for (k = 1; k<= n; k++) {
				fprintf(fpo,"      Manure_ID=            %d\n",k); 
                fprintf(fpo,"        Month/Day=          %d %d\n",ManuMonth[k], ManuDay[k]);
                fprintf(fpo,"        Amount/C|N_ratio=   %f %f\n",ManuAmount[k], ManuCN[k]);
				fprintf(fpo,"        Type=               %d\n", ManuType[k]);
				fprintf(fpo,"        Method=             %d\n", manu_method[k]);
				fprintf(fpo,"        Depth=              %f\n", ManureDepth[k]);//Brian
            }
                
			int WeedOption, PlasticM1, PlasticD1,PlasticM2, PlasticD2;
		
			sprintf(DB, "%s\\CropPlastic_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d %d", &n, &WeedOption);
			for(i=1; i<=n; i++)
				{
					fscanf(db, "%d %d", &WeedMonth1[i], &WeedDay1[i]);
					fscanf(db, "%d %d", &WeedMonth2[i], &WeedDay2[i]);
					fscanf(db, "%f", &CoverFraction[i]);

					//WeedMonth1[i] = JulianDay(PlasticM1, PlasticD1);
					//WeedDay1[i] = JulianDay(PlasticM2, PlasticD2);
				}
			fclose(db);
			
            fprintf(fpo,"    Plastic_film=            %d\n",n);
            fprintf(fpo,"    Ventilation=             %d\n",WeedOption); 
            for (k = 1; k<= n;k++) 
			{
                fprintf(fpo,"      Plastic_ID=           %d\n",k); 
                fprintf(fpo,"      Start/End=          %d %d\n",WeedMonth1[k], WeedDay1[k]); 
				fprintf(fpo,"      Start/End=          %d %d\n",WeedMonth2[k], WeedDay2[k]);
				fprintf(fpo,"      CoverFraction=      %f\n",CoverFraction[k]);
            }
                
			
			//DB.Format("%s\\inter\\CropFloo_%d_%d.txt", OUTPUT, rrr, j);
			float FloodWaterN;

			sprintf(DB, "%s\\CropFloo_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d %f %d %f", &n, &FloodWaterN, &WaterControl, &WaterLeakRate);
			for(i=1; i<=n; i++)
			{
				fscanf(db, "%d %d", &FlooMonth1[i], &FlooDay1[i]);
				fscanf(db, "%d %d", &FlooMonth2[i], &FlooDay2[i]);
				fscanf(db, "%f", &FlooN[i]);
				fscanf(db, "%d", &ShallowFlood[i]);
			}
			
			fscanf(db, "%f", &WaterGetherIndex);				
			fscanf(db, "%s", WT_file);
			fscanf(db, "%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
												&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);
			fclose(db);
           
            fprintf(fpo,"    Flood_number=           %d\n",n); 
            fprintf(fpo,"    FloodWaterN=            %f\n",FloodWaterN);
			fprintf(fpo,"    Water_control=          %d\n",WaterControl);
			fprintf(fpo,"    Leak_rate=              %f\n",WaterLeakRate);
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Flooding_ID=          %d\n",k); 
                fprintf(fpo,"        Flood_Month/Day=    %d %d\n",FlooMonth1[k], FlooDay1[k]);
                fprintf(fpo,"        Drain_Month/Day=    %d %d\n",FlooMonth2[k], FlooDay2[k]);
				fprintf(fpo,"        Water_N=            %f\n",FlooN[k]);
				fprintf(fpo,"        Shallow_flood=       %d\n",ShallowFlood[k]);
			}
			fprintf(fpo,"        Water_gather=       %f\n", WaterGetherIndex);				
			fprintf(fpo,"        WT_file=            %s\n", WT_file);
			fprintf(fpo,"        Empirical_parameters= %f %f %f %f %f %f\n", m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, 
												m_SurfOutflowIntensity, m_GroundOutflowIntensity);
		
			sprintf(DB, "%s\\CropIrri_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d %d %f %d", &n, &IrrMode, &IrrIndex, &IrriMethod[0]);
			for(i=1; i<=n; i++)
				{
					fscanf(db, "%d %d", &IrriMonth[i], &IrriDay[i]);
					fscanf(db, "%f %d", &IrriAmount[i], &IrriMethod[i],&TileIrriDays[i]);
				}
			fclose(db);
            
            fprintf(fpo,"    Irrigation_number=      %d\n",n); 
            fprintf(fpo,"    Irrigation_type=        %d\n",IrrMode);
			fprintf(fpo,"    Irrigation_Index=       %f\n",IrrIndex); 
			fprintf(fpo,"    Irrigation_Method=       %d\n",IrriMethod[0]);
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Irrigation_ID=        %d\n",k); 
                fprintf(fpo,"        Irr_Month/Day=      %d %d\n",IrriMonth[k], IrriDay[k]); 
                fprintf(fpo,"        Water_amount/Method=    %f %d %d\n",IrriAmount[k], IrriMethod[k],TileIrriDays[k]); 
            }

			//DB.Format("%s\\inter\\CropGraz_%d_%d.txt", OUTPUT, rrr, j);
			sprintf(DB, "%s\\CropGraz_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &n);
				for(i=1; i<=n; i++)
				{
					fscanf(db, "%d %d", &GrazMonth1[i], &GrazDay1[i]);
					fscanf(db, "%d %d", &GrazMonth2[i], &GrazDay2[i]);
					fscanf(db, "%f", &GrazHour[i]);
					fscanf(db, "%f %f %f %f %f", &Dairy[i], &Beef[i], &Pig[i], &Sheep[i], &Horse[i]);
					fscanf(db, "%f %f %d", &AddFeed[i], &FeedCN[i], &Excreta[i]);
				}
			fclose(db);
            
            fprintf(fpo,"    Grazing_number=           %d\n",n); 
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Grazing_ID=           %d\n",k); 
                fprintf(fpo,"        Start_Month/Day=    %d %d\n",GrazMonth1[k], GrazDay1[k]);
				fprintf(fpo,"        End_Month/Day=      %d %d\n",GrazMonth2[k], GrazDay2[k]);
                fprintf(fpo,"        Dairy_Head_per_ha= %f\n",Dairy[k]);
				fprintf(fpo,"        Beef_Head_per_ha= %f\n",Beef[k]);
				fprintf(fpo,"        Pig_Head_per_ha= %f\n",Pig[k]);
				fprintf(fpo,"        Sheep_Head_per_ha_= %f\n",Sheep[k]);
				fprintf(fpo,"        Horse_Head_per_ha_= %f\n",Horse[k]);				
				fprintf(fpo,"        Graz_Hours_Per_day= %f\n",GrazHour[k]);
				fprintf(fpo,"        Additional_feed= %f\n",AddFeed[k]);
				fprintf(fpo,"        Feed_C/N= %f\n",FeedCN[k]);
				fprintf(fpo,"        Excreta= %d\n",Excreta[k]);
            }

			//DB.Format("%s\\inter\\GrassCut_%d_%d.txt", OUTPUT, rrr, j);
			sprintf(DB, "%s\\GrassCut_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &n);
				for(i=1; i<=n; i++)
				{
					fscanf(db, "%d %d", &CutMonth[i], &CutDay[i]);
					fscanf(db, "%f", &CutAmount[i]);
					fscanf(db, "%d", &CutPart[i]);
				}
			fclose(db);
           
            fprintf(fpo,"    Cut_number=           %d\n",n); 
            for (k = 1; k<= n;k++) 
			{
                fprintf(fpo,"      Cut_ID=           %d\n",k); 
                fprintf(fpo,"        Cut_Month/Day=    %d %d\n",CutMonth[k], CutDay[k]);
				fprintf(fpo,"        Cut_amount= %f\n",CutAmount[k]);
				fprintf(fpo,"        Cut_part= %d\n",CutPart[k]);
            }

        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	fprintf(fpo,"Crop_model_approach         %d\n", 0);//IData.CropModel);
	
	if(IData.SCSuse==1)
	{
		float m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage;

		char scs[120];
		FILE *scspara;
		sprintf(scs,"%s\\Inputs\\scspara", OUTPUT);
		scspara = fopen(scs, "r");
		if(scspara==NULL) note(0, scs);
		fscanf(scspara, "%f %f %f %f %f %f\n", &m_CN, &m_RoughLand, &m_RoughChannel, &m_ChannelSlope, &m_ChannelLength, &m_LandManage);
		fclose(scspara);
		
		fprintf(fpo, "%f %f %f %f %f %f\n", m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage);	
	}

	
	char LB[200];
	FILE* ddb;
	int US;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "r");
	if(ddb==NULL) note(0, LB);
	fscanf(ddb, "%d", &US);
	fclose(ddb);

	fprintf(fpo, "Unit:			%d\n", US);

    fclose (fpo);
}

void ReadInputDatafromDND(char *fname, int UseID)
{
	int  i, j, k, cropn, MissFlag=0, note_flag=0;
	int floon, ShallowFlood, WaterControl, FlooMonth1, FlooDay1, FlooMonth2, FlooDay2;
	float FlooN, WaterGetherIndex, WaterLeakRate;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex,m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	float FloodWaterN;
	char notes[255],tmp[255],ffname[300];
    FILE *fp;

	CString txt;

	//if(UseID==10) sprintf(ffname, "%s", fname);
	//else sprintf(ffname, "%s", fname);
	sprintf(ffname, "%s", fname);

	fp=sopen(ffname,"r");
	if(fp==NULL) note(0, ffname);
	
        // Initial IData class
	//memset(&IData,0,sizeof(Site_BaseInformation));
	Site_BaseInformation();
	ClimateFilename.clear();

	int Line=1;

// Read site
fscanf(fp,"%s",notes);
if(strcmp(notes, "DNDC_Input_Parameters")==0)
{
	fclose(fp);
	ReadDNDfile(fname, 0);
}
else 
{	
		    
		//Site data:
	fscanf(fp,"%s",notes);//"--------------------"
	fscanf(fp,"%s",notes);
	
	fscanf(fp,"%s",notes);
	if(strcmp(notes, "Site_name:")!=0) 
	{
		sprintf(IData.sitename, "%s", notes);
	}
	else
		fscanf(fp,"%s",IData.sitename);
	 
	
	fscanf(fp,"%s %d",notes,&IData.years);
	if(strcmp(notes, "Simulated_Year:")!=0) Toend("Simulated_Year:", fname);
	

    fscanf(fp,"%s %f", notes,&IData.latitude);// "  "
	if(strcmp(notes, "Latitude:")!=0) Toend("Latitude:", fname);
	
    
	fscanf(fp,"%s %d", notes,&IData.ifdaily);	//"  "
	if(strcmp(notes, "Daily_Record:")!=0) Toend("Daily_Record:", fname);


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
	float m_LagoonCapacity, m_LagoonSurfaceArea, LagoonToField[10], LagoonToMarket[10], LagoonRemain[10], LagoonManureAplDepth[10];
	int m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes, LagoonDrainMonth[10], LagoonDrainDay[10], LagoonManureAplMethod[10];
	float m_CompostDensity, m_LitterAmount, m_LitterCN, CompostToField, CompostToMarket, CompostRemain;
	float m_DigesterCapacity,m_DigesterCH4,m_DigesterDays, DigesterToField;
	int m_Temp, m_Flash, HouseID, m_CompostCover, m_CompostRemoveTimes, CompostRemoveMonth, CompostRemoveDay;
	float DigesterToMarket, DigesterRemain, m_FlushWater, LiquidFraction;
	float HouseManureOutDays,m_UC, m_UL, m_UD, m_UF, m_UR, m_FC, m_FL, m_FD, m_FF, m_FR;
	float PenManureOutDays, PenUC, PenUL,PenUD,PenUR,PenFC, PenFL,PenFD,PenFR;
	float GrazeManureOutDays, GrazeUF, GrazeUR, GrazeFF, GrazeFR, FieldArea, jf;
	
	CString MP;
	FILE *mp;
	CString SF;
	FILE* sf;

	int m_FeedLots, m_FeedlotYears;

	fscanf(fp,"%s", notes);
	fscanf(fp,"%s", notes);
	fscanf(fp,"%s %d",notes, &m_FeedlotYears);

	for(int m_FeedlotYear=1; m_FeedlotYear<=m_FeedlotYears; m_FeedlotYear++)
	{
		fscanf(fp,"%s %d",notes, &m_FeedLots);

		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Result\\inter\\TotalFeedLots_%d", ROOTDIR, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", m_FeedLots);
		fclose(TFL);

		for(i=1; i<=m_FeedLots; i++)
		{
			fscanf(fp,"%s %d",notes,&HouseID);
			if(fscanf(fp,"%s %d",notes,&HouseInputFormat)!=2)
			{
				AfxMessageBox("No livostock data");
			}
			else
			{
				if(HouseInputFormat==1||HouseInputFormat==2)
					fscanf(fp,"%s %s",notes,HouseInputFileName);
				else if(HouseInputFormat==3)
					fscanf(fp,"%s %d",notes,&NutritionModelX);
				else
				{
					fscanf(fp,"%s %d",notes,&AnimalTypes);
					fscanf(fp,"%s %d",notes,&AnimalType[1]);
					fscanf(fp,"%s %f",notes,&AnimalHeads[1]);
					fscanf(fp,"%s",notes);//feed
					fscanf(fp,"%s %f",notes,&FeedRate[1]);
					fscanf(fp,"%s %f",notes,&FeedProtein[1]);
					fscanf(fp,"%s %f",notes,&FeedTP[1]);			
				}
				fscanf(fp,"%s",notes);//floor
				fscanf(fp,"%s %f",notes,&m_FloorArea);
				fscanf(fp,"%s %d",notes,&m_FloorSurface);
				fscanf(fp,"%s",notes);//bedding			
				fscanf(fp,"%s %d",notes,&m_BedType);
				fscanf(fp,"%s %f",notes,&m_BedCN);
				fscanf(fp,"%s %f",notes,&m_BedFrequency);
				fscanf(fp,"%s %f",notes,&m_BedRate);
				fscanf(fp,"%s",notes);//ventilation			
				fscanf(fp,"%s %d",notes,&m_Ventilation);
				fscanf(fp,"%s %f",notes,&m_VentRate);
				fscanf(fp,"%s %s",notes,IndoorClimateFile);
				fscanf(fp,"%s",notes);//manure removal			
				fscanf(fp,"%s %f", notes, &HouseManureOutDays);
				fscanf(fp,"%s %f", notes, &m_UC);
				fscanf(fp,"%s %f", notes, &m_UL);
				fscanf(fp,"%s %f", notes, &m_UD);
				fscanf(fp,"%s %f", notes, &m_UF);
				fscanf(fp,"%s %f", notes, &m_UR);			
				fscanf(fp,"%s %f", notes, &m_FC);
				fscanf(fp,"%s %f", notes, &m_FL);
				fscanf(fp,"%s %f", notes, &m_FD);
				fscanf(fp,"%s %f", notes, &m_FF);
				fscanf(fp,"%s %f", notes, &m_FR);
				fscanf(fp,"%s", notes);//flushing
				fscanf(fp,"%s %d", notes, &m_Flash);
				fscanf(fp,"%s %f", notes, &m_FlushWater);
				fscanf(fp,"%s %f", notes, &LiquidFraction);

				//if(AnimalHeads[1]>0)
				{
					SF.Format("%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
					sf=fopen(SF, "w");
					fprintf(sf, "%d\n", HouseInputFormat);  

					if(HouseInputFormat==1||HouseInputFormat==2)								//use a input file name
						fprintf(sf, "%s\n", HouseInputFileName);
					else if(HouseInputFormat==3)								//use nutrition model
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
					fprintf(sf, "%d %f %f\n", m_Flash, m_FlushWater, LiquidFraction);
					fclose(sf);
				}
			}
		}
	}

	fscanf(fp,"%s", notes);//lagoon
	fscanf(fp,"%s %f",notes, &m_LagoonCapacity);
	fscanf(fp,"%s %f",notes, &m_LagoonSurfaceArea);
	fscanf(fp,"%s %d",notes, &m_LagoonCover);
	fscanf(fp,"%s %d",notes, &m_LagoonRain);

	fscanf(fp,"%s",notes);
	if(strcmp(notes, "SlurryRemovalFrequency")==0) 
	{
		fscanf(fp,"%f", &jf);
		m_LagoonDrainTimes = 0;
		fscanf(fp,"%s %f",notes, &LagoonToField[1]);
		fscanf(fp,"%s %f",notes, &LagoonToMarket[1]);
		fscanf(fp,"%s %f",notes, &LagoonRemain[1]);
	}
	else
	{
		fscanf(fp,"%d",&m_LagoonDrainTimes);

		for(i=1; i<=m_LagoonDrainTimes; i++)
		{
			fscanf(fp,"%s %d",notes, &LagoonDrainMonth[i]);
			fscanf(fp,"%s %d",notes, &LagoonDrainDay[i]);
			fscanf(fp,"%s %f",notes, &LagoonToField[i]);
			fscanf(fp,"%s %f",notes, &LagoonToMarket[i]);
			fscanf(fp,"%s %f",notes, &LagoonRemain[i]);
			fscanf(fp,"%s %d",notes, &LagoonManureAplMethod[i]);
			fscanf(fp,"%s %f",notes, &LagoonManureAplDepth[i]);
		}
	}
	
	//if(m_LagoonCapacity>0.0)
	{
		SF.Format("\%s\\Inter\\ManureLagoon.txt", OUTPUT);
		sf=fopen(SF, "w");
		fprintf(sf, "%f  %f  %d  %d  %d\n", m_LagoonCapacity, m_LagoonSurfaceArea, m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes); 
		for(i=1; i<=m_LagoonDrainTimes; i++)
		{
			fprintf(sf, "%d  %d  %f  %f  %f\n", LagoonDrainMonth[i], LagoonDrainDay[i], LagoonToField[i], LagoonToMarket[i], LagoonRemain[i]);
			fprintf(sf, "%d %f\n", LagoonManureAplMethod[i], LagoonManureAplDepth[i]);
		}
		fclose(sf);
	}

	fscanf(fp,"%s", notes);//compost
	fscanf(fp,"%s %f",notes,&m_CompostDensity);
	fscanf(fp,"%s %d",notes,&m_CompostCover);
	fscanf(fp,"%s %d",notes,&m_CompostRemoveTimes);
	fscanf(fp,"%s %f",notes,&m_LitterAmount);
	fscanf(fp,"%s %f",notes,&m_LitterCN);

	//if(m_CompostDensity>0.0)
	{
		SF.Format("%s\\Inter\\ManureCompost.txt", OUTPUT);
		sf=fopen(SF, "w");
		fprintf(sf, "%f  %d  %d  %f  %f\n", m_CompostDensity, m_CompostCover, m_CompostRemoveTimes, m_LitterAmount, m_LitterCN);  
		for(i=1;i<=m_CompostRemoveTimes;i++)
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
	
	fscanf(fp,"%s", notes);//digester
	fscanf(fp,"%s %d",notes, &m_Temp);
	fscanf(fp,"%s %f",notes, &m_DigesterCH4);
	fscanf(fp,"%s %f",notes, &m_DigesterDays);
	fscanf(fp,"%s %f",notes, &DigesterToField);
	fscanf(fp,"%s %f",notes, &DigesterToMarket);
	fscanf(fp,"%s %f",notes, &DigesterRemain);
	
	//if(m_DigesterDays>0.0)
	{
		SF.Format("%s\\Inter\\ManureDigester.txt", OUTPUT);
		sf=fopen(SF, "w");
		fprintf(sf, "%d  %f  %f\n", m_Temp,m_DigesterCH4,m_DigesterDays);  
		fprintf(sf, "%f  %f  %f\n", DigesterToField,  DigesterToMarket, DigesterRemain);
		fclose(sf);
	}

	fscanf(fp,"%s", notes);//land application
	fscanf(fp,"%s %f",notes, &FieldArea);

	if(FieldArea>0.0)
	{
		MP.Format("%s\\Inter\\ManureField.txt", OUTPUT);
		mp=fopen(MP, "w");
		fprintf(mp, "%f\n", FieldArea);
		fclose(mp);
	}

	CString XFF;
	FILE *xff;
	XFF.Format("%s\\inter\\ManureFieldCrops", OUTPUT);		
	xff=fopen(XFF, "w");
	int CropOrder, FarmCropType, FarmCrops, TotalFarmYears;
	float FarmCropHa, ManuFraction;
	
	fscanf(fp,"%s %d %d",notes, &FarmCrops, &TotalFarmYears);
	fprintf(xff, "%d\n", FarmCrops);
	
	for(i=1;i<=FarmCrops;i++)
	{
		fscanf(fp,"%s %d",notes, &CropOrder);
		fscanf(fp,"%s %d",notes, &FarmCropType);
		fscanf(fp,"%s %f",notes, &FarmCropHa);
		fscanf(fp,"%s %f",notes, &ManuFraction);

		fprintf(xff, "%d  %d  %f  %f\n", i, FarmCropType, FarmCropHa, ManuFraction);

		CString FCT0, FCT100;
		FCT100.Format("%s\\INPUTS\\FarmCrop_%d", OUTPUT, i);
		mkdir(FCT100);
	}
	fclose(xff);

	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", FarmCrops, CropOrder, FarmCropType);//ManureCropOrder, &CropIDID
	fclose(xff);

/*	if(FieldArea>0.0)
	{
		XFF.Format("%s\\ManureFieldAll.txt", INTER);
		xff=fopen(XFF, "w");
		if(xff==NULL) note(1, XFF);
		fprintf(xff, "%d %f\n", FarmCrops, FieldArea);
		fclose(xff);
	}
*/
#endif
    
		//climate data
	fscanf(fp,"%s",notes);//"--------------------"
	
	fscanf(fp,"%s",notes);//"Climate data:"
	
	fscanf(fp,"%s %d", notes,&IData.ClimateFileType);
	if(strcmp(notes, "Climate_Data_Type:")!=0) Toend("Climate_Data_Type:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.NO3NH4_Rainfall);	//"
	if(strcmp(notes, "NO3NH4_in_Rainfall")!=0) Toend("NO3NH4_in_Rainfall", fname);
	

	fscanf(fp,"%s %f", notes,&IData.NH3_Atmosphere);	//"
	//if(strcmp(notes, "NH3_of_Atmosphere")!=0) Toend("NH3_of_Atmosphere:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.BaseCO2);		//"
	if(strcmp(notes, "BaseCO2_of_Atmosphere")!=0) Toend("BaseCO2_of_Atmosphere:", fname);
	

	fscanf(fp,"%s %d", notes,&IData.ClimateFileNumber);	
	if(strcmp(notes, "Climate_file_count=")!=0) Toend("Climate_file_count:", fname);
	

	k=IData.ClimateFileType;
	int nn=IData.ClimateFileNumber;
	//IData.MaxCycle = IData.years;
		//read climate file name
	ClimateFilename.clear();
	for (i=1;i<=IData.ClimateFileNumber;i++) 
	{
		fscanf(fp,"%d",&j);
		
		fgets(tmp,230,fp);
		EraseFBSpace(tmp);
		ClimateFilename.insert(301,tmp);
	}

	fscanf(fp,"%s", notes);
	if(strcmp(notes, "Climate_file_mode")!=0) 
	{ 
		IData.if1File = 0;
		IData.CO2IncreaseRate = 0.0;
		MissFlag=1;
	}
	else
	{
		fscanf(fp,"%d", &IData.if1File);
		fscanf(fp,"%s %f", notes,&IData.CO2IncreaseRate);
		MissFlag=0;
	}

		// Read Soil parameter
	if(MissFlag==0) fscanf(fp,"%s",notes);//"--------------------"
	MissFlag=0;
	
	
	fscanf(fp,"%s",notes);//"Soil data:"
	
	fscanf(fp,"%s %d", notes,&IData.Soil_Texture);// "  "
	if(strcmp(notes, "Soil_Texture")!=0) Toend("Soil_Texture:", fname);
	

	fscanf(fp,"%s %d", notes,&IData.Soil_landuse);// "  "
	if(strcmp(notes, "Landuse_Type")!=0) Toend("Landuse_Type:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.Soil_Density);// "  Soil_"
	if(strcmp(notes, "Density")!=0) Toend("Density:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.Soil_pH);	 // "  Soil_pH"
	if(strcmp(notes, "Soil_pH")!=0) Toend("Soil_pH:", fname);
	

	//fscanf(fp,"%s %f", notes,&IData.Flood_pH);	
	fscanf(fp,"%s %f", notes,&IData.Soil_OCatSurface);// "  "
	if(strcmp(notes, "SOC_at_Surface")!=0) Toend("SOC_at_Surface:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.Soil_Clay);	// "  Soil_Clay_Content"
	if(strcmp(notes, "Clay_fraction")!=0) Toend("Clay_fraction:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.Soil_BypassFlow);	// "  "
	if(strcmp(notes, "BypassFlow")!=0) Toend("BypassFlow:", fname);
	

    fscanf(fp,"%s %f", notes,&IData.Soil_Litter);	// "  Litter"
	if(strcmp(notes, "Litter_SOC")!=0) Toend("Litter_SOC:", fname);
	

    fscanf(fp,"%s %f", notes,&IData.Soil_humads);	// "  "
	if(strcmp(notes, "Humads_SOC")!=0) Toend("Humads_SOC:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.Soil_humus);	// "  humus"
	if(strcmp(notes, "Humus_SOC")!=0) Toend("Humus_SOC:", fname);
	

	fscanf(fp,"%s %f", notes,&IData.Soil_NO3);	// "  "
	if(strcmp(notes, "Soil_NO3(-)(mgN/kg)")!=0) Toend("Soil_NO3(-)(mgN/kg):", fname);
	

	fscanf(fp,"%s %f", notes,&IData.Soil_NH4);	// "  Soil_NH4"
	if(strcmp(notes, "Soil_NH4(+)(mgN/kg)")!=0) Toend("Soil_NH4(-)(mgN/kg):", fname);
	

	fscanf(fp,"%s %f", notes,&IData.PassiveCCN);// "  Soil_moisture"
	//if(strcmp(notes, "Soil_PassiveCN")!=0) Toend("Soil_PassiveCN:", fname);
	IData.Soil_moiture = 0.5;
	IData.PassiveCCN = 500.0;	

	fscanf(fp,"%s %f", notes,&IData.LateralInflux);	
	if(strcmp(notes, "Temperature")==0) IData.LateralInflux = 1.0;
	if(IData.LateralInflux<1.0) IData.LateralInflux = 1.0;
	//if(strcmp(notes, "Temperature")!=0) Toend("Temperature:", fname);	

	fscanf(fp,"%s", notes);
	if(strcmp(notes, "Field_capacity")!=0) 
	{ 
		IData.Fldcap = 0.0;
		IData.Wiltpt = 0.0;
		IData.Sks = 0.0;
		IData.Soil_Porosity = 0.0;
		IData.SOCa = nSoca[IData.Soil_landuse];
		IData.SOCb = nSocb[IData.Soil_landuse];
		IData.DClitter = 1.0;
		IData.DChumads = 1.0;
		IData.DChumus = 1.0;
		IData.HumadCN = 10.0;
		IData.HumusCN = 10.0;
		IData.PassiveC = 0.0;
		IData.Soil_MicrobioIndex = 1.0;
		IData.HighestWT = 1.0;
		IData.Soil_WaterObstructLayer = 3.00;
		IData.slope = 0.0;
		IData.UseION = 0;
		IData.SCSuse = 0;
		IData.Soil_Quality = 0.0;
		IData.WaterPoolBD = 0.0;
		IData.ProfileType=0;
		IData.ProfileFileName="none";
		
		MissFlag=1;
	}
	else
	{
		fscanf(fp,"%f", &IData.Fldcap);
		fscanf(fp,"%s %f", notes,&IData.Wiltpt);
		fscanf(fp,"%s %f", notes,&IData.Sks);
		fscanf(fp,"%s %f", notes,&IData.Soil_Porosity);
		fscanf(fp,"%s %f", notes,&IData.SOCa);
		fscanf(fp,"%s %f", notes,&IData.SOCb);
		fscanf(fp,"%s %f", notes,&IData.DClitter);
		fscanf(fp,"%s %f", notes,&IData.DChumads);
		fscanf(fp,"%s %f", notes,&IData.DChumus);
		fscanf(fp,"%s %f", notes,&IData.HumadCN);
		fscanf(fp,"%s %f", notes,&IData.HumusCN);
		fscanf(fp,"%s %f", notes,&IData.PassiveC);
		fscanf(fp,"%s %f", notes,&IData.Soil_MicrobioIndex);
		fscanf(fp,"%s %f", notes,&IData.HighestWT);
		fscanf(fp,"%s %f", notes,&IData.Soil_WaterObstructLayer);
		fscanf(fp,"%s %f", notes,&IData.slope);
		fscanf(fp,"%s", notes);
		
		if(strcmp(notes, "Salinity")!=0) 
		{
			IData.Soil_Quality = 0.0;
			fscanf(fp,"%d", &IData.SCSuse);
		}
		else
		{
			fscanf(fp,"%f", &IData.Soil_Quality);
			fscanf(fp,"%s %d", notes,&IData.SCSuse);
		}
		
		fscanf(fp,"%s %f", notes,&IData.WaterPoolBD);
		fscanf(fp,"%s %d", notes,&IData.ProfileType);
		fscanf(fp,"%s %d", notes,&IData.ProfileFileName);
		if(IData.Sks<0.015) IData.Sks = 0.015;//sks default 0.015
		MissFlag=0;
		
		if(IData.HighestWT>1.0) 
			IData.HighestWT = 1.0;

	}
    
    // Read crop parameter
    int ri, temp, yc, db_CycleYear[20], FCTT=0;
	int db_Rotation_Number, FarmMode=0, FarmCropNumber;

	CString DB, FCT60;
	FILE *db;

	CString CropDB;
	FILE *cropdb;

	if(MissFlag==0) fscanf(fp,"%s",notes);//"--------------------"
	MissFlag=0;

NewFarmCrop:

	FCTT++;
	FCT60.Format("%s_%d", INTERMANAGE, FCTT);
	mkdir(FCT60);
	
	fscanf(fp,"%s",notes);//"Crop_data:"
	if(strcmp(notes, "Crop_data:")!=0) Toend("Crop_data:", fname);
	
	fscanf(fp,"%s %d", notes,&db_Rotation_Number);// "  Rotation_Number"
	if(strcmp(notes, "Rotation_Number=")!=0) Toend("Rotation_Number=", fname);
	
	DB.Format("%s\\CropRotation.txt", FCT60);//###
	db=fopen(DB, "w");
	fprintf(db, "%d\n", db_Rotation_Number);
	fclose(db);
	
	//IData.Rotation_Number=db_Rotation_Number;
		// Set CroPracticeArray
	//rotation.dim(IData.Rotation_Number);
	//cycle.dim(IData.Rotation_Number, IData.years);

	for (i=1;i<=db_Rotation_Number;i++)
	{
		int db_TotalYear;
		int tilln, TillMonth, TillDay, TillMethod;
		int manun, ManuMonth, ManuDay, ManuType, ManuMethod;
		float ManuAmount, ManuCN, ManuN, ManureDepth, ManureNH4, ManureNO3,ManureAppHour, ManureDM,ManurePH;

		fscanf(fp,"%s %d", notes,&ri);// "---->"
		if(strcmp(notes, "Rotation_ID=")!=0) Toend("Rotation_ID=", fname);
		

		//ri=i;
		
			//normal crop
		fscanf(fp,"%s %d", notes,&db_TotalYear);
		if(strcmp(notes, "Totalyear=")!=0) Toend("Totalyear=", fname);
		
		
		fscanf(fp,"%s %d", notes,&db_CycleYear[i]);
		if(strcmp(notes, "Years_Of_A_Cycle=")!=0) Toend("Years_of_a_cycle=", fname);
		
		DB.Format("%s\\CropRotation_%d.txt", FCT60, i);//write: ReadInputDatafromDND, OK
		db=fopen(DB, "w");
		fprintf(db, "%d\n", i);
		fprintf(db, "%d\n", db_TotalYear);			
		fprintf(db, "%d\n", db_CycleYear[i]);
		fclose(db);	

		//rrr = i;
		for (j=1;j<=db_CycleYear[i];j++)
		{
			char WT_file[200];

			//CropDB.Format("%s\\inter\\CropRotation_%d_%d.txt", OUTPUT, i, j);
			CropDB.Format("%s\\CropRotation_%d_%d.txt", FCT60, i, j);
			cropdb=fopen(CropDB, "w");
			if(cropdb==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", CropDB);
				AfxMessageBox(notes);
				exit(0);
			}

			if(MissFlag==0) fscanf(fp,"%s",notes);
			fscanf(fp,"%d",&yc);	
			MissFlag=0;

			//fscanf(fp,"%s %d", notes,&yc);
			if(strcmp(notes, "YearID_of_a_cycle=")!=0) Toend("YearID_of_a_cycle=", fname);
			
		
			//yc = j;

			fscanf(fp,"%s %d", notes,&cropn);//CCPP.M_YrCrops[i][j]);
			if(strcmp(notes, "Crop_total_Number=")!=0) Toend("Crop_total_Number=", fname);
			
					
			fprintf(cropdb, "%d\n", cropn);
			//cropn=CCPP.M_YrCrops[i][j];

			//cycle.get(i,j)->CropNumber = cropn;
			//yyy = j;
			//SetArrayRange(1, cropn);
			int db_Type, db_Pmonth, db_Pday, db_Hmonth , db_Hday, db_Hyear, db_CoverCrop, db_PerennialCrop;
			int db_Transplant;
			float db_Yield, db_Residue;
			float db_GrowthReproductive, db_PsnEfficiency, db_PsnMax, db_TreeAge=0.0;
			float db_TreeCurrentAge=0.0, db_TreeLeafMax=0.0, db_TreeLeafMin=0.0;
			float db_GrainFraction, db_LeafFraction, db_ShootFraction, db_RootFraction;
			float db_GrainCN, db_LeafCN, db_ShootCN, db_RootCN;
			float db_TDD, db_Water, db_OptT, db_Nfix, db_Vascularity;
			float db_GrainFill;
			int	db_RootShape;

			for (k=1;k<=cropn;k++) 
			{
				if(MissFlag==0) fscanf(fp,"%s",notes);
				fscanf(fp,"%d",&temp);	
				MissFlag=0;
				if(strcmp(notes, "Crop_ID=")!=0) Toend("Crop_ID=", fname);
								

				fscanf(fp,"%s %d",notes,&db_Type);
				if(strcmp(notes, "Crop_Type=")!=0) Toend("Crop_Type=", fname);
								

				fscanf(fp,"%s %d %d",notes, &db_Pmonth , &db_Pday);
				if(strcmp(notes, "Plant_time=")!=0) Toend("Plant_time=", fname);
				
				
				fscanf(fp,"%s %d %d",notes,&db_Hmonth , &db_Hday);
				if(strcmp(notes, "Harvest_time=")!=0) Toend("Harvest_time=", fname);
				

				fscanf(fp,"%s %d",notes,&db_Hyear);
				if(strcmp(notes, "Year_of_harvest=")!=0) Toend("Year_of_harvest=", fname);
				
				
				fscanf(fp,"%s %f",notes,&db_Residue);
				if(strcmp(notes, "Ground_Residue=")!=0) Toend("Ground_Residue=", fname);
				

				fscanf(fp,"%s %f",notes,&db_Yield);// "
				if(strcmp(notes, "Yield=")!=0) Toend("Yield=", fname);
							

				fscanf(fp,"%s",notes);
				if(strcmp(notes, "Leaf_fraction=")!=0) 
				{
					fscanf(fp,"%f",&db_GrowthReproductive);
					db_LeafFraction = 0.0;
				}
				else
				{
					fscanf(fp,"%f", &db_LeafFraction);
				}				
				//if(strcmp(notes, "Rate_reproductive=")!=0) Toend("Rate_reproductive=", fname);
				
//float jf;
				fscanf(fp,"%s",notes);
				if(strcmp(notes, "Leaf_CN=")!=0) 
				{
					//fscanf(fp,"%f", &jf);//db_Transplant);
					fscanf(fp,"%d", &db_Transplant);
					db_LeafCN = 0.0;
				}
				else
				{
					fscanf(fp,"%f", &db_LeafCN);
				}				
				//if(strcmp(notes, "Rate_vegetative=")!=0) Toend("Rate_vegetative=", fname);
				

				fscanf(fp,"%s %f",notes,&db_PsnEfficiency);
				//if(strcmp(notes, "Psn_efficiency=")!=0) Toend("Psn_efficiency=", fname);
				
				float Tttt;
				fscanf(fp,"%s %f",notes,&Tttt);
				db_Transplant = (int)Tttt;

				//if(strcmp(notes, "Transplant=")!=0) Toend("Transplant=", fname);
				

				fscanf(fp,"%s %f",notes,&db_TreeAge);
				//if(strcmp(notes, "Initial_biomass=")!=0) Toend("Initial_biomass=", fname);
				
				
				fscanf(fp,"%s %d",notes,&db_CoverCrop);
				if(strcmp(notes, "Cover_crop=")!=0) Toend("Cover_crop=", fname);
				

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "Perennial_crop=")!=0) 
				{ 
					AfxMessageBox("Error in Input data");
				
				}
				else
				{
					fscanf(fp,"%d",&db_PerennialCrop);
					fscanf(fp,"%s %f",notes,&db_GrainFraction);
					fscanf(fp,"%s %f",notes,&db_ShootFraction);
					fscanf(fp,"%s %f",notes,&db_RootFraction);
					fscanf(fp,"%s %f",notes,&db_GrainCN);
					fscanf(fp,"%s %f",notes,&db_ShootCN);
					fscanf(fp,"%s %f",notes,&db_RootCN);
					fscanf(fp,"%s %f",notes,&db_TDD);
					fscanf(fp,"%s %f",notes,&db_Water);
					fscanf(fp,"%s %f",notes,&db_OptT);
					fscanf(fp,"%s %f",notes,&db_Nfix);

					if(db_LeafFraction==0.0)
					{
						db_LeafFraction = 0.5 * db_ShootFraction;
						db_ShootFraction = db_LeafFraction;
					}

					if(db_LeafCN==0.0)
					{
						db_LeafCN = db_ShootCN;
					}

					MissFlag=0;

					fscanf(fp,"%s",notes);
					if(strcmp(notes, "Vascularity=")!=0) 
					{ 
						db_Vascularity = 0.0;
						MissFlag=1;
					}
					else
						fscanf(fp,"%f",&db_Vascularity);

					fscanf(fp,"%s",notes);
					if(strcmp(notes, "Crop_ID=")==0||strcmp(notes, "Tillage_number=")==0)
					{
						db_TreeAge=0.0;
						db_TreeCurrentAge=0.0;
						db_TreeLeafMax=0.0;
						db_TreeLeafMin=0.0;

						MissFlag = 1;
					}
					else
					{
						fscanf(fp,"%f",&db_TreeAge);
						fscanf(fp,"%s %f",notes,&db_TreeCurrentAge);
						fscanf(fp,"%s %f",notes,&db_TreeLeafMax);
						fscanf(fp,"%s %f",notes,&db_TreeLeafMin);
					}					
				}

				fprintf(cropdb, "%d\n", k);
				fprintf(cropdb, "%d\n", db_Type);
				fprintf(cropdb, "%d  %d\n", db_Pmonth , db_Pday);
				fprintf(cropdb, "%d  %d\n", db_Hmonth , db_Hday);
				fprintf(cropdb, "%d\n", db_Hyear);
				fprintf(cropdb, "%f\n", db_Residue);
				fprintf(cropdb, "%f\n", db_Yield);
				fprintf(cropdb, "%f %d %f %f %f\n", db_GrowthReproductive, db_Transplant,
					db_PsnEfficiency, db_PsnMax, db_TreeAge);
				fprintf(cropdb, "%d\n", db_CoverCrop);
				fprintf(cropdb, "%d\n", db_PerennialCrop);

				fprintf(cropdb, "%f %f %f %f\n", db_GrainFraction, db_LeafFraction, db_ShootFraction, db_RootFraction);
				fprintf(cropdb, "%f %f %f %f\n", db_GrainCN, db_LeafCN, db_ShootCN, db_RootCN);
				fprintf(cropdb, "%f %f %f %f %f\n", db_TDD, db_Water, db_OptT, db_Nfix, db_Vascularity);	
				fprintf(cropdb, "%f %f %f %f\n", db_TreeAge, db_TreeCurrentAge, db_TreeLeafMax, db_TreeLeafMin);					
				fprintf(cropdb, "%d %f\n", db_RootShape, db_GrainFill);					
				
			}
			
			fclose(cropdb);
			
			//Tillage
			//DB.Format("%s\\inter\\CropTill_%d_%d.txt", OUTPUT, i, j);
			DB.Format("%s\\CropTill_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}			

			if(MissFlag==0) fscanf(fp,"%s", notes);// "---"
			fscanf(fp,"%d", &tilln);
			MissFlag=0;
			if(strcmp(notes, "Tillage_number=")!=0) Toend("Tillage_number=", fname);			

			fprintf(db, "%d\n", tilln);

			for (k=1;k<=tilln;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);// "th Tillage:"   //  Month,Day,method"
				if(strcmp(notes, "Tillage_ID=")!=0) Toend("Tillage_ID=", fname);
				

				fscanf(fp,"%s %d %d %d", notes,&TillMonth, &TillDay, &TillMethod);
				if(strcmp(notes, "Month/Day/method=")!=0) Toend("Tillage_Month/Day/method=", fname);
				

				fprintf(db, "%d  %d  %d\n", TillMonth, TillDay, TillMethod);	
			}
			fclose(db);

			//Fertilization
			//DB.Format("%s\\inter\\CropFert_%d_%d.txt", OUTPUT, i, j);
			DB.Format("%s\\CropFert_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}

			int fertn, FertMonth, FertDay, FertMethod, FertOption=0;
			float FertNitrate, FertAbi, FertUrea, FertAnh, FertNH4NO3, FertNH42SO4, FertNH42HPO4, FertDepth;
			float DayRelease, NIefficiency, NIduration, UreaseEfficiency, UreaseDuration;

			fscanf(fp,"%s %d", notes,&fertn);// "Fertilization_number---"
			if(strcmp(notes, "Fertil_number=")!=0) Toend("Fertil_number=", fname);
			

			fprintf(db, "%d\n", fertn);

			if(fertn!=-1)
			{
				for (k=1;k<=fertn;k++) 
				{
					if(MissFlag==0) fscanf(fp,"%s %d", notes,&temp);
					else fscanf(fp,"%d", &temp);
					MissFlag=0;

					/*fscanf(fp,"%s %d", notes,&temp);
					if(strcmp(notes, "fertilization_ID=")!=0) Toend("fertilization_ID=", fname);
					*/

					fscanf(fp,"%s %d %d %d", notes,&FertMonth, &FertDay, &FertMethod);
					if(strcmp(notes, "Month/Day/method=")!=0) Toend("Month/Day/method=", fname);
					

					fscanf(fp,"%s %f", notes,&FertDepth);
					if(strcmp(notes, "Depth=")!=0) Toend("Depth=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNitrate);
					if(strcmp(notes, "Nitrate=")!=0) Toend("Nitrate=", fname);
					

					fscanf(fp,"%s %f", notes,&FertAbi);
					if(strcmp(notes, "AmmBic=")!=0) Toend("AmmBic=", fname);
					

					fscanf(fp,"%s %f", notes,&FertUrea);
					if(strcmp(notes, "Urea=")!=0) Toend("Urea=", fname);
					

					fscanf(fp,"%s %f", notes,&FertAnh);
					if(strcmp(notes, "Anh=")!=0) Toend("Anh=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNH4NO3);
					if(strcmp(notes, "NH4NO3=")!=0) Toend("NH4NO3=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNH42SO4);
					if(strcmp(notes, "NH42SO4=")!=0) Toend("NH42SO4=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNH42HPO4);
					if(strcmp(notes, "NH4HPO4=")!=0) Toend("NH4HPO4=", fname);
					

					fprintf(db, "%d %d %d\n", FertMonth, FertDay, FertMethod);
					fprintf(db, "%f %f %f %f %f %f %f %f\n", FertNitrate, FertAbi, FertUrea, FertAnh, FertNH4NO3, 
					FertNH42SO4, FertNH42HPO4, FertDepth);
					
					fscanf(fp,"%s %f", notes,&DayRelease);
					if(strcmp(notes, "Release_rate=")!=0) Toend("Release_rate=", fname);					

					fscanf(fp,"%s %f", notes,&NIefficiency);
					if(strcmp(notes, "Inhibitor_efficiency=")!=0) Toend("Inhibitor_efficiency=", fname);					

					fscanf(fp,"%s %f", notes,&NIduration);
					if(strcmp(notes, "Inhibitor_duration=")!=0) Toend("Inhibitor_duration=", fname);	
					
					fscanf(fp,"%s", notes);
					if(strcmp(notes, "Urease_efficiency=")!=0) 
					{
						UreaseEfficiency=0.0;
						UreaseDuration=0.0;
						MissFlag=1;
					}
					else
					{
						fscanf(fp,"%f", &UreaseEfficiency);
						if(strcmp(notes, "Urease_efficiency=")!=0) Toend("Urease_efficiency=", fname);
						fscanf(fp,"%s %f", notes, &UreaseDuration);
						if(strcmp(notes, "Urease_duration=")!=0) Toend("Urease_duration=", fname);
					}

					fprintf(db, "%f %f %f %f %f\n", DayRelease, NIefficiency, NIduration, 
						UreaseEfficiency, UreaseDuration);
				}

				if(MissFlag==0)
					fscanf(fp,"%s",notes);
				else
				{
				}

				if(strcmp(notes, "FertilizationOption=")!=0) 
				{ 
					FertOption = 0;
					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%d",&FertOption);
					MissFlag=0;
				}

				fprintf(db, "%d\n", FertOption);
			}
			else
			{
				char Fertigation[200];
				
				fscanf(fp,"%s %s", notes, Fertigation);
				fprintf(db, "%s\n", Fertigation);
			}

			fclose(db);

			//Manure
			//DB.Format("%s\\inter\\CropManu_%d_%d.txt", OUTPUT, i, j);
			DB.Format("%s\\CropManu_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}			

			if(MissFlag==0) fscanf(fp,"%s %d", notes,&manun);
			else fscanf(fp,"%d", &manun);
			MissFlag=0;

			if(strcmp(notes, "Manure_number=")!=0) Toend("Manure_number=", fname);			
						
			fprintf(db, "%d\n", manun);
			
			fprintf(db, "%d %d\n", 0, 0);
			fprintf(db, "%f %f %d %d %f\n", 0.0, 0.0, 0, 0, 0.0);
			fprintf(db, "%f %f %f\n", 0.0, 0.0, 0.0);

			for (k=1;k<=manun;k++) 
			{
				if(MissFlag==0) fscanf(fp,"%s %d", notes,&temp);
				else fscanf(fp,"%d", &temp);
				MissFlag=0;

				if(strcmp(notes, "Manure_ID=")!=0) Toend("Manure_ID=", fname);
				

				fscanf(fp,"%s %d %d", notes,&ManuMonth, &ManuDay);
				if(strcmp(notes, "Month/Day=")!=0) Toend("Month/Day=", fname);
				

				fscanf(fp,"%s %f %f", notes,&ManuAmount, &ManuCN);
				if(strcmp(notes, "Amount/C|N_ratio=")!=0) Toend("Amount/C|N_ratio=", fname);
				

				fscanf(fp,"%s %d", notes, &ManuType);
				if(strcmp(notes, "Type=")!=0) Toend("Type=", fname);
				

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "Method=")!=0)
				{ 
					ManuMethod = 0;
					MissFlag=1;
				}
				else
					fscanf(fp,"%d",&ManuMethod);

				fscanf(fp,"%f", &ManureDepth);

				ManuN = ManuAmount / ManuCN;

				fprintf(db, "%d %d\n", ManuMonth, ManuDay);
				fprintf(db, "%f %f %d %d %f\n", ManuAmount, ManuCN, ManuType, ManuMethod, ManureDepth);
				fprintf(db, "%f %f %f %d %f %f\n", ManuN, ManureNH4, ManureNO3,ManureAppHour,ManureDM, ManurePH);//Brian was 0.0 for ManureNH4 and ManureNO3


			}
			fclose(db);

			//Plastic
	
			DB.Format("%s\\CropPlastic_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}

			int weedn, WeedOption, WeedMonth1, WeedDay1, WeedMonth2, WeedDay2;
			float CoverFraction;
			if(MissFlag==0) fscanf(fp,"%s %d", notes,&weedn);// "Weed_number---"
			else fscanf(fp,"%d", &weedn);
			MissFlag=0;

			fscanf(fp,"%s %d", notes,&WeedOption);// "Weed_Problem"
			fprintf(db, "%d %d\n", weedn, WeedOption);

			for (k=1;k<=weedn;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);// "th Weeding:"			//Month,Day,method"
				//if(strcmp(notes, "Plastic_ID=")!=0) Toend("Plastic_ID=", fname);
				

				fscanf(fp,"%s %d %d", notes,&WeedMonth1, &WeedDay1);
				fscanf(fp,"%s %d %d", notes,&WeedMonth2, &WeedDay2);
				fscanf(fp,"%s %f", notes,&CoverFraction);
				if(strcmp(notes, "CoverFraction=")!=0) 
				{
					CoverFraction = 1.0;
					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%f", &CoverFraction);
				}
				

				fprintf(db, "%d %d\n", WeedMonth1, WeedDay1);
				fprintf(db, "%d %d\n", WeedMonth2, WeedDay2);
				fprintf(db, "%f\n", CoverFraction);
				
			}
			fclose(db);

			//Flooding
			DB.Format("%s\\CropFloo_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}

			if(MissFlag==1) 
			{
				fscanf(fp,"%d", &floon);
				MissFlag=0;
			}
			else
			{
				fscanf(fp,"%s %d", notes,&floon);// "Flood_number---"
			}
			
			if(strcmp(notes, "Flood_number=")!=0) Toend("Flood_number=", fname);
				

			fscanf(fp,"%s %f", notes,&FloodWaterN);// FloodWaterN
			//if(strcmp(notes, "Leak_type=")!=0) Toend("Leak_type=", fname);
				

			fscanf(fp,"%s %d", notes,&WaterControl);// 
			if(strcmp(notes, "Water_control=")!=0) Toend("Water_control=", fname);
				

			fscanf(fp,"%s %f", notes, &WaterLeakRate);
			if(strcmp(notes, "Leak_rate=")!=0) Toend("Leak_rate=", fname);
				
				
			fprintf(db, "%d %f %d %f\n", floon, FloodWaterN, WaterControl, WaterLeakRate);

			for (k=1;k<=floon;k++) 
			{ 
				fscanf(fp,"%s %d", notes,&temp);// "th Flooding:"			
				if(strcmp(notes, "Flooding_ID=")!=0) Toend("Flooding_ID=", fname);
				

				fscanf(fp,"%s %d %d", notes,&FlooMonth1, &FlooDay1);
				if(strcmp(notes, "Flood_Month/Day=")!=0) Toend("Flood_Month/Day=", fname);
				

				fscanf(fp,"%s %d %d", notes,&FlooMonth2, &FlooDay2);
				if(strcmp(notes, "Drain_Month/Day=")!=0) Toend("Drain_Month/Day=", fname);
				

				fscanf(fp,"%s %f", notes,&FlooN);
				//if(strcmp(notes, "Water_N=")!=0) Toend("Water_N=", fname);
				

				fscanf(fp,"%s %d", notes,&ShallowFlood);
				if(strcmp(notes, "Shallow_flood=")!=0) Toend("Shallow_flood=", fname);
				

				fprintf(db, "%d %d\n", FlooMonth1, FlooDay1);
				fprintf(db, "%d %d\n", FlooMonth2, FlooDay2);
				fprintf(db, "%f\n", FlooN);
				fprintf(db, "%d\n", ShallowFlood);
			}
			
			fscanf(fp,"%s", notes);
			if(strcmp(notes, "Water_gather=")!=0) 
			{
				WaterGetherIndex = 1.0;
				MissFlag=1;
			}
			else
				fscanf(fp,"%f", &WaterGetherIndex);
				
			fprintf(db, "%f\n", WaterGetherIndex);				
			
			if(MissFlag==1)
			{
				if(strcmp(notes, "WT_file=")!=0) 
				{
					sprintf(WT_file, "None"); 
				}
				else 
				{
					fscanf(fp,"%s", WT_file);
					MissFlag=0;
				}
			}
			else
			{
				fscanf(fp,"%s", notes);
				if(strcmp(notes, "WT_file=")!=0) 
				{
					sprintf(WT_file, "None"); 
					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%s", WT_file);
				}
			}

			fprintf(db, "%s\n", WT_file);


			if(MissFlag==1)
			{			
				if(strcmp(notes, "Empirical_parameters=")!=0) 
				{					
					m_IniWT=0.0;
					m_LWTceasingSurfFlow=0.0;
					m_LWTceasingGroungFlow=0.0;
					m_WatershedIndex=0.0;
					m_SurfOutflowIntensity=0.0;
					m_GroundOutflowIntensity=0.0;

					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
													&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);
					MissFlag=0;
				}
			}
			else
			{
				fscanf(fp,"%s", notes);
				if(strcmp(notes, "Empirical_parameters=")!=0) 
				{
					m_IniWT=0.0;
					m_LWTceasingSurfFlow=0.0;
					m_LWTceasingGroungFlow=0.0;
					m_WatershedIndex=0.0;
					m_SurfOutflowIntensity=0.0;
					m_GroundOutflowIntensity=0.0;

					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
													&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);
					MissFlag=0;
				}
			}

			fprintf(db, "%f %f %f %f %f %f\n", m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, 
												m_SurfOutflowIntensity, m_GroundOutflowIntensity);
			
			fclose(db);

			//Irrigation
			DB.Format("%s\\CropIrri_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}

			int irrin, IrriMode, IrriMonth, IrriDay, IrriMethod;
			float IrriIndex, IrriAmount;

			if(MissFlag==0) fscanf(fp,"%s", notes);
			fscanf(fp,"%d", &irrin);// "Irrigation_number---"
			MissFlag=0;

			if(strcmp(notes, "Irrigation_number=")!=0) Toend("Irrigation_number=", fname);				

			fscanf(fp,"%s %d", notes,&IrriMode);// Irrigation type"
			if(strcmp(notes, "Irrigation_type=")!=0) Toend("Irrigation_type=", fname);
				

			fscanf(fp,"%s %f", notes,&IrriIndex);// Irrigation type"
			if(strcmp(notes, "Irrigation_Index=")!=0) Toend("Irrigation_Index=", fname);

			fscanf(fp,"%s", notes);
			if(strcmp(notes, "Irrigation_Method=")!=0) //Toend("Irrigation_Method=", fname);
			{
				IrriMethod = 0;
				MissFlag=1;
			}
			else
				fscanf(fp,"%d", &IrriMethod);

			fprintf(db, "%d %d %f %d\n", irrin, IrriMode, IrriIndex, IrriMethod);

			for (k=1;k<=irrin;k++) 
			{
				if(MissFlag==1) 
				{
					fscanf(fp,"%d", &temp);
					MissFlag = 0;
				}
				else fscanf(fp,"%s %d", notes,&temp);
				if(strcmp(notes, "Irrigation_ID=")!=0) Toend("Irrigation_ID=", fname);				

				fscanf(fp,"%s %d %d", notes,&IrriMonth, &IrriDay);
				if(strcmp(notes, "Irr_Month/Day=")!=0) Toend("Irr_Month/Day=", fname);				

				int jd;
				fscanf(fp,"%s %f %d", notes,&IrriAmount, &jd);
				if(jd<0||jd>10) IrriMethod=0;
				else IrriMethod=jd;				

				fprintf(db, "%d %d\n", IrriMonth, IrriDay);
				fprintf(db, "%f %d\n", IrriAmount, IrriMethod);
			}
			fclose(db);

			//Grazing
			//DB.Format("%s\\inter\\CropGraz_%d_%d.txt", OUTPUT, i, j);
			DB.Format("%s\\CropGraz_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}

			int grazn, GrazMonth1, GrazDay1, GrazMonth2, GrazDay2, Excreta;
			float GrazHour, Dairy, Beef, Pig, Horse, Sheep, AddFeed, FeedCN;
		
			if(MissFlag==1) 
			{
				fscanf(fp,"%d", &grazn);
				MissFlag = 0;
			}
			else 
			{
				fscanf(fp,"%s %d", notes,&grazn);// "Grazing_number---"
			}

			if(strcmp(notes, "Grazing_number=")!=0) Toend("Grazing_number= ", fname);				

			fprintf(db, "%d\n", grazn);

			//cycle.get(ri,yc)->GrazingNumber = grazn;
			//SetArrayRange(8, grazn);
			for (k=1;k<=grazn;k++) 
			{
				fscanf(fp,"%s %d", notes,&temp);
				if(strcmp(notes, "Grazing_ID=")!=0) Toend("Grazing_ID=", fname);
				

				fscanf(fp,"%s %d %d", notes,&GrazMonth1, &GrazDay1);
				if(strcmp(notes, "Start_Month/Day=")!=0) Toend("Start_Month/Day=", fname);
				

				fscanf(fp,"%s %d %d", notes,&GrazMonth2, &GrazDay2);
				if(strcmp(notes, "End_Month/Day=")!=0) Toend("End_Month/Day=", fname);
				

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "Dairy_Head_per_ha=")!=0)//old version 
				{
					//MissFlag=1;
					fscanf(fp,"%f", &Beef);
					fscanf(fp,"%s %f", notes,&Horse);
					fscanf(fp,"%s %f", notes,&Sheep);
					Pig = 0.0;
					Dairy = 0.0;
				}
				else//new version
				{
					fscanf(fp,"%f", &Dairy);
					fscanf(fp,"%s %f", notes,&Beef);
					fscanf(fp,"%s %f", notes,&Pig);
					fscanf(fp,"%s %f", notes,&Sheep);
					fscanf(fp,"%s %f", notes,&Horse);
				}

				fscanf(fp,"%s %f", notes,&GrazHour);
				if(strcmp(notes, "Graz_Hours_Per_day=")!=0) Toend("Graz_Hours_Per_day=", fname);
				
				fscanf(fp,"%s", notes);

				if(strcmp(notes, "Additional_feed=")!=0) 
				{
					AddFeed=0.0;					
					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%f", &AddFeed);
					MissFlag=0;
				}

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "Feed_C/N=")!=0) 
				{
					FeedCN=0.0;					
					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%f", &FeedCN);
					MissFlag=0;
				}

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "Excreta=")!=0) 
				{
					Excreta=1;
					MissFlag=1;
				}
				else
				{
					fscanf(fp,"%d", &Excreta);
					MissFlag=0;
				}

				fprintf(db, "%d %d\n", GrazMonth1, GrazDay1);
				fprintf(db, "%d %d\n", GrazMonth2, GrazDay2);
				fprintf(db, "%f\n", GrazHour);
				fprintf(db, "%f %f %f %f %f %f %f %d\n", Dairy, Beef, Pig, Sheep, Horse, AddFeed, FeedCN, Excreta);
			}
			fclose(db);	
			
			//Grass cutting
			//DB.Format("%s\\inter\\GrassCut_%d_%d.txt", OUTPUT, i, j);
			DB.Format("%s\\GrassCut_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}

			int cutn, CutMonth, CutDay, CutPart;
			float CutAmount;
		
			fscanf(fp,"%s %d", notes,&cutn);// "Cutting_number---"
			

			if(strcmp(notes, "Cut_number=")==0) 
			{
				fprintf(db, "%d\n", cutn);

				for (k=1;k<=cutn;k++) 
				{
					if(MissFlag==0) fscanf(fp,"%s %d", notes,&temp);
					else 
					{
						fscanf(fp,"%d", &temp);
						MissFlag = 0;
					}
					if(strcmp(notes, "Cut_ID=")!=0) Toend("Cut_ID=", fname);
					

					fscanf(fp,"%s %d %d", notes,&CutMonth, &CutDay);
					if(strcmp(notes, "Cut_Month/Day=")!=0) Toend("Cut_Month/Day=", fname);
					

					fscanf(fp,"%s %f", notes,&CutAmount);
					if(strcmp(notes, "Cut_amount=")!=0) Toend("Cut_amount=", fname);
					

					fscanf(fp,"%s", notes);
					if(strcmp(notes, "Cut_part=")!=0) 
					{
						MissFlag=1;
						CutPart=0;
					}
					else
					{ 
						fscanf(fp,"%d", &CutPart);
						
					}

					fprintf(db, "%d %d\n", CutMonth, CutDay);
					fprintf(db, "%f %d\n", CutAmount, CutPart);
				}				
			}
			fclose(db);	
		}
	}	

	fscanf(fp,"%s", notes);
	if(strcmp(notes, "----------------------------------------")==0) FarmMode = 1;
	else
	{
		if(strcmp(notes, "Crop_model_approach")==0) 
		{
			int jjd;
			FarmMode = 0;
			MissFlag = 1;
			fscanf(fp,"%d", &jjd);
		}
		//else
		//	fscanf(fp,"%d", &IData.CropModel);

	}

	if(FarmMode==1) 
		goto NewFarmCrop;	
	
	//if(strcmp(notes, "Crop_model_approach")!=0) IData.CropModel = 0;

	////////////////////////////////////////////////////////////////////////////////
	if(IData.SCSuse==1)
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

	int US;
	fscanf(fp, "%s %d", notes, &US);
	fclose(fp);
	
	if(US==0||US==1) US = US;
	else US = 0;
	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", US);
	fclose(ddb);
}

}


void Toend(char *notes, char *FN)
{
	CString cl;
	cl.Format("The old input file does not match this version any more. You may need to create a new file manually. Sorry for the inconvenience. Error at %s", FN);
	AfxMessageBox(cl);
    exit(0);
}