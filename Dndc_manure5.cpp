#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;
extern class_model *DNDC;

float day_compost_Ngas;

void class_manure::compost_BGC(int FN, int GN, 
		int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float *urea, float *doc,
		float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, 
		float DayPET, float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, int WTL, float day_WT, 
		float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, float rcnm, float *son, float *SIN, float *no3, float *no2, 
		float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, float *w_no2, float *w_nh3, 
		float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, int tilq, 
		FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, float WaterLeakRate,
		float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, float *ocini,
		float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim, float DClitter,
		float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, 
		float day_runoff, float *day_runoff_N, float *day_clay_N, 
		float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, float *ds_doc, int *crop, float *yr_fixn,
		float till_fact, float *sts, float rainfall, float *O2_old, float *O2, float *vvv, float *ave_anvf,
		int year, double water[25][250], float total_ice, float *day_rco2, int flo_num, float *Eh,
		float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, float *Tttoo, 
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, 
		float *assim2, float *fldcap, float by_passf, int NIDay1, int NIDay2,
		float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *wiltpt, float *day_frostDOC, float *yr_frostDOC,
		float *winertC, float *inert_C, int fert_flag, float *root_doc,  
		float precipitation, float manuFlag, int irri_flag, float *FreezeDOC, float *day_O2, float RFM, 
		float *SoilDepth, float *sop, float *OrgP, float *LabP, float *ComP, float *AdsP,
		float LateralInflux, int drain_flag, float day_leach_water, int CompostCover, FILE* HSM, int fertigate_flag,
		float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, int scale, float ha, 
		int livestock, float *day_nitrification, float *day_denitrification, float* manco2, float *manurePool, float manurePoolCN,float rno3, float day_inRainN, float denitMulti,float nitMulti, float N2N2OFactor,
	    int manureHour, int manureCounter, int UreaHydroInhibDays, int UIDay1, int UIDay2,  float newmanuPH, float combinedpHDeep, float NH3Vol, float *day_nitrify_n2ol,float *day_denitrify_n2ol)
{
	float F_density, HeatLoss, water_evap, dTEMP, Compost_Density;
	float compost_V, compost_porosity, compost_diffusion, compost_O2, compost_upper_area;
	float compost_mass, compost_SHC, compost_poro, max_water, manure_SW, manure_V, CompostHeatGain;
	int i;

	MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);

	//F_density = (float)log(MData.m_CompostDensity) /2.3026 / 3.0;//0-1000 kg DM/m3

	//compost mass and geometry
	manure_SW = 306.8; //manure specific weight: 25 lb/cubic foot (306.8 kg/m3)
	compost_mass = soc[GN] / 0.58; //kg DM/compost
	manure_V = compost_mass / manure_SW; //Solid volumn, m3
	vvv[GN] = manure_V;
	compost_poro = MData.m_CompostPoro;
	sph[GN] = MData.m_CompostPH;
	compost_V = manure_V / (1.0 - compost_poro);//compost volumn, m3	
	compost_upper_area = powf(compost_V, 0.3); //m2	

	Compost_Density = compost_mass / compost_V;//kg DM/m3
	F_density = (float)log(Compost_Density) /2.3026 / 3.0;//0-1000 kg DM/m3
	
	compost_diffusion = 0.0000009 * Compost_Density*Compost_Density - 0.0019*Compost_Density + 1.0405;	
	h[GN] = h[1];

	//manure moisture
	max_water = compost_V * compost_poro * 1000.0 * 0.6; //m3 -> kg water; field capacity 0.6
	if(rainfall>0.0&&CompostCover==1)//air open 
	{
		float InRain = rainfall * compost_upper_area * 1000.0;
		
		water[1][GN] += InRain; //rain water m -> kg water/day/pen
		MData.day_compost_InRain = InRain;
		MData.yr_compost_InRain += InRain;
	}

	if(CompostCover==1)//air open
		water_evap = DayPET * compost_upper_area * 1000.0 * wind_speed;//kg water/day
	else if(CompostCover==2)//sheltered
		water_evap = DayPET * compost_upper_area * 1000.0;//kg water/day
	else
		water_evap = 0.01* DayPET * compost_upper_area * 1000.0;//kg water/day

	if(water_evap>water[1][GN]*0.5) water_evap = water[1][GN] * 0.5;

	MData.day_compost_EV = water_evap;
	MData.yr_compost_EV += water_evap;//kg water
	
	water[1][GN] -= MData.day_compost_EV;	
	
	if(water[1][GN]> max_water) 
	{
		MData.day_compost_leach_H2O = water[1][GN] - max_water;
		water[1][GN] = max_water;
		MData.yr_compost_leach_H2O += MData.day_compost_leach_H2O;
	}
	
	day_wfps[GN] = water[1][GN] / max_water;//1000.0 / compost_poro;

	if(MData.day_compost_leach_H2O>0.0)
	{
		float LFF = MData.day_compost_leach_H2O / max_water;
		LFF = min(0.5, max(0.0, LFF));
		MData.day_LOS_LeachN = no3[GN] * LFF;
		no3[GN] -= MData.day_LOS_LeachN;
	}

	if(rainfall>0.0&&CompostCover==1)//air open
	{
		float RFL[24] = {0.0,0.0};
		float RunoffIndex = 0.1 * rainfall * (1.0 - F_density); 
		RunoffIndex = min(1.0, max(0.0, RunoffIndex));

		RFL[1] = rcvl[GN] * RunoffIndex;
		RFL[2] = rcl[GN] * RunoffIndex; 
		RFL[3] =  rcr[GN] * RunoffIndex; 
		RFL[4] =   CRB1[GN] * RunoffIndex; 
		RFL[5] = CRB2[GN] * RunoffIndex; 
		RFL[6] = crhl[GN] * RunoffIndex;
		RFL[7] = crhr[GN] * RunoffIndex; 
		RFL[8] = dphum[GN] * RunoffIndex; 		
		RFL[9] = nh4[GN] * RunoffIndex;
		RFL[10] = no3[GN] * RunoffIndex;
		RFL[11] = no2[GN] * RunoffIndex;
		RFL[12] = no[GN] * RunoffIndex; 
		RFL[13] = n2o[GN] * RunoffIndex;
		RFL[14] =  n2[GN] * RunoffIndex; 
		RFL[15] =  nh3[GN] * RunoffIndex; 	
		RFL[16] =  urea[GN] * RunoffIndex; 
		RFL[17] = co2[GN] * RunoffIndex;	
		RFL[18] =  doc[GN] * RunoffIndex; 
		RFL[19] = water[1][GN] * RunoffIndex; 
		RFL[20] = OrgP[GN] * RunoffIndex;
		RFL[21] = LabP[GN] * RunoffIndex;
		RFL[22] = ComP[GN] * RunoffIndex;

		ManureRunoff(FN, GN, RFL, rcnrvl, rcnrl,rcnrr,rcnb,rcnh,rcnm,
			rcvl,rcl,rcr,CRB1,CRB2,crhl,crhr,dphum,nh4,no3,no2,
			no,n2o,n2,nh3,urea,co2,doc,water,OrgP,LabP,ComP);
	}
		

	//manure Eh
	compost_porosity = 1.0 - day_wfps[GN];
	compost_O2 = 3100.8 / 10000 * compost_V * compost_porosity - 0.01 * MData.day_compost_co2;//kg O2/compost
	O2[GN] = compost_O2 * compost_diffusion / compost_mass;// kg O2/kg DM
	if(O2[GN]<0.0) O2[GN] = 0.0;
	
	Eh[GN] = O2[GN] * 1000000.0;	
	Eh[GN] = min(650.0, max(-350.0, Eh[GN]));
	if(Eh[GN] < -100.0)
	{
		*flood_flag=1;
		//flood_num=1;
	}
	else
		*flood_flag=0;


	//convert_lot_to_ha(FC, compost_upper_area);

	//manure biogeochemistry
	DNDC->dndc_decomposition(CRB1, CRB2, newh, w_no2, 
		w_nh3, w_no3, w_nh4, wurea, wpool_no, 
		1.0, DayFlux, tilq, 
		fCB, fNB, w_n2o, w_n2,
		GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, 
		SIN, rcvl, rcl, rcr, dphum, doc, nh4, no3, no2, 
		no, n2o, n2, nh3, urea, jday, co2, clay, TTT, *flood_flag,
		day_wfps, WTL, temp, LandUse, FloDays, crhl, crhr, mmm, ocini,
		h, day_C_mine, day_N_mine, day_N_assim, DClitter, 
		litco22, litco23, st, DChumads, EFFAC, DChumus, sph,
		wetland_flag, wind_speed, ice, day_soil_nh3,
		lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3,
		day_N_demand, day_nup, day_fixN, day_DWater, day_plant_nh3, yr_NH3_deposit, 
		plantn, clay_nh4, base_clay_N, max_clay_N,
		wrcvl, wrcl, wrcr, wcrb, wcrhl, wcrhr, whumus, wtcavai,
		day_ice_N, day_ice_doc, day_ice_n2o, day_ice_n2, IniSOC, IniSON, EndSON,
		day_runoff, day_runoff_N, day_clay_N, 
		dsno3, dsnh4, dsnh3, day_dsurea, ds_doc, crop, yr_fixn, rainfall, soil_ph, 
		winertC, inert_C, fert_flag, root_doc, day_O2, RFM, SoilDepth, Tttoo, 
		sop, OrgP, LabP, AdsP, ComP, sts, day_leach_water, 1.0, 0, 0, manco2, manurePool, manurePoolCN, UreaHydroInhibDays, UIDay1, UIDay2,  newmanuPH, combinedpHDeep,manureHour,NH3Vol, manureCounter);//added last 3 parameters to deal with crop side and new manure pool.

	MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);
	//manure temperature
	float dFH=0.0, BLHC=0.0, PTHC=0.0, HeatDF=0.0;
	
	compost_SHC = 1000.0; //soil specific heat capacity: 800-1480 J/kg*K
	float HeatCapa = compost_mass * compost_SHC;// heat for 1 deree C increase: J/K 
	float HV = 34500000.0;// Heat value of manure-C: J/kg C (Heat value of manure is 20 MJ/kg dry manure)
	BLHC = air_temp * HeatCapa;// Baseline (air temperature) heat capacity, J
	PTHC = temp[GN] * HeatCapa;// Present time (compost temperature) heat capacity, J
	CompostHeatGain = HV * co2[GN];// Heat produced from manure decomposition	
	PTHC += CompostHeatGain;//Present time (compost temperature) heat capacity, J	
	
	if(CompostCover==1)//air open
		HeatDF = 5.0 * compost_upper_area / compost_V * MData.m_CompostPoro;//diffused fraction of excessive heat
	else if(CompostCover==2)//sheltered
		HeatDF = 4.0 * compost_upper_area / compost_V * MData.m_CompostPoro;
	else
		HeatDF = 1.0 * compost_upper_area / compost_V * MData.m_CompostPoro;

	HeatDF = min(1.0, max(0.0, HeatDF));
	
	dFH = (PTHC - BLHC) * HeatDF;//Heat transfer from compost to air	
	PTHC -= dFH;//Present time (compost temperature) heat capacity, J	
	temp[GN] = PTHC / HeatCapa;
	
	DNDC->N2O_balloon(GN, till_fact, sts, h, jday, *flood_flag, FloDays, rainfall,
		O2_old, O2, TTT, vvv, ave_anvf, q, st, temp, year, water, day_wfps, day_WT, 
		WTL, total_ice, day_rco2, co2, flo_num, ice, sph, Eh, anvf,
		nh4, no3, no2, no, n2, doc, n2o, doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,
		doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, LandUse, Tttoo, 
		ManureAddCN, ManureDays, soc, MicrobioIndex, mRBO, mFD, WaterControl, 
		crop, assim2, clay, fldcap, by_passf, NIDay1, NIDay2,
		day_soil_nitrify, day_nitrify_NO, day_nitrify_N2O, day_soil_an_no,
		day_soil_an_n2o, day_soil_n2, Root_Wt, WaterLeakRate,
		rcvl, rcl, rcr, day_soil_denitrification,
		wiltpt, CRB1, CRB2, rcnb, day_frostDOC, yr_frostDOC, precipitation, 
		manuFlag, irri_flag, FreezeDOC, nh3, urea, LateralInflux, drain_flag,
		0, HSM, fertigate_flag,
		hrPE0, DayFlux, dby_flux, DroughtID, YieldToday, drc, scale, ha, livestock,
		day_nitrification, day_denitrification, 1,rno3, &day_inRainN,denitMulti, nitMulti, N2N2OFactor, day_nitrify_n2ol, day_denitrify_n2ol);

	MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);
	
	//DNDC->nh43_equil(GN, temp, sph, nh4, nh3, q);

	DNDC->nh3_volatilization(GN, temp, *flood_flag, wetland_flag, nh3, q, wind_speed, day_wfps, 
								ice, day_soil_nh3, nh4, jday, no3, manureHour, manureCounter);
	
	compost_CH4(GN, day_wfps, doc, CompostCover);

	MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);
}

