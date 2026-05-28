#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <cmath>


#ifdef MANURE 
extern class_manure MData;
#endif

void class_model::N2O_balloon(int GN, float till_fact, float *sts, float *h, int jday, int flood_flag, int FloDays, float rainfall,
		float *O2_old, float *O2, float TTT, float *vvv, float *ave_anvf, int q, int *st,
		float *temp, int year, double water[25][250], float *day_wfps, float day_WT,
		int WTL, float total_ice, float *day_rco2, float *co2, int flo_num, float *ice, float *sph, float *Eh, 
		float *anvf, float *nh4, float *no3, float *no2, float *no, float *n2, float *doc, float *n2o,
		float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d,
		int LandUse, float *Tttoo, float ManureAddCN, int ManureDays, float *soc, float MicrobioIndex,
		float mRBO, float mFD, int WaterControl, int *crop, float *assim2, float *clay,
		float *fldcap, float by_passf, int NIDay1, int NIDay2,
		float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float WaterLeakRate,
		float *rcvl, float *rcl, float *rcr,
		float *day_soil_denitrification, float *wiltpt, float *CRB1, float *CRB2, float rcnb, 
		float *day_frostDOC, float *yr_frostDOC, float precipitation, int manuFlag, int irri_flag,
		float *FreezeDOC, float *nh3, float *urea, float LateralInflux, int drain_flag,
		int IrriRice_flag, FILE* HSM, int fertigate_flag,
		float hrPE0, float* DayFlux,float* dby_flux, int DroughtID, int YieldToday, 
		int drc, int scale, float ha, int livestock, float *day_nitrification, float *day_denitrification,
		int farm_flag, float rno3, float *day_inRainN,float denitMulti, float nitMulti,float N2N2OFactor, float *day_nitrify_n2ol, float *day_denitrify_n2ol)//day_inRainN was changed to pointer because wasn't carrying output to summary.
{
    float KC, KN;
    float u_no3, u_no2, u_no, u_n2o, U, DBG, DB, Nw;
    float d_no3, d_no2, d_no2_kk, d_no, d_n2o;
    float dn_co2, bypass_f;//d_co2,
	float Fde=1.0, Fph=1.0, Fmn=1.0, Fst=1.0, Fsm=1.0, Ftm=1.0;

    int   T, l, rain_hrs;
    float assim_N, air_poro_max;
    float TE[MAXSOILLAYER], phk1[MAXSOILLAYER], phk2[MAXSOILLAYER], phk3[MAXSOILLAYER];
	float cck, n3k, n2k, nok, n2o_k, DBD, da_no3;
    float da_no2, da_no2_kk, da_no;
    float da_n2o, DC, PORO;
	float aere=0.0;
    float lost_DOC, lost_no3;
    float leach_factor;
    float fact_t, fact_m, nno;
    float wwzz, ae_n2o, ae_no;
    float micro_growth, micro_death, micro_delta, k, AA;
	int flood_day=0;
	float EEE, RRR, nitrifier[MAXSOILLAYER], denitrifier[MAXSOILLAYER]; 
	int BL, EL;
	air_poro_max = 0.0;//init error
	if(GN>q)//manure
	{
		BL = GN; EL = GN; 

		till_fact = 1.0;

		//if(GN==(q+5)) temp[GN] *= 0.5;
	}
	else
	{
		BL = 1; EL = q;
	}

	float sts_h = 0.451 * h[1];//sts*h;

	CString DNF;
	
	
	no3_w[1] += (rno3 * (precipitation) * 10);

	*day_inRainN += (rno3 * (precipitation) * 10);
	
	
	if (jday==1) flood_day = 0;
    
	if (flood_flag==1) 
	{	
		flood_day = FloDays;
		if (flood_day > 20) flood_day = 20;
	}
/*
//code to add the effect of sequential rainfall days used to ramp up N2O emissions
	if(TTT==0)
	{oldTTT=oldTTT *.1;
	}
	if(oldTTT>0.0 && oldTTT<4.0)
	{
	 TTT=TTT+oldTTT*2; //default *2
	
	}
 oldTTT=TTT;
//end code to add 
*/

	


	
    PORO = 0.451 * 4.0;//sts
	
    if (flood_flag == 0)
    {
		rain_hrs = (int)TTT;//TTT is determined in climate section depending on amount of precipitation that fell on that day. Since the climate is daily and assumption is made to determine how much rain fell in an hour (crude estimate).
    }
    else
	{
		rain_hrs = 24;
		TTT = 24.0;
	}
#ifdef MANURE
	if (vvv[GN] <= 0.0)vvv[GN] = vvv[1];//added because vvv for manure was being initiatlized oddly
#endif
    KC = KCI * vvv[GN];
    KN = KNI * vvv[GN];

    if (st[1]>=12) bypass_f = 2.0;//2.0
    else bypass_f = 1.0 - 0.8 * by_passf;//1.2;
    
    dn_co2 = 0.0;
    assim_N = 0.0;

	if(GN>q) 
		ave_anvf[GN] = 0.0;
	else for(l=1; l<=q; l++) ave_anvf[l] = 0.0;

	for ( T = 1; T <= 24; T++ )
	{

		if(farm_flag==0)
		{
			hour_loop(hrPE0, DayFlux, dby_flux, DroughtID, YieldToday, drc, scale, ha, livestock, T);
			Substrate_leaching(T);
		}


		for (l = BL; l <= EL; l++)
		{

			float cc = 1.0;

			if (l <= q)
			{
				soil_oxygen_profile(l, T, rain_hrs, bypass_f, air_poro_max, flood_day,
					temp, year, jday, q, water, day_wfps, h, sts, O2, day_WT, WTL,
					total_ice, TTT, day_rco2, co2, flo_num, ice);
				/*
				if (day_wfps[l] > 0.550)
				{
					Eh[l] = 649.0;
				}
				else {
					Eh[l] = 100.0;
				}
				*/
			}
			else//manure
			{
				float ps = 0.5;//h[l] * sts[l];
				float actual_poro = ps * (1.0 - day_wfps[l]) + 0.0000001;//10000.0 * (1.0 - water[T][l] / ps) + 0.000001;//m3/layer/ha, actual pores
				float air_O2 = 0.299251;
				float full_O2 = air_O2 * ps * 10000.0;//g O2/layer/ha
				O2[l] = air_O2 * actual_poro * 10000.0;//g O2/layer/ha
				Eh[l] = 626.1 * O2[l] / full_O2; //Redox potential . Likely in the wrong range for denitrification due to considerations with tippping bucket mechanisms and difficulties in capturing hourly soil moisture above field capacity. 



			}

			float EhMulti;
			if (FreezeDOC[l] > 0)
				EhMulti = 0.01;
			else
				EhMulti = 0.3;//was 0.1//brazil 0.5

			if (Eh[l] >= 0.0)
				anvf[l] = (1.0 - Eh[l] / 650.0) * EhMulti;// * 0.1; //tried 850 with per layer calculated O2 in EH file
			else
				anvf[l] = 0.99;//full anaerobic

			//float denitFactor = day_wfps[l] / fldcap[l];


			if (st[1] == 12 && TTT > T) anvf[l] = 0.99;
			//else anvf[l] = 0.01;

			//if(flood_flag==1) anvf[l] = 0.99;
			//if (day_wfps[l] / fldcap[l] >= 1.0 && air_temp<5.0){anvf[l] = 0.3;}
			//else anvf[l] = 0.01;
			
			float currentWFPS, relativeWFPS;

			currentWFPS = day_wfps[l];
			relativeWFPS = currentWFPS / fldcap[l];

		/*
			if (fldcap[l] < 0.8)
			{
				if (relativeWFPS > 0.80)
				{
					anvf[l] = (relativeWFPS - 0.80) / 0.4; //relative denitrifier activity level
				}
				else
				{
					anvf[l] = 0.01;//mostly 99% aerobic 
				}
			}
			
			else
			{
			*/


			
			float waterFilledPoreSurf = 0.0;
			float waterFilledPore = 0.0;
			waterFilledPoreSurf = water[T][l] / (h[l] * sts[l]) + ice[1] / 10000.0 / (h[1] * sts[1]);
			waterFilledPore = water[T][l]/(h[l]*sts[l]) + ice[l] / 10000.0 / (h[l] * sts[l]);
			waterFilledPore = min(1.0, max(0.0, waterFilledPore));
				if (waterFilledPoreSurf >= fldcap[l])
				{
				  anvf[l] = 0.75;//anaerobic volumetric fraction
				  //anvf[1] = (day_wfps[1] - 0.70) / 0.4;
				}
				else if (waterFilledPoreSurf > 0.60)
				{
					anvf[l] = (waterFilledPoreSurf - 0.60) / 0.4; //relative denitrifier activity level
					//anvf[l]= 1 / (1.0 + exp(-20.0 * (waterFilledPoreSurf - 0.60)));
				}
				else
				{
					anvf[l] = 0.01;//mostly 99% aerobic 
				}
				
		//	}
				
				anvf[l] = anvf[l];
				
				
				ave_anvf[l] = anvf[l];



			
			anvf[l] = min(0.95, max(0.001, anvf[l]));
			ave_anvf[l] = anvf[l];

			// Allocate NH4+, NO3-, NO2-, NO, N2O, and DOC to anaerobic balloon 
			if (T == 1)
			{
				//if (temp[l]>9.0) TE[l] = (float)pow(2.0, ( temp[l] - 22.5) / 10.0);
				//else if (temp[l]>0.0) TE[l] = (0.0002 * (float)exp(.8255 * temp[3]));
				if (temp[l] > 0.0) TE[l] = 0.001 + temp[l] / 30.0;
				else TE[l] = 0.001;

				//if(ice[l]>0.0) TE[l] = 0.01; 			

				TE[l] = min(1.0, max(0.0, TE[l]));

				phk1[l] = 2.0 * (1.0 - 1.0 / (1.0 + (float)exp((sph[l] - 4.250) / 0.5))); //0.5

				phk2[l] = 2.0 * (1.0 - 1.0 / (1.0 + (float)exp((sph[l] - 5.250) / 1.0)));

				if (sph[l] <= 7.0 || manuFlag == 1)
					phk3[l] = 2.0 * (1.0 - 1.0 / (1.0 + (float)exp((sph[l] - 6.250) / 1.5)));
				else
					phk3[l] = 5.0 * (float)pow(10.0, -8) * (float)exp(2.5538 * sph[l]);
				//Michael Dannenmann et al. Soil Biology & Biochemistry 40(2008) 2317-2323.

				if (phk1[l] < 0.0) phk1[l] = 0.0;
				if (phk2[l] < 0.0) phk2[l] = 0.0;
				phk3[l] = min(100.0, max(0.0, phk3[l]));
			}

			if (st[l] >= 12) AA = 1.0;//st = soil texture class (1=sand, 11= heavy clay,  12=organic soil)
			else AA = 1.0;

			nh4_w[l] = (nh4[l]) * anvf[l] * AA;//determines the NH4 available in anaerobic pathway based on redox potential of soil layer
			nh4_d[l] = ((nh4[l]) - nh4_w[l]);//NH4 difference remiaining after above partitioning above. Anaerobic (D= Dry , W= Wet)
			if (nh4_d[l] < 0.0||jday==2)
			{
				float blah;
				blah = 1.0;
			}
			if (isnan(nh4[1]))
			{
				float blah;
				blah = 1.0;

			}

			nh4[l] = 0.0;//set remaining nh4[l] = 0.0 kg/ha
			//nh3[l] = 0.0;
			

			float pwN = no3[l] * anvf[l] * AA;//AA seems to be always 1.0 can ignore. 
			no3_w[l] += pwN;
			no3_d[l] = no3[l] - pwN;
			no3[l] = 0.0;

			no2_w[l] = no2[l] * anvf[l] * AA;//reminder anvf=redox potential
			no2_d[l] = no2[l] - no2_w[l];
			no2[l] = 0.0;

			no_w[l] = no[l] * anvf[l] * AA;
			no_d[l] = no[l] - no_w[l];
			no[l] = 0.0;

			n2o_w[l] = n2o[l] * anvf[l] * AA;
			n2o_d[l] = n2o[l] - n2o_w[l];
			n2o[l] = 0.0;

			n2_w[l] = n2[l];
			n2[l] = 0.0;

			//if(T==1&&l==1) doc[l] *= 0.0;

			float pwC = doc[l] * anvf[l] * AA;
			doc_w[l] += pwC;
			doc_d[l] = doc[l] - pwC;
			doc[l] = 0.0;

			// Allocate N deposit to top soil
			if (l == 1 && T <= rain_hrs && flood_flag == 0)
			{


				/*
				nh4_w[1] += (rno3 * (rainfall/rain_hrs) * 10 * 0.5); // rainfall-N ppm -> kg N/ha/hr
			   no3_w[1] += (rno3 * (rainfall/rain_hrs) * 10 * 0.5);

			   day_inRainN += (rno3 * (rainfall/rain_hrs) * 10);



			   nh4_w[1] += (rno3 * .025); // rainfall-N ppm -> kg N/ha/hr
			   no3_w[1] += (rno3 * .025);

			   day_inRainN += (rno3*0.05);
			*/
			}






			// Initialize denitrifier and nitrifier biomass each day, kg C/layer/ha
			float wetFactor;
			wetFactor = (day_wfps[1] - 0.6) / 0.4;

			wetFactor = min(1.0, max(0.0, wetFactor));
			
			if (TTT > 0.0 && irri_flag == 0)
			{
				//Fsm = 2.0 * (float)pow((float)TTT, 1.5);
				//Fsm = pow(0.775 * TTT,((1-clay[l])* (1 - clay[l]))) ; //0.075 * rainMulti
				Fsm = (0.775 * TTT) * 9.6825 * exp(-6.596*clay[l]) ; //0.075 * rainMulti
				//Fsm = (0.775 * TTT) * 4.4721 * exp(-7.601 * clay[l]); //0.075 * rainMulti
				Fsm = (0.775 * TTT) * 1.0;
			}
			else
			{
				if (irri_flag == 1)
				{
					Fsm = 2500.0 * day_irri;//2500		
					float irriMulti;
					irriMulti = pow(day_irri * 10.0, 1.4);
					irriMulti = min(24.0, max(irriMulti, 0.0));
					Fsm = 0.775  * irriMulti;//* rainMulti
				}
				else
					Fsm = 1.0;//0.1

				if (fertigate_flag == 1)
					Fsm = 1.0 + 50.0 * day_irri;
			}

			/*	float FFde=1.0;

				if(LandUse==3) Fde=Tttoo[1]*0.035;//*(float)exp(0.2525*temp[l]);
				else if(LandUse==4) Fde= Tttoo[1] * 0.3;//0.01
				else if(LandUse==2) Fde=0.00007*(float)exp(0.2525*temp[l]);
				else
				{
					Fde=Tttoo[1]*0.0035*(float)exp(0.2525*temp[l]);

			#ifdef MANURE
					Fde=Tttoo[GN]*0.0035*(float)exp(0.2525*temp[l]);
			#else
					if(till_flag==1)
						Fde=1.0*Tttoo[1]*0.025*(float)exp(0.2525*temp[l])*till_fact;//1000.0 -> 1.0 modified on July 26, 2012
			#endif
					if(LandUse==6)
					{
						if (l <= T && T <= rain_hrs)// && Leaf_Wt[1]==0.0)
							FFde = 100.0 * T / (99.0 + T);
						else
							FFde = Fde;
					}
					else
					{
						if (l <= T && T <= rain_hrs)// && Leaf_Wt[1]==0.0)
						{
							FFde = 100.0 * T / (99.0 + T);
						}
						else
							FFde = Fde;
					//}
				}
			*/
			/*	if(total_ice>0.0)
				{
					if((ice[l]/10000.0+water[T][l])/sts_h < wiltpt)
						Fde = 0.0;
					else
						Fde = 0.005 * water[T][l]/sts_h;//(float)exp(-5.4039*clay);//0.0752
				}*/

			if (st[l] == 12 || st[l] == 13 || st[l] == 14) Fst = 0.05;//0.1;
			else Fst = 1.0;

			if (sph[l] < 5.0) //calculate the effect of pH on overall denitrifier and nitrifier populations see below
				Fph = -0.1797 * sph[l] * sph[l] + 2.4158 * sph[l] - 7.057;
			else
				Fph = -0.1225 * sph[l] * sph[l] + 1.6165 * sph[l] - 4.3095;
			Fph = min(1.0, max(0.2, Fph));
			

			if (manuFlag == 1 && l < 7)
				Fmn = 250.0 / (float)ManureDays;//250.0
			else Fmn = 5.0;
			Fmn = max(5.0, Fmn);

			//if(SlurryFlag==1&&ManureDays<60) Fmn *= 10.0;


			//temperature flag on microbial growth
			if (temp[l] <= 0.0) Ftm = 0.01;
			else Ftm = 1.0;

			if (l > q) //livestock system
			{
				Fde = 0.5;//1.0;
				Fmn = 0.5;//1.0;
				Fst = 0.5;//1.0;
				Fsm = 0.5;//1.0;
			}

			//denitrifying bacteria temperature rsponse function
			float deMinTemp, deOptTemp, deMaxTemp, deAlpha, deBeta, deFtm;
			deMinTemp = -1.0;//minimum temperature for denitrifier bacteria growth
			deOptTemp = 25.0;//optimum temperature for denitrifier bacteria growth
			deMaxTemp = 40.0;//Max temperature for denitrifier bacteria growth
			deAlpha = 1.5;//how fast this drops off below optimum temperature 1.0 slow, 2 is pretty fast
			deBeta = 1.5;//how fast this drops off above optimum temperature.
			if (temp[l] > deMaxTemp)deFtm = 0.01;
			else
			{
				deFtm = pow((temp[l] - deMinTemp) / (deOptTemp - deMinTemp), deAlpha) * pow((deMaxTemp - temp[l]) / (deMaxTemp - deOptTemp), deBeta);
			}
			if (temp[l] < deMinTemp)deFtm = 0.01;
			deFtm = min(1.0, max(0.000001, deFtm));


			float deMinTempD, deOptTempD, deMaxTempD, deAlphaD, deBetaD, deFtmD;
			deMinTempD = -1.0;//minimum temperature for denitrifier bacteria growth
			deOptTempD = 30.0;//optimum temperature for denitrifier bacteria growth
			deMaxTempD = 40.0;//Max temperature for denitrifier bacteria growth
			deAlphaD = 5.0;//how fast this drops off below optimum temperature 1.0 slow, 2 is pretty fast
			deBetaD = 1.5;//how fast this drops off above optimum temperature.
			if (temp[l] > deMaxTempD)deFtmD = 0.01;
			else
			{
				deFtmD = pow((temp[l] - deMinTempD) / (deOptTempD - deMinTempD), deAlphaD) * pow((deMaxTempD - temp[l]) / (deMaxTempD - deOptTempD), deBetaD);
			}
			if (temp[l] < deMinTempD)deFtmD = 0.01;
			deFtmD = min(1.0, max(0.01, deFtmD));
			
			if (isnan(sph[l]))
			{
				float blah;
				blah=1.0;
			}
			

			//variable reminder from what I can determine
			//Ftm : Soil Temperature Factor (when less than zero = 0. 0)
			//FpH Effect of soil pH on denitrifier and nitrifier populations
			//Fsm = appears to be a soil moisture factor related to hourly precipitation 
			//Fmn = broadcast manure factor
			//soc[l]=Soil Organic Carbon content per layer
			//denitMulti=Denitrifier user control
			//FreezeDOC= wintertime freeze/thaw substrate increase
			//MicrobioIndex= soil polution control
			//mFD = 0.05? - defined in source_main.h constants //was thinking these are somehow related to labile/passive fractioning of C&N pools but not sure the basis.  
			//MRBO = 0.019??? - defined in source_main.h constants
			//ave_anvf[l] = Redox potential of a layer (using Nernst equation)

			//denitifier[l]=dentifier biomass per layer
			//nitrifier[l]=nitrifier biomass per layer
			float no3Factw, no3Factd,nh4Factd;

			float depthF, soilH;//define variables for influencing depth of application
			soilH = (l * h[1] * 100);//calculate soil height in cm
			float k = 0.01f; //Increase k  faster decay(shallower denitrification zone) Decrease k  deeper denitrification possible
			k = 0.09f;
			depthF = exp(-k * soilH); // Decay rate per cm, tune this value
			//depthF = 1.0;
			
			if (soilH <= 10.0) depthF = 1.0;
			//if (surf_water > 0.0)depthF = 1.0;
			if (max_temp > 0.0)
			{
				//depthF = 1.0;
			}
			else
			{
				//depthF = 1.0;
			}
			freezeWaterFactor = 1.0;
			no3Factw = no3_w[l] * 0.1;//testing tying in a better relationship between soil substrate NO3 and denitrifcation.
			if ((no3_w[l]) > 1.0) no3Factw = 2.0;

			no3Factw = no3_w[l] / (1.0 + no3_w[l]);
			no3Factw = pow(min(1.0, max(no3Factw, 0.1))+1.0,1.0);//can change this factor to 2.0 to increase the sensitivity to NO3
			//no3Factw = max(no3Factw, 0.1);

			nh4Factd = nh4_d[l] * 0.1;//testing tying in a better relationship between soil substrate NO3 and denitrifcation.
			if (nh4_d[l] > 10.0) nh4Factd = 2.0;
			nh4Factd = 1.0;
			nh4Factd = nh4_d[l] / (1.0 + nh4_d[l]);
			nh4Factd = min(1.0, max(nh4Factd, 0.1))+1.0;

			
			float  waterFilledP = water[T][l] / (h[l] * sts[l]) + ice[l] / 10000.0 / (h[l] * sts[l]);//water filled pore space plus ice water to give total water in a soil layer
			waterFilledP = min(1.0, max(0.0, waterFilledP));
			float soilWaterFactor;//factor influencing emission rate for denitrification processes
			if (waterFilledP <= wiltpt[1]) { soilWaterFactor = 0.0001; }///day_wfps[l]
			else 
				{
				float B = 20.0;
				float A = 1.0;
				if (total_ice > 0.0) { soilWaterFactor = 1.0 + A * (1.0 / (1.0 + exp(-B * (waterFilledP - 0.75)))); }
				else
				{
					soilWaterFactor = 1.0 / (1.0 + exp(-20.0 * (waterFilledP - 0.75)));
				}//0.60 is the infelction point, 20 controls steepness of curve up from 0.6}
				
				}
		//	if (day_wfps[l] < 0.6)soilWaterFactor = 0.0001;
			//soilWaterFactor = min(1.0, max(0.01, soilWaterFactor));

			soilWaterFactor = max(0.1, soilWaterFactor);
			//soilWaterFactor = 1.0;

			//soilWaterFactor *= Fsm;
		//	soilWaterFactor = 1.0;
			float soilWaterFactorNit = soilWaterFactor * 2.0;
	//	soilWaterFactor = 1.0;

	//no3Fact = min(10.0, max(no3Fact, 0.0));
	//no3Factw = 1.0;
	//no3Factd = 1.0;

			
			float clayFactor;
			clayFactor = 1 + (pow(clay[l], 4)) / (pow(clay[l], 4) + pow(0.3, 4));
			//clayFactor = 1.0;
			//depthF = 1.0;
			//if (jday > 120)primeDenit = 1.0;
			if (FreezeDOC[l] ==0.0 && snow_pack==0.0)primeDenit *= 0.9999;
			if (primeDenit < 1.0)primeDenit = 1.0;
			//primeDenit = 1.0;
			if ( jday == 200)
			{
				float blah;
				blah = 1.0;
			}
			if (soilProfileType == 0)
			{
				denitrifier[l] = 0.0008 * mRBO * mFD * MicrobioIndex * Fph * Fst * Fmn * deFtm * denitMulti   * no3Factw * depthF  * clayFactor * soc[l] * primeDenit * soilWaterFactor*Fsm ;//* soc[l] *no3_w[l];//0.02 max(FreezeDOC[l] * 8, 1.0) ave_anvf[l] 0.0005
			}
			else
			{
				denitrifier[l] = 0.0004 * mRBO * mFD * MicrobioIndex * Fph * Fst * Fmn * deFtm * denitMulti * no3Factw * depthF *  soilWaterFactor * clayFactor * soc[l]*primeDenit ;//* soc[l] *no3_w[l];//0.02 max(FreezeDOC[l] * 8, 1.0) ave_anvf[l] 0.0005
			}
		
	nitrifier[l] = 0.03 * mRBO * mFD * MicrobioIndex * Fph * Fst  * Fmn * deFtmD   * nh4Factd * nitMulti  * soc[l];// 0.1 //0.01 //was 0.02 (0.00002) * FSM  * Fsm  *soilWaterFactor

//	if (T == 24)primeDenit = 1.0;

	// Denitrification =========================================================================================================================================================================================
	if(denitrifier[l]>0.0)
	{
		assim2[l] = 0.0;


		//Further explanation available in Nutr Cycl Agroecosyst (2012) 93:163–200    DOI 10.1007/s10705-012-9507-z  //Manure-DNDC: a biogeochemical process model for quantifying greenhouse gasand ammonia emissions from livestock manure systems
		// Growth of denitrifiers (% per hour)
		cck = doc_w[l] / (KC + doc_w[l]);//
		n3k = no3_w[l] / (KN + no3_w[l]);
		u_no3 = (um_no3 * cck * n3k);//growth rate of NO3 denitrifiers,Kc half saturation value of soluble C in Monod model (kg C/m3 soil water) Kn  half saturation value of N species in the Monod model (kg N/m3 soil water)

		n2k = no2_w[l] / (KN + no2_w[l]);
		u_no2 = (um_no2 * cck * n2k);//growth rate of NO2 denitrifiers , Kc half saturation value of soluble C in Monod model (kg C/m3 soil water) Kn  half saturation value of N species in the Monod model (kg N/m3 soil water)

		nok = no_w[l] / (KN + no_w[l]);
		u_no = (um_no * cck * nok);//growth rate of NO denitrifiers,Kc half saturation value of soluble C in Monod model (kg C/m3 soil water) Kn  half saturation value of N species in the Monod model (kg N/m3 soil water)

		n2o_k = n2o_w[l] / (KN + n2o_w[l]);
		u_n2o = (um_n2o * cck * n2o_k);//growth rate of N2O denitrifiers,Kc half saturation value of soluble C in Monod model (kg C/m3 soil water) Kn  half saturation value of N species in the Monod model (kg N/m3 soil water)

		U = u_no3 + u_no2 + u_no + u_n2o;
		DBG = U * denitrifier[l];//denitirifier biomass growth = total growth rate of N species * denitifier
		DBD = (MC * YMC * denitrifier[l]);//YMC=0.503, MC=0.0076 defined in source_main.h constants. MC=maintenance coefficient (kg C/kg C/hr)? And YMC = Maximum growth yield on soluble carbon (kg C/kg C)? 
		DB = DBG - DBD;//Denitrifier biomass = denitrifier biomass growth minus denitrifier biomass decay. 
		if ( DB < 0.0 ) DB = 0.0;
		Nw = no3_w[l] + no2_w[l] + no_w[l] + n2o_w[l];
		if (Nw <= 0.0) goto RUN_OUT;

		// no3(-) -> no2(-)

		// Amount of no3(-) converted to no2(-) ============================================================================================================================

		if ( fabs(doc_w[l]) < 0.00001 )
		{
			d_no3 = 0.0;
		}
		else
		{
			float FFF;		
			if(flood_flag==0) 
			{
				FFF = 0.01;//2.0
			}
			else FFF = 0.1;//2.0;

			//if(WaterControl==1&&crop[cwc]==20) FFF = 0.005;
			if(WaterControl==1&&flood_flag==1) FFF = 0.005;
			//if(flood_flag==1) 
				

			//if(GN==(q+4)) FFF = 1.0;//compost

			//if(flood_flag==0)
				d_no3 = FFF * (u_no3 / ym_no3 + m_no3 * no3_w[l] / Nw) * phk1[l] * denitrifier[l] * TE[l];
			//else 
			//	d_no3 = 0.5 * no3_w[l];
		}

		if (no3_w[l] < d_no3)
		{
		   d_no3 = no3_w[l];
		   no3_w[l] = 0.0;
		}
		else no3_w[l] -= d_no3;

		day_denitrification[l] += d_no3;

		no2_w[l] += d_no3;

		//*day_soil_denitrification += d_no3;

		// Amount of no3(-) synthesized into no3(-) denitrifier
		if ( fabs(Nw) < 0.00001 )
		{
			da_no3 = 0.0;
		}
		else
		{
			da_no3 = cc * R * DBG * (no3_w[l] / Nw);
		}

		if (no3_w[l] < da_no3)
		{
		   da_no3 = no3_w[l];
		   no3_w[l] = 0.0;
		}
		else no3_w[l] -= da_no3;

		assim2[l] += da_no3;

		// no2(-) -> n2o

		// Amount of no2(-) converted to n2o

		if ( fabs(doc_w[l]) < 0.00001 )
		{
			d_no2 = 0.0;
		}
		else
		{
			float FFF;		
			if(flood_flag==0) FFF = 10.0; //default 10.0
			else FFF = 10.0;

			d_no2 = FFF * (u_no2 / ym_no2 + m_no2 * no2_w[l] / Nw)
				 * phk2[l] * denitrifier[l] * TE[l] * QK;//reminder TE[l] = 0.001 + temp[l] / 30.0;

			
		//	d_no2_kk= d_no2 *.4;//parition to NO
		//	d_no2 *= 0.6;//partition to N2O

		}

		if ((no2_w[l]) < d_no2)
		{
		   d_no2 = no2_w[l];
		   no2_w[l] = 0.0;
		}
		else no2_w[l] -= d_no2;

		n2o_w[l] += d_no2;

		// Amount of no2(-) synthesized into no2(-) denitrifier ======================================================================================================================

		if ( fabs(Nw) < 0.00001 )
		{
			da_no2 = 0.0;
		}
		else
		{
			da_no2 = cc * R * DBG * (no2_w[l] / Nw);//R=constant 0.29 value
		}

		if (no2_w[l] < da_no2)
		{
		   da_no2 = no2_w[l];
		   no2_w[l] = 0.0;
		}
		else no2_w[l] -= da_no2;

		assim2[l] += da_no2;

		// no2(-) -> no

		// Amount of no2(-) converted to no ===========================================================================================================================

		if ( fabs(doc_w[l]) < 0.00001 )
		{
			d_no2_kk = 0.0;
		}
		else
		{
			float FFF;		
			if(flood_flag==0) FFF = 0.5;//default 0.5
			else FFF = 5.0;

			d_no2_kk = FFF * (u_no2 / ym_no2 + m_no2 * no2_w[l] / Nw)  
				  * phk1[l] * denitrifier[l] * TE[l] * QK;// Defined Constants QK = 2.0, ym_no2=0.428 and m_no2=0.0349
		}

		if (no2_w[l] < d_no2_kk)
		{
		   d_no2_kk = no2_w[l];
		   no2_w[l] = 0.0;
		}
		else no2_w[l] -= d_no2_kk;

		no_w[l] += d_no2_kk;

		// Amount of no2(-) synthesized into no2(-) denitrifier===================================================================================================================

		if ( fabs(Nw) < 0.00001 )
		{
			da_no2_kk = 0.0;
		}
		else
		{
			da_no2_kk = cc * R * DBG * (no2_w[l] / Nw) / 100.0;//defined constant R=0.29 , DBG=denitirifier biomass growth
		}

		if (no2_w[l] < da_no2_kk)
		{
		   da_no2_kk = no2_w[l];
		   no2_w[l] = 0.0;
		}
		else no2_w[l] -= da_no2_kk;

		assim2[l] += da_no2_kk;//Might need some code logic to ensure that da_No2_kk is always >0 etc.

		// no -> n2o

		// Amount of NO converted to N2O=============================================================================================================================
		
		if ( fabs(Nw) < 0.00001 )
		{
			d_no = 0.0;
		}
		else
		{
			float FFF;		
			if(flood_flag==0) FFF = 1.0; //default 1.0
			else FFF = 1.0;

			d_no = FFF * (u_no / ym_no + m_no * no_w[l] / Nw)
				   * phk2[l] * denitrifier[l] * TE[l]  * QK;//brian constants defined as ym_no=0.151, m_no=0.0792
		}

		if (no_w[l] < d_no)
		{
		   d_no = no_w[l];
		   no_w[l] = 0.0;
		}
		else no_w[l] -= d_no;

		n2o_w[l] += d_no;
		
		// Amount of NO synthesized by NO denitrifier===============================================================================================================

		if ( fabs(Nw) < 0.00001 )
		{
			da_no = 0.0;
		}
		else
		{
			da_no = cc * 2.0 * R * DBG * (no_w[l] / Nw);//brian reminder DBG=denitrifier Biomass Growth 
		}

		if (no_w[l] < da_no)
		{
		   da_no = no_w[l];
		   no_w[l] = 0.0;
		}
		else no_w[l] -= da_no;

		assim2[l] += da_no;

		// n2o -> n2

		// Amount of n2o coverted to n2 =================================================================================================================================

		if ( fabs(doc_w[l]) < 0.00001 )
		{
			d_n2o = 0.0;
		}
		else
		{
			float FFF;
			if (st[l]==12) FFF = 0.2;
			else FFF =	1.2 * clay[l];	//12.5; 1.2 //clay[l]=soil clay fraction
						
			if(TTT>5.0) FFF *= 0.01 / TTT;//0.025
			
			if(l==q+1) FFF = 1.0;//feedlot

			if(LateralInflux>1.0&&precipitation>0.0) FFF *= 0.5;

			if(irri_flag==1) FFF = 0.0;

			if(flood_flag==1)
				FFF = 1.0;
			
			if(l==q+5) //lagoons =====================================================================================================================
			{
				d_n2o = n2o_w[l] + no3_w[l] + no3_d[l];
				no3_w[l] = 0.0;
				no3_d[l] = 0.0;
			}
			else//calculates the amount of N2O produced in a layer???
				d_n2o = FFF * (u_n2o / ym_n2o + m_n2o * n2o_w[l] / Nw) * phk3[l] * denitrifier[l] * TE[l]*N2N2OFactor;//N2:N2O Factor control for user to adjust N2 : N2O partitioning if it seems incorrect.
			
		}

		if (n2o_w[l]<d_n2o)// || Fsm >10.0)
		{
		   d_n2o = n2o_w[l];
		   n2o_w[l] = 0.0;
		}
		else n2o_w[l] -= d_n2o;
		
		n2_w[l] += d_n2o;

		// Amount on n2o synthesized by n2o denitrifier

		if ( fabs(Nw) < 0.00001 )
		{
			da_n2o = 0.0;
		}
		else
		{
			da_n2o = cc * R * DBG * (n2o_w[l] / Nw);
		}

		if (n2o_w[l] < da_n2o)
		{
		   da_n2o = n2o_w[l];
		   n2o_w[l] = 0.0;
		}
		else n2o_w[l] -= da_n2o;

		assim2[l] += da_n2o;

		// Assimilated N in microorganisms during denitrification ========================================================================================================
		//assim2[l] = (da_no3+da_no2+da_no2_kk+da_no+da_n2o);
		da_no3 = 0.0; da_no2 = 0.0; da_no2_kk = 0.0;
		da_no = 0.0; da_n2o = 0.0;
		assim_N += assim2[l];//where to go?

		//n2_w[l] += assim2[l];
		nh4[l] += assim2[l];
		if (nh4[l] < 0.0)nh4[l] = 0.0;
		assim2[l] = 0.0;

		// DOC consumption

		// Amount of doc consumed  ==============================================================================================================

		if ( fabs(doc_w[l]) < 0.00001 )	DC = 0.0;
		else DC = (U / YMC + MC) * denitrifier[l];

		// Amount of doc converted to CO2 ============================================================================================================================
		if(doc_w[l] >= DC)
			doc_w[l] -= DC;
		else
		{
			DC = doc_w[l];
			doc_w[l] = 0.0;
		}

		dn_co2 += DC;// - DBG;

		// New denitrifiers ========================================================================================================================

		denitrifier[l] += DB;
	
#ifdef MANURE // FOR MANURE-DNDC compile only
#else
		day_DOC_cons += DC;
#endif
		if ( denitrifier[l] < 0.0 ) denitrifier[l] = 0.0;
		if ( doc_w[l] < 0.0 ) doc_w[l] = 0.0;
		//if ( d_co2 < 0.0 ) d_co2 = 0.0;
		if ( no3_w[l] < 0.0 ) no3_w[l] = 0.0;
		if ( no2_w[l] < 0.0 ) no2_w[l] = 0.0;

		//dn_co2 += d_co2;
		//d_co2 = 0.0;

		RUN_OUT:;
	}

	//Nitrification =========================================================================================================================================================
	if(nitrifier[l]>0.0)
	{
		fact_t = (float)pow(3.503,(60.0-temp[l])/(60.0-34.22))  //soil temperature factor
		   * (float)exp(3.503*(temp[l]-34.22)/(60.0-34.22)); //O'neill

		if ( fact_t > 1.0 ) fact_t = 1.0;
		if ( fact_t < 0.0 ) fact_t = 0.0;

		if (day_wfps[l] > 0.05)
		   fact_m = 0.8 + 0.21 * (1.0 - day_wfps[l]);
		else
		   fact_m = 0.0;

		if ( fact_m > 1.0 ) fact_m = 1.0;
		if ( fact_m < 0.0 ) fact_m = 0.0;

		// developed by Florian based on Blagodatsky and Richter 1998
		/*
		micro_growth = 0.0166 * (doc_d[l] / (1.0 + doc_d[l]) + fact_m / (1.0 + fact_m)) / 24.0 * MicrobioIndex;
		if (micro_growth < 0.0) micro_growth = 0.0;

		micro_death = 0.008 * nitrifier[l] * 1.0 / (1.0 + doc_d[l]) / (1.0 + fact_m) / 24.0;

		micro_delta = (micro_growth - micro_death) * nitrifier[l] * fact_t * fact_m;

		nitrifier[l] += micro_delta;
		*/
		if (year == 1 && jday == 208)
		{
			float blah;
			blah = 1.0;

		}
		if (nitrifier[l] < 0.0) nitrifier[l] = 0.0;
		//clay[1]
		//float Fclay = -46.603 * (float)log(0.25) - 7.2499;//was log(clay[1])-7.2499
		//float Fclay = (-46.603 * (float)log(clay[l]) - 7.2499) *1.616;
		float Fclay = 1 * exp(-(pow((clay[l] - 0.6), 2)) / (2 * pow(0.2, 2)))*100.0;
		float k1;

		if(Fclay<1.0) Fclay = 1.0;
		if(Fclay>100.0) Fclay = 100.0;

		if (day_wfps[l] > fldcap[l] || by_passf > 0.0) {
			k1 = 0.1; }//0.001 //moisture adjusted k factor
		else { 
			k1 = 0.005 * Fclay; }//0.005 ///otherwise k factor is adjusted by Clay content
		
		if(l==q+1) //barn
		{
			k1 = 0.0001;//0.00001;
			day_wfps[1] = day_wfps[l];
		}
		else if(l==q+2||l==q+3) //grazing field
			k1 = 0.001;//0.00001;
		else if(l==q+4)
		{
			k1 = 0.0000001;//compost
			day_wfps[1] = day_wfps[l];
		}
		else if(l==q+5||l==q+6||l==q+8) //lagoon, digester, gutter
		{
			k1 = 0.0001;
			day_wfps[1] = 1.0;
		}

		float LFactor = 1.0*pow(0.97,h[1]*100*l);//1.0 * (float)pow(0.9, (float)l);//depth influence on nitrification.
		LFactor = 1.0;
		//float TFactor = (temp[l]-9.0) / 20.0;//soil temperature factor
		//TFactor = max(0.0, TFactor);

		float TFactor, TNitMin, TNitMax, TNitOpt,thetaNit,kNit;
		TFactor = 1.0;
		TNitMin = -5.0; TNitMax = 45.0; TNitOpt = 30.0; thetaNit = 10.0; kNit = 5;

			if(temp[l]>=TNitMin && temp[l] <= TNitMax)
			{
				
				TFactor = exp(-((temp[l] - TNitOpt)*(temp[l] - TNitOpt)) / (2 * thetaNit*thetaNit));

			}
			if (temp[l] < TNitMin)
			{
				TFactor = 0.0;
			}
			if (temp[l] > TNitMax)
			{
				TFactor = exp(-((temp[l] - TNitOpt) * (temp[l] - TNitOpt)) / (2 * thetaNit * thetaNit)) * exp(-((temp[l] - TNitMax) / (kNit)));

			}
			if (temp[l] >= 0)
			{
				//TFactor *= 100.0;

			}
			TFactor = min(1.0, max(TFactor, 0.00));
			
			//TFactor = 1.0;
			//TFactor = 1.0;
		//if(l>q) LFactor = 0.001;
		if(l<=q) 
		{		
			float pHNitFact;
			float pHOpt = 7.5;
			float pHTheta = 0.8;
			pHNitFact = exp(-((sph[l] - pHOpt) * (sph[l] - pHOpt)) / 2 * pHTheta * pHTheta)/0.92;//soil pH factor on nitrification, optimium at pH 6.5, min at pH 4 and 9
			pHNitFact = min(1.0, max(pHNitFact, 0.001));
			//pHNitFact = -1.0864 * sph[l] * sph[l] + 16.584 * sph[l] - 55.14;//relationship of pH on nitrification adapated from Sahrawat 1982 and Sahrawat 2008 Soil Science and Plant Analysis 39:1436-1446  
			//pHNitFact = min(8.0, max(pHNitFact, 0.0));
			//pHNitFact = sph[l];//turn it back to original.
			
			/*
			float soilWaterFactor=1.0;
			if (day_wfps[l] <= wiltpt[l]) { soilWaterFactor = 1.0; }
			else if(day_wfps[l]< 0.6)
			{
				soilWaterFactor = day_wfps[l] / wiltpt[l]*100.0;
			}
			else
			{
				soilWaterFactor = 1.0;
			}

			soilWaterFactor = min(20.0, max(0.5, soilWaterFactor));
			*/
			if(flood_flag==0)
			{//was pow(clay[1],0.5)
				//wwzz = 0.010 * k1 * nitrifier[l] * (1.0 - pow(0.25, 0.5)) * pHNitFact * till_fact * LFactor * TFactor * nit2Multi;//* day_wfps[1]//sph[l] // 0.001, HanZhen//0.00005 ///calculates the nitrification rate //def 0.005 //not temperature sensitive atm? day_wfps set to layer 1. Water regulates nitrifier biomass already
				wwzz =  8.00 * k1 * nitrifier[l] * (1.0 - pow(0.25, 0.5))  * pHNitFact  * till_fact * LFactor * TFactor * nit2Multi*Fsm;//* day_wfps[1]//sph[l] // 0.001, HanZhen//0.00005 ///calculates the nitrification rate //def 0.005 //not temperature sensitive atm? day_wfps set to layer 1. Water regulates nitrifier biomass already
				if(IrriRice_flag==1) wwzz *= 0.0002;
				
			}
			else
				wwzz = 0.0;//0.002;
		}
		else 
		{
			if(l==q+1) wwzz = 0.3;
			else if(l==q+4) wwzz = 0.005;//compost
			else if(l==q+6) wwzz = 0.0002;
			else wwzz = 0.0002;

		}
		
		if(jday>=NIDay1&&jday<=NIDay2)//effective duration of nitrification inhibitor  -==========================================================
		{
			if ((jday - NIDay1) > 45)
			{
				float dayGUI, redEffNI;
				
			}
			

			float NIEF = 1.04 - 1.2 * pow(clay[1],2);//effectiveness of nitrification inhibitor ...should this be silt content based instead..would need to be estimated base on input soil texture as only clay fraction is explicitedly tracked
			NIEF = min(1.0, max(0.0, NIEF));
			wwzz *= (1.0 - NIEfficiency) * NIEF;//controls the nitrification rate. 
		}
		else if(jday>NIDay2)
		{
			NIEfficiency = 0.0;//might need to test if this is messing it  up
		}

		if(drain_flag>0) 
		{
			wwzz *= 1.0;
			EEE = 0.1;
		}
		else
		{
			EEE = 0.003;

		}
		//if(irri_flag==1) wwzz *= 500.0;
	

		//nitrification max
		float massSoil = 10000.0 * h[1] * sd[l] * 1000.0;//10,000 * h in metre * bulk density

		float nh4Conc = (nh4_d[l] * pow(10, 6)) / massSoil;
		if (jday==204)
		{
			float blah;
			blah = 1.0;
		}
		float Km = 20.0; //half saturation rate mg/L
		float Vmax = 1.0; //max concentration mg/L
		float NitRateMax = (Vmax * nh4Conc) / (Km + nh4Conc); // mg / L per hour
		if (NitRateMax < 0.0)NitRateMax = 0.01;
		//Max Nit rate about 2-3 mg NH4-N/kgsoil/hr



		if (wwzz > 1.0) wwzz = 1.0;
		if (wwzz < 0.0) wwzz = 0.0;

		//if (SnowMelt>0.0&&temp[1]<1.0)
		if (temp[1] <= 0.0)//temp[1] <= 0.0
		{	
			float snowMeltFactor = 1.0;
			if (SnowMelt > 0.0)snowMeltFactor = 2.0;

			if (LandUse == 3 || LandUse == 4)
				nno = 0.01 * fact_m * nh4_d[l];
			else
				nno = NitRateMax * wwzz * (nh4_d[l])*snowMeltFactor;///+nh4_w[l]); //for temperature surface below zero situations freezing N2O 
		}
		else
			nno = NitRateMax * wwzz * nh4_d[l];//+nh4_w[l]);//0.0;nh4Factd 0.4
				//nno = 0.001 * wwzz * (nh4_d[l]);//+nh4_w[l]);//0.0;
		if (nh4_d[l] > 10.0 && l<10)
		{
			float blah;
			blah = 1.0;
		}
		if (year==12 && l < 10 && T==1 && jday>222)
		{
			float blah;
			blah = 1.0;
		}
		//float soilWaterFactor;
		
		if (day_wfps[l] <= wiltpt[l])
		{
			soilWaterFactor = 1.0; 
		}
		else
		{
			soilWaterFactor = pow((day_wfps[1] - wiltpt[1]) + 1.0, 7.0);//sept 17 was 18
		}

		//soilWaterFactor = min(3.0, max(1.0, soilWaterFactor));
		//soilWaterFactor = 0.775 * TTT;
		//soilWaterFactor = min(10.0, max(1.0, soilWaterFactor));
		//soilWaterFactor = 1.0;

		

		nno = nno * soilWaterFactor;

		
		

		if (nh4_d[l] > 5.0)
		{
			float blah;
			blah = 1.0;
			

		}
		if(nno > 0.36)
		{
			nno = pow(nno+1, 0.001)-1.0+0.36;
			//primeDenit = 2.0;
			//blah = 1.0;

		}
		//if(isnan(nno))nno = 0.0;
			//nno=max(0.0, min(0.06, nno));//capping maximum nitrification rate per day. 5kgN hr/day. /def 1.5  --nitrifiation max   //8.0
			//if(nno>(nh4_d[l]-5.0))nno*=0.01;//put in a cap for nitrification when soil is low NH4
			//if (nh4_d[l]<=2.0)nno *= 0.01;//put in a cap for nitrification when soil is low NH4
			
			
			
			//pH shift from nitrification --disabled at the moment
			


			double Kw, V_water, produce_H, hydrogen, mol_nitrification, hydroxide;//define variables
			float tempKelvin;
			tempKelvin = 273.15 + temp[l];
			Kw = exp(14.01708 - 10294.83 / (tempKelvin)-0.039282 * (tempKelvin));

			//lastKw[l] = Kw;

			float convertNit;

			convertNit = nno * 1000000.0 / (mmm[1] / h[1]);//convert nitrification NH4-N to unit kg/m3

			//V_water = day_wfps[l] * h[l] * 10000.0 * 1000.0;//liter water/ha in layer l
			mol_nitrification = convertNit * 1000.0 / 1000.0 / 14.0; //kg N/layer -> mol N/L  correct units? kg/m3
			produce_H = mol_nitrification*2;//BandedAppMulti[l]
			//BandedAppMulti[l] *= 0.99;
			//BandedAppMulti[l] = min(100.0, max(1.0, BandedAppMulti[l]));
			//if (BandedAppMulti[l]>1.0)
			//{
			//	float blah;
			//	blah = 1.0;
			//}
			
			// soil pH 
			// buffer effect 


			//double produce_pH= max(0.0,(double)log(Kw/produce_OH)/-2.3026);//calculates the produced H from hydro-urea

			double produce_pH = (double)log10(produce_H) * -1.0;

			//if (soilcec<1)//user input soilcec=0 or NA then do this 
			//{
			float xx = (clay[l]) * 100.0 + 0.01 * (soc[l] / mmm[l] * 100.0);
			//float xx = (clay[l]) * 100.0;// + (float)exp(soc[i]/m*1000.0-20.0);
			if (xx > 100.0) xx = 100.0;
			float CEC;
			CEC = min(100, (1.0802 * xx));//meq/100 g soil			+ 14.442
			//CEC = 1.0;


			//CEC[1] = CEC[1] * 14.0 / 100000.0 * mmm[1];//meq/100 g soil -> kg N/ha/layer
			double Fcec = (0.004 * (100 - double(CEC)));// //pH Buffer currently broken!!! Turned it off. Nitrification rate faster for sands which results in less NH3 losses
			Fcec = pow(Fcec, 0.6);  //pH Buffer currently broken!!! Turned it off. Nitrification rate faster for sands which results in less NH3 losses
			//Fcec = 1.0;

			//if this PH buffer has a higher capacity to absorb H ions the real shift in soil pH from nitrification will be reduced. Thus that higher Fcec the value is the larger the soil buffer and smaller the soil pH shift.


			produce_H = pow(10.0, -(produce_pH / Fcec));//recalculates the produced OH including the CEC buffering effect.
			if (isnan(produce_H))
			{
				float blah;
				blah = 1.0;
			}
			if (isnan(sph[l]))
			{
				float blah;
				blah = 1.0;
			}

			hydrogen = (double)powf(10.0, -sph[l]);//mol H/L  //calculates mols of H based on current pH
			hydroxide = Kw / hydrogen;//mol OH/L // calculates mols of OH based on H #brian test lastKw[l]

											//hydroxide +=oHBufferPool[l];//add what is incoming with pHBuffer
			double oldKw = Kw;//just used for output testing to see if Kw is transfered from one day to next.

			float oldhydrogen = hydrogen;//calculate oldhydrogen used for outputTesting only
			float oldhydroxide = hydroxide; //calculate oldhydroxide used for outputTesting only



			//hydroxide += produce_OH;//calculate new hydroxide and hydrogen ratios



			hydrogen = hydrogen+produce_H;

			sph[l] = log10(hydrogen) * -1.0;//default -2.3026 determine new soil pH based on logarithmic hydrogen function.

			
			
			sph[l] = max(5, min(9, sph[l]));//sets the max and minumum soil pH boundaries to be 3 and 11

			
			

			// end addition
			


		if(flood_flag==1&&l<=q) 
		{
			if(Eh[l]>=-200.0) nno *= 0.1;
			else nno = 0.0;

			//nno = 0.0;
		}
	
		//nno = 0.05 *fact_t*fact_m *(nh4_d[l]);

		if ( nno < 0.0 ) nno = 0.0;

		day_nitrification[l] += nno;
		
	
		float vNH4 = nh4_d[l];//+nh4_w[l];

		if(vNH4<=0.0)
		{
			nh4_d[l] = 0.0;
			//nh4_w[l] = 0.0;
		}
		else
		{
			if (nno > 1.0)
			{
				nno = 1.0;

			}
			float maxNit = 0.0;
			float potNitAmount = 0.0;
			maxNit = 0.2 * massSoil / 1000000.0;//3.0 mg NH4-N/kg soil/hr * 24 hr/day -> kg NH4-N/ha/day
			potNitAmount = nno * nh4_d[l];
			if ( potNitAmount > maxNit)
			{
				potNitAmount = maxNit;

			}
			
		  // nh4_d[l] -= potNitAmount;
		   
			nh4_d[l] -= nno * nh4_d[l] / vNH4;
			//nh4_w[l] -= nno * nh4_w[l] / vNH4;
			if (nh4_d[l] < 0.0) nh4_d[l] = 0.0;
		}

		*day_soil_nitrify += nno;

		//EEE = 0.003;

		ae_no = EEE * nno * fact_t;
		ae_no = max(0.0, min(1.0, ae_no));
    
		*day_nitrify_NO += ae_no;
    
		nno -= ae_no;  
		no_d[l] += ae_no;
		ae_no = 0.0;

		if(l<=q)
		{
			if(drain_flag==0)
			{
				if(LandUse==1||LandUse==2)
				{
					if(flood_flag==1&&l==1)
					{
						EEE = 10.0 * (float)pow(water[T][l]/(h[l]*sts[l]), 5.0);//0.01
					}
					else
						EEE = 0.1 * (float)pow(water[T][l]/(h[l]*sts[l]), 5.0);//0.75
				}
				else 
				{
					EEE = 0.2 * (float)pow(water[T][l]/(h[l]*sts[l]), 5.0);//0.2
				}
			}
			else 
				EEE = 0.1;
		}
		else
		{
			if(l==q+2||l==q+3) //pen, grazing field
				EEE = 0.0;
			else if(l==q+4) //compost
				EEE = 0.1;
			else
				EEE = 1.0;
		}

#ifdef MANURE
#else
		if(till_flag==1) EEE *= 1.0;//30.0; HanZhen //brian tillage factor for N2O emissions was 60.0 interacting with manure and tillage emissions

		//if(irri_flag==1) EEE *= 150.0;//30.0; 
#endif

		//if(till_fact>1.0) EEE *= (till_fact*till_fact);
		EEE = min(1.0, max(0.0, EEE));

		float FclayN2O = 1 * exp(-(pow((clay[l] - 0.4), 2)) / (2 * pow(0.2, 2)));
		FclayN2O = min(100.0, max(0.0, FclayN2O));

		//textural N2O
		float sandContent,clayContent;
		if (st[l] == 1)//sand
		{
			sandContent = 0.9;
			clayContent = 0.05;
		}
		else if (st[l] == 2)//loamy sand
		{
			sandContent = 0.82;
			clayContent = 0.07;
		}
		else if (st[l] == 3)//sandy loam
		{
			sandContent = 0.65;
			clayContent = 0.1;
		}
		else if (st[l] == 4)//silt loam
		{
			sandContent = 0.20;
			clayContent = 0.15;
		}
		else if (st[l] == 5)//loam
		{
			sandContent = 0.43;
			clayContent = 0.18;
		}
		else if (st[l] == 6)//sand clay loam
		{
			sandContent = 0.55;
			clayContent = 0.25;
		}
		else if (st[l] == 7)//silty clay loam
		{
			sandContent = 0.20;
			clayContent = 0.35;
		}
		else if (st[l] == 8)//clay loam
		{
			sandContent = 0.35;
			clayContent = 0.30;
		}
		else if (st[l] == 9)//sandy clay
		{
			sandContent = 0.45;
			clayContent = 0.40;
		}
		else if (st[l] == 10)//silty clay
		{
			sandContent = 0.05;
			clayContent = 0.45;
		}
		else if (st[l] == 11)//clay
		{
			sandContent = 0.20;
			clayContent = 0.50;
		}
		else
		{
			sandContent = 0.2;
		}
		float nitNFraction;

		nitNFraction = (exp(-((sandContent - 0.4) * (sandContent - 0.4)) / (2 * 0.2 * 0.2)) * exp(-((clayContent - 0.25) * (clayContent - 0.25)) / (2 * 0.1 * 0.1)))*0.8;//based on relationship for nitrificaiton. Seems odd for clay soils
		nitNFraction = 1 * exp(-(pow((clay[l] - 0.5), 2)) / (2 * pow(0.18, 2)));//better relationship
		//nitNfraction was set to a constant 0.2;
		
		float clayFactor2;
		clayFactor2 = clay[l];
		clayFactor2 = min(0.46, clay[l]);
		//nitNFraction = clayFactor2*1.2;

		if (soilProfileType == 0) nitNFraction *= 1.2;
		nitNFraction = min(.8, max(nitNFraction, 0.45));
		//nitNFraction = min(0.8, max(nitNFraction, 0.30));
		if (DrainEfficiency == 0)
		{
			//nitNFraction *= 1.5;
		}
		
		//test all 3 factors
		const double A =0.35;       // Scaling factor
		const double Q10 = 3.1;     // Temperature sensitivity higher value means more emissions at higher temp
		const double T_ref = 20.0;  // Reference temperature (°C)
		const double a = 50.0;      // Coefficient for W_opt = a * clay + b
		const double b = 40.0;
		const double c = 10.0;      // Coefficient for sigma = c * clay + d
		const double d = 5.0;
		const double k = 5.0;       // Controls clay effect
		const double lambda = 3.0;  // Depth decay constant (m^-1)



		double Ta = temp[l];
		double W = day_wfps[l] * 100.0;
		double C = clay[l] * 100.0;
		double D = h[l] * l;  // Soil depth in meters

		double f_T = pow(Q10, (Ta - T_ref) / 10.0);
		double W_opt = a * (C / 100.0) + b;
		double sigma = c * (C / 100.0) + d;
		double f_W = exp(-pow(W - W_opt, 2) / (2.0 * pow(sigma, 2)));
		double f_C = 1.0 - exp(-k * (C / 100.0));
		double f_D = exp(-lambda * D);
		//f_T = 1.0;
		// Combined nitrification rate
		//double Na = A * f_T * f_W * f_C * f_D;
		//if (f_T > 1.0)f_T = 1.0;
		double Na = A * f_C * f_T ;
		nitNFraction = Na;
		//nitNFraction = 1.0;


		//TFactor=soil Temperature factor 
		//nitNFraction = 0.0001;
		ae_n2o =  rainMulti* nitNFraction* EEE * nno * powf(bypass_f, 2.0);// Ingwersen, 1998 was 1.2 -- controls the amount of N2O produced from nitrification. //was 1.8 vs 0.8 v2
		
		*day_nitrify_N2O += ae_n2o;
		day_nitrify_n2ol[l] += ae_n2o;//tracking n2O produced by nitrification.
		 
		//would need to track here the aerobic N2O produced in a layer by referencing aerobic_N2O[l]


		nno -= ae_n2o;
		n2o_d[l] += ae_n2o;
		ae_n2o = 0.0;

		if (nno<0.0) nno=0.0;
		no3_d[l] += nno;
		nno = 0.0;
	}

  // Recover substrates ===============================================
  doc[l] += (doc_w[l] + doc_d[l]);
  nh4[l] += (nh4_w[l] + nh4_d[l]);
  if (nh4[l] < 0.0) {
	  nh4[l] = 0.0;
  }
  no3[l] += (no3_w[l] + no3_d[l]);
  no2[l] += (no2_w[l] + no2_d[l]);
  no[l] += (no_w[l] + no_d[l]);
  n2o[l] += (n2o_w[l] + n2o_d[l]);
  n2[l] += n2_w[l];

  doc_w[l] = 0.0;
  nh4_w[l] = 0.0;
  no3_w[l] = 0.0;
  no2_w[l] = 0.0;
  no_w[l] = 0.0;
  n2o_w[l] = 0.0;
  n2_w[l] = 0.0;

  doc_d[l] = 0.0;
  nh4_d[l] = 0.0;
  no3_d[l] = 0.0;
  no2_d[l] = 0.0;
  no_d[l] = 0.0;
  n2o_d[l] = 0.0;

  //if(sph[l]<4.5) Chemodenitrification(l, temp);
  // Gas emission ===================================================
  if (flood_flag==0)
  {
     float PA, AD, emsno, emsn2o, emsn2, pno, pn2o, pn2, tt, peat;

     if(temp[l] > 0.0) tt = temp[l];
     else 
		 tt = 0.0;

	// tt = -0.0001 * pow(temp[l], 3) + 0.0037 * pow(temp[l], 2) + 0.0635 * temp[l] + 0.0265;
	// tt = 0.0009 * pow(temp[l], 2.2559);
	// if (temp[l] <= 0.0)tt = 0.0;

	

#ifdef MANURE
     PA = 1.0 - (((water[T][l] /1000.0) / 10000.0) / (h[l] * sts[l]));//Modified on 6/13/2013
	 PA = 1.0 * (1.0 - (water[T][l] / sts_h));//potential floating point nan(inf) error because sts[l]=0.0 for lagoon. 
#else
	 PA = 1.0 * (1.0 - (water[T][l] / sts_h));
#endif

	 //if(seed[cwc]>0&&crop[cwc]==20) PA *= 1.0;//0.25;

     AD = 2.0 * clay[l] / 0.63;//soil texture factor

	 if(st[l]==12) peat=10.0;//if soil texture is heavy clay else peat = 1.0
	 else peat=1.0;

	float f_litter = (rcvl[l]+rcl[l]+rcr[l])/600.0;

	if(f_litter < 1.0) f_litter = 1.0;

	if(drain_flag>0)
	{
		pno = 0.05;
		pn2o = 0.05;
		pn2 = 0.05;

	}
	else
	{

		//float tempEffect;
		//tempEffect=  0.2054 * temp[z] * temp[z] - 0.0525 * temp[z] + 0.0321;
		// pno = peat*0.5*(f_litter * ((.0006 + .0013 * AD) + (.013 - .005 * AD) * PA * tt) * PORO);//Lena //default 0.5 instead of PA
		// pn2o = peat*PA * (f_litter * (30.0 * (.0006 + .0013 * AD) + (.013 - .005 * AD) * tt * PORO)); //*****
		// pn2 = peat*f_litter * (0.017 + (.025 - .0013 * AD) * PA * tt * PORO);
		PORO = sts[l];//brian new addition to porosity
		 pno = peat * 0.5 * (f_litter * ((.0006 + .0013 * AD) + (.013 - .005 * AD) * PA * (float)pow(2.0, tt / 20.0)) * PORO);//Lena //default 0.5 instead of PA
		 pn2o = peat * 0.5 * (f_litter * (30.0 * (.0006 + .0013 * AD) + (.013 - .005 * AD) * (float)pow(2.0, tt / 20.0) * PORO)); //*****
		 
		 pn2 = peat * f_litter * (0.017 + (.025 - .0013 * AD) * PA * (float)pow(2.0, tt / 20.0) * PORO);
		 if (temp[l] > 0.0) pn2o = 0.0343*temp[l];// *temp[l];
		 else pn2o = 0.0003;
		 if (temp[l] > 0.0) pno = 0.0004*temp[l];
		 else pno = 0.0003;
		 if (temp[l] > 0.0) pn2 = 0.0013*temp[l];
		 else pn2 = 0.0003;

		 


	}

	

     if ( pno > 1.0 ) pno = 1.0;
     if ( pn2o > 1.0 ) pn2o = 1.0;
     if ( pn2 > 1.0 ) pn2 = 1.0;
     if ( pno < 0.01 ) pno = 0.01;
     if ( pn2o < 0.01 ) pn2o = 0.01;
     if ( pn2 < 0.01 ) pn2 = 0.01;

	 /*
	 if (snow_pack > 0.0 || ice[1] > 0.0)//reduce the emission rate when there is snowpack or surface ice present.//was 0.005
	 {
		 float precipFactor;
		 
			 precipFactor = temp[1];
			 if (temp[1] < 1.0)precipFactor = 1.0;
		 //precipFactor = 1.0;
		 //precipFactor = min(10.0, max(1.0, precipFactor));
		 //adjusts the amount of N2O releasing as atmospheric flux. Larger = less remains in soil and more going directly to atmosphere.
		 
		 //test samantha
		 pno = 0.0204 *precipFactor;
		 pn2o = 0.0113 * precipFactor;
		 pn2 = 0.0213 * precipFactor;
		 pno = 0.0204 * precipFactor;

		 //pno = 0.003;
		 //pn2o = 0.003;
		 //pn2 = 0.003;
		 //pno = 0.003;

	 }
	 */

	 if (temp[1]>0.0 && temp[1] < 10.0 && snow_pack==0.0&&ice[1]==0.0)//new eq to reduce emissions below 10 C soil temperature. Adapted from Li .
	 {
		 //pn2o *= abs(temp[1] / 10.0);
	 }


	 // actual N emissions of NO, N2O and N2 as affected by diffusivity of soil pno, pn2O, pn2
	//emsno = no[l] * pno;
	//emsn2o = n2o[l] * pn2o;
	//emsn2 = n2[l] * pn2;


	//turn on for mechanistic diffusion
	emsno = 0;
	emsn2o = 0;
	emsn2 = 0;

	
	
	 

	 
	 
	 if (emsn2o < 0)
	 {
		 float blah;
		 blah = 1.0;

	 }

#ifdef MANURE
	 if(l==q+1)//housing
	 {
		MData.day_house_no += emsno;
		MData.day_house_n2o += emsn2o;
		MData.day_house_n2 += emsn2;
		MData.day_house_co2 += dn_co2;
		dn_co2 = 0.0;
	 }
	 else if(l==q+4)//composting
	 {
		MData.day_compost_no += emsno;
		MData.day_compost_n2o += emsn2o;
		MData.day_compost_n2 += emsn2;
	 }
	 else if(l==q+5)//lagoon
	 {
		MData.day_lagoon_no += emsno;
		MData.day_lagoon_n2o += emsn2o;
		MData.day_lagoon_n2 += emsn2;
	 }
	 else if(l==q+6)//digester
	 {
		MData.day_digester_no += emsno;
		MData.day_digester_n2o += emsn2o;
		MData.day_digester_n2 += emsn2;
	 }	
	 else if(l==q+8)//gutter
	 {
		MData.day_gutter_no += emsno;
		MData.day_gutter_n2o += emsn2o;
		MData.day_gutter_n2 += emsn2;
	 }	
#endif

	 if(l<=q)// q = bottom layer of the soil profile
	 {
		 

		 *day_soil_an_no += emsno;
		 *day_soil_an_n2o += emsn2o;
		*day_soil_n2 += emsn2;
		 day_denitrify_n2ol[l] += emsn2o;

	
	 }
	 
     no[l] -= emsno;
     n2o[l] -= emsn2o;
     n2[l] -= emsn2;

     if (no[l] < 0.0) no[l] = 0.0;
     if (n2o[l] < 0.0) n2o[l] = 0.0;
     if (n2[l] < 0.0) n2[l] = 0.0;


	 //tried recovering N2O in a layer
	 //no3[l] += n2o[l] * 0.05;
	// n2o[l] = n2o[l] * 0.95;

	 //hr_no += emsno;
	 //hr_n2o += emsn2o;
	 //hr_n2 += emsn2;

     	 
	 //ideas for improvement ---------------------------------
	 
	 


	// Optional: Snowpack layer handling
// If snowpack is present, define a snow layer with:
// - Low air-filled porosity (e.g., air_filled_snow = 0.05)
// - Reduced diffusion coefficient (e.g., D_snow = D0 * temp_factor * air_filled_snow^n * snow_reduction_factor)
// - snow_reduction_factor could be 0.1 or lower depending on snow density


	 
		// Constants -- these constants are applied to a single hour at the end of the day....should they be converted from cm2/s to cm2/day
	 float snowEffect;
	 snowEffect = 1.0;
	 if (snow_pack * 1000.0 == 0.0) snowEffect = 1.0;
	 if (SnowMelt > 0.0) snowEffect = 1.0;
	 float D0_NO = 0.139 * 3600.0*snowEffect;   // 0.139 cm2/s in air at 25°C converted to cm2/hr ...multiplying by 3600 to go to hourly
	 float D0_N2O = 0.126 * 3600.0 * snowEffect;
	 float D0_N2 = 0.176 * 3600.0 * snowEffect;
	 float tau = 0.66;       // Tortuosity factor (Millington-Quirk)
	 
	 // Loop through soil layers
	 if (l == 1)//layer == 1 and T is equal to hour of the day//only do this calculation for the outter loop at one layer...not all layers. 
	 {
		 for (int l1 = q - 1; l1 >= 1; l1--) //loop from bottom + 1 layer to surface layer 
		 {
			 float theta = water[T][l1] / h[l1]; // volumetric water content (m3/m3)
			 float air_filled = sts[l1] - theta;
			 if (air_filled < 1e-6) air_filled = 1e-6; // avoid division by zero

			 // Temperature-adjusted diffusion coefficient
			// float temp_K = temp[l1] + 273.15; // Convert °C to Kelvin
			 //float temp_factor = pow(temp_K / 298.15, 1.75); // Temperature scaling
			 float Qref = 20.0;//was 20
			 float Qten = 3.8;//was 3.8
			 float tempATM = temp[l1];
			 tempATM = min(40.0, max(-2.0, temp[l1]));
			 if (temp[l1] < -2.0) tempATM = -2.0;

				
			 float temp_factor = pow(Qten, ((tempATM - Qref) / 10));
			 float soilWaterFactorPoreSpace = pow(air_filled, 30.0 / 3.0) / pow(sts[l1], 2.0);//was 10.0/3.0 but that was too fast for low WFPS with high pore space
			 soilWaterFactorPoreSpace = min(3.0,max(1.0, soilWaterFactorPoreSpace));
			 // soilWaterFactorPoreSpace = 1.0;

			 float D_NO = D0_NO * soilWaterFactorPoreSpace * temp_factor;
			 float D_N2O = D0_N2O * soilWaterFactorPoreSpace * temp_factor;
			 float D_N2 = D0_N2 * soilWaterFactorPoreSpace * temp_factor;

			 //calculates the air-filled concentration based on porosity and water in a soil layer
			 float conc_no = no[l1] / (h[l1] * air_filled);
			 float conc_n2o = n2o[l1] / (h[l1] * air_filled);
			 float conc_n2 = n2[l1] / (h[l1] * air_filled);

			 float conc_no_below = no[l1 + 1] / (h[l1 + 1] * air_filled);//(sts[l1 + 1] - (water[T][l1 + 1] / h[l1 + 1])))
			 float conc_n2o_below = n2o[l1 + 1] / (h[l1 + 1] * air_filled);
			 float conc_n2_below = n2[l1 + 1] / (h[l1 + 1] * air_filled);

			 float dz = h[l1] * 100.0; // convert from metres of soil height to cm
			 float flux_NO;
			 float flux_N2O;
			 float flux_N2;
			 //testing condition if the concentration below is greater than the concentration in a layer. Want to limit to only upward flux of N2O. 

			 //--singular direction N gas flux upwards

			 if (conc_no_below > conc_no) {
				 flux_NO = (-D_NO * (conc_no - conc_no_below) / dz) * h[l1] * air_filled;
			 }
			 else
			 {
				 flux_NO = 0.0;
			 }

			 if (conc_n2o_below > conc_n2o) {
				 flux_N2O = (-D_N2O * (conc_n2o - conc_n2o_below) / dz) * h[l1] * air_filled;
			 }
			 else
			 {
				 flux_N2O = 0.0;
			 }

			 if (conc_n2_below > conc_n2) {
				 flux_N2 = (-D_N2 * (conc_n2 - conc_n2_below) / dz) * h[l1] * air_filled;
			 }
			 else
			 {
				 flux_N2 = 0.0;
			 }

			 //-bidirectional N gas flux
			
		//	 if (snow_pack == 0.0)
			// {
		//		 flux_NO = (-D_NO * (conc_no - conc_no_below) / dz) * h[l1] * air_filled;
			//	 flux_N2O = (-D_N2O * (conc_n2o - conc_n2o_below) / dz) * h[l1] * air_filled;
		//		 flux_N2 = (-D_N2 * (conc_n2 - conc_n2_below) / dz) * h[l1] * air_filled;
			// }
			
			 
			 //microbial consumption
			 
			 // --- Microbial consumption using Michaelis-Menten kinetics ---
			 
			// float microbial_sink_NO = (0.05 * conc_no) / (0.1 + conc_no) * dz;//Vmax = 0.05 ug/cm3/hr and Km = 0.1 ug/cm3
			// float microbial_sink_N2O = (0.03 * conc_n2o) / (0.08 + conc_n2o) * dz;
			// float microbial_sink_N2 = (0.01 * conc_n2) / (0.05 + conc_n2) * dz;

			// if (flux_NO > 0 && flux_N2O>0 && flux_N2>0)
			// {
			//	 flux_NO -= microbial_sink_NO;
			//	 flux_N2O -= microbial_sink_N2O;
			//	 flux_N2 -= microbial_sink_N2;

			//	 float microbial_sink_NOC = rcnb * microbial_sink_NO;
			//	 float microbial_sink_N2OC = rcnb * microbial_sink_N2O;
			//	 float microbial_sink_N2C = rcnb * microbial_sink_N2;
			//	 microbial_sink_NO = 0.0;
			//	 microbial_sink_N2O = 0.0;
			//	 microbial_sink_N2 = 0.0;

			//	 float sumMicrobeC = microbial_sink_NOC + microbial_sink_N2OC + microbial_sink_N2C;
			//	 if (FreezeDOC[l1] < sumMicrobeC) sumMicrobeC = FreezeDOC[l];
			//	 FreezeDOC[l1] -= sumMicrobeC;
			//	 CRB1[l1] += (sumMicrobeC * 0.5);//add New Microbial Biological C to Microbial labile pool
			//	 CRB2[l1] += (sumMicrobeC * 0.5);
			// }
			 
			 //add microbial sink to microbe pool using rcnb



			 // -------------------------------------------------------------


			 //conditional testing to ensure mass balance
			 if (flux_NO >= 0)
			 {
				 if (no[l1 + 1] < flux_NO)flux_NO = no[l1 + 1];
				 no[l1 + 1] -= flux_NO;
				 no[l1] += flux_NO;
				 
			 }
			 else
			 {
				 if (no[l1] < -flux_NO)flux_NO = -no[l1];
				 no[l1 + 1] -= flux_NO;
				 no[l1] += flux_NO;
			 }
			 if (flux_N2O >= 0)
			 {
				 if (n2o[l1 + 1] < flux_N2O)flux_N2O = n2o[l1 + 1];
				 n2o[l1 + 1] -= flux_N2O;
				 n2o[l1] += flux_N2O;
				 
			 }
			 else
			 {
				 if (n2o[l1] < -flux_N2O)flux_N2O = -n2o[l1];
				 n2o[l1 + 1] -= flux_N2O;
				 n2o[l1] += flux_N2O;

			 }
			 if (flux_N2 >= 0)
			 {
				 if (n2[l1 + 1] < flux_N2)flux_N2 = n2[l1 + 1];
				 n2[l1 + 1] -= flux_N2;
				 n2[l1] += flux_N2;
				 
			 }
			 else
			 {
				 if (n2[l1] < -flux_N2)flux_N2 = -no[l1];
				 n2[l1 + 1] -= flux_N2;
				 n2[l1] += flux_N2;
			 }
			 if (l1 == 1)//if layer is 1 then all the nitrogen gas in the top layer are assumed to emit to atmosphere.
			 {
				 float deMinTemp1, deOptTemp1, deMaxTemp1, deAlpha1, deBeta1, deFtm1;
				 deMinTemp1 = -1.0;//minimum temperature for denitrifier bacteria growth
				 deOptTemp1 = 25.0;//optimum temperature for denitrifier bacteria growth
				 deMaxTemp1 = 40.0;//Max temperature for denitrifier bacteria growth
				 deAlpha1 = 1.5;//how fast this drops off below optimum temperature 1.0 slow, 2 is pretty fast
				 deBeta1 = 1.5;//how fast this drops off above optimum temperature.
				 deFtm1 = pow((temp[l1] - deMinTemp1) / (deOptTemp1 - deMinTemp1), deAlpha1) * pow((deMaxTemp1 - temp[l1]) / (deMaxTemp1 - deOptTemp1), deBeta1);
				 if (temp[l1] > deMaxTemp1) deFtm1 = 0.01;
				 if (temp[l1] < deMinTemp1)deFtm1 = 0.01;
				 deFtm1 = min(1.0, max(0.000001, deFtm1));
				 
				 if (year == 7 && jday > 100)
				 {
					 float blah;
					 blah = 1.0;

				 }
				 float reductionFactor;
				 reductionFactor = 1.0;
				 
				 if (temp[l1]>0.0 && (snow_pack*1000) == 0.0 && surf_water==0.0)
				 {
					 emsno = no[l1]*1.0*deFtm1 ;//surface layer no in kg N is assumed to be lost to amtmosphere
					 emsn2o = n2o[l1] * 1.0 * deFtm1;//surface layer n2o in kg N is assumed to be lost to amtmosphere
					 emsn2 = n2[l1] * 1.0 * deFtm1;//surface layer n2 in kg N is assumed to be lost to amtmosphere
					 no[l1] = no[l1]-emsno;
					 n2o[l1] = n2o[l1] - emsn2o;
					 n2[l1] = n2[l1] - emsn2;
				 }
				 else if (temp[l1] < 1.0||surf_water>0.0)
				 {
					 emsno = no[l1] * reductionFactor * deFtm1;//surface layer no in kg N is assumed to be lost to amtmosphere
					 emsn2o = n2o[l1] * reductionFactor * deFtm1; //surface layer n2o in kg N is assumed to be lost to amtmosphere
					 emsn2 = n2[l1] * reductionFactor * deFtm1;//surface layer n2 in kg N is assumed to be lost to amtmosphere
					 no[l1] = no[l1] - emsno;
					 n2o[l1] = n2o[l1] - emsn2o;
					 n2[l1] = n2[l1] - emsn2;

				 }
				 else
				 {

					 emsno = no[l1]* reductionFactor * deFtm1;//surface layer no in kg N is assumed to be lost to amtmosphere
					 emsn2o = n2o[l1] * reductionFactor * deFtm1;//surface layer n2o in kg N is assumed to be lost to amtmosphere
					 emsn2 = n2[l1] * reductionFactor * deFtm1;//surface layer n2 in kg N is assumed to be lost to amtmosphere
					 no[l1] = no[l1] - emsno;
					 n2o[l1] = n2o[l1] - emsn2o;
					 n2[l1] = n2[l1] - emsn2;
					 //emsno = no[l1];//surface layer no in kg N is assumed to be lost to amtmosphere
					 //emsn2o = n2o[l1];//surface layer n2o in kg N is assumed to be lost to amtmosphere
					 //emsn2 = n2[l1];//surface layer n2 in kg N is assumed to be lost to amtmosphere
					 //no[l1] = 0.0;
					 //n2o[l1] = 0.0;
					 //n2[l1] = 0.0;

					 //emsno = 0.0;//surface layer no in kg N is assumed to be lost to amtmosphere
					// emsn2o = 0.0;//surface layer n2o in kg N is assumed to be lost to amtmosphere
					 //emsn2 = 0.0;//surface layer n2 in kg N is assumed to be lost to amtmosphere
					 //no[l1] *= 0.99;
					 //n2o[l1] *= 0.99;
					 //n2[l1] *= 0.99;

				 }

				 *day_soil_an_no += emsno;
				 *day_soil_an_n2o += emsn2o;
				 day_denitrify_n2ol[l1] += emsn2o;
				 *day_soil_n2 += emsn2;
				 emsno = 0.0;
				 emsn2o = 0.0;
				 emsn2 = 0.0;

			 }

		 }



	 }
	 //end improvement - diffusion
	 
   //}
  }
  else //flood_flag = 1
  {
    float emsno, emsn2o, emsn2, a;
    float no_aere, n2o_aere, n2_aere, no_ebul, n2o_ebul, n2_ebul;
	
    if(l<=q) aere = 0.00001 * (Root_Wt[1]+Root_Wt[2])/ 2200.0; 
	else aere = 0.01;
	if (aere > 1.0) aere = 1.0;

	if(l>1)
	{
		n2[l] += (no[l]+n2o[l]) * 0.99;
		no[l] *= 0.01;
		n2o[l] *= 0.01;	
	}
	else
	{
		n2[l] += (no[l]+n2o[l]) * 0.9;
		no[l] *= 0.1;
		n2o[l] *= 0.1;	
	}


    no_aere = no[l] * aere;
    n2o_aere = n2o[l] * aere;
    n2_aere = n2[l] * aere;
	if (n2o_aere < 0)
	{
		float blah;
		blah = 1.0;

	}
    no[l] -= no_aere;
    n2o[l] -= n2o_aere;
    n2[l] -= n2_aere;

    if (no[l] < 0.0) no[l] = 0.0;
	if (n2o[l] < 0.0) { 
		
		n2o[l] = 0.0; 
	}

    if (n2[l] < 0.0) n2[l] = 0.0;

    // NOx efflux by ebulation

    if (l <= 10 )
    {
       float ActTemp, tt;

       if(temp[l] > 0.0) tt = temp[l];
       else tt = 0.0;

       //if (temp[l] < 0.0) temp[l] = 0.0;
       ActTemp = (-.1687 * (float)pow((0.1 * tt), 3.0) + 1.167 * 
				(float)pow((0.1 * tt), 2.0) - 2.0303 * (0.1 * tt) + 1.042);
	   if(ActTemp<0.0) ActTemp = 0.0;

	   if(l<WTL)
		a = PORO * ActTemp * 0.2 * 0.01;//0.2
	   else
		a = PORO * ActTemp * 0.01 * 0.01;//1.0;//crop_t;//0.00007

	   if(l==1) a = 1.0;

	   //a = 0.0;

	   //if(crop_t<0.0) crop_t=0.0;

       no_ebul = no[l] * a;
       n2o_ebul = n2o[l] * a;
       n2_ebul = n2[l] * a;

       no[l] -= no_ebul;
       n2o[l] -= n2o_ebul;
       n2[l] -= n2_ebul;

       if (no[l] < 0.0) no[l] = 0.0;
	   if (n2o[l] < 0.0) {
		   n2o[l] = 0.0;
	   }
       if (n2[l] < 0.0) n2[l] = 0.0;
    }
    else
    {
		no_ebul = 0.0;
		n2o_ebul = 0.0;
		n2_ebul = 0.0;
    }

     emsno = no_aere + no_ebul;
     emsn2o = n2o_aere + n2o_ebul;
     emsn2 = n2_aere + n2_ebul;

#ifdef MANURE
	 if(l==q+1)//housing
	 {
		MData.day_house_no += emsno;
		MData.day_house_n2o += emsn2o;
		MData.day_house_n2 += emsn2;
	 }
	 else if(l==q+4)//composting
	 {
		MData.day_compost_no += emsno;
		MData.day_compost_n2o += emsn2o;
		MData.day_compost_n2 += emsn2;
	 }
	 else if(l==q+5)//lagoon
	 {
		MData.day_lagoon_no += emsno;
		MData.day_lagoon_n2o += emsn2o;
		MData.day_lagoon_n2 += emsn2;
	 }
	 else if(l==q+6)//digester
	 {
		MData.day_digester_no += emsno;
		MData.day_digester_n2o += emsn2o;
		MData.day_digester_n2 += emsn2;
	 }
	 else if(l==q+8)//gutter
	 {
		MData.day_gutter_no += emsno;
		MData.day_gutter_n2o += emsn2o;
		MData.day_gutter_n2 += emsn2;
	 }	
#endif

	 if(l<=q)
	 {
		 *day_soil_an_no += emsno;
		 *day_soil_an_n2o += emsn2o;
		 *day_soil_n2 += emsn2;
		 day_denitrify_n2ol[l] += emsn2o;
	 }

	 //hr_no += emsno;
	 //hr_n2o += emsn2o;
	 //hr_n2 += emsn2;

     emsno = 0.0;
     emsn2o = 0.0;
     emsn2 = 0.0;
  }//flood_flag = 1

  
  } // End of layer loop, go to next layer


} // End of hourly loop, go to next hour

#ifdef MANURE
	if(l<=q) day_co2 += dn_co2;
#else
	day_co2 += dn_co2;
#endif


#ifdef DEBUG_CBALANCE
	day_dn_co2 += dn_co2;   // add this in the module right where you do: day_co2 += dn_co2;
#endif


	//if(sph[l]<4.5&&TTT>0.0) Chemodenitrification(1);

   *day_soil_denitrification += (*day_soil_an_n2o+*day_soil_n2);//d_no3

   //N2O and N2 induced from frozen soil layers during winter -substrate generation during freeze/thaw conditions to facilitate spring melt-emissions ========================================================================================================================
   int FreezeDayCounter = 1;
  if(GN<=q)
   {
	for(int z=1; z<=q; z++) //Loop over soil layers 1 to q = bottom soil layer
	{
		if (year == 7 && jday > 97)
		{
			float blah;
			blah = 1.0;

		}



		float dead_micro, Tt, ACTN, IceDN; 
		//if (temp[z] < -0.1 || min_temp < -15.0 && snow_pack * 1000.0 < 10.0)

		//==============This loop liberates NH4 into the soil pool from microbial pools as a response to freezing soil. Doesn't take into account freezing duration or freeze thaw conditions. 
		if (temp[1] < -0.5 )// || min_temp < -2.5 && snow_pack == 0.0 && z < 2)//if soil temperature below freezing //was -0.1 && snow_pack * 1000.00 <= 10.0 //|| min_temp < -0.1 && snow_pack == 0.0 && temp[z] < 0.5 || min_temp < -0.1 && snow_pack == 0.0 || min_temp < -5.1 && snow_pack == 0.0 || min_temp < -5.5 && snow_pack == 0.0 && z<2
		{		

			/*
			float snowpackRed=1.0;
			if ((snow_pack * 1000.0 ) <= 1.0)
			{
				snowpackRed = 1.0;

			}
			else
			{
				snowpackRed = 1.0;
			}
			*/

			float Fpeat;
			if(st[1]>=12) Fpeat = 0.1;//soil texture factor st[1]=sand st[12]=Organic Soil
			else Fpeat = 1.0;

			Tt = abs(temp[z]) * 0.3;//was 0.1...leah 0.3 ..//was 2.0   //soil temperature of layer [z] //scales the spring burst emissions quite significantly./0.5
			//Tt = pow(0.2,1.0/abs(temp[z]));
			//Tt = -temp[z] * 0.45 + 3.72;

			//if (snow_pack>0.0 && rainfall>0.0) Tt = -min_temp * 5.1;
			//Tt = min(1.0, max(0.0, Tt)); //set min/max soil temperature

			float TCRB = CRB1[z] + CRB2[z]; //total microbe C (two microbe pools CRB1=labile, CRB2=resistant)?
			if(TCRB>0.0) //as long as some microbes available > 0
			{
				dead_micro = Fpeat * Tt * TCRB*0.1;// *0.2115; //microbes to be killed for generation of substrates due to freezing of soil, Fpeat = soil texture factor , Tt=level of soil freezing, TCRB = total microbes available (multiplied by 10%)
				if (dead_micro < 0.0) dead_micro = 0.0;
				dead_micro = min(TCRB,max(0.0, dead_micro));
				//dead_micro = 0.0;

				CRB1[z] -= (dead_micro * CRB1[z] / TCRB); //update C microbe pool 1 for removal of killed microbes from microbe pool based on % of microbe from total of two microbe pools
				CRB2[z] -= (dead_micro * CRB2[z] / TCRB); //update C microbe pool 1 for removal of killed microbes from microbe pool based on % of microbe from total of two microbe pools

				nh4[z] += (dead_micro / rcnb);//add microbe N to NH4 pool
				if (nh4[z] < 0.0)nh4[z] = 0.0;
				FreezeDOC[z] += dead_micro; // add microbe C to FreezeDOC pool (stored for spring burst)
				TotalFreezeDOC += FreezeDOC[z];//tracks the total FreezeDOC in a model
				primeDenit = 25.0;
				
				//primeDenit = 50.0;

			}

			//ice_doc[z] = FreezeDOC[z];
		}

		//if(FreezeDOC[z]>0.0000001 && min_temp > 5.0)

	
		//if (FreezeDOC[z] > 0.0000001 && temp[z] > 1.0 && (snow_pack * 1000.00) <= 0.01 && temp[1] > 1.0 && (ice[1] * 1000) == 0.0)
		if (temp[l] > 0.0)freezeWaterFactor = 1.0;
		//test samantha
		//if (FreezeDOC[z] > 0.0000001 && temp[1] > -1.9)
		//if (FreezeDOC[z] > 0.0000001 && temp[1] > -1.9)

		//=== Checks if FreezeDOC[z] is present and if so if the temperature of a layer is now about a threshold to generate N2O in that layer. 
		if (FreezeDOC[z] > 0.0000001 && temp[z] > -0.7 || SnowMelt > 0.0 && temp[z] < 0.0 && temp[z]>-2.0)// && temp[z] > -2.5//FreezeDOC[z] > 0.0000001  && // && snow_pack * 1000.0 < 5.0) //&& snow_pack * 1000.0 < 5.0 //&& (snow_pack * 1000.00) <= 0.01  //&& (snow_pack * 1000.00) <= 0.01 && temp[1] > 1.0 && (ice[1] * 1000) == 0.0   or || FreezeDOC[z] > 0.0000001 && max_temp>0.0 && precipitation > 0.0  || FreezeDOC[z] > 0.0000001 && max_temp > 0.0 && precipitation > 0.0
		{
			float depthF, soilH;//define variables for influencing depth of application
			soilH = (z * h[1] * 100);//calculate soil height in cm
			float k = 0.01f; //Increase k  faster decay(shallower denitrification zone) Decrease k  deeper denitrification possible
			k = 0.06f;
			depthF = exp(-k * soilH);
			//depthF = 1.0;
			
			if (temp[1]<0.5)
			{
				

			}
			float snowMeltFactor = 1.0;
			if(snow_pack==0.0 && SnowMelt>0.0)
			{
				snowMeltFactor = max_temp*2.0 ;
				if (temp[z] < 0.0 && temp[z]>-2.0)
				{
					snowMeltFactor = 2.5;
				}//was 1.5}

				
				//float blah;
				//blah = 1.0;
				//primeDenit = 200.0;
			}

			float scalarT, scalarT2; //this was to limit the temperature increase to emissions peak. 
			//scalarT2 = -0.0655 * temp[z] * temp[z] + 1.1689 * temp[z] + 0.8497;
			float TFactor5, TNitMin5, TNitMax5, TNitOpt5, thetaNit5, kNit5;
			TFactor5 = 1.0;
			TNitMin5 = -5.0; TNitMax5 = 10.0; TNitOpt5 = 8.0; thetaNit5 = 2.3; kNit5 = 5.0;
			if (temp[1] >= TNitMin5 && temp[1] <= TNitMax5)
			{

				TFactor5 = exp(-((temp[1] - TNitOpt5) * (temp[1] - TNitOpt5)) / (2 * thetaNit5 * thetaNit5));

			}
			if (temp[1] < TNitMin5)
			{
				TFactor5 = 0.0;
			}
			if (temp[1] > TNitMax5)
			{
				TFactor5 = exp(-((temp[1] - TNitOpt5) * (temp[1] - TNitOpt5)) / (2 * thetaNit5 * thetaNit5)) * exp(-((temp[1] - TNitMax5) / (kNit5)));

			}
			if (temp[1] >= 0)
			{
				//TFactor *= 100.0;

			}
			TFactor5 = min(1.0, max(TFactor5, 0.00));
			//TFactor5 *= 50.0;
			//scalarT3 = 0.2054 * temp[z] * temp[z] - 0.0525 * temp[z] + 0.0321;
			//scalarT3 = min(5.50, max(1.0, scalarT3));
			scalarT2 = 1.0;
			
			
			
			if(no3[z]>0.0) //if NO3 in a layer > 0
			{
				float AssN=0.0, AssC= 0.0, GasN=0.0, Mbio=0.0;	
				float F_clay = 0.5 * (1.0 - clay[1]);//clay factor 

				float no3Fact, FreezeFact;
				no3Fact = no3[z] / (1.0 + no3[z]);
				no3Fact = min(1.0, max(no3Fact, 0.01));

				no3Fact = no3[z] / (1.0 + no3[z]);
				no3Fact = min(1.0, max(no3Fact, 0.01));

				FreezeFact = FreezeDOC[z] / (1 + FreezeDOC[z]);
				FreezeFact = min(1.0, max(FreezeFact, 0.01));

				IceDN = 1.0 * no3Fact;//  *FreezeFact;//25.0 //Factor for controlling the rate of Denitrification during spring melt //* FreezeDOC[z]/(1.0+FreezeDOC[z])
				IceDN = min(1.0, max(0.0, IceDN));

				

				//wet in spring
				float soilWaterFactor;
				if (day_wfps[1] > 0.6) { soilWaterFactor = pow(1.0 + (day_wfps[1] - 0.6) / 0.4, 1.2); }
				else { soilWaterFactor = 0.01; }
				soilWaterFactor = min(5.0, max(1.0, soilWaterFactor));
				soilWaterFactor = 1.0;
				
				// Why not make this a function of soil moisture content for N2/N2O proportion. 

				//

				





				//



				float fN2Owfps;
				float fN2wfps;
				fN2Owfps = (16.0 * pow(day_wfps[z], 3.5) * pow((1 - day_wfps[z]), 1.3));
				if(day_wfps[z]<fldcap[l])
				{
					fN2Owfps = 1.0;
				}
				if (day_wfps[z] < 0.7) 
					{ fN2Owfps = 0.98; }
				else
					{
					fN2Owfps = 0.55;
				}
				fN2Owfps = min(0.98, max(0.55, fN2Owfps));
				fN2wfps = 1.0 - fN2Owfps;
				if (max_temp>=1.0&&snow_pack==0.0)
				{
					scalarT = max_temp;
				}
				else
				{
					scalarT = 1.0;
				}
				scalarT = min(1.0, max(1.0, scalarT));
				if ( surf_water>0.0&&snow_pack>0.0)//snow_pack *1000.0 >5.0 ||
				{
					scalarT2 = 0.12;//when Ponded water seems to really limit spring burst
				}
				else scalarT2 = 0.21;
			 //scalarT = 1.0;
				//IceDN = 1.0;//was off
				//IceDN = 0.46;//found this too influential to peaks based on soilno3
				GasN = 20.0*0.000573 * IceDN * scalarT * scalarT2 * soilWaterFactor * springMulti * snowMeltFactor*depthF ;//0.12 //.4//.114 ///0.00914 Geoff //claudia 0.0314  //was  0.02014 // total GAS N species produced as a funcation of ICEDN and NO3 (again?) * springMultiplier (User control)
				//GasN = min(0.020, max(0.0, GasN));
			

				if (GasN > no3[z])
				{
					GasN = no3[z];
				}
				if (GasN < 0)GasN = 0.0;
				no3[z] -= GasN; //remove total GASN from NO3 pool as it would require N substrate //need extra code to ensure this doesn't exceed NO3 availability
				//n2o[z] += GasN * powf(F_clay,0.75);//F_clay //N2O proportion as a function of clay
				n2o[z] += GasN * fN2Owfps;
				//no[z] += GasN * 0.05;
				//n2[z] += GasN * (1.0 - powf(F_clay,0.75)); //N2 proportion as remainder of GasN not evolved as N2O
				n2[z] += GasN * fN2wfps;
				day_denitrification[z] += GasN; //total denitrification as a function of GAS N
				day_denitrify_n2ol[l] += GasN;
				
			}

	//	if( snow_pack == 0.0 && surf_water==0.0)//&& temp[1]>2.5  ||snow_pack==0.0
		//	{
			      //float AvaN = ( nh4[z]), NewBioC, TAvaN = ( nh4[z]);
				float AvaN = (no3[z] + nh4[z]), NewBioC, TAvaN = (no3[z] + nh4[z]);//no3[z] + nh4[z]
				if (AvaN > 0.0)
				{
					if ((AvaN * rcnb) > FreezeDOC[z])//if available mineral N is greater than Frozen labile Dissolved organic Carbon then do this 
					{
						NewBioC = FreezeDOC[z];
						TotalFreezeDOC -= FreezeDOC[z];
						FreezeDOC[z] *= 0.0;
						AvaN -= (NewBioC / rcnb);
						no3[z] = AvaN * (no3[z] / TAvaN);
						nh4[z] = AvaN * (nh4[z] / TAvaN);
					}
					else//if available mineral N is less than Frozen labile Dissolved organic Carbon then do this 
					{
						NewBioC = AvaN * rcnb * 1.0;//rcnb is the C:N ratio of microbial pool at 10:1
						AvaN *= 0.0;
						FreezeDOC[z] -= NewBioC; //
						TotalFreezeDOC -= NewBioC;//TotalFreezeDOC is a accumulator to keep track of total Frozen DOC
						no3[z] = 0.0;//reset nitrate pool to zero
						nh4[z] = 0.0;//reset ammonium pool to zero

						
					}
					
					
					//FreezeDOC[z] = 0.0;
					
					/*
					micro_growth = 0.2166 * (FreezeDOC[z] / (1.0 + FreezeDOC[z]));
					if (micro_growth < 0.0) micro_growth = 0.0;

					micro_death = 0.008 * denitrifier[z] * 1.0 / (1.0 + FreezeDOC[z]) ;
					micro_death = 0.0;

					micro_delta = (micro_growth - micro_death) * denitrifier[z]  ;
					micro_delta = micro_growth;
					denitrifier[z] += micro_delta;
					
					NewBioC -= micro_delta;
					//FreezeDOC[z] -= micro_delta;
					*/
					CRB1[z] += (NewBioC * 0.5);//add New Microbial Biological C to Microbial labile pool
					CRB2[z] += (NewBioC * 0.5);//add New Microbial Biological C to Microbial resistant pool
					
					
					//if (snow_pack > 0.0) { FreezeDOC[z] += 0.01; }
				}
				
		//	}//snow condition
			

			//testing a limited DOC draining function based on temperature and freeze conditions
			/*
			float AvaN = no3[z] + nh4[z];
			float TAvaN = AvaN; // Tracker for total available mineral N
			float NewBioC = 0.0;

			// Temperature-dependent microbial activity factor (Q10 scaling)
			float Q10 = 2.0;
			float Tref = 10.0;
			float tempFactor = pow(Q10, (temp[l] - Tref) / 10.0);
			tempFactor = max(0.0f, min(tempFactor, 1.0f)); // Clamp between 0 and 1

			// Freezing point inhibition (sigmoid response)
			float Tsoil = temp[l];
			float Tmid = 0.0f;  // Midpoint temperature (°C)
			float Twidth = 5.0f; // Spread of the transition zone (°C)
			float freezeInhibition = 1.0f / (1.0f + exp(-(Tsoil - Tmid) / Twidth));

			// Combine both temperature effects
			float activityFactor = tempFactor * freezeInhibition;

			if (AvaN > 0.0 && activityFactor > 0.01f) { // Only proceed if there's N and microbial activity is non-negligible
				float maxAccessibleDOC = FreezeDOC[z] * activityFactor;

				if ((AvaN * rcnb) > maxAccessibleDOC) {
					NewBioC = maxAccessibleDOC;
					TotalFreezeDOC -= maxAccessibleDOC;
					FreezeDOC[z] -= maxAccessibleDOC;

					AvaN -= (NewBioC / rcnb);
					if (TAvaN > 0.0f) {
						no3[z] = AvaN * (no3[z] / TAvaN);
						nh4[z] = AvaN * (nh4[z] / TAvaN);
					}
				}
				else {
					NewBioC = AvaN * rcnb;
					AvaN = 0.0f;

					float docLoss = min(NewBioC, maxAccessibleDOC);
					FreezeDOC[z] -= docLoss;
					TotalFreezeDOC -= docLoss;

					no3[z] = 0.0f;
					nh4[z] = 0.0f;
				}

				// Distribute new microbial C
				CRB1[z] += (NewBioC * 0.5f);
				CRB2[z] += (NewBioC * 0.5f);
			}
			*/
			//new addition end
		}


	}
   }

} 


