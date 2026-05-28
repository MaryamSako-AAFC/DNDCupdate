#include "stdafx.h"
#include "RunPaths.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;
#endif

float sdx,sdK1=0.14,sdK2=1.6;
float co2_crop;

void class_model::initiation(int facility)
{
	int i;
	diTemp=0.0;
	OldTHr=0.0;
	manureHour=0;
	newmanuPH=0.0;
	oldWP = -1.0;
	oldFC = -1.0;
//	spinup=0;//flag for running with spinup
//	cropSpin=0;//flag for running with spinup every other year
	rootFracIncrease=0.0;
	manurePoolCN = 10.0;
	accumNewPlantN = 0.0;
	soilWaterStress=0.0;
	RFM= 0.0;
    wrcvl = 0.0;
    wrcl = 0.0;
	flower=0.0;
	pod=0.0;
	seedFill=0.0;
	writeOutPlant = 0;//testing a writeoutSoilFile
	NIEfficiency = 0.0;//might not want to reset this.
	slowReleaseCounter = 1;
	consec5Days = 1;//counter for Degree Days accumulator for perrenial growth after March 1st. See Crop TDD.
	flagHeader=1;
	if(year>1)
	{
		flagHeader=0;
	}
    wrcr = 0.0;
	snowmeltMulti=1.0;
    wcrb = 0.0;
	cumWaterStress = 0;
	cumWaterStress1 = 0;
	cropT = 0;
	upFertCrop = 1;
	cumFlowerPrecip = 0.0;//summate Precip during Flowring Stage
	soyFlowerWStress = 1.0;//Water Stress factor for Flowering Soybean;
	SoilSpinUpCounter=0;
	DynGermDays[0]=0;
	DynGermDays[1]=0;
	totalManureC = 0.0;
	manureCK1 = 0.0;
	totalManureN = 0.0;
	TotalFreezeDOC = 0.0;
	totalSens1=0;
	totalSens2=0;
	totalSens3=0;
	GrassProductivityFactor = 1.0;
    wcrhl = 0.0;
	wcrhr = 0.0;
    whumus = 0.0;
	winertC = 0.0;
    wnew_hum = 0.0;
    day_co2 = 0.0;
	HarvSIN=0.0;
	cropGrowDays1 = 0;
	cropGrowDays2 = 0;
	cropGrowDays3 = 0;
	GermReport=0;
	header=1;
	yrPPT=0.0;
	//winterKill=1.0;
	winterCrown=0.0;
	winterCrownDays=0;
	winterKillRed=1.0;
	springCrown=0.0;
	springCrownDays=0;
	farmAgentModel=0;
	controlledDrainageDepth=1000;
	WTDrain=0;
	NH3Vol=1.0;
	//runoff_pool = 0.0;
	wCH4_C = 0.0;
	counterPHLEFT=0;    
    day_ch4 = 0.0;
    wtcavai = 0.0;
	TileIrriAmount=0.0;
	TileIrriRate=0.0;
	TileIrri=0;//flag for if Tile its on or off
	count_Drain=1;
    autoHarvPer=0;//autoHarvest perrenial
	perCut1EstGDD=650;//set GDD value for 1st perennial cut 650 GDD in establishment year
	perCut1ProdGDD=450; //set GDD value for 1st perennial cut at 450 GDD in production year
	perCut2ProdGDD = 520;
	perGDDSinceLastCut = 0;
    soilProfileType=0;//for homogeneousProfile
    //day_weednup = 0.0;
    day_dsurea = 0.0;
	tillYieldFact = 1.0; //effect of tillage on yield
    /*dsno3 = 0.0;
    dsnh4 = 0.0;
	dsno3b = 0.0;
    dsnh4b = 0.0;
	dsno3c = 0.0;
    dsnh4c = 0.0;
	dsno3d = 0.0;
    dsnh4d = 0.0;
	dsno3e = 0.0;
    dsnh4e = 0.0;
	dsno3f = 0.0;
    dsnh4f = 0.0;*/
	snow_micro_growth=0.0;	
	germinationDays=0;
    dsnh3 = 0.0;
    ds_doc = 0.0;
    day_soil_ae_no = 0.0;
    day_soil_an_no = 0.0;
    day_soil_ae_n2o = 0.0;
    day_soil_an_n2o = 0.0;
    day_soil_n2 = 0.0;
    day_soil_nh3 = 0.0;
	yearAutoFert=1;
    germTemp=0.0;
	if(year==1)
	{
germCount=1;
	}
	
	//}
	//else{germCount=26;}
	day_soil_denitrification = 0.0;
	vernDays=0;
    irr_num = 0;
    til_num = 0;
    fer_num = 0;
    man_num = 0;
    plastic_num = 0;

	currentCut=0;
	stuntGrowth=1.0;
    //weeds = 0;
    //weedcn = 0.0;
    flo_num = 0;
	endYearOfSim = 0;
    //fdleak = 1;
    total_yr = 1;
	fert_flag = 0;
	irri_flag = 0;
    seed[1] = 0;
    yr_avet = 0.0;
    yr_rain = 0.0;
    //rno3 = 0.0;
    //base_nh3 = 0.0;
    PoolWater0 = 0.0;
    //irri_water = 0.0;
    yr_irri = 0.0;
    yr_PET = 0.0;
	yr_PETCROP=0.0;
	irri_index = 0.0;
	FloodingDays = 0;
	//StormFlag = 0;

    yr_addmc = 0.0;
    yr_addmn = 0.0;
	yr_addmP = 0.0;
    yr_sln = 0.0;
    yr_addrc = 0.0;
    yr_addrn = 0.0;
    yr_addrp = 0.0;
    //yr_weedn = 0.0;
    yr_wln = 0.0;
    yr_addtc = 0.0;
    yr_addtn = 0.0;
    yr_addleafc = 0.0;
    yr_addleafn = 0.0;
    yr_soil_co2 = 0.0;
    yr_root_co2 = 0.0;
    yr_ch4 = 0.0;
    yr_dnno = 0.0;
    yr_dnn2o = 0.0;
    yr_dnn2 = 0.0;
    yr_dcn2o = 0.0;
    yr_dcno = 0.0;
    yr_soil_nh3 = 0.0;
	//yr_water_demand=0.0;
	//yr_TDD=0.0;
    
    yr_minern = 0.0;
	//yr_assim = 0.0;
    cropWStress=0.0;
    yr_plant_nh3 = 0.0;
    yr_leach_hu = 0.0;
    yr_leach_un = 0.0;
    yr_leach_DOC = 0.0;
    by_pass_no3 = 0.0;
    flood_leachn = 0.0;
    yr_addfer = 0.0;
    //yr_rainn = 0.0;
	yr_rainN = 0.0;
	yr_PE=0.0;
	SolarEffectTemp=1.0;
    
    yr_ini_water = 0.0;
    yr_prec_water = 0.0;
    ini_snow_pack = 0.0;
    ini_surf_water = 0.0;
    ini_leaf_water = 0.0;
    tirri = 0.0;
    yr_end_water = 0.0;
    yr_snow_ev = 0.0;
	yr_soilIce_ev = 0.0;
	yr_pond_ev = 0.0;
    yr_fol_ev = 0.0;
    yr_trans = 0.0;
    yr_soil_ev = 0.0;
    //yr_byflux = 0.0;
    yr_leach_water = 0.0;
	yr_intercept = 0.0;
	yr_runoff = 0.0;
	//yr_FluxC = 0.0;
	//yr_FluxN = 0.0;
	yr_C_mine=0.0;
	//yr_FrostBio=0.0;
	
	
	yr_GrazeStub=0.0;
	yr_GWsuply=0.0;
	yr_WindSpeed=0.0;
	yr_shoot_CO2=0.0;
	yr_CropGPP=0.0;
	yr_Psn=0.0;
	yr_EcoCO2=0.0;
	yr_NEE=0.0;
	//yr_root_exudation=0.0;
	//yr_RootExude_co2=0.0;
	//season_N_stress=0.0;
	yr_GrazeDemandC=0.0;
	//yr_CutDemandC=0.0;
	//yr_RootDOC=0.0;
	yr_FineRootN=0.0;
	yr_total_ev =0.0;
	yr_NH3_deposit=0.0;
	yr_runoff_N=0.0;
	yr_runoff_C=0.0;
	yr_irri_N=0.0;
	yr_frostDOC=0.0;
	yr_inert_C = 0.0;
	yr_soilN_from_Nfixation=0.0;
    //AddC1 = 0.0;
    //AddC2 = 0.0;
    //AddC3 = 0.0;
    yr_leach_NO3 = 0.0;
	yr_leach_urea = 0.0;
    yr_DNassimN = 0.0;
    //I_Stage = 7;
    X_Stage = 7.0;
    Z_Stage = 0.0;
	remain_root=0.0;
	TotalSoilC=0.0;
	yr_runoff_SOC=0.0;
	yr_runoff_ION=0.0;
	yr_runoff_P=0.0;
	yr_leach_P = 0.0;

	yr_graze_dung_C= 0.0;
	yr_graze_dung_N= 0.0;
	yr_graze_urine_C= 0.0;
	yr_graze_urine_N= 0.0;
	yr_graze_urine_P= 0.0;
	yr_graze_dung_P= 0.0;
	yr_manure_water=0.0;


	seasDay1_129_wrunoff=0.0;seasDay130_365_wrunoff=0.0;seasDay305_365_wrunoff=0.0;seasDay1_304_wrunoff=0.0;seasDay288_365_wrunoff=0.0;
    seasDay1_129_wleach=0.0;seasDay130_365_wleach=0.0;seasDay305_365_wleach=0.0;seasDay1_304_wleach=0.0;seasDay288_365_wleach=0.0;
	seasDay1_129_N2O=0.0;seasDay130_365_N2O=0.0;seasDay305_365_N2O=0.0;seasDay1_304_N2O=0.0;seasDay288_365_N2O=0.0;
	seasDay1_129_NH3=0.0;seasDay130_365_NH3=0.0;seasDay305_365_NH3=0.0;seasDay1_304_NH3=0.0;seasDay288_365_NH3=0.0;
	seasDay1_129_Nleach=0.0;seasDay130_365_Nleach=0.0;seasDay305_365_Nleach=0.0;seasDay1_304_Nleach=0.0;seasDay288_365_Nleach=0.0;
	seasDay1_129_Nrunoff=0.0;seasDay130_365_Nrunoff=0.0;seasDay305_365_Nrunoff=0.0;seasDay1_304_Nrunoff=0.0;seasDay288_365_Nrunoff=0.0;
	seasDay1_129_precip=0.0;seasDay130_365_precip=0.0;seasDay305_365_precip=0.0;seasDay1_304_precip=0.0;seasDay288_365_precip=0.0;
	seasDay1_129_atemp=0.0;seasDay130_365_atemp=0.0;seasDay305_365_atemp=0.0;seasDay1_304_atemp=0.0;seasDay288_365_atemp=0.0;

	seasDay1_harv_atemp=0.0;seasDay1_harv_precip=0.0;seasDay1_harv_wrunoff=0.0;seasDay1_harv_wleach=0.0;seasDay1_harv_denit=0.0;seasDay1_harv_N2O=0.0;seasDay1_harv_NH3=0.0;seasDay1_harv_netNmin=0.0;seasDay1_harv_Nleach=0.0;seasDay1_harv_irri=0.0;seasDay1_harv_trans=0.0;seasDay1_harv_evap=0.0;
    seasDay1_pDate_atemp=0.0;seasDay1_pDate_precip=0.0;seasDay1_pDate_wrunoff=0.0;seasDay1_pDate_wleach=0.0;seasDay1_pDate_denit=0.0;seasDay1_pDate_N2O=0.0;seasDay1_pDate_NH3=0.0;seasDay1_pDate_netNmin=0.0;seasDay1_pDate_Nleach=0.0;seasDay1_pDate_irri=0.0;seasDay1_pDate_trans=0.0;seasDay1_pDate_evap=0.0;
	seasDay182_365_atemp=0.0;seasDay182_365_precip=0.0;seasDay182_365_wrunoff=0.0;seasDay182_365_wleach=0.0;seasDay182_365_denit=0.0;seasDay182_365_N2O=0.0;seasDay182_365_NH3=0.0;seasDay182_365_netNmin=0.0;seasDay182_365_Nleach=0.0;seasDay182_365_irri=0.0;seasDay182_365_trans=0.0;seasDay182_365_evap=0.0;
	gs_N2O = 0.0;  gs_precip = 0.0; gs_atemp = 0.0;
	ngs1_N2O = 0.0; ngs1_precip = 0.0; ngs1_atemp = 0.0;
	ngs2_N2O = 0.0; ngs2_precip = 0.0; ngs2_atemp = 0.0;
	countIrri=0;
	seasPET = 0.0; //define seasonal PET unmodified for batch output
	seasPETKC = 0.0;//define seasonal PET KC modified for batch output

	seasCO2Het1 = 0.0;
	seasCO2Het2 = 0.0;
	seasCO2Het3 = 0.0;
	autoPlantCount = 0;
	cropGrowDays1 = 0;
	cropGrowDays2 = 0; 
	cropGrowDays3 = 0;
	seasEvap1 = 0.0;
	seasEvap2 = 0.0; 
	seasEvap3 = 0.0;
	trans1 = 0.0;
	trans2 = 0.0; 
	trans3 = 0.0;
	Nmin1 = 0.0; Nmin2 = 0.0; Nmin3 = 0.0; Nimb1 = 0.0; Nimb2 = 0.0; Nimb3 = 0.0;
	seasWL1 = 0.0; seasNH31 = 0.0; seasSoilN1 = 0.0; seasSOC1 = 0.0; seasSON1 = 0.0; seasNO31 = 0.0; seasCO21 = 0.0;
	seasWL2 = 0.0; seasNH32 = 0.0; seasSoilN2 = 0.0; seasSOC2 = 0.0; seasSON2 = 0.0; seasNO32 = 0.0; seasCO22 = 0.0;
	seasWL3 = 0.0; seasNH33 = 0.0; seasSoilN3 = 0.0; seasSOC3 = 0.0; seasSON3 = 0.0; seasNO33 = 0.0; seasCO23 = 0.0;
	seasMaxLAI1 = 0.0; seasMaxLAI2 = 0.0; seasMaxLAI3 = 0.0; SOC64 = 0.0; SOC66 = 0.0; SOC80 = 0.0; SOC304 = 0.0; SON64 = 0.0; SON66 = 0.0; SON80 = 0.0; SON304;
	daySoilWater151 = 0.0; daySoilWater201 = 0.0; daySoilWater152 = 0.0; daySoilWater202 = 0.0; daySoilWater153 = 0.0; daySoilWater203 = 0.0;
	for (int sa = 1; sa <= 3; sa++)
	{
		FertAddNSA[sa] = 0.0;
		FertAddCSA[sa] = 0.0;
	}
	seasDenit1 = 0.0; harvSoilN1 = 0.0; seasDenit2 = 0.0; harvSoilN2 = 0.0; seasDenit3 = 0.0; harvSoilN3 = 0.0;
	cropCHU = 0.0;
	cropGDD = 0.0;
    Assim = 0.0;
    Total_Resp = 0.0;
    canopy_Tmin = 0.0;
    canopy_Tmax = 0.0;
    canopy_Tmean = 0.0;
    biomass = 0.0;
	
    //gs_PET = 0.0;
    //gs_ET = 0.0;
    //gs_rain = 0.0;
    yr_ET = 0.0;
    muture_flag = 0;
    EFFAC = 0.2;
	u_PGI = 0.0;
	
	old_Tmin = 0.0;
	IrriMethod=0;
	wddupn=0.0;
	OldT = 0.0;
	old_tev = 0.0;
	manuFlag=0;
	slurry_doc=0.0;
	//deep_doc=0.0;
	RainfedRice_flag=0;
	DeepRice_flag=0;
	irri_close=0;
	wind_damage_flag=0.0;
	//old_lh_out_water=0.0;
	totalqDrain=0.0;
	//crhl=0.0;
	//crhr=0.0;
	//drcvl=0.0;
    //DRCB=0.0;
	//DRCB1=0.0;
	//DRCB2=0.0;
	//lit_co2=0.0;
    //sumn=0.0;
	//fb_nh4=0.0;
	//fb_co2=0.0;
	//dcbavai=0.0;
	//fh_co2=0.0;
    //fh_nh4=0.0;	
    
	old_leach_no3 = 0.0;
	//urea_day = 0;
	k = 0;
	NDEF1=1.0;
	NDEF2=1.0;
	rainMulti=1.0;
	primeDenit = 1.0;
	runMulti=1.0;//runoff Multiplyer.
	runMulti=1.0;
	denitMulti=1.0;
	nitMulti=1.0;
	nit2Multi=1.0;
	springMulti=1.0;
	manureCounter=0;
	Root_Depth = 0.0;
	  TCNP = 0.0;
	  RCNP = 0.0;
	  CumVD = 0.0;
	  Sum_Dtt = 0.0;
	  Days_After_Sow = 0;
	  Days_In_Stage = 0;
	  old_Canopy_Tmax=0.0;
  
   root_up=0.0;
   sfer6=0.0;
   sfer7=0.0;
   fer_layer=1;
   manu_layer=1;
   flood_flag=0;
   tilld = 0.0;
   //weedn = 0.0;
   
   FloDays=0;
   SatuDays=0;
   //unFloDays=30;
   
   //unFloDs=0;
   //k1=0;
   //k2=0;
   clayCrackLayer = 0;
   ABC_day = 0;
   prof_DOC = 0.0;

   yr_balance_ch4 = 0.0;
      
   SnowMelt = 0.0;
   yr_bypass_in = 0.0;
   yr_water_in = 0.0;
   //yr_paddy_water_ev = 0.0;
   total_ice = 0.0;
   flood_num = 0;
   labile_manure = 0.0;
   //LabileLitterC = 0.0;
   //LabileLitterN = 0.0;
   ManureDays = 0;
   Manure_water = 0.0;
   plastic_flag = 0;
   NIDuration0=0.0;
   NIDuration1=0.0;
   NIDay1=0;
   NIDay2=0;
     UIDay1=0;
   UIDay2=0;
   UreaAppDays=0;
   SlowReleaseDays =0;
   IniFixFert1=0.0;
   IniFixFert2=0.0;
   IniFixFert3=0.0;
   IniFixFert4=0.0;
   IniFixFert5=0.0;
   IniFixFert6=0.0;
   IniFixFert7=0.0;
   Profile_OrgP=0.0;
   Profile_LabP=0.0;
   Profile_ComP=0.0;
   Profile_AdsP=0.0;
   SlurryFlag=0;
   crop1_trans=0.0;
   crop2_trans=0.0;
   crop_terminator=0;

   DayAT = 0.0;
   act_DayAT=0.0;
   leaf_area_N = 0.0;
   //irri_add_water = 0.0;
   ddday = 0;
   Pfer1=0.0;
   Pfer2=0.0;
   Pfer3=0.0;
   Pfer4=0.0;
   Pfer5=0.0;
   Pfer6=0.0;
   Pfer7=0.0;
   Pso4 = 0.0;
   RainfedDepth=0.0;
   RainfedPool=0.0;
   //DFcrop = 1.0;
   ShallowFloodFlag = -1;
   WaterLeakRate = 0.001;
   WaterGetherIndex = 1.0;
   
   //weed_demandn = 0.0;   
   PI= 3.1415926;
   DayPET=0.0;
   DayAET = 0.0;
   DayPETmod=0.0;
    
   SurfaceUrea=0.0;
   //frost_doc=0.0;
   wetland_flag = 0;
   //CropEndDay = 0;
   CropNumbers = 0;
   dFlag = 0;
   crop_transp = 0.0;
   UreaHydroInhibEf=0.0;
   UreaHydroInhibDu=0.0;
   UreaHydroInhibDays=0;

   sfer1=0.0;
   sfer2=0.0;
   sfer3=0.0;
   sfer4=0.0;
   sfer5=0.0;
   sfer6=0.0;
   sfer7=0.0;

   day_RootInput_DOC=0.0;
   yr_InputRoot_DOC=0.0;
   LayerDeficit=0.0;
   IrriRice_flag=0;
   fertigate_flag=0;
   stem_age=1;
   drain_flag=0;
   manure_flag=0;
  
   sedyld = 0.0;

   FloodWater_N = 0.0;
   pen_soil_wfps = 0.3;
   rice_maturity_flag = 0;
   IniProfWater = 0.0;
   DayCropWaterDeficit=0.0;
   jarovization_flag=1.0;
   OverHotDays = 0;
   IniSP=0.0;
   EndSP=0.0;
   yr_inFertP=0.0;
   yr_indirect_n2o=0.0;
   yr_indirect_n2=0.0;

   for(i=0;i<=7;i++) 
   {
	   DayFertRelease[i]=0.0;
	   yr_GrazeGrain[i]=0.0;
		yr_GrazeShoot[i]=0.0;
		yr_GrazeRoot[i]=0.0;
		yrShootSenesN[i] = 0.0;
		cropRad[i] = 0.0;
		cropRadAcc[i] = 0.0;
			
   }
   for (int z = 0; z <= 9; z++)
   {
	   for (i = 0; i <= 9; i++)
	   {
		   
		   yearlyNStress[z][i] = 0.0;
		   yearlyNUptake[z][i] = 0.0;
		   averageNStress[i] = 0.0;
		   averageNUptake[i] = 0.0;
		   cropRotType[i] = 0;
	   }
   }
   //averageNStress=0.0;
   //averageNUptake=0.0;

   for(i=0;i<=10;i++) SWT[i]=20.0;
      
 

#ifdef MANURE
//if(facility==0)//feedlot
{    
    MData.yr_enteric_ch4=0.0;
	MData.yr_enteric_n2o=0.0;
	MData.yr_enteric_nh3=0.0;
	MData.yr_house_nh3=0.0;
	MData.yr_house_n2o=0.0;
	MData.yr_house_ch4=0.0;
	MData.yr_house_co2=0.0;
	MData.yr_house_n2=0.0;
	MData.yr_house_no=0.0;
	MData.yr_intake_C=0.0;
	MData.yr_intake_N=0.0;
	MData.yr_intake_P=0.0;
	
	MData.yr_milk_C=0.0;
	MData.yr_milk_N=0.0;
	MData.yr_milk_P=0.0;
	MData.yr_meat_C=0.0;
	MData.yr_meat_N=0.0;
	MData.yr_meat_P=0.0;
	MData.yr_urine_C=0.0;
	MData.yr_urine_N=0.0;
	MData.yr_urine_P=0.0;
	MData.yr_dung_C=0.0;
	MData.yr_dung_N=0.0;
	MData.yr_dung_P=0.0;
	MData.yr_enteric_co2=0.0;
	MData.yr_waste_water=0.0;
	MData.yr_milk_product=0.0;
	MData.yr_urine_water=0.0;
	MData.yr_dung_water=0.0;
	//MData.yr_animal_CO2=0.0;
	MData.yr_house_evap=0.0;
	MData.yr_bed_C=0.0;
	MData.yr_bed_N=0.0;
	MData.yr_floor_leach_water=0.0;
	MData.yr_floor_leach_urea=0.0;
	MData.yr_floor_leach_NH4=0.0;
	MData.yr_floor_leach_NO3=0.0;
	MData.yr_floor_leach_doc=0.0; 

}	
	
//if(facility==1)//storage/treatment
{ 	
	MData.yr_compost_nh3=0.0;
	MData.yr_compost_ch4=0.0;
	MData.yr_compost_n2o=0.0;
	MData.yr_compost_n2=0.0;
	MData.yr_compost_no=0.0;
	MData.yr_compost_co2=0.0;
	MData.yr_compost_EV=0.0;
	MData.yr_compost_leach_H2O=0.0;
	MData.yr_compost_InRain=0.0;
	MData.yr_compost_add_C=0.0;
	MData.yr_compost_add_N=0.0;
	
	MData.yr_lagoon_nh3=0.0;
	MData.yr_lagoon_n2o=0.0;
	MData.yr_lagoon_ch4=0.0;
	MData.yr_lagoon_co2=0.0;
	MData.yr_lagoon_n2=0.0;
	MData.yr_lagoon_co2=0.0;
	MData.yr_lagoon_no=0.0;
	MData.yr_lagoon_EV=0.0;
	MData.yr_Lagoon_to_field_N=0.0;
	MData.yr_Lagoon_to_field_C=0.0;
	MData.yr_Lagoon_to_field_H2O=0.0;
	MData.yr_Lagoon_to_field_P=0.0;
	MData.yr_lagoon_InRain=0.0;

	MData.yr_House_to_field_N=0.0;
	MData.yr_House_to_field_C=0.0;
	MData.yr_House_to_field_H2O=0.0;
	MData.yr_House_to_field_P=0.0;

	MData.yr_digester_ch4=0.0;
	MData.yr_digester_nh3=0.0;
	MData.yr_digester_n2o=0.0;
	MData.yr_digester_no=0.0;
	MData.yr_digester_n2=0.0;
	MData.yr_digester_co2=0.0;
	MData.yr_digester_EV=0.0;

	MData.yr_digester_to_field_C=0.0;
	MData.yr_digester_to_field_N=0.0;
	MData.yr_digester_to_field_H2O=0.0;
	MData.yr_digester_to_field_P=0.0;

	MData.yr_digester_to_lagoon_C=0.0;
	MData.yr_digester_to_lagoon_N=0.0;
	MData.yr_digester_to_lagoon_H2O=0.0;
	MData.yr_digester_to_lagoon_P=0.0;	
	
	MData.yr_digester_to_market_C=0.0;
	MData.yr_digester_to_market_N=0.0;
	MData.yr_digester_to_market_H2O=0.0;
	MData.yr_digester_to_market_P=0.0;
	
	MData.yr_ManureN_toField=0.0;	
	MData.yr_House_to_Compost_H2O=0.0;
	MData.yr_House_to_compost_C=0.0;
	MData.yr_House_to_compost_N=0.0;
	MData.yr_House_to_compost_P=0.0;

	MData.yr_House_to_lagoon_C=0.0;
	MData.yr_House_to_lagoon_N=0.0;
	MData.yr_House_to_lagoon_H2O=0.0;
	MData.yr_House_to_lagoon_P=0.0;

	MData.yr_House_to_digester_C=0.0;	
	MData.yr_House_to_digester_N=0.0;
	MData.yr_House_to_digester_H2O=0.0;
	MData.yr_House_to_digester_P=0.0;
	
	MData.yr_House_to_field_C=0.0;	
	MData.yr_House_to_field_N=0.0;
	MData.yr_House_to_field_H2O=0.0;
	MData.yr_House_to_field_P=0.0;	

	MData.yr_Compost_to_field_C=0.0;
	MData.yr_Compost_to_field_N=0.0;
	MData.yr_Compost_to_field_H2O=0.0;
	MData.yr_Compost_to_field_P=0.0;
}

	//MData.yr_field_nh3=0.0;
	//MData.yr_field_ch4=0.0;
	//MData.yr_field_n2o=0.0;	
	
	MData.LI_NH3 = 0.0;
	MData.AI_NH3 = 0.0;

	MData.yr_LOS_ch4 = 0.0;
	MData.yr_LOS_n2o = 0.0;
	MData.yr_LOS_nh3 = 0.0;
	MData.yr_LOS_LeachN = 0.0;
	
	MData.yr_compost_runoff_WATER=0.0;
	MData.BarnDays=0;
			
	for(i=0; i<=9; i++)
	{
	MData.yr_runoff_MC[i]=0.0;
	MData.yr_runoff_MIN[i]=0.0;
	MData.yr_runoff_MON[i]=0.0;
	MData.yr_market_MC[i]=0.0;
	MData.yr_market_MIN[i]=0.0;
	MData.yr_market_MON[i]=0.0;
	}
	
	day_inManureN = 0.0;
	MData.LagoonCrustC = 0.0;
	MData.lagoon_days = 0;
	MData.yr_flush_H2O = 0.0;
//}
#endif	

//#ifdef HYDRO//===Record annual variable;dengjia===
	 yr_muslerunoff=0.0;
	 yr_muslesedyld=0.0;
	 yr_muslesoc=0.0;
	 yr_musleson=0.0;
	 yr_muslenh4=0.0;
	 yr_musleno3=0.0;
	 yr_muslenh3=0.0;
	 yr_musleurea=0.0;
	 yr_musleclayn=0.0;
//#endif
	
   for(i=0; i<=20; i++)
		{
		topc[i]=0.0;
		topn[i]=0.0;
		layerc[i]=0.0;
		layern[i]=0.0;
	     LayerSoilWeight[i]=0.0;	
	   }
    for(i=0; i<=7; i++)
    {
		leafTemp_C[i] = 0.0;
		winterKill[i] = 1.0;
		photoPeriodStress[i]=0.0;
		cTT[i]=0.0;
		cropTempStress[i] = 0.0;
		cropTempStressAnnual[i] = 0.0;
		meanTempStressT[i] = 0.0;
		pDF[i]=0.0;
		pDFCUM[i]=0.0;
		vernal[i]=0;
		cropHarvestDay[i]=366;
		flowering1Day[i]=0;
		flowering2Day[i] = 0;
		flowering3Day[i] = 0;
		floweringDay[i] = 0;
		podDay[i]=0;
		emergenceDay[i] = 0;
		plantingDay[i] = 0;
		seasGrain[i] = 0.0; seasLeaf[i] = 0.0; seasRoot[i] = 0.0; seasStem[i] = 0.0; seasGrainN[i] = 0.0; seasLeafN[i] = 0.0; seasRootN[i] = 0.0; seasStemN[i] = 0.0;
		seedFillDay[i]=0;
		maturityDay[i]=0.0;
		growthStatus[i] = 0;
		cropGrowDays[i]=0;
		cropYieldDry[i]=0;
		N2NodEFACC[i] = 0.0;
		jdseed[i] = 0;
		left_perc[i] = 0.0;
		grow_days[i] = 0;
		crop[i] = 0;
		nitscaleC[i]=0.0;
		//liupt[i] = 0.0;
		PresentBiomass[i] = 0.0;
		YrG_grain[i] = 0.0;
		YrG_leaf[i] = 0.0;
		YrG_stem[i] = 0.0;
		YrG_root[i] = 0.0;
		YrG_lai[i]=0.0;
		startOptLeafC[i] = 0.0;
		YrN_grain[i] = 0.0;
		YrN_leaf[i] = 0.0;
		YrN_stem[i] = 0.0;
		YrN_root[i] = 0.0;

		MaxYrG_grain[i] = 0.0;
		MaxYrG_leaf[i] = 0.0;
		MaxYrG_stem[i] = 0.0;
		MaxYrG_root[i] = 0.0;
		MaxYrG_lai[i] = 0.0;
		MaxYrN_grain[i] = 0.0;
		MaxYrN_leaf[i] = 0.0;
		MaxYrN_stem[i] = 0.0;
		MaxYrN_root[i] = 0.0;


		plantn[i] = 0.0;
		PlantTakeN[i]=0.0;
		yr_plantn[i] = 0.0;
		plantP[i] = 0.0;
		GrainP[i] = 0.0;
	    LeafP[i] = 0.0;
	    StemP[i] = 0.0;
	    RootP[i] = 0.0;

		yr_plantP[i] = 0.0;
		day_P_uptake[i] = 0.0;
		maxmn[i] = 0.0;
		harvest_flag[i] = 0;
		demandn[i] = 0.0;
		
		rootcnDyn[i] = 0.0;
		leafcnDyn[i] = 0.0;
		stemcnDyn[i] = 0.0;
		graincnDyn[i] = 0.0;




		graincn[i] = 0.0;
		rootcn[i] = 0.0001;
		leafcn[i] = 0.0;
		stemcn[i] = 0.0;
		wreq[i] = 0.0;
		
		base_graincn[i] = 0.0;//Brian
		base_rootcn[i] = 0.0001;
		base_leafcn[i] = 0.0;
		base_stemcn[i] = 0.0;
		base_wreq[i] = 0.0;
		base_maxmn[i] = 0.0;

		sprintf(crop_name[i], "None");
		
		root_depth[i] = 0.0;
		root_length[i]=0.0;
		
		leafcn[i] = 0.0001;
		stemcn[i] = 0.0001;
		CropSumN[i] = 0.0;
		
		WinterCropFlag[i] = 0;
		HarvestYear[i] = 0;
		yr_uptaken[i] = 0.0;
		yr_fixn[i] = 0.0;
		//CropAbsorbN[i]=0.0;

		OptGrainC[i] = 0.0;
		OptCropC[i] = 0.0;
		OptLeafC[i] = 0.0;
		OptStemC[i] = 0.0;
		OptRootC[i]=0.0;

		CropWaterDemand[i]=0.0;
		//cropNdemand[i]=0.0;
		crop_T_demand[i]=0.0;
		//crop_optimum_yield[i]=0.0;
		TDD[i]=0.0;
		crop_trans[i]=0.0;
		HarvestDay[i]=0;
		crop_N_stress[i]=0.0;
		crop_water_stress[i]=0.0;
		crop_PPT[i]=0.0;
		crop_PPT_days[i]=0;
		crop_N_stress_days[i]=0;
		cropTempStressDays[i] = 0;
		crop_water_stress_days[i]=0;
		crop_days[i]=0;
		perRegrow[i]=0;
		ProdC[i]=0.0;
		YrProdC[i]=0.0;
		ProdCGrain[i]=0.0;
		ProdCShoot[i]=0.0;
		ProdCRoot[i]=0.0;
		crop_PT[i]=0.0;
		crop_AT[i]=0.0;
		Root_Wt[i]=0.0;
		Pod_Wt[i] = 0.0;
		Root_ExuC[i] = 0.0;
		Root_ExuN[i] = 0.0;
		Leaf_Wt[i]=0.0;
		Stem_Wt[i]=0.0;
		Grain_Wt[i]=0.0;
		FertAddN[i]=0.0;
		//yr_CropN_air[i]=0.0;
		//cropN_demand[i]=0.0;
		crop_NH3_absorp[i]=0.0;
		lai[i] = 0.0;
		PGI[i] = 0.0;
		totalFFPGI[i]=0.0;
		int bb;
		for(bb=1;bb<=8;bb++)
		{
		per[i][bb]=0.0;
		}
		day_nup[i] = 0.0;
		N_stress[i] = 1.0;
		//cut_root_litter[i]=0.0;
		//fine_root_pool[i]=0.0;
		day_soilN_from_Nfixation[i]=0.0;
		ddupn[i] = 0.0;
		day_plant_nh3[i] = 0.0;
		root_doc[i]=0.0;//rice caborn rhizodeposition (kg doc-C/ha/d)
		day_rco2[i] = 0.0;
		Day_GrowthN[i] = 0.0;
		day_DWater[i] = 1.0;
		yr_need_N[i]=0.0;
		Yr_PlantBiomass[i]=0.0;
		
		Dwilt[i]=0;
		WiltFlag[i]=0.0;
		PerennialFlag[i]=0;
		GrassFlag[i]=0;
		//CropEndN[i]=0.0;
		crop_flag[i]=0;
		maturity_flag[i]=0; 
//		max_root_length[i]=0.0;
		root_length[i]=0.0;
		PPT[i]=0.0;
		DayPETCROP[i]=0.0;
		PPTactual[i]=0.0;
		APT[i]=0.0;
		flood_N[i]=0.0;
		yr_CutGrain[i]=0.0;
		for (int zz = 0; zz <= 6; zz++)
		{
			eachGrassCut[i][zz] = 0.0;
			eachGrassCutN[i][zz] = 0.0;
		}
		yr_CutLeaf[i]=0.0;
		yr_CutStem[i]=0.0;
		yr_CutRoot[i]=0.0;
		LeafN[i]=0.0;
		StemN[i]=0.0;
		RootN[i]=0.0;
		GrainN[i]=0.0;
		PodN[i] = 0.0;
		DayGrow_LeafN[i]= 0.0;
		DayGrow_StemN[i]= 0.0;
		DayGrow_RootN[i]= 0.0;
		DayGrow_GrainN[i]= 0.0;
		DayGrow_PodN[i] = 0.0;
		
		plantP[i]=0.0;
		GrainP[i] = 0.0;
	    LeafP[i] = 0.0;
	    StemP[i] = 0.0;
	    RootP[i] = 0.0;
		Excreta[i]=1;
		if(i>0) Transplant[i]=0;
		HarvestedBiomassC[i]=0.0;
		ReserveN[i]=0.0;
    }
    
	for (i=1; i<=25; i++)
    {
		jdirr[i] = 0;
		irria[i] = 0.0;
		tileIrriDays[i]=0;
		irriph[i] = 7.0;
		stdrain[i]=0;
		enddrain[i]=0;
		cdraindepth[i]=0.0;
		jdtil[i] = 0;
		til_dept[i] = 0.0;
		jdfer[i] = 0;
		
		fer_dept[i] = 0.0;
		fer1[i] = 0.0;
		fer2[i] = 0.0;
		fer3[i] = 0.0;
		fer4[i] = 0.0;
		fer5[i] = 0.0;
		fer6[i] = 0.0;
		fer7[i] = 0.0;
		//NH4_type[i] = 1;
		jdman[i] = 0;
		ManureOrgC[i] = 0.0;
		manucn[i] = 0.0;
		ManureType[i] = 0;
		jdplastic1[i] = 0;
		jdplastic2[i] = 0;
		jdflo1[i] = 0;
		jdflo2[i] = 0;
		inject[i] = 0.0;
		manuAppHour[i]=0;
		manuDM[i]=0.0;
		manuPH[i]=0.0;
		ManureDepth[i] = 0.0;
		ManureOrgN[i] = 0.0;
		ManureNH4[i] = 0.0;
		ManureNO3[i] = 0.0;
		ManureDOC[i]=0.0;
		ManureUREA[i] = 0.0;
    }

    for(i=0; i<10; i++)
    {
       AnimalCode[i]=0;
	   //AnimalName[i]='NULL';
		Default_C_intake[i]=0.0; 
		Milk_C_fraction[i]=0.0; 
		Meat_C_fraction[i]=0.0; 
		Urine_C_fraction[i]=0.0;
		Dung_C_fraction[i]=0.0; 
		Enteric_CH4_C_fraction[i]=0.0; 
		Respiration_C_fraction[i]=0.0; 
		Default_N_intake[i]=0.0;
		Milk_N_fraction[i]=0.0; 
		Meat_N_fraction[i]=0.0; 
		Urine_N_fraction[i]=0.0; 
		Dung_N_fraction[i]=0.0; 
		Enteric_N2O_N_fraction[i]=0.0;
		for(int j=0; j<50; j++) livestock_C_demand[i][j]=0.0;
		
    }

	for(i=0; i<366; i++)
    {
       DayFert1[i] = 0.0;
	   DayFert2[i] = 0.0;
	   DayFert3[i] = 0.0;
	   DayFert4[i] = 0.0;
	   DayFert5[i] = 0.0;
	   DayFert6[i] = 0.0;
	   DayFert7[i] = 0.0;
	   total_C_demand[i] = 0.0;
	   
	   //DDW[i] = 1.0;
    }
    DayFixFert1=0.0;
	   DayFixFert2=0.0;
	   DayFixFert3=0.0;
	   DayFixFert4=0.0;
	   DayFixFert5=0.0;
	   DayFixFert6=0.0;
	   DayFixFert7=0.0;
    Total_Resp=0.0;  //total respiration of plant kg C/ha/d (growth res. + maint. res.)
    surf_w=0.0;//surface water depth,m
    dw_temp=0.0;//daily avrage value of surface water temperature
    Surf_Temp=0.0;//daily surface temperature
    ch4_prod=0.0; // daily ch4 production rate (kg CH4-C/ha/d)
	ch4_prod1=0.0;
	ch4_prod2=0.0;
    plant_day_ch4=0.0;//emission flux of ch4 via plant(kg ch4-C/ha/d)
    ch4_day_oxid=0.0; //oxidation rate (kg ch4-C/ha/d)
    //ch4_dif=0.0;//emission rate of ch4 via diffusion (kg ch4-C/ha/d)
    //ch4_eb=0.0;//emission rate of ch4 via ebullition (kg ch4-C/ha/d)
    
int a1;
	for(i=0; i<MAXSOILLAYER; i++)
    {
		for(a1=0;a1<=7;a1++)
		{
		rootDensity[a1][i]=0.0;
		}
	BandedAppMulti[i] = 1.0;
	UreaHydroCounter[i]=0.0;
	theta_s[i]=0.0;//added for hydrology
	hourly_theta[i]=0.0;//added for hydrology
	Ks[i]=0.0;//added for hydrology
	theta_app[i]=0.0;//added for hydrology
	unsat_K[i]=0.0;//added for hydrology
	mat_pot_entry[i]=0.0;//added for hydrology
	mat_pot[i]=0.0;//added for hydrology
	h_pot[i]=0.0;//added for hydrology
	hydro_condK[i]=0.0;//added for hydrology
	clayCrackAccum[i] = 0.0;//added for clay Cracking method
    hourlyTemp[i]=0.0;
	lastKw[i]=0.0;
	rcvl[i] = 0.0;
	rcl[i] = 0.0;
	manurePool[i] = 0.0;
	rcr[i] = 0.0;
	ocini[i] = 0.0;
	dphum[i] = 0.0;
	startHead[i]=0.0;
	finalHead[i]=0.0;
	theta[i]=0.0;
	kTheta[i]=0.0;
	no2[i] = 0.0;
	no3[i] = 0.0;
	nh4[i] = 0.0;
	clay_nh4[i] = 0.0;
	urea[i] = 0.0;
	NH4HCO3[i] = 0.0;
	nh3[i] = 0.0;
	no[i] = 0.0;
	n2o[i] = 0.0;
	n2[i] = 0.0;
	temp[i] = 0.0;
	day_wfps[i] = 0.0;
	sph[i] = 0.0;
	//oldwater[i] = 0.0;
	ave_anvf[i] = 0.0;
	anvf[i] = 0.0;
	ice[i] = 0.0;
	R_Wt[i] = 0.0;
	doc[i] = 0.0;
	Eh[i] = 0.0;
	day_O2[i] = 0.0;
	co2[i]=0.0;
	//day_hdc[i]=0.0;
	crhl[i]=0.0;
	crhr[i]=0.0;
	CRB1[i] = 0.0;
	CRB2[i] = 0.0;
	newh[i] = 0.0;
	DayFlux[i] = 0.0;
	ch4[i] = 0.0;
	
	O2_old[i] = 0.0;
	Eh_old[i] = 0.0;
	O2[i] = 0.0;
    //nitrifier[i] = 0.0;
	//old_f_lost[i] = 0.0;
	Mn4[i] = 0.0;
	Mn2[i] = 0.0;
	Fe3[i] = 0.0;
	Fe2[i] = 0.0;
	SO4[i] = 0.0;
	H2S[i] = 0.0;
	doc_w[i]=0.0;  
	//denitrifier[i]=0.0;  
	no_w[i]=0.0; 
    n2o_w[i]=0.0;  
	no2_w[i]=0.0; 
    no3_w[i]=0.0;  
	assim2[i]=0.0;  
	nh4_w[i]=0.0; 
    doc_d[i]=0.0;  
	no_d[i]=0.0; 
    n2o_d[i]=0.0;  
	n2_w[i]=0.0;  
	no2_d[i]=0.0; 
    no3_d[i]=0.0;  
	nh4_d[i]=0.0; 
	//root_CO2[i]=0.0;
	crhl[i]=0.0;
	crhr[i]=0.0;
	F_methanogen[i]=0.0;
	//ice_N[i]=0.0;
	//ice_n2o[i]=0.0;
	//ice_n2[i]=0.0;
	soc[i] = 0.0;
	son[i] = 0.0;
	sop[i] = 0.0;
	inert_C[i]=0.0;
	SoilDepth[i] = 0.0;
	LabP[i]=0.0;
	OrgP[i]=0.0;
	ComP[i]=0.0;
	AdsP[i]=0.0;
	MinP[i]=0.0;
	ch4_doc_pool[i]=0.0;
	//old_AdsP[i]=0.0;
	acetate[i]=0.0;
	H2[i]=0.0;
	Tttoo[i]=0.0;
	TotalDOC[i]=0.0;
	peat_DOC[i]=0.0;
	peat_CO2[i]=0.0;
	ch4_doc_pool[i]=0.0;
	day_H2_pool[i]=0.0;
	day_ch4_CO2[i]=0.0;
	day_nitrification[i]=0.0;
	day_nitrify_n2ol[i] = 0.0;
	day_denitrification[i]=0.0;
	day_denitrify_n2ol[i] = 0.0;

#ifdef ISOTOPE
	CO2_13[i]=0.0;
	CO2_12[i]=0.0;
	DOC_13[i]=0.0;
	DOC_12[i]=0.0;
	CH4_13[i]=0.0;
	CH4_12[i]=0.0;
#endif	
	for(int j=0;j<25;j++) water[j][i]=0.0;
	
	}

	
}

