#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "RunPaths.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include "CreateInputFile.h"
#include <io.h>
#include <direct.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#ifdef BASE
extern Site_BaseInformation	IData;
#endif

void NewCreateDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, float latitude,
							int IfCheck, float NO3NH4_Rainfall,float NH3_Atmosphere,float BaseCO2,
							float CO2IncreaseRate, char *LocaName, int YieldYear, int YieldToday,
							int DMW, char *r_Country);//Brian IfCheck converted from CString to int
void Toendd(char *notes, char *FN);
int NewSaveInterFarmParas(void);
int NewSaveCropParas(void);
//void NewRecordManureFiles(int years);

float nnSoca[6]={0.0f,0.2f,0.2f,0.08f,0.05f,0.2f};
float nnSocb[6]={10.0f,2.0f,2.0f,1.4f,4.0f,2.0f};
int MonthDay[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
float Soil_T;

NewCropofEachYear CYr[2];

void CreateDndcInputFiles(char *InputFileName)
{
	int jjd;//CropModel;
	CString SF, MP;
	FILE* sf, *mp;

	CString DB;
	FILE *db;
	char DCB[200];
	for(int kx10=1; kx10<=10; kx10++)
	{
		sprintf(DCB, "%s_1\\CropRotation_%d.txt", INTERMANAGE, kx10);//write: Initial files
		db=fopen(DCB, "w");
		if(db==NULL) note(1,DCB);
		fprintf(db, "%d %d %d", kx10, 1, 1);
		fclose(db);
	}

	DB.Format("%s\\Inter\\OpenFile.txt", OUTPUT);
	db=fopen(DB, "w");
	fprintf(db, "%d", 1);
	fclose(db);

	
#ifdef MANURE
	//Create blank manure files////////////////////////////////////////////////////
	for(int m_FeedlotYear=0; m_FeedlotYear<=10; m_FeedlotYear++)//seems to be capped at 10 years???
	{
		for(int iy3=0; iy3<=10; iy3++)
		{
			SF.Format("%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, iy3);
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
			fprintf(sf, "%d %f\n", -1, 0.0);

			fclose(sf);
		}

		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Inter\\TotalFeedLots_%d", OUTPUT, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", 1);
		fclose(TFL);
	}

	SF.Format("%s\\Inter\\ManureGraze.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	fprintf(sf, "%d  %d  %d  %f\n", 0, 8, 0, 0.0);  	
	fclose(sf);





#ifdef CONSOLE
	SF.Format("%s\\Inter\\ManureLagoon.txt", OUTPUT);
#else
	SF.Format("%s\\Result\\Inter\\ManureLagoon.txt", ROOTDIR);//would need to do similar to ManureHouse%d
#endif

	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %f  %d  %d  %d\n", 0.0, 0.0, 0, 0, 0);  
	fprintf(sf, "%d %d %f  %f  %f\n", 0, 0, 0.0, 0.0, 0.0); 
	fprintf(sf, "%d %f\n", 0, 0.0); 
	fclose(sf);

	SF.Format("%s\\Inter\\ManureCompost.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %d  %d  %f  %f\n", 0.0, 0, 0, 0.0, 0.0);  
	fclose(sf);

	SF.Format("%s\\Inter\\ManureDigester.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d  %f  %f\n", 0, 0.0, 0.0);    
	fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);

	SF.Format("%s\\Inter\\ManureField.txt", OUTPUT);
	sf=fopen(SF, "w");

	if(sf==NULL) note(1, SF);
	fprintf(sf, "%f", 0.0);    
	fclose(sf);

	CString XFF;
	FILE *xff;

	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", 0, 0, 0);
	fclose(xff);
#endif

	/////////////////////////////////////////////////////////////////////////////////////////////

	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Read in input file data
	int  j, cropn, MissFlag=0, years, ifdaily;
	int floon, ShallowFlood, WaterControl, FlooMonth1, FlooDay1, FlooMonth2, FlooDay2;
	float FlooN, WaterGetherIndex, WaterLeakRate, latitude, FloodWaterN;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex,m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	char notes[255],tmp[255],ffname[300],sitename[200];
    FILE *fp;
	CString txt;

	char fname[300];
	sprintf(fname, "%s", InputFileName);

	sprintf(ffname, "%s", fname);

	fp=fopen(ffname,"r");
	if(fp==NULL) note(0, ffname);
	
	///////////////////////////////////////////////////////////////////////////////////////
	//Site_BaseInformation();
	strcpy(sitename,"");
	//strcpy(Regionname,"");
	latitude =0;
	float longitude=120.0;
    int totalday =0;
    years    =0;
    ifdaily  =0;
	
	//ClimateFilename.clear();

	int Line=1;
	
	fscanf(fp,"%s",notes);
	if(strcmp(notes, "Input_Parameters:")!=0) Toendd("Input_Parameters:", fname); 
	
	fscanf(fp,"%s",notes);//"--------------------"
	fscanf(fp,"%s",notes);
	
	fscanf(fp,"%s",notes);
	if(strcmp(notes, "Site_name:")!=0) 
	{
		sprintf( sitename, "%s", notes);
	}
	else
		fscanf(fp,"%s", sitename);
	 
	
	fscanf(fp,"%s %d",notes,&years);
	if(strcmp(notes, "Simulated_Year:")!=0) Toendd("Simulated_Year:", fname);
	

    fscanf(fp,"%s %f", notes,& latitude);// "  "
	if(strcmp(notes, "Latitude:")!=0) Toendd("Latitude:", fname);
	
    
	fscanf(fp,"%s %d", notes,& ifdaily);	//"  "
	if(strcmp(notes, "Daily_Record:")!=0) Toendd("Daily_Record:", fname);


#ifdef MANURE
	//this section doesn't handle the new housing inputs.
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
	float m_LagoonCapacity, m_LagoonSurfaceArea, LagoonToField[30], LagoonToMarket[30], LagoonRemain[30], LagoonManureAplDepth[30];
	int m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes, LagoonDrainMonth[30], LagoonDrainDay[30], LagoonManureAplMethod[30];
	float m_CompostDensity, m_LitterAmount, m_LitterCN, CompostToField, CompostToMarket, CompostRemain;
	float m_DigesterCapacity,m_DigesterCH4,m_DigesterDays, DigesterToField;
	int m_Temp, m_Flash, HouseID, m_CompostCover, m_CompostRemoveTimes, CompostRemoveMonth, CompostRemoveDay;
	float DigesterToMarket, DigesterRemain, m_FlushWater, LiquidFraction;
	float HouseManureOutDays,m_UC, m_UL, m_UD, m_UF, m_UR, m_FC, m_FL, m_FD, m_FF, m_FR;
	float PenManureOutDays, PenUC, PenUL,PenUD,PenUR,PenFC, PenFL,PenFD,PenFR;
	float GrazeManureOutDays, GrazeUF, GrazeUR, GrazeFF, GrazeFR, FieldArea, jf;
	int NutritionModel;

	//CString MP;
	//FILE *mp;
	//CString SF;
	//FILE* sf;

	int m_FeedLots, m_FeedlotYears,m_FeedlotYear;

	fscanf(fp,"%s", notes);
	fscanf(fp,"%s", notes);
	fscanf(fp,"%s %d",notes, &m_FeedlotYears);

	for(m_FeedlotYear=1; m_FeedlotYear<=m_FeedlotYears; m_FeedlotYear++)
	{

		fscanf(fp,"%s %d",notes, &m_FeedLots);

		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Inter\\TotalFeedLots_%d", OUTPUT, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", m_FeedLots);
		fclose(TFL);

		for(int iy4=1; iy4<=m_FeedLots; iy4++)
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
				if(HouseInputFormat==3)
					fscanf(fp,"%s %d",notes,&NutritionModel);
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
					SF.Format("%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, iy4);
					sf=fopen(SF, "w");
					fprintf(sf, "%d\n", HouseInputFormat);  
					if(HouseInputFormat==1||HouseInputFormat==2)								//use a input file name
						fprintf(sf, "%s\n", HouseInputFileName);
					if(HouseInputFormat==3)
						fprintf(sf, "%d\n", NutritionModel);
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
		}//end of m_FeedlotYear
	}//end of iy4 loop


	//read in lagoon information
	// Looks like "%s\\Result\\inter\\TotalFeedLots_%d contains lagoon information as well.

	//will need to scan for m_LagoonYears to read in specific lagoon management.

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

		for(int iy5=1; iy5<=m_LagoonDrainTimes; iy5++)
		{
			fscanf(fp,"%s %d",notes, &LagoonDrainMonth[iy5]);
			fscanf(fp,"%s %d",notes, &LagoonDrainDay[iy5]);
			fscanf(fp,"%s %f",notes, &LagoonToField[iy5]);
			fscanf(fp,"%s %f",notes, &LagoonToMarket[iy5]);
			fscanf(fp,"%s %f",notes, &LagoonRemain[iy5]);
			fscanf(fp,"%s %d",notes, &LagoonManureAplMethod[iy5]);
			fscanf(fp,"%s %f",notes, &LagoonManureAplDepth[iy5]);
		}
	}
	
	//write out lagoon information to ManureLagoon.txt will need to update for multiple years.

	//if(m_LagoonCapacity>0.0)
	{
		SF.Format("\%s\\Inter\\ManureLagoon.txt", OUTPUT);
		sf=fopen(SF, "w");
		fprintf(sf, "%f  %f  %d  %d  %d\n", m_LagoonCapacity, m_LagoonSurfaceArea, m_LagoonCover, m_LagoonRain, m_LagoonDrainTimes); 
		for(int iy6=1; iy6<=m_LagoonDrainTimes; iy6++)
		{
			fprintf(sf, "%d  %d  %f  %f  %f\n", LagoonDrainMonth[iy6], LagoonDrainDay[iy6], LagoonToField[iy6], LagoonToMarket[iy6], LagoonRemain[iy6]);
			fprintf(sf, "%d  %f\n", LagoonManureAplMethod[iy6], LagoonManureAplDepth[iy6]);
		}
		fclose(sf);
	}

	//Compost Section

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
		
		for(int iy7=1;iy7<=m_CompostRemoveTimes;iy7++)
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
	
	// Digester output
	
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
		if(sf==NULL) note(1, SF);
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
		if(mp==NULL) note(1, MP);
		fprintf(mp, "%f\n", FieldArea);
		fclose(mp);
	}

	
	//CString XFF;
	//FILE *xff;
	XFF.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);		
	xff=fopen(XFF, "w");
	if(mp==NULL) note(1, MP);

	int CropOrder, FarmCropType, TotalFields=0, TotalFarmYears=0;
	float FarmCropHa, ManuFraction;
	
	fscanf(fp,"%s %d",notes, &TotalFields);
	fprintf(xff, "%d %d\n", TotalFields, TotalFarmYears);
	
	for(int iy8=1;iy8<=TotalFields;iy8++)
	{
		fscanf(fp,"%s %d",notes, &CropOrder);
		fscanf(fp,"%s %d",notes, &FarmCropType);
		fscanf(fp,"%s %f",notes, &FarmCropHa);
		fscanf(fp,"%s %f",notes, &ManuFraction);

		fprintf(xff, "%d  %d  %f  %f\n", iy8, FarmCropType, FarmCropHa, ManuFraction);

		CString FCT0, FCT100;
		FCT100.Format("%s\\Inputs\\FarmCrop_%d", OUTPUT, iy8);
		_mkdir(FCT100);
	}
	fclose(xff);

	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", TotalFields, CropOrder, FarmCropType);//ManureCropOrder, &CropIDID
	fclose(xff);

