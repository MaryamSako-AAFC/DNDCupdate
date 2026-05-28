// GlobeData.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "GlobeData.h"
#include "math.h"
#include "direct.h"
#include "SitePara.h"
#include "dndc_tool.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//void Glean_StringW(char *String, int Num1, int Num2, char *Sub_Str);
int SelectedContinent;
/////////////////////////////////////////////////////////////////////////////
// GlobeData dialog


GlobeData::GlobeData(CWnd* pParent /*=NULL*/)
	: CDialog(GlobeData::IDD, pParent)
{
	//{{AFX_DATA_INIT(GlobeData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GlobeData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GlobeData)
	DDX_Control(pDX, IDC_Continent, m_Continent);
	DDX_Control(pDX, IDC_DataFileList, m_DataFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GlobeData, CDialog)
	//{{AFX_MSG_MAP(GlobeData)
	ON_BN_CLICKED(IDC_DataFile, OnDataFile)
	ON_BN_CLICKED(IDC_DataCalculate, OnDataCalculate)
	ON_CBN_SELCHANGE(IDC_Continent, OnSelchangeContinent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GlobeData message handlers

void GlobeData::OnDataFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char RegionName[200];
	CString cst;
	
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );

	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_DataFileName.GetCount();
	if (num==1) return;
	
	k=m_DataFileName.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_DataFileName.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_DataFileName.GetCount()==1) break;
		k++;
	}
	m_DataFileName.SetCurSel(k);
	
	//RegionSelectFlag = 1;

	CString CP;
	int i, L1, L2;

	int LL=strlen(FileName);
	for(i=LL; i>=0; i--)
	{
		if(FileName[i]=='_') 
		{
			L1=i-1;
			break;
		}
	}

	for(i=LL; i>=0; i--)
	{
		if(FileName[i]==92) 
		{
			L2=i+1;
			break;
		}
	}

	Glean_String(FileName, 0, L1, RegionName);
	
	CP.Format("%s", RegionName);

	int RegionCode = 0;

	CString Fregion;
	FILE *region;

	Fregion.Format("%s\\GlobeSourceData", INTER);
	region = fopen(Fregion, "w");

	if (region==NULL)
	{
		char err[120];
		sprintf(err, "Can not create %s", Fregion);
		AfxMessageBox(err);
		exit(0); 
	}

	fprintf(region, "%d %d\n", -1, 0);
	//fprintf(region, "%s\n", CP);
	fprintf(region, "%s_1.txt\n", CP);
	fprintf(region, "%s_2.txt\n", CP);
	fprintf(region, "%s_3.txt\n", CP);
	fprintf(region, "%s_4.txt\n", CP);
	fclose (region);
	
}

void GlobeData::OnDataCalculate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString DF, RF;
	FILE *df, *rf;

	float C,CLAY,T,P,PH,CN,M,Rf,LU, N2O;
	int i=0;

/*	RF.Format("%s\\Record\\SiteSummary\\GlobalN2O.txt", OUTPUT);
	rf=fopen(RF, "w");
	if (rf==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", RF);
		AfxMessageBox(err);
		exit(0); 
	}
	fprintf(rf, "No   Background_N2O  Fertilizer_N2O  Total_N2O\n");

	DF.Format("%s", FileName);
	df=fopen(DF, "r");
	if (df==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", DF);
		AfxMessageBox(err);
		exit(0); 
	}

	//fgets(W, 200, df);
	//fgets(W, 200, df);
	//fgets(W, 200, df);
	//fgets(W, 200, df);
	for(;;)
	{
		i++;

		if(fscanf(df, "%f %f %f %f %f %f %f %f %f",&C,&CLAY,&T,&P,&PH,&CN,&M,&Rf,&LU)!=9) break;
		else 
		{
			N2O = N2O_flux(C,CLAY,T,P,PH,CN,M,Rf,LU);
			fprintf(rf, "%4d %11.3f %11.3f %11.3f\n", i, Background_N2O, Fertilizer_N2O, N2O);
		}
	}

	fclose(df);
	fclose(rf);
*/
	AfxMessageBox("Calculation is accomplished");
}

