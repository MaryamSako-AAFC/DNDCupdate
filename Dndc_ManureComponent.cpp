#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE
//#ifdef FACILITY

extern class_manure MData;
class_manure *MWM;

float till_fact, w_no2, w_nh3, w_n2o, w_n2, ttoo[90];
float w_no3, w_nh4, wurea, wpool_no, OverT, wpool_no2, day_clayn;
float litco22, litco23, DM_CN, pH, Removal_percent;
FILE *LClim, *LMan, *OutClim, *fNB=NULL, *fCB=NULL;
char WW[200], jss[50];
int i, junkd, tilq;

void class_model::FarmFacilityCompost(FILE* HSM, float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc)
{
	q=10;
	float CompostSolidC, CompostWater, CompostSolidN, CompostLiquidNH4, CompostLiquidNO3, CompostPH, CompostSolidP, CompostDM; 
	int FN=4, GN=q+4, k=0, CompostCover=0, CompostSet, jdayb;
	char FarmClimName[500], FarmManaName[500], DAYCompost[300];

	CString FCF;
	FILE *fcf, *fcompost;
	
	FCF.Format("C:\\%s\\FarmCompostPara", INTER);
		fcf=fopen(FCF, "r");
		if(fcf==NULL) note(0, FCF);
		fscanf(fcf, "%s",  FarmClimName);
		fscanf(fcf, "%s",  FarmManaName);
		fscanf(fcf, "%d %f %f %f",  &CompostCover, &latitude, &MData.m_CompostPoro, &MData.m_CompostPH);
		fclose(fcf);

		//soil data
		clay[1] = 0.05;
		st[GN] = 2;
		sts[GN] = MData.m_CompostPoro;
		sph[GN] = MData.m_CompostPH;
		DClitter = 1.0;
		DChumads = 1.0;
		DChumus = 1.0;
		rcnrvl = 5.0;
		rcnrl = 25.0;
		rcnrr = 100.0;
		rcnb = 10.0;
		rcnh = 10.0;
		rcnm = 10.0;
		rcnh = 10.0;
		PassiveCCN = 500.0;
		MicrobioIndex = 1.0;
			
		initiation(2);
	
		read_in_clim(0);
		read_in_climy(0, 0, 0);	

		char FWF[300];
		sprintf(FWF, "%s\\Inputs\\%s", OUTPUT, climd[0]);

		OutClim = fopen(FWF, "r");
		if(OutClim==NULL) note(0, FWF);
				
		LMan = fopen(FarmManaName, "r");
		if(LMan==NULL) note(0, FarmManaName);
		fgets(WW, 500, LMan);
		fgets(WW, 500, LMan);
		
		sprintf(DAYCompost, "%s\\Record\\Site\\Facility_Compost.csv", OUTPUT);
		fcompost = fopen(DAYCompost, "w" );
		if ( fcompost == NULL ) note(1,DAYCompost);

		for(int i=1; i<=365; i++)
		{	
			day_zero();

			fscanf(OutClim, "%d %f %f %f %f %f %f %f %f", &jday, &air_temp, &max_temp, &min_temp, &precipitation, &PAR, &Day_Hrs, &wind_speed, &humidity);

			rainfall = precipitation * 0.01;//cm -> m

			fscanf(LMan, "%d %d %f %f %f %f %f %f %f", 
				&jdayb, &CompostSet, &CompostDM, &CompostSolidC, &CompostSolidN, &CompostSolidP, &CompostWater, &CompostLiquidNH4, &CompostLiquidNO3);
					
			if(jday!=jdayb)
			{
				CString ENote;
				ENote.Format("Error on day %d in file %s", jday, FarmManaName);
				AfxMessageBox(ENote);
			}

			//Load compost 
			if(CompostSet==1)
			{	
				float CompostSolidCN = CompostSolidC / CompostSolidN;

				if(CompostSolidCN <= rcnh)
				{
					rcvl[GN] += 0.0;
					rcl[GN] += 0.0;
					rcr[GN] += 0.0;
					CRB1[GN] += CompostSolidC * 0.05;
					CRB2[GN] += CompostSolidC * 0.05;
					crhl[GN] += CompostSolidC * 0.25;
					crhr[GN] += CompostSolidC * 0.25;
					dphum[GN] += CompostSolidC * 0.4;

					float CompostHumusN = CompostSolidC / rcnh;

					if(CompostSolidN > CompostHumusN) nh4[GN] += (CompostSolidN - CompostHumusN);					
				}
				else
				{
					float CompostHumusN = 0.5 * CompostSolidN;
					float CompostHumusC = CompostHumusN * rcnh;
					float CompostLitterC = CompostSolidC - CompostHumusC;
					float CompostLitterN = 0.5 * CompostSolidN; 
					float CompostLitterCN = CompostLitterC / CompostLitterN;

					float AddCN, AddC, oz, AddC1, AddC2, AddC3, dInertC;
					AddCN = CompostLitterCN;
					AddC = CompostLitterC;
					alloc_litter_into_pools(&AddCN, &AddC, oz, &AddC1, &AddC2, &AddC3, &dInertC, 1, rcnrvl, rcnrl, rcnrr, nh4);
			
					rcvl[GN] += AddC1;
					rcl[GN] += AddC2;
					rcr[GN] += AddC3;
					CRB1[GN] += CompostHumusC * 0.05;
					CRB2[GN] += CompostHumusC * 0.05;
					crhl[GN] += CompostHumusC * 0.25;
					crhr[GN] += CompostHumusC * 0.25;
					dphum[GN] += CompostHumusC * 0.4;
				}
			
				co2[GN] += 0.0;
				doc[GN]  += 0.0;
				sph[GN] = CompostPH;			
				water[1][GN] += CompostWater;					
				nh4[GN] += CompostLiquidNH4;
				urea[GN] += 0.0;
				no3[GN] += CompostLiquidNO3;				
				no2[GN] += 0.0;
				no[GN] += 0.0;
				n2o[GN] += 0.0;
				n2[GN] += 0.0;
				nh3[GN] += 0.0;	
				
				OrgP[GN] += 0.0;
				LabP[GN] += 0.0;
				ComP[GN] += 0.0;

				temp[GN] = air_temp;
				day_wfps[GN] = 0.5;
				Eh[GN] = 300.0;
			
				h[1] = 0.02;

				//for(int j=1; j<=5; j++) MData.CompostT[j] = air_temp;
				//MData.m_LagoonCover = m_CompostMethod;						
			}

			//Compost biogeochemistry
			float Lsoc = MWM->Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

			//soc[GN] = rcvl[GN] + rcl[GN] + rcr[GN] + CRB1[GN] + CRB2[GN] + crhl[GN] + crhr[GN] + dphum[GN] + co2[GN] + doc[GN];
			ttoo[GN] = 0.5;

			if(soc[GN]>0.0)
			{
				k++;

				if(CompostSet==3)
				{
					Eh[GN] = 300.0;
				}

				//Daily biogeochemical reactions
				float mRBO, mFD;

				if(k==1) temp[GN] = air_temp;

				DayPET = potential_et_manure();//m water/day
						
				int scale=0, Batch=0;
				int livestock = 1;
				float ha=0.0;
				FILE *fout2=NULL;
				char Pass[300];
				//float manco2;//added this to handle manure
				MWM->compost_BGC(
					FN, GN, q, jday, rcnrvl, rcnrl, rcnrr, rcnh, rcnb, urea, //10
					doc, rcvl, rcl, rcr, CRB1, CRB2, dphum, temp, air_temp, DayPET, //20
					wind_speed, day_wfps, soc, sph, &flood_flag, WTL, day_WT, soil_ph, nh4, &ch4_prod, //30
					&ch4_day_oxid, &plant_day_ch4, rcnm, son, SIN, no3, no2, no, n2o, n2, 	//40				
					nh3, ch4, TTT, newh, &w_no2, &w_nh3, &w_no3, &w_nh4, &wurea, day_clayn, //50
					&wpool_no, DayFlux, tilq, fCB, fNB, &w_n2o, &w_n2, seed, &day_ch4, //60
					anvf, WaterLeakRate, co2, clay, LandUse, FloDays, crhl, crhr, mmm, ocini, //70
					h, &day_C_mine, &day_N_mine, &day_N_assim, DClitter, &litco22, &litco23, st, DChumads, EFFAC, //80
					DChumus, wetland_flag, ice, &day_soil_nh3, lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3, //90
					day_N_demand, day_nup, day_fixN, day_DWater, day_plant_nh3, &yr_NH3_deposit, plantn, clay_nh4, base_clay_N, max_clay_N,//100
					&wrcvl, &wrcl, &wrcr, &wcrb, &wcrhl, &wcrhr, &whumus, &wtcavai,	&day_ice_N, &day_ice_doc, //110
					&day_ice_n2o, &day_ice_n2, &IniSOC, &IniSON, &EndSON, day_runoff, &day_runoff_N, &day_clay_N, dsno3, dsnh4, //120
					&dsnh3, &day_dsurea, &ds_doc, crop, yr_fixn, till_fact, sts, rainfall, O2_old, O2, //130
					vvv, ave_anvf, year, water, total_ice, day_rco2, flo_num, Eh, doc_w, nh4_w, no3_w, //140
					no2_w, no_w, n2o_w, n2_w, doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, //150
					ttoo, ManureAddCN, ManureDays, MicrobioIndex, RBO, FD, WaterControl, assim2, fldcap, by_passf,//160 
					NIDay1, NIDay2, &day_soil_nitrify, &day_nitrify_NO, &day_nitrify_N2O, &day_soil_an_no, &day_soil_an_n2o, &day_soil_n2, Root_Wt, &day_soil_denitrification,//170
					R_Wt, vascularity, wiltpt, &day_frostDOC, &yr_frostDOC, &winertC, inert_C, fert_flag, root_doc, //180
					precipitation, manuFlag, irri_flag, FreezeDOC, day_O2, RFM, SoilDepth, sop, //190
					OrgP, LabP, ComP, AdsP, LateralInflux, drain_flag, day_leach_water, CompostCover, HSM, fertigate_flag,
					hrPE0, dby_flux, DroughtID, YieldToday, drc, scale, ha, livestock, day_nitrification,
					day_denitrification, 0, manurePool, manurePoolCN,rno3, day_inRainN,denitMulti, nitMulti, N2N2OFactor, manureHour, manureCounter, UreaHydroInhibDays, UIDay1, UIDay2,  newmanuPH, combinedpHDeep,NH3Vol, day_nitrify_n2ol, day_denitrify_n2ol);
				
				Eh[GN] -= (co2[GN] / 500.0);

				MData.day_compost_co2 = co2[GN];
				co2[GN] = 0.0;
			}
			else//empty lagoo
			{

			}

			//MWM->write_out_dayCompost(fcompost, jday, temp, nh4, no3, nh3, son, urea,
			//		"site", 1, q, soc, water, no2, no, n2o, n2, sop, 0, doc);

			MWM->write_out_dayCompost(fcompost, jday, "site", year, q, 
					day_wfps,sph,soc,son,urea,nh4,no3,doc,temp, water, nh3, sop, 0);

			//Remove compost
			if(CompostSet==3)
			{
				rcvl[GN] = 0.0;
				rcl[GN] = 0.0;
				rcr[GN] = 0.0;
				CRB1[GN] = 0.0;
				CRB2[GN] = 0.0;
				crhl[GN] = 0.0;
				crhr[GN] = 0.0;
				dphum[GN] = 0.0;
				co2[GN] = 0.0;
				doc[GN]  = 0.0;
			
				water[1][GN] = 0.0;			
				
				nh4[GN] = 0.0;
				urea[GN] = 0.0;
				no3[GN] = 0.0;			
				no2[GN] = 0.0;
				no[GN] = 0.0;
				n2o[GN] = 0.0;
				n2[GN] = 0.0;
				nh3[GN] = 0.0;	
				
				OrgP[GN] = 0.0;
				LabP[GN] = 0.0;
				ComP[GN] += 0.0;

				temp[GN] = 0.0;
				day_wfps[GN] = 0.0;
				MData.day_lagoon_co2 = 0.0;
				MData.day_lagoon_ch4 = 0.0;
				MData.day_lagoon_nh3 = 0.0;
				MData.day_lagoon_n2o = 0.0;
				MData.day_lagoon_no = 0.0;
				MData.day_lagoon_n2 = 0.0;
			}

		}//daily loop
		fclose(OutClim);
		fclose(LMan);
		fclose(fcompost);

		AfxMessageBox("Compost simulation is done");
		
		//exit(0);
}

