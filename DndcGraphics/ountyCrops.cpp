// ountyCrops.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "ountyCrops.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CountyCrops dialog
float SOCA2[6]={0.0,0.2,0.2,0.08,0.05,0.2};
float SOCB2[6]={10.0,2.0,2.0,1.4,4.0,2.0};


CountyCrops::CountyCrops(CWnd* pParent /*=NULL*/)
	: CDialog(CountyCrops::IDD, pParent)
{
	//{{AFX_DATA_INIT(CountyCrops)
	m_crop1 = 0.0f;
	m_crop2 = 0.0f;
	m_crop3 = 0.0f;
	m_crop4 = 0.0f;
	m_crop5 = 0.0f;
	m_crop6 = 0.0f;
	m_crop7 = 0.0f;
	m_crop8 = 0.0f;
	m_crop9 = 0.0f;
	m_crop10 = 0.0f;
	m_crop11 = 0.0f;
	m_crop12 = 0.0f;
	m_crop13 = 0.0f;
	m_crop14 = 0.0f;
	m_crop15 = 0.0f;
	m_crop16 = 0.0f;
	m_crop17 = 0.0f;
	m_crop18 = 0.0f;
	m_SelectedCounty = _T("");
	m_SelectedState = _T("");
	m_SelectedCrop = -1;
	
	//}}AFX_DATA_INIT

	
}


void CountyCrops::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CountyCrops)
	DDX_Text(pDX, IDC_crop1, m_crop1);
	DDX_Text(pDX, IDC_crop2, m_crop2);
	DDX_Text(pDX, IDC_crop3, m_crop3);
	DDX_Text(pDX, IDC_crop4, m_crop4);
	DDX_Text(pDX, IDC_crop5, m_crop5);
	DDX_Text(pDX, IDC_crop6, m_crop6);
	DDX_Text(pDX, IDC_crop7, m_crop7);
	DDX_Text(pDX, IDC_crop8, m_crop8);
	DDX_Text(pDX, IDC_crop9, m_crop9);
	DDX_Text(pDX, IDC_crop10, m_crop10);
	DDX_Text(pDX, IDC_crop11, m_crop11);
	DDX_Text(pDX, IDC_crop12, m_crop12);
	DDX_Text(pDX, IDC_crop13, m_crop13);
	DDX_Text(pDX, IDC_crop14, m_crop14);
	DDX_Text(pDX, IDC_crop15, m_crop15);
	DDX_Text(pDX, IDC_crop16, m_crop16);
	DDX_Text(pDX, IDC_crop17, m_crop17);
	DDX_Text(pDX, IDC_crop18, m_crop18);
	DDX_Text(pDX, IDC_County, m_SelectedCounty);
	DDX_Text(pDX, IDC_State, m_SelectedState);
	DDX_Radio(pDX, IDC_RADIO1, m_SelectedCrop);
	//}}AFX_DATA_MAP

	
}


