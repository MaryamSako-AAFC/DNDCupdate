//------------------------------------------------------ 
//The functions to calculate site's information


#include "stdafx.h"
#include <io.h>
#include <direct.h>
#include "RunPaths.h"
#include "SitePara.h"
#include "dndc_main.h"
#include "dndc_tool.h"

extern CropArray			Crop;
extern Site_BaseInformation	IData;
extern StringArray			ClimateFilename;
extern CropofEachYear CYr[2];
//extern DNDCSystem DNDCSys;
float Soca[6]={0.0,0.2,0.2,0.08,0.05,0.2};
float Socb[6]={10.0,2.0,2.0,1.4,4.0,2.0};
int Mday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

char  Crop_Name[100];
float m_GrainCN;
float m_RootCN, m_ShootCN, m_CropWaterDemand, m_OptT, m_CropTDD,m_GrainFill;
float m_CropNfixation, m_Vascularity, m_CropTotalN, TotalHa=0;
int m_PerennialCrop,m_RootShape;

void RecordManureFiles();
void CreateDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, 
							float lat, CString IfCheck, float NO3NH4_Rainfall,float NH3_Atmosphere,
							float BaseCO2, float CO2IncreaseRate, char *LocaName, int YieldYear, 
							int YieldToday, int DMW, char *r_Country);

CString FCT0, FCT100, SF;
int TotalFarmFields;
FILE *sf;

int CreateInputFiles(int DaymetFlag, int UseID, char *r_Country, int DayRecord) 
{

    if (SaveSite(DayRecord)==-1) return -1;
      
    if (RecordClimateFile(1, DaymetFlag, UseID, r_Country) == -1) return -1;
    
	//ReadClimateHead(1);

	if (SetSoilH()==-1) return -1;

    if (SaveSoilParas(1)==-1) return -1;
    
    SaveInterFarmParas();

    if (SaveCropParas()==-1) return -1;

#ifdef MANURE	
	RecordManureFiles();
#endif
	return 0;
}

int ReadClimateHead(int yr)
{
	char fname[255],fn1[256],fn2[256];
	FILE *fpo;
	int  jday;
	float temp,maxT, minT, Rainfall, solrad, Day_Hrs;

	sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,yr);
	fpo=sopen(fname, 1);
	if (fpo==NULL) return -1;
	fscanf(fpo,"%s",fn1);
	fscanf(fpo,"%s",fn2);
	fclose(fpo);

	sprintf(fname,"%s\\Inputs\\%s", OUTPUT,fn1);
	fpo=sopen(fname,1);
	if (fpo==NULL) return -1;
	fscanf(fpo, "%d %f %f %f %f %f %f",
		&jday, &temp, &maxT, &minT, &Rainfall, &solrad, &Day_Hrs);
	IData.Soil_T=temp;
	fclose(fpo);

	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,fn2);
	return GetAMT(fname);
}

//mode=0:Get initial Soil T   mode=1:ReSave climate data for simulation
int RecordClimateFile(int mode, int DaymetFlag, int UseID, char *r_Country)
{
    int i, yn, result=-1, TotalYear, FirstYear;
	float longitute, latitude;

#ifdef GLOBE_CLIM
	IData.ClimateFileType= 4;
#endif

	if(DaymetFlag==1)
	{
		CString DMF;
		FILE *dmf;
		DMF.Format("%s\\Inter\\SiteLocation.txt", OUTPUT);
		dmf=fopen(DMF, "r");
		if(dmf==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DMF);
			AfxMessageBox(note);
			exit(0);
		}

		fscanf(dmf, "%f %f %d %d", &longitute, &latitude, &TotalYear, &FirstYear);
		fclose(dmf);

		IData.ClimateFileType = 3;
	}
	else
	{
	}

    i = ClimateFilename.n;
	yn = IData.years;

    if (mode==1 && i<IData.years && IData.if1File==0) {
        MessageBox(NULL,"No enough Climate data files! Please re-input.","Input Error:",0);
        return result;
    }
	    
    char fname[255],ch[255];//cn[250],
	FILE *fpo;//*fpi, 
    	
    for (i = 1;i<=IData.years;i++) 
	{
		if(DaymetFlag==1)
		{
			sprintf(ch,"%s\\Inter\\daymet%d", OUTPUT, FirstYear+i-1);
		}
		else
		{
			if(IData.if1File==0)
				sprintf(ch,"%s",ClimateFilename.get(i));
			else
				sprintf(ch,"%s",ClimateFilename.get(1));
		}
		
		SaveClimateFileOfAYear(i,ch,IData.latitude,
			IData.ClimateFileType,IData.NO3NH4_Rainfall,
			IData.NH3_Atmosphere,IData.BaseCO2,"Check",mode,
			IData.CO2IncreaseRate, UseID, r_Country);
    }
	result = 0; 

	//delete YrAveT;//free(YrAveT);
	//delete YrRain;//free(YrRain);

    return result;
}


int SaveClimateFileOfAYear(int id,char *ch, 
	float lat, int ClimateFileType, float NO3NH4_Rainfall,
	float NH3_Atmosphere, float BaseCO2, CString IfCheck,int mode, 
	float CO2IncreaseRate, int UseID, char *r_Country)
{
	char fname[356],Pname[356],cn[356];
	FILE *fpo,*fpi;

	sprintf(Pname,"%s",ch);
	sprintf(cn,"%s",ch);

	GetShortFileName(cn);

	//////////////////////////
	char Dname[300], Yname[300], LocationName[300];
	char Dname1[300],Dname2[300],Dname3[300],Yname1[300],Yname2[300],Yname3[300];
	int Site, YieldYear, YieldToday, YieldCrop,YieldMonth, YieldDay;
	if(UseID==10)//drought option
	{
		//////////////////////////////////////////////////////////////////////////
			CString YF;
			FILE* yf;
			YF.Format("%s\\YieldPrediction", INTER);
			yf=fopen(YF, "r");
			if(yf==NULL) note(0,YF);

			fscanf(yf, "%d %d %d %d %s %d %d", &Site, &YieldCrop, &YieldYear, &YieldToday, LocationName,&YieldMonth, &YieldDay);
			fclose(yf);
		///////////////////////////////////////////////////////////////////////////
	
		if(id==1)
		{
			sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,id);
			if ((fpo=sopen(fname,0))==NULL) note(1, fname);
			
			sprintf(Dname,"%s-%d.day",LocationName, id);
			sprintf(Yname,"%s-%d.yr",LocationName, id);	
			fprintf(fpo,"%s\n",Dname);		
			fprintf(fpo,"%s\n",Yname);
			fclose(fpo);
		}
		else
		{
			sprintf(Pname,"%s",LocationName);

			sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,id);
			if ((fpo=sopen(fname,0))==NULL) note(1, fname);		
			sprintf(Dname1,"%s-%d-dry.day",LocationName, id);
			sprintf(Dname2,"%s-%d-mid.day",LocationName, id);
			sprintf(Dname3,"%s-%d-wet.day",LocationName, id);
			sprintf(Yname1,"%s-%d-dry.yr",LocationName, id);
			sprintf(Yname2,"%s-%d-mid.yr",LocationName, id);
			sprintf(Yname3,"%s-%d-wet.yr",LocationName, id);
			fprintf(fpo,"%s %s %s\n",Dname1,Dname2,Dname3);		
			fprintf(fpo,"%s %s %s\n",Yname1,Yname2,Yname3);
			fclose(fpo);
		}
	}
	else
	{
		sprintf(fname,"%s\\Inputs\\clim-%d",OUTPUT,id);
		if ((fpo=sopen(fname,0))==NULL) note(1, fname);
		
		sprintf(Dname,"%s-%d.day",cn, id);
		sprintf(Yname,"%s-%d.yr",cn, id);	
		fprintf(fpo,"%s\n",Dname);		
		fprintf(fpo,"%s\n",Yname);
		fclose(fpo);
	}

	//Create daily climate files
	if(UseID==10)//drought option
	{
		if(id==1)
		{
			CreateDailyClimateFile(Pname, Dname, Yname, UseID, ClimateFileType, lat, IfCheck,
				IData.NO3NH4_Rainfall,IData.NH3_Atmosphere,IData.BaseCO2, IData.CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 0, r_Country);
		}
		else
		{
			CreateDailyClimateFile(Pname, Dname1, Yname1, UseID, ClimateFileType, lat, IfCheck,
				IData.NO3NH4_Rainfall,IData.NH3_Atmosphere,IData.BaseCO2, IData.CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 1, r_Country);
			CreateDailyClimateFile(Pname, Dname2, Yname2, UseID, ClimateFileType, lat, IfCheck,
				IData.NO3NH4_Rainfall,IData.NH3_Atmosphere,IData.BaseCO2, IData.CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 2, r_Country);
			CreateDailyClimateFile(Pname, Dname3, Yname3, UseID, ClimateFileType, lat, IfCheck,
				IData.NO3NH4_Rainfall,IData.NH3_Atmosphere,IData.BaseCO2, IData.CO2IncreaseRate,
				LocationName, YieldYear, YieldToday, 3, r_Country);
		}
	}
	else
	{
		CreateDailyClimateFile(Pname, Dname, Yname, UseID, ClimateFileType, lat, IfCheck,
			IData.NO3NH4_Rainfall,IData.NH3_Atmosphere,IData.BaseCO2,IData.CO2IncreaseRate,
			"None", 0, 0, 0, r_Country);
	}
    return -1;
}

