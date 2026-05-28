#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "direct.h"

#ifdef MANURE
extern class_manure MData;
CString LOSname[7]={"","Dairy","Beef","Veal","Pig","Sheep","Poultry"};
#endif
//dengjia
void class_model::write_globe_summary(int SoilYear, float ha, char* cropping_system, int province, int county, 
				int CountyIDX, char *DatabaseName, char *ScenarioName, int LandOrder, 
				int year, int StartYear, char* r_Province, 
				int helai, int Batch, int GlobeData, int RRRRR, int IrriType,
				char* country_ID, int livestock, int DroughtID, int drc, char f_region[6][150],
				char* DroughtYield, int SoilDataUse, int FFN)
{
	int i, SN, crop_ID[90]={0,0}, cropping_number=0;
	char cropsystem[150][50], SSSS[200];;

	CString DWM[10]={"","Dry","Mid","Wet","NoRain0days","NoRain5days","NoRain10days","NoRain20days","NoRain30days","NoRain50days"};

	FindCrops(cropping_system, crop_ID, &cropping_number);

	EndStub = stub1 + stub2 + stub3;
	yr_dSON = EndSON - IniSON;
	yr_dSIN = EndSIN - IniSIN;

	float net_SOC = EndSOC - IniSOC;
	float Soil_dCO2 = 0.0;

	//if(yr_pond_ev>0.0)
	//	yr_irri = (yr_pond_ev+yr_trans+yr_soil_ev+yr_runoff+yr_leach_water) - yr_rain/100.0;
	//if(yr_irri<0.0) yr_irri = 0.0;
	yr_plant_demand = (yr_pond_ev+yr_trans+yr_soil_ev)*1000.0;
	//yr_trans_WE = (yr_trans)*1000.0;
	yr_TotalEvap = (yr_pond_ev + yr_soil_ev)*1000.0;
	//yr_LeachWater = yr_leach_water*1000.0;
	//yr_IrriWater = yr_irri*1000.0;
	yr_PrecWater = yr_rain*10.0;

	yr_dSoilWater = (yr_rain+yr_irri) - (yr_trans+yr_soil_ev+yr_runoff+yr_leach_water); //m

	CString CropCode;
	FILE *CC;
	CropCode.Format("%s\\Inter\\RegionCropCode", OUTPUT);
	CC = fopen(CropCode, "r");
	if(CC==NULL) note(0, CropCode);
	
	fscanf(CC, "%d", &SN);
	for(int in=1; in<=SN; in++) fscanf(CC, "%s", cropsystem[in]);
	fclose(CC);

	CString RP;
	//char f_region[150];
	FILE* FfFf;
	CString MaMi[3]={"ave","max","min"};
	CString IrIr[2]={"ZeroIrri", "FullIrri"};
#ifdef MANURE
	if(livestock>=1)
	{
		ha = MData.ManureFieldArea;
		sprintf(cropping_system, "%s", LOSname[MData.mm_AnimalType[1]]);
		sprintf(SSSS, "%6.0f", MData.mm_AnimalHeads[1]);

		if(ha==0.0)
		{
			IniSOC=0.0;
			//net_SOC=0.0;
			yr_addmc=0.0;
			yr_addtc=0.0;
			yr_addrc=0.0;
			yr_ch4=0.0;
			yr_dnn2o=0.0;
			yr_dnno=0.0;
			yr_dnn2=0.0;
			yr_soil_nh3=0.0;
			yr_plant_nh3=0.0;
			yr_plantn[1]=0.0;
			yr_plantn[2]=0.0;
			yr_plantn[3]=0.0;
			yr_leach_NO3=0.0;
			yr_leach_urea=0.0;
			yr_rainN=0.0;
			yr_fixn[1]=0.0;
			yr_fixn[2]=0.0;
			yr_fixn[3]=0.0;
			yr_minern=0.0;
			yr_addfer=0.0;
			yr_addmn=0.0;
			yr_dSON=0.0;
			yr_dSIN=0.0;
			yr_trans=0.0;
			yr_total_ev=0.0;
			yr_runoff=0.0;
			yr_leach_water=0.0;
			yr_irri=0.0;
			yr_rain=0.0;
			yr_dSoilWater=0.0;
			layerc[1]=0.0;
			layerc[2]=0.0;
			layerc[3]=0.0;
			layerc[4]=0.0;
			layerc[5]=0.0;
			EndSOC=0.0;
			yr_soil_co2=0.0;
			net_SOC=0.0;
		}
	}
	else
		sprintf(SSSS, "%s", cropsystem[LandOrder]);
#else
	sprintf(SSSS, "%s", cropsystem[LandOrder]);
#endif
	

	char FREGION[200];
	sprintf(FREGION, "%s", f_region[FFN]);

	FfFf = fopen(FREGION, "a"); 
	if(FfFf==NULL) note(0,FREGION);

	float cc1=0.0, cc2=0.0;	
	if(crop_days[1]>0) 
	{
		cc1 = crop_water_stress[1]/(float)crop_days[1];
		cc2 = crop_N_stress[1]/(float)crop_days[1];
	}
	
	Soil_dCO2 = yr_addmc+yr_addtc+yr_addrc-net_SOC-yr_ch4;
	if(yr_dSIN>=0.0) BalanceN = yr_dSIN;
	else BalanceN = 0.0;

	if(DroughtID==0)
	fprintf(FfFf, "%8d , %-8s , %-11s , %8.0f , %12d , ", CountyIDX, cropping_system, SSSS, ha, year);
	else
	fprintf(FfFf, "%8d , %-8s , %-11s , %8.0f , %-12s , ", CountyIDX, cropping_system, SSSS, ha, DWM[drc]);

	fprintf(FfFf, "%8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , ", 
		EndStub, layerc[1], layerc[2],layerc[3],layerc[4],layerc[5],EndSOC, yr_addmc, yr_addtc+yr_addrc, Soil_dCO2, net_SOC);//+yr_InputRoot_DOC, yr_soil_co2
	
	fprintf(FfFf, "%8d , %8d , %8d , ", 
		crop_ID[1], crop_ID[2], crop_ID[3]);
	fprintf(FfFf, "%8.0f , %8.0f , %8.0f , ", 
		YrG_grain[1], YrG_grain[2], YrG_grain[3]);
	fprintf(FfFf, "%8.0f , %8.0f , %8.0f , ", 
		YrG_leaf[1]+YrG_stem[1],YrG_leaf[2]+YrG_stem[2],YrG_leaf[3]+YrG_stem[3]);
	fprintf(FfFf, "%8.0f , %8.0f , %8.0f , ", 
		YrG_root[1],YrG_root[2],YrG_root[3]);
	fprintf(FfFf, "%8.2f, ", yr_ch4);	
	fprintf(FfFf, "%8.3f , %8.3f , %8.3f , %8.3f , %8.3f , %8.3f , ", 
		yr_dnn2o, yr_dnno, yr_dnn2, yr_soil_nh3, yr_indirect_n2o, yr_indirect_n2);
	fprintf(FfFf, "%8.2f , %8.2f , %8.2f , %8.2f , %8.2f , ", 
		yr_plantn[1]+yr_plantn[2]+yr_plantn[3], yr_leach_NO3+yr_leach_urea+yr_leach_un,  yr_runoff_N, yr_rainN, yr_fixn[1]+yr_fixn[2]+yr_fixn[3]);
	fprintf(FfFf, "%8.2f , %8.2f , %8.2f , %8.2f , %8.2f , %8.2f , %8.0f , ", 
		yr_minern, yr_addfer, yr_addmn, yr_sln, yr_dSON,  yr_dSIN, yr_trans*1000.0);
	fprintf(FfFf, "%8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.2f , %8s , ", 
		yr_total_ev*1000.0, yr_runoff*1000.0, yr_leach_water*1000.0, yr_irri*1000.0, yr_rain*1000.0, yr_dSoilWater*1000.0, yr_avetj, country_ID);
	fprintf(FfFf, "%8.2f , %8.2f , %8.2f , ", cc1, cc2, TDD[1]/max_TDD[1]);

#ifdef MANURE
	fprintf(FfFf, "%8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , %8.0f , ", 
		MData.yr_LOS_ch4, MData.yr_LOS_n2o, MData.yr_LOS_nh3, 
		MData.yr_LOS_LeachN+MData.yr_runoff_MIN[4], MData.yr_runoff_MON[4],
		MData.yr_Compost_to_field_C+MData.yr_Lagoon_to_field_C+MData.yr_digester_to_field_C,  
		MData.yr_Compost_to_field_N+MData.yr_Lagoon_to_field_N+MData.yr_digester_to_field_N);

#endif
#ifdef HYDRO
	fprintf(FfFf, "%8.2f , %8.2f , %8.2f , %8.2f , %8.2f , %8.2f , %8.2f , %8.2f , %8.2f , ", 
		yr_muslerunoff, yr_muslesedyld, yr_muslesoc, yr_musleson, yr_muslenh4, 
		yr_musleno3,yr_muslenh3,yr_musleurea,yr_musleclayn);

#endif
	fprintf(FfFf, "\n");
	fclose(FfFf);

	if(DroughtID==1&&IrriType==0&&year==2)
	{
		FILE* DYY;
		DYY = fopen(DroughtYield, "a"); 
		if(DYY==NULL) note(0,DroughtYield);

		if(drc==1) fprintf(DYY, "\n%8d, ", CountyIDX);		
		fprintf(DYY, "%8.0f, ", (YrG_grain[1])*2.5);
		
		fclose(DYY);
	}

	if(DroughtID==1&&IrriType==1&&year==2)
	{
		FILE* DYY;
		DYY = fopen(DroughtYield, "a"); 
		if(DYY==NULL) note(0,DroughtYield);
			
		fprintf(DYY, "%8.0f, %8.0f, ", yr_rain*1000.0, yr_irri*1000.0);
		//if(drc==3) fprintf(DYY, "\n");

		fclose(DYY);
	}	
}