void class_model::read_in_site(int MODE, int Batch)
{
    int junk_d, jjd;
    char site_file[80];
    FILE *fp;

    sprintf(site_file, "%s\\Inputs\\SITE", OUTPUT);
    fp = fopen(site_file, "r");
    if (fp==NULL) note(0, site_file);
	 
    fscanf(fp, "%s", site);
    fscanf(fp, "%d %d %f %d %f", &total_yr, &day_file,
	   &latitude, &junk_d, &longitude);
	fscanf(fp, "%d %d", &LandUse, &jjd);
	if(MODE==1)
	{
		fscanf(fp, "%s", countryName);
		fscanf(fp, "%s", stateName);
	}

    fclose( fp );

	if(Batch==3) day_file = 1;//site-mode test for region run

}
int class_model::read_in_extra_parm(int MODE, int SoilYear, int MonteCarlo)
{
	 FILE *fp;
    char  EXTRA_YEAR[80];
    int   i, IniYr=1;

	if (MODE==0||MonteCarlo==1)
    {
		sprintf(EXTRA_YEAR, "%s\\Inputs\\extra2-%d", OUTPUT, year);
    }
    else
    {
		if(SoilYear==999) sprintf(EXTRA_YEAR, "%s\\Inputs\\extra2-A", OUTPUT);
		else
		{
			if(SoilYear==1||SoilYear==0)
				sprintf(EXTRA_YEAR, "%s\\Inputs\\extra2-A%d", OUTPUT, year);
			else
				sprintf(EXTRA_YEAR, "%s\\Inputs\\extra2-B%d", OUTPUT, year);
		}
    }
  fp = fopen(EXTRA_YEAR, "r");
    if ( fp == NULL ) note(0, EXTRA_YEAR);//reading the soil-1 etc parameters.
	
    fscanf(fp, "%d", &SoilSpinUpCounter);
	fclose(fp);

	return(0);
}
int class_model::read_in_soil_parm(int MODE, int SoilYear, int MonteCarlo)
{
    FILE *fp;
    char  SOIL_YEAR[80];
    int   i, IniYr=1;
    float jf, SOCa, SOCb, SoilIniP;
	float LayerDepth = 0.0;//, Tttoo[100]={0.0, 0.0};
	float wrcvl=0.0, wrcl=0.0, wrcr=0.0, wcrb=0.0, wcrhl=0.0, wcrhr=0.0; 
	float whumus=0.0, wtcavai=0.0, winertC=0.0, wFreezedoc=0.0;
	float wrnvl=0.0, wrnl=0.0, wrnr=0.0, wnrb=0.0, wnrhl=0.0, wnrhr=0.0, whumusn=0.0;//, winertC/PassiveCCN, ;
	float w_n2o=0.0, w_n2=0.0, w_nh3=0.0, w_no3=0.0, w_nh4=0.0, wurea=0.0, day_clay_N=0.0, wpool_no=0.0; 
	float InertN=0.0;
	float manPoolTot = 0.0;//initialize manPoolTot for total manurePool C











	default_Mn = 0.05; //mol/L soil, U.S. GEOLOGICAL SURVEY PROFESSIONAL PAPER 1270, 1984; 550 ppm.
	default_Fe = 1.073; //mol/L soil, U.S. GEOLOGICAL SURVEY PROFESSIONAL PAPER 1270, 1984: 26000 ppm
	default_SO4 = 0.1166; //mol/L soil, U.S. GEOLOGICAL SURVEY PROFESSIONAL PAPER 1270, 1984: 1600 ppm
	//day_WT = -9.99;

/*
				//drainage Params
				char junk[80];

				CString TESTFILE;
				FILE *pFile=NULL;
				TESTFILE.Format("%s\\Record\\Drainage.txt", OUTPUT);
				pFile = fopen (TESTFILE,"r");
				fscanf(pFile, "%f",&drainageDepthM);
				fscanf(pFile, "%f",&spaceDrain);
				fscanf(pFile, "%f",&dDrain);
				fscanf(pFile, "%f",&reDrain);
				fscanf(pFile, "%d",&LRA1);
				fscanf(pFile, "%f",&aCurve);
				fscanf(pFile, "%f",&bCurve);
				fscanf(pFile, "%d",&waterOut);
				fscanf(pFile, "%f",&keDrainM);
				fscanf(pFile, "%f",&evapMulti);
				fscanf(pFile, "%f",&snowmeltMulti);
				fscanf(pFile, "%f",&maxNO3F);	
				fscanf(pFile, "%f",&moveN);
				fscanf(pFile, "%f",&partitN);
				fscanf(pFile, "%f",&NLeachF);
				fclose (pFile);
*/				
/*
				int T1[17];
				int T2[17];
				float cM[17];
				int cy[17];
				int cs[17];

				CString TESTFILE1;
				FILE *pFile1=NULL;
				TESTFILE1.Format("%s\\Record\\TileIrrigation.txt", OUTPUT);
				pFile1 = fopen (TESTFILE1,"r");
				
				fscanf(pFile1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&T1[1],&T1[2],&T1[3],&T1[4],&T1[5],&T1[6],&T1[7],&T1[8],&T1[9],&T1[10],&T1[11],&T1[12],&T1[13],&T1[14],&T1[15],&T1[16]);
				fscanf(pFile1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&T2[1],&T2[2],&T2[3],&T2[4],&T2[5],&T2[6],&T2[7],&T2[8],&T2[9],&T2[10],&T2[11],&T2[12],&T2[13],&T2[14],&T2[15],&T2[16]);
				fscanf(pFile1, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",&cM[1],&cM[2],&cM[3],&cM[4],&cM[5],&cM[6],&cM[7],&cM[8],&cM[9],&cM[10],&cM[11],&cM[12],&cM[13],&cM[14],&cM[15],&cM[16]);
				fscanf(pFile1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&cy[1],&cy[2],&cy[3],&cy[4],&cy[5],&cy[6],&cy[7],&cy[8],&cy[9],&cy[10],&cy[11],&cy[12],&cy[13],&cy[14],&cy[15],&cy[16]);
				fscanf(pFile1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&cs[1],&cs[2],&cs[3],&cs[4],&cs[5],&cs[6],&cs[7],&cs[8],&cs[9],&cs[10],&cs[11],&cs[12],&cs[13],&cs[14],&cs[15],&cs[16]);
				fclose (pFile1);

TileIrri=T1[year];
TileIrriDays=T2[year];
controlledDrainageDepthM=cM[year];
controlledDrainageStartDay=cy[year];
controlledDrainageDays=cs[year];
*/
/*



				fscanf(pFile1, "%d",&TileIrri);
				fscanf(pFile1, "%d",&TileIrriDays);
				fscanf(pFile1, "%f",&controlledDrainageDepthM);
				fscanf(pFile1, "%d",&controlledDrainageStartDay);
				fscanf(pFile1, "%d",&controlledDrainageDays);


				fclose (pFile1);
*/				


				///pay attention for other modificaitons.......................................
				    



    if (MODE==0||MonteCarlo==1)
    {
		sprintf(SOIL_YEAR, "%s\\Inputs\\soil-%d", OUTPUT, year);
    }
    else
    {
		if(SoilYear==999) sprintf(SOIL_YEAR, "%s\\Inputs\\soil-A", OUTPUT);
		else
		{
			if(SoilYear==1||SoilYear==0)
				sprintf(SOIL_YEAR, "%s\\Inputs\\soil-A%d", OUTPUT, year);
			else
				sprintf(SOIL_YEAR, "%s\\Inputs\\soil-B%d", OUTPUT, year);
		}
    }


	/*
		CString TESTFILE1;
		FILE *pFile1=NULL;
		TESTFILE1.Format("%s\\Record\\spinupFlag.txt", OUTPUT);
		pFile1 = fopen (TESTFILE1,"r");
		fscanf(pFile1, "%d %d",&spinup,&cropSpin);
		fclose (pFile1);
*/
		if(SoilReset==1&&year>10)//&& cropSpin==1
		{
		sprintf(SOIL_YEAR, "%s\\Inputs\\soil-10", OUTPUT);//Brian initialize with spinup-value
		}
			

		
		if(SoilSpinUp>0)
			{
				if(SoilSpinUpYears==SoilSpinUpCounter)
				{
				SoilSpinUpCounter=0;
				}
				if(SoilSpinUpCounter==0)
				{
					sprintf(SOIL_YEAR, "%s", SoilSpinUpFileName);//Brian initialize with spinup-value	
				}
				if (year == 1 && jdseed[1] == jday)
				{
					sprintf(SOIL_YEAR, "%s", SoilSpinUpFileName);//Brian initialize with spinup-value	
				}
				SoilSpinUpCounter+=1;

			}
			

    fp = fopen(SOIL_YEAR, "r");
    if ( fp == NULL ) note(0, SOIL_YEAR);//reading the soil-1 etc parameters.
	
    fscanf(fp, "%d", &st[1]);
    fscanf(fp, "%s", soil);
    fscanf(fp, "%f %f %f %f %f %f %f %f", &clay[1], &sts[1], &sks[1], &ini_fldcap,&wiltpt[1],&LateralInflux,&jf,&jf);
    fscanf(fp, "%f %f %d %f %f %f %f %f %f", 
		&sd[1], &soil_ph[1], &idc, &ini_ttoo[1], &ini_no3, &ini_nh4, &resoc, &ahsoc, &phsoc);//residue fraction resoc, ahsoc humads fraction, phsoc fraction
    fscanf(fp, "%f %f %f %f %f %d", &byp, &h[1], &th, &mmm[1], &vvv[1], &q);		
    fscanf(fp, "%f %f %f %f %d", &clay_f1, &clay_f2, &qstar, &by_passf, &retard);
    fscanf(fp, "%f %f %f %f %f %f", &rcnb, &rcnh, &rcnm, &rcnrvl, &rcnrl, &rcnrr);//might have to sneak in waterpool BD here somewhere?
	fscanf(fp, "%f %f %f %f %f %f", &leaf_water, &surf_water, &snow_pack, &stub1, &stub2, &stub3);
    fscanf(fp, "%f %f %f", &PassiveCCN, &jf, &jf);

	ini_snow_pack=snow_pack;//brian
	ini_surf_water=surf_water;//brian

	/*
	//insert saxton pedotransfer function needs to be read in twice
	float  sandFraction, soilOM, surfaceSOC, newFC, newWP;
	float sandContent[13] = { 0.0,0.85,0.80,0.63,0.15,0.41,0.53,0.09,0.29,0.52,0.08,0.13,0.15 };
	if (st[1] <= 12) { sandFraction = sandContent[st[1]]; }
	else
	{
		sandFraction = 0.15;
	}
	soilOM = ini_ttoo[1] * 100 * 1.72; //calculate OM%

	float PredMois1500, PredMois1500Adj, PredMois33, PredMois33Adj, poroMois33, poroMois33Adj, satPoro33, satSandAdj, satSandAdj2, denwOM, denwComp, poroOMCompact, poroDelComp, mois33wComp, poroMois33wComp, Lambda, GravelRed, SatCond;
	PredMois1500 = -0.024 * sandFraction + 0.487 * clay[1] + 0.006 * soilOM + 0.005 * clay[1] * soilOM - 0.013 * clay[1] * soilOM + 0.068 * sandFraction * clay[1] + 0.031;
	PredMois1500Adj = PredMois1500 + 0.14 * PredMois1500 - 0.02;
	PredMois33 = -0.251 * sandFraction + 0.195 * clay[1] + 0.011 * soilOM + 0.006 * sandFraction * soilOM - 0.027 * clay[1] * soilOM + 0.462 * sandFraction * clay[1] + 0.299;
	PredMois33Adj = PredMois33 + (1.283 * PredMois33 * PredMois33 - 0.374 * PredMois33 - 0.015);
	poroMois33 = 0.278 * sandFraction + 0.034 * clay[1] + 0.022 * soilOM - 0.018 * sandFraction * soilOM - 0.027 * clay[1] * soilOM - 0.584 * sandFraction * clay[1] + 0.078;
	poroMois33Adj = poroMois33 + (0.636 * poroMois33 - 0.107);
	satPoro33 = poroMois33Adj + PredMois33Adj;
	satSandAdj = -0.097 * sandFraction + 0.043;
	satSandAdj2 = satSandAdj + satPoro33;
	denwOM = (1 - satSandAdj2) * 2.65;
	denwComp = denwOM * 1.00;
	poroOMCompact = 1 - (denwComp / 2.65);
	poroDelComp = (1 - denwComp / 2.65) - (1 - denwOM / 2.65);
	mois33wComp = PredMois33Adj + 0.2 * poroDelComp;
	poroMois33wComp = poroOMCompact - mois33wComp;
	Lambda = (log(mois33wComp) - log(PredMois1500Adj)) / (log(1500) - log(33));
	GravelRed = 1.0;
	SatCond = (1930 * pow(((poroMois33wComp)), ((3 - Lambda) * GravelRed))) / 1000;//satConductivity m/hr for comparison to sks[1]//Equations developed by Dr. Keith Saxton, 10 -15-04: Added 33 Comp, gravel, salinity
	//end saxton Pedotransfer Function
	*/

/*
//cropspin

	
	if(cropSpin==1)
	{cropSpin=0;

		CString TESTFILE;
		FILE *pFile=NULL;
		TESTFILE.Format("%s\\Record\\spinupFlag.txt", OUTPUT);
		pFile = fopen (TESTFILE,"w");
		fprintf(pFile, "%1d %1d\n",spinup,cropSpin);
		fclose (pFile);
	}
	else if(cropSpin==0)
	{
		
	cropSpin=1;

		CString TESTFILE;
		FILE *pFile=NULL;
		TESTFILE.Format("%s\\Record\\spinupFlag.txt", OUTPUT);
		pFile = fopen (TESTFILE,"w");
		fprintf(pFile, "%1d %1d\n",spinup,cropSpin);
		fclose (pFile);
	}
//cropspin
*/

	if(Option>100&&year==1)
	{
		clay[1] *= (1.0 + SMC[6]);
		sd[1] *= (1.0 + SMC[7]);
		sks[1] *= (1.0 + SMC[8]);
		ini_fldcap *= (1.0 + SMC[9]);
		wiltpt[1] *= (1.0 + SMC[10]);
		sts[1] *= (1.0 + SMC[11]);
		ini_ttoo[1] *= (1.0 + SMC[12]);
		ini_no3 *= (1.0 + SMC[15]);
		ini_nh4 *= (1.0 + SMC[16]);
		soil_ph[1] *= (1.0 + SMC[17]);

		clay[1] = min(0.8, clay[1]);
		ini_fldcap = min(0.8, ini_fldcap);
		wiltpt[1] = min(0.6, wiltpt[1]);
		sts[1] = min(0.8, sts[1]);
		ini_ttoo[1] = min(0.8, ini_ttoo[1]);
		soil_ph[1] = min(11.0, soil_ph[1]);
		
		fldcap[1] = ini_fldcap;
	}

//	WaterPoolMax = 0.4 * (ini_fldcap+wiltpt[1])*(1.0 - th) * sts[1];//0.1

	if(year==1 && SoilSpinUp==0 )//&&IniYr==1) //|| year==1 && SoilSpinUpYears>1
	{	
		fscanf(fp, "%f", &BaseMicroIndex); //microbial index	
		fscanf(fp, "%f", &MaxWTDepth);//m
		fscanf(fp, "%f %f", &sslope, &salinity);
		fscanf(fp, "%f", &jf); 
		fscanf(fp, "%f", &jf); 
		fscanf(fp, "%f %f", &SOCa, &SOCb);
		fscanf(fp, "%f %f %f %f %f %f %f %f %f", &rcvl[1], &rcl[1], &rcr[1], 
			&ocini[1], &dphum[1], &no2[1], &no3[1], &nh4[1], &clay_nh4[1]);
		fscanf(fp, "%f", &temp[1]);
		fscanf(fp, "%f", &DrainEfficiency);if(DrainEfficiency==1){MaxWTDepth=2.5;}else {MaxWTDepth=2.0;}
		fscanf(fp, "%d", &SCSuse);
		fscanf(fp, "%f", &inert_C[1]);
		fscanf(fp, "%f", &DClitter);
		fscanf(fp, "%f", &DChumads);
		fscanf(fp, "%f", &DChumus);
		fscanf(fp, "%f", &rcnh);
		fscanf(fp, "%f", &rcnm);
		fscanf(fp, "%f", &waterpoolbd);
		//put fscanf for wpbd
	//	MaxDeepPerc=MaxDeepPerc/1000;
//		DeepPerc=max(0.0, min(1.0, DeepPerc));
		WaterRetentionDepth=9.99;//brian was 9.99 MaxWTDepth
		float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;//! soil bulk density (kg/dm3)
		waterpoolbd=min(2.0,max(1.0,waterpoolbd));

WaterPoolMax = 1.0*(ini_fldcap-wiltpt[1])*(waterpoolbd - th) * sts[1];//*bulk_density/waterpoolbd;//50 cm
WaterPoolMax=0.0;
//WaterPoolMax = 1.0*(ini_fldcap-wiltpt[1])*(1.0) * sts[1]*bulk_density/waterpoolbd;1 metre
if(waterpoolbd<=0)WaterPoolMax=0.0;
//WaterPoolMax = 0.4 * (ini_fldcap+wiltpt[1])*(1.0 - th) * sts[1];
		
		
		fscanf(fp, "%d", &soilProfileType);

		//fgets(tmp,230,fp);//copied the code for the climate Name reading don't fully understand.
		//EraseFBSpace(tmp);
		//soilProfileName=tmp;//set the file name to IData.ProfileFileName

		if (soilProfileType == 1)
		{
			fscanf(fp, "%s", &soilProfileName);
			fscanf(fp, "%d", &homoWaterFlow);
		}
		else
		{
			fscanf(fp, "%d", &jf);
			fscanf(fp, "%d", &homoWaterFlow);
		}
		//new code for soil profile
		if(soilProfileType==1)
		{
		float depthProf,junk;
		float layerD,pBulkD,pSOC,pFieldC,pWiltingP,pPorosity,pPH,pKSat,pClayF,bottomDepth,topDepth;
		int numLayerProf,profileNum,pTexture,layerNumberTop,layerNumberBottom;
		topDepth=0.0;
		bottomDepth=0.0;







// read soilFile heterogenous ----------------------------------------------------		
		FILE *soilFile=NULL;

		soilFile = fopen(soilProfileName, "r");
		if(soilFile==NULL) note(1,soilProfileName);
		
		fscanf(soilFile,"%f %d",&depthProf,&numLayerProf);
			for(int pp=1;pp<=numLayerProf;pp++)
			{
			fscanf(soilFile	,"%d %f %f %f %d %f %f %f %f %f %f",&profileNum,&layerD,&pBulkD,&pSOC,&pTexture,&pPH,&pFieldC,&pWiltingP,&pPorosity,&pKSat,&pClayF);
			bottomDepth+=layerD;
			if (profileNum == 1)
			{
				layerNumberTop = 1;
			}
			else
			{
				layerNumberTop = (int)(topDepth / h[1] + 2);//calculating Manure_layer;
			}
			layerNumberBottom = (int)(bottomDepth / h[1] + 1);//calculating Manure_layer;
			topDepth+=layerD;
			
				for(int pz=layerNumberTop;pz<=layerNumberBottom;pz++)
				{
				sd[pz]=pBulkD;
					fldcap[pz]=pFieldC;
					fldcapOLD[pz]=pFieldC;
					wiltpt[pz]=pWiltingP;
					sts[pz]=pPorosity;
					clay[pz]=pClayF;
					st[pz]=pTexture;
					sks[pz]=pKSat;
					Tttoo[pz]=pSOC;
					mmm[pz] = sd[pz] * 1000.0 * h[1] * 10000.0;
					soil_ph[pz] = pPH;//set pH
					
				}


			}
			ini_fldcap=fldcap[1];
		fclose(soilFile);
		}
		rcnb=rcnh;
		day_WT=-MaxWTDepth;

	//	if (LandUse == 2) WTL = -1;
	//	day_WT = -WaterRetentionDepth;//brian was this
		//Odoc[1] = 0.0 * ocini[1];
		OrgP[1] = 4.0;
		LabP[1] = 1.0;
		AdsP[1] = 1.0;//kg P/kg soil/layer
		fldcap[1] = ini_fldcap;
		DrainEfficiency = min(1.0, max(0.0, DrainEfficiency));
		
		if(Option>100)
		{
			SOCa *= (1.0 + SMC[44]);
			SOCb *= (1.0 + SMC[45]);
			rcvl[1] *= (1.0 + SMC[12]);
			rcl[1] *= (1.0 + SMC[12]);
			rcr[1] *= (1.0 + SMC[12]);
			ocini[1] *= (1.0 + SMC[12]);
			dphum[1] *= (1.0 + SMC[12]);
			inert_C[1] *= (1.0 + SMC[12]);
			no3[1] *= (1.0 + SMC[15]);
			nh4[1] *= (1.0 + SMC[16]);
			clay_nh4[1] *= (1.0 + SMC[16]);
		}

		soc[1] = rcvl[1]+rcl[1]+rcr[1]+ocini[1]+dphum[1]+inert_C[1];
		
		if (soilProfileType == 0)
		{
			Tttoo[1] = soc[1] / mmm[1];			//should only be in case of soilProfile==0
		}
		//sdx  = Tttoo[1] / 0.58 * 100.0;// kg SOC/kg soil -> SOM %
		//sd[1]  = (sdK2 * sdK1 / (sdx/100.0 * sdK2 + (1.0 - sdx/100.0) * sdK1));// developed by C. Li

		no[1]=0.0;
		n2o[1]=0.0;
		n2[1]=0.0;
		urea[1]=0.0;
		nh3[1]=0.0;
		doc[1]=0.0;
		ManureDays = 0;
		salinity=0.0;

		T_SOC = 0.0;
		old_T_SOC = 0.0;
		C_soil = 0.0;

		for (int is=1; is <= q; is++ )  h[is] = h[1];
		
		IniProfWater = 0.0;
		IniSP = 0.0;

		for (int i=1; i <= q; i++ ) 
		{
			int ji = (int)(SOCa/h[1]);//saying the first 20cm is homogenous.

			if(soilProfileType==1)
			{
				ji = 1;//this is so that it doesn't recalculate rcvl for the top 20cm
			}

			if (i <= ji)
			{
 				rcvl[i]    = rcvl[1];
				rcl[i]	   = rcl[1];
				rcr[i]	   = rcr[1];
				rcr[i] = Tttoo[1] * resoc * mmm[1];
				ocini[i]   = ocini[1];
				ocini[i] = Tttoo[1] * ahsoc * mmm[1];
				dphum[i]   = dphum[1]; //should be OC% * humus%* mass of soil
				dphum[i] = Tttoo[1] * phsoc *mmm[1];
				inert_C[i]   = inert_C[1];
				no3[i]   = no3[1];
				nh4[i]   = nh4[1];
				clay_nh4[i] = clay_nh4[1];
				urea[i]   = urea[1];
				nh3[i]     = nh3[1];
				no2[i] = no2[1];
				no[i] = no[1];
				n2o[i] = n2o[1];
				n2[i] = n2[1];					
				doc[i] = doc[1];
				//doc[i] = ocini[i] * 0.001;
				AdsP[i] = AdsP[1];
				OrgP[i] = OrgP[1];
				LabP[i] = LabP[1];
			}
			else 
			{
				float dt;
				if(SOCb>=1.0) 
					dt = powf(SOCb, ((float)i*h[1] - SOCa)/0.1);
				else
					dt = 1.0 / ((1.0-SOCb) * logf(i-ji) + 1.0);

				if(soilProfileType==1)
				{
					dt=Tttoo[1]/Tttoo[i];//ratio of %carbon in top of the profile to % of that layer.
					dt = (Tttoo[1] * sd[1]) / (Tttoo[i] * sd[i]);
				//	float blah;
				//	blah=1.0;
				}


					rcvl[i]    = rcvl[1]/dt;
					rcl[i]	   = rcl[1]/dt;
					rcr[i]	   = rcr[1]/dt;
					ocini[i]   = ocini[1]/dt;
					dphum[i]   = dphum[1]/dt;
				//	dphum[i] = Tttoo[i] * phsoc * mmm[i];
					inert_C[i]   = inert_C[1]/dt;
					no3[i]   = no3[1]/dt;
					nh4[i]   = nh4[1]/dt;
					clay_nh4[i] = clay_nh4[(int)(SOCa/h[1])];
					urea[i]   = urea[1]/dt;
					nh3[i]     = nh3[1]/dt;
					no2[i] = no2[1]/dt;
					no[i] = no[1]/dt;
					n2o[i] = n2o[1]/dt;
					n2[i] = n2[1]/dt;										
					doc[i] = doc[1]/dt;
					AdsP[i] = AdsP[1]/dt;
					OrgP[i] = OrgP[1]/dt;
					LabP[i] = LabP[1]/dt;
					//doc[i]   = doc[1]/dt;
					//ttoo[i] = ttoo[1]/dt;
			}

			
			soc[i] = rcvl[i]+rcl[i]+rcr[i]+ocini[i]+dphum[i]+doc[i]+inert_C[i];
			
			if (soilProfileType == 0)
			{
				mmm[i] = mmm[1];
				ini_ttoo[i] = soc[i] / mmm[i];
				Tttoo[i] = soc[i] / mmm[i];
			}
			else
			{
				ini_ttoo[i] = Tttoo[i];
			}
			///////////////////////////
			double CRB, Thc;		
			CRB = RBO * ocini[i];		
			CRB1[i] = CRB * SRB;
			CRB2[i] = CRB * (1.0 - SRB);
			Thc = ocini[i] - CRB;
			crhl[i] = Thc * srh;
			crhr[i] = Thc - crhl[i];
			///////////////////////////////////
			
			FreezeDOC[i]=0.0;
						
			LayerDepth += h[1];
			SoilDepth[i] = LayerDepth;
			h[i] = h[1];
			
			

			

			if(soilProfileType==0)
			{
			sts[i] = sts[1];//Brian turned off so I could use profile
			wiltpt[i] = wiltpt[1];
			fldcap[i] = fldcap[1];
			fldcapOLD[i]=fldcap[1];
			clay[i] = clay[1];
			st[i] = st[1];
			sks[i] = sks[1];
			
			if (homoWaterFlow == 1)
			{
				sks[5] = 0.001145;
			}
			
			soil_ph[i] = soil_ph[1];//when only single pH for non soil profile
			}
			//soil_ph[i] = soil_ph[1];//was this
			//sd[i] = sd[1];
			
			
			//mmm[i] = mmm[1];
			vvv[i] = vvv[1];
			
			ice[i] = 0.0;
			Eh[i]=600.0;
			//inert_C[i]=0.0;
			float DeepT = yr_avetj + 0.0;
			temp[i] = temp[1] / (float)i + 10.0 * DeepT / (float)(q-i+1);
			hourlyTemp[i] = temp[1] / (float)i + 10.0 * DeepT / (float)(q-i+1);
			
			sksHydro[i]=sks[1];//Brian added for water physics

			
			Mn4[i] = default_Mn;
			Fe3[i] = default_Fe;
			SO4[i] = default_SO4;
			//old_AdsP[i] = AdsP[i];

			soc[i] = rcvl[i]+rcl[i]+rcr[i]+ocini[i]+dphum[i]+inert_C[i];
			if (soilProfileType == 0)
			{
				Tttoo[i] = soc[i] / mmm[i];
			}
			
			sdx  = Tttoo[i] / 0.58 * 100.0;// kg SOC/kg soil -> SOM %
			

			//T_SOC += soc[i];
			//old_T_SOC += soc[i]; 

			//sts[i] - porosity
			//Based on Hudson, 1994, J Soil and Water Cons. 49(2):189-194
			//AWC = 6.4 + 2.9 * OM;
			//AWC - FieldCapacity - WiltPoint (% water by volume)
			//OM - % SOM by weight

			//sdx  = Tttoo[i] / 0.58 * 100.0;// kg SOC/kg soil -> SOM %
			
			//fldcap[i] = ini_fldcap * (0.00005 * soc[i] + 0.7426);
			if(soilProfileType==0)//batch??
			{
			sd[i] = (sdK2 * sdK1 / (sdx / 100.0 * sdK2 + (1.0 - sdx / 100.0) * sdK1));// developed by C. Li  //was being calculated outside of this loop
			fldcap[i] = ini_fldcap - 2.9 / sts[i] * (ini_ttoo[i] - Tttoo[i]);
			fldcap[i] = min(0.9, max(wiltpt[i], fldcap[i]));
			fldcapOLD[i]=fldcap[i];
			}
			if(SoilStructEffect==1.0)
			{
			fldcap[1]=ini_fldcap;//enable for saxton
			
			}


			if(st[i]>12) day_wfps[i] = fldcap[i];//(fldcap[i]+wiltpt[i])*0.5;
			else day_wfps[i] = fldcap[i];//(fldcap[i]+wiltpt[i])*0.5;
			water[1][i] = day_wfps[i]*h[i] * sts[i];
			IniProfWater += water[1][i];//m water

			wrcvl += rcvl[i]; wrcl += rcl[i]; wrcr += rcr[i]; wcrb += (CRB1[i]+CRB2[i]); wcrhl += crhl[i]; wcrhr += crhr[i]; 
			whumus += dphum[i]; 
			
			wtcavai += doc[i]; 
			
			winertC += inert_C[i]; wFreezedoc += FreezeDOC[i];

			w_n2o += n2o[i]; w_n2 += n2[i]; w_nh3 += nh3[i]; w_no3 += no3[i];
			w_nh4 += nh4[i]; wurea += urea[i]; day_clay_N += clay_nh4[i]; wpool_no += no[i]; 

			IniSP += (AdsP[i]+OrgP[i]+LabP[i]);
		}
		
		WaterPool = WaterPoolMax;
		WaterPool =0.0;//brian Waterpool for water table	
		IniWaterPool = WaterPool;
		//////////////////////////////////////////////////////////////////////////////////////
	}//end of if(year==1)
	else// if(year>1)
	{
		//////////////////////////////////////////////////////////////////////////////////////
		
		IniProfWater = 0.0;
		IniSP = 0.0;
		
		for (int i=1; i <= q; i++ )
		{			
			fscanf(fp, "%f %f %f", &rcvl[i], &rcl[i], &rcr[i]);
			fscanf(fp, "%f %f %f %f %f", &CRB1[i], &CRB2[i], &crhl[i], &crhr[i], &dphum[i]);
			fscanf(fp, "%f %f %f %f %f %f", &no2[i], &no3[i], &nh4[i], &clay_nh4[i], &urea[i], &nh3[i]);
			fscanf(fp, "%f %f %f", &no[i], &n2o[i],  &n2[i]);
			fscanf(fp, "%f %f %f", &temp[i], &day_wfps[i], &ice[i]);
			fscanf(fp, "%f %f", &Eh[i], &ch4[i]);
			fscanf(fp, "%f %f %f %f", &FreezeDOC[i], &F_methanogen[i], &jf, &jf);
			fscanf(fp, "%f %f", &inert_C[i], &doc[i]);

			fscanf(fp, "%d %f %f %f", &st[i], &h[i], &SoilDepth[i], &ini_ttoo[i]);
			fscanf(fp, "%f %f %f %f %f %f %f %f", &sts[i], &clay[i], &ini_fldcap, &wiltpt[i], &sd[i], &soil_ph[i], &fldcap[i],&fldcapOLD[i]);//brian &ini_fldcap
			fscanf(fp, "%f %f %f", &mmm[i], &vvv[i], &sks[i]);
			fscanf(fp, "%f %f %f", &Fe3[i], &Mn4[i], &SO4[i]);
			fscanf(fp, "%f %f %f %f", &OrgP[i], &AdsP[i], &LabP[i], &ch4_doc_pool[i]);
			fscanf(fp, "%f", &manurePool[i]);

			ocini[i] = CRB1[i] + CRB2[i] + crhl[i] + crhr[i];

			soc[i] = rcvl[i]+rcl[i]+rcr[i]+ocini[i]+dphum[i]+inert_C[i];//+FreezeDOC[i];

			Tttoo[i] = soc[i] / mmm[1];			
			sdx  = Tttoo[i] / 0.58 * 100.0;// kg SOC/kg soil -> SOM %
			sd[i]  = (sdK2 * sdK1 / (sdx/100.0 * sdK2 + (1.0 - sdx/100.0) * sdK1));// developed by C. Li
	
			//old_T_SOC += soc[i];
			water[1][i] = day_wfps[i]*h[i] * sts[i];
			IniProfWater += water[1][i];//m water
		
			float rbo = 0.015 * 0.5 + 0.00001;
			float CRB = ocini[i] * rbo + 0.00001;
			CRB1[i] = CRB * SRB;
			CRB2[i] = CRB * (1.0 - SRB);
			float AHM = ocini[i] - CRB;
			if(AHM<=0.0) AHM = 0.0000001;
			crhl[i] = AHM * srh;
			crhr[i] = AHM * (1.0 - srh);

			//wcrb += (CRB1[i]+CRB2[i]);

			//Mn4[i] = default_Mn;
			//Fe3[i] = default_Fe;
			//SO4[i] = default_SO4;
			
			SoilDepth[i] = i * h[i];


			//li code
			//fldcap[i] = ini_fldcap * (0.5 * soc[i] + 0.7426);//(0.00005 * soc[i] + 0.7426);
			//fldcap[i] = min(0.9, max(ini_fldcap, fldcap[i]));
				
			

			//insert saxton pedotransfer function
			/*
			float  sandFraction,soilOM, surfaceSOC, newFC, newWP;
			float sandContent[13] = { 0.0,0.85,0.80,0.63,0.15,0.41,0.53,0.09,0.29,0.52,0.08,0.13,0.15 };
			if (st[1] <= 12) { sandFraction = sandContent[st[1]]; }
			else
			{
				sandFraction = 0.15;
			}
			soilOM = ini_ttoo[1] * 100 * 1.72; //calculate OM%

			float PredMois1500,PredMois1500Adj,PredMois33,PredMois33Adj,poroMois33, poroMois33Adj,satPoro33,satSandAdj,satSandAdj2,denwOM,denwComp,poroOMCompact,poroDelComp,mois33wComp,poroMois33wComp,Lambda,GravelRed,SatCond;
			PredMois1500 = -0.024 * sandFraction + 0.487 * clay[1] + 0.006 * soilOM + 0.005 * clay[1] * soilOM - 0.013 * clay[1] * soilOM + 0.068 * sandFraction * clay[1] + 0.031;
			PredMois1500Adj = PredMois1500 + 0.14 * PredMois1500 - 0.02;
			PredMois33 = -0.251 * sandFraction + 0.195 * clay[1] + 0.011 * soilOM + 0.006 * sandFraction * soilOM - 0.027 * clay[1] * soilOM + 0.462 * sandFraction * clay[1] + 0.299;
			PredMois33Adj = PredMois33 + (1.283 * PredMois33 * PredMois33 - 0.374 * PredMois33 - 0.015);
			poroMois33 = 0.278 * sandFraction + 0.034 * clay[1] + 0.022 * soilOM - 0.018 * sandFraction * soilOM - 0.027 * clay[1] * soilOM - 0.584 * sandFraction * clay[1] + 0.078;
			poroMois33Adj = poroMois33 + (0.636 * poroMois33 - 0.107);
			satPoro33 = poroMois33Adj + PredMois33Adj;
			satSandAdj = -0.097 * sandFraction + 0.043;
			satSandAdj2 = satSandAdj + satPoro33;
			denwOM = (1 - satSandAdj2) * 2.65;
			denwComp = denwOM * 1.00;
			poroOMCompact = 1 - (denwComp / 2.65);
			poroDelComp = (1 - denwComp / 2.65) - (1 - denwOM / 2.65);
			mois33wComp = PredMois33Adj + 0.2 * poroDelComp;
			poroMois33wComp = poroOMCompact - mois33wComp;
			Lambda = (log(mois33wComp) - log(PredMois1500Adj)) / (log(1500) - log(33));
			GravelRed = 1.0;
			SatCond = (1930*pow(((poroMois33wComp)), ((3 - Lambda) * GravelRed)))/1000;//satConductivity m/hr for comparison to sks[1]//Equations developed by Dr. Keith Saxton, 10 -15-04: Added 33 Comp, gravel, salinity
			*/
			//end saxton Pedotransfer Function
		






/*

			//insert saxton pedotransfer function
			
					
						float sandContent,soilOM,surfaceSOC,newFC,newWP;
						float relWP, relFC;
							
						if(st[1]==1)
						{sandContent=0.85;}
						else if(st[1]==2)
						{sandContent=0.80;}
						else if(st[1]==3)
						{sandContent=0.63;}
						else if(st[1]==4)
						{sandContent=0.15;}
						else if(st[1]==5)
						{sandContent=0.41;}
						else if(st[1]==6)
						{sandContent=0.53;}
						else if(st[1]==7)
						{sandContent=0.09;}
						else if(st[1]==8)
						{sandContent=0.29;}
						else if(st[1]==9)
						{sandContent=0.52;}
						else if(st[1]==10)
						{sandContent=0.08;}
						else if(st[1]==11)
						{sandContent=0.13;}
						else
						{sandContent=0.15;}

						soilOM=ini_ttoo[1]*100*1.72; //calculate OM%

						surfaceSOC=soc[1]+soc[2]+soc[3];//calculate surface SOC
						float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;//! soil bulk density (kg/dm3)
						soilOM=(surfaceSOC/10000/bulk_density/20)*100*1.72;


						newWP=-0.024*sandContent+0.487*clay[1]+0.006*soilOM+0.005*sandContent*soilOM-0.013*clay[1]*soilOM+0.068*sandContent*clay[1]+0.031;
						//newWP=-0.024*sandContent+0.487*clay[1]+0.006*soilOM+0.005*sandContent*soilOM-0.013*clay[1]*soilOM+0.068*sandContent*clay[1]+0.031;
						newWP=(newWP+0.14*newWP-0.02)/sts[1];
						//newFC=-0.251*sandContent+0.195*clay[1]+0.049*soilOM+0.006*sandContent*soilOM-0.027*clay[1]*soilOM+0.452*sandContent*clay[1]+0.299;
						newFC=-0.251*sandContent+0.195*clay[1]+0.011*soilOM+0.006*sandContent*soilOM-0.027*clay[1]*soilOM+0.452*sandContent*clay[1]+0.299;
						newFC=(newFC+(1.283*newFC*newFC-0.374*newFC-0.015))/sts[1];
						if(oldWP<0||oldFC<0)
							{
							relWP=1.0;
							relFC=1.0;
							oldWP=newWP;
							oldFC=newFC;
							}
						else
						{
							relWP=newWP/oldWP;
							relFC=newFC/oldFC;
							
							if(relWP>1.0 || relFC>1.0)
								{
								relWP=pow(relWP,1);
								relFC=pow(relFC,2.0);//2.2
								}
							else
								{
								relWP=pow(relWP,1);
								relFC=pow(relFC,2.0);
								}

							//added year==1 to the field capacity depth allocation. In data I assigned in the fldcap[l] when it was just assigning in just at depth....note this is the problem!!!


							
							oldWP=newWP;
							oldFC=newFC;
							WaterPoolMax*=relFC;
						}
					
			
						
					
						//fc wp
						if(wiltpt[1]*relWP<.8)
						{
						wiltpt[1]=wiltpt[1]*relWP;
						}
						if(fldcap[1]*relFC<.99 && (fldcap[1]*relFC)>(wiltpt[1]+0.1))
						{
						fldcap[1]=fldcap[1]*relFC;
						ini_fldcap=ini_fldcap*relFC;
						}
						//end fc wp
						
				//end new saxton code
				*/

			//li code for tuning field capacity
			if(soilProfileType==0&&year==1)//Brian added year==1  //soilProfileType isn't read until further down. Only doing this if the first year
			{
			fldcap[i] = ini_fldcap - 2.9 / sts[i] * (ini_ttoo[i] - Tttoo[i]);
			fldcap[i] = min(0.9, max(wiltpt[i], fldcap[i]));
			fldcapOLD[i]=fldcap[i];

		//	sks[5] = 0.000080;
			}
						if(SoilStructEffect==1.0)
			{
			fldcap[1]=ini_fldcap; //enable for saxton
						}
			wrcvl += rcvl[i]; wrcl += rcl[i]; wrcr += rcr[i]; wcrb += (CRB1[i]+CRB2[i]); wcrhl += crhl[i]; wcrhr += crhr[i]; 
			whumus += dphum[i]; 
			manPoolTot += manurePool[i];//accumulating manurePool across layers.
			
			wtcavai += doc[i]; 
			
			winertC += inert_C[i]; wFreezedoc += FreezeDOC[i];

			w_n2o += n2o[i]; w_n2 += n2[i]; w_nh3 += nh3[i]; w_no3 += no3[i];
			w_nh4 += nh4[i]; wurea += urea[i]; day_clay_N += clay_nh4[i]; wpool_no += no[i]; 

			 
			IniSP += (AdsP[i]+OrgP[i]+LabP[i]);

		}

		fscanf(fp, "%f", &BaseMicroIndex); //microbial index	
		fscanf(fp, "%f", &MaxWTDepth);//m
		fscanf(fp, "%f %f", &sslope, &salinity);
		fscanf(fp, "%f", &WaterPool); //water storage in deep layer
		fscanf(fp, "%d", &ManureDays);
		fscanf(fp, "%f", &day_WT); 
		fscanf(fp, "%d %d", &flood_flag, &FloDays);
		fscanf(fp, "%f", &DrainEfficiency);if(DrainEfficiency==1){MaxWTDepth=2.5;}else {MaxWTDepth=2.0;}
		fscanf(fp, "%d", &SCSuse);
		fscanf(fp, "%f", &PassiveC);
		fscanf(fp, "%f", &DClitter);
		fscanf(fp, "%f", &DChumads);
		fscanf(fp, "%f", &DChumus);
		fscanf(fp, "%f %f %f", &remain_root, &FineRootCN, &jf); //, &fine_root_pool[1]
		fscanf(fp, "%f %f", &frost_doc, &C_soil); 
		fscanf(fp, "%f %f %f %f %f %f %f", &DayFixFert1,&DayFixFert2,&DayFixFert3,&DayFixFert4,&DayFixFert5,&DayFixFert6,&DayFixFert7); 
		fscanf(fp, "%f %f %f %f %f %f %f", &sfer1,&sfer2,&sfer3,&sfer4,&sfer5,&sfer6,&sfer7);
		fscanf(fp, "%d", &UreaAppDays);
		fscanf(fp, "%f", &waterpoolbd);//read in waterpoolBulk Density here. Write out at end of year waterpool bd in DNDC_output
		fscanf(fp, "%d", &soilProfileType);
		if(soilProfileType>0) fscanf(fp, "%s", &soilProfileName);
		fscanf(fp, "%f %f",&oldWP,&oldFC);
		fscanf(fp, "%f",&WaterPoolMax);
		fscanf(fp, "%d",&WTL);
		fscanf(fp, "%d",&nWTL);
		fscanf(fp, "%f", &manurePoolCN);
		fscanf(fp, "%d", &lastFrost);
		fscanf(fp, "%f", &totalManureC);
		fscanf(fp, "%f", &totalManureN);
		fscanf(fp, "%d", &fallFrost1);
		fscanf(fp, "%f", &manPoolRate[1]);
		fscanf(fp, "%f", &TotalFreezeDOC);
		fscanf(fp, "%d", &homoWaterFlow);
	//	MaxDeepPerc=MaxDeepPerc/1000;
		//DeepPerc=max(0.0, min(1.0, DeepPerc));
		WaterRetentionDepth=9.99;//9.99 -day_WT;
		float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;//! soil bulk density (kg/dm3)
		//WaterPoolMax = 1.0*(ini_fldcap-wiltpt[1])*(1.0 - th) * sts[1];
		//WaterPoolMax = 1.0*(ini_fldcap-wiltpt[1])*(1.0 - th) * sts[1]*bulk_density/waterpoolbd;//this one for WaterPool
//		WaterPoolMax = 1.0*(ini_fldcap-wiltpt[1])*(1.0) * sts[1]*bulk_density/waterpoolbd;
		if(waterpoolbd<=0)WaterPoolMax=0.0;//every year after year 1 use this one
	//	WaterPoolMax = 0.4 * (ini_fldcap+wiltpt[1])*(1.0 - th) * sts[1];


		/////////////////////////////////
					if(soilProfileType==1)
					{
					float depthProf,junk;
					float layerD,pBulkD,pSOC,pFieldC,pWiltingP,pPorosity,pPH,pKSat,pClayF,bottomDepth,topDepth;
					int numLayerProf,profileNum,pTexture,layerNumberTop,layerNumberBottom;
					topDepth=0.0;
					bottomDepth=0.0;

					FILE *soilFile=NULL;

					soilFile = fopen(soilProfileName, "r");
					if(soilFile==NULL) note(1,soilProfileName);
					
					fscanf(soilFile,"%f %d",&depthProf,&numLayerProf);
						for(int pp=1;pp<=numLayerProf;pp++)
						{
						fscanf(soilFile	,"%d %f %f %f %d %f %f %f %f %f %f",&profileNum,&layerD,&pBulkD,&pSOC,&pTexture,&pPH,&pFieldC,&pWiltingP,&pPorosity,&pKSat,&pClayF);
						bottomDepth+=layerD;
						if (profileNum == 1)
						{
							layerNumberTop = 1;
						}
						else
						{
							layerNumberTop = (int)(topDepth / h[1] + 2);//calculating Manure_layer;
						}
						layerNumberBottom = (int)(bottomDepth / h[1] + 1);//calculating Manure_layer;
						topDepth+=layerD;
						
							for(int pz=layerNumberTop;pz<=layerNumberBottom;pz++)
							{
							sd[pz]=pBulkD;
								fldcap[pz]=pFieldC;
								fldcapOLD[pz]=fldcap[pz];
								wiltpt[pz]=pWiltingP;
								sts[pz]=pPorosity;
								clay[pz]=pClayF;
								st[pz]=pTexture;
								sks[pz]=pKSat;
								mmm[pz] = sd[pz] * h[1] * 1000.0 * 10000.0;
								Tttoo[pz] = soc[pz] / mmm[pz];
								
							}


						}
						ini_fldcap=fldcap[1];
					fclose(soilFile);
					}

////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////
		IniWaterPool = WaterPool;
		//AdsP[1] = 10.0;//kg P/kg soil	
		DrainEfficiency = min(1.0, max(0.0, DrainEfficiency));
	}
	fclose( fp );	
  
	//ini_deep_doc = deep_doc;

	MicrobioIndex = BaseMicroIndex;

	WRL = (int)(WaterRetentionDepth/h[1])-1;
	WRL=664;
	

	WTL= (int)((-day_WT)/h[1]);//Depth_convert_to_layer(-day_WT, h, q)+1;//(int)(-day_WT/h[1]);
if(year==1 && SoilSpinUp == 0)
{
	nWTL=q; //sets WTL to bottom layer
}
    WTL=nWTL;//Brian nWTL is meant to copy the WTL for pre-transpiration code.
	day_WT=-WTL*h[1];//Brian calculates the effective depth of the water table layer

//	if (LandUse == 2) WTL = -1;//for Rice Paddy systems
	

	surface_litter = 0.0;

		wrnvl = wrcvl/rcnrvl;
		wrnl = wrcl/rcnrl;
		wrnr = wrcr/rcnrr;
		wnrb = wcrb/rcnb;
		wnrhl = wcrhl/rcnh;
		wnrhr = wcrhr/rcnh;
		whumusn = whumus/rcnm;
		InertN = winertC/PassiveCCN;

		wno31 = w_no3;
		wnh41 = w_nh4;
		wnh31 = w_nh3;
		wurea1 = wurea;
		wno1 = wpool_no;
		day_clay_n1 = day_clay_N;
		ini_N_gases = w_n2o + w_n2;
		IniSIN = wno31 + wnh41 + wnh31 + wurea1 + wno1 + day_clay_n1 + ini_N_gases;

		IniLitter = wrcvl + wrcl + wrcr;
		IniActHumus = wcrb + wcrhl + wcrhr;
		IniSOC = IniLitter + IniActHumus + whumus + wtcavai + winertC + wFreezedoc+manPoolTot;//manurePool?
		whumus1 = whumus;

		IniLitterN = wrnvl + wrnl + wrnr;
		IniActHumusN = wnrb + wnrhl + wnrhr;
		IniSON = IniLitterN + IniActHumusN + whumusn + InertN+totalManureN;//adding manurePoolN
		ini_N_gases = w_n2o + w_n2;
		
		//IniSN = w_nh3 + w_no3 + w_nh4 + wurea + day_clay_N + wpool_no + ini_N_gases;
		whumusn1 = whumusn;

	return(0);
}


