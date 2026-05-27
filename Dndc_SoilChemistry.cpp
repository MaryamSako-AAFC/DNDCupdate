#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE
extern class_manure MData;
#endif

float ttn, KTT=10.0;

int DDepth_convert_to_layer(float DepthO, float *hh, int q);

void class_model::dndc_decomposition(float* CRB1, float* CRB2, float* newh, float* w_no2, float* w_nh3, 
			float* w_no3, float* w_nh4, float* wurea, float* wpool_no, float till_fact, 
			float* DayFlux, int tilq, FILE*fCB, FILE*fNB, float* w_n2o, float* w_n2,
			int GN, int q, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
			float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
			float *dphum, float *doc, float *nh4, float *no3, float *no2, float *no, float *n2o, 
			float *n2, float *nh3, float *urea, int jday, float *co2, float *clay, float TTT, int flood_flag,
			float *day_wfps, int WTL, float *temp, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, 
			float *ocini, float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim,
			float DClitter, float *litco22, float *litco23, int *st, float DChumads, float EFFAC, 
			float DChumus, float *sph, int wetland_flag, float wind_speed, float *ice, float *day_soil_nh3,
			float *lai, float *PlantTakeN, float *maxmn, float leaf_water, float cropht, float base_nh3,
			float *day_N_demand, float *day_nup, float *day_fixN, float *day_DWater, float *day_plant_nh3, 
			float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
			float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		    float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		    float *EndSON, 
			float day_runoff, float *day_runoff_N, float *day_clay_N, 
			float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, float *ds_doc,
			int *crop, float *yr_fixn, float rainfall, float *soil_ph, float *winertC,
			float *inert_C, int fert_flag, float *root_doc, float *day_O2, float RFM,
			float *SoilDepth, float *ttoo, float *sop, float *OrgP, float *LabP, float *AdsP,
			float *ComP, float *sts, float day_leach_water, float MicrobioIndex, int facility, int manure_flag, float *manco2, float *manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2,
			float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol, int manureCounter)
{
    float  clayc=0.0, krh=0.0, hrh=0.0, DDRF=0.0;
	float drcvl=0.0, DRCB=0.0, DRCB1=0.0, DRCB2=0.0, lit_co2=0.0, sumn=0.0, fb_nh4=0.0, DRCB4=0.0;//DRCB4=new manure microbe pool
	float fb_co2=0.0, fh_nh4=0.0, dcbavai=0.0, fh_co2=0.0;
	*litco22=0.0;
	*litco23=0.0;
	//*manco2 = 0.0;//manureDNDC AugFix Broken!!!
	int LRL = DDepth_convert_to_layer(0.15, h, q);
	
	int    l;
    if ( jday==1 )
    {
		drcvl=(float)0.0;
		DRCB=(float)0.0;
		DRCB1=(float)0.0;
		DRCB2=(float)0.0;
		DRCB4 = (float)0.0;
		lit_co2=(float)0.0;
		sumn=(float)0.0;
		fb_nh4=(float)0.0;
		fb_co2=(float)0.0;
		dcbavai=(float)0.0;
		fh_co2=(float)0.0;
		fh_nh4=(float)0.0;		
		
    }





    clayc = (float)(log(.14 / clay[1]) / 2.3026 + 1);
    krh = (float)0.16 * clayc;//0.16
    hrh = (float)0.006 * clayc;//0.006

	if(krh>1.0) krh=1.0;
	if(hrh>1.0) hrh=1.0;

	int BL, EL;

	if(GN>q)//manure
	{
		BL = GN; EL = GN; 
	}
	else
	{
		BL = 1; EL = q;
	}

    for (l=BL; l<=EL; l++ )
    {

//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
		if(l>q) 
		{
			clay[l] = 0.01;
			soil_ph[l] = sph[l];
		}

		float Fl=1.0;
		
		Fl = 0.6 * powf(l, -0.1366);
		if(Fl>1.3) Fl = 1.3;
		if(Fl<0.0) Fl = 0.0;

		DDRF = (DRF - 0.02 * clay[l]) * Fl; 
		if ( DDRF < 0.0 ) DDRF = 0.0;
		
		float dev_ph, Frain, D_ph;

		Frain = 0.5; //20.0 * rainfall;
		if(flood_flag==0) 
			D_ph = soil_ph[l];
		else 
			D_ph = 7.0;
		
		if(sph[l]!=D_ph)
		{
		   dev_ph = (sph[l] - D_ph) * Frain;
		   sph[l] -= dev_ph;
		}
		
		// Effect of temp/mois on decomposition 

		effect_temp_mois(l, day_wfps, WTL, temp, LandUse, flood_flag, FloDays, &RFM, st, ice, q, MicrobioIndex);

//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		// Redefine daily microbes/humads 
		redefine_microbe(l, RFM, TTT, jday, soc, rcvl, rcl, rcr, CRB1, CRB2, crhl,
				crhr, dphum, mmm, clay, ocini, no2, no3,manurePool);
	    
//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
		// Decomposition of surface litter 
		//if(l==1) decomp_of_litter(l, co2, nh4, h, temp, day_wfps, day_C_mine, day_N_assim, &DRCB, DRCB1, DRCB2, RFM);
		//Decomposition of manure
#ifdef MANURE
#else
		if (manurePool[l] > 0.0)
		{
			manure_decomp(l, RFM, DDRF, till_fact, &DRCB4, tilq, DClitter, manurePool, manurePoolCN, rcnb, nh4,
				no3, co2, CRB1, CRB2, day_C_mine, day_N_mine, day_N_assim, manco2, day_O2, h, flood_flag);
		}
#endif
		// Decomposition of very labile litter 
		if(rcvl[l]>0.0)
		{
			rcvl_decomp(l, &drcvl, RFM, DDRF, till_fact, &DRCB1, tilq,
				DClitter, rcvl, nh4,
				co2, CRB1, CRB2, day_C_mine, day_N_mine, day_N_assim, rcnrvl, rcnb, day_O2, flood_flag);
		}

		// Decomposition of labile litter 
		if(rcl[l]>0.0)
		{
			rcl_decomp(l, RFM, DDRF, till_fact, &DRCB2, tilq, DClitter, rcl, rcnrl, rcnb, nh4,
				no3, co2, CRB1, CRB2, day_C_mine, day_N_mine, day_N_assim, litco22, day_O2, h, flood_flag);
		}
//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
		// Decomposition of resistant litter 
	
		if(rcr[l]>0.0)
		{
			rcr_decomp(l, RFM, DDRF, till_fact, DRCB1, DRCB2,
				&lit_co2, drcvl, CRB1, CRB2, &DRCB, &sumn, tilq, litco22,
				litco23, DClitter, rcr, nh4, co2, day_C_mine, day_N_mine, day_N_assim,
				rcnrvl, rcnb, rcnrr, no3, rcnrl, day_O2, h, q, flood_flag, doc, DRCB4, manco2);
		}

//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		// Life and death of soil microbes 
		decomp_microbes(l, RFM, DDRF, till_fact, CRB1, CRB2,&fb_nh4, &fb_co2, &dcbavai, tilq,
			st, nh4, rcnb, crhr, crhl, co2, day_C_mine, day_N_mine, day_N_assim, DChumads, EFFAC, rcnh,
			doc, q, day_O2);
//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		//if(nh4[l]<0.0) nh4[l]=0.0;
		// Decomposition of humads (this function has error source) 
		decomp_humads(l, RFM, DDRF, till_fact, hrh, krh, &fh_co2,newh, &fh_nh4, CRB1, CRB2, dcbavai,DRCB, tilq,
			clay, DChumads, crhr, crhl, nh4, rcnh, rcnb, co2, doc, temp, day_C_mine, day_N_mine, day_N_assim, 
			st, dphum, rcnm, q, day_O2, OrgP, LabP, ComP, jday);
//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		decomp_humus(l, DDRF, tilq, till_fact, clay, h, DChumus, dphum, nh4, co2, rcnm, 
					day_C_mine, day_N_mine, day_N_assim, day_O2, SoilDepth, temp, RFM, q,
					flood_flag, TTT, day_leach_water, doc);//(this function has error source) 

		
		
//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
		facility = 0;//ManureDNDC fix not sure how to set facility to not run urea_hydrolysis etc
		if(facility==0)
		{
			urea_hydrolysis(l, urea, temp, day_wfps, nh4, sph, h, 0, ttoo, UreaHydroInhibDays, flood_flag, q, manure_flag,UIDay1,UIDay2,mmm,fldcap,wiltpt);
//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
	
		// NH4+/NH3(l) equilibrium in liquid phase 
		//if(l<=q) 
			nh43_equil(l, temp, sph, nh4, nh3, q, h, day_wfps, flood_flag, newmanuPH, combinedpHDeep,manureHour,wind_speed, NH3Vol);

//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
	
		// NH3 volatilization from soil 
		//if(l<=q) 
		
			nh3_volatilization(l, temp, flood_flag, wetland_flag, nh3, q, wind_speed, day_wfps, ice, day_soil_nh3, nh4, jday, no3, manureHour, manureCounter);
//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
		}

		// NH4+ adsorption on clay 
        if(l<=q)
			clay_adsorption(l, RFM, nh4, clay_nh4, base_clay_N, max_clay_N, q, clay);

		//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
	
		//Chemodenitrification
		//if(sph[l]<4.5&&TTT>0.0) Chemodenitrification(1);

		earth_worm(l, RFM, h, rcvl, rcl, rcr);

		// Recover layer lables 
		recover_layer_lables(l, CRB1, CRB2, crhl, crhr, ocini);

		//DOC consumption in soil
		if(l<=q)//&&doc[l]>0.0)
		{
			//float TB = CRB1[l]+CRB2[l];
			//float BAC = temp[l]/(40.0+temp[l]) * TB/(500.0+TB);
			float Ttem=temp[l];
			if(temp[l]<=0.0) Ttem = 0.1;

			float VRmax = Ttem/(40.0+Ttem) * (day_wfps[l]+0.1)/(0.4+day_wfps[l]) * (1.0-clay[l])/(0.5+(1.0-clay[l]));
			
			float BAC = VRmax * doc[l]/(50.0+doc[l]) * O2[l]/(0.00015+O2[l]);//0.0003125 mol/L
			
			BAC = max(0.0, min(1.0, BAC));
			float dDOC = BAC * doc[l];
			day_co2 += dDOC;//Turned on for DOC  
			
			//co2[l] += dDOC;////Turned off for DOC


#ifdef DEBUG_CBALANCE
			day_doc_to_co2 += dDOC;   // how much DOC went to CO2 today
#endif


			doc[l] -= dDOC;
			//H2[l] += 0.28 * dDOC;//0.028
			day_DOC_cons += dDOC;

			//day_O2[l] += dDOC;
			//if(day_O2[l]<0.0) day_O2[l]=0.0;
		}
		else
		{
#ifdef MANURE

//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

			float TB = CRB1[l]+CRB2[l];
			float BAC = 0.0;

			if(l<=q+3) //feedlots
			{				
				BAC = 0.1 * temp[l]/(40.0+temp[l]) * TB/(500.0+TB);
			}
			else if(l<=q+4) //compost
			{
				BAC = temp[l]/(40.0+temp[l]) * TB/(500.0+TB);
			}
			else if(l<=q+5) //lagoon
			{

				/*float Assimilation = 1.0 - powf((float)MData.lagoon_days,1.1) / 365.0;

				Assimilation = min(1.0, max(0.0, Assimilation));

				temp[l] = max(0.0, temp[l]);

				float STL = (float)pow(((float)MData.lagoon_days / 365.0), 4.0);

				BAC = 0.01 * temp[l]/(100.0+temp[l]) * STL * 300.0;//STL;// 10.0, * TB/(100.0+TB),temp[l]/(100.0+temp[l]) * 

				if(crhr[l]>0.0)
				{
					float dHH = (float)MData.lagoon_days/800.0 * crhr[l];
					doc[l] += dHH;
					crhr[l] -= dHH;

					crhr[l] = max(0.0, crhr[l]);

					float difN = dHH / rcnh;
					nh4[l] += difN;

					//if(l<=q) day_DOC_prod += dHH;
				}
				
				//doc[l] -= ddC;*/

				
				if(temp[l]>0.0) 
				{
					float ckk = 1.0; 
					if(MData.lagoon_days<70) ckk = 0.1 + 0.5 * (float)MData.lagoon_days / 70.0;

					//ckk = (float)MData.lagoon_days;
					
					BAC = 0.000025 * (float)powf(temp[l], 2.0) * ckk;//0.00005
				}
				

			}
			
			if(till_fact>1.0) BAC *= 4.0;

			BAC = max(0.0, min(1.0, BAC));
			float dDOC = BAC * doc[l];
			co2[l] += dDOC;
			doc[l] -= dDOC;
			if(l<=q) day_DOC_cons += dDOC;
#endif			
		}

		// Daily profile accumulation 
		if(l<=q)
		{
			profile_accum(l, newh, sumn, fb_nh4, fh_nh4, w_no2, w_no3,
				w_nh4, w_nh3, wurea, wpool_no, fCB, fNB, w_n2o, w_n2,
				wrcvl, wrcl, wrcr, wcrb, wcrhl, wcrhr, whumus, wtcavai,
			   day_ice_N, day_ice_doc, day_ice_n2o, day_ice_n2, IniSOC, IniSON, 
			   EndSON, 
			   soc, rcvl, rcl, rcr, CRB1, CRB2, crhl, crhr,
			   dphum, doc, no3, nh4, nh3, n2, no, n2o, urea,
			   flood_flag, jday, q,
			   no2, winertC);
		}

//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

		if(day_runoff>0.0&&l<=2)//soil erosion by surface runoff flow
		{
			float fw = day_runoff*runMultiN;// / rainfall;//Brian Adjusted runoff increased
			fw = min(1.0, max(0.0, fw));
			

			*day_runoff_N += fw * no3[l];//Runoff N calculation was off previously
			no3[l] *= (1.0 - fw);
			//*day_runoff_N += fw * nh4[l];
			//nh4[l] *= (1.0 - fw);

			//day_runoff_C += fw * doc[l];
			//doc[l] *= (1.0 - fw);

			day_runoff_P += fw * LabP[l];
			LabP[l] *= (1.0 - fw);
			day_runoff_P += 0.05 * fw * AdsP[l];
			AdsP[l] *= (1.0 - 0.05*fw);

		}

		if(l==q) P_adsorption(q, LabP, AdsP, h, day_wfps, sts, mmm);//P adsorption 
 
	} //end of layer loop

	*day_clay_N = 0.0;

	if(BL!=EL) for(int vv=1; vv<=q; vv++) *day_clay_N += clay_nh4[vv];

    *dsnh3 = 0.0;
    *day_dsurea = 0.0;
    *ds_doc = 0.0;

	if(BL!=EL)
	{
			//float SoilDepth = 0.0;
			for(int xx=0; xx<=q; xx++)//xx=1 was before added 0-5 cm. 
			{	
				if(SoilDepth[xx]<=0.05)
				{
			
					dsurea[0] += urea[xx];
	

				}
				
				
				if ((day_denitrify_n2ol[xx]-day_nitrify_n2ol[xx]) < 0.000)
				{
					day_nitrify_n2ol[xx] = (day_nitrify_n2ol[xx] + (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]));//fixes mass balance recovery of substrates.
					//day_denitrify_n2ol[xx] = 0.0;
				}
				
				if(SoilDepth[xx]<=0.1)
				{
					dsno3[1] += no3[xx];
					dsnh4[1] += nh4[xx];
					dsurea[1] += urea[xx];
					dsClayN[1] += clay_nh4[xx];
					*dsnh3 += nh3[xx];
					*day_dsurea += urea[xx];
					*ds_doc += doc[xx];

					day_nitrif[1] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[1] += (day_denitrify_n2ol[xx]- day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[1] += co2[xx];
					total_n2o[1] += n2o[xx];

				}
				else if(SoilDepth[xx]<=0.2)
				{
					dsno3[2] += no3[xx];
					dsnh4[2] += nh4[xx];
					dsurea[2] += urea[xx];
					dsClayN[2] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[2] += day_nitrify_n2ol[xx];//  day_nitrification[xx];
					day_denitrif[2] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[2] += co2[xx];
					total_n2o[2] += n2o[xx];
				}
				else if(SoilDepth[xx]<=0.3)
				{
					dsno3[3] += no3[xx];
					dsnh4[3] += nh4[xx];
					dsurea[3] += urea[xx];
					dsClayN[3] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[3] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[3] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[3] += co2[xx];
					total_n2o[3] += n2o[xx];
				}
				else if(SoilDepth[xx]<=0.4)
				{
					dsno3[4] += no3[xx];
					dsnh4[4] += nh4[xx];
					dsurea[4] += urea[xx];
					dsClayN[4] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[4] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[4] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[4] += co2[xx];
					total_n2o[4] += n2o[xx];
				}
				else if(SoilDepth[xx]<=0.5)
				{
					dsno3[5] += no3[xx];
					dsnh4[5] += nh4[xx];
					dsurea[5] += urea[xx];
					dsClayN[5] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[5] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[5] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[5] += co2[xx];
					total_n2o[5] += n2o[xx];
				}
				else if(SoilDepth[xx]<=0.6)
				{
					dsno3[6] += no3[xx];
					dsnh4[6] += nh4[xx];
					dsurea[6] += urea[xx];
					dsClayN[6] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[6] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[6] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[6] += co2[xx];
					total_n2o[6] += n2o[xx];
				}
				else if(SoilDepth[xx]<=0.7)
				{
					dsno3[7] += no3[xx];
					dsnh4[7] += nh4[xx];
					dsClayN[7] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[7] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[7] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[7] += co2[xx];
					total_n2o[7] += n2o[xx];
				}
				else if(SoilDepth[xx]<=0.8)
				{
					dsno3[8] += no3[xx];
					dsnh4[8] += nh4[xx];
					dsClayN[8] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[8] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[8] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[8] += co2[xx];
					total_n2o[8] += n2o[xx];
				}
				else if(SoilDepth[xx]<=0.9)
				{
					dsno3[9] += no3[xx];
					dsnh4[9] += nh4[xx];
					dsClayN[9] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[9] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[9] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[9] += co2[xx];
					total_n2o[9] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.0)
				{
					dsno3[10] += no3[xx];
					dsnh4[10] += nh4[xx];
					dsClayN[10] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[10] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[10] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[10] += co2[xx];
					total_n2o[10] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.1)
				{
					dsno3[11] += no3[xx];
					dsnh4[11] += nh4[xx];
					dsClayN[11] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[11] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[11] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[11] += co2[xx];
					total_n2o[11] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.2)
				{
					dsno3[12] += no3[xx];
					dsnh4[12] += nh4[xx];
					dsClayN[12] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[12] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[12] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[12] += co2[xx];
					total_n2o[12] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.3)
				{
					dsno3[13] += no3[xx];
					dsnh4[13] += nh4[xx];
					dsClayN[13] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[13] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[13] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[13] += co2[xx];
					total_n2o[13] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.4)
				{
					dsno3[14] += no3[xx];
					dsnh4[14] += nh4[xx];
					dsClayN[14] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[14] += day_nitrify_n2ol[xx];// day_nitrification[xx];
					day_denitrif[14] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[14] += co2[xx];
					total_n2o[14] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.5)
				{
					dsno3[15] += no3[xx];
					dsnh4[15] += nh4[xx];
					dsClayN[15] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[15] += day_nitrify_n2ol[xx]; // day_nitrification[xx];
					day_denitrif[15] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[15] += co2[xx];
					total_n2o[15] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.6)
				{
					dsno3[16] += no3[xx];
					dsnh4[16] += nh4[xx];
					dsClayN[16] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[16] += day_nitrify_n2ol[xx];//  day_nitrification[xx];
					day_denitrif[16] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[16] += co2[xx];
					total_n2o[16] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.7)
				{
					dsno3[17] += no3[xx];
					dsnh4[17] += nh4[xx];
					dsClayN[17] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[17] += day_nitrify_n2ol[xx];//  day_nitrification[xx];
					day_denitrif[17] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[17] += co2[xx];
					total_n2o[17] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.8)
				{
					dsno3[18] += no3[xx];
					dsnh4[18] += nh4[xx];
					dsClayN[18] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[18] += day_nitrify_n2ol[xx];//  day_nitrification[xx];
					day_denitrif[18] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[18] += co2[xx];
					total_n2o[18] += n2o[xx];
				}
				else if(SoilDepth[xx]<=1.9)
				{
					dsno3[19] += no3[xx];
					dsnh4[19] += nh4[xx];
					dsClayN[19] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[19] += day_nitrify_n2ol[xx];//  day_nitrification[xx];
					day_denitrif[19] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[19] += co2[xx];
					total_n2o[19] += n2o[xx];
				}
				else if(SoilDepth[xx]<=2.0)
				{
					dsno3[20] += no3[xx];
					dsnh4[20] += nh4[xx];
					dsClayN[20] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[20] += day_nitrify_n2ol[xx];//  day_nitrification[xx];
					day_denitrif[20] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[20] += co2[xx];
					total_n2o[20] += n2o[xx];
				}

				else
				{
					dsno3[21] += no3[xx];
					dsnh4[21] += nh4[xx];
					dsClayN[21] += clay_nh4[xx];
					*day_dsurea += urea[xx];
					day_nitrif[21] += day_nitrify_n2ol[xx];//  day_nitrification[xx];
					day_denitrif[21] += (day_denitrify_n2ol[xx] - day_nitrify_n2ol[xx]);// day_denitrification[xx];
					day_decomp[21] += co2[xx];
					total_n2o[21] += n2o[xx];
				}

				
				day_nitrify_n2ol[xx] = 0.0;
				day_denitrify_n2ol[xx] = 0.0;

			}// end of xx loop
	}

	if(crop[1]==0&&temp[1]>0.0) //fungi N fixation
	{
		float MicroNfix = soc[1] * 0.0000001 * temp[1];
		for(int i=4;i<=8;i++) nh4[i] += (MicroNfix*0.2);
		yr_fixn[1] += MicroNfix;
	}

