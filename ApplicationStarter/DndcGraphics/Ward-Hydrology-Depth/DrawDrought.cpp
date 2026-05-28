// DrawDrought.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "DrawDrought.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
CString CropName[5]={"","Corn","Wheat","Rice","Soybean"};
/////////////////////////////////////////////////////////////////////////////
// DrawDrought dialog


DrawDrought::DrawDrought(CWnd* pParent /*=NULL*/)
	: CDialog(DrawDrought::IDD, pParent)
{
	//{{AFX_DATA_INIT(DrawDrought)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DrawDrought::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DrawDrought)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DrawDrought, CDialog)
	//{{AFX_MSG_MAP(DrawDrought)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DrawDrought message handlers

BOOL DrawDrought::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

//AfxMessageBox("HERE");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DrawDrought::OnOK() 
{
	// TODO: Add extra validation here
	int CountyID, YieldCrop, YieldYear, YieldToday, YieldMonth, YieldDay;
	float HighYield=0.0, MidYield=0.0, LowYield=0.0;
	char CountyName[100];
	CString YF;
	FILE* yf;
	YF.Format("%s\\YieldPrediction", INTER);
	yf=fopen(YF, "r");
	if(yf==NULL) note(0,YF);

	fscanf(yf, "%d  %d  %d  %d  %s %d %d", &CountyID, &YieldCrop, &YieldYear, &YieldToday, CountyName, &YieldMonth, &YieldDay);
	fclose(yf);

	int i, jday;
	double leaf1[366]={0.0,0.0}, stem1[366]={0.0,0.0}, root1[366]={0.0,0.0}, grain1[366]={0.0,0.0};
	double leaf2[366]={0.0,0.0}, stem2[366]={0.0,0.0}, root2[366]={0.0,0.0}, grain2[366]={0.0,0.0};
	double leaf3[366]={0.0,0.0}, stem3[366]={0.0,0.0}, root3[366]={0.0,0.0}, grain3[366]={0.0,0.0};
    char DryYear[120], WetYear[120], MidYear[120], www[300], js[50];
	FILE *DY, *WY, *MY;

    sprintf(DryYear, "%s\\Record\\Site\\Day_FieldCrop_2_dry.csv", OUTPUT);
	sprintf(WetYear, "%s\\Record\\Site\\Day_FieldCrop_2_wet.csv", OUTPUT);
	sprintf(MidYear, "%s\\Record\\Site\\Day_FieldCrop_2_mid.csv", OUTPUT);

    DY = fopen(DryYear, "r");
    if(DY==NULL) note(0, DryYear);
	WY = fopen(WetYear, "r");
    if(WY==NULL) note(0, WetYear);
	MY = fopen(MidYear, "r");
    if(MY==NULL) note(0, MidYear);

	fgets(www, 300, DY);
	fgets(www, 300, DY);
	fgets(www, 300, DY);
	fgets(www, 300, DY);
	fgets(www, 300, DY);
	fgets(www, 300, WY);
	fgets(www, 300, WY);
	fgets(www, 300, WY);
	fgets(www, 300, WY);
	fgets(www, 300, WY);
	fgets(www, 300, MY);
	fgets(www, 300, MY);
	fgets(www, 300, MY);
	fgets(www, 300, MY);
	fgets(www, 300, MY);

	for(i=1; i<=365; i++)
	{
		fscanf(DY, "%d %s", &jday, js);//dry year
		fscanf(DY, "%lf %s %lf %s %lf %s %lf %s", &leaf1[jday], js, &stem1[jday], js, &root1[jday], js, &grain1[jday], js);
		fgets(www, 300, DY);
		fgets(www, 300, DY);

		fscanf(WY, "%d %s", &jday, js);//wet year
		fscanf(WY, "%lf %s %lf %s %lf %s %lf %s", &leaf2[jday], js, &stem2[jday], js, &root2[jday], js, &grain2[jday], js);
		fgets(www, 300, WY);
		fgets(www, 300, WY);

		fscanf(MY, "%d %s", &jday, js);//mid year
		fscanf(MY, "%lf %s %lf %s %lf %s %lf %s", &leaf3[jday], js, &stem3[jday], js, &root3[jday], js, &grain3[jday], js);
		fgets(www, 300, MY);
		fgets(www, 300, MY);

		LowYield = max(LowYield, grain1[jday]);
		HighYield = max(HighYield, grain2[jday]);
		MidYield = max(MidYield, grain3[jday]);
	}

	fclose(DY);
	fclose(WY);
	fclose(MY);

	///////////////////////////////////////////////////////////////////////////////////////////
	CString w;
	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1900, 3700);
	pDC.SetBkMode(TRANSPARENT);
	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);

	pDC.FillSolidRect(20, 10, 1600, 850, RGB(200,200,200));

	int lv=1, hv=365, be=4, ini=700, k1=0, k2=0, k3=0, k4=0;;
	int OldLeaf1, OldLeaf2, OldLeaf3,OldLeaf7,jp=50;

	OldLeaf1 = ini;
	OldLeaf2 = ini;
	k2 = lv*be+jp;
	k4 = lv*be+jp;

	CPen *pOldPen = NULL;	
	
	CPen  Pen5(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = pDC.SelectObject(&Pen5);

	k1=50;
	int aa=140;
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));
	//pDC.SetTextJustification(50,50);

	for(i=0; i<=14; i++)
	{
		pDC.MoveTo(k1, aa+i*40);
		pDC.LineTo(k1+1400, aa+i*40);

		int YY=int((5600-i*400)*2.5);
		w.Format("%d", YY);
		pDC.TextOut(k1+70, aa-25+i*40, w);

		if(i==0) 
		{
			w.Format("kg C/ha");
			pDC.TextOut(k1+200, aa-25+i*40, w);
		}
	}

	for(i=lv; i<=hv; i++)
	{
		if(i%20==0)
		{
		k1 = (i-lv) * be + jp;

		w.Format("|");
		pDC.TextOut(k1+5, 675, w);
		w.Format("%d", i);
		pDC.TextOut(k1+5, 720, w);
		}
	}

	w.Format("Crop biomass");
	pDC.TextOut(230, 80, w);

	w.Format("Day of year");
	pDC.TextOut(900, 750, w);

	pDC.SelectObject(pOldPen);
	Pen5.DeleteObject();

	CPen  Pen0(PS_SOLID, 3, RGB(150,150,50));//min shoot
	pOldPen = pDC.SelectObject(&Pen0);

	for(i=lv; i<=hv; i++)
	{
		int IntLeaf = ini - (int)((leaf1[i]+stem1[i]) * 0.1);
		k1 = (i-lv) * be + jp;
		pDC.MoveTo(k2, OldLeaf1);
		pDC.LineTo(k1, IntLeaf);

		k2 = k1;
		OldLeaf1 = IntLeaf; 
	}

	pDC.SelectObject(pOldPen);
	Pen0.DeleteObject();

	CPen  Pen1(PS_SOLID, 3, RGB(100,100,50));//max shoot
	pOldPen = pDC.SelectObject(&Pen1);

	for(i=lv; i<=hv; i++)
	{
		int IntLeaf = ini - (int)((leaf2[i]+stem2[i]) * 0.1);
		k3 = (i-lv) * be + jp;
		pDC.MoveTo(k4, OldLeaf2);
		pDC.LineTo(k3, IntLeaf);

		k4 = k3;
		OldLeaf2 = IntLeaf; 
	}

	pDC.SelectObject(pOldPen);
	Pen1.DeleteObject();

	CPen  Pen6(PS_SOLID, 3, RGB(20,100,150));//mid shoot
	pOldPen = pDC.SelectObject(&Pen6);

	for(i=lv; i<=hv; i++)
	{
		int IntLeaf = ini - (int)((leaf3[i]+stem3[i]) * 0.1);
		k3 = (i-lv) * be + jp;
		pDC.MoveTo(k4, OldLeaf3);
		pDC.LineTo(k3, IntLeaf);

		k4 = k3;
		OldLeaf3 = IntLeaf; 
	}

	pDC.SelectObject(pOldPen);
	Pen6.DeleteObject();

	////////////////////////////////////////	
	CPen  Pen3(PS_SOLID, 3, RGB(250,230,10));//min yield
	pOldPen = pDC.SelectObject(&Pen3);

	for(i=lv; i<=hv; i++)
	{
		int IntLeaf = ini - (int)((grain1[i]) * 0.1);
		k1 = (i-lv) * be + jp;
		pDC.MoveTo(k2, OldLeaf1);
		pDC.LineTo(k1, IntLeaf);

		k2 = k1;
		OldLeaf1 = IntLeaf; 
	}

	pDC.SelectObject(pOldPen);
	Pen3.DeleteObject();

	CPen  Pen4(PS_SOLID, 3, RGB(250,120,10));//max yield
	pOldPen = pDC.SelectObject(&Pen4);

	for(i=lv; i<=hv; i++)
	{
		int IntLeaf = ini - (int)((grain2[i]) * 0.1);
		k3 = (i-lv) * be + jp;
		pDC.MoveTo(k4, OldLeaf2);
		pDC.LineTo(k3, IntLeaf);

		k4 = k3;
		OldLeaf2 = IntLeaf; 
	}

	pDC.SelectObject(pOldPen);
	Pen4.DeleteObject();

	CPen  Pen7(PS_SOLID, 3, RGB(200,20,50));//mid yield
	pOldPen = pDC.SelectObject(&Pen7);

	for(i=lv; i<=hv; i++)
	{
		int IntLeaf = ini - (int)((grain3[i]) * 0.1);
		k3 = (i-lv) * be + jp;
		pDC.MoveTo(k4, OldLeaf7);
		pDC.LineTo(k3, IntLeaf);

		k4 = k3;
		OldLeaf7 = IntLeaf; 
	}

	pDC.SelectObject(pOldPen);
	Pen7.DeleteObject();

	///today
	int today = (YieldToday-lv)*be+jp;
	pDC.FillSolidRect(today, 700, 5, -600, RGB(250,250,255));

	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(255,255,255));
	
	w.Format("Real climate");
	pDC.TextOut(today-30, 100, w);

	pDC.SetTextAlign(TA_LEFT);
	w.Format("Default climate");
	pDC.TextOut(today+30, 100, w);

	pDC.FillSolidRect(1370, 200, 50, 3, RGB(250,120,10));
	pDC.FillSolidRect(1370, 230, 50, 3, RGB(200,20,50));
	pDC.FillSolidRect(1370, 260, 50, 3, RGB(250,230,10));
	pDC.FillSolidRect(1370, 290, 50, 3, RGB(100,100,50));
	pDC.FillSolidRect(1370, 320, 50, 3, RGB(20,100,150));
	pDC.FillSolidRect(1370, 350, 50, 3, RGB(150,150,50));

	pDC.SetTextColor(RGB(5,5,5));

	w.Format("Area: %s (%d)", CountyName, CountyID);
	pDC.TextOut(1650, 150, w);
	w.Format("Crop: %s", CropName[YieldCrop]);
	pDC.TextOut(1650, 180, w);
	w.Format("Predicting date: %d/%2d/%2d", YieldYear, YieldMonth, YieldDay);
	pDC.TextOut(1650, 210, w);
	w.Format("Predicted yield (kg DM/ha)");
	pDC.TextOut(1650, 240, w);

	w.Format("Wet scenario: %6.0f", HighYield/0.4);
	pDC.TextOut(1650, 270, w);
	w.Format("Mid scenario:  %6.0f", MidYield/0.4);
	pDC.TextOut(1650, 300, w);
	w.Format("Dry scenario:  %6.0f", LowYield/0.4);
	pDC.TextOut(1650, 330, w);
	
	w.Format("Grain - wet");
	pDC.TextOut(1440, 190, w);
	w.Format("Grain - mid");
	pDC.TextOut(1440, 220, w);
	w.Format("Grain - dry");
	pDC.TextOut(1440, 250, w);
	w.Format("Shoot - wet");
	pDC.TextOut(1440, 280, w);
	w.Format("Shoot - mid");
	pDC.TextOut(1440, 310, w);
	w.Format("Shoot - dry");
	pDC.TextOut(1440, 340, w);

	


	//AfxMessageBox("HERE");

/*
	CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = pDC.SelectObject(&Pen1);	
	
	pDC.MoveTo(z, 130);
	pDC.LineTo(z, 650);

	pDC.SelectObject(pOldPen);
	Pen1.DeleteObject();

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
*/
	//CDialog::OnOK();
}
