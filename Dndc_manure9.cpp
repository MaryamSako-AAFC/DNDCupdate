#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <stdio.h>

#ifdef MANURE 
extern class_manure MData;

float HouseOCin, HouseOCout, HouseONin, HouseONout, HouseINin, HouseINout;
float CompostOCin, CompostOCout, CompostONin, CompostONout, CompostINin, CompostINout;
float LagoonOCin, LagoonOCout, LagoonONin, LagoonONout, LagoonINin, LagoonINout;
float FieldOCin, FieldOCout, FieldONin, FieldONout, FieldINin, FieldINout;
CString AniName[7]={"","Dairy","Beef","Veal","Pig","Sheep","Poultry"};
float w1;

void class_manure::write_out_dayFarmCN(FILE *ffarmC, int jday, char *site, int year, int m_unit)
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

/*#ifdef DEGUI
	if (jday==1)
    {
		fprintf(ffarmC, "Daily C and N fluxes for farm %s in year %d\n", site, year);
		if(m_unit==0) fprintf(ffarmC, "Units: kg C or N per farm\n\n");
		else fprintf(ffarmC, "Units: lb C or N per farm\n\n");

		fprintf(ffarmC, "Day Intake-C Milk-C Meat-C Respiration-CO2 Enteric-CH4 Dung-C Urine-C Intake-N Milk-N Meat-N Enteric-N2O Dung-N Urine-N   Intake-P Milk-P Meat-P Dung-P Urine-P \n");
   	}
	fprintf(ffarmC, "%3d ", jday);
	fprintf(ffarmC, "%7.2f %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f ", MData.day_intake_C*w1, MData.day_milk_C*w1, MData.day_meat_C*w1, MData.animal_co2*w1, 
		(MData.DAY_enteric_ch4[1]+MData.DAY_enteric_ch4[2]+MData.DAY_enteric_ch4[3])*w1, (MData.mm_DungC[1]+MData.mm_DungC[2]+MData.mm_DungC[3])*w1, 
		(MData.mm_UrineC[1]+MData.mm_UrineC[2]+MData.mm_UrineC[3])*w1); 
	fprintf(ffarmC, "%7.2f %7.2f %7.2f %7.4f %7.2f %7.2f ", MData.day_intake_N*w1, MData.day_milk_N*w1, MData.day_meat_N*w1, 
		(MData.DAY_enteric_n2o[1]+MData.DAY_enteric_n2o[2]+MData.DAY_enteric_n2o[3])*w1, 
		(MData.mm_DungN[1]+MData.mm_DungN[2]+MData.mm_DungN[3])*w1, (MData.mm_UrineN[1]+MData.mm_UrineN[2]+MData.mm_UrineN[3])*w1);
	fprintf(ffarmC, "%7.2f %7.2f %7.2f %7.2f %7.2f\n", MData.day_intake_P*w1, MData.day_milk_P*w1, MData.day_meat_P*w1, 
		(MData.mm_DungP[1]+MData.mm_DungP[2]+MData.mm_DungP[3])*w1, (MData.mm_UrineP[1]+MData.mm_UrineP[2]+MData.mm_UrineP[3])*w1);


#else*/
	if (jday==1)
    {
		fprintf(ffarmC, "Daily C and N fluxes for farm %s in year %d\n", site, year);
		if(m_unit==0) fprintf(ffarmC, "Units: kg C or N per farm\n\n");
		else fprintf(ffarmC, "Units: lb C or N per farm\n\n");

		fprintf(ffarmC, "Day,Intake-C,Milk-C,Meat-C,Respiration-CO2,Enteric-CH4,Dung-C,Urine-C,Intake-N,Milk-N,Meat-N,Enteric-N2O,Dung-N,Urine-N,  Intake-P,Milk-P,Meat-P,Dung-P,Urine-P,\n");
   	}
	fprintf(ffarmC, "%3d,", jday);
	fprintf(ffarmC, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", MData.day_intake_C*w1, MData.day_milk_C*w1, MData.day_meat_C*w1, MData.animal_co2*w1, 
		(MData.DAY_enteric_ch4[1]+MData.DAY_enteric_ch4[2]+MData.DAY_enteric_ch4[3])*w1, (MData.mm_DungC[1]+MData.mm_DungC[2]+MData.mm_DungC[3])*w1, 
		(MData.mm_UrineC[1]+MData.mm_UrineC[2]+MData.mm_UrineC[3])*w1); 
	fprintf(ffarmC, "%7.2f,%7.2f,%7.2f,%7.4f,%7.2f,%7.2f,", MData.day_intake_N*w1, MData.day_milk_N*w1, MData.day_meat_N*w1, 
		(MData.DAY_enteric_n2o[1]+MData.DAY_enteric_n2o[2]+MData.DAY_enteric_n2o[3])*w1, 
		(MData.mm_DungN[1]+MData.mm_DungN[2]+MData.mm_DungN[3])*w1, (MData.mm_UrineN[1]+MData.mm_UrineN[2]+MData.mm_UrineN[3])*w1);
	fprintf(ffarmC, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n", MData.day_intake_P*w1, MData.day_milk_P*w1, MData.day_meat_P*w1, 
		(MData.mm_DungP[1]+MData.mm_DungP[2]+MData.mm_DungP[3])*w1, (MData.mm_UrineP[1]+MData.mm_UrineP[2]+MData.mm_UrineP[3])*w1);
