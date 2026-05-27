// WizardUncertainty.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "WizardUncertainty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WizardUncertainty dialog


WizardUncertainty::WizardUncertainty(CWnd* pParent /*=NULL*/)
	: CDialog(WizardUncertainty::IDD, pParent)
{
	//{{AFX_DATA_INIT(WizardUncertainty)
	m_StateName = _T("");
	m_CountyName = _T("");
	m_CropName = _T("");
	m_DensityRange = _T("");
	m_PhRange = _T("");
	m_SOCRange = _T("");
	m_ClayRange = _T("");
	m_Size = 0;
	m_Year = 0;
	//}}AFX_DATA_INIT
}


void WizardUncertainty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WizardUncertainty)
	DDX_Text(pDX, IDC_StateName, m_StateName);
	DDX_Text(pDX, IDC_CountyName, m_CountyName);
	DDX_Text(pDX, IDC_CropName, m_CropName);
	DDX_Text(pDX, IDC_density, m_DensityRange);
	DDX_Text(pDX, IDC_pH, m_PhRange);
	DDX_Text(pDX, IDC_SOC, m_SOCRange);
	DDX_Text(pDX, IDC_clay, m_ClayRange);
	DDX_Text(pDX, IDC_Size, m_Size);
	DDX_Text(pDX, IDC_year, m_Year);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WizardUncertainty, CDialog)
	//{{AFX_MSG_MAP(WizardUncertainty)
	ON_BN_CLICKED(ID_WizardUncertainData, OnWizardUncertainData)
	ON_BN_CLICKED(ID_MSFmethod, OnMSFmethod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WizardUncertainty message handlers

void WizardUncertainty::OnWizardUncertainData() 
{
	// TODO: Add your control notification handler code here
	CString SOC, clay, pH, density, js;
	char ww[300];
	

	CString cID, countyID;
	int i;
	float minCLAY, maxCLAY, minBD, maxBD, minSOC, maxSOC, minPH, maxPH, jf;
	float ddSOC, ddPH, ddBD, ddCLAY;
	
	char StateName[200], CountyName[300];
	int cropD;

	for(i=0;i<=9;i++)
	{
		dSOC[i]=0.0;
		dPH[i]=0.0;
		dBD[i]=0.0;
		dCLAY[i]=0.0;
	}
	
	CString IDfile;
	FILE *fid;
		
	IDfile.Format("%s\\inter\\SelectedCounty.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("3. Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	fscanf(fid, "%s %s %d", StateName, CountyName, &cropD);		
	fclose(fid);

	m_StateName.Format("%s", StateName);
	m_CountyName.Format("%s", CountyName);
	dndc74 zzz;
	m_CropName.Format("%s", zzz.CropSystem[cropD]);


	IDfile.Format("%s\\inter\\SoilRanges.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	fgets(ww, 300, fid);
	fscanf(fid, "%s %f %f %f", js, &jf, &maxSOC, &minSOC);
	fscanf(fid, "%s %f %f %f", js, &jf, &maxCLAY, &minCLAY);
	fscanf(fid, "%s %f %f %f", js, &jf, &maxPH, &minPH);
	fscanf(fid, "%s %f %f %f", js, &jf, &maxBD, &minBD);

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


	m_SOCRange = SOC;
	m_ClayRange = clay;
	m_PhRange = pH;
	m_DensityRange = density;

	m_Size = 5000;
		
	UpdateData(FALSE);
	
	
}


void WizardUncertainty::OnOK() 
{
	// TODO: Add extra validation here
	int i;
	UpdateData(TRUE);

	CString IDfile;
	FILE *fid;
		
	IDfile.Format("%s\\inter\\MonteCarlo.txt", OUTPUT);
	fid = fopen(IDfile, "w");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("3 Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	
	fprintf(fid, "%d\n", m_Size);

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

void WizardUncertainty::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();	
}

void WizardUncertainty::OnMSFmethod() 
{
	// TODO: Add your control notification handler code here
	int i;
	UpdateData(TRUE);

	CString IDfile;
	FILE *fid;
		
	IDfile.Format("%s\\inter\\MonteCarlo.txt", OUTPUT);
	fid = fopen(IDfile, "w");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("4 Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	
	fprintf(fid, "%d\n", m_Size);

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


	CString SSS;
		FILE* sss;
		SSS.Format("%s\\Inter\\MonteCarloSOC.txt", OUTPUT);
		sss=fopen(SSS, "w");
		if(sss==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SSS);
			AfxMessageBox(note);
			exit(0);
		}
		fprintf(sss, "%d\n", 1);
		fprintf(sss, "%f %f %f %f %f %f\n", 
			0.025, 0.025, 0.95, 5.0, 0.5, 100.0);
		
		fclose(sss);

	//RunWizardMonteCarlo(1);
	
}

void WizardUncertainty::OnMSFmethod2() 
{
	// TODO: Add your control notification handler code here
	int i;
	UpdateData(TRUE);

	CString IDfile;
	FILE *fid;
		
	IDfile.Format("%s\\inter\\MonteCarlo.txt", OUTPUT);
	fid = fopen(IDfile, "w");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("4 Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	
	fprintf(fid, "%d\n", m_Size);

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

	//RunWizardMonteCarlo(1);
	
}

/*void WizardUncertainty::OnWizardMonteCarlo() 
{
	// TODO: Add your control notification handler code here
	RunWizardMonteCarlo(0);
}*/