void class_manure::compost_CH4(int FC, float *day_wfps, float *doc, int CompostCover)
{
	//based on Amon 1999
	float Ech4, E0, E01, E02, compost_ch4, DM;
	DM = day_wfps[FC] * 100.0;//manure moisture (%)
	E01 = 0.021 + 0.423 * DM; //for wet compost
	E02 = 0.001 + 0.025 * DM; //for dry compost

	E0 = E01 * (day_wfps[FC]/(day_wfps[FC]+1)) + E02 * (1-day_wfps[FC])/(1+day_wfps[FC]);

	Ech4 = 0.5 * E0 * (float)exp(-0.0462 * MData.compost_days) * 0.001 * 12.0 / 16.0 / 0.58;//kg CH4-C/kg manure-C

	compost_ch4 = Ech4 * doc[FC];// kg CH4-C per compost

	if(compost_ch4 < doc[FC])
	{
		MData.day_compost_ch4 += compost_ch4;// kg CH4-C per compost
		doc[FC] -= compost_ch4;
	}
	else
	{
		MData.day_compost_ch4 += doc[FC];
		doc[FC] = 0.0;
	}
}


void class_manure::ManureRunoff(int FN, int GN, float *RFL, float rcnrvl, float rcnrl,float rcnrr,
								   float rcnb,float rcnh,float rcnm,
								   float *rcvl,float *rcl,float *rcr,float *CRB1,float *CRB2,
								   float *crhl,float *crhr,float *dphum,
								   float *nh4,float *no3,float *no2,
								   float *no,float *n2o,float *n2,float *nh3,float *urea,float *co2,
								   float *doc,double water[25][250], 
								   float *OrgP,float *LabP,float *ComP)
{
	int MK=FN;
	for(int i1=1; i1<=8; i1++) MData.day_runoff_MC[MK] += RFL[i1];
	
	MData.day_runoff_MC[MK] += (RFL[20]+RFL[21]);

	MData.day_runoff_MON[MK] += RFL[1] / rcnrvl;
	MData.day_runoff_MON[MK] += RFL[2] / rcnrl;
	MData.day_runoff_MON[MK] += RFL[3] / rcnrr;
	MData.day_runoff_MON[MK] += RFL[4] / rcnb;
	MData.day_runoff_MON[MK] += RFL[5] / rcnb;
	MData.day_runoff_MON[MK] += RFL[6] / rcnh;
	MData.day_runoff_MON[MK] += RFL[7] / rcnh;
	MData.day_runoff_MON[MK] += RFL[8] / rcnm;

	for(int i2=12; i2<=19; i2++) MData.day_runoff_MIN[MK] += RFL[i2];

	MData.day_runoff_MOP[MK] += (RFL[9]+RFL[10]+RFL[11]);

		rcvl[GN] -= RFL[1];
		rcl[GN] -= RFL[2]; 
		rcr[GN] -= RFL[3]; 
		CRB1[GN] -= RFL[4]; 
		CRB2[GN] -= RFL[5]; 
		crhl[GN] -= RFL[6];
		crhr[GN] -= RFL[7]; 
		dphum[GN] -= RFL[8]; 
		OrgP[GN] -= RFL[9];
		LabP[GN] -= RFL[10];
		ComP[GN] -= RFL[11];
		nh4[GN] -= RFL[12];
		no3[GN] -= RFL[13];
		no2[GN] -= RFL[14];
		no[GN] -= RFL[15]; 
		n2o[GN] -= RFL[16];
		n2[GN] -= RFL[17]; 
		nh3[GN] -= RFL[18]; 	
		urea[GN] -= RFL[19]; 
		co2[GN] -= RFL[20];	
		doc[GN] -= RFL[21]; 
		water[1][GN] -= RFL[22]; 
		

	if(FN==4) MData.day_compost_runoff_WATER = RFL[22]; 
	
}

