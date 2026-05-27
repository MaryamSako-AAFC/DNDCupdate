#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <io.h>
#include "RunPaths.h"
#include "DNDCgo.h"
#include "dndc_tool.h"

#define BASE
#define CONSOLE


//#define MANURE
//#define DROUGHT
//#define DEGUI
//#define HYDRO
//#define HOURLY
#define BALANCE   //Note that there is a File handler issue when this is enabled for batch simulations.
//#define DAILY
//#define VOC
//#define ISOTOPE
//#define PHOSPHOROUS

//#ifdef DEGUI
//#define ROOTDIR "\\DNDC\\"
////#define ROOTDIR get_path()
//#define OUTPUT "\\DNDC\\RESULT"
//#define INTER "\\DNDC\\INTER"
//#define INPUTS "\\DNDC\\INPUTS"
//#define INTERMANAGE "\\DNDC\\Inter\\Management"
///*
//	#define ROOTDIR ""
//	#define OUTPUT "RESULT"
//	#define INTER "RESULT\\INTER"
//	#define INPUTS "RESULT\\INPUTS"
//	#define INTERMANAGE "RESULT\\Inter\\Management"
//	*/
//#else


#ifdef CONSOLE
#else 
#define ROOTDIR "\\DNDC\\"
#define OUTPUT "\\DNDC\\RESULT"
#define INTER "\\DNDC\\RESULT\\INTER"
#define INPUTS "\\DNDC\\RESULT\\INPUTS"
#define INTERMANAGE "\\DNDC\\RESULT\\INTER\\Management"
#endif
#ifdef MANURE
#define ROOTDIR "\\ManureDNDC\\"
#define OUTPUT "\\ManureDNDC\\RESULT"
#define INTER "\\ManureDNDC\\RESULT\\INTER"
#define INPUTS "\\ManureDNDC\\RESULT\\INPUTS"
#define INTERMANAGE "\\ManureDNDC\\RESULT\\INTER\\Management"
#endif

//extern char * ROOTDIR = NULL;
//extern const char * get_path();

//#endif

#define CSV "csv"
#define MAXSOILLAYER		280
#define SOILDEPTH           2.0
#define MAXYEARS			100
#define FILE_NOT_FOUND		1001
#define RI					0.005
#define DRF   0.04//0.03 
#define EFFRB .67
#define srh 0.16
#define RBO 0.02
#define SRB 0.9
#define krcvl 0.25
#define krcl 0.074
#define krcr 0.02
#define KRB    0.12
#define hrb    0.04
#define EFFNO  0.2
#define KCI 0.017
#define KNI 0.083
#define FD  0.05
#define um_no3   .67
#define um_no2   .67
#define um_no    .34
#define um_n2o   .34
#define YMC      .503
#define MC       .0076
#define m_no3   .09
#define ym_no3  .401
#define R       .29
#define m_no2  .0349
#define ym_no2 .428
#define ym_no .151
#define m_no  .0792
#define ym_n2o .151
#define m_n2o  .0792
#define D_O2 0.07236  // O2 diffusion in air, m2/h from Beisecker 1994
#define K35       25
#define QK        2.0
#define ten9      1000000000.0
#define CANNOT_CREATE_FILE 1002
//#define Eh_ch4 -100.0 //!! Critical Eh (mV) for CH4 production

#define foot2_m2 0.0929
#define foot3_m3 0.0283
#define lb_kg 0.4535
#define lboft3_kgom3 16.015
#define ac_ha 0.405
#define lboac_kgoha 1.12

/*class dailyrecord
{
public:
	float tbiomas[3][366],tdSOC[3][366],tco2[3][366],tn2o[3][366],tno[3][366],tnh3[3][366],tch4[3][366];
	float RDbiomas[366],RDdSOC[366],RDco2[366],RDn2o[366],RDno[366],RDnh3[366],RDch4[366];
	float tleach[3][366];
	float RDleach[366];
	int IniFluxSum();
	int SaveFluxSum(char *CountryName,char *ScenarioName,int soilflag,CString county_ID1,int landuse,int CropIden, int crop_number);
};*/

class class_model
{
	
public:

  // public member functions
	class_model();
	~class_model();

	//changed by liujm
	void dndc_site(MODEL_LINK_INFO* pLinkInfo, int scale, int S_SoilYear, float S_crop_ha, int S_crop_ID, int ProvinceOrder, 
					int S_county, CString county_ID1, int landuse, int ifdaily, char* DatabaseName, char* ScenarioName,
					int S_ThisYear, int StartYear);

	//float RMCST, RMCSO, RMCRT, laminae_area, PCGC_Zero, DSRad, DPAR, ALV;//new variables added by KK
	//float WLV_t0, WRT_t0, WST_t0, WSO_t0;
	
	float	SoilReset;
	int       year;
    int       total_yr;       
    int       day_file;
    char      cliname[MAXYEARS][240]; 
	int soilProfileType;
	char soilProfileName[250];
	char SoilSpinUpFileName[250];
	char OBSYieldFileName[250];
	char CO2FileName[250];
	int CO2file;
	int SoilSpinUp, SoilSpinUpCounter;
	int SoilSpinUpYears;
    char      soil[80];      
	int		  countTemp;
	int		  countWater;
	int		  harvIdxFlag;		  
    int       st[MAXSOILLAYER];
    float     clay[MAXSOILLAYER];
    float     sts[MAXSOILLAYER];
	float	  kTheta[MAXSOILLAYER];
	float	  theta[MAXSOILLAYER];
	float	  finalHead[MAXSOILLAYER];
	float	  startHead[MAXSOILLAYER];
    float     sks[MAXSOILLAYER];
    float     fldcap[MAXSOILLAYER], ini_fldcap,fldcapOLD[MAXSOILLAYER];
    float     wiltpt[MAXSOILLAYER];
    float     sd[MAXSOILLAYER];
    float     soil_ph[MAXSOILLAYER];
    int       idc;
    float     ini_ttoo[MAXSOILLAYER], Tttoo[MAXSOILLAYER];
	int manureCounter;//keeps track of days after manure Appliction;
	float shapeDensity;
	float SwcWTEffect; //sets a water extraction limitation for certain textured soils
	int	  SwcWTEffect2;//turns on and off the textural effect of WT on SWC
	float SolarEffectTemp;
	float UreaHydroFactor;
	float UreaHydroWaterFactor,UreaHydroCounter[MAXSOILLAYER];
	float NH3SoilDFactor;
	float N2N2OFactor;
	float UreaDifFactor;
	int spinUpPlant;//planting 0 = no initialize at plant 1= initialize at plant.
	int writeOutPlant;
	int obsYieldFlag;//flag 0= no reading obs yields;
	float flower, pod,seedFill;
	// new batch acronyms
int emergDate, flowerDate, podDate, matDate;
float totET,cumIrri, totIrriDays;

float slowManFrac, slowManKRate; //new manureParameters
float accumNewPlantN;

float lagoonTempPartition[101][2];
int annualMinTempDay, oldLayerDepth;

float averageAnnualTemp;
float  lagoon_snowpack, lagoon_SnowMelt, lagoon_snowfall;//lagoon_snowpack,
float lagoon_ice[21];

	int DynGermDays[2];
    float     ini_no3;
    float     ini_nh4;
    float     resoc;
    float     ahsoc;
    float     phsoc;
    float     byp;
    float     h[MAXSOILLAYER];
	float	  maxAnnualTemp;
    float     th;
    float     mmm[MAXSOILLAYER];
    float     vvv[MAXSOILLAYER], day_RootInput_DOC;
	float     acetate[MAXSOILLAYER];
	float totalqDrain;
	int GermReport; //days after planting for germination
	float	HarvSIN;//harvest soil organic N
	float evapMulti;
	float snowmeltMulti;
	float keDrainM;//effective lateral hydraulic conductivity;
	float drainageDepthM;//drainageDepth in meters
	float spaceDrain;//drain spacing in meters
	float dDrain;//actual depth between drains and bedrock-impermeable layer in m (depth below drains to bedrock)
	float reDrain;//radius of drain in meters
	int LRA1;//recession curve on off
	float aCurve,bCurve; //recesion curve numbers
	int waterOut,TileIrri,TileIrriDays,controlledDrainageDays,controlledDrainageStartDay; //file for outputting water data
	float 	maxNO3F,moveN,partitN,NLeachF,TileIrriAmount,TileIrriRate;//scalars for Drainage
	float    controlledDrainageDepthM; //Depth for Controlled Drainage. 
	int controlledDrainageDepth; //Depth in layers for Controlled Drainage
	float	snowInsulationFactor; //snow Insulation Effect
    int       q;
	int germCount;//germination Counter
	int cumWaterStress,cumWaterStress1;//cumulative excess moisture stress
	float GermAvgTemp;
	float germTemp;//germination Temperature
	float stuntGrowth;//germination effect on growth
	float rainFallInterFactor;//rainfall Intercept Factor
	int		  yearAutoFert;
	int		  manureHour,counterPHLEFT;
	float     newmanuPH;
	int		  maxTempAvg;//BrianCrop Model
	int		  WTDrain;
	int autoHarvestF;//1 means autoharvest. 0 means no autoharvest 
	int autoPlantF;//1 means autoPlant. 0 means no autoPlant
	int prefFlowCheck;//1 means Preferrential Flow. 0 means don't use PrefFlow Algorithm
	float prefFlowDepth;//float for Depth of Pref Flow Calc.
	float prefFlowRecov;//float for recovery rate for surface preferrential flow cracks
	int autoPlantCount;//tracks the condition for autoPlant;
	float RFM;
	int lastFrost; //calculates the last spring Frost of the year after day 105.
	int fallFrost1; //calculates the first fall frost of the year after day 152;
	int consec5Days;
	float waterpoolbd;
	int homoWaterFlow;
	float winterCrown,springCrown;
	int winterCrownDays,springCrownDays;
	float winterKillRed;
	float cropWStress;
	float oldWP,oldFC;
	int farmAgentModel;
	float rootMResp[8], rootNewResp[8], shootMResp[8],shootNewResp[8];
	int header;
	float rainMulti,denitMulti,nitMulti,springMulti,nit2Multi,runMulti,runMultiN;
	int vernDays; //Vernalization counter for perennial crops.
    //float     psw[MAXSOILLAYER];
    //float     fldcapw;
    //float     wiltptw;
    //float     travelt;
	int	  autoHarvPer;//auto harvest perrenials
	float winterKill[8];//winterKill for 8 crop species
	float totalSens1,totalSens2,totalSens3;//accumulator for aboveground senenscence
    float     clay_f1;
    float     clay_f2;
	float	  PrefNMove;
	float	  DayPETmod,DayPETRN,DayPETPAR,DayPETRa,DayPETRs,DayPETAlbedo;
	
	float     NreductionFactor,NH3Vol;
    float     qstar;
    float     by_passf;
    float     rcnb;
    float     rcnh;//, rcnh;
    float     rcnm;
    float     rcnrvl;
    float     rcnrl;
    float     rcnrr;
    float     leaf_water;
    float     surf_water;
    float     snow_pack;
    float     stub1;
    float     stub2;
    float     stub3, stubP;
    //float     weedn;
	float     lastKw[MAXSOILLAYER];
    float     ave_anvf[MAXSOILLAYER];
    float     rcvl[MAXSOILLAYER];
    float     rcl[MAXSOILLAYER];
	float     manurePool[MAXSOILLAYER];//new manure pool 
	float	  manurePoolCN;
    float     rcr[MAXSOILLAYER];
    float     ocini[MAXSOILLAYER];
    float     dphum[MAXSOILLAYER];
    float     no2[MAXSOILLAYER];
    float     no3[MAXSOILLAYER];
    float     nh4[MAXSOILLAYER];
    float     clay_nh4[MAXSOILLAYER];
    float     urea[MAXSOILLAYER];
    float     NH4HCO3[MAXSOILLAYER];
	float	  hourlyTemp[MAXSOILLAYER];
    float     nh3[MAXSOILLAYER];
    float     no[MAXSOILLAYER];
    float     n2o[MAXSOILLAYER];
    float     n2[MAXSOILLAYER];
    float     temp[MAXSOILLAYER];
    float     day_wfps[MAXSOILLAYER];
    float     anvf[MAXSOILLAYER];
    float     ice[MAXSOILLAYER];
    float     R_Wt[MAXSOILLAYER];
    float     doc[MAXSOILLAYER];
	//float     Odoc[MAXSOILLAYER];
    float     Eh[MAXSOILLAYER];
    float     day_O2[MAXSOILLAYER];
    float     co2[MAXSOILLAYER];
    float     sph[MAXSOILLAYER];
	int		clayCrackLayer;
	float  clayCrackAccum[MAXSOILLAYER];
	double 	  water[25][250];
	float	  CRB1[MAXSOILLAYER];
	float		CRB2[MAXSOILLAYER];
	//float		day_hdc[MAXSOILLAYER];
	float		newh[MAXSOILLAYER];
    float		DayFlux[MAXSOILLAYER];
	float O2_old[MAXSOILLAYER], Eh_old[MAXSOILLAYER];
	float O2[MAXSOILLAYER]; // kg oxygen/(ha * layer)
	float  potbiomass[ MAXSOILLAYER ];//BrianCrop Model
    //float nitrifier[MAXSOILLAYER];
	//float old_f_lost[MAXSOILLAYER];
	float Fe3[MAXSOILLAYER]; // mole Fe(3+) or Mn(4+)/kg soil
	float Fe2[MAXSOILLAYER];
	float Mn4[MAXSOILLAYER]; // mole Mn(4+) or Mn(4+)/kg soil
	float Mn2[MAXSOILLAYER];
	float SO4[MAXSOILLAYER]; // mole sulfate/kg soil
	float H2S[MAXSOILLAYER]; // mole sulfate/kg soil
    //float O2_mole[MAXSOILLAYER];
	float ch4[MAXSOILLAYER];
	float soc[MAXSOILLAYER];
	float son[MAXSOILLAYER];
	float sop[MAXSOILLAYER];
	float OrgP[MAXSOILLAYER], LabP[MAXSOILLAYER], ComP[MAXSOILLAYER], AdsP[MAXSOILLAYER], MinP[MAXSOILLAYER];
	float SIN[MAXSOILLAYER];
	float doc_w[MAXSOILLAYER],  no_w[MAXSOILLAYER];//denitrifier[MAXSOILLAYER],
    float n2o_w[MAXSOILLAYER], no2_w[MAXSOILLAYER];
    float no3_w[MAXSOILLAYER], assim2[MAXSOILLAYER], nh4_w[MAXSOILLAYER];
    float doc_d[MAXSOILLAYER], no_d[MAXSOILLAYER];
    float n2o_d[MAXSOILLAYER], n2_w[MAXSOILLAYER], no2_d[MAXSOILLAYER];
    float no3_d[MAXSOILLAYER], nh4_d[MAXSOILLAYER];
	//float root_CO2[MAXSOILLAYER];
	double OutWater[MAXSOILLAYER][25], TileWater[MAXSOILLAYER][25];
	//float day_layer_soil_ev[MAXSOILLAYER];
	float crhl[MAXSOILLAYER], crhr[MAXSOILLAYER]; 
	//float ice_doc[MAXSOILLAYER], ice_N[MAXSOILLAYER], ice_n2o[MAXSOILLAYER], ice_n2[MAXSOILLAYER];
	float inert_C[MAXSOILLAYER];
	float FreezeDOC[MAXSOILLAYER];
	float TotalFreezeDOC;
	float freezeWaterFactor;
	float SoilDepth[MAXSOILLAYER];
	float F_methanogen[MAXSOILLAYER]; 
	float H2[MAXSOILLAYER], day_H2_prod[MAXSOILLAYER], day_ch4_CO2[MAXSOILLAYER]; 
	float day_ch4_1[MAXSOILLAYER], day_ch4_2[MAXSOILLAYER], day_ch4_3[MAXSOILLAYER];
	float peat_DOC[MAXSOILLAYER], peat_CO2[MAXSOILLAYER],  day_H2_pool[MAXSOILLAYER];
	float day_nitrification[MAXSOILLAYER], day_denitrification[MAXSOILLAYER],day_nitrify_n2ol[MAXSOILLAYER],day_denitrify_n2ol[MAXSOILLAYER]; 
	float hydro_condK[MAXSOILLAYER],theta_s[MAXSOILLAYER],Ks[MAXSOILLAYER],hourly_theta[MAXSOILLAYER],theta_app[MAXSOILLAYER],unsat_K[MAXSOILLAYER];//added for water calc
	float mat_pot_entry[MAXSOILLAYER],mat_pot[MAXSOILLAYER],h_pot[MAXSOILLAYER];//added for water calc
	float sand[MAXSOILLAYER],sksHydro[MAXSOILLAYER];//added for water calc

	float base_clay_N, max_clay_N;
	float WaterPool;