void class_model::FarmFacilityLagoon()
{
	char FarmLagoonClim[500], FarmLagoonManage[500], FarmClimFile[500], DAYlagoon[300];
	float m_SurfaceArea, m_capacity, lagoon_temp;
	float SlurryDM, DM_CN, SlurryDOC, SlurryUrea, SlurryNH4, SlurryNO3, SlurryWater;
	float disturbance=0.0, dist=0.0;
		
	q=10;
	int FN=5, GN=q+5;
		
		CString FCF;
		FILE *fcf, *flagoon;
		FCF.Format("C:\\%s\\FarmLagoonPara", INTER);
		fcf=fopen(FCF, "r");
		if(fcf==NULL) note(0, FCF);
		fscanf(fcf, "%s",  FarmClimFile);
		fscanf(fcf, "%s",  FarmLagoonClim);
		fscanf(fcf, "%s",  FarmLagoonManage);
		fscanf(fcf, "%d %f %f %f",  &MData.m_LagoonCover, &m_SurfaceArea, &m_capacity, &latitude);
		fclose(fcf);

		MData.m_LagoonSurfaceArea = m_SurfaceArea;
		MData.m_LagoonCapacity = m_capacity;
	
		//soil data
		clay[1] = 0.05;
		st[GN] = 2;
		DClitter = 1.0;
		DChumads = 1.0;
		DChumus = 1.0;
		rcnrvl = 5.0;
		rcnrl = 25.0;
		rcnrr = 100.0;
		rcnb = 10.0;
		rcnh = 10.0;
		rcnm = 10.0;
		rcnh = 10.0;
		PassiveCCN = 500.0;
			
		initiation(2);
	
		read_in_clim(0);
		read_in_climy(0, 0, 0);	

		char FWF[300];
		sprintf(FWF, "%s\\Inputs\\%s", OUTPUT, climd[0]);

		OutClim = fopen(FWF, "r");
		if(OutClim==NULL) note(0, FWF);
		//fgets(WW, 500, OutClim);	
		
		LClim = fopen(FarmLagoonClim, "r");
		if(LClim==NULL) note(0, FarmLagoonClim);
		fgets(WW, 500, LClim);	
		fgets(WW, 500, LClim);	

		LMan = fopen(FarmLagoonManage, "r");
		if(LMan==NULL) note(0, FarmLagoonManage);
		fgets(WW, 500, LMan);
		fgets(WW, 500, LMan);
		
		sprintf(DAYlagoon, "%s\\Record\\Site\\Facility_Lagoon.csv", OUTPUT);
		flagoon = fopen( DAYlagoon, "w" );
		if ( flagoon == NULL ) note(1,DAYlagoon);

		for(int i=1; i<=365; i++)
		{
			float SlurryHumads=0.0, SlurryLitter=0.0, SlurryC=0.0, SlurryN=0.0, SlurryUrea=0.0; 

			day_zero();
			//fscanf(OutClim, "%d %f %f %f", &jday, &max_temp, &min_temp, &precipitation);//degree C, cm water
			fscanf(OutClim, "%d %f %f %f %f %f %f %f %f", 
				&jday, &air_temp, &max_temp, &min_temp, &precipitation, &PAR, &Day_Hrs, 
				&wind_speed, &humidity);

			rainfall = precipitation * 0.01;//cm -> m

			fscanf(LClim, "%d %f %f", &jday, &lagoon_temp, &wind_speed);//degree C, m/s

			//temp[GN] = lagoon_temp;
			//air_temp = lagoon_temp;
			//yr_avetj = lagoon_temp;		
			
			fscanf(LMan, "%d %f %f %f %f %f %f %f %f %f %f", 
				&jday, &SlurryDM, &DM_CN, &SlurryDOC, &SlurryUrea, &SlurryNH4, 
				&SlurryNO3, &SlurryWater, &pH, &Removal_percent, &dist);//

			if(dist>0.0) disturbance = dist;
			else
			{
				disturbance -= 0.05;
				if(disturbance<0.0) disturbance = 0.0;
			}


			sph[GN] = 8.5;			
			day_wfps[GN] = 1.0;
			Eh[GN] = -300.0;
			h[1] = 0.02;

/*			if(MData.m_LagoonCover==1)//air open
				temp[GN] = lagoon_temp * 0.2 + air_temp * 0.8;
			else if(MData.m_LagoonCover==2)//sheltered
				temp[GN] = lagoon_temp * 0.9 + air_temp * 0.1;
			if(MData.m_LagoonCover==3)//covered
				temp[GN] = lagoon_temp * 1.0 + air_temp * 0.0;
			else {}*/

			//temp[GN] = lagoon_temp;

			//Update slurry composition due to load
			if(SlurryDM>0.0)
			{	
				SlurryC = SlurryDM * 0.58;//kg C
				SlurryN = SlurryC / DM_CN;

				if(DM_CN >= rcnh)
				{
					SlurryHumads = (SlurryN - SlurryC / rcnrr) / (1.0/rcnh - 1.0/rcnrr);
					SlurryLitter = SlurryC - SlurryHumads;
					SlurryUrea = 0.0;
				}
				else
				{
					SlurryHumads = SlurryC;
					SlurryLitter = 0.0;
					SlurryUrea = SlurryN - SlurryC / rcnh;
				}
		
				urea[GN] += SlurryUrea;
				rcr[GN] += SlurryLitter;
				CRB1[GN] += SlurryHumads * 0.05;
				CRB2[GN] += SlurryHumads * 0.05;
				crhl[GN] += SlurryHumads * 0.25;
				crhr[GN] += SlurryHumads * 0.25;
				dphum[GN] += SlurryHumads * 0.4;
				
				rcvl[GN] += 0.0;
				rcl[GN] += 0.0;
				rcr[GN] += 0.0;				
				co2[GN] += 0.0;
				doc[GN]  += SlurryDOC;
				day_DOC_prod += SlurryDOC;
			}
							
			nh4[GN] += SlurryNH4;
			urea[GN] += SlurryUrea;
			no3[GN] += SlurryNO3;				
			no2[GN] += 0.0;
			no[GN] += 0.0;
			n2o[GN] += 0.0;
			n2[GN] += 0.0;
			nh3[GN] += 0.0;	
				
			OrgP[GN] += 0.0;
			LabP[GN] += 0.0;
			ComP[GN] += 0.0;

			water[1][GN] += SlurryWater;//kg water
			day_wfps[GN] = 1.0;
			
			MData.House_to_lagoon_C = SlurryC + SlurryDOC;
			MData.House_to_lagoon_N = SlurryNH4 + SlurryUrea + SlurryNO3 + SlurryN;
			MData.House_to_lagoon_H2O = SlurryWater;
			MData.House_to_lagoon_P = 0.0;


			/*	

				for(int j=1; j<=5; j++) MData.LagoonT[j] = lagoon_temp;
						*/				
			//}

			

			float Lsoc = MWM->Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

			//soc[GN] = rcvl[GN] + rcl[GN] + rcr[GN] + CRB1[GN] + CRB2[GN] + crhl[GN] + crhr[GN] + dphum[GN] + co2[GN] + doc[GN];
	
			if(soc[GN]>0.0)
			{
				//Daily biogeochemical reactions
				float mRBO, mFD;

				temp[GN] = lagoon_temp;

				MData.lagoon_days++;

				DayPET = potential_et_manure();
					
				MWM->lagoon_BGC(FN, GN, q, jday, rcnrvl, rcnrl, rcnrr, rcnh, rcnb, 
					urea, doc,//11 
					rcvl, rcl, rcr, CRB1, CRB2, dphum, temp, air_temp, //19
					DayPET, wind_speed, day_wfps, soc, sph, &flood_flag, WTL, day_WT,//27 
					soil_ph, nh4, &ch4_prod, &ch4_day_oxid, &plant_day_ch4, rcnm, son, SIN, no3, no2,//37 
					no, n2o, n2, nh3, ch4, TTT, newh, &w_no2, &w_nh3,//46 
					&w_no3, &w_nh4, &wurea, day_clayn, &wpool_no, DayFlux, tilq,//53  
					fCB, fNB, &w_n2o, &w_n2, seed, &day_ch4, anvf, WaterLeakRate, co2, clay, LandUse, FloDays,//65
					crhl, crhr, mmm, ocini, h, &day_C_mine, &day_N_mine, &day_N_assim, DClitter,//74
					&litco22, &litco23, st, DChumads, EFFAC, DChumus, wetland_flag, ice, &day_soil_nh3,//83
					lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3, day_N_demand, day_nup, day_fixN, day_DWater,//93
					day_plant_nh3, &yr_NH3_deposit, plantn, clay_nh4, base_clay_N, max_clay_N,//99
					&wrcvl, &wrcl, &wrcr, &wcrb, &wcrhl, &wcrhr,& whumus, &wtcavai,//107
					&day_ice_N, &day_ice_doc, &day_ice_n2o, &day_ice_n2, &IniSOC, &IniSON, //113
					&EndSON, day_runoff, &day_runoff_N, &day_clay_N,//117 
					dsno3, dsnh4, &dsnh3, &day_dsurea, &ds_doc, crop, yr_fixn, till_fact,//125
					sts, rainfall, O2_old, O2, vvv, ave_anvf, year, water, total_ice, day_rco2, flo_num, Eh,//137
					doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,//144
					doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, ttoo, ManureAddCN, ManureDays, MicrobioIndex,//154
					mRBO, mFD, WaterControl, assim2, fldcap, by_passf, NIDay1, NIDay2,//162
					&day_soil_nitrify, &day_nitrify_NO, &day_nitrify_N2O, &day_soil_an_no,//166
					&day_soil_an_n2o, &day_soil_n2, Root_Wt, &day_soil_denitrification,//170
					R_Wt, vascularity, &winertC, inert_C, fert_flag, root_doc, //177
					day_O2, RFM, SoilDepth, wiltpt, &day_frostDOC, &yr_frostDOC, precipitation,manuFlag, irri_flag, //187
					FreezeDOC, sop, OrgP, LabP, ComP, AdsP, LateralInflux, drain_flag, day_leach_water, 555,
					m_capacity, disturbance, 0, manurePool, manurePoolCN, UreaHydroInhibDays, UIDay1, UIDay2, newmanuPH, combinedpHDeep,manureHour,NH3Vol,manureCounter,
					max_temp, maxAnnualTemp, min_temp, yr_avetj, oldLayerDepth, lagoonTempPartition, &lagoon_snowpack, &lagoon_SnowMelt, lagoon_snowfall, DayPETRN, lagoon_ice, latitude,humidity);

				MData.day_lagoon_co2 = co2[GN];
				co2[GN] = 0.0;
				
			}
			else//empty lagoo
			{
				temp[GN] = lagoon_temp;
				MData.lagoon_days = 0;
				MData.LagoonT[1] = 0.0;
				MData.LagoonT[2] = 0.0;
				MData.LagoonT[3] = 0.0;
				MData.LagoonT[4] = 0.0;
				MData.LagoonT[5] = 0.0;
				//not sure if necessary
				/*
					MData.LagoonT[6]=0.0;
				MData.LagoonT[7]=0.0;
				MData.LagoonT[8]=0.0;
				MData.LagoonT[9]=0.0;
				MData.LagoonT[10]=0.0;
				MData.LagoonT[11]=0.0;
				MData.LagoonT[12]=0.0;
				MData.LagoonT[13]=0.0;
				MData.LagoonT[14]=0.0;
				MData.LagoonT[15]=0.0;
				MData.LagoonT[16]=0.0;
				MData.LagoonT[17]=0.0;
				MData.LagoonT[18]=0.0;
				MData.LagoonT[19]=0.0;
				MData.LagoonT[20]=0.0;
				MData.LagoonT[21]=0.0;
				*/
			}

			float Lsoc2 = MWM->Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

			MWM->write_out_dayLagoon(flagoon, jday, lagoon_temp, nh4, no3, nh3, son, urea,
					"site", 1, q, soc, water, no2, no, n2o, n2, sop, 0, doc, MData.LagoonT, air_temp, &lagoon_snowpack, lagoon_ice);

			if(Removal_percent>0.0)
			{
				rcvl[GN] = 0.0;
				rcl[GN] = 0.0;
				rcr[GN] = 0.0;
				CRB1[GN] = 0.0;
				CRB2[GN] = 0.0;
				crhl[GN] = 0.0;
				crhr[GN] = 0.0;
				dphum[GN] = 0.0;
				co2[GN] = 0.0;
				doc[GN]  = 0.0;
			
				water[1][GN] = 0.0;			
				
				nh4[GN] = 0.0;
				urea[GN] = 0.0;
				no3[GN] = 0.0;			
				no2[GN] = 0.0;
				no[GN] = 0.0;
				n2o[GN] = 0.0;
				n2[GN] = 0.0;
				nh3[GN] = 0.0;	
				
				OrgP[GN] = 0.0;
				LabP[GN] = 0.0;
				ComP[GN] += 0.0;

				temp[GN] = 0.0;
				day_wfps[GN] = 0.0;
				MData.day_lagoon_co2 = 0.0;
				MData.day_lagoon_ch4 = 0.0;
				MData.day_lagoon_nh3 = 0.0;
				MData.day_lagoon_n2o = 0.0;
				MData.day_lagoon_no = 0.0;
				MData.day_lagoon_n2 = 0.0;
				MData.LagoonCrustC = 0.0;
			}

		}//daily loop
		fclose(OutClim);
		fclose(LClim);
		fclose(LMan);
		fclose(flagoon);

		
}



//#endif
#endif