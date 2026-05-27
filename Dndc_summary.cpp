#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;
#endif

void class_model::profile_accum(int l, float* newh, float sumn, float fb_nh4, float fh_nh4,
	       float* w_no2, float* w_no3, float* w_nh4, float* w_nh3, float* wurea, float* wpool_no, 
		   FILE*fCB, FILE*fNB, float* w_n2o, float* w_n2,
		   float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		   float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		   float *EndSON, 
		   float *soc, float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *crhl, float *crhr,
		   float *dphum, float *doc, float *no3, float *nh4, float *nh3, float *n2, float *no, float *n2o, float *urea,
		   int flood_flag, int jday, int q,
		   float *no2, float *winertC)
{


	//manurePool[l] should this get added?
	
    *wrcvl += rcvl[l];
    *wrcl += rcl[l];
    *wrcr += rcr[l];
    *wcrb += (CRB1[l] + CRB2[l]);
    *wcrhl += crhl[l];
	*wcrhr += crhr[l];
    *whumus += dphum[l];
	*wtcavai += doc[l];
	*winertC += inert_C[l];
	//wFreezedoc += FreezeDOC[l];

	if(manurePool[l]>0.0||manurePool[l]<0.0)
	{
		float blah;
		blah = 1.0;
	}

	soc[l] = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] + crhl[l] + crhr[l] + dphum[l] + doc[l] + inert_C[l]+manurePool[l]; //add manurePool[l]?
	if (isnan(soc[l]))
	{
		float blah;
		blah = 1.0;

	}
	Tttoo[l] = soc[l] / mmm[l];


	//li code on adjusting field capacity down layers

	
	if(soilProfileType==0&&year==1&&jday==1)//Brian added and jday==1 This calculates a adjusted fld capacity throughout the soil profile. Intended to make it more in line with increasing bulk density.
	{
	fldcap[l] = ini_fldcap - 2.9f / sts[l] * (ini_ttoo[l] - Tttoo[l]);
	fldcap[l] = min(0.9f, max(wiltpt[l], fldcap[l]));
	}
	if(SoilStructEffect==1.0f)
			{
	fldcap[1]=ini_fldcap; //enable for saxton
			}

	//	oldFC=fldcap[1];

	TotalSoilC += soc[l];

	//if(flood_flag==0) ch4_doc_pool[l]=0.0;

	//*day_ice_N += ice_N[l];
	*day_ice_doc += FreezeDOC[l];
	//*day_ice_n2o += ice_n2o[l];
	//*day_ice_n2 += ice_n2[l];    
    
    *w_no3 += no3[l];
    *w_nh4 += nh4[l];
    *w_nh3 += nh3[l];

	ch4_pool += ch4[l];
    
	*w_no2 += no2[l];
	*wurea += urea[l];
	*wpool_no += no[l];
	*w_n2o += n2o[l];
	*w_n2 += n2[l];

	day_acetate += acetate[l];

	if(jday==cropHarvestDay[1]) // to come up with end Harvest SIN
{
	HarvSIN=*w_nh3 + *w_no3 + *w_nh4 + *wurea  + *wpool_no;// + *end_N_gases+ *day_clay_N;
}
	if(jday==365) EndSP += (AdsP[l]+OrgP[l]+LabP[l]);

	day_SoilWater += water[24][l];//m water/layer

    if ( jday == 365 && l==q)
    {
		yr_end_grain = 0.0;
		yr_end_leaf = 0.0;
		yr_end_stem = 0.0;
		yr_end_root = 0.0;

		for(int i=1;i<=CropNumbers;i++)
		{
			yr_end_grain += Grain_Wt[i];
			yr_end_leaf += Leaf_Wt[i];
			yr_end_stem += Stem_Wt[i];
			yr_end_root += Root_Wt[i];
		}
	}
}

void class_model::cn_pools(float w_no3, float w_nh4, float w_nh3, 
						   float wurea, float wpool_no, float w_n2o, float w_n2)
{
    float wrnvl, wrnl, wrnr, wnrb, wnrhl, wnrhr, whumusn, winertn;
    //static float oldSOC=0.0;
	float wrcvl1, wrcl1, wrcr1, wcrb1, wcrhl1, wcrhr1, whumus1, wtcavai1, winertC1;
  
	FILE  *fp;
    char  IE[120];

    wrnvl = wrcvl / rcnrvl;
    wrnl = wrcl / rcnrl;
    wrnr = wrcr / rcnrr;
    wnrb = wcrb / rcnb;
    wnrhl = wcrhl / rcnh;
	wnrhr = wcrhr / rcnh;
    whumusn = whumus / rcnm;
	winertn = winertC / PassiveCCN;

    //T_SOC = wrcvl+wrcl+wrcr+wcrb+wcrhl+wcrhr+whumus + wtcavai + winertC + wFreezedoc + wCH4_C;
	float T_SON = wrnvl + wrnl + wrnr + wnrb + wnrhl + wnrhr + whumusn + winertn;

	//day_dSOC = T_SOC - old_T_SOC;
	//old_T_SOC = T_SOC;

	day_inLitterN = day_inStubN + day_addrn;// + day_fineroot_N;

	Profile_OrgP =0.0;
	Profile_LabP=0.0;
	Profile_ComP=0.0;
	Profile_AdsP=0.0;
	EndProfWater=0.0;
	totalManureC = 0.0;
	totalManureN = 0.0;
	for(int l=1; l<=q; l++)
	{
		//day_ch4_doc_pool += ch4_doc_pool[l];
		wCH4_C += ch4_doc_pool[l];

		day_ch4_co2_pool += day_ch4_CO2[l];
		day_ch4_H2_pool += day_H2_pool[l];

		Profile_OrgP += OrgP[l];
		Profile_LabP += LabP[l];
		Profile_ComP += ComP[l];
		Profile_AdsP += AdsP[l];

		EndProfWater += water[24][l];
		totalManureC+= manurePool[l];
		totalManureN += manurePool[l] / manurePoolCN;
	}

}


