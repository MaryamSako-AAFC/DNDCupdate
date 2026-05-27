#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <io.h>
//#include "dndc_main.h"

void ReadCropPara1(int *v_CropID, char v_CropName[95][100], float *v_max_biomass_C, float *v_grain_fraction, float *v_leaf_fraction,
				  float *v_leafstem_fraction, float *v_root_fraction, float *v_GrainCN, 
				  float *v_LeafCN, float *v_ShootCN, float *v_RootCN, float *v_WaterDemand, float *v_OptimumT, 
				  float *v_TDD, float *v_Nfixatio, float *v_Vascularity, int *v_Perennial, float *v_TreeAge, float *v_Root1, float *v_Root2, float* v_AGResp1, float* v_AGResp2,float* v_Kext1,float* v_Kext2,float* v_CMaxH, float* v_cropGRate, float* v_cropTime, float* v_RUEHI, float* v_DelayP);

FILE *sopen (char *fname, int mode);
FILE *sopen (char *fname, char *mode);
void FileMessage(char* FILEname, int OC);
void FileMessage(CString FILEname, int OC);
void Glean_String(char *String, int Num1, int Num2, char *Sub_Str);
int FileCopy(char *source, char *dest);
void XX(FILE *xx);
void FindCrops(char *cropping_system, int *crop_ID, int *CropNumber);
void DefinePHDates(char *PlantHarvDates, int *plant_jday, int *harvest_jday, int *cropping_number, int *WinterCrop, int *WCN);
void DefineFertDates(char* FertDates, int* CropFertDate, int *CropFertType, 
					 float* CropFertRate, int *TotalFertApplications);//, int *CropFertTYPES, int* crop_ID, int cropping_number);
void CellColor(int FluxType, float Para, int* Rr, int * Gg, int* Bb);
float SOCtoNO3(float SOC, float latitude);
float HumadsFraction(float TTOO, int landtype);
void SocProfile(int landtype, float TTOO, float latitude, float *Soil_Litter, float *Soil_humads, float *Soil_humus, float *PassiveC);
void note(int rw, char* ZZ);
void note(int rw, CString ZZ);
void FindCrops(char *CroppingID, int *CropNumber, int *Cropid);
void DefineTillDates(char *TillDates, int *TillDate, int *TillDepth, int *TotalTillApplications);
void DefineManureDates(char* ManureRate, int* TotalManureApplications, int* CManureDate, float* CManureN, float* CManureCN);
void DefineResidueDates(char* ResidueData, int* TotalResidueApplications, float* ResidueRate);
void DefineFloodDates(char* FloodDate, int* FloodIni, int* FloodEnd, int* FloodMethod, int* TotalFloodApplications);
void FindCropPara(char* CropPara, float *DMaxYield, float *DTDD, float *DWaterDemand, int CropID);
int FindOneCrop(char* CroppingSystem, int Cropid);
float CropTN(float TotC, float GraCN, float LeafCN, float ShoCN, float RooCN, float GraFra, float LeafFra, float ShoFra, float RooFra);
