#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;

extern class_model *DNDC;

//extern class_model DData;

float mm_ManurePH[7]={7.0, 7.0, 7.0, 7.0, 8.1, 7.5, 7.8}; 
//for dairy cattle, beef, veal, pig, sheep, foultry

void class_manure::HouseManure_BGC(int FN, int GN, 
		int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float *urea, float *doc,
		float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, 
		float DayPET, float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, int WTL, float day_WT, 
		float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, float rcnm, float *son, float *SIN, float *no3, float *no2, 
		float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, float *w_no2, float *w_nh3, 
		float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, int tilq, 
		FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate,
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
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, 
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, 
		float *assim2, float *fldcap, float by_passf, int NIDay1, int NIDay2,
		float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *wiltpt, float *day_frostDOC, float *yr_frostDOC,
		float *winertC, float *inert_C, int fert_flag, float *root_doc,  
		float precipitation, float manuFlag, int irri_flag, float *FreezeDOC, float mm_VentRate,
		float *day_O2, float RFM, float *SoilDepth, float *C_soil, float *sop, 
		float *OrgP, float *LabP, float *ComP, float *AdsP, float *ch4_doc_pool, 
		float humidity, float min_temp, float max_temp, float PAR, float *F_methanogen, float *Tttoo, float *H2,
		float *day_ch4_CO2, float *day_ch4_1, float *day_ch4_2, float day_leach_water, float* pen_soil_wfps,
		float *SO4, float sslope, float day_root_resp, FILE* HSM, int fertigate_flag,
		float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, int scale, float ha, 
		int livestock, float *day_nitrification, float *day_denitrification, float *day_H2_prod, float rno3, float day_inRainN, float denitMulti,float nitMulti, float N2N2OFactor, 
	    float* manco2, float* manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2,  float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol,int manureCounter, float *day_nitrify_n2ol,float *day_denitrify_n2ol)//,float *manco2, float* manurePool, float manurePoolCN
{
	int i;
	float thorni, A, TTMP, x, mm_DayPET, L_m, DHE=0.0, fldcp_manure, poro_manure, pen_soil_satu;
	float m_humidity, m_air_temp, m_max_temp, m_min_temp, m_wind_speed, m_Day_Hrs, m_PAR, m_albedo;
	Root_Wt[GN]=0.0;
	R_Wt[GN]=0.0;
	//float manure_Eh[50]={0.0,0.0};

	h[GN] = h[1];

/*	//manure temperature
	if(MData.mm_Ventilation==-1)//use daily indoor climate data
	{
		temp[GN] = MData.indoor_T;
		//MData.indoor_T, MData.indoor_RH, MData.indoor_airflow);
	}
	else if(MData.mm_Ventilation==0) 
	{
		temp[GN] = air_temp-(air_temp-20.0)*0.5;
	}
	else 
	{
		temp[GN] = 0.5 * air_temp + 10.0 * MData.mm_VentRate;
	}
*/		
	//manure moisture
	m_Day_Hrs = 12.0;
	m_albedo = 0.2;
	m_humidity = humidity;
	temp[GN] = air_temp;
	m_air_temp = temp[GN];
	m_max_temp = max_temp;
	m_min_temp = min_temp;
	m_wind_speed = wind_speed;
	m_PAR = PAR;

	float ttn4=MData.Total_SOCSON(q+1, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);		
	
	//pen water runoff and leaching
	poro_manure = (soc[GN] / 0.58) / 400.0 * 0.5;//m^3/lot
	fldcp_manure = 0.7 * poro_manure * 1000.0;//manure water capacity, kg water/lot
	float fldcapw = h[1] * sts[1] * fldcap[1] * MData.mm_GroundArea[1] * 1000.0;//soil water capacity, kg water/lot
	float ManureLayerHoldWaterCapacity = fldcp_manure + fldcapw; //kg water/lot/layer 1
	
	if(MData.mm_GroundSurface[1]==3)//outdoor pen with open air
	{
		temp[GN] = air_temp;
		m_air_temp = temp[GN];
		m_wind_speed = wind_speed;
		mm_DayPET = Penman_PET(m_humidity, m_air_temp, m_max_temp, m_min_temp, m_wind_speed, m_Day_Hrs, m_PAR, m_albedo);//m water/day

		//TTT = precipitation / 0.005;
		
/*		float ttn4=MData.Total_SOCSON(q+1, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea,  
								 co2, sop,OrgP, LabP, ComP);		
	
		//pen water runoff and leaching
		poro_manure = (soc[GN] / 0.58) / 400.0 * 0.5;//m^3/lot
		fldcp_manure = 0.7 * poro_manure * 1000.0;//manure water capacity, kg water/lot
		float fldcapw = h[1] * sts[1] * fldcap[1] * MData.mm_GroundArea[1] * 1000.0;//soil water capacity, kg water/lot
		float ManureLayerHoldWaterCapacity = fldcp_manure + fldcapw; //kg water/lot/layer 1 */

		//pen_soil_satu = 0.5 * MData.mm_GroundArea[1] * 0.5 * 1000.0; //kg water/lot
		//float pen_soil_water = *pen_soil_wfps * pen_soil_satu;//kg water/lot
		//float pen_water = water[1][GN] + pen_soil_water * 0.7; 		
		
		if(water[1][GN]<=ManureLayerHoldWaterCapacity) //no leaching or runoff
		{
			MData.day_floor_leach_urea = 0.0;
			MData.day_floor_leach_NH4 = 0.0;
			MData.day_floor_leach_NO3 = 0.0;
			MData.day_floor_leach_doc = 0.0;
		}
		else //pen water runoff and leaching
		{
			if(sslope>0.0)//surface runoff
			{
				float WDW = sslope / 90.0;
				MData.day_feedlot_runoff_WATER = (water[1][GN] - ManureLayerHoldWaterCapacity) * WDW;

				float RFL[24] = {0.0,0.0};
				float RunoffIndex = MData.day_feedlot_runoff_WATER / water[1][GN]; 
								
				RFL[1] = rcvl[GN] * RunoffIndex;
				RFL[2] = rcl[GN] * RunoffIndex; 
				RFL[3] =  rcr[GN] * RunoffIndex; 
				RFL[4] =   CRB1[GN] * RunoffIndex; 
				RFL[5] = CRB2[GN] * RunoffIndex; 
				RFL[6] = crhl[GN] * RunoffIndex;
				RFL[7] = crhr[GN] * RunoffIndex; 
				RFL[8] = dphum[GN] * RunoffIndex; 
				RFL[9] = OrgP[GN] * RunoffIndex;
				RFL[10] = LabP[GN] * RunoffIndex;
				RFL[11] = ComP[GN] * RunoffIndex;
				
				RFL[12] = nh4[GN] * RunoffIndex;
				RFL[13] = no3[GN] * RunoffIndex;
				RFL[14] = no2[GN] * RunoffIndex;
				RFL[15] = no[GN] * RunoffIndex; 
				RFL[16] = n2o[GN] * RunoffIndex;
				RFL[17] =  n2[GN] * RunoffIndex; 
				RFL[18] =  nh3[GN] * RunoffIndex; 	
				RFL[19] =  urea[GN] * RunoffIndex; 
				RFL[20] = co2[GN] * RunoffIndex;	
				RFL[21] =  doc[GN] * RunoffIndex; 
				RFL[22] = water[1][GN] * RunoffIndex; 
				

				ManureRunoff(FN, GN, RFL, rcnrvl, rcnrl,rcnrr,rcnb,rcnh,rcnm,
					rcvl,rcl,rcr,CRB1,CRB2,crhl,crhr,dphum,nh4,no3,no2,
					no,n2o,n2,nh3,urea,co2,doc,water, OrgP,LabP,ComP);
				
				water[1][GN] -= MData.day_feedlot_runoff_WATER;
			}
			else
			{
				MData.day_feedlot_runoff_WATER = 0.0;
			}

			if(water[1][GN]>ManureLayerHoldWaterCapacity)//leaching
			{
				MData.day_floor_leach_water = water[1][GN] - ManureLayerHoldWaterCapacity;
				float WFF = MData.day_floor_leach_water / water[1][GN];
				MData.day_floor_leach_urea = WFF * urea[GN];
				MData.day_floor_leach_NH4 = WFF * nh4[GN];
				MData.day_floor_leach_NO3 = WFF * no3[GN];
				MData.day_floor_leach_doc = WFF * doc[GN];

				water[1][GN] -= MData.day_floor_leach_water;
				urea[GN] -= MData.day_floor_leach_urea;
				nh4[GN] -= MData.day_floor_leach_NH4;
				no3[GN] -= MData.day_floor_leach_NO3;
				doc[GN] -= MData.day_floor_leach_doc;

				MData.yr_floor_leach_urea += MData.day_floor_leach_urea;
				MData.yr_floor_leach_NH4 += MData.day_floor_leach_NH4;
				MData.yr_floor_leach_NO3 += MData.day_floor_leach_NO3;
				MData.yr_floor_leach_doc += MData.day_floor_leach_doc;

				MData.day_house_n2o += 0.0001 * (MData.day_floor_leach_urea+MData.day_floor_leach_NH4+MData.day_floor_leach_NO3);
				MData.day_house_nh3 += 0.1 * (MData.day_floor_leach_urea+MData.day_floor_leach_NH4);
				MData.day_floor_leach_urea *= 0.9;
				MData.day_floor_leach_NH4 *= 0.9;
			}
			else
			{
				MData.day_floor_leach_urea = 0.0;
				MData.day_floor_leach_NH4 = 0.0;
				MData.day_floor_leach_NO3 = 0.0;
				MData.day_floor_leach_doc = 0.0;
			}
		}			

		day_wfps[GN] = water[1][GN] / (poro_manure * 1000.0);
		day_wfps[GN] = max(0.001, min(1.0, day_wfps[GN]));

		//*pen_soil_wfps = pen_soil_water / pen_soil_satu;
		//*pen_soil_wfps = max(0.5, min(0.7, *pen_soil_wfps));
		
		//manure evaporation					
		DHE = 0.1 * mm_DayPET * MData.mm_GroundArea[1] * 1000.0;//ground surface evaporated water, kg water/day

		if(water[1][GN]<DHE)
		{
			MData.day_house_evap += water[1][GN];
			DHE -= water[1][GN];
			water[1][GN] = 0.0;			
		}
		else
		{
			MData.day_house_evap += DHE;
			water[1][GN] -= DHE;
			DHE = 0.0;
		}

		//Pen soil evaporation
/*		if((pen_soil_water*0.7) < DHE)
		{
			MData.day_house_evap += (pen_soil_water*0.7);
			DHE -= (pen_soil_water*0.7);
			pen_soil_water -= (pen_soil_water*0.7);
		}
		else
		{
			MData.day_house_evap += DHE;
			pen_soil_water -= DHE;
			DHE = 0.0;
		}
*/		
		if(water[1][GN]<0.0) water[1][GN]=0.0;	
		
		//MData.day_house_evap += DHE;	
		MData.yr_house_evap += MData.day_house_evap;	

		
	}
	else //indoor feedlot
	{
		if(MData.mm_Ventilation==0)//natural ventilation in shelter
		{
			if(GN==q+1) //floor
				temp[GN] = air_temp-(air_temp-20.0)*0.5;
			else //gutter
				temp[GN] = air_temp-(air_temp-20.0)*0.5 + 5.0;

			//float dTEMP = temp[GN] - air_temp;			

			m_air_temp = temp[GN];
			m_max_temp = temp[GN] + 2.0;
			m_min_temp = temp[GN] - 2.0;

			m_wind_speed = 0.2 * wind_speed;
			//m_PAR *= 0.2;
		}
		else if(MData.mm_Ventilation==1)//fan
		{
			//20-150 L/s = 0.02-0.15 m3/s
			if(air_temp<0.0)
				temp[GN] = 0.5 * air_temp;// + 14.0 * MData.mm_VentRate;
			else
				temp[GN] = 0.5 * air_temp;// + 10.0 * MData.mm_VentRate;

			m_air_temp = temp[GN];
			m_max_temp = temp[GN] + 2.0;
			m_min_temp = temp[GN] - 2.0;
		}
		else //-1 indoor climate file data
		{
			//temp[GN] = air_temp-(air_temp-20.0)*0.5;
			temp[GN] = MData.indoor_T;
			m_air_temp = MData.indoor_T;
			m_max_temp = MData.indoor_T;
			m_min_temp = MData.indoor_T;
			m_humidity = MData.indoor_RH;
			m_wind_speed = 2.0;//MData.mm_VentRate * 0.1;//MData.indoor_airflow * 0.1;
			//m_PAR = PAR;
		}

		//water runoff loss
		
		/*if(water[1][GN]>fldcp_manure)
		{
			float RunoffLoss = 0.2 * (water[1][GN] - fldcp_manure);
			water[1][GN] -= RunoffLoss;
		}*/

		water[1][GN] += MData.m_FlushWater[FN] * 1000.0;
		MData.yr_flush_H2O += MData.m_FlushWater[FN] * 1000.0;

		mm_DayPET = Penman_PET(m_humidity, m_air_temp, m_max_temp, m_min_temp, m_wind_speed, m_Day_Hrs, m_PAR, m_albedo);
	
		DHE = 0.2 * mm_DayPET * MData.mm_GroundArea[1] * 1000.0;//ground surface evaporated water, kg water/day
		if(GN==q+8) DHE = 0.0;//gutter

		if(water[1][GN]>DHE)
		{
			water[1][GN] -= DHE;
		}
		else
		{
			DHE = water[1][GN] * 0.9;
			water[1][GN] *= 0.1;
		}

		if(water[1][GN]<0.0) water[1][GN]=0.0;	

		day_wfps[GN] = water[1][GN] / (poro_manure * 1000.0);
		day_wfps[GN] = max(0.01, min(1.0, day_wfps[GN]));
		
		MData.day_house_evap += DHE;	
		MData.yr_house_evap += DHE;	
	}	

	sph[GN] = mm_ManurePH[MData.mm_AnimalType[FN]];

	//Eh[GN] = (1.0-day_wfps[GN]) * 500.0;
	
	vascularity[7]=0.0;
	
	//if(day_wfps[GN]>0.8) *flood_flag=1;

	anvf[GN] = day_wfps[GN];

	Tttoo[GN] = 0.4;

	float PGI[7]={0.0,0.0};
	
	if(GN==q+8)//gutter
	{
		Tttoo[GN] = doc[GN];

		DNDC->CH4_paddy(0, GN, temp, clay, 1, 5, Root_Wt,
							  q, Eh, sph, vascularity, 1, day_rco2,
							  R_Wt, 0.0, 0.0, 1, rcvl,
							  rcl, rcr, st, rcnrvl, rcnrl, rcnrr,
							  1.0, ch4, WTL, day_WT, 
							  soil_ph, doc, nh4, ch4_prod, ch4_day_oxid, 
							  plant_day_ch4, day_wfps, seed, day_ch4, anvf, 
							  WaterLeakRate, h, CRB1, rcnb, co2, crhl, crhr,  
							  air_temp, ch4_doc_pool, F_methanogen, WaterControl, 
							  Tttoo, jday, rcnh, H2, day_ch4_CO2, day_ch4_1, 
							  day_ch4_2, SO4, day_root_resp, PGI, 0, 0.0, 0.0, 0.0, day_H2_prod);
	}
	else
	{
		if(day_wfps[GN]==1.0)
		{
			DNDC->CH4_paddy(0, GN, temp, clay, 1, 5, Root_Wt,
							  q, Eh, sph, vascularity, 1, day_rco2,
							  R_Wt, 0.0, 0.0, 1, rcvl,
							  rcl, rcr, st, rcnrvl, rcnrl, rcnrr,
							  1.0, ch4, WTL, day_WT, 
							  soil_ph, doc, nh4, ch4_prod, ch4_day_oxid, 
							  plant_day_ch4, day_wfps, seed, day_ch4, anvf, 
							  WaterLeakRate, h, CRB1, rcnb, co2, crhl, crhr, 
							  air_temp, ch4_doc_pool, F_methanogen, WaterControl, 
							  Tttoo, jday, rcnh, H2, day_ch4_CO2, day_ch4_1, 
							  day_ch4_2, SO4, day_root_resp, PGI, 0, 0.0, 0.0, 0.0, day_H2_prod);
		}
		else
			Eh[GN] = (1.0-day_wfps[GN]) * 500.0;
	}	
	
	

	//solid manure biogeochemistry //need to add manurePool etc here
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
		winertC, inert_C, fert_flag, root_doc, day_O2, RFM, SoilDepth, Tttoo, sop,
		OrgP, LabP, AdsP, ComP, sts, day_leach_water, 1.0, 0, 0, manco2,manurePool,manurePoolCN, UreaHydroInhibDays, UIDay1, UIDay2,  newmanuPH, combinedpHDeep,manureHour,NH3Vol, manureCounter);//added 3 zeros for manco2, manurePool, manurePoolCN to match crop side.

	