	float day_water_in;
	float day_ice_N, day_ice_doc, day_ice_n2o, day_ice_n2;
	//CString CropSystem[250];
    int	      germinationDays;//for crop[1]
    int       crop[8];
	int       flagHeader;
	float	  nitscaleC[8];
	//float	  optffPGI[731][4];
    float     maxmn[8], ini_maxmn[8];
    int       jdseed[8];
    int       jdtrans[8];
    int       grow_days[8];
    float     left_perc[8];
    float     liupt[8];
    float     PresentBiomass[8], HarvestedBiomassC[8];
    float     YrG_grain[8], YrG_leaf[8], YrG_stem[8], YrG_root[8];
	float	  YrN_grain[8], YrN_leaf[8], YrN_stem[8], YrN_root[8],YrG_lai[8], startOptLeafC[8];
	float     MaxYrG_grain[8], MaxYrG_leaf[8], MaxYrG_stem[8], MaxYrG_root[8];
	float	  MaxYrN_grain[8], MaxYrN_leaf[8], MaxYrN_stem[8], MaxYrN_root[8], MaxYrG_lai[8];

    //float     Genet_Ps[12];
	float	  root_depth[8];
	float rootDensity[8][MAXSOILLAYER];//rootDensity per crop per layer
	float     proleaf[8];
	float     prostem[8];
	float     GrainYield[8], OptCropC[8], OptGrainC[8], OptLeafC[8], OptStemC[8], OptRootC[8];
	int		  WinterCropFlag[8], HarvestYear[8], Excreta[8];    
    int       crop_flag[8], GrassFlag[8], IrriRice_flag, DeepRice_flag;
    int       seed[8];
	float     N2NodEFACC[8];
    int	      harvest_flag[8];
	int		  vernal[8];
	float	  cTT[8],pDF[8];//crop cold tolerance ALFALFA
	float     cropTempStress[8],cropTempStressAnnual[8], meanTempStressT[8];//daily cardinal temp crop Stress
	float BandedAppMulti[MAXSOILLAYER];
	int endYearOfSim;
	float gddT[731];
	float	  pDFCUM[8]; //cumulative population death rate.
    float     plantn[8], yr_plantn[8], PlantTakeN[8];
    float     demandn[8];//, weed_demandn, day_weed_N_demand;
	int		  maturity_flag[8]; 
	float	  OptimumT[8], ideal_DayCropC[8];
	int		  RootShape[8];
	double    kext1[8], kext2[8], cmaxh[8];//theo
	float     cropGRate[8], cropTime[8], rueHI[8], delayP[8];
	float	  GrainFill[8];
	float	  LAImax[8];
	float	  FrostKill[8];
	float	  cHRMX[8];
	float	  cDRMX[8];
	float	  cTMX[8];
	float	  pDFMX[8];
	float crop1_trans, crop2_trans;
    float rootFracIncrease;   
    char      climd[6][300];
    char      climy[6][300];
	char ClimateFileBri[120];
    float     mon_avet[13];
    float     yr_avet, yr_avetj;
    float     yr_rain;
    float     rno3;
    float     base_nh3;
    float     Base_CO2;
	float yrPPT;
	float manureCK1;
	float totalManureC;
	float totalManureN;
    int       irr_num, jdirr[366], irrimethod[366], IrriMethod,tileIrriDays[366];
	int	      cdrain_num,count_Drain,stdrain[366],enddrain[366],cdrainDays[366];
	float	  cdraindepth[366];
    float     irria[366], irriph[366], irri_index;
    
    int       til_num;
    int       jdtil[50], til_method[50];
    float     til_dept[50];

    int       fer_num;
    int       jdfer[50];
	int	      FertMethodApp[30];
    
    float     inject[50];
    float     fer_dept[50], FertDepth;
    float     fer1[50];
    float     fer2[50];
    float     fer3[50];
    float     fer4[50];
    float     fer5[50];
    float     fer6[50];
    float     fer7[50];
	int       NIDay1, NIDay2,UIDay1,UIDay2;
	float     NIEfficiency;
    
    int       man_num;
    int       ManureType[50];
    int       jdman[50], manure_flag;
	int		  manuAppHour[50],useManPool[50], autoManure;
	float	  manuDM[50],manuPH[50], manPoolFrac[50],manPoolRate[50];
    float     ManureOrgC[50], ManureDepth[50], ManureOrgN[50], ManureNH4[50], ManureNO3[50], ManureDOC[50], ManureUREA[50];
    float     manucn[50];
    int       gra_num, cut_num;
	int		  currentCut;//tracks the current Cut Number;
    int       jdgra1[100], jdgra2[100], kind[100], jdcut[100], CutPart[100];
    //float     head[20];
	//float     cattle[20], horse[20], sheep[20], hours[20];
	float     AnimalHead[10][100],hrs[100], CutFraction[100], AddFeed[100], FeedCN[100],GrazBiomass[100],GrazCConsume[100],GrazCExcrete[100];
	float   GrassProductivityFactor;
    int       plastic_num, jdplastic1[50],jdplastic2[50],plastic_method;
	float	  FilmCoverF[50], FilmEffect, FilmCoverFraction;
    
    int       flo_num;
    int       jdflo1[50];
    int       jdflo2[50];
    //int       fdleak;
    
    char      crop_name[8][50];
    //float     myc;
    float     grain[8];
    float     leaf[8], stem[8];
    float     root[8];
    float     plantcn[8];
	float	  rootcnDyn[8], graincnDyn[8], leafcnDyn[8], stemcnDyn[8];


    float     graincn[8], base_graincn[8];//Brian
    float     rootcn[8], base_rootcn[8];
	float     leafcn[8], base_leafcn[8];
	float     stemcn[8], base_stemcn[8];
    float     wreq[8], base_wreq[8],base_maxmn[8];

    float     lai_index[8];
    float     lai[8];
    float     cropht;
    


#define DEBUG_CBALANCE 1   // <— uncomment to enable debug columns //Turned on for DOC check balance. 

#ifdef DEBUG_CBALANCE
// DOC production (by source) and consumption (to CO2)
	double day_doc_from_rcvl = 0.0;  // DOC from very labile litter (RCVL)
	double day_doc_from_rcl = 0.0;  // DOC from labile litter (RCL)
	double day_doc_from_rcr = 0.0;  // DOC from resistant litter (RCR)
	double day_doc_from_humads = 0.0;  // DOC produced inside decomp_humads (0.4/0.6 parts)
	double day_doc_from_humus = 0.0;  // DOC produced by humus decomp (d_humus)
	double day_doc_from_manure = 0.0;  // if any explicit manure DOC channel
	double day_doc_prod_total = 0.0;  // convenience sum

	double day_doc_to_co2 = 0.0;  // DOC mineralized to CO2 (sum over layers)
	double day_dn_co2 = 0.0;  // if your DOC balloon emits via dn_co2 -- day_co2, capture it here

	// CO2 routing checkpoints
	double day_co2_before_roll = 0.0;  // day_co2 value before end-of-day consolidation
	double day_cmine_before_roll = 0.0;// day_C_mine value before end-of-day consolidation
	double dCO2_pool_today = 0.0;  // (end_prof_co2 - ini_prof_co2) – net pool change today
	double dDOC_pool_today = 0.0;  // (end_prof_doc - ini_prof_doc)
#endif


    int jday;
    float     air_temp;
    float     rainfall;//, rain_ph;
    float     rainf;
    float     wrcvl;
    float     wrcl;
    float     wrcr;
    float     wcrb;
    float     wcrhl, wcrhr;
    float     whumus;
	float	  winertC;
    float     wnew_hum;
    float     day_co2;
    float     day_rco2[8];
    float     day_ch4;
    float     wtcavai;
    float     day_nup[8];
    float     day_weednup;
    float     day_dsurea;
    float     dsno3[22];
    float     dsnh4[22];
	float	  dsurea[22];
	float     dsClayN[22];
    float     dsnh3;
    float     ds_doc;
    float     day_soil_nh3;
    float     day_plant_nh3[8];
    float     day_DWater[8];
    float     day_leach_NO3, day_leach_P, yr_leach_P, day_runoff_P;
	float     day_leach_urea;
    float     day_soil_an_no;
    float     day_soil_an_n2o;
    float     day_soil_ae_no;
    float     day_soil_ae_n2o;
    float     day_soil_n2;
    float     day_soil_nitrify;
	float     day_addC;
	float	  snow_micro_growth; //microbial denitrifier index for spring burst
	    
    float     yr_addmc;
    float     yr_addmn;
    float     yr_sln;
    float     yr_addrc;
    float     yr_addrn;
    float     yr_addrp;
    //float     yr_weedn;
    float     yr_wln;
    float     yr_addtc, day_add_litter;
    float     yr_addtn;
    float     yr_addleafc;
    float     yr_addleafn;
    float     yr_soil_co2;
    float     yr_root_co2;
    float     yr_ch4;
    float     yr_dnno;
    float     yr_dnn2o;
    float     yr_dcno;
    float     yr_dcn2o;
    float     yr_dnn2;
    float     yr_soil_nh3;
    float     yr_uptaken[8];
    float     yr_minern;
    
    float     yr_plant_nh3;
    float     yr_leach_hu;
    float     yr_leach_un;
    float     yr_leach_NO3;
	float     yr_leach_urea;
	float     yr_leach_DOC;
	float yr_runoff_SOC, yr_runoff_ION, yr_runoff_P;
    float     by_pass_no3;
    float     flood_leachn;
    float     yr_addfer;
	float     seasDay1_129_wrunoff,seasDay130_365_wrunoff,seasDay305_365_wrunoff,seasDay1_304_wrunoff,seasDay288_365_wrunoff;
    float seasDay1_129_wleach,seasDay130_365_wleach,seasDay305_365_wleach,seasDay1_304_wleach,seasDay288_365_wleach;
	float seasDay1_129_N2O,seasDay130_365_N2O,seasDay305_365_N2O,seasDay1_304_N2O,seasDay288_365_N2O;
	float seasDay1_129_NH3,seasDay130_365_NH3,seasDay305_365_NH3,seasDay1_304_NH3,seasDay288_365_NH3;
	float seasDay1_129_Nleach,seasDay130_365_Nleach,seasDay305_365_Nleach,seasDay1_304_Nleach,seasDay288_365_Nleach;
	float seasDay1_129_Nrunoff,seasDay130_365_Nrunoff,seasDay305_365_Nrunoff,seasDay1_304_Nrunoff,seasDay288_365_Nrunoff;
	float seasDay1_129_precip,seasDay130_365_precip,seasDay305_365_precip,seasDay1_304_precip,seasDay288_365_precip;
	float seasDay1_129_atemp,seasDay130_365_atemp,seasDay305_365_atemp,seasDay1_304_atemp,seasDay288_365_atemp;
	float seasDay1_harv_atemp, seasDay1_harv_precip,seasDay1_harv_wrunoff,seasDay1_harv_wleach,seasDay1_harv_denit,seasDay1_harv_N2O,seasDay1_harv_NH3,seasDay1_harv_netNmin,seasDay1_harv_Nleach, seasDay1_harv_irri,seasDay1_harv_trans,seasDay1_harv_evap;
	float seasDay1_pDate_atemp,seasDay1_pDate_precip,seasDay1_pDate_wrunoff,seasDay1_pDate_wleach,seasDay1_pDate_denit,seasDay1_pDate_N2O,seasDay1_pDate_NH3,seasDay1_pDate_netNmin,seasDay1_pDate_Nleach,seasDay1_pDate_irri,seasDay1_pDate_trans,seasDay1_pDate_evap;
	float seasDay182_365_atemp,seasDay182_365_precip,seasDay182_365_wrunoff,seasDay182_365_wleach,seasDay182_365_denit,seasDay182_365_N2O,seasDay182_365_NH3,seasDay182_365_netNmin,seasDay182_365_Nleach,seasDay182_365_irri,seasDay182_365_trans,seasDay182_365_evap;	
	float seasCO2Het1, seasCO2Het2, seasCO2Het3, seasNetNMin;
	float gs_N2O, gs_precip, gs_atemp;
	float ngs1_N2O, ngs1_precip, ngs1_atemp;
	float ngs2_N2O, ngs2_precip, ngs2_atemp;
	int countIrri;
	float cropCHU;
	float cropGDD;
	float dayLengthHr;//calculates dayLenghtHr based on latitude;
	float photoPeriodIndex;
	float seasPET, seasPETKC;
    float     yr_fixn[8];
    float     topc[21], topn[21];
    float     layerc[21],layern[21];
    double     yr_ini_water;
    float     yr_end_water;
    float     yr_DNassimN;
	float	  day_nitrif[22], day_denitrif[22], day_decomp[22],total_n2o[22];
    
    float     yr_prec_water;
    float     ini_snow_pack;
    float     ini_surf_water;
    float     ini_leaf_water;
    float     tirri;
    float     yr_snow_ev,yr_soilIce_ev;
    float     yr_fol_ev;
	float     yr_pond_ev;
    float     yr_trans;
    float     yr_soil_ev;
    float     yr_leach_water;
    
    float     PoolWater0;
    
    //float     litco22;
    char      site[80];
	char	  countryName[80];
	
	char	  stateName[120];
    float     latitude, longitude;
    float     PGI[8],OLDPGI[8],totalFFPGI[8],per[8][8],curveK_prev[8];
    float     factor_Eh;
    float     day_vol_nh3;
    //float     irri_water;
    float     yr_irri;
    float     f_TTT;

    float     day_leach_DOC;
    
    float     N_stress[8];
    float     straw_C, straw_CN;
    float     day_N_demand[8], day_N_demand2[8], plantP[8], yr_plantP[8], day_P_uptake[8], day_P_demand[8];
	float GrainP[8], LeafP[8], StemP[8], RootP[8];
    float PAR, max_temp, min_temp, Day_Hrs;
    float canopy_Tmean, canopy_Tmax, canopy_Tmin;
    float DTGA;//photosynthesis, kg CO2/ha/d
    float Canopy_Temp[26];
    float     w_temp[26];
    //int       I_Stage;
    float     X_Stage, Z_Stage;
    
    float     Root_Wt[8], Leaf_Wt[8], Stem_Wt[8], Grain_Wt[8],Pod_Wt[8],Root_ExuC[8],Root_ExuN[8];
	float TreeMatuAge[8], TreeCurretAge[8], TreeLeafMax[8], TreeLeafMin[8];
	float     old_Root_Wt[8], old_Leaf_Wt[8], old_Stem_Wt[8], old_Grain_Wt[8];
	
	float	  CF_water[8][MAXSOILLAYER];
	float	  CF_N[8];
	double	  lightStressFactor[8];
	double     cropRad[8];//actual radiation reaching crop
	double     cropRadAcc[8];//accumulation for cropRad;
	float     CropHeight[8];
	float     leafTemp_C[8];
	float	  totalRootDens[MAXSOILLAYER];

    float     Assim;//daily net growth. kg C/ha/d
    //float     GPP;
//    float     N_Str[9];
    float     Total_Resp;  //total respiration of plant kg C/ha/d (growth res. + maint. res.)
    float     surf_w;//surface water depth,m
    float     dw_temp;//daily avrage value of surface water temperature
    float     Surf_Temp;//daily surface temperature
    float     ch4_prod, ch4_prod1, ch4_prod2; // daily ch4 production rate (kg CH4-C/ha/d)
    float     plant_day_ch4;//emission flux of ch4 via plant(kg ch4-C/ha/d)
    float     ch4_day_oxid; //oxidation rate (kg ch4-C/ha/d)
    //float     ch4_dif;//emission rate of ch4 via diffusion (kg ch4-C/ha/d)
    //float     ch4_eb;//emission rate of ch4 via ebullition (kg ch4-C/ha/d)
    float     root_doc[8];//rice caborn rhizodeposition (kg doc-C/ha/d)
    float      biomass;//leaf_flag,;
    float     yr_PET, yr_ET,yr_PETCROP;
    //float     gs_ET;//, gs_rain;gs_PET,
    float     EFFAC;//total_Ndemand[8], 
    //float SOC;
    int muture_flag, graz, irri_flag;
    int farm_ID, clim_ID, site_ID, retard;
    float byflow;
    //float food_defi;
    float max_TDD[8], TDD[8], day_TDD[8];//, N_fix;
	float cumFlowerPrecip, soyFlowerWStress;
	float photoPeriodStress[8];
	float tillYieldFact;
	float obsGrain[300], obsLeaf[300], obsStem[300], obsRoot[300];
    //int mature_flag;
    float day_transp, day_evapor, PassiveCCN;

	float TTT,oldTTT;

	//new addition
	float day_leachhu, ddupn[8], add_SOC_litter,add_SOC_root,add_SOC_manure,add_SOC_weed;
	float old_Tmin, wddupn, OldT, old_tev, a_stress;//end_SOC,net_SOC,
	//float old_lh_out_water;
	//float drcvl; 
    //float lit_co2;//DRCB, DRCB1, DRCB2, 
    //float  dcbavai, fh_co2;//sumn,fb_nh4, fb_co2, fh_nh4, 
    float  old_leach_no3;
	int  k;//urea_day,
	float NDEF1, NDEF2;
	float Root_Depth;
	float TCNP;
	float RCNP;
	float CumVD;
	float Sum_Dtt;
	int Days_After_Sow;
	int Days_In_Stage;
	float old_Canopy_Tmax;
	float primeDenit;