void class_model::read_in_cropini(int MODE, int GlobeData, CString FCT40)
{    
	int iii, crop_code;
	char F_CROP[80], js[50];
	float BiomassC, MaxLAI, MaxHeight, jf;
	FILE *fp;

	if(year==1&&WinterCropFlag[1]==1)
	{
		BiomassC = GrainYield[1] / grain[1];

		seed[1] = 61;
		plantn[1] = 7.26;
		PlantTakeN[1] = 7.26;
		demandn[1] = 7.26;
		lai[1] = 0.2;
		Leaf_Wt[1] = 169.05;
		Stem_Wt[1] = 197.24;
		Grain_Wt[1] = 0.0;
		Root_Wt[1] = 75.02;
		TDD[1] = 200.01;
		crop_trans[1] = 0.007;
		WinterCropFlag[1] = 1;
		WCLeftDays[1] = 139;
		//GrainYield[1] = BiomassC * grain[1];//3203.2;
		HarvestYear[1] = 1;
		grow_days[1] = 200;
		left_perc[1] = 0.8;

		//maxmn[1] = BiomassC / plantcn[1];//128.6;
		//indi = 111;
		InitialBiomass[1] = 12.5;
		GrowthVegetative[1] = 0.012;
		GrowthReproductive[1] = 0.025;
		PsnEfficiency[1] -= 0.4;
		PsnMax[1] = 60.0;
		CoverCrop[1] = 0;
		//PerennialFlag[1] = 0;
		//grain[1] = 0.41;
		//straw[1] = 0.42;
		//root[1] = 0.71;
		//graincn[1] = 40.0;
		//strawcn[1] = 95.0;
		//rootcn[1] = 95.0;
		//max_TDD[1] = 1300.0;
		//wreq[1] = 300.0;
	//	max_root_length[1] = 1.5;
		//ini_N_fix[1] = 1.0;
		//vascularity[1] = 0.0;	
		Transplant[1] = 0;
		
		crop_flag[1] = 1;
		jdseed[1] = 0;
		lai_index[1] = 1.0;

		if(vascularity[1]<0.0) vascularity[1] = 0.0;

		if(crop[1]==20||crop[1]==64||crop[1]==65) vascularity[1] = 1.0;
		
		if(maxmn[1]<=0.0) 
		{
			plantcn[1] = 0.00001;
			grain[1] = 0.00001;
			leaf[1] = 0.00001;
			stem[1] = 0.00001;
			root[1] = 0.00001;
		}
		else
		{
			//plantcn[1] = (GrainYield[1]/grain[1]) / maxmn[1];
		}

		ini_maxmn[1] = maxmn[1];
		
		/*if(Option>100) 
		{
			GrainYield[1] *= (1.0 + SMC[18]);
			maxmn[1] *= (1.0 + SMC[18]);
			left_perc[1] *= (1.0 + SMC[28]);
		}*/

		if(crop[1]==11||crop[1]==12) GrassFlag[1] = 1;//grass crops
		//if(crop[1]==46) RainfedRice_flag = 1;//rainfed rice

		if(PerennialFlag[1]==1)//perrenial grassland
		{				
			WinterCropFlag[1] = 1;
			HarvestYear[1] = 1;
			jdseed[1] = 1;
			grow_days[1] = 365;
			seed[1] = 1;
			InitialBiomass[1] = 0.0;//kg C/ha
			TDD[1]=0.0;
			PlantTakeN[1]=0.0;
			demandn[1]=0.0;
			crop_trans[1]=0.0;
			ddupn[1] = 0.0;
			Transplant[1]=0;

			if(GlobeData==1)
			{
				plantn[1] = 0.0;
				demandn[1] = 0.0;
				lai[1] = 0.0;
				Leaf_Wt[1] = 0.0;
				Stem_Wt[1] = 0.0;
				Grain_Wt[1] = 0.0;
				Root_Wt[1] = 0.0;
				LeafN[1] = 0.0;
				StemN[1] = 0.0;
				GrainN[1] = 0.0;
				RootN[1] = 0.0;
				DayGrow_LeafN[1]= 0.0;
				DayGrow_StemN[1]= 0.0;
				DayGrow_RootN[1]= 0.0;
				DayGrow_GrainN[1]= 0.0;
			}			
		}
	//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if(crop[1]==11||crop[1]==12)
		{
			seed[1] = 1;
			if(latitude<0.0)
			{
				plantn[1] = 90.0;
				lai[1] = 0.5;
			}
			else
			{
				plantn[1] = 20.0;
				lai[1] = 0.2;
			}
		
			TDD[1]=0.0;
			PlantTakeN[1]=0.0;

			if(GlobeData==1)
			{
				plantn[1] = 0.0;
				demandn[1] = 0.0;
				lai[1] = 0.0;
				Leaf_Wt[1] = 0.0;
				Stem_Wt[1] = 0.0;
				Grain_Wt[1] = 0.0;
				Root_Wt[1] = 0.0;
				LeafN[1] = 0.0;
				StemN[1] = 0.0;
				GrainN[1] = 0.0;
				RootN[1] = 0.0;
				DayGrow_LeafN[1]= 0.0;
				DayGrow_StemN[1]= 0.0;
				DayGrow_RootN[1]= 0.0;
				DayGrow_GrainN[1]= 0.0;
			}
		}
	}
}

