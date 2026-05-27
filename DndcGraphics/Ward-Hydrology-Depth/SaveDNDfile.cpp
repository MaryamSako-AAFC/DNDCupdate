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
//float db_TreeCurrentAge[20][20][5]={0.0,0.0};

void NewSaveDatatoFile(char *fname, int SiteRegion)
{
	int NutritionModelX, TotalFarmFields=0;

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
	int IrrMode, IrriMonth[366], IrriDay[366],DrainMonth[366],DrainDay[366],DrainMonth2[366],DrainDay2[366];
	float IrrIndex, IrriAmount[366],CDrainDepth[366];
	int IrriMethod[366],TileIrriDays[366];
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

	char LB[200];
	FILE* ddb;
	int US;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "r");
	if(ddb==NULL) note(0, LB);
	fscanf(ddb, "%d", &US);
	fclose(ddb);	

	if(IData.Sks<0.008) IData.Sks = 0.008;//default 0.015 was 0.008
    
    sprintf(Oname,"%s.fn", fname);
    
    if ((fpo=sopen(fname,0))==NULL) return;//write
    
    //Site information
    fprintf(fpo,"DNDC_Input_Parameters\n");
    fprintf(fpo,"----------------------------------------\n");
	fprintf(fpo,"%-40s\n", "Site_infomation\n");
    fprintf(fpo,"%-40s %30s\n", "__Site_name", IData.sitename);
	fprintf(fpo,"%-40s %30d\n", "__Simulated_years", IData.years);
    fprintf(fpo,"%-40s %30.4f\n", "__Latitude", IData.latitude);
	fprintf(fpo,"%-40s %30d\n", "__Daily_record", IData.ifdaily);
	fprintf(fpo,"%-40s %30d\n", "__Unit_system", US);

	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);  
    

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
	float FieldHeads, FieldHrs;

	float LagoonCapacity, LagoonSurfaceArea, LagoonDays;
	float LagoonToField[10]={0.0,0.0}, LagoonToMarket[10]={0.0,0.0}, LagoonToRemain[10]={0.0,0.0}, LagoonManureAplDepth[10]={0,0};
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
	fprintf(fpo,"%-40s %30d\n", "__Simulated_years", IData.years);

	for(int m_FeedlotYear=1; m_FeedlotYear<=IData.years; m_FeedlotYear++)
	{
		fprintf(fpo,"%-40s %30d\n", "____Year", m_FeedlotYear);

		int m_FeedLots;
		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Result\\inter\\TotalFeedLots_%d", ROOTDIR, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "r");
		if(TFL==NULL) note(0, TotalFeedlots);
		fscanf(TFL, "%d", &m_FeedLots);
		fclose(TFL);

		fprintf(fpo,"%-40s %30d\n", "______Number_of_feedlots", m_FeedLots);

		for(i=1; i<=m_FeedLots; i++)
		{
			CString CM;
			FILE* cm;

			fprintf(fpo,"%-40s %30d\n", "________Feedlot", i);
			
			CM.Format("%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
			cm=fopen(CM, "r");
			if(cm==NULL) note(0, CM);
		
			fscanf(cm, "%d", &InputFormat);

			fprintf(fpo,"%-40s %30d\n", "________Feedlot_input_option",InputFormat);
			
			if(InputFormat==1)
			{
				fscanf(cm, "%s", ManureHouseName);

				fprintf(fpo,"%-40s %30s\n", "________-Feedlot_input_file_name", ManureHouseName);
			}
			else if(InputFormat==2)
			{
				fscanf(cm, "%s", ManureHouseName);

				fprintf(fpo,"%-40s %30s\n", "________Feedlot_input_file_name", ManureHouseName);
			}
			else if(InputFormat==3)
			{
				//Name a nutrition model
				fscanf(cm, "%d", &NutritionModelX);
				fprintf(fpo,"-%-40s %30d\n", "________Feedlot_input_file_name", NutritionModelX);
			}
			else
			{
				fscanf(cm, "%d", &AnimalTypes);
				fprintf(fpo,"%-40s %30d\n", "________Livestock_types", AnimalTypes);
								
				fscanf(cm, "%d %f %f %f %f", &AnimalType, &m_AnimalHeads, &m_FeedRate, &m_FeedProtein, &m_FeedTP);

				fprintf(fpo,"%-40s %30d\n", "________Livestock_typesID", AnimalType);
				fprintf(fpo,"%-40s %30.4f\n", "________Heads", m_AnimalHeads);
				fprintf(fpo,"%-40s %30.4f\n", "________Intake_rate", m_FeedRate);
				fprintf(fpo,"%-40s %30.4f\n", "________Crude_protein_percent", m_FeedProtein);
				fprintf(fpo,"%-40s %30.4f\n", "________Phosphorus_percent", m_FeedTP);

				fprintf(fpo,"%-40s %30d\n", "________None", 0);
				fprintf(fpo,"%-40s %30d\n", "________None", 0);
				fprintf(fpo,"%-40s %30d\n", "________None", 0);
				fprintf(fpo,"%-40s %30d\n", "________None", 0);
				fprintf(fpo,"%-40s %30d\n", "________None", 0);
			}
			
			fscanf(cm, "%f %d", &m_GroundArea, &m_GroundSurface);//0 slatted floor; 1 conrete floor
			fscanf(cm, "%d  %f  %f %f", &m_BedType, &m_BedCN, &m_BedApplications, &m_BedAmount);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			
			fprintf(fpo,"%-40s %30.4f\n", "________Floor_surface_area", m_GroundArea);
			fprintf(fpo,"%-40s %30d\n", "________Floor_type", m_GroundSurface);

			fprintf(fpo,"%-40s %30d\n", "________Bedding_material_type",  m_BedType);
			fprintf(fpo,"%-40s %30.4f\n", "________Bedding_material_C/N",  m_BedCN);
			fprintf(fpo,"%-40s %30.4f\n", "________Bedding_frequency",  m_BedApplications);
			fprintf(fpo,"%-40s %30.4f\n", "________Bedding_amount",  m_BedAmount);

			fscanf(cm, "%d  %f  %s", &m_Ventilation, &m_VentRate, IndoorClimateFile);// 0 natural, 1 fan, -1 IndoorClimateFile

			fprintf(fpo,"%-40s %30d\n", "________Ventilation_type",  m_Ventilation);
			fprintf(fpo,"%-40s %30.4f\n", "________Ventilation_rate",  m_VentRate);

			fprintf(fpo,"%-40s %30s\n", "________Indoor_climate_file",  IndoorClimateFile);

			fscanf(cm, "%f", &m_Frequency);
			fscanf(cm, "%f %f %f %f %f", &m_UC, &m_UL, &m_UD, &m_UF, &m_UR);
			fscanf(cm, "%f %f %f %f %f", &m_FC, &m_FL, &m_FD, &m_FF, &m_FR);
			fscanf(cm, "%d %f %f", &m_Flash, &m_FlushWater, &LiquidFraction);

			fprintf(fpo,"%-40s %30.4f\n", "________Manure_removal_frequency", m_Frequency);
			fprintf(fpo,"%-40s %30.4f\n", "________Liquid_to_compost", m_UC);
			fprintf(fpo,"%-40s %30.4f\n", "________Liquid_to_lagoon", m_UL);
			fprintf(fpo,"%-40s %30.4f\n", "________Liquid_to_digester", m_UD);
			fprintf(fpo,"%-40s %30.4f\n", "________Liquid_to_field", m_UF);
			fprintf(fpo,"%-40s %30.4f\n", "________Liquid_remain_in_feedlot", m_UR);

			fprintf(fpo,"%-40s %30.4f\n", "________Solid_to_compost", m_FC);
			fprintf(fpo,"%-40s %30.4f\n", "________Solid_to_lagoon", m_FL);
			fprintf(fpo,"%-40s %30.4f\n", "________Solid_to_digester", m_FD);
			fprintf(fpo,"%-40s %30.4f\n", "________Solid_to_field", m_FF);
			fprintf(fpo,"%-40s %30.4f\n", "________Solid_remain_in_feedlot", m_FR);

			fprintf(fpo,"%-40s %30d\n", "________Flushing_liquid_type", m_Flash);
			fprintf(fpo,"%-40s %30.4f\n", "________Flushing_water_m3", m_FlushWater);
			fprintf(fpo,"%-40s %30.4f\n", "________Liquid_fraction", LiquidFraction);
			fprintf(fpo,"%-40s %30d\n", "________None", 0);
			fprintf(fpo,"%-40s %30d\n", "________None", 0);
			fprintf(fpo,"%-40s %30d\n", "________None", 0);
			
			fclose(cm);
		}
	}

	CString CM;
	FILE* cm;

	CM.Format("%s\\Inter\\ManureLagoon.txt", OUTPUT);
	cm=fopen(CM, "r");
	if(cm==NULL) note(0, CM);
	
	fscanf(cm, "%f %f %d %d %d", &LagoonCapacity, &LagoonSurfaceArea, &LagoonCover,	&LagoonRain, &LagoonDrainTimes);

	fprintf(fpo,"%-40s %30.4f\n", "______Lagoon_capacity", LagoonCapacity);
	fprintf(fpo,"%-40s %30.4f\n", "______Lagoon_surface_area", LagoonSurfaceArea);
	fprintf(fpo,"%-40s %30d\n", "______Lagoon_cover_type", LagoonCover);
	fprintf(fpo,"%-40s %30d\n", "______Lagoon_rainfall_receival", LagoonRain);
	fprintf(fpo,"%-40s %30d\n", "______Lagoon_slurry_removal_applications", LagoonDrainTimes);

	for(i=1; i<=LagoonDrainTimes; i++)
	{
		fscanf(cm, "%d %d %f %f %f", &LagoonDrainMonth[i], &LagoonDrainDay[i], &LagoonToField[i], &LagoonToMarket[i], &LagoonToRemain[i]);
		fscanf(cm, "%d %f\n", &LagoonManureAplMethod[i], &LagoonManureAplDepth[i]);
	
		fprintf(fpo,"%-40s %30d\n", "________Lagoon_slurry_removal", i);
		fprintf(fpo,"%-40s %30d\n", "________Lagoon_slurry_removal_month", LagoonDrainMonth[i]);
		fprintf(fpo,"%-40s %30d\n", "________Lagoon_slurry_removal_day", LagoonDrainDay[i]);
		fprintf(fpo,"%-40s %30.4f\n", "________Lagoon_slurry_to_field", LagoonToField[i]);
		fprintf(fpo,"%-40s %30.4f\n", "________Lagoon_slurry_to_digester", LagoonToMarket[i]);
		fprintf(fpo,"%-40s %30.4f\n", "________Lagoon_slurry_remain", LagoonToRemain[i]);
		fprintf(fpo,"%-40s %30d\n", "________Land_application_method", LagoonManureAplMethod[i]);
		fprintf(fpo,"%-40s %30.4f\n", "________Land_application_depth", LagoonManureAplDepth[i]);	

	}	
	
	fclose(cm);

	

	CString SF, DB;
	FILE* sf, *db;
	SF.Format("%s\\Inter\\ManureCompost.txt", OUTPUT);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);
	fscanf(sf, "%f  %d  %d  %f  %f", &m_CompostDensity, &m_CompostCover, &m_CompostRemoveTimes, &m_LitterAmount, &m_LitterCN);    
		
	fprintf(fpo,"%-40s %30.4f\n", "______Compost_porosity", m_CompostDensity);
	fprintf(fpo,"%-40s %30d\n", "______Compost_cover_type", m_CompostCover);
	fprintf(fpo,"%-40s %30d\n", "______Compost_removal_applications", m_CompostRemoveTimes);
	fprintf(fpo,"%-40s %30.4f\n", "______Compost_additive_amount", m_LitterAmount);
	fprintf(fpo,"%-40s %30.4f\n", "______Compost_additive_C/N", m_LitterCN);

	for(i=1;i<=m_CompostRemoveTimes;i++)
	{
		fscanf(sf, "%d %d %f  %f  %f", &m_CompostRemoveMonth, &m_CompostRemoveDay, &m_ToField, &m_ToMarket, &m_Remain);

		fprintf(fpo,"%-40s %30d\n", "________Compost_removal", i);
		fprintf(fpo,"%-40s %30d\n", "________Compost_removal_month", m_CompostRemoveMonth);
		fprintf(fpo,"%-40s %30d\n", "________Compost_removal_day", m_CompostRemoveDay);
		fprintf(fpo,"%-40s %30.4f\n", "________Compost_manure_to_field", m_ToField);
		fprintf(fpo,"%-40s %30.4f\n", "________Compost_manure_to_market", m_ToMarket);
		fprintf(fpo,"%-40s %30.4f\n", "________Compost_manure_remain", m_Remain);
	}
	fclose(sf);
	
	SF.Format("%s\\Inter\\ManureDigester.txt", OUTPUT);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0,SF);
	fscanf(sf, "%d  %f  %f", &m_Temp, &m_DigesterCH4, &m_DigesterDays);    
	fscanf(sf, "%f  %f  %f", &m_ToField, &m_ToMarket, &m_Remain);	
	
	fprintf(fpo,"%-40s %30d\n", "______Digester_type", m_Temp);
	fprintf(fpo,"%-40s %30.4f\n", "______Digester_retention_days", m_DigesterDays);
	fprintf(fpo,"%-40s %30.4f\n", "______Digester_manure_to_field", m_ToField);
	fprintf(fpo,"%-40s %30.4f\n", "______Digester_manure_to_lagoon", m_ToMarket);
	fprintf(fpo,"%-40s %30.4f\n", "______Digester_manure_to_bedding", m_Remain);
	
	fclose(sf);

	CM.Format("%s\\Inter\\ManureField.txt", OUTPUT);
	sf=fopen(CM, "r");
	if(sf==NULL) note(0,CM);
	fscanf(sf, "%f", &m_FieldArea);
	fclose(sf);

	if(m_FieldArea<=0.0) m_FieldArea = 1.0;
	
	
	int ManuCropType, jd, FieldNum, TotalFarmYears=0;
	float ManuCropArea[11]={0.0,0.0}, ManuFraction[11][50]={0.0,0.0};

	DB.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);
	db=fopen(DB, "r");	
	fscanf(db, "%d %d", &TotalFarmFields, &TotalFarmYears); 
	fclose(db);

	for(int YFM=1; YFM<=10; YFM++)//TotalFarmFields
	{
		for(int FYR=1; FYR<=TotalFarmYears; FYR++)
		{
			DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM, FYR);
			db=fopen(DB, "r");	
			fscanf(db, "%d %f %f", &jd, &ManuCropArea[YFM], &ManuFraction[YFM][FYR]); 
			fclose(db);			
		}
	}

	fprintf(fpo,"%-40s %30.4f\n", "______Crop_land_area", m_FieldArea);
	fprintf(fpo,"%-40s %15d\n", "______Crop_fields", TotalFarmFields);
	fprintf(fpo,"%-40s %15d\n", "______Simulated_yrs", TotalFarmYears);

	for(int FM=1; FM<=10; FM++)//TotalFarmFields
	{
		if(FM==1) fprintf(fpo,"%-40s ", "________Field_area");
		fprintf(fpo,"%30.2f ", ManuCropArea[FM]);
	}
	fprintf(fpo,"\n");
				
	for(int FYR=1; FYR<=TotalFarmYears; FYR++)
	{
		fprintf(fpo,"%-40s %30d\n", "________Year", FYR);

		for(int FW=1; FW<=10; FW++)//TotalFarmFields
		{
			if(FW==1) fprintf(fpo,"%-40s ", "________Manure_fraction");
			fprintf(fpo,"%30.4f ", ManuFraction[FW][FYR]);
		}
		fprintf(fpo,"\n");
	}
	fprintf(fpo,"\n");

	
