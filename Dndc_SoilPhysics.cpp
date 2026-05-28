#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "algorithm"
#include <cmath>
#include <algorithm>
#include <vector>



float ANGOT;

void class_model::snowfall_snowpack()
{
 	//rainfall = precipitation;

	SnowMelt = 0.0;

    if ( precipitation > 0.0 && air_temp <= -1.0 )//air_temp ...// if set air_temp <= 0.0 then days you get above zero max temp the precip all falls as snow since it's a daily assumption. 
    {
		snowfall = precipitation;
		rainfall = 0.0;  //m		
		TTT = 0.0;

		//if(st[1]>=12)
		//{
		//	if(sslope>0.0) snowfall /= (1.0+sslope);
		//	else snowfall *= 1.0;
		//}
		snow_pack += snowfall; //m water
    }
    else
    {
		snowfall = 0.0;
    }

    if ( snow_pack > 0.0f && max_temp > 1.5f )//max_temp //min_temp //air_temp > 1.5f
    {	
		if (precipitation > 0.0 && snowfall == 0.0)
		{
			//SnowMelt = 0.0007f * max_temp * snowmeltMulti * (precipitation)*1000;
			SnowMelt = 0.0007f * max_temp * snowmeltMulti * 1.05;
		}
		else
		{
			SnowMelt = 0.0007f * max_temp * snowmeltMulti;//0.001 /max_temp
		}

		if ( SnowMelt > snow_pack )
		{
			SnowMelt = snow_pack; //m water
			snow_pack = 0.0;
		}
		else
		{
			snow_pack -= SnowMelt;
		}

		//rainfall += (0.5*SnowMelt);
		//TTT = rainfall / 0.005;
		//day_runoff += SnowMelt; 

		day_runoff+=(SnowMelt * runMulti);
		surf_water += (SnowMelt * (1-runMulti));

	/*	
		//Brian texture runoff
		float textureFactor;
			textureFactor=0.000000002194*pow((clay[1]*100),5.9997);
			textureFactor=0.1005*clay[1]*100+0.0089;	
			textureFactor=pow(textureFactor,4);
				textureFactor=min(0.12,max(0.0,textureFactor));

		

		day_runoff+= SnowMelt * textureFactor;
		surf_water += (1-textureFactor)*SnowMelt;
		//brian end texture runoff
		*/
    }
    else
    {
		//melt_flag = 0.0;
    }

}

void class_model::water_temperatue(void)
{
	
	int i;
	float Td, Txn, Tmn, X, AJT, Tt, Tlai=(lai[1]+lai[2]+lai[3]), MaxLAI=10.0;

	Td = (max_temp - min_temp)*0.01;
	Txn = max_temp - Td;
	Tmn = min_temp + Td;

	Tt = SatuDays/(25.0f - Tlai);

	X = (Txn - Tmn) * (MaxLAI - Tt) / MaxLAI;

	AJT = min_temp + X - 2.0f;

	for(i=0; i<=1; i++) SWT[i] = SWT[i+1];
	SWT[2] = AJT;
	
	SurfaceWaterT = (SWT[0]+SWT[1]+SWT[2])/3.0;//+SWT[3]+SWT[4]+SWT[5]+SWT[6]+SWT[7]+SWT[8]+SWT[9]+SWT[10])/11.0;

	if(day_WT>0.0f&&AJT<0.0f) 
	{
		SurfaceWaterT = 4.0f;
	}


	//SurfaceWaterT = (0.6625 * air_temp + 1.157);// / (1.0 + (lai[1]+lai[2]+lai[3]) * 0.1);
}

//only used for urea-NH3 sub models. Needs a bit of retooling
void class_model::hourly_soil_temperature()
{
	  int l, n, qq;
  float K[250], Z[250], C[250], outQ[250], Kave, dQ;
  float Org, Min, Vwater, Vmin, Vorg, Vsoil, TM, Csoil, Ksoil, a,dQQ;
  float Mleaf, bcv1, bcv2;

  qq = q;//(int)(0.3/h);
  
  Mleaf = (Grain_Wt[1] + Leaf_Wt[1] + Stem_Wt[1])/.58/1000.0;//ton try matter/ha

  bcv1 = Mleaf / (Mleaf + (float)exp(7.563 - .0001297 * Mleaf));
  bcv2 = (snow_pack * 1000.00 / (snow_pack * 1000.0 + (float)exp(2.303 - .2197 * snow_pack * 1000.0)));
 // bcv1=0.001;
  //bcv2=0.001;

  //albedo = max(bcv1, bcv2);

  if ( jday == 1 ) OldTHr = air_temp;

//  float adjT = (air_temp+max_temp)*0.5;//Remove for soil temp mod
 // float adjT = air_temp;
  float fsl, dTT;
  
float albedoPlant= 0.25*(1-exp(-0.5*lai[1]));//Add for soil temp mod -- 
//if(surface_litter>=200)
//{fsl=1-(-0.0587*(float)log(surface_litter+0.0000001) + 1.0643);}//residue factor
//else{fsl=0;}
fsl=1-(-0.0987*(float)log(surface_litter+0.0000001) + 1.4943);
fsl=min(1.0, max(0.0,fsl)); //sets fsl to minimum and maximum between 0 and 1
float tempSurface=(1-albedoPlant-fsl)*(diTemp)*sqrt(0.05 * PAR);//Calculates surface soil temperature ..default 0.03 * PAR
float residueCoverF, radHeatF;
residueCoverF = fsl;
radHeatF = 0.5;
tempSurface = diTemp + (((1 - albedoPlant) * PAR / 0.0864) / (radHeatF * sd[1] * 800)) * (1 - residueCoverF);

float snowDepth=snow_pack*1.5f;//multiplies snow_pack in m/water to snowdepth/m
float frezThawD=0.05f;//Freezing thawing depth (set to 50cm)
float Ks=0.18f; //snow thermal conductivity;//0.15 default
float KsPlus=1/(1/Ks+fsl*100+lai[1]*2);
float Ka=0.25; //thermal conductivity of soil
float KaZ=Ka*snowDepth;
float KsX=KsPlus*frezThawD;

if(snow_pack==0.0)
{
	Surf_Temp=(tempSurface*.5+OldTHr*.5);
	if (jday == 1 && year == 1)Surf_Temp = OldTHr;
}
else
{
Surf_Temp=diTemp/(1+(KaZ/KsX));
}


//no flood flag (if(flood_flag==1){fsl=0.5}



  if(plastic_flag==1) 
  {Surf_Temp += FilmCoverFraction * 5.0;}
   
	  OldTHr = Surf_Temp;

	hourlyTemp[1]=Surf_Temp;
 

}


void class_model::soil_temperature()
{
	  int l, n, qq;
  float K[250], Z[250], C[250], outQ[250], Kave, dQ;
  float Org, Min, Vwater, Vmin, Vorg, Vsoil, TM, Csoil, Ksoil, a,dQQ;
  float Mleaf, bcv1, bcv2;
  
  qq = q;//(int)(0.3/h);
  
//  Mleaf = (Grain_Wt[1] + Leaf_Wt[1] + Stem_Wt[1])/.58/1000.0;//ton try matter/ha

 // bcv1 = Mleaf / (Mleaf + (float)exp(7.563 - .0001297 * Mleaf));
 
 // bcv1=0.001;
 // bcv2=0.001;

//albedo = max(bcv1, bcv2);
//calculate weighted albedo effect from soil moisture and LAI. When soil is dry = high albedo, when LAI=5 = crop LAI weight dominant.

 
 
 
 float maxLai,wtLai,wtSoil,cropAb;
 cropAb = 0.155;//maximum crop albedo...needs to be elaborated for multiple crops
 
 bcv2 = (snow_pack * 1000.0 / (snow_pack * 1000.0 + (float)exp(2.303 - .2197 * snow_pack * 1000.0)));
 bcv2 = min(0.55, bcv2);//max bcv2 is 0.55 for snow covered albedo

float laiArray[7] = { lai[1],lai[2],lai[3],lai[4],lai[5],lai[6],lai[7] };//an array of LAI from crops
maxLai =*std::max_element(laiArray, laiArray+7);
wtLai=0.2f*(maxLai);//20% of LAI
wtLai=min(1.0f,max(wtLai,0.0f)); //calculates the fraction of crop coverage over the soil


float soilMoistFact,holdCap,drySoilAb,wetSoilAb,soilAb;
drySoilAb = 0.30;//the albedo for dry soil
wetSoilAb = 0.19; //the albedo for wet soil
holdCap=fldcap[1]-wiltpt[1];//holding capacity of the soil layer 1
soilMoistFact = day_wfps[1]/fldcap[1];// fraction of soil moisture to field capacity
soilMoistFact=min(1.00f,max(soilMoistFact,0.0f));
soilAb = soilMoistFact * wetSoilAb + (1 - soilMoistFact) * drySoilAb;
albedo = wtLai * cropAb + (1 - wtLai) * soilAb;

if(bcv2>0)
{
	albedo=bcv2;
}

/*
if (Leaf_Wt[1] > 0)
{
	Albedo = 0.195;
}
*/



 // if(bcv1>0)
//{albedo=0.26;}
//if(albedo<0.195)albedo=0.195;
  if ( jday == 1 && year==1 ) OldT = air_temp;//li code


  float fsl, dTT;
  

  //Volumatric heat capacity, J/(layer*K), and conductivity
 
//New Code

float b1,b2,b3; // defining emperical parameters for thermal conductivity for soil texture 	
float clayKsoil[3]={-0.197f,-0.962f,2.521f}; //criteria for clay texture	
float loamKsoil[3]={0.243f,0.393f,1.534f}; // criteria for loam texture	
float sandKsoil[3]={0.228f,-2.406f,4.909f}; // criteria for sand texture	
	
if(st[1]<4) //texture coefficients	
{	
	b1=sandKsoil[0];
	b2=sandKsoil[1];
	b3=sandKsoil[2];
}	
if(st[1]>3 && st[1]<7)	
{	
	b1=loamKsoil[0];
	b2=loamKsoil[1];
	b3=loamKsoil[2];
}	
if(st[1]>6)	
{	
	b1=clayKsoil[0];
	b2=clayKsoil[1];
	b3=clayKsoil[2];
}	


	b1=loamKsoil[0];
	b2=loamKsoil[1];
	b3=loamKsoil[2];	
	
		
	
  for (l=1; l<=qq; l++)	
  {	
   	
	
float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;	//calculate bulk density of soil layer
bulk_density = sd[l];//changed from above equation as it was using only the mass of the soil for the top layer as a calculation of bulk density for all layers.
if (bulk_density < 1.1)bulk_density = 1.1;
float pi = 3.14f;	//set pi
float voidRatio = sts[l]/(1-sts[l]);//porosity 	
//if (sts[l] > 0.6)
//voidRatio = 0.6 / (1 - 0.6);

float vWater;
float repWater;//representative volumetric water content
repWater=(day_wfps[l]+ice[l]/100)*sts[l];
if(repWater>sts[l])//if representative water content exceeds pore space then make it equal to pore space.
{repWater=sts[l];
}
if(repWater<(wiltpt[l]*sts[l]))//if representative water content falls below wilting point then make it equal to wilting point.
{repWater=(wiltpt[l]*sts[l]);
}
vWater=repWater;//volumetric water content cm3/cm3	

float degSat = repWater/sts[l]/sts[l];
float voidSpace = vWater/degSat;//volumetric space filled by air	
float vMin = voidSpace/voidRatio; //volumetric fraction of solids in soil space	
float vOrg = (soc[l]/mmm[l]) * vMin; //volumetric fraction of organic matter in soil space	
double Fs = ((1.0/3.0)* (1.0/((1.0+((b1+b2*vWater+b3*powf(vWater,0.5))/0.573)-1.0)*1.0)));//ratio of avg temp in soil to avg temp in water (continuous medium) - Jame, 1977 (thesis)
float L= 333.4f;// latent heat of ice with melting included (J/g)
float rho_ice= 917; // density of ice (kg/m3)
float rate_water=0.033f;//rate of change of water content with temp - Rankinen et al (2004)



if 	(snow_pack ==0)//for no snow case
{

	K[l] = (b1+b2*vWater+b3*powf(vWater,0.5))*5.0*100000; //Thermal Conductivity of soil (W/mK)(based on texture  Chung and Horton 1987 -- Hydrus 1d	
	C[l] = (((1.92 * vMin + 2.51 * vOrg + 4.18 * vWater) * 1000000)* (bulk_density/1000))*4.5*1000000; //Volumetric specific heat capacity of soil, J/m3/K -- de Vries 1963	

}

//Cmin = 1.92; Corg = 2.51; Cwater = 4.18 -- constants used as per de Vries, 1963
else
{
	float scalar;
	scalar = 4.5; //4.5 ; 
	if(l==1)//surface layer consider ice thickness for specific heat capacity
	{
	K[l] = (((vWater*0.573*1)+((vMin+vOrg)*(b1+b2*vWater+b3*powf(vWater,0.5)* Fs))/((vWater*1)+(vMin+vOrg)*Fs)))*5.0*100000;//Jame, 1977 (thesis)
	C[l] = ((((1.92 * vMin + 2.51 * vOrg + 4.18 * vWater) * 1000000) * (bulk_density / 1000)) + ((L * rho_ice * rate_water) / 1000)) *scalar * 1000000;//Rankinen et al (2004)
	}
	else //all other layers.
	{
	K[l] = (b1+b2*vWater+b3*powf(vWater,0.5))*5.0*100000; //Thermal Conductivity of soil (W/mK)(based on texture  Chung and Horton 1987 -- Hydrus 1d	
	C[l] = (((1.92 * vMin + 2.51 * vOrg + 4.18 * vWater) * 1000000) * (bulk_density / 1000)) *scalar * 1000000; //Volumetric specific heat capacity of soil, J/m3/K -- de Vries 1963

	}
}
		

  
float avg_temp = (max_temp + min_temp)/2; //average air temp	
float A0 = max_temp - avg_temp;//maxAnnualTemp - yr_avetj; 
 A0=0.0;

float z = 1*h[1]; // Surface soil depth 	
float w = 2*pi/365; //angular frequency	
float Dh = K[l]/C[l];// Thermal diffusivity	
float d = powf ((2*Dh/w), 0.5); // Damping depth	
float ratio_depth = z/d;	
int jdayCalc=jday;
jdayCalc=min(180,max(30,jdayCalc));//270 110	
	
Surf_Temp = avg_temp + A0 * exp (-ratio_depth) * sin ((w*(jdayCalc-14)) - ratio_depth - pi/2);//Surface temp code by texture -- Hydrus 1D	//sin ((w*(jday-14))



float greenLai,maxPGI;
float maxPGIA[7] = { PGI[1],PGI[2],PGI[3],PGI[4],PGI[5],PGI[6],PGI[7]};
greenLai=lai[1]+lai[2]+lai[3];
maxPGI = *std::max_element(maxPGIA, maxPGIA+7);
greenLai=-16.136*pow(maxPGI,2)+20.108*maxPGI-1.77767;
//greenLai=-15.568*pow(maxPGI,2)+20.149*maxPGI-1.8183;
//greenLai=-21.553*pow(maxPGI,2)+25.405*maxPGI-2.075;
greenLai=max(greenLai,0.0);
if((lai[1]+lai[2]+lai[3]+lai[4]+lai[5])==0.0)
{greenLai=0.0;}

//float albedoPlant= 0.19*(1-exp(-0.6*(lai[1]+lai[2]+lai[3])));//Add for soil temp mod -- //default .19 & 0.6
float albedoPlant=0.005*(1-exp(-1.0*(greenLai)));//default 0.3 .05 0.005
if(surface_litter>=200)//minimum surface litter required
{fsl=1-(-0.0287*(float)log(surface_litter+0.0000001) + 1.0643);}//residue factor -0.0287 
else{fsl=0;}
fsl=min(1.0, max(0.0,fsl)); //sets fsl to minimum and maximum between 0 and 1
float tempSurface=(1-max(albedoPlant,fsl))*(Surf_Temp)*(1+sqrt(0.0009 * PAR*SolarEffectTemp*3.0));//0.0004 Calculates surface soil temperature ...default 0.03  default 0.000005  - 0.0015 0.0012
//tempSurface=Surf_Temp;

/*
float albedoPlant= 0.50*(1-exp(-0.5*(lai[1]+lai[2]+lai[3])));//Add for soil temp mod -- 
if(surface_litter>=200)
{fsl=1-(-0.0287*(float)log(surface_litter+0.0000001) + 1.1343);}//residue factor  1-(-0.0587*(float)log(surface_litter+0.0000001) + 1.1343
else{fsl=0;}
fsl=min(1.0, max(0.0,fsl)); //sets fsl to minimum and maximum between 0 and 1
float tempSurface=(1-(albedoPlant)-fsl)*(Surf_Temp);//*sqrt(0.03 * PAR);//Calculates surface soil temperature ...default 0.03
*/
//snowInsulationFactor = pow(snowInsulationFactor, 5);//scale the factor to be a more sensitive factor for users (0-2 index)
float snowDepth = snow_pack * 100.0 * snowInsulationFactor;// *snowInsulationFactor;//multiplies snow_pack in m/water to snowdepth/m

/*
float frezThawD=0.05;//Freezing thawing depth (set to 50cm)
float Ks=0.18; //snow thermal conductivity;
float KsPlus=1/(1/Ks+fsl*100+lai[1]*2);//*100 * 2 converts into similiar rage of impact of snow....really need themral conductivity of residue and biomass to be mechanistic
float Ka=K[l]/100000; //thermal conductivity of soil
float KaZ=Ka*snowDepth;
float KsX=KsPlus*frezThawD;
*/


if(snow_pack==0.0&& surface_litter==0.0)
{
	Surf_Temp=(tempSurface)*0.5+OldT*0.5;
	
}
else if(snow_pack>0.0&&surface_litter<200)
{

Surf_Temp=(tempSurface*exp(-0.02*snowDepth));//Rankinen et al (2004) 


}
else if(surface_litter>=200&&snow_pack>0.0)
{
Surf_Temp=(tempSurface*exp(-0.02*(surface_litter/10000+snowDepth)));
}
else
{
Surf_Temp=(tempSurface*exp(-0.02*(surface_litter/10000)))*0.5 + OldT*0.5;
}

OldT = Surf_Temp;//sets today's temperature to OldT
if (isnan(Surf_Temp)||jday==204)
{
	float blah;
	blah = 1.0;

}

/*
//Outputting Stresses code
if(l==1&&jday==1&&year==1)
{CString TESTFILE;
FILE *pFile=NULL;
TESTFILE.Format("%s\\Record\\Stress.txt", OUTPUT);
pFile = fopen (TESTFILE,"w");
fprintf(pFile, "jday,year,layer,b1,b2,b3,vWater,vMin,vOrg,bulk_density,Fs,L,rho_ice,rate_water,K[l],C[l],day_wfps[l],ice[l],repWater,sts[l],wiltpt[l],tempSurface,airtemp,degSat,Surf_Temp,PAR\n");
fprintf(pFile, "%1d,%1d,%1d,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n",jday,year,l,b1,b2,b3,vWater,vMin,vOrg,bulk_density,Fs,L,rho_ice,rate_water,K[l],C[l],day_wfps[l],ice[l],repWater,sts[l],wiltpt[l],tempSurface,air_temp,degSat,Surf_Temp,PAR);
fclose (pFile);
}
else
{
CString TESTFILE;
FILE *pFile=NULL;
TESTFILE.Format("%s\\Record\\Stress.txt", OUTPUT);
pFile = fopen (TESTFILE,"a");
fprintf(pFile, "%1d,%1d,%1d,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n",jday,year,l,b1,b2,b3,vWater,vMin,vOrg,bulk_density,Fs,L,rho_ice,rate_water,K[l],C[l],day_wfps[l],ice[l],repWater,sts[l],wiltpt[l],tempSurface,air_temp,degSat,Surf_Temp,PAR);
fclose (pFile);
}
*/


	Org = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] + crhl[l]+crhr[l] + dphum[l]; //kg C/layer/ha  //add manurePool[l]
    Min = mmm[l];
    Vwater = water[1][l] * 10000.0; //m water/layer -> m3 water/layer/ha
    
    Vmin = Min / (1000 * sd[l]); //volume of mineral matter, m3/layer/ha
    Vorg = Org / 0.58 / (1000 * 0.4); //volume of organic matter, m3/layer/ha
    Vsoil = Vmin + Vorg; //volume of soil, m3/layer/ha

    TM = Org + Min;


	
  

    //Depth of layer, cm
    //Z[l] = 100.0 * l * h[l]; // cm
	if(l==1) Z[l] = h[1] * 100.0;
	else Z[l] = Z[l-1] + h[l] * 100.0;
 
 }//end layer bracket