float GlobeData::N2O_flux(float C,float CLAY,float T,float P,float PH,float CN,float M,float Rf,float LU)
{
	float N2O;
	float a, fal, fam, fact, b, fbt, W;
	float k, fkp, fkt, fkst, fkph, fkct, fkm, fkft;

	a = 245.0 * C - 1.4385; 
	b = 21.704 * log(C) + 122.51;
	k = 300.0;
	fal = 1.0 / (LU*LU);
	fam = 0.9259*exp(0.0005*M);
	fact = 1E-05*CN*CN - 0.0053*CN + 1.5254;
	fbt = 0.2207*exp(0.1858*T);
	fkp =  0.000001*P*P - 0.004*P + 5.5656;
	fkt = 0.2356*exp(0.1694*T);
	fkst = 1.0339*exp(3.9509*CLAY);
	fkph = 0.2029*PH*PH - 2.7911*PH + 10.568;
	fkct = 0.0745*exp(0.0166*CN);
	fkm = -0.00009*M + 0.9808;
	fkft = 1.0;


	W = k* fkp* fkt * fkst * fkph * fkct * fkm * fkft;
	Background_N2O = a* fal*fam*fact;
	Fertilizer_N2O = b* fbt * Rf /( Rf + W);
	N2O = Background_N2O + Fertilizer_N2O;

	return(N2O);
}

/*void Glean_StringW(char *String, int Num1, int Num2, char *Sub_Str)
// Abstract part of String (from Num1 to Num2) and put to Sub_Str

{
  int i, l;
  l=strlen(String);
  if(Num1>Num2)  {
    //printf("%s\n",String);
    //Hint("Num1>Num2 in Glean_String",String);
    Sub_Str[0]='\0';
    return;
  }
  if (Num1>l) {
    //Hint("Out of range ",String);
    Sub_Str[0]='\0';
    return;
  }
    if (Num2>l)  Num2=l;
    for(i=Num1;i<=Num2;i++)
       Sub_Str[i-Num1]=String[i];
       Sub_Str[i-Num1]='\0';
}*/

void GlobeData::OnSelchangeContinent() 
{
	// TODO: Add your control notification handler code here
	
	SelectedContinent=m_Continent.GetCurSel()+1;

}

void GlobeData::OnOK() 
{
	// TODO: Add extra validation here
	int RegionID, row, column;
	int CellID1, CountryID;
	
	char SF1[200], ww[200], CountryName[150];
	float lon, lat;

	CString ContinentName[106]={" ", "Africa", "Asia", "Europe", "NorthAmerica",  
		"Oceania","SouthAmerica","Canada", "UnitedStates", "Brazil", "Russia", "China", "India", "Australia",
		"Algeria", "Libya", "Egypt", "Mauritania", "Mali", "Niger", "Chad", "Sudan", 
		"Nigeria", "Ethiopia", "Cent_Afr_Rep", "Kenya", "DR_Congo", "Tanzania", "Angola",
		"Zambia", "Mozambique", "Namibia", "Botswana", "Zimbabwe", "Madagascar", "South_Africa"
		"Kazakhstan", "Uzbekistan", "Turkmenistan", "Azerbajian", "Kyrgystan", "Tajikistan", "Afghanistan",
		"Iran", "Iraq", "Armenia", "Turkey", "Geogia", "Mongolia", "NorthKorea", "SouthKorea", "Japan", "Pakistan", 
		"SaudiAraba", "Oman","Nepal","Bhutan","Bangladesh","Myanmar","Laos","Thailand","Cambodia","Vietnam","Philippines",
		"SriLanka", "Malaysia","Indonesia",
		"Iceland","Norway","Sweden","Ireland","UK","Estonia","Latvia","Denmark","Netherlands","Germany","Poland","Belarus",
		"Ukraine","Belgium","Switzerland","France","Spain","Portugal","Italy","Austria","Hungary","Romania","Greece",
		"Slovenia","Slovakia", "Albania","Bulgaria","Czeck","Finland","Lithuania",
		"Greenland","Mexico","Cuba","DominicanRep","Guatemala", "CostaRica","Honduras","Nicaragua","Panama"
	
	};

	CString Fregion, TF1, TF2, TF3, TF4, TF5, TF6, CCL;
	FILE *tf1, *sf1;

	//Open source and target files

	sprintf(SF1, "%s\\Database\\Globe\\GIS\\Globe_1.txt", ROOTDIR);
//	sprintf(SF2, "%s\\Database\\Globe\\GIS\\Globe_2.txt");
//	sprintf(SF3, "%s\\Database\\Globe\\GIS\\Globe_3.txt");
//	sprintf(SF4, "%s\\Database\\Globe\\GIS\\Globe_4.txt");
//	sprintf(SF5, "%s\\Database\\Globe\\GIS\\Globe_5.txt");
//	sprintf(SF6, "%s\\Database\\Globe\\GIS\\Globe_6.txt");
	
	sf1 = fopen(SF1, "r");
	if (sf1==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF1);
		AfxMessageBox(err);
		exit(0); 
	}
	
