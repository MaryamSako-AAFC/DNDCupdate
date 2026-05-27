#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "RunPaths.h"
#include "dndc_main.h"
#include <io.h>
#include <direct.h>
#include <math.h>
#include "dndc_tool.h"

extern Site_BaseInformation	IData;
extern StringArray	ClimateFilename;
float jf;

void ReadDNDfile(char *fname, int UseID)
{
	float nSoca[6]={0.0,0.2,0.2,0.08,0.05,0.2};
	float nSocb[6]={10.0,2.0,2.0,1.4,4.0,2.0};
	int NutritionModelX, AllFarmFields=0, x, jd;

	int  i, j, k, cropn, MissFlag=0, yr, note_flag=0;
	int floon, ShallowFlood, WaterControl, FlooMonth1, FlooDay1, FlooMonth2, FlooDay2;
	float FlooN, WaterGetherIndex, WaterLeakRate;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex,m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	float FloodWaterN;
	char notes[255],tmp[255],ffname[300];
    FILE *fp;

	CString txt;

	sprintf(ffname, "%s", fname);

	fp=sopen(ffname,"r");
	if(fp==NULL) note(0, ffname);
	
  	Site_BaseInformation();
	ClimateFilename.clear();

	int Line=1, US;

	fscanf(fp,"%s",notes);//DNDC_Input_Parameters

	fscanf(fp,"%s",notes);//"--------------------"
	
	fscanf(fp, "%s", notes);//Site_information
	fscanf(fp, "%s %s", notes, IData.sitename);		
	fscanf(fp, "%s %d", notes, &IData.years);
    fscanf(fp, "%s %f", notes, &IData.latitude);
	fscanf(fp, "%s %d", notes, &IData.ifdaily);
	fscanf(fp, "%s %d", notes, &US);	
	
	if(US==0||US==1) US = US;
	else US = 0;
	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Inter\\UnitSystem", OUTPUT);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", US);
	fclose(ddb);
	
	for(x=1; x<=5; x++) fscanf(fp,"%s %d", notes, &jd);