	float root_up;
	//float sfer6, sfer7;
    int fer_layer;
	int manu_layer;
	float diTemp;
	float combinedpH,combinedpHDeep,OldTHr;
	int   flood_flag;
	float tilld;
	int FloDays, SatuDays;
	//int unFloDays;
	//int unFloDs;
	//int kkk1,kkk2;
	//float day_minen;
	double PPT[8], APT[8],PPTactual[8]; 
	double DayPETCROP[8];
	int ABC_day; 
	int ViewMode;
	int CountryCode, StateCode, MajorConcern, DailyRecord;
	int DBType;
	float day_pro_ch4_eb;
	int oxi;
	float Eh000;
	float day_soil_denitrification;
	float day_clay_N;//, N_balance;
	float w_n2o;
	float day_nitrify_N2O, day_nitrify_NO;//accumulator across layers
	char mDatabaseName[200];	
	int mOnlyRice, mInterDrain;
	double ini_soil_water, end_soil_water, day_bypass_influx, day_leach_water,day_tile_water,day_Deep_Perc;
	float ini_day_PoolWater, day_ET, yr_bypass_in, yr_water_in, day_intercept, yr_intercept;
	float day_soil_ev, day_snow_ev, day_pond_ev, dfol_ev, day_runoff, yr_runoff,day_soilIce_ev;
	//char CountyName[100];
	//float crop_t;//dsno3b, dsnh4b, dsno3c, dsnh4c, dsno3d, dsnh4d, dsno3e, dsnh4e, dsno3f, dsnh4f,  
	double prof_SON, prof_SIN, prof_SN, total_SN, prof_SOC, total_SOC, ch4_co2, CO2_CH4, prof_DOC;
	double ini_prof_SOC, end_prof_SOC, prof_fluxC;

	double ini_prof_inorgC = 0.0;
	double end_prof_inorgC = 0.0;

	float BalanceC, BalanceN, rain_N, yr_rainN;
	float InitialSOC, InitialSON, yr_influxN, yr_effluxN;//TerminalSOC, TerminalSON, 
	float day_addmc, day_inC, day_outC, day_inN, day_outN;//, day_assimN;
	float yr_addmP;

	//new crop functions
	int IFDAILY;
	float day_balance_ch4, yr_balance_ch4;
	float prof_Water, SnowMelt, inWater, outWater, total_Water, hrfol_ev, sslope, salinity;
	float day_surplus_water,  total_ice;//day_ice,
	float soilWaterStress; //keep track of soilWater available for crops.
	//float Pool_leach_NO3;
	float MicrobioIndex;
	int flood_num, LaiFlag;
	float day_inFertN,day_inManureN,day_inGrazeN,day_inStubN,day_inRainN;
	float day_inFertP,day_inManureP, yr_inFertP, yr_inManuP;
	
	float default_Mn, default_Fe, default_SO4;
	float crop_transp;
	float GrowthVegetative[8], GrowthReproductive[8], PsnEfficiency[8], PsnMax[8], InitialBiomass[8];
	float day_fixN[8];
	int   CropModel;
	float SoilStructEffect;//Soil Pedo Transfer Function for effect of aggregate structure over time.
	
	int r_NoTill;
	//char r_Province[200];
	//float r_CO2, r_AirTemp, r_RainChange, r_YieldIncrease, r_ResidueLeft, r_AnimalManure, r_HumanManure;
	//float r_FertRate, r_Irri, yr_assim;
	float sfer1,sfer2,sfer3,sfer4,sfer5,sfer6,sfer7;
	float Pfer1,Pfer2,Pfer3,Pfer4,Pfer5,Pfer6,Pfer7, Pso4;
	float WRI;
	float WaterRetentionDepth,MaxWTDepth;
	int WRL;
	float day_deficit, H_beef, H_dairy, H_pig, H_horse, H_sheep, H_hrs, day_grass_consume[8];
	float yr_graze_dung_C, yr_graze_dung_N, grazedN, yr_graze_urine_C, yr_graze_urine_N, day_DNassimN, yr_graze_urine_P, yr_graze_dung_P;
	int RegionCode;
	float DayCropWaterDeficit;
	float day_acetate, day_acetate_prod, day_acetate_cons;

	//float ch4_prod_root_co2; // Daily CH4 production rate (kg C/ha/d) from root-CO2
    //float ch4_prod_soil_co2; // Daily CH4 production rate (kg C/ha/d) from soil-CO2
    //float ch4_prod_root_doc; // Daily CH4 production rate (kg C/ha/d) from root-DOC
    //float ch4_prod_soil_doc; // Daily CH4 production rate (kg C/ha/d) from soil-DOC
	//float ch4_coeff2; // Coeff2 of CH4 transport through plant.
	//float CH4_RES; //! CH4 residue the day (kgC/ha)
	float WRTX, dw;//, irri_add_water
	float labile_manure;
	int StartYear;
	float CO2_IncreaseRate;
	char FertigationFile[200];
	float day_fert1, day_fert2,day_fert3,day_fert4,day_fert5,day_fert6,day_fert7,day_irri,day_dSOC, day_LeachN;
	int   grazFlag, till_flag, ddday, manuFlag;
	float Day_GrowthN[8], Day_C_growth[8], dayG_grain[8], dayG_root[8], dayG_leaf[8], dayG_stem[8],dayG_pod[8];
	float day_C_mine, day_N_mine, day_N_assim, yr_C_mine;//, day_frostMicrobe, yr_FrostBio;
	float prof_frostDOC, ini_SON, ini_SIN, prof_ClayNH4, ini_ClayNH4;
	float yr_plant_demand, yr_TotalEvap, ini_N_fix[8], vascularity[8];//, LabileLitterC, LabileLitterN;//, yr_trans_WE
	int FloodingDays;
	float flood_N[10];//AdditionCO21, AdditionCO22, 

	float DayGrassCut, yr_CutGrain[8], yr_CutLeaf[8], yr_CutStem[8], yr_CutRoot[8];//yr_CutShoot,
	float DayGrassCut_C[8], DayGrassCut_N[8];
	float eachGrassCut[8][7];//track a grassCutting
	float eachGrassCutN[8][7];//track a grassCutting
	float yr_GrazeGrain[8], yr_GrazeShoot[8], yr_GrazeRoot[8], yr_GrazeStub;
	int MargenalFlood[30], ManureDays, UplandRice, FertSO4;
	int WaterControl, WTL, FertOption,nWTL;
	float RainfedDepth, RainfedPool;
	CString WT_file;
	float Manure_water, ManureAddCN;// PerennialRoots, CropAbsorbN[8], 
	float FertDayRelease[30], NIefficiency[30], NIduration[30], ReleaseDays, wFreezedoc;
	float UreaseEfficiency[30], UreaseDuration[30], UreaHydroInhibEf, UreaHydroInhibDu;
	//int FertMethodApp[30];
	int cwc, GrowStartDay, UreaHydroInhibDays;
	float DayLeafSenes[8],DayStemSenes[8],DayRootSenes[8],DayGrainSenes[8],DayShootSenesN[8],DayLeafSenesN[8], DayStemSenesN[8], DayRootSenesN[8], DayGrainSenesN[8],yrShootSenesN[8];
	float SurfaceWaterT, C_soil;
	float AppliedUrea, LateralInflux, u_PGI;
	int cropHarvestDay[8],flowering1Day[8], flowering2Day[8], flowering3Day[8],podDay[8],maturityDay[8],seedFillDay[8],emergenceDay[8], floweringDay[8],plantingDay[8];
	
	int cropGrowDays1, cropGrowDays2, cropGrowDays3;
	float seasEvap1, seasEvap2, seasEvap3, trans1, trans2, trans3;
	float Nmin1, Nmin2, Nmin3, Nimb1, Nimb2, Nimb3;
	float seasWL1, seasNH31, seasSoilN1, seasSOC1, seasSON1, seasNO31, seasCO21, seasWL2, seasNH32, seasSoilN2, seasSOC2, seasSON2, seasNO32, seasCO22,seasWL3, seasNH33, seasSoilN3, seasSOC3, seasSON3, seasNO33, seasCO23;
	float  seasMaxLAI1, seasMaxLAI2, seasMaxLAI3, SOC64, SOC66, SOC80, SOC304, SON64, SON66, SON80, SON304;
	float daySoilWater151, daySoilWater201, daySoilWater152, daySoilWater202, daySoilWater153, daySoilWater203;
	float FertAddNSA[3], FertAddCSA[3];
	float seasDenit1, harvSoilN1, seasDenit2, harvSoilN2, seasDenit3, harvSoilN3;
	float seasGrain[8], seasLeaf[8], seasRoot[8], seasStem[8], seasGrainN[8], seasLeafN[8], seasRootN[8], seasStemN[8];
	




	float growthStatus[8];
	int cropGrowDays[8];
	int cropYieldDry[8];

	int AnimalCode[10], m_unit;
	float TotalHeads[100];
   char AnimalNames[10][50];
   float Default_C_intake[10], Milk_C_fraction[10], Meat_C_fraction[10], Urine_C_fraction[10];
   float Dung_C_fraction[10], Enteric_CH4_C_fraction[10], Respiration_C_fraction[10], Default_N_intake[10];
   float Milk_N_fraction[10], Meat_N_fraction[10], Urine_N_fraction[10], Dung_N_fraction[10], Enteric_N2O_N_fraction[10];
   float livestock_C_demand[10][50], total_C_demand[366];
   float day_GrazeC, day_GrazeN;

   float day_graze_intake_C[10], day_graze_intake_N[10], day_graze_milk_C[10], day_graze_milk_N[10], day_graze_meat_C[10];
   float day_graze_meat_N[10], day_graze_urine_C[10], day_graze_urine_N[10], day_graze_dung_C[10], day_graze_dung_N[10];
   float day_graze_enteric_CH4[10], day_graze_enteric_N2O[10], day_graze_respiration_CO2[10], day_graze_dung_P[10];
	
	float SWT[12], LayerSoilWeight[21];
	int LL0, LL1, LL2, LL3, LL4, LL5, LL6,LL7,LL8,LL9,LL10,LL11,LL12,LL13,LL14,LL15,LL16,LL17,LL18,LL19,LL20,LL21, fertigate_flag, stem_age, drain_flag;
	
	float yr_end_grain, yr_end_leaf, yr_end_stem, yr_end_root;
	float day_Root_DOC, day_SOM_DOC; 
	float day_CO2_prod, day_Root_CO2, day_SOM_CO2;
	float day_H2_PROD, day_SOM_H2, day_ch4_H2_pool;
	int OverHotDays;
	float day_indirect_n2, day_indirect_n2o, yr_indirect_n2o, yr_indirect_n2;

	int x1, y1, z1, a1, b1, c1, Wf1[8], Wg1[8], Wfw1[8], rf1, fp1, Wfz1[8], We1[8], Wd1[8], Wh1[8];
	int wi1, ii1, j1, k1, l1, m1, n1, o1, p1, q1, s1, t1, w1, u1, v1, aa1, bb1;
	int cc1, lw1, hh1, dd1, ee1, ww1, yd;
	int pp_crop;
	int pp_stub;
		float	  optffPGI[731][4];
	//Crop submodels
	//float InitialCropBiomass; //Intitial crop weight, kg dry matter/ha
/*	float WLVI; //Intitial leaf weight, kg dry matter/ha
	float WRTI; //Intitial root weight, kg dry matter/ha
	float ALVI; //Initial LAI
	float SLC; //specific leaf weight constant, kg d,m./ha
	float DSI; //Initial development stage, 0.0-2.0
	float DS; //development stage
	float SLA; //specific leaf weight, kg d.m./ha
	float CPEW; //effect of water stress on C partitioning
	float DREW; //effect of water stress on crop development rate
	float PCEW; //effect of water stress on canopy gross photosynthesis 
	float WLV; //leaf weight, kg d.m./ha
	float GLV; //growth rate of leaves, kg d.m./ha/day
	float LLV; //loss rate of leaves, kg d.m./ha/day
	float CAGLV; //carbohydrates available for growth of leaves, kg/ha/day
	float CRGLV; //carbohydrates required for growth of each unit leaves, kg/kg leaf d.m.
	float WST, WSTI; //stem weight, kg d.m./ha
	float GST; // stem growth rate, kg d.m./ha/day
	float FSTR; // fraction of stem remobilized at flowering kg/kg
	float WIR; //weight of increment reserves (starch) since start simulation, kg/ha 
	float LSTR; //loss rate of stem reserves (starch), kg/ha/day
	float WRT; //root weight, kg dm/ha
	float WSO, WSOI; //storage organs weight, kg dm/ha
	float GSO; //growth rate of storage organs, kg dm/ha/day
	float WEPSO, FEPSO; //weight of economic part of storage organs, kg dm/ha
	float GRT; //growth rate of root, kg dm/ha/day
	float LRT; //loss rate of root weight, kg dm/ha/day
	float WSS; //shoot + storage organs, kg dm/ha
	float WCR; //total crop weight, kg dm/ha
	float WLVD;//weight of dead leaves, kg dm/ha
	float WRTD;//weight of dead roots, kg dm/ha
	float CAGST; //carbohydrate available for stem growth (kg/ha/day)
	float CRGST; //weight of carbohydrate required by stem growth (kg/kg) 
	float CAGRT; //carbohydrate available for root growth (kg/ha/day)
	float CRGRT; //weight of carbohydrate required by root growth (kg/kg) 
	float CAGSO; //carbohydrate available for storage organs growth (kg/ha/day)
	float CRGSO; //weight of carbohydrate required by storage organs growth (kg/kg) 
	float CAGCR; //Carbohydrate available for growth of total crop, kg/ha/d;
	float PCGW; //Gross photosynthsis, kg CO2/ha/d;
	float RMCR; //maintenance respiration of total crop, kg CO2/ha/d
	float RGCR; //growth respiration of total crop, kg CO2/ha/d
	float CAGSS; //Carbohydrate available for growth of shoot + storage organs, kg glucose/ha/d
	float CELV; //carbohydrate export from leaf and stem (excluding remobilization), kg glucose/ha/d
	float RMLV; //maintenance respiration of leaves, kg CO2/ha/d
	float RMST; //maintenance respiration of stems, kg CO2/ha/d
	float RMMA; //maintenance respiration due to motabolic activity, kg CO2/ha/d
	float CELVN; //number of days that CELV is negative, day
	float PCGC; //gross canopy photosynthesis, kg CO2/ha/d
	float PLMX; //maximum photosynthesis rate of single leaves, kg CO2/ha/h
	float PLEA; //intial efficiency of absorbed light use by leaves
	float PLEI; //actual intial efficiency of absorbed light use by leaves
	//float ALV; //LAI
	float RDTM; //measured daily radiation (400-1400 mm), J/m2/d
	int DATE; //Julian day
	float LAT; //latitude
	float RDTC; //daily radiation above atmosphere, J/m2/d
	float FRDIF;
	float DLA; //day length, astronomical, hrs
	float DLP; //day length effective for photoperiodism, hrs
	float DSINBE, SOLC, COSLD, SINLD;
	float PLMXP; //PLMX for standard SLC and otimal conditions, kg CO2/ha/h
	float PCGT; //accumulative gross photosynthesis, kg CO2/ha
	float RCRT; //accumulative crop respiration, kg CO2/ha
	float PCNT; //accumulative net photosynthesis, kg CO2/ha
	float RMCT; //accumulative crop respiration, kg CO2/ha
	float RMSO; //maintenance respiration of storage organs, kg CO2/ha/d
	float RMRT; //maintenance respiration of root, kg CO2/ha/d

	float RMCLV; //standard coefficient for leaf maintenance respiration, kg CO2/kg/d
	float TPEM; //temperature effect on maintenance respiration
	float TPAV; //24-hour average air temperature, degree C
	float TPR; //reference temperature for maintenance respiration, degee C
	float RGLV, RGST, RGSO, RGRT, RLSR;
	float SSC; //specific stem weight constant, kg dm/ha
	float WLVT;
	float WLVST;
	float WLVSO;
	float HI;
	float RSH;
	float WSTR;
	float GLA, LLA, GSA, SLN; 
	float DRV, DRED, DRR;
	float DRCV, DRCR, TPAD;
	float FCST, FCLV, FCSO, FCRT;//C/d.m. ratio for stem, leaf, storage organs, root
	float FIEC;//ratio of internal/external CO2 concentrations for stomata
	float TRW; //actual transpiration rate, mm water/d
	float TRC;//potential transpiration rate, mm water/d
	float VPDC;//water vapour deficity, kPa
	float PLEH; //direct effect of air humidity on maximum photosynthesis rate
	float TRCPD;//potential transpiration of canopy due to absorbed radiation, mm/d
	float TRCPR;//potential transpiration of canopy due to air drying power, mm/d
	float VPA;//air humidity, kPa
	float RSLL;//leaf resistance for water vapour diffusion, s/m
	float RSBL;//boundary layer resistance for water vapour diffusion, s/m
	float RSTL;//resistance for water vapour diffusion, CO2 and heat due to turbulence in canopy from average leaf, s/m
	float CO2E;//ambiant CO2 concentration, vppm
	float CO2I;//CO2 concentration in stomatal cavity, vppm
	float PLNA;//daytime average leaf net photosynthesis per unit area, kg CO2/ha/d
	float RSLLM;//minimum value of leaf resistance for water vapour diffusion, s/m
	float WDLV;//width of leaves, m
	float WDSAD;//daytime average wind speed, m/s
	float PLHT;//plant height, m
	float TRRM;//potential transpiration rate per unit rooted length, mm/d/m
	float ZRT;//rooting depth, m
	float GZRT;//growth rate of root depth, m/d
	float ZRTM;//maximum root depth, m
	float ZRTMC;//maximum root depth for crop, m
	float ZRTMS;//maximum root depth for soil, m
	float TKLT;//thickness of combined soil compartments, m
	float GZRTZ;//maximum growth rate of root depth, m/d
	float WSERT;//effect of water stress on root water uptake
	float TERT;//effect of temperature on root growth
	float EVSPR;//potential soil evaporation due to radiation, mm/d
	float EVSPD;//potential soil evaporation due to air drying power, mm/d
	float RFS;//soil reflection coefficient for daily total radiation, 
	float RSBS;//boundary layer resistance for water vapour diffusion from soil, s/m
	float RSTS;//resistance to diffusion for water vapour diffusion, CO2 and heat due to turbulence in canopy from soil, s/m 
	float RFSD;//soil reflection coefficient for daily total radiation in dry days
	float WCL1;//relative water content per layer, m3/m3
	float WCST1;//volumatric water content at saturation, m3/m3
	float WDCL;//width of soil cloth, m
	float WDSS;//wind speed near the soil surface, m/s
	float WDSAV;//wind speed, 24 hr average, m/s
	float WDST;//observed daily wind speed, m/s
	float HUAAT;//observed daily air humitidy, kPa
	float RAIN;//daily rainfall, mm/d
	float WUPC; //water use efficiency, current, related to net photosynthesis, water transpired per kg CO2 fixed (net) at daytime, kg water/kg net CO2
	float WUPT; //water use efficiency, total net photosynthesis and transpiration, kg water/kg net CO2
	float EVSC;//daily soil potential evaporation, mm/d
	float DSLR;//number of days since last rain
	float ZRTI;//initial root depth, m
*/
	int C_type[8];	
	float dtrans, day_WT, day_dWT;//, DFcrop;
	//float season_N_stress[8];// yr_IrriWater, yr_LeachWater, 
	