void class_manure::ManureMarket(int FN, int GN, float *RFL, float rcnrvl, float rcnrl,float rcnrr,
								   float rcnb,float rcnh,float rcnm,
								   float *rcvl,float *rcl,float *rcr,float *CRB1,float *CRB2,
								   float *crhl,float *crhr,float *dphum,
								   float *nh4,float *no3,float *no2,
								   float *no,float *n2o,float *n2,float *nh3,float *urea,float *co2,
								   float *doc,double water[25][250], float *OrgP,float *LabP,float *ComP)
{
	for(int i2=1; i2<=8; i2++) 
		{
			MData.day_market_MC[FN] += RFL[i2];
		}
		MData.day_market_MC[FN] += (RFL[17]+RFL[18]);

		MData.day_market_MON[FN] += RFL[1] / rcnrvl;
		MData.day_market_MON[FN] += RFL[2] / rcnrl;
		MData.day_market_MON[FN] += RFL[3] / rcnrr;
		MData.day_market_MON[FN] += RFL[4] / rcnb;
		MData.day_market_MON[FN] += RFL[5] / rcnb;
		MData.day_market_MON[FN] += RFL[6] / rcnh;
		MData.day_market_MON[FN] += RFL[7] / rcnh;
		MData.day_market_MON[FN] += RFL[8] / rcnm;

		for(int ix=12; ix<=19; ix++) 
		{
			MData.day_market_MIN[FN] += RFL[ix];
		}

		MData.day_market_MOP[FN] += (RFL[9]+RFL[10]+RFL[11]);

		rcvl[GN] -= RFL[1];
		rcl[GN] -= RFL[2]; 
		rcr[GN] -= RFL[3]; 
		CRB1[GN] -= RFL[4]; 
		CRB2[GN] -= RFL[5]; 
		crhl[GN] -= RFL[6];
		crhr[GN] -= RFL[7]; 
		dphum[GN] -= RFL[8]; 
		OrgP[GN] -= RFL[9];
		LabP[GN] -= RFL[10];
		ComP[GN] -= RFL[11];
		
		nh4[GN] -= RFL[12];
		no3[GN] -= RFL[13];
		no2[GN] -= RFL[14];
		no[GN] -= RFL[15]; 
		n2o[GN] -= RFL[16];
		n2[GN] -= RFL[17]; 
		nh3[GN] -= RFL[18]; 	
		urea[GN] -= RFL[19]; 
		co2[GN] -= RFL[20];	
		doc[GN] -= RFL[21]; 
		water[1][GN] -= RFL[22]; 
		
	//}

}

