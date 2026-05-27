#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "math.h"

#ifdef MANURE 
extern class_manure MData;

class_model *DNDC;

float DungCN[7]={0.0, 16.0, 16.0, 16.0, 18.5, 3.1, 7.9}; //dung C/N ratio for dairy cattle, beef, veal, pig, sheep, foultry
float UrineCN[7]={0.0, 1.25, 1.25, 1.25, 4.24, 4.0, 4.0};//urine C/N ratio 
float DungH2O[7]={0.0, 0.8, 0.8, 0.8, 0.82, 0.68, 0.8}; //water fraction of dung
float UrineH2O[7]={0.0, 10.0, 10.0, 10.0, 3.3, 0.0, 0.0}; //kg water/head/day in urine
float UrineNF[7]={0.0, 0.5, 0.5, 0.5, 0.786, 0.7, 0.0}; //urine fraction of total waste N
float MilkNc[7]={0.0, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005};// N concentration in milk by weiht, kg N/kg milk
float MeatNc[7]={0.0, 0.022, 0.022, 0.022, 0.022, 0.022, 0.024};// N concentration in meat by weight, kg N/kg meat

float old_HouseC, old_HouseN, new_HouseC, new_HouseN;
float old_DigesterC, old_DigesterN, old_DigesterP, new_DigesterC, new_DigesterN, new_DigesterP;
float old_LagoonC, old_LagoonN, new_LagoonC, new_LagoonN;
float CN_partition(float addC, float addN, float rcnrr, float rcnh);

void class_manure::HouseManureProduct(int FN)
{
	int i;
	float MilkN, MeatN, hd_ManureC, hd_ManureWater, ManureCN, ManureC;
	float hd_ManureN, hd_UrineN, hd_DungN, hd_DungC, hd_DungDM, hd_DungWater, hd_UrineC, hd_UrineWater;
	float day_meat, day_milk, ManureN, MilkP, MeatP, hd_UrineP, hd_DungP;
	
	MData.day_intake_C = 0.0;
	MData.day_intake_N = 0.0;
	MData.day_intake_P = 0.0;
	MData.day_milk_N=0.0;
	MData.day_milk_C=0.0;
	MData.day_milk_P=0.0;
	MData.day_meat_N=0.0;
	MData.day_meat_C=0.0;
	MData.day_meat_P=0.0;
	
	MData.day_milk_product=0.0;
	MData.day_urine_water=0.0;
	MData.day_dung_water=0.0;
	
	MData.mm_UrineN[FN] =0.0;//kg N/day
	MData.mm_UrineC[FN] =0.0;//kg C/day
	MData.mm_UrineP[FN] =0.0;//kg P/day
	MData.mm_DungN[FN] =0.0;//kg N/day
	MData.mm_DungC[FN] =0.0;	//kg C/day
	MData.mm_DungP[FN] =0.0;
	MData.mm_DungWater[FN] =0.0;//kg water/day
	MData.mm_UrineWater[FN] =0.0;
	MData.animal_co2 = 0.0;

	//Milk and meat production per animal per day
	MData.mm_FeedC[FN] = MData.mm_FeedRate[FN] * 0.4; // kg dry matter/animal/day - kg C/animal/day
	MData.mm_FeedN[FN] = MData.mm_FeedProtein[FN] * 0.01 * MData.mm_FeedRate[FN] / 6.25; // kg N/animal/day
	MData.mm_FeedP[FN] = MData.mm_FeedTP[FN] * 0.01 * MData.mm_FeedRate[FN]; // kg P/animal/day

	MData.mm_FeedNDF[FN] = MData.mm_FeedNDFP[FN] * 0.01 * MData.mm_FeedRate[FN]; //kg NDF/animal/day
	MData.mm_FeedADF[FN] = MData.mm_FeedADFP[FN] * 0.01 * MData.mm_FeedRate[FN]; //kg ADF/animal/day
	MData.mm_FeedLignin[FN] = MData.mm_FeedLigninP[FN] * 0.01 * MData.mm_FeedRate[FN]; //kg Lignin/animal/day
	MData.mm_FeedFAT[FN] = MData.mm_FeedFATP[FN] * 0.01 * MData.mm_FeedRate[FN]; //kg FAT/animal/day
	MData.mm_FeedASH[FN] = MData.mm_FeedASHP[FN] * 0.01 * MData.mm_FeedRate[FN]; //kg ASH/animal/day

	if(MData.mm_AnimalType[FN]==1) //lactating cow
	{
		MilkN = MData.mm_FeedN[FN] * 0.18;//0.25; // Powell et al, 2006
		MeatN = MData.mm_FeedN[FN] * 0.0356;//0.05		
		MData.mm_MilkProduct[FN] = MilkN / 0.003; // milk production kg/animal/day, 0.005
		MilkP = MData.mm_FeedP[FN] * 0.253;//0.367;//milk P, kg P/cow/day
		MeatP = MData.mm_FeedP[FN] * 0.0386;//meat P, kg P/cow/day
		hd_UrineP = MData.mm_FeedP[FN] * 0.011;//urine P, kg P/cow/day
		hd_DungP = MData.mm_FeedP[FN] * 0.6974;//feces P, kg P/cow/day

	}
	else
	{
		MilkN = 0.0; // Powell et al, 2006
		MeatN = MData.mm_FeedN[FN] * 0.214;//0.3;	
		MData.mm_MilkProduct[FN] = 0.0;
		MilkP = 0.0;
		MeatP = MData.mm_FeedP[FN] * 0.19;//meat P, kg P/cow/day
		hd_UrineP = MData.mm_FeedP[FN] * 0.02;//urine P, kg P/cow/day
		hd_DungP = MData.mm_FeedP[FN] * 0.79;//feces P, kg P/cow/day

		//Sheep hair contains N 16% of DM
	}
	MData.mm_MeatProduct[FN] = MeatN / 0.0484;//0.022; // meat production, kg/animal/day

	//enteric N2O£¬ 0.5g N2O-N/kg feed-N; 0.2% of intake N
	MData.head_enteric_n2o = 0.00001 * MData.mm_FeedN[FN];//0.0005; 0.9 * 0.001981 * MData.mm_FeedN[FN] / 0.225333;// * MData.mm_AnimalHeads[FN]; //kg N/day/head

	//manure production per animal per day
	hd_ManureN = MData.mm_FeedN[FN] - (MilkN + MeatN + MData.head_enteric_n2o);//kg N/head/day
	
	hd_UrineN = UrineNF[MData.mm_AnimalType[FN]] * hd_ManureN;//kg N/head/day, Broderick 2003; Wattiaux and Karg 2004
	//hd_DungN = (1.0 - UrineNF[MData.mm_AnimalType[FN]]) * hd_ManureN;//kg N/head/day
	hd_DungN = hd_ManureN - hd_UrineN;//kg N/head/day
			
	hd_DungC = hd_DungN * DungCN[MData.mm_AnimalType[FN]];//kg C/head/day
	hd_DungDM = hd_DungC / 0.58;// kg dry matter/head/day
	hd_UrineC = hd_UrineN * UrineCN[MData.mm_AnimalType[FN]];//kg C/head/day
		
	hd_ManureC = hd_DungC + hd_UrineC;//kg C/head/day
	ManureCN = hd_ManureC / hd_ManureN;//kg N/head/day
		
	hd_DungWater = hd_DungDM / (1.0 - DungH2O[MData.mm_AnimalType[FN]]) * DungH2O[MData.mm_AnimalType[FN]];//kg water/head/day
	hd_UrineWater = UrineH2O[MData.mm_AnimalType[FN]];//kg water/head/day
	hd_ManureWater = hd_DungWater + hd_UrineWater;//kg water/head/day

	//manure production per farm per day
	ManureN = hd_ManureN * MData.mm_AnimalHeads[FN];
	ManureC = hd_ManureC * MData.mm_AnimalHeads[FN];
	MData.mm_DungDM = hd_DungDM * MData.mm_AnimalHeads[FN];
	MData.mm_ManureWater[FN] = hd_ManureWater * MData.mm_AnimalHeads[FN];
	//MData.day_enteric_n2o[FN] = head_enteric_n2o * MData.mm_AnimalHeads[FN]; //kg N/day
			
	MData.mm_UrineN[FN] = hd_UrineN * MData.mm_AnimalHeads[FN];//kg N/day
	MData.mm_UrineC[FN] = hd_UrineC * MData.mm_AnimalHeads[FN];//kg C/day
	MData.mm_DungN[FN] = hd_DungN * MData.mm_AnimalHeads[FN];//kg N/day
	MData.mm_DungC[FN] = hd_DungC * MData.mm_AnimalHeads[FN];	//kg C/day
	MData.mm_UrineP[FN] = hd_UrineP * MData.mm_AnimalHeads[FN];//kg P/day
	MData.mm_DungP[FN] = hd_DungP * MData.mm_AnimalHeads[FN];//kg P/day

	MData.mm_DungWater[FN] = hd_DungWater * MData.mm_AnimalHeads[FN];//kg water/day
	MData.mm_UrineWater[FN] = hd_UrineWater * MData.mm_AnimalHeads[FN];//kg water/day	
	MData.ManureCapacity = DungH2O[MData.mm_AnimalType[FN]];
		
	MData.day_intake_C = MData.mm_FeedC[FN] * MData.mm_AnimalHeads[FN];
	MData.day_intake_N = MData.mm_FeedN[FN] * MData.mm_AnimalHeads[FN];
	MData.day_intake_P = MData.mm_FeedP[FN] * MData.mm_AnimalHeads[FN];
		
	MData.day_milk_N = MilkN * MData.mm_AnimalHeads[FN];
	MData.day_milk_C = MilkN * MData.mm_AnimalHeads[FN] / MilkNc[MData.mm_AnimalType[FN]] * 0.05 * 0.4;
	
	MData.day_meat_N = MeatN * MData.mm_AnimalHeads[FN];
	MData.day_meat_C = MeatN * MData.mm_AnimalHeads[FN] / MeatNc[MData.mm_AnimalType[FN]] * 0.2 * 0.4;
	MData.day_milk_P = MilkP * MData.mm_AnimalHeads[FN];
	MData.day_meat_P = MeatP * MData.mm_AnimalHeads[FN];
	
	MData.day_milk_product = MData.mm_MilkProduct[FN]*MData.mm_AnimalHeads[FN];//kg milk/MData.day
	MData.day_urine_water = MData.mm_UrineWater[FN];
	MData.day_dung_water = MData.mm_DungWater[FN];

	  
	float KKanimal_co2 = (MData.mm_FeedC[FN] * MData.mm_AnimalHeads[FN] - 
		MilkN * MData.mm_AnimalHeads[FN] / MilkNc[MData.mm_AnimalType[FN]] * 0.05 * 0.4 -
		MeatN * MData.mm_AnimalHeads[FN] / MeatNc[MData.mm_AnimalType[FN]] * 0.2 * 0.4 -
		ManureC - MData.DAY_enteric_ch4[FN]);

	MData.animal_co2 = KKanimal_co2;//MData.mm_FeedC[FN] * 0.4805193 * MData.mm_AnimalHeads[FN];

	//MData.animal_co2 -= MData.DAY_enteric_ch4[FC];
	//MData.yr_enteric_co2 -= MData.DAY_enteric_ch4[FC];

	//float ddCC = MData.animal_co2 - KKanimal_co2;
	//MData.mm_DungC[FN] -= ddCC;

	MData.yr_enteric_co2 += MData.animal_co2;
	MData.yr_intake_C += MData.day_intake_C;
	MData.yr_intake_N += MData.day_intake_N;
	MData.yr_intake_P += MData.day_intake_P;
	MData.yr_milk_N += MData.day_milk_N;
	MData.yr_milk_C += MData.day_milk_C;
	MData.yr_milk_P += MData.day_milk_P;
	MData.yr_meat_N += MData.day_meat_N;
	MData.yr_meat_C += MData.day_meat_C;
	MData.yr_meat_P += MData.day_meat_P;
	//MData.yr_animal_CO2 += MData.animal_co2;
	MData.yr_milk_product += MData.day_milk_product;

	MData.yr_urine_C += MData.mm_UrineC[FN];
	MData.yr_urine_N += MData.mm_UrineN[FN];
	MData.yr_dung_C += MData.mm_DungC[FN];
	MData.yr_dung_N += MData.mm_DungN[FN];
	MData.yr_urine_P += MData.mm_UrineP[FN];
	MData.yr_dung_P += MData.mm_DungP[FN];
	MData.yr_urine_water += MData.day_urine_water;
	MData.yr_dung_water += MData.day_dung_water;
	
	
	
	
}