	int DailyCO2, ObservedLAI, LAIday, LandUse;
	float DayAirCO2, FieldLAI, leaf_area_N, WaterGetherIndex, WaterLeakRate;
    float CropSumN[8];//, dayCropDeficit;

	int ShallowFloodFlag, CFloodDays, CDryDays;
	int crop_ID[100], CoverCrop[8];
	
	float RDbiomas[366],RDtrans[366],RDevap[366],RDirri[366],RDleach[366];
#ifdef DROUGHT
	float RDwaterstress[366],RDtotalwater[366],RDwater1[366],RDwater2[366],RDwater3[366],RDwater4[366],RDwater5[366];
#else
	float RDdSOC[366],RDco2[366],RDn2o[366],RDno[366],RDnh3[366],RDch4[366],RDLeachN[366];
#endif

	float DayFert1[366], DayFert2[366],DayFert3[366],DayFert4[366],DayFert5[366];
	float DayFert6[366],DayFert7[366];

	float DayFixFert1, DayFixFert2,DayFixFert3,DayFixFert4,DayFixFert5;
	float DayFixFert6,DayFixFert7;

	float surface_litter, day_FreshWasteNH3, crop_PT[10], crop_AT[10];//yr_optimum_yield, yr_TDD,
	float WaterPoolMax, BaseMicroIndex;//WaterPoolFidcp, WaterPoolWiltp, 
	float CropWaterDemand[8], crop_T_demand[8], crop_trans[8], max_N_fix[8];
	int HarvestDay[8];
	float AddHum, day_inLitterN, day_NetN, day_addrn;
	float day_GWsuply, yr_GWsuply, PI, yr_PE, DrainEfficiency;//maxN, 

	float crop_N_stress[8], crop_water_stress[8], wind_speed, max_root_length[8], root_length[8],crop_PPT[8];
	int crop_N_stress_days[8], crop_water_stress_days[8],crop_PPT_days[8], cropTempStressDays[8];
	int crop_days[8];
	int perRegrow[8];//variable to track whether perennial is on secondary+ growth.
	int perRegrowGDD[8];//variable to track whether perennial has grown
	int perCut1EstGDD;//set GDD value for 1st perennial cut 650 GDD in establishment year
	int perCut1ProdGDD; //set GDD value for 1st perennial cut at 450 GDD in production year
	int perCut2ProdGDD;//set GDD value for 2nd cuts at 520 GDD
	int perGDDSinceLastCut;//tracks the GDD since last perennial Cut.

	int SMC_k, SMC_SampleSize, SMC_item[60], Option;
	float SMC_value[60], SMC[60], yr_PrecWater, add_liq_N;
	float ProdCGrain[8],ProdCShoot[8],ProdCRoot[8], ProdC[8], YrProdC[8];
	float temp_Root_Wt;//root_litter, root_litter_CN, root_litter_N, day_RootExudate, 
	float day_fineroot_C, day_fineroot_N, NO3[50], NH4[50], DayPET, act_DayPE, yr_WindSpeed;
	float DayAET, yr_AET;
	int UseION, ReDefineIONday, IONdata, IONlayer[50], WiltFlag[8], PerennialFlag[8];
	float EndWaterPool, AdjustNO3, AdjustNH4;
	float root_exudates;
	float day_shoot_CO2[8], day_stem_CO2[8], soil_hete_CO2, dPlantBiomass, Psn, EcoCO2, NEE;
	float yr_shoot_CO2, yr_CropGPP, yr_Psn, yr_EcoCO2, yr_NEE;
	float DClitter, DChumads, DChumus, PassiveC, root_dCO2;//cut_root_litter[8],fine_root_pool[8],
	float f_grain[8], f_leaf[8], f_stem[8], f_root[8], yr_GrazeDemandC, FineRootCN;//, MicrobeDemand_DOC_base;//MicrobeDemand_DOC, 
	float SurfaceUrea, yr_FineRootN, frost_doc;//, frost_N; 
	float yr_dSON, yr_dSIN, yr_dSoilWater, yr_total_ev, yr_NH3_deposit;
	int wetland_flag, ManureMethod[366];
	float day_runoff_N, yr_runoff_N, day_runoff_C, yr_runoff_C;//
	float DayAverageWater[MAXSOILLAYER];
	float snowfall, precipitation, CO2_factor, ProfileN[6], FertAddN[6], remain_root, DayIniWaterPool;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, m_SurfOutflowIntensity, m_GroundOutflowIntensity;
	float day_irri_N, yr_irri_N, day_frostDOC, yr_frostDOC, day_inert_C, yr_inert_C;
	float ch4_pool, crop_NH3_absorp[6];//yr_CropN_air[6], day_CropN_air[8],, cropN_demand[6]
	int fert_flag;
	float slurry_doc, IrriWater, day_IrriWater, yr_soilN_from_Nfixation, day_soilN_from_Nfixation[8];
	double T_SOC, old_T_SOC;
	float sum_shoot_CO2, sum_stem_CO2, TotalCropBiomass;//, DayPTF[8];//RFsoc,
	int MC_StartDay, MC_EndDay, CropNumbers, IniCropNumbers, WCLeftDays[6];
	float day_need_N[8], yr_need_N[8];
	float Yr_PlantBiomass[8], TotalSoilC;//, day_RootCO2;
	float Dwilt[8];//, CropEndN[8];//deep_doc, ini_deep_doc, 
	int plastic_flag, dFlag;
	float OLD_SOC, old_SN;
	int NO3_flag, Mn_flag, Fe_flag, SO4_flag;
	float day_farm_to_field_N, day_farm_to_field_C, day_farm_to_field_P, day_farm_to_field_H2O;
	float day_FM_C,day_FM_N,day_FM_H2O;
	int SCSuse, manuMethod;
	float day_SumPT;
	//float DDW[366];
	float yr_Lagoon_to_field_N_T, yr_Lagoon_to_field_C_T, yr_Lagoon_to_field_P_T;
	float yr_Compost_to_field_C_T, yr_Compost_to_field_N_T, yr_Compost_to_field_P_T;
	float yr_Digester_to_field_C_T, yr_Digester_to_field_N_T, yr_Digester_to_field_P_T;
	float yr_House_to_field_C_T, yr_House_to_field_N_T, yr_House_to_field_P_T;
	double yr_Lagoon_to_field_H2O_T, yr_Compost_to_field_H2O_T, yr_Digester_to_field_H2O_T, yr_House_to_field_H2O_T;
	float NIDuration0, NIDuration1;
	int UreaAppDays, DAA, SlowReleaseDays,slowReleaseCounter;
	float IniFixFert1,IniFixFert2,IniFixFert3,IniFixFert4,IniFixFert5,IniFixFert6,IniFixFert7;
	float albedo, humidity, ch4_doc_pool[MAXSOILLAYER];// day_ch4_doc_pool;//
	float LeafN[8], StemN[8], RootN[8], GrainN[8],PodN[8];
	float DayGrow_LeafN[8], DayGrow_StemN[8], DayGrow_RootN[8], DayGrow_GrainN[8], DayGrow_PodN[8];
	float V1Growth,V2Growth,V3Growth,R1Growth,R2Growth;//parameters for crop Growth to replace polynomials
	float V1GrowthPGI, V2GrowthPGI, V3GrowthPGI, R1GrowthPGI, R2GrowthPGI; //parameters for growth to explain broad phenology.



	float MaxLeafN[8], MaxStemN[8], MaxRootN[8], MaxGrainN[8], ReserveN[8];
	int NoRainFlag;
	int cropT, upFertCrop;//cropType index
	double StormIndex, horricane_event, hail_event, day_SoilWater, DayPT2, DayPT0, DayPT1, DayPT3;//, TodayPT;
	
	float Profile_OrgP, Profile_LabP, Profile_ComP, Profile_AdsP, DayFertRelease[8], yr_InputRoot_DOC;
	int SlurryFlag;//, FertMethod;
	float TotalDOC[MAXSOILLAYER];

	float LayerDeficit, DayAT, act_DayAT, day_H2S_flux, day_root_resp;//DayWaterStress, 
	float ini_prof_litter, ini_prof_humad, ini_prof_humus, ini_prof_doc, ini_prof_co2, ini_prof_ch4, ini_prof_blackc;
	float end_prof_litter, end_prof_humad, end_prof_humus, end_prof_doc, end_prof_co2, end_prof_ch4, end_prof_blackc;
	float end_SON, end_SIN, end_ClayNH4;
	//Painting
	
	float ManningRoughOverflow;
	float hrDemand, FloodWater_N, pen_soil_wfps, wind_damage_flag;
	int Transplant[10],farm_flag;
	float jarovization_flag, yr_flush_H2O;


	float yearlyNStress[10][10],yearlyNUptake[10][10];
	int yearlyNStressYear[10][10];
	float averageNStress[10],averageNUptake[10];
	int cropRotType[10];
/*	/////////////////////////////////////

#ifdef DROUGHT
	float DDcrop[366][10][30][3][2];
	float DDWtotal[366][10][30][3][2];
	float DDWstress[366][10][30][3][2];
	float DDW1[366][10][30][3][2];
	float DDW2[366][10][30][3][2];
	float DDW3[366][10][30][3][2];
	float DDW4[366][10][30][3][2];
	float DDW5[366][10][30][3][2];
	float DDtrans[366][10][30][3][2];
	float DDevap[366][10][30][3][2];
	float DDleach[366][10][30][3][2];
	float DDirri[366][10][30][3][2];
#else
	float DDbiomass[366][10][30][3][2];
	float DDdSOC[366][10][30][3][2];
	float DDco2[366][10][30][3][2];
	float DDn2o[366][10][30][3][2];
	float DDno[366][10][30][3][2];
	float DDnh3[366][10][30][3][2];
	float DDLeachN[366][10][30][3][2];
	float DDch4[366][10][30][3][2];
	float DDtrans[366][10][30][3][2];
	float DDevap[366][10][30][3][2];
	float DDleach[366][10][30][3][2];
	float DDirri[366][10][30][3][2];
#endif

#ifdef HYDRO//===Record daily and month result;dengjia===
// record the daily result
	float DDmuslerunoff[366][10][30][3][2];
    float DDmuslesedyld[366][10][30][3][2];
    float DDmuslesoc[366][10][30][3][2];
    float DDmusleson[366][10][30][3][2];
    float DDmuslenh4[366][10][30][3][2];
    float DDmusleno3[366][10][30][3][2];
    float DDmuslenh3[366][10][30][3][2];
    float DDmusleurea[366][10][30][3][2];
    float DDmusleclayn[366][10][30][3][2];
	
// sum some daily result
	float DDsumrunoff[366][10][30][3][2];
	float DDsumno3[366][10][30][3][2];
	float DDsumn[366][10][30][3][2];

// record month result
	float MMleach[13][10][30][3][2];
    float MMleachN[13][10][30][3][2];
    float MMmuslerunoff[13][10][30][3][2];
    float MMmuslesedyld[13][10][30][3][2];
    float MMmuslesoc[13][10][30][3][2];
    float MMmusleson[13][10][30][3][2];
    float MMmuslenh4[13][10][30][3][2];
    float MMmusleno3[13][10][30][3][2];
    float MMsumrunoff[13][10][30][3][2];
    float MMsumno3[13][10][30][3][2];
    float MMsumn[13][10][30][3][2];
#endif
	/////////////////////////////////////*/

//#ifdef HYDRO//=== Variable definition;dengjia===
    float scs_runoff; //runoff (mm)
    float sedyld;//the sediment yield on a given day(metric tons)
    float sub_km;//the hru area
	float MaxHalfHR;

	float yr_muslerunoff;
	float yr_muslesedyld;
	float yr_muslesoc;
	float yr_musleson;
	float yr_muslenh4;
	float yr_musleno3;
	float yr_muslenh3;
	float yr_musleurea;
	float yr_musleclayn;
    //record daily reslut
	float RDmuslerunoff[366],RDmuslesedyld[366],RDmuslesoc[366],RDmusleson[366];
	float RDmuslenh4[366],RDmusleno3[366],RDmuslenh3[366],RDmusleurea[366],RDmusleclayn[366];	
		float depthsed;//the depth of the soil layer eroded by runoff
	float rcvlmusle,rclmusle,rcrmusle,CRB1musle,CRB2musle,crhlmusle,crhrmusle,dphummusle;	
	float sonmusle, nh4musle, no3musle, nh3musle, ureamusle, claynmusle, socmusle;
	float LabPmusle, AdsPmusle, OrgPmusle, wCH4_C, yr_manure_water;
	int RainfedRice_flag, crop_terminator, irri_close, RiceDrySeeding, rice_maturity_flag;
	float day_ch4_co2_pool, day_ch4_pool, IniProfWater, IniWaterPool, EndProfWater;
	float EndSON, EndSOC, EndSIN, EndStub, IniSON, IniSOC, IniSIN, IniSP, EndSP;
	float ini_clay_N, whumusn1, whumus1, whumusn2, whumus2;
	float IniLitter, IniActHumus, EndLitter, EndActHumus, IniLitterN;
    float IniActHumusN, EndLitterN, EndActHumusN;
	float wno31, wnh41, wnh31, wurea1, wno1, day_clay_n1, ini_N_gases;
	float wno32, wnh42, wnh32, wurea2, wno2, day_clay_n2, end_N_gases;
	int flood_end;

#ifdef ISOTOPE

	float del13C_CO2, del13C_DOC;
	float CO2_12[MAXSOILLAYER], CO2_13[MAXSOILLAYER];
	float DOC_12[MAXSOILLAYER], DOC_13[MAXSOILLAYER];
	float CH4_12[MAXSOILLAYER], CH4_13[MAXSOILLAYER];
	float delCH4[MAXSOILLAYER], del_fCH4, del_fCO2;
	float fCH4_13, fCH4_12;
	float day_CO2_13, day_CO2_12, day_DOC_13, day_DOC_12, day_CH4_13, day_CH4_12;
	float day_prod_CH4_13, day_prod_CH4_12, day_oxid_CH4_13, day_oxid_CH4_12;
	
#endif
	
	
	
	
	
