// MonteCarlo.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "MonteCarlo.h"
#include "graphexDoc.h"
#include "graphexView.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include "dndc_RegionFiles.h"
#include <stdlib.h>
#include <time.h>
#include "iostream"
#include "direct.h"
#include <io.h>
#include "../DNDCgo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//void MonteCarloRun(void);
int size, miss_flag;
float LAtitude;
char ThisName[300], CROPID[100];
/////////////////////////////////////////////////////////////////////////////
// MonteCarlo dialog


MonteCarlo::MonteCarlo(CWnd* pParent /*=NULL*/)
	: CDialog(MonteCarlo::IDD, pParent)
{
	//{{AFX_DATA_INIT(MonteCarlo)
	m_SOC = _T("");
	m_clay = _T("");
	m_density = _T("");
	m_pH = _T("");
	m_size = 0;
	//}}AFX_DATA_INIT
}


void MonteCarlo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MonteCarlo)
	DDX_Text(pDX, IDC_SOC, m_SOC);
	DDX_Text(pDX, IDC_clay, m_clay);
	DDX_Text(pDX, IDC_density, m_density);
	DDX_Text(pDX, IDC_pH, m_pH);
	DDX_Text(pDX, IDC_Size, m_size);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MonteCarlo, CDialog)
	//{{AFX_MSG_MAP(MonteCarlo)
	ON_BN_CLICKED(ID_data, Ondata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MonteCarlo message handlers

void MonteCarlo::Ondata() 
{
	// TODO: Add your control notification handler code here
	CString SOC, clay, pH, density;
	char ww[300];
	
	int i, year, TotalCrops;
	float minCLAY, maxCLAY, minBD, maxBD, minSOC, maxSOC, minPH, maxPH;
	float ddSOC, ddPH, ddBD, ddCLAY, lon, Ndeposit, Fert[5];
	char RootPart[300], ClimFile[300];
	char FullName[200], CountyName[300], PlantDate[50][50], HarvestDate[50][50];
	int cropD;
	float ha;
	CString cID;
	int countyID;

	for(i=0;i<=9;i++)
	{
		dSOC[i]=0.0;
		dPH[i]=0.0;
		dBD[i]=0.0;
		dCLAY[i]=0.0;
	}
	
	CString IDfile;
	FILE *fid;
		
	IDfile.Format("%s\\Inter\\SelectSite.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	fscanf(fid, "%s %s %d", ThisName, CountyName, &countyID);
	fscanf(fid, "%d  %f", &cropD, &ha);
	fscanf(fid, "%s %s ", RootPart, FullName);
	fscanf(fid, "%s", ClimFile);
	fscanf(fid, "%d", &year);
	fscanf(fid, "%f %f %f %f %f %f %f %f", &maxSOC, &minSOC, &maxCLAY, &minCLAY, &maxPH, &minPH, &maxBD, &minBD);
	fscanf(fid, "%f %f %f", &lon, &LAtitude, &Ndeposit);
	
	fscanf(fid, "%d", &TotalCrops); 
	for(i=1;i<=TotalCrops;i++)
	{
		fscanf(fid, "%s %s", HarvestDate[i], PlantDate[i]);
		fscanf(fid, "%f", &Fert[i]); 
		//sprintf(HarvestDate[i], "%s_%s", PlantDate[i], HarvestDate[i]);
	}
	fclose(fid);

	ddSOC = (maxSOC - minSOC) / 7.0;
	for(i=1;i<=8;i++)
	{
		dSOC[i] = minSOC + (float)(i-1)*ddSOC;
	}

	ddCLAY = (maxCLAY - minCLAY) / 7.0;
	for(i=1;i<=8;i++)
	{
		dCLAY[i] = minCLAY + (float)(i-1)*ddCLAY;
	}

	ddPH = (maxPH - minPH) / 7.0;
	for(i=1;i<=8;i++)
	{
		dPH[i] = minPH + (float)(i-1)*ddPH;
	}

	ddBD = (maxBD - minBD) / 7.0;
	for(i=1;i<=8;i++)
	{
		dBD[i] = minBD + (float)(i-1)*ddBD;
	}

	SOC.Format("%6.4f -- %6.4f:  %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f", minSOC, maxSOC, dSOC[1], dSOC[2],dSOC[3],dSOC[4],dSOC[5],dSOC[6],dSOC[7],dSOC[8]);
	clay.Format("%6.4f -- %6.4f:  %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f", minCLAY, maxCLAY, dCLAY[1], dCLAY[2],dCLAY[3],dCLAY[4],dCLAY[5],dCLAY[6],dCLAY[7],dCLAY[8]);
	pH.Format("%6.4f -- %6.4f:  %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f", minPH, maxPH, dPH[1], dPH[2],dPH[3],dPH[4],dPH[5],dPH[6],dPH[7],dPH[8]);
	density.Format("%6.4f -- %6.4f:  %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f | %6.4f", minBD, maxBD, dBD[1], dBD[2],dBD[3],dBD[4],dBD[5],dBD[6],dBD[7],dBD[8]);

	m_SOC = SOC;
	m_clay = clay;
	m_pH = pH;
	m_density = density;

	m_size = 4000;
		
	UpdateData(FALSE);	
}

void MonteCarlo::OnOK() 
{
	// TODO: Add extra validation here
	int i;
	UpdateData(TRUE);

	CString IDfile;
	FILE *fid;
		
	IDfile.Format("%s\\Inter\\MonteCarlo.txt", OUTPUT);
	fid = fopen(IDfile, "w");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("1 Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	
	fprintf(fid, "%d\n", m_size);

	for(i=1;i<=8;i++)
	{
		fprintf(fid, "%f ", dSOC[i]);
	}
	fprintf(fid, "\n");

	for(i=1;i<=8;i++)
	{
		fprintf(fid, "%f ", dCLAY[i]);		 
	}
	fprintf(fid, "\n");

	for(i=1;i<=8;i++)
	{
		fprintf(fid, "%f ", dBD[i]);		 
	}
	fprintf(fid, "\n");

	for(i=1;i<=8;i++)
	{
		fprintf(fid, "%f ", dPH[i]);		 
	}
	fprintf(fid, "\n");
		
	fclose(fid);

	CDialog::OnOK();
}

void CGraphexView::RunMonteCarlo(int method) 
{
	int k, i, m_size, landtype, County_ID, TotalCrops;
	int RN1, RN2, RN3, RN4;
	float ha, lon, Ndeposit, BaseCO2=350.0;
	FILE *f1, *f2;
	char File1[200],File2[200];	
	char state_name[200], county_name[200], climfile_ID[300];
	float dSOC[10], dCLAY[10], dBD[10], dPH[10];
	float SOC, Clay, pH, BD;
	char FullName[300], CropFileName[300];
	char RootPart[300], ClimFile[300];
	char CountyName[300];
	char WW[300], HarvestDate[50][50], NewHarvestDate[50][50], PlantDate[50][50];
	int year, county_ID1;	
	float minCLAY, maxCLAY, minBD, maxBD, minSOC, maxSOC, minPH, maxPH;
	char ClimFileName[150], FarmFileName[150], FertDates[100], ManureRate[100];
	float xx[10]={0.0,0.0}, Fert[5]={0.0,0.0}, animal[10]={0.0,0.0};
	CString note;
	FILE *mc;

	CString IDfile;
	FILE *fid;

	IDfile.Format("%s\\Inter\\SelectSite.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	fscanf(fid, "%s %s %d", ThisName, CountyName, &County_ID);
	fscanf(fid, "%s  %f", CROPID, &ha);
	fscanf(fid, "%s %s ", RootPart, FullName);
	fscanf(fid, "%s", ClimFile);
	fscanf(fid, "%d", &year);
	fscanf(fid, "%f %f %f %f %f %f %f %f", &maxSOC, &minSOC, &maxCLAY, &minCLAY, &maxPH, &minPH, &maxBD, &minBD);
	fscanf(fid, "%f %f %f", &lon, &LAtitude, &Ndeposit);

	fscanf(fid, "%d", &TotalCrops); 
	for(i=1;i<=TotalCrops;i++)
	{
		fscanf(fid, "%s %s", HarvestDate[i], PlantDate[i]);
		fscanf(fid, "%f", &Fert[i]); 
		//sprintf(NewHarvestDate[i], "%s_%s", PlantDate[i], HarvestDate[i]);
	}
	fclose(fid);	

	sprintf(ClimFileName, "%s", ClimFile);

	region_site_files(ThisName, lon, LAtitude, ClimFileName, CountyName);

	miss_flag = region_climate_files(ClimFileName, LAtitude, Ndeposit, BaseCO2, County_ID, 0.0, 0, 1, year, 0, 0, 0, 0);

	int CropID[60]={0,0};
	float DMaxYield[100], DTDD[100], DWaterDemand[100];

	region_farm_files(CROPID, state_name, 1, 0, 1, 0, "0", 0, FarmFileName, "region", "county", 0.0, HarvestDate[1],
						PlantDate[1], animal, 0.0, "0", 45.0, "0", "0", "0", "0", 0, CropID, 1, DMaxYield, DTDD, DWaterDemand);

	////////////////////////////////////////////////////////////////
	IDfile.Format("%s\\Inter\\MonteCarlo.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("2. Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}	
	fscanf(fid, "%d", &m_size);
	for(i=1;i<=8;i++) fscanf(fid, "%f ", &dSOC[i]);	
	for(i=1;i<=8;i++) fscanf(fid, "%f ", &dCLAY[i]);		 	
	for(i=1;i<=8;i++) fscanf(fid, "%f ", &dBD[i]);		 	
	for(i=1;i<=8;i++) fscanf(fid, "%f ", &dPH[i]);		 	
	fclose(fid);
	
	int MCN=0;
	long t;
	long int xyz, r1, r2, r3, r4;
	
	xyz = (long int)time(NULL);

	if(method==0) size = m_size;
	else size = 2;
	for(k=1; k<=size; k++)
	{
		MCN++;

		if(method==0)
		{
			r1 = rand();
			RN1 = (r1+xyz)%8+1;	
			r2 = rand();
			RN2 = (r2+xyz)%8+1;	
			r3 = rand();
			RN3 = (r3+xyz)%8+1;
			r4 = rand();
			RN4 = (r4+xyz)%8+1;
			SOC = dSOC[RN1];
			Clay = dCLAY[RN2];
			pH = dPH[RN3];
			BD = dBD[RN4];
		}
		else
		{			
			if(k==1)
			{
				RN1 = 1;
				RN2 = 8;
				RN3 = 1;
			}
			else
			{
				RN1 = 8;
				RN2 = 1;
				RN3 = 8;				
			}
			RN4 = 4;
			SOC = dSOC[RN1];
			Clay = dCLAY[RN2];
			pH = dPH[RN3];
			BD = (dBD[1]+dBD[8])*0.5;
		}

		
		note.Format("%s\\Inter\\Combination_%d", OUTPUT, k);
		mc=fopen(note, "w");
		if ( mc == NULL )
		{
			CString mess;
			mess.Format("Can not create %s.", note);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(mc, "%f %f %f %f\n", SOC, Clay, pH, BD);
		fprintf(mc, "%d %d %d %d\n", RN1, RN2, RN3, RN4);
		fclose(mc);
	}

	note.Format("%s\\Inter\\MonteCarlo_index", OUTPUT);
	mc=fopen(note, "w");
	if ( mc == NULL )
	{
		CString mess;
		mess.Format("Can not create %s.", note);
		AfxMessageBox(mess);
		exit(0);
	}
	fprintf(mc, "%d %s %s %f\n", size, CROPID, ThisName, LAtitude);
	fclose(mc);

	//note.Format("Ready to run Monte Carlo with sample size %d", size);
	//AfxMessageBox(note);
}

