#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#define _USE_MATH_DEFINES
#include "math.h"


#ifdef MANURE 
extern class_manure MData;
extern class_model *DNDC;

float conc_uear, conc_nh4, conc_no3, conc_doc, lagoon_windspeed;
static float ManurePH[7]={7.0, 7.0, 7.0, 7.0, 8.1, 7.5, 7.0}; 
//for dairy cattle, beef, veal, pig, sheep, foultry

void class_manure::lagoon_BGC(int FN, int GN,
	int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float* urea, float* doc,
	float* rcvl, float* rcl, float* rcr, float* CRB1, float* CRB2, float* dphum, float* temp, float air_temp,
	float DayPET, float wind_speed, float* day_wfps, float* soc, float* sph, int* flood_flag, int WTL, float day_WT,
	float* soil_ph, float* nh4, float* ch4_prod, float* ch4_day_oxid, float* plant_day_ch4, float rcnm, float* son, float* SIN, float* no3, float* no2,
	float* no, float* n2o, float* n2, float* nh3, float* ch4, float TTT, float* newh, float* w_no2,
	float* w_nh3,
	float* w_no3, float* w_nh4, float* wurea, float day_clayn, float* wpool_no,
	float* DayFlux, int tilq,
	FILE* fCB, FILE* fNB, float* w_n2o, float* w_n2, int* seed, float* day_ch4, float* anvf, float WaterLeakRate,
	float* co2, float* clay, int LandUse, int FloDays, float* crhl, float* crhr, float* mmm, float* ocini,
	float* h, float* day_C_mine, float* day_N_mine, float* day_N_assim, float DClitter,
	float* litco22, float* litco23, int* st, float DChumads, float EFFAC, float DChumus,
	int wetland_flag, float* ice, float* day_soil_nh3, float* lai, float* PlantTakeN, float* maxmn,
	float leaf_water, float cropht, float base_nh3, float* day_N_demand, float* day_nup, float* day_fixN,
	float* day_DWater,
	float* day_plant_nh3, float* yr_NH3_deposit, float* plantn, float* clay_nh4, float base_clay_N, float max_clay_N,
	float* wrcvl, float* wrcl, float* wrcr, float* wcrb, float* wcrhl, float* wcrhr, float* whumus, float* wtcavai,
	float* day_ice_N, float* day_ice_doc, float* day_ice_n2o, float* day_ice_n2, float* IniSOC, float* IniSON,
	float* EndSON,
	float day_runoff, float* day_runoff_N, float* day_clay_N,
	float* dsno3, float* dsnh4, float* dsnh3, float* day_dsurea, float* ds_doc, int* crop, float* yr_fixn,
	float till_fact, float* sts, float rainfall, float* O2_old, float* O2, float* vvv, float* ave_anvf,
	int year, double water[25][250], float total_ice, float* day_rco2, int flo_num, float* Eh,
	float* doc_w, float* nh4_w, float* no3_w, float* no2_w, float* no_w, float* n2o_w, float* n2_w,
	float* doc_d, float* nh4_d, float* no3_d, float* no2_d, float* no_d, float* n2o_d, float* ttoo,
	float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl,
	float* assim2, float* fldcap, float by_passf, int NIDay1, int NIDay2,
	float* day_soil_nitrify, float* day_nitrify_NO, float* day_nitrify_N2O, float* day_soil_an_no,
	float* day_soil_an_n2o, float* day_soil_n2, float* Root_Wt, float* day_soil_denitrification,
	float* R_Wt, float* vascularity, float* winertC, float* inert_C, int fert_flag,
	float* root_doc, float* day_O2, float RFM, float* SoilDepth,
	float* wiltpt, float* day_frostDOC, float* yr_frostDOC, float precipitation, int manuFlag, int irri_flag,
	float* FreezeDOC, float* sop, float* OrgP, float* LabP, float* ComP, float* AdsP,
	float LateralInflux, int drain_flag, float day_leach_water, int facility, float LagoonCapacity,
	float disturbance, float* manco2, float* manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2, float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol, int manureCounter,
	float max_temp, float maxAnnualTemp, float min_temp, float yr_avetj, int oldLayerDepth, float lagoonTempPartition[101][2], float *lagoon_snowpack, float *lagoon_SnowMelt, float lagoon_snowfall, float DayPETRN, float lagoon_ice[21],float latitude, float humidity)
{
	float ttn;
	h[GN] = h[1];

	
	

	lagoon_snowfall_snowpack(air_temp, rainfall, *lagoon_snowpack, *lagoon_SnowMelt, lagoon_snowfall, year,lagoon_ice);
	lagoon_climate(GN, temp, air_temp, day_wfps, Eh, wind_speed, DayPET, water, jday, rainfall, facility, max_temp, maxAnnualTemp, min_temp, yr_avetj, year, soc, oldLayerDepth, lagoonTempPartition, *lagoon_snowpack, *lagoon_SnowMelt, lagoon_snowfall, DayPETRN, lagoon_ice, latitude,humidity);

//ttn = Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

	if(water[1][GN]>0.0)
	{

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
			winertC, inert_C, fert_flag, root_doc, day_O2, RFM, SoilDepth, ttoo, 
			sop, OrgP, LabP, AdsP, ComP, sts, day_leach_water, 1.0, facility, 0,manco2,manurePool,manurePoolCN, UreaHydroInhibDays, UIDay1, UIDay2,  newmanuPH,combinedpHDeep,manureHour,NH3Vol, manureCounter);//added 3 zeros to handle manco2, manurepool, manurePoolCN

//ttn = Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		lagoon_nh3(GN, temp, nh3, water, nh4, sph, LagoonCapacity, disturbance, urea, jday);

//ttn = Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		lagoon_denitrification(GN, temp, nh4, no3, soc, doc,no2,no,n2o,n2, dphum, rcnm, disturbance);

//ttn = Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

/*		DNDC->N2O_balloon(GN, till_fact, sts, h, jday, *flood_flag, FloDays, rainfall,
			O2_old, O2, TTT, vvv, ave_anvf, q, st, temp, year, water, day_wfps, day_WT, 
			WTL, total_ice, day_rco2, co2, flo_num, ice, sph, Eh, anvf,
			nh4, no3, no2, no, n2, doc, n2o, doc_w, nh4_w, no3_w, no2_w, no_w, n2o_w, n2_w,
			doc_d, nh4_d, no3_d, no2_d, no_d, n2o_d, LandUse, ttoo, 
			ManureAddCN, ManureDays, soc, MicrobioIndex, mRBO, mFD, WaterControl, 
			crop, assim2, clay, fldcap, by_passf, NIDay1, NIDay2,
			day_soil_nitrify, day_nitrify_NO, day_nitrify_N2O, day_soil_an_no,
			day_soil_an_n2o, day_soil_n2, Root_Wt, WaterLeakRate,
			rcvl, rcl, rcr, day_soil_denitrification,
			wiltpt, CRB1, CRB2, rcnb, Odoc, day_frostDOC, yr_frostDOC, precipitation, 
			manuFlag, irri_flag, FreezeDOC, nh3, urea, LateralInflux, drain_flag,
			0);
*/		
		lagoon_ch4(GN, temp, dphum, doc, disturbance, jday, rcr, rcvl, rcl, CRB1, CRB2, crhl, crhr,	rcnrvl, rcnrl, rcnrr, rcnb, rcnh, nh4);

		//Crust formation
//ttn = Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		float ManureConc = soc[GN] / water[1][GN];

//ttn = Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		float EV_m = MData.yr_lagoon_EV / (1000.0 * MData.m_LagoonSurfaceArea); 
		if(ManureConc>0.005 && EV_m>0.1&&MData.lagoon_days>50)//0.12
		{
			MData.LagoonCrustC += 0.003 * soc[GN] * 50.0 / MData.lagoon_days;  //0.006
		}
		
	}
	else
	{
		MData.day_lagoon_ch4 = 0.0;
		MData.day_lagoon_nh3 = 0.0;
		MData.day_lagoon_n2o = 0.0;
		MData.day_lagoon_no = 0.0;
		MData.day_lagoon_n2 = 0.0;
		MData.LagoonCrustC = 0.0;
	}

}

//BIRK -------------------------------------NEW LAGOON EVAPORATION CALCUATION BASED ON PENMAN 1956---------------------------------------------------------------------------

class atmospheric_cal {
	public:


		// Calculate [Atmospheric Pressure] using [elevation]
		float atmosphere_pressure(float elevation) {

			// Atmosphere pressure calculation function 
			// Input: Location elevation [m]
			// Output: Atmospheric pressure [kPa]

			float atm_pressure;

			atm_pressure = 101.3 * powf(((293. - 0.0065 * elevation) / 293.), 5.26);

			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Atmospheric Pressure (P) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Elevation (z) : " << std::setw(8) << std::left << elevation << "[m]" << std::setw(10) << std::left << std::endl;
			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Atmospheric Pressure (P):" << std::setw(8) << std::left << atm_pressure << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return atm_pressure;
		}