#ifdef MANURE

	int HouseInputFormat, AnimalTypes, AnimalType[10];
	char HouseInputFileName[200], IndoorClimateFile[300];
	float AnimalHeads[10],FeedRate[10],FeedProtein[10],FeedTP[10];
	float BodyWeight[10], DryMatterFraction[10], MilkProtein[10], DaysInMilk[10];//new
	float NDF[10], ADF[10], Lignin[10], FAT[10], ASH[10];//new
	int FeedAdditiveType[10];//new
	float FeedAdditiveRate[10];//new
	int EmpiricalModel;//new

	float m_FloorArea,m_BedCN, m_VentRate, m_BedRate, m_BedFrequency,PenBedFrequency;
	int m_FloorSurface, m_BedType, m_Ventilation;
	int PenInputFormat, PenAnimalTypes, PenAnimalType[15],PenSurface,PenBedMaterial; 
	char PenInputFileName[200];
	float PenAnimalHeads[15],PenFeedRate[15],PenFeedProtein[15],PenFeedTP[15],PenArea,PenBedCN,PenBedAmount;
	int GrazeInputFormat, GrazeAnimalType, GrazeTimes, IniMonth[366],IniDay[366],EndMonth[366],EndDay[366];
	char GrazeInputFileName[200];
	float GrazeAnimalHeads[366],GrazeAnimalHrs[366], GrazeArea;
	float m_LagoonCapacity, m_LagoonSurfaceArea, LagoonToField[30], LagoonToDigester[30], LagoonRemain[30], LagoonManureAplDepth[30];
	int m_LagoonYear;//new

	int m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes, LagoonDrainMonth[30], LagoonDrainDay[30], LagoonManureAplMethod[30];
	float m_CompostDensity, m_LitterAmount, m_LitterCN, CompostToField, CompostToMarket, CompostRemain;
	float m_DigesterCapacity,m_DigesterCH4,m_DigesterDays, DigesterToField;
	int m_Temp, m_Flash, HouseID, m_CompostCover, m_CompostRemoveTimes, CompostRemoveMonth, CompostRemoveDay;
	float DigesterToLagoon, DigesterRemain, m_FlushWater, LiquidFraction;
	float HouseManureOutDays,m_UC, m_UL, m_UD, m_UF, m_UR, m_FC, m_FL, m_FD, m_FF, m_FR;
	float PenManureOutDays, PenUC, PenUL,PenUD,PenUR,PenFC, PenFL,PenFD,PenFR;
	float GrazeManureOutDays, GrazeUF, GrazeUR, GrazeFF, GrazeFR, FieldArea;
	int Compostt;
	
	CString MP;
	FILE *mp;
	CString SF;
	FILE* sf;


	//read feedlot housing etc.
	int m_FeedLots, m_FeedlotYears;

	fscanf(fp,"%s", notes);//--------------------------
	fscanf(fp,"%s", notes);
	fscanf(fp,"%s %d", notes, &m_FeedlotYears);

	for(int m_FeedlotYear=1; m_FeedlotYear<=m_FeedlotYears; m_FeedlotYear++)
	{
		fscanf(fp,"%s %d", notes, &yr);
		fscanf(fp,"%s %d", notes, &m_FeedLots);

		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Inter\\TotalFeedLots_%d", OUTPUT, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", m_FeedLots);
		fclose(TFL);

		for(i=1; i<=m_FeedLots; i++)
		{
			fscanf(fp,"%s %d", notes, &HouseID);
			fscanf(fp, "%s %d", notes, &EmpiricalModel);//new
			fscanf(fp,"%s %d", notes, &HouseInputFormat);
		
			if(HouseInputFormat==1||HouseInputFormat==2)
				fscanf(fp,"%s %s", notes, HouseInputFileName);
			else if(HouseInputFormat==3)
				fscanf(fp,"%s %d", notes, &NutritionModelX);
			else
			{
				fscanf(fp,"%s %d", notes, &AnimalTypes);
				fscanf(fp,"%s %d", notes, &AnimalType[1]);
				fscanf(fp,"%s %f", notes, &AnimalHeads[1]);
				fscanf(fp,"%s %f", notes, &FeedRate[1]);
				fscanf(fp,"%s %f", notes, &FeedProtein[1]);
				fscanf(fp,"%s %f", notes, &FeedTP[1]);	

				//new
				fscanf(fp, "%s %f", notes, &BodyWeight[1]);
				fscanf(fp, "%s %f", notes, &DryMatterFraction[1]);
				fscanf(fp, "%s %f", notes, &MilkProtein[1]);
				fscanf(fp, "%s %f", notes, &DaysInMilk[1]);
				fscanf(fp, "%s %f", notes, &NDF[1]);
				fscanf(fp, "%s %f", notes, &ADF[1]);
				fscanf(fp, "%s %f", notes, &Lignin[1]);
				fscanf(fp, "%s %f", notes, &FAT[1]);
				fscanf(fp, "%s %f", notes, &ASH[1]);
				fscanf(fp, "%s %d", notes, &FeedAdditiveType[1]);
				fscanf(fp, "%s %f", notes, &FeedAdditiveRate[1]);

				
				for(x=1; x<=5; x++) fscanf(fp,"%s %d", notes, &jd);//5 blank scans for the none______ in dnd file
			}
				
			fscanf(fp,"%s %f", notes, &m_FloorArea);
			fscanf(fp,"%s %d", notes, &m_FloorSurface);
			
			fscanf(fp,"%s %d", notes, &m_BedType);
			fscanf(fp,"%s %f", notes, &m_BedCN);
			fscanf(fp,"%s %f", notes, &m_BedFrequency);
			fscanf(fp,"%s %f", notes, &m_BedRate);
					
			fscanf(fp,"%s %d", notes, &m_Ventilation);
			fscanf(fp,"%s %f", notes, &m_VentRate);
			fscanf(fp,"%s %s", notes, IndoorClimateFile);
					
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
			fscanf(fp,"%s %d", notes, &m_Flash);
			fscanf(fp,"%s %f", notes, &m_FlushWater);
			fscanf(fp,"%s %f", notes, &LiquidFraction);

			for(x=1; x<=3; x++) fscanf(fp,"%s %d", notes, &jd);

			SF.Format("%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
			sf=fopen(SF, "w");
			//new

			fprintf(sf, "%d\n", EmpiricalModel); //UCD empirical model calculating GHG and Manure
			fprintf(sf, "%d\n", FeedAdditiveType[1]); //FeedAdditive for CH4 mitigation
			fprintf(sf, "%f\n", FeedAdditiveRate[1]); //FeedAdditive for CH4 mitigation


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
				//new
				fprintf(sf, "%f  %f  %f  %f\n", BodyWeight[1], 100 * DryMatterFraction[1], MilkProtein[1], DaysInMilk[1]);
				fprintf(sf, "%f  %f  %f  %f  %f\n", NDF[1], ADF[1], Lignin[1], FAT[1], ASH[1]);
			}
			fprintf(sf, "%f  %d\n", m_FloorArea, m_FloorSurface);//0 slatted floor; 1 conrete floor	
			fprintf(sf, "%d  %f  %f  %f\n", m_BedType, m_BedCN, m_BedFrequency, m_BedRate);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			fprintf(sf, "%d  %f  %s\n", m_Ventilation, m_VentRate, IndoorClimateFile);// 0 natural, 1 fan, -1 IndoorClimateFile
			fprintf(sf, "%f\n", HouseManureOutDays);
			fprintf(sf, "%f %f %f %f %f\n", m_UC, m_UL, m_UD, m_UF, m_UR);
			fprintf(sf, "%f %f %f %f %f\n", m_FC, m_FL, m_FD, m_FF, m_FR);
			fprintf(sf, "%d %f %f\n", m_Flash, m_FlushWater, LiquidFraction);
			fclose(sf);
		}//end of feedlots loop
	}//end of feedlots years loop


	//need to read in m_LagoonYear to figure out how to loop through indendent lagoon management.
	int m_LagoonYears;
	m_LagoonYears = m_FeedlotYears;
	for (int m_LagoonYear = 1; m_LagoonYear <= m_LagoonYears; m_LagoonYear++)
	{
		fscanf(fp, "%s %f", notes, &m_LagoonCapacity);
		fscanf(fp, "%s %f", notes, &m_LagoonSurfaceArea);
		fscanf(fp, "%s %d", notes, &m_LagoonCover);
		fscanf(fp, "%s %d", notes, &m_LagoonRain);

		fscanf(fp, "%s %d", notes, &m_LagoonDrainTimes);
		for (i = 1; i <= m_LagoonDrainTimes; i++)
		{
			if (note_flag == 1)
			{
				fscanf(fp, "%d", &jd);
				note_flag = 0;
			}
			else fscanf(fp, "%s %d", notes, &jd);
			fscanf(fp, "%s %d", notes, &LagoonDrainMonth[i]);
			fscanf(fp, "%s %d", notes, &LagoonDrainDay[i]);
			fscanf(fp, "%s %f", notes, &LagoonToField[i]);
			fscanf(fp, "%s %f", notes, &LagoonToDigester[i]);
			fscanf(fp, "%s %f", notes, &LagoonRemain[i]);

			fscanf(fp, "%s", notes);
			if (strcmp(notes, "________Land_application_method") != 0)
			{
				LagoonManureAplMethod[i] = 0;
				LagoonManureAplDepth[i] = 1.0;
				note_flag = 1;
			}
			else
			{
				fscanf(fp, "%d", &LagoonManureAplMethod[i]);
				fscanf(fp, "%s %f", notes, &LagoonManureAplDepth[i]);
			}
		}
		//write out to inter file
		SF.Format("\%s\\Inter\\ManureLagoon_%d.txt", OUTPUT, m_LagoonYear);
		sf = fopen(SF, "w");
		fprintf(sf, "%f  %f  %d  %d  %d\n", m_LagoonCapacity, m_LagoonSurfaceArea, m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes);
		for (i = 1; i <= m_LagoonDrainTimes; i++)
		{
			fprintf(sf, "%d  %d  %f  %f  %f\n", LagoonDrainMonth[i], LagoonDrainDay[i], LagoonToField[i], LagoonToDigester[i], LagoonRemain[i]);
			fprintf(sf, "%d  %f\n", LagoonManureAplMethod[i], LagoonManureAplDepth[i]);
		}
		fclose(sf);
	}//LagoonYears
	
	if(note_flag==1) 
	{
		fscanf(fp,"%f", &m_CompostDensity);
		note_flag = 0;
	}
	else
		fscanf(fp,"%s %f",notes,&m_CompostDensity);

	fscanf(fp,"%s %d",notes,&m_CompostCover);
	fscanf(fp,"%s %d",notes,&m_CompostRemoveTimes);
	fscanf(fp,"%s %f",notes,&m_LitterAmount);
	fscanf(fp,"%s %f",notes,&m_LitterCN);

	SF.Format("%s\\Inter\\ManureCompost.txt", OUTPUT);
	sf=fopen(SF, "w");
	fprintf(sf, "%f  %d  %d  %f  %f\n", m_CompostDensity, m_CompostCover, m_CompostRemoveTimes, m_LitterAmount, m_LitterCN);  
	for(i=1;i<=m_CompostRemoveTimes;i++)
	{	
		fscanf(fp,"%s %d",notes, &jd);
		fscanf(fp,"%s %d",notes, &CompostRemoveMonth);
		fscanf(fp,"%s %d",notes, &CompostRemoveDay);
		fscanf(fp,"%s %f",notes, &CompostToField);
		fscanf(fp,"%s %f",notes, &CompostToMarket);
		fscanf(fp,"%s %f",notes, &CompostRemain);
		fprintf(sf, "%d %d %f %f %f\n", CompostRemoveMonth, CompostRemoveDay, CompostToField, CompostToMarket, CompostRemain);
	}
	fclose(sf);
	
	int m_DigesterType;
	fscanf(fp,"%s %d",notes, &m_DigesterType);	
	//fscanf(fp,"%s %f",notes, &m_DigesterCH4);
	fscanf(fp,"%s %f",notes, &m_DigesterDays);
	fscanf(fp,"%s %f",notes, &DigesterToField);
	fscanf(fp,"%s %f",notes, &DigesterToLagoon);
	fscanf(fp,"%s %f",notes, &DigesterRemain);

	if(m_DigesterType==0) m_DigesterCH4 = 0.12;//fracton of OC added
	else if(m_DigesterType==1) m_DigesterCH4 = 0.15;
	else if(m_DigesterType==2) m_DigesterCH4 = 0.1875;
	else m_DigesterCH4 = 0.0;

	
	SF.Format("%s\\Inter\\ManureDigester.txt", OUTPUT);
	sf=fopen(SF, "w");
	fprintf(sf, "%d  %f  %f\n", m_DigesterType, m_DigesterCH4, m_DigesterDays);  
	fprintf(sf, "%f  %f  %f\n", DigesterToField, DigesterToLagoon, DigesterRemain);
	fclose(sf);
	
	//land application
	int CropOrder, FarmCropType, TotalFarmYears, TotalFarmFields;
	float ManuCropArea[11]={0.0,0.0}, ManuFraction[11][50]={0.0,0.0};
	CString DB;
	FILE *db;

	fscanf(fp,"%s %f",notes, &FieldArea);
	fscanf(fp,"%s %d", notes, &TotalFarmFields);
	fscanf(fp,"%s %d", notes, &TotalFarmYears);

	DB.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);
	db=fopen(DB, "w");	
	fprintf(db, "%d %d\n", TotalFarmFields, TotalFarmYears); 
	fclose(db);	


	for(int FM=1; FM<=10; FM++)//TotalFarmFields
	{
		if(FM==1) fscanf(fp,"%s", notes);//"________Field_area");
		fscanf(fp,"%f", &ManuCropArea[FM]);
	}
					
	for(int FYR=1; FYR<=TotalFarmYears; FYR++)
	{
		fscanf(fp,"%s %d", notes, &jd);//"________Year", FYR);

		for(int FW=1; FW<=10; FW++)//TotalFarmFields
		{
			if(FW==1) fscanf(fp,"%s", notes);//"________Manure_fraction");
			fscanf(fp,"%f", &ManuFraction[FW][FYR]);

			DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, FW, FYR);
			db=fopen(DB, "w");	
			fprintf(db, "%d %f %f\n", FW, ManuCropArea[FW], ManuFraction[FW][FYR]); 
			fclose(db);
		}		
	}
	
	for(int FYRa=1; FYRa<=TotalFarmYears; FYRa++)
	{
		CString FCT0, FCT100;
		FCT100.Format("%s\\Inputs\\FarmCrop_%d", OUTPUT, FYRa);
		_mkdir(FCT100);
	}

	//if(FieldArea>0.0)
	//{
		MP.Format("%s\\Inter\\ManureField.txt", OUTPUT);
		mp=fopen(MP, "w");
		if(mp==NULL) note(1, MP);
		fprintf(mp, "%f\n", FieldArea);
		fclose(mp);
	//}


