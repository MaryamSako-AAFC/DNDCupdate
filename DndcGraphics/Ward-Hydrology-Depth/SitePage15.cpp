// SitePage15.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "stdio.h"
#include <math.h>
#include "SitePara.h"
#include "SitePage15.h"
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

extern Site_BaseInformation	IData ;

/////////////////////////////////////////////////////////////////////////////
// SitePage15

IMPLEMENT_DYNCREATE(SitePage15, CPropertyPage)

SitePage15::SitePage15() : CPropertyPage(SitePage15::IDD)
{
	//{{AFX_DATA_INIT(SitePage15)
		// NOTE: the ClassWizard will add member initialization here
	m_DrainDepth=1.0f;
	m_DrainSpace=10.0f;
m_DrainRad=0.07f;
m_DrainBed=3.0f;
m_keDrain=0.6f;
m_MaxNMove=0.5f;// TileD - MaxNF
m_MobileNF=0.9f; //TileD - AvaNO3 to move next layer
m_NLayerF=0.75f;//TileD - Fraction of N not pref leached
m_NMoveRate=1.0f;// Overall N leaching Rate
m_SoilEvapF=1.0f;
m_RunOffWF=0.2f;//not sure think its set to snow runoff
m_RunOffNF=1.0f;
m_Factor1=1.0f;//nitrification factor
m_Factor2=1.0f;//snowtemp factor
m_Factor3=1.0f;//Snowmelt Factor
m_DenitGRate=1.0f;
m_NitGRate=1.0f;
m_NitRate=1.0f;
m_N2ORain=1.0f;
m_SprMeltF=1.0f;//spring melt multiplier
m_Factor4=0.3f;//fraction of avail-N plant uptake
m_Factor5=1.0f; //NH3 vol factor
m_Factor6=0.96f;//Fraction of N that does not move preferrentially through layers
m_Factor7=0;//autoharvest on
m_Factor8=1.0f;
m_Factor9=1.0f;
m_SpinUpCheck=FALSE;
m_SpinUpYears=0;
m_Factor10=1.0f;
m_Factor11=0.0f;
m_Factor13=1.0f;
m_UreaHydro=1.0f;
m_UreaHydro2=1.0f;
m_UreaDifF=0.08f;
m_NH3SoilDF=1.0f;

//m_SpinUpFileName
//m_CO2FileName

	//}}AFX_DATA_INIT
}

SitePage15::~SitePage15()
{
}