void class_model::read_in_crop(int MODE, int GlobeData, CString FCT40)
{
    FILE *fp, *fpp;
	char crop_file[80], F_CROP[200];
    int i, indi, NewCropNumbers, IniCropNumbers, NEWPerennialFlag[8]={0,0}, NEWcrop[8]={0,0};
	float jf;
	///////////////////////////////////////////////////////////////////////////////////////////////
	//Read initial crop status



	sprintf(F_CROP, "%s\\Inputs\\cropini-%d", OUTPUT, year);
	fpp = fopen(F_CROP, "r");
	if(fpp==NULL) note(0, F_CROP);

	fscanf(fpp, "%d", &IniCropNumbers);
	{
		for(int i=1; i<=IniCropNumbers; i++)
		{
			fscanf(fpp, "%d %d %f %f %f %f", &crop[i], &seed[i], &plantn[i], &PlantTakeN[i], &demandn[i], &OptimumT[i]);
			fscanf(fpp, "%f %f %f %f %f", &Leaf_Wt[i], &Stem_Wt[i], &Grain_Wt[i], &Root_Wt[i], &TDD[i]);
			fscanf(fpp, "%f %f", &crop_trans[i], &plantcn[i]);

			fscanf(fpp, "%d %s %d %d %f %d", 
				&crop[i], crop_name[i], &WinterCropFlag[i], &WCLeftDays[i], &GrainYield[i], &HarvestYear[i]);
			fscanf(fpp, "%d %d %f %f %f", 
				&jdseed[i], &grow_days[i], &left_perc[i], &maxmn[i], &base_maxmn[i]);	//&indi		
			fscanf(fpp, "%f %d %f %f %f", 
				   &InitialBiomass[i], &Transplant[i], &PGI[i], &PsnEfficiency[i], &PsnMax[i]);
			fscanf(fpp, "%d", &CoverCrop[i]);
			fscanf(fpp, "%d", &PerennialFlag[i]);
			fscanf(fpp, "%f %f %f %f", &grain[i], &leaf[i], &stem[i], &root[i]);
			fscanf(fpp, "%f %f %f %f", &base_graincn[i], &base_leafcn[i], &base_stemcn[i], &base_rootcn[i]);//Brian
			fscanf(fpp, "%f %f %f %f %f", &max_TDD[i], &base_wreq[i], &OptimumT[i], &ini_N_fix[i], &max_root_length[i]);//Brian	
			fscanf(fpp, "%f %d", &plantP[i], &stem_age);
			fscanf(fpp, "%f %f %f %f", &TreeMatuAge[i], &TreeCurretAge[i], &TreeLeafMax[i], &TreeLeafMin[i]);
			fscanf(fpp, "%d", &maturity_flag[i]);
			fscanf(fpp, "%d", &crop_days[i]);
			fscanf(fpp, "%f", &totalFFPGI[i]);
			fscanf(fpp, "%f", &root_depth[i]);
			fscanf(fpp, "%d", &crop_water_stress_days[i]);
			fscanf(fpp, "%f", &crop_water_stress[i]);
			fscanf(fpp, "%d", &crop_N_stress_days[i]);
			fscanf(fpp, "%f", &crop_N_stress[i]);
			fscanf(fpp, "%f", &root_length[i]);
			fscanf(fpp, "%d", &perRegrow[i]);
			fscanf(fpp, "%d", &vernal[i]);
			fscanf(fpp, "%f", &cTT[i]);
			fscanf(fpp, "%f", &pDFCUM[i]);
			fscanf(fpp, "%d", &RootShape[i]);
			fscanf(fpp, "%f", &GrainFill[i]);
			fscanf(fpp, "%f", &LAImax[i]);
			fscanf(fpp, "%f", &FrostKill[i]);
			fscanf(fpp, "%f", &cHRMX[i]);
			fscanf(fpp, "%f", &cDRMX[i]);
			fscanf(fpp, "%f", &cTMX[i]);
			fscanf(fpp, "%f", &pDFMX[i]);
			fscanf(fpp, "%f", &rootNewResp[i]);
			fscanf(fpp, "%f", &rootMResp[i]);
			fscanf(fpp, "%f", &shootNewResp[i]);
			fscanf(fpp, "%f", &shootMResp[i]);
		fscanf(fpp, "%lf", &kext1[i]);//Theo
			fscanf(fpp, "%lf", &kext2[i]);//Theo
	fscanf(fpp, "%lf", &cmaxh[i]);//Theo
	fscanf(fpp, "%f", &cropGRate[i]);//Theo
	fscanf(fpp, "%f", &cropTime[i]);//Theo
	fscanf(fpp, "%f", &rueHI[i]);//Theo
	fscanf(fpp, "%f", &delayP[i]);//Theo

			
			for(int ip=1;ip<8;ip++)
		{
			fscanf(fpp, "%f", &per[i][ip]);
		}
		//	fscanf(fpp, "%f", &crop_days[i]);

						//adjust rooting Depth based on clay content
			float rootPenetration;
			rootPenetration = -1.1429 * clay[1] + 1.2857;
			rootPenetration = min(1.0, max(0.0, rootPenetration));
			rootPenetration = 1.0;
			max_root_length[i] = rootPenetration * max_root_length[i];

			float CO2Multi;
			if (crop[cwc] == 3||crop[cwc]==29)//soybean
				{
					CO2Multi = 0.25;
				}
			if (crop[cwc] == 18)//potato
			{
				CO2Multi = 0.6;

			}
			else //all other crops
				{
					CO2Multi = 0.6;
				}
			CO2_factor = 1.0 + CO2Multi * log(Base_CO2 / 350.0);	//July 2021 addded this because CO2 factor needed to be recalculated based on current Base_CO2 for perennial crops 1.0 + 0.6 * log(Base_CO2 / 350.0)


			//Effect of CO2
			if (crop[i] == 1 || crop[i] == 7 || crop[i] == 65 || crop[i] == 13 || crop[i] == 27||crop[i]==90) C_type[i] = 4;//determines C3 or C4 species for later.
			else C_type[i] = 3;

			if(C_type[i]==4)
			maxmn[i] *= 1.0;
			else
		    maxmn[i] = base_maxmn[i]*CO2_factor;//needed to calculate based on basemaxmn
			//maxmn[i] *= CO2_factor;//worked fine for annual crops ...not for perennials.
			wreq[i] = base_wreq[i] / CO2_factor;//this must be for perennials or batch?

			graincn[i] = base_graincn[i];
			leafcn[i] = base_leafcn[i];
			stemcn[i] = base_stemcn[i];
			rootcn[i] = base_rootcn[i]; 

			/*
			if(C_type[i]==3)
				co2_crop = powf(CO2_factor, 0.1);
			else
				co2_crop = 1.0;

			graincn[i] = base_graincn[i] * co2_crop;//Brian
			leafcn[i] = base_leafcn[i] * co2_crop;
			stemcn[i] = base_stemcn[i] * co2_crop;
			rootcn[i] = base_rootcn[i] * co2_crop;
			*/
			//Brian enabled this for CO2 project
			co2_crop = powf(CO2_factor, 0.1);
			graincn[i] = base_graincn[i] * co2_crop;//Brian
			leafcn[i] = base_leafcn[i] * co2_crop;
			stemcn[i] = base_stemcn[i] * co2_crop;
			rootcn[i] = base_rootcn[i] * co2_crop;

			if(maxmn[i]<=0.0) 
			{
				plantcn[i] = 0.00001;
				grain[i] = 0.00001;
				stem[i] = 0.00001;
				root[i] = 0.00001;
			}
			else
			{
				plantcn[i] = 1.0 / (grain[i]/graincn[i] + leaf[i]/leafcn[i] + stem[i]/stemcn[i] + root[i]/rootcn[i]);//Effect of CO2
			}

			float MaxCropBiomass = maxmn[i] * plantcn[i];
			MaxLeafN[i] = MaxCropBiomass * leaf[i] / base_leafcn[i];			
			MaxStemN[i] = MaxCropBiomass * stem[i] / base_stemcn[i];
			MaxRootN[i] = MaxCropBiomass * root[i] / base_rootcn[i];
			MaxGrainN[i] = MaxCropBiomass * grain[i] / base_graincn[i];

			LeafN[i] = Leaf_Wt[i] / base_leafcn[i];
			StemN[i] = Stem_Wt[i] / base_stemcn[i];
			RootN[i] = Root_Wt[i] / base_rootcn[i];
			GrainN[i] = Grain_Wt[i] / base_graincn[i];
			
			if(Transplant[i]<0) Transplant[i] = 0;

			crop_flag[i] = 1;
			//jdseed[i] = 0;
			lai_index[i] = 1.0;
			plantP[i] = 0.4;
		//	max_root_length[i]=1.5;

			f_root[i] = root[i];
			f_grain[i] = grain[i];
			f_leaf[i] = leaf[i];
			f_stem[i] = stem[i];

			if(crop[i]==1||crop[i]==7||crop[i]==65||crop[i]==13||crop[i]==27||crop[i]==90) C_type[i] = 4;
			else C_type[i] = 3;		

			if(vascularity[i]<0.0) vascularity[i] = 0.0;

			if(crop[i]==20||crop[i]==64||crop[i]==65) vascularity[i] = 1.0;		

			ini_maxmn[i] = maxmn[i];
			
			if(Option>100) 
			{
				GrainYield[i] *= (1.0 + SMC[18]);
				maxmn[i] *= (1.0 + SMC[18]);
				left_perc[i] *= (1.0 + SMC[28]);

				plantcn[i] *= (1.0 + SMC[22]);
				graincn[i] *= (1.0 + SMC[22]);
				leafcn[i] *= (1.0 + SMC[22]);
				stemcn[i] *= (1.0 + SMC[22]);
				rootcn[i] *= (1.0 + SMC[22]);
				ini_N_fix[i] *= (1.0 + SMC[23]);
				wreq[i] *= (1.0 + SMC[24]);
				cropht *= (1.0 + SMC[26]);
				max_TDD[i] *= (1.0 + SMC[27]);
			}

			if(crop[i]==11||crop[i]==12) GrassFlag[i] = 1;//grass crops

			if(PerennialFlag[i]==1)//perrenial grassland
			{				
				WinterCropFlag[i] = 1;
				HarvestYear[i] = 1;
				//jdseed[i] = 1;
				//grow_days[i] = 365;
				//seed[i] = 1;
				InitialBiomass[i] = 0.0;//kg C/ha
				//TDD[i]=0.0;
				//PlantTakeN[i]=0.0;
				//demandn[i]=0.0;
				//crop_trans[i]=0.0;
				//ddupn[i] = 0.0;

				if(GlobeData==1)
				{
					plantn[i] = 0.0;
					demandn[i] = 0.0;
					lai[i] = 0.0;
					Leaf_Wt[i] = 0.0;
					Pod_Wt[i] = 0.0;
					Root_ExuC[i] = 0.0;
					Root_ExuN[i] = 0.0;
					Stem_Wt[i] = 0.0;
					Grain_Wt[i] = 0.0;
					Root_Wt[i] = 0.0;
					LeafN[1] = 0.0;
					StemN[1] = 0.0;
					GrainN[1] = 0.0;
					RootN[1] = 0.0;
				}			
			}

			if(i==1) 
			{
				crop1_trans = crop_trans[1];
				crop_trans[1] = 0.0;
			}

			if(i==2) 
			{
				crop2_trans = crop_trans[2];
				crop_trans[2] = 0.0;
			}
		}
	//fclose(fpp);
	}
	fscanf(fpp, "%d %d %d %d %d %d %d %d %d %d", &cropRotType[0], &cropRotType[1], &cropRotType[2], &cropRotType[3], &cropRotType[4], &cropRotType[5], &cropRotType[6], &cropRotType[7], &cropRotType[8], &cropRotType[9]);
	fclose(fpp);
			
	///////////////////////////////////////////////////////////////////////////////////////////////
	//if(PerennialFlag[1]==0)
	{
		sprintf(crop_file, "%s\\crop-%d", FCT40, year);
			
		fp = fopen(crop_file, "r");
		if ( fp == NULL ) note(0,crop_file);

		fscanf(fp, "%d", &NewCropNumbers);
if(IniCropNumbers==1 && PerennialFlag[1]==1)
{
	//NewCropNumbers=1;//added this for the perrenial flag to work properly. Otherwise you got excessive planting.
}
		int IniCCC, TotalCCC;
		if(MODE==0) 
		{
			IniCCC = IniCropNumbers+1;
			TotalCCC = IniCropNumbers+NewCropNumbers;//IniCCC+NewCropNumbers;//
		}
		else 
		{
			IniCCC = 1;
			TotalCCC = NewCropNumbers;
		}

		for (i=IniCCC; i<=TotalCCC; i++)
		{
			
			fscanf(fp, "%d %s %d %d %f %d", 
				&crop[i], crop_name[i], &WinterCropFlag[i], &WCLeftDays[i], &GrainYield[i], &HarvestYear[i]);
			fscanf(fp, "%d %d %f %f %d", 
				&jdseed[i], &grow_days[i], &left_perc[i], &maxmn[i], &indi);			
			fscanf(fp, "%f %d %f %f %f", 
				&InitialBiomass[i],&Transplant[i],&jf,&jf,&jf);
				   //&InitialBiomass[i], &GrowthVegetative[i], &GrowthReproductive[i],
				   //&PsnEfficiency[i], &PsnMax[i]);
			fscanf(fp, "%d", &CoverCrop[i]);
			fscanf(fp, "%d", &PerennialFlag[i]);
			fscanf(fp, "%f %f %f %f", &grain[i], &leaf[i], &stem[i], &root[i]);
			fscanf(fp, "%f %f %f %f", &base_graincn[i],  &base_leafcn[i], &base_stemcn[i], &base_rootcn[i]);//Brian
			fscanf(fp, "%f %f %f %f %f", &max_TDD[i], &base_wreq[i], &OptimumT[i], &ini_N_fix[i], &max_root_length[i]);//Brian //was vascularity
			fscanf(fp, "%f %f %f %f", &TreeMatuAge[i], &TreeCurretAge[i], &TreeLeafMax[i], &TreeLeafMin[i]);
			fscanf(fp, "%d %f", &RootShape[i], &GrainFill[i]);
			fscanf(fp, "%f %f", &LAImax[i], &FrostKill[i]);
			fscanf(fp, "%f %f %f %f", &cHRMX[i], &cDRMX[i], &cTMX[i], &pDFMX[i]);
			fscanf(fp, "%f %f", &rootNewResp[i], &rootMResp[i]);
			fscanf(fp, "%f %f",  &shootNewResp[i], &shootMResp[i]);
			fscanf(fp, "%lf %lf %lf", &kext1[i], &kext2[i], &cmaxh[i]);//Theo
			fscanf(fp, "%f %f %f %f", &cropGRate[i], &cropTime[i], &rueHI[i], &delayP[i]);//Theo
			
			if (crop[i] == 3)//testing to fix podN
			{
				//maxmn[i] = maxmn[i] + GrainYield[i] / base_graincn[i];
			}
			//adjust rooting Depth based on clay content
			float rootPenetration;
			rootPenetration = -1.1429 * clay[1] + 1.2857;
			rootPenetration = min(1.0, max(0.0, rootPenetration));
			rootPenetration = 1.0;
			max_root_length[i] = rootPenetration * max_root_length[i];


			plantP[i] = 0.0;
		//	max_root_length[i]=1.5;
			f_root[i] = root[i];
			f_grain[i] = grain[i];
			f_leaf[i] = leaf[i];
			f_stem[i] = stem[i];

			//if(NEWcrop[i]==crop[i]&&PerennialFlag[i]==1) NewCropNumbers--;
						
			if(vascularity[i]<0.0) vascularity[i] = 0.0;

			if(crop[i]==1||crop[i]==7||crop[i]==65||crop[i]==13||crop[i]==27||crop[i]==90) C_type[i] = 4;
			else C_type[i] = 3;

			//Effect of CO2
			CO2_factor=1.0;

			float CO2Multi;
			if (crop[cwc] == 3||crop[cwc]==29)//soybean
			{
				CO2Multi = 0.25;
			}
			if (crop[cwc] == 18)//potato
			{
				CO2Multi = 0.6;

			}
			else//other crops
			{
				CO2Multi = 0.6;
			}
			CO2_factor = 1.0 + CO2Multi * log(Base_CO2 / 350.0);	//July 2021 addded this because CO2 factor needed to be recalculated based on current Base_CO2 for perennial crops 1.0 + 0.6 * log(Base_CO2 / 350.0)

			//if(C_type[i]==4)
			base_maxmn[i] = maxmn[i];
			if(crop[i]==1||crop[i]==41)//||crop[i]==3
			maxmn[i] *= 1.0;
			else
			maxmn[i] *= CO2_factor; //brian investigate for crash -- should this be multiplying the maxmn * CO2 factor? Makes the optimal plant maxmn go up. // base_maxmn[i]*CO2_factor;
			//wreq[i] = base_wreq[i] / CO2_factor;
			wreq[i] = base_wreq[i] /(1+(CO2_factor-1.0)*1.0);//for major crops wreq[i] = base_wreq[i] /(1+(CO2_factor-1.0)*0.25)
			graincn[i] = base_graincn[i];
			leafcn[i] = base_leafcn[i];
			stemcn[i] = base_stemcn[i];
			rootcn[i] = base_rootcn[i]; 
			co2_crop = powf(CO2_factor, 0.1);
			
			/*
			if(C_type[i]==3)
				co2_crop = powf(CO2_factor, 0.1);
			else
				co2_crop = 1.0;*/
			//Brian enabled for CO2 project
			graincn[i] = base_graincn[i] * co2_crop;//Brian
			leafcn[i] = base_leafcn[i] * co2_crop;
			stemcn[i] = base_stemcn[i] * co2_crop;
			rootcn[i] = base_rootcn[i] * co2_crop;
			//wreq[i] = base_wreq[i] / CO2_factor;


			lai_index[i] = 1.0;
			
			if(maxmn[i]<=0.0) 
			{
				plantcn[i] = 0.00001;
				grain[i] = 0.00001;
				stem[i] = 0.00001;
				root[i] = 0.00001;
			}
			else
			{
				//plantcn[i] = (GrainYield[i]/grain[i]) / maxmn[i];
				plantcn[i] = 1.0 / (grain[i]/graincn[i] + leaf[i]/leafcn[i] + stem[i]/stemcn[i] + root[i]/rootcn[i]);//Effect of CO2
			}

			ini_maxmn[i] = maxmn[i];
			
			if(Option>100) 
			{
				GrainYield[i] *= (1.0 + SMC[18]);
				maxmn[i] *= (1.0 + SMC[18]);
				left_perc[i] *= (1.0 + SMC[28]);

				plantcn[i] *= (1.0 + SMC[22]);
				graincn[i] *= (1.0 + SMC[22]);
				leafcn[i] *= (1.0 + SMC[22]);
				stemcn[i] *= (1.0 + SMC[22]);
				rootcn[i] *= (1.0 + SMC[22]);
				ini_N_fix[i] *= (1.0 + SMC[23]);
				wreq[i] *= (1.0 + SMC[24]);
				cropht *= (1.0 + SMC[26]);
				max_TDD[i] *= (1.0 + SMC[27]);
			}

			if ( crop[i] == 0 ) jdseed[i] = 0;

			float MaxCropBiomass = maxmn[i] * plantcn[i];
			MaxLeafN[i] = MaxCropBiomass * leaf[i] / base_leafcn[i];			
			MaxStemN[i] = MaxCropBiomass * stem[i] / base_stemcn[i];
			MaxRootN[i] = MaxCropBiomass * root[i] / base_rootcn[i];
			MaxGrainN[i] = MaxCropBiomass * grain[i] / base_graincn[i];

			if(WCLeftDays[i]==0) seed[i] = 0;
			else seed[i] = grow_days[i] - WCLeftDays[i];
			
			if(PerennialFlag[i]==1)//perrenial grassland
			{				
				WinterCropFlag[i] = 1;
				HarvestYear[i] = 1;
				//jdseed[i] = 1;
//				grow_days[i] = 365;
				seed[i] = 0;
				InitialBiomass[i] = 0.0;//kg C/ha
				TDD[i]=0.0;
				PlantTakeN[i]=0.0;
				demandn[i]=0.0;
				crop_trans[i]=0.0;
				ddupn[i] = 0.0;
				//crop_flag[i] = 1;
				Transplant[i]=0;

				if(GlobeData==1)
				{
					plantn[i] = 0.0;
					demandn[i] = 0.0;
					lai[i] = 0.0;
					Leaf_Wt[i] = 0.0;
					Pod_Wt[i] = 0.0;
					Root_ExuC[i] = 0.0;
					Root_ExuN[i] = 0.0;
					Stem_Wt[i] = 0.0;
					Grain_Wt[i] = 0.0;
					Root_Wt[i] = 0.0;
					LeafN[1] = 0.0;
					StemN[1] = 0.0;
					GrainN[1] = 0.0;
					RootN[1] = 0.0;
				}			
			}
		}	
		fclose( fp );
	}
	//else 
	//{
	//	NewCropNumbers = 0;
	//}

//	if(PerennialFlag[1]==1)
//	{NewCropNumbers=0;
//	}

	CropNumbers = IniCropNumbers + NewCropNumbers;

	//if(IniCropNumbers==1) WinterCropFlag[1]=1;

	int FCR=0;
	for (i=1; i<=CropNumbers; i++)
	{
		if(crop[i]==0) FCR++;
	}

	CropNumbers -= FCR;

	if(crop[1]==20||crop[1]==64||crop[1]==65)
	{
		if(WinterCropFlag[1]==1) flood_flag = 1;


	}
}

