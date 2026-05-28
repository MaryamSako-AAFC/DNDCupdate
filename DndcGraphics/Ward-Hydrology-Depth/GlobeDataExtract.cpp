// GlobeDataExtract.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "GlobeDataExtract.h"
#include "SitePara.h"
#include "dndc_main.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char CSF[200], CTF[200];
int m_TotalCells;
/////////////////////////////////////////////////////////////////////////////
// GlobeDataExtract dialog


GlobeDataExtract::GlobeDataExtract(CWnd* pParent /*=NULL*/)
	: CDialog(GlobeDataExtract::IDD, pParent)
{
	//{{AFX_DATA_INIT(GlobeDataExtract)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GlobeDataExtract::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GlobeDataExtract)
	DDX_Control(pDX, IDC_PROGRESS1, m_ConvertGo);
	DDX_Control(pDX, IDC_SouthAmerica, m_SouthAmerica);
	DDX_Control(pDX, IDC_Oceania, m_Oceania);
	DDX_Control(pDX, IDC_Europe, m_Europe);
	DDX_Control(pDX, IDC_Asia, m_Asia);
	DDX_Control(pDX, IDC_Africa, m_Africa);
	DDX_Control(pDX, IDC_NorthAmerica, m_NorthAmerica);
	DDX_Control(pDX, IDC_Continent, m_continent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GlobeDataExtract, CDialog)
	//{{AFX_MSG_MAP(GlobeDataExtract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GlobeDataExtract message handlers

void GlobeDataExtract::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int continent, country;

	continent = m_continent.GetCurSel()+1;

	if(continent==1)//Africa
	{
		country = m_Africa.GetCurSel()+1;
	}
	else if(continent==2)//Asia
	{
		country = m_Asia.GetCurSel()+1;
	}
	else if(continent==3)//Europe
	{
		country = m_Europe.GetCurSel()+1;
	}
	else if(continent==4)//N. America
	{
		country = m_NorthAmerica.GetCurSel()+1;
	}
	else if(continent==5)//Oceania
	{
		country = m_Oceania.GetCurSel()+1;
	}
	else if(continent==6)//S. America
	{
		country = m_SouthAmerica.GetCurSel()+1;
	}
	else {}

	//DataExtract1(continent, country);//This program converts old global data sets to new global database
	DataExtract2(continent, country);

	CDialog::OnOK();
}

