#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <stdio.h>

#define _USE_32BIT_TIME_T


#ifdef MANURE
extern class_manure MData;
#endif

float day_clay_n2;
int File_Copy(char *source, char *dest);

void class_model::write_out_dayClim(FILE *fclim, int jday, char*site, int year, float air_temp, float precipitation,
									 float wind_speed, float radiation, float humidity)
{
	if (jday==1&&year==1)
     {
		fprintf(fclim, "Daily climate at site %s in year %d\n", site, year);
		//fprintf(fclim, "Day,Temp.(C),Prec.(mm),WindSpeed(m/s),Radiation(MJ/m2/d),Humidity(%),PET(mm),Actual_ET(mm),Evaporation(mm),Transpiration(mm),DayPET_RN(MJ/m2/d),PAR,Rs,Ra,Albedo,DayPET_Crop(mm)\n");
		fprintf(fclim, "Year,Day,Temp.(C),Prec.(mm),WindSpeed(m/s),Radiation(MJ/m2/d),Humidity(%%),PET(mm),Actual_ET(mm),Evaporation(mm),Transpiration(mm),DayPET_RN(MJ/m2/d),DayPET(mm),DayPET_Crop(mm),Base_CO2,DayAET,LeafTemp\n");
	}
		fprintf(fclim, "%3d,", year);
		fprintf(fclim, "%4d, ", jday);
		fprintf(fclim, "%7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f\n", 
			air_temp, precipitation*1000.0, wind_speed, DayPETRs, humidity, DayPET*1000.0, 
			(day_transp+day_snow_ev + dfol_ev + day_soil_ev + day_pond_ev)*1000.0, (day_snow_ev + dfol_ev + day_soil_ev + day_pond_ev)*1000.0,
			day_transp*1000.0,DayPETRN,PPT[1]*1000,DayPETCROP[1]*1000,Base_CO2,DayAET*1000.0,leafTemp_C[1]);
//		fprintf(fclim, "%7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f\n", 
	//		air_temp, precipitation*1000.0, wind_speed, radiation, humidity, DayPET*1000.0, 
	//		(day_transp+day_snow_ev + dfol_ev + day_soil_ev + day_pond_ev)*1000.0, (day_snow_ev + dfol_ev + day_soil_ev + day_pond_ev)*1000.0,
	//		day_transp*1000.0,DayPETRN,DayPETPAR,DayPETRs,DayPETRa,DayPETAlbedo,DayPETCROP[1]*1000);

}

