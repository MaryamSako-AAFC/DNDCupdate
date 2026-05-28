// SitePage2.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "stdio.h"
#include <math.h>
#include "SitePara.h"
#include "SitePage2.h"
#include "dndc_main.h"
#include "SCSDlg.h"
#include "DNDC_SoilProfile.h"
#include "dndc_tool.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CropArray			Crop;
extern Site_BaseInformation	IData ;
extern StringArray			ClimateFilename;
extern CropofEachYear CYr[2];
extern char *soiltexture[];
extern char *soillanduse[];
int ifwork=0;
float soca[6]={0.0,0.2,0.2,0.08,0.05,0.01};
float socb[6]={10.0,2.0,2.0,1.4,4.0,0.9};
float HumCN=10.0;

/////////////////////////////////////////////////////////////////////////////
// SitePage2 property page

IMPLEMENT_DYNCREATE(SitePage2, CPropertyPage)

SitePage2::SitePage2() : CPropertyPage(SitePage2::IDD)
{
	//{{AFX_DATA_INIT(SitePage2)
	m_Soilbypass = FALSE;
	m_SoilClay = 0.0f;
	m_SoilDensity = 0.0f;
	m_WaterPoolBD=2.0f;
	m_SoilHumads = 0.0f;
	m_SoilHumus = 0.0f;
	m_SoilLitter = 0.0f;
	m_SoilMoisture = 0.4f;
	m_SoilNH4 = 0.0f;
	m_SoilNO3 = 0.0f;
	m_SoilOrganic = 0.01f;
	m_SoilpH = 0.0f;
	m_SoilTemp = 0.0f;
	m_SoilFieldCapacity = 0.0f;
	m_SoilWiltingPoint = 0.0f;
	m_SoilRetardation = -1;
	m_MicrobioIndex = 0.0f;
	m_WaterObstructLayer = 2.50f;
	m_slope = 0.0f;
	m_TopM = 0.2f;
	m_DecreaseRate = 0.0f;
	m_SOMdefine = FALSE;
	m_SOMprofile = FALSE;
	m_BypassYes = FALSE;
	m_VLLcn = 0.0f;
	m_VLLitter = 0.0f;
	m_HumadCN = 0.0f;
	m_HumusCN = 0.0f;
	m_LLcn = 0.0f;
	m_LLitter = 0.0f;
	m_RLcn = 0.0f;
	m_BulkCN = 0.0f;
	m_SoilSks = 0.0f;
	m_BypassFlowRate = 0.0f;
	m_UseION = FALSE;
	m_HighestWT = 1.0f;
	m_WaterLoggingYes = FALSE;
	m_WaterLoggingNo = TRUE;
	m_SoilPorosity = 0.0f;
	m_PassiveC = 0.0f;
	m_PassiveCCN = 500.0f;
	m_DClitter = 1.0f;
	m_DChumads = 1.0f;
	m_DChumus = 1.0f;
	m_DCfactor = FALSE;
	m_ProfileType = 0;//This changes the Profile selection between heterogenous and homogeneous
	m_ProfileFileName="none";
	m_LateralInflux = 1.0f;
	m_salinity = 0.0f;
	m_SCSuse = FALSE;
	//}}AFX_DATA_INIT

}

SitePage2::~SitePage2()
{
	m_MicrobioIndex = 1.0;
	m_WaterObstructLayer = 2.50;//m
	m_slope = 0.0;
}