int class_model::read_in_vege(int MODE, int CU, int ccwc)
{
    FILE *fp;
    char  VEGE[80], Wd[160], WW[100];
	float jf;
	int jd;

	//WiltFlag[ccwc] = 0;
	//cropht = 0.5;

/*	if(Option>100)
	{
		//myc *= (1.0 + SMC[18]);
		plantcn[ccwc] *= (1.0 + SMC[22]);
		graincn[ccwc] *= (1.0 + SMC[22]);
		leafcn[ccwc] *= (1.0 + SMC[22]);
		stemcn[ccwc] *= (1.0 + SMC[22]);
		rootcn[ccwc] *= (1.0 + SMC[22]);
		ini_N_fix[ccwc] *= (1.0 + SMC[23]);
		wreq[ccwc] *= (1.0 + SMC[24]);
		cropht *= (1.0 + SMC[26]);
		max_TDD[ccwc] *= (1.0 + SMC[27]);
	}
*/
	//crop_T_demand[ccwc]=max_TDD[ccwc];

	if(CU==1)
	{
		//float Fco2= -0.0009 * Base_CO2 + 1.3;//Dhakhwa et al. 1997
		
		CropWaterDemand[ccwc] = wreq[ccwc] * maxmn[ccwc] * plantcn[ccwc] / 0.4 / 1000.0 / 10000.0;
		if(jday==1)
		{
			if(crop1_trans>0.0) 
			{
				CropWaterDemand[1] -= crop1_trans;
				crop1_trans = 0.0;
			}

			if(crop2_trans>0.0) 
			{
				CropWaterDemand[2] -= crop2_trans;
				crop2_trans = 0.0;
			}
		}
	}

	//SLN = 250.0;
	//ALV = InitialCropBiomass / SLN;
	//lai[ccwc] = InitialCropBiomass / 250.0;
	//N_fix = ini_N_fix[ccwc];
	if (year == 12 && jday == 5)
	{
		float blah;
		blah = 1.0;

	}
	//maxN = maxmn[ccwc] / N_fix;// * DrainF;//???
	if(ini_N_fix[ccwc]>1.0) ini_N_fix[ccwc]=1.0;
	if(ini_N_fix[ccwc]>0.0) max_N_fix[ccwc] = ini_N_fix[ccwc]* maxmn[ccwc];//max_N_fix[ccwc] = (1.0 - 1.0 / (ini_N_fix[ccwc]*ini_N_fix[ccwc])) * maxmn[ccwc];
	else max_N_fix[ccwc] = 0.0;

	//stemcn[ccwc] = stemcn[ccwc];
	//leafcn[ccwc] = leafcn[ccwc];
	if(graincn[ccwc]<=0.0) graincn[ccwc] = leafcn[ccwc];

	if(crop[ccwc]==1||crop[ccwc]==7||crop[ccwc]==65||crop[ccwc]==13||crop[ccwc]==27|| crop[ccwc] == 90) C_type[ccwc] = 4;
	else C_type[ccwc] = 3;

  	ddupn[ccwc] = 0.0;

	

	//----------------------------
	
//	stemcn[ccwc] = 30; // Rice FACE observation
//	leafcn[ccwc] = 15; // Rice FACE observation
//	stemcn[ccwc] = 41; // Rice FACE observation


	//----------------------------
	if(crop[ccwc]==11||crop[ccwc]==12)//grass
	{			
		float PG_b, PG_s, PG_g, PG_r;
		PG_b = maxmn[ccwc] * plantcn[ccwc];
		PG_g = PG_b * grain[ccwc];
		PG_s = PG_b * stem[ccwc];
		PG_r = PG_b * root[ccwc];

		GrainYield[ccwc] = PG_g;// + PG_s;//kg C/ha
		OptCropC[ccwc] = GrainYield[ccwc] / grain[ccwc];//+straw[ccwc]);
	}
	else
	{
		OptCropC[ccwc] = GrainYield[ccwc] / grain[ccwc];
	}

	OptGrainC[ccwc] = OptCropC[ccwc] * grain[ccwc];
	OptLeafC[ccwc] = OptCropC[ccwc] * leaf[ccwc];
	OptStemC[ccwc] = OptCropC[ccwc] * stem[ccwc];
	OptRootC[ccwc] = OptCropC[ccwc] * root[ccwc];

    return( 0 );
}