	//#endif
    //changed by liujm
#ifdef DEGUI
	int DNDClinuxgo(int MODE, int SoilYear, float ha, char* cropping_system, 
		       int province, int county, int county_ID1, int landuse,
			   int MonteCarlo, int scale, int S_ThisYear, char* r_Province, int ZXH, int Batch, 
			   int sampple, int RRRRR, int IrriType, char* country_ID, int livestock, int Monitor,
			   int drc, int DroughtID, char f_region[6][150], char* DroughtYield, int FFN, char* BatchName, int FarmField);
#else
	int DNDC100go(MODEL_LINK_INFO* pLinkInfo, int MODE, int SoilYear, float ha, char* cropping_system, 
		       int province, int county, int county_ID1, int landuse,
			   int MonteCarlo, int scale, int S_ThisYear, char* r_Province, int ZXH, int Batch, 
			   int sampple, int RRRRR, int IrriType, char* country_ID, int livestock, int Monitor,
			   int drc, int DroughtID, char f_region[6][150], char* DroughtYield, int FFN, int FarmField,
			   char *BatchPass);
#endif

	int DNDC101go(MODEL_LINK_INFO* pLinkInfo, int MODE, int SoilYear, float ha, char* cropping_system, 
		int province, int county, int county_ID1, int landuse,
		int MonteCarlo, int scale, int S_ThisYear, char* r_Province, int ZXH, int Batch, 
		int sampple, int RRRRR, int IrriType, char* country_ID, int livestock, int Monitor,
		int drc, int DroughtID, char f_region[6][150], char* DroughtYield, int FFN, int FarmField);
	
	void initiation(int facility);
	void read_in_site(int MODE, int Batch);
	int read_in_soil_parm(int MODE, int SoilYear, int MonteCarlo);
	int read_in_extra_parm(int MODE, int SoilYear, int MonteCarlo);
	void read_in_crop(int MODE, int GlobeData, CString FCT40);
	void read_in_cropini(int MODE, int GlobeData, CString FCT40);
	void read_in_LAI(void);

	int read_in_vege(int MODE, int CU, int ccwc);
	int read_in_clim(int DroughtID);
	int read_in_climy(int MODE, int drc, int DroughtID);
	int write_out_NStress();
	int read_in_NStress();
	void read_in_irri(int MODE, int IrriType, CString FCT40);
	void read_in_OBSYield(int MODE);
	int read_in_till(CString FCT40);
	int read_in_extra(CString FCT40);
    int read_in_fert(int MODE, CString FCT40);
    int read_in_manu(CString FCT40);
	int read_in_cut(CString FCT40);
	int read_in_graz(CString FCT40);
	int read_in_plastic(CString FCT40);
	int read_in_flood(int MODE, CString FCT40);
	void CreateObservedDayWT(void);
	void CreateEmpiricalDayWT(void);
	float day_zero(void);
	void zero_DayFlux(void);
	char weatherName[80];
	float Picewise_Line_Value(float x, float *xx, float *yy, int Points);
	//void read_in_SeedDensity_CM1(void);
	void Hint (char *Hint_Msg1, char *Hint_Msg2);
	float Line_Value(float x, float x1,float y1, float x2, float y2);

	void frame(MODEL_LINK_INFO* pLinkInfo, char *countryName, char *stateName, char* xxID, int MODE, int year, char *weatherName);
	//void FM_frame(MODEL_LINK_INFO* pLinkInfo, char *countryName, char *stateName, char* site, int MODE, int year);
	void paint(MODEL_LINK_INFO* pLinkInfo, int MODE, int c_ViewMode, char* cropping_system);
	//void crop_note(MODEL_LINK_INFO* pLinkInfo, char *cropName, int MODE, int c_ViewMode, int landuse);

	void profile_accum(int l, float* newh, float sumn, float fb_nh4, float fh_nh4,
	       float* w_no2, float* w_no3,
	       float* w_nh4, float* w_nh3, float* wurea, float* wpool_no,
	       FILE*fCB, FILE*fNB, float* w_n2o, float* w_n2,
		   float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		   float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		   float *EndSON, 
		   float *soc, float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *crhl, float *crhr,
		   float *dphum, float *doc, float *no3, float *nh4, float *nh3, float *n2, float *no, float *n2o, float *urea,
		   int flood_flag, int jday, int q,
		   float *no2, float *winert_C);
	void cn_pools(float w_no3, float w_nh4, float w_nh3, 
						   float wurea, float wpool_no, float w_n2o, float w_n2);
	void annu_accumu(void);
	void annu_accumu_manure_house(int jday);
	void annu_accumu_manure_storage(int jday);
	void soc_distribution(float *CRB1, float* CRB2, float* newh);
	int write_out_cropini(int MODE );
	int write_out_soil_parm(int MODE, int SoilYear, int SimuYears);
	int write_out_extra_parm(int MODE, int SoilYear, int SimuYears);
	void write_out_end_manure(void);
	void read_out_ini_manure(void);
	
	int write_out_wb(int Batch, char *BatchFileName, char *PassC1);
	int multi_yr_record(int MODE, int Batch, float EndSOC, char *Pass, char *PassC1);
	int write_out_annual_report(int MODE, float ha, int Batch, int livestock, FILE *fout, 
		FILE *fout2, int CL, float *FarmCropArea, float *FarmCropManureFraction, int drc, char *Pass, char *PassC1, char *PassL1);
	void MC_annu_accumu(void);
	float day_DOC_prod, day_DOC_cons;
#ifdef DEGUI
#else	
	void write_MonteCarlo(int sample, int county_ID1, char* cropping_system);
	void write_BatchSummary(int sample, char* site, char* cropping_system);
#endif
/*	void write_region_summary(int SoilYear, float ha, int landuse, int province, int county,
		int CountyIDX, char *DatabaseName, char *ScenarioName, int LandOrder, int year, 
		int StartYear, char* r_Province, int helai, int Batch, int GlobeData);*/
	void write_globe_summary(int SoilYear, float ha, char* cropping_system, int province, int county,
		int CountyIDX, char *DatabaseName, char *ScenarioName, int LandOrder, int year, 
		int StartYear, char* r_Province, int helai, int Batch, int GlobeData, int RRRRR, 
		int IrriType, char* country_ID, int livestock, int DroughtID, int drc, char f_region[6][150],
		char* DroughtYield, int SoilDataUse, int FFN);

	void CheckBalance(int ttmm);

	void SCS(float CN2,float sslope,float sol_sumfc,float sol_sw,float sw,float sol_ice,float precipday);
    void MUSLE(float PEAKR, float MSAND, float MCLAY, float MSILT, float ORGC, float MUSLEC, float sslope,float length, float USLE_P, float ROCK,float ha);
    float USLE_K(float MSAND,float MCLAY,float MSILT,float ORGC);
    //float USLE_C(float C,float COV);
    float USLE_LS(float sslope,float length);
    float PEAKRUNOFF(float a15,float ch_l,float ch_n,float ch_s, float slsubbsn,float ov_n,float sub_slp,float ha);
    float alph(float precipday,float rain_yrs,float adj_pkr,int mon,float *rain_hhsm,int *pcpd,float *pcp_stat);
   //void read_in_sitemusle();
   //void read_in_soilmusle();
   //void read_in_climmusle();
	// record month record
	//void  MonthData(int S_ThisYear, int landuse, int S_SoilYear, float crop_ha, int IrriType);
    //void  Month_record(int S_SimuYears, int ii_ha, char* CountryName, char* ScenarioName, int cell_ID1, int crop_number, char* r_Province, int IrriType);
	void SCS_MUSLE(int scale, float ha, int livestock);

	void irrigating(int MODE, float DayPET);
	void fertilizing(void);
	float manuring(int livestock, int scale, int FarmNumber, float *FarmCropArea, 
		float *FarmCropManureFraction, int FarmField, FILE *ftf);
	float cutting();
	void alloc_litter_into_pools(float *AddCN, float *AddC, int oz, float *AddC1, float *AddC2, 
		float *AddC3, float *dInertC, int IfStub, float rcnrvl, float rcnrl, float rcnrr, float *nh4);
	float grazing();
	float PlasticCover(void);
	void day_flooding(int MODE);
	void tree_leaves_fall();
	float tilling(int* tilq_p, float *CRB1, float* CRB2,
		float *newh, float till_fact);//float* rhrl_p, 
	void stub_fall(void);
	void crop_harvesting(int scale, int ccwc);

	void init_soil_moisture();
	void snowfall_snowpack();
	void soil_temperature(void);
	void water_temperatue(void);
	//void Canopy_temperature(void);
	float potential_et(int ETM);
	float actual_et_PM_leaf(int ccwc);
	float potential_et_manure();
	void hour_loop(float hrPE0, float* DayFlux,float* dby_flux, int DroughtID, int YieldToday, 
		int drc, int scale, float ha, int livestock, int hr);
	void hourly_soil_temperature(void);
	//void hourly_transp_and_water_stress(int hr, int DroughtID, int YieldToday, int drc);
	double crop_transpiration(int irri_close, double PPTw, int ccwc);
	double crop_pretranspiration(int irri_close, double PPTw, int ccwc);
	void water_CompFactor();
	void N_CompFactor();
	void crop_Height();
	void light_CompFactor();
	void leafTemp(int ccwc);
	void leafTempMod(int ccwc);

	void evaporation_of_snow(float hrPE2, float* hrsnow_ev, float* hrPE25);
	void evaporation_of_soilIce(int hr,float* hrPE3, float* hrsoilIce_ev,float hrPE25);
	void rain_intercept(int hr, float* Throufall, float* Intercept );
	float pond_water_bypass_flux(float Throufall, int scale, float ha, int livestock);
	float water_delivery(int hr, float* DayFlux, float hrPE3);
	float clay_cracking(int hr);
	

	

	float paddy_water_delivery(int hr, float* DayFlux, float hrPE3);
	void annu_water_budget(float dby_flux);
	void water_diffusion(int hr);
	//void soil_freeze(void);
	float wetland_water_delivery(int hr, float* DayFlux,float hrPE3);
	float soil_EV(int hr, float* DayFlux, float hrPE3);
	void ini_crop(int MODE, int ccwc);
	void ini_cropAuto(int MODE, int ccwc);//for autoPlant
	
	//float Assim_Sub(float SCP, float Amax, float EFF, float KDF, float SINB, float PARDR, float PARDF);
	void n_uptake_by_crop(int ccwc);
	void growth_stage(int ccwc);
	void lai_definition_CM1(int ccwc);
	void root_respir(int ccwc);
	
	void crop_N_demand(int ccwc ,float till_fact);
	//void biomass_C_partition(int ccwc);
	void biomass_N_partition(int ccwc);
	void biomass_N_partition_per(int ccwc);
	//void weeds_demand_for_n();
	//void weeds_demand_for_n_CM1();
	//void n_uptake_by_weed();
	//void n_uptake_by_weed_CM1();
	void water_demand(float DayPET, int ccwc);
	void root_develop(int ccwc);
	void root_density(int ccwc);
	void crop_senescence(int ccwc);
	void crop_Leafsenescence(int ccwc);
	void crop_rejuvenation(int ccwc);

	//farming agent
	void farmAgent(float yearlyNStress[10][10],float yearlyNUptake[10][10],int cropRotType[10]);
		
/*	void crop_growth_CM1(int MODE, FILE *fLAI);
	float crop_FUPHOT();
	void crop_SUASTC(void);
	void crop_SUASTR(void);
	float crop_CALVT();
	float crop_CASST();
	float crop_CASTT();
	float crop_DRDT();
	float crop_DRRTT();
	float crop_DRVTT();
	float crop_PLMTT();
	float crop_PLMHT_f();
	void crop_TDD();
//	void crop_leaf_litter_deposition(float AddCN, float AddC);
	void crop_N_uptake();
	void crop_water_demand(float DayPET, float wreq_weed );
	void crop_root_CM1();
	void crop_transpiration_CM1(int MODE);
	void crop_SUEVTR(float RDTC, float RDTM, float RF, float FRD, float TPAD, 
		             float VPA, float RSL, float RSB, float RST, float *EVPR, 
					 float *EVPD);
	float crop_FURSC(float WDS, float ALV, float PLHT, float ZREF);
	float crop_PLHTT_f();
	float crop_FUWRED(float WDLV, float ALV, float PLHT, float WDS);
	float crop_FUVP(float TP);
	void crop_water_stress_CM1();
	void crop_N_demand_CM1();
*/





	


	void dndc_decomposition(float* CRB1, float* CRB2, float* newh, float* w_no2, 
		float* w_nh3, float* w_no3, float* w_nh4, float* wurea, float* wpool_no, 
		float till_fact, float* DayFlux, int tilq, 
		FILE*fCB, FILE*fNB, float* w_n2o, float* w_n2,
		int GN, int q, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
		float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
		float *dphum, float *doc, float *nh4, float *no3, float *no2, float *no, 
		float *n2o, float *n2, float *nh3, float *urea,
		int jday, float *co2, float *clay, float TTT, int flood_flag, float *day_wfps, int WTL,
		float *temp, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, float *ocini, float *h, 
		float *day_C_mine, float *day_N_mine, float *day_N_assim, float DClitter, float *litco22,
		float *litco23, int *st, float DChumads, float EFFAC, float DChumus, float *sph,
		int wetland_flag, float wind_speed, float *ice, float *day_soil_nh3,
		float *lai, float *PlantTakeN, float *maxmn, float leaf_water, float cropht, float base_nh3,
		float *day_N_demand, float *day_nup, float *day_fixN, float *day_DWater, float *day_plant_nh3, 
		float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, 
		float day_runoff, float *day_runoff_N, float *day_clay_N, 
		float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, float *ds_doc,
		int *crop, float *yr_fixn, float rainfall, float *soil_ph, float *winert_C,
		float *inert_C, int fert_flag, float *root_doc, float *day_O2, float RFM,
		float *SoilDepth, float *ttoo, float *sop, float *OrgP, float *LabP, float *AdsP, 
		float *ComP, float *sts, float day_leach_water, float MicrobioIndex, int facility, int manure_flag, float *manco2, float *manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2,
		 float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol, int manureCounter);
	void Substrate_leaching(int hr);
	void redefine_microbe(int l, float RFM, float TTT, int jday, float *soc, float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *crhl,
		float *crhr, float *dphum, float *mmm, float *clay, float *ocini, float *no2, float *no3, float *manurePool);
	void effect_temp_mois(int l, float *day_wfps, int WTL, float *temp, int LandUse, int flood_flag, int FloDays,
			float *RFM, int *st, float *ice, int q, float MicrobioIndex);
	void decomp_of_litter(int l, float *co2, float *nh4, float *h, float *temp, 
		float *day_wfps, float *day_C_mine, float *day_N_assim, float *DRCB, float DRCB1, float DRCB2, float RFM);
	void rcvl_decomp(int l, float* drcvl, float RFM, float DDRF, float till_fact, float* DRCB1, int tilq,
		float DClitter, float *rcvl, float *nh4,
		float *co2, float *CRB1, float *CRB2, float *day_C_mine, float *day_N_mine, float *day_N_assim,
		float rcnrvl, float rcnb, float *day_O2, int flood_flag);
	void manure_decomp(int l, float RFM, float DDRF, float till_fact, float* DRCB4, int tilq,
		float DClitter, float* manurePool, float manurePoolCN, float rcnb, float* nh4,
		float* no3, float* co2, float* CRB1, float* CRB2, float* day_C_mine, float* day_N_mine,
		float* day_N_assim, float* manco2, float* day_O2, float* h, int flood_flag);//manure pool