//#endif 				   
}

void class_manure::write_out_dayFarmManureRemove(FILE *ffarmMR, int jday, char *site, int year, int m_unit)
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

	if (jday==1)
    {
		fprintf(ffarmMR, "Daily manure removal from feedlot to storage/treatment for farm %s in year %d\n", site, year);
		if(m_unit==0) fprintf(ffarmMR, "Units: kg C or N per day\n\n");
		else fprintf(ffarmMR, "Units: lb C or N per day\n\n");
		fprintf(ffarmMR, "Day,to_compost-C,to_compost-N,to_compost-P,to_compost-H2O,to_lagoon-C,to_lagoon-N,to_lagoon-P,to_lagoon-H2O,to_digester-C,to_digester-N,to_digester-P,to_digester-H2O,to_field-C,to_field-N,to_field-P,to_field-H2O,\n");
   	}
	fprintf(ffarmMR, "%3d,", jday);
	fprintf(ffarmMR, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n",
		MData.House_to_compost_C, MData.House_to_compost_N, MData.House_to_compost_P, MData.House_to_compost_H2O,
		MData.House_to_lagoon_C, MData.House_to_lagoon_N, MData.House_to_lagoon_P, MData.House_to_lagoon_H2O,
		MData.House_to_digester_C, MData.House_to_digester_N, MData.House_to_digester_P, MData.House_to_digester_H2O,
		MData.House_to_field_C, MData.House_to_field_N, MData.House_to_field_P, MData.House_to_field_H2O);

}