//ttn = MData.Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
//				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
}

void class_model::redefine_microbe(int l, float RFM, 
	float TTT, int jday, float *soc, float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *crhl,
	float *crhr, float *dphum, float *mmm, float *clay, float *ocini, float *no2, float *no3, float *manurePool)
{
/*	if(TTT>0.0||jday==1)
    {
		soc[l] = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] + crhl[l]+crhr[l] + dphum[l];
		ocini[l] = CRB1[l] + CRB2[l] + crhl[l]+crhr[l];

		//CRB1[l] = ocini[l] * RBO * SRB;
		//CRB2[l] = ocini[l] * RBO * (1.0 - SRB);
		CRB1[l] = soc[l] * RBO * SRB;
		CRB2[l] = soc[l] * RBO * (1.0 - SRB);

		if((ocini[l]*0.8) < (CRB1[l] + CRB2[l]))
		{
			float dBC = (CRB1[l] + CRB2[l]) - ocini[l]*0.8;
			float df1=dBC * CRB1[l] / (CRB1[l] + CRB2[l]);
			float df2=dBC * CRB2[l] / (CRB1[l] + CRB2[l]);
			CRB1[l] -=df1; 
			CRB2[l] -=df2;

		}
		
		float day_hdcx = ocini[l] - (CRB1[l] + CRB2[l]);

		crhl[l] = day_hdcx * srh;
		crhr[l] = day_hdcx * (1.0 - srh);		
    }
*/
	
	
#ifdef MANURE
	soc[l] = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] + crhl[l] + crhr[l] + dphum[l]; //add manurePool[l]?
#else
	soc[l] = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] + crhl[l] + crhr[l] + dphum[l] +manurePool[l]; //add manurePool[l]?
#endif
	if (isnan(soc[l]))
	{
		float blah;
		blah = 1.0;

	}
	if(TTT>0.0)//||jday==1)
    {
		/*soc[l] = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] + crhl[l]+crhr[l] + dphum[l];
		float total_humus = CRB1[l] + CRB2[l] + crhl[l]+crhr[l] + dphum[l];		
		float rbo = 0.02 * RFM + 0.0000001;
		float clay_humus = 0.01 * m * clay;
		float CRB;		
		if(total_humus>clay_humus)
			CRB = (total_humus - clay_humus) * rbo;
		else
			CRB = 0.0000001;
		CRB1[l] = CRB * SRB;
		CRB2[l] = CRB * (1.0 - SRB);
		float AHM = crhl[l] + crhr[l];
		ocini[l] = CRB + AHM;
		dphum[l] = total_humus - ocini[l];*/

		double Fhc, ActSOC, CRB, Thc;
		ActSOC = CRB1[l] + CRB2[l] + crhl[l] + crhr[l];
		if(ActSOC<=0.0) Fhc = 0.0;
		else Fhc = crhl[l] / (crhl[l] + crhr[l]);
		CRB = 0.01 * ActSOC;		
		CRB1[l] = CRB * SRB;
		CRB2[l] = CRB * (1.0 - SRB);
		Thc = ActSOC - CRB;
		crhl[l] = Thc * Fhc;
		crhr[l] = Thc - crhl[l];
		double new_ActSOC = CRB1[l] + CRB2[l] + crhl[l] + crhr[l];
		double dActSOC;
		if(new_ActSOC!=ActSOC) 
		{
			dActSOC = new_ActSOC - ActSOC;
			crhr[l] -= dActSOC;
		}	
    }

    no3[l] += no2[l];
    no2[l] = 0.0;
}

void class_model::effect_temp_mois(int l, float *day_wfps, int WTL, float *temp, int LandUse, int flood_flag, 
									int FloDays, float *RFM, int *st, float *ice, int q, float MicrobioIndex)
{
    float  RFMM, RFMT, Fpeat;


	//testing to see if day water fps is less than this small value...ensures its not zero
    if (day_wfps[l]<0.00001) day_wfps[l] = 0.00001;

    //RFMM = (-4.3717 * day_wfps[l] * day_wfps[l] + 5.1364 * day_wfps[l] - 0.5455);
	//RFMM = (-5.9991 * day_wfps[l] * day_wfps[l] + 7.8176 * day_wfps[l] - 1.6204);
	//RFMM = -4.1107* day_wfps[l]* day_wfps[l] + 5.1597* day_wfps[l] - 0.6429;
	
	
	//Effect of moisture 
	RFMM = -2.8516* day_wfps[l]* day_wfps[l]* day_wfps[l] + 1.4936* day_wfps[l]* day_wfps[l] + 1.7699* day_wfps[l] - 0.0301;//effect of moisture only

	RFMM = max(0.01, RFMM);
	//if(day_wfps[1]<wiltpt) RFMM *= 0.01;
	
/*	if(l>WTL) 
		RFMM *= 0.001;//0.005;
	else
	{
		if(st[1]>=12&&day_wfps[l]>0.7) 
			RFMM *= 0.001;//0.005; 
		else 
			RFMM = RFMM;

		if(ice[l]>0.0) RFMM = 0.0;
	}
*/


	//new arctangent function for temperature effect on C decomposition. Upcomming publication Siteini et al., 2024 on Biosolids. Old default function below but has poor representation of decompostion  <15 oC 
	
    if (temp[l]<=0.0) 
		RFMT = 0.01;//if temperature is less than 0 then effect of temperature on decomposition is fixed at 0.01
    else 
		RFMT = 0.0000000038 * temp[l] * temp[l] * temp[l] * temp[l] * temp[l] - 0.0000008001 * temp[l] * temp[l] * temp[l] * temp[l] + 0.0000038932 * temp[l] * temp[l] * temp[l] + 0.0009827301 * temp[l] * temp[l] + 0.0160017336 * temp[l] + 0.0910419050;
		
	RFMT = min(1.0, max(0.01, RFMT));
	
	
	//Current default in DNDC
	
	//RFMT = (-.0014 * temp[l] * temp[l]) + 0.0992 * temp[l] + 0.0198;//effect of temperature on decomposition //default DNDC
	//RFMT = max(0.1, RFMT);//default DNDC
	 
	 
	
	//RFMT = (0.00000012 * pow(temp[l], 5) - 0.00001128 * pow(temp[l], 4) + 0.00030296 * pow(temp[l], 3) - 0.00194091 * pow(temp[l], 2) + 0.02744517 * temp[l] + 0.05236364);//adapted from 2005.  https://doi.org/10.1016/j.femsec.2004.10.002
	

#ifdef MANURE
#else
	if(day_WT>0.0)
		RFMT = (-.0014 * SurfaceWaterT * SurfaceWaterT) + 0.0992 * SurfaceWaterT + 0.0198;
#endif
	
    if (RFMT <= 0.0) RFMT = 0.0;
    
	if(LandUse==5) //wetland, anaerobic fermentation
		*RFM = RFMM * RFMT * 1.0;//5.0;// * 20.0 
	else if(LandUse==6) //woodland, anaerobic fermentation
		*RFM = RFMM * RFMT * 0.1;//5.0;// * 20.0 
	else
	{
		/*if(flood_flag==0)
			*RFM = RFMM * RFMT;
		else
		{
			if(FloDays>=1)
			{
				float F_phenol; 

				F_phenol = 1.0 / FloDays;
				*RFM = F_phenol * RFMM * RFMT;
			}
			else
				*RFM = RFMM * RFMT;
			
		}*/

		*RFM = RFMM * RFMT;//effect of moisture and temperature combined into the variable RFM to be passed onto all the individual decomp pools 
	}

	*RFM=min(1.0, max(0.01, *RFM));

	//if(ice[l]>0.0) *RFM = (0.9 - day_wfps[l]) * 0.05;//0.015;//

	if(st[l]==12) *RFM *= 0.05;
	if(st[l]>12) *RFM *= 0.005;//0.025;//0.1;

#ifdef MANURE
	if(l==q+4) *RFM = *RFM;//compost
	else if(l==q+5) //lagoon
	{
		if(temp[l]<0.0) *RFM = 0.0;//8.0
		else *RFM = (temp[l] - 0.0) * 0.00007;
	}
	else if(l==q+6) *RFM = RFMT * 0.00001;//anaerobic digester
	else if(l==q+8) *RFM = RFMT * 0.00001;//gutter
	else {}	
#else
	if(Eh[1]<-250.0) *RFM = 0.0;
#endif

	*RFM=min(1.0, max(0.0, *RFM));

	*RFM *= MicrobioIndex;

	//else Fpeat = 1.0;
	//*RFM *= 0.0;//Fpeat;
    //return( RFM );
}

