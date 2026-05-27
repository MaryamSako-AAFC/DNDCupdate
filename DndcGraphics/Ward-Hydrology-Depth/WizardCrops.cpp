// WizardCrops.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "WizardCrops.h"
#include "dndc_main.h"
#include "SitePara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WizardCrops dialog

float WSOCA[6]={0.0,0.2,0.2,0.08,0.05,0.2};
float WSOCB[6]={10.0,2.0,2.0,1.4,4.0,2.0};

WizardCrops::WizardCrops(CWnd* pParent /*=NULL*/)
	: CDialog(WizardCrops::IDD, pParent)
{
	//{{AFX_DATA_INIT(WizardCrops)
	m_SCname = _T("");
	//}}AFX_DATA_INIT
}


void WizardCrops::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WizardCrops)
	DDX_Control(pDX, IDC_WizardCrops, m_WizardCrops);
	DDX_Text(pDX, IDC_SCname, m_SCname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WizardCrops, CDialog)
	//{{AFX_MSG_MAP(WizardCrops)
	ON_CBN_SELCHANGE(IDC_WizardCrops, OnSelchangeWizardCrops)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WizardCrops message handlers

BOOL WizardCrops::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i, crop_ID[90];
		
	CString IDfile;
	FILE *fid;
	
	IDfile.Format("%s\\inter\\WizardSite.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
		CString mess;
		mess.Format("Can not open %s.", IDfile);
		AfxMessageBox(mess);
		exit(0);
	}
	fscanf(fid, "%d  %d", &stateID, &WizardCountyID);
	fscanf(fid, "%s  %s", Sname, Cname);
	i=0;
	for(;;)
	{
		if(fscanf(fid, "%d  %f", &crop_ID[i], &crop_ha[i])!=2) break;
		i++;
	}
	fclose(fid);

	if(crop_ha[11]>0.0&&crop_ha[12]==0.0)
	{
		crop_ha[12] = crop_ha[11] * 0.3;
		crop_ha[11] *= 0.7;
	}

	int id,CropNum,Si=m_WizardCrops.GetCurSel();
	FILE *fp;
	char fname[256],str[256];

	sprintf(fname,"%s\\Library\\lib_crop\\crop.lst", ROOTDIR);
	fp=fopen(fname,"r");
	if (fp==NULL) 
	{
		
		MessageBox("Sorry: Your DNDC70 database of crop preperties is loss","DNDC System file error:",NULL);
		return FALSE;
	}

	m_WizardCrops.ResetContent();
	fscanf(fp,"%d",&CropNum);
	if (CropNum<=0) return FALSE;
	//if (CropNum>0) Cname=new CString[CropNum+1];
	//else {fclose(fp);return -1;}
	for (i=0;i<29;i++)
	{
		if (fscanf(fp,"%d",&id)!=1) break;
		if (fgets(str,250,fp)==NULL) break;
		EraseFBSpace(str);
		sprintf(fname,"%s  (%.0f ha)",str, crop_ha[id]);
		//sprintf(fname,"%12.0f     %-30s", crop_ha[id],str);
		m_WizardCrops.AddString(fname);
		//Cname[i]=str;
	}
	fclose(fp);

	if (Si>=0) m_WizardCrops.SetCurSel(Si);
	
	m_SCname.Format("%s,  %s", Cname, Sname);

	

	UpdateData(FALSE);

	//ShowCountyData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void WizardCrops::OnSelchangeWizardCrops() 
{
	// TODO: Add your control notification handler code here
		
	UpdateData(TRUE);
	CropType = m_WizardCrops.GetCurSel();	
}