int class_model::write_out_days(FILE *fs, float DayPET)  // day_soilClimate file
{
	

	//int ww=(int)((float)q/5.0);
	
	 //if(LL1==0) LL1=1;

	if (jday == 69 && year == 8)
	{
		float blah;
		blah = 1.0;
	}

	 if (jday==1&&year==1)//&&year==1
     {
		fprintf(fs, "Daily soil climate at site %s in year %d\n", site, year);
		fprintf(fs, ",,,,,Soil_temperature,,,,,,,,,,,,,,,,,,,,,,Soil_moisture(wfps),,,,,,,,,,,,,,,,,,,,,,Soil_oxygen(mol/L),,,,,,Soil_Eh(mv),,,,,,WT(m), Ice(wfps),,,,,,Ice,Snowpack,SoilWater,DeepWater,Soil_pH,,,,,,SurfaceWaterT,BulkDensity,,,,,,UpperLimit,,,,,,,,,,\n");
	//	fprintf(fs, "Day,Temp.(C),Prec.(mm),PET,1cm,5cm,10cm,20cm,30cm,40cm,50cm,60cm,70cm,80cm,90cm,100cm,110cm,120cm,130cm,140cm,150cm,160cm,170cm,180cm,190cm,200cm,1cm,5cm,10cm,20cm,30cm,40cm,50cm,60cm,70cm,80cm,90cm,100cm,110cm,120cm,130cm,140cm,150cm,160cm,170cm,180cm,190cm,200cm,1cm,10cm,20cm,30cm,40cm,50cm,1cm,10cm,20cm,30cm,40cm,50cm,,1cm,10cm,20cm,30cm,40cm,50cm,(mm),(mm),(mm),(mm),1,10,20,30,40,50, degreeC,1cm,10cm,20cm,30cm,40cm,50cm\n\n");
		fprintf(fs, "Year,Day,Temp.(C),Prec.(mm),PET,1cm,5cm,10cm,20cm,30cm,40cm,50cm,60cm,70cm,80cm,90cm,100cm,110cm,120cm,130cm,140cm,150cm,160cm,170cm,180cm,190cm,200cm,1cm,5cm,10cm,20cm,30cm,40cm,50cm,60cm,70cm,80cm,90cm,100cm,110cm,120cm,130cm,140cm,150cm,160cm,170cm,180cm,190cm,200cm,1cm,10cm,20cm,30cm,40cm,50cm,1cm,10cm,20cm,30cm,40cm,50cm,,1cm,10cm,20cm,30cm,40cm,50cm,(mm),(mm),(mm),(mm),1,10,20,30,40,50, degreeC,1cm,10cm,20cm,30cm,40cm,50cm,1cm,10cm,20cm,30cm,40cm,50cm,60cm,70cm,80cm,90cm,100cm\n\n");
	}
		fprintf(fs, "%3d,", year);
		fprintf(fs, "%3d,", jday);
		fprintf(fs, "%7.2f,%7.2f,%7.1f,", air_temp, precipitation*1000, DayPET*1000);
		fprintf(fs, "%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,", temp[LL0],temp[LL6], temp[LL1], temp[LL2], temp[LL3], temp[LL4], temp[LL5], temp[LL7], temp[LL8], temp[LL9], temp[LL10], temp[LL11], temp[LL12], temp[LL13], temp[LL14], temp[LL15], temp[LL16], temp[LL17], temp[LL18], temp[LL19], temp[LL20], temp[LL21]);
		fprintf(fs, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,", day_wfps[LL0], day_wfps[LL6],day_wfps[LL1], day_wfps[LL2], day_wfps[LL3], day_wfps[LL4], day_wfps[LL5], day_wfps[LL7], day_wfps[LL8], day_wfps[LL9], day_wfps[LL10], day_wfps[LL11], day_wfps[LL12], day_wfps[LL13], day_wfps[LL14], day_wfps[LL15], day_wfps[LL16], day_wfps[LL17], day_wfps[LL18], day_wfps[LL19], day_wfps[LL20], day_wfps[LL21]); //wfps
		fprintf(fs, "%7.6f,%7.6f,%7.6f,%7.6f,%7.6f,%7.6f,", O2_old[LL0], O2_old[LL1], O2_old[LL2], O2_old[LL3], O2_old[LL4], O2_old[LL5]);
		fprintf(fs, "%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,", Eh_old[LL0], Eh_old[LL1], Eh_old[LL2], Eh_old[LL3], Eh_old[LL4], Eh_old[LL5]);
		fprintf(fs, "%7.4f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.1f,%7.2f,",
		    day_WT,
			ice[LL0],ice[LL1],ice[LL2],ice[LL3],ice[LL4],ice[LL5], 
			//ice[LL1] /10/( h[LL1]*sts[LL1] * 1000), ice[LL2] /10/( h[LL2]*sts[LL2] * 1000), ice[LL3] /10/( h[LL3]*sts[LL3] * 1000), 
			total_ice * 1000, snow_pack*1000, day_SoilWater*1000, WaterPool*1000); 
		fprintf(fs, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", sph[LL0], sph[LL1], sph[LL2], sph[LL3], sph[LL4], sph[LL5]);
		fprintf(fs, "%7.2f,", SurfaceWaterT);
		fprintf(fs, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", sd[LL0],sd[LL1],sd[LL2],sd[LL3],sd[LL4],sd[LL5]);
	    fprintf(fs, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n", fldcap[LL0],fldcap[LL1],fldcap[LL2],fldcap[LL3],fldcap[LL4],fldcap[LL5],fldcap[LL7],fldcap[LL8],fldcap[LL9],fldcap[LL10],fldcap[LL11]);
     return( 0 );


}

#ifdef HOURLY
void class_model::write_out_HrSoilMoist(FILE *HSM)
{
	//int ww=(int)((float)q/5.0);
	
	 if(LL1==0) LL1=1;

	if (jday==1)
     {
		fprintf(HSM, "Hourly soil moisture in wfps at site %s in year %d\n\n", site, year);
		fprintf(HSM, "Day,Hour,1cm,5cm,10cm,20cm,30cm,40cm,50cm\n\n");
     }
	
	for(int i=1;i<=24;i++)
	{
		fprintf(HSM, "%3d,%3d,",jday,i);			
		fprintf(HSM, "%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n", 
			water[i][1]/(h[1] * sts[1]),water[i][LL6]/(h[LL6] * sts[LL6]),water[i][LL1]/(h[LL1] * sts[LL1]), water[i][LL2]/(h[LL2] * sts[LL2]), water[i][LL3]/(h[LL3] * sts[LL3]), water[i][LL4]/(h[LL4] * sts[LL4]), water[i][LL5]/(h[LL5] * sts[LL5])); 
		    
	}
}

void class_model::write_out_HrSoilN(FILE *HSM, int T, int JDY)
{
	if (jday==JDY&&T==1)
    {
		fprintf(HSM, "Hourly soil N at site %s in year %d\n\n", site, year);
		fprintf(HSM, "Day,Hour,NH4+,NO3-,NO2-,NO,N2O,N2,DOC\n");
    }
	
	fprintf(HSM, "%3d,%3d,",jday,T);			
	fprintf(HSM, "%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n", 
			nh4[1], no3[1], no2[1], no[1], n2o[1], n2[1], doc[1]); 
		    
}

#endif

int class_model::write_out_dayw(FILE *fw, float DayPET)//day soil water
{
	float SoilWaterBalance;

     int L1, L2, L3;
	 for(int i=1; i<=q; i++)
	{
		if(SoilDepth[i]>0.0&&SoilDepth[i]<=0.05) L1 = i;
		else if(SoilDepth[i]>0.05&&SoilDepth[i]<=0.15) L2 = i;
		else if(SoilDepth[i]>0.15&&SoilDepth[i]<=0.3) L3 = i;
		//else if(SoilDepth[i]>0.2&&SoilDepth[i]<=0.3) LL3 = i;
		//else if(SoilDepth[i]>0.3&&SoilDepth[i]<=0.4) LL4 = i;
		//else if(SoilDepth[i]>=0.4&&SoilDepth[i]<=0.5) LL5 = i;
		else {}
	}
    /* L1 = (int)(.05/h);
     L2 = (int)(.15/h);
     L3 = (int)(.30/h);*/

	 float soil_water_change = end_soil_water - ini_soil_water;
	 float free_water = 0.0;
	 for(int w=1; w<=q; w++)
	 {
		free_water += water[24][w];
	 }


	 if(flood_flag==0) 
		 SoilWaterBalance = soil_water_change - day_water_in + day_soil_ev + day_transp + day_leach_water;
	 else 
		 SoilWaterBalance = soil_water_change - day_water_in + day_soil_ev + day_transp + day_leach_water;
	 //float dBalance2 = (day_water_in + day_bypass_influx) - (day_transp + day_soil_ev + day_leach_water + soil_water_change + dPool);
    
	 float DayIniPool = ini_soil_water + DayIniWaterPool;
	 float DayEndPool = end_soil_water + EndWaterPool;
	 float DayInFlux = precipitation + day_irri;
	 float DayOutFlux = day_soil_ev + day_transp + day_leach_water + day_runoff + day_snow_ev + dfol_ev + day_pond_ev+day_soilIce_ev;//

	 //float dDaySoilWater = ((end_soil_water+EndWaterPool)-(ini_soil_water+DayIniWaterPool))*1000;
	 //float dDayOutFlow = (day_soil_ev+day_transp+day_leach_water)*1000;
	 float balance = (DayEndPool+DayOutFlux)-(DayIniPool+DayInFlux);//dDaySoilWater - day_water_in*1000 + dDayOutFlow;
     
	 if (jday==1&&year==1)//&&year==1
     {
		fprintf(fw, "Daily soil water budget at site %s in year %d. Unit: mm water\n", site, year);
		//fprintf(fw, "____________________________________________________________________________________________________________________________________________\n");
	//	fprintf(fw, "Day,IniSoilWater,IniDeepWater,IniWaterPool,Precipitation,Irrigation,DayInFlow,EndSoilWater,EndDeepWater,EndWaterPool,PET,Transpiration,PotEvap,Evaporation,Leaching,Runoff,DayOutFlow,Balance,SedimentYield, SOC_loss, ION_loss, OrgP_loss, AdsP_loss, LabP_loss,FreeWater,SoilIce,Ponding,SnowPack,DaySoilEvap,DayWTDepth,WaterTableLayer,DayTileWater\n");
	fprintf(fw, "Year,Day,IniSoilWater,IniDeepWater,IniWaterPool,Precipitation,Irrigation,DayInFlow,EndSoilWater,EndDeepWater,EndWaterPool,PET,Transpiration,PotEvap,Evaporation,Leaching,Runoff,DayOutFlow,Balance,SedimentYield, SOC_loss, ION_loss, OrgP_loss, AdsP_loss, LabP_loss,FreeWater,SoilIce,Ponding,SnowPack,DaySoilEvap,DayWTDepth,WaterTableLayer,DayTileWater,RootDepthC1,RootDepthC2,RootDepthC3,day_Intercept,RootDen(0-5cm),RootDen(5-15cm),RootDen(15-35cm),RootDen(35-45cm),RootDen(45-55cm),RootDen(55-85cm),RootDen(85-115cm),RootDen(115-150cm),RootDen(150-200cm)\n");
		//fprintf(fw, "____________________________________________________________________________________________________________________________________________\n");
     }

	
//	 fprintf(fw, "%3d,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%3d,%7.4f\n",
	fprintf(fw, "%3d,%3d,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%16.7f,%16.7f,%16.7f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%3d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,",
		 year,
			jday,
			ini_soil_water*1000.0,
			DayIniWaterPool*1000.0,
			DayIniPool*1000.0,

			precipitation*1000.0,
			day_irri*1000.0,
			DayInFlux*1000.0,

			end_soil_water*1000.0,				
			EndWaterPool*1000.0,
			DayEndPool*1000.0,			
				
			DayPET*1000.0,
			//act_DayAT*1000.0,
			day_transp*1000.0,
			act_DayPE*1000.0,
			(day_soil_ev+day_snow_ev + dfol_ev + day_pond_ev+day_soilIce_ev)*1000.0,			
			day_leach_water *1000.0,
			//day_Deep_Perc * 1000.0, turn this on for deep percolation code
			day_runoff * 1000.0,			
			DayOutFlux*1000.0,
			
			balance*1000.0,
			
			sedyld*1000.0, socmusle, nh4musle+no3musle, OrgPmusle,AdsPmusle,LabPmusle,
			free_water * 1000.0,
			total_ice,surf_water * 1000.0, snow_pack * 1000.0,day_soil_ev*1000.0,day_WT,WTL,day_tile_water*1000,root_depth[1]*100,root_depth[2]*100,root_depth[3]*100,day_intercept*1000);

	int root_layer,z;
	root_layer = (int)((root_length[1]+h[1])/h[1]); 
	int dens05,dens010,dens1020,dens2030,dens3040,dens4050,dens50100,dens100150,dens150200;
	float sumdens05,sumdens010,sumdens1020,sumdens2030,sumdens3040,sumdens4050,sumdens50100,sumdens100150,sumdens150200;
	sumdens05=0;
	sumdens010=0;
	sumdens1020=0;
	sumdens2030=0;
	sumdens3040=0;
	sumdens4050=0;
	sumdens50100=0;
	sumdens100150=0;
	sumdens150200=0;
	dens05=int((0.05+h[1])/h[1]);
	dens010=int((0.15+h[1])/h[1]);
	dens1020=int((0.35+h[1])/h[1]);
	dens2030=int((0.45+h[1])/h[1]);
	dens3040=int((0.55+h[1])/h[1]);
	dens4050=int((0.85+h[1])/h[1]);
	dens50100=int((1.15+h[1])/h[1]);
	dens100150=int((1.5+h[1])/h[1]);
	dens150200=int((2.0+h[1])/h[1]);

	/*
	dens010=int(0.1/h[1])+1;
	dens1020=int(0.2/h[1])+1;
	dens2030=int(0.3/h[1])+1;
	dens3040=int(0.4/h[1])+1;
	dens4050=int(0.5/h[1])+1;
	dens50100=int(1.0/h[1])+1;
	dens100150=int(1.5/h[1])+1;
	dens150200=int(2.0/h[1])+1;
*/
	float sumDensity;
	sumDensity=0.0;
if(root_layer>1)
{
	for (z=1; z<=(root_layer); z++)
	{
	
	if(z<=dens05)
	{sumdens05+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens05 && z<=dens010)
	{sumdens010+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens010 && z<=dens1020)
	{sumdens1020+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens1020 && z<=dens2030)
	{sumdens2030+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens2030 && z<=dens3040)
	{sumdens3040+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens3040 && z<=dens4050)
	{sumdens4050+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens4050 && z<=dens50100)
	{sumdens50100+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens50100 && z<=dens100150)
	{sumdens100150+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}
	if(z>dens100150 && z<=dens150200)
	{sumdens150200+=rootDensity[1][z]*100;
	sumDensity+=rootDensity[1][z];}	
	}
}
else if(root_layer==1 && rootDensity[1][1]>0)
{
sumdens05=100;
sumDensity=1.0;
}
if(sumDensity==0)
{sumDensity=1.0;}

	fprintf(fw, "%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",
			sumdens05/sumDensity,sumdens010/sumDensity,sumdens1020/sumDensity,sumdens2030/sumDensity,sumdens3040/sumDensity,sumdens4050/sumDensity,sumdens50100/sumDensity,sumdens100150/sumDensity,sumdens150200/sumDensity);
	//rootDensity[1][layer?]
			//SoilWaterBalance*1000,			
			//day_surplus_water*1000);

/*			day_bypass_influx * 1000,
			day_intercept*1000,
		    
		    day_snow_ev*1000, //mm/day
			dfol_ev*1000,
			
			day_paddy_water_ev * 1000,
			
			day_runoff*1000,
			soil_water_change*1000,
			ini_soil_water*1000,
			end_soil_water*1000);
*/			
			//SoilWaterBalance*1000);
			
     return( 0 );
}

int class_model::write_out_dayc(FILE *fc )//day soil carbon
{


	if (jday==1&&year==1)
	{
    fprintf(fc, "Daily C pools (kg C/ha) and fluxes (kg C/ha/day) at site %s in year %d\n", site, year);
//	fprintf(fc, "Day,Very labile litter,Labile litter,Resistant litter,Microbe,Humads,Humus,CharC,SOC,SOC0-10cm, SOC10-20cm,SOC20-30cm,SOC30-40cm,SOC40-50cm,SOC50-60cm,SOC60-70cm,SOC70-80cm,SOC80-90cm,SOC90-100cm,SOC100-110cm, SOC110-120cm,SOC120-130cm,SOC130-140cm,SOC140-150cm,SOC150-160cm,SOC160-170cm,SOC170-180cm,SOC180-190cm,SOC190-200cm,dSOC,DOC,DOC_produce,DOC_consume,DOC_leach,Photosynthesis,Leaf-respiration, Stem-respiration, Root-respiration,Soil-heterotrophic-respiration, NPP,Eco-respiration, NEE,Stub,DOC_from_root,CH4-prod.,CH4-oxid.,CH4-flux,CH4-pool,DOC-leach,Litter-C,Manure-C, SoilCO2_0-10cm,SoilCO2_10-20cm,SoilCO2_20-30cm,SoilCO2_30-40cm,SoilCO2_40-50cm,Acetate_produced,Acetate_consumed,Acetate_pool\n");
	fprintf(fc, "Year,Day,Very labile litter,Labile litter,Resistant litter,Microbe,Humads,Humus,CharC,SOC,SOC0-10cm, SOC10-20cm,SOC20-30cm,SOC30-40cm,SOC40-50cm,SOC50-60cm,SOC60-70cm,SOC70-80cm,SOC80-90cm,SOC90-100cm,SOC100-110cm, SOC110-120cm,SOC120-130cm,SOC130-140cm,SOC140-150cm,SOC150-160cm,SOC160-170cm,SOC170-180cm,SOC180-190cm,SOC190-200cm,dSOC,DOC,DOC_produce,DOC_consume,DOC_leach,Photosynthesis,Leaf-respiration, Stem-respiration, Root-respiration,Soil-heterotrophic-respiration, NPP,Eco-respiration, NEE,Stub,DOC_from_root,CH4-prod.,CH4-oxid.,CH4-flux,CH4-pool,DOC-leach,Litter-C,Manure-C, SoilCO2_0-10cm,SoilCO2_10-20cm,SoilCO2_20-30cm,SoilCO2_30-40cm,SoilCO2_40-50cm,Acetate_produced,Acetate_consumed,Acetate_pool,ManurePool,ManurePoolCN,ManurePoolN,ManurePoolKRate\n");
	}
	fprintf(fc, "%3d,", year);//for year
	fprintf(fc, "%3d,", jday);
	fprintf(fc, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.3f,%7.3f,%7.3f,%7.3f,%7.3f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",
		    wrcvl, wrcl, wrcr, wcrb, wcrhl+wcrhr, whumus, winertC, T_SOC, layerc[1],layerc[2],layerc[3],layerc[4],layerc[5],layerc[6],layerc[7],layerc[8],layerc[9],layerc[10],layerc[11],
			layerc[12],layerc[13],layerc[14],layerc[15],layerc[16],layerc[17],layerc[18],layerc[19],layerc[20],day_dSOC, wtcavai, day_DOC_prod, day_DOC_cons, day_leach_DOC);
	fprintf(fc, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", 
		Psn, sum_shoot_CO2, sum_stem_CO2, day_root_resp, soil_hete_CO2, dPlantBiomass, EcoCO2, NEE, stub1+stub2+stub3);
	fprintf(fc, "%7.2f,%7.5f,%7.5f,%7.5f,%7.2f,", day_RootInput_DOC, ch4_prod, -ch4_day_oxid, day_ch4, ch4_pool);
	fprintf(fc, "%7.2f,%7.2f,%7.2f, %7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n", day_leachhu,day_addC, day_addmc, day_decomp[1],day_decomp[2],day_decomp[3],day_decomp[4],day_decomp[5],day_acetate_prod, day_acetate_cons,day_acetate,totalManureC,manurePoolCN,totalManureN, manureCK1);//, C_soil);//+day_frostMicrobe);

    return( 0 );
}


int class_model::write_out_co2(FILE* fco2)
{


	if (jday == 1 && year == 1)
	{
		fprintf(fco2, "Daily CO2 impacts on crops at site %s in year %d\n", site, year);
		//	fprintf(fc, "Day,Very labile litter,Labile litter,Resistant litter,Microbe,Humads,Humus,CharC,SOC,SOC0-10cm, SOC10-20cm,SOC20-30cm,SOC30-40cm,SOC40-50cm,SOC50-60cm,SOC60-70cm,SOC70-80cm,SOC80-90cm,SOC90-100cm,SOC100-110cm, SOC110-120cm,SOC120-130cm,SOC130-140cm,SOC140-150cm,SOC150-160cm,SOC160-170cm,SOC170-180cm,SOC180-190cm,SOC190-200cm,dSOC,DOC,DOC_produce,DOC_consume,DOC_leach,Photosynthesis,Leaf-respiration, Stem-respiration, Root-respiration,Soil-heterotrophic-respiration, NPP,Eco-respiration, NEE,Stub,DOC_from_root,CH4-prod.,CH4-oxid.,CH4-flux,CH4-pool,DOC-leach,Litter-C,Manure-C, SoilCO2_0-10cm,SoilCO2_10-20cm,SoilCO2_20-30cm,SoilCO2_30-40cm,SoilCO2_40-50cm,Acetate_produced,Acetate_consumed,Acetate_pool\n");
		fprintf(fco2, "Year,Day,Temp,Precip,CO2,CO2factor,cropType1,wreq1,maxmn1,graincn1,cropType2,wreq2,maxmn2,graincn2,cropType3,wreq3,maxmn3,graincn3\n");
	}
	fprintf(fco2, "%3d,", year);//for year
	fprintf(fco2, "%3d,", jday);
	fprintf(fco2, "%7.2f,%7.2f,%7.2f,%7.2f,%3d,%7.2f,%7.2f,%7.2f,",
		air_temp,precipitation*1000.0, Base_CO2, CO2_factor,crop[1],wreq[1],maxmn[1],graincn[1]);
	fprintf(fco2, "%3d,%7.2f,%7.2f,%7.2f,", crop[2], wreq[2], maxmn[2], graincn[2]);
	fprintf(fco2, "%3d,%7.2f,%7.2f,%7.2f\n", crop[3], wreq[3], maxmn[3], graincn[3]);
	return(0);
}

int class_model::write_out_multiCrop(FILE* fmcrop)//DAY_multiCrop output //Theos crop competition factors
{
	int i;
	
	if (jday == 1 && year == 1)
	{
		fprintf(fmcrop, "Daily MultiCrop growth factors at site %s", site);
		fprintf(fmcrop, " in year %d\n", year);
		fprintf(fmcrop, "Year,");
		fprintf(fmcrop, "Day,");
		fprintf(fmcrop, "Temperature,Precipitation,Irrigation,Radiation,PET,");
		//for(int i=1;i<=CropNumbers;i++) fprintf(fcrop, ",Crop %d,,,,,,,,,,,,,,,,,,,,,,,,,,,", i);

		//headers for per crop type
		for (int i = 1; i <= 4; i++) 
		{
			fprintf(fmcrop, "Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,,Crop %d,",i,i,i,i,i,i,i,i,i,i,i,i,i,i,i);//20 of 31 columns
			
		}//11 of 34columns
		fprintf(fmcrop, "\n");

		//2nd row headers for all crops
		fprintf(fmcrop, "Annual,Daily,Daily,Daily,Daily,Daily,Daily,");
		//fprintf(fcrop, ",,,,,,,,LeafC,StemC,RootC,GrainC,");
		//for(int i3=1;i3<=CropNumbers;i3++) 

		for (int i3 = 1; i3 <= 4; i3++) 
		{ //2nd level headers per Crop type
			fprintf(fmcrop, "CropID,TDD,GrowthIndex,Water_demand,Water_stress,Comp_water,N_demand,N_stress,Comp_N,Temp_Stress,lightStress,LAI,LeafTemp,CropHeight,Kext,");
		}
		fprintf(fmcrop, "\n");

		fprintf(fmcrop, "(Year),JD,degree_C,mm,mm,MJ/m2/d,mm,");
		//	fprintf(fcrop, ",degree_C,mm,mm,MJ/m2/d,mm,mm,mm,kgC/ha/d,kgC/ha,kgC/ha,kgC/ha,");		
		//	for(int i4=1;i4<=CropNumbers;i4++) 

		for (int i4 = 1; i4 <= 4; i4++)
		{  // 3rd level headers per crop type 
			fprintf(fmcrop, "#,degree_C,index,mm,index,index, kgN/ha/d,index,index,index,index,,oC,m,index,");
		}
		//	fprintf(fcrop, ",degree_C,,mm,,,kgN/ha/d,,kgN/ha/d,kgN/ha/d,kgN/ha/d,kgN/ha/d,kgN/ha,kgC/ha/d,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgN/ha,kgN/ha,kgN/ha,kgN/ha,oC,");
		fprintf(fmcrop, "\n");
	}


	fprintf(fmcrop, "%4d,", year);
	fprintf(fmcrop, "%4d,", jday);


	fprintf(fmcrop, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,",
		air_temp, precipitation * 1000.0, day_irri * 1000.0, DayPETRs, DayPET * 1000.0);/// was writing out PAR vs DayPETRs for radiation.




	//for(cwc=1;cwc<=CropNumbers;cwc++)
	for (cwc = 1; cwc <= 4; cwc++) //outputs per crop type
	{

		

		fprintf(fmcrop, "%10d,%10.2f,%10.6f,%10.2f,%10.2f,%10.2f,",
			crop[cwc], TDD[cwc], PGI[cwc], PPT[cwc] * 1000.0, day_DWater[cwc],CF_water[cwc][1]);
		fprintf(fmcrop, "%10.2f,%10.2f,%10.4f,%7.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,",
			day_N_demand[cwc], N_stress[cwc],CF_N[cwc], cropTempStress[cwc], lightStressFactor[cwc],lai[cwc], leafTemp_C[cwc], CropHeight[cwc], kext1[cwc]);
	}
	fprintf(fmcrop, "\n");
	return(0);
}
int class_model::write_out_dayn2o(FILE *fn2o)//DAY_SOILN2O output
{
	float total_dayNit = 0.0;
	float total_dayDenit = 0.0;
	//float ps = h[1] * sts[1];
	//ps = 1.0;
	if (jday == 1 && year == 1)
	{
		fprintf(fn2o, "Daily N2O pools and fluxes at site %s in year %d\n", site, year);
		fprintf(fn2o, ",,N Gas Fluxes,,,NET Soil GAS N pools that will emit that day (g N2O-N/ha/d),,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Total Soil N2O that is in the profile (g N2O-N/ha/d),,,,,,,,,,,,,,,,,,,,Total Water & ice, (WFPS)\n");
			fprintf(fn2o, "Year,Day,N2O-flux,NO-flux,N2-flux,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,nitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,denitrification,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,SoilN2O,");
			fprintf(fn2o, "TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,TotWater,FreezeDOC\n");//totWaterOutput
			fprintf(fn2o, "Year,Day,kgN/ha/day,kgN/ha/day,kgN/ha/day,0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,50-60cm,60-70cm,70-80cm,80-90cm,90-100cm,100-110cm,110-120cm,120-130cm,130-140cm,140-150cm,150-160cm,160-170cm,170-180cm,180-190cm,190-200cm,");
			fprintf(fn2o, "0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,50-60cm,60-70cm,70-80cm,80-90cm,90-100cm,100-110cm,110-120cm,120-130cm,130-140cm,140-150cm,150-160cm,160-170cm,170-180cm,180-190cm,190-200cm,");
			fprintf(fn2o, "0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,50-60cm,60-70cm,70-80cm,80-90cm,90-100cm,100-110cm,110-120cm,120-130cm,130-140cm,140-150cm,150-160cm,160-170cm,170-180cm,180-190cm,190-200cm,");
			fprintf(fn2o, "1cm,5cm,10cm,20cm,30cm,40cm,50cm,60cm,70cm,80cm,90cm,100cm,110cm,120cm,130cm,140cm,150cm,160cm,170cm,180cm,190cm,200cm,gC/ha/day\n\n");//total water output

	}
	fprintf(fn2o, " %3d,", year);
	fprintf(fn2o, " %3d,", jday);
	fprintf(fn2o, "%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,",
		day_soil_an_n2o,
		day_soil_an_no,
		day_soil_n2,
		day_nitrif[1]*1000.0, day_nitrif[2] * 1000.0, day_nitrif[3] * 1000.0, day_nitrif[4] * 1000.0, day_nitrif[5] * 1000.0, day_nitrif[6] * 1000.0, day_nitrif[7] * 1000.0, day_nitrif[8] * 1000.0, day_nitrif[9] * 1000.0, day_nitrif[10] * 1000.0, day_nitrif[11] * 1000.0, day_nitrif[12] * 1000.0, day_nitrif[13] * 1000.0, day_nitrif[14] * 1000.0, day_nitrif[15] * 1000.0, day_nitrif[16] * 1000.0, day_nitrif[17] * 1000.0, day_nitrif[18] * 1000.0, day_nitrif[19] * 1000.0, day_nitrif[20] * 1000.0);  //day_soil_nitrify,
	fprintf(fn2o, "%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,",
		day_denitrif[1] * 1000.0, day_denitrif[2] * 1000.0, day_denitrif[3] * 1000.0, day_denitrif[4] * 1000.0, day_denitrif[5] * 1000.0, day_denitrif[6] * 1000.0, day_denitrif[7] * 1000.0, day_denitrif[8] * 1000.0, day_denitrif[9] * 1000.0, day_denitrif[10] * 1000.0, day_denitrif[11] * 1000.0, day_denitrif[12] * 1000.0, day_denitrif[13] * 1000.0, day_denitrif[14] * 1000.0, day_denitrif[15] * 1000.0, day_denitrif[16] * 1000.0, day_denitrif[17] * 1000.0, day_denitrif[18] * 1000.0, day_denitrif[19] * 1000.0, day_denitrif[20] * 1000.0);//day_soil_denitrification,
		//day_nitrify_N2O * 1000.0, (day_soil_an_n2o - day_nitrify_N2O) * 1000.0);
	fprintf(fn2o, "%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,",
		total_n2o[1] * 1000.0, total_n2o[2] * 1000.0, total_n2o[3] * 1000.0, total_n2o[4] * 1000.0, total_n2o[5] * 1000.0, total_n2o[6] * 1000.0, total_n2o[7] * 1000.0, total_n2o[8] * 1000.0, total_n2o[9] * 1000.0, total_n2o[10] * 1000.0, total_n2o[11] * 1000.0, total_n2o[12] * 1000.0, total_n2o[13] * 1000.0, total_n2o[14] * 1000.0, total_n2o[15] * 1000.0, total_n2o[16] * 1000.0, total_n2o[17] * 1000.0, total_n2o[18] * 1000.0, total_n2o[19] * 1000.0, total_n2o[20] * 1000.0);
	fprintf(fn2o, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f\n", day_wfps[LL0]+ice[LL0]/10000.0/(h[LL0]*sts[LL0]), day_wfps[LL6] + ice[LL6] / 10000.0 / (h[LL6] * sts[LL6]), day_wfps[LL1] + ice[LL1] / 10000.0 / (h[LL1] * sts[LL1]), day_wfps[LL2] + ice[LL2] / 10000.0 / (h[LL2] * sts[LL2]), day_wfps[LL3] + ice[LL3] / 10000.0 / (h[LL3] * sts[LL3]), day_wfps[LL4] + ice[LL4] / 10000.0 / (h[LL4] * sts[LL4]), day_wfps[LL5] + ice[LL5] / 10000.0 / (h[LL5] * sts[LL5]), day_wfps[LL7] + ice[LL7] / 10000.0 / (h[LL7] * sts[LL7]), day_wfps[LL8] + ice[LL8] / 10000.0 / (h[LL8] * sts[LL8]), day_wfps[LL9] + ice[LL9] / 10000.0 / (h[LL9] * sts[LL9]), day_wfps[LL10] + ice[LL10] / 10000.0 / (h[LL10] * sts[LL10]), day_wfps[LL11] + ice[LL11] / 10000.0 / (h[LL11] * sts[LL11]), day_wfps[LL12] + ice[LL12] / 10000.0 / (h[LL12] * sts[LL12]), day_wfps[LL13] + ice[LL13] / 10000.0 / (h[LL13] * sts[LL13]), day_wfps[LL14] + ice[LL4] / 10000.0 / (h[LL14] * sts[LL14]), day_wfps[LL15] + ice[LL15] / 10000.0 / (h[LL15] * sts[LL15]), day_wfps[LL16] + ice[LL16] / 10000.0 / (h[LL16] * sts[LL16]), day_wfps[LL17] + ice[LL17] / 10000.0 / (h[LL17] * sts[LL17]), day_wfps[LL18] + ice[LL18] / 10000.0 / (h[LL18] * sts[LL18]), day_wfps[LL19] + ice[LL19] / 10000.0 / (h[LL19] * sts[LL19]), day_wfps[LL20] + ice[LL20] / 10000.0 / (h[LL20] * sts[LL20]), day_wfps[LL21] + ice[LL21] / 10000.0 / (h[LL21] * sts[LL21]),TotalFreezeDOC*1000.0); //total Water Output

	return(0);
}

int class_model::write_out_dayn( FILE *fn )//DAY_SOILN output
{
	float total_nh3=0.0;
	float total_dayNit=0.0;
	float total_dayDenit=0.0;
	for(int i=1; i<=q; i++) {total_nh3 += nh3[i];total_dayNit += day_nitrification[i];total_dayDenit += day_denitrification[i];}
	 

   if (jday==1&&year==1)
   {
	fprintf(fn, "Daily N pools and fluxes at site %s in year %d\n", site, year);
	fprintf(fn, ",N uptake,,N pools (kg N/ha),,,,,,,,,,,,,,,,N gas fluxes (kg N/ha/day)\n");
//	fprintf(fn, "Day,Crop,Urea,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4, NO3-, NO3-, NO3-, NO3-, NO3-, NO3-,NO3-,NO3-,NO3-,NO3-,   NH3,N2O-flux,NO-flux,N2-flux,NH3-flux,NO3-leach,Urea-leach,DON-leach,ION-runoff,Gross N mineralization,N assimilation,Ice_DOC,Ice_N,Ice_N2O,Ice_N2,nitrification,nitrification,nitrification,nitrification,nitrification,denitrification,denitrification,denitrification,denitrification,denitrification,N_fixation,Litter_N,SON0-10cm, SON10-20cm,SON20-30cm,SON30-40cm,SON40-50cm,SON0-10cm, SON10-20cm,SON20-30cm,SON30-40cm,SON40-50cm,\n");
//	fprintf(fn, ",kgN/ha/day,,0-10cm,0-10cm,10-20cm,10-20cm,20-30cm,20-30cm,30-40cm,30-40cm,40-50cm,40-50cm,50-60cm,50-60cm,60-70cm,60-70cm,70-80cm,70-80cm,80-90cm,80-90cm,90-100cm,90-100cm,0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,50-60cm,60-70cm,70-80cm,80-90cm,90-100cm,0-50cm,,,,,,,,,,,,,,,0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,\n\n");   
	fprintf(fn, "Year,Day,Crop,Urea,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4,NH4+,exchengeable-NH4, NO3-, NO3-, NO3-, NO3-, NO3-, NO3-,NO3-,NO3-,NO3-,NO3-,   NH3,N2O-flux,NO-flux,N2-flux,NH3-flux,NO3-leach,Urea-leach,DON-leach,ION-runoff,Gross N mineralization,N assimilation,Ice_DOC,Ice_N,Ice_N2O,Ice_N2,nitrification,nitrification,nitrification,nitrification,nitrification,denitrification,denitrification,denitrification,denitrification,denitrification,N_fixation,Litter_N,SON0-10cm, SON10-20cm,SON20-30cm,SON30-40cm,SON40-50cm,SON0-10cm, SON10-20cm,SON20-30cm,SON30-40cm,SON40-50cm,TotalNitN2O,TotalDenitN2O,TotNitri,TotDenit,UREA0-5,UREA0-10,UREA10-20,UREA20-30,UREA30-40,UREA40-50,UREA-L1,UREA-L2,UREA-L3,UREA-L4,UREA-L5,UI-INHB,NI-INHB\n");
	fprintf(fn, ",,kgN/ha/day,,0-10cm,0-10cm,10-20cm,10-20cm,20-30cm,20-30cm,30-40cm,30-40cm,40-50cm,40-50cm,50-60cm,50-60cm,60-70cm,60-70cm,70-80cm,70-80cm,80-90cm,80-90cm,90-100cm,90-100cm,0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,50-60cm,60-70cm,70-80cm,80-90cm,90-100cm,0-50cm,,,,,,,,,,,,,,,0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,0-10cm,10-20cm,20-30cm,30-40cm,40-50cm,,input,kgNha,kgNha,kgNha,kgNha,kgNha,kgNkg,kgNkg,kgNkg,kgNkg,kgNkg,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,kgNha,factor,factor\n\n");   
   }
	fprintf(fn, " %3d,", year);
	fprintf(fn, " %3d,", jday);
	
	fprintf(fn, "%7.2f,%7.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,",
		    day_nup[1]+day_nup[2]+day_nup[3],		    
		    day_dsurea+DayFixFert3,

		    /*dsnh4[1], dsno3[1], dsClayN[1],
			dsnh4[2], dsno3[2], dsClayN[2],
			dsnh4[3], dsno3[3], dsClayN[3],
			dsnh4[4], dsno3[4], dsClayN[4],
			dsnh4[5], dsno3[5],	dsClayN[5],	*/

			dsnh4[1], dsClayN[1],
			dsnh4[2], dsClayN[2],
			dsnh4[3], dsClayN[3],
			dsnh4[4], dsClayN[4],
			dsnh4[5], dsClayN[5],
			dsnh4[6], dsClayN[6],
			dsnh4[7], dsClayN[7],
			dsnh4[8], dsClayN[8],
			dsnh4[9], dsClayN[9],
			dsnh4[10], dsClayN[10],

			dsno3[1], dsno3[2], dsno3[3],  dsno3[4], dsno3[5],dsno3[6],dsno3[7],dsno3[8],dsno3[9],dsno3[10],	

			total_nh3);	 
	fprintf(fn, "%8.6f,%8.6f,%8.6f,%8.2f,",
		    day_soil_an_n2o,
		    day_soil_an_no,
		    day_soil_n2,
		    day_soil_nh3+day_vol_nh3); 
	fprintf(fn, "%16.7f,%16.7f,%8.4f,%8.4f,%8.2f,%8.2f,%8.2f,%8.6f,%8.6f,%8.6f,%8.6f,%8.6f,%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,",		    
		    day_leach_NO3,
			day_leach_urea,
			day_leachhu/rcnm,
			day_runoff_N,
			day_N_mine,
			day_N_assim,
			day_ice_doc,
			day_ice_N,
			day_ice_n2o,
			day_ice_n2,
			day_nitrif[1],day_nitrif[2],day_nitrif[3],day_nitrif[4],day_nitrif[5], //day_soil_nitrify,
			day_denitrif[1],day_denitrif[2],day_denitrif[3],day_denitrif[4],day_denitrif[5],//day_soil_denitrification,
			day_soilN_from_Nfixation[1]+day_soilN_from_Nfixation[2]+day_soilN_from_Nfixation[3],
			day_inLitterN);
	fprintf(fn, "%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,",
		layern[1],layern[2],layern[3],layern[4],layern[5],topn[1],topn[2],topn[3],topn[4],topn[5]);
	fprintf(fn, "%8.6f,%8.6f,%8.6f,%8.6f,",
		day_nitrify_N2O,(day_soil_an_n2o-day_nitrify_N2O),total_dayNit,total_dayDenit);
	//urea per 10cm
	fprintf(fn, "%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f\n",
		dsurea[0],dsurea[1],dsurea[2],dsurea[3],dsurea[4],dsurea[5],urea[1],urea[2],urea[3],urea[4],urea[5], UreaHydroInhibEf, NIEfficiency);
    return( 0 );
}

int class_model::write_out_daysp(FILE *fsp )//day_soilP
{
	if (jday==1&&year==1)
	{
    fprintf(fsp, "Daily P pools (kg P/ha) and fluxes (kg P/ha/day) at site %s in year %d\n", site, year);
	fprintf(fsp, "Year,Day,Fertilizer_P,Manure_P,OrganicP,LabileP,SorbedP,ComplexP,CropDemandP,DayUptakeP,Runoff_P,Leach_P, SO4, H2S_flux\n");
	}
	fprintf(fsp, "%3d,%3d,", year,jday);
	fprintf(fsp, "%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n", 
		day_inFertP, day_inManureP, Profile_OrgP, Profile_LabP, Profile_AdsP, Profile_ComP, 
		day_P_demand[1], day_P_uptake[1], day_runoff_P, day_leach_P, SO4[1], day_H2S_flux);
		    
    return( 0 );
}

int class_model::write_out_dayg( FILE *fg )//day_Graze
{
	float Tgrass=0.0;
	float dung_C=0.0, dung_N=0.0, urine_C=0.0, urine_N=0.0, dung_P=0.0;
	for (int i=1; i<=CropNumbers; i++)
	{
		Tgrass = Grain_Wt[i] + Leaf_Wt[i] + Stem_Wt[i];
	}

	for(int i2=1; i2<=5; i2++)
	{
		dung_C += day_graze_dung_C[i2];
		dung_N += day_graze_dung_N[i2];
		urine_C += day_graze_urine_C[i2];
		urine_N += day_graze_urine_N[i2];
		dung_P += day_graze_dung_P[i2];
	}

   if (jday==1&&year==1)
   {
	fprintf(fg, "Daily grazing-induced C and N fluxes at site %s in year %d\n", site, year);
	fprintf(fg, "______________________________________________________________________________________________________________________________________________________\n");   
	fprintf(fg, "Year,Day,Grass shoot-C (kgC/ha),Dairy,Beef,Pig,Sheep,Horse,Hours,Grazed-C,Grazed-N,Dung-C,Dung-N,Urine-C, Urine-N,Dung_P,Food deficit\n"); 
	fprintf(fg, ",,kg C/ha,heads/ha,heads/ha,heads/ha,heads/ha,heads/ha,heads/ha,kgC/ha/day,kgN/ha/day,kgC/ha/day,kgN/ha/day,kgC/ha/day,kgN/ha/day,kgP/ha/day\n");   
	fprintf(fg, "______________________________________________________________________________________________________________________________________________________\n");
   }

	fprintf(fg, "%3d,%3d,", year,jday);
	fprintf(fg, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%5.2f,", 
		Tgrass, H_dairy, H_beef, H_pig, H_sheep, H_horse, H_hrs);
	fprintf(fg, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n",
		    day_GrazeC, day_GrazeN, dung_C, dung_N, urine_C, urine_N, dung_P, day_deficit); //day_grass_consume
	
    return( 0 );
}

int class_model::write_out_dayp(FILE *fcrop)//Day_FieldCrop
{
	
	int i;

	if (jday==1&&year==1)
	{
		fprintf(fcrop, "Daily crop growth at site %s",site);
		fprintf(fcrop, " in year %d\n", year);
		fprintf(fcrop, "Year,");
		fprintf(fcrop, "Day,");
		fprintf(fcrop, "Temperature,Precipitation,Irrigation,Radiation,PET,Transpiration,Evaporation,All_crops,All_crops,All_crops,All_crops,");		
		//for(int i=1;i<=CropNumbers;i++) fprintf(fcrop, ",Crop %d,,,,,,,,,,,,,,,,,,,,,,,,,,,", i);

		//headers for per crop type
		for (int i = 1; i <= 4; i++) {
			fprintf(fcrop, "Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d", i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i);//20 of 31 columns
			fprintf(fcrop, ",Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,Crop %d,", i, i, i, i, i, i, i, i, i, i, i,i,i,i);}//11 of 34columns
		fprintf(fcrop, "\n");	

		//2nd row headers for all crops
		fprintf(fcrop, "Annual,Daily,Daily,Daily,Daily,Daily,Daily,Daily,Daily,LeafC,StemC,RootC,GrainC,");
		//fprintf(fcrop, ",,,,,,,,LeafC,StemC,RootC,GrainC,");
		//for(int i3=1;i3<=CropNumbers;i3++) 
		
		for(int i3=1;i3<=4;i3++) //2nd level headers per Crop type
		fprintf(fcrop, "CropID,TDD,GrowthIndex,Water_demand,Water_stress,N_demand,N_stress,Temp_Stress,LAI,N_from_soil,N_from_air_NH3,N_fixation,Day_N_increase,TotalCropN,DailyCropGrowth,DayLeafGrowth,DayStemGrowth,DayRootGrowth,DayGrainGrowth,DayShootSenes,DayRootSenes,DayShootSenesN,LeafC,StemC,RootC,GrainC,LeafN,StemN,RootN,GrainN,PodC,PodN,RootExuC,RootExuN,");
		fprintf(fcrop, "\n");
		
		fprintf(fcrop, "(Year),JD,degree_C,mm,mm,MJ/m2/d,mm,mm,mm,kgC/ha/d,kgC/ha,kgC/ha,kgC/ha,");		
	//	fprintf(fcrop, ",degree_C,mm,mm,MJ/m2/d,mm,mm,mm,kgC/ha/d,kgC/ha,kgC/ha,kgC/ha,");		
	//	for(int i4=1;i4<=CropNumbers;i4++) 

		for(int i4=1;i4<=4;i4++)  // 3rd level headers per crop type 
		fprintf(fcrop, "#,degree_C,index,mm,index,kgN/ha/d,index,index,(LAI),kgN/ha/d,kgN/ha/d,kgN/ha/d,kgN/ha/d,kgN/ha,kgC/ha/d,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgN/ha,kgN/ha,kgN/ha,kgN/ha,kgC/ha,kgN/ha,kgC/ha,kgN/ha,");
	//	fprintf(fcrop, ",degree_C,,mm,,,kgN/ha/d,,kgN/ha/d,kgN/ha/d,kgN/ha/d,kgN/ha/d,kgN/ha,kgC/ha/d,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgC/ha,kgN/ha,kgN/ha,kgN/ha,kgN/ha,oC,");
		fprintf(fcrop, "\n");	
	}
    fprintf(fcrop, "%4d,", year);
	fprintf(fcrop, "%4d,", jday);

	
	fprintf(fcrop, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,", 
		air_temp, precipitation*1000.0,day_irri*1000.0, DayPETRs,DayPET*1000.0, day_transp*1000.0, day_evapor*1000.0,
		Leaf_Wt[1]+Leaf_Wt[2]+Leaf_Wt[3]+Leaf_Wt[4], Stem_Wt[1] + Stem_Wt[2] + Stem_Wt[3] + Stem_Wt[4], Root_Wt[1] + Root_Wt[2] + Root_Wt[3] + Root_Wt[4],
		Grain_Wt[1]+Grain_Wt[2]+Grain_Wt[3]+Grain_Wt[4]);/// was writing out PAR vs DayPETRs for radiation.
	
	
	
	
	//for(cwc=1;cwc<=CropNumbers;cwc++)
	for(cwc=1;cwc<=4;cwc++) //outputs per crop type
	{ 
	


		fprintf(fcrop, "%10d,%10.2f,%10.6f,%10.2f,%10.2f,", 
			crop[cwc],TDD[cwc], PGI[cwc],PPT[cwc]*1000.0, day_DWater[cwc]);
		fprintf(fcrop, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%16.7f,%16.7f,",
			day_N_demand[cwc], N_stress[cwc], cropTempStress[cwc], lai[cwc], day_nup[cwc], day_plant_nh3[cwc], day_fixN[cwc], Day_GrowthN[cwc],
			plantn[cwc]);
		fprintf(fcrop, "%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%10.2f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%10.2f,%10.2f,%10.2f,%10.2f,",
				   Day_C_growth[cwc], dayG_leaf[cwc],dayG_stem[cwc],dayG_root[cwc],dayG_grain[cwc],DayLeafSenes[cwc]+DayStemSenes[cwc], DayRootSenes[cwc], (yrShootSenesN[cwc]),
				   Leaf_Wt[cwc], Stem_Wt[cwc], Root_Wt[cwc], Grain_Wt[cwc],
				   LeafN[cwc], StemN[cwc], RootN[cwc], GrainN[cwc], Pod_Wt[cwc],PodN[cwc],Root_ExuC[cwc],Root_ExuN[cwc]);//cut_root_litter[cwc]+fine_root_pool[cwc]	//cTT[ccwc]=cold tolerance
		
		
				if(harvest_flag[cwc]==1) //For ensuring that the Day_field_crop.csv outputs match the multi-year-csv.
	{	
	Leaf_Wt[cwc] = 0.0;
	Stem_Wt[cwc] = 0.0;
	Grain_Wt[cwc] = 0.0;
	Pod_Wt[cwc] = 0.0;
	Root_ExuC[cwc] = 0.0;
	Root_ExuN[cwc] = 0.0;
	seed[cwc] = 0;
	//crop_days[ccwc]=0;
	PGI[cwc] = 0.0;
	//*cwc_p = ccwc;
	//I_Stage = 7;
	plantn[cwc]=0.0;
	Root_Wt[cwc] = 0.0;
	Grain_Wt[cwc] = 0.0;
	Leaf_Wt[cwc] = 0.0;
	Stem_Wt[cwc] = 0.0;
	LeafN[cwc] = 0.0;
	StemN[cwc] = 0.0;
	GrainN[cwc] = 0.0;
	PodN[cwc] = 0.0;
	RootN[cwc] = 0.0;
	harvest_flag[cwc]=0;
	}
	
	}
	fprintf(fcrop, "\n");
	


    return( 0 );
}

int class_model::write_out_dayEh( FILE *fEh )
{
   if (jday==1)
   {
	fprintf(fEh, "Daily Eh-driven processes at site %s",site);
	fprintf(fEh, " in year %d\n", year);
	fprintf(fEh, "____________________________________________________");
	fprintf(fEh, "____________________________________________________");
	fprintf(fEh, "________\n");
	fprintf(fEh, "Julian    Eh     Decom.  Nitri. Denit. CH4-pr CH4-ox    CH4     N2O      SOC      O2   soil_N2O\n");
	fprintf(fEh, "day       mV     kg C or N/ha/dayg\n");
	fprintf(fEh, "____________________________________________________");
	fprintf(fEh, "____________________________________________________");
	fprintf(fEh, "________\n");
    }
	fprintf(fEh, "%3d,", jday);
	fprintf(fEh, "%7.2f,%7.2f,%7.4f,%7.4f,%7.2f,%7.2f,%7.2f,%7.4f,%9.2f,%7.2f,%7.2f\n",
					Eh[1],			
					day_co2, 
					day_soil_nitrify,
					day_soil_denitrification,
					ch4_prod,
					ch4_day_oxid,
					day_ch4,
					day_soil_an_n2o,
					day_co2 - day_addC,
					O2_old[3],
					w_n2o);

    return( 0 );
}

void class_model::write_out_dayCB(FILE *fCB, FILE *fNB)  //BALANCE FILES Day_SoilBalanceN
{	
	//static float old_SOC;
	double Balance1, Balance2, net;//  = (day_co2 + day_balance_ch4 + day_leachhu)-(day_addC + day_addmc + day_RootInput_DOC +day_root_resp);//+day_RootDOC

    if (jday==1&&year==1)
    {
		fprintf(fCB, "Daily soil C balance at site %s in year %d. Unit: kg C/ha\n", site, year);
		fprintf(fCB, "Year,Day,IniPool  ,IniPool  ,IniPool ,IniPool  ,IniPool,IniPool,IniPool,IniPool,EndPool  ,EndPool  ,EndPool ,EndPool  ,EndPool,EndPool,EndPool,EndPool, InputC,InputC,InputC,OutputC,OutputC,OutputC,OutputC,OutputC,C-balance,error_SOC_only,error_total,\n");
		fprintf(fCB, "Year,Day,Litter,Humads,Humus,BlackC,DOC ,CO2 ,CH4 ,SOC ,Litter,Humads,Humus,BlackC,DOC ,CO2 ,CH4 ,SOC, Litter,Manure,RootExudation,CO2flux,CH4flux,LeachSOC,LeachDOC,RunoffC,error,error_SOC_only,error_total,");//error_total,\n");


#ifdef DEBUG_CBALANCE
		fprintf(fCB, "DBG_co2_pre,DBG_cmine_pre,DBG_dCO2pool,DBG_dDOCpool,");
		fprintf(fCB, "DBG_doc_to_co2,DBG_dn_co2,DBG_doc_prod_total,");
		fprintf(fCB, "DBG_doc_rcvl,DBG_doc_rcl,DBG_doc_rcr,DBG_doc_humads,DBG_doc_humus,DBG_doc_manure,");
#endif
		fprintf(fCB, "\n");



	}

	Balance1 = (end_prof_SOC - ini_prof_SOC) - (day_addC+day_addmc+day_RootInput_DOC) + (day_co2+day_balance_ch4+day_leachhu+day_leach_DOC+day_runoff_C);//+day_root_resp


	double Balance_total = ((end_prof_SOC + end_prof_inorgC) - (ini_prof_SOC + ini_prof_inorgC))- (day_addC + day_addmc + day_RootInput_DOC)+ (day_co2 + day_balance_ch4 + day_leachhu + day_leach_DOC + day_runoff_C);

	// For clarity we also print error_SOC_only = Balance1 (so both are visible side-by-side)
	double Balance_SOC_only = Balance1;

	
	fprintf(fCB, "%4d,", year);
	fprintf(fCB, "%4d,", jday);
	
	fprintf(fCB, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", 	
		ini_prof_litter, ini_prof_humad, ini_prof_humus, ini_prof_blackc, ini_prof_doc, ini_prof_co2, ini_prof_ch4, ini_prof_SOC);
    fprintf(fCB, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,", 
		end_prof_litter, end_prof_humad, end_prof_humus, end_prof_blackc, end_prof_doc, end_prof_co2, end_prof_ch4, end_prof_SOC);
	//fprintf(fCB, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.8lf,%7.8lf,%7.8lf,\n",
		//day_addC, day_addmc, day_RootInput_DOC, day_co2, day_balance_ch4, day_leachhu, day_leach_DOC, day_runoff_C, Balance1, Balance_SOC_only, Balance_total);


	//new
	fprintf(fCB, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.8lf,",
		day_addC, day_addmc, day_RootInput_DOC,
		day_co2, day_balance_ch4, day_leachhu, day_leach_DOC, day_runoff_C,
		Balance1 /* error */);

	fprintf(fCB, "%7.8lf,%7.8lf,", Balance_SOC_only, Balance_total);

#ifdef DEBUG_CBALANCE
	fprintf(fCB, "%7.4f,%7.4f,%7.4f,%7.4f,",
		day_co2_before_roll, day_cmine_before_roll,
		dCO2_pool_today, dDOC_pool_today);

	fprintf(fCB, "%7.4f,%7.4f,%7.4f,",
		day_doc_to_co2, day_dn_co2, day_doc_prod_total);

	fprintf(fCB, "%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,",
		day_doc_from_rcvl, day_doc_from_rcl, day_doc_from_rcr,
		day_doc_from_humads, day_doc_from_humus, day_doc_from_manure);
#endif

	fprintf(fCB, "\n");
	//end new
		
		
	//	ini_prof_SOC, prof_SOC, Balance1, day_addC, day_addmc, day_RootInput_DOC,day_root_resp,day_co2, day_balance_ch4, day_leachhu, Balance2, net);

	//old_SOC = prof_SOC;  

	///////////////////////////////////////////////////////////////////////////////////
	//static float old_SON, old_SIN, old_clay_N;
	
	Balance2 = day_inN - day_outN;
	Balance1 = (end_SON+end_SIN)-(ini_SON+ini_SIN);
	net = Balance2-Balance1;

	if (jday==1 && year==1)
    {
		fprintf(fNB, "Daily soil N balance at site %s in year %d. Unit: kg N/ha\n", site, year);
		fprintf(fNB, "___________________________________________________________________________________________________________________________________________________________________________\n");
		fprintf(fNB, ",N Pools,,,,,Influx N,,,,,,,Efflux N\n");
		fprintf(fNB, "Year,Day,iniSON,iniSIN,endSON,endSIN,dSoilN,Deposit,Fertilizer,Manure,Litter,Irrigation,Fixation,Sum-In,SoilNUptake,NH3,N2O,NO,N2,N-leach,Sum-Out,dFluxN,Error\n");
		fprintf(fNB, "___________________________________________________________________________________________________________________________________________________________________________\n");

		//old_SON = prof_SON;
		//old_SIN = prof_SIN;
		//old_clay_N = day_clay_N;
		
    }
	fprintf(fNB, "%4d,", year);
	fprintf(fNB, "%4d,", jday);
	fprintf(fNB, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",					
				//old_SON, prof_SON, old_SIN, prof_SIN, old_Pool_leach_NO3, Pool_leach_NO3, Balance1);
				ini_SON, ini_SIN, end_SON, end_SIN, Balance1);
	
	fprintf(fNB, "%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,",					
				day_inRainN, day_inFertN, day_inManureN, day_inLitterN, day_irri_N, 
				day_soilN_from_Nfixation[1]+day_soilN_from_Nfixation[2]+day_soilN_from_Nfixation[3], day_inN);
	
	fprintf(fNB, "%7.2f,%7.2f,%7.6f,%7.6f,%7.6f,%7.2f,%7.2f,",					
				day_nup[1]+day_nup[2]+day_nup[3], day_soil_nh3+day_vol_nh3, 
				day_soil_an_n2o, day_soil_an_no, day_soil_n2, 
				day_leach_NO3+day_leach_urea+day_leachhu/rcnm+by_pass_no3, day_outN);

	fprintf(fNB, "%7.2f,%7.2f\n", Balance2, net-(day_soilN_from_Nfixation[1]+day_soilN_from_Nfixation[2]+day_soilN_from_Nfixation[3]));//soilN_from fixation.

    //old_SON = prof_SON;
	//old_SIN = prof_SIN;
	//old_clay_N = day_clay_N;
}

int class_model::write_out_daym(FILE *fma)//day_fieldManage
{
	if (jday==1&&year==1)
     {
		fprintf(fma, "Daily management at site %s in year %d\n\n", site, year);
		fprintf(fma, "Year,Day,Irrigation (mm),Fertilizer (kgN/ha),Fertilizer (kgP/ha),Manure (kgN/ha),Manure (kgP/ha),All_Plant_cut (kg C/ha),CROP1_ID,Crop1_CutC (kgC/ha),Crop1_CutN  (kgN/ha),CROP2_ID,Crop2_CutC (kgC/ha),Crop2_CutN (kgN/ha),CROP3_ID,Crop3_CutC (kgC/ha),Crop3_CutN (kgN/ha),CROP4_ID,Crop4_CutC (kgC/ha),Crop4_CutN (kgN/ha)\n\n");
     }
	
	fprintf(fma, "%3d,%3d,%7.4f,%7.1f,%7.1f,%7.1f,%7.1f,%7.1f,%3d,%7.1f,%7.1f,%3d,%7.1f,%7.1f,%3d,%7.1f,%7.1f,%3d,%7.1f,%7.1f\n",
		    year,jday, day_irri*1000.0, day_inFertN, day_inFertP,day_inManureN, day_inManureP, DayGrassCut, crop[1], DayGrassCut_C[1], DayGrassCut_N[1], crop[2], DayGrassCut_C[2], DayGrassCut_N[2], crop[3], DayGrassCut_C[3], DayGrassCut_N[3], crop[4], DayGrassCut_C[4], DayGrassCut_N[4]);

	return (0);
}

#ifdef ISOTOPE
int class_model::write_out_dayisotope(FILE *fis)
{
	if (jday==1)
    {
		fprintf(fis, "Daily soil C isotope at site %s in year %d, unit: kg C/ha\n\n", site, year);
		fprintf(fis, "Day,day_prod_DOC, day_DOC_from_root, day_DOC_from_SOM, day_prod_CO2, day_CO2_from_root, day_CO2_from_SOM, CO2_pool, day_prod_H2, day_SOM_H2, H2_pool, CH4_prod_from_CO2,CH4_prod_from_DOC,CH4_prod_sum, CH4_oxid,CH4_flux,CH4_pool,	DOC-13,DOC-12,delta-DOC,CO2-13,CO2-12,delta-CO2,CH4_prod_13,CH4_prod_12,CH4_oxid_13,CH4_oxid_12,CH4_flux_13,CH4_flux_12,delta_flux_CH4,CH4_pool_13,CH4_pool_12,delta-sCH4(10cm),delta-sCH4(20cm),delta-sCH4(30cm),delta-sCH4(40cm),delta-sCH4(50cm)\n"); 
	}
	
	fprintf(fis, "%3d,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.2f,%7.4f,%7.4f,%7.4f,%7.2f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.2f,%7.4f,%7.4f,%7.4f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f\n",
		    
			jday, 
			day_DOC_prod, day_Root_DOC, day_SOM_DOC, 
			day_CO2_prod, day_Root_CO2, day_SOM_CO2, day_ch4_co2_pool,
			day_H2_PROD, day_SOM_H2, day_ch4_H2_pool,
			ch4_prod1,ch4_prod2,ch4_prod, ch4_day_oxid,day_ch4,day_ch4_pool,

			day_DOC_13, day_DOC_12, del13C_DOC*1000.0,
			day_CO2_13, day_CO2_12, del13C_CO2*1000.0,			
			day_prod_CH4_13, day_prod_CH4_12,			
			day_oxid_CH4_13, day_oxid_CH4_12,
			fCH4_13, fCH4_12, 
			del_fCH4*1000.0,
			day_CH4_13, day_CH4_12, 			
			delCH4[LL1]*1000.0,delCH4[LL2]*1000.0,delCH4[LL3]*1000.0,delCH4[LL4]*1000.0,delCH4[LL5]*1000.0);

	return(0);
}
#endif

int class_model::write_out_daymicrobe(FILE *fmb)//day_microbe
{
	if (jday==1&&year==1)
     {
		fprintf(fmb, "Daily soil microbial activity at site %s in year %d\n\n", site, year);
		fprintf(fmb, "Year,Day,Decomposition (kgC/ha),Nitrification (kgN/ha),Denitrification (kgN/ha),Methanogenesis (kgC/ha),Methanotrophy (kgC/ha), Methanogen_index (1cm), Methanogen_index (10cm), Methanogen_index (20cm), Methanogen_index (30cm), Methanogen_index (40cm),Methanogen_index (50cm),"); 
		fprintf(fmb, "H2(kgH/ha/day-10cm), H2(kgH/ha/day-20cm), H2(kgH/ha/day-30cm), H2(kgH/ha/day-40cm), H2(kgH/ha/day-50cm),");  
		fprintf(fmb, "DOC(kgC/ha/day-10cm), DOC(kgC/ha/day-20cm), DOC(kgC/ha/day-30cm), DOC(kgC/ha/day-40cm), DOC(kgC/ha/day-50cm),"); 
		fprintf(fmb, "CO2(kgC/ha/day-10cm), CO2(kgC/ha/day-20cm), CO2(kgC/ha/day-30cm), CO2(kgC/ha/day-40cm), CO2(kgC/ha/day-50cm),");
		fprintf(fmb, "DOC_CH4(kgC/ha/day-10cm), DOC_CH4(kgC/ha/day-20cm), DOC_CH4(kgC/ha/day-30cm), DOC_CH4(kgC/ha/day-40cm), DOC_CH4(kgC/ha/day-50cm),");
		fprintf(fmb, "CO2_CH4(kgC/ha/day-10cm), CO2_CH4(kgC/ha/day-20cm), CO2_CH4(kgC/ha/day-30cm), CO2_CH4(kgC/ha/day-40cm), CO2_CH4(kgC/ha/day-50cm),");
		fprintf(fmb, "CH4_Oxi(kgC/ha/day-10cm), CH4_Oxi(kgC/ha/day-20cm), CH4_Oxi(kgC/ha/day-30cm), CH4_Oxi(kgC/ha/day-40cm), CH4_Oxi(kgC/ha/day-50cm)\n\n");
     }
	
	fprintf(fmb, "%3d,%3d,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.5f,%7.5f,%7.5f,%7.5f,%7.5f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f,%7.4f\n",
		    year,jday, soil_hete_CO2, day_soil_nitrify, day_soil_denitrification,ch4_prod, ch4_day_oxid, F_methanogen[LL0], F_methanogen[LL1], F_methanogen[LL2], F_methanogen[LL3], F_methanogen[LL4], F_methanogen[LL5],
			day_H2_prod[LL1], day_H2_prod[LL2], day_H2_prod[LL3], day_H2_prod[LL4], day_H2_prod[LL5], 
			ch4_doc_pool[LL1], ch4_doc_pool[LL2], ch4_doc_pool[LL3], ch4_doc_pool[LL4], ch4_doc_pool[LL5],
			day_ch4_CO2[LL1],day_ch4_CO2[LL2],day_ch4_CO2[LL3],day_ch4_CO2[LL4],day_ch4_CO2[LL5],
			day_ch4_2[LL1], day_ch4_2[LL2], day_ch4_2[LL3], day_ch4_2[LL4], day_ch4_2[LL5], 
			day_ch4_1[LL1], day_ch4_1[LL2], day_ch4_1[LL3], day_ch4_1[LL4], day_ch4_1[LL5], 
			day_ch4_3[LL1], day_ch4_3[LL2], day_ch4_3[LL3], day_ch4_3[LL4], day_ch4_3[LL5]);

	return (0);
}

int class_model::write_out_cropini(int MODE )
{



	int KK=0, LeftDays[8];
    FILE *fp;
    char F_INI[80];
    
	for(int i=1; i<=CropNumbers; i++)
	{
		if((crop_flag[i]==1||PerennialFlag[i]==1)&&harvest_flag[i]==0) 
		{
			KK++;
			crop[KK]=crop[i];
			crop_days[KK] = crop_days[i];
			sprintf(crop_name[KK], "%s", crop_name[i]);
			seed[KK]=seed[i];
			plantn[KK]=plantn[i];
			PlantTakeN[KK]=PlantTakeN[i];
			demandn[KK]=demandn[i];
			lai[KK]=lai[i];
			Leaf_Wt[KK]=Leaf_Wt[i];
			Stem_Wt[KK]=Stem_Wt[i];
			Grain_Wt[KK]=Grain_Wt[i];
			Root_Wt[KK]=Root_Wt[i];
			TDD[KK]=TDD[i];
			crop_trans[KK]=crop_trans[i];
			PGI[KK]=PGI[i];

			WCLeftDays[KK]=grow_days[i]-seed[i];
			GrainYield[KK]=GrainYield[i];
			HarvestYear[KK]=HarvestYear[i]-1;
			jdseed[KK]=jdseed[i];
			grow_days[KK]=grow_days[i];
			left_perc[KK]=left_perc[i];
			maxmn[KK]=maxmn[i];
			base_maxmn[KK] = base_maxmn[i];
			InitialBiomass[KK]=InitialBiomass[i];
			GrowthVegetative[KK]=GrowthVegetative[i];
			GrowthReproductive[KK]=GrowthReproductive[i];
			PsnEfficiency[KK]=PsnEfficiency[i];
			PsnMax[KK]=PsnMax[i];
			CoverCrop[KK]=CoverCrop[i];
			PerennialFlag[KK]=PerennialFlag[i];
			grain[KK]=grain[i];
			stem[KK]=stem[i];
			leaf[KK]=leaf[i];
			root[KK]=root[i];
			base_graincn[KK]=base_graincn[i];
			base_leafcn[KK]=base_leafcn[i];
			base_stemcn[KK]=base_stemcn[i];
			base_rootcn[KK]=base_rootcn[i];
			max_TDD[KK]=max_TDD[i];
			wreq[KK]=wreq[i];
			base_wreq[KK]=base_wreq[i];
			//max_root_length[KK]=max_root_length[i];
			OptimumT[KK]=OptimumT[i];
			ini_N_fix[KK]=ini_N_fix[i];
			max_root_length[KK]=max_root_length[i];
			maxmn[KK] = ini_maxmn[i]; //turned this off Nov 13_2024
			plantcn[KK] = plantcn[i];
			totalFFPGI[KK] = totalFFPGI[i];
			root_depth[KK]= root_depth[i];
			TreeMatuAge[KK] = TreeMatuAge[i];
			TreeCurretAge[KK] = TreeCurretAge[i]+1;
			TreeLeafMax[KK] = TreeLeafMax[i];
			TreeLeafMin[KK] = TreeLeafMin[i];
			maturity_flag[KK] = maturity_flag[i];
			GrainFill[KK]=GrainFill[i];
			RootShape[KK]=RootShape[i];
			LAImax[KK] = LAImax[i];
			FrostKill[KK] = FrostKill[i];
			cHRMX[KK] = cHRMX[i];
			cDRMX[KK] = cDRMX[i];
			cTMX[KK] = cTMX[i];
			pDFMX[KK] = pDFMX[i];
			rootMResp[KK] = rootMResp[i];
			rootNewResp[KK] = rootNewResp[i];
			shootMResp[KK] = shootMResp[i];
			shootNewResp[KK] = shootNewResp[i];
			kext1[KK] = kext1[i];//Theo
			kext2[KK] = kext2[i];//Theo
			cmaxh[KK] = cmaxh[i];	//Theo
			cropGRate[KK] = cropGRate[i];
			cropTime[KK] = cropTime[i];
			rueHI[KK] = rueHI[i];
			delayP[KK] = delayP[i];
		}
	}

	IniCropNumbers = KK;

	if(LandUse==6) stem_age++;
	else stem_age = 0;

    sprintf(F_INI, "%s\\Inputs\\cropini-%d", OUTPUT, year+1);    
	fp = fopen(F_INI, "w");
	if (fp == NULL) note(1, F_INI); 
	fprintf(fp, "%d\n", IniCropNumbers);
	








	for(int iw=1; iw<=IniCropNumbers; iw++)
	{
		
		
		//Included a fix to allow for the change in a perrenial cultivar over time. Need to add a crop every year in the DNDC dnd. 

if(PerennialFlag[iw]==1) //checks to see if Perrenial flag is marked.//&& SimuYears==year
{			
FILE  *fp;


//FCT401.Format("%s\\inputs", OUTPUT);
char  F_CROP[200];//define a directory using F_CROP
float junk,cropNum;//define a junk variable so that you can scan in and parse file without being forced to store values
sprintf(F_CROP, "%s\\Inputs\\crop-%d", OUTPUT, year+1);//Not sure why but you need this to force the directory structure
			
		fp = fopen(F_CROP, "r"); //Opens the FILE fp for read-access with F_CROP directory
		//if ( fp == NULL ) note(0,F_CROP);
		int endFlag=0;

		if ( fp == NULL )
		{endFlag=1;}
		
    if(endFlag==0)
	{
	fscanf(fp, "%d",&cropNum);//scan's first fvalue of \\Inputs\\CROP-* but doesn't store it.
	
		if (cropNum == 0)//brian Nov2021 - added to control the perrenial read in for changes in fallow years. Doesn't let changing of stand age atm. 
		{
		fscanf(fp, "%d %s %d %d %f %d",
			&crop[iw], crop_name[iw], &junk, &junk, &GrainYield[iw], &junk);//Reads in the various variables and stores some and discards other in junk.
		fscanf(fp, "%d %d %f %f %d",
			&junk, &junk, &junk, &maxmn[iw], &junk);
		fscanf(fp, "%f %d %f %f %f",
			&junk, &junk, &junk, &junk, &junk);
		//reading maxmn from file 

		   //&InitialBiomass[iw], &GrowthVegetative[iw], &GrowthReproductive[iw],
		   //&PsnEfficiency[iw], &PsnMax[iw]);
		fscanf(fp, "%d", &junk);
		fscanf(fp, "%d", &junk);
		fscanf(fp, "%f %f %f %f", &grain[iw], &leaf[iw], &stem[iw], &root[iw]);
		fscanf(fp, "%f %f %f %f", &base_graincn[iw], &base_leafcn[iw], &base_stemcn[iw], &base_rootcn[iw]);
		fscanf(fp, "%f %f %f %f %f", &max_TDD[iw], &wreq[iw], &OptimumT[iw], &ini_N_fix[iw], &max_root_length[iw]);
		fscanf(fp, "%f %d", &plantP[iw], &stem_age);
		fclose(fp);//closes the file fp.

				//adjust rooting Depth based on clay content
		float rootPenetration;
		rootPenetration = -1.1429 * clay[1] + 1.2857;
		rootPenetration = min(1.0, max(0.0, rootPenetration));
		max_root_length[iw] = rootPenetration * max_root_length[iw];

		}
		else
		{
		fclose(fp);//closes the file fp.
		}
	}
	
}

//end fix for perrrenial crop read in.




		fprintf(fp, "%d %d %f %f %f %f\n",crop[iw], seed[iw], plantn[iw], PlantTakeN[iw], demandn[iw], lai[iw]);
		fprintf(fp, "%f %f %f %f %f\n", Leaf_Wt[iw], Stem_Wt[iw], Grain_Wt[iw], Root_Wt[iw], TDD[iw]);
		fprintf(fp, "%f %f\n", crop_trans[iw], plantcn[iw]);
		//////////////////////////////////////////
		fprintf(fp, "%d %s %d %d %f %d\n", 
			crop[iw], crop_name[iw], 1, WCLeftDays[iw], GrainYield[iw], HarvestYear[iw]);
		fprintf(fp, "%d %d %f %f %f\n", 
			jdseed[iw], grow_days[iw], left_perc[iw], maxmn[iw], base_maxmn[iw]);//111			
		fprintf(fp, "%f %d %f %f %f\n", 
			   InitialBiomass[iw], Transplant[iw], PGI[iw], PsnEfficiency[iw], PsnMax[iw]);
		fprintf(fp, "%d\n", CoverCrop[iw]);
		fprintf(fp, "%d\n", PerennialFlag[iw]);
		fprintf(fp, "%f %f %f %f\n", grain[iw], leaf[iw], stem[iw], root[iw]);
		fprintf(fp, "%f %f %f %f\n", base_graincn[iw], base_leafcn[iw], base_stemcn[iw], base_rootcn[iw]);//Brian
		fprintf(fp, "%f %f %f %f %f\n", max_TDD[iw], base_wreq[iw], OptimumT[iw], ini_N_fix[iw], max_root_length[iw]);//Brian
		fprintf(fp, "%f %d\n", plantP[iw], stem_age);
		fprintf(fp, "%f %f %f %f\n", TreeMatuAge[iw], TreeCurretAge[iw], TreeLeafMax[iw], TreeLeafMin[iw]);
		fprintf(fp, "%d\n", maturity_flag[iw]);
		fprintf(fp, "%d\n", crop_days[iw]);
		
		//adjust rooting Depth based on clay content
		float rootPenetration;
		rootPenetration = -1.1429 * clay[1] + 1.2857;
		rootPenetration = min(1.0, max(0.0, rootPenetration));
		max_root_length[iw] = rootPenetration * max_root_length[iw];
/*
		if(HarvestYear[iw+1]==2)
		{
			fprintf(fp, "%f\n",totalFFPGI[iw+1]);
		//	fprintf(fp, "%f\n",crop_days[iw]);
		}
		else
		{
			fprintf(fp, "%f\n",totalFFPGI[iw]);
			//fprintf(fp, "%f\n",crop_days[iw]);
		}

		*/
		///////////////////////////////////////////
		/*
		if(HarvestYear[iw+1]==2)
		{
			fprintf(fp, "%f\n",root_depth[iw+1]);
		//	fprintf(fp, "%f\n",crop_days[iw]);
		}
		else
		{
			root_depth[iw]=0.0;
			fprintf(fp, "%f\n",root_depth[iw]);
		}
		*/
		fprintf(fp, "%f\n",totalFFPGI[iw]);
		fprintf(fp, "%f\n",root_depth[iw]);
		fprintf(fp, "%d\n",crop_water_stress_days[iw]);
		fprintf(fp, "%f\n",crop_water_stress[iw]);
		fprintf(fp, "%d\n",crop_N_stress_days[iw]);
		fprintf(fp, "%f\n",crop_N_stress[iw]);
		fprintf(fp, "%f\n",root_length[iw]);
		fprintf(fp, "%d\n",perRegrow[iw]);
		fprintf(fp, "%d\n",vernal[iw]);
		fprintf(fp, "%f\n",cTT[iw]);
		fprintf(fp, "%f\n",pDFCUM[iw]);
		fprintf(fp, "%d\n",RootShape[iw]);
		fprintf(fp, "%f\n",GrainFill[iw]);
		fprintf(fp, "%f\n", LAImax[iw]);
		fprintf(fp, "%f\n", FrostKill[iw]);
		fprintf(fp, "%f\n", cHRMX[iw]);
		fprintf(fp, "%f\n", cDRMX[iw]);
		fprintf(fp, "%f\n", cTMX[iw]);
		fprintf(fp, "%f\n", pDFMX[iw]);
		fprintf(fp, "%f\n", rootNewResp[iw]);
		fprintf(fp, "%f\n", rootMResp[iw]);
		fprintf(fp, "%f\n", shootNewResp[iw]);
		fprintf(fp, "%f\n", shootMResp[iw]);
		fprintf(fp, "%lf\n", kext1[iw]); //Theo
		fprintf(fp, "%lf\n", kext2[iw]);//Theo
		fprintf(fp, "%lf\n", cmaxh[iw]);//Theo
		fprintf(fp, "%f\n", cropGRate[iw]);//Theo
		fprintf(fp, "%f\n", cropTime[iw]);//Theo
		fprintf(fp, "%f\n", rueHI[iw]);//Theo
		fprintf(fp, "%f\n", delayP[iw]);//Theo

		
		for(int ip=1;ip<8;ip++)
		{
			fprintf(fp, "%f\n", per[iw][ip]);
		}
		

	}
	//write out the crop rotation table 
	fprintf(fp, "%d %d %d %d %d %d %d %d %d %d\n", cropRotType[0], cropRotType[1], cropRotType[2], cropRotType[3], cropRotType[4], cropRotType[5], cropRotType[6], cropRotType[7], cropRotType[8], cropRotType[9]);

	fclose( fp );

    return( 0 );
}
int class_model::write_out_extra_parm(int MODE, int SoilYear, int SimuYears)
{
   FILE *fp;
    char  SoilYr[200], EXTRA[80];
    int   l;

    if (MODE==0)
       sprintf(EXTRA, "%s\\Inputs\\extra2-%d", OUTPUT, year + 1);
	else 
	{
		if(SoilYear<=1) 
		{
			sprintf(SoilYr, "Extra2-A");
			sprintf(EXTRA, "%s\\Inputs\\%s%d", OUTPUT, SoilYr, year + 1);
		}
		else 
		{
			sprintf(SoilYr, "Extra2-B");
			sprintf(EXTRA, "%s\\Inputs\\%s%d", OUTPUT, SoilYr, year + 1);
		}
	}
    
		fp = fopen(EXTRA, "w");
		if ( fp == NULL )
		{
			char err[60];
			sprintf(err,"can not create file %s",EXTRA);
			AfxMessageBox(err);
			exit(0);
		}
		fprintf(fp, "%d\n", SoilSpinUpCounter); 		
		fclose( fp );
return(0);
}
int class_model::write_out_soil_parm(int MODE, int SoilYear, int SimuYears)
{
	FILE* fp;
	char  SoilYr[200], SOIL[80];
	int   l;
	float wrcvl = 0.0, wrcl = 0.0, wrcr = 0.0, wcrb = 0.0, wcrhl = 0.0, wcrhr = 0.0;
	float whumus = 0.0, wtcavai = 0.0, winertC = 0.0, wFreezedoc = 0.0;
	float wrnvl = 0.0, wrnl = 0.0, wrnr = 0.0, wnrb = 0.0, wnrhl = 0.0, wnrhr = 0.0, whumusn = 0.0;//, winertC/PassiveCCN, ;
	float w_n2o = 0.0, w_n2 = 0.0, w_nh3 = 0.0, w_no3 = 0.0, w_nh4 = 0.0, wurea = 0.0, day_clay_N = 0.0, wpool_no = 0.0;
	float InertN = 0.0;


	if (writeOutPlant == 1 && jday < 365)
	{
		sprintf(SOIL, "%s\\Inputs\\soil-%d", OUTPUT, 999);
	}
	else
	{
		if (MODE == 0)
			sprintf(SOIL, "%s\\Inputs\\soil-%d", OUTPUT, year + 1);
		else
		{
			if (SoilYear <= 1)
			{
				sprintf(SoilYr, "Soil-A");
				sprintf(SOIL, "%s\\Inputs\\%s%d", OUTPUT, SoilYr, year + 1);
			}
			else
			{
				sprintf(SoilYr, "Soil-B");
				sprintf(SOIL, "%s\\Inputs\\%s%d", OUTPUT, SoilYr, year + 1);
			}
		}
	}
	fp = fopen(SOIL, "w");
	if (fp == NULL)
	{
		char err[60];
		sprintf(err, "can not create file %s", SOIL);
		AfxMessageBox(err);
		exit(0);
	}



	/*
	// Outputting Stresses code
	if(year==1&&jday==1)
	{
		CString TESTFILE;
		FILE *pFile=NULL;


	TESTFILE.Format("%s\\Record\\PET.txt", OUTPUT);
	pFile = fopen (TESTFILE,"w");
	fprintf(pFile, "jday,year,fldcap\n");
	fprintf(pFile, "%1d,%1d,%7.16f\n",jday,year,fldcap[1]);
	fclose (pFile);
	}
	else
	{
	CString TESTFILE;
	FILE *pFile=NULL;


	TESTFILE.Format("%s\\Record\\PET.txt", OUTPUT);//OUTPUTBatchFileName
	pFile = fopen (TESTFILE,"a");
	fprintf(pFile, "%1d,%1d,%7.16f\n",jday,year,fldcap[1]);
	fclose (pFile);
	}
*/










	fprintf(fp, "%d\n", st[1]);
	fprintf(fp, "%s\n", soil);

	fprintf(fp, "%f %f %f %f %f %f %f %f\n", clay[1], sts[1], sks[1], ini_fldcap, wiltpt[1], LateralInflux, 0.0, 0.0);//ini_fldcap with saxton put fldcap[1]
	fprintf(fp, "%f %f %d %f %f %f %f %f %f\n", sd[1], soil_ph[1], idc, ini_ttoo[1], ini_no3, ini_nh4, resoc, ahsoc, phsoc);
	fprintf(fp, "%f %f %f %f %f %d\n", byp, h[1], th, mmm[1], vvv[1], q);
	fprintf(fp, "%f %f %f %f %d\n", clay_f1, clay_f2, qstar, by_passf, retard);
	fprintf(fp, "%f %f %f %f %f %f\n", rcnb, rcnh, rcnm, rcnrvl, rcnrl, rcnrr);
	fprintf(fp, "%f %f %f %f %f %f\n", leaf_water, surf_water, snow_pack, stub1, stub2, stub3);
	fprintf(fp, "%f %f %f\n", PassiveCCN, 0.0, 0.0);

	for (l = 1; l <= q; l++)
	{
		fprintf(fp, "\n");
		fprintf(fp, "%f %f %f\n", rcvl[l], rcl[l], rcr[l]);
		fprintf(fp, "%f %f %f %f %f\n", CRB1[l], CRB2[l], crhl[l], crhr[l], dphum[l]);
		fprintf(fp, "%f %f %f %f %f %f\n", no2[l], no3[l], nh4[l], clay_nh4[l], urea[l], nh3[l]);
		fprintf(fp, "%f %f %f\n", no[l], n2o[l], n2[l]);
		fprintf(fp, "%f %f %f\n", temp[l], day_wfps[l], ice[l]);
		fprintf(fp, "%f %f\n", Eh[l], ch4[l]);
		fprintf(fp, "%f %f %f %f\n", FreezeDOC[l], F_methanogen[l], 0.0, 0.0);
		fprintf(fp, "%f %f\n", inert_C[l], doc[l]);

		fprintf(fp, "%d %f %f %f\n", st[l], h[l], SoilDepth[l], ini_ttoo[l]);
		fprintf(fp, "%f %f %f %f %f %f %f %f\n", sts[l], clay[l], ini_fldcap, wiltpt[l], sd[l], soil_ph[l], fldcap[l], fldcapOLD[l]);//ini_fldcap soil_ph[l]
		fprintf(fp, "%f %f %f\n", mmm[l], vvv[l], sks[l]);
		fprintf(fp, "%f %f %f\n", Fe3[l], Mn4[l], SO4[l]);
		fprintf(fp, "%f %f %f %f\n", OrgP[l], AdsP[l], LabP[l], ch4_doc_pool[l]);
		fprintf(fp, "%f\n", manurePool[l]);//manurePoolCN;

		wrcvl += rcvl[l]; wrcl += rcl[l]; wrcr += rcr[l]; wcrb += (CRB1[l] + CRB2[l]); wcrhl += crhl[l]; wcrhr += crhr[l];
		whumus += dphum[l]; winertC += inert_C[l]; wFreezedoc += FreezeDOC[l];
		wtcavai += doc[l];

		w_n2o += n2o[l]; w_n2 += n2[l]; w_nh3 += nh3[l]; w_no3 += no3[l];
		w_nh4 += nh4[l]; wurea += urea[l]; day_clay_N += clay_nh4[l]; wpool_no += no[l];
	}

	fprintf(fp, "%f\n", BaseMicroIndex);
	fprintf(fp, "%f\n", (MaxWTDepth)); //m
	fprintf(fp, "%f %f\n", sslope, salinity); //0-100
	fprintf(fp, "%f\n", WaterPool);
	fprintf(fp, "%d\n", ManureDays);
	fprintf(fp, "%f\n", day_WT);
	fprintf(fp, "%d %d\n", flood_flag, FloDays);
	fprintf(fp, "%f\n", DrainEfficiency);
	fprintf(fp, "%d\n", SCSuse);
	fprintf(fp, "%f\n", PassiveC);
	fprintf(fp, "%f\n", DClitter);
	fprintf(fp, "%f\n", DChumads);
	fprintf(fp, "%f\n", DChumus);
	fprintf(fp, "%f %f %f\n", remain_root, FineRootCN, 0.0);//, fine_root_pool[1]
	fprintf(fp, "%f %f\n", frost_doc, C_soil);
	fprintf(fp, "%f %f %f %f %f %f %f\n", DayFixFert1, DayFixFert2, DayFixFert3, DayFixFert4, DayFixFert5, DayFixFert6, DayFixFert7);
	fprintf(fp, "%f %f %f %f %f %f %f\n", sfer1, sfer2, sfer3, sfer4, sfer5, sfer6, sfer7);
	fprintf(fp, "%d\n", UreaAppDays);
	fprintf(fp, "%f\n", waterpoolbd);//have to write out bulk density for waterpool here.
	fprintf(fp, "%d\n", soilProfileType);//have to write out bulk density for waterpool here.
	if (soilProfileType > 0)
	{
		fprintf(fp, "%s\n", soilProfileName);
	}
	else
	{
		fprintf(fp, "%s\n", "");
	}
		fprintf(fp, "%f %f\n", oldWP,oldFC);//write out old Wilting Point and old Field Capacity.
		fprintf(fp, "%f\n", WaterPoolMax);//write out WaterPoolMax
		fprintf(fp, "%d\n", WTL);//write out WaterPoolMax
		fprintf(fp, "%d\n", nWTL);//write out WaterPoolMax
		fprintf(fp, "%f\n", manurePoolCN);//write out manurePoolCN
		fprintf(fp, "%d\n", lastFrost);//write out lastFrost;
		fprintf(fp, "%f\n", totalManureC);//write out lastFrost;
		fprintf(fp, "%f\n", totalManureN);//write out lastFrost;
		fprintf(fp, "%d\n", fallFrost1);//write out lastFrost;
		fprintf(fp, "%f\n", manPoolRate[1]);//write out lastFrost;
		fprintf(fp, "%f\n", TotalFreezeDOC);//write out totalFreezeDOC;
		fprintf(fp, "%d\n", homoWaterFlow);//write out totalFreezeDOC;
		

		fclose( fp );

		if(SimuYears==year)
		{
			char FileB[200];
			sprintf(FileB, "%s\\Inter\\%s-%s.txt", OUTPUT, SoilYr, site);
			File_Copy(SOIL, FileB);
		}

		wrnvl = wrcvl/rcnrvl;
		wrnl = wrcl/rcnrl;
		wrnr = wrcr/rcnrr;
		wnrb = wcrb/rcnb;
		wnrhl = wcrhl/rcnh;
		wnrhr = wcrhr/rcnh;
		whumusn = whumus/rcnm;
		InertN = winertC/PassiveCCN;

		wno32 = w_no3;
		wnh42 = w_nh4;
		wnh32 = w_nh3;
		wurea2 = wurea;
		wno2 = wpool_no;
		day_clay_n2 = day_clay_N;
		end_N_gases = w_n2o + w_n2;
		EndSIN = wno32 + wnh42 + wnh32 + wurea2 + wno2 + day_clay_n2 + end_N_gases;

		whumusn2 = whumusn;
		whumus2 = whumus;

		EndLitter = wrcvl + wrcl + wrcr;
		EndActHumus = wcrb + wcrhl + wcrhr;
		EndSOC = T_SOC;//EndLitter + EndActHumus + whumus + wtcavai + winertC + wFreezedoc;		

		EndLitterN = wrnvl + wrnl + wrnr;
		EndActHumusN = wnrb + wnrhl + wnrhr;
		EndSON = EndLitterN + EndActHumusN + whumusn + InertN+totalManureN;//adding what is locked up in manurePool
		//end_N_gases = w_n2o + w_n2;
		//EndSIN = w_nh3 + w_no3 + w_nh4 + wurea + day_clay_N + wpool_no + end_N_gases;
	
    return( 0 );
}

int File_Copy(char *source, char *dest)
{
	FILE *fpi,*fpo;
	long flen,rt,num,adr;
	char *p;

	p=(char*)malloc(4096);
	if (p==NULL) {
		MessageBox(NULL,"No enough memory!","Running Error:",0);
		return -1;
	}

	fpi=fopen(source,"rb");
	if (fpi==NULL) {
		CString note;
		note.Format("Cannot open source file %s",source);
		AfxMessageBox(note);
		exit(0);
	}
	fpo=fopen(dest,"wb");
	if (fpo==NULL) {
		CString note;
		note.Format("Cannot create file %s", dest); 
		AfxMessageBox(note);
		exit(0);
	}
	flen=_filelength(_fileno(fpi));
	num=4096;
	adr=0;
	for (;;) {
		fseek(fpi,adr,SEEK_SET);
		fseek(fpo,adr,SEEK_SET);
		if (adr+num>flen) num=flen-adr;
		rt=fread(p,sizeof(char),num,fpi);
		rt=fwrite(p,sizeof(char),num,fpo);
		adr+=num;
		if (adr==flen) break;
	}
	fclose(fpi);
	fclose(fpo);
	free(p);
	return 0;
}

int class_model::write_out_wb(int Batch, char *BatchFileName, char *PassC1)//water budget file
{
    FILE *fout;
    char  junkc[400];  //liz: had to resize for longer paths

	if(Batch==1) 
	{
#ifdef DEGUI
		sprintf(junkc, "%s\\RECORD\\Site\\Multi_year_water.%s", OUTPUT, CSV);
#else
		sprintf(junkc, "%s\\Multi_year_water.%s", PassC1, CSV);
#endif
	}
	else
	{
#ifdef MANURE
		sprintf(junkc, "%s\\Multi_year_water.%s", PassC1, CSV);
#else
		sprintf(junkc, "%s\\RECORD\\Site\\Multi_year_water.%s", OUTPUT, CSV);
#endif
	}

    if (year==1)
    {		
		fout = fopen(junkc, "w" );
		if ( fout==NULL )
		{
			char err[60];
			sprintf(err,"cannot create %s",junkc);
				MessageBox(NULL,err,"Error Message",0);
				return( FILE_NOT_FOUND );
		}

		fprintf(fout, "Annual water budget for site: %s\n", site);
		fprintf(fout, "Year,Initial water pools (mm),,,,,Input (mm/yr),,,Output (mm/yr),,,,,,,End water pools (mm)\n");
		fprintf(fout, ",Soil,Snow,Leaf,Pond,Deep,Precipitation,Irrigation,Interception,Snow evap,Leaf evap,Pond evap,Soil evap,Tranpiration,Leaching,Runoff,Soil,Snow,Leaf,Pond,Deep\n");
    }
    else
    {
		fout = fopen(junkc, "a" );
		if ( fout==NULL )
		{
			char err[60];
			sprintf(err,"cannot create %s",junkc);
				MessageBox(NULL,err,"Error Message",0);
				return( FILE_NOT_FOUND );
		}
    }

	/*float wa, wb;
	if(irr_num==0)
	{
		wa = yr_prec_water;
		wb = yr_irri;
	}
	else
	{
		wa = yr_prec_water-yr_irri;
		wb = yr_irri;
	}*/

    fprintf(fout, "%3d,", year);
    fprintf(fout, "%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,",
		yr_ini_water * 1000.0,
		ini_snow_pack * 1000,
		ini_leaf_water * 1000,
		ini_surf_water * 1000,
		PoolWater0 * 1000);
    fprintf(fout, "%5.1f,%5.1f,%5.1f,",
		yr_prec_water * 1000,
		yr_irri * 1000,
		yr_intercept * 1000);
    fprintf(fout, "%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,",
		yr_snow_ev * 1000,
		yr_fol_ev * 1000,
		yr_pond_ev * 1000,
		yr_soil_ev * 1000,
		//yr_paddy_water_ev * 1000,
		yr_trans * 1000,
		yr_leach_water * 1000,
		yr_runoff * 1000);
    fprintf(fout, "%5.1f,%5.1f,%5.1f,%5.1f,%5.1f\n",
		yr_end_water * 1000,
		snow_pack * 1000,
		leaf_water * 1000,
		surf_water * 1000,
		WaterPool * 1000);
    //fprintf(fout, "\n");
    fclose( fout );

    return( 0 );
}

int class_model::multi_yr_record(int MODE, int Batch, float EndSOC, char *Pass, char *PassC1) //multi_year_summary
{
    char F_RECORD[400], BatchFileName[150];
    FILE *fp;

	float dSN = -IniSON - IniSIN + EndSON + EndSIN;

	if(Batch==0)
	{
#ifdef MANURE
		sprintf(F_RECORD, "%s\\Multi_year_summary.%s", PassC1, CSV);
#else
		sprintf(F_RECORD, "%s\\RECORD\\Site\\Multi_year_summary.%s", OUTPUT, CSV);	
#endif
	}
	else
	{
#ifdef DEGUI
		sprintf(F_RECORD, "%s\\Multi_year_summary.%s", Pass, CSV);
#else
		
#ifdef MANURE
		sprintf(F_RECORD, "%s\\Multi_year_summary.%s", PassC1, CSV);
#else		
		sprintf(F_RECORD, "%s\\Multi_year_summary.%s", Pass, CSV);
#endif			

#endif
		
	}	

	float TotalCutC = 0.0;
	for(int i=1;i<=CropNumbers;i++) 
	{
		TotalCutC += (yr_CutGrain[i]+yr_CutLeaf[i]+yr_CutStem[i]+yr_CutRoot[i]);
	}
	
    if (year == 1)
    {
		fp = fopen(F_RECORD, "w");
		if (fp==NULL) note(0, F_RECORD);
		
		fprintf(fp, "Multi-year report for site %s\n", site);
		fprintf(fp, "\n"); 
		
		/*
		fprintf(fp, "%-5s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s\n",	
			"Year","Crop1","GrainC1","LeafC1","StemC1","RootC1","Crop2","GrainC2","LeafC2","StemC2","RootC2","Crop3","GrainC3","LeafC3","StemC3","RootC3","SOC 0-10cm","SOC 10-20cm","SOC 20-30cm","SOC 30-40cm","SOC 40-50cm","SOC 0-10cm","SOC 10-20cm","SOC 20-30cm","SOC 30-40cm","SOC 40-50cm",
			"IniSOC","End_SOC","dSOC","ShootLitterC_input","RootLitterC_input","ManureC_input","RootExudation_DOC",
			"Soil-CO2","Leach_C","Runoff_C","CH4","IniSON","IniSIN","EndSON","EndSIN",
			"dSN","Atmo_N_input","Fertilizer_N_input","Manure_N_input","Litter_N_input","N_fixation",
			"Crop_N_uptake","Leach_NO3","Runoff_SON","Leach_DON","N2O_flux","NO_flux","N2_flux","NH3_flux","exchengeable-NH4",
			"PET","Transpiration","Evaporation","WaterLeach","Runoff","Irrigation",
			"Precipitation", "DeepWater","MeanT","WindSpeed","ColdStress","PotTrans/WreqTrans","N_Stress","Cut_CropC",
			"yr_end_grain", "yr_end_leaf", "yr_end_stem", "yr_end_root", "yr_end_stub","WaterStress-Crop1","WaterStress-Crop2","WaterStress-Crop3","NStress-Crop1","NStress-Crop2","NStress-Crop3","ColdStress-Crop1","ColdStress-Crop2","ColdStress-Crop3","CropHarvestDay","CropGrowDay", "EOYPlantPopSurv_Crp1","EOYPlantPopSurv_Crp2","EOYPlantPopSurv_Crp3","EOYPlantPopSurv_Crp4","CutNumber","CrownBelowMax(WINTER)","CrownBelowMax(SPRING)","GermDays","StuntGrowth","GDD",
			"MatDay1", "MatDay2", "MatDay3","FlowDay1", "FlowDay2", "FlowDay3","EmerDay1", "EmerDay2", "EmerDay3","PlantDay1","TDD", "PGI","photoPrdStr");
		fprintf(fp, "%-5s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s\n\n",
			"#","ID","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","ID","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","ID","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/kg","kgC/kg","kgC/kg","kgC/kg","kgC/kg","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha/y","kgC/ha/y","kgC/ha/y",
			"kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgN/ha","kgN/ha","kgN/ha",
			"kgN/ha","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y",
			"kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha","mm","mm","mm","mm","mm","mm","mm","degree C","m/s","index","index","index","kgC/ha/y","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","index","index","index","index","index","index","index","index","index","days","days","%","%","oC","oC","#","days","days","index","index","DOY", "DOY", "DOY", "DOY", "DOY", "DOY", "DOY", "DOY", "DOY","DOY","DOY","Base_0C","index","index");
		
		*/



		fprintf(fp, "%-5s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s\n",	
			"Year","Crop1","GrainC1","LeafC1","StemC1","RootC1","Crop2","GrainC2","LeafC2","StemC2","RootC2","Crop3","GrainC3","LeafC3","StemC3","RootC3", "Crop4", "GrainC4", "LeafC4", "StemC4", "RootC4","SOC 0-10cm","SOC 10-20cm","SOC 20-30cm","SOC 30-40cm","SOC 40-50cm","SOC 0-10cm","SOC 10-20cm","SOC 20-30cm","SOC 30-40cm","SOC 40-50cm",
			"IniSOC","End_SOC","dSOC","ShootLitterC_input","RootLitterC_input","ManureC_input","RootExudation_DOC",
			"Soil-CO2","Leach_C","Runoff_C","CH4","IniSON","IniSIN","EndSON","EndSIN",
			"dSN","Atmo_N_input","Fertilizer_N_input","Manure_N_input","Litter_N_input","N_fixation",
			"Crop_N_uptake","Leach_NO3","Runoff_SON","Leach_DON","N2O_flux","NO_flux","N2_flux","NH3_flux","exchengeable-NH4",
			"PET","Transpiration","Evaporation","WaterLeach","Runoff","Irrigation",
			"Precipitation", "DeepWater","MeanT","WindSpeed","ColdStress","PotTrans/WreqTrans","N_Stress","Cut_CropC",
			"yr_end_grain", "yr_end_leaf", "yr_end_stem", "yr_end_root", "yr_end_stub","WaterStress-Crop1","WaterStress-Crop2","WaterStress-Crop3", "WaterStress-Crop4","NStress-Crop1","NStress-Crop2","NStress-Crop3","NStress-Crop4","TempStress-Crop1","TempStress-Crop2","TempStress-Crop3","TempStress-Crop4","CropHarvestDay","CropGrowDay", "EOYPlantPopSurv_Crp1","EOYPlantPopSurv_Crp2","EOYPlantPopSurv_Crp3","EOYPlantPopSurv_Crp4","CutNumber","CrownBelowMax(WINTER)","CrownBelowMax(SPRING)","GermDays","StuntGrowth","GDD",
			"MatDay1", "MatDay2", "MatDay3","FlowDay1", "FlowDay2", "FlowDay3","EmerDay1", "EmerDay2", "EmerDay3","PlantDay1","TDD", "PGI","photoPrdStr","LastFrost","HeatDDays_Crop1", "HeatDDays_Crop2", "HeatDDays_Crop3", "HeatDDays_Crop4");
		fprintf(fp, "%-5s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s,%-11s\n\n",
			"#","ID","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","ID","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","ID","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y", "ID", "kgC/ha/y", "kgC/ha/y", "kgC/ha/y", "kgC/ha/y","kgC/kg","kgC/kg","kgC/kg","kgC/kg","kgC/kg","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha/y","kgC/ha/y","kgC/ha/y",
			"kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgC/ha/y","kgN/ha","kgN/ha","kgN/ha",
			"kgN/ha","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha/y",
			"kgN/ha/y","kgN/ha/y","kgN/ha/y","kgN/ha","mm","mm","mm","mm","mm","mm","mm","degree C","m/s","index","index","index","kgC/ha/y","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","index","index","index", "index", "index", "index","index","index","index","index","index","index","days","days","%","%","oC","oC","#","days","days","index","index","DOY", "DOY", "DOY", "DOY", "DOY", "DOY", "DOY", "DOY", "DOY","DOY","DOY","Base_0C","index","index","DOY","oC", "oC", "oC", "oC");
    }
    else
    {
		fp = fopen(F_RECORD, "a");
		if (fp==NULL) note(1, F_RECORD); 
    }
    for(int zz=1; zz<=3; zz++)
	{
	if(crop_N_stress_days[zz]<=0)
	crop_N_stress_days[zz]=1.0;
	if(crop_water_stress_days[zz]<=0)
    crop_water_stress_days[zz]=1.0;
	if(crop_PPT_days[zz]<=0)	
	crop_PPT_days[zz]=1.0;

	}
	float actualWStress;
	actualWStress = crop_PPT[1] / (float)crop_PPT_days[1];
	actualWStress = max(1.0, min(0.0, actualWStress));
	//fprintf(fp, "%5d,%11d, %16.7f,%16.7f,%16.7f,%16.7f,%11d,%11.2f,%11.2f,%11.2f,%11.2f,%11d,%11.2f,%11.2f,%11.2f,%11.2f,%15.4f,%15.4f,%15.4f,%15.4f,%15.4f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%15.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%11.2f,%5d,%5d,%11.2f,%11.2f,%11.2f,%11.2f,%11d,%11d,%11d,%11d,%11.2f\n",
	fprintf(fp, "%5d,%11d, %16.7f,%16.7f,%16.7f,%16.7f,%11d,%16.7f,%16.7f,%16.7f,%16.7f,%11d,%16.7f,%16.7f,%16.7f,%16.7f,%11d,%16.7f,%16.7f,%16.7f,%16.7f,%15.4f,%15.4f,%15.4f,%15.4f,%15.4f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%16.7f,%5d,%5d,%16.7f,%16.7f,%16.7f,%16.7f,%11d,%11d,%11d,%11d,%16.7f,%16.7f,%11d,%11d,%11d,%11d,%11d,%11d,%11d,%11d,%11d,%11d,%16.7f,%16.7f,%16.7f,%11d,%16.7f,%16.7f,%16.7f,%16.7f\n",
		year,
		crop[1],
		YrG_grain[1],//+yr_CutGrain[1]+yr_GrazeGrain[1],
		YrG_leaf[1],
		YrG_stem[1],//+yr_CutLeaf[1]+yr_CutStem[1]+yr_GrazeShoot[1],
		YrG_root[1],//+yr_CutRoot[1]+yr_GrazeRoot[1],
		crop[2],
		YrG_grain[2],//+yr_CutGrain[2]+yr_GrazeGrain[2],
		YrG_leaf[2],
		YrG_stem[2],//+yr_CutLeaf[2]+yr_CutStem[2]+yr_GrazeShoot[2],
		YrG_root[2],//+yr_CutRoot[2]+yr_GrazeRoot[2],
		crop[3],
		YrG_grain[3],//+yr_CutGrain[3]+yr_GrazeGrain[3],
		YrG_leaf[3],
		YrG_stem[3],//+yr_CutLeaf[3]+yr_CutStem[3]+yr_GrazeShoot[3],
		YrG_root[3],//+yr_CutRoot[3]+yr_GrazeRoot[3],
		crop[4],
		YrG_grain[4],//+yr_CutGrain[3]+yr_GrazeGrain[3],
		YrG_leaf[4],
		YrG_stem[4],//+yr_CutLeaf[3]+yr_CutStem[3]+yr_GrazeShoot[3],
		YrG_root[4],//+yr_CutRoot[3]+yr_GrazeRoot[3],
		topc[1], topc[2], topc[3], topc[4], topc[5], layerc[1], layerc[2], layerc[3], layerc[4], layerc[5],
		IniSOC, EndSOC, EndSOC - IniSOC, yr_addtc, yr_addrc, yr_addmc, yr_InputRoot_DOC,//end_SOC
		yr_soil_co2, yr_leach_hu + yr_leach_DOC, yr_runoff_C, yr_ch4,
		IniSON, IniSIN, EndSON, EndSIN, dSN,
		yr_rainN, yr_addfer, yr_addmn, yr_sln, yr_soilN_from_Nfixation,//yr_addtn+yr_sln+yr_addrn
		yr_uptaken[1] + yr_uptaken[2] + yr_uptaken[3], yr_leach_NO3 + yr_leach_urea, yr_runoff_N, yr_leach_un, yr_dnn2o, yr_dnno, yr_dnn2, yr_soil_nh3, day_clay_N,
		yr_PET * 1000.0, yr_trans * 1000.0, yr_total_ev * 1000.0, yr_leach_water * 1000.0, yr_runoff * 1000.0,
		yr_irri * 1000.0, yr_rain * 1000.0, WaterPool * 1000.0, yr_avet, yr_WindSpeed / 365.0,
		TDD[1] / max_TDD[1], actualWStress, crop_N_stress[1] / (float)crop_N_stress_days[1],
		TotalCutC, yr_end_grain, yr_end_leaf, yr_end_stem, yr_end_root,
		stub1 + stub2 + stub3, crop_water_stress[1] / (float)crop_water_stress_days[1], crop_water_stress[2] / max((float)crop_water_stress_days[2], 1.0), crop_water_stress[3] / max((float)crop_water_stress_days[3], 1.0), crop_water_stress[4] / max((float)crop_water_stress_days[4], 1.0), crop_N_stress[1] / (float)crop_N_stress_days[1], crop_N_stress[2] / max((float)crop_N_stress_days[2], 1.0), crop_N_stress[3] / max((float)crop_N_stress_days[3], 1.0), crop_N_stress[4] / max((float)crop_N_stress_days[4], 1.0), cropTempStressAnnual[1]/ max((float)crop_N_stress_days[1], 1.0), cropTempStressAnnual[2]/max((float)crop_N_stress_days[2], 1.0), cropTempStressAnnual[3]/ max((float)crop_N_stress_days[3], 1.0), cropTempStressAnnual[4]/ max((float)crop_N_stress_days[4], 1.0),//TDD[1] / max_TDD[1], TDD[2] / max(max_TDD[2], 1.0), TDD[3] / max(max_TDD[3], 1.0), TDD[4] / max(max_TDD[4], 1.0),
		cropHarvestDay[1], cropGrowDays[1], pDFCUM[1] * 100, pDFCUM[2] * 100, pDFCUM[3] * 100, pDFCUM[4] * 100, cut_num, winterCrownDays, springCrownDays, germinationDays, stuntGrowth, cropGDD, maturityDay[1], maturityDay[2], maturityDay[3], floweringDay[1], floweringDay[2], floweringDay[3], emergenceDay[1], emergenceDay[2], emergenceDay[3], jdseed[1],max_TDD[1], growthStatus[1],photoPeriodStress[1],lastFrost  , meanTempStressT[1] , meanTempStressT[2] , meanTempStressT[3] , meanTempStressT[4] ); //(yr_pond_ev+yr_soil_ev)*1000.0 //(pDFCUM[1]*100)
	//cropHarvestDay[1], cropGrowDays[1], 100 - (winterKill[1] * 100), pDFCUM[1] * 100, winterCrown / 66, springCrown / 100, cut_num, winterCrownDays, springCrownDays, germinationDays, stuntGrowth, cropGDD, maturityDay[1], maturityDay[2], maturityDay[3], floweringDay[1], floweringDay[2], floweringDay[3], emergenceDay[1], emergenceDay[2], emergenceDay[3], jdseed[1], max_TDD[1], growthStatus[1], photoPeriodStress[1]); //(yr_pond_ev+yr_soil_ev)*1000.0 //(pDFCUM[1]*100)
	 fclose( fp );
    return( 0 );
}

int class_model::write_out_annual_report(int MODE, float ha, int Batch, int livestock, FILE *fout, 
										 FILE *fout2, int CL, float *FarmCropArea, 
										 float *FarmCropManureFraction, int drc, char *Pass, char *PassC1, char *PassL1)
{
    //FILE  *fout;
    char  YR[80], date_time[80];
	
    time_t  t;
    float CNRatio, GrainC, LeafC, StemC, RootC;
    float YrLeachNO3, R_plantn[8];

    time(&t);
    sprintf(date_time, "%s", ctime(&t));

	yr_dSON = EndSON - IniSON;
	yr_dSIN = EndSIN - IniSIN;

	CNRatio = EndSOC / EndSON;

	for(int i=1;i<=4; i++)
	{
		GrainC = YrG_grain[i];// +yr_CutGrain[i]+yr_GrazeGrain[i];
		LeafC = YrG_leaf[i];
		StemC = YrG_stem[i];// + yr_CutLeaf[i]+yr_CutStem[i]+yr_GrazeShoot[i];
		RootC = YrG_root[i];// +yr_CutRoot[i]+yr_GrazeRoot[i];
	}
	
	YrLeachNO3 = yr_leach_NO3+yr_leach_urea;
	if (YrLeachNO3 < 0.0) YrLeachNO3 = 0.0;

	char BatchFileName[400];

	float G_days[8];
	for(int mb=1; mb<=7; mb++)
	{
		if(crop_days[mb]==0) crop_days[mb]=1;
	
		G_days[mb]=crop_days[mb];

		R_plantn[mb]=yr_plantn[mb];
	}

	//fout = fopen( YR, "w" );
	//if (fout==NULL) note(1, YR);

	//YIELD2(yr_uptaken[1]+yr_fixn[1],yr_uptaken[2]+yr_fixn[2],yr_uptaken[3]+yr_fixn[3]);			
	//YIELD3(plantn[1],plantn[2],plantn[3]);	
	
	//if(yr_pond_ev>0.0) yr_irri = (yr_pond_ev+yr_trans+yr_soil_ev+yr_runoff+yr_leach_water) - yr_rain/100.0;
	//if(yr_irri<0.0) yr_irri = 0.0;
	yr_plant_demand = (yr_pond_ev+yr_trans+yr_soil_ev)*1000.0;
	yr_TotalEvap = (yr_pond_ev + yr_soil_ev)*1000.0;
	yr_PrecWater = yr_rain*10.0;
	yr_dSoilWater = (yr_rain+yr_irri) - (yr_trans+yr_soil_ev+yr_runoff+yr_leach_water); //m


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//if(livestock==0)
{
	int i;
	float _ha=FarmCropArea[CL];
	float FIC = (yr_Lagoon_to_field_C_T+yr_Compost_to_field_C_T+yr_Digester_to_field_C_T+yr_House_to_field_C_T)*FarmCropManureFraction[CL] + (yr_addtc+yr_addrc)*_ha
		+ yr_InputRoot_DOC*_ha + (yr_graze_urine_C+yr_graze_dung_C)*_ha;
	float FOC = (yr_soil_co2+yr_ch4)*_ha + yr_leach_DOC*_ha + yr_runoff_C*_ha;
	float DFC = FIC - FOC;
	
	float FIN = (yr_Lagoon_to_field_N_T+yr_Compost_to_field_N_T+yr_Digester_to_field_N_T+yr_House_to_field_N_T)*FarmCropManureFraction[CL] + 
		(yr_rainN+yr_sln+yr_addfer+yr_irri_N+yr_graze_urine_N+yr_graze_dung_N+yr_soilN_from_Nfixation)*_ha;
	float FON = (yr_soil_nh3+yr_dnn2o+yr_dnno+yr_dnn2+yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3]+YrLeachNO3+yr_runoff_N)*_ha;
	float DFN = FIN - FON;
	
	float FIP = (yr_Lagoon_to_field_P_T+yr_Compost_to_field_P_T+yr_Digester_to_field_P_T+yr_House_to_field_P_T)*FarmCropManureFraction[CL] + yr_addrp*_ha + yr_inFertP*_ha + yr_graze_dung_P*_ha;
	float FOP = (plantP[1]+plantP[2]+plantP[3]+yr_runoff_P+yr_leach_P)*_ha;	
	float DFP = FIP - FOP;

	float FIWW = (yr_Lagoon_to_field_H2O_T+yr_Compost_to_field_H2O_T+yr_Digester_to_field_H2O_T+yr_House_to_field_H2O_T)*FarmCropManureFraction[CL] + 
		(yr_rain + yr_irri)*10000.0*_ha*1000.0;
	float FOWW = (yr_leach_water + yr_runoff + yr_trans + yr_soil_ev+yr_pond_ev) *10000.0*_ha*1000.0;	
	float DFWW = FIWW - FOWW;
	
	float DFW = yr_dSoilWater*10000.0*_ha*1000.0;
	float TCN = (yr_uptaken[1]+crop_NH3_absorp[1]+yr_fixn[1]+yr_uptaken[2]+crop_NH3_absorp[2]+yr_fixn[2]) * _ha;
	float CNF = (crop_NH3_absorp[1]+yr_fixn[1]+crop_NH3_absorp[2]+yr_fixn[2])*_ha;
	float GNC = (YrG_grain[1]/graincn[1]+YrG_grain[2]/(graincn[2]+0.000001))*_ha;
	float SNC = (YrG_leaf[1]/leafcn[1]+YrG_stem[1]/stemcn[1]+YrG_leaf[2]/(leafcn[2]+0.000001)+YrG_stem[2]/(stemcn[2]+0.000001))*_ha;
	float RNC = (YrG_root[1]/rootcn[1]+YrG_root[2]/rootcn[2])*_ha;//TCN-GNC-SNC;
	float BIO = (YrG_grain[1]+YrG_leaf[1]+YrG_stem[1]+YrG_root[1]+YrG_grain[2]+YrG_leaf[2]+YrG_stem[2]+YrG_root[2])*_ha;
	float PPP = (plantP[1]+plantP[2]+plantP[3])*_ha;

#ifdef MANURE

// could be %e
if(m_unit==0)
{
	CString FFD;
	FFD.Format("FIELD_%d_%s_%.2fha", CL, crop_name[1], FarmCropArea[CL]);
	fprintf(fout2, "%-28s %12s    %15s     %15s    %15s\n\n", FFD, "C_kg", "N_kg", "Water_kg", "P_kg");
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_lagoon", yr_Lagoon_to_field_C_T*FarmCropManureFraction[CL], yr_Lagoon_to_field_N_T*FarmCropManureFraction[CL], yr_Lagoon_to_field_H2O_T*FarmCropManureFraction[CL], yr_Lagoon_to_field_P_T*FarmCropManureFraction[CL]);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_compost", yr_Compost_to_field_C_T*FarmCropManureFraction[CL], yr_Compost_to_field_N_T*FarmCropManureFraction[CL], yr_Compost_to_field_H2O_T*FarmCropManureFraction[CL], yr_Compost_to_field_P_T*FarmCropManureFraction[CL]);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_digester", yr_Digester_to_field_C_T*FarmCropManureFraction[CL], yr_Digester_to_field_N_T*FarmCropManureFraction[CL], yr_Digester_to_field_H2O_T*FarmCropManureFraction[CL], yr_Digester_to_field_P_T*FarmCropManureFraction[CL]);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_barn", yr_House_to_field_C_T*FarmCropManureFraction[CL], yr_House_to_field_N_T*FarmCropManureFraction[CL], yr_House_to_field_H2O_T*FarmCropManureFraction[CL], yr_House_to_field_P_T*FarmCropManureFraction[CL]);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_precipitation", 0.0, yr_rainN*_ha, yr_rain*10000.0*_ha*1000.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_crop_residue", (yr_addtc+yr_addrc)*_ha, (yr_sln)*_ha, 0.0, yr_addrp*_ha);//yr_addtn + +yr_addrn
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_root_exudation", yr_InputRoot_DOC*_ha, 0.0, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_fertilizer", 0.0, yr_addfer*_ha, 0.0, yr_inFertP*_ha);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_irrigation", 0.0, yr_irri_N*_ha, yr_irri*10000.0*_ha*1000.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx_from_grazing_herd", (yr_graze_urine_C+yr_graze_dung_C)*_ha, (yr_graze_urine_N+yr_graze_dung_N)*_ha, 0.0, yr_graze_dung_P*_ha);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Influx_from_N_fixation", 0.0, yr_soilN_from_Nfixation*_ha, 0.0, 0.0);

    fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_CO2_emission", (yr_soil_co2)*_ha, 0.0,0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_CH4_emission", yr_ch4*_ha, 0.0,0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_NH3_emission", 0.0, yr_soil_nh3*_ha, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_N2O_emission", 0.0, yr_dnn2o*_ha, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_NO_emission", 0.0, yr_dnno*_ha, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_N2_emission", 0.0, yr_dnn2*_ha, 0.0, 0.0);	
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_leaching_loss", yr_leach_DOC*_ha, YrLeachNO3*_ha, yr_leach_water*10000.0*_ha*1000.0, yr_leach_P*_ha);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_runoff_loss", yr_runoff_C*_ha, yr_runoff_N*_ha, yr_runoff*10000.0*_ha*1000.0, yr_runoff_P*_ha);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_loss_to_crop", 0.0, (yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3])*_ha, yr_trans*10000.0*_ha*1000.0, PPP);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Soil_evaporation", 0.0, 0.0, (yr_soil_ev+yr_pond_ev)*10000.0*_ha*1000.0, 0.0);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_initial_pool", IniSOC*_ha, IniSON*_ha, (IniProfWater+IniWaterPool)*10000.0*_ha*1000.0, IniSP*_ha);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil_end_pool", EndSOC*_ha, EndSON*_ha, (EndProfWater+EndWaterPool)*10000.0*_ha*1000.0, EndSP*_ha);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Soil_sequestration", DFC, DFN, DFWW, DFP);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop_N_fixation", 0.0, (yr_fixn[1]+yr_fixn[2]+yr_fixn[3]+yr_NH3_deposit)*_ha, 0.0, 0.0);	
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop_biomass", BIO, TCN, 0.0, PPP); 
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop_grain", (YrG_grain[1]+YrG_grain[2])*_ha, GNC, 0.0, PPP*0.6);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop_shoot", (YrG_leaf[1]+YrG_stem[1]+YrG_leaf[2]+YrG_stem[2])*_ha, SNC, 0.0, PPP*0.3);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop_root", (YrG_root[1]+YrG_root[2])*_ha, RNC, 0.0, PPP*0.1);
	fprintf(fout2, "---------------------------------------------------------------------------------------------------\n");
}
else
{
	float w1=1.0/ac_ha, w2=1.0/lb_kg;

	CString FFD;
	FFD.Format("FIELD %d: %s (%.0f ac)", CL, crop_name[1], FarmCropArea[CL]*w1);
	fprintf(fout2, "%-25s %11s     %11s     %11s     %11s\n\n", FFD, "C_lb", "N_lb", "Water_lb", "P_lb");
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx from lagoon", yr_Lagoon_to_field_C_T*FarmCropManureFraction[CL]*w2, yr_Lagoon_to_field_N_T*FarmCropManureFraction[CL]*w2, yr_Lagoon_to_field_H2O_T*FarmCropManureFraction[CL]*w2, yr_Lagoon_to_field_P_T*FarmCropManureFraction[CL]*w2);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx from compost", yr_Compost_to_field_C_T*FarmCropManureFraction[CL]*w2, yr_Compost_to_field_N_T*FarmCropManureFraction[CL]*w2, yr_Compost_to_field_H2O_T*FarmCropManureFraction[CL]*w2, yr_Compost_to_field_P_T*FarmCropManureFraction[CL]*w2);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Influx from digester", yr_Digester_to_field_C_T*FarmCropManureFraction[CL]*w2, yr_Digester_to_field_N_T*FarmCropManureFraction[CL]*w2, yr_Digester_to_field_H2O_T*FarmCropManureFraction[CL]*w2, yr_Digester_to_field_P_T*FarmCropManureFraction[CL]*w2);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx from precipitation", 0.0, yr_rainN*_ha*w2, yr_rain*10000.0*_ha*1000.0*w2, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx from crop litter", (yr_addtc+yr_addrc)*_ha*w2, (yr_sln)*_ha*w2, 0.0, yr_addrp);//yr_addtn + +yr_addrn
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx from fertilizer", 0.0, yr_addfer*_ha*w2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Influx from irrigation", 0.0, yr_irri_N*_ha*w2, yr_irri*10000.0*_ha*1000.0*w2, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Influx from N fixation", 0.0, yr_soilN_from_Nfixation*_ha*w2, 0.0, 0.0);

    fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil CO2 emission", (yr_soil_co2)*_ha*w2, 0.0,0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil CH4 emission", yr_ch4*_ha*w2, 0.0,0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil NH3 emission", 0.0, yr_soil_nh3*_ha*w2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil N2O emission", 0.0, yr_dnn2o*_ha*w2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil NO emission", 0.0, yr_dnno*_ha*w2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil N2 emission", 0.0, yr_dnn2*_ha*w2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Uptake by crop", 0.0, (yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3])*_ha*w2, yr_trans*10000.0*_ha*1000.0*w2, plantP[1]*_ha*w2);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil N loss by leaching", 0.0, YrLeachNO3*_ha*w2, (yr_leach_water)*10000.0*_ha*1000.0*w2, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Soil runoff loss", yr_runoff_SOC*_ha*w2, yr_runoff_ION*_ha*w2, yr_runoff*10000.0*_ha*1000.0*w2, yr_runoff_P*_ha*w2);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Soil water evaporation", 0.0, 0.0, (yr_soil_ev+yr_pond_ev)*10000.0*_ha*1000.0*w2, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n\n", "Soil sequestration", DFC*w2, DFN*w2, DFW*w2, 0.0);

	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop N", 0.0, TCN*w2, 0.0, 0.0); 
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop grain", YrG_grain[1]*_ha*w2, GNC*w2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop shoot", (YrG_leaf[1]+YrG_stem[1])*_ha*w2, SNC*w2, 0.0, 0.0);
	fprintf(fout2, "%-25s %15.0f    %15.0f     %15.0f    %15.0f\n", "Crop root", YrG_root[1]*_ha*w2, RNC*w2, 0.0, 0.0);
	fprintf(fout2, "---------------------------------------------------------------------------------------------------\n");
}
#endif
	///////////////////////////////////////////////////////////////////////////////////////////////////////