void class_manure::HouseManureOccumulation(int FN, int GN, int q, int jday, float rcnrvl, float rcnrl, float rcnrr, 
		   float rcnh, float rcnb, float *urea, float *doc, float *rcvl, 
		   float *rcl, float *rcr, float *crhl, float *crhr, float *CRB1, float *CRB2, float *dphum, double water[25][250],
		   float rcnm, float *soc, float *son, float *SIN, float *nh4, float *no3, float *no2, float *no, float *n2o,
		   float *n2, float *nh3, float *co2, float *sop, float *OrgP, float *LabP, float *ComP,
		   float precipitation)
{
	float AddC=0.0, AddN=0.0, ManureAddCN, Free_N, solid_C, solid_CN, solid_MN, AddCN;
	int i, j;

	Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

/*	if(MData.mm_GroundSurface[FN]==0) //slatted floor with gutter, urine, DOC, water go to gutter
	{
		float wb = 0.8;
		urea[q+8] += MData.mm_UrineN[FN] * wb;
		doc[q+8] += MData.mm_UrineC[FN] * wb;
		water[1][q+8] += (MData.mm_UrineWater[FN] + MData.mm_DungWater[FN]*wb);
		
		urea[GN] += MData.mm_UrineN[FN] * (1.0-wb);
		doc[GN] += MData.mm_UrineC[FN] * (1.0-wb);
		water[1][GN] += (MData.mm_DungWater[FN]*(1.0-wb));
	}
	else if(MData.mm_GroundSurface[FN]==1) //concrete floor*/
	{
		urea[GN] += MData.mm_UrineN[FN];
		doc[GN] += MData.mm_UrineC[FN];
		water[1][GN] += (MData.mm_DungWater[FN]+MData.mm_UrineWater[FN]);//kg water/feedlot

		if(MData.mm_GroundSurface[FN]==3)
		{
			float AddRainWater = precipitation * MData.mm_GroundArea[FN] * 1000.0;
			water[1][GN] += AddRainWater;
		}

		urea[q+8] = 0.0;
		doc[q+8] = 0.0;
		water[1][q+8] = 0.0;
	}	
/*	else if(MData.mm_GroundSurface[FN]==2) //sub-floor (only gutter)
	{
		urea[q+8] += MData.mm_UrineN[FN];
		doc[q+8] += MData.mm_UrineC[FN];
		water[1][q+8] += (MData.mm_UrineWater[FN] + MData.mm_DungWater[FN]);
	}
	else if(MData.mm_GroundSurface[FN]==3) //outdoor pen with bare soil
	{
		urea[GN] += MData.mm_UrineN[FN];
		doc[GN] += MData.mm_UrineC[FN];
		water[1][GN] += (MData.mm_DungWater[FN]+MData.mm_UrineWater[FN]);//kg water/feedlot

		if(precipitation>0.0)
		{
			float AddRainWater = precipitation * MData.mm_GroundArea[FN] * 1000.0;
			water[1][GN] += AddRainWater;//kg water/lot
		}

		urea[q+8] = 0.0;
		doc[q+8] = 0.0;
		water[1][q+8] = 0.0;		
	}
	else
	{
		AfxMessageBox("Error for defining floor type");
		exit(0);
	}
*/	
	//Partition feces C and N into ressistant litter and humads
	AddC = MData.mm_DungC[FN];
	AddN = MData.mm_DungN[FN];

	float Nh, Nl, Ch, Cl, AddH;
	float CNl = rcnrr, CNh = rcnh;

	Nh = (CNl * AddN - AddC) / (CNl - CNh);
	Nl = AddN - Nh;
	Cl = CNl * Nl;
	Ch = CNh * Nh;

	AddH = Ch;
		
/*	if(MData.mm_GroundSurface[FN]==0) //slatted floor with gutter
	{
		float wb = 0.2;
		crhl[q+8] += 0.4*AddH*wb; 
		crhr[q+8] += 0.4*AddH*wb;
		CRB1[q+8] += 0.1*AddH*wb;
		CRB2[q+8] += 0.1*AddH*wb;
		rcr[q+8] += Cl*wb;

		crhl[GN] += 0.4*AddH*(1.0-wb); 
		crhr[GN] += 0.4*AddH*(1.0-wb);
		CRB1[GN] += 0.1*AddH*(1.0-wb);
		CRB2[GN] += 0.1*AddH*(1.0-wb);
		rcr[GN] += Cl*(1.0-wb);

		LabP[GN] += MData.mm_UrineP[FN];
		OrgP[GN] += MData.mm_DungP[FN];
	}
	else if(MData.mm_GroundSurface[FN]==1||MData.mm_GroundSurface[FN]==3) //concrete floor or outdoor pen with bare soil*/
	{
		crhl[GN] += 0.4*AddH; 
		crhr[GN] += 0.4*AddH;
		CRB1[GN] += 0.1*AddH;
		CRB2[GN] += 0.1*AddH;
		rcr[GN] += Cl;
		LabP[GN] += MData.mm_UrineP[FN];
		OrgP[GN] += MData.mm_DungP[FN];
	}
/*	else if(MData.mm_GroundSurface[FN]==2) //sub-floor (only gutter)
	{
		crhl[q+8] += 0.4*AddH; 
		crhr[q+8] += 0.4*AddH;
		CRB1[q+8] += 0.1*AddH;
		CRB2[q+8] += 0.1*AddH;
		LabP[q+8] += MData.mm_UrineP[FN];
		OrgP[q+8] += MData.mm_DungP[FN];
		rcr[q+8] += Cl;
	}
	else
	{
		AfxMessageBox("Error for defining floor type");
		exit(0);
	}
*/
/*	float TTTN1, TTTN2, T1N, T2N;
	
	T1N = Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

	T2N = Total_SOCSON(q+8, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
				 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);

	TTTN1 = T1N + T2N;

	TTTN2 = MData.mm_UrineN[FN] + MData.mm_DungN[FN];*/

	//bedding material partitioning
	if(MData.mm_BedApplications>0.0)
	{
		int BF = jday%(int)MData.mm_BedApplications;
		if(BF==0&&(MData.mm_BedType==1||MData.mm_BedType==2||MData.mm_BedType==3))
		{		
			float AddC1, AddC2, AddC3, dInertC;
			AddC = MData.mm_BedAmount*0.4;
			AddCN = MData.mm_BedCNN;

			MData.day_bed_C += AddC;
			MData.day_bed_N += AddC/AddCN;

			MData.yr_bed_C += AddC;
			MData.yr_bed_N += AddC/AddCN;

			DNDC->alloc_litter_into_pools(&AddCN, &AddC, 2, &AddC1, &AddC2, &AddC3, &dInertC, 1, rcnrvl, rcnrl, rcnrr, nh4);

			if(MData.mm_GroundSurface[FN]==2) //sub-floor (only gutter)
			{
				rcvl[q+8] += AddC1;
				rcl[q+8] += AddC2;
				rcr[q+8] += AddC3;
			}
			else
			{
				rcvl[GN] += AddC1;
				rcl[GN] += AddC2;
				rcr[GN] += AddC3;
			}
		}
	}
		
	

	//Total_SOCSON(GN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
	//			 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, 
	//			 sop,OrgP, LabP, ComP);
	
}

