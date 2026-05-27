#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "math.h"

#ifdef MANURE 
extern class_manure MData;

#ifdef VOC

void VOC_EMSN(int FEED,float &DM, int NSTR, float SILDAT[6][5], int SILTYP, char *F_CLIMD, int year, int FeedMixer,
			  float *AnimalHeads, float *FeedRates);
float CDMOD(float DM, int voc, float PERM,float DENSD,float TEMP,float THICK,float TIME,int TYP,float WSPD);
void TAN_ROOTS(float L,float *BETA,int S,int E,float TOL);

void class_manure::VOCs(char *F_CLIMD, int year, float *AnimalHeads, float *FeedRates)
{
	//Silage data
	float dm;//Silage DM content, fraction
	float SILDAT[6][5]={0.0,0.0};
	int SILTYP, FEEDTYPE, SiloNumber, FeedMixer;

	CString SilF;
	FILE* silf;
	SilF.Format("%s\\Silage", INTER);
	silf = fopen(SilF, "r");
	if(silf==NULL) note(0, SilF);
	fscanf(silf, "%d", &SILTYP);//1)stave tower, 2)sealed tower, 3)bunker, 4)bag, 5)bale 
	fscanf(silf, "%d", &SiloNumber);//Silo number 1) HQ silo 1, 2) HQ silo 2, 3)LQ silo 1, 4) LQ silo 2
	fscanf(silf, "%d", &FEEDTYPE);//1)corn, 2)small grain, 3)alfalfa, 4)grass, 5)HMC
	fscanf(silf, "%d", &FeedMixer);
	fscanf(silf, "%f %f %f %f", &SILDAT[SILTYP][1], &SILDAT[SILTYP][2], &SILDAT[SILTYP][3], &SILDAT[SILTYP][4]);
	//m_BunckLength, m_Diameter, m_Height, m_SilageAmount
	fscanf(silf, "%f", &dm); 
	fclose(silf);
	
	VOC_EMSN(FEEDTYPE, dm, SiloNumber, SILDAT, SILTYP, F_CLIMD, year, FeedMixer, AnimalHeads, FeedRates);
}