void CreateDailyClimateFile(char *Pname, char *Dname, char *Yname, int UseID, int ClimateFileType, float lat,
							CString IfCheck, float NO3NH4_Rainfall,float NH3_Atmosphere,float BaseCO2,
							float CO2IncreaseRate, char *LocaName, int YieldYear, int YieldToday,
							int DMW, char *r_Country)
{
	int tn, j, k;
	float Day_Hrs,temp=0.0,Rainfall=0.0,maxT=0.0,minT=0.0,solrad,wind_speed=2.0;
	float AveMonthT[13],AveYrT, TotalYrRain, humidity=30.0, CloudIndex=1.0;
	int   jday=0,jday0=0,Aday;
	char fname[256],cn[256], cjunk[200], junkcc[300], ch[256];
	char CurrentClim[300], junkc[200];
	
	FILE* fpo, *fpi, *fcc;
	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,Dname);
	fpo=sopen(fname,"w");
	if(fpo==NULL) note(1,fname);
        
	if(UseID==0)
	{
		fpi=sopen(Pname,"r");
		if (fpi==NULL) 
		{
			CString NCF;
			NCF.Format("%s.txt", Pname);
			fpi=fopen(NCF,"r");
			if (fpi==NULL) note(0, Pname);
		}   
		if (ClimateFileType!=4) 
			fscanf(fpi,"%s", cjunk);	// read climate file dataname

		if(strcmp(cjunk, "1")==0)
		{
			fclose(fpi);
			fpi=sopen(Pname,"r");
		} 
	}
	else
	{
		if(DMW==0)//year 1
		{
			sprintf(Pname, "%s\\Database\\%s\\%s\\Lib_clim\\%s_%d", ROOTDIR, r_Country, LocaName, LocaName, YieldYear-1);
		}
		else if(DMW==1)//dry year
		{
			sprintf(Pname, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_dry", ROOTDIR, r_Country, LocaName, LocaName);
		}
		else if(DMW==2)//medium
		{
			sprintf(Pname, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_mid", ROOTDIR, r_Country, LocaName, LocaName);
		}
		else
		{
			sprintf(Pname, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_wet", ROOTDIR, r_Country, LocaName, LocaName);
		}

		fpi=sopen(Pname,"r");
		if (fpi==NULL) note(0, Pname);
		 
		if (ClimateFileType!=4) 
		{
			fscanf(fpi,"%s", cjunk);	// read climate file dataname
			if(strcmp(cjunk, "1")==0)
			{
				fclose(fpi);
				fpi=sopen(Pname,"r");
			} 
		}

		sprintf(CurrentClim, "%s\\Database\\DroughtPrediction\\%s\\%s\\%s_%d", ROOTDIR, r_Country, LocaName, LocaName, YieldYear);
		fcc=fopen(CurrentClim, "r");
		if(fcc==NULL) note(0, CurrentClim);
		fscanf(fcc,"%s", cjunk);
	}    
    
	tn = 0;
    AveYrT = 0.0;
	TotalYrRain = 0.0;

	//default data
	wind_speed = 2.0;//m/s
	humidity = 60.0;//%
	int djunk=0, dflag=0;
	char www[100];

	for (j = 1;j<=12;j++) 
	{
		AveMonthT[j] = 0;
        for (k = 1;k<=Mday[j];k++) 
		{	
			dflag=0;

			if(j==1&&k==1)
			{
				fscanf(fpi,"%d", &djunk);	// read climate file dataname
				if(djunk!=1)
				{
					fgets(www, 300, fpi);
					dflag=0;
				} 
				else
				{
					jday = djunk;
					dflag = 1;
				}
			}

			tn++;
			Day_Hrs = 0.0;

			if(lat<0.0)
			{
				Aday = tn - 182;//for southern semisphere
				if(Aday<=0) Aday = 365 + Aday;

				solrad = day_par(Aday, -lat, &Day_Hrs);
			}
			else
				solrad = day_par(tn, lat, &Day_Hrs);//extre-terrestrial radiation, MJ/m2/day

				float N = Day_Hrs; //calculated maximum possible duration of sunshine or dalight hours (hours)
				float n = 0.58 * N; //actual duration of sunshine (hours)
				float As = 0.25; //refression constant, expressing the fraction of extraterestrial radiation reaching the earth on overcast days (n=0)
		        float Bs = 0.50; //(As+Bs) = refression constant, expressing the fraction of extraterestrial radiation reaching the earth on clear days (n=N)


			if(Day_Hrs<=0.0) Day_Hrs=0.01;

			if (ClimateFileType ==0) //aveT, prec
				{
					if(dflag==1) fscanf(fpi, "%f %f", &temp, &Rainfall);
					else fscanf(fpi, "%d %f %f", &jday, &temp, &Rainfall);
					//fgets(junkcc, 200, fpi);
					maxT = temp + (float)5.3;
					minT = temp - (float)5.3;
					
				}
				else if (ClimateFileType ==1) //maxT, minT, prec
				{
					if(dflag==1) fscanf(fpi, "%f %f %f", &maxT, &minT, &Rainfall);
					else fscanf(fpi, "%d %f %f %f", &jday, &maxT, &minT, &Rainfall);
					
					if(UseID==10&&DMW>0&&YieldToday>=jday)//drought effect
					{
						if(dflag==1) fscanf(fcc, "%f %f %f", &maxT, &minT, &Rainfall);
						else fscanf(fcc, "%d %f %f %f", &jday, &maxT, &minT, &Rainfall);
					}

					//fgets(junkcc, 200, fpi);
					temp = (maxT + minT) * 0.5;
			
					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}
				else if (ClimateFileType ==2) //maxT, minT, prec, radiation
				{	
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &solrad);
					else fscanf(fpi, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &solrad);
					//fgets(junkcc, 200, fpi);
					temp =float( (maxT + minT) *0.5);
					solrad = solrad;// / (As + Bs * n / N); //measured or calculated solar or shortwave radiation (MJ/m2/day)
				}
				else if (ClimateFileType ==3) //maxT, minT, prec, wind speed (m/s)
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &wind_speed);//wind speed, m/second
					else fscanf(fpi, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &wind_speed);//wind speed, m/second
					temp =float( (maxT + minT) *0.5);

					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;

				}
				if(ClimateFileType ==4)
				{					
					int yr_ID, month_ID, day_ID;
					float radiation, ave_T;
					char polygon_ID[100];

					fscanf(fpi, "%s %d %d %d %f %f %f %f %f", 
							polygon_ID, &yr_ID, &month_ID, &day_ID, &radiation, &maxT, &minT, &ave_T, &Rainfall);
					//fgets(junkc, 200, fpi);
					temp =float( (maxT + minT) *0.5);
					Rainfall *= 0.1;
					jday = tn;

					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}
				else if(ClimateFileType==5) //maxT, minT, prec, wind speed, radiation, relative humidity
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f %f %f", &maxT, &minT, &Rainfall, &wind_speed, &solrad, &humidity);
					else fscanf(fpi, "%d %f %f %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &wind_speed, &solrad, &humidity);//wind speed, m/second
					temp =float( (maxT + minT) *0.5);
					solrad = solrad;// / (As + Bs * n / N); //measured or calculated solar or shortwave radiation (MJ/m2/day)
				}
				else if(ClimateFileType==6) //maxT, minT, prec, wind speed, relative humidity
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f %f", &maxT, &minT, &Rainfall, &wind_speed, &humidity);
					else fscanf(fpi, "%d %f %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &wind_speed, &humidity);
					temp =float( (maxT + minT) *0.5);

					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}
				else if(ClimateFileType==7) //maxT, minT, prec, relative humidity
				{
					if(dflag==1) fscanf(fpi, "%f %f %f %f", &maxT, &minT, &Rainfall, &humidity);
					else fscanf(fpi, "%d %f %f %f %f", &jday, &maxT, &minT, &Rainfall, &humidity);

					temp =float( (maxT + minT) *0.5);
					
					CloudIndex = 0.9693 * (float)exp(-1.3903 * Rainfall);
					if(CloudIndex<0.0001) CloudIndex = 0.0001;
					solrad *= CloudIndex;
				}

			if(tn!=jday)
			{
				CString note;
				note.Format("Error at day %d in climate data file %s", tn, Pname);
				AfxMessageBox(note);
				
				//exit(0);//Crashes the model when this happens from misread climate file. Still notifies user
			}

			if (IfCheck=="Check")
			{

			// Check whether or not if Julian day is continous
				if (tn > 1) {
					if (jday0 != jday - 1) {
						sprintf(ch,"Julian day of %dth line of <%s>",tn,fname);
						MessageBox(NULL,ch,"Climate Data Error:",0);
						fclose (fpi); fclose (fpo);
						goto outerr;
					}
				}
					
				// Check if rainfall is bigger than 0
				if (Rainfall < 0.0) {
					sprintf(ch,"Rainfall in %dth line of <%s>",tn,fname);
					MessageBox(NULL,ch,"Climate Data Error:",0);
					fclose (fpi); fclose (fpo);

					goto outerr;
				}
            
				// check if  -50<T<70
				if (temp < -70.0 || temp > 70.0) {
					sprintf(ch,"Temperature in %dth line of <%s>",tn,fname);
					MessageBox(NULL,ch,"Climate Data Error:",0);
					fclose (fpi); fclose (fpo);

					goto outerr;
				}
			}
            jday0 = jday;
			if (tn==1)//(mode==0) 
			{
				IData.Soil_T = temp;
			}

			// Output climate data of 365 days
			
			fprintf(fpo, "%3d %5.2f  %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f\n",
					jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs, wind_speed, humidity);

			//if (ClimateFileType ==3)
			//{
			//	fprintf(fpo, "%3d %5.2f  %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f\n",
			//		jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs, wind_speed);
			//}
			//else
			//{
			//	fprintf(fpo, "%3d %5.2f  %5.2f %5.2f %5.2f %5.2f %5.2f\n",
			//		jday, temp, maxT, minT, Rainfall, solrad, Day_Hrs);
			//}
                
            // Calculate the average T and rainfall for month, year
            AveMonthT[j] += temp / Mday[j];
            AveYrT += (temp / 365.0);
            TotalYrRain += Rainfall;
		}
	}
    fclose (fpi);
    fclose (fpo);
	if(DMW>0) fclose (fcc);

	sprintf(fname,"%s\\Inputs\\%s",OUTPUT,Yname);
	fpo=sopen(fname,"w");
	if (fpo==NULL) note(1, fname);
    for (j=1;j<=12;j++) 
	{
		fprintf(fpo,"%.2f	", AveMonthT[j]);
	}
    fprintf(fpo,"\n%.2f\n", AveYrT);
    fprintf(fpo,"%.2f\n", TotalYrRain);
    fprintf(fpo,"%.3f\n", NO3NH4_Rainfall);//IData.
    fprintf(fpo,"%.2f\n", NH3_Atmosphere);//IData.
	fprintf(fpo,"%.2f\n", BaseCO2);//IData.
	fprintf(fpo,"%.2f\n", CO2IncreaseRate);
	fprintf(fpo,"%d\n", ClimateFileType);
    fclose (fpo);
	
outerr:;
    
}

int GetAMT(char *fname)
{
	int j;
	float dt;
	FILE *fp;
	fp=sopen(fname,1);
	if (fp==NULL) return -1;
	for (j=1;j<=12;j++) {
		fscanf(fp,"%f", &dt);
	}
    fscanf(fp,"%f", &dt);
	fclose(fp);
	IData.AnnualMeanT = dt;
	return 0;
}

int ReadSoilFeature(CString mode)
{
    int result = -1;
	FILE *fpi;
    char fname[255],nnote[255];
	
	float DClay, DFldcap, DWiltpt, DSks, DPorosity;
    
	if (IData.Soil_Texture<1 && IData.Soil_Texture>13) return result;
	
#ifdef CONSOLE
	sprintf(fname, "%s\\lib_soil\\soil_%d", LIBRARY, IData.Soil_Texture); 
#else
	sprintf(fname, "%s\\Library\\lib_soil\\soil_%d", ROOTDIR, IData.Soil_Texture);
#endif	
	if(IData.Soil_Texture<=0)
	{
		sprintf(IData.SoilName, "None");
		DClay = 0.0;
		DPorosity = 0.0;
		DSks = 0.0;
		DFldcap = 0.0;
		DWiltpt = 0.0;
	}
	else
	{
		fpi=sopen(fname, "r");
		if(fpi==NULL) note(0, fname);
		
		fscanf(fpi,"%s %s", IData.SoilName,nnote);//IData.NameNote);
		fscanf(fpi,"%f %s", &DClay,nnote);
		fscanf(fpi,"%f %s", &DPorosity, nnote);//IData.StsNote);
		fscanf(fpi,"%f %s", &DSks, nnote);//IData.SksNote);
		fscanf(fpi,"%f %s", &DFldcap, nnote);//IData.FldcapNote);
		fscanf(fpi,"%f %s", &DWiltpt, nnote);//IData.WiltptNote);
		//fscanf(fpi,"%f %s", &IData.Soilhtcp, note);//IData.SoilhtcpNote);
		//fscanf(fpi,"%f %s", &IData.Psisat, note);//IData.PsisatNote);
		//fscanf(fpi,"%f %s", &IData.Beta, note);//IData.BetaNote);
		fclose (fpi);   
	}
	
	//insert saxton pedotransfer function to recalculate sat conductivity
	float  sandFraction, soilOM, surfaceSOC, newFC, newWP;
	float clay[2] = { 0.0, IData.Soil_Clay };
	float sandContent[13] = { 0.0,0.85,0.80,0.63,0.15,0.41,0.53,0.09,0.29,0.52,0.08,0.13,0.15 };
	if (IData.Soil_Texture <= 12) { sandFraction = sandContent[IData.Soil_Texture]; }
	else
	{
		sandFraction = 0.15;
	}
	soilOM = IData.Soil_OCatSurface * 100 * 1.72; //calculate OM%

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
	

	







	DSks *= 0.6;//cm/min ->m/hr
    if(DSks<0.015) DSks=0.015;//default sks 0.015 was 0.008
	//if (DSks < 0.015) DSks = 0.015;
	if(IData.Soil_Clay==0.0) IData.Soil_Clay = DClay;
	if(IData.Fldcap==0.0) IData.Fldcap = DFldcap;
	if(IData.Wiltpt==0.0) IData.Wiltpt = DWiltpt;
	if(IData.Sks==0.0) IData.Sks = DSks;
	if(IData.Soil_Porosity==0.0) IData.Soil_Porosity = DPorosity;
	/*
	float checkPorosity; 
	checkPorosity = 1 - IData.Soil_Density / 2.65;
	if (IData.Soil_Porosity > checkPorosity * 1.05 || IData.Soil_Porosity < checkPorosity * 0.95)
	{
		MessageBox(NULL, "Check Soil Porosity based on Bulk Density ", "Porosity", checkPorosity);
		return -1;
	}
	*/
	if (mode=="Default")
	{
		IData.Soil_Clay=DClay;
		IData.Fldcap=DFldcap;
		IData.Wiltpt=DWiltpt;
		IData.Sks=DSks;
		IData.Soil_Porosity=DPorosity;
	}

    result = 1;
	return result;
}

void SetCropCN(CropParameter *cp)
{
    cp->YieldC = (float)(cp->Yield);
    
	//if(cp->CropCode==4||cp->CropCode==5||cp->CropCode==10||cp->CropCode==11||cp->CropCode==12||cp->CropCode==22||cp->CropCode==32)
	//    cp->PlantC = cp->YieldC / cp->Straw;
	//else
		cp->PlantC = cp->YieldC / cp->Grain;

    if (cp->RCNPlan == 0) {
		MessageBox(NULL,"Crop C/N ratio is 0!", "System file error:",0);
        return;
    }
    cp->MaxPlantN = cp->PlantC / cp->RCNPlan;


/*        //Dry weight --> C partition
    Crop.get(rrr,yyy,NowC.crop)->YieldC = (float)(Crop.get(rrr,yyy,NowC.crop)->Yield * 0.4);
    if (Crop.get(rrr,yyy,NowC.crop)->Grain > 0) 
        Crop.get(rrr,yyy,NowC.crop)->PlantC = Crop.get(rrr,yyy,NowC.crop)->YieldC / Crop.get(rrr,yyy,NowC.crop)->Grain;
	else {
		if (Crop.get(rrr,yyy,NowC.crop)->Straw == 0) {
            MessageBox(NULL,"Crop base file error ! (Straw=0) ", "System file error:",0);
            return;
        }
        Crop.get(rrr,yyy,NowC.crop)->PlantC = Crop.get(rrr,yyy,NowC.crop)->YieldC / Crop.get(rrr,yyy,NowC.crop)->Straw;
    }
    if (Crop.get(rrr,yyy,NowC.crop)->RCNPlan == 0) {
		MessageBox(NULL,"Crop base file error ! (RCNPlan = 0) ", "System file error:",0);
        return;
    }
    Crop.get(rrr,yyy,NowC.crop)->MaxPlantN = Crop.get(rrr,yyy,NowC.crop)->PlantC / Crop.get(rrr,yyy,NowC.crop)->RCNPlan;*/
}