/*	sf2 = fopen(SF2, "r");
	if (sf2==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF2);
		AfxMessageBox(err);
		exit(0); 
	}

	sf3 = fopen(SF3, "r");
	if (sf3==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF3);
		AfxMessageBox(err);
		exit(0); 
	}

	sf4 = fopen(SF4, "r");
	if (sf4==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF4);
		AfxMessageBox(err);
		exit(0); 
	}

	sf5 = fopen(SF5, "r");
	if (sf5==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF5);
		AfxMessageBox(err);
		exit(0); 
	}

	sf6 = fopen(SF6, "r");
	if (sf6==NULL)
	{
		char err[120];
		sprintf(err, "Cannot open %s", SF6);
		AfxMessageBox(err);
		exit(0); 
	}
*/
	fgets(ww, 300, sf1);
/*	fgets(ww, 300, sf2);
	fgets(ww, 300, sf3);
	fgets(ww, 300, sf3);	
	fgets(ww, 300, sf4);
	fgets(ww, 300, sf5);
	fgets(ww, 300, sf6);	
*/	
/*	fscanf(sf4, "%d", &CropNumber);
	for(i=1; i<=CropNumber; i++) fscanf(sf4, "%s ", SystemName[i]);	
	fscanf(sf4, "%s", js);
	for(i=1; i<=CropNumber; i++) fscanf(sf4, "%d ", &CropID[i]);	
	
	fscanf(sf5, "%d", &CropTypeNumber);
	for(i=1; i<=CropTypeNumber; i++) fscanf(sf5, "%s ", CropName[i]);
	fscanf(sf5, "%s", js);	
	for(i=1; i<=CropTypeNumber; i++) fscanf(sf5, "%d ", &CropTypeID[i]);
*/								
	TF1.Format("%s\\Database\\Globe\\%s_1.txt", ROOTDIR, ContinentName[SelectedContinent]);
	tf1 = fopen(TF1, "w");
	if (tf1==NULL)
	{
		char err[120];
		sprintf(err, "Cannot create %s", TF1);
		AfxMessageBox(err);
		exit(0); 
	}

/*	TF2.Format("%s\\Database\\Globe\\%s_2.txt", ContinentName[SelectedContinent]);
	tf2 = fopen(TF2, "w");
	TF3.Format("%s\\Database\\Globe\\%s_3.txt", ContinentName[SelectedContinent]);
	tf3 = fopen(TF3, "w");
	TF4.Format("%s\\Database\\Globe\\%s_4.txt", ContinentName[SelectedContinent]);
	tf4 = fopen(TF4, "w");
	TF5.Format("%s\\Database\\Globe\\%s_5.txt", ContinentName[SelectedContinent]);
	tf5 = fopen(TF5, "w");
	TF6.Format("%s\\Database\\Globe\\%s_6.txt", ContinentName[SelectedContinent]);
	tf6 = fopen(TF6, "w");
*/
	fprintf(tf1, "DNDC_global_data_1: Grid cell location and country name and ID\n");
