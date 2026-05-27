// ountySave.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ountySave.h"
#include "direct.h"
#include "SitePara.h"
#include "dndc_main.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CountySave dialog

CountySave::CountySave(CWnd* pParent /*=NULL*/)
	: CDialog(CountySave::IDD, pParent)
{
	//{{AFX_DATA_INIT(CountySave)
	m_FileName = _T("");
	m_AirTemp = FALSE;
	m_CH4 = FALSE;
	m_CropResp = FALSE;
	m_Daily = FALSE;
	m_Evaporation = FALSE;
	m_GHG = FALSE;
	m_GrainMass = FALSE;
	m_Ice = FALSE;
	m_LAI = FALSE;
	m_N2 = FALSE;
	m_N2O = FALSE;
	m_NH3 = FALSE;
	m_NO = FALSE;
	m_Nuptake = FALSE;
	m_Prec = FALSE;
	m_PSN = FALSE;
	m_Radiation = FALSE;
	m_RootCO2 = FALSE;
	m_RootMass = FALSE;
	m_ShootMass = FALSE;
	m_SnowPack = FALSE;
	m_SoilCO2 = FALSE;
	m_SoilM1 = FALSE;
	m_SoilM2 = FALSE;
	m_SoilM3 = FALSE;
	m_SoilT1 = FALSE;
	m_SoilT2 = FALSE;
	m_SoilT3 = FALSE;
	m_TotalCO2 = FALSE;
	m_Transpiration = FALSE;
	m_YrReport = FALSE;
	m_SOC = FALSE;
	m_Nleach = FALSE;
	//}}AFX_DATA_INIT
}


void CountySave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CountySave)
	DDX_Text(pDX, IDC_FileName, m_FileName);
	DDX_Check(pDX, IDC_AirTemp, m_AirTemp);
	DDX_Check(pDX, IDC_CH4, m_CH4);
	DDX_Check(pDX, IDC_CropResp, m_CropResp);
	DDX_Check(pDX, IDC_Daily, m_Daily);
	DDX_Check(pDX, IDC_Evaporation, m_Evaporation);
	DDX_Check(pDX, IDC_GHG, m_GHG);
	DDX_Check(pDX, IDC_GrainMass, m_GrainMass);
	DDX_Check(pDX, IDC_Ice, m_Ice);
	DDX_Check(pDX, IDC_LAI, m_LAI);
	DDX_Check(pDX, IDC_N2, m_N2);
	DDX_Check(pDX, IDC_N2O, m_N2O);
	DDX_Check(pDX, IDC_NH3, m_NH3);
	DDX_Check(pDX, IDC_NOFLUX, m_NO);
	DDX_Check(pDX, IDC_Nuptake, m_Nuptake);
	DDX_Check(pDX, IDC_Prec, m_Prec);
	DDX_Check(pDX, IDC_PSN, m_PSN);
	DDX_Check(pDX, IDC_Radiation, m_Radiation);
	DDX_Check(pDX, IDC_RootCO2, m_RootCO2);
	DDX_Check(pDX, IDC_RootMass, m_RootMass);
	DDX_Check(pDX, IDC_ShootMass, m_ShootMass);
	DDX_Check(pDX, IDC_SnowPack, m_SnowPack);
	DDX_Check(pDX, IDC_SoilCO2, m_SoilCO2);
	DDX_Check(pDX, IDC_SoilM1, m_SoilM1);
	DDX_Check(pDX, IDC_SoilM2, m_SoilM2);
	DDX_Check(pDX, IDC_SoilM3, m_SoilM3);
	DDX_Check(pDX, IDC_SoilT1, m_SoilT1);
	DDX_Check(pDX, IDC_SoilT2, m_SoilT2);
	DDX_Check(pDX, IDC_SoilT3, m_SoilT3);
	DDX_Check(pDX, IDC_TotalCO2, m_TotalCO2);
	DDX_Check(pDX, IDC_Trspiration, m_Transpiration);
	DDX_Check(pDX, IDC_YrReport, m_YrReport);
	DDX_Check(pDX, IDC_SOC, m_SOC);
	DDX_Check(pDX, IDC_Nleach, m_Nleach);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CountySave, CDialog)
	//{{AFX_MSG_MAP(CountySave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CountySave message handlers