void class_model::decomp_of_litter(int l, float *co2, float *nh4, float *h, float *temp, float *day_wfps,
								   float *day_C_mine, float *day_N_assim, float *DRCB, float DRCB1, float DRCB2,
								   float RFM)
{

	//currently not being utilized.....

	if(st[l] < 12)
	{
		if((stub1+stub2+stub3)>0.0&&air_temp>0.0)//&&Eh[1]>-200.0)
		{
			float Ftw= air_temp * 0.0005;//0.005
			float FungiLitterDecomposition2, FungiN, FungiMicrobe, AdditionCO22, DRCB3=0.0;
			float Ftill=0.005f;//0.005

			if(flood_flag==1) Ftill = 0.1;
			
			if(flood_flag!=1)
			{
				FungiLitterDecomposition2 = stub1 * Ftill * RFM;
				FungiN = FungiLitterDecomposition2 / rcnrr;
				FungiMicrobe = FungiN * rcnb;
				AdditionCO22 = FungiLitterDecomposition2 - FungiMicrobe;
				co2[l] += AdditionCO22;
				//day_O2[l] += AdditionCO22;
				//if(day_O2[l]<0.0) day_O2[l]=0.0;
				stub1 -= FungiLitterDecomposition2;
				CRB1[l] += (FungiMicrobe * SRB);
				CRB2[l] += (FungiMicrobe * (1.0 - SRB));
				*day_C_mine += AdditionCO22;
				*day_N_assim += FungiN;
				DRCB3 += FungiMicrobe;

				day_addC += FungiMicrobe;
				day_inStubN += (FungiMicrobe / rcnb);
				yr_addtc += FungiMicrobe;
				yr_addtn += (FungiMicrobe / rcnb);

				FungiLitterDecomposition2 = stub2 * Ftill * RFM;
				FungiN = FungiLitterDecomposition2 / rcnrr;
				FungiMicrobe = FungiN * rcnb;
				AdditionCO22 = FungiLitterDecomposition2 - FungiMicrobe;
				co2[l] += AdditionCO22;
				//day_O2[l] += AdditionCO22;
				//if(day_O2[l]<0.0) day_O2[l]=0.0;
				stub2 -= FungiLitterDecomposition2;
				CRB1[l] += (FungiMicrobe * SRB);
				CRB2[l] += (FungiMicrobe * (1.0 - SRB));
				*day_C_mine += AdditionCO22;
				*day_N_assim += FungiN;
				DRCB3 += FungiMicrobe;

				day_addC += FungiMicrobe;
				day_inStubN += (FungiMicrobe / rcnb);
				yr_addtc += FungiMicrobe;
				yr_addtn += (FungiMicrobe / rcnb);
			
				FungiLitterDecomposition2 = stub3 * Ftill * RFM;
				FungiN = FungiLitterDecomposition2 / rcnrr;
				FungiMicrobe = FungiN * rcnb;
				AdditionCO22 = FungiLitterDecomposition2 - FungiMicrobe;
				co2[l] += AdditionCO22;
				//day_O2[l] += AdditionCO22;
				//if(day_O2[l]<0.0) day_O2[l]=0.0;
				stub3 -= FungiLitterDecomposition2;
				CRB1[l] += (FungiMicrobe * SRB);
				CRB2[l] += (FungiMicrobe * (1.0 - SRB));
				*day_C_mine += AdditionCO22;
				*day_N_assim += FungiN;
				DRCB3 += FungiMicrobe;

				day_addC += FungiMicrobe;
				day_inStubN += (FungiMicrobe / rcnb);
				yr_addtc += FungiMicrobe;
				yr_addtn += (FungiMicrobe / rcnb);
			}

			//*DRCB = DRCB3; //DRCB1 + DRCB2 + 

/*			float dS1, dS2, dS3;
			//Ftw = temp[1] / 40.0 * day_wfps[1]; 
			Ftw = max(0.0, min(Ftw, 0.5));

			dS1 = stub1 * Ftw;
			co2[l] += dS1;
			day_O2[l] += dS1;
			if(day_O2[l]<0.0) day_O2[l]=0.0;
			nh4[l] += (dS1 / rcnrvl);
			stub1 -= dS1;
			if ( stub1 <= 0.0000001 ) stub1 = 0.0;

			dS2 = stub2 * Ftw * 0.5;
			co2[l] += dS2;
			day_O2[l] += dS2;
			if(day_O2[l]<0.0) day_O2[l]=0.0;
			nh4[l] += (dS2 / rcnrl);
			stub2 -= dS2;
			if ( stub2 <= 0.0000001 ) stub2 = 0.0;

			dS3 = stub3 * Ftw * 0.1;
			co2[l] += dS3;
			day_O2[l] += dS3;
			if(day_O2[l]<0.0) day_O2[l]=0.0;
			nh4[l] += (dS3 / rcnrr);
			stub3 -= dS3;
			if ( stub3 <= 0.0000001 ) stub3 = 0.0;

			//day_inStubN += dS1 / rcnrvl + dS2 / rcnrl + dS3 / rcnrr;
*/
		}	

	}
	else
	{
		rcvl[l] += stub1;
		rcl[l] += stub2;
		rcr[l] += stub3;
		stub1 = 0.0;
		stub2 = 0.0;
		stub3 = 0.0;
	}
}

void class_model::manure_decomp(int l, float RFM, float DDRF, float till_fact, float* DRCB4, int tilq,
	float DClitter, float* manurePool, float manurePoolCN, float rcnb, float* nh4,
	float* no3, float* co2, float* CRB1, float* CRB2, float* day_C_mine, float* day_N_mine,
	float* day_N_assim, float* manco2, float* day_O2, float* h, int flood_flag)//labile litter pool (after surface residue added is called)
{
	float PTAN, PDN, p_mandrcl, p_manDRCB2, total_mandrcl, f_till_fact,TN1, TN2,dTN;

	TN1 = manurePool[l] / manurePoolCN + (CRB1[l] + CRB2[l]) / rcnb + no3[l] + nh4[l];

	//if ( l > (tilq + 3) ) f_till_fact = 1.0;
	if (l >= tilq) f_till_fact = 1.0;// + 3
	else  f_till_fact = till_fact;

	/* potential CO2 from rcl decomposition */
	///krcl == 0.074 base decomposition. 
	//DDRF = texture/depth factor
	//DClitter is the overall decomposition factor in soils tab
	//f_till_fact^2 is tillage factor

	float mankr;
	mankr = slowManKRate;//slowManKRate
	//calcalate net decomposition rate of labile litter pool.  //krcl is normally 0.074
	float Frcl = 2.0 * RFM * mankr * DDRF  *   f_till_fact; ///this is calculating the net decomposition rate of the pool  * f_till_fact

	if (flood_flag == 1)//was just if(flood_flag) 
		Frcl *= KTT;//KTT=10.0;

	if (Frcl > 1.0) Frcl = 1.0;
	
	
	manureCK1 = Frcl;
	p_mandrcl = manurePool[l] * Frcl;//litter labile C X rate decomposition for //p_drcl is the portion of the pool that is decomposed. rcl[l] is the total labile litter pool ...replaced with manurePool[l]

	/* potential microbe formation from rcl decomposition */ //EFFRB = 0.67 of the decomposable labile litter... 0.67 to microbe formation 
	p_manDRCB2 = p_mandrcl * EFFRB;//EFFRB=0.67

	/* potential total rcl decomposition */
	total_mandrcl = p_mandrcl + p_manDRCB2;//adds the sum off the previous 2 calculations to figure out the total_C needed for these two pools

	/* N release from potential total rcl decomposition */
	PTAN = total_mandrcl / manurePoolCN;//TAN available Nitrogen from manurePool decompostion/mineralization C + microbe formation to faciliate decomposition of that manurePoolC??

	/* potential N demand for microbial formation */
	PDN = p_manDRCB2 / rcnb; //calculate the N requirement for microbe formation //PDN = microbe  //rcnb probably needs to be for manure C:N actually it should be rcnb since that's what the microbe CN is

	/* net release of mineral N */
	float ddN = PTAN-PDN;// -PDN;// ddN is the difference between what is available from mineralizing/immobilizing that manurePoolC and what the microbes actually need//the requirement to need all the N upfront for microbe formation seems problematic
	float resistantFractionManure,labileManure;
	resistantFractionManure = slowManFrac;
	labileManure = 1 - slowManFrac;

	if (ddN >= 0.0)//if the Total N required for decomposition > N required for the microbe formation
	{


		*manco2 = p_mandrcl;//CO2 release? non-microbe portion of C that is lost to atmosphere
		*DRCB4 = p_manDRCB2;//portion of microbe C formation to be tracked 

		
//		*manco2 = p_mandrcl*labileManure;//CO2 release? non-microbe portion of C that is lost to atmosphere
//		*DRCB4 = p_manDRCB2+(p_mandrcl*resistantFractionManure);//portion of microbe C formation to be tracked 


		//no3[l] += 0.5 * ddN;
		nh4[l] += ddN;//The left over released N (minus microbe requirement) from mineralization of manureC pool that is to be added to NH4 pool

		//day_minen += ddN;
	}
	else //if ddN is negative the microbes needed more nitrogen for assimiliation than the decomposed manureC fraciton provided thus we need to removed N from soil mineral N pools
	{
		if ((no3[l] + nh4[l]) >= (-ddN))//if mineral N pools in a layer can supply the necessary microbe N assimiliation requirements then take from those mineral N pools
		{
			*manco2 = p_mandrcl ; //litco22 still decomposes //probably need new parameter for manaure
			*DRCB4 = p_manDRCB2; //microbes still form //probably need new parameter for manure
//		*manco2 = p_mandrcl*labileManure;//CO2 release? non-microbe portion of C that is lost to atmosphere
//		*DRCB4 = p_manDRCB2+(p_mandrcl*resistantFractionManure);//portion of microbe C formation to be tracked 


			no3[l] -= no3[l] / (no3[l] + nh4[l]) * (-ddN); //Nitrate pool is reduced by the weighted representation of the total minearl N pool ///i.e. Nitrate fraction * the total N difference needed for microbe formations
			nh4[l] -= nh4[l] / (no3[l] + nh4[l]) * (-ddN); //Ammonium pool is reduced by the weighted representation of the total minearl N pool ///i.e. Ammonium fraction * the total N difference needed for microbe formations
		}
		else //we need to see what proportion of C can be dcomposed and microbes can be produced based on available mineral N pool since it can only help supply a portion of the difference
		{
			float rf = (no3[l] + nh4[l]) / (-ddN); // see what fraction the mineral pool can provide of the difference

			*manco2 = rf * p_mandrcl; //recalculate the manCO2 reduce the potential decomposition by that fraction  ...this should be made into new manco2 variable
			*DRCB4 = rf * p_manDRCB2; //recalculate the microbe formationby that fraction..this shoudl be made into new manDRCB variable?

//		*manco2 = rf * p_mandrcl*labileManure;//CO2 release? non-microbe portion of C that is lost to atmosphere
//		*DRCB4 = rf * p_manDRCB2+(rf* p_mandrcl*resistantFractionManure);//portion of microbe C formation to be tracked 


			no3[l] = 0.0; //deplete Nitrate pool completely
			nh4[l] = 0.0; //deplete Manure pool completely
		}

		//day_minen += ddN;
	}
	
	manurePool[l] -= (*manco2 + *DRCB4);//labile litter C reduced by litter decomposed C and microbe C formation

	if (manurePool[l] < 0.0)manurePool[l] = 0.0;
	//CRB1[l] += *DRCB2;
	//co2[l] += *manco2; //tried turning off
	//day_O2[l] += *manco2;//tried turning off
	if(day_O2[l]<0.0) day_O2[l]=0.0;
	CRB1[l] += ((*DRCB4) * SRB);//SRB = 0.9 /// CRB1[l] gets 90% of microbe formation //labile microbe pool?  //later added into decomp_microbes into humads pool
	CRB2[l] += ((*DRCB4) * (1.0 - SRB));//CRB2[l] gets 10% of microbe formation //resistant microbe pool //later added into decomp_microbes into humads pool


	//nh4[l] -= (*DRCB4 / rcnb);//testing rcvl additoin
	

	//testing  rcr //change in the total N from manure N + microbe N + mineral N (TN1) done before new microbe formation and manurePool decomposition and TN2 done after microbe formation and manurePoolDecomposition+N needed from mineral N pools
		//TN2 = manurePool[l] / manurePoolCN + (CRB1[l] + CRB2[l]) / rcnb + no3[l] + nh4[l];

		//dTN = TN2 - TN1;//difference between start and end total N of three N sources

		//nh4[l] -= dTN;//balance the difference on NH4 mineral pool.
		//if (nh4[l] < 0.0) nh4[l] = 0.0;
	//end testing rcr

	*day_C_mine += *manco2;//net C release based on whatever decomposed
	*day_N_mine += *manco2 / manurePoolCN;//1 RCL decomposition using the C:N of labile litter pool based on what decomposed  ....was /rcnrl instead of manurePoolCN
	*day_N_assim += *DRCB4 / rcnb;//N assimilation into microbe pool using microbe C:N ratio


 //turn this off for manure pool decomposibility
	
	//this is using slowManFrac as an adjuster.
	//slowManFrac
	//this adds a lot of additional decomposition of manurepool. 
	if (l <= (int)(0.15 / h[1])) //if a layer is in top 15 cm. Only decomposes the top 15cm of manure
	{
		float FungiLitterDecomposition;
		float Ftill = 0.01f;
		FungiLitterDecomposition = manurePool[l] * Ftill * (RFM)*mankr;// *slowManFrac;//*mankr added the mankr to make it based on Krate of manurePool user specified
		float FungiN = FungiLitterDecomposition / manurePoolCN;
		float FungiMicrobe = FungiN * rcnb;
		float AdditionCO21 = FungiLitterDecomposition - FungiMicrobe;
		if (AdditionCO21 < 0.0)AdditionCO21 = 0.0;
		//co2[l] += AdditionCO21; //Turned off for DOC
		day_O2[l] += AdditionCO21;
		day_co2 += AdditionCO21;//Turned on for DOC
		if (day_O2[l] < 0.0) day_O2[l] = 0.0;
		manurePool[l] -= FungiLitterDecomposition;
		*day_C_mine += AdditionCO21;
		*day_N_assim += FungiN;
		CRB1[l] += (FungiMicrobe * SRB);
		CRB2[l] += (FungiMicrobe * (1.0 - SRB));
		*DRCB4 += FungiMicrobe;//adds to the microbe. 
	}
	
}


void class_model::rcvl_decomp(int l, float* drcvl, float RFM, float DDRF, float till_fact, float* DRCB1, int tilq,
							  float DClitter, float *rcvl, float *nh4, float *co2, float *CRB1, float *CRB2, 
							  float *day_C_mine, float *day_N_mine, float *day_N_assim, float rcnrvl, float rcnb,
							  float *day_O2, int flood_flag) //very labile litter pool
{
    float sum_drcvl, f_till_fact;

    if (l>=tilq) f_till_fact = 1.0;// + 3
    else  f_till_fact = till_fact;//enhanced tillage factor from farming cpp based on tillage depth. 
	//f_till_fact = 1.0;

    // CO2 from rcvl decomposition 
	float r_RFM = max(0.0, min(1.0, RFM));//max(0.7, min(1.0, RFM));
	
	//krcvl == 0.25 base decomposition rate for very labile litter
	//DDRF is defined in main part of DNDC_soilChemistry (seems like a texture/depth function)
	//DClitter is multiplier for decomposition rate on litter fraction.

	float Frcvl = 2.0 * r_RFM * krcvl * DDRF * DClitter * f_till_fact;//* f_till_fact

	if(flood_flag==1) 
		Frcvl *= KTT;//KTT =10.0;

	if(Frcvl>1.0) Frcvl=1.0;
	if(Frcvl<0.0) Frcvl=0.0;
    
	*drcvl = Frcvl * rcvl[l];
	// microbes formed from rcvl decomposition 
    *DRCB1 = (*drcvl) * EFFRB;
	sum_drcvl = (*drcvl) + (*DRCB1);
	rcvl[l] -= sum_drcvl;

	nh4[l] += (sum_drcvl / rcnrvl);	
	
	//co2[l] += *drcvl;
	//day_O2[l] += *drcvl;
	//if(day_O2[l]<0.0) day_O2[l]=0.0;

	CRB1[l] += ((*DRCB1) * SRB);

    CRB2[l] += ((*DRCB1) * (1.0 - SRB));
	
	nh4[l] -= (*DRCB1 / rcnb);	

    // N demand for microbes formation 
    //DRNB1 = (*DRCB1) / rcnb;
    // suplas N 
    //FreeN1 = sum_drcvl / rcnrvl - DRNB1;

	*day_C_mine += *drcvl;
	*day_N_mine += *drcvl/rcnrvl;//1 RCVL decomposition
	*day_N_assim += (*DRCB1 / rcnb);

}