void class_manure::write_dayManureProduction(FILE *fhouse, int FN, int GN, int jday, char*site, int year, float *soc, float *doc,
			float *son, float *urea, float *nh4, float *no3, float *temp, float *day_wfps, float *sph, 
			double water[25][250], int q, float *sop, int m_unit, float *Eh, float pen_soil_wfps)
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

	int FC=FN;

	if (jday==1)
    {
    fprintf(fhouse, "Daily manure biogeochemistry in feedlot at %s in year %d\n", site, year);

	fprintf(fhouse, "Units: per feedlot\n\n");
	fprintf(fhouse, "Day,AnimalType,Heads,Milk,MeatGain,FecesC,UrineC,BeddingC,Floor-CO2,Floor-CH4,Floor_RunoffC,Floor-MOC,Floor-DOC,Removed_C,FecesN,UrineN,BeddingN,Floor-NH3,Floor-N2O,Floor-MON,Floor-urea,Floor-NH4,Floor-NO3,Floor_Runoff_N,Removed_N,FecesP,UrineP,ManureP,Removed_P,Feedlot_runoff_P,FecesH2O,UrineH2O,FlushH2O,FloorEV,Floor_H2O,Floor_runoffH2O, Removed_H2O,Floor_mois, Floor-temp, Floor-pH,Floor-Eh,floor-leach-water,floor-leach-urea,floor-leach-NH4,floor-leach-NO3,floor-leach-DOC\n");
    if(m_unit==0) fprintf(fhouse, "   ,          ,     ,kg  ,kg DM   ,kgC   ,kgC   ,kgC      ,kgC      ,kgC      ,kgC      ,kgC,kgC         ,kgC        ,kgN   ,kgN   ,kgN     ,kgN     ,kgN      ,kgN      ,kgN         ,kgN          ,kgN      ,kgN         ,kgN     ,kgP   ,kgP   ,kgP    ,kgP ,kgP ,kgWater,kgWater ,kgWater ,kgWater,kgWater,kgWater,kgWater,WFPS, degreeC,,mV,kgWater,kgN,kgN,kgN,kgC\n\n");
	else fprintf(fhouse, "   ,          ,     ,lb  ,lb      ,lbC   ,lbC   ,lbC      ,lbC      ,lbC      ,lbC ,lbC     ,lbC      ,lbC         ,lbC          ,lbN   ,lbN   ,lbN     ,lbN      ,lbN      ,lbN         ,lbP   ,lbP         ,lbP        ,lbP ,lbP         ,lbWater ,lbWater ,lbWater,lbWater       ,lbWater      ,lbWater     ,          ,WFPS    ,\n\n");
	}
	fprintf(fhouse, "%3d,%3d,%7.2f,%7.2f,%7.2f,", 
		jday, MData.mm_AnimalType[FC], MData.mm_AnimalHeads[FC], MData.day_milk_product*w1, MData.mm_MeatProduct[FC]*MData.mm_AnimalHeads[FC]);

	fprintf(fhouse, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",
		MData.mm_DungC[FC]*w1, MData.mm_UrineC[FC]*w1, MData.day_bed_C*w1, 
		MData.day_house_co2*w1, //MData.day_gutter_co2*w1, 
		MData.day_house_ch4*w1, //MData.day_gutter_ch4*w1, 
		MData.day_runoff_MC[FC],
		soc[GN]*w1, //soc[q+8]*w1, 
		doc[GN]*w1, //doc[q+8]*w1, 
		MData.House_floor_removedC*w1);	 
	
	fprintf(fhouse, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.4f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",
		MData.mm_DungN[FC]*w1, MData.mm_UrineN[FC]*w1, MData.day_bed_N*w1, MData.day_house_nh3*w1, MData.day_house_n2o*w1, 
		son[GN]*w1, urea[GN]*w1, nh4[GN]*w1, no3[GN]*w1, MData.day_runoff_MON[FC]+MData.day_runoff_MIN[FC],
		MData.House_floor_removedN*w1);

	fprintf(fhouse, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",
		MData.mm_DungP[FC]*w1, MData.mm_UrineP[FC]*w1, (sop[GN]+sop[q+8])*w1, 
		MData.House_floor_removedP*w1,
		MData.day_runoff_MOP[FC]);
	
	fprintf(fhouse, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", 
		MData.mm_DungWater[FC]*w1, MData.mm_UrineWater[FC]*w1, MData.m_FlushWater[FC] * 1000.0*w1, MData.day_house_evap*w1, 
		water[1][GN]*w1, MData.day_feedlot_runoff_WATER, MData.House_floor_removedH2O*w1,		
		day_wfps[GN], temp[GN],  sph[GN], Eh[GN]);
	fprintf(fhouse, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n", 
		MData.day_floor_leach_water, MData.day_floor_leach_urea, MData.day_floor_leach_NH4, MData.day_floor_leach_NO3, MData.day_floor_leach_doc); 
				 
}


void class_manure::write_out_dayCompost(FILE *fcompost, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float *sop, int m_unit)
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

	int GN=q+4, MK=4;
	//float input_C = MData.House_to_compost_C;
	//float input_N = MData.House_to_compost_N;
	//float input_H2O = MData.House_to_compost_H2O + MData.day_compost_InRain;
	//float input_P = MData.House_to_compost_P;