OldT = Surf_Temp;//Brian added
  //Heat flux from layer L-1 down to L

#pragma loop(hint_parallel(8))
  for (n=1; n<=450; n++) //default 400 
  {

	  

	   for (l=1; l<=qq; l++)
	   {
		   a =14500.0; //10000 // Need to scale this to work for our new K value;//default 2000 //default 14000 ///(qq/(qq-l+1))  //was 14500
		  float ab = 10000;
			if (l==1)
			{
				float pondWater, F_water;
				F_water = 0.0;
				pondWater = surf_water * 2100.0;


				float F_litter = 0.0;

				if (surface_litter > 0.0) {
					F_litter = 3.5 * log10(surface_litter + 1.0); // +1 to avoid log(0)
				}
				else {
					F_litter = 0.0;
				}



			  float F_snow = 40.0  * snow_pack;//snow dampening on heat transfer
			  if (F_snow < 1.0) F_snow = 1.0;

			  if (pondWater > 0.0) F_water = 0.0;//pondWater


			  //heat transfer between air and first layer
			  float F_ice;
			  if(ice[l]>0 && snow_pack>0)
			  {
			  F_ice = 15.0;//default was 75 --super influential in adjusting the deep soil temperatures. Too high a value for ice and it'll cause problems with irrigation in colder climates.//trying 55
			  }
			  else if(ice[l]>0 && Surf_Temp<0.0)
			  {
				  F_ice=150.0;//default was 35
			  }
			  else if (ice[l] > 0 && Surf_Temp >= 0.0)
			  {
				  F_ice =0.0; //was seeing if this could be used to increase thawing in case when surf temp was above zero and there was ice up to the surface layer. //default 5.0
			  }
			  else
			  {
				  F_ice=0.0;

			  }
	
	





			  if (snow_pack > 0.0 || ice[l] > 0)
				  outQ[l - 1] = a * K[l] * (Surf_Temp - temp[l]) / Z[l] / (F_snow + F_ice + F_water + F_litter );//J/(cm2*day) 
			  else
				outQ[l-1] = a * K[l] * (Surf_Temp - temp[l]) / Z[l]/(F_litter);
			}

			if (l<qq)
			{
			   Kave = (K[l] + K[l+1]) / 2.0;
			   //heat from layer l to l+1
			   outQ[l] = a * Kave * (temp[l] - temp[l+1]) / (Z[l+1] - Z[l]);
			}
			else
			{
			   //heat from bottom layer to deeper soil
			   outQ[l] = a * K[l] * (temp[l] - yr_avetj) / (450.0 - Z[l]);//yr_avetj	//was set to 300 but setting it higher improves the deeper temperature simulation by increasing the overall temp		   //was 450
			}

			dQ = outQ[l-1] - outQ[l];

			float dT = dQ / C[l];
		//	dT=min(0.0075,max(-0.0075,dT));
			dT=min(0.00300,max(-0.00300,dT));//this shifts the temporal pattern of temperature at depth. Was at 0.5 -0.5 //was 0.150 vs -0.150//was 0.00250 -0.00250
			
			
			//temp[l] += dT;
			//float soilDepth = l * h[1]*100;
			//float depthFactor, difDepthFactor;
			//depthFactor=-0.00000924 * pow(soilDepth, 2) + 0.00193328 * pow(soilDepth, 1) + 0.14866775;
			
			//depthFactor = min(0.25, max(0.15, depthFactor));
			//difDepthFactor = 1 - depthFactor;
			if (isnan(temp[l]))
			{
				float blah;
				blah = 1.0;
			}
			temp[l] = (temp[l]*0.05) + (temp[l]+dT)*0.95;//was 0.2 and 0.8 weighted distrubtion //was 0.15 and 0.85
			if (isnan(temp[l]))
			{
				float blah;
				blah=1.0;
			}
			
	   } // l loop
 
  } // n


  const double T_f = 273.15; // Freezing point in Kelvin
  const double lambda_param = 0.5; // Soil-specific parameter (adjustable)

  for(l=1; l<=qq; l++)
  {

	  double layerHeight = h[l];           // m
	  double porosity = sts[l];            // m3/m3
	  double theta_s = porosity;           // Saturated water content
	  double total_water = water[1][l] + ice[l] / 10000.0; // m water/layer

	  double T_C = temp[l];                // °C
	  double T_K = T_C + 273.15;           // Convert to Kelvin

	  if (T_C <= 0.0) {
		  // Freezing condition
		  double theta_l = theta_s * pow((T_f - T_K) / T_f, -lambda_param)/100.0; // m3/m3
		  theta_l = min(theta_l, theta_s); // Cap at saturation

		  double liquid_vol = theta_l * layerHeight; // m water/layer
		  liquid_vol = min(liquid_vol, total_water); // Can't exceed total water

		  double frozen_vol = total_water - liquid_vol;


		  // Calculate change in ice
		  double delta_ice = frozen_vol - (ice[l] / 10000.0); // m water/layer

		  // Apply latent heat release if freezing occurred
		  if (delta_ice > 0.0) 
		  {
			  double latent_heat = delta_ice * 1000.0 * 334000.0; // J/layer
			  temp[l] += latent_heat / C[l]*1000.0; // Adjust temperature
		  }
		  if (delta_ice < 0.0)
		  {
			  double latent_heat = delta_ice * 1000.0 * 334000.0; // J/layer
			  temp[l] += latent_heat / C[l] * 1000.0; // Adjust temperature

		  }


		  water[1][l] = liquid_vol;
		  ice[l] = frozen_vol * 10000.0; // Convert to m3/ha
	  }
	  else {

		  double delta_ice = ice[l] / 10000.0; // m water/layer

		  if (delta_ice > 0.0) {
			  double latent_heat = delta_ice * 1000.0 * 334000.0; // J/layer
			  temp[l] -= latent_heat / C[l]*1000.0; // Adjust temperature

			 // primeDenit += 250.0; was thinking of adding N2O emission from that.
		  }
		  if (isnan(temp[l]))
		  {
			  float blah;
			  blah = 1.0;
		  }

		  // Thawing condition
		  water[1][l] = total_water;
		  ice[l] = 0.0;
	  }

	  // Optional: enforce physical limits
	  if (ice[l] / 10000.0 > porosity) {
		  ice[l] = porosity * 10000.0;
	  }
  

	  //typical method
	  /*
    float pQ1, pQ2, d_ice=0;
	float ps = h[l]*sts[l];
	float max_water = ps * 10000.0;//ps

    Vwater = water[1][l] * 10000.0;  // m water -> m3 water/layer/ha	
	
    if (temp[l]<=0.0) //freeze
    {
		if(Vwater>0.0&&ice[l]/10000.0<ps)
		{
			float freezeFactor;//was introducing to slow the rapid freezing down. Should be //4.186 J/g°C 
			freezeFactor = 0.005;// 1.0;// 0.005; // default is 1.0 adjusts how fast water freezes when temperature drops below zero. Affects soil temperature during winter  a fair bit. Slower Freezing = higher predicted soil temperature.
		   pQ1 = -temp[l] * C[l]*freezeFactor; //J/layer, heat release when T->0
		   pQ2 = Vwater * (4100000.0 - 2100000.0); //J/layer, water heat capacity

		   if (pQ1 > pQ2) //totally freeze
		   {
				dQQ = pQ2; //J/layer/ha
				temp[l] += (dQQ / C[l]);
				d_ice = Vwater; //m3 water/lay/ha
				Vwater = 0.0;

				ice[l] += d_ice;//m3 water/lay/ha
				water[1][l] = 0.0; //Vwater / 10000.0; // m water/layer 

				freezeWaterFactor = 1.0;

				//day_ice += d_ice/10000.0;
				//if(day_ice<0.0) day_ice = 0.0;

		   }
		   else //partially freeze
		   {
				dQQ = pQ1;
				temp[l] = 0.0;
				d_ice = dQQ / (4100000.0 - 2100000.0);

				if(d_ice > Vwater) 
					d_ice = Vwater;//m3 water/lay/ha
				else 
					d_ice = d_ice;

				Vwater -= d_ice;

				ice[l] += d_ice; //m3 water/lay/ha	
				
				water[1][l] -= (d_ice / 10000.0); // m water/layer
				//day_ice += d_ice/10000.0;// m water/layer
				//if(day_ice<0.0) day_ice = 0.0;
				
				//temp[l] += (dQQ / C[l]); // increase temp since energy is released (exothermic)

				freezeWaterFactor = 1.0;
		   }

		   if(ice[l]/10000.0 > ps) ice[l] = ps * 10000.0;
		}
		else
		{
			d_ice = 0.0;
		}

    }
	else  //thawing
    {
		//float thawFactor;//was introducing to slow the rapid freezing down. Should be //4.186 J/g°C 
		//thawFactor = 0.0003;
		if (ice[l]>0.0&&temp[l]>0.0)
		{
		   pQ1 = temp[l] * C[l] * 0.05;//0.1;//0.05;
		   //pQ2 = 2.0 * ice[l] * (4100000.0 - 2100000.0);
		   pQ2 = ice[l] * (4100000.0 - 2100000.0);

		   if (pQ1 > pQ2) //totally thawing
		   {
			dQQ = pQ2;
			temp[l] -= dQQ / C[l];
			d_ice = ice[l];
			
			Vwater += d_ice;
			ice[l] = 0.0;
			water[1][l] += d_ice / 10000.0; // m water/layer

			freezeWaterFactor = 1.0;

			//day_ice -= d_ice/10000.0;
			//if(day_ice<0.0) day_ice = 0.0;
		   }
		   else //partially thawing
		   {
			dQQ = pQ1;
			temp[l] = 0.0;
			//d_ice = -0.5 * pQ1 / (4100000.0 - 2100000.0);
			d_ice = pQ1 / (4100000.0 - 2100000.0);
			if(d_ice > ice[l]) d_ice = ice[l];
			Vwater += d_ice;
			ice[l] -= d_ice;// m3 water/layer/ha

			water[1][l] += d_ice / 10000.0; // m water/layer
			//temp[l] -= dQQ / C[l];

			freezeWaterFactor = 1.0;
			//day_ice -= d_ice/10000.0;
			//if(day_ice<0.0) day_ice = 0.0;
		   }
		   if(ice[l]>max_water) 
			   ice[l] = max_water;
		}
		else
		{ 
			d_ice = 0.0;
		}

    }	
    */
	if (ice[l] < 0.0) ice[l] = 0.0;

    if (water[1][l] < 0.0) water[1][l] = 0.0;

    total_ice += (ice[l]/10000.0); //m water for profile

  }//layer loop



//baishali end ===============================================================================================


/*
//Li start =====================================================================================
 //Volumatric heat capacity, J/(layer*K), and conductivity
 
  //Heat flux from layer L-1 down to L
  int WV = 200;
  
  for (n=1; n<=WV; n++)
  {
	   for (l=1; l<=qq; l++)
	   {
		  

		   a = 16000.0; //5000
			if (l==1)
			{
			  float F_snow = 20.0 * snow_pack;
			  if (F_snow < 1.0) F_snow = 1.0;

			  //heat transfer between air and first layer

			  if(snow_pack > 0.0)
				outQ[l-1] = a * K[l] * (Surf_Temp - temp[l]) / Z[l] / F_snow;//J/(cm2*day)
			  else
				outQ[l-1] = a * K[l] * (Surf_Temp - temp[l]) / Z[l];
			}

			if (l<qq)
			{
			   Kave = (K[l] + K[l+1]) / 2.0;
			   //heat from layer l to l+1
			   outQ[l] = 2000.0 * Kave * (temp[l] - temp[l+1]) / (Z[l+1] - Z[l]);
			}
			else
			{
			   //heat from bottom layer to deeper soil
			   outQ[l] = a * K[l] * (temp[l] - yr_avetj) / (200.0 - Z[l]);			   
			}

			dQ = outQ[l-1] - outQ[l];

			float dT = dQ / C[l];
 
			temp[l] += dT;

			//if(Surf_Temp>=yr_avetj) temp[l] = min(Surf_Temp, max(yr_avetj, temp[l]));
		//	else temp[l] = min(yr_avetj, max(Surf_Temp, temp[l]));


	   } // l loop
 
  } // n

  for(l=1; l<=qq; l++)
  {
    float pQ1, pQ2, d_ice=0;
	float ps = h[l]*sts[l];
	float max_water = ps * 10000.0;//ps

    Vwater = water[1][l] * 10000.0;  // m water -> m3 water/layer/ha	

    if (temp[l]<=0.0) //freeze
    {
		if(Vwater>0.0&&ice[l]/10000.0<ps)
		{
		   pQ1 = -temp[l] * C[l]; //J/layer, heat release when T->0
		   pQ2 = Vwater * (4100000.0 - 2100000.0); //J/layer, water heat capacity

		   if (pQ1 > pQ2) //totally freeze
		   {
				dQQ = pQ2; //J/layer/ha
				temp[l] += (dQQ / C[l]);
				d_ice = Vwater; //m3 water/lay/ha
				Vwater = 0.0;

				ice[l] += d_ice;//m3 water/lay/ha
				water[1][l] = 0.0; //Vwater / 10000.0; // m water/layer

				//day_ice += d_ice/10000.0;
				//if(day_ice<0.0) day_ice = 0.0;

		   }
		   else //partially freeze
		   {
				dQQ = pQ1;
				temp[l] = 0.0;
				d_ice = dQQ / (4100000.0 - 2100000.0);

				if(d_ice > Vwater) 
					d_ice = Vwater;//m3 water/lay/ha
				else 
					d_ice = d_ice;

				Vwater -= d_ice;

				ice[l] += d_ice; //m3 water/lay/ha	
				
				water[1][l] -= (d_ice / 10000.0); // m water/layer
				//day_ice += d_ice/10000.0;// m water/layer
				//if(day_ice<0.0) day_ice = 0.0;
		   }

		   if(ice[l]/10000.0 > ps) ice[l] = ps * 10000.0;
		}
		else
		{
			d_ice = 0.0;
		}

    }
	else  //thawing
    {
		if (ice[l]>0.0&&temp[l]>0.0)
		{
		   pQ1 = temp[l] * C[l] * 0.05;//0.1;//0.05;
		   //pQ2 = 2.0 * ice[l] * (4100000.0 - 2100000.0);
		   pQ2 = ice[l] * (4100000.0 - 2100000.0);

		   if (pQ1 > pQ2) //totally thawing
		   {
			dQQ = pQ2;
			temp[l] -= dQQ / C[l];
			d_ice = ice[l];
			
			Vwater += d_ice;
			ice[l] = 0.0;
			water[1][l] += d_ice / 10000.0; // m water/layer

			//day_ice -= d_ice/10000.0;
			//if(day_ice<0.0) day_ice = 0.0;
		   }
		   else //partially thawing
		   {
			dQQ = pQ1;
			temp[l] = 0.0;
			//d_ice = -0.5 * pQ1 / (4100000.0 - 2100000.0);
			d_ice = pQ1 / (4100000.0 - 2100000.0);
			if(d_ice > ice[l]) d_ice = ice[l];
			Vwater += d_ice;
			ice[l] -= d_ice;// m3 water/layer/ha

			water[1][l] += d_ice / 10000.0; // m water/layer
			//day_ice -= d_ice/10000.0;
			//if(day_ice<0.0) day_ice = 0.0;
		   }
		   if(ice[l]>max_water) 
			   ice[l] = max_water;
		}
		else
		{ 
			d_ice = 0.0;
		}

    }	
    
	if (ice[l] < 0.0) ice[l] = 0.0;

    if (water[1][l] < 0.0) water[1][l] = 0.0;

    total_ice += (ice[l]/10000.0); //m water for profile

  }//layer loop
//Li end ================================================================= 
*/
} // turn this on for Baishali temp code!!!!


// -Li soil temp


//working temp

