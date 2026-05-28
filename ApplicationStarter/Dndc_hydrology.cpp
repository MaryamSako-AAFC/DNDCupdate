#include "stdafx.h"
#include "Dndcgo.h"
#include "RunPaths.h"
#include "Source_main.h"
#include "Dndc_tool.h"

//#ifdef HYDRO
void class_model::SCS_MUSLE(int scale, float ha, int livestock)
{
	// ===scs and musle to calculate runoff and sediment;dengjia===
	float PeakR;

	scs_runoff=0;
	sedyld=0;

	if(precipitation>0)
	{
		  float CN2=0;
		  
		  float sol_sumfc=0;//amount of water in the soil profile at field capacity(mm H20)
		  float sol_sw=0;//the amount of water in the soil profile when completely saturated (mmH20)
		  float sw=0;//soil water content of the entire profile excluding the amount of water 
					 //held in the profile at wilting point(mm H20)
		  float wiltsw=0;
		  float sol_ice=0;// top layer soil temprature
		  float precipday=0;//rainfall depth for the day (mm H20)

		  float MSAND=0;//the percent sand content(0.05-2.00mm diameter particles)
		  float MCLAY=0;//the percent clay content(<0.002 diameter particles)
		  float MSILT=0;//the percent silt content(0.002-0.05mm diameter particles)
		  float ORGC=0;//the percent organic carbon content of the layer
		  float MUSLEC=0;//the average annual C factor for the land cover
		//float COV=0;//amount of residue on the soil surface(kg/ha) 
		  float length=0;//the slope length(m)
		  float USLE_P=0;//the supprt practice factor 
		  float ROCK=0;//the percent rock in the first soil layer(%)

		  float a15=0;//the maximum half-hour rainfall fraction for the day
		  float ch_l=0;//the channel length from the most distant point to the subbasin outlet(km)
		  float ch_n=0;//Manning's roughness coeffcient for the channel
		  float ch_s=0;//the channel slope(m/m)
		  float slsubbsn=0;//the subbasin slope length(m) 
		  ManningRoughOverflow=0;//Manning's roughness coeffcient for the subbasin
		  float sno=0;//the water content of the snow cover
/*
		  int rain_yrs=0;//the number of years data used to obtain values for monthly extreme half-hour rainfalls 
		  float adj_pkr=0;//the adjustment factor
		  int mon=0;
		  mon=7;
		  if(jday>=1&&jday<=31)mon=1;
		  else if(jday>=32&&jday<=59)mon=2;
		  else if(jday>=60&&jday<=90)mon=3;
		  else if(jday>=90&&jday<=120)mon=4;
		  else if(jday>=120&&jday<=151)mon=5;
		  else if(jday>=151&&jday<=181)mon=6;
		  else if(jday>=181&&jday<=212)mon=7;
		  else if(jday>=212&&jday<=243)mon=8;
		  else if(jday>=243&&jday<=273)mon=9;
		  else if(jday>=273&&jday<=304)mon=10;
		  else if(jday>=304&&jday<=334)mon=11;
		  else if(jday>=334&&jday<=365)mon=12;

		  int pcpd[13];//the number of wet days in the month
		  float rain_hhsm[13];//the smoothed half _hour rainfall amount for the month(mm H20)
		  float pcp_stat[13];//the mean daily rainfall(mm H20)

  */
		
		//read_in_sitemusle();
		if(scale==1) 
		{
			char site_file[80];
			FILE *fp;

			sprintf(site_file, "%sResult\\Inputs\\muslesite", ROOTDIR);
			fp = fopen(site_file, "r");
			if ( fp == NULL ) note(0, site_file);
			 
			fscanf(fp, "%f %f %f %f %f %f %f %f %f %f", &CN2, &length,
			&ch_l, &ch_n, &ch_s, &ManningRoughOverflow,&sub_km,&MUSLEC,&USLE_P,&sslope);

			fclose( fp );

	 //    read_in_soilmusle();   
			char soil_file[80];
			FILE *fps;

			sprintf(soil_file, "%sResult\\Inputs\\muslesoil", ROOTDIR);
			fps = fopen(soil_file, "r");
			if ( fps == NULL )
			{
				printf("File %s not found", soil_file);
				exit(0);
			}
 
			fscanf(fps, "%f %f %f %f %f %f %f %f", &sol_sumfc,&sol_sw, &wiltsw, &MSAND,&MCLAY,&MSILT,&ORGC,&ROCK);

			fclose( fps );  
		}
		else
		{
			//MaxHalfHR: maxmum 0.5-hour precipitation, (cm)
			//ch_l: the channel length from the most distant point to the subbasin outlet(km)
			//ch_n: Manning's roughness coeffcient for the channel
			//ch_s: the channel slope(m/m)
			//length: the slope length(m)
			//ManningRoughOverflow: Manning's roughness coeffcient for the subbasin
			//MSAND, MCLAY, MSILT, ORGC, ROCK: sand, clay, silt, SOC, rock percentage (%)
			//MUSLEC, impact vegetation on erosion (0-1, good-bad),  
			//USLE_P, impact of land management on erosion (0-1, good-bad),

			sol_sw = 2.0 * 1000.0 * sts[1];//2.0 represent the depth of the profile for SCS Brian
			sol_sumfc = sol_sw * fldcap[1];
			wiltsw = sol_sw * wiltpt[1];
			sub_km = 1.0;//ha
			length = 100.0;//m
			MCLAY = clay[1] * 100.0;
			MSILT = (100.0 - MCLAY) * 0.6;
			MSAND = 100.0 - MCLAY - MSILT;
			ROCK = 0.0;
			float TotalBiomass=0.0;
			for(int i=1; i<= CropNumbers; i++) TotalBiomass += PresentBiomass[i];
			MUSLEC = 1.0 - TotalBiomass / 5000.0;
			MUSLEC = max(0.0, min(1.0, MUSLEC));
			
			char scs_para[80];
			FILE *fscs;
			sprintf(scs_para, "%s\\Inputs\\scspara", OUTPUT);
			fscs = fopen(scs_para, "r");
			if(fscs==NULL) note(0, scs_para);			
			fscanf(fscs, "%f %f %f %f %f %f", &CN2, &ManningRoughOverflow, &ch_n, &ch_s, &ch_l, &USLE_P);
			fclose(fscs);		 		
			
		}
/*
	//     read_in_climmusle();
		char clim_file[80];
		FILE *fpc;

		sprintf(clim_file, "%s\\Inputs\\climmusle", OUTPUT);
		fpc = fopen(clim_file, "r");
		if ( fpc == NULL )
		{
			printf("File %s not found", clim_file);
			exit(0);
		}
		fscanf(fpc,"%d %f",&rain_yrs,&adj_pkr);
		for(int i=1;i<=12;i++)
		{
			fscanf(fpc,"%d",&pcpd[i]);
		}
		
		for(int j=1;j<=12;j++)
		{
			fscanf(fpc,"%f",&rain_hhsm[j]);
		}
		for(int k=1;k<=12;k++)
		{
			fscanf(fpc,"%f",&pcp_stat[k]);
		}
	   fclose( fpc );
	*/
	   precipday = precipitation * 1000.0;//m to mm
		//update the sw sno and sol_ice daily   		
	   for(int i=1;i<=q;i++)
	   {
		   sw+=h[i]*1000.0*day_wfps[i]*sts[i];
	   }
	   sw -= wiltsw;  
	   sno = snow_pack * 1000.0;//m to mm
	   sol_ice = ice[1];
		//run scs
		SCS(CN2, sslope,sol_sumfc, sol_sw,sw, sol_ice, precipday);

		//if(scs_runoff>0&&scale==1)
		if(scs_runoff>0)
		{
			//a15=alph(precipday,rain_yrs,adj_pkr,mon,rain_hhsm, pcpd, pcp_stat);
		   a15 = (MaxHalfHR / 100.0) / precipitation;

		   float area=0;
		   if(scale==1)
		   {
			   area=ha;
		   }
		   else
			   area=sub_km;

			//run PEAKRUNOFF
		   float sub_slp;
		   sub_slp=tan(sslope/180.0*3.1416);
		   PeakR=PEAKRUNOFF(a15, ch_l, ch_n, ch_s, length, ManningRoughOverflow, sub_slp, area);

			//run musle
		   MUSLE(PeakR, MSAND, MCLAY, MSILT, ORGC, MUSLEC, sslope, length, USLE_P, ROCK, area);
		   if(sno>0)//if snow greater than zero!!!
		   {
			  sedyld=sedyld/exp(3*sno/25.4);
		   }

		}

		precipitation -= (scs_runoff/1000,0);//mm -> m

	}//Surface runoff and Sediment calculation end if precipitation>0
	else //if no precipitation
	{
		sedyld=0;
	}

	//precipitation -= (scs_runoff/1000,0);//mm -> m

//Calculate the C and N carried by runoff and soil
//	float depthsed;//the depth of the soil layer eroded by runoff
//	float rcvlmusle,rclmusle,rcrmusle,CRB1musle,CRB2musle,crhlmusle,crhrmusle,dphummusle,socmusle;

//Enrichment Ratio
	float concsed=0, EnrichR;
	if(sedyld>0)
	{
	   if(scale==1)
	   {
		concsed=sedyld/(10*ha*scs_runoff);
	   }
	   else
		concsed=sedyld/(10*sub_km*scs_runoff);

	   EnrichR=0.78*powf(concsed,-0.2468);

	   if(scale==1)
		{
		  depthsed=sedyld/sd[1]/((ha+0.0001)*10000);
		}
		else
		  //depthsed=sedyld/sd[1] * 0.01;//eroded thickness of soil, m
			depthsed = sedyld / sd[1] / (sub_km*10000.0);//eroded thickness of soil, m
	}
	else
	{
	   EnrichR=1;
	   depthsed = 0.0;
	}

    

if(depthsed>0.0)
{
	if(depthsed>h[1])//????
		depthsed=h[1];//????
	
	socmusle = (rcvl[1] + rcl[1] + rcr[1] + CRB1[1] + CRB2[1] + crhl[1]+crhr[1] + dphum[1]+inert_C[1])*depthsed/h[1]*EnrichR;//????

	float summuslesoc;
	summuslesoc=rcvl[1] + rcl[1] + rcr[1] + CRB1[1] + CRB2[1] + crhl[1]+crhr[1] + dphum[1]+inert_C[1];
	
	float LossF = socmusle / (summuslesoc+0.0000001);
	
	rcvlmusle = LossF * rcvl[1];
	rcvl[1] -= rcvlmusle;

	rclmusle = LossF * rcl[1];
    rcl[1] -= rclmusle;
	
	rcrmusle = LossF * rcr[1];
    rcr[1] -= rcrmusle;
	
	CRB1musle = LossF * CRB1[1];
    CRB1[1] -= CRB1musle;
	
	CRB2musle = LossF * CRB2[1];
    CRB2[1] -= CRB2musle;
	
	crhlmusle = LossF * crhl[1];
    crhl[1] -= crhlmusle;
	
	crhrmusle = LossF * crhr[1];
    crhr[1] -= crhrmusle;
	
	dphummusle = LossF * dphum[1];
    dphum[1] -= dphummusle;

	float dCharC = LossF * inert_C[1];
    inert_C[1] -= dCharC;

    float Ninsurf=0;
	Ninsurf=rno3*10000*(scs_runoff/1000)*1000/1000000;
	
    sonmusle=rcvlmusle/rcnrvl+rclmusle/rcnrl+rcrmusle/rcnrr+(CRB1musle+CRB2musle)/rcnb+(crhlmusle+crhrmusle)/rcnh+dphummusle/rcnm+dCharC/PassiveCCN;
    nh4musle=nh4[1]*depthsed/h[1]*EnrichR+Ninsurf*0.5;//????
	nh4[1]-=nh4[1]*depthsed/h[1]*EnrichR;
    no3musle=no3[1]*depthsed/h[1]+Ninsurf*0.5;
	no3[1]-=no3[1]*depthsed/h[1];
    nh3musle=nh3[1]*depthsed/h[1];
	nh3[1]-=nh3musle;
	ureamusle=urea[1]*depthsed/h[1];
	urea[1]-=ureamusle;
	claynmusle=clay_nh4[1]*depthsed/h[1]*EnrichR;
	clay_nh4[1]-=claynmusle;

	OrgPmusle = OrgP[1]*depthsed/h[1]*EnrichR;
	OrgP[1] -= OrgPmusle;
	AdsPmusle = AdsP[1]*depthsed/h[1]*EnrichR;
	AdsP[1] -= AdsPmusle;
	LabPmusle = LabP[1]*depthsed/h[1]*EnrichR;
	LabP[1] -= LabPmusle;

    yr_muslerunoff+=scs_runoff;
	yr_muslesedyld+=sedyld;
	yr_muslesoc+=socmusle;
	yr_musleson+=sonmusle;
	yr_muslenh4+=nh4musle;
	yr_musleno3+=no3musle;
	yr_muslenh3+=nh3musle;
	yr_musleurea+=ureamusle;
	yr_musleclayn+=claynmusle;
}
else
{
	socmusle = 0.0;
}

}