void SitePage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage2)
	DDX_Control(pDX, IDC_Landuse, m_Soillanduse);
	DDX_Control(pDX, IDC_Soiltexture, m_Soiltexture);
	DDX_Check(pDX, IDC_Soilbypass2, m_Soilbypass);
	DDX_Text(pDX, IDC_SoilClay, m_SoilClay);
	DDX_Text(pDX, IDC_WaterPoolBD, m_WaterPoolBD);
	DDX_Text(pDX, IDC_SoilDensity, m_SoilDensity);
	DDX_Text(pDX, IDC_SoilHumads, m_SoilHumads);
	DDX_Text(pDX, IDC_SoilHumus, m_SoilHumus);
	DDX_Text(pDX, IDC_SoilLitter, m_SoilLitter);
	DDX_Text(pDX, IDC_SoilMoisture, m_SoilMoisture);
	DDX_Text(pDX, IDC_SoilNH4, m_SoilNH4);
	DDX_Text(pDX, IDC_SoilNO3, m_SoilNO3);
	DDX_Text(pDX, IDC_SoilOrganic, m_SoilOrganic);
	DDX_Text(pDX, IDC_SoilpH, m_SoilpH);
	DDX_Text(pDX, IDC_SoilTemp, m_SoilTemp);
	DDX_Text(pDX, IDC_FieldCapacity, m_SoilFieldCapacity);
	DDX_Text(pDX, IDC_SoilWiltingPoint, m_SoilWiltingPoint);
	DDX_Radio(pDX, IDC_SoilRetardation, m_SoilRetardation);
	DDX_Text(pDX, IDC_SoiMicrobioIndex, m_MicrobioIndex);
	DDX_Text(pDX, IDC_WaterObstructLayer, m_WaterObstructLayer);
	DDX_Text(pDX, IDC_IrriWaterpH, m_slope);
	DDX_Text(pDX, IDC_TopM, m_TopM);
	DDX_Text(pDX, IDC_DecreaseRate, m_DecreaseRate);
	DDX_Check(pDX, IDC_SOMdefine, m_SOMdefine);
	DDX_Check(pDX, IDC_SOMprofile, m_SOMprofile);
	DDX_Check(pDX, IDC_Soilbypass1, m_BypassYes);
	DDX_Text(pDX, IDC_VLLcn, m_VLLcn);
	DDX_Text(pDX, IDC_VLLitter, m_VLLitter);
	DDX_Text(pDX, IDC_HumadCN, m_HumadCN);
	DDX_Text(pDX, IDC_HumusCN, m_HumusCN);
	DDX_Text(pDX, IDC_LLcn, m_LLcn);
	DDX_Text(pDX, IDC_LLitter, m_LLitter);
	DDX_Text(pDX, IDC_RLcn, m_RLcn);
	DDX_Text(pDX, IDC_BulkCN, m_BulkCN);
	DDX_Text(pDX, IDC_SoilSks, m_SoilSks);
	DDX_Text(pDX, IDC_BypassFlowRate, m_BypassFlowRate);
	DDX_Check(pDX, IDC_UseION, m_UseION);
	DDX_Text(pDX, IDC_HighestWT, m_HighestWT);
	DDX_Check(pDX, IDC_WaterLoggingYes, m_WaterLoggingYes);
	DDX_Check(pDX, IDC_WaterLoggingNo, m_WaterLoggingNo);
	DDX_Text(pDX, IDC_SoilPorosity, m_SoilPorosity);
	DDX_Text(pDX, IDC_PassiveC, m_PassiveC);
	DDX_Text(pDX, IDC_PassiveCCN, m_PassiveCCN);
	DDX_Text(pDX, IDC_DClitter, m_DClitter);
	DDX_Text(pDX, IDC_DChumads, m_DChumads);
	DDX_Text(pDX, IDC_DChumus, m_DChumus);
	DDX_Check(pDX, IDC_DCfactor, m_DCfactor);
	DDX_Radio(pDX, IDC_ProfileType, m_ProfileType);
	DDX_Text(pDX, IDC_LateralInflux, m_LateralInflux);
	DDX_Text(pDX, IDC_salinity, m_salinity);
	DDX_Check(pDX, IDC_SCSuse, m_SCSuse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage2, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage2)
	ON_BN_CLICKED(IDC_SoilRecover, OnSoilRecover)
	ON_EN_KILLFOCUS(IDC_SoilDensity, OnKillfocusSoilDensity)
	ON_EN_KILLFOCUS(IDC_SoilLitter, OnKillfocusSoilLitter)
	ON_EN_KILLFOCUS(IDC_SoilHumads, OnKillfocusSoilHumads)
	ON_EN_KILLFOCUS(IDC_SoilHumus, OnKillfocusSoilHumus)
	ON_EN_KILLFOCUS(IDC_SoilOrganic, OnKillfocusSoilOrganic)
	ON_BN_CLICKED(IDC_AcceptSoil, OnAcceptSoil)
	ON_EN_KILLFOCUS(IDC_SoilpH, OnKillfocusSoilpH)
	ON_EN_KILLFOCUS(IDC_SoilClay, OnKillfocusSoilClay)
	ON_EN_KILLFOCUS(IDC_FieldCapacity, OnKillfocusFieldCapacity)
	ON_EN_KILLFOCUS(IDC_SoilWiltingPoint, OnKillfocusSoilWiltingPoint)
	ON_BN_CLICKED(IDC_SoilRetardation, OnSoilRetardation)
	ON_BN_CLICKED(IDC_SoilRetardation1, OnSoilRetardation1)
	ON_BN_CLICKED(IDC_SOMdefine, OnSOMdefine)
	ON_BN_CLICKED(IDC_SOMprofile, OnSOMprofile)
	ON_BN_CLICKED(IDC_Soilbypass1, OnSoilbypassYes)
	ON_BN_CLICKED(IDC_Soilbypass2, OnSoilbypass)
	ON_EN_KILLFOCUS(IDC_BulkCN, OnKillfocusBulkCN)
	ON_BN_CLICKED(IDC_WaterLoggingYes, OnWaterLoggingYes)
	ON_BN_CLICKED(IDC_WaterLoggingNo, OnWaterLoggingNo)
	ON_BN_CLICKED(IDC_DCfactor, OnDCfactor)
	ON_BN_CLICKED(IDC_SCSCurve, OnSCSCurve)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_ProfileType, OnProfileType)
	ON_CBN_SELCHANGE(IDC_Soiltexture, OnSelchangeSoiltexture)
	ON_BN_CLICKED(IDC_SCSuse, OnSCSuse)
	ON_EN_KILLFOCUS(IDC_VLLitter, OnKillfocusVLLitter)
	ON_EN_KILLFOCUS(IDC_LLitter, OnKillfocusLLitter)
	ON_EN_KILLFOCUS(IDC_PassiveC, OnKillfocusPassiveC)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage2 message handlers