void class_model::annu_accumu_manure_house(int jday)
{
#ifdef MANURE
	MData.yr_house_nh3 += (MData.day_house_nh3+MData.day_gutter_nh3);
	MData.yr_house_n2o += (MData.day_house_n2o+MData.day_gutter_n2o);
	MData.yr_house_ch4 += (MData.day_house_ch4+MData.day_gutter_ch4); 
	MData.yr_house_no += (MData.day_house_no+MData.day_gutter_no);
	MData.yr_house_n2 += (MData.day_house_n2+MData.day_gutter_n2);
	MData.yr_house_co2 += (MData.day_house_co2+MData.day_gutter_co2);

/*	MData.yr_House_to_compost_C += MData.House_to_compost_C;
	MData.yr_House_to_lagoon_C += MData.House_to_lagoon_C;
	//MData.yr_House_to_digester_C += MData.House_to_digester_C;
	MData.yr_House_to_field_C += MData.House_to_field_C;
	MData.yr_House_to_compost_N += MData.House_to_compost_N;
	MData.yr_House_to_lagoon_N += MData.House_to_lagoon_N;
	MData.yr_House_to_digester_N += MData.House_to_digester_N;
	MData.yr_House_to_field_N += MData.House_to_field_N;

	MData.yr_House_to_compost_P += MData.House_to_compost_P;
	MData.yr_House_to_lagoon_P += MData.House_to_lagoon_P;
	MData.yr_House_to_digester_P += MData.House_to_digester_P;
	MData.yr_House_to_field_P += MData.House_to_field_P;

	MData.yr_House_to_compost_H2O += MData.House_to_compost_H2O;
	MData.yr_House_to_lagoon_H2O += MData.House_to_lagoon_H2O;
	MData.yr_House_to_digester_H2O += MData.House_to_digester_H2O;
	MData.yr_House_to_field_H2O += MData.House_to_field_H2O;
*/
	
/*	MData.yr_compost_nh3 += MData.day_Compost_nh3;
	MData.yr_compost_n2o += MData.day_compost_n2o;
	MData.yr_compost_ch4 += MData.day_compost_ch4; 
	MData.yr_compost_no += MData.day_compost_no;
	MData.yr_compost_n2 += MData.day_compost_n2;
	MData.yr_compost_co2 += MData.day_compost_co2;
	
	MData.yr_lagoon_nh3 += MData.day_lagoon_nh3;
	MData.yr_lagoon_n2o += MData.day_lagoon_n2o;
	MData.yr_lagoon_ch4 += MData.day_lagoon_ch4; 
	MData.yr_lagoon_no += MData.day_lagoon_no;
	MData.yr_lagoon_n2 += MData.day_lagoon_n2;
	MData.yr_lagoon_co2 += MData.day_lagoon_co2;

	for(int i=0;i<=9;i++)
	{
		MData.yr_runoff_MC[i] += MData.day_runoff_MC[i];
		MData.yr_runoff_MIN[i] += MData.day_runoff_MIN[i];
		MData.yr_runoff_MON[i] += MData.day_runoff_MON[i];
		MData.yr_runoff_MOP[i] += MData.day_runoff_MOP[i];

		MData.yr_market_MC[i] += MData.day_market_MC[i];
		MData.yr_market_MIN[i] += MData.day_market_MIN[i];
		MData.yr_market_MON[i] += MData.day_market_MON[i];
		MData.yr_market_MOP[i] += MData.day_market_MOP[i];
	}

	MData.yr_compost_runoff_WATER += MData.day_compost_runoff_WATER;

	MData.yr_LOS_LeachN += MData.day_LOS_LeachN;
*/
	if(jday==365)
	{
		MData.yr_LOS_ch4 += MData.yr_enteric_ch4 + MData.yr_house_ch4;// + MData.yr_compost_ch4 + MData.yr_lagoon_ch4;
		MData.yr_LOS_n2o += MData.yr_enteric_n2o + MData.yr_house_n2o;// + MData.yr_compost_n2o + MData.yr_lagoon_n2o;
		MData.yr_LOS_nh3 += MData.yr_enteric_nh3 + MData.yr_house_nh3;// + MData.yr_compost_nh3 + MData.yr_lagoon_nh3;
	}
#endif
}