void class_model::SCS(float CN2,float sslope,float sol_sumfc,float sol_sw,float sw,float sol_ice,float precipday)
{
	float CN1,CN3, CN1S,CN2S,CN3S, SMX,S3,r2, CNDAY;
	float wrt1,wrt2;//1st&2nd shape parameter for calculation of water retention
	float rto3,rtos;
	r2 = 0.0;
	CN1=CN2-20*(100-CN2)/(100-CN2+exp(2.533-0.0636*(100-CN2)));
    CN3=CN2*exp(0.006729*(100-CN2));
	//Slope adjustments
	CN2S=(CN3-CN2)*(1-2*exp(-13.86*tan(sslope/180*3.1416)))/3+CN2;

    // calculate moisture condition I and III curve numbers
	CN1S=CN2S-20*(100-CN2S)/(100-CN2S+exp(2.533-0.0636*(100-CN2S)));
    if(CN1S<0.4*CN2S) CN1S=0.4*CN2S;
	CN3S=CN2S*exp(0.006729*(100-CN2S));
	SMX=25.4*(1000/CN1S-10);
    S3=25.4*(1000/CN3S-10);
	rto3=1-S3/SMX;
	rtos=1-2.54/SMX;
	wrt2=(log(sol_sumfc/rto3-sol_sumfc)-log(sol_sw/rtos-sol_sw))/(sol_sw-sol_sumfc);
	wrt1=log(sol_sumfc/rto3-sol_sumfc)+wrt2*sol_sumfc;
    float xx=wrt1-wrt2*sw;
    if (xx < -20) xx = -20;
    if (xx > 20) xx = 20;

    if ((sol_sw + exp(xx)) > 0.001) 
        r2 = SMX * (1. - sw / ( sw + exp(xx)));
	//adjustments for frozen conditions
    if (sol_ice >0.0) 
		r2 = SMX * (1. - exp(- 0.000862 * r2));

	if (r2 < 3.0f)
	{
		r2 = 3.0;
	}

	CNDAY= 25400 / (r2 + 254);
    r2=25400. /CNDAY - 254;
	

	float litterFactor;
			litterFactor=1.0;
			if(surface_litter>200)
			{litterFactor=0.5;}
	
	if(precipday>(0.2*r2))
	{
		   scs_runoff += ((precipday-0.2*r2)*(precipday-0.2*r2)/(precipday+0.8*r2))*litterFactor;//surface runoff, mm
	}
	else
		scs_runoff = 0.0;//surface runoff, mm
	

}

