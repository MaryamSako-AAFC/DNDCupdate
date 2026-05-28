#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "math.h"


class_model DData;


// These are nomrally set to 10 days standard. Experimenting with dynamic gernmination with some crops.		
int GermDays[100]={3,26,15,26,3,3,3,3,3,3,3,
					   3,0,3,3,3,3,3,3,3,3,
					   3,3,3,3,3,3,3,3,3,3,
					   3,3,3,3,3,3,3,3,3,3,
					   3,3,26,3,3,3,15,3,3,3,
					   3,3,3,3,3,3,3,3,3,3,
					   3,3,3,3,3,3,3,3,3,3,
					   3,3,3,3,3,3,3,3,3
					   ,3,3,3,3,3,3,3,3,3,3,
						3,3,3,3,3,3,3,3,3,3 };//adjust crop 47 to have 15 germination days
			 
float WinterWheat_LimitiT = 1.0;//was 0.1
int root_q;

void class_model::crop_growth(int scale, float till_fact)
{
	int ccwc;
	if(year==1&&jday==1)
	{
	GermDays[3]=26;
	GermDays[1]=26;
	//GermDays[8] = 26;
	//GermDays[90] = 26;
	//GermDays[3] = 3;
	//GermDays[1] = 3;
	//GermDays[8] = 3;
	
	}


	


	for(ccwc=1; ccwc<=CropNumbers; ccwc++)
	{

		

		//Crop parameters initiation
		TotalCropBiomass = 0.0;	

		if (ccwc == 1)//was messing up the year 2 accumulators without this for NEE and EcoCO2
		{
			dPlantBiomass = 0.0;
			sum_shoot_CO2 = 0.0;
			sum_stem_CO2 = 0.0;
		}
		cropht = 0.5;
		WiltFlag[ccwc] = 0;
		crop_T_demand[ccwc]=max_TDD[ccwc];
		CropWaterDemand[ccwc] = wreq[ccwc] * maxmn[ccwc] * plantcn[ccwc] / 0.4 / 1000.0 / 10000.0;
		if(ini_N_fix[ccwc]>1.0) ini_N_fix[ccwc]=1.0;
		if(ini_N_fix[ccwc]>0.0) max_N_fix[ccwc] = ini_N_fix[ccwc]* maxmn[ccwc];//max_N_fix[ccwc] = (1.0 - 1.0 / (ini_N_fix[ccwc]*ini_N_fix[ccwc])) * maxmn[ccwc];
		else max_N_fix[ccwc] = 0.0;

		if(crop[ccwc]==1||crop[ccwc]==7||crop[ccwc]==65||crop[ccwc]==13||crop[ccwc]==27|| crop[ccwc] == 90) C_type[ccwc] = 4;//determines C3 or C4 species for later.
		else C_type[ccwc] = 3;
  		ddupn[ccwc] = 0.0;
		OptCropC[ccwc] = GrainYield[ccwc] / grain[ccwc];//sets optimum C for plant and fractions.
		OptGrainC[ccwc] = OptCropC[ccwc] * grain[ccwc];//sets for grain
		OptLeafC[ccwc] = OptCropC[ccwc] * leaf[ccwc];//sets for Leaf
		OptStemC[ccwc] = OptCropC[ccwc] * stem[ccwc];//sets for Stem
		OptRootC[ccwc] = OptCropC[ccwc] * root[ccwc];//sets for root
float lai_index1[100]={2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
					   2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
					   2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
					   2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
					   2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
					   2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
					   2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
					   2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5
						,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,
						2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5 };

//for calculating Green LAI - needs to better correlate with actual leaf weight changes.
float laiPGIFactor;
//laiPGIFactor= -26.101*pow(PGI[ccwc],3)+56.392*pow(PGI[ccwc],2)-41.709*PGI[ccwc]+11.513;
//laiPGIFactor = -7.0714 * pow(PGI[ccwc], 2) + 8.7798 * pow(PGI[ccwc], 1) - 1.7112;
laiPGIFactor = 7.6094 * pow(PGI[ccwc], 3)-21.942 * pow(PGI[ccwc], 2)+17.7 * PGI[ccwc] -3.3559;
//laiPGIFactor= -5.3498 * pow(PGI[ccwc], 2) + 6.2833 * PGI[ccwc] - 0.8419; //was using this Canada-ET
if(PGI[ccwc]<0.6) laiPGIFactor=1.0;
laiPGIFactor= min(1.0,max(laiPGIFactor,0.0));
//laiPGIFactor = 1.0;


//laiPGIFactor = 1.0;//testing new leafSenscence
if (PGI[ccwc] > 0.80)
{
//	crop_Leafsenescence(ccwc);
}
//end test



float cropLAIScalar = OptGrainC[ccwc];//introducing a generalized scalar that helps put LAI per crop type into the appropriate range based on leaf biomass for grain crops and total biomass for forages.
if (OptGrainC[ccwc] < 1000)
{
	cropLAIScalar = OptCropC[ccwc]*.5;
}
//cropLAIScalar = 2000.0;
if (PGI[ccwc] > 0.0)
{
	if (PGI[ccwc] < 0.2)
	{
		startOptLeafC[ccwc] = OptLeafC[ccwc];//so that OptLeafC isn't reworked in case of changing harvest index
	}
	if (startOptLeafC[ccwc] == 0.0)startOptLeafC[ccwc] = OptLeafC[ccwc];

	if (PGI[ccwc] >= 0.75 && crop[ccwc]!=3)//was ==1.0 //simple mechanism to set in a senescence for leaf 
	{
		if (lai[ccwc] > YrG_lai[ccwc]) YrG_lai[ccwc] = lai[ccwc];	//keeping track of maximum LAI achieved for the season in YrG_lai[ccwc];
		lai[ccwc] = lai[ccwc] * .99;//reduces green LAI to correspond with sensence. //was 0.95 for faster Green LAI die off. 
		//crop_Leafsenescence(ccwc);
	}
	else
	{
		//lai[ccwc] = (Leaf_Wt[ccwc]) / 1000.0 * LAImax[ccwc]*laiPGIFactor;//lai_index[ccwc]LAI a function of leaf, stem and grain wt multiplied by LAI index.//lai_index1[crop[ccwc]] //was developing this for leaf senescence.
		//lai[ccwc] = (Leaf_Wt[ccwc]) / 1000.0 * 2000 / cropLAIScalar * LAImax[ccwc] * laiPGIFactor;//lai_index[ccwc]LAI a function of leaf, stem and grain wt multiplied by LAI index.//lai_index1[crop[ccwc]]//+ Stem_Wt[ccwc] + Grain_Wt[ccwc] //for barley project was using stem and grain wt for LAI calculation
		if (PGI[ccwc] >= 0.75 && crop[ccwc] == 3) {
			//&& crop[ccwc] == 3
			//crop_Leafsenescence(ccwc);//turned this off with new biomass
			lai[ccwc] = lai[ccwc] * .95;
		}
		else {
			lai[ccwc] = ((Leaf_Wt[ccwc]) / (startOptLeafC[ccwc] * 0.5)) * LAImax[ccwc];
			lai[ccwc] = ((Leaf_Wt[ccwc] / 0.45) * 20.0) / 10000.0;//was 30
		}
		//float redLAIFactor;
	//	redLAIFactor= (((startOptLeafC[ccwc] / 0.45) * 20.0) / 10000.0)/LAImax[ccwc];
		//lai[ccwc] = lai[ccwc]/redLAIFactor;
		lai[ccwc] = max(lai[ccwc], 0.0);
		
		if (lai[ccwc] > LAImax[ccwc]) 
		{
			LAImax[ccwc] = lai[ccwc];
		}
		//lai[ccwc] = min(LAImax[ccwc],max(lai[ccwc], 0.0));

		if (lai[ccwc] > YrG_lai[ccwc]) YrG_lai[ccwc] = lai[ccwc];//keeping track of of maximum LAI achieved.
		
	}
}
//lai[ccwc] = (Leaf_Wt[ccwc]+Stem_Wt[ccwc] + Grain_Wt[ccwc]) / 1000.0;///testing


//keeps track of when crop is reaching flowering and first pod.		


//read from file first root respiration bug test
/*
if(year==1&&jday==1)
						{
						CString TESTFILE;
						FILE *pFile=NULL;

						TESTFILE.Format("%s\\Record\\ReturnWater.txt", OUTPUT);
						pFile = fopen (TESTFILE,"w");
						fprintf(pFile, "jday,year,ReturnW\n");
						fprintf(pFile, "%1d,%1d,%7.4f\n",jday,year,0);
						fclose (pFile);
						}
if(year==1&&jday==1)
						{
						CString TESTFILE;
						FILE *pFile=NULL;

						TESTFILE.Format("%s\\Record\\WaterDemand.txt", OUTPUT);
						pFile = fopen (TESTFILE,"w");
						fprintf(pFile, "jday,year,layer, LayerWaterDemand, LayerWaterDeficit,RootDensity,RootLength,PPTw,wiltptw,waterLayer\n");
						
						fclose (pFile);
						}
*/

//root resp file
/*
				//rootMResp=0.4;
				//rootNewResp=0.007;

if(PGI[ccwc]==0.0 || jday==1)
{

	
CString TESTFILE;
FILE *pFile=NULL;
TESTFILE.Format("%s\\Record\\RootResp.txt", OUTPUT);//Root
pFile = fopen (TESTFILE,"r");
	if(pFile==NULL)
	{
		CString note;
		note.Format("Can not create file %s", TESTFILE);
		AfxMessageBox(note);
		exit(0);

	}
fscanf(pFile, "%f %f",&rootMResp, &rootNewResp);//&OldResp, &newResp
fclose (pFile);
}
*/




/*
//read from file first flowering and pod PGI

if(PGI[ccwc]==0.0 || jday==1)
{

	
CString TESTFILE;
FILE *pFile=NULL;
TESTFILE.Format("%s\\Record\\flowering.txt", OUTPUT);//flowering
pFile = fopen (TESTFILE,"r");
	if(pFile==NULL)
	{
		CString note;
		note.Format("Can not create file %s", TESTFILE);
		AfxMessageBox(note);
		exit(0);

	}
fscanf(pFile, "%f %f %f",&flower, &pod, &seedFill);//&flower, &pod & see
fclose (pFile);
}

//sets range for flowering and pod filling
if(PGI[ccwc]>flower && floweringDay[ccwc]==0)
{
	floweringDay[ccwc]=jday;
}
if(PGI[ccwc]>pod && podDay[ccwc]==0)
{
podDay[ccwc]=jday;
}
if(PGI[ccwc]>seedFill && seedFillDay[ccwc]==0)
{
seedFillDay[ccwc]=jday;
}
//read from file first flowering and pod PGI
*/

		
		/*if(jday==1)
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
		}*/

		//initiate crop growth
		if(crop_flag[ccwc]==0 && autoPlantF==0)//if(seed[ccwc]==0) 
		{			
			ini_crop(scale, ccwc);		//checks daily to see if jdseed == jday	
		}

		if (crop_flag[ccwc] == 0 && autoPlantF == 1 && PerennialFlag[1] == 0 && snow_pack == 0.0 && jday<153 && crop[ccwc]!=47 && crop[ccwc] != 2)//if(seed[ccwc]==0) //&& jday>105
		{
			ini_cropAuto(scale, ccwc);		//checks daily to see if jdseed == jday	
		}
		if (crop_flag[ccwc] == 0 && autoPlantF == 1 && PerennialFlag[1] == 1 && snow_pack == 0.0 && jday<153 && crop[ccwc] != 47 && crop[ccwc] != 2)
		{
			ini_cropAuto(scale, ccwc);		//checks daily to see if jdseed == jday	

		}
		if (crop_flag[ccwc] == 0 && autoPlantF == 1 && PerennialFlag[1] == 0  && crop[ccwc] == 47 || crop_flag[ccwc] == 0 && autoPlantF == 1 && PerennialFlag[1] == 0 && crop[ccwc] == 2)
		{
			ini_crop(scale, ccwc);		//checks daily to see if jdseed == jday	
		}
		else
		{
			//ini_crop(scale, ccwc);		//checks daily to see if jdseed == jday	

		}
		
		

		if(crop_flag[ccwc]==1 )//if crop is being grown
		{
			seed[ccwc]++;//advance the days since seed

	
		
			crop_days[ccwc]++;//crop days counter
			
			if(seed[ccwc]==1) pDFCUM[ccwc]=1.0;
			if(seed[ccwc]==1){ germCount=1;}
			if(seed[ccwc]==1) maturity_flag[ccwc] = 0;//if seed is the first day then the crop maturity is set to zero
									
			if(maturity_flag[ccwc]==0)//section for when crop is not at manturity
			{
				
				if (crop[ccwc] == 2)
				{
					if (crop_days[ccwc] < 2)
					{
						float blah;
						blah = 1.0;

					}

				}


				growth_stage(ccwc);//define PGI[cwcc], dat_TDD[cwcc], TDD[cwcc]

				crop_N_demand(ccwc, till_fact);//define day_N_demand[ccwc] (daily crop N demand, kg N/ha)

				//optimum temperature
				
				if (seed[ccwc] > GermDays[crop[ccwc]])
				{
					root_develop(ccwc);//define root depth, m (no use at this moment)
					root_density(ccwc);
				}
				
				//need this hear
				// Calculate the water competition factor (0-1) for each crop based on root weight fraction
				water_CompFactor();//Theo
				
				// Update crop height based on LAI
				crop_Height();//Theo
				leafTemp(ccwc);
				// Calculate light stress factor (0-1) for each crop based on height and LAI
				light_CompFactor();//Theo
				
				
				if(day_N_demand[ccwc]>0.0)//when demand for N is zero.
				{
					water_demand(DayPET, ccwc);//sets PPT[ccwc] (daily potential plant transpiration, m)				
								
					crop_PT[ccwc] += PPT[ccwc];
					day_SumPT += PPT[ccwc];				
					DayPT0 += PPT[ccwc]; 

					if(crop[ccwc]==46) irri_close = 1;
					else irri_close = 0;



					if(PPT[ccwc]>0.0)
					{
						//PPT[ccwc] = (wreq[ccwc]/250)*PPT[ccwc]; //gives some control over water stress
						//need to put proper water req otherwise it's going to overestimate ET but still want water uptake to effect production

						
						APT[ccwc] = crop_pretranspiration(irri_close, PPT[ccwc], ccwc);
						if(year==11 && jday==270)
						{
							float blah;
							blah = 1.0;
						}
						
						//float blah,blah1;
						//blah = crop_pretranspiration(irri_close, PPT[ccwc], ccwc);
						//blah1 = 1.0;
						//if (APT[ccwc] > PPT[ccwc]) APT[ccwc] = PPT[ccwc];
						
						
						//Brian insert for calculating appropriate water stress
						
						float PPTA;
						PPTA = wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0;//m water
						//if(PPTA>DayPETCROP[ccwc])
						//PPTA=DayPETCROP[ccwc];

						float leafTrans, WStressFactor,WStressFactor2,wreqFactor;
						/*
						leafTrans = PPT[ccwc] * (1.0 - exp(-0.5 * lai[ccwc]));//DayPET
						if (lai[ccwc] > 1.0)
						{
							PPT[ccwc] = leafTrans;//this might need to be rethought because its not working with kc Crop at this point for calculating water stress. 
						}
						else
						{
						PPT[ccwc]=wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0;
						}
						*/
						wreqFactor = wreq[ccwc] / 250;//was 250

						WStressFactor = pow(APT[ccwc] / PPT[ccwc],wreqFactor);//PPTA//wreq[ccwc] / 250
						WStressFactor2 = pow((APT[ccwc] / PPT[ccwc]),wreqFactor);
						WStressFactor = (APT[ccwc] / PPT[ccwc]);
						WStressFactor2 = (APT[ccwc] / PPT[ccwc]);
						WStressFactor = min(1.0, max(WStressFactor, 0.0));
						WStressFactor2 = min(1.0, max(WStressFactor2, 0.0));
						PPTA = PPT[ccwc];

						//excess moisture stress on barley grain yields
						if (crop[ccwc] == 888 && PGI[ccwc] > 0.25 && PGI[ccwc] < 0.45 && WStressFactor < 1.0) //don't turn on for breton or normandin barley measurements//wait
						{
							day_DWater[ccwc] = powf(WStressFactor2, 1.0);//0.0 + 0.85*(APT[ccwc]/PPT[ccwc]);//powf(APT[ccwc] /PPTA,1.3);/// PPT[ccwc];//PPTA;//actual plant transpiration / potential plant transpiration //PPT[ccwc] instead of PPTA ///PPTA,1.50
							crop_water_stress[ccwc] += powf(WStressFactor2, 1.0);//0.0 + 0.85*(APT[ccwc]/PPT[ccwc]); //powf(APT[ccwc] /PPT[ccwc],1.3);//day_DWater[ccwc];//Geoff had this at 1.5


							float changeHi;

							changeHi = -0.028 * (WStressFactor2)+0.028;
							changeHi = min(1.0, max(changeHi, 0.0));

							if ((grain[ccwc] - changeHi) > 0.05)
							{
								grain[ccwc] -= changeHi;
								stem[ccwc] += changeHi / 2;
								leaf[ccwc] += changeHi / 2;
							}
							else
							{
								stem[ccwc] += (grain[ccwc] - 0.05) / 2;
								leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
								grain[ccwc] = 0.05;
							}
						}


						if (crop[ccwc] == 888 && PGI[ccwc]>0.15 && PGI[ccwc]<0.25 && irri_index==0.0)//was off for normandin
						{
							//test to see if rooting depth water content is near/at/above field capacity

							int root_layer = (int)(root_length[ccwc] / h[1]);
							if (root_layer < 1) root_layer = 1;
							if (root_layer > q) root_layer = q;
							float avgWaterContent = 0.0;
							float avgFieldCapacity = 0.0;

							for (int il = 1; il <= root_layer; il++)
							{
								avgWaterContent += day_wfps[il];
								avgFieldCapacity += fldcap[il];

							}
							avgWaterContent = avgWaterContent / root_layer;
							avgFieldCapacity = avgFieldCapacity / root_layer;

							if (avgWaterContent >= (avgFieldCapacity * 0.70))
							{
								cumWaterStress += 1;
							}
							else
							{
								cumWaterStress = 0;
							}
							if (cumWaterStress >= 7)
							{
								float excessStress = 2.0 / float( cumWaterStress);
								stuntGrowth = stuntGrowth*0.97;
								stuntGrowth = min(1.0, max(0.3, stuntGrowth)); //was some variance. 0.5 for normadin...0.3 for breton
							}
							
						}

						if(crop[ccwc]==1||crop[ccwc]==43||crop[ccwc]==908) //silage corn
						{
							if(stuntGrowth<1) PPTA*=1.0;
						}

						if(crop[ccwc]==1 && PGI[ccwc]>0.45 && PGI[ccwc]<0.60 && WStressFactor<1.0 ||crop[ccwc]==43 && PGI[ccwc]>0.45 && PGI[ccwc]<0.60 && WStressFactor<1.0|| crop[ccwc] == 908 && PGI[ccwc]>0.45 && PGI[ccwc] < 0.60 && WStressFactor < 1.0)//|| crop[ccwc] == 18 && PGI[ccwc]>0.45 && PGI[ccwc] < 0.65 && WStressFactor < 1.0
						{
						
						day_DWater[ccwc] = powf(WStressFactor,1.7);//was 1.2 default for corn simulations//0.0 + 0.85*(APT[ccwc]/PPT[ccwc]);//powf(APT[ccwc] /PPTA,1.3);/// PPT[ccwc];//PPTA;//actual plant transpiration / potential plant transpiration //PPT[ccwc] instead of PPTA ///PPTA,1.50
						crop_water_stress[ccwc] += powf(WStressFactor2,1.7);//was 1.2 //0.0 + 0.85*(APT[ccwc]/PPT[ccwc]); //powf(APT[ccwc] /PPT[ccwc],1.3);//day_DWater[ccwc];//Geoff had this at 1.5
						
							float changeHi;

							changeHi = -0.028 * powf(WStressFactor2,1.7)+0.028;//should base this on Morrison et al., 2006
							changeHi = min(1.0, max(changeHi, 0.0));

							if ((grain[ccwc] - changeHi) > 0.05)
							{
								grain[ccwc] -= changeHi;
								stem[ccwc] += changeHi / 2;
								leaf[ccwc] += changeHi / 2;
							}
							else
							{
								stem[ccwc] += (grain[ccwc] - 0.05) / 2;
								leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
								grain[ccwc] = 0.05;
							}
						
						}
						else if(crop[ccwc]==6 && PGI[ccwc]>0.01 && PGI[ccwc]<0.3)
						{
							day_DWater[ccwc] = powf(WStressFactor,1.0);
							crop_water_stress[ccwc] += powf(WStressFactor2,1.0);
						}
						else if(crop[ccwc]==6 && PGI[ccwc]>0.50 && PGI[ccwc]<0.60)
						{
							day_DWater[ccwc] = powf(WStressFactor,1.0);
							crop_water_stress[ccwc] += powf(WStressFactor2,1.0);
						}
						else if(crop[ccwc]==3 && PGI[ccwc]>(GrainFill[ccwc]-0.25) && PGI[ccwc]<GrainFill[ccwc])//currently turned off. 
						{
						
						day_DWater[ccwc] = powf(WStressFactor2,1.0);//0.0 + 0.85*(APT[ccwc]/PPT[ccwc]);//powf(APT[ccwc] /PPTA,1.3);/// PPT[ccwc];//PPTA;//actual plant transpiration / potential plant transpiration //PPT[ccwc] instead of PPTA ///PPTA,1.50
						crop_water_stress[ccwc] += powf(WStressFactor2,1.0);//0.0 + 0.85*(APT[ccwc]/PPT[ccwc]); //powf(APT[ccwc] /PPT[ccwc],1.3);//day_DWater[ccwc];//Geoff had this at 1.5
						float tempSoyStress;
						

						
						cumFlowerPrecip += precipitation*1000;
						tempSoyStress = 1743.45 + 24.67 * cumFlowerPrecip;
						soyFlowerWStress = tempSoyStress / 4200.0;
						int root_layer = (int)(root_length[ccwc] / h[1]);
						if (root_layer > WTL||day_DWater[ccwc]>0.99) soyFlowerWStress = 1.0;

						soyFlowerWStress = min(1.0, max(0.0, soyFlowerWStress));


						//if Rooting Layer is in WTL then soyFlowerWStress = 1.0;

						/*
						float changeHi;

							changeHi=-0.028*(WStressFactor2)+0.028;//should base this on Morrison et al., 2006
							changeHi=min(1.0,max(changeHi,0.0));
				
							if((grain[ccwc]-changeHi)>0.05)
								{
								grain[ccwc]-=changeHi;
								stem[ccwc]+=changeHi/2;
								leaf[ccwc]+=changeHi/2;
								}
							else
								{
								stem[ccwc]+= (grain[ccwc]-0.05)/2;
								leaf[ccwc]+= (grain[ccwc]-0.05)/2;
								grain[ccwc]=0.05;
								}
						*/
							
						//day_DWater[ccwc] =powf(APT[ccwc]/PPT[ccwc],1.0);
						//crop_water_stress[ccwc] +=powf(APT[ccwc]/PPT[ccwc],1.0);//PPT[ccwc]
						}
						else if(crop[ccwc]==89||crop[ccwc]==10)
						{
						day_DWater[ccwc] =powf(WStressFactor2,1.0);
						crop_water_stress[ccwc] += powf(WStressFactor2,1.0);
						}
						else if (crop[ccwc] == 98 && PGI[ccwc] > 0.45 && PGI[ccwc] < 0.65 && WStressFactor < 1.0)
						{
							day_DWater[ccwc] = powf(WStressFactor2, 0.15);
							crop_water_stress[ccwc] += powf(WStressFactor2, 0.15);


						}
						else
						{
						day_DWater[ccwc] =powf(WStressFactor,1.0);//0.15 + 0.85*(APT[ccwc]/PPT[ccwc]);//powf(APT[ccwc] /PPTA,0.5);/// PPT[ccwc];//PPTA;//actual plant transpiration / potential plant transpiration //PPT[ccwc] instead of PPTA // Geoff had 0.7  /PPTA,0.7
						crop_water_stress[ccwc] +=powf(WStressFactor2,1.0);//0.15 + 0.85*(APT[ccwc]/PPT[ccwc]);//powf(APT[ccwc] /PPT[ccwc],0.50);//day_DWater[ccwc]; //this keeps track of the days of crop//at 0.7
						}
						
						crop_water_stress_days[ccwc]++;
						if(crop_water_stress_days[ccwc]<crop_water_stress[ccwc])
							crop_water_stress_days[ccwc]=crop_water_stress[ccwc];

						if (PPTactual[ccwc] > 0)
						{
							crop_PPT[ccwc] += PPT[ccwc] / PPTactual[ccwc];
						}
					    crop_PPT_days[ccwc]++;
						}





					else
					{
						APT[ccwc] = 0.0;
						day_DWater[ccwc] = 1.0;
					}
					if (crop[ccwc] == 3 && PGI[ccwc] > GrainFill[ccwc] && soyFlowerWStress < 1.0 && irri_index==0.0)
					{
						float changeHi, tempGrainF, tempStemF, tempLeafF, tempHI, newGrainF;//temporary fractions + tempHarvest Index
						tempGrainF = grain[ccwc];
						tempStemF = stem[ccwc];
						tempLeafF = leaf[ccwc];
						tempHI = tempGrainF / (tempGrainF + tempStemF + tempLeafF);
						newGrainF = tempGrainF * soyFlowerWStress;
						changeHi = tempGrainF - newGrainF;
						changeHi = min(1.0, max(changeHi, 0.0));

						if ((grain[ccwc] - changeHi) > 0.05)
						{
							grain[ccwc] -= changeHi;
							stem[ccwc] += changeHi / 2;
							leaf[ccwc] += changeHi / 2;
							soyFlowerWStress = 1.0;//resets soyFlowerStress to be a 1 time allocation.
						}
						else
						{
							stem[ccwc] += (grain[ccwc] - 0.05) / 2;
							leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
							grain[ccwc] = 0.05;
						}

					}
					//Total_PT += APT[ccwc];
					
					//brian testing to see if water demand is met.
					if(APT[ccwc]==PPT[ccwc]&&irri_index>0.0)
					{
						day_DWater[ccwc]=1.0;
					}

					
					/* was trying to alleviate the water stress issue with NT
					if(crop[ccwc]==1 || crop[ccwc]==43)
					{
						if(stuntGrowth<1.0)
						{
							day_DWater[ccwc]=pow(day_DWater[ccwc],(1+(1-stuntGrowth)));
						}
					}
					*/
					day_N_demand2[ccwc] = day_N_demand[ccwc] * day_DWater[ccwc];//daily N demand adjusted by water stress  (day_Dwater[ccwc])
					soilWaterStress=0.0;
					//is this necessary..recalculate water stress?
					
					/*
					if(PPT[ccwc]>0)day_DWater[ccwc]=powf((APT[ccwc] /PPT[ccwc]),0.25);//brian recalculate for reporting proper water stress
					else
					{
						APT[ccwc] = 0.0;
						day_DWater[ccwc] = 1.0;
					}
					*/
					//test
					
					///
					if (Leaf_Wt[ccwc] == 0 && PGI[ccwc] > 0.3 && PerennialFlag[ccwc]==0)//
					{
						day_N_demand2[ccwc] = 0.0;
						day_nup[ccwc] = 0.0;

					}
					if (day_N_demand2[ccwc] > 0.0)
					{
						if (year == 11 && jday == 270)
						{
							float blah;
							blah = 1.0;
						}

						n_uptake_by_crop(ccwc);//define day_nup[ccwc] (actual daily N uptake from soil, kg N/ha) and N_stress[ccwc]
					}
					else
						day_nup[ccwc] = 0.0;

					if (day_nup[ccwc] > day_N_demand2[ccwc])
					{
						float blah;
						blah = 1.0;

					}
					double ExtractW;
					if (day_N_demand2[ccwc] > 0.0)
					{
						double Fdj = (day_nup[ccwc] + day_fixN[ccwc]) / day_N_demand2[ccwc];
						ExtractW = PPT[ccwc] * (Fdj);//was APT
					}
					else
					{
						PPT[ccwc] = 0.0;
						ExtractW = 0.0;
					}

					//double ExtractW = PPT[ccwc] * (Fdj);//was APT
					if (PPT[ccwc] > 0.0)
					{
						double ActualTrans,ActualTrans2;
						//PPT[ccwc] = (wreq[ccwc]/250)*PPT[ccwc]; //gives some control over water stress
						//need to put proper water req otherwise it's going to overestimate ET but still want water uptake to effect production
						//ActualTrans = crop_pretranspiration(irri_close, ExtractW, ccwc);
						//ActualTrans2 = crop_transpiration(irri_close, ExtractW, ccwc);
						APT[ccwc] = crop_transpiration(irri_close, ExtractW, ccwc);
						//float blah;
						//blah = 1.0;

						/*
						ActualTrans2 = ActualTrans / ExtractW;
						if (ActualTrans2 < 1.0)
						{
							ExtractW = ExtractW * (1.0 + (1.0 - ActualTrans2));
							APT[ccwc] = crop_transpiration(irri_close, ExtractW, ccwc);
							float blah;
							blah = 1.0;

							//APT[ccwc] = ActualTrans2;//crop_transpiration(irri_close, ExtractW, ccwc);

						}
						else
						{
							APT[ccwc] = crop_transpiration(irri_close, ExtractW, ccwc);
						//	APT[ccwc] = ActualTrans2; // crop_transpiration(irri_close, ExtractW, ccwc);
						}
						*/
					}
					else
					{
						APT[ccwc] = 0.0;
						day_DWater[ccwc] = 0.0;
					}
					/*
					//Adjust APT[ccwc] based on actual N taken //Returns the excess water that is removed from initial crop transpiration back to top 10 layers (fraction).
						if(day_nup[ccwc]>0.0&&((day_nup[ccwc]+day_fixN[ccwc])/day_N_demand2[ccwc])<0.99)//+day_fixN[ccwc]
					{
						float Fdj = (day_nup[ccwc]+day_fixN[ccwc]) / day_N_demand2[ccwc];
								
						float ReturnW = APT[ccwc] * (1.0 - Fdj); 

						
						//if(ReturnW>0)
						//{
						
						//CString TESTFILE;
						//FILE *pFile=NULL;
						//TESTFILE.Format("%s\\Record\\waterTable.txt", OUTPUT);//OUTPUTBatchFileName
						//pFile = fopen (TESTFILE,"a");
						//fprintf(pFile, "%1d,%1d,%7.4f\n",jday,year,ReturnW*1000);
						
						
						//fclose (pFile);


						//}
						

						APT[ccwc] -= ReturnW;
						for(int i=1; i<=10; i++)
						{
							water[1][i] += (0.1 * ReturnW);
						}						
					}
					*/

					crop_AT[ccwc] += APT[ccwc]; //actual accumulative plant water uptake, m
					act_DayAT += APT[ccwc];//sum up daily actual water uptake by crops, m

					// NH3 uptake by and release from canopy 
					nh3_uptake_release(lai, &day_soil_nh3, PlantTakeN, maxmn, leaf_water, cropht, base_nh3,
											day_N_demand2, day_nup, day_fixN, day_DWater, day_plant_nh3, &yr_NH3_deposit, ccwc);

					total_crop_N(ccwc);//define Day_GrowthN[ccwc] (actual daily plant-gained N and plantn[ccwc] (actual plant accumulative N, kg N/ha)
					
					if(PerennialFlag[ccwc] == 1  )//perennial crops
					{
						
					
						//biomass_N_partitionSoyBean(ccwc);
						biomass_N_partition_per(ccwc);
					}
					else//annual crops
					{
						if (crop[ccwc]!=3 && crop[ccwc]!=90)
						{
							biomass_N_partition_per(ccwc);
						}
						else 
						{

							biomass_N_partition(ccwc);//soybean and corn 90 partitioning. 
						}
					}
				}
				else
				{
				PPT[ccwc]=0.0;//Brian test added if NDemand<0.0;
				}
				//define crop damage by weather events
				if(wind_damage_flag>0.0) weather_damage(0, 0.17, ccwc);
				if(hail_event>0.0) weather_damage(1, hail_event, ccwc);
				if(horricane_event>0.0) weather_damage(2, horricane_event, ccwc);

				/*
				if(seed[ccwc]>GermDays[crop[ccwc]])
				{
				root_develop(ccwc);//define root depth, m (no use at this moment)
				root_density(ccwc);
				}
				*/
				crop_N_stress[ccwc] += N_stress[ccwc];
				crop_N_stress_days[ccwc]++; 

				if(crop_N_stress_days[ccwc]<crop_N_stress[ccwc])
				crop_N_stress_days[ccwc]=N_stress[ccwc];

				if(Root_Wt[ccwc]>0.0)
					root_respir(ccwc);//define root_doc[ccwc]

				//define plant respiration
				float leafGLAI;
				leafGLAI = -0.0085 * pow(PGI[ccwc], 2) + 0.1769 * PGI[ccwc];
				if (PGI[ccwc] < 0.5)
				{
					leafGLAI = 0.3;
				}
				else
				{
					//leafGLAI = 0.025;
				}


				//note shootNewResp = leaf + stem respiration and reported under Leaf Respiration. 
				leafGLAI = min(1.0, max(0.0, leafGLAI));
				TotalCropBiomass = (Grain_Wt[ccwc]+Leaf_Wt[ccwc]+Stem_Wt[ccwc]+Root_Wt[ccwc]+Pod_Wt[ccwc]);	
				float TotalAGBiomass = ( dayG_stem[ccwc]+dayG_grain[ccwc]);
				float ShootpBiomass = dayG_leaf[ccwc] * shootNewResp[ccwc];//  Leaf_Wt[ccwc] * leafGLAI + 0.0 * Grain_Wt[ccwc];//LEAF + GRAIN CO2; ///turned off Leaf from this portion.
				float TotalAGBiomass2 = (dayG_stem[ccwc] + dayG_grain[ccwc] + dayG_leaf[ccwc]) * shootNewResp[ccwc];
				float TotalAGBiomass3 = (Day_C_growth[ccwc] - dayG_root[ccwc]) * shootNewResp[ccwc];
				//float ShootpBiomass = 5.0*dayG_leaf[ccwc] *shootNewResp[ccwc];//  Leaf_Wt[ccwc] * leafGLAI + 0.0 * Grain_Wt[ccwc];//LEAF + GRAIN CO2; ///turned off Leaf from this portion.
				float podResp;
				podResp = 0.55;

				if (crop[ccwc] == 3)
				{

					//ShootpBiomass = Leaf_Wt[ccwc] * leafGLAI ;//LEAF + GRAIN CO2; ///to account for PODs + 0.0*Grain_Wt[ccwc]*1.4
					podResp = 0.85;
				}
				//rootMResp=0.007;//enable when not using the read from file option maintenance resp
				//rootNewResp=0.4;//enable when not using the read from file option 
				float PGIndex,dayGROOT;
				PGIndex = PGI[ccwc];
				dayGROOT = dayG_root[ccwc];
				if(TotalCropBiomass>0.0&&crop_flag[ccwc]==1&&air_temp>0.0)
				{
					

						//old values
					/*
						if (crop[ccwc] == 11 || crop[ccwc] == 12)
						{
							day_shoot_CO2[ccwc] = 5.0 * (dayG_grain[ccwc] + dayG_leaf[ccwc]) * (1.0 - PGI[ccwc]) + 0.001 * (Leaf_Wt[ccwc] + Grain_Wt[ccwc]);//0.9
							day_stem_CO2[ccwc] = 5.0 * dayG_stem[ccwc] * (1.0 - PGI[ccwc]) + 0.001 * Stem_Wt[ccwc];//0.9
							day_rco2[ccwc] = 5.0 * dayG_root[ccwc] * (1.0 - PGI[ccwc]) + 0.001 * Root_Wt[ccwc];//0.9
						}
						else
						{
							float FAT = air_temp / 50.0;
							day_shoot_CO2[ccwc] = 0.03 * ShootpBiomass * (1.0 - PGI[ccwc]) * FAT;//0.015 * ShootpBioma						
							if (LandUse == 6) day_stem_CO2[ccwc] = 0.001 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;
							else day_stem_CO2[ccwc] = 0.03 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;
							day_rco2[ccwc] = 0.9 * dayG_root[ccwc] * (1.0 - PGI[ccwc]) + 0.001 * Root_Wt[ccwc];
						}
						*/
					
					
					if(crop[ccwc]==11||crop[ccwc]==12)
					{
						day_shoot_CO2[ccwc] = 5.0 * (dayG_grain[ccwc]+dayG_leaf[ccwc]) * (1.0 - PGI[ccwc]) + 0.001 * (Leaf_Wt[ccwc] + Grain_Wt[ccwc]);//0.9
						day_stem_CO2[ccwc] = 5.0 * dayG_stem[ccwc] * (1.0 - PGI[ccwc]) + 0.001 * Stem_Wt[ccwc];//0.9
						day_rco2[ccwc] = 5.0 * dayG_root[ccwc] * (1.0 - PGI[ccwc]) + 0.009 * Root_Wt[ccwc];//0.9
						if(day_rco2[ccwc]<0)day_rco2[ccwc]=0.0;
					}
					else
					{
					    //else day_stem_CO2[ccwc] = 0.1 * shootNewResp[ccwc] * (dayG_stem[ccwc]) * (1.0 - PGI[ccwc]) + shootMResp[ccwc] * (Stem_Wt[ccwc])+podResp*dayG_grain[ccwc] ;/
						
						float FAT = pow(air_temp / 50.0,2.0);

						//FAT = 1.0 / (1 + exp(8 * (PGI[ccwc] - 0.75)))*0.05;
						//FAT = 1.0 / (1 + exp(8 * (PGI[ccwc] - 0.5)))*0.25;
						/*
						day_shoot_CO2[ccwc] = (0.15*ShootpBiomass*lai[ccwc] + 0.01 * Leaf_Wt[ccwc] * shootMResp[ccwc])*FAT;// + 0.1 * dayG_grain[ccwc] * shootMResp[ccwc]) * FAT;//0.015 * ShootpBioma			//changed respiration from 0.03 to 0.21 to up grain portion of CO2		//0.28	//LEAF Portion * lai[ccwc]   /
						if(LandUse==6) day_stem_CO2[ccwc] = 0.001 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;
						else day_stem_CO2[ccwc] = (2.5 * shootNewResp[ccwc] * (TotalAGBiomass) + 0.2* (Grain_Wt[ccwc]+Stem_Wt[ccwc]) *shootMResp[ccwc]) * FAT;//0.9 //day_stem_CO2[ccwc] = 0.03 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;0.7 0.0017 ///STEM Portion * (1.0 - PGI[ccwc]))
						if (dayG_root[ccwc] < 0.0)dayG_root[ccwc] = 0.0;
						if (maturity_flag[ccwc] == 1)PGIndex = 1.0;
						day_rco2[ccwc] = (10.0*rootNewResp[ccwc] * dayGROOT * (1.0 - PGIndex) + rootMResp[ccwc] * Root_Wt[ccwc]*1.0)*FAT ;// 0.5 and 0.009
						if(day_rco2[ccwc]<0)day_rco2[ccwc]=0.0;
						*/

						
						day_shoot_CO2[ccwc] = (5.00 * ShootpBiomass * (1.0 - PGI[ccwc])+ 0.1*Leaf_Wt[ccwc]*(lai[ccwc]) *shootMResp[ccwc] + 0.1 * dayG_grain[ccwc] * shootMResp[ccwc]) * FAT;//0.015 * ShootpBioma			//changed respiration from 0.03 to 0.21 to up grain portion of CO2		//0.28	//LEAF Portion * lai[ccwc]   /+ 0.1 * dayG_grain[ccwc] * shootMResp[ccwc]
						if (LandUse == 6) day_stem_CO2[ccwc] = 0.001 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;
						else day_stem_CO2[ccwc] = (1.0 * shootNewResp[ccwc] * (dayG_stem[ccwc]) * (1.0 - PGI[ccwc]) ) * FAT ;//0.9 //day_stem_CO2[ccwc] = 0.03 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;0.7 0.0017 ///STEM Portion * (1.0 - PGI[ccwc]))
						if (dayG_root[ccwc] < 0.0)dayG_root[ccwc] = 0.0;
						if (maturity_flag[ccwc] == 1)PGIndex = 1.0;
						day_rco2[ccwc] = (10.0*rootNewResp[ccwc] * dayGROOT * (1.0 - PGIndex) + rootMResp[ccwc] * Root_Wt[ccwc]*1.0 )*FAT;// 0.5 and 0.009
						if(day_rco2[ccwc]<0)day_rco2[ccwc]=0.0;
						
						FAT = 1.0 / (1 + exp(50 * (PGI[ccwc] - 0.9)));
						if (crop[ccwc] == 2 )
						{
							
							/* empirical fit
							day_shoot_CO2[ccwc] = max( 0.4*(0.00778*(Leaf_Wt[ccwc]+Stem_Wt[ccwc]+Grain_Wt[ccwc]+Root_Wt[ccwc])+0.18803*air_temp),0);
							day_stem_CO2[ccwc] = max(0.3 * (0.00778 * (Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc] + Root_Wt[ccwc]) + 0.18803 * air_temp), 0);
							day_rco2[ccwc] = max(0.3 * (0.00778 * (Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc] + Root_Wt[ccwc]) + 0.18803 * air_temp), 0);;
							*/


							
							float day_AGCO2_live = 0.0;
							float day_AGCO2_maint = 0.0;
							day_AGCO2_live = 1.0 * TotalAGBiomass2 * FAT;
							day_shoot_CO2[ccwc] = day_AGCO2_live * leaf[ccwc]/(leaf[ccwc]+stem[ccwc])* air_temp*0.1 + (0.01 * Grain_Wt[ccwc] * shootMResp[ccwc]) * FAT;//+ (0.05 * Grain_Wt[ccwc] * shootMResp[ccwc])*FAT
							day_stem_CO2[ccwc] = day_AGCO2_live * (stem[ccwc])/(leaf[ccwc]+stem[ccwc]) * air_temp*0.1*FAT;
							day_rco2[ccwc] = 5.0*dayG_root[ccwc] * rootNewResp[ccwc] * FAT* air_temp*0.05 + rootMResp[ccwc] * Root_Wt[ccwc] * 0.01*FAT;
							

							//day_rco2[ccwc] = (10.0 * rootNewResp[ccwc] * dayGROOT * (1.0 - PGIndex) + rootMResp[ccwc] * Root_Wt[ccwc] * 1.0);
							//day_rco2[ccwc] = 1.0 * (rootMResp[ccwc] * Root_Wt[ccwc]) * FAT * air_temp * 0.05;

						}

						/*
						day_shoot_CO2[ccwc] = (1.00 * ShootpBiomass * (1.0 - PGI[ccwc]) + 0.05 * Leaf_Wt[ccwc] * (lai[ccwc]) * shootMResp[ccwc] * (1.0 - PGI[ccwc]) / 0.6) * FAT;//0.015 * ShootpBioma			//changed respiration from 0.03 to 0.21 to up grain portion of CO2		//0.28	//LEAF Portion * lai[ccwc]   /+ 0.1 * dayG_grain[ccwc] * shootMResp[ccwc]
						if (LandUse == 6) day_stem_CO2[ccwc] = 0.001 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;
						else day_stem_CO2[ccwc] = (1.0 * shootNewResp[ccwc] * (dayG_stem[ccwc]) * (1.0 - PGI[ccwc]) + 0.005 * (Stem_Wt[ccwc]) * (lai[ccwc]) * shootMResp[ccwc] * (1.0 - PGI[ccwc]) / 0.6) * FAT;//0.9 //day_stem_CO2[ccwc] = 0.03 * Stem_Wt[ccwc] * (1.0 - PGI[ccwc]) * FAT;0.7 0.0017 ///STEM Portion * (1.0 - PGI[ccwc]))
						if (dayG_root[ccwc] < 0.0)dayG_root[ccwc] = 0.0;
						if (maturity_flag[ccwc] == 1)PGIndex = 1.0;
						day_rco2[ccwc] = (5.0 * rootNewResp[ccwc] * dayGROOT * (1.0 - PGIndex) + rootMResp[ccwc] * Root_Wt[ccwc] * 0.5 * (1.0 - PGI[ccwc]) / 0.6) * FAT;// 0.5 and 0.009
						if (day_rco2[ccwc] < 0)day_rco2[ccwc] = 0.0;
						*/
						
					}	
					
					
				}
				else
				{
					day_shoot_CO2[ccwc] = 0.0;
					day_stem_CO2[ccwc] = 0.0;
					day_rco2[ccwc] = 0.0;
				}
		
				sum_shoot_CO2 += day_shoot_CO2[ccwc];
				sum_stem_CO2 += day_stem_CO2[ccwc];
				day_root_resp += day_rco2[ccwc];

		


				dPlantBiomass += Day_C_growth[ccwc];
				
				if(Day_C_growth[ccwc]<=0.0)
				{
//					Root_Wt[ccwc] -= 0.05*day_rco2[ccwc];//was causing an issue with perrenial root decomposition.
				}

		



			}//end of if(maturity_flag[ccwc]==0)

			//Crop maturity/harvest
			if(PerennialFlag[ccwc]==1)//if perrenial cropping
			{
				float cDRMX1,cHRMX1,pDFMX1,cTMX1,cRTMP,hRIH,hRID;
				//pDF crop population death coeffiicent % fraction of death per day
				//cTT state of cold tolerance oC
				//cDRMX rate of dehardening oC d-1
				//cHRMX rate of hardening oC d-1
				//pDFMX plant population death rate per day per oC
				//cTMX maximum cultivar threshold for temperature
				//cRTMP crown temperature.
				
				cDRMX1=0.82;
				cHRMX1=0.184;//rate of hardening //default 0.184 //.134
				pDFMX1=0.108;
				cTMX1=-15.0;

				cDRMX1 = cDRMX[ccwc];
				cHRMX1= cHRMX[ccwc];//rate of hardening //default 0.184 //.134
				pDFMX1 = pDFMX[ccwc];
				cTMX1 = cTMX[ccwc];


				pDF[ccwc]=1.0;

/* //output for testing alfalfa interm parmeteres
   CString TESTFILE;
   FILE *pFile=NULL;
   TESTFILE.Format("%s\\Record\\alfalfa.txt",OUTPUT);
   pFile=fopen(TESTFILE,"r");
   fscanf(pFile, "%f %f %f %f",&cHRMX,&pDFMX,&cTMX,&cDRMX);
   fclose(pFile);
*/






				cRTMP=temp[1];//set crown temperature to be equal to first layer soil temperature.
				//cRTMP=min(cRTMP,minTemp);
				//Rate of Hardening oC per Day
				if(cRTMP<=15.0)
				{
					hRIH=min(1-((cRTMP-10)/10),1)*cHRMX1*-1;//hardening rate
					hRID=0.0;//dehardening set to zero
				}
				else //Rate of Dehardening oC per Day
				{
					hRID=max(-1,(5-(20-cRTMP))/5*-1)*cDRMX1;//dehardening rate
					hRIH=0.0;//hardening set to zero
				}
				//Cold Tolerance Threshold
				cTT[ccwc]=max(cTMX1,min(0,cTT[ccwc]+(hRIH-hRID)));
				//Plant Population death rate.
				pDF[ccwc]=max(0.0,min(0.99,pDFMX1 * max(0,(cTT[ccwc]-cRTMP))));//plant pop death factor


				
					
				
				if(crop[ccwc]==10)
				{	
					pDFCUM[ccwc]*=(1-pDF[ccwc]);
					pDFCUM[ccwc]=max(0.02,pDFCUM[ccwc]);
					winterKillRed=pDFCUM[ccwc];
					
					if (cTMX1 <= -25.0)
					{
						winterKillRed = 1.0;//no winterkill effect
					}
					/*
					if(pDFCUM[ccwc]<0.74)
					{
					winterKillRed=-1.29993*pow(pDFCUM[ccwc],2)+2.2772*pDFCUM[ccwc]-0.0235;
					}
					else
					{
						winterKillRed=1.0;
					}
					*/
				  //  pDFCUM[ccwc]=min(1.0,max(0.0,pDFCUM[ccwc]));
				}
				else pDFCUM[ccwc]=1.0;

				if(jday>=300 && jday<=365 && crop[ccwc]==10)
				{
					winterCrown+=cRTMP;
					if(cRTMP<cTMX1)
					{
						winterCrownDays+=1;
					}

				}
				if(jday>=1 && jday<=100 && crop[ccwc]==10)
				{
					springCrown+=cRTMP;
					if(cRTMP<cTMX1)
					{
						springCrownDays+=1;
					}
				}

				


				


				

				//if(jday>jdcut[cut_num] && jday <= (30+jdcut[cut_num]))
				//{
					
					

					

				//}
				if(PGI[ccwc]>=1.0||TDD[ccwc]>=max_TDD[ccwc])//||plantn[ccwc]>=maxmn[ccwc])//seed[ccwc]>=364|| testing to see if PGI or TDD is at maximum and then set maturity flag to 1 to stop growing
				{					
					maturity_flag[ccwc]=1;
					vernal[ccwc]=0;
					maturity_flag[ccwc]=0;
				
				
					//seed[ccwc] = 1;
					//seed[ccwc] = 0; //set to 12 to not trigger the counter for TDD growth but maybe should set to zero?
				//	crop_days[ccwc] = 0;//set to 12 to not trigger counter for TDD growth
					
					
					//crop_days[ccwc] = 1;
				//	PGI[ccwc] = 0.0;//set to zero
				//	TDD[ccwc] = 0.0;			//set to zero		
				}
				if (autoHarvestF == 1 && PerennialFlag[ccwc]==1)
				{
					autoHarvPer=1;
				}
				float perCutGDD;
				
				if (cut_num == 0 && crop_days[ccwc]<jday)// no cuts yet and planted "Establishment year 1st cut"
				{
					perCutGDD = 650;
				}
				else if (cut_num == 0)//no cuts but not planted this year "Production year 1st cut"
				{
					perCutGDD = 450;
				}
				else//cut_num > 0  "Establishment or Production year 2nd+ cut"
				{

					perCutGDD = 520;
				}


				//need to decide here which perennial GDD we should be testing for.
				if (year == 30 && jday == 187|| year == 30 && jday == 188)
				{
					float blah;
					blah = 2.0;
				}
				//if(autoHarvPer==1 && TDD[ccwc]>=max_TDD[ccwc]*0.85 && jday>jdcut[cut_num])
				if(autoHarvPer==1 && perGDDSinceLastCut>perCutGDD && jday>jdcut[cut_num] && jday<(fallFrost1) )//adding cutting events //perCut1EstGDD=650 ,perCut1ProdGDD = 450; perCut2ProdGDD = 520    (cut_num==1),perGDDSinceLastCut=0. lastFrost jday
				{
					if (year == 30 && jday == 187)
					{
						float blah;
						blah = 2.0;
					}

					cut_num+=1;	
					CutPart[cut_num]=6;
					CutFraction[cut_num]=0.8;
					jdcut[cut_num]=jday+1;
					perGDDSinceLastCut = 0;//reset perrenial GDD counter
				}
				/*
				if (jday == fallFrost1 && autoHarvPer==1 && PGI[ccwc]>0.51)
				{

					cut_num += 1;
					CutPart[cut_num] = 6;
					CutFraction[cut_num] = 0.8;
					jdcut[cut_num] = jday + 1;
					perGDDSinceLastCut = 0;//reset perrenial GDD counter

				}
				*/
				int az;
				for ( az = 1; az <= cut_num; az++ )//counting through the cuts for each potential planted crop
				{if(jdcut[az]==jday)//if there is a cut on that day
					{
					maturity_flag[ccwc]=0;//set maturity to zero to allow regrowth
					//PGI[ccwc] = 0.50;
					//TDD[ccwc] = max_TDD[ccwc]/2;

					

					if(PGI[ccwc]>0.324)
					{
					PGI[ccwc] = 0.324;//PGI to pre-grain filling
					TDD[ccwc] = max_TDD[ccwc]*.324;//TDD to the same as PGI

					}
					
					seed[ccwc] = 10;//seed to after growing
					crop_days[ccwc] = 10;
					perRegrow[ccwc]=1;
					/*
					float nRemoved;
					if(CutPart[1]==6)
					{
						
						nRemoved=0.0;
						nRemoved+=GrainN[1] * CutFraction[1];
						nRemoved+=LeafN[1]*CutFraction[1];
						nRemoved+=StemN[1]*CutFraction[1];
						
					}
					


					plantn[ccwc]-=nRemoved;
					*/
					}
				}
				/*
				if(maturity_flag[ccwc]==1)//might not need this for vernalization
				{
					//crop_flag[ccwc] = 0;
					
					maturity_flag[ccwc]=0;
					seed[ccwc] = 12;
					crop_days[ccwc] = 12;
					PGI[ccwc] = 0.49;
					TDD[ccwc] = max_TDD[ccwc]*.49;
					//PGI[ccwc] = 0.0;
					//TDD[ccwc] = 0.0;
					vernDays=0;
				}
				*/
				if(jday==180)//365
				{
				if(vernal[ccwc]==0)
				{
					winterKill[ccwc]=winterKillRed;
				}
				}
				
				if(air_temp<-4.0 && PGI[ccwc]>0.2 && vernal[ccwc]==0 && jday>120)//a crude vernalization counter to see if the crop is done growing should limit this by temperature.
					{
					
					float cropHeight; //(cm. Taken from Vanderzaag Alfalfa Dataset 2018)
					cropHeight=(Leaf_Wt[ccwc]+Stem_Wt[ccwc]+Grain_Wt[ccwc])/0.4/10*0.1541;
					maturity_flag[ccwc]=1;
					crop_senescence(ccwc);
					maturity_flag[ccwc]=0;
					seed[ccwc] = 10;//12
					crop_days[ccwc] = 10;//12
					PGI[ccwc] = 0.324;//supposed to be .324 for ley
					TDD[ccwc] = max_TDD[ccwc]*0.324;
					vernal[ccwc]=60;
					
					if(crop[ccwc]==10||crop[ccwc]==5||crop[ccwc]==4||crop[ccwc]==12||crop[ccwc]==11)
					{
					perRegrow[ccwc]=1;//makes all subsequent years of growth be the regrowth phase
					}
					else if(crop[ccwc]==89)
					{
					perRegrow[ccwc]=1;
					}
					else
					{
						perRegrow[ccwc]=1;
					}
					

					//winterKill=pDFCUM[ccwc];
					/*
					winterKill=winterKillRed;
					
					if(pDFCUM[ccwc]==1.0)
					{
						winterKill=1.0;
					}
					*/
					
					}
				if(vernal[ccwc]>0)
				{
				//	vernal[ccwc]-=1;
				}
				if(PGI[ccwc]>=0.50)//vernal[ccwc]>0
				{
					vernal[ccwc]=0;
					//vernal[ccwc]=vernal[ccwc]-1;
					/*
					if(vernal[ccwc]==0)
					{
					maturity_flag[ccwc]=0;
					seed[ccwc] = 12;
					crop_days[ccwc] = 12;
					PGI[ccwc] = 0.0;//supposed to be .324 for ley
					TDD[ccwc] = max_TDD[ccwc]*0.0;
					perRegrow[ccwc]=0;

					}
					*/
				}

			
				/*
				if(jday==365 && crop[ccwc]==89)
				{
					maturity_flag[ccwc]=1;
				crop_senescence(ccwc);
					maturity_flag[ccwc]=0;
					seed[ccwc] = 12;
					crop_days[ccwc] = 12;
					PGI[ccwc] = 0.0;
					TDD[ccwc] = 0;
					vernal[ccwc]=1;
					perRegrow[ccwc]=0;
				}
				*/
				/*
				if(vernDays==29)
				{
					maturity_flag[ccwc]=0;
					seed[ccwc] = 12;
					crop_days[ccwc] = 12;
					PGI[ccwc] = 0.0;
					TDD[ccwc] = 0.0;
					//PGI[ccwc] = 0.0;
					//TDD[ccwc] = 0.0;
					vernDays=0;
				}
				
				if(air_temp<0.0 && vernDays<29 && maturity_flag[ccwc]==1)//a crude vernalization counter to see if the crop is done growing should limit this by temperature.
					{
					vernDays+=1;	
				
					}
					/*
			   /*
				
				if(maturity_flag[ccwc]==1 )//might not need this for vernalization
				{
					//crop_flag[ccwc] = 0;
					
					vernDays+=1;
					
					if(vernDays>30)
					{
					maturity_flag[ccwc]=0;
					seed[ccwc] = 12;
					crop_days[ccwc] = 12;
					PGI[ccwc] = 0.49;
					TDD[ccwc] = max_TDD[ccwc]*.49;
					//PGI[ccwc] = 0.0;
					//TDD[ccwc] = 0.0;
					vernDays=0;
					}
				}
				*/				


				/*
				if(seed[ccwc]==364)
				{
					maturity_flag[ccwc]=0;
					jdseed[ccwc]=0;
					crop_flag[ccwc] = 0;
					seed[ccwc] = 11;
				    crop_days[ccwc] = 11;
					PGI[ccwc] = 0.0;
					TDD[ccwc] = 0.0;
				}
				*/

			  if(maturity_flag[ccwc]==1)//||air_temp<=0.0
				{
				  

					TotalCropBiomass = (Grain_Wt[ccwc]+Leaf_Wt[ccwc]+Stem_Wt[ccwc]+Root_Wt[ccwc]);
					if(TotalCropBiomass>0.0) crop_senescence(ccwc);
				}
			}
			else
			{ 
			//========================================================CoverCrop
			
			if (CoverCrop[ccwc] == 1 && air_temp < FrostKill[ccwc] && crop[ccwc] == 47)
			{//routine will harvest a cover crop if its below the frostKill temperature.
				//maturity_flag[ccwc] = 1;
				
				maturity_flag[ccwc] = 1;
				crop_harvesting(scale, ccwc);
				CoverCrop[ccwc] == 0;


				//CoverCrop[ccwc] =0;
				//seed[ccwc] = 0;

				//PGI[ccwc] = 1.0;
				//crop_senescence(ccwc);

			}
			if ( crop[ccwc] == 47 && PGI[ccwc]==1.0)
			{
				maturity_flag[ccwc] = 1;
				CoverCrop[ccwc] == 0;
				crop_senescence(ccwc);
			}

				
			if(autoHarvestF==1 && crop[ccwc]!=47 && crop[ccwc]!=2)
				{
				//Brian added these options to autoharvest if air_temp goes below zero. Needs a more robust mechanism
				//need to figure out if harvest after jdseed[ but before jdtil[
				
				
				if (jdtil[2] == jday+1|| jdtil[1] == jday + 1||jdtil[3] == jday + 1|| jdtil[4] == jday + 1|| jdtil[5] == jday + 1|| jdtil[6] == jday + 1|| jdtil[7] == jday + 1|| jdtil[8] == jday + 1)
				{
					maturity_flag[ccwc] = 1;
					if (PGI[ccwc] < 0.50) { 
						stub1 += Grain_Wt[ccwc];
						Grain_Wt[ccwc] = 0.0; }//might need to put this Grain_Wt added into residue.
					crop_harvesting(scale, ccwc);
					GermDays[3] = 26;
					GermDays[1] = 26;
				//	GermDays[8] = 26;

				}
				

				if (crop[ccwc] == 6 && air_temp <= -6.0 && PGI[ccwc] < 1.0 && PGI[ccwc]>0.25 || crop[ccwc] == 57 && air_temp <= -6.0 && PGI[ccwc] < 1.0 && PGI[ccwc]>0.25)// || crop[ccwc] == 8 && air_temp <= -7.0 && PGI[ccwc] < 1.0 && PGI[ccwc]>0.1)// || crop[ccwc] == 8 && air_temp <= -4.0 && PGI[ccwc] < 1.0 && PGI[ccwc]>0.1)
					{
					maturity_flag[ccwc]=1;

					if (Grain_Wt[ccwc] > 0.0)
					{
						stub1 += Grain_Wt[ccwc];
						Grain_Wt[ccwc] = 0.0;
					}



					crop_harvesting(scale, ccwc);
					GermDays[3]=26;//reset necessary for old germination code. Should turn off soon.
					GermDays[1]=26;
				//	GermDays[8] = 26;

				
					}

				//should likely be minimum air temperature //was min_temp=-1.0 for soybean

					if(crop[ccwc]==1 && min_temp<=-5.0 && PGI[ccwc]<1.0 && PGI[ccwc]>0.25||crop[ccwc]==3 && min_temp<= -3.0 && PGI[ccwc]<0.8 && PGI[ccwc]>0.25|| crop[ccwc] == 8 && min_temp <= -5.0 && PGI[ccwc]>0.25)// || crop[ccwc] == 8 && air_temp <= -2.0 && PGI[ccwc] < 1.0 && PGI[ccwc]>0.05)
					{
						maturity_flag[ccwc]=1;
						if(crop[ccwc]==3 && PGI[ccwc]>0.50|| crop[ccwc] == 1 && PGI[ccwc] > 0.80 || crop[ccwc] == 8 && PGI[ccwc] > 0.80)//|| crop[ccwc] == 8 && PGI[ccwc] > 0.80
							{
							maturity_flag[ccwc]=1;
							maturityDay[ccwc]=jday;
							}
							else
							{
								if (Grain_Wt[ccwc] > 0.0)
								{
									stub1 += Grain_Wt[ccwc];
									Grain_Wt[ccwc] = 0.0;
								}
							
							}
							crop_harvesting(scale, ccwc);
						GermDays[3]=26;
						GermDays[1]=26;
						//GermDays[8] = 26;
					}
					
				//end autoharvest
			}
				if(PGI[ccwc]>0.85 && crop[ccwc]==3)//for maturity was 0.85
				{
				//crop_senescence(ccwc);//	was on for AgMIP soybean
				}

				if(plantn[ccwc]>=maxmn[ccwc] && PerennialFlag[ccwc]==0||PGI[ccwc]>=1.0||TDD[ccwc]>=max_TDD[ccwc])
				{
					
					maturity_flag[ccwc]=1;
				//	crop_senescence(ccwc);
					if(crop[ccwc]==1||crop[ccwc]==43)//doesn't work to put crop in. //crop[ccwc] == 8
					{
					GermDays[crop[ccwc]]=-99;
					}
					if(IrriRice_flag==1) rice_maturity_flag=1;
				
					//keeps track of when crop reaches physical maturity.
					if(PGI[ccwc]==1.0 && maturityDay[ccwc]==0 &&jdseed[ccwc]<jday)
					{
					maturityDay[ccwc]=jday;
					}

			if(autoHarvestF==1)
					{
					//Brian put for autoharvest
						if(cropYieldDry[ccwc]>(grow_days[ccwc]*.03))//0.08//sets the harvest day to 8% of the days it took to reach maturity. Typically 10-14 days after reaching maturity.
						{
							crop_harvesting(scale, ccwc);
							GermDays[3]=26;
					GermDays[1]=26;
				 //  GermDays[8] = 26;
							
						}
						cropYieldDry[ccwc]=cropYieldDry[ccwc]+1;
					//end autoharvest
					}
				}

				if((seed[ccwc]-1)==grow_days[ccwc])
				{
					germCount=1;
				GermDays[3]=26;//resetting for germination code
				GermDays[1]=26;
				//GermDays[8] = 26;
				//GermDays[3] = 3;//resetting for germination code
				//GermDays[1] = 3;
				//GermDays[8] = 3;

				//crop_days[ccwc]=1;
					crop_harvesting(scale, ccwc);}
			}	
		}
	}//end of crop loop
		


	//actual daily evaporation should not be higher than the pre crop coefficient evap?
	act_DayPE = (DayPET - act_DayAT)* evapMulti;//daily potential soil evaporation, m  //reducing overall evap here.//CROP[ccwc]
	
	
	//had this before crop coeficient put in.
	
	/*
	float oldEvap;
	
	//oldEvap=DayPETmod-act_DayAT;

	oldEvap=DayPET*.75;
	if(act_DayPE>oldEvap) 
	{
	  act_DayPE=oldEvap;
	}//brian
	*/
	if(act_DayPE<0.0)
	{
		//float blah;
		act_DayPE=act_DayAT*0.05;
		//act_DayPE = 0.0;
	} //
					
}

void class_model::crop_N_demand(int ccwc, float till_fact)
{
    float GrassBiomassProductivity, GrassCProductivity;
	float T_stress=1.0;

	//temperature stress, using Beta distribution curve, Yan and Hunt 1999 (Annals of Botany 84:607-614).				
	float TTmax = 40.0, TTopt = OptimumT[ccwc];
	if(crop[ccwc]==2&&PGI[ccwc]>=0.5){
		TTopt = OptimumT[ccwc]+8.0;
	}
		
	if (crop[ccwc] == 3)
		{
		TTopt = OptimumT[ccwc]+6;
		}

		if(crop[ccwc]==1)
		{
			
				if(air_temp<OptimumT[ccwc]*0.2) 
					T_stress = 0.2;
				else T_stress = 1.0;
		}
		else
		{
			
			if (air_temp < OptimumT[ccwc] * 0.2 )
			{
				T_stress = 0.2;
			}
			else T_stress = 1.0;
			if (crop[ccwc] == 2)
			{
			//	T_stress = 1.0;
			}
			//if (crop[ccwc] == 2)T_stress = 1.0;
		}

	if(crop[ccwc]==1||crop[ccwc]==20)
	{
		TTmax=45.0;
	}
	if (crop[ccwc] == 18)
	{
		TTmax = 31.0;
	}
	if(PGI[ccwc]<1.0)
	{

		if (crop[ccwc] == 2) 
		{
			float blah;
			blah = 1.0;
		}

		float maxAirTemp = max_temp;
		if (maxAirTemp < 0)maxAirTemp = 0;
	T_stress = (TTmax- maxAirTemp)/(TTmax-TTopt)*powf((maxAirTemp /TTopt), TTopt/(TTmax-TTopt));//original implementaion-using average air-temp -fix Oct 28 2021 was creating too much temperature stress
		//T_stress = (TTmax-max_temp)/(TTmax-TTopt)*powf((max_temp/TTopt), TTopt/(TTmax-TTopt));//now using Max_temp as the stress indicator
		//if(crop[ccwc]==2)T_stress=1.0;
		T_stress = min(1.0, max(0.0, T_stress)); //needed to set a minimum value
		cropTempStress[ccwc] = T_stress;
		cropTempStressAnnual[ccwc] += T_stress;
		cropTempStressDays[ccwc] ++;
		if(air_temp>TTopt) meanTempStressT[ccwc] += air_temp;
		
	}
	else//if PGI[ccwc]==1.0
	{

		if(crop[ccwc]==1)
		{
				if(air_temp<OptimumT[ccwc]*0.5) T_stress = 0.2;
				else T_stress = 1.0;
		}
		else
		{
			if(crop[ccwc]==2)
			{
			T_stress=1.0;	
			}
			else
			{
				if(air_temp<OptimumT[ccwc]*0.2) T_stress = 0.2;
				else T_stress = 1.0;
			}
		}
		
	}

/*	if(crop[ccwc]==1)//corn
	{
		float J_flag1=1.0, J_flag2=1.0, J_flag3=1.0, J_flag4=1.0;

		if(jday>=210&&jday<=225&&wind_speed>=10.0) 
		{
			J_flag1 = 0.9;
			jarovization_flag = min(J_flag1, jarovization_flag);
			wind_damage_flag = 2.0;
		}

		if(wind_damage_flag>0.0)
		{
			//day_N_demand[ccwc] = 0.0;
			wind_damage_flag -= 1.0;//0.5;
			if(wind_damage_flag<0.0) wind_damage_flag = 0.0;
		}

	}
*/
/*	if(crop[ccwc]==2)//winter wheat
	{	
		float J_flag1=1.0, J_flag2=1.0, J_flag3=1.0, J_flag4=1.0;

		//jarovization
		if(jday<100&&air_temp>=5.0&&TDD[ccwc]<=140.0) 
		{
			J_flag1 = 0.3;
			jarovization_flag = min(J_flag1, jarovization_flag);
		}

		//growing too fast in last winter
		if(jday==1&&(Leaf_Wt[ccwc]+Leaf_Wt[ccwc])>2160.0) 
		{
			J_flag2 = 0.2;
			jarovization_flag = min(J_flag2, jarovization_flag);
		}
		
		//Fen-Nie T
		//(TDD[ccwc]>300.0&&TDD[ccwc]<380.0&&air_temp>18.0) jarovization_flag = 0.3;
	
		//if(TDD[ccwc]>1400.0&&TDD[ccwc]<1500.0&&max_temp>30.0) 
		{
		//	J_flag3 = 0.1;
		//	jarovization_flag = min(J_flag3, jarovization_flag);
		}

		if(jday>140&&jday<165&&max_temp>=30.0) 
		{
			OverHotDays++;
			if(OverHotDays>=3) 
			{
				J_flag1 = 0.1;
				jarovization_flag = min(J_flag1, jarovization_flag);
				OverHotDays = 0;
			}
		}
	}
*/
	T_stress = min(1.0, max(0.0, T_stress));

	if(crop[ccwc]>0)
	{
		day_N_demand[ccwc] = 0.0;
	
		float FloodEffect, WTEffect=1.0, WSEffect=1.0;

			if(wetland_flag==1||(retard==1&&st[1]>12))
			{
				FloodEffect = 1.0;
				WTEffect = 1.0;
				WiltFlag[ccwc]=0;
			}
			else 
			{
				FloodEffect = 1.0 / (FloDays+1.0);
				if(day_WT>-0.3) 
					WTEffect = -day_WT;

				WSEffect = powf(day_DWater[ccwc], 1.00);//0.5



				
				if(PGI[ccwc]>0.01&&PGI[ccwc]<0.3&&crop[ccwc]==8)
				{					
					if(WSEffect<=0.50) Dwilt[ccwc]+=1.0;
					else Dwilt[ccwc]=0.0;

					if (Dwilt[ccwc] >= 7)
					{
						stuntGrowth *= 1.0;// 0.995;//
						WiltFlag[ccwc]++;

					}//17.0

						/*
					{		float harvFact,newHi,changeHi;
							harvFact=log(Dwilt[ccwc]/11);
							newHi= ((0.44-harvFact)*grain[ccwc]/0.44);
							changeHi=(grain[ccwc]-newHi);
							if((grain[ccwc]-changeHi)>0.05)
							{
							grain[ccwc]-=changeHi;
							stem[ccwc]+=changeHi/2;
							leaf[ccwc]+=changeHi/2;
							}
							else
							{
							 stem[ccwc]+= (grain[ccwc]-0.05)/2;
							 leaf[ccwc]+= (grain[ccwc]-0.05)/2;
							 grain[ccwc]=0.05;
							}
					}
					*/



					
				}
				else 
					WiltFlag[ccwc]=0;								
			}			

			/*if(PerennialFlag[ccwc]==1)
			{
				if(plantn[ccwc]>=maxmn[ccwc]||PGI[ccwc]==1||seed[ccwc]>=363)
				{
					maturity_flag[ccwc]=1;
				}
			}
			else
			{
				if(plantn[ccwc]>=maxmn[ccwc])//&&PerennialFlag[ccwc]==0) 
				{
					maturity_flag[ccwc]=1;

					if(IrriRice_flag==1) rice_maturity_flag=1;//crop[ccwc]==20
				}
			}*/


//testing for crop germination effect on germdays. Need to add a stress factor that has a negative effect on production if germination occurs too late.
//only works for a few crops (corn-corn silage and soybean)
			if(year==79)
			{
				float blah;
				blah=2.0;
			}
			if (crop[ccwc] == 888 && germCount < 26 || crop[ccwc] == 1 && germCount < 26 || crop[ccwc] == 43 && germCount < 26 || crop[ccwc] == 3 && germCount < 26)//new germination routine to improve germination timing
			{
				float plantEmerg;

				if (crop[ccwc] == 3)
				{
					plantEmerg = max(25, pow(germCount, 5 + temp[LL6]));
				}
				else
				{
					plantEmerg = max(20, pow(germCount, 1 + temp[LL6] / 3));
				}
				germTemp += plantEmerg;
				if (germTemp > 100.0)
				{
					GermDays[crop[ccwc]] = germCount;
					germCount = 25;
				}
				else if (germCount == 25)
				{
					GermDays[crop[ccwc]] = germCount;
					stuntGrowth = pow(12.0 / GermDays[crop[ccwc]], 0.15);
				}
				germCount += 1;
			}
			
			/*
		if(crop[ccwc]==1 && germCount<26||crop[ccwc]==43 && germCount<26||crop[ccwc]==3 && germCount<26|| crop[ccwc] == 98 && germCount < 26)
			{
			float germMulti;
			germMulti = 0.1205;//helps to calibrate days to emergence. High value = longer time to emerge
				if(year==11)
				{float blah;
				blah=1.0;
				}
				if(germCount==1)
				{
					//	germTemp=(-0.8955*temp[LL6]+27.244);
					//	germTemp=(-2.6904*temp[LL6]+57.516);
					//	germTemp=(-3.5*temp[LL6]+57.0);//temp[LL6]
						germTemp=(0.1255*temp[LL6]*temp[LL6]-7.7709*temp[LL6]+115.82);//5 cm depth
						if(crop[ccwc]==3||crop[ccwc]==1 || crop[ccwc] == 8){germTemp=(germMulti *temp[LL6]*temp[LL6]-7.7709*temp[LL6]+115.82);
						germTemp=max(5.0,min(25.0,germTemp));}
						else{germTemp=max(8.0,min(25.0,germTemp));}
				}
				else
				{
					//germTemp+=(-0.8955*temp[LL6]+27.244);
				//	germTemp+=max(5.0,min(25.0,(-2.6904*temp[LL6]+57.516)));
					if(crop[ccwc]==3 || crop[ccwc] == 1 || crop[ccwc] == 8){germTemp+=max(5.0,min(25.0,(germMulti *temp[LL6]*temp[LL6]-7.7709*temp[LL6]+115.82)));}
					else{
						germTemp+=max(8.0,min(25.0,(0.1255*temp[LL6]*temp[LL6]-7.7709*temp[LL6]+115.82)));}
				//	germTemp+=max(5.0,min(25.0,(-3.5*temp[LL6]+57.0)));//temp[LL6]
				//	germDays=(0.1255*temp[LL6]*temp[LL6]-7.7709*temp[LL6]+123.82);
				}
				
				//if(germDays<(int(germTemp/germCount))
				//	{
				int minCountGerm=8;
				if(crop[ccwc]==3)minCountGerm=5;
				if (crop[ccwc] == 1)minCountGerm = 5;
				if (crop[ccwc] == 8)minCountGerm = 5;
				//if(germCount>=5 && int(germTemp/germCount)<=germCount && germCount<25)
				if(germCount>=minCountGerm && germCount<25)
				{
				float germTemp2,germTemp3;
				if(crop[ccwc]==3 || crop[ccwc] == 1 || crop[ccwc] == 8){germTemp2=(germMulti *temp[LL6]*temp[LL6]-7.7709*temp[LL6]+115.82);}
				else{
					germTemp2=(0.1255*temp[LL6]*temp[LL6]-7.7709*temp[LL6]+115.82);}
				germTemp3=(germTemp/germCount);
					if(germTemp2<germTemp3)
					{
					germTemp3=int(germTemp3*0.40 + germTemp2*0.60);
					}
					else
					{
					germTemp3=int(germTemp3);
					}
				
					if(germTemp3<germCount)
					{
				//germTemp=int(germTemp/germCount);
					
					GermDays[crop[ccwc]]=max(minCountGerm,min(25,germTemp3));
					germCount=25;
				
				
					float residueFactor;
					residueFactor=surface_litter/100;
					residueFactor=int(min(minCountGerm,max(0,residueFactor)));
					GermDays[crop[ccwc]]+=residueFactor;
					GermDays[crop[ccwc]]=max(minCountGerm,min(25,germTemp3));

						if(GermDays[crop[ccwc]]>=13&&crop[ccwc]==1||GermDays[crop[ccwc]]>=13&&crop[ccwc]==43)
						{
						stuntGrowth=pow(12.0/GermDays[crop[ccwc]],0.15);	
						}
						if(crop_days[ccwc]-GermDays[crop[ccwc]]>1)
						{
							GermDays[crop[ccwc]]=crop_days[ccwc]-1;
						}
					}	

				}
				else if(germCount==25)
				{
					GermDays[crop[ccwc]]=25;
					stuntGrowth=pow(12.0/25.0,0.25);
					if(crop_days[ccwc]-GermDays[crop[ccwc]]>1)
						{
							GermDays[crop[ccwc]]=crop_days[ccwc]-1;
						}
				}
				
				germCount+=1;
			
			}//end germination code
			*/
//stuntGrowth=1.0;
//end test on germination effect

			
			if(seed[ccwc]>GermDays[crop[ccwc]])//maturity_flag[ccwc]==0&&
			{
				if(GermReport==0)
				{GermReport=GermDays[crop[ccwc]];}
				
				//if((CropSumN[ccwc]<(maxmn[ccwc] / (1.0 + (float)WiltFlag[ccwc])) && TDD[ccwc]<max_TDD[ccwc])||
				if((plantn[ccwc]<(maxmn[ccwc] / (1.0 + (float)WiltFlag[ccwc])) && TDD[ccwc]<max_TDD[ccwc]|| PerennialFlag[ccwc]==1 && TDD[ccwc]<max_TDD[ccwc]))// (yr_plantn[ccwc]<(maxmn[ccwc] / (1.0 + (float)WiltFlag[ccwc])) && //Currently determines whether plantN exceed maxmn (maximum N uptake).
				{
					float fPGI=0.0, dfPGI=0.0, ffPGI=0.0, GWa, GWb, GWc;

			 		if(C_type[ccwc]==3)//C3 crops 
					{
						GWa = 5.0;//5.0
						GWb = 5.0;//5.0
						GWc = 0.5;
					}
					else //C4 type crops
					{
						GWa = 6.0;//6.0;
						GWb = 5.0;//6.0;
						GWc = 0.5;
					}

					/*
					if(crop[ccwc]==3)
					{

							dfPGI = day_TDD[ccwc] / max_TDD[ccwc];

							if(PGI[ccwc]<=0.2&&crop[ccwc]!=20&&air_temp<10.0) //early vegetative stage
							{
								dfPGI *= 1.0;//0.2;
							}
							else if(PGI[ccwc]<=0.5)//vegetative stage
							{
								dfPGI *= 1.1;//1.2;
							}
							else //reproductive stage
							{
								//if(GrainN[ccwc]>=MaxGrainN[ccwc]) dfPGI = 0.0; 
								//else dfPGI *= 1.5;
								dfPGI *= 1.1;
							}
							
							day_need_N[ccwc] = maxmn[ccwc] * dfPGI;	


					}


					//need to do this only on first day of growth
							
						
					else
					{
					*/	

					if((crop_days[ccwc]-GermDays[crop[ccwc]])==1 && PerennialFlag[ccwc]==0 || crop_days[ccwc] == 11 && PerennialFlag[ccwc] == 1)//only want to do this for one day and non-perrenial crops //Perrenial Flag =0//&& WinterCropFlag[ccwc]==0 //crop_days[ccwc]==11 && PerennialFlag[ccwc]==1
					{
					germinationDays=GermDays[crop[ccwc]];
					if(crop[ccwc]==1||crop[ccwc]==43) GermDays[crop[ccwc]]=-99;
					
	

						for(int u=0;u<732;u++)//Reading ahead for 2 years worth of climate data for annual crops.
						{optffPGI[u][0]=0.0;
						optffPGI[u][1]=0.0;
						optffPGI[u][2]=0.0;
						optffPGI[u][3]=0.0;
						}

					
						
					
						

							FILE* fpa;//Create new file handler
							char   CLIM1[80];// , junk8[80];//store path name in char //reading cliamte average temperature
							float  junk1, junk2, junk3, junk4, junk5, junk6, junk7;//gddT[731],
							//int endYearOfSim;
							int thisYearLastFrost = 115;
							int thisYearFallFrost = 365;
							int thisYearFallFrostCutoffHarv = 0;
							float GDDCounter = 0.0;
							int GDDDays = 0;
							int finalFrostCounter = 0;
							float gddTrack[366] = { 0.0 };
							float averageLastFrost, averageFallFrost;
							float avgTempDay = 0.0;
							//endYearOfSim = 0;
							int dayClim[731];
							sprintf(CLIM1, "%s\\Inputs\\%s", OUTPUT, climd[0]);
							fpa = fopen(CLIM1, "r");
							if (fpa == NULL) note(0, CLIM1);

							if (currentCut < 2)
							{

								//create temp variables to hold climate variables


								for (int z = 1; z < 366; z++)
								{
									fscanf(fpa, "%d %f %f %f %f %f %f %f %f", &dayClim[z], &gddT[z], &junk1, &junk2, &junk3, &junk4, &junk5, &junk6, &junk7);//scans the day and the average temperature
									//	fscanf(fpa, "%d %f %s",&dayClim[z],&gddT[z],&junk8[1]);
									if (gddT[z] < 0)
									{
										gddT[z] = 0.0;
									}
									avgTempDay = (junk1 + junk2) / 2;
									if (z > 85 && z < 152)//calculate the last frost of the spring between Jdays 86 and 151.... problematic for southern hempisphere. would need to test if latitude positive or negative otherwise 
									{
										if (junk2 < -2.0)//if minimum temperature is less than -2
										{
											thisYearLastFrost = z;//set this thisYearLastFrost to today
										}
										if (thisYearLastFrost == 151)
										{
											thisYearLastFrost = 85;
										}
									}
									if (z > 152 && z < 366 && finalFrostCounter < 1)//test for first all frost.
									{
										if (avgTempDay <= -4.0)//junk2 == mininum air temp
										{
											thisYearFallFrost = z;
											thisYearFallFrostCutoffHarv = (z - GDDDays);//calculates what 500GDD before the harvest trigger
											finalFrostCounter = 1;

										}
										else
										{
											if (((junk1 + junk2) / 2.0 - 5.0) >= 0.0)
											{
												GDDCounter += ((junk1 + junk2) / 2.0 - 5.0);
												GDDDays += 1;
												gddTrack[z] = ((junk1 + junk2) / 2.0 - 5.0);
											}
											if (GDDCounter > 500.0)
											{
												GDDCounter -= gddTrack[z - GDDDays];//subtracts the average GDD at beginning
												GDDDays -= 1;
											}


										}
									}
									if (z == 365 && thisYearFallFrost == 0)
									{
										thisYearFallFrost = 0;
									}
								}
								//fclose(fpa);

								if (year > 1)//if year is greater than 1 calculate the average last year frost in spring
								{
									averageLastFrost = float(lastFrost) * float(((year - 1.0) / year)) + float(thisYearLastFrost) * float((1.0 / year));//average date for average last Frost considering the year.
									lastFrost = int(averageLastFrost);

									averageFallFrost = float(fallFrost1) * float(((year - 1.0) / year)) + float(thisYearFallFrostCutoffHarv) * float((1.0 / year));//average date for average last Frost considering the year.
									fallFrost1 = int(averageFallFrost);

								}
								else//if its just this year.
								{
									lastFrost = thisYearLastFrost;//otherwise its this years.
									fallFrost1 = thisYearFallFrostCutoffHarv;//last day for harvest
								}
							}//currentCut

							fclose(fpa);
						
						//	FILE  *fpa;//Create new file handler
						
							if (endYearOfSim != 1)
							{
								FILE* fcl;//create File Handler
								char CLIM0[80], climFile[80];//create two strings one for file name and one for the 2nd year of climate data to be read in.
								sprintf(CLIM0, "%s\\Inputs\\clim-%d", OUTPUT, year + 1);//OUTPUT is the string for the path for DNDC. year+1 grabs the next year for the crop

								if ((fcl = fopen(CLIM0, "r")) != NULL)//test to see if overwintering crop if(HarvestYear[ccwc]==2)
								{

									//	fcl = fopen(CLIM0, "r");
											//if ( fcl == NULL ) note(0, CLIM0);

									fscanf(fcl, "%s", &climFile);//breaking here
									fclose(fcl);






									sprintf(CLIM1, "%s\\Inputs\\%s", OUTPUT, climFile);
									fpa = fopen(CLIM1, "r");
									if (fpa == NULL) note(0, CLIM1);
									for (int y = 1; y < 366; y++)
									{
										fscanf(fpa, "%d %f %f %f %f %f %f %f %f", &dayClim[y + 365], &gddT[y + 365], &junk1, &junk2, &junk3, &junk4, &junk5, &junk6, &junk7);
										//	fscanf(fpa, "%d %f %s",&dayClim[z],&gddT[z],&junk8[1]);
										if (gddT[y + 365] < 0)
										{
											gddT[y + 365] = 0.0;
										}
										if (year == total_yr && total_yr > 1)
										{
											gddT[y + 365] = 0.0;

										}
									}
									fclose(fpa);
								}
								else
								{
									for (int y = 1; y < 366; y++)
									{
										gddT[y + 365] = 0.0;
										gddT[y + 365] = gddT[y];
									}
									endYearOfSim = 1;
								}
								fclose(fpa);

							}



							
							//section for calculating the appropriate biomass growth over time.Going to decouple from N demand
						
							float sumGDD,tPGI,tffPGI,vegTDD;//define variables for storing sumGDD=sum of all GDD days from planting to TDD max, tPGI=a independent PGI counter for this loop. tffPGI=The new ffPGI that is calculated in advance
							int cropGDD,cropDays;//This is just the day counter for the loop
							cropGDD=jday;
							sumGDD=0.0;//set sumGDD to zero
							cropDays=1;
							tPGI=0.0;
							float oldtffPGI;
							oldtffPGI=0.0;
							tffPGI = 0.0;
							if(PerennialFlag[ccwc]==0)
							{
								while(sumGDD<=max_TDD[ccwc]&&cropDays<365&&cropGDD<730)
								{
									if(gddT[cropGDD]<0)//ensures the gddT array is only using positive numbers (can be negatives in array if only 1 year is filled as opposed to 2 = overwintering
										gddT[cropGDD]=0.0;

									if (crop[ccwc] == 2 )// || crop[ccwc] == 47
									{
										if (gddT[cropGDD] < WinterWheat_LimitiT)
										{
											//do nothing here if crop type = 2
										}
										else
										{
											sumGDD += (gddT[cropGDD]- WinterWheat_LimitiT);//add the present GDD to the running total

											tPGI += (gddT[cropGDD]- WinterWheat_LimitiT) / max_TDD[ccwc];//calculate an accumulating PGI based on GDD/TDD
										}
									
									}
									else {
										sumGDD += gddT[cropGDD];//add the present GDD to the running total

										tPGI += gddT[cropGDD] / max_TDD[ccwc];//calculate an accumulating PGI based on GDD/TDD
										}
								

											//crop curves
											if(crop[ccwc]==8||crop[ccwc]==6||crop[ccwc]==9||crop[ccwc]==25)//wheat,barley,rye
											{
												if(tPGI<=0.32) //vegetative stage
												tffPGI =(0.000000000000003953*pow((tPGI*1600),6) - 0.000000000006329*pow((tPGI*1600),5) + 0.000000003623*pow((tPGI*1600),4) - 0.0000008819*pow((tPGI*1600),3) + 0.00009362*pow((tPGI*1600),2) - 0.003539*(tPGI*1600) +0.106086);
												else//reproductive stage
												{
													//tffPGI = (0.000001299 * pow((tPGI * 1600), 2) - 0.0045671 * (tPGI * 1600) + 3.9851175);//11963

													float f1tffPGI = 0.0;
													float f2tffPGI = (0.000001299 * pow((tPGI * 1600), 2) - 0.0045671 * (tPGI * 1600) + 3.9851175) * 1.6;//11963
													tffPGI = max(f1tffPGI, f2tffPGI);

												}
												if (tffPGI < 0.0) tffPGI = 0.0; 


												

											}
											else if (crop[ccwc] == 2 || crop[ccwc]==15)//
											{
											
											tffPGI=(-1483.8*pow(tPGI,5)+2432.7*pow(tPGI,4)-1014*pow(tPGI,3)+19.265*pow(tPGI,2)+58.998*tPGI-4.8248);
											tffPGI = (-281.42693032 * pow(tPGI, 4) + 118.65687434 * pow(tPGI, 3) + 194.60023224 * pow(tPGI, 2) - 20.66236050 * pow(tPGI, 1) - 0.33530002)*4.0;
											tffPGI = -17.574 * pow(tPGI, 4) + 36.688 * pow(tPGI, 3) - 27.521 * pow(tPGI, 2) + 7.9361 * tPGI + 0.4105;
											tffPGI = -34.809 * pow(tPGI, 5) + 88.859 * pow(tPGI, 4) - 79.784 * pow(tPGI, 3) + 26.406 * pow(tPGI, 2) - 0.8607 * pow(tPGI, 1) + 0.1969;//decent
											tffPGI = -234.59 * pow(tPGI, 6) + 757.24 * pow(tPGI, 5) - 903.29 * pow(tPGI, 4) + 479.33 * pow(tPGI, 3) - 109.41 * pow(tPGI, 2) + 10.903 * pow(tPGI, 1) - 0.172;
										//	tffPGI = 429.94966717 * pow(tPGI, 4) - 1, 171.26418971 * pow(tPGI, 3) + 809.24760101 * pow(tPGI, 2) - 57.41775345 * pow(tPGI, 1) - 1.78861464;
											if (tffPGI < 0.0) tffPGI = 0.0;
											}
											else if(crop[ccwc]==1||crop[ccwc]==43)
											{	
												if (tPGI <= 0.28) //vegetative stage
													 tffPGI = (0.0049 * exp(20.123 * tPGI));
											
												else//reproductive stage
												{
													tffPGI = (-0.1256 * pow(tPGI, 4) - 11.249 * pow(tPGI, 3) + 7.5513 * pow(tPGI, 2) + 3.9352 * tPGI - 0.0499);//Brian change to test *4

												//	tffPGI = (-0.1256 * pow(tPGI, 4) - 11.249 * pow(tPGI, 3) + 7.5513 * pow(tPGI, 2) + 3.9352 * tPGI - 0.0499);//Brian change to test *4
												//	tffPGI = min(tffPGI, max(0.01, tffPGI));
												}
											}
											else if (crop[ccwc] == 90)
											{

												//-test brian code
												
												// --end test
												if (tPGI <= 0.25) //vegetative stage  //was 0.25
												{
													tffPGI = (0.0049 * exp(20.123 * tPGI) * 0.25); //was 0.25
													vegTDD = tffPGI;
												}
												else//reproductive stage
												{
													//tffPGI = (-0.1256 * pow(tPGI, 4) - 11.249 * pow(tPGI, 3) + 7.5513 * pow(tPGI, 2) + 3.9352 * tPGI - 0.0499);//Brian change to test *4

												tffPGI = (-0.1256 * pow(tPGI, 4) - 11.249 * pow(tPGI, 3) + 7.5513 * pow(tPGI, 2) + 3.9352 * tPGI - 0.0499)*0.25;//Brian change to test *4
												tffPGI = min(tffPGI, max(0.01, tffPGI));
											
												vegTDD = tffPGI;
												}

											//	tffPGI = (-2.8614 * pow(tPGI, 3) + 3.1512 * pow(tPGI, 2) - 0.2857 * pow(tPGI, 1) + 0.005)*10.0;//empirical corn

											
											}

											else if(crop[ccwc]==3||crop[ccwc]==29) //soybean and alfalfa
											{ 


												tffPGI = (33.057 * pow(tPGI, 4) - 92.276 * pow(tPGI, 3) + 52.899 * pow(tPGI, 2) - 3.6027 * tPGI + 0.0419)*1.0;//for agmip ET (43.057 * pow(tPGI, 4) - 92.276 * pow(tPGI, 3) + 52.899 * pow(tPGI, 2) - 3.6027 * tPGI + 0.0419)*1.0
												tffPGI = -0.0026 * pow(tPGI, 3) + 0.4802 * pow(tPGI, 2) - 13.3 * tPGI + 96.9;
												tffPGI = (157.5 * pow(tPGI, 4) - 389.35 * pow(tPGI, 3) + 260.78 * pow(tPGI, 2) - 24.219 * tPGI + 0.8611)*1.0;
												tffPGI = -4.7468677 * pow(tPGI, 3) + 4.237085 * pow(tPGI, 2) + 0.9928785 * pow(tPGI, 1) - 0.0826368;//testing out new curve
												tffPGI = -0.9811400 * pow(tPGI, 3) - 2.5991566 * pow(tPGI, 2) + 4.0115191 * pow(tPGI, 1) - 0.1481734;
												if(tffPGI<0)
													tffPGI=0.01;
												//if (tPGI < 0.05)
													//tPGI = 0.25 * (tPGI / 0.05);
												
												if (tffPGI < 0.15)
													tffPGI = 0.15;
												//if (tPGI < 0.2)
												//	tffPGI = 0.01;
											
											
											
								
											}
											else if(crop[ccwc]==57) //canola
											{ 
												if(tPGI<=0.34) //vegetative stage PGI<=0.5
												//tffPGI=0.00232;
												tffPGI=0.00009*exp(17.193*tPGI);
												else if(tPGI>0.34&&tPGI<=0.89) //vegetative stage PGI<=0.5
												tffPGI = -0.0568*tPGI+0.0547;
												else//reproductive stage
												tffPGI = 0.0; 
								
											}
											else
											{
												if(tPGI<=0.5) //vegetative stage
												tffPGI = tPGI / (0.5 + tPGI) * (1.0 - tPGI) / (0.5 + tPGI) * GWa; 
												else//reproductive stage
												tffPGI = tPGI / (0.5 + tPGI) * (1.0 - tPGI) / (0.5 + tPGI) * GWb;
												if (tffPGI < 0.0) tffPGI = 0.0; 
									
											}
			
									if(oldtffPGI==tffPGI)
									{
									tffPGI=0.0;
									totalFFPGI[ccwc]+=tffPGI;//total of the tffPGI. This is important because it is used to scale the C/N growth properly.
									}
									else
									{
									totalFFPGI[ccwc]+=tffPGI;
									oldtffPGI=tffPGI;
									}
									optffPGI[cropDays][0]=tPGI;
									optffPGI[cropDays][1]=tffPGI;
									cropGDD=cropGDD+1;//counter + 1
									cropDays+=1;	


								}	//end of while
							} //end of annual crops
						else //sum up GDD for perrenial crops per cut
							{
							int zz;
							int timeToCut;
							timeToCut=jday;
							int reGrow;
							int tempCut;
							
							
							reGrow=perRegrow[ccwc];
							//sumGDD=max_TDD[ccwc]* PGI[ccwc];

						
							for(zz=1;zz<8;zz++)
							{
							per[ccwc][zz]=0.0;
							}
			
							   for ( zz = 1; zz <= 1 ; zz++ )//(cut_num+1)
							   {
								   if(reGrow==1)//||sumGDD>=max_TDD[ccwc]
								   {
									   sumGDD=max_TDD[ccwc]* PGI[ccwc];//0.324
									   tPGI=PGI[ccwc];//0.324
									   crop_days[ccwc]++;
									   if(zz>1)
									   {
									   //timeToCut=jdcut[zz-1]+1;
									   //cropGDD=timeToCut;
									   }

								   }
								   else if(vernal[ccwc]>0)
								   {
									sumGDD=max_TDD[ccwc]* PGI[ccwc];//0.324
									   tPGI=PGI[ccwc];
									   crop_days[ccwc]++;
								   }
								   if(jday>270&&vernal[ccwc]==0)//zz==(cut_num+1)
								   {
									//per[ccwc][zz]+=2000;//Just adding enough to make the growth slow in the last period after cut. Currently it is not calculating the N uptake curve properly over one year to next
								   }
								
								   if (year == 130)
								   {
									   float blah;
									   blah = 1.0;

								   }
								while(sumGDD<=max_TDD[ccwc])//jdcut[cutCounter]//sumGDD<=max_TDD[ccwc]|
								{
								
								if(gddT[cropGDD]<0)//ensures the gddT array is only using positive numbers (can be negatives in array if only 1 year is filled as opposed to 2 = overwintering
									gddT[cropGDD]=0.0;
								
								if(jdcut[zz]<0)
									tempCut=365;
									else
									tempCut=jdcut[zz];


					
											sumGDD+=gddT[cropGDD];//add the present GDD to the running total
											tPGI+=gddT[cropGDD]/max_TDD[ccwc];//calculate an accumulating PGI based on GDD/TDD
											
												
											if(crop[ccwc]==10||crop[ccwc]==5 || crop[ccwc] == 4 || crop[ccwc] == 12 || crop[ccwc] == 11)
											{

												if (year == 30 && jday == 188)
												{
													float blah;
													blah = 2.0;
												}
												float pGIScalar;
												if(reGrow==0)
													{
														//float maxNScale;
												
													//pGIScalar=1.0;
													if(tPGI>0.6) pGIScalar=1-tPGI;
														tffPGI=27.423*tPGI;//dfPGI*3/0.1
											
														tffPGI = 6.423 * tPGI;//test Andrea //was 22  ...was 12 with Oct 2024// reduced to encourage better growth of perennial first cut
														
													}
													else
													{

													
														float parScale;
														
													
													    parScale=1.0;


												
														tffPGI=12.423*tPGI*parScale;
														tffPGI=12.423*pow((tPGI),2)*parScale+1.0*(1-tPGI);
														
														
													}
											}
										    else if(crop[ccwc]==89)
											{
												float pGIScalar;
												if(reGrow==0)
													{


														tffPGI=27.423*tPGI;	

													
														
														
													}
													else
													{
														
													
														tffPGI=1.423*pow((tPGI),2) + 1.0*(1-tPGI);
														
															if(tPGI>0.6)
												     	pGIScalar=1-tPGI;
														
											
														//tffPGI=(-784.86/2*tPGI*tPGI)+1017.2/2*tPGI-216.97/2;
														tffPGI=max(0.0,tffPGI);
													}
											}
											
										
											//summation part
											if(oldtffPGI==tffPGI)
											{
											tffPGI=0.0;
											//totalFFPGI[ccwc]+=tffPGI;//total of the tffPGI. This is important because it is used to scale the C/N growth properly.
											per[ccwc][zz]+=tffPGI;
											}
											else
											{
											per[ccwc][zz]+=tffPGI;
											oldtffPGI=tffPGI;
											}
											
											







											optffPGI[cropDays][0]=tPGI;
											optffPGI[cropDays][1]=tffPGI;
											cropGDD=cropGDD+1;//counter + 1
											cropDays+=1;
											timeToCut+=1;
											if (cropGDD == 365 && endYearOfSim == 1)
											{
												sumGDD = max_TDD[ccwc] + 1.0;//needs to get out of loop
											}
											else if (cropGDD >= 730)//need condition to exit alfalfa loop if doesn't get enough gDD in 2 years otherwise stack overflow
											{
												sumGDD = max_TDD[ccwc] + 1.0;//need to get out of the loop
											}
								//	}//end of cutCounter
								//	else
								//	{
								//	sumGDD=max_TDD[ccwc]+1;
								//	reGrow=1;
								//	}
								}//end of while
											
							   }//end of for
							}//end of else
						
						
					

					}	//calculating sum under the curve for growth curves to scale plant C appropriately for growth curves resolves totalFFPGI

					

					//new section of growth stages - plan to replace the previous growth calculations.
					
					float endPGIV1, endPGIV2, endPGIV3, endPGIV4, endPGIR1, endPGIR2;//PGI end of growth
					float uptakeV1, uptakeV2, uptakeV3, uptakeV4, uptakeR1, uptakeR2; //growth rates
					float totalUpV1, totalUpV2, totalUpV3, totalUpR1, totalUpR2;


					endPGIV1 = 0.1;//vegetative V1 Germination/Emergence
					endPGIV2 = 0.3;//vegetative V1  - Tillering
					endPGIV3 = 0.6;//vegetative V1 - Stem Elongation
					endPGIV4 = 0.0;
					endPGIR1 = 0.80;//reproductive R1 Heading Flowering
					endPGIR2 = 1.0;//reproductive R2 Ripening

					uptakeV1 = 15;
					uptakeV2 = 70;//70
					uptakeV3 = 90;//90
					uptakeR1 = 99;//99
					uptakeR2 = 100;

					totalUpV1 = maxmn[ccwc] * uptakeV1 / 100;
					totalUpV2 = maxmn[ccwc] * uptakeV2 / 100 - totalUpV1;
					totalUpV3 = maxmn[ccwc] * uptakeV3 / 100 - totalUpV1 - totalUpV2;
					totalUpR1 = maxmn[ccwc] * uptakeR1 / 100  - totalUpV1 - totalUpV2 - totalUpV3;
					totalUpR2 = maxmn[ccwc] * uptakeR2 / 100 - totalUpV1 - totalUpV2 - totalUpV3 - totalUpR1;

					float dailyPGI;
					dailyPGI = PGI[ccwc] - OLDPGI[ccwc];
					float dailyNup;

					if (PGI[ccwc] < endPGIV1)
					{

						dailyNup = dailyPGI / endPGIV1 * totalUpV1;
					}
					else if (PGI[ccwc] < endPGIV2)
					{
						dailyNup = dailyPGI / (endPGIV2-endPGIV1) * totalUpV2;
					}
					else if (PGI[ccwc] < endPGIV3)
					{
						dailyNup = dailyPGI / (endPGIV3 - endPGIV2) * totalUpV3;
					}
					else if (PGI[ccwc] < endPGIR1)
					{
						dailyNup = dailyPGI / (endPGIR1 - endPGIV3) * totalUpR1;
					}
					else
					{
						dailyNup = dailyPGI / (endPGIR2 - endPGIR1) * totalUpR2;
					}
					//end new section of growth
					accumNewPlantN += dailyNup;
				


					float plantNGrowthStage;
					
					
					if (PGI[ccwc] < GrainFill[ccwc])
					{
						plantNGrowthStage = MaxLeafN[ccwc] + MaxStemN[ccwc] + MaxRootN[ccwc];
					}
					else
					{
						plantNGrowthStage = MaxGrainN[ccwc];
					}
			
				
				
					if (PerennialFlag[ccwc] == 0)
					{

						float baseNeedN, scaleN;

						if (crop[ccwc] == 8 || crop[ccwc] == 6 || crop[ccwc] == 9 || crop[ccwc] == 25)
						{


							if (PGI[ccwc] <= 0.32) //vegetative stage
								ffPGI = (0.000000000000003953 * pow((PGI[ccwc] * 1600), 6) - 0.000000000006329 * pow((PGI[ccwc] * 1600), 5) + 0.000000003623 * pow((PGI[ccwc] * 1600), 4) - 0.0000008819 * pow((PGI[ccwc] * 1600), 3) + 0.00009362 * pow((PGI[ccwc] * 1600), 2) - 0.003539 * (PGI[ccwc] * 1600) + 0.106086);

							else//reproductive stage

							{
							//	ffPGI = (0.000001299 * pow((PGI[ccwc] * 1600), 2) - 0.0045671 * (PGI[ccwc] * 1600) + 3.9851175);//11963
								float f1ffPGI = 0.0;
								float f2ffPGI = (0.000001299 * pow((PGI[ccwc] * 1600), 2) - 0.0045671 * (PGI[ccwc] * 1600) + 3.9851175) * 1.6;//11963
								ffPGI = max(f1ffPGI, f2ffPGI);



							}
							if (ffPGI < 0.0) ffPGI = 0.0;

							

							day_need_N[ccwc] = ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];//This really represents optimal C gain.

							//day_need_N[ccwc] = dailyNup;//testing new approach for N uptake

						}
						else if (crop[ccwc] == 2 || crop[ccwc] == 15)//
						{



							ffPGI = (-1483.8 * pow(PGI[ccwc], 5) + 2432.7 * pow(PGI[ccwc], 4) - 1014 * pow(PGI[ccwc], 3) + 19.265 * pow(PGI[ccwc], 2) + 58.998 * PGI[ccwc] - 4.8248);
							ffPGI = (-281.42693032 * pow(PGI[ccwc], 4) + 118.65687434 * pow(PGI[ccwc], 3) + 194.60023224 * pow(PGI[ccwc], 2) - 20.66236050 * pow(PGI[ccwc], 1) - 0.33530002) * 4.0;
							ffPGI = -17.574 * pow(PGI[ccwc], 4) + 36.688 * pow(PGI[ccwc], 3) - 27.521 * pow(PGI[ccwc], 2) + 7.9361 * PGI[ccwc] + 0.4105;
							ffPGI = -34.809 * pow(PGI[ccwc], 5) + 88.859 * pow(PGI[ccwc], 4) - 79.784 * pow(PGI[ccwc], 3) + 26.406 * pow(PGI[ccwc], 2) - 0.8607 * pow(PGI[ccwc], 1) + 0.1969;
							ffPGI = ( - 234.59 * pow(PGI[ccwc], 6) + 757.24 * pow(PGI[ccwc], 5) - 903.29 * pow(PGI[ccwc], 4) + 479.33 * pow(PGI[ccwc], 3) - 109.41 * pow(PGI[ccwc], 2) + 10.903 * pow(PGI[ccwc], 1) - 0.172)*0.85;
							
							//ffPGI = 429.94966717 * pow(PGI[ccwc], 4) - 1, 171.26418971 * pow(PGI[ccwc], 3) + 809.24760101 * pow(PGI[ccwc], 2) - 57.41775345 * pow(PGI[ccwc], 1) - 1.78861464;
							if (ffPGI < 0.0) ffPGI = 0.0;
							day_need_N[ccwc] = ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];


						


							// Inputs per cohort/plant ccwc:
							// - day_TDD[ccwc]: cumulative thermal degree-days to date
							// - max_TDD[ccwc]: thermal sum at maturity
							// - maxmn[ccwc]: total seasonal N requirement (kg N/ha or your unit)
							// - curveK_prev[ccwc]: stored from previous timestep (initialize to logistic at f=0 on planting/emergence)

							// Tunable logistic parameters
							const double m = cropTime[ccwc];// = 0.35;   // inflection at 30% of thermal time
							const double k = cropGRate[ccwc];//10.0;   // steepness; higher = sharper mid-season surge
							float blah;
							blah = 1.0;
							// Safety helpers
							auto clamp01 = [](double x) {
								if (x < 0.0) return 0.0;
								if (x > 1.0) return 1.0;
								return x;
								};

							auto logistic = [&](double f) {
								// for numerical stability with large k, clamp the exponent argument
								const double x = -k * (f - m);
								// avoid overflow in exp(x) for large |x|
								const double x_clamped = max(-40.0, min(40.0, x));
								return 1.0 / (1.0 + exp(x_clamped));
								};

							// Compute normalized thermal progress
							double denom = max(1e-9, max_TDD[ccwc]);  // avoid divide-by-zero
							double f = clamp01(TDD[ccwc] / denom);
							//double f1 = clamp01(OLDPGI[ccwc]);

							// Current cumulative growth fraction (sigmoidal)
							double curveK = logistic(f);
							//double curveK_prev = logistic(f1);

							// DAILY increment in growth fraction
							double delta = curveK - curveK_prev[ccwc];
							if (delta < 0.0) delta = 0.0;  // guard against numerical/ordering issues

							// Daily N demand based on increment
							day_need_N[ccwc] = maxmn[ccwc] * delta;
							curveK_prev[ccwc] = curveK;
							// Update stored state for next timestep
							



						}
						else if (crop[ccwc] == 1 || crop[ccwc] == 43)
						{




							if (PGI[ccwc] <= 0.28) //vegetative stage //was .28
								ffPGI = (0.0049 * exp(20.123 * PGI[ccwc]));
							else//reproductive stage
							{
								ffPGI = (-0.1256 * pow(PGI[ccwc], 4) - 11.249 * pow(PGI[ccwc], 3) + 7.5513 * pow(PGI[ccwc], 2) + 3.9352 * PGI[ccwc] - 0.0499);//Brian change to test *4


								//	ffPGI = (-0.1256 * pow(PGI[ccwc], 4) - 11.249 * pow(PGI[ccwc], 3) + 7.5513 * pow(PGI[ccwc], 2) + 3.9352 * PGI[ccwc] - 0.0499) * 1.1;//Brian change to test *4
									//ffPGI = min(ffPGI, max(0.01, ffPGI));
							}
							day_need_N[ccwc] = ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];

							


						}
						else if (crop[ccwc] == 90)
						{

							//brian test code
						
							//end test code



							ffPGI = -2.8614 * pow(PGI[ccwc], 3) + 3.1512 * pow(PGI[ccwc], 2) - 0.2857 * pow(PGI[ccwc], 1) + 0.005;

							if (PGI[ccwc] <= 0.25) //vegetative stage //was .28
								ffPGI = (0.0049 * exp(20.123 * PGI[ccwc]) * 0.25);
							else//reproductive stage
							{
								ffPGI = (-0.1256 * pow(PGI[ccwc], 4) - 11.249 * pow(PGI[ccwc], 3) + 7.5513 * pow(PGI[ccwc], 2) + 3.9352 * PGI[ccwc] - 0.0499) * 0.25;//Brian change to test *4


								//	ffPGI = (-0.1256 * pow(PGI[ccwc], 4) - 11.249 * pow(PGI[ccwc], 3) + 7.5513 * pow(PGI[ccwc], 2) + 3.9352 * PGI[ccwc] - 0.0499) * 1.1;//Brian change to test *4
								ffPGI = min(ffPGI, max(0.01, ffPGI));
							}

							
							//ffPGI = (-2.8614 * pow(PGI[ccwc], 3) + 3.1512 * pow(PGI[ccwc], 2) - 0.2857 * pow(PGI[ccwc], 1) + 0.005)*10.0;  -- emperical corn

							if (PGI[ccwc] >= GrainFill[ccwc])
							{
								day_need_N[ccwc] = ffPGI * plantNGrowthStage / (totalFFPGI[ccwc] * (1 - GrainFill[ccwc]));//ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];
							}
							else
							{
								day_need_N[ccwc] = ffPGI * plantNGrowthStage / (totalFFPGI[ccwc] * GrainFill[ccwc]);//ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];
							}
						
							//	dfPGI = 0.0;
							//	dfPGI = day_TDD[ccwc] / max_TDD[ccwc];
							//	day_need_N[ccwc] = maxmn[ccwc] * dfPGI;

						}
						else if (crop[ccwc] == 3 || crop[ccwc] == 29) //soybean and alfalfa
						{

							ffPGI = (33.057 * pow(PGI[ccwc], 4) - 92.276 * pow(PGI[ccwc], 3) + 52.899 * pow(PGI[ccwc], 2) - 3.6027 * PGI[ccwc] + 0.0419) * 1.0;//for agmip ET
							ffPGI = -0.0026 * pow(PGI[ccwc], 3) + 0.4802 * pow(PGI[ccwc], 2) - 13.3 * PGI[ccwc] + 96.9;
							ffPGI = (157.5 * pow(PGI[ccwc], 4) - 389.35 * pow(PGI[ccwc], 3) + 260.78 * pow(PGI[ccwc], 2) - 24.219 * PGI[ccwc] + 0.8611) * 1.0;
							ffPGI = -4.7468677 * pow(PGI[ccwc], 3) + 4.237085 * pow(PGI[ccwc], 2) + 0.9928785 * pow(PGI[ccwc], 1) - 0.0826368;//trying out new growth

							ffPGI = -0.9811400 * pow(PGI[ccwc], 3) - 2.5991566 * pow(PGI[ccwc], 2) + 4.0115191 * pow(PGI[ccwc], 1) - 0.1481734;
							if (ffPGI < 0)
								ffPGI = 0.01;
							if (ffPGI < 0.15)
								ffPGI = 0.15;
							//if (PGI[ccwc] < 0.05)
								//ffPGI = 0.25*(PGI[ccwc]/0.05);
							//if (PGI[ccwc] < 0.2)
							//	ffPGI = 0.01;




							if (PGI[ccwc] >= GrainFill[ccwc])
							{
								day_need_N[ccwc] = (ffPGI * plantNGrowthStage * GrainFill[ccwc] / 0.5) / (totalFFPGI[ccwc] * (1 - GrainFill[ccwc]));//ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];
							}
							else
							{
								day_need_N[ccwc] = (ffPGI * plantNGrowthStage) / (totalFFPGI[ccwc] * GrainFill[ccwc]);//ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];
							}

							//dfPGI = 0.0;
							//dfPGI = day_TDD[ccwc] / max_TDD[ccwc];
							//day_need_N[ccwc] = maxmn[ccwc] * dfPGI;

						//day_need_N[ccwc]=ffPGI*maxmn[ccwc]/totalFFPGI[ccwc];

						

						//dfPGI = 0.0;
						//dfPGI = day_TDD[ccwc] / max_TDD[ccwc];
						//day_need_N[ccwc] = maxmn[ccwc] * dfPGI;


						}
						else if (crop[ccwc] == 57) //canola
						{

							if (PGI[ccwc] <= 0.34) //vegetative stage PGI<=0.5

								ffPGI = 0.00009 * exp(17.193 * PGI[ccwc]);
							else if (PGI[ccwc] > 0.34 && PGI[ccwc] <= 0.89) //vegetative stage PGI<=0.5
								ffPGI = -0.0568 * PGI[ccwc] + 0.0547;
							else//reproductive stage
								ffPGI = 0.0;


							day_need_N[ccwc] = ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];


						}

						else //uses this for alfalfa but shouldn't if its not flagged perrenial
						{


							if (PGI[ccwc] <= 0.5) //vegetative stage
								ffPGI = PGI[ccwc] / (0.5 + PGI[ccwc]) * (1.0 - PGI[ccwc]) / (0.5 + PGI[ccwc]) * GWa;
							else//reproductive stage
								ffPGI = PGI[ccwc] / (0.5 + PGI[ccwc]) * (1.0 - PGI[ccwc]) / (0.5 + PGI[ccwc]) * GWb;
							if (ffPGI < 0.0) ffPGI = 0.0;

							day_need_N[ccwc] = ffPGI * maxmn[ccwc] / totalFFPGI[ccwc];
						}



						//bypass all crop curves

						/*
							// Tunable logistic parameters
							const double m = cropTime[ccwc];// = 0.35;   // inflection at 30% of thermal time
							const double k = cropGRate[ccwc];//10.0;   // steepness; higher = sharper mid-season surge
							float blah;
							blah = 1.0;
							// Safety helpers
							auto clamp01 = [](double x) {
								if (x < 0.0) return 0.0;
								if (x > 1.0) return 1.0;
								return x;
								};

							auto logistic = [&](double f) {
								// for numerical stability with large k, clamp the exponent argument
								const double x = -k * (f - m);
								// avoid overflow in exp(x) for large |x|
								const double x_clamped = max(-40.0, min(40.0, x));
								return 1.0 / (1.0 + exp(x_clamped));
								};

							// Compute normalized thermal progress
							double denom = max(1e-9, max_TDD[ccwc]);  // avoid divide-by-zero
							double f = clamp01(TDD[ccwc] / denom);
							//double f1 = clamp01(OLDPGI[ccwc]);

							// Current cumulative growth fraction (sigmoidal)
							double curveK = logistic(f);
							//double curveK_prev = logistic(f1);

							// DAILY increment in growth fraction
							double delta = curveK - curveK_prev[ccwc];
							if (delta < 0.0) delta = 0.0;  // guard against numerical/ordering issues

							// Daily N demand based on increment
							day_need_N[ccwc] = maxmn[ccwc] * delta;
							curveK_prev[ccwc] = curveK;
							// Update stored state for next timestep
							
							*/



						//}//end else Wentian soybean
						if (totalFFPGI[ccwc] == 0.0)
							day_need_N[ccwc] = 0.0;

						//	float real_need_N;
						//	int daysPlant;
						//	daysPlant=crop_days[ccwc];
						//	real_need_N=optffPGI[daysPlant-10][3];


					}
			if(PerennialFlag[ccwc]==1) //For Perrenial crops then the growth is tied to GDD 
			
				

				
				if(crop[ccwc]==10||crop[ccwc]==5||crop[ccwc]==4||crop[ccwc]==12||crop[ccwc]==11 )//&& vernal[ccwc]==0
				{
					
					float maxNScale;
					day_need_N[ccwc]=0.0;
					if(plantn[ccwc]<(maxmn[ccwc]))
					{
									float pGIScalar;
								if(perRegrow[ccwc]==0)//first cut
								{
									
									
									if(per[ccwc][1]<=0.0)
										{
										day_need_N[ccwc]=0.0;
										}
									else
									{
										if(jdcut[1]==jday)//this triggers a weird N demand sometimes
										{
											maxNScale=	((per[ccwc][1])/(maxmn[ccwc]));
											//maxNScale=2000.01;
											}
										else
										{
											maxNScale=	((per[ccwc][1])/(maxmn[ccwc]));
										}
		                                                                               //currentCut was causing a 1 day break where it would try to use the precalculated daily N uptake to deterimine N
										dfPGI = day_TDD[ccwc] / max_TDD[ccwc];
										//pGIScalar=1.0;
													//if(PGI[ccwc]>0.6)
														//pGIScalar=1-PGI[ccwc];
										ffPGI=(27.423*PGI[ccwc]+1)/maxNScale*1.9;//*2.6;//dfPGI*3/0.1
										ffPGI = (1.423 * PGI[ccwc]+1)/maxNScale;//test Andrea //was finding this was contributing to poor initial perrenial growth. 
 										ffPGI = (12.423 * (PGI[ccwc]) * (PGI[ccwc])) / maxNScale * 1.32 + (1.0 * (1 - PGI[ccwc])) / maxNScale * 1.32;
										day_need_N[ccwc]=ffPGI;
										if (year == 30 && jday == 188)
										{
											float blah;

											blah = 2.0;
										}
									}
								}
								else
								{
									float parScale;
														parScale=pow(PAR/30,15);
														parScale=min(1.0,max(0.0,parScale));
													
														
														
									
									
									if(per[ccwc][1]<=0.0)
									{
										day_need_N[ccwc]=0.0;}
									else
									{
										if(jdcut[currentCut-1]==jday)
										{
											maxNScale=((per[ccwc][1])/(maxmn[ccwc]));//0.676
										maxNScale=2000.01;
										}
										else
										{
											maxNScale=((per[ccwc][1])/(maxmn[ccwc]));
										}
									

									dfPGI = day_TDD[ccwc] / max_TDD[ccwc];

									parScale=1.0;

									ffPGI=(12.423*PGI[ccwc])/maxNScale*1.20*parScale;
									ffPGI=(12.423*(PGI[ccwc])*(PGI[ccwc]))/maxNScale*1.32+(1.0*(1-PGI[ccwc]))/maxNScale*1.32;

									day_need_N[ccwc]=ffPGI;
									}
								}
						
										








					}
					else
					{
						day_need_N[ccwc]=0.0;
					}
				//day_need_N[ccwc]=maxmn[ccwc]*
				}
				else if(crop[ccwc]==89 )//&& vernal[ccwc]==0
				{
					float maxNScale;
					day_need_N[ccwc]=0.0;

					if(plantn[ccwc]<maxmn[ccwc])
					{
									float pGIScalar;
								if(perRegrow[ccwc]==0)
								{
									
									
									if(per[ccwc][1]<=0.0)//currentCut
									{day_need_N[ccwc]=0.0;}
									else
									{
										if(jdcut[1]==jday)
										{
											maxNScale=	((per[ccwc][1])/maxmn[ccwc]);
											maxNScale=2000.01;}
										else
										{
											maxNScale=	((per[ccwc][1])/maxmn[ccwc]);
										}
		                                                                               //currentCut was causing a 1 day break where it would try to use the precalculated daily N uptake to deterimine N
									dfPGI = day_TDD[ccwc] / max_TDD[ccwc];
									//pGIScalar=1.0;
													//if(PGI[ccwc]>0.6)
														//pGIScalar=1-PGI[ccwc];
									ffPGI=(27.423*PGI[ccwc]+1)/maxNScale*1.0;//*2.6;//dfPGI*3/0.1
									day_need_N[ccwc]=ffPGI;
									
									}
								}

								else
								{
									float parScale;
														parScale=pow(PAR/30,15);
														parScale=min(1.0,max(0.0,parScale));
													
														
														
									
									
									if(per[ccwc][1]<=0.0)
									{
										day_need_N[ccwc]=0.0;}
									else
									{
										if(jdcut[currentCut-1]==jday)
										{
											maxNScale=((per[ccwc][1])/maxmn[ccwc]);//0.676
										maxNScale=2000.01;
										}
										else
										{
											maxNScale=((per[ccwc][1])/maxmn[ccwc]);
										}
									
										dfPGI = day_TDD[ccwc] / max_TDD[ccwc];
									
									parScale=1.0;
									

									ffPGI=(-784.86/2*PGI[ccwc]*PGI[ccwc])/maxNScale + ((1017.2/2*PGI[ccwc])/maxNScale) - 216.97/2/maxNScale;
									ffPGI=max(0.0,ffPGI);

									day_need_N[ccwc]=ffPGI;
									}
								}
						
										







					}
					else
					{
						day_need_N[ccwc]=0.0;
					}
				//day_need_N[ccwc]=maxmn[ccwc]*
				
				}
				
				



				
				
				else{
					//Li code for Perrenial Growth
						{

							dfPGI = day_TDD[ccwc] / max_TDD[ccwc];
							day_need_N[ccwc] = maxmn[ccwc] * dfPGI;

					
							if(PGI[ccwc]<=0.2&&crop[ccwc]!=20&&air_temp<10.0) //early vegetative stage
							{
								dfPGI *= 1.0;//0.2;
							}
							else if(PGI[ccwc]<=0.5)//vegetative stage
							{
								dfPGI *= 1.1;//1.2;
							}
							else //reproductive stage
							{
								if(GrainN[ccwc]>=MaxGrainN[ccwc]) dfPGI = 0.0; 
								//else dfPGI *= 1.5;
								else dfPGI *= 1.1;
							}
					
							if (air_temp <= 5.0)
							{
								dfPGI*= 0.02;
							}
							if (DayPETRs < 10)
							{

								dfPGI *= 0.02;
							}
						
							day_need_N[ccwc] = maxmn[ccwc] * dfPGI;//sets the growth to strictly be tied to GDD growth
						}

						
					//End Li Code for Perrenial Growth		
					}//end else


				
					


					//Perennial

				


					float F_salinity = 1.0 / (1.0 + salinity * 0.02);
									
					float parScale;
				

					parScale = 1.0;
					parScale=min(1.0,max(0.0,parScale));
					
					
					//day_need_N[ccwc]=max(day_need_N[ccwc],0.0);

				
					
					//figure out a way to add RUE
					float rueMaxDayN;
					float RUEStress;
					RUEStress = 1.0;
					
					
					rueMaxDayN = (DayPETRs * 10000.0 * 0.6 * 2.0 * 0.45)/plantcn[ccwc]/1000;
					//if (day_need_N[ccwc] > rueMaxDayN && PGI[ccwc] > 0.33 && PGI[ccwc] < 0.38 && crop[ccwc] == 8) testing 
					if (day_need_N[ccwc] > rueMaxDayN &&crop[ccwc]==888)//if (day_need_N[ccwc] > rueMaxDayN && PGI[ccwc] > 0.10 && PGI[ccwc] < 0.55 &&crop[ccwc]==8)
					{
						//stuntGrowth*= pow((rueMaxDayN / day_need_N[ccwc]),0.5);
						
							stuntGrowth *= 0.970;//.93 for normandin 0.99 for breton  was .97
						
							
						

					}

					
					//testing turning off
				//	T_stress = 1.0;
				//	stuntGrowth = 1.0;
				//	parScale = 1.0;
				//	RUEStress = 1.0;
				
					//check if tillage and moisture a factor//won't work for winter wheat wihtout carrying over tillYieldFact
					float effClay;
					effClay = -0.1143* clay[1]+1;//clay texture effect, fine textured soils are more effected by moisture than coarse
					effClay = min(1.0, max(0.99, effClay));
						
					
					float avgWaterContent = 0.0;
					float avgFieldCapacity = 0.0;
					if (PGI[ccwc] < 0.2)//check in early stages of growth
					{
						for (int il = 1; il <= 10; il++)
						{
							avgWaterContent += day_wfps[il];
							avgFieldCapacity += fldcap[il];

						}
						avgWaterContent = avgWaterContent / 10;
						avgFieldCapacity = avgFieldCapacity / 10;

						if (avgWaterContent >= (avgFieldCapacity * 0.95) && till_fact == 1.0 && cumWaterStress1 < 10)//was 0.7 test if average water content in tillage profile is within 95% of field capacity
						{
							tillYieldFact *= effClay;
							cumWaterStress1 += 1;

						}
					}
					tillYieldFact = min(1.0, max(0.9, tillYieldFact));//maximum reduction is 10%.
					if (crop[ccwc] == 4 || crop[ccwc] == 5 || crop[ccwc] == 10 || crop[ccwc] == 11 || crop[ccwc] == 12)
					{
						tillYieldFact = 1.0;

					}


					float photoStress;
					if (crop[ccwc] == 3||crop[ccwc]==18)
					{
						if (PGI[ccwc] < 0.1||PGI[ccwc]>0.5)//added a yield reduction on photoperiod effect besides just TDD increase
						{
							photoStress = 1.0;
						}
						else 
						{
							photoStress = pow(photoPeriodStress[ccwc],1.00);//Brian was 0.25

							//photoStress = 1.0;
						}
					}

					else 
					{
						photoStress = 1.0;
					}

					/*
					if (crop[ccwc] == 18 && harvIdxFlag == 1 && PGI[ccwc] <= 0.5 && PGI[ccwc]>0.25 && photoStress<1.0)
					{

						float changeHi=0.0;
						if (photoStress<1.0) //Potato heat stress at tuber initiatiion. 
						{
							changeHi = -1.0* (pow((photoStress-1.0),3) * grain[ccwc]);
							//changeHi=((1-(-15.097*maxTempAvg+407.77)/100)*grain[ccwc]);
							if ((grain[ccwc] - changeHi) > 0.05)
							{
								grain[ccwc] -= changeHi;
								stem[ccwc] += changeHi / 2;
								leaf[ccwc] += changeHi / 2;
							}
							else
							{
								stem[ccwc] += (grain[ccwc] - 0.05) / 2;
								leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
								grain[ccwc] = 0.05;
							}
							//harvIdxFlag = 0;
						}
					}
					*/
					//T_stress = 1.0;
					//photoStress = 1.0;
				

					//=============================================================================== testing a frostkill parameter
					/*
					if (CoverCrop[ccwc] == 1 && min_temp < FrostKill[ccwc]&&crop[ccwc]==47)
					{
						maturity_flag[ccwc] = 1;
						
						crop_senescence(ccwc);
						CoverCrop[ccwc] = 0;

					
					}
					*/

					//float RUEStress;
					RUEStress = pow(DayPETRs / 25.0, 0.50);//tie in growth to RUE
					
					if (PGI[ccwc] > 0.5)
					{
						RUEStress = pow(DayPETRs / 15.0, 0.1);//tie in growth to RUE
						//if (crop[ccwc] == 3)RUEStress = pow(DayPETRs / 45.0, 0.10);//tie in growth to RUE
					}
					if (PGI[ccwc] > 0.5 && crop[ccwc] == 20)
					{
						RUEStress = pow(DayPETRs / 25.0, 0.50);//tie in growth to RUE

					}
					if (crop[ccwc] == 200)
					{
						RUEStress = pow(DayPETRs / 20.0, 0.20);//tie in growth to RUE
						if (DayPETRs < 5.0)
						{
							RUEStress = 0.1;
						}
					}
					

						RUEStress = min(1.0, max(0.45, RUEStress));
						//RUEStress = 1.0;

					//cover crop RUE stress
					float coverCropRUE;
					coverCropRUE = 1.0;
					float maxLAI;
					maxLAI= ((Leaf_Wt[1]) / (startOptLeafC[1] * 0.5)) * LAImax[1];
					if (ccwc >= 2 && Leaf_Wt[1] > 1000.0 && lai[1] > 3.0) // will need to turn this off with light stress. 
					{
						float blah;
						coverCropRUE = (DayPETRs * exp(-0.8 * lai[1])) / DayPETRs;
						coverCropRUE = (DayPETRs * exp(-0.8 * maxLAI)) / DayPETRs;
						
					}
					else if(DayPETRs<10.0 && ccwc>=2 )
					{
						coverCropRUE = 0.10;
					}

						//RUEStress = 1.0;
		
					//lightStressFactor[ccwc] = 1.0; //turn off once it works//theo

					//lightStressFactor[ccwc] = min(1.0, max(0.2, lightStressFactor[ccwc]));//test)
					//lightStressFactor[ccwc] = 1.0;	

					



					day_N_demand[ccwc] = (day_need_N[ccwc] * T_stress * F_salinity)*winterKill[ccwc]*parScale*stuntGrowth*GrassProductivityFactor*RUEStress*tillYieldFact* photoStress* lightStressFactor[ccwc];//WSEffect * * ffPGI , jarovization_flag *winterKillRed
				///	day_need_N[ccwc] *= stuntGrowth;//test this
				
					if(crop[ccwc]==20&&flood_flag==0) day_N_demand[ccwc] *= 0.5;
					
					//TPNN += day_N_demand[ccwc];

					//float wst = TPNN;
				}			  
				else  
				{
					day_N_demand[ccwc] = 0.0;
					/*if(TDD[ccwc]>=max_TDD[ccwc]) 
					{
						maturity_flag[ccwc]++;
						if(IrriRice_flag==1) rice_maturity_flag=1;//crop[ccwc]==20
					}*/

					//maturaty_flag[ccwc]++;
				}
			}
			else
				day_N_demand[ccwc] = 0.0;


				
				////reset to old//////////////////////////////////////////////////////////////////////////////////////////////////
				/*
				float dfPGI = 0.0;

				dfPGI = day_TDD[ccwc] / max_TDD[ccwc];

				if (PGI[ccwc] <= 0.2 && crop[ccwc] != 20 && air_temp < 10.0) //early vegetative stage
				{
					dfPGI *= 1.0;//0.2;
				}
				else if (PGI[ccwc] <= 0.5)//vegetative stage
				{
					dfPGI *= 1.1;//1.2;
				}
				else //reproductive stage
				{
					//if(GrainN[ccwc]>=MaxGrainN[ccwc]) dfPGI = 0.0; 
					//else dfPGI *= 1.5;
					dfPGI *= 1.1;
				}

				day_need_N[ccwc] = maxmn[ccwc] * dfPGI;

				float F_salinity = 1.0 / (1.0 + salinity * 0.02);

				day_N_demand[ccwc] = day_need_N[ccwc] * T_stress * F_salinity;//WSEffect * * ffPGI , jarovization_flag

				if (crop[ccwc] == 20 && flood_flag == 0) day_N_demand[ccwc] *= 0.5;

				//TPNN += day_N_demand[ccwc];

				//float wst = TPNN;
			*/

				//end reset
				


	}

	
	if(ice[1]>0.0||snow_pack>0.0) day_N_demand[ccwc] = 0.0;

	//day_N_demand[ccwc] *= CO2_factor;

/*	if(crop[ccwc]==20)
	{
		//Heat stress for young shoots
		if(PGI[ccwc]<0.4&&max_temp>25.0)
		{
			day_N_demand[ccwc] *= 0.5;
		}

		//Wind damage during flowering
		if(wind_speed>5.0&&PGI[ccwc]>0.75) 
		{
			day_N_demand[ccwc] *= 0.0;
		}

		//Wind damage 
		if(wind_speed>9.0)
			wind_damage_flag = 0.0;//10.0

		if(wind_damage_flag>0.0)
		{
			day_N_demand[ccwc] = 0.0;
			wind_damage_flag -= 0.5;
			if(wind_damage_flag<0.0) wind_damage_flag = 0.0;
		}
	}
*/
	if(crop[ccwc]==2&&air_temp<5.0) 
		day_N_demand[ccwc] *= 1.0;
//day_need_N[ccwc]=min(10,max(day_need_N[ccwc],0.0));


	ideal_DayCropC[ccwc] = day_need_N[ccwc] * plantcn[ccwc];

	
 
}

/*
void class_model::n_uptake_by_crop(int ccwc)//for CropModel=0
{
    int i;
    float    layer_demand, layer_up_no3, layer_up_nh4, layer_up_nh3, UPP;
    float layer_up, day_Nuptake_from_clayN, day_SoilN_demand;

	day_Nuptake_from_clayN=0.0;

    if (seed[ccwc]==1) ddupn[ccwc] = 0.0;

    demandn[ccwc] += day_N_demand2[ccwc];


	//Li code for N fix
	
	//end Li code

	//new code for leakage from other N fixing crops
	int crops;
if(max_N_fix[ccwc]==0.0)
{
	for(crops=1; crops<=CropNumbers; crops++)
	{
		if(ini_N_fix[crops]>0 && seed[crops]<=grow_days[crops] && seed[crops]>0)//testing to see if there is a Nfixing crop available to provide fixed N during N demand. Should be at a reduced rate. note ini_N_fix[crops] is to represent highest N fix rate available of co-crops
		{

			if (ini_N_fix[ccwc] == 0)
			{
			//	max_N_fix[ccwc] = ini_N_fix[crops] * 0.25* maxmn[ccwc];//calculates the maximum N available to be provided by N fixation. (adopts the N fixation rate of other N fixing crops) Likely should be at a 4:1 ratio as estimated by Laidlaw et al., 1996
			}
			else
			{
			//	max_N_fix[ccwc] = ini_N_fix[crops] * maxmn[ccwc];//calculates the maximum N available to be provided by N fixation. (adopts the N fixation rate of other N fixing crops) Likely should be at a 4:1 ratio as estimated by Laidlaw et al., 1996
			}

		}
		else
		{

			//max_N_fix[ccwc]=0.0;
		}
	}		

}
//end code for N fix leakage.

	if(max_N_fix[ccwc]>0.0) //test to see if Nfix is on
	{
		float tempFixN,nStatusFixN;
		float sumNO3,sumNH4,averageTemp3;
		int tempCounter;
		tempCounter=0;
		sumNO3=0.0;
		sumNH4=0.0;
		averageTemp3=0.0;
		
      int root_layer = (int)(root_length[ccwc]/h[1]); 
	  
			for(int xx=1; xx<q; xx++) //calculate the N in rooting depth
			{
				if(SoilDepth[xx]<=root_depth[ccwc])//was 0.3 depth  //root_depth[ccwc]   max_root_length[ccwc]
				{
					sumNO3 += no3[xx];
					sumNH4 += nh4[xx];
					averageTemp3 +=temp[xx];
					tempCounter +=1;
				}
			}
			
			
		averageTemp3=averageTemp3/tempCounter;  //apsim temperature adjustment on Nodulatation
		if (tempCounter < 1) averageTemp3 = air_temp;
		tempFixN= averageTemp3*averageTemp3*(55-averageTemp3)*powf(10,-4);
		tempFixN = (averageTemp3 * averageTemp3 * (40 - averageTemp3) * powf(10, -4))/0.9477;
		
		tempFixN=1.0;
		tempFixN=min(1.0,max(0.0,tempFixN));




		//calculate a N2 Nodulation efficiency based on Zhang McGill study.
		float N2NodEF;

		N2NodEF = 1.0 / ((25.0 - averageTemp3) * 1.8182 + 17.0); //25.0 = optimal temperature to generate full nodulation by V2-V3 stage/averageTemp3=rooting depth soil temp /1.8182 is slope of FIg 1 from Zhan/ 17.0 = days after emergence to expect full nodulations
		N2NodEFACC[ccwc] += N2NodEF; //add the 
		N2NodEFACC[ccwc] = min(1.0, max(0.0, N2NodEFACC[ccwc]));//accumulator set between 0 and 1.

		// Moisture stress on N fixation potential
		double wiltptw = h[1] * sts[1] * wiltpt[1];
		double fldcapw = h[1] * sts[1] * fldcap[1];

		float waterStressFactor, waterNodStress;

		//need to figure out water stress maybe using crop stress factor. day_CropWater???
		waterStressFactor = (water[1][1] - fldcapw) / (1.0 - fldcapw);

		waterNodStress = 1.6667 * waterStressFactor - 0.3333;  //adapted from APSIM - Modeling Flood-Induced Stress in Soybeans Feb 2020
		waterNodStress = 1.0 - (min(1.0, max(0.0, waterNodStress)));
		if (waterNodStress < 0.0) waterNodStress = 0.0;
		if (waterNodStress >1.0) waterNodStress = 1.0;



		//tempFixN = N2NodEFACC[ccwc];
		//calculate concentration conversion to kg N/ha of 10 g N /m3 and 30 g N /m3
		float conc10, conc30,concDNDC;
		float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;	//calculate bulk density of soil layer
		conc10=bulk_density*(3000)*10/1000;//bulk density * 3000 m3 volume of soil in a ha in .3m * 10 g N/kg /1000 g to kg.//units kg/ha 10000*max_root_length[ccwc]
		conc30=bulk_density*(3000)*30/1000;//units kg/ha 10000*max_root_length[ccwc]
		concDNDC=(sumNO3+sumNH4)*1000/(3000*bulk_density)*root_depth[ccwc];//units in g N /m3 10000*max_root_length[ccwc]
		
		conc10=400;//80
	    conc30=500;//was 30 for agmip soybean
		//concDNDC=(sumNO3+sumNH4);

		if((sumNO3+sumNH4)<conc10)//(sumNO3+sumNH4)<10)
		{
			nStatusFixN=1.0;
		}
		else if((sumNO3+sumNH4)>conc30)//(sumNO3+sumNH4)>30)
		{
			nStatusFixN = (conc30 / (sumNO3 + sumNH4));
			nStatusFixN = max(0.5, nStatusFixN);
			//nStatusFixN=0.0;
		
		}//was 0.0
		else
		{
			nStatusFixN=1-((sumNO3+sumNH4)/conc30);
			//	nStatusFixN=1.0-0.05*(concDNDC);//(sumNO3+sumNH4) //0.025
		}
			
		nStatusFixN=min(1.0,max(nStatusFixN,0.0));


		//nStatusFixN = 1.0;
		day_fixN[ccwc] = (day_N_demand2[ccwc] / maxmn[ccwc]) * max_N_fix[ccwc] * tempFixN * nStatusFixN;
		//nh4[5] += day_fixN[ccwc] * .25; messing around with exudates


		
		//old way before added the soy N fix to soil matrix 
		day_SoilN_demand = day_N_demand2[ccwc] - day_fixN[ccwc];
		day_soilN_from_Nfixation[ccwc] = day_fixN[ccwc];
		

		//soybean N fix to soil matrix
	
		//end soybean N fix to soil matrix



		//day_soilN_from_Nfixation[ccwc] = 0.5 * day_fixN[ccwc];
	    //float dfn = day_soilN_from_Nfixation[ccwc]/20.0; //why is DNDC adding N to the profile from N fixation?
		//for(int i=1;i<=20;i++) nh4[i] += dfn;
	}
	else
	{
		day_fixN[ccwc] = 0.0;
		day_SoilN_demand = day_N_demand2[ccwc];
	}


	///////////////////////////////////////START SECTION -root exudate soil N in multiple crop scenarios when one is a N fixer

	float fixedrootExudateN = 0.0;//accumulator for fixedrootExudateN
	
	int needNOtherCropFlag = 0;// is another non-Nfixer growing
	
	//need to test if there is multiple crops growing and a non-N fixer needing N-demand and is currently growing
	
	///////////////////////////////////////END SECTION -root exudate soil N in multiple crop scenarios when one is a N fixer 


	/////////////////////////////////////////////
	if(day_SoilN_demand>0.0&&FertOption==333)//precision fertilization
	{
		float DADF = day_SoilN_demand * 1.1;
		day_inFertN += DADF;
		yr_addfer += DADF;
		fert_flag = 1;
		for (int i=1; i<=2; i++) nh4[i] += (DADF / 2.0);
		
	}
	///////////////////////////////////////////////

    day_nup[ccwc] = 0.0;

	day_clay_N = 0.0;

	for(int vv=1; vv<=q; vv++) 
	{
		day_clay_N += clay_nh4[vv]; 
	}
	int root_layer = round(root_length[ccwc]/h[1]); 
	int QqQ = root_q;//was q
	QqQ=max(1,root_q);

	UPP = day_SoilN_demand;// / (float)QqQ;//* powf(0.5, i);
	float layer_Ndef = 0.0;//layer Demand N deficeit. 
    for ( i = 1; i <= QqQ; i++ )
    {
		//UPP = day_SoilN_demand;// / (float)QqQ;//* powf(0.5, i);
	    layer_up = 0.0;

	
		if (root_layer <= 1)
		{
			layer_demand = UPP ;
		}
		else
		{
			layer_demand = UPP * rootDensity[ccwc][i] + layer_Ndef;
		}
	
			float ava_nh4, ava_nh3, ava_no3;
			float layer_demand1, layer_demand2, layer_demand3;



//reduce N availability Roland CSW
//NreductionFactor=1.0;
	//n uptake reduction
	float Red_f_NO3 = no3[i] * 0.1;//(no3[i]/5) - 0.05;//25		//reduction factor for no3
	Red_f_NO3 = min(1.0, max(0.0, Red_f_NO3));

	float Red_f_NH4 = nh4[i] * (nh4[i]*0.1);//5		//reduction factor for nh4 and nh3
	Red_f_NH4 = min(1.0, max(0.0, Red_f_NH4));

	
	if ((no3[i] - 1.0) < 1)									//if NO3 in the layer is smaller than 5 kg
	{
		ava_no3 = no3[i] * NreductionFactor;//Red_f_NO3; was 0.1						//the available nitrate is the nitrate pool times reduction factor
											//the reduced nitrate amount is transferred to an intermediate variable
	}	
	else {ava_no3 = no3[i];}		//else available and intermediate variables are unreduced

	if ((nh4[i] - 1.0) < 1.0)									//if NH4 in the layer is smaller than 10 kg
	{
		ava_nh4 = nh4[i] * NreductionFactor;
		//ava_nh4 = nh4[i] * NreductionFactor;//Red_f_NH4; was 0.1						//the available ammonium is the nitrate pool times reduction factor
											//the reduced ammonium amount is transferred to an intermediate variable
	}
	else {ava_nh4 = nh4[i]; }		//else available and intermediate variables are unreduced

	if (nh3[i] < 0.1)									//if NH3 in the layer is smaller than 10 kg
	{
		ava_nh3 = nh3[i] * Red_f_NH4;						//the available ammonia is the nitrate pool times reduction factor
										//the reduced ammonia amount is transferred to an intermediate variable
	}
	else {ava_nh3 = nh3[i]; }

//Reduce N availability Roladn CSW




			float TotalAN = no3[i]+ nh4[i] + nh3[i] + 0.0000001;
			

			layer_demand1 = layer_demand * no3[i] / TotalAN;

			layer_demand2 = layer_demand * nh4[i] / TotalAN;

			layer_demand3 = layer_demand * nh3[i] / TotalAN;

			
			
			if ( layer_demand1 <= ava_no3 )
			{
			layer_up_no3 = layer_demand1 ;
			}
			else
			{
			layer_up_no3 = ava_no3;
			}

			if ( layer_demand2 <= ava_nh4 )
			{
			layer_up_nh4 = layer_demand2 ;
			}
			else
			{
			layer_up_nh4 = ava_nh4;
			}

			if ( layer_demand3 <= ava_nh3 )
			{
			layer_up_nh3 = layer_demand3 ;
			}
			else
			{
			layer_up_nh3 = ava_nh3;
			}
			

		
		float UPno3, UPnh4, UPnh3;
		if(no3[i] >= layer_up_no3) 
		{
			UPno3 = layer_up_no3;
			no3[i] -= UPno3;
		}
		else
		{
			UPno3 = no3[i];
			no3[i] = 0.0;
		}
		day_nup[ccwc] += UPno3;
	
		if(nh4[i] >= layer_up_nh4) 
		{
			UPnh4 = layer_up_nh4;
			nh4[i] -= UPnh4;
			if (i == 1)
			{
				float blah;
				blah = 1.0;

			}
		}
		else
		{
			UPnh4 = nh4[i];
			nh4[i] = 0.0;
		}
		day_nup[ccwc] += UPnh4;

		if(nh3[i] >= layer_up_nh3) 
		{
			UPnh3 = layer_up_nh3;
			nh3[i] -= UPnh3;
		}
		else
		{
			UPnh3 = nh3[i];
			nh3[i] = 0.0;
		}
		day_nup[ccwc] += UPnh3;

		if ( no3[i] < 0.0 ) no3[i] = 0.0;
		if ( nh4[i] < 0.0 ) nh4[i] = 0.0;
		if ( nh3[i] < 0.0 ) nh3[i] = 0.0;
		
		layer_up = UPno3 + UPnh4 + UPnh3;
		if (layer_demand > layer_up) {
			layer_Ndef = layer_demand - layer_up;
		}
		else
		{
			layer_Ndef = 0.0;
		}
		//UPP -= layer_up; //turn off for rootdensity uptake.... 
		if(UPP<0.0) UPP = 0.0;
		/*
		if ( layer_demand > layer_up )
		{
			 ddupn[ccwc] += (layer_demand - layer_up);
		}
		
		if ( ddupn[ccwc] < 0.0 ) ddupn[ccwc] = 0.0;

		if(i==QqQ) ddupn[ccwc] = 0.0;

		float aN = day_clay_N - base_clay_N;
		if(aN<0.0) aN=0.0;		
    

    } //end of layer loop for N uptake


	//--- new routine to take care of deficet N not uptook in a given layer. 
	if (day_N_demand2[ccwc] > (day_nup[ccwc] + day_plant_nh3[ccwc] + day_fixN[ccwc]))
	{
		
		
		
		//for (i = 1; i <= QqQ; i++)
		for (i = q; i >= 1; i--)
		{

			float layer_demand1, layer_demand2, layer_demand3;
			float TotalAN = no3[i] + nh4[i] + nh3[i] + 0.0000001;




			layer_demand1 = layer_demand * no3[i] / TotalAN;

			layer_demand2 = layer_demand * nh4[i] / TotalAN;

			layer_demand3 = layer_demand * nh3[i] / TotalAN;

			if (layer_demand1 <= no3[i])
			{
				layer_up_no3 = layer_demand1;
			}
			else
			{
				layer_up_no3 = no3[i];
			}

			if (layer_demand2 <= nh4[i])
			{
				layer_up_nh4 = layer_demand2;
			}
			else
			{
				layer_up_nh4 = nh4[i];
			}

			if (layer_demand3 <= nh3[i])
			{
				layer_up_nh3 = layer_demand3;
			}
			else
			{
				layer_up_nh3 = nh3[i];
			}


			float UPno3, UPnh4, UPnh3;
			if (no3[i] >= layer_up_no3)
			{
				UPno3 = layer_up_no3;
				no3[i] -= UPno3;
			}
			else
			{
				UPno3 = no3[i];
				no3[i] = 0.0;
			}
			day_nup[ccwc] += UPno3;

			if (nh4[i] >= layer_up_nh4)
			{
				UPnh4 = layer_up_nh4;
				nh4[i] -= UPnh4;
				if (i == 1)
				{
					float blah;
					blah = 1.0;

				}
			}
			else
			{
				UPnh4 = nh4[i];
				nh4[i] = 0.0;
			}
			day_nup[ccwc] += UPnh4;

			if (nh3[i] >= layer_up_nh3)
			{
				UPnh3 = layer_up_nh3;
				nh3[i] -= UPnh3;
			}
			else
			{
				UPnh3 = nh3[i];
				nh3[i] = 0.0;
			}
			day_nup[ccwc] += UPnh3;

			if (no3[i] < 0.0) no3[i] = 0.0;
			if (nh4[i] < 0.0) nh4[i] = 0.0;
			if (nh3[i] < 0.0) nh3[i] = 0.0;

			layer_up = UPno3 + UPnh4 + UPnh3;
			layer_demand -= layer_up;
		}
		//end new routine
		

	}

	//if(ddupn[ccwc]>0.00001&&WaterControl==2&&day_WT>-0.5&&FloodWater_N>0.0)//wetland plants
	if(UPP>0.00001&&WaterControl==2&&day_WT>-0.5&&FloodWater_N>0.0)//wetland plants
	{
			float Wn=0.0;
			
			if(FloodWater_N>0.0)
			{
				//if(ddupn[ccwc]>=FloodWater_N)
				if(UPP>=FloodWater_N)
				{
					Wn = FloodWater_N; 
					FloodWater_N = 0.0;
					UPP -= Wn;
				}
				else
				{
					Wn = UPP;//ddupn[ccwc]; 
					FloodWater_N -= Wn;
					UPP = 0.0;//ddupn[ccwc] = 0.0;
				}
			}
			
			day_nup[ccwc] += Wn;
	}

	day_nup[ccwc] += day_Nuptake_from_clayN;

	for ( i = 1; i <= q; i++ )
    {
		clay_nh4[i] = day_clay_N * powf(0.5, i);
	}

    if (seed[ccwc]==grow_days[ccwc]-1) UPP = 0.0;//ddupn[ccwc] = 0.0;

   // N stress
   if(day_N_demand2[ccwc] > 0.0)
     N_stress[ccwc] = (day_nup[ccwc]+day_plant_nh3[ccwc]+day_fixN[ccwc])/(day_N_demand2[ccwc]);//buffering
   else
     N_stress[ccwc] = 1.0;

   if (N_stress[ccwc] < 0.95)
   {
	   float blah;
	   blah = 1.0;

   }
   N_stress[ccwc] = min(1.0, max(0.0, N_stress[ccwc]));

#ifdef PHOSPHOROUS
   //P uptake by crop
   day_P_demand[ccwc] = (day_nup[ccwc]+day_plant_nh3[ccwc]+day_fixN[ccwc]) / 15.0;//Koerselman and Meuleman, 1996, J. of Applied Ecology 33:1441-1450.
   
   for ( i = 1; i <= q; i++ )
   {
		if(LabP[i]>0.0&&day_P_demand[ccwc]>0.0)
		{
			if(day_P_demand[ccwc]>=LabP[i]) 
			{
				day_P_uptake[ccwc] += LabP[i];
				day_P_demand[ccwc] -= LabP[i];
				LabP[i] = 0.0;
			}
			else
			{
				day_P_uptake[ccwc] += day_P_demand[ccwc];
				day_P_demand[ccwc] = 0.0;
			}
		}
   }   
   plantP[ccwc] += day_P_uptake[ccwc];
   GrainP[ccwc] += 0.6 * day_P_uptake[ccwc];
   LeafP[ccwc] += 0.2 * day_P_uptake[ccwc];
   StemP[ccwc] += 0.1 * day_P_uptake[ccwc];
   RootP[ccwc] += 0.1 * day_P_uptake[ccwc];

#endif
 
}
*/

// chatgpt fix
void class_model::n_uptake_by_crop(int ccwc) // for CropModel=0
{
	int i;
	// Promote sensitive numerics to double where they accumulate or drive branching
	double UPP_d, day_Nuptake_from_clayN_d, day_SoilN_demand_d;

	float layer_up_no3, layer_up_nh4, layer_up_nh3; // write-backs stay float
	float layer_up;                                  // per-layer sum (float for storage symmetry)

	day_Nuptake_from_clayN_d = 0.0;
	if (seed[ccwc] == 1) ddupn[ccwc] = 0.0;                       // as-is
	demandn[ccwc] += day_N_demand2[ccwc];                         // as-is

	// --- N fixation prelude (unchanged logic; minor safety) --------------------
	// NOTE: I left your “leakage from other N fixing crops” logic as-is/commented.
	N_CompFactor(); // Theo  // as-is

	if (max_N_fix[ccwc] > 0.0)
	{
		float tempFixN, nStatusFixN;
		float sumNO3 = 0.0f, sumNH4 = 0.0f, averageTemp3 = 0.0f;
		int tempCounter = 0;

		int root_layer = round(root_length[ccwc] / h[1]);
		for (int xx = 1; xx < q; xx++) // rooting depth sum (as-is)
		{
			if (SoilDepth[xx] <= root_depth[ccwc])
			{
				sumNO3 += no3[xx];
				sumNH4 += nh4[xx];
				averageTemp3 += temp[xx];
				tempCounter += 1;
			}
		}
		// *** Guard division by zero
		if (tempCounter > 0) averageTemp3 = averageTemp3 / tempCounter;
		else                 averageTemp3 = air_temp;

		// Your temp polynomials (you set to 1.0 later). Keeping intent as-is.
		tempFixN = averageTemp3 * averageTemp3 * (55 - averageTemp3) * powf(10, -4);
		tempFixN = (averageTemp3 * averageTemp3 * (40 - averageTemp3) * powf(10, -4)) / 0.9477;
		tempFixN = 1.0f;
		tempFixN = min(1.0f, max(0.0f, tempFixN));

		// Nodulation accumulator (as-is)
		float N2NodEF;
		N2NodEF = 1.0f / ((25.0f - averageTemp3) * 1.8182f + 17.0f);
		N2NodEFACC[ccwc] += N2NodEF;
		N2NodEFACC[ccwc] = min(1.0f, max(0.0f, N2NodEFACC[ccwc]));

		// Moisture stress (as-is)
		double wiltptw = h[1] * sts[1] * wiltpt[1];
		double fldcapw = h[1] * sts[1] * fldcap[1];
		double waterStressFactor = (water[1][1] - fldcapw) / (1.0 - fldcapw);
		double waterNodStress = 1.6667 * waterStressFactor - 0.3333;
		waterNodStress = 1.0 - (min(1.0, max(0.0, waterNodStress)));
		if (waterNodStress < 0.0) waterNodStress = 0.0;
		if (waterNodStress > 1.0) waterNodStress = 1.0;

		// Concentration logic (kept as-is)
		float conc10, conc30, concDNDC;
		float bulk_density = mmm[1] / 10000.0f / h[1] / 1000.0f;
		conc10 = bulk_density * 3000.0f * 10.0f / 1000.0f;
		conc30 = bulk_density * 3000.0f * 30.0f / 1000.0f;
		concDNDC = (sumNO3 + sumNH4) * 1000.0f / (3000.0f * bulk_density) * root_depth[ccwc];
		conc10 = 100.0f;
		conc30 = 200.0f;

		if ((sumNO3 + sumNH4) < conc10) {
			nStatusFixN = 1.0f;
		}
		else if ((sumNO3 + sumNH4) > conc30) {
			nStatusFixN = (conc30 / (sumNO3 + sumNH4));
			nStatusFixN = max(0.5f, nStatusFixN);
		}
		else {
			nStatusFixN = 1.0f - ((sumNO3 + sumNH4) / conc30);
		}
		nStatusFixN = min(1.0f, max(nStatusFixN, 0.0f));

		day_fixN[ccwc] = (day_N_demand2[ccwc] / maxmn[ccwc]) * max_N_fix[ccwc] * tempFixN * nStatusFixN;

		day_SoilN_demand_d = static_cast<double>(day_N_demand2[ccwc] - day_fixN[ccwc]);
		day_soilN_from_Nfixation[ccwc] = day_fixN[ccwc];
	}
	else
	{
		day_fixN[ccwc] = 0.0f;
		day_SoilN_demand_d = static_cast<double>(day_N_demand2[ccwc]);
	}

	// Precision fertilization (as-is)
	if (day_SoilN_demand_d > 0.0 && FertOption == 333)
	{
		float DADF = static_cast<float>(day_SoilN_demand_d * 1.1);
		day_inFertN += DADF;
		yr_addfer += DADF;
		fert_flag = 1;
		for (int i = 1; i <= 2; i++) nh4[i] += (DADF / 2.0f);
	}

	// --- Initialize accumulators and bounds ------------------------------------
	day_nup[ccwc] = 0.0f;
	day_clay_N = 0.0f;
	for (int vv = 1; vv <= q; vv++) day_clay_N += clay_nh4[vv];

	int root_layer = round(root_length[ccwc] / h[1]);

	// *** Do NOT mutate root_q here; use a local, clamped copy
	const int capped_root_q = (root_q > q) ? q : root_q;
	const int QqQ = max(1, capped_root_q);

	UPP_d = day_SoilN_demand_d;                         // unmet soil N demand (double)
	double layer_Ndef_d = 0.0;                          // carried deficit between layers
	const double max_n_demand_d = static_cast<double>(day_N_demand2[ccwc]);
	double cumulative_n_uptake_d = 0.0;                 // running total in double

	// --- PASS 1: primary layer-by-layer uptake --------------------------------
	for (i = 1; i <= QqQ; i++)
	{
		// Deterministic per-layer demand
		double layer_demand_d = (root_layer <= 1)
			? UPP_d
			: UPP_d * static_cast<double>(rootDensity[ccwc][i]) + layer_Ndef_d;

		// Current pools as double
		double no3i = static_cast<double>(no3[i]);
		double nh4i = static_cast<double>(nh4[i]);
		double nh3i = static_cast<double>(nh3[i]);

		// Reduced availability with stable thresholds (eps = 1e-12)
		const double eps = 1e-12;
		double ava_no3 = (no3i < 2.0 - eps) ? no3i * NreductionFactor : no3i;
		double ava_nh4 = (nh4i < 2.0 - eps) ? nh4i * NreductionFactor : nh4i;
		double Red_f_NH4 = min(1.0, max(0.0, 0.1 * nh4i * nh4i));
		double ava_nh3 = (nh3i < 0.1 - eps) ? nh3i * Red_f_NH4 : nh3i;

		const double TotalAN = no3i + nh4i + nh3i;
		if (TotalAN <= 0.0) continue;

		const double fNO3 = no3i / TotalAN;
		const double fNH4 = nh4i / TotalAN;
		const double fNH3 = nh3i / TotalAN;

		const double dem_no3 = layer_demand_d * fNO3;
		const double dem_nh4 = layer_demand_d * fNH4;
		const double dem_nh3 = layer_demand_d * fNH3;

		// *** Single cap rule INCLUDING CF_N
		const double cfN = static_cast<double>(CF_N[ccwc]);
		double up_no3_d = min(dem_no3, ava_no3 * cfN);
		double up_nh4_d = min(dem_nh4, ava_nh4 * cfN);
		double up_nh3_d = min(dem_nh3, ava_nh3 * cfN);

		// Respect remaining daily demand ceiling
		const double room = max_n_demand_d - cumulative_n_uptake_d;
		if (room <= 0.0) break;
		const double denom = (up_no3_d + up_nh4_d + up_nh3_d);
		const double scale = (denom > 0.0) ? min(1.0, room / denom) : 0.0;
		up_no3_d *= scale;  up_nh4_d *= scale;  up_nh3_d *= scale;

		// Commit uptake to pools (cast back to float)
		layer_up_no3 = static_cast<float>(up_no3_d);
		layer_up_nh4 = static_cast<float>(up_nh4_d);
		layer_up_nh3 = static_cast<float>(up_nh3_d);

		if (no3[i] >= layer_up_no3) no3[i] -= layer_up_no3; else no3[i] = 0.0f;
		if (nh4[i] >= layer_up_nh4) nh4[i] -= layer_up_nh4; else nh4[i] = 0.0f;
		if (nh3[i] >= layer_up_nh3) nh3[i] -= layer_up_nh3; else nh3[i] = 0.0f;

		// Accumulate totals in double
		const double layer_up_d = up_no3_d + up_nh4_d + up_nh3_d;
		cumulative_n_uptake_d += layer_up_d;
		day_nup[ccwc] += static_cast<float>(layer_up_d);

		// Update inter-layer deficit deterministically
		layer_Ndef_d = max(0.0, layer_demand_d - layer_up_d);

		// If you want UPP to shrink by actual uptake, uncomment:
		// UPP_d = max(0.0, UPP_d - layer_up_d);
		if (UPP_d < 0.0) UPP_d = 0.0; // keep original guard style
	}

	// --- Compute remaining demand for PASS 2 -----------------------------------
	double remaining = max_n_demand_d
		- (static_cast<double>(day_nup[ccwc]) + static_cast<double>(day_plant_nh3[ccwc]) + static_cast<double>(day_fixN[ccwc]));
	if (remaining < 0.0) remaining = 0.0;

	// --- PASS 2: deterministic redistribution of remaining demand --------------
	if (remaining > 1e-15)
	{
		// Normalize weights over 1..QqQ using rootDensity; fallback to equal weights
		double sum_w = 0.0;
		for (int k = 1; k <= QqQ; ++k)
			sum_w += max(0.0, static_cast<double>(rootDensity[ccwc][k]));
		if (sum_w <= 0.0) sum_w = static_cast<double>(QqQ); // equal weights if all zero

		for (i = QqQ; i >= 1 && remaining > 1e-15; --i)
		{
			const double w_i = max(0.0, static_cast<double>(rootDensity[ccwc][i]));
			const double wi_over_sum = (sum_w > 0.0) ? (w_i / sum_w) : (1.0 / static_cast<double>(QqQ));
			double layer_demand_d = remaining * wi_over_sum;

			double no3i = static_cast<double>(no3[i]);
			double nh4i = static_cast<double>(nh4[i]);
			double nh3i = static_cast<double>(nh3[i]);
			const double TotalAN = no3i + nh4i + nh3i;
			if (TotalAN <= 0.0) { sum_w -= w_i; if (sum_w < 0.0) sum_w = 0.0; continue; }

			// same availability rules as pass 1 (stable thresholds)
			const double eps2 = 1e-12;
			double ava_no3 = (no3i < 2.0 - eps2) ? no3i * NreductionFactor : no3i;
			double ava_nh4 = (nh4i < 2.0 - eps2) ? nh4i * NreductionFactor : nh4i;
			double Red_f_NH4 = min(1.0, max(0.0, 0.1 * nh4i * nh4i));
			double ava_nh3 = (nh3i < 0.1 - eps2) ? nh3i * Red_f_NH4 : nh3i;

			const double fNO3 = no3i / TotalAN, fNH4 = nh4i / TotalAN, fNH3 = nh3i / TotalAN;
			const double dem_no3 = layer_demand_d * fNO3;
			const double dem_nh4 = layer_demand_d * fNH4;
			const double dem_nh3 = layer_demand_d * fNH3;

			const double cfN = static_cast<double>(CF_N[ccwc]);
			double up_no3_d = min(dem_no3, ava_no3 * cfN);
			double up_nh4_d = min(dem_nh4, ava_nh4 * cfN);
			double up_nh3_d = min(dem_nh3, ava_nh3 * cfN);

			const double denom = (up_no3_d + up_nh4_d + up_nh3_d);
			const double scale = (denom > 0.0) ? min(1.0, remaining / denom) : 0.0;
			up_no3_d *= scale;  up_nh4_d *= scale;  up_nh3_d *= scale;

			// Write-back
			layer_up_no3 = static_cast<float>(up_no3_d);
			layer_up_nh4 = static_cast<float>(up_nh4_d);
			layer_up_nh3 = static_cast<float>(up_nh3_d);

			if (no3[i] >= layer_up_no3) no3[i] -= layer_up_no3; else no3[i] = 0.0f;
			if (nh4[i] >= layer_up_nh4) nh4[i] -= layer_up_nh4; else nh4[i] = 0.0f;
			if (nh3[i] >= layer_up_nh3) nh3[i] -= layer_up_nh3; else nh3[i] = 0.0f;

			const double layer_up_d = up_no3_d + up_nh4_d + up_nh3_d;
			remaining -= layer_up_d;
			day_nup[ccwc] += static_cast<float>(layer_up_d);

			// consume weight to keep proportions for remaining layers
			sum_w -= w_i;
			if (sum_w < 0.0) sum_w = 0.0;
		}
	}

	// --- Floodwater uptake: use remaining, not stale UPP -----------------------
	if (remaining > 0.00001 && WaterControl == 2 && day_WT > -0.5 && FloodWater_N > 0.0)
	{
		float Wn = 0.0f;
		if (FloodWater_N > 0.0f)
		{
			if (remaining >= static_cast<double>(FloodWater_N))
			{
				Wn = FloodWater_N;
				FloodWater_N = 0.0f;
				remaining -= static_cast<double>(Wn);
			}
			else
			{
				Wn = static_cast<float>(remaining);
				FloodWater_N -= Wn;
				remaining = 0.0;
			}
		}
		day_nup[ccwc] += Wn;
	}

	// Clay NH4 redistribution (*** mass-conserving ***)
	{
		// Preserve original total in day_clay_N; normalize geometric weights
		double geom_sum = 0.0;
		for (int k = 1; k <= q; ++k) geom_sum += pow(0.5, static_cast<double>(k));
		if (geom_sum <= 0.0) geom_sum = 1.0;

		for (i = 1; i <= q; i++)
		{
			double w = pow(0.5, static_cast<double>(i)) / geom_sum;
			clay_nh4[i] = static_cast<float>(static_cast<double>(day_clay_N) * w);
		}
	}

	if (seed[ccwc] == grow_days[ccwc] - 1) {
		// UPP legacy flag; left as-is
		float UPP_dummy = 0.0f; (void)UPP_dummy;
	}

	// N stress (as-is)
	if (day_N_demand2[ccwc] > 0.0f)
		N_stress[ccwc] = (day_nup[ccwc] + day_plant_nh3[ccwc] + day_fixN[ccwc]) / (day_N_demand2[ccwc]);
	else
		N_stress[ccwc] = 1.0f;

	N_stress[ccwc] = min(1.0f, max(0.0f, N_stress[ccwc]));

#ifdef PHOSPHOROUS
	// P uptake by crop (unchanged)
	day_P_demand[ccwc] = (day_nup[ccwc] + day_plant_nh3[ccwc] + day_fixN[ccwc]) / 15.0f;
	for (i = 1; i <= q; i++)
	{
		if (LabP[i] > 0.0f && day_P_demand[ccwc] > 0.0f)
		{
			if (day_P_demand[ccwc] >= LabP[i])
			{
				day_P_uptake[ccwc] += LabP[i];
				day_P_demand[ccwc] -= LabP[i];
				LabP[i] = 0.0f;
			}
			else
			{
				day_P_uptake[ccwc] += day_P_demand[ccwc];
				day_P_demand[ccwc] = 0.0f;
			}
		}
	}
	plantP[ccwc] += day_P_uptake[ccwc];
	GrainP[ccwc] += 0.6f * day_P_uptake[ccwc];
	LeafP[ccwc] += 0.2f * day_P_uptake[ccwc];
	StemP[ccwc] += 0.1f * day_P_uptake[ccwc];
	RootP[ccwc] += 0.1f * day_P_uptake[ccwc];
#endif
}


/*
void class_model::n_uptake_by_crop(int ccwc)//for CropModel=0
{
	int i;
	float    layer_demand, layer_up_no3, layer_up_nh4, layer_up_nh3, UPP;
	float layer_up, day_Nuptake_from_clayN, day_SoilN_demand;

	day_Nuptake_from_clayN = 0.0;

	if (seed[ccwc] == 1) ddupn[ccwc] = 0.0;

	demandn[ccwc] += day_N_demand2[ccwc];



	//new code for leakage from other N fixing crops
	int crops;

	// Compute Nitrogen competition factor for this crop
	N_CompFactor(); //Theo

	if (max_N_fix[ccwc] == 0.0)
	{
		for (crops = 1; crops <= CropNumbers; crops++)
		{
			if (ini_N_fix[crops] > 0 && seed[crops] <= grow_days[crops] && seed[crops] > 0)//testing to see if there is a Nfixing crop available to provide fixed N during N demand. Should be at a reduced rate. note ini_N_fix[crops] is to represent highest N fix rate available of co-crops
			{

				if (ini_N_fix[ccwc] == 0)
				{
					//	max_N_fix[ccwc] = ini_N_fix[crops] * 0.25* maxmn[ccwc];//calculates the maximum N available to be provided by N fixation. (adopts the N fixation rate of other N fixing crops) Likely should be at a 4:1 ratio as estimated by Laidlaw et al., 1996
				}
				else
				{
					//	max_N_fix[ccwc] = ini_N_fix[crops] * maxmn[ccwc];//calculates the maximum N available to be provided by N fixation. (adopts the N fixation rate of other N fixing crops) Likely should be at a 4:1 ratio as estimated by Laidlaw et al., 1996
				}

			}
			else
			{

				//max_N_fix[ccwc]=0.0;
			}
		}

	}
	//end code for N fix leakage.

	if (max_N_fix[ccwc] > 0.0) //test to see if Nfix is on
	{
		float tempFixN, nStatusFixN;
		float sumNO3, sumNH4, averageTemp3;
		int tempCounter;
		tempCounter = 0;
		sumNO3 = 0.0;
		sumNH4 = 0.0;
		averageTemp3 = 0.0;

		int root_layer = round(root_length[ccwc] / h[1]);

		for (int xx = 1; xx < q; xx++) //calculate the N in rooting depth
		{
			if (SoilDepth[xx] <= root_depth[ccwc])//was 0.3 depth  //root_depth[ccwc]   max_root_length[ccwc]
			{
				sumNO3 += no3[xx];
				sumNH4 += nh4[xx];
				averageTemp3 += temp[xx];
				tempCounter += 1;
			}
		}

		if (tempCounter > 0)
		{
			averageTemp3 = averageTemp3 / tempCounter;  //apsim temperature adjustment on Nodulatation
		}
		else
		{
			averageTemp3 = air_temp;
		}
		tempFixN = averageTemp3 * averageTemp3 * (55 - averageTemp3) * powf(10, -4);
		tempFixN = (averageTemp3 * averageTemp3 * (40 - averageTemp3) * powf(10, -4)) / 0.9477;

		tempFixN = 1.0;
		tempFixN = min(1.0, max(0.0, tempFixN));




		//calculate a N2 Nodulation efficiency based on Zhang McGill study.
		float N2NodEF;

		N2NodEF = 1.0 / ((25.0 - averageTemp3) * 1.8182 + 17.0); //25.0 = optimal temperature to generate full nodulation by V2-V3 stage/averageTemp3=rooting depth soil temp /1.8182 is slope of FIg 1 from Zhan/ 17.0 = days after emergence to expect full nodulations
		N2NodEFACC[ccwc] += N2NodEF; //add the
		N2NodEFACC[ccwc] = min(1.0, max(0.0, N2NodEFACC[ccwc]));//accumulator set between 0 and 1.

		// Moisture stress on N fixation potential
		double wiltptw = h[1] * sts[1] * wiltpt[1];
		double fldcapw = h[1] * sts[1] * fldcap[1];

		double waterStressFactor, waterNodStress;

		//need to figure out water stress maybe using crop stress factor. day_CropWater???
		waterStressFactor = (water[1][1] - fldcapw) / (1.0 - fldcapw);

		waterNodStress = 1.6667 * waterStressFactor - 0.3333;  //adapted from APSIM - Modeling Flood-Induced Stress in Soybeans Feb 2020
		waterNodStress = 1.0 - (min(1.0, max(0.0, waterNodStress)));
		if (waterNodStress < 0.0) waterNodStress = 0.0;
		if (waterNodStress > 1.0) waterNodStress = 1.0;



		//tempFixN = N2NodEFACC[ccwc];
		//calculate concentration conversion to kg N/ha of 10 g N /m3 and 30 g N /m3
		float conc10, conc30, concDNDC;
		float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;	//calculate bulk density of soil layer
		conc10 = bulk_density * (3000) * 10 / 1000;//bulk density * 3000 m3 volume of soil in a ha in .3m * 10 g N/kg /1000 g to kg.//units kg/ha 10000*max_root_length[ccwc]
		conc30 = bulk_density * (3000) * 30 / 1000;//units kg/ha 10000*max_root_length[ccwc]
		concDNDC = (sumNO3 + sumNH4) * 1000 / (3000 * bulk_density) * root_depth[ccwc];//units in g N /m3 10000*max_root_length[ccwc]

		conc10 = 100;//80
		conc30 = 200;//was 30 for agmip soybean
		//concDNDC=(sumNO3+sumNH4);

		if ((sumNO3 + sumNH4) < conc10)//(sumNO3+sumNH4)<10)
		{
			nStatusFixN = 1.0;
		}
		else if ((sumNO3 + sumNH4) > conc30)//(sumNO3+sumNH4)>30)
		{
			nStatusFixN = (conc30 / (sumNO3 + sumNH4));
			nStatusFixN = max(0.5, nStatusFixN);
			//nStatusFixN=0.0;

		}//was 0.0
		else
		{
			nStatusFixN = 1 - ((sumNO3 + sumNH4) / conc30);
			//	nStatusFixN=1.0-0.05*(concDNDC);//(sumNO3+sumNH4) //0.025
		}

		nStatusFixN = min(1.0, max(nStatusFixN, 0.0));


		//nStatusFixN = 1.0;
		day_fixN[ccwc] = (day_N_demand2[ccwc] / maxmn[ccwc]) * max_N_fix[ccwc] * tempFixN * nStatusFixN;
		//nh4[5] += day_fixN[ccwc] * .25; messing around with exudates



		//old way before added the soy N fix to soil matrix
		day_SoilN_demand = day_N_demand2[ccwc] - day_fixN[ccwc];
		day_soilN_from_Nfixation[ccwc] = day_fixN[ccwc];


		//soybean N fix to soil matrix

		//end soybean N fix to soil matrix




	}
	else
	{
		day_fixN[ccwc] = 0.0;
		day_SoilN_demand = day_N_demand2[ccwc];
	}


	///////////////////////////////////////START SECTION -root exudate soil N in multiple crop scenarios when one is a N fixer

	float fixedrootExudateN = 0.0;//accumulator for fixedrootExudateN

	int needNOtherCropFlag = 0;// is another non-Nfixer growing

	//need to test if there is multiple crops growing and a non-N fixer needing N-demand and is currently growing

	///////////////////////////////////////END SECTION -root exudate soil N in multiple crop scenarios when one is a N fixer


	/////////////////////////////////////////////
	if (day_SoilN_demand > 0.0 && FertOption == 333)//precision fertilization
	{
		float DADF = day_SoilN_demand * 1.1;
		day_inFertN += DADF;
		yr_addfer += DADF;
		fert_flag = 1;
		for (int i = 1; i <= 2; i++) nh4[i] += (DADF / 2.0);

	}
	///////////////////////////////////////////////

	day_nup[ccwc] = 0.0;

	day_clay_N = 0.0;

	for (int vv = 1; vv <= q; vv++)
	{
		day_clay_N += clay_nh4[vv];
	}
	int root_layer = round(root_length[ccwc] / h[1]);
	if (root_q > q) root_q = q;
	int QqQ = root_q;//was q //is root layer it extends to. 
	QqQ = max(1, root_q);

	UPP = day_SoilN_demand;// / (float)QqQ;//* powf(0.5, i);
	float layer_Ndef = 0.0;//layer Demand N deficeit.
	float max_n_demand = day_N_demand2[ccwc];// day_N_demand2[ccwc];
	float cumulative_n_uptake = 0.0;
	for (i = 1; i <= QqQ; i++)
	{
		//UPP = day_SoilN_demand;// / (float)QqQ;//* powf(0.5, i);
		layer_up = 0.0;

		if (root_layer <= 1)
		{
			layer_demand = UPP;
		}
		else
		{
			layer_demand = UPP * rootDensity[ccwc][i] + layer_Ndef;
		}

		float ava_nh4, ava_nh3, ava_no3;
		float layer_demand1, layer_demand2, layer_demand3;



		//reduce N availability Roland CSW
		//NreductionFactor=1.0;
			//n uptake reduction
		float Red_f_NO3 = no3[i] * 0.1;//(no3[i]/5) - 0.05;//25		//reduction factor for no3
		Red_f_NO3 = min(1.0, max(0.0, Red_f_NO3));

		float Red_f_NH4 = nh4[i] * (nh4[i] * 0.1);//5		//reduction factor for nh4 and nh3
		Red_f_NH4 = min(1.0, max(0.0, Red_f_NH4));


		if ((no3[i] - 1.0) < 1)									//if NO3 in the layer is smaller than 5 kg
		{
			ava_no3 = no3[i] * NreductionFactor;//Red_f_NO3; was 0.1						//the available nitrate is the nitrate pool times reduction factor
			//the reduced nitrate amount is transferred to an intermediate variable
		}
		else { ava_no3 = no3[i]; }		//else available and intermediate variables are unreduced

		if ((nh4[i] - 1.0) < 1.0)									//if NH4 in the layer is smaller than 10 kg
		{
			ava_nh4 = nh4[i] * NreductionFactor;
			//ava_nh4 = nh4[i] * NreductionFactor;//Red_f_NH4; was 0.1						//the available ammonium is the nitrate pool times reduction factor
												//the reduced ammonium amount is transferred to an intermediate variable
		}
		else { ava_nh4 = nh4[i]; }		//else available and intermediate variables are unreduced

		if (nh3[i] < 0.1)									//if NH3 in the layer is smaller than 10 kg
		{
			ava_nh3 = nh3[i] * Red_f_NH4;						//the available ammonia is the nitrate pool times reduction factor
			//the reduced ammonia amount is transferred to an intermediate variable
		}
		else { ava_nh3 = nh3[i]; }

		//Reduce N availability Roladn CSW


	
		//float TotalAN = no3[i] + nh4[i] + nh3[i] + 0.0000001;

		float TotalAN = no3[i] + nh4[i] + nh3[i];
		if (TotalAN <= 0.0f) {
			// nothing available in this layer; continue or break
			float blah;
			blah = 1.0;
			continue;
		}


		layer_demand1 = layer_demand * no3[i] / TotalAN;

		layer_demand2 = layer_demand * nh4[i] / TotalAN;

		layer_demand3 = layer_demand * nh3[i] / TotalAN;

		layer_up_no3 = min(layer_demand1, ava_no3 * CF_N[ccwc]);
		layer_up_nh4 = min(layer_demand2, ava_nh4 * CF_N[ccwc]);
		layer_up_nh3 = min(layer_demand3, ava_nh3 * CF_N[ccwc]);

		if (layer_demand1 <= ava_no3)
		{
			layer_up_no3 = layer_demand1;//ava_no3;// layer_demand1;
		}
		else
		{
			layer_up_no3 = ava_no3;
		}

		if (layer_demand2 <= ava_nh4)
		{
			layer_up_nh4 = layer_demand2;// ava_nh4;// layer_demand2;
		}
		else
		{
			layer_up_nh4 = ava_nh4;
		}

		if (layer_demand3 <= ava_nh3)
		{
			layer_up_nh3 = layer_demand3;//ava_nh3;// layer_demand3;
		}
		else
		{
			layer_up_nh3 = ava_nh3;
		}



		float UPno3, UPnh4, UPnh3;
		if (no3[i] >= layer_up_no3)
		{
			UPno3 = layer_up_no3;
			if (cumulative_n_uptake + UPno3 > max_n_demand) UPno3 = max_n_demand - cumulative_n_uptake;
			no3[i] -= UPno3;
		}
		else
		{
			UPno3 = no3[i];
			if (cumulative_n_uptake + UPno3 > max_n_demand) UPno3 = max_n_demand - cumulative_n_uptake;
			no3[i] -= UPno3;
			//no3[i] = 0.0;
		}

		day_nup[ccwc] += UPno3;
		cumulative_n_uptake += UPno3;

		if (nh4[i] >= layer_up_nh4)
		{
			UPnh4 = layer_up_nh4;
			if (cumulative_n_uptake + UPnh4 > max_n_demand) UPnh4 = max_n_demand - cumulative_n_uptake;
			nh4[i] -= UPnh4;

		}
		else
		{
			UPnh4 = nh4[i];
			if (cumulative_n_uptake + UPnh4 > max_n_demand) UPnh4 = max_n_demand - cumulative_n_uptake;

			nh4[i] -= UPnh4;
			//nh4[i] = 0.0;
		}

		day_nup[ccwc] += UPnh4;
		cumulative_n_uptake += UPnh4;

		if (nh3[i] >= layer_up_nh3)
		{
			UPnh3 = layer_up_nh3;
			if (cumulative_n_uptake + UPnh3 > max_n_demand) UPnh3 = max_n_demand - cumulative_n_uptake;
			nh3[i] -= UPnh3;
		}
		else
		{
			UPnh3 = nh3[i];
			if (cumulative_n_uptake + UPnh3 > max_n_demand) UPnh3 = max_n_demand - cumulative_n_uptake;
			nh3[i] -= UPnh3;
			//nh3[i] = 0.0;
		}

		day_nup[ccwc] += UPnh3;
		cumulative_n_uptake += UPnh3;

		if (no3[i] < 0.0) no3[i] = 0.0;
		if (nh4[i] < 0.0) nh4[i] = 0.0;
		if (nh3[i] < 0.0) nh3[i] = 0.0;

		layer_up = UPno3 + UPnh4 + UPnh3;
		if (layer_demand > layer_up) {
			layer_Ndef = layer_demand - layer_up;
		}
		else
		{
			layer_Ndef = 0.0;
		}
		//UPP -= layer_up; //turn off for rootdensity uptake....
		if (UPP < 0.0) UPP = 0.0;


	} //end of layer loop for N uptake


	//--- new routine to take care of deficet N not uptook in a given layer.


	//float remaining_demand = day_N_demand2[ccwc] - (day_nup[ccwc] + day_plant_nh3[ccwc] + day_fixN[ccwc]);
	//remaining_demand = max(0.0f, remaining_demand);

	if (day_N_demand2[ccwc] > (day_nup[ccwc] + day_plant_nh3[ccwc] + day_fixN[ccwc]))
		//if(remaining_demand>0.0f)
	{



		//for (i = 1; i <= QqQ; i++)
		for (i = QqQ; i >= 1; i--)
		{

			float layer_demand1, layer_demand2, layer_demand3;
			//float TotalAN = no3[i] + nh4[i] + nh3[i] + 0.0000001;


			float TotalAN = no3[i] + nh4[i] + nh3[i];
			if (TotalAN <= 0.0f) {
				// nothing available in this layer; continue or break
				float blah;
				blah = 1.0;
				continue;
			}



			layer_demand1 = layer_demand * no3[i] / TotalAN;

			layer_demand2 = layer_demand * nh4[i] / TotalAN;

			layer_demand3 = layer_demand * nh3[i] / TotalAN;

			//might need N competition factor installed here

			if (layer_demand1 <= no3[i])
			{
				layer_up_no3 = layer_demand1;
			}
			else
			{
				layer_up_no3 = no3[i];
			}

			if (layer_demand2 <= nh4[i])
			{
				layer_up_nh4 = layer_demand2;
			}
			else
			{
				layer_up_nh4 = nh4[i];
			}

			if (layer_demand3 <= nh3[i])
			{
				layer_up_nh3 = layer_demand3;
			}
			else
			{
				layer_up_nh3 = nh3[i];
			}


			float UPno3, UPnh4, UPnh3;
			if (no3[i] >= layer_up_no3)
			{
				UPno3 = layer_up_no3;
				if (cumulative_n_uptake + UPno3 > max_n_demand) UPno3 = max_n_demand - cumulative_n_uptake;
				no3[i] -= UPno3;
			}
			else
			{
				UPno3 = no3[i];
				if (cumulative_n_uptake + UPno3 > max_n_demand) UPno3 = max_n_demand - cumulative_n_uptake;
				no3[i] -= UPno3;
				//no3[i] = 0.0;
			}

			day_nup[ccwc] += UPno3;
			cumulative_n_uptake += UPno3;

			if (nh4[i] >= layer_up_nh4)
			{
				UPnh4 = layer_up_nh4;
				if (cumulative_n_uptake + UPnh4 > max_n_demand) UPnh4 = max_n_demand - cumulative_n_uptake;
				nh4[i] -= UPnh4;

			}
			else
			{
				UPnh4 = nh4[i];
				if (cumulative_n_uptake + UPnh4 > max_n_demand) UPnh4 = max_n_demand - cumulative_n_uptake;

				nh4[i] -= UPnh4;
				//nh4[i] = 0.0;
			}

			day_nup[ccwc] += UPnh4;
			cumulative_n_uptake += UPnh4;

			if (nh3[i] >= layer_up_nh3)
			{
				UPnh3 = layer_up_nh3;
				if (cumulative_n_uptake + UPnh3 > max_n_demand) UPnh3 = max_n_demand - cumulative_n_uptake;
				nh3[i] -= UPnh3;
			}
			else
			{
				UPnh3 = nh3[i];
				if (cumulative_n_uptake + UPnh3 > max_n_demand) UPnh3 = max_n_demand - cumulative_n_uptake;
				nh3[i] -= UPnh3;
				//nh3[i] = 0.0;
			}

			day_nup[ccwc] += UPnh3;
			cumulative_n_uptake += UPnh3;

			if (no3[i] < 0.0) no3[i] = 0.0;
			if (nh4[i] < 0.0) nh4[i] = 0.0;
			if (nh3[i] < 0.0) nh3[i] = 0.0;

			layer_up = UPno3 + UPnh4 + UPnh3;
			layer_demand -= layer_up;
		}
		//end new routine
		if (isnan(nh4[1]))
		{
			float blah;
			blah = 1.0;
		}

	}

	//if(ddupn[ccwc]>0.00001&&WaterControl==2&&day_WT>-0.5&&FloodWater_N>0.0)//wetland plants
	if (UPP > 0.00001 && WaterControl == 2 && day_WT > -0.5 && FloodWater_N > 0.0)//wetland plants
	{
		float Wn = 0.0;

		if (FloodWater_N > 0.0)
		{
			//if(ddupn[ccwc]>=FloodWater_N)
			if (UPP >= FloodWater_N)
			{
				Wn = FloodWater_N;
				FloodWater_N = 0.0;
				UPP -= Wn;
			}
			else
			{
				Wn = UPP;//ddupn[ccwc];
				FloodWater_N -= Wn;
				UPP = 0.0;//ddupn[ccwc] = 0.0;
			}
		}

		day_nup[ccwc] += Wn;
	}

	day_nup[ccwc] += day_Nuptake_from_clayN;

	for (i = 1; i <= q; i++)
	{
		clay_nh4[i] = day_clay_N * pow(0.5, i);
	}

	if (seed[ccwc] == grow_days[ccwc] - 1) UPP = 0.0;//ddupn[ccwc] = 0.0;

	// N stress
	if (day_N_demand2[ccwc] > 0.0)
		N_stress[ccwc] = (day_nup[ccwc] + day_plant_nh3[ccwc] + day_fixN[ccwc]) / (day_N_demand2[ccwc]);//buffering
	else
		N_stress[ccwc] = 1.0;

	if (N_stress[ccwc] < 0.95)
	{
		float blah;
		blah = 1.0;

	}

	N_stress[ccwc] = min(1.0, max(0.0, N_stress[ccwc]));

#ifdef PHOSPHOROUS
	//P uptake by crop
	day_P_demand[ccwc] = (day_nup[ccwc] + day_plant_nh3[ccwc] + day_fixN[ccwc]) / 15.0;//Koerselman and Meuleman, 1996, J. of Applied Ecology 33:1441-1450.

	for (i = 1; i <= q; i++)
	{
		if (LabP[i] > 0.0 && day_P_demand[ccwc] > 0.0)
		{
			if (day_P_demand[ccwc] >= LabP[i])
			{
				day_P_uptake[ccwc] += LabP[i];
				day_P_demand[ccwc] -= LabP[i];
				LabP[i] = 0.0;
			}
			else
			{
				day_P_uptake[ccwc] += day_P_demand[ccwc];
				day_P_demand[ccwc] = 0.0;
			}
		}
	}
	plantP[ccwc] += day_P_uptake[ccwc];
	GrainP[ccwc] += 0.6 * day_P_uptake[ccwc];
	LeafP[ccwc] += 0.2 * day_P_uptake[ccwc];
	StemP[ccwc] += 0.1 * day_P_uptake[ccwc];
	RootP[ccwc] += 0.1 * day_P_uptake[ccwc];

#endif

}
*/
void class_model::total_crop_N(int ccwc)
{	

	if (crop[ccwc] == 3)
	{
		float blah;
		blah = 1.0;
	}
    Day_GrowthN[ccwc] = day_nup[ccwc] + day_fixN[ccwc] + day_plant_nh3[ccwc];//estimated off N growth curves and maxmn based on N availability. NEXT STEP biomass N partitions based on updated plantN
	plantn[ccwc] += Day_GrowthN[ccwc];//N existing in plants... sets plantn to be the growth N based on curves etc.

	PlantTakeN[ccwc] += Day_GrowthN[ccwc]; //N stored in plants in life cycle	 
	CropSumN[ccwc] += Day_GrowthN[ccwc];//crop life-time obtained N
	yr_plantn[ccwc] += Day_GrowthN[ccwc];//N taken by plants only in this calendar year
	yr_fixn[ccwc] += day_fixN[ccwc];//N fixed by plants in this calendar year
	//if(Day_GrowthN[ccwc]>0.0) CropEndN[ccwc] = plantn[ccwc];
}



void class_model::biomass_N_partition(int ccwc)// soybean and corn
{
	float f_shoot = 0.0;

	float CTF, GST, GGG;

	if (C_type[ccwc] == 4)
	{
		CTF = 0.5;//1.0;
		GST = 0.5;//0.4;
		GGG = 5.0;
	}
	else
	{
		CTF = 0.2;//0.4;
		GST = 0.5;
		GGG = 1.7;
	}

	GST = GrainFill[ccwc];

	if (PGI[ccwc] > 0.0)
	{
		if (crop[ccwc] == 7) GST = 0.2;
		else if (crop[ccwc] == 53) GST = 0.3;

		//f_root[ccwc] = CTF * (root[ccwc] + (0.6-root[ccwc])*(0.9-PGI[ccwc])/0.9);//0.4
		//if(f_root[ccwc]<root[ccwc]) f_root[ccwc] = root[ccwc];

		if (crop[ccwc] == 7) f_root[ccwc] = root[ccwc];//sugarcane

		if (LandUse == 6)//trees
		{

			{
				f_grain[ccwc] = grain[ccwc];
				f_leaf[ccwc] = leaf[ccwc];
				f_stem[ccwc] = stem[ccwc];
				f_root[ccwc] = root[ccwc];
			}
		}
		else
		{
			if (PGI[ccwc] < GST)
			{
				float TotalBio = leaf[ccwc] + stem[ccwc] + root[ccwc];
				f_grain[ccwc] = 0.0;
				f_root[ccwc] = root[ccwc] / TotalBio;
				f_leaf[ccwc] = leaf[ccwc] / TotalBio;
				f_stem[ccwc] = stem[ccwc] / TotalBio;

	

				///temperature routine part 1

			
//------------------testing if temperature stress changes the biomass fractions

					//Reset variables for Heat stress routine at Anthesis for Wheat
				if (PGI[ccwc] < 0.50 && crop[ccwc] != 18)
				{
					maxTempAvg = 0.0;
					countTemp = 0;
					countWater = 0;
					harvIdxFlag = 1;

				}
				else if (crop[ccwc] == 18 && PGI[ccwc] < 0.40)
				{
					maxTempAvg = 0.0;
					countTemp = 0;
					countWater = 0;
					harvIdxFlag = 1;


				}

				//For Anthesis in Spring Wheat come up with the Maximum Temperature average 
				if (PGI[ccwc] > 0.50 && PGI[ccwc] < 0.6 && crop[ccwc] == 57) //for canola heat stress sensitive period
				{


					maxTempAvg += max_temp;
					countTemp += 1;



				}
				if (PGI[ccwc] > 0.40 && PGI[ccwc] < 0.5 && crop[ccwc] == 18) //for canola heat stress sensitive period
				{


					maxTempAvg += max_temp;
					countTemp += 1;



				}
				if (PGI[ccwc] > 0.50 && PGI[ccwc] < 0.6 && crop[ccwc] == 3)
				{


					maxTempAvg += max_temp;
					countTemp += 1;



					//maxTempAvg=max_temp+maxTempAvg;//averagetemp maxTempAvg=max_temp+maxTempAvg;
					 //countTemp+=1;
				}

				if (PGI[ccwc] > 0.50 && PGI[ccwc] < 0.6 && crop[ccwc] == 6)//sensitive wheat growth period  to anthesis heat stress
				{
					maxTempAvg += max_temp;
					countTemp += 1;

				}
				if (PGI[ccwc] > 0.50 && PGI[ccwc] < 0.6 && crop[ccwc] == 8) //sensitive barley period to heat stress
				{

					if (maxTempAvg < max_temp)
					{
						maxTempAvg = max_temp;
					}

				}
				if (PGI[ccwc] > 0.50 && PGI[ccwc] < 0.6 && crop[ccwc] == 2) // senesitve winter wheat period
				{

					if (maxTempAvg < max_temp)
					{
						maxTempAvg = max_temp;
					}

				}
				if (PGI[ccwc] > 0.50 && PGI[ccwc] < 0.60 && crop[ccwc] == 1)//was .5 to .55 //budong was .60
				{

					if (maxTempAvg < max_temp)
					{
						maxTempAvg += max_temp;
						countTemp += 1;

					}


					cropWStress += day_DWater[ccwc];
					countWater += 1;



				}

				//routine for Harvest Index reducxtion for corn taken from Carberry et al 1989 Testing the CERRES-Maize Simulation Model
				float harvFact = 0.0;
				float newHi = 0.0;
				float changeHi = 0.0;

				//end temperature functions part 1
	//			

				


			}
			else
			{

	

			//---- need to turn this off if using brian - insert code
						//when PGI > GST
						//if (LeafN[ccwc] < (0.7 * MaxLeafN[ccwc]) && crop[ccwc]!=3 && LeafN[ccwc] < (0.7 * MaxLeafN[ccwc]) && crop[ccwc] != 29)
						
						//if (LeafN[ccwc] < (0.9 * MaxLeafN[ccwc]) )  //was 0.5  || LeafN[ccwc] < (0.5 * MaxLeafN[ccwc]) && crop[ccwc] != 29 //&& LeafN[ccwc] < (0.7 * MaxLeafN[ccwc]) && crop[ccwc] != 29
			if (LeafN[ccwc] < (0.7 * MaxLeafN[ccwc]) && crop[ccwc] != 3 && LeafN[ccwc] < (0.7 * MaxLeafN[ccwc]) && crop[ccwc] != 29)
				{
							float TotalBio = leaf[ccwc] + stem[ccwc] + root[ccwc]+grain[ccwc];
							
							f_root[ccwc] = root[ccwc] / (TotalBio);
								f_leaf[ccwc] = leaf[ccwc] / (TotalBio);
								f_stem[ccwc] = stem[ccwc] / (TotalBio);
								f_grain[ccwc] = grain[ccwc] / (TotalBio);
							
								//f_grain[ccwc] = 1.0;
								//f_leaf[ccwc] = 0.0;
								//f_stem[ccwc] = 0.0;
								//f_root[ccwc] = 0.0;

						}
						else //critical Leaf N was achieved.
						{
							f_grain[ccwc] = 1.0;
							f_leaf[ccwc] = 0.0;
							f_stem[ccwc] = 0.0;
							f_root[ccwc] = 0.0;
						}
						
						
						/*
						if (PGI[ccwc] < 0.8)
						{
							float TotalBio = leaf[ccwc] + stem[ccwc] + root[ccwc] + grain[ccwc];

							f_root[ccwc] = root[ccwc] / (TotalBio);
							f_leaf[ccwc] = leaf[ccwc] / (TotalBio);
							f_stem[ccwc] = stem[ccwc] / (TotalBio);
							f_grain[ccwc] = grain[ccwc] / (TotalBio);


						}
						else
						{
							f_grain[ccwc] = 1.0;
							f_leaf[ccwc] = 0.0;
							f_stem[ccwc] = 0.0;
							f_root[ccwc] = 0.0;

						}
						*/
						//end turn this off
						

// 

				//temperature functions part 2

				//Routine for reduced Harvest Index due to Heat stress from Anthesis based on work of Ferris and Wheeler 1998

				float harvSlope = -0.0243;//default is -0.0143
				float harvFact = 0.0;
				float newHi = 0.0;
				float cropTempAdd = 0.0;
				float changeHi = 0.0;




				if (crop[ccwc] == 6 || crop[ccwc] == 8)
				{
					cropTempAdd = 6.0;
				}//default 8.0
				if (crop[ccwc] == 57)
				{
					cropTempAdd = 2.0;
				}
				if (crop[ccwc] == 2)
				{
					cropTempAdd = 18.0;
				}
				if (crop[ccwc] == 1)
				{
					cropTempAdd = 8.0;
				}
				if (crop[ccwc] == 3)
				{
					cropTempAdd = 5.0;
				}

				if (crop[ccwc] == 57 && harvIdxFlag == 1 && PGI[ccwc] >= 0.6)
				{

					if (countTemp > 0)
					{
						maxTempAvg = maxTempAvg / countTemp;
						countTemp = 0;
					}
					if (maxTempAvg > (OptimumT[ccwc])) //Y.Gan 2004 Canola and Mustard response to short periods of temperature and water stress
					{
						changeHi = grain[ccwc] - ((-0.0018 * maxTempAvg * maxTempAvg + 0.0674 * maxTempAvg + 0.392) * grain[ccwc]);
						//changeHi=((1-(-15.097*maxTempAvg+407.77)/100)*grain[ccwc]);
						if ((grain[ccwc] - changeHi) > 0.05)
						{
							grain[ccwc] -= changeHi;
							stem[ccwc] += changeHi / 2;
							leaf[ccwc] += changeHi / 2;
						}
						else
						{
							stem[ccwc] += (grain[ccwc] - 0.05) / 2;
							leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
							grain[ccwc] = 0.05;
						}
						harvIdxFlag = 0;
					}
				}
				if (crop[ccwc] == 18 && harvIdxFlag == 1 && PGI[ccwc] >= 0.5)
				{

					if (countTemp > 0)
					{
						maxTempAvg = maxTempAvg / countTemp;

					}
					if (maxTempAvg > (OptimumT[ccwc] + 4.0)) //Potato heat stress at tuber initiatiion. 
					{
						changeHi = (grain[ccwc] - ((-0.00177 * maxTempAvg * maxTempAvg + 0.0674 * maxTempAvg + 0.392) * grain[ccwc])) * countTemp;
						changeHi = changeHi / 2.0;
						if (changeHi < 0.0)changeHi = 0.0;
						if (changeHi > 1.0)changeHi = 0.0;
						if (changeHi > grain[ccwc])changeHi = grain[ccwc] - 0.06;

						//changeHi=((1-(-15.097*maxTempAvg+407.77)/100)*grain[ccwc]);
						if ((grain[ccwc] - changeHi) > 0.05)
						{
							grain[ccwc] -= changeHi;
							stem[ccwc] += changeHi / 2;
							leaf[ccwc] += changeHi / 2;
						}
						else
						{
							stem[ccwc] += (grain[ccwc] - 0.05) / 2;
							leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
							grain[ccwc] = 0.05;
						}
						harvIdxFlag = 0;
					}
					countTemp = 0;
				}
				if (crop[ccwc] == 3 && harvIdxFlag == 1 && PGI[ccwc] >= 0.6)
				{

					if (countTemp > 0)
					{
						maxTempAvg = maxTempAvg / countTemp;
						countTemp = 0;
					}
					if (maxTempAvg > ((OptimumT[ccwc]) + 4.0)) //Soybean paper - Agmip High temp Response
					{
						changeHi = grain[ccwc] - ((-0.0205 * maxTempAvg + 1.2629) * grain[ccwc]);
						changeHi = min(1.0, max(changeHi, 0.0));
						//changeHi=((1-(-15.097*maxTempAvg+407.77)/100)*grain[ccwc]);
						if ((grain[ccwc] - changeHi) > 0.05)
						{
							grain[ccwc] -= changeHi;
							stem[ccwc] += changeHi / 2;
							leaf[ccwc] += changeHi / 2;
						}
						else
						{
							stem[ccwc] += (grain[ccwc] - 0.05) / 2;
							leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
							grain[ccwc] = 0.05;
						}
						harvIdxFlag = 0;
					}
				}


				if (harvIdxFlag == 1 && crop[ccwc] == 6 && PGI[ccwc] >= 0.6 || crop[ccwc] == 2 && harvIdxFlag == 1 && PGI[ccwc] >= 0.6 || crop[ccwc] == 18 && harvIdxFlag == 1 && PGI[ccwc] >= 0.6)
				{
					if (countTemp > 0)
					{
						maxTempAvg = maxTempAvg / countTemp;
						countTemp = 0;
					}
					//maxTempAvg=maxTempAvg/countTemp; //for average calc
					if (maxTempAvg > (OptimumT[ccwc] + cropTempAdd))
					{
						harvFact = (OptimumT[ccwc] + cropTempAdd - maxTempAvg) * harvSlope;
						newHi = ((0.44 - harvFact) * grain[ccwc] / 0.44);
						changeHi = (grain[ccwc] - newHi);


						if ((grain[ccwc] - changeHi) > 0.05)
						{
							grain[ccwc] -= changeHi;
							stem[ccwc] += changeHi / 2;
							leaf[ccwc] += changeHi / 2;
						}
						else
						{
							stem[ccwc] += (grain[ccwc] - 0.05) / 2;
							leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
							grain[ccwc] = 0.05;
						}

						//grain[ccwc]-=changeHi;
						//straw[ccwc]+=changeHi;
						harvIdxFlag = 0;
					}

				}





				if (harvIdxFlag == 1 && crop[ccwc] == 1 && PGI[ccwc] >= 0.6 || harvIdxFlag == 1 && crop[ccwc] == 43 && PGI[ccwc] >= 0.6)
				{
					if (countTemp > 0)
					{
						maxTempAvg = maxTempAvg / countTemp; //for average calc
					}

					if (maxTempAvg > 38.0)//cropTempAdd //default +3.0
					{

						//	harvFact=max((maxTempAvg-34),1.0);
						//	newHi= grain[ccwc]*(1-log10(harvFact));

						harvFact = 1 - (maxTempAvg - 38.0) * 0.019; //Carberry 1989 - Testing the ceres maize simulation model in a semi-arid tropical environment.
						newHi = (harvFact * grain[ccwc]);
						changeHi = (grain[ccwc] - newHi);

						if (newHi > 0.05) //ensure that grain fraction remains above 0.05
						{
							grain[ccwc] -= changeHi;
							stem[ccwc] += changeHi / 2;
							leaf[ccwc] += changeHi / 2;
						}
						else
						{
							stem[ccwc] += (grain[ccwc] - 0.05) / 2;
							leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
							grain[ccwc] = 0.05;
						}
						harvIdxFlag = 0;
					}


				}

//

				//end temperature functions part 2


	//-----this is also from brian insert to get grain going
				
			//	float finalGrainStage;
			//	if (crop[ccwc] == 57)
			//	{
			//		finalGrainStage = .89;
			//	}
			//	else
			//	{
			//		finalGrainStage = 1.0;
			//	}

				
			//	f_grain[ccwc] = 1.00 * (PGI[ccwc] - GST) / (finalGrainStage - GST) * grain[ccwc];//1.7 * is default - adjusts the rate at which grain accumulation occurs.

			//	if (f_grain[ccwc] > grain[ccwc]) f_grain[ccwc] = grain[ccwc];
				

	//end insert

			}
		}
	}
	else
	{
		f_root[ccwc] = 0.0;
		f_grain[ccwc] = 0.0;
		f_leaf[ccwc] = 0.0;
		f_stem[ccwc] = 0.0;
	}

	//N partitioning to crop components



	
	
	//---copied from Brian code................................................................................
	///---end brian insert





//was simplifying the allocation of growth




//---testing turning this off 


//is this whwere we should be rethinking where the growth is going. 


//working agustin

	DayGrow_LeafN[ccwc] = Day_GrowthN[ccwc] * f_leaf[ccwc];
	DayGrow_StemN[ccwc] = Day_GrowthN[ccwc] * f_stem[ccwc];
	DayGrow_RootN[ccwc] = Day_GrowthN[ccwc] * f_root[ccwc];
	DayGrow_GrainN[ccwc] = Day_GrowthN[ccwc] * f_grain[ccwc];

	LeafN[ccwc] += DayGrow_LeafN[ccwc];
	StemN[ccwc] += DayGrow_StemN[ccwc];
	RootN[ccwc] += DayGrow_RootN[ccwc];
	GrainN[ccwc] += DayGrow_GrainN[ccwc];
	




	//----testing something
	//Need to slowly check if fractions need to shift back to targets.
//	float totalBiomassC=0.0,currentLeafF=0.0, currentStemF=0.0, currentRootF=0.0, currentGrainF=0.0;
//	totalBiomassC = Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Root_Wt[ccwc] + Grain_Wt[ccwc];
//	currentLeafF = Leaf_Wt[ccwc] / totalBiomassC;
//	currentStemF = Stem_Wt[ccwc] / totalBiomassC;
//	currentRootF = Root_Wt[ccwc] / totalBiomassC;
//	currentGrainF = Grain_Wt[ccwc] / totalBiomassC;


//	if (currentLeafF > f_leaf[ccwc]);
//	{
	

//	}
	//---end testing
	
	


	





	if (LeafN[ccwc] > MaxLeafN[ccwc])
	{
		ReserveN[ccwc] += (LeafN[ccwc] - MaxLeafN[ccwc]);
		LeafN[ccwc] = MaxLeafN[ccwc];
	}

	if (StemN[ccwc] > MaxStemN[ccwc])
	{
		ReserveN[ccwc] += (StemN[ccwc] - MaxStemN[ccwc]);
		StemN[ccwc] = MaxStemN[ccwc];
	}

	if (RootN[ccwc] > MaxRootN[ccwc])
	{
		ReserveN[ccwc] += (RootN[ccwc] - MaxRootN[ccwc]);
		RootN[ccwc] = MaxRootN[ccwc];
	}

	if (f_grain[ccwc] > 0.0 && ReserveN[ccwc] > 0.0)
	{
		float RelocateN = ReserveN[ccwc] * 0.2;
		ReserveN[ccwc] -= RelocateN;
		GrainN[ccwc] += RelocateN;
	}

	if (GrainN[ccwc] > MaxGrainN[ccwc])
	{
		ReserveN[ccwc] += (GrainN[ccwc] - MaxGrainN[ccwc]);
		GrainN[ccwc] = MaxGrainN[ccwc];

		if (ReserveN[ccwc] > 0.0)
		{
			if (LeafN[ccwc] < MaxLeafN[ccwc])
			{
				float ddl = MaxLeafN[ccwc] - LeafN[ccwc];
				if (ddl >= ReserveN[ccwc])
				{
					LeafN[ccwc] += ReserveN[ccwc];
					ReserveN[ccwc] = 0.0;
				}
				else
				{
					LeafN[ccwc] += ddl;
					ReserveN[ccwc] -= ddl;

					if (StemN[ccwc] < MaxStemN[ccwc])
					{
						float ddl = MaxStemN[ccwc] - StemN[ccwc];
						if (ddl >= ReserveN[ccwc])
						{
							StemN[ccwc] += ReserveN[ccwc];
							ReserveN[ccwc] = 0.0;
						}
						else
						{
							StemN[ccwc] += ddl;
							ReserveN[ccwc] -= ddl;

							if (ReserveN[ccwc] > 0.0)
							{
								nh4[1] += ReserveN[ccwc];
								ReserveN[ccwc] = 0.0;
							}
						}
					}
				}

			}
		}
	}
	



	//Daily crop C increase
	if (LandUse == 6)//trees
	{
		Day_C_growth[ccwc] = plantcn[ccwc] * Day_GrowthN[ccwc];
		dayG_grain[ccwc] = Day_C_growth[ccwc] * f_grain[ccwc];
		dayG_root[ccwc] = Day_C_growth[ccwc] * f_root[ccwc];
		dayG_leaf[ccwc] = Day_C_growth[ccwc] * f_leaf[ccwc];
		dayG_stem[ccwc] = Day_C_growth[ccwc] * f_stem[ccwc];

		YrG_grain[ccwc] += dayG_grain[ccwc];
		YrG_leaf[ccwc] += dayG_leaf[ccwc];
		YrG_stem[ccwc] += dayG_stem[ccwc];
		YrG_root[ccwc] += dayG_root[ccwc];

		Root_Wt[ccwc] += dayG_root[ccwc];
		Grain_Wt[ccwc] += dayG_grain[ccwc];
		Leaf_Wt[ccwc] += dayG_leaf[ccwc];
		Stem_Wt[ccwc] += dayG_stem[ccwc];

	}
	else//normal annual crops --- but only crops 3 and 90 and perrenial. 
	{

		//Daily biomass growth	
		float cnBuffer;
		cnBuffer = 1.0;
		if (crop[ccwc] == 10 || crop[ccwc] == 89 || crop[ccwc] == 1 || crop[ccwc] == 43 || crop[ccwc] == 6 || crop[ccwc] == 57 || crop[ccwc] == 90)//|| crop[ccwc]==89 ||crop[ccwc]==1
		{
			if (N_stress[ccwc] < 1.0)//turned off was 1.0
			{
				float maxBuffer;
				maxBuffer = min(1.0, (max(0.70, N_stress[ccwc])));



				cnBuffer = maxBuffer;
				//1.0+(1.0-maxBuffer);
			}
		}
		cnBuffer = 1.0;//for soybean and corn90
		
		if (year == 13 && PGI[2] > 0.5)
		{
			float blah;
			blah = 1.0;
		}
		

		//Daily biomass growth		--dayC_growth be based on overall plantcn and N increase rather than specific parts? --when grain N takes over at PGI 0.5 because the C:N ratio is lower the biomass C accumulation drops and the GPP is low even though the 
		dayG_grain[ccwc] = DayGrow_GrainN[ccwc] * graincn[ccwc]/cnBuffer;
		dayG_root[ccwc] = DayGrow_RootN[ccwc] * rootcn[ccwc] / cnBuffer;
		dayG_leaf[ccwc] = DayGrow_LeafN[ccwc] * leafcn[ccwc] / cnBuffer;
		dayG_stem[ccwc] = DayGrow_StemN[ccwc] * stemcn[ccwc] / cnBuffer;
		//dayG_pod[ccwc] = DayGrow_PodN[ccwc] * [ccwc] / cnBuffer;
		Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc];


		//was using this without cn buffer
		//Grain_Wt[ccwc] = GrainN[ccwc] * graincn[ccwc];
		//Leaf_Wt[ccwc] = LeafN[ccwc] * leafcn[ccwc];
		//Stem_Wt[ccwc] = StemN[ccwc] * stemcn[ccwc];
		//Root_Wt[ccwc] = RootN[ccwc] * rootcn[ccwc];
		float tempHI;//calcalate what the new Harvest Index would be with the newly added Day_C_growth allocated to grain fraction
		float actHI;//calculate the user specified max harvest index using crop fractions
		float abGround;//sum of the above ground components leaf stem and grain
		float dayGrainMax;// max daily Grain C accumulation that wouldn't exceed the actHI the user specifies

		actHI = grain[ccwc] / (grain[ccwc] + stem[ccwc] + leaf[ccwc]);
		tempHI = (Grain_Wt[ccwc] + dayG_grain[ccwc]) / ((Leaf_Wt[ccwc] + dayG_leaf[ccwc]) + (Stem_Wt[ccwc] + dayG_stem[ccwc]) + (Grain_Wt[ccwc] + dayG_grain[ccwc]));
		abGround = ((Leaf_Wt[ccwc] + dayG_leaf[ccwc]) + (Stem_Wt[ccwc] + dayG_stem[ccwc]) + (Grain_Wt[ccwc] + dayG_grain[ccwc]));
		if (tempHI > actHI)//test that the new HI doesn't exceed the user parameterized HI
		{
			dayGrainMax = actHI * abGround- Grain_Wt[ccwc];//figure out the maximum daily added C that can be added without exceeding user specified HI
			dayG_grain[ccwc] = dayGrainMax;//set dayG_grain to that maximum daily C that can be added
			Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc];//set day_C_growth;

		}
		
			
		Grain_Wt[ccwc] += dayG_grain[ccwc];
		Leaf_Wt[ccwc] += dayG_leaf[ccwc];
		Stem_Wt[ccwc] += dayG_stem[ccwc];
		Root_Wt[ccwc] += dayG_root[ccwc];
		//Pod_Wt[ccwc] += dayG_pod[ccwc];

		//PresentBiomass[ccwc] = Grain_Wt[ccwc] + Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Root_Wt[ccwc];  //kg C/ha	

		YrG_grain[ccwc] += dayG_grain[ccwc];
		YrG_leaf[ccwc] += dayG_leaf[ccwc];
		YrG_stem[ccwc] += dayG_stem[ccwc];
		YrG_root[ccwc] += dayG_root[ccwc];

	}

	if (Root_Wt[ccwc] > 0.0)
	{
		root_length[ccwc] = max_root_length[ccwc] * PGI[ccwc] * 2.0;
		if (root_length[ccwc] > max_root_length[ccwc]) root_length[ccwc] = max_root_length[ccwc];
	}
	else
		root_length[ccwc] = 0.0;



	

	float Ftt = min(30.0, max(0.0, air_temp));

	float f_PGI = PGI[ccwc];

	if (PGI[ccwc] > 0.4) f_PGI = 0.4;
}





  //-------------------------------------------------------------------------------------------------------------------------------------------------- Brian Biomass ----------------------------------------------------------------------------------------------
//New biomass---brian
void class_model::biomass_N_partition_per(int ccwc)//all crops but soybean and corn
{
   float f_shoot=0.0;

   float CTF, GST, GGG;				

	if(C_type[ccwc]==4) //C4 type crops
	{
		CTF = 0.5;//1.0;
		GST = 0.5;//0.4;//grain filling stage

	}
	else //C3 type crops
	{
		CTF = 0.2;//0.4;
		GST = 0.5;//grain filling stage
	
	}



if(PerennialFlag[ccwc]==0)//||PerennialFlag[ccwc]==1,&&crop[ccwc]!=3
{
float dynRootFrac,dynGrainFrac,dynStrawFrac,dynStemFrac,dynLeafFrac,dynRootCN,dynStemCN,dynLeafCN,PGIcrop;//Code for dynamic fractions of crop
PGIcrop = PGI[ccwc];
if(PGI[ccwc]<0.01)
{
	PGIcrop = 0.01;
}

dynRootFrac=((((110.4 * pow(PGI[ccwc],3)) - (145.44 * pow(PGI[ccwc],2)) - (40.614 * PGI[ccwc]) + 90.869) / 100) + ((root[ccwc] - 0.15) * PGI[ccwc]));//root fraction changes over time

GST=GrainFill[ccwc];

float repphaseindex = PGI[ccwc] - GST;						//the reproduction phase index equals the plant growth index grain minus 0.4
if (PGI[ccwc] < GST) repphaseindex = 0;
dynGrainFrac=(((35.3621172653138 * pow(repphaseindex,5)) - (39.2676242682337 * pow (repphaseindex, 4)) + (7.55435245133936 * pow(repphaseindex, 3)) + (2.46187847239896 * pow(repphaseindex,2)) + (0.470285559593467 * repphaseindex)) + ((grain[ccwc] - 0.4465)*repphaseindex*2));
dynGrainFrac=(-1.8636*pow(repphaseindex,2)+1.9171*repphaseindex-0.0398)*grain[ccwc]/.45;
if(dynGrainFrac<0)
{
	dynGrainFrac=0.0;
}
dynStrawFrac=(1-(dynRootFrac+dynGrainFrac));

if (PGI[ccwc] < 0.5)//during leaf phase
{
	dynLeafFrac = (1 - PGI[ccwc]) * dynStrawFrac;
}
else//when in reproductive phase
{
	dynLeafFrac = max((1 - PGI[ccwc]) * dynStrawFrac,dynStrawFrac*leaf[ccwc]/(leaf[ccwc]+stem[ccwc]));
	dynLeafFrac = (1 - PGI[ccwc]) * dynStrawFrac;
}
dynStemFrac=1-dynRootFrac-dynGrainFrac-dynLeafFrac;

if (floweringDay[1] == 0 && PGI[ccwc] >= (GST-0.1))
{
	floweringDay[1] = jday;
}

if (floweringDay[2] == 0 && PGI[ccwc] >= (GST))
{
	floweringDay[2] = jday; //temporarily labelling seed fill date
}




dynRootCN=(71.0141978359679 * pow(PGI[ccwc],3) - 13.8128991003396 * pow(PGI[ccwc],2) + 14.2553720136202 * PGI[ccwc] + 6.69085249154296) + ((rootcn[ccwc] - 78.14)*(PGI[ccwc]*pow(PGI[ccwc],2)));
dynStemCN=(71.0141978359679 * pow(PGI[ccwc],3) - 13.8128991003396 * pow(PGI[ccwc],2) + 14.2553720136202 * PGI[ccwc] + 6.69085249154296) + ((stemcn[ccwc] - 78.14)*(PGI[ccwc]*pow(PGI[ccwc],2)));
dynLeafCN=(71.0141978359679 * pow(PGI[ccwc],3) - 13.8128991003396 * pow(PGI[ccwc],2) + 14.2553720136202 * PGI[ccwc] + 6.69085249154296) + ((leafcn[ccwc] - 78.14)*(PGI[ccwc]*pow(PGI[ccwc],2)));













}














   if (PGI[ccwc] > 0.0)
   {
		if(crop[ccwc]==7) GST = 0.2;
		else if(crop[ccwc]==53) GST = 0.3;


		if(crop[ccwc]==7) f_root[ccwc] = root[ccwc];//sugarcane

		if(LandUse==6)//trees
		{
			if(PGI[ccwc] < GST) 
			{
				float TBN = 1.0/leafcn[ccwc] + 1.0/stemcn[ccwc] + 1.0/rootcn[ccwc];
				f_grain[ccwc] = 0.0;
				f_leaf[ccwc] = (1.0/leafcn[ccwc]) / TBN;
				f_stem[ccwc] = (1.0/stemcn[ccwc]) / TBN;
				f_root[ccwc] = (1.0/rootcn[ccwc]) / TBN;
			}
			else 
			{
				f_grain[ccwc] = grain[ccwc];				
				f_leaf[ccwc] = leaf[ccwc];
				f_stem[ccwc] = stem[ccwc];
				f_root[ccwc] = root[ccwc];
			}
		}
		else
		{
			
			if (crop[ccwc] == 2  && PGI[ccwc]>0.05 && PGI[ccwc]<0.35)
			{
				//cropRadAcc[ccwc] += cropRad[ccwc];

			}



//------------------testing if temperature stress changes the biomass fractions
				
					//Reset variables for Heat stress routine at Anthesis for Wheat
				if(PGI[ccwc]<0.50&&crop[ccwc]!=18)
				{
				   maxTempAvg=0.0;
					countTemp=0;
					countWater=0;
					harvIdxFlag=1;

				}
				else if(crop[ccwc]==18 && PGI[ccwc]<0.40)
				{
					maxTempAvg = 0.0;
					countTemp = 0;
					countWater = 0;
					harvIdxFlag = 1;


				}

				//For Anthesis in Spring Wheat come up with the Maximum Temperature average 
				if(PGI[ccwc] >0.50 && PGI[ccwc]<0.6&&crop[ccwc]==57) //for canola heat stress sensitive period
					{				
					 
					
						maxTempAvg+=max_temp;
						countTemp+=1;
						
					

					}
				if (PGI[ccwc] > 0.40 && PGI[ccwc] < 0.5 && crop[ccwc] == 18) //for canola heat stress sensitive period
				{


					maxTempAvg += max_temp;
					countTemp += 1;



				}
				if(PGI[ccwc] >0.50 && PGI[ccwc]<0.6&&crop[ccwc]==3)
					{				
					 
					
						maxTempAvg+=max_temp;
						countTemp+=1;
						
					

					//maxTempAvg=max_temp+maxTempAvg;//averagetemp maxTempAvg=max_temp+maxTempAvg;
					 //countTemp+=1;
					}
				
				if(PGI[ccwc] >0.50 && PGI[ccwc]<0.6&&crop[ccwc]==6)//sensitive wheat growth period  to anthesis heat stress
					{				
					 maxTempAvg+=max_temp;
					 countTemp+=1;
					 
					}
						if(PGI[ccwc] >0.50 && PGI[ccwc]<0.6&&crop[ccwc]==8) //sensitive barley period to heat stress
					{				
					 
					if(maxTempAvg<max_temp)
					{maxTempAvg=max_temp;}

					}
						if(PGI[ccwc] >0.50 && PGI[ccwc]<0.6&&crop[ccwc]==2) // senesitve winter wheat period
					{				
					 
					if(maxTempAvg<max_temp)
					{
						maxTempAvg=max_temp;}

					}
							if(PGI[ccwc] >0.50 && PGI[ccwc]<0.60&&crop[ccwc]==1)//was .5 to .55 //budong was .60
							{				
					 
								if(maxTempAvg<max_temp)
								{
								maxTempAvg+=max_temp;
								countTemp+=1;
					
								}

					
						cropWStress+=day_DWater[ccwc];
						countWater+=1;
						
					

					}
				
					//routine for Harvest Index reducxtion for corn taken from Carberry et al 1989 Testing the CERRES-Maize Simulation Model
					float harvFact = 0.0;
					float newHi = 0.0;
					float changeHi=0.0;




			if(PGI[ccwc] < GST) 
			{
				
			}
			else
			{

				if (crop[ccwc] == 2 && cropRadAcc[ccwc]>10.0 && cropRadAcc[ccwc]!= 0.0)//if crop == 2 winter wheat and cropRadAcc resulted in 10 cummulative delayed phenology days and is not equal to zero
				{
					/*
					float hiReductionF = 10.0;//will make this eventually a user calibrated parameter 
					float changeHi = min(1.0, (hiReductionF/cropRadAcc[ccwc]));//winter wheat system 5 = 10.0  , winter wheat system 4 = 25
					float oldGrain = grain[ccwc];//old Grain Factor
					grain[ccwc] *= changeHi;//grain Fraction
					stem[ccwc] += (oldGrain - grain[ccwc]) / 2.0;//new stem fraction
					leaf[ccwc] += (oldGrain - grain[ccwc]) / 2.0;//new leaf fraction
					
					cropRadAcc[ccwc] = 0.0;//reset to zero to not call this routine again during this growth phase
					*/

					// User provides a normalized fraction between 0 and 1
					float hiReductionF_norm = rueHI[ccwc]; //was 1.0;    // 0 = max reduction, 1 = no reduction ..user input of 0.4 would produce the previous hiReductionF max of 10 and 1 would produce 

					// Define your current maximum reduction value (formerly 10.0)
					float hiReductionF_max = 50.0;

					// Scale normalized input to actual model magnitude
					float hiReductionF = hiReductionF_norm * hiReductionF_max;

					// Compute reduction scaled by accumulated radiation delay
					float changeHi = min(1.0f, hiReductionF / cropRadAcc[ccwc]);

					float oldGrain = grain[ccwc];

					// Apply new grain fraction after reduction
					grain[ccwc] *= changeHi;

					// Redistribute lost grain equally to stem and leaf
					float diff = oldGrain - grain[ccwc];
					stem[ccwc] += diff * 0.5f;
					leaf[ccwc] += diff * 0.5f;

					// Reset cumulative delay metric
					cropRadAcc[ccwc] = 0.0f;


				}

//Routine for reduced Harvest Index due to Heat stress from Anthesis based on work of Ferris and Wheeler 1998

			float harvSlope = -0.0243;//default is -0.0143
			float harvFact = 0.0;
			float newHi = 0.0;
			float cropTempAdd =0.0;
			float changeHi=0.0;


			
			
			if (crop[ccwc]==6||crop[ccwc]==8)
			{cropTempAdd = 6.0;}//default 8.0
			if (crop[ccwc]==57)
			{cropTempAdd = 2.0;}
			if (crop[ccwc]==2)
			{cropTempAdd = 15.0;
			harvSlope = -0.1443;
			}
			if (crop[ccwc]==1)
			{cropTempAdd = 8.0;}
				if (crop[ccwc]==3)
			{cropTempAdd = 5.0;}
			
			if(crop[ccwc]==57&&harvIdxFlag==1&&PGI[ccwc]>=0.6)
			{

				if(countTemp>0)
				{
				maxTempAvg=maxTempAvg/countTemp;
				countTemp=0;
				}
			if(maxTempAvg>(OptimumT[ccwc])) //Y.Gan 2004 Canola and Mustard response to short periods of temperature and water stress
				{
				changeHi=grain[ccwc]-((-0.0018*maxTempAvg*maxTempAvg+0.0674*maxTempAvg+0.392)*grain[ccwc]);
				//changeHi=((1-(-15.097*maxTempAvg+407.77)/100)*grain[ccwc]);
				if((grain[ccwc]-changeHi)>0.05)
					{
					grain[ccwc]-=changeHi;
					stem[ccwc]+=changeHi/2;
					leaf[ccwc]+=changeHi/2;
					}
				else
					{
					 stem[ccwc]+= (grain[ccwc]-0.05)/2;
					 leaf[ccwc]+= (grain[ccwc]-0.05)/2;
					 grain[ccwc]=0.05;
					}
					harvIdxFlag=0;
				}
			}
			if (crop[ccwc] == 18 && harvIdxFlag == 1 && PGI[ccwc] >= 0.5)
			{

				if (countTemp > 0 )
				{
					maxTempAvg = maxTempAvg / countTemp;
					
				}
				if (maxTempAvg > (OptimumT[ccwc]+4.0) ) //Potato heat stress at tuber initiatiion. 
				{
					changeHi = (grain[ccwc] - ((-0.00177 * maxTempAvg * maxTempAvg + 0.0674 * maxTempAvg + 0.392) * grain[ccwc]))*countTemp;
					changeHi = changeHi / 2.0;
					if (changeHi < 0.0)changeHi = 0.0;
					if (changeHi > 1.0)changeHi = 0.0;
					if (changeHi > grain[ccwc])changeHi = grain[ccwc] - 0.06;

					//changeHi=((1-(-15.097*maxTempAvg+407.77)/100)*grain[ccwc]);
					if ((grain[ccwc] - changeHi) > 0.05)
					{
						grain[ccwc] -= changeHi;
						stem[ccwc] += changeHi / 2;
						leaf[ccwc] += changeHi / 2;
					}
					else
					{
						stem[ccwc] += (grain[ccwc] - 0.05) / 2;
						leaf[ccwc] += (grain[ccwc] - 0.05) / 2;
						grain[ccwc] = 0.05;
					}
					harvIdxFlag = 0;
				}
				countTemp = 0;
			}
		if(crop[ccwc]==3&&harvIdxFlag==1&&PGI[ccwc]>=0.6)
			{

				if(countTemp>0)
				{
				maxTempAvg=maxTempAvg/countTemp;
				countTemp=0;
				}
				if(maxTempAvg>((OptimumT[ccwc])+4.0)) //Soybean paper - Agmip High temp Response
				{
				changeHi=grain[ccwc]-((-0.0205*maxTempAvg+1.2629)*grain[ccwc]);
				changeHi=min(1.0,max(changeHi,0.0));
				//changeHi=((1-(-15.097*maxTempAvg+407.77)/100)*grain[ccwc]);
				if((grain[ccwc]-changeHi)>0.05)
					{
					grain[ccwc]-=changeHi;
					stem[ccwc]+=changeHi/2;
					leaf[ccwc]+=changeHi/2;
					}
				else
					{
					 stem[ccwc]+= (grain[ccwc]-0.05)/2;
					 leaf[ccwc]+= (grain[ccwc]-0.05)/2;
					 grain[ccwc]=0.05;
					}
					harvIdxFlag=0;
				}
			}

		//wheat and corn
			if(harvIdxFlag==1&&crop[ccwc]==6&&PGI[ccwc]>=0.6||crop[ccwc]==2&&harvIdxFlag==1&&PGI[ccwc]>=0.3||crop[ccwc]==18&&harvIdxFlag==1&&PGI[ccwc]>=0.6)
				{
				if(countTemp>0)
				{
				maxTempAvg=maxTempAvg/countTemp;
				countTemp=0;
				}
				//maxTempAvg=maxTempAvg/countTemp; //for average calc
					if(maxTempAvg>(OptimumT[ccwc]+cropTempAdd))
					{harvFact=(OptimumT[ccwc]+cropTempAdd-maxTempAvg)*harvSlope;
					newHi= ((0.44-harvFact)*grain[ccwc]/0.44);
					changeHi=(grain[ccwc]-newHi);

					
					if((grain[ccwc]-changeHi)>0.05)
					{
					grain[ccwc]-=changeHi;
					stem[ccwc]+=changeHi/2;
					leaf[ccwc]+=changeHi/2;
					}
					else
					{
					 stem[ccwc]+= (grain[ccwc]-0.05)/2;
					 leaf[ccwc]+= (grain[ccwc]-0.05)/2;
					 grain[ccwc]=0.05;
					}
					
					//grain[ccwc]-=changeHi;
					//straw[ccwc]+=changeHi;
					harvIdxFlag=0;
					}

				}


	
		
		
		
		if(harvIdxFlag==1&&crop[ccwc]==1&&PGI[ccwc]>=0.6||harvIdxFlag==1&&crop[ccwc]==43&&PGI[ccwc]>=0.6)
				{
			if(countTemp>0)
				{	
				maxTempAvg=maxTempAvg/countTemp; //for average calc
				}
			
			if(maxTempAvg>38.0)//cropTempAdd //default +3.0
					{ 
					
				//	harvFact=max((maxTempAvg-34),1.0);
				//	newHi= grain[ccwc]*(1-log10(harvFact));

						harvFact=1-(maxTempAvg-38.0)*0.019; //Carberry 1989 - Testing the ceres maize simulation model in a semi-arid tropical environment.
						newHi=(harvFact*grain[ccwc]);
						changeHi=(grain[ccwc]-newHi);
			
							if(newHi>0.05) //ensure that grain fraction remains above 0.05
								{
								grain[ccwc]-=changeHi;
								stem[ccwc]+=changeHi/2;
								leaf[ccwc]+=changeHi/2;
								}
							else
								{
								 stem[ccwc]+= (grain[ccwc]-0.05)/2;
								leaf[ccwc]+= (grain[ccwc]-0.05)/2;
								grain[ccwc]=0.05;
								}
						harvIdxFlag=0;
					}
			//waterStress
				float cornStress;


				}
   
		//	harvIdxFlag=0;
		 

			
			//float finalGrainStage;
			//if(crop[ccwc]==57)
			//{finalGrainStage=.89;}
		//	else
			//{finalGrainStage=1.0;}

													
			
			}//end loop PGI<GST


			
						float finalGrainStage;
			if(crop[ccwc]==57)
			{finalGrainStage=.89;}
			else
			{finalGrainStage=1.0;}
			f_grain[ccwc] = 1.00 * (PGI[ccwc] - GST) / (finalGrainStage - GST) * grain[ccwc];//1.7 * is default - adjusts the rate at which grain accumulation occurs.
			
			if(f_grain[ccwc]>grain[ccwc]) f_grain[ccwc] = grain[ccwc];
			
		}	//end loop land type Tree or not




		//Brian was turned off to allow for dynamic growth biomass fractions!!!

//	f_stem[ccwc] = (1.0 - f_root[ccwc] - f_grain[ccwc])/2;
//		f_leaf[ccwc]=f_stem[ccwc];
   }
   else// if PGI <= 0.0 ...never seems to happen.
   {		


   //turned off for perrenial grasses option 12 and 11
   
 //   f_root[ccwc] = 0.0;
 //    f_grain[ccwc] = 0.0;
//	f_leaf[ccwc] = 0.0;
//f_stem[ccwc] = 0.0;
   }


float rootGrow,stemGrow,leafGrow,grainGrow,fractionGrow, podGrow;//intitalize if fractions are growing from start
rootGrow=1.0;
stemGrow=1.0;
leafGrow=1.0;
grainGrow=0.0;
podGrow = 0.0;

float f_pod;//biomass fraction for pod growth
if (PGI[ccwc] < GrainFill[ccwc]&&PGI[ccwc]>0.5)
{
	//f_pod = f_grain[ccwc];
	f_pod = 0.5 * (PGI[ccwc] - 0.5) / (GrainFill[ccwc] - 0.5) * grain[ccwc];//grain[ccwc]
}
else
{
	f_pod = 0.0;
}
if(PerennialFlag[ccwc]==0)//annual crops
{


			if(Root_Wt[ccwc]<=OptRootC[ccwc] )//if root_wt (in kgC/ha) is less than OptRootC
			{
				rootGrow = 1.0;
				
			}//if set to zero dynamic fractions don't work.
			else
			{
				rootGrow = 0.0;
			}
			if (Leaf_Wt[ccwc]<= OptLeafC[ccwc])
			{
				leafGrow = 1.0;
				if (PGI[ccwc] >= GrainFill[ccwc] &&crop[ccwc]==3)leafGrow = 1.0;//testing Agmip
			}
			else
			{
				leafGrow = 0.0;
			}
			if(Stem_Wt[ccwc]<= OptStemC[ccwc])
				{
				stemGrow = 1.0;
					if (PGI[ccwc] >= GrainFill[ccwc] && crop[ccwc] == 3)stemGrow = 1.0;//testing agmip
				}
			else
			{
				stemGrow = 0.0;
			}
			if (crop[ccwc] == 3) //testing soybean POD partitioning for soybean
			{
				if (PGI[ccwc] > 0.5 && PGI[ccwc] <= GST)
				{
					podGrow = 1.0;
					grainGrow = 0.0;
				}
				else if(PGI[ccwc] > GST)
				{
					grainGrow = 1.0;
					podGrow = 0.0;
				}
				if (OptGrainC[ccwc] <= Grain_Wt[ccwc])
				{
					grainGrow = 0.0;
				}
			}
			else
			{


				if (PGI[ccwc] > GST)//GST=GrainFill PGI timing
				{
					grainGrow = 1.0;
					podGrow = 0.0;
					if (OptGrainC[ccwc] <= Grain_Wt[ccwc])
					{
						grainGrow = 0.0;
					}
				}
			}
}
else //for perrennial growth
{
	float rootCO2C,leafCO2C,stemCO2C,grainCO2C;

	rootCO2C = maxmn[ccwc] * plantcn[ccwc] * root[ccwc];
	leafCO2C = maxmn[ccwc] * plantcn[ccwc] * leaf[ccwc];
	stemCO2C = maxmn[ccwc] * plantcn[ccwc] * stem[ccwc];
	grainCO2C = maxmn[ccwc] * plantcn[ccwc] * grain[ccwc];


			if((rootCO2C ) <=Root_Wt[ccwc])//OptRootC[ccwc] but doesn't take into account CO2
			{
				rootGrow = 0.0;}//if set to zero dynamic fractions don't work.
			if((leafCO2C) <=Leaf_Wt[ccwc])
				{leafGrow = 0.0;}
			if((stemCO2C) <=Stem_Wt[ccwc])
				{stemGrow = 0.0;}
			if((grainCO2C) <=Grain_Wt[ccwc])
			{grainGrow = 0.0;}
}

fractionGrow=f_root[ccwc]*rootGrow+f_stem[ccwc]*stemGrow + f_leaf[ccwc]*leafGrow+f_grain[ccwc]*grainGrow;
if(fractionGrow<=0)
{fractionGrow=1.0;}
	








//this is an old way
float leafGrow1=1.0, stemGrow1=1.0, rootGrow1=1.0, grainGrow1=0.0, podGrow1=0.0;
if (PGI[ccwc] >= GrainFill[ccwc])grainGrow1 = 1.0;
if (crop[ccwc] == 3 && PGI[ccwc] > 0.5)podGrow1 = 1.0;
if (Leaf_Wt[ccwc] > 0)leafGrow1 = 1.0;
if (Stem_Wt[ccwc] > 0)stemGrow1 = 1.0;
if (Root_Wt[ccwc] > 0)rootGrow1 = 1.0;
if (Pod_Wt[ccwc] > 0)podGrow1 = 1.0;
if (Grain_Wt[ccwc] > 0)grainGrow1 = 1.0;

float weightedTotalFractions = leafGrow1 * f_leaf[ccwc] / leafcn[ccwc] + stemGrow1 * f_stem[ccwc] / stemcn[ccwc] + rootGrow1 * f_root[ccwc] / rootcn[ccwc] + grainGrow1 * f_grain[ccwc] / graincn[ccwc] + podGrow1 * f_pod / graincn[ccwc];
float weightedLeafFraction=0.0, weightedStemFraction=0.0, weightedPodFraction=0.0, weightedGrainFraction=0.0, weightedRootFraction=0.0;
int transLeafFlag=0, transStemFlag=0, transRootFlag=0;




float adjLeafC = 1.0, adjLeafCN = 1.0, adjLeafN = 1.0, adjStemC = 1.0, adjStemCN = 1.0, adjStemN = 1.0, adjRootC = 1.0, adjRootCN = 1.0, adjRootN = 1.0, adjPodC = 1.0, adjPodCN = 1.0, adjPodN = 1.0, adjGrainC = 1.0, adjGrainCN = 1.0, adjGrainN = 1.0;
float NEWplantcn = (leafGrow1 * f_leaf[ccwc]  + stemGrow1 * f_stem[ccwc]  + rootGrow1 * f_root[ccwc]  + grainGrow1 * f_grain[ccwc] + podGrow1 * f_pod / graincn[ccwc])/weightedTotalFractions;


  float newPlantTotalN, newPlantTotalC2, newPlantTotalC,oldLeafN,oldStemN,oldRootN,oldGrainN,tempNewC,oldPodN,LeafNOLD = 0.0,StemNOLD = 0.0,RootNOLD = 0.0,GrainNOLD = 0.0,PodNOLD=0.0;
  
  newPlantTotalN=plantn[ccwc];//Day_GrowthN[ccwc]+plantn[ccwc]; //based on growthN+oldplantN for new current plantN
  newPlantTotalC =(newPlantTotalN)*plantcn[ccwc];//the new plant C though it uses the plantcn based on all components being growht and their cn ratios. plantcn[ccwc]
  newPlantTotalC2= (newPlantTotalN)*NEWplantcn; //using all the N uptake
  
 
  

 //calculating the weighted contribution of the plant N 
    float wRoot, wStem, wLeaf, wGrain,totwPlant;

	wRoot = plantcn[ccwc] / rootcn[ccwc] * f_root[ccwc];
  wStem = plantcn[ccwc] / stemcn[ccwc] * f_stem[ccwc];
  wLeaf = plantcn[ccwc] / leafcn[ccwc] * f_leaf[ccwc];
  wGrain = plantcn[ccwc] / graincn[ccwc] * f_grain[ccwc];
  totwPlant = wRoot + wStem + wLeaf + wGrain;
  wRoot = wRoot / totwPlant;
  wLeaf = wLeaf / totwPlant;
  wStem = wStem / totwPlant;
  wGrain = wGrain / totwPlant;



  //calculating the new C:N for fractions based on dynamic fractions
  rootcnDyn[ccwc] = newPlantTotalC * f_root[ccwc] / (plantn[ccwc] * wRoot);
  stemcnDyn[ccwc] = newPlantTotalC * f_stem[ccwc] / (plantn[ccwc] * wStem);
  leafcnDyn[ccwc] = newPlantTotalC * f_leaf[ccwc] / (plantn[ccwc] * wLeaf);
  graincnDyn[ccwc] = newPlantTotalC * f_grain[ccwc] / (plantn[ccwc] * wGrain);




  //dont change this...storing existing Leaf,Stem, Root, GrainN amounts

	oldLeafN=LeafN[ccwc];
	oldStemN=StemN[ccwc];
	oldRootN=RootN[ccwc];
	oldGrainN=GrainN[ccwc];
	oldPodN = PodN[ccwc];
	float difLeafFraction = 0.0;//difference in leaf fraction change due to senescence

	

if(PerennialFlag[ccwc]==0 && plantn[ccwc]>0)//annual crops
{
	//currently a disconnect between newPlantTotalC (based on plantn and growthN - from N demand curves) and then having this dynamic fractions reallocate the totalPlantC to a new C:N ratio based on the plant fraction) plantn[ccwc]>grainN+rootN+stemN+LeafN
	//float weightedTotalFractions = leafGrow * f_leaf[ccwc]/leafcn[ccwc] + stemGrow * f_stem[ccwc]/stemcn[ccwc] + rootGrow * f_root[ccwc]/rootcn[ccwc] + grainGrow * f_grain[ccwc]/graincn[ccwc]+podGrow*f_pod/graincn[ccwc];
	if (grainGrow == 1)
	{
	//	leafGrow = 0;
	 //   stemGrow = 0;
	//	rootGrow = 0;

	}
	
	if(leafGrow>0)
			{
				
				if (PGI[ccwc] > 2.6)//off atm
				{
					crop_Leafsenescence(ccwc);
					float newFleaf;
					newFleaf = (LeafN[ccwc] * leafcn[ccwc]) / newPlantTotalC;
					difLeafFraction = f_leaf[ccwc] - newFleaf;
					LeafN[ccwc] = newPlantTotalC * newFleaf / leafcn[ccwc];//newPlantTotalC/plantcn[ccwc]*f_leaf[ccwc];//newPlantTotalC*f_leaf[ccwc]/leafcn[ccwc];
				}
				else {

					if (crop[ccwc] == 3)//soybean
					{
						//only fractions that are growing.
						weightedLeafFraction = (f_leaf[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));

						//float weightedLeafFraction = f_leaf[ccwc]/plantcn[ccwc]/ weightedTotalFractions;


						// Allocates all the N from the growth curve to the LeafN fraction
						LeafN[ccwc] += weightedLeafFraction * Day_GrowthN[ccwc];
						adjLeafN = newPlantTotalC * f_leaf[ccwc] / leafcn[ccwc];//same as old LeafN to track the eventually calculation of leaf C
						adjLeafC = newPlantTotalC * f_leaf[ccwc];//target LeafC that is based off the growth curve
						adjLeafCN = adjLeafC / (LeafN[ccwc]);//the newly calibrated CN for leaf using old leafcn . This makes the C:N ratio allowed to be much narrower than the user defined C:N ratio for the fraction.
						//will need to eventually put limits on the C:N by increasing the adjLeafC to meet the mininum C:N that that fraction could expect to have. 

					}
					else//do the classic calculation for discerning LeafN
					{
						//LeafN[ccwc] = newPlantTotalC * weightedLeafFraction / plantcn[ccwc];

						//WORKS
						LeafN[ccwc] = newPlantTotalC * f_leaf[ccwc] / leafcn[ccwc];//old way using lower plant C and fractions of leaf

						//weightedLeafFraction = (f_leaf[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));

						//LeafN[ccwc] += weightedLeafFraction/leafcn[ccwc] * newPlantTotalC;
					}


					 }
			  

			}
			if(stemGrow>0)
			{
				if (PGI[ccwc] > 2.6)
				{
					StemN[ccwc] = newPlantTotalC * (f_stem[ccwc]+difLeafFraction/2) / stemcn[ccwc];

				}
				else
				{
					if (crop[ccwc] == 3)
					{
						weightedStemFraction = (f_stem[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));

						//float weightedStemFraction = f_stem[ccwc] / plantcn[ccwc] / weightedTotalFractions;
						//StemN[ccwc] = newPlantTotalC * weightedStemFraction / plantcn[ccwc];
						StemN[ccwc] += weightedStemFraction * Day_GrowthN[ccwc];
						adjStemN = newPlantTotalC * f_stem[ccwc] / stemcn[ccwc];//same as old LeafN
						adjStemC = newPlantTotalC * f_stem[ccwc];//target LeafC
						adjStemCN = adjStemC / (StemN[ccwc]);//the newly calibrated CN for leaf using old leafcn
					}
					else
					{
						//WORKS
						StemN[ccwc] = newPlantTotalC * f_stem[ccwc] / stemcn[ccwc];//old way
						//weightedStemFraction = (f_stem[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));
						//StemN[ccwc] += weightedStemFraction/stemcn[ccwc] *newPlantTotalC;

					}
					


					//StemNOLD = oldPlantC * f_stem[ccwc] / stemcn[ccwc];
																			   
					//StemN[ccwc] = newPlantTotalC * weightedStemFraction / stemcn[ccwc]; //newPlantTotalC/plantcn[ccwc]*f_stem[ccwc];



				}
			}
			if(rootGrow>0)
			{
				if (crop[ccwc] == 3)
				{
					weightedRootFraction = (f_root[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));

					//float weightedRootFraction = f_root[ccwc] / plantcn[ccwc] / weightedTotalFractions;
					//RootN[ccwc] = newPlantTotalC * weightedRootFraction / plantcn[ccwc];

					RootN[ccwc] += weightedRootFraction * Day_GrowthN[ccwc];
					adjRootN = newPlantTotalC * f_root[ccwc] / rootcn[ccwc];//same as old LeafN
					adjRootC = newPlantTotalC * f_root[ccwc];//target LeafC
					adjRootCN = adjRootC / (RootN[ccwc]);//the newly calibrated CN for leaf using old leafcn
				}
				else
				{
					//WORKS OLD WAY
					RootN[ccwc] = newPlantTotalC * f_root[ccwc] / rootcn[ccwc];//old way

					//weightedRootFraction = (f_root[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));


					//RootN[ccwc] += weightedRootFraction/rootcn[ccwc] * newPlantTotalC;

				}


	
			}
			if(grainGrow>0||podGrow>0)
			{
				if (PGI[ccwc] > 2.6)
				{
					GrainN[ccwc] = newPlantTotalC * (f_grain[ccwc]+difLeafFraction/2) / graincn[ccwc];
				}
				else 
				{

					if (crop[ccwc] == 3)//was testing for soybean
					{
						if (PGI[ccwc] < GrainFill[ccwc])//lest than grainfill but but when grainfilling reproductive occurs
						{
							weightedPodFraction = (f_pod / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));
							

							
							//float weightedPodFraction =f_pod / plantcn[ccwc] / weightedTotalFractions;
							//PodN[ccwc] = newPlantTotalC * weightedPodFraction / plantcn[ccwc];
							PodN[ccwc] += weightedPodFraction * Day_GrowthN[ccwc];//weightedPodFraction
							//float addedFixPodN;
							//addedFixPodN = weightedPodFraction * Day_GrowthN[ccwc]*0.0;//weightedPodFraction
							//day_fixN[ccwc] += addedFixPodN;
							//yr_fixn[ccwc] += addedFixPodN;
							adjPodN = newPlantTotalC * f_pod / graincn[ccwc];//same as old LeafN
							adjPodC = newPlantTotalC * f_pod;//target LeafC
							adjPodCN = adjPodC / (PodN[ccwc]);//the newly calibrated CN for leaf using old leafcn

							//WORKS OLD WAY
							//PodN[ccwc] = newPlantTotalC * f_pod / graincn[ccwc];//f_grain[ccwc]
							//float addedFixPodN;
							//addedFixPodN = (plantn[ccwc] - Day_GrowthN[ccwc]) * f_pod / graincn[ccwc];
							//day_fixN[ccwc] += addedFixPodN;
							//yr_fixn[ccwc] += addedFixPodN;




						}
						else//still soybean growht but now filling seed part.
						{
							weightedGrainFraction = (f_grain[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));
							//float weightedGrainFraction = f_grain[ccwc] / plantcn[ccwc] / weightedTotalFractions;
							//GrainN[ccwc] = newPlantTotalC * weightedGrainFraction / plantcn[ccwc];
							GrainN[ccwc] += weightedGrainFraction * Day_GrowthN[ccwc];//works with dynamic CN
							//GrainN[ccwc] = 0.0;
							
							
								

								
								float transRate = 0.45 * (PGI[ccwc] - GrainFill[ccwc]) / (1 - GrainFill[ccwc]);
								transRate = 0.08;
								//float transRate = 0.1;
								float actualLeafCN = Leaf_Wt[ccwc] / LeafN[ccwc];
								float actualStemCN= Stem_Wt[ccwc] / StemN[ccwc];
								float actualRootCN=Root_Wt[ccwc] / RootN[ccwc];

								float transLeaf, transStem, transRoot;
								if (actualLeafCN < leafcn[ccwc])//adjLeafCN
								{
									//float targetLeafN = Leaf_Wt[ccwc] / leafcn[ccwc];
									//float difLeafN = LeafN[ccwc] - targetLeafN;
									//float transRate = (PGI[ccwc] - GrainFill[ccwc]) / (1.0 - GrainFill[ccwc]);

									transRate = min(0.15, max(0.0, transRate));
									transLeaf = LeafN[ccwc] * transRate;
									float checkLeafCN = Leaf_Wt[ccwc] / (LeafN[ccwc] - transLeaf);
									if (checkLeafCN > leafcn[ccwc])transLeaf = LeafN[ccwc] - (Leaf_Wt[ccwc] / leafcn[ccwc]);

									LeafN[ccwc] -= transLeaf;
									GrainN[ccwc] += transLeaf;
									transLeafFlag = 1;

									adjLeafN = newPlantTotalC * f_leaf[ccwc] / leafcn[ccwc];//same as old LeafN
									adjLeafC = newPlantTotalC * f_leaf[ccwc];//target LeafC
									adjLeafCN = adjLeafC / (LeafN[ccwc]);//the newly calibrated CN for leaf using old leafcn

								}
								if (actualStemCN < stemcn[ccwc])//adjStemCN
								{
									//float targetStemN = Stem_Wt[ccwc] / stemcn[ccwc];
									//float difStemN = StemN[ccwc] - targetStemN;
									//float transRate = (PGI[ccwc] - GrainFill[ccwc]) / (1.0 - GrainFill[ccwc]);
									transRate = min(0.15, max(0.0, transRate));
									transStem = StemN[ccwc] * transRate;
									float checkStemCN = Stem_Wt[ccwc] / (StemN[ccwc] - transStem);
									if (checkStemCN > stemcn[ccwc])transStem = StemN[ccwc] - (Stem_Wt[ccwc] / stemcn[ccwc]);

									StemN[ccwc] -= transStem;
									GrainN[ccwc] += transStem;
									transStemFlag = 1;

									adjStemN = newPlantTotalC * f_stem[ccwc] / stemcn[ccwc];//same as old LeafN
									adjStemC = newPlantTotalC * f_stem[ccwc];//target LeafC
									adjStemCN = adjStemC / (StemN[ccwc]);//the newly calibrated CN for leaf using old leafcn
								}
								if (actualRootCN < rootcn[ccwc])//adjRootCN
								{
									//float targetRootN = Root_Wt[ccwc] / rootcn[ccwc];
									//float difRootN = RootN[ccwc] - targetRootN;
									//float transRate = (PGI[ccwc] - GrainFill[ccwc]) / (1.0 - GrainFill[ccwc]);
									transRate = min(0.15, max(0.0, transRate));
									transRoot = RootN[ccwc] * transRate;
									float checkRootCN = Root_Wt[ccwc] / (RootN[ccwc] - transRoot);
									if (checkRootCN > rootcn[ccwc])transRoot = RootN[ccwc] - (Root_Wt[ccwc] / rootcn[ccwc]);

									RootN[ccwc] -= transRoot;
									GrainN[ccwc] += transRoot;
									transRootFlag = 1;

									adjRootN = newPlantTotalC * f_root[ccwc] / rootcn[ccwc];//same as old LeafN
									adjRootC = newPlantTotalC * f_root[ccwc];//target LeafC
									adjRootCN = adjRootC / (RootN[ccwc]);//the newly calibrated CN for leaf using old leafcn
								}
								adjGrainN = newPlantTotalC * f_grain[ccwc] / graincn[ccwc];//same as old LeafN
								adjGrainC = newPlantTotalC * f_grain[ccwc];//target LeafC
								adjGrainCN = adjGrainC / (GrainN[ccwc]);//the newly calibrated CN for leaf using old leafcn
							


							//WORKS OLD Way
							//GrainN[ccwc] = newPlantTotalC * f_grain[ccwc] / graincn[ccwc];




						}

					}
					else // for crops other than soybean
					{
						weightedGrainFraction = (f_grain[ccwc] / (f_leaf[ccwc] * leafGrow + f_stem[ccwc] * stemGrow + f_root[ccwc] * rootGrow + f_grain[ccwc] * grainGrow + f_pod * podGrow));
						//float weightedGrainFraction = f_grain[ccwc] / plantcn[ccwc] / weightedTotalFractions;
						//GrainN[ccwc] = newPlantTotalC * weightedGrainFraction / plantcn[ccwc];
						
						

						if (crop[ccwc] == 3)
						{

							GrainN[ccwc] += weightedGrainFraction * Day_GrowthN[ccwc];


							// if PGI>0.75

							float transRate = 0.45 * (PGI[ccwc] - GrainFill[ccwc]) / (1 - GrainFill[ccwc]);
							//float transRate = 0.1;
							float actualLeafCN = Leaf_Wt[ccwc] / LeafN[ccwc];
							float actualStemCN = Stem_Wt[ccwc] / StemN[ccwc];
							float actualRootCN = Root_Wt[ccwc] / RootN[ccwc];

							float transLeaf, transStem, transRoot;
							if (actualLeafCN < leafcn[ccwc])//adjLeafCN
							{
								//float targetLeafN = Leaf_Wt[ccwc] / leafcn[ccwc];
								//float difLeafN = LeafN[ccwc] - targetLeafN;
								//float transRate = (PGI[ccwc] - GrainFill[ccwc]) / (1.0 - GrainFill[ccwc]);

								transRate = min(0.15, max(0.0, transRate));
								transLeaf = LeafN[ccwc] * transRate;
								float checkLeafCN = Leaf_Wt[ccwc] / (LeafN[ccwc] - transLeaf);
								if (checkLeafCN > leafcn[ccwc])transLeaf = LeafN[ccwc] - (Leaf_Wt[ccwc] / leafcn[ccwc]);

								LeafN[ccwc] -= transLeaf;
								GrainN[ccwc] += transLeaf;
								transLeafFlag = 1;

								adjLeafN = newPlantTotalC * f_leaf[ccwc] / leafcn[ccwc];//same as old LeafN
								adjLeafC = newPlantTotalC * f_leaf[ccwc];//target LeafC
								adjLeafCN = adjLeafC / (LeafN[ccwc]);//the newly calibrated CN for leaf using old leafcn

							}
							if (actualStemCN < stemcn[ccwc])//adjStemCN
							{
								//float targetStemN = Stem_Wt[ccwc] / stemcn[ccwc];
								//float difStemN = StemN[ccwc] - targetStemN;
								//float transRate = (PGI[ccwc] - GrainFill[ccwc]) / (1.0 - GrainFill[ccwc]);
								transRate = min(0.15, max(0.0, transRate));
								transStem = StemN[ccwc] * transRate;
								float checkStemCN = Stem_Wt[ccwc] / (StemN[ccwc] - transStem);
								if (checkStemCN > stemcn[ccwc])transStem = StemN[ccwc] - (Stem_Wt[ccwc] / stemcn[ccwc]);

								StemN[ccwc] -= transStem;
								GrainN[ccwc] += transStem;
								transStemFlag = 1;

								adjStemN = newPlantTotalC * f_stem[ccwc] / stemcn[ccwc];//same as old LeafN
								adjStemC = newPlantTotalC * f_stem[ccwc];//target LeafC
								adjStemCN = adjStemC / (StemN[ccwc]);//the newly calibrated CN for leaf using old leafcn
							}
							if (actualRootCN < rootcn[ccwc])//adjRootCN
							{
								//float targetRootN = Root_Wt[ccwc] / rootcn[ccwc];
								//float difRootN = RootN[ccwc] - targetRootN;
								//float transRate = (PGI[ccwc] - GrainFill[ccwc]) / (1.0 - GrainFill[ccwc]);
								transRate = min(0.15, max(0.0, transRate));
								transRoot = RootN[ccwc] * transRate;
								float checkRootCN = Root_Wt[ccwc] / (RootN[ccwc] - transRoot);
								if (checkRootCN > rootcn[ccwc])transRoot = RootN[ccwc] - (Root_Wt[ccwc] / rootcn[ccwc]);

								RootN[ccwc] -= transRoot;
								GrainN[ccwc] += transRoot;
								transRootFlag = 1;

								adjRootN = newPlantTotalC * f_root[ccwc] / rootcn[ccwc];//same as old LeafN
								adjRootC = newPlantTotalC * f_root[ccwc];//target LeafC
								adjRootCN = adjRootC / (RootN[ccwc]);//the newly calibrated CN for leaf using old leafcn
							}
							adjGrainN = newPlantTotalC * f_grain[ccwc] / graincn[ccwc];//same as old LeafN
							adjGrainC = newPlantTotalC * f_grain[ccwc];//target LeafC
							adjGrainCN = adjGrainC / (GrainN[ccwc]);//the newly calibrated CN for leaf using old leafcnon);

						}
						else
						{
							//WORKS OLD WAY
							GrainN[ccwc] = newPlantTotalC * f_grain[ccwc] / graincn[ccwc];
						}


	
					}
				//	GrainN[ccwc] = newPlantTotalN * wGrain;
			//	GrainN[ccwc] = newPlantTotalN * f_grain[ccwc];//newPlantTotalC/plantcn[ccwc]*f_grain[ccwc];
				}
			
			}
			//plantcn[ccwc] = (leafGrow * f_leaf[ccwc]  + stemGrow * f_stem[ccwc]  + rootGrow * f_root[ccwc]  + grainGrow * f_grain[ccwc] + podGrow * f_pod / graincn[ccwc])/weightedTotalFractions;
	
}
else //for perrenial growth
{





			if(leafGrow>0)
			{
			 // LeafN[ccwc] = newPlantTotalC*f_leaf[ccwc]/leafcn[ccwc];
			LeafN[ccwc] = Day_GrowthN[ccwc]*(f_leaf[ccwc]/(f_leaf[ccwc]*leafGrow+f_stem[ccwc]*stemGrow+f_root[ccwc]*rootGrow+f_grain[ccwc]*grainGrow))+oldLeafN;

			}
			if(stemGrow>0)
			{
			  // StemN[ccwc]  = newPlantTotalC*f_stem[ccwc]/stemcn[ccwc];
			  StemN[ccwc] = Day_GrowthN[ccwc]*(f_stem[ccwc]/(f_leaf[ccwc]*leafGrow+f_stem[ccwc]*stemGrow+f_root[ccwc]*rootGrow+f_grain[ccwc]*grainGrow))+oldStemN;
			}
			if(rootGrow>0)
			{
			  // RootN[ccwc] = newPlantTotalC*f_root[ccwc]/rootcn[ccwc];
			   RootN[ccwc] = Day_GrowthN[ccwc]*(f_root[ccwc]/(f_leaf[ccwc]*leafGrow+f_stem[ccwc]*stemGrow+f_root[ccwc]*rootGrow+f_grain[ccwc]*grainGrow))+oldRootN;
			}
			if(grainGrow>0)
			{
			  //GrainN[ccwc] = newPlantTotalC*f_grain[ccwc]/graincn[ccwc];


				GrainN[ccwc] = Day_GrowthN[ccwc]*(f_grain[ccwc]/(f_leaf[ccwc]*leafGrow+f_stem[ccwc]*stemGrow+f_root[ccwc]*rootGrow+f_grain[ccwc]*grainGrow))+oldGrainN;
			}

}


//if ((LeafN[ccwc] - oldLeafN) >= 0.0)
//{
//	DayGrow_LeafN[ccwc] = LeafN[ccwc] - oldLeafN;
//}
//else
//{
//	LeafN[ccwc] = 0.0;
//	DayGrow_LeafN[ccwc] = 0.0;

//}


//New Growth N is the previous old growth N 

//calculates to see if the crop actually grew. Shouldn't be allowed to be negative. Problem in above calculations if so. h
  DayGrow_LeafN[ccwc] = LeafN[ccwc] - oldLeafN;
  DayGrow_StemN[ccwc] = StemN[ccwc]-oldStemN;
  DayGrow_RootN[ccwc] =  RootN[ccwc]-oldRootN;
  DayGrow_GrainN[ccwc] =  GrainN[ccwc]-oldGrainN;
  DayGrow_PodN[ccwc] = PodN[ccwc] - oldPodN;//new soybean pod Growth


  //If Translocation occuring....Carbon stays constant in fractions but N shifts.
  if (transLeafFlag == 1 && DayGrow_LeafN[ccwc]<0) DayGrow_LeafN[ccwc] = 0;
  if (transStemFlag == 1 && DayGrow_StemN[ccwc] < 0) DayGrow_StemN[ccwc] = 0;
  if (transRootFlag == 1 && DayGrow_RootN[ccwc] < 0) DayGrow_RootN[ccwc] = 0;

  
//  DayGrow_LeafN[ccwc] = LeafNOLD - oldLeafN;
 // DayGrow_StemN[ccwc] = StemNOLD - oldStemN;
 // DayGrow_RootN[ccwc] = RootNOLD - oldRootN;
 // DayGrow_GrainN[ccwc] = GrainNOLD - oldGrainN;
 // DayGrow_PodN[ccwc] = PodNOLD - oldPodN;//new soybean pod Growth
  


  
 // DayGrow_LeafN[ccwc] = f_leaf[ccwc]*Day_GrowthN[ccwc]; 
 // DayGrow_StemN[ccwc] = f_stem[ccwc]*Day_GrowthN[ccwc];
 // DayGrow_RootN[ccwc] =  f_root[ccwc]*Day_GrowthN[ccwc];
 // DayGrow_GrainN[ccwc] =  f_grain[ccwc]*Day_GrowthN[ccwc];
  




   



   //Daily crop C increase
	if(LandUse==6)//trees
	{
		Day_C_growth[ccwc] = plantcn[ccwc] * Day_GrowthN[ccwc];
		dayG_grain[ccwc] = Day_C_growth[ccwc] * f_grain[ccwc];
		dayG_root[ccwc] = Day_C_growth[ccwc] * f_root[ccwc];
		dayG_leaf[ccwc] = Day_C_growth[ccwc] * f_leaf[ccwc];
		dayG_stem[ccwc] = Day_C_growth[ccwc] * f_stem[ccwc];
		
		YrG_grain[ccwc] += dayG_grain[ccwc];
		YrG_leaf[ccwc] += dayG_leaf[ccwc];
		YrG_stem[ccwc] += dayG_stem[ccwc];
		YrG_root[ccwc] += dayG_root[ccwc];

		Root_Wt[ccwc] += dayG_root[ccwc];
		Grain_Wt[ccwc] += dayG_grain[ccwc];
		Leaf_Wt[ccwc] += dayG_leaf[ccwc];
		Stem_Wt[ccwc] += dayG_stem[ccwc];

	}
	else//normal annual crops
	{












		//Daily biomass growth	
		float cnBuffer;
		cnBuffer = 1.0;
		if (crop[ccwc] == 10 || crop[ccwc] == 89 || crop[ccwc] == 1 || crop[ccwc] == 43 || crop[ccwc] == 6 || crop[ccwc] == 57 || crop[ccwc] == 90)//|| crop[ccwc]==89 ||crop[ccwc]==1
		{
			if (N_stress[ccwc] < 1.0)//turned off was 1.0
			{
				float maxBuffer;
				maxBuffer = min(1.0, (max(0.70, N_stress[ccwc])));



				cnBuffer = maxBuffer;
				//1.0+(1.0-maxBuffer);
			}
		}
		cnBuffer = 1.0;//for all crops
	
		//calculates the C growth for each biomass fraction
		
//		float grainFact=1.0, rootFact=1.0, stemFact=1.0, leafFact=1.0, podFact=1.0;
//		if(weightedGrainFraction>0.0)grainFact = 1 / weightedGrainFraction * 10;
//		if (weightedRootFraction > 0.0)rootFact = 1 / weightedRootFraction * 10;
//		if (weightedLeafFraction > 0.0)leafFact = 1 / weightedLeafFraction * 10;
//		if (weightedStemFraction > 0.0)stemFact = 1 / weightedStemFraction * 10;
//		if (weightedPodFraction > 0.0)podFact = 1 / weightedPodFraction * 10;



//		dayG_grain[ccwc] = (DayGrow_GrainN[ccwc]) * grainFact/ cnBuffer;//This would need to be based off the C growth.
//		dayG_root[ccwc] = (DayGrow_RootN[ccwc])* rootFact  / cnBuffer;
//		dayG_leaf[ccwc] = (DayGrow_LeafN[ccwc])* leafFact / cnBuffer;
//		dayG_stem[ccwc] = (DayGrow_StemN[ccwc])* stemFact / cnBuffer;
//		dayG_pod[ccwc] = (DayGrow_PodN[ccwc])* podFact / cnBuffer;
//		Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc] + dayG_pod[ccwc];
		

		
//		float adjFactor;
//		adjFactor = plantcn[ccwc] / NEWplantcn;

		
//		dayG_grain[ccwc] = DayGrow_GrainN[ccwc] *adjFactor* graincn[ccwc] / cnBuffer;//This would need to be based off the C growth.
//		dayG_root[ccwc] = DayGrow_RootN[ccwc] * adjFactor * rootcn[ccwc] / cnBuffer;
//		dayG_leaf[ccwc] = DayGrow_LeafN[ccwc] * adjFactor * leafcn[ccwc] / cnBuffer;
//		dayG_stem[ccwc] = DayGrow_StemN[ccwc] * adjFactor * stemcn[ccwc] / cnBuffer;
//		dayG_pod[ccwc] = DayGrow_PodN[ccwc] * adjFactor * graincn[ccwc] / cnBuffer;
//		Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc] + dayG_pod[ccwc];
		
		
//		dayG_grain[ccwc] = (GrainNOLD - oldGrainN) * graincn[ccwc] / cnBuffer;//This would need to be based off the C growth.
//		dayG_root[ccwc] = (RootNOLD - oldRootN) * rootcn[ccwc] / cnBuffer;
//		dayG_leaf[ccwc] = (LeafNOLD - oldLeafN) * leafcn[ccwc] / cnBuffer;
//		dayG_stem[ccwc] = (StemNOLD - oldStemN) * stemcn[ccwc] / cnBuffer;
//		dayG_pod[ccwc] = (PodNOLD - oldPodN) * graincn[ccwc] / cnBuffer;
//		Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc] + dayG_pod[ccwc];
		


	


		if (crop[ccwc] == 3)
		{
			dayG_grain[ccwc] = DayGrow_GrainN[ccwc] * graincn[ccwc] / cnBuffer;//This would need to be based off the C growth.
			dayG_root[ccwc] = DayGrow_RootN[ccwc] * adjRootCN / cnBuffer;
			dayG_leaf[ccwc] = DayGrow_LeafN[ccwc] * adjLeafCN / cnBuffer;
			dayG_stem[ccwc] = DayGrow_StemN[ccwc] * adjStemCN / cnBuffer;
			dayG_pod[ccwc] = DayGrow_PodN[ccwc] * adjPodCN / cnBuffer;
			Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc] + dayG_pod[ccwc];
		}
		else
		{
			dayG_grain[ccwc] = DayGrow_GrainN[ccwc] * graincn[ccwc] / cnBuffer;//This would need to be based off the C growth.
			dayG_root[ccwc] = DayGrow_RootN[ccwc] * rootcn[ccwc] / cnBuffer;
			dayG_leaf[ccwc] = DayGrow_LeafN[ccwc] * leafcn[ccwc] / cnBuffer;
			dayG_stem[ccwc] = DayGrow_StemN[ccwc] * stemcn[ccwc] / cnBuffer;
			dayG_pod[ccwc] = DayGrow_PodN[ccwc] * graincn[ccwc] / cnBuffer;
			Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc] + dayG_pod[ccwc];
		}
		//Normal Way
		
//		dayG_grain[ccwc] = DayGrow_GrainN[ccwc] * graincn[ccwc] / cnBuffer;//This would need to be based off the C growth.
//		dayG_root[ccwc] = DayGrow_RootN[ccwc] * rootcn[ccwc] / cnBuffer;
//		dayG_leaf[ccwc] = DayGrow_LeafN[ccwc] * leafcn[ccwc] / cnBuffer;
//		dayG_stem[ccwc] = DayGrow_StemN[ccwc] * stemcn[ccwc] / cnBuffer;
//		dayG_pod[ccwc]= DayGrow_PodN[ccwc] * graincn[ccwc] / cnBuffer;
//		Day_C_growth[ccwc] = dayG_grain[ccwc] + dayG_root[ccwc] + dayG_leaf[ccwc] + dayG_stem[ccwc]+dayG_pod[ccwc];
		

		Grain_Wt[ccwc] += dayG_grain[ccwc];
		if (dayG_leaf[ccwc] < 0)
		{
			

		}

		
//		if ((Leaf_Wt[ccwc] += dayG_leaf[ccwc]) <= 0)
//		{
//			Leaf_Wt[ccwc] = 0.0;
//		}
//		else
//		{
//			Leaf_Wt[ccwc] += dayG_leaf[ccwc];
//		}
		
		Leaf_Wt[ccwc] += dayG_leaf[ccwc];
		Stem_Wt[ccwc] += dayG_stem[ccwc];
		Root_Wt[ccwc] += dayG_root[ccwc];
		Pod_Wt[ccwc] += dayG_pod[ccwc];


		// old way without cnBuffer
//		Grain_Wt[ccwc] = GrainN[ccwc] * graincn[ccwc];
//	Leaf_Wt[ccwc] = LeafN[ccwc] * leafcn[ccwc];
//	Stem_Wt[ccwc] = StemN[ccwc] * stemcn[ccwc];
//	Root_Wt[ccwc] = RootN[ccwc] * rootcn[ccwc];
	
		if (dayG_grain[ccwc] < 0.0 || dayG_leaf[ccwc] < 0.0 || dayG_stem[ccwc] < 0.0 || dayG_root[ccwc] < 0.0)//testing to see if negative C accumluation
		{
			float blah;

			blah = 1.0;
		}



		//testing to see if we can pass maximum values for each component to annual reports
		if (YrG_grain[ccwc] > (YrG_grain[ccwc] + dayG_grain[ccwc])) { if (YrG_grain[ccwc] > MaxYrG_grain[ccwc]) { MaxYrG_grain[ccwc] = YrG_grain[ccwc]; MaxYrN_grain[8] = YrN_grain[8]; } }
		else { MaxYrG_grain[ccwc] += dayG_grain[ccwc]; }
		
		if (YrG_leaf[ccwc] > (YrG_leaf[ccwc] + dayG_leaf[ccwc])) {if (YrG_leaf[ccwc] > MaxYrG_leaf[ccwc]) { MaxYrG_leaf[ccwc] = YrG_leaf[ccwc]; MaxYrN_leaf[8] = YrN_leaf[8]; }}
		else { MaxYrG_leaf[ccwc] += dayG_leaf[ccwc]; }
		if (YrG_stem[ccwc] > (YrG_stem[ccwc] + dayG_stem[ccwc])) { if (YrG_stem[ccwc] > MaxYrG_stem[ccwc]) { MaxYrG_stem[ccwc] = YrG_stem[ccwc]; MaxYrN_stem[8] = YrN_stem[8]; } }
		else { MaxYrG_stem[ccwc] += dayG_stem[ccwc]; }
		if (YrG_root[ccwc] > (YrG_root[ccwc] + dayG_root[ccwc])) { if (YrG_root[ccwc] > MaxYrG_root[ccwc]) { MaxYrG_root[ccwc] = YrG_root[ccwc]; MaxYrN_root[8] = YrN_root[8]; } }
		else { MaxYrG_root[ccwc] += dayG_root[ccwc]; }



		YrG_grain[ccwc] += dayG_grain[ccwc];
		YrG_leaf[ccwc] += dayG_leaf[ccwc];
		YrG_stem[ccwc] += dayG_stem[ccwc];
		YrG_root[ccwc] += dayG_root[ccwc];




	




	}


	//sets root_length[ccwc] based on maximum root length. Root growth function also uses max_root_length calc.
	if(Root_Wt[ccwc]>0.0) 
	{
		root_length[ccwc] = max_root_length[ccwc] * PGI[ccwc] * 3.0;
		if(root_length[ccwc] > max_root_length[ccwc]) root_length[ccwc] = max_root_length[ccwc];
	}
	else
		root_length[ccwc] = 0.0;

 	float Ftt = min(30.0, max(0.0,air_temp));

	float f_PGI=PGI[ccwc];

	if(PGI[ccwc]>0.4) f_PGI=0.4;
}























void class_model::ini_crop(int MODE, int ccwc)
{
	int i;


	//code to read in a planting date automatically for climate change
/*	
	if(jday==1)
	{
	int jdseeder,jdjunk;

   CString TESTFILE;
   FILE *pFile=NULL;
   TESTFILE.Format("%s\\Record\\plantingDate.txt",OUTPUT);
   pFile=fopen(TESTFILE,"r");
   for(int loopi=1;loopi<year;loopi++)
   {
	fscanf(pFile, "%d %d %d",&jdjunk,&jdjunk,&jdjunk);	   
   }
   if(crop[ccwc]==10)
   {
   fscanf(pFile, "%d %d %d",&jdjunk,&jdseed[ccwc],&jdjunk);
   }
   else
   {
	   fscanf(pFile, "%d %d %d",&jdjunk,&jdjunk,&jdseed[ccwc]);
   }
   fclose(pFile);
   
	}
	
*/
	//end code addition

	if(jday==jdseed[ccwc])//if dates is equal to seeding date.
	{
		//check to see if needs to initialize due to planting
		if (spinUpPlant == 1 && autoPlantF == 0)//needs to read in soil conditions to initialize at planting.
		{
			read_in_soil_parm(0, 0, 0);
		}

		if (SoilSpinUp == 1 && year == 1 && jday == jdseed[1]&&autoPlantF==0 && spinUpPlant == 1)//autoPlanting should be off
		{
			read_in_soil_parm(0, 0, 0);
			//write_out_soil_parm(0,0,0)
		}

		if (writeOutPlant == 1)
		{
			write_out_soil_parm(0, 0, 0);

		}

		crop_flag[ccwc] = 1;
		maturity_flag[ccwc] = 0;
		WiltFlag[ccwc]=0;

		read_in_vege(MODE, 1, ccwc);

		if(crop[ccwc]==20||crop[ccwc]==64||crop[ccwc]==65) //irrigated paddy rice
		{
			wetland_flag = 1;
			IrriRice_flag = 1;
			RainfedRice_flag = 0;
			DeepRice_flag = 0;
			rice_maturity_flag = 0;
		}		
		else if(crop[ccwc]==46)//rainfed rice
		{
			wetland_flag = 1;
			IrriRice_flag = 0;
			RainfedRice_flag = 1;
			DeepRice_flag = 0;
		}
		else if(crop[ccwc]==30)//deep-water rice
		{
			wetland_flag = 1;
			IrriRice_flag = 0;
			RainfedRice_flag = 0;
			DeepRice_flag = 1;
		}
		else
		{
			wetland_flag = 0;
			IrriRice_flag = 0;
			RainfedRice_flag = 0;
			DeepRice_flag = 0;
		}

		if(crop[ccwc]==20&&Transplant[ccwc]==1&&TDD[ccwc]==0.0)//where the model sets the biomass for transplantted crops like rice
		{

			
			///reading in the set transplanting allocations
			CString TESTFILE;
			FILE* pFile = NULL;
			TESTFILE.Format("%s\\Library\\Lib_crop\\transplant.txt", ROOTDIR);//flowering
			pFile = fopen(TESTFILE, "r");
			if (pFile == NULL)
			{
				CString note;
				note.Format("Can not OPEN transplanting file %s", TESTFILE);
				AfxMessageBox(note);
				exit(0);

			}
			float transTDD1, transGrain1, transLeaf1, transStem1, transRoot1, transPlant1;//initializing temporary variables for transplanting crop1
			float transTDD2, transGrain2, transLeaf2, transStem2, transRoot2, transPlant2;//initializing temporary variables for transplanting crop2
			int transSeed1, transSeed2;
			char cjunk[200];
			fscanf(pFile, "%s %s %s %s %s %s %s", &cjunk, &cjunk, &cjunk, &cjunk, &cjunk, &cjunk, &cjunk);
			fscanf(pFile, "%f %f %f %f %f %f %d", &transTDD1, &transGrain1, &transLeaf1, &transStem1, &transRoot1, &transPlant1, &transSeed1);//&crop 1 parameters 
			fscanf(pFile, "%f %f %f %f %f %f %d", &transTDD2, &transGrain2, &transLeaf2, &transStem2, &transRoot2, &transPlant2, &transSeed2);//&crop 2 parameters
			fclose(pFile);
		

		
			if(ccwc == 1)
				{
					TDD[ccwc] = transTDD1;
					Grain_Wt[ccwc] = transGrain1;
					Leaf_Wt[ccwc] = transLeaf1;
					Stem_Wt[ccwc] = transStem1;
					Root_Wt[ccwc] = transRoot1;
					plantn[ccwc] = transPlant1;
					seed[ccwc] = transSeed1;
				}
			else if (ccwc == 2)
			{
				TDD[ccwc] = transTDD2;
				Grain_Wt[ccwc] = transGrain2;
				Leaf_Wt[ccwc] = transLeaf2;
				Stem_Wt[ccwc] = transStem2;
				Root_Wt[ccwc] = transRoot2;
				plantn[ccwc] = transPlant2;
				seed[ccwc] = transSeed2;


			}
			else
			{//old fixed code
				TDD[ccwc] = 100.0;
				Grain_Wt[ccwc] = 0.0;
				Leaf_Wt[ccwc] = 30.0;
				Stem_Wt[ccwc] = 30.0;
				Root_Wt[ccwc] = 20.0;
				plantn[ccwc] = 4.0;
				seed[ccwc] = 30;

			}
			
			//TDD[ccwc] = 100.0;
			//Grain_Wt[ccwc] = 0.0;
			//Leaf_Wt[ccwc] = 30.0;
			//Stem_Wt[ccwc] = 30.0;
			//Root_Wt[ccwc] = 20.0;
			//plantn[ccwc] = 4.0;
			//seed[ccwc] = 30;
		}
		else
		{
			//seed[ccwc] = 1;

			if(PerennialFlag[ccwc]==0)//if not perrenial.
			{
				Grain_Wt[ccwc] = 0.0;
				Leaf_Wt[ccwc] = 0.0;
				Stem_Wt[ccwc] = 0.0;
				Pod_Wt[ccwc] = 0.0;
				Root_Wt[ccwc] = 0.0;
				GrainN[ccwc] = 0.0;
				LeafN[ccwc] = 0.0;
				StemN[ccwc] = 0.0;
				RootN[ccwc] = 0.0;
			}
		}
	
	}
}

void class_model::ini_cropAuto(int MODE, int ccwc)
{
	int i;//not used in routine

	//function meant to replace ini_crop if autoplant parameter is set to 1 in dnd


	//determine 

	//need to check if planting conditions are met for appropriate crop type (cool season or warm season)

		//conditions for cool season crops //Bootsma and De Jong 1988 (Can J. Plant Sci. 68:513-517)
		// snow on ground <10mm
		//daily precip <2mm
		//SW in layer 1 <0.90 Available water Content
		//SW in layer 2 <0.90 Available water Content
		//seeding to start 10d with these condtions after April 15th! or day 105

		//if(snow_pack<0.01)
			//if(precipitation<0.02)

		//initialize calc for wiltpw and fldcapw need different instructions for warm season crops.
		/*
		double wiltptw1 = h[1] * sts[1] * wiltpt[1];//calculate wiltpointwater for determining available soil layer water.Soil  Layer1
		double fldcapw1 = h[1] * sts[1] * fldcap[1];//calculate fieldpointwater for determining available soil layer water.Soil Layer1
		double wiltptw2 = h[2] * sts[2] * wiltpt[2];//calculate wiltpointwater for determining available soil layer water.Soil  Layer2
		double fldcapw2 = h[2] * sts[2] * fldcap[2];//calculate fieldpointwater for determining available soil layer water.Soil Layer2
		double totalAvailableWater1;//Available water capacity
		double totalAvailableWater2;//Available water capacity


		totalAvailableWater1 = fldcapw1 - wiltptw1;//determine maximum available water in layer1
		totalAvailableWater2 = fldcapw2 - wiltptw2;//determine maximum available water in layer2
		*/

	
		
		
	
	if (OptimumT[1] <= 23)//for cool season crops ///only checks Optimum temperature for array spot 1 --needs to be dynamic
	{
		int plantTime;//jday earliest planting date to start the calculations below. Can't occur on this date but it's the starting point calc
		if (year == 1)//first year set the plantTime accumulator to begin on day 105
		{
			plantTime = 115;
		}

		else 
    {
			if (lastFrost < 115) //lastfrost calculated in above function to track when last spring frost occured.
			{
				plantTime = lastFrost;//using previous years lastFrost to deterimine plantime
			}
			else
			{
				plantTime = 115; //else plantTime is last year

			}
		}

		int layerDepth = 0.1 / h[1];
		float avgWaterContent = 0.0;
		float avgFieldCapacity = 0.0;
		double wiltptw1;
		double fldcapw1;
		double totalAvailableWater1;
		
		for (int il = 1; il <= layerDepth; il++)
		{
			wiltptw1 = h[1] * sts[il] * wiltpt[il];//calculate wiltpointwater for determining available soil layer water.Soil  Layer1
			fldcapw1 = h[1] * sts[il] * fldcap[il];//calculate fieldpointwater for determining available soil layer water.Soil Layer1
			totalAvailableWater1 = fldcapw1 - wiltptw1;//determine maximum available water in layer1
			//avgWaterContent += day_wfps[il];
			//avgFieldCapacity += fldcap[il];
			avgWaterContent += water[1][il];
			avgFieldCapacity += fldcapw1;
		}
		avgWaterContent = avgWaterContent / layerDepth;
		avgFieldCapacity = avgFieldCapacity / layerDepth;

		if (year == 1 && lastFrost==0)
		{
			lastFrost = jday;

		}
		if (avgWaterContent <= (avgFieldCapacity) && precipitation < 0.002 && snow_pack < 0.001 && jday >= plantTime && (0.75 * max_temp + 0.25 * min_temp)>10.0 && jday>=(lastFrost-10))//last possible day is june 142 water[1][1] <= fldcapw1 * 0.9 && water[1][2] <= fldcapw2 * 0.9
		{
			autoPlantCount++;//if all above conditions are met then advance autoPlantCounter

		}

		if (jday >= 152)//was ==

		{
			autoPlantCount = 7;
		}
	}
	else//warm season flag.
	{

		if (year == 1 && lastFrost == 0)
		{
			lastFrost = jday;

		}
		int plantTime;
		if (year == 1)//first year set the plantTime accumulator to begin on day 105 -- currently redudant logic. Was testing variable plantdate starting times
		{
			plantTime = 115;//set a bit earlier than coolseason becauase the accumulator criteria below is more easily reached
		}
		else
		{
			if (lastFrost < 115) //lastfrost calculated in above function to track when last spring frost occured.
			{
				plantTime = lastFrost;//using previous years lastFrost to deterimine plantime
			}
			else
			{
				plantTime = lastFrost; //else plantTime is last year

			}
			//plantTime = 115;//set a bit earlier than coolseason becauase the accumulator criteria below is more easily reached
		}


		int layerDepth = 0.2 / h[1];//counts the number of layers in 20cm of soil profile since layer height is variable depending on texture
		float avgWaterContent = 0.0;//initialize to zero for avgWater Content
		float avgFieldCapacity = 0.0;//initialize to zero for avgFieldCapacity
		double wiltptw1;//water equivalent wilting point m water
		double fldcapw1;//water equivalent field capacity units m water
		double totalAvailableWater1;//available water content between wilt point and field cap. units m water

		for (int il = 1; il <= layerDepth; il++)//calculating agWater content soil moisture up to 20 cms
		{
			wiltptw1 = h[1] * sts[il] * wiltpt[il];//calculate wiltpointwater for determining available soil layer water.Soil  Layer1
			fldcapw1 = h[1] * sts[il] * fldcap[il];//calculate fieldpointwater for determining available soil layer water.Soil Layer1
			totalAvailableWater1 = fldcapw1 - wiltptw1;//determine maximum available water in layer1
			//avgWaterContent += day_wfps[il];
			//avgFieldCapacity += fldcap[il];
			avgWaterContent += water[1][il];
			avgFieldCapacity += fldcapw1;
		}
		avgWaterContent = avgWaterContent / layerDepth;
		avgFieldCapacity = avgFieldCapacity / layerDepth;


		if (autoPlantCount < 1)
		{
			autoPlantCount = 1;//acumulator for # of days to require to meet below conditions until planting can occur
		}

		if (air_temp >= 10.8 && jday > plantTime && precipitation <0.002 && snow_pack < 0.001 && avgWaterContent <= (avgFieldCapacity))//accumulator criteria for plantime based on airtmep precipitation and snowpack for trafficability
		{
			autoPlantCount++;
		}
		else
		{
			
		}
		if (jday == 152)// should be >= ???
		{
			autoPlantCount = 10;
		}

	}
	if (jdseed[1] > jday && jday > 100)//autoplant not working for multiple crops in the same year because of this logic. Need to make it more dynamic for multiple crops and years. Currently hard coded for crop 1 and day 100.
	{
		jdseed[1] = 100; autoPlantCount = 1;
	}
	if (autoPlantCount>=7)//if autoplant counting is at least 10 days  was // && jday>120
	{
		jdseed[1] = jday;//sets jdseed[1] for reporting.
		


		crop_flag[ccwc] = 1;
		maturity_flag[ccwc] = 0;
		WiltFlag[ccwc] = 0;

		read_in_vege(MODE, 1, ccwc);

		if (crop[ccwc] == 20 || crop[ccwc] == 64 || crop[ccwc] == 65) //irrigated paddy rice
		{
			wetland_flag = 1;
			IrriRice_flag = 1;
			RainfedRice_flag = 0;
			DeepRice_flag = 0;
			rice_maturity_flag = 0;
		}
		else if (crop[ccwc] == 46)//rainfed rice
		{
			wetland_flag = 1;
			IrriRice_flag = 0;
			RainfedRice_flag = 1;
			DeepRice_flag = 0;
		}
		else if (crop[ccwc] == 30)//deep-water rice
		{
			wetland_flag = 1;
			IrriRice_flag = 0;
			RainfedRice_flag = 0;
			DeepRice_flag = 1;
		}
		else
		{
			wetland_flag = 0;
			IrriRice_flag = 0;
			RainfedRice_flag = 0;
			DeepRice_flag = 0;
		}

		if (crop[ccwc] == 20 && Transplant[ccwc] == 1 && TDD[ccwc] == 0.0)//sets transplanting biomass
		{
			
			///reading in the set transplanting allocations
			CString TESTFILE;
			FILE* pFile = NULL;
			TESTFILE.Format("%s\\Library\\Lib_crop\\transplant.txt", ROOTDIR);//flowering
			pFile = fopen(TESTFILE, "r");
			if (pFile == NULL)
			{
				CString note;
				note.Format("Can not OPEN transplanting file %s", TESTFILE);
				AfxMessageBox(note);
				exit(0);

			}
			float transTDD1, transGrain1, transLeaf1, transStem1, transRoot1, transPlant1;//initializing temporary variables for transplanting crop1
			float transTDD2, transGrain2, transLeaf2, transStem2, transRoot2, transPlant2;//initializing temporary variables for transplanting crop2
			int transSeed1, transSeed2;
			char cjunk[200];
			fscanf(pFile, "%s %s %s %s %s %s %s", &cjunk, &cjunk, &cjunk, &cjunk, &cjunk, &cjunk, &cjunk);
			fscanf(pFile, "%f %f %f %f %f %f %d", &transTDD1, &transGrain1, &transLeaf1, &transStem1, &transRoot1, &transPlant1, &transSeed1);//&crop 1 parameters 
			fscanf(pFile, "%f %f %f %f %f %f %d", &transTDD2, &transGrain2, &transLeaf2, &transStem2, &transRoot2, &transPlant2, &transSeed2);//&crop 2 parameters
			fclose(pFile);



			if (ccwc == 1)
			{
				TDD[ccwc] = transTDD1;
				Grain_Wt[ccwc] = transGrain1;
				Leaf_Wt[ccwc] = transLeaf1;
				Stem_Wt[ccwc] = transStem1;
				Root_Wt[ccwc] = transRoot1;
				plantn[ccwc] = transPlant1;
				seed[ccwc] = transSeed1;
			}
			else if (ccwc == 2)
			{
				TDD[ccwc] = transTDD2;
				Grain_Wt[ccwc] = transGrain2;
				Leaf_Wt[ccwc] = transLeaf2;
				Stem_Wt[ccwc] = transStem2;
				Root_Wt[ccwc] = transRoot2;
				plantn[ccwc] = transPlant2;
				seed[ccwc] = transSeed2;


			}
			else
			{//old fixed code
				TDD[ccwc] = 100.0;
				Grain_Wt[ccwc] = 0.0;
				Leaf_Wt[ccwc] = 30.0;
				Stem_Wt[ccwc] = 30.0;
				Root_Wt[ccwc] = 20.0;
				plantn[ccwc] = 4.0;
				seed[ccwc] = 30;

			}
			

			//TDD[ccwc] = 100.0;
			//Grain_Wt[ccwc] = 0.0;
			//Leaf_Wt[ccwc] = 30.0;
			//Stem_Wt[ccwc] = 30.0;
			//Root_Wt[ccwc] = 20.0;
			//plantn[ccwc] = 4.0;
			//seed[ccwc] = 30;
		}
		else
		{
			//seed[ccwc] = 1;

			if (PerennialFlag[ccwc] == 0)//if not perrenial.
			{
				Grain_Wt[ccwc] = 0.0;
				Leaf_Wt[ccwc] = 0.0;
				Stem_Wt[ccwc] = 0.0;
				Pod_Wt[ccwc] = 0.0;
				Root_Wt[ccwc] = 0.0;
				GrainN[ccwc] = 0.0;
				LeafN[ccwc] = 0.0;
				StemN[ccwc] = 0.0;
				RootN[ccwc] = 0.0;
			}
		}

	}
}
void class_model::growth_stage(int ccwc)
{
    float lai1, lai2;
    float specific_leaf_weight; //kg C/ha

/*	if(crop[ccwc]==20&&Transplant[ccwc]==1&&TDD[ccwc]==0.0)
	{
		TDD[ccwc] = 100.0;
		Leaf_Wt[ccwc] = 30.0;
		Stem_Wt[ccwc] = 30.0;
		Root_Wt[ccwc] = 20.0;
		plantn[ccwc] = 40.0;
		seed[ccwc] = 30;

		//planting_flag = 1;
	}*/

    if (crop[ccwc]>0&&seed[ccwc]>GermDays[crop[ccwc]])//should I turn on a perrenial flag????
    {
		
		float T_limit, LLT;
		
		
		
		if (jday < 60) //don't count GDD before March 1st
		{
			perGDDSinceLastCut = 0.0;

		}
		if (air_temp > 5.0 && jday>60)//if air_temp higher than 5oC and after March 1st
		{
			consec5Days += 1;
			if (consec5Days > 4)
			{
				perGDDSinceLastCut += air_temp - 5.0;//count GDD for perennial growth cuts.
			}

			

		}
		else
		{
			if (consec5Days < 5) 
			{
				consec5Days = 0;
			}
		}
		if (crop[ccwc] == 2) //winter crops
			T_limit = WinterWheat_LimitiT; //WinterWheat_LimitiT;
		else T_limit = 0.0;

		if(LandUse==4) LLT = min_temp;//dry grassland
		else LLT = air_temp;

		if (crop[ccwc] == 2 && min_temp < 0.0) LLT = 0.0;

		//if(LLT>=0.0)
		if(LLT>=T_limit)
		{

			float RUEStress;
			RUEStress = pow(DayPETRs/25.0, 0.5);//tie in growth to RUE

			RUEStress = min(1.0, max(0.3, RUEStress));//maximum reducition in TDD gained = 0.5;
			if(crop[ccwc]!=2) RUEStress = 1.0;//turned off for now...N demand instead. 
			RUEStress = 1.0;
			if (crop[ccwc] == 2 && DayPETRs <= 5.5 && PGI[ccwc]<0.5 && PGI[ccwc]>0.01) //put a winter wheat control in so that low RUE doesn't trigger Accumulation of PGI
			{
				RUEStress = 0.05;//reduce phenology PGI advancement
				

				//delayed growth day accumulator for calculating HI stress on reducing yields. controllable by user parameterization. 
				if (PGI[ccwc] > 0.05) {
					cropRadAcc[ccwc] += 1.0;//Theo
				}
				

			}
			if (lightStressFactor[ccwc] < 1.0 && crop[ccwc] == 3  && PGI[ccwc]<0.25)
			{
				RUEStress = lightStressFactor[ccwc]*0.55;

			}
			day_TDD[ccwc] = LLT * RUEStress;
			
			if(crop[ccwc]==1&&PGI[ccwc]<0.28)//for corn we have growth rate set to surface temp up till PGI
			{
				if (temp[1] > 0.0)//if surface soil temp >0.0
				{
					day_TDD[ccwc] = temp[1];//set to surface soil temp
				}
				else
				{
					day_TDD[ccwc] = 0.0;
				}
			}
			else
			{
			day_TDD[ccwc] = LLT * RUEStress;
			}
			
		}
		else
		{
		  day_TDD[ccwc] = 0.0;
		  //TDD[ccwc] = 0.0;
		}
		if (crop[ccwc] == 2)
		{
			dayLength(jday, latitude);//sets dayLengthHr which is a calculation of daylenght based on latitude and time of year
			if (dayLengthHr > 14.0 && PGI[ccwc]<0.4 && day_TDD[ccwc]>0.0 && air_temp > 10.0)//a trigger for stem elongation based on daylight hours
			{
				day_TDD[ccwc] *= 2.0;
			}

		}


		if (crop[ccwc] == 3||crop[ccwc]==18)
		{
			//test for photoperiod ... need to use to adjust PGI gain and TDD[ccwc]
			dayLength(jday, latitude);//sets dayLengthHr which is a calculation of daylenght based on latitude and time of year
			photoPeriod(dayLengthHr, max_TDD[ccwc]);//sets photoPeriodIndex which is a calculation of soybean photoperiod sensitivity based on dayLengthHr;
			if (PGI[ccwc] < 0.10 || PGI[ccwc]>0.5) photoPeriodIndex = 1.0;//need to add soybean water stress in August?
			//photoPeriodIndex = 1.0;
			day_TDD[ccwc] *= pow(photoPeriodIndex,0.20);//Brian was 0.1
			if (seed[ccwc] == 10 && photoPeriodStress[ccwc]==0.0)
				{
				photoPeriodStress[ccwc] = photoPeriodIndex;
				}
			else if(seed[ccwc] > 10)
				{
				photoPeriodStress[ccwc] = photoPeriodIndex;
					//(photoPeriodStress[ccwc] * (seed[ccwc] - 1) / seed[ccwc]) + (photoPeriodIndex * 1 / seed[ccwc]);
				}
		}
		if (crop[ccwc] == 3||crop[ccwc]==18)
		{
			if (PGI[ccwc] < 0.5)
			{


				if (TDD[ccwc] < max_TDD[ccwc])
					TDD[ccwc] += day_TDD[ccwc];
			}
			else
			{
				if (TDD[ccwc] < max_TDD[ccwc])
					TDD[ccwc] += day_TDD[ccwc];//was testing an increase in day_TDD for reproductive phase
			}
		}
		else
		{
			if (TDD[ccwc] < max_TDD[ccwc])
				TDD[ccwc] += day_TDD[ccwc];//was testing an increase in day_TDD for reproductive phase
		}
		if(GrassFlag[ccwc]==1&&air_temp<=5.0) 
			PGI[ccwc] -= 0.1;
		else
		{
		
		OLDPGI[ccwc]=PGI[ccwc];
	
		PGI[ccwc] = TDD[ccwc] / max_TDD[ccwc];}//plant growth index

		PGI[ccwc] = max(0.0, min(1.0, PGI[ccwc]));


	

		/*
		if(PerennialFlag[ccwc]==1 && perRegrow[ccwc]==0 && crop_days[ccwc]==1 && vernal[ccwc]==1)
		{ 
		TDD[ccwc]=max_TDD[ccwc]*0.324;
		PGI[ccwc]=0.324;
		}
		*/
		//specific_leaf_weight = 1500.0;//2.0 * (1620.3 * PGI[ccwc] + 64.0);// kg C/ha per LAI

		//lai[ccwc] = (Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc]) / specific_leaf_weight * lai_index[ccwc];
    }
    else
    {
		//lai[ccwc] = 0.0;
		//lai[ccwc] = (Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc]) / specific_leaf_weight * lai_index[ccwc];
		day_TDD[ccwc] = 0.0;
		PGI[ccwc] = 0.0;
    }

	u_PGI = PGI[ccwc];

	//=============================================================================== testing a frostkill parameter
			/*
					if (CoverCrop[ccwc] == 1 && min_temp < FrostKill[ccwc])
					{
						float killCrop;
						killCrop = 0.15;
						winterKill[ccwc] *= killCrop;
					}
				*/	

}

void class_model::root_respir(int ccwc)
{

    float Tfactor, RootAge, age;
	int i;

    if (air_temp<= 0.0)
    {
       Tfactor = 0.0;
    }
    else
    {
       Tfactor = air_temp / 35.0;
    }

    if ( seed[ccwc] > 0 )
    {
		age=(float)seed[ccwc]/(float)grow_days[ccwc];
		if(age<0.0) age = 0.0;
	  
	  RootAge = -2.1091*age*age + 2.7486*age + 0.0614;
	  if(RootAge < 0.0) RootAge = 0.0;
    }
    else
    {
	  RootAge = 0.0;
    }

	if(wetland_flag==1)
	{
		float soilte = max(4.0, (float)st[1]); 
		float SoilD = 6.0 / soilte;
		float RootF;
		if(PGI[1]<0.5) RootF = PGI[1];
		else RootF = 1.0 - PGI[1];
		RootF = max(0.0, min(1.0, RootF));

		day_rco2[ccwc] = 0.1 * Root_Wt[ccwc] * RootF * Tfactor * SoilD;//0.1

	}
	else if(crop[ccwc]==30)
	{
		float SoilD = 6.0 / (float)st[1];
		
		day_rco2[ccwc] = 500.0 * RootAge * Tfactor * SoilD; 
	}
	else if(crop[ccwc]==11||crop[ccwc]==12||crop[ccwc]==10||crop[ccwc]==89)//grass
	{
		float AgeFactor;
		if(PGI[ccwc]<1.0) AgeFactor = -2.352*PGI[ccwc]*PGI[ccwc] + 1.645*PGI[ccwc] +0.7561;
		else AgeFactor = 0.1;
		if(AgeFactor<0.0) AgeFactor=0.0;

		float Tf;
		if(air_temp>0.0) Tf = air_temp/1.0;
		else Tf = 0.0;

		day_rco2[ccwc] = 0.2 * Root_Wt[ccwc] * Tfactor * AgeFactor * (float)(365-jday)/365.0;// + Tf;//0.1
	}
	else
	{

		float AgeFactor;
		if(PGI[ccwc]<1.0) AgeFactor = -2.8348*PGI[ccwc]*PGI[ccwc] + 2.4848*PGI[ccwc] + 0.4554;//1.0 + (1.0-PGI)/(1.0+PGI);
		else AgeFactor = 0.1;
		if(AgeFactor<0.0) AgeFactor=0.0;
		
		if(crop[ccwc]==2) 
		{
			Tfactor = (air_temp - 4.0) / 4.0;
			Tfactor = max(0.0, Tfactor);
		}
		else
		{
			if(PGI[ccwc]>0.4&&PGI[ccwc]<0.7) 
			{
				Tfactor = (air_temp - 10.0) / 6.0;
				Tfactor = max(0.0, Tfactor);
			}
		}

		day_rco2[ccwc] = 0.025 * Root_Wt[ccwc] * AgeFactor;//Tfactor;//0.025
	}

	if(LandUse==6)
	{
		day_rco2[ccwc] = 0.001 * Root_Wt[ccwc] * Tfactor;
	}
	
	/*for(int i15=1; i15<=q; i15++)
	{
		root_CO2[i15] = (day_rco2[1]+day_rco2[2]+day_rco2[3]) / (float)q;
	}*/

	//root exudation
	float TotalRootWT = Root_Wt[ccwc]; 
	
	if (TotalRootWT>0.0)//&&flood_flag==0)
	{
		 float bq = 0.3;
		 float fPGI = 1.0 / (PGI[ccwc]+0.001);

		 if(PerennialFlag[ccwc]==1) 
			 fPGI = 0.2;
		 else
		 {
			 if(u_PGI>0.5) 
			 {
				fPGI = 1.0 - u_PGI * 0.5;
				fPGI *= 0.25;//Modified for CA rice of Maegen case ???
			 }		
		 }

		//day_RootInput_DOC = TotalRootWT * bq * fPGI;//(kg C/ha/layer)
		float ddDOC = 0.001 * (1.0 + PGI[ccwc]) * TotalRootWT;//Deng JIa's ref. 0.11 * Day_C_growth[ccwc] + was 0.001

		
		//alternative to adding root DOC/exudate into the system. 
		//day_rco2[ccwc] = 0.0;
		
		
		if(ddDOC>0.0)
		{
			float AddC1, AddC2, AddC3, AddC, AddCN, dInertC;
			

			AddC = ddDOC;
			AddCN = rootcn[ccwc];
			alloc_litter_into_pools(&AddCN, &AddC, 1, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);
		

			int root_layer = round(root_depth[ccwc] / h[1]);
			if (root_layer < 2) root_layer = 2;//testing to see if root density distribution is more realistic with at least 2 layers.
			if (root_layer > q) root_layer = q;

			float totalRDensity;
			totalRDensity = 0.0;

			//new root C allocation based on Root Density to allocate across layers

			//test off

			
			for (int l = 1; l <= root_layer; l++)
			{
				
				rcvl[l] += AddC1 * rootDensity[ccwc][l];///problem with root density not equaling 1?
				rcl[l] += AddC2 * rootDensity[ccwc][l];
				rcr[l] += AddC3 * rootDensity[ccwc][l];
				inert_C[l] += day_inert_C * rootDensity[ccwc][l];
				
				/*
				float RRdoc = (ddDOC);// *rootDensity[ccwc][l]);
				doc[l] += RRdoc;
				root_doc[ccwc] += RRdoc;
				day_RootInput_DOC += RRdoc;
				*/
				
				//OrgP[l] += AddP * rootDensity[ccwc][l];
				totalRDensity += rootDensity[ccwc][l];

			}
			if (totalRDensity < 1.0)
			{
				float blah;
				blah = 1.0;
			}
			day_addC += (AddC1 + AddC2 + AddC3);
			yr_addrc += (AddC1 + AddC2 + AddC3);

			float AddToSoilN = day_addC / AddCN;
			day_addrn += AddToSoilN;
			yr_addrn += AddToSoilN;
			
			

					//root_doc[ccwc] += RRdoc;
				//	day_RootInput_DOC += RRdoc;
				AddC1 = 0.0;
				AddC2 = 0.0;
				AddC3 = 0.0;
				//AddP = 0.0;
		}

		

		//end alternative exudate addition
		
		   
		//Perrenial ROOT DOC addition --- root exudates?
		/*
		if(ddDOC>0.0)
		{
			int root_layer = round(root_length[ccwc] / h[1]);

			for(int i=1; i<=root_layer; i++)
			{
				//float RRdoc = (ddDOC / (float)q);
				float RRdoc = (ddDOC * rootDensity[ccwc][i]);
				doc[i] += RRdoc;
				root_doc[ccwc] += RRdoc;
				day_RootInput_DOC += RRdoc;
				//day_DOC_prod += RRdoc;
			}
		}
		*/

	}
	else
	{
	   
	}  
	
}

void class_model::water_demand(float DayPET, int ccwc)
{


//for(zcrops=1;zcrops<=CropNumbers;zcrops++)
//{

//	PPT[zcrops] = wreq[zcrops] * day_N_demand[zcrops] * plantcn[zcrops] * 2.5 / 1000.0 / 10000.0;//m water
	//PPT[ccwc] = (wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0);//+(wreq[ccwc] * plantn[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0) * 0.25;//m water


/*
	float leafTrans;
	leafTrans = DayPET * (1.0 - exp(-0.5 * lai[ccwc]));
	if (lai[ccwc] > 1)///was 0.3
	{
		PPT[ccwc] = leafTrans;
	}
	else
	{
		leafTrans = DayPETCROP[ccwc] * (1.0 - exp(-0.5 * 1));
		PPT[ccwc] = leafTrans;

		//PPT[ccwc] = (wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0); //maybe an alternative way for beginning phase.
	}
	*/
//}

	
//Brian insert crop coefficient here from FAO intrepretation.
//if(crop[ccwc]==6||crop[ccwc]==3||crop[ccwc]==9||crop[ccwc]==8||crop[ccwc]==1||crop[ccwc]==43||crop[ccwc]==6||crop[ccwc]==3||crop[ccwc]==9||crop[ccwc]==8||crop[ccwc]==1||crop[ccwc]==43)
//{		
int i;
	
//for(i=1;i<=IniCropNumbers;i++)

//yr_PET -= DayPET;//temporarily subtracting DayPET before adding it back below after recalculation.


DayPETCROP[ccwc]=DayPET;

		//set arrays with the 3 valus for Kc per crop type
		float LegumeKc[3]={0.65,1.00,0.70};//soybean was .4 1.15 .55 was 0.5,1.1,0.7 //preseason-ET {0.5,1.9,0.7}//{0.35,1.20,0.5} step 2
		float OilSeedKc[3]={0.65,1.15,0.65};//0.35,1.05,0.35//budong {0.85,2.45,0.85};
		float CerealKc[3]={0.65,1.05,0.85};//0.4,1.3,0.45//{0.6,1.6,0.45}//wheat was 0.4 1.15 0.4//Budong {0.85,2.45,0.85}; 
		float CornKc[3]={0.6,1.05,0.8};//0.3,1.15,0.6//{0.7,1.1,0.7}//0.6,1.0,0.6//corn was 0.5 1.05 0.5//budong {0.85,1.65,0.85};
		float ForageKc[3]={0.45,1.0,0.80};//0.4,0.95,0.9;//budong {1.5,1.90,1.5}
		float WWKc[3]={0.6,1.15,0.6};

   float kcini,kcmid,kcend,interval1,interval2,interval3;


if(crop[ccwc]==6)
{
interval1=0.1;
interval2=0.3;//.5
interval3=0.6;
}
else if(crop[ccwc]==1)
{
interval1=0.1;//0.1
interval2=0.3;//0.3
interval3=0.4;//0.4
}
else if(crop[ccwc]==3)
{
interval1=0.1;//0.1
interval2=0.42;//0.3
interval3=0.83;//0.4
}
else
{
interval1=0.1;
interval2=0.3;
interval3=0.6;
}

/*
   if(crop[ccwc]==10)
   {
   CString TESTFILE;
   FILE *pFile=NULL;
   TESTFILE.Format("%s\\Record\\kcValue.txt",OUTPUT);
   pFile=fopen(TESTFILE,"r");
   fscanf(pFile, "%f %f %f %f %f %f",&kcini,&kcmid,&kcend,&interval1,&interval2, &interval3);
   fclose(pFile);
   }
   LegumeKc[0]=kcini;
   LegumeKc[1]=kcmid;
   LegumeKc[2]=kcend;
*/

/*
if(crop[ccwc]==6)
{
interval1=0.1;
interval2=0.3;//.5
interval3=0.6;
}
else if(crop[ccwc]==1)
{
interval1=0.1;//0.1
interval2=0.3;//0.3
interval3=0.4;//0.4
}
else
{
interval1=0.1;
interval2=0.3;
interval3=0.6;
}
*/


		//test to see if PGI is less than crop development stage currently set to occur at PGI of 0.2 and use Table 12 Kcini (http://www.fao.org/docrep/x0490e/x0490e0b.htm)
		if(PGI[ccwc]==0.0||PGI[ccwc]>0.0 && PGI[ccwc]<=interval1)
		{		//test if cereal
				if(crop[ccwc]==6||crop[ccwc]==8||crop[ccwc]==9||crop[ccwc]==43)
				{
					DayPETCROP[ccwc]=DayPET*CerealKc[0];}
				else if(crop[ccwc]==1||crop[ccwc]==43)
				{
					DayPETCROP[ccwc]=DayPET*CornKc[0];}
				//test if oilseed
				else if(crop[ccwc]==25||crop[ccwc]==57)
				{DayPETCROP[ccwc]=DayPET*OilSeedKc[0];}
				//test if Legume
				else if(crop[ccwc]==3||crop[ccwc]==29)
				{DayPETCROP[ccwc]=DayPET*LegumeKc[0];}
				//test if Forage
				else if(crop[ccwc]==4||crop[ccwc]==5||crop[ccwc]==10||crop[ccwc]==11||crop[ccwc]==12||crop[ccwc]==89)
				{
					DayPETCROP[ccwc]=DayPET*ForageKc[0];}
				//test if ww
				else if(crop[ccwc]==2)
				{DayPETCROP[ccwc]=DayPET*WWKc[0];}

				else
				{DayPETCROP[ccwc]=DayPET*CerealKc[0];
				//DayPETCROP[ccwc]=DayPETCROP[ccwc];
				}
		}
		//test if PGI is in crop development stage. If so then calculate slope using Kcmid and Kcini  and solve Kc at PGI value
		else if(PGI[ccwc]>interval1 && PGI[ccwc]<=interval2)
		{float CKc,LKc,FKc,OKc,WKc,WinterKc;
			CKc=((CerealKc[1]-CerealKc[0])/(interval2 - interval1))*PGI[ccwc]+(CerealKc[1]-(CerealKc[1]-CerealKc[0])/(interval2 - interval1)*interval2);
			WKc=((CornKc[1]-CornKc[0])/(interval2 - interval1))*PGI[ccwc]+(CornKc[1]-(CornKc[1]-CornKc[0])/(interval2 - interval1)*interval2);
			LKc=((LegumeKc[1]-LegumeKc[0])/(interval2 - interval1))*PGI[ccwc]+(LegumeKc[1]-(LegumeKc[1]-LegumeKc[0])/(interval2 - interval1)*interval2);
			FKc=((ForageKc[1]-ForageKc[0])/(interval2 - interval1))*PGI[ccwc]+(ForageKc[1]-(ForageKc[1]-ForageKc[0])/(interval2 - interval1)*interval2);
			OKc=((OilSeedKc[1]-OilSeedKc[0])/(interval2 - interval1))*PGI[ccwc]+(OilSeedKc[1]-(OilSeedKc[1]-OilSeedKc[0])/(interval2 - interval1)*interval2);
            WinterKc=((WWKc[1]-WWKc[0])/(interval2 - interval1))*PGI[ccwc]+(WWKc[1]-(WWKc[1]-WWKc[0])/(interval2 - interval1)*interval2);
				if(crop[ccwc]==6||crop[ccwc]==8||crop[ccwc]==9||crop[ccwc]==43)
				{DayPETCROP[ccwc]=DayPET*CKc;}
				else if(crop[ccwc]==1||crop[ccwc]==43)
				{
					DayPETCROP[ccwc]=DayPET*WKc;}
				else if(crop[ccwc]==25||crop[ccwc]==57)
				{DayPETCROP[ccwc]=DayPET*OKc;}
				else if(crop[ccwc]==3||crop[ccwc]==29)
				{
					DayPETCROP[ccwc]=DayPET*LKc;}
				else if(crop[ccwc]==4||crop[ccwc]==5||crop[ccwc]==10||crop[ccwc]==11||crop[ccwc]==12||crop[ccwc]==89)
				{DayPETCROP[ccwc]=DayPET*FKc;}
				else if(crop[ccwc]==2)
				{DayPETCROP[ccwc]=DayPET*WinterKc;}
				else
				{DayPETCROP[ccwc]=DayPET*CKc;
				//DayPETCROP[ccwc]=DayPETCROP[ccwc];
				}
		}
		//test if PGI is in crop mid stage. If so then use Kcmid value
		else if(PGI[ccwc]>interval2 && PGI[ccwc]<=interval3)
		{
				if(crop[ccwc]==6||crop[ccwc]==8||crop[ccwc]==9||crop[ccwc]==43)
				{DayPETCROP[ccwc]=DayPET*CerealKc[1];}
			     else if(crop[ccwc]==1||crop[ccwc]==43)
				 {
					 DayPETCROP[ccwc]=DayPET*CornKc[1];}

				else if(crop[ccwc]==25||crop[ccwc]==57)
				{DayPETCROP[ccwc]=DayPET*OilSeedKc[1];}
				else if(crop[ccwc]==2)
				{DayPETCROP[ccwc]=DayPET*WWKc[1];}
				else if(crop[ccwc]==3||crop[ccwc]==29)
				{
					DayPETCROP[ccwc]=DayPET*LegumeKc[1];}
				else if(crop[ccwc]==4||crop[ccwc]==5||crop[ccwc]==10||crop[ccwc]==11||crop[ccwc]==12||crop[ccwc]==89)
				{DayPETCROP[ccwc]=DayPET*ForageKc[1];}
				else
				{DayPETCROP[ccwc]=DayPET*CerealKc[0];
				//DayPETCROP[ccwc]=DayPETCROP[ccwc];
				}
		}
		//test if PGI is in crop end stage. If so then calculate slope using Kcmid and Kcend and solve for Kc at PGI value
		else if(PGI[ccwc]>interval3 && PGI[ccwc]<=1.0)
		{float CKc,LKc,FKc,OKc,WKc,WinterKc;
			CKc=((CerealKc[2]-CerealKc[1])/(1.0 - interval3))*PGI[ccwc]+(CerealKc[2]-(CerealKc[2]-CerealKc[1])/(1.0 - interval3)*1.00);
			WKc=((CornKc[2]-CornKc[1])/(1.0 - interval3))*PGI[ccwc]+(CornKc[2]-(CornKc[2]-CornKc[1])/(1.0 - interval3)*1.00);
			LKc=((LegumeKc[2]-LegumeKc[1])/(1.0 - interval3))*PGI[ccwc]+(LegumeKc[2]-(LegumeKc[2]-LegumeKc[1])/(1.0 - interval3)*1.00);
			FKc=((ForageKc[2]-ForageKc[1])/(1.0 - interval3))*PGI[ccwc]+(ForageKc[2]-(ForageKc[2]-ForageKc[1])/(1.0 - interval3)*1.00);
			OKc=((OilSeedKc[2]-OilSeedKc[1])/(1.0 - interval3))*PGI[ccwc]+(OilSeedKc[2]-(OilSeedKc[2]-OilSeedKc[1])/(1.0 - interval3)*1.00);
			WinterKc=((WWKc[2]-WWKc[1])/(1.0 - interval3))*PGI[ccwc]+(WWKc[2]-(WWKc[2]-WWKc[1])/(1.0 - interval3)*1.00);
				if(crop[ccwc]==6||crop[ccwc]==8||crop[ccwc]==9||crop[ccwc]==43)
				{DayPETCROP[ccwc]=DayPET*CKc;}
				else if(crop[ccwc]==1||crop[ccwc]==43)
				{
					DayPETCROP[ccwc]=DayPET*WKc;}

				else if(crop[ccwc]==25||crop[ccwc]==57)
				{DayPETCROP[ccwc]=DayPET*OKc;}
				else if(crop[ccwc]==2)
				{DayPETCROP[ccwc]=DayPET*WinterKc;}
				else if(crop[ccwc]==3||crop[ccwc]==29)
				{
					DayPETCROP[ccwc]=DayPET*LKc;}
				else if(crop[ccwc]==4||crop[ccwc]==5||crop[ccwc]==10||crop[ccwc]==11||crop[ccwc]==12||crop[ccwc]==89)
				{DayPETCROP[ccwc]=DayPET*FKc;}
				else
				{
					DayPETCROP[ccwc]=DayPET*CKc;
				//DayPETCROP[ccwc]=DayPETCROP[ccwc];
				}
		}
		//in case PGI isn't defined use Kcini value for DayPETCROP[ccwc]
		else
				{
				if(crop[ccwc]==6||crop[ccwc]==8||crop[ccwc]==9||crop[ccwc]==43)
				{DayPETCROP[ccwc]=DayPET*CerealKc[0];}
				else if(crop[ccwc]==1||crop[ccwc]==43)
				{
					DayPETCROP[ccwc]=DayPET*CornKc[0];}
				else if(crop[ccwc]==25||crop[ccwc]==57)
				{DayPETCROP[ccwc]=DayPET*OilSeedKc[0];}
				else if(crop[ccwc]==2)
				{DayPETCROP[ccwc]=DayPET*WWKc[0];}
				else if(crop[ccwc]==3||crop[ccwc]==29)
				{DayPETCROP[ccwc]=DayPET*LegumeKc[0];}
				else if(crop[ccwc]==4||crop[ccwc]==5||crop[ccwc]==10||crop[ccwc]==11||crop[ccwc]==12||crop[ccwc]==89)
				{DayPETCROP[ccwc]=DayPET*ForageKc[0];}
				else
				{DayPETCROP[ccwc]=DayPET*CerealKc[0];
				//DayPETCROP[ccwc]=DayPETCROP[ccwc];
				}
				}

//}
	//End Crop coefficient code
	
	
	
	
	PPTactual[ccwc]=PPT[ccwc];//actual water req.


	float fractionTrans;
	fractionTrans=(DayPETCROP[ccwc]*(1.0 - exp(-0.70*(lai[ccwc]))))/DayPETCROP[ccwc];//calculates the proportion of potential transpiration relative to PET..Not used currently
	//fractionTrans = min(0.95,max(0.15,(Leaf_Wt[ccwc]/OptLeafC[ccwc])+0.4));

	
	
/*	
	// Outputting Stresses code
	if(year==1&&jday==1)
	{CString TESTFILE;
		FILE *pFile=NULL;

	
	TESTFILE.Format("%s\\Record\\PET.txt", OUTPUT);
	pFile = fopen (TESTFILE,"w");
	fprintf(pFile, "jday,year,crop,PPT[ccwc],DayPETCROP[ccwc],wreq[ccwc],day_N_demand[ccwc],plantcn[ccwc]\n");
	fprintf(pFile, "%1d,%1d,%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,year,ccwc,PPT[ccwc],DayPETCROP[ccwc],wreq[ccwc],day_N_demand[ccwc],plantcn[ccwc]);
	fclose (pFile);
	}
	else
	{
	CString TESTFILE;
	FILE *pFile=NULL;
	
	
	TESTFILE.Format("%s\\Record\\PET.txt", OUTPUT);//OUTPUTBatchFileName
	pFile = fopen (TESTFILE,"a");
	fprintf(pFile, "%1d,%1d,%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,year,ccwc,PPT[ccwc],DayPETCROP[ccwc],wreq[ccwc],day_N_demand[ccwc],plantcn[ccwc]);
	fclose (pFile);
	}		

*/















	
	//if (PPT[ccwc] > DayPETCROP[ccwc] * 0.95)
	//{
		//PPT[ccwc] = DayPETCROP[ccwc] * 0.95;
		
	//}
//	else
	//{
		//PPT[ccwc] = wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0;
		
	//PPT[ccwc] = wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0;///THIS MAKES BIOMASS TO TRANSPIRATION FIT  BUT PROBABLY BREAKS estimation of ET.
	

	//Optimum temperature adjusting wreq - Leon Hartwell Allen Jr. USDA 2014 Crop Responses to Elevated Carbon Dioxide.
	float adjustWreq, optWreq, adjFactor,minAirTemp;
	minAirTemp = max_temp;//max_temp
	if (max_temp < 20.0)minAirTemp = 20.0;//max_temp

	adjustWreq = 0.3938 * minAirTemp - 5.863;
	adjustWreq = min(15.0, max(2.0, adjustWreq));
	optWreq = 0.3938 * OptimumT[ccwc]-5.863;
	if (OptimumT[ccwc]<20)optWreq = 2.0;
	adjFactor = adjustWreq / optWreq;
	adjFactor = pow(adjFactor, 0.25);
	adjFactor = min(3.0, max(0.90, adjFactor));
	//adjFactor = 1.0;



	
	float leafTrans;
	leafTrans = DayPETCROP[ccwc] * (1.0 - exp(-0.5 * lai[ccwc])); //taken from response of crops to limited water : Ahuja et al.,  pg 65. KEP values (-0.5 * lai) can be 0.7-0.46 //DayPETCROP
		if (lai[ccwc] > 0.3)//&&PerennialFlag[ccwc]==0
		{
			PPT[ccwc] = leafTrans*pow((wreq[ccwc]*adjFactor) / 250, 1.0);// *pow(wreq[ccwc] / 100, 0.35);  //added wreq/100 to have more control on water req effects on transpiration ///probably needs to change to pow(wreq[ccwc]/100,0.35)
		}
		else
		{
			float laiSmall;
			laiSmall = 0.3;//minimum lai
			leafTrans = DayPETCROP[ccwc] * (1.0 - exp(-0.5 * laiSmall));//was 1//leafTrans = DayPETCROP[ccwc] * (1.0 - exp(-0.5 * laiSmall));
			PPT[ccwc] = leafTrans * pow((wreq[ccwc] * adjFactor) / 250, 1.0);//0.35
			//PPT[ccwc] = leafTrans;
		}
	


		//testing daily transpiration estimate vs biomass accumulation and LAI . Ideally need to rework the leaf growth to be in better sync with LAI.

		/*
		
		float totBiomass,totWreq;
		totBiomass = Leaf_Wt[ccwc] + Root_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc];
		totWreq = wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0;
		if (year == 1 && (jdseed[ccwc]+10) == jday)
		{
			CString TESTFILE;
			FILE* pFile = NULL;

			TESTFILE.Format("%s\\Record\\water.txt", OUTPUT);
			pFile = fopen(TESTFILE, "w");
			fprintf(pFile, "jday,year,PGI[ccwc], leafTrans,DayPETCROP[ccwc],PPT[ccwc],lai[ccwc],Biomass[WT],totWreq,leafWt\n");
			fprintf(pFile, "%1d,%1d,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f\n", jday, year,PGI[ccwc],leafTrans*1000,DayPETCROP[ccwc]*1000,PPT[ccwc]*1000,lai[ccwc],totBiomass,totWreq,Leaf_Wt[ccwc]);
			fclose(pFile);
			flagHeader = 0;
		}
		else
		{
			CString TESTFILE;
			FILE* pFile = NULL;


			TESTFILE.Format("%s\\Record\\water.txt", OUTPUT);//OUTPUTBatchFileName
			pFile = fopen(TESTFILE, "a");
			fprintf(pFile, "%1d,%1d,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f,%10.7f\n", jday, year, PGI[ccwc], leafTrans*1000, DayPETCROP[ccwc]*1000, PPT[ccwc]*1000,lai[ccwc],totBiomass,totWreq,Leaf_Wt[ccwc]);
			fclose(pFile);
		}
	*/	
		///PPT[ccwc] = (wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0) + (wreq[ccwc] * plantn[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0) * 0.25;//m water
	
	
//PPT[ccwc] = DayPETCROP[ccwc]*0.95;
	




//PPT[ccwc] = wreq[ccwc] * day_N_demand[ccwc] * plantcn[ccwc] * 2.5 / 1000.0 / 10000.0;///THIS MAKES BIOMASS TO TRANSPIRATION FIT  BUT PROBABLY BREAKS estimation of ET.
	yrPPT += PPT[ccwc];

//	yr_PET += DayPET;//adding in the newly calculated DayPET (subtracted above the routine)
/*
	float FPT; 
    if(plantn[ccwc]>0.0&&TDD[ccwc]<=max_TDD[ccwc])//&&crop_PT[ccwc]<=CropWaterDemand[ccwc])
	{
		PPT[ccwc] = CropWaterDemand[ccwc] * (day_TDD[ccwc] / max_TDD[ccwc]);

		if(PPT[ccwc]>DayPET) PPT[ccwc] = DayPET;
	}
	else
	{
		PPT[ccwc] = 0.0;
	}
*/
}

double class_model::crop_pretranspiration(int irri_close, double PPTw, int ccwc)
{
	int l, hr = 1;
	double Fptt, LayerWaterDemand, LayerTrans, limit1;
	double LayerH2Odemand = 0.0;
	const double epsRoot = 1e-12;

	if (year == 7 && jday == 129)
	{
		float blah;
		blah = 1.0;
	}

	int root_layer = round(root_length[ccwc] / h[1]);
	if (root_layer <= 2)
	{
		root_layer = 2;
		rootDensity[ccwc][1] = 0.5;
	    rootDensity[ccwc][2] = 0.5;
		
	}
	if (root_layer > q) root_layer = q;
	double cropAvailableWater, totalAvailableWater;//brian parameters added to see if soil water status can be added.
	double LayerCropWaterDeficit = 0.0;
	double prewater[25][250];
	int prenWTL,preWTL;
	prenWTL = nWTL;
	preWTL = WTL;
	float preWaterPool = WaterPool;
	memcpy(prewater, water, sizeof(prewater));

	//DayPT0: daily all crops demand for water, mm

	DayPT1 = 0.0;//daily water taken by crops from soil



	//1: crop get water from soil profile
	if (PPTw > 0.0 && snow_pack == 0.0)//total_ice==0.0
	{
		//root_layer = q; //this will allow all layers to contribute ... turning off for use with root density function
		LayerDeficit = 0.0;
		soilWaterStress = 0.0;
		float rootDensityTotal = 0.0;
		int root_layer_from_density = 0;

		for (int lz = 1; lz <= q; lz++)
		{
			//if (rootDensity[ccwc][lz] > 0.0)
			//	root_layer = lz;


			if (rootDensity[ccwc][lz] > epsRoot) root_layer_from_density = lz;
		}
		root_layer = max(root_layer, root_layer_from_density);

		//}
		if (crop[ccwc] == 2) root_layer = (int)(max_root_length[ccwc] / h[1]);
		for (l = 1; l <= root_layer; l++)//was q  root_layer
		{
			
			if (rootDensity[ccwc][l] < 0.0)rootDensity[ccwc][l] = 0.0;





			if (prenWTL > l)//water Table is below layer
			{

				if (PerennialFlag[ccwc] == 0 || PerennialFlag[ccwc] == 1)
				{
					rootDensityTotal += rootDensity[ccwc][l];
					//LayerH2Odemand = PPTw / (float)q;//* powf(0.5, l) ;//+ DayCropWaterDeficit
					LayerH2Odemand = (PPTw * rootDensity[ccwc][l]) + (LayerCropWaterDeficit * 0.995);//0.995);//+ LayerCropWaterDeficit;// + LayerCropWaterDeficit;//+ DayCropWaterDeficit;//* powf(0.5, l) ;//+ DayCropWaterDeficit //*0.995

				}
				else
				{
					LayerH2Odemand = PPTw / (float)q;// evenly divided water requirement per layer if perrenial //+ DayCropWaterDeficit;//* powf(0.5, l) ;//+ DayCropWaterDeficit
				}



				double wiltptw = h[l] * sts[l] * wiltpt[l];
				double fldcapw = h[l] * sts[l] * fldcap[l];


				totalAvailableWater = fldcapw - wiltptw;


				if (FilmEffect > 0.0) wiltptw *= (1.0 - FilmEffect);

				if (prewater[1][l] <= wiltptw)
				{
					LayerTrans = 0.0;
					LayerCropWaterDeficit = LayerH2Odemand;
				}
				else
				{
					double Firri = 1.0;

					

					double Fptt;
					if (DrainEfficiency == 1)
					{
						//CF_water[ccwc][l] = 1.0;//Theo
						Fptt = Firri * (prewater[1][l] - wiltptw) *CF_water[ccwc][l];
					}//no water table


					else
					{
						double restrictionWT;
						restrictionWT = 1 + (1 - SwcWTEffect);
						//CF_water[ccwc][l] = 1.0;////Theo
						Fptt = Firri * pow((prewater[1][l] - wiltptw), restrictionWT)*CF_water[ccwc][l];//1.65 default
					 
					}//water table

					Fptt = max(0.0, Fptt);

					if (Fptt >= LayerH2Odemand)
					{
						LayerTrans = LayerH2Odemand;
						LayerH2Odemand = 0.0;
					//	DayCropWaterDeficit = 0.0;
						LayerCropWaterDeficit = 0.0;
					}
					else
					{
						LayerTrans = Fptt;
					//	DayCropWaterDeficit = LayerH2Odemand - Fptt;
						LayerCropWaterDeficit = LayerH2Odemand - Fptt;
					}


					


					prewater[1][l] -= LayerTrans;



					if (prewater[1][l] < 0.0)
					{
						LayerTrans += prewater[1][l];
						prewater[1][l] = 0.0;
					}
				}

				DayPT1 += LayerTrans;
				LayerTrans = 0.0;

			}//end if(WTL>l)

			else//if Water Table is in current layer
			{

				LayerH2Odemand = (PPTw - DayPT1);//LayerDemand is equal to potential transpiration - actual transpiration + deficit
				LayerH2Odemand = max(0.0, LayerH2Odemand);

				if (LayerH2Odemand > 0)
				{

					if (day_WT > 0.0 && crop[ccwc] == 200)
					{
						LayerTrans = LayerH2Odemand;
						LayerH2Odemand = 0.0;
						DayPT1 += LayerTrans;
						LayerTrans = 0.0;
					}
					else//all other crops
					{
						double wiltptw = h[l] * sts[l] * wiltpt[l];
						double fldcapw = h[l] * sts[l] * fldcap[l];

						totalAvailableWater = fldcapw - wiltptw;


						if (FilmEffect > 0.0) wiltptw *= (1.0 - FilmEffect);

						if (prewater[1][l] <= wiltptw)//if water in layer is less than wilting point water then don't do any transpiration. Should never be case since WTL is in layer
						{
							LayerTrans = 0.0;//trans for this layer is zero
							LayerCropWaterDeficit = LayerH2Odemand; //layerCropWaterDeficit is set to whatever the demand was.
							prenWTL += 1;
							preWTL += 1;

						}
						else
						{
							double Firri = 1.0;
							//CF_water[ccwc][l] = 1.0;//Theo
							double Fptt = Firri * (prewater[1][l] - fldcapw) *CF_water[ccwc][l];//wiltptw drain to field capacity
							Fptt = max(0.0, Fptt);

							if (Fptt >= LayerH2Odemand)
							{
								LayerTrans = LayerH2Odemand;
								LayerH2Odemand = 0.0;
								//	DayCropWaterDeficit = 0.0;
								LayerCropWaterDeficit = 0.0;
							}
							else if (prewater[1][l] >= wiltptw)//(root_layer == l)
							{
								double Fptta;//water above field capacity and water above wilting point
								//CF_water[ccwc][l] = 1.0;////Theo
								Fptta = (prewater[1][l] - wiltptw)*CF_water[ccwc][l];

								if (Fptta >= LayerH2Odemand)
								{
									LayerTrans = LayerH2Odemand;
									LayerH2Odemand = 0.0;
									//	DayCropWaterDeficit = 0.0;
									LayerCropWaterDeficit = 0.0;
								}
								else
								{
									LayerTrans = Fptta;
									//	DayCropWaterDeficit = LayerH2Odemand - Fptt;
									LayerCropWaterDeficit = LayerH2Odemand - Fptt;
								}

							}
							else
							{
								LayerTrans = Fptt;
								//	DayCropWaterDeficit = LayerH2Odemand - Fptt;
								LayerCropWaterDeficit = LayerH2Odemand - Fptt;

							}

							/*
							else
							{
								LayerTrans = Fptt;
							//	DayCropWaterDeficit = LayerH2Odemand - Fptt;
								LayerCropWaterDeficit = LayerH2Odemand - Fptt;
							}
							*/





							prewater[1][l] -= LayerTrans;
							if (prewater[1][l] <= fldcapw && prenWTL == l)
							{
								prenWTL += 1;
								preWTL += 1;

							}


							if (prewater[1][l] < 0.0)
							{
								LayerTrans += prewater[1][l];
								prewater[1][l] = 0.0;
							}
						}

						DayPT1 += LayerTrans;
						LayerTrans = 0.0;

					}//for rice
				}
				LayerTrans = 0.0;
			}//end else if(WTL<l)

		}//end of layer loop

		//soilWaterStress=soilWaterStress/root_layer; //calculate soil Water Stress

//seeing if remaining water in layers can meet demand.









	}//end of PPTw>0.0 loop


	///////////crop get water from deep water pool --- PPTw1 water still required from PPTw (water demand - soil water uptaken DayPT1)
	float PPTw1 = (PPTw - DayPT1);
	if (PPTw1 < 0) PPTw1 = 0.0;

	DayPT2 = 0.0;//daily water taken by crops from deep water pool - DayPT2- deep water pool transpiration


	if (PPTw1 > 0.)//&&root_layer==q 0&&WaterPool>0.00001
	{
		float add_water2 = 0.0;



		

		//li code

		if (PPTw1 <= preWaterPool)
		{
			add_water2 = PPTw1;
			preWaterPool -= add_water2;

			//DayPTdef = 0.0;
		}
		else
		{

			add_water2 = preWaterPool;
			preWaterPool = 0.0;
			//WaterPool-=add_water2;
			//DayPTdef -= add_water2;
		}

		//End li code
		//WaterPool -= add_water2;
		DayPT2 = add_water2;//m water
		add_water2 = 0.0;
	}

	//////crop get water from irrigation water/////////////////////////////////////////// PPTw2 (irrigation water demand after remaining deamnd from after soil trans (PPTw1)   and deep water pool trans (DayPT2)  )
	float PPTw2 = PPTw1 - DayPT2;
	DayPT3 = 0.0;//actual daily water taken by crops from irrigation water (DayPT3)//Deficiet soil watter difference between potential demand and actual available water.

	if (PPTw2 > 0.0 && irri_index > 0.0)//index-irrigation
	{
		DayPT3 = PPTw2 * irri_index;

		if (irri_close == 0 && RainfedRice_flag == 0)
		{
			if (IrriMethod == 0)//furrow irrigation
			{
				IrriWater = (5.0 * DayPT3); // irrigates 5 times the amount of water necessary to meet the transpiration demand of irrigation water
			//	TTT += 0.1 * IrriWater / 0.005;
			//	WaterPool+=IrriWater;
			}
			else if (IrriMethod == 1)//sprinkler
			{
				IrriWater = (4.0 * DayPT3);
				//	TTT += 0.05 * IrriWater / 0.005;
			}
			else if (IrriMethod == 2)//surface dripping
			{
				IrriWater = (3.0 * DayPT3);
				//	TTT += 0.05 * IrriWater / 0.005;
			}
			else if (IrriMethod == 3)//deep dripping
			{
				IrriWater = (2.0 * DayPT3);
			}
			else if (IrriMethod == 4)//film mulch
			{
				IrriWater = (1.0 * DayPT3);
			}

			//yr_irri += IrriWater + DayPT3;
			//day_irri += IrriWater + DayPT3;




			//DayPT3=0.0;
		}
		if (PPTw2 > 0.0 && IrriWater > 0.0)
		{
			/*
			if(IrriWater>DayPT3)
			{
				float AxcessH2O = IrriWater - DayPT3;
				if(IrriMethod==0||IrriMethod==1||IrriMethod==2)
					prewater[1][1] += AxcessH2O;
				else
					prewater[1][8] += AxcessH2O;
			}
			*/
		}
	}

	if (irri_index == 0.0 && IrriWater > 0.0)//event irrigation
	{
		float Accessibility[5] = { 0.15, 0.5, 0.75, 1.0, 1.0 };
		float AccessibleH2O = Accessibility[IrriMethod] * IrriWater;

		if (AccessibleH2O >= PPTw2)
			DayPT3 = PPTw2;
		else
			DayPT3 = AccessibleH2O;

		DayPT3 = 0.0;

		//IrriWater-=DayPT3;

		
	}

	float TotalDayPT = DayPT1 + DayPT2 + DayPT3;

	if (PPTw > TotalDayPT)
	{
		//DayCropWaterDeficit = PPTw - TotalDayPT;// m water
		PPTw = 0.0;
	}


	return(TotalDayPT);
}



double class_model::crop_transpiration(int irri_close, double PPTw, int ccwc)
{
	int l, hr=1;
	double Fptt, LayerWaterDemand, LayerTrans, limit1;
	double LayerH2Odemand = 0.0;
	int root_layer = round(root_length[ccwc]/h[1]);
	const double epsRoot = 1e-12;
	if (root_layer <= 2) 
	{
			root_layer = 2;
			rootDensity[ccwc][1] = 0.5;
			rootDensity[ccwc][2] = 0.5;

		

	}
	if(root_layer>q) root_layer = q;
	
		double cropAvailableWater,totalAvailableWater;//brian parameters added to see if soil water status can be added.
	double LayerCropWaterDeficit=0.0;
		//DayPT0: daily all crops demand for water, mm
	
	DayPT1 = 0.0;//daily water taken by crops from soil
	

	
	//1: crop get water from soil profile
	if(PPTw>0.0 && snow_pack==0.0)//total_ice==0.0
	{
		//root_layer = q; //this will allow all layers to contribute ... turning off for use with root density function
		LayerDeficit = 0.0;		
      soilWaterStress=0.0;
float rootDensityTotal=0.0;
int root_layer_from_density = 0;
for(int lz=1; lz<=q;lz++)
{
	//if(rootDensity[ccwc][lz]>0.0)
		//root_layer=lz;
	
	

		if (rootDensity[ccwc][lz] > epsRoot) root_layer_from_density = lz;
	}
	root_layer = max(root_layer, root_layer_from_density);

	

//}
if (crop[ccwc] == 2 ) root_layer = (int)(max_root_length[ccwc] / h[1]);

		for (l=1; l<=root_layer; l++)//was q  root_layer
		{
			if(rootDensity[ccwc][1]<=0.0)rootDensity[ccwc][1]=1.0;
			if(rootDensity[ccwc][l]<0.0)rootDensity[ccwc][l]=0.0;


			
			if (year == 15)
			{
				float blah;
				blah =1.0;


			}

			if(nWTL>l)//water Table is below layer
			{
				
				if(PerennialFlag[ccwc]==0 ||PerennialFlag[ccwc]==1)
				{
					rootDensityTotal+=rootDensity[ccwc][l];
					//LayerH2Odemand = PPTw / (float)q;//* powf(0.5, l) ;//+ DayCropWaterDeficit
					LayerH2Odemand = (PPTw * rootDensity[ccwc][l]) + (LayerCropWaterDeficit * 0.995);// 0.995);//+ LayerCropWaterDeficit;// + LayerCropWaterDeficit;//+ DayCropWaterDeficit;//* powf(0.5, l) ;//+ DayCropWaterDeficit //*0.995
				
				}
				else
				{
				LayerH2Odemand = PPTw / (float)q;// evenly divided water requirement per layer if perrenial //+ DayCropWaterDeficit;//* powf(0.5, l) ;//+ DayCropWaterDeficit
				}



				double wiltptw = h[l] * sts[l] * wiltpt[l];
				double fldcapw = h[l] * sts[l] * fldcap[l];

			
				totalAvailableWater=fldcapw-wiltptw;
			

				if(FilmEffect>0.0) wiltptw *= (1.0 - FilmEffect);

				if(water[1][l]<=wiltptw)
				{
					LayerTrans = 0.0;
					LayerCropWaterDeficit=LayerH2Odemand;
				}
				else
				{
					double Firri=1.0;
			
					//float Fptt = Firri * (water[1][l] - wiltptw);//old way introducing a reduction in water requirement
				//	float Fptt = Firri * pow((water[1][l] - wiltptw),1.65);
				
					double Fptt;
					if (DrainEfficiency == 1)
					{
						//CF_water[ccwc][l] = 1.0;////Theo
						Fptt = Firri * (water[1][l] - wiltptw) *CF_water[ccwc][l];
					}//no water table
					
					
					else
					{
						double restrictionWT;
						restrictionWT=1+(1-SwcWTEffect);
						//CF_water[ccwc][l] = 1.0;////Theo
						Fptt = Firri * pow((water[1][l] - wiltptw), restrictionWT) *CF_water[ccwc][l];//1.65 default
					 //Fptt= Firri * (water[1][l] - wiltptw);
					}//water table

					Fptt=max(0.0,Fptt);

					if(Fptt>=LayerH2Odemand)
					{
						LayerTrans = LayerH2Odemand;
						LayerH2Odemand = 0.0;	
						DayCropWaterDeficit = 0.0;
						LayerCropWaterDeficit=0.0;
					}
					else
					{
						LayerTrans = Fptt;
						DayCropWaterDeficit = LayerH2Odemand - Fptt;
						LayerCropWaterDeficit=LayerH2Odemand - Fptt;
					}


	/*
				//brian trying to see if can get soil water status playing a role in determing water uptake capacity.
				cropAvailableWater=water[1][l]-wiltptw;
				if(cropAvailableWater<0)
					cropAvailableWater=0.0;
				soilWaterStress=cropAvailableWater/totalAvailableWater;
					LayerTrans=LayerTrans*pow(soilWaterStress,1.0);
				//end brian
	*/


					water[1][l] -= LayerTrans;

			
				
					if(water[1][l]<0.0)
					{
						LayerTrans += water[1][l];
						water[1][l] = 0.0;
					}
					}

				DayPT1 += LayerTrans;
				LayerTrans = 0.0;
			
				}//end if(WTL>l)

			else//if Water Table is in current layer
			{
				
					LayerH2Odemand = (PPTw-DayPT1);//LayerDemand is equal to potential transpiration - actual transpiration + deficit
					LayerH2Odemand = max(0.0, LayerH2Odemand);
				


					if (LayerH2Odemand > 0)
					{
						if (day_WT > 0.0 && crop[ccwc] == 200)
						{
							LayerTrans = LayerH2Odemand;
							LayerH2Odemand = 0.0;
							DayPT1 += LayerTrans;
							LayerTrans = 0.0;
						}
						else//all other crops
						{
							double wiltptw = h[l] * sts[l] * wiltpt[l];
							double fldcapw = h[l] * sts[l] * fldcap[l];

							totalAvailableWater = fldcapw - wiltptw;


							if (FilmEffect > 0.0) wiltptw *= (1.0 - FilmEffect);

							if (water[1][l] <= wiltptw)//if water in layer is less than wilting point water then don't do any transpiration. Should never be case since WTL is in layer
							{
								LayerTrans = 0.0;//trans for this layer is zero
								LayerCropWaterDeficit = LayerH2Odemand; //layerCropWaterDeficit is set to whatever the demand was.
								nWTL += 1;
								WTL += 1;
								day_WT = -WTL * h[1];
							}
							else
							{
								double Firri = 1.0;
								//CF_water[ccwc][l] = 1.0;////Theo
								double Fptt = Firri * (water[1][l] - fldcapw)*CF_water[ccwc][l];//wiltptw drain to field capacity
								Fptt = max(0.0, Fptt);

								if (Fptt >= LayerH2Odemand)//if water above field capacity then Fptt
								{
									LayerTrans = LayerH2Odemand;
									LayerH2Odemand = 0.0;
									DayCropWaterDeficit = 0.0;
									LayerCropWaterDeficit = 0.0;
								}
								else if (water[1][l] >= wiltptw)
								{
									double Fptta;//water above field capacity and water above wilting point
									//CF_water[ccwc][l] = 1.0;////Theo
									Fptta = (water[1][l] - wiltptw) *CF_water[ccwc][l];

									if (Fptta >= LayerH2Odemand)
									{
										LayerTrans = LayerH2Odemand;
										LayerH2Odemand = 0.0;
										DayCropWaterDeficit = 0.0;
										LayerCropWaterDeficit = 0.0;
									}
									else
									{
										LayerTrans = Fptta;
										DayCropWaterDeficit = LayerH2Odemand - Fptt;
										LayerCropWaterDeficit = LayerH2Odemand - Fptt;
									}

								}
								else
								{

									LayerTrans = Fptt;
									DayCropWaterDeficit = LayerH2Odemand - Fptt;
									LayerCropWaterDeficit = LayerH2Odemand - Fptt;

								}



								/*
											//brian trying to see if can get soil water status playing a role in determing water uptake capacity.
											cropAvailableWater=water[1][l]-wiltptw;
											if(cropAvailableWater<0)
												cropAvailableWater=0.0;
											soilWaterStress=cropAvailableWater/totalAvailableWater;
												LayerTrans=LayerTrans*pow(soilWaterStress,1.0);
											//end brian
								*/


								water[1][l] -= LayerTrans;
								if (water[1][l] <= fldcapw && nWTL == l)
								{
									nWTL += 1;
									WTL += 1;
									day_WT = -WTL * h[1];
								}


								if (water[1][l] < 0.0)
								{
									LayerTrans += water[1][l];
									water[1][l] = 0.0;
								}
							}

							DayPT1 += LayerTrans;
							LayerTrans = 0.0;
						}
					}
					LayerTrans = 0.0;

			}//end else if(WTL<l)
			
		}//end of layer loop

		//soilWaterStress=soilWaterStress/root_layer; //calculate soil Water Stress

//seeing if remaining water in layers can meet demand.









	}//end of PPTw>0.0 loop

	
	///////////crop get water from deep water pool --- PPTw1 water still required from PPTw (water demand - soil water uptaken DayPT1)
	float PPTw1 = (PPTw - DayPT1);
	if(PPTw1<0) PPTw1=0.0;

	DayPT2 = 0.0;//daily water taken by crops from deep water pool - DayPT2- deep water pool transpiration

	
	if(PPTw1>0.)//&&root_layer==q 0&&WaterPool>0.00001
	{
		float add_water2=0.0;



		//Brian Code

		/*
		float cropRootWPFactor;

		if(crop[ccwc]==1||crop[ccwc]==43)
		{
			cropRootWPFactor=0.55;
		}
		else if(crop[ccwc]==10)
		{cropRootWPFactor=0.75;
		}
		else
		{cropRootWPFactor=0.25;
		}

			if(WaterPool>WaterPoolMax*cropRootWPFactor)
			{

					if(PPTw1<=(WaterPool-WaterPoolMax*cropRootWPFactor))
					{
						add_water2 = PPTw1;
						WaterPool-=add_water2;

						//DayPTdef = 0.0;
					}
					else
					{
						
						add_water2 = (WaterPool-WaterPoolMax*cropRootWPFactor);
						WaterPool=WaterPoolMax*cropRootWPFactor;
						//DayPTdef -= add_water2;
					}

			}
		*/	

//li code
		
		if(PPTw1<=WaterPool)
		{
			add_water2 = PPTw1;
			WaterPool-=add_water2;

			//DayPTdef = 0.0;
		}
		else
		{
			
			add_water2 = WaterPool;
			WaterPool=0.0;
			//WaterPool-=add_water2;
			//DayPTdef -= add_water2;
		}

		//End li code
		//WaterPool -= add_water2;
		DayPT2 = add_water2;//m water
		add_water2 = 0.0;		
	}

	//////crop get water from irrigation water/////////////////////////////////////////// PPTw2 (irrigation water demand after remaining deamnd from after soil trans (PPTw1)   and deep water pool trans (DayPT2)  )
	float PPTw2 = PPTw1 - DayPT2;
	DayPT3 = 0.0;//actual daily water taken by crops from irrigation water (DayPT3)

	if(PPTw2>0.0&&irri_index>0.0)//index-irrigation
	{
			DayPT3 = PPTw2 * irri_index;

			if(irri_close==0&&RainfedRice_flag==0) 
			{
				if(IrriMethod==0)//furrow irrigation
				{
					IrriWater = (5.0 * DayPT3); // irrigates 5 times the amount of water necessary to meet the transpiration demand of irrigation water
				//	TTT += 0.1 * IrriWater / 0.005;
				//	WaterPool+=IrriWater;
				}
				else if(IrriMethod==1)//sprinkler
				{
					IrriWater = (4.0 * DayPT3);
				//	TTT += 0.05 * IrriWater / 0.005;
				}
				else if(IrriMethod==2)//surface dripping
				{
					IrriWater = (3.0 * DayPT3);
				//	TTT += 0.05 * IrriWater / 0.005;
				}
				else if(IrriMethod==3)//deep dripping
				{
					IrriWater = (2.0 * DayPT3);
				}
				else if(IrriMethod==4)//film mulch
				{
					IrriWater = (1.0 * DayPT3);
				}

				yr_irri += IrriWater+DayPT3;
				day_irri += IrriWater+DayPT3;
				
				

				
				//DayPT3=0.0;
			}
			if(PPTw2>0.0 && IrriWater>0.0)
			{

				float blah;
				blah = 1.0;

				/*
				if(IrriWater>DayPT3)
				{
					float AxcessH2O = IrriWater - DayPT3;
					if(IrriMethod==0||IrriMethod==1||IrriMethod==2)
						water[1][1] += AxcessH2O;
					else
						water[1][8] += AxcessH2O;				
				}
				*/
			}
	}
			
	if(irri_index==0.0&&IrriWater>0.0)//event irrigation
	{
		float Accessibility[5] = {0.15, 0.5, 0.75, 1.0, 1.0};
		float AccessibleH2O = Accessibility[IrriMethod] * IrriWater;

		if(AccessibleH2O>=PPTw2) 
			DayPT3 = PPTw2;
		else
			DayPT3 = AccessibleH2O;

		DayPT3=0.0;
		
		//IrriWater-=DayPT3;

		/*	
		if(IrriWater>DayPT3)
		{
			float AxcessH2O = IrriWater - DayPT3;
			if(IrriMethod==0||IrriMethod==1||IrriMethod==2)
				water[1][1] += AxcessH2O;
				//surf_water += AxcessH2O-DayPT3;
				
		    else
				
				water[1][8] += AxcessH2O;
			//	surf_water += AxcessH2O-DayPT3;
		}
		*/
	}

	float TotalDayPT = DayPT1 + DayPT2 + DayPT3;
			
	if(PPTw>TotalDayPT) 
	{
		DayCropWaterDeficit = PPTw - TotalDayPT;// m water
		PPTw = 0.0;	
	}


	return(TotalDayPT);
}

void class_model::root_develop(int ccwc)
{

	//adopted from Yang et al., 2009 Journal of Hydrology "An easily implemented agro-hyrdological procedure..."
	float minRootGrowthTemp,rootGrowthRate,OptTempRootGrowth;
	minRootGrowthTemp=5.0;//minimum root growth temperature
	rootGrowthRate=0.006;//growth rate in metre /Day degree C
	OptTempRootGrowth=OptimumT[ccwc];//optimum root growth temperature set to optimum temperature
	root_depth[ccwc]=min((root_depth[ccwc]+min(OptTempRootGrowth,max(0,(air_temp-minRootGrowthTemp)))*rootGrowthRate),max_root_length[ccwc]);//simple function of root Depth a function of Optimum temperature, air temperature and minRootGrowth Temp.
	//root_depth[ccwc]=0.5;
	root_q = (int)round((root_depth[ccwc]/h[1]));//+1
	root_length[ccwc] = root_depth[ccwc];

/*

	//li root growth
	if(jday==1&&(crop[1]==11||crop[1]==12)) 
		root_depth[ccwc] = 0.2;
	else
		root_depth[ccwc] = 0.05 + PGI[ccwc] * 0.5;//m

	root_q = (int)(root_depth[ccwc]/h[1])+1;//????
//end root growth
*/
}

void class_model::root_density(int ccwc)
{
	int layerD; //Keeps track of layer number
//	int shapeDensity;//This should eventually be set to be a function of crop type and soil texture. Clay textured soils 8 and sandy soils a 1. 
if(shapeDensity<1)
{shapeDensity=1;}
//	shapeDensity=5;//This shape density effects the exponential curve of rooting density with depth. Should be shifted from 1 to 8. At 8 it has a more exponential fit vs 1 where its more linear. 
	float layerDepth;//This is the depth of layer in m
	float sumLayerPart;//sum up the total layerPart
	sumLayerPart=0.0;//An accumulator for keeping track of the total relative fractions of root density that is used to solve the absolute fractions.
//adopted from Yang et al., 2009 Journal of Hydrology "An easily implemented agro-hyrdological procedure..."
	for(layerD=1;layerD<=q;layerD++)
	{
		layerDepth=(h[1]*layerD);	
		if(layerDepth>(root_depth[ccwc]*1.0))//determines if roots extend to the current depth. If not then root density at that layer is equal to zero
		{rootDensity[ccwc][layerD]=0.0;}
		else
		{
			if(layerDepth<root_depth[ccwc])
			{
			float blah;
			blah=RootShape[ccwc];
			rootDensity[ccwc][layerD]=exp(-RootShape[ccwc]*layerDepth);//shapeDensity
			}
			else
			{
				rootDensity[ccwc][layerD]=exp(-RootShape[ccwc]*layerDepth)*(1-(layerDepth-root_depth[ccwc])/(0.3*root_depth[ccwc]));

			}
		}
	


	}

	for(layerD=1;layerD<=q;layerD++)
	{
	sumLayerPart+=rootDensity[ccwc][layerD];//summing up layers to come up with the appropraite total for determing absolute root frationcs
	}
	for(layerD=1;layerD<=q;layerD++)
	{
		if(sumLayerPart==0.0)sumLayerPart=1.0;
	rootDensity[ccwc][layerD]=rootDensity[ccwc][layerD]/sumLayerPart; //root density being set from relative fraction to absolute fracitons.
	}
	
}
void class_model::weather_damage(int damage, float w_event, int ccwc)
{
	float Fdamage = w_event;
	//float CropNLost;
	Fdamage = max(0.0, min(1.0, Fdamage));

	//float hail_damage_N = 0.0;

	//for(int i=1; i<=CropNumbers; i++)
	//{
		//CropNLost = plantn[i] * Fdamage;
		//hail_damage_N += CropNLost;
		//plantn[i] -= CropNLost;

		Root_Wt[ccwc] *= (1.0 - Fdamage);
		Grain_Wt[ccwc] *= (1.0 - Fdamage);
		Leaf_Wt[ccwc] *= (1.0 - Fdamage);
		Stem_Wt[ccwc] *= (1.0 - Fdamage);
		plantn[ccwc] *= (1.0 - Fdamage);
		//PlantTakeN[i] *= (1.0 - Fdamage);
		//maxmn[i] *= (1.0 - Fdamage);
	//}
}

void class_model::frost_damage(int ccwc)
{
	float FiD;

	//for(ccwc=1; ccwc<=CropNumbers; ccwc++)
	{
		if(crop[ccwc]!=2&&PGI[ccwc]<0.5)//not winter wheat
		{
			FiD = 1.0 + 0.08 * min_temp;
			if(FiD<0.0) FiD=0.0;

			Root_Wt[ccwc] *= FiD;
			Grain_Wt[ccwc] *= FiD;
			Leaf_Wt[ccwc] *= FiD;
			Stem_Wt[ccwc] *= FiD;
			plantn[ccwc] *= FiD;
			PlantTakeN[ccwc] *= FiD;
		}
	}
}

void class_model::nh3_uptake_release(float *lai, float *day_soil_nh3, float *PlantTakeN, float *maxmn,
									 float leaf_water, float cropht, float base_nh3,
									 float *day_N_demand2, float *day_nup, float *day_fixN, float *day_DWater,
									 float *day_plant_nh3, float *yr_NH3_deposit, int ccwc)
{
    float max_leaf_water;
	float fpn, flm, vg, vca, x;

    if (lai[ccwc] > 0.0 )
    {
		max_leaf_water = lai[ccwc] * .0002;

	    fpn = 1.0 - PlantTakeN[ccwc] / maxmn[ccwc];
	    if ( fpn < 0.0 ) fpn = 0.0;
	    flm = 1.0;//leaf_water / max_leaf_water + 0.5;
	    if ( flm > 1.0 ) flm = 1.0;
	    vg = fpn * flm;//0.05
	    vca = 0.3 * 10000.0;//cropht * 10000.0;
	    //x = ((*day_soil_nh3 * powf(10.0, 9.0) / vca * lai[ccwc] / (lai[ccwc] + 10.0) * .01));
		x = ((0.1 * powf(10.0, 9.0) / vca * lai[ccwc] / (lai[ccwc] + 10.0) * .01));
	    if (x < 0.0) x = 0.0;
		//if(x>1.0)
		//	air_nh3 = base_nh3 * powf(x, 0.5);//0.5
		//else
		//	air_nh3 = base_nh3;

		//air_nh3 = base_nh3;

		float dD=0.0, pP=0.0;
		if(maxmn[ccwc]>plantn[ccwc])
		{
			//float dD = 1.0 * day_N_demand[ccwc] - day_nup[ccwc] - day_fixN[ccwc];
			dD = 0.1 * day_N_demand2[ccwc];// - day_nup[ccwc] - day_fixN[ccwc];
			pP = vg * base_nh3 * lai[ccwc] * day_DWater[ccwc];// 0.864 *
		}

		if(N_stress[ccwc]<1.0&&day_N_demand2[ccwc]>0.0) //dD>0.0)
		{
			//day_plant_nh3[ccwc] = 0.0;
			//if(dD>pP) day_plant_nh3[ccwc] = 0.9 * pP;//N uptake from atmospheric NH3 by crop
			//else day_plant_nh3[ccwc] = 0.9 * dD;

			dD = 1.0 * (1.0 - N_stress[ccwc]) / (1.0 + N_stress[ccwc]) * base_nh3 / (1.0 + base_nh3);//kg N/ha/day
			day_plant_nh3[ccwc] = dD;
		}
		else
			day_plant_nh3[ccwc] = 0.0;
    }
    else
    {
	    day_plant_nh3[ccwc] = 0.0;

    }

	crop_NH3_absorp[ccwc] += day_plant_nh3[ccwc];
	*yr_NH3_deposit += day_plant_nh3[ccwc];
}
void class_model::crop_Leafsenescence(int ccwc)
{

	float dPG = 0.0, dPL, dPW, dPR, sLeaf = 0.0, sStem = 0.0, sGrain = 0.0, sRoot = 0.0,sPod=0.0;
	float AddC, AddN, AddCN, dInertC, AddP;
	float AddC1, AddC2, AddC3;

	float leafPGIFactor;//make sure this is in sync with LAI equation at beginning of crop.cpp to control leaves. 

	leafPGIFactor = 7.6094 * pow(PGI[ccwc], 3) - 21.942 * pow(PGI[ccwc], 2) + 17.7 * PGI[ccwc] - 3.3559;
	leafPGIFactor = -5.3498 * pow(PGI[ccwc], 2) + 6.2833 * PGI[ccwc] - 0.8419;
	if (PGI[ccwc] < 0.75) leafPGIFactor = 1.0;
	leafPGIFactor = min(1.0, max(leafPGIFactor, 0.0));

	//sLeaf = LeafN[ccwc] * (1-leafPGIFactor)/5;
	sLeaf = LeafN[ccwc] * (0.048);
	sStem = StemN[ccwc] * (0.012);//was 0.015
	//sPod = PodN[ccwc] * 0.05;
	float currentLeafCN, currentStemCN;
	currentLeafCN = Leaf_Wt[ccwc] / LeafN[ccwc];
	currentStemCN = Stem_Wt[ccwc] / StemN[ccwc];
	if (sLeaf > 0.0 && PGI[ccwc] >= 0.75|| sStem > 0.0 && PGI[ccwc] >= 0.75)//test to see if the reduction factor is greater than zero
	{
		if (sLeaf > LeafN[ccwc]){sLeaf = LeafN[ccwc];}
		
		float senesGrainF = 0.30;//how much N is being translocated into crop during senescence
		//remove the senesence part of Leaf
		LeafN[ccwc] -= sLeaf ;//remove 100% of the sensensce N 
		Leaf_Wt[ccwc] -= sLeaf * currentLeafCN;
		StemN[ccwc] -= sStem;
		Stem_Wt[ccwc] -= sStem * currentStemCN;


		float updateLeafCN, updateStemCN;
		

		// recalculated current Leaf/STem CN
		updateLeafCN = Leaf_Wt[ccwc] / LeafN[ccwc];
		updateStemCN= Stem_Wt[ccwc] / StemN[ccwc];

		
		if (maturity_flag[ccwc] <= 1)
		{
			GrainN[ccwc] += sLeaf* senesGrainF;//25% of the N is going to grain
			GrainN[ccwc] += sStem* senesGrainF;//stem portion
			//StemN[ccwc] += sLeaf / 2;
		}
		if (maturity_flag[ccwc] == 1)senesGrainF = 0.0;

		//something is broken here between plantn[ccwc] and leafn[ccwc].      
		//plantn[ccwc] = LeafN[ccwc] + StemN[ccwc] + RootN[ccwc] + GrainN[ccwc] + PodN[ccwc];
		//if (plantn[ccwc] < 0.0) plantn[ccwc] = 0.0;
		//plantn[ccwc] = LeafN[ccwc] + StemN[ccwc] + RootN[ccwc] + GrainN[ccwc]; 
		//if(plantn[ccwc]<0.0) plantn[ccwc] = 0.0;

		//Leaf_Wt[ccwc] = LeafN[ccwc] * leafcn[ccwc];
		//Stem_Wt[ccwc] = StemN[ccwc] * stemcn[ccwc];
		//Grain_Wt[ccwc] = GrainN[ccwc] * graincn[ccwc];




		//Leaf_Wt[ccwc] = LeafN[ccwc] * currentLeafCN;//derives the Leaf C
		//Stem_Wt[ccwc] = StemN[ccwc] * currentStemCN;//derives the Stem C
		Grain_Wt[ccwc] = GrainN[ccwc] * graincn[ccwc];

		//plantP[ccwc] = CropP[ccwc] * 0.01 * (Leaf_Wt[ccwc]+Stem_Wt[ccwc]+Root_Wt[ccwc]+Grain_Wt[ccwc]) / 0.4;
		//calculates the senscence for each fraction for incorporation.
		DayLeafSenes[ccwc] = sLeaf * Leaf_Wt[ccwc]/LeafN[ccwc];//leafcn[ccwc]
		DayLeafSenesN[ccwc] += sLeaf * (1.0 - senesGrainF);

		DayStemSenes[ccwc] = sStem * Stem_Wt[ccwc] / StemN[ccwc];
		DayStemSenesN[ccwc] += sStem * (1.0 - senesGrainF);
		//DayGrainSenes[ccwc] = sGrain * graincn[ccwc];

		//ABOVE-GROUND litter incorporation
		//if (maturity_flag[ccwc] == 1)
		//{
			AddN = sLeaf*(1.0-senesGrainF)+sStem * (1.0 - senesGrainF);
			AddC = DayLeafSenes[ccwc]+DayStemSenes[ccwc];
			AddCN = AddC / AddN;
			AddP = plantP[ccwc] * 0.01 * AddC / 0.4;



			alloc_litter_into_pools(&AddCN, &AddC, 1, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);

			//float OutN = AddC1/rcnrvl + AddC2/rcnrl + AddC3/rcnrr;

			rcvl[1] += AddC1;
			rcl[1] += AddC2;
			rcr[1] += AddC3;
			OrgP[1] += AddP;

			day_addC += (AddC1 + AddC2 + AddC3);
			day_addrn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);
			yr_addtc += (AddC1 + AddC2 + AddC3);
			yr_addtn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);

			AddC1 = 0.0;
			AddC2 = 0.0;
			AddC3 = 0.0;
			AddP = 0.0;
			sGrain = 0.0;
			sLeaf = 0.0;
		
		//}

	}

}
void class_model::crop_senescence(int ccwc)
{
	//All the litter from senescence will be incorporated in the soil
	float dPG=0.0, dPL, dPW, dPR, sLeaf=0.0, sStem=0.0, sGrain=0.0, sRoot=0.0;
	float AddC, AddN, AddCN, dInertC, AddP;
	float AddC1, AddC2, AddC3;

	if(LandUse==6)//trees
	{
		if(jday>200)
		{
			dPG = 0.05;
			dPL = 0.001;
			dPW = 0.0005 * TreeCurretAge[ccwc];
			dPR = 0.00015;

			if(Leaf_Wt[ccwc]>TreeLeafMin[ccwc])
			{
				sLeaf = Leaf_Wt[ccwc] * dPL;
				Leaf_Wt[ccwc] -= sLeaf;
			}

			sGrain = Grain_Wt[ccwc] * dPG;							
			Grain_Wt[ccwc] -= sGrain;
			
			sStem = Stem_Wt[ccwc] * dPW * 0.015;
			Stem_Wt[ccwc] -= sStem;

			sRoot = Root_Wt[ccwc] * dPR;
			Root_Wt[ccwc] -= sRoot;	
		}	
		else
		{
				sGrain = 0.0;
				sLeaf = 0.0;
				sStem = 0.0;
				sRoot = 0.0;

				DayLeafSenes[ccwc]=0.0;
				DayStemSenes[ccwc]=0.0;
				DayRootSenes[ccwc]=0.0;
				DayGrainSenes[ccwc]=0.0;
		}
	}
	else if(PerennialFlag[ccwc]==1 && maturity_flag[ccwc]==1)//&&maturity_flag[ccwc]==1
	{
		float rootSensN;
		//if(PGI[ccwc]>0.8)//||plantn[ccwc]>maxmn[ccwc])//maturity_flag[ccwc]==1)
		{
			//TDD[ccwc] = 0.0;

			dPG = 0.00001 * (0.2 + PGI[ccwc]);

			sLeaf = LeafN[ccwc] * dPG;
			sStem = StemN[ccwc] * dPG;
			sRoot = RootN[ccwc] * dPG * 1.0;//was .1
			if(GrainN[ccwc]<0)
			{GrainN[ccwc]=0;
			}
			sGrain = GrainN[ccwc] * dPG;

			if(sGrain+sLeaf+sStem+sRoot>0.0)//test to see if the reduction factor is greater than zero
			{
				
				if(air_temp<-2)
					{
					sLeaf=LeafN[ccwc]*1;
					sStem=StemN[ccwc]*1;
					sGrain=GrainN[ccwc]*1;
					sRoot=RootN[ccwc]*.05;
					}
					

				LeafN[ccwc] -= sLeaf;
				StemN[ccwc] -= sStem;
				RootN[ccwc] -= sRoot;
				GrainN[ccwc] -= sGrain;	
				plantn[ccwc] = LeafN[ccwc] + StemN[ccwc] + RootN[ccwc] + GrainN[ccwc]+PodN[ccwc]; 
				if(plantn[ccwc]<0.0) plantn[ccwc] = 0.0;
				
				Leaf_Wt[ccwc] = LeafN[ccwc] * leafcn[ccwc];
				Stem_Wt[ccwc] = StemN[ccwc] * stemcn[ccwc];
				Root_Wt[ccwc] = RootN[ccwc] * rootcn[ccwc];
				Grain_Wt[ccwc] = GrainN[ccwc] * graincn[ccwc];				
				
				//plantP[ccwc] = CropP[ccwc] * 0.01 * (Leaf_Wt[ccwc]+Stem_Wt[ccwc]+Root_Wt[ccwc]+Grain_Wt[ccwc]) / 0.4;
				//calculates the senscence for each fraction for incorporation.
				DayLeafSenes[ccwc] = sLeaf * leafcn[ccwc];
				DayStemSenes[ccwc] = sStem * stemcn[ccwc];
				DayRootSenes[ccwc] = sRoot * rootcn[ccwc];//report DayRootSenesence C
				DayGrainSenes[ccwc] = sGrain * rootcn[ccwc];

				//ABOVE-GROUND litter incorporation
				AddN = sLeaf + sStem + sGrain;//adding root to above ground litter for now. Should be in soil. 
				AddC = DayLeafSenes[ccwc] + DayStemSenes[ccwc] + DayGrainSenes[ccwc]; 
				AddCN = AddC/AddN;
				AddP = plantP[ccwc] * 0.01 * AddC /0.4;

				if(sRoot>0)yr_uptaken[ccwc] -= sRoot;//remove rootN senensence from uptake balance since it gets returned to soil.
				

				alloc_litter_into_pools(&AddCN, &AddC, 1, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);

				//float OutN = AddC1/rcnrvl + AddC2/rcnrl + AddC3/rcnrr;

				rcvl[1] += AddC1;
				rcl[1] += AddC2;
				rcr[1] += AddC3;
				OrgP[1] += AddP;

				day_addC += (AddC1 + AddC2 + AddC3);
				day_addrn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);
				yr_addtc += (AddC1 + AddC2 + AddC3);
				yr_addtn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);

				AddC1 = 0.0;
				AddC2 = 0.0;
				AddC3 = 0.0;
				AddP = 0.0;		
				sGrain = 0.0;
				sLeaf = 0.0;
				sStem = 0.0;
			}				
		
			//Root litter incorporation
			if(sRoot>0.0)
			{
				AddCN = rootcn[ccwc];
				for (int l = 1; l <= q; l++ )
				{
					if ( l >= 1 && l <= 3 )
					{
						AddC = DayRootSenes[ccwc] * 0.5 / 3.0;//50% of root C applied to top three layers
						AddP = plantP[ccwc] * 0.01 /0.4 * sRoot * 0.5 / 3.0;
					}
					if ( l >= 4 && l <= 6 )
					{
						AddC = DayRootSenes[ccwc] * 0.4 / 3.0;//40% of root C applied to 4 - 6 layers
						AddP = plantP[ccwc] * 0.01 /0.4 * sRoot * 0.4 / 3.0;
					}
					if ( l >= 7 && l <= q )
					{
						AddC = DayRootSenes[ccwc] * 0.1 / (float)(q - 6);//10% of root C applied to  layers 7 to bottom
						AddP = plantP[ccwc] * 0.01 /0.4 * sRoot * 0.1 / (float)(q - 6);
					}

					alloc_litter_into_pools(&AddCN, &AddC, 10, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);//should add N to pools.
					rcvl[l] += AddC1;
					rcl[l] += AddC2;
					rcr[l] += AddC3;
					OrgP[l] += AddP;
								
					float AddToSoilN = sRoot/AddCN;

					day_addC += (AddC1+AddC2+AddC3);
					yr_addrc += (AddC1+AddC2+AddC3);
					day_addrn += AddToSoilN;
					yr_addrn += AddToSoilN;
					yr_addrp += AddP;

					sRoot = 0.0;
					AddC1 = 0.0;
					AddC2 = 0.0;
					AddC3 = 0.0;
					AddP = 0.0;
				}

			}
		}
	}
	else //annual crops
	{
		


			dPG = 0.006;//was 0.006
			if (crop[ccwc] == 47) dPG = 0.002;

			sLeaf = LeafN[ccwc] * dPG;
			sStem = StemN[ccwc] * dPG;
		    sRoot = RootN[ccwc] * dPG;//was .1
			if (crop[ccwc] == 47)
				sGrain = GrainN[ccwc] * dPG;
			
			if(GrainN[ccwc]<0)
			{GrainN[ccwc]=0;
			}
			sGrain = 0.0;//GrainN[ccwc] * dPG;

			if(sGrain+sLeaf+sStem+sRoot>0.0)//test to see if the reduction factor is greater than zero
			{
				/*
				if(air_temp<-2)
					{
					sLeaf=LeafN[ccwc]*1;
					sStem=StemN[ccwc]*1;
					sGrain=GrainN[ccwc]*1;
					sRoot=RootN[ccwc]*.05;
					}
				*/	
				
				LeafN[ccwc] -= sLeaf;
				StemN[ccwc] -= sStem;
				RootN[ccwc] -= sRoot;
				if (crop[ccwc] == 47) GrainN[ccwc] -= sGrain;
				if(maturity_flag[ccwc]<=1)
				{
				//	GrainN[ccwc] += sLeaf+sStem+sRoot;
				}

				//something is broken here between plantn[ccwc] and leafn[ccwc].      
				
				//plantn[ccwc] = LeafN[ccwc] + StemN[ccwc] + RootN[ccwc] + GrainN[ccwc]; 
				//if(plantn[ccwc]<0.0) plantn[ccwc] = 0.0;
				
				Leaf_Wt[ccwc] = LeafN[ccwc] * leafcn[ccwc];
				Stem_Wt[ccwc] = StemN[ccwc] * stemcn[ccwc];
				Root_Wt[ccwc] = RootN[ccwc] * rootcn[ccwc];
				Grain_Wt[ccwc] = GrainN[ccwc] * graincn[ccwc];				
				
				//plantP[ccwc] = CropP[ccwc] * 0.01 * (Leaf_Wt[ccwc]+Stem_Wt[ccwc]+Root_Wt[ccwc]+Grain_Wt[ccwc]) / 0.4;
				//calculates the senscence for each fraction for incorporation.
				DayLeafSenes[ccwc] = sLeaf * leafcn[ccwc];
				DayStemSenes[ccwc] = sStem * stemcn[ccwc];
				DayRootSenes[ccwc] = sRoot * rootcn[ccwc];
				DayGrainSenes[ccwc] = sGrain * graincn[ccwc];

				//ABOVE-GROUND litter incorporation
				if(maturity_flag[ccwc]==1)
				{
				AddN = sLeaf + sStem + sGrain;
				AddC = DayLeafSenes[ccwc] + DayStemSenes[ccwc] + DayGrainSenes[ccwc]; 
				AddCN = AddC/AddN;
				AddP = plantP[ccwc] * 0.01 * AddC /0.4;

			

				alloc_litter_into_pools(&AddCN, &AddC, 1, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);

				//float OutN = AddC1/rcnrvl + AddC2/rcnrl + AddC3/rcnrr;

				rcvl[1] += AddC1;
				rcl[1] += AddC2;
				rcr[1] += AddC3;
				OrgP[1] += AddP;

				day_addC += (AddC1 + AddC2 + AddC3);
				day_addrn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);
				yr_addtc += (AddC1 + AddC2 + AddC3);
				yr_addtn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);

				AddC1 = 0.0;
				AddC2 = 0.0;
				AddC3 = 0.0;
				AddP = 0.0;		
				sGrain = 0.0;
				sLeaf = 0.0;
				sStem = 0.0;
				}
			}				
		
			//Root litter incorporation
			if(sRoot>0.0 && maturity_flag[ccwc]==1)
			{
				AddCN = rootcn[ccwc];
				for (int l = 1; l <= q; l++ )
				{
					if ( l >= 1 && l <= 3 )
					{
						AddC = DayRootSenes[ccwc] * 0.5 / 3.0;
						AddP = plantP[ccwc] * 0.01 /0.4 * sRoot * 0.5 / 3.0;
					}
					if ( l >= 4 && l <= 6 )
					{
						AddC = DayRootSenes[ccwc] * 0.4 / 3.0;
						AddP = plantP[ccwc] * 0.01 /0.4 * sRoot * 0.4 / 3.0;
					}
					if ( l >= 7 && l <= q )
					{
						AddC = DayRootSenes[ccwc] * 0.1 / (float)(q - 6);
						AddP = plantP[ccwc] * 0.01 /0.4 * sRoot * 0.1 / (float)(q - 6);
					}

					alloc_litter_into_pools(&AddCN, &AddC, 10, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);
					rcvl[l] += AddC1;
					rcl[l] += AddC2;
					rcr[l] += AddC3;
					OrgP[l] += AddP;
								
					float AddToSoilN = sRoot/AddCN;

					day_addC += (AddC1+AddC2+AddC3);
					yr_addrc += (AddC1+AddC2+AddC3);
					day_addrn += AddToSoilN;
					yr_addrn += AddToSoilN;
					yr_addrp += AddP;

					sRoot = 0.0;
					AddC1 = 0.0;
					AddC2 = 0.0;
					AddC3 = 0.0;
					AddP = 0.0;
				}

			}
}//annual crops end




	


// was turned off
	/*
float TPN = Leaf_Wt[ccwc]/leafcn[ccwc] + Stem_Wt[ccwc]/stemcn[ccwc] + Root_Wt[ccwc]/rootcn[ccwc] + Grain_Wt[ccwc]/graincn[ccwc];

	if(TPN>0.0)
	{
		LeafN[ccwc] = (Leaf_Wt[ccwc]/leafcn[ccwc]) / TPN * plantn[ccwc];
		StemN[ccwc] = (Stem_Wt[ccwc]/stemcn[ccwc]) / TPN * plantn[ccwc];
		RootN[ccwc] = (Root_Wt[ccwc]/rootcn[ccwc]) / TPN * plantn[ccwc];
		GrainN[ccwc] = (Grain_Wt[ccwc]/graincn[ccwc]) / TPN * plantn[ccwc];
	}

	plantn[ccwc] = LeafN[ccwc] + StemN[ccwc] + RootN[ccwc] + GrainN[ccwc]; 
	plantP[ccwc] = LeafP[ccwc] + StemP[ccwc] + RootP[ccwc] + GrainP[ccwc]; 

	DayLeafSenes[ccwc]=sLeaf;
	DayStemSenes[ccwc]=sStem;
	DayRootSenes[ccwc]=sRoot;
	DayGrainSenes[ccwc]=sGrain;

	if(sGrain+sLeaf+sStem+sRoot>0.0)
	{	
		AddN = sLeaf/leafcn[ccwc] + sStem/stemcn[ccwc] + sRoot/rootcn[ccwc] + sGrain/graincn[ccwc];

		plantn[ccwc] -= AddN;
		if(plantn[ccwc]<0.0) plantn[ccwc] = 0.0;	

		// Add dead shoot in stable
		AddC = sLeaf+sStem+sGrain; 
		AddCN = leafcn[ccwc];//AddC / AddN;?
		AddP = plantP[ccwc] * 0.01 * AddC /0.4;
	//	AddP = CropP[ccwc] * 0.01 * AddC /0.4;

		float AddC1, AddC2, AddC3;
		
		alloc_litter_into_pools(&AddCN, &AddC, 1, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);

		float OutN = AddC1/rcnrvl + AddC2/rcnrl + AddC3/rcnrr;

		rcvl[1] += AddC1;
		rcl[1] += AddC2;
		rcr[1] += AddC3;
		OrgP[1] += AddP;

		day_addC += (AddC1 + AddC2 + AddC3);
		day_addrn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);
		yr_addtc += (AddC1 + AddC2 + AddC3);
		yr_addtn += (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr);

		AddC1 = 0.0;
		AddC2 = 0.0;
		AddC3 = 0.0;
		AddP = 0.0;

		//root litter incorporation
		AddCN = rootcn[ccwc];
		for (int l = 1; l <= q; l++ )
		{
			if ( l >= 1 && l <= 3 )
			{
				AddC = sRoot * 0.5 / 3.0;
				AddP = RootP[ccwc] * 0.01 * sRoot * 0.5 / 3.0 /0.4;
				//AddP = CropP[ccwc] * 0.01 /0.4 * sRoot * 0.5 / 3.0;
			}
			if ( l >= 4 && l <= 6 )
			{
				AddC = sRoot * 0.4 / 3.0;
				AddP = RootP[ccwc] * 0.01 * sRoot * 0.5 / 3.0 /0.4;
			//	AddP = CropP[ccwc] * 0.01 /0.4 * sRoot * 0.4 / 3.0;
			}
			if ( l >= 7 && l <= q )
			{
				AddC = sRoot * 0.1 / (float)(q - 6);
				AddP = RootP[ccwc] * 0.01 * sRoot * 0.5 / 3.0 /0.4;
			//	AddP = CropP[ccwc] * 0.01 /0.4 * sRoot * 0.1 / (float)(q - 6);
			}

			alloc_litter_into_pools(&AddCN, &AddC, 10, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);
			rcvl[l] += AddC1;
			rcl[l] += AddC2;
			rcr[l] += AddC3;
			OrgP[l] += AddP;
			AddC1 = 0.0;
			AddC2 = 0.0;
			AddC3 = 0.0;
			AddP = 0.0;
		}

		float AddToSoilC, AddToSoilN;
		AddToSoilC = sRoot;
		AddToSoilN = sRoot/AddCN;

		day_addC += AddToSoilC;
		yr_addrc += AddToSoilC;
		day_addrn += AddToSoilN;
		yr_addrn += AddToSoilN;

		sRoot = 0.0;

	}

	PresentBiomass[ccwc] = Root_Wt[ccwc] + Grain_Wt[ccwc] + Leaf_Wt[ccwc] + Stem_Wt[ccwc];

//was turned off
*/

}

void class_model::crop_rejuvenation(int ccwc)
{
	
}
void class_model::dayLength(int jday, float latitude)//, float dayLengthHr
{
	float angleDEC,decDeg,decRAD,latRAD,daylength;
	angleDEC = (360 * jday / 365) * PI /180;
	decDeg = 0.39637 - 22.9133 * cos(angleDEC) + 4.02543 * sin(angleDEC) - 0.3872 * cos(2 * angleDEC) + 0.052 * sin(2 * angleDEC);
	decRAD = (decDeg * PI / 180);
	latRAD = (latitude * PI) / 180;
	dayLengthHr = 0.133 * ((acos(-tan(latRAD) * tan(decRAD)))*180)/ PI;
	
	
	


}
void class_model::photoPeriod(float dayLengthHr, float max_TDD)//,float photoPeriodIndex
{
	float mX, b;

	mX = -0.00020035 * max_TDD + 0.22398934;// -0.000233373 * max_TDD + 0.28658333;
	b = 0.00274211 * max_TDD - 1.94102285;// 0.0032 * max_TDD - 2.8; 
	photoPeriodIndex = mX * dayLengthHr + b;
	photoPeriodIndex = min(1.0, max(0.0, photoPeriodIndex));

}

void class_model::water_CompFactor()
{
	//int ccwc;
	int root_layer_CF = 1; // deepest root layer in the mixture (initialized to 1)
	int deepest_crop = 1; // index is = 1 by default
	bool growflag = 0; // growflag = 0 if none of the crops are currently growing (i.e. don't go into loop, save time) 

	// Loop to determine whether to initialize CF_water to 0 or to actually compute CF_water
	for (int ccwcb = 1; ccwcb <= CropNumbers; ccwcb++)
	{
		if (crop_flag[ccwcb] == 1) // if at least one crop is currently growing, go ahead and calculate CF_water 
		{
			growflag = 1;
		}
	}

	if (growflag == 0) // if nothing is currently growing, initialize all CF_water[ccwc][lz] = 0 
	{
		for (int ccwcb = 1; ccwcb <= CropNumbers; ccwcb++)
		{
			for (int lz = 1; lz <= q; lz++)
			{
				CF_water[ccwcb][lz] = 0.0;
			}
		}
	}


	else if (growflag == 1) // if at least one crop is growing, go into CF_water calculation loop
	{
		// First we need to find which crop currently has the deepest root, to set the number of soil layers to compute the CFs for (i.e. down to q_max)
		for (int ccwcb = 1; ccwcb <= CropNumbers; ccwcb++)
		{
			
			int root_layer_crop = round(root_length[ccwcb] / h[1]);

			if(root_length[ccwcb]>0.0 && root_layer_crop<2)
			{
				root_layer_crop = 2;
				rootDensity[ccwcb][1] = 0.5;
				rootDensity[ccwcb][2] = 0.5;

			}

			if (root_layer_crop >= root_layer_CF)
			{
				root_layer_CF = root_layer_crop; // set the deepest root layer in the mixture
				deepest_crop = ccwcb; // save index of the crop with the deepest root
			}
		}

		// Make sure the deepest root layer corresponds to that where the deepest crop still has root density (otherwise we may be going too deep with CF_water)
		for (int lz = 1; lz <= q; lz++)
		{
			if (rootDensity[deepest_crop][lz] > 0.0)
				root_layer_CF = lz;

		}
		
		

		// Loop through each layer individually (down to the deepest root layer, as determined previously) 
		for (int lz = 1; lz <= root_layer_CF; lz++)
		{
			totalRootDens[lz] = 0.0;

			// Calculate the total root mass in each layer by summing up the root mass of all crops growing in that layer
			for (int ccwcb = 1; ccwcb <= CropNumbers; ccwcb++)
			{
				totalRootDens[lz] += rootDensity[ccwcb][lz] * Root_Wt[ccwcb];
			}

			// Calculate the CF_water for each crop in that layer
			for (int ccwcb = 1; ccwcb <= CropNumbers; ccwcb++)
			{
				// If the PGI of a crop is very low, no competition (0.05 is arbitrary and can be changed!)
				if (PGI[ccwcb] < 0.15)
				{
					CF_water[ccwcb][lz] = 1;
				}
				// Else, calculate water competition factor for that crop in that layer
				else if(totalRootDens[lz]==0.0) // if there is no root mass in that layer, then there is no competition, set CF_water = 1 to avoid divide by zero error
				{
					CF_water[ccwcb][lz] = 1;
				}
				else if(totalRootDens[lz]!=0)
				{
					CF_water[ccwcb][lz] = rootDensity[ccwcb][lz] * Root_Wt[ccwcb] / totalRootDens[lz];
				}

				CF_water[ccwcb][lz] = max(0, CF_water[ccwcb][lz]);

				//CF_water[ccwcb][lz] = 1.0;
			}
		}
	}
}



void class_model::N_CompFactor()
{
	int ccwc;
	float totalRootComp = 0;
	float f_up[8];
	float day_SoilN_demand;
	float day_fix_N;
	bool growflag = 0; // growflag = 0 if none of the crops are currently growing (i.e. don't go into loop, save time) 

	// Loop to determine whether to initialize CF_N to 0 or to actually compute CF_N
	for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
	{
		if (crop_flag[ccwc] == 1)
		{
			growflag = 1; // if at least one crop is currently growing, go ahead and calculate CF_N
		}
	}

	if (growflag == 0) // if nothing is currently growing, initialize all CF_N[ccwc] = 0 
	{
		for (ccwc = 1; ccwc <= CropNumbers; ccwc++)
		{
			CF_N[ccwc] = 0.0;
		}
	}

	else if (growflag == 1) // if at least one crop is growing, go ahead and calculate the CF_N
	{
		for (ccwc = 1; ccwc <= CropNumbers; ccwc++)
		{
			if (max_N_fix[ccwc] > 0.0) //test to see if Nfix is on
			{
				float tempFixN, nStatusFixN, day_fix_N_temp, day_SoilN_demand_temp;
				float sumNO3, sumNH4, averageTemp3;
				int tempCounter;
				tempCounter = 0;
				sumNO3 = 0.0;
				sumNH4 = 0.0;
				averageTemp3 = 0.0;

				for (int xx = 1; xx < q; xx++) //calculate the N in rooting depth
				{
					if (SoilDepth[xx] <= root_depth[ccwc])//was 0.3 depth  //root_depth[ccwc]   max_root_length[ccwc]
					{
						sumNO3 += no3[xx];
						sumNH4 += nh4[xx];
						averageTemp3 += temp[xx];
						tempCounter += 1;
					}
				}


				averageTemp3 = averageTemp3 / tempCounter;  //apsim temperature adjustment on Nodulatation
				if (tempCounter < 1) averageTemp3 = air_temp;
				tempFixN = averageTemp3 * averageTemp3 * (55 - averageTemp3) * powf(10, -4);
				tempFixN = (averageTemp3 * averageTemp3 * (40 - averageTemp3) * powf(10, -4)) / 0.9477;

				tempFixN = 1.0;
				tempFixN = min(1.0, max(0.0, tempFixN));




				//calculate a N2 Nodulation efficiency based on Zhang McGill study.
				float N2NodEF;

				N2NodEF = 1.0 / ((25.0 - averageTemp3) * 1.8182 + 17.0); //25.0 = optimal temperature to generate full nodulation by V2-V3 stage/averageTemp3=rooting depth soil temp /1.8182 is slope of FIg 1 from Zhan/ 17.0 = days after emergence to expect full nodulations


				// Moisture stress on N fixation potential
				double wiltptw = h[1] * sts[1] * wiltpt[1];
				double fldcapw = h[1] * sts[1] * fldcap[1];

				float waterStressFactor, waterNodStress;

				//need to figure out water stress maybe using crop stress factor. day_CropWater???
				waterStressFactor = (water[1][1] - fldcapw) / (1.0 - fldcapw);

				waterNodStress = 1.6667 * waterStressFactor - 0.3333;  //adapted from APSIM - Modeling Flood-Induced Stress in Soybeans Feb 2020
				waterNodStress = 1.0 - (min(1.0, max(0.0, waterNodStress)));
				if (waterNodStress < 0.0) waterNodStress = 0.0;
				if (waterNodStress > 1.0) waterNodStress = 1.0;



				//tempFixN = N2NodEFACC[ccwc];
				//calculate concentration conversion to kg N/ha of 10 g N /m3 and 30 g N /m3
				float conc10, conc30, concDNDC;
				float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;	//calculate bulk density of soil layer
				conc10 = bulk_density * (3000) * 10 / 1000;//bulk density * 3000 m3 volume of soil in a ha in .3m * 10 g N/kg /1000 g to kg.//units kg/ha 10000*max_root_length[ccwc]
				conc30 = bulk_density * (3000) * 30 / 1000;//units kg/ha 10000*max_root_length[ccwc]
				concDNDC = (sumNO3 + sumNH4) * 1000 / (3000 * bulk_density) * root_depth[ccwc];//units in g N /m3 10000*max_root_length[ccwc]

				conc10 = 400;//80
				conc30 = 500;//was 30 for agmip soybean
				//concDNDC=(sumNO3+sumNH4);

				if ((sumNO3 + sumNH4) < conc10)//(sumNO3+sumNH4)<10)
				{
					nStatusFixN = 1.0;
				}
				else if ((sumNO3 + sumNH4) > conc30)//(sumNO3+sumNH4)>30)
				{
					nStatusFixN = (conc30 / (sumNO3 + sumNH4));
					nStatusFixN = max(0.5, nStatusFixN);
					//nStatusFixN=0.0;

				}//was 0.0
				else
				{
					nStatusFixN = 1 - ((sumNO3 + sumNH4) / conc30);
					//	nStatusFixN=1.0-0.05*(concDNDC);//(sumNO3+sumNH4) //0.025
				}

				nStatusFixN = min(1.0, max(nStatusFixN, 0.0));
				

				day_fix_N_temp = (day_N_demand2[ccwc] / maxmn[ccwc]) * max_N_fix[ccwc] * tempFixN * nStatusFixN;
				day_SoilN_demand_temp = day_N_demand2[ccwc] - day_fix_N_temp;

				
				// Now compute the f_up for the N-fixer, based on ratio of daily soil N uptake to daily N demand
				f_up[ccwc] = day_SoilN_demand_temp / day_N_demand2[ccwc];

				//if (PGI[ccwc] > 0.05 && day_SoilN_demand_temp==0.0) f_up[ccwc] = 1.0 - (PGI[ccwc]);

				if (day_N_demand2[ccwc] == 0) // divide-by-zero error messes everything up if day_N_demand2[ccwc] = 0 
				{
					f_up[ccwc] = 1;
				}

			}

			else
			{
				// If non-N-fixing crop, set f_up to 1.0
				f_up[ccwc] = 1.0;
			}

			// Compute "total" root competition (denominator of CF) across all root types
			totalRootComp += f_up[ccwc] * Root_Wt[ccwc];

		}

		// Now compute nitrogen competition factor for the crop (not per layer, contrary to water_CompFactor)
		for (ccwc = 1; ccwc <= CropNumbers; ccwc++)
		{
			// If the PGI of a crop is very low, no competition (0.05 is arbitrary and can be changed!)
			if (PGI[ccwc] < 0.05)
			{
				CF_N[ccwc] = 1;
			}
			else if (totalRootComp == 0.0) // if there is no root mass in the mixture, then there is no competition, set CF_N = 1 to avoid divide by zero error
			{
				CF_N[ccwc] = 1;
			}
			// Else, compute the CF_N for that crop
			else if (totalRootComp > 0.0)
			{
				if (f_up[ccwc] == 0.0)
				{
					float blah;

					blah = 1.0;

				}
				CF_N[ccwc] = f_up[ccwc] * Root_Wt[ccwc] / totalRootComp;
			}

			CF_N[ccwc] = max(0, CF_N[ccwc]);
			//CF_N[ccwc] = 1.0;

		}
	}
}
void class_model::leafTempMod(int ccwc)
{

	// Constants
	const double lapseRate = 0.0065; // oC/m
	const double albedo = 0.23; // typical crop albedo
	const double sigma = 5.67e-8; // Stefan-Boltzmann constant (W/m2 K)
	//const double k = 0.5; // extinction coefficient ...might use the Kext1[ccwc]
	float k;
	k = kext1[ccwc];
	// Step 1: Air temperature at canopy height
	double t_air_canopy = ((max_temp + min_temp) / 2.0) - lapseRate * (2.0 - CropHeight[ccwc]) * 100.0;

	// Step 2: Convert solar radiation to (W/m2 K)
	double solarRad_W_m2 = (DayPETRs * 1e6) / (24.0 * 3600.0);

	// Step 3: Vapor pressure deficit (VPD)
	double es = 0.6108 * exp((17.27 * t_air_canopy) / (t_air_canopy + 237.3)); // kPa
	double ea = es * (humidity / 100.0);
	double vpd = es - ea;

	// Step 4: Net radiation absorbed by leaves
	double r_absorbed = (1.0 - albedo) * DayPETRs;

	// Step 5: Estimate delta T (leaf-air temperature difference)
	double deltaT = (r_absorbed * (1.0 - exp(-k * lai[ccwc]))) /
		(4.0 * sigma * pow(t_air_canopy + 273.15, 3));

	// Step 6: Final leaf temperature
	leafTemp_C[ccwc] = t_air_canopy + deltaT;

	if(leafTemp_C[ccwc]<0.0)leafTemp_C[ccwc] = 0.0;	

	//return leafTemp_C[ccwc];
}


// ===================  LEAF TEMPERATURE (SENSIBLE + LATENT)  ===================
// Irrigation/soil-water sensitivity via day_DWater[ccwc] (0..1; 1=no stress).
// Uses daily inputs: max_temp, min_temp, air_temp, humidity (%), wind_speed (m s-1),
// PAR (MJ m-2 d-1; your global shortwave), albedo, latitude, jday (only for Rn if needed),
// CropHeight[], lai[], kext1[]. Stores: leafTemp_C[ccwc].

// --- clamp Support ---
inline double clamp(double value, double min, double max) {
	return value < min ? min : (value > max ? max : value);
}
//improved leaf temp based on latent and sensible heat fluxes. Sensitive to irrigation/water supply.
void class_model::leafTemp(int ccwc)
{


	
	// ---- constants ----
	const double sigma = 5.670374419e-8;     // W m-2 K-4
	const double kvon = 0.41;               // von Kármán
	const double Cp = 1004.0;             // J kg-1 K-1
	const double Rgas = 287.05;             // J kg-1 K-1 (dry air)
	const double lambda_v = 2.45e6;          // J kg-1
	const double lapse = 0.0065;             // °C m-1
	const double emis_leaf = 0.96;           // leaf emissivity

	// ---- inputs ----
	const double h = CropHeight[ccwc];                // m
	const double LAI = max(lai[ccwc], 0.01);
	const double k = kext1[ccwc];                     // extinction coefficient
	const double Tmean = air_temp;                      // °C at 2 m (daily mean)
	const double RH = clamp(humidity, 0.0, 100.0);// %
	const double u2 = max(wind_speed, 0.1);       // m s-1 (avoid calm)
	const double PkPa = 101.325;                        // kPa (or your pressure if available)
	const double Rs_MJ = PAR;                           // MJ m-2 d-1 (your global Rs)
	const double alb = albedo;                          // canopy/surface albedo
	const double water_stress = clamp(day_DWater[ccwc], 0.0f, 1.0f); // 0..1

	// ---- air at canopy height (small height correction) ----
	const double Tair_can = Tmean - lapse * (2.0 - max(h, 0.1)); // °C
	const double Tair_K = Tair_can + 273.15;

	// ---- conversions & helpers ----
	const double Rs_W = (Rs_MJ * 1e6) / 86400.0;            // W m-2
	auto es_kPa = [](double Tc) { return 0.6108 * exp(17.27 * Tc / (Tc + 237.3)); };
	auto Delta = [&](double Tc) { return 4098.0 * es_kPa(Tc) / ((Tc + 237.3) * (Tc + 237.3)); };
	const double ea = es_kPa(Tair_can) * (RH / 100.0);      // kPa

	// ---- shortwave absorbed by leaves (Beer–Lambert) ----
	const double f_can = 1.0 - exp(-k * LAI);
	const double SW_abs = (1.0 - alb) * Rs_W * f_can;   // W m-2

	// ---- longwave down (Brutsaert 1975 clear-sky emissivity) ----
	double eps_sky = 1.24 * pow((ea * 10.0) / Tair_K, 1.0 / 7.0); // ea in mb ~ kPa*10
	eps_sky = clamp(eps_sky, 0.5, 1.0);
	const double Ldown = eps_sky * sigma * pow(Tair_K, 4);  // W m-2

	// ---- aerodynamic resistance ra (FAO-56 neutral) from canopy height ----
	double d = 0.67 * h, z0m = 0.123 * h, z0h = 0.1 * z0m;
	if (h < 0.12) { d = 0.08; z0m = 0.01476; z0h = 0.001476; }
	const double zref = 2.0;
	const double ra = (log((zref - d) / z0m) * log((zref - d) / z0h)) / (kvon * kvon * u2); // s m-1

	// ---- air density (ideal gas) ----
	const double rho = (PkPa * 1000.0) / (Rgas * Tair_K);   // kg m-3

	// ---- Jarvis-type gs -> rc; include day_DWater[ccwc] explicitly ----
	auto f_VPD = [](double vpd_kPa) { return 1.0 / (1.0 + vpd_kPa / 2.0); };
	auto f_T = [](double TleafC) { return 1.0 / (1.0 + max(TleafC - 35.0, 0.0) / 5.0); };
	const double gs_max = 0.01;  // m s-1 (tune per crop) //crops often fall in 0.005–0.02 --can calibrate

	auto rc_from_T = [&](double TleafC) {
		double vpd = max(es_kPa(TleafC) - ea, 0.0);
		double gs = gs_max * water_stress * f_VPD(vpd) * f_T(TleafC); // <-- irrigation via day_DWater will lower leaf_temp
		double LAI_eff = max(LAI, 0.1);
		return 1.0 / max(gs * LAI_eff, 1e-5);                       // s m-1
		};

	// ---- iterate Tleaf so that Rn_leaf = H + LE ----
	double Tleaf = Tair_can; // initial guess (°C)
	for (int it = 0; it < 8; ++it) {
		const double Tleaf_K = Tleaf + 273.15;
		const double Rn_leaf = SW_abs + emis_leaf * (Ldown - sigma * pow(Tleaf_K, 4)); // W m-2
		const double rc = rc_from_T(Tleaf);
		const double vpd_leaf = max(es_kPa(Tleaf) - ea, 0.0); // kPa

		// PM latent heat with ? and VPD evaluated at Tleaf (G?0 for canopy daily)
		const double gamma = 0.000665 * PkPa; // kPa °C-1
		const double num = Delta(Tleaf) * Rn_leaf + rho * Cp * (vpd_leaf) / ra; // Pa factor
		const double den = max(Delta(Tleaf) + gamma * (1.0 + rc / ra), 1e-6);
		const double LE = num / den;                // W m-2
		const double H = Rn_leaf - LE;           // W m-2

		const double Tnew = Tair_can + H * ra / (rho * Cp);
		if (std::abs(Tnew - Tleaf) < 0.05) { Tleaf = Tnew; break; }
		Tleaf = Tnew;
	}

	leafTemp_C[ccwc] = Tleaf; // store (°C), no clamping
}





/*
void class_model::crop_Height()
{
	// Numerical guards
	const double EPS_H = 1e-6;       // floor to avoid exact zero heights
	const double PGI_C1 = 0.8;  
	const double PGI_C2 = 0.4;  // transition around maturity
	const double SLOPE = 1.25;       // linear ramp factor used in your code

	// Update heights for all crops deterministically
	for (int c = 1; c <= CropNumbers; ++c)
	{
		// 1) Pick Hmax from parameters (cmaxh overrides species mapping in your code)
		double Hmax = static_cast<double>(cmaxh[c]);   // ensure meters; clamp later

		// 2) Read PGI defensively
		double pgi = static_cast<double>(PGI[c]);
		if (!isfinite(pgi)) pgi = 0.0;
		pgi = clamp(pgi, 0.0, 1.0);

		double H;
		if (pgi <= PGI_C2) {
			H = Hmax * SLOPE * pgi;// same cubic as before // same as Hmax * (3 * pow((PGI[c] / 0.8), 2) - 2 * pow((PGI[c] / 0.8), 3));//Hmax * 1.25f * PGI[c];
		}
		else if (pgi <= PGI_C1)
		{
			const double x = pgi / PGI_C1;
			H = Hmax * (3.0 * x * x - 2.0 * x * x * x);

		}
		else {
			H = Hmax;
		}
		// 4) Clamp and floor
		if (!(H >= 0.0)) H = 0.0;                    // NaN safe: !(H>=0) catches NaN
		H = clamp(H, 0.0, Hmax);
		if (H < EPS_H) H = EPS_H;                    // avoid exact zeros for light solver

		CropHeight[c] = static_cast<float>(H);
		//CropHeight[c] = 1.000;
	}
	

}
*/


void class_model::crop_Height()
{
	// Simple thermally driven crop height calculation routine
	// Hmax: maximum crop height (m), should be crop-specific (Hmax[c])
	// NOTE: This should come from Crop_parameters (cmaxh[c]).

	for (int c = 1; c <= CropNumbers; ++c)
	{
		double Hmax;

		// Original species-based defaults (overwritten by cmaxh[c] below)
		

		// Use parameter file value
		Hmax = cmaxh[c];

		// Linear crop height calculation:
		// Max height is reached at PGI = 0.80 (1.25 * 0.8 = 1.0)
		// 2) Read PGI defensively
		double pgi = static_cast<double>(PGI[c]);
		if (!isfinite(pgi)) pgi = 0.0;
		pgi = clamp(pgi, 0.0, 1.0);


		const double x = pgi;
		double H;

		double p50 = 0.25;
		p50 = clamp(p50, 0.0, 1.0);
		double k = 12.0;
		const double s = -k * (pgi - p50);
		CropHeight[c] = Hmax * (1.0 / (1.0 + exp(s)));

		CropHeight[c]=clamp(CropHeight[c], 0.0, Hmax);

		/*
		if (PGI[c] <= 0.8f) {
			CropHeight[c] = Hmax * 1.25f * PGI[c];
		}
		else {
			CropHeight[c] = Hmax;
		}

		// Avoid exact zero to prevent divide-by-zero in light competition
		if (CropHeight[c] == 0.0f) {
			CropHeight[c] = 0.01f;
		}
		*/
		
	}

	// TODO: Update height after cutting using CutFraction[c] if applicable.
}


#include <algorithm>
#include <cmath>

void class_model::light_CompFactor()
// Calculates a light stress factor in [0,1] for each crop in the mixture
{
	// ----- numerical guards -----
	const double EPS_H = 1e-6;   // height epsilon to avoid exact-zero branch flips
	const double EPS_K = 1e-12;  // denominator guard for k*LAI sums & ratios
	const double GAMMA = 0.3;    // your original exponent
	const float  STRESS_MIN = 0.2f; // your original lower bound
	const float  STRESS_MAX = 1.0f;
	

	//check Kext value being imported. 

	/*
	lai[1] = 5.0;
	lai[2] = 5.0;
	lai[3] = 5.0;
	lai[4] = 5.0;
	lai[5] = 5.0;
	*/
	// ----- default all crops to "no light stress" each call -----
	// (prevents stale values if a branch returns early)
	for (int c = 1; c <= CropNumbers; ++c) {
		lightStressFactor[c] = 1.0f;
											} // [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)

	// ----- edge: no crops -----
	if (CropNumbers <= 0) return; // nothing to do  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)



	if (CropNumbers <= 2) {
		const int c = 1;
		const double I0 = static_cast<double>(PAR);           // incident PAR
		const double Kext = static_cast<double>(kext1[c]);
		const double LAI = static_cast<double>(lai[c]);

		// physically-consistent intercepted PAR by the single canopy
		const double Itot = I0 * (1.0 - exp(-Kext * LAI));

		cropRad[c] = Itot;          // <-- populate cropRad even when 1 crop
		lightStressFactor[c] = 1.0f; // no competition stress

		//return; // done
	}


	// ----- identify tallest crop and total LAI -----
	int    tallestCrop = 1;
	double maxHeight1 = -1.0;
	double maxHeight2 = -1.0;
	double LAItot = 0.0;
	const double I0 = static_cast<double>(PAR); // incident PAR (global)

	// one pass to find tallest and LAI total
	for (int c = 1; c <= CropNumbers; ++c) {
		const double h = static_cast<double>(CropHeight[c]);
		LAItot += static_cast<double>(lai[c]);
		if (h > maxHeight1) {
			maxHeight2 = maxHeight1;
			maxHeight1 = h;
			tallestCrop = c;
		}
		else if (h > maxHeight2) {
			maxHeight2 = h;
		}
	} // [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)



	


	// ----- trivial no-stress cases -----
	if (CropNumbers == 1) return;                 // already set to 1.0  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)
	if (LAItot <= 1.0)    return;                 // Wiles & Wilkerson heuristic in your code  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)
	if (maxHeight1 <= EPS_H) return;              // tallest crop effectively absent  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)

	// ----- define two canopy layers -----
	const double cl1 = max(0.0, maxHeight1 - max(0.0, maxHeight2)); // top layer
	const double cl2 = max(0.0, min(maxHeight1, max(0.0, maxHeight2))); // bottom layer thickness
	if (cl2 <= EPS_H) return; // no bottom layer => effectively no interspecies shading  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)

	// ----- top layer interception: only tallest crop's top portion -----
	const double Kext_tall = static_cast<double>(kext1[tallestCrop]); // fixed parameter
	const double LAI_tall_total = static_cast<double>(lai[tallestCrop]);
	const double LAI_tall_top = (maxHeight1 > 0.0) ? (LAI_tall_total * cl1 / maxHeight1) : 0.0;

	const double I1 = I0 * (1.0 - exp(-Kext_tall * LAI_tall_top)); // intercepted in top layer
	const double T1 = I0 - I1;                                          // transmitted to bottom layer  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)

	// ----- bottom layer k*LAI sum over all crops -----
	const double LAI_tall_bottom = (maxHeight1 > 0.0) ? (LAI_tall_total * cl2 / maxHeight1) : 0.0;

	double kLAI2 = 0.0;
	for (int c = 1; c <= CropNumbers; ++c) {
		const double Kext_c = static_cast<double>(kext1[c]);
		if (c == tallestCrop) {
			kLAI2 += Kext_c * LAI_tall_bottom;
		}
		else {
			kLAI2 += Kext_c * static_cast<double>(lai[c]);
		}
	}
	if (kLAI2 < EPS_K) kLAI2 = EPS_K; // denominator guard  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)

	// intercepted in bottom layer
	const double I2 = T1 * (1.0 - exp(-kLAI2)); //  [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)

	// ----- share I2 by crop and accumulate total intercepted per crop -----
	// local temporaries sized to CropNumbers (you had [8] originally; now we compute directly)
	for (int c = 1; c <= CropNumbers; ++c) {
		const double Kext_c = static_cast<double>(kext1[c]);
		const double LAI_c_bot = (c == tallestCrop) ? LAI_tall_bottom
			: static_cast<double>(lai[c]);
		const double share_num = Kext_c * LAI_c_bot;
		const double I2_c = (share_num <= 0.0) ? 0.0 : (I2 * (share_num / kLAI2));

		// total intercepted per crop across both layers
		const double Itot_c = (c == tallestCrop) ? (I1 + I2_c) : I2_c;
		 cropRad[c] = Itot_c;
		// ----- compute stress factor with clamped ratio and bounds -----
		const double Ipot = I0 * (1.0 - exp(-Kext_c * static_cast<double>(lai[c])));
		double stress;
		if (Ipot > EPS_K) {
			const double ratio = clamp(Itot_c / Ipot, 0.0, 1.0);
			stress = static_cast<float>(pow(ratio, GAMMA));
						}
		else	{
			stress = 1.0f; // effectively no LAI => no light stress
				}

		// final clamp to your requested range
		stress = min(STRESS_MAX, max(STRESS_MIN, stress));
		lightStressFactor[c] = stress;
	//	lightStressFactor[c] = 1.0;
										} // [1](https://001gc-my.sharepoint.com/personal/brian_grant_agr_gc_ca/Documents/Microsoft%20Copilot%20Chat%20Files/lightstress.txt)

	
}


/*
void class_model::light_CompFactor() // calculates a light stress factor bound between 0 (complete shading, no growth) and 1 (no stress, full growth) for each crop in the mixture
{
	int tallestCrop; // index of the tallest crop in the mixture
	float maxCropHeight1 = 0.0; // height of the tallest crop in the mixture
	float maxCropHeight2 = 0.0; // height of the second-to-tallest crop in the mixture
	float cl1, cl2; // "thicknesses" of the top layer (cl1) and bottom layer (cl2)
	float LAItall1, LAItall2; // share of the LAI of the tall crop in the top and bottom layers, respectively
	float LAItot = 0.0; // total LAI (summed across all crops)
	float I0 = PAR; // incident radiation (PAR = global variable)
	float I1, I2; // intercepted radiation in the top and bottom layers, respectively
	float T1, T2; // transmitted radiation in the top and bottom layers, respectively
	float I_albedo; // reflected radiation from the soil into bottom layer (= soil albedo)
	float kLAI2; // exponent of e for layer 2
	float I2_crop[8]; // temporary variable
	float Itot[8]; // total intercepted radiation for each crop in the mixture
	float Ipot; //potential intercepted radiation (optimal)
	float Kext = 0.6; // TEMPORARY extinction coefficient for all crops until we make it crop-specific (Kext[ccwc]) - can be approximated by searching literature  controls how much solar radiation is intercepted by the canopy
	if(year==5 && jday==1)
	{
		float blah;
		blah = 1.0;
	}
	// First, identify tallest crop in the mixture
	for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
	{
		Kext = kext1[ccwc];
		if (CropHeight[ccwc] > maxCropHeight1)
		{
			maxCropHeight1 = CropHeight[ccwc];
			tallestCrop = ccwc; // save index of tallest crop
		}

		// also update the total LAI in the mixture
		LAItot += lai[ccwc];

	}

	if (CropNumbers == 1) // if only one crop is growing, no inter-species shading occurs -> no light stress
	{
		lightStressFactor[1] = 1.0;
	}

	else if (LAItot <= 1.0) // if multiple crops are growing concurrently but the total (combined) LAI is below 1.0, no shading is assumed to occur -> no light stress (Wiles and Wilkerson, 1991)
	{
		for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
		{
			lightStressFactor[ccwc] = 1.0;
		}
	}
	if (year == 5 && jday == 1)
	{
		float blah;
		blah = 1.0;
	}
	else // if multiple crops are growing concurrently and total LAI is greater than 1.0, shading is assumed to occur -> compute light stress factors
	{
		// identify second-to-tallest crop in the mixture
		for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
		{
			if (CropHeight[ccwc] < maxCropHeight1 && CropHeight[ccwc] > maxCropHeight2)
			{
				maxCropHeight2 = CropHeight[ccwc];
			}
		}

		if (maxCropHeight1 > 0.05) // if tallest crop has a height greater than 0
		{
			// divide canopy vertically into two layers
			cl1 = maxCropHeight1 - maxCropHeight2; // top layer only contains the top part of the tallest plant
			cl2 = maxCropHeight2; // bottom layer contains the bottom part of the tallest plant + all shorter plants

			// light interception in top layer
			Kext = kext1[tallestCrop];
			LAItall1 = lai[tallestCrop] * cl1 / maxCropHeight1; // share of the LAI of tallest crop residing in top layer
			I1 = I0 * (1 - exp(-Kext * LAItall1)); // Kext[ccwc] needs to be an accessible crop parameter (can use 0.5 as placeholder?) //Kext1[ccwc]
			T1 = (I0 - I1); // T1 is the transmitted light in layer 1. (we could also multiply by 0.9 if we assume 10% of the PAR is lost due to reflection by the canopy / plant albedo: Zhu et al. 2008 https://doi.org/10.1016/j.copbio.2008.02.004)

			if (maxCropHeight2 > 0.0) // if the second-to-tallest crop has a height greater than 0 (i.e. there is a bottom layer)
			{
				// compute light interception in bottom layer
				LAItall2 = lai[tallestCrop] * cl2 / maxCropHeight1; // share of the LAI of tallest crop residing in bottom layer

				// calculate the exponent term for Beer law for bottom layer (which is KLAI2 = Kext * LAI summed across all crops in that layer)
				kLAI2 = 0.0;

				for (int ccwc = 1; ccwc <= CropNumbers; ccwc++) // sum kLAI for all crops
				{
					Kext = kext1[ccwc];

					if (ccwc == tallestCrop)
					{
						kLAI2 += Kext * LAItall2; // for the tallest crop, make sure the LAI is only the fraction of its LAI present in the layer Kext1[ccwc]
					}
					else
					{
						kLAI2 += Kext * lai[ccwc]; // for all other (shorter) crops, the LAI is the total LAI //Kext1[ccwc]
					}


				}

				// compute light interception in bottom layer
				I2 = T1 * (1 - exp(-kLAI2)); // T1 is the total amount of light transmitted through top layer (that reaches bottom layer)


				// could also compute albedo from the soil back into the bottom layer (albedo calculation taken from Dndc_SoilPhysics.cpp)
				// T2 = 0.9 * (I1 - I2); // T2 is the light transmitted from bottom layer to soil
				//float drySoilAb = 0.35;//the albedo for dry soil
				//float wetSoilAb = 0.19; //the albedo for wet soil
				//float holdCap = fldcap[1] - wiltpt[1];//holding capacity of the soil layer 1
				//float soilMoistFact = day_wfps[1] / fldcap[1];// fraction of soil moisture to field capacity
				//float soilMoistFact = min(1.00f, max(soilMoistFact, 0.0f));
				//float soilAb = soilMoistFact * wetSoilAb + (1 - soilMoistFact) * drySoilAb;
				//I_albedo = soilAb * T2; // the reflected light from the soil up into the bottom layer


				// compute total amount of absorbed light for each crop in the bottom layer
				for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
				{
					Kext = kext1[ccwc];
					if (ccwc == tallestCrop)
					{
						// compute amount of light intercepted by the tallest crop in the bottom layer
						I2_crop[ccwc] = I2 * (Kext * LAItall2) / kLAI2;//possibly Kext2[ccwc] for Kext here
						// sum amount of light intercepted in the top and the bottom layers
						Itot[ccwc] = I1 + I2_crop[ccwc];
					}
					else
					{
						// compute amount of light intercepted by the shorter crop(s) in the bottom layer
						I2_crop[ccwc] = I2 * (Kext * lai[ccwc]) / kLAI2; // possibly Kext2[ccwc] for Kext here
						Itot[ccwc] = I2_crop[ccwc];
					}

				}

				// now compute light stress factor for each crop
				for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
				{
					Kext = kext1[ccwc];//Brian insert to populate the crop specific Kext into this function.
					Ipot = I0 * (1 - exp(-Kext * lai[ccwc])); //should this be Kext1[ccwc] or Kext2[ccwc]?

					if (Ipot > 0.0)
					{
						lightStressFactor[ccwc] = pow(Itot[ccwc] / Ipot,0.3);
					}

					else // avoid divide-by-zero in case the crop has height = 0 (and therefore Itot and Ipot = 0)
					{
						lightStressFactor[ccwc] = 1.0;
					}
					if (lightStressFactor[ccwc] < 0.2)lightStressFactor[ccwc] = 0.2;//set a minimum light stress factor to avoid complete shut down of growth.
					
				}

			}

			else // if the second-to-tallest crop has not started growing so its height = 0 (i.e. only one crop is really present at the moment), no light stress
			{
				for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
				{
					lightStressFactor[ccwc] = 1.0;

				}
			}
		}

		else // if no crop has actually started growing, no light stress
		{
			for (int ccwc = 1; ccwc <= CropNumbers; ccwc++)
			{
				lightStressFactor[ccwc] = 1.0;
			}
			
		}
	

	}
}
*/