/*	if(FieldArea>0.0)
	{
		MP.Format("%s\\ManureFieldAll.txt", INTER);
		mp=fopen(MP, "w");
		if(mp==NULL) note(1, MP);
		fprintf(mp, "%d %f\n", TotalFields, FieldArea);
		fclose(mp);
	}
*/
#endif


	int ClimateFileType, ClimateFileNumber, if1File;
	float NO3NH4_Rainfall, NH3_Atmosphere, BaseCO2, CO2IncreaseRate;
	char ClimateFilename[300][200];
		
    
		//climate data
	fscanf(fp,"%s",notes);//"--------------------"
	
	fscanf(fp,"%s",notes);//"Climate data:"
	
	fscanf(fp,"%s %d", notes,& ClimateFileType);
	if(strcmp(notes, "Climate_Data_Type:")!=0) Toendd("Climate_Data_Type:", fname);
	

	fscanf(fp,"%s %f", notes,& NO3NH4_Rainfall);	//"
	if(strcmp(notes, "NO3NH4_in_Rainfall")!=0) Toendd("NO3NH4_in_Rainfall", fname);
	

	fscanf(fp,"%s %f", notes,& NH3_Atmosphere);	//"
	//if(strcmp(notes, "NH3_of_Atmosphere")!=0) Toendd("NH3_of_Atmosphere:", fname);
	

	fscanf(fp,"%s %f", notes,& BaseCO2);		//"
	if(strcmp(notes, "BaseCO2_of_Atmosphere")!=0) Toendd("BaseCO2_of_Atmosphere:", fname);
	

	fscanf(fp,"%s %d", notes,& ClimateFileNumber);	
	if(strcmp(notes, "Climate_file_count=")!=0) Toendd("Climate_file_count:", fname);
	

	//k= ClimateFileType;
	//int nn= ClimateFileNumber;
	// MaxCycle =  years;
		//read climate file name
	//ClimateFilename.clear();
	for (int iy1=1;iy1<= ClimateFileNumber;iy1++) 
	{
		fscanf(fp,"%d %s",&j, ClimateFilename[iy1]);
		
		//fgets(ClimateFilename[iy1],230,fp);
		//EraseFBSpace(tmp);
		//ClimateFilename.insert(301,tmp);
	}

	fscanf(fp,"%s", notes);
	if(strcmp(notes, "Climate_file_mode")!=0) 
	{ 
		 if1File = 0;
		 CO2IncreaseRate = 0.0;
		MissFlag=1;
	}
	else
	{
		fscanf(fp,"%d", & if1File);
		fscanf(fp,"%s %f", notes,& CO2IncreaseRate);
		MissFlag=0;
	}

		// Read Soil parameter
	if(MissFlag==0) fscanf(fp,"%s",notes);//"--------------------"
	MissFlag=0;
	
	int Soil_Texture, Soil_landuse;
	float Soil_Density, Soil_pH, Soil_OCatSurface, Soil_Clay, Soil_BypassFlow, Soil_Litter;
	float Soil_humads, Soil_humus, Soil_NO3, Soil_NH4, PassiveCCN, Soil_moiture, LateralInflux;

	fscanf(fp,"%s",notes);//"Soil data:"
	
	fscanf(fp,"%s %d", notes,& Soil_Texture);// "  "
	if(strcmp(notes, "Soil_Texture")!=0) Toendd("Soil_Texture:", fname);
	

	fscanf(fp,"%s %d", notes,& Soil_landuse);// "  "
	if(strcmp(notes, "Landuse_Type")!=0) Toendd("Landuse_Type:", fname);
	

	fscanf(fp,"%s %f", notes,& Soil_Density);// "  Soil_"
	if(strcmp(notes, "Density")!=0) Toendd("Density:", fname);
	

	fscanf(fp,"%s %f", notes,& Soil_pH);	 // "  Soil_pH"
	if(strcmp(notes, "Soil_pH")!=0) Toendd("Soil_pH:", fname);
	

	//fscanf(fp,"%s %f", notes,& Flood_pH);	
	fscanf(fp,"%s %f", notes,& Soil_OCatSurface);// "  "
	if(strcmp(notes, "SOC_at_Surface")!=0) Toendd("SOC_at_Surface:", fname);
	

	fscanf(fp,"%s %f", notes,& Soil_Clay);	// "  Soil_Clay_Content"
	if(strcmp(notes, "Clay_fraction")!=0) Toendd("Clay_fraction:", fname);
	

	fscanf(fp,"%s %f", notes,& Soil_BypassFlow);	// "  "
	if(strcmp(notes, "BypassFlow")!=0) Toendd("BypassFlow:", fname);
	

    fscanf(fp,"%s %f", notes,& Soil_Litter);	// "  Litter"
	if(strcmp(notes, "Litter_SOC")!=0) Toendd("Litter_SOC:", fname);
	

    fscanf(fp,"%s %f", notes,& Soil_humads);	// "  "
	if(strcmp(notes, "Humads_SOC")!=0) Toendd("Humads_SOC:", fname);
	

	fscanf(fp,"%s %f", notes,& Soil_humus);	// "  humus"
	if(strcmp(notes, "Humus_SOC")!=0) Toendd("Humus_SOC:", fname);
	

	fscanf(fp,"%s %f", notes,& Soil_NO3);	// "  "
	if(strcmp(notes, "Soil_NO3(-)(mgN/kg)")!=0) Toendd("Soil_NO3(-)(mgN/kg):", fname);
	

	fscanf(fp,"%s %f", notes,& Soil_NH4);	// "  Soil_NH4"
	if(strcmp(notes, "Soil_NH4(+)(mgN/kg)")!=0) Toendd("Soil_NH4(-)(mgN/kg):", fname);
	

	fscanf(fp,"%s %f", notes,& PassiveCCN);// "  Soil_moisture"
	//if(strcmp(notes, "Soil_PassiveCN")!=0) Toendd("Soil_PassiveCN:", fname);
	 Soil_moiture = 0.5;
	 PassiveCCN = 500.0;	

	fscanf(fp,"%s %f", notes,& LateralInflux);	
	if(strcmp(notes, "Temperature")==0)  LateralInflux = 1.0;
	if( LateralInflux<1.0)  LateralInflux = 1.0;
	//if(strcmp(notes, "Temperature")!=0) Toendd("Temperature:", fname);	

	float Fldcap, Wiltpt, Sks, Soil_Porosity, SOCa, SOCb, DClitter, DChumads, DChumus;
	float HumadCN, HumusCN, PassiveC, Soil_MicrobioIndex, HighestWT, Soil_WaterObstructLayer;
	float slope, Soil_Quality;
	int UseION, SCSuse;

	fscanf(fp,"%s", notes);
	if(strcmp(notes, "Field_capacity")!=0) 
	{ 
		 Fldcap = 0.0;
		 Wiltpt = 0.0;
		 Sks = 0.0;
		 Soil_Porosity = 0.0;
		 SOCa = nnSoca[ Soil_landuse];
		 SOCb = nnSocb[ Soil_landuse];
		 DClitter = 1.0;
		 DChumads = 1.0;
		 DChumus = 1.0;
		 HumadCN = 10.0;
		 HumusCN = 10.0;
		 PassiveC = 0.0;
		 Soil_MicrobioIndex = 1.0;
		 HighestWT = 1.0;
		 Soil_WaterObstructLayer = 2.50;
		 slope = 0.0;
		 UseION = 0;
		 SCSuse = 0;
		 Soil_Quality = 0.0;
		
		MissFlag=1;
	}
	else
	{
		fscanf(fp,"%f", & Fldcap);
		fscanf(fp,"%s %f", notes,& Wiltpt);
		fscanf(fp,"%s %f", notes,& Sks);//m/hr
		fscanf(fp,"%s %f", notes,& Soil_Porosity);
		fscanf(fp,"%s %f", notes,& SOCa);
		fscanf(fp,"%s %f", notes,& SOCb);
		fscanf(fp,"%s %f", notes,& DClitter);
		fscanf(fp,"%s %f", notes,& DChumads);
		fscanf(fp,"%s %f", notes,& DChumus);
		fscanf(fp,"%s %f", notes,& HumadCN);
		fscanf(fp,"%s %f", notes,& HumusCN);
		fscanf(fp,"%s %f", notes,& PassiveC);
		fscanf(fp,"%s %f", notes,& Soil_MicrobioIndex);
		fscanf(fp,"%s %f", notes,& HighestWT);
		fscanf(fp,"%s %f", notes,& Soil_WaterObstructLayer);
		fscanf(fp,"%s %f", notes,& slope);
		fscanf(fp,"%s", notes);

		if(strcmp(notes, "Salinity")!=0) 
		{
			 Soil_Quality = 0.0;
			fscanf(fp,"%d", & SCSuse);
		}
		else
		{
			fscanf(fp,"%f", & Soil_Quality);
			fscanf(fp,"%s %d", notes,& SCSuse);
		}

		if( Sks<0.015)  Sks = 0.015f;//sks default 0.015
		MissFlag=0;
	}
    
    // Read crop parameter
    int ri, yc, db_CycleYear[20], FCTT=0;
	int db_Rotation_Number, FarmMode=0, FarmCropNumber;
	int pemp;

	CString FCT60;
	//FILE *db;

	CString CropDB;
	FILE *cropdb;

	if(MissFlag==0) fscanf(fp,"%s",notes);//"--------------------"
	MissFlag=0;