void CountySave::OnOK() 
{
	// TODO: Add extra validation here
	CString DIR0;
	DIR0.Format("%s\\SAVE");
	mkdir(DIR0);

	UpdateData(TRUE);

	if(m_FileName=="")
	{
		CString note;
		note.Format("Please type a name first");
		AfxMessageBox(note);
		return;
	}

	
	int da[30] = {0, 0};
	int i, jday;
	CString Ditem[30] = {"Julian", 
		"AirTemp", "Precip", "SoilIce", "SnowPack", "Evapor", 
		"SoilT1cm", "SoilT15cm", "SoilT30cm", "SoilM5cm", "SoilM15cm", 
		"SoilM30cm", "SOC30cm", "Crop_N", "Shoot_C", " ", 
		" ", "Root_C", "Grain_C", " ", "CropLAI", 
		"SoilCO2", "RootCO2", "TotalCO2", "CH4", "N2O", 
		"NO", "N2", "NH3", "Nleach"};

	CString Unit[30] = {"day", 
		"degree C", "cm", "cm", "cm", "cm", 
		"degree C", "degree C", "degree C", "wfps", "wfps", 
		"wfps", "kg C/ha", "kg N/ha", "kg C/ha", " ", 
		" ", "kg C/ha", "kg C/ha", " ", " ", 
		"kg C/ha/d", "kg C/ha/d", "kg C/ha/d", "kg C/ha/d", "g N/ha/d", 
		"g N/ha/d", "g N/ha/d", "kg N/ha/d", "kgN/ha/d"};
	float SOC1, SON1, SIN1, SOC2, SON2, SIN2;
	float soilCO2, rootCO2, CH4, leachHumC, leachHumN, leachN, uptakeN, weedupN, NH3, N2O, NO, N2, NO2;
	float manureC, manureN, litterC, litterN, rootC, rootN, weedC, weedN, irriN;
	float rainN, fertN, fixN, runoffN;
	char SelectedState[200], SelectedCounty[200];
	int CropCode;
	float ha;


	float C_CO2, C_N2O, C_CH4;
	float GWP_CO2,GWP_N2O, GWP_CH4, NetGWP, dC, dN;
	FILE* RCD;
	int ResultYr=1, jd, year;
	char WW[600], js[100], qqq[300];
	char SF[300], DF[300];
	float jf, C[25], N[25], P[25], S[25], W[25], flux[29][366];
	CString rcd, Site_Name, Crop_Name;
	CString filename1, filename2, filename3;
	FILE *rf;


	
	rcd.Format("%s\\record\\site\\Year-%d.txt", OUTPUT, ResultYr);
		RCD = fopen(rcd, "r");
		if(RCD==NULL) 
		{
			CString mess;
			mess.Format("Can not open file %s", rcd);
			AfxMessageBox(mess);
			exit(0);
		}
	fscanf(RCD, "%s %s %s %s %s %d", 
				js, js, js, Site_Name, js, &year);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);

	fscanf(RCD, "%s %d %f %f %f %f %f %f %f %f", 
			js, &jd, &jf, &jf, &jf, &jf, &jf, &jf, &SOC1, &SON1);
	fscanf(RCD, "%s %d %f %f %f %f %f %f %f %f", 
			js, &jd, &jf, &jf, &jf, &jf, &jf, &jf, &SOC2, &SON2);

	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);

	fscanf(RCD, "%s %d %f %f %f %f %f %f %f", 
			js, &jd, &jf, &jf, &jf, &jf, &jf, &jf, &SIN1);
	fscanf(RCD, "%s %d %f %f %f %f %f %f %f", 
			js, &jd, &jf, &jf, &jf, &jf, &jf, &jf, &SIN2);

	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
			
	fscanf(RCD, "%s %f %f", js, &manureC, &manureN);
			fscanf(RCD, "%s %f %f", js, &litterC, &litterN);
			fscanf(RCD, "%s %f %f", js, &rootC, &rootN);
			fscanf(RCD, "%s %f %f", js, &weedC, &weedN);
			fscanf(RCD, "%s %s %f", js, js, &rainN);
			fscanf(RCD, "%s %f", js, &fertN);
			fscanf(RCD, "%s %s %s %f", js, js, js, &fixN);
	
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fscanf(RCD, "%s %s %f", js, js, &soilCO2);
			fscanf(RCD, "%s %s %f", js, js, &rootCO2);
			fscanf(RCD, "%s %s %f", js, js, &CH4);
			fscanf(RCD, "%s %s %f %f", js, js, &leachHumC, &leachHumN);
			fscanf(RCD, "%s %s %s %f", js, js, js, &uptakeN);
			fscanf(RCD, "%s %s %s %f", js, js, js, &weedupN);
			fscanf(RCD, "%s %s %f", js, js, &leachN);
			//fscanf(RCD, "%s %s %f", js, js, &runoffN);
			fscanf(RCD, "%s %s %f", js, js, &NH3);
			fscanf(RCD, "%s %f", js, &N2O);
			fscanf(RCD, "%s %f", js, &NO);
			fscanf(RCD, "%s %f", js, &N2);
			fscanf(RCD, "%s %f", js, &NO2);

	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fgets(WW, 500, RCD);
	fscanf(RCD, "%s %s %s", js, js, Crop_Name);
	
	fclose(RCD);
	runoffN = 0.0;

	char hh[200];
		CString IDfile;
		FILE* fid;
		IDfile.Format("%s\\Inter\\SelectedCounty.txt", OUTPUT);
		fid = fopen(IDfile, "r");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("7. Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fscanf(fid, "%s", hh);
		sprintf(SelectedState, "%s", hh);
		fscanf(fid, "%s", hh);
		sprintf(SelectedCounty, "%s", hh);
		fscanf(fid, "%d", &CropCode);
		fscanf(fid, "%f", &ha);

		fclose(fid);

	dC = (manureC+litterC+rootC+weedC)-(soilCO2+leachHumC+CH4*0.2);

	dN =(manureN+litterN+rootN+weedN+rainN+fertN)-
				(leachHumN+uptakeN+weedupN+leachN+runoffN+NH3+N2O+NO+N2);

	C_CO2 = ha * (-dC) * 0.001;
	C_N2O = ha * (N2O) * 0.001;
	C_CH4 = ha * (CH4) * 0.001;

	GWP_CO2 = -dC / 12 * 44;
	GWP_N2O = N2O / 28 * 44 * 310;
	GWP_CH4 = CH4 / 12 * 16 * 21;
	NetGWP = GWP_CO2 + GWP_N2O + GWP_CH4;


	//Save GHG fluxes and GWP
	if(m_GHG == TRUE)
	{
		filename1.Format("%s\\Save\\%s_GHG", ROOTDIR, m_FileName);
		rf=fopen(filename1, "w");
		if(rf==NULL)
		{
			CString note;
			note.Format("Can not create file %s", filename1);
			AfxMessageBox(note);
			exit(0);
		}
		fprintf(rf, "State: %s/County: %s/Year: %d/Crop: %s/Acreage: %10.1f ha\n\n", 
			SelectedState, SelectedCounty, year, Crop_Name, ha);

		fprintf(rf, "Gas flux:\n");
		fprintf(rf, "CO2 (kg C/ha/yr): %10.2f\n", -dC);
		fprintf(rf, "N2O (kg N/ha/yr): %10.2f\n", N2O);
		fprintf(rf, "CH4 (kg C/ha/yr): %10.2f\n\n", CH4);

		fprintf(rf, "GWP (kg CO2 emission equivalent/ha/yr):\n");
		fprintf(rf, "CO2             : %10.2f\n", GWP_CO2);
		fprintf(rf, "N2O             : %10.2f\n", GWP_N2O);
		fprintf(rf, "CH4             : %10.2f\n", GWP_CH4);
		fprintf(rf, "Net             : %10.2f\n", NetGWP);

		fclose(rf);
	}
	//Annual report
	if(m_YrReport==TRUE)
	{
		
		sprintf(SF, "%s\\Record\\site\\Year-%d.txt", OUTPUT, year);
		sprintf(DF, "%s\\Save\\%s_year_%d", OUTPUT, ROOTDIR, m_FileName, year);
		FileCopy(SF, DF);
		filename2.Format("%s", DF);
	}

	//Save daily data

	if(m_Daily==TRUE)
	{
		//read in daily results
		CString DayFile;
		FILE *DF;

		DayFile.Format("%s\\Record\\site\\day_C_%d", OUTPUT, year);
		DF=fopen(DayFile, "r");
		if(DF==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DayFile);
			AfxMessageBox(note);
			exit(0);
		}
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		for(i=1; i<=365; i++)
		{
			fscanf(DF, "%d", &jday);
			if(i!=jday)
			{
				CString note;
				note.Format("Error on daily C data for day %d in file %s", i, DayFile);
				AfxMessageBox(note);
				exit(0);
			}
			for(int j=1; j<=13; j++) fscanf(DF, "%f", &C[j]);

			//1-V.Labile 2-Labile  3-Resis.  4-Microbe 5-Humads  6-Humus   
			//7-soil_CO2 8-root_CO2 9-DOC  10-CH4_Prod.  11-CH4_Oxid.  12-CH4_Flux  13-SOC_leach

			flux[12][i] = C[1]+C[2]+C[3]+C[4]+C[5]+C[6];
			flux[21][i] = C[7];
			flux[22][i] = C[8];
			flux[24][i] = C[12];
			flux[23][i] = C[7]+C[8];

		}
		fclose(DF);

		DayFile.Format("%s\\Record\\site\\day_N_%d", OUTPUT, year);
		DF=fopen(DayFile, "r");
		if(DF==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DayFile);
			AfxMessageBox(note);
			exit(0);
		}
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		for(i=1; i<=365; i++)
		{
			fscanf(DF, "%d", &jday);
			if(i!=jday)
			{
				CString note;
				note.Format("Error on daily N data for day %d in file %s", i, DayFile);
				AfxMessageBox(note);
				exit(0);
			}
			for(int j=1; j<=19; j++) fscanf(DF, "%f", &N[j]);

						
//N uptake-----  N pools (kg N/ha)-------------------------------------------    N gas flux (g N/ha/day)---------------------------                            Gross       Microbial 
//1Crop   2Weed    3Urea   4NH4+   5NO3-   6NH4+   7NO3-   8NH4+   9NO3-   10NH3  11Clay-N    12N2O       13NO       14N2       15Soil   16Plant  17Leach    18mineral   19assimilation  
//(kg N/ha/day)         0-10cm-----   10-20cm----   20-30cm----                                                                   NH3    NH3                   ization     

			//Nuptake[i] = N[1];
			flux[25][i] = N[12];//N2O
			flux[26][i] = N[13];//NO
			flux[27][i] = N[14];//N2
			flux[28][i] = N[15]+N[16];//NH3
			flux[29][i] = N[17];//N leach

		}
		fclose(DF);


		DayFile.Format("%s\\Record\\site\\day_Crop_%d", OUTPUT, year);
		DF=fopen(DayFile, "r");
		if(DF==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DayFile);
			AfxMessageBox(note);
			exit(0);
		}
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		
		for(i=1; i<=365; i++)
		{
			fscanf(DF, "%d", &jday);
			if(i!=jday)
			{
				CString note;
				note.Format("Error on daily crop data for day %d in file %s", i, DayFile);
				AfxMessageBox(note);
				exit(0);
			}
			for(int j=1; j<=10; j++) fscanf(DF, "%f", &P[j]);
			//1-LAI  2-CropN  3-shootC  4-RootC  5-GrainC  6-N_demand  7-N_fixation

			flux[20][i] = P[1];//
			flux[13][i] = P[2];//crop N
			flux[14][i] = P[3];//shoot C
			flux[17][i] = P[4];//Root C
			flux[18][i] = P[5];//grain C
			flux[19][i] = P[6];//N demand
			//flux[16][i] = P[11];

	

		}
		fclose(DF);

		DayFile.Format("%s\\Record\\site\\day_Soil_%d", OUTPUT, year);
		DF=fopen(DayFile, "r");
		if(DF==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DayFile);
			AfxMessageBox(note);
			exit(0);
		}
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		
		for(i=1; i<=365; i++)
		{
			fscanf(DF, "%d", &jday);
			if(i!=jday)
			{
				CString note;
				note.Format("Error on daily soil data for day %d in file %s", i, DayFile);
				AfxMessageBox(note);
				exit(0);
			}
			for(int j=1; j<=18; j++) fscanf(DF, "%f", &S[j]);
			//1-Temp. 2-Prec. 3-Eh 4,5,6,7,8-Soil_temperature       9,10,11,12,13-Soil moisture (wfps)     14,15,16-Ice (wfps)   17-Ice  18-Snow_pack 
			//(C)     (mm)   (mv)     5    15    30    40    50     5       15      30      40      50      5      15     30       (mm)  (mm)      

			flux[1][i] = S[1];//air T
			flux[2][i] = S[2];//precipitation
			flux[6][i] = S[4];//soil T at 5cm
			flux[7][i] = S[5];//soil T at 15cm
			flux[8][i] = S[6];//soil T at 30cm
			flux[9][i] = S[9];//soil moisture at 5cm
			flux[10][i] = S[10];//soil moisture at 15cm
			flux[11][i] = S[11];//soil moisture at 30cm
			flux[3][i] = S[17];//ice
			flux[4][i] = S[18];//snow pack
			
		}
		fclose(DF);


		DayFile.Format("%s\\Record\\site\\day_Water_%d", OUTPUT, year);
		DF=fopen(DayFile, "r");
		if(DF==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DayFile);
			AfxMessageBox(note);
			exit(0);
		}
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		fgets(qqq, 300, DF);
		//fgets(qqq, 300, DF);
		
		for(i=1; i<=365; i++)
		{
			fscanf(DF, "%d", &jday);
			if(i!=jday)
			{
				CString note;
				note.Format("Error on daily water data for day %d in file %s", i, DayFile);
				AfxMessageBox(note);
				exit(0);
			}
			for(int j=1; j<=13; j++) fscanf(DF, "%f", &W[j]);
			//1-Ini_pool 2-End_pool 3-FreeWater 4-SoilIce 5-Influx 6-Evapor. 7-Transp.  8-Leach 9-Balance  
			//10-Ponding 11-SnowPack 12-DeepPool 13-Runoff

			flux[5][i] = W[6];
			
			
		}
		fclose(DF);

		filename3.Format("%s\\Save\\%s_DailyData", ROOTDIR, m_FileName);
		rf=fopen(filename3, "w");
		if(rf==NULL)
		{
			CString note;
			note.Format("Can not create file %s", filename3);
			AfxMessageBox(note);
			exit(0);
		}
		fprintf(rf, "State: %s/County: %s/Year: %d/Crop: %s/Acreage: %10.1f ha\n\n", 
			SelectedState, SelectedCounty, year, Crop_Name, ha);
		//fprintf(rf, "Day");

		if(m_AirTemp ==1) da[1]=1;;
		if(m_Prec ==1) da[2]=1;;
		if(m_Ice ==1) da[3]=1;;
		if(m_SnowPack ==1) da[4]=1;;
		if(m_Evaporation ==1) da[5]=1;;

		if(m_SoilT1 ==1) da[6]=1;;
		if(m_SoilT2 ==1) da[7]=1;;
		if(m_SoilT3 ==1) da[8]=1;;
		if(m_SoilM1 ==1) da[9]=1;;
		if(m_SoilM2 ==1) da[10]=1;;
		if(m_SoilM3 ==1) da[11]=1;;
		if(m_SOC ==1) da[12]=1;;

		/*if(m_PSN ==1) da[13]=1;;
		if(m_CropResp ==1) da[14]=1;;
		if(m_Transpiration ==1) da[15]=1;;
		if(m_Nuptake ==1) da[16]=1;;
		if(m_ShootMass ==1) da[17]=1;;
		if(m_RootMass ==1) da[18]=1;;
		if(m_GrainMass ==1) da[19]=1;;
		if(m_LAI ==1) da[20]=1;;*/

			//	if(m_PSN ==1) da[13]=1;;
		//if(m_CropResp ==1) da[14]=1;;
		//if(m_Transpiration ==1) da[15]=1;;
		if(m_Nuptake ==1) da[13]=1;;
		if(m_ShootMass ==1) da[14]=1;;
		if(m_RootMass ==1) da[17]=1;;
		if(m_GrainMass ==1) da[18]=1;;
		if(m_LAI ==1) da[20]=1;;

		if(m_SoilCO2 ==1) da[21]=1;;
		if(m_RootCO2 ==1) da[22]=1;;
		if(m_TotalCO2 ==1) da[23]=1;;
		if(m_CH4 ==1) da[24]=1;;
		if(m_N2O ==1) da[25]=1;;
		if(m_NO ==1) da[26]=1;;
		if(m_N2 ==1) da[27]=1;;
		if(m_NH3 ==1) da[28]=1;;
		if(m_Nleach ==1) da[29]=1;;

		da[0] = 1;
	
		for(i=0; i<= 29; i++)
		{
			if(da[i]==1) fprintf(rf, "%10s ", Ditem[i]);
		}
		fprintf(rf, "\n");

		for(i=0; i<= 29; i++)
		{
			if(da[i]==1) fprintf(rf, "%10s ", Unit[i]);
		}
		fprintf(rf, "\n");

		for(int k=1; k<=365; k++)
		{
			fprintf(rf, "%10d ", k);

			for(i=1; i<= 29; i++)
			{
				if(da[i]==1) fprintf(rf, "%10.2f ", flux[i][k]);
			}
			fprintf(rf, "\n");
		}


		fclose(rf);

	}

	CString note, F1, F2, F3;
	if(m_GHG == TRUE)
		F1.Format("%s, ", filename1);
	else
		F1.Format("");

	if(m_YrReport==TRUE)
		F2.Format("%s, ", filename2);
	else
		F2.Format("");
	if(m_Daily==TRUE)
		F3.Format("%s", filename3);
	else
		F3.Format("");

	note.Format("Your data have been saved in files %s%s%s.", F1, F2, F3);
	AfxMessageBox(note);

	CDialog::OnOK();
}