/*	fprintf(tf2, "DNDC_global_data_2: Climate file names and atmo N deposit rate (ppm)\n");

	fprintf(tf3, "Grid_ID	SOC (kg C/kg soil)	Clay fraction	pH		Bulk density (mg/cm3)\n");
	fprintf(tf3, "		max	min	max	min	max	min	max	min\n");

	fprintf(tf4, "DNDC_global_data_4: crop acreage (ha)\n");	
	fprintf(tf4, "%8d ", CropNumber);
	for(i=1; i<=CropNumber; i++) fprintf(tf4, "%8s ", SystemName[i]);
	fprintf(tf4, "\n");
	fprintf(tf4, "%8s ", "System");
	for(i=1; i<=CropNumber; i++) fprintf(tf4, "%8d ", CropID[i]);
	fprintf(tf4, "\n");

	fprintf(tf5, "DNDC_global_data_5: Fertilizer rate (kg N/ha per crop)\n");	
	fprintf(tf5, "%8d ", CropTypeNumber);	
	for(i=1; i<=CropTypeNumber; i++) fprintf(tf5, "%8s ", CropName[i]);
	fprintf(tf5, "\n");	
	fprintf(tf5, "%8s ", "Crop");
	for(i=1; i<=CropTypeNumber; i++) fprintf(tf5, "%8d ", CropTypeID[i]);
	fprintf(tf5, "\n");

	fprintf(tf6, "DNDC_global_data_6: Initial snowpack and soil temperature\n");
*/	
	//Read source files
	for(int k=1; k<=67685; k++)
	{
		float TotalHa=0.0;

		fscanf(sf1, "%d %s %d %d %f %f %d %d", &CellID1, CountryName, &RegionID, &CountryID, &lon, &lat, &row, &column);
/*		fscanf(sf2, "%d %s %f", &CellID2, ClimName, &AtmoN);
		fscanf(sf3, "%d %f %f %f %f %f %f %f %f", &CellID3, &S1, &S2, &S3, &S4, &S5, &S6, &S7, &S8);
		
		fscanf(sf4, "%d", &CellID4);
		for(i=1; i<=CropNumber; i++) 
		{
			fscanf(sf4, "%f", &ha[i]);
			TotalHa += ha[i];
		}
		
		fscanf(sf5, "%d", &CellID5);
		for(i=1; i<=CropTypeNumber; i++) fscanf(sf5, "%f", &fert[i]);

		fscanf(sf6, "%d %f %d", &CellID6, &SnowPack, &SoilLayers);
		for(i=1; i<=SoilLayers; i++) fscanf(sf6, "%f", &SoilT[i]);

		if(CellID1!=CellID2||CellID1!=CellID3||CellID1!=CellID4||CellID1!=CellID5||CellID1!=CellID6)
		{
			CString note;
			note.Format("Data errot at %d", CellID1);
			AfxMessageBox(note);
			exit(0);
		}
*/
		if(SelectedContinent==RegionID)//Continent assemply
		{
			//selecting
			/*CCL.Format("%s\\Database\\Globe\\ContinentCountryCode.txt");
			ccl = fopen(CCL, "r");
			if (ccl==NULL)
			{
				char err[120];
				sprintf(err, "Cannot open %s", CCL);
				AfxMessageBox(err);
				exit(0); 
			}
			fgets(ww, 300, ccl);
		
			for(;;)
			{
				if(fscanf(ccl, "%d %d", &CtyID, &CntID)!=2)
				{
					fclose (ccl);
					break;
				}
				else 
				{
					fgets(ww, 300, ccl);
				
					if(CtyID==CountryID && CntID==SelectedContinent)
					{
							fclose (ccl);*/
							
			fprintf(tf1, "%8d %26s %8d %8d %8.2f %8.2f %8d %8d\n", CellID1, CountryName, RegionID, CountryID, lon, lat, row, column);
/*			fprintf(tf2, "%8d %12s %8.2f\n", CellID2, ClimName, AtmoN);
			fprintf(tf3, "%d %8.4f %8.4f %8.4f %8.4f %8.2f %8.2f %8.2f %8.2f\n", CellID3, S1, S2, S3, S4, S5, S6, S7, S8);
			fprintf(tf4, "%8d ", CellID4);
			for(i=1; i<=CropNumber; i++) fprintf(tf4, "%8.0f ", ha[i]);
			fprintf(tf4, "\n");
			fprintf(tf5, "%8d ", CellID4);
			for(i=1; i<=CropTypeNumber; i++) 
			{
				if(i<CropTypeNumber) fprintf(tf5, "%8.1f ", fert[i]);
				else fprintf(tf5, "%8.4f ", fert[i]);
			}
			fprintf(tf5, "\n");
			fprintf(tf6, "%8d %8.3f %8d ", CellID6, SnowPack, SoilLayers);
			for(i=1; i<=SoilLayers; i++) fprintf(tf6, "%8.1f ", SoilT[i]);
			fprintf(tf6, "\n");
*/							
//			sprintf(CSF, "%s\\Database\\Globe\\Lib_clim\\2000\\%s", ClimName);
//			sprintf(CTF, "%s\\Database\\Globe\\%s_%s", CountryName, ClimName);
//			FileCopy(CSF, CTF);
//			break;
						
			}
			else {}
			
		}//end of loop k