#endif
        // Climate data
    fprintf(fpo,"----------------------------------------\n");

	fprintf(fpo,"%-40s\n", "Climate_data");
    fprintf(fpo,"\n%-40s %30d\n", "__Climate_data_type", IData.ClimateFileType);
	fprintf(fpo,"%-40s %30.4f\n", "__N_in_rainfall", IData.NO3NH4_Rainfall);
	fprintf(fpo,"%-40s %30.4f\n", "__Air_NH3_concentration", IData.NH3_Atmosphere);
	fprintf(fpo,"%-40s %30.4f\n", "__Air_CO2_concentration", IData.BaseCO2);
	fprintf(fpo,"%-40s %30d\n", "__Climate_files", IData.ClimateFileNumber);

    for(i=0; i<IData.ClimateFileNumber;i++) 
	{
		fprintf(fpo,"%-40d %40s\n", i+1, ClimateFilename.get(i+1));
    }

	fprintf(fpo,"%-40s %30d\n", "__Climate_file_mode", IData.if1File);
	fprintf(fpo,"%-40s %30.4f\n", "__CO2_increase_rate", IData.CO2IncreaseRate);

	fprintf(fpo,"%-40s %30d\n", "__CO2_File_Mode", IData.CO2file);//fprintf(fpo,"%-40s %30d\n", "__None", 0);

	if(IData.CO2file==1)
	{
		fprintf(fpo,"%-40s %40s\n", "__CO2_FileName", IData.CO2FileName);//fprintf(fpo,"%-40s %30d\n", "__None", 0);
	}
	else
	{
		fprintf(fpo,"%-40s %40s\n", "__CO2_FileName", "");//fprintf(fpo,"%-40s %30d\n", "__None", 0);
		IData.CO2FileName="";
	}


	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);

	
        // Soil parameter
    fprintf(fpo,"----------------------------------------\n");
	fprintf(fpo,"%-40s\n", "Soil_data");
	fprintf(fpo,"\n%-40s %30d\n", "__Land_use_ID", IData.Soil_landuse);
	fprintf(fpo,"%-40s %30d\n", "__Soil_texture_ID", IData.Soil_Texture);
	fprintf(fpo,"%-40s %30.4f\n", "__Bulk_density", IData.Soil_Density);
	fprintf(fpo,"%-40s %30.4f\n", "__pH", IData.Soil_pH);
	fprintf(fpo,"%-40s %30.4f\n", "__Clay_fraction", IData.Soil_Clay);
	fprintf(fpo,"%-40s %30.4f\n", "__Porosity", IData.Soil_Porosity);
	fprintf(fpo,"%-40s %30.4f\n", "__Bypass_flow", IData.Soil_BypassFlow);
	fprintf(fpo,"%-40s %30.4f\n", "__Field_capacity", IData.Fldcap);
	fprintf(fpo,"%-40s %30.4f\n", "__Wilting_point", IData.Wiltpt);
	fprintf(fpo,"%-40s %30.4f\n", "__Hydro_conductivity", IData.Sks);

	fprintf(fpo,"%-40s %30.4f\n", "__Top_layer_SOC", IData.Soil_OCatSurface);
	fprintf(fpo,"%-40s %30.4f\n", "__Litter_fraction", IData.Soil_Litter);
	fprintf(fpo,"%-40s %30.4f\n", "__Humads_fraction", IData.Soil_humads);
	fprintf(fpo,"%-40s %30.4f\n", "__Humus_fraction", IData.Soil_humus);
	fprintf(fpo,"%-40s %30.4f\n", "__Adjusted_litter_factor", IData.DClitter);
	fprintf(fpo,"%-40s %30.4f\n", "__Adjusted_humads_factor", IData.DChumads);
	fprintf(fpo,"%-40s %30.4f\n", "__Adjusted_humus_factor", IData.DChumus);
	fprintf(fpo,"%-40s %30.4f\n", "__Humads_C/N", IData.HumadCN);
	fprintf(fpo,"%-40s %30.4f\n", "__Humus_C/N", IData.HumusCN);
	fprintf(fpo,"%-40s %30.4f\n", "__Black_C", IData.PassiveC);
	fprintf(fpo,"%-40s %30.4f\n", "__Black_C_C/N", IData.PassiveCCN);
	fprintf(fpo,"%-40s %30.4f\n", "__SOC_profile_A", IData.SOCa);
	fprintf(fpo,"%-40s %30.4f\n", "__SOC_profile_B", IData.SOCb);
	fprintf(fpo,"%-40s %30.4f\n", "__Initial_nitrate_ppm", IData.Soil_NO3);
	fprintf(fpo,"%-40s %30.4f\n", "__Initial_ammonium_ppm", IData.Soil_NH4);
	fprintf(fpo,"%-40s %30.4f\n", "__Soil_microbial_index", IData.Soil_MicrobioIndex);
	fprintf(fpo,"%-40s %30.4f\n", "__Soil_slope", IData.slope);
	fprintf(fpo,"%-40s %30.4f\n", "__Lateral_influx_index", IData.LateralInflux);
	fprintf(fpo,"%-40s %30.4f\n", "__Drainage_Efficiency", IData.HighestWT);if(IData.HighestWT==1)IData.Soil_WaterObstructLayer=2.5; else IData.Soil_WaterObstructLayer=2.0;
	fprintf(fpo,"%-40s %30.4f\n", "__WaterTable_Depth", IData.Soil_WaterObstructLayer);//Water_retension_layer_depth
	fprintf(fpo,"%-40s %30.4f\n", "__Soil_salinity", IData.Soil_Quality);
	fprintf(fpo,"%-40s %30d\n", "__SCS_curve_use", IData.SCSuse);
	

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
		
		fprintf(fpo,"%-40s %30.4f\n", "____SCS_curve_number", m_CN);
		fprintf(fpo,"%-40s %30.4f\n", "____Land_surface_roughness", m_RoughLand);
		fprintf(fpo,"%-40s %30.4f\n", "____Channel_surface_roughness", m_RoughChannel);
		fprintf(fpo,"%-40s %30.4f\n", "____Channel_slope", m_ChannelSlope);
		fprintf(fpo,"%-40s %30.4f\n", "____Channel_length", m_ChannelLength);
		fprintf(fpo,"%-40s %30.4f\n", "____Land_management_factor", m_LandManage);
	}
	fprintf(fpo,"%-40s %30.4f\n", "__Deep_WaterPoolBD", IData.WaterPoolBD);//printed water pool
	fprintf(fpo,"%-40s %30d\n", "__Soil_Profile_Type", IData.ProfileType);
	
	//CString ProfileFileName;
	//ProfileFileName="C:\dndc\File";
