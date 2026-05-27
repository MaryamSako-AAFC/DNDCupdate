// WizardResult.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "WizardResult.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString Dates[366]={"0/1", 
				"1/1","1/2","1/3","1/4","1/5","1/6","1/7","1/8","1/9","1/10","1/11","1/12","1/13","1/14","1/15",
				"1/16","1/17","1/18","1/19","1/20","1/21","1/22","1/23","1/24","1/25","1/26","1/27","1/28","1/29","1/30","1/31",
				"2/1","2/2","2/3","2/4","2/5","2/6","2/7","2/8","2/9","2/10","2/11","2/12","2/13","2/14","2/15",
				"2/16","2/17","2/18","2/19","2/20","2/21","2/22","2/23","2/24","2/25","2/26","2/27","2/28",
				"3/1","3/2","3/3","3/4","3/5","3/6","3/7","3/8","3/9","3/10","3/11","3/12","3/13","3/14","3/15",
				"3/16","3/17","3/18","3/19","3/20","3/21","3/22","3/23","3/24","3/25","3/26","3/27","3/28","3/29","3/30","3/31",
				"4/1","4/2","4/3","4/4","4/5","4/6","4/7","4/8","4/9","4/10","4/11","4/12","4/13","4/14","4/15",
				"4/16","4/17","4/18","4/19","4/20","4/21","4/22","4/23","4/24","4/25","4/26","4/27","4/28","4/29","4/30",
				"5/1","5/2","5/3","5/4","5/5","5/6","5/7","5/8","5/9","5/10","5/11","5/12","5/13","5/14","5/15",
				"5/16","5/17","5/18","5/19","5/20","5/21","5/22","5/23","5/24","5/25","5/26","5/27","5/28","5/29","5/30","5/31",
				"6/1","6/2","6/3","6/4","6/5","6/6","6/7","6/8","6/9","6/10","6/11","6/12","6/13","6/14","6/15",
				"6/16","6/17","6/18","6/19","6/20","6/21","6/22","6/23","6/24","6/25","6/26","6/27","6/28","6/29","6/30",
				"7/1","7/2","7/3","7/4","7/5","7/6","7/7","7/8","7/9","7/10","7/11","7/12","7/13","7/14","7/15",
				"7/16","7/17","7/18","7/19","7/20","7/21","7/22","7/23","7/24","7/25","7/26","7/27","7/28","7/29","7/30","7/31",
				"8/1","8/2","8/3","8/4","8/5","8/6","8/7","8/8","8/9","8/10","8/11","8/12","8/13","8/14","8/15",
				"8/16","8/17","8/18","8/19","8/20","8/21","8/22","8/23","8/24","8/25","8/26","8/27","8/28","8/29","8/30","8/31",
				"9/1","9/2","9/3","9/4","9/5","9/6","9/7","9/8","9/9","9/10","9/11","9/12","9/13","9/14","9/15",
				"9/16","9/17","9/18","9/19","9/20","9/21","9/22","9/23","9/24","9/25","9/26","9/27","9/28","9/29","9/30",
				"10/1","10/2","10/3","10/4","10/5","10/6","10/7","10/8","10/9","10/10","10/11","10/12","10/13","10/14","10/15",
				"10/16","10/17","10/18","10/19","10/20","10/21","10/22","10/23","10/24","10/25","10/26","10/27","10/28","10/29","10/30","10/31",
				"11/1","11/2","11/3","11/4","11/5","11/6","11/7","11/8","11/9","11/10","11/11","11/12","11/13","11/14","11/15",
				"11/16","11/17","11/18","11/19","11/20","11/21","11/22","11/23","11/24","11/25","11/26","11/27","11/28","11/29","11/30",
				"12/1","12/2","12/3","12/4","12/5","12/6","12/7","12/8","12/9","12/10","12/11","12/12","12/13","12/14","12/15",
				"12/16","12/17","12/18","12/19","12/20","12/21","12/22","12/23","12/24","12/25","12/26","12/27","12/28","12/29","12/30","12/31"};


/////////////////////////////////////////////////////////////////////////////
// WizardResult dialog
float rootDOC;