int SaveSite(int DayRecord)
{
    char fname[255];
	FILE *fpo;

    sprintf(fname,"%s\\Inputs\\site",OUTPUT);
	fpo=sopen(fname,0);
	if (fpo==NULL) return -1;

    if (strlen(IData.sitename)==0) {
		MessageBox(NULL,"No Site name information!","Input Error:",0);
		return -1;
	}
	fprintf(fpo,"%s\n",IData.sitename);
	if (IData.years<=0) {
		MessageBox(NULL,"No Simulated year information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}
	/*if (IData.latitude<=0) {
		MessageBox(NULL,"No latitude information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}*/

    fprintf(fpo,"%d %d %f %ld %f\n", IData.years, DayRecord,
		IData.latitude, IData.totalday, IData.longitude);//, IData.if1File);
    fprintf(fpo,"%d %d\n", IData.Soil_landuse, 0);//IData.CropModel);
    fclose (fpo);

	sprintf(fname, "%s\\Inputs\\SPAN",OUTPUT);
	fpo=sopen(fname,0);
	if (fpo==NULL) return -1;
	fprintf(fpo, "%d\n", 1);//Span
	fclose(fpo);

	return 0;


}

int SaveSoilParas(int id)//1
{

    IData.CEC= (float)(IData.Soil_Clay * 46.0);
    IData.m  = (float)(IData.Soil_Density * 1000. * IData.H * 10000.);
    IData.V  = (float)(IData.H * 10000. * IData.Soil_Porosity);	// m^3/layer/ha
    
    int n;
    n = IData.Q;
    double RCVL[2], RCL[2], RCR[2];
    double Urea[2], NH3[2];
    double Tranr[2], OCini[2], Dphum[2], CharC[2];
    double s_NO3[2], s_NH4[2], ClayNH4[2];
    double s_NO[2], s_N2O[2];
    double s_N2[2], s_NO2[2], s_IniNH4[2];
    
    double PS, FLDCAPw, Wiltptw, TravelTime, ClayF1, ClayF2;//, ePS;
    float RCNRVL, RCNRL, RCNRR, RCNB, RCNH, RCNM, PassiveCCN;
    double stub1, stub2, stub3, Dbm;
    
    PS		= IData.H * IData.Soil_Porosity;	// porosity  (m/layer)
    FLDCAPw = PS * IData.Fldcap;	// m water/layer IData.FieldCapacity
    Wiltptw = PS * IData.Wiltpt;	// m water/layer
    TravelTime = 20.0 * (PS - FLDCAPw) / IData.Sks;	// hr/layer
        // fraction of soil water available for plants, can be tuned
    ClayF1 = pow(10.0,-IData.Soil_Clay / 0.75 - 0.2);
    ClayF2 = IData.Soil_Clay * 6.;

	CN_ratios(&RCNRVL, &RCNRL, &RCNRR, &RCNB, &RCNH, &RCNM, &PassiveCCN);
    
	int DFF;
	CString SPP;
	FILE* spp;
	SPP.Format("%s\\Inter\\SOCpartition.txt", OUTPUT);
	spp=fopen(SPP, "r");
	if(spp==NULL)
	{
		
	}
	else
	{
		fscanf(spp, "%d", &DFF);
		if(DFF==1)
			fscanf(spp, "%f %f %f %f %f", &RCNRVL, &RCNRL, &RCNRR, &RCNH, &RCNM);
		fclose(spp);
	}

	//RCNB=RCNH;

    
    Tranr[1] = IData.Soil_OCatSurface * IData.Soil_Litter * IData.m;
    OCini[1] = IData.Soil_OCatSurface * IData.Soil_humads * IData.m;
    Dphum[1] = IData.Soil_OCatSurface * IData.Soil_humus * IData.m;
	CharC[1] = IData.Soil_OCatSurface * IData.PassiveC * IData.m;
    
    s_NO3[1] = IData.Soil_NO3 * IData.m / 1000000.;
    s_IniNH4[1] = IData.Soil_NH4 * IData.m / 1000000.;
    
    RCVL[1] = 0.0 * Tranr[1];
    RCL[1]  = 0.0 * Tranr[1];
    RCR[1]  = 1.0 * Tranr[1];

/*	if (IfForest()) //ffffffff
	{
		RCVL[1] = 0;
		RCL[1]  = 0;
		RCR[1]  = Tranr[1];
		RCNRVL = 20.0;
		RCNRL = 400.0 / 11.0;
		RCNRR = 200.0;
		IData.LitterWater = (float)(IData.Soil_moiture / IData.Fldcap * IData.FloorC /300000.0);

		float Fo;
		Fo = 2 * IData.Soil_OCatSurface;
		Dbm = float((1 - Fo) * 0.14 * IData.Soil_Density / 
			(.14 - IData.Soil_Density * Fo));
	}
	else*/
		
	Dbm = IData.Soil_Density;
     
    s_NH4[1]   = s_IniNH4[1] * 0.7;
    ClayNH4[1] = s_IniNH4[1] * 0.3;

	float F_soc = IData.Soil_OCatSurface/0.058;
	if(F_soc>1.0) F_soc = 1.0;

	//ClayNH4[1] = F_soc * IData.CEC * 0.4; 
	//ClayNH4[1] = IData.CEC * 0.4; //NewChange

    Urea[1]= 0.;
    NH3[1] = 0.;
    stub1  = 0.;
    stub2  = 0.;
    stub3  = 0.;
    //WeedN  = 0.0;
     
   	int i;
	//double TD1,TD2,TD3,TD4,TD5,TD6,TD7,TD8;
	float TCN=0.0;

/*	TD1 = RCVL[1];
	TD2 = RCL[1];
	TD3 = RCR[1];
	TD4 = OCini[1];
	TD5 = Dphum[1];
	TD6 = s_NO3[1];//NO3[1];
	TD7 = s_NH4[1];//NH4[1];
	TD8 = ClayNH4[1];
*/

    /*for (i = 1;i<=IData.Q;i++) 
	{
        if (i <= IData.Toph) 
		{
            RCVL[i]    = TD1 * IData.SOC12;
            RCL[i]	   = TD2 * IData.SOC12;
            RCR[i]	   = TD3 * IData.SOC12;
            OCini[i]   = TD4 * IData.SOC12;
            Dphum[i]   = TD5 * IData.SOC12;
            s_NO3[i]   = TD6 * IData.SOC12;
            s_NH4[i]   = TD7 * IData.SOC12;
            ClayNH4[i] = TD8 * IData.SOC12;
            Urea[i]    = Urea[1];
            NH3[i]     = NH3[1];
			TCN += ClayNH4[i];
		}
        else 
		{
            //dt = pow(IData.Topr, (i - IData.Toph) * IData.H / 0.1));
            dt         = pow(IData.Topr, (i - IData.Toph) * IData.H / 0.1);
            RCVL[i]    = TD1 / dt;
            RCL[i]     = TD2 / dt;
            RCR[i]     = TD3 / dt;
            OCini[i]   = TD4 / dt;
            Dphum[i]   = TD5 / dt;
            s_NO3[i]   = TD6 / dt;
            s_NH4[i]   = TD7 / dt;
            ClayNH4[i] = ClayNH4[(int)IData.Toph];
            Urea[i]    = Urea[1] / dt;
            NH3[i]     = NH3[1] / dt;
			TCN += ClayNH4[i];
        }*/
        s_NO[1] = 0.;
        s_N2O[1]= 0.;
        s_N2[1] = 0.;
        s_NO2[1]= 0.;
    //}
            
    char fname[255];
	FILE *fpo;
    sprintf(fname,"%s\\Inputs\\soil-%d",OUTPUT,(int)fabsf(id));
	fpo=sopen(fname,0);
	if (fpo==NULL) return -1;

	float IniFrostN2O=0, IniFrostN2=0,ice=0,tt[290];
	int Retard=1;
	if (IData.SoilRetardation==1) Retard=3;
    
		//check data
    if (IData.Soil_Texture<0) {
		MessageBox(NULL,"No Soil_Texture information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}
    if (IData.Soil_Clay<0) {
		MessageBox(NULL,"No Soil_Clay information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}
    if (IData.Soil_Density<0) {
		MessageBox(NULL,"No Soil_Density information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}
    if (IData.Soil_OCatSurface<0) {
		MessageBox(NULL,"No Soil_Organic information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}
    if (IData.Soil_NO3<0) {
		MessageBox(NULL,"No Soil_NO3 information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}
    if (IData.Soil_NH4<0) {
		MessageBox(NULL,"No Soil_NH4 information!","Input Error:",0);
		fclose(fpo);
		return -1;
	}
    if (IData.Soil_Litter<0 || IData.Soil_humads<0 || IData.Soil_humus<0) {
		MessageBox(NULL,"Soil_Litter or humads, mumus information error!","Input Error:",0);
		fclose(fpo);
		return -1;
	}

	for (i=1; i<=IData.Q; i++)
	{
		tt[i] = IData.AnnualMeanT + (IData.Soil_T - IData.AnnualMeanT)/ (float)powf(i*IData.H*100, 0.5);
		if (IData.Soil_T<0.0 && tt[i] < IData.Soil_T) tt[i] = IData.Soil_T;

		
		/*tt[L] =  yr_avet + (s_temp - yr_avet)
			/ (float)pow(L*H*100, 0.5);
		if (s_temp<0.0 && tt[L] < s_temp) tt[L] = s_temp;*/
	}


	fprintf(fpo,"%3d\n", IData.Soil_Texture);
    fprintf(fpo,"%s\n\n", IData.SoilName);

    fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
		IData.Soil_Clay, IData.Soil_Porosity, IData.Sks, IData.Fldcap,
		IData.Wiltpt, IData.LateralInflux); 
    fprintf(fpo,"%f %f %f %f %d  %f\n",
		IData.Psisat, IData.Beta, Dbm, IData.Soil_pH, 
		IData.Idc, IData.Soil_OCatSurface);
    fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
		IData.Soil_NO3, IData.Soil_NH4, IData.Soil_Litter, 
		IData.Soil_humads, IData.Soil_humus, 0.0);//Byp
    fprintf(fpo,"%.8f  %.4f  %.4f  %.4f  %d\n",
		IData.H, IData.TH, IData.m, IData.V, IData.Q);//IData.m seems to be mass of soil
    fprintf(fpo,"%.4f  %.4f\n", ClayF1, ClayF2);
    fprintf(fpo,"%.4f  %.4f  %d  %.4f  %.4f  %.4f  %.4f\n",
		IData.Qstar, IData.BypassF, Retard, RCNB, RCNH, RCNM, RCNRVL);
    fprintf(fpo,"%.4f  %.4f %.4f  %.4f  %.4f  %.4f\n",
		RCNRL, RCNRR, IData.AcWater, IData.SurfWater, IData.SnowPack, stub1);
    fprintf(fpo,"%.4f  %.4f\n", stub2, stub3);
    fprintf(fpo, "%.4f  %.4f  %.4f\n\n", PassiveCCN, IniFrostN2O, IniFrostN2);
    
	int WRL = (int)(IData.Soil_WaterObstructLayer*0.01/IData.H);
    /*for (i = 1;i<=IData.Q;i++) 
	{
		//if(WRL>0&&i>=WRL) IData.Soil_moiture=1.0;
		//else IData.Soil_moiture=IData.Fldcap;

		IData.Soil_moiture=IData.Fldcap;

        fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f\n",
			RCVL[i], RCL[i], RCR[i], OCini[i], Dphum[i]);
        fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
			s_NO2[i], s_NO3[i], s_NH4[i], ClayNH4[i], Urea[i], NH3[i]);
        fprintf(fpo,"%.4f  %.4f  %.4f  %.4f  %.4f  %.4f\n",
			s_NO[i], s_N2O[i], s_N2[i], tt[i],
			IData.Soil_moiture,ice);

		fprintf(fpo,"\n");
    }*/
	
	fprintf(fpo, "%f\n", IData.Soil_MicrobioIndex); 
	fprintf(fpo, "%f\n", IData.Soil_WaterObstructLayer);//m
	fprintf(fpo, "%f %f\n", IData.slope, IData.Soil_Quality); 
	fprintf(fpo, "%f\n", IData.Fldcap); 
	fprintf(fpo, "%f\n", IData.Wiltpt); 
	fprintf(fpo, "%f %f\n", IData.SOCa, IData.SOCb);
	fprintf(fpo, "%f %f %f %f %f %f %f %f %f\n", RCVL[1], RCL[1], RCR[1], OCini[1], Dphum[1],
		s_NO2[1], s_NO3[1], s_NH4[1], ClayNH4[1]);
	fprintf(fpo, "%f\n", tt[1]);
	fprintf(fpo, "%f\n", IData.HighestWT);
	fprintf(fpo, "%d\n", IData.SCSuse);
	fprintf(fpo, "%f\n", CharC[1]);
	fprintf(fpo, "%f\n", IData.DClitter);
	fprintf(fpo, "%f\n", IData.DChumads);
	fprintf(fpo, "%f\n", IData.DChumus);
	fprintf(fpo, "%f\n", IData.HumadCN);
	fprintf(fpo, "%f\n", IData.HumusCN);
	fprintf(fpo, "%f\n", IData.WaterPoolBD);
	fprintf(fpo, "%d\n", IData.ProfileType);
	if (IData.ProfileType == 0)
	{
		fprintf(fpo, "%d\n", IData.ProfileType);
	}
	else
	{
		fprintf(fpo, "%s\n", IData.ProfileFileName);
	}
	fprintf(fpo, "%d\n", IData.CheckHomo1);//add Water Flow Homogeneous
	
    fclose (fpo);

	if (id<0) return 0;

	char SYF[200];
	FILE* sni;
	sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
	sni=sopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 1);
	fclose(sni);

	return 0;

}

void ReSetCcomponent()
{
	IData.Topr = Socb[IData.Soil_landuse];
    IData.Toph = (Soca[IData.Soil_landuse] / IData.H);
  
    //IData.Soil_NO3 = 500.0 * IData.Soil_OCatSurface;///IData.Soil_landuse;
    //IData.Soil_NH4 = 100.0 * IData.Soil_OCatSurface;///IData.Soil_landuse;

	IData.Soil_NO3 = SOCtoNO3(IData.Soil_OCatSurface, IData.latitude);
	IData.Soil_NO3 = max(1.0, IData.Soil_NO3);
	IData.Soil_NH4 = 0.1 * IData.Soil_NO3;	
}

int SetSoilH()
{
    IData.AcWater   = 0;
	IData.SurfWater = 0;
	IData.SnowPack  = 0;

    //IData.Idc = 1# + IIf(soilbypass(0).Value = True, 0, 1) 'Soil_BypassFlow
	IData.Idc = 1 + (int)IData.Soil_BypassFlow;
    
	//if (IData.Soil_Texture != 12) { //'If Soiltexture.ListIndex <> 11 Then
    //     IData.Sts = float(1 - IData.Soil_Density * (IData.Soil_OCatSurface / 1.3 + (1 - IData.Soil_OCatSurface) / 2.6));
    //
	//if (IData.Sts<=0) //safety check
	/*{
		MessageBox(NULL,"Soil-Density or Soil Organic may be wrong! Please input a smaller one.","Inputed Error:",NULL);
		IData.Sts = 1;
		return -1;
	}*/

    //if (IData.Soil_Texture < 10) IData.Sks = IData.RawSKS * (float)0.6; //cm/min -> m/hr
    IData.Qstar = (float)(6.45 * (IData.Soil_Clay - 0.01) + 1);
    IData.BypassF = IData.Soil_BypassFlow;//(float)0.1 * (IData.Idc - 1);
    
    //float T01 = 1;
    //if (IData.BypassF > 0.0) T01 = IData.BypassF * 10.0 + 1.0;
    //IData.Sks = IData.Sks * T01;

	//insert saxton pedotransfer function to recalculate sat conductivity
	float  sandFraction, soilOM, surfaceSOC, newFC, newWP;
	float clay[2] = {0.0, IData.Soil_Clay };
	float sandContent[13] = { 0.0,0.85,0.80,0.63,0.15,0.41,0.53,0.09,0.29,0.52,0.08,0.13,0.15 };
	if (IData.Soil_Texture <= 12) { sandFraction = sandContent[IData.Soil_Texture]; }
	else
	{
		sandFraction = 0.15;
	}
	soilOM = IData.Soil_OCatSurface * 100 * 1.72; //calculate OM%

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
	if (SatCond < 0.015)SatCond = 0.015;
	if (SatCond > 1.0)SatCond = 1.0;
	
	//IData.Sks = SatCond;//set Sat Conductivity to saxton value for use in determining layer count. Turned on for Sustainability metrics
	/*
	IData.Soil_Density
	IData.Soil_pH
	IData.Soil_Clay
	IData.Soil_Porosity
	IData.Soil_BypassFlow)
	IData.Fldcap
	fIData.Wiltpt
	*/


    float dt;//brian determines the depth of the layers here
	int max_layers=280-10;
	IData.TH = SOILDEPTH;//1.0 m, total depth of simulated soil profile -- layer thickness IData.H
    dt = 0.01 / IData.Soil_Porosity;//modifying this from default 0.01 to 0.015 speeds things up a tonne. Defines soil layer height.
	
   if (dt < IData.Sks) IData.H = dt;
    else IData.H = IData.Sks;

   if (IData.DynLayerCheck == 0)//checks to see if Dynamic Layer Depth is on or off. 
   {
	   if (IData.DynLayerEdit < 1.0)IData.DynLayerEdit = 1.0;
	   if (IData.DynLayerEdit > 10.0)IData.DynLayerEdit = 10.0;
	   IData.H = (IData.DynLayerEdit/100.0);//convert user input Layer Depth from cm to m 
	  
   }
   if (IData.AutoManureCheck == 0)//checks to see if Auto Manure is on or off. 
   {
	   

   }

	//IData.H = 0.025;//test a fixed depth //liz - temporary to speed things up
    if (IData.H <= 0) {
        MessageBox (NULL,"There is a parameter error of Soil_H=0 ! Please check system file and your data.", "Input Error :",0);
		return -1;
    }	
	if (IData.H*max_layers < IData.TH )
		IData.H = IData.TH / max_layers;

	IData.Q = (int)(IData.TH / IData.H);

	if (IData.Q > max_layers) 
	{
		IData.Q = max_layers;
		IData.H = IData.TH / max_layers;
	}

	return 0;
    
    //ReSetCcomponent();
}



//-----------------------------------------------------------------
// A base class to process array

CropWorkArrayDefine::CropWorkArrayDefine()
{
	CWAP	   =NULL;
	maxRotation=0;
	maxYear    =0;
	maxN	   =0;
}

int CropWorkArrayDefine::dim (int rt,int yr,int num)
{
	long cl=(rt+1)*(yr+1)*(num+1);
	if (cl<=0) 
	{
		CWAP=NULL;
		return -1;
	}
	char *newp = (char *)malloc(cl*SizeOfData());
	if (newp==NULL) return -1;
	memset(newp,-1,cl*SizeOfData());

	if (CWAP !=NULL) {	// copy the old data into the new array
		long oldlen=(maxRotation+1)*(maxYear+1)*(maxN+1);
		if (oldlen>0) {

/*			int i,j,k,NR,NY,NN;
			if (maxRotation>rt) NR=rt;
			else NR=maxRotation;
			if (maxYear>yr) NY=yr;
			else NY=maxYear;
			if (maxN>num) NN=num;
			else NN=maxN;

			oldlen=SizeOfData();
			for (i=0;i<NR;i++)
			{
				for (j=0;j<NY;j++)
				{
					for (k=0;k<NN;k++)
					{
						//*(newp+i*num*yr+j*num+k)=*(CWAP+i*maxN*maxYear+j*maxN+k);
						memcpy(newp+i*num*yr+j*num+k,CWAP+i*maxN*maxYear+j*maxN+k,oldlen);
					}
				}
			}
*/
			if (oldlen > cl) oldlen = cl;
			oldlen=oldlen*SizeOfData();
			memcpy(newp,CWAP,oldlen);
			free(CWAP);
		}
	}
	CWAP=newp;
	maxRotation=rt;
	maxYear=yr;
	maxN=num;
	return 0;
}

int CropWorkArrayDefine::dim (int rt,int yr)
{
	long cl=(rt+1)*(yr+1);
	if (cl<=0) 
	{
		CWAP=NULL;
		return -1;
	}
	char *newp = (char *)malloc(cl*SizeOfData());
	if (newp==NULL) return -1;
	memset(newp,-1,cl*SizeOfData());

	if (CWAP !=NULL) {	// copy the old data into the new array
		long oldlen=(maxRotation+1)*(maxYear+1);
		if (oldlen>0) {
			if (oldlen > cl) oldlen = cl;
			oldlen=oldlen*SizeOfData();
			memcpy(newp,CWAP,oldlen);
			free(CWAP);
		}
	}
	CWAP=newp;
	maxRotation=rt;
	maxYear=yr;
	return 0;
}

// one-dimension array:
int CropWorkArrayDefine::dim (int rt)
{
	long cl=(rt+1);
	if (cl<=0) 
	{
		CWAP=NULL;
		return -1;
	}
	char *newp = (char *)malloc(cl*SizeOfData());
	memset(newp,-1,cl*SizeOfData());
	if (newp==NULL) return -1;

	if (CWAP !=NULL) {	// copy the old data into the new array
		long oldlen=(maxRotation+1);
		if (oldlen>0) {
			if (oldlen > cl) oldlen = cl;
			oldlen=oldlen*SizeOfData();
			memcpy(newp,CWAP,oldlen);
			free(CWAP);
		}
	}
	CWAP=newp;
	maxRotation=rt;
	return 0;
}

CropWorkArrayDefine::~CropWorkArrayDefine()
{
	if (CWAP!=NULL) free(CWAP);
	CWAP=NULL;
	maxRotation=0;
	maxYear=0;
	maxN=0;
}

int CropWorkArrayDefine::clear()
{
	if (CWAP!=NULL) free(CWAP);
	CWAP=NULL;
	maxRotation=0;
	maxYear=0;
	maxN=0;
	return 0;
}

//-----------------------------------------------------------------
// Crop parameter class's definition

int CropArray::SizeOfData()
{
	return (sizeof(CropParameter));
}

int CropArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(CropParameter *)CWAP;
	return 0;
}

CropArray::CropArray()
{
//	CropWorkArrayDefine::CropWorkArrayDefine();
	Pnt=NULL;
}

CropArray::~CropArray()
{
//	CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

int CropArray::Reset()
{
	clear();
	return 0;
}

CropParameter * CropArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) {
		MessageBox(NULL, "1. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}


//-----------------------------------------------------------------
// Till parameter class's definition
/*int TillArray::SizeOfData()
{
	return (sizeof(TillageParameter));
}

int TillArray::Reset()
{
	clear();
	return 0;
}

int TillArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(TillageParameter *)CWAP;
	return 0;
}

TillArray::~TillArray()
{
	//CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

TillageParameter * TillArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) {
		MessageBox(NULL, "2. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}
*/

//-----------------------------------------------------------------
// Fer parameter class's definition
/*int FerArray::SizeOfData()
{
	return (sizeof(FertilizationParameter));
}
int FerArray::Reset()
{
	clear();
	return 0;
}
int FerArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(FertilizationParameter *)CWAP;
	return 0;
}

FerArray::~FerArray()
{
	//CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

FertilizationParameter * FerArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) {
		MessageBox(NULL, "3. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}
*/
//-----------------------------------------------------------------
// Lime parameter class's definition
/*int LimeArray::SizeOfData()
{
	return (sizeof(LimeParameter));
}
int LimeArray::Reset()
{
	clear();
	return 0;
}
int LimeArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(LimeParameter *)CWAP;
	return 0;
}

LimeArray::~LimeArray()
{
	//CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

LimeParameter * LimeArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) {
		MessageBox(NULL, "4. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}
*/

//-----------------------------------------------------------------
// Manure parameter class's definition
/*int ManureArray::SizeOfData()
{
	return (sizeof(ManureParameter));
}
int ManureArray::Reset()
{
	clear();
	return 0;
}

int ManureArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(ManureParameter *)CWAP;
	return 0;
}

ManureArray::~ManureArray()
{
	//CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

ManureParameter * ManureArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) {
		MessageBox(NULL, "5. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}
*/
//-----------------------------------------------------------------
// Weed parameter class's definition
/*int WeedArray::SizeOfData()
{
	return (sizeof(WeedParameter));
}
int WeedArray::Reset()
{
	clear();
	return 0;
}
int WeedArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(WeedParameter *)CWAP;
	return 0;
}

WeedArray::~WeedArray()
{
	//CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

WeedParameter * WeedArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) ||Pnt==NULL) {
		MessageBox(NULL, "6. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}
*/

//-----------------------------------------------------------------
// Flood parameter class's definition
/*int FloodArray::SizeOfData()
{
	return (sizeof(FloodParameter));
}
int FloodArray::Reset()
{
	clear();
	return 0;
}
int FloodArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(FloodParameter *)CWAP;
	return 0;
}

FloodArray::~FloodArray()
{
//	CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

FloodParameter * FloodArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) 
	{
		MessageBox(NULL, "7. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}

*/
//-----------------------------------------------------------------
// Irrigation parameter class's definition
/*int IrrigationArray::SizeOfData()
{
	return (sizeof(IrrigationParameter));
}
int IrrigationArray::Reset()
{
	clear();
	return 0;
}
int IrrigationArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(IrrigationParameter *)CWAP;
	return 0;
}

IrrigationArray::IrrigationArray()
{
//	CropWorkArrayDefine::CropWorkArrayDefine();
	Pnt=NULL;
}
IrrigationArray::~IrrigationArray()
{
//	CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

IrrigationParameter * IrrigationArray::get(int rt,int yr,int num)
{

	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) {
		MessageBox(NULL, "8. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}
*/
//-----------------------------------------------------------------
// Grazing parameter class's definition
/*int GrazingArray::SizeOfData()
{
	return (sizeof(GrazingArray));
}
int GrazingArray::Reset()
{
	clear();
	return 0;
}
int GrazingArray::dim(int rt,int yr,int num)
{
	if (CropWorkArrayDefine::dim(rt,yr,num)==-1) return -1;
	Pnt=(GrazingParameter *)CWAP;
	return 0;
}

GrazingArray::GrazingArray()
{
//	CropWorkArrayDefine::CropWorkArrayDefine();
	Pnt=NULL;
}
GrazingArray::~GrazingArray()
{
//	CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

GrazingParameter * GrazingArray::get(int rt,int yr,int num)
{
	if ((rt<1 || rt>maxRotation) ||(yr<1 || yr>maxYear) ||(num<1) || (num>maxN) || Pnt==NULL) {
		MessageBox(NULL, "9. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1)*maxN*maxYear+(yr-1)*maxN+num-1;
	return Pnt+cl;
}

*/

//-----------------------------------------------------------------
// Cycle definition
/*int Cycle_a_year::SizeOfData()
{
	return (sizeof(ParameterEachYear));
}

int Cycle_a_year::Reset()
{
	clear();
	return 0;
}

int Cycle_a_year::dim (int rt,int yr)
{
	if (CropWorkArrayDefine::dim(rt,yr)==-1) return -1;
	Pnt=(ParameterEachYear *)CWAP;
	return 0;
}

Cycle_a_year::~Cycle_a_year()
{
	//CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

ParameterEachYear * Cycle_a_year::get(int rt,int yr)
{


	return 0;
}
*/

//-----------------------------------------------------------------
// RotationArray definition
/*int RotationArray::SizeOfData()
{
	return (sizeof(RotationParameter));
}

int RotationArray::Reset()
{
	clear();
	return 0;
}

int RotationArray::dim (int rt)
{
	if (CropWorkArrayDefine::dim(rt)==-1) return -1;
	Pnt=(RotationParameter *)CWAP;
	return 0;
}

RotationArray::~RotationArray()
{
	//CropWorkArrayDefine::~CropWorkArrayDefine();
	Pnt=NULL;
}

RotationParameter * RotationArray::get(int rt)
{
	if ((rt<1 || rt>maxRotation) || Pnt==NULL) {
		MessageBox(NULL, "12. Pointer error! Can't continue!", "Error Message", NULL);
		exit(0);	//there is a pointer error!
	}
	long cl=(long)(rt-1);
	return Pnt+cl;
}

*/
//-----------------------------------------------------------------
// StringArray definition
StringArray::StringArray()
{
	n=0;
	//dim(100);
}

StringArray::~StringArray()
{
	//clear();
	
	int i;
	char *p1;
	for (i=1;i<=n;i++) {
		p1=get(i);
		if (p1!=NULL) free(p1);
		p1=NULL;
	}
	n=0;
//	delete [] p;
	tn=0;
}

int StringArray::dim(int num)
{
	tn = num;
	//p = (char **) new char(tn);
	return 0;
}

int StringArray::clear()
{
	int i;
	for (i=n;i>0;i--) del(i);
	n=0;
	return 0;
}
int StringArray::del(int pos)
{
	if (pos<1 || pos>n) return -1;
	if (n<1) return 0;
	int i;
	free(get(pos));
	for (i=pos;i<n;i++) p[i]=p[i+1];
	n--;
	return 0;
}

int StringArray::insert(int pos,char *dat)
{
	int i;
/*	if (n>tn-1)
	{
		tn+=50;
		char **mp=NULL;
		mp = (char **) new char(tn);
		for (i=1;i<=n;i++) mp[i]=p[i];
		delete [] p;
		p = mp;
	}*/

	/*if (n==301) {
		MessageBox(NULL,"Climate file must be less than 100!","Error",NULL);
		return -1;
	}*/
	char *p1;
	
	p1=(char *)malloc(strlen(dat)+3);
	if (p1==NULL) return -1;
	strcpy(p1,dat);
	if (pos>n || n==0) {
		p[n+1]=p1;
	}
	else if (pos<=1) {
		for (i=2;i<=n+1;i++) p[i]=p[i-1];
		p[1]=p1;
	}
	else {
		for (i=pos+1;i<=n+1;i++) p[i]=p[i-1];
		p[pos]=p1;
	}
	n++;
	return 0;
}

char* StringArray::get(int pos)
{
	if (pos<1 ||pos>n) 
	{
		MessageBox(NULL,"String Index is out of the range!","System Error:",0);
		return NULL;
	}
	return p[pos];
}


//----------------------------------------------
// Initialize Site information
Site_BaseInformation::Site_BaseInformation()
{

// variable part:

		// Site information
	strcpy(sitename,"");
	strcpy(Regionname,"");
	latitude =0;
	longitude=120.0;
    totalday =0;
    years    =0;
    ifdaily  =0;
	if1File  =0;

		// Climate information
    ClimateFileType  = 1;
    ClimateFileNumber= 0;
    NO3NH4_Rainfall  = 0;
    NH3_Atmosphere   = (float)0.06;
	BaseCO2			 = 380;
	
	WaterYr = 0;
	CO2IncreaseRate = 0.0;
	SOCa = 0.0;
	SOCb = 0.0;
    
        // Soil information
    Soil_Texture = 0;
    Soil_Density = 0;
    Soil_pH      = 0;
    Soil_OCatSurface = 0;
    Soil_Clay    = 0;
    Soil_landuse = 0;
    Soil_BypassFlow  = 0;
    Soil_Litter  = 0;// Resoc
    Soil_humads  = 0;// Ahsoc
    Soil_humus   = 0;// Phsoc
	PassiveC = 0.0;
    Soil_NO3     = 0;// IniNO3
    Soil_NH4     = 0;// IniNH4
    Soil_moiture = 0;
    Soil_T       = 0;
	SoilRetardation = 0;
	LateralInflux = 1.0;
	Soil_MicrobioIndex = 1.0;
	Soil_Quality = 0.0;
	Soil_WaterObstructLayer = 2.50;//m /sets default Water
	slope = 0.0;
	Fldcap = 0.0;
	Wiltpt = 0.0;
	HighestWT = 1.0;
	CheckHomo1 = 1;
	Soil_Porosity = 0.0;
	
	DClitter=1.0;
	DChumads=1.0;
	DChumus=1.0;
	HumadCN=10.0;
	HumusCN = 10.0;
	SCSuse = 0;
    
    Idc       = 0;
    H		  = 0;
    Topr	  = 0;
    Toph	  = 0;
    CEC		  = 0;
    TH		  = 0;
    m		  = 0;
    V		  = 0;
    Q		  = 0;
    Qstar	  = 0;
    AcWater	  = 0;
    SurfWater = 0;
    SnowPack  = 0;
    BypassF   = 0;
    
    //Clay;
    //Sts   = 0;
    //RawSKS= 0;
    Sks   = 0;
    //Fldcap= 0;
    //Wiltpt= 0;
    LateralInflux= 1.0;
    Psisat= 0; 
    Beta  = 0;
//    strcpy(BetaNote,"");
//    strcpy(PsisatNote,"");
//    strcpy(SoilhtcpNote,"");
//    strcpy(WiltptNote,"");
 //   strcpy(ClayNote,"");
//    strcpy(StsNote,"");
//    strcpy(SksNote,"");
//    strcpy(FldcapNote,"");

    
        // rotation
    Rotation_Number = 0;
    //MaxCycle        = 0;;
    
    MaxCrop = 0;
    MaxTill = 0;
    MaxFer  = 0;
    MaxManure = 0;
    MaxWeed = 0;
    MaxFlood  = 0;
    MaxIrr  = 0;
    MaxGrazing = 0;
	MaxLime = 0;


		// forest
	FoliageMass = 0;
	WoodMass = 0;
	LitterMass = 0;
	ForestAge = 0;
	ForestType = 0;
	SoilFertility = -1;
	SOC12 = 1;
	FolCNR = 0;
	FloorC = 0;
	LitterWater = 0;
	LitterpH = 0;
	ForestName = "";

}


void Site_BaseInformation::NewData()
{
	Site_BaseInformation();
	years = 0;
	strcpy(sitename, "");
    latitude = 0;
    NO3NH4_Rainfall = 0;
    NH3_Atmosphere  = (float)0.06;
	BaseCO2 = 350;
	CO2IncreaseRate = 0.0;
	SOCa = 0.0;
	SOCb = 0.0;
    
    Rotation_Number = 0;
	
}



int SaveCropParas() //!!!!!!!!!!!
{
	int CropIDID, ManureCropOrder;
	
	CString SETINPUTS;
	SETINPUTS.Format("%s\\Inputs", OUTPUT);

#ifdef MANURE	
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureFieldCrops", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d", &TotalFarmFields, &CropIDID);
	fclose(xff);
	//FCT10.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	//FCT10.Format("%s", INTERMANAGE);
	TotalFarmFields = 1;
#endif

    char fname[255],outname[255];
    int  i, j, k, kkk, yr;//, hyr=0;
	FILE *fcrop, *fpi;

	int db_Rotation_Number;
	int db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20],db_PerennialCrop[20][20][5];
	int db_YrCrops[20][20], db_YrCropOrder[20][20][5], db_YrCropType[20][20][5], db_CoverCrop[20][20][5];
	int db_PMonth[20][20][5], db_PDay[20][20][5], db_HMonth[20][20][5], db_HDay[20][20][5], db_HYr[20][20][5];
	float db_Residue[20][20][5], db_Yield[20][20][5], db_RepRate[20][20][5];
	int db_Transplant[20][20][5];
	float db_PsnEff[20][20][5], db_PsnMax[20][20][5], db_TreeAge[20][20][5]={0.0,0.0};
	float db_GrainFraction[20][20][5], db_LeafFraction[20][20][5], db_ShootFraction[20][20][5], db_RootFraction[20][20][5];
	float db_GrainCN[20][20][5], db_LeafCN[20][20][5], db_ShootCN[20][20][5], db_RootCN[20][20][5];
	float db_TDD[20][20][5], db_Water[20][20][5], db_OptT[20][20][5], db_Nfix[20][20][5], db_Vascularity[20][20][5],db_GrainFill[20][20][5];
	float db_TreeCurrentAge[20][20][5]={0.0,0.0}, db_TreeLeafMax[20][20][5]={0.0,0.0}, db_TreeLeafMin[20][20][5]={0.0,0.0};
    int db_RootShape[20][20][5];
	float db_LAImax[20][20][5];
	float db_FrostKill[20][20][5];
	float db_AlfCHRMX[20][20][5];
	float db_ALFCDRMX[20][20][5];
	float db_ALFCTMX[20][20][5];
	float db_ALFPDFMX[20][20][5];
	float db_Root1[20][20][5], db_Root2[20][20][5], db_VE[20][20][5], db_V1[20][20][5], db_VT[20][20][5], db_R1[20][20][5], db_R3[20][20][5], db_R5[20][20][5], db_R7[20][20][5], db_R8[20][20][5], db_PVE[20][20][5], db_PV1[20][20][5], db_PVT[20][20][5], db_PR1[20][20][5], db_PR3[20][20][5], db_PR5[20][20][5], db_PR7[20][20][5], db_PR8[20][20][5];
	float db_AGResp1[20][20][5], db_AGResp2[20][20][5];
	float db_Kext1[20][20][5], db_Kext2[20][20][5], db_cropHeight[20][20][5];//Theo db_cropHeight,db_Kext2,db_Kext1
	float db_cropGRate[20][20][5], db_cropTime[20][20][5], db_RUEHI[20][20][5], db_DelayP[20][20][5];
	CString DB;
	FILE *db;

for(int MFFC=1; MFFC<=TotalFarmFields; MFFC++)
{
#ifdef MANURE
	FCT0.Format("%s_%d", INTERMANAGE, MFFC);
	FCT100.Format("%s\\FarmCrop_%d", SETINPUTS, MFFC);
	_mkdir(FCT100);
#else
	FCT0.Format("%s_1", INTERMANAGE);
	FCT100.Format("%s", SETINPUTS);
#endif

	DB.Format("%s\\CropRotation.txt", FCT0);
	db=fopen(DB, "r");
	if(db==NULL) note(0,DB);
	
	fscanf(db, "%d", &db_Rotation_Number);
	fclose(db);

	int ccc;
	for(int rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		DB.Format("%s\\CropRotation_%d.txt", FCT0, rrr);//read: SaveCropParas()
		db=fopen(DB, "r");
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);

		for(int yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
		{
			//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, rrr, yyy);
			DB.Format("%s\\CropRotation_%d_%d.txt", FCT0, rrr, yyy);
			db=fopen(DB, "r");
			if(db==NULL) note(0,DB);
			fscanf(db, "%d", &db_YrCrops[rrr][yyy]);

			for(ccc=1; ccc<=db_YrCrops[rrr][yyy]; ccc++)
			{
				fscanf(db, "%d %d", &db_YrCropOrder[rrr][yyy][ccc], &db_YrCropType[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_PMonth[rrr][yyy][ccc], &db_PDay[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_HMonth[rrr][yyy][ccc], &db_HDay[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_HYr[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_Residue[rrr][yyy][ccc], &db_Yield[rrr][yyy][ccc]);
				fscanf(db, "%f %d", &db_RepRate[rrr][yyy][ccc], &db_Transplant[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_PsnEff[rrr][yyy][ccc], &db_PsnMax[rrr][yyy][ccc]);
				fscanf(db, "%f", &db_TreeAge[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_CoverCrop[rrr][yyy][ccc]);	
				fscanf(db, "%d", &db_PerennialCrop[rrr][yyy][ccc]);

				fscanf(db, "%f %f %f %f", &db_GrainFraction[rrr][yyy][ccc], &db_LeafFraction[rrr][yyy][ccc], &db_ShootFraction[rrr][yyy][ccc], &db_RootFraction[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_GrainCN[rrr][yyy][ccc], &db_LeafCN[rrr][yyy][ccc], &db_ShootCN[rrr][yyy][ccc], &db_RootCN[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f %f", &db_TDD[rrr][yyy][ccc], &db_Water[rrr][yyy][ccc], &db_OptT[rrr][yyy][ccc], &db_Nfix[rrr][yyy][ccc], &db_Vascularity[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_TreeAge[rrr][yyy][ccc], &db_TreeCurrentAge[rrr][yyy][ccc], &db_TreeLeafMax[rrr][yyy][ccc], &db_TreeLeafMin[rrr][yyy][ccc]);
				fscanf(db, "%d %f", &db_RootShape[rrr][yyy][ccc], &db_GrainFill[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_LAImax[rrr][yyy][ccc], &db_FrostKill[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_AlfCHRMX[rrr][yyy][ccc], &db_ALFCDRMX[rrr][yyy][ccc], &db_ALFCTMX[rrr][yyy][ccc], &db_ALFPDFMX[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_Root1[rrr][yyy][ccc], &db_Root2[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &db_AGResp1[rrr][yyy][ccc], &db_AGResp2[rrr][yyy][ccc]);
				fscanf(db, "%f %f %f %f", &db_cropGRate[rrr][yyy][ccc], &db_cropTime[rrr][yyy][ccc], &db_RUEHI[rrr][yyy][ccc], &db_DelayP[rrr][yyy][ccc]);//might be problematic?
			//	fscanf(db, "%f %f %f", &db_Kext1[rrr][yyy][ccc], &db_Kext2[rrr][yyy][ccc], &db_cropHeight[rrr][yyy][ccc]);
			}
			
			fclose(db);

			///////////////////////////////////////////////////////////
			char fname[255];
			FILE *fp;
			int WinterCropFlag=0, LeftDays=0;
    
			sprintf(fname, "%s\\cyc-%d_%d", FCT0,rrr, yyy);
			fp=fopen(fname, "w");

			if (db_YrCrops[rrr][yyy]==0) //no crop
			{
				fprintf(fp, "%d\n", 0);
				fprintf(fp, "%d  %s  %d  %d  %f  %d\n", 0, "None", 0, 0, 0.0, 10);
				fprintf(fp, "%d  %d  %f  %f  %d\n", 0, 0, 0.0, 0.0, 999);
				fprintf(fp, "%f  %d  %f  %f  %f\n", 0.0, 0, 0.0, 0.0, 0.0);
				fprintf(fp, "%d\n", 0);
				//fprintf(fp, "%d\n", 0);

				// CropCode, WinterCropFlag, WinterCropLeftDays, OptimumYield, HarvestYear;
				  // PalntingJday, GrowingDays, ResidueIncorporation, MaxNDemand, EndCropFlag;
				  // IniCropBiomass, GRvege, GRreprod, PsnEfficiency, PsnMax 
				//cover_crp
			}
			else
			{
				fprintf(fp, "%d\n", db_YrCrops[rrr][yyy]);
				for (i = 1;i<=db_YrCrops[rrr][yyy];i++) 
				{
					int SeedDay = JulianDay(db_PMonth[rrr][yyy][i], db_PDay[rrr][yyy][i]);
					int HarvDay = JulianDay(db_HMonth[rrr][yyy][i], db_HDay[rrr][yyy][i]);
					int GrowDays;
					if(db_HYr[rrr][yyy][i]==1)//SeedDay<HarvDay)
					{
						GrowDays = HarvDay - SeedDay;
						WinterCropFlag = 0;
						LeftDays = 0;
					}
					else
					{
						GrowDays = 365 - SeedDay + HarvDay + (db_HYr[rrr][yyy][i] - 2) * 365;
						WinterCropFlag = db_HYr[rrr][yyy][i] - 1;//yyy-1;
						if(WinterCropFlag==1) LeftDays = GrowDays;
						else LeftDays = GrowDays - (365*(db_HYr[rrr][yyy][i] - 1) - SeedDay);
					}

					int wwww=111, jd;
					if(i==db_YrCrops[rrr][yyy]) wwww = 999;

					
					int CropType = db_YrCropType[rrr][yyy][i];
					char CropNameX[100];

					///////////////////////////////////////////////////////////////////////////////////////////
					int v_CropID[95], v_Perennial[95];
					float v_max_biomass_C[95], v_grain_fraction[95], v_leaf_fraction[95], v_leafstem_fraction[95], v_root_fraction[95];
					float v_GrainCN[95], v_LeafCN[95], v_ShootCN[95], v_RootCN[95], v_TreeAge[95];
					float v_WaterDemand[95], v_OptimumT[95], v_TDD[95], v_Nfixation[95], v_Vascularity[95];
					float v_Root1[95], v_Root2[95], v_AGResp1[95], v_AGResp2[95];//new Root Respiration
					float v_Kext1[95], v_Kext2[95],v_CMaxH[95];//crop extinction coefficients
					float v_cropGRate[95], v_cropTime[95], v_RUEHI[95], v_DelayP[95];
					//CString v_CropName[95];
					char v_CropName[95][100]={"NONE","NONE"};

					ReadCropPara1(v_CropID, v_CropName, v_max_biomass_C, v_grain_fraction, v_leaf_fraction,
					  v_leafstem_fraction, v_root_fraction, v_GrainCN, 
					  v_LeafCN, v_ShootCN, v_RootCN, v_WaterDemand, v_OptimumT, 
					  v_TDD, v_Nfixation, v_Vascularity, v_Perennial, v_TreeAge,v_Root1,v_Root2,v_AGResp1,v_AGResp2,v_Kext1,v_Kext2, v_CMaxH, v_cropGRate, v_cropTime, v_RUEHI, v_DelayP);

					///////////////////////////////////////////////////////////////////////////////////////////
					
					/*m_CropYield = v_max_biomass_C[CropType] * v_grain_fraction[CropType];//kg C/ha
					m_ShootYield = v_max_biomass_C[CropType] * v_leafstem_fraction[CropType];
					m_RootYield = v_max_biomass_C[CropType] * v_root_fraction[CropType];
					m_GrainFraction = v_grain_fraction[CropType];
					m_ShootFraction = v_leafstem_fraction[CropType];
					m_RootFraction = v_root_fraction[CropType];*/
					
					sprintf(Crop_Name, "%s", v_CropName[CropType]);

					////////////////////////////////////////////////////////////////////////////////////////////

    				float PlantC = db_Yield[rrr][yyy][i] / db_GrainFraction[rrr][yyy][i];
					float LeafC = PlantC * db_LeafFraction[rrr][yyy][i];
					float ShootC = PlantC * db_ShootFraction[rrr][yyy][i];
					float RootC = PlantC * db_RootFraction[rrr][yyy][i];
					float PlantCN = 1.0 / (db_GrainFraction[rrr][yyy][i]/db_GrainCN[rrr][yyy][i] + 
						db_LeafFraction[rrr][yyy][i]/db_LeafCN[rrr][yyy][i] + 
						db_ShootFraction[rrr][yyy][i]/db_ShootCN[rrr][yyy][i] + 
						db_RootFraction[rrr][yyy][i]/db_RootCN[rrr][yyy][i]);
					float MaxPlantN = PlantC / PlantCN;					
					if(db_YrCropType[rrr][yyy][i]==0) MaxPlantN = 0.0;
					
					fprintf(fp, "%d  %s  %d  %d  %f  %d\n", db_YrCropType[rrr][yyy][i], Crop_Name, WinterCropFlag, LeftDays, db_Yield[rrr][yyy][i], db_HYr[rrr][yyy][i]);
					fprintf(fp, "%d  %d  %f  %f  %d\n", SeedDay, GrowDays, db_Residue[rrr][yyy][i], MaxPlantN, wwww);
					fprintf(fp, "%f  %d  %f  %f  %f\n", db_TreeAge[rrr][yyy][i], db_Transplant[rrr][yyy][i], 
						db_RepRate[rrr][yyy][i], db_PsnEff[rrr][yyy][i], db_PsnMax[rrr][yyy][i]);
					fprintf(fp, "%d\n", db_CoverCrop[rrr][yyy][i]);
					fprintf(fp, "%d\n", db_PerennialCrop[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f\n", db_GrainFraction[rrr][yyy][i], db_LeafFraction[rrr][yyy][i], db_ShootFraction[rrr][yyy][i], db_RootFraction[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f\n", db_GrainCN[rrr][yyy][i], db_LeafCN[rrr][yyy][i], db_ShootCN[rrr][yyy][i], db_RootCN[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f %f\n", db_TDD[rrr][yyy][i], db_Water[rrr][yyy][i], db_OptT[rrr][yyy][i], db_Nfix[rrr][yyy][i], db_Vascularity[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f\n", db_TreeAge[rrr][yyy][i], db_TreeCurrentAge[rrr][yyy][i], db_TreeLeafMax[rrr][yyy][i], db_TreeLeafMin[rrr][yyy][i]);
					fprintf(fp, "%d %f\n", db_RootShape[rrr][yyy][i], db_GrainFill[rrr][yyy][i]);
					fprintf(fp, "%f %f\n", db_LAImax[rrr][yyy][i], db_FrostKill[rrr][yyy][i]);
					fprintf(fp, "%f %f %f %f\n", db_AlfCHRMX[rrr][yyy][i], db_ALFCDRMX[rrr][yyy][i], db_ALFCTMX[rrr][yyy][i], db_ALFPDFMX[rrr][yyy][i]);
					fprintf(fp, "%f %f\n", db_Root1[rrr][yyy][i], db_Root2[rrr][yyy][i]);
					fprintf(fp, "%f %f\n", db_AGResp1[rrr][yyy][i], db_AGResp2[rrr][yyy][i]);
					fprintf(fp, "%f %f %f\n", v_Kext1[db_YrCropType[rrr][yyy][i]], v_Kext2[db_YrCropType[rrr][yyy][i]], v_CMaxH[db_YrCropType[rrr][yyy][i]]);
					fprintf(fp, "%f %f %f %f\n", db_cropGRate[rrr][yyy][i], db_cropTime[rrr][yyy][i], db_RUEHI[rrr][yyy][i], db_DelayP[rrr][yyy][i]);//might be problematic here
				//	fprintf(fp, "%f %f %f\n", db_Kext1[rrr][yyy][i], db_Kext2[rrr][yyy][i], db_cropHeight[rrr][yyy][i]);
	
				}				
			}
			fclose (fp);
			///////////////////////////////////////////////////////////
		}

	}

    int CropNumbers;
	char Crop_Name[100];
    yr = 0;
    for (i = 1;i<=db_Rotation_Number;i++) 
	{
        kkk = 0;
        for (j = 1;j<=db_RotateSpan[i];j++) //total years within a rotation
		{
            yr++;
			kkk++;
        
            // Open output crop file
			
			sprintf(outname,"%s\\crop-%d",FCT100,yr);
			fcrop=sopen(outname, "w");
			if(fcrop==NULL) note(1, outname);            

			sprintf(fname,"%s\\cyc-%d_%d",FCT0,i,kkk);
			fpi=sopen(fname, "r");
			if (fpi==NULL) note(0, fname);
			            
			fscanf(fpi, "%d", &CropNumbers);
			fprintf(fcrop, "%d\n", CropNumbers);

            for (k = 1;k<=CropNumbers;k++) 
			{
				fscanf(fpi, "%d  %s  %d  %d  %f  %d", 
					&CYr[1].CropID, Crop_Name, &CYr[1].WCFlag, &CYr[1].Left, &CYr[1].Yield, 
					&CYr[1].HarYr);
				fscanf(fpi, "%d  %d  %f  %f  %d", 
					&CYr[1].SeedDay, &CYr[1].GrowDays, &CYr[1].LeftPrec, 
					&CYr[1].MaxPlanN, &CYr[1].CropOrder);
				fscanf(fpi, "%f  %d  %f  %f  %f", 
					&CYr[1].TreeAge, &CYr[1].Transplant, &CYr[1].GrowthReproductive, 
					&CYr[1].PsnEfficiency, &CYr[1].PsnMax);
				fscanf(fpi, "%d", &CYr[1].CoverCrop);
				fscanf(fpi, "%d", &CYr[1].PerennialCrop);

				fscanf(fpi, "%f %f %f %f", &CYr[1].Grain, &CYr[1].Leaf, &CYr[1].Straw, &CYr[1].Root);
				fscanf(fpi, "%f %f %f %f", &CYr[1].GrainCN, &CYr[1].LeafCN, &CYr[1].ShootCN, &CYr[1].RootCN);
				fscanf(fpi, "%f %f %f %f %f", &CYr[1].CropTDD, &CYr[1].WRuq, &CYr[1].OptT, 
					&CYr[1].CropNFix, &CYr[1].Vascularity);
				fscanf(fpi, "%f %f %f %f", &CYr[1].TreeAge, &CYr[1].TreeCurrentAge, &CYr[1].TreeLeafMax, &CYr[1].TreeLeafMin);
				fscanf(fpi, "%d %f", &CYr[1].RootShape, &CYr[1].GrainFill);
				fscanf(fpi, "%f %f", &CYr[1].LAImax, &CYr[1].FrostKill);
				fscanf(fpi, "%f %f %f %f", &CYr[1].AlfCHRMX, &CYr[1].ALFCDRMX, &CYr[1].ALFCTMX, &CYr[1].ALFPDFMX);
				fscanf(fpi, "%f %f", &CYr[1].Root1, &CYr[1].Root2);
				fscanf(fpi, "%f %f", &CYr[1].ShootResp1, &CYr[1].ShootResp2);
				fscanf(fpi, "%f %f %f", &CYr[1].kExt1, &CYr[1].kExt2, &CYr[1].cropMH);
				fscanf(fpi, "%f %f %f %f", &CYr[1].cropGrate, &CYr[1].croptime, &CYr[1].RUEHi, &CYr[1].delayp);
				if(CYr[1].CropID==0) CYr[1].HarYr=1;

				CYr[1].WCFlag = 0;
				CYr[1].Left = 0;


				fprintf(fcrop, "%d  %s  %d  %d  %f  %d\n", 
				CYr[1].CropID, Crop_Name, CYr[1].WCFlag, CYr[1].Left, CYr[1].Yield, CYr[1].HarYr);
				fprintf(fcrop, "%d  %d  %f  %f  %d\n", 
				CYr[1].SeedDay, CYr[1].GrowDays, CYr[1].LeftPrec, 
				CYr[1].MaxPlanN, CYr[1].CropOrder);
				fprintf(fcrop, "%f  %d  %f  %f  %f\n", 
				CYr[1].TreeAge, CYr[1].Transplant, CYr[1].GrowthReproductive, 
				CYr[1].PsnEfficiency, CYr[1].PsnMax);
				fprintf(fcrop, "%d\n", CYr[1].CoverCrop);
				fprintf(fcrop, "%d\n", CYr[1].PerennialCrop);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].Grain, CYr[1].Leaf, CYr[1].Straw, CYr[1].Root);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].GrainCN, CYr[1].LeafCN, CYr[1].ShootCN, CYr[1].RootCN);
				fprintf(fcrop, "%f %f %f %f %f\n", CYr[1].CropTDD, CYr[1].WRuq, CYr[1].OptT, CYr[1].CropNFix, CYr[1].Vascularity);			
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].TreeAge, CYr[1].TreeCurrentAge, CYr[1].TreeLeafMax, CYr[1].TreeLeafMin);
				fprintf(fcrop, "%d %f\n",CYr[1].RootShape , CYr[1].GrainFill);
				fprintf(fcrop, "%f %f\n", CYr[1].LAImax, CYr[1].FrostKill);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].AlfCHRMX, CYr[1].ALFCDRMX, CYr[1].ALFCTMX, CYr[1].ALFPDFMX);
				fprintf(fcrop, "%f %f\n", CYr[1].Root1, CYr[1].Root2);
				fprintf(fcrop, "%f %f\n", CYr[1].ShootResp1, CYr[1].ShootResp2);
				fprintf(fcrop, "%f %f %f\n", CYr[1].kExt1, CYr[1].kExt2, CYr[1].cropMH);
				fprintf(fcrop, "%f %f %f %f\n", CYr[1].cropGrate, CYr[1].croptime, CYr[1].RUEHi, CYr[1].delayp);
			}

            fclose (fpi);
            fclose (fcrop);
                        
            // output Tillage data
			//sprintf(fname,"%s\\Inter\\ti-%d_%d",OUTPUT,i,kkk);
			sprintf(fname,"%s\\ti-%d_%d",FCT0,i,kkk);
			//sprintf(outname,"%s\\Inputs\\till-%d",OUTPUT,yr);
			sprintf(outname,"%s\\till-%d",FCT100,yr);
			FileCopy(fname,outname);

            // output Fertilization data
			
			sprintf(fname,"%s\\fe-%d_%d",FCT0,i,kkk);			
			sprintf(outname,"%s\\fert-%d",FCT100,yr);
			FileCopy(fname,outname);
            
            // output Manure data
			//sprintf(fname,"%s\\Inter\\ma-%d_%d",OUTPUT,i,kkk);
			sprintf(fname,"%s\\ma-%d_%d",FCT0,i,kkk);
			//sprintf(outname,"%s\\Inputs\\manu-%d",OUTPUT,yr);
			sprintf(outname,"%s\\manu-%d",FCT100,yr);
			FileCopy(fname,outname);
           
            // output Flooding data
			
			sprintf(fname,"%s\\fl-%d_%d",FCT0,i,kkk);
			//sprintf(outname,"%s\\Inputs\\flood-%d",OUTPUT,yr);
			sprintf(outname,"%s\\flood-%d",FCT100,yr);
			FileCopy(fname,outname);
            
            // output Irrigation data
			sprintf(fname,"%s\\ir-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\irri-%d",FCT100,yr);
			FileCopy(fname,outname);

			//output Controlled Drainage Data
			sprintf(fname,"%s\\cd-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\cdrain-%d",FCT100,yr);
			FileCopy(fname,outname);

			//output Additional Parameter Data
			sprintf(fname,"%s\\extra-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\extra-%d",FCT100,yr);
			FileCopy(fname,outname);
            
            // output Weeding data
			//sprintf(fname,"%s\\Inter\\we-%d_%d",OUTPUT,i,kkk);
			sprintf(fname,"%s\\pl-%d_%d",FCT0,i,kkk);
			sprintf(outname,"%s\\plastic-%d",FCT100,yr);
			FileCopy(fname,outname);

            // output Grazing data
			//sprintf(fname,"%s\\Inter\\gr-%d_%d",OUTPUT,i,kkk);
			sprintf(fname,"%s\\gr-%d_%d",FCT0,i,kkk);
			//sprintf(outname,"%s\\Inputs\\graz-%d",OUTPUT,yr);
			sprintf(outname,"%s\\graz-%d",FCT100,yr);
			FileCopy(fname,outname);

			// output grass cutting data
			//sprintf(fname,"%s\\Inter\\cut-%d_%d",OUTPUT,i,kkk);
			sprintf(fname,"%s\\cut-%d_%d",FCT0,i,kkk);
			//sprintf(outname,"%s\\Inputs\\cut-%d",OUTPUT,yr);
			sprintf(outname,"%s\\cut-%d",FCT100,yr);
			FileCopy(fname,outname);

            if (kkk == db_CycleSpan[i]) kkk = 0;
    
        }
    }
    
	char F_INI[200];
	FILE *fpp;
	sprintf(F_INI, "%s\\Inputs\\cropini-1", OUTPUT);    
	fpp = fopen(F_INI, "w");
	if (fpp == NULL) note(1, F_INI); 
	fprintf(fpp, "%d\n", 0);
	fclose( fpp );
}
    return 0;
    
}


int SaveInterFarmParas()
{
	int rrr, yyy;
	int result = -1;
    char fname[255];
	FILE *fp;
    int i, n, day, db_Rotation_Number, db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20];
		
	int TillID[300], TillMonth[300], TillDay[300], TillMethod[300];
	int FertMonth[300], FertDay[300], FertMethod[300];
	float FertNitrate[300], FertAbi[300], FertUrea[300], FertAnh[300], FertAmNi[300], NH42SO4[300], NH42HPO4[300], FertDepth[300];
	int ManuMonth[300], ManuDay[300], ManuType[300], ManuMethod[300], FertOption=0, ManureAppHour[300],UseManPool[300],AutoManure;
	float ManuAmount[300], ManuCN[300], ManuN[300], ManureDepth[300], ManureNH4[300], ManureNO3[300],ManureDM[300],ManurePH[300],ManPoolFrac[300], ManPoolRate[300];
	float DayRelease[300], NIefficiency[300], NIduration[300];
	float UreaseEfficiency[300], UreaseDuration[300];
	int WeedMonth1[300], WeedDay1[300], WeedMonth2[300], WeedDay2[300];
	float CoverFraction[300];
	int FlooID[300], FlooMonth1[300], FlooDay1[300], FlooMonth2[300], FlooDay2[300];
	float FlooN[300];
	int ShallowFlood[300];
	int IrriMonth[366], IrriDay[366], irrimethod[366];
	int CDrainA[366],DrainMonth[366],DrainDay[366],DrainMonth2[366],DrainDay2[366],TileIrriDays[366];
	float CDrainDepth[366];
	float IrriAmount[366];
	int GrazMonth1[300], GrazDay1[300], GrazMonth2[300], GrazDay2[300];
	float GrazHour[300], Dairy[300], Beef[300], Pig[300], Horse[300], Sheep[300], AddFeed[300], FeedCN[300],GrazBiomass[300],GrazCConsume[300],GrazCExcrete[300];
	int CutMonth[300], CutDay[300], CutPart[300], Excreta[300];
	float CutAmount[300];
	char Fertigation[200];
	float WaterGetherIndex, WaterLeakRate;
	float m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex,m_SurfOutflowIntensity, m_GroundOutflowIntensity;

#ifdef MANURE
	int CropIDID, ManureCropOrder;
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureFieldCrops", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d", &TotalFarmFields, &CropIDID);
	fclose(xff);
	//FCT0.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	//FCT0.Format("%s", INTERMANAGE);
	TotalFarmFields = 1;
#endif

for(int MFFC=1; MFFC<=TotalFarmFields; MFFC++)
{
#ifdef MANURE
	FCT0.Format("%s_%d", INTERMANAGE, MFFC);
#else 
	FCT0.Format("%s_1", INTERMANAGE);
#endif

	CString DB;
	FILE *db;

	DB.Format("%s\\CropRotation.txt", FCT0);
	db=fopen(DB, "r");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not open file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(db, "%d", &db_Rotation_Number);
	fclose(db);

	for(rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		DB.Format("%s\\CropRotation_%d.txt", FCT0, rrr);//read: SaveInterFarmParas
		db=fopen(DB, "r");
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);

		for(yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
		{    
			// Save tillage
			DB.Format("%s\\CropTill_%d_%d.txt", FCT0, rrr, yyy);
			db=fopen(DB, "r");
			fscanf(db, "%d", &n);
			for(i=1; i<=n; i++)
			{
				TillID[i] = i;
				fscanf(db, "%d %d %d", &TillMonth[i], &TillDay[i], &TillMethod[i]);
			}
			fclose(db);
	
			sprintf(fname,"%s\\ti-%d_%d",FCT0,rrr,yyy);
			fp=sopen(fname, "w");
			if (fp == NULL) return result;
    
   			fprintf(fp,"%d\n",n);
			for (i = 1;i<=n;i++) 
			{		
				day = JulianDay(TillMonth[i], TillDay[i]);
				fprintf(fp,"%d %d\n",day,TillMethod[i]);
			}
			fclose (fp);
    
    // Save fertilization
	DB.Format("%s\\CropFert_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
	if(n==-1)
	{
		fscanf(db, "%s", Fertigation);
	}
	else if (n == -2)
	{
		for (i = 1; i <= 2; i++)
		{
			fscanf(db, "%d %d %d", &FertMonth[i], &FertDay[i], &FertMethod[i]);
			fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[i], &FertAbi[i], &FertUrea[i], &FertAnh[i], &FertAmNi[i],
				&NH42SO4[i], &NH42HPO4[i], &FertDepth[i]);
			fscanf(db, "%f %f %f %f %f", &DayRelease[i], &NIefficiency[i], &NIduration[i], &UreaseEfficiency[i], &UreaseDuration[i]);
		}
		fscanf(db, "%d", &FertOption);
	}
	else
	{
		for(i=1; i<=n; i++)
		{
			fscanf(db, "%d %d %d", &FertMonth[i], &FertDay[i], &FertMethod[i]);
			fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[i], &FertAbi[i], &FertUrea[i], &FertAnh[i], &FertAmNi[i], 
				&NH42SO4[i], &NH42HPO4[i], &FertDepth[i]);
			fscanf(db, "%f %f %f %f %f", &DayRelease[i], &NIefficiency[i], &NIduration[i],&UreaseEfficiency[i], &UreaseDuration[i]);
		}
		fscanf(db, "%d", &FertOption);
		
	}
	fclose(db);

	sprintf(fname,"%s\\fe-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, "w");
    if (fp == NULL) note(1, fname);
    
    fprintf(fp,"%d\n", n);
	if(n==-1)
	{
		fprintf(fp,"%s\n", Fertigation);
	}
	else if (n == -2)
	{
		for (i = 1; i <= 2; i++)
		{
			day = JulianDay(FertMonth[i], FertDay[i]);
			if (day < 0)day = 0;
			fprintf(fp, "%d %f\n", day, FertDepth[i] * 0.01);
			fprintf(fp, "%f %f %f %f %f %f %f\n", FertNitrate[i], FertAbi[i], FertUrea[i], FertAnh[i], FertAmNi[i], NH42SO4[i], NH42HPO4[i]);
			fprintf(fp, "%d %f %f %f %f %f %d\n", FertOption, DayRelease[i], NIefficiency[i], NIduration[i], UreaseEfficiency[i], UreaseDuration[i], FertMethod[i]);//added FertMethod 0=surface , 1= Inject , 2=Incorporate, FertOption== 0=manual etc.);
		}

	}
	else
	{
		for (i = 1; i<=n;i++) 
		{
			day = JulianDay(FertMonth[i], FertDay[i]);
			fprintf(fp,"%d %f\n", day, FertDepth[i]*0.01);			
			fprintf(fp,"%f %f %f %f %f %f %f\n", FertNitrate[i], FertAbi[i], FertUrea[i], FertAnh[i], FertAmNi[i], NH42SO4[i], NH42HPO4[i]); 
			fprintf(fp,"%d %f %f %f %f %f %d\n", FertOption, DayRelease[i], NIefficiency[i], NIduration[i],UreaseEfficiency[i], UreaseDuration[i],FertMethod[i]);//added FertMethod 0=surface , 1= Inject , 2=Incorporate, FertOption== 0=manual etc.
		}		
	}
    fclose (fp);
    
        // Save Manuring file
	//DB.Format("%s\\Inter\\CropManu_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropManu_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
	for(i=1; i<=n; i++)
		{
			fscanf(db, "%d %d", &ManuMonth[i], &ManuDay[i]);
			fscanf(db, "%f %f %d %d %f", &ManuAmount[i], &ManuCN[i], &ManuType[i], &ManuMethod[i], &ManureDepth[i]);
			fscanf(db, "%f %f %f %d %f %f %f %f %d %d", &ManuN[i], &ManureNH4[i], &ManureNO3[i], &ManureAppHour[i], &ManureDM[i], &ManurePH[i], &ManPoolFrac[i], &ManPoolRate[i], &UseManPool[i], &AutoManure);//added new manure parameters
			
		}
	fclose(db);

    //sprintf(fname,"%s\\Inter\\ma-%d_%d",OUTPUT,rrr,yyy);
	sprintf(fname,"%s\\ma-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;
    
    fprintf(fp,"%d\n", n);
    for (i = 1; i<=n; i++) 
	{
        day = JulianDay(ManuMonth[i], ManuDay[i]);
		
        fprintf(fp,"%d %f %f %d %d %f %f %f %f %d %f %f %f %f %d %d\n", 
			day, 
			ManuAmount[i],
			ManuCN[i], 
			ManuType[i],
			ManuMethod[i],
			ManureDepth[i],
			ManuN[i], ManureNH4[i], ManureNO3[i], ManureAppHour[i], ManureDM[i], ManurePH[i], ManPoolFrac[i], ManPoolRate[i], UseManPool[i], AutoManure);
    }
    fclose (fp);
        
    // Save plastic file
	int WeedOption;
	
	DB.Format("%s\\CropPlastic_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &n, &WeedOption);
	for(i=1; i<=n; i++)
	{
		fscanf(db, "%d %d", &WeedMonth1[i], &WeedDay1[i]);
		fscanf(db, "%d %d", &WeedMonth2[i], &WeedDay2[i]);
		fscanf(db, "%f", &CoverFraction[i]);
	}
	fclose(db);

	sprintf(fname,"%s\\pl-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;
    
    fprintf(fp, "%d %d\n",n, WeedOption);
    for (i = 1; i<=n;i++) 
	{
        int day1 = JulianDay(WeedMonth1[i], WeedDay1[i]);
		int day2 = JulianDay(WeedMonth2[i], WeedDay2[i]);
        fprintf(fp,"%d %d\n",day1, day2);
		fprintf(fp,"%f\n",CoverFraction[i]);
    }
    fclose (fp);
    
        // Save Flooding file
	int WaterControl;
	float FloodWaterN;
	CString WT_file;
	//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropFloo_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d %f %d %f", &n, &FloodWaterN, &WaterControl, &WaterLeakRate);
	for(i=1; i<=n; i++)
		{
			FlooID[i] = i;
			fscanf(db, "%d %d", &FlooMonth1[i], &FlooDay1[i]);
			fscanf(db, "%d %d", &FlooMonth2[i], &FlooDay2[i]);
			fscanf(db, "%f", &FlooN[i]);
			fscanf(db, "%d", &ShallowFlood[i]);
		}

	fscanf(db, "%f", &WaterGetherIndex);
	fscanf(db, "%s", WT_file);

	fscanf(db, "%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
												&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);
	
	fclose(db);

    
	sprintf(fname,"%s\\fl-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;

	fprintf(fp,"%d\n", n);

    for (i = 1; i<=n;i++) 
	{
        day = JulianDay(FlooMonth1[i], FlooDay1[i]);		
        fprintf(fp, "%d ",day);
        day = JulianDay(FlooMonth2[i], FlooDay2[i])+1;	
        fprintf(fp, "%d\n",day);
		fprintf(fp, "%f %d\n", FlooN[i], ShallowFlood[i]);
    }
	
    fprintf(fp, "%d %f %f %f\n", WaterControl, WaterLeakRate, WaterGetherIndex, FloodWaterN);
	fprintf(fp, "%s\n",WT_file);
	fprintf(fp, "%f %f %f %f %f %f\n",m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, m_SurfOutflowIntensity, m_GroundOutflowIntensity);
    fclose (fp);

	     
    // Save Irrigation file
	int IrrMode;
	float IrrIndex;
	
	DB.Format("%s\\CropIrri_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d %d %f %d", &n, &IrrMode, &IrrIndex, &irrimethod[0]);
	for(i=1; i<=n; i++)
		{
			fscanf(db, "%d %d", &IrriMonth[i], &IrriDay[i]);
			fscanf(db, "%f %d %d", &IrriAmount[i], &irrimethod[i],&TileIrriDays[i]);
		}
	fclose(db);

	sprintf(fname,"%s\\ir-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;

    fprintf(fp,"%d %f %d\n", n, IrrIndex, irrimethod[0]);
    
	for (i=1; i<=n;i++) 
	{
        day = JulianDay(IrriMonth[i], IrriDay[i]);
		
        fprintf(fp,"%d %f %d %d\n", day, IrriAmount[i], irrimethod[i],TileIrriDays[i]);
    }
    //fprintf(fp," %d", cycle.get(rn, cn)->IrrIndex);
    fclose (fp);
    
//Save Controlled Drainage File

	DB.Format("%s\\CTDrain_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);//scan the number of drainage
			for (i = 1; i<=n;i++) 
			{
				fscanf(db, "%d %d", &DrainMonth[i], &DrainDay[i]);
				fscanf(db, "%d %d %f", &DrainMonth2[i], &DrainDay2[i],&CDrainDepth[i]);
			}
	fclose(db);
//write out interm drainage file for later reading
	sprintf(fname,"%s\\cd-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;

    fprintf(fp,"%d\n", n);
    int dayst,dayend;
	for (i=1; i<=n;i++) 
	{
        dayst = JulianDay(DrainMonth[i], DrainDay[i]);
		dayend=JulianDay(DrainMonth2[i], DrainDay2[i]);
        fprintf(fp,"%d %d %f\n", dayst, dayend, CDrainDepth[i]);
    }
    
    fclose (fp);

	//save Extra Inputs File

//write out interm drainage file for later reading
	sprintf(fname,"%s\\extra-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;

    fprintf(fp,"%f\n", IData.DrainDepth);
	fprintf(fp,"%f\n", IData.DrainSpace);
	fprintf(fp,"%f\n", IData.DrainRad);
	fprintf(fp,"%f\n", IData.DrainBed);
	fprintf(fp,"%f\n", IData.keDrain);
	fprintf(fp,"%f\n", IData.MaxNMove);
	fprintf(fp,"%f\n", IData.MobileNF);
	fprintf(fp,"%f\n", IData.NLayerF);
	fprintf(fp,"%f\n", IData.NMoveRate);
	fprintf(fp,"%f\n", IData.SoilEvapF);
	fprintf(fp,"%f\n", IData.RunOffWF);
	fprintf(fp,"%f\n", IData.RunOffNF);
	fprintf(fp,"%f\n", IData.Factor1);//nitrification 2 multi
	fprintf(fp,"%f\n", IData.Factor2);
	fprintf(fp,"%f\n", IData.Factor3);
	fprintf(fp,"%f\n", IData.DenitGRate);
	fprintf(fp,"%f\n", IData.NitGRate);
	fprintf(fp,"%f\n", IData.N2ORain);
	fprintf(fp,"%f\n", IData.SprMeltF);
	fprintf(fp,"%f\n", IData.Factor4);
	fprintf(fp,"%f\n", IData.Factor5);
	fprintf(fp,"%f\n", IData.Factor6);
	fprintf(fp,"%d\n", IData.Factor7);
	fprintf(fp,"%f\n", IData.Factor8);
	fprintf(fp,"%f\n", IData.Factor9);
	fprintf(fp,"%d\n", IData.SpinUpCheck);
	if (IData.SpinUpCheck == 0)
	{
		IData.SpinUpFileName = " ";
	}
	fprintf(fp,"%d\n", IData.SpinUpYears);
	fprintf(fp, "%s\n", IData.SpinUpFileName);
	fprintf(fp, "%d\n", IData.CO2file);
	if(IData.CO2file==0)
	{
		IData.CO2FileName = " ";
	}

	fprintf(fp, "%s\n", IData.CO2FileName);
	fprintf(fp, "%f\n", IData.Factor10);
	fprintf(fp, "%f\n", IData.Factor11);
	fprintf(fp, "%f\n", IData.Factor13);
	fprintf(fp, "%f\n", IData.UreaHydro);
	fprintf(fp, "%f\n", IData.UreaHydro2);
	fprintf(fp, "%f\n", IData.NH3SoilDF);
	fprintf(fp, "%f\n", IData.UreaDifF);
	fprintf(fp, "%f\n", IData.N2N2OF);
	fprintf(fp, "%d\n", IData.SpinUpCheck2);
	fprintf(fp, "%d\n", IData.OBSYield);
	if (IData.OBSYield == 0)
	{
		IData.OBSYieldFileName = " ";
	}
	fprintf(fp, "%s\n", IData.OBSYieldFileName);
	fprintf(fp, "%d\n", IData.AutoPlant);
	fprintf(fp, "%d\n", IData.PrefFlowCheck);
	fprintf(fp, "%f\n", IData.PrefFlowDepth);
	fprintf(fp, "%f\n", IData.PrefFlowRecov);

    fclose (fp);

	
        // Save Grazing file
	
	//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropGraz_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
		for(i=1; i<=n; i++)
		{
			fscanf(db, "%d %d", &GrazMonth1[i], &GrazDay1[i]);
			fscanf(db, "%d %d", &GrazMonth2[i], &GrazDay2[i]);
			fscanf(db, "%f", &GrazHour[i]);
			fscanf(db, "%f %f %f %f %f", &Dairy[i], &Beef[i], &Pig[i], &Sheep[i], &Horse[i]);
			fscanf(db, "%f %f %d", &AddFeed[i], &FeedCN[i], &Excreta[i]);
			fscanf(db, "%f %f %f", &GrazBiomass[i], &GrazCConsume[i], &GrazCExcrete[i]);
		}
	fclose(db);

    //sprintf(fname,"%s\\Inter\\gr-%d_%d",OUTPUT,rrr,yyy);
	sprintf(fname,"%s\\gr-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;

    fprintf(fp, "%d\n", n);
	int bt,et;
    for (i = 1; i<=n; i++)
    {
		bt=JulianDay(GrazMonth1[i], GrazDay1[i]);
		et=JulianDay(GrazMonth2[i], GrazDay2[i]);
		fprintf(fp, "%d %d %f %f %f %f %f %f %f %f %d %f %f %f\n",bt,et,Dairy[i], Beef[i], Pig[i], Sheep[i],Horse[i],
			GrazHour[i], AddFeed[i], FeedCN[i], Excreta[i],GrazBiomass[i],GrazCConsume[i],GrazCExcrete[i]);
			
    }
    fclose(fp);

	// Save garss cutting file
	//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\GrassCut_%d_%d.txt", FCT0, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &n);
		for(i=1; i<=n; i++)
		{
			fscanf(db, "%d %d", &CutMonth[i], &CutDay[i]);
			fscanf(db, "%f", &CutAmount[i]);
			fscanf(db, "%d", &CutPart[i]);
		}
	fclose(db);

    //sprintf(fname,"%s\\Inter\\cut-%d_%d",OUTPUT,rrr,yyy);
	sprintf(fname,"%s\\cut-%d_%d",FCT0,rrr,yyy);
	fp=sopen(fname, 0);
    if (fp == NULL) return result;

    fprintf(fp, "%d\n", n);
    for (i = 1; i<=n; i++)
    {
		bt=JulianDay(CutMonth[i], CutDay[i]);
		fprintf(fp, "%d %f\n",bt, CutAmount[i]);
		fprintf(fp, "%d\n", CutPart[i]);
    }
    fclose(fp);
	}
	}
}
    //result = 1;
    return (0);
}


int savetillage(FILE *fp,TillageParameter *tp)//,int n)
{
    int   day;
	float mtd;
    
	day = JulianDay(tp->month, tp->day);//till.get(rn, cn, i)
	if (day<0) {
		MessageBox(NULL,"Tillage time is wrong!","Input Error:",0);
		fclose(fp);
		return -1;
	}

    if (tp->method == 1) //till.get(rn, cn, i)
		mtd = 0;
    else if (tp->method == 2)//till.get(rn, cn, i) 
		mtd = (float)0.05;
    else if (tp->method == 3) //till.get(rn, cn, i)
		mtd = (float)0.1;
    else if (tp->method == 4) //till.get(rn, cn, i)
		mtd = (float)0.2;
	else if (tp->method == 5) 
		mtd = (float)0.3;
	else {
		MessageBox(NULL,"2. Tillage method is wrong!","Input Error:",0);
		fclose(fp);
		return -1;
	}
    fprintf(fp,"%d %f\n",day,mtd);
	return 0;
}

/*DNDCSystem::DNDCSystem()
{
	Mode			= 1;
	MSite			= 0;
	Country			= 1;
	Province		= 1;
	lit_back_field	= 0.2;
    animal_manure	= 0.6;
    human_manure	= 0.1;
	IrrIndex		= 1;

	FertMode        = 0;//0:county-specified,1:crop-specified
	Fertilizer		= 1;
//	Manure			= 0;
	CO2				= 350;
	Rainfall		= 1;
	Temp			= 0;

	ColorNum		= 256;

	ShowCnty = "NO";
	Sort[0]	 = 0;
	Sort[1]	 = -1;
	Sort[2]	 = -1;
	ViewIndex[0] =  0;
	ViewIndex[1] = -1; 
	ViewIndex[2] = -1;
	Type[0]		    = 0;
	Type[1]		    = 0;
	Type[2]		    = 0;
	MMM[0] = 0; //0:min,1:max,2:average
	MMM[1] = 0;
	MMM[2] = 0;
	deLog  = 0;
	ifLog[0]  = -1;
	ifLog[1]  = -1;
	ifLog[2]  = -1;

	Scenario		= 0;
	VValue			= 0;

	int i;
	for (i=0;i<100;i++)
	{
		Group[0][i]=0;
		Group[1][i]=0;
	}
};
*/

/*DNDCDatabase::DNDCDatabase ()
{
	Country =0;
	
	CountyID=0;
	State	="";
	County	="";
	Latitude=0;
	Longitude=0;

	CliFile	="";
	NO3		=0;

	SOCMax=0;
	SOCMin=0;
	ClayMax=0;
	ClayMin=0;
	pHMax=0;
	pHMin=0;
	DMax=0;
	DMin=0;

	CropLand=0;
	Sown=0;
	NFer=0;
	NRate=0;
	IrrInd=0;
	W_C=0;
	WWT=0;
	CRN=0;
	R_R=0;
	R_1=0;
	RAP=0;
	SWT=0;
	POT=0;
	SOR=0;
	CER=0;
	W_R=0;
	SOY=0;
	COT=0;
	TOB=0;
	SUG=0;
	BET=0;
	GRE=0;
	VEG=0;
	R_2=0;
	FAL=0;
	PAS=0;
	N_HAY=0;
	L_HAY=0;

	MapID="";

	Beef=0;
	Horse=0;
	Pig=0;
	Sheep=0;
	Dairy=0;
}*/

void RecordManureFiles()
{
	char SF[300], TF[300];
	int m_FeedLots, i;
	char TotalFeedlots[300];
	FILE *TFL;

	for(int m_FeedlotYear=1; m_FeedlotYear<=IData.years; m_FeedlotYear++)
	{
	sprintf(TotalFeedlots, "%s\\Inter\\TotalFeedLots_%d", OUTPUT, m_FeedlotYear);
	TFL=fopen(TotalFeedlots, "r");
	if(TFL==NULL) note(0, TotalFeedlots);
	fscanf(TFL, "%d", &m_FeedLots);
	fclose(TFL);

	sprintf(TF, "%s\\Inputs\\TotalFeedLots_%d", OUTPUT, m_FeedlotYear);
	FileCopy(TotalFeedlots, TF);

	for(i=1; i<=m_FeedLots; i++)
	{
		sprintf(SF, "%s\\Inter\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
		sprintf(TF, "%s\\Inputs\\ManureHouse_%d_%d.txt", OUTPUT, m_FeedlotYear, i);
		FileCopy(SF, TF);
	}
	}

	//sprintf(SF, "%s\\Inter\\ManurePen.txt", OUTPUT);
	//sprintf(TF, "%s\\Inputs\\ManurePen.txt", OUTPUT);
	//FileCopy(SF, TF);
	//sprintf(SF, "%s\\Inter\\ManureGraze.txt", OUTPUT);
	//sprintf(TF, "%s\\Inputs\\ManureGraze.txt", OUTPUT);
	//FileCopy(SF, TF);
	int m_LagoonYears;
	for (int m_LagoonYears = 1; m_LagoonYears <= IData.years; m_LagoonYears++)
	{
		sprintf(SF, "%s\\Inter\\ManureLagoon_%d.txt", OUTPUT,m_LagoonYears);
		sprintf(TF, "%s\\Inputs\\ManureLagoon_%d.txt", OUTPUT,m_LagoonYears);
		FileCopy(SF, TF);
	}
	sprintf(SF, "%s\\Inter\\ManureCompost.txt", OUTPUT);
	sprintf(TF, "%s\\Inputs\\ManureCompost.txt", OUTPUT);
	FileCopy(SF, TF);
	sprintf(SF, "%s\\Inter\\ManureDigester.txt", OUTPUT);
	sprintf(TF, "%s\\Inputs\\ManureDigester.txt", OUTPUT);
	FileCopy(SF, TF);
	sprintf(SF, "%s\\Inter\\ManureField.txt", OUTPUT);
	sprintf(TF, "%s\\Inputs\\ManureField.txt", OUTPUT);
	FileCopy(SF, TF);

}



 