	void rcl_decomp(int l, float RFM, float DDRF, float till_fact,float* DRCB2, int tilq,
		float DClitter, float *rcl, float rcnrl, float rcnb, float *nh4,
		float *no3, float *co2, float *CRB1, float *CRB2, float *day_C_mine, float *day_N_mine, 
		float *day_N_assim, float *litco22, float *day_O2, float *h, int flood_flag);
	void rcr_decomp(int l, float RFM, float DDRF, float till_fact,
		   float DRCB1, float DRCB2, float* lit_co2,
		   float drcvl, float *CRB1, float* CRB2, float* DRCB,
		   float* sumn, int tilq, float *litco22,
		   float *litco23, float DClitter, float *rcr, float *nh4,
		   float *co2, float *day_C_mine, float *day_N_mine, float *day_N_assim,
		   float rcnrvl, float rcnb, float rcnrr, float *no3, float rcnrl, float *day_O2, float *h,
		   int q, int flood_flag, float *doc, float DRCB4, float* manco2);
	void decomp_microbes(int l, float RFM, float DDRF, float till_fact,
		float* CRB1, float* CRB2, float* fb_nh4, float* fb_co2, float* dcbavai,
		int tilq, int *st, float *nh4, float rcnb, float *crhr, float *crhl, float *co2, float *day_C_mine, 
		float *day_N_mine, float *day_N_assim, float DChumads, float EFFAC, float rcnh, float *doc, 
		int q, float *day_O2);
	void decomp_humads(int l, float RFM, float DDRF, float till_fact,
			  float hrh, float krh, float* fh_co2, float* newh, float* fh_nh4,
			  float* CRB1, float* CRB2, float dcbavai, float DRCB, int tilq,
			  float *clay, float DChumads, float *crhr, float *crhl, float *nh4, float rcnh, float rcnb,
			  float *co2, float *doc, float *temp, float *day_C_mine, float *day_N_mine, float *day_N_assim,
			  int *st, float *dphum, float rcnm, int q, float *day_O2,
			  float *OrgP, float *LabP, float *ComP, int jday);
	void decomp_humus(int l, float DDRF, int tilq, float till_fact, float *clay, float *h, float DChumus, 
		float *dphum, float *nh4, float *co2, float rcnm, 
		float *day_C_mine, float *day_N_mine, float *day_N_assim, float *day_O2, float *SoilDepth, float *temp,
		float RFM, int q, int flood_flag, float TTT, float day_leach_water, float *doc);
	void urea_hydrolysis(int l, float *urea, float *temp, float *day_wfps, float *nh4, float *sph, 
		float *h, int UreaAppDays, float *ttoo, int UreaHydroInhibDays, int flood_flag, int q, int manure_flag,int UIDay1,int UIDay2,
		 float *mmm, float *fldcap, float *wiltpt);
	void NH4_HCO3(void);
	void nh43_equil(int l, float *temp, float *sph, float *nh4, float *nh3, int q, float *h, float *day_wfps, int flood_flag,  float newmanuPH, float combinedpHDeep, int manureHour, float wind_speed, float NH3Vol);
	void nh3_volatilization(int l, float *temp, int flood_flag, int wetland_flag, float *nh3, int q,  
		float wind_speed, float *day_wfps, float *ice,	float *day_soil_nh3, 
		float *nh4, int jday, float *no3, int manureHour, int manureCounter);
	void nh3_uptake_release(float *lai, float *day_soil_nh3, float *PlantTakeN, float *maxmn,
							float leaf_water, float cropht, float base_nh3,
							float *day_N_demand, float *day_nup, float *day_fixN, float *day_DWater,
							float *day_plant_nh3, float *yr_NH3_deposit, int ccwc);
	void clay_adsorption(int l, float RFM, float *nh4, float *clay_nh4, float base_clay_N, float max_clay_N, int q, float *clay);
	
	void recover_layer_lables(int l, float* CRB1, float* CRB2, float* crhl, float* crhr, float* ocini);
	void riceland_ch4_oxidation();
	void dryland_ch4_oxidation();
	void earth_worm(int l, float RFM, float *h, float *rcvl, float *rcl, float *rcr);
	void dayLength(int jday, float latitude);
	void photoPeriod(float dayLengthHr, float max_TDD);

	void N2O_balloon(int GN, float till_fact, float *sts, float *h, int jday, int flood_flag, int FloDays, float rainfall,
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
		int farm_flag, float rno3, float *day_inRainN, float denitMulti, float nitMulti, float N2N2OFactor,float *day_nitrify_n2ol,float *day_denitrify_n2ol);

	void saturation_Eh(void);
	void soil_oxygen_profile(int l, int T, int rain_hrs, float bypass_f, 
		float air_poro_max, int flood_day, float *temp, int year, int jday, int q, 
		double water[25][250], float *day_wfps, float *h, float *sts, float *O2,
		float day_WT, int WTL, float total_ice, float TTT, float *day_rco2, float *co2,
		int flo_num, float *ice);	
	float CH4_paddy(int MODE, int GN, float *temp, float *clay, int flood_num, int FloDays, 
		float *Root_Wt, int q, float *Eh, float *sph, float *vascularity, int LandUse, float *day_rco2,
		float *R_Wt, float day_co2, float root_dCO2, int flood_flag, float *rcvl, float *rcl, float *rcr, 
		int *st, float rcnrvl, float rcnrl, float rcnrr, float MicrobioIndex, float *ch4, int WTL, 
		float day_WT, float *soil_ph, float *doc, float *nh4, float *ch4_prod, float *ch4_day_oxid,
		float *plant_day_ch4, float *day_wfps, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate, float *h, float *CRB1, float rcnb, float *co2, float *crhl, float *crhr,
		float air_temp, float *ch4_doc_pool, float *F_methanogen,
		int WaterControl, float *Tttoo, int jday, float rcnh, float *H2,
		float *day_ch4_CO2, float *day_ch4_1, float *day_ch4_2, float *SO4, float day_root_resp,
		float *PGI, int ShallowFloodFlag, float stub1, float stub2, float stub3, float *day_H2_prod);
	float CH4_peat(int MODE, int GN, float *temp, float *clay, int flood_num, int FloDays, 
		float *Root_Wt, int q, float *Eh, float *sph, float *vascularity, int LandUse, float *day_rco2,
		float *R_Wt, float *day_co2, float root_dCO2, int flood_flag, float *rcvl, float *rcl, float *rcr, 
		int *st, float rcnrvl, float rcnrl, float rcnrr, float MicrobioIndex, float *ch4, int WTL, 
		float day_WT, float *soil_ph, float *doc, float *nh4, float *ch4_prod, float *ch4_day_oxid,
		float *plant_day_ch4, float *day_wfps, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate, float *h, float *CRB1, float rcnb, float *co2);
	void ch4_ebulition(void);
	int write_out_dayw(FILE *fw, float DayPET);
	int write_out_days(FILE *fs, float DayPET);
	int write_out_dayc(FILE *fc );
	int write_out_co2(FILE* fco2);//new CO2 file
	int write_out_dayn( FILE *fn );
	int write_out_dayn2o(FILE *fn2o);//new N2O file for layers
	int write_out_multiCrop(FILE* fmcrop);//new N2O file for layers
	int write_out_dayg( FILE *fg );
	int write_out_dayEh(FILE *fEh);
	int write_out_dayp(FILE *fcrop);
	int write_out_daym(FILE *fma);
	void write_out_dayCB(FILE *fCB, FILE *fNB);
	int write_out_daysp( FILE *fsp );
	int write_out_daymicrobe(FILE *fmb);

#ifdef ISOTOPE
	int write_out_dayisotope(FILE *fis);
#endif
	//void DailyDataRead2(int year, int LandOrder, int SoilYear, float ha, int IrriType);

	//void Daily_record(int S_SimuYears, int S_county, char* CountryName, char* ScenarioName, int CountyIDX, 
	//	int crop_number, char* r_Province, int IrriType, int SoilDataUse);
	//void Daily_record2(int S_SimuYears, int S_county, char* CountryName, char* ScenarioName, int CountyIDX, int crop_number, char* r_Province, int IrriType, int SoilDataUse);

	void Record_summary();

	void site_files(char *county_name, float r_longitude, float r_latitude, 
					char *CountryName, char *state_name);
	void climate_files(char *climfile_ID, float r_latitude, float RainN, 
						float BaseCO2, CString county_ID1, float CO2IncreaseRate);
	void soil_files_new(int k, float SOC, float Clay, float pH, float BD, CString CountyID, int landtype);
	void soil_files(int k, float max_SOC, float min_SOC, float max_clay, float min_clay, 
					float max_pH, float min_pH, float max_BD, float min_BD, int landtype,
					int OnlyRice, int CROPID, int WRL);
	void map_county(MODEL_LINK_INFO* pLinkInfo, char *CountryName, char *ProvinceName, long int map_ID, 
							 int fill_color, int RegionCode, int CountryCode, int StateCode);
	void region_farm_files(int CROP_ID, char *CountryName, int province, int InterDrain, int MonteCarlo,
							int RegionCode, int CountryCode, int StateCode, char *cropping_system);
	int JulianDay(int month, int day);
	
	void map_scale(int RegionCode, int country_code, int state_code, float *qq, float *xx, float *yy);
	float day_ref_par(int Jday, float LATITUDE);
	//changed by liujm
	void map_state(MODEL_LINK_INFO* pLinkInfo, char *CountryName, char *ProvinceName, int databaseType, 
							int RegionCode, int country_code, int state_code);
	//changed by liujm
	void MappingCountry(MODEL_LINK_INFO* pLinkInfo, char *CountryName, char *ProvinceName, int RegionCode, int country_code, int state_code);

	//int WT_define();
	//void water_balance(void);
	//void YIELD1(float nn1, float nn2, float nn3);
	//void YIELD2(float nn1, float nn2, float nn3);
	//void YIELD3(float nn1, float nn2, float nn3);
	void soilCEC(void);
	void partition_vll_humad(float solid_CN, float AddC, float solid_MN, float *AddC1, float *AddC2, float *AddC3,
		float *AddHum, float rcnrvl, float rcnrl, float rcnrr, float rcnh);

	void alloc_manure_into_pools(float AddCN, float AddC, int oz, float *AddC1, 
		float *AddC2, float *AddC3, float *dInertC, float *AddHum, float *AddDOC);
	void ReDefineION(void);
	void total_crop_N(int ccwc);
	void crop_growth(int scale, float till_fact);
	//void SASTRO(void);

	void weather_damage(int damage, float w_event, int ccwc);
	void frost_damage(int ccwc);
	void daily_WT(FILE* fWT);
	void Mn_Fe_S_oxidation(void);
	void Chemodenitrification(int l, float *temp);
	void write_out_dayClim(FILE *fclim, int jday, char*site, int year, float air_temp, float precipitation,
		float wind_speed, float radiation, float humidity);
	//void O2_driven_Eh(int l, int T, float *sph, float *O2, float *Eh, float sts, float h);
	void P_adsorption(int q, float *LabP, float *AdsP, float *h, float *day_wfps, float *sts, float *mmm);

#ifdef MANURE
	int write_out_annual_report_treatment(int MODE, int FarmPart, float ha, int Batch, int livestock, 
		FILE *fout2, int Feedlot);
	int write_out_annual_report_feedlot(int MODE, int FarmPart, float ha, int Batch, 
												int livestock, FILE *fout2, int Feedlot);
	void Main_Feedlot(int year, int scale, FILE* fout2, char *F_CLIMD,
						float w_no2, float w_nh3, float w_no3, float w_nh4, 
						float wurea, float day_clayn, float wpool_no,
						int tilq, FILE* fCB, FILE* fNB, float w_n2, float litco22, float litco23, 
						float till_fact, float *Tttoo, 
						float ha, int Batch, int livestock, int q, char *PassL1, int FarmField, char *Pass, FILE* HSM,
						float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc);

	void Main_Treatment(int year, int scale, char *F_CLIMD, float w_no2, float w_nh3, float w_no3, float w_nh4, float wurea, 
						float day_clayn, float wpool_no, int tilq, FILE* fCB, FILE* fNB, 
						float w_n2, float litco22, float litco23, float till_fact, float *ttoo,
						float ha, int Batch, int livestock, FILE* fout2, char *PassL1, int FarmField, char *Pass, FILE* HSM,
						float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, int m_Temp);
	void FarmFacilityLagoon(void);
	void FarmFacilityCompost(FILE* HSM, float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc);

#endif

#ifdef HOURLY
	void write_out_HrSoilMoist(FILE *HSM);
	void write_out_HrSoilN(FILE *HSM, int T, int JDY);
#endif
};

#ifdef MANURE
class class_manure
{
	
public:

  // public member functions
	class_manure();
	~class_manure();

	//manure parameters///////////////////////////////////////////////////////////////
	int FN, GN, EMDD;
	int mm_AnimalType[5], mm_GroundSurface[5], mm_Ventilation;
	float mm_AnimalHeads[5], mm_FeedRate[5], mm_FeedProtein[5], mm_FeedTP[5];
	float mm_FeedNDFP[5], mm_FeedADFP[5], mm_FeedLigninP[5], mm_FeedFATP[5], mm_FeedASHP[5];//new nutrient
	float mm_BodyWeight[5], mm_DMFraction[5], mm_MilkProtein[5], mm_DayInMilk[5];//new nutrient
	float mm_FeedNDF[5], mm_FeedADF[5], mm_FeedLignin[5], mm_FeedFAT[5], mm_FeedASH[5];//new nutrient
	float mm_MilkProduct[5], mm_MeatProduct[5];
	float mm_UrineN[5], mm_DungN[5], mm_UrineC[5], mm_DungC[5], mm_UrineP[5], mm_DungP[5];
	float mm_DungWater[5], mm_UrineWater[5];
	float mm_FeedCNratio[5], mm_FeedC[5], mm_FeedN[5], mm_FeedP[5];
	float mm_InitialManure, mm_InitialMoisture, mm_InitialPH, mm_WaterAddition;	
	float mm_ManureDM,  mm_DungDM, mm_ManureWater[6], mm_BedCNN;
	float mm_BedAmount, FM_urea, FM_doc, ToLagoonUrea, ToLagoonDOC, ToLagoonWater, ToCompostWater, mm_CleanFrequency; 
	int mm_BedNumber, mm_BedType, mm_Bedding, LagoonStoreDays;
	float mm_GroundArea[5], FM_RMM;	
	char FeedFileName[200][50], ExcretionFileName[200][50];
	int InputFormat[5], AnimalTypes[5], NutritionModel[50];
	int mm_PenBedType, mm_PenBedFrequency, FieldAnimalType, FieldGrazeTimes;
	float mm_VentRate, mm_PenBedCN, m_LitterCN, mm_BedApplications;
	float mm_PenBedAmount, FieldHeads, FieldHrs, FieldArea, m_CompostPoro, m_LitterAmount, m_CompostPH;
	int m_CompostCover, m_CompostRemoveDate[10][10];
	float m_LagoonCapacity, m_LagoonSurfaceArea, m_LagoonDepth, m_ToField[8][10], m_ToMarket[8][10], m_Remain[8][10], m_LagoonFieldAplDepth[10];
	int m_LagoonCover, m_LagoonRain, m_LagoonDrainDate[8][10], m_LagoonFieldAplMethod[10];//, m_LagoonDrainTimes[10];
	float m_DigesterCH4;
	int m_DigesterTemp, m_Flash[10], m_ManureRemoveTimes[10];
	float m_FlushWater[10], LiquidFraction[10];
	float m_UC[10], m_UL[10], m_UD[10], m_UR[10], m_FC[10], m_FL[10], m_FD[10], m_ManureRemoveFrequency[10]; 
	float m_FR[10], m_UF[10], m_FF[10];
	int mm_StorageDays, mm_LagoonDays, mm_SlurryDays, mm_SlurryCover, mm_DigesterDays, mm_WasteSeparate;
	float mm_StorageCN, mm_StorageFraction, mm_LagoonCapacity;
	float mm_LagoonSurfaceArea, mm_LagoonFraction, mm_SlurrySurfaceArea, mm_SlurryFraction;
	float mm_DigesterCapacity, mm_DigesterCH4, mm_DigesterFraction;

	int EmpiricalModel[5], FeedAdditive[5];
	float FeedAdditiveRate[5];
		
	float yr_intake_C, yr_intake_N, yr_intake_P; 
	float yr_waste_water, yr_milk_water;
	float yr_milk_C, yr_milk_N, yr_meat_C, yr_meat_N, yr_milk_P, yr_meat_P;
	float yr_urine_C, yr_urine_N, yr_dung_C, yr_dung_N, yr_urine_P, yr_dung_P, ManureFieldArea;

	//Enteric gases
	float day_enteric_ch4[5], day_enteric_n2o[5], day_enteric_nh3[5];
	float DAY_enteric_ch4[4], DAY_enteric_n2o[4], DAY_enteric_nh3[4]; 
	float yr_enteric_ch4, yr_enteric_n2o, yr_enteric_nh3;

	//Housing
	float HouseManure, HouseManureN;
	float HouseLiquid_nh4, HouseLiquid_no3, HouseLiquid_humad, HouseLiquid_vll, HouseLiquid_ll;
	float HouseLiquid_rl, HouseLiquid_mbm1, HouseLiquid_mbm2, HouseLiquid_humus; 
	float day_house_ch4, day_house_nh3, day_house_no, day_house_n2o, day_house_n2; 
	float day_gutter_n2o, day_gutter_n2, day_gutter_no, day_gutter_nh3, day_gutter_ch4;
	float day_HouseOutputSolidC, day_HouseOutputSolidN, day_HouseOutputMoisture;
	float yr_house_nh3, yr_house_ch4, yr_house_n2o, yr_house_co2;
	float yr_house_n2, yr_compost_n2, yr_house_no, day_house_evap, yr_house_evap;
	float House_to_compost_C, House_to_compost_N, House_to_lagoon_C;
	float House_to_lagoon_N, House_to_digester_C, House_to_digester_N;
	float House_to_field_C, House_to_field_N, House_to_field_P, House_to_field_H2O;
	float House_to_compost_P, House_to_lagoon_P, House_to_digester_P;
	float House_to_compost_H2O, House_to_lagoon_H2O, House_to_digester_H2O;
	float House_floor_removedN, House_floor_removedC, House_floor_removedP, House_floor_removedH2O;
	//float House_gutter_removedN, House_gutter_removedC;
	//float House_floor_removed_H2O, House_gutter_removed_H2O, House_floor_removed_P, House_gutter_removed_P;
	float yr_floor_leach_water, yr_floor_leach_urea, yr_floor_leach_NH4, yr_floor_leach_NO3, yr_floor_leach_doc;
	float day_floor_leach_water, day_floor_leach_urea, day_floor_leach_NH4, day_floor_leach_NO3, day_floor_leach_doc;