WizardResult::WizardResult(CWnd* pParent /*=NULL*/)
	: CDialog(WizardResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(WizardResult)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void WizardResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WizardResult)
	DDX_Control(pDX, IDC_WizardYear, m_WizardYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WizardResult, CDialog)
	//{{AFX_MSG_MAP(WizardResult)
	ON_BN_CLICKED(IDC_GHG, OnGhg)
	ON_BN_CLICKED(IDC_Agronomy, OnAgronomy)
	ON_BN_CLICKED(IDC_Crop, OnCrop)
	ON_BN_CLICKED(IDC_Water, OnWater)
	ON_BN_CLICKED(IDC_GWP, OnGwp)
	ON_CBN_SELCHANGE(IDC_WizardYear, OnSelchangeWizardYear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WizardResult message handlers
BOOL WizardResult::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int total_yr;
    char site_file[80], site[120];
    FILE *fp;

    sprintf(site_file, "%s\\Inputs\\Site", OUTPUT);
    fp = fopen(site_file, "r");
    if ( fp == NULL )
	{
		CString note;
		note.Format("Cannot open %s", site_file);
		AfxMessageBox(note);
		exit(0);
	}
 
    fscanf(fp, "%s", site);
    fscanf(fp, "%d", &total_yr);
	fclose( fp );

	m_WizardYear.ResetContent();
	for (int i=0;i<total_yr;i++)
	{
		char fname[50];
		sprintf(fname,"Year %d",i+1);
		m_WizardYear.AddString(fname);
	}

	read_summary(1);
	
	
			runoffN = 0.0;
			leachHumN = 0.0;
			//weedN = 0.0;
			//weedupN = 0.0;
			year=1;

			m_WizardYear.SetCurSel(year-1);
			
#ifdef WIZARD
	char hh[200];
		CString IDfile;
		FILE* fid;
		IDfile.Format("%s\\Inter\\SelectedCounty.txt", OUTPUT);
		fid = fopen(IDfile, "r");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("4. Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fscanf(fid, "%s", hh);
		sprintf(SelectedState, "%s", hh);
		fscanf(fid, "%s", hh);
		sprintf(SelectedCounty, "%s", hh);
		fscanf(fid, "%d", &CropCode);
		fscanf(fid, "%f", &haha);

		fclose(fid);
#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void WizardResult::OnGhg() 
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

	pDC.FillSolidRect(20, 10, 1300, 740, RGB(120,120,150));

	int r=30;
	int t=1.0;
	int z=450;
	
	int c1=150,c2=250,c3=0;
	int b1=150,b2=50,b3=0;

	float ji=40.0;
	
	int L_manureC = (int)(manureC/ji);
	int L_litterC = (int)(litterC/ji);
	int L_rootC = (int)(rootC/ji);
	int L_weedC = (int)(rootDOC/ji);
	int L_soilCO2 = (int)(soilCO2/ji);
	int L_leachC = (int)(leachHumC/ji);
	int L_CH4 = (int)(CH4/ji);
	int L_rootCO2 = (int)(rootCO2/ji);

	//dSOC = (manureC+litterC+rootC+weedC)-(soilCO2+leachHumC+CH4*0.2);
	//int L_dC = (int)(dC/20);
	int L_dC = (int)(dSOC/ji);

	pDC.FillSolidRect(z-L_manureC, 150, L_manureC, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_litterC, 200, L_litterC, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_rootC, 250, L_rootC, r, RGB(c1,c2,c3));
	//pDC.FillSolidRect(z-L_weedC, 300, L_weedC, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 350, L_soilCO2, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 400, L_leachC, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 450, L_CH4, r, RGB(c1,c2,c3));
	//pDC.FillSolidRect(z, 500, L_rootCO2, r, RGB(c1,c2,c3));
	if(L_dC>0) pDC.FillSolidRect(z, 550, -L_dC, r, RGB(200,150,0));
	else pDC.FillSolidRect(z-L_dC, 550, L_dC, r, RGB(200,150,0));


	int x=900, y=50, c=50, b=370;
	CString w;
	
	//w.Format("( Source data file: \%s )", rcd);
	//pDC.TextOut(350, 90, w);

	pDC.SetTextAlign(TA_LEFT);
	pDC.SetTextColor(RGB(255,255,255));
	
	w.Format("Manure C input");
	pDC.TextOut(x, y+50+1*(c), w);
	w.Format("Crop shoot C input");
	pDC.TextOut(x, y+50+2*(c), w);
	w.Format("Crop root C input");
	pDC.TextOut(x, y+50+3*(c), w);
	w.Format("Root exudation");
	pDC.TextOut(x, y+50+4*(c), w);
	w.Format("CO2 emission");
	pDC.TextOut(x, y+50+5*(c), w);
	w.Format("DOC leaching");
	pDC.TextOut(x, y+50+6*(c), w);
	w.Format("CH4 emission");
	pDC.TextOut(x, y+50+7*(c), w);
	//w.Format("Root respiration");
	//pDC.TextOut(x, y+50+8*(c), w);
	w.Format("Change in soil C storage");
	pDC.TextOut(x, y+50+9*(c), w);

	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));
		
	w.Format("%8.1f", manureC);
	pDC.TextOut(x+b, y+50+1*(c), w);	
	w.Format("%8.1f", litterC);
	pDC.TextOut(x+b, y+50+2*(c), w);	
	w.Format("%8.1f", rootC);
	pDC.TextOut(x+b, y+50+3*(c), w);	
	w.Format("%8.1f", rootDOC);
	pDC.TextOut(x+b, y+50+4*(c), w);
	//w.Format("%8.1f", soilCO2);
	w.Format("%8.1f", soilCO2);
	pDC.TextOut(x+b, y+50+5*(c), w);	
	w.Format("%8.1f", leachHumC);
	pDC.TextOut(x+b, y+50+6*(c), w);	
	w.Format("%8.1f", CH4);
	pDC.TextOut(x+b, y+50+7*(c), w);	
	//w.Format("%8.1f", rootCO2);
	//pDC.TextOut(x+b, y+50+8*(c), w);
	w.Format("%8.1f", dSOC);
	pDC.TextOut(x+b, y+50+9*(c), w);

	//CPen *pOldPen = NULL;
	CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = pDC.SelectObject(&Pen1);	
	
	pDC.MoveTo(z, 130);
	pDC.LineTo(z, 650);

	pDC.SelectObject(pOldPen);
	Pen1.DeleteObject();	

	CFont hNewFont;
	TEXTMETRIC tm;
	CString dndc;
#ifdef WIZARD	
	dndc.Format("Soil C balance: %s county in %s, %s, year %d (Unit: kg C/ha)", SelectedCounty, SelectedState, Crop_Name[1], year);
#else
	dndc.Format("Soil C balance (kg C/ha/yr): Site: %s   Year %d", Site_Name, year);