void class_model::rcl_decomp(int l, float RFM, float DDRF, float till_fact,float* DRCB2, int tilq,
							 float DClitter, float *rcl, float rcnrl, float rcnb, float *nh4,
							 float *no3, float *co2, float *CRB1, float *CRB2, float *day_C_mine, float *day_N_mine, 
							 float *day_N_assim, float *litco22, float *day_O2, float *h, int flood_flag)//labile litter pool (after surface residue added is called)
{
    float PTAN, PDN, p_drcl, p_DRCB2, total_drcl, f_till_fact;

    //if ( l > (tilq + 3) ) f_till_fact = 1.0;
	if (l>=tilq) f_till_fact = 1.0;// + 3
    else  f_till_fact = till_fact;
	//f_till_fact = 1.0;

    /* potential CO2 from rcl decomposition */
	///krcl == 0.074 base decomposition. 
	//DDRF = texture/depth factor
	//DClitter is the overall decomposition factor in soils tab
	//f_till_fact^2 is tillage factor


	//calcalate net decomposition rate of labile litter pool.
	float Frcl = 2.0*RFM * krcl * DDRF * DClitter * f_till_fact* f_till_fact; 

	if(flood_flag==1)//was just if(flood_flag) 
		Frcl *= KTT;

	if(Frcl>1.0) Frcl=1.0;

    p_drcl = rcl[l] * Frcl;//litter labile C X rate decomposition for 

    /* potential microbe formation from rcl decomposition */ //EFFRB = 0.67 of the decomposable labile litter... 0.67 to microbe formation 
    p_DRCB2 = p_drcl * EFFRB;

    /* potential total rcl decomposition */
    total_drcl = p_drcl + p_DRCB2;//adds the sum off the previous 2 calculations

    /* N release from potential total rcl decomposition */
    PTAN = total_drcl / rcnrl;//TAN available Nitrogen from decompostion??

    /* potential N demand for microbial formation */
    PDN = p_DRCB2 / rcnb; //calculate the N requirement for microbe formation

    /* net release of N */
	float ddN = PTAN - PDN;// left over N is available for release

	if(ddN >= 0.0)
	{
		*litco22 = p_drcl;//CO2 release?
		*DRCB2 = p_DRCB2;//microbe C

		//no3[l] += 0.5 * ddN;
		nh4[l] += ddN;//soil ammonium added from the left over released N (minus microbe requirement)

		//day_minen += ddN;
	}
	else
	{
		if((no3[l] + nh4[l]) >= (-ddN))
		{
			*litco22 = p_drcl;
			*DRCB2 = p_DRCB2;
			no3[l] -= no3[l]/ (no3[l] + nh4[l]) * (-ddN);
			nh4[l] -= nh4[l]/ (no3[l] + nh4[l]) * (-ddN);
		}
		else
		{
			float rf = (no3[l] + nh4[l]) / (-ddN);

			*litco22 = rf * p_drcl;
			*DRCB2 = rf * p_DRCB2;

			no3[l] = 0.0;
			nh4[l] = 0.0;
		}

		//day_minen += ddN;
	}

	rcl[l] -= (*litco22+*DRCB2);//labile litter C reduced by litter decomposed C and microbe C formation
	//CRB1[l] += *DRCB2;
	//co2[l] += *litco22;
	//day_O2[l] += *litco22;
	//if(day_O2[l]<0.0) day_O2[l]=0.0;
	CRB1[l] += ((*DRCB2) * SRB);//SRB = 0.9 /// CRB1[l] gets 90% of microbe formation
    CRB2[l] += ((*DRCB2) * (1.0 - SRB));//CRB2[l] gets 10% of microbe formation

	*day_C_mine += *litco22;//net C release  
	*day_N_mine += *litco22 / rcnrl;//1 RCL decomposition using the C:N of labile litter pool
	*day_N_assim += *DRCB2 / rcnb;//N assimilation into microbe pool using microbe C:N ratio

	if(l<=(int)(0.15/h[1]))
	{
		float FungiLitterDecomposition;
		float Ftill=0.01f;	
		FungiLitterDecomposition = rcl[l] * Ftill * (RFM);
		float FungiN = FungiLitterDecomposition / rcnrl;
		float FungiMicrobe = FungiN * rcnb;	
		float AdditionCO21 = FungiLitterDecomposition - FungiMicrobe;
		//co2[l] += AdditionCO21;//Turned off for DOC
		day_co2 += AdditionCO21;//Turned on for DOC
		day_O2[l] += AdditionCO21;
		if(day_O2[l]<0.0) day_O2[l]=0.0;
		rcl[l] -= FungiLitterDecomposition;
		//*day_C_mine += AdditionCO21;
		*day_N_assim += FungiN;
		CRB1[l] += (FungiMicrobe * SRB);
		CRB2[l] += (FungiMicrobe * (1.0 - SRB));
		*DRCB2 += FungiMicrobe;
	}
}

void class_model::rcr_decomp(int l, float RFM, float DDRF, float till_fact, float DRCB1, float DRCB2, float* lit_co2,
		   float drcvl, float *CRB1, float* CRB2, float* DRCB, float* sumn, int tilq, float *litco22,
		   float *litco23, float DClitter, float *rcr, float *nh4,
		   float *co2, float *day_C_mine, float *day_N_mine, float *day_N_assim,
		   float rcnrvl, float rcnb, float rcnrr, float *no3, float rcnrl, float *day_O2, float *h,
		   int q, int flood_flag, float *doc, float DRCB4, float* manco2)//resistant labile pool.
{
    float drcra, DRCB3, TN1, TN2, dTN;
    float PTAN, PDN, p_drcr, p_DRCB3, total_drcr, f_till_fact;
	
	TN1 = rcr[l]/rcnrr + (CRB1[l]+CRB2[l])/rcnb + no3[l]+nh4[l];
    //if ( l > (tilq + 3) ) f_till_fact = 1.0;
	if (l>=tilq) f_till_fact = 1.0;// + 3 // sets the layers that tillfactor is enhanced to the tillq depth
    else  f_till_fact = till_fact;

	if (year == 26 && jday == 129)
	{
		float blah;
		blah = 1.0;

	}

	//f_till_fact = 1.0;
    /* potential CO2 from rcr decomposition */
	float Frcr = 2.0*RFM * krcr * DDRF * DClitter * f_till_fact;//2.0

	if(flood_flag==1) Frcr *= KTT;

	if(Frcr>1.0) Frcr=1.0;
	if(l==q+1) Frcr *= 1000.0;
	Frcr = min(1.0, max(0.0, Frcr));

    p_drcr = Frcr * rcr[l];

    /* potential microbe formation from rcr decomposition */
    p_DRCB3 = p_drcr * EFFRB;

    /* potential total rcr decomposition */
    total_drcr = p_drcr + p_DRCB3;

    /* N release from potential total rcr decomposition */
    PTAN = total_drcr / rcnrr;

    /* potential N demand for microbe formation */
    PDN = p_DRCB3 / rcnb;

	/* deficiency of N */
	float ddN = PTAN - PDN;

	if(ddN >= 0.0)
	{
		*litco23 = p_drcr;
		DRCB3 = p_DRCB3;

		//no3[l] += 0.5 * ddN;
		nh4[l] += ddN;
		//day_minen += ddN;
	}
	else
	{
		if((no3[l] + nh4[l]) >= (-ddN))
		{
			*litco23 = p_drcr;
			DRCB3 = p_DRCB3;
			float tin = no3[l] + nh4[l];
			no3[l] -= no3[l]/ tin * (-ddN);
			nh4[l] -= nh4[l]/ tin * (-ddN);
		}
		else
		{
			float rf = (no3[l] + nh4[l]) / (-ddN);

			*litco23 = rf * p_drcr;
			DRCB3 = rf * p_DRCB3;

			no3[l] = 0.0;
			nh4[l] = 0.0;
		}

		//day_minen += ddN;
	}

	rcr[l] -= (*litco23+DRCB3);
	rcr[l] = max(0.0, rcr[l]);

	//co2[l] += *litco23;	
	//day_O2[l] += *litco23;
	//if(day_O2[l]<0.0) day_O2[l]=0.0;

	CRB1[l] += (DRCB3 * SRB);
    CRB2[l] += (DRCB3 * (1.0 - SRB));

	TN2 = rcr[l]/rcnrr + (CRB1[l]+CRB2[l])/rcnb + no3[l]+nh4[l];

	dTN = TN2 - TN1;

	nh4[l] -= dTN;
	if(nh4[l]<0.0) nh4[l] = 0.0;

	*day_C_mine += *litco23;//net C release
	*day_N_mine += *litco23 / rcnrr;//1 RCR decomposition
	*day_N_assim += DRCB3 / rcnb;//N assimilation

	drcra = p_drcr;
	float manureCO2Factor;
	manureCO2Factor = slowManFrac;//changing the user input to allow the Fraction of C going to manure Pool to control the fraction of heterotrophic CO2 evolved from decomposition of manure C added. This might be better suited in manure Decomp function. 
	//tempCO2Factor = 1.0;
    //*lit_co2 = drcvl + *litco22 + *litco23;//!!!
	if ((*manco2 * manureCO2Factor) > 0.0)
	{
		float blah;
		blah = 1.0;
	}
	//new

	//Turned on for DOC
// === Begin: Substrate-to-DOC routing with CO2 & N correction ===

// Conservative starting values; adjust by calibration/site:
	const float DOC_FRAC_RCVL = 0.00f;  // very labile  DOC
	const float DOC_FRAC_RCL = 0.05f;  // labile       DOC
	const float DOC_FRAC_RCR = 0.02f;  // resistant   DOC
	const float DOC_FRAC_MAN = 0.00f;  // manure heterotrophic CO2  DOC (keep 0 unless intentional)

	// Substrate portions currently flowing to CO2-equivalents per pool:
	const float doc_from_rcvl = DOC_FRAC_RCVL * drcvl;       // RCVL substrate slice  DOC
	const float doc_from_rcl = DOC_FRAC_RCL * (*litco22);  // RCL  substrate slice  DOC
	const float doc_from_rcr = DOC_FRAC_RCR * (*litco23);  // RCR  substrate slice  DOC
	const float doc_from_man = DOC_FRAC_MAN * (*manco2 * manureCO2Factor); // optional

	const float doc_add = doc_from_rcvl + doc_from_rcl + doc_from_rcr + doc_from_man;

	// Add DOC (and production counter)
	doc[l] += doc_add;
	if (l <= q) day_DOC_prod += doc_add;


#ifdef DEBUG_CBALANCE
day_doc_from_rcvl   += doc_from_rcvl;
day_doc_from_rcl    += doc_from_rcl;
day_doc_from_rcr    += doc_from_rcr;
day_doc_from_manure += doc_from_man;
day_doc_prod_total  += doc_add;
#endif


	// CO2 correction: remove the same carbon from the day’s CO2 flux
	*day_C_mine -= doc_add;
	if (*day_C_mine < 0.0f) *day_C_mine = 0.0f;

	// N correction: remove the N that would have been mineralized with those diverted substrate parts
	const float doc_add_N =
		(doc_from_rcvl > 0.0f ? doc_from_rcvl / rcnrvl : 0.0f)
		+ (doc_from_rcl > 0.0f ? doc_from_rcl / rcnrl : 0.0f)
		+ (doc_from_rcr > 0.0f ? doc_from_rcr / rcnrr : 0.0f)
		+ (doc_from_man > 0.0f ? doc_from_man / manurePoolCN : 0.0f);
	*sumn -= doc_add_N;

	//end new
	

	//Turned off for DOC
	//doc[l] += drcvl + *litco22 + *litco23 + (*manco2 * manureCO2Factor);//added manco2 for proper linkage to Litter C decomposition //might prefer to remove this here.
	//if (l <= q) day_DOC_prod += drcvl + *litco22 + *litco23 + (*manco2 * manureCO2Factor);//aded manco2 here.  //and put in the manure decomposition code.
	//*sumn = drcvl / rcnrvl + *litco22 / rcnrl + drcra / rcnrr +(*manco2 / manurePoolCN * manureCO2Factor);   /* not accurate */   // was (*manco2/rcnb * tempCO2Factor) but changed to (*manco2/manurePoolCN * tempCO2Factor)
	//Turned off for DOC



	//doc[l] += drcvl + *litco22 + *litco23 + (*manco2 );//added manco2 for proper linkage to Litter C decomposition //might prefer to remove this here.
	//if (l <= q) day_DOC_prod += drcvl + *litco22 + *litco23 + (*manco2 );//aded manco2 here.  //and put in the manure decomposition code.
	//*sumn = drcvl / rcnrvl + *litco22 / rcnrl + drcra / rcnrr + (*manco2 / manurePoolCN );   /* not accurate */   // was (*manco2/rcnb * tempCO2Factor) but changed to (*manco2/manurePoolCN * tempCO2Factor)
	

    *litco22 = 0.0;
	drcvl = 0.0;
	*litco23 = 0.0;
	*manco2 = 0.0;
	//the mass balance of manCO2 needs to be maintained...


	if(l<=(int)(0.1/h[1])&&air_temp>5.0)
	{
		float FungiLitterDecomposition2;
		float Ftill=0.005f;//0.0001
		FungiLitterDecomposition2 = rcr[l] * Ftill * RFM * DClitter;
		float FungiN = FungiLitterDecomposition2 / rcnrr;
		float FungiMicrobe = FungiN * rcnb;
		float AdditionCO22 = FungiLitterDecomposition2 - FungiMicrobe;
		//co2[l] += AdditionCO22;//Turned off for DOC
		day_co2 += AdditionCO22;//new//Turned on for DOC
		//day_O2[l] += AdditionCO22;
		//if(day_O2[l]<0.0) day_O2[l]=0.0;
		rcr[l] -= FungiLitterDecomposition2;
		CRB1[l] += (FungiMicrobe * SRB);
		CRB2[l] += (FungiMicrobe * (1.0 - SRB));
		//*day_C_mine += AdditionCO22;
		*day_N_assim += FungiN;
		DRCB3 += FungiMicrobe;
	}

	*DRCB = DRCB1 + DRCB2 + DRCB3 +DRCB4; 	 //total microbe pool the microbes from verylabile, labile and resistant labile //would add a manure one
}



void class_model::decomp_humads(int l, float RFM, float DDRF, float till_fact,
			  float hrh, float krh, float* fh_co2, float* newh, float* fh_nh4,
			  float* CRB1, float* CRB2, float dcbavai, float DRCB, int tilq,
			  float *clay, float DChumads, float *crhr, float *crhl, float *nh4, float rcnh, float rcnb,
			  float *co2, float *doc, float *temp, float *day_C_mine, float *day_N_mine, float *day_N_assim, 
			  int *st, float *dphum, float rcnm, int q, float *day_O2, 
			  float *OrgP, float *LabP, float *ComP, int jday)

{
    float dchr, dchl, fhc, dhbcr, dhbcl, nhumr, nhuml, f_till_fact, k1, k2;
	float crhl_co2, TN1, TN2, dTN;

    //if ( l > (tilq + 3) ) f_till_fact = 1.0;
	if (l>=tilq) f_till_fact = 1.0;// + 3
    else  f_till_fact = powf(till_fact, 2.0);

	//f_till_fact = 1.0;

    // humads decomposition */
	if(l>q) 
		clay[l] = 0.01;
	float Fclay = 0.5 * powf(clay[l], -0.471); //clay factor
	
	k1 = 1.0 * RFM * hrh * DDRF * f_till_fact * Fclay * DChumads;//0.8  //DDRF - tillage depth factor? hrr=clay factor //RFM=humads decomp input factor?
	k2 = 1.0 * RFM * krh * DDRF * f_till_fact * Fclay * DChumads;//0.8

	if(l==(q+5))
	{
		k1 *= 10000.0;
		k2 *= 10000.0;
	}

	if(k1>1.0) k1=1.0;
	if(k2>1.0) k2=1.0;
    
	dchr = k1 * crhr[l];
    dchl = k2 * crhl[l];

	float dPP = k1 * OrgP[l];
	LabP[l] += dPP;
	OrgP[l] -= dPP;

	TN1 = crhr[l]/rcnh + crhl[l]/rcnh + nh4[l] + (CRB1[l]+CRB2[l])/rcnb + dphum[l]/rcnm;//new humads

	crhr[l] -= dchr;
    crhl[l] -= dchl;

	//dchr partitioning
	doc[l] += dchr * 0.4;
	if(l<=q) day_DOC_prod += dchr * 0.4;
	nh4[l] += (dchr * 0.4 / rcnh);

	// efficiency */
	dhbcr = dchr * 0.2;
	CRB1[l] += (dhbcr * SRB);
	CRB2[l] += (dhbcr * (1.0 - SRB));

	nhumr = dchr * 0.4;//- (dhbcr + crhr_co2);
	dphum[l] += nhumr;

	//dchl partitioning
	doc[l] += dchl * 0.6;
	if(l<=q) day_DOC_prod += dchl * 0.6;
	nh4[l] += (dchl * 0.6 / rcnh);

	// efficiency */
	dhbcl = dchl * 0.15;
	CRB1[l] += (dhbcl * SRB);
	CRB2[l] += (dhbcl * (1.0 - SRB));

	
#ifdef DEBUG_CBALANCE
	day_doc_from_humads += dchr * 0.4 + dchl * 0.6;
	day_doc_prod_total += dchr * 0.4 + dchl * 0.6;
#endif


	nhuml = dchl * 0.25;
	dphum[l] += nhuml;

	TN2 = crhr[l]/rcnh + crhl[l]/rcnh + nh4[l] + (CRB1[l]+CRB2[l])/rcnb + dphum[l]/rcnm;
	dTN = TN2 - TN1;


	nh4[l] -= dTN;

	nh4[l] = max(0.0, nh4[l]);
		
	float humad_mine = dchr * 0.4 + dchl * 0.6;
//	*day_C_mine += humad_mine;// turn this off to not count the humads decomposition as part of the mineralization.//Turned off for DOC
	*day_N_mine += (dchr * 0.4 / rcnh) + (dchl * 0.6 / rcnh);//humads decomposition

	

}

