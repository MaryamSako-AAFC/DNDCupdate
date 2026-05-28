#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 

extern class_manure MData;

void class_manure::FM_frame(MODEL_LINK_INFO* pLinkInfo, char *countryName, char *stateName, char *site, 
				   int MODE, int year)
{
	CWnd* pDC = pLinkInfo->pWnd;
	CDC& dc = *(pLinkInfo->pDC);

	pDC->EnableWindow(TRUE);

	CRect rectClient;
	pDC->GetClientRect(rectClient);

	dc.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	dc.SetWindowExt(1500, 3000);

	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(1500, 3000);	

	CBrush *pOldBrush = dc.GetCurrentBrush(); 
	CBrush brush0;								
	brush0.CreateSolidBrush(RGB(200,0,0));	
	pOldBrush = dc.SelectObject(&brush0);

	dc.SetViewportOrg (0, 0); //profile note
	dc.SetViewportExt(1500, 1500);
	dc.FillSolidRect(0, 0, 1020, 1280, RGB(0,0,0)); //background

	dc.FillSolidRect(245, 0, 4, 1280, RGB(200,200,200));
	dc.FillSolidRect(802, 0, 4, 1280, RGB(200,200,200));
	dc.FillSolidRect(0, 160, 248, 4, RGB(200,200,200));
	dc.FillSolidRect(0, 1050, 248, 4, RGB(200,200,200));

	dc.FillSolidRect(248, 256, 770, 4, RGB(200,200,200));
	dc.FillSolidRect(248, 512, 770, 4, RGB(200,200,200));
	dc.FillSolidRect(248, 768, 770, 4, RGB(200,200,200));
	dc.FillSolidRect(248, 1024, 770, 4, RGB(200,200,200));

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(200,200,200));

	CString w_clim0;

	dc.SetViewportOrg (0,0); //notes
	dc.SetViewportExt(365, 400);

	
	if(MODE==0)
		w_clim0.Format ("Site:          %s", site);
	else
		w_clim0.Format ("%s  %s", site, stateName);
	dc.TextOut(40, 100, w_clim0);
	w_clim0.Format("Year:         %d", year);
	dc.TextOut(40, 250, w_clim0);
	w_clim0 = "Crop: ";
	dc.TextOut(40, 400, w_clim0);
	
	dc.SetViewportOrg (260,5); //climate
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);	
	
	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Climate";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "air temperature";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "precipitation";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "snowpack";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "evaporation";
	dc.TextOut(740, 340, w_clim0);
	//w_clim0 = "transpiration";
	//dc.TextOut(740, 420, w_clim0);
	w_clim0 = "wind speed";
	dc.TextOut(740, 420, w_clim0);

	dc.FillSolidRect(900, 150, 70, 5, RGB(255,0,0)); //temperature
	dc.FillSolidRect(935, 200, 2, 50, RGB(180,180,255)); //precipitation
	dc.FillSolidRect(935, 280, 2, 50, RGB(255,255,255)); //snowpack
	dc.FillSolidRect(935, 360, 2, 50, RGB(250,0,250)); //evaporation
	dc.FillSolidRect(935, 440, 2, 50, RGB(100,0,250)); //wind speed(transpiration)

	dc.SetViewportOrg (260,135); //plant
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	/*dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Crop";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "photosynthesis";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "respiration";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "N uptake";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "water stress";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "N stress";
	dc.TextOut(740, 420, w_clim0);
	w_clim0 = "biomass & LAI";
	dc.TextOut(740, 500, w_clim0);*/

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Feeding lot";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "temperature";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "moisture";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "manure";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "CO2";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "NH3";
	dc.TextOut(740, 420, w_clim0);
	w_clim0 = "CH4";
	dc.TextOut(740, 500, w_clim0);

	dc.FillSolidRect(900, 130, 70, 10, RGB(255, 0, 50)); //temp
	dc.FillSolidRect(900, 210, 70, 10, RGB(250, 250, 250)); //moisture
	dc.FillSolidRect(900, 290, 70, 10, RGB(250,200,20)); //manure
	dc.FillSolidRect(900, 370, 70, 5, RGB(200,255,255)); //CO2
	dc.FillSolidRect(900, 450, 70, 5, RGB(250,100,155)); //NH3
	dc.FillSolidRect(900, 530, 70, 10, RGB(120,180,120)); //CH4
	//dc.FillSolidRect(935, 550, 30, 5, RGB(0, 255, 255)); //LAI
	//dc.FillSolidRect(915, 520, 2, 50, RGB(150,200,200)); //grain

	dc.SetViewportOrg (260,259); //soil
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Compost";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "temperature";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "moisture";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "manure";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "CO2";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "NH3";
	dc.TextOut(740, 420, w_clim0);
	w_clim0 = "CH4";
	dc.TextOut(740, 500, w_clim0);

	dc.FillSolidRect(900, 150, 70, 10, RGB(255,0,0)); //temp
	dc.FillSolidRect(900, 230, 70, 10, RGB(20,200,250)); //mois
	dc.FillSolidRect(900, 310, 70, 10, RGB(200,200,0)); //manure
	dc.FillSolidRect(900, 390, 70, 5, RGB(200,255,255)); //CO2
	dc.FillSolidRect(900, 470, 70, 10, RGB(250,100,155)); //NH3
	dc.FillSolidRect(900, 550, 70, 10, RGB(120,180,120)); //CH4

	dc.SetViewportOrg (260,391); //microbial activity
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Lagoon";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "slurry";
	dc.TextOut(740, 100, w_clim0);
	//w_clim0 = "NH4";
	//dc.TextOut(740, 180, w_clim0);
	w_clim0 = "NH3 flux";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "CH4 flux";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "N2O flux";
	dc.TextOut(740, 420, w_clim0);
	//w_clim0 = "Organic C";
	//dc.TextOut(740, 500, w_clim0);

	dc.FillSolidRect(900, 150, 70, 10, RGB(100,150,255)); //water 
	//dc.FillSolidRect(900, 230, 70, 10, RGB(250,100,100)); //NH4
	dc.FillSolidRect(900, 310, 70, 10, RGB(250,100,155)); //NH3
	dc.FillSolidRect(900, 390, 70, 5, RGB(200,150,240)); //CH4 
	dc.FillSolidRect(900, 470, 70, 5, RGB(250,250,0)); //N2O
	//dc.FillSolidRect(900, 550, 70, 5, RGB(250,200,80)); //SOC

	dc.SetViewportOrg (260,523); //gas flux
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Digester";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "CH4";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "NH3";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "N2O";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "N2";
	dc.TextOut(740, 340, w_clim0);
	//w_clim0 = "NH4+NO3";
	//dc.TextOut(740, 420, w_clim0);

	dc.FillSolidRect(900, 130, 70, 5, RGB(150,200,100)); //CH4
	dc.FillSolidRect(900, 210, 70, 5, RGB(50,150,200)); //NH3
	dc.FillSolidRect(900, 290, 70, 5, RGB(250,100,155)); //N2O
	dc.FillSolidRect(900, 370, 70, 10, RGB(255,255,255)); //N2 
	//dc.FillSolidRect(900, 470, 70, 5, RGB(250,200,80)); //NH4+NO3


	dc.SelectObject(pOldBrush);	

}