void class_model::read_in_LAI(void)
{
	FILE *fp;
    char  FLOOD[80], LaiFile[200];
    int   i;

    sprintf(FLOOD, "%s\\Inter\\Observed_LAI.txt", OUTPUT);
    
    fp = fopen(FLOOD, "r");
    if ( fp == NULL ) 
    {
        char err[60];
		sprintf(err,"%s not found",FLOOD);
		MessageBox(NULL, err, "Error Message", 0);
		exit(0);
    }

    fscanf(fp, "%d", &LaiFlag);
	if(LaiFlag==1) fscanf(fp, "%s", LaiFile);
    fclose( fp );

	if(LaiFlag==1) 
	{
		char ww[200];
		sprintf(FLOOD, "%s", LaiFile);
		float lai_v;
		int flag = 1;
    
		fp = fopen(FLOOD, "r");
		if ( fp == NULL ) 
		{
			char err[60];
			sprintf(err,"%s not found",FLOOD);
			MessageBox(NULL, err, "Error Message", 0);
			exit(0);
		}

		fgets(ww, 200, fp);
		for(int i=1; i<=365; i++)
		{
			
			if(flag==1) fscanf(fp, "%d", &jday);

			if(jday==i)
			{
				fscanf(fp, "%f", &lai_v);
				
				flag=1;
			}
			else
			{
				
				flag = 0;
			}
			
		}
		fclose( fp );

	}

}

int class_model::read_in_clim(int DroughtID)
{
    FILE  *fp;
    char   CLIM[80];
 
    sprintf(CLIM, "%s\\Inputs\\clim-%d", OUTPUT, year);
    
    fp = fopen(CLIM, "r");
    if ( fp == NULL ) note(0, CLIM);
    
	if(DroughtID==1&&year==2)
	{
		fscanf(fp, "%s %s %s", climd[1],climd[2],climd[3]);//for dry, mid, wet years
		fscanf(fp, "%s %s %s", climy[1],climy[2],climy[3]);

	}
	else
	{
		fscanf(fp, "%s", climd[0]);
		fscanf(fp, "%s", climy[0]);
	}
	//fgets(climd, 200, fp);
	//fgets(climy, 200, fp);
    fclose( fp );
    return( 0 );
}