NewFarmCrop:

	FCTT++;
	FCT60.Format("%s_%d", INTERMANAGE, FCTT);
	_mkdir(FCT60);
	
	fscanf(fp,"%s",notes);//"Crop_data:"
	if(strcmp(notes, "Crop_data:")!=0) Toendd("Crop_data:", fname);
	
	fscanf(fp,"%s %d", notes,&db_Rotation_Number);// "  Rotation_Number"
	if(strcmp(notes, "Rotation_Number=")!=0) Toendd("Rotation_Number=", fname);
	
	DB.Format("%s\\CropRotation.txt", FCT60);//###
	db=fopen(DB, "w");
	fprintf(db, "%d\n", db_Rotation_Number);
	fclose(db);
	
	// Rotation_Number=db_Rotation_Number;
		// Set CroPracticeArray
	//rotation.dim( Rotation_Number);
	//cycle.dim( Rotation_Number,  years);

	for(int ix1=1;ix1<=db_Rotation_Number;ix1++)
	{
		int db_TotalYear;
		int tilln, TillMonth, TillDay, TillMethod;
		int manun, ManuMonth, ManuDay, ManuType, ManuMethod,ManureAppHour;
		float ManuAmount, ManuCN, ManuN, ManureDepth, ManureNH4, ManureNO3,ManureDM,ManurePH;

		fscanf(fp,"%s %d", notes,&ri);// "---->"
		if(strcmp(notes, "Rotation_ID=")!=0) Toendd("Rotation_ID=", fname);
		

		//ri=ix1;
		
			//normal crop
		fscanf(fp,"%s %d", notes,&db_TotalYear);
		if(strcmp(notes, "Totalyear=")!=0) Toendd("Totalyear=", fname);
		
		
		fscanf(fp,"%s %d", notes,&db_CycleYear[ix1]);
		if(strcmp(notes, "Years_Of_A_Cycle=")!=0) Toendd("Years_of_a_cycle=", fname);
		
		DB.Format("%s\\CropRotation_%d.txt", FCT60, ix1);//write: ReadInputDatafromDND, OK
		db=fopen(DB, "w");
		fprintf(db, "%d\n", ix1);
		fprintf(db, "%d\n", db_TotalYear);			
		fprintf(db, "%d\n", db_CycleYear[ix1]);
		fclose(db);	

		//rrr = ix1;
		for (int j=1;j<=db_CycleYear[ix1];j++)
		{
			char WT_file[200];

			//CropDB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, ix1, j);
			CropDB.Format("%s\\CropRotation_%d_%d.txt", FCT60, ix1, j);
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
			if(strcmp(notes, "YearID_of_a_cycle=")!=0) Toendd("YearID_of_a_cycle=", fname);
			
		
			//yc = j;

			fscanf(fp,"%s %d", notes,&cropn);//CCPP.M_YrCrops[ix1][j]);
			if(strcmp(notes, "Crop_total_Number=")!=0) Toendd("Crop_total_Number=", fname);
			
					
			fprintf(cropdb, "%d\n", cropn);
			//cropn=CCPP.M_YrCrops[ix1][j];

			//cycle.get(ix1,j)->CropNumber = cropn;
			//yyy = j;
			//SetArrayRange(1, cropn);
			int db_Type, db_Pmonth, db_Pday, db_Hmonth , db_Hday, db_Hyear, db_CoverCrop, db_PerennialCrop;
			int db_Transplant;
			float db_Yield, db_Residue;
			float db_GrowthReproductive, db_PsnEfficiency, db_PsnMax, db_TreeAge=0.0;
			float db_TreeCurrentAge, db_TreeLeafMax, db_TreeLeafMin;
			float db_GrainFraction, db_LeafFraction, db_ShootFraction, db_RootFraction;
			float db_GrainCN, db_LeafCN, db_ShootCN, db_RootCN;
			float db_TDD, db_Water, db_OptT, db_Nfix, db_Vascularity;
			float db_GrainFill;
			float db_LAImax;
			float db_FrostKill;
			float db_AlfCHRMX, db_ALFCDRMX, db_ALFCTMX, db_ALFPDFMX;
			float db_Root1, db_Root2;
			float db_AGResp1, db_AGResp2;//new Root Respiration data.
			int	db_RootShape;
			float db_kext1, db_kext2, db_cropHeight;
			float db_cropGRate, db_cropTime, db_RUEHI, db_DelayP;

			for (int k=1;k<=cropn;k++) 
			{
				if(MissFlag==0) fscanf(fp,"%s",notes);
				fscanf(fp,"%d",&pemp);	
				MissFlag=0;
				if(strcmp(notes, "Crop_ID=")!=0) Toendd("Crop_ID=", fname);
								

				fscanf(fp,"%s %d",notes,&db_Type);
				if(strcmp(notes, "Crop_Type=")!=0) Toendd("Crop_Type=", fname);
								

				fscanf(fp,"%s %d %d",notes, &db_Pmonth , &db_Pday);
				if(strcmp(notes, "Plant_time=")!=0) Toendd("Plant_time=", fname);
				
				
				fscanf(fp,"%s %d %d",notes,&db_Hmonth , &db_Hday);
				if(strcmp(notes, "Harvest_time=")!=0) Toendd("Harvest_time=", fname);
				

				fscanf(fp,"%s %d",notes,&db_Hyear);
				if(strcmp(notes, "Year_of_harvest=")!=0) Toendd("Year_of_harvest=", fname);
				
				
				fscanf(fp,"%s %f",notes,&db_Residue);
				if(strcmp(notes, "Ground_Residue=")!=0) Toendd("Ground_Residue=", fname);
				

				fscanf(fp,"%s %f",notes,&db_Yield);// "
				if(strcmp(notes, "Yield=")!=0) Toendd("Yield=", fname);
							

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
				//if(strcmp(notes, "Rate_reproductive=")!=0) Toendd("Rate_reproductive=", fname);
				

				fscanf(fp,"%s",notes);
				if(strcmp(notes, "Leaf_CN=")!=0) 
				{
					float jff;
					fscanf(fp,"%f",&jff);
					db_LeafCN = 0.0;
				}
				else
				{
					fscanf(fp,"%f", &db_LeafCN);
				}				
				//if(strcmp(notes, "Rate_vegetative=")!=0) Toendd("Rate_vegetative=", fname);
				

				fscanf(fp,"%s %f",notes,&db_PsnEfficiency);
				//if(strcmp(notes, "Psn_efficiency=")!=0) Toendd("Psn_efficiency=", fname);
				

				fscanf(fp,"%s %d",notes,&db_Transplant);
				//if(strcmp(notes, "Psn_maximum=")!=0) Toendd("Psn_maximum=", fname);
				

				fscanf(fp,"%s %f",notes,&db_TreeAge);
				//if(strcmp(notes, "TreeAge=")!=0) Toendd("TreeAge=", fname);
				
				
				fscanf(fp,"%s %d",notes,&db_CoverCrop);
				if(strcmp(notes, "Cover_crop=")!=0) Toendd("Cover_crop=", fname);
				

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
						db_LeafFraction = 0.5f * db_ShootFraction;
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

					fscanf(fp,"%s %f",notes,&db_TreeAge);
					fscanf(fp,"%s %f",notes,&db_TreeCurrentAge);
					fscanf(fp,"%s %f",notes,&db_TreeLeafMax);
					fscanf(fp,"%s %f",notes,&db_TreeLeafMin);
					fscanf(fp,"%s %d",notes,&db_RootShape);
					fscanf(fp,"%s %f",notes,&db_GrainFill);
					fscanf(fp, "%s %f", notes, &db_LAImax);
					fscanf(fp, "%s %f", notes, &db_FrostKill);
					fscanf(fp, "%s %f", notes, &db_AlfCHRMX);
					fscanf(fp, "%s %f", notes, &db_ALFCDRMX);
					fscanf(fp, "%s %f", notes, &db_ALFCTMX);
					fscanf(fp, "%s %f", notes, &db_ALFPDFMX);
					fscanf(fp, "%s %f", notes, &db_Root1);//root respiration parm1
					fscanf(fp, "%s %f", notes, &db_Root2);//root respiration parm2
					fscanf(fp, "%s %f", notes, &db_AGResp1);//root respiration parm1
					fscanf(fp, "%s %f", notes, &db_AGResp2);//root respiration parm2
					fscanf(fp, "%s %f", notes, &db_cropGRate);//root respiration parm2
					fscanf(fp, "%s %f", notes, &db_cropTime);//root respiration parm2
					fscanf(fp, "%s %f", notes, &db_RUEHI);//root respiration parm2
					fscanf(fp, "%s %f", notes, &db_DelayP);//root respiration parm2
					
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
				fprintf(cropdb, "%f %f\n", db_LAImax, db_FrostKill);
				fprintf(cropdb, "%f %f %f %f\n", db_AlfCHRMX, db_ALFCDRMX,db_ALFCTMX,db_ALFPDFMX);
				fprintf(cropdb, "%f %f\n", db_Root1, db_Root2);
				fprintf(cropdb, "%f %f\n", db_AGResp1, db_AGResp2);
				fprintf(cropdb, "%f %f %f %f\n", db_cropGRate, db_cropTime,db_RUEHI,db_DelayP);
				
			}
			
			fclose(cropdb);
			
			//Tillage
			//DB.Format("%s\\Inter\\CropTill_%d_%d.txt", OUTPUT, ix1, j);
			DB.Format("%s\\CropTill_%d_%d.txt", FCT60, ix1, j);
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
			if(strcmp(notes, "Tillage_number=")!=0) Toendd("Tillage_number=", fname);
			

			fprintf(db, "%d\n", tilln);

				//cycle.get(ri,yc)->TillNumber = tilln;
			//SetArrayRange(2, tilln);
			for (int kx1=1;kx1<=tilln;kx1++) 
			{
				fscanf(fp,"%s %d", notes,&pemp);// "th Tillage:"   //  Month,Day,method"
				if(strcmp(notes, "Tillage_ID=")!=0) Toendd("Tillage_ID=", fname);
				

				fscanf(fp,"%s %d %d %d", notes,&TillMonth, &TillDay, &TillMethod);
				if(strcmp(notes, "Month/Day/method=")!=0) Toendd("Tillage_Month/Day/method=", fname);
				

				fprintf(db, "%d  %d  %d\n", TillMonth, TillDay, TillMethod);	
			}
			fclose(db);

			//Fertilization
			//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, ix1, j);
			DB.Format("%s\\CropFert_%d_%d.txt", FCT60, ix1, j);
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
			if(strcmp(notes, "Fertil_number=")!=0) Toendd("Fertil_number=", fname);
			

			fprintf(db, "%d\n", fertn);

			if(fertn!=-1)
			{
				for (int k=1;k<=fertn;k++) 
				{
					if(MissFlag==0) fscanf(fp,"%s %d", notes,&pemp);
					else fscanf(fp,"%d", &pemp);
					MissFlag=0;

					/*fscanf(fp,"%s %d", notes,&temp);
					if(strcmp(notes, "fertilization_ID=")!=0) Toendd("fertilization_ID=", fname);
					*/

					fscanf(fp,"%s %d %d %d", notes,&FertMonth, &FertDay, &FertMethod);
					if(strcmp(notes, "Month/Day/method=")!=0) Toendd("Month/Day/method=", fname);
					

					fscanf(fp,"%s %f", notes,&FertDepth);
					if(strcmp(notes, "Depth=")!=0) Toendd("Depth=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNitrate);
					if(strcmp(notes, "Nitrate=")!=0) Toendd("Nitrate=", fname);
					

					fscanf(fp,"%s %f", notes,&FertAbi);
					if(strcmp(notes, "AmmBic=")!=0) Toendd("AmmBic=", fname);
					

					fscanf(fp,"%s %f", notes,&FertUrea);
					if(strcmp(notes, "Urea=")!=0) Toendd("Urea=", fname);
					

					fscanf(fp,"%s %f", notes,&FertAnh);
					if(strcmp(notes, "Anh=")!=0) Toendd("Anh=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNH4NO3);
					if(strcmp(notes, "NH4NO3=")!=0) Toendd("NH4NO3=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNH42SO4);
					if(strcmp(notes, "NH42SO4=")!=0) Toendd("NH42SO4=", fname);
					

					fscanf(fp,"%s %f", notes,&FertNH42HPO4);
					if(strcmp(notes, "NH4HPO4=")!=0) Toendd("NH4HPO4=", fname);
					

					fprintf(db, "%d %d %d\n", FertMonth, FertDay, FertMethod);
					fprintf(db, "%f %f %f %f %f %f %f %f\n", FertNitrate, FertAbi, FertUrea, FertAnh, FertNH4NO3, 
					FertNH42SO4, FertNH42HPO4, FertDepth);
					
					fscanf(fp,"%s %f", notes,&DayRelease);
					if(strcmp(notes, "Release_rate=")!=0) Toendd("Release_rate=", fname);					

					fscanf(fp,"%s %f", notes,&NIefficiency);
					if(strcmp(notes, "Inhibitor_efficiency=")!=0) Toendd("Inhibitor_efficiency=", fname);					

					fscanf(fp,"%s %f", notes,&NIduration);
					if(strcmp(notes, "Inhibitor_duration=")!=0) Toendd("Inhibitor_duration=", fname);	
					
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
						if(strcmp(notes, "Urease_efficiency=")!=0) Toendd("Urease_efficiency=", fname);
						fscanf(fp,"%s %f", notes, &UreaseDuration);
						if(strcmp(notes, "Urease_duration=")!=0) Toendd("Urease_duration=", fname);
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
			//DB.Format("%s\\Inter\\CropManu_%d_%d.txt", OUTPUT, ix1, j);
			DB.Format("%s\\CropManu_%d_%d.txt", FCT60, ix1, j);
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

			if(strcmp(notes, "Manure_number=")!=0) Toendd("Manure_number=", fname);
			
						
			fprintf(db, "%d\n", manun);

			//cycle.get(ri,yc)->ManNumber = manun;
			//SetArrayRange(4, manun);
			for (int kx2=1; kx2<=manun; kx2++) 
			{
				if(MissFlag==0) fscanf(fp,"%s %d", notes,&pemp);
				else fscanf(fp,"%d", &pemp);
				MissFlag=0;

				if(strcmp(notes, "Manure_ID=")!=0) Toendd("Manure_ID=", fname);
				

				fscanf(fp,"%s %d %d", notes,&ManuMonth, &ManuDay);
				if(strcmp(notes, "Month/Day=")!=0) Toendd("Month/Day=", fname);
				

				fscanf(fp,"%s %f %f", notes,&ManuAmount, &ManuCN);
				if(strcmp(notes, "Amount/C|N_ratio=")!=0) Toendd("Amount/C|N_ratio=", fname);
				

				fscanf(fp,"%s %d", notes, &ManuType);
				if(strcmp(notes, "Type=")!=0) Toendd("Type=", fname);
				

				fscanf(fp,"%s", notes);
				if(strcmp(notes, "Method=")!=0)
				{ 
					ManuMethod = 0;
					MissFlag=1;
				}
				else
					fscanf(fp,"%d",&ManuMethod);

				fscanf(fp,"%s %f", notes,&ManureDepth);
				fscanf(fp,"%s %f", notes,&ManuN);
				fscanf(fp,"%s %f", notes,&ManureNH4);
				fscanf(fp,"%s %f", notes,&ManureNO3);
				fscanf(fp,"%s %d", notes,&ManureAppHour);
				fscanf(fp,"%s %f", notes,&ManureDM);
				fscanf(fp,"%s %f", notes,&ManurePH);

				fprintf(db, "%d %d\n", ManuMonth, ManuDay);
				fprintf(db, "%f %f %d %d %f\n", ManuAmount, ManuCN, ManuType, ManuMethod, ManureDepth);
				//fprintf(db, "%f %f %f\n", ManuN, ManureNH4, ManureNO3);
				fprintf(db, "%f %f %f %d %f %f\n", ManuN, ManureNH4, ManureNO3, ManureAppHour, ManureDM, ManurePH);

			}
			fclose(db);

			//Plastic
	
			DB.Format("%s\\CropPlastic_%d_%d.txt", FCT60, ix1, j);
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

			for (int kx3=1;kx3<=weedn;kx3++) 
			{
				fscanf(fp,"%s %d", notes,&pemp);// "th Weeding:"			//Month,Day,method"
				//if(strcmp(notes, "Plastic_ID=")!=0) Toendd("Plastic_ID=", fname);
				

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
			DB.Format("%s\\CropFloo_%d_%d.txt", FCT60, ix1, j);
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
			
			if(strcmp(notes, "Flood_number=")!=0) Toendd("Flood_number=", fname);
				

			fscanf(fp,"%s %f", notes,&FloodWaterN);// FloodWaterN
			//if(strcmp(notes, "Leak_type=")!=0) Toendd("Leak_type=", fname);
				

			fscanf(fp,"%s %d", notes,&WaterControl);// 
			if(strcmp(notes, "Water_control=")!=0) Toendd("Water_control=", fname);
				

			fscanf(fp,"%s %f", notes, &WaterLeakRate);
			if(strcmp(notes, "Leak_rate=")!=0) Toendd("Leak_rate=", fname);
				
				
			fprintf(db, "%d %f %d %f\n", floon, FloodWaterN, WaterControl, WaterLeakRate);

			for (int kx4=1;kx4<=floon;kx4++) 
			{ 
				fscanf(fp,"%s %d", notes,&pemp);// "th Flooding:"			
				if(strcmp(notes, "Flooding_ID=")!=0) Toendd("Flooding_ID=", fname);
				

				fscanf(fp,"%s %d %d", notes,&FlooMonth1, &FlooDay1);
				if(strcmp(notes, "Flood_Month/Day=")!=0) Toendd("Flood_Month/Day=", fname);
				

				fscanf(fp,"%s %d %d", notes,&FlooMonth2, &FlooDay2);
				if(strcmp(notes, "Drain_Month/Day=")!=0) Toendd("Drain_Month/Day=", fname);
				

				fscanf(fp,"%s %f", notes,&FlooN);
				//if(strcmp(notes, "Water_N=")!=0) Toendd("Water_N=", fname);
				

				fscanf(fp,"%s %d", notes,&ShallowFlood);
				if(strcmp(notes, "Shallow_flood=")!=0) Toendd("Shallow_flood=", fname);
				

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
			DB.Format("%s\\CropIrri_%d_%d.txt", FCT60, ix1, j);
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

			if(strcmp(notes, "Irrigation_number=")!=0) Toendd("Irrigation_number=", fname);				

			fscanf(fp,"%s %d", notes,&IrriMode);// Irrigation type"
			if(strcmp(notes, "Irrigation_type=")!=0) Toendd("Irrigation_type=", fname);
				

			fscanf(fp,"%s %f", notes,&IrriIndex);// Irrigation type"
			if(strcmp(notes, "Irrigation_Index=")!=0) Toendd("Irrigation_Index=", fname);

			fscanf(fp,"%s", notes);
			if(strcmp(notes, "Irrigation_Method=")!=0) //Toendd("Irrigation_Method=", fname);
			{
				IrriMethod = 0;
				MissFlag=1;
			}
			else
				fscanf(fp,"%d", &IrriMethod);

			fprintf(db, "%d %d %f %d\n", irrin, IrriMode, IrriIndex, IrriMethod);

			for (int kx5=1;kx5<=irrin;kx5++) 
			{
				if(MissFlag==1) 
				{
					fscanf(fp,"%d", &pemp);
					MissFlag = 0;
				}
				else fscanf(fp,"%s %d", notes,&pemp);
				if(strcmp(notes, "Irrigation_ID=")!=0) Toendd("Irrigation_ID=", fname);				

				fscanf(fp,"%s %d %d", notes,&IrriMonth, &IrriDay);
				if(strcmp(notes, "Irr_Month/Day=")!=0) Toendd("Irr_Month/Day=", fname);				

				int jd;
				fscanf(fp,"%s %f %d", notes,&IrriAmount, &jd);
				if(jd!=0&&jd!=1&&jd!=2) IrriMethod=0;
				else IrriMethod=jd;				

				fprintf(db, "%d %d\n", IrriMonth, IrriDay);
				fprintf(db, "%f %d\n", IrriAmount, IrriMethod);
			}
			fclose(db);

			//Grazing
			//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, ix1, j);
			DB.Format("%s\\CropGraz_%d_%d.txt", FCT60, ix1, j);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString notes;
				notes.Format("Can not create file %s", DB);
				AfxMessageBox(notes);
				exit(0);
			}

			int grazn, GrazMonth1, GrazDay1, GrazMonth2, GrazDay2;
			float GrazHour, Dairy, Beef, Pig, Horse, Sheep;
		
			if(MissFlag==1) 
			{
				fscanf(fp,"%d", &grazn);
				MissFlag = 0;
			}
			else 
			{
				fscanf(fp,"%s %d", notes,&grazn);// "Grazing_number---"
			}

			if(strcmp(notes, "Grazing_number=")!=0) Toendd("Grazing_number= ", fname);				

			fprintf(db, "%d\n", grazn);

			//cycle.get(ri,yc)->GrazingNumber = grazn;
			//SetArrayRange(8, grazn);
			for (int kx6=1;kx6<=grazn;kx6++) 
			{
				fscanf(fp,"%s %d", notes,&pemp);
				if(strcmp(notes, "Grazing_ID=")!=0) Toendd("Grazing_ID=", fname);
				

				fscanf(fp,"%s %d %d", notes,&GrazMonth1, &GrazDay1);
				if(strcmp(notes, "Start_Month/Day=")!=0) Toendd("Start_Month/Day=", fname);
				

				fscanf(fp,"%s %d %d", notes,&GrazMonth2, &GrazDay2);
				if(strcmp(notes, "End_Month/Day=")!=0) Toendd("End_Month/Day=", fname);
				

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
				if(strcmp(notes, "Graz_Hours_Per_day=")!=0) Toendd("Graz_Hours_Per_day=", fname);				

				fprintf(db, "%d %d\n", GrazMonth1, GrazDay1);
				fprintf(db, "%d %d\n", GrazMonth2, GrazDay2);
				fprintf(db, "%f\n", GrazHour);
				fprintf(db, "%f %f %f %f %f\n", Dairy, Beef, Pig, Sheep, Horse);

			}
			fclose(db);	
			
			//Grass cutting
			//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, ix1, j);
			DB.Format("%s\\GrassCut_%d_%d.txt", FCT60, ix1, j);
			db=fopen(DB, "w");
			if(db==NULL) note(0, DB);
			
			int cutn, CutMonth, CutDay, CutPart;
			float CutAmount;
		
			fscanf(fp,"%s %d", notes,&cutn);// "Cutting_number---"
			

			//if(strcmp(notes, "Cut_number=")==0) 
			//{
				fprintf(db, "%d\n", cutn);

				for (int kx7=1;kx7<=cutn;kx7++) 
				{
					if(MissFlag==0) fscanf(fp,"%s %d", notes,&pemp);
					else 
					{
						fscanf(fp,"%d", &pemp);
						MissFlag = 0;
					}
					if(strcmp(notes, "Cut_ID=")!=0) Toendd("Cut_ID=", fname);
					

					fscanf(fp,"%s %d %d", notes,&CutMonth, &CutDay);
					if(strcmp(notes, "Cut_Month/Day=")!=0) Toendd("Cut_Month/Day=", fname);
					

					fscanf(fp,"%s %f", notes,&CutAmount);
					if(strcmp(notes, "Cut_amount=")!=0) Toendd("Cut_amount=", fname);
					

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
			//}
			fclose(db);	
		}
	}	

	fscanf(fp,"%s", notes);
	if(strcmp(notes, "----------------------------------------")==0) FarmMode = 1;
	if(strcmp(notes, "Crop_model_approach")==0) 
	{
		FarmMode = 0;
		MissFlag = 1;
	}

	if(FarmMode==1) 
		goto NewFarmCrop;

	if(MissFlag==0) fscanf(fp,"%s %d", notes,&jjd);// CropModel);
	else 
	{
		fscanf(fp,"%d", &jjd);// CropModel);
		MissFlag=0;
	}


	if(strcmp(notes, "Crop_model_approach")!=0) 
	{
		//Toendd("Crop_model_approach", fname);
		//
		 jjd = 0;
	}


	////////////////////////////////////////////////////////////////////////////////
	if( SCSuse==1)
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
	sprintf(LB,"%s\\Inter\\UnitSystem", OUTPUT);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", US);
	fclose(ddb);

/*	CString CM;
	FILE *cm;
	CM.Format("%s\\Inter\\CropModel", OUTPUT);
	cm=fopen(CM, "w");
	if(cm==NULL)
	{
		CString notes;
		notes.Format("Can not create file %s", CM);
		AfxMessageBox(notes);
		exit(0);
	}
	else
	{
		fprintf(cm, "%d\n",  CropModel);
	}
	fclose(cm);
*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Read soil parameters
	int result = -1;
	FILE *fpi;
    char nnote[255], SoilName[50];
	
	float DClay, DFldcap, DWiltpt, DSks, DPorosity;
    
	//if ( Soil_Texture<1 &&  Soil_Texture>13) return result;
    sprintf(fname, "%s\\Library\\lib_soil\\soil_%d", ROOTDIR,  Soil_Texture);
	
	if( Soil_Texture<=0)
	{
		sprintf( SoilName, "None");
		DClay = 0.0;
		DPorosity = 0.0;
		DSks = 0.0;
		DFldcap = 0.0;
		DWiltpt = 0.0;
	}
	else
	{
		fpi=fopen(fname, "r");
		if(fpi==NULL) note(0, fname);		
		fscanf(fpi,"%s %s",  SoilName,nnote);// NameNote);
		fclose (fpi); 


		/*fscanf(fpi,"%f %s", &DClay,nnote);
		fscanf(fpi,"%f %s", &DPorosity, nnote);// StsNote);
		fscanf(fpi,"%f %s", &DSks, nnote);// cm/min
		fscanf(fpi,"%f %s", &DFldcap, nnote);// FldcapNote);
		fscanf(fpi,"%f %s", &DWiltpt, nnote);// WiltptNote);
		//fscanf(fpi,"%f %s", & Soilhtcp, note);// SoilhtcpNote);
		//fscanf(fpi,"%f %s", & Psisat, note);// PsisatNote);
		//fscanf(fpi,"%f %s", & Beta, note);// BetaNote);
		  
		DSks *= 0.6;//cm/min ->m/hr
		if(DSks<0.008) DSks=0.008;
*/
	}

	
	//Soil_Clay=DClay;
	//Fldcap=DFldcap;
	//Wiltpt=DWiltpt;
	//Sks=DSks;
	//Soil_Porosity=DPorosity;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Save site info
	//char fname[255];
	FILE *fpo;

    sprintf(fname,"%s\\Inputs\\site",OUTPUT);
	fpo=fopen(fname,0);
	if (fpo==NULL) note(1, fname);

	fprintf(fpo,"%s\n", sitename);
	fprintf(fpo,"%d %d %f %ld %d\n",  years,  ifdaily,
		 latitude,  0,  120);
    fprintf(fpo,"%d %d\n",  Soil_landuse, 0);
    fclose (fpo);

	sprintf(fname, "%s\\Inputs\\SPAN",OUTPUT);
	fpo=fopen(fname,0);
	if (fpo==NULL) note(1, fname);
	fprintf(fpo, "%d\n", 1);
	fclose(fpo);

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Record climate files
	// SaveClimateFileOfAYear
	int TotalYear, FirstYear;  
    char ch[255];
    	
    for (int ix2=1; ix2<= years; ix2++) 
	{
		if( if1File==0)
			sprintf(ch,"%s",ClimateFilename[ix2]);
		else
			sprintf(ch,"%s",ClimateFilename[1]);
				
		char fname[356],Pname[356],cn[356];
		CString SiteName[4]={"","Changtu","Chaoyang","Fuxin"};
		CString CropName[4]={"","corn","s_wheat",""};
		FILE *fpo,*fpi;		

		int ii;
		for (ii=strlen(ch)-1;ii>=0;ii--)
		{
			if (ch[ii]==92)//'\\')
			{
				sprintf(ch,"%s",ch+ii+1);
				break;
			}
		}

		sprintf(Pname,"%s",ch);
		sprintf(cn,"%s",ch);
		
		char Dname[300], Yname[300], LocationName[300];
		char Dname1[300],Dname2[300],Dname3[300],Yname1[300],Yname2[300],Yname3[300];
		int Site, YieldYear, YieldToday, YieldCrop,YieldMonth, YieldDay;
		int UseID=0, id, IfCheck=0;

		if(UseID==10)//drought option
		{
				CString YF;
				FILE* yf;
				YF.Format("%s\\YieldPrediction", INTER);
				yf=fopen(YF, "r");
				if(yf==NULL) note(0,YF);

				fscanf(yf, "%d %d %d %d %s %d %d", &Site, &YieldCrop, &YieldYear, &YieldToday, LocationName,&YieldMonth, &YieldDay);
				fclose(yf);

					
			if(id==1)
			{
				sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,id);
				if ((fpo=fopen(fname,0))==NULL) note(1, fname);
				
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
				if ((fpo=fopen(fname,0))==NULL) note(1, fname);		
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
			id = ix2;
			sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,id);
			if ((fpo=fopen(fname,0))==NULL) note(1, fname);
			
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
				NewCreateDailyClimateFile(Pname, Dname, Yname, UseID, ClimateFileType, latitude, IfCheck,
					NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
					LocationName, YieldYear, YieldToday, 0, "");
			}
			else
			{
				NewCreateDailyClimateFile(Pname, Dname1, Yname1, UseID, ClimateFileType, latitude, IfCheck,
					NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
					LocationName, YieldYear, YieldToday, 1, "");
				NewCreateDailyClimateFile(Pname, Dname2, Yname2, UseID, ClimateFileType, latitude, IfCheck,
					NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
					LocationName, YieldYear, YieldToday, 2, "");
				NewCreateDailyClimateFile(Pname, Dname3, Yname3, UseID, ClimateFileType, latitude, IfCheck,
					NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2, CO2IncreaseRate,
					LocationName, YieldYear, YieldToday, 3, "");
			}
		}
		else
		{
			NewCreateDailyClimateFile(Pname, Dname, Yname, UseID, ClimateFileType, latitude, IfCheck,
				NO3NH4_Rainfall,NH3_Atmosphere,BaseCO2,CO2IncreaseRate,
				"None", 0, 0, 0, "");
		}
    }//end of climate year loop
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// ReadClimateHead(1);

	char fn1[256],fn2[256];
	int  jday, yr=1;
	float maxT, minT, Rainfall, solrad, Day_Hrs;

	sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,yr);
	fpo=fopen(fname, "r");
	if (fpo==NULL) note(1, fname);
	fscanf(fpo,"%s",fn1);
	fscanf(fpo,"%s",fn2);
	fclose(fpo);

	float temp;

	sprintf(fname,"%s\\Inputs\\%s", OUTPUT,fn1);
	fpo=fopen(fname, "r");
	if (fpo==NULL) note(1, fname);
	fscanf(fpo, "%d %f %f %f %f %f %f",
		&jday, &temp, &maxT, &minT, &Rainfall, &solrad, &Day_Hrs);
	Soil_T=temp;
	fclose(fpo);

	float dt;
	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,fn2);
	fp=fopen(fname, "r");
	if (fp==NULL) note(1,fname);
	for (j=1;j<=12;j++) 
	{
		fscanf(fp,"%f", &dt);
	}
    fscanf(fp,"%f", &dt);
	fclose(fp);
	float AnnualMeanT = dt;
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	//SetSoilH();

	float H;

	float AcWater   = 0.0;
	float SurfWater = 0.0;
	float SnowPack  = 0.0;

	int Idc = 1 + (int)Soil_BypassFlow;
    
    float Qstar = (float)(6.45 * (Soil_Clay - 0.01) + 1);
    float BypassF = Soil_BypassFlow;
	int max_layers=280-10;
	float TH = SOILDEPTH;//1.0 m, total depth of simulated soil profile 
    dt = 0.01f / Soil_Porosity;
    if (dt < Sks) H = dt;
    else H = Sks;
    if (H <= 0) 
	{
        AfxMessageBox ("Data error on soil porosity or hydrological conductivity");
		exit(0);
    }	
	if (H*max_layers < TH )
		H = TH / max_layers;

	int Q = (int)(TH / H);

	if (Q > max_layers) 
	{
		Q = max_layers;
		H = TH / max_layers;
	}

	////////////////////////////////////////////////////////////////////////////////////////////
    // SaveSoilParas(1);

	float CEC= (float)(Soil_Clay * 46.0);
    float m  = (float)(Soil_Density * 1000. * H * 10000.);
    float V  = (float)(H * 10000. * Soil_Porosity);	// m^3/layer/ha
    
    int n;
    n = Q;
    double RCVL[2], RCL[2], RCR[2];
    double Urea[2], NH3[2];
    double Tranr[2], OCini[2], Dphum[2], CharC[2];
    double s_NO3[2], s_NH4[2], ClayNH4[2];
    double s_NO[2], s_N2O[2];
    double s_N2[2], s_NO2[2], s_IniNH4[2];
    
    double PS, FLDCAPw, Wiltptw, TravelTime, ClayF1, ClayF2;//, ePS;
    float RCNRVL, RCNRL, RCNRR, RCNB, RCNH, RCNM;
    double stub1, stub2, stub3, Dbm;
    
    PS		= H * Soil_Porosity;	// porosity  (m/layer)
    FLDCAPw = PS * Fldcap;	// m water/layer FieldCapacity
    Wiltptw = PS * Wiltpt;	// m water/layer
    TravelTime = 20.0 * (PS - FLDCAPw) / Sks;	// hr/layer
        // fraction of soil water available for plants, can be tuned
    ClayF1 = pow(10.0,-Soil_Clay / 0.75 - 0.2);
    ClayF2 = Soil_Clay * 6.;

	CN_ratios(&RCNRVL, &RCNRL, &RCNRR, &RCNB, &RCNH, &RCNM, &PassiveCCN);
    
	int DFF;
	CString SPP;
	FILE* spp;
	SPP.Format("%s\\Inter\\SOCpartition.txt", OUTPUT);
	spp=fopen(SPP, "r");
	if(spp==NULL)
	{
		
	}
	else
	{
		fscanf(spp, "%d", &DFF);
		if(DFF==1)
			fscanf(spp, "%f %f %f %f %f", &RCNRVL, &RCNRL, &RCNRR, &RCNH, &RCNM);
	}
	fclose(spp);

	//RCNB=RCNH;

    
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

	float F_soc = Soil_OCatSurface/0.058f;
	if(F_soc>1.0f) F_soc = 1.0f;

	//ClayNH4[1] = F_soc * CEC * 0.4; 
	//ClayNH4[1] = CEC * 0.4; //NewChange

    Urea[1]= 0.;
    NH3[1] = 0.;
    stub1  = 0.;
    stub2  = 0.;
    stub3  = 0.;
     
	float TCN=0.0;    
        s_NO[1] = 0.;
        s_N2O[1]= 0.;
        s_N2[1] = 0.;
        s_NO2[1]= 0.;

	int id = 1, SoilRetardation=0;

    sprintf(fname,"%s\\Inputs\\soil-%d",OUTPUT,(int)fabsf(id));
	fpo=fopen(fname,0);
	if (fpo==NULL) note(1, fname);

	float IniFrostN2O=0, IniFrostN2=0,ice=0,tt[290];
	int Retard=1;
	if (SoilRetardation==1) Retard=3;
    
		//check data
 /*   if (Soil_Texture<0) {
		AfxMessageBox("No Soil_Texture information!");
		exit(0);
	}
    if (Soil_Clay<0) {
		AfxMessageBox("No Soil_Clay information!");
		exit(0);
	}
    if (Soil_Density<0) {
		AfxMessageBox("No Soil_Density information!");
		exit(0);
	}
    if (Soil_OCatSurface<0) {
		AfxMessageBox("No Soil_Organic information!");
		exit(0);
	}
    if (Soil_NO3<0) {
		AfxMessageBox("No Soil_NO3 information!");
		exit(0);
	}
    if (Soil_NH4<0) {
		AfxMessageBox("No Soil_NH4 information!");
		exit(0);
	}
    if (Soil_Litter<0 || Soil_humads<0 || Soil_humus<0) {
		AfxMessageBox("Soil_Litter or humads, mumus information error!");
		exit(0);
	}
*/
	for (int ix3=1; ix3<=Q; ix3++)
	{
		tt[ix3] = AnnualMeanT + (Soil_T - AnnualMeanT)/ (float)powf(ix3*H*100, 0.5);
		if (Soil_T<0.0 && tt[ix3] < Soil_T) tt[ix3] = Soil_T;
	}

	fprintf(fpo,"%3d\n", Soil_Texture);
    fprintf(fpo,"%s\n\n", SoilName);

    fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
		Soil_Clay, Soil_Porosity, Sks, Fldcap,
		Wiltpt, LateralInflux); 
    fprintf(fpo,"%f %f %f %f %d  %f\n",
		0.0, 0.0, Dbm, Soil_pH, 
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
	sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
	sni=fopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 1);
	fclose(sni);
    
	////////////////////////////////////////////////////////////////////////////////////////////
    NewSaveInterFarmParas();

	/////////////////////////////////////////////////////////////////////////////////////////////
    NewSaveCropParas();

	/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MANURE	
//	NewRecordManureFiles(years);
#endif

#ifdef BASE

	sprintf(IData.sitename, "%s", sitename);
	IData.latitude = latitude;
	IData.years = years;
	IData.ifdaily = ifdaily;
	IData.ClimateFileType = ClimateFileType;
	IData.NO3NH4_Rainfall = NO3NH4_Rainfall;
	IData.NH3_Atmosphere = NH3_Atmosphere;
	IData.BaseCO2 = BaseCO2;
	IData.if1File = if1File;
	IData.CO2IncreaseRate = CO2IncreaseRate;

#endif
}

void NewCreateDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, float latitude,
							CString IfCheck, float NO3NH4_Rainfall,float NH3_Atmosphere,float BaseCO2,
							float CO2IncreaseRate, char *LocaName, int YieldYear, int YieldToday,
							int DMW, char *r_Country)
{
	int tn, j;
	float Day_Hrs,temp=0.0,Rainfall=0.0,maxT=0.0,minT=0.0,solrad,wind_speed=2.0;
	float AveMonthT[13],AveYrT, TotalYrRain, humidity=30.0, CloudIndex=1.0;
	int   jday=0,jday0=0,Aday;
	char fname[256],cn[256], cjunk[200], junkcc[300], ch[256];
	char CurrentClim[300], junkc[200];
	
	FILE* fpo, *fpi, *fcc;
	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,Dname);
	fpo=fopen(fname,"w");
	if(fpo==NULL) note(1,fname);
        
	if(UseID==0)
	{
		/*fpi=sopen(Pname,"r");
		if (fpi==NULL) note(1, Pname);
				
		if (ClimateFileType!=4) 
			fscanf(fpi,"%s", cjunk);	// read climate file dataname

		if(strcmp(cjunk, "1")==0)
		{
			fclose(fpi);
			fpi=sopen(Pname,"r");
		}*/ 
	}
	else
	{
		if(DMW==0)//year 1
		{
			sprintf(Pname, "%s\\Database\\%s\\%s\\Lib_clim\\%s_%d", ROOTDIR, r_Country, LocaName, LocaName, YieldYear-1);
		}
		else if(DMW==1)//dry year
		{
			sprintf(Pname, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_dry", ROOTDIR, r_Country, LocaName, LocaName);
		}
		else if(DMW==2)//medium
		{
			sprintf(Pname, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_mid", ROOTDIR, r_Country, LocaName, LocaName);
		}
		else
		{
			sprintf(Pname, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_wet", ROOTDIR, r_Country, LocaName, LocaName);
		}

		fpi=fopen(Pname,"r");
		if (fpi==NULL) note(0, Pname);
		 
		if (ClimateFileType!=4) 
		{
			fscanf(fpi,"%s", cjunk);	// read climate file dataname
			if(strcmp(cjunk, "1")==0)
			{
				fclose(fpi);
				fpi=fopen(Pname,"r");
			} 
		}

		sprintf(CurrentClim, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_%d", ROOTDIR, r_Country, LocaName, LocaName, YieldYear);
		fcc=fopen(CurrentClim, "r");
		if(fcc==NULL) note(0, CurrentClim);
		fscanf(fcc,"%s", cjunk);
	}    
    
	tn = 0;
    AveYrT = 0.0;
	TotalYrRain = 0.0;

	//default data
	wind_speed = 2.0;//m/s
	humidity = 60.0;//%
	int djunk=0, dflag=0;
	char www[100];

	for (j = 1;j<=12;j++) 
	{
		AveMonthT[j] = 0;
        for (int kx8 = 1;kx8<=MonthDay[j];kx8++) 
		{	
			dflag=0;

			if(j==1&&kx8==1)
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

			if(latitude<0.0)
			{
				Aday = tn - 182;//for southern semisphere
				if(Aday<=0) Aday = 365 + Aday;

				solrad = day_par(Aday, -latitude, &Day_Hrs);
			}
			else
				solrad = day_par(tn, latitude, &Day_Hrs);//extre-terrestrial radiation, MJ/m2/day

			if(Day_Hrs<=0.0) Day_Hrs=0.01f;

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
					temp = (maxT + minT) * 0.5f;
			
					CloudIndex = 0.9693f * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001f;
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

					CloudIndex = 0.9693f * (float)exp(-1.3903f * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001f;
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
					Rainfall *= 0.1f;
					jday = tn;

					CloudIndex = 0.9693f * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001f;
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

					CloudIndex = 0.9693f * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001f;
					solrad *= CloudIndex;
				}
				else if(ClimateFileType==7) //maxT, minT, prec, relative humidity
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &humidity);
					else fscanf(fpi, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &humidity);

					temp =float( (maxT + minT) *0.5);
					
					CloudIndex = 0.9693f * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001f;
					solrad *= CloudIndex;
				}

			if(tn!=jday)
			{
				CString note;
				note.Format("Error at day %d in climate data file %s", tn, Pname);
				AfxMessageBox(note);
				exit(0);
			}

			/*if (IfCheck=="Check")
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
			}*/

            jday0 = jday;
			
			if (tn==1) Soil_T = temp;

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
            AveMonthT[j] += temp / MonthDay[j];
            AveYrT += (temp / 365.0f);
            TotalYrRain += Rainfall;
		}
	}
    fclose (fpi);
    fclose (fpo);
	if(DMW>0) fclose (fcc);

	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,Yname);
	fpo=fopen(fname,"w");
	if (fpo==NULL) note(1, fname);
    for (int jx1=1;jx1<=12;jx1++) 
	{
		fprintf(fpo,"%.2f	", AveMonthT[jx1]);
	}
    fprintf(fpo,"\n%.2f\n", AveYrT);
    fprintf(fpo,"%.2f\n", TotalYrRain);
    fprintf(fpo,"%.3f\n", NO3NH4_Rainfall);// 
    fprintf(fpo,"%.2f\n", NH3_Atmosphere);// 
	fprintf(fpo,"%.2f\n", BaseCO2);// 
	fprintf(fpo,"%.2f\n", CO2IncreaseRate);
	fprintf(fpo,"%d\n", ClimateFileType);
    fclose (fpo);
	
//outerr:;
    
}

