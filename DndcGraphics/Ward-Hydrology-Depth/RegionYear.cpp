// RegionYear.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "RegionYear.h"
#include "dndc_main.h"
#include "Help_AutoFert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int FertAlter,FloodAlter, TillAlter, IrriAlter, RicePlantAlter;
/////////////////////////////////////////////////////////////////////////////
// RegionYear dialog


RegionYear::RegionYear(CWnd* pParent /*=NULL*/)
	: CDialog(RegionYear::IDD, pParent)
{
	//{{AFX_DATA_INIT(RegionYear)
	m_LitterBackField = 1.0f;
	m_AnimalManure = 1.0f;
	m_FertilizerRate = 1.0f;
	m_IrriIndex = 0.0f;
	m_AtmoCO2 = 370.0f;
	m_AirTemp = 0.0f;
	m_Tillage = 0;
	m_RegionYear = 0;
	m_YieldIncrease = 0.0f;
	m_ShallowFlood = FALSE;
	m_UplandRice = FALSE;
	m_FertSO4 = FALSE;
	m_SlowReleaseDays = 1;
	m_RainChange = 1.0f;
	m_MicroIndex = 0.0f;
	m_WaterDemand = 1.0f;
	m_MaxTemp = 1.0f;
	m_CropCN = 1.0f;
	//}}AFX_DATA_INIT
}