void class_model::annu_accumu()
{

	
  
	for(cwc=1; cwc<=CropNumbers; cwc++) 
	{
		if(APT[cwc]>0.0)
		{
			yr_trans += APT[cwc]; 			
			crop_trans[cwc] += APT[cwc];			
			APT[cwc] = 0.0;
		}
		
		yr_root_co2 += day_rco2[cwc];
		//day_root_resp += day_rco2[cwc];
		//for(int wx=1; wx<=10; wx++) co2[wx] += day_rco2[cwc];
		day_rco2[cwc] = 0.0;
				
		yr_plant_nh3 += day_plant_nh3[cwc];
		day_plant_nh3[cwc] = 0.0;
		yr_uptaken[cwc] += day_nup[cwc];
		day_nup[cwc]=0.0;
		yr_soilN_from_Nfixation += day_soilN_from_Nfixation[cwc];
		day_soilN_from_Nfixation[cwc] = 0.0;		
		yr_need_N[cwc] += day_need_N[cwc];
		day_need_N[cwc] = 0.0;	

		Yr_PlantBiomass[cwc] += Day_C_growth[cwc];
		Day_C_growth[cwc]=0.0;
	}



    yr_soil_co2 += soil_hete_CO2;//day_co2;
	day_co2 = 0.0;
	root_dCO2 = 0.0;
	
    yr_ch4 += day_ch4;
	day_ch4 = 0.0;
   
    yr_dnno += day_soil_an_no;
    day_soil_an_no = 0.0;
   // yr_dnn2o += day_soil_an_n2o;
    //day_soil_an_n2o = 0.0;
    yr_dnn2 += day_soil_n2;
    day_soil_n2 = 0.0;
    

	//NH3 emissions
    yr_soil_nh3 += (day_soil_nh3+day_vol_nh3);
	yr_leach_NO3 += (day_leach_NO3 + by_pass_no3);
	yr_runoff_N += day_runoff_N;
	yr_leach_water += (day_leach_water); 
	yr_runoff += day_runoff;
	yr_dnn2o += day_soil_an_n2o;

float total_dayDenit2=0.0;
for(int i=1; i<=q; i++) {total_dayDenit2 += day_denitrification[i];}
	//seasonal Batch Outputs Jan1st-Harvest

if(jday>=1 && cropHarvestDay[1]==0 || jday>=1 && jday<=cropHarvestDay[1])
{
seasDay1_harv_atemp += air_temp;
seasDay1_harv_precip += precipitation;
seasDay1_harv_wrunoff += day_runoff;
seasDay1_harv_wleach +=(day_leach_water);
seasDay1_harv_denit += total_dayDenit2;
seasDay1_harv_N2O += day_soil_an_n2o;
seasDay1_harv_NH3 += (day_soil_nh3+day_vol_nh3);
seasDay1_harv_netNmin +=(	day_N_mine-day_N_assim);
seasDay1_harv_Nleach += (day_leach_NO3 + by_pass_no3+day_leach_urea);
seasDay1_harv_irri += day_irri;
if(day_irri>0)
{countIrri+=1;}
seasDay1_harv_trans += day_transp; 
seasDay1_harv_evap += day_soil_ev;
}
//float seasEvap1, seasEvap2, seasEvap3, trans1, trans2, trans3;
//float Nmin1, Nmin2, Nmin3, Nimb1, Nimb2, Nimb3

int   l;
float wrcvl = 0.0, wrcl = 0.0, wrcr = 0.0, wcrb = 0.0, wcrhl = 0.0, wcrhr = 0.0;
float whumus = 0.0, wtcavai = 0.0, winertC = 0.0, wFreezedoc = 0.0;
float wrnvl = 0.0, wrnl = 0.0, wrnr = 0.0, wnrb = 0.0, wnrhl = 0.0, wnrhr = 0.0, whumusn = 0.0;//, winertC/PassiveCCN, ;
float w_n2o = 0.0, w_n2 = 0.0, w_nh3 = 0.0, w_no3 = 0.0, w_nh4 = 0.0, wurea = 0.0, day_clay_N = 0.0, wpool_no = 0.0;
float InertN = 0.0, EndSOC1 = 0.0, EndSON1 = 0.0, EndSIN1 = 0.0;
int layerNum,layerN15,layerN20;

layerN15 = (0.15 / h[1]);
layerN20 = (0.20 / h[1] + 1);

if (PGI[1]>=0.85 && maturityDay[1]==jday|| PGI[2] >= 0.85 && maturityDay[2] == jday || PGI[3] >= 0.85 && maturityDay[3] == jday ||jday==64||jday==66||jday==80||jday==304)
{
	if (jday == 64 || jday == 66)
	{
		layerNum = layerN15;
	}
	else if (jday == 80 || jday == 304)
	{
		layerNum = layerN20;
	}
	else
	{
		if (maturityDay[1] == jday)
		{
			layerNum = root_length[1] / h[1] + 1;
		}
		else if (maturityDay[2] == jday)
		{
			layerNum = root_length[2] / h[1] + 1;
		}
		else if (maturityDay[3] == jday)
		{
			layerNum = root_length[3] / h[1] + 1;
		}
		else
		{
			layerNum = 1;
		}

		if (layerNum < layerN20)layerNum = layerN20;
		
	}
	/*
	finaoc = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l]
		+ crhl[l] + crhr[l] + dphum[l] + inert_C[l] + doc[l]
		+ FreezeDOC[l] + manurePool[l];//add manurePool
		*/
	for (l = 1; l <= layerNum; l++)
	{
		wrcvl += rcvl[l]; wrcl += rcl[l]; wrcr += rcr[l]; wcrb += (CRB1[l] + CRB2[l]); wcrhl += crhl[l]; wcrhr += crhr[l];
		whumus += dphum[l]; winertC += inert_C[l]; wFreezedoc += FreezeDOC[l];
		wtcavai += doc[l];

		w_n2o += n2o[l]; w_n2 += n2[l]; w_nh3 += nh3[l]; w_no3 += no3[l];
		w_nh4 += nh4[l]; wurea += urea[l]; day_clay_N += clay_nh4[l]; wpool_no += no[l];
	}
	wrnvl = wrcvl / rcnrvl;
	wrnl = wrcl / rcnrl;
	wrnr = wrcr / rcnrr;
	wnrb = wcrb / rcnb;
	wnrhl = wcrhl / rcnh;
	wnrhr = wcrhr / rcnh;
	whumusn = whumus / rcnm;
	InertN = winertC / PassiveCCN;

	wno32 = w_no3;
	wnh42 = w_nh4;
	wnh32 = w_nh3;
	wurea2 = wurea;
	wno2 = wpool_no;
	day_clay_n2 = day_clay_N;
	end_N_gases = w_n2o + w_n2;
	EndSIN1 = wno32 + wnh42 + wnh32 + wurea2 + wno2 + day_clay_n2 + end_N_gases;

	whumusn2 = whumusn;
	whumus2 = whumus;

	EndLitter = wrcvl + wrcl + wrcr;
	EndActHumus = wcrb + wcrhl + wcrhr;
	EndSOC1 = EndLitter + EndActHumus + whumus + wtcavai + winertC + wFreezedoc;		//T_SOC;

	EndLitterN = wrnvl + wrnl + wrnr;
	EndActHumusN = wnrb + wnrhl + wnrhr;
	EndSON1 = EndLitterN + EndActHumusN + whumusn + InertN;

	if (maturityDay[1] == jday && PGI[1] >= 0.85)
	{
		seasSoilN1 = EndSIN1;
	}
	if (maturityDay[2] == jday && PGI[2] >= 0.85)
	{
		seasSoilN2 = EndSIN1;
	}
	if (maturityDay[3] == jday && PGI[3] >= 0.85)
	{
		seasSoilN3 = EndSIN1;
	}



	if (jday == 64)
	{
		SOC64 = layerc[1] + layerc[2] / 2.0;//EndSOC1;
		SON64 = layern[1] + layern[2] / 2.0;// EndSON1;
	}
	if (jday == 66)
	{
		SOC66 = layerc[1] + layerc[2] / 2.0; //EndSOC1;
		SON66 = layern[1] + layern[2] / 2.0; //EndSON1;
	}
	if (jday == 80)
	{
		SOC80 = layerc[1] + layerc[2];// EndSOC1;

		SON80 = layern[1] + layern[2]; //EndSON1;

	}
	if (jday == 304)
	{

		SOC304 = layerc[1] + layerc[2]; //EndSOC1;

		SON304 = layern[1] + layern[2]; //EndSON1;
	}

}

if (seed[1] == 1)
{
	plantingDay[1] = jday;
}

if (seed[1]>0||Root_Wt[1]>0.0)//jday<=cropHarvestDay[1] //jday >= jdseed[1] && jdseed[1] > 0
{
	if(PGI[1]<0.5 && Leaf_Wt[1]>0.0){ flowering1Day[1] = jday+1; }
	if (PGI[1] < 0.53 && Leaf_Wt[1]>0.0) { flowering1Day[2] = jday + 1; }
	if (PGI[1] < 0.57 && Leaf_Wt[1]>0.0) { flowering1Day[3] = jday + 1; }
	if (PGI[1] < 0.59 && Leaf_Wt[1]>0.0) { flowering1Day[4] = jday + 1; }
	if (Leaf_Wt[1] <= 0.0 && jday<(jdseed[1]+30)) { emergenceDay[1] = jday+1; }
	if (PGI[1] < 0.9 && Leaf_Wt[1]>0.0) { maturityDay[1] = jday+1; }
	

	
	if (Root_Wt[1] > 0.0)
	{
		seasGrain[1] = Grain_Wt[1];
		seasLeaf[1] = Leaf_Wt[1];
		seasStem[1] = Stem_Wt[1];
		seasRoot[1] = Root_Wt[1];
		seasGrainN[1] = GrainN[1];
		seasLeafN[1] = LeafN[1];
		seasStemN[1] = StemN[1];
		seasRootN[1] = RootN[1];
	}
	

	if (PGI[1] <= 0.9)
	{
		cropGrowDays1 += 1;
		seasEvap1 += day_soil_ev;
		trans1 += day_transp;
		Nmin1 += (day_N_mine);// -day_N_assim);
		Nimb1 += day_N_assim;
		seasCO2Het1 += soil_hete_CO2;

		float total_dayDenit1 = 0.0;
		for (int i = 1; i <= q; i++) { total_dayDenit1 += day_denitrification[i]; }
		seasDenit1 += total_dayDenit1;

		if (lai[1] > seasMaxLAI1)
		{
			seasMaxLAI1 = lai[1];
		}

		seasWL1 += day_leach_water*1000.0;
		seasNH31 += (day_soil_nh3 + day_vol_nh3);
		//seasSoilN1 = EndSIN1;
		seasSOC1 = EndSOC;
		seasSON1 = EndSON;
		seasNO31 += (day_leach_NO3 + by_pass_no3 + day_leach_urea);
		seasCO21 += soil_hete_CO2;
		FertAddNSA[1] += day_inFertN;
		FertAddCSA[1] += day_addmc;

		if (jday == jdseed[1])//calculate soil water at planting in top 15 and top 20cm
		{
			int za, layer15, layer20;
			layer15 = (0.15 / h[1] + 1);
			layer20 = (0.20 / h[1] + 1);
			for (int za = 1; za <= layer15; za++)
			{
				daySoilWater151 += water[24][za] * 1000.0;
			}
			for (int za = 1; za <= layer20; za++)
			{
				daySoilWater201 += water[24][za] * 1000.0;
			}
		}
	}
}
if (seed[2] == 1)
{
	plantingDay[2] = jday;
}


if (seed[2]> 0 || Root_Wt[2] > 0.0)
{
	if (PGI[2] < 0.5 && Leaf_Wt[2]>0.0) { flowering2Day[1] = jday + 1; }
	if (PGI[2] < 0.53 && Leaf_Wt[2]>0.0) { flowering2Day[2] = jday + 1; }
	if (PGI[2] < 0.57 && Leaf_Wt[2]>0.0) { flowering2Day[3] = jday + 1; }
	if (PGI[2] < 0.59 && Leaf_Wt[2]>0.0) { flowering2Day[4] = jday + 1; }
	if (Leaf_Wt[2] <= 0.0 && jday < (jdseed[2] + 30)) { emergenceDay[2] = jday + 1; }
	if (PGI[2] < 0.9 && Leaf_Wt[2]>0.0) { maturityDay[2] = jday + 1; }
	if (seed[2] == 1 ) { plantingDay[2] = jday; }

	if (Root_Wt[2] > 0.0)
	{
		seasGrain[2] = Grain_Wt[2];
		seasLeaf[2] = Leaf_Wt[2];
		seasStem[2] = Stem_Wt[2];
		seasRoot[2] = Root_Wt[2];
		seasGrainN[2] = GrainN[2];
		seasLeafN[2] = LeafN[2];
		seasStemN[2] = StemN[2];
		seasRootN[2] = RootN[2];
	}
	if (PGI[2] <= 0.9)
	{
		cropGrowDays2 += 1;
		seasEvap2 += day_soil_ev;
		trans2 += day_transp;
		Nmin2 += (day_N_mine);// -day_N_assim);
		Nimb2 += day_N_assim;
		seasCO2Het2 += soil_hete_CO2;
		if (lai[2] > seasMaxLAI2)
		{
			seasMaxLAI2 = lai[2];
		}

		float total_dayDenit2 = 0.0;
		for (int i = 1; i <= q; i++) { total_dayDenit2 += day_denitrification[i]; }
		seasDenit2 += total_dayDenit2;



		seasWL2 += day_leach_water * 1000.0;
		seasNH32 += (day_soil_nh3 + day_vol_nh3);
	//	seasSoilN2 = EndSIN1;
		seasSOC2 = EndSOC;
		seasSON2 = EndSON;
		seasNO32 += day_leach_NO3 + by_pass_no3 + day_leach_urea;
		seasCO22 += soil_hete_CO2;
		FertAddNSA[2] += day_inFertN;
		FertAddCSA[2] += day_addmc;

		if (jday == jdseed[2])//calculate soil water at planting in top 15 and top 20cm
		{
			int za, layer15, layer20;
			layer15 = (0.15 / h[1] + 1);
			layer20 = (0.20 / h[1] + 1);
			for (int za = 1; za <= layer15; za++)
			{
				daySoilWater152 += water[24][za] * 1000.0;
			}
			for (int za = 1; za <= layer20; za++)
			{
				daySoilWater202 += water[24][za] * 1000.0;
			}
		}
	}
}

if (seed[3] == 1)
{
	plantingDay[3] = jday;
}


if (seed[3]>0 || Root_Wt[3] > 0.0)
{
	if (PGI[3] < 0.5 && Leaf_Wt[3]>0.0) { flowering3Day[1] = jday+1; }
	if (PGI[3] < 0.53 && Leaf_Wt[3]>0.0) { flowering3Day[2] = jday + 1; }
	if (PGI[3] < 0.57 && Leaf_Wt[3]>0.0) { flowering3Day[3] = jday + 1; }
	if (PGI[3] < 0.59 && Leaf_Wt[3]>0.0) { flowering3Day[4] = jday + 1; }
	if (Leaf_Wt[3] <= 0.0  && jday < (jdseed[3] + 30)) { emergenceDay[3] = jday+1; }
	if (PGI[3] < 0.9 && Leaf_Wt[3]>0.0) { maturityDay[3] = jday+1; }
	if (seed[3] == 1 && PGI[3]<0.1) { plantingDay[3] = jday; }
	
	if (Root_Wt[3] > 0.0)
	{
		seasGrain[3] = Grain_Wt[3];
		seasLeaf[3] = Leaf_Wt[3];
		seasStem[3] = Stem_Wt[3];
		seasRoot[3] = Root_Wt[3];
		seasGrainN[3] = GrainN[3];
		seasLeafN[3] = LeafN[3];
		seasStemN[3] = StemN[3];
		seasRootN[3] = RootN[3];
	}
	if (PGI[3] <= 0.9)
	{
		cropGrowDays3 += 1;
		seasEvap3 += day_soil_ev;
		trans3 += day_transp;
		Nmin3 += (day_N_mine);// -day_N_assim);
		Nimb3 += day_N_assim;
		seasCO2Het3 += soil_hete_CO2;
		if (lai[3] > seasMaxLAI3)
		{
			seasMaxLAI3 = lai[3];
		}
		float total_dayDenit3 = 0.0;
		for (int i = 1; i <= q; i++) { total_dayDenit3 += day_denitrification[i]; }
		seasDenit3 += total_dayDenit3;

		seasWL3 += day_leach_water * 1000.0;
		seasNH33 += (day_soil_nh3 + day_vol_nh3);
	//	seasSoilN3 = EndSIN1;
		seasSOC3 = EndSOC;
		seasSON3 = EndSON;
		seasNO33 += day_leach_NO3 + by_pass_no3 + day_leach_urea;
		seasCO23 += soil_hete_CO2;
		FertAddNSA[3] += day_inFertN;
		FertAddCSA[3] += day_addmc;

		if (jday == jdseed[3])//calculate soil water at planting in top 15 and top 20cm
		{
			int za, layer15, layer20;
			layer15 = (0.15 / h[1] + 1);
			layer20 = (0.20 / h[1] + 1);
			for (int za = 1; za <= layer15; za++)
			{
				daySoilWater153 += water[24][za] * 1000.0;
			}
			for (int za = 1; za <= layer20; za++)
			{
				daySoilWater203 += water[24][za] * 1000.0;
			}
		}
	}
}

if(jday>=jdseed[1] && cropHarvestDay[1]==0 || jday>=jdseed[1] && jday<=cropHarvestDay[1])//HarvestYear
{
seasDay1_pDate_atemp += air_temp;
seasDay1_pDate_precip += precipitation;
seasDay1_pDate_wrunoff += day_runoff;
seasDay1_pDate_wleach +=(day_leach_water);
seasDay1_pDate_denit += total_dayDenit2;
seasDay1_pDate_N2O += day_soil_an_n2o;
seasDay1_pDate_NH3 += (day_soil_nh3+day_vol_nh3);
seasDay1_pDate_netNmin +=(day_N_mine - day_N_assim);
seasDay1_pDate_Nleach += (day_leach_NO3 + by_pass_no3+day_leach_urea);
seasDay1_pDate_irri += day_irri;
if(day_irri>0)
{countIrri+=1;}
seasDay1_pDate_trans += day_transp; 
seasDay1_pDate_evap += day_soil_ev;
seasPET += DayPET;
seasPETKC += DayPETCROP[1];
cropCHU += (1.8 * (min_temp - 4.4) + 3.3*(max_temp - 10.0) - 0.084 * (max_temp - 10) * 2) / 2;
if (air_temp >= 5.0 && PGI[1]<1.0) cropGDD += air_temp-5.0;
}

if (jday >= 121 && jday <= 304)//GS
{
	gs_N2O += day_soil_an_n2o;
	gs_precip += precipitation;
	gs_atemp += air_temp;
}
if (jday < 121)//NGS1
{
	ngs1_N2O += day_soil_an_n2o;
	ngs1_precip += precipitation;
	ngs1_atemp += air_temp;
}
if (jday > 304)//NGS2
{
	ngs2_N2O += day_soil_an_n2o;
	ngs2_precip += precipitation;
	ngs2_atemp += air_temp;
	}



if(jday>=182 && jday<=365)
{
seasDay182_365_atemp += air_temp;
seasDay182_365_precip += precipitation;
seasDay182_365_wrunoff += day_runoff;
seasDay182_365_wleach +=(day_leach_water);
seasDay182_365_denit += total_dayDenit2;
seasDay182_365_N2O += day_soil_an_n2o;
seasDay182_365_NH3 += (day_soil_nh3+day_vol_nh3);
seasDay182_365_netNmin += (	day_N_mine-day_N_assim);
seasDay182_365_Nleach += (day_leach_NO3 + by_pass_no3+day_leach_urea);
seasDay182_365_irri += day_irri;
seasDay182_365_trans += day_transp; 
seasDay182_365_evap += day_soil_ev;
}


	
	if(jday>=1 && jday<=129)
	{
	seasDay1_129_atemp += air_temp;
	seasDay1_129_precip += precipitation;
	seasDay1_129_wrunoff += day_runoff;
	seasDay1_129_wleach +=(day_leach_water); 
	seasDay1_129_N2O += day_soil_an_n2o;
	seasDay1_129_Nrunoff += day_runoff_N;
	seasDay1_129_Nleach +=	(day_leach_NO3 + by_pass_no3+day_leach_urea);
	seasDay1_129_NH3 += (day_soil_nh3+day_vol_nh3);
	}
	if(jday>=130 && jday<=365)
	{
	seasDay130_365_atemp += air_temp;
	seasDay130_365_precip += precipitation;
	seasDay130_365_wrunoff += day_runoff;
	seasDay130_365_wleach +=(day_leach_water); 
	seasDay130_365_N2O += day_soil_an_n2o;
	seasDay130_365_Nrunoff += day_runoff_N;
	seasDay130_365_Nleach +=	(day_leach_NO3 + by_pass_no3+day_leach_urea);
	seasDay130_365_NH3 += (day_soil_nh3+day_vol_nh3);
	}
	if(jday>=305 && jday<=365)
	{
	seasDay305_365_atemp += air_temp;
	seasDay305_365_precip += precipitation;
	seasDay305_365_wrunoff += day_runoff;
	seasDay305_365_wleach +=(day_leach_water); 
	seasDay305_365_N2O += day_soil_an_n2o;
	seasDay305_365_Nrunoff += day_runoff_N;
	seasDay305_365_Nleach +=	(day_leach_NO3 + by_pass_no3+day_leach_urea);
	seasDay305_365_NH3 += (day_soil_nh3+day_vol_nh3);
	}
	if(jday>=1 && jday<=304)
	{
	seasDay1_304_atemp += air_temp;
	seasDay1_304_precip += precipitation;
	seasDay1_304_wrunoff += day_runoff;
	seasDay1_304_wleach +=(day_leach_water); 
	seasDay1_304_N2O += day_soil_an_n2o;
	seasDay1_304_Nrunoff += day_runoff_N;
	seasDay1_304_Nleach +=	(day_leach_NO3 + by_pass_no3+day_leach_urea);
	seasDay1_304_NH3 += (day_soil_nh3+day_vol_nh3);
	}
	if(jday>=288 && jday<=365)
	{
	seasDay288_365_atemp += air_temp;
	seasDay288_365_precip += precipitation;
	seasDay288_365_wrunoff += day_runoff;
	seasDay288_365_wleach +=(day_leach_water); 
	seasDay288_365_N2O += day_soil_an_n2o;
	seasDay288_365_Nrunoff += day_runoff_N;
	seasDay288_365_Nleach +=	(day_leach_NO3 + by_pass_no3+day_leach_urea);
	seasDay288_365_NH3 += (day_soil_nh3+day_vol_nh3);
	}

//incorporated a new accumulator for annual senecence.
DayShootSenesN[1] = DayLeafSenesN[1] + DayStemSenesN[1];
yrShootSenesN[1] += DayShootSenesN[1];//accumulator for N 
if(HarvestDay[1]==(jday-1))yrShootSenesN[1] = 0.0;
totalSens1+=(DayLeafSenes[1] + DayStemSenes[1]);
totalSens2+=(DayLeafSenes[2] + DayStemSenes[2]);
totalSens3+=(DayLeafSenes[3] + DayStemSenes[3]);
if(totalSens1<0.00)totalSens1=0.0;
if(totalSens2<0.00)totalSens2=0.0;
if(totalSens3<0.00)totalSens3=0.0;
	day_soil_nh3 = 0.0;
	day_vol_nh3 = 0.0;    
	day_soil_an_n2o = 0.0;

	//day_co2 += day_C_mine;   // move heterotrophic CO2 into the reported flux
	//day_C_mine = 0.0f;       // optional: reset if it's only an accumulator

	yr_C_mine += day_C_mine;

	day_C_mine = 0.0;

    yr_minern += day_N_mine;
	day_N_mine = 0.0;

	day_N_assim = 0.0;

	yr_leach_hu += day_leachhu;    
	yr_leach_un += day_leachhu/rcnm;
	day_leachhu = 0.0;

//	yr_runoff_N += day_runoff_N;
	day_runoff_N = 0.0;

	yr_runoff_C += day_runoff_C;
	day_runoff_C = 0.0;

    //yr_leach_NO3 += (day_leach_NO3 + by_pass_no3);
	day_leach_NO3 = 0.0;
	yr_leach_urea += day_leach_urea;
	day_leach_urea = 0.0;

	yr_runoff_SOC += socmusle;
	yr_runoff_ION += nh4musle+no3musle;
	yr_runoff_P += day_runoff_P;//(OrgPmusle+AdsPmusle+LabPmusle);
	yr_leach_P += day_leach_P;
	day_leach_P = 0.0;

	by_pass_no3 = 0.0;

    //yr_leach_un = yr_leach_hu / rcnm;
    yr_leach_DOC += day_leach_DOC;
    //day_leach_DOC = 0.0;
    
	yr_balance_ch4 += day_balance_ch4;
	day_balance_ch4 = 0.0;
		
	//yr_leach_water += (day_leach_water);  
	day_leach_water = 0.0;
	  day_tile_water=0.0;
	
	yr_soil_ev += day_soil_ev + day_soilIce_ev;
	yr_total_ev += day_snow_ev + dfol_ev + day_soil_ev + day_pond_ev+day_soilIce_ev;
	day_soil_ev = 0.0;
	day_soilIce_ev = 0.0;

	yr_water_in += day_water_in; //m water
	day_water_in = 0.0;

	//if(crop[1]==0) 
//	{
	//	float RunoffF = (1.0 - clay[1]) * 0.38;
	//	WaterPool += day_runoff * RunoffF;//fallow year effect
	//	yr_runoff += day_runoff * (1.0-RunoffF);//0.7;
	//	yr_runoff += day_runoff;
//	}
//	else 
	//yr_runoff += day_runoff;
	day_runoff = 0.0;
	
	yr_pond_ev += day_pond_ev;
	day_pond_ev = 0.0;


	if(DayPETCROP[1]>0) //tests to see if DayPETCROP is calculated for growing season
	{
	yr_PETCROP+=DayPETCROP[1];
	}
	else //just adds DayPET;
	{
		yr_PETCROP+=DayPET;
	}


	yr_GWsuply += day_GWsuply;
	day_GWsuply=0.0;

	yr_shoot_CO2 += (sum_shoot_CO2 + sum_stem_CO2);
	sum_shoot_CO2=0.0;
	sum_stem_CO2=0.0;
	yr_CropGPP += dPlantBiomass;
	dPlantBiomass=0.0;
	yr_Psn += -Psn;
	Psn=0.0;
	yr_EcoCO2 += EcoCO2;
	EcoCO2=0.0;
	yr_NEE += NEE;
	NEE=0.0;

	yr_irri_N += day_irri_N;
	day_irri_N = 0.0;

	yr_rainN += day_inRainN;
	day_inRainN = 0.0;

	yr_sln += day_inLitterN;
	day_inLitterN = 0.0;

	yr_InputRoot_DOC += day_RootInput_DOC;

	yr_indirect_n2o += day_indirect_n2o;
	day_indirect_n2o = 0.0;

	yr_indirect_n2 += day_indirect_n2;
	day_indirect_n2 = 0.0;



}