/*
void class_model::soil_temperature()
{
  int l, n, qq;
  float K[120], Z[120], C[120], outQ[120], Kave, dQ;
  float Org, Min, Vwater, Vmin, Vorg, Vsoil, TM, Csoil, Ksoil, a,dQQ;
  float Mleaf, bcv1, bcv2;
 
  qq = q;//(int)(0.3/h);
  
  Mleaf = (Grain_Wt[1] + Leaf_Wt[1] + Stem_Wt[1])/.58/1000.0;//ton try matter/ha

  bcv1 = Mleaf / (Mleaf + (float)exp(7.563 - .0001297 * Mleaf));
  bcv2 = (snow_pack * 100.0 / (snow_pack * 100.0 + (float)exp(2.303 - .2197 * snow_pack * 100.0)));
  
  albedo = max(bcv1, bcv2);

  if ( jday == 1 ) OldT = air_temp;

  float adjT = (air_temp+max_temp)*0.5;
  //float adjT = air_temp;
  
  float fsl, dTT;

  //adjT = adjT / powf((1.0+lai),0.2); //albedo * OldT + (1.0 - albedo) * adjT;
  //adjT = albedo * OldT + (1.0 - albedo) * adjT;

  if(snow_pack==0.0)//&&surface_litter<=2000.0)
  {
	  if(SatuDays==0)//flood_flag==0)
	  {	
		  fsl = surface_litter / 1000.0;//-0.1097*(float)log(surface_litter+0.0000001) + 1.3143;
		  fsl = min(0.5, max(0.0, fsl));

		  Surf_Temp = OldT * fsl + adjT * (1.0 - fsl);
	  }
	  else
	  {
		  fsl = 0.8;
		  
		  Surf_Temp = SurfaceWaterT;
	  }
	  

	  //if(day_WT>0.0) 
	//	  Surf_Temp = SurfaceWaterT;
	  //else
	//	  Surf_Temp = OldT * fsl + adjT * (1.0 - fsl);//min_temp * (1.0 - fsl);//

	  //Surf_Temp = min_temp;//OldT * fsl + min_temp * (1.0 - fsl);
  }
  else
  {
	  float SnowDepth = snow_pack*20.0; //cm, snow pack thicknes
	  //Surf_Temp = 0.0 + adjT / (10.0 + SnowDepth);//
	  //Surf_Temp = max(0.0, Surf_Temp);
	  Surf_Temp = adjT / (1.0 + SnowDepth);//
	  
  } 

  float dHHH = 0.0;
  if(plastic_flag==1) 
  {
	  float TCfilm=0.25; //film thermal conductivity, 0.25 J/(s*m*K) 
	  float Dfilm=0.001; //film thickness, 0.001 m
	  float dt = 86400; //time, second
	  float SHsoil = 0.2; //soil heat capacity, 0.2 calorie/g/degree C
	  //1 calorie = 4.184 J

	  dHHH = (adjT - Surf_Temp) * Dfilm * TCfilm * dt;//J
	  float dTTT = (dHHH / 4.184) / (SHsoil * mmm[1]*1000.0);//degree C
	  Surf_Temp += dTTT;
  }
  else
  {
	  dHHH = 0.0;
  }

   
	  OldT = Surf_Temp;

  //Volumatric heat capacity, J/(layer*K), and conductivity
  for (l=1; l<=qq; l++)
  {
  
    
	Org = rcvl[l] + rcl[l] + rcr[l] + CRB1[l] + CRB2[l] + crhl[l]+crhr[l] + dphum[l]; //kg C/layer/ha
	if(Org<1000.0) Org = 1000.0;

    Min = mmm[l];
    Vwater = water[1][l] * 10000.0; //m water/layer -> m3 water/layer/ha
    
    Vmin = Min / (1000 * sd[l]); //volume of mineral matter, m3/layer/ha
    Vorg = Org / 0.58 / (1000 * 0.4); //volume of organic matter, m3/layer/ha
    Vsoil = Vmin + Vorg; //volume of soil, m3/layer/ha

    TM = Org + Min;

    Csoil = 0.25 * (3450000.0 * Vorg / Vsoil + 2350000.0 * Vmin / Vsoil); //J/(m3*K)
	//if(st[1]>=12) Csoil *= 2.0;

    C[l] = 0.5 * (Vsoil * Csoil + Vwater * 4180000.0); // J/(layer*K)

    //layer_Q[l] = (temp[l] + 273) * C[l];

    //Thermal conductivity, J/(cm*s*K)
	if(st[l]>=12)
		Ksoil = (0.0025 * Org / TM + 0.029 * Min / TM) * 10.0;
	else
		Ksoil = (0.0025 * Org / TM + 0.029 * Min / TM) * 10.0;
	
    K[l] = 86400.0 * ((1.0 - sts[l]) * Ksoil + sts[l] * day_wfps[l] * 0.0057);//
	   //J/(cm*day*K)

    //Depth of layer, cm
    //Z[l] = 100.0 * l * h[l]; // cm

	float Zz = 0.022;
	if(l==1) Z[l] = Zz * 100.0;
	else Z[l] = Z[l-1] + Zz * 100.0;
 
  }

  //Heat flux from layer L-1 down to L
  int WV = 200;
  
  for (n=1; n<=WV; n++)
  {
	   for (l=1; l<=qq; l++)
	   {
		  

		   a = 10000.0; //5000
			if (l==1)
			{
			  float F_snow = 100.0 * snow_pack;
			  if (F_snow < 1.0) F_snow = 1.0;

			  //heat transfer between air and first layer

			  if(snow_pack > 0.0)
				outQ[l-1] = a * K[l] * (Surf_Temp - temp[l]) / Z[l] / F_snow;//J/(cm2*day)
			  else
				outQ[l-1] = a * K[l] * (Surf_Temp - temp[l]) / Z[l];
			}

			if (l<qq)
			{
			   Kave = (K[l] + K[l+1]) / 2.0;
			   //heat from layer l to l+1
			   outQ[l] = 2000.0 * Kave * (temp[l] - temp[l+1]) / (Z[l+1] - Z[l]);
			}
			else
			{
			   //heat from bottom layer to deeper soil
			   outQ[l] = a * K[l] * (temp[l] - yr_avetj) / (200.0 - Z[l]);			   
			}

			dQ = outQ[l-1] - outQ[l];

			float dT = dQ / C[l];
 
			temp[l] += dT;

			if(Surf_Temp>=yr_avetj) temp[l] = min(Surf_Temp, max(yr_avetj, temp[l]));
			else temp[l] = min(yr_avetj, max(Surf_Temp, temp[l]));


	   } // l loop
 
  } // n

  for(l=1; l<=qq; l++)
  {
    float pQ1, pQ2, d_ice=0;
	float ps = h[l]*sts[l];
	float max_water = ps * 10000.0;//ps

    Vwater = water[1][l] * 10000.0;  // m water -> m3 water/layer/ha	

    if (temp[l]<=0.0) //freeze
    {
		if(Vwater>0.0&&ice[l]/10000.0<ps)
		{
		   pQ1 = -temp[l] * C[l]; //J/layer, heat release when T->0
		   pQ2 = Vwater * (4100000.0 - 2100000.0); //J/layer, water heat capacity

		   if (pQ1 > pQ2) //totally freeze
		   {
				dQQ = pQ2; //J/layer/ha
				temp[l] += (dQQ / C[l]);
				d_ice = Vwater; //m3 water/lay/ha
				Vwater = 0.0;

				ice[l] += d_ice;//m3 water/lay/ha
				water[1][l] = 0.0; //Vwater / 10000.0; // m water/layer

				//day_ice += d_ice/10000.0;
				//if(day_ice<0.0) day_ice = 0.0;

		   }
		   else //partially freeze
		   {
				dQQ = pQ1;
				temp[l] = 0.0;
				d_ice = dQQ / (4100000.0 - 2100000.0);

				if(d_ice > Vwater) 
					d_ice = Vwater;//m3 water/lay/ha
				else 
					d_ice = d_ice;

				Vwater -= d_ice;

				ice[l] += d_ice; //m3 water/lay/ha	
				
				water[1][l] -= (d_ice / 10000.0); // m water/layer
				//day_ice += d_ice/10000.0;// m water/layer
				//if(day_ice<0.0) day_ice = 0.0;
		   }

		   if(ice[l]/10000.0 > ps) ice[l] = ps * 10000.0;
		}
		else
		{
			d_ice = 0.0;
		}

    }
	else  //thawing
    {
		if (ice[l]>0.0&&temp[l]>0.0)
		{
		   pQ1 = temp[l] * C[l] * 0.2;//0.1;//0.05;
		   //pQ2 = 2.0 * ice[l] * (4100000.0 - 2100000.0);
		   pQ2 = ice[l] * (4100000.0 - 2100000.0);

		   if (pQ1 > pQ2) //totally thawing
		   {
			dQQ = pQ2;
			temp[l] -= dQQ / C[l];
			d_ice = ice[l];
			
			Vwater += d_ice;
			ice[l] = 0.0;
			water[1][l] += d_ice / 10000.0; // m water/layer

			//day_ice -= d_ice/10000.0;
			//if(day_ice<0.0) day_ice = 0.0;
		   }
		   else //partially thawing
		   {
			dQQ = pQ1;
			temp[l] = 0.0;
			//d_ice = -0.5 * pQ1 / (4100000.0 - 2100000.0);
			d_ice = pQ1 / (4100000.0 - 2100000.0);
			if(d_ice > ice[l]) d_ice = ice[l];
			Vwater += d_ice;
			ice[l] -= d_ice;// m3 water/layer/ha

			water[1][l] += d_ice / 10000.0; // m water/layer
			//day_ice -= d_ice/10000.0;
			//if(day_ice<0.0) day_ice = 0.0;
		   }
		   if(ice[l]>max_water) 
			   ice[l] = max_water;
		}
		else
		{ 
			d_ice = 0.0;
		}

    }	
    
	if (ice[l] < 0.0) ice[l] = 0.0;

    if (water[1][l] < 0.0) water[1][l] = 0.0;

    total_ice += (ice[l]/10000.0); //m water for profile

  }//layer loop
}
*/



float class_model::potential_et_manure()
{	
	// Thornthwaite equation for daily PET:
	float thorni, A, TTMP, x, Fws;

    x = yr_avetj / 14.0;
    if (x < 0.0) x = 0.0;
    thorni = 30.0 * (1.0 + powf(x, 2.0));
    if (thorni < 0.0) thorni = 0.0;
    A = (.49 + .0179 * thorni - .0000771 * powf(thorni, 2.0) + .000000675 * powf(thorni, 3.0));

    if ( air_temp >= 0.0 ) TTMP = air_temp;
    else TTMP = 0.0;
    
    x = 10.0 * TTMP / thorni;
    if (x< 0.0) x =0.0;    
    
	//Fws = 1.0 + wind_speed / 5.0;  
	//DayPET = (.015 * (1.6 * powf(x, A)) / 30.0) * Fws - 0.0025;
	Fws = 1.0;// + wind_speed / 20.0; 
	if(Fws>3.0) Fws=3.0;

	DayPET = (0.015 * (1.6 * powf(x, A)) / 30.0) * Fws;//0.015

	/*if(wind_speed>0.0)
	{
		float Fws = 1.0 + wind_speed / 20.0; 
		DayPET *= Fws;
	}*/
/*
	//Penman-Monteith method for daily PET
//Input data from measuremant
	float RHmean = humidity; //measured daily mean relative humidity (%)
	float Tmean = air_temp; //measured mean daily air temperature (degree C)
	float Tmax = max_temp; //measured mean daily air temperature (degree C)
	float Tmin = min_temp; //measured mean daily air temperature (degree C)
	float u2 = wind_speed; //measured wind speed (m/second)	//Brian multiply windspeed times 2
	float AtmoP = 101.325f; //atmospheric pressure (kPa), = 760 mmHg
	float N = Day_Hrs; //calculated maximum possible duration of sunshine or dalight hours (hours)
	float n = 0.58 * N; //actual duration of sunshine (hours)
	float z = 50.0; //elevation above sea level (m)

//Input data from DNDC-modeled results
	float Ra; //extraterrestrial radiation, (MJ/m2/day)
	//float Rs=PAR;//fix

	DayPETPAR = PAR;//tracking global radiation.
	float Albedo = albedo; //measured or calculated albedo
	DayPETAlbedo = albedo;//pulling albedo calculation from soil_temperature routine wet/dry soil algorithm.
  // Albedo = 0.0; //set Albedo to 0.0 whenever there isn't a crop


//Constants
	float G = 0.0; //soil heat flux density (MJ/m2/day)
	float As = 0.25; //refression constant, expressing the fraction of extraterestrial radiation reaching the earth on overcast days (n=0)
	float Bs = 0.50; //(As+Bs) = refression constant, expressing the fraction of extraterestrial radiation reaching the earth on clear days (n=N)
	double mu = 4.903 * pow(10.0, -9.0); //Stefan-Boltzmann constant (MJ/K^4/m^2/day)
	double gama = 0.000664742 * AtmoP; //psychrometric constatnt (kPa/degree C)
	float dewPointT = Tmean - (100 - RHmean) / 5;
	float delta = (4098.0 * (0.6108 * exp(17.27 * Tmean / (Tmean + 237.3)))) / ((Tmean + 237.3) * (Tmean + 237.3)); //slope vapour pressure curve (kPa/degree C)
	float E0_max = 0.6108 * exp(17.27 * Tmax / (Tmax + 237.3));
	float E0_min = 0.6108 * exp(17.27 * Tmin / (Tmin + 237.3));
	float E0_mean = 0.6108 * exp(17.27 * dewPointT / (dewPointT + 237.3));//E0_mean = 0.6108 * exp(17.27*Tmean/(Tmean+237.3));
	float Es = (E0_max + E0_min) * 0.5; //saturation vapour pressure (kPa)
	float Ea = E0_mean * RHmean / 100.0; //actual vapour pressure (kPa)
	// (Es - Ea) = saturation vapour pressure deficit (kPa)

	float KTmax = Tmax + 273.16;
	float KTmin = Tmin + 273.16;
	float Gsc = 0.082;//solar constant in MJ m-2 min-1
	float latRad = latitude * PI / 180;
	float decSun = 0.409 * sin((2 * PI) / 365 * jday - 1.39);
	float dr = 1 + 0.033 * cos((2 * PI) / 365 * jday);
	float ws = acos(-tan(latRad) * tan(decSun));
	Ra = 24 * 60 / PI * Gsc * dr * (ws * sin(latRad) * sin(decSun) + cos(latRad) * cos(decSun) * sin(ws));

	//float Ra= (Rs/(As + Bs * n / N));//fix
	float Rs = PAR;//global radiation input - PAR variable is mislabbled is really global radiation input from measuremenets/incedent solar rad/direct beam radiation/Rs/shorwave radiation.... was previously Rs=(As+Bs*n/N)*PAR;

	//float Rs = (As + Bs * n / N) * Ra; //measured or calculated solar or shortwave radiation (MJ/m2/day)
	float Rso = (0.75 + 0.00002 * z) * Ra;//calculated clear-sky radiation (MJ/m2/day)
	DayPETRa = Ra;
	DayPETRs = Rs;
	float Rns = (1.0 - Albedo) * Rs; //net solar or shortwave radiation (MJ/m2/day)
	float Rnl = mu * (powf(KTmax, 4.0) + powf(KTmin, 4.0)) / 2.0 *
		(0.34 - 0.14 * powf(Ea, 0.5)) *
		(1.35 * Rs / Rso - 0.35); //net outgoing longwave radiation (MJ/m2/day)
	float Rn = Rns - Rnl; //net radiation at the crop surface (MJ/m2/day)
	DayPETRN = Rn;
#ifdef MANURE
#else
	DayPETRN = Rn;
#endif
	float DPET = (0.408 * delta * (Rn - G) + gama * 900.0 / (Tmean + 273) * u2 * (Es - Ea)) / (delta + gama * (1.0 + 0.34 * u2));//mm/day

	DayPET = DPET / 1000.0; //m water/day
	DayPET = DPET / 1000.0; //m water/day
*/






	//newManure Addition
	float RHmean = humidity; //measured daily mean relative humidity (%)
	float Tmean = air_temp; //measured mean daily air temperature (degree C)
	float Tmax = max_temp; //measured mean daily air temperature (degree C)
	float Tmin = min_temp; //measured mean daily air temperature (degree C)
	float u2 = wind_speed; //measured wind speed (m/second)	
	float AtmoP = 101.325; //atmospheric pressure (kPa), = 760 mmHg
	float N = Day_Hrs; //calculated maximum possible duration of sunshine or dalight hours (hours)
	float n = 0.58 * N; //actual duration of sunshine (hours)
	float z = 50.0; //elevation above sea level (m)

//Input data from DNDC-modeled results
	float Ra = PAR; //extraterrestrial radiation, (MJ/m2/day)
	float Albedo = albedo; //measured or calculated albedo
	if (Albedo < 0)
	{
		if (air_temp < 0)
			Albedo = 0.9;
		else
			Albedo = 0.1;
	}


	//Constants
	float G = 0.0; //soil heat flux density (MJ/m2/day)
	float As = 0.25; //refression constant, expressing the fraction of extraterestrial radiation reaching the earth on overcast days (n=0)
	float Bs = 0.50; //(As+Bs) = refression constant, expressing the fraction of extraterestrial radiation reaching the earth on clear days (n=N)
	double mu = 4.903 * pow(10.0, -9.0); //Stefan-Boltzmann constant (MJ/K^4/m^2/day)
	double gama = 0.000664742 * AtmoP; //psychrometric constatnt (kPa/degree C)	

	float delta = (4098.0 * (0.6108 * exp(17.27 * Tmean / (Tmean + 237.3)))) / ((Tmean + 237.3) * (Tmean + 237.3)); //slope vapour pressure curve (kPa/degree C)
	float E0_max = 0.6108 * exp(17.27 * Tmax / (Tmax + 237.3));
	float E0_min = 0.6108 * exp(17.27 * Tmin / (Tmin + 237.3));
	float E0_mean = 0.6108 * exp(17.27 * Tmean / (Tmean + 237.3));
	float Es = (E0_max + E0_min) * 0.5; //saturation vapour pressure (kPa)
	float Ea = E0_mean * RHmean / 100.0; //actual vapour pressure (kPa)
	// (Es - Ea) = saturation vapour pressure deficit (kPa)

	float KTmax = Tmax + 273.16;
	float KTmin = Tmin + 273.16;

	float Rs = (As + Bs * n / N) * Ra; //measured or calculated solar or shortwave radiation (MJ/m2/day)
	float Rso = (0.75 + 0.00002 * z) * Ra;//calculated clear-sky radiation (MJ/m2/day)
	float Rns = (1.0 - Albedo) * Rs; //net solar or shortwave radiation (MJ/m2/day)
	float Rnl = mu * (powf(KTmax, 4.0) + powf(KTmin, 4.0)) / 2.0 * (0.34 - 0.14 * powf(Ea, 0.5)) * (1.35 * Rs / Rso - 0.35); //net outgoing longwave radiation (MJ/m2/day)
	float Rn = Rns - Rnl; //net radiation at the crop surface (MJ/m2/day)
	DayPETRN = Rn;
	float DPET = (0.408 * delta * (Rn - G) + gama * 900.0 / (Tmean + 273) * u2 * (Es - Ea)) / (delta + gama * (1.0 + 0.34 * u2)) / 1000;//mm/day //this should be calculated based on pan evap method
	float blah;
	//DayPET = DPET;
	if (DayPET < 0.0) DayPET = 0.0;
//end ManureAddition


	return(DayPET);
}