void WizardCrops::OnOK() 
{
	// TODO: Add extra validation here

	if(CropType<0)
	{
		AfxMessageBox("Please select a crop for this simulation");
		return;
	}
	else
	{		
		
		CString IDfile;
		FILE* fid;
		IDfile.Format("%s\\Inter\\SelectedCounty.txt", OUTPUT);
		fid = fopen(IDfile, "w");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("2. Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(fid, "%s\n", Sname);
		fprintf(fid, "%s\n", Cname);
		fprintf(fid, "%d\n", CropType);
		fprintf(fid, "%f\n", crop_ha[CropType]);

		fclose(fid);

		SaveDatatoFile();
	}

	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\OpenFile.txt", OUTPUT);
	db=fopen(DB, "w");
	fprintf(db, "%d", 1);
	fclose(db);
	
	CDialog::OnOK();
}

void WizardCrops::SaveDatatoFile()
{
	int i, j, k, n;
	float NO3NH4_Rainfall;
	char ClimateFilename[200], temp[200], jk[200], SiteName[300], ww[300];
	int Soil_Texture, Soil_landuse;
	float Soil_Density, Soil_pH, Soil_OCatSurface;
	float Soil_Clay;

	float SoilBD1, SoilBD2, SoilPH1, SoilPH2, SoilOC1, SoilOC2, SoilCLAY1, SoilCLAY2;
	int SoilTexture1, SoilTexture2;
	float CropResidue[10], FertUrea[10], FertAA[10], FertAN[10];
	float FertAS[10], FertAP[10], FertAB[10], FertNitrate[10], ManureAmount[10], ManureCN[10];

	float IrriAmount[10], CropYield[10], IrriIndex[10];
	int CropSystemID, CropPlantMonth[5], CropPlantDay[5];
	int CropHarvestMonth[5], CropHarvestDay[5], TillMethod[5], TillMonth[5], TillDay[5];
	int FertMonth[10], FertDay[10], FertMethod[10], ManureType[10], ManureMonth[10];
	int ManureDay[10], IrriMonth[366], IrriDay[366], IrriMethod[300];

	int WeedMonth1[10], WeedDay1[10],WeedMonth2[10], WeedDay2[10], WeedProblem;
	int FloodStartMonth[10], FloodStartDay[10];
	int FloodEndMonth[10], FloodEndDay[10], FloodPH[10];
	int WeedTimes, IrriTimes, ManureTimes, FertTimes, TillTimes, FloodTimes;
	int GrazeTimes, GrazeStartMonth[10], GrazeStartDay[10], GrazeEndMonth[10], GrazeEndDay[10];
	float cattle[10], horse[10], sheep[10], hrs[10], FertDepth;
	int CropNumber[10], LeakType;

	CString File1, File2, File3, File4;
	FILE *f1, *f2, *f3, *f4;

	//open data files for reading
	int county_ID1;
	char state_name[200], county_name[200];
	float longitude, latitude;
	File1.Format("%s\\Database\\USA\\GIS\\USA1_%d", ROOTDIR, stateID);
	f1=fopen(File1, "r");
	if (f1==NULL)
	{
		char err[120];
		sprintf(err, "Can not open %s", File1);
		AfxMessageBox(err);
		exit(0); 
	}

	for(;;)
	{
		if (fscanf(f1, "%d %s  %s %f  %f", &county_ID1, state_name, county_name, 
			&longitude, &latitude)!=5)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File1);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			if(WizardCountyID==county_ID1)
			{
				sprintf(SiteName, "%s-%s", state_name, county_name);
				break;
			}
		}
	}
	fclose(f1);

	File2.Format("%s\\Database\\USA\\GIS\\USA2_%d", ROOTDIR, stateID);
	f2=fopen(File2, "r");
	if (f2==NULL)
	{
		CString note;
		note.Format("Can not open file %s", File2);
		AfxMessageBox(note);
		exit(0);
	}

	for(;;)
	{
		if (fscanf(f2, "%d  %s  %f", &county_ID1, temp, &NO3NH4_Rainfall)!=3)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File2);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			sprintf(ClimateFilename, "%s\\Database\\USA\\lib_clim\\%s", ROOTDIR, temp);
			if(WizardCountyID==county_ID1)
			{
				break;
			}
		}
	}
	fclose(f2);

	File3.Format("%s\\Database\\USA\\GIS\\USA3_%d", ROOTDIR, stateID);
	f3=fopen(File3, "r");
	if (f3==NULL)
	{
		CString note;
		note.Format("Can not open file %s", File3);
		AfxMessageBox(note);
		exit(0);
	}

	fgets(ww, 200, f3);
	fgets(ww, 200, f3);

	for(;;)
	{
		if (fscanf(f3, "%d %f %f %f %f %f %f %f %f", &county_ID1, 
			&SoilOC1, &SoilOC2, &SoilCLAY1, &SoilCLAY2, &SoilPH1, &SoilPH2, &SoilBD1, &SoilBD2)!=9)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File2);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			if(WizardCountyID==county_ID1)
			{
				break;
			}
		}
	}
	fclose(f3);

	if(SoilPH1==SoilPH2)
	{
		SoilPH1 += 1.0;
		SoilPH2 -= 1.0;
	}

	Soil_Clay = (SoilCLAY1+SoilCLAY2)*0.5;

	if(CropType==20) Soil_landuse = 2; 
	else if(CropType==11||CropType==22) Soil_landuse = 4;
	else if(CropType==12) Soil_landuse = 3;
	else Soil_landuse = 1;
	
	Soil_Density = (SoilBD1+SoilBD2)*0.5;
	Soil_pH = (SoilPH1+SoilPH2)*0.5;
	Soil_OCatSurface = (SoilOC1+SoilOC2)*0.5;

	if (SoilOC1 >= 0.2) SoilTexture1 = 12;
	else SoilTexture1 = clay_texture(SoilCLAY1);
	
	if (SoilOC2 >= 0.2) SoilTexture2 = 12;
	else SoilTexture2 = clay_texture(SoilCLAY2);
	
	if (Soil_OCatSurface >= 0.2) Soil_Texture = 12;
	else Soil_Texture = clay_texture(Soil_Clay);