if(m_unit==0)//Metric system
{
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  ANNUAL REPORT: ");
	fprintf(fout, "  Site %s     Year %d     %s\n",	site, year, date_time );
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  SOIL SECTION: Unit kg C or N/ha \n");	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	
	fprintf(fout, "  SOM pools  -----Litter-----  -----Humads-----  -----Humus------  -----Total-----\n");
	fprintf(fout, "               C        N        C        N        C        N        C        N   \n");
	fprintf(fout, "  Day 1    %7.2f  %7.2f  %7.2f  %7.2f %7.2f  %7.2f  %7.2f  %7.2f\n",
		IniLitter, IniLitterN, IniActHumus, IniActHumusN, whumus1, whumusn1, IniSOC, IniSON);
	fprintf(fout, "  Day 365  %7.2f  %7.2f  %7.2f  %7.2f %7.2f  %7.2f  %7.2f  %7.2f\n",
		EndLitter, EndLitterN, EndActHumus, EndActHumusN, whumus2, whumusn2, EndSOC, EndSON);
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Inorganic N pools in kg N/ha\n\n");
	fprintf(fout, "                   NO3-     NH4+    NH3(w)   Urea     NO(w)    clay-NH4   N2O+N2   Total\n");
	fprintf(fout, "  Day 1         %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f\n",
						wno31, wnh41, wnh31, wurea1, wno1, day_clay_n1, ini_N_gases, IniSIN); 
	fprintf(fout, "  Day 365       %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f\n",
						wno32, wnh42, wnh32, wurea2, wno2, day_clay_n2, end_N_gases, EndSIN);//	
	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Fluxes                         C (kg C/ha/yr)              N (kg N/ha/yr)\n\n");
	fprintf(fout, "  Inputs -------------------------------------------------------------------------------\n");
	fprintf(fout, "  Manure                            %7.2f			%9.2f\n", yr_addmc, yr_addmn);
	fprintf(fout, "  Shoot litter                      %7.2f			%9.2f\n", yr_addtc, yr_sln-yr_addrn);//yr_addtn + 
	fprintf(fout, "  Root litter			    %7.2f                     %9.2f\n", yr_addrc, yr_addrn);
	fprintf(fout, "  Root exudation		    %7.2f							\n", yr_InputRoot_DOC);	
	fprintf(fout, "  Rain-N deposit                                  ");
	fprintf(fout, "               %8.2f\n", yr_rainN);
	fprintf(fout, "  Irrigation N input                              ");
	fprintf(fout, "               %8.2f\n", yr_irri_N);
	fprintf(fout, "  Fertilizer-N                                    ");
	fprintf(fout, "               %8.2f\n", yr_addfer);
	fprintf(fout, "  Soil N fixation                                 ");
	fprintf(fout, "               %8.2f\n\n", yr_soilN_from_Nfixation);
	
	fprintf(fout, "  Outputs ------------------------------------------------------------------------------\n");
	fprintf(fout, "  Soil-CO2 emission                 %7.2f\n", yr_soil_co2);//+yr_rootDOC_co2
	fprintf(fout, "  CH4 emission                      %7.2f\n", yr_ch4);
	fprintf(fout, "  Soil runoff                       %7.2f                      %8.2f\n", yr_runoff_C, yr_runoff_N);
	fprintf(fout, "  Soil leaching                     %7.2f                      %8.2f\n", yr_leach_DOC, YrLeachNO3);
	fprintf(fout, "  Crop N uptake from soil                                        %8.2f\n", yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3]);
	fprintf(fout, "  NH3 volatilization                                             %8.2f\n", yr_soil_nh3);
	fprintf(fout, "  N2O                                                            %8.2f\n", yr_dnn2o);
	fprintf(fout, "  NO                                                             %8.2f\n", yr_dnno);
	fprintf(fout, "  N2                                                             %8.2f\n", yr_dnn2);
	fprintf(fout, "  Indirect N2O                                                   %8.2f\n", yr_indirect_n2o);
	fprintf(fout, "  Indirect N2                                                    %8.2f\n", yr_indirect_n2);
		
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Mineralization: %6.1f kg C/ha and %6.1f kg N/ha; ", yr_C_mine, yr_minern);
	fprintf(fout, "  Soil C/N ratio: %4.1f\n", CNRatio);
	fprintf(fout, "  --------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Depth (cm)         kg C/kg           kg C/ha		Soil_weight_kg/ha\n");
	fprintf(fout, "    0 - 10         %8.4f             %8.2f		%6.0f\n", topc[1], layerc[1], LayerSoilWeight[1]);
	fprintf(fout, "   10 - 20         %8.4f             %8.2f		%6.0f\n", topc[2], layerc[2], LayerSoilWeight[2]);
	fprintf(fout, "   20 - 30         %8.4f             %8.2f		%6.0f\n", topc[3], layerc[3], LayerSoilWeight[3]);
	fprintf(fout, "   30 - 40         %8.4f             %8.2f		%6.0f\n", topc[4], layerc[4], LayerSoilWeight[4]);
	fprintf(fout, "   40 - 50         %8.4f             %8.2f		%6.0f\n", topc[5], layerc[5], LayerSoilWeight[5]);
  
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  CROP SECTION %d: Unit kg C or N/ha \n", CL);	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");

	fprintf(fout, "  Cropping season	");
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12d ", i);
	fprintf(fout, "\n");

    fprintf(fout, "  Crop name			");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%-12s ", crop_name[i]);
	}
	fprintf(fout, "\n");			
		
	fprintf(fout, "  Planting date		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12d ", jdseed[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Growing days		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12d ", grow_days[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Growing season TDD	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.0f ", TDD[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Water demand (mm)	");	
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_PT[i]*1000.0);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Water uptake (mm)	");	
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_trans[i]*1000.0);
	}
	fprintf(fout, "\n");
	
    fprintf(fout, "  Water stress		");	
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_water_stress[i]/G_days[i]);
	}
	fprintf(fout, "\n");
							
	fprintf(fout, "  Crop N demand		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", maxmn[i]);// yr_need_N[i], demandn[i]
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop N from soil	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", yr_uptaken[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop N from air NH3	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_NH3_absorp[i]);
	}
	fprintf(fout, "\n");

	//fprintf(fout, "  NH3 deposition                                  ");
	//fprintf(fout, "               %8.2f\n\n", yr_NH3_deposit);
	
	fprintf(fout, "  Crop N fixation	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", yr_fixn[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Nitrogen stress	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_N_stress[i]/G_days[i]);
	}
	fprintf(fout, "\n\n");
	
	fprintf(fout, "  Annual crop biomass production:\n");
	fprintf(fout, "  Crop N (kg N/ha)	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", yr_plantn[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop C (kg C/ha)	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", Yr_PlantBiomass[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  -- Grain C		");
	{
	for(int i=1;i<=CropNumbers;i++) 
		fprintf(fout, "%12.2f ", YrG_grain[i]);
	}
	fprintf(fout, "\n");
												
	fprintf(fout, "  -- Leaf C		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", YrG_leaf[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  -- stem C		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", YrG_stem[i]);
	}
	fprintf(fout, "\n");
						
	fprintf(fout, "  -- Root C		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", YrG_root[i]);
	}
	fprintf(fout, "\n\n");
	
	fprintf(fout, "  Photosynthesis (kg C/ha)       %7.1f\n", -yr_Psn);
	fprintf(fout, "  Shoot respiration              %7.1f\n", yr_shoot_CO2);
	fprintf(fout, "  Root respiration               %7.1f\n", yr_root_co2);	
	fprintf(fout, "  Crop NPP                       %7.1f\n", yr_CropGPP);
	fprintf(fout, "  NEE                            %7.1f\n", yr_NEE);
	fprintf(fout, "  Stubble (kg C/ha)		%8.1f\n", stub1+stub2+stub3);

	fprintf(fout, "  Fruit cut (kg C/ha)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutGrain[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Leaf cut (kg C/ha)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutLeaf[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Stem cut (kg C/ha)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutStem[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Root cut (kg C/ha)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutRoot[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Livestock feed demand (kg C/ha) %8.0f\n", yr_GrazeDemandC);
	fprintf(fout, "  Grazed biomass (kg C/ha)	  %8.0f\n", yr_GrazeGrain[1]+yr_GrazeShoot[1]+yr_GrazeStub);
	
	fprintf(fout, "  --------------------------------------------------------------------------------------\n");
	fprintf(fout, "  WATER SECTION: Unit mm water/year\n");	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");

	yr_plant_demand = (yr_pond_ev+yr_trans+yr_soil_ev)*1000.0;
	yr_TotalEvap = (yr_pond_ev + yr_soil_ev)*1000.0;
	yr_PrecWater = yr_rain*10.0;

	yr_dSoilWater = (yr_rain+yr_irri) - (yr_trans+yr_soil_ev+yr_runoff+yr_leach_water); //m
	
	fprintf(fout, "  Precipitation			%.2f\n", yr_rain*1000.0); 
	fprintf(fout, "  Irrigation			%.2f\n", yr_irri*1000.0);
	fprintf(fout, "  Manure water			%.2f\n", yr_manure_water*1000.0);	
	fprintf(fout, "  PET				%.2f\n", yr_PET*1000.0);
	fprintf(fout, "  Transpiration			%.2f\n", yr_trans*1000.0);
	fprintf(fout, "  Soil evaporation		%.2f\n", (yr_soil_ev+yr_pond_ev)*1000.0);
	fprintf(fout, "  Run off			%.2f\n", yr_runoff*1000.0);
	fprintf(fout, "  Leaching			%.2f\n", yr_leach_water*1000.0);
	//fprintf(fout, "  Change in soil water		%.2f\n", yr_dSoilWater*1000.0);
	fprintf(fout, "  Soil profile water:	Initial %.2f;	End: %.2f\n", IniProfWater*1000.0, day_SoilWater*1000.0);
	fprintf(fout, "  Deep water pool   :	Initial %.2f;	End: %.2f\n", IniWaterPool*1000.0, WaterPool*1000.0);
	fprintf(fout, "  Mean wind speed (m/s) 	%.2f\n", yr_WindSpeed/365.0);

	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Soil P (kg P/ha): Day 1-- %.2f; Day 365-- %.2f\n", IniSP, EndSP); 
	fprintf(fout, "  Fertilizer P (kg P/ha): %.2f\n", yr_inFertP); 
	fprintf(fout, "  Manure P (kg P/ha): %.2f\n", yr_addmP);
	fprintf(fout, "  P flux of crop uptake (kg P/ha): %.2f\n", plantP[1]+plantP[2]+plantP[3]);
	fprintf(fout, "  P flux of runoff (kg P/ha): %.2f\n", yr_runoff_P); 
	fprintf(fout, "  P flux of leaching (kg P/ha): %.2f\n", yr_leach_P); 
	fprintf(fout, "  P flux of residue incorporation (kg P/ha): %.2f\n", yr_addrp);
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");


	if(UseION==1) 
	{
		fprintf(fout, "  Soil inorganic N adjustment due to artificially altering ION profile\n"); 
		fprintf(fout, "  Adjusted NO3 (kg N/ha)			%.2f\n", AdjustNO3);
		fprintf(fout, "  Adjusted NH4 (kg N/ha)			%.2f\n", AdjustNH4);
	}
}
else//English system
{
	float w3=1.0/lboac_kgoha;

	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  ANNUAL REPORT: ");
	fprintf(fout, "  Site %s     Year %d     %s\n",	site, year, date_time );
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  SOIL SECTION: Unit lb C or N/ac \n");	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	
	fprintf(fout, "  SOM pools       -----Litter-----  -----Humads-----  -----Humus------  -----Total-----\n");
	fprintf(fout, "                    C        N        C        N        C        N        C        N   \n");
	fprintf(fout, "  Day 1         %7.2f  %7.2f  %7.2f  %7.2f %7.2f  %7.2f  %7.2f  %7.2f\n",
		IniLitter*w3, IniLitterN*w3, IniActHumus*w3, IniActHumusN*w3, whumus1*w3, whumusn1*w3, IniSOC*w3, IniSON*w3);
	fprintf(fout, "  Day 365       %7.2f  %7.2f  %7.2f  %7.2f %7.2f  %7.2f  %7.2f  %7.2f\n",
		EndLitter*w3, EndLitterN*w3, EndActHumus*w3, EndActHumusN*w3, whumus2*w3, whumusn2*w3, EndSOC*w3, EndSON*w3);
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Inorganic N pools in kg N/ha\n\n");
	fprintf(fout, "                   NO3-     NH4+    NH3(w)   Urea     NO(w)    clay-NH4   N-gases   Total\n");
	fprintf(fout, "  Day 1         %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f\n",
						wno31*w3, wnh41*w3, wnh31*w3, wurea1*w3, wno1*w3, day_clay_n1*w3, ini_N_gases*w3, IniSIN*w3); 
	fprintf(fout, "  Day 365       %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f\n",
						wno32*w3, wnh42*w3, wnh32*w3, wurea2*w3, wno2*w3, day_clay_n2*w3, end_N_gases*w3, EndSIN*w3);//	
	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Fluxes                         C (kg C/ha/yr)              N (kg N/ha/yr)\n\n");
	fprintf(fout, "  Inputs -------------------------------------------------------------------------------\n");
	fprintf(fout, "  Manure                           ");
	fprintf(fout, " %7.2f  ", yr_addmc*w3);
	fprintf(fout, "                   %9.2f\n", yr_addmn*w3);
	fprintf(fout, "  Shoot litter                      %7.2f			%9.2f\n", yr_addtc*w3, yr_sln-yr_addrn*w3);//yr_addtn + 
	fprintf(fout, "  Root litter			    %7.2f                     %9.2f\n", yr_addrc*w3, yr_addrn*w3);
	fprintf(fout, "  Rain-N deposit                                  ");
	fprintf(fout, "               %8.2f\n", yr_rainN*w3);
	fprintf(fout, "  Irrigation N input                              ");
	fprintf(fout, "               %8.2f\n", yr_irri_N*w3);
	fprintf(fout, "  Fertilizer-N                                    ");
	fprintf(fout, "               %8.2f\n", yr_addfer*w3);
	fprintf(fout, "  Soil N fixation                                 ");
	fprintf(fout, "               %8.2f\n", yr_soilN_from_Nfixation*w3);
	fprintf(fout, "  NH3 deposition                                  ");
	fprintf(fout, "               %8.2f\n\n", yr_NH3_deposit*w3);
	fprintf(fout, "  Outputs ------------------------------------------------------------------------------\n");
	fprintf(fout, "  Soil-CO2 emission                ");	
	fprintf(fout, " %7.2f\n", yr_soil_co2*w3);//+yr_rootDOC_co2
	fprintf(fout, "  CH4 emission                      %7.2f\n", yr_ch4*w3);
	fprintf(fout, "  DOC leached                      ");
	fprintf(fout, " %7.2f          ", yr_leach_hu*w3);//+yr_FrostBio);
	fprintf(fout, "             %7.2f\n", yr_leach_un*w3);
	fprintf(fout, "  Crop N uptake from soil                         ");
	fprintf(fout, "               %8.2f\n", yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3]*w3);
	fprintf(fout, "  ION runoff                                      ");
	fprintf(fout, "               %8.2f\n", yr_runoff_N*w3);
	fprintf(fout, "  ION leaching                                    ");
	fprintf(fout, "               %8.2f\n", YrLeachNO3*w3);
	fprintf(fout, "  NH3 volatilization                              ");
	fprintf(fout, "               %8.2f\n", yr_soil_nh3*w3);
	fprintf(fout, "  N2O                                             ");
	fprintf(fout, "               %8.2f\n", yr_dnn2o*w3);
	fprintf(fout, "  NO                                              ");
	fprintf(fout, "               %8.2f\n", yr_dnno*w3);
	fprintf(fout, "  N2                                              ");
	fprintf(fout, "               %8.2f\n", yr_dnn2*w3);
	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Mineralization: %6.1f lb C/ac and %6.1f lb N/ac; ", yr_C_mine, yr_minern);
	fprintf(fout, "  Soil C/N ratio: %4.1f\n", CNRatio);
	fprintf(fout, "  --------------------------------------------------------------------------------------\n");
	fprintf(fout, "  Depth (cm)         lb C/ac           lb C/ac	\n");
	fprintf(fout, "    0 - 10         %8.4f             %6.2f\n", topc[1]*w3, layerc[1]*w3);
	fprintf(fout, "   10 - 20         %8.4f             %6.2f\n", topc[2]*w3, layerc[2]*w3);
	fprintf(fout, "   20 - 30         %8.4f             %6.2f\n", topc[3]*w3, layerc[3]*w3);
	fprintf(fout, "   30 - 40         %8.4f             %6.2f\n", topc[4]*w3, layerc[4]*w3);
	fprintf(fout, "   40 - 50         %8.4f             %6.2f\n", topc[5]*w3, layerc[5]*w3);
  
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");
	fprintf(fout, "  CROP SECTION %d: Unit lb C or N/ac \n", CL);	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");

	fprintf(fout, "  Cropping season	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12d ", i);
	}
	fprintf(fout, "\n");

    fprintf(fout, "  Crop name			");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%-12s ", crop_name[i]);
	}
	fprintf(fout, "\n");			
		
	fprintf(fout, "  Planting date		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12d ", jdseed[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Growing days		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12d ", grow_days[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Growing season TDD	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.0f ", TDD[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Water demand (mm)	");	
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_PT[i]*1000.0);
	}
	fprintf(fout, "\n");

    fprintf(fout, "  Water stress		");	
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_water_stress[i]/G_days[i]);
	}
	fprintf(fout, "\n");
							
	fprintf(fout, "  Crop N demand		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", maxmn[i]*w3);// yr_need_N[i], demandn[i]
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop N from soil	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", yr_uptaken[i]*w3);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop N from air NH3	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_NH3_absorp[i]*w3);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop N fixation	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", yr_fixn[i]*w3);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Nitrogen stress	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", crop_N_stress[i]/G_days[i]);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop biomass:\n");
	fprintf(fout, "  Crop N (kg N/ha)	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", yr_plantn[i]*w3);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Crop C (kg C/ha)	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", Yr_PlantBiomass[i]*w3);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  -- Grain C		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", YrG_grain[i]*w3);
	}
	fprintf(fout, "\n");
												
	fprintf(fout, "  -- Leaf C	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", (YrG_leaf[i])*w3);
	}
	fprintf(fout, "\n");	
	
	fprintf(fout, "  -- stem C	");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", (YrG_stem[i])*w3);
	}
	fprintf(fout, "\n");
						
	fprintf(fout, "  -- Root C		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%12.2f ", YrG_root[i]*w3);
	}
	fprintf(fout, "\n\n");
	
	fprintf(fout, "  Photosynthesis (lb C/ac)       %7.2f\n", -yr_Psn*w3);
	fprintf(fout, "  Shoot respiration              %7.2f\n", yr_shoot_CO2*w3);
	fprintf(fout, "  Root respiration               %7.2f\n", yr_root_co2*w3);	
	fprintf(fout, "  Crop NPP                       %7.2f\n", yr_CropGPP*w3);
	fprintf(fout, "  NEE                            %7.2f\n", yr_NEE*w3);
	fprintf(fout, "  Stubble (lb C/ac)		%8.0f\n", (stub1+stub2+stub3)*w3);

	fprintf(fout, "  Fruit cut (lb C/ac)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutGrain[i]*w3);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Leaf cut (lb C/ac)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutLeaf[i]*w3);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Stem cut (lb C/ac)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutStem[i]*w3);
	}
	fprintf(fout, "\n");

	fprintf(fout, "  Root cut (lb C/ac)		");
	{
	for(int i=1;i<=CropNumbers;i++) fprintf(fout, "%8.0f", yr_CutRoot[i]*w3);
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "  Grazed biomass (lb C/ac)	%8.0f\n", (yr_GrazeGrain[1]+yr_GrazeShoot[1]+yr_GrazeStub)*w3);
	fprintf(fout, "  Livestock demand for grass biomass (lb C/ac)	%8.0f\n", yr_GrazeDemandC*w3);

	fprintf(fout, "  --------------------------------------------------------------------------------------\n");
	fprintf(fout, "  WATER SECTION: Unit mm water/year\n");	
	fprintf(fout, "  -------------------------------------------------------------------------------------\n");

	yr_plant_demand = (yr_pond_ev+yr_trans+yr_soil_ev)*1000.0;
	yr_TotalEvap = (yr_pond_ev + yr_soil_ev)*1000.0;
	yr_PrecWater = yr_rain*10.0;

	yr_dSoilWater = (yr_rain+yr_irri) - (yr_trans+yr_soil_ev+yr_runoff+yr_leach_water); //m
	
	fprintf(fout, "  Precipitation			%.2f\n", yr_rain*1000.0); 
	fprintf(fout, "  Irrigation			%.2f\n", yr_irri*1000.0);
	fprintf(fout, "  PET				%.2f\n", yr_PET*1000.0);
	fprintf(fout, "  Transpiration			%.2f\n", yr_trans*1000.0);
	fprintf(fout, "  Soil evaporation		%.2f\n", (yr_soil_ev+yr_pond_ev)*1000.0);
	fprintf(fout, "  Run off			%.2f\n", yr_runoff*1000.0);
	fprintf(fout, "  Leaching			%.2f\n", yr_leach_water*1000.0);