/*#ifdef DEGUI
	if (jday==1)
    {
		fprintf(fcompost, "Daily compost C and N dynamics at %s in year %d\n", site, year);
		fprintf(fcompost, "Unit: per compost\n\n");
		fprintf(fcompost, "Day Temperature Moisture CO2-flux CH4-flux Runoff_C MOC-pool Removed_C  NH3-flux N2O-flux NO-flux N2-flux Runoff_N MON-pool Urea-pool NH4-pool NO3-pool NH3-pool Removed_N  Evaporation Water-leach Water-pool Removed_water  Compost_P Compost_removed_P\n");
		if(m_unit==0) fprintf(fcompost, "   kgC kgC kgC kgC kgC  kgN kgN kgN kgN kgN kgN kgN kgN kgN kgN kgN  kgWater kgWater kgWater kgWater  kgP kgP\n\n");
   		else fprintf(fcompost, "   lbC lbC lbC lbC lbC lbC  lbN lbN lbN lbN lbN lbN lbN lbN lbN lbN lbN  lb lb lb lb  lbP lbP\n\n");
 
	}
	fprintf(fcompost, "%3d %7.2f %7.2f ",jday, temp[GN], day_wfps[GN]);
	fprintf(fcompost, "%7.2f %7.4f %7.2f %7.2f %7.2f  ",MData.day_compost_co2*w1, MData.day_compost_ch4*w1, MData.day_runoff_MC[MK]*w1,soc[GN]*w1, 
		MData.Compost_to_field_C*w1);
	fprintf(fcompost, "%7.2f %7.2f %7.2f %7.2f %7.2f %7.0f %7.2f %7.2f %7.2f %7.2f %7.2f  ", MData.day_Compost_nh3*w1,
		MData.day_compost_n2o*w1,MData.day_compost_no*w1,MData.day_compost_n2*w1,
		(MData.day_runoff_MIN[MK] + MData.day_runoff_MON[MK] + MData.day_LOS_LeachN)*w1,
		son[GN]*w1,urea[GN]*w1,nh4[GN]*w1,no3[GN]*w1,nh3[GN]*w1, 
		MData.Compost_to_field_N*w1);
	fprintf(fcompost, "%7.0f %7.0f %7.0f %7.0f  ", MData.day_compost_EV*w1, (MData.day_compost_leach_H2O+MData.day_compost_runoff_WATER)*w1,
		water[1][GN]*w1, MData.Compost_to_field_H2O*w1);
	fprintf(fcompost, "%7.2f %7.2f\n", sop[GN]*w1, MData.Compost_to_field_P*w1);


#else*/
	if (jday==1)
    {
		fprintf(fcompost, "Daily compost C and N dynamics at %s in year %d\n", site, year);
		fprintf(fcompost, "Unit: per compost\n\n");
		fprintf(fcompost, "Day,Temperature,Moisture,CO2-flux,CH4-flux,Runoff_C,MOC-pool,Removed_C,N_input,NH3-flux,N2O-flux,NO-flux,N2-flux,Runoff_N,Leach_N,MON-pool,Urea-pool,NH4-pool,NO3-pool,NH3-pool,Removed_N,,Evaporation,Water-leach,Water-runoff,Water-pool,Removed_water,,Compost_P,Compost_removed_P\n");
		if(m_unit==0) fprintf(fcompost, ",,,kgC,kgC,kgC,kgC,kgC,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,,kgWater,kgWater,kgWater,kgWater,kgWater,,kgP,kgP\n\n");
   		else fprintf(fcompost, ",,,lbC,lbC,lbC,lbC,lbC,lbC,,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,,lb,lb,lb,lb,lb,lbP,lbP\n\n");
 
	}
	fprintf(fcompost, "%3d,%7.2f,%7.2f,",jday, temp[GN], day_wfps[GN]);
	fprintf(fcompost, "%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,",MData.day_compost_co2*w1, MData.day_compost_ch4*w1, MData.day_runoff_MC[MK]*w1,soc[GN]*w1, 
		MData.Compost_to_field_C*w1);
	fprintf(fcompost, "%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.0f,%7.0f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,,", 
		MData.House_to_compost_N*w1,MData.day_Compost_nh3*w1,
		MData.day_compost_n2o*w1,MData.day_compost_no*w1,MData.day_compost_n2*w1,
		(MData.day_runoff_MIN[MK]+MData.day_runoff_MON[MK])*w1, MData.day_LOS_LeachN*w1,
		son[GN]*w1,urea[GN]*w1,nh4[GN]*w1,no3[GN]*w1,nh3[GN]*w1, 
		MData.Compost_to_field_N*w1);
	fprintf(fcompost, "%7.0f,%7.0f,%7.0f,%7.0f,%7.0f,,", MData.day_compost_EV*w1, MData.day_compost_leach_H2O*w1, MData.day_compost_runoff_WATER*w1,
		water[1][GN]*w1, MData.Compost_to_field_H2O*w1);
	fprintf(fcompost, "%7.4f,%7.4f\n", sop[GN]*w1, MData.Compost_to_field_P*w1);