float class_model::potential_et(int ETM)
{	

		//Penman-Monteith method for daily PET
	//Input data from measuremant
		float RHmean = humidity; //measured daily mean relative humidity (%)
		float Tmean = air_temp; //measured mean daily air temperature (degree C)
		float Tmax = max_temp; //measured mean daily air temperature (degree C)
		float Tmin = min_temp; //measured mean daily air temperature (degree C)
		float u2 = wind_speed; //measured wind speed (m/second)	//Brian multiply windspeed times 2
		float AtmoP = 101.325f; //atmospheric pressure (kPa), = 760 mmHg
		float N = Day_Hrs; //calculated maximum possible duration of sunshine or dalight hours (hours)
		float n = 0.58 * N; //actual duration of sunshine (hours)
		float z = 50.0; //elevation above sea level (m)

	//Input data from DNDC-modeled results
		float Ra; //extraterrestrial radiation, (MJ/m2/day)
		//float Rs=PAR;//fix
		
		DayPETPAR=PAR;//tracking global radiation.
	     float Albedo = albedo; //measured or calculated albedo
	    DayPETAlbedo=albedo;//pulling albedo calculation from soil_temperature routine wet/dry soil algorithm.
      // Albedo = 0.0; //set Albedo to 0.0 whenever there isn't a crop


	//Constants
		float G = 0.0; //soil heat flux density (MJ/m2/day)
		float As = 0.25; //refression constant, expressing the fraction of extraterestrial radiation reaching the earth on overcast days (n=0)
		float Bs = 0.50; //(As+Bs) = refression constant, expressing the fraction of extraterestrial radiation reaching the earth on clear days (n=N)
		double mu = 4.903 * pow(10.0,-9.0); //Stefan-Boltzmann constant (MJ/K^4/m^2/day)
		double gama = 0.000664742 * AtmoP; //psychrometric constatnt (kPa/degree C)
		float dewPointT = Tmean - (100 - RHmean) / 5;
		float delta = (4098.0 * (0.6108 * exp(17.27*Tmean/(Tmean+237.3)))) / ((Tmean+237.3)*(Tmean+237.3)); //slope vapour pressure curve (kPa/degree C)
		float E0_max = 0.6108 * exp(17.27*Tmax/(Tmax+237.3));
		float E0_min = 0.6108 * exp(17.27*Tmin/(Tmin+237.3));
		float E0_mean = 0.6108 * exp(17.27*dewPointT/(dewPointT +237.3));//E0_mean = 0.6108 * exp(17.27*Tmean/(Tmean+237.3));
		float Es = (E0_max + E0_min) * 0.5; //saturation vapour pressure (kPa)
		
		//use leafTemp as the leaf surface temperature instead of air_temp
		if (leafTemp_C[1] > 0.0 && PGI[1]>0.0)
		{
		//	Es = 0.6108 * exp(17.27 * leafTemp_C[1] / (leafTemp_C[1] + 237.3)); // saturation vapour pressure at leaf surface 
		}

		float Ea = E0_mean * RHmean / 100.0; //actual vapour pressure (kPa)
		// (Es - Ea) = saturation vapour pressure deficit (kPa)

		float KTmax = Tmax + 273.16;
		float KTmin = Tmin + 273.16;
		float Gsc = 0.082;//solar constant in MJ m-2 min-1
		float latRad = latitude * PI / 180;
		float decSun = 0.409 * sin((2 * PI) / 365 * jday - 1.39);
		float dr = 1 + 0.033 * cos((2 * PI) / 365 * jday);
		float ws = acos(-tan(latRad) * tan(decSun));
		Ra = 24 * 60 / PI * Gsc * dr * (ws * sin(latRad) * sin(decSun) + cos(latRad) * cos(decSun) * sin(ws));

		//float Ra= (Rs/(As + Bs * n / N));//fix
		float Rs = PAR;//global radiation input - PAR variable is mislabbled is really global radiation input from measuremenets/incedent solar rad/direct beam radiation/Rs/shorwave radiation.... was previously Rs=(As+Bs*n/N)*PAR;

		//float Rs = (As + Bs * n / N) * Ra; //measured or calculated solar or shortwave radiation (MJ/m2/day)
		float Rso = (0.75 + 0.00002 * z) * Ra;//calculated clear-sky radiation (MJ/m2/day)
		DayPETRa=Ra;
		DayPETRs=Rs;
		float Rns = (1.0 - Albedo) * Rs; //net solar or shortwave radiation (MJ/m2/day)
		float Rnl = mu * (powf(KTmax,4.0)+powf(KTmin,4.0))/2.0 *
					(0.34 - 0.14*powf(Ea,0.5)) *
					(1.35 * Rs/Rso - 0.35); //net outgoing longwave radiation (MJ/m2/day)
		float Rn = Rns - Rnl; //net radiation at the crop surface (MJ/m2/day)
#ifdef MANURE
#else
		DayPETRN=Rn;
#endif
		float DPET = (0.408 * delta * (Rn - G) + gama * 900.0 / (Tmean + 273) * u2 * (Es-Ea)) / (delta + gama * (1.0 + 0.34 * u2));//mm/day

		DayPET = DPET / 1000.0; //m water/day
  DayPET = DPET / 1000.0; //m water/day

						
						


if(crop_flag[1]!=1&&crop_flag[2]!=1&&crop_flag[3]!=1&&crop_flag[4]!=1&&crop_flag[5]!=1&&crop_flag[6]!=1&&crop_flag[7]!=1)

{
			DayPET=DayPET*0.9;}
		else
		{DayPET*=1.0;}


	// Outputting Climate interim PET code

/*
	if(year==1 && jday==1)
	{CString TESTFILE;
	FILE *pFile=NULL;

	TESTFILE.Format("%s\\Record\\climate.txt", OUTPUT);
	pFile = fopen (TESTFILE,"w");
	fprintf(pFile, "jday,humidity,Ra,Albedo,E0_max,E0_min,E0_mean,Es,Ea,KTmax,KTmin,Rs,Rso,Rns,Rnl,Rn,DPET\n");
	fprintf(pFile, "%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,humidity,Ra,Albedo,E0_max,E0_min,E0_mean,Es,Ea,KTmax,KTmin,Rs,Rso,Rns,Rnl,Rn,DPET);
	fclose (pFile);
	}
	else
	{
	CString TESTFILE;
	FILE *pFile=NULL;	
	TESTFILE.Format("%s\\Record\\climate.txt", OUTPUT);//OUTPUTBatchFileName
	pFile = fopen (TESTFILE,"a");
	fprintf(pFile, "%1d,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f,%7.16f\n",jday,humidity,Ra,Albedo,E0_max,E0_min,E0_mean,Es,Ea,KTmax,KTmin,Rs,Rso,Rns,Rnl,Rn,DPET);
	fclose (pFile);
	}		
*/












	if(DayPET<0.0) DayPET=0.0;
	DayPETmod=DayPET;
	if(flood_flag==1) 
		DayPET *= 1.3;

    yr_PET += DayPET;

    
/*	/////////////////////////////////////////////////////////////////////////////////////

	//Priestley-Taylor equation for daily PET:
	//This subroutine calculates reference evapotranspiration     
	//     in a manner similar to Priestley and Taylor (1972).         
	//     To obtain crop evapotranspiration, multiplication with a    
	//     crop factor should be done.                                 
	//Refs.  : Kraalingen, D.W.G. van, W. Stol, 1997. Evapotranspiration   
	//         modules for crop growth simulation. Quantitative Approaches 
	//         in Systems Analysis No. 11. DLO Research Institute for      
	//         Agrobiology and Soil Fertility (AB-DLO), The C.T. de Wit    
	//         graduate school for Production Ecology (PE). Wageningen.    
	//         The Netherlands. 

	float LHVAP, PSCH, SIGMA, PTFAC, DATMTR;//ANGOT
    float RDLOI, RDLO, RDLII, RDLI, RDN;
    float DUMR1, DUMR2, DUMR3, DUMR4, DUMR5, DUMR6, DUMR;
	float RDD;//Daily short-wave radiation (J.m-2.d) 

	RDD = PAR * 1000000.0;

    LHVAP = 2454000.0;
	PSCH = 0.067;
    SIGMA = 0.00000005668;
	PTFAC = 1.42;

	if(RDD > 500000.0)
	{
        CString note;
		note.Format("WARNING from Potential_ET: Low short-wave radiation = %f MJ/m2/d", RDD/1000000.0);
		AfxMessageBox(note);
		//exit(0);
	} 
	
	//Vapor presure deficit
	//This subroutine calculates saturated vapour pressure and    
	//     slope of saturated vapour pressure. Parameters of the       
	//     formula were fitted on the Goff-Gratch formula used in the  
	//     Smithsonian Handbook of Meteorological Tables. The          
	//     saturated vapour following the Goff-Gratch formula is also  
	//     available as a subroutine. (Note that 1kPa = 10 mbar)       
	     
	float VPS;//Saturated vapour pressure, kPa
	float VPSL;//Slope of VPS at air_temp, kPa/C  

	if(air_temp< -20.0) air_temp = -20.0;
	if(air_temp > 50.0) air_temp = 50.0;
    VPS = 0.1 * 6.10588 * (float)exp(17.32491 * air_temp / (air_temp + 238.102));
    VPSL = 238.102 * 17.32491 * VPS / powf((air_temp + 238.102),2.0);

	//Longwave radiation (J/m2/s and J/m2/d) and net radiation according to Swinbank

	SASTRO();

	DATMTR = max(0.0, min(1.0, RDD / ANGOT));

      RDLOI = SIGMA * powf((air_temp + 273.16), 4.0);
      RDLII = DATMTR * (0.000000000000531 * powf((air_temp + 273.16),6.0) - RDLOI) / 0.7 + RDLOI;
      RDLO = 86400.0 * RDLOI;
      RDLI = 86400.0 * RDLII;
      RDN = (1.0 - RF) * RDD + RDLI - RDLO;//RF: Reflection (=albedo) of surface (-) 

	//Priestley and Taylor reference evapotranspiration
      DayPET = PTFAC * (RDN * (VPSL / (VPSL + PSCH))) / LHVAP;
*/
/*	if(ETM!=5)//input climate data don't include relative humidity
	{
		// Thornthwaite equation
		float thorni, A, TTMP, x, Fws;

		x = yr_avetj / 14.0;
		if (x < 0.0) x = 0.0;
		thorni = 30.0 * (1.0 + powf(x, 2.0));
		if (thorni < 0.0) thorni = 0.0;
		A = (.49 + .0179 * thorni - .0000771 * powf(thorni, 2.0) + .000000675 * powf(thorni, 3.0));

		if ( Surf_Temp >= 0.0 ) TTMP = Surf_Temp ;
		else TTMP = 0.0;
    
		x = 10.0 * TTMP / thorni;
		if (x< 0.0) x =0.0;    
    
		Fws = 1.0 + wind_speed / 5.0; 
		if(Fws>3.0) Fws=3.0;

 		DayPET = (0.015 * (1.6 * powf(x, A)) / 30.0) * Fws;//m water/day

	}
	else //input climate data include measured wind speed (m/s), radiation (MJ/m2/day) and relative humidity (%), 
*/

    return( DayPET );
}


// ===================  ACTUAL ET FROM PM @ Tleaf  ===================
// Returns DayAET in m d-1 (analogous to DayPET). Uses your daily met & canopy.
// Call order per day: leafTemp(ccwc) -> actual_et_PM_leaf(ccwc) -> your transpiration/soil code.
inline double clamp(double value, double min, double max) {
	return value < min ? min : (value > max ? max : value);
}

float class_model::actual_et_PM_leaf(int ccwc)
{
	// ---- met inputs ----
	const double RHmean = humidity;          // %
	const double Tmax = max_temp;          // C
	const double Tmin = min_temp;          // C
	const double Tmean = air_temp;          // C
	const double u2 = max(wind_speed, 0.1);  // m s-1
	const double PkPa = 101.325;           // kPa (or your site pressure)
	const double z = 50.0;              // m (site elevation if used in Rso)
	const double latRad = latitude * PI / 180.0;

	// ---- radiation (same style as in potential_et()) ----
	const double Rs = PAR;                // MJ m-2 d-1 (global shortwave)
	const double Gsc = 0.082;              // MJ m-2 min-1
	const double j = jday;
	const double dec = 0.409 * sin((2 * PI) / 365.0 * j - 1.39);
	const double dr = 1.0 + 0.033 * cos((2 * PI) / 365.0 * j);
	const double ws = acos(-tan(latRad) * tan(dec));
	const double Ra = 24.0 * 60.0 / PI * Gsc * dr * (ws * sin(latRad) * sin(dec) + cos(latRad) * cos(dec) * sin(ws)); // MJ m-2 d-1
	const double Rso = (0.75 + 2e-5 * z) * Ra;                                 // MJ m-2 d-1
	const double Rns = (1.0 - albedo) * Rs;                                  // MJ m-2 d-1

	auto es_kPa = [](double Tc) { return 0.6108 * exp(17.27 * Tc / (Tc + 237.3)); };
	const double Es_Tmax = es_kPa(Tmax), Es_Tmin = es_kPa(Tmin);
	const double Es = 0.5 * (Es_Tmax + Es_Tmin);                                 // kPa

	// actual vapour pressure Ea using your dewpoint proxy & RH
	const double dewPointT = Tmean - (100.0 - RHmean) / 5.0;
	const double Ea = es_kPa(dewPointT);                         // kPa

	// FAO-56 net longwave (MJ m-2 d-1), then Rn in W m-2
	const double mu = 4.903e-9; // MJ K-4 m-2 d-1
	const double KTmax = Tmax + 273.16, KTmin = Tmin + 273.16;
	const double Rnl = mu * ((pow(KTmax, 4.0) + pow(KTmin, 4.0)) / 2.0)
		* (0.34 - 0.14 * sqrt(max(Ea, 0.0)))
		* (1.35 * min(Rs / max(Rso, 1e-6), 1.0) - 0.35);
	const double Rn_MJ = Rns - Rnl;                                            // MJ m-2 d-1
	const double Rn_W = (Rn_MJ * 1e6) / 86400.0;                                  // W m-2
	const double G_W = 0.0;                                                  // canopy daily G0 (FAO-56)

	// ---- Tleaf from step A ----
	const double Tleaf = leafTemp_C[ccwc];

	// ---- aerodynamic resistance ra (FAO-56 neutral) ----
	const double h = CropHeight[ccwc];
	const double kvon = 0.41;
	double d = 0.67 * h, z0m = 0.123 * h, z0h = 0.1 * z0m;
	if (h < 0.12) { d = 0.08; z0m = 0.01476; z0h = 0.001476; }
	const double zref = 2.0;
	const double ra = (log((zref - d) / z0m) * log((zref - d) / z0h)) / (kvon * kvon * u2); // s m-1  // FAO-56

	// ---- canopy resistance rc (Jarvis-type; includes day_DWater) ----
	const double LAI = max(lai[ccwc], 0.0);
	const double water_stress =  clamp(day_DWater[ccwc], 0.0f, 1.0f);
	auto f_VPD = [](double vpd_kPa) { return 1.0 / (1.0 + vpd_kPa / 2.0); };
	auto f_T = [](double TleafC) { return 1.0 / (1.0 + max(TleafC - 35.0, 0.0) / 5.0); };
	const double gs_max = 0.01; // m s-1
	const double vpd_leaf = max(es_kPa(Tleaf) - Ea, 0.0); // kPa; saturation at Tleaf minus ambient Ea
	const double gs = gs_max * water_stress * f_VPD(vpd_leaf) * f_T(Tleaf);
	const double rc = 1.0 / max(gs * max(LAI, 0.1), 1e-5);              // s m-1

	// ---- PM evaluated at Tleaf (general form) ----
	auto Delta = [&](double Tc) { return 4098.0 * es_kPa(Tc) / ((Tc + 237.3) * (Tc + 237.3)); }; // kPa C-1
	const double gamma = 0.000665 * PkPa;                                      // kPa C-1
	const double Tair_K = (0.5 * (Tmax + Tmin)) + 273.15;
	const double Rgas = 287.05, Cp = 1004.0;
	const double rho = (PkPa * 1000.0) / (Rgas * Tair_K);                           // kg m-3

	const double num = Delta(Tleaf) * (Rn_W - G_W) + rho * Cp * (vpd_leaf) / ra; // W m-2
	const double den = max(Delta(Tleaf) + gamma * (1.0 + rc / ra), 1e-6);
	const double LE = num / den;                                                // W m-2

	// ---- convert to m d-1 and store ----
	const double ETa_mm = max(0.0, LE) * 86400.0 / 2.45e6; // mm d-1
	DayAET = ETa_mm / 1000.0;   // m d-1
	if (DayAET < 0.0) DayAET = 0.0;
	yr_AET += DayAET;
	return (float)DayAET;
}