BOOL SitePage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_VLLcn = 5.;
	m_LLcn = 25.;
	m_RLcn = 100.;
    m_HumadCN = HumCN;
	m_HumusCN = HumCN;
	m_VLLitter = 0.0;
	m_LLitter = 0.0;
	m_BypassYes = FALSE;
	m_Soilbypass=TRUE;
	m_PassiveCCN = 500.0;
	m_SoilOrganic = 0.01;
	m_SCSuse = IData.SCSuse;

	if(IData.Sks<0.008) 
		IData.Sks = 0.008; //default 0.015 was 0.008

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_SoilRecover);

	if(m_SCSuse==1)
	{		
		Edt->EnableWindow(TRUE);
	}
	else
	{
		Edt->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL SitePage2::OnSetActive() 
{
	
	ifwork=1;
	//if (IData.Soil_Texture-1>=0 && IData.Soil_Texture-1<14) {
	m_Soiltexture.SetCurSel(IData.Soil_Texture-1);
	ReadSoilFeature("UnDefault");//read soil parameters from database
		//if (m_SoilClay==0 && IData.Soil_Clay !=0) m_SoilClay=IData.Soil_Clay;
		//else if (m_SoilClay!=0) IData.Soil_Clay = m_SoilClay;
		//m_SoilClay = IData.Soil_Clay;
	//}
	//if (IData.Soil_landuse-1 >=0 && IData.Soil_landuse-1 <5) 
	m_Soillanduse.SetCurSel(IData.Soil_landuse-1);
	
	//m_Soilbypass=(IData.Soil_BypassFlow==0)?true:false;
	
	if(m_Soilbypass==TRUE) m_BypassYes=FALSE;
	else m_BypassYes=TRUE;

	m_SoilSks= IData.Sks;
	m_SoilFieldCapacity= IData.Fldcap;
	m_SoilWiltingPoint = IData.Wiltpt;
	m_SoilRetardation  = IData.SoilRetardation;
	m_SoilDensity  = IData.Soil_Density;
	IData.WaterPoolBD=2.0;
	m_WaterPoolBD = IData.WaterPoolBD;
	m_ProfileType=IData.ProfileType;
	m_ProfileFileName=IData.ProfileFileName;
	m_SoilpH       = IData.Soil_pH;
	//m_IrriWaterpH       = IData.Flood_pH;
	m_SoilClay     = IData.Soil_Clay;
	m_SoilOrganic  = IData.Soil_OCatSurface;
	m_SoilLitter   = IData.Soil_Litter;
	m_SoilHumads   = IData.Soil_humads;
	m_SoilHumus    = IData.Soil_humus;
	m_PassiveC = IData.PassiveC;
	m_SoilNO3      = IData.Soil_NO3;
	m_SoilNH4	   = IData.Soil_NH4;
	m_SoilMoisture = IData.Soil_moiture;
	m_SoilTemp     = IData.Soil_T; 
	m_MicrobioIndex = IData.Soil_MicrobioIndex; 
	m_SoilPorosity = IData.Soil_Porosity;
		
	//m_WaterTable = IData.HighWT;
	m_WaterObstructLayer = IData.Soil_WaterObstructLayer;
	m_TopM	 = IData.SOCa;
	m_DecreaseRate	 = IData.SOCb;
	m_slope = IData.slope;
	m_BypassFlowRate = IData.Soil_BypassFlow;
	m_LateralInflux = IData.LateralInflux;
	m_salinity = IData.Soil_Quality;
	
	if(IData.HighestWT>1.0) m_HighestWT = 1.0;
	else m_HighestWT = IData.HighestWT;
	if(IData.HighestWT==1.0)
	{
		m_WaterObstructLayer=2.5;
		IData.Soil_WaterObstructLayer=2.5;
	}
		else
		{
		m_WaterObstructLayer=2.0;
		IData.Soil_WaterObstructLayer=2.0;
		}
	
	if(IData.Soil_BypassFlow>0.0) 
	{
		m_BypassYes=TRUE;
		m_Soilbypass=FALSE;
	}
	else 
	{
		m_BypassYes=FALSE;
		m_Soilbypass=TRUE;
	}

	if(m_BypassYes==FALSE) m_BypassFlowRate = 0.0;
	if(IData.UseION==1) m_UseION = TRUE;

	m_DClitter = IData.DClitter;
	m_DChumads = IData.DChumads;
	m_DChumus = IData.DChumus;

	m_HumadCN = IData.HumadCN;
	m_HumusCN = IData.HumusCN;

	m_SCSuse = IData.SCSuse;

	/*if(IData.Fldcap!=0)
		m_SoilFieldCapacity = IData.Fldcap;
	if(IData.Wiltpt!=0)
		m_SoilWiltingPoint = IData.Wiltpt;*/

	//m_Default      = TRUE;

	/*m_VLLcn = 5.;
	m_LLcn = 25.;
	m_RLcn = 100.;
    m_HumadCN = 10.0;
	m_HumusCN = 10.0;
	m_VLLitter = 0.0;
	m_LLitter = 0.0;*/

	//float TotN = m_VLLitter/m_VLLcn + m_LLitter/m_LLcn + m_SoilLitter/m_RLcn* + m_SoilHumads/m_HumadCN + m_SoilHumus/m_HumusCN + m_PassiveC/m_PassiveCCN;
	m_BulkCN = 1.0 / (m_VLLitter/m_VLLcn + m_LLitter/m_LLcn + m_SoilLitter/m_RLcn + m_SoilHumads/m_HumadCN + m_SoilHumus/m_HumusCN + m_PassiveC/m_PassiveCCN);

	OldVLLcn=m_VLLcn;
	OldVLLitter=m_VLLitter;
	OldLLcn=m_LLcn;
	OldLLitter=m_LLitter;
	OldRLcn=m_RLcn;
	OldSoilLitter=m_SoilLitter;
	OldHumadCN=m_HumadCN;
	OldSoilHumads=m_SoilHumads;
	OldHumusCN=m_HumusCN;
	OldSoilHumus=m_SoilHumus;

	ifwork=0;

	CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_SoilLitter);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SoilHumads);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SoilHumus);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_VLLitter);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LLitter);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_VLLcn);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LLcn);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RLcn);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_HumadCN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_HumusCN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_TopM);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DecreaseRate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_BulkCN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_PassiveCCN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_PassiveC);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DClitter);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DChumads);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DChumus);
		Edt->EnableWindow(FALSE);

/*		if(m_Soilbypass==TRUE)
		{
			Edt=(CEdit *)GetDlgItem(IDC_BypassFlowRate);
			Edt->EnableWindow(FALSE);
		}
*/
		if(m_HighestWT<1.00) 
		{
			m_WaterLoggingYes = TRUE;
			m_WaterLoggingNo = FALSE;
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			//Edt->EnableWindow(TRUE);
		}
		else
		{
			m_WaterLoggingYes = FALSE;
			m_WaterLoggingNo = TRUE;
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			//Edt->EnableWindow(FALSE);
		}

		UpdateData(FALSE);
		
		CString SPP;
	FILE* spp;
	SPP.Format("%s\\Inter\\SOCpartition.txt", OUTPUT);
	spp=fopen(SPP, "w");
	fprintf(spp, "%d\n", 1);
	fprintf(spp, "%f %f %f %f %f\n", m_VLLcn, m_LLcn, m_RLcn, m_HumadCN, m_HumusCN);
	fclose(spp);
	return CPropertyPage::OnSetActive();
}


// Read data from control into IData class
void SitePage2::GetSoilParas()
{
	//UpdateData(TRUE);

	IData.Soil_Texture = m_Soiltexture.GetCurSel()+1;
	IData.Soil_landuse = m_Soillanduse.GetCurSel()+1;
	/*IData.Soil_BypassFlow=1;//visible
	if (m_Soilbypass==TRUE) 
	{
		IData.Soil_BypassFlow=0;//not visible
		m_BypassYes=FALSE;
	}
	else
	{
		IData.Soil_BypassFlow=1;//not visible
		m_BypassYes=TRUE;
	}*/

	IData.Soil_BypassFlow = m_BypassFlowRate;

	IData.Sks = m_SoilSks;
	IData.Fldcap = m_SoilFieldCapacity;
	IData.Wiltpt = m_SoilWiltingPoint;
	IData.SoilRetardation = m_SoilRetardation;
	IData.LateralInflux = m_LateralInflux;

	IData.Soil_Litter=m_SoilLitter;
	IData.Soil_humads=m_SoilHumads;
	IData.Soil_humus =m_SoilHumus;
	IData.PassiveC = m_PassiveC;
	IData.Soil_Density=m_SoilDensity;
	m_WaterPoolBD=2.0;
	IData.WaterPoolBD=m_WaterPoolBD;
	IData.ProfileType=m_ProfileType;
	IData.ProfileFileName=m_ProfileFileName;
	IData.Soil_pH=m_SoilpH;
	//IData.Flood_pH=m_IrriWaterpH;
	IData.Soil_Clay  =m_SoilClay;
	IData.Soil_OCatSurface=m_SoilOrganic;
	IData.Soil_NO3   =m_SoilNO3;
	IData.Soil_NH4   =m_SoilNH4;
	IData.Soil_moiture = m_SoilMoisture;
	IData.Soil_T     =m_SoilTemp;
	IData.Soil_MicrobioIndex = m_MicrobioIndex;
	
	IData.Soil_Porosity = m_SoilPorosity;
	//IData.HighWT = m_WaterTable;
	IData.HighestWT = m_HighestWT;
	IData.Soil_WaterObstructLayer = m_WaterObstructLayer;
	IData.slope = m_slope;

	IData.DClitter = m_DClitter;
	IData.DChumads = m_DChumads;
	IData.DChumus = m_DChumus;

	IData.HumadCN = m_HumadCN;
	IData.HumusCN = m_HumusCN;

	IData.SCSuse = m_SCSuse;
	IData.Soil_Quality = m_salinity;
	

}