	float day_intake_C, day_intake_N, day_intake_P, day_milk_N, day_milk_C, day_meat_N, day_meat_C;
	float day_milk_P, day_meat_P; 
	float day_milk_product, yr_milk_product, day_urine_water, day_dung_water, yr_urine_water, yr_dung_water;//, yr_animal_CO2;
	
	float yr_House_to_compost_C, yr_House_to_lagoon_C, yr_House_to_digester_C; 	
	float yr_House_to_compost_N, yr_House_to_lagoon_N, yr_House_to_digester_N; 
	float yr_House_to_compost_P, yr_House_to_lagoon_P, yr_House_to_digester_P; 
	float yr_House_to_compost_H2O, yr_House_to_lagoon_H2O, yr_House_to_digester_H2O; 
	float yr_House_to_field_C, yr_House_to_field_N, yr_House_to_field_P, yr_House_to_field_H2O;

	float yr_farm_to_compost_C, yr_farm_to_lagoon_C, yr_farm_to_digester_C; 
	float yr_farm_to_compost_N, yr_farm_to_lagoon_N, yr_farm_to_digester_N; 
	float yr_farm_to_compost_P, yr_farm_to_lagoon_P, yr_farm_to_digester_P; 
	float yr_farm_to_compost_H2O, yr_farm_to_lagoon_H2O, yr_farm_to_digester_H2O; 
	float yr_farm_to_field_C, yr_farm_to_field_N, yr_farm_to_field_P, yr_farm_to_field_H2O; 

	float day_house_co2,day_gutter_co2, yr_bed_C, yr_bed_N, day_bed_C, day_bed_N;
	//double yr_House_to_lagoon_H2O;
	float enteric_ch4, enteric_n2o;
	float indoor_T, indoor_RH, head_enteric_n2o;//, indoor_airflow;
	int BarnDays;

	//float day_to_market_MC, day_to_market_MIN,day_to_market_MON;
	//float yr_to_market_MC, yr_to_market_MIN,yr_to_market_MON;

	//Outdoor pen	
	int IniMonth, IniDay, EndMonth, EndDay;
	//float day_pen_ch4, day_pen_nh3, day_pen_n2o, day_pen_no, day_pen_n2,day_pen_co2;
	//float day_PenLeachWater, day_PenEvapWater, day_pen_no3Leach, day_pen_docLeach;
	//float Pen_to_compost_C, Pen_to_compost_N, Pen_to_lagoon_C, Pen_to_lagoon_N, Pen_to_digester_C, Pen_to_digester_N;
	//float Pen_to_compost_P, Pen_to_lagoon_P, Pen_to_digester_P;
	//float Pen_to_lagoon_H2O, Pen_to_compost_H2O, Pen_to_digester_H2O;
	//float yr_pen_evap, yr_Pen_to_compost_C,	yr_Pen_to_lagoon_C,	yr_Pen_to_digester_C,yr_Pen_to_compost_N;
	//float yr_Pen_to_compost_P,	yr_Pen_to_lagoon_P,	yr_Pen_to_digester_P;
	//float yr_Pen_to_lagoon_N,yr_Pen_to_digester_N,yr_Pen_to_compost_H2O,yr_Pen_to_lagoon_H2O,yr_Pen_to_digester_H2O;
	//float yr_pen_nh3,yr_pen_n2o,yr_pen_ch4,yr_pen_no,yr_pen_n2,yr_pen_co2;

	//Grazing field
	float FieldInMN;
	//float yr_field_nh3, yr_field_ch4, yr_field_n2o;

	//Composting
	//float day_CompostCO2;
	float day_Compost_nh3, day_compost_no, day_compost_n2o, day_compost_n2,day_compost_co2;
	float day_compost_ch4, day_CompostOutputMoisture, yr_House_to_Compost_H2O;
	float CompostInN, CompostOutN, yr_compost_EV, day_compost_EV, day_compost_InRain, yr_compost_InRain;
	float yr_compost_nh3, yr_compost_ch4, yr_compost_n2o, yr_compost_co2, yr_compost_no, yr_compost_leach_H2O;
	float yr_compost_add_C, yr_compost_add_N; 

	//Lagoon
	float day_lagoon_ch4, day_lagoon_nh3, day_lagoon_n2o, day_lagoon_no, day_lagoon_n2,day_lagoon_co2;
	float day_lagoon_EV, yr_lagoon_EV;
	float LagoonOutION, LagoonInDOC, LagoonInWater, LagoonInUrea;
	float ToLagoon_rcvl,ToLagoon_rcl,ToLagoon_rcr,ToLagoon_CRB1,ToLagoon_CRB2,ToLagoon_hdc,ToLagoon_dphum;
	float HouseToLagoonSOC,HouseToLagoonSON;
	float yr_lagoon_nh3, yr_lagoon_n2o, yr_lagoon_ch4, yr_lagoon_n2, yr_lagoon_no, yr_lagoon_co2, yr_lagoon_InRain;
	float yr_Lagoon_to_field_N, yr_Lagoon_to_field_P, yr_Lagoon_to_field_C, yr_House_to_Lagoon_H2O;
	//float yr_House_to_field_N, yr_House_to_field_P, yr_House_to_field_C,  yr_House_to_field_H2O;
	double yr_Lagoon_to_field_H2O; 
	float LagoonCrustC;

	//Digester
	float day_digester_nh3, day_digester_no, day_digester_EV, Digester_to_field_H2O;
	float yr_digester_ch4, yr_digester_nh3, yr_digester_n2o, day_digester_n2o;
	float yr_digester_n2, yr_digester_no, day_digester_n2, yr_digester_EV;
	float yr_digester_co2;
	float yr_digester_to_field_C, yr_digester_to_field_N, yr_digester_to_field_H2O, yr_digester_to_field_P;
	float yr_digester_to_lagoon_C, yr_digester_to_lagoon_N, yr_digester_to_lagoon_P, yr_digester_to_lagoon_H2O;
	float yr_lagoon_to_digester_C, yr_lagoon_to_digester_N, yr_lagoon_to_digester_P, yr_lagoon_to_digester_H2O;
	float Digester_to_field_N, Digester_to_field_C, Digester_to_field_P;
	float Digester_to_lagoon_N, Digester_to_lagoon_C, Digester_to_lagoon_P, Digester_to_lagoon_H2O;
	float Digester_to_market_N, Digester_to_market_C, Digester_to_market_P, Digester_to_market_H2O;
	float yr_digester_to_market_C, yr_digester_to_market_N, yr_digester_to_market_P, yr_digester_to_market_H2O;
	float Lagoon_to_digester_N, Lagoon_to_digester_C, Lagoon_to_digester_P, Lagoon_to_digester_H2O;
	
	float rcvl_HO,rcl_HO,rcr_HO,CRB1_HO,CRB2_HO,day_hdc_HO,dphum_HO,soc_HO,ocini_HO,nh4_HO,no3_HO;
	float no2_HO,no_HO,n2o_HO,n2_HO,nh3_HO,co2_HO,urea_HO,doc_HO,son_HO;
	float rcvl_CO,rcl_CO,rcr_CO,CRB1_CO,CRB2_CO,day_hdc_CO,dphum_CO,soc_CO,ocini_CO,nh4_CO,no3_CO;
	float no2_CO,no_CO,n2o_CO,n2_CO,nh3_CO,co2_CO,urea_CO,doc_CO,sph_CO,son_CO;
	float water_LO;
	float rcvl_LO,rcl_LO,rcr_LO,CRB1_LO,CRB2_LO,day_hdc_LO,dphum_LO,soc_LO,ocini_LO,nh4_LO,no3_LO;
	float no2_LO,no_LO,n2o_LO,n2_LO,nh3_LO,co2_LO,urea_LO,doc_LO,sph_LO,son_LO;	  
	
	float day_manure_an_no, day_manure_an_n2o, day_manure_n2, day_UrineN, mm_TotalHeads[4];
	float day_compost_leach_H2O, ManureCapacity; 
	float yr_enteric_co2, yr_ManureN_toField;
	float LI_NH3, AI_NH3, LagoonT[21], day_digester_CH4, day_digester_CO2, animal_co2, bottomT;
	int compost_days, lagoon_days, digester_days;
	float manure_irri, ttc, ttp, yr_flush_H2O;
	float Lagoon_to_field_C, Lagoon_to_field_N, Lagoon_to_field_H2O, Lagoon_to_field_P, LagoonFieldAplDepth;
	int LagoonFieldAplMethod;
	float Compost_to_field_C, Compost_to_field_N, Compost_to_field_H2O, Compost_to_field_P;
	float yr_Compost_to_field_C, yr_Compost_to_field_N, yr_Compost_to_field_H2O, yr_Compost_to_field_P;
	float yr_LOS_ch4, yr_LOS_n2o, yr_LOS_nh3, yr_LOS_LeachN;
	float day_LOS_ch4, day_LOS_n2o, day_LOS_nh3, day_LOS_LeachN;
	float day_runoff_MC[10], day_runoff_MIN[10], day_runoff_MON[10], yr_runoff_MC[10], yr_runoff_MIN[10], yr_runoff_MON[10];
	float day_market_MC[10], day_market_MIN[10], day_market_MON[10], yr_market_MC[10], yr_market_MIN[10], yr_market_MON[10];
	float day_runoff_MOP[10], day_market_MOP[10], yr_runoff_MOP[10], yr_market_MOP[10];
	float day_lagoon_MC, day_lagoon_MIN, day_lagoon_MON, day_lagoon_WATER, yr_lagoon_MC, day_lagoon_MOP, yr_lagoon_MIN, yr_lagoon_MON, yr_lagoon_WATER;
	float ToField[25], day_compost_runoff_WATER, yr_compost_runoff_WATER, day_feedlot_runoff_WATER, yr_feedlot_runoff_WATER;
	float yr_carryover_lagoon_C, yr_carryover_lagoon_N, yr_carryover_lagoon_H2O, yr_carryover_lagoon_P;
	float yr_carryover_compost_C, yr_carryover_compost_N, yr_carryover_compost_H2O, yr_carryover_compost_P;
	float yr_carryover_digester_C, yr_carryover_digester_N, yr_carryover_digester_H2O, yr_carryover_digester_P;
		
	void ManureTreatmentFacility(int q, int scale, int *CompostCover, float *LagoonCapacity,int year);

	void ManureFeedlot(
		int *FN, int *GN,
		int jday, FILE* fLV1, FILE* fLV4, FILE* fLV3, float rcnrr, float rcnh, float rcnb, float *urea, float *doc, float *rcvl, 
		float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, float DayPET, 
		float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, float rcnrvl, float rcnrl, int WTL, 
		float day_WT, float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, int q, float rcnm, float *son, float *SIN, 
		float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, 
		float *w_no2, float *w_nh3, float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, 
		int tilq, FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate, float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float* mmm, 
		float *ocini, float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim,  
		float DClitter, float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, float day_runoff, float *day_runoff_N, 
		float *day_clay_N, float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, 
		float *ds_doc, int *crop, float *yr_fixn, float till_fact, float *sts, float rainfall, float *O2_old, float *O2, 
		float *vvv, float *ave_anvf, int year, double water[25][250], float total_ice, float *day_rco2, int flo_num,
		float *Eh, float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d,
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, float *assim2,
		float *fldcap, float by_passf, int NIDay1, int NIDay2, float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *wiltpt, float *day_addmc, float *yr_addmc, float *yr_addmn, 
		float *day_inManureN, float *day_frostDOC, float *yr_frostDOC, float *winertC, 
		float *inert_C, int fert_flag, float *root_doc, float precipitation, 
		int manuFlag, int irri_flag, float *FreezeDOC, float *day_O2, float *day_farm_to_field_N, float *day_farm_to_field_C, 
		float *day_farm_to_field_H2O, float RFM, float *SoilDepth, int scale, 
		float *C_soil, float *sop, float *OrgP, float *LabP, float *ComP, float *AdsP, 
		float *day_farm_to_field_P, int fln, float *ch4_doc_pool, FILE* fFeedOut,
		float humidity, float min_temp, float max_temp, float PAR, float *F_methanogen, float *Tttoo, float *H2,
		float *day_ch4_CO2, float *day_ch4_1, float *day_ch4_2, int Option, float *SMC, float day_leach_water,
		float* pen_soil_wfps, float *SO4, float sslope, float day_root_resp, FILE* HSM, int fertigate_flag,
		float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, float ha, int livestock,
		float *day_nitrification, float *day_denitrification, float *day_H2_prod,float rno3, float day_inRainN, float denitMulti,float nitMulti, float N2N2OFactor,
		float* manco2, float* manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2,  float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol, int manureCounter,float *day_nitrify_n2ol, float *day_denitrify_n2ol);
	
	void ManureTreatmentBGC(
		int *FN, int *GN,
		int jday, float rcnrr, float rcnh, float rcnb, float *urea, float *doc, float *rcvl, 
		float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, float DayPET, 
		float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, float rcnrvl, float rcnrl, int WTL, 
		float day_WT, float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, int q, float rcnm, float *son, float *SIN, 
		float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, 
		float *w_no2, float *w_nh3, float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, 
		int tilq, FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate, float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float* mmm, 
		float *ocini, float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim,  
		float DClitter, float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, float day_runoff, float *day_runoff_N, 
		float *day_clay_N, float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, 
		float *ds_doc, int *crop, float *yr_fixn, float till_fact, float *sts, float rainfall, float *O2_old, float *O2, 
		float *vvv, float *ave_anvf, int year, double water[25][250], float total_ice, float *day_rco2, int flo_num,
		float *Eh, float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, float *ttoo,
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, float *assim2,
		float *fldcap, float by_passf, int NIDay1, int NIDay2, float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *wiltpt, float *day_addmc, float *yr_addmc, float *yr_addmn, 
		float *day_inManureN, float *day_frostDOC, float *yr_frostDOC, float *winertC, 
		float *inert_C, int fert_flag, float *root_doc, float precipitation, 
		int manuFlag, int irri_flag, float *FreezeDOC, float *day_O2, FILE *ftf, float *day_farm_to_field_N, float *day_farm_to_field_C, 
		float *day_farm_to_field_H2O, float RFM, float *SoilDepth, int scale, 
		float *C_soil, float *sop, float *OrgP, float *LabP, float *ComP, float *AdsP, 
		float *day_farm_to_field_P, float LateralInflux, int drain_flag, float *ToField, float day_leach_water,
		int CompostCover, float LagoonCapacity, FILE* HSM, int fertigate_flag,
		float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, float ha, int livestock,
		float *day_nitrification, float *day_denitrification, int m_Temp, float* manco2, float *manurePool, float manurePoolCN,float rno3, float day_inRainN, float denitMulti,float nitMulti, float N2N2OFactor, 
		int manureHour,int manureCounter, int UreaHydroInhibDays, int UIDay1, int UIDay2,  float newmanuPH, float combinedpHDeep, float NH3Vol,
		float max_temp, float min_temp, int annualMinTempDay, float *lagoon_snowpack, float *lagoon_SnowMelt, float lagoon_snowfall, float lagoonTempPartition[101][2], float yr_avetj, float maxAnnualTemp, float averageAnnualTemp, float lagoon_ice[21], int& oldLayerDepth, float DayPETRN, float latitude,float humidity,float *day_nitrify_n2ol, float *day_denitrify_n2ol);//added 3 new parameters to the outputs.
	