void class_model::hour_loop(float hrPE0, float* DayFlux, float* dby_flux, int DroughtID, 
							int YieldToday, int drc, int scale, float ha, int livestock, int hr)
{
    int   l, i;
    float hrPE1, hrTrans, hrPE2, hrsnow_ev, hrPE3, dfIR, HrIrri=0.0,hrsoilIce_ev,hrPE25;
    float Throufall=0.0, dWW, Intercept, hrPonding_ev=0.0, dIT=0.0;

    dw = 0.0;

	if(IrriWater>0.0) 
	{
		if(IrriMethod==0)//Furrow irrigation
		{
			if(hr==1)
			{
				surf_water += IrriWater;
				IrriWater = 0.0;
				HrIrri = 0.0;
			}
		}
		else if(IrriMethod==1&&hr<=12)//Sprinkler
		{
			HrIrri = IrriWater / 12.0;
			surf_water += HrIrri;
		}
		else if(IrriMethod==2)//Surface drip
		{
			HrIrri = IrriWater / 24.0;
			surf_water += HrIrri;
		}
		else if(IrriMethod==3)//Deep drip
		{
			if(hr==12)
			{
				//HrIrri = IrriWater;
			}
			else
			{
				//HrIrri = 0.0;;
			}
			HrIrri = IrriWater / 24.0;
			int irriLayerDepth;//new for Huan
			irriLayerDepth = round(0.30 / h[1]); //new for Huan
			water[hr][irriLayerDepth] += HrIrri;//water[hr][5] += HrIrri;
			
			/*
			water[hr][irriLayerDepth] += HrIrri*0.4;
			water[hr][irriLayerDepth-1] += HrIrri * 0.3;
			water[hr][irriLayerDepth-2] += HrIrri * 0.15;
			water[hr][irriLayerDepth-3] += HrIrri * 0.10;
			water[hr][irriLayerDepth-4] += HrIrri * 0.05;
			*/
		}			
		
	}//end of irrigation water deliveral
		


		// Evaporation of water on leaves ///////////////////////////////////////////
		if(leaf_water > 0.0)
		{
			if ( hrPE0 * .5 < leaf_water )
			{
				leaf_water -= hrPE0 * 0.5;
				hrfol_ev = hrPE0 * 0.5;
				hrPE1 = hrPE0 * 0.5;
			}
			else
			{
				hrfol_ev = leaf_water;
				hrPE1 = hrPE0 - leaf_water;
				leaf_water = 0.0;
			}
		}
		else
		{
			hrfol_ev = 0.0;
			hrPE1 = hrPE0;
		}

		dfol_ev += hrfol_ev;

		
		// Evaporation of snow ////////////////////////////////////////////////////
		hrPE2 = hrPE1;

		evaporation_of_snow(hrPE2, &hrsnow_ev, &hrPE25);//test turrn off

		day_snow_ev += hrsnow_ev;//test turn off

		//could put evap of soil ice (top layers)
		

		
		if (snow_pack == 0.0 && total_ice>0) //occurs when soil is bare and soil ice is greater than zero
		{
			//evaporation_of_soilIce(hr,&hrPE3, &hrsoilIce_ev,hrPE25);//passing hour (hr), Potential evap, hourly soil Ice evap)

			//day_soilIce_ev += hrsoilIce_ev; //day accumulator of hourly soilIce evap.
			hrPE3 = hrPE25;  //turn this on if turning off evaporation of soilIce routine
		}
		else
		{

		hrPE3 = hrPE25;

		}
		
		hrPE3 = hrPE2;
		// Evaporation of water from surface water//////////////////////////////////
		if(day_WT >= 0.0) //WT is above ground
		{

			if (LandUse == 1)
			{
				surf_water = 0.1;//day_WT; //m 
			}

			for(int sa=1; sa<=q; sa++) 
			{
				float ps = h[sa]*sts[sa];
			//	water[hr][sa] = ps; //m/layer  // Brian turn off reset of water
			//	day_wfps[sa] = 1.0;
			}
		}
		
		if(surf_water>0.0) 
		{
			//calculate ponded evap
			float potPondEvap;
			potPondEvap = 0.0002 * (air_temp + 17.8) * (air_temp + 17.8);
			dayLength(jday, latitude);
			potPondEvap = (0.16 * (DayPETRs / dayLengthHr) + 0.61 * (air_temp) * (1 + 0.1 * wind_speed * wind_speed))/1000.0;
			if (air_temp <= 0.0) potPondEvap = 0.0;
			potPondEvap = min(0.0001, max(0.0, potPondEvap));
				 if(surf_water >= potPondEvap)
				 {
					 hrPonding_ev = potPondEvap;//Ftt * 					
				 }
				 else
				 {
					 hrPonding_ev = surf_water;//Ftt * 					
				 }
			 /*
			float Ftt;
			if(air_temp>0.0) Ftt = 1.0 * air_temp/40.0;//0.1
			else Ftt = 0.0;

			Ftt = max(0.0, min(1.0, Ftt));

			if(surf_water>=hrPE3) 
			{
				hrPonding_ev = hrPE3;//Ftt * 					
			}
			else 
			{
				hrPonding_ev = surf_water;//Ftt * 					
			}
			*/
		}
			else
				hrPonding_ev = 0.0;

		hrPE3 -= hrPonding_ev;
		surf_water -= hrPonding_ev;
			
			//flood_flag=0;
		//}
		
		day_pond_ev += hrPonding_ev;
	

		//Rainfall interception by foliage and throughfall ////////////////////////
		rain_intercept(hr, &Throufall, &Intercept );

		day_intercept += Intercept;
		
		// Ponding water and bypass flux (m/hr) ///////////////////////////////////
		pond_water_bypass_flux(Throufall, scale, ha, livestock);

		//water move downward and evaporation from soil profile////////////////////////////////////////////	

		if(WaterControl==1||crop[1]==30)//||WaterControl==2
		{
			wetland_water_delivery(hr, DayFlux, hrPE3);
			soil_EV(hr, DayFlux, hrPE3);
		}
		else
		{
			if(IrriRice_flag==1||(wetland_flag==1&&flood_flag==1))
			{
				paddy_water_delivery(hr, DayFlux, hrPE3);
				soil_EV(hr, DayFlux, hrPE3);
			}
			else //if(flood_flag == 0)
			{				

				
			 
				 soil_EV(hr, DayFlux, hrPE3); 
			 
				

					if(total_ice==0.0) // won't get soil evap if total ice is greater than zero. 
					{
						water_delivery(hr, DayFlux, hrPE3);
							
						
					}
					else
					{
					}
				
			}			
		}
	//}
		//if(hr<24) 
		//{
		//	for ( l = 1; l <= q; l++ ) water[hr+1][l] = water[hr][l];				
		//}

    //} //end of hr loop

	/* Summary/conversion at end of a day */

	if(hr<24) 
	{
		for ( l = 1; l <= q; l++ ) water[hr+1][l] = water[hr][l];				
	}
	else
	{
		for ( l = 1; l <= q; l++ )
		{
			//day_soil_ev += day_layer_soil_ev[l];
			//day_layer_soil_ev[l] = 0.0;
			
			//float fldcapw = h[l] * sts[l] * fldcap[l];
			//if(st[1]>=12) water[24][l] = fldcapw;

			float ps = h[l]*sts[l];
			day_wfps[l] = (water[24][l] / ps);
			day_wfps[l] = min(1.0, max(0.00000001, day_wfps[l]));	
		}
 
		 /*if(runoff_pool>0.0)
		 {
			 float dRF;
			 if(SCSuse==0) dRF = runoff_pool;// * 0.5;
			 else dRF = runoff_pool * (1.0 - ManningRoughOverflow) * 0.1;

			 day_runoff += dRF;
			 runoff_pool -= dRF;
		 }*/
	}
}


void class_model::evaporation_of_snow(float hrPE2, float* hrsnow_ev, float* hrPE25 )
{
 
	

   if ( snow_pack > 0.0 && hrPE2 > 0.0 )
    {
		if ( snow_pack >= hrPE2 )
		{
			*hrsnow_ev = hrPE2*.3;
			snow_pack -= hrPE2*.3;
			*hrPE25 = hrPE2*.7;
		}
		else
		{
			*hrsnow_ev = snow_pack*.3;
			*hrPE25 = hrPE2 - snow_pack*.3;
			//snow_pack = 0.0;
		}
    }
    else
    {
	

        *hrPE25 = hrPE2;
		*hrsnow_ev = 0.0;
    }
	
 //Brian old code here ...code above allows only 20% of the snow to be evaporated due to sublimation


/*

   if ( snow_pack > 0.0 && hrPE2 > 0.0 )
    {
		if ( snow_pack >= hrPE2 )
		{
			*hrsnow_ev = hrPE2;
			snow_pack -= hrPE2;
			*hrPE3 = 0.0;
		}
		else
		{
			*hrsnow_ev = snow_pack;
			*hrPE3 = hrPE2 - snow_pack;
			snow_pack = 0.0;
		}
    }
    else
    {
        *hrPE3 = hrPE2;
		*hrsnow_ev = 0.0;
    }		
*/	
}

void class_model::evaporation_of_soilIce(int hr, float* hrPE3, float* hrsoilIce_ev,float hrPE25)
{
	float sev,totalSoilIceSev,totalhrPE;
	int EVL = (int)(0.1 / h[1]);//top 10 cm
	//*hrPE3 = hrPE25;
	totalSoilIceSev = 0.0;
	totalhrPE = 0.0;

	if (hrPE25 > 0.0)
	{
		sev = hrPE25 / (float)EVL; //partition the soilice evap across the top 5cm layers
		for (int l = 1; l <= EVL; l++)//loop from top layer to the 5 cm layer
		{
			float wiltptw = h[l] * sts[l] * wiltpt[l];//calculate wilting point water

			if ((water[hr][l] + ice[l] / 10000.0) > wiltptw)//test to see if water in layer + ice in layer > wilting point water
			{

				if ((ice[l] / 10000.0) >= sev)//if ice in the layer is greater than 
				{
					ice[l] -= sev * 10000.0;//reduce ice in the layer by  ice evap potential
					totalSoilIceSev += sev;
					totalhrPE += sev;
				}
				else
				{
					totalSoilIceSev += ice[l]/10000.0;
					totalhrPE += (ice[l] / 10000.0);
					ice[l] = 0.0;
					
				}


			}
			else
			{
				totalSoilIceSev += 0.0;
				totalhrPE += 0.0;

			}


		}

		*hrsoilIce_ev = totalSoilIceSev;
		*hrPE3 = hrPE25-totalhrPE;

	}
	else
	{
		totalSoilIceSev = 0.0;
		totalhrPE = 0.0;
		*hrsoilIce_ev = totalSoilIceSev;
		*hrPE3 = hrPE25 - totalhrPE;
	}
}
void class_model::rain_intercept(int hr, float* Throufall, float* Intercept )
{
    float RIRI, max_leaf_water;
	float Tlai = lai[1]+lai[2]+lai[3];

    max_leaf_water = Tlai * 0.0001*rainFallInterFactor; //m water

    f_TTT = 1.0;

    if ( TTT > 0.0 && hr <= (int)(TTT + 1) )
    {
		if(TTT==24)
		{
		RIRI = (float)(TTT * RI / ((int)(TTT)));	
		}
		else
		{
			RIRI = (float)(TTT * RI / ((int)(TTT + 1)));	
		}

		*Throufall = RIRI;
		*Intercept = 0.0;
		
		//test intercept
	//	surface_litter = rcvl[1]+rcl[1]+rcr[1]+stub1+stub2+stub3;
		if ( Tlai > 0.0 )
		{

			if ( leaf_water < max_leaf_water )
			{
				*Intercept = (0.1 * Tlai * RIRI);
				if ( Tlai > 10.0 ) *Intercept = RIRI;
				if ( (*Intercept) > max_leaf_water - leaf_water )
					*Intercept = max_leaf_water - leaf_water;

				leaf_water += *Intercept;
				*Throufall = RIRI - (*Intercept);
				f_TTT = 1.0 - leaf_water / (TTT * RI);
			}
			else
			{
				*Throufall = RIRI;
				*Intercept = 0.0;
			}

		}
		else
		{
			*Throufall = RIRI;
			*Intercept = 0.0;
		}

		//test intecept
    }
    else
    {
		RIRI = 0.0;
		*Intercept = 0.0;
		*Throufall = 0.0;
    }
}

float class_model::pond_water_bypass_flux(float Throufall, int scale, float ha, int livestock)
{

	if(st[1]<12)
	{
		if(SCSuse==0)
		{
			if (Throufall>0.0&&sslope>0.0) 
			{
				//float VegeIndex = (1.0 - PresentBiomass[1]/8000.0);
				//float MoistIndex = day_wfps[1] / fldcap[1];
				float aslope = sslope / 90.0;//degree -> fraction	
				if(total_ice > 0.0) aslope = 0.9;
				if(aslope>1.0) aslope=1.0;

				float RainFactor = 0.8 * TTT * clay[1];
				RainFactor = min(1.0, max(0.0, RainFactor));
				
				float SufaceRunoff;
				if(TTT>18.0) SufaceRunoff = 0.4 * Throufall;
				else SufaceRunoff = aslope * RainFactor * Throufall;
				day_runoff += SufaceRunoff; //m water/day
				Throufall -= SufaceRunoff;
			}
		}
		else
		{
			if(scs_runoff>0.0)
			{
				float hr_runoff;
				
				if(scs_runoff>=Throufall) 
				{
					hr_runoff = Throufall;
					scs_runoff -= hr_runoff;
					Throufall = 0.0;
				}
				else
				{
					hr_runoff = scs_runoff;
					Throufall -= scs_runoff;//was broken
					scs_runoff = 0.0;
					
				}

				day_runoff += hr_runoff;//m water/day
			}
		}
	}

	if(jday==135)
	{
		float blah;
		blah=1.0;
	}
    surf_water += Throufall;

	Throufall = 0.0;

//brian surf_water allocation to runoff
	////surface adjustment setup....................................

	
/*
if(jday==1)
{
	
char junk[80];

CString TESTFILE;
FILE *pFile=NULL;
TESTFILE.Format("%s\\Record\\Runoff.txt", OUTPUT);
pFile = fopen (TESTFILE,"r");
fscanf(pFile, "%f",&runMulti);
fscanf(pFile, "%f",&runMultiN);
fclose (pFile);
}
///pay attention for other modificaitons.......................................
*/

//runMulti=0.3;//0.3





if ( surf_water > 0.0 && total_ice > 0.0 && air_temp>0.0)//&& air_temp>0.0
{ 
	float aslope = max(sslope / 90.0,0.005)*0.3;//runMulti
	day_runoff += aslope * surf_water;
	surf_water -= aslope * surf_water;
}




    if ( surf_water > 0.0 && by_passf > 0.0 && total_ice == 0.0 && WRL>q)
    {
		//byflow = surf_water * by_passf * 8.0;
		byflow = surf_water * by_passf;
		surf_water -= byflow;

		OutWater[1][1] += byflow;
    }
    else
    {
		byflow = 0.0;
    }

		//brian surfWater runoff in season
	if(surf_water > 0.0 && total_ice ==0.0 && WRL>q)
	{
		float aslope = max(sslope / 90.0,0.005);
	//	aslope=0.0;
	day_runoff += aslope * surf_water;
	surf_water -= aslope * surf_water;
	}

    return(0 );
}
float class_model::clay_cracking(int hr)
{
	int l;//layer
	float clayCrack,clayCrackDepth, clayCrackDepthL,textureCrack;
	int clayCrackLayer;
	//prefFlowDepth

	clayCrackDepth = 0.10;
	clayCrackDepth = prefFlowDepth;
	clayCrackDepthL = clayCrackDepth / h[1] + 1;
	//textureCrack = -20.689 * pow(clay[l], 3) + 17.407 * pow(clay[l], 2) - 1.497 * clay[l] + 0.0496;
	//textureCrack = min(1.0, max(0.0, textureCrack));
	clayCrackLayer = 1;

	//if (st[1] == 11 && l == clayCrackLayer && hr == 1)//Test to see if soil texture is clay and only test first hour for clay formation.
	//{


		for (l = 1; l <= clayCrackLayer; l++) //from top to bottom layer
		{
			textureCrack = -20.689 * pow(clay[l], 3) + 17.407 * pow(clay[l], 2) - 1.497 * clay[l] + 0.0496;
			textureCrack = min(1.0, max(0.0, textureCrack));
			double ps = h[l] * sts[l];//m, porosity
			double wiltptw = h[l] * sts[l] * wiltpt[l];//wilting point water (m)
			double fldcapw = h[l] * sts[l] * fldcap[l];//fieldcapacity water (m)
			double waterDry = wiltptw + ((fldcapw - wiltptw) * 0.60);
			//textureCrack = -20.689 * pow(clay[l], 3) + 17.407 * pow(clay[l], 2) - 1.497 * clay[l] + 0.0496;
			textureCrack = 22.669 * pow(clay[l], 4) - 37.727 * pow(clay[l], 3) + 18.618 * pow(clay[l], 2) - 1.219 * clay[l] + 0.035;

			textureCrack = min(1.0, max(0.0, textureCrack));

			//test if soil dryness is below 50% holding capacity. If so
			if (clayCrackAccum[l] < 0.0)
			{
				clayCrackAccum[l] = 0.0;
			}
			if (water[hr][l] < waterDry)//if water hr1 in layer is less than 50% of holding capacity then clayCrackAccumulator will be adjusted
			{
				clayCrackAccum[l] += textureCrack;//increase the accumulator to determine if clay crack has formed. 
				if (clayCrackAccum[l] >= 1.0)clayCrackAccum[l] = 1.0;
			}
			else
			{

				//moved Crack recession into Water_delivery. 
				/*
				if (clayCrackAccum[l] > 0.0)
				{
					clayCrackAccum[l] -= (1.0 - textureCrack);
				}
				*/
				if (clayCrackAccum[l] < 0.0)clayCrackAccum[l] = 0.0;
				//clayCrackAccum[l] = 0.0;


			}
			if(clayCrackAccum[l]>0.0&&l<q)//proceed to test next layer since crack has formed in this layer
			{
				if(l+1< clayCrackDepthL)clayCrackLayer++;
			}
			

			//newSat[1] = sks[1] * (3.2 * clayCrack); // calculate the new conductivity to be used to calculate amount of water to segment below. 
			//newSat[i]=newSat[1]+0.01;
			//sks[i]=oldSat[1] + clayCrack/10.0;
		}
//	}
		/*
		if(averageWFPS> clayWFPS && clayCrack==0.0)  //condition if wfps goes above the clay formation condition and there are no cracks then saturation should be set to normal
		{newSat[1]=sks[1];}
		if(averageWFPS> clayWFPS && clayCrack>0.0) //reduce the clay cracking slowly assuming that wfps is above clay cracking condition
		{clayCrack -= 7.0;
		if(clayCrack<0.0)
		{clayCrack=0.0;}
		newSat[1]=sks[1]*(3.2 * clayCrack);
		}
		if(temp[1]<0.0)
		{clayCrack=0.0;
		newSat[1]=sks[1];
		}*/
	return 0;
}


// --- Begin van Genuchten Support ---

template <typename T>
T clamp(T val, T min_val, T max_val) 
{
	return max(min_val, min(val, max_val));
}