void SitePage2::OnSoilRecover() 
{
	UpdateData(TRUE);

	if(m_SCSuse==1)
	{
		CSCSDlg SCSdlg;
		SCSdlg.DoModal();
	}
	else
	{
	}
}

int SitePage2::EditParameter()
{
	int i;
	i=m_Soiltexture.GetCurSel();
	if (i<0 || i>11) return 0;
	i=m_Soillanduse.GetCurSel();
	if (i<0 || i>3) return 0;
/*	if (m_SoilLitter<0 || m_SoilLitter>1) return 0;
	if (m_SoilHumads<0 || m_SoilHumads>1) return 0;
	if (m_SoilHumus <0 || m_SoilHumus >1) return 0;
	if (m_SoilDensity<=0.000001) return 0;
	if (m_SoilpH<0 || m_SoilpH>14) return 0;
	if (m_SoilClay <=0 ) return 0;
	if (m_SoilOrganic <=0) return 0;
	if (m_MicrobioIndex <=0) return 0;
	IData.Soil_NO3   =m_SoilNO3;
	IData.Soil_NH4   =m_SoilNH4;
	IData.Soil_moiture=m_SoilMoisture;
	IData.Soil_T     =m_SoilTemp;
*/
	GetSoilParas();	//get inputed values from controls
	if (SetSoilH()==-1) return -1;//scientific calculation
	ReSetCcomponent();//get new litter,humads,humus,NO3 and NH4 values
	//ChangeOthers();	//recover values inputed by user
	OnSetActive();	//send values into controls

	return 1;
}

/*
void SitePage2::OnSelchangeLanduse() 
{
	if (ifwork==0) 
	{
		ifwork=1;
		//UpdateData(TRUE);//FALSE);
		
		GetSoilParas();	//get inputed values from controls
		IData.Soil_landuse=m_Soillanduse.GetCurSel()+1;

		ifwork=0;
	}
	m_MicrobioIndex = 1.0;
	m_slope = 0.0;

	if(IData.Soil_landuse==2)
		m_WaterObstructLayer = 0.30;//m
	else
		m_WaterObstructLayer = 9.99;//m
	
	UpdateData(FALSE);

	OnKillfocusSoilOrganic();
}
*/



void SitePage2::OnKillfocusSoilDensity() 
{
/*	if (ifwork==0) {
		ifwork=1;
		UpdateData(TRUE);

		
		if (m_Default==TRUE) EditParameter();

		if (m_Default==TRUE)
		{
			if (IfForest())
			{
				//Dbm = (1 - Fo) * Dbo * SD / (Dbo - SD * Fo);
				float Fo,Dbo;
				Fo  = (float)(2.0 * m_SoilOrganic);
				Dbo = (float).14;
				IData.Soil_Density = (1 - Fo) * Dbo * m_SoilDensity / (Dbo - m_SoilDensity * Fo);
			}
		}

		if (fabs(m_SoilDensity-IData.Soil_Density) <0.0000001) {ifwork=0;return;}

		ifwork=0;
	}
*/
}

void SitePage2::OnKillfocusSoilClay() 
{
	/*if (ifwork==0) {
        ifwork=1;
		UpdateData(TRUE);

		if (m_Default==FALSE) return;

		// Set initial soil moisture--->No useful?
		//m_SoilMoisture = float(0.75 * m_SoilClay + 0.2); //!!!
		m_SoilMoisture = m_SoilFieldCapacity;

		UpdateData(FALSE);

		if (m_Default==TRUE) 
		{
			if (IfForest())
				SetSoilDensity();
		}

			// Set Soil organic C partition and other related parameters
        if (EditParameter()==1) {}

		if (fabs(m_SoilClay-IData.Soil_Clay) <0.0000001) {ifwork=0;return;}
		if (fabs(m_SoilMoisture-IData.Soil_moiture) <0.0000001) {ifwork=0;return;}
            // Set Soil organic C partition and other related parameters
        //if (EditParameter()==1) {}

		ifwork=0;
	}*/
}

int SitePage2::SetSoilDensity()
{
	//BD = 100/(x/K1) + (100-x)/K2; based on Stewart et al., 1970 (J. Soil Sci. 21:248-255.
	//x - OM % by weight; K1 - OM bulk density (g/cm3); K2 - bulk density of mineral matter (g/cm3)

	//Top soil bulk density is calculate as:
	if (m_SoilClay<=0) return -1;
	if (m_SoilOrganic<=0) return -1;
	
	float x,K1,K2,BD;
    x  = m_SoilOrganic / 0.58 * 100.0;// kg SOC/kg soil -> SOM %
    K1 = 0.14;
    K2 = 1.6;	
    BD  = (K2 * K1 / (x/100.0 * K2 + (1.0 - x/100.0) * K1));// developed by C. Li
	//BD = 1.55 - 0.06 * x;//OK for only mineral soils, from Hudson, J. Soil and Water Conservation 49(2) 189-194, 1994
	//BD = 100.0/(x/K1) + (100.0 - x) / K2;//wrong

	m_SoilDensity = BD;

	UpdateData(FALSE);
	return 0;
}