//	fprintf(fout, "  Change in soil water		%.2f\n", yr_dSoilWater*1000.0);
	fprintf(fout, "  Deep water pool    		%.2f\n", WaterPool*1000.0);
	fprintf(fout, "  Mean wind speed (m/s) 	%.2f\n", yr_WindSpeed/365.0);

	fprintf(fout, "  -------------------------------------------------------------------------------------\n");

	if(UseION==1) 
	{
		fprintf(fout, "  Soil inorganic N adjustment due to artificially altering ION profile\n"); 
		fprintf(fout, "  Adjusted NO3 (lb N/ac)			%.2f\n", AdjustNO3*w3);
		fprintf(fout, "  Adjusted NH4 (lb N/ac)			%.2f\n", AdjustNH4*w3);
	}
}

}	/////////////////////////////////////////////////////////////////////////////////////////////////////

//#endif		
		
	//fclose( fout );

	int IDID=0;

	sprintf(YR, "%s\\Inter\\Summary-%d", OUTPUT, year);
	
	fout = fopen( YR, "w" );
	if ( fout == NULL ) note(1, YR);
		
	fprintf(fout, "%d	Site_ID:	\n", IDID);
	fprintf(fout, "%s	Site_name:	\n", site);
	fprintf(fout, "%.2f	Mean annual temperature (degree C):	\n", yr_avet);
	
	fprintf(fout, "%.2f	Soil_bulk_density (g/cm3):	\n", sd[1]);
	fprintf(fout, "%.2f	Initial_SOC (kg C/kg soil):	\n", Tttoo[1]);
	fprintf(fout, "%.2f	Clay_fraction:	\n", clay[1]);
	fprintf(fout, "%.2f	Soil_pH:	\n", soil_ph[1]);
	fprintf(fout, "%s	Crop_type:	\n", crop_name[1]);
	fprintf(fout, "%s	Crop_type:	\n", crop_name[2]);
	fprintf(fout, "%s	Crop_type:	\n", crop_name[3]);
	//fprintf(fout, "%.2f	Planted_area (ha):			\n", ha);
	
	fprintf(fout, "%.2f	Irrigation_index:	\n", irri_index);
	fprintf(fout, "%.2f	Manure_amended (kg C/ha/yr):	\n\n", yr_addmc);

	fprintf(fout, "%.2f	N_deposit (kg N/ha/yr):	\n", yr_rainN);
	fprintf(fout, "%.2f	Fertilizer_N (kg N/ha/yr):	\n", yr_addfer);
	fprintf(fout, "%.2f	Manure_N (kg N/ha/yr):	\n", yr_addmn);
	fprintf(fout, "%.2f	Irrigation_N (kg N/ha/yr):	\n", yr_irri_N);
	fprintf(fout, "%.2f	Root_N (kg N/ha/yr):	\n", 0.0);
	fprintf(fout, "%.2f	Crop_residue_N (kg N/ha/yr):	\n", yr_sln);
	fprintf(fout, "%.2f	Soil_fixed_N (kg N/ha/yr):	\n", yr_soilN_from_Nfixation);
	fprintf(fout, "%.2f	N_fixation1 (kg N/ha/yr):	\n", yr_fixn[1]);
	fprintf(fout, "%.2f	N_fixation2 (kg N/ha/yr):	\n", yr_fixn[2]);
	fprintf(fout, "%.2f	N_fixation3 (kg N/ha/yr):	\n", yr_fixn[3]);

	fprintf(fout, "%.2f	N_uptaken_by_crop1 (kg N/ha/yr):	\n", yr_uptaken[1]);//R_plantn[1]);
	fprintf(fout, "%.2f	N_uptaken_by_crop2 (kg N/ha/yr):	\n", yr_uptaken[2]);//R_plantn[2]);
	fprintf(fout, "%.2f	N_uptaken_by_crop3 (kg N/ha/yr):	\n", yr_uptaken[3]);//R_plantn[3]);

	fprintf(fout, "%.2f	Runoff N (kg N/ha/yr):	\n", yr_runoff_N);	
	fprintf(fout, "%.2f	Nitrate_leached (kg N/ha/yr):	\n", YrLeachNO3);
	fprintf(fout, "%.2f	NH3_volatilization (kg N/ha/yr):	\n", yr_soil_nh3);
	fprintf(fout, "%.2f	N2O_emission (kg N/ha/yr):	\n", yr_dnn2o);
	fprintf(fout, "%.2f	NO_emission (kg N/ha/yr):	\n", yr_dnno);
	fprintf(fout, "%.2f	N2_emission (kg N/ha/yr):	\n", yr_dnn2);
	//fprintf(fout, "%.2f	Weed_N (kg N/ha/yr):	\n\n", yr_weedn);
	
	fprintf(fout, "%.2f	C_input_from_crop_root (kg C/ha/yr):	\n", yr_addrc);
	fprintf(fout, "%.2f	C_input_from_crop_shoot (kg C/ha/yr):	\n", yr_addtc);
	fprintf(fout, "%.2f	C_input_from_roots (kg C/ha/yr):	\n", yr_InputRoot_DOC);
	fprintf(fout, "%.2f	C_input_from_manure (kg C/ha/yr):	\n", yr_addmc);
	fprintf(fout, "%.2f	Soil_heterotrophic_CO2 (kg C/ha/yr):	\n", yr_soil_co2);
	fprintf(fout, "%.2f	CH4_emission (kg C/ha/yr):	\n", yr_ch4);
	fprintf(fout, "%.2f	SOC_leaching (kg C/ha/yr):	\n\n",yr_leach_hu);//+yr_FrostBio);
	fprintf(fout, "%.2f	Change_in_SOC (kg C/ha/yr):	\n\n", EndSOC-IniSOC);

	fprintf(fout, "%.2f	Annual precipitation (mm):	\n", yr_rain*1000.0);	
	fprintf(fout, "%.0f	Irrigation			\n", yr_irri*1000.0);
	fprintf(fout, "%.0f	Transpiration1			\n", crop_trans[1]*1000.0);
	fprintf(fout, "%.0f	Transpiration2			\n", crop_trans[2]*1000.0);
	fprintf(fout, "%.0f	Transpiration3			\n", crop_trans[3]*1000.0);
	fprintf(fout, "%.0f	Soil evaporation		\n", yr_soil_ev*1000.0);
	fprintf(fout, "%.0f	Surface water evaporation	\n", yr_pond_ev*1000.0);
	fprintf(fout, "%.0f	Run off			\n", yr_runoff*1000.0);
	fprintf(fout, "%.0f	Leaching			\n", yr_leach_water*1000.0);
	fprintf(fout, "%.0f	Groundwater suply		\n\n", yr_GWsuply*1000.0);
	
	fprintf(fout, "%.2f	Crop_biomass1 (kg C/ha):	\n", Yr_PlantBiomass[1]);
	fprintf(fout, "%.2f	Crop_biomass2 (kg C/ha):	\n", Yr_PlantBiomass[2]);
	fprintf(fout, "%.2f	Crop_biomass3 (kg C/ha):	\n", Yr_PlantBiomass[3]);
	
	for(int ia=1; ia<=3; ia++)
		fprintf(fout, "%.2f	Crop_grain1 (kg C/ha):	\n", YrG_grain[ia]);//+ yr_CutGrain[i]+yr_GrazeGrain[i]);
	
	for(int ib=1; ib<=3; ib++)	
		fprintf(fout, "%.2f	Crop_shoot1 (kg C/ha):	\n", YrG_leaf[ib]+YrG_stem[ib]);// + yr_CutLeaf[i]+yr_CutStem[i]+yr_GrazeShoot[i]);
	
	for(int ic=1; ic<=3; ic++)
		fprintf(fout, "%.2f	Crop_root1 (kg C/ha):	\n", YrG_root[ic]);// + yr_CutRoot[i]+yr_GrazeRoot[i]);

	for(int id=1; id<=3; id++)
		fprintf(fout, "%.2f	Crop_N1 (kg N/ha):	\n", yr_plantn[id]);
	
	for(int ie=1; ie<=3; ie++)
		fprintf(fout, "%.2f	Optimum_grain1 (kg C/ha):	\n", OptGrainC[ie]);
	
	for(int ifw=1; ifw<=3; ifw++)
		fprintf(fout, "%.2f	Optimum_straw1 (kg C/ha):	\n", OptLeafC[ifw]+OptStemC[ifw]);
	
	for(int ig=1; ig<=3; ig++)
		fprintf(fout, "%.2f	Optimum_root1 (kg C/ha):	\n", OptRootC[ig]);
	
	for(int ih=1; ih<=3; ih++)
		fprintf(fout, "%.2f	Crop_water_demand1 (mm):	\n", crop_PT[ih]*1000.0);//CropWaterDemand[1]*1000.0);
	
	for(int ii=1; ii<=3; ii++)
		fprintf(fout, "%.2f	Crop_N_demand1 (kg N/ha):	\n", maxmn[ii]);//maxmn[1]);

	for(int ij=1; ij<=3; ij++)
		fprintf(fout, "%.2f	Crop_T_demand1 (degree):	\n", crop_T_demand[ij]);

	for(int ik=1; ik<=3; ik++)
		fprintf(fout, "%.2f	TDD (degree):	\n", TDD[ik]);

	for(int il=1; il<=3; il++)
		fprintf(fout, "%d %d	Crop1 plant/harvest dates:	\n", jdseed[il], HarvestDay[il]);

	fclose( fout );
	
	multi_yr_record(MODE, Batch, EndSOC, Pass, PassC1);//+

    return( 0 );
}