/*
void class_model::SCS(float CN2, float sslope, float sol_sumfc, float sol_sw,
	float sw, float sol_ice, float precipday  mm )
{
	float CN1, CN3, CN1S, CN2S, CN3S, SMX, S3, r2, CNDAY;
	float wrt1, wrt2; // shape parameters
	float rto3, rtos;
	r2 = 0.0f;

	// --- (1) Your CN slope & soil-moisture mapping (keep as-is) ---
	CN1 = CN2 - 20.0f * (100.0f - CN2) / (100.0f - CN2 + expf(2.533f - 0.0636f * (100.0f - CN2)));
	CN3 = CN2 * expf(0.006729f * (100.0f - CN2));
	CN2S = (CN3 - CN2) * (1.0f - 2.0f * expf(-13.86f * tanf(sslope / 180.0f * 3.1416f))) / 3.0f + CN2;

	CN1S = CN2S - 20.0f * (100.0f - CN2S) / (100.0f - CN2S + expf(2.533f - 0.0636f * (100.0f - CN2S)));
	if (CN1S < 0.4f * CN2S) CN1S = 0.4f * CN2S;
	CN3S = CN2S * expf(0.006729f * (100.0f - CN2S));

	SMX = 25.4f * (1000.0f / CN1S - 10.0f);
	S3 = 25.4f * (1000.0f / CN3S - 10.0f);
	rto3 = 1.0f - S3 / SMX;
	rtos = 1.0f - 2.54f / SMX;
	wrt2 = (logf(sol_sumfc / rto3 - sol_sumfc) - logf(sol_sw / rtos - sol_sw)) / (sol_sw - sol_sumfc);
	wrt1 = logf(sol_sumfc / rto3 - sol_sumfc) + wrt2 * sol_sumfc;

	float xx = wrt1 - wrt2 * sw;
	if (xx < -20.0f) xx = -20.0f;
	if (xx > 20.0f) xx = 20.0f;
	if ((sol_sw + expf(xx)) > 0.001f)
		r2 = SMX * (1.0f - sw / (sw + expf(xx)));

	// Frozen adjustment
	if (sol_ice > 0.0f)
		r2 = SMX * (1.0f - expf(-0.000862f * r2));

	// Enforce minimum storage depth
	if (r2 < 3.0f) r2 = 3.0f;

	// Convert r2 <-> CN for the day
	CNDAY = 25400.0f / (r2 + 254.0f);
	r2 = 25400.0f / CNDAY - 254.0f;   // ensure consistency (S in mm)

	// Litter/residue factor
	float litterFactor = 1.0f;
	if (surface_litter > 200.0f) litterFactor = 0.5f;

	// --- (2) Helper lambdas: accumulated excess Pe(P) and incremental ?Pe ---
	auto Ia = 0.2f * r2; // initial abstraction (mm)  (SCS default)  [Ia = 0.2*S] 
	auto Pe_accum = [&](float P) -> float {
		if (P <= Ia) return 0.0f;
		return (P - Ia) * (P - Ia) / (P + 0.8f * r2); // Pe formula 
		};
	auto Pe_incr = [&](float P_old, float dP) -> float {
		// incremental runoff for an added depth dP on top of previous cumulative P_old
		float P_new = P_old + dP;
		return Pe_accum(P_new) - Pe_accum(P_old);
		};

	// --- (3) Compute runoff from rainfall first (if any) ---
	float Q_runoff = 0.0f;    // (mm) for this day
	float P_cum = 0.0f;    // (mm) cumulative "effective" depth passed through SCS so far

	if (precipday > 0.0f) {
		Q_runoff += Pe_incr(P_cum, precipday);
		P_cum += precipday;
	}

	// --- (4) Add irrigation according to method ---
	if (irri_flag == 1) {
		if (IrriMethod <= 2) {
			// surface-applied irrigation contributes to potential runoff
			float Irri_mm = IrriWater * 1000.0f; // IrriWater is in meters ? mm
			if (Irri_mm > 0.0f) {
				Q_runoff += Pe_incr(P_cum, Irri_mm);
				P_cum += Irri_mm;
			}
		}
		else if (IrriMethod == 3) {
			// subsurface drip: no direct surface runoff via SCS (do nothing here)
			// it will affect soil moisture/AMC for subsequent days in your soil module
		}
	}

	// Apply litter/residue reduction
	Q_runoff *= litterFactor;

	// --- (5) Store/accumulate runoff safely ---
	scs_runoff += Q_runoff;  // mm for this timestep/day
}
*/