void SitePage2::OnAcceptSoil() 
{
	UpdateData(TRUE);

/*	SocProfile(IData.Soil_landuse, m_SoilOrganic, IData.latitude, &IData.Soil_Litter, &IData.Soil_humads, &IData.Soil_humus, &IData.PassiveC);

	m_SoilLitter = IData.Soil_Litter;
	m_SoilHumads = IData.Soil_humads;
	m_SoilHumus = IData.Soil_humus;
	m_PassiveC = IData.PassiveC;

	UpdateData(FALSE);*/

	if(m_SoilClay==0.0) 
	{
		MessageBox("No SoilClay data! Please input it","Data missing",NULL);
		return;
	}
	
	if (m_SoilDensity==0) {
		MessageBox("No Soil Density data! Please input it","Data missing",NULL);
		return;
	}
	if (m_SoilHumads==0) {
		MessageBox("No Soil Humads data! Please input it","Data missing",NULL);
		return;
	}
	if (m_SoilHumus==0) {
		MessageBox("No Soil Humus data! Please input it","Data missing",NULL);
		return;
	}
	/*if (m_SoilLitter==0) {
		MessageBox("No Soil Litter data! Please input it","Data missing",NULL);
		return;
	}
	if (m_SoilMoisture==0) {
		MessageBox("No Soil Moisture data! Please input it","Data missing",NULL);
		return;
	}
	if (m_SoilNH4==0) {
		MessageBox("No Soil NH4 data! Please input it","Data missing",NULL);
		return;
	}
	if (m_SoilNO3==0) {
		MessageBox("No Soil NO3 data! Please input it","Data missing",NULL);
		return;
	}*/
	if (m_SoilOrganic==0) {
		MessageBox("No Soil Organic data! Please input it","Data missing",NULL);
		return;
	}
	if (m_SoilpH==0) {
		MessageBox("No Soil pH data! Please input it","Data missing",NULL);
		return;
	}

	if (m_HighestWT>1.0||m_HighestWT<0.0)
	{
		AfxMessageBox("Drainage efficiency must be between 0 and 1");
		return;
	}

	if (m_SoilSks<0.008) m_SoilSks=0.008;//default 0.015 was 0.008

	/*if (m_MicrobioIndex==0) {
		MessageBox("Please input microbial activity index. The default is 1.","Data missing",NULL);
		return;
	}*/
	
	if (m_WaterObstructLayer==-1) {
		MessageBox("No water retention layer depth! Please input it","Data missing",NULL);
		return;
	}

	if (IData.Soil_landuse-1 <0 || IData.Soil_landuse-1 >6) {
		MessageBox("Please input Land-use","Data missing",NULL);
		return;
	}
	if (IData.Soil_Texture-1<0 || IData.Soil_Texture-1>13) {
		MessageBox("Please input Soil Texture","Data missing",NULL);
		return;
	}

	if(m_LateralInflux<0.0) {
		MessageBox("Please set Lateral influx index as a number > 0");
		return;
	}

	CString Fiwp;
	FILE *fiw;
	Fiwp.Format("%s\\inputs\\WaterPH", OUTPUT);

	float IrriWaterpH = 7.0;
	
	fiw = fopen(Fiwp, "w");
    if ( fiw == NULL )
	{
		CString err;
		err.Format("can not create file %s", Fiwp);
		AfxMessageBox(err);
		exit(0);
	}
    fprintf(fiw, "%f", IrriWaterpH);
	fclose(fiw);

	ifwork=1;

	IData.SOCa = m_TopM;
	IData.SOCb = m_DecreaseRate;

	IData.Soil_Litter = m_SoilLitter;
    IData.Soil_humads=m_SoilHumads;
    IData.Soil_humus=m_SoilHumus;
	IData.PassiveC=m_PassiveC;

	IData.Fldcap = m_SoilFieldCapacity;
	
	IData.Wiltpt = m_SoilWiltingPoint;
	IData.Sks = m_SoilSks;
	IData.UseION = m_UseION;
	IData.Soil_Porosity = m_SoilPorosity;
	
	IData.DClitter = m_DClitter;
	IData.DChumads = m_DChumads;
	IData.DChumus = m_DChumus;

	IData.HumadCN = m_HumadCN;
	IData.HumusCN = m_HumusCN;
	m_WaterPoolBD=2.0;
	IData.WaterPoolBD = m_WaterPoolBD;
	IData.ProfileType=m_ProfileType;
	IData.ProfileFileName=m_ProfileFileName;

	IData.LateralInflux = m_LateralInflux;

	IData.SCSuse = m_SCSuse;
	
	
	UpdateData(FALSE);
	
	IData.Soil_Texture=m_Soiltexture.GetCurSel()+1;
	//ReadSoilFeature("UnDefault");//read soil parameters from database
	GetSoilParas();	//get inputed values from controls
	//if (m_SoilClay>0) IData.Soil_Clay = m_SoilClay;
	SetSoilH();		//scientific calculation
	ReSetCcomponent();
	ChangeOthers();	//recover values inputed by user
	OnSetActive();	//send values into controls
	ifwork=0;
	
}

void SitePage2::OnKillfocusSoilpH() 
{
	/*if (ifwork==0) {
        ifwork=1;
		UpdateData(TRUE);
		if (fabs(m_SoilpH-IData.Soil_pH) <0.0000001) {ifwork=0;return;}
            // Set Soil organic C partition
        //if (EditParameter()==1) {}
		ifwork=0;
	}*/	
}

/*
void SitePage2::OnKillfocusSoilNO3() 
{
	UpdateData(TRUE);
}

void SitePage2::OnKillfocusSoilNH4() 
{
	UpdateData(TRUE);
}

void SitePage2::OnKillfocusSoilMoisture() 
{
	UpdateData(TRUE);
}

void SitePage2::OnKillfocusSoilTemp() 
{
	UpdateData(TRUE );
}
*/

void SitePage2::ChangeOthers()
{
 	if (m_SoilClay!=0)     IData.Soil_Clay    = m_SoilClay;
	if (m_SoilHumads!=0)   IData.Soil_humads  = m_SoilHumads;
	if (m_SoilHumus!=0)    IData.Soil_humus   = m_SoilHumus;
	if (m_PassiveC!=0)	   IData.PassiveC = m_PassiveC;
	if (m_SoilLitter!=0)   IData.Soil_Litter  = m_SoilLitter;
	if (m_SoilNH4!=0)	   IData.Soil_NH4     = m_SoilNH4;
	if (m_SoilNO3!=0)	   IData.Soil_NO3     = m_SoilNO3;
	if (m_SoilMoisture!=0) IData.Soil_moiture = m_SoilMoisture;
	if (m_SoilOrganic!=0)  IData.Soil_OCatSurface = m_SoilOrganic;
	if (m_SoilDensity!=0)  IData.Soil_Density = m_SoilDensity;
	if (m_SoilpH!=0)	   IData.Soil_pH	  = m_SoilpH;
	if (m_SoilTemp!=0)	   IData.Soil_T		  = m_SoilTemp;
	if (m_MicrobioIndex!=0)	   IData.Soil_MicrobioIndex = m_MicrobioIndex;
	if (m_SoilPorosity!=0)	   IData.Soil_Porosity = m_SoilPorosity;
	if (m_salinity!=0) IData.Soil_Quality = m_salinity;
	//IData.HighWT = m_WaterTable;
	IData.HighestWT = m_HighestWT;
	if (m_WaterObstructLayer!=-1) IData.Soil_WaterObstructLayer = m_WaterObstructLayer;
	if(IData.HighestWT==1.0)
	{
		m_WaterObstructLayer=2.5;
		IData.Soil_WaterObstructLayer=2.5;
	}
		else
		{
		m_WaterObstructLayer=2.0;
		IData.Soil_WaterObstructLayer=2.0;
		}

	if (m_slope!=0)     IData.slope    = m_slope;
	if (m_SoilFieldCapacity!=0) IData.Fldcap = m_SoilFieldCapacity;
	if (m_SoilWiltingPoint!=0) IData.Wiltpt = m_SoilWiltingPoint;
	if (m_SoilSks!=0) IData.Sks = m_SoilSks;
	if (m_WaterPoolBD!=0) IData.WaterPoolBD = m_WaterPoolBD;
	if (m_ProfileType!=0) IData.ProfileType = m_ProfileType;
	//if (m_ProfileFileName!=0) IData.ProfileFileName = m_ProfileFileName;
	IData.LateralInflux = m_LateralInflux;

	IData.DClitter = m_DClitter;
	IData.DChumads = m_DChumads;
	IData.DChumus = m_DChumus;

	IData.HumadCN = m_HumadCN;
	IData.HumusCN = m_HumusCN;

	IData.SCSuse = m_SCSuse;
}