void NewCreateDailyClimateFile(char* Pname, char* Dname, char* Yname, int UseID, int ClimateFileType, float latitude, int IfCheck, float NO3NH4_Rainfall, float NH3_Atmosphere, float BaseCO2, float CO2IncreaseRate, char* LocaName, int YieldYear, int YieldToday, int DMW, char* r_Country)
{
}

void Toendd(char *notes, char *FN)
{
	CString cl;
	cl.Format("The old input file does not match this version any more. You may need to create a new file manually. Sorry for the inconvenience. Error at %s", FN);
	AfxMessageBox(cl);
    exit(0);
}

int NewSaveInterFarmParas()
{
	int rrr, yyy, TotalManureCropss;
	int result = -1;
    char fname[255];
	FILE *fp;
    int n, day, db_Rotation_Number, db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20];
		
	int TillID[300], TillMonth[300], TillDay[300], TillMethod[300];
	int FertMonth[300], FertDay[300], FertMethod[300];
	float FertNitrate[300], FertAbi[300], FertUrea[300], FertAnh[300], FertAmNi[300], NH42SO4[300], NH42HPO4[300], FertDepth[300];
	int ManuMonth[300], ManuDay[300], ManuType[300], ManuMethod[300], FertOption=0,ManureAppHour[300], UseManPool[300], AutoManure;
	float ManuAmount[300], ManuCN[300], ManuN[300], ManureDepth[300], ManureNH4[300], ManureNO3[300],ManureDM[300],ManurePH[300],ManPoolFrac[300],ManPoolRate[300];
	float DayRelease[300], NIefficiency[300], NIduration[300];
	float UreaseEfficiency[300], UreaseDuration[300];
	int WeedMonth1[300], WeedDay1[300], WeedMonth2[300], WeedDay2[300];
	float CoverFraction[300];
	int FlooID[300], FlooMonth1[300], FlooDay1[300], FlooMonth2[300], FlooDay2[300];
	float FlooN[300];
	int ShallowFlood[300];
	int IrriMonth[366], IrriDay[366], irrimethod[366], NewTotalManureCropss;
	float IrriAmount[366];
	int TileIrriDays[366];
	int GrazMonth1[300], GrazDay1[300], GrazMonth2[300], GrazDay2[300];
	float GrazHour[300], Dairy[300], Beef[300], Pig[300], Horse[300], Sheep[300];
	int CutMonth[300], CutDay[300], CutPart[300];
	float CutAmount[300];
	char Fertigation[200];
	float WaterGetherIndex, WaterLeakRate;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex,m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	CString FCT0;

