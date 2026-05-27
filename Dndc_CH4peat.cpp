#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;
#endif

float class_model::CH4_peat(int MODE, int GN, float *temp, float *clay, int flood_num, int FloDays, float *Root_Wt,
							  int q, float *Eh, float *sph, float *vascularity, int LandUse, float *day_rco2,
							  float *R_Wt, float *day_co2, float root_dCO2, int flood_flag, float *rcvl,
							  float *rcl, float *rcr, int *st, float rcnrvl, float rcnrl, float rcnrr,
							  float MicrobioIndex, float *ch4, int WTL, float day_WT,
							  float *soil_ph, float *doc, float *nh4, float *ch4_prod, float *ch4_day_oxid,
							  float *plant_day_ch4, float *day_wfps, int *seed, float *day_ch4, float *anvf,
							  float WaterLeakRate, float *h, float *CRB1, float rcnb, float *co2)
{
	int l;
	float F_temp, CH4_P1, CH4_P3, CH4_P2, CH4_O;
	float ch4_balloon=0.0, InputRoot_DOC[300]={0.0,0.0}, C_soil[300]={0.0,0.0};
	float soil_CO2=0.0, root_CO2=0.0;
	float acetate_mol[300]={0.0,0.0}, H2_mol[300]={0.0,0.0}, CO2_mol[300]={0.0,0.0}, DOC_mol[300]={0.0,0.0};
	float CH4_mol[300]={0.0,0.0};
	float d_acetate_mol=0.0, d_acetate_cons_mol=0.0, d_H2_mol=0.0, d_CO2_mol=0.0, d_CH4h_mol=0.0, d_CH4a_mol=0.0;
	float ad_DOC_mol=0.0, ch4_max_30;
	float Q10CH4 = 2.0, ch4_max=0.0;	

	ch4_max_30 = 0.01;// (kmol C/ha/day/layer)

#ifdef ISOTOPE // Define constant factors	
	
	float pCH4mc_12, pCH4mc_13;// 12C and 13C in CO2-converted CH4, kg C/ha
	float pCH4md_12, pCH4md_13;// 12C and 13C in acetate-converted CH4, kg C/ha
	float fCH4ep_12, fCH4ep_13;// 12C and 13C in CH4 emitted through plant, kg C/ha/day
	float fCH4eb_12, fCH4eb_13;// 12C and 13C in CH4 emitted through ibulation, kg C/ha/day
	float fCH4ed_12, fCH4ed_13;// 12C and 13C in CH4 emitted through diffusion, kg C/ha/day
	float fCO2_12, fCO2_13;// 12C and 13C in CO2 from CH4 oxidation, kg C/ha/day

	float PDB = 0.0112372;// Standard d13C
	float alf_CO2_CH4 = 1.095;//alfa from CO2 to CH4:1.080 [Conrad 2005: 1.045-1.082]
	float alf_DOC_CH4 = 1.026;//alfa from acetate to CH4:1.040 [Conrad 2005: 1.000-1.032]
	float alf_CH4ep = 1.016;//alfa for CH4 transport by plant
	float alf_CH4eb = 1.0;//alfa for CH4 transport by ibulation
	float alf_CH4ed = 1.001;//alfa for CH4 transport by diffusion
	float alf_CH4_CO2 = 1.025;//alfa from CH4 to CO2
	del13C_CO2 = -0.026;//initial d13C of peat_CO2
	del13C_DOC = -0.026;//initial d13C of peat_acetate

#endif	
 
	CH4_P1=0.0;
	CH4_P2=0.0;
	CH4_P3=0.0;
	
	float TotalRootWT = Root_Wt[1]+Root_Wt[2]+Root_Wt[3];	 
	float TotalVas = max(vascularity[1], max(vascularity[2],vascularity[3]));	 
	
	for (l=1; l<=q; l++)
	{
		//Define Eh & balloon profile
		if(l>=WTL)//layer is saturated  
		{
			Eh[l] = -65.0 * (float)l + 25.0;
			if(Eh[l]<-250.0) Eh[l] = -250.0;
			
			ch4_balloon = -0.0018 * Eh[l] + 0.5651;
			ch4_balloon = min(1.0, max(0.1, ch4_balloon));    
		}
		else 
		{
			Eh[l] = 100.0;
			ch4_balloon = 0.1;
		}

		//Define temperature profile and temperature factor
		//Arrhenius equation (ref. Ding & Wang,1996): CH4 production rate is a first order of temperature	
		
		if(temp[l]<=0.0) F_temp = 0.0;
		else if(temp[l]<=10.0) F_temp = 0.1 * temp[l];
		else F_temp = (float)powf(Q10CH4, temp[l]/10.0);

		F_temp = max(0.0, F_temp);
		
		//Define C sources 	
		//--- DOC from root exudation
		if (TotalRootWT>0.0)
		{
			InputRoot_DOC[l] = 0.00010 * Day_C_growth[1] / (1.0 + PGI[1]) * TotalRootWT / (float)q;//0.00015

			doc[l] += InputRoot_DOC[l];

			day_RootInput_DOC += InputRoot_DOC[l];
		}
		else
		{
		    InputRoot_DOC[l] = 0.0;
		}     
		
		//--- DOC from fermentation of plant residue
		if(ch4_balloon>=0.0)
		{ 
			float LitterC1=0.0, LitterC2=0.0, LitterC3=0.0, HumadsC1=0.0, HumadsC2=0.0;			

/*			if(rcvl[l]>0.0) 
			{
				LitterC1 = rcvl[l] * F_temp * 0.00025;//kg C/ha
				rcvl[l] -= LitterC1;
				nh4[l] += (LitterC1 / rcnrvl);	
				doc[l] += LitterC1;
				soil_CO2 += LitterC1;
			}

			if(rcl[l]>0.0) 
			{
				LitterC2 = rcl[l] * F_temp * 0.0005;
				rcl[l] -= LitterC2;
				nh4[l] += (LitterC2 / rcnrl);
				doc[l] += LitterC2;
				soil_CO2 += LitterC2;
			}
			
			if(rcr[l]>0.0) 
			{
				LitterC3 = rcr[l] * F_temp * 0.000025;
				rcr[l] -= LitterC3;
				nh4[l] += (LitterC3 / rcnrr);
				doc[l] += LitterC3;
				soil_CO2 += LitterC3;
			}
*/
			/*float dFDC1=0.0, dFDC2=0.0, dFDC3=0.0;
			if(l==1&&flood_flag==1 && (stub1+stub2+stub3)>0.0)
			{
				float DD = 0.1 * F_temp;//0.001
				float dFDC,  dLN;
				DD=min(1.0, max(0.0, DD));

				dFDC1 = stub1 * DD;
				stub1 -= dFDC1;
				nh4[l] += (dFDC1 / rcnrvl);

				dFDC2 = stub2 * DD * 0.1;
				stub2 -= dFDC2;
				nh4[l] += (dFDC2 / rcnrl);

				dFDC3 = stub3 * DD * 0.05;
				stub3 -= dFDC3;
				nh4[l] += (dFDC3 / rcnrr);

				//InputSoil_DOC += (dFDC1 + dFDC2 + dFDC3);

				doc[l] += (dFDC1 + dFDC2 + dFDC3);
			}*/
		}

		day_Root_DOC += InputRoot_DOC[l];
		InputRoot_DOC[l] = 0.0;
		
		//CO2 sources
		//CO2 from root respiration
		if(TotalRootWT>0.0)
		{
			root_CO2 = 0.000001 * Day_C_growth[1] / (1.0 + PGI[1]) * TotalRootWT / (float)q;
			co2[l] += root_CO2;
		}
		else
		{
			root_CO2 = 0.0;
		}

		//Convert soil DOC, CO2, acetate, H2 and CH4 pools from kg/ha to kmol/ha
		DOC_mol[l] = doc[l] / 12.0;
		CO2_mol[l] = co2[l] / 12.0;
		acetate_mol[l] = acetate[l] / 12.0;
		H2_mol[l] = H2[l] / 2.0;
		CH4_mol[l] = ch4[l] / 12.0;

		
		
		//Anaerobic decomposition (fermentation + syntrophy)
		float VmaxDOC = 100.0 * DOC_mol[l] * F_temp;//??? maximum decomposition rate of DOC, kmol/ha/day
		float Kdoc = 10.0;//??? DOC concentration at half of maximum decomposition rate of DOC. kmol/ha
		
		ad_DOC_mol = VmaxDOC * DOC_mol[l] / (Kdoc + DOC_mol[l]);//Rate of decomposition of DOC. kmol/ha
				
		d_acetate_mol = 2.0 * ad_DOC_mol;//Rate of production of acetate. kmol C/ha
		d_H2_mol = 4.0 * ad_DOC_mol;//Rate of production of H2. kmol H2/ha
		d_CO2_mol = 2.0 * ad_DOC_mol;//Rate of production of H2. kmol CO2/ha

		//Update DOC, acetate, H2 and CO2 pools available for methanogenesis
		DOC_mol[l] -= ad_DOC_mol;
		acetate_mol[l] += d_acetate_mol;
		H2_mol[l] += d_H2_mol;
		CO2_mol[l] += d_CO2_mol;

		//Hydrogenotrophic methanogenesis
		if(H2_mol[l]>0.0&&CO2_mol[l]>0.0)
		{
			float VmaxCH4h = ch4_max_30 * F_temp * ch4_balloon;//Maximum production rate of CH4 from hydrogenotrophic methanogenesis, kmol/ha
			float KH2 = 0.001;//H2 concentration at half of maximum hydrogenotrophic CH4 production rate, kmol/ha
			float KCO2 = 1.0;//CO2 concentration at half of maximum hydrogenotrophic CH4 production rate, kmol/ha 

			d_CH4h_mol = VmaxCH4h * H2_mol[l]/(KH2 + H2_mol[l]) * CO2_mol[l]/(KCO2 + CO2_mol[l]);
			
			d_H2_mol = 4.0 * d_CH4h_mol;//H2 comsumption
			d_CO2_mol = d_CH4h_mol;//CO2 comsumption

			//Update H2, CO2 and CH4 pools for methanogenesis
			H2_mol[l] -= d_H2_mol;
			CO2_mol[l] -= d_CO2_mol;
			CH4_mol[l] += d_CH4h_mol;
		}
		else
		{
			d_CH4h_mol = 0.0;
		}

		//Acetotrophic methanogenesis	
		if(acetate_mol[l]>0.0)
		{
			float VmaxCH4a = 100.0 * ch4_max_30 * F_temp * ch4_balloon;//Maximum production rate of CH4 from acetotrophic methanogenesis, kmol/ha
			float Kacetate = 1.0; //Acetate concentration at half of maximum acetotrophic CH4 production rate, kmol/ha 
	
			d_CH4a_mol = VmaxCH4a * acetate_mol[l]/(Kacetate + acetate_mol[l]);	//CH4 production in 1cetotrophic methanogenesis, kmol/ha/day
			
			d_acetate_cons_mol = d_CH4a_mol;//Acetate consumption in acetotrophic methanogenesis, kmol/ha
			d_CO2_mol = d_CH4a_mol;//CO2 production from acetotrophic methanogenesis, kmol/ha

			//Update acetate, CO2 and CH4 pools for methanogenesis
			acetate_mol[l] -= d_acetate_cons_mol;
			CO2_mol[l] += d_CO2_mol;
			CH4_mol[l] += d_CH4a_mol;
		}
		else
		{
			d_CH4a_mol = 0.0;
		}

		//Convert soil DOC, CO2, acetate, H2 and CH4 pools from kmol/ha to kg/ha
		doc[l] = DOC_mol[l] * 12.0;
		co2[l] = CO2_mol[l] * 12.0;
		acetate[l] = acetate_mol[l] * 12.0;
		H2[l] = H2_mol[l] * 2.0;
		ch4[l] = CH4_mol[l] * 12.0;

		if(doc[l]<0.0) doc[l] = 0.0;
		if(co2[l]<0.0) co2[l] = 0.0;
		if(acetate[l]<0.0) acetate[l] = 0.0;
		if(H2[l]<0.0) H2[l] = 0.0;
		if(ch4[l]<0.0) ch4[l] = 0.0;

		CH4_P1 = d_CH4h_mol * 12.0;//CH4 production from hydrogenotrophic methanogenesisi, kg CH4-C/ha/day/layer
		CH4_P2 = d_CH4a_mol * 12.0;//CH4 production from acetatotrophic methanogenesisi, kg CH4-C/ha/day/layer

#ifdef ISOTOPE
		if(CH4_P1>0.0)
		{
				CO2_12[l] = co2[l] / ((1.0 + del13C_CO2) * PDB + 1);// = CO2(n) * 0.9891734;
				CO2_13[l] = co2[l] - CO2_12[l];

				day_CO2_13 += CO2_13[l];
				day_CO2_12 += CO2_12[l];				

				pCH4mc_12 = CH4_P1 / ((CO2_13[l] / CO2_12[l]) / alf_CO2_CH4 + 1.0);
				pCH4mc_13 = CH4_P1 - pCH4mc_12;

				CH4_13[l] += pCH4mc_13;
				CH4_12[l] += pCH4mc_12;
				day_prod_CH4_13 += pCH4mc_13;
				day_prod_CH4_12 += pCH4mc_12;
				CO2_13[l] -= pCH4mc_13;
				CO2_12[l] -= pCH4mc_12;
				pCH4mc_13 = 0.0;
				pCH4mc_12 = 0.0;				
		}
		else
		{
				CO2_12[l] = 0.0;
				CO2_13[l] = 0.0;
				pCH4mc_12 = 0.0;
				pCH4mc_13 = 0.0;
		}

		if(CH4_P2>0.0)
		{
				DOC_12[l] = doc[l] / ((1.0 + del13C_DOC) * PDB + 1);
				DOC_13[l] = doc[l] - DOC_12[l];
				day_DOC_13 += DOC_13[l];
				day_DOC_12 += DOC_12[l];

				pCH4md_12 = CH4_P2 / ((DOC_13[l] / DOC_12[l]) / alf_DOC_CH4 + 1.0);
				pCH4md_13 = CH4_P2 - pCH4md_12;

				day_prod_CH4_13 += pCH4md_13;
				day_prod_CH4_12 += pCH4md_12;

				CH4_13[l] += pCH4md_13;
				CH4_12[l] += pCH4md_12;	
				
				day_CH4_13 += CH4_13[l];
				day_CH4_12 += CH4_12[l];
				
				//DOC_13[l] -= pCH4md_13;
				//DOC_12[l] -= pCH4md_12;
				delCH4[l] = (CH4_13[l] / CH4_12[l]) / PDB - 1.0;
		}
		else
		{
				DOC_12[l] = 0.0;
				DOC_13[l] = 0.0;
				pCH4md_13 = 0.0;
				pCH4md_12 = 0.0;
			}
#endif

		//Summary
		day_CO2_prod += (root_CO2 + soil_CO2);
		day_Root_CO2 += root_CO2;
		day_SOM_CO2 += soil_CO2;
		day_ch4_CO2[l] += (root_CO2 + soil_CO2);
		root_CO2 = 0.0;
		soil_CO2 = 0.0;

		*ch4_prod += CH4_P1; // daily ch4 production, kg CH4-C/ha/d
		ch4_prod1 += CH4_P1;
		day_ch4_1[l] = CH4_P1;
		day_ch4_pool += CH4_P1;

		ch4_prod2 += CH4_P2;
		day_ch4_2[l] = CH4_P2;
		day_ch4_pool += CH4_P2;
		*ch4_prod += CH4_P2;	
		
		day_acetate_prod += d_acetate_mol * 12.0;
		day_acetate_cons += d_acetate_cons_mol * 12.0;

		CH4_P1 = 0.0;	
		CH4_P2 = 0.0;	
			

		

/*
		//H2[l] = 1.0 * (peat_CO2[l] * 2.0/72.0);
		H2[l] = 1.0 * (co2[l] * 2.0/72.0);

		day_H2_PROD += H2[l];
		day_SOM_H2 += H2[l];
		day_H2_pool[l] += H2[l];
*/	

			//CO2 and H2 are produced from anaerobic decomposition of soil DOC:
			// C6H12O6 -> CH3COOH + CH3CH2COOH + CO2 + H2

/*			float ch4_max_30 = 5.0E-5 * 1.0E-6 * 12.01 * 3600.0 * 24.0 * mmm[l];//! (kgC/ha/day per layer)
			float ch4_max;
			float Q10CH4 = 4.6;

			if (temp[l] <= 0.0) ch4_max = 0.0;
		     else if (temp[l] < 40.0) ch4_max = ch4_max_30 * pow(Q10CH4, (temp[l] - 0.0)/10.0); //!
			 else ch4_max = ch4_max_30 * Q10CH4 ;//! fixed Vmax over 40C

			 float ch4_max_h2 = ch4_max * 0.5;//! Vmax of CH4 production from H2
			 float ch4_max_doc = ch4_max * 0.5;//! Vmax of CH4 production from DOC
*/

/*			if(root[1]>0.15) //sedge
			{
				C_soil[l] = TotalDOC[l];
				co2[l] = 0.0;
				H2[l] = 0.0;
				TotalDOC[l] = 0.0;
			}
			else// moss
			{
				co2[l] = 5.0 * TotalDOC[l];
				C_soil[l] = 0.0;
				H2[l] = 5.0 * (co2[l] * 2.0/72.0);
				TotalDOC[l] = 0.0;
			}
*/
/*			float Rcc = max(0.4, min(0.6, ch4_balloon));//5.0/6.0;
			float Rhh = 2.0/72.0;//by weight

			C_soil[l] = (TotalDOC[l] * Rcc);					
			co2[l] += (TotalDOC[l] * (1.0 - Rcc));
			
			//H2[l] += (TotalDOC[l] * Rhh);
			//day_H2_prod[l] += (TotalDOC[l] * Rhh);//kg H/ha
			float PHR = 1.0;
			if(root[1]<=0.15) PHR = 5.0 * PGI[1]; 

			H2[l] += (PHR * (C_soil[l] * Rhh));
			day_H2_prod[l] += (C_soil[l] * Rhh);//kg H/ha

			TotalDOC[l] = 0.0;
*/				 
/*			/////////Refer to Fumoto's routines//////////////////////////
			 
			 //--- kinetic parameters and variables for CH4 production ------------------------------
			 float ch4_max_30, Q10CH4, ch4_max, ch4_max_h2, ch4_max_doc, km_h2, km_doc;//, K1_DOC;
			 float H2_conc, avail_h2, doc_conc, dAcetate;
			 
			 // saturated H2 conc. in water at 25C, from Henry const. (Atkins 1998, Physical Chemistry 6th ed., Oxford U. Press)
			 float saturate_h2 = 0.78E-3; //! (mol H2 /L)
			 float V_water = day_wfps[l] * h[l] * 10000.0 * 1000.0;//liter water/ha in layer l
			 saturate_h2 = saturate_h2 * 2.0 * V_water / 1000.0; // kg H/ha/layer

			 // Max. CH4 production rate at 30C. 2.0E-5 (mmol/L/s) or 5.0E-5 (mmol/kg soil/s) (Van Bodegom and Scholten, 2001) 
			 ch4_max_30 = 5.0E-5 * 1.0E-6 * 12.01 * 3600.0 * 24.0 * mmm[l];//! (kgC/ha/day per layer)
			 //ch4_max_30 = 2.0E-5 *1.0E-6 *12.01 *3600.0 * soil_water;//! (kgC/ha/h) <--- looks too low

			 Q10CH4 = 4.6;//! Q10 for CH4 production (van Bodegom and Stams,1999, Chemosphere 39:167-182)

			 if (temp[l] <= 0.0) ch4_max = 0.0;
		     else if (temp[l] < 40.0) ch4_max = ch4_max_30 * powf(Q10CH4, (temp[l] - 20.0)/10.0); //30.0
			 else ch4_max = ch4_max_30 * Q10CH4 ;//! fixed Vmax over 40C

			 ch4_max_h2 = ch4_max * 0.5;//! Vmax of CH4 production from H2
			 ch4_max_doc = ch4_max * 0.5;//! Vmax of CH4 production from DOC

			 km_h2 = 13.3E-6 * 2.0 * V_water / 1000.0;//!  Km for H2 (mol H2/L -> kg H/ha/layer) (Van Bodegom and Scholten, 2001)
		//	 km_h2 = 13.3E-4;//! 
			 km_doc = 5.12E-3 * 12.0 * V_water / 1000.0;//! Km for acetate (mol DOC /L -> kg C/ha/layer) (Van Bodegom and Scholten, 2001)

			// K1_DOC = 0.286;//! virtual 1st-order rate constant at 30C (/d) (Van Bodegom and Scholten, 2001; Bodegom and Stams, 1999) 
		//	 K1_DOC = 0.5;//! theoretical maximum
		
			//----- available H2 
			//H2_conc = min(saturate_h2, hour_h2 / n * m /soil_water); //! (mol H2/L)
			H2_conc = min(saturate_h2, H2[l]); //! (kg H/ha/layer)
			avail_h2 = H2_conc;// kg H/ha/layer /1000.0 * water[1][l];//! (kmol H2/ha)

			//----- CH4 production from H2 and CO2 
			//if(peat_CO2[l]>0.0)
			if(co2[l]>0.0)
			{
				day_ch4_CO2[l] = 0.5 * co2[l];

				CH4_P1 = ch4_max_h2 * H2_conc/(km_h2 + H2_conc); //! (kgC/ha) 
				//pro_ch41 = ch4_max_h2;//! CH4 production with high affinity to H2 (kgC/ha)

				if (CH4_P1 > day_ch4_CO2[l]) CH4_P1 = day_ch4_CO2[l];//! limit by CO2, kg C/ha/layer
				if (CH4_P1/12.01*4.0 > avail_h2) CH4_P1 = avail_h2 /4.0*12.01;//! limit by H2 
				
				H2[l] -= CH4_P1 /12.01 * 4.0;//! H2 after CH4 production (kg H/ha/layer)

				day_H2_pool[l] -= CH4_P1 /12.01 * 4.0;
*/			
/*#ifdef ISOTOPE
				CO2_12[l] = CH4_P1 /((1.0 + del13C_CO2) * PDB + 1);// = CO2(n) * 0.9891734;
				CO2_13[l] = CH4_P1 - CO2_12[l];

				day_CO2_13 += CO2_13[l];
				day_CO2_12 += CO2_12[l];				

				pCH4mc_12 = CH4_P1 / ((CO2_13[l] / CO2_12[l]) / alf_CO2_CH4 + 1.0);
				pCH4mc_13 = CH4_P1 - pCH4mc_12;

				CH4_13[l] += pCH4mc_13;
				CH4_12[l] += pCH4mc_12;
				day_prod_CH4_13 += pCH4mc_13;
				day_prod_CH4_12 += pCH4mc_12;
				CO2_13[l] -= pCH4mc_13;
				CO2_12[l] -= pCH4mc_12;
				pCH4mc_13 = 0.0;
				pCH4mc_12 = 0.0;
#endif
				
			}
			else
			{
				CH4_P1 = 0.0;
#ifdef ISOTOPE
				CO2_12[l] = 0.0;
				CO2_13[l] = 0.0;

				pCH4mc_12 = 0.0;
				pCH4mc_13 = 0.0;
#endif
			}
*/
/*			ch4[l] += CH4_P1;//kg C/ha/layer
			*ch4_prod += CH4_P1; // daily ch4 production (kg CH4-C/ha/d)
			ch4_prod1 += CH4_P1;
			day_ch4_1[l] = CH4_P1;
			co2[l] -= CH4_P1; //! CO2 after CH4 production (kgC/ha/layer)
			day_ch4_pool += CH4_P1;
			day_ch4_CO2[l] -= CH4_P1;
*/
		
			//----- CH4 production from DOC (acetate) 
			
/*			//if(peat_DOC[l]>0.0)
			if(doc[l]>0.0)
			{
				//dAcetate = ch4_max_doc * peat_DOC[l]/(km_doc + peat_DOC[l]); //consumption of acetate, kg C/ha/layer// ! (kg CH4-C/ha)
			 
				dAcetate = ch4_max_doc * doc[l]/(km_doc + doc[l]); //consumption of acetate, kg C/ha/layer// ! (kg CH4-C/ha)

				if (dAcetate > doc[l]) dAcetate = doc[l];//! limit by DOC
				if ((dAcetate * 0.5) > (ch4_max - CH4_P1)) dAcetate = (ch4_max - CH4_P1) * 2.0;//! 

				CH4_P2 = dAcetate;

				//InputRoot_DOC[l] -= (dAcetate * InputRoot_DOC[l] / Totdoc);
								
				//CH4_P2 = dAcetate * 0.75;//! CH4 production, kg C/ha/layer
				//co2[l] += dAcetate * 0.25;//! CO2 after CH4 production (CH3COOH ---> CH4 + CO2), kg C/ha/layer 				

#ifdef ISOTOPE
				DOC_12[l] = doc[l] / ((1.0 + del13C_DOC) * PDB + 1);//peat_DOC
				DOC_13[l] = doc[l] - DOC_12[l];
				day_DOC_13 += DOC_13[l];
				day_DOC_12 += DOC_12[l];

				pCH4md_12 = CH4_P2 / ((DOC_13[l] / DOC_12[l]) / alf_DOC_CH4 + 1.0);
				pCH4md_13 = CH4_P2 - pCH4md_12;

				day_prod_CH4_13 += pCH4md_13;
				day_prod_CH4_12 += pCH4md_12;

				CH4_13[l] += pCH4md_13;
				CH4_12[l] += pCH4md_12;	
				
				day_CH4_13 += CH4_13[l];
				day_CH4_12 += CH4_12[l];
				
				//DOC_13[l] -= pCH4md_13;
				//DOC_12[l] -= pCH4md_12;
				delCH4[l] = (CH4_13[l] / CH4_12[l]) / PDB - 1.0;
#endif	
			
			}
			else
			{
				CH4_P2 = 0.0;
				//ch4_doc_pool[l] = 0.0;
#ifdef ISOTOPE
				DOC_12[l] = 0.0;
				DOC_13[l] = 0.0;
				pCH4md_13 = 0.0;
				pCH4md_12 = 0.0;
#endif
			}	
*/			
/*			doc[l] -= CH4_P2;//peat_DOC
			//doc[l] -= CH4_P2;//ch4_doc_pool
			if(doc[l]<0.0) doc[l] = 0.0;

			doc[l] -= CH4_P2;
			if(doc[l]<0.0) doc[l] = 0.0;

			ch4_prod2 += CH4_P2;
			day_ch4_2[l] = CH4_P2;
			day_ch4_pool += CH4_P2;
			ch4[l] += CH4_P2;//kg C/ha/layer
			*ch4_prod += CH4_P2; // daily ch4 production (kg CH4-C/ha/d)			

			//----- CH4 production on the day 
			CH4_P1 = 0.0;	
			CH4_P2 = 0.0;			
			/////////End of Fumoto's routines////////////////////
*/			 
			 
			 
			/* if(nh4[l] >= InputRoot_DOC[l] / rcnb)
			 {
				CRB1[l] += InputRoot_DOC[l];
				nh4[l] -= (InputRoot_DOC[l] / rcnb);
				InputRoot_DOC[l] = 0.0;
			 }
			 else
			 {
				CRB1[l] += nh4[l] * rcnb;
				InputRoot_DOC[l] -= nh4[l] * rcnb;
				NH4[l] = 0.0;
			 }*/
			 		 
			 //InputRoot_DOC[l] = 0.0;
			 

		//}//end of if(ch4_balloon>=0.5)
	}//end of layer loop

	//// CH4 transport ////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ISOTOPE	
		fCH4ep_13 = 0.0;
		fCH4ep_12 = 0.0;
		fCH4eb_13 = 0.0;
		fCH4eb_12 = 0.0;
		fCH4ed_13 = 0.0;
		fCH4ed_12 = 0.0;
#endif

		for (l=1; l<=q; l++)
		{
			//plant trnsport
			if(ch4[l]>0.0&&Leaf_Wt[1]>0.0&&PGI[1]<1.0&&air_temp>0.0) //TotalVas>0.0&&
			{		
				float TFT=0;
				
				if(PGI[1]<0.5) TFT = 5.0 * PGI[1] * F_temp;//Leaf_Wt[1] / 2000.0 *TotalVas * 
				else TFT = 5.0 * (1.0 - PGI[1]*1.6) * F_temp;//Leaf_Wt[1] / 2000.0 *TotalVas * 
				
				TFT = min(1.0, max(0.0, TFT));

				float dPF = TFT * ch4[l];// 0.2,;
				//float dPFC = 1.0 * co2[l] * TotalVas;

				*day_ch4 += dPF;
				//day_co2 += dPFC;
				ch4[l] -= dPF;
				//co2[l] -= dPFC;
#ifdef ISOTOPE
				if(CH4_12[l]>0.0&&CH4_13[l]>0.0)
				{
					float qw = dPF / (1.0 + (alf_CH4ep * CH4_12[l] / CH4_13[l]));
					fCH4ep_13 += qw;
					fCH4ep_12 += (dPF - qw);

					CH4_13[l] -= qw;
					CH4_12[l] -= (dPF - qw);
					
					CH4_13[l] = max(0.0, CH4_13[l]);
					CH4_12[l] = max(0.0, CH4_12[l]);
				}
				
#endif
			}
			
			
			//ebullition
			if(ch4[l]>0.0)
			{
				//float Ttt = temp[1];
				//if(Ttt < 0.0) Ttt = 0.0;
				float ebul_ch4 = 1.0 * ch4[l] * (float) powf(F_temp, 2.0) * PGI[1];//Ttt/40.0 *
				ch4[l] -= ebul_ch4;
				*day_ch4 += ebul_ch4;
#ifdef ISOTOPE

				if(CH4_12[l]>0.0&&CH4_13[l]>0.0)
				{
					float qw = ebul_ch4 / (1.0 + (alf_CH4eb * CH4_12[l] / CH4_13[l]));
					fCH4eb_13 += qw;
					fCH4eb_12 += (ebul_ch4 - qw);

					CH4_13[l] -= qw;
					CH4_12[l] -= (ebul_ch4 - qw);

					CH4_13[l] = max(0.0, CH4_13[l]);
					CH4_12[l] = max(0.0, CH4_12[l]);
				}
#endif
			}

			//diffusion
			if(ch4[l]>0.0)
			{
				float dDF, TFT;

				TFT = max(0.0, air_temp) / 50.0;

				if(day_WT>0.0) dDF = 0.0001 * ch4[l] / (float)l;// * F_temp; 0.0001					
				else dDF = 0.0 * ch4[l] * TFT;//1.0

				//if(total_ice>0.0) dDF *= 0.01;
				
				*day_ch4 += dDF;					
				ch4[l] -= dDF;
								
#ifdef ISOTOPE
				if(CH4_12[l]>0.0&&CH4_13[l]>0.0)
				{
					float qw = dDF / (1.0 + (alf_CH4ed * CH4_12[l] / CH4_13[l]));
					fCH4ed_13 += qw;
					fCH4ed_12 += (dDF - qw);

					CH4_13[l] -= qw;
					CH4_12[l] -= (dDF - qw);

					CH4_13[l] = max(0.0, CH4_13[l]);
					CH4_12[l] = max(0.0, CH4_12[l]);
				}

#endif
			}

		}//end of layer loop
	
#ifdef ISOTOPE			
		fCH4_13 = fCH4ep_13 + fCH4eb_13 + fCH4ed_13;
		fCH4_12 = fCH4ep_12 + fCH4eb_12 + fCH4ed_12;
		if(fCH4_12==0.0) del_fCH4 = -0.075;//0.0;
		else
			del_fCH4 = (fCH4_13 / fCH4_12) / PDB - 1.0;

	///// CH4 oxidation //////////////////////////////////////////////////////////////////////////////////////

	fCO2_13 = 0.0;
	fCO2_12 = 0.0;
#endif

	for (l=1; l<=q; l++)
	{
		if(ch4[l]>0.0)
		{
			if(TotalVas>0.0)
			{
				//if(ch4_balloon>0.1) CH4_O = ch4[l] * 0.6;//0.2
				//else CH4_O = ch4[l] * 0.6;
				CH4_O = ch4[l] * 0.1;
			}
			else
			{
				if(l>=WTL)//lower than WT
					CH4_O = ch4[l]*0.2;//0.05
				else
					CH4_O = ch4[l];// * 0.05; //(1.0 - ch4_balloon);

				//if(ch4_balloon>0.1) CH4_O = ch4[l] * 0.005;
				//else CH4_O = ch4[l] * 0.05;
			}

			day_ch4_3[l] = CH4_O;
			ch4[l] -= CH4_O;
			*ch4_day_oxid += CH4_O;//daily oxidation rate (kg CH4-C/ha/d)
			co2[l] += CH4_O;
			//co2[l] += CH4_O;
			day_ch4_pool -= CH4_O;
			day_ch4_CO2[l] += CH4_O;
			//*day_co2 += peat_CO2[l];
			
#ifdef ISOTOPE
			if(CH4_12[l]>0.0&&CH4_13[l]>0.0)
			{
				float wss = CH4_O / (1.0 + (alf_CH4_CO2 * CH4_12[l] / CH4_13[l]));
				fCO2_13 += wss;
				fCO2_12 += (CH4_O - wss);

				day_oxid_CH4_13 += wss;
				day_oxid_CH4_12 += (CH4_O - wss);

				CH4_13[l] -= wss;
				CH4_12[l] -= (CH4_O - wss);	
				
				day_CH4_13 += CH4_13[l];
				day_CH4_12 += CH4_12[l];

				//delCH4[l] = (CH4_13[l] / CH4_12[l]) / PDB - 1.0;
			}			
#endif
		}	
		
		//*day_co2 += (0.1 * peat_CO2[l]);
		//peat_CO2[l] *= 0.9;
	} 
#ifdef ISOTOPE	
	del_fCO2 = (fCO2_13 / fCO2_12) / PDB - 1.0;
#endif
 
	return(*day_ch4);
}