//#endif	
}

void class_manure::write_out_dayLagoon(FILE *flagoon, int jday, float lagoon_temp, float *nh4, float *no3, float *nh3, 
									   float *son, float *urea, char *site, int year, int q, float *soc, 
									   double water[25][250], float *no2, float *no, float *n2o, float *n2, float *sop,
									   int m_unit, float *doc, float *LagoonT, float air_temp, float *lagoon_snowpack, float lagoon_ice[21])
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

	float input_C = MData.House_to_lagoon_C;
	float input_N = MData.House_to_lagoon_N;
	float input_H2O = MData.House_to_lagoon_H2O;
	float input_P = MData.House_to_lagoon_P;

	float lagoon_N = son[q+5]+urea[q+5]+nh4[q+5]+no3[q+5]+nh3[q+5]+no2[q+5]+no[q+5]+n2o[q+5];
	float total_lagoon_ice = 0.0;

	total_lagoon_ice = lagoon_ice[1];
	float dayLagoonEvap = MData.day_lagoon_EV / (MData.m_LagoonSurfaceArea * 1000.0)*1000.0; 
	if (jday == 1)
	{
		fprintf(flagoon, "Daily lagoon/slurry C and N dynamics at %s in year %d\n", site, year);
		fprintf(flagoon, "Unit: per lagoon\n\n");
		fprintf(flagoon, "Day,T_air,Lagoon_ice,snowpackcm,T_1cm,T_10cm,T_20cm,T_30cm,T_40cm,T_50cm,T_60cm,T_70cm,T_80cm,T_90cm,T_100cm,T_110cm,T_120cm,T_130cm,T_140cm,T_150cm,T_160cm,T_170cm,T_180cm,T_190cm,T_200cm,C_input,CO2-flux,CH4-flux,Removed_C,C-pool,DOC-pool,N_input,NH3-flux,N2O-flux,NO-flux,N2-flux,Removed_N,N_pool,MON-pool,Urea-pool,NH4-pool,NO3-pool,NH3-pool,NO2-pool,NO-pool,N2O-pool,N2-pool,Water_input,Evaporation,water_to_field,Water-pool,P_input,P_to_field,P_pool,Crust-C,LagoonFieldMth,LagoonFieldDepth,mmEvap\n");
		if (m_unit == 0) fprintf(flagoon, ",,,,,,,,,,,,,,,,,,,,,,,,,kgC,kgC,kgC,kgC,kgC,kgC,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgWater,kgWater,kgWater,kgWater,kgP,kgP,kgP, kgC\n\n");
		else fprintf(flagoon, ",,,,,,,,,,,,,,,,,,,,,,,,,lbC,lbC,lbC,lbC,,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,,lb,lb,lb,,lbP,lbP,lbC\n\n");

	}
	fprintf(flagoon, "%3d,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", jday, air_temp, total_lagoon_ice, *lagoon_snowpack * 100, MData.LagoonT[1], MData.LagoonT[2], MData.LagoonT[3], MData.LagoonT[4], MData.LagoonT[5], MData.LagoonT[6], MData.LagoonT[7], MData.LagoonT[8], MData.LagoonT[9], MData.LagoonT[10], MData.LagoonT[11], MData.LagoonT[12], MData.LagoonT[13], MData.LagoonT[14], MData.LagoonT[15], MData.LagoonT[16], MData.LagoonT[17], MData.LagoonT[18], MData.LagoonT[19], MData.LagoonT[20], MData.LagoonT[21]);//lagoon_temp
	fprintf(flagoon, "%7.4f,%7.4f,%7.4f,%7.2f,%7.2f,%7.2f,",
		MData.House_to_lagoon_C + MData.Digester_to_lagoon_C, MData.day_lagoon_co2 * w1, MData.day_lagoon_ch4 * w1, MData.Lagoon_to_field_C * w1, soc[q + 5] * w1, doc[q + 5] * w1);//day_lagoon_co2,
	fprintf(flagoon, "%7.4f,%7.4f,%7.5f,%7.5f,%7.5f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",
		MData.House_to_lagoon_N + MData.Digester_to_lagoon_N, MData.day_lagoon_nh3 * w1, MData.day_lagoon_n2o * w1, MData.day_lagoon_no * w1, MData.day_lagoon_n2 * w1, MData.Lagoon_to_field_N * w1, lagoon_N * w1, son[q + 5] * w1,
		urea[q + 5] * w1, nh4[q + 5] * w1, no3[q + 5] * w1, nh3[q + 5] * w1, no2[q + 5] * w1, no[q + 5] * w1, n2o[q + 5] * w1, n2[q + 5] * w1);
	fprintf(flagoon, "%7.2f,%7.2f,%7.2f,%7.2f,", MData.House_to_lagoon_H2O + MData.Digester_to_lagoon_H2O, MData.day_lagoon_EV * w1, MData.Lagoon_to_field_H2O * w1, water[1][q + 5] * w1);
	fprintf(flagoon, "%7.2f,%7.2f,%7.2f,%7.2f,", MData.House_to_lagoon_P + MData.Digester_to_lagoon_P, MData.Lagoon_to_field_P * w1, sop[q + 5] * w1, MData.LagoonCrustC * w1);

	fprintf(flagoon, "%7d,%7.2f,%7.2f\n", MData.LagoonFieldAplMethod, MData.LagoonFieldAplDepth,dayLagoonEvap);
	/*

	if (jday==1)
    {
		fprintf(flagoon, "Daily lagoon/slurry C and N dynamics at %s in year %d\n", site, year);
		fprintf(flagoon, "Unit: per lagoon\n\n");
		fprintf(flagoon, "Day,T_air,T_1cm,T_20cm,T_40cm,T_60cm,T_80cm,C_input,CO2-flux,CH4-flux,Removed_C,TotalC-pool,DOC-pool,N_input,NH3-flux,N2O-flux,NO-flux,N2-flux,Removed_N,N_pool,MON-pool,Urea-pool,NH4-pool,NO3-pool,NH3-pool,NO2-pool,NO-pool,N2O-pool,N2-pool,Water_input,Evaporation,water_to_field,Water-pool,P_input,P_to_field,P_pool,Crust-C,SlurryAplMethod,SlurryAplDepth\n");
		if(m_unit==0) fprintf(flagoon, ",,,,,,,kgC,kgC,kgC,kgC,kgC,kgC,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgWater,kgWater,kgWater,kgWater,kgP,kgP,kgP, kgC,,cm\n\n");
   		else fprintf(flagoon, ",,,lbC,lbC,lbC,lbC,,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,,lb,lb,lb,,lbP,lbP,lbC\n\n");

	}
	fprintf(flagoon, "%3d,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",jday, lagoon_temp, MData.LagoonT[1], MData.LagoonT[2], MData.LagoonT[3], MData.LagoonT[4], MData.LagoonT[5]);
	fprintf(flagoon, "%7.4f,%7.4f,%7.4f,%7.2f,%7.2f,%7.2f,",
		MData.House_to_lagoon_C+MData.Digester_to_lagoon_C,MData.day_lagoon_co2*w1, MData.day_lagoon_ch4*w1, MData.Lagoon_to_field_C*w1, soc[q+5]*w1, doc[q+5]*w1);//day_lagoon_co2,
	fprintf(flagoon, "%7.4f,%7.4f,%7.5f,%7.5f,%7.5f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", 
		MData.House_to_lagoon_N+MData.Digester_to_lagoon_N, MData.day_lagoon_nh3*w1,MData.day_lagoon_n2o*w1,MData.day_lagoon_no*w1,MData.day_lagoon_n2*w1,MData.Lagoon_to_field_N*w1, lagoon_N*w1,son[q+5]*w1,
		urea[q+5]*w1,nh4[q+5]*w1,no3[q+5]*w1,nh3[q+5]*w1, no2[q+5]*w1, no[q+5]*w1, n2o[q+5]*w1, n2[q+5]*w1);
	fprintf(flagoon, "%7.2f,%7.2f,%7.2f,%7.2f,", MData.House_to_lagoon_H2O+MData.Digester_to_lagoon_H2O,MData.day_lagoon_EV*w1, MData.Lagoon_to_field_H2O*w1, water[1][q+5]*w1);
	fprintf(flagoon, "%7.2f,%7.2f,%7.2f,%7.2f,", MData.House_to_lagoon_P+MData.Digester_to_lagoon_P,MData.Lagoon_to_field_P*w1, sop[q+5]*w1,MData.LagoonCrustC*w1);

	fprintf(flagoon, "%7d,%7.2f\n", MData.LagoonFieldAplMethod, MData.LagoonFieldAplDepth);
	*/
}