void GlobeDataExtract::DataExtract1(int continent, int country)
{
	//This program converts old global data sets to new global database

	int RegionID, row, column, CellID1,CellID2,CellID3, CellID4,CellID5,CellID6,CountryID,layer;
	float lon, lat, AtmoN, SnowPack, S1, S2, S3, S4, S5, S6, S7, S8,jf;
	
	char SF1[200],SF2[200],SF3[200],SF4[200],SF5[200],SF6[200],SF7[200];
	char ww[200],countryname[200], CountName[200], ClimName[50];
	
	CString Fregion, TF1, TF2, TF3, TF4, TF5, TF6, TF7, CCL;
	FILE *tf1, *sf1, *sf2, *sf3, *sf4, *sf5, *sf6, *sf7;
	
	CString ContinentName[7]={"","Africa", "Asia", "Europe", "NorthAmerica", "Oceania","SouthAmerica"};

	//Open source and target files

	sprintf(SF1, "%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF2, "%s\\Database\\Globe\\%s\\GIS\\%s_2.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF3, "%s\\Database\\Globe\\%s\\GIS\\%s_3.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF6, "%s\\Database\\Globe\\%s\\GIS\\%s_6.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	
	sf1 = fopen(SF1, "r");
	if (sf1==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF1);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf1);
		
	sf2 = fopen(SF2, "r");
	if (sf2==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF2);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf2);

	sf3 = fopen(SF3, "r");
	if (sf3==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF3);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf3);
	fgets(ww, 300, sf3);

	sf6 = fopen(SF6, "r");
	if (sf6==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF6);
		AfxMessageBox(err);
		exit(0); 
	}

	TF1.Format("%s\\Database\\Globe\\%s_1.txt", ROOTDIR, ContinentName[continent]);
	tf1 = fopen(TF1, "w");
	if (tf1==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF1);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(tf1, "ID	Country	            Country_name	Lon	Lat	Climate_file	N_dep	Snow	SOCmax	SOCmin	Claymax	Claymin	pHmax	pHmin	Densmax	Densmin	Column	Row	Region\n");


	for(;;)
	{
		if(fscanf(sf1, "%d %s %d %d %f %f %d %d", &CellID1, CountName, &RegionID, &CountryID, &lon, &lat, &row, &column)!=8) 
			break;

		fscanf(sf2, "%d %s %f", &CellID2, ClimName, &AtmoN);
		fscanf(sf3, "%d %f %f %f %f %f %f %f %f", &CellID3, &S1, &S2, &S3, &S4, &S5, &S6, &S7, &S8);
		fscanf(sf6, "%d %f %d", &CellID6, &SnowPack, &layer);
		for(int i=1;i<=layer;i++) fscanf(sf6, "%f", &jf); 

		fprintf(tf1, "%6d %8d %26s %8.2f %8.2f %12s %8.2f %8.4f %8.4f %8.4f %8.4f %8.4f %8.2f %8.2f %8.2f %8.2f %8d %8d %8d\n", 
					CellID1, CountryID, CountName, lon, lat, ClimName, AtmoN, SnowPack, S1, S2, S3, S4, S5, S6, S7, S8, column, row, RegionID);
	
		//sprintf(CSF, "%s\\Database\\Globe\\%s\\Lib_clim\\2000\\%s_%s", ContinentName[continent], ContinentName[continent], ClimName);
		//sprintf(CTF, "%s\\Database\\Globe\\%s", ClimName);
		//FileCopy(CSF, CTF);
	}

	fclose(sf1);
	fclose(sf2);
	fclose(sf3);
	fclose(sf6);
	fclose(tf1);	

	AfxMessageBox("Done");
}