#ifdef DEGUI
#else	
void class_model::write_MonteCarlo(int sample, int county_ID1, char* cropping_system)
{
    float dSOC;
 	
	CString para[6]={"None","None","None","None","None","None"};
	CString MCname[48]={"",
		"Temp ", "Prec ", "CO2  ", "NH3  ", "N_dep", 
		"Clay ", "Dens ", "SKS  ", "Fldcp", "Wiltp", 
		"Poro ", "SOC  ", "IniLi", "IniHu", "NO3  ", 
		"NH4  ", "pH   ", "Yield", "FeedRate ", "CP ", 
		"Phosphorus ", "P_C/N", "N_fix", "R_H2O", "LAI  ", 
		"High ", "TDD  ", "Resid", "T_day", "T_dep", 
		"F_day", "F_dep", "F_rat", "M_day", "M_C/N", 
		"M_rat", "Irri ", "     ", "G_num", "G_day", 
		"G_hrs", "     ", "G_cut", "Top_s", "dSOC ",
		"     ", "     "};

	dSOC = EndSOC - IniSOC;

	//////////////////////////////////////////
	float MC_grainC=0.0, MC_shootC=0.0, MC_rootC=0.0, MC_CutPlantC=0.0, MC_GrazePlantC=0.0;
	for(int i=1;i<=CropNumbers;i++) 
	{
		MC_grainC += (YrG_grain[i]);//+yr_CutGrain[i]+yr_GrazeGrain[i]); 
		MC_shootC += (YrG_leaf[i]+YrG_stem[i]);//+yr_CutLeaf[i]+yr_CutStem[i]+yr_GrazeShoot[i]);
		MC_rootC += (YrG_root[i]);//+yr_CutRoot[i]+yr_GrazeRoot[i]);
		MC_CutPlantC += (yr_CutGrain[i]+yr_CutLeaf[i]+yr_CutStem[i]+yr_CutRoot[i]);
		MC_GrazePlantC += (yr_GrazeGrain[i]+yr_GrazeShoot[i]+yr_GrazeRoot[i]);
	}
	
	////////////////////////////////////////////////////////////

	CString MCC;
	FILE *mc;

	if(Option>100)
	{
		int item[10], k, i;
		float value[10]={0.0,0.0};
		CString SMCabc;
		FILE *smc;
		SMCabc.Format("%s\\Inter\\SiteMCinput", OUTPUT);
		smc=fopen(SMCabc, "r");
		if(smc==NULL) note(0, SMCabc);
		
		fscanf(smc, "%d", &k);
		for(int im=1; im<=k; im++)
		{
			fscanf(smc, "%d %f", &item[im], &value[im]);
			para[im] = MCname[item[im]];
		}
		fclose(smc);

		MCC.Format("%s\\Record\\MonteCarlo\\Site_%s.%s",  OUTPUT,site, CSV);
		if(sample==1&&year==1) //
		{
			mc=fopen(MCC, "w");
			
			fprintf(mc, "Results of Monte Carlo test\n");
			fprintf(mc, ",,Output parameters,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Variation of input parameters\n");

			fprintf(mc, "%-5s,  %-5s, ", "No.","Year");
	
#ifdef MANURE
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, ",
				         "Intake-C", "Intake-N", "Barn-CO2","Barn-CH4","Barn-N2O","Barn-NH3", "Compost-CO2","Compost-CH4","Compost-N2O","Compost-NH3","Lagoon-CO2","Lagoon-CH4","Lagoon-N2O","Lagoon-NH3","Digester-CO2","Digester-CH4","Digester-N2O","Digester-NH3");
#endif

			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,%-10s\n",
				         "Grain-C","Shoot-C","Root-C","CutBiomassC","GrazedBiomassC","dSOC","Field-CH4","Field-N2O","Field-NO","Field-N2","Field-NH3","Field-N-leach","Field-N-runoff","Field_runoff",para[1],para[2],para[3],para[4],para[5]);
			
			fprintf(mc, "%-5s,  %-5s, ", "No.","Year");			

#ifdef MANURE
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, ",
						"kgC","kgN","kgC","kgC","kgN","kgN","kgC","kgC","kgN","kgN","kgC","kgC","kgN","kgN","","","","");