void class_model::decomp_humus(int l, float DDRF, int tilq, float till_fact,
		float *clay, float *h, float DChumus, float *dphum, float *nh4, float *co2, float rcnm, 
		float *day_C_mine, float *day_N_mine, float *day_N_assim, float *day_O2, float *SoilDepth,
		float *temp, float RFM, int q, int flood_flag, float TTT, float day_leach_water,
		float *doc)
{
	float d_humus, d_factor, f_till_fact, Fclay, Fdepth, Ftemp; 
	float TN1, TN2, dTN;

    //d_factor = dphum[l] * 0.000005 - 0.004; 
	//if ( l > (tilq + 3) ) f_till_fact = 1.0;
	if (l>=tilq) f_till_fact = 1.0;// + 3
    else  f_till_fact = till_fact;
	//f_till_fact = 1.0;
	if(l>q) 
	{
		clay[l] = 0.01;
		SoilDepth[l] = 0.01;
	}

	//if(st[l]<12)
	Fclay = (1.0 - clay[l]) / 0.81;//0.1793 * powf(clay[l], -0.471) * 20.0;	
	//Fclay=max(0.0, min(1.0, Fclay));
	
	//if(st==12) Fclay *= 0.1;

	Fdepth = 1.0;// / (float)(l);//powf(10.0, (-20.0 * SoilDepth[l]) + 1.0);
	Fdepth=max(0.0, min(1.0, Fdepth));

	Ftemp = temp[l] / 20.0;//temp[l] / 25.0;
	Ftemp = min(1.0, max(0.001, Ftemp));

	//float SOCf = 1.2E-06 * dphum[l] - 0.0013;
	float SOCf = 0.0013f;//0.00115;//1.0E-05 * dphum[l] - 0.016;//brian was 0.0013
	SOCf = min(1.0, max(0.0, SOCf));
	//exit(0);
	d_factor = 1.0 * SOCf * RFM * DDRF * f_till_fact * Fclay * Fdepth * DChumus * Ftemp; 
	d_factor = min(1.0, max(0.0, d_factor));

	d_humus = dphum[l] * d_factor; 

	TN1 = dphum[l]/rcnm + nh4[l];

      dphum[l] -= d_humus;
	  if(dphum[l] < 0.0)
	  {
		  dphum[l] = 0.0;
		  d_humus = 0.0;
	  }

	  nh4[l] += (d_humus / rcnm);
	  //co2[l] += d_humus;
	  //day_O2[l] += d_humus;
	  //if(day_O2[l]<0.0) day_O2[l]=0.0;
	  doc[l] += d_humus;
	  if(l<=q) day_DOC_prod += d_humus;


#ifdef DEBUG_CBALANCE
	  day_doc_from_humus += d_humus;
	  day_doc_prod_total += d_humus;
#endif



	  *day_N_mine += (d_humus / rcnm);//6
     
	// *day_C_mine += d_humus;//removed for double counting of humus decomposition as part of mineralization.//Turned off for DOC

	  TN2 = dphum[l]/rcnm + nh4[l];

	  dTN = TN2 - TN1;

	  nh4[l] -= dTN;

	  if(nh4[l]<0.0) nh4[l] = 0.0;


}

////////////////////////////////////////
void class_model::NH4_HCO3(void)
{
   int l;
 
	for (l=1; l<=q; l++)
	{
		if(NH4HCO3[l] > 0.0000001)
		{
			float dFF=0.1*sph[l]-0.5;
			dFF = max(0.0, min(0.5, dFF));

			//float Fsf = -3.6735 * powf((float)l, 2.0)/(float)q - 0.7551;
			float Fsf = -3.6735 * (float)l/(float)q - 0.7551;
			Fsf = 6.0 * dFF * powf(10.0, Fsf);

			if(Fsf > 0.5) Fsf = 0.5;

			day_vol_nh3 += Fsf * NH4HCO3[l];

			float dABC = 0.5 * (1.0-Fsf) * NH4HCO3[l];

			nh4[l] += dABC;
			NH4HCO3[l] -= dABC;
		}
		else NH4HCO3[l] = 0.0;
    }
   
   /*else
   {
	   total_ABC = 0.0;

	   for (l=1; l<=q; l++)
	   {
		  total_ABC += NH4HCO3[l];
	   }

	   if (total_ABC == 0.0)
	   {
		  ABC_day = 0;
		  for (l=1; l<=q; l++)
		  {
			old_f_lost[l] = 0.0;
		  }
	   }
	   else
	   {
		 ABC_day += 1;

		 for (l=1; l<=q; l++)
		 {
		   if (ABC_day == 1)
		   {
			ABC[l] = NH4HCO3[l];
		   }

		   if (NH4HCO3[l] > 0.0)
		   {
			  f_lost[l] = 0.01 * ((27.628 + ((temp[l] - 20.0) * 0.374) - (1.0 - day_wfps[l] * 27.41)
						) * (float)log(ABC_day) + (7.6393 + ((temp[l] - 20.0) * 0.886)
						- (1.0 - day_wfps[l]) * 6.17)) * (Eh[l] / 600.0) * (sph[l] / 7.0);

			  if (f_lost[l] < 0.0) f_lost[l] = 0.0;
			  if (f_lost[l] > 1.0) f_lost[l] = 1.0;

			  day_lost = f_lost[l] - old_f_lost[l];

			  if(day_lost < 0.0) day_lost = 0.0;

			  old_f_lost[l] = f_lost[l];

			  ABC_lost = day_lost * ABC[l];

			  if (NH4HCO3[l] >= ABC_lost)
			  {
				NH4HCO3[l] -= ABC_lost;
				day_vol_nh3 += ABC_lost;

			  }
			  else
			  {
				day_vol_nh3 += NH4HCO3[l];
				NH4HCO3[l] = 0.0;
			  }

			  NH4_lost = 0.1 * NH4HCO3[l];
			  nh4[l] += NH4_lost;
			  NH4HCO3[l] -= NH4_lost;
			  if (NH4HCO3[l] < 0.0) NH4HCO3[l] = 0.0;

		   } 
		   else
		   {
				ABC[l] = 0.0;
		   }
		 } // end of layer loop 
	} //if flood_flag = 0
   }*/
}



void class_model::urea_hydrolysis(int l, float *urea, float *temp, float *day_wfps, float *nh4, 
								  float *sph, float *h, int UreaAppDays, float *ttoo, int UreaHydroInhibDays,
								  int flood_flag, int q,int manure_flag,int UIDay1,int UIDay2, float *mmm, float *fldcap, float *wiltpt)
{
	//Urea hydrolysis: CO(NH2)2 + 2H+ + 2H2O -> 2NH4 + H2CO3
		

		float ddf=0.0;
	float rem_urea;
	float buffered_ph;
		

			if(l==1)
			{
				if(UreaHydroInhibDays>0) 
					UreaHydroInhibDays++;
				if(UreaHydroInhibDays==(int)UreaHydroInhibDu) 
					UreaHydroInhibDays=0;

				if (jday >= UIDay1 && jday <= UIDay2)//UreaHydroInhibDays
				{
					
					if (UIDay2 > UIDay1)
					{
						if ((jday - UIDay1) > ((UIDay2 - UIDay1) - 10))//default 9
						{
							float dayGUI, redEffUI;
							dayGUI = (jday - UIDay1) - 9; // need a equation for number of days before degradation.
							redEffUI = 1 - (0.5 * 1 / (-5.93 + 1.13 * sph[l]));//Urea NBPT half-life @ pH engel et al.2015, 
							if (redEffUI < 0) redEffUI = 0.0;
							redEffUI = min(1.0, max(0.0, redEffUI));
							UreaHydroInhibEf *= redEffUI;
							//urea_rate *= (1 - (UreaHydroInhibEf));
						}
						else
						{

						}
					}

				}
				if (jday > UIDay2)
				{
					UreaHydroInhibEf = 0.0;

				}



			}

			if(urea[l]>0.0)//test to see if urea in a layer.  
				{

				
					int diHour=1;//Create variable for hours to be tracked over diurnal cycle.



				
					float urea_hydro, soil_T, urea_rate;
				
					double tempKelvin;
					if(l==1)//working only for surface conditions using hourly
					{
					//tempKelvin=273.15+hourlyTemp[l];
					tempKelvin=273.15+temp[l];
					}
					else //when at depth utilize the same soilT for each layer every hour.
					{
					tempKelvin=273.15+temp[l];
					}

					if(tempKelvin<0.0) soil_T = 0.0;
					else soil_T = tempKelvin;
					

				
					
				//	float Fsoc = 0.01 / ttoo[1]; //effect of soil carbon is 0.01/organic carbon fraction
					float Fsoc = ttoo[1]/0.015;
					Fsoc=max(1.0,min(2.0,Fsoc));
		
						
				//	if(UreaHydroInhibDays==0) //if no inhibitor
						float tempHydroFactor;
					    ddf = -0.03*(float)exp(-0.225*(1/soil_T-0.003356)*(diHour*3600))*5.0;//Thermal degradation (eq 2); Cortus et al. (2008) //new code
					    ddf=pow(((temp[l]/40)+0.2),0.4);//CERES
					    tempHydroFactor=pow(((1.4322*exp(0.0794*temp[l]))/15),1.5)*15;//CERES temperature// ddf=pow(((1.4322*exp(0.0794*temp[l]))/15),0.4)*7;
					     ddf=max(2.5,min(5.0,tempHydroFactor))*-1;//CERES ddf=max(0.0,min(3.0,ddf))*-1;//ddf was set to max(0.0,min(5.0,tempHydroFactor))*-1;
		
		 
		
						if(flood_flag==1) ddf *= 0.0375;//earlier 0.9; // running on 24 hour step now

						
						#ifdef MANURE //running 24 hour step...ddf appropriate?
						/*
								if(MData.m_Flash[l-q]>=1) ddf =  (0.01 * (float)pow(soil_T, 0.9) + 0.2)/24.0;//running on 24 hr time step now
								else 
								{
									if(soil_T>1.0) ddf =  (0.02 * (float)pow(soil_T, 1.0))/24.0;//running on 24 hr time step now
									else ddf =  (0.02 * soil_T)/24.0;//running on 24 hr time step now
								}
								*/
						#endif

						
						if(ddf<=0.0 && l<=q)
						{

							//leads to lower ureahydrolysis at high levels of urea in the soil layer (i.e. greater than 50).
							float ureaConcFactor;
							ureaConcFactor=powf((50/urea[l]),0.5);
							ureaConcFactor=max(0.3,min(1.0,ureaConcFactor));
							
							
						
							
							urea[l]= (urea[l]*1000000.0/(mmm[1] / h[1]));//converts urea to kg/m3 //should be using a temporary variable here .....
							
							//if water content is greater than 45% of holding capacity for subsequent days enable hydrolysis

							//calculate average water content

							float avgWaterContent,ureaWaterMultiplier;
							if (l > 1)
							{
								avgWaterContent = (day_wfps[l] + day_wfps[l + 1] + day_wfps[l - 1]) / 3;
							}
							else
							{
								avgWaterContent = (day_wfps[l] + day_wfps[l + 1]) / 2;
								

							}

							if (avgWaterContent > ((fldcap[l] - wiltpt[l]) * 0.45) + wiltpt[l])//test to see if it is greater than 45% holding capacity
							{
								float aboveWiltPt,counterAdd;
								aboveWiltPt = (avgWaterContent - wiltpt[l]) / (fldcap[l] - wiltpt[l]);
								counterAdd= min(8.0,max(0.0,powf(exp(aboveWiltPt), 1.0)-1.50));
								UreaHydroCounter[l] += counterAdd;
								
								//UreaHydroCounter[l] += 1;
							}
							else
							{
								if (UreaHydroCounter[l] > 1) 
								{ 
									
										//UreaHydroCounter[l]-= 1;
										
								}
								else
								{
									UreaHydroCounter[l] = 0;
								}
							}

							
							if (UreaHydroCounter[l] > 9.0)// Currently waits for counter to reach 8 days....need to adjust this to be more of a % of water content.
							{
								ureaWaterMultiplier = 1.0;// +rainfall * 100;
							}
							else
							{
								ureaWaterMultiplier = 0.1;
							}
							
							
								urea_rate = (urea[l] * ddf * Fsoc * ureaWaterMultiplier * ureaConcFactor) * UreaHydroWaterFactor*UreaHydroFactor*0.05;
								


							
							//urea_rate = (urea[l] * ddf* (day_wfps[l]*sts[l])); //calculates the rate of urea hydrolysis based on soil organic carbon and soil temp..no soil water presently??
							if(jday>=UIDay1 && jday<=UIDay2)//UreaHydroInhibDays
							{
								urea_rate *= (1 - (UreaHydroInhibEf));//testpush


								
							}			
							float SlowReleaseDecompose = 1.0;
							float waterDecomposeFactor = 1.0;

							if (slowReleaseCounter > jday)//tied to slow_release urea fertilizers atm. Need to be moved outside of hydrolysis routine.
							{
								waterDecomposeFactor = (day_wfps[l] - wiltpt[l]) / (fldcap[l] - wiltpt[l])*2.00;//affects how fast this comes out ....needs to be based on literature a bit more rather than a general concept of moisture. Some sigmodial relationships for coating degradation.
								waterDecomposeFactor = max(0.0, min(5.0, waterDecomposeFactor));

								SlowReleaseDecompose = pow((float(slowReleaseCounter) - float(jday)) / float(SlowReleaseDays), waterDecomposeFactor);
								SlowReleaseDecompose = 1 - SlowReleaseDecompose;
								SlowReleaseDecompose = max(0.100, min(1.0, SlowReleaseDecompose));
								urea_rate *= SlowReleaseDecompose;//Modifies the amount of hydrolyzed urea. If dry none will hydrolyze. Should be ideally changed to a slowReleaseFertPool seperate from urea that hydrolyzes seperately due to it's own parameterization. 

							
								

							}


							rem_urea= urea[l]+(urea_rate*1.0);//rem_urea=remaining urea. reduce urea pool by the amount of urea hyrdolysis that occurs (1.0= hourly). urea_rate evaluates to a negative thus additive to total pool for remaining(kg/m3)
							if(rem_urea<0)
							{rem_urea=0.0;}//was 0.0;
							
							urea_hydro= urea[l]-rem_urea; //calculates the amount of urea hydrolysed (kg/m3)
							urea[l]= rem_urea; //assignes new urea amount (kg/m3)
							urea[l]=(urea[l]*(mmm[1] / h[1]))/1000000.0; //converts urea from kg N/m3 to kg N/ha
							
							//urea diffusion into soil per hour
							
							if(l<q&&urea[l]>0.0)
							{
								float ureaMove,depthF,ureaFraction;
								depthF=12.9393*expf(-1*l);
								depthF=min(1.0,max(0.0,depthF));
								//depthF = 1.0;
								ureaFraction=UreaDifFactor;//reading UreaDifFactor from GUI (between 0-1);
								if (UreaHydroInhibEf > 0)
								{
									ureaMove = urea[l] * ureaFraction*1 * depthF;
								}
								else
								{
									ureaMove = urea[l] * ureaFraction * depthF;
								}
								if (ureaMove > 0.1)
								{
									if (ureaMove <= urea[l])
									{
										urea[l + 1] += ureaMove;
										urea[l] -= ureaMove;
									}
									else
									{
										urea[l + 1] += urea[l];
										urea[l] = 0.0;
									}
								}
							}
							
							//urea_hydro=(urea_hydro*(mmm[1] / h[1]))/1000000.0;
							nh4[l] += (urea_hydro *(mmm[1] / h[1]))/1000000.0;//add urea hydrolyzed to ammonium pool in the same layer.
						
															
								//impact of urea hydrolisis on soil pH -chemical equilibrium
								double Kw, V_water, produce_OH, hydrogen, mol_hydro_urea, hydroxide;//define variables
								Kw = exp(14.01708 - 10294.83 / (tempKelvin)-0.039282 * (tempKelvin));
								
								lastKw[l] = Kw;


								//V_water = day_wfps[l] * h[l] * 10000.0 * 1000.0;//liter water/ha in layer l
								mol_hydro_urea = urea_hydro*1000.0/1000.0/ 14.0; //kg N/layer -> mol N/L  --- is urea_hydro in correct units? kg/m3
								produce_OH = mol_hydro_urea; 
								// soil buffer effect 
								if (produce_OH == 0.0) produce_OH = 0.0000000000001;
								
								//double produce_pH= max(0.0,(double)log(Kw/produce_OH)/-2.3026);//calculates the produced H from hydro-urea
								
								double produce_pH=(double)log10(Kw/produce_OH)*-1;
								//if (soilcec<1)//user input soilcec=0 or NA then do this 
								//{
								float xx = (clay[l]) * 100.0 + 0.01 * (soc[l] / mmm[l] * 100.0);// (float)exp(soc[l] / mmm[1] * 1000.0 - 20.0);// + (float)exp(soc[i]/m*1000.0-20.0);
								
								
								/*
								float testSOC;
								testSOC = clay[l]*100.0*1.08 + 1.0* (soc[l] / mmm[l] * 100.0);
								double Fcec = (0.01 * (100 - double(testSOC)));
								Fcec = min(1.0, max(0.0000000001, Fcec));
								*/

								
								if(xx>100.0) xx=100.0;
								float CEC;
								CEC = min(100,(1.0802*xx ));//meq/100 g soil			+ 14.442
								//CEC = 1.0;
								
								
								//CEC[1] = CEC[1] * 14.0 / 100000.0 * mmm[1];//meq/100 g soil -> kg N/ha/layer
								double Fcec = (0.007*(100-double (CEC)));// //pH Buffer currently broken!!! Turned it off. Nitrification rate faster for sands which results in less NH3 losses
								Fcec = pow(Fcec, 0.4);  // Soil CEC effect on buffering Hydrolysis shift on soil pH, >0.6 will increase soil buffering effect on pH shift
																		//Fcec=1.0;
								
													
								produce_OH=  Kw/(double)pow(10.0, -(produce_pH*Fcec));//recalculates the produced OH including the CEC buffering effect.
								
								
								hydrogen = (double)powf(10.0, -sph[l]);//mol H/L  //calculates mols of H based on current pH
								hydroxide = lastKw[l] / hydrogen;//mol OH/L // calculates mols of OH based on H #brian test lastKw[l]
								
																//hydroxide +=oHBufferPool[l];//add what is incoming with pHBuffer
								double oldKw=lastKw[l];//just used for output testing to see if Kw is transfered from one day to next.
								
								float oldhydrogen=hydrogen;//calculate oldhydrogen used for outputTesting only
								float oldhydroxide=hydroxide; //calculate oldhydroxide used for outputTesting only
								
								
								
								hydroxide += produce_OH;//calculate new hydroxide and hydrogen ratios
								

								
								hydrogen = Kw / hydroxide;

								sph[l] = (double)log10(hydrogen)*-1;//default -2.3026 determine new soil pH based on logarithmic hydrogen function.
					 			sph[l] = max(3, min(11, sph[l]));//sets the max and minumum soil pH boundaries to be 3 and 11
								
								//sph[l]=pHShift;

								lastKw[l]=Kw;


								//if(l<=10 && year==10 && diHour==23)
								//{
								
									
								// Outputting Urea code
									/*
									if(jday==jdfer[1] && diHour==1&&l==1)
									{CString TESTFILE;
									FILE *pFile=NULL;
									TESTFILE.Format("%s\\Record\\UREA.txt", OUTPUT);
									pFile = fopen (TESTFILE,"w");
									//fprintf(pFile, "jday,year,layer,sph[l]\n");
									//fprintf(pFile, "%1d,%1d,%1d,%7.16f\n",jday,year,l,sph[l]);

									fprintf(pFile, "jday,year,layer,diHour,hourlyTemp[l],temp[l],day_wfps[l],urea[l],nh4[l],CEC,Fcec,sph[l],ddf,urea_hydro, urea_rate,soil_T,produce_OH,hydrogen, hydroxide,oldhydrogen,oldhydroxide,Kw,oldKw\n");
									fprintf(pFile, "%1d,%1d,%1d,%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.26f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,year,l,diHour,hourlyTemp[l],temp[l],day_wfps[l],urea[l],nh4[l],CEC,Fcec,sph[l],ddf,urea_hydro, urea_rate,soil_T,produce_OH,hydrogen, hydroxide,oldhydrogen,oldhydroxide,Kw,oldKw);
									fclose (pFile);

									}
								
									else
									{
									CString TESTFILE;
									FILE *pFile=NULL;
									TESTFILE.Format("%s\\Record\\UREA.txt", OUTPUT);//OUTPUTBatchFileName
									pFile = fopen (TESTFILE,"a");
									//fprintf(pFile, "%1d,%1d,%1d,%7.16f\n",jday,year,l,sph[l]);
									fprintf(pFile, "%1d,%1d,%1d,%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,year,l,diHour,hourlyTemp[l],temp[l],day_wfps[l],urea[l],nh4[l],CEC,Fcec,sph[l],ddf,urea_hydro, urea_rate,soil_T,produce_OH,hydrogen, hydroxide,oldhydrogen,oldhydroxide,Kw, oldKw);
									fclose (pFile);
									}
								*/
								//}


						
						}//ddf
							
							
								
		
					//	} //dihour loop?
	
					 }//urea concentration >1.0


		 
}