#ifdef MANURE
	int CropIDID, ManureCropOrder;
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d %d", &NewTotalManureCropss, &ManureCropOrder, &CropIDID);
	fclose(xff);
	//FCT0.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	//FCT0.Format("%s", INTERMANAGE);
	NewTotalManureCropss = 1;
#endif

for(int MFFC=1; MFFC<=NewTotalManureCropss; MFFC++)
{
#ifdef MANURE
	FCT0.Format("%s_%d", INTERMANAGE, MFFC);
#else 
	FCT0.Format("%s_1", INTERMANAGE);
#endif

	CString DB;
	FILE *db;

	DB.Format("%s\\CropRotation.txt", FCT0);
	db=fopen(DB, "r");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not open file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(db, "%d", &db_Rotation_Number);
	fclose(db);

	for(rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		DB.Format("%s\\CropRotation_%d.txt", FCT0, rrr);//read: SaveInterFarmParas
		db=fopen(DB, "r");
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);

		for(yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
		{    
			// Save tillage
			DB.Format("%s\\CropTill_%d_%d.txt", FCT0, rrr, yyy);
			db=fopen(DB, "r");
			fscanf(db, "%d", &n);
			for(int ix4=1; ix4<=n; ix4++)
			{
				TillID[ix4] = ix4;
				fscanf(db, "%d %d %d", &TillMonth[ix4], &TillDay[ix4], &TillMethod[ix4]);
			}
			fclose(db);
	
			sprintf(fname,"%s\\ti-%d_%d",FCT0,rrr,yyy);
			fp=fopen(fname, "w");
			if (fp == NULL) return result;
    
   			fprintf(fp,"%d\n",n);
			for (int ix5 = 1;ix5<=n;ix5++) 
			{		
				day = JulianDay(TillMonth[ix5], TillDay[ix5]);
				fprintf(fp,"%d %d\n",day,TillMethod[ix5]);
			}
			fclose (fp);
    
    // Save fertilization
	DB.Format("%s\\CropFert_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
	if(n==-1)
	{
		fscanf(db, "%s", Fertigation);
	}
	else
	{
		for(int ix6=1; ix6<=n; ix6++)
		{
			fscanf(db, "%d %d %d", &FertMonth[ix6], &FertDay[ix6], &FertMethod[ix6]);
			fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[ix6], &FertAbi[ix6], &FertUrea[ix6], &FertAnh[ix6], &FertAmNi[ix6], 
				&NH42SO4[ix6], &NH42HPO4[ix6], &FertDepth[ix6]);
			fscanf(db, "%f %f %f %f %f", &DayRelease[ix6], &NIefficiency[ix6], &NIduration[ix6],&UreaseEfficiency[ix6], &UreaseDuration[ix6]);
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
		for (int ix7 = 1; ix7<=n;ix7++) 
		{
			day = JulianDay(FertMonth[ix7], FertDay[ix7]);
			fprintf(fp,"%d %f\n", day, FertDepth[ix7]*0.01);			
			fprintf(fp,"%f %f %f %f %f %f %f\n", FertNitrate[ix7], FertAbi[ix7], FertUrea[ix7], FertAnh[ix7], FertAmNi[ix7], NH42SO4[ix7], NH42HPO4[ix7]); 
			fprintf(fp,"%d %f %f %f %f %f\n", FertOption, DayRelease[ix7], NIefficiency[ix7], NIduration[ix7],UreaseEfficiency[ix7], UreaseDuration[ix7]);
		}		
	}
    fclose (fp);
    
        // Save Manuring file
	//DB.Format("%s\\Inter\\CropManu_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropManu_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
	for(int ix8=1; ix8<=n; ix8++)
		{
			fscanf(db, "%d %d", &ManuMonth[ix8], &ManuDay[ix8]);
			fscanf(db, "%f %f %d %d %f", &ManuAmount[ix8], &ManuCN[ix8], &ManuType[ix8], &ManuMethod[ix8], &ManureDepth[ix8]);
			fscanf(db, "%f %f %f %d %f %f %f %f %d %d", &ManuN[ix8], ManureNH4[ix8], ManureNO3[ix8], ManureAppHour[ix8], ManureDM[ix8], ManurePH[ix8], ManPoolFrac[ix8], ManPoolRate[ix8], UseManPool[ix8] , AutoManure);
		}
	fclose(db);

    //sprintf(fname,"%s\\Inter\\ma-%d_%d",OUTPUT,rrr,yyy);
	sprintf(fname,"%s\\ma-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, 0);
    if (fp == NULL) return result;
    
    fprintf(fp,"%d\n", n);
    for (int ix9=1; ix9<=n; ix9++) 
	{
        day = JulianDay(ManuMonth[ix9], ManuDay[ix9]);
		
		fprintf(fp, "%d %f %f %d %d %f %f %f %f %d %f %f %f %f %d %d\n",
			day,
			ManuAmount[ix9],
			ManuCN[ix9],
			ManuType[ix9],
			ManuMethod[ix9],
			ManureDepth[ix9],
			ManuN[ix9],
			ManureNH4[ix9],
			ManureNO3[ix9],
			ManureAppHour[ix9],
			ManureDM[ix9],
			ManurePH[ix9],
			ManPoolFrac[ix9],
			ManPoolRate[ix9],
			UseManPool[ix9]
		    ,AutoManure);
    }
    fclose (fp);
        
    // Save plastic file
	int WeedOption;
	
	DB.Format("%s\\CropPlastic_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &n, &WeedOption);
	for(int ix10=1; ix10<=n; ix10++)
	{
		fscanf(db, "%d %d", &WeedMonth1[ix10], &WeedDay1[ix10]);
		fscanf(db, "%d %d", &WeedMonth2[ix10], &WeedDay2[ix10]);
		fscanf(db, "%f", &CoverFraction[ix10]);
	}
	fclose(db);

	sprintf(fname,"%s\\pl-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, 0);
    if (fp == NULL) return result;
    
    fprintf(fp, "%d %d\n",n, WeedOption);
    for (int ix11 = 1; ix11<=n;ix11++) 
	{
        int day1 = JulianDay(WeedMonth1[ix11], WeedDay1[ix11]);
		int day2 = JulianDay(WeedMonth2[ix11], WeedDay2[ix11]);
        fprintf(fp,"%d %d\n",day1, day2);
		fprintf(fp,"%f\n",CoverFraction[ix11]);
    }
    fclose (fp);
    
        // Save Flooding file
	int WaterControl;
	float FloodWaterN;
	CString WT_file;
	//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropFloo_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d %f %d %f", &n, &FloodWaterN, &WaterControl, &WaterLeakRate);
	for(int ix12=1; ix12<=n; ix12++)
		{
			FlooID[ix12] = ix12;
			fscanf(db, "%d %d", &FlooMonth1[ix12], &FlooDay1[ix12]);
			fscanf(db, "%d %d", &FlooMonth2[ix12], &FlooDay2[ix12]);
			fscanf(db, "%f", &FlooN[ix12]);
			fscanf(db, "%d", &ShallowFlood[ix12]);
		}

	fscanf(db, "%f", &WaterGetherIndex);
	fscanf(db, "%s", WT_file);

	fscanf(db, "%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
												&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);
	
	fclose(db);

    
	sprintf(fname,"%s\\fl-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, 0);
    if (fp == NULL) return result;

	fprintf(fp,"%d\n", n);

    for (int ix13 = 1; ix13<=n;ix13++) 
	{
        day = JulianDay(FlooMonth1[ix13], FlooDay1[ix13]);		
        fprintf(fp, "%d ",day);
        day = JulianDay(FlooMonth2[ix13], FlooDay2[ix13])+1;	
        fprintf(fp, "%d\n",day);
		fprintf(fp, "%f %d\n", FlooN[ix13], ShallowFlood[ix13]);
    }
	
    fprintf(fp, "%d %f %f %f\n", WaterControl, WaterLeakRate, WaterGetherIndex, FloodWaterN);
	fprintf(fp, "%s\n",WT_file);
	fprintf(fp, "%f %f %f %f %f %f\n",
		m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, m_SurfOutflowIntensity, m_GroundOutflowIntensity);
    fclose (fp);

	     
    // Save Irrigation file
	int IrrMode;
	float IrrIndex;
	
	DB.Format("%s\\CropIrri_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d %d %f %d", &n, &IrrMode, &IrrIndex, &irrimethod[0]);
	for(int ix14=1; ix14<=n; ix14++)
		{
			fscanf(db, "%d %d", &IrriMonth[ix14], &IrriDay[ix14]);
			fscanf(db, "%f %d %d", &IrriAmount[ix14], &irrimethod[ix14], &TileIrriDays[ix14]);
		}
	fclose(db);

	sprintf(fname,"%s\\ir-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, 0);
    if (fp == NULL) return result;

    fprintf(fp,"%d %f %d\n", n, IrrIndex, irrimethod[0]);
    
	for (int ix15=1; ix15<=n;ix15++) 
	{
        day = JulianDay(IrriMonth[ix15], IrriDay[ix15]);
		
        fprintf(fp,"%d %f %d\n", day, IrriAmount[ix15], irrimethod[ix15]);
    }
    //fprintf(fp," %d", cycle.get(rn, cn)->IrrIndex);
    fclose (fp);
    

        // Save Grazing file
	
	//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropGraz_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
		for(int ix16=1; ix16<=n; ix16++)
		{
			fscanf(db, "%d %d", &GrazMonth1[ix16], &GrazDay1[ix16]);
			fscanf(db, "%d %d", &GrazMonth2[ix16], &GrazDay2[ix16]);
			fscanf(db, "%f", &GrazHour[ix16]);
			fscanf(db, "%f %f %f %f %f", &Dairy[ix16], &Beef[ix16], &Pig[ix16], &Sheep[ix16], &Horse[ix16]);
		}
	fclose(db);

    //sprintf(fname,"%s\\Inter\\gr-%d_%d",OUTPUT,rrr,yyy);
	sprintf(fname,"%s\\gr-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, 0);
    if (fp == NULL) return result;

    fprintf(fp, "%d\n", n);
	int bt,et;
    for (int ix17 = 1; ix17<=n; ix17++)
    {
		bt=JulianDay(GrazMonth1[ix17], GrazDay1[ix17]);
		et=JulianDay(GrazMonth2[ix17], GrazDay2[ix17]);
		fprintf(fp, "%d %d %f %f %f %f %f %f\n",bt,et,Dairy[ix17], Beef[ix17], Pig[ix17], Sheep[ix17],Horse[ix17],GrazHour[ix17]);
		
    }
    fclose(fp);

	// Save garss cutting file
	//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\GrassCut_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
		for(int ix18=1; ix18<=n; ix18++)
		{
			fscanf(db, "%d %d", &CutMonth[ix18], &CutDay[ix18]);
			fscanf(db, "%f", &CutAmount[ix18]);
			fscanf(db, "%d", &CutPart[ix18]);
		}
	fclose(db);

    //sprintf(fname,"%s\\Inter\\cut-%d_%d",OUTPUT,rrr,yyy);
	sprintf(fname,"%s\\cut-%d_%d",FCT0,rrr,yyy);
	fp=fopen(fname, "w");
    if (fp == NULL) note(0, fname);

    fprintf(fp, "%d\n", n);
    for (int ix19 = 1; ix19<=n; ix19++)
    {
		bt=JulianDay(CutMonth[ix19], CutDay[ix19]);
		fprintf(fp, "%d %f\n",bt, CutAmount[ix19]);
		fprintf(fp, "%d\n", CutPart[ix19]);
    }
    fclose(fp);

	}
	}
}
    //result = 1;
    return (0);
}

int NewSaveCropParas() //!!!!!!!!!!!
{
	int CropIDID, ManureCropOrder, NewTotalManureCropss;
	CString SETINPUTS;
	SETINPUTS.Format("%s\\inputs", OUTPUT);

#ifdef MANURE	
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d %d", &NewTotalManureCropss, &ManureCropOrder, &CropIDID);
	fclose(xff);
	//FCT10.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	//FCT10.Format("%s", INTERMANAGE);
	NewTotalManureCropss = 1;
#endif

    char fname[255],outname[255],Crop_Name[150];
    int  kkk, yr;//, hyr=0;
	FILE *fcrop, *fpi;

	int db_Rotation_Number;
	int db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20],db_PerennialCrop[20][20][5];
	int db_YrCrops[20][20], db_YrCropOrder[20][20][5], db_YrCropType[20][20][5], db_CoverCrop[20][20][5];
	int db_PMonth[20][20][5], db_PDay[20][20][5], db_HMonth[20][20][5], db_HDay[20][20][5], db_HYr[20][20][5];
	float db_Residue[20][20][5], db_Yield[20][20][5], db_RepRate[20][20][5];
	int db_Transplant[20][20][5]={0,0};
	float db_PsnEff[20][20][5], db_PsnMax[20][20][5], db_TreeAge[20][20][5]={0.0,0.0};
	float db_GrainFraction[20][20][5], db_LeafFraction[20][20][5], db_ShootFraction[20][20][5], db_RootFraction[20][20][5];
	float db_GrainCN[20][20][5], db_LeafCN[20][20][5], db_ShootCN[20][20][5], db_RootCN[20][20][5];
	float db_TDD[20][20][5], db_Water[20][20][5], db_OptT[20][20][5], db_Nfix[20][20][5], db_Vascularity[20][20][5],db_GrainFill[20][20][5], db_LAImax[20][20][5], db_FrostKill[20][20][5], db_AlfCHRMX[20][20][5], db_ALFCDRMX[20][20][5], db_ALFCTMX[20][20][5], db_ALFPDFMX[20][20][5];
	float db_TreeCurrentAge[20][20][5]={0.0,0.0}, db_TreeLeafMax[20][20][5]={0.0,0.0}, db_TreeLeafMin[20][20][5]={0.0,0.0};
	int db_RootShape[20][20][5];
	float db_Root1[20][20][5], db_Root2[20][20][5], db_VE[20][20][5], db_V1[20][20][5], db_VT[20][20][5], db_R1[20][20][5], db_R3[20][20][5], db_R5[20][20][5], db_R7[20][20][5], db_R8[20][20][5], db_PVE[20][20][5], db_PV1[20][20][5], db_PVT[20][20][5], db_PR1[20][20][5], db_PR3[20][20][5], db_PR5[20][20][5], db_PR7[20][20][5], db_PR8[20][20][5];
	float db_AGResp1[20][20][5], db_AGResp2[20][20][5];
	float db_Kext1[20][20][5], db_Kext2[20][20][5], db_cropHeight[20][20][5];//Theo db_cropHeight,db_Kext2,db_Kext1
	float db_cropGRate[20][20][5], db_cropTime[20][20][5], db_RUEHI[20][20][5], db_DelayP[20][20][5];
	CString DB;
	FILE *db;

	CString FCT0, FCT100;

for(int MFFC=1; MFFC<=NewTotalManureCropss; MFFC++)
{
#ifdef MANURE
	FCT0.Format("%s_%d", INTERMANAGE, MFFC);
	FCT100.Format("%s\\FarmCrop_%d", SETINPUTS, MFFC);
	_mkdir(FCT100);
#else
	FCT0.Format("%s_1", INTERMANAGE);
	FCT100.Format("%s", SETINPUTS);
#endif

	DB.Format("%s\\CropRotation.txt", FCT0);
	db=fopen(DB, "r");
	if(db==NULL) note(0,DB);
	
	fscanf(db, "%d", &db_Rotation_Number);
	fclose(db);

	int ccc;
	for(int rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		DB.Format("%s\\CropRotation_%d.txt", FCT0, rrr);//read: SaveCropParas()
		db=fopen(DB, "r");
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);

		for(int yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
		{
			//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, rrr, yyy);
			DB.Format("%s\\CropRotation_%d_%d.txt", FCT0, rrr, yyy);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &db_YrCrops[rrr][yyy]);

			for(int ccc=1; ccc<=db_YrCrops[rrr][yyy]; ccc++)
			{
				fscanf(db, "%d %d", &db_YrCropOrder[rrr][yyy][ccc], &db_YrCropType[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_PMonth[rrr][yyy][ccc], &db_PDay[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_HMonth[rrr][yyy][ccc], &db_HDay[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_HYr[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_Residue[rrr][yyy][ccc], &db_Yield[rrr][yyy][ccc]);
				fscanf(db, "%f %d", &db_RepRate[rrr][yyy][ccc], &db_Transplant[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_PsnEff[rrr][yyy][ccc], &db_PsnMax[rrr][yyy][ccc]);
				fscanf(db, "%f", &db_TreeAge[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_CoverCrop[rrr][yyy][ccc]);	
				fscanf(db, "%d", &db_PerennialCrop[rrr][yyy][ccc]);

				fscanf(db, "%f %f %f %f", &db_GrainFraction[rrr][yyy][ccc], &db_LeafFraction[rrr][yyy][ccc], &db_ShootFraction[rrr][yyy][ccc], &db_RootFraction[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_GrainCN[rrr][yyy][ccc], &db_LeafCN[rrr][yyy][ccc], &db_ShootCN[rrr][yyy][ccc], &db_RootCN[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f %f", &db_TDD[rrr][yyy][ccc], &db_Water[rrr][yyy][ccc], &db_OptT[rrr][yyy][ccc], &db_Nfix[rrr][yyy][ccc], &db_Vascularity[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_TreeAge[rrr][yyy][ccc], &db_TreeCurrentAge[rrr][yyy][ccc], &db_TreeLeafMax[rrr][yyy][ccc], &db_TreeLeafMin[rrr][yyy][ccc]);
				fscanf(db, "%d %f", &db_RootShape[rrr][yyy][ccc], &db_GrainFill[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_LAImax[rrr][yyy][ccc], &db_FrostKill[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_AlfCHRMX[rrr][yyy][ccc], &db_ALFCDRMX[rrr][yyy][ccc], &db_ALFCTMX[rrr][yyy][ccc], &db_ALFPDFMX[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_Root1[rrr][yyy][ccc], &db_Root2[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_AGResp1[rrr][yyy][ccc], &db_AGResp2[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f", &db_Kext1[rrr][yyy][ccc], &db_Kext2[rrr][yyy][ccc], &db_cropHeight[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f\n", &db_cropGRate[rrr][yyy][ccc], &db_cropTime[rrr][yyy][ccc], &db_RUEHI[rrr][yyy][ccc], &db_DelayP[rrr][yyy][ccc]);
					
			}
			
			fclose(db);

			///////////////////////////////////////////////////////////
			char fname[255];
			FILE *fp;
			int WinterCropFlag=0, LeftDays=0;
    
			sprintf(fname, "%s\\cyc-%d_%d", FCT0,rrr, yyy);
			fp=fopen(fname, "w");

			if (db_YrCrops[rrr][yyy]==0) //no crop
			{
				fprintf(fp, "%d\n", 0);
				fprintf(fp, "%d  %s  %d  %d  %f  %d\n", 0, "None", 0, 0, 0.0, 10);
				fprintf(fp, "%d  %d  %f  %f  %d\n", 0, 0, 0.0, 0.0, 999);
				fprintf(fp, "%f  %d  %f  %f  %f\n", 0.0, 0, 0.0, 0.0, 0.0);
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
				for (int ix20 = 1;ix20<=db_YrCrops[rrr][yyy];ix20++) 
				{
					int SeedDay = JulianDay(db_PMonth[rrr][yyy][ix20], db_PDay[rrr][yyy][ix20]);
					int HarvDay = JulianDay(db_HMonth[rrr][yyy][ix20], db_HDay[rrr][yyy][ix20]);
					int GrowDays;
					if(db_HYr[rrr][yyy][ix20]==1)//SeedDay<HarvDay)
					{
						GrowDays = HarvDay - SeedDay;
						WinterCropFlag = 0;
						LeftDays = 0;
					}
					else
					{
						GrowDays = 365 - SeedDay + HarvDay + (db_HYr[rrr][yyy][ix20] - 2) * 365;
						WinterCropFlag = db_HYr[rrr][yyy][ix20] - 1;//yyy-1;
						if(WinterCropFlag==1) LeftDays = GrowDays;
						else LeftDays = GrowDays - (365*(db_HYr[rrr][yyy][ix20] - 1) - SeedDay);
					}

					int wwww=111, jd;
					if(ix20==db_YrCrops[rrr][yyy]) wwww = 999;

					
					int CropType = db_YrCropType[rrr][yyy][ix20];
					char CropNameX[100];

					///////////////////////////////////////////////////////////////////////////////////////////
					int v_CropID[95], v_Perennial[95];
					float v_max_biomass_C[95], v_grain_fraction[95], v_leaf_fraction[95], v_leafstem_fraction[95], v_root_fraction[95];
					float v_GrainCN[95], v_LeafCN[95], v_ShootCN[95], v_RootCN[95], v_TreeAge[95];
					float v_WaterDemand[95], v_OptimumT[95], v_TDD[95], v_Nfixation[95], v_Vascularity[95];
					float v_Root1[95], v_Root2[95], v_AGResp1[95], v_AGResp2[95];
					float v_Kext1[95],v_Kext2[95],v_CMaxH[95];
					float v_cropGRate[95], v_cropTime[95], v_RUEHI[95], v_DelayP[95];
					//CString v_CropName[95];
					char v_CropName[95][100]={"NONE","NONE"};

					ReadCropPara1(v_CropID, v_CropName, v_max_biomass_C, v_grain_fraction, v_leaf_fraction,
					  v_leafstem_fraction, v_root_fraction, v_GrainCN, 
					  v_LeafCN, v_ShootCN, v_RootCN, v_WaterDemand, v_OptimumT, 
					  v_TDD, v_Nfixation, v_Vascularity, v_Perennial, v_TreeAge,v_Root1,v_Root2,v_AGResp1,v_AGResp2,v_Kext1,v_Kext2,v_CMaxH, v_cropGRate, v_cropTime, v_RUEHI, v_DelayP);

					///////////////////////////////////////////////////////////////////////////////////////////
					
					/*m_CropYield = v_max_biomass_C[CropType] * v_grain_fraction[CropType];//kg C/ha
					m_ShootYield = v_max_biomass_C[CropType] * v_leafstem_fraction[CropType];
					m_RootYield = v_max_biomass_C[CropType] * v_root_fraction[CropType];
					m_GrainFraction = v_grain_fraction[CropType];
					m_ShootFraction = v_leafstem_fraction[CropType];
					m_RootFraction = v_root_fraction[CropType];*/
					
					sprintf(Crop_Name, "%s", v_CropName[CropType]);

					////////////////////////////////////////////////////////////////////////////////////////////

    				float PlantC = db_Yield[rrr][yyy][ix20] / db_GrainFraction[rrr][yyy][ix20];
					float LeafC = PlantC * db_LeafFraction[rrr][yyy][ix20];
					float ShootC = PlantC * db_ShootFraction[rrr][yyy][ix20];
					float RootC = PlantC * db_RootFraction[rrr][yyy][ix20];
					float PlantCN = 1.0f / (db_GrainFraction[rrr][yyy][ix20]/db_GrainCN[rrr][yyy][ix20] + 
						db_LeafFraction[rrr][yyy][ix20]/db_LeafCN[rrr][yyy][ix20] + 
						db_ShootFraction[rrr][yyy][ix20]/db_ShootCN[rrr][yyy][ix20] + 
						db_RootFraction[rrr][yyy][ix20]/db_RootCN[rrr][yyy][ix20]);
					float MaxPlantN = PlantC / PlantCN;					
					if(db_YrCropType[rrr][yyy][ix20]==0) MaxPlantN = 0.0;
					
					fprintf(fp, "%d  %s  %d  %d  %f  %d\n", db_YrCropType[rrr][yyy][ix20], Crop_Name, WinterCropFlag, LeftDays, db_Yield[rrr][yyy][ix20], db_HYr[rrr][yyy][ix20]);
					fprintf(fp, "%d  %d  %f  %f  %d\n", SeedDay, GrowDays, db_Residue[rrr][yyy][ix20], MaxPlantN, wwww);
					fprintf(fp, "%f  %d  %f  %f  %f\n", db_TreeAge[rrr][yyy][ix20], db_Transplant[rrr][yyy][ix20], 
						db_RepRate[rrr][yyy][ix20], db_PsnEff[rrr][yyy][ix20], db_PsnMax[rrr][yyy][ix20]);
					fprintf(fp, "%d\n", db_CoverCrop[rrr][yyy][ix20]);
					fprintf(fp, "%d\n", db_PerennialCrop[rrr][yyy][ix20]);
					fprintf(fp, "%f %f %f %f\n", db_GrainFraction[rrr][yyy][ix20], db_LeafFraction[rrr][yyy][ix20], db_ShootFraction[rrr][yyy][ix20], db_RootFraction[rrr][yyy][ix20]);
					fprintf(fp, "%f %f %f %f\n", db_GrainCN[rrr][yyy][ix20], db_LeafCN[rrr][yyy][ix20], db_ShootCN[rrr][yyy][ix20], db_RootCN[rrr][yyy][ix20]);
					fprintf(fp, "%f %f %f %f %f\n", db_TDD[rrr][yyy][ix20], db_Water[rrr][yyy][ix20], db_OptT[rrr][yyy][ix20], db_Nfix[rrr][yyy][ix20], db_Vascularity[rrr][yyy][ix20]);
					fprintf(fp, "%f %f %f %f\n", db_TreeAge[rrr][yyy][ix20], db_TreeCurrentAge[rrr][yyy][ix20], db_TreeLeafMax[rrr][yyy][ix20], db_TreeLeafMin[rrr][yyy][ix20]);
					fprintf(fp, "%d %f\n", db_RootShape[rrr][yyy][ix20], db_GrainFill[rrr][yyy][ix20]);
					fprintf(fp, "%f %f\n", db_LAImax[rrr][yyy][ix20], db_FrostKill[rrr][yyy][ix20]);
					fprintf(fp, "%f %f %f %f\n", db_AlfCHRMX[rrr][yyy][ix20], db_ALFCDRMX[rrr][yyy][ix20], db_ALFCTMX[rrr][yyy][ix20], db_ALFPDFMX[rrr][yyy][ix20]);
					fprintf(fp, "%f %f\n", db_Root1[rrr][yyy][ix20], db_Root2[rrr][yyy][ix20]);
					fprintf(fp, "%f %f\n", db_AGResp1[rrr][yyy][ix20], db_AGResp2[rrr][yyy][ix20]);
					fprintf(fp, "%f %f %f\n", db_Kext1[rrr][yyy][ix20], db_Kext2[rrr][yyy][ix20], db_cropHeight[rrr][yyy][ix20]);
					fprintf(fp, "%f %f %f %f\n", db_cropGRate[rrr][yyy][ix20], db_cropTime[rrr][yyy][ix20], db_RUEHI[rrr][yyy][ix20], db_DelayP[rrr][yyy][ix20]);
				
				}				
			}
			fclose (fp);
			///////////////////////////////////////////////////////////
		}

	}

    int CropNumbers;
	char Crop_Name[100];
    yr = 0;
    for (int ix21 = 1;ix21<=db_Rotation_Number;ix21++) 
	{
        kkk = 0;
        for (int j = 1;j<=db_RotateSpan[ix21];j++) //total years within a rotation
		{
            yr++;
			kkk++;
        
            // Open output crop file--working one -not linux
			
			sprintf(outname,"%s\\crop-%d",FCT100,yr);
			fcrop=fopen(outname, "w");
			if(fcrop==NULL) note(1, outname);            

			sprintf(fname,"%s\\cyc-%d_%d",FCT0,ix21,kkk);
			fpi=fopen(fname, "r");
			if (fpi==NULL) note(0, fname);
			            
			fscanf(fpi, "%d", &CropNumbers);
			fprintf(fcrop, "%d\n", CropNumbers);

            for (int kx9 = 1;kx9<=CropNumbers;kx9++) 
			{
				fscanf(fpi, "%d  %s  %d  %d  %f  %d", 
					&CYr[1].CropID, Crop_Name, &CYr[1].WCFlag, &CYr[1].Left, &CYr[1].Yield, 
					&CYr[1].HarYr);
				fscanf(fpi, "%d  %d  %f  %f  %d", 
					&CYr[1].SeedDay, &CYr[1].GrowDays, &CYr[1].LeftPrec, 
					&CYr[1].MaxPlanN, &CYr[1].CropOrder);
				fscanf(fpi, "%f  %d  %f  %f  %f", 
					&CYr[1].TreeAge, &CYr[1].Transplant, &CYr[1].GrowthReproductive, 
					&CYr[1].PsnEfficiency, &CYr[1].PsnMax);
				fscanf(fpi, "%d", &CYr[1].CoverCrop);
				fscanf(fpi, "%d", &CYr[1].PerennialCrop);

				fscanf(fpi, "%f %f %f %f", &CYr[1].Grain, &CYr[1].Leaf, &CYr[1].Straw, &CYr[1].Root);
				fscanf(fpi, "%f %f %f %f", &CYr[1].GrainCN, &CYr[1].LeafCN, &CYr[1].ShootCN, &CYr[1].RootCN);
				fscanf(fpi, "%f %f %f %f %f", &CYr[1].CropTDD, &CYr[1].WRuq, &CYr[1].OptT, 
					&CYr[1].CropNFix, &CYr[1].Vascularity);

				fscanf(fpi, "%f %f %f %f", &CYr[1].TreeAge, &CYr[1].TreeCurrentAge, &CYr[1].TreeLeafMax, &CYr[1].TreeLeafMin);
				fscanf(fpi, "%d %f", &CYr[1].RootShape, &CYr[1].GrainFill);
				fscanf(fpi, "%f %f", &CYr[1].LAImax, &CYr[1].FrostKill);
				fscanf(fpi, "%f %f %f %f", &CYr[1].AlfCHRMX, &CYr[1].ALFCDRMX, &CYr[1].ALFCTMX, &CYr[1].ALFPDFMX);
				fscanf(fpi, "%f %f", &CYr[1].Root1, &CYr[1].Root2);
				fscanf(fpi, "%f %f", &CYr[1].ShootResp1, &CYr[1].ShootResp2);
				if(CYr[1].CropID==0) CYr[1].HarYr=1;
				if(CYr[1].TreeAge<0.0) CYr[1].TreeAge=0.0;

				CYr[1].WCFlag = 0;
				CYr[1].Left = 0;


				fprintf(fcrop, "%d  %s  %d  %d  %f  %d\n", 
				CYr[1].CropID, Crop_Name, CYr[1].WCFlag, CYr[1].Left, CYr[1].Yield, CYr[1].HarYr);
				fprintf(fcrop, "%d  %d  %f  %f  %d\n", 
				CYr[1].SeedDay, CYr[1].GrowDays, CYr[1].LeftPrec, 
				CYr[1].MaxPlanN, CYr[1].CropOrder);
				fprintf(fcrop, "%f  %d  %f  %f  %f\n", 
				CYr[1].TreeAge, CYr[1].Transplant, CYr[1].GrowthReproductive, 
				CYr[1].PsnEfficiency, CYr[1].PsnMax);
				fprintf(fcrop, "%d\n", CYr[1].CoverCrop);
				fprintf(fcrop, "%d\n", CYr[1].PerennialCrop);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].Grain, CYr[1].Leaf, CYr[1].Straw, CYr[1].Root);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].GrainCN, CYr[1].LeafCN, CYr[1].ShootCN, CYr[1].RootCN);
				fprintf(fcrop, "%f %f %f %f %f\n", CYr[1].CropTDD, CYr[1].WRuq, CYr[1].OptT, CYr[1].CropNFix, CYr[1].Vascularity);			
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].TreeAge, CYr[1].TreeCurrentAge, CYr[1].TreeLeafMax, CYr[1].TreeLeafMin);
				fprintf(fcrop, "%d %f\n", CYr[1].RootShape, CYr[1].GrainFill);
				fprintf(fcrop, "%f %f\n", CYr[1].LAImax, CYr[1].FrostKill);
				fprintf(fcrop, "%f %f %f %f", CYr[1].AlfCHRMX, CYr[1].ALFCDRMX, CYr[1].ALFCTMX, CYr[1].ALFPDFMX);
				fprintf(fcrop, "%f %f", CYr[1].Root1, CYr[1].Root2);
				fprintf(fcrop, "%f %f", CYr[1].ShootResp1, CYr[1].ShootResp2);
			}

            fclose (fpi);
            fclose (fcrop);
                        
            // output Tillage data
			//sprintf(fname,"%s\\Inter\\ti-%d_%d",OUTPUT,ix21,kkk);
			sprintf(fname,"%s\\ti-%d_%d",FCT0,ix21,kkk);
			//sprintf(outname,"%s\\Inputs\\till-%d",OUTPUT,yr);
			sprintf(outname,"%s\\till-%d",FCT100,yr);
			FileCopy(fname,outname);

            // output Fertilization data
			
			sprintf(fname,"%s\\fe-%d_%d",FCT0,ix21,kkk);			
			sprintf(outname,"%s\\fert-%d",FCT100,yr);
			FileCopy(fname,outname);
            
            // output Manure data
			//sprintf(fname,"%s\\Inter\\ma-%d_%d",OUTPUT,ix21,kkk);
			sprintf(fname,"%s\\ma-%d_%d",FCT0,ix21,kkk);
			//sprintf(outname,"%s\\Inputs\\manu-%d",OUTPUT,yr);
			sprintf(outname,"%s\\manu-%d",FCT100,yr);
			FileCopy(fname,outname);
           
            // output Flooding data
			
			sprintf(fname,"%s\\fl-%d_%d",FCT0,ix21,kkk);
			//sprintf(outname,"%s\\Inputs\\flood-%d",OUTPUT,yr);
			sprintf(outname,"%s\\flood-%d",FCT100,yr);
			FileCopy(fname,outname);
            
            // output Irrigation data
			sprintf(fname,"%s\\ir-%d_%d",FCT0,ix21,kkk);
			sprintf(outname,"%s\\irri-%d",FCT100,yr);
			FileCopy(fname,outname);
            
            // output Weeding data
			//sprintf(fname,"%s\\Inter\\we-%d_%d",OUTPUT,ix21,kkk);
			sprintf(fname,"%s\\pl-%d_%d",FCT0,ix21,kkk);
			sprintf(outname,"%s\\plastic-%d",FCT100,yr);
			FileCopy(fname,outname);

            // output Grazing data
			//sprintf(fname,"%s\\Inter\\gr-%d_%d",OUTPUT,ix21,kkk);
			sprintf(fname,"%s\\gr-%d_%d",FCT0,ix21,kkk);
			//sprintf(outname,"%s\\Inputs\\graz-%d",OUTPUT,yr);
			sprintf(outname,"%s\\graz-%d",FCT100,yr);
			FileCopy(fname,outname);

			// output grass cutting data
			//sprintf(fname,"%s\\Inter\\cut-%d_%d",OUTPUT,ix21,kkk);
			sprintf(fname,"%s\\cut-%d_%d",FCT0,ix21,kkk);
			//sprintf(outname,"%s\\Inputs\\cut-%d",OUTPUT,yr);
			sprintf(outname,"%s\\cut-%d",FCT100,yr);
			FileCopy(fname,outname);

            if (kkk == db_CycleSpan[ix21]) kkk = 0;
    
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