#endif			
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s\n",
			            "kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha", "kgC/ha","kgN/ha","kgN/ha","kgN/ha","kgN/ha","kgN/ha","kgN/ha","mm","","","","","");
		}
		else 
		{
			mc=fopen(MCC, "a");
		}

		fprintf(mc, "%5d,  %5d, ", Option-100, year);

#ifdef MANURE
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, ",
				 MData.yr_intake_C, MData.yr_intake_N, MData.yr_house_co2+MData.yr_enteric_co2, MData.yr_enteric_ch4+MData.yr_house_ch4,MData.yr_enteric_n2o+MData.yr_house_n2o, MData.yr_house_nh3,
				 MData.yr_compost_co2, MData.yr_compost_ch4, MData.yr_compost_n2o, MData.yr_compost_nh3, 
				 MData.yr_lagoon_co2, MData.yr_lagoon_ch4, MData.yr_lagoon_n2o, MData.yr_lagoon_nh3, 
				 MData.yr_digester_co2,MData.yr_digester_ch4,MData.yr_digester_n2o,MData.yr_digester_nh3);

#endif
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f\n",
				 MC_grainC,MC_shootC,MC_rootC,MC_CutPlantC,MC_GrazePlantC, dSOC, yr_ch4, yr_dnn2o, yr_dnno, yr_dnn2, yr_soil_nh3, yr_leach_NO3+yr_leach_urea, yr_runoff_N, yr_runoff*1000.0, value[1],value[2],value[3],value[4],value[5]);
	}
	else
	{
		float SOC, Clay, pH, BD;
		int RN1, RN2, RN3, RN4;
		CString note;
			FILE *mcc;
			note.Format("%s\\Inter\\Combination_%d", OUTPUT, sample);
			mcc=fopen(note, "r");
			if ( mcc == NULL )
			{
					CString mess;
					mess.Format("Can not open %s.", note);
					AfxMessageBox(mess);
					exit(0);
			}
			fscanf(mcc, "%f %f %f %f", &SOC, &Clay, &pH, &BD);
			fscanf(mcc, "%d %d %d %d", &RN1, &RN2, &RN3, &RN4);
			fclose(mcc);

		MCC.Format("%s\\Record\\MonteCarlo\\MonteCarlo.txt", OUTPUT);
		if(sample==1) 
		{
			mc=fopen(MCC, "w");
			fprintf(mc, "Result of Monte Carlo test for crop %s in grid %d\n", cropping_system, county_ID1);
			fprintf(mc, "No.       dSOC        CH4         N2O         NO         N2         NH3        N_leaching          Combination of soil parameters\n");
			fprintf(mc, "          kg C/ha     kg C/ha     kg N/ha     kg N/ha    kg N/ha    kg N/ha    kg N/ha/yr          SOC       Clay      pH        Density\n");
		}
		else 
		{
			mc=fopen(MCC, "a");
		}

		
		fprintf(mc, "%6d,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,  %10.2f,            %2d,%6.3f,%2d,%6.2f,%2d,%6.2f,%2d,%6.2f\n",
						 sample, dSOC, yr_ch4, yr_dnn2o, yr_dnno, yr_dnn2, yr_soil_nh3, yr_leach_NO3+yr_leach_urea, RN1, SOC, RN2, Clay, RN3, pH, RN4, BD);
	}
	fclose(mc);
	
}