void SitePage15::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage15)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_SpinUpFileList, m_SpinUpFileList);
	DDX_Text(pDX, IDC_DrainDepth,	m_DrainDepth);
	DDX_Text(pDX, IDC_DrainSpace,	m_DrainSpace);
    DDX_Text(pDX, IDC_DrainRad,	m_DrainRad);
    DDX_Text(pDX, IDC_DrainBed,	m_DrainBed);
	DDX_Text(pDX, IDC_keDrain,	m_keDrain);
    DDX_Text(pDX, IDC_MaxNMove,	m_MaxNMove);
	DDX_Text(pDX, IDC_MobileNF,	m_MobileNF);
    DDX_Text(pDX, IDC_NLayerF,	m_NLayerF);
    DDX_Text(pDX, IDC_NMoveRate,	m_NMoveRate);
    DDX_Text(pDX, IDC_SoilEvapF,	m_SoilEvapF);
    DDX_Text(pDX, IDC_RunOffWF,	m_RunOffWF);
	DDX_Text(pDX, IDC_RunOffNF,	m_RunOffNF);
    DDX_Text(pDX, IDC_Factor1,	m_Factor1);
    DDX_Text(pDX, IDC_Factor2,	m_Factor2);
    DDX_Text(pDX, IDC_Factor3,	m_Factor3);
	DDX_Text(pDX, IDC_DenitGRate,	m_DenitGRate);
    DDX_Text(pDX, IDC_NitGRate,	m_NitGRate);
	 DDX_Text(pDX, IDC_SpinUpYears,	m_SpinUpYears);
    DDX_Text(pDX, IDC_N2ORain,	m_N2ORain);
	DDX_Text(pDX, IDC_SprMeltF,	m_SprMeltF);
	 DDX_Text(pDX, IDC_Factor4,	m_Factor4);
	  DDX_Text(pDX, IDC_Factor5,	m_Factor5);
	   DDX_Text(pDX, IDC_Factor6,	m_Factor6);
	    DDX_Text(pDX, IDC_Factor7,	m_Factor7);
		 DDX_Text(pDX, IDC_Factor8,	m_Factor8);
		  DDX_Text(pDX, IDC_Factor9,	m_Factor9);
		  DDX_Text(pDX, IDC_SWCWT,	m_Factor10);
		  DDX_Text(pDX, IDC_SWCWT2,	m_Factor11);
		  DDX_Check(pDX, IDC_SpinUpCheck, m_SpinUpCheck);
		  DDX_Text(pDX, IDC_Factor13,	m_Factor13);
		  DDX_Text(pDX, IDC_UreaHydro,	m_UreaHydro);
		  DDX_Text(pDX, IDC_UreaHydro2,	m_UreaHydro2);
		  DDX_Text(pDX, IDC_NH3SoilDF,	m_NH3SoilDF);
		  DDX_Text(pDX, IDC_UreaDifF,	m_UreaDifF);
	//DDX_Radio(pDX, IDC_DRAINRADIO1, m_TileOption);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(SitePage15, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage15)
	ON_BN_CLICKED(IDC_ACCEPTTILE, OnAccepttile)
	ON_BN_CLICKED(IDC_DRAINRADIO1, OnDrainradio1)
	ON_BN_CLICKED(IDC_DRAINRADIO2, OnDrainradio2)
	ON_BN_CLICKED(IDC_SpinUpCheck, OnSpinUpCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage15 diagnostics

#ifdef _DEBUG

/////////////////////////////////////////////////////////////////////////////
// SitePage15 message handlers
#endif

BOOL SitePage15::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL SitePage15::OnSetActive() 
{

		
if(IData.DrainDepth!=0.0) m_DrainDepth=IData.DrainDepth; 
if(IData.DrainSpace!=0.0) m_DrainSpace=IData.DrainSpace; 
if(IData.DrainRad!=0.0)m_DrainRad=IData.DrainRad;
if(IData.DrainBed!=0.0)m_DrainBed=IData.DrainBed;
if(IData.keDrain!=0.0)m_keDrain=IData.keDrain;
if(IData.MaxNMove!=0.0)m_MaxNMove=IData.MaxNMove;
if(IData.MobileNF!=0.0)m_MobileNF=IData.MobileNF;
if(IData.NLayerF!=0.0) m_NLayerF=IData.NLayerF;
if(IData.NMoveRate!=0.0)m_NMoveRate=IData.NMoveRate;
if(IData.SoilEvapF!=0.0)m_SoilEvapF=IData.SoilEvapF;
if(IData.RunOffWF!=0.0)m_RunOffWF=IData.RunOffWF;//b
if(IData.RunOffNF!=0.0)m_RunOffNF=IData.RunOffNF;
if(IData.Factor1!=0.0)m_Factor1=IData.Factor1;
if(IData.Factor2!=0.0)m_Factor2=IData.Factor2;
if(IData.Factor3!=0.0)m_Factor3=IData.Factor3;
if(IData.DenitGRate!=0.0)m_DenitGRate=IData.DenitGRate;
if(IData.NitGRate!=0.0)m_NitGRate=IData.NitGRate;
if(IData.NitRate!=0.0)m_NitRate=IData.NitRate;
if(IData.N2ORain!=0.0)m_N2ORain=IData.N2ORain;
if(IData.SprMeltF!=0.0)m_SprMeltF=IData.SprMeltF;
if(IData.Factor4!=0.0)m_Factor4=IData.Factor4;
if(IData.Factor5!=0.0)m_Factor5=IData.Factor5;
if(IData.Factor13!=0.0)m_Factor13=IData.Factor13;
if(IData.UreaHydro!=0.0)m_UreaHydro=IData.UreaHydro;
if(IData.UreaHydro2!=0.0)m_UreaHydro2=IData.UreaHydro2;
if(IData.NH3SoilDF!=0.0)m_NH3SoilDF=IData.NH3SoilDF;
if(IData.UreaDifF!=0.0)m_UreaDifF=IData.UreaDifF;
if(IData.Factor6!=0.0)m_Factor6=IData.Factor6;
if(IData.Factor7!=0.0)m_Factor7=IData.Factor7;
if(IData.SpinUpCheck==1)
{

	if(m_SpinUpFileList.GetCount()==0)
	{m_SpinUpFileList.InsertString(0, IData.SpinUpFileName);
	m_SpinUpFileList.SetCurSel(0);}

  m_SpinUpFileName=IData.SpinUpFileName;
	//Put the string on screen
	
	
	
}
//if(IData.Factor8!=0.0)m_Factor8=IData.Factor8;
//if(IData.Factor9!=0.0)m_Factor9=IData.Factor9;
//m_RunOffWF=IData.RunOffWF;
m_Factor8=IData.Factor8;
m_Factor9=IData.Factor9;
m_Factor10=IData.Factor10;//WT effect on soil Water
m_Factor11=IData.Factor11;
m_SpinUpCheck=IData.SpinUpCheck;
m_SpinUpYears=IData.SpinUpYears;
m_SpinUpFileName=IData.SpinUpFileName;
//m_TileOption=IData.TileOption;

UpdateData(FALSE);   	
	
	return CPropertyPage::OnSetActive();
}


// Read data from control into IData class
void SitePage15::GetAddParas()
{

IData.DrainDepth=m_DrainDepth; 
IData.DrainSpace=m_DrainSpace; 
IData.DrainRad=m_DrainRad;
IData.DrainBed=m_DrainBed;
IData.keDrain=m_keDrain;
IData.MaxNMove=m_MaxNMove;
IData.MobileNF=m_MobileNF;
IData.NLayerF=m_NLayerF;
IData.NMoveRate=m_NMoveRate;
IData.SoilEvapF=m_SoilEvapF;
IData.RunOffWF=m_RunOffWF;
IData.RunOffNF=m_RunOffNF;
IData.Factor1=m_Factor1;
IData.Factor2=m_Factor2;
IData.Factor3=m_Factor3;
IData.DenitGRate=m_DenitGRate;
IData.NitGRate=m_NitGRate;
IData.NitRate=m_NitRate;
IData.N2ORain=m_N2ORain;
IData.SprMeltF=m_SprMeltF;   
IData.TileOption=m_TileOption;	
IData.Factor4=m_Factor4;
IData.Factor5=m_Factor5;
IData.Factor6=m_Factor6;
IData.Factor7=m_Factor7;
IData.Factor8=m_Factor8;
IData.Factor9=m_Factor9;
IData.Factor10=m_Factor10;
IData.Factor11=m_Factor11;
IData.Factor13=m_Factor13;
IData.UreaHydro=m_UreaHydro;
IData.UreaHydro2=m_UreaHydro2;
IData.NH3SoilDF=m_NH3SoilDF;
IData.UreaDifF=m_UreaDifF;
IData.SpinUpCheck=m_SpinUpCheck;
IData.SpinUpYears=m_SpinUpYears;
IData.SpinUpFileName=m_SpinUpFileName;


}
int SitePage15::EditParameters()
{

	GetAddParas();	//get inputed values from controls
	
	OnSetActive();	//send values into controls

	return 1;



}
void SitePage15::ChangeParas()
{
if(m_DrainDepth!=0) IData.DrainDepth=m_DrainDepth; 
if(m_DrainSpace!=0) IData.DrainSpace=m_DrainSpace; 
if(m_DrainRad!=0) IData.DrainRad=m_DrainRad;
if(m_DrainBed!=0) IData.DrainBed=m_DrainBed;
if(m_keDrain!=0) IData.keDrain=m_keDrain;
if(m_MaxNMove!=0) IData.MaxNMove=m_MaxNMove;
if(m_MobileNF!=0) IData.MobileNF=m_MobileNF;
if(m_NLayerF!=0) IData.NLayerF=m_NLayerF;
if(m_NMoveRate!=0) IData.NMoveRate=m_NMoveRate;
if(m_SoilEvapF!=0) IData.SoilEvapF=m_SoilEvapF;
if(m_RunOffWF!=0) IData.RunOffWF=m_RunOffWF;//b
if(m_RunOffNF!=0) IData.RunOffNF=m_RunOffNF;
if(m_Factor1!=0) IData.Factor1=m_Factor1;
if(m_Factor2!=0) IData.Factor2=m_Factor2;
if(m_Factor3!=0) IData.Factor3=m_Factor3;
if(m_DenitGRate!=0) IData.DenitGRate=m_DenitGRate;
if(m_NitGRate!=0) IData.NitGRate=m_NitGRate;
if(m_NitRate!=0) IData.NitRate=m_NitRate;
if(m_N2ORain!=0) IData.N2ORain=m_N2ORain;
if(m_SprMeltF!=0) IData.SprMeltF=m_SprMeltF; 
if(m_Factor4!=0) IData.Factor4=m_Factor4;
if(m_Factor5!=0) IData.Factor5=m_Factor5;
if(m_Factor6!=0) IData.Factor6=m_Factor6;
if(m_Factor7!=0) IData.Factor7=m_Factor7;
if(m_Factor13!=0) IData.Factor13=m_Factor13;//solar rad effect on soil temp
if(m_UreaHydro!=0) IData.UreaHydro=m_UreaHydro;
if(m_UreaHydro2!=0) IData.UreaHydro2=m_UreaHydro2;
if(m_NH3SoilDF!=0) IData.NH3SoilDF=m_NH3SoilDF;
if(m_UreaDifF!=0) IData.UreaDifF=m_UreaDifF;

//if(m_Factor8!=0) IData.Factor8=m_Factor8;
//if(m_Factor9!=0) IData.Factor9=m_Factor9;  
IData.RunOffWF=m_RunOffWF;	
IData.Factor8=m_Factor8;
IData.Factor9=m_Factor9;
IData.Factor11=m_Factor11;
IData.Factor10=m_Factor10;
IData.SpinUpCheck=m_SpinUpCheck;
IData.SpinUpYears=m_SpinUpYears;
IData.SpinUpFileName=m_SpinUpFileName;
}
void SitePage15::OnAccepttile() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);

			GetAddParas();
	ChangeParas();

}