BEGIN_MESSAGE_MAP(CountyCrops, CDialog)
	//{{AFX_MSG_MAP(CountyCrops)
	ON_BN_CLICKED(IDC_SiteView, OnSiteView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CountyCrops message handlers

void CountyCrops::OnSiteView() 
{
	// TODO: Add your control notification handler code here
	ShowCountyData();
	
}

void CountyCrops::ShowCountyData(void)
{
	CString IDfile, CountyName;
	char qq[200], Sname[200], Cname[200];
	FILE *fid;
	int i, j;
	CString CID;
	
	
	IDfile.Format("%s\\inter\\WizardSite.txt", OUTPUT);
		fid = fopen(IDfile, "r");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fscanf(fid, "%d  %s", &State_ID, County_ID);
		fscanf(fid, "%s  %s", Sname, Cname);
		for(i=1; i<=18; i++)
		{
			fscanf(fid, "%d  %f", &j, &ha[i]);
		}
		fclose(fid);

		m_crop1=ha[1];
		m_crop2=ha[2];
		m_crop3=ha[3];
		m_crop4=ha[4];
		m_crop5=ha[5];
		m_crop6=ha[6];
		m_crop7=ha[7];
		m_crop8=ha[8];
		m_crop9=ha[9];
		m_crop10=ha[10];
		m_crop11=ha[11];
		m_crop12=ha[12];
		m_crop13=ha[13];
		m_crop14=ha[14];
		m_crop15=ha[15];
		m_crop16=ha[16];
		m_crop17=ha[17];
		m_crop18=ha[18];


		CString StateName[57] = {"", "Alabama", "Alaska", "", "Arizona", "Arkansas",
			"California", "", "Colorado", "Connecticut", "Delaware", 
			"DC", "Florida", "Georgia", "", "Hawaii",
			"Idaho", "Illinois", "Indiana", "Iowa", "Kansas", 
			"Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts",
			"Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", 
			"Nebraska", "Nevada", "New_Hampshire", "New_Jersey", "New_Mexico",
			"New_York", "North_Carolina", "North_Dakota", "Ohio", "Oklahoma", 
			"Oregon", "Pennsylvania", "", "Rhode_Island", "South_Carolina",
			"South_Dakota", "Tennessee", "Texas", "Utah", "Vermont ", 
			"Virginia", "", "Washington", "West_Virginia ", "Wisconsin",
			"Wyoming "};

		m_SelectedState.Format("%s", StateName[State_ID]);


		IDfile.Format("%s\\Database\\USA\\Map\\County_name_scope.txt", ROOTDIR);
		fid = fopen(IDfile, "r");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		
		for(;;)
		{
			if(fscanf(fid, "%s %s", CID, CountyName)!=2) 
			{
				CountyName = "Unknown";
				break;
			}
			else
			{
				fgets(qq, 300, fid);

				if(CID==County_ID) break;
			}
		}
		fclose(fid);
     
		m_SelectedCounty.Format("%s", CountyName);

		UpdateData(FALSE);
      
}
	

void CountyCrops::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	if(m_SelectedCrop<0)
	{
		AfxMessageBox("Please select a crop for this simulation");
		return;
	}
	else
	{		
			if(m_SelectedCrop+1 == 1) CropCode = 1;//corn
			else if(m_SelectedCrop+1 == 2) CropCode = 6;//spring wheat
			else if(m_SelectedCrop+1 == 3) CropCode = 2;//winter wheat
			else if(m_SelectedCrop+1 == 4) CropCode = 9;//oats
			else if(m_SelectedCrop+1 == 5) CropCode = 8;//barley
			else if(m_SelectedCrop+1 == 6) CropCode = 20;//rice
			else if(m_SelectedCrop+1 == 7) CropCode = 13;//sorghum
			else if(m_SelectedCrop+1 == 8) CropCode = 14;//cotton
			else if(m_SelectedCrop+1 == 9) CropCode = 3;//soybean
			else if(m_SelectedCrop+1 == 10) CropCode = 18;//potato
			else if(m_SelectedCrop+1 == 11) CropCode = 19;//beet
			else if(m_SelectedCrop+1 == 12) CropCode = 23;//peanut
			else if(m_SelectedCrop+1 == 13) CropCode = 16;//vegetables
			else if(m_SelectedCrop+1 == 14) CropCode = 7;//sugarcane
			else if(m_SelectedCrop+1 == 15) CropCode = 26;//tobacco
			else if(m_SelectedCrop+1 == 16) CropCode = 28;//sunflower
			else if(m_SelectedCrop+1 == 17) CropCode = 4;//legume hay
			else CropCode = 5;//non-legume hay

		CString IDfile;
		FILE* fid;
		IDfile.Format("%s\\Inter\\SelectedCounty.txt", OUTPUT);
		fid = fopen(IDfile, "w");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("6. Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(fid, "%s\n", m_SelectedState);
		fprintf(fid, "%s\n", m_SelectedCounty);
		fprintf(fid, "%d\n", CropCode);
		fprintf(fid, "%f\n", ha[m_SelectedCrop+1]);

		fclose(fid);

		SaveDatatoFile();
	}

	CDialog::OnOK();
}

void CountyCrops::SaveDatatoFile()
{
	int i, j, k, n;
	float NO3NH4_Rainfall;
	char ClimateFilename[200], temp[200], jk[200], SiteName[300], ww[300],SoilProfileFileName[200];
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
	int ManureDay[10], IrriMonth[366], IrriDay[366];
	
	int WeedMonth1[10], WeedDay1[10],WeedMonth2[10], WeedDay2[10], WeedProblem;
	int FloodStartMonth[10], FloodStartDay[10];
	int FloodEndMonth[10], FloodEndDay[10], FloodPH[10];
	int WeedTimes, IrriTimes, ManureTimes, FertTimes, TillTimes, FloodTimes;
	int GrazeTimes, GrazeStartMonth[10], GrazeStartDay[10], GrazeEndMonth[10], GrazeEndDay[10];
	float cattle[10], horse[10], sheep[10], hrs[10], FertDepth;
	int CropType[10], LeakType;

	CString File1, File2, File3, File4;
	FILE *f1, *f2, *f3, *f4;

	//open data files for reading
	CString county_ID1;
	char state_name[200], county_name[200];
	float longitude, latitude;
	//File1.Format("%s\\GIS\\USA1_%d", INPUTPATH3, State_ID);
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
		if (fscanf(f1, "%s  %s  %s %f  %f", county_ID1, state_name, county_name, 
			&longitude, &latitude)!=5)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File1);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			if(County_ID==county_ID1)
			{
				sprintf(SiteName, "%s-%s", state_name, county_name);
				break;
			}
		}
	}
	fclose(f1);