float class_model::water_delivery(int hr, float* DayFlux, float hrPE3)
{

	//Li's water delivery
    int    l;
    float  W01, DeliWater,clayPref=0.0; 
	double AvaWater = 0.0;
	float  lost_ev_water = 0.0;
	float  OutFlow = 0.0;


	if(total_ice <= 0.0) //water delivery doesn't occur if any ice present in the soil profile. 
	{
		
#pragma loop(hint_parallel(8)
		for ( l = 1; l <= q; l++ ) //from top to bottom layer
		{	
			
			
			//insert saxton pedotransfer function for the testing of adjustment of water holding capacity based on changes in SOC
			if(SoilStructEffect==1.0)//start SoilStructEffect ..only if turned on through user input.
			{
				if(l==1&&hr==1)//for calc of the relative changes in soil water contents
					{
					

					
						float sandContent,soilOM,surfaceSOC,newFC,newWP;
						float relWP, relFC;
							
						if(st[l]==1)
						{sandContent=0.85;}
						else if(st[l]==2)
						{sandContent=0.80;}
						else if(st[l]==3)
						{sandContent=0.63;}
						else if(st[l]==4)
						{sandContent=0.15;}
						else if(st[l]==5)
						{sandContent=0.41;}
						else if(st[l]==6)
						{sandContent=0.53;}
						else if(st[l]==7)
						{sandContent=0.09;}
						else if(st[l]==8)
						{sandContent=0.29;}
						else if(st[l]==9)
						{sandContent=0.52;}
						else if(st[l]==10)
						{sandContent=0.08;}
						else if(st[l]==11)
						{sandContent=0.13;}
						else
						{sandContent=0.15;}

						soilOM=ini_ttoo[1]*100*1.72; //calculate OM%
						float layerDepth;
						layerDepth = h[1] * l;
						int layerSOC=1;						
						while(layerDepth<.2)
						{
						layerDepth=h[1]*layerSOC;
						layerSOC=layerSOC+1;
						}
						surfaceSOC=0.0;
						int iSOC;
						for(iSOC=1;iSOC<=(layerSOC-1);iSOC++)
						{
						surfaceSOC+=soc[iSOC];//calculate surface SOC
						}
						float bulk_density = mmm[1] / 10000.0 / h[1] / 1000.0;//! soil bulk density (kg/dm3)
						soilOM=(surfaceSOC/100000/bulk_density/20)*100*1.72;

						//new Wilting point
						newWP=-0.024*sandContent+0.487*clay[1]+0.006*soilOM+0.005*sandContent*soilOM-0.013*clay[1]*soilOM+0.068*sandContent*clay[1]+0.031;
						//newWP=-0.024*sandContent+0.487*clay[1]+0.006*soilOM+0.005*sandContent*soilOM-0.013*clay[1]*soilOM+0.068*sandContent*clay[1]+0.031;
						newWP=(newWP+0.14*newWP-0.02)/sts[1];
						//newFC=-0.251*sandContent+0.195*clay[1]+0.049*soilOM+0.006*sandContent*soilOM-0.027*clay[1]*soilOM+0.452*sandContent*clay[1]+0.299;

						//new field capacity
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
								relFC=pow(relFC,35);//35
								}
							else
								{
								relWP=pow(relWP,1);
								relFC=pow(relFC,35);//35
								}

							//added year==1 to the field capacity depth allocation. In data I assigned in the fldcap[l] when it was just assigning in just at depth....note this is the problem!!!


							
							
							
						}
									
					
						//Setting new Field Capacity/Wilting Point based on saxton recalcuations above
							
						if( ((fldcap[l]*relFC)-(wiltpt[l]*relWP))<.1  ||  ((fldcap[l]*relFC)-(wiltpt[l]*relWP))>.50 || (fldcap[l]*relFC)>.9 || (fldcap[l]*relFC)<.14 )
						{
						
						wiltpt[l]=wiltpt[l];
						fldcap[l]=fldcap[l];
					    ini_fldcap=fldcap[1];
						fldcapOLD[l]=fldcap[l];
					//	WaterPoolMax=WaterPoolMax;
						oldWP=oldWP;
						oldFC=oldFC;



						}
						else
						{
						
						wiltpt[l]=wiltpt[l]*relWP;
						fldcap[l]=fldcap[l]*relFC;
						ini_fldcap=fldcap[1];
						fldcapOLD[l]=fldcap[l];
					//	WaterPoolMax*=relFC;
						oldWP=newWP;
						oldFC=newFC;
						}
						
						//end fc wp
					
					}	
				//end new saxton code
				}//end SoilStructEffect statement


			double ps = h[l]*sts[l];//m, porosity
			double wiltptw = h[l] * sts[l] * wiltpt[l];
			double fldcapw = h[l] * sts[l] * fldcap[l];



			if(byflow>0.0)//with bypass flow
			{		
				W01 = (fldcap[l] - water[hr][l] / ps) / (fldcap[l] - wiltpt[l]);

				if ( W01 >= 1.0 ) DeliWater = byflow;
				if ( W01 <= 0.0 ) DeliWater = (float)0.0;
				if ( W01 > 0.0 && W01 < 1.0 ) DeliWater = 0.01 * byflow * W01;

				if(DeliWater > byflow) DeliWater = byflow;

				water[hr][l] += DeliWater;
				byflow -= DeliWater;
				if(byflow < 0.0) byflow = 0.0;

				day_bypass_influx += DeliWater;
				DeliWater = 0.0;
			}
			else
			{
				DeliWater = 0.0;
			}	  

			// Water available for and entering in each layer 

			//afps = 1.0 - water[hr][l] / ps;//air-filled porosity
			//pswc = ps * afps; // air depth, m
			
			//preset off pedotransfer water conductivity rates. Tend to work better than default values.
			float newSKS;
			if(st[1]==1)//sand
			{
				newSKS=0.1145;
			}
			else if(st[1]==2)//loamy sand
			{
				newSKS=0.0912;
			}
			else if(st[1]==3)//sandy loam
			{
				newSKS=0.0503;
			}
			else if(st[1]==4)//silt loam
			{
				newSKS=0.012;
			}
			else if(st[1]==5)//loam
			{
				newSKS=0.0186;
			}
			else if(st[1]==6)//sand clay loam
			{
				newSKS=0.0078;
			}
			else if(st[1]==7)//silty clay loam
			{
				newSKS=0.0059;
			}
			else if(st[1]==8)//clay loam
			{
				newSKS=0.0045;
			}
			else if(st[1]==9)//sandy clay
			{
				newSKS=0.0008;
			}
			else if(st[1]==10)//silty clay
			{
				newSKS=0.0039;
			}
			else if(st[1]==11)//clay
			{
				newSKS=0.00078;
			}
			else
			{
				newSKS=sks[1];
			}
			
			if(l==1)
			{
				if(surf_water>0.0 && nWTL>l)
				{
					
					if(surf_water>newSKS)
					{
					AvaWater=newSKS;
					surf_water-=newSKS;
					day_water_in +=AvaWater;
					}
					else
					{
					AvaWater=surf_water;
					surf_water=0.0;
					day_water_in +=AvaWater;
					}
								
				}
				else
				{
					AvaWater = 0.0;
				}				
			}
			else //if layer>1 then calculated OutWater of the layer above is added to AvaWater
			{
				
			AvaWater = OutWater[l-1][hr]+clayPref;//old_lh_out_water;
			}

			
			if (l == 1 && hr == 1&&prefFlowCheck==1)
			{
				clay_cracking(hr);//turns on Clay Cracking -----------------------
			}
			
			//Water flux from the ABOVE layer is added here from AvaWater = OutWater[l-1][hr]

			water[hr][l] += AvaWater * (1.0 - clayCrackAccum[l]);//water[hr][l] is at this point above field capacity
			clayPref = (AvaWater * clayCrackAccum[l]);
		
			
			//-------------------------Clay Crack Recession---------------------------------------------------------
			float textureCrack;
			textureCrack = 22.669 * pow(clay[l], 4) - 37.727 * pow(clay[l], 3) + 18.618 * pow(clay[l], 2) - 1.219 * clay[l] + 0.035;//caclulates the crack formation intensity based on clay content
			textureCrack = min(1.0, max(0.0, textureCrack));
			if (clayCrackAccum[l] > 0.0 && AvaWater > 0.0 && hr == 1 && l < q)//only reduces cracks in first hour   && clayCrackAccum[l+1]==0.0
			{
				clayCrackAccum[l] -= (1.0 - textureCrack)*prefFlowRecov;//---reduces by 25% rate
				if (clayCrackAccum[l] < 0.0)clayCrackAccum[l] = 0.0;
			}



			//code for outputting water layer movement
/*
	if(hr<=1 && l==1)
	{


		if(year==1&&flagHeader==1)
			{
			CString TESTFILE;
			FILE *pFile=NULL;

			TESTFILE.Format("%s\\Record\\water.txt", OUTPUT);
			pFile = fopen (TESTFILE,"w");
			fprintf(pFile, "jday,year,layer,hr,day_WFPS,clayCrackAccum[1],clayCrackAccum[2],clayCrackAccum[3]\n");
			fprintf(pFile, "%1d,%1d,%1d,%1d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",jday,year,l,hr,(water[hr][l] / ps), clayCrackAccum[1], clayCrackAccum[2], clayCrackAccum[3]);
			fclose (pFile);
			flagHeader=0;
			}
			else
			{
			CString TESTFILE;
			FILE *pFile=NULL;


			TESTFILE.Format("%s\\Record\\water.txt", OUTPUT);//OUTPUTBatchFileName
			pFile = fopen (TESTFILE,"a");
			fprintf(pFile, "%1d,%1d,%1d,%1d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",jday,year,l,hr,(water[hr][l] / ps), clayCrackAccum[1], clayCrackAccum[2], clayCrackAccum[3]);
			fclose (pFile);
			}

	}
	*/


			//------ End Clay Crack Recession ------------------------------------------
			 
			AvaWater = 0.0;
			//water movement when layer is over-saturated 
	
			
			
			
			//begin Hooghoudt equation;
			int drainageDepth;//sets drainage depth;

			
			double qDrain;//drainage discharge rate m of water hr-1
			double keDrain;
			double mWTh;//water table level above the drain at midpoint between drains in meters
			double conDrain;//constant drain;
			double deDrain;//effective depth of impermeable layer below drain in meters 

			
			
			//float totalqDrain;//This is available flow per hour that can flow out. 

			LRA1=0;

						
			drainageDepth = int(drainageDepthM/h[1]);

			    cdrainDays[366];
				stdrain[366];
				enddrain[366];
				cdraindepth[366];
				cdrain_num;

					
		//controlled drainage		
			if(cdrain_num==0)//if controlledDrainage is not on controlledDrainageDepthM==0.0 || controlledDrainageStartDay>jday
			{
				controlledDrainageDepth = q+1;
			}
			else if(hr==1&&l==1)
			{	
			  

			  if(jday>=stdrain[count_Drain] && cdrainDays[count_Drain]>0)
			  {
				controlledDrainageDepth = int(cdraindepth[count_Drain]/h[1]);
				cdrainDays[count_Drain]-=1;
			  }
			  else if(cdrainDays[count_Drain]==0)
			  {
				count_Drain+=1;
				cdrain_num-=1;
			  }
			}
				
		

			if(TileIrriRate>0 && drainageDepth==l && TileIrriDays>0 && hr==1)
			{
			water[hr][l] +=TileIrriRate;
		    day_irri += TileIrriRate;
			TileIrriDays-=1;
			if(TileIrriDays==0)
				{
					TileIrriRate=0.0;
				}

			}
			

			
			//water table effect on field capacity
		SwcWTEffect2=0;		
		if(SwcWTEffect2>0)
		{
			float distanceToWT,clayWTFactor;
			distanceToWT=(nWTL*h[1])-(l*h[1]);
			distanceToWT=min(2.0,max(0,distanceToWT));
			clayWTFactor=38.095*pow(clay[l],2)-47.857*clay[l]+17.033;
			clayWTFactor=(304.76*pow(clay[l],2)-382.86*clay[l]+136.27);
			clayWTFactor=min(68.0,max(1,clayWTFactor));

			if(distanceToWT<1.0)
			{
				fldcap[l]=fldcapOLD[l]+(1.0-fldcapOLD[l])*pow((100-distanceToWT*100)/100,clayWTFactor);
				fldcap[l]=min(0.98,max(wiltpt[l],fldcap[l]));

			}
			else
			{
				fldcap[l]=fldcapOLD[l];
			}
		}//end if SwcWTEffect2
			//end water table effect on field capacity
			
			keDrain=keDrainM*sks[1];
		
			mWTh=((nWTL*h[1])-(drainageDepth*h[1]))*-1;//max(0.0,((drainageDepth*h[1])-(WTL*h[1])));
			

			if(mWTh<0)mWTh=0;

			conDrain=3.55-1.6*(dDrain/spaceDrain)+2*pow((dDrain/spaceDrain),2);//solving for se
			deDrain=dDrain/(1+(dDrain/spaceDrain)*((8/3.17*log(dDrain/reDrain))-conDrain));

			qDrain= (4*keDrain*mWTh*(2*deDrain+mWTh))/pow(spaceDrain,2);

			
			//water movement when layer water > field capacity			
			double LRA = 1.0;//0.9 * (0.1439 * (float)log(sks[l]) + 1.0879);//0.1
			LRA = min(1.0, max(0.001, LRA));
			
			if(l==1)//need to set totalqDrain when layer == 1 so as to initialize totalqDrain 
			{
			totalqDrain=qDrain;
			if(TileIrriRate>0)
			{
				totalqDrain=0.0;
			
			}
			}
			
				//code for outputting water layer movement
			/*
				if(hr<=1 && l==1)
				{	
					
					
					if(waterOut==1&&year==1&&flagHeader==1)
						{
						CString TESTFILE;
						FILE *pFile=NULL;

						TESTFILE.Format("%s\\Record\\water.txt", OUTPUT);
						pFile = fopen (TESTFILE,"w");
						fprintf(pFile, "jday,year,layer,hr,day_WFPS,OutWater[l][hr],WTL,qDrain,totalqDrain,day_WT,layerH,water[1][1],water[1][2],water[1][3],water[1][4],water[1][5],water[1][6],water[1][7],water[1][8],water[1][9],water[1][10],water[1][35],water[1][36],water[1][37],water[1][38],water[1][39],water[1][40],water[1][41],water[1][42]\n");
						fprintf(pFile, "%1d,%1d,%1d,%1d,%7.4f,%7.4f,%1d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",jday,year,l,hr,(water[hr][l] / ps),OutWater[l][hr],WTL,qDrain,day_WT,h[1],water[1][1],water[1][2],water[1][3],water[1][4],water[1][5],water[1][6],water[1][7],water[1][8],water[1][9],water[1][10],water[1][35],water[1][36],water[1][37],water[1][38],water[1][39],water[1][40],water[1][41],water[1][42]);
						fclose (pFile);
						flagHeader=0;
						}
						else 
						{
						CString TESTFILE;
						FILE *pFile=NULL;
						
						
						TESTFILE.Format("%s\\Record\\water.txt", OUTPUT);//OUTPUTBatchFileName
						pFile = fopen (TESTFILE,"a");
						fprintf(pFile, "%1d,%1d,%1d,%1d,%7.4f,%7.4f,%1d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",jday,year,l,hr,(water[hr][l] / ps),OutWater[l][hr],WTL,qDrain,totalqDrain,day_WT,h[1],water[1][1],water[1][2],water[1][3],water[1][4],water[1][5],water[1][6],water[1][7],water[1][8],water[1][9],water[1][10],water[1][35],water[1][36],water[1][37],water[1][38],water[1][39],water[1][40],water[1][41],water[1][42]);
						fclose (pFile);
						}
					
				}
			*/	

			//Begin Capilillary Rise
			
			
			int capRiseDepthLayer = 1;
			capRiseDepthLayer = round(0.3/h[1])+1;
			if (day_irri > 0.0 && IrriMethod==3) // Only perform capillary rise at for sub surface drainage when irrigation occurs/ computationally heavy
			{
				for (int l = capRiseDepthLayer - 1; l >= 2; l--) // Loop from second-to-bottom layer up to the top
				{
					// Calculate total pore space (volume) for above and below layers
					float ps_above = h[l]; //* sts[l];
					float ps_below = h[l + 1];//* sts[l + 1]

					// Calculate volumetric water content (theta) for each layer
					float theta_above = water[hr][l] / ps_above;
					float theta_below = water[hr][l + 1] / ps_below;

					// --- Assign van Genuchten parameters for the above layer based on soil texture ---
					// --- Inline van Genuchten parameters for above layer ---
					float theta_r_above, theta_s_above, alpha_above, n_above;
					if (st[l] == 1) { theta_r_above = 0.045f; theta_s_above = 0.43f; alpha_above = 14.5f; n_above = 2.68f; }
					else if (st[l] == 2) { theta_r_above = 0.057f; theta_s_above = 0.41f; alpha_above = 12.4f; n_above = 2.28f; }
					else if (st[l] == 3) { theta_r_above = 0.065f; theta_s_above = 0.41f; alpha_above = 7.5f; n_above = 1.89f; }
					else if (st[l] == 4) { theta_r_above = 0.067f; theta_s_above = 0.45f; alpha_above = 3.6f; n_above = 1.56f; }
					else if (st[l] == 5) { theta_r_above = 0.078f; theta_s_above = 0.43f; alpha_above = 3.6f; n_above = 1.56f; }
					else if (st[l] == 6) { theta_r_above = 0.100f; theta_s_above = 0.39f; alpha_above = 2.7f; n_above = 1.48f; }
					else if (st[l] == 7) { theta_r_above = 0.100f; theta_s_above = 0.36f; alpha_above = 1.9f; n_above = 1.41f; }
					else if (st[l] == 8) { theta_r_above = 0.095f; theta_s_above = 0.38f; alpha_above = 1.9f; n_above = 1.41f; }
					else if (st[l] == 9) { theta_r_above = 0.100f; theta_s_above = 0.38f; alpha_above = 1.5f; n_above = 1.37f; }
					else if (st[l] == 10) { theta_r_above = 0.070f; theta_s_above = 0.36f; alpha_above = 1.1f; n_above = 1.31f; }
					else { theta_r_above = 0.068f; theta_s_above = 0.38f; alpha_above = 1.1f; n_above = 1.09f; }

					// --- Inline van Genuchten parameters for below layer ---
					float theta_r_below, theta_s_below, alpha_below, n_below;
					if (st[l + 1] == 1) { theta_r_below = 0.045f; theta_s_below = 0.43f; alpha_below = 14.5f; n_below = 2.68f; }
					else if (st[l + 1] == 2) { theta_r_below = 0.057f; theta_s_below = 0.41f; alpha_below = 12.4f; n_below = 2.28f; }
					else if (st[l + 1] == 3) { theta_r_below = 0.065f; theta_s_below = 0.41f; alpha_below = 7.5f; n_below = 1.89f; }
					else if (st[l + 1] == 4) { theta_r_below = 0.067f; theta_s_below = 0.45f; alpha_below = 3.6f; n_below = 1.56f; }
					else if (st[l + 1] == 5) { theta_r_below = 0.078f; theta_s_below = 0.43f; alpha_below = 3.6f; n_below = 1.56f; }
					else if (st[l + 1] == 6) { theta_r_below = 0.100f; theta_s_below = 0.39f; alpha_below = 2.7f; n_below = 1.48f; }
					else if (st[l + 1] == 7) { theta_r_below = 0.100f; theta_s_below = 0.36f; alpha_below = 1.9f; n_below = 1.41f; }
					else if (st[l + 1] == 8) { theta_r_below = 0.095f; theta_s_below = 0.38f; alpha_below = 1.9f; n_below = 1.41f; }
					else if (st[l + 1] == 9) { theta_r_below = 0.100f; theta_s_below = 0.38f; alpha_below = 1.5f; n_below = 1.37f; }
					else if (st[l + 1] == 10) { theta_r_below = 0.070f; theta_s_below = 0.36f; alpha_below = 1.1f; n_below = 1.31f; }
					else { theta_r_below = 0.068f; theta_s_below = 0.38f; alpha_below = 1.1f; n_below = 1.09f; }



					// --- Compute effective saturation (Se) and matric potential (ψ) using van Genuchten equation ---
					float Se_above = (theta_above - theta_r_above) / (theta_s_above - theta_r_above);
					Se_above = clamp(Se_above, 0.01f, 0.999f); // Clamp to avoid numerical instability
					float m_above = 1.0f - 1.0f / n_above;
					float psi_above = -pow(pow(Se_above, -1.0f / m_above) - 1.0f, 1.0f / n_above) / alpha_above;

					float Se_below = (theta_below - theta_r_below) / (theta_s_below - theta_r_below);
					Se_below = clamp(Se_below, 0.01f, 0.999f);
					float m_below = 1.0f - 1.0f / n_below;
					float psi_below = -pow(pow(Se_below, -1.0f / m_below) - 1.0f, 1.0f / n_below) / alpha_below;

					//---if wanting to use Unsaturated Conductivity instead ---

						// Mualem–van Genuchten parameters
						//float m_below = 1.0f - 1.0f / n_below;
						//float l_param = 0.5f; // Commonly used pore-connectivity parameter

						// Compute unsaturated hydraulic conductivity
						//float K_unsat = sks[l + 1] * pow(Se_below, l_param) * pow(1.0f - pow(1.0f - pow(Se_below, 1.0f / m_below), m_below), 2.0f);

						//then replace below Darcy's Law using K_unsat.
						//float cap_rise_flux = -K_unsat * moisture_gradient; // Darcy's Law
					
					//---if wanting to use Unsaturated Conductivity instead ---
					 
					
					// Compute vertical distance between layer centers
					float dz = (h[l] + h[l + 1]) / 2.0f;

					// Compute moisture gradient (matric potential difference per unit depth)
					float moisture_gradient = (psi_above - psi_below) / dz;

					// Convert field capacity and wilting point from WFPS to volumetric
					float fldcap_vol_above = fldcap[l] * sts[l];
					float wiltpt_vol_below = wiltpt[l + 1] * sts[l + 1];

					// Capillary rise condition: water moves up if upper layer is drier and below field capacity
					if (theta_below > theta_above && theta_above < fldcap_vol_above)//(theta_below > theta_above && theta_above < fldcap_vol_above)
					{
						float K = sks[l + 1]*0.0001; // Saturated hydraulic conductivity of the lower layer
						float cap_rise_flux = -K * moisture_gradient; // Darcy's Law
						cap_rise_flux = max(0.0f, cap_rise_flux); // Only allow upward flow

						float max_cap_rise = 0.0001f; // 0.1 mm/hr
						cap_rise_flux = min(cap_rise_flux, max_cap_rise);


						// Limit rise by available water above wilting point in the lower layer
						float min_water_below = wiltpt_vol_below * h[l + 1];
						float available_water_below = water[hr][l + 1] - min_water_below;
						available_water_below = max(0.0f, available_water_below);

						// Actual water that can rise is the minimum of potential and available
						float actual_rise = min(cap_rise_flux, available_water_below);

						
						float leachNO3Flow = 0.0;
						float leachNH4Flow = 0.0;
						leachNO3Flow = actual_rise * 1000.0;
						leachNH4Flow = actual_rise * 1000.0;
						if (leachNO3Flow > 0.5)leachNO3Flow = 0.5;
						leachNO3Flow= leachNO3Flow * no3[l + 1];
						if (leachNH4Flow > 0.1)leachNH4Flow = 0.1;
						leachNH4Flow = leachNH4Flow * nh4[l + 1];
						if ((no3[l + 1] - leachNO3Flow) < 0.0)leachNO3Flow = 0.0;
						if ((nh4[l + 1] - leachNH4Flow) < 0.0)leachNH4Flow = 0.0;
						no3[l] += leachNO3Flow;
						nh4[l] += leachNH4Flow;
						no3[l + 1] -= leachNO3Flow;
						nh4[l + 1] -= leachNH4Flow;
						

						// Update water content in both layers
						water[hr][l] += actual_rise;
						water[hr][l + 1] -= actual_rise;
					}
					float wfps = water[hr][l] / h[l] / sts[l];
					if (fabs(wfps-fldcap[l])<0.001f)
					{
						
						

						//float leachNO3Flow = 0.0;
						//float leachNH4Flow = 0.0;
						//leachNO3Flow = 0.9;
						//leachNH4Flow = 0.9;
						//if (leachNO3Flow > 0.9)leachNO3Flow = 0.9;
						//leachNO3Flow = leachNO3Flow * no3[l + 1];
						//if (leachNH4Flow > 0.9)leachNH4Flow = 0.9;
						//leachNH4Flow = leachNH4Flow * nh4[l + 1];
						//if (no3[l + 1] - leachNO3Flow < 0.0)leachNO3Flow = 0.0;
						//if (nh4[l + 1] - leachNH4Flow < 0.0)leachNH4Flow = 0.0;
						//no3[l] += leachNO3Flow;
						//nh4[l] += leachNH4Flow;
						//no3[l + 1] -= leachNO3Flow;
						//nh4[l + 1] -= leachNH4Flow;
						

					}


				}
			}
			
			
			// --- End Capillary Rise Logic ---



			



			
			



			if (water[hr][l]>fldcapw && WRL>l)//brian added l<q if water (cm)(hr) is greater than field capacity of the layer then tip by making outWater
			{
		
	
				if(water[hr][l+1]<h[l+1]*sts[l+1] && l<q  || l==q && DrainEfficiency==1.0)//if Water below layer is not saturated or if it is saturated but there is a positive q   totalqDrain>0 && WTL==l ||
				{

					if (water[hr][l + 1] > 0.0)
					{
						if (l + 1 == nWTL && (water[hr][l] - fldcapw) >= 0.0) //try to distrubute extra water down profile if it is filled with water. This is just ensuring things are tied up. //tests that the layer below current layer is water table and water is above field capacity
						{
							double extraWTwater;
							extraWTwater = water[hr][l] - fldcapw;//water above field capacity
							water[hr][l] = fldcapw;//water in a layer is set to field capacity (i.e. water+extraWater should be what was in the layer before it got split apart0
							int counter;
							counter = 1;//helps keep track of the current layer iteration/
							while (extraWTwater > 0 && (l + counter) < q)//if extrawater(i.e. the water in current layer that is above field capacity is greater than zero) and  [layer + counter] is still above the bottom soil layer)
							{
								if ((counter + l) < q && water[hr][l + counter] < (h[counter + 1] * sts[counter + 1])) //if [layer+counter] is still 1 layer above the bottom layer and water in the layer below the current layer is less than saturation (this is the condition true to distribute some of the excess water from the above layers to fill up to saturation)
								{
									double fillup;
									fillup = (h[counter + 1] * sts[counter + 1]) - water[hr][l + counter]; //fillup calculates the difference to get the soil layer to saturation
									if (extraWTwater > fillup)//if extrawater is greater than the fillup amount
									{
										water[hr][l + counter] += fillup;//just add water to the calculated layer up to fillup amount
										extraWTwater -= fillup;//remove the fillup amount from extrawater pool
									}
									else
									{
										water[hr][l + counter] += extraWTwater;//else fillup water is greater than extrawater and thus all of extra water can go into the calulated layer
										extraWTwater = 0.0;//extra water is now zero
									}


									counter += 1;

								}
								counter = q;



							}
							water[hr][l] += extraWTwater;



						}//end l+1==WTL

					}

					


					
					if(LRA1==1)
					{
					OutWater[l][hr] = aCurve * (water[hr][l]-fldcapw)* (float)pow(10.0,(-bCurve/((water[hr][l]-fldcapw)/((sts[1]*h[1])-fldcapw))));
					double maxOutWater;
					maxOutWater=(h[l]*sts[l]) -fldcapw;//recession curve can result in water outFlux greater than water[hr][l];
					OutWater[l][hr]=min(maxOutWater,max(0.0,OutWater[l][hr]));
					}
					else
					{

					OutWater[l][hr] = LRA * (water[hr][l] - fldcapw);//OutWater is calculated as water above fld capacity
					

					double unSatK, theta, thetaS,thetaR, sE;//Unsaturated Conductivity calculation based on water content and kSat. Vereeken et al., 1990
					theta=(water[hr][l] / ps)*sts[l];
					thetaS=sts[l];
					thetaR=((h[l] * sts[l] * wiltpt[l])/ps)*sts[l];
					sE=(theta-thetaR)/(thetaS-thetaR);
					unSatK=sks[l]*powf(sE,3.5);
					
					
					if (OutWater[l][hr] > unSatK) { 
						OutWater[l][hr] = unSatK; }
					//OutWater[l][hr] = unSatK;
					//unSatK=ksat*(o/osat)n
					}

				   
					
					//water table adjustment







					
					if(water[hr][l+1]<=(h[l+1]*sts[l+1]*fldcap[l+1]))//test for WTL adjustment for first condition if water below layer is less than equal to field capacity
					{
						if(nWTL<=l+1 && l+2<=q)//set WTL to layer below
						{

						nWTL=l+2;
						WTL=l+2;
						day_WT=-WTL*h[1];
						}
					}
					

				//	WTL=(int)(-day_WT/h[1])+1;
				}//end if(WTL>l)
				else//if water below is saturated or is layer q bottom layer and is not free drain
				{

	

					if(drainageDepth>=l) //if drains are below the layer then calculate how much excess water can move to drains drainageDepth>=l
					{

						double excessWTwater;
						excessWTwater=water[hr][l]-fldcapw;
					
					if(LRA1==1)//testing recession curve for water modeling
					{
					excessWTwater = aCurve * (water[hr][l]-fldcapw)* (float)pow(10.0,(-bCurve/((water[hr][l]-fldcapw)/((sts[1]*h[1])-fldcapw))));
					double maxOutWater;
					maxOutWater=h[l]*sts[l] -fldcapw;//recession curve can result in water outFlux greater than water[hr][l];
					excessWTwater=min(maxOutWater,max(0.0,excessWTwater));
					}
					


						if(excessWTwater>0)
						{
								double nDrainLeach,nDrainLeachF;
								//float maxNO3F,actNO3F,moveN,partitN,NLeach;
								double actNO3F, NLeach;
												//maxNO3F=0.004;//0.0022 //0.005 and chemistry at 7.5 worked  // A Scaling Factor for calcuting maximum N that can move per layer per time step. 
											
												actNO3F=1.0;//0.4
												//moveN=0.90;	//0.65 //fraction of N that is mobilized in a layer with water movement
												//partitN=0.95;//fraction N that is moved to next layer and difference is preferrentially leached //0.95 worked ok
								if(totalqDrain>excessWTwater && controlledDrainageDepth>l)//&& controlledDrainageDepth>l	
												{
												day_leach_water+=excessWTwater;
												day_tile_water+=excessWTwater;
												TileWater[l][hr]=excessWTwater;
												totalqDrain-=excessWTwater;

												//n Leach to Tiles
												
												
												nDrainLeachF=excessWTwater*1000/3;
												nDrainLeachF = min(1.0, max(0.1, nDrainLeachF));
												//nDrainLeachF=0.0;
												
												//code for handling Nitrogen movement when water table present.
												for(int iz=l; iz<=(q); iz++)
												{
													float maxNO3,actNO3;
													//maxNO3F=pow(no3[iz],2)/1000;
													//maxNO3F=min(0.9,max(0.5,maxNO3F));
													maxNO3=maxNO3F*no3[iz];
													actNO3=no3[iz]*(nDrainLeachF*actNO3F);
													

													if(actNO3>maxNO3)
													{
														actNO3=maxNO3;//never happens should remove condition
													}
													
													if(iz<q)
													{
													no3[iz+1]+=(actNO3*moveN*partitN); //layer below move NO3 down
													no3[iz]-=(actNO3*moveN); //layer remove NO3
													day_leach_NO3+=(actNO3*(moveN)*(1-partitN));
													NLeach=(actNO3*(moveN)*(1-partitN));
													}
													else
													{
														no3[iz]-=(actNO3*moveN*(1-partitN));
														day_leach_NO3+=(actNO3*moveN*(1-partitN));
														NLeach=(actNO3*moveN*(1-partitN));
													}
													
//write out drainage of N
/*
if(year==17)
	{CString TESTFILE;
	FILE *pFile=NULL;

	TESTFILE.Format("%s\\Record\\Nwater.txt", OUTPUT);
	pFile = fopen (TESTFILE,"w");
	fprintf(pFile, "jday,year,hr,layer,totalqDrain,maxNO3,actNO3,no3[iz],no3[iz+1],day_leach_NO3,waterFlow,NLeach\n");
	fprintf(pFile, "%1d,%1d,%1d,%1d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",jday,year,hr,iz,totalqDrain,maxNO3,actNO3,no3[iz],no3[iz+1],day_leach_NO3,excessWTwater*1000,NLeach);
	fclose (pFile);
	}
	else if(year>17)
	{
	CString TESTFILE;
	FILE *pFile=NULL;
	
	
	TESTFILE.Format("%s\\Record\\Nwater.txt", OUTPUT);//OUTPUTBatchFileName
	pFile = fopen (TESTFILE,"a");
	fprintf(pFile, "%1d,%1d,%1d,%1d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",jday,year,hr,iz,totalqDrain,maxNO3,actNO3,no3[iz],no3[iz+1],day_leach_NO3,excessWTwater*1000,NLeach);
	fclose (pFile);
	}	
*/

												
												
   }


												
												water[hr][l] -= excessWTwater; //remove water from layer to drains
												excessWTwater=0.0;
													if(nWTL==l)
													{
													nWTL=l+1;
													WTL=l+1;
													day_WT=-WTL*h[1];
													}
												}
												else if(totalqDrain>0.0 && controlledDrainageDepth>l)//&& controlledDrainageDepth>l
												{
												 day_leach_water+=totalqDrain;
												 day_tile_water+=totalqDrain;
												 TileWater[l][hr]=totalqDrain;
												
												 
												 nDrainLeachF=totalqDrain*1000/3;
												nDrainLeachF = min(1.0, max(0.1, nDrainLeachF));
												//nDrainLeachF=1.0;
												
												for(int iz=l; iz<=(q); iz++)
												{
													float maxNO3,actNO3;
													//maxNO3F=pow(no3[iz],2)/1000;
													//maxNO3F=min(0.9,max(0.5,maxNO3F));
													maxNO3=maxNO3F*no3[iz];
													actNO3=no3[iz]*(nDrainLeachF*actNO3F);
													
													if(actNO3>maxNO3)
													{
														actNO3=maxNO3;
													}
													
													if(iz<q)
													{
													no3[iz+1]+=(actNO3*moveN*partitN); //layer below move NO3 down
													no3[iz]-=(actNO3*moveN); //layer remove NO3
													day_leach_NO3+=(actNO3*(moveN)*(1-partitN));
													NLeach=(actNO3*(moveN)*(1-partitN));
													}
													else
													{
													no3[iz]-=(actNO3*moveN*(1-partitN));
														day_leach_NO3+=(actNO3*moveN*(1-partitN));
														NLeach=(actNO3*moveN*(1-partitN));
													}


												}
												

												 water[hr][l] -= totalqDrain;//remove water from layer to drains
												 excessWTwater-=totalqDrain;
												 totalqDrain=0.0;
												 excessWTwater=0.0;
												}








						}
					
	}//end if drainageDepth>l
					
					  
									if(water[hr][l]>ps ) //if water in cm is greater than saturation will move water back up the profile//was ps && nWTL==(l+1)
									{
									    double extraWTwater,excessFCwater;
										extraWTwater=(water[hr][l]-ps);
										water[hr][l]=ps;
									
										if(nWTL==l+1)
										{
										nWTL=l;
										WTL=nWTL;
										day_WT=-WTL*h[1];
										}
										excessFCwater=ps-fldcapw;
											
								



										
									//whatever water is left after drainage code extracts is then allocated here to be pushed upwards over the layers above
								
										int counter=1;
											
											while(extraWTwater>0)//adding water to layers above
											{   

										
												if(l-counter>=1)
												{	
													double fldcapw1 = h[l-counter] * sts[l-counter] * fldcap[l-counter];
													double saturatedContent =h[l-counter]*sts[l-counter];
													water[hr][l-counter]+=extraWTwater;
													extraWTwater=0.0;
													
													if(water[hr][l-counter]>(saturatedContent))
														{
														extraWTwater=water[hr][l-counter]-saturatedContent;
														water[hr][l-counter]=saturatedContent;
														
														
														 if(nWTL==(l-counter+1))
														 {
															nWTL=l-counter;
															nWTL=max(1,nWTL);
															WTL=l-counter;
															WTL=max(1,WTL);
															day_WT=-WTL*h[1];
														 }
														counter+=1;
													
														}
													else //enough water to fill next layer above field capacity but not to saturation
													{
														//nothing to do ...water[hr][l-1] already got water added above
													extraWTwater=0.0;
													}
												}
												else //saturation reached surface layer
												{
												day_runoff+=extraWTwater;//surf_water
												extraWTwater=0.0;
										
												}
											}//end while
																				
									}//end if water[hr][l]>ps
									

OutWater[l][hr] = 0.0;
if(OutWater[l][hr]<0.0) OutWater[l][hr]=0.0;

//OutWater[l][hr] = 0.0;
//end turn things off




				}//end else if water below is saturated	






				

						
			}//end if (water[hr][l]>fldcapw && WRL>l) if water isn't above field capacity in a layer
			if (water[hr][l] <= fldcapw) //if water is less than field capacity then no water movement
			{
				//if(water[hr][l]>wiltptw)
				//	OutWater[l][hr] = 0.0 * (water[hr][l] - wiltptw);//0.005
				//else
					OutWater[l][hr] = 0.0;
					TileWater[l][hr]=0.0;
			}
			
			//testing a unsaturated flow below field capacity
			/*
			else if(water[hr][l] <= fldcapw) // water is below field capacity
			{
				if (water[hr][l] > wiltptw) // allow slow drainage between wilting point and field capacity
				{
					float theta = (water[hr][l] / ps) * sts[l];
					float thetaS = sts[l];
					float thetaR = ((h[l] * sts[l] * wiltpt[l]) / ps) * sts[l];
					float sE = (theta - thetaR) / (thetaS - thetaR);
					sE = min(1.0f, max(0.01f, sE)); // clamp for stability
					float unSatK = sks[l] * powf(sE, 9.5f); // Vereecken-style unsat K //higher values for powf exponent result in slower leaching losses ..9.5 or 3.5
					float maxDrain = water[hr][l] - wiltptw;

					OutWater[l][hr] = min(unSatK, maxDrain);
				}
				else
				{
					OutWater[l][hr] = 0.0;
				}

				TileWater[l][hr] = 0.0;
			}
			*/
			//end testing 
			


			water[hr][l] -= OutWater[l][hr];//water that moves out of layer should be removed from water in layer
			if(water[hr][l]<0.0) water[hr][l] = 0.0; 

			//day_leach_water += (0.1 * OutWater[l][hr]);
			//OutWater[l][hr] *= 0.85;
			
			//water move upward

			//float ps = h[l]*sts[l];
			day_wfps[l] = (water[hr][l] / ps);
			day_wfps[l] = min(1.0, max(0.00000001, day_wfps[l]));//will loose water if water for some reason is above saturation
			
			////////////////////////////////////////////////////////////water_leaching
	
			float dDID = 1.0 * (-0.1375 *(float)log(clay[1]) + 0.0188);//1.0
			dDID = max(0.0, min(1.0, dDID));	
			float dDVD = 0.0;//0.00001
			dDID=0.0;
			if(flood_flag==1) 
			{
				dDID *= WaterLeakRate;
				dDVD *= WaterLeakRate;
			}

			DayFlux[l] += (OutWater[l][hr]);

			
			if(l==q)
			{
			  
				



				  

			
				if(OutWater[l][hr] > 0.0)
				{
					day_leach_water+=OutWater[l][hr];



			    

				//defines how much is going to tile drainage and how much to leaching...
				  


  
				}//end if(OutWater[l][hr]>0.0

			
					

									
				if(byflow>0.0)
				{
					day_leach_water += byflow;
					byflow = 0.0;
				}

				if(day_WT>0.1) 
				{
					day_leach_water += (day_WT - 0.1);//why is water table going above field?????
					//this doesn't account for all the water
					
					day_WT = 0.1;
				}
				
			}//end if l==q
			
				
		}//end of layer loop, l
	}//if ice = 0;

	return(0);
}