void class_manure::write_out_dayDigester(FILE *fdigester, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float *sop, int m_unit,
				float *no2, float *no, float *n2o, float ttn)
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

	int GN=q+6;
	float input_C = MData.House_to_digester_C;
	float input_N = MData.House_to_digester_N;
	float input_H2O = MData.House_to_digester_H2O;
	float input_P = MData.House_to_digester_P;

	//float digester_N = son[q+6]+urea[q+6]+nh4[q+6]+no3[q+6]+nh3[q+6]+no2[q+6]+no[q+6]+n2o[q+6];

	if (jday==1)
    {
		fprintf(fdigester, "Daily digester C and N dynamics at %s in year %d\n", site, year);
		fprintf(fdigester, "Unit: per digester\n\n");
		fprintf(fdigester, "Day,Temperature,C_input,CO2-flux,CH4-flux,To_field_C,To_lagoon_C,C_pool,N_input,NH3-flux,N2O-flux,NO-flux,N2-flux,To_field_N,To_lagoon_N,N_pool,MON-pool,Urea-pool,NH4-pool,NO3-pool,NH3-pool,Water_input,To_field_water,To_lagoon_water,Water-pool,P_input,To_field_P,To_lagoon_P,P_pool\n");
		if(m_unit==0) fprintf(fdigester, ",,kgC,kgC,kgC,kgC,kgC,kgC,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgN,kgWater,kgWater,kgWater,kgWater,kgP,kgP,kgP,kgP\n\n");
   		else fprintf(fdigester, ",,,lbC,lbC,lbC,lbC,lbC,,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,lbN,,lb,lb,lb,lb,lb,,lbP,lbP,lbP\n\n");

	}
	fprintf(fdigester, "%3d,%7.2f,",jday, temp[GN]);
	fprintf(fdigester, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",MData.House_to_digester_C*w1,MData.day_digester_CO2*w1, MData.day_digester_CH4*w1, 
		MData.Digester_to_field_C*w1, MData.Digester_to_lagoon_C*w1,MData.ttc*w1);
	fprintf(fdigester, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", 
		MData.House_to_digester_N*w1, MData.day_digester_nh3*w1,MData.day_digester_n2o*w1,MData.day_digester_no*w1,
		MData.day_digester_n2*w1,MData.Digester_to_field_N*w1, MData.Digester_to_lagoon_N*w1, 
		ttn*w1, son[GN]*w1,urea[GN]*w1,nh4[GN]*w1,no3[GN]*w1,nh3[GN]*w1);
	fprintf(fdigester, "%7.2f,%7.2f,%7.2f,%7.2f,", MData.House_to_digester_H2O*w1,MData.Digester_to_field_H2O*w1,MData.Digester_to_lagoon_H2O*w1, water[1][GN]*w1);
	fprintf(fdigester, "%7.2f,%7.2f,%7.2f,%7.2f\n", MData.House_to_digester_P*w1,MData.Digester_to_field_P*w1, MData.Digester_to_lagoon_P*w1,sop[GN]*w1);

}