//revised by dengjia 2008/10/28
void class_model::MUSLE(float PEAKR, float MSAND, float MCLAY, float MSILT, float ORGC, float MUSLEC, float sslope,float length, float USLE_P, float ROCK, float ha)
{

	float kusle,cusle,lsusle,crock,pusle;
    kusle=USLE_K(MSAND,MCLAY,MSILT,ORGC);
	//the USLE soil erodibility factor (0.013 metric ton m2*hr/(m3-metric ton cm))
	//cusle=USLE_C(C,COV);//the usle cover and management factor
	cusle=MUSLEC;
	lsusle=USLE_LS(sslope,length);//the usle topographic factor
	crock=exp(-0.053*ROCK);//the coarse fragment factor 
	pusle=USLE_P;//usle support practice factor
//	sedyld=11.8*pow(scs_runoff*PEAKR,0.56)*kusle*cusle*lsusle*crock*pusle;

	sedyld=11.8*pow(scs_runoff*PEAKR*1000.0*(ha/100),.56)*kusle*cusle*lsusle*crock*pusle;
	
	
}

float class_model::USLE_K(float MSAND,float MCLAY,float MSILT,float ORGC)
{
	float fcsand,fclsi,forgc,fhisand,usle_k;
	fcsand=0.2+0.3*exp(-0.256*MSAND*(1-MSILT/100));
	fclsi=powf(MSILT/(MCLAY+MSILT),0.3);
	forgc=1-0.25*ORGC/(ORGC+exp(3.72-2.95*ORGC));
	fhisand=1-0.7*(1-MSAND/100)/((1-MSAND/100)+exp(-5.51+22.9*(1-MSAND/100)));
	usle_k=fcsand*fclsi*forgc*fhisand;
	if(usle_k<0) usle_k=0;
    if(usle_k>1) usle_k=1;
	usle_k=0.4;
	return usle_k;
}