//	File2.Format("%s\\GIS\\USA2_%d", INPUTPATH3, State_ID);
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
		if (fscanf(f2, "%s  %s  %f", county_ID1, temp, &NO3NH4_Rainfall)!=3)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File2);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			sprintf(ClimateFilename, "%s\\Database\\USA\\lib_clim\\%s", ROOTDIR, temp);
			if(County_ID==county_ID1)
			{
				break;
			}
		}
	}
	fclose(f2);

	//File3.Format("%s\\GIS\\USA3_%d", INPUTPATH3, State_ID);
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
		if (fscanf(f3, "%s %f %f %f %f %f %f %f %f", county_ID1, 
			&SoilOC1, &SoilOC2, &SoilCLAY1, &SoilCLAY2, &SoilPH1, &SoilPH2, &SoilBD1, &SoilBD2)!=9)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File2);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			if(County_ID==county_ID1)
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
	Soil_landuse = 1; 
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

	//File4.Format("%s\\Farming\\farm_crop%d.txt", INPUTPATH3, CropCode);
	f4=fopen(File4, "r");
	if (f4==NULL)
	{
		char err[120];
		sprintf(err, "Can not open %s", File4);
		AfxMessageBox(err);
		exit(0); 
	}

	fscanf(f4, "%s %d", jk, &CropType[1]);
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
                fprintf(fpo,"        Crop_Type=          %d\n",CropType[k]);
                fprintf(fpo,"        Plant_time=         %d %d\n", CropPlantMonth[k], CropPlantDay[k]);
				fprintf(fpo,"        Harvest_time=       %d %d\n",CropHarvestMonth[k], CropHarvestDay[k]);
                fprintf(fpo,"        Year_of_harvest=    %d\n",1);
                fprintf(fpo,"        Ground_Residue=     %6.4f\n",CropResidue[k]); 
				CropYield[k] = OptimumYield(CropType[k]);
                fprintf(fpo,"        Yield=              %8.2f\n",CropYield[k]);
				fprintf(fpo,"        Rate_reproductive=  %8.2f\n",0.02);
				fprintf(fpo,"        Transplant=         %d\n",0);
				fprintf(fpo,"        Psn_efficiency=     %8.2f\n",0.15);
				fprintf(fpo,"        Psn_maximum=        %8.2f\n",40.0);
				fprintf(fpo,"        TreeAge=            %8.2f\n",0);
				fprintf(fpo,"        Cover_crop=         %d\n",0);
				/*fprintf(fpo,"        GeneID=             %d\n",-1);
				fprintf(fpo,"        If_transplanting=   %d\n",-1);
				fprintf(fpo,"        Transplant_month=   %d \n",-1);
				fprintf(fpo,"        Transplant_day=     %d\n",-1);*/
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
				fprintf(fpo,"      Release_rate=         %f\n",0.0); 
				fprintf(fpo,"      Inhibitor_efficiency= %f\n",0.0); 
				fprintf(fpo,"      Inhibitor_duration=   %f\n",0.0); 
				fprintf(fpo,"      FertilizationOption=  %d\n",0); 
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
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Plastic_ID=           %d\n",k); 
                fprintf(fpo,"        Start/End=          %d %d\n",WeedMonth1[k], WeedDay1[k]); 
				fprintf(fpo,"        Start/End=          %d %d\n",WeedMonth2[k], WeedDay2[k]); 
            }
                
            n = FloodTimes;
            fprintf(fpo,"    Flood_number=           %d\n",n); 
            fprintf(fpo,"    FloodWaterN=            %f\n",FloodWaterN);
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Flooding_ID=          %d\n",k); 
                fprintf(fpo,"        Flood_Month/Day=    %d %d\n",FloodStartMonth[k], FloodStartDay[k]);
                fprintf(fpo,"        Drain_Month/Day=    %d %d\n",FloodEndMonth[k], FloodEndDay[k]);
				fprintf(fpo,"        Water_pH=    %f\n",7.0);
			}
               
            n = IrriTimes;
            fprintf(fpo,"    Irrigation_number=      %d\n",n); 
            fprintf(fpo,"    Irrigation_type=        %d\n",1);
			fprintf(fpo,"    Irrigation_Index=       %f\n",IrriIndex[1]); 
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Irrigation_ID=        %d\n",k); 
                fprintf(fpo,"        Irr_Month/Day=      %d %d\n",IrriMonth[k], IrriDay[k]); 
                fprintf(fpo,"        Water_amount/pH=    %f %f\n",IrriAmount[k], 7.0); 
            }

            n = 0;
            fprintf(fpo,"    Grazing_number=           %d\n",n); 
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Grazing_ID=           %d\n",k); 
                fprintf(fpo,"        Start_Month/Day=    %d %d\n",0, 0);
				fprintf(fpo,"        End_Month/Day=      %d %d\n",0, 0);
                //fprintf(fpo,"        Animal_Type=        %d\n",grazing.get(i, j, k)->Type);
                fprintf(fpo,"        Cattle_Head_per_ha= %f\n",0);
				fprintf(fpo,"        Horse_Head_per_ha_= %f\n",0);
				fprintf(fpo,"        Sheep_Head_per_ha_= %f\n",0);
				fprintf(fpo,"        Graz_Hours_Per_day= %f\n",0);
            }

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
	fprintf(fpo,"Depth_WRL_m                 %f\n",100.0);
	fprintf(fpo,"Slope                       %f\n",0.0);
	fprintf(fpo,"Field_capacity              %f\n",0.0);
	fprintf(fpo,"Wilting_point               %f\n",0.0);
	fprintf(fpo,"CO2_increase_rate           %f\n",0.0);
	fprintf(fpo,"SOC_profile_A               %f\n",SOCA2[Soil_landuse]);
	fprintf(fpo,"SOC_profile_B               %f\n",SOCB2[Soil_landuse]);
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

float CountyCrops::OptimumYield(int CT)
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

int CountyCrops::clay_texture(float Clay)
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


BOOL CountyCrops::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ShowCountyData();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