void GlobeDataExtract::DataExtract2(int continent, int country)
{
	int RegionID, row, column, CellID1,CellID2,CellID3, CellID4,CellID5,CellID6,CellID7,CountryID,layer;
	int CropNumber, jd,  CropTypeNumber, CropTypeID[50], i;
	char SystemName[150][150], CropName[50][50]; 
	float lon, lat, AtmoN, SnowPack, S1, S2, S3, S4, S5, S6, S7, S8,jf, ha[110], fert[50];
	float IrriHa, IrriPercent;
	char PlantHarvDates[150][150], FertDates[150][150], CropID[150][150], ManureRate[150][150];
	
	char SF1[200],SF2[200],SF3[200],SF4[200],SF5[200],SF6[200], SF7[200],ww[200],countryname[200], CountName[200], ClimName[50];
	CString Fregion, TF1, TF2, TF3, TF4, TF5, TF6, TF7, js;
	FILE *sf1, *sf2, *sf3, *sf4, *sf5, *sf6, *sf7, *tf1, *tf2, *tf3, *tf4, *tf5, *tf6, *tf7;
	
	CString ContinentName[7]={"","Africa", "Asia", "Europe", "NorthAmerica", "Oceania","SouthAmerica"};

	if(continent==1) 
	{
		CString CountryName[25]={"","Algeria", "Libya", "Egypt", "Mauritania", "Mali", "Niger", "Chad", "Sudan", 
		"Nigeria", "Ethiopia", "Cent_Afr_Rep", "Kenya", "DR_Congo", "Tanzania", "Angola", "Zambia", "Mozambique", "Namibia", 
		"Botswana", "Zimbabwe", "Madagascar", "South_Africa", "SaudiAraba", "Oman"};

		sprintf(countryname, "%s", CountryName[country]);
	}
	
	if(continent==2) 
	{
		CString CountryName[30]={"","China", "India", "Kazakhstan", "Uzbekistan", "Turkmenistan", "Azerbajian", 
		"Kyrgystan", "Tajikistan", "Afghanistan", "Iran", "Iraq", "Armenia","Mongolia", "NorthKorea", 
		"SouthKorea", "Japan", "Pakistan","Nepal","Bhutan","Bangladesh","Myanmar","Laos","Thailand","Cambodia","Vietnam","Philippines",
		"SriLanka", "Malaysia","Indonesia"};

		sprintf(countryname, "%s", CountryName[country]);
	}

	if(continent==3) 
	{
		CString CountryName[34]={"","Russia", "Germany", "Iceland","Norway","Sweden","Ireland","UK","Estonia",
		"Latvia","Denmark","Netherlands","Poland","Belarus", "Ukraine","Belgium","Switzerland","France","Spain",
		"Portugal","Italy","Austria","Hungary","Romania","Greece", "Slovenia","Slovakia", "Albania","Bulgaria","Czeck","Finland","Lithuania",
		"Turkey", "Geogia"};

		sprintf(countryname, "%s", CountryName[country]);
	}

	if(continent==4) 
	{
		CString CountryName[8]={"","UnitedStates", "Canada","Greenland", "Mexico","Cuba","CostaRica","Panama"};
		sprintf(countryname, "%s", CountryName[country]);
	}

	if(continent==5) 
	{
		CString CountryName[3]={"","Australia", "NewZealand"};
		sprintf(countryname, "%s", CountryName[country]);
	}

	if(continent==6) 
	{
		CString CountryName[6]={"","Brazil", "DominicanRep","Guatemala", "Honduras","Nicaragua"};
		sprintf(countryname, "%s", CountryName[country]);
	}
	

	//Open source and target files

	sprintf(SF1, "%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF2, "%s\\Database\\Globe\\%s\\GIS\\%s_2.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF3, "%s\\Database\\Globe\\%s\\GIS\\%s_3.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF4, "%s\\Database\\Globe\\%s\\GIS\\%s_4.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF5, "%s\\Database\\Globe\\%s\\GIS\\%s_5.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF6, "%s\\Database\\Globe\\%s\\GIS\\%s_6.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
	sprintf(SF7, "%s\\Database\\Globe\\%s\\GIS\\%s_7.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);

	//shu yi xia
	sf1 = fopen(SF1, "r");
	if (sf1==NULL) note(0, SF1);
	fgets(ww, 300, sf1);	
	m_TotalCells = 0;
	for(;;)
	{
		if(fscanf(sf1, "%d", &jd)!=1) break;
		else 
		{
			fgets(ww, 300, sf1);
			m_TotalCells++;
		}
	}
	fclose(sf1);

	sf1 = fopen(SF1, "r");
	if (sf1==NULL) note(0, SF1);
	fgets(ww, 300, sf1);
		
	sf2 = fopen(SF2, "r");
	if (sf2==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF2);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf2);
	fscanf(sf2, "%d", &CropNumber);
	for(i=1; i<=CropNumber; i++) fscanf(sf2, "%s ", SystemName[i]);	
	fscanf(sf2, "%d", &jd);
	for(i=1; i<=CropNumber; i++) fscanf(sf2, "%s ", CropID[i]);

	sf3 = fopen(SF3, "r");
	if (sf3==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF3);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf3);
	fscanf(sf3, "%d", &CropTypeNumber);
	for(i=1; i<=CropTypeNumber; i++) fscanf(sf3, "%s ", CropName[i]);
	fscanf(sf3, "%s", js);	
	for(i=1; i<=CropTypeNumber; i++) fscanf(sf3, "%d ", &CropTypeID[i]);

	sf4 = fopen(SF4, "r");
	if (sf4==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF4);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf4);

	sf5 = fopen(SF5, "r");
	if (sf5==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF5);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf5);
	fscanf(sf5, "%d", &jd);
	for(i=1; i<=jd; i++) fscanf(sf5, "%s ", js);
	fscanf(sf5, "%d", &jd);	
	for(i=1; i<=jd; i++) fscanf(sf5, "%s ", js);

	sf6 = fopen(SF6, "r");
	if (sf6==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF6);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, sf6);
	fscanf(sf6, "%d", &jd);
	for(i=1; i<=jd; i++) fscanf(sf6, "%s ", js);
	fscanf(sf6, "%d", &jd);	
	for(i=1; i<=jd; i++) fscanf(sf6, "%s ", js);

	sf7 = fopen(SF7, "r");
	if (sf7==NULL) note(0, SF7);
	fgets(ww, 300, sf7);
	fscanf(sf7, "%d", &CropNumber);
	for(i=1; i<=CropNumber; i++) fscanf(sf7, "%s ", SystemName[i]);	
	fscanf(sf7, "%d", &jd);
	for(i=1; i<=CropNumber; i++) fscanf(sf7, "%s ", CropID[i]);

	
	TF1.Format("%s\\Database\\Globe\\%s_1.txt", ROOTDIR, countryname);
	tf1 = fopen(TF1, "w");
	if (tf1==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF1);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(tf1, "ID	Country	            Country_name	Lon	Lat	Climate_file	N_dep	Snow	SOCmax	SOCmin	Claymax	Claymin	pHmax	pHmin	Densmax	Densmin	Column	Row	Region\n");

	TF2.Format("%s\\Database\\Globe\\%s_2.txt", ROOTDIR, countryname);
	tf2 = fopen(TF2, "w");
	if (tf2==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF2);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(tf2, "DNDC_global_data_2: crop acreage (ha)\n");	
	fprintf(tf2, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf2, "%8s ", SystemName[i]);
	fprintf(tf2, "\n");
	fprintf(tf2, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf2, "%15s ", CropID[i]);
	fprintf(tf2, "\n");


	TF3.Format("%s\\Database\\Globe\\%s_3.txt", ROOTDIR, countryname);
	tf3 = fopen(TF3, "w");
	if (tf3==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF3);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(tf3, "DNDC_global_data_3: Fertilizer rate (kg N/ha per crop)\n");	
	fprintf(tf3, "%8d ", CropTypeNumber);	
	for(i=1; i<=CropTypeNumber; i++) fprintf(tf3, "%8s ", CropName[i]);
	fprintf(tf3, "\n");	
	fprintf(tf3, "%8d ", CropTypeNumber);
	for(i=1; i<=CropTypeNumber; i++) fprintf(tf3, "%8d ", CropTypeID[i]);
	fprintf(tf3, "\n");

	TF4.Format("%s\\Database\\Globe\\%s_4.txt", ROOTDIR, countryname);
	tf4 = fopen(TF4, "w");
	if (tf4==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF4);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(tf4, "DNDC_global_data_4: Irrigated Area (ha) and Percent of Cell (%)\n");

	TF5.Format("%s\\Database\\Globe\\%s_5.txt", ROOTDIR, countryname);
	tf5 = fopen(TF5, "w");
	if (tf5==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF5);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(tf5, "DNDC_global_data_5: plant-harvest dates\n");	
	fprintf(tf5, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf5, "%8s ", SystemName[i]);
	fprintf(tf5, "\n");
	fprintf(tf5, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf5, "%15s ", CropID[i]);
	fprintf(tf5, "\n");

	TF6.Format("%s\\Database\\Globe\\%s_6.txt", ROOTDIR, countryname);
	tf6 = fopen(TF6, "w");
	if (tf6==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF6);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(tf6, "DNDC_global_data_6: fertilizing dates\n");	
	fprintf(tf6, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf6, "%8s ", SystemName[i]);
	fprintf(tf6, "\n");
	fprintf(tf6, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf6, "%15s ", CropID[i]);
	fprintf(tf6, "\n");

	TF7.Format("%s\\Database\\Globe\\%s_7.txt", ROOTDIR, countryname);
	tf7 = fopen(TF7, "w");
	if (tf7==NULL) note(1, TF7);
	fprintf(tf7, "DNDC_global_data_7: manure rates\n");	
	fprintf(tf7, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf7, "%8s ", SystemName[i]);
	fprintf(tf7, "\n");
	fprintf(tf7, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf7, "%15s ", CropID[i]);
	fprintf(tf7, "\n");

	int ii=0;
	for(;;)
	{
		ii++;

		if(fscanf(sf1, "%d %d %s %f %f %s %f %f %f %f %f %f %f %f %f %f %d %d %d", 
					&CellID1, &CountryID, CountName, &lon, &lat, ClimName, &AtmoN, &SnowPack, &S1, &S2, &S3, &S4, &S5, &S6, &S7, &S8, &column, &row, &RegionID)!=19) 
			break;

		fscanf(sf2, "%d", &CellID2);
		for(i=1; i<=CropNumber; i++) fscanf(sf2, "%f", &ha[i]);

		fscanf(sf3, "%d", &CellID3);
		for(i=1; i<=CropTypeNumber; i++) fscanf(sf3, "%f", &fert[i]);

		fscanf(sf4, "%d", &CellID4);
		fscanf(sf4, "%f", &IrriPercent);

		fscanf(sf5, "%d", &CellID5);
		for(i=1; i<=CropNumber; i++) 
		{
			fscanf(sf5, "%s", PlantHarvDates[i]);
		}

		fscanf(sf6, "%d", &CellID6);
		for(i=1; i<=CropNumber; i++) fscanf(sf6, "%s", FertDates[i]);
		
		fscanf(sf7, "%d", &CellID7);
		for(i=1; i<=CropNumber; i++) fscanf(sf7, "%s", ManureRate[i]);

		if(CellID1!=CellID2||CellID1!=CellID3||CellID1!=CellID4||CellID1!=CellID5||CellID1!=CellID6||CellID1!=CellID7)
		{
			CString note;
			note.Format("Cell ID inconsistency for cell %d", CellID1);
			AfxMessageBox(note);
			exit(0);
		}

		if(strcmp(CountName,countryname)==0)
		{
			fprintf(tf1, "%6d %8d %26s %8.2f %8.2f %12s %8.2f %8.4f %8.4f %8.4f %8.4f %8.4f %8.2f %8.2f %8.2f %8.2f %8d %8d %8d\n", 
					CellID1, CountryID, CountName, lon, lat, ClimName, AtmoN, SnowPack, S1, S2, S3, S4, S5, S6, S7, S8, column, row, RegionID);


			fprintf(tf2, "%8d ", CellID2);
			for(i=1; i<=CropNumber; i++) fprintf(tf2, "%8.0f ", ha[i]);
			fprintf(tf2, "\n");

			fprintf(tf3, "%8d ", CellID3);
			for(i=1; i<=CropTypeNumber; i++) fprintf(tf3, "%8.1f ", fert[i]);			
			fprintf(tf3, "\n");

			fprintf(tf4, "%8d ", CellID4);
			fprintf(tf4, "%8.2f\n", IrriPercent);	
			
			fprintf(tf5, "%8d ", CellID5);
			for(i=1; i<=CropNumber; i++) fprintf(tf5, "%15s ", PlantHarvDates[i]);
			fprintf(tf5, "\n");

			fprintf(tf6, "%8d ", CellID6);
			for(i=1; i<=CropNumber; i++) fprintf(tf6, "%15s ", FertDates[i]);
			fprintf(tf6, "\n");

			fprintf(tf7, "%8d ", CellID7);
			for(i=1; i<=CropNumber; i++) fprintf(tf7, "%15s ", ManureRate[i]);
			fprintf(tf7, "\n");
			
			sprintf(CSF, "%s\\Database\\Globe\\%s\\Lib_clim\\2000\\%s_%s_2000", ROOTDIR, ContinentName[continent], ContinentName[continent], ClimName);
			sprintf(CTF, "%s\\Database\\Globe\\%s_%s_2000", ROOTDIR, countryname, ClimName);
			FileCopy(CSF, CTF);
		}

		int BB=(int)(100.0*(float)ii/(float)m_TotalCells);
		m_ConvertGo.SetPos(BB);
	}

	fclose(sf1);
	fclose(sf2);
	fclose(sf3);
	fclose(sf4);
	fclose(sf5);
	fclose(sf6);
	fclose(sf7);

	fclose(tf1);
	fclose(tf2);
	fclose(tf3);
	fclose(tf4);
	fclose(tf5);
	fclose(tf6);
	fclose(tf7);

	AfxMessageBox("Done");


}

BOOL GlobeDataExtract::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ConvertGo.SetRange(0,100);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