float class_model::USLE_LS(float sslope,float length)
{
	float slp;
	float usle_ls;
	float m=0.6*(1-exp(-35.835*tan(sslope/180.0*3.1416)));
	usle_ls=powf(length/22.1,m)*(65.41*sin(sslope/180*3.1416)*sin(sslope/180*3.1416)+4.56*sin(sslope/180*3.1416)+0.065);
	return usle_ls;
	
}
//revised by dengjia to calculate the peakrunoff in hru level 2008/10/29
float class_model::PEAKRUNOFF(float a15,float ch_l,float ch_n,float ch_s,
				 float slsubbsn,float ManningRoughOverflow,float sub_slp,float ha)
{
	float tconc;//the time of concentration for a subbasin
	float altc;
	float peakr;
	float t_ch = 0;//the time of concentration for channel flow 
	float t_ov=0;//the time of concentration for overland flow

	if(ch_l>0)
    t_ch = 0.62 * ch_l * (ha/100/sub_km)*powf(ch_n,0.75 )/(powf(ha/100,0.125)*powf(ch_s,0.375));
	else
    t_ch=0;

    t_ov = .0556 * powf((slsubbsn*ManningRoughOverflow), 0.6 )/ powf(sub_slp,0.3);
    tconc = t_ov + t_ch;
    altc = 1. - exp(2. * tconc *log(1. - a15));
    peakr = altc * scs_runoff / tconc;           // mm/h
    peakr = peakr * ha/100 / 3.6;           // m^3/s
    
    return peakr;

}

