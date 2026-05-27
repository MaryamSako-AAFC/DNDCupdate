// ManureLagoon.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "ManureLagoon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManureLagoon dialog

float SlurryRetain[10] = {0.0,0,0}, SlurryToField[10] = {0.0,0.0}, SlurryToMarket[10]={0.0,0.0}, LagoonManureAplDepth[10]={0.0,0.0};
int DrainMonth[10]={0,0}, DrainDay[10]={0,0}, LagoonManureAplMethod[10]={0,0};

ManureLagoon::ManureLagoon(CWnd* pParent /*=NULL*/)
	: CDialog(ManureLagoon::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureLagoon)
	m_LagoonCapacity = 0.0f;
	m_RemoveFrequency = 0.0f;
	m_LagoonSurfaceArea = 0.0f;
	m_RainWater = -1;
	m_LagoonCover = -1;
	m_SlurryRetain = 0.0f;
	m_SlurryToField = 0.0f;
	m_SlurryToMarket = 0.0f;
	m_unit = -1;
	m_DrainTimes = 0;
	m_DrainID = 1;
	m_DrainMonth = 0;
	m_DrainDay = 0;
	m_LagoonManureAplMethod = 0;
	m_LagoonManureAplDepth = 0.0f;
	//}}AFX_DATA_INIT
}


void ManureLagoon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureLagoon)
	DDX_Text(pDX, IDC_LagoonCapacity, m_LagoonCapacity);
	DDX_Text(pDX, IDC_LagoonDays, m_RemoveFrequency);
	DDX_Text(pDX, IDC_LagoonSurfaceArea, m_LagoonSurfaceArea);
	DDX_Radio(pDX, IDC_RainWater, m_RainWater);
	DDX_Radio(pDX, IDC_Cover, m_LagoonCover);
	DDX_Text(pDX, IDC_Remain, m_SlurryRetain);
	DDX_Text(pDX, IDC_ToField, m_SlurryToField);
	DDX_Text(pDX, IDC_ToMarket, m_SlurryToMarket);
	DDX_Radio(pDX, IDC_unit, m_unit);
	DDX_Text(pDX, IDC_LagoonDrainTimes, m_DrainTimes);
	DDX_Text(pDX, IDC_DrainID, m_DrainID);
	DDX_Text(pDX, IDC_DrainMonth, m_DrainMonth);
	DDX_Text(pDX, IDC_DrainDay, m_DrainDay);
	DDX_Radio(pDX, IDC_LagoonManuMethod, m_LagoonManureAplMethod);
	DDX_Text(pDX, IDC_LagoonManureDepth, m_LagoonManureAplDepth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureLagoon, CDialog)
	//{{AFX_MSG_MAP(ManureLagoon)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureLagoon message handlers