if(IData.ProfileType==0)
{IData.ProfileFileName="";}
	fprintf(fpo,"%-34s %40s\n","__Profile_File_Name", IData.ProfileFileName);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);
	fprintf(fpo,"%-40s %30d\n", "__None", 0);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CString FCT30;
	
	 
#ifdef MANURE	
			
/*	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d", &TotalFarmFields);
	fclose(xff);
*/
	//fprintf(fpo,"Farm_mode					%d %d\n",1, TotalFarmFields);
#else
	TotalFarmFields = 1;		
	//fprintf(fpo,"Farm_mode					%d %d\n",0, 1);
#endif

for(int CSL=1; CSL<=TotalFarmFields; CSL++)
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
					if(IData.db_TreeCurrentAge[rrr][yyy][ccc]<0.0) IData.db_TreeCurrentAge[rrr][yyy][ccc] = 0.0;
					if(IData.db_TreeAge[rrr][yyy][ccc]<0.0) IData.db_TreeAge[rrr][yyy][ccc] = 0.0;
			}
			fclose(db);
		}
	}

    fprintf(fpo,"----------------------------------------\n");
	fprintf(fpo,"%-40s\n", "Crop_data");
	fprintf(fpo,"\n%-40s %30d\n", "Cropping_systems", IData.db_Rotation_Number);

    for (rrr = 1; rrr<=IData.db_Rotation_Number;rrr++) 
	{
		fprintf(fpo,"\n%-40s %30d\n", "__Cropping_system", rrr);
		fprintf(fpo,"%-40s %30d\n", "__Total_years", IData.db_RotateSpan[rrr]);
		fprintf(fpo,"%-40s %30d\n", "__Years_of_a_cycle", IData.db_CycleSpan[rrr]);

        for (j = 1; j<=IData.db_CycleSpan[rrr];j++) 
		{
			fprintf(fpo,"\n%-40s %30d\n", "____Year", j);
			fprintf(fpo,"%-40s %30d\n", "____Crops", IData.db_YrCrops[rrr][j]);
			
            for (k = 1; k<= IData.db_YrCrops[rrr][j];k++)
			{
				if(IData.db_TreeCurrentAge[rrr][j][k]<0.0) IData.db_TreeCurrentAge[rrr][j][k] = 0.0;

				fprintf(fpo,"%-40s %30d\n", "______Crop#", k);
				fprintf(fpo,"%-40s %30d\n", "______Crop_ID", IData.db_YrCropType[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______Planting_month", IData.db_PMonth[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______Planting_day", IData.db_PDay[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______Harvest_month", IData.db_HMonth[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______Harvest_day", IData.db_HDay[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______Harvest_year", IData.db_HYr[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Residue_left_in_field", IData.db_Residue[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Maximum_yield", IData.db_Yield[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Leaf_fraction", IData.db_LeafFraction[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Stem_fraction", IData.db_ShootFraction[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Root_fraction", IData.db_RootFraction[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Grain_fraction", IData.db_GrainFraction[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Leaf_C/N", IData.db_LeafCN[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Stem_C/N", IData.db_ShootCN[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Root_C/N", IData.db_RootCN[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Grain_C/N", IData.db_GrainCN[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Accumulative_temperature", IData.db_TDD[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Optimum_temperature", IData.db_OptT[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Water_requirement", IData.db_Water[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______N_fixation_index", IData.db_Nfix[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Root_Depth", IData.db_Vascularity[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______If_cover_crop", IData.db_CoverCrop[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______If_perennial_crop", IData.db_PerennialCrop[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______If_transplanted", IData.db_Transplant[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Tree_maturity_age", IData.db_TreeAge[rrr][j][k]);

				fprintf(fpo,"%-40s %30.4f\n", "______Tree_current_age", IData.db_TreeCurrentAge[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Tree_max_leaf", IData.db_TreeLeafMax[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Tree_min_leaf", IData.db_TreeLeafMin[rrr][j][k]);
				
				fprintf(fpo,"%-40s %30d\n", "______Root_Shape", IData.db_RootShape[rrr][j][k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Grain_Fill", IData.db_GrainFill[rrr][j][k]);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n\n", "______None", 0);
            }

  fprintf(fpo,"----------------------------------------\n");
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

			fprintf(fpo,"%-40s %30d\n", "____Till_applications", NNN);
            
            for (k = 1; k<= NNN; k++) 
			{
				fprintf(fpo,"%-40s %30d\n", "______Till#", k);
				fprintf(fpo,"%-40s %30d\n", "______Till_month", TillMonth[k]);
				fprintf(fpo,"%-40s %30d\n", "______Till_day", TillDay[k]);
				fprintf(fpo,"%-40s %30d\n", "______Till_method", TillMethod[k]);
            }

fprintf(fpo,"----------------------------------------\n");
            int FertOption=0, jd=0;

			sprintf(DB, "%s\\CropFert_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &FertOption);

			if(FertOption==-2)//Auto-fertilization
			{
				fscanf(db, "%f %f %f %f %f", &DayRelease[0], &NIefficiency[0], &NIduration[0],
						&UreaseEfficiency[0], &UreaseDuration[0]);

			}
			else if(FertOption==-1)//Fertigation
			{
				fscanf(db, "%s", FertigationFile);
				fscanf(db, "%f %f %f %f %f", &DayRelease[0], &NIefficiency[0], &NIduration[0],
						&UreaseEfficiency[0], &UreaseDuration[0]);
			}
			else if(FertOption==-3)
			{
				fscanf(db, "%f %f %f %f %f", &DayRelease[0], &NIefficiency[0], &NIduration[0],
						&UreaseEfficiency[0], &UreaseDuration[0]);
			}
			else
			{
				for(i=1; i<=FertOption; i++)
				{
					fscanf(db, "%d %d %d", &FertMonth[i], &FertDay[i], &FertMethod[i]);
					fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[i], &FertAbi[i], &FertUrea[i], &FertAnh[i], 
						&FertAmNi[i], &NH42SO4[i], &NH42HPO4[i], &FertDepth[i]);
					fscanf(db, "%f %f %f %f %f", &DayRelease[i], &NIefficiency[i], &NIduration[i],
						&UreaseEfficiency[i], &UreaseDuration[i]);
				}
				fscanf(db, "%d", &jd);
			}
			fclose(db);

			fprintf(fpo,"%-40s %30d\n", "____Fertilizer_applications", FertOption);

			if(FertOption==-1)//Fertigation
			{
				fprintf(fpo,"%-40s %30s\n", "______Fertilization_file", FertigationFile);
				fprintf(fpo,"%-40s %30.4f\n", "______Slow_release_rate", DayRelease[0]); 
				fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_efficiency", NIefficiency[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_duration", NIduration[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_efficiency", UreaseEfficiency[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_duration", UreaseDuration[0]);
			}
			if(FertOption==-2)//Auto-fertilization
			{
				fprintf(fpo,"%-40s %30.4f\n", "______Slow_release_rate", DayRelease[0]); 
				fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_efficiency", NIefficiency[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_duration", NIduration[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_efficiency", UreaseEfficiency[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_duration", UreaseDuration[0]);
			}
			if(FertOption==-3)//Precision fertilization
			{
				fprintf(fpo,"%-40s %30.4f\n", "______Slow_release_rate", DayRelease[0]); 
				fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_efficiency", NIefficiency[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_duration", NIduration[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_efficiency", UreaseEfficiency[0]);
				fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_duration", UreaseDuration[0]);
			}
			else
			{
				for(k=1; k<=FertOption; k++) 
				{
					fprintf(fpo,"%-40s %30d\n", "______Fertilizing#", k);
					fprintf(fpo,"%-40s %30d\n", "______Fertilizing_month", FertMonth[k]);
					fprintf(fpo,"%-40s %30d\n", "______Fertilizing_day", FertDay[k]);
					fprintf(fpo,"%-40s %30d\n", "______Fertilizing_method", FertMethod[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Fertilizing_depth", FertDepth[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Nitrate", FertNitrate[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Ammonium_bicarbonate", FertAbi[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Urea", FertUrea[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Anhydrous_ammonia", FertAnh[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Ammonium", FertAmNi[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Sulphate", NH42SO4[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Phosphate", NH42HPO4[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Slow_release_rate", DayRelease[k]); 
					fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_efficiency", NIefficiency[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Nitrification_inhibitor_duration", NIduration[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_efficiency", UreaseEfficiency[k]);
					fprintf(fpo,"%-40s %30.4f\n", "______Urease_inhibitor_duration", UreaseDuration[k]);	
					
					fprintf(fpo,"%-40s %30d\n", "______None", 0);
					fprintf(fpo,"%-40s %30d\n", "______None", 0);
					fprintf(fpo,"%-40s %30d\n", "______None", 0);
					fprintf(fpo,"%-40s %30d\n", "______None", 0);
					fprintf(fpo,"%-40s %30d\n", "______None", 0);				
					
				}

				fprintf(fpo,"%-40s %30d\n", "____Fertilization_option", 0); 
				
			}

fprintf(fpo,"----------------------------------------\n");
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

			fprintf(fpo,"%-40s %30d\n", "____Manure_applications", n);

            for(k=1; k<= n; k++) 
			{
				fprintf(fpo,"%-40s %30d\n", "______Manuring#", k);
				fprintf(fpo,"%-40s %30d\n", "______Manuring_month", ManuMonth[k]);
				fprintf(fpo,"%-40s %30d\n", "______Manuring_day", ManuDay[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_amount", ManuAmount[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_C/N", ManuCN[k]);
				fprintf(fpo,"%-40s %30d\n", "______Manure_type", ManuType[k]);
				fprintf(fpo,"%-40s %30d\n", "______Manuring_method", manu_method[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_depth", ManureDepth[k]);
			
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_OrgN", ManuN[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_NH4", ManureNH4[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_NO3", ManureNO3[k]);
				fprintf(fpo,"%-40s %30d\n", "______Manure_AppHour", ManureAppHour[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_DM", ManureDM[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Manure_PH", ManurePH[k]);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
            }
            
fprintf(fpo,"----------------------------------------\n");
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
			
			fprintf(fpo,"%-40s %30d\n", "____Film_applications", n);
			fprintf(fpo,"%-40s %30d\n", "____Method", WeedOption);

            for (k = 1; k<= n;k++) 
			{
				fprintf(fpo,"%-40s %30d\n", "______Filming#", k);
				fprintf(fpo,"%-40s %30d\n", "______Start_month", WeedMonth1[k]);
				fprintf(fpo,"%-40s %30d\n", "______Start_day", WeedDay1[k]);
				fprintf(fpo,"%-40s %30d\n", "______End_month", WeedMonth2[k]);
				fprintf(fpo,"%-40s %30d\n", "______End_day", WeedDay2[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Cover_fraction", CoverFraction[k]);

				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
            }
         
fprintf(fpo,"----------------------------------------\n");
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
           
			fprintf(fpo,"%-40s %30d\n", "____Flood_applications", n);
			fprintf(fpo,"%-40s %30d\n", "____Water_control", WaterControl);
			fprintf(fpo,"%-40s %30.4f\n", "____Flood_water_N", FloodWaterN);
			fprintf(fpo,"%-40s %30.4f\n", "____Leak_rate", WaterLeakRate);
			fprintf(fpo,"%-40s %30.4f\n", "____Water_gather_index", WaterGetherIndex);
			fprintf(fpo,"%-40s %30s\n", "____Watertable_file", WT_file);
			fprintf(fpo,"%-40s %30.4f\n", "____Empirical_para_1", m_IniWT);
			fprintf(fpo,"%-40s %30.4f\n", "____Empirical_para_2", m_LWTceasingSurfFlow);
			fprintf(fpo,"%-40s %30.4f\n", "____Empirical_para_3", m_LWTceasingGroungFlow);
			fprintf(fpo,"%-40s %30.4f\n", "____Empirical_para_4", m_WatershedIndex);
			fprintf(fpo,"%-40s %30.4f\n", "____Empirical_para_5", m_SurfOutflowIntensity);
			fprintf(fpo,"%-40s %30.4f\n", "____Empirical_para_6", m_GroundOutflowIntensity);

            for(k=1; k<=n; k++) 
			{
				fprintf(fpo,"%-40s %30d\n", "______Flooding#", k);
				fprintf(fpo,"%-40s %30d\n", "______Start_month", FlooMonth1[k]);
				fprintf(fpo,"%-40s %30d\n", "______Start_day", FlooDay1[k]);
				fprintf(fpo,"%-40s %30d\n", "______End_month", FlooMonth2[k]);
				fprintf(fpo,"%-40s %30d\n", "______End_day", FlooDay2[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Water_N", FlooN[k]);
				fprintf(fpo,"%-40s %30d\n", "______Alter_wet_dry", ShallowFlood[k]);	
				
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
			}
			
fprintf(fpo,"----------------------------------------\n");			
			sprintf(DB, "%s\\CropIrri_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d %d %f %d", &n, &IrrMode, &IrrIndex, &IrriMethod[0]);
			for(i=1; i<=n; i++)
				{
					fscanf(db, "%d %d", &IrriMonth[i], &IrriDay[i]);
					fscanf(db, "%f %d %d", &IrriAmount[i], &IrriMethod[i],&TileIrriDays[i]);
				}
			fclose(db);
            
			fprintf(fpo,"%-40s %30d\n", "____Irrigation_applications", n);
			fprintf(fpo,"%-40s %30d\n", "____Irrigation_control", IrrMode);
			fprintf(fpo,"%-40s %30.4f\n", "____Irrigation_index", IrrIndex);
			fprintf(fpo,"%-40s %30d\n", "____Irrigation_method", IrriMethod[0]);

            for(k=1; k<=n; k++)
			{
				fprintf(fpo,"%-40s %30d\n", "______Irrigation#", k);
				fprintf(fpo,"%-40s %30d\n", "______Irri_month", IrriMonth[k]);
				fprintf(fpo,"%-40s %30d\n", "______Irri_day", IrriDay[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Water_amount", IrriAmount[k]);
				fprintf(fpo,"%-40s %30d\n", "______Irri_method", IrriMethod[k]);

				fprintf(fpo,"%-40s %30d\n", "______TileIrriDays", TileIrriDays[k]);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
            }
//write out controlled Drainage
fprintf(fpo,"----------------------------------------\n");	
			sprintf(DB, "%s\\CTDrain_%d_%d.txt", FCT30, rrr, j);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &n);
			for (i = 1; i<=n;i++) 
			{
				fscanf(db, "%d %d", &DrainMonth[i], &DrainDay[i]);
				fscanf(db, "%d %d %f", &DrainMonth2[i], &DrainDay2[i],&CDrainDepth[i]);
			}
			fclose(db);

			fprintf(fpo,"%-40s %30d\n", "____ControlledDrainage_applications", n);

			for(k=1; k<=n; k++)
			{
				fprintf(fpo,"%-40s %30d\n", "______CDrain#", k);
				fprintf(fpo,"%-40s %30d\n", "______CDrain_stmonth", DrainMonth[k]);
				fprintf(fpo,"%-40s %30d\n", "______CDrain_stday", DrainDay[k]);
				fprintf(fpo,"%-40s %30d\n", "______CDrain_endmonth", DrainMonth2[k]);
				fprintf(fpo,"%-40s %30d\n", "______CDrain_endday", DrainDay2[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______CDrain_Depth", CDrainDepth[k]);
				            }
//end write out controlled Drainage		
fprintf(fpo,"----------------------------------------\n");
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
            
			fprintf(fpo,"%-40s %30d\n", "____Grazing_applications", n);		
        
            for(k=1; k<=n; k++)
			{
				fprintf(fpo,"%-40s %30d\n", "______Grazing#", k);
				fprintf(fpo,"%-40s %30d\n", "______Start_month", GrazMonth1[k]);
				fprintf(fpo,"%-40s %30d\n", "______Start_day", GrazDay1[k]);
				fprintf(fpo,"%-40s %30d\n", "______End_month", GrazMonth2[k]);
				fprintf(fpo,"%-40s %30d\n", "______End_day", GrazDay2[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Dairy_heads", Dairy[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Beef_heads", Beef[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Pig_heads", Pig[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Sheep_heads", Sheep[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Horse_heads", Horse[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Grazing_hours/day", GrazHour[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Additional_feed", AddFeed[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Additional_feed_C/N", FeedCN[k]);
				fprintf(fpo,"%-40s %30d\n", "______Excreta_handling", Excreta[k]);

				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
	
            }

fprintf(fpo,"----------------------------------------\n");
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
           
			fprintf(fpo,"%-40s %30d\n", "____Cut_applications", n);	

            for(k=1; k<=n; k++) 
			{
				fprintf(fpo,"%-40s %30d\n", "______Cut#", k);
				fprintf(fpo,"%-40s %30d\n", "______Cut_month", CutMonth[k]);
				fprintf(fpo,"%-40s %30d\n", "______Cut_day",  CutDay[k]);
				fprintf(fpo,"%-40s %30.4f\n", "______Cut_fraction", CutAmount[k]);
				fprintf(fpo,"%-40s %30d\n", "______Cut_part",  CutPart[k]);

				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
				fprintf(fpo,"%-40s %30d\n", "______None", 0);
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fprintf(fpo,"----------------------------------------\n");
	//fprintf(fpo,"Crop_model_approach         %d\n", 0);//IData.CropModel);
   	fprintf(fpo,"%-40s\n", "____Extra_Parameters");
	fprintf(fpo,"%-40s %30.4f\n", "______DrainDepth(m)", IData.DrainDepth);
	fprintf(fpo,"%-40s %30.4f\n", "______DrainSpace(m)", IData.DrainSpace);
	fprintf(fpo,"%-40s %30.4f\n", "______DrainRadius(m)", IData.DrainRad);
	fprintf(fpo,"%-40s %30.4f\n", "______Drain_to_Bedrock(m)", IData.DrainBed);
	fprintf(fpo,"%-40s %30.4f\n", "______keDrain_Factor", IData.keDrain);
	fprintf(fpo,"%-40s %30.4f\n", "______MaxN_movement", IData.MaxNMove);
	fprintf(fpo,"%-40s %30.4f\n", "______MobileN_Factor", IData.MobileNF);
	fprintf(fpo,"%-40s %30.4f\n", "______Pref_NLayerFraction", IData.NLayerF);
	fprintf(fpo,"%-40s %30.4f\n", "______N_Leaching_Factor", IData.NMoveRate);
	fprintf(fpo,"%-40s %30.4f\n", "______Soil_Evaporation_Factor", IData.SoilEvapF);
	fprintf(fpo,"%-40s %30.4f\n", "______Runoff_Water_Factor", IData.RunOffWF);
	fprintf(fpo,"%-40s %30.4f\n", "______Runoff_N_Factor", IData.RunOffNF);
	fprintf(fpo,"%-40s %30.4f\n", "______Overall_NitrificationF", IData.Factor1);
	fprintf(fpo,"%-40s %30.4f\n", "______Snow_Insulation_Factor", IData.Factor2);
	fprintf(fpo,"%-40s %30.4f\n", "______Snow_Melt_Factor", IData.Factor3);
	fprintf(fpo,"%-40s %30.4f\n", "______Denitrifier_Grow", IData.DenitGRate);
	fprintf(fpo,"%-40s %30.4f\n", "______Nitrier_Grow", IData.NitGRate);
	fprintf(fpo,"%-40s %30.4f\n", "______N2O_Rain_Factor", IData.N2ORain);
	fprintf(fpo,"%-40s %30.4f\n", "______Spring_Melt_N2O_F", IData.SprMeltF);
	fprintf(fpo,"%-40s %30.4f\n", "______N_Retention_F", IData.Factor4);
	fprintf(fpo,"%-40s %30.4f\n", "______NH3_Vol_Multi", IData.Factor5);
	fprintf(fpo,"%-40s %30.4f\n", "______Pref_N_Move2", IData.Factor6);
	fprintf(fpo,"%-40s %30d\n", "______AutoHarvest", IData.Factor7);
	fprintf(fpo,"%-40s %30.4f\n", "______SoilStructEffect", IData.Factor8);
	fprintf(fpo,"%-40s %30.4f\n", "______SoilReset", IData.Factor9);
    fprintf(fpo,"%-40s %30d\n", "______UseSpinUpFile", IData.SpinUpCheck);
	fprintf(fpo,"%-40s %30d\n", "______ReadSpinUpYears", IData.SpinUpYears);
	if(IData.SpinUpCheck==1)
	{
	fprintf(fpo,"%-40s %40s\n", "______SpinUpFileName", IData.SpinUpFileName);
	}
	else
	{
	fprintf(fpo,"%-40s %30s\n", "______SpinUpFileName", "0");
	}
	fprintf(fpo,"%-40s %30.4f\n", "______WTEffectonSoilWaterContent", IData.Factor10);
	fprintf(fpo,"%-40s %30.4f\n", "______RainFallInterceptFactor", IData.Factor11);//WTEffectonTextureSWC
	fprintf(fpo,"%-40s %30.4f\n", "______SolarRadEffectonSoilTemp", IData.Factor13);
	fprintf(fpo,"%-40s %30.4f\n", "______UreaHydrolysisFactor", IData.UreaHydro);
	fprintf(fpo,"%-40s %30.4f\n", "______UreaHydrolysisWaterFactor", IData.UreaHydro2);	
	fprintf(fpo,"%-40s %30.4f\n", "______NH3SoilDepthFactor", IData.NH3SoilDF);	
	fprintf(fpo,"%-40s %30.4f\n", "______UreaDiffusionFactor", IData.UreaDifF);	

    fclose (fpo);
}