/*	CString KK;
	FILE *KKw;
	KK.Format("%s\\Result\\inter\\SoilRanges.txt");
	if ((KKw=fopen(KK,"w"))==NULL) 
	{
		CString note;
		note.Format("Can not create file %s", KK);
		AfxMessageBox(note);
		exit(0);
	}
    
    //fprintf(KKw,"Property   Ave    Max    Min:\n");
    fprintf(KKw,"SOC        %s     %s    %s\n", Soil_OCatSurface, SoilOC1, SoilOC2);
	fprintf(KKw,"Clay       %s     %s    %s\n", Soil_Clay, SoilCLAY1, SoilCLAY2);
	fprintf(KKw,"pH         %s     %s    %s\n", Soil_pH, SoilPH1, SoilPH2);
	fprintf(KKw,"Density    %s     %s    %s\n", Soil_Density, SoilBD1, SoilBD2);
	fprintf(KKw,"Texture    %d     %d    %d\n", Soil_Texture, SoilTexture1, SoilTexture2);
    
	fclose(KKw);
*/	

	File4.Format("%s\\Database\\USA\\\Farming\\farm_crop%d.txt", ROOTDIR, CropType);
	f4=fopen(File4, "r");
	if (f4==NULL)
	{
		char err[120];
		sprintf(err, "Can not open %s", File4);
		AfxMessageBox(err);
		exit(0); 
	}

	fscanf(f4, "%s %d", jk, &CropNumber[1]);
	fscanf(f4, "%s %d", jk, &CropPlantMonth[1]);
	fscanf(f4, "%s %d", jk, &CropPlantDay[1]);
	fscanf(f4, "%s %d", jk, &CropHarvestMonth[1]);
	fscanf(f4, "%s %d", jk, &CropHarvestDay[1]);
	fscanf(f4, "%s %f", jk, &CropResidue[1]);

	fscanf(f4, "%s %d", jk, &TillTimes);
	for(k=1; k<=TillTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &TillMethod[k]);
		fscanf(f4, "%s %d", jk, &TillMonth[k]);
		fscanf(f4, "%s %d", jk, &TillDay[k]);
	}
	

	fscanf(f4, "%s %d", jk, &FertTimes);
	for(k=1; k<=FertTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &FertMonth[k]);
		fscanf(f4, "%s %d", jk, &FertDay[k]);
		fscanf(f4, "%s %d", jk, &FertMethod[k]);
		fscanf(f4, "%s %f", jk, &FertUrea[k]);
		fscanf(f4, "%s %f", jk, &FertAA[k]);
		fscanf(f4, "%s %f", jk, &FertAN[k]);
		fscanf(f4, "%s %f", jk, &FertAS[k]);
		fscanf(f4, "%s %f", jk, &FertAP[k]);
		fscanf(f4, "%s %f", jk, &FertAB[k]);
		fscanf(f4, "%s %f", jk, &FertNitrate[k]);
		//fscanf(f4, "%s %f", jk, &DayRelease[k]);
		//fscanf(f4, "%s %f", jk, &NIefficiency[k]);
		//fscanf(f4, "%s %f", jk, &NIduration[k]);
	}

	fscanf(f4, "%s %d", jk, &ManureTimes);
	for(k=1; k<=ManureTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &ManureType[k]);
		fscanf(f4, "%s %f", jk, &ManureAmount[k]);
		fscanf(f4, "%s %f", jk, &ManureCN[k]);
		fscanf(f4, "%s %d", jk, &ManureMonth[k]);
		fscanf(f4, "%s %d", jk, &ManureDay[k]);
	}

	fscanf(f4, "%s %f", jk, &IrriIndex[1]);
	IrriTimes = 0;