float class_model::paddy_water_delivery(int hr, float* DayFlux, float hrPE3)
{
	float FLF;
    
	//if(flood_flag==1) FLF = 0.03 / powf((1.0 + clay[1]), 4.0);
	//else FLF = 0.01 / powf((1.0 + clay[1]), 4.0);
	
	float leak_water = WaterLeakRate/24.0;

	float ps = h[1]*sts[1];
	
	if(flood_flag==1) water[hr][1] = ps;
	if (surf_water>0.0 && WTL==0 && surf_water > leak_water)
	{
		surf_water -= leak_water;
	}
	else if (surf_water > 0.0 && surf_water < leak_water && WTL == 0)
	{
		leak_water = surf_water;
		surf_water = 0.0;

	}
	else
	{
		leak_water = 0.0;
	}
	day_leach_water += leak_water; //paddy leachinf

    /*for ( l = 1; l <= q; l++ )
    {
	
		if(l==1) 
			day_water_in += surf_water;
	   
		OutWater[l][hr] = surf_water;

		if(flood_flag==1) 
			water[hr][l] = ps;

		DayFlux[l] += (OutWater[l][hr]);

		if (l == q) 
		{
			day_leach_water += OutWater[l][hr];
		}
			
		if (water[hr][l]>ps) water[hr][l]=ps;
    }*/

	return(0);
}