void class_model::soc_distribution(float *CRB1, float* CRB2, float* newh)
{
    int i, l, qqq[21]={0,0}, Tq=0, accumL=0, BDL;
    float culdept[6], finaoc;//, accumC=0.0,accumN=0.0;

	culdept[0] = 0.0f;
    culdept[1] = 0.1f;
    culdept[2] = 0.2f;
    culdept[3] = 0.3f;
	culdept[4] = 0.4f;
	culdept[5] = 0.5f;
	BDL = (int)((float)q/20.0f);//was /5.0 for 50cm making 10 cm intervals BDL is used to decide layer interval for every 10 cm layer. 
	float remLayer=((float)q/20.0f);//cacluate partial layer remainder
	
	if ((remLayer - float(BDL)) > 0.5)
	{
	//	BDL += 1;  //
	}

	if(BDL*h[1])


	T_SOC = 0.0;

    for ( i = 1; i <= 20; i++ )
    {
		if(i<20) qqq[i] = (i * BDL);//(int)((culdept[i]-culdept[i-1]) / h[i]);//+1;	
		else qqq[i] = q;
		
		layerc[i] = 0.0;
		layern[i] = 0.0;
		LayerSoilWeight[i] = 0.0;
		accumL = 0;
			
		for ( l = Tq+1; l <= qqq[i]; l++ )
		{
			accumL ++;

			finaoc = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] 
				+ crhl[l] + crhr[l] + dphum[l] + inert_C[l] + doc[l] 
				+ FreezeDOC[l]+manurePool[l];//add manurePool
			layerc[i] += finaoc;
			//accumC += finaoc;			

			float Wson = (rcvl[l] / rcnrvl + rcl[l] / rcnrl + rcr[l] / rcnrr + CRB1[l] / rcnb + CRB2[l] / rcnb + crhl[l] / rcnh + crhr[l] / rcnh + dphum[l] / rcnm + inert_C[l] / PassiveCCN) + manurePool[l] / manurePoolCN;// +manurePool[l] / manurePoolCN;//add manurePool N
			layern[i] += Wson;
			
			LayerSoilWeight[i] += mmm[l];

			
			

		}

		topc[i] = layerc[i] / LayerSoilWeight[i]; //layerc[i] / (m * qqq[i]);
		topn[i] = layern[i] / LayerSoilWeight[i];

		Tq = qqq[i];

		T_SOC += layerc[i];//will be reported as EndSOC in multi_yearSummary
    }

	day_dSOC = T_SOC - old_T_SOC;
	old_T_SOC = T_SOC;
}