void class_manure::write_out_dayTreatmentGas(FILE *ffarmgas, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float day_soil_nh3, float day_vol_nh3, 
				float day_soil_an_n2o, float *sop, int m_unit)
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

	int i, j;
/*	MData.enteric_ch4=0.0;
	MData.enteric_n2o=0.0;
	for(j=1;j<=3; j++)
	{
		MData.enteric_ch4 += MData.day_enteric_ch4[j];
		MData.enteric_n2o += MData.day_enteric_n2o[j];
	}
*/	
/*#ifdef DEGUI
	if (jday==1)
    {
		fprintf(ffarmgas, "Daily gas emissions from treatments %s in year %d\n", site, year);
		if(m_unit==0) fprintf(ffarmgas, "Units: kg N or C per farm\n\n");
		else fprintf(ffarmgas, "Units: lb N or C per farm\n\n");	
		fprintf(ffarmgas, "Day NH3 N2O CH4\n");
   	}
	fprintf(ffarmgas, "%3d ", jday);
	fprintf(ffarmgas, "%7.2f %7.2f %7.2f\n",
		            (MData.day_Compost_nh3+MData.day_lagoon_nh3)*w1,
					(MData.day_compost_n2o+MData.day_lagoon_n2o)*w1,
					(MData.day_compost_ch4+MData.day_lagoon_ch4)*w1);

#else*/
	if (jday==1)
    {
		fprintf(ffarmgas, "Daily gas emissions from treatments %s in year %d\n", site, year);
		if(m_unit==0) fprintf(ffarmgas, "Units: kg N or C per farm\n\n");
		else fprintf(ffarmgas, "Units: lb N or C per farm\n\n");	
		fprintf(ffarmgas, "Day,Compost-NH3,Compost-N2O,Compost-CH4,Lagoon-NH3,Lagoon-N2O,Lagoon-CH4,Digester-NH3,Digester-N2O,Digester-CH4\n");
   	}
	fprintf(ffarmgas, "%3d,", jday);
	fprintf(ffarmgas, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n",
		            MData.day_Compost_nh3*w1,MData.day_compost_n2o*w1,MData.day_compost_ch4,
					MData.day_lagoon_nh3,MData.day_lagoon_n2o*w1,MData.day_lagoon_ch4*w1,
					MData.day_digester_nh3*w1, MData.day_digester_n2o*w1, MData.day_digester_CH4*w1);//; 		