void class_model::write_BatchSummary(int sample, char* site, char* PassC1)
{
    float dSOC;
    FILE  *fp;
    char  IE[120];
 	
	CString para[6]={"None","None","None","None","None","None"};
	CString MCname[48]={"",
		"Temp ", "Prec ", "CO2  ", "NH3  ", "N_dep", 
		"Clay ", "Dens ", "SKS  ", "Fldcp", "Wiltp", 
		"Poro ", "SOC  ", "IniLi", "IniHu", "NO3  ", 
		"NH4  ", "pH   ", "Yield", "FeedRate ", "CP ", 
		"Phosphorus ", "P_C/N", "N_fix", "R_H2O", "LAI  ", 
		"High ", "TDD  ", "Resid", "T_day", "T_dep", 
		"F_day", "F_dep", "F_rat", "M_day", "M_C/N", 
		"M_rat", "Irri ", "     ", "G_num", "G_day", 
		"G_hrs", "     ", "G_cut", "Top_s", "dSOC ",
		"     ", "     "};


	dSOC = EndSOC - IniSOC;
	float dSN = -IniSON - IniSIN + EndSON + EndSIN;
	float totalInputN = yr_rainN + yr_addfer + yr_addmn + yr_sln;
	float totalCropNUptake = yr_uptaken[1] + yr_uptaken[2] + yr_uptaken[3]+ yr_uptaken[4];
	float totalOutputN = totalCropNUptake  + yr_leach_NO3 + yr_leach_urea + yr_runoff_N + yr_dnn2o + yr_dnno + yr_dnn2 + yr_soil_nh3;


	//////////////////////////////////////////
	float MC_grainC = 0.0, MC_shootC = 0.0, MC_rootC = 0.0, MC_CutPlantC = 0.0, MC_GrazePlantC = 0.0, MC_CutPlantCEach[7] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	for(int i=1;i<=CropNumbers;i++) 
	{
		MC_grainC += (YrG_grain[i]);//+yr_CutGrain[i]+yr_GrazeGrain[i]); 
		MC_shootC += (YrG_leaf[i]+YrG_stem[i]);//+yr_CutLeaf[i]+yr_CutStem[i]+yr_GrazeShoot[i]);
		MC_rootC += (YrG_root[i]);//+yr_CutRoot[i]+yr_GrazeRoot[i]);
		MC_CutPlantC += (yr_CutGrain[i]+yr_CutLeaf[i]+yr_CutStem[i]+yr_CutRoot[i]);
		MC_GrazePlantC += (yr_GrazeGrain[i]+yr_GrazeShoot[i]+yr_GrazeRoot[i]);
		

	}
	for (int z = 0; z <= cut_num; z++)
	{
		
		MC_CutPlantCEach[z] = eachGrassCut[1][z];
	}
	////////////////////////////////////////////////////////////

	CString MCC;
	FILE *mc;

	//if(Option>100)
	{
		int item[10], k, i;
		float value[10]={0.0,0.0};
		
		/*CString SMCabc;
		FILE *smc;
		SMCabc.Format("%s\\Inter\\SiteMCinput", OUTPUT);
		smc=fopen(SMCabc, "r");
		if(smc==NULL) note(0, SMCabc);
		
		fscanf(smc, "%d", &k);
		for(int i=1; i<=k; i++)
		{
			fscanf(smc, "%d %f", &item[i], &value[i]);
			para[i] = MCname[item[i]];
		}
		fclose(smc);*/

		MCC.Format("%s\\Record\\Batch\\BatchSummary.csv",  OUTPUT);
		if(year==1&&sample==1)
		{
			mc=fopen(MCC, "w");
			//fprintf(mc, "Results of Monte Carlo test for crop %s in grid %s\n", cropping_system, county_ID1);
			fprintf(mc, "Results of a batch run\n");
			
			fprintf(mc, "%-5s,  %-5s, ", "File","Year");
	
#ifdef MANURE
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, , %-10s, %-10s, ",
				         "Intake-C", "Intake-N", "Barn-CO2","Barn-CH4","Barn-N2O","Barn-NH3", "Compost-CO2","Compost-CH4","Compost-N2O","Compost-NH3","Lagoon-CO2","Lagoon-CH4","Lagoon-N2O","Lagoon-NH3","Digester-CO2","Digester-CH4","Digester-N2O","Digester-NH3","Rainfall","AveT");
#endif

	/*
			//start Lowinput output
			
			fprintf(mc, "%-10s, %-10s,",
				"Site", "WeatherFile");


			
			fprintf(mc, "%-10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, ",
					 "CropID1", "Ninput1", "Cinput1", "PDate1", "Yield1", "EmergDate1", "AnthDate1", "AnthDate1b", "AnthDate1c", "AnthDate1d", "MatDate1");
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, ",
				"Biom-Agb1", "Biom-Roots1", "MaxLAI1", "CumEvap1", "Transpiration1", "CropN-Abg1", "CropN-Roots1", "GrainN1", "Nuptake1", "Nleach1");
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,%-10s,%-10s,%-10s,%-10s, ",
				"Nmin1", "WDrain1", "NH3Vol1", "NImmo1", "NDen1", "SoilNMat1",  "QCO2hum1", "QCO2res1","QNHum1","QNres1","SoilWL151","SoilW201");

			fprintf(mc, "%-10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, ",
				"CropID2", "Ninput2", "Cinput2", "PDate2", "Yield2", "EmergDate2", "AnthDate2", "AnthDate2b", "AnthDate2c", "AnthDate2d", "MatDate2");
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, ",
				"Biom-Agb2", "Biom-Roots2", "MaxLAI2", "CumEvap2", "Transpiration2", "CropN-Abg2", "CropN-Roots2", "GrainN2", "Nuptake2", "Nleach2");
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,%-10s,%-10s,%-10s,%-10s, ",
				"Nmin2", "WDrain2", "NH3Vol2", "NImmo2", "NDen2", "SoilNMat2", "QCO2hum2", "QCO2res2", "QNHum2", "QNres2", "SoilWL152", "SoilW202");

			fprintf(mc, "%-10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, % -10s, ",
				"CropID3", "Ninput3", "Cinput3", "PDate3", "Yield3", "EmergDate3", "AnthDate3", "AnthDate3b", "AnthDate3c", "AnthDate3d", "MatDate3");
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, ",
				"Biom-Agb", "Biom-Roots", "MaxLAI", "CumEvap", "Transpiration", "CropN-Abg", "CropN-Roots", "GrainN", "Nuptake", "Nleach");
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,%-10s,%-10s,%-10s,%-10s, ",
				"Nmin3", "WDrain3", "NH3Vol3", "NImmo3", "NDen3", "SoilNMat3", "QCO2hum3", "QCO2res3", "QNHum3", "QNres3", "SoilWL153", "SoilW203");


			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s\n",
				"Precip", "Temp","CropGD1", "CropGD2", "CropGD3","SOC64","SOC66","SOC80","SOC304","SON64","SON66","SON80","SON304","BASECO2");
				
		//end lowInput output
		*/ 
		
//start normal output


		fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,", 
				         "Grain1-C","Shoot1-C","Root1-C","Grain2-C","Shoot2-C","Root2-C","Grain3-C","Shoot3-C","Root3-C","CutBiomassC","GrazedBiomassC");
		fprintf(mc ,"%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,", 
						 "Manure-C","Manure-N","Fertilizer-N","Litter-C","Litter-N","Soil-fixation-N","CropN-from-soil","CropN-from-fixation");
		fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-40s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,", 
						 "dSOC","Field-CH4","Field-N2O","Field-NO","Field-N2","Field-NH3","Field-N-leach","Site_name","Rainfall","AveT","ENDSIN","Water","Nitrogen","CROP","CROP");
		fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,",				 
		"Total_SOC-30","PET","Transp","Evap","ENDSIN","FloweringDay","PodDay","MaturityDay1","GrowthStatus");
		fprintf(mc, "%-10s, %-10s, %-10s, %-10s,%-10s,", "Grain1-N","Shoot1-N","Leaf1-N","Root1-N", "LAI1");
		fprintf(mc, "%-10s, %-10s, %-10s, %-10s,%-10s,", "Grain2-N","Shoot2-N","Leaf2-N","Root2-N", "LAI2");
	//	fprintf(mc, "%-10s, %-10s, %-10s, %-10s,%-10s,", "Grain3-N", "Shoot3-N", "Leaf3-N", "Root3-N", "LAI3");
				fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,","HarvSIN","GermReport","Biomass-Sens1","Biomass-Sens2","Biomass-Sens3","SeedFillDay","GCutNumber");//YR_PETCROP
		fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,","SOC010","SOC1020","SOC2030","SOC3040","SOC4050","CROP","CROP","CROP","NSTRESS","NSTRESS","NSTRESS","IRRI","CROPTStress","PlantDate","StuntGrowth","SeasPrecip","SeasEvap","CO2_Factor","MaxMn","cropCHU","SeasPET","SeasPETKC","Leach","runoff","PhotoPeriod");
		fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "GrassCUT1", "GrassCUT2", "GrassCUT3", "GrassCUT4", "GrassCUT5", "GrassCUT6");
		fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "Atmo_N", "FertN", "ManureN", "LitterN", "Total_InputN", "CropN_up", "Leach_NO3", "RunOff_N", "N2O", "NO", "N2", "NH3", "TotalN_Out", "Diff_INOUT","Soil_DSN","BALANCE","ClimName","Clay");
		fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s\n", "GS-Prec", "GS-TEMP", "GS-N2O", "NGS1-Prec", "NGS1-TEMP", "NGS1-N2O", "NGS2-Prec", "NGS2-TEMP", "NGS2-N2O","Leach_Water","LeafTemp");