/*	if(urea[GN]>0.0)
	{
		float dUREA = (0.1 * urea[GN] * temp[GN] / 50.0);
		nh4[GN] += dUREA;
		urea[GN] -= dUREA;
	}
*/
/*	if(nh4[GN]>0.0)
	{
		float dNH4 = (0.1 * nh4[GN] * temp[GN] / 50.0);//0.1
		no3[GN] += dNH4;
		nh4[GN] -= dNH4;
	}
*/

	MData.day_house_co2 += co2[GN];
	co2[GN] = 0.0;

	Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, 
				 sop,OrgP, LabP, ComP);

	if(MData.mm_GroundSurface[1]!=3)
	{
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
			manuFlag, irri_flag, FreezeDOC, nh3, urea, 0.0, 0, 0, HSM, fertigate_flag,
			hrPE0, DayFlux, dby_flux, DroughtID, YieldToday, drc, scale, ha, livestock,
			day_nitrification, day_denitrification, 1, rno3, &day_inRainN, denitMulti, nitMulti,N2N2OFactor, day_nitrify_n2ol, day_denitrify_n2ol);
	}

	MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);

	//liquid manure in gutter
	//if(MData.mm_GroundSurface[1]==0)  
	{
		if(GN==q+8)//gutter
		{
			*flood_flag = 1;
			temp[GN] = temp[GN] + 5.0;
			sph[GN] = sph[GN];
			day_wfps[GN] = 1.0;
			Root_Wt[GN]=0.0;
			R_Wt[GN]=0.0;
			Eh[GN] = -300.0;
			anvf[GN] = 0.99;
		}

		
		//DNDC->urea_hydrolysis(GN, urea, temp, day_wfps, nh4, sph);		
		//DNDC->nh43_equil(GN, temp, sph, nh4, nh3, q);
		//DNDC->nh3_volatilization(GN, temp, *flood_flag, wetland_flag, nh3, q, wind_speed, day_wfps, ice, day_soil_nh3, nh4, ps);

		/*float r_t = 0.05 * temp[GN];

		r_t = min(1.0, max(0.0, r_t));

		float vol_nh3 = urea[GN] * r_t;
		MData.day_house_nh3 += vol_nh3;
		urea[GN] -= vol_nh3;
		if (urea[GN] < 0.0) urea[GN] = 0.0;*/

	
		MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm,
								 soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, 
								 nh4, no3, no2, no, n2o, n2, nh3, 
								 urea, co2, sop,OrgP, LabP, ComP);
	}

}

#endif