void SitePage2::OnSoilDefault() 
{
	//UpdateData(TRUE);	
}

void SitePage2::OnKillfocusFieldCapacity() 
{
	//UpdateData(TRUE);	
}

void SitePage2::OnKillfocusSoilWiltingPoint() 
{
	//UpdateData(TRUE);	
}

void SitePage2::OnSoilRetardation() 
{
	//UpdateData(TRUE);	
}

void SitePage2::OnSoilRetardation1() 
{
	//UpdateData(TRUE);
}


/*
void SitePage2::OnSetfocusSoiltexture() 
{
	// TODO: Add your control notification handler code here

}
*/

void SitePage2::OnSOMdefine() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	SocProfile(IData.Soil_landuse, m_SoilOrganic, IData.latitude, &IData.Soil_Litter, &IData.Soil_humads, &IData.Soil_humus, &IData.PassiveC);

	m_SoilLitter = IData.Soil_Litter;
	m_SoilHumads = IData.Soil_humads;
	m_SoilHumus = IData.Soil_humus;
	m_PassiveC = IData.PassiveC;

	UpdateData(FALSE);

	CEdit *Edt;

	if(m_SOMdefine==0)
	{
		Edt=(CEdit *)GetDlgItem(IDC_SoilLitter);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SoilHumads);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SoilHumus);
		Edt->EnableWindow(FALSE); 	
		Edt=(CEdit *)GetDlgItem(IDC_VLLitter);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LLitter);
		Edt->EnableWindow(FALSE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_VLLcn);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LLcn);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RLcn);*/
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_HumadCN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_HumusCN);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_BulkCN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_PassiveC);
		Edt->EnableWindow(FALSE); 
		
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_SoilLitter);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_SoilHumads);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_SoilHumus);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_VLLitter);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LLitter);
		Edt->EnableWindow(TRUE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_VLLcn);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LLcn);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_RLcn);*/
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_HumadCN);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_HumusCN);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_BulkCN);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_PassiveC);
		Edt->EnableWindow(TRUE);
	}


	
}

void SitePage2::OnSOMprofile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEdit *Edt;

	if(m_SOMprofile==0)
	{
		Edt=(CEdit *)GetDlgItem(IDC_TopM);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DecreaseRate);
		Edt->EnableWindow(FALSE);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_TopM);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_DecreaseRate);
		Edt->EnableWindow(TRUE);
	}
	
}


void SitePage2::OnSoilbypassYes() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEdit *Edt;

/*	if(m_BypassYes==TRUE) 
	{
		m_Soilbypass=FALSE;
		Edt=(CEdit *)GetDlgItem(IDC_BypassFlowRate);
		Edt->EnableWindow(TRUE);
		m_BypassFlowRate=0.8;
	}
	else 
	{
		m_Soilbypass=TRUE;
		Edt=(CEdit *)GetDlgItem(IDC_BypassFlowRate);
		Edt->EnableWindow(FALSE);
		m_BypassFlowRate=0.0;
	}
*/
	UpdateData(FALSE);
}

void SitePage2::OnSoilbypass() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEdit *Edt;

/*	if(m_Soilbypass==TRUE) 
	{
		m_BypassYes=FALSE;

		Edt=(CEdit *)GetDlgItem(IDC_BypassFlowRate);
		Edt->EnableWindow(FALSE);
		m_BypassFlowRate=0.0;
	}
	else 
	{
		m_BypassYes=TRUE;
		Edt=(CEdit *)GetDlgItem(IDC_BypassFlowRate);
		Edt->EnableWindow(TRUE);
		m_BypassFlowRate=0.8;
	}
*/
	UpdateData(FALSE);
}



void SitePage2::OnKillfocusBulkCN() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	/*m_VLLcn=OldVLLcn;
	m_VLLitter=OldVLLitter;
	m_LLcn=OldLLcn;
	m_LLitter=OldLLitter;
	m_RLcn=OldRLcn;
	m_SoilLitter=OldSoilLitter;
	m_HumadCN=OldHumadCN;
	m_SoilHumads=OldSoilHumads;
	m_HumusCN=OldHumusCN;
	m_SoilHumus=OldSoilHumus;*/

	IData.Soil_Texture = m_Soiltexture.GetCurSel()+1;

	if(IData.Soil_Texture==13||IData.Soil_Texture==14)
	{
		if(m_BulkCN<HumCN) 
		{
			m_HumadCN = m_BulkCN;
			m_HumusCN = m_BulkCN;
			m_SoilLitter = 0.0;
			m_PassiveC = 0.0;
		}
		else
		{
			m_HumadCN = HumCN;
			m_HumusCN = HumCN;
			m_PassiveC = 0.0;//(m_BulkCN - HumCN) / 500.0;
			m_SoilLitter = 0.4;//0.0;
		}

		m_SoilHumads = 0.2;//0.001;
		m_SoilHumus = 1.0 - m_PassiveC - m_SoilHumads;

	}
	else
	{

		if(m_BulkCN<HumCN) 
		{
			m_HumadCN = m_BulkCN;
			m_HumusCN = m_BulkCN;
			m_SoilLitter = 0.0;
		}
		else
		{
			m_HumadCN = HumCN;
			m_HumusCN = HumCN;
			m_SoilLitter = (m_BulkCN - HumCN) / 90.0;
		}

		if(IData.Soil_landuse==3) //paddy soil
			m_SoilHumads = 0.8;
		else
			m_SoilHumads = 0.01;
		
		m_SoilHumus = 1.0 - m_SoilLitter - m_SoilHumads;
		m_PassiveC = 0.0;
	}

	//
	
	m_VLLitter = 0.0;
	m_LLitter = 0.0;
	
	UpdateData(FALSE);

	CString SPP;
	FILE* spp;
	SPP.Format("%s\\Inter\\SOCpartition.txt", OUTPUT);
	spp=fopen(SPP, "w");
	fprintf(spp, "%d\n", 1);
	fprintf(spp, "%f %f %f %f %f\n", m_VLLcn, m_LLcn, m_RLcn, m_HumadCN, m_HumusCN);
	fclose(spp);
}