#endif

	hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_LEFT);
		pDC.TextOut(50, 40, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("C inputs");
	hNewFont.CreateFont(30,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(z-150, 100, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("C outputs");
	hNewFont.CreateFont(30,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(z+150, 100, dndc);
		
		hNewFont.DeleteObject();


	
	
}

void WizardResult::OnAgronomy() 
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

	pDC.FillSolidRect(20, 10, 1300, 740, RGB(120,120,150));

	int t=1.0;
	int z=450;
	int r=20;
	
	//int L_SON1 = (int)(SON1 /400.0);
	//int L_SON2 = (int)(SON2 /400.0);
	//int L_SIN1 = (int)(SIN1 /400.0);
	//int L_SIN2 = (int)(SIN2 /400.0);	

	int L_manureN = (int)(manureN/t);
	int L_litterN = (int)(litterN/t);	
	int L_rootN = (int)(rootN/t);
	int L_irriN = (int)(irriN/t);
	int L_rainN = (int)(rainN/t);
	int L_fertN = (int)(fertN/t);
	int L_fixN = (int)(SoilFixN/t);

	int L_leachHumN = (int)(leachHumN/t);
	int L_upN = (int)((uptakeN)/t);
	//int L_weedupN = (int)(weedupN/t);
	int L_leachN = (int)(leachN/t);
	int L_runoffN = 0;//(int)(runoffN/t);
	int L_NH3 = (int)(NH3/t);
	int L_N2O = (int)(N2O/t);	
	int L_NO = (int)(NO/t);
	int L_N2 = (int)(N2/t);
	//int L_NO2 = (int)(NO2/t);

	float dN =(manureN+litterN+rootN+rainN+fertN+irriN+SoilFixN)-
				(leachHumN+uptakeN+leachN+runoffN+NH3+N2O+NO+N2);

	int L_dN = (int)(dN/t);


	int c1=150,c2=250,c3=0;
	int b1=150,b2=50,b3=0;

	//pDC.FillSolidRect(50, 50, L_SIN1, 10, RGB(150,150,0));
	//pDC.FillSolidRect(50, 100, L_SIN2, 10, RGB(150,150,0));
	

	pDC.FillSolidRect(z-L_manureN, 150, L_manureN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_litterN, 180, L_litterN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_rootN, 210, L_rootN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_irriN, 240, L_irriN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_rainN, 270, L_rainN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_fertN, 300, L_fertN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_fixN, 330, L_fixN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 360, L_leachN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 390, L_runoffN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 420, L_upN, r, RGB(c1,c2,c3));
	//pDC.FillSolidRect(z, 450, L_weedupN, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 480, L_NH3, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 510, L_N2O, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 540, L_NO, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 570, L_N2, r, RGB(c1,c2,c3));
	//pDC.FillSolidRect(z, 600, L_NO2, r, RGB(c1,c2,c3));
	if(L_dN>0) pDC.FillSolidRect(z, 600, -L_dN, r, RGB(250,200,0));
	else pDC.FillSolidRect(z-L_dN, 600, L_dN, r, RGB(200,0,0));

	
	int x=900, y=70, c=30, b=370;
	

	pDC.SetTextAlign(TA_LEFT);
	pDC.SetTextColor(RGB(255,255,255));
	
	CString w;
	w.Format("Manure N input");
	pDC.TextOut(x, y+50+1*(c), w);
	w.Format("Crop stub N input");
	pDC.TextOut(x, y+50+2*(c), w);
		w.Format("Crop root N input");
	pDC.TextOut(x, y+50+3*(c), w);
	w.Format("Irrigation N input");
	pDC.TextOut(x, y+50+4*(c), w);
	w.Format("Atmospheric N deposit");
	pDC.TextOut(x, y+50+5*(c), w);
	w.Format("Fertilizer N input");
	pDC.TextOut(x, y+50+6*(c), w);
	w.Format("N fixation");
	pDC.TextOut(x, y+50+7*(c), w);
	w.Format("N leaching");
	pDC.TextOut(x, y+50+8*(c), w);
	w.Format("N runoff");
	pDC.TextOut(x, y+50+9*(c), w);
	w.Format("N uptaken by crop");
	pDC.TextOut(x, y+50+10*(c), w);
	//w.Format("N uptaken by weeds");
	//pDC.TextOut(x, y+50+11*(c), w);
	w.Format("NH3 volatilization");
	pDC.TextOut(x, y+50+12*(c), w);
	w.Format("N2O flux");
	pDC.TextOut(x, y+50+13*(c), w);
	w.Format("NO flux");
	pDC.TextOut(x, y+50+14*(c), w);
	w.Format("N2 flux");
	pDC.TextOut(x, y+50+15*(c), w);
	w.Format("Change in soil N storage");
	pDC.TextOut(x, y+50+16*(c), w);

	//w.Format("Soil N input and output fluxes at site %s in year %d", Site_Name, year);
	//pDC.TextOut(350, 60, w);

	//w.Format("( Source data file: \%s )", rcd);
	//pDC.TextOut(350, 80, w);

	pDC.SetTextAlign(TA_RIGHT);

	pDC.SetTextColor(RGB(0,0,0));
	//pDC.SetTextColor(RGB(80,80,80));
		
	w.Format("%8.1f", manureN);
	pDC.TextOut(x+b, y+50+1*(c), w);	
	w.Format("%8.1f", litterN);
	pDC.TextOut(x+b, y+50+2*(c), w);
	w.Format("%8.1f", rootN);
	pDC.TextOut(x+b, y+50+3*(c), w);	
	w.Format("%8.1f", irriN);
	pDC.TextOut(x+b, y+50+4*(c), w);	
	w.Format("%8.1f", rainN);
	pDC.TextOut(x+b, y+50+5*(c), w);	
	w.Format("%8.1f", fertN);
	pDC.TextOut(x+b, y+50+6*(c), w);
	w.Format("%8.1f", SoilFixN);
	pDC.TextOut(x+b, y+50+7*(c), w);
		
	w.Format("%8.1f", leachN);
	pDC.TextOut(x+b, y+50+8*(c), w);
	w.Format("%8.1f", runoffN);
	pDC.TextOut(x+b, y+50+9*(c), w);
	w.Format("%8.1f", uptakeN);
	pDC.TextOut(x+b, y+50+10*(c), w);
	//w.Format("%8.1f", weedupN);
	//pDC.TextOut(x+b, y+50+11*(c), w);
	w.Format("%8.1f", NH3);
	pDC.TextOut(x+b, y+50+12*(c), w);
	w.Format("%8.1f", N2O);
	pDC.TextOut(x+b, y+50+13*(c), w);
	w.Format("%8.1f", NO);
	pDC.TextOut(x+b, y+50+14*(c), w);
	w.Format("%8.1f", N2);
	pDC.TextOut(x+b, y+50+15*(c), w);
	w.Format("%8.1f", dN);
	pDC.TextOut(x+b, y+50+16*(c), w);

	//w.Format("NO2 flux");
	//pDC.TextOut(x, y+50+16*(c), w);
	//w.Format("%8.1f", NO2);
	//pDC.TextOut(x+b, y+50+16*(c), w);

	//CPen *pOldPen = NULL;
	CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = pDC.SelectObject(&Pen1);	
	//pDC.MoveTo(20, 350);
	//pDC.LineTo(1050, 350);

	//pDC.MoveTo(20, 145);
	//pDC.LineTo(1050, 145);

	pDC.MoveTo(z, 110);
	pDC.LineTo(z, 650);


	pDC.SelectObject(pOldPen);
	Pen1.DeleteObject();
	
	CFont hNewFont;
	TEXTMETRIC tm;
	CString dndc;
#ifdef WIZARD		
	dndc.Format("Soil N balance: %s county in %s, %s, year %d (Unit: kg N/ha)", SelectedCounty, SelectedState, Crop_Name[1], year);
#else
	dndc.Format("Soil N balance (kg N/ha/yr): Site: %s   Year: %d", Site_Name, year);
#endif
	
		hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_LEFT);
		pDC.TextOut(50, 40, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("N inputs");
	hNewFont.CreateFont(30,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(z-150, 100, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("N outputs");
	hNewFont.CreateFont(30,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(z+150, 100, dndc);
		
		hNewFont.DeleteObject();	
}


void WizardResult::OnCrop() 
{
	// TODO: Add your control notification handler code here
	int L_Grain, L_Straw, L_Root, O_Grain, O_Straw, O_Root, L_T, WD, ND, TD, tDD, L_upN; 

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

	pDC.FillSolidRect(20, 10, 1300, 770, RGB(120,120,150));

	int r=10;
	int t=1.0;
	int z=450;	
	int c1=150,c2=250,c3=0;
	int b1=150,b2=50,b3=0;
	int YY=170, dr=16;
	int x=700, y=100, c=16, b=380;
	CString w;	
	
	L_Grain = (int)(prograin[1]/10);
	L_Straw = (int)(prostraw[1]/10);
	L_Root = (int)(proroot[1]/10);

	O_Grain=(int)(Optimum_grain[1]/10);
	O_Straw=(int)(Optimum_straw[1]/10);
	O_Root=(int)(Optimum_root[1]/10);
	
	WD=(int)(Water_demand[1]/2.5);
	L_T = (int)(CropTrans[1]/2.5);

	ND=(int)(N_demand[1]/1.0);
	L_upN = (int)(CropN[1]);//(uptakeSoilN[1]);//((uptakeSoilN[1]+fixN[1])/1.0);
		
	TD=(int)(T_demand[1]/25.);
	tDD=(int)(TDD[1]/25.);

	if(WD>600)
	{
		WD=(int)(WD*0.2);
		L_T=(int)(L_T*0.2);
	}

	if(ND>600)
	{
		ND=(int)(ND*0.2);
		L_upN=(int)(L_upN*0.2);
	}

	if(O_Grain>600||O_Straw>600||O_Root>600)
	{
		O_Grain=(int)(O_Grain*0.2);
		O_Straw=(int)(O_Straw*0.2);
		O_Root=(int)(O_Root*0.2);
	
		L_Grain=(int)(L_Grain*0.2);
		L_Straw=(int)(L_Straw*0.2);
		L_Root=(int)(L_Root*0.2);
	}

	if(WD>600) WD=600;
	if(L_T>600) L_T=600;
	if(ND>600) ND=600;
	if(L_upN>600) L_upN=600;

	pDC.FillSolidRect(150, YY+0*dr, O_Grain, r, RGB(250,250,150));
	pDC.FillSolidRect(150, YY+1*dr, L_Grain, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(150, YY+3*dr, O_Straw, r, RGB(250,250,150));
	pDC.FillSolidRect(150, YY+4*dr, L_Straw, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(150, YY+6*dr, O_Root, r, RGB(250,250,150));
	pDC.FillSolidRect(150, YY+7*dr, L_Root, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(150, YY+9*dr, WD, r, RGB(130,150,250));
	pDC.FillSolidRect(150, YY+10*dr, L_T, r, RGB(50,60,200));

	pDC.FillSolidRect(150, YY+12*dr, ND, r, RGB(173,136,190));
	pDC.FillSolidRect(150, YY+13*dr, L_upN, r, RGB(132,39,126));
	
	pDC.FillSolidRect(150, YY+15*dr, TD, r, RGB(244,128,120));
	pDC.FillSolidRect(150, YY+16*dr, tDD, r, RGB(211,32,47));
	
	pDC.SetTextAlign(TA_LEFT);
	pDC.SetTextColor(RGB(255,255,255));

	w.Format("Maximum grain");
	pDC.TextOut(x, y+50+1*(c), w);	

	w.Format("kg C/ha");
	pDC.TextOut(x+400, y+50+1*(c), w);

	w.Format("Actual grain");
	pDC.TextOut(x, y+50+2*(c), w);	
	
	w.Format("Maximum leaf+stem");
	pDC.TextOut(x, y+50+4*(c), w);
	w.Format("Actual leaf+stem");
	pDC.TextOut(x, y+50+5*(c), w);

	w.Format("Maximum root");
	pDC.TextOut(x, y+50+7*(c), w);	
	w.Format("Actual root");
	pDC.TextOut(x, y+50+8*(c), w);	

	w.Format("Water demand");
	pDC.TextOut(x, y+50+10*(c), w);

	w.Format("mm");
	pDC.TextOut(x+400, y+50+10*(c), w);

	w.Format("Water uptake");
	pDC.TextOut(x, y+50+11*(c), w);	

	w.Format("N demand");
	pDC.TextOut(x, y+50+13*(c), w);

	w.Format("kg N/ha");
	pDC.TextOut(x+400, y+50+13*(c), w);

	w.Format("N uptake");
	pDC.TextOut(x, y+50+14*(c), w);

	w.Format("Temperature demand");
	pDC.TextOut(x, y+50+16*(c), w);
	w.Format("TDD");
	pDC.TextOut(x, y+50+17*(c), w);
	
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));

	w.Format("%8.0f", Optimum_grain[1]);
	pDC.TextOut(x+b, y+50+1*(c), w);		
	w.Format("%8.0f", prograin[1]);
	pDC.TextOut(x+b, y+50+2*(c), w);
	
	w.Format("%8.0f", Optimum_straw[1]);
	pDC.TextOut(x+b, y+50+4*(c), w);
	w.Format("%8.0f", prostraw[1]);
	pDC.TextOut(x+b, y+50+5*(c), w);
	
	w.Format("%8.0f", Optimum_root[1]);
	pDC.TextOut(x+b, y+50+7*(c), w);
	w.Format("%8.0f", proroot[1]);
	pDC.TextOut(x+b, y+50+8*(c), w);
	
	w.Format("%8.0f", Water_demand[1]);
	pDC.TextOut(x+b, y+50+10*(c), w);	
	w.Format("%8.0f", CropTrans[1]);
	pDC.TextOut(x+b, y+50+11*(c), w);

	w.Format("%8.0f", N_demand[1]);
	pDC.TextOut(x+b, y+50+13*(c), w);	
	w.Format("%8.0f", CropN[1]);//uptakeSoilN[1]);//uptakeSoilN[1]+fixN[1]);//
	pDC.TextOut(x+b, y+50+14*(c), w);

	w.Format("%8.0f", T_demand[1]);
	pDC.TextOut(x+b, y+50+16*(c), w);	
	w.Format("%8.0f", TDD[1]);
	pDC.TextOut(x+b, y+50+17*(c), w);
	
	//CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	//pOldPen = pDC.SelectObject(&Pen1);	
	
	//pDC.SelectObject(pOldPen);
	//Pen1.DeleteObject();	

	//CFont hNewFont;
	//TEXTMETRIC tm;
	CString dndc;

pDC.SetTextAlign(TA_LEFT);
	dndc.Format("--------------------------------------------------------------------------------------");
	pDC.TextOut(650, 140, dndc);
	
#ifdef WIZARD	
		dndc.Format("Crop production: %s county in %s, %s, year %d (Unit: kg dry matter/ha)", SelectedCounty, SelectedState, Crop_Name[1], year);
#else
		dndc.Format("Crop 1: %s    %s - %s", Crop_Name[1], Dates[PlantDay[1]], Dates[HarvestDay[1]]);
#endif 

	pDC.TextOut(150, 140, dndc);

	////////////////////////////////////////
	YY=480;
	y=400;

	L_Grain = (int)(prograin[2]/10);
	L_Straw = (int)(prostraw[2]/10);
	L_Root = (int)(proroot[2]/10);

	O_Grain=(int)(Optimum_grain[2]/10);
	O_Straw=(int)(Optimum_straw[2]/10);
	O_Root=(int)(Optimum_root[2]/10);

	L_T = (int)(CropTrans[2]/2.5);
	WD=(int)(Water_demand[2]/2.5);
	ND=(int)(N_demand[2]/1.0);
	TD=(int)(T_demand[2]/25.);
	tDD=(int)(TDD[2]/25.);
	L_upN = (int)(CropN[2]);//(uptakeSoilN[2]);//(uptakeSoilN[2]+fixN[2])/1.0);

	if(WD>600)
	{
		WD=(int)(WD*0.2);
		L_T=(int)(L_T*0.2);
	}

	if(ND>600)
	{
		ND=(int)(ND*0.2);
		L_upN=(int)(L_upN*0.2);
	}

	if(O_Grain>600||O_Straw>600||O_Root>600)
	{
		O_Grain=(int)(O_Grain*0.2);
		O_Straw=(int)(O_Straw*0.2);
		O_Root=(int)(O_Root*0.2);
	
		L_Grain=(int)(L_Grain*0.2);
		L_Straw=(int)(L_Straw*0.2);
		L_Root=(int)(L_Root*0.2);
	}

	if(O_Grain>600) O_Grain=600;
	if(O_Straw>600) O_Straw=600;
	if(O_Root>600) O_Root=600;

	if(L_Grain>600) L_Grain=600;
	if(L_Straw>600) L_Straw=600;
	if(L_Root>600) L_Root=600;
	if(WD>600) WD=600;
	if(L_T>600) L_T=600;
	if(ND>600) ND=600;
	if(L_upN>600) L_upN=600;

	pDC.FillSolidRect(150, YY+0*dr, O_Grain, r, RGB(250,250,150));
	pDC.FillSolidRect(150, YY+1*dr, L_Grain, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(150, YY+3*dr, O_Straw, r, RGB(250,250,150));
	pDC.FillSolidRect(150, YY+4*dr, L_Straw, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(150, YY+6*dr, O_Root, r, RGB(250,250,150));
	pDC.FillSolidRect(150, YY+7*dr, L_Root, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(150, YY+9*dr, WD, r, RGB(130,150,250));
	pDC.FillSolidRect(150, YY+10*dr, L_T, r, RGB(50,60,200));

	pDC.FillSolidRect(150, YY+12*dr, ND, r, RGB(173,136,190));
	pDC.FillSolidRect(150, YY+13*dr, L_upN, r, RGB(132,39,126));
	
	pDC.FillSolidRect(150, YY+15*dr, TD, r, RGB(244,128,120));
	pDC.FillSolidRect(150, YY+16*dr, tDD, r, RGB(211,32,47));
	
	pDC.SetTextAlign(TA_LEFT);
	pDC.SetTextColor(RGB(255,255,255));

	w.Format("Maximum grain");
	pDC.TextOut(x, y+50+1*(c), w);	

	w.Format("kg C/ha");
	pDC.TextOut(x+400, y+50+1*(c), w);

	w.Format("Actual grain");
	pDC.TextOut(x, y+50+2*(c), w);	
	
	w.Format("Maximum leaf+stem");
	pDC.TextOut(x, y+50+4*(c), w);
	w.Format("Actual leaf+stem");
	pDC.TextOut(x, y+50+5*(c), w);

	w.Format("Maximum root");
	pDC.TextOut(x, y+50+7*(c), w);	
	w.Format("Actual root");
	pDC.TextOut(x, y+50+8*(c), w);	

	w.Format("Water demand");
	pDC.TextOut(x, y+50+10*(c), w);

	w.Format("mm");
	pDC.TextOut(x+400, y+50+10*(c), w);

	w.Format("Water uptake");
	pDC.TextOut(x, y+50+11*(c), w);	

	w.Format("N demand");
	pDC.TextOut(x, y+50+13*(c), w);

	w.Format("kg N/ha");
	pDC.TextOut(x+400, y+50+13*(c), w);

	w.Format("N uptake");
	pDC.TextOut(x, y+50+14*(c), w);

	w.Format("Temperature demand");
	pDC.TextOut(x, y+50+16*(c), w);
	w.Format("TDD");
	pDC.TextOut(x, y+50+17*(c), w);
	
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));

	w.Format("%8.0f", Optimum_grain[2]);
	pDC.TextOut(x+b, y+50+1*(c), w);		
	w.Format("%8.0f", prograin[2]);
	pDC.TextOut(x+b, y+50+2*(c), w);
	
	w.Format("%8.0f", Optimum_straw[2]);
	pDC.TextOut(x+b, y+50+4*(c), w);
	w.Format("%8.0f", prostraw[2]);
	pDC.TextOut(x+b, y+50+5*(c), w);
	
	w.Format("%8.0f", Optimum_root[2]);
	pDC.TextOut(x+b, y+50+7*(c), w);
	w.Format("%8.0f", proroot[2]);
	pDC.TextOut(x+b, y+50+8*(c), w);
	
	w.Format("%8.0f", Water_demand[2]);
	pDC.TextOut(x+b, y+50+10*(c), w);	
	w.Format("%8.0f", CropTrans[2]);
	pDC.TextOut(x+b, y+50+11*(c), w);

	w.Format("%8.0f", N_demand[2]);
	pDC.TextOut(x+b, y+50+13*(c), w);	
	w.Format("%8.0f", CropN[2]);//uptakeSoilN[2]);
	pDC.TextOut(x+b, y+50+14*(c), w);

	w.Format("%8.0f", T_demand[2]);
	pDC.TextOut(x+b, y+50+16*(c), w);	
	w.Format("%8.0f", TDD[2]);
	pDC.TextOut(x+b, y+50+17*(c), w);
	
pDC.SetTextAlign(TA_LEFT);
	dndc.Format("--------------------------------------------------------------------------------------");
	pDC.TextOut(650, 450, dndc);


#ifdef WIZARD	
		dndc.Format("Crop production: %s county in %s, %s, year %d (Unit: kg dry matter/ha)", SelectedCounty, SelectedState, Crop_Name[2], year);
#else
		dndc.Format("Crop 2: %s    %s - %s", Crop_Name[2], Dates[PlantDay[2]], Dates[HarvestDay[2]]);
#endif 

	pDC.TextOut(150, 450, dndc);
	////////////////////////////////////////

	CFont hNewFont;
		TEXTMETRIC tm;
		//CString dndc;
		dndc.Format("%s", "Crop Yields and Heat-Water-Nitrogen Stresses");

		hNewFont.CreateFont(35,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);
		pDC.SetBkMode(TRANSPARENT);
		pDC.GetTextMetrics(&tm);

		pDC.SetTextColor(RGB(250,250,255));//5,85,100));	
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(700, 50, dndc);

		hNewFont.DeleteObject();
/*
	YY=550;
	y=470;

	L_Grain = (int)(prograin[3]/10);
	L_Straw = (int)(prostraw[3]/10);
	L_Root = (int)(proroot[3]/10);

	O_Grain=(int)(Optimum_yield[3]/10);
	O_Straw=(int)(Optimum_straw[3]/10);
	O_Root=(int)(Optimum_root[3]/10);
	L_T = (int)(CropTrans[3]/2.5);
	WD=(int)(Water_demand[3]/2.5);
	ND=(int)(N_demand[3]/1.0);
	TD=(int)(T_demand[3]/25.);
	tDD=(int)(TDD[3]/25.);
	L_upN = (int)(CropN[3]);//(uptakeSoilN[3]+fixN[3])/1.0);

	if(O_Grain>600) O_Grain=600;
	if(O_Straw>600) O_Straw=600;
	if(O_Root>600) O_Root=600;
	if(L_Grain>600) L_Grain=600;
	if(L_Straw>600) L_Straw=600;
	if(L_Root>600) L_Root=600;
	if(WD>600) WD=600;
	if(L_T>600) L_T=600;
	if(ND>600) ND=600;
	if(L_upN>600) L_upN=600;

	pDC.FillSolidRect(150, YY+0*dr, O_Grain, r, RGB(250,250,150));
	pDC.FillSolidRect(150, YY+1*dr, L_Grain, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(150, YY+2*dr, L_Straw, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(150, YY+3*dr, L_Root, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(150, YY+5*dr, WD, r, RGB(130,150,250));
	pDC.FillSolidRect(150, YY+6*dr, L_T, r, RGB(50,60,200));

	pDC.FillSolidRect(150, YY+8*dr, ND, r, RGB(173,136,190));
	pDC.FillSolidRect(150, YY+9*dr, L_upN, r, RGB(132,39,126));
	
	pDC.FillSolidRect(150, YY+11*dr, TD, r, RGB(244,128,120));
	pDC.FillSolidRect(150, YY+12*dr, tDD, r, RGB(211,32,47));
	
	pDC.SetTextAlign(TA_LEFT);
	pDC.SetTextColor(RGB(255,255,255));

	w.Format("Optimum yield (kg/ha)");
	pDC.TextOut(x, y+50+1*(c), w);	
	w.Format("Grain (kg/ha)");
	pDC.TextOut(x, y+50+2*(c), w);
	w.Format("Straw (kg/ha)");
	pDC.TextOut(x, y+50+3*(c), w);
	w.Format("Root (kg/ha)");
	pDC.TextOut(x, y+50+4*(c), w);	

	w.Format("Water demand (mm)");
	pDC.TextOut(x, y+50+6*(c), w);
	w.Format("Water uptake (mm)");
	pDC.TextOut(x, y+50+7*(c), w);	

	w.Format("N demand (kg N/ha)");
	pDC.TextOut(x, y+50+9*(c), w);
	w.Format("N uptake (kg N/ha)");
	pDC.TextOut(x, y+50+10*(c), w);
	w.Format("Temperature demand");
	pDC.TextOut(x, y+50+12*(c), w);
	w.Format("TDD");
	pDC.TextOut(x, y+50+13*(c), w);
	
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));

	w.Format("%8.0f", Optimum_yield[3]);
	pDC.TextOut(x+b, y+50+1*(c), w);		
	w.Format("%8.0f", prograin[3]);
	pDC.TextOut(x+b, y+50+2*(c), w);	
	w.Format("%8.0f", prostraw[3]);
	pDC.TextOut(x+b, y+50+3*(c), w);	
	w.Format("%8.0f", proroot[3]);
	pDC.TextOut(x+b, y+50+4*(c), w);
	
	w.Format("%8.0f", Water_demand[3]);
	pDC.TextOut(x+b, y+50+6*(c), w);	
	w.Format("%8.0f", CropTrans[3]);
	pDC.TextOut(x+b, y+50+7*(c), w);
	w.Format("%8.0f", N_demand[3]);
	pDC.TextOut(x+b, y+50+9*(c), w);	
	w.Format("%8.0f", CropN[3]);
	pDC.TextOut(x+b, y+50+10*(c), w);
	w.Format("%8.0f", T_demand[3]);
	pDC.TextOut(x+b, y+50+12*(c), w);	
	w.Format("%8.0f", TDD[3]);
	pDC.TextOut(x+b, y+50+13*(c), w);

	pDC.SetTextAlign(TA_LEFT);
	dndc.Format("-----------------------------------------------------------------------------------------------");
	pDC.TextOut(650, 520, dndc);
	
#ifdef WIZARD	
		dndc.Format("Crop production: %s county in %s, %s, year %d (Unit: kg dry matter/ha)", SelectedCounty, SelectedState, Crop_Name[3], year);
#else
		dndc.Format("Crop 3: %s    %s - %s", Crop_Name[3], Dates[PlantDay[3]], Dates[HarvestDay[3]]);
#endif 

	pDC.TextOut(150, 520, dndc);
*/	
	
}

void WizardResult::OnWater() 
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

	pDC.FillSolidRect(20, 10, 1300, 740, RGB(120,120,150));

	int r=30;
	int t=1.0;
	int z=450;
	
	int c1=150,c2=250,c3=0;
	int b1=150,b2=50,b3=0;

	float WR=0.3;

	int L_rain = (int)(yr_rain*WR);
	int L_irri = (int)(yr_irri*WR);	

	int L_T = (int)(yr_trans*WR);
	int L_SE = (int)(yr_soil_ev*WR);
	int L_WE = (int)(yr_pond_ev*WR);
	int L_leach = (int)(yr_leach_water*WR);
	int L_runoff = (int)(yr_runoff*WR);
	int L_GWsuply = (int)(yr_GWsuply*WR);

	float dW=(yr_rain+yr_irri+yr_GWsuply)-(yr_trans+yr_soil_ev+yr_pond_ev+yr_leach_water+yr_runoff);

	int L_dW = (int)dW;//(L_rain+L_irri)-(L_T+L_SE+L_WE+L_leach+L_runoff);

	pDC.FillSolidRect(z-L_rain, 150, L_rain, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_irri, 200, L_irri, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z-L_GWsuply, 250, L_GWsuply, r, RGB(c1,c2,c3));

	pDC.FillSolidRect(z, 300, L_T, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 350, L_SE, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 400, L_WE, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 450, L_leach, r, RGB(c1,c2,c3));
	pDC.FillSolidRect(z, 500, L_runoff, r, RGB(c1,c2,c3));

	if(L_dW>0) pDC.FillSolidRect(z, 600, -L_dW, r, RGB(250,200,0));
	else pDC.FillSolidRect(z-L_dW, 600, L_dW, r, RGB(200,0,0));


	int x=900, y=50, c=50, b=370;
	CString w;
	
	//w.Format("( Source data file: \%s )", rcd);
	//pDC.TextOut(350, 90, w);

	pDC.SetTextAlign(TA_LEFT);
	pDC.SetTextColor(RGB(255,255,255));
	
	w.Format("Precipitation");
	pDC.TextOut(x, y+50+1*(c), w);
	w.Format("Irrigation");
	pDC.TextOut(x, y+50+2*(c), w);
	w.Format("Groundwater suply");
	pDC.TextOut(x, y+50+3*(c), w);

	w.Format("Transpiration");
	pDC.TextOut(x, y+50+4*(c), w);
	w.Format("Soil evaporation");
	pDC.TextOut(x, y+50+5*(c), w);
		w.Format("Surface evaporation");
	pDC.TextOut(x, y+50+6*(c), w);
	w.Format("Leaching");
	pDC.TextOut(x, y+50+7*(c), w);
	w.Format("Runoff");
	pDC.TextOut(x, y+50+8*(c), w);
	//w.Format("Root respiration");
	//pDC.TextOut(x, y+50+8*(c), w);
	w.Format("Change in soil water storage");
	pDC.TextOut(x, y+50+10*(c), w);

	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));
		
	w.Format("%8.0f", yr_rain);
	pDC.TextOut(x+b, y+50+1*(c), w);	
	w.Format("%8.0f", yr_irri);
	pDC.TextOut(x+b, y+50+2*(c), w);
	w.Format("%8.0f", yr_GWsuply);
	pDC.TextOut(x+b, y+50+3*(c), w);
	
	w.Format("%8.0f", yr_trans);
	pDC.TextOut(x+b, y+50+4*(c), w);	
	w.Format("%8.0f", yr_soil_ev);
	pDC.TextOut(x+b, y+50+5*(c), w);
	w.Format("%8.0f", yr_pond_ev);
	pDC.TextOut(x+b, y+50+6*(c), w);	
	w.Format("%8.0f", yr_leach_water);
	pDC.TextOut(x+b, y+50+7*(c), w);	
	w.Format("%8.0f", yr_runoff);
	pDC.TextOut(x+b, y+50+8*(c), w);	
	//w.Format("%8.1f", rootCO2);
	//pDC.TextOut(x+b, y+50+8*(c), w);
	w.Format("%8.0f", dW);
	pDC.TextOut(x+b, y+50+10*(c), w);

	//CPen *pOldPen = NULL;
	CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = pDC.SelectObject(&Pen1);	
	
	pDC.MoveTo(z, 130);
	pDC.LineTo(z, 650);

	pDC.SelectObject(pOldPen);
	Pen1.DeleteObject();	

	CFont hNewFont;
	TEXTMETRIC tm;
	CString dndc;
	
#ifdef WIZARD	
	dndc.Format("Water balance: %s county in %s, %s, year %d (Unit: mm water)", SelectedCounty, SelectedState, Crop_Name[1], year);
#else
	dndc.Format("Water balance (mm): Site: %s   Year %d", Site_Name, year);
#endif

	hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_LEFT);
		pDC.TextOut(50, 40, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("Water outputs");
	hNewFont.CreateFont(28,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(z+150, 100, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("Water inputs");
	hNewFont.CreateFont(28,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(z-150, 100, dndc);
		
		hNewFont.DeleteObject();	
}

void WizardResult::OnGwp() 
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

	pDC.FillSolidRect(20, 10, 1300, 740, RGB(120,120,150));	

	C_CO2 = haha * (-dSOC) * 0.001;
	C_N2O = haha * (N2O) * 0.001;
	C_CH4 = haha * (CH4) * 0.001;

	//GWP_CO2 = C_CO2 / 12 * 44 * 0.000001;
	//GWP_N2O = C_N2O / 28 * 44 * 310 * 0.000001;
	//GWP_CH4 = C_CH4 / 12 * 16 * 21 * 0.000001;
	
	GWP_CO2 = -dSOC / 12 * 44;
	GWP_N2O = N2O / 28 * 44 * 310;
	GWP_CH4 = CH4 / 12 * 16 * 21;

	NetGWP = GWP_CO2 + GWP_N2O + GWP_CH4;

	//GWP = CO2i / 12 * 44 + N2Oi / 28 * 44 * 310  + CH4i / 12 * 16 * 21

	CBrush Brush1(RGB(120,120,150));
	//pDC.FillRect(rectClient, &Brush1);
	Brush1.DeleteObject();

	CString data;

	//pDC.SetTextColor(RGB(0,0,0));
	//pDC.SetTextAlign(TA_RIGHT);
		CFont hNewFont;
	
		CString dndc;


	pDC.SetTextColor(RGB(0,0,0));
		hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);

		pDC.SetTextAlign(TA_RIGHT);

	int x=650,y=270;
	data.Format("%5.0f", -dSOC);
	pDC.TextOut(x+0*y, 250, data);
	data.Format("%5.1f", N2O);
	pDC.TextOut(x+1*y, 250, data);
	data.Format("%5.0f", CH4);
	pDC.TextOut(x+2*y, 250, data);

	data.Format("%5.0f", GWP_CO2);
	pDC.TextOut(x+0*y, 350, data);
	data.Format("%5.0f", GWP_N2O);
	pDC.TextOut(x+1*y, 350, data);
	data.Format("%5.0f", GWP_CH4);
	pDC.TextOut(x+2*y, 350, data);

/*	data.Format("%5.3f", GWP_CO2);
	pDC.TextOut(x+0*y, 450, data);
	data.Format("%5.3f", GWP_N2O);
	pDC.TextOut(x+1*y, 450, data);
	data.Format("%5.3f", GWP_CH4);
	pDC.TextOut(x+2*y, 450, data);*/

	data.Format("%5.0f", NetGWP);
	pDC.TextOut(x+0*y, 550, data);

	hNewFont.DeleteObject();


		
		pDC.SetTextColor(RGB(255,255,255));
		hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);

		pDC.SetTextAlign(TA_LEFT);
#ifdef WIZARD
		dndc.Format("%s county in %s, %s, Year %d", SelectedCounty, SelectedState, Crop_Name[1], year);		
#else
		dndc.Format("Greenhouse Gases: Site: %s  Year: %d", Site_Name, year);		
#endif

		pDC.TextOut(50, 30, dndc);

		pDC.SetTextAlign(TA_LEFT);
		dndc.Format("Greenhouse gas                            dSOC                      N2O                   CH4");		
		pDC.TextOut(50, 150, dndc);	
		dndc.Format("                                                      kg C/ha                  kg N/ha              kg C/ha");		
		pDC.TextOut(50, 290, dndc);

		//dndc.Format("gas");		
		//pDC.TextOut(50, 170, dndc);			

		dndc.Format("Flux rate");		
		pDC.TextOut(50, 250, dndc);

		dndc.Format("GWP");		
		pDC.TextOut(50, 350, dndc);

		//dndc.Format("GWP");		
		//pDC.TextOut(50, 450, dndc);

		dndc.Format("Net GWP");		
		pDC.TextOut(50, 550, dndc);

		hNewFont.DeleteObject();


		pDC.SetTextColor(RGB(255,255,255));
		hNewFont.CreateFont(30,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);

		pDC.SetTextAlign(TA_LEFT);
		
		dndc.Format("                                                      kg CO2-equivalent/ha");		
		pDC.TextOut(50, 390, dndc);

		//dndc.Format("Tg CO2 emission");		
		//pDC.TextOut(50, 490, dndc);
		//dndc.Format("equivalent");		
		//pDC.TextOut(50, 510, dndc);
		dndc.Format("                                                      kg CO2-equivalent/ha");		
		pDC.TextOut(50, 590, dndc);

		hNewFont.DeleteObject();

		int a=380,b=150,c=130,aa=200, cc=100;
	//CPen *pOldPen = NULL;
	CPen  Pen1(PS_SOLID, 1, RGB(200,200,250));
	pOldPen = pDC.SelectObject(&Pen1);	
	
	for(int i=0; i<=5; i++)
	{
		if(i!=4)
		{
			pDC.MoveTo(50, c+i*cc);
			pDC.LineTo(1300, c+i*cc);
		}

		//pDC.MoveTo(a+i*aa, 130);
		//pDC.LineTo(a+i*aa, 530);
	}

	pDC.SelectObject(pOldPen);
	Pen1.DeleteObject();

	

	
}

void WizardResult::OnSelchangeWizardYear() 
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

	pDC.FillSolidRect(20, 10, 1300, 740, RGB(120,120,150));

	CFont hNewFont;
	TEXTMETRIC tm;
	CString dndc;
	dndc.Format("Several major outputs from the simulation can be reviewed here.");

	hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(650, 240, dndc);
		
		hNewFont.DeleteObject();

		dndc.Format("The detailed annual and daily results are recorded at");

	hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(650, 280, dndc);
		
		hNewFont.DeleteObject();

		dndc.Format("%s\\Record\\Site\\.", OUTPUT);

	hNewFont.CreateFont(32,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		pDC.SelectObject(&hNewFont);
		pDC.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		pDC.GetTextMetrics(&tm);
		pDC.SetTextAlign(TA_CENTER);
		pDC.TextOut(650, 400, dndc);
		
		hNewFont.DeleteObject();
	UpdateData(TRUE);
	year = m_WizardYear.GetCurSel()+1;

	read_summary(year);


			
			leachHumN = 0.0;
			weedN = 0.0;
			//weedupN = 0.0;


			
}

void WizardResult::read_summary(int YR)
{

	FILE* RCD;
		int ResultYr=1, IDID;
		float sd, ttoo, clay, soil_ph;
		char WW[600];
		
		rcd.Format("%s\\Inter\\Summary-%d", OUTPUT, YR);
			RCD = fopen(rcd, "r");
			if(RCD==NULL) 
			{
				CString mess;
				mess.Format("Can not open file %s", rcd);
				AfxMessageBox(mess);
				exit(0);
			}

			fscanf(RCD, "%d", &IDID); fgets(WW, 300, RCD);
			fscanf(RCD, "%s", Site_Name); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_avet); fgets(WW, 300, RCD);
			
			fscanf(RCD, "%f", &sd); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &ttoo); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &clay); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &soil_ph); fgets(WW, 300, RCD);
			fscanf(RCD, "%s", Crop_Name[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%s", Crop_Name[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%s", Crop_Name[3]); fgets(WW, 300, RCD);
						
			fscanf(RCD, "%f", &irriIndex); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_addmc); fgets(WW, 300, RCD);

			fscanf(RCD, "%f", &rainN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &fertN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &manureN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &irriN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &rootN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &litterN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &SoilFixN); fgets(WW, 300, RCD);
			
			fscanf(RCD, "%f", &fixN[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &fixN[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &fixN[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &uptakeSoilN[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &uptakeSoilN[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &uptakeSoilN[3]); fgets(WW, 300, RCD);
		
			fscanf(RCD, "%f", &runoffN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &leachN); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &NH3); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &N2O); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &NO); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &N2); fgets(WW, 300, RCD);
			//fscanf(RCD, "%f", &weedupN); fgets(WW, 300, RCD);
			
			fscanf(RCD, "%f", &rootC); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &litterC); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &rootDOC); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &manureC); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &soilCO2); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &CH4); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &leachHumC); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &dSOC); fgets(WW, 300, RCD);

			fscanf(RCD, "%f", &yr_rain);	 fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_irri); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &CropTrans[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &CropTrans[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &CropTrans[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_soil_ev); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_pond_ev); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_runoff); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_leach_water); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &yr_GWsuply); fgets(WW, 300, RCD);
			
			fscanf(RCD, "%f", &ProdC[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &ProdC[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &ProdC[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &prograin[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &prograin[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &prograin[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &prostraw[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &prostraw[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &prostraw[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &proroot[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &proroot[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &proroot[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &CropN[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &CropN[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &CropN[3]); fgets(WW, 300, RCD);
			
			fscanf(RCD, "%f", &Optimum_grain[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Optimum_grain[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Optimum_grain[3]); fgets(WW, 300, RCD);

			fscanf(RCD, "%f", &Optimum_straw[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Optimum_straw[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Optimum_straw[3]); fgets(WW, 300, RCD);

			fscanf(RCD, "%f", &Optimum_root[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Optimum_root[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Optimum_root[3]); fgets(WW, 300, RCD);


			fscanf(RCD, "%f", &Water_demand[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Water_demand[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &Water_demand[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &N_demand[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &N_demand[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &N_demand[3]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &T_demand[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &T_demand[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &T_demand[3]); fgets(WW, 300, RCD);

			fscanf(RCD, "%f", &TDD[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &TDD[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%f", &TDD[3]); fgets(WW, 300, RCD);

			fscanf(RCD, "%d %d", &PlantDay[1], &HarvestDay[1]); fgets(WW, 300, RCD);
			fscanf(RCD, "%d %d", &PlantDay[2], &HarvestDay[2]); fgets(WW, 300, RCD);
			fscanf(RCD, "%d %d", &PlantDay[3], &HarvestDay[3]); fgets(WW, 300, RCD);

		
			fclose(RCD);

			uptakeN=uptakeSoilN[1]+uptakeSoilN[2]+uptakeSoilN[3];
			yr_trans=CropTrans[1]+CropTrans[2]+CropTrans[3];
}