void class_model::nh43_equil(int l, float *temp, float *sph, float *nh4, float *nh3, int q, float *h, float *day_wfps, int flood_flag,  float newmanuPH, float combinedpHDeep,int manureHour, float wind_speed, float NH3Vol)//manureHour
{
	//Chemical equilibrium: NH4+ + OH- = NH3 + H2O
	
	double Kw, Ka, hydrogen, hydroxide, V_water, mol_nh4, mol_nh3,combinedpH, combined_hydrogen, combined_hydroxide, hydroxide_pool,hydroxide_poolDeep,combined_hydrogenDeep,combined_hydroxideDeep; //new code

	double prenh3=nh3[l], prenh4=nh4[l];
 



int diHour=1;//Create variable for hours to be tracked over diurnal cycle.

if(l==1)
{//only do this for first layer
	float nh3Gas=0.0,kH=0.0,tempKelvin=0.0,nh3GasDeep;//,combinedpH=0.0;
	
/*
hourly_soil_temperature();//call hourly soil temperature to return just the surface soil temperature.
Kw=exp(14.01708-10294.83/(hourlyTemp[l]+273.15)-0.039282*(hourlyTemp[l]+273.15));//new code Kate
hydrogen = (float)powf(10.0, -sph[l]);//convert ph into H ions//new code

hydroxide = Kw /hydrogen;//now get the OH ions from H//new code

combinedpH= (newmanuPH *0.87 + sph[l]*1.21 ) /2.08;//weighting for combined OH pool in case of manure application

combined_hydrogen = (float)pow(10.0, -combinedpH);//convert ph into H ions//new code

combined_hydroxide = Kw /combined_hydrogen;//now get the OH ions from H//new code

if(manu_layer==1)//test to see if manure is applied on surface
{
	if(manureHour>0)//test to see if there is a manure application happening
	{
	
	hydroxide_pool=combined_hydroxide;//new code

	}
	else
	{
		if(combined_hydroxide<hydroxide)
		{
		hydroxide_pool=hydroxide;
		}
	}

}
else
{
	hydroxide_pool=hydroxide;
}
*/



//float reductOH=1.0;// Depletion in OH- amount in acid-base reaction as it proceeds
int startHour; //using to put diurnal cycle into proper temporal scale
if(manureHour>0)//ensuring the offset is not smaller than 0 //4
{
	startHour=manureHour;}//utilizing the offset for diurnal cycle //startHour=manureHour-4;
else
{startHour=manureHour;
}
for (diHour=startHour; diHour<=23; diHour++)//loop for to scroll through for calculating NH3aqueous that is evolved (may use this as gas).
{//start loop for diurnal hours

//---start copy of the following block.
	
	

	hourly_soil_temperature();//call hourly soil temperature to return just the surface soil temperature.
	Kw = exp(14.01708 - 10294.83 / (hourlyTemp[l] + 273.15) - 0.039282 * (hourlyTemp[l] + 273.15));//new code Kate
	hydrogen = (float)powf(10.0, -sph[l]);//convert ph into H ions//new code

	hydroxide = Kw / hydrogen;//now get the OH ions from H//new code

	combinedpH = (newmanuPH * 0.87 + sph[l] * 1.21) / 2.08;//weighting for combined OH pool in case of manure application

	combined_hydrogen = (float)pow(10.0, -combinedpH);//convert ph into H ions//new code

	combined_hydroxide = Kw / combined_hydrogen;//now get the OH ions from H//new code

	if (manu_layer == 1)//test to see if manure is applied on surface
	{
		if (manureHour > 0)//test to see if there is a manure application happening
		{

			hydroxide_pool = combined_hydroxide;//new code

		}
		else
		{
			if (combined_hydroxide < hydroxide)
			{
				hydroxide_pool = hydroxide;
			}
		}

	}
	else
	{
		hydroxide_pool = hydroxide;
	}
///------------------------------------ end copy of the above block


			if(diHour<10)
				{
					diTemp=(max_temp-min_temp)/2*tanh((diHour-4.5)/2.5)+(max_temp+min_temp)/2;//formulate for hours 1-10
				}
			else
				{
				diTemp=-1*(max_temp-min_temp)/2*tanh((diHour-16.5)/3.5)+(max_temp+min_temp)/2;//formulate for hours 11-24
				}
 


if(manureHour==0)//testing for manure application and if phcounter 
{
	{
		hydroxide_pool=hydroxide;
	}//setting newmanuPH to be set to sph[l]
}

	
	Ka= exp(191.97-(8451.61/(hourlyTemp[l]+273.15))-31.4335 * log(hourlyTemp[l]+273.15)+0.0152123*(hourlyTemp[l]+273.15));//new code Kate
	//hydrogen = (double)pow(10.0, -combinedpH);//mol/L  default -sph[l]
	//hydroxide = Kw / hydrogen* reductOH;//mol/L

	V_water = day_wfps[l] * h[l] * 10000.0 * 1000.0;//liter water/ha in layer l
	
	mol_nh4 = 1000.0 * nh4[l] / 14.0 / V_water;//kg N -> mol/L//

	mol_nh3 = mol_nh4 * hydroxide_pool / Ka;//mol/L////new code




	//float TotalAvailN =nh4[l]+nh3[l];
	if((mol_nh4 + mol_nh3)<=0.0)
	{
		nh4[l] = 0.0;
		nh3[l] = 0.0;
	}
	else
	{
		float cvf = mol_nh4 / (mol_nh4 + mol_nh3); 
		float TtN = nh4[l]+nh3[l];


#ifdef MANURE				
		if(MData.m_Flash[l-q]>=1) cvf = 0.0;
		else cvf = 0.0;
#endif

		float pHFactor,tempTerm,cTerm;
		tempTerm = 0.0;
		cTerm = 1.0;
		tempTerm = 0.09018 + 2729.92 / (273.16 + hourlyTemp[l]) - sph[l] * cTerm;

		pHFactor =1-( 1 / (1 + pow(10, tempTerm)));
		pHFactor = min(1.0, max(pHFactor, 0.0));
	

		cvf = min(1.0, max(0.0, cvf));
		nh4[l] = TtN * pHFactor; //aqueious amount of NH4 //was cvf
		nh3[l] = TtN - nh4[l];//aqeous amounts of NH3

	




		//nh3[l] = TtN - (TtN * cvf);//kg N/ha in layer l		nh4[l]
		
	}

/*
	float PAA = 0.00005 * powf(sph[l], 4.3);
	PAA = min(1.0, max(0.0, PAA));

	float TAA = nh4[l] + nh3[l];

	if(TAA<=0.0)
	{
		nh4[l] = 0.0;
		nh3[l] = 0.0;
	}
	else
	{
		nh3[l] = TAA * PAA;
		nh4[l] = TAA - nh3[l]; //kg N/ha in layer l		
	}

*/


//Henry's law
float windFact;
//windFact=1+1.5*wind_speed/(wind_speed+1);
if(wind_speed<=1.05)
{windFact=1;}
else if(wind_speed<=1.4)
{
	windFact=3.0;
}
else
{
	windFact=(0.9286*wind_speed-0.8571)+1.0;
	//windFact=3.0;
	
}
tempKelvin=273.15+hourlyTemp[l];//hourlyTemp[l]
kH=(0.2138/tempKelvin)*pow(10,(6.123-1825/tempKelvin));


//moisture factor -- not active atm. Reduces NH3 emissions under wet conditions.

float  sandFraction, soilOM, surfaceSOC, newFC, newWP;
float sandContent[13] = { 0.0,0.85,0.80,0.63,0.15,0.41,0.53,0.09,0.29,0.52,0.08,0.13,0.15 };
if (st[1] <= 12) { sandFraction = sandContent[st[1]]; }
else
{
	sandFraction = 0.15;
}
soilOM = soc[l]/mmm[1] * 100 * 1.72; //calculate OM%
float PredMois1500, PredMois1500Adj, PredMois33, PredMois33Adj, poroMois33, poroMois33Adj,Afactor,Bfactor,MoisFactor;
PredMois1500 = (-0.024 * sandFraction + 0.487 * clay[l] + 0.006 * soilOM + 0.005 * clay[l] * soilOM - 0.013 * clay[l] * soilOM + 0.068 * sandFraction * clay[l] + 0.031)*100;
PredMois1500Adj = PredMois1500 + 0.14 * PredMois1500 - 0.02;
PredMois33 = (-0.251 * sandFraction + 0.195 * clay[l] + 0.011 * soilOM + 0.006 * sandFraction * soilOM - 0.027 * clay[l] * soilOM + 0.462 * sandFraction * clay[l] + 0.299)*100;
PredMois33Adj = PredMois33 + (1.283 * PredMois33 * PredMois33 - 0.374 * PredMois33 - 0.015);
poroMois33 = (0.278 * sandFraction + 0.034 * clay[l] + 0.022 * soilOM - 0.018 * sandFraction * soilOM - 0.027 * clay[l] * soilOM - 0.584 * sandFraction * clay[l] + 0.078)*100;
poroMois33Adj = poroMois33 + (0.636 * poroMois33 - 0.107);


Bfactor = (log(1500) - log(33)) / (log(PredMois33) - log(PredMois1500));
Afactor = exp(log(33) - Bfactor * log(PredMois33));

MoisFactor = (1 + Afactor) / (1 + Afactor * pow(day_wfps[l] * sts[l]*100.0, Bfactor));
//end MoistureFactor


float potnh3Gas;
if(newmanuPH>0)
{
potnh3Gas=kH*nh3[l]*windFact*100*NH3Vol;//default * 4  //3600*4
}
else
{
potnh3Gas=kH*nh3[l]*windFact*100*NH3Vol;//right now its arbitrary //*3600*.5050
}

//float oldNH4=nh4[l];


//test to turn this off
if(potnh3Gas>(nh4[l]+nh3[l]))//this needs to be linked to TAN nh4[l] //nh4[l]
{
	nh3Gas+=(nh3[l]+nh4[l]);//nh3[l]
    nh3[l]=0.0;
	nh4[l]=0.0;
}
else if(potnh3Gas<=nh3[l])
{
nh3Gas+=potnh3Gas;
nh3[l]-=potnh3Gas;
nh4[l] += nh3[l];//put the remaining NH3[l] back into NH4[l];
nh3[l] = 0.0;
}
else
{
	nh3Gas += potnh3Gas; //can be met by fully by NH3[l] and partial NH4[l] pools 
	nh4[l] -= potnh3Gas - nh3[l]; //reduce NH4[l] by the excess not met by NH3[l]
	nh3[l] = 0.0;
	
//nh3Gas+=nh3[l];
//potnh3Gas-=nh3[l];
//nh3[l]=0.0;
//nh4[l]-=potnh3Gas;
//nh3Gas+=potnh3Gas;
}

/*
if(potnh3Gas>(nh3[l]+nh4[l]))//this needs to be linked to TAN nh4[l] //nh4[l] //Brian nh3[l]
{
	nh3Gas+=nh3[l]+nh4[l];//nh3[l]
	nh3[l]=0.0;
	nh4[l]=0.0;
}
else
{
nh3Gas+=potnh3Gas;
nh3[l]-=potnh3Gas;
if(nh3[l]<0)
	{
	nh4[l]+=nh3[l];
	nh3[l]=0.0;
	}


}
*/
//reductOH=nh4[l]/oldNH4;
}//end of diurnal loop

//testing with off
nh3[l]=nh3Gas;//nh3 conc at the end of the day

hydrogen = Kw / hydroxide_pool;//new code

sph[l] = (float)log10(hydrogen)*-1;//new code

}//end of layer 1 loop
	



//start for rest of layers after layer 1
else
{

Kw=exp(14.01708-10294.83/(temp[l]+273.15)-0.039282*(temp[l]+273.15));//new code
hydrogen = (float)powf(10.0, -sph[l]);//convert ph into H ions//new code

hydroxide = Kw /hydrogen;//now get the OH ions from H//new code

combinedpHDeep= ((sph[l]*0.50)+(newmanuPH*0.50))/1;//weighting for combined OH pool in case of manure application

combined_hydrogenDeep = (float)powf(10.0, -combinedpHDeep);//convert ph into H ions//new code

combined_hydroxideDeep = Kw /combined_hydrogenDeep;//now get the OH ions from H//new code
	
if(manureHour>0)//test to see if there is a manure application happening
	{
		
		if(l*h[1]<.10)//probably needs checking!!!
		{
		hydroxide_poolDeep=combined_hydroxideDeep;//new code /
			//combinedpHDeep=((sph[l]*0.90)+(newmanuPH*0.10))/1;
		}
		else
		{

		hydroxide_poolDeep=hydroxide;//new code

		}



	}
else
	{
		if(combined_hydroxideDeep<hydroxide)
		{
			hydroxide_poolDeep=hydroxide;//new code

		}
		else
		{
			hydroxide_poolDeep=hydroxide;
		}
			
		
		
	}//if manure application is occuring then come up with a new combined pH
	
	//else of layer loop 
	float nh3Gas=0.0,kH=0.0,tempKelvin=0.0,nh3GasDeep,denom;
	
	
	Ka= exp(191.97-(8451.61/(temp[l]+273.15))-31.4335 * log(temp[l]+273.15)+0.0152123*(temp[l]+273.15));//NH4+/NH3 equilibrium constant ---this is really a Kb..new code Kate


	//hydrogen = (double)pow(10.0, -combinedpHDeep);//mol/L
	//hydroxide = Kw / hydrogen;//mol/L

	V_water = day_wfps[l] * h[l] * 10000.0 * 1000.0;//liter water/ha in layer l
	
	mol_nh4 = 1000.0 * nh4[l] / 14.0 / V_water;//kg N -> mol/L
	mol_nh3 = mol_nh4 * hydroxide_poolDeep / Ka;//mol/L

	
	
	
	
	if((mol_nh4 + mol_nh3)<=0.0)
	{
		nh4[l] = 0.0;
		nh3[l] = 0.0;
	}
	else
	{
		float cvf = mol_nh4 / (mol_nh4 + mol_nh3); 
		float TtN = nh4[l]+nh3[l];
#ifdef MANURE				
		if(MData.m_Flash[l-q]>=1) cvf = 0.0;
		else cvf = 0.0;
#endif

		float pHFactor, tempTerm, cTerm;
		tempTerm = 0.0;
		cTerm = 1.0;
		tempTerm = 0.09018 + 2729.92 / (273.16 + hourlyTemp[l]) - sph[l] * cTerm;

		pHFactor = 1 - (1 / (1 + pow(10, tempTerm)));
		pHFactor = min(1.0, max(pHFactor, 0.0));


		//if(flood_flag==1) cvf *= 0.2;
		cvf = min(1.0, max(0.0, cvf));
		nh4[l] = TtN * pHFactor; //cvf
		nh3[l] = TtN - nh4[l];//kg N/ha in layer l		nh4[l]
	}
	

	


//Henry's law
float windFact;
//windFact=1+1.5*wind_speed/(wind_speed+1);
if(wind_speed<=1.05)
{windFact=1;}
else if(wind_speed<=1.4)
{
	windFact=3.0;
}
else
{
	windFact=(0.9286*wind_speed-0.8571)+1.0;
	//windFact=3.0;
	
}

windFact=1.0;
//Henry's law
tempKelvin=273.15+temp[l];
kH=(0.2138/tempKelvin)*pow(10,(6.123-1825/tempKelvin));

//if(newmanuPH>0)
//{
nh3GasDeep=kH*nh3[l]*100*windFact*NH3Vol;  // *4 *3600
//}
//else
//{
//nh3GasDeep=kH*nh3[l]*60*60*windFact*0.5050;
//}

//brian testing this off


//float depthFactor, soilH;//define variables for influencing depth of application
//soilH = (l*h[1]*100);//calculate soil height in cm
//depthFactor= 53.6 - (10.582 * soilH) +(0.5006 * pow(soilH,2));//new code
//depthFactor=(-0.0417*pow(soilH,4)+1.2644*pow(soilH,3)-11.756*pow(soilH,2)+24.211*soilH+85.833)/100;//reduce emissions per depth
//depthFactor=(20.4+(100-20.4)*exp(-0.772*soilH))/100;

//nh3GasDeep*=depthFactor;

   //testing turning depth off
if(nh3GasDeep>(nh4[l]+nh3[l]))//this needs to be linked to TAN nh4[l] //nh4[l]
{
	nh3GasDeep=(nh3[l]+nh4[l]);//nh3[l]
	nh3[l]=0.0;
	nh4[l]=0.0;
	nh3[l]=nh3GasDeep;
}
else if(nh3GasDeep<=nh3[l])
{

nh3[l]-=nh3GasDeep;
nh4[l]+=nh3[l];


nh3[l]=nh3GasDeep;

}
else
{
nh4[l]-=(nh3GasDeep-nh3[l]);

nh3[l]=nh3GasDeep;
}
//nh3[l]=nh3GasDeep;//off


//brian turning off

/*
if(nh3GasDeep>nh3[l])//test to see if emissions are higher than ammonium available in layer
{nh3GasDeep=nh3[l];//if they are then only let the amount of ammonium in layer be emitted
nh3[l]=0.0;}//set the ammonium levels to zero
else//otherwise
{

	
	
	
//	nh3[l]=nh3[l]-nh3GasDeep;//set ammonium to be the difference between what is available and what is emitted
nh3[l]=nh3GasDeep;}//nh3 gas is now set to what is produced.
*/
/*
if(nh3GasDeep>(nh3[l]+nh4[l]))//test to see if emissions are higher than ammonium available in layer
{//if they are then only let the amount of ammonium in layer be emitted
nh3[l]+=nh4[l];
nh4[l]=0.0;
}//set the ammonium levels to zero
else//otherwise
{
nh3[l]=nh3GasDeep;
	if((nh3[l]-nh3GasDeep)<0)
	{nh4[l]+=(nh3[l]-nh3GasDeep);
	}

}//nh3 gas is now set to what is produced.
*/


hydrogen = Kw / hydroxide_poolDeep;//new code

sph[l] = (float)log10(hydrogen)*-1;//new code
}//end of layer loop
//if (l==fer_layer)
//{
//	float depthFactor, soilH,nh3_depth,rem_nh3;//define variables for influencing depth of application
//	nh3_depth=0.0;
//	rem_nh3=0.0;
	//int csl;
	//for (csl=1;csl<=fer_num;csl++)
	//{
		
		//depthFactor=(-21.0*fer_dept[csl])+1.3417;
	//depthFactor=-0.1856*fer_depth
	//	depthFactor = max(0.0, min(1.0, depthFactor));
	//	if (l==1)
	//	{
	//	nh3_depth=nh3[l]*depthFactor;
	//	}
	//	else
	//	{
	//	nh3_depth=nh3[l]*depthFactor*24.0;
	//	}
	//	rem_nh3=nh3[l]-nh3_depth;
	//}	
	//	if(nh3_depth>nh3[l])//this needs to be linked to TAN nh4[l]
//{
//			nh4[l]+=rem_nh3;
//}

//nh3[l]=nh3_depth;


//}//end of fer_layer code

/*
if(l==5)
{
	
					
	// Outputting Stresses code
	if(year==1&&jday==255)
	{CString TESTFILE;
	FILE *pFile=NULL;

	//if(noBatch==1)
	//{
	//	TESTFILE.Format("%s\\Record\\UREA.txt", OUTPUT);}
	//else
	//{TESTFILE.Format("%s\\UREA.txt", BatchFileName1);}
	TESTFILE.Format("%s\\Record\\UREA.txt", OUTPUT);
	pFile = fopen (TESTFILE,"w");
	fprintf(pFile, "jday,year,prenh3[l],prenh4[l],NO3[1],NO3[2],Kw,Ka,hydrogen,hydroxide,V_water,mol_nh4,mol_nh3,NH4[l],NH3[l],temp[l],sph[l],combinedpH,day_wfps[l],h[l]\n");
	fprintf(pFile, "%1d,%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,year,prenh3,prenh4,no3[1],no3[2],Kw,Ka,hydrogen,hydroxide,V_water,mol_nh4,mol_nh3,nh4[l],nh3[l],temp[l],sph[l],combinedpH,day_wfps[l],h[l]);
	fclose (pFile);
	}
	else
	{
	CString TESTFILE;
	FILE *pFile=NULL;
	
	//if(noBatch==1)
	//{
	//	TESTFILE.Format("%s\\Record\\UREA.txt", OUTPUT);}
	//else
//{TESTFILE.Format("%s\\UREA.txt", BatchFileName1);}
	
	TESTFILE.Format("%s\\Record\\UREA.txt", OUTPUT);//OUTPUTBatchFileName
	pFile = fopen (TESTFILE,"a");
	fprintf(pFile, "%1d,%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,year,prenh3,prenh4,no3[1],no3[2],Kw,Ka,hydrogen,hydroxide,V_water,mol_nh4,mol_nh3,nh4[l],nh3[l],temp[l],sph[l],combinedpH,day_wfps[l],h[l]);
	fclose (pFile);
	}		

}	
*/


}//end of sub model



