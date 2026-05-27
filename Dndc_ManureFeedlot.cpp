#include "stdafx.h"
#include "Dndcgo.h"
#include "RunPaths.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <stdlib.h>
#include <iostream>
#include "Swine.h"

#ifdef MANURE
extern class_manure MData;
class_manure *MUM;
CString AnimalName[7]={"","Dairy","Beef","Veal","Pig","Sheep","Poultry"};

void class_model::Main_Feedlot(int year, int scale, FILE* fout2, char *F_CLIMD,
							   float w_no2, float w_nh3, float w_no3, float w_nh4, 
							   float wurea, float day_clayn, float wpool_no,
							   int tilq, FILE* fCB, FILE* fNB, float w_n2, float litco22, float litco23, 
							   float till_fact, float *Tttoo, float ha, int Batch, 
							   int livestock, int q, char *PassL1, int FarmField, char *Pass, FILE* HSM,
							   float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc)
{
	char LAI[200], IndoorCliameFile[300], Zz[300];
	char F_LV1[150], DAYfarmgas[90], DAYfarmC[90], DAYfarmMR[90], F_LV2[150];
	char DAYpen[90], DAYhouse[90], DAYFeedOut[90];
	int m_FeedLots, fln, junkd, GN=0, FN=0, CNN=q+4, LNN=q+5, DNN=q+6;
	CString TotalFeedlots;
	FILE *TFL=NULL, *fLV1=NULL, *fLV4=NULL, *fday, *fLV2=NULL, *fLV3=NULL;
	FILE *fhouse=NULL, *fpen=NULL, *fgraze=NULL, *fcompost=NULL, *flagoon=NULL, *fdigester=NULL;
	FILE *ffarmgas=NULL, *ftreatgas=NULL, *ffarmC=NULL, *ffarmMR=NULL, *fFeedOut=NULL, *cm=NULL;
	
	TotalFeedlots.Format("%sResult\\Inputs\\TotalFeedLots_%d", ROOTDIR, year);
	TFL=fopen(TotalFeedlots, "r");
	if(TFL==NULL) note(0, TotalFeedlots);
	fscanf(TFL, "%d", &m_FeedLots);
	fclose(TFL);

	MData.yr_farm_to_compost_C=0.0; MData.yr_farm_to_lagoon_C=0.0; MData.yr_farm_to_digester_C=0.0; 
	MData.yr_farm_to_compost_N=0.0; MData.yr_farm_to_lagoon_N=0.0; MData.yr_farm_to_digester_N=0.0; 
	MData.yr_farm_to_compost_P=0.0; MData.yr_farm_to_lagoon_P=0.0; MData.yr_farm_to_digester_P=0.0; 
	MData.yr_farm_to_compost_H2O=0.0; MData.yr_farm_to_lagoon_H2O=0.0; MData.yr_farm_to_digester_H2O=0.0; 
	MData.yr_farm_to_field_C=0.0; MData.yr_farm_to_field_N=0.0; MData.yr_farm_to_field_P=0.0; MData.yr_farm_to_field_H2O=0.0; 

	for(fln=1; fln<=m_FeedLots; fln++) ////////////////////////////////////////////////////////////
	{
		initiation(0);

		FN = 1;

		//read in feedlot specifications
		sprintf(LAI,"%s\\ManureHouse_%d_%d.txt", INTER, year, fln);
		cm = fopen(LAI, "r");
		if(cm==NULL) note(0, LAI);

		fscanf(cm, "%d", &MData.EmpiricalModel[FN]);//use UCD empirical model calculating GHG and Manure
		fscanf(cm, "%d", &MData.FeedAdditive[FN]);//use FeedAdditive for CH4 mitigation
		fscanf(cm, "%f", &MData.FeedAdditiveRate[FN]);//use FeedAdditive for CH4 mitigation
	
		fscanf(cm, "%d", &MData.InputFormat[FN]);//reads wweather to use daily feed file , daily excretion file or nutrition model
		//MData.InputFormat[FN] = 0;
		if (MData.InputFormat[FN] == 1) fscanf(cm, "%s", MData.FeedFileName[FN]);//use daily feed file
		else if (MData.InputFormat[FN] == 2) fscanf(cm, "%s", MData.ExcretionFileName[FN]);//use daily excretion file
		else if (MData.InputFormat[FN] == 3)//use a nutrition model			
		{
/*			fscanf(cm, "%d", &MData.NutritionModel[FN]);
		
			Swine swine;

			wchar_t  input[255], output[255], table[255];
			swprintf(table, 255, L"%hsLibrary\\Lib_livestock\\SwineIngredientTable.csv", ROOTDIR);
			if (!fexists(table)){
				note(0, table);
			}

			if(MData.NutritionModel[FN]==5)
			{
				swprintf(output, 255, L"%hs\\sow_output.csv", OUTPUT);
				swprintf(input, 255, L"%hsLibrary\\Lib_input_examples\\Barn%d_sow_input.csv", ROOTDIR, fln);

				if (!fexists(input)){
					note(0, input);
				}

				int result = swine.RunSowModel(table, input, output);
				if (result != 1){
					note("Error running Swine Sow model.");
				}
			}
			else if(MData.NutritionModel[FN]==4)
			{
				swprintf(output, 255, L"%hs\\growth_output.csv", OUTPUT);
				swprintf(input, 255, L"%hsLibrary\\Lib_input_examples\\Barn%d_growth_input.csv", ROOTDIR, fln);
				
				if (!fexists(input)){
					note(0, input);
				}

				int result = swine.RunGrowthModel(table, input, output);
				if (result != 1){
					note("Error running Swine Growth model.");
				}
			}
*/
		}
		else
		{
			fscanf(cm, "%d", &MData.AnimalTypes[FN]);	
			MData.mm_TotalHeads[FN] = 0.0;
			fscanf(cm, "%d %f %f %f %f", &MData.mm_AnimalType[FN], &MData.mm_AnimalHeads[FN], 
					&MData.mm_FeedRate[FN], &MData.mm_FeedProtein[FN], &MData.mm_FeedTP[FN]);
			MData.mm_TotalHeads[FN] += MData.mm_AnimalHeads[FN];

			if(Option>100) 
			{
				MData.mm_FeedRate[FN] *= (1.0 + SMC[19]);
				MData.mm_FeedProtein[FN] *= (1.0 + SMC[20]);
				MData.mm_FeedTP[FN] *= (1.0 + SMC[21]);
				MData.mm_AnimalHeads[FN] *= (1.0 + SMC[46]);
			}

			//new Jia Deng
			fscanf(cm, "%f %f %f %f", &MData.mm_BodyWeight[FN], &MData.mm_DMFraction[FN],
				&MData.mm_MilkProtein[FN], &MData.mm_DayInMilk[FN]);
			fscanf(cm, "%f %f %f %f %f", &MData.mm_FeedNDFP[FN], &MData.mm_FeedADFP[FN],
				&MData.mm_FeedLigninP[FN], &MData.mm_FeedFATP[FN], &MData.mm_FeedASHP[FN]);

		}
		fscanf(cm, "%f %d", &MData.mm_GroundArea[FN], &MData.mm_GroundSurface[FN]);//0 slatted floor; 1 conrete floor; 2 sub-floor; 3 outdorr pen with bare soil
		fscanf(cm, "%d", &MData.mm_BedType);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
		fscanf(cm, "%f", &MData.mm_BedCNN);//C/N ratio
		fscanf(cm, "%f", &MData.mm_BedApplications);//days/application
		fscanf(cm, "%f", &MData.mm_BedAmount);//kg DM/application		
		fscanf(cm, "%d  %f  %s", &MData.mm_Ventilation, &MData.mm_VentRate, IndoorCliameFile);// 0 natural, 1 fan, -1 indoor climate file
		fscanf(cm, "%f", &MData.m_ManureRemoveFrequency[FN]);
		fscanf(cm, "%f %f %f %f %f", &MData.m_UC[FN], &MData.m_UL[FN], &MData.m_UD[FN], &MData.m_UF[FN], &MData.m_UR[FN]);
		fscanf(cm, "%f %f %f %f %f", &MData.m_FC[FN], &MData.m_FL[FN], &MData.m_FD[FN], &MData.m_FF[FN], &MData.m_FR[FN]);

		//Jia Deng was adding a 2nd lagoon here.
		fscanf(cm, "%d %f %f", &MData.m_Flash[FN], &MData.m_FlushWater[FN], &MData.LiquidFraction[FN]);//0 water; 1 urine; 2 None
		fclose(cm);

		if(MData.mm_GroundSurface[FN]==3) //outdoor pen
			MData.mm_Ventilation = -5;

		if(Option>100) 
		{
			MData.mm_GroundArea[FN] *= (1.0 + SMC[47]);
			MData.mm_BedAmount *= (1.0 + SMC[48]);
			MData.mm_BedCNN *= (1.0 + SMC[49]);
			MData.mm_VentRate *= (1.0 + SMC[50]);
			MData.m_ManureRemoveFrequency[FN] *= (1.0 + SMC[51]);
		}

		//open feedlot daily farmer record data file
		if(MData.InputFormat[1]==1) //use daily feed file
		{
			sprintf(F_LV1, "%s", MData.FeedFileName[1]);
			fLV1 = fopen(F_LV1, "r");
			if(fLV1==NULL) note(0, F_LV1);
			fgets(Zz, 200, fLV1);
			fgets(Zz, 200, fLV1);
		}

		if(MData.InputFormat[1]==2) //use daily excretion file
		{
			sprintf(F_LV1, "%s", MData.ExcretionFileName[1]);
			fLV1 = fopen(F_LV1, "r");
			if(fLV1==NULL) note(0, F_LV1);
			fgets(Zz, 200, fLV1);
			fgets(Zz, 200, fLV1);
		}

		if(MData.InputFormat[1]==3) 
		{
			if(MData.NutritionModel[1]==5)
				sprintf(F_LV1, "%s\\sow_output.csv", OUTPUT);

			if(MData.NutritionModel[1]==4)
				sprintf(F_LV1, "%s\\growth_output.csv", OUTPUT);

			fLV1 = fopen(F_LV1, "r");
			if(fLV1==NULL) 
			{
				AfxMessageBox("Can't open Swine model output.");
				note(0, F_LV1);
			}
			fgets(Zz, 200, fLV1);
			//fgets(Zz, 200, fLV1);
		}

		//open feedlot in-door climate data file
		if(MData.mm_Ventilation==-1)
		{
			fLV4 = fopen(IndoorCliameFile, "r");
			if(fLV4==NULL) note(0, IndoorCliameFile);
			fgets(Zz, 200, fLV4);
			fgets(Zz, 200, fLV4);
		}

		if(scale==0)
		{
			
			fday = fopen(F_CLIMD, "r");
			if (fday == NULL) note(0, F_CLIMD);
			
			sprintf(DAYFeedOut, "%s\\Day_FeedlotOutput_yr%d_lot%d.txt", INTER, year, fln);
			fFeedOut = fopen( DAYFeedOut, "w" );
			if ( fFeedOut == NULL ) note(1,DAYFeedOut);

			if(day_file==1)
			{
				if(Batch==0)
				{
					sprintf(DAYhouse, "%s\\Day_FeedlotManure_yr%d_lot%d.%s", Pass, year, fln, CSV);
					fhouse = fopen( DAYhouse, "w");
					if ( fhouse == NULL ) note(1,DAYhouse);

					sprintf(DAYfarmgas, "%s\\Day_FeedlotGases_yr%d_lot%d.%s", Pass, year, fln, CSV);
					ffarmgas = fopen( DAYfarmgas, "w" );
					if ( ffarmgas == NULL ) note(1,DAYfarmgas);

					sprintf(DAYfarmC, "%s\\Day_FeedlotNutrients_yr%d_lot%d.%s", Pass, year, fln, CSV);
					ffarmC = fopen( DAYfarmC, "w" );
					if ( ffarmC == NULL ) note(1,DAYfarmC);

					sprintf(DAYfarmMR, "%s\\Day_FeedlotManureRemove_yr%d_lot%d.%s", Pass, year, fln, CSV);
					ffarmMR = fopen( DAYfarmMR, "w" );
					if ( ffarmMR == NULL ) note(1,DAYfarmMR);					
				}
				else
				{
					sprintf(DAYhouse, "%s\\Day_FeedlotManure_yr%d_lot%d.%s", PassL1, year, fln, CSV);
					fhouse = fopen( DAYhouse, "w" );
					if ( fhouse == NULL ) note(1,DAYhouse);

					sprintf(DAYfarmgas, "%s\\Day_FeedlotGases_yr%d_lot%d.%s", PassL1, year, fln, CSV);
					ffarmgas = fopen( DAYfarmgas, "w");
					if ( ffarmgas == NULL ) note(1,DAYfarmgas);

					sprintf(DAYfarmC, "%s\\Day_FeedlotNutrients_yr%d_lot%d.%s", PassL1, year, fln, CSV);
					ffarmC = fopen( DAYfarmC, "w");
					if ( ffarmC == NULL ) note(1,DAYfarmC);

					sprintf(DAYfarmMR, "%s\\Day_FeedlotManureRemove_yr%d_lot%d.%s", PassL1, year, fln, CSV);
					ffarmMR = fopen( DAYfarmMR, "w");
					if ( ffarmMR == NULL ) note(1,DAYfarmMR);
				}
			}


			for(jday=1; jday<=365; jday++)
			{
				day_zero();//Read in Climate for manure sim

				fscanf(fday, "%d %f %f %f %f %f %f %f %f", &junkd, &air_temp, &max_temp, &min_temp, &precipitation, &PAR, &Day_Hrs, &wind_speed, &humidity);

				precipitation *= 0.01; //cm -> m
				rainfall = precipitation;

				DayPET = potential_et_manure();

				cwc = 1;

				MUM->ManureFeedlot(
					&FN, &GN, jday, fLV1, fLV4, fLV3, rcnrr, rcnh, rcnb, urea, 
					doc, rcvl, rcl, rcr, CRB1, CRB2, dphum, temp, air_temp, DayPET, 
					wind_speed,	day_wfps, soc, sph, &flood_flag, rcnrvl, rcnrl, WTL,
					day_WT, soil_ph, nh4, &ch4_prod, &ch4_day_oxid, &plant_day_ch4, q, rcnm, son, SIN,
					no3, no2, no, n2o, n2, nh3, ch4, TTT, newh, 
					&w_no2, &w_nh3, &w_no3, &w_nh4, &wurea, day_clayn, &wpool_no, DayFlux,tilq, fCB, 
					fNB, &w_n2o, &w_n2, seed, &day_ch4, anvf, WaterLeakRate, co2, clay,	LandUse, 
					FloDays, crhl, crhr, mmm, ocini, h, &day_C_mine, &day_N_mine, &day_N_assim,
					DClitter, &litco22, &litco23, st, DChumads, EFFAC, DChumus,	wetland_flag, ice, &day_soil_nh3, 
					lai, PlantTakeN, maxmn, leaf_water, cropht, base_nh3,day_N_demand, day_nup, day_fixN, day_DWater, 
					day_plant_nh3, &yr_NH3_deposit, plantn,clay_nh4, base_clay_N, max_clay_N,&wrcvl, &wrcl, &wrcr, &wcrb, 
					&wcrhl, &wcrhr, &whumus, &wtcavai,&day_ice_N, &day_ice_doc, &day_ice_n2o, &day_ice_n2, &IniSOC, &IniSON, &EndSON,
					day_runoff, &day_runoff_N, &day_clay_N, 
					dsno3, dsnh4, &dsnh3, &day_dsurea, &ds_doc, crop, yr_fixn, till_fact,
					sts, rainfall, O2_old, O2, vvv, ave_anvf, year, water, total_ice, day_rco2, flo_num,
					Eh, doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,
					doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, ManureAddCN, ManureDays, MicrobioIndex,
					RBO, FD, WaterControl, assim2, fldcap, by_passf, NIDay1, NIDay2,
					&day_soil_nitrify, &day_nitrify_NO, &day_nitrify_N2O, &day_soil_an_no,
					&day_soil_an_n2o, &day_soil_n2, Root_Wt, &day_soil_denitrification,
					R_Wt, vascularity, wiltpt, &day_addmc, &yr_addmc, &yr_addmn, &day_inManureN,
					&day_frostDOC, &yr_frostDOC, &winertC, inert_C, fert_flag, root_doc, 
					precipitation, manuFlag, irri_flag, FreezeDOC, day_O2, 
					&day_farm_to_field_N, &day_farm_to_field_C,&day_farm_to_field_H2O, RFM, SoilDepth,
					scale, &C_soil, sop, OrgP, LabP, ComP, AdsP, &day_farm_to_field_P, 
					fln, ch4_doc_pool, fFeedOut, humidity, min_temp, max_temp, PAR, F_methanogen,
					Tttoo, H2, day_ch4_CO2, day_ch4_1, day_ch4_2, Option, SMC, day_leach_water, 
					&pen_soil_wfps, SO4, sslope, day_root_resp, HSM, fertigate_flag,
					hrPE0, dby_flux, DroughtID, YieldToday, drc, ha, livestock, day_nitrification,
					day_denitrification, day_H2_prod, rno3, day_inRainN,denitMulti, nitMulti, N2N2OFactor, 0, manurePool, manurePoolCN, 
					UreaHydroInhibDays, UIDay1, UIDay2, newmanuPH, combinedpHDeep,manureHour,NH3Vol, manureCounter, day_nitrify_n2ol, day_denitrify_n2ol);//, &House_to_compost_C, &House_to_compost_N, &House_to_compost_H2O);

					MUM->Total_SOCSON(q+1, q+1, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
						 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,
						 OrgP, LabP, ComP);

					if(day_file==1)
					{
						MUM->write_dayManureProduction(fhouse, 1, q+1, jday, site, year, soc, doc,son, urea, nh4, no3, temp, day_wfps, 
							sph, water, q, sop, m_unit, Eh, pen_soil_wfps);

						MUM->write_out_dayFeedlotGas(ffarmgas, jday, site, year, q, day_wfps,sph,soc,son,urea,nh4,no3,doc,
							temp, water, nh3, day_soil_nh3, day_vol_nh3, day_soil_an_n2o, sop, m_unit);

						MUM->write_out_dayFarmCN(ffarmC, jday, site, year, m_unit);

						MUM->write_out_dayFarmManureRemove(ffarmMR, jday, site, year, m_unit);
					}
			
					annu_accumu_manure_house(jday);

			}//end of daily loop for feedlots
			fclose(fday);
			fclose(fFeedOut);

			if(day_file==1)
			{
				fclose( fhouse );
				fclose( ffarmC );
				fclose( ffarmMR );
				fclose( ffarmgas );
			}
			
			MData.yr_farm_to_compost_C += MData.yr_House_to_compost_C;
			MData.yr_farm_to_compost_N += MData.yr_House_to_compost_N;
			MData.yr_farm_to_compost_P += MData.yr_House_to_compost_P;
			MData.yr_farm_to_compost_H2O += MData.yr_House_to_compost_H2O;

			MData.yr_farm_to_lagoon_C += MData.yr_House_to_lagoon_C;
			MData.yr_farm_to_lagoon_N += MData.yr_House_to_lagoon_N;
			MData.yr_farm_to_lagoon_P += MData.yr_House_to_lagoon_P;
			MData.yr_farm_to_lagoon_H2O += MData.yr_House_to_lagoon_H2O;
			
			MData.yr_farm_to_digester_C += MData.yr_House_to_digester_C; 
			MData.yr_farm_to_digester_N += MData.yr_House_to_digester_N; 
			MData.yr_farm_to_digester_P += MData.yr_House_to_digester_P;  
			MData.yr_farm_to_digester_H2O += MData.yr_House_to_digester_H2O;  

			MData.yr_farm_to_field_C += MData.yr_House_to_field_C;  
			MData.yr_farm_to_field_N += MData.yr_House_to_field_N;
			MData.yr_farm_to_field_P += MData.yr_House_to_field_P;
			MData.yr_farm_to_field_H2O += MData.yr_House_to_field_H2O; 

			
			//if(MData.InputFormat[1]==1||MData.InputFormat[1]==2||MData.InputFormat[1]==3) fclose(fLV1);
			//if(MData.mm_Ventilation==-1) fclose(fLV4);

/*			MData.yr_House_to_compost_N = MUM->Total_SOCSON(CNN, CNN, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
							 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
			
			MData.yr_House_to_compost_C = MData.ttc;
			MData.yr_House_to_compost_P = MData.ttp;
			MData.yr_House_to_compost_H2O = water[1][CNN]; 
			
			MData.yr_House_to_lagoon_N = MUM->Total_SOCSON(LNN, LNN, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
							 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
		
			MData.yr_House_to_lagoon_C = MData.ttc;
			MData.yr_House_to_lagoon_P = MData.ttp;
			MData.yr_House_to_lagoon_H2O = water[1][LNN];

			MData.yr_House_to_digester_N = MUM->Total_SOCSON(DNN, DNN, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
							 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
		
			MData.yr_House_to_digester_C = MData.ttc;
			MData.yr_House_to_digester_P = MData.ttp;
			MData.yr_House_to_digester_H2O = water[1][DNN];
*/
			if(FarmField==1)
				write_out_annual_report_feedlot(scale, 1, ha, Batch, livestock, fout2, fln);
			
		}//end of if scale=0
		
		if(MData.InputFormat[1]==1||MData.InputFormat[1]==2||MData.InputFormat[1]==3) fclose(fLV1);
		if(MData.mm_Ventilation==-1) fclose(fLV4);

	}//end of feedlots loop

	//AfxMessageBox("!!!");
	
}