void class_model::annu_water_budget(float dby_flux)
{


	
	if(day_leach_water>0.0&&snow_pack>0.0)//Brian was turning off runoff when snowpack was present.
	{

		//brian experimental texture factor for leaching water based on texture.

		/*
		float textureFactor;
		textureFactor=pow(clay[1],0.7);
		
		day_runoff+= day_leach_water * textureFactor;
		day_leach_water *= (1-textureFactor);
		
		//day_runoff+= day_leach_water * (1-DeepPerc);
		//day_leach_water *= DeepPerc;
		*/

		
		double textureFactor;//texture factor when snowpack exists to reallocate leaching to runoff
			textureFactor=0.000000019194*powf((clay[1]*100.0),2.997);//0.5 to turn it to half

			if(clay[1]>0.35)
				textureFactor=1.0;
				
			//textureFactor=0.0;
			textureFactor=0.0;
			textureFactor=min(1.0,max(0.0, textureFactor));

		day_runoff+= day_leach_water * textureFactor;
		day_leach_water *= (1-textureFactor);
		
		//day_runoff += day_leach_water;
		//day_leach_water = 0.0;
	}
	if (jday == 305 && year == 1)
	{
		float blah;
		blah = 1.0;

	}
    day_transp = act_DayAT;
    day_evapor = day_snow_ev + dfol_ev + day_pond_ev + day_soil_ev+day_soilIce_ev;
	//day_leach_water = day_pwater + dby_flux; //leached water, not available for plants
	day_ET = day_snow_ev + dfol_ev + day_pond_ev + day_transp + day_soil_ev+day_soilIce_ev;
    
	yr_prec_water += precipitation;

	//yr_water_in += day_water_in; //m water
	//day_water_in = 0.0;

	yr_bypass_in +=	day_bypass_influx;  
	day_bypass_influx = 0.0;
	yr_soilIce_ev += day_soilIce_ev;
	yr_snow_ev += day_snow_ev;
    yr_fol_ev += dfol_ev;
//	yr_pond_ev += day_pond_ev;

	//yr_soil_ev += day_soil_ev;
	//day_soil_ev = 0.0;

	//yr_trans += day_transp;  
	//day_transp = 0.0;

	yr_ET += day_ET;   
	yr_intercept += day_intercept;
	
}

void class_model::water_diffusion(int hr)
// Diffusion of water(Upward as positive) in unsaturated and thawing zone
// Its slower, so calculated independently layer by layer.
{
	int L, L1, Bottom_Type, First, Next_Layer;
	float A, SW[250], Water_Diff[250], THET1, THET2, DBAR, Depth2;
	float Water_Flux[250], Bottom_Depth=2.0;

/*  float SW[MaxL], Water_Diff[MaxL],
	THET1, THET2, DBAR, Depth2, A, F;
  int L, L1, Next_Layer, First, Last, Bottom_Type;*/

//Bottom_Type =1 for frozen layer, =2 for water table, 3: neither
  Bottom_Type=3;
  L1 = q-1;
  A=0.0;
  for(L=0; L<q; L++)  
  {
     A += h[L];//??? h[0]
     /*if(temp[L]<0.0) 
	 {
		Bottom_Type=1;
		L1=L-1;
		L=q;   //exit loop
     }
     else if (L>WRL) 
	 {
		Bottom_Type=2;
		L1=L;
		if(L1>q-1) L1=q-1;
		L=q;   //exit loop
     }*/
  }

  /*if(Bottom_Type==3)  
  {
     L1=q-1;
	 F=(water[hr][L1]-fldcapw)*h;
     water[hr][L1]=fldcapw;
     Water_Table-=F/(Porosity[L1]-Field_Capacity[L1]);
     if(Water_Table>Bottom_Depth) Water_Table=Bottom_Depth;
  }*/

  for(L=1; L<=q; L++) 
  {
     Water_Diff[L]=0.0;
     SW[L]=water[hr][L];
  }

// estimating diffusivity DBAR.
  First =1;
  for(L=First; L<q; L++)  
  {
	 float wiltptw = h[L] * sts[L] * wiltpt[L];
	 float fldcapw = h[L] * sts[L] * fldcap[L];
     Next_Layer=L+1;
     THET1=water[hr][L]-wiltptw;
     if (THET1 < 0.0)  THET1=0.0;
     THET2=water[hr][Next_Layer]-wiltptw;
     if (THET2 < 0.0)  THET2=0.0;
     //DBAR=0.88*exp(35.4*(THET1+THET2)*0.5);
	 DBAR=0.00001*exp(35.4*(THET1+THET2)*0.5);
     if (DBAR >100.0)  DBAR=100.0;
     Depth2 = 2.0 * h[L];
     Water_Diff[L]=DBAR*(THET2-THET1)/(Depth2/2.0);
// Duing diffusion, the water content in the receiving layer
// cannot be higher than the average of the two layers.
   /*  A=(water[hr][L]*h + water[hr][Next_Layer]*h)/Depth2;
     if(Water_Diff[L] > 0.0) 
	 {
       F = (A-water[hr][L]) *h;
       Water_Diff[L] = min(Water_Diff[L], F);
     }
     else 
	 {
       F = (water[hr][Next_Layer]-A) *h;
       Water_Diff[L] = max(Water_Diff[L], F);
     }*/

     SW[L] += Water_Diff[L]/h[L];
     SW[Next_Layer] -= Water_Diff[L]/h[L];
  }  //end for loop

 /* if(Bottom_Type==2) 
  {    //water table in CN layers
     Drain_W +=(SW[L1]-fldcapw)*h;
     if(SW[L1]<fldcapw)  
	 {
       F=fldcapw-SW[L1];
       SW[L1]=fldcapw;
       Water_Table +=F/(sts*h-fldcapw);
     }
     else  
	 {
       Water_Table=L1*h;
       F=(SW[L1]-fldcapw)/(sts*h-fldcapw)*h;
       Water_Table-=F;
     }
  }   //end bottom_type=2
  else if(Bottom_Type==3) 
  {
       F=(SW[L1]-fldcapw)*h;
       Water_Table -= F/(sts*h-fldcapw);
       if(Water_Table>Bottom_Depth) Water_Table=Bottom_Depth;
       Drain_W += F;
       SW[L1]=fldcapw;
  }*/

  for(L=0; L<=L1; L++)  water[hr][L] = SW[L];

  for(L=First; L<L1; L++)  
  {
     A = - Water_Diff[L];
     Water_Flux[L] += A;
     Next_Layer = L + 1;
     //N_Mass_Flow(Next_Layer, A);
  }

}


float class_model::wetland_water_delivery(int hr, float* DayFlux, float hrPE3)
{
    int    l;
    float  W01, DeliWater, AvaWater=0.0; //OutWater
	float  lost_ev_water = 0.0;
	float  OutFlow = 0.0;
	float TravelT;

	//WTlayer = (int)(-day_WT/h);
   
	if(total_ice == 0.0)//total_ice == 0.0
	{    
		for ( l = 1; l <= q; l++ )
		{
			float ps = h[l]*sts[l];			
			//bypass flow
			if(byflow>0.0&&l<WTL)
			{		
				W01 = (fldcap[l] - water[hr][l] / ps) / (fldcap[l] - wiltpt[l]);
				if ( W01 >= 1.0 ) DeliWater = byflow;
				if ( W01 <= 0.0 ) DeliWater = (float)0.0;
				if ( W01 > 0.0 && W01 < 1.0 )

				DeliWater = .01 * byflow * W01;

				if(DeliWater > byflow) DeliWater = byflow;

				water[hr][l] += DeliWater;
				byflow -= DeliWater;
				if(byflow < 0.0) byflow = 0.0;

				day_bypass_influx += DeliWater;
				DeliWater = 0.0;
			}
			else
			{
				DeliWater = 0.0;
			}	  

			if(l<WTL)
			{
				if ( l == 1 )
				{
					AvaWater = surf_water;
					surf_water = 0.0;
					
					day_water_in += AvaWater;
				}
				else
				{
					AvaWater = OutWater[l-1][hr];//old_lh_out_water;
				}

				water[hr][l] += AvaWater;
				AvaWater = 0.0;

				if (water[hr][l] > ps)
				{

				   float sw = (water[hr][l] - ps);			   
				   water[hr][l] = ps;
				   surf_water += sw;			   
				   if(l==1) day_water_in -= sw;			  
				   sw = 0.0;

				}

				float travelt = 20.0 * (h[l] * sts[l] - h[l] * sts[l] * fldcap[l]) / sks[l];	// hr/layer
				TravelT = 0.5 * powf(clay[l],1.9188)  * travelt;

				float wiltptw = h[l] * sts[l] * wiltpt[l];
				float fldcapw = h[l] * sts[l] * fldcap[l];

				if (water[hr][l] > fldcapw)
				{					
					OutWater[l][hr] = 0.1 * (water[hr][l] - fldcapw) * (1.0 - .9 * (float)exp(-1.0 / TravelT));
						 
					water[hr][l] -= OutWater[l][hr]; 
					//water[hr][l+1] += OutWater[l][hr]; 
					//OutWater[l][hr] = 0.0;
				}
				else 
				{
					OutWater[l][hr] = 0.0;
				}
			}
			else//l>=WTL
			{
				water[hr][l] = ps;
			}		
		}//end of layer loop
	}//if ice>0
		
	
	{
		day_leach_water += (WaterLeakRate / 24.0);//wetland leaching
	}
			
	return(0);
}

float class_model::soil_EV(int hr, float* DayFlux, float hrPE3)
{
	float limit1=1.0, limit2=1.0, sev, asev, fsl, residue_volume;
	float WhrPE3 =hrPE3; 

	int EVL=(int)(0.20/h[1]);//depth of EVL evaportation layer set to 20cm
	
	if(EVL>nWTL) EVL=nWTL;//brian was added to 200cm

	fsl = 1.0;
	
	int iceLayer = 1;
	int il = 1;
	while (ice[il] == 0.0 && il <= q)//figure out ice layer.
	{

		il++;

	}
	iceLayer = il;
	
	if (iceLayer == 1|| air_temp<0) {
		EVL = 0; }
	else if(iceLayer<EVL)
	{
		EVL = iceLayer - 1;
	}
	if (year == 1 && jday == 305)
	{
		float blah;
		blah = 1.0;

	}
	surface_litter = rcvl[1]+rcl[1]+rcr[1]+stub1+stub2+stub3;//kg C/ha 
	residue_volume = surface_litter / 100.0 /10000.0; //cubic m/square m
	if(surface_litter>0.0) 
	{
		fsl = -0.99 - 0.236 * (float)log(residue_volume);// based on J.L. Steiner, 1989, SSSAJ 53:911-916
		if(fsl>1.0) fsl=1.0;
	}
	else
		fsl = 1.0;

	float  tev, zz;

	//calculate weighted distribution
	std::vector<float> weights(EVL + 1);
	float total_weight = 0.0;
	//float weights[EVL + 1]; // assuming EVL is small (e.g., ≤ 20)

	float decay_factor = 0.9f; // adjust this to control how steeply evaporation declines with depth

	for (int l = 1; l <= EVL; l++) {
		weights[l] = expf(-decay_factor * (l - 1));
		total_weight += weights[l];
	}
	//end distribution

	for(int l=1; l<=EVL; l++)
	{
		//sev = hrPE3 / (float)EVL;//(* powf(0.5, l);//hrPE3 / (float)EVL
		sev = hrPE3 * (weights[l] / total_weight);
/*		if ( l<= (int)(EVL / h) )
		{
			if ( jday==1 && l==1 ) old_tev=0.0;

			zz = l * h;       
			if ( l == 1 ) old_tev = (float)0.0;

			tev = fsl*(hrPE3 * ((zz / EVL) / (zz / EVL+ (float)exp(-2.92 - 1.43 * zz /EVL))));

			sev = tev - old_tev;
			old_tev = tev;

		}
		else
		{
			sev = 0.0;
		}
*/
		if(FilmCoverFraction>0.0) //plastic film mulching
		{
			limit1 = (1.0 - FilmCoverFraction);
		}
		else if(irri_flag==1)
		{

			/*
			if(IrriMethod==0) //furrow
				limit1 = 50.0;
			else if(IrriMethod==1) //sprinkler
				limit1 = 30.0;
			else if(IrriMethod==2) //drip 0cm
				limit1 = 20.0;
			else
				limit1 = 1.0;//drip 30cm
				*/
			limit1 = 1.0;

		}
		else 
			limit1 = 1.0;

		float wiltptw = h[l] * sts[l] * wiltpt[l];
		float fldcapw = h[l] * sts[l] * fldcap[l];

		if ( water[hr][l] < fldcapw )
		{
			limit2 = ((water[hr][l] - 0.0) / (fldcapw - 0.0));
			if (limit2 < 0.0) limit2 = 0.0;
			limit2 = powf(limit2, qstar);
		}
		else
		{
			limit2 = 1.0;
		}

		float limit = limit1 * limit2 * fsl*.75;//*.75;//brian limit soil evap
		//limit = min(1.0, max(0.0, limit));

		if(st[1]>=12&&day_WT>0.0) limit *= 0.01;

		asev = sev * limit;

		if ( asev < 0.0 ) asev = 0.0;

		/*if (by_passf > 0.0)
		{
		   asev += (0.0001 * water[hr][l]);//water evaporation from layer l at hour hr
		}*/

		if(WhrPE3<=asev) asev = 0.0;
		else WhrPE3 -= asev;
	
		if(water[hr][l]>asev && water[hr][l]> (wiltptw*0.50))
			water[hr][l] -= asev;//should allow water in a layer to go below wilting point in evaporative layers.
		else
		{
			asev = 0.0;
			//asev = water[hr][l];
		//	water[hr][l] = 0.0;
		}

		day_soil_ev += asev;

		//hrPE3 -= asev;
		//if(hrPE3<0.0) hrPE3 = 0.0;
				

		//float fldcapw = h[l] * sts[l] * fldcap[l];
		if(st[1]>=12&&day_WT>0.0) water[hr][l] = fldcapw;
	}
	if(year==12 && jday==141)
	{
		float blah;
		blah = 1.0;
	}
	
	return(0);
}