void RegionYear::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RegionYear)
	DDX_Control(pDX, IDC_RicePlanting, m_RicePlantingMethod);
	DDX_Control(pDX, IDC_IrriAlter, m_IrriAlter);
	DDX_Control(pDX, IDC_TillAlter, m_TillAlter);
	DDX_Control(pDX, IDC_FloodAlter, m_FloodAlter);
	DDX_Control(pDX, IDC_AutoFert, m_AutoFert);
	DDX_Control(pDX, IDC_MidseasonDrainage, m_InterDrain);
	DDX_Text(pDX, IDC_LitterBackField, m_LitterBackField);
	DDX_Text(pDX, IDC_Animal_Manure, m_AnimalManure);
	DDX_Text(pDX, IDC_Fertilizer, m_FertilizerRate);
	DDX_Text(pDX, IDC_IrrIndex, m_IrriIndex);
	DDX_Text(pDX, IDC_CO2, m_AtmoCO2);
	DDX_Text(pDX, IDC_Temp, m_AirTemp);
	DDX_Radio(pDX, IDC_RADIO83, m_Tillage);
	DDX_Text(pDX, IDC_RegionYear, m_RegionYear);
	DDX_Text(pDX, IDC_Rainfall, m_YieldIncrease);
	DDX_Check(pDX, IDC_ShallowFlood, m_ShallowFlood);
	DDX_Check(pDX, IDC_UplandRice, m_UplandRice);
	DDX_Check(pDX, IDC_FertSO4, m_FertSO4);
	DDX_Text(pDX, IDC_SlowReleaseDays, m_SlowReleaseDays);
	DDX_Text(pDX, IDC_RainChange, m_RainChange);
	DDX_Text(pDX, IDC_MicroIndex, m_MicroIndex);
	DDX_Text(pDX, IDC_WaterDemand, m_WaterDemand);
	DDX_Text(pDX, IDC_MaxTemp, m_MaxTemp);
	DDX_Text(pDX, IDC_PlantCN, m_CropCN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RegionYear, CDialog)
	//{{AFX_MSG_MAP(RegionYear)
	ON_BN_CLICKED(IDC_DataCopy, OnDataCopy)
	ON_BN_CLICKED(IDC_AF, OnAf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RegionYear message handlers

BOOL RegionYear::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int year, FileFlag, Drainage, jd;	
	
	float jf;

	CString RegYr;
	FILE* regyr;
	RegYr.Format("%s\\Inter\\RegionInputFileFlag", OUTPUT);
	regyr = fopen(RegYr, "r");
	if(regyr==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RegYr);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(regyr, "%d", &FileFlag);
	fclose(regyr);	

	char Fregion[120];
	FILE *region;
	sprintf(Fregion, "%s\\RegionYear", INTER);
	region = fopen(Fregion, "r");
	if(region==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", Fregion);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(region, "%d", &year);
	fclose(region);

	m_RegionYear=year;

	// TODO: Add extra initialization here

	if(FileFlag==0)
	{
		m_LitterBackField = 1.0;
		m_AnimalManure = 1.0;
		m_FertilizerRate = 1.0;
		m_AtmoCO2 = 370.0f;
		m_AirTemp = 0.0f;
		m_YieldIncrease = 1.0f;
		m_Tillage = 0;
		m_InterDrain.SetCurSel(0);
		m_ShallowFlood = 0;
		m_CropCN = 1.0;
		m_AutoFert.SetCurSel(0);
		m_FloodAlter.SetCurSel(0);
		m_TillAlter.SetCurSel(0);
		m_IrriAlter.SetCurSel(0);
		m_RicePlantingMethod.SetCurSel(0);

		int jd, SimuMode;
		float jf;
		char js[30];
		char Fregion[120];
		FILE *region;
		sprintf(Fregion, "%s\\region_input", INTER);
		region = fopen(Fregion, "r");

		fscanf(region, "%d %d %d\n", &jd, &jd, &jd);
		fscanf(region, "%s\n", js);
		fscanf(region, "%s %s\n", js, js);
		fscanf(region, "%s\n", js);//r_DatabaseName);
		fscanf(region, "%s\n", js);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%f %f %f\n", &jf, &jf, &jf);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd); 
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &jd);
		fscanf(region, "%d\n", &SimuMode);
		fscanf(region, "%d\n", &jd);
		fclose(region);

		if(SimuMode==0||SimuMode==1) m_IrriIndex = 1.0;
		else m_IrriIndex = 0.0;

		
	}
	else
	{
		CString RegYr;
		FILE* regyr;
		RegYr.Format("%s\\Inter\\Region_yr%d", OUTPUT, year);
		regyr = fopen(RegYr, "r");
		if(regyr==NULL)
		{
			CString note;
			note.Format("Can not open file %s", RegYr);
			AfxMessageBox(note);
			exit(0);
		}

		fscanf(regyr, "%f %f %f", &m_AtmoCO2, &m_AirTemp, &m_RainChange);
		fscanf(regyr, "%f %f %f", &m_LitterBackField, &m_FertilizerRate, &m_AnimalManure);
		fscanf(regyr, "%d %d %d", &FertAlter, &FloodAlter, &TillAlter);	
		fscanf(regyr, "%f %f %f", &m_YieldIncrease, &m_WaterDemand, &m_MaxTemp);
		fscanf(regyr, "%f %f %f %f %f", &m_CropCN, &m_IrriIndex, &jf, &jf, &jf);
		fscanf(regyr, "%d %d %d %d %d", &IrriAlter, &RicePlantAlter, &jd, &jd, &jd);		
		fclose(regyr);		

		m_IrriAlter.SetCurSel(IrriAlter-1);
		m_AutoFert.SetCurSel(FertAlter-1);
		m_FloodAlter.SetCurSel(FloodAlter);
		m_TillAlter.SetCurSel(TillAlter);
		m_RicePlantingMethod.SetCurSel(RicePlantAlter);
	}	
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RegionYear::OnOK() 
{
	// TODO: Add extra validation here
	int year;

	if(m_LitterBackField>1.0)
	{
		AfxMessageBox("Change in crop residue incorporation must be a fraction");
		return;
	}

	if(m_FertilizerRate>1.0)
	{
		AfxMessageBox("Change in fertilizer rate must be a fraction");
		return;
	}

	if(m_AnimalManure>1.0)
	{
		AfxMessageBox("Change in manure application rate must be a fraction");
		return;
	}

	m_AirTemp=0.0;
	m_YieldIncrease=1.0;
	m_RainChange = 1.0;

	char Fregion[120];
	FILE *region;
	sprintf(Fregion, "%s\\RegionYear", INTER);
	region = fopen(Fregion, "r");
	if(region==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", Fregion);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(region, "%d", &year);
	fclose(region);

	UpdateData(TRUE);
	
	FertAlter = m_AutoFert.GetCurSel()+1;	
	FloodAlter = m_FloodAlter.GetCurSel();
	TillAlter = m_TillAlter.GetCurSel();
	IrriAlter = m_IrriAlter.GetCurSel()+1;
	RicePlantAlter = m_RicePlantingMethod.GetCurSel();

	sprintf(Fregion, "%s\\region_yr%d", INTER, year);
	region = fopen(Fregion, "w");	
	fprintf(region, "%f %f %f\n", m_AtmoCO2, m_AirTemp, m_RainChange);
	fprintf(region, "%f %f %f\n", m_LitterBackField, m_FertilizerRate, m_AnimalManure);
	fprintf(region, "%d %d %d\n", FertAlter, FloodAlter, TillAlter);	
	fprintf(region, "%f %f %f\n", m_YieldIncrease, m_WaterDemand, m_MaxTemp);
	fprintf(region, "%f %f %f %f %f\n", m_CropCN, m_IrriIndex, 0.0, 0.0, 0.0);
	fprintf(region, "%d %d %d %d %d\n", IrriAlter, RicePlantAlter, 0, 0, 0);
	
	fclose(region);

	CDialog::OnOK();
}

void RegionYear::OnDataCopy() 
{
	// TODO: Add your control notification handler code here
	float junkf, jf;
	int year, Drainage, jd;

	char FF[120];
	FILE *region;
	sprintf(FF, "%s\\RegionYear", INTER);
	region = fopen(FF, "r");
	if(region==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", FF);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(region, "%d", &year);
	fclose(region);

	CString Fregion;
	
	Fregion.Format("%s\\region_yr%d", INTER, year-1);
	region = fopen(Fregion, "r");
	if(region==NULL)
	{
		CString note;
		note.Format("cannot open file %s", Fregion);
		AfxMessageBox(note);
		exit(0);
	}
		fscanf(region, "%f %f %f", &m_AtmoCO2, &m_AirTemp, &m_RainChange);
		fscanf(region, "%f %f %f", &m_LitterBackField, &m_FertilizerRate, &m_AnimalManure);
		fscanf(region, "%d %d %d", &FertAlter, &FloodAlter, &TillAlter);	
		fscanf(region, "%f %f %f", &m_YieldIncrease, &m_WaterDemand, &m_MaxTemp);
		fscanf(region, "%f %f %f %f %f", &m_CropCN, &m_IrriIndex, &jf, &jf, &jf);
		fscanf(region, "%d %d %d %d %d", &IrriAlter, &RicePlantAlter, &jd, &jd, &jd);
				
		fclose(region);

		m_AutoFert.SetCurSel(FertAlter-1);
		m_FloodAlter.SetCurSel(FloodAlter);
		m_TillAlter.SetCurSel(TillAlter);
		m_IrriAlter.SetCurSel(IrriAlter-1);
		m_RicePlantingMethod.SetCurSel(RicePlantAlter);
	
	UpdateData(FALSE);
}

void RegionYear::OnAf() 
{
	// TODO: Add your control notification handler code here
	Help_AutoFert ww;
	ww.DoModal();
	
}