/*		else //Country assemply
		{
			int SelectCountry[99] = {27, 153, 20, 103, 186, 162, 240, 106, 110, 132, 87, 86, 117, 114, 95,
									118, 93, 109, 208, 224, 210, 222, 211, 219, 227, 204, 212, 231, 220,
									101,168,167,171,179,182, 178,173, 98,170,137,133,94,188,191, 187,181,
									176,164,180,184,183,195,193,197,192,198,190,166,194,238,68,102,104,69,
									73,155,157,140,151,148,142,154,161,146,152,147,81,80,124,138,141,160,
									134,144,143,121, 130,139,156,158,66,31,53,43,28,52,55,56,57};

			if(SelectCountry[SelectedContinent-7]==CountryID) 
			{
				fprintf(tf1, "%8d %26s %8d %8.2f %8.2f\n", CellID1, CountryName, CountryID, lon, lat);
				fprintf(tf2, "%8d %12s %8.2f\n", CellID2, ClimName, AtmoN);
				fprintf(tf3, "%d %8.4f %8.4f %8.4f %8.4f %8.2f %8.2f %8.2f %8.2f\n", CellID3, S1, S2, S3, S4, S5, S6, S7, S8);
				fprintf(tf4, "%8d ", CellID4);
				for(i=1; i<=CropNumber; i++) fprintf(tf4, "%6.0f ", ha[i]);
				fprintf(tf4, "\n");
				fprintf(tf5, "%8d ", CellID5);
				for(i=1; i<=CropTypeNumber; i++) fprintf(tf5, "%6.1f ", fert[i]);
				fprintf(tf5, "\n");

				fprintf(tf6, "%8d %8.3f %8d ", CellID6, SnowPack, SoilLayers);
				for(i=1; i<=SoilLayers; i++) fprintf(tf6, "%8.1f ", SoilT[i]);
				fprintf(tf6, "\n");

				sprintf(CSF, "%s\\Database\\Globe\\Lib_clim\\2000\\%s", ClimName);
				sprintf(CTF, "%s\\Database\\Globe\\%s_%s", CountryName, ClimName);
				FileCopy(CSF, CTF);
			}
		}
	}
*/
	fclose(sf1);
/*	fclose(sf2);
	fclose(sf3);
	fclose(sf4);
	fclose(sf5);
	fclose(sf5);
	fclose(tf1);
	fclose(tf2);
	fclose(tf3);
	fclose(tf4);
	fclose(tf5);
	fclose(tf6);
*/
	AfxMessageBox("Done");
	CDialog::OnOK();
}