void ManureLagoon::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	float LagoonCapacity, LagoonSurfaceArea;
	if(m_unit==0)
	{
		LagoonCapacity = m_LagoonCapacity;
		LagoonSurfaceArea = m_LagoonSurfaceArea;
	}
	else
	{
		LagoonCapacity = m_LagoonCapacity * foot3_m3;//ft3 -> m3 
		LagoonSurfaceArea = m_LagoonSurfaceArea * foot2_m2;//ft2 -> m2 
	}

	CString note;

	if(m_LagoonCapacity==0.0)
	{
		note.Format("Please define lagoon capacity");
		AfxMessageBox(note);
		return;
	}

	if(m_LagoonSurfaceArea==0.0)
	{
		note.Format("Please define lagoon surface area");
		AfxMessageBox(note);
		return;
	}
	
	if(m_SlurryToField+m_SlurryToMarket+m_SlurryRetain<0.9999||m_SlurryToField+m_SlurryToMarket+m_SlurryRetain>1.0001)
	{
		note.Format("The sum of fractions of the laggon slurry effluxes must be equal to 1");
		AfxMessageBox(note);
		return;
	}
	
	DrainMonth[m_DrainID] = m_DrainMonth;
	DrainDay[m_DrainID] = m_DrainDay; 
	SlurryToField[m_DrainID] = m_SlurryToField; 
	SlurryToMarket[m_DrainID] = m_SlurryToMarket;
	SlurryRetain[m_DrainID] = m_SlurryRetain;
	LagoonManureAplDepth[m_DrainID]=m_LagoonManureAplDepth;
	LagoonManureAplMethod[m_DrainID]=m_LagoonManureAplMethod;

	CString SF;
	FILE* sf;
	SF.Format("%s\\Inter\\ManureLagoon.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL)
	{		
		note.Format("Cannot create file %s", SF);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(sf, "%f %f %d %d %d\n", LagoonCapacity, LagoonSurfaceArea, m_LagoonCover+1, m_RainWater, m_DrainTimes);  
	for(int i=1;i<=m_DrainTimes;i++)
	{
		fprintf(sf, "%d %d %f %f %f\n", DrainMonth[i], DrainDay[i], SlurryToField[i], SlurryToMarket[i], SlurryRetain[i]);
		fprintf(sf, "%d %f\n", LagoonManureAplMethod[i], LagoonManureAplDepth[i]);
	}
	fclose(sf);
	
	CDialog::OnOK();
}

BOOL ManureLagoon::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString DB;
	FILE *db;	
	DB.Format("%s\\Result\\inter\\UnitSystem", ROOTDIR);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &m_unit);
	fclose(db);
	
	// TODO: Add extra initialization here
		CString SF;
		FILE* sf;
		SF.Format("%s\\Result\\Inter\\ManureLagoon.txt", ROOTDIR);
		sf=fopen(SF, "r");
		if(sf==NULL)
		{	
			sf=fopen(SF, "w");
			fprintf(sf, "%f  %f  %d  %d  %d\n", 0.0, 0.0, 0, 0, 0);
			fclose(sf);
			return(0);

			/*CString note;
			note.Format("Cannot open file %s", SF);
			AfxMessageBox(note);
			exit(0);*/
		}
		fscanf(sf, "%f  %f  %d  %d  %d", &m_LagoonCapacity, &m_LagoonSurfaceArea, &m_LagoonCover, &m_RainWater, &m_DrainTimes);  
		for(int i=1;i<=m_DrainTimes;i++)
		{
			fscanf(sf, "%d %d %f %f %f", &DrainMonth[i], &DrainDay[i], &SlurryToField[i], &SlurryToMarket[i], &SlurryRetain[i]);
			fscanf(sf, "%d %f\n", &LagoonManureAplMethod[i], &LagoonManureAplDepth[i]);
		}
		
		fclose(sf);

		m_LagoonCover--;
	
	if(m_unit==1)
	{
		m_LagoonCapacity /= foot3_m3;//m3 -> ft3 
		m_LagoonSurfaceArea /= foot2_m2;//m2 -> ft2 
	}
	
	if(m_DrainTimes>0)
	{
		m_DrainID = 1;
		m_DrainMonth = DrainMonth[1];
		m_DrainDay = DrainDay[1];
		m_SlurryToField = SlurryToField[1];
		m_SlurryToMarket = SlurryToMarket[1];
		m_SlurryRetain = SlurryRetain[1];
		m_LagoonManureAplDepth = LagoonManureAplDepth[1];
		m_LagoonManureAplMethod = LagoonManureAplMethod[1];
	
	}

	UpdateData(FALSE);

	Onunit();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ManureLagoon::Onunit() 
{
	// TODO: Add your control notification handler code here
	
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==0&&n_unit==1) 
	{
		m_LagoonCapacity *= foot3_m3;//ft3 -> m3 
		m_LagoonSurfaceArea *= foot2_m2;//ft2 -> m2 
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(TRUE); */
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(FALSE);*/
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void ManureLagoon::Onunit2() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==1&&n_unit==0) 
	{
		m_LagoonCapacity /= foot3_m3;//m3 -> ft3 
		m_LagoonSurfaceArea /= foot2_m2;//m2 -> ft2 
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(TRUE); */
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(FALSE);*/
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void ManureLagoon::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	DrainMonth[m_DrainID] = m_DrainMonth;
	DrainDay[m_DrainID] = m_DrainDay;
	SlurryRetain[m_DrainID] = m_SlurryRetain;
	SlurryToField[m_DrainID] = m_SlurryToField;
	SlurryToMarket[m_DrainID] = m_SlurryToMarket;
	LagoonManureAplDepth[m_DrainID] = m_LagoonManureAplDepth;
	LagoonManureAplMethod[m_DrainID] = m_LagoonManureAplMethod;
	
	m_DrainID++;
	if(m_DrainID>m_DrainTimes) m_DrainID = m_DrainTimes;

	m_DrainMonth = DrainMonth[m_DrainID];
	m_DrainDay = DrainDay[m_DrainID];
	m_SlurryRetain = SlurryRetain[m_DrainID];
	m_SlurryToField = SlurryToField[m_DrainID];
	m_SlurryToMarket = SlurryToMarket[m_DrainID];
	m_LagoonManureAplDepth = LagoonManureAplDepth[m_DrainID];
	m_LagoonManureAplMethod = LagoonManureAplMethod[m_DrainID];

	UpdateData(FALSE);
}

void ManureLagoon::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	DrainMonth[m_DrainID] = m_DrainMonth;
	DrainDay[m_DrainID] = m_DrainDay;
	SlurryRetain[m_DrainID] = m_SlurryRetain;
	SlurryToField[m_DrainID] = m_SlurryToField;
	SlurryToMarket[m_DrainID] = m_SlurryToMarket;
	LagoonManureAplDepth[m_DrainID] = m_LagoonManureAplDepth;
	LagoonManureAplMethod[m_DrainID] = m_LagoonManureAplMethod;
	
	m_DrainID--;
	if(m_DrainID<1) m_DrainID = 1;

	m_DrainMonth = DrainMonth[m_DrainID];
	m_DrainDay = DrainDay[m_DrainID];
	m_SlurryRetain = SlurryRetain[m_DrainID];
	m_SlurryToField = SlurryToField[m_DrainID];
	m_SlurryToMarket = SlurryToMarket[m_DrainID];
	m_LagoonManureAplDepth = LagoonManureAplDepth[m_DrainID];
	m_LagoonManureAplMethod = LagoonManureAplMethod[m_DrainID];

	UpdateData(FALSE);
}