#endif
    
	fscanf(fp,"%s",notes);//"--------------------"
	
	fscanf(fp,"%s",notes);//Climate_data
	
	fscanf(fp,"%s %d", notes, &IData.ClimateFileType);
	fscanf(fp,"%s %f", notes, &IData.NO3NH4_Rainfall);	
	fscanf(fp,"%s %f", notes, &IData.NH3_Atmosphere);	
	fscanf(fp,"%s %f", notes, &IData.BaseCO2);		
	fscanf(fp,"%s %d", notes, &IData.ClimateFileNumber);	

	k=IData.ClimateFileType;
	int nn=IData.ClimateFileNumber;
	ClimateFilename.clear();
	//char* weatherName;
	for(i=1; i<=IData.ClimateFileNumber; i++) 
	{
		fscanf(fp,"%s", notes);		
		fgets(tmp,230,fp);
		EraseFBSpace(tmp);
		ClimateFilename.insert(301,tmp);
		//weatherName = tmp;
		//blah = ClimateFilename.[1][IData.ClimateFileNumber];
		//weatherName = ClimateFilename;
	}

	fscanf(fp,"%s %d", notes, &IData.if1File);
	fscanf(fp,"%s %f", notes, &IData.CO2IncreaseRate);



	fscanf(fp,"%s %d", notes, &IData.CO2file);
			if(IData.CO2file==1)
				{
				fscanf(fp,"%s",notes);//scan the ProfileFileName
				fgets(tmp,230,fp);//copied the code for the climate Name reading don't fully understand.
				EraseFBSpace(tmp);
				IData.CO2FileName=tmp;//set the file name to IData.ProfileFileName

				}
			else
				{
				fscanf(fp,"%s", notes);//probably should be %s fscanf(fp,"%s %d", notes, &jd)
				}

	//for(x=1; x<=5; x++) fscanf(fp,"%s %d", notes, &jd);
	// 
		//scans 5 notes at end of climate file
	for(x=1; x<=3; x++) fscanf(fp,"%s %d", notes, &jd);

	fscanf(fp,"%s", notes);//"--------------------"
	fscanf(fp,"%s", notes);//Soil_data
	fscanf(fp,"%s %d", notes, &IData.Soil_landuse);	
	fscanf(fp,"%s %d", notes, &IData.Soil_Texture);
	fscanf(fp,"%s %f", notes, &IData.Soil_Density);
	fscanf(fp,"%s %f", notes, &IData.Soil_pH);
	fscanf(fp,"%s %f", notes, &IData.Soil_Clay);
	fscanf(fp,"%s %f", notes, &IData.Soil_Porosity);
	fscanf(fp,"%s %f", notes, &IData.Soil_BypassFlow);
	fscanf(fp,"%s %f", notes, &IData.Fldcap);
	fscanf(fp,"%s %f", notes, &IData.Wiltpt);
	fscanf(fp,"%s %f", notes, &IData.Sks);	
	fscanf(fp,"%s %f", notes, &IData.Soil_OCatSurface);
    fscanf(fp,"%s %f", notes, &IData.Soil_Litter);	
    fscanf(fp,"%s %f", notes, &IData.Soil_humads);
	fscanf(fp,"%s %f", notes, &IData.Soil_humus);
	fscanf(fp,"%s %f", notes, &IData.DClitter);
	fscanf(fp,"%s %f", notes, &IData.DChumads);
	fscanf(fp,"%s %f", notes, &IData.DChumus);
	fscanf(fp,"%s %f", notes, &IData.HumadCN);
	fscanf(fp,"%s %f", notes, &IData.HumusCN);
	fscanf(fp,"%s %f", notes, &IData.PassiveC);
	fscanf(fp,"%s %f", notes, &IData.PassiveCCN);
	fscanf(fp,"%s %f", notes, &IData.SOCa);
	fscanf(fp,"%s %f", notes, &IData.SOCb);
	fscanf(fp,"%s %f", notes, &IData.Soil_NO3);	
	fscanf(fp,"%s %f", notes, &IData.Soil_NH4);	
	fscanf(fp,"%s %f", notes, &IData.Soil_MicrobioIndex);
	fscanf(fp,"%s %f", notes, &IData.slope);
	fscanf(fp,"%s %f", notes, &IData.LateralInflux);
	fscanf(fp,"%s %f", notes, &IData.HighestWT);
	fscanf(fp,"%s %f", notes, &IData.Soil_WaterObstructLayer);
	fscanf(fp,"%s %f", notes, &IData.Soil_Quality);
	fscanf(fp,"%s %d", notes, &IData.SCSuse);

	if(IData.SCSuse==1)
	{
		float m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage;
		
		fscanf(fp,"%s %f", notes, &m_CN);
		fscanf(fp,"%s %f", notes, &m_RoughLand);
		fscanf(fp,"%s %f", notes, &m_RoughChannel);
		fscanf(fp,"%s %f", notes, &m_ChannelSlope);
		fscanf(fp,"%s %f", notes, &m_ChannelLength);
		fscanf(fp,"%s %f", notes,&m_LandManage);
				
		char scs[120];
		FILE *scspara;
		sprintf(scs,"%s\\Inputs\\scspara", OUTPUT);
		scspara = fopen(scs, "w");
		if(scspara==NULL) note(1, scs);
		fprintf(scspara, "%f %f %f %f %f %f\n", m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage);	
		fclose(scspara);		
	}

    fscanf(fp,"%s %f", notes, &IData.WaterPoolBD);//added waterpool
	fscanf(fp,"%s", notes);
	
	if(strcmp(notes, "__Soil_Profile_Type")==0)
			{
			fscanf(fp,"%d", &IData.ProfileType);//added ProfileType
			if(IData.ProfileType==1)
			{
			fscanf(fp,"%s",notes);//scan the ProfileFileName
			fgets(tmp,230,fp);//copied the code for the climate Name reading don't fully understand.
			EraseFBSpace(tmp);
			IData.ProfileFileName=tmp;//set the file name to IData.ProfileFileName

			}
			fscanf(fp,"%s",notes);
			//fscanf(fp,"%s %s", notes, &IData.ProfileFileName);
			}
	else
	{
	IData.ProfileType=0;
	//fscanf(fp,"%s",notes);
	}

	fscanf(fp, "%s %d", notes, &IData.CheckHomo1);//Homogeneous Slow Water Flow

	for(x=1; x<=4; x++) fscanf(fp,"%s %d", notes, &jd);//5 lines of junk at end of soil section. Now 4 with Homogeneous slowed water flow.

	IData.Soil_moiture = 0.5;
	if(IData.Sks<0.015) IData.Sks = 0.015;//sks default 0.015
	if(IData.HighestWT>1.0) IData.HighestWT = 1.0;



 
    // Read crop parameter
    int ri, temp, yc, db_CycleYear[20], FCTT=0;
	int db_Rotation_Number, FarmCropNumber;
	CString FCT60, CropDB;
	FILE *cropdb;