void class_model::MC_annu_accumu()
{
	
    yr_soil_co2 += day_co2;
	//yr_RootExude_co2 += root_dCO2; //day_RootExudate;
	day_co2 = 0.0;
	root_dCO2 = 0.0;

	//yr_RootDOC += day_RootDOC;
	//day_RootDOC = 0.0;

    yr_root_co2 += (day_rco2[1]+day_rco2[2]+day_rco2[3]);
	day_rco2[1]=0.0;
	day_rco2[2]=0.0;
	day_rco2[3]=0.0;
	
    yr_ch4 += day_ch4;
	day_ch4 = 0.0;
    //yr_dcn2o += day_soil_ae_n2o;
    //day_soil_ae_n2o = 0.0;
    //yr_dcno += day_soil_ae_no;
    //day_soil_ae_no = 0.0;
    yr_dnno += day_soil_an_no;
    day_soil_an_no = 0.0;
    yr_dnn2o += day_soil_an_n2o;
    day_soil_an_n2o = 0.0;
    yr_dnn2 += day_soil_n2;
    day_soil_n2 = 0.0;
    
    yr_soil_nh3 += (day_soil_nh3+day_vol_nh3);

	day_soil_nh3 = 0.0;
	day_vol_nh3 = 0.0;

    yr_plant_nh3 += (day_plant_nh3[1]+day_plant_nh3[2]+day_plant_nh3[3]);
	day_plant_nh3[1] = 0.0;
	day_plant_nh3[2] = 0.0;
	day_plant_nh3[3] = 0.0;

	yr_C_mine += day_C_mine;
	day_C_mine = 0.0;

    yr_minern += day_N_mine;
	day_N_mine = 0.0;

	//yr_assim += day_N_assim;
	day_N_assim = 0.0;

	yr_leach_hu += (day_leachhu);    
	yr_leach_un += day_leachhu/rcnm;
	day_leachhu = 0.0;

	yr_runoff_N += day_runoff_N;
	day_runoff_N = 0.0;

	yr_runoff_C += day_runoff_C;
	day_runoff_C= 0.0;

    yr_leach_NO3 += (day_leach_NO3 + by_pass_no3);
	day_leach_NO3 = 0.0;
	yr_leach_urea += day_leach_urea;
	day_leach_urea = 0.0;
	by_pass_no3 = 0.0;

    //yr_leach_un = yr_leach_hu / rcnm;
    yr_leach_DOC += day_leach_DOC;
    //day_leach_DOC = 0.0;
    //plantn[cwc] += day_nup;
    //if (crop[cwc]==20) liupt[cwc] = plantn[cwc];
	for(cwc=1; cwc<=CropNumbers; cwc++)
	{
		yr_uptaken[cwc] += day_nup[cwc];
		day_nup[cwc]=0.0;
	}
    //weedn += day_weednup;
	//yr_weedn += day_weednup;
	//day_weednup = 0.0;

	yr_balance_ch4 += day_balance_ch4;
	day_balance_ch4 = 0.0;
		
	yr_leach_water += (day_leach_water);  
	day_leach_water = 0.0;
	
	yr_soil_ev += day_soil_ev+day_soilIce_ev;
	yr_total_ev += day_snow_ev + dfol_ev + day_soil_ev + day_pond_ev+day_soilIce_ev;
	day_soil_ev = 0.0;
	day_soilIce_ev = 0.0;

	yr_water_in += day_water_in; //m water
	day_water_in = 0.0;

	yr_trans += day_transp; 
	for(cwc=1; cwc<=CropNumbers; cwc++)
	{
		crop_trans[cwc] += APT[cwc];//day_transp;
	}
	day_transp = 0.0;	
	
	if(crop[1]==0) 
	{
		float RunoffF = (1.0f - clay[1]) * 0.38f;
		WaterPool += day_runoff * RunoffF;//fallow year effect
		yr_runoff += day_runoff * (1.0f-RunoffF);//0.7;
	}
	else yr_runoff += day_runoff;
	day_runoff = 0.0;

	yr_pond_ev += day_pond_ev;
	day_pond_ev = 0.0;

	//yr_DNassimN += day_DNassimN;
	//day_DNassimN = 0.0;

	//yr_FrostBio += day_frostMicrobe;
	//day_frostMicrobe = 0.0;

	yr_GWsuply += day_GWsuply;
	day_GWsuply=0.0;

	yr_shoot_CO2 += (sum_shoot_CO2+ sum_stem_CO2);
	sum_shoot_CO2=0.0;
	sum_stem_CO2=0.0;
	yr_CropGPP += dPlantBiomass;
	dPlantBiomass=0.0;
	yr_Psn += -Psn;
	Psn=0.0;
	yr_EcoCO2 += EcoCO2;
	EcoCO2=0.0;
	yr_NEE += NEE;
	NEE=0.0;

	yr_irri_N += day_irri_N;
	day_irri_N = 0.0;

	yr_rainN += day_inRainN;
	day_inRainN = 0.0;

	yr_soilN_from_Nfixation += (day_soilN_from_Nfixation[1]+day_soilN_from_Nfixation[2]+day_soilN_from_Nfixation[3]);
	day_soilN_from_Nfixation[1] = 0.0;
	day_soilN_from_Nfixation[2] = 0.0;
	day_soilN_from_Nfixation[3] = 0.0;



}