//#endif					   				   
}

void class_manure::write_out_dayFeedlotGas(FILE *ffarmgas, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float day_soil_nh3, float day_vol_nh3, 
				float day_soil_an_n2o, float *sop, int m_unit)
{
	if(m_unit==0) w1=1.0;
	else w1=1.0/lb_kg;

	int i, j;
	MData.enteric_ch4=0.0;
	MData.enteric_n2o=0.0;
	for(j=1;j<=3; j++)
	{
		MData.enteric_ch4 += MData.day_enteric_ch4[j];
		MData.enteric_n2o += MData.day_enteric_n2o[j];
	}

	if (jday==1)
    {
		fprintf(ffarmgas, "Daily gas emissions from feedlot %s in year %d\n", site, year);
		if(m_unit==0) fprintf(ffarmgas, "Units: kg N or C per farm\n\n");
		else fprintf(ffarmgas, "Units: lb N or C per farm\n\n");	
		fprintf(ffarmgas, "Day,floor_NH3,gutter_NH3,enteric_N2O,floor_N2O,gutter_N2O,enteric_CH4, floor_CH4, gutter_CH4, floor_CO2, gutter_CO2, animal_CO2\n");
   	}
	fprintf(ffarmgas, "%3d,", jday);
	fprintf(ffarmgas, "%7.5f,%7.5f,%7.5f,%7.5f,%7.5f,%7.5f,%7.5f,%7.5f,%7.5f,%7.5f,%7.5f\n",
		            MData.day_house_nh3*w1, MData.day_gutter_nh3*w1,
					MData.enteric_n2o*w1, MData.day_house_n2o*w1, MData.day_gutter_n2o*w1,
					MData.enteric_ch4*w1, MData.day_house_ch4*w1, MData.day_gutter_ch4*w1,
					MData.day_house_co2*w1, MData.day_gutter_co2*w1,MData.animal_co2*w1);//; 		
//#endif					   				   
}

#endif