int class_model::write_out_annual_report_feedlot(int MODE, int FarmPart, float ha, int Batch, 
												int livestock, FILE *fout2, int Feedlot)
{
	float YrLeachNO3=0;

	///////////////////////////////////////////////////////////////////////////////////////////
	MData.yr_milk_water = MData.yr_milk_product - MData.yr_milk_C - MData.yr_milk_N;	
	float yr_meat_water = MData.yr_meat_C / 0.2;
	float yr_intake_water = MData.yr_urine_water + MData.yr_dung_water + MData.yr_milk_water + yr_meat_water;
	float _ha=MData.ManureFieldArea, ttn;
	float FIC = MData.yr_Lagoon_to_field_C+MData.yr_Compost_to_field_C+MData.yr_digester_to_field_C+(yr_addtc+yr_addrc)*_ha;
	float FOC = (yr_soil_co2)*_ha+yr_ch4*_ha;
	float DFC = FIC - FOC;
	float FIN = MData.yr_Lagoon_to_field_N+MData.yr_Compost_to_field_N+MData.yr_digester_to_field_N+yr_rainN*_ha+(yr_sln)*_ha+yr_addfer*_ha+yr_irri_N*_ha;
	float FON = yr_soil_nh3*_ha+yr_dnn2o*_ha+yr_dnno*_ha+yr_dnn2*_ha+(yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3])*_ha+YrLeachNO3*_ha;
	float DFN = FIN - FON;
	float DFW = yr_dSoilWater*10000.0*_ha*1000.0;

	if(Feedlot==1)
	{
		fprintf(fout2, "ANNUAL_REPORT: C,_N,_P_and_water_fluxes_in_livestock_operation_system\n");
		fprintf(fout2, "---------------------------------------------------------------------------------------------------\n");
		fprintf(fout2, "FARM:%-s\n",site);
		fprintf(fout2, "YEAR:%d\n",	year);
	}
	
	//%e or %15.0f

	fprintf(fout2, "---------------------------------------------------------------------------------------------------\n");
	fprintf(fout2, "\nFEEDLOT:%d\n", Feedlot);
	fprintf(fout2, "HERD:type:%s; heads:%.0f\n", AnimalName[MData.mm_AnimalType[1]], MData.mm_AnimalHeads[1]);
	fprintf(fout2, "FEED:rate:%.2f_kg_DM/head/day; crude_protein:%.2f_percent; P:%.2f_percent\n", MData.mm_FeedRate[1], MData.mm_FeedProtein[1], MData.mm_FeedTP[1]);
	fprintf(fout2, "---------------------------------------------------------------------------------------------------\n");
	fprintf(fout2, "FEEDLOT_%d                 %15s    %15s     %15s    %15s\n\n", Feedlot, "C_kg", "N_kg", "Water_kg", "P_kg");
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Feed_intake", MData.yr_intake_C, MData.yr_intake_N, yr_intake_water, MData.yr_intake_P);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Bedding_input", MData.yr_bed_C, MData.yr_bed_N, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Flushing_input", 0.0, 0.0, MData.yr_flush_H2O, 0.0);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Milk_production", MData.yr_milk_C, MData.yr_milk_N, MData.yr_milk_water, MData.yr_milk_P);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Meat_production", MData.yr_meat_C, MData.yr_meat_N, yr_meat_water, MData.yr_meat_P);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Animal_CO2_respiration", MData.yr_enteric_co2, 0.0, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Enteric_CH4_emission", MData.yr_enteric_ch4, 0.0, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Enteric_N2O_emission", 0.0, MData.yr_enteric_n2o, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Urine_excretion", MData.yr_urine_C, MData.yr_urine_N, MData.yr_urine_water, MData.yr_urine_P);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Feces_excretion", MData.yr_dung_C, MData.yr_dung_N, MData.yr_dung_water, MData.yr_dung_P);


	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Floor_CO2_emission", MData.yr_house_co2, 0.0, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Floor_CH4_emission", MData.yr_house_ch4, 0.0, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Floor_NH3_emission", 0.0, MData.yr_house_nh3, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Floor_N2O_emission", 0.0, MData.yr_house_n2o, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Floor_NO_emission", 0.0, MData.yr_house_no, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Floor_N2_emission", 0.0, MData.yr_house_n2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Floor_evaporation", 0.0, 0.0, MData.yr_house_evap, 0.0);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Export_to_compost", MData.yr_House_to_compost_C, MData.yr_House_to_compost_N, MData.yr_House_to_compost_H2O, MData.yr_House_to_compost_P);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Export_to_lagoon", MData.yr_House_to_lagoon_C, MData.yr_House_to_lagoon_N, MData.yr_House_to_lagoon_H2O, MData.yr_House_to_lagoon_P);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Export_to_digester", MData.yr_House_to_digester_C, MData.yr_House_to_digester_N, MData.yr_House_to_digester_H2O, MData.yr_House_to_digester_P);
	float ttn1=MData.Total_SOCSON(q+1, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, 
								 co2, sop,OrgP, LabP, ComP);
	float ttc1 = MData.ttc;
	float ttp1 = MData.ttp;

	float ttn8=MData.Total_SOCSON(q+8, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
								 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, 
								 co2, sop,OrgP, LabP, ComP);
	float ttc8 = MData.ttc;
	float ttp8 = MData.ttp;
	
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Remain_in_barn", ttc1+ttc8, ttn1+ttn8, water[1][q+1]+water[1][q+8], ttp1+ttp8);
	
	//fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Remain_in_gutter", ttc8, ttn8, water[1][q+8], ttp8);

	return(0);
}

#endif