void class_model::nh3_volatilization(int l, 
	float *temp, int flood_flag, int wetland_flag, float *nh3, int q, float wind_speed, float *day_wfps, 
	float *ice,	float *day_soil_nh3, float *nh4, int jday, float *no3, int manureHour, int manureCounter)
{
    float vol_nh3=0.0, clay_nh3=0.0, soil_T, r_t=0.0;

    if (temp[l] < 0.0) soil_T = 0.0;
    else soil_T = temp[l];

	if(jday>=136 && l<3)


	/////////////////////////////////////////////////////////////
#ifdef MANURE

	if(nh3[l] > 0.0)
	{
		float qk=0.0, BDS=1.0;
		
		if(l>0&&l<=q) r_t = 0.05 * soil_T / (float)l;
		else r_t = 0.075 * temp[l];// * (1.0 + MData.mm_VentRate)
		
		float Fwind = wind_speed / (wind_speed + 3.0);
		
		r_t *= Fwind;

	
		r_t = max(0.1, min(1.0, r_t));
		
		if(l==q+1) //feedlot floor
		{
			/*if(MData.m_Flash[l-q]==0)//water flush 
				qk = r_t * 0.9;
			else if(MData.m_Flash[l-q]==1) //fresh manure liquid flush
				qk = r_t * 1.1;
			else//-1, no flush
				qk = r_t * 1.5;*/

			r_t = 0.0125 * temp[l];

			if(MData.mm_BedType==0)//no bedding
				qk = r_t * 0.15;
			else if(MData.mm_BedType==3)//manure solids
				qk = r_t * 0.9;
			else
			{
				qk = r_t * 1.0;//1.0;
			}
			
			qk = max(0.0, min(1.0, qk));
			
			vol_nh3 = qk * nh3[l];
			
			MData.day_house_nh3 += vol_nh3;
			nh3[l] -= vol_nh3;
			if (nh3[l] < 0.0) nh3[l] = 0.0;
		}

		if(l==q+8) //feedlot gutter
		{
			if(MData.m_Flash[l-q]==0)//water flash 
				qk = 0.025 * r_t;
			else if(MData.m_Flash[l-q]==1) //fresh manure liquid flash
				qk = r_t;
			else//-1, no flash
				qk = r_t;// * r_t;

			qk = max(0.0, min(1.0, qk));

			vol_nh3 = qk * nh3[l];

			MData.day_gutter_nh3 += vol_nh3;
			nh3[l] -= vol_nh3;
			if (nh3[l] < 0.0) nh3[l] = 0.0;
		}

		
		if(l==q+4) //compost
		{
			float KFK = r_t * 10.0 * (1.0 - day_wfps[l] + 0.2);
			KFK = min(1.0, max(0.0, KFK));

			vol_nh3 = nh3[l] * KFK;
			MData.day_Compost_nh3 += vol_nh3;
			nh3[l] -= vol_nh3;
			if (nh3[l] < 0.0) nh3[l] = 0.0;
		}
		
		if(l==q+5) //lagoon
		{
			float F_am = 0.5 * r_t * MData.m_LagoonSurfaceArea / MData.m_LagoonCapacity / (1.0 + 5.0 * MData.m_LagoonCover);//0.01
			F_am = max(0.0, min(1.0, F_am));
			
			vol_nh3 = nh3[l] * F_am;
			MData.day_lagoon_nh3 += vol_nh3;
			nh3[l] -= vol_nh3;
			vol_nh3 = 0.0;
			if (nh3[l] < 0.0) nh3[l] = 0.0;
		}

	
	}
#endif

//float manureApp;
//manureApp=0.0;

if(manureHour>0)
{
	//manureApp=0.0;
	manureCounter=jday+6;
}
if((manureCounter-jday)<0||manureCounter-jday>6)
{
//manureApp=1.0;
}


	if(l<=q && nh3[l]>0.15) //field soil  //&&nh3[l]>(1.5*manureApp) //nh3[l]>0.15 is meant to cut back on background NH3 emissions.
	{
		//effects on NH3 difussion
		float Fsd = powf(((float)(q-l)/(float)q), 50.0);//effect of depth//powf(10.0, -((float)l/1.0));//
		if(l==1) Fsd = 1.0;

		float Fpo = 1.0 / clay[l];//effect of texture
		float Fwi = 1.5 * wind_speed / (1.0 + wind_speed);//effect of wind speed
		float Fst = soil_T / (50.0 + soil_T);//effect of T


		//brian new NH3 code

		Fsd=1.0;
		Fpo=1.0;
		Fwi=1.0;
		Fst=1.0;
		float layerDepth;
		layerDepth=(l*h[1]);//-h[1]
		if(layerDepth<0.01)
		{layerDepth=0.01;}
		Fsd=(-12.556*layerDepth * NH3SoilDFactor +1.1856);
		Fsd=min(1.0,max(0.0,Fsd));
		if(Fsd<0.0)
		{
			Fsd=0.0;
		}
		if(flood_flag==0)//upland soils, //&&nh3[l]>(1.50*manureApp)
		{
	

			float ddf = 1.0 * Fsd * Fpo * Fwi * Fst;
			if(	manuFlag==1)
				ddf *= 2.0;

			ddf = max(0.0, min(1.0, ddf));

			vol_nh3 = nh3[l] * ddf;
			nh3[l] -= vol_nh3;

			*day_soil_nh3 += vol_nh3; 
		}    
		else if(flood_flag==1)
		{
			r_t = 0.001 * temp[1];//soil_T;//0.003
			if(r_t > 1.0) r_t = 1.0;
			  
			vol_nh3 = nh3[l] * r_t; 

			*day_soil_nh3 += vol_nh3;
			nh3[l] -= vol_nh3;
			if(nh3[l] < 0.0) nh3[l] = 0.0;
		}
		

		vol_nh3 = 0.0;
	}
	
if(l<3)
{float blah;
blah=1.0;
}
	
	nh4[l] += nh3[l];
	nh3[l] = 0.0;

}

void class_model::recover_layer_lables(int l, float* CRB1, float* CRB2, float* crhl, float* crhr, float* ocini)
{
    ocini[l] = CRB1[l] + CRB2[l] + crhl[l]+crhr[l];	
}