/*void SitePage2::OnSoilLogging() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_SoilLogging==FALSE) m_SoilLogging=TRUE;
	else m_SoilLogging=FALSE;

	CEdit *Edt;
	if(m_SoilLogging==FALSE)
		{
			m_HighestWT = 9.99;
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			Edt->EnableWindow(FALSE);
		}
		else
		{
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			Edt->EnableWindow(TRUE);
		}

		UpdateData(FALSE);

}*/


void SitePage2::OnWaterLoggingYes() 
{
	// TODO: Add your control notification handler code here
	if(m_WaterLoggingYes==FALSE) 
	{
		m_WaterLoggingYes=TRUE;
		m_WaterLoggingNo=FALSE;
	}
	else 
	{
		m_WaterLoggingYes=FALSE;
		m_WaterLoggingNo=TRUE;
	}

	CEdit *Edt;
	if(m_WaterLoggingYes==FALSE)
		{
			m_HighestWT = 1.0;
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			Edt->EnableWindow(FALSE);
		}
		else
		{
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			Edt->EnableWindow(TRUE);
		}

		UpdateData(FALSE);

	
}

void SitePage2::OnWaterLoggingNo() 
{
	// TODO: Add your control notification handler code here
	if(m_WaterLoggingNo==TRUE) 
	{
		m_WaterLoggingYes=TRUE;
		m_WaterLoggingNo=FALSE;
	}
	else 
	{
		m_WaterLoggingYes=FALSE;
		m_WaterLoggingNo=TRUE;
	}

	CEdit *Edt;
	if(m_WaterLoggingNo==TRUE)
		{
			m_HighestWT = 1.0;
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			Edt->EnableWindow(FALSE);
		}
		else
		{
			Edt=(CEdit *)GetDlgItem(IDC_HighestWT);
			Edt->EnableWindow(TRUE);
		}

		UpdateData(FALSE);

}

void SitePage2::OnDCfactor() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEdit *Edt;

	if(m_DCfactor==0)
	{
		Edt=(CEdit *)GetDlgItem(IDC_DClitter);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DChumads);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DChumus);
		Edt->EnableWindow(FALSE);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_DClitter);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_DChumads);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DChumus);
		Edt->EnableWindow(TRUE);
	}
}

void SitePage2::OnSCSCurve() 
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);

	
//#ifdef HYDRO
	//CSCSDlg SCSdlg;
	//SCSdlg.DoModal();	
//#endif
}

void SitePage2::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	CEdit *Edt;
	
	DNDC_SoilProfile ww;
	if(ww.DoModal()==IDOK)
	{
		int m_SPlayers, m_SPso1, layerID;
		float m_SPthickness, m_SPth1, m_SPd1, m_SPsoc1, m_SPph1, m_SPfc1;
		float m_SPwp1, m_SPpo1, m_SPhy1, m_SPc1;
	
		CString SPF;
		FILE *spf;
		SPF.Format("%s\\Inter\\SoilProfileData.spf", OUTPUT);
		if(IData.ProfileFileName=="")
		{
			spf=fopen(SPF, "r");
		}
		else
		{
		spf=fopen(IData.ProfileFileName, "r");//SPF
		}
		if(spf==NULL) note(0, SPF);

		fscanf(spf, "%f %d", &m_SPthickness, &m_SPlayers);
		fscanf(spf, "%d %f %f %f %d %f %f %f %f %f %f", 
			&layerID, &m_SPth1, &m_SPd1, &m_SPsoc1, &m_SPso1, &m_SPph1, &m_SPfc1, &m_SPwp1, &m_SPpo1, &m_SPhy1, &m_SPc1);
		fclose(spf);

		IData.Soil_Density = m_SPd1;
		IData.Soil_OCatSurface = m_SPsoc1;
		IData.Soil_pH = m_SPph1;
		IData.Fldcap = m_SPfc1;
		IData.Wiltpt = m_SPwp1;
		IData.Soil_Porosity = m_SPpo1;
		IData.Sks = m_SPhy1;
		IData.Soil_Clay = m_SPc1;
		IData.Soil_Texture = m_SPso1;
		IData.LateralInflux = m_LateralInflux;

		m_SoilDensity  = IData.Soil_Density;
		m_WaterPoolBD = IData.WaterPoolBD;
		m_ProfileType = IData.ProfileType;
		m_ProfileFileName=IData.ProfileFileName;
		m_SoilOrganic  = IData.Soil_OCatSurface;
		m_SoilpH       = IData.Soil_pH;
		m_SoilFieldCapacity= IData.Fldcap;
		m_SoilWiltingPoint = IData.Wiltpt;
		m_SoilPorosity = IData.Soil_Porosity;
		m_SoilSks= IData.Sks;
		m_SoilClay     = IData.Soil_Clay;
		m_Soiltexture.SetCurSel(IData.Soil_Texture-1);	
		m_LateralInflux = IData.LateralInflux;

        CString fCap,sDen,sOC,sPH,sWilt,sPor,sClay,sSKS;
		fCap.Format("%f", m_SoilFieldCapacity);
		SetDlgItemText(IDC_FieldCapacity, fCap);
		sDen.Format("%f", m_SoilDensity);
		SetDlgItemText(IDC_SoilDensity, sDen);
		sSKS.Format("%f", m_SoilSks);
		SetDlgItemText(IDC_SoilSks, sSKS);
		sClay.Format("%f", m_SoilClay);
		SetDlgItemText(IDC_SoilClay, sClay);
		sWilt.Format("%f", m_SoilWiltingPoint);
		SetDlgItemText(IDC_SoilWiltingPoint, sWilt);
		sPor.Format("%f", m_SoilPorosity);
		SetDlgItemText(IDC_SoilPorosity, sPor);
		sOC.Format("%f", m_SoilOrganic);
		SetDlgItemText(IDC_SoilOrganic, sOC);
		sPH.Format("%f", m_SoilpH);
		SetDlgItemText(IDC_SoilpH, sPH);
		//Edt->EnableWindow(TRUE);
		//;SetDlgItemText(
		
		/*
		Edt=(CEdit *)GetDlgItem(IDC_SoilClay);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SoilDensity);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SoilOrganic);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SoilpH);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_FieldCapacity);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_SoilWiltingPoint);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SoilSks);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SoilPorosity);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SOMprofile);
		Edt->EnableWindow(FALSE);
		//Edt=(CEdit *)GetDlgItem(IDC_SoilClay);
		//Edt->EnableWindow(FALSE);
		*/	
		m_ProfileType=1;
		UpdateData(TRUE);

		OnKillfocusSoilOrganic();
		UpdateData(FALSE);

		CString CM;
		FILE *cm;	
		CM.Format("%s\\Inter\\CropModel", OUTPUT);
		cm=fopen(CM, "w");
		if(cm==NULL) note(1, CM);
		else
		{
			fprintf(cm, "%d\n", 1);
			fclose(cm);
		}

	}
}