float CN_partition(float addC, float addN, float rcnrr, float rcnh)
{
	float x,y;
	y = (rcnrr*addN - addC) / (rcnrr-rcnh);
	x = addN - y;

	return(y);
}


void class_manure::StorageManureRemoval(int FN, int GN, int q, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
								 float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
								 float *CRB1, float *CRB2, float *crhl, float *crhr, float *dphum, float *doc, 
								 float *nh4, float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, 
								 float *urea, int jday, float *co2, float *sph, double water[25][250],
								 float *day_wfps, float *temp, float air_temp,
								 float *day_addmc, float *yr_addmc, float *yr_addmn, float *day_inManureN,
								 float *day_farm_to_field_N, float *day_farm_to_field_C, float *day_farm_to_field_H2O,
								 int scale, float *sop, float *OrgP, float *LabP, float *ComP, float *day_farm_to_field_P,
								 int j, float *ToField)
{
	float CTF[24]={0.0,0.0}, ToLagoon[24]={0.0,0.0}, ToMarket[24]={0.0,0.0}, ToDigester[24]={0.0,0.0};
	float Remain[24]={0.0,0.0};
	float RemovedC=0.0, RemovedN=0.0, RemovedWater=0.0, RemovedP=0.0;
	
	//removal of manure from compost, lagoon or digester to field
	if(MData.m_ToField[FN][j]>0.0)
	{
		CTF[1] = MData.m_ToField[FN][j] * rcvl[GN];
		CTF[2] = MData.m_ToField[FN][j] * rcl[GN];
		CTF[3] = MData.m_ToField[FN][j] * rcr[GN];
		CTF[4] = MData.m_ToField[FN][j] * CRB1[GN];
		CTF[5] = MData.m_ToField[FN][j] * CRB2[GN];
		CTF[6] = MData.m_ToField[FN][j] * crhl[GN];
		CTF[7] = MData.m_ToField[FN][j] * crhr[GN];
		CTF[8] = MData.m_ToField[FN][j] * dphum[GN];
		CTF[9] = MData.m_ToField[FN][j] * OrgP[GN];
		CTF[10] = MData.m_ToField[FN][j] * LabP[GN];
		CTF[11] = MData.m_ToField[FN][j] * ComP[GN];
		CTF[12] = MData.m_ToField[FN][j] * nh4[GN];
		CTF[13] = MData.m_ToField[FN][j] * no3[GN];
		CTF[14] = MData.m_ToField[FN][j] * no2[GN];
		CTF[15] = MData.m_ToField[FN][j] * no[GN];
		CTF[16] = MData.m_ToField[FN][j] * n2o[GN];
		CTF[17] = MData.m_ToField[FN][j] * n2[GN];
		CTF[18] = MData.m_ToField[FN][j] * nh3[GN];	
		CTF[19] = MData.m_ToField[FN][j] * urea[GN];
		CTF[20] = MData.m_ToField[FN][j] * co2[GN];
		CTF[21] = MData.m_ToField[FN][j] * doc[GN];
		CTF[22] = MData.m_ToField[FN][j] * water[1][GN];
		//CTF[18] = MData.m_ToField[FN][j] * sph[GN];
		

		ToField[1] += CTF[1];
		ToField[2] += CTF[2];
		ToField[3] += CTF[3];
		ToField[4] += CTF[4];
		ToField[5] += CTF[5];
		ToField[6] += CTF[6];
		ToField[7] += CTF[7];
		ToField[8] += CTF[8];
		ToField[9] += CTF[9];
		ToField[10] += CTF[10];
		ToField[11] += CTF[11];
		ToField[12] += CTF[12];
		ToField[13] += CTF[13];
		ToField[14] += CTF[14];
		ToField[15] += CTF[15];
		ToField[16] += CTF[16];
		ToField[17] += CTF[17];
		ToField[18] += CTF[18];
		ToField[19] += CTF[19];
		ToField[20] += CTF[20];
		ToField[21] += CTF[21];
		ToField[22] += CTF[22];

		
		RemovedC = (CTF[1]+CTF[2]+CTF[3]+CTF[4]+CTF[5]+CTF[6]+CTF[7]+CTF[8]+CTF[20]+CTF[21]);	
		RemovedN = (CTF[1]/rcnrvl +CTF[2]/rcnrl +CTF[3]/rcnrr+CTF[4]/rcnb +CTF[5]/rcnb +
					CTF[6]/rcnh +CTF[7]/rcnh +CTF[8]/rcnm + CTF[12]+CTF[13]+CTF[14]+CTF[15]+CTF[16]+CTF[17]+CTF[18]+CTF[19]);
		RemovedWater = CTF[22];
		RemovedP = (CTF[9]+CTF[10]+CTF[11]);

		if(GN==(q+4)) //manure revoved from compost to field
		{
			MData.Compost_to_field_C = RemovedC;
			MData.Compost_to_field_N = RemovedN;		
			MData.Compost_to_field_H2O = RemovedWater;
			MData.yr_Compost_to_field_N += MData.Compost_to_field_N;
			MData.yr_Compost_to_field_C += MData.Compost_to_field_C;
			MData.yr_Compost_to_field_H2O += RemovedWater;
			MData.yr_ManureN_toField += MData.Compost_to_field_N;
			MData.Compost_to_field_P = RemovedP;
			MData.yr_Compost_to_field_P += MData.Compost_to_field_P;

			*day_farm_to_field_N += MData.Compost_to_field_N;
			*day_farm_to_field_C += MData.Compost_to_field_C;
			*day_farm_to_field_H2O += MData.Compost_to_field_H2O;
			*day_farm_to_field_P += MData.Compost_to_field_P;
		}
	
		if(GN==(q+5)) //manure revoved from lagoon to field
		{
			MData.Lagoon_to_field_C = RemovedC;
			MData.Lagoon_to_field_N = RemovedN;		
			MData.Lagoon_to_field_H2O = RemovedWater;
			MData.Lagoon_to_field_P = RemovedP;
			MData.yr_Lagoon_to_field_N += MData.Lagoon_to_field_N;
			MData.yr_Lagoon_to_field_C += MData.Lagoon_to_field_C;
			MData.yr_Lagoon_to_field_H2O += RemovedWater;
			MData.yr_Lagoon_to_field_P += MData.Lagoon_to_field_P;

			MData.yr_ManureN_toField += MData.Lagoon_to_field_N;			

			*day_farm_to_field_N += MData.Lagoon_to_field_N;
			*day_farm_to_field_C += MData.Lagoon_to_field_C;
			*day_farm_to_field_H2O += MData.Lagoon_to_field_H2O;
			*day_farm_to_field_P += MData.Lagoon_to_field_P;
		}
	
		if(GN==(q+6)) //manure revoved from digester to field
		{
			MData.Digester_to_field_C = RemovedC;
			MData.Digester_to_field_N = RemovedN;		
			MData.Digester_to_field_H2O = RemovedWater;
			MData.Digester_to_field_P = RemovedP;

			MData.yr_digester_to_field_N += MData.Digester_to_field_N;
			MData.yr_digester_to_field_C += MData.Digester_to_field_C;
			MData.yr_digester_to_field_H2O += RemovedWater;
			MData.yr_digester_to_field_P += MData.Digester_to_field_P;

			MData.yr_ManureN_toField += MData.Digester_to_field_N;			

			*day_farm_to_field_N += MData.Digester_to_field_N;
			*day_farm_to_field_C += MData.Digester_to_field_C;
			*day_farm_to_field_H2O += MData.Digester_to_field_H2O;
			*day_farm_to_field_P += MData.Digester_to_field_P;
		}		
	}//end of removal to field

	if(GN==(q+6))//Removal from digester 
	{
		if(MData.m_ToMarket[FN][j]>0.0)// Remove from digester to lagoon
		{
			ToLagoon[1] = MData.m_ToMarket[FN][j] * rcvl[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[2] = MData.m_ToMarket[FN][j] * rcl[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[3] = MData.m_ToMarket[FN][j] * rcr[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[4] = MData.m_ToMarket[FN][j] * CRB1[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[5] = MData.m_ToMarket[FN][j] * CRB2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[6] = MData.m_ToMarket[FN][j] * crhl[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[7] = MData.m_ToMarket[FN][j] * crhr[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[8] = MData.m_ToMarket[FN][j] * dphum[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[9] = MData.m_ToMarket[FN][j] * OrgP[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[10] = MData.m_ToMarket[FN][j] * LabP[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[11] = MData.m_ToMarket[FN][j] * ComP[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[12] = MData.m_ToMarket[FN][j] * nh4[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[13] = MData.m_ToMarket[FN][j] * no3[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[14] = MData.m_ToMarket[FN][j] * no2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[15] = MData.m_ToMarket[FN][j] * no[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[16] = MData.m_ToMarket[FN][j] * n2o[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[17] = MData.m_ToMarket[FN][j] * n2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[18] = MData.m_ToMarket[FN][j] * nh3[GN] / MData.m_ManureRemoveFrequency[FN];	
			ToLagoon[19] = MData.m_ToMarket[FN][j] * urea[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[20] = MData.m_ToMarket[FN][j] * co2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[21] = MData.m_ToMarket[FN][j] * doc[GN] / MData.m_ManureRemoveFrequency[FN];
			ToLagoon[22] = MData.m_ToMarket[FN][j] * water[1][GN] / MData.m_ManureRemoveFrequency[FN];		

			/////////////////////////////////////////// to lagoon
			int LN = q+5;//lagoon

			/*old_DigesterN = Total_SOCSON(LN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
					 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
			old_DigesterC = MData.ttc;
			old_DigesterP = MData.ttp;*/

			rcvl[LN] += ToLagoon[1];
			rcl[LN] += ToLagoon[2];
			rcr[LN] += ToLagoon[3] ;
			CRB1[LN] += ToLagoon[4] ;
			CRB2[LN] += ToLagoon[5] ;
			crhl[LN] += ToLagoon[6]; 
			crhr[LN] += ToLagoon[7] ;
			dphum[LN] += ToLagoon[8] ;

			OrgP[LN] += ToLagoon[9];
			LabP[LN] += ToLagoon[10];
			ComP[LN] += ToLagoon[11];

			nh4[LN] += ToLagoon[12] ;
			no3[LN] += ToLagoon[13] ;
			no2[LN] += ToLagoon[14] ;
			no[LN] += ToLagoon[15] ;
			n2o[LN] += ToLagoon[16] ;
			n2[LN] += ToLagoon[17] ;
			nh3[LN] += ToLagoon[18] ;
			urea[LN] += ToLagoon[19];
			co2[LN] += ToLagoon[20] ;
			doc[LN] += ToLagoon[21];		
			water[1][LN] += ToLagoon[22];						
		
			/*new_DigesterN = Total_SOCSON(LN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
					 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
			new_DigesterC = MData.ttc;
			new_DigesterP = MData.ttp;*/

			MData.Digester_to_lagoon_C = (ToLagoon[1]+ToLagoon[2]+ToLagoon[3]+ToLagoon[4]+ToLagoon[5]+ToLagoon[6]+ToLagoon[7]+ToLagoon[8]+ToLagoon[20]+ToLagoon[21]);	
			MData.Digester_to_lagoon_N = (ToLagoon[1]/rcnrvl +ToLagoon[2]/rcnrl +ToLagoon[3]/rcnrr+ToLagoon[4]/rcnb +ToLagoon[5]/rcnb +
					ToLagoon[6]/rcnh +ToLagoon[7]/rcnh +ToLagoon[8]/rcnm + ToLagoon[12]+ToLagoon[13]+ToLagoon[14]+ToLagoon[15]+ToLagoon[16]+ToLagoon[17]+ToLagoon[18]+ToLagoon[19]);
			MData.Digester_to_lagoon_H2O = ToLagoon[22];
			MData.Digester_to_lagoon_P = (ToLagoon[9]+ToLagoon[10]+ToLagoon[11]);

			/*MData.Digester_to_lagoon_C = new_DigesterC - old_DigesterC;
			MData.Digester_to_lagoon_N = new_DigesterN - old_DigesterN;
			MData.Digester_to_lagoon_H2O = ToLagoon[22];
			MData.Digester_to_lagoon_P = new_DigesterP - old_DigesterP;*/

			MData.yr_digester_to_lagoon_C += MData.Digester_to_lagoon_C;
			MData.yr_digester_to_lagoon_N += MData.Digester_to_lagoon_N;
			MData.yr_digester_to_lagoon_H2O += MData.Digester_to_lagoon_H2O;
			MData.yr_digester_to_lagoon_P += MData.Digester_to_lagoon_P;
		}

		if(MData.m_Remain[FN][j]>0.0)//remove from digester to market
		{
			ToMarket[1] = MData.m_Remain[FN][j] * rcvl[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[2] = MData.m_Remain[FN][j] * rcl[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[3] = MData.m_Remain[FN][j] * rcr[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[4] = MData.m_Remain[FN][j] * CRB1[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[5] = MData.m_Remain[FN][j] * CRB2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[6] = MData.m_Remain[FN][j] * crhl[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[7] = MData.m_Remain[FN][j] * crhr[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[8] = MData.m_Remain[FN][j] * dphum[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[9] = MData.m_Remain[FN][j] * OrgP[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[10] = MData.m_Remain[FN][j] * LabP[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[11] = MData.m_Remain[FN][j] * ComP[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[12] = MData.m_Remain[FN][j] * nh4[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[13] = MData.m_Remain[FN][j] * no3[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[14] = MData.m_Remain[FN][j] * no2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[15] = MData.m_Remain[FN][j] * no[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[16] = MData.m_Remain[FN][j] * n2o[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[17] = MData.m_Remain[FN][j] * n2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[18] = MData.m_Remain[FN][j] * nh3[GN] / MData.m_ManureRemoveFrequency[FN];	
			ToMarket[19] = MData.m_Remain[FN][j] * urea[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[20] = MData.m_Remain[FN][j] * co2[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[21] = MData.m_Remain[FN][j] * doc[GN] / MData.m_ManureRemoveFrequency[FN];
			ToMarket[22] = MData.m_Remain[FN][j] * water[1][GN] / MData.m_ManureRemoveFrequency[FN];		

			/////////////////////////////////////////// to market
			MData.Digester_to_market_C = (ToMarket[1]+ToMarket[2]+ToMarket[3]+ToMarket[4]+ToMarket[5]+ToMarket[6]+ToMarket[7]+ToMarket[8]+ToMarket[20]+ToMarket[21]);	
			MData.Digester_to_market_N = (ToMarket[1]/rcnrvl +ToMarket[2]/rcnrl +ToMarket[3]/rcnrr+ToMarket[4]/rcnb +ToMarket[5]/rcnb +
					ToMarket[6]/rcnh +ToMarket[7]/rcnh +ToMarket[8]/rcnm + ToMarket[12]+ToMarket[13]+ToMarket[14]+ToMarket[15]+ToMarket[16]+ToMarket[17]+ToMarket[18]+ToMarket[19]);
			MData.Digester_to_market_H2O = ToMarket[22];
			MData.Digester_to_market_P = (ToMarket[9]+ToMarket[10]+ToMarket[11]);

			MData.yr_digester_to_market_C += MData.Digester_to_market_C;
			MData.yr_digester_to_market_N += MData.Digester_to_market_N;
			MData.yr_digester_to_market_H2O += MData.Digester_to_market_H2O;
			MData.yr_digester_to_market_P += MData.Digester_to_market_P;
		}

		
			rcvl[GN] -= (CTF[1]+ToLagoon[1]+ToMarket[1]);
			rcl[GN] -= (CTF[2]+ToLagoon[2]+ToMarket[2]);
			rcr[GN] -= (CTF[3]+ToLagoon[3]+ToMarket[3]);
			CRB1[GN] -= (CTF[4]+ToLagoon[4]+ToMarket[4]);
			CRB2[GN] -= (CTF[5]+ToLagoon[5]+ToMarket[5]);
			crhl[GN] -= (CTF[6]+ToLagoon[6]+ToMarket[6]);
			crhr[GN] -= (CTF[7]+ToLagoon[7]+ToMarket[7]);
			dphum[GN] -= (CTF[8]+ToLagoon[8]+ToMarket[8]);
			OrgP[GN] -= (CTF[9]+ToLagoon[9]+ToMarket[9]);
			LabP[GN] -= (CTF[10]+ToLagoon[10]+ToMarket[10]);
			ComP[GN] -= (CTF[11]+ToLagoon[11]+ToMarket[11]);
			nh4[GN] -= (CTF[12]+ToLagoon[12]+ToMarket[12]);
			no3[GN] -= (CTF[13]+ToLagoon[13]+ToMarket[13]);
			no2[GN] -= (CTF[14]+ToLagoon[14]+ToMarket[14]);
			no[GN] -= (CTF[15]+ToLagoon[15]+ToMarket[15]);
			n2o[GN] -= (CTF[16]+ToLagoon[16]+ToMarket[16]);
			n2[GN] -= (CTF[17]+ToLagoon[17]+ToMarket[17]);
			nh3[GN] -= (CTF[18]+ToLagoon[18]+ToMarket[18]);
			urea[GN] -= (CTF[19]+ToLagoon[19]+ToMarket[19]);
			co2[GN] -= (CTF[20]+ToLagoon[20]+ToMarket[20]);
			doc[GN] -= (CTF[21]+ToLagoon[21]+ToMarket[21]);	
			water[1][GN] -= (CTF[22]+ToLagoon[22]+ToMarket[22]);		
	
	}//end of removal from digester

	if(GN==(q+5))//Removal from lagoon
	{
		if(MData.m_ToMarket[FN][j]>0.0)//Removal from lagoon to digester
		{
			ToDigester[1] = MData.m_ToMarket[FN][j] * rcvl[GN];
			ToDigester[2] = MData.m_ToMarket[FN][j] * rcl[GN];
			ToDigester[3] = MData.m_ToMarket[FN][j] * rcr[GN];
			ToDigester[4] = MData.m_ToMarket[FN][j] * CRB1[GN];
			ToDigester[5] = MData.m_ToMarket[FN][j] * CRB2[GN];
			ToDigester[6] = MData.m_ToMarket[FN][j] * crhl[GN];
			ToDigester[7] = MData.m_ToMarket[FN][j] * crhr[GN];
			ToDigester[8] = MData.m_ToMarket[FN][j] * dphum[GN];
			ToDigester[9] = MData.m_ToMarket[FN][j] * OrgP[GN];
			ToDigester[10] = MData.m_ToMarket[FN][j] * LabP[GN];
			ToDigester[11] = MData.m_ToMarket[FN][j] * ComP[GN];
			ToDigester[12] = MData.m_ToMarket[FN][j] * nh4[GN];
			ToDigester[13] = MData.m_ToMarket[FN][j] * no3[GN];
			ToDigester[14] = MData.m_ToMarket[FN][j] * no2[GN];
			ToDigester[15] = MData.m_ToMarket[FN][j] * no[GN];
			ToDigester[16] = MData.m_ToMarket[FN][j] * n2o[GN];
			ToDigester[17] = MData.m_ToMarket[FN][j] * n2[GN];
			ToDigester[18] = MData.m_ToMarket[FN][j] * nh3[GN];	
			ToDigester[19] = MData.m_ToMarket[FN][j] * urea[GN];
			ToDigester[20] = MData.m_ToMarket[FN][j] * co2[GN];
			ToDigester[21] = MData.m_ToMarket[FN][j] * doc[GN];
			ToDigester[22] = MData.m_ToMarket[FN][j] * water[1][GN];		

			int DN = q+6;

			old_LagoonN = Total_SOCSON(DN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
					 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
			old_LagoonC = MData.ttc;

			rcvl[DN] += ToDigester[1];
			rcl[DN] += ToDigester[2];
			rcr[DN] += ToDigester[3] ;
			CRB1[DN] += ToDigester[4] ;
			CRB2[DN] += ToDigester[5] ;
			crhl[DN] += ToDigester[6]; 
			crhr[DN] += ToDigester[7] ;
			dphum[DN] += ToDigester[8] ;
			OrgP[DN] += ToDigester[9];
			LabP[DN] += ToDigester[10];
			ComP[DN] += ToDigester[11];
			nh4[DN] += ToDigester[12] ;
			no3[DN] += ToDigester[13] ;
			no2[DN] += ToDigester[14] ;
			no[DN] += ToDigester[15] ;
			n2o[DN] += ToDigester[16] ;
			n2[DN] += ToDigester[17] ;
			nh3[DN] += ToDigester[18] ;
			urea[DN] += ToDigester[19];
			co2[DN] += ToDigester[20] ;
			doc[DN] += ToDigester[21];
			//sph[DN] = ToDigester[18];		
			water[1][DN] += ToDigester[22];

			rcvl[GN] -= ToDigester[1];
			rcl[GN] -= ToDigester[2];
			rcr[GN] -= ToDigester[3] ;
			CRB1[GN] -= ToDigester[4] ;
			CRB2[GN] -= ToDigester[5] ;
			crhl[GN] -= ToDigester[6]; 
			crhr[GN] -= ToDigester[7] ;
			dphum[GN] -= ToDigester[8] ;
			OrgP[GN] -= ToDigester[9];
			LabP[GN] -= ToDigester[10];
			ComP[GN] -= ToDigester[11];
			nh4[GN] -= ToDigester[12] ;
			no3[GN] -= ToDigester[13] ;
			no2[GN] -= ToDigester[14] ;
			no[GN] -= ToDigester[15] ;
			n2o[GN] -= ToDigester[16] ;
			n2[GN] -= ToDigester[17] ;
			nh3[GN] -= ToDigester[18] ;
			urea[GN] -= ToDigester[19];
			co2[GN] -= ToDigester[20] ;
			doc[GN] -= ToDigester[21];
			//sph[GN] = ToDigester[18];		
			water[1][GN] -= ToDigester[22];		
				
			new_LagoonN = Total_SOCSON(DN, q, rcnrvl, rcnrl, rcnrr, rcnb, rcnh, rcnm, soc, son, SIN, rcvl, rcl, rcr, 
					 CRB1, CRB2, crhl, crhr, dphum, doc, nh4, no3, no2, no, n2o, n2, nh3, urea, co2, sop,OrgP, LabP, ComP);
			new_LagoonC = MData.ttc;

			MData.Lagoon_to_digester_C = (new_LagoonC - old_LagoonC);
			MData.Lagoon_to_digester_N = (new_LagoonN - old_LagoonN);
			MData.Lagoon_to_digester_H2O = ToDigester[22];
			MData.Lagoon_to_digester_P = (ToDigester[20]+ToDigester[21]+ToDigester[22]);

			MData.yr_lagoon_to_digester_C += MData.Lagoon_to_digester_C;
			MData.yr_lagoon_to_digester_N += MData.Lagoon_to_digester_N;
			MData.yr_lagoon_to_digester_H2O += MData.Lagoon_to_digester_H2O;
			MData.yr_lagoon_to_digester_P += MData.Lagoon_to_digester_P;
		}//end of removal from lagoon to digester
		
		rcvl[GN] -= (CTF[1]+ToDigester[1]+ToMarket[1]);
			rcl[GN] -= (CTF[2]+ToDigester[2]+ToMarket[2]);
			rcr[GN] -= (CTF[3]+ToDigester[3]+ToMarket[3]);
			CRB1[GN] -= (CTF[4]+ToDigester[4]+ToMarket[4]);
			CRB2[GN] -= (CTF[5]+ToDigester[5]+ToMarket[5]);
			crhl[GN] -= (CTF[6]+ToDigester[6]+ToMarket[6]);
			crhr[GN] -= (CTF[7]+ToDigester[7]+ToMarket[7]);
			dphum[GN] -= (CTF[8]+ToDigester[8]+ToMarket[8]);
			OrgP[GN] -= (CTF[9]+ToDigester[9]+ToMarket[9]);
			LabP[GN] -= (CTF[10]+ToDigester[10]+ToMarket[10]);
			ComP[GN] -= (CTF[11]+ToDigester[11]+ToMarket[11]);
			nh4[GN] -= (CTF[12]+ToDigester[12]+ToMarket[12]);
			no3[GN] -= (CTF[13]+ToDigester[13]+ToMarket[13]);
			no2[GN] -= (CTF[14]+ToDigester[14]+ToMarket[14]);
			no[GN] -= (CTF[15]+ToDigester[15]+ToMarket[15]);
			n2o[GN] -= (CTF[16]+ToDigester[16]+ToMarket[16]);
			n2[GN] -= (CTF[17]+ToDigester[17]+ToMarket[17]);
			nh3[GN] -= (CTF[18]+ToDigester[18]+ToMarket[18]);
			urea[GN] -= (CTF[19]+ToDigester[19]+ToMarket[19]);
			co2[GN] -= (CTF[20]+ToDigester[20]+ToMarket[20]);
			doc[GN] -= (CTF[21]+ToDigester[21]+ToMarket[21]);	
			water[1][GN] -= (CTF[22]+ToDigester[22]+ToMarket[22]);
	}//end of removal from lagoon
	
	if(GN==(q+4))//Removal from compost
	{
		if(MData.m_ToMarket[FN][j]>0.0)//Removal from compost to market
		{
			ToMarket[1] = MData.m_ToMarket[FN][j] * rcvl[GN];
			ToMarket[2] = MData.m_ToMarket[FN][j] * rcl[GN];
			ToMarket[3] = MData.m_ToMarket[FN][j] * rcr[GN];
			ToMarket[4] = MData.m_ToMarket[FN][j] * CRB1[GN];
			ToMarket[5] = MData.m_ToMarket[FN][j] * CRB2[GN];
			ToMarket[6] = MData.m_ToMarket[FN][j] * crhl[GN];
			ToMarket[7] = MData.m_ToMarket[FN][j] * crhr[GN];
			ToMarket[8] = MData.m_ToMarket[FN][j] * dphum[GN];
			ToMarket[9] = MData.m_ToMarket[FN][j] * OrgP[GN];
			ToMarket[10] = MData.m_ToMarket[FN][j] * LabP[GN];
			ToMarket[11] = MData.m_ToMarket[FN][j] * ComP[GN];
			ToMarket[12] = MData.m_ToMarket[FN][j] * nh4[GN];
			ToMarket[13] = MData.m_ToMarket[FN][j] * no3[GN];
			ToMarket[14] = MData.m_ToMarket[FN][j] * no2[GN];
			ToMarket[15] = MData.m_ToMarket[FN][j] * no[GN];
			ToMarket[16] = MData.m_ToMarket[FN][j] * n2o[GN];
			ToMarket[17] = MData.m_ToMarket[FN][j] * n2[GN];
			ToMarket[18] = MData.m_ToMarket[FN][j] * nh3[GN];	
			ToMarket[19] = MData.m_ToMarket[FN][j] * urea[GN];
			ToMarket[20] = MData.m_ToMarket[FN][j] * co2[GN];
			ToMarket[21] = MData.m_ToMarket[FN][j] * doc[GN];
			ToMarket[22] = MData.m_ToMarket[FN][j] * water[1][GN];
		}//end of Removal from compost to market
		
		rcvl[GN] -= (CTF[1]+ToDigester[1]+ToMarket[1]);
			rcl[GN] -= (CTF[2]+ToDigester[2]+ToMarket[2]);
			rcr[GN] -= (CTF[3]+ToDigester[3]+ToMarket[3]);
			CRB1[GN] -= (CTF[4]+ToDigester[4]+ToMarket[4]);
			CRB2[GN] -= (CTF[5]+ToDigester[5]+ToMarket[5]);
			crhl[GN] -= (CTF[6]+ToDigester[6]+ToMarket[6]);
			crhr[GN] -= (CTF[7]+ToDigester[7]+ToMarket[7]);
			dphum[GN] -= (CTF[8]+ToDigester[8]+ToMarket[8]);
			OrgP[GN] -= (CTF[9]+ToDigester[9]+ToMarket[9]);
			LabP[GN] -= (CTF[10]+ToDigester[10]+ToMarket[10]);
			ComP[GN] -= (CTF[11]+ToDigester[11]+ToMarket[11]);
			nh4[GN] -= (CTF[12]+ToDigester[12]+ToMarket[12]);
			no3[GN] -= (CTF[13]+ToDigester[13]+ToMarket[13]);
			no2[GN] -= (CTF[14]+ToDigester[14]+ToMarket[14]);
			no[GN] -= (CTF[15]+ToDigester[15]+ToMarket[15]);
			n2o[GN] -= (CTF[16]+ToDigester[16]+ToMarket[16]);
			n2[GN] -= (CTF[17]+ToDigester[17]+ToMarket[17]);
			nh3[GN] -= (CTF[18]+ToDigester[18]+ToMarket[18]);
			urea[GN] -= (CTF[19]+ToDigester[19]+ToMarket[19]);
			co2[GN] -= (CTF[20]+ToDigester[20]+ToMarket[20]);
			doc[GN] -= (CTF[21]+ToDigester[21]+ToMarket[21]);	
			water[1][GN] -= (CTF[22]+ToDigester[22]+ToMarket[22]);
		
	}

	temp[GN] = air_temp;
}
/*
void class_manure::EntericGasProduction(int FN, float air_temp)//Li
{
	int i, FC=FN;
	float houseT, Ftemp;

	//manure temperature
	if(MData.mm_Ventilation==0) houseT = air_temp-(air_temp-20.0)*0.05;
	else houseT = air_temp-(air_temp-20.0)*0.5;//*MData.mm_VentRate;

	Ftemp = 0.05 * houseT + 0.5;
	Ftemp = min(1.5, max(0.5, Ftemp));

	MData.DAY_enteric_n2o[FC] = 0.0;//kg N2O-N/day
	MData.DAY_enteric_ch4[FC] = 0.0;//kg CH4-C/day
	MData.DAY_enteric_nh3[FC] = 0.0;

	//for(int i=1;i<=MData.AnimalTypes[FC];i++)
	{
		MData.day_enteric_ch4[FC] = 0.0;
		MData.day_enteric_n2o[FC] = 0.0;
		MData.day_enteric_nh3[FC] = 0.0;

		if(MData.mm_AnimalType[FC]==1)// milking cows
		{
			//Based on Mangino, Peterson and Jacobs at http://www.epa.gov/ttn/chief/conference/ei12/green/mangino.pdf

			float GE = MData.mm_FeedProtein[FC] * 0.01 * MData.mm_FeedRate[FC] * 17.0 * 0.6; //Gross energy demand by animal, kg protein/head/day -> MJ/head/day
			float Ym = 0.3;//0.4;//0.77;//CH4 conversion rate, a fraction of gross energy (GE) in feed converted to CH4 (percent)
			float F_FeedQuality = MData.mm_FeedC[FC] / 2.7;//impact of quality of feeding materials
			float dFeedN = MData.mm_FeedN[FC] / 0.225333;

			//Ellis et al. model CH4 (kg CH4/cow/day) = [3.23 + 0.809 * DMI (kg/day)]/55.6). 
			MData.day_enteric_ch4[FC] = GE * Ym / 55.65 * 12.0 / 16.0 * MData.mm_AnimalHeads[FC];// * powf(Ftemp, 0.8); //daily enteric CH4 production, kg C/day per farm

			//Based on Frank's experimets reported in August 2007
			//Enteric N2O: 2.5 lb N2O/cow/yr -> 0.001981 kg N/cow/day, 0.723 kg N/cow/yr
			//Enteric CH4: 300 lb CH4/cow/yr -> 0.3859 kg C/cow/day, 140 kg C/cow/yr
			//day_enteric_ch4 = 0.3859 * F_FeedQuality * mm_AnimalHeads; //kg C/day

			//MData.day_enteric_n2o[FC] = 0.5 * 0.001981 * dFeedN * MData.mm_AnimalHeads[FC]; //kg N/day
			MData.day_enteric_n2o[FC] = MData.head_enteric_n2o * MData.mm_AnimalHeads[FC]; //kg N/day

			//MData.day_enteric_nh3[FC] = 0.0 * dFeedN * MData.mm_AnimalHeads[FC]; //kg N/day

			//*day_enteric_ch4 = (50.0 + 0.01 * day_milk) / 365.0;// * mm_AnimalHeads; //kg CH4/day, for dairy cows
			//*day_enteric_ch4 = 65.0 / 365.0 * mm_AnimalHeads; //kg CH4/day, for heifers
			//*day_enteric_ch4 = 25.0 / 365.0 * mm_AnimalHeads; //kg CH4/day, for calves
		}
		else if(MData.mm_AnimalType[FC]==2||MData.mm_AnimalType[FC]==3)//beef or veal
		{
			//Based on Mangino, Peterson and Jacobs at http://www.epa.gov/ttn/chief/conference/ei12/green/mangino.pdf

			float GE = MData.mm_FeedProtein[FC] * 0.01 * MData.mm_FeedRate[FC] * 17.0 * 0.6; //Gross energy demand by animal, kg protein/head/day -> MJ/head/day
			float Ym = 0.4;//CH4 conversion rate, a fraction of gross energy (GE) in feed converted to CH4 (percent)
			float F_FeedQuality = MData.mm_FeedC[FC] / 2.7;//impact of quality of feeding materials

			MData.day_enteric_ch4[FC] = GE * Ym / 55.65 * 12.0 / 16.0 * MData.mm_AnimalHeads[FC];// * Ftemp; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 1.7 * 0.001918 * MData.mm_AnimalHeads[FC]; //kg N/day

			//MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else if(MData.mm_AnimalType[FC]==4)//pig
		{
			//based on RFF report: at http://www.epa.gov/ttn/chief/ap42/ch14/final/c14s04.pdf
			MData.day_enteric_ch4[FC] = MData.mm_AnimalHeads[FC] * 1.5 / 365.0 * 12.0 / 16.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else if(MData.mm_AnimalType[FC]==5)//sheep
		{
			MData.day_enteric_ch4[FC] = MData.mm_AnimalHeads[FC] * 8.0 / 365.0 * 12.0 / 16.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else if(MData.mm_AnimalType[FC]==6)//poultry
		{
			MData.day_enteric_ch4[FC] = 0.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else 
		{
			MData.day_enteric_ch4[FC] = 0.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
	}//animal type loop

	MData.DAY_enteric_n2o[FC] += MData.day_enteric_n2o[FC];//kg N2O-N/day
	MData.DAY_enteric_ch4[FC] += MData.day_enteric_ch4[FC];//kg CH4-C/day
	MData.DAY_enteric_nh3[FC] += MData.day_enteric_nh3[FC];//kg NH3-N/day

	MData.yr_enteric_ch4 += MData.DAY_enteric_ch4[FC];
	MData.yr_enteric_n2o += MData.DAY_enteric_n2o[FC];
	MData.yr_enteric_nh3 += MData.DAY_enteric_nh3[FC];

	//MData.animal_co2 -= MData.DAY_enteric_ch4[FC];
	//MData.yr_enteric_co2 -= MData.DAY_enteric_ch4[FC];
	
}
*/
void class_manure::EntericGasProduction(int FN, float air_temp)
{
	int i, FC = FN;
	float houseT, Ftemp;

	//manure temperature
	if (MData.mm_Ventilation == 0) houseT = air_temp - (air_temp - 20.0) * 0.05;
	else houseT = air_temp - (air_temp - 20.0) * 0.5;//*MData.mm_VentRate;

	Ftemp = 0.05 * houseT + 0.5;
	Ftemp = min(1.5, max(0.5, Ftemp));

	MData.mm_FeedC[FC] = MData.mm_FeedRate[FC] * 0.4; // kg dry matter/animal/day - kg C/animal/day
	MData.mm_FeedN[FC] = MData.mm_FeedProtein[FC] * 0.01 * MData.mm_FeedRate[FC] / 6.25; // kg N/animal/day
	MData.mm_FeedP[FC] = MData.mm_FeedTP[FC] * 0.01 * MData.mm_FeedRate[FC]; // kg P/animal/day

	MData.mm_FeedNDF[FC] = MData.mm_FeedNDFP[FC] * 0.01 * MData.mm_FeedRate[FC]; //kg NDF/animal/day
	MData.mm_FeedADF[FC] = MData.mm_FeedADFP[FC] * 0.01 * MData.mm_FeedRate[FC]; //kg ADF/animal/day
	MData.mm_FeedLignin[FC] = MData.mm_FeedLigninP[FC] * 0.01 * MData.mm_FeedRate[FC]; //kg Lignin/animal/day
	MData.mm_FeedFAT[FC] = MData.mm_FeedFATP[FC] * 0.01 * MData.mm_FeedRate[FC]; //kg FAT/animal/day
	MData.mm_FeedASH[FC] = MData.mm_FeedASHP[FC] * 0.01 * MData.mm_FeedRate[FC]; //kg ASH/animal/day

	MData.DAY_enteric_n2o[FC] = 0.0;//kg N2O-N/day
	MData.DAY_enteric_ch4[FC] = 0.0;//kg CH4-C/day
	MData.DAY_enteric_nh3[FC] = 0.0;

	//for(int i=1;i<=MData.AnimalTypes[FC];i++)
	{
		MData.day_enteric_ch4[FC] = 0.0;
		MData.day_enteric_n2o[FC] = 0.0;
		MData.day_enteric_nh3[FC] = 0.0;

		//enteric N2O£¬ 0.5g N2O-N/kg feed-N; 0.2% of intake N
		MData.head_enteric_n2o = 0.00001 * MData.mm_FeedN[FC];//0.0005; 0.9 * 0.001981 * MData.mm_FeedN[FN] / 0.225333;// * MData.mm_AnimalHeads[FN]; //kg N/day/head


		float CH4Ruduction = 0.0;

		if (MData.mm_AnimalType[FC] == 1)// milking cows
		{
			//Based on Mangino, Peterson and Jacobs at http://www.epa.gov/ttn/chief/conference/ei12/green/mangino.pdf
			float GE = MData.mm_FeedProtein[FC] * 0.01 * MData.mm_FeedRate[FC] * 17.0 * 0.6; //Gross energy demand by animal, kg protein/head/day -> MJ/head/day
			float Ym = 0.3;//0.4;//0.77;//CH4 conversion rate, a fraction of gross energy (GE) in feed converted to CH4 (percent)
			float F_FeedQuality = MData.mm_FeedC[FC] / 2.7;//impact of quality of feeding materials
			float dFeedN = MData.mm_FeedN[FC] / 0.225333;

			//Ellis et al. model CH4 (kg CH4/cow/day) = [3.23 + 0.809 * DMI (kg/day)]/55.6). 
			MData.day_enteric_ch4[FC] = GE * Ym / 55.65 * 12.0 / 16.0 * MData.mm_AnimalHeads[FC];// * powf(Ftemp, 0.8); //daily enteric CH4 production, kg C/day per farm

			if (MData.EmpiricalModel[FC] == 1)
			{
				MData.day_enteric_ch4[FC] = (49.5 + 12.1 * MData.mm_FeedRate[FC] + 2.57 * MData.mm_FeedNDFP[FC]) * MData.mm_AnimalHeads[FC] * 0.001; //daily enteric CH4 production, kg CH4/day per farm
				MData.day_enteric_ch4[FC] = MData.day_enteric_ch4[FC] * 12.01 / 16.04; //kg CH4/day per farm to kg C/day per farm
			}

			if (MData.FeedAdditive[FC] == 2 && MData.FeedAdditiveRate[FC] > 0.0) //3-NOP
			{
				CH4Ruduction = (-38 - 0.23 * (MData.FeedAdditiveRate[FC] * 1000 - 118) + 0.15 * (MData.mm_FeedNDFP[FC] * 10 - 333)) * -0.01;// g/kg of DM to mg/kg of DM for additive  
				CH4Ruduction = min(CH4Ruduction, 0.6);
			}
			else if (MData.FeedAdditive[FC] == 3 && MData.FeedAdditiveRate[FC] > 0.0) //Nitrate
			{
				CH4Ruduction = (-20.4 - 0.911 * (MData.FeedAdditiveRate[FC] - 16.7) + 0.691 * (MData.mm_FeedRate[FC] - 11.1)) * -0.01;
				CH4Ruduction = min(CH4Ruduction, 0.276);
			}
			else
			{
				CH4Ruduction = 0.0;
			}

			//Based on Frank's experimets reported in August 2007
			//Enteric N2O: 2.5 lb N2O/cow/yr -> 0.001981 kg N/cow/day, 0.723 kg N/cow/yr
			//Enteric CH4: 300 lb CH4/cow/yr -> 0.3859 kg C/cow/day, 140 kg C/cow/yr
			//day_enteric_ch4 = 0.3859 * F_FeedQuality * mm_AnimalHeads; //kg C/day

			//MData.day_enteric_n2o[FC] = 0.5 * 0.001981 * dFeedN * MData.mm_AnimalHeads[FC]; //kg N/day
			MData.day_enteric_n2o[FC] = MData.head_enteric_n2o * MData.mm_AnimalHeads[FC]; //kg N/day

			//MData.day_enteric_nh3[FC] = 0.0 * dFeedN * MData.mm_AnimalHeads[FC]; //kg N/day

			//*day_enteric_ch4 = (50.0 + 0.01 * day_milk) / 365.0;// * mm_AnimalHeads; //kg CH4/day, for dairy cows
			//*day_enteric_ch4 = 65.0 / 365.0 * mm_AnimalHeads; //kg CH4/day, for heifers
			//*day_enteric_ch4 = 25.0 / 365.0 * mm_AnimalHeads; //kg CH4/day, for calves
		}
		else if (MData.mm_AnimalType[FC] == 2 || MData.mm_AnimalType[FC] == 3)//beef or veal
		{
			//Based on Mangino, Peterson and Jacobs at http://www.epa.gov/ttn/chief/conference/ei12/green/mangino.pdf

			float GE = MData.mm_FeedProtein[FC] * 0.01 * MData.mm_FeedRate[FC] * 17.0 * 0.6; //Gross energy demand by animal, kg protein/head/day -> MJ/head/day
			float Ym = 0.4;//CH4 conversion rate, a fraction of gross energy (GE) in feed converted to CH4 (percent)
			float F_FeedQuality = MData.mm_FeedC[FC] / 2.7;//impact of quality of feeding materials

			MData.day_enteric_ch4[FC] = GE * Ym / 55.65 * 12.0 / 16.0 * MData.mm_AnimalHeads[FC];// * Ftemp; //daily enteric CH4 production, kg C/day per farm

			if (MData.EmpiricalModel[FC] == 1)
			{
				MData.day_enteric_ch4[FC] = (49.5 + 12.1 * MData.mm_FeedRate[FC] + 2.57 * MData.mm_FeedNDFP[FC]) * MData.mm_AnimalHeads[FC] * 0.001; //daily enteric CH4 production, kg C/day per farm
				MData.day_enteric_ch4[FC] = MData.day_enteric_ch4[FC] * 12.01 / 16.04; //kg CH4/day per farm to kg C/day per farm
			}

			if (MData.FeedAdditive[FC] == 2 && MData.FeedAdditiveRate[FC] > 0.0) //3-NOP
			{
				CH4Ruduction = (-26.1 - 0.23 * (MData.FeedAdditiveRate[FC] * 1000 - 118) + 0.15 * (MData.mm_FeedNDFP[FC] * 10 - 333)) * 0.01;// g/kg of DM to mg/kg of DM for additive  
				CH4Ruduction = min(CH4Ruduction, 0.81);
			}
			else if (MData.FeedAdditive[FC] == 3 && MData.FeedAdditiveRate[FC] > 0.0)
			{
				CH4Ruduction = (-10.1 - 0.911 * (MData.FeedAdditiveRate[FC] - 16.7) + 0.691 * (MData.mm_FeedRate[FC] - 11.1)) * -0.01;
				CH4Ruduction = min(CH4Ruduction, 0.294);
			}
			else
			{
				CH4Ruduction = 0.0;
			}

			//MData.day_enteric_n2o[FC] = 1.7 * 0.001918 * MData.mm_AnimalHeads[FC]; //kg N/day
			//MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else if (MData.mm_AnimalType[FC] == 4)//pig
		{
			//based on RFF report: at http://www.epa.gov/ttn/chief/ap42/ch14/final/c14s04.pdf
			MData.day_enteric_ch4[FC] = MData.mm_AnimalHeads[FC] * 1.5 / 365.0 * 12.0 / 16.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else if (MData.mm_AnimalType[FC] == 5)//sheep
		{
			MData.day_enteric_ch4[FC] = MData.mm_AnimalHeads[FC] * 8.0 / 365.0 * 12.0 / 16.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else if (MData.mm_AnimalType[FC] == 6)//poultry
		{
			MData.day_enteric_ch4[FC] = 0.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}
		else if (MData.mm_AnimalType[FC] == 7)//heifer
		{
			//From UCD Ermias Kebreab 
			float GE = MData.mm_FeedProtein[FC] * 0.01 * MData.mm_FeedRate[FC] * 17.0 * 0.6; //Gross energy demand by animal, kg protein/head/day -> MJ/head/day
			float Ym = 0.063;//CH4 conversion rate, a fraction of gross energy (GE) in feed converted to CH4

			if (MData.EmpiricalModel[FC] == 1)
			{
				MData.day_enteric_ch4[FC] = (49.5 + 12.1 * MData.mm_FeedRate[FC] + 2.57 * MData.mm_FeedNDFP[FC]) * MData.mm_AnimalHeads[FC] * 0.001; //daily enteric CH4 production, kg CH4/day per farm
				MData.day_enteric_ch4[FC] = MData.day_enteric_ch4[FC] * 12.01 / 16.04; //kg CH4/day per farm to kg C/day per farm
			}

			MData.day_enteric_ch4[FC] = GE * Ym / 55.65 * 12.01 / 16.04 * MData.mm_AnimalHeads[FC];//daily enteric CH4 production, kg C/day per farm

			if (MData.FeedAdditive[FC] == 2 && MData.FeedAdditiveRate[FC] > 0.0) //3-NOP
			{
				CH4Ruduction = (-38 - 0.23 * (MData.FeedAdditiveRate[FC] * 1000 - 118) + 0.15 * (MData.mm_FeedNDFP[FC] * 10 - 333)) * -0.01;// g/kg of DM to mg/kg of DM for additive  
				CH4Ruduction = min(CH4Ruduction, 0.6);
			}
			else if (MData.FeedAdditive[FC] == 3 && MData.FeedAdditiveRate[FC] > 0.0) //Nitrate
			{
				CH4Ruduction = (-20.4 - 0.911 * (MData.FeedAdditiveRate[FC] - 16.7) + 0.691 * (MData.mm_FeedRate[FC] - 11.1)) * -0.01;
				CH4Ruduction = min(CH4Ruduction, 0.276);
			}
			else
			{
				CH4Ruduction = 0.0;
			}

			MData.day_enteric_n2o[FC] = MData.head_enteric_n2o * MData.mm_AnimalHeads[FC]; //kg N/day

		}
		else
		{
			MData.day_enteric_ch4[FC] = 0.0; //daily enteric CH4 production, kg C/day per farm

			//MData.day_enteric_n2o[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day

			MData.day_enteric_nh3[FC] = 0.0 * MData.mm_AnimalHeads[FC]; //kg N/day
		}

		MData.day_enteric_ch4[FC] = MData.day_enteric_ch4[FC] * (1.0 - CH4Ruduction);
	}//animal type loop

	MData.DAY_enteric_n2o[FC] += MData.day_enteric_n2o[FC];//kg N2O-N/day
	MData.DAY_enteric_ch4[FC] += MData.day_enteric_ch4[FC];//kg CH4-C/day
	MData.DAY_enteric_nh3[FC] += MData.day_enteric_nh3[FC];//kg NH3-N/day

	MData.yr_enteric_ch4 += MData.DAY_enteric_ch4[FC];
	MData.yr_enteric_n2o += MData.DAY_enteric_n2o[FC];
	MData.yr_enteric_nh3 += MData.DAY_enteric_nh3[FC];

	//MData.animal_co2 -= MData.DAY_enteric_ch4[FC];
	//MData.yr_enteric_co2 -= MData.DAY_enteric_ch4[FC];

}

float class_manure::Total_SOCSON(int FC, int FCC, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
								 float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
								 float *CRB1, float *CRB2, float *crhl, float *crhr, float *dphum, float *doc, 
								 float *nh4, float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, 
								 float *urea, float *co2, float *sop, float *OrgP, float *LabP, float *ComP)
{
	float ttn;

	soc[FC] = rcvl[FC] + rcl[FC] + rcr[FC] + CRB1[FC] + CRB2[FC] + crhl[FC] + crhr[FC] + dphum[FC] + co2[FC] + doc[FC];
	son[FC] = rcvl[FC]/rcnrvl + rcl[FC]/rcnrl + rcr[FC]/rcnrr + CRB1[FC]/rcnb + CRB2[FC]/rcnb + crhl[FC]/rcnh + crhr[FC]/rcnh + dphum[FC]/rcnm;
	SIN[FC] = nh4[FC] + no3[FC] + no2[FC] + no[FC] + n2o[FC] + n2[FC] + nh3[FC] + urea[FC];
	sop[FC] = OrgP[FC] + LabP[FC] + ComP[FC];

	MData.ttc = soc[FC];
	ttn = son[FC] + SIN[FC];
	
	MData.ttp = sop[FC];

	return(ttn);
}

#endif