int class_model::read_in_climy(int MODE, int drc, int DroughtID)
{
    FILE *fp;
    int   mon, ETM=1;
    char F_CLIM[80];

	if(year==2&&DroughtID==1)
	{
		int CYR=drc;
		if(drc>=4) CYR=2;
		sprintf(F_CLIM, "%s\\Inputs\\%s", OUTPUT, climy[CYR]);
	}
	else
		sprintf(F_CLIM, "%s\\Inputs\\%s", OUTPUT, climy[0]);
    
	float jf;
    fp = fopen(F_CLIM, "r");
    if ( fp == NULL ) note(0, F_CLIM);
    
    for ( mon = 1 ; mon <= 12; mon++ )
    {
	fscanf(fp, "%f", &mon_avet[mon]);
    }

    fscanf(fp, "%f %f %f %f %f %f %d", &yr_avetj, &jf, &rno3, &base_nh3, &Base_CO2, &CO2_IncreaseRate, &ETM);

    fclose( fp );

	if(MODE==1) CO2_IncreaseRate=0.0;

	if(CO2_IncreaseRate<0.0)
	{
		int YY, Y;
		float new_CO2;
		FILE  *fp;
		char   CLIM[80];
		sprintf(CLIM, "%s",CO2FileName);
		//sprintf(CLIM, "%s\\Inter\\MultiYear_AirCO2.txt", OUTPUT);    
		fp = fopen(CLIM, "r");
		if ( fp == NULL ) note(0,"your CO2 file. Try re-entering your multi-airCO2 file and save the dnd");//,CLIM
		
		fscanf(fp, "%d", &YY);
		for(int i=1; i<=YY; i++)
		{
			fscanf(fp, "%d", &Y);
			fscanf(fp, "%f", &new_CO2);

			if(Y==year) break;

			if(i==YY)
			{
				CString note;
				note.Format("File MultiYear_AirCO2 is not correctly prepared");
				AfxMessageBox(note);
				exit(0);
			}
		}
		fclose( fp );

		Base_CO2 = new_CO2;
	}
	else
	{
		Base_CO2 += CO2_IncreaseRate * (float)(year-1);
	}	

	if(Option>100)
	{
		Base_CO2 *= (1.0 + SMC[3]);
		base_nh3 *= (1.0 + SMC[4]);
		rno3 *= (1.0 + SMC[5]);
		yr_avetj *= (1.0 + SMC[1]);
		yr_rain *= (1.0 + SMC[2]);
	}

	//CO2_factor = 1.0 + 0.6 * log(Base_CO2 / 350.0);

	float CO2Multi;
	if (crop[cwc] == 3 || crop[cwc]==29)//soybean
	{
		CO2Multi = 0.25;
	}
	if (crop[cwc] == 18)//potato
	{
		CO2Multi = 0.6;
	
	}
	else//othercrops
	{
		CO2Multi = 0.6;
	}
	CO2_factor = 1.0 + CO2Multi * log(Base_CO2 / 350.0);	//July 2021 addded this because CO2 factor needed to be recalculated based on current Base_CO2 for perennial crops 1.0 + 0.6 * log(Base_CO2 / 350.0)


	//rain_ph = 6.7;

    return(ETM);
}
void class_model::read_in_OBSYield(int MODE)
{
	//obsYieldFlag == 1)
	// OBSYieldFileName);
	FILE* fp;
	char  YIELD[150];
	int   csl,jdd;
	char jd[80];

	sprintf(YIELD, "%s", OBSYieldFileName);
	fp = fopen(YIELD, "r");
	if (fp == NULL) note(0, YIELD);

	fscanf(fp, "%s %s %s %s %s", &jd, &jd, &jd, &jd, &jd);//header year GrainC LeafC StemC RootC

	for (csl = 1; csl <= year; csl++)
	{
		fscanf(fp, "%d %f %f %f %f",&jdd, &obsGrain[csl], &obsLeaf[csl], &obsStem[csl],&obsRoot[csl]);
	}
	fclose(fp);

}
void class_model::read_in_irri(int MODE, int IrriType, CString FCT40)
{
    FILE *fp;
    char  IRRI[80];
    int   csl;

    sprintf(IRRI, "%s\\irri-%d", FCT40, year);

    fp = fopen(IRRI, "r");
    if ( fp == NULL ) note(0, IRRI);
    
	if (MODE==0)
    {
		fscanf(fp, "%d %f %d", &irr_num, &irri_index, &irrimethod[0]);
		
		if(irr_num==0&&irri_index>0.0) IrriMethod = irrimethod[0];

		for (csl=1; csl<=irr_num; csl++ )
		{
			fscanf(fp, "%d %f %d %d", &jdirr[csl], &irria[csl], &irrimethod[csl],&tileIrriDays[csl]);
			irriph[csl] = 6.7;
			irria[csl] *= 0.01;// cm -> m
		}

		//if(IrriType==0) irri_index = 0.0;
	}
	else
	{
		fscanf(fp, "%d %f %d", &irr_num, &irri_index, &irrimethod[0]);

		IrriMethod = irrimethod[0];

		if(IrriType==0) irri_index = 0.0;
	}
    fclose( fp );

	if(Option>100)
	{
		irri_index *= (1.0 + SMC[37]);
		irri_index = max(0.0, min(1.0, irri_index)); 
	}
//controlled drainage
FILE *fd;
    char  Drain[80];
    int   cdl;

    sprintf(Drain, "%s\\cdrain-%d", FCT40, year);

    fd = fopen(Drain, "r");


	if ( fd == NULL ) note(0, Drain);
	if (MODE==0)
    {
	fscanf(fd, "%d", &cdrain_num);
	for (cdl=1; cdl<=cdrain_num; cdl++ )
		{
			fscanf(fd, "%d %d %f", &stdrain[cdl], &enddrain[cdl], &cdraindepth[cdl]);
			cdrainDays[cdl]=enddrain[cdl]-stdrain[cdl]+1;
		}
	}
	else
	{
	fscanf(fd, "%d", &cdrain_num);
	}
    fclose(fd);
}
int class_model::read_in_extra(CString FCT40)
{
	FILE *fp;
    char  EXTRA[80];
    int   csl;

	sprintf(EXTRA, "%s\\extra-1", FCT40, year); //sprintf(EXTRA, "%s\\extra-%d", FCT40, year);
	fp = fopen(EXTRA, "r");
    if ( fp == NULL ) 
    {
	char err[60];
		sprintf(err,"%s not found",EXTRA);
		MessageBox(NULL, err, "Error Message", 0);
		return( FILE_NOT_FOUND );
    }
	float Factor1,Factor2,Factor3,Factor4,Factor5,Factor6,Factor7,Factor8,Factor9;
	fscanf(fp, "%f", &drainageDepthM);
	fscanf(fp, "%f", &spaceDrain);
	fscanf(fp, "%f", &reDrain);
	fscanf(fp, "%f", &dDrain);
	fscanf(fp, "%f", &keDrainM);
	fscanf(fp, "%f", &maxNO3F);maxNO3F=maxNO3F*0.004;maxNO3F=min(2.0,max(0.0,maxNO3F));
	fscanf(fp, "%f", &moveN);
	fscanf(fp, "%f", &partitN);
	fscanf(fp, "%f", &NLeachF); NLeachF=pow(NLeachF,4);
	fscanf(fp, "%f", &evapMulti);
	fscanf(fp, "%f", &runMulti);//snow water runoff
	fscanf(fp, "%f", &runMultiN);runMultiN=pow(runMultiN,4);
	fscanf(fp, "%f", &nit2Multi);
	fscanf(fp, "%f", &snowInsulationFactor); snowInsulationFactor = pow(snowInsulationFactor, 5);//scale the factor to be a more sensitive factor for users (0-2 index)
	fscanf(fp, "%f", &snowmeltMulti);snowmeltMulti=pow(snowmeltMulti,4);
	fscanf(fp, "%f", &denitMulti);denitMulti=pow(denitMulti,4);
	fscanf(fp, "%f", &nitMulti);nitMulti=pow(nitMulti,4);
	fscanf(fp, "%f", &rainMulti);rainMulti=pow(rainMulti,4);
	fscanf(fp, "%f", &springMulti);
	fscanf(fp, "%f", &NreductionFactor);
	fscanf(fp, "%f", &NH3Vol);NH3Vol=pow(NH3Vol,4);
	fscanf(fp, "%f", &PrefNMove);PrefNMove=min(1.0,max(0.0,PrefNMove));
	fscanf(fp, "%d", &autoHarvestF);
	fscanf(fp, "%f", &SoilStructEffect); if(SoilStructEffect>0) SoilStructEffect=1.0;
	fscanf(fp, "%f", &SoilReset);if(SoilReset>0) SoilReset=1.0;
	fscanf(fp, "%d", &SoilSpinUp);
	fscanf(fp, "%d", &SoilSpinUpYears);
	if (SoilSpinUp == 1)
	{
		fscanf(fp, "%s", &SoilSpinUpFileName);
	}
	
	fscanf(fp, "%d", &CO2file);
	if (CO2file == 1)
	{
		fscanf(fp, "%s", &CO2FileName);
	}

	fscanf(fp, "%f", &SwcWTEffect); //for certain textured soils
	fscanf(fp, "%f", &rainFallInterFactor); // rainFallInterFactor=powf(rainFallInterFactor,2.5);	//sets a texture effect of WT on SWC (on or off) //SwcWTEffect2>0
	fscanf(fp, "%f", &SolarEffectTemp);
	fscanf(fp, "%f", &UreaHydroFactor);
	fscanf(fp, "%f", &UreaHydroWaterFactor);
	fscanf(fp, "%f", &NH3SoilDFactor); if(NH3SoilDFactor<=0)NH3SoilDFactor=1.0;
	fscanf(fp, "%f", &UreaDifFactor); UreaDifFactor=min(1.0,max(0.0,UreaDifFactor));
	fscanf(fp, "%f", &N2N2OFactor);  if (N2N2OFactor <= 0)N2N2OFactor = 1.0;
	fscanf(fp, "%d", &spinUpPlant);  if (spinUpPlant < 0)spinUpPlant = 0;
	fscanf(fp, "%d", &obsYieldFlag);  if (obsYieldFlag < 0)obsYieldFlag = 0;
	if (obsYieldFlag == 1)
	{
		fscanf(fp, "%s", &OBSYieldFileName);
	}
	fscanf(fp, "%d", &autoPlantF);
	fscanf(fp, "%d", &prefFlowCheck); if (prefFlowCheck < 0)prefFlowCheck = 0;
	fscanf(fp, "%f", &prefFlowDepth); if (prefFlowDepth < 0 && prefFlowCheck==1)prefFlowDepth = 0.1;
	fscanf(fp, "%f", &prefFlowRecov); if (prefFlowRecov < 0 || prefFlowRecov >1 )prefFlowRecov = 0.1;

if(UreaHydroFactor<=0)
{UreaHydroFactor=1.0;}
if(UreaHydroWaterFactor<=0)
{UreaHydroWaterFactor=1.0;}

if(SolarEffectTemp<=0)
{SolarEffectTemp=1.0;}
if(snowInsulationFactor<=0)
{snowInsulationFactor=1.0;}
	fclose(fp);
	return 0;

}
int class_model::read_in_till(CString FCT40)
{
    FILE *fp;
    char  TILL[80];
    int   csl;

    sprintf(TILL, "%s\\till-%d", FCT40, year);
    
    fp = fopen(TILL, "r");
    if ( fp == NULL ) 
    {
	char err[60];
		sprintf(err,"%s not found",TILL);
		MessageBox(NULL, err, "Error Message", 0);
		return( FILE_NOT_FOUND );
    }
    fscanf(fp, "%d", &til_num);

    //til_num = 0;

    for ( csl = 1; csl <= til_num; csl++ )
    {
		fscanf(fp, "%d %d", &jdtil[csl], &til_method[csl]);

		if(til_method[csl]==1) til_dept[csl] = 0.0;
		else if(til_method[csl]==2) til_dept[csl] = 0.05;
		else if(til_method[csl]==3) til_dept[csl] = 0.1;
		else if (til_method[csl] == 8) til_dept[csl] = 0.15;
		else if(til_method[csl]==4) til_dept[csl] = 0.2;
		else if(til_method[csl]==5) til_dept[csl] = 0.3;
		else if(til_method[csl]==6) til_dept[csl] = 0.2;
		else if(til_method[csl]==7) 
		{
			til_dept[csl] = 0.2;
			crop_terminator = 1;
		}
		else til_dept[csl] = 0.2;
		
		if(Option>100)
		{
			jdtil[csl] += (int)(SMC[29]);
			til_dept[csl] *= (1.0 + SMC[30]);
		}
    }
    fclose( fp );

    return( 0 );
}


int class_model::read_in_fert(int MODE, CString FCT40)
{
    FILE *fp;
    char  FERT[80];
    int   csl, FertMethod;
	float jf;

	FertOption=0;
	
    sprintf(FERT, "%s\\fert-%d", FCT40, year);

    fp = fopen(FERT, "r");
    if(fp==NULL) note(0, FERT); 
    
    fscanf(fp, "%d", &fer_num);

	//fer_num = 0;

	if(fer_num>=0)//manual application
	{
		for ( csl =1 ; csl <= fer_num; csl++ )
		{
			fscanf(fp, "%d %f", &jdfer[csl], &fer_dept[csl]);
			fscanf(fp, "%f %f %f %f %f %f %f", &fer1[csl], &fer2[csl], &fer3[csl], &fer4[csl], &fer5[csl], &fer6[csl], &fer7[csl]);
			fscanf(fp, "%d %f %f %f %f %f %d", &FertMethod, &FertDayRelease[csl], &NIefficiency[csl], &NIduration[csl],
											&UreaseEfficiency[csl], &UreaseDuration[csl],&FertMethodApp[csl]);//fertmethodApp is 0,1,2,3 for surface, injected,incorporated and soon to be banded
			if(MODE==1)
			{
				//FertMethod: 1- conventional, 2- Slow-release, 3- Nitrification inhibitor, 4- Soil-N-adjusted rate, 
				//5- Precision fertilization, 6-urease inhibitor, 7-sulphate, 
				
				FertDayRelease[csl]=1;
				NIefficiency[csl]=0.0;
				NIduration[csl] = 0;
				UreaseEfficiency[csl]=0.0;
				UreaseDuration[csl]=0;

				if(FertMethod==1) fer_dept[csl] = 0.002;//conventional application
				if(FertMethod==2) FertDayRelease[csl]=90.0;//slow release
				if(FertMethod==3)						//nitrification inhibitor
				{
					NIefficiency[csl]=1.0;
					NIduration[csl] = 120;
				}
				if(FertMethod==4) FertOption=222;//auto-fert
				if(FertMethod==5) FertOption=333;//precision fertilization
				if(FertMethod==6) 
				{
					UreaseEfficiency[csl]=1.0;
					UreaseDuration[csl] = 120;
				}
				if(FertMethod==7) //sulphate
				{
					//FertOption=111;//fertigation
					//fscanf(fp, "%s", FertigationFile);
				}	
			}

			if(Option>100)
			{
				jdfer[csl] += (int)(SMC[31]);
				fer_dept[csl] *= (1.0 + SMC[32]);
				fer1[csl] *= (1.0 + SMC[33]);
				fer2[csl] *= (1.0 + SMC[33]);
				fer3[csl] *= (1.0 + SMC[33]);
				fer4[csl] *= (1.0 + SMC[33]);
				fer5[csl] *= (1.0 + SMC[33]);
				fer6[csl] *= (1.0 + SMC[33]);
				fer7[csl] *= (1.0 + SMC[33]);
			}
		}		
	}	
	else
	{
		if(fer_num==-1)
		{
			FertOption=111;//fertigation
			fscanf(fp, "%s", FertigationFile);
			if(irri_index>=100.0) FertOption=999; //with auto-adjusted irrigation index based on PET
		}
		else if (fer_num == -2)
		{
			FertOption = 222;//auto-fert

			for (csl = 1; csl <= 2; csl++)//always read in 2 fert for split application
			{
				fscanf(fp, "%d %f", &jdfer[csl], &fer_dept[csl]);
				fscanf(fp, "%f %f %f %f %f %f %f", &fer1[csl], &fer2[csl], &fer3[csl], &fer4[csl], &fer5[csl], &fer6[csl], &fer7[csl]);
				fscanf(fp, "%d %f %f %f %f %d", &FertMethod, &FertDayRelease[csl], &NIefficiency[csl], &NIduration[csl],
					&UreaseEfficiency[csl], &UreaseDuration[csl],&FertMethodApp[csl]);//fertmethodApp is 0,1,2,3 for surface, injected,incorporated and soon to be banded
				if (MODE == 1)
				{
					//FertMethod: 1- conventional, 2- Slow-release, 3- Nitrification inhibitor, 4- Soil-N-adjusted rate, 
					//5- Precision fertilization, 6-urease inhibitor, 7-sulphate, 

					FertDayRelease[csl] = 1;
					NIefficiency[csl] = 0.0;
					NIduration[csl] = 0;
					UreaseEfficiency[csl] = 0.0;
					UreaseDuration[csl] = 0;

					if (FertMethod == 1) fer_dept[csl] = 0.002;//conventional application
					if (FertMethod == 2) FertDayRelease[csl] = 90.0;//slow release
					if (FertMethod == 3)						//nitrification inhibitor
					{
						NIefficiency[csl] = 1.0;
						NIduration[csl] = 120;
					}
					if (FertMethod == 4) FertOption = 222;//auto-fert
					if (FertMethod == 5) FertOption = 333;//precision fertilization
					if (FertMethod == 6)
					{
						UreaseEfficiency[csl] = 1.0;
						UreaseDuration[csl] = 120;
					}
					if (FertMethod == 7) //sulphate
					{
						//FertOption=111;//fertigation
						//fscanf(fp, "%s", FertigationFile);
					}
				}

			}



		}
		else if(fer_num==-3) FertOption=333;//precision fertilization
		else
		{
			CString msa;
			msa.Format("Error in fertilizer input data in file %s", FERT);
			AfxMessageBox(msa);
			exit(0);
		}
	}
	
    fclose( fp );	

    return( 0 );
}

int class_model::read_in_manu(CString FCT40)
{
    FILE *fp;
    char  MANU[80];
    int   csl;

    sprintf(MANU, "%s\\manu-%d", FCT40, year);
    
    fp = fopen(MANU, "r");
    if ( fp == NULL )
    {
		char err[60];
		sprintf(err,"%s not found",MANU);
		MessageBox(NULL, err, "Error Message", 0);
		return( FILE_NOT_FOUND );
    }

    fscanf(fp, "%d", &man_num);
    for ( csl = 1; csl <= man_num; csl++ )
    {
		fscanf(fp, "%d %f %f %d %d %f", &jdman[csl], &ManureOrgC[csl], &manucn[csl], &ManureType[csl], &ManureMethod[csl], &ManureDepth[csl]);
		fscanf(fp, "%f %f %f %d %f %f %f %f %d %d", &ManureOrgN[csl], &ManureNH4[csl], &ManureNO3[csl], &manuAppHour[csl], &manuDM[csl], &manuPH[csl], &manPoolFrac[csl], &manPoolRate[csl], &useManPool[csl], &autoManure);//read in new manure parameters ... wasn't turned off

		if(manuDM[csl]<=0)
		{manuDM[csl]=40.0;}
		if(manuAppHour[csl]<=0)
		{manuAppHour[csl]=12;}
		if(manuPH[csl]<=0)
		{manuPH[csl]=7.0;}
		if(autoManure<=0)
		{
			autoManure = 0;
		}

		if(Option>100)
		{
			jdman[csl] += (int)(SMC[34]);
			manucn[csl] *= (1.0 + SMC[35]);
			ManureOrgC[csl] *= (1.0 + SMC[36]);
		}
    }
    fclose( fp );

    return( 0 );
}

int class_model::read_in_cut(CString FCT40)
{
    FILE *fp;
    char  GRAZ[80];
    int   csl;

    sprintf(GRAZ, "%s\\cut-%d", FCT40, year);
    
    fp = fopen(GRAZ, "r");
    if ( fp == NULL )
    {
		char err[60];
		sprintf(err,"%s not found", GRAZ);
		MessageBox(NULL, err, "Error Message", 0);
		return( FILE_NOT_FOUND );
    }
    fscanf(fp, "%d", &cut_num);
    for ( csl = 1; csl <= cut_num; csl++ )
    {
		fscanf(fp, "%d %f", &jdcut[csl], &CutFraction[csl]);
		CutFraction[csl] *= (1.0 + SMC[43]);

		if(CutFraction[csl]>1.0) CutFraction[csl] = 1.0;

		fscanf(fp, "%d", &CutPart[csl]);

		//yr_CutDemandC += CutAmount[csl];
    }
    fclose( fp );

    return( 0 );
}