void SitePage2::OnProfileType() 
{
	// TODO: Add your control notification handler code here
	CEdit *Edt;
	
	Edt=(CEdit *)GetDlgItem(IDC_SoilClay);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SoilDensity);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SoilOrganic);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SoilpH);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_FieldCapacity);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SoilWiltingPoint);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SoilSks);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SoilPorosity);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SOMprofile);
	Edt->EnableWindow(TRUE);
	//Edt=(CEdit *)GetDlgItem(IDC_SoilClay);
	//Edt->EnableWindow(FALSE);
		
	m_ProfileType=0;
	UpdateData(FALSE);
}


void SitePage2::OnSelchangeSoiltexture() 
{
	// TODO: Add your control notification handler code here

	IData.Soil_Texture=m_Soiltexture.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SoilClay = IData.Soil_Clay;
	m_SoilFieldCapacity= IData.Fldcap;
	m_SoilWiltingPoint = IData.Wiltpt;
	m_SoilSks = IData.Sks;
	m_SoilPorosity = IData.Soil_Porosity;
		
	m_SoilMoisture = (m_SoilFieldCapacity+m_SoilWiltingPoint)*0.5;

	m_SoilNO3 = 0.5;
	m_SoilNH4 = 0.05;
	m_SoilHumads = IData.Soil_humads;
	m_SoilHumus = IData.Soil_humus;
	m_PassiveC = IData.PassiveC;
	m_SoilLitter = IData.Soil_Litter;
	m_BulkCN = 10.0;
	
	UpdateData(FALSE);
}

void SitePage2::OnKillfocusSoilOrganic() 
{
	UpdateData(TRUE);

	if(m_SoilOrganic>0.5)
	{
		AfxMessageBox("SOC content must be < 0.5 kg C/kg soil");
		return;
	}

	IData.Soil_landuse = m_Soillanduse.GetCurSel()+1;
	IData.Soil_Texture = m_Soiltexture.GetCurSel()+1;

	m_TopM = soca[IData.Soil_landuse];
	m_DecreaseRate = socb[IData.Soil_landuse];

	SocProfile(IData.Soil_landuse, m_SoilOrganic, IData.latitude, &IData.Soil_Litter, &IData.Soil_humads, &IData.Soil_humus, &IData.PassiveC);
	
/*	if(IData.Soil_landuse==5)//wetland
	{
		IData.Soil_Litter = 0.4;		
	}
	else
	{
		IData.Soil_Litter = 0.01;		
	}

	IData.Soil_humads = HumadsFraction(m_SoilOrganic, IData.Soil_landuse);

	if(IData.Soil_humads>0.9) IData.Soil_humads=0.9;
	IData.Soil_humus = (1.0 - IData.Soil_Litter - IData.Soil_humads - IData.PassiveC);*/

	m_SoilHumads = IData.Soil_humads;
	m_SoilHumus = IData.Soil_humus;
	m_SoilLitter = IData.Soil_Litter;
	m_PassiveC = IData.PassiveC;

	m_SoilNO3 = SOCtoNO3(m_SoilOrganic, IData.latitude);
	m_SoilNH4 = 0.1 * m_SoilNO3;

	//m_BulkCN = m_VLLcn*m_VLLitter + m_LLcn*m_LLitter + m_RLcn*m_SoilLitter+m_HumadCN*m_SoilHumads+m_HumusCN*m_SoilHumus;
	float RCNB=0.0;

	CN_ratios(&m_VLLcn, &m_LLcn, &m_RLcn, &RCNB, &m_HumadCN, &m_HumusCN, &m_PassiveCCN);

	m_BulkCN = 1.0 / (m_VLLitter/m_VLLcn + m_LLitter/m_LLcn + m_SoilLitter/m_RLcn + m_SoilHumads/m_HumadCN + m_SoilHumus/m_HumusCN + m_PassiveC/m_PassiveCCN);

	//SetSoilDensity();//brian turned off so bulk density doesn't get reset.

	UpdateData(FALSE);
}

void SitePage2::OnSCSuse() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_SoilRecover);

	if(m_SCSuse==1)
	{		
		Edt->EnableWindow(TRUE);
	}
	else
	{
		Edt->EnableWindow(FALSE);
	}
	
}

void SitePage2::OnKillfocusVLLitter() 
{
	// TODO: Add your control notification handler code here
	SetSoilOrganicPart(5);
}

void SitePage2::OnKillfocusLLitter() 
{
	// TODO: Add your control notification handler code here
	SetSoilOrganicPart(4);
}

void SitePage2::OnKillfocusSoilLitter() 
{
	SetSoilOrganicPart(1);	
}


void SitePage2::OnKillfocusSoilHumads() 
{
	// TODO: Add your control notification handler code here
	SetSoilOrganicPart(2);
}

void SitePage2::OnKillfocusSoilHumus() 
{
	// TODO: Add your control notification handler code here
	SetSoilOrganicPart(3);
}


void SitePage2::OnKillfocusPassiveC() 
{
	// TODO: Add your control notification handler code here
	SetSoilOrganicPart(6);
}

void SitePage2::SetSoilOrganicPart(int Index)
{
	UpdateData(TRUE);

	if (Index==1) //change humus fraction
	{
		m_SoilHumads=1.0-m_VLLitter-m_LLitter-m_SoilLitter-m_SoilHumus-m_PassiveC;
	}
    else 
		m_SoilHumus=1.0-m_VLLitter-m_LLitter-m_SoilLitter-m_SoilHumads-m_PassiveC;

	if(m_SoilHumads<0.0||m_SoilHumus<0.0)
	{
		CString NNN;
		NNN.Format("Error: The sum of fractions > 1");
		AfxMessageBox(NNN);
		return;
	}

	m_BulkCN = 1.0 / (m_VLLitter/m_VLLcn + m_LLitter/m_LLcn + m_SoilLitter/m_RLcn + m_SoilHumads/m_HumadCN + m_SoilHumus/m_HumusCN + m_PassiveC/m_PassiveCCN);

	UpdateData(FALSE);
}
