// ManureCycle.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "ManureCycle.h"
#include "ManureHousing.h"
#include "ManureGrazing.h"
#include "ManureLagoon.h"
#include "ManureCompost.h"
#include "ManureDigester.h"
#include "ManureField.h"
#include "Dndc_manure12.h"
#include "ManureSilo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManureCycle property page

IMPLEMENT_DYNCREATE(ManureCycle, CPropertyPage)

ManureCycle::ManureCycle() : CPropertyPage(ManureCycle::IDD)
{
	//{{AFX_DATA_INIT(ManureCycle)
	m_unit = 0;
	//}}AFX_DATA_INIT
}

ManureCycle::~ManureCycle()
{
}

void ManureCycle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureCycle)
	DDX_Radio(pDX, IDC_unit, m_unit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureCycle, CPropertyPage)
	//{{AFX_MSG_MAP(ManureCycle)
	ON_BN_CLICKED(IDC_HOUSE, OnHouse)
	//ON_BN_CLICKED(IDC_GROUND, OnPen)
	ON_BN_CLICKED(IDC_GRAZING, OnGrazing)
	ON_BN_CLICKED(IDC_LAGOON, OnLagoon)
	ON_BN_CLICKED(IDC_COMPOST, OnCompost)
	ON_BN_CLICKED(IDC_DIGESTER, OnDigester)
	ON_BN_CLICKED(IDC_FIELD, OnField)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Storage, OnStorage)
	ON_BN_CLICKED(IDC_SILO, OnSilo)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureCycle message handlers

void ManureCycle::OnHouse() 
{
	// TODO: Add your control notification handler code here
	ManureHousing ww;

	CClientDC pDC(this);	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);
	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);
	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));
	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);
	pDC.SetBkMode(TRANSPARENT);	

	if(ww.DoModal()==IDOK)
	{
		
	}

}


void ManureCycle::OnGrazing() 
{
	// TODO: Add your control notification handler code here
	CClientDC pDC(this);	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);
	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);
	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));
	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);
	pDC.SetBkMode(TRANSPARENT);	

	ManureGrazing ww;
	if(ww.DoModal()==IDOK)
	{

	}
}

void ManureCycle::OnLagoon() 
{
	// TODO: Add your control notification handler code here
	CClientDC pDC(this);	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);
	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);
	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));
	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);
	pDC.SetBkMode(TRANSPARENT);	

	ManureLagoon ww;
	if(ww.DoModal()==IDOK)
	{

	}
}

void ManureCycle::OnCompost() 
{
	// TODO: Add your control notification handler code here
		CClientDC pDC(this);	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);
	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);
	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));
	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);
	pDC.SetBkMode(TRANSPARENT);	

	ManureCompost ww;
	if(ww.DoModal()==IDOK)
	{

	}
}

void ManureCycle::OnDigester() 
{
	// TODO: Add your control notification handler code here
		CClientDC pDC(this);	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);
	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);
	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));
	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);
	pDC.SetBkMode(TRANSPARENT);	

	ManureDigester ww;
	if(ww.DoModal()==IDOK)
	{

	}
}

void ManureCycle::OnField() 
{
	// TODO: Add your control notification handler code here
	CClientDC pDC(this);	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);
	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);
	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));
	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);
	pDC.SetBkMode(TRANSPARENT);	

	ManureField ww;
	if(ww.DoModal()==IDOK)
	{

	}
}

BOOL ManureCycle::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "r");
	if(ddb==NULL) 
	{
		ddb=fopen(LB, "w");
		fprintf(ddb, "%d", 0);
		fclose(ddb);
	}

	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "r");
	if(ddb==NULL) note(0, LB);
	fscanf(ddb, "%d", &m_unit);
	fclose(ddb);

	UpdateData(FALSE);

	// TODO: Add extra initialization here
/*	m_redcolor=RGB(255,0,0);                      // red
	m_bluecolor=RGB(0,0,255);                     // blue
	m_textcolor=RGB(255,255,255);                 // white text
	m_redbrush.CreateSolidBrush(m_redcolor);      // red brush
	m_bluebrush.CreateSolidBrush(m_bluecolor);    // blue brush
*/	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH ManureCycle::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	if (pWnd->GetDlgCtrlID() == IDC_EDITcolor1)//第一个编辑框
   {
		pDC->SetBkColor(m_redcolor);    // 输入文本的的底色
		pDC->SetTextColor(m_textcolor);  // 输入文本的颜色
		hbr = (HBRUSH) m_redbrush;    // 编辑框控件的填充色
	}

/*	if (pWnd->GetDlgCtrlID() == IDC_EDIT2)//第二个编辑框
   {
		pDC->SetBkColor(m_bluecolor);    // 输入文本的的底色
		pDC->SetTextColor(m_textcolor);  // 输入文本的颜色
		hbr = (HBRUSH) m_bluebrush;    // 编辑框控件的填充色
	}
*/		
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void ManureCycle::OnStorage() 
{
	// TODO: Add your control notification handler code here
	Dndc_manure12 ww;
	if(ww.DoModal()==IDOK)
	{
		
	}
}

void ManureCycle::OnSilo() 
{
	// TODO: Add your control notification handler code here
	ManureSilo ww;
	if(ww.DoModal()==IDOK)
	{
		
	}
	
}

void ManureCycle::Onunit() 
{
	// TODO: Add your control notification handler code here
	m_unit = 0;

	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", m_unit);
	fclose(ddb);

	UpdateData(FALSE);
}

void ManureCycle::Onunit2() 
{
	// TODO: Add your control notification handler code here
	m_unit = 1;

	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", m_unit);
	fclose(ddb);

	UpdateData(FALSE);
}