void class_manure::ManureLagoon(int GN, float *RFL, float rcnrvl, float rcnrl,float rcnrr,
								   float rcnb,float rcnh,float rcnm,
								   float *rcvl,float *rcl,float *rcr,float *CRB1,float *CRB2,
								   float *crhl,float *crhr,float *dphum,
								   float *nh4,float *no3,float *no2,
								   float *no,float *n2o,float *n2,float *nh3,float *urea,float *co2,
								   float *doc,double water[25][250], float *OrgP,float *LabP,float *ComP)
{
	for(int i3=1; i3<=8; i3++) MData.day_lagoon_MC += RFL[i3];
	
		MData.day_lagoon_MC += (RFL[17]+RFL[18]);

		MData.day_lagoon_MON += RFL[1] / rcnrvl;
		MData.day_lagoon_MON += RFL[2] / rcnrl;
		MData.day_lagoon_MON += RFL[3] / rcnrr;
		MData.day_lagoon_MON += RFL[4] / rcnb;
		MData.day_lagoon_MON += RFL[5] / rcnb;
		MData.day_lagoon_MON += RFL[6] / rcnh;
		MData.day_lagoon_MON += RFL[7] / rcnh;
		MData.day_lagoon_MON += RFL[8] / rcnm;

		MData.day_lagoon_MOP += (RFL[9]+RFL[10]+RFL[11]);

		for(int i4=2; i4<=19; i4++) 
		{
			MData.day_lagoon_MIN += RFL[i4];
		}

		MData.day_lagoon_WATER += RFL[22];
		

		rcvl[GN] -= RFL[1];
		rcl[GN] -= RFL[2]; 
		rcr[GN] -= RFL[3]; 
		CRB1[GN] -= RFL[4]; 
		CRB2[GN] -= RFL[5]; 
		crhl[GN] -= RFL[6];
		crhr[GN] -= RFL[7]; 
		dphum[GN] -= RFL[8]; 
		OrgP[GN] -= RFL[9];
		LabP[GN] -= RFL[10];
		ComP[GN] -= RFL[11];		
		nh4[GN] -= RFL[12];
		no3[GN] -= RFL[13];
		no2[GN] -= RFL[14];
		no[GN] -= RFL[15]; 
		n2o[GN] -= RFL[16];
		n2[GN] -= RFL[17]; 
		nh3[GN] -= RFL[18]; 	
		urea[GN] -= RFL[19]; 
		co2[GN] -= RFL[20];	
		doc[GN] -= RFL[21]; 
		water[1][GN] -= RFL[22]; 
		

}
#endif

