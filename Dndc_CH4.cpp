#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;
#endif

float class_model::CH4_paddy(int MODE, int GN, float *temp, float *clay, int flood_num, int FloDays, float *Root_Wt,
							  int q, float *Eh, float *sph, float *vascularity, int LandUse, float *day_rco2,
							  float *R_Wt, float day_co2, float root_dCO2, int flood_flag, float *rcvl,
							  float *rcl, float *rcr, int *st, float rcnrvl, float rcnrl, float rcnrr,
							  float MicrobioIndex, float *ch4, int WTL, float day_WT,
							  float *soil_ph, float *doc, float *nh4, float *ch4_prod, float *ch4_day_oxid,
							  float *plant_day_ch4, float *day_wfps, int *seed, float *day_ch4, float *anvf,
							  float WaterLeakRate, float *h, float *CRB1, float rcnb, float *co2, float *crhl, float *crhr,
							  float air_temp, float *ch4_doc_pool, float *F_methanogen,
							  int WaterControl, float *Tttoo, int jday, float rcnh, float *H2,
							  float *day_ch4_CO2, float *day_ch4_1, float *day_ch4_2, float *SO4, float day_root_resp,
							  float *PGI, int ShallowFloodFlag, float stub1, float stub2, float stub3, float *day_H2_prod)
{
	int l, step, stunde, BL, EL;
	float T, FF, F_temp, soil_t, Coef1, Coef2, CH4_P1, CH4_P2, CH4_P3, pro_ch4;// C_soil, 
	float SMS, saturated_CH4, CCH4, CH4_concentration, plant_ch4, convertor, CH4_O,O2_mol,CH4_out, CH4_in;
	float surf_w_fact, max_surf_w, temp_eb_f, F_clay, bubble_em_f, ch4_balloon, F_texture;
	float FFclay, FFst, TotalRootWT, Froot, F_leak, TotalVas;
	float Rt=8.31;//temperature coefficient 1
	float EA=87000.0; //temperature coefficient 2		 
	float ch4_eb=0.0;
	float NewSumRootCO2, PeatDOC=0.0;;
	float flood_pH;//, flux_co2=0.0;	 
	float w_anvf, w_hete_CO2=0.0, w_day_ch4=0.0;
		
	//float DRco2 = day_root_resp;
	float InputRoot_DOC[300]={0.0,0.0}, InputSoil_DOC[300]={0.0,0.0};

	CH4_P1=0.0;
	CH4_P2=0.0;
	CH4_P3 = 0.0;
	pro_ch4=0.0;
	max_surf_w=0.2; //max. water depth, m	

	surf_w_fact = 0.005;//1.0 - surf_w / (max_surf_w + 0.01);

	//clay factor---------------------------------------------------------	 
	 if(clay[1] < 0.05) FFclay = 0.05;
	 if(clay[1] > 0.5) FFclay = 0.5;
	 else FFclay = clay[1];
	 F_clay = 1.0 * (1.0 - exp((-FFclay) * 10.0) * 3.0);
	 if (F_clay <0.1) F_clay = 0.1;
	 if (F_clay > 1.0) F_clay = 1.0;

	 //soil texture-------------------------------------------------------	 
	 //F_texture = exp((-FFclay) * 10.0) * 3.0;	 
	 if(st[1]>10) FFst = 10.0;
	 else FFst = (float)st[1];
	 F_texture = -0.015*FFst*FFst + 0.021*FFst + 1.409;
	 F_texture = min(1.0, max(0.0, F_texture));
	 F_leak = max(1.0, WaterLeakRate*50.0);//leak
	 if(MODE==1) F_leak = 1.0;
     
	 //root vascularity
	 TotalRootWT = Root_Wt[1]+Root_Wt[2]+Root_Wt[3];
	 Froot = TotalRootWT / (50.0 + TotalRootWT);
	 if(GN>q) Froot = 1.0;
	 TotalVas = max(vascularity[1], max(vascularity[2],vascularity[3]));

	 //float Ff = (float)FloDays / 150.0;//150
	 //Ff = max(0.0, min(1.0,Ff));
	 
	if(GN>q)//livestock farm facility
	{
		BL = GN; EL = GN; 
		
		if(GN==q+4) Eh[GN] = -50.0;//compost
		else if(GN==q+5||GN==q+6||GN==q+8) Eh[GN] = -250.0;//lagoon
		else 
		{
			if(day_wfps[GN]==1.0) Eh[GN] = -250.0;
			else Eh[GN] = (1.0 - day_wfps[GN]) * 500.0;
		}
	}
	else
	{
		BL = 1; EL = q;
	}

	for (l=BL; l<=EL; l++)
	{
		//clay effect----------------------------------------------
		Coef1 = min(300.0, 122.88 * powf(FFclay, -0.7414));//300 ???		 
		if(Coef1 < 0.0) Coef1 = 0.0;

		//balloon--------------------------------------------------
	
		if(flood_flag==1&&GN<=q)
		{
			if(SO4[l]>0.75)//mol/kg soil
			{
				Eh[l] = 0.0;
				ch4_balloon = 0.0;

				float dS = SO4[l] * 0.005;//0.15
				SO4[l] -= dS;
				day_H2S_flux += dS;								
			}
			else
			{
				Eh[l]=-180.0;
				ch4_balloon = 0.9;
			}

			/*if(Eh[l]<=-150.0)
				ch4_balloon += 0.05;//0.008 * anvf[l]*exp(-0.0308*Eh[l]);
			else if(Eh[l]>-150.0&&Eh[l]<=0.0)
				ch4_balloon = 0.0;
			else
				ch4_balloon = 0.007 * anvf[l]*exp(-0.0308*Eh[l]);*/
		}
		else
		{
			ch4_balloon = 0.9;
		}

		//ch4_balloon *= (1.0 - aerenchyma);
		
		ch4_balloon = max(0.0, min(1.0, ch4_balloon));

		if(LandUse==5)
		{
			float Fwd;
			if(WTL<=0) Fwd = 0.0;
			else Fwd = (float)WTL;
			ch4_balloon /= (5.0 + 5.0*Fwd); 
		}

		//methanogen activity as a function of time 
		 if(st[l]>12&&WTL<q)//Organic soil
		 {
			F_methanogen[l] = 1.0;
		 }
		 else
		 {
			 if(WaterControl==2) //driven by observed WT data
			 {
				F_methanogen[l] = (50.0 * exp(0.047*(float)FloDays) * (1.0 + powf(F_clay,0.5))-0.3) * Tttoo[l];
			 }
			 else
			 {	
				 if(WaterControl==1) 
					 F_methanogen[l] = (5.0 * exp(0.047*(float)FloDays) * (1.0 + powf(F_clay,0.5))-0.3) * Tttoo[l] ;
				 else
				 {
					 if(flood_num==1)
						F_methanogen[l] = (5.0 * exp(0.047*(float)FloDays) * (1.0 + powf(F_clay,0.5))-0.3) * Tttoo[l] ;//0.1;
					 else
						F_methanogen[l] = 50.0 * (0.2259 * log((float)FloDays) + 0.113) * (1.0 + powf(F_clay,0.5)) * (1.0 / (float)(flood_num-1)) * Tttoo[l];//50.0
			 	 }		
			 }
		 }
		 
		 F_methanogen[l] = max(0.0, min(1.0, F_methanogen[l]));

		 if(l>q)  F_methanogen[l] = 1.0;

		//temperature factor (Arrhenius equation (ref. Ding & Wang,1996))-----------------
		// CH4 production rate is a first order chemical reaction of temperature
		if(GN<=q)
		{
			if (temp[l] < 0.0) soil_t = 0.0;
			else 
			{
				if(WTL<=0) soil_t = temp[l];//[15]
				else soil_t = temp[l];
			}
		}
		else
		{
			soil_t = temp[GN];
		}

		T = soil_t + 273.0;
		
		float Mttt = -87000.0;
		if(MODE==1) Mttt = -82000.0;

		//Mttt = -82000.0;
	 
		F_temp = 5.0 * 1.1574E13 * (float)exp(Mttt / 8.31 / T);
		F_temp = min(1.0, max(0.0, F_temp));
		
		// saturated concentration of CH4 in water, (approx. using values of Kaltofen et al. 1975)  
		if(T <= 0.0)
			SMS = 0.056;
		else
			SMS = 0.0285 * exp(-0.0414*T) + 0.0115;

		saturated_CH4 = SMS / (22.42 / 1000.0) * 12.0 / 1000.0; //kg CH4-C/m3 water
		saturated_CH4 *= 10000.0 * h[1]; // kg CH4-C/ha/layer 

		
 		// general effect of environemtal factors----------------------------------------------
		if(l>q) 
		 {
			 if(l==q+1) FF = 1.0;//0.5; //housing
			 //else if(l==q+2) FF = 0.1; //outdoor pen
			 else if(l==q+3) FF = 0.1; //grazing
			 else if(l==q+4) FF = 0.5; //compost
			 else if(l==q+5) FF = 1.0; //lagoon
			 else if(l==q+6) FF = 1.0; //digester
			 else if(l==q+8) FF = 1.0;//house gutter
			 else FF = 0.0;
		 }
		 else
		 {
			FF = 0.05 * F_temp * Coef1 * ch4_balloon * F_methanogen[1] * F_texture / F_leak;//0.025
		 }

		 FF = min(1.0, max(0.0, FF));

     //C sources-------------------------------------------------------------------------------
	 if(GN==q)//cropping land soil
	 {
		if (TotalRootWT>0.0)
		{
			 float bq = powf(0.5, (float)l);
			 float fPGI = 0.625;//1.0;
			 if(u_PGI>0.75) 
			 {
				 fPGI = 1.0 - u_PGI * 0.5;
				 //fPGI *= 0.25;//Modified for CA rice of Maegen case ???
			 }		
		 
		   InputRoot_DOC[l] = 0.02 * TotalRootWT * fPGI * bq; // * 0.05;//(kg C/ha/layer)//DRco2 +
		   		   
		   doc[l] += InputRoot_DOC[l];
		   day_RootInput_DOC += InputRoot_DOC[l];
		   		   
		   //ch4_doc_pool[l] += InputRoot_DOC[l];
		   InputRoot_DOC[l] = 0.0;
		}
		else
		{
		   InputRoot_DOC[l] = 0.0;
		}     

	 
		//DOC, CO2 and H2 from soil litter decomposition: (C6H12O6 -> CH3COOH + CH3CH2COOH + CO2 + H2)
		InputSoil_DOC[l] = 0.0;
		float Rcc = 0.8;//5.0/6.0;
		float Rhh = 2.0/72.0;//by weight
		float dccc;

		if(rcvl[l]>0.0&&FloDays>5) 
		{
			float FFCC =  min(1.0, F_temp * 100.0);

				dccc = rcvl[l] * FFCC;//0.001;//kg C/ha
				InputSoil_DOC[l] += (dccc * Rcc);

				doc[l] += (dccc * Rcc);
				co2[l] += (dccc * (1.0 - Rcc));				
				//H2[l] += (dccc * Rhh);//kg H/ha
				//day_H2_prod[l] += (dccc * Rhh);//kg H/ha
				nh4[l] += (dccc / rcnrvl);
				rcvl[l] -= dccc;

				rcvl[l] = max(0.0, rcvl[l]);
		}
			
		if(rcl[l]>0.0&&FloDays>5) 
		{
			float FFCC =  min(1.0, F_temp * 5.0);

				dccc = rcl[l] * FFCC;//0.5;
				InputSoil_DOC[l] += (dccc * Rcc);

				doc[l] += (dccc * Rcc);
				co2[l] += (dccc * (1.0 - Rcc));				
				//H2[l] += (dccc * Rhh);
				//day_H2_prod[l] += (dccc * Rhh);//kg H/ha
				nh4[l] += (dccc / rcnrl);
				rcl[l] -= dccc;

				rcl[l] = max(0.0, rcl[l]);
		}
			
		if(rcr[l]>0.0&&FloDays>5) 
		{		
			float FFCC =  min(1.0, F_temp * 0.2);

				dccc = rcr[l] * FFCC;//0.0005
				InputSoil_DOC[l] += (dccc * Rcc);
				
				doc[l] += (dccc * Rcc);
				co2[l] += (dccc * (1.0 - Rcc));				
				//H2[l] += (dccc * Rhh);
				//day_H2_prod[l] += (dccc * Rhh);//kg H/ha
				nh4[l] += (dccc / rcnrr);
				rcr[l] -= dccc;

				rcr[l] = max(0.0, rcr[l]);
		}

		//ch4_doc_pool[l] += InputSoil_DOC[l];
		doc[l] += InputSoil_DOC[l];
		InputSoil_DOC[l] = 0.0;

		//DOC, CO2 and H2 from stub decomposition
		if(l==1&&flood_flag==1 && (stub1+stub2+stub3)>0.0)
		{
			if(stub1>0.0&&FloDays>10) 
			{
				float FFCC =  min(1.0, F_temp * 100.0);

					dccc = stub1 * FFCC;//0.001;//kg C/ha
					InputSoil_DOC[l] += (dccc * Rcc);
					doc[l] += (dccc * Rcc);
					co2[l] += (dccc * (1.0 - Rcc));				
					//H2[l] += (dccc * Rhh);//kg H/ha
					//day_H2_prod[l] += (dccc * Rhh);//kg H/ha
					nh4[l] += (dccc / rcnrvl);
					stub1 -= dccc;

					stub1 = max(0.0, stub1);
			}
			
			if(stub2>0.0&&FloDays>10) 
			{
				float FFCC =  min(1.0, F_temp * 0.5);

					dccc = stub2 * FFCC;
					InputSoil_DOC[l] += (dccc * Rcc);
					doc[l] += (dccc * Rcc);
					co2[l] += (dccc * (1.0 - Rcc));				
					//H2[l] += (dccc * Rhh);
					//day_H2_prod[l] += (dccc * Rhh);//kg H/ha
					nh4[l] += (dccc / rcnrl);
					stub2 -= dccc;

					stub2 = max(0.0, stub2);
			}
			
			if(stub3>0.0&&FloDays>10) 
			{		
				float FFCC =  min(1.0, F_temp * 0.1);

					dccc = stub3 * FFCC;//0.0005
					InputSoil_DOC[l] += (dccc * Rcc);
					doc[l] += (dccc * Rcc);
					co2[l] += (dccc * (1.0 - Rcc));				
					//H2[l] += (dccc * Rhh);
					//day_H2_prod[l] += (dccc * Rhh);//kg H/ha
					nh4[l] += (dccc / rcnrr);
					stub3 -= dccc;

					stub3 = max(0.0, stub3);
			}

			//doc[l] += InputSoil_DOC[l];//ch4_doc_pool[l]
			InputSoil_DOC[l] = 0.0;
/*				float DD = 0.35 * F_temp;//0.001
				float dFDC, dFDC1, dFDC2, dFDC3, dLN;

				DD=min(1.0, max(0.0, DD));

				dFDC1 = stub1 * DD;
				//InputSoil_DOC[l] += (dFDC1 * Rcc);
				//co2[l] += (dFDC1 * (1.0 - Rcc));				
				//H2[l] += (dFDC1 * Rhh);
				//day_H2_prod[l] += (dFDC1 * Rhh);//kg H/ha
				nh4[l] += (dFDC1 / rcnrl);
				stub1 -= dFDC1;

				dFDC2 = stub2 * DD * 0.1;
				//InputSoil_DOC[l] += (dFDC2 * Rcc);
				//co2[l] += (dFDC2 * (1.0 - Rcc));				
				//H2[l] += (dFDC2 * Rhh);
				//day_H2_prod[l] += (dFDC2 * Rhh);//kg H/ha
				nh4[l] += (dFDC2 / rcnrvl);
				stub2 -= dFDC2;

				dFDC3 = stub3 * DD * 0.05;
				//InputSoil_DOC[l] += (dFDC3 * Rcc);
				//co2[l] += (dFDC3 * (1.0 - Rcc));				
				//H2[l] += (dFDC3 * Rhh);
				//day_H2_prod[l] += (dFDC3 * Rhh);//kg H/ha
				//nh4[l] += (dFDC3 / rcnrvl);
				stub3 -= dFDC3;

				*day_ch4 += dFDC1 + dFDC2 + dFDC3;

*/					//dFDC = dFDC1+dFDC2+dFDC3;
					//dLN = dFDC1/rcnrvl+dFDC2/rcnrl+dFDC3/rcnrr;
					//CRB1[l] += (dLN * rcnb);					
					//dFDC -= (dLN * rcnb);
					//C_soil += dFDC;
		}
	 }
	 else//manure
	 {
#ifdef MANURE
		InputRoot_DOC[GN] = 0.0;
		if(GN==q+8||GN==q+1) //gutter or floor
		{
			/*float tmc= doc[GN]+crhl[GN]+crhr[GN];
			*C_soil = 0.2 * tmc;			
			doc[GN] -= (*C_soil * doc[GN] / tmc);
			crhl[GN] -= (*C_soil * crhl[GN] / tmc);
			crhr[GN] -= (*C_soil * crhr[GN] / tmc);
			float ddn = (*C_soil * crhr[GN] / tmc) / rcnh + (*C_soil * crhl[GN] / tmc) / rcnh; 
			nh4[GN] += ddn;*/ //??? error on N balance

		/*	float tmc= 0.15 * doc[GN];
			//*C_soil = tmc;
			InputSoil_DOC[GN] = tmc;
			doc[GN] -= tmc;
			co2[GN] += tmc;
			H2[GN] = tmc;

			ch4_doc_pool[l] += tmc;*/

			//if(l<=q) day_DOC_cons += tmc;
		}
		else
		{
			if(Eh[GN]<-100.0)
			{	
				float ssoc = doc[GN]+crhl[GN]+crhr[GN];

				if(MData.mm_GroundSurface[1]==3&&ssoc>300.0)//outdoor pen with open air
				{
					InputSoil_DOC[GN] = 0.5*doc[GN];
					co2[GN] += 0.5*doc[GN];
					InputSoil_DOC[GN] = max(0.0, InputSoil_DOC[GN]);
					H2[GN] = InputSoil_DOC[GN];						
					doc[GN] -= InputSoil_DOC[GN];
					day_DOC_cons += InputSoil_DOC[GN];
				}
				else
				{
					InputSoil_DOC[GN] = 1.0*(doc[GN]-10.0);//0.4
					InputSoil_DOC[GN] = max(0.0, InputSoil_DOC[GN]);
					H2[GN] = InputSoil_DOC[GN];			
					doc[GN] -= InputSoil_DOC[GN];
					day_DOC_cons += InputSoil_DOC[GN];
				}
			}
			else
			{
				InputSoil_DOC[GN] = 0.0;
				H2[GN] = 0.0;
			}
		}
#endif
	 }

     //---- gross CH4 production (ref. Cappenberg TH.E, 1975.
     //     Relationship between sulfate-reducing and methane-producing
     //     bacteria, Plant and Soil, 43, 125-139.

     // Hypothysis: only the C_co2 within anaerobic balloon is available
     //             for methanogenesis
	 // Unit conversions: C: kg to mole by 1.0/5.378 and 1.0/6.43
     // 86400.0: from second to hour;
     // 1/10000.0: from cm to m;
     // 1000.0: from kg to g;
     // 1/12.0: from g C to mol C
 	 

	 /////////modified based on Fumoto's routine//////////////////////////
			 
	 //--- kinetic parameters and variables for CH4 production ------------------------------
	 float ch4_max_30=0.0, Q10CH4=0.0, ch4_max=0.0, ch4_max_h2=0.0, ch4_max_doc=0.0, km_h2=0.0, km_doc=0.0;//, K1_DOC;
	 float H2_conc=0.0, avail_h2=0.0, doc_conc=0.0, dAcetate=0.0;
			 
	 // saturated H2 conc. in water at 25C, from Henry const. (Atkins 1998, Physical Chemistry 6th ed., Oxford U. Press)
	 float saturate_h2 = 0.78E-3; //! (mol H2 /L)
	 float V_water = day_wfps[l] * h[l] * 10000.0 * 1000.0;//liter water/ha in layer l
	 
	 saturate_h2 = saturate_h2 * 2.0 * V_water / 1000.0; // kg H/ha/layer

	 // Max. CH4 production rate at 30C. 2.0E-5 (mmol/L/s) or 5.0E-5 (mmol/kg soil/s) (Van Bodegom and Scholten, 2001) 
	 if(l>q) 
	 {
		 ch4_max_30 = 10.0 * day_wfps[l] * temp[l]/10.0;//1000.0 * 5.0E-5 * 1.0E-6 * 12.01 * 3600.0 * 24.0;
	 }
	 else
	 {
		 ch4_max_30 = 5.0E-5 * 1.0E-6 * 12.01 * 3600.0 * 24.0 * mmm[l];//! (kgC/ha/day per layer)
		 //ch4_max_30 = 2.0E-5 *1.0E-6 *12.01 *3600.0 * soil_water;//! (kgC/ha/h) <--- looks too low
	 }

	 //DOC decomposition
	 float Rhh = 2.0/72.0;//by weight
	 float AAD = doc[l] * 0.05;
	 doc[l] -= AAD;
	 H2[l] += (AAD * Rhh);
	 day_H2_prod[l] += (AAD * Rhh);//kg H/ha
	 co2[l] += AAD;//(AAD * (1.0 - Rhh)); 	 

	 Q10CH4 = 4.6;//! Q10 for CH4 production (van Bodegom and Stams,1999, Chemosphere 39:167-182)

	 if(temp[l]<=0.0) 
		 ch4_max = 0.0;
	 else if (temp[l] < 40.0) 
		 ch4_max = ch4_max_30 * powf(Q10CH4, (temp[l] - 30.0)/10.0); //!
	 else 
		 ch4_max = ch4_max_30 * Q10CH4 ;//! fixed Vmax over 40C

	 ch4_max_h2 = ch4_max * 0.1;//0.5;//! Vmax of CH4 production from H2
	 ch4_max_doc = ch4_max * 0.1;//0.5;//! Vmax of CH4 production from DOC

	 km_h2 = 13.3E-6 * 2.0 * V_water / 1000.0;//!  Km for H2 (mol H2/L -> kg H/ha/layer) (Van Bodegom and Scholten, 2001)
	//	 km_h2 = 13.3E-4;//! 
	 km_doc = 5.12E-3 * 12.0 * V_water / 1000.0;//! Km for acetate (mol DOC /L -> kg C/ha/layer) (Van Bodegom and Scholten, 2001)

	// K1_DOC = 0.286;//! virtual 1st-order rate constant at 30C (/d) (Van Bodegom and Scholten, 2001; Bodegom and Stams, 1999) 
	//	 K1_DOC = 0.5;//! theoretical maximum
		
	//----- available H2 
	//H2_conc = min(saturate_h2, hour_h2 / n * m /soil_water); //! (mol H2/L)
	H2_conc = min(saturate_h2, H2[l]); //! (kg H/ha/layer)
	avail_h2 = H2_conc;// kg H/ha/layer /1000.0 * water[1][l];//! (kmol H2/ha)

	//----- CH4 production from H2 and CO2 at this time step 
	//day_ch4_CO2[l] = co2[l];

	CH4_P1 = 0.5 * ch4_max_h2 * H2_conc/(km_h2 + H2_conc) * MicrobioIndex;//(float)pow(MicrobioIndex,2.0); //! (kgC/ha) 
	//pro_ch41 = ch4_max_h2;//! CH4 production with high affinity to H2 (kgC/ha)

	
	if (CH4_P1 >= co2[l]) 
	{
		CH4_P1 = co2[l];//! limit by CO2, kg C/ha/layer
		co2[l] = 0.0;
	}
	else 
	{
		co2[l] -= CH4_P1; //! CO2 after CH4 production (kgC/ha/layer)
	}

	if(l<=q&&CH4_P1>0.0)
	{
		H2[l] -= CH4_P1 /12.01 * 4.0;//! H2 after CH4 production (kg H/ha/layer)
		if(H2[l]<0.0) H2[l] = 0.0;		
	}

	//----- CH4 production from DOC 
	
	//float Totdoc = InputRoot_DOC[l] + InputSoil_DOC[l];//kg C/ha/layer
			
	//ch4_doc_pool[l];// = Totdoc;
	/*if(GN>q&&rcr[l]>0.0)//Manure farm
	{

		ch4_doc_pool[l] += (0.025 * rcr[l]);
		rcr[l] *= 0.95;
	}*/

	if(l>q)//farm manure
	{
if(jday==190)
jday=jday;
		if(doc[l]>0.0)
		{
			if(l==q+8)//manure feedlot gutter
				dAcetate = doc[l] * 0.01 * FF;
			if(l==q+1)//manure feedlot floor
			{
				float fT =  (0.0017*temp[l]*temp[l] + 0.0057*temp[l] + 0.0057);//temp[l]/30.0;//0.9 * pow(Q10CH4, temp[l])/10.0;
				fT = min(1.0, max(0.0, fT));
				dAcetate = doc[l] * fT * FF;
			}
		}
		else
			dAcetate = 0.0;
	}
	else//soil
	{

		if(doc[l]>0.0)
		{
				//dAcetate = ch4_max_doc * ch4_doc_pool[l]/(km_doc + ch4_doc_pool[l]) * (float)pow(MicrobioIndex,2.0); //consumption of acetate, kg C/ha/layer// ! (kg CH4-C/ha)
				dAcetate = 5.0 * ch4_max_doc * doc[l]/(100.0 + doc[l]) * MicrobioIndex;//(float)pow(MicrobioIndex,2.0);
				//km_doc = 9.216
				if (dAcetate > doc[l]) dAcetate = doc[l];//! limit by DOC

				if ((dAcetate * 0.5) > (ch4_max - CH4_P1)) 
					dAcetate = (ch4_max - CH4_P1) * 2.0;//! 
		}
		else
			dAcetate = 0.0;
	}		

	if(doc[l] >= dAcetate)
	{
		doc[l] -= dAcetate; //doc_conc -= dAcetate;
	}
	else
	{
		dAcetate = doc[l];
		doc[l] = 0.0;
	}

	CH4_P2 = dAcetate * 0.95;//! CH4 production, kg C/ha/layer
	co2[l] += dAcetate * 0.05;//! CO2 after CH4 production (CH3COOH ---> CH4 + CO2), kg C/ha/layer 
		
	
		
	//----- CH4 production on the day 
	pro_ch4 = CH4_P1 + CH4_P2;//! 1.0
	day_ch4_1[l] = CH4_P1;
	day_ch4_2[l] = CH4_P2;

	//ch4_doc_pool[l] -= CH4_P2;
					    
	/////////End of Fumoto's routines////////////////////

/*	if(ch4_doc_pool[l] >= pro_ch4)
		ch4_doc_pool[l] -= pro_ch4;
	else
	{
		pro_ch4 = ch4_doc_pool[l];
		ch4_doc_pool[l] = 0.0;
	}
*/
	//ch4_doc_pool[l] -= pro_ch4;

	 ch4[l] += pro_ch4;//kg C/ha/layer
	 CH4_P1 = 0.0;
	 CH4_P2 = 0.0;
	
     *ch4_prod += pro_ch4; // daily ch4 production (kg CH4-C/ha/d)

	 //DRco2 -= CH4_P1;
	 //co2[l] -= CH4_P1;
	 
/*	 if(InputRoot_DOC[l] > CH4_P1)
		 InputRoot_DOC[l] -= CH4_P1;
	 else
	 {
		CH4_P1 = InputRoot_DOC[l];
		InputRoot_DOC[l] = 0.0;
	 }*/
	 
	 //*C_soil -= CH4_P2;
	 /*if(InputSoil_DOC[l] > CH4_P2)
		InputSoil_DOC[l] -= CH4_P2;
	 else 
	 {
		CH4_P2 = InputSoil_DOC[l];
		InputSoil_DOC[l] = 0.0;
	 }*/

	 //CH4_P1 = 0.0;
	 //CH4_P2 = 0.0;
	 pro_ch4 = 0.0;
	 

 		//CH4 oxidation
		float RFclay = 30.544*log(max(0.1, FFclay)) + 104.08;// 0.4
	 
		// Hypothysis: only the CH4 outside anaerobic balloon is
		// available for oxidation
		CH4_out = ch4[l] * (1.0 - ch4_balloon);//kg ch4-C/ha/layer
	
		CH4_in = ch4[l] * ch4_balloon;//kg ch4-C/ha/layer

		float f_Eh = -2.0 * Eh[l];//300.0;//-Eh[l];//day_O2[l] / 32.0 / 10.0 / h;//mol O2/m3 soil  
		if(f_Eh<0.0) f_Eh = 0.0;

		if(soil_t<0.0001) soil_t=0.0001;

		//CH4 oxidation rate: dual substrate Michaelis-Menten kinetics
		// ref. Watson etal(1997), Soil Biol Biochem 8:1257-1267

		CH4_O = 0.07 * RFclay * (CH4_out / (5.0 + CH4_out));// * (f_Eh / (100.0 + f_Eh));// * Froot;//0.05-0.09	
       
		 if(TotalRootWT==0.0&&GN==q) CH4_O *= 0.1;
		// 0.045 = CH4 Michaelis constant for CH4-oxidation; mol CH4/m3 water
		// 0.033 = O2 Michaelis constant for CH4-oxidatio; mol O2/m3 water
		// both constants from Nedwell & Watson (1995) Soil Biol Biochem 27, 893-903
		// 5E-5: oxidation potential constant mol m-3 s-1
		// 3600 = conversion sec to day

		CH4_O = max(0.0, min(CH4_out, CH4_O));  
		
		if(ShallowFloodFlag==1) CH4_O = 0.3 * ch4[l];

		ch4[l] -= CH4_O;//CH4_out + CH4_in;

	    co2[l] += CH4_O;
	       
       *ch4_day_oxid += CH4_O;//daily oxidation rate (kg CH4-C/ha/d)

	   

 	   //plant transport 
	   plant_ch4 = 0.0;
       Coef2 = 0.0;

	   if (TotalRootWT>0.0&&GN==q)
	   {
		  float Fratio = 0.0001 * TotalRootWT * Froot * TotalVas;	//0.00005

		  if(u_PGI > 0.5) Fratio *= (float)pow((1.5 - u_PGI),3.0);
		  
		  Fratio = min(1.0, max(0.0, Fratio));

		  // CH4 plant transport is linearly related to CH4 concentration in pore water (ref. Walter et al., 1996. p.3727)
		  plant_ch4 = ch4[l] * Fratio;  //flux, kg CH4-C/ha/d/layer

		}
		else
		{
			plant_ch4 = 0.0;
		}

		ch4[l] -= plant_ch4;
		if(ch4[l]<0.0) ch4[l] = 0.0;

       *plant_day_ch4 += plant_ch4;
       //flux: kg CH4-C/ha/d)

	   //  bubble ebullition
	   float EBF;
	   //if(TotalRootWT<=0.0)
	   {
		   if((stub1+stub2+stub3)>0.0) 
		   {
			   EBF = max(0.01, min(1.0, stub3 / 20000.0));
		   }
		   else
		   {
				//if(IrriRice_flag==1) 
			   if(flood_flag==1)
					EBF = 0.01;//0.01;
				else 
					EBF = 0.01;//0.05;
		   }
	   }

	   if(GN>q) 
	   {	
		   CCH4 = ch4[l];
		   ch4[l] = 0.0;		   
	   }
	   else
	   {
		   /*if(Froot>0.0)
		   {
			   //ebul_ch4 = EBF * ch4_doc_pool[l] * Ff * temp[1]/40.0;//0.0025
			   //ch4_doc_pool[l] -= ebul_ch4;

			   ebul_ch4 = 0.0;//EBF * (ch4[l] - saturated_CH4);//ch4[l] * Ff * temp[1]/40.0;//0.0025
			   ch4[l] -= ebul_ch4;

			   CCH4 = ebul_ch4;
		   }
		   else*/
		   {
			   if(ch4[l]<=saturated_CH4)//||clay[1]>0.5)
			   {
 					CCH4 = 0.0;
			   }
			   else
			   {					  
				 CCH4 = EBF * ch4[l];//0.5 //kg C/m3 water
				 ch4[l] -= CCH4; //kg C/m3 water
				 if(ch4[l]<0.0) ch4[l] = 0.0;
			   }
		   }
	   }		
	   ch4_eb += CCH4;
	   
   }//end layer loop
	 
   //total daily CH4 flux
   if(GN<=q)
   {
	   *day_ch4 += (ch4_eb + *plant_day_ch4);
	   	
		//flux_co2 = 0.0;
   }
   else
   {
#ifdef MANURE
	   if(GN==q+1)//barn floor 
	   {
			MData.day_house_ch4 += (ch4_eb+ch4[GN]);
			*day_ch4 += (ch4_eb+ch4[GN]);
			MData.day_house_co2 += co2[GN];
			co2[GN] = 0.0;
	   }
	   
	   if(GN==q+8)//barn gutter
	   {
			MData.day_gutter_ch4 += (ch4_eb+ch4[GN]);
			*day_ch4 += (ch4_eb+ch4[GN]);
			MData.day_gutter_co2 += co2[GN];
			co2[GN] = 0.0;
	   }

		ch4[GN] = 0.0;
		//flux_co2 = 0.0;
#endif
   }


	return(0);
}