#ifdef MANURE

for(int FW=1; FW<=TotalFarmFields; FW++)
{

#endif

	FCTT++;
	FCT60.Format("%s_%d", INTERMANAGE, FCTT);
	_mkdir(FCT60);
	
	fscanf(fp,"%s", notes);//---------------------------
	fscanf(fp,"%s", notes);//Crop_data
	
	fscanf(fp,"%s %d", notes, &db_Rotation_Number);//Cropping_systems

	CString DB;
	FILE *db;
		
	DB.Format("%s\\CropRotation.txt", FCT60);//###
	db=fopen(DB, "w");
	fprintf(db, "%d\n", db_Rotation_Number);
	fclose(db);
	
	for(i=1;i<=db_Rotation_Number;i++)
	{
		int db_TotalYear;
		int tilln, TillMonth, TillDay, TillMethod;
		int manun, ManuMonth, ManuDay, ManuType, ManuMethod, ManureAppHour;
		float ManuAmount, ManuCN, ManuN, ManureDepth, ManureNH4, ManureNO3,ManureDM, ManurePH,ManPoolFrac,ManPoolRate;
		int UseManPool, AutoManure;
		int skipLine = 0;
		fscanf(fp,"%s %d", notes, &ri);// Cropping_system
		fscanf(fp,"%s %d", notes, &db_TotalYear);//Total_years
		fscanf(fp,"%s %d", notes, &db_CycleYear[i]);//Years_of_a_cycle
				
		DB.Format("%s\\CropRotation_%d.txt", FCT60, i);//write: ReadInputDatafromDND, OK
		db=fopen(DB, "w");
		fprintf(db, "%d\n", i);
		fprintf(db, "%d\n", db_TotalYear);			
		fprintf(db, "%d\n", db_CycleYear[i]);
		fclose(db);	

		for(j=1; j<=db_CycleYear[i]; j++)
		{
			char WT_file[200];

			CropDB.Format("%s\\CropRotation_%d_%d.txt", FCT60, i, j);
			cropdb=fopen(CropDB, "w");
			if(cropdb==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", CropDB);
				AfxMessageBox(notes);
				exit(0);
			}

			fscanf(fp,"%s %d", notes, &yr);
			fscanf(fp,"%s %d", notes, &cropn);//Crops
					
			fprintf(cropdb, "%d\n", cropn);
		
			int db_Type, db_Pmonth, db_Pday, db_Hmonth , db_Hday, db_Hyear, db_CoverCrop, db_PerennialCrop;
			int db_Transplant, db_crop_order;
			float db_Yield, db_Residue;
			float db_GrowthReproductive, db_PsnEfficiency, db_PsnMax, db_TreeAge=0.0;
			float db_TreeCurrentAge=0.0, db_TreeLeafMax=0.0, db_TreeLeafMin=0.0;
			float db_GrainFraction, db_LeafFraction, db_ShootFraction, db_RootFraction;
			float db_GrainCN, db_LeafCN, db_ShootCN, db_RootCN;
			float db_TDD, db_Water, db_OptT, db_Nfix, db_Vascularity;
			float db_GrainFill;
			int	db_RootShape;
			float db_LAImax;
			float db_FrostKill;
			float db_AlfCHRMX;
			float db_ALFCDRMX;
			float db_ALFCTMX;
			float db_ALFPDFMX;
			float db_Root1, db_Root2;
			float db_AGResp1, db_AGResp2;
			float db_cropGRate, db_cropTime, db_RUEHI, db_DelayP;
			int noRootParm = 0;
			//init error
			db_GrowthReproductive = 0.0;
			db_Transplant = 0.0;
			db_PsnEfficiency = 0.0; 
			db_PsnMax = 0.0;

			for(k=1; k<=cropn; k++) 
			{
				if (skipLine == 0)
				{
					fscanf(fp, "%s %d", notes, &db_crop_order);
				}
				else {
					db_crop_order = float(k);
					skipLine = 0;//so that it reads the old dnd files right
				}
				fscanf(fp,"%s %d", notes, &db_Type);
				fscanf(fp,"%s %d", notes, &db_Pmonth);
				fscanf(fp,"%s %d", notes, &db_Pday);
				fscanf(fp,"%s %d", notes, &db_Hmonth);
				fscanf(fp,"%s %d", notes, &db_Hday);
				fscanf(fp,"%s %d", notes, &db_Hyear);
				fscanf(fp,"%s %f", notes, &db_Residue);
				fscanf(fp,"%s %f", notes, &db_Yield);
				fscanf(fp,"%s %f", notes, &db_LeafFraction);
				fscanf(fp,"%s %f", notes, &db_ShootFraction);
				fscanf(fp,"%s %f", notes, &db_RootFraction);
				fscanf(fp,"%s %f", notes, &db_GrainFraction);
				fscanf(fp,"%s %f", notes, &db_LeafCN);					
				fscanf(fp,"%s %f", notes, &db_ShootCN);
				fscanf(fp,"%s %f", notes, &db_RootCN);
				fscanf(fp,"%s %f", notes, &db_GrainCN);
				fscanf(fp,"%s %f", notes, &db_TDD);
				fscanf(fp,"%s %f", notes, &db_OptT);
				fscanf(fp,"%s %f", notes, &db_Water);
				fscanf(fp,"%s %f", notes, &db_Nfix);
				fscanf(fp,"%s %f", notes, &db_Vascularity);
				fscanf(fp,"%s %d", notes, &db_CoverCrop);
				fscanf(fp,"%s %d", notes, &db_PerennialCrop);
				fscanf(fp,"%s %d", notes, &db_Transplant);
				fscanf(fp,"%s %f", notes, &db_TreeAge);
				fscanf(fp,"%s %f", notes, &db_TreeCurrentAge);
				fscanf(fp,"%s %f", notes, &db_TreeLeafMax);
				fscanf(fp,"%s %f", notes, &db_TreeLeafMin);
				fscanf(fp,"%s %d", notes, &db_RootShape);
				fscanf(fp,"%s %f", notes, &db_GrainFill);
				if(db_RootShape==0)db_RootShape=5;
				if(db_GrainFill==0.0)db_GrainFill=0.6;
				fscanf(fp, "%s %f", notes, &db_LAImax);
				fscanf(fp, "%s %f", notes, &db_FrostKill);
				fscanf(fp, "%s %f", notes, &db_AlfCHRMX);
				fscanf(fp, "%s %f", notes, &db_ALFCDRMX);
				fscanf(fp, "%s %f", notes, &db_ALFCTMX);
				fscanf(fp, "%s %f", notes, &db_ALFPDFMX);
				/*
				//test to see if new Root parameters are added to dnd file?
				fscanf(fp, "%s", &tmp);
				std::string temp2 = "----------------------------------------";
				if (tmp == temp2)//means its not encountered the Root Parameter yet
				{
					db_Root1 = 0.4;
					db_Root2 = 0.007;
					noRootParm = 1;
					db_AGResp1 = 0.4;
					db_AGResp2 = 0.007;
				}
				else
				{
				*/
				//fscanf(fp, "%f", &db_Root1);
					fscanf(fp, "%s %f", notes, &db_Root1);
					fscanf(fp, "%s %f", notes, &db_Root2);
					fscanf(fp, "%s %f", notes, &db_AGResp1);
					fscanf(fp, "%s %f", notes, &db_AGResp2);
					fscanf(fp, "%s %f", notes, &db_cropGRate);
					if ( strcmp(notes, "______Crop#") == 0)
					{
						float blah;
						blah = 1.0;

						db_cropGRate = 10.0;
						db_cropTime = 0.35;
						db_RUEHI = 1.0;
						db_DelayP = 1.0;
						skipLine = 1;

					}
					
else if (strcmp(notes, "----------------------------------------") == 0)//coding for adopting old dnds to new ones
{
	db_cropGRate = 10.0;
	db_cropTime = 0.35;
	db_RUEHI = 1.0;
	db_DelayP = 1.0;
	skipLine = 1;
}
else {

	fscanf(fp, "%s %f", notes, &db_cropTime);
	fscanf(fp, "%s %f", notes, &db_RUEHI);
	fscanf(fp, "%s %f", notes, &db_DelayP);
}
				//	db_AGResp1 = 0.7;
				//	db_AGResp2 = 0.0017;
					 
				//}
				

/*//Joji batch run
if(db_Type==15)//trun rye to cover crop
{
	db_Type = 47;
	db_Nfix = 4.0;
	db_TDD = 1800.0;
	db_Yield = 100.0;
	db_GrainFraction = 0.01;
	db_LeafFraction = 0.4;
	db_ShootFraction = 0.4;
	db_RootFraction = 0.19;
	db_LeafCN = 20.0;
	db_ShootCN = 20.0;
	db_RootCN = 25.0;
	db_Water = 100.0;
}

if(db_Type==53)//change parameters of broccoli
{
	//db_Type = 47;
	//db_Nfix = 4.0;
	db_TDD = 1200.0;
	db_Yield = 900.0;
	db_GrainFraction = 0.4;
	db_LeafFraction = 0.2;
	db_ShootFraction = 0.3;
	db_RootFraction = 0.1;
	db_GrainCN = 10.0;
	db_LeafCN = 30.0;
	db_ShootCN = 30.0;
	db_RootCN = 30.0;
	db_Water = 150.0;
}*/

				//writes out three notes
				//for(x=1; x<=2; x++) fscanf(fp,"%s %d", notes, &jd);
				//for(x=1; x<=3; x++) fscanf(fp,"%s %d", notes, &jd);//normally x<=5 until i added additional 2 lines //adjusted down for LAIMAX and FrostKill


				// writing out to cropdb the crop parameters
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
				fprintf(cropdb, "%f %f\n", db_LAImax, db_FrostKill);
				fprintf(cropdb, "%f %f %f %f\n", db_AlfCHRMX, db_ALFCDRMX,db_ALFCTMX,db_ALFPDFMX);
				fprintf(cropdb, "%f %f\n", db_Root1, db_Root2);
				fprintf(cropdb, "%f %f\n", db_AGResp1, db_AGResp2);
				fprintf(cropdb, "%f %f %f %f\n", db_cropGRate, db_cropTime,db_RUEHI,db_DelayP);
				
			}
			
			fclose(cropdb);
			
			//Tillage
			DB.Format("%s\\CropTill_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}			

			if (noRootParm == 0 && skipLine==0)//testing to see if this line was already scanned above.
			{
				fscanf(fp, "%s", &tmp);//---------------------
			}
			skipLine = 0;
			fscanf(fp,"%s %d", notes, &tilln);
			
			fprintf(db, "%d\n", tilln);

			for(k=1; k<=tilln; k++) 
			{
				fscanf(fp,"%s %d", notes, &temp);
				fscanf(fp,"%s %d", notes, &TillMonth);
				fscanf(fp,"%s %d", notes, &TillDay);
				fscanf(fp,"%s %d", notes, &TillMethod);				

				fprintf(db, "%d  %d  %d\n", TillMonth, TillDay, TillMethod);	
			}
			fclose(db);

			//Fertilization
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

			fscanf(fp,"%s", notes);//---------------------
			fscanf(fp,"%s %d", notes, &FertOption);
			
			fprintf(db, "%d\n", FertOption);

			if(FertOption==-1)//Fertigation
			{
				char Fertigation[200];
				
				fscanf(fp,"%s %s", notes, Fertigation);
				fprintf(db, "%s\n", Fertigation);

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "______Slow_release_rate")!=0)
				{
					DayRelease = 0.0;
					NIefficiency = 0.0;
					NIduration = 0.0;
					UreaseEfficiency = 0.0;
					UreaseDuration = 0.0;
					note_flag = 1;
				}
				else
				{
					fscanf(fp,"%f", &DayRelease);
					fscanf(fp,"%s %f", notes, &NIefficiency);
					fscanf(fp,"%s %f", notes, &NIduration);
					fscanf(fp,"%s %f", notes, &UreaseEfficiency);
					fscanf(fp,"%s %f", notes, &UreaseDuration);
				}

				fprintf(db, "%f %f %f %f %f\n", DayRelease, NIefficiency, NIduration, 
						UreaseEfficiency, UreaseDuration);

			}
			else if(FertOption==-2) //Auto-fertilization
			{
				for (k = 1; k <= 2; k++)
				{
					fscanf(fp, "%s %d", notes, &temp);
					fscanf(fp, "%s %d", notes, &FertMonth);
					fscanf(fp, "%s %d", notes, &FertDay);
					fscanf(fp, "%s %d", notes, &FertMethod);
					fscanf(fp, "%s %f", notes, &FertDepth);
					fscanf(fp, "%s %f", notes, &FertNitrate);
					fscanf(fp, "%s %f", notes, &FertAbi);
					fscanf(fp, "%s %f", notes, &FertUrea);
					fscanf(fp, "%s %f", notes, &FertAnh);
					fscanf(fp, "%s %f", notes, &FertNH4NO3);
					fscanf(fp, "%s %f", notes, &FertNH42SO4);
					fscanf(fp, "%s %f", notes, &FertNH42HPO4);

					fprintf(db, "%d %d %d\n", FertMonth, FertDay, FertMethod);
					fprintf(db, "%f %f %f %f %f %f %f %f\n", FertNitrate, FertAbi, FertUrea, FertAnh, FertNH4NO3,
						FertNH42SO4, FertNH42HPO4, FertDepth);

					fscanf(fp, "%s %f", notes, &DayRelease);
					fscanf(fp, "%s %f", notes, &NIefficiency);
					fscanf(fp, "%s %f", notes, &NIduration);
					fscanf(fp, "%s %f", notes, &UreaseEfficiency);
					fscanf(fp, "%s %f", notes, &UreaseDuration);

					for (x = 1; x <= 5; x++) fscanf(fp, "%s %d", notes, &jd);//5 nones

					fprintf(db, "%f %f %f %f %f\n", DayRelease, NIefficiency, NIduration,
						UreaseEfficiency, UreaseDuration);
				}



				/*

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "______Slow_release_rate")!=0)
				{
					DayRelease = 0.0;
					NIefficiency = 0.0;
					NIduration = 0.0;
					UreaseEfficiency = 0.0;
					UreaseDuration = 0.0;
					note_flag = 1;
				}
				else
				{
					fscanf(fp,"%f", &DayRelease);
					fscanf(fp,"%s %f", notes, &NIefficiency);
					fscanf(fp,"%s %f", notes, &NIduration);
					fscanf(fp,"%s %f", notes, &UreaseEfficiency);
					fscanf(fp,"%s %f", notes, &UreaseDuration);
				}

				fprintf(db, "%f %f %f %f %f\n", DayRelease, NIefficiency, NIduration, 
						UreaseEfficiency, UreaseDuration);

				//Brian added following 2 lines for auto-fert 
					fscanf(fp,"%s %d", notes, &jd);
				fprintf(db, "%d\n", jd);
			}
			else if(FertOption==-3) //Precision fertilization
			{
				fscanf(fp,"%s", notes);
				if(strcmp(notes, "______Slow_release_rate")!=0)
				{
					DayRelease = 0.0;
					NIefficiency = 0.0;
					NIduration = 0.0;
					UreaseEfficiency = 0.0;
					UreaseDuration = 0.0;
					note_flag = 1;
				}
				else
				{
					fscanf(fp,"%f", &DayRelease);
					fscanf(fp,"%s %f", notes, &NIefficiency);
					fscanf(fp,"%s %f", notes, &NIduration);
					fscanf(fp,"%s %f", notes, &UreaseEfficiency);
					fscanf(fp,"%s %f", notes, &UreaseDuration);
				}

				fprintf(db, "%f %f %f %f %f\n", DayRelease, NIefficiency, NIduration, 
						UreaseEfficiency, UreaseDuration);
						*/
				//Brian added following 2 lines for auto-fert 
					fscanf(fp,"%s %d", notes, &jd);
				fprintf(db, "%d\n", jd);
				
			}
			else //Manual 
			{
				int jd=0;
				for(k=1; k<=FertOption; k++) 
				{
					fscanf(fp,"%s %d", notes, &temp);
					fscanf(fp,"%s %d", notes, &FertMonth);
					fscanf(fp,"%s %d", notes, &FertDay);
					fscanf(fp,"%s %d", notes, &FertMethod);
					fscanf(fp,"%s %f", notes, &FertDepth);
					fscanf(fp,"%s %f", notes, &FertNitrate);
					fscanf(fp,"%s %f", notes, &FertAbi);
					fscanf(fp,"%s %f", notes, &FertUrea);
					fscanf(fp,"%s %f", notes, &FertAnh);
					fscanf(fp,"%s %f", notes, &FertNH4NO3);
					fscanf(fp,"%s %f", notes, &FertNH42SO4);
					fscanf(fp,"%s %f", notes, &FertNH42HPO4);
				
					fprintf(db, "%d %d %d\n", FertMonth, FertDay, FertMethod);
					fprintf(db, "%f %f %f %f %f %f %f %f\n", FertNitrate, FertAbi, FertUrea, FertAnh, FertNH4NO3, 
					FertNH42SO4, FertNH42HPO4, FertDepth);
					
					fscanf(fp,"%s %f", notes, &DayRelease);
					fscanf(fp,"%s %f", notes, &NIefficiency);
					fscanf(fp,"%s %f", notes, &NIduration);
					fscanf(fp,"%s %f", notes, &UreaseEfficiency);
					fscanf(fp,"%s %f", notes, &UreaseDuration);
					
					for(x=1; x<=5; x++) fscanf(fp,"%s %d", notes, &jd);

					fprintf(db, "%f %f %f %f %f\n", DayRelease, NIefficiency, NIduration, 
						UreaseEfficiency, UreaseDuration);
				}
				fscanf(fp,"%s %d", notes, &jd);
				fprintf(db, "%d\n", jd);
			}
			
			fclose(db);

			//Manure
			DB.Format("%s\\CropManu_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}			

			if(note_flag==1)
			{
				note_flag = 0;
			}
			else
			 fscanf(fp,"%s", notes);//---------------------
			
			fscanf(fp,"%s %d", notes, &manun);
									
			fprintf(db, "%d\n", manun);

			for(k=1; k<=manun; k++) 
			{
				fscanf(fp,"%s", notes);

				if(strcmp(notes, "______Manuring#")==0)
				{
					fscanf(fp,"%d", &temp);
					fscanf(fp,"%s %d", notes, &ManuMonth);
					fscanf(fp,"%s %d", notes, &ManuDay);
					fscanf(fp,"%s %f", notes, &ManuAmount);
					fscanf(fp,"%s %f", notes, &ManuCN);
					fscanf(fp,"%s %d", notes, &ManuType);
					fscanf(fp,"%s %d", notes, &ManuMethod);
					fscanf(fp,"%s", notes);
					if(strcmp(notes, "______None")==0)
					{
						fscanf(fp,"%f", &jf);
						fscanf(fp,"%s %f", notes, &jf);
						fscanf(fp,"%s %f", notes, &jf);
						fscanf(fp,"%s %f", notes, &jf);
						fscanf(fp,"%s %d", notes, &jd);

						if(ManuMethod==0)//broadcast
							ManureDepth = 0.0;
						else//incorporation or injection
							ManureDepth = 10.0;

						if(ManuType==4)//slurry manure
						{
							float dManuN = ManuAmount / ManuCN;
							ManureNH4 = 0.5 * dManuN;
							ManureNO3 = 0.0;
							ManuN = 0.5 * dManuN;
							ManuCN = ManuAmount / ManuN;
						}
						else
						{
							ManuN = ManuAmount / ManuCN;
							ManureNH4 = 0.0;
							ManureNO3 = 0.0;
						}
					}
					else
					{
					fscanf(fp,"%f", &ManureDepth);
					fscanf(fp,"%s %f", notes, &ManuN);
					fscanf(fp,"%s %f", notes, &ManureNH4);
					fscanf(fp,"%s %f", notes, &ManureNO3);
					fscanf(fp,"%s %d", notes, &ManureAppHour);
					fscanf(fp,"%s %f", notes, &ManureDM);
					fscanf(fp,"%s %f", notes, &ManurePH);
					fscanf(fp, "%s %d", notes, &UseManPool);
					fscanf(fp, "%s %f", notes, &ManPoolFrac);
					fscanf(fp, "%s %f", notes, &ManPoolRate);
					fscanf(fp, "%s %d", notes, &AutoManure);
					//fscanf(fp,"%s %d", notes, &jd);
					//UseManPool = 1;
					//ManPoolFrac = 1.0;
					//ManPoolRate = 0.078;
					}

					fprintf(db, "%d %d\n", ManuMonth, ManuDay);
					fprintf(db, "%f %f %d %d %f\n", ManuAmount, ManuCN, ManuType, ManuMethod, ManureDepth);
					fprintf(db, "%f %f %f %d %f %f %f %f %d %d\n", ManuN, ManureNH4, ManureNO3, ManureAppHour, ManureDM, ManurePH, ManPoolFrac, ManPoolRate, UseManPool , AutoManure ); //for manure file
					//fprintf(db, "%f %f %f %d %f %f %f %f %d\n", ManuN, ManureNH4, ManureNO3, ManureAppHour, ManureDM, ManurePH, ManPoolRate); //for manure file temp Agmip
					//fprintf(db, "%f %f %f %d %f %f\n", ManuN, ManureNH4, ManureNO3, ManureAppHour, ManureDM, ManurePH);
				}
				else
				{				
					//fprintf(db, "%d %d\n", 0, 0);
					//fprintf(db, "%f %f %d %d %f\n", 0,0, 0.0, 0, 0, 0.0);
					//fprintf(db, "%f %f %f\n", 0.0, 0.0, 0.0); 

					note_flag = 1;
				}
			}
			fclose(db);

			//Plastic film	
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
			
			if(note_flag==0)
				fscanf(fp,"%s", notes);//---------------------
			else
				note_flag = 0;

			fscanf(fp,"%s %d", notes, &weedn);

			fscanf(fp,"%s %d", notes, &WeedOption);
			fprintf(db, "%d %d\n", weedn, WeedOption);
		
			for(k=1; k<=weedn; k++) 
			{
				fscanf(fp,"%s %d", notes, &temp);
				fscanf(fp,"%s %d", notes, &WeedMonth1);
				fscanf(fp,"%s %d", notes, &WeedDay1);
				fscanf(fp,"%s %d", notes, &WeedMonth2);
				fscanf(fp,"%s %d", notes, &WeedDay2);
				fscanf(fp,"%s %f", notes, &CoverFraction);

				for(x=1; x<=5; x++) fscanf(fp,"%s %d", notes, &jd);

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

			fscanf(fp,"%s", notes);//---------------------
			fscanf(fp,"%s %d", notes, &floon);
			fscanf(fp,"%s %d", notes, &WaterControl);
			fscanf(fp,"%s %f", notes, &FloodWaterN);
			fscanf(fp,"%s %f", notes, &WaterLeakRate);
			fscanf(fp,"%s %f", notes, &WaterGetherIndex);
			fscanf(fp,"%s %s", notes, WT_file);
			fscanf(fp,"%s %f", notes, &m_IniWT);
			fscanf(fp,"%s %f", notes, &m_LWTceasingSurfFlow);
			fscanf(fp,"%s %f", notes, &m_LWTceasingGroungFlow);
			fscanf(fp,"%s %f", notes, &m_WatershedIndex);
			fscanf(fp,"%s %f", notes, &m_SurfOutflowIntensity);
			fscanf(fp, "%s %f", notes, &m_GroundOutflowIntensity); if (m_GroundOutflowIntensity < 0.0)m_GroundOutflowIntensity = 0.0;
				
			fprintf(db, "%d %f %d %f\n", floon, FloodWaterN, WaterControl, WaterLeakRate);

			for(k=1; k<=floon; k++) 
			{ 
				fscanf(fp,"%s %d", notes, &temp);
				fscanf(fp,"%s %d", notes, &FlooMonth1);
				fscanf(fp,"%s %d", notes, &FlooDay1);
				fscanf(fp,"%s %d", notes, &FlooMonth2);
				fscanf(fp,"%s %d", notes, &FlooDay2);
				fscanf(fp,"%s %f", notes, &FlooN);
				fscanf(fp,"%s %d", notes, &ShallowFlood);

				for(x=1; x<=5; x++) fscanf(fp,"%s %d", notes, &jd);
			
				fprintf(db, "%d %d\n", FlooMonth1, FlooDay1);
				fprintf(db, "%d %d\n", FlooMonth2, FlooDay2);
				fprintf(db, "%f\n", FlooN);
				fprintf(db, "%d\n", ShallowFlood);
			}
						
			fprintf(db, "%f\n", WaterGetherIndex);				
			fprintf(db, "%s\n", WT_file);
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

			int irrin, IrriMode, IrriMonth, IrriDay, IrriMethod,TileIrriDays;
			float IrriIndex, IrriAmount;

			fscanf(fp,"%s", notes);//---------------------
			fscanf(fp,"%s %d", notes, &irrin);
			fscanf(fp,"%s %d", notes, &IrriMode);
			fscanf(fp,"%s %f", notes, &IrriIndex);
			fscanf(fp,"%s %d", notes, &IrriMethod);
		
			fprintf(db, "%d %d %f %d\n", irrin, IrriMode, IrriIndex, IrriMethod);

			for(k=1; k<=irrin; k++) 
			{
				fscanf(fp,"%s %d", notes, &temp);
				fscanf(fp,"%s %d", notes, &IrriMonth);
				fscanf(fp,"%s %d", notes, &IrriDay);
				fscanf(fp,"%s %f", notes, &IrriAmount);
				fscanf(fp,"%s %d", notes, &IrriMethod);
				fscanf(fp,"%s %d", notes, &TileIrriDays);

				for(x=1; x<=4; x++) fscanf(fp,"%s %d", notes, &jd);//writes 5 lines of junk notes
				//writes out to CropIrri_1_1
				
				fprintf(db, "%d %d\n", IrriMonth, IrriDay);
				fprintf(db, "%f %d %d\n", IrriAmount, IrriMethod, TileIrriDays);
			}
			fclose(db);
//Controlled Drainage
			DB.Format("%s\\CTDrain_%d_%d.txt", FCT60, i, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}
			int drainn,drainID, drainMonth, drainDay, drainMonth2, drainDay2;
			float cdrainDepth;
			fscanf(fp,"%s", notes);//---------------------
			fscanf(fp,"%s %d", notes, &drainn);
			fprintf(db, "%d\n", drainn);
			for(k=1; k<=drainn; k++) 
			{
				fscanf(fp,"%s %d", notes, &drainID);
				fscanf(fp,"%s %d", notes, &drainMonth);
				fscanf(fp,"%s %d", notes, &drainDay);
				fscanf(fp,"%s %d", notes, &drainMonth2);
				fscanf(fp,"%s %d", notes, &drainDay2);
				fscanf(fp,"%s %f", notes, &cdrainDepth);

				
				//writes out to CTDrain_1_1
				


				
				fprintf(db, "%d %d\n", drainMonth, drainDay);
				fprintf(db, "%d %d %f\n", drainMonth2, drainDay2, cdrainDepth);
			}
			fclose(db);

			//Grazing
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
			float GrazHour, Dairy, Beef, Pig, Horse, Sheep, AddFeed, FeedCN,GrazBiomass, GrazCConsume, GrazCExcrete;
		
			fscanf(fp,"%s", notes);//---------------------
			fscanf(fp,"%s %d", notes, &grazn);
			
			fprintf(db, "%d\n", grazn);

			for (k=1;k<=grazn;k++) 
			{
				fscanf(fp,"%s %d", notes, &temp);
				fscanf(fp,"%s %d", notes, &GrazMonth1);
				fscanf(fp,"%s %d", notes, &GrazDay1);
				fscanf(fp,"%s %d", notes, &GrazMonth2);
				fscanf(fp,"%s %d", notes, &GrazDay2);
				fscanf(fp,"%s %f", notes, &Dairy);
				fscanf(fp,"%s %f", notes, &Beef);
				fscanf(fp,"%s %f", notes, &Pig);
				fscanf(fp,"%s %f", notes, &Sheep);
				fscanf(fp,"%s %f", notes, &Horse);
				fscanf(fp,"%s %f", notes, &GrazHour);
				fscanf(fp,"%s %f", notes, &AddFeed);
				fscanf(fp,"%s %f", notes, &FeedCN);
				fscanf(fp,"%s %d", notes, &Excreta);
				fscanf(fp, "%s %f", notes, &GrazBiomass);
				fscanf(fp, "%s %f", notes, &GrazCConsume);
				fscanf(fp, "%s %f", notes, &GrazCExcrete);

				for(x=1; x<=2; x++) fscanf(fp,"%s %d", notes, &jd);
				
				fprintf(db, "%d %d\n", GrazMonth1, GrazDay1);
				fprintf(db, "%d %d\n", GrazMonth2, GrazDay2);
				fprintf(db, "%f\n", GrazHour);
				fprintf(db, "%f %f %f %f %f %f %f %d %f %f %f\n", Dairy, Beef, Pig, Sheep, Horse, AddFeed, FeedCN, Excreta,GrazBiomass,GrazCConsume, GrazCExcrete );
			}
			fclose(db);	
			
			//Grass cutting
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
		
			fscanf(fp,"%s", notes);//---------------------
			fscanf(fp,"%s %d", notes, &cutn);

			fprintf(db, "%d\n", cutn);

			for(k=1; k<=cutn; k++) 
			{
				fscanf(fp,"%s %d", notes, &temp);
				fscanf(fp,"%s %d", notes, &CutMonth);
				fscanf(fp,"%s %d", notes, &CutDay);
				fscanf(fp,"%s %f", notes, &CutAmount);
				fscanf(fp,"%s %d", notes, &CutPart);
				
				for(x=1; x<=5; x++) fscanf(fp,"%s %d", notes, &jd);

				fprintf(db, "%d %d\n", CutMonth, CutDay);
				fprintf(db, "%f %d\n", CutAmount, CutPart);			
			}

			//fprintf(db, "%d\n", 0);//Joji batch run





			fclose(db);	
		}
	}	


#ifdef MANURE

}//end of FarmCrops loop

#endif

//tail end for extra parameters.
		fscanf(fp,"%s", notes);
		fscanf(fp,"%s", notes);
		fscanf(fp,"%s %f", notes, &IData.DrainDepth);
		fscanf(fp,"%s %f", notes, &IData.DrainSpace);
		fscanf(fp,"%s %f", notes, &IData.DrainRad);
		fscanf(fp,"%s %f", notes, &IData.DrainBed);
		fscanf(fp,"%s %f", notes, &IData.keDrain);
		fscanf(fp,"%s %f", notes, &IData.MaxNMove);
		fscanf(fp,"%s %f", notes, &IData.MobileNF);
		fscanf(fp,"%s %f", notes, &IData.NLayerF);
		fscanf(fp,"%s %f", notes, &IData.NMoveRate);
		fscanf(fp,"%s %f", notes, &IData.SoilEvapF);
		fscanf(fp,"%s %f", notes, &IData.RunOffWF);
		fscanf(fp,"%s %f", notes, &IData.RunOffNF);
		fscanf(fp,"%s %f", notes, &IData.Factor1);
		fscanf(fp,"%s %f", notes, &IData.Factor2);
		fscanf(fp,"%s %f", notes, &IData.Factor3);
		fscanf(fp,"%s %f", notes, &IData.DenitGRate);
		fscanf(fp,"%s %f", notes, &IData.NitGRate);
		fscanf(fp,"%s %f", notes, &IData.N2ORain);
		fscanf(fp,"%s %f", notes, &IData.SprMeltF);
		fscanf(fp,"%s %f", notes, &IData.Factor4);
		fscanf(fp,"%s %f", notes, &IData.Factor5);
		fscanf(fp,"%s %f", notes, &IData.Factor6);
		fscanf(fp,"%s %d", notes, &IData.Factor7);
		fscanf(fp,"%s %f", notes, &IData.Factor8);
		fscanf(fp,"%s %f", notes, &IData.Factor9);
		fscanf(fp,"%s %d", notes, &IData.SpinUpCheck);
        fscanf(fp,"%s %d", notes, &IData.SpinUpYears);
//		fscanf(fp,"%s %s", notes, &IData.SpinUpFileName);

			if(IData.SpinUpCheck==1)
			{
			fscanf(fp,"%s",notes);//scan the ProfileFileName
			fgets(tmp,230,fp);//copied the code for the climate Name reading don't fully understand.
			EraseFBSpace(tmp);
			IData.SpinUpFileName=tmp;//set the file name to IData.ProfileFileName

			}
			else
			{	fscanf(fp,"%s", notes);}//fscanf(fp,"%s %s", notes,&jd)
	////////////////////////////////////////////////////////////////////////////////
	
	fscanf(fp,"%s %f", notes, &IData.Factor10);
	fscanf(fp,"%s %f", notes, &IData.Factor11);
	fscanf(fp,"%s %f", notes, &IData.Factor13);
	fscanf(fp,"%s %f", notes, &IData.UreaHydro);
    fscanf(fp,"%s %f", notes, &IData.UreaHydro2);
	fscanf(fp,"%s %f", notes, &IData.NH3SoilDF);
	fscanf(fp,"%s %f", notes, &IData.UreaDifF);
	fscanf(fp, "%s %f", notes, &IData.N2N2OF);
	fscanf(fp, "%s %d", notes, &IData.SpinUpCheck2);//planting reset
	fscanf(fp, "%s %d", notes, &IData.OBSYield);
	if (IData.OBSYield == 1)
	{
		fscanf(fp, "%s", notes);//scan the ProfileFileName
		fgets(tmp, 230, fp);//copied the code for the climate Name reading don't fully understand.
		EraseFBSpace(tmp);
		IData.OBSYieldFileName = tmp;//set the file name to IData.ProfileFileName

	}
	else
	{
		fscanf(fp, "%s", notes);
	}//fscanf(fp,"%s %s", notes,&jd)
	IData.DynLayerCheck = 0;
	IData.DynLayerEdit = 0.0;
	fscanf(fp, "%s %d", notes, &IData.AutoPlant);
	fscanf(fp, "%s %d", notes, &IData.PrefFlowCheck);
	fscanf(fp, "%s %f", notes, &IData.PrefFlowDepth);
	fscanf(fp, "%s %f", notes, &IData.PrefFlowRecov);
	fscanf(fp, "%s %d", notes, &IData.DynLayerCheck);
	fscanf(fp, "%s %f", notes, &IData.DynLayerEdit);
	fclose(fp);
	if (IData.DynLayerCheck == 1||IData.DynLayerCheck==0 && IData.DynLayerEdit==0.0)
	{
	
		IData.DynLayerEdit = 0.0;
	}

}