//end normal output

		//fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "seasDay1-harv-atemp","seasDay1-harv-precip","seasDay1-harv-wrunoff","seasDay1-harv-wleach","seasDay1-harv-denit","seasDay1-harv-N2O","seasDay1-harv-NH3","seasDay1-harv-netNmin","seasDay1-harv-Nleach","seasDay1-harv-irri","seasDay1-harv-cIrri","seasDay1-harv-trans","seasDay1-harv-evap");
		//fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "seaspDate-365-atemp","seaspDate-365-precip","seaspDate-365-wrunoff","seaspDate-365-wleach","seaspDate-365-denit","seaspDate-365-N2O","seaspDate-365-NH3","seaspDate-365-netNmin","seaspDate-365-Nleach","seaspDate-365-irri","seaspDate-365-cIrri","seaspDate-365-trans","seaspDate-365-evap");
		//fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,","seasDay182-365-atemp","seasDay182-365-precip","seasDay182-365-wrunoff","seasDay182-365-wleach","seasDay182-365-denit","seasDay182-365-N2O","seasDay182-365-NH3","seasDay182-365-netNmin","seasDay182-365-Nleach","seasDay182-365-irri","seasDay182-365-trans","seasDay182-365-evap");

			

		
		//AGMIP-Soybean	
	//	fprintf(mc, "%-10s, %-10s, %-10s, %-10s,%-10s,", "Grain1-N","Shoot1-N","Leaf1-N","Root1-N", "LAI1");
	//	fprintf(mc, "%-10s, %-10s, %-10s, %-10s,%-10s,", "Grain2-N","Shoot2-N","Leaf2-N","Root2-N", "LAI2");
	//	fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "seasDay1-harv-atemp","seasDay1-harv-precip","seasDay1-harv-wrunoff","seasDay1-harv-wleach","seasDay1-harv-denit","seasDay1-harv-N2O","seasDay1-harv-NH3","seasDay1-harv-netNmin","seasDay1-harv-Nleach","seasDay1-harv-irri","seasDay1-harv-cIrri","seasDay1-harv-trans","seasDay1-harv-evap");
	//	fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "seaspDate-365-atemp","seaspDate-365-precip","seaspDate-365-wrunoff","seaspDate-365-wleach","seaspDate-365-denit","seaspDate-365-N2O","seaspDate-365-NH3","seaspDate-365-netNmin","seaspDate-365-Nleach","seaspDate-365-irri","seaspDate-365-cIrri","seaspDate-365-trans","seaspDate-365-evap");
	//	fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,","seasDay182-365-atemp","seasDay182-365-precip","seasDay182-365-wrunoff","seasDay182-365-wleach","seasDay182-365-denit","seasDay182-365-N2O","seasDay182-365-NH3","seasDay182-365-netNmin","seasDay182-365-Nleach","seasDay182-365-irri","seasDay182-365-trans","seasDay182-365-evap");
	//	fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s\n","HarvSIN","GermReport","Biomass-Sens1","Biomass-Sens2","Biomass-Sens3");
//AGMIP-Soybean				 
						 
			//normal output -- off for lowinput 
			fprintf(mc, "%-5s,  %-5s, ", "File","Year");			

#ifdef MANURE
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, ",
						"kgC","kgN","kgC","kgC","kgN","kgN","kgC","kgC","kgN","kgN","kgC","kgC","kgN","kgN","","","","");
#endif			
			
			
			
			
			
		//normal ouptut	--off for lowinput
			fprintf(mc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-40s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,",
			            "kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha", "kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgC/ha","kgN/ha","kgN/ha","kgN/ha", "kgC/ha","kgC/ha", "kgN/ha","kgN/ha", "kgC/ha","kgC/ha","kgN/ha","kgN/ha","kgN/ha","kgN/ha","kgN/ha","Site_name","mm","Degree_C","kgN/ha","WaterStress","NStress","HarvestDay","GrowDays","mm","mm","mm","mm","mm","mm","mm","mm","mm","mm","kg N ha","kg N ha","kg N ha","kg N ha","kg N ha","kg N ha","kg N ha","kg N ha","","kg N ha","day","kg  ha","kg ha","kg ha","day","mm","kg C ha","kg C ha","kg C ha","kg C ha", "kg C ha","type#", "type#", "type#","","","","","","","","mm","mm","index","kgN/ha","mm","mm","mm","mm", "mm", "");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha", "kgC/ha");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgN/ha","File","Fract");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s\n", "mm", "oC", "kgN/ha", "mm", "oC", "kgN/ha", "mm", "oC", "kgN/ha","mm","oC");
/*
//Agmip Low input output units
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,","","", "site", "weatherName");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "cropID", "kgN/ha", "kgC/ha", "jday", "t/DM/ha", "jday", "jday", "jday", "jday", "jday", "jday");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "t/DM/ha", "t/DM/ha", "LAI", "mm", "mm", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "kg N/ha", "mm", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg CO2/ha", "kg CO2/ha", "kg N/ha", "kg N/ha", "mm", "mm");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "cropID", "kgN/ha", "kgC/ha", "jday", "t/DM/ha", "jday", "jday", "jday", "jday", "jday", "jday");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "t/DM/ha", "t/DM/ha", "LAI", "mm", "mm", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "kg N/ha", "mm", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg CO2/ha", "kg CO2/ha", "kg N/ha", "kg N/ha", "mm", "mm");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "cropID", "kgN/ha", "kgC/ha", "jday", "t/DM/ha", "jday", "jday", "jday", "jday", "jday", "jday");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "t/DM/ha", "t/DM/ha", "LAI", "mm", "mm", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha");
			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,", "kg N/ha", "mm", "kg N/ha", "kg N/ha", "kg N/ha", "kg N/ha", "kg CO2/ha", "kg CO2/ha", "kg N/ha", "kg N/ha", "mm", "mm");

			fprintf(mc, "%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s\n", "mm", "oC", "days", "days", "days", "t C/ha", "t C/ha", "t C/ha", "t C/ha", "t N/ha", "t N/ha", "t N/ha", "t N/ha", "CO2");
//end Agmip Low input output units
*/
		}
		else 
		{
			mc=fopen(MCC, "a");
		}

		fprintf(mc, "%5d,  %5d, ", sample, year);

#ifdef MANURE
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, ",
				 MData.yr_intake_C, MData.yr_intake_N, MData.yr_house_co2+MData.yr_enteric_co2, MData.yr_enteric_ch4+MData.yr_house_ch4,MData.yr_enteric_n2o+MData.yr_house_n2o, MData.yr_house_nh3,
				 MData.yr_compost_co2, MData.yr_compost_ch4, MData.yr_compost_n2o, MData.yr_compost_nh3, 
				 MData.yr_lagoon_co2, MData.yr_lagoon_ch4, MData.yr_lagoon_n2o, MData.yr_lagoon_nh3, 
				 MData.yr_digester_co2,MData.yr_digester_ch4,MData.yr_digester_n2o,MData.yr_digester_nh3);

#endif

	/*
//start Agmip Lowinput output

		float DMConv = 1.0 / 1000 / 0.435;


		fprintf(mc, "%-40s, %-40s,",
			site, weatherName); 

		fprintf(mc, "%6d, % 10.2f, % 10.2f, % 6d, % 10.4f, % 6d, % 6d, % 6d,% 6d, % 6d, % 6d, ",
			crop[1], FertAddNSA[1], FertAddCSA[1]/1000.0, plantingDay[1], seasGrain[1]*DMConv, emergenceDay[1], flowering1Day[1], flowering1Day[2], flowering1Day[3], flowering1Day[4], maturityDay[1]);
		fprintf(mc, "%10.4f, %10.4f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,%10.2f,%10.2f,",
			(seasGrain[1] + seasLeaf[1] + seasStem[1])* DMConv, seasRoot[1] * DMConv, seasMaxLAI1, (seasEvap1 * 1000), trans1 * 1000.0, (seasGrainN[1] + seasLeafN[1] + seasStemN[1]), seasRootN[1], seasGrainN[1], (seasGrainN[1]+seasLeafN[1]+seasStemN[1]+seasRootN[1]), seasNO31);
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,%10.2f,%10.2f,%10.2f,%10.2f,",
			Nmin1, seasWL1, seasNH31, Nimb1, seasDenit1, seasSoilN1, seasCO2Het1, seasCO2Het1,Nmin1, Nmin1, daySoilWater151, daySoilWater201);

		fprintf(mc, "%6d, % 10.2f, % 10.2f, % 6d, % 10.4f, % 6d, % 6d, % 6d, % 6d, % 6d, % 6d, ",
			crop[2], FertAddNSA[2], FertAddCSA[2] / 1000.0, plantingDay[2], seasGrain[2] * DMConv, emergenceDay[2], flowering2Day[1], flowering2Day[2], flowering2Day[3], flowering2Day[4], maturityDay[2]);
		fprintf(mc, "%10.4f, %10.4f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,%10.2f,%10.2f,",
			(seasGrain[2] + seasLeaf[2] + seasStem[2])* DMConv, seasRoot[2] * DMConv, seasMaxLAI2, (seasEvap2 * 1000), trans2 * 1000.0, (seasGrainN[2] + seasLeafN[2] + seasStemN[2]), seasRootN[2], seasGrainN[2], (seasGrainN[2] + seasLeafN[2] + seasStemN[2] + seasRootN[2]), seasNO32);
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,%10.2f,%10.2f,%10.2f,%10.2f,",
			Nmin2, seasWL2, seasNH32, Nimb2, seasDenit2, seasSoilN2, seasCO2Het2, seasCO2Het2, Nmin2, Nmin2, daySoilWater152, daySoilWater202);

		fprintf(mc, "%6d, % 10.2f, % 10.2f, % 6d, % 10.4f, % 6d, % 6d, % 6d,% 6d, % 6d, % 6d, ",
			crop[3], FertAddNSA[3], FertAddCSA[3] / 1000.0, plantingDay[3], seasGrain[3] * DMConv, emergenceDay[3], flowering3Day[1], flowering3Day[2], flowering3Day[3], flowering3Day[4], maturityDay[3]);
		fprintf(mc, "%10.4f, %10.4f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,%10.2f,%10.2f,",
			(seasGrain[3] + seasLeaf[3] + seasStem[3])* DMConv, seasRoot[3] * DMConv, seasMaxLAI3, (seasEvap3 * 1000), trans3 * 1000.0, (seasGrainN[3] + seasLeafN[3] + seasStemN[3]), seasRootN[3], seasGrainN[3], (seasGrainN[3] + seasLeafN[3] + seasStemN[3] + seasRootN[3]), seasNO33);
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,%10.2f,%10.2f,%10.2f,%10.2f,",
			Nmin3, seasWL3, seasNH33, Nimb3, seasDenit3, seasSoilN3, seasCO2Het3, seasCO2Het3, Nmin3, Nmin3, daySoilWater153, daySoilWater203);


		fprintf(mc, "%10.2f, %10.2f,%6d,%6d,%6d, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f\n", 
			yr_rain * 1000.0, yr_avet,cropGrowDays1,cropGrowDays2,cropGrowDays3,SOC64/1000.0,SOC66 / 1000.0,SOC80 / 1000.0,SOC304 / 1000.0,SON64 / 1000.0,SON66 / 1000.0,SON80 / 1000.0,SON304 / 1000.0,Base_CO2);

//end Agmip Lowinput output		
*/
		//start normal output

		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,", 
				 YrG_grain[1],YrG_leaf[1]+YrG_stem[1],YrG_root[1],YrG_grain[2],YrG_leaf[2]+YrG_stem[2],YrG_root[2],YrG_grain[3],YrG_leaf[3]+ YrG_stem[3],YrG_root[3], MC_CutPlantC, MC_GrazePlantC);
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f,", 
				 yr_addmc, yr_addmn, yr_addfer, yr_addtc+yr_addrc, yr_sln-yr_addrn+yr_addrn, yr_soilN_from_Nfixation, yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3],yr_fixn[1]+yr_fixn[2]+yr_fixn[3]);
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %-40s, %10.2f, %10.2f, %10.2f, %10.2f, %10.2f, %6d, %6d,",
				 dSOC, yr_ch4, yr_dnn2o, yr_dnno, yr_dnn2, yr_soil_nh3, yr_leach_NO3+yr_leach_urea, site, yr_rain*1000.0, yr_avet,EndSIN,crop_water_stress[1]/(float)crop_water_stress_days[1],crop_N_stress[1]/(float)crop_N_stress_days[1],cropHarvestDay[1],cropGrowDays[1]);
		fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%5d, %5d, %5d,%10.2f,", 
		(layerc[1]+layerc[2]+layerc[3]),yr_PET*1000,yr_trans*1000.0,yr_total_ev*1000,EndSIN,floweringDay[1],podDay[1],maturityDay[1],growthStatus[1]);
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f,%10.2f,", YrN_grain[1],YrN_stem[1],YrN_leaf[1],YrN_root[1], YrG_lai[1]);
		fprintf(mc, "%10.2f, %10.2f, %10.2f, %10.2f,%10.2f,", YrN_grain[2],YrN_stem[2],YrN_leaf[2],YrN_root[2], YrG_lai[2]);

		fprintf(mc, "%10.2f,%5d,%10.2f,%10.2f,%10.2f,%5d,%5d,", (HarvSIN+ end_N_gases + day_clay_N),GermReport,totalSens1,totalSens2,totalSens3,seedFillDay[1], currentCut);//yr_PETCROP*1000
		fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%5d,%5d,%5d,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%5d,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,", layerc[1], layerc[2], layerc[3], layerc[4], layerc[5], crop[1], crop[2], crop[3], crop_N_stress[1] / (float)crop_N_stress_days[1], crop_N_stress[2] / (float)crop_N_stress_days[2], crop_N_stress[3] / (float)crop_N_stress_days[3], yr_irri * 1000.0, cropTempStressAnnual[1] / cropTempStressDays[1], jdseed[1], stuntGrowth, seasDay1_pDate_precip * 1000.0, seasDay1_pDate_evap * 1000, CO2_factor, maxmn[1], cropGDD, seasPET * 1000.0, seasPETKC * 1000.0, yr_leach_water * 1000.0, yr_runoff * 1000.0, photoPeriodStress[1]);//EndSOC
		fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,", MC_CutPlantCEach[1], MC_CutPlantCEach[2], MC_CutPlantCEach[3], MC_CutPlantCEach[4], MC_CutPlantCEach[5], MC_CutPlantCEach[6]);
		fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%-10s,%10.2f,", yr_rainN, yr_addfer, yr_addmn, yr_sln, totalInputN, totalCropNUptake, yr_leach_NO3 + yr_leach_urea, yr_runoff_N, yr_dnn2o, yr_dnno, yr_dnn2, yr_soil_nh3, totalOutputN, totalInputN - totalOutputN, dSN, (totalInputN - totalOutputN)-dSN,climd[0],clay[1]);
		fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f\n", gs_precip*1000, gs_atemp/184, gs_N2O, ngs1_precip*1000, ngs1_atemp/120, ngs1_N2O, ngs2_precip*1000, ngs2_atemp/61, ngs2_N2O, yr_leach_water * 1000.0,leafTemp_C[1]);
			//end normal output

		//	fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%3d,%10.2f,%10.2f,", seasDay1_harv_atemp,seasDay1_harv_precip*1000,seasDay1_harv_wrunoff*1000,seasDay1_harv_wleach*1000,seasDay1_harv_denit,seasDay1_harv_N2O,seasDay1_harv_NH3,seasDay1_harv_netNmin,seasDay1_harv_Nleach,seasDay1_harv_irri*1000,countIrri,seasDay1_harv_trans*1000,seasDay1_harv_evap*1000);
//	fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%3d,%10.2f,%10.2f,", seasDay1_pDate_atemp,seasDay1_pDate_precip*1000,seasDay1_pDate_wrunoff*1000,seasDay1_pDate_wleach*1000,seasDay1_pDate_denit,seasDay1_pDate_N2O,seasDay1_pDate_NH3,seasDay1_pDate_netNmin,seasDay1_pDate_Nleach,seasDay1_pDate_irri*1000,countIrri,seasDay1_pDate_trans*1000,seasDay1_pDate_evap*1000);
//	fprintf(mc, "%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,%10.2f,", seasDay182_365_atemp,seasDay182_365_precip*1000,seasDay182_365_wrunoff*1000,seasDay182_365_wleach*1000,seasDay182_365_denit,seasDay182_365_N2O,seasDay182_365_NH3,seasDay182_365_netNmin,seasDay182_365_Nleach,seasDay182_365_irri*1000,seasDay182_365_trans*1000,seasDay182_365_evap*1000);

	
	}

/*
	IniSON,IniSIN,EndSON,EndSIN,dSN, 		
		yr_rainN,yr_addfer,yr_addmn,yr_sln,yr_soilN_from_Nfixation,//yr_addtn+yr_sln+yr_addrn
		yr_uptaken[1]+yr_uptaken[2]+yr_uptaken[3], yr_leach_NO3+yr_leach_urea,yr_runoff_N, yr_leach_un,yr_dnn2o, yr_dnno, yr_dnn2, yr_soil_nh3, day_clay_N,
		yr_PET*1000.0,yr_trans*1000.0, yr_total_ev*1000.0, yr_leach_water*1000.0, yr_runoff*1000.0,
		yr_irri*1000.0, yr_rain*1000.0, WaterPool*1000.0,yr_avet, yr_WindSpeed/365.0, 
		TDD[1]/max_TDD[1], crop_PPT[1]/(float)crop_PPT_days[1],crop_N_stress[1]/(float)crop_N_stress_days[1],
		TotalCutC, yr_end_grain, yr_end_leaf, yr_end_stem, yr_end_root,
		stub1+stub2+stub3,crop_water_stress[1]/(float)crop_water_stress_days[1],crop_water_stress[2]/max((float)crop_water_stress_days[2],1.0),crop_water_stress[3]/max((float)crop_water_stress_days[3],1.0),crop_N_stress[1]/(float)crop_N_stress_days[1],crop_N_stress[2]/max((float)crop_N_stress_days[2],1.0),crop_N_stress[3]/max((float)crop_N_stress_days[3],1.0),TDD[1]/max_TDD[1],TDD[2]/max(max_TDD[2],1.0),TDD[3]/max(max_TDD[3],1.0),
		cropHarvestDay[1],cropGrowDays[1]); 
*/

	fclose(mc);
	
}

#endif