		// Calculate [Psychrometric Constant] using [atmospheric pressure]
		float psychrometric_constant(float elevation) {

			// Input: elevation 
			// Call [atmosphere_pressure] to calculate [atmosphere pressure] using elevation
			// Output: Psychrometric constant [kPa C-1]

			// spec_heat_pressure :: specific heat at constant pressure [MJ kg-1 C-1]
			// lat_heat_vap :: latent heat of vaporization [MJ kg-1]
			// ratio_mol_weight_vap_air :: ratio molecular weight of water vapour/dry air 

			const float spec_heat_pressure = 1.013e-3;
			const float lat_heat_vap = 2.45;
			const float ratio_mol_weight_vap_air = 0.622;

			// atm_press :: atmospheric pressure [kPa]
			// psychrom_const :: Psychrometric constant [kPa C-1]
			float atm_press, psychrom_const;

			atm_press = atmosphere_pressure(elevation);

			psychrom_const = (spec_heat_pressure * atm_press) / (ratio_mol_weight_vap_air * lat_heat_vap);

			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Slope of saturation vapour press. (Delta) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Spec. heat pressure (Cp) : " << std::setw(8) << std::left << spec_heat_pressure << "[kPa C-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Atmospheric pressure (P) : " << std::setw(8) << std::left << atm_press << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Latent heat for evap. (lambda) : " << std::setw(8) << std::left << lat_heat_vap << "[MJ kg-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Molecular ratio water/air (epsilon) : " << std::setw(8) << std::left << ratio_mol_weight_vap_air << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Psychrometric const. (Gamma) : " << std::setw(8) << std::left << psychrom_const << "[kPa C-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return psychrom_const;
		}


		// Calculate [Slope of saturation vapour pressure curve] using [Mean Air Temp.]
		float slope_vap_press_curve(float max_temp, float min_temp) {

			float mean_temp, slpVapCurve;

			mean_temp = mean_air_temp(max_temp, min_temp);

			slpVapCurve = 4098. * (0.6108 * exp((17.27 * mean_temp) / (mean_temp + 237.3))) / (pow((mean_temp + 273.3), 2));
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Slope of saturation vapour press. (Delta) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Mean air temp (t) : " << std::setw(8) << std::left << mean_temp << "[deg C]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Slope of saturation vapour press. (Delta) : " << std::setw(8) << std::left << slpVapCurve << "[kPa C-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG


			return slpVapCurve;
		}


		// Calculate [Vapour deficit], depending on MEAN_SAT_VAP_PRESS() and ACTUAL_VAP_PRESS()
		float vapour_deficit(float max_temp, float min_temp, float max_rh, float min_rh) {

			float vap_deficit, act_vap_press, avg_sat_vap_press;

			avg_sat_vap_press = mean_sat_vap_press(max_temp, min_temp);

			act_vap_press = actual_vap_press(max_temp, min_temp, max_rh, min_rh);

			vap_deficit = avg_sat_vap_press - act_vap_press;

			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Vapour deficit (Es - Ea) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Mean Saturation vapour press. (E_s) : " << std::setw(8) << std::left << avg_sat_vap_press << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Actual vpour press. (E_a) : " << std::setw(8) << std::left << act_vap_press << "[kPa]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Vapour pressure deficit (Es-Ra) : " << std::setw(8) << std::left << vap_deficit << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return vap_deficit;
		}


		// Calculate [Clear sky radiation], using [Extraterrestrail radiation]
		float clear_sky_solar_rad(float lat, float DOY, float elevation) {

			float clear_sky_rad, extraTerresRad;

			extraTerresRad = extraTerrestrial_rad(lat, DOY);

			clear_sky_rad = (0.75 + 2e-5 * elevation) * extraTerresRad;
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Clear-sky solar radiation (R_so) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Elevation (z) : " << std::setw(8) << std::left << lat << "[m]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Daily Extraterrestrial radiation (R_a) : " << std::setw(8) << std::left << extraTerresRad << "[MJ m-2 min-1]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Clear-sky solar radiation (R_so) : " << std::setw(8) << std::left << clear_sky_rad << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return clear_sky_rad;
		}


		// Calculate [Extraterrestrail radiaton], depending on INVERSE_RELATIVE_DIST_EARTH_SUN(), SUNSET_HOUR_ANGLE(), SOLAR_DECLINATION_ANGLE()
		float extraTerrestrial_rad(float lat, float DOY) {

			const float solarCons = 0.0820;
			float extraTerrRad, inverDistance, sunsetAngle, solarDeci, lat_rad;


			//lat_rad = deg2rad(lat);
			lat_rad=lat* M_PI / 180;

			inverDistance = inverse_relative_dist_Earth_Sun(DOY);
			sunsetAngle = sunset_hour_angle(lat, DOY);
			solarDeci = solar_declination_angle(DOY);

			extraTerrRad = (24. * 60. / M_PI) * solarCons * inverDistance * (sunsetAngle * sin(lat_rad) * sin(solarDeci) + cos(lat_rad) * cos(solarDeci) * sin(sunsetAngle));
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Extraterrestrial radiation for daily periods (R_a) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Lattitude (phi) : " << std::setw(8) << std::left << lat << "[deg]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Solar Constant (G_sc) : " << std::setw(8) << std::left << solarCons << "[MJ m-2 min-1]" << std::setw(10) << std::left << std::endl;

			std::cout << std::left << std::setw(40) << "Inverse relative distance (d_r) : " << std::setw(8) << std::left << inverDistance << "[rad]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Solar declination (sigma) : " << std::setw(8) << std::left << solarDeci << "[rad]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Sunset hour angle (omega) : " << std::setw(8) << std::left << sunsetAngle << "[rad]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Lattitude (phi) : " << std::setw(8) << std::left << lat_rad << "[rad]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Daily Extraterrestrial radiation (R_a) : " << std::setw(8) << std::left << extraTerrRad << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG
			return extraTerrRad;
		}


		// Calculate [Net longwave radiation] using [Solar Radiation]
		// NOTE ALBEDO IS SET TO 0.14, THIS IS FOR MANURE ONLY !!!!
		float net_shortWave_rad(float lat, float DOY) {

			// aledo for canopy :: 0.23 (FAO Chapther 3)
			//const float albedo = 0.23;

			// albedo for manure :: 0.14 (Cluett, VanderZaag; 2020)
			const float albedo = 0.14;

			float net_shortW, solarRad;

			solarRad = solar_rad(lat, DOY);

			//solarRad = 14.5;

			net_shortW = (1 - albedo) * solarRad;
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Net Shortwave radiation (R_ns) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Albedo (alpha) : " << std::setw(8) << std::left << albedo << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Solar radiation (R_s) : " << std::setw(8) << std::left << solarRad << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Net Shortwave radiation (R_ns) " << std::setw(8) << std::left << solarRad << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return net_shortW;
		}


		// Calculate [Solar radiation], depending on DAY_LIGHT_HOUR(), EXTRATERRESTRIAL_RAD()
		float solar_rad(float lat, float DOY) {

			const float a_s = 0.25;
			const float b_s = 0.5;

			float act_durationSun, max_durationSun, extraTerrRad, solarRad;

			max_durationSun = day_light_hour(lat, DOY);

			extraTerrRad = extraTerrestrial_rad(lat, DOY);

			act_durationSun = max_durationSun * 0.58; //Assumption of act_duration is 0.58 of Max duration, value took from OG DNDC - Birk

			solarRad = (a_s + b_s * (act_durationSun / max_durationSun)) * extraTerrRad;

			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Solar radiation (R_s) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Regression Constant (a_s) : " << std::setw(8) << std::left << a_s << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Regression Constant (b_s) : " << std::setw(8) << std::left << b_s << std::setw(10) << std::left << std::endl;

			std::cout << std::left << std::setw(40) << "Actual Duration of Sunshine (n) : " << std::setw(8) << std::left << act_durationSun << "[hour]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Maximum Possible duration of sunshine (N)" << std::setw(8) << std::left << max_durationSun << "[hour]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Extraterrestrial radiation (R_a) : " << std::setw(8) << std::left << solarRad << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Solar radiation (R_s): " << std::setw(8) << std::left << solarRad << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return solarRad;
		}


		// Calculate [Net Longwave Radiation], depending on SOLAR_RAD(). CLEAR_SKY_SOLAR_RAD(), ACTUAL_VAP_PRESS() 
		float net_longWave_rad(float max_temp, float min_temp, float rh_max, float rh_min, float elev, float lat, float DOY) {

			float abs_Tmax, abs_Tmin, act_vap_pressure, solarRad, clearSolarRad;

			const float Ste_Botz_Cont = 4.903e-9;

			float net_longWave;

			abs_Tmax = abs_air_temp(max_temp);
			abs_Tmin = abs_air_temp(min_temp);

			solarRad = solar_rad(lat, DOY);
			clearSolarRad = clear_sky_solar_rad(lat, DOY, elev);

			act_vap_pressure = actual_vap_press(max_temp, min_temp, rh_max, rh_min);

			//act_vap_pressure = 2.1; // For demo testing - Birk 

			net_longWave = Ste_Botz_Cont * (0.5 * (pow(abs_Tmax, 4) + pow(abs_Tmin, 4))) * (0.34 - 0.14 * sqrt(act_vap_pressure)) * (1.35 * (solarRad / clearSolarRad) - 0.35);

			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Net Longwave radiation (R_nl) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Maximum Temp. (Tmax) : " << std::setw(8) << std::left << max_temp << "[deg C]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Minimum Temp. (Tmax) : " << std::setw(8) << std::left << min_temp << "[deg C]" << std::setw(10) << std::left << std::endl;

			std::cout << std::left << std::setw(40) << "Maximum Humidity (RhMax) : " << std::setw(8) << std::left << rh_max << "[%]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Minimum Humidity (RhMin) : " << std::setw(8) << std::left << rh_min << "[%]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Solar Radiation (R_s) : " << std::setw(8) << std::left << solarRad << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Clear Sky Solar Radiation (R_so)  : " << std::setw(8) << std::left << rh_min << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Actual Vapour Pressure (E_a)  : " << std::setw(8) << std::left << act_vap_pressure << "[kPa]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Net Longwave radiation (R_nl): " << std::setw(8) << std::left << net_longWave << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return net_longWave;
		}


		// Calculate [Net Radation], depending on NET_SHORTWAVE_RAD(), NET_LONGWAVE_RAD()
		float net_radiation(float max_temp, float min_temp, float rh_max, float rh_min, float elev, float lat, float DOY) {

			float netShortWave, netLongWave;
			float netRadiation;

			netShortWave = net_shortWave_rad(lat, DOY);
			netLongWave = net_longWave_rad(max_temp, min_temp, rh_max, rh_min, elev, lat, DOY);

			netRadiation = netShortWave - netLongWave;

			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Net Radiation (R_n) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Net Short Wave Radiation (R_ns) : " << std::setw(8) << std::left << netShortWave << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Net Long Wave Radiation (R_ls) : " << std::setw(8) << std::left << netLongWave << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Net Radiation (R_n) : " << std::setw(8) << std::left << netRadiation << "[MJ m-2 d-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;

#endif // DEBUG

			return netRadiation;
		}

		// Calculate [Mean Saturation Vapour Pressure], depending on SAT_VAP_PRESSURE() 
		float mean_sat_vap_press(float max_temp, float min_temp) {

			float avg_satVapPressure, max_satVapPressure, min_satVapPressure;

			max_satVapPressure = sat_vap_pressure(max_temp);
			min_satVapPressure = sat_vap_pressure(min_temp);

			avg_satVapPressure = 0.5 * (max_satVapPressure + min_satVapPressure);

			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Mean Saturation Vapour Press. (Es) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Saturation Vapour Pressure @ Tmax : " << std::setw(8) << std::left << max_satVapPressure << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Saturation Vapour Pressure @ Tmin : " << std::setw(8) << std::left << min_satVapPressure << "[kPa]" << std::setw(10) << std::left << std::endl;


			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Mean Saturation Vapoure Press. (E0 (T)): " << std::setw(8) << std::left << avg_satVapPressure << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG
			return avg_satVapPressure;
		}


		// Calculate [Acutal Vapour Pressure], depending on SAT_VAP+PRESSURE()
		float actual_vap_press(float max_temp, float min_temp, float max_rh, float min_rh) {

			float act_vap_press, max_satVapPressure, min_satVapPressure;

			max_satVapPressure = sat_vap_pressure(max_temp);
			min_satVapPressure = sat_vap_pressure(min_temp);


			act_vap_press = 0.5 * (min_satVapPressure * (max_rh * 0.01)) + (min_satVapPressure * (min_rh * 0.01));
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Mean Saturation Vapour Press. (Es) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Saturation Vapour Pressure @ Tmax : " << std::setw(8) << std::left << max_satVapPressure << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Saturation Vapour Pressure @ Tmin : " << std::setw(8) << std::left << min_satVapPressure << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Maximum Humidity : " << std::setw(8) << std::left << max_rh << "[%]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Minimum Humidity : " << std::setw(8) << std::left << min_rh << "[%]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Actual Vapour Pressure (e_a): " << std::setw(8) << std::left << act_vap_press << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG
			return act_vap_press;
		}

	private:

		// Convert Temperature from Celsius to Kevin
		float abs_air_temp(float temp) {

			float abs_temp;

			abs_temp = temp + 273.16;

			return abs_temp;
		}


		// Calculate [Mean Temp] from [Maximum Temp.] amd [Minimum Temp.] 
		float mean_air_temp(float max_temp, float min_temp) {

			// To calcualte mean temperature
			float mean_temp;

			mean_temp = 0.5 * (max_temp + min_temp);

			return mean_temp;
		}

		// Calculate [Saturation Vapour Pressure] using [Temp.]
		float sat_vap_pressure(float temp) {

			// input -> temp [C]
			// output -> saturation vapoure pressure [kPa] 
			float sat_vapPress;

			sat_vapPress = 0.6108 * exp((17.27 * temp / (temp + 237.3)));
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Saturation Pressure@Temp (E0 (T)) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Temp. (T) : " << std::setw(8) << std::left << temp << "[deg C]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Saturation Pressure@Temp (E0 (T)): " << std::setw(8) << std::left << sat_vapPress << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return sat_vapPress;
		}


		// Calculate Inverse Relative distance Earth Sun 
		float inverse_relative_dist_Earth_Sun(int DOY) {

			float inv_rela_dist;

			inv_rela_dist = 1 + 0.033 * cos(((2 * M_PI) / 365) * DOY);
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Inverse relative distance Earth-Sun. (dr) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Day-Of-Year : " << std::setw(8) << std::left << DOY << std::setw(10) << std::left << std::endl;
			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Inverse relative distance Earth-Sun. (dr): " << std::setw(8) << std::left << inv_rela_dist << "[rad]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG
			return inv_rela_dist;
		}


		// Calculate Solar declination angle 
		float solar_declination_angle(int DOY) {

			float declin_angle;

			declin_angle = 0.409 * sin(((2 * M_PI) / 365) * DOY - 1.39);
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Solar declination angle (delta) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Day-Of-Year : " << std::setw(8) << std::left << DOY << std::setw(10) << std::left << std::endl;
			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Solar declination angle (delta): " << std::setw(8) << std::left << declin_angle << "[rad]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return declin_angle;
		}


		// Calcualte Sunset hour angle, depending on SOLAR_DECLINATION_ANGLE(), DEG2RAD()
		float sunset_hour_angle(float lat, int DOY) {

			float sun_angle, lat_rad;

			float decline_angle;

			decline_angle = solar_declination_angle(DOY);

			//lat_rad = deg2rad(lat);
			lat_rad = lat * M_PI / 180;

			sun_angle = acos(-tan(lat_rad) * tan(decline_angle));

			return sun_angle;
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Sunset hour angle (omega_s) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Day-Of-Year : " << std::setw(8) << std::left << DOY << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Solar declination angle (delta) : " << std::setw(8) << std::left << decline_angle << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Latitude (delta) : " << std::setw(8) << std::left << lat << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Latitude (delta): " << std::setw(8) << std::left << lat_rad << "[rad]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Sunset hour angle (omega_s): " << std::setw(8) << std::left << sun_angle << "[rad]" << std::setw(10) << std::left << std::endl;

			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG
		}


		// Calcualte Day light hour, depending on SUNSET_HOUR_ANGLE()
		float day_light_hour(float lat, int DOY) {

			float sun_angle, dayLightHour;

			sun_angle = sunset_hour_angle(lat, DOY);

			dayLightHour = (24. / M_PI) * sun_angle;
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(3);
			std::cout << std::left << std::setw(70) << "Daylight hours (N) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Sunset hour angle (omega_s) : " << std::setw(8) << std::left << sun_angle << std::setw(10) << std::left << std::endl;
			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Daylight hours (N): " << std::setw(8) << std::left << dayLightHour << "[hour/day]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return dayLightHour;
		}


	};


	// Penman Evaporation calculation 
	// NEED ATMOSPHERIC_CAL TO OPERATE
	// NOT ET !!! EVAPORATION ONLY
	// USING PENMAN, 1956
	// DETAIL SEE TECHNICAL DOCUMENT - BIRK 
	// Coded by Birk., 2023

	class penman_evap : public atmospheric_cal {
	public:
		// Calculate Evaporation cause by drying power of the air (Ea)
		// Equation modified from PENMAN, 1956 for SI unit conversion
		float evap_DryingPower(float wind_2m, float max_temp, float min_temp, float max_rh, float min_rh, float para_a = 0.5, float para_b = 0.53686) {


			float sat_vap, act_vap;
			float evap_fromDrying;

			sat_vap = mean_sat_vap_press(max_temp, min_temp);
			act_vap = actual_vap_press(max_temp, min_temp, max_rh, min_rh);

			evap_fromDrying = 2.6252 * (para_a + para_b * wind_2m) * (sat_vap - act_vap);
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG
			std::cout << std::fixed << std::setprecision(4);
			std::cout << std::left << std::setw(70) << "Evaporation by drying power (E_a) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Parameter 1 (a) : " << std::setw(8) << std::left << para_a << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Parameter 2 (b) : " << std::setw(8) << std::left << para_b << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Wind speed @ 2m (u_2) : " << std::setw(8) << std::left << wind_2m << "[m/s]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Saturation Vapour Pressure (e_s) : " << std::setw(8) << std::left << sat_vap << "[kPa]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Actual Vapour Pressure (e_a) : " << std::setw(8) << std::left << act_vap << "[kPa]" << std::setw(10) << std::left << std::endl;

			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Evaporation by drying power (E_a):" << std::setw(8) << std::left << evap_fromDrying << "[mm day-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG

			return evap_fromDrying;
		}


		// Calculate Daily Evaporation
		float net_evaporation(float wind_2m, float elev, float Tmax, float Tmin, float max_rh, float min_rh, float DOY, float lat) {

			const float latent_water = 2.45;
			const float density_water = 997;

			float net_radi, slp_vap_press, psychro_const, evap_dry;

			float net_evap;

			psychro_const = psychrometric_constant(elev);
			slp_vap_press = slope_vap_press_curve(Tmax, Tmin);
			evap_dry = evap_DryingPower(wind_2m, Tmax, Tmin, max_rh, min_rh);
			net_radi = net_radiation(Tmax, Tmin, max_rh, min_rh, elev, lat, DOY);

			net_evap = (psychro_const / (psychro_const + slp_vap_press)) * (net_radi / (latent_water * density_water)) * 1000. + (slp_vap_press / (psychro_const + slp_vap_press) * evap_dry);
			//--------------------------DEBUG VISUALIZE OUTPUT TEST ----CONSOLE ONLY-------------------------------------
#ifdef DEBUG //meant as a degbugger output
			std::cout << std::fixed << std::setprecision(3); //codes for  writing out each variable or predefined output to screen //std::cout = stream << 
			std::cout << std::left << std::setw(70) << "Daily Evaporation (E) Calculation:" << std::endl;
			std::cout << std::left << std::setw(70) << "------------------------------------------------------------------" << std::endl;
			std::cout << "Input: " << std::endl;
			std::cout << std::left << std::setw(40) << "Psychrometric constant (gamma) : " << std::setw(8) << std::left << psychro_const << "[kPa C-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Slope of sat. vapour pressure (Delta): " << std::setw(8) << std::left << slp_vap_press << "[kPa C-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Net radiation (Rn) : " << std::setw(8) << std::left << net_radi << "[MJ m-2]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Density of Water (rho) : " << std::setw(8) << std::left << density_water << "[kg m-3]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Latent Heat of vapor. (lambda) : " << std::setw(8) << std::left << latent_water << "[MJ kg-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(40) << "Evaporation by drying power (E_a): " << std::setw(8) << std::left << evap_dry << "[mm day-1]" << std::setw(10) << std::left << std::endl;


			std::cout << std::setw(5) << std::left << "\t\t\t" << "-------------------------" << std::endl;
			std::cout << "Output: " << std::endl;
			std::cout << std::left << std::setw(40) << "Daily Evaporation(E_a):" << std::setw(8) << std::left << net_evap << "[mm day-1]" << std::setw(10) << std::left << std::endl;
			std::cout << std::left << std::setw(70) << "==================================================================" << std::endl;
			std::cout << std::endl;
#endif // DEBUG
			return net_evap;
		}

	};


void class_manure::lagoon_snowfall_snowpack(float air_temp, float rainfall, float& lagoon_snowpack, float& lagoon_SnowMelt, float& lagoon_snowfall, int year,float lagoon_ice[21])
	{
		//rainfall = precipitation;

		//lagoon_snowpack = 10.0;//testing BD
		if (MData.lagoon_days == 1 && year == 1 && lagoon_snowpack < 0.0)//first day of simulation initialize snowpack to zero
		{
			lagoon_snowpack = 0.0;
		}

		lagoon_SnowMelt = 0.0;//snowmelt initalized to zero
		
		//added condition of the top surface being frozen to accumulate snowpack!!!!
		if (rainfall > 0.0 && air_temp <= 0.0 && MData.LagoonT[1] <= 0.0&&lagoon_ice[1]>0.0)//if ( precipitation > 0.0 && air_temp <= 0.0 )//BD && MData.LagoonT[1]<0.0 ---should we have another condition that the manure surface is frozen (seems that way).
		{
			lagoon_snowfall = rainfall;

			lagoon_snowpack += lagoon_snowfall; //m water
		}
		else//no snowfall accumulation.
		{
			lagoon_snowfall = 0.0;
		}

		if (lagoon_snowpack > 0.0 && air_temp > 0.0)//if average temperature is above zero and there is a snowpack
		{
			lagoon_SnowMelt = 0.004 * air_temp;//0.004? Brian---adopted from Crop Code. Just a rate of snowmelt -- ideally should be more process-based
			
			if (lagoon_SnowMelt > lagoon_snowpack)//test to see if Snowmelt amount > existing snowpack
			{
				//snowpack reduced to zero
				lagoon_SnowMelt = lagoon_snowpack; //m water
				lagoon_snowpack = 0.0;
			}
			else
			{
				//snowpack reduced by snowmelt amount
				lagoon_snowpack -= lagoon_SnowMelt;
			}



			//water[1][GN] += lagoon_SnowMelt; //Make snowmelt add to open lagoon...probably needs to pull double water[25][180] into this function
			

		}
		else//either snowpack is zero or air_temp less than zero ... shouldn't do anything.
		{
			if (MData.LagoonT[1] > 0.0&&lagoon_ice[1]==0.0)
			{
				lagoon_snowpack = 0.0;
				
			
			}
			//if there isn't any ice
			/*
			if (MData.LagoonT[1] > 0.0 && lagoon_ice == 0.0)//&& air_temp >0.0
			{
				lagoon_snowpack = 0.0;
			}
			*/
		}

	}
double deg2rad(double degrees) {

	return degrees * 4.0 * atan(1.0) / 180.0;
}
void class_manure::lagoon_climate(int GN, float* temp, float air_temp, float* day_wfps, float* Eh, float wind_speed,
	float DayPET, double water[25][250], int jday, float rainfall, int facility,
	float max_temp, float maxAnnualTemp, float min_temp, float yr_avetj, int year, float* soc, int oldLayerDepth, float lagoonTempPartition[101][2], float lagoon_snowpack, float lagoon_SnowMelt, float lagoon_snowfall, float DayPETRN, float lagoon_ice[21], float latitude, float humidity)
{

	float mm_DayPET, LInRain = 0.0, dT = 0.0;
	float total_lagoon_ice = 0.0;
	//float lagoon_snowpack = 10.0;
	float outQ[120], Z[101], K[101], Kave, dQ;
	float lag_coeff;
	int n, a;
	//lagoon temperature
	temp[GN] = air_temp;

	/*
				int newT2;
			for (newT2=1; newT2<=20; newT2++)
			{
				if(lagoon_ice[newT2]<0)lagoon_ice[newT2]=0.0;
			total_lagoon_ice+=lagoon_ice[newT2];
			}
	*/
	if (year == 2 || jday ==1||jday==365)
	{
		float blah;
		blah = 1.0;
	}

	float pi = 3.14;//value of pi
	float lagoonWaterPool, lagoonDryMPool, lagoonSlurryDensity, lagoonTS, lagoonHeight, lagoonRadius;//define variables for use in calculation of specific heat mC[1] and thermal conductivity mK[1]
	lagoonWaterPool = water[1][GN] + rainfall * MData.m_LagoonSurfaceArea * 1000.0;//kg water in lagoon (rainfall plus flushing )
	lagoonDryMPool = soc[GN] / 0.42;//kg of dry matter (SOC divided by an assumed %42 C in dry matter)
	lagoonSlurryDensity = 1.04;//996.4 + 4.439*(lagoonTS*100);// //Lagoon Density g/cm3 ...probably less because it has alot of water flushed from feedlot...

	float L = 333.4;// latent heat of ice with melting included (J/g)
	float rho_ice = 917; // density of ice (kg/m3)
	float rate_water = 0.033;//rate of change of water content with temp - Rankinen et al (2004)

	float avg_temp = (max_temp + min_temp) / 2; //average air temp	
	float A0 = maxAnnualTemp - yr_avetj; //annual amplitude	//max_temp - yr_avetj
	float currentLagoonDepth;
	lagoonHeight = MData.m_LagoonCapacity / MData.m_LagoonSurfaceArea;//Height (m) of full lagoon.
	currentLagoonDepth = (water[1][GN] + rainfall + soc[GN] / 0.42) / 1.02 / 1000 / MData.m_LagoonSurfaceArea;//current depth based on volume
	//MData.m_LagoonDepth = MData.m_LagoonCapacity / MData.m_LagoonSurfaceArea;
	float currentLagoonFraction;
	currentLagoonFraction = (water[1][GN] + rainfall + soc[GN] / 0.42) / 1.02 / MData.m_LagoonCapacity / 1000;//cuurent Lagoon fraction of total volume
	float sumLagoonPartition; //This is a accumulator for determining average lagoon temperature.
	sumLagoonPartition = 0.0;//initialize to zero.
	float lagoonDepth[101];//,lagoonTempPartition[20][2]; //define an array that holds temperature partitions for 100 layers
	float depth_Partition = lagoonHeight / 100;// this is the height of each layer //lagoonHeight/100;
	int l, qq, x, maxLayerDepth, currentLayerDepth; //counter for depths
	float mK[101], mC[101], T[101], C_SOM;//Thermal Conductivity and Specific Heat Capacity and Temperature
	maxLayerDepth = int(lagoonHeight / depth_Partition + 1);//calculates the bottom layer # for the simultation not used yet
	currentLayerDepth = int(currentLagoonDepth / depth_Partition + 1);



	sumLagoonPartition = 0.0;
	//////////////////////////code for adding heat flux from new manure comming into the tank. Ignore for now.
	if (MData.lagoon_days > 1 && year == 1 && oldLayerDepth <= currentLayerDepth)
	{

		/*
			int newT1;
			for (newT1=1; newT1<=oldLayerDepth; newT1++)
			{
			//lagoonTempPartition[newT1][0]=lagoonTempPartition[newT1][1];
			sumLagoonPartition+=lagoonTempPartition[newT1][1];
			}
			temp[GN] = (sumLagoonPartition)/oldLayerDepth;//divides the sum by the number of partitions to come up with an average tank temperature



			int newT;
			float fractionIncMan,incManTemp,fractionLayerTemp,newManAvgTemp;
			incManTemp=15.0;//manure is barn temp but influenced by infastructure to tank (6oC) //21.0*.5+avg_temp*.2+6*.3//min(avg_temp,max(avg_temp,15.0))
			fractionIncMan= (MData.House_to_lagoon_C+MData.Digester_to_lagoon_C)/soc[GN];
			fractionIncMan=min(1.0,max(fractionIncMan,0.0));
			sumLagoonPartition=0.0;
			newManAvgTemp=temp[GN]*(1.0 - fractionIncMan)+incManTemp*(fractionIncMan);

			for (newT=1; newT<=oldLayerDepth; newT++)
			{
			fractionLayerTemp=lagoonTempPartition[newT][1]/(temp[GN]);
			fractionLayerTemp= min(0.99,max(fractionLayerTemp,0.01));

			lagoonTempPartition[newT][1]=fractionLayerTemp*newManAvgTemp;
			sumLagoonPartition+=lagoonTempPartition[newT][1];
			//lagoonTempPartition[newT][0]=lagoonTempPartition[newT][1];
			}
			temp[GN] = (sumLagoonPartition)/oldLayerDepth;//divides the sum by the number of partitions to come up with an average tank temperature
			if(currentLayerDepth>oldLayerDepth)//testing to see if when extra layers get added to the simulation that bottom layers are set to the previous bottom layer temperatures before the heat flux starts
						{
						 int difDepth,cc;
						 difDepth=currentLayerDepth-oldLayerDepth;
						for(cc=oldLayerDepth;cc<=(oldLayerDepth+difDepth-1);cc++)
							{
							lagoonTempPartition[cc+1][1]=lagoonTempPartition[cc][1];
							}
						}
		*/
	}
	else
	{
		temp[GN] = air_temp;//wouldn't this be set every day as it is?
	}











	sumLagoonPartition = 0.0;

	for (l = 1; l <= currentLayerDepth; l++)//Loop to generate the different depths..depths not used for any calculation at moment- might need to expand.
	{
		lagoonDepth[l] = depth_Partition * l;
		lagoonTS = ((lagoonDryMPool / (lagoonWaterPool + lagoonDryMPool)) * 100) + (7.9624 * (lagoonDepth[l]) - 0.8947);//calcuation of total Solids with depth
		lagoonTS = min(88.0, max(0.0, lagoonTS));//sets the max and minumum lagoonTS boundaries to be 0 and 88



		//setting of Manure Thermal Conductivity and Specific Heat Capacity ---- if thawed and no snow 
		if (lagoon_snowpack == 0 && total_lagoon_ice == 0.0)//&&total_lagoon_ice==0.0
		{
			if (l == 1)//separated for now in case we want to introduce crusting at a later date. -- layer 1 of manure
			{
				mK[l] = 0.617 - 0.007 * (lagoonTS);//0.52;//0.004513;//manure Thermal Conductivity in W/m/degC
				//mK[0] = min(0.617, max(0.52, mK[0]));//sets the max and minumum mK[0] boundaries to be 0 and 100

				mC[l] = 4187.5 - 28.9 * (lagoonTS) * 1.2;//3950;//Specific Heat Capacity in J/kg/degC// Will test it later for equation for volumetric heat capacity
				//mC[0] = min(4187.5, max(3950, mC[0]));//sets the max and minumum mC[0] boundaries to be 0 and 100

				C_SOM = 1925;//J/kg/degC --Hillel, 1998
			}
			else// all other layers
			{
				mK[l] = 0.617 - 0.007 * (lagoonTS);//0.52;//0.004513;//manure Thermal Conductivity in W/m/degC
				//mK[0] = min(0.617, max(0.52, mK[0]));//sets the max and minumum mK[0] boundaries to be 0 and 100

				mC[l] = 4187.5 - 28.9 * (lagoonTS) * 1.2;//3950;//Specific Heat Capacity in J/kg/degC// Will test it later for equation for volumetric heat capacity
				//mC[0] = min(4187.5, max(3950, mC[0]));//sets the max and minumum mC[0] boundaries to be 0 and 100

				C_SOM = 1925;//J/kg/degC --Hillel, 1998


			}
		}
		else//setting of Manure Thermal Conductivity and Specific Heat Capacity ---- if snow or frozen
		{

			if (l == 1)//layer 1 of manure 
			{
				mK[l] = 0.617 - 0.007 * (lagoonTS);//0.52;//0.004513;//manure Thermal Conductivity in W/m/degC; 
				//mK[0] = min(0.617, max(0.52, mK[0]));//sets the max and minumum mK[0] boundaries to be 0 and 100
				mC[l] = 4187.5 - 28.9 * (lagoonTS)+((L * rho_ice * rate_water) / 1000) * 1.2;//Rankinen et al (2004)
				//mC[0] = min(4187.5, max(3950, mC[0]));//sets the max and minumum mC[0] boundaries to be 0 and 100
			}
			else //all other layers.....
			{
				mK[l] = 0.617 - 0.007 * (lagoonTS);//0.52;//0.004513;//manure Thermal Conductivity in W/m/degC
				//mK[0] = min(0.617, max(0.52, mK[0]));//sets the max and minumum mK[0] boundaries to be 0 and 100
				mC[l] = 4187.5 - 28.9 * (lagoonTS)+((L * rho_ice * rate_water) / 1000) * 1.2;//3950;//Specific Heat Capacity in J/kg/degC// Will test it later for equation for volumetric heat capacity
				//mC[0] = min(4187.5, max(3950, mC[0]));//sets the max and minumum mC[0] boundaries to be 0 and 100
				C_SOM = 1925;//J/kg/degC --Hillel, 1998
			}
		}


		//mC[0]=(lagoonSlurryDensity*lagoonDryMPool*C_SOM+1000*lagoonWaterPool*4187)/1000;//3950;//Specific Heat Capacity in J/kg/degC// Will test it later for equation for volumetric heat capacity


		float z = lagoonDepth[l];//Lagoon Depth 	- predefined
		float w = 2 * pi / 365; //angular frequency	
		float Dh = mK[l] / mC[l];// Thermal diffusivity	
		float d = pow((2 * Dh / w), 0.5); // Damping depth	
		float ratio_depth = z / d;//ratio depth
		float frezThawD = 0.5;//Freezing thawing depth (set to 50cm)
		float snowDepth = (lagoon_snowpack * 10);//multiplies snow_pack in m/water to snowdepth/m
		snowDepth = min(1.5, max(0.0, snowDepth));//sets the max and minumum snowDepth boundaries to be 0 and 0.05 m


		//lag_coeff=pow((l/20),1.5);//lag coefficient (ranging from 0.0 to 1.0) that controls the influence of the previous day's temperature on the current day's temperature

		//	lag_coeff=min(0.9,max(log10(l),0.0)); //should be set to be more influential with depth?
		float fillFactor;

		//lag_coeff=0.8 * (water[1][GN]+rainfall)/MData.m_LagoonCapacity*1000; //1m3 = 1000 kg water. I know water in tank(kg) and I know the capacity of tank in m3 * 1000
		float currentLagoonDepth;
		//	currentLagoonDepth=(water[1][GN]+rainfall)/1000/MData.m_LagoonSurfaceArea;
		currentLagoonDepth = ((water[1][GN] + rainfall + soc[GN] / 0.42) / 1.02 / 1000) / (3.14 * MData.m_LagoonSurfaceArea / 3.14);


		//MData.m_LagoonDepth = MData.m_LagoonCapacity / MData.m_LagoonSurfaceArea;
		float currentLagoonFraction;
		currentLagoonFraction = (water[1][GN] + rainfall + soc[GN] / 0.42) / 1.02 / MData.m_LagoonCapacity / 1000;
		float depthLgFactor;
		if (l == 1)depthLgFactor = 0.0001;
		else
			//depthLgFactor=log10(l*.1*10/2+0.001);
			depthLgFactor = pow((float)l / 5, 1 / (float)l);
		lag_coeff = min(0.90, max(pow(depthLgFactor, 1.05 - currentLagoonFraction), 0.0));

		//lag_coeff=0.9;


		float snowFactor;//not being used atm.

		if (lagoon_snowpack == 0.0)
		{
			snowFactor = 1.0;
			if (lagoon_ice[1] > 0)//provide some insultation of ice properties.
			{
				snowFactor = (exp(-50 * 100));
			}

		}
		else
		{
			snowFactor = (exp(-50 * snowDepth));
			//snowFactor=1.0;

		}


		if (MData.lagoon_days == 1 && year == 1 && lagoonTempPartition[1][1] < -30.0)//this is set so that it only calculates a temperature for the very first day of a sim. Also it allows you to read in temperatures froma multiyear sim.
		{
			//lagoonTempPartition[l][1] = (avg_temp + A0 * exp (-ratio_depth) * sin ((w*(jday-annualMinTempDay)) - ratio_depth - pi/2))*snowFactor;
			int aa;
			for (aa = 1; aa <= 100; aa++)
			{
				lagoonTempPartition[aa][1] = 15.0;//+aa/30;//populating with an initialized lagoon temperature on Janury 1st.
			}
			//lagoonTempPartition[1][1]=0.0;
		}
		else
		{
			//nothing calculated here..using heat flux algorithm only.
			//lagoonTempPartition[l][1] = (lag_coeff *lagoonTempPartition[l][0]) + ((1.0 - lag_coeff)* (avg_temp + A0 * exp (-ratio_depth) * sin ((w*(jday-annualMinTempDay)) - ratio_depth - pi/2)))*snowFactor;//Surface temp code by texture -- Hydrus 1D ---Lagoon temperature now!	
		}


		//extra stuff probably not needed anymore --------------------------------------------------
		//lagoonTempPartition[l][1]=lagoonTempPartition[1][1];


		//this is an running sum of the layers to be used for overall lagoon temperature

		//Surf_Temp = avg_temp + A0 * exp (-ratio_depth) * sin ((w*(jday-46)) - ratio_depth - pi/2);//Surface temp code by texture -- Hydrus 1D	
		//sumLagoonPartition+=lagoonTempPartition[l][1];		
		//lagoonTempPartition[l][0]=lagoonTempPartition[l][1]; //this sets the present days temperature into the array in the same layer at position index 0.





//Heat flux from layer L-1 down to L ------------------------------------- This is similar to soil Heat Flux transfer--------------------------------------------------------------------------------



  ///for heat Flux code below  defines the incremental depths from surface - nested here for layer loop
		float Zz = depth_Partition; //Used in HEAT flux loop below//0.022 this is dynamic manure layer depth.
		if (l == 1) Z[l] = Zz * 100.0;
		else Z[l] = Z[l - 1] + Zz * 100.0;//incrementally increasing with layer. This might need to change seems like a dampening factor for depth?
		K[l] = mK[l] * 86400;//turns the unit from W/m2/deg C to J/s m2 * 86400 is J/day m2




	} //end of layer loop

				//temp[GN] = (sumLagoonPartition)/20.0;//divides the sum by the number of partitions to come up with an average tank temperature

			//define surface air temp/manure temp boundary. 



	//-------------------------This Surf_Temp code here set to Air Temp is older legacy code ---- surf Temp is recalculated further below based on Tim Energy Balance Concept.
	float Surf_Temp, b;
	float adjT = (air_temp + max_temp) * 0.5;//disabled this just air temp
	adjT = air_temp;//ignores the above 

	float SnowDepth = lagoon_snowpack * 100.0; //cm, snow pack thicknes
	if (lagoon_snowpack == 0)
	{
		Surf_Temp = adjT;//setting surf_temp to air  temp
	}
	else
	{
		Surf_Temp = adjT / (1.0 + SnowDepth);//else its airtemp adjusted for snowpack...adopted from soil Li code.

	}
	
	
	//ChihYu Shade effect on solar input---------------------------------------------------------------------------------------------------
	float wallHeight, cotAlpha, cosTheta, degTheta, interHeight, shadow, lightPercent, sinAlpha,declinationS;
	declinationS = 23.45 * sin((2 * pi * (284 + jday) / 365));//T.Day instead of jday. Need to ask Chih-Yu what T.Day resolves to
	float tankRadius;//lagoonRadius
	tankRadius = sqrt(MData.m_LagoonSurfaceArea / (pi));
	//L=site Latitude, H= hour angle but will assume in DNDC it's always 12 since we use daily solar radiation.
	float hourAngle;
	hourAngle = 12;
	float sLat = latitude;

	sinAlpha = max((cos(deg2rad(sLat)) * cos(deg2rad(declinationS)) * cos(deg2rad(hourAngle)) + sin(deg2rad(sLat)) * sin(deg2rad(declinationS))), 0);
	wallHeight = lagoonHeight - currentLagoonDepth;
	cotAlpha = pow((1.0 - pow(sinAlpha,2)),0.5)/sinAlpha;
	cosTheta = (wallHeight * cotAlpha / 2) / tankRadius;
	degTheta = acos(cosTheta);
	interHeight = tankRadius * pow(1 - pow(cosTheta, 2), 0.5);
	shadow = pi * pow(tankRadius, 2) - (4 * pi * pow(tankRadius, 2) * degTheta / (2 * pi) - 4 * (wallHeight * cotAlpha) / 2 * interHeight / 2);
	lightPercent = 1 - (shadow / MData.m_LagoonSurfaceArea);
	//lightPercent = 1.0;

	/*
	wall.h < -Htank - M.depth                              # the wall height above manure surface, m, double
		cot.alpha < -(1 - sin.alpha ^ 2) ^ (1 / 2) / sin.alpha         # angle, vector of numbers(288)
		cos.theta < -(wall.h * cot.alpha / 2) / ri                 # the angle in the circle - circle intersection, vector of numbers(288)
		deg.theta < -acos(cos.theta)                         # vector of numbers(288)
		Intersection.h < -ri * (1 - cos.theta ^ 2) ^ (1 / 2)           # the height(m) of triangle in the circle - circle intersection, vector of numbers(288)
		shadow < -pi * ri ^ 2 - (4 * pi * ri ^ 2 * deg.theta / (2 * pi)
			- 4 * (wall.h * cot.alpha) / 2 * Intersection.h / 2)  # shadow area, m2, vector of numbers(288)
		light.d < -1 - (shadow / Au)                             # the percentage that sunlight on the surface, between 0 - 1
		light.d[is.nan(light.d)] < -1
		*/



	//Tim energy balance method------------------------------------------------------------------------------------------------------------------------------------------
//lagoonTempPartition[1][1] at this point is yesterdays surface temperature
	//hcv.ms=Nu L ka / L eff 
	float hcv, lagoonLgth, netRad, netEvap, netConv1, netConv2, sumEnergy, tankEnergy, tankTempChange,reynoldsNum,nusselt;
	lagoonLgth = sqrt(MData.m_LagoonSurfaceArea / 3.14) * 2;//meters

	reynoldsNum = 310000000;//calibrated value //Reynolds num 	
		nusselt = (0.037 * pow(reynoldsNum,0.8) - 871.0) * (pow(0.709, 1 / 3));
		//hcv = 31695.14483 * 0.0258 / lagoonLgth;//W m2 K
		hcv = nusselt * 0.0258 / lagoonLgth;//W m2 K
	netRad = MData.m_LagoonSurfaceArea * DayPETRN * 1.2*lightPercent;//MJ/day///added factor for shadow to reduce  incoming solar radiation as % due to lagoon wall height.
	
	//Birk EVAPORATION CODE -------------------------------------------------------------------------------------------------------------------------------------------------

	float maxTemp, minTemp, maxRH, minRH, elev, lat, DOY, wind_2m;
	float radiation, evaporation;

	//set climate variables to new evap algorithm variables.
	maxTemp = max_temp;//climate
	minTemp = min_temp;
	lat = latitude;
	DOY = jday;
	maxRH = humidity;//don't estimate max or min relative humidity, just use average RH
	minRH = humidity;
	elev = 75.0;//currently fixed value for elevation in (m). Could modify for input.
	wind_2m = wind_speed;


	
	penman_evap penman;
	atmospheric_cal atmoPara;
	
	radiation = atmoPara.net_radiation(maxTemp, minTemp, maxRH, minRH, elev, lat, DOY);
	evaporation = penman.net_evaporation(wind_2m, elev, maxTemp, minTemp, maxRH, minRH, DOY, lat)/1000;//net evaporation m of water.
	if (lagoon_snowpack > 0)evaporation = 0;
	//Birk updated net evaporation
	netEvap = MData.m_LagoonSurfaceArea * evaporation * 1000 * 2265 / 1000;//MJ/m2/day // *0.4 evap partiton *1000 mm to m of water *2265/1000 = energy conversion for evap. 
	//--------------------------------------- END BIRK EVAP CODE --------------------------------------------------------------------------------------------------------------------

	//old method for calculating net Evaporation based off of DayPET @ 40%
	//netEvap = MData.m_LagoonSurfaceArea * DayPET * 0.4 * 1000 * 2265 / 1000;//MJ/m2/day // *0.4 evap partiton *1000 mm to m of water *2265/1000 = energy conversion for evap. 
	
	
	

	tankEnergy = (MData.m_LagoonSurfaceArea * currentLagoonDepth * 1000) * 4187 / 1000000 *0.2 ;//MJ/day //capped at 20% of total tank energy --- calibrated . specific heat of water is  4187 KJ/kg Degree C  
	netConv1 = hcv * ((lagoonTempPartition[1][1] + 273) - (air_temp + 273));
	netConv2 = netConv1 * MData.m_LagoonSurfaceArea * 86400 / 1000000;//MJ/day
	sumEnergy = netRad - netEvap - netConv2;
	tankTempChange = sumEnergy / tankEnergy;
	tankTempChange = min(10.0, max(tankTempChange, -10.0)); //was capping maximum energy change with respect to maximum oC daily temp change. Was -5 +5

	

	//ensuring that the current Lagoon Depth is greater than zero to calculate Surf_temperature
	if (currentLagoonDepth > 0.0)
	{

		if (lagoon_snowpack > 0 || lagoon_ice[1] > 0 ) //if there is a snowpack or surface ice then reduce the tank temperature change. 
		{
			tankTempChange = tankTempChange / (1);//BIG Dampener on expected tank temperature change when ICE or SNOWPACK is pressent. 
		}

		Surf_Temp = tankTempChange + lagoonTempPartition[1][1];//Surf Temp is the net energy balance differencial due to evaporative and  lowave differences  in energy + 
	}


	//store older top partion surface tempeature 
	float oldSurfaceTemp = lagoonTempPartition[1][1];
	lagoonTempPartition[1][1] = Surf_Temp;
	int zz;
	for (zz = 1; zz < 2; zz++)
	{
		///start Li Heat Flux CODE -- Note this code is dynamic with lagoon depth.

		int WV = 570;//270 default This value influences the correlation with air temperature - higher value will correlate the depth better with air temp..was 420
		for (n = 1; n <= WV; n++)
		{
			for (l = 1; l <= currentLayerDepth; l++)
			{
				//K[l]=86400.0 * ((1.0 - sts[l]) * Ksoil + sts[l] * day_wfps[l] * 0.0057);





				a = 150.0; //5000 //fudge factors //1000 warms it up.//150
				b =  0.001;//fudge factors - influences bottom profile 2000  0.001
				if (l == 1)
				{
					if (lagoon_snowpack < 0)lagoon_snowpack = 0.0;
					if (lagoon_ice[1] < 0) lagoon_ice[1] = 0.0;
					float F_snow = 100.0 * (lagoon_snowpack + lagoon_ice[1]);//brian was lagoon_snowpack * 50
					if (F_snow < 1.0) F_snow = 1.0;
					//F_snow = 1.0;

					//heat transfer between air and first layer

					if (lagoon_snowpack > 0.0 || lagoon_ice[1] > 0.0)
						outQ[l - 1] = 1.0 * (a * K[l] * (Surf_Temp - lagoonTempPartition[l][1]) / Z[l] / F_snow);//J/(cm2*day) //Surf_Temp - temp[1]
					else
						outQ[l - 1] = a * K[l] * (Surf_Temp - lagoonTempPartition[l][1]) / Z[l];
				}

				if (l < currentLayerDepth)//20 layers in the lagoon.
				{
					Kave = (K[l] + K[l + 1]) / 2.0; //average thermal capacity of the two layers.
					//heat from layer l to l+1
					outQ[l] = 800 * Kave * (lagoonTempPartition[l][1] - lagoonTempPartition[l + 1][1]) / (Z[l + 1] - Z[l]);//was 550
				}
				else
				{
					//heat from bottom layer to deeper soil
					outQ[l] = b * K[l] * (lagoonTempPartition[l][1] - yr_avetj) / (540 - Z[l]);//yr_avetj //makes heat loss out bottom near zero 2480000
					//200	   /default was 400
				}

				dQ = outQ[l - 1] - outQ[l];

				float heatCapDepth;
				heatCapDepth = MData.m_LagoonSurfaceArea * (depth_Partition) * 1000 * mC[l];//Joules/day
				float dT = dQ / heatCapDepth;//mC[l]heatCapDepth
				dT = min(5.050, max(-0.010, dT));//min(5.05, max(-0.010, dT));
				if (l >= 1)
				{
					if (lagoonTempPartition[l][1] <= -99.8)
					{
						lagoonTempPartition[l][1] = lagoonTempPartition[l - 1][1];
					}
					lagoonTempPartition[l][1] += dT;
				}
				//if(lagoonTempPartition[1][1]>=yr_avetj) lagoonTempPartition[l][1] = min(lagoonTempPartition[1][1], max(yr_avetj, lagoonTempPartition[l][1]));
				//else lagoonTempPartition[l][1] = min(yr_avetj, max(lagoonTempPartition[1][1], lagoonTempPartition[l][1]));


			} // l loop

		} // n

	  //////////////////end li's Heat Flux Code
	}
	//lagoonTempPartition[1][1] = Surf_Temp;
	if (lagoon_snowpack == 0 && lagoon_ice[1] == 0)                              //&& lagoon_ice[1] == 0   ---was causing prolonged freezing of lagoon once we changed to improved evaporation code. Need way to warm up surface 
		{
		lagoonTempPartition[1][1] = (air_temp + Surf_Temp) / 2;//once snowpack melts off the surface temperature of lagoon is set to be the average (air_temp + calcualted Surface temp)
		}
	else
	{
		//lagoonTempPartition[1][1] = oldSurfaceTemp;
	}
	//was resetting the surface temperature.

	//////////////////////////////////////////lagoon_ice routine for simulating an ice layer. Does not modify temperature. Using it for a condition of insulation if snowpack isn't present--- again borrowed from SOIL routines
	float Vwater, dQQ;

	for (l = 1; l <= 1; l++)
	{
		float sts;
		sts = 1 - 1.05 / 2.65;
		float pQ1, pQ2, d_ice = 0;
		float ps = depth_Partition * sts;//sts[l]
		float max_water = ps * 10000.0;//ps
		if (MData.lagoon_days == 1)lagoon_ice[1] = 0.0;

		Vwater = water[1][GN] / 1000;  //  m3 water	//total volume of tank

		if (lagoonTempPartition[l][1] < 0.0 && air_temp < 0) //Lagoon freeze
		{
			if (Vwater > 0.0)
			{
				pQ1 = -lagoonTempPartition[l][1] * mC[l]; //J/layer, heat release when T->0
				pQ2 = Vwater * (4100000.0 - 2100000.0); //J/layer, water heat capacity


				if (pQ1 > pQ2) //totally freeze
				{




					dQQ = pQ2; //J/layer/ha
					 //lagoonTempPartition[l][1] += (dQQ / mC[l]);
					d_ice = Vwater; //m3 water/lay/ha
					Vwater = 0.0;

					lagoon_ice[l] += d_ice;//m3 water/lay/ha
					//water[1][GN] -= d_ice/10000.0; //Vwater / 10000.0; // m water/layer

					//day_ice += d_ice/10000.0;
					//if(day_ice<0.0) day_ice = 0.0;

				}
				else //partially freeze
				{
					dQQ = pQ1;
					//lagoonTempPartition[l][1] = 0.0;
					d_ice = dQQ / (4100000.0 - 2100000.0);

					if (d_ice > Vwater)
						d_ice = Vwater;//m3 water/lay/ha
					else
						d_ice = d_ice;

					//Vwater -= d_ice;

					lagoon_ice[l] += d_ice; //m3 water/lay/ha	

					//water[1][GN] -= (d_ice / 10000.0); // m water/layer
					//day_ice += d_ice/10000.0;// m water/layer
					//if(day_ice<0.0) day_ice = 0.0;
				}

				//if(lagoon_ice[l]/10000.0 > ps) lagoon_ice[l] = ps * 10000.0;
			}
			else
			{
				//d_ice = 0.0;
			}

		}
		else  //thawing
		{
			if (lagoon_ice[l] > 0.0 && lagoonTempPartition[l][1] >= 0.0)
			{
				pQ1 = lagoonTempPartition[l][1] * mC[l];//0.1;//0.05;
				//pQ2 = 2.0 * ice[l] * (4100000.0 - 2100000.0);
				pQ2 = lagoon_ice[l] * (4100000.0 - 2100000.0);

				if (pQ1 > pQ2) //totally thawing
				{
					dQQ = pQ2;
					//lagoonTempPartition[l][1] -= dQQ / mC[l];
					d_ice = lagoon_ice[l];

					//	Vwater += d_ice;
					lagoon_ice[l] = 0.0;
					//water[1][GN] += d_ice / 10000.0; // m water/layer

					//day_ice -= d_ice/10000.0;
					//if(day_ice<0.0) day_ice = 0.0;
				}
				else //partially thawing
				{
					dQQ = pQ1;
					//lagoonTempPartition[l][1] = 0.0;
					//d_ice = -0.5 * pQ1 / (4100000.0 - 2100000.0);
					d_ice = pQ1 / (4100000.0 - 2100000.0);
					if (d_ice > lagoon_ice[l]) d_ice = lagoon_ice[l];
					//Vwater += d_ice;
					lagoon_ice[l] -= d_ice;// m3 water/layer/ha

					//water[1][GN] += d_ice / 10000.0; // m water/layer
					//day_ice -= d_ice/10000.0;
					if (lagoon_ice[l] < 0.0) lagoon_ice[l] = 0.0;
				}
				//if(lagoon_ice[l]>max_water) 
					//lagoon_ice[l] = max_water;
			}
			else
			{
				d_ice = 0.0;
			}

		}

		if (lagoon_ice[l] < 0.0) lagoon_ice[l] = 0.0;

		// if (water[1][GN] < 0.0) water[1][GN] = 0.0;

		 //total_lagoon_ice += (lagoon_ice[l]/10000.0); //m water for profile

	}//layer loop



			  //defined for comming up with a lag_coeff for influencing day to day temperature. Not using currently as heat-flux method seems to work ok.




	float depthLgFactor;



	int newT1;
	for (newT1 = 1; newT1 <= currentLayerDepth; newT1++)
	{
		/*
		//disabled the lag_coeff for now.....
			if(newT1==1)depthLgFactor=0.0001;
			else
			//depthLgFactor=log10(l*.1*10/2+0.001);
			depthLgFactor=pow((float)newT1/20,1/(float)newT1);
				lag_coeff=min(0.5,max(pow(depthLgFactor,1.05-currentLagoonFraction),0.0));
		if(lagoonTempPartition[newT1][0]>-30.0)
		lagoonTempPartition[newT1][1]=(lag_coeff*lagoonTempPartition[newT1][0])+(1-lag_coeff)*lagoonTempPartition[newT1][1];
		*/

		sumLagoonPartition += lagoonTempPartition[newT1][1];
	}
	temp[GN] = (sumLagoonPartition) / currentLayerDepth;//divides the sum by the number of partitions to come up with an average tank temperature
	int bb;
	for (bb = 1; bb <= 100; bb++)

	{
		lagoonTempPartition[bb][0] = lagoonTempPartition[bb][1];
	}





	oldLayerDepth = currentLayerDepth;//gotta store the current day layer number for bottom of lagoon.
	MData.LagoonT[1] = lagoonTempPartition[1][1];	//sets the LagoonT for surface temperature to top layer of partition when no snow


//writes out the interval temperatures.	
	int xb;//defines a counter
	for (xb = 1; xb <= 20; xb++)//loop to set the defined intervals for depth 0.25,0.5,0.75,1.00,1.25 ... meters)

	{
		int layerNumberLagoon;//defines variable to hold the layer number for the equivalent depth

		layerNumberLagoon = int(0.10 * xb / depth_Partition + 1);//discerns the appropriate depth for a given height interval at 0.25 m * the loop counter

		if (currentLagoonDepth > (0.10 * xb))
		{
			MData.LagoonT[xb + 1] = lagoonTempPartition[layerNumberLagoon][1]; //sets MData.LagoonT to the equivalent temperate partitiion with no snow.
		}
		else
		{
			MData.LagoonT[xb + 1] = -99.9;
		}

	}


	day_wfps[GN] = 1.0;
	Eh[GN] = -250.0;

	if (MData.m_LagoonCover == 1)//air open
		lagoon_windspeed = wind_speed;
	else
		lagoon_windspeed = 0.0;


	

//OLD METHOD BASED off of DAYPET-----------------------------------
	
	 /*
	//need to check which function is estimating DayPET (tool.cpp, DNDC_SoilPhysics, etc)
	mm_DayPET = DayPET * (1.0 + wind_speed * 0.01);//m water/day //enhanced by windspeed

	if (MData.m_LagoonCover == 1)//air open 
		MData.day_lagoon_EV = (0.2 * mm_DayPET) * MData.m_LagoonSurfaceArea * 1000.0;//m3 -> kg water// * 0.09 //Evap is being set to full PET...seems problematic 
	else if (MData.m_LagoonCover == 2)//sheltered 
		MData.day_lagoon_EV = 0.4 * (0.2 * mm_DayPET) * MData.m_LagoonSurfaceArea * 1000.0;
	else //covered
		MData.day_lagoon_EV = 0.1 * (0.2 * mm_DayPET) * MData.m_LagoonSurfaceArea * 1000.0;
		*/
	
//OLD EVAP METHOD END-------------------------------------

	
//BIRK Not sure why I'd need to reduce evaporation to 20% of new evaporation calculation. Seems to evap a lot more than old method otherwise.
	
	if (MData.m_LagoonCover == 1)//air open 
		MData.day_lagoon_EV = (evaporation) * MData.m_LagoonSurfaceArea * 1000.0;//m3 -> kg water// * 0.09 //Evap is being set to full PET...seems problematic 
	else if (MData.m_LagoonCover == 2)//sheltered 
		MData.day_lagoon_EV = 0.4 * (evaporation) * MData.m_LagoonSurfaceArea * 1000.0;
	else //covered
		MData.day_lagoon_EV = 0.1 * (evaporation) * MData.m_LagoonSurfaceArea * 1000.0;
		


	if (water[1][GN] <= MData.day_lagoon_EV)
	{
		MData.day_lagoon_EV = water[1][GN];//set evap to be equal to water left in tank...gross oversimplification
		water[1][GN] = 0.0;
	}
	else
	{
		water[1][GN] -= MData.day_lagoon_EV;//else remove the lagoon_EV from water pool
	}

	MData.yr_lagoon_EV += MData.day_lagoon_EV;//annual lagoonEV +day lagoonEV

	if (MData.m_LagoonCover == 1)//air open
	{
		LInRain = rainfall * MData.m_LagoonSurfaceArea * 1000.0; //kg water

		water[1][GN] += LInRain;//add incoming rainfall to open lagoon

		MData.yr_lagoon_InRain += LInRain;
	}

	if (water[1][GN] > MData.m_LagoonCapacity * 1000.0|| currentLagoonFraction>1.0)
	{
#ifdef LINUX		
		char EMSS[200];
		sprintf(EMSS, "Lagoon is overflowed");
		MData.EMDD++;
		ErrorMessage(EMSS, MData.EMDD);
#else
		CString note;
		note.Format("Lagoon is overflowed!");
		AfxMessageBox(note);
#endif
		exit(0);
	}



//old climate code
/*
	float mm_DayPET, LInRain=0.0;

	//lagoon temperature
	if(facility==0) temp[GN] = air_temp;

	if(MData.lagoon_days==1) 
	{
		MData.LagoonT[1] = temp[GN];	
		MData.LagoonT[2] = temp[GN];
		MData.LagoonT[3] = temp[GN];
		MData.LagoonT[4] = temp[GN];
		MData.LagoonT[5] = temp[GN];
		MData.bottomT = temp[GN];
	}
	else
	{
		float ddT=0.0;
		MData.LagoonT[1] += 0.05 * (temp[GN] - MData.LagoonT[1]);
	
		ddT = (MData.LagoonT[1] - 10.0) / 5.0;
		//if(ddT<0.0) ddT = 0.0;
			
			MData.LagoonT[2] = MData.LagoonT[1] - ddT;
			MData.LagoonT[3] = MData.LagoonT[1] - 2.0 * ddT;
			MData.LagoonT[4] = MData.LagoonT[1] - 3.0 * ddT;
			MData.LagoonT[5] = MData.LagoonT[1] - 4.0 * ddT;
	}

	temp[GN] = MData.LagoonT[2];

	day_wfps[GN] = 1.0;
	Eh[GN] = -250.0;

	if(MData.m_LagoonCover==1)//air open
		lagoon_windspeed = wind_speed;
	else
		lagoon_windspeed = 0.0;

	mm_DayPET = DayPET * (1.0 + wind_speed * 0.01);//m water/day

	if(MData.m_LagoonCover==1)//air open 
		MData.day_lagoon_EV = mm_DayPET * MData.m_LagoonSurfaceArea * 1000.0;//m3 -> kg water// * 0.09 
	else if(MData.m_LagoonCover==2)//sheltered 
		MData.day_lagoon_EV = 0.4 * mm_DayPET * MData.m_LagoonSurfaceArea * 1000.0;
	else //covered
		MData.day_lagoon_EV = 0.1 * mm_DayPET * MData.m_LagoonSurfaceArea * 1000.0;

	if(water[1][GN] <= MData.day_lagoon_EV) 
	{
		MData.day_lagoon_EV = water[1][GN];
		water[1][GN]=0.0;
	}
	else
	{
		water[1][GN] -= MData.day_lagoon_EV;
	}

	MData.yr_lagoon_EV += MData.day_lagoon_EV;

	if(MData.m_LagoonCover==1)//air open
	{
		LInRain = rainfall * MData.m_LagoonSurfaceArea * 1000.0; //kg water

		water[1][GN] += LInRain;

		MData.yr_lagoon_InRain += LInRain;
	}

	if(water[1][GN] > MData.m_LagoonCapacity * 1000.0)
	{
#ifdef LINUX		
		char EMSS[200];
		sprintf(EMSS, "Lagoon is overflowed");
		MData.EMDD++;
		ErrorMessage(EMSS, MData.EMDD);
#else
		CString note;
		note.Format("Lagoon is overflowed!");
		AfxMessageBox(note);
#endif
		exit(0);
	}
*/
}

void class_manure::lagoon_nh3(int GN, float *temp, float *nh3, double water[25][250], float *nh4, float *sph,
							  float LagoonCapacity, float disturbance, float *urea, int jday)
{
	//Chemical equilibrium: NH4+ + OH- = NH3 + H2O
	float BAC = 0.0;

	if(temp[GN]>0.0) 
	{
		float ckk = 1.0, ccc = 1.0, dall = 1.0, dsdd = 1.0, crust = 1.0; 

		if(urea[GN]>0.0)
		{
			nh4[GN] += urea[GN];
			urea[GN] = 0.0;
		}

		float PAA = 0.0001 * powf(sph[GN], 4.3);
		PAA = min(1.0, max(0.0, PAA));

		float TAA = nh4[GN] + nh3[GN];

		if(TAA<=0.0)
		{
			nh4[GN] = 0.0;
			nh3[GN] = 0.0;
		}
		else
		{
			nh3[GN] = TAA * PAA;
			nh4[GN] = TAA - nh3[GN]; //kg N/ha in layer l	
		}

		if(disturbance<=0.0)
		{
			if(MData.m_LagoonCover==1) ccc = 1.2;//open
			else if(MData.m_LagoonCover==2) ccc = 0.8;//shelter
			else ccc = 0.1;//covered
		}
		else
			ccc = 1.0;

		dsdd = 1.0 + 0.5 * disturbance;

		BAC = (float)powf(temp[GN], 1.0);

		if(disturbance<=0.0)
		{
			if(MData.LagoonCrustC>10.0) crust = 35904 * powf(MData.LagoonCrustC, -4.223);//0.0003 * MData.LagoonCrustC * MData.LagoonCrustC - 0.0515 * MData.LagoonCrustC + 2.2465;
			else crust = 1.0;

			crust = min(1.0, max(0.0, crust));
		}
		else
			crust = 1.0;


		dall = 0.00005 * ckk * ccc * dsdd * BAC * crust;
		
		dall = min(1.0, max(0.0, dall));

		float ddNH3 = dall * nh3[GN];

		MData.day_lagoon_nh3 += ddNH3;
		nh3[GN] -= ddNH3;
	}

	

/*

	double wd1, wd2, Kw, Ka, hydrogen, hydroxide, V_water, mol_nh4, mol_nh3, dnh3=0.0;//, old_nh3=nh3[GN]; 

	wd1 = (double)pow(10.0, -15.0);
	wd2 = (double)pow(10.0, -5.0);
	Kw = 1.945 * exp(0.0645 * temp[GN]) * wd1;//water dissociation constant
	Ka = (1.416 + 0.01357 * temp[GN]) * wd2;//NH4+/NH3 equilibrium constant
	hydrogen = (double)pow(10.0f, -sph[GN]);//mol/L
	hydroxide = Kw / hydrogen;//mol/L

	//V_water = LagoonCapacity * 1000.0;//liter water

	float EmiF=0.0;
	if(MData.m_LagoonCover==1) EmiF = 0.8;
	else if(MData.m_LagoonCover==2) EmiF = 0.7;
	else if(MData.m_LagoonCover==3) EmiF = 0.05;
	else {}
	
	mol_nh4 = nh4[GN] / 14.0;// / V_water;//kg N -> mol/L
	mol_nh3 = mol_nh4 * EmiF;//hydroxide / Ka;//mol/L

	if((mol_nh4 + mol_nh3)<=0.0)
	{
		nh4[GN] = 0.0;
		nh3[GN] = 0.0;
	}
	else
	{
		float cvf = mol_nh4 / (mol_nh4 + mol_nh3); 
		float TtN = nh4[GN]+nh3[GN];
				
		//if(flood_flag==1) cvf *= 0.2;
		nh4[GN] = TtN * cvf; 
		nh3[GN] = TtN - nh4[GN];//kg N/ha in layer l		
	}

	if(disturbance>0.0)
	{
		if(MData.m_LagoonCover==3)
			 dnh3 = (0.001 + 0.15 * disturbance) * nh3[GN] ;
		else
			dnh3 = (0.001 + 0.02 * disturbance) * nh3[GN] ;
	}
	else
		dnh3 = 0.075 * nh3[GN] * temp[GN] / 45.0;

	nh3[GN] -= dnh3;
	MData.day_lagoon_nh3 += dnh3;

	nh4[GN] += nh3[GN];
	nh3[GN] = 0.0;
*/
/*	//Modified Two-film model by Visscher et al. 2002
	float FLUX_AItoBA_NH3;

	float Air_nh3 = 0.0;//1.0;//background NH3 concentration in the air (ug N/m3)
	float Tk = temp[GN] + 273.16; //Kelvins teperature, degree K
	float KH = 239000.0 / Tk * (float)exp(-4151.0/Tk);//Henry's law constant
	float u8 = lagoon_windspeed; //u8 is wind speed (m/sec) at 8 meter height
	float Patm = 760.0; //atmospheric pressure (mmHg) or 101.325 kPa
	
	float Mair = 28.97; //molecular weight of air
	float Mnh3 = 17.0; //molecular weight of NH3
	float Mh2o = 18.0; //molecular weight of H2O
	float ADVair = 20.1; //atomic diffusion volume (cm3/mol) of air
	float ADVnh3 = 14.9; //atomic diffusion volume (cm3/mol) of NH3
	float ADVh2o = 12.7; //atomic diffusion volume (cm3/mol) of water

	float KG_h2o = 18.568 + 703.61 * u8 / 360000.0;//H2O mass tranfer coefficient (m/sec) in the air boundary layer

	float ww1 = powf(10,-7) * pow(Tk, 1.75) * pow((Mair+Mnh3)/(Mair*Mnh3), 0.5);
	float ww2 = Patm * pow(pow(ADVair, 0.3333)+pow(ADVnh3, 0.3333), 2.0);
	float DA_nh3 = ww1 / ww2; //diffusion coefficient (m2/sec) of NH3 in the air phase
	float uu1 = powf(10,-7) * pow(Tk, 1.75) * pow((Mair+Mh2o)/(Mair*Mh2o), 0.5);
	float uu2 = Patm * pow(pow(ADVair, 0.3333)+pow(ADVh2o, 0.3333), 2.0);
	float DA_h2o = uu1 / uu2;//diffusion coefficient (m2/sec) of H2O in the air phase	
	float DW_nh3 = 6.14526 * powf(10.0, -15.0) * Tk / (float)exp(1622.0/Tk - 12.40518);//diffusion coefficient (m2/sec) of NH3 in the liquid phase
	float DW_o2 = 7.28236 * powf(10.0, -15.0) * Tk / (float)exp(1622.0/Tk - 12.40518);////diffusion coefficient (m2/sec) of O2 in the liquid phase
	float KL_o2 = 0.6034 * (float)exp(0.2361*u8) / 360000.0;//KL_o2 is O2 mass tranfer coefficient (m/sec) in the liquid boundary layer
	float KL_nh3 = KL_o2 * powf((DW_nh3/DW_o2), 0.57);//KL_nh3 is NH3 mass tranfer coefficient (m/sec) in the liquid boundary layer
	float KG_nh3 = 0.2;//KG_h2o * powf((DA_nh3/DA_h2o), 0.67);//KG_nh3 is NH3 mass tranfer coefficient (m/sec) in the air boundary layer
	
	float BL_NH3 = (nh3[GN] * 1000000000.0) / (water[1][GN]/1000.0);//ug N/m3

	float FLUX_NH3_LiquidInterface = 2.5 * KL_nh3 * (BL_NH3 - MData.LI_NH3);//NH3 transferred from bulk water to the liquid interface, ug N/m2/second

	BL_NH3 -= FLUX_NH3_LiquidInterface;//ug N/m3
	MData.LI_NH3 += FLUX_NH3_LiquidInterface;//ug N/m3

	float FLUX_NH3_GasInterface = KL_nh3 * (MData.LI_NH3 - MData.AI_NH3);//NH3 transferred from the liquid interface to the air interface, ug N/m2/second

	MData.LI_NH3 -= FLUX_NH3_GasInterface;//ug N/m3
	MData.AI_NH3 += FLUX_NH3_GasInterface;//ug N/m3

	Air_nh3 *= 1.0 / (lagoon_windspeed + 1.0);
	
	if(MData.AI_NH3 > Air_nh3) 
		FLUX_AItoBA_NH3 = KG_nh3 * (MData.AI_NH3 - Air_nh3);//NH3 transferred from the air interface to the bulk air, ug N/m2/second
	else
		FLUX_AItoBA_NH3 = 0.0;

	MData.AI_NH3 -= FLUX_AItoBA_NH3;

	MData.day_lagoon_nh3 += 3.0 * FLUX_AItoBA_NH3 * MData.m_LagoonSurfaceArea * 86400.0 / 1000000000.0; //0.7//kg NH3-N/day from the lagoon surface
	
	if(MData.m_LagoonCover>1)
	{
		float retain_nh3 = MData.day_lagoon_nh3 * (0.5 * (float)MData.m_LagoonCover - 1.2);

		MData.day_lagoon_nh3 -= retain_nh3;

		Air_nh3 += retain_nh3;
	}

	nh3[GN] -= MData.day_lagoon_nh3;*/
}

void class_manure::lagoon_denitrification(int GN, float *temp, float *nh4, float *no3, float *soc, float *doc,
										  float *no2,float *no,float *n2o,float *n2, float *dphum, float rcnm, float disturbance)
{
	if(temp[GN]>0.0) 
	{
		float ckk = 1.0, ccc = 1.0, dall = 1.0, dsdd = 1.0; 

		if(MData.lagoon_days<60) ckk = 0.0;
		else if(MData.lagoon_days>=60&&MData.lagoon_days<90) ckk = (float)(MData.lagoon_days-60) / 30.0;
		else if(MData.lagoon_days>=90&&MData.lagoon_days<120) ckk = (float)(120-MData.lagoon_days) / 30.0;
		else ckk = 0.0;

		if(MData.m_LagoonCover==1) ccc = 1.0;//open
		else if(MData.m_LagoonCover==2) ccc = 1.0;//shelter
		else ccc = 1.2;//covered
		
		float BAC = powf(temp[GN], 4.0) * ckk;

		float ddNH4 = 0.000005 * BAC * nh4[GN];

		nh4[GN] -= ddNH4;

		no3[GN] += ddNH4 * 0.9;

		MData.day_lagoon_n2o += ddNH4 * 0.1;

		MData.day_lagoon_n2 += no3[GN];

		no3[GN] = 0.0;
	}
/*

	float fact_t, fact_m, micro_growth, micro_death, micro_delta, wwzz, k, nno, ae_no, ae_n2o;
	float nitrifier, denitrifier;

	nitrifier = soc[GN] * RBO * FD / 500.0;// * Fmn;

	fact_t = powf(3.503,(60.0-temp[GN])/(60.0-34.22))* (float)exp(3.503*(temp[GN]-34.22)/(60.0-34.22)); //O'neill
    fact_t = min(1.0, max(0.0, fact_t));
    
    fact_m = 0.001;//0001;

	wwzz = nitrifier * fact_t * fact_m;
    
	wwzz = min(0.1, max(0.0, wwzz));

	float dNH4d = nh4[GN] * wwzz;

    no3[GN] += dNH4d;
	nh4[GN] -= dNH4d;

	MData.day_lagoon_n2o = 0.05 * no3[GN];//de_rate + n2o[GN] + no[GN] + ae_n2o;
	MData.day_lagoon_n2 = 0.95 * no3[GN];//de_rate + n2[GN] + no2[GN];
	no3[GN] = 0.0;
	n2o[GN] = 0.0;
	no[GN] = 0.0;
	no2[GN] = 0.0;
	n2[GN] = 0.0;
*/
/*    // developed by Florian based on Blagodatsky and Richter 1998
    micro_growth = 0.01 * (doc[GN] / (1.0 + doc[GN]) + fact_m / (1.0 + fact_m)) / 24.0;
    if (micro_growth < 0.0) micro_growth = 0.0;

    micro_death = 0.01 * (nitrifier) * 1.0 / (1.0 + doc[GN]) / (1.0 + fact_m) / 24.0;

    micro_delta = (micro_growth - micro_death) * nitrifier * fact_t * fact_m;

    nitrifier += micro_delta;
    if (nitrifier<0.0) nitrifier = 0.0;

	k = 0.01;

	/////////////////////////////////////////////////////////////////////////////
	float Km, Ft, Vs, Bo, Tt, Tref, dE, Rr, Ut; 

	Km = 0.13; //conversion factor at 15 degree C

	//dE = 122000.0; //enthalpy of CH4 formation, J/mol
	//Rr = 8.31; //gas constant, J/mol/K   
	Tt = 273.15 + MData.LagoonT[1];//temp[GN];//absolute temperature, K
	Tref = 273.15 + 15.0;// reference temperature, K, 15.0
	Ft = (float)exp((-1.0/Tt + 1.0/Tref));//effect of temperature

	if(MData.m_LagoonCover==1)
		Bo = 3.0;//open
	if(MData.m_LagoonCover==2)
		Bo = 2.5;//sheltered
	else 
		Bo = 0.3;//covered

	if(MData.lagoon_days>1)
	{
		Ut = (float)(MData.lagoon_days - 55) * 0.01;

		if(MData.lagoon_days>100) Ut *= powf((100.0/(float)MData.lagoon_days),3.0);

		Ut = min(1.0, Ut);

		float STL = 0.01;
		float stl = dphum[GN]*STL;
		doc[GN] += stl;
		dphum[GN] -= stl;

		float difN = stl / rcnm;
		nh4[GN] += difN;

		if(dphum[GN]<0.0) dphum[GN] = 0.0;
	}
	else Ut = 0.0;

	float KWK = Km * Ft * Bo * Ut;
	KWK = min(1.0, max(0.0, KWK));
	///////////////////////////////////////////////////////////////////////////////
	
	nno = 0.001;//nitrifier * fact_m;
	
    nno = max(0.0, min(1.0, nno));

	if(nh4[GN]>=nno) 
		nh4[GN] -= nno;
	else 
	{
		nno = nh4[GN];
		nh4[GN] = 0.0;
	}

    ae_n2o = 0.001 * nno;// Ingwersen, 1998
	  
    nno -= ae_n2o;

    //day_lagoon_n2o += ae_n2o;
    //ae_n2o = 0.0;
*/

	

	//denitrification
/*	denitrifier = soc[GN] * RBO * FD;

	micro_growth = 0.0166 * (doc[GN] / (1.0 + doc[GN]) + fact_m / (1.0 + fact_m)) / 24.0;
    if (micro_growth < 0.0) micro_growth = 0.0;

    micro_death = 0.008 * (denitrifier) * 1.0 / (1.0 + doc[GN]) / (1.0 + fact_m) / 24.0;

    micro_delta = (micro_growth - micro_death) * denitrifier * fact_t * fact_m;

    denitrifier += micro_delta;
    if (denitrifier < 0.0) denitrifier = 0.0;

	float de_rate = 0.002 * denitrifier / (1.0 + denitrifier) * no3[GN];

	if(no3[GN] > de_rate) 
	{
		no3[GN] -= de_rate;
	}
	else
	{
		de_rate = no3[GN];
		no3[GN] = 0.0;
	}
*/
	
}

void class_manure::lagoon_ch4(int GN, float *temp, float *dphum, float *doc, float disturbance, int jday, float *rcr,
							  float *rcvl, float *rcl, float *CRB1, float *CRB2, float *crhl, float *crhr,
							  float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float *nh4)
{
//Ward+Brian Testing of Manure_DNDC prior to Birk
	
	float Km, Ft, Vs, Bo, Tt, Tref, dE, Rr, Ut, DifN;

	Km = 0.04; //conversion factor at 15 degree C

	dE = 122000.0; //enthalpy of CH4 formation, J/mol
	Rr = 8.31; //gas constant, J/mol/K   
	Tt = 273.15 + temp[GN];//temp[GN];//absolute temperature, K  MData.LagoonT[1]
	Tref = 273.15 + 15.0;// reference temperature, K, 15.0
	Ft = 0.01 * (float)exp(dE / Rr * (-1.0 / Tt + 1.0 / Tref));//effect of temperature

	Ft = max(0.0, min(1.0, Ft));

	//Ft = MData.LagoonT[1] / 45.0;

	if (MData.m_LagoonCover == 1)//open
		Bo = 2.0;//maximum CH4 producing capacity, kg CH4-C/kg SOC
	if (MData.m_LagoonCover == 2)//sheltered
		Bo = 2.5;
	else //covered
		Bo = 3.2;//0.5 * (float)MData.m_LagoonCover;

	//float STL = 0.0;
	if (MData.lagoon_days > 1)
	{


		Ut = min(1.0, max(0.0, Ft));
		//STL = min(1.0, max(0.0,STL));

		float AvailableC = rcvl[GN] + rcl[GN] + rcr[GN] + CRB1[GN] + CRB2[GN] + crhl[GN] + crhr[GN];

		float stl = AvailableC * Ft * 2.1;//time 1.0

		rcvl[GN] -= stl * rcvl[GN] / AvailableC;
		rcl[GN] -= stl * rcl[GN] / AvailableC;
		rcr[GN] -= stl * rcr[GN] / AvailableC;
		CRB1[GN] -= stl * CRB1[GN] / AvailableC;
		CRB2[GN] -= stl * CRB2[GN] / AvailableC;
		crhl[GN] -= stl * crhl[GN] / AvailableC;
		crhr[GN] -= stl * crhr[GN] / AvailableC;

		doc[GN] += stl;

		float DifN = stl / AvailableC * (rcvl[GN] / rcnrvl + rcl[GN] / rcnrl + rcr[GN] / rcnrr + CRB1[GN] / rcnb + CRB2[GN] / rcnb + crhl[GN] / rcnh + crhr[GN] / rcnh);

		nh4[GN] += DifN;


		float STL = (float)pow(((float)MData.lagoon_days / 365.0), 5.0);

		float KWK = 3000.0 * Km * Ft * Bo * STL;// * Ut; 0.015
		KWK = min(1.0, max(0.0, KWK));

		MData.day_lagoon_ch4 = doc[GN] * KWK;

		if (MData.day_lagoon_ch4 < 0.0) MData.day_lagoon_ch4 = 0.0;

		if (doc[GN] >= MData.day_lagoon_ch4)
		{
			doc[GN] -= MData.day_lagoon_ch4;
		}
		else
		{
			MData.day_lagoon_ch4 = doc[GN];
			doc[GN] = 0.0;
		}
	}
//END Ward and Brian testing of Manure_DNDC prior to Birk


//Low Emission CODE
//FLAG OFF for Nov25th 2022
/*
	float BAC = 0.0;

	if(temp[GN]>0.0) 
	{
		float ckk = 1.0, ccc = 1.0, dall = 1.0, dsdd = 1.0; 

		if(MData.lagoon_days<70) ckk = (float)MData.lagoon_days / 70.0;
		else ckk = 1.0;

		if(MData.m_LagoonCover==1) ccc = 1.2;//open
		else if(MData.m_LagoonCover==2) ccc = 0.8;//shelter
		else ccc = 0.6;//covered

		dsdd = 1.0 + 1.0 * disturbance;

		dall = 0.00000005  * ckk * ccc * dsdd;//0.0000005
		
		dall = min(1.0, max(0.0, dall));

		BAC = (float)powf(temp[GN], 4.0) * dall;
	}

	float ddDOC = BAC * doc[GN];

	MData.day_lagoon_ch4 = ddDOC;
	doc[GN] -= ddDOC;
	*/


/*	float Km, Ft, Vs, Bo, Tt, Tref, dE, Rr, Ut, DifN; 

	Km = 0.04; //conversion factor at 15 degree C

	dE = 122000.0; //enthalpy of CH4 formation, J/mol
	Rr = 8.31; //gas constant, J/mol/K   
	Tt = 273.15 + MData.LagoonT[1];//temp[GN];//absolute temperature, K
	Tref = 273.15 + 15.0;// reference temperature, K, 15.0
	Ft = 0.01 * (float)exp(dE/Rr * (-1.0/Tt + 1.0/Tref));//effect of temperature

	Ft = max(0.0, min(1.0, Ft));

	//Ft = MData.LagoonT[1] / 45.0;

	if(MData.m_LagoonCover==1)//open
		Bo = 2.0;//maximum CH4 producing capacity, kg CH4-C/kg SOC
	if(MData.m_LagoonCover==2)//sheltered
		Bo = 2.5;
	else //covered
		Bo = 3.2;//0.5 * (float)MData.m_LagoonCover;

	//float STL = 0.0;
	//if(MData.lagoon_days>1)
	{
		

		Ut = min(1.0, max(0.0, Ft));
		//STL = min(1.0, max(0.0,STL));

		float AvailableC = rcvl[GN] + rcl[GN] + rcr[GN] + CRB1[GN] + CRB2[GN] + crhl[GN] + crhr[GN];
		
		float stl = AvailableC * Ft;
		
		rcvl[GN] -= stl * rcvl[GN] / AvailableC;
		rcl[GN] -= stl * rcl[GN] / AvailableC;
		rcr[GN] -= stl * rcr[GN] / AvailableC;
		CRB1[GN] -= stl * CRB1[GN] / AvailableC;
		CRB2[GN] -= stl * CRB2[GN] / AvailableC;
		crhl[GN] -= stl * crhl[GN] / AvailableC;
		crhr[GN] -= stl * crhr[GN] / AvailableC;

		doc[GN] += stl;

		float DifN = stl / AvailableC * (rcvl[GN]/rcnrvl+rcl[GN]/rcnrl+rcr[GN]/rcnrr+CRB1[GN]/rcnb+CRB2[GN]/rcnb+crhl[GN]/rcnh+crhr[GN]/rcnh);

		nh4[GN] += DifN;
		

	//}
	//else 
		//STL = 0.0;

		float STL = (float)pow(((float)MData.lagoon_days / 365.0), 5.0);

		float KWK = 3000.0 * Km * Ft * Bo * STL;// * Ut; 0.015
		KWK = min(1.0, max(0.0, KWK));

		MData.day_lagoon_ch4 = doc[GN] * KWK;

		if(MData.day_lagoon_ch4<0.0) MData.day_lagoon_ch4 = 0.0;

		if(doc[GN]>=MData.day_lagoon_ch4) 
		{
			doc[GN] -= MData.day_lagoon_ch4;
		}
		else
		{
			MData.day_lagoon_ch4 = doc[GN];
			doc[GN] = 0.0;
		}
	}
*/

}


#endif