int class_model::read_in_graz(CString FCT40)
{
	//The default average weights refered: cattle 753 kg; finishing steers 640 kg; cows 725 kg, and Bulls 1090 kg.

    FILE *fp;
    char  GRAZ[80];
    int   csl;

    sprintf(GRAZ, "%s\\graz-%d", FCT40, year);
    
    fp = fopen(GRAZ, "r");
    if ( fp == NULL )
    {
		char err[60];
		sprintf(err,"%s not found", GRAZ);
		MessageBox(NULL, err, "Error Message", 0);
		return( FILE_NOT_FOUND );
    }
    fscanf(fp, "%d", &gra_num);
    for ( csl = 1; csl <= gra_num; csl++ )
    {
		fscanf(fp, "%d %d %f %f %f %f %f %f %f %f %d %f %f %f", &jdgra1[csl],&jdgra2[csl], &AnimalHead[1][csl], &AnimalHead[2][csl], 
										&AnimalHead[3][csl], &AnimalHead[4][csl], &AnimalHead[5][csl], &hrs[csl],
										&AddFeed[csl], &FeedCN[csl], &Excreta[csl], &GrazBiomass[csl],&GrazCConsume[csl],&GrazCExcrete[csl]);


		if(FeedCN[csl]<=0.0) FeedCN[csl] = 30.0;

/*		
#ifdef MANURE
		AnimalHead[1][csl] /= MData.ManureFieldArea; //heads/ha
		AnimalHead[2][csl] /= MData.ManureFieldArea; 
		AnimalHead[3][csl] /= MData.ManureFieldArea;
		AnimalHead[4][csl] /= MData.ManureFieldArea;
		AnimalHead[5][csl] /= MData.ManureFieldArea;
#endif
*/
		if(Option>100)
		{
			for(int i=1;i<=5; i++) AnimalHead[i][csl] *= (1.0 + SMC[39]);
			
			jdgra2[csl] += (int)(SMC[40]);
			hrs[csl] *= (1.0 + SMC[41]);
		}
    }
    fclose( fp );

	//////////////////////////////////////////////////////////////////////////
	CString LiveFile;
	FILE *lf;
	char notes[100];
	int a;

	for (int oz = 1; oz <= gra_num; oz++ )
	{
		//herd
		TotalHeads[oz] = 0.0;
		for(a=1;a<=5;a++) 
			TotalHeads[oz] += AnimalHead[a][oz];

		//Food demand and forage C and N partitions
		total_C_demand[oz] = 0.0;

		for(a=1;a<=5;a++)//1 dairy, 2 beef, 3 swine, 4 sheep, 5 horse
		{
			if(AnimalHead[a][oz]>0.0)
			{			
				LiveFile.Format("%sLibrary\\Lib_livestock\\Livestock_%d.txt", ROOTDIR, a);
				lf=fopen(LiveFile, "r");
				if(lf==NULL) note(0,LiveFile);
				
				fscanf(lf, "%d %s", &AnimalCode[a], notes); 
				fscanf(lf, "%s %s", AnimalNames[a], notes);
				fscanf(lf, "%f %s", &Default_C_intake[a], notes);//kg C/head/day
				fscanf(lf, "%f %s", &Milk_C_fraction[a], notes);
				fscanf(lf, "%f %s", &Meat_C_fraction[a], notes);
				fscanf(lf, "%f %s", &Urine_C_fraction[a], notes);
				fscanf(lf, "%f %s", &Dung_C_fraction[a], notes);
				fscanf(lf, "%f %s", &Enteric_CH4_C_fraction[a], notes);
				fscanf(lf, "%f %s", &Respiration_C_fraction[a], notes);
				fscanf(lf, "%f %s", &Default_N_intake[a], notes);
				fscanf(lf, "%f %s", &Milk_N_fraction[a], notes);
				fscanf(lf, "%f %s", &Meat_N_fraction[a], notes);
				fscanf(lf, "%f %s", &Urine_N_fraction[a], notes);
				fscanf(lf, "%f %s", &Dung_N_fraction[a], notes);
				fscanf(lf, "%f %s", &Enteric_N2O_N_fraction[a], notes);
				fclose(lf);
				
				livestock_C_demand[a][oz] = Default_C_intake[a] * AnimalHead[a][oz];//kg C/ha
				total_C_demand[oz] += livestock_C_demand[a][oz];
			}
		}
	}

    return( 0 );
}

int class_model::read_in_plastic(CString FCT40)
{
    FILE *fp;
    char  WEED[80];
    int   sef, PlasM1, PlasD1, PlasM2, PlasD2;

    sprintf(WEED, "%s\\plastic-%d", FCT40, year);
    
    fp = fopen(WEED, "r");
    if ( fp == NULL ) note(0, WEED);
    
    fscanf(fp, "%d %d", &plastic_num, &plastic_method);
    	
    for ( sef = 1; sef <= plastic_num; sef++ )
    {
		fscanf(fp, "%d %d", &jdplastic1[sef], &jdplastic2[sef]);
		fscanf(fp, "%f", &FilmCoverF[sef]);
    }
    fclose( fp );

    return( 0 );
}


float class_model::day_zero()
{

// #define DEBUG_CBALANCE 1   // <— uncomment to enable debug columns

#ifdef DEBUG_CBALANCE
// DOC production (by source) and consumption (to CO2)
	day_doc_from_rcvl = 0.0;  // DOC from very labile litter (RCVL)
	day_doc_from_rcl = 0.0;  // DOC from labile litter (RCL)
	day_doc_from_rcr = 0.0;  // DOC from resistant litter (RCR)
	 day_doc_from_humads = 0.0;  // DOC produced inside decomp_humads (0.4/0.6 parts)
	day_doc_from_humus = 0.0;  // DOC produced by humus decomp (d_humus)
	 day_doc_from_manure = 0.0;  // if any explicit manure DOC channel
	 day_doc_prod_total = 0.0;  // convenience sum

	 day_doc_to_co2 = 0.0;  // DOC mineralized to CO2 (sum over layers)
	 day_dn_co2 = 0.0;  // if your DOC balloon emits via dn_co2day_co2, capture it here

	// CO2 routing checkpoints
	 day_co2_before_roll = 0.0;  // day_co2 value before end-of-day consolidation
	 day_cmine_before_roll = 0.0;// day_C_mine value before end-of-day consolidation
	 dCO2_pool_today = 0.0;  // (end_prof_co2 - ini_prof_co2) – net pool change today
	 dDOC_pool_today = 0.0;  // (end_prof_doc - ini_prof_doc)
#endif

	
	
	int i;

	wrcvl = 0.0;
	wrcl = 0.0;
	wrcr = 0.0;
	wcrb = 0.0;
	wcrhl = 0.0;
	wcrhr = 0.0;
	whumus = 0.0;
	winertC = 0.0;
	wtcavai = 0.0;
	day_co2 = 0.0;
	wCH4_C = 0.0;
	manureHour=0;
	
	//ch4_eb = 0.0;
	plant_day_ch4 = 0.0;
	day_ch4 = 0.0;

	//N_stress = 1.0;
	day_leachhu = 0.0;
	//day_leachun = 0.0;
	day_soil_nitrify = 0.0;	
	
	DTGA = 0.0;
	by_pass_no3 = 0.0;
	plant_day_ch4 = 0.0;
	ch4_prod = 0.0;
	ch4_prod1=0.0;
	ch4_prod2=0.0;
	//ch4_dif=0.0;
	ch4_day_oxid=0.0;
	//ch4_eb=0.0;
	plant_day_ch4=0.0;
	day_soil_an_n2o=0.0;
	day_soil_an_no=0.0;
	day_soil_n2=0.0;
	day_leach_NO3 = 0.0;
	day_leach_P = 0.0;
	day_runoff_P = 0.0;
	day_leach_urea = 0.0;
	by_pass_no3 = 0.0;
	day_soil_nh3 = 0.0;
	day_vol_nh3 = 0.0;
	day_IrriWater = 0.0;
	slurry_doc=0.0;
	
	straw_C = 0.0;
	//day_weednup = 0.0;
	//day_minen = 0.0;
	//day_assim = 0.0;
	day_pro_ch4_eb = 0.0;
	day_soil_denitrification = 0.0;
	//day_clay_N = 0.0;
	w_n2o = 0.0;
	day_addC = 0.0;
	day_nitrify_NO = 0.0;
	day_nitrify_N2O = 0.0;
	day_intercept = 0.0;
	day_snow_ev = 0.0;
	day_soilIce_ev = 0.0;
	day_pond_ev = 0.0;
	dfol_ev = 0.0;
	TotalSoilC = 0.0;
	//dsno3 = 0.0;
    //dsnh4 = 0.0;
	/*dsno3b = 0.0;
    dsnh4b = 0.0;
	dsno3c = 0.0;
    dsnh4c = 0.0;
	dsno3d = 0.0;
    dsnh4d = 0.0;
	dsno3e = 0.0;
    dsnh4e = 0.0;
	dsno3f = 0.0;
    dsnh4f = 0.0;*/
	day_leach_DOC = 0.0;
	rain_N = 0.0; 
	//day_rainN = 0.0;
	day_vol_nh3 = 0.0;
	day_addmc = 0.0;
	
	day_inC = 0.0;
	day_outC = 0.0;
	day_inN = 0.0;
	day_outN = 0.0;
	//day_assimN = 0.0;
	day_balance_ch4 = 0.0;
	SnowMelt = 0.0;
	hrfol_ev = 0.0;
	
	day_transp = 0.0;
	day_soil_ev = 0.0;
	day_bypass_influx = 0.0;
	day_leach_water = 0.0;
	day_tile_water = 0.0;
	day_Deep_Perc = 0.0;
	day_water_in = 0.0;
	ini_soil_water = 0.0;
	end_soil_water = 0.0;
	day_bypass_influx = 0.0;
	day_runoff = 0.0;
	//day_paddy_water_ev = 0.0;
	day_surplus_water = 0.0;
	//total_ice = 0.0;
	total_ice = 0.0;
	day_leach_urea = 0.0;
	day_inFertN = 0.0;
	day_inManureN = 0.0;
	day_inLitterN=0.0;
	day_inGrazeN = 0.0;
	day_inStubN = 0.0;
	
	day_inFertP = 0.0;
	day_inManureP=0.0;
	day_H2S_flux=0.0;
#ifdef ISOTOPE
	day_CO2_13=0.0;
	day_CO2_12=0.0;
	day_DOC_13=0.0;
	day_DOC_12=0.0;
	day_CH4_13=0.0;
	day_CH4_12=0.0;
	day_ch4_co2_pool=0.0;
	day_prod_CH4_13=0.0;
	day_prod_CH4_12=0.0;
	day_ch4_pool=0.0;
	day_oxid_CH4_13=0.0;
	day_oxid_CH4_12=0.0;
#endif	
	//day_inStub3N = 0.0;
	//day_inRootN = 0.0;
	day_inRainN = 0.0;
	
	day_deficit = 0.0;
	
	grazedN = 0.0;
	H_beef=0.0;
	H_dairy=0.0;
	H_sheep=0.0;
	H_pig=0.0;
	H_horse=0.0;
	H_hrs = 0.0;
	day_DNassimN = 0.0;
	day_irri = 0.0;
	
	grazFlag=0;
	till_flag=0;
	//dayG_N=0;
	
	//day_DWater = 1.0;
	day_C_mine =0.0;
	day_N_mine =0.0;
	day_N_assim =0.0;
	day_FreshWasteNH3=0.0;
	
	day_addrn=0.0;
	day_GWsuply=0.0;
	//day_RootDOC=0.0;
	
	root_dCO2 = 0.0;
	day_fineroot_N=0.0;
	day_fineroot_C=0.0;
	add_liq_N=0.0;
	
	day_runoff_N=0.0;
	day_runoff_C=0.0;
	day_ice_N=0.0;
	day_ice_doc=0.0;
	day_ice_n2o=0.0;
	day_ice_n2=0.0;
	day_irri_N=0.0;
	day_frostDOC=0.0;
	day_inert_C=0.0;
	ch4_pool=0.0;
	
	DayGrassCut=0.0;
	day_farm_to_field_N=0.0;
	day_farm_to_field_C=0.0;
	day_farm_to_field_H2O=0.0;
	day_farm_to_field_P=0.0;

	TTT = 0.0;
	wFreezedoc=0.0;
	soil_hete_CO2=0.0;
		
	day_GrazeC = 0.0;
	day_GrazeN = 0.0;
	IrriWater = 0.0;
	day_SoilWater=0.0;
	//dayPlantP=0.0;
	//day_ch4_doc_pool=0.0;
	day_RootInput_DOC=0.0;
	
	socmusle=0.0;
	sonmusle=0.0;
	nh4musle=0.0;
	no3musle=0.0;
	nh3musle=0.0;
	ureamusle=0.0;
	claynmusle=0.0;
	LabPmusle=0.0;
	AdsPmusle=0.0;
	OrgPmusle=0.0;
	//dayCropDeficit=0.0;
	day_SumPT = 0.0;
	DayAT=0.0;
	act_DayAT=0.0;
	rainfall=0.0;
	SurfaceWaterT=0.0;
	irri_flag = 0;
	drain_flag = 0;
	flood_end = 0;

	day_Root_DOC=0.0;
	day_SOM_DOC=0.0;
	day_CO2_prod=0.0;
	day_Root_CO2=0.0;
	day_SOM_CO2=0.0;
	day_H2_PROD=0.0;
	day_SOM_H2=0.0;
	day_ch4_H2_pool=0.0;
	day_DOC_prod=0.0;
	day_DOC_cons=0.0;
	DayPT2 = 0.0;
	DayPT0 = 0.0;
	day_indirect_n2=0.0;
	day_indirect_n2o=0.0;
	day_acetate=0.0;
	day_acetate_prod=0.0;
	day_acetate_cons=0.0;

#ifdef MANURE
	MData.day_house_evap=0.0;
	MData.day_house_no=0.0;
	MData.day_house_n2=0.0;
	MData.day_house_co2=0.0;
	MData.day_house_nh3=0.0;
	MData.day_house_n2o=0.0;
	MData.day_house_ch4=0.0;
	MData.day_bed_C=0.0;
	MData.day_bed_N=0.0;
	MData.day_floor_leach_water=0.0;
	MData.day_floor_leach_urea=0.0;
	MData.day_floor_leach_NH4=0.0;
	MData.day_floor_leach_NO3=0.0;
	MData.day_floor_leach_doc=0.0; 
	
	MData.day_gutter_co2=0.0;
	MData.day_gutter_nh3=0.0;
	MData.day_gutter_n2o=0.0;
	MData.day_gutter_n2=0.0;
	MData.day_gutter_no=0.0;
	MData.day_gutter_ch4=0.0;
	
	MData.day_lagoon_ch4=0.0;
	MData.day_lagoon_nh3=0.0;
	MData.day_lagoon_n2o=0.0;
	MData.day_lagoon_no=0.0;
	MData.day_lagoon_n2=0.0;
	MData.day_lagoon_EV=0.0;
	MData.day_lagoon_co2=0.0;

	MData.day_HouseOutputSolidC = 0.0;
    MData.day_HouseOutputSolidN = 0.0;
    MData.HouseToLagoonSOC =0.0;
	MData.HouseToLagoonSON=0.0;	

	MData.day_Compost_nh3=0.0;
	MData.day_compost_ch4=0.0;
	MData.day_compost_n2o=0.0;
	MData.day_compost_n2=0.0;
	MData.day_compost_no=0.0;
	MData.day_compost_EV=0.0;
	MData.day_compost_InRain=0.0;
	MData.day_compost_co2 =0.0;

	MData.day_digester_no =0.0;
	MData.day_digester_n2o =0.0;
	MData.day_digester_n2 =0.0;
	MData.day_digester_CO2 =0.0;
	MData.day_digester_nh3 =0.0;
	MData.day_digester_CH4=0.0;
	
	MData.day_compost_leach_H2O=0.0;
	MData.mm_UrineC[1]=0.0;
	MData.mm_UrineC[2]=0.0;
	MData.mm_UrineC[3]=0.0;
	MData.mm_DungC[1]=0.0;
	MData.mm_DungC[2]=0.0;
	MData.mm_DungC[3]=0.0;
	MData.mm_UrineN[1]=0.0;
	MData.mm_UrineN[2]=0.0;
	MData.mm_UrineN[3]=0.0;
	MData.mm_DungN[1]=0.0;
	MData.mm_DungN[2]=0.0;
	MData.mm_DungN[3]=0.0;

	MData.House_to_lagoon_C = 0.0;
	MData.House_to_lagoon_N = 0.0;
	MData.House_to_lagoon_H2O = 0.0;
	MData.House_to_lagoon_P = 0.0;

	MData.day_LOS_ch4=0.0;
	MData.day_LOS_n2o=0.0;
	MData.day_LOS_nh3=0.0;
	MData.day_LOS_LeachN=0.0;
	
	for(i=0; i<9; i++)
	{
	MData.day_runoff_MC[i]=0.0;
	MData.day_runoff_MIN[i]=0.0;
	MData.day_runoff_MON[i]=0.0;
	MData.day_runoff_MOP[i]=0.0;
	MData.day_market_MC[i]=0.0;
	MData.day_market_MIN[i]=0.0;
	MData.day_market_MON[i]=0.0;
	MData.day_market_MOP[i]=0.0;
	}

	MData.day_feedlot_runoff_WATER=0.0;
	MData.day_compost_runoff_WATER=0.0;

	for(i=0; i<24; i++)
	{
		MData.ToField[i] = 0.0;
	}
#endif
	
	for (i=0; i<=q; i++)
	{
	   //doc[i] = 0.0;

	   anvf[i] = 0.0;
	   ave_anvf[i] = 0.0;
	   day_O2[i] =0.0;
	   //soc[i] = 0.0;
	   //frost_doc[i] = 0.0;
	   doc_w[i] = 0.0; 

	   //denitrifier[i] = 0.0; 
	   no_w[i] = 0.0;
		n2o_w[i] = 0.0; 
		no2_w[i]= 0.0;
		no3_w[i] = 0.0; 
		assim2[i] = 0.0; 
		nh4_w[i]= 0.0;
		doc_d[i] = 0.0; 

		no_d[i]= 0.0;
		n2o_d[i] = 0.0; 
		n2_w[i] = 0.0; 
		no2_d[i]= 0.0;
		no3_d[i] = 0.0; 
		nh4_d[i]= 0.0;

		//day_layer_soil_ev[i] = 0.0;
		DayAverageWater[i]=0.0;
		//InputRoot_DOC[i]=0.0;
		day_H2_prod[i]=0.0;
		//day_ch4_CO2[i]=0.0;
		day_ch4_1[i]=0.0;
		day_ch4_2[i]=0.0;
		day_ch4_3[i]=0.0;

		day_nitrification[i]=0.0;
		day_denitrification[i]=0.0;
		O2_old[i] = 0.0;
		Eh_old[i] = 0.0;

#ifdef ISOTOPE
		CO2_12[i]=0.0;
		CO2_13[i]=0.0;
		delCH4[i]=0.0;
#endif
		H2[i]=0.0;
		

		for(int w=0; w<=24; w++)
		{
			OutWater[i][w] = 0.0;
			TileWater[i][w]=0.0;
			//day_water_in[i][h] = 0.0;
		}
	}

	day_root_resp=0.0;

	for(int zb=0; zb<=21; zb++)//was 7
	{
		dsurea[zb]=0.0;
		dsno3[zb] = 0.0;
		dsnh4[zb] = 0.0;
		dsClayN[zb]= 0.0;
		day_nitrif[zb]=0.0;
		day_denitrif[zb]=0.0;
		day_decomp[zb]=0.0;
		total_n2o[zb] = 0.0; //totalN2O in a layer
	}
	for(int z=0;z<=7; z++)
	{
		day_N_demand[z] = 0.0;
		day_fixN[z] = 0.0;
		//day_DWater[z] = 1.0;
		Day_C_growth[z]=0.0;
		dayG_grain[z]=0.0;
		dayG_root[z]=0.0;
		dayG_leaf[z]=0.0;
		dayG_stem[z]=0.0;
		dayG_pod[z] = 0.0;
		DayGrassCut_C[z] = 0.0;
		DayGrassCut_N[z] = 0.0;
				
		//day_CropN_air[z]=0.0;
		Day_GrowthN[z] = 0.0;
		day_plant_nh3[z] = 0.0;
		day_rco2[z] = 0.0;
		day_shoot_CO2[z] = 0.0;
		day_stem_CO2[z] = 0.0;
		ideal_DayCropC[z] = 0.0;
		root_doc[z]=0.0;
		
		day_need_N[z]=0.0;
		DayLeafSenes[z]=0.0;
		DayLeafSenesN[z] = 0.0;
		DayStemSenesN[z] = 0.0;
		DayRootSenesN[z] = 0.0;
		DayGrainSenesN[z] = 0.0;
		DayShootSenesN[z] = 0.0;
		DayStemSenes[z]=0.0;
		DayRootSenes[z]=0.0;
		DayGrainSenes[z]=0.0;
		day_P_demand[z]=0.0;

		day_graze_dung_C[z]=0.0;
		day_graze_dung_N[z]=0.0;
		day_graze_urine_C[z]=0.0;
		day_graze_urine_N[z]=0.0;
		day_graze_dung_P[z]=0.0;
		day_grass_consume[z] = 0.0;

		day_P_uptake[z] = 0.0;

	}

	return(0);
}

void class_model::zero_DayFlux(void)
{
	int l;
	for ( l = 1; l <= q; l++ )
	{
	    DayFlux[l] = 0.0;
	}

}



int class_model::read_in_flood(int MODE, CString FCT40)
{
    FILE *fp;
    char  FLOOD[80];
    int   i, junkd;

    sprintf(FLOOD, "%s\\flood-%d", FCT40, year);
    
    fp = fopen(FLOOD, "r");
    if(fp==NULL) note(0, FLOOD); 
    
    fscanf(fp, "%d", &flo_num);

    if ( flo_num > 0 )
    {
		for ( i = 1; i <= flo_num; i++ )
		{
			fscanf(fp, "%d %d %f %d", &jdflo1[i], &jdflo2[i], &flood_N[i], &MargenalFlood[i]);	
			//if(RiceDrySeeding==1&&i==1) jdflo1[i] += 40; 
		}
		wetland_flag = 1;
    }
	else
		wetland_flag = 0;

	//flood_pH = 7.0;

    fscanf(fp, "%d %f %f %f", &WaterControl, &WaterLeakRate, &WaterGetherIndex, &FloodWater_N);
	fscanf(fp, "%s", WT_file);
	fscanf(fp, "%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
									&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);
	fclose(fp);

	WaterGetherIndex = 1.5;
	WaterLeakRate *= 0.001; //mm -> m

	//WaterControl: 0-irrigation; 1-rainfed; 2-observed data; 3-empirical parameters

	if(WaterControl==0||WaterControl==1)
	{
	
	}
	else if(WaterControl==2) 
	{
		CreateObservedDayWT();
	}
	else if(WaterControl==3) 
	{
		m_IniWT *= 0.01;//cm -> m
		m_LWTceasingSurfFlow *= 0.01;
		m_LWTceasingGroungFlow *= 0.01;		
	}
	else
	{
		CString err;
		err.Format("Error on Water Control");
		AfxMessageBox(err);
		return(0);
	}
	
    return( 0 );
}