void class_model::earth_worm(int l, float RFM, float *h, float *rcvl, float *rcl, float *rcr)
{
	float EarthWormActivity = powf(0.0001, (float)l);//0.01
	float ConsumedLitter1, ConsumedLitter2,ConsumedLitter3;

	if(l<(int)(0.2/h[1]))
	{
		if(rcvl[l]>rcvl[l+1])
		{
		ConsumedLitter1 = EarthWormActivity * rcvl[l];
		rcvl[l] -= ConsumedLitter1;
		rcvl[l+1] += ConsumedLitter1;
		}
		
		if(rcl[l]>rcl[l+1])
		{
		ConsumedLitter2 = EarthWormActivity * rcl[l];
		rcl[l] -= ConsumedLitter2;
		rcl[l+1] += ConsumedLitter2;
		}

		if(rcr[l]>rcr[l+1])
		{
		ConsumedLitter3 = EarthWormActivity * rcr[l];	
		rcr[l] -= ConsumedLitter3;	

		rcr[l] = max(0.0, rcr[l]);

		rcr[l+1] += ConsumedLitter3;
		}
	}
}

void class_model::clay_adsorption(int l, float RFM, float *nh4, float *clay_nh4, float base_clay_N, float max_clay_N, int q, float *clay)////////N_adsorption
{
    float active_clay_nh4, totalN, FIXRATE, lbcn, lmcn;
	float TotalNH4 = nh4[l] + clay_nh4[l];

	lbcn = base_clay_N * powf(0.5, (float)l);
	lmcn = max_clay_N * powf(0.5, (float)l);

	if(clay_nh4[l] > lbcn) active_clay_nh4 = clay_nh4[l] - lbcn;
	else active_clay_nh4 = 0.0;

	totalN = nh4[l] + active_clay_nh4;

	FIXRATE = 0.99 * (7.2733*clay[l]*clay[l]*clay[l] - 11.22*clay[l]*clay[l] + 5.7198*clay[l] + 0.0263);//0.5

	//FIXRATE =  0.0144 * (float)exp(0.0981*CEC[l]); 

	if ( FIXRATE < 0.01 ) FIXRATE = 0.01;
	if ( FIXRATE > 0.999) FIXRATE = 0.999;

    active_clay_nh4 = FIXRATE * totalN;

	nh4[l] = (1.0 - FIXRATE) * totalN;

	clay_nh4[l] = TotalNH4 - nh4[l];//lbcn + active_clay_nh4;

	if(clay_nh4[l] > lmcn)
	{
		nh4[l] += (clay_nh4[l] - lmcn);
		clay_nh4[l] = lmcn;		
	}

   
	//Old code /////////////////////////////////////////////////////////////
/*	float active_clay_nh4, totalN, FIXRATE, d_clay_nh4, lbcn;

	lbcn = base_clay_N/(float)q;

	if(clay_nh4[l] > lbcn) active_clay_nh4 = clay_nh4[l] - lbcn;
	else active_clay_nh4 = 0.0;

	totalN = nh4[l] + active_clay_nh4;

    FIXRATE = (0.3325*log(clay)/2.30259 + 1.114)*0.98;

	if ( FIXRATE < 0.01 ) FIXRATE = 0.01;
	if ( FIXRATE > 0.999) FIXRATE = 0.999;

    active_clay_nh4 = FIXRATE * totalN;

	nh4[l] = (1.0 - FIXRATE) * totalN;

	clay_nh4[l] = lbcn + active_clay_nh4;
*/
}



void class_model::soilCEC()
{
	float xx = clay[1]*100.0;// + (float)exp(soc[i]/m*1000.0-20.0);
	float CEC = 1.0802*xx + 14.442 * 14.0 / 100000.0 * mmm[1];//meq/100 g soil	-> kg N/ha/layer		
	
CEC=0.5343*(clay[1]*100) + 1.8555*(ini_ttoo[1]*100)+2.4178;
if(CEC>34.78)
CEC=0.0159*(clay[1]*100)+0.9529*(ini_ttoo[1]*100)+39.8759;

CEC=CEC/100000.0*mmm[1];

	base_clay_N = 0.003 * CEC;//0.01
	max_clay_N = 10.0 * base_clay_N;

}

void class_model::ReDefineION()
{
	int i, k;

	float cc = mmm[1] * 0.000001; //mg N/kg soil -> kg N/ha/layer

	float IniNO3=0.0, IniNH4=0.0, EndNO3=0.0, EndNH4=0.0;

	for(int io=1; io<=q; io++)
	{
		IniNO3 += no3[io];
		IniNH4 += nh4[io];
	}

	{
	for(int i=1; i<=IONdata; i++)
	{
		if(i==1) 
		{
			for(k=1; k<=IONlayer[i]; k++) 
			{
				no3[k]=NO3[i]*cc;
				nh4[k]=NH4[i]*cc;
			}
		}
		else if(i==IONdata) 
		{
			for(k=IONlayer[i]; k<=q; k++) 
			{
				no3[k]=NO3[i]*cc;
				nh4[k]=NH4[i]*cc;
			}
		}
		else 
		{
			for(k=IONlayer[i-1]+1; k<=IONlayer[i]; k++) 
			{
				no3[k]=NO3[i]*cc;
				nh4[k]=NH4[i]*cc;
			}
		}
	}
	}

	
	for(int ip=1; ip<=q; ip++)
	{
		EndNO3 += no3[ip];
		EndNH4 += nh4[ip];
	}

	AdjustNO3 = EndNO3 - IniNO3;
	AdjustNH4 = EndNH4 - IniNH4;
}


void class_model::decomp_microbes(int l, float RFM, float DDRF, float till_fact,float* CRB1, float* CRB2, 
		float* fb_nh4, float* fb_co2, float* dcbavai,int tilq,
		int *st, float *nh4, float rcnb, float *crhr, float *crhl, float *co2, float *day_C_mine, float *day_N_mine, 
		float *day_N_assim, float DChumads, float EFFAC, float rcnh, float *doc, int q, float *day_O2)
{
    float dlhc, DCRB1, DCRB2, DCRB, FBBC, FBHC, f_till_fact, Fo;
	float TN1, TN2, dTN;

	//if(st[l]>=12) Fo=0.1;
	//else Fo=0.7;
	Fo=0.7;
	
    //if ( l > (tilq + 3) ) f_till_fact = 1.0;
	if (l>=tilq) f_till_fact = 1.0;// + 3
    else  f_till_fact = till_fact;

	TN1 = (CRB1[l]+CRB2[l])/rcnb + nh4[l] + crhr[l]/rcnh;

    /* microbe decomposition */
    DCRB1 = RFM * KRB * DDRF * f_till_fact * CRB1[l] * Fo * DChumads;
    DCRB2 = RFM * hrb * DDRF * f_till_fact * CRB2[l] * Fo * DChumads;
    DCRB = DCRB1 + DCRB2;

	CRB1[l] -= (DCRB1);
    CRB2[l] -= (DCRB2);

	nh4[l] += (DCRB / rcnb);	

    /* efficiency */
    FBBC = DCRB * EFFAC;
	/* new microbe */
    CRB1[l] += (FBBC * SRB);
    CRB2[l] += (FBBC * (1.0 - SRB));

	nh4[l] -= (FBBC / rcnb);
	*day_N_assim += (FBBC / rcnb);

    *dcbavai = FBBC;

    /* new resistant humads from microbe decomposition */
    FBHC = DCRB * EFFNO;
    crhr[l] += FBHC;

	nh4[l] -= (FBHC / rcnh);
	//day_N_assim += (FBHC / rcnh);
	

    /* CO2 from net microbe decomposition */
    *fb_co2 = DCRB - FBBC - FBHC;
	//co2[l] += *fb_co2;
	//day_O2[l] += *fb_co2;
	//if(day_O2[l]<0.0) day_O2[l]=0.0;
	doc[l] += *fb_co2;
	if(l<=q) day_DOC_prod += *fb_co2;

//	*day_C_mine += *fb_co2;//Turned off for DOC
	*day_N_mine += *fb_co2/ rcnb;//4

    /* NH4 from net microbe decomposition */
    *fb_nh4 = (*fb_co2) / rcnb;
     

	TN2 = (CRB1[l]+CRB2[l])/rcnb + nh4[l] + crhr[l]/rcnh;
	dTN = TN2 - TN1;

	nh4[l] -= dTN;

	nh4[l] = max(0.0, nh4[l]);
}

void class_model::Substrate_leaching(int hr)//N_leaching
{	
	float LeachN_f, layer_leachN, layer_leachP, layer_leachDOC, fCLAY,TileLeachN_f,LeachU_f; //total_N=0.0, F_NO3, leached_NO3;
	int drainageDepth;
	drainageDepth = int(drainageDepthM/h[1]);
	for(int i=1; i<=q; i++) 
	{
		if(flood_flag==0)
		{
			fCLAY= 0.5 * powf(clay[i],-2.5);//-0.4907);//1.0, 0.8, 0.5
			fCLAY=1.0;//turned off clay factor! brian
			double LeachFlow = OutWater[i][hr];//leach_water per layer per hour
			double TileLeachFlow = TileWater[i][hr];
			
			
			/*
			if(TileLeachFlow>0.0)
			{
					TileLeachN_f= 5.5 * fCLAY * TileLeachFlow;
					TileLeachN_f=min(1.0, max(0.0, TileLeachN_f));
					TileLeachN_f=0.9;

					
					for(int iz=i; iz<=drainageDepth; iz++)
						{
						day_leach_NO3 += no3[iz] * TileLeachN_f;
						no3[iz]-=no3[iz]*TileLeachN_f;
						}
			}
			*/





			if(LeachFlow>0.0 )
			{
				
				int layerLeachedBottom;
				layerLeachedBottom=i;
				for(int iz=i;iz<=q;iz++)
				{
					if(OutWater[iz][hr]>0.0)
					{
					layerLeachedBottom=iz;
					}
				
				}
				
				if(st[i]>=12||by_passf>0.0) LeachN_f = by_passf;//0.8;
				else LeachN_f = 8.0 * fCLAY * LeachFlow*NLeachF;//5.0; 0.05 //Geoff project was 5.5 for leaching
				
				if (UreaHydroInhibEf > 0)
				{
					if (st[i] >= 12 || by_passf > 0.0) LeachU_f = by_passf;//0.8;
					else LeachU_f = 8.0 * fCLAY * powf(LeachFlow, 0.75) * 1.5;//speeding up leaching // 8.0 * fCLAY * LeachFlow*3  powf(LeachFlow,0.90)
				}
				else
				{
					if (st[i] >= 12 || by_passf > 0.0) LeachU_f = by_passf;//0.8;
					else LeachU_f = 8.0 * fCLAY * powf(LeachFlow, 0.95) * 1.5;//speeding up leaching // 8.0 * fCLAY * LeachFlow*3  powf(LeachFlow,0.90)

				}
				

				if(LandUse==6) LeachN_f *= 0.01;
					
				LeachN_f = min(1.0, max(0.0, LeachN_f));
				if(LandUse==6) LeachU_f *= 0.01;
				LeachU_f = min(1.0, max(0.0, LeachU_f));
				
				//float NreductionFactor;
				//NreductionFactor=no3[i]*(no3[i]/100);
				//NreductionFactor=no3[i]/NreductionFactor;
			//	NreductionFactor=min(1.0,max(0.0,NreductionFactor));
				//NreductionFactor=1.0;
				float layer_leachN1=0.0;
				if (no3[i] > 0.0)
				{
				
					layer_leachN1 = no3[i] * LeachN_f;//*(NreductionFactor);
					//if (no3[i] - layer_leachN1 < 25.0)layer_leachN1 = no3[i] * LeachN_f * .001;
					no3[i] -= layer_leachN1;
				}

				//float layer_leachN2 = nh4[i] * LeachN_f;
				//nh4[i] -= layer_leachN2;
				float layer_leachU = 0.0;
						if (urea[i] > 0.01)
						{
							LeachU_f = 0.0;
							layer_leachU = urea[i] * LeachU_f;
							if (layer_leachU > 0.01)
							{
								urea[i] -= layer_leachU;
							}
							else 
							{
							//do nothing.
							}
						}
						

				//layer_leachN = layer_leachN1 + layer_leachN3;// + layer_leachN2;

				layer_leachP = LabP[i] * LeachN_f;
				LabP[i] -= layer_leachP;
				

				layer_leachDOC = doc[i] * LeachN_f;
				doc[i] -= layer_leachDOC;
					
				if(i<q)
				{
				float zz;				
				if(DrainEfficiency>0)
				{
					zz = PrefNMove;//0.9
				}
				else
				{   
				//	if(i>drainageDepth)
				//	zz=1.0;
				//	else
					zz=PrefNMove;//0.99;
				}

				//if(drainageDepth<=i)
				//{zz=0.0;}

					no3[i+1] += (layer_leachN1 * zz);//layer+1 receives 90% of N removed by layer_leachN1
				//	day_leach_NO3 += (layer_leachN1 * (1.0-zz));
					no3[layerLeachedBottom] +=(layer_leachN1*(1.0-zz));

					urea[i + 1] += (layer_leachU * zz);
					day_leach_urea += (layer_leachU * (1.0-zz));

					zz = 0.95;//0.95
					LabP[i+1] += (layer_leachP * zz);
					day_leach_P += (layer_leachP * (1.0-zz));

					zz = 0.9;//0.9
					doc[i+1] += (layer_leachDOC * zz);
					day_leach_DOC += (layer_leachDOC * (1.0-zz));
				}
				else
				{
					day_leach_NO3 += layer_leachN1;
					day_leach_urea += layer_leachU;
					day_leach_P += layer_leachP;
					day_leach_DOC += layer_leachDOC;
				}
			}
		}
		else //if(flood_flag==1&&hr==24)//wetland leaching
		{	
			if(hr==24)
			{
				float leached_humus = dphum[q] * TTT * day_leach_water * 0.01;
				dphum[q] -= leached_humus;					
				day_leachhu += leached_humus;
						
		//		float leach_urea = 3.0 * urea[i] * day_leach_water;//3.0
		//		urea[i] -= leach_urea;
		//		day_leach_urea += leach_urea;
			}		
		}

	}//end of layer loop

/*	if(day_leach_NO3>0.0)//indirect N2O emission
	{
		float Fd, Fs;
		if(st[1]>=12) 
		{
			Fs=0.6;
			Fd=0.75;			
		}
		else
		{
			Fs = 0.0075;//0.07;//clay[1];// * 0.5;//0.25;
			Fd = 0.02;//(1.0-clay[1]); //0.5;			
		}

		float LeachN2 = day_leach_NO3 * Fd;
		float LeachN2O = day_leach_NO3 * Fs;
		float LeachDenN = LeachN2 + LeachN2O;

		day_leach_NO3 -= LeachDenN;
		day_indirect_n2 += LeachN2;
		day_indirect_n2o += LeachN2O;
			
		day_soil_denitrification += LeachDenN;
	}
*/
}


void class_model::Chemodenitrification(int l, float *temp)
{
	
	///////////////////////////////////////////////////////
	float f1, f2, f3, soil_T, fa=0.0001f, chem_no, Tph;

	if (temp[l] < 0.0) soil_T = 0.0;
    else soil_T = temp[l];

    f1 = (-.0014 * soil_T * soil_T) + 0.0992 * soil_T + 0.0198;
	f2 = 90706.0 * (float)exp(-4.2532 * sph[l]);
    f3 = TTT * f1 * f2;
	f3 = max(0.0, min(1.0,f3));

	chem_no = f3 * powf(day_soil_an_no, 1.5);
	if(chem_no>day_soil_an_no) chem_no = day_soil_an_no;
	day_soil_an_no -= chem_no;
	day_soil_an_n2o += chem_no;

	/////////////////////////////
/*	f1 = 0.03 * powf(soil_T, 2.0) + 0.2;//  (based on Yamulki et al., 1997);
	f2 = 2236 * (float)exp(-2.5*sph[l]);//  (based on Blackmer and Cerrato, 1986);
	f3 = TTT * f1 * f2;
	f3 = max(0.0, min(1.0, f3));

	chem_no = fa * nh4[l] * f3;
	nh4[l] -= chem_no;
	day_soil_an_no += 0.9*chem_no;
	day_soil_an_n2o += 0.1*chem_no;
*/
}

int DDepth_convert_to_layer(float DepthO, float *hh, int q)
{
	int LayerN, Qflag=0;

	float Tk=0.0;
	for(int i=1;i<=1000;i++)
	{
		if(i<=q) Tk += hh[i];
		else Tk += hh[q];
		if(Tk>=DepthO)
		{
			LayerN = i-1;
			Qflag=1;
			break;
		}
	}

	if(Qflag==0) LayerN = q;
	return(LayerN);
}