void class_manure::FM_paint(MODEL_LINK_INFO* pLinkInfo, int cwc, char *cropName, int MODE, int c_ViewMode, 
							char *cropping_system, int jday, float air_temp, float rainfall, float *soc, 
							float *day_wfps, int q, float *nh4, float *no3, float *urea, double water[25][250], 
							float *temp, float day_soil_nh3, float *day_plant_nh3, float day_vol_nh3, 
							float day_soil_an_n2o, float day_soil_n2)
{
		static int x1, y1, z1, a1, b1, c1, d1, e1, f1, g1, fw1, rf1;
		static int h1, i1, ii1, j1, k1, l1, m1, n1, o1, p1, q1, s1, t1, wt1, w1, u1, v1, aa1, bb1;
		static int cc1, lw1, hh1, dd1, ee1, ww1, yd=0, CB=0;
		int x2, y2, z2, a2, b2, c2, d2, e2, f2, g2, lw2, fw2, rf2;
		int h2, i2, ii2, j2, k2, l2, m2, n2, o2, p2, q2, s2, t2, wt2, w2, u2, v2, aa2, bb2, cc2;
		int i, hh2, dd2, ee2, ww2;
		float total_N=0.0;
		CString CName;

		if(jday==1) yd=0;

		CWnd* pDC = pLinkInfo->pWnd;
		CDC& dc = *(pLinkInfo->pDC);

		CRect rectClient;
		pDC->GetClientRect(rectClient);

		dc.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
		dc.SetWindowExt(1500, 3000);
			
		CPen *pOldPen = NULL;

		dc.SetViewportOrg (0,0); //notes
		dc.SetViewportExt(365, 400);

		dc.SetTextColor(RGB(200,200,200));
		CString w_clim0;
		
		if(MODE==0 || (MODE==1&&c_ViewMode==1))
		{
			dc.FillSolidRect(280, 400, 700, 100, RGB(0,0,0));
			w_clim0.Format ("%s", cropName);
			dc.TextOut(300, 400, w_clim0);
		}
		else 
		{
			dc.FillSolidRect(5, 300, 1100, 300, RGB(0,0,0));
			w_clim0.Format ("  Crop system:%s  %s", cropping_system, cropName);
			dc.TextOut(10, 400, w_clim0);
		}
				
		if(jday==1) x1 = 0;
		x2 = jday*2;
		
		// climate ///////////////////////////////////
		dc.SetViewportOrg (250,0); //climate
		dc.SetViewportExt(1130, 580);	
		
		if(jday==1) 
		{
			y1 = (int) (325 - air_temp * 7);
			z1 = (int) (rainfall * 2000);
			//a1 = (int) (650 - snow_pack * 5000);
			//b1 = (int) (650 - (day_transp+day_evapor) * 10000);	
			//c1 = (int) (650 - day_evapor * 10000);

			CPen  Pen1(PS_SOLID, 1, RGB(100,100,100));
			pOldPen = dc.SelectObject(&Pen1);		
			dc.MoveTo(0, 325);
			dc.LineTo(730, 325);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
		}
		
		//air temperature
		y2 = (int) (325 - air_temp * 7);

		CPen  Pen1(PS_SOLID, 1, RGB(255,0,0));
		pOldPen = dc.SelectObject(&Pen1);		
		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();

		y1 = y2;

		//precipitation
		z2 = (int) (rainfall * 2000);

		Pen1.CreatePen(PS_SOLID, 1, RGB(180,180,255));
		pOldPen = dc.SelectObject(&Pen1);
		dc.MoveTo(x1, 0);
		dc.LineTo(x1, z2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();

		z1 = z2;

/*		//snowpack		
		//a2 = (int) (650 - snow_pack * 2500);
		
		Pen1.CreatePen(PS_SOLID, 1, RGB(255,255,255));
		pOldPen = dc.SelectObject(&Pen1);		
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, a2);	
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();		

		a1 = a2;

		//evapotranspiration
//		b2 = (int) (650 - (day_transp+day_evapor) * 10000);	
		
		Pen1.CreatePen(PS_SOLID, 1, RGB(100,0,250));
		pOldPen = dc.SelectObject(&Pen1);	
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, b2);	
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	

		b1 = b2;

		//evaporation
//		c2 = (int) (650 - day_evapor * 10000);
		Pen1.CreatePen(PS_SOLID, 1, RGB(250,0,250));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, c2);	
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	

		c1 = c2;
*/
		// housing ///////////////////////////////////
		int GN=q+1, FN=1;
		dc.SetViewportOrg (250,127); 
		dc.SetViewportExt(1130, 580);

		if(jday==1) 
		{
			d1 = (int) (650 - (soc[GN]/MData.mm_GroundArea[FN])*0.01);
			h1 = (int) (650 - (MData.day_house_co2/MData.mm_GroundArea[FN])*2.0);
			g1 = (int) (650 - (MData.day_house_nh3/MData.mm_GroundArea[FN])*4.0);
			e1 = (int) (650 - (day_wfps[GN])*200.0);
			f1 = (int) (650 - (MData.day_house_ch4+MData.day_gutter_ch4)/MData.mm_GroundArea[FN]*5.0);
						
			//hh1 = (int) (650 - (lai)*80);
			

			//if(CropModel==1)
			//{
			//	ww1 = (int) (280 - leaf_area_N * 80);
			//	dd1 = (int) (650 - (PCGW)*0.5);
			//	ee1 = (int) (650 - (RMCR+RGCR)*0.5);
			//}
		}

	//if(seed[cwc]>0)
	//{
		//CB++;

		//accumulated manure in house
		float Fsoc=soc[GN];

		if(MData.mm_GroundArea[FN]<=0.0) d2 = 0;
		else
		{
		d2 = (int) (650 - (Fsoc/MData.mm_GroundArea[FN])*0.1);
		//if(d2>0)
		//{
		Pen1.CreatePen(PS_SOLID, 1, RGB(250,200,20));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, d2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();
		d1 = d2;
		}

		//CO2 from house
		if(MData.mm_GroundArea[FN]<=0.0) h2 = 0;
		else
		{
		h2 = (int) (650 - (MData.day_house_co2/MData.mm_GroundArea[FN])*0.1);
		Pen1.CreatePen(PS_SOLID, 1, RGB(200,255,255));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, h1);
		dc.LineTo(x2, h2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		h1 = h2;
		}

		//NH3 from house and pen
		if(MData.mm_GroundArea[FN]<=0.0) g2 = 0;
		else
		{
		g2 = (int) (650 - (MData.day_house_nh3+MData.day_gutter_nh3)/MData.mm_GroundArea[FN]);
		Pen1.CreatePen(PS_SOLID, 1, RGB(250,100,155));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, g1);
		dc.LineTo(x2, g2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		g1 = g2;
		}
	
		//moisture
		e2 = (int) (650 - (day_wfps[GN])*200.0);
		Pen1.CreatePen(PS_SOLID, 1, RGB(200,200,200));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, e1);
		dc.LineTo(x2, e2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		e1 = e2;

		//Enteric N2O
		if(MData.mm_GroundArea[FN]<=0.0) f2 = 0;
		else
		{
		f2 = (int) (650 - (MData.day_house_ch4+MData.day_gutter_ch4)/MData.mm_GroundArea[FN]);
		Pen1.CreatePen(PS_SOLID, 1, RGB(10,250,50));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, f1);
		dc.LineTo(x2, f2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		f1 = f2;
		}


		//////////////////////////////////////////
		 GN=q+4;
if(soc[GN]>0.0)
{
		dc.SetViewportOrg (250,255); //compost
		dc.SetViewportExt(1130, 580);
		//int L05 = (int)(0.05/Lh+1);
		//int L15 = (int)(0.15/Lh+1);
		//int L30 = (int)(0.3/Lh+1);
	
		total_N = 0.0;

		//for (i=1; i<=q; i++)
		//{
		total_N = (nh4[GN] + no3[GN] + urea[GN]);
		//}

		if(jday==1) 
		{
			i1 = (int) (650 - water[1][GN]*0.001);
			ii1 = (int) (650 - soc[GN]*0.001);
			j1 = (int) (650 - MData.day_compost_co2*1.0);	
			k1 = (int) (650 - (temp[GN])*7);
			l1 = (int) (650 - MData.day_Compost_nh3*1.0);
			m1 = (int) (650 - (MData.day_compost_ch4)*1.5);	
			//m1 = (int) (650 - day_clay_N);
			n1 = (int) (650 - (total_N)*3);
			//lw1 = (int) (650 - (day_leach_water)*15000);
			//rf1 = (int) (600 - RainfedDepth*500);
		}

		//moisture
		i2 = (int) (650 - water[1][GN]*0.001);
		Pen1.CreatePen(PS_SOLID, 1, RGB(20,200,250));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, i1);
		dc.LineTo(x2, i2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		i1 = i2;

		//soc
		ii2 = (int) (650 - soc[GN]*0.001);
		Pen1.CreatePen(PS_SOLID, 1, RGB(200,200,0));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, ii2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		ii1 = ii2;

		j2 = (int) (650 - (MData.day_compost_co2 * 1.0));
		Pen1.CreatePen(PS_SOLID, 1, RGB(200,255,255));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, j1);
		dc.LineTo(x2, j2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		j1 = j2;
	
		//soil temperature
		k2 = (int) (650 - (temp[GN])*7);	
		Pen1.CreatePen(PS_SOLID, 1, RGB(255,0,0));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, k1);
		dc.LineTo(x2, k2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		k1 = k2;

		l2 = (int) (650 - MData.day_Compost_nh3*1.0);
		Pen1.CreatePen(PS_SOLID, 1, RGB(250,100,155));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, l1);
		dc.LineTo(x2, l2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		l1 = l2;

		m2 = (int) (650 - (MData.day_compost_ch4)*100.0);		
		Pen1.CreatePen(PS_SOLID, 1, RGB(120,180,120));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, m1);
		dc.LineTo(x2, m2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		m1 = m2;
}
		
		//lagoon////////////////////////////////////////////////
		GN=q+5;
if(soc[GN]>0.0)
{
		dc.SetViewportOrg (250,383); 
		dc.SetViewportExt(1130, 580);
		if(jday==1) 
		{
			o1 = (int) (650 - (water[1][GN])*0.0002);			
			bb1 = (int) (650 - (nh4[GN])*0.005);
			cc1 = (int) (650 - (MData.day_lagoon_ch4)*0.2);
			v1 = (int) (650 - (MData.day_lagoon_nh3)*1.0);
			aa1 = (int) (650 - soc[GN]*0.0005);
		}
		
		o2 = (int) (650 - (water[1][GN])*0.0002);		
		Pen1.CreatePen(PS_SOLID, 3, RGB(100,150,255));//(250,250,255));
		pOldPen = dc.SelectObject(&Pen1);		
		dc.MoveTo(x1, o1);
		dc.LineTo(x2, o2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();
		o1 = o2;
		
		//Daily methane oxidation rate
		if(MData.day_lagoon_ch4>0.0)
		{
		cc2 = (int) (650 - MData.day_lagoon_ch4*0.2);
		
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(200,150,240));
			pOldPen = dc.SelectObject(&Pen1);

			dc.MoveTo(x1, cc1);
			dc.LineTo(x2, cc2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			cc1 = cc2;
		}
		}

		//Daily NH3 volatilizatione
		v2 = (int) (650 - MData.day_lagoon_nh3*1.0);
		//v2 = (int) (650 - nh3[-4]*0.1);
		{
			Pen1.CreatePen(PS_SOLID, 2, RGB(250,100,155));
			pOldPen = dc.SelectObject(&Pen1);

			dc.MoveTo(x1, v1);
			dc.LineTo(x2, v2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			v1 = v2;
		}

		//lagoon SON
		
}

		//Digester ///////////////////////////////////////////////////////////
		dc.SetViewportOrg (250,523); //gas 2
		dc.SetViewportExt(1130, 400);

		total_N = 0.0;
		for (i=1; i<=q; i++)
		{
			total_N += (nh4[i] + no3[i]);
		}

		if(jday==1) 
		{
			//w1 = (int) (650 - (Leaf_Wt+Stem_Wt+Root_Wt+Grain_Wt)*0.05);
			//wt1 = (int) (650 - (total_N)*0.1);
			//s1 = (int) (650 - (day_soil_an_n2o+day_soil_n2)*400);
			//t1 = (int) (650 - (day_soil_an_n2o)*400);	
			//w1 = (int) (250 - (day_soil_an_no)*400);
			//p1 = (int) (650 - (day_soil_nh3 + day_plant_nh3 + day_vol_nh3)*20);	
			//q1 = (int) (650 - (day_ch4)*50);

		}

		//CH4
		w2 = (int) (650 - (MData.day_digester_CH4)*1.0);
		Pen1.CreatePen(PS_SOLID, 2, RGB(150,200,100));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, w1);
		dc.LineTo(x2, w2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		w1 = w2;

		//NH3
		wt2 = (int) (650 - (MData.day_digester_nh3)*1.0);
		Pen1.CreatePen(PS_SOLID, 2, RGB(50,150,200));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, wt1);
		dc.LineTo(x2, wt2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		wt1 = wt2;

		//N2O
		p2 = (int) (650 - MData.day_digester_n2o*1.0);
		if(p2<0) p2=0;
		if(MData.day_digester_n2o>0.0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(250,100,155));
			pOldPen = dc.SelectObject(&Pen1);

			dc.MoveTo(x1, p1);
			dc.LineTo(x2, p2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			p1 = p2;
		}


		//N2
		s2 = (int) (650 - MData.day_digester_n2*1.0);	
		if(s2<0) s2=0;
		if(MData.day_digester_n2>0.0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(255,255,255));
			pOldPen = dc.SelectObject(&Pen1);
			
			dc.MoveTo(x1, s1);
			dc.LineTo(x2, s2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			s1 = s2;
		}

/*		//N2O 
		t2 = (int) (650 - day_soil_an_n2o*400);
		if(t2<0) t2=0;
		if(day_soil_an_n2o>0.0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(0,255,0));
			pOldPen = dc.SelectObject(&Pen1);
			
			dc.MoveTo(x1, 650);
			dc.LineTo(x1, t2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			t1 = t2;
		}
*/

		CString mn;
		dc.SetTextColor(RGB(200,200,200));
		dc.SetBkMode(TRANSPARENT);
		int   Mday[12]={1,31,59,90,121,151,182,213,243,274,304,335};
		CString mmn[12]={"J","F","M","A","M","J","J","A","S","O","N","D"}; 

		if(jday==Mday[yd]) 
		{	
			dc.FillSolidRect(x1-1, 660, 2, 85, RGB(200,200,200));
			dc.TextOut(x1+20, 750, mmn[yd]);
			yd++;
		}
		
		x1 = x2;

if(jday==365)
{
	dc.SetViewportOrg (0,85); //soil profile
	dc.SetViewportExt(365, 2000);
	//dc.FillRect(rectClient, &brush0);
	CString FGS;

	int g_co2 = (int)(MData.yr_enteric_co2+MData.yr_house_co2+MData.yr_digester_co2+MData.yr_lagoon_co2+MData.yr_compost_co2);
	int g_ch4 = (int)(MData.yr_enteric_ch4+MData.yr_house_ch4+MData.yr_lagoon_ch4+MData.yr_compost_ch4);
	int g_n2o = (int)(MData.yr_enteric_n2o+MData.yr_house_n2o+MData.yr_digester_n2o+MData.yr_lagoon_n2o+MData.yr_compost_n2o);
	int g_nh3 = (int)(MData.yr_house_nh3+MData.yr_digester_nh3+MData.yr_lagoon_nh3+MData.yr_compost_nh3);
	int g_n2 = (int)(MData.yr_house_n2+MData.yr_digester_n2+MData.yr_lagoon_n2+MData.yr_compost_n2);
	int g_dgch4 = (int)(MData.yr_digester_ch4);

	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "Farm gas flux (kg C or N)";
	dc.TextOut(25, 5, w_clim0);

	FGS.Format("CO2          %d", g_co2);
	w_clim0 = FGS;
	dc.TextOut(25, 85, w_clim0);
	FGS.Format("CH4          %d", g_ch4);
	w_clim0 = FGS;
	dc.TextOut(25, 165, w_clim0);
	FGS.Format("N2O          %d", g_n2o);
	w_clim0 = FGS;
	dc.TextOut(25, 245, w_clim0);
	FGS.Format("NH3          %d", g_nh3);
	w_clim0 = FGS;
	dc.TextOut(25, 325, w_clim0);
	FGS.Format("N2          %d", g_n2);
	w_clim0 = FGS;;
	dc.TextOut(25, 405, w_clim0);
	FGS.Format("Biofuel_CH4          %d", g_dgch4);
	w_clim0 = FGS;
	dc.TextOut(25, 485, w_clim0);
}

}


#endif