/*
	fscanf(f4, "%s %d", jk, &IrriTimes);
	for(k=1; k<=IrriTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &IrriMonth[k]);
		fscanf(f4, "%s %d", jk, &IrriDay[k]);
		fscanf(f4, "%s %f", jk, &IrriAmount[k]);
		fscanf(f4, "%s %f", jk, &IrriN[k]);

	}*/

	fscanf(f4, "%s %d", jk, &FloodTimes);
	
	for(k=1; k<=FloodTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &LeakType);
		fscanf(f4, "%s %d", jk, &FloodStartMonth[k]);
		fscanf(f4, "%s %d", jk, &FloodStartDay[k]);
		fscanf(f4, "%s %d", jk, &FloodEndMonth[k]);
		fscanf(f4, "%s %d", jk, &FloodEndDay[k]);
		fscanf(f4, "%s %f", jk, &FloodPH[k]);
	}

	fscanf(f4, "%s %d", jk, &WeedTimes);
	for(k=1; k<=WeedTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &WeedMonth1[k]);
		fscanf(f4, "%s %d", jk, &WeedDay1[k]);
		fscanf(f4, "%s %d", jk, &WeedMonth2[k]);
		fscanf(f4, "%s %d", jk, &WeedDay2[k]);
		fscanf(f4, "%s %d", jk, &WeedProblem);
	}

	fscanf(f4, "%s %d", jk, &GrazeTimes);
	for(k=1; k<=GrazeTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &GrazeStartMonth[k]);
		fscanf(f4, "%s %d", jk, &GrazeStartDay[k]);
		fscanf(f4, "%s %d", jk, &GrazeEndMonth[k]);
		fscanf(f4, "%s %d", jk, &GrazeEndDay[k]);
		fscanf(f4, "%s %f", jk, &cattle[k]);
		fscanf(f4, "%s %f", jk, &horse[k]);
		fscanf(f4, "%s %f", jk, &sheep[k]);
		fscanf(f4, "%s %f", jk, &hrs[k]);
	}
    fclose(f4);       



	CString fname;
	FILE *fpo;
	fname.Format("%s\\inter\\InputParameters.txt", OUTPUT);
	if ((fpo=fopen(fname,"w"))==NULL) 
	{
		CString note;
		note.Format("Can not create file %s", fname);
		AfxMessageBox(note);
		exit(0);
	}
    
    // Save site
    fprintf(fpo,"Input_Parameters:\n");
    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Site_data:                  %s\n",SiteName);
    fprintf(fpo,"Simulated_Year:             %d\n",1);
    fprintf(fpo,"Latitude:                   %6.3f\n",latitude);
    fprintf(fpo,"Daily_Record:               %6d\n",1);  
    
        // Climate data
    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Climate_data:\n");
	fprintf(fpo,"Climate_Data_Type:          %d\n",1);
    fprintf(fpo,"NO3NH4_in_Rainfall          %8.4f\n",NO3NH4_Rainfall);
    fprintf(fpo,"NH3_of_Atmosphere           %8.4f\n",0.06);
	fprintf(fpo,"BaseCO2_of_Atmosphere       %8.4f\n",350.0);
    fprintf(fpo,"Climate_file_count=         %d\n",1);
	
    fprintf(fpo,"    %d   %s\n",1, ClimateFilename);

    // Soil parameter
    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Soil_data:\n");
    fprintf(fpo,"   Soil_Texture             %2d\n",Soil_Texture);
    fprintf(fpo,"   Landuse_Type             %2d\n",Soil_landuse);
    fprintf(fpo,"   Density                  %8.5f\n",Soil_Density);
    fprintf(fpo,"   Soil_pH                  %8.5f\n",Soil_pH);
	//fprintf(fpo,"   Flood_water_pH           %8.5f\n",Flood_pH);
    fprintf(fpo,"   SOC_at_Surface           %8.5f\n",Soil_OCatSurface); 
    fprintf(fpo,"   Clay_fraction            %8.5f\n",Soil_Clay);
    fprintf(fpo,"   BypassFlow               %2d\n",0);
    fprintf(fpo,"   Litter_SOC               %8.5f\n",F_litter);
    fprintf(fpo,"   Humads_SOC               %8.5f\n",F_humads);
    fprintf(fpo,"   Humus_SOC                %8.5f\n",F_humus);
    fprintf(fpo,"   Soil_NO3(-)(mgN/kg)      %8.5f\n",10.0);
    fprintf(fpo,"   Soil_NH4(+)(mgN/kg)      %8.5f\n",0.1);
    fprintf(fpo,"   Moisture                 %8.5f\n",0.5);
    fprintf(fpo,"   Temperature              %8.5f\n",5.0);
    
    // Save crop parameter
	CropSystemID = 1;
    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Crop_data:\n");
    fprintf(fpo,"Rotation_Number=            %d\n",1);
    for (i = 1; i<=1;i++) 
	{ 
		fprintf(fpo,"  Rotation_ID=              %d\n",1);
        fprintf(fpo,"  Totalyear=                %d\n", 1);
        fprintf(fpo,"  Years_Of_A_Cycle=         %d\n", 1);
		
        for (j = 1; j<=1;j++) 
		{
			fprintf(fpo,"    YearID_of_a_cycle=      %d\n",j);
            n = CropSystemID;
            fprintf(fpo,"    Crop_total_Number=      %d\n",n); 
            for (k = 1; k<= n;k++)
			{
				fprintf(fpo,"      Crop_ID=              %d\n",k);
                fprintf(fpo,"        Crop_Type=          %d\n",CropNumber[k]);
                fprintf(fpo,"        Plant_time=         %d %d\n", CropPlantMonth[k], CropPlantDay[k]);
				fprintf(fpo,"        Harvest_time=       %d %d\n",CropHarvestMonth[k], CropHarvestDay[k]);
                fprintf(fpo,"        Year_of_harvest=    %d\n",1);
                fprintf(fpo,"        Ground_Residue=     %6.4f\n",CropResidue[k]); 
				CropYield[k] = OptimumYield(CropNumber[k]);
                fprintf(fpo,"        Yield=              %8.2f\n",CropYield[k]);
				fprintf(fpo,"        Rate_reproductive=  %8.2f\n",0.02);
				fprintf(fpo,"        Rate_vegetative=    %8.2f\n",0.015);
				fprintf(fpo,"        Psn_efficiency=     %8.2f\n",0.15);
				fprintf(fpo,"        Psn_maximum=        %8.2f\n",40.0);
				fprintf(fpo,"        TreeAge=			 %8.2f\n",12.5);
				fprintf(fpo,"        Cover_crop=         %d\n",0);
				
            }
            
            n = TillTimes;
            fprintf(fpo,"    Tillage_number=         %d\n",n); 
            for (k = 1; k<= n; k++) {
                fprintf(fpo,"      Tillage_ID=           %d\n",k); 
                fprintf(fpo,"        Month/Day/method=   %d %d %d\n",TillMonth[k], TillDay[k], TillMethod[k]); 
            }
            
            n = FertTimes;
            fprintf(fpo,"    Fertil_number=          %d\n",n);
            for (k = 1; k<=n;k++) {

				if(FertMethod[k]==0) FertDepth = 0.0;
				else if(FertMethod[k]==1) FertDepth = 5.0;
				else if(FertMethod[k]==2) FertDepth = 10.0;
				else FertDepth = 20.0;

                fprintf(fpo,"      fertilization_ID=     %d\n",k); 
                fprintf(fpo,"        Month/Day/method=   %d %d %d\n", FertMonth[k], FertDay[k], FertMethod[k]); 
                
				fprintf(fpo,"        Depth=              %f\n",FertDepth); 
                fprintf(fpo,"        Nitrate=            %.2f\n",FertNitrate[k]); 
                fprintf(fpo,"        AmmBic=             %.2f\n",FertAB[k]); 
                fprintf(fpo,"        Urea=               %.2f\n",FertUrea[k]); 
                fprintf(fpo,"        Anh=                %.2f\n",FertAA[k]); 
                fprintf(fpo,"        NH4NO3=             %.2f\n",FertAN[k]);
                fprintf(fpo,"        NH42SO4=            %.2f\n",FertAS[k]); 
                fprintf(fpo,"        NH4HPO4=            %.2f\n",FertAP[k]); 
				fprintf(fpo,"      Release_rate=         %f\n",1.0); 
				fprintf(fpo,"      Inhibitor_efficiency= %f\n",0.0); 
				fprintf(fpo,"      Inhibitor_duration=   %f\n",0.0); 
				fprintf(fpo,"      FertilizationOption=  %d\n",0); 

				//DayRelease[k], NIefficiency[k], NIduration[k]
            }
                
            n = ManureTimes;
            fprintf(fpo,"    Manure_number=          %d\n",n);
            for (k = 1; k<= n;k++) {
				fprintf(fpo,"      Manure_ID=            %d\n",k); 
                fprintf(fpo,"        Month/Day=          %d %d\n",ManureMonth[k], ManureDay[k]);
                fprintf(fpo,"        Amount/C|N_ratio=   %f %f\n",ManureAmount[k], ManureCN[k]);
				fprintf(fpo,"        Type=               %d\n", ManureType[k]);
            }
                
            n = WeedTimes;
            fprintf(fpo,"    Plastic_applications=            %d\n",n);
            fprintf(fpo,"    Ventilation=           %d\n",0); 
            for (k = 1; k<= n;k++) 
			{
                fprintf(fpo,"      Plastic_ID=           %d\n",k); 
                fprintf(fpo,"        Start/End=          %d %d\n",WeedMonth1[k], WeedDay1[k]); 
				fprintf(fpo,"        Start/End=          %d %d\n",WeedMonth2[k], WeedDay2[k]);
            }
                
            n = FloodTimes;
            fprintf(fpo,"    Flood_number=           %d\n",n); 
            fprintf(fpo,"    Leak_type=              %d\n",1);
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Flooding_ID=          %d\n",k); 
                fprintf(fpo,"        Flood_Month/Day=    %d %d\n",FloodStartMonth[k], FloodStartDay[k]);
                fprintf(fpo,"        Drain_Month/Day=    %d %d\n",FloodEndMonth[k], FloodEndDay[k]);
				fprintf(fpo,"        Water_pH=    %f\n",7.0);
			}
            fprintf(fpo,"    Water_control=           %d\n",0); 
			fprintf(fpo,"    Leak_rate=               %d\n",0); 

            n = IrriTimes;
            fprintf(fpo,"    Irrigation_number=      %d\n",n); 
            fprintf(fpo,"    Irrigation_type=        %d\n",1);
			fprintf(fpo,"    Irrigation_Index=       %f\n",IrriIndex[1]); 
			fprintf(fpo,"    Irrigation_Method=      %d\n",IrriMethod[0]);
            for (k = 1; k<= n;k++) 
			{
                fprintf(fpo,"      Irrigation_ID=        %d\n",k); 
                fprintf(fpo,"        Irr_Month/Day=      %d %d\n",IrriMonth[k], IrriDay[k]); 
                fprintf(fpo,"        Water_amount/Method=    %f %f\n",IrriAmount[k], IrriMethod[k]); 
            }

            n = GrazeTimes;
            fprintf(fpo,"    Grazing_number=           %d\n",n); 
            for (k = 1; k<= n;k++) 
			{
                fprintf(fpo,"      Grazing_ID=           %d\n",k); 
                fprintf(fpo,"        Start_Month/Day=    %d %d\n",GrazeStartMonth[k], GrazeStartDay[k]);
				fprintf(fpo,"        End_Month/Day=      %d %d\n",GrazeEndMonth[k], GrazeEndDay[k]);
                //fprintf(fpo,"        Animal_Type=        %d\n",grazing.get(i, j, k)->Type);
                fprintf(fpo,"        Cattle_Head_per_ha= %f\n",cattle[k]);
				fprintf(fpo,"        Horse_Head_per_ha_= %f\n",horse[k]);
				fprintf(fpo,"        Sheep_Head_per_ha_= %f\n",sheep[k]);
				fprintf(fpo,"        Graz_Hours_Per_day= %f\n",hrs[k]);
            }
			fprintf(fpo,"      Cut_number=           %d\n",0); 

			/*n = FilmTimes;
            fprintf(fpo,"    Film_number=            %d\n",n);
            
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Film_ID=           %d\n",k); 
                fprintf(fpo,"      Start_Month/Day=          %d %d\n",FilmStartMonth[k], FilmStartDay[k]); 
				fprintf(fpo,"      Start_Month/Day=          %d %d\n",FilmEndMonth[k], FilmEndDay[k]); 
				fprintf(fpo,"      Film_type=           %d\n",FilmType[k]); 
			}*/
        }
    }
	fprintf(fpo,"Climate_file_mode           %6d\n",0);
	fprintf(fpo,"Soil_microbial_index        %f\n",1.0);
	fprintf(fpo,"Crop_model_approach         %d\n",0);

	fprintf(fpo,"Depth_WRL_m                 %f\n", 100.0);
	fprintf(fpo,"Slope                       %f\n", 0.0);
	fprintf(fpo,"Field_capacity              %f\n", 0.0);
	fprintf(fpo,"Wilting_point               %f\n", 0.0);
	fprintf(fpo,"CO2_increase_rate           %f\n", 0.0);
	fprintf(fpo,"SOC_profile_A               %f\n", WSOCA[Soil_landuse]);
	fprintf(fpo,"SOC_profile_B               %f\n", WSOCB[Soil_landuse]);
	fprintf(fpo,"High_WT                     %d\n",0);
	fprintf(fpo,"Hydro_conductivity          %f\n", 0.0);
	fprintf(fpo,"Soil_porosity               %f\n", 0.0);
	fprintf(fpo,"Perennial_crop              %d\n", 0);

	fclose (fpo);

	CString KK;
	FILE *KKw;
	KK.Format("%s\\inter\\SoilRanges.txt", OUTPUT);
	if ((KKw=fopen(KK,"w"))==NULL) 
	{
		CString note;
		note.Format("Can not create file %s", KK);
		AfxMessageBox(note);
		exit(0);
	}
    
    fprintf(KKw,"Property   Ave           Max           Min:\n");
    fprintf(KKw,"SOC        %f     %f    %f\n", Soil_OCatSurface, SoilOC1, SoilOC2);
	fprintf(KKw,"Clay       %f     %f    %f\n", Soil_Clay, SoilCLAY1, SoilCLAY2);
	fprintf(KKw,"pH         %f     %f    %f\n", Soil_pH, SoilPH1, SoilPH2);
	fprintf(KKw,"Density    %f     %f    %f\n", Soil_Density, SoilBD1, SoilBD2);
	fprintf(KKw,"Texture    %d     %d    %d\n", Soil_Texture, SoilTexture1, SoilTexture2);
   
	fclose(KKw);
  
}

