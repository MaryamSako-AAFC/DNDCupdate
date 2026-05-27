#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <math.h>

void class_model::CheckBalance(int ttmm)
{
	float prof_GasN, prof_AssimN=0.0, prof_fluxN;
	float prof_NO2, prof_NO3, prof_ocini_N;
	float prof_NH3, prof_NO, prof_N2O, prof_N2, prof_urea;
	float prof_RCVL_N, prof_RCL_N, prof_RCR_N;
	float prof_crb1_N, prof_crb2_N, prof_crh_N;
	float prof_HUMUS_N, prof_CO2, prof_CO2flux, prof_CH4;
	float prof_MICRO, prof_RCVL, prof_RCL, prof_RCR, prof_crb1;//, prof_RootLitter;
	float prof_crb2, prof_crhl, prof_crhr, prof_HUMUS, prof_NH4;
	float prof_FluxNO, prof_FluxN2O, prof_FluxN2, prof_FluxNH3, prof_LeachN;
	float prof_UptakeN, prof_FertilizerN, prof_LitterN, prof_IrriN, prof_SoilFixN;
	float prof_LitterC, prof_ManureC, prof_RootDOC, prof_CH4flux, prof_LeachC, prof_ocini, prof_RainN;//, prof_RootLitterN;
	float prof_InertC, prof_SurfaceLitter, prof_FreezeDOC, prof_CH4C;
	float prof_NH4HCO3 = 0.0;//new

	prof_DOC=0.0;
	prof_CO2=0.0;
	prof_CH4 = 0.0;
	prof_MICRO=0.0;
	prof_RCVL=0.0;
	prof_RCL=0.0;
	prof_RCR=0.0;
	prof_crb1 = 0.0;
	prof_crb2 = 0.0;
	prof_crhl = 0.0;
	prof_crhr = 0.0;
	prof_ocini = 0.0;
	prof_InertC=0.0;
	prof_RootDOC=0.0;
	
	prof_HUMUS=0.0;
	prof_NO2=0.0;
	prof_NO3=0.0;
	prof_NH4=0.0;
	prof_urea = 0.0;
	prof_ClayNH4=0.0;
	prof_NH3=0.0;
	prof_NO=0.0;
	prof_N2O=0.0;
	prof_N2=0.0;
	prof_FreezeDOC=0.0;
	prof_SurfaceLitter = 0.0;//stub1 + stub2 + stub3;
	prof_CH4C=0.0;
	prof_CO2flux=0.0;

	prof_Water = 0.0;	

	for(int l=1; l<=q; l++)
	{
		prof_CO2 += co2[l];
		prof_CH4 += ch4[l];

		prof_RCVL += rcvl[l];
		prof_RCL += rcl[l];
		prof_RCR += rcr[l];
		prof_crb1 += CRB1[l];
		prof_crb2 += CRB2[l];
		prof_crhl += crhl[l];
		prof_crhr += crhr[l];
		prof_ocini += ocini[l];
		prof_DOC += doc[l];
		prof_HUMUS += dphum[l];
		prof_InertC += inert_C[l];
		prof_FreezeDOC += FreezeDOC[l];
		prof_CH4C += ch4_doc_pool[l];
		prof_NO2 += (no2[l] + no2_d[l] + no2_w[l]);
		prof_NO3 += (no3[l] + no3_d[l] + no3_w[l]);
		prof_NH4 += (nh4[l] + nh4_w[l] + nh4_d[l]);
		prof_urea += urea[l]+assim2[l];
		prof_ClayNH4 += clay_nh4[l];
		prof_NH3 += nh3[l];
		prof_NO += (no[l] + no_d[l] + no_w[l]);
		prof_N2O += (n2o[l] + n2o_d[l] + n2o_w[l]);
		prof_N2 += (n2[l] + n2_w[l]);
		prof_NH4HCO3 += NH4HCO3[l];//new

		prof_Water += (water[24][l] + ice[l]/10000.0);
	}


	// Convert inorganic N pools to C-equivalent (kg C/ha) using stoichiometry.
	// Assumes urea[] and NH4HCO3[] are in kg N/ha. Adjust if stored otherwise.
	const double UREA_C_PER_N = 12.0 / 28.0; //  0.428571 C per N (urea)
	const double NH4HCO3_C_PER_N = 12.0 / 14.0; //  0.857143 C per N (bicarbonate)

	//double prof_inorgC_Ceq = prof_urea * UREA_C_PER_N + prof_NH4HCO3 * NH4HCO3_C_PER_N;

	double prof_inorgC_Ceq = prof_urea + prof_NH4HCO3 ;

	// Set start vs end totals alongside SOC
	if (ttmm == 1) {
		// ... your existing ini_prof_* assignments ...
		ini_prof_inorgC = prof_inorgC_Ceq;   // NEW
	}
	else if (ttmm == 2) {
		// ... your existing end_prof_* assignments ...
		end_prof_inorgC = prof_inorgC_Ceq;   // NEW
	}


	//double dCO2pool_today = end_prof_co2 - ini_prof_co2;
	//day_co2 += dCO2pool_today;     // make the pool change visible as a flux



	prof_RCVL_N = prof_RCVL / rcnrvl;
	prof_RCL_N = prof_RCL / rcnrl;
	prof_RCR_N = prof_RCR / rcnrr;
	prof_crb1_N = prof_crb1 / rcnb;
	prof_crb2_N = prof_crb2 / rcnb;
	prof_crh_N = prof_crhl / rcnh + prof_crhr / rcnh;	
	prof_ocini_N = prof_ocini / rcnh;
	prof_HUMUS_N = prof_HUMUS / rcnm;
	
	prof_SON = prof_RCVL_N + prof_RCL_N + prof_RCR_N + prof_crb1_N + prof_crb2_N + 
		       prof_crh_N + prof_HUMUS_N;
	prof_SIN = prof_NO2 + prof_NO3 + prof_NH4 + prof_ClayNH4 + prof_NH3 + prof_urea + 
				prof_NO + prof_N2O + prof_N2;

	prof_FluxNO = yr_dnno + day_soil_an_no; 
	prof_FluxN2O = yr_dnn2o + day_soil_an_n2o + yr_indirect_n2o + day_indirect_n2o; 
	prof_FluxN2 = yr_dnn2 + day_soil_n2 + yr_indirect_n2 + day_indirect_n2;
	prof_FluxNH3 = yr_soil_nh3 + day_soil_nh3 + day_vol_nh3;
	prof_GasN = prof_FluxNO + prof_FluxN2O + prof_FluxN2 + prof_FluxNH3;
	prof_LeachN = yr_leach_NO3 + yr_leach_urea + yr_leach_hu/rcnm + yr_runoff_N + (day_leach_NO3 + day_leach_urea + by_pass_no3 + 
		          day_leachhu/rcnm + day_runoff_N) ;
	prof_UptakeN = yr_uptaken[1] + yr_uptaken[2] +yr_uptaken[3] + day_nup[1] + day_nup[2] + day_nup[3];	
	prof_FertilizerN = yr_addfer + yr_addmn;
	prof_IrriN = yr_irri_N + day_irri_N;
	prof_LitterN = yr_addtn + yr_addrn;
	//prof_AssimN = yr_DNassimN + day_DNassimN;
	prof_RainN = yr_rainN + day_inRainN;//day_rainN;
	prof_SoilFixN = yr_soilN_from_Nfixation + day_soilN_from_Nfixation[1]+ day_soilN_from_Nfixation[2]+ day_soilN_from_Nfixation[3];
	
	prof_SN = prof_SON + prof_SIN;
	prof_fluxN = prof_GasN + prof_LeachN + prof_UptakeN + prof_AssimN
		      - prof_FertilizerN - prof_LitterN - prof_RainN - prof_IrriN - prof_SoilFixN;	
	total_SN = prof_SN + prof_fluxN;

	day_inN = day_inRainN+ day_inFertN+ day_inManureN+ day_inLitterN + day_irri_N + day_soilN_from_Nfixation[1]+ day_soilN_from_Nfixation[2]+ day_soilN_from_Nfixation[3];
	day_outN = day_nup[1] + day_nup[2] + day_nup[3] + day_soil_nh3 + day_vol_nh3 + 
				day_soil_an_n2o + day_soil_an_no + day_soil_n2 + day_runoff_N +
				day_leach_NO3+day_leach_urea+day_leachhu/rcnm + by_pass_no3;
	day_NetN = day_inN - day_outN;

	yr_influxN = prof_FertilizerN + prof_LitterN + prof_RainN + prof_IrriN + prof_SoilFixN;
	yr_effluxN = prof_GasN + prof_LeachN + prof_UptakeN + prof_AssimN;

	//C pools
	//prof_SOC = prof_RCVL + prof_RCL + prof_RCR + prof_crb1 + prof_crb2 + prof_crhl + prof_crhr + prof_HUMUS + prof_InertC 
	//			+ prof_DOC + prof_FreezeDOC + prof_CO2 + prof_CH4;  

	if(ttmm==1)
	{
		ini_prof_litter = prof_RCVL + prof_RCL + prof_RCR;
		ini_prof_humad = prof_crb1 + prof_crb2 + prof_crhl + prof_crhr;
		ini_prof_humus = prof_HUMUS;
		ini_prof_blackc = prof_InertC;
		ini_prof_doc = prof_DOC + prof_FreezeDOC;
		ini_prof_co2 = prof_CO2;
		ini_prof_ch4 = prof_CH4;
		ini_prof_SOC = ini_prof_litter + ini_prof_humad + ini_prof_humus + ini_prof_blackc + ini_prof_doc + ini_prof_co2 + ini_prof_ch4;
		prof_SOC = ini_prof_SOC;

		ini_SON = prof_SON;
		ini_SIN = prof_SIN;
		ini_ClayNH4 = prof_ClayNH4;
	}
	else if(ttmm==2)
	{
		end_prof_litter = prof_RCVL + prof_RCL + prof_RCR;
		end_prof_humad = prof_crb1 + prof_crb2 + prof_crhl + prof_crhr;
		end_prof_humus = prof_HUMUS;
		end_prof_blackc = prof_InertC;
		end_prof_doc = prof_DOC + prof_FreezeDOC;
		end_prof_co2 = prof_CO2;
		end_prof_ch4 = prof_CH4;
		end_prof_SOC = end_prof_litter + end_prof_humad + end_prof_humus + end_prof_blackc + end_prof_doc + end_prof_co2 + end_prof_ch4;
		prof_SOC = end_prof_SOC;

		end_SON = prof_SON;
		end_SIN = prof_SIN;
		end_ClayNH4 = prof_ClayNH4;
	}
			    
	//daily C fluxes

	prof_RootDOC = day_RootInput_DOC;

	prof_LitterC = day_addC;//yr_addtc + yr_addrc + yr_inert_C;

	prof_ManureC = day_addmc + slurry_doc;//yr_addmc;

	prof_CO2flux = day_co2;// + yr_RootExude_co2 + root_dCO2;// - ch4_co2 + CO2_CH4; yr_soil_co2 + 

	prof_LeachC = day_leachhu + day_leach_DOC + day_runoff_C;// + yr_leach_DOC + day_leach_DOC;yr_leach_hu + 	

	prof_CH4flux = day_balance_ch4;//yr_balance_ch4 
	
	//float flux_frostDOC = yr_frostDOC + day_frostDOC;

	prof_fluxC = prof_CO2flux + prof_LeachC  + prof_CH4flux - prof_LitterC - prof_ManureC - day_RootInput_DOC; 

	total_SOC = prof_SOC + prof_fluxC;	

	if(jday==1) 
	{
		InitialSOC = prof_SOC;
		InitialSON = prof_SN + prof_fluxN;		
	}

	//if(jday==365) 
	//{
		//yr_FluxC = prof_fluxC;
		//yr_FluxN = prof_fluxN;
	//}

	BalanceC = total_SOC - OLD_SOC;
	BalanceN = total_SN - old_SN;

	OLD_SOC = total_SOC;
	old_SN = total_SN;

	//prof_Water += (leaf_water + surf_water + snow_pack); //PoolWater + 
	inWater = yr_bypass_in + day_bypass_influx + yr_water_in + day_water_in;
	outWater = yr_trans + day_transp + yr_soil_ev + day_soil_ev + yr_leach_water + day_leach_water; 

	total_Water = prof_Water - inWater + outWater;

}