void VOC_EMSN(int FEED,float &DM, int NSTR, float SILDAT[6][5], int SILTYP, char *F_CLIMD, int year, int FeedMixer,
			  float *AnimalHeads, float *FeedRates)
{/* 
	PREDICTS SILAGE VOC EMISSIONS FROM THE SILO FACE, FEED MIXER AND FEED BUNK

   CCN   = Concentration of remaining VOC, fraction of DM
   CFCLTY= Housing 1)drylot, 3)tie stall, 4)open freestall, 5)closed freestall
   CSAF  = Exposed area on silo face, m2
   DENS  = Silage wet density, kg/m3
   DF    = Depth of silage removed from silo each day, m
   DENSD = Silage dry matter density, kg/m3
   DM    = Silage DM content, fraction
   FEMIT = Fraction of remaining compound mass emitted each day
   FEED  = Type of silage 1)corn, 2)small grain, 3)alfalfa, 4)grass, 5)HMC
   FDRTE = Silage feeding rate, kg DM/day
   IVOC  = Initial concentration of VOC in silage, fraction of DM
   NSTR  = Silo number 1) HQ silo 1, 2) HQ silo 2, 3)LQ silo 1, 4) LQ silo 2
   PERM  = Gas phase permeability, m2
   SILDAT(I,J) SILO INFORMATION [I = Feed type; J = Information type:
           1) bunker length, 2) silo diameter or width, m, 3)silo height, m
           4) amount of silage, tonne DM]
   SILTYP= Silo type 1)stave tower, 2)sealed tower, 3)bunker, 4)bag, 5)bale 
   THIK  = Total silage layer thickness, m
   TIME  = Duration of emission, s
   TMP   = Mean daily temperature of ambient air, C
   WSPD  = Wind speed (any direction), m/s
   WTHR  = Daily weather 3)mean ambient temperature, 7)wind velocity
   VOCEMSN= Daily emission from 1)silo face, 2)feed mixer, 3)feed bunk, 6)total
   VOCEMIT= Daily emission of each VOC group from each silage feeding phase

  
      INCLUDE 'MANURE.BLK'
      INCLUDE 'GENERAL.BLK'
      INCLUDE 'STRG.BLK'
      INCLUDE 'ANMLCST.BLK'
      INCLUDE 'FDCOW.BLK'
*/	  

	//Following variables included in the  "include" files seem public 
		 
	//Data are needed for the variables as follows:	//////////////////////////////////////////////////	

	//SILTYP=;//Silo type 1)stave tower, 2)sealed tower, 3)bunker, 4)bag, 5)bale

	//SILDAT[6][5]=;//SILDAT(I,J) SILO INFORMATION [I = Feed type; J = Information type:
           //1) bunker length, 2) silo diameter or width, m, 3)silo height, m
           //4) amount of silage, tonne DM]	

		float WTHR[367][8]={0.0};//Daily weather 3)mean ambient temperature, 7)wind velocity
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		float HIGT=0.0;//from input data
		float DIAM=0.0;//from input data
		float DENS=0.0;//self-calculated; Silage wet density, kg/m3			

		float VOCEMIT[367][4][4]={0.0}; //results: VOCEMIT[jday][silage feeding phase][type of voc]

		float VOCEMSN[367][7]={0.0};//results: Daily emission from 1)silo face, 2)feed mixer, 3)feed bunk, 6)total			
		
		float CSAF=0.0;//self-calculated; Exposed area on silo face, m2
		
		float WDTH = 0.0;//from input data
		
		float FDRTE = 0.0;//self-calculated; FeedRates[1]+FeedRates[2]+FeedRates[3];//Silage feeding rate, kg DM/day

		float DF = 0.0;//self-calculated; Depth of silage removed from silo each day, m

		int FMHL = 1;//FeedMixer;//from input data

		float XLCOWS = (AnimalHeads[1]+AnimalHeads[2]);//from input data
		float XOHEIF = AnimalHeads[3];//from input data
		float XYHEIF = 0.0;//?

		int CFCLTY=5;//Housing 1)drylot, 3)tie stall, 4)open freestall, 5)closed freestall

		// ~ ~ ~ ~ ~ ~ ~ ~ ~ End ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~



//  VARIABLES
	  int FFD=0;
	  int i=0, JDAY=0;
      float FEMIT,CCN[4];
	  float IVOC[4][6];//[4]-- 1)alcohols, 2)alkenes, 3)aldenydes; [6]--1)corn, 2)small grain, 3)alfalfa, 4)grass, 5)high-moisture corn, 
      float DA,DW,DENSD,THIK,WSPD,TMP,TIME,LNTH;
      
	  float PERM = 5.0E-9;
  
	//INITIAL CONCENTRATION OF VOC GROUPS IN VARIOUS TYPES OF SILAGE
    //CONCENTRATIONS SHOULD BE THE SUM OF ALL COMPOUNDS WITHIN GROUP

//	ALCOHOLS - VALUES ARE SUM OF MEDIAN CONCENTRATIONS FROM LITERATURE
//  COMPILATION (ONLY 1 STUDY FOR SOME) (SMALL GRAIN FROM SINGLE STUDY WITH WHEAT)

      IVOC[1][1]=0.01; 
	  IVOC[1][2]=0.007;
	  IVOC[1][3]=0.006;
	  IVOC[1][4]=0.01;
	  IVOC[1][5]=0.004;

// ALKENES - CONCENTRATIONS SET EQUAL TO THOSE FOR ALDEHYDES
	  IVOC[2][1]=0.0006; 
	  IVOC[2][2]=0.0006;
	  IVOC[2][3]=0.0006;
	  IVOC[2][4]=0.0005;
	  IVOC[2][5]=0.0006;
//  ALDEHYDES - VALUES ARE SUM OF MEDIAN CONCENTRATIONS FROM LITERATURE
//  COMPLIATION FOR CORN AND GRASS ONLY; 2 STUDIES (1 FOR CORN, 2 FOR GRASS)
      IVOC[3][1]=0.0006; 
	  IVOC[3][2]=0.0006;
	  IVOC[3][3]=0.0006;
	  IVOC[3][4]=0.0005;
	  IVOC[3][5]=0.0006;

//  SET SILO CHARACTERISTICS FOR 5 FEEDS
	  FFD=SILTYP;		//Type of silage 1)corn, 2)small grain, 3)alfalfa, 4)grass, 5)HMC	// Added by ZZX
      //if(FEED==1) FFD = 5;//1)corn
      //if(FEED==3) FFD = 1;//3)alfalfa

      if(SILTYP==1) //Silo type 1)stave tower, 2)sealed tower, 3)bunker, 4)bag, 5)bale 
	  {
//      TOP UNLOADING STAVE TOWER SILO
        DIAM = SILDAT[FFD][2]; //diameter, m
        HIGT = SILDAT[FFD][3]; // hight, m
        DENS = (100.8*log(HIGT) - 23.1)/0.38; //Silage wet density, kg/m3
        CSAF = 3.1416*(DIAM/2.)*(DIAM/2.); //Exposed area on silo face, m2
        DM   = 0.38;// dry matter fraction?
	  }
	  else if(SILTYP==2)
	  {   
		//BOTTOM UNLOADING SEALED TOWER SILO
        DIAM = SILDAT[FFD][2];
        HIGT = SILDAT[FFD][3];
        DENS = (100.8*log(HIGT) - 23.1)/0.45;
        CSAF = 3.1416*(DIAM/2.)*(DIAM/2.);
        DM   = 0.45;
	  }
      else if(SILTYP==3) 
	  {	  
		//BUNKER SILO
		LNTH = SILDAT[FFD][1];
        WDTH = SILDAT[FFD][2];
        HIGT = SILDAT[FFD][3];
        DENS = 800.;//240 tons dry matter/cubic m, dry matter density
        CSAF = HIGT*WDTH*0.8;//sattle
        DM   = 0.35;
	  }
      else if (SILTYP==4) 
	  {	  
		//BAGGED SILO
        DIAM = 3.;
        DENS = 200./0.32;
        CSAF = 3.1416*(DIAM/2.)*(DIAM/2.);
        DM   = 0.32;
	  }
      else
	  {
		//BALE SILAGE
        DIAM = 1.5;
        DENS = 200./0.4;
        CSAF = 3.1416*(DIAM/2.)*(DIAM/2.);
        DM   = 0.4;
      }
      if(FEED==2||FEED==3) DENS = 0.85*DENS;
      if(FEED==5) DENS = 2.22*DENS;
      FDRTE  = 1000.*SILDAT[FFD][4]/365.;

//  ANNUAL SIMULATION 
      DF  = (FDRTE/DM)/(DENS*CSAF);//Depth of silage removed from silo each day, m
	  // = [(Silage feeding rate, kg DM/day) / (DM, dry matter fraction)] / [(Silage wet density, kg/m3) * (Exposed area on silo face, m2)]
      
	  for (i=1; i<4; i++) CCN[i] = 0.0;//Concentration of remaining VOC, fraction of DM

	  //daily climate data
	  char Passs[100];
	  sprintf(Passs, "%s\\RECORD\\Site", OUTPUT);

	  char DAYvoc[120];
	  FILE* fvoc;
	  sprintf(DAYvoc, "%s\\Day_VOC_%d.%s", Passs, year, CSV);
	  fvoc = fopen(DAYvoc, "w");
	  if(fvoc==NULL) note(1,DAYvoc);

	  fprintf(fvoc, "VOC emissions from feed phases (kg/day)\n");
	  fprintf(fvoc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s\n", "Day", "Silage", "Silage", "Silage","FeedMix", "FeedMix", "FeedMix","FeedBunk", "FeedBunk", "FeedBunk","O3 potential","O3 potential","O3 potential","O3 potential","O3 potential","O3 potential","O3 potential");
	  fprintf(fvoc, "%-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s, %-10s\n", "   ", "Alcohols", "Alkenes", "Aldehydes","Alcohols", "Alkenes", "Aldehydes","Alcohols", "Alkenes", "Aldehydes","Alcohols", "Alkenes", "Aldehydes","Silage","Mixer","Bunker","Total");

	  int junkd;
	  float air_temp, max_temp, min_temp, precipitation, PAR, Day_Hrs, wind_speed, humidity;
	  FILE* fday;
	  fday = fopen(F_CLIMD, "r");
	  if(fday==NULL) note(0, F_CLIMD);
	
      for (JDAY=1;JDAY<=365;JDAY++)
	  {

		  fscanf(fday, "%d %f %f %f %f %f %f %f %f", &junkd, &air_temp, &max_temp, &min_temp, &precipitation, &PAR, &Day_Hrs, &wind_speed, &humidity);

        
		  WTHR[JDAY][3] = 21.65;//air_temp;
		  WTHR[JDAY][7] = wind_speed;
		  
		  TMP = WTHR[JDAY][3]; // mean ambient temperature; WTHR  = Daily weather 3)mean ambient temperature, 7)wind velocity

//      SILO FACE
        TIME = 24.*3600.;//seconds

//      SEALED TOWER SILO, OPEN FOR FEEDOUT 2 HOUR PER DAY
        if(SILTYP==2) TIME = 2.*3600.;

        WSPD = 0.7*WTHR[JDAY][7];			//wind velocity

//       TOWER SILO OR BALE SILAGE, EXPOSED WIND SPEED VERY LOW
        if(SILTYP<=2||SILTYP==5) WSPD = 0.01;
        THIK = DF; //Depth of silage removed from silo each day, m

        DENSD = DM*DENS; //dry matter density

		fprintf(fvoc, "%10d, ", JDAY);

        for (i=1; i<=3; i++)//calculate fluxes of 4 VOCs
		{
          CCN[i] = IVOC[i][FEED];//IVOC  = Initial concentration of VOC in silage, fraction of DM

          FEMIT = CDMOD(DM,i,PERM,DENSD,TMP,THIK,TIME,1,WSPD);
          
		  VOCEMIT[JDAY][1][i] += CCN[i]*FDRTE*FEMIT;// kg DM/day, VOCEMIT[jday][silage][type of voc]
          
		  CCN[i] *= (1.0 - FEMIT);

		  fprintf(fvoc, "%10.2f, ", VOCEMIT[JDAY][1][i]);
			  
        }
        
//      FEED MIXING
        //if(FMHL >= 2) 
		{
	//         FEED MIXER IS USED; MIXING TIME A FUNTION OF HERD SIZE
			  TIME = 3600.*(2.0*(XLCOWS+XOHEIF+XYHEIF)+250.)/FDRTE;
			  WSPD = 0.5*WTHR[JDAY][7];
			  THIK = 1.5;
			  DENSD= 100.;
			  for(int i=1;i<=3;i++)
			  {
				FEMIT = CDMOD(DM,i,PERM,DENSD,TMP,THIK,TIME,2,WSPD);
				VOCEMIT[JDAY][2][i] += CCN[i]*FDRTE*FEMIT;// VOCEMIT[jday][feed mixing][type of voc]
				CCN[i] = CCN[i]*(1.-FEMIT);	
				
				fprintf(fvoc, "%10.2f, ", VOCEMIT[JDAY][2][i]);
			  }

		}
		/*else
		{
			for(int i=1;i<=3;i++)
			{
				fprintf(fvoc, "%10.2f, ", 0.0);
			}
		}*/


//       FEED BUNK
        TIME = 24.*3600.;
        WSPD = 0.5*WTHR[JDAY][7];
        if (CFCLTY==3||CFCLTY>5) 
		{
//         TUNNEL VENTILATED BARN, AIR SPEED FUNCTION OF TEMPERATURE
          WSPD = 1.7 + 0.076*TMP;
		  if (WSPD<0.2) WSPD=0.2;
		  WSPD = 0.5*WSPD;
		  

		}

        THIK  = 0.15;
        DENSD = 100.;
		for(int i=1;i<=3;i++)
		{
            FEMIT = CDMOD(DM,i,PERM,DENSD,TMP,THIK,TIME,3,WSPD);//!!!!
            VOCEMIT[JDAY][3][i] += CCN[i]*FDRTE*FEMIT/2.0;// VOCEMIT[jday][feed bunk][type of voc]
	  
			fprintf(fvoc, "%10.2f, ", VOCEMIT[JDAY][3][i]);
		} 


		//fprintf(fvoc, "\n");

//  TOTAL FARM OZONE FORMATION POTENTIAL (EQUAL BENEFIT INCREMENTAL 
//  REACTIVITY [EBIR] [g O3/g VOC] FROM CARTER [2009, ])
        VOCEMSN[JDAY][1] = 0.57*VOCEMIT[JDAY][1][1] + 3.1*VOCEMIT[JDAY][1][2]
                         + 1.6*VOCEMIT[JDAY][1][3];//silage phase
        VOCEMSN[JDAY][2] = 0.57*VOCEMIT[JDAY][2][1] + 3.1*VOCEMIT[JDAY][2][2]
                         + 1.6*VOCEMIT[JDAY][2][3];//mixer phase
        VOCEMSN[JDAY][3]= 0.57*VOCEMIT[JDAY][3][1] + 3.1*VOCEMIT[JDAY][3][2]
                         + 1.6*VOCEMIT[JDAY][3][3];//bunker phase
        VOCEMSN[JDAY][6] = VOCEMSN[JDAY][1] +VOCEMSN[JDAY][2]
                         + VOCEMSN[JDAY][3];

		float O3_1 = 0.57*VOCEMIT[JDAY][1][1] + 0.57*VOCEMIT[JDAY][2][1] + 0.57*VOCEMIT[JDAY][3][1];
		float O3_2 = 3.1*VOCEMIT[JDAY][1][2] + 3.1*VOCEMIT[JDAY][2][2] + 3.1*VOCEMIT[JDAY][3][3];
		float O3_3 = 1.6*VOCEMIT[JDAY][1][3] + 1.6*VOCEMIT[JDAY][2][3] + 1.6*VOCEMIT[JDAY][3][3];

		fprintf(fvoc, "%10.2f, %10.2f, %10.2f, %10.2f,%10.2f, %10.2f, %10.2f,\n", 
			O3_1, O3_2,O3_3, VOCEMSN[JDAY][1], VOCEMSN[JDAY][2], VOCEMSN[JDAY][3], VOCEMSN[JDAY][6]);
   
		//fprintf(fvoc, "\n");
	 }// End of 365

	 fclose(fday);
	 fclose(fvoc);
     
}

float CDMOD(float DM, int voc, float PERM,float DENSD,float TEMP,
		  float THICK,float TIME,int TYP,float WSPD)
{
/* CALCULATES CUMULATIVE EMISSION FROM A LAYER OF FEED

   ALPHA  = Effective mass transfer coefficient (Crank's model), m/s
   BETA   = Roots of btanb (Crank's model)
   DW     = Diffusion coefficient in clear water, m2/s
   DM     = Silage dry matter content, kg/kg
   DSS    = Diffusion coefficient in silage solution, m2/s
   FEMIT  = Fraction of initial compound mass loss via emission
   ESG    = Gas-phase diffusion-dispersion coefficient in silage, m2/s
   D      = Effective diffusion coefficient in silage (Crank's model), m2/s
   HCOEF  = Henry's law constant coefficients for determining KH
   KH     = Henry's law constant, mol/kg-atm
   HI     = Henry's law constant, mol/kgw / mol/m3 = m3/kg
   HM     = Mass transfer coefficient, m/s
   PERM   = Gas-phase permeability in silage, m2
   PORAQ  = Aqueous porosity in silage, m3/m3
   PORG   = Gas-phase porosity in silage, m3/m3
   PORT   = Total porosity in silage, m3/m3
   RrR      = Universal gas constant, m3 atm/K-mol
   DENSD  = Silage dry matter density, kg/m3
   DENSH2O= Water density, kg/m3
   DENSP  = Silage particle density, kg/m3
   DENSW  = Silage wet density, kg/m3
   TEMP   = Silage and air temperature (assumed to be equal), degrees C
   TEMPK  = Silage and air temperature (assumed to be equal), K
   THICK  = Thickness of emitting layer, m
   TIME   = Time silage layer is exposed during single feeding cycle, s
   TSUM   = An intermediate calculation in Crank's model
   TYP    = Type of silage, 1 for packed silage (determines whether 
            porosity or permeability is used for ESG)
   WC     = Silage water content, kg/kg
   WSPD   = Surface wind speed, m/s
*/

	float FEMIT=0.0;

// INPUT VARIABLES
      float DW,DSS,TEM;
      float HCOEF[4][3]={0.0, 0.0};


//  CALCULATED VARIABLES
      float ALPHA,D,ESG,HI,HM,KH,PORAQ,PORG,PORT,DENSH2O,DENSW,TEMPK,TSUM,WC;
      float BETA[101]={0.0, 0.0};
      
//  MODEL CONSTANTS
      float DENSP=1500;
	  float RrR=8.2057E-5;

//  FUNCTION VARIABLES
     float L;

//  HENRY'S LAW CONSTANT PARAMETERS
//     HIGH SOLUBILITY ALCOHOLS (ETHANOL) (FROM WARNECK [2006, ATMOS. ENV. 40: 7146¨C7151])
		HCOEF[1][1]=-15.78;
		HCOEF[1][2]=6248.; 
//     ALKENES (2-BUTENE, MEAN OF Z- AND E- FROM SANDER [2008] AND CONVERTED)
      HCOEF[2][1]=-5.424;
	  HCOEF[2][2]=0.0;
//     ALDEHYDES (ACETALDEHYDE, FROM STAUDINGER & ROBERTS [2001, CHEMOSPHERE 44: 561-576])
      HCOEF[3][1]=-16.38;
	  HCOEF[3][2]=5663.;

//  MODEL CONSTANTS
      DW = 1.E-9;
      TEMPK = TEMP + 273.15;
      KH = (float)exp(HCOEF[voc][1] + HCOEF[voc][2]/TEMPK);
      HI = KH*RrR*TEMPK;

//  CALCULATE POROSITIES
      DENSH2O = 999.887 + 4.8915899E-2*TEMP - 7.40977565E-3*pow(TEMP,2) 
				+ 3.998247E-05*pow(TEMP,3) - 1.23288498E-7*pow(TEMP,4);   // orignal code is wrong. ZZX

      WC    = 1. - DM;
      DENSW = DENSD/DM;
      PORT  = 1. - DENSD/DENSP;
      PORAQ = WC*DENSW/DENSH2O;
      PORG  = PORT - PORAQ;
	  if (PORG<0.0) PORG=0.0;


// TRANSPORT PARAMETERS
      HM = 0.01302*pow(WSPD,0.7931);
      if(TYP==1)		ESG = 0.0002437*pow(WSPD,0.9367)*pow(PORG,1.720);
      else if (TYP==2)	ESG = 0.0; // Not used in calculation
      else				ESG = 2.654E25*pow(WSPD,1.102)*pow(PERM,3.644); 

      DSS = DW*pow(PORAQ,(11./3.))/pow(PORT,3.0667);
      D   = DSS*DENSH2O/(DENSW*WC + PORG/HI) + ESG/(HI*DENSW*WC + PORG);
      ALPHA = HM/(HI*DENSW*WC + PORG);

// CUMULATION EMISSION
      if(TYP==1||TYP==3) 
	  {
			 L = THICK*ALPHA/D;
	//       FIRST CALL USES SINGLE ROOT
			TAN_ROOTS(L,BETA,1,1,1.01);//!!!!
			TSUM = 2*L*L*exp(-pow(BETA[1],2)* D*TIME/pow(THICK,2)) /
					(pow(BETA[1],2)*(pow(BETA[1],2) + L*L + L));	  
		  
			if (TSUM > 0.5 ) 
			{
			
	//         MORE ROOTS USED AS NEEDED TO GIVE LESS THAN 1% ERROR IN EMISSION.
	//         BELOW FEMIT OF 0.01, ERROR WILL BE LARGER
			   TAN_ROOTS(L,BETA,2,5,1.01);
			   for (int i = 2; i<=5;i++)
				 TSUM = TSUM + 2*L*L*exp(-pow(BETA[i],2) * D*TIME/pow(THICK,2)) / 
						(pow(BETA[i],2)*(pow(BETA[i],2) + L*L + L));
			}
			if (TSUM>0.88) 
			{
			  TAN_ROOTS(L,BETA,6,20,1.001);

			  for (int i = 6; i<=20;i++)
				 TSUM = TSUM + 2*L*L*exp(-pow(BETA[i],2) * D*TIME/pow(THICK,2)) / 
						(pow(BETA[i],2)*(pow(BETA[i],2) + L*L + L));

			}
			if (TSUM >0.97) 
			{		
			
			  TAN_ROOTS(L,BETA,21,100,1.0001);

			  for (int i = 21; i<=100;i++)
				 TSUM = TSUM + 2*L*L*exp(-pow(BETA[i],2) * D*TIME/pow(THICK,2)) / 
						(pow(BETA[i],2)*(pow(BETA[i],2) + L*L + L));

			}
			FEMIT = 1.0 - TSUM;
			if (FEMIT<0.001) FEMIT=0.001;
	  }

      else  FEMIT = 1.0 - exp(-ALPHA/THICK*TIME);

	  return(FEMIT);

}


void TAN_ROOTS(float L,float *BETA,int S,int E,float TOL)
{
/*  SOLVES FOR THE S to E VALUES OF B IN B*TAN(B) = L
C
C   I      = Integer for loop
C   S      = Position of first root (start)
C   E      = Position of last root (end)
C   CT     = Counter variable
C   L      = L in B*TAN(B) = L
C   B      = B in B*TAN(B) = L
C   Y      = Iterative guess for L
C   BETA      = Set of roots
*/

//  VARIABLES
      int I,CT;
      float B,Y;
      float PI=3.14159265358979;

// START LOOP FOR 1ST THROUGH 20TH ROOT
     
	 for (I=S;I<=E;I++)
	 {
		int k=0;
        B = PI/4.0;
        CT = 0;
        while (fabs(log10((B + (I-1)*PI)*tan(B)/L)) > log10(TOL))//!!!!
		{
		
          CT = CT + 1;
          if (CT>1)  B = (atan(L/(B + (I-1)*PI)) + B)/2;
          else		 B = atan(L/(B + (I-1)*PI));
          Y = B*tan(B);	
		  k++;
		  //if(k>50) break;
		}

		BETA[I] = B + (I-1)*PI; //RrR[I] ???
	 
	 }


}

#endif
#endif