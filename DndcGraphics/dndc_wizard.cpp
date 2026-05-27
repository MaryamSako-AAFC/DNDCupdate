#include "stdafx.h"
#include "RunPaths.h"
#include "dndc71.h"
#include "graphexDoc.h"
#include "graphexView.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include "../DNDCgo.h"
#include "WizardResult.h"

#define _USE_32BIT_TIME_T

int ww1=200,ww2=200,ww3=200;
int qq1=0,qq2=30,qq3=0;
void landuse_color(float ha, int *c1, int *c2, int *c3);
float find_ha(long int CountyID, int cropID);

int WizardRandomGenerator(int ss);

void CGraphexView::County_data(int WizardCountyID, int domain)
{
	char MM[500];
	int county_ID4;
	
	int i,landuse, crop_number, crop_ID[5];
	float crop_ha[90];

	CString RF;
	FILE *ref;

	RF.Format("%s\\Database\\USA\\GIS\\usa4_%d", ROOTDIR, stateID);
	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}

	fgets(MM, 500, ref);
	fgets(MM, 500, ref);

	CString CropCode;
	FILE *CC;

	CropCode.Format("%s\\Inter\\RegionCropCode", OUTPUT);
	CC = fopen(CropCode, "w");
	if (CC==NULL)
	{
		char err[120];
		sprintf(err, "Can not create file %s", CropCode);
		AfxMessageBox(err);
		exit(0); 
	}

	fscanf(ref, "%d", &crop_number);
	fprintf(CC, "%d\n", crop_number);

	for(i=1; i<=crop_number; i++)
	{
		fscanf(ref, "%d", &crop_ID[i]);
		fprintf(CC, "%d\n", crop_ID[i]);
	}

	fclose(CC);

	for(i=1; i<= 10000; i++)
	{

		if(fscanf(ref, "%d", &county_ID4)!=1)
		{
			CString note;
			note.Format("Can not find crop census data for county %d", WizardCountyID);
			AfxMessageBox(note);
			exit(0);
		}

		if(county_ID4==WizardCountyID)
		{
			for(landuse=1; landuse<=crop_number; landuse++)
			{
				fscanf(ref, "%f", &crop_ha[landuse]);
			}
			break;
		}
		else
		{
			fgets(MM, 300, ref);
		}
			
	}
	fclose(ref);

	char Sname[200], Cname[200];
	int CID;
	float logi, lati;

	RF.Format("%s\\Database\\USA\\GIS\\usa1_%d", ROOTDIR, stateID);
	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}

	for(;;)
	{
		fscanf(ref, "%d %s %s %f %f", &CID, Sname, Cname, &logi, &lati);
		if(CID==WizardCountyID) 
			break;

	}


	CString IDfile;
	FILE *fid;
	
	IDfile.Format("%s\\Inter\\WizardSite.txt", OUTPUT);
		fid = fopen(IDfile, "w");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(fid, "%d  %d\n", stateID, WizardCountyID);
		fprintf(fid, "%s  %s\n", Sname, Cname);
		for(i=1; i<=crop_number; i++)
			fprintf(fid, "%d  %f\n", crop_ID[i], crop_ha[i]);

		fclose(fid);
	
/*	else if(stateID==6)
	{
		CString IDfile;
		FILE *fid;
		
		IDfile.Format("%s\\Inter\\WizardSite.txt", OUTPUT);
		fid = fopen(IDfile, "w");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(fid, "%d  %ld\n", stateID, County_ID);
		
		fclose(fid);

	}*/
}


