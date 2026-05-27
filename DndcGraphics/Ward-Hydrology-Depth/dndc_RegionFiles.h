#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <io.h>

void region_site_files(char *county_name, float r_longitude, float r_latitude,	char *CountryName, char *state_name);
int region_climate_files(char *climfile_ID, float r_latitude, float RainN, float BaseCO2,int county_ID1, float CO2IncreaseRate, 
				   int GlobeData, int MonteCarlo, int StartYear, int DroughtID, int DryYear, int MidYear, int WetYear);
void region_farm_files(char* cropping_system, char *CountryName, int province, int junk, int MonteCarlo, int RegionCode, 
					   char* CountryCode, int StateCode, char *NewDire, char* state_name, char* county_name, 
						float ManureN, char* PlantHarvDates, char* FertDates, 
						float* animal, float CountyHa, char* ManureRate, float S_latitude, char* TillDates, 
						char* ResidueData, char* FloodDate, char* CropPara, int DroughtID, int *CropID, 
						int CropNumber, float* DMaxYield, float* DTDD, float* DWaterDemand);
void region_soil_files(int soil_yr, float max_SOC, float min_SOC, float max_clay, float min_clay, 
					float max_pH, float min_pH, float max_BD, float min_BD, int landtype, 
					int OnlyRice, char* CROPID, float WRL, char* state_name, int GlobeData,
					float S_latitude, float IniSnow, int MonteCarlo, float slope, float SoilQuality);

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
					float LagToField[100][10], float LagToMarket[100][10], float LagRemain[100][10], int *LagCover, int *DigTemp,
					float *DigRetentionDays, float *DigToField, float *DigToMarket, float *FieldArea,
					float *BarnTP, float *PenTP, int *FlashType, int LagDrainMonth[100][10], int LagDrainDay[100][10],
					float *DigToRemain, int ComRemoveMonth[100][10], int ComRemoveDay[100][10], float *FlushWater);
