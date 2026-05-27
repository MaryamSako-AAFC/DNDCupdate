#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;
char js[50];
float NM_CH4=0.0;
/*

Rick Uritch's comment: 
  
Right now, our models predict DFI, DME (dry matter excretion) and ADG completely independently, they are not linked at all.  I would like to link them by saying what goes into the pig ends up either as new pig (ADG), excretion (DME) or exhaled as carbon.

                          DFI = (ADG)(fraction solids in new grown mass) + DME + C exhaled

I want to use this to predict DME instead of estimating it independently.

Using our current models on a 100 day pig:

weight = 59.5 kg (131 lb)

DFI = 2.48 kg/day
ADG = 0.81 kg/day
C in exhalations = 0.40 kg/day
      Ni, Hendriks et al. "Production of Carbon Dioxide in a Fattening Pig House under Field Conditions"
      Atmospheric Environment 33 (1999) p. 691

This gives: feed efficiency = 2.48/0.81 = 3.06

With those numbers, and assuming that a new kg of pig growth is 60% solids (about right for humans, can¡¯t find for pigs), then:

                        DME = 2.48 ¨C (0.81)(0.6) ¨C 0.40 = 1.59 kg/day
*/

void class_manure::ManureFeedlot(
		int *FN, int *GN,
		int jday, FILE* fLV1, FILE* fLV4, FILE* fLV3, float rcnrr, float rcnh, float rcnb, float *urea, float *doc, float *rcvl, 
		float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, float DayPET, 
		float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, float rcnrvl, float rcnrl, int WTL, 
		float day_WT, float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, int q, float rcnm, float *son, float *SIN, 
		float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, 
		float *w_no2, float *w_nh3, float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, 
		int tilq, FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate, float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, 
		float *ocini, float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim,  
		float DClitter, float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, float day_runoff, float *day_runoff_N, 
		float *day_clay_N, float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, 
		float *ds_doc, int *crop, float *yr_fixn, float till_fact, float *sts, float rainfall, float *O2_old, float *O2, 
		float *vvv, float *ave_anvf, int year, double water[25][250], float total_ice, float *day_rco2, int flo_num,
		float *Eh, float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, 
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, float *assim2,
		float *fldcap, float by_passf, int NIDay1, int NIDay2, float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *wiltpt, float *day_addmc, float *yr_addmc, float *yr_addmn, 
		float *day_inManureN, float *day_frostDOC, float *yr_frostDOC, float *winertC, 
		float *inert_C, int fert_flag, float *root_doc, float precipitation, 
		int manuFlag, int irri_flag, float *FreezeDOC, float *day_O2, float *day_farm_to_field_N, float *day_farm_to_field_C, 
		float *day_farm_to_field_H2O, float RFM, float *SoilDepth, int scale, 
		float *C_soil, float *sop, float *OrgP, float *LabP, float *ComP, float *AdsP, float *day_farm_to_field_P, 
		int fln, float *ch4_doc_pool, FILE* fFeedOut, float humidity, float min_temp, float max_temp, float PAR, 
		float *F_methanogen, float *Tttoo, float *H2, float *day_ch4_CO2, float *day_ch4_1, float *day_ch4_2,
		int Option, float *SMC, float day_leach_water, float* pen_soil_wfps, float *SO4, float sslope, float day_root_resp, FILE* HSM,
		int fertigate_flag, float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, float ha, 
		int livestock, float *day_nitrification, float *day_denitrification, float *day_H2_prod,float rno3, float day_inRainN, float denitMulti,float nitMulti, float N2N2OFactor, 
	    float* manco2, float* manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2,  float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol, int manureCounter, float *day_nitrify_n2ol, float *day_denitrify_n2ol)
{
	int i, jd, MDD=0;
	float TTT0, tntn;
	char IndoorClimateFile[10][300];
		
	//feedlot
	CString LAI;
	FILE *cm;
	char F_LV1[300], F_LV2[300], Zz[300];

	MData.FN = 1;
	MData.GN = q+1;

	*FN=1;
	if(MData.InputFormat[*FN]==1) //use daily feed file
	{
		fscanf(fLV1, "%d %s", &jd, js);//&MData.AnimalName[*FN]);		
		fscanf(fLV1, "%d %f %f %f %f", &MData.mm_AnimalType[*FN], &MData.mm_AnimalHeads[*FN], 
			&MData.mm_FeedRate[*FN], &MData.mm_FeedProtein[*FN], &MData.mm_FeedTP[*FN]);

		if(jd!=jday)
		{
#ifdef DEGUI		
		char EMSS[200];
		sprintf(EMSS, "Error on day %s in daily barn file", jday);
		MData.EMDD++;
		ErrorMessage(EMSS, MData.EMDD);
#else
			CString note;
			note.Format("Error on day %s in daily barn file", jday);
			AfxMessageBox(note);
#endif
			exit(0);
		}

		if(Option>100) 
			{
				MData.mm_FeedRate[*FN] *= (1.0 + SMC[19]);
				MData.mm_FeedProtein[*FN] *= (1.0 + SMC[20]);
				MData.mm_FeedTP[*FN] *= (1.0 + SMC[21]);
				MData.mm_AnimalHeads[*FN] *= (1.0 + SMC[46]);
			}
	}

	if(MData.InputFormat[*FN]==2) //use daily excretion file
	{
		float day_DM, day_DungN, day_UrineN, day_P, day_H2O;
		int Animal_type;
		float UrineCN[7]={0.0, 1.25, 1.25, 1.25, 4.24, 4.0, 4.0};//urine C/N ratio .. used to calculate incoming urine C based on Urine N and animal type (UrineCN array index)

		fscanf(fLV1, "%d", &jd);		//read excretion data? -- expects 2 header lines before first julian day.
		fscanf(fLV1, "%f %f %f %f %f %d", &day_DM, &day_DungN, &day_UrineN, &day_P, &day_H2O, &Animal_type);

		if(jd!=jday)
		{
#ifdef DEGUI		
		char EMSS[200];
		sprintf(EMSS, "Error on day %s in daily excretion file", jday);
		MData.EMDD++;
		ErrorMessage(EMSS, MData.EMDD);
#else
			CString note;
			note.Format("Error on day %s in daily excretion file", jday);
			AfxMessageBox(note);
#endif
			exit(0);
		}		

		MData.mm_UrineN[*FN] = day_UrineN;
		MData.mm_UrineC[*FN] = UrineCN[Animal_type] * day_UrineN;//kg N/day, Broderick 2003; Wattiaux and Karg 2004; //calculates urine C from animal type and Urine N  value
		MData.mm_DungN[*FN] = day_DungN; 
		MData.mm_DungC[*FN] = day_DM * 0.4;// - MData.mm_UrineC[*FN];

		if(MData.mm_DungC[*FN]<0.0) 
		{
#ifdef DEGUI		
		char EMSS[200];
		sprintf(EMSS, "Error in excreta input file data on %d", jday);
		MData.EMDD++;
		ErrorMessage(EMSS, MData.EMDD);
#else
			CString note;
			note.Format("Error in excreta input file data on %d", jday);
			AfxMessageBox(note);
#endif
			exit(0);
		}

		MData.mm_UrineWater[*FN] = day_H2O * 0.8;//kg water
		MData.mm_DungWater[*FN] = day_H2O * 0.2;

		MData.mm_UrineP[*FN] = day_P * 0.028;//kg P/day
		MData.mm_DungP[*FN] = day_P * 0.972;//kg P/day
		
	}

	if(MData.InputFormat[*FN]==3) //nutrition model output file
	{
		char VX[1];
		float NM_UreaC=0.0,	NM_UreaN=0.0, NM_FecesC=0.0, NM_FecesN=0.0,	NM_water=0.0;
		
		fscanf(fLV1, "%d %c", &jd, VX);
		if(jd!=jday)
		{
			CString NNO;
			NNO.Format("Error in nutrition model output file on day %d", jday);
			AfxMessageBox(NNO);
			exit(0);
		}
		fscanf(fLV1, "%f %c %f %c %f %c %f %c %f %c %f", &NM_UreaC, VX, &NM_UreaN, VX, &NM_FecesC, VX, &NM_FecesN, VX, &NM_water, VX, &NM_CH4);
		MData.mm_UrineC[*FN] = NM_UreaC;
		MData.mm_UrineN[*FN] = NM_UreaN;
		MData.mm_DungC[*FN] = NM_FecesC;
		MData.mm_DungN[*FN] = NM_FecesN;
		MData.mm_UrineP[*FN] = 0.0;
		MData.mm_DungP[*FN] = 0.0;
		MData.mm_UrineWater[*FN] = NM_water * 0.8;
		MData.mm_DungWater[*FN] = NM_water * 0.2;

	}

	if(MData.mm_Ventilation==-1)//read daily indoor climate data
	{
		fscanf(fLV4, "%d %f %f %f", &jd, &MData.indoor_T, &MData.indoor_RH, &MData.mm_VentRate);//MData.indoor_airflow);
		if(jd!=jday) 
		{
#ifdef DEGUI		
		char EMSS[200];
		sprintf(EMSS, "Error in indoor climate file  on day %d", jday);
		MData.EMDD++;
		ErrorMessage(EMSS, MData.EMDD);
#else
			AfxMessageBox("Error in indoor climate file on day %d", jday);
#endif
			exit(0);
		}
	}

	//manure biogeochemistry in feedlot
	*FN=1;
	*GN=q+1;
	MData.House_to_compost_C = 0.0;
	MData.House_to_compost_N = 0.0;
	MData.House_to_compost_H2O = 0.0;
	MData.House_to_lagoon_C = 0.0;
	MData.House_to_lagoon_N = 0.0;
	MData.House_to_lagoon_H2O = 0.0;
	MData.House_to_digester_C = 0.0;
	MData.House_to_digester_N = 0.0;
	MData.House_to_digester_H2O = 0.0;
	MData.House_to_compost_P = 0.0;
	MData.House_to_lagoon_P = 0.0;
	MData.House_to_digester_P = 0.0;

	EntericGasProduction(*FN, air_temp);
	 
	if(MData.InputFormat[*FN]==2||MData.InputFormat[*FN]==3) 
	{
		MData.yr_urine_C += MData.mm_UrineC[*FN];
		MData.yr_urine_N += MData.mm_UrineN[*FN];
		MData.yr_dung_C += MData.mm_DungC[*FN];
		MData.yr_dung_N += MData.mm_DungN[*FN];
		MData.yr_urine_P += MData.mm_UrineP[*FN];
		MData.yr_dung_P += MData.mm_DungP[*FN];
		MData.yr_urine_water += MData.mm_UrineWater[*FN];
		MData.yr_dung_water += MData.mm_DungWater[*FN];

		MData.yr_enteric_co2 = 0.0;
		MData.yr_intake_C = 0.0;
		MData.yr_intake_N = 0.0;
		MData.yr_intake_P = 0.0;
		MData.yr_milk_N = 0.0;
		MData.yr_milk_C = 0.0;
		MData.yr_milk_P = 0.0;
		MData.yr_meat_N = 0.0;
		MData.yr_meat_C = 0.0;
		MData.yr_meat_P = 0.0;
		//MData.yr_animal_CO2 = 0.0;
		MData.yr_milk_product = 0.0;
	}
	else
	{
		HouseManureProduct(*FN);
	}
			
	HouseManureOccumulation(*FN, *GN, q, jday, rcnrvl, rcnrl, rcnrr, rcnh, rcnb, urea, doc, rcvl, rcl, rcr, 
			crhl, crhr, CRB1, CRB2, dphum, water, rcnm, soc, son, SIN, nh4, no3, no2, no, n2o,
		   n2, nh3, co2, sop, OrgP, LabP, ComP, precipitation);

	//if(MData.mm_DungC[*FN]>0.0 && (MData.mm_GroundSurface[*FN]==0||MData.mm_GroundSurface[*FN]==1||MData.mm_GroundSurface[*FN]==3)) //up-floor for slatted floor, concrate floor or outdoor pen with bare soil, MData.mm_GroundSurface[*FN]==0||
	if(MData.mm_DungC[*FN]>0.0)
	{
		MData.BarnDays++;

		HouseManure_BGC(*FN, *GN, q, jday, rcnrvl, rcnrl, rcnrr, rcnh, rcnb, urea, doc, 
			rcvl, rcl, rcr, CRB1, CRB2, dphum, temp, air_temp, 
			DayPET, wind_speed, day_wfps, soc, sph, flood_flag, WTL, day_WT, 
			soil_ph, nh4, ch4_prod, ch4_day_oxid, plant_day_ch4, rcnm, son, SIN, no3, no2, 
			no, n2o, n2, nh3, ch4, TTT, newh, w_no2, w_nh3, 
			w_no3, w_nh4, wurea, day_clayn, wpool_no, DayFlux, tilq,  
			fCB, fNB, w_n2o, w_n2, seed, day_ch4, anvf, WaterLeakRate, co2, clay, LandUse, FloDays,
			crhl, crhr, mmm, ocini, h, day_C_mine, day_N_mine, day_N_assim, DClitter,
			litco22, litco23, st, DChumads, EFFAC, DChumus, wetland_flag, ice, day_soil_nh3,
			lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3, day_N_demand, day_nup, day_fixN, day_DWater,
			day_plant_nh3, yr_NH3_deposit, plantn, clay_nh4, base_clay_N, max_clay_N,
			wrcvl, wrcl, wrcr, wcrb, wcrhl, wcrhr, whumus, wtcavai,
		    day_ice_N, day_ice_doc, day_ice_n2o, day_ice_n2, IniSOC, IniSON, 
		    EndSON, day_runoff, day_runoff_N, day_clay_N, 
			dsno3, dsnh4, dsnh3, day_dsurea, ds_doc, crop, yr_fixn, till_fact,
			sts, rainfall, O2_old, O2, vvv, ave_anvf, year, water, total_ice, day_rco2, flo_num, Eh,
			doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,
			doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, ManureAddCN, ManureDays, MicrobioIndex,
			mRBO, mFD, WaterControl, assim2, fldcap, by_passf, NIDay1, NIDay2,
			day_soil_nitrify, day_nitrify_NO, day_nitrify_N2O, day_soil_an_no,
			day_soil_an_n2o, day_soil_n2, Root_Wt, day_soil_denitrification,
			R_Wt, vascularity, wiltpt, day_frostDOC, yr_frostDOC, winertC, inert_C, fert_flag,
			root_doc, precipitation, manuFlag, irri_flag, FreezeDOC, MData.mm_VentRate,
			day_O2, RFM, SoilDepth, C_soil, sop, OrgP, LabP, ComP, AdsP, ch4_doc_pool,
			humidity, min_temp, max_temp, PAR, F_methanogen, Tttoo, H2, day_ch4_CO2, day_ch4_1, day_ch4_2,
			day_leach_water, pen_soil_wfps, SO4, sslope, day_root_resp, HSM, fertigate_flag,
			hrPE0, dby_flux, DroughtID, YieldToday, drc, scale, ha, livestock, day_nitrification,
			day_denitrification, day_H2_prod,rno3, day_inRainN, denitMulti, nitMulti, N2N2OFactor, manco2, manurePool, manurePoolCN, UreaHydroInhibDays, UIDay1, UIDay2,  newmanuPH, combinedpHDeep,manureHour,NH3Vol, manureCounter, day_nitrify_n2ol, day_denitrify_n2ol);
	
		float TTF = 0.1 * (temp[*GN] + 20.0) / 55.0;
		TTF=max(0.0, min(1.0, TTF));
		float doc_co2 = doc[*GN] * TTF;
		doc[*GN] -= doc_co2;
		co2[*GN] += doc_co2;
		//day_O2[*GN] += doc_co2;
		MData.day_house_co2 += co2[*GN];		
		co2[*GN] = 0.0;	
	}
	else
	{
		MData.BarnDays = 0;

	}


	float TTTN1, TTTN2, T1N, T2N;
	
	T1N = Total_SOCSON(q+1, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

	T2N = Total_SOCSON(q+8, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

	TTTN1 = T1N + T2N;

	FeedlotManureRemoval0(*FN, *GN, q,  rcnrvl,  rcnrl,  rcnrr,  rcnb,  rcnh,  rcnm,
							 soc, son, SIN, rcvl, rcl, rcr, 
							 CRB1, CRB2, crhl, crhr, dphum, doc, 
							 nh4, no3, no2, no, n2o, n2, nh3, 
							 urea, jday, co2, sph, water, day_wfps, temp, air_temp,
							 scale, sop, OrgP, LabP, ComP, fFeedOut);// House_to_compost_C, House_to_compost_N, House_to_compost_H2O);
			
	//enteric CH4 and N2O from animals 
	if(MData.InputFormat[*FN]==2) 
	{
	}
	else if(MData.InputFormat[*FN]==3) //nutrition model
	{
		/*MData.yr_enteric_ch4 += NM_CH4;
		MData.yr_enteric_n2o += 0.0;//MData.DAY_enteric_n2o[FC];
		MData.yr_enteric_nh3 += 0.0;//MData.DAY_enteric_nh3[FC];

		MData.yr_enteric_co2 -= 0.0;//MData.DAY_enteric_ch4[FC];*/
	}
	else
	{
		//EntericGasProduction(*FN, air_temp);
	}
	
}

void class_manure::ManureTreatmentBGC(
		int *FN, int *GN,
		int jday, float rcnrr, float rcnh, float rcnb, float *urea, float *doc, float *rcvl, 
		float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, float DayPET, 
		float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, float rcnrvl, float rcnrl, int WTL, 
		float day_WT, float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, int q, float rcnm, float *son, float *SIN, 
		float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, 
		float *w_no2, float *w_nh3, float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, 
		int tilq, FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate, float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, 
		float *ocini, float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim,  
		float DClitter, float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, float day_runoff, float *day_runoff_N, 
		float *day_clay_N, float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, 
		float *ds_doc, int *crop, float *yr_fixn, float till_fact, float *sts, float rainfall, float *O2_old, float *O2, 
		float *vvv, float *ave_anvf, int year, double water[25][250], float total_ice, float *day_rco2, int flo_num,
		float *Eh, float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, float *ttoo,
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, float *assim2,
		float *fldcap, float by_passf, int NIDay1, int NIDay2, float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *wiltpt, float *day_addmc, float *yr_addmc, float *yr_addmn, 
		float *day_inManureN, float *day_frostDOC, float *yr_frostDOC, float *winertC, 
		float *inert_C, int fert_flag, float *root_doc, float precipitation, 
		int manuFlag, int irri_flag, float *FreezeDOC, float *day_O2, FILE *ftf, float *day_farm_to_field_N, float *day_farm_to_field_C, 
		float *day_farm_to_field_H2O, float RFM, float *SoilDepth, int scale, 
		float *C_soil, float *sop, float *OrgP, float *LabP, float *ComP, float *AdsP, 
		float *day_farm_to_field_P, float LateralInflux, int drain_flag, float *ToField, float day_leach_water,
		int CompostCover, float LagoonCapacity, FILE* HSM, int fertigate_flag,
		float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, float ha, int livestock,
		float *day_nitrification, float *day_denitrification, int m_Temp, float *manco2, float *manurePool, float manurePoolCN, float rno3, float day_inRainN, float denitMulti, float nitMulti, float N2N2OFactor,
	    int manureHour, int manureCounter, int UreaHydroInhibDays, int UIDay1, int UIDay2,  float newmanuPH, float combinedpHDeep, float NH3Vol,
	    float max_temp, float min_temp, int annualMinTempDay, float *lagoon_snowpack, float *lagoon_SnowMelt, float lagoon_snowfall, float lagoonTempPartition[101][2], float yr_avetj, float maxAnnualTemp, float averageAnnualTemp, float lagoon_ice[21], int& oldLayerDepth, float DayPETRN, float latitude, float humidity,float *day_nitrify_n2ol,float *day_denitrify_n2ol)//, float lagoon_snowpack							 )
{
	int i, j, jd, MDD=0;
	float TTT0, ttc;

	//manure biogeochemistry in compost
	*FN=4;
	*GN=q+4;
	MData.Compost_to_field_N = 0.0;
	MData.Compost_to_field_C = 0.0;
	MData.Compost_to_field_H2O = 0.0;
	MData.Compost_to_field_P = 0.0;

	MData.Total_SOCSON(*GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);

	if(soc[*GN]>0.0)//compost
	{
		MData.compost_days++;

		compost_BGC(*FN, *GN, q, jday, rcnrvl, rcnrl, rcnrr, rcnh, rcnb, urea, doc, 
			rcvl, rcl, rcr, CRB1, CRB2, dphum, temp, air_temp, 
			DayPET, wind_speed, day_wfps, soc, sph, flood_flag, WTL, day_WT, 
			soil_ph, nh4, ch4_prod, ch4_day_oxid, plant_day_ch4, rcnm, son, SIN, no3, no2, 
			no, n2o, n2, nh3, ch4, TTT, newh, w_no2, w_nh3, 
			w_no3, w_nh4, wurea, day_clayn, wpool_no, DayFlux, tilq, 
			fCB, fNB, w_n2o, w_n2, seed, day_ch4, anvf, WaterLeakRate, co2, clay, LandUse, FloDays,
			crhl, crhr, mmm, ocini, h, day_C_mine, day_N_mine, day_N_assim, DClitter,
			litco22, litco23, st, DChumads, EFFAC, DChumus, wetland_flag, ice, day_soil_nh3,
			lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3, day_N_demand, day_nup, day_fixN, day_DWater,
			day_plant_nh3, yr_NH3_deposit, plantn, clay_nh4, base_clay_N, max_clay_N,
			wrcvl, wrcl, wrcr, wcrb, wcrhl, wcrhr, whumus, wtcavai,
		    day_ice_N, day_ice_doc, day_ice_n2o, day_ice_n2, IniSOC, IniSON, 
		    EndSON, day_runoff, day_runoff_N, day_clay_N, 
			dsno3, dsnh4, dsnh3, day_dsurea, ds_doc, crop, yr_fixn, till_fact,
			sts, rainfall, O2_old, O2, vvv, ave_anvf, year, water, total_ice, day_rco2, flo_num, Eh,
			doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,
			doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, ttoo, ManureAddCN, ManureDays, MicrobioIndex,
			mRBO, mFD, WaterControl, assim2, fldcap, by_passf, NIDay1, NIDay2,
			day_soil_nitrify, day_nitrify_NO, day_nitrify_N2O, day_soil_an_no,
			day_soil_an_n2o, day_soil_n2, Root_Wt, day_soil_denitrification,
			R_Wt, vascularity, wiltpt, day_frostDOC, yr_frostDOC, winertC, inert_C,
			fert_flag, root_doc, precipitation, manuFlag, irri_flag, FreezeDOC,
			day_O2, RFM, SoilDepth, sop, OrgP, LabP, ComP, AdsP, LateralInflux,
			drain_flag, day_leach_water, CompostCover, HSM, fertigate_flag,
			hrPE0, dby_flux, DroughtID, YieldToday, drc, scale, ha, livestock, day_nitrification,
			day_denitrification,manco2, manurePool, manurePoolCN,rno3, day_inRainN, denitMulti, nitMulti,  N2N2OFactor, manureHour, manureCounter,
			UreaHydroInhibDays, UIDay1, UIDay2,  newmanuPH, combinedpHDeep, NH3Vol, day_nitrify_n2ol, day_denitrify_n2ol);
		
			MData.day_compost_co2 = co2[*GN];
			co2[*GN] = 0.0;

			
		//compost removal 
		if(MData.m_ManureRemoveTimes[*FN]>0)
		{
			for(int zx=1; zx<=MData.m_ManureRemoveTimes[*FN]; zx++)
			{			
				if(jday==MData.m_CompostRemoveDate[*FN][zx])
				{
					StorageManureRemoval(*FN, *GN, q,  rcnrvl,  rcnrl,  rcnrr,  rcnb,  rcnh,  rcnm,
									 soc, son, SIN, rcvl, rcl, rcr, 
									 CRB1, CRB2, crhl, crhr, dphum, doc, 
									 nh4, no3, no2, no, n2o, n2, nh3, 
									 urea, jday, co2, sph, water, day_wfps, temp, air_temp,
									 day_addmc, yr_addmc, yr_addmn, day_inManureN, 
									 day_farm_to_field_N, day_farm_to_field_C, day_farm_to_field_H2O,
									 scale, sop, OrgP, LabP, ComP, day_farm_to_field_P, 1, ToField);
					MData.compost_days = 0;
				}
			}
		}
		else
		{
			
		}
	}
	

	//manure biogeochemistry in lagoonn
	*FN=5;
	*GN=q+5;
	MData.Lagoon_to_field_N = 0.0;
	MData.Lagoon_to_field_C = 0.0;
	MData.Lagoon_to_field_H2O = 0.0;
	MData.Lagoon_to_field_P = 0.0;

	/*MData.House_to_lagoon_N = MData.Total_SOCSON(*GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);*/

	if(soc[*GN]>0.0||water[1][*GN]>0.0)//lagoon
	{
		float disturbance=0.0;

		MData.lagoon_days++;

		lagoon_BGC(*FN, *GN, q, jday, rcnrvl, rcnrl, rcnrr, rcnh, rcnb, urea, doc, 
			rcvl, rcl, rcr, CRB1, CRB2, dphum, temp, air_temp, 
			DayPET, wind_speed, day_wfps, soc, sph, flood_flag, WTL, day_WT, 
			soil_ph, nh4, ch4_prod, ch4_day_oxid, plant_day_ch4, rcnm, son, SIN, no3, no2, 
			no, n2o, n2, nh3, ch4, TTT, newh, w_no2, w_nh3, 
			w_no3, w_nh4, wurea, day_clayn, wpool_no, DayFlux, tilq,  
			fCB, fNB, w_n2o, w_n2, seed, day_ch4, anvf, WaterLeakRate, co2, clay, LandUse, FloDays,
			crhl, crhr, mmm, ocini, h, day_C_mine, day_N_mine, day_N_assim, DClitter,
			litco22, litco23, st, DChumads, EFFAC, DChumus, wetland_flag, ice, day_soil_nh3,
			lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3, day_N_demand, day_nup, day_fixN, day_DWater,
			day_plant_nh3, yr_NH3_deposit, plantn, clay_nh4, base_clay_N, max_clay_N,
			wrcvl, wrcl, wrcr, wcrb, wcrhl, wcrhr, whumus, wtcavai,
		    day_ice_N, day_ice_doc, day_ice_n2o, day_ice_n2, IniSOC, IniSON, 
		    EndSON, day_runoff, day_runoff_N, day_clay_N, 
			dsno3, dsnh4, dsnh3, day_dsurea, ds_doc, crop, yr_fixn, till_fact,
			sts, rainfall, O2_old, O2, vvv, ave_anvf, year, water, total_ice, day_rco2, flo_num, Eh,
			doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,
			doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, ttoo, ManureAddCN, ManureDays, MicrobioIndex,
			mRBO, mFD, WaterControl, assim2, fldcap, by_passf, NIDay1, NIDay2,
			day_soil_nitrify, day_nitrify_NO, day_nitrify_N2O, day_soil_an_no,
			day_soil_an_n2o, day_soil_n2, Root_Wt, day_soil_denitrification,
			R_Wt, vascularity, winertC, inert_C, fert_flag, root_doc, 
			day_O2, RFM, SoilDepth, wiltpt, day_frostDOC, yr_frostDOC, precipitation,manuFlag, irri_flag, 
			FreezeDOC, sop, OrgP, LabP, ComP, AdsP, LateralInflux, drain_flag, day_leach_water, 0,
			LagoonCapacity, disturbance, manco2, manurePool, manurePoolCN, UreaHydroInhibDays, UIDay1, UIDay2, newmanuPH, combinedpHDeep,manureHour, NH3Vol, manureCounter,
			max_temp, maxAnnualTemp, min_temp, yr_avetj, oldLayerDepth, lagoonTempPartition, lagoon_snowpack, lagoon_SnowMelt, lagoon_snowfall, DayPETRN, lagoon_ice,latitude,humidity);
		
		MData.Total_SOCSON(*GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);

		MData.day_lagoon_co2 = co2[*GN];
		co2[*GN] = 0.0;

		for(j=1; j<=MData.m_ManureRemoveTimes[*FN]; j++)
		{
			if(jday==MData.m_LagoonDrainDate[*FN][j]) //lagoon removal
			{
				StorageManureRemoval(*FN, *GN, q,  rcnrvl,  rcnrl,  rcnrr,  rcnb,  rcnh,  rcnm,
									 soc, son, SIN, rcvl, rcl, rcr, 
									 CRB1, CRB2, crhl, crhr, dphum, doc, 
									 nh4, no3, no2, no, n2o, n2, nh3, 
									 urea, jday, co2, sph, water, day_wfps, temp, air_temp,
									 day_addmc, yr_addmc, yr_addmn, day_inManureN, 
									 day_farm_to_field_N, day_farm_to_field_C, day_farm_to_field_H2O,
									 scale, sop, OrgP, LabP, ComP, day_farm_to_field_P, j,
									 ToField);
				
				MData.LagoonFieldAplMethod = MData.m_LagoonFieldAplMethod[j];
				MData.LagoonFieldAplDepth = MData.m_LagoonFieldAplDepth[j];

				if(soc[*GN]<=0.0) 
					MData.lagoon_days = 0;
			}
			else
			{
				
			}
		}

	}

	//manure biogeochemistry in anaerobic digester
	*FN=6;
	*GN=q+6;
	MData.day_digester_CH4=0.0;
	MData.day_digester_n2o=0.0;
	MData.day_digester_n2=0.0;
	MData.Digester_to_field_N = 0.0;
	MData.Digester_to_field_C = 0.0;
	MData.Digester_to_field_H2O = 0.0;
	MData.Digester_to_field_P = 0.0;

	MData.Total_SOCSON(*GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);
	ttc = MData.ttc;

	if(soc[*GN]>0.0)//digester
	{	
		MData.digester_days++;

		digester_BGC(*FN, *GN, q, jday, rcnrvl, rcnrl, rcnrr, rcnh, rcnb, urea, doc, 
			rcvl, rcl, rcr, CRB1, CRB2, dphum, temp, air_temp, 
			DayPET, wind_speed, day_wfps, soc, sph, flood_flag, WTL, day_WT, 
			soil_ph, nh4, ch4_prod, ch4_day_oxid, plant_day_ch4, rcnm, son, SIN, no3, no2, 
			no, n2o, n2, nh3, ch4, TTT, newh, w_no2, w_nh3, 
			w_no3, w_nh4, wurea, day_clayn, wpool_no, DayFlux, tilq, 
			fCB, fNB, w_n2o, w_n2, seed, day_ch4, anvf, WaterLeakRate, co2, clay, LandUse, FloDays,
			crhl, crhr, mmm, ocini, h, day_C_mine, day_N_mine, day_N_assim, DClitter,
			litco22, litco23, st, DChumads, EFFAC, DChumus, wetland_flag, ice, day_soil_nh3,
			lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3, day_N_demand, day_nup, day_fixN, day_DWater,
			day_plant_nh3, yr_NH3_deposit, plantn, clay_nh4, base_clay_N, max_clay_N,
			wrcvl, wrcl, wrcr, wcrb, wcrhl, wcrhr, whumus, wtcavai,
		    day_ice_N, day_ice_doc, day_ice_n2o, day_ice_n2, IniSOC, IniSON, 
		    EndSON, day_runoff, day_runoff_N, day_clay_N, 
			dsno3, dsnh4, dsnh3, day_dsurea, ds_doc, crop, yr_fixn, till_fact,
			sts, rainfall, O2_old, O2, vvv, ave_anvf, year, water, total_ice, day_rco2, flo_num, Eh,
			doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,
			doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, ttoo, ManureAddCN, ManureDays, MicrobioIndex,
			mRBO, mFD, WaterControl, assim2, fldcap, by_passf, NIDay1, NIDay2,
			day_soil_nitrify, day_nitrify_NO, day_nitrify_N2O, day_soil_an_no,
			day_soil_an_n2o, day_soil_n2, Root_Wt, day_soil_denitrification,
			R_Wt, vascularity, sop, m_Temp);

	MData.Total_SOCSON(*GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);
	ttc = MData.ttc;

		//MData.day_digester_CO2 = co2[*GN];
		co2[*GN] = 0.0;
	
		//digester removal
		if(MData.m_ManureRemoveFrequency[*FN]>0.0) 
		{
			StorageManureRemoval(*FN, *GN, q,  rcnrvl,  rcnrl,  rcnrr,  rcnb,  rcnh,  rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, jday, co2, sph, water, day_wfps, temp, air_temp,
								 day_addmc, yr_addmc, yr_addmn, day_inManureN, 
								 day_farm_to_field_N, day_farm_to_field_C, day_farm_to_field_H2O,
								 scale, sop, OrgP, LabP, ComP, day_farm_to_field_P, 1, ToField);
			MData.digester_days = 0;

			MData.Total_SOCSON(*GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);
	ttc = MData.ttc;
		}
	}

	//Record manure applied to field
	fprintf(ftf, "%4d %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10d %10.2f\n", 
			jday, 
			ToField[1],ToField[2],ToField[3],ToField[4],ToField[5],ToField[6],ToField[7],ToField[8],ToField[9],ToField[10],
			ToField[11],ToField[12],ToField[13],ToField[14],ToField[15],ToField[16],ToField[17],ToField[18],ToField[19],ToField[20],
			ToField[21],ToField[22], MData.LagoonFieldAplMethod, MData.LagoonFieldAplDepth);

		
}
#endif