void CGraphexView::DrawCbalance(CGraphexDoc *pDoc)
{
	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (5,10); 
	art.SetViewportExt(950, 1450);
	
	CBrush Brush1(RGB(120,120,150));
	art.FillRect(rectClient, &Brush1);
	Brush1.DeleteObject();

	//art.FillSolidRect(20, 10, 980, 620, RGB(120,120,150));


	int r=30;
	int t=1;
	int z=250;
	
	int c1=150,c2=250,c3=0;
	int b1=150,b2=50,b3=0;
	
	//int L_SOC1 = (int)(SOC1 /400.0);
	//int L_SOC2 = (int)(SOC2 /400.0);
	//int L_dC = (int)((SOC2-SOC1)/20);
	int L_manureC = (int)(manureC/20);
	int L_litterC = (int)(litterC/20);
	int L_rootC = (int)(rootC/20);
	int L_weedC = (int)(weedC/20);
	int L_soilCO2 = (int)(soilCO2/20);
	int L_leachC = (int)(leachHumC/20);
	int L_CH4 = (int)(CH4/20);
	int L_rootCO2 = (int)(rootCO2/20);

	//dC = (manureC+litterC+rootC+weedC)-(soilCO2+leachHumC+CH4*0.2);
	//int L_dC = (int)(dC/20);
	int L_dC = (int)(dSOC/20.0);

	art.FillSolidRect(z-L_manureC, 150, L_manureC, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_litterC, 200, L_litterC, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_rootC, 250, L_rootC, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_weedC, 300, L_weedC, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 350, L_soilCO2, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 400, L_leachC, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 450, L_CH4, r, RGB(c1,c2,c3));
	//art.FillSolidRect(z, 500, L_rootCO2, r, RGB(c1,c2,c3));
	if(L_dC>0) art.FillSolidRect(z, 550, -L_dC, r, RGB(250,200,0));
	else art.FillSolidRect(z-L_dC, 550, L_dC, r, RGB(200,0,0));


	int x=600, y=50, c=50, b=300;
	CString w;
	
	//w.Format("( Source data file: \%s )", rcd);
	//art.TextOut(350, 90, w);

	art.SetTextAlign(TA_LEFT);
	art.SetTextColor(RGB(255,255,255));
	
	w.Format("Manure C input");
	art.TextOut(x, y+50+1*(c), w);
	w.Format("Crop stub C input");
	art.TextOut(x, y+50+2*(c), w);
	w.Format("Crop root C input");
	art.TextOut(x, y+50+3*(c), w);
	w.Format("Weeds C input");
	art.TextOut(x, y+50+4*(c), w);
		w.Format("Soil CO2 flux");
	art.TextOut(x, y+50+5*(c), w);
	w.Format("DOC leaching");
	art.TextOut(x, y+50+6*(c), w);
	w.Format("CH4 emission");
	art.TextOut(x, y+50+7*(c), w);
	//w.Format("Root respiration");
	//art.TextOut(x, y+50+8*(c), w);
	w.Format("Net change in soil C");
	art.TextOut(x, y+50+9*(c), w);

	art.SetTextAlign(TA_RIGHT);
	art.SetTextColor(RGB(0,0,0));
		
	w.Format("%8.1f", manureC);
	art.TextOut(x+b, y+50+1*(c), w);	
	w.Format("%8.1f", litterC);
	art.TextOut(x+b, y+50+2*(c), w);	
	w.Format("%8.1f", rootC);
	art.TextOut(x+b, y+50+3*(c), w);	
	w.Format("%8.1f", weedC);
	art.TextOut(x+b, y+50+4*(c), w);
	w.Format("%8.1f", soilCO2);
	art.TextOut(x+b, y+50+5*(c), w);	
	w.Format("%8.1f", leachHumC);
	art.TextOut(x+b, y+50+6*(c), w);	
	w.Format("%8.1f", CH4);
	art.TextOut(x+b, y+50+7*(c), w);	
	//w.Format("%8.1f", rootCO2);
	//art.TextOut(x+b, y+50+8*(c), w);
	w.Format("%8.1f", dSOC);
	art.TextOut(x+b, y+50+9*(c), w);

	

	CPen *pOldPen = NULL;
	CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = art.SelectObject(&Pen1);	
	
	art.MoveTo(250, 130);
	art.LineTo(250, 650);


	art.SelectObject(pOldPen);
	Pen1.DeleteObject();
	

	CFont hNewFont;
	TEXTMETRIC tm;
	CString dndc;
	
	dndc.Format("Soil C balance for %s land in %s for year %d (kg C/ha)", CropName, Site_Name, year);

	hNewFont.CreateFont(45,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextAlign(TA_LEFT);
		art.TextOut(50, 40, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("C inputs");
	hNewFont.CreateFont(40,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextAlign(TA_LEFT);
		art.TextOut(100, 100, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("C outputs");
	hNewFont.CreateFont(40,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextAlign(TA_LEFT);
		art.TextOut(300, 100, dndc);
		
		hNewFont.DeleteObject();


	//AfxMessageBox("");
	//exit(0);
}


void CGraphexView::DrawNbalance(CGraphexDoc *pDoc)
{

	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (5,330); 
	art.SetViewportExt(950, 1450);
	

	CBrush Brush1(RGB(120,120,150));
	art.FillRect(rectClient, &Brush1);
	Brush1.DeleteObject();

	//art.FillSolidRect(20, 10, 980, 620, RGB(150,150,0));

	int t=1;
	int z=250;
	int r=20;
	
	//int L_SON1 = (int)(SON1 /400.0);
	//int L_SON2 = (int)(SON2 /400.0);
	//int L_SIN1 = (int)(SIN1 /400.0);
	//int L_SIN2 = (int)(SIN2 /400.0);
	

	int L_manureN = (int)(manureN/t);
	int L_litterN = (int)(litterN/t);
	int L_rootN = (int)(rootN/t);
	int L_weedN = (int)(weedN/t);
	int L_rainN = (int)(rainN/t);
	int L_fertN = (int)(fertN/t);
	int L_fixN = (int)(fixN/t);

	int L_leachHumN = (int)(leachHumN/t);
	int L_upN = (int)(uptakeN/t);
	int L_weedupN = (int)(weedupN/t);
	int L_leachN = (int)(leachN/t);
	int L_runoffN = 0;//(int)(runoffN/t);
	int L_NH3 = (int)(NH3/t);
	int L_N2O = (int)(N2O/t);	
	int L_NO = (int)(NO/t);
	int L_N2 = (int)(N2/t);
	//int L_NO2 = (int)(NO2/t);

	float dN =(manureN+litterN+rootN+rainN+fertN)-
				(leachHumN+uptakeN+weedupN+leachN+runoffN+NH3+N2O+NO+N2);

	int L_dN = (int)(dN/t);


	int c1=150,c2=250,c3=0;
	int b1=150,b2=50,b3=0;

	//art.FillSolidRect(50, 50, L_SIN1, 10, RGB(150,150,0));
	//art.FillSolidRect(50, 100, L_SIN2, 10, RGB(150,150,0));
	

	art.FillSolidRect(z-L_manureN, 150, L_manureN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_litterN, 180, L_litterN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_rootN, 210, L_rootN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_weedN, 240, L_weedN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_rainN, 270, L_rainN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_fertN, 300, L_fertN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z-L_fixN, 330, L_fixN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 360, L_leachN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 390, L_runoffN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 420, L_upN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 450, L_weedupN, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 480, L_NH3, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 510, L_N2O, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 540, L_NO, r, RGB(c1,c2,c3));
	art.FillSolidRect(z, 570, L_N2, r, RGB(c1,c2,c3));
	//art.FillSolidRect(z, 600, L_NO2, r, RGB(c1,c2,c3));
	if(L_dN>0) art.FillSolidRect(z, 600, -L_dN, r, RGB(250,200,0));
	else art.FillSolidRect(z-L_dN, 600, L_dN, r, RGB(200,0,0));

	
	int x=600, y=55, c=30, b=300;
	CString w;

	art.SetTextAlign(TA_LEFT);
	art.SetTextColor(RGB(255,255,255));
	
	w.Format("Manure N input");
	art.TextOut(x, y+50+1*(c), w);
	w.Format("Crop stub N input");
	art.TextOut(x, y+50+2*(c), w);
		w.Format("Crop root N input");
	art.TextOut(x, y+50+3*(c), w);
	w.Format("Weeds N input");
	art.TextOut(x, y+50+4*(c), w);
	w.Format("Atmospheric N deposit");
	art.TextOut(x, y+50+5*(c), w);
	w.Format("Fertilizer N input");
	art.TextOut(x, y+50+6*(c), w);
	w.Format("N fixation");
	art.TextOut(x, y+50+7*(c), w);
	w.Format("N leaching");
	art.TextOut(x, y+50+8*(c), w);
	w.Format("N runoff");
	art.TextOut(x, y+50+9*(c), w);
	w.Format("N uptaken by crop");
	art.TextOut(x, y+50+10*(c), w);
	w.Format("N uptaken by weeds");
	art.TextOut(x, y+50+11*(c), w);
	w.Format("NH3 volatilization");
	art.TextOut(x, y+50+12*(c), w);
	w.Format("N2O flux");
	art.TextOut(x, y+50+13*(c), w);
	w.Format("NO flux");
	art.TextOut(x, y+50+14*(c), w);
	w.Format("N2 flux");
	art.TextOut(x, y+50+15*(c), w);
	w.Format("Soil N balance");
	art.TextOut(x, y+50+16*(c), w);

	//w.Format("Soil N input and output fluxes at site %s in year %d", Site_Name, year);
	//art.TextOut(350, 60, w);

	//w.Format("( Source data file: \%s )", rcd);
	//art.TextOut(350, 80, w);

	art.SetTextAlign(TA_RIGHT);

	art.SetTextColor(RGB(80,80,80));
	w.Format("%8.1f", fixN);
	art.TextOut(x+b, y+50+7*(c), w);

	art.SetTextColor(RGB(0,0,0));
		
	w.Format("%8.1f", manureN);
	art.TextOut(x+b, y+50+1*(c), w);	
	w.Format("%8.1f", litterN);
	art.TextOut(x+b, y+50+2*(c), w);
	w.Format("%8.1f", rootN);
	art.TextOut(x+b, y+50+3*(c), w);	
	w.Format("%8.1f", weedN);
	art.TextOut(x+b, y+50+4*(c), w);	
	w.Format("%8.1f", rainN);
	art.TextOut(x+b, y+50+5*(c), w);	
	w.Format("%8.1f", fertN);
	art.TextOut(x+b, y+50+6*(c), w);	
		
	w.Format("%8.1f", leachN);
	art.TextOut(x+b, y+50+8*(c), w);
	w.Format("%8.1f", runoffN);
	art.TextOut(x+b, y+50+9*(c), w);
	w.Format("%8.1f", uptakeN);
	art.TextOut(x+b, y+50+10*(c), w);
	w.Format("%8.1f", weedupN);
	art.TextOut(x+b, y+50+11*(c), w);
	w.Format("%8.1f", NH3);
	art.TextOut(x+b, y+50+12*(c), w);
	w.Format("%8.1f", N2O);
	art.TextOut(x+b, y+50+13*(c), w);
	w.Format("%8.1f", NO);
	art.TextOut(x+b, y+50+14*(c), w);
	w.Format("%8.1f", N2);
	art.TextOut(x+b, y+50+15*(c), w);
	w.Format("%8.1f", dN);
	art.TextOut(x+b, y+50+16*(c), w);

	//w.Format("NO2 flux");
	//art.TextOut(x, y+50+16*(c), w);
	//w.Format("%8.1f", NO2);
	//art.TextOut(x+b, y+50+16*(c), w);

	CPen *pOldPen = NULL;
	CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = art.SelectObject(&Pen1);	
	//art.MoveTo(20, 350);
	//art.LineTo(1050, 350);

	//art.MoveTo(20, 145);
	//art.LineTo(1050, 145);

	art.MoveTo(250, 110);
	art.LineTo(250, 650);


	art.SelectObject(pOldPen);
	Pen1.DeleteObject();
	
	CFont hNewFont;
		TEXTMETRIC tm;
		CString dndc;
		dndc.Format("Soil N balance for %s land in %s for year %d (kg N/ha)", CropName, Site_Name, year);

		hNewFont.CreateFont(45,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextAlign(TA_LEFT);
		art.TextOut(50, 40, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("N inputs");
	hNewFont.CreateFont(40,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextAlign(TA_LEFT);
		art.TextOut(100, 100, dndc);
		
		hNewFont.DeleteObject();

	dndc.Format("N outputs");
	hNewFont.CreateFont(40,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(200,200,255));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextAlign(TA_LEFT);
		art.TextOut(300, 100, dndc);
		
		hNewFont.DeleteObject();


}

void CGraphexView::GWP(CGraphexDoc *pDoc)
{

	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (660,10); 
	art.SetViewportExt(510, 2940);

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
	art.FillRect(rectClient, &Brush1);
	Brush1.DeleteObject();

	CString data;

	art.SetTextColor(RGB(0,0,0));
	art.SetTextAlign(TA_RIGHT);

	int x=200, y=200;
	data.Format("%5.0f", -dSOC);
	art.TextOut(x+0*y, 250, data);
	data.Format("%5.1f", N2O);
	art.TextOut(x+1*y, 250, data);
	data.Format("%5.0f", CH4);
	art.TextOut(x+2*y, 250, data);

	data.Format("%5.0f", GWP_CO2);
	art.TextOut(x+0*y, 350, data);
	data.Format("%5.0f", GWP_N2O);
	art.TextOut(x+1*y, 350, data);
	data.Format("%5.0f", GWP_CH4);
	art.TextOut(x+2*y, 350, data);

/*	data.Format("%5.3f", GWP_CO2);
	art.TextOut(x+0*y, 450, data);
	data.Format("%5.3f", GWP_N2O);
	art.TextOut(x+1*y, 450, data);
	data.Format("%5.3f", GWP_CH4);
	art.TextOut(x+2*y, 450, data);*/

	data.Format("%5.0f", NetGWP);
	art.TextOut(x+1*y, 550, data);

	CFont hNewFont;

		CString dndc;

		
		art.SetTextColor(RGB(255,255,255));
		hNewFont.CreateFont(22,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);

		art.SetTextAlign(TA_CENTER);
		dndc.Format("%s, %s", SelectedCounty, SelectedState);		
		art.TextOut(500, 10, dndc);

		dndc.Format("%s, %8.0f ha", CropName, haha);		
		art.TextOut(500, 40, dndc);

		dndc.Format("Year %d", year);		
		art.TextOut(500, 70, dndc);

		art.SetTextAlign(TA_LEFT);
		dndc.Format("Greenhouse     CO2      N2O     CH4");		
		art.TextOut(50, 150, dndc);		
		dndc.Format("gas");		
		art.TextOut(50, 170, dndc);			

		dndc.Format("Flux rate");		
		art.TextOut(50, 250, dndc);

		dndc.Format("GWP");		
		art.TextOut(50, 350, dndc);

		//dndc.Format("GWP");		
		//art.TextOut(50, 450, dndc);

		dndc.Format("Net GWP");		
		art.TextOut(50, 550, dndc);

		hNewFont.DeleteObject();


		art.SetTextColor(RGB(255,255,255));
		hNewFont.CreateFont(16,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);

		art.SetTextAlign(TA_LEFT);
		dndc.Format("                              kg C/ha       kg N/ha      kg C/ha");		
		art.TextOut(50, 290, dndc);

		dndc.Format("kg CO2-equivalent/ha");		
		art.TextOut(50, 390, dndc);

		//dndc.Format("Tg CO2 emission");		
		//art.TextOut(50, 490, dndc);
		//dndc.Format("equivalent");		
		//art.TextOut(50, 510, dndc);
		dndc.Format("Kg CO2-equivalent/ha");		
		art.TextOut(50, 590, dndc);

		hNewFont.DeleteObject();

		int a=380,b=150,c=130,aa=200, cc=100;
	CPen *pOldPen = NULL;
	CPen  Pen1(PS_SOLID, 1, RGB(250,250,250));
	pOldPen = art.SelectObject(&Pen1);	
	
	for(int i=0; i<=5; i++)
	{
		art.MoveTo(50, c+i*cc);
		art.LineTo(980, c+i*cc);

		//art.MoveTo(a+i*aa, 130);
		//art.LineTo(a+i*aa, 530);
	}

	art.SelectObject(pOldPen);
	Pen1.DeleteObject();

	

}


void CGraphexView::RunWizardMonteCarlo(int method)
{
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int i, k, Size, RN1, RN2, RN3, RN4, CropID, StateID, CountyID, landtype;
	float dSOC[20], dCLAY[20], dBD[20], dPH[20];
	float SOC, Clay, pH, BD;

	CString IDfile;
	char StateName[120], CountyName[120];
	FILE *fid;

	IDfile.Format("%s\\Inter\\WizardSite.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	fscanf(fid, "%d %d", &StateID, &CountyID);
	
	fclose(fid);

	IDfile.Format("%s\\Inter\\SelectedCounty.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	fscanf(fid, "%s", StateName);
	//sprintf(StateName, "%s", js);
	fscanf(fid, "%s %d", CountyName, &CropID);
	//CountyName.Format("%s", js);
	
	fclose(fid);

	if(CropID==20) landtype=2;
	else landtype=1;

	IDfile.Format("%s\\Inter\\MonteCarlo.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	
	fscanf(fid, "%d", &Size);

	for(i=1;i<=8;i++)
	{
		fscanf(fid, "%f ", &dSOC[i]);
	}
	
	for(i=1;i<=5;i++)
	{
		fscanf(fid, "%f ", &dCLAY[i]);		 
	}
	
	for(i=1;i<=5;i++)
	{
		fscanf(fid, "%f ", &dBD[i]);		 
	}
	
	for(i=1;i<=5;i++)
	{
		fscanf(fid, "%f ", &dPH[i]);		 
	}
	
	fclose(fid);

	//dndc74 oz;
	int size;

	if(method==0) size = Size;
	else size = 2;

	for(k=1; k<=size; k++)
	{
		if(method==0)
		{
			RN1 = WizardRandomGenerator(8);
			RN2 = WizardRandomGenerator(5);
			RN3 = WizardRandomGenerator(5);
			RN4 = WizardRandomGenerator(5);

			SOC = dSOC[RN1];
			Clay = dCLAY[RN2];
			pH = dPH[RN3];
			BD = dBD[RN4];
		}
		else
		{
			if(k==1)
			{
				SOC = dSOC[1];
				Clay = dCLAY[5];
			}
			else
			{
				SOC = dSOC[8];
				Clay = dCLAY[1];
			}
			pH = dPH[3];
			BD = dBD[3];
		}

		CString note;
		FILE *mc;
		note.Format("%s\\Inter\\Combination", OUTPUT);
		mc=fopen(note, "w");
		if ( mc == NULL )
		{
			CString mess;
			mess.Format("Can not create %s.", note);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(mc, "%f %f %f %f\n", SOC, Clay, pH, BD);
		fclose(mc);

		//region_soil_files(k, SOC, Clay, pH, BD, CountyID, landtype);

		/*class_model *DNDC; //define DNDC as a point of class_model

		if(!(DNDC = new class_model() )) //assign a memory space for DNDC
				AfxMessageBox("No enough memory to run class_model()");

		DNDC->year = 1;

		DNDC->DNDC74(pDoc, 1, 999, 1, CropID, 1, k, CountyID, 1, 1); 

		delete DNDC;*/

		char KK[50];
		sprintf(KK, "%d", k);

// changed by liujm

		//MODEL_LINK_INFO link;
		CClientDC dc(this);
		link.pWnd = this;
		link.pDC = &dc;
		link.DNDC_or_Other = pDoc->DNDC_or_Other;
		link.StopRun = pDoc->StopRun;
		char FfFf[6][150]={"",""};
		int FFN=0;
#ifdef DEGUI
#else
		char BatchPass[300]="NULL";
		Model_link(&link, 1, "CropID", 0, 1, 1, StateName, CountyName, KK, 1, 1, 1, 1, 1, 2000, 
			0, 0, 0, 0,1, "", 0, 0, 0, "0", 0, 0, 0, FfFf, "", 4, BatchPass);
		pDoc->DNDC_or_Other = link.DNDC_or_Other;
		pDoc->StopRun = link.StopRun;
#endif
	}
}


int WizardRandomGenerator(int ss)
{
	int RN;

	time_t t = time(NULL);

	srand(t);

	RN = rand() % ss;

	RN += 1;

	return(RN);
}

void CGraphexView::draw_LandUse(CGraphexDoc *pDoc, int stateID, int cropID)
{
	int pairs=0, StateID, i;
	long int CountyID, MapID, map_id;
	float Da, Db, ha;
	int c1, c2, c3;
	
	CPoint map_data[50000];

	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (0,0); 
	art.SetViewportExt(1500, 3000);
	

	CPen *pOldPen = NULL;				//create a point for pen
	CPen Pen1(PS_SOLID, 1, RGB(255,255,255));	//define a pen
	pOldPen = art.SelectObject(&Pen1);	//select the pen into pen point		

	CBrush Brush1(RGB(ww1,ww2,ww3));		//define a brush

	art.FillRect(rectClient, &Brush1);

	Brush1.DeleteObject();

	
	CString led;

	for(i=0; i<=10; i++)
	{
		ha = 50000.0 * i;

		landuse_color(ha, &c1, &c2, &c3);
		art.FillSolidRect(250+i*50, 580, 50, 10, RGB(c1,c2,c3));

	}
	art.SetTextColor(RGB(qq1,qq2,qq3));
	led.Format ("0        0.1        0.2       0.3        0.4        0.5       0.6       0.7        0.8        0.9       1.0  million ha/county");
	art.TextOut(250, 600, led);

	CString Crop[20] = {"All crop", "Corn", "Winter wheat", "Spring wheat", "Qats",
						"Barley", "Rice", "Sorhgum", "Cotton", "Soybean", "Potato",
						"Beet", "Peanut", "Vegetable", "Pineapple", "Sugarcane",
						"Tobacco", "Sunflower", "Legume hay", "Non-legume hay"};


		CFont hNewFont;
		TEXTMETRIC tm;
		CString dndc;
		dndc.Format("%s lands in the U.S.", Crop[cropID]);

		hNewFont.CreateFont(30,0,0,0,FW_SEMIBOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(10,100,50));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.TextOut(350, 10, dndc);
		
		hNewFont.DeleteObject();


	FILE *Fcounty;
	CString StateName;	

	StateName.Format("%s\\Database\\USA\\Map\\CountyID_MapID.txt", ROOTDIR);
	Fcounty = fopen(StateName, "r");
	if(Fcounty==NULL)
	{
		CString note;
		note.Format("Can not open file %s", StateName);
		AfxMessageBox(note);
		exit(0); 
	}

	read_scale(stateID);

	TotalCounty = 0;
	for(;;)
	{
		if(fscanf(Fcounty, "%ld %ld", &CountyID, &MapID)!=2) 
			break;
		else
		{
			StateID = (int)((float)CountyID/1000.0);

			if(StateID==2) goto NEXTC;

			CString RF;
			FILE *ref;

			RF.Format("%s\\Database\\USA\\Map\\%ld", ROOTDIR, MapID);
			ref = fopen(RF, "r");
			if(ref==NULL)
			{
				//CString note;
				//note.Format("Can not find file %s", RF);
				//AfxMessageBox(note);
				//exit(0); 
			}
			else
			{

				if(fscanf(ref, "%ld %d", &map_id, &pairs)!=2) 
				{
				}
				else
				{
					for(i=0; i<pairs; i++)
					{
						fscanf(ref, "%f %f", &Da, &Db);					
						{
							map_data[i].x  = (int)((X1 + Da) * X2);
							map_data[i].y = (int)((Y1 - Db) * Y2);
						}
					}					

					ha = find_ha(CountyID, cropID);

					landuse_color(ha, &c1, &c2, &c3);

					CBrush *pOldBrush = NULL;			//create a point for brush 
					CBrush Brush2(RGB(c1,c2,c3));
					pOldBrush = art.SelectObject(&Brush2);  //select the brush into brush point
					
					art.Polygon(map_data, pairs);				//draw poligon with the pen and brush
				
					art.SelectObject(pOldBrush);		//return original brush into brush point	
					Brush1.DeleteObject();

					}
			}
			fclose(ref);			
		}
NEXTC:	
		;
	}//end of for{}

	art.SelectObject(pOldPen);			//return original pen into oen point
	Pen1.DeleteObject();

	fclose(Fcounty);

	draw_states(pDoc);
}

void landuse_color(float ha, int *c1, int *c2, int *c3)
{
	*c1 = (int)(8E-10*ha*ha - 0.0009*ha + 251.83);
	*c2 = (int)(-8E-10*ha*ha - 0.0001*ha + 252.53);
	*c3 = (int)(1E-09*ha*ha - 0.0012*ha + 251.74);

	if(*c1>255) *c1=255;
	if(*c1<0) *c1=0;
	if(*c2>255) *c2=255;
	if(*c2<0) *c2=0;
	if(*c3>255) *c3=255;
	if(*c3<0) *c3=0;

}

float find_ha(long int CountyID, int cropID)
{
	float ha, area;
	char WW[200];
	long int C_ID;

	FILE *Fcounty;
	CString StateName, CropName;	

	if(cropID==0) CropName.Format("US_cropland_area_97.txt");
	else if(cropID==1) CropName.Format("US_corn_area_97.txt");
	else if(cropID==2) CropName.Format("US_winterwheat_area_97.txt");
	else if(cropID==3) CropName.Format("US_springwheat_area_97.txt");
	else if(cropID==4) CropName.Format("US_oat_area_97.txt");
	else if(cropID==5) CropName.Format("US_barley_area_97.txt");
	else if(cropID==6) CropName.Format("US_rice_area_97.txt");
	else if(cropID==7) CropName.Format("US_sorhgum_area_97.txt");
	else if(cropID==8) CropName.Format("US_cotton_area_97.txt");
	else if(cropID==9) CropName.Format("US_soybean_area_97.txt");
	else if(cropID==10) CropName.Format("US_potato_area_97.txt");
	else if(cropID==11) CropName.Format("US_beet_area_97.txt");
	else if(cropID==12) CropName.Format("US_peanut_area_97.txt");
	else if(cropID==13) CropName.Format("US_vegetable_area_97.txt");
	else if(cropID==14) CropName.Format("US_pineapple_area_97.txt");
	else if(cropID==15) CropName.Format("US_sugarcane_area_97.txt");
	else if(cropID==16) CropName.Format("US_tobacco_area_97.txt");
	else if(cropID==17) CropName.Format("US_sunflower_area_97.txt");
	else if(cropID==18) CropName.Format("US_legumehay_area_97.txt");
	else if(cropID==19) CropName.Format("US_nonlegumehay_area_97.txt");
	else
	{
		CString note;
		note.Format("The selected crop type %d is wrong", cropID);
		AfxMessageBox(note);
		exit(0);
	}
	
	
	StateName.Format("%s\\Database\\USA\\Land_cover\\%s", ROOTDIR, CropName);
	
	Fcounty = fopen(StateName, "r");
	if(Fcounty==NULL)
	{
		CString note;
		note.Format("Can not open file %s", StateName);
		AfxMessageBox(note);
		return(0);//exit(0); 
	}

	fgets(WW, 200, Fcounty);
	for(;;)
	{
		if(fscanf(Fcounty, "%ld %f", &C_ID, &area)!=2)

			break;
		else
		{
			if(C_ID==CountyID) 
			{
				ha = area;
				break;
			}			
		}
	}
	fclose(Fcounty);

	return(ha);
}