void class_model::riceland_ch4_oxidation()
{
    float ch4up, soil_T;
	
    if (temp[1] < 0.0) soil_T = 0.0;
    else soil_T = temp[1]; //temp[1] + (42.735*PGI*PGI*PGI - 71.678*PGI*PGI + 24.293*PGI - 0.2657);
    
	ch4up = 0.01 * soil_T * (36.26 * (float)log(wrcvl + wrcl + wrcr + wcrb + wcrhl + wcrhr + whumus) / 2.3026 - 162.57) / 28.0 * MicrobioIndex;//0.0025

	ch4up *= (0.5 * (1.0 - day_wfps[1]));//Donna 

    if (ch4up < 0.0) ch4up = 0.0;

	ch4_day_oxid = ch4up;
	day_ch4 = -ch4up;
	co2[1] += ch4up;

	for(int i=1; i<=q; i++)
	{
		float OCH4 = 0.05 * (0.65 - clay[i]);//0.05
		OCH4 = min(1.0, max(0.0, OCH4));

		if(ch4[i] > 0.0)
		{
 			float dOX = ch4[i] * OCH4;
			day_ch4 += dOX;
			ch4[i] -= dOX;
		  	co2[i] += ch4[i];// * (1.0 - OCH4);			
			ch4_day_oxid += ch4[i];
			ch4[i] = 0.0;
		}
		
		/*if(ch4_doc_pool[i]>0.0)
		{
			float dOY = ch4_doc_pool[i];// * OCH4;
			co2[i] += dOY;
			ch4_doc_pool[i] = 0.0;
		}*/
	}
    
	surf_w=0.0;
}