float class_model::alph(float precipday,float rain_yrs,float adj_pkr,int mon,float *rain_hhsm,int *pcpd,float *pcp_stat)
{    
     float  ab = 0.02083;    
     float  ajp = 0.;
     ajp = 1. - exp(-125. / (precipday + 5.));

     float x1 = 0.;
     float x2 = 0.;
     float x3 = 0.;
	 float ran=0;
	 float amp_ave[12];
	 float amp;
     
     float amp_r[12];
	

  //   srand(unsigned(time(NULL))); //canceled by dengjia for this function is only reasonable in large area


        if (rain_yrs < 1.0) rain_yrs = 10.;
	    x1 = .5 / rain_yrs;
        x2 = x1 / pcpd[mon];
        x3 = rain_hhsm[mon] / log(x2);
        if (pcp_stat[mon] >0.0001) 
          amp_r[mon] = adj_pkr * (1. - exp(x3 / pcp_stat[mon]));
        else
          amp_r[mon] = 0.95;
        if (amp_r[mon] < .1) amp_r[mon] = .1;
        if (amp_r[mon] > .95) amp_r[mon] = .95;
		amp=amp_r[mon];

/*		amp_ave[mon]=(amp_r[mon]+ab+ajp)/3;
		ran=(double)rand();
		ran/=(double)RAND_MAX;


		
		if(ran<=(amp_r[mon]-ab)/(ajp-ab))
			amp=amp_r[mon]*(ab+pow(ran*(ajp-ab)*(amp_r[mon]-ab),0.5))/amp_ave[mon];
		else
			amp=amp_r[mon]*(ajp-(ajp-amp_r[mon])*pow((ajp*(1-ran)-ab*(1-ran))/(ajp-amp_r[mon]),0.5))/amp_ave[mon];
*/
		return amp;

}