void SitePage15::OnDrainradio1() 
{
	// TODO: Add your control notification handler code here
	m_TileOption=0;
	UpdateData(TRUE);
	IData.TileOption = m_TileOption;	
}

void SitePage15::OnDrainradio2() 
{
	// TODO: Add your control notification handler code here
	m_TileOption=1;	
	UpdateData(TRUE);
	IData.TileOption = m_TileOption;	
}

void SitePage15::OnSpinUpCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	

	CEdit *Edt;
		
	if(m_SpinUpCheck==1)
	{
	
		//put file handler for pointing to file here
		SelectSpinUpFile();



	}
	else
	{
		
	}

	UpdateData(FALSE);	
}
void SitePage15::SelectSpinUpFile()
{
	char FileName[255];
	UpdateData(TRUE);
	int rrr, yyy;
	CString pre_SpinUpFileName[5];
	CString f_site, cst;
	FILE *Fsite;


	//Open a menu window
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();

	POSITION pos=ask.GetStartPosition();
	
	

	//Count number (num) of selected strings
	int k,num;
	num = m_SpinUpFileList.GetCount();//1 FG
		
	//Obtain order number (k) of each selected string
	k = m_SpinUpFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		//Obtain a character from the string
		pre_SpinUpFileName[num].Format("%s", ask.GetNextPathName(pos));
		if (pre_SpinUpFileName[num]=="") break;


		//Add the character into pre_ClimateFileName[num]
		m_SpinUpFileList.InsertString(k, pre_SpinUpFileName[num]);

		if (cst.IsEmpty() || pos==NULL) break;		
		if (m_SpinUpFileList.GetCount()==1) break;

		k++;
	}
	m_SpinUpFileName=pre_SpinUpFileName[0];
	//Put the string on screen
	m_SpinUpFileList.SetCurSel(k);
	
	UpdateData(FALSE);
}