void class_model::dryland_ch4_oxidation()
{
    float ch4up, soil_T;

	if (temp[1] < 0.0) soil_T = 0.0;
    else soil_T = temp[1]; //temp[1] + (42.735*PGI*PGI*PGI - 71.678*PGI*PGI + 24.293*PGI - 0.2657);

	ch4up = 0.001 * soil_T * (36.26 * (float)log(wrcvl + wrcl + wrcr + wcrb + wcrhl + wcrhr + whumus + 0.000001) / 2.3026 - 162.57) / 28.0 * MicrobioIndex;

	ch4up *= (0.5 * (1.0 - day_wfps[1]));//Donna 

    if (ch4up < 0.0) ch4up = 0.0;

	ch4_day_oxid = ch4up;
	day_ch4 = -ch4up;
	co2[1] += ch4up;
	    
	for(int i=1; i<=q; i++)
	{
		float OCH4 = 0.5;//0.95;
		OCH4 = min(1.0, max(0.0, OCH4));

		if(ch4[i] > 0.0)
		{
			float dOX = ch4[i] * OCH4;			
			ch4[i] -= dOX;
		  	day_ch4 += dOX * 0.06;
			co2[i] += dOX * 0.94;
			ch4_day_oxid += dOX * 0.94;
		}
		
		/*if(ch4_doc_pool[i]>0.0)
		{
			float dOY = doc[i] * OCH4;
			doc[i] -= dOY;
			co2[i] += dOY;
			ch4_doc_pool[i] -= dOY;
			if(ch4_doc_pool[i]<0.0) ch4_doc_pool[i] = 0.0;
		}*/
	}

	surf_w=0.0;
}