/*float class_model::USLE_C(float C,float COV)
{
	float cmin;
	float usle_c;
	cmin=1.463*log(C)+0.1034;
	usle_c=exp((log(0.8)-log(cmin))*exp(-0.00115*COV)+log(cmin));
	return usle_c;
}*/


/*void class_model::read_in_sitemusle()
{
    char site_file[80];
    FILE *fp;

    sprintf(site_file, "%s\\Inputs\\SITE_MUSLE", OUTPUT);
    fp = fopen(site_file, "r");
    if ( fp == NULL )
	{
		printf("File %s not found", site_file);
		exit(0);
	}
 
    fscanf(fp, "%d %f %f %f %f %f %f %f %f %f %f", &CN2, &length,
	   &ch_l, &ch_n, &ch_s,&slsubbsn,&ManningRoughOverflow,&sub_slp,&sub_km,&C,&USLE_P);

    fclose( fp );


}*/

/*void class_model::read_in_soilmusle()
{
  char soil_file[80];
    FILE *fps;

    sprintf(soil_file, "%s\\Inputs\\soilmusle", OUTPUT);
    fps = fopen(soil_file, "r");
    if ( fps == NULL )
	{
		printf("File %s not found", soil_file);
		exit(0);
	}
 
    fscanf(fps, "%f %f %f %f %f %f %f %f %f %f %f %f", &sslope, &sol_sumfc,
	   &sol_sw, &wiltsw, &sw,&sol_ice,&MS,&MC,&MSILT,&ORGC,&ROCK,&sno);

    fclose( fps );  
}*/
/*void class_model::read_in_climmusle()
{
    char clim_file[80];
    FILE *fpc;

    sprintf(clim_file, "%s\\Inputs\\climmusle", OUTPUT);
    fpc = fopen(clim_file, "r");
    if ( fpc == NULL )
	{
		printf("File %s not found", clim_file);
		exit(0);
	}
	fscanf(fpc,"%d %f",&rain_yrs,&adj_pkr);
	for(int i=1;i<=12;i++)
	{
		fscanf(fpc,"%d",&pcpd[i]);
	}
	
	for(int j=1;j<=12;j++)
	{
		fscanf(fpc,"%f",&rain_hhsm[j]);
	}
    for(int k=1;k<=12;k++)
	{
		fscanf(fpc,"%f",&pcp_stat[k]);
	}
   fscanf(fpc,"%f",&precipday);
   fclose( fpc );
}*/

//#endif