	void HouseManureProduct(int FN);
#ifdef VOC
	void VOCs(char *F_CLIMD, int year, float *AnimalHeads, float *FeedRates);
#endif
	void HouseManureOccumulation(int FN, int GN, int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float *urea, float *doc, float *rcvl, 
		   float *rcl, float *rcr, float *crhl, float *crhr, float *CRB1, float *CRB2, float *dphum, 
		   double water[25][250],
		   float rcnm, float *soc, float *son, float *SIN, float *nh4, float *no3, float *no2, float *no, float *n2o,
		   float *n2, float *nh3, float *co2, float *sop, float *OrgP, float *LabP, float *ComP,
		   float precipitation);
	void HouseManure_BGC(int FN, int GN, 
		int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float *urea, float *doc,
		float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, 
		float DayPET, float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, int WTL, float day_WT, 
		float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, float rcnm, float *son, float *SIN, float *no3, float *no2, 
		float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, float *w_no2, float *w_nh3, 
		float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, int tilq, 
		FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, 
		float WaterLeakRate,
		float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, float *ocini,
		float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim, float DClitter,
		float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, 
		float day_runoff, float *day_runoff_N, float *day_clay_N, 
		float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, float *ds_doc, int *crop, float *yr_fixn,
		float till_fact, float *sts, float rainfall, float *O2_old, float *O2, float *vvv, float *ave_anvf,
		int year, double water[25][250], float total_ice, float *day_rco2, int flo_num, float *Eh,
		float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, 
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, 
		float *assim2, float *fldcap, float by_passf, int NIDay1, int NIDay2,
		float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *wiltpt, float *day_frostDOC, float *yr_frostDOC,
		float *winertC, float *inert_C, int fert_flag, float *root_doc, 
		float precipitation, float manuFlag, int irri_flag, float *FreezeDOC, float mm_VentRate,
		float *day_O2, float RFM, float *SoilDepth, float *C_soil, float *sop, float *OrgP,
		float *LabP, float *ComP, float *AdsP, float *ch4_doc_pool, float humidity, float min_temp, float max_temp, 
		float PAR, float *F_methanogen, float *Tttoo, float *H2, float *day_ch4_CO2, float *day_ch4_1, 
		float *day_ch4_2, float day_leach_water, float* pen_soil_wfps, float *SO4, float sslope, float day_root_resp, FILE* HSM,
		int fertigate_flag, float hrPE0, float *dby_flux, int DroughtID, int YieldToday, int drc, int scale, 
		float ha, int livestock, float *day_nitrification, float *day_denitrification, float *day_H2_prod,float rno3, float day_inRainN, float denitMulti,float nitMulti, float N2N2OFactor, 
		float* manco2, float* manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2,  float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol, int manureCounter, float *day_nitrify_n2ol,float *day_denitrify_n2ol);//, float *manco2, float *manurePool, float manurePoolCN

	void FeedlotManureRemoval0(int FN, int GN, int q, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
								 float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
								 float *CRB1, float *CRB2, float *crhl, float *crhr, float *dphum, float *doc, 
								 float *nh4, float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, 
								 float *urea, int jday, float *co2, float *sph, double water[25][250],
								 float *day_wfps, float *temp, float air_temp, int scale, 
								 float *sop, float *OrgP, float *LabP, float *ComP, FILE* fFeedOut);

	void compost_BGC(int FN, int GN,
		int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float* urea, float* doc,
		float* rcvl, float* rcl, float* rcr, float* CRB1, float* CRB2, float* dphum, float* temp, float air_temp,
		float DayPET, float wind_speed, float* day_wfps, float* soc, float* sph, int* flood_flag, int WTL, float day_WT,
		float* soil_ph, float* nh4, float* ch4_prod, float* ch4_day_oxid, float* plant_day_ch4, float rcnm, float* son, float* SIN, float* no3, float* no2,
		float* no, float* n2o, float* n2, float* nh3, float* ch4, float TTT, float* newh, float* w_no2, float* w_nh3,
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
		float* doc_d, float* nh4_d, float* no3_d, float* no2_d, float* no_d, float* n2o_d, float* Tttoo,
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl,
		float* assim2, float* fldcap, float by_passf, int NIDay1, int NIDay2,
		float* day_soil_nitrify, float* day_nitrify_NO, float* day_nitrify_N2O, float* day_soil_an_no,
		float* day_soil_an_n2o, float* day_soil_n2, float* Root_Wt, float* day_soil_denitrification,
		float* R_Wt, float* vascularity, float* wiltpt, float* day_frostDOC, float* yr_frostDOC,
		float* winertC, float* inert_C, int fert_flag, float* root_doc,
		float precipitation, float manuFlag, int irri_flag, float* FreezeDOC, float* day_O2, float RFM,
		float* SoilDepth, float* sop, float* OrgP, float* LabP, float* ComP, float* AdsP,
		float LateralInflux, int drain_flag, float day_leach_water, int CompostCover, FILE* HSM, int fertigate_flag,
		float hrPE0, float* dby_flux, int DroughtID, int YieldToday, int drc, int scale, float ha, int livestock,
		float* day_nitrification, float* day_denitrification, float* manco2, float* manurePool, float manurePoolCN, float rno3, float day_inRainN, float denitMulti, float nitMulti, float N2N2OFactor,
		int manureHour, int manureCounter, int UreaHydroInhibDays, int UIDay1, int UIDay2, float newmanuPH, float combinedpHDeep, float NH3Vol, float *day_nitrify_n2ol, float *day_denitrify_n2ol);

	void compost_CH4(int FC, float *day_wfps, float *doc, int CompostCover);
	void StorageManureRemoval(int FN, int GN, int q, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
								 float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
								 float *CRB1, float *CRB2, float *crhl, float *crhr, float *dphum, float *doc, 
								 float *nh4, float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, 
								 float *urea, int jday, float *co2, float *sph, double water[25][250],
								 float *day_wfps, float *temp, float air_temp,
								 float *day_addmc, float *yr_addmc, float *yr_addmn, float *day_inManureN,
								 float *day_farm_to_field_N, float *day_farm_to_field_C, 
								 float *day_farm_to_field_H2O, int scale, float *sop, float *OrgP, 
								 float *LabP, float *ComP, float *day_farm_to_field_P, int j, float *ToField);

	void lagoon_BGC(int FN, int GN, 
		int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float *urea, float *doc,
		float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, 
		float DayPET, float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, int WTL, float day_WT, 
		float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, float rcnm, float *son, float *SIN, float *no3, float *no2, 
		float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, float *w_no2, float *w_nh3, 
		float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no,
		float *DayFlux, int tilq, 
		FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, float WaterLeakRate,
		float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, float *ocini,
		float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim, float DClitter,
		float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, 
		float day_runoff, float *day_runoff_N, float *day_clay_N, 
		float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, float *ds_doc, int *crop, float *yr_fixn,
		float till_fact, float *sts, float rainfall, float *O2_old, float *O2, float *vvv, float *ave_anvf,
		int year, double water[25][250], float total_ice, float *day_rco2, int flo_num, float *Eh,
		float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, float *ttoo, 
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, 
		float *assim2, float *fldcap, float by_passf, int NIDay1, int NIDay2,
		float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *winertC, float *inert_C, int fert_flag, 
		float *root_doc, float *day_O2, float RFM, float *SoilDepth, 
		float *wiltpt, float *day_frostDOC, float *yr_frostDOC, float precipitation, int manuFlag, int irri_flag, 
		float *FreezeDOC, float *sop, float *OrgP, float *LabP, float *ComP, float *AdsP,
		float LateralInflux, int drain_flag, float day_leach_water, int facility, float m_capacity,
		float disturbance, float* manco2, float* manurePool, float manurePoolCN, int UreaHydroInhibDays, int UIDay1, int UIDay2,
		 float newmanuPH, float combinedpHDeep, int manureHour, float NH3Vol, int manureCounter,
		float max_temp, float maxAnnualTemp, float min_temp, float yr_avetj, int oldLayerDepth, float lagoonTempPartition[101][2], float *lagoon_snowpack,  float *lagoon_SnowMelt, float lagoon_snowfall, float DayPETRN, float lagoon_ice[21], float latitude, float humidity);
	
	void lagoon_snowfall_snowpack(float air_temp, float rainfall, float& lagoon_snowpack, float& lagoon_SnowMelt, float& lagoon_snowfall, int year,float lagoon_ice[21]);
	void lagoon_climate(int GN, float *temp, float air_temp, float *day_wfps, float *Eh, float wind_speed,
								  float DayPET, double water[25][250], int jday, float rainfall, int facility, float max_temp, float maxAnnualTemp, float min_temp, float yr_avetj, int year, float* soc, int oldLayerDepth, float lagoonTempPartition[101][2], float lagoon_snowpack, float lagoon_SnowMelt, float lagoon_snowfall, float DayPETRN, float lagoon_ice[21], float latitude, float humidity);
	void lagoon_nh3(int GN, float *temp, float *nh3, double water[25][250], float *nh4, float *sph,
		float LagoonCapacity, float disturbance, float *urea, int jday);
	void lagoon_denitrification(int GN, float *temp, float *nh4, float *no3, float *soc, float *doc,
		float *no2,float *no,float *n2o,float *n2, float *dphum, float rcnm, float disturbance);
	void lagoon_ch4(int GN, float *temp, float *dphum, float *doc, float disturbance, int jday, float *rcr,
		float *rcvl, float *rcl, float *CRB1, float *CRB2, float *crhl, float *crhr,
		float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float *nh4);

	void digester_BGC(int FN, int GN, 
		int q, int jday, float rcnrvl, float rcnrl, float rcnrr, float rcnh, float rcnb, float *urea, float *doc,
		float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2, float *dphum, float *temp, float air_temp, 
		float DayPET, float wind_speed, float *day_wfps, float *soc, float *sph, int *flood_flag, int WTL, float day_WT, 
		float *soil_ph, float *nh4, float *ch4_prod, float *ch4_day_oxid, float *plant_day_ch4, float rcnm, float *son, float *SIN, float *no3, float *no2, 
		float *no, float *n2o, float *n2, float *nh3, float *ch4, float TTT, float *newh, float *w_no2, float *w_nh3, 
		float *w_no3, float *w_nh4, float *wurea, float day_clayn, float *wpool_no, 
		float *DayFlux, int tilq, 
		FILE *fCB, FILE *fNB, float *w_n2o, float *w_n2, int *seed, float *day_ch4, float *anvf, float WaterLeakRate,
		float *co2, float *clay, int LandUse, int FloDays, float *crhl, float *crhr, float *mmm, float *ocini,
		float *h, float *day_C_mine, float *day_N_mine, float *day_N_assim, float DClitter,
		float *litco22, float *litco23, int *st, float DChumads, float EFFAC, float DChumus,
		int wetland_flag, float *ice, float *day_soil_nh3, float *lai, float *PlantTakeN, float *maxmn,
		float leaf_water, float cropht, float base_nh3, float *day_N_demand, float *day_nup, float *day_fixN, 
		float *day_DWater,
		float *day_plant_nh3, float *yr_NH3_deposit, float *plantn, float *clay_nh4, float base_clay_N, float max_clay_N,
		float *wrcvl, float *wrcl, float *wrcr, float *wcrb, float *wcrhl, float *wcrhr, float *whumus, float *wtcavai,
		float *day_ice_N, float *day_ice_doc, float *day_ice_n2o, float *day_ice_n2, float *IniSOC, float *IniSON, 
		float *EndSON, 
		float day_runoff, float *day_runoff_N, float *day_clay_N, 
		float *dsno3, float *dsnh4, float *dsnh3, float *day_dsurea, float *ds_doc, int *crop, float *yr_fixn,
		float till_fact, float *sts, float rainfall, float *O2_old, float *O2, float *vvv, float *ave_anvf,
		int year, double water[25][250], float total_ice, float *day_rco2, int flo_num, float *Eh,
		float *doc_w, float *nh4_w, float *no3_w, float *no2_w, float *no_w, float *n2o_w, float *n2_w,
		float *doc_d, float *nh4_d, float *no3_d, float *no2_d, float *no_d, float *n2o_d, float *ttoo, 
		float ManureAddCN, int ManureDays, float MicrobioIndex, float mRBO, float mFD, int WaterControl, 
		float *assim2, float *fldcap, float by_passf, int NIDay1, int NIDay2,
		float *day_soil_nitrify, float *day_nitrify_NO, float *day_nitrify_N2O, float *day_soil_an_no,
		float *day_soil_an_n2o, float *day_soil_n2, float *Root_Wt, float *day_soil_denitrification,
		float *R_Wt, float *vascularity, float *sop, int m_Temp);
	void digester_decomposition(int GN, float *temp, float *rcvl, float *rcl, float *rcr, float *CRB1, float *CRB2,
										 float *crhl, float *crhr, float *dphum, float rcnrvl, float rcnrl, float rcnrr,
										 float rcnb, float rcnh, float rcnm, float *urea, float *nh3, float *nh4,
										 float *no3, float *no2, float *no, float *n2o, float *n2, float *doc, float *sph);

	void EntericGasProduction(int FN, float air_temp);

	float Total_SOCSON(int FC, int FCC, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
								 float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
								 float *CRB1, float *CRB2, float *crhl, float *crhr, float *dphum, float *doc, 
								 float *nh4, float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, 
								 float *urea, float *co2, float *sop, float *OrgP, float *LabP, float *ComP);

	void FM_frame(MODEL_LINK_INFO* pLinkInfo, char *countryName, char *stateName, char *site, int MODE, int year);
	void FM_paint(MODEL_LINK_INFO* pLinkInfo, int cwc, char *cropName, int MODE, int c_ViewMode, char *cropping_system,
		          int jday, float air_temp, float rainfall, float *soc, float *day_wfps, int q, float *nh4, 
				  float *no3, float *urea, double water[25][250], float *temp, float day_soil_nh3, float *day_plant_nh3,
				  float day_vol_nh3, float day_soil_an_n2o, float day_soil_n2);

	void write_out_dayCompost(FILE *fcompost, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float *sop, int m_unit);
	void write_out_dayLagoon(FILE *flagoon, int jday, float lagoon_temp, float *nh4, float *no3, float *nh3, float *son, 
		float *urea, char *site, int year, int q, float *soc, double water[25][250], float *no2, float *no, float *n2o, 
		float *n2, float *sop, int m_unit, float *doc, float *LagoonT, float air_temp, float *lagoon_snowpack, float lagoon_ice[21]);
	void write_out_dayTreatmentGas(FILE *ffarmgas, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float day_soil_nh3, float day_vol_nh3, 
				float day_soil_an_n2o, float *sop, int m_unit);
	void write_out_dayFeedlotGas(FILE *ffarmgas, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float day_soil_nh3, float day_vol_nh3, 
				float day_soil_an_n2o, float *sop, int m_unit);
	//void write_out_dayClim(FILE *fclim, int jday, char*site, int year, float air_temp, float precipitation,
	//	float wind_speed, float radiation, float humidity);
	void write_dayManureProduction(FILE *fhouse, int FN, int GN, int jday, char*site, int year, float *soc, float *doc,
			float *son, float *urea, float *nh4, float *no3, float *temp, float *day_wfps, float *sph, 
			double water[25][250], int q, float *sop, int m_unit, float *Eh, float pen_soil_wfps);

	void write_out_dayDigester(FILE *fdigester, int jday, char *site, int year, int q, 
				float *day_wfps,float *sph,float *soc,float *son,float *urea,float *nh4,float *no3,float *doc,
				float *temp, double water[25][250], float *nh3, float *sop, int m_unit,
				float *no2, float *no, float *n2o, float ttn);
	void read_in_ManureInputs(void);
	void write_out_dayFarmCN(FILE *ffarmC, int jday, char *site, int year, int m_unit);
	void write_out_dayFarmManureRemove(FILE *ffarmMR, int jday, char *site, int year, int m_unit);
	//void write_out_dayFarmN(FILE *ffarmN, int jday, char *site, int year);
	void ManureRunoff(int FN, int GN, float *RFL, float rcnrvl, float rcnrl,float rcnrr,
								   float rcnb,float rcnh,float rcnm,
								   float *rcvl,float *rcl,float *rcr,float *CRB1,float *CRB2,
								   float *crhl,float *crhr,float *dphum,
								   float *nh4,float *no3,float *no2,
								   float *no,float *n2o,float *n2,float *nh3,float *urea,float *co2,
								   float *doc,double water[25][250], float *OrgP,float *LabP,float *ComP);
	void ManureMarket(int FN, int GN, float *RFL, float rcnrvl, float rcnrl,float rcnrr,
								   float rcnb,float rcnh,float rcnm,
								   float *rcvl,float *rcl,float *rcr,float *CRB1,float *CRB2,
								   float *crhl,float *crhr,float *dphum,
								   float *nh4,float *no3,float *no2,
								   float *no,float *n2o,float *n2,float *nh3,float *urea,float *co2,
								   float *doc,double water[25][250], float *OrgP,float *LabP,float *ComP);
	void ManureLagoon(int GN, float *RFL, float rcnrvl, float rcnrl,float rcnrr,
								   float rcnb,float rcnh,float rcnm,
								   float *rcvl,float *rcl,float *rcr,float *CRB1,float *CRB2,
								   float *crhl,float *crhr,float *dphum,
								   float *nh4,float *no3,float *no2,
								   float *no,float *n2o,float *n2,float *nh3,float *urea,float *co2,
								   float *doc,double water[25][250], float *OrgP,float *LabP,float *ComP);

	
};

#endif

int Model_linux(  int scale, char* cropping_system, int S_SoilYear, int S_ThisYear, 
						int S_SimuYears, char* DatabaseName, char* r_Province, char* ScenarioName, 
						float ha, int ProvinceOrder, int S_county, int CountyIDX, int landuse,
						int StartYear, int ifdaily, int MonteCarlo, int ZXH, int Batch, 
						int GlobeData, char* DirRoot, int sample, int RRRRR, int IrriType, 
						char* country_ID, int livestock, int Monitor, int DroughtID, 
						char f_region[6][150], char* DroughtYield, int FFN, char *BatchName);