float WizardCrops::OptimumYield(int CT)
{
	int crop;
	float yield, myc, grain, straw, root;

	FILE *fp;
    char  VEGE[80], note[160];
	CString note1;

	sprintf(VEGE, "%s\\Library\\LIB_CROP\\crop_%d", ROOTDIR, CT);
    fp = fopen(VEGE, "r");
    if ( fp == NULL )
    {
		sprintf(VEGE, "%s\\Library\\LIB_CROP\\crop_%d.txt", ROOTDIR, CT);
		fp = fopen(VEGE, "r");

		if ( fp == NULL )
		{
			CString mess;
			mess.Format("Can not open %s.", VEGE);
			AfxMessageBox(mess);
			exit(0);
		}
    }

    fscanf(fp, "%d %s", &crop, note);
    fscanf(fp, "%s %s", note, note);
    fscanf(fp, "%s %s", note, note);
    fscanf(fp, "%f %s", &myc, note);
    fscanf(fp, "%f %s", &grain, note);
    fscanf(fp, "%f %s", &straw, note);
    fscanf(fp, "%f %s", &root, note);
    fclose( fp );

	if(crop!=CT)
	{
		note1.Format("Error for crop type %d vs. %d", CT, crop);
		AfxMessageBox(note);
		exit(0);
	}

	yield = myc * grain / 0.4; //kg dry matter/ha

	return(yield);
}

int WizardCrops::clay_texture(float Clay)
{
	int ST;
	if (Clay <= .03) ST = 1;
		else if (Clay <=  .06) ST = 2;
		else if (Clay <= .09) ST = 3;
		else if (Clay <= .14) ST = 4;
		else if (Clay <= .19) ST = 5;
	    else if (Clay <= .27) ST = 6;
		else if (Clay <= .34) ST = 7;
		else if (Clay <= .41) ST = 8;
		else if (Clay <= .43) ST = 9;
		else if (Clay <= .49) ST = 10;
		else ST = 11;

	return(ST);
}


