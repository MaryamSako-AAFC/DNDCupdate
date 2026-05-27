#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
//#include "Dndc_draw.h"

void class_model::frame(MODEL_LINK_INFO* pLinkInfo, char *countryName, char *stateName, char* xxID, 
				   int MODE, int year, char *weatherName2)//???
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
		w_clim0.Format ("Site:          %s", xxID);
	else
		w_clim0.Format ("%s  %s", stateName, xxID);
	dc.TextOut(40, 100, w_clim0);//100
	w_clim0.Format("Year:         %d", year);//year Could edit graphic output here to add climateFilename.p[1]
	dc.TextOut(40, 200, w_clim0);//250
	w_clim0 = "Day: ";
	dc.TextOut(40, 300, w_clim0);//400
	
	w_clim0.Format("Clim_Name: %s",weatherName);
	dc.TextOut(40, 450, w_clim0);//490
	
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
	w_clim0 = "transpiration";
	dc.TextOut(740, 420, w_clim0);

	dc.FillSolidRect(900, 150, 70, 5, RGB(255,0,0)); //temperature
	dc.FillSolidRect(935, 200, 2, 50, RGB(180,180,255)); //precipitation
	dc.FillSolidRect(935, 280, 2, 50, RGB(255,255,255)); //snowpack
	dc.FillSolidRect(935, 360, 2, 50, RGB(250,0,250)); //evaporation
	dc.FillSolidRect(935, 440, 2, 50, RGB(100,0,250)); //transpiration

	dc.SetViewportOrg (260,135); //plant
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Crop";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	//w_clim0 = "photosynthesis";
	//dc.TextOut(740, 100, w_clim0);
	//w_clim0 = "respiration";
	//dc.TextOut(740, 180, w_clim0);
	w_clim0 = "water stress";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "N stress";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "N uptake";
	dc.TextOut(740, 260, w_clim0);	
	w_clim0 = "biomass";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "stub";
	dc.TextOut(740, 420, w_clim0);

	//dc.FillSolidRect(900, 150, 70, 10, RGB(255, 0, 50)); //photosynthesis
	//dc.FillSolidRect(900, 230, 70, 10, RGB(250, 250, 250)); //respiration
	dc.FillSolidRect(900, 150, 70, 5, RGB(100,100,255)); //water stress
	dc.FillSolidRect(900, 230, 70, 5, RGB(150, 50, 0)); //N stress
	dc.FillSolidRect(900, 310, 70, 10, RGB(220,250,55)); //N uptake
	
	dc.FillSolidRect(900, 370, 70, 20, RGB(250,200,50)); //biomass-grain
	dc.FillSolidRect(900, 390, 70, 20, RGB(10,250,50)); //biomass-shoot
	dc.FillSolidRect(900, 410, 70, 20, RGB(100,100,250)); //biomass-root
	dc.FillSolidRect(900, 470, 70, 10, RGB(255,255,170)); //stub

	dc.SetViewportOrg (260,259); //soil
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Soil";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "temperature";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "moisture";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "NH4+";
	dc.TextOut(740, 260, w_clim0);
	//w_clim0 = "ice";
	//dc.TextOut(740, 260, w_clim0);
	w_clim0 = "NO3-";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "Eh";
	dc.TextOut(740, 420, w_clim0);
	w_clim0 = "Water table";
	dc.TextOut(740, 500, w_clim0);

	dc.FillSolidRect(900, 150, 70, 10, RGB(150,50,0)); //soil temp
	dc.FillSolidRect(900, 230, 70, 10, RGB(20,200,250)); //soil mois
	dc.FillSolidRect(900, 310, 70, 5, RGB(250,0,0)); //soil NH4
	dc.FillSolidRect(900, 390, 70, 5, RGB(255,255,0)); //soil NO3-
	dc.FillSolidRect(900, 470, 70, 10, RGB(150,150,200)); //Eh
	dc.FillSolidRect(900, 530, 70, 10, RGB(0,0,255)); //water table

	dc.SetViewportOrg (260,391); //microbial activity
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Microbial activity";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "decomposition";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "nitrification";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "denitrification";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "methanogenesis";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "methanotrophy";
	dc.TextOut(740, 420, w_clim0);

	dc.FillSolidRect(900, 150, 70, 5, RGB(150,0,0)); //Decomposition (CO2 from soil)
	dc.FillSolidRect(900, 230, 70, 5, RGB(150,120,5)); //Nitrification
	dc.FillSolidRect(900, 310, 70, 10, RGB(100,255,180)); //Denitrification
	dc.FillSolidRect(900, 390, 70, 10, RGB(0,100,200)); //CH4 prod
	dc.FillSolidRect(900, 470, 70, 5, RGB(0,150,150)); //Ch4 oxid

	dc.SetViewportOrg (260,523); //gas flux
	dc.SetViewportExt(1130, 600);
	//dc.FillRect(rectClient, &brush0);
	//dc.MoveTo(730, 0);
	//dc.LineTo(730, 700);

	dc.SetTextColor(RGB(100,100,100));
	w_clim0 = "Gas flux";
	dc.TextOut(740, 10, w_clim0);
	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "N2O";
	dc.TextOut(740, 100, w_clim0);
	w_clim0 = "NO";
	dc.TextOut(740, 180, w_clim0);
	w_clim0 = "N2";
	dc.TextOut(740, 260, w_clim0);
	w_clim0 = "CH4";
	dc.TextOut(740, 340, w_clim0);
	w_clim0 = "NH3";
	dc.TextOut(740, 420, w_clim0);

	dc.FillSolidRect(935, 120, 2, 50, RGB(0,255,50)); //N2O
	dc.FillSolidRect(935, 200, 2, 50, RGB(0,100,250)); //NO
	dc.FillSolidRect(935, 280, 2, 50, RGB(255,255,255)); //N2
	dc.FillSolidRect(900, 390, 70, 10, RGB(250,100,155)); //CH4 
	dc.FillSolidRect(900, 470, 70, 5, RGB(250,200,20)); //NH3

	dc.SetViewportOrg (0,85); //soil profile
	dc.SetViewportExt(365, 2000);
	//dc.FillRect(rectClient, &brush0);
	
	dc.SetTextColor(RGB(150,150,150));
	//dc.TextOut(2, 50, "Soil depth, cm");
	for(int i=1; i<=6; i++)
	{
		w_clim0.Format("%d", (i-1)*20);		
		dc.TextOut(10, 20+(i-1)*120, w_clim0);
	}
	//dc.TextOut(100, 600, "cm");

	dc.SetViewportOrg (0, 525); //profile note
	dc.SetViewportExt(365, 620);//570);

	//dc.FillRect(rectClient, &brush0);

	dc.FillSolidRect(700, 50, 150, 50, RGB(0,200,0)); //biomass
	dc.FillSolidRect(700, 130, 150, 50, RGB(150,50,0)); // stab
	dc.FillSolidRect(700, 210, 150, 50, RGB(100,100, 255)); //litter
	dc.FillSolidRect(700, 290, 150, 50, RGB(0,50, 155)); //humads
	dc.FillSolidRect(700, 370, 150, 50, RGB(100, 50, 155)); //humus
	dc.FillSolidRect(700, 450, 150, 5, RGB(255, 255, 0)); //nitrate

	dc.SetTextColor(RGB(150,150,150));
	w_clim0 = "crop";
	dc.TextOut(25, 5, w_clim0);
	w_clim0 = "stub";
	dc.TextOut(25, 85, w_clim0);
	w_clim0 = "litter";
	dc.TextOut(25, 165, w_clim0);
	w_clim0 = "humads";
	dc.TextOut(25, 245, w_clim0);
	w_clim0 = "humus";
	dc.TextOut(25, 325, w_clim0);
	w_clim0 = "available N";
	dc.TextOut(25, 405, w_clim0);

	//dc.SelectObject(pOldPen);			//return original pen
	dc.SelectObject(pOldBrush);	

}

void class_model::paint(MODEL_LINK_INFO* pLinkInfo, int MODE, int c_ViewMode, char* cropping_system)
{

		CWnd* pDC = pLinkInfo->pWnd;
		CDC& dc = *(pLinkInfo->pDC);

		CRect rectClient;
		pDC->GetClientRect(rectClient);

		dc.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
		dc.SetWindowExt(1500, 3000);
			
		CPen *pOldPen = NULL;

		//dc.SetViewportOrg (0,0); //notes
		//dc.SetViewportExt(365, 400);

		dc.SetTextColor(RGB(200,200,200));
		CString w_clim0;

		int x2, y2, z2, a2, b2, c2, Wf2[8], Wg2[8], lw2, Wfw2[8], rf2, fp2, Wfz2[8], We2[8], Wd2[8];
		int Wh2[10], i2, ii2, j2, k2, l2, m2, n2, o2, p2, q2, s2, t2, w2, v2, aa2, bb2, cc2;
		int i, dd2, ee2;
		float total_NH4=0.0, total_NO3=0.0;
		CString CName;
		
		if(jday==1) 
		{
			yd=0; x1=0; y1=0; z1=0; a1=0; b1=0; c1=0;  rf1=0; fp1=0;
			wi1=0; ii1=0; j1=0; k1=0; l1=0; m1=0; n1=0; o1=0; p1=0; q1=0; s1=0; t1=0; w1=0; u1=0; v1=0; aa1=0; bb1=0;
			cc1=0; lw1=0; hh1=0; dd1=0; ee1=0; ww1=0; pp_crop=0; pp_stub=0;

			for(int zx=0; zx<=7; zx++)
			{
				Wf1[zx]=0; Wg1[zx]=0; Wfw1[zx]=0;
				Wfz1[zx]=0; We1[zx]=0; Wd1[zx]=0;
				//if(zx<3) 
				Wh1[zx]=0;
			}

			y1 = (int) (325 - air_temp * 7);
			z1 = (int) (precipitation * 2000);
			a1 = (int) (650 - snow_pack * 1000);
			b1 = (int) (650 - (day_transp+day_evapor) * 10000);	
			c1 = (int) (650 - day_evapor * 10000);

			CPen  Pen1(PS_SOLID, 1, RGB(100,100,100));
			pOldPen = dc.SelectObject(&Pen1);		
			dc.MoveTo(0, 325);
			dc.LineTo(730, 325);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
		}

		
				
		x2 = jday*2;
		
		dc.SetViewportOrg (0,0); //notes
		dc.SetViewportExt(365, 350);
		dc.FillSolidRect(345, 345, 150, 125, RGB(0,0,0));
		w_clim0.Format("%d", jday);//day positioning in graphic interface
		dc.TextOut(350, 350, w_clim0);

		/*
		 dc.SetViewportOrg(0, 0); //notes
		dc.SetViewportExt(365, 400);
		dc.FillSolidRect(345, 395, 150, 125, RGB(0, 0, 0));
		w_clim0.Format("%d", jday);//day positioning in graphic interface
		dc.TextOut(350, 400, w_clim0);
		*/

		// climate ///////////////////////////////////
		dc.SetViewportOrg (250,0); //climate
		dc.SetViewportExt(1130, 580);	
			
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
		z2 = (int) (precipitation * 2000);

		Pen1.CreatePen(PS_SOLID, 1, RGB(180,180,255));
		pOldPen = dc.SelectObject(&Pen1);
		dc.MoveTo(x1, 0);
		dc.LineTo(x1, z2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();

		z1 = z2;

		//snowpack		
		a2 = (int) (650 - snow_pack * 2500);
		
		Pen1.CreatePen(PS_SOLID, 1, RGB(255,255,255));
		pOldPen = dc.SelectObject(&Pen1);		
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, a2);	
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();		

		a1 = a2;

		//evapotranspiration
		b2 = (int) (650 - (day_transp+day_evapor) * 10000);	
		
		Pen1.CreatePen(PS_SOLID, 1, RGB(100,0,250));
		pOldPen = dc.SelectObject(&Pen1);	
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, b2);	
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	

		b1 = b2;

		//evaporation
		c2 = (int) (650 - day_evapor * 10000);
		Pen1.CreatePen(PS_SOLID, 1, RGB(250,0,250));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, c2);	
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	

		c1 = c2;

		// plant ///////////////////////////////////
		dc.SetViewportOrg (250,127); 
		dc.SetViewportExt(1130, 580);
		float STUB = stub1+stub2+stub3;
		float pfl=0.05f;
		if(LandUse==6) pfl = 0.003;

		for(cwc=1;cwc<=CropNumbers;cwc++)
		{		
		if(seed[cwc]>0)
		{
			if(seed[cwc]==1||jday==1) 
			{
				Wd1[cwc] = (int) (650 - day_nup[cwc]*50);
				We1[cwc] = (int) (650 - (Leaf_Wt[cwc]+Stem_Wt[cwc]+Root_Wt[cwc]+Grain_Wt[cwc])*pfl);
				Wf1[cwc] = (int) (650 - (Leaf_Wt[cwc]+Stem_Wt[cwc]+Root_Wt[cwc])*pfl);
				Wfz1[cwc] = (int) (650 - (Stem_Wt[cwc]+Root_Wt[cwc])*pfl);
				Wg1[cwc] = (int) (150 - (day_DWater[cwc])*100);//day_DWater[cwc]
				Wh1[cwc] = (int) (280 - (N_stress[cwc])*100);
				//hh1 = (int) (650 - (lai[cwc])*80);
			}

			if(seed[cwc]==1||(WinterCropFlag[cwc]==1&&jday==1)) 
			{
				dc.SetTextColor(RGB(250,250,250));
				dc.SetBkMode(TRANSPARENT);
				//if(crop[cwc]==20)
				/*if(wetland_flag==1)
				{
					if(WaterControl==1) CName.Format("Rainfed-rice");
					else CName.Format("%s", crop_name[cwc]);//"Irrigated-rice");
				}
				else*/
					
				CName.Format("%s", crop_name[cwc]);
				dc.TextOut(x1, 250, CName);
			}

			We2[cwc] = (int) (650 - (Leaf_Wt[cwc]+Stem_Wt[cwc]+Root_Wt[cwc]+Grain_Wt[cwc])*pfl);
			Pen1.CreatePen(PS_SOLID, 1, RGB(250,200,50));
			pOldPen = dc.SelectObject(&Pen1);
			
			dc.MoveTo(x1, 650);
			dc.LineTo(x1, We2[cwc]);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			We1[cwc] = We2[cwc];
		
			//total shoots (crop)
			Wf2[cwc] = (int) (650 - (Leaf_Wt[cwc]+Stem_Wt[cwc]+Root_Wt[cwc])*pfl);
			Pen1.CreatePen(PS_SOLID, 1, RGB(10,250,50));
			pOldPen = dc.SelectObject(&Pen1);
		
			dc.MoveTo(x1, 650);
			dc.LineTo(x1, Wf2[cwc]);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			Wf1[cwc] = Wf2[cwc];

			//total leaves (crop)
			//f2 = (int) (650 - (Leaf_Wt[cwc]+Stem_Wt[cwc]+Root_Wt[cwc]+STUB)*pfl);
			Wfz2[cwc] = (int) (650 - (Stem_Wt[cwc]+Root_Wt[cwc])*pfl);
			Pen1.CreatePen(PS_SOLID, 1, RGB(5,125,25));
			pOldPen = dc.SelectObject(&Pen1);
	
			dc.MoveTo(x1, 650);
			dc.LineTo(x1, Wfz2[cwc]);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			Wfz1[cwc] = Wfz2[cwc];

			//root (crop)
			//fw2 = (int) (650 - (Root_Wt[cwc]+STUB)*pfl);
			Wfw2[cwc] = (int) (650 - (Root_Wt[cwc])*pfl);
			Pen1.CreatePen(PS_SOLID, 1, RGB(95,125,75));
			pOldPen = dc.SelectObject(&Pen1);
		
			dc.MoveTo(x1, 650);
			dc.LineTo(x1, Wfw2[cwc]);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			Wfw1[cwc] = Wfw2[cwc];	

			//water stress
			Wg2[cwc] = (int) (150 - (day_DWater[cwc])*100);//day_DWater[cwc]
			Pen1.CreatePen(PS_SOLID, 1, RGB(150,150,255));
			pOldPen = dc.SelectObject(&Pen1);
		
			dc.MoveTo(x1, Wg1[cwc]);
			dc.LineTo(x2, Wg2[cwc]);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			Wg1[cwc] = Wg2[cwc];

			//N stress
			Wh2[cwc] = (int) (280 - (N_stress[cwc])*100);
			Pen1.CreatePen(PS_SOLID, 1, RGB(150, 50, 0));
			pOldPen = dc.SelectObject(&Pen1);
			
			dc.MoveTo(x1, Wh1[cwc]);
			dc.LineTo(x2, Wh2[cwc]);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			Wh1[cwc] = Wh2[cwc];

			//N uptake (crop + weeds)
			Wd2[cwc] = (int) (650 - day_nup[cwc]*50);
			if(Wd2[cwc]>0)
			{
				Pen1.CreatePen(PS_SOLID, 1, RGB(220,250,55));
				pOldPen = dc.SelectObject(&Pen1);
	
				dc.MoveTo(x1, Wd1[cwc]);
				dc.LineTo(x2, Wd2[cwc]);
				dc.SelectObject(pOldPen);
				Pen1.DeleteObject();
				Wd1[cwc] = Wd2[cwc];
			}

		}
	}

	//stuble
		fp2 = (int) (650 - (STUB)*pfl);
		Pen1.CreatePen(PS_SOLID, 1, RGB(255,255,170));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, fp2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		fp1 = fp2;

		if(fert_flag==1) dc.FillSolidRect(x2, 15, 4, 50, RGB(0,250, 0));
		if(manuFlag==1) dc.FillSolidRect(x2, 15, 4, 50, RGB(250,250, 0));
		if(grazFlag==1) dc.FillSolidRect(x2, 20, 4, 23, RGB(70,150, 100));
		if(till_flag==1) dc.FillSolidRect(x2, 15, 4, 50, RGB(150,50, 200));
	
		//soil /////////////////////////////////////////////////
		dc.SetViewportOrg (250,255); //soil
		dc.SetViewportExt(1130, 580);
		int L05 = (int)(0.05/h[1]);
		int L10 = (int)(0.1/h[1]);
		int L20= (int)(0.2/h[1]);
		int L30 = (int)(0.3/h[1]);
	
		total_NH4 = 0.0;
		total_NO3 = 0.0;

		for (i=1; i<=q; i++)
		{
			total_NH4 += nh4[i]+clay_nh4[i];//+urea[i];
			total_NO3 += no3[i];
		}

		float WWTT=day_WT;
		if(day_WT<-1.0) WWTT = -1.0;

		if(jday==1) 
		{
			wi1 = (int) (650 - day_wfps[L05]*500);
			ii1 = (int) (325 - WWTT*350);
			j1 = (int) (200 - Eh000*0.25);	
			k1 = (int) (325 - (temp[L05])*7);
			//l1 = (int) (325 - (temp[L30])*7);
			m1 = (int) (650 - (total_ice)*1000);	
			//m1 = (int) (650 - day_clay_N);
			n1 = (int) (650 - (total_NH4)*2.5);
			l1 = (int) (650 - (total_NO3)*2.5);
			lw1 = (int) (650 - (day_leach_water)*10000);
			//rf1 = (int) (600 - RainfedDepth*500);

/*			CPen  Pen1(PS_SOLID, 1, RGB(100,100,100));
			pOldPen = dc.SelectObject(&Pen1);		
			dc.MoveTo(0, 325);
			dc.LineTo(730, 325);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();

			Pen1.CreatePen(PS_SOLID, 1, RGB(0,50,100));
			pOldPen = dc.SelectObject(&Pen1);		
			dc.MoveTo(0, 150);
			dc.LineTo(730, 150);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
*/
		}

		//soil moisture

		i2 = (int) (650 - (day_wfps[L05])*500);
		Pen1.CreatePen(PS_SOLID, 1, RGB(20,200,250));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, wi1);
		dc.LineTo(x2, i2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		wi1 = i2;

		//ii2 = (int) (650 - (day_wfps[L15])*500);

		ii2 = (int) (325 - (WWTT)*350);
		Pen1.CreatePen(PS_SOLID, 2, RGB(0,0,255));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, ii1);
		dc.LineTo(x2, ii2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		ii1 = ii2;

		//soil Eh

		//j2 = (int) (325 - (Eh_000 * 0.25));

		j2 = (int) (200 - (Eh000 * 0.25));
		Pen1.CreatePen(PS_SOLID, 1, RGB(150,150,200));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, j1);
		dc.LineTo(x2, j2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		j1 = j2;
	
		//soil temperature
		k2 = (int) (325 - temp[L10]*7);	
		Pen1.CreatePen(PS_SOLID, 1, RGB(150,50,0));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, k1);
		dc.LineTo(x2, k2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		k1 = k2;

	/*	l2 = (int) (325 - (temp[L30])*7);
		Pen1.CreatePen(PS_SOLID, 1, RGB(150,150,0));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, l1);
		dc.LineTo(x2, l2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		l1 = l2;*/

		//soil ice
		m2 = (int) (650 - (total_ice)*1000);
		//m2 = (int) (650 - (day_clay_N-base_clay_N));
		//m2 = (int) (650 - (WaterPool)*5000);
		//m2 = (int) (650 - (day_leach_NO3)*100.0);
				
		Pen1.CreatePen(PS_SOLID, 1, RGB(180,180,255));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, m2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		m1 = m2;

		//leached water
		lw2 = (int) (650 - (day_leach_water)*10000);

		if(lw2<0) lw2=0;
		{
		Pen1.CreatePen(PS_SOLID, 1, RGB(0,100,250));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, 650);
		dc.LineTo(x1, lw2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		lw1 = lw2;
		}

/*		//water table depth
		rf2 = (int) (day_WT*500);

		Pen1.CreatePen(PS_SOLID, 1, RGB(0,250,250));
		pOldPen = dc.SelectObject(&Pen1);
	
		dc.MoveTo(x1, 10);
		dc.LineTo(x1, rf2+10);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();	
		rf1 = rf2;
*/
		//soil NO3- + NH4+
	
		//n2 = (int) (650 - ((total_NH4+day_clay_N) * 2.5));
		n2 = (int) (650 - ((total_NH4) * 2.5));
		if(n2<0) n2=0;
		
		Pen1.CreatePen(PS_SOLID, 1, RGB(255,0,0));
		pOldPen = dc.SelectObject(&Pen1);

		dc.MoveTo(x1, n1);
		dc.LineTo(x2, n2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();
		n1 = n2;

		l2 = (int) (650 - (total_NO3 * 2.5));
		if(l2<0) l2=0;
		
		Pen1.CreatePen(PS_SOLID, 1, RGB(255,255,0));
		pOldPen = dc.SelectObject(&Pen1);

		dc.MoveTo(x1, l1);
		dc.LineTo(x2, l2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();
		l1 = l2;
		
	
		
		//microbial activity//////////////////////////////////////////////////
		dc.SetViewportOrg (250,383); 
		dc.SetViewportExt(1130, 580);
		if(jday==1) 
		{
			//o1 = (int) (650 - (day_co2 + day_rco2)*10);
			o1 = (int) (650 - (soil_hete_CO2)*1.5);			
			bb1 = (int) (650 - ch4_prod*10.0);
			cc1 = (int) (650 - ch4_day_oxid*10.);
			v1 = (int) (550 - day_soil_nitrify*50.);
			aa1 = (int) (650 - day_soil_denitrification*150.);
		}
		
	
		//CO2
		//o2 = (int) (650 - (day_co2 + day_rco2)*5);
		o2 = (int) (650 - soil_hete_CO2*1.5);
		//o2 = (int) (650 - (F_time)*500);
		//if(o2>=0)
		{
		Pen1.CreatePen(PS_SOLID, 1, RGB(150,0,0));//(250,250,255));
		pOldPen = dc.SelectObject(&Pen1);
		
		dc.MoveTo(x1, o1);
		dc.LineTo(x2, o2);
		dc.SelectObject(pOldPen);
		Pen1.DeleteObject();
		o1 = o2;
		}

		//Daily methane production rate
		if(ch4_prod>0.0)
		{
			bb2 = (int) (650 - ch4_prod*10);
			if(bb2<0) bb2=0;
			if(bb2>0)
			{
				Pen1.CreatePen(PS_SOLID, 2, RGB(0,100,200));
				pOldPen = dc.SelectObject(&Pen1);

				dc.MoveTo(x1, bb1);
				dc.LineTo(x2, bb2);
				dc.SelectObject(pOldPen);
				Pen1.DeleteObject();
				bb1 = bb2;
			}
		}

		//Daily methane oxidation rate
		if(ch4_day_oxid>0.1)
		{
		cc2 = (int) (650 - ch4_day_oxid*10);
		
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(0,150,150));
			pOldPen = dc.SelectObject(&Pen1);

			dc.MoveTo(x1, cc1);
			dc.LineTo(x2, cc2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			cc1 = cc2;
		}
		}

		//Daily nitrification rate
		v2 = (int) (550 - day_soil_nitrify*20);
		if(v2<0) v2=0;
		//if(v2>0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(150,120,5));
			pOldPen = dc.SelectObject(&Pen1);

			dc.MoveTo(x1, v1);
			dc.LineTo(x2, v2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			v1 = v2;
		}

		//Daily denitrification rate
		aa2 = (int) (650 - (day_soil_denitrification)*20);
		if(aa2<0) aa2=0;
		//if(aa2>0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(100,255,180));
			pOldPen = dc.SelectObject(&Pen1);

			dc.MoveTo(x1, aa1);
			dc.LineTo(x2, aa2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			aa1 = aa2;
		}


		//gas flux ///////////////////////////////////////////////////////////
		dc.SetViewportOrg (250,523); //gas 2
		dc.SetViewportExt(1130, 400);
		if(jday==1) 
		{
			s1 = (int) (650 - (day_soil_an_n2o + day_soil_n2)*1000);
			t1 = (int) (650 - (day_soil_an_n2o)*1000);	
			w1 = (int) (250 - (day_soil_an_no)*1000);
			p1 = (int) (650 - (day_soil_nh3 + day_vol_nh3)*100);	
			q1 = (int) (650 - (day_ch4)*50);

		}

		//NH3
		float T_NH3 = day_soil_nh3 + day_vol_nh3;
		p2 = (int) (650 - T_NH3*100);
		if(p2<0) p2=0;
		//if(T_NH3>0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(250,200,20));
			pOldPen = dc.SelectObject(&Pen1);

			dc.MoveTo(x1, p1);
			dc.LineTo(x2, p2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			p1 = p2;
		}

		//N2O + N2
		float T_DN=day_soil_an_n2o + day_soil_n2;
		s2 = (int) (650 - T_DN*1000);	
		if(s2<0) s2=0;
		if(T_DN>0.0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(255,255,255));
			pOldPen = dc.SelectObject(&Pen1);
			
			dc.MoveTo(x1, 650);
			dc.LineTo(x1, s2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			s1 = s2;
		}

		//N2O 
		t2 = (int) (650 - day_soil_an_n2o*1000);
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

		//NO 
		w2 = (int) (250 - day_soil_an_no*1000);
		if(w2<0) w2=0;
		if(day_soil_an_no>0.0)
		{
			Pen1.CreatePen(PS_SOLID, 1, RGB(0,100,250));
			pOldPen = dc.SelectObject(&Pen1);
			
			dc.MoveTo(x1, 250);
			dc.LineTo(x1, w2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			w1 = w2;
		}

		//CH4
		q2 = (int) (650 - (day_ch4)*50);
		if(q2<0) q2=0;	
		if(day_ch4>0.0)
		{
			Pen1.CreatePen(PS_SOLID, 2, RGB(250,100,155));
			pOldPen = dc.SelectObject(&Pen1);
			dc.MoveTo(x1, q1);
			dc.LineTo(x1, q2);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();	
			q1 = q2;
		}

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

		//////////////////////////////////
		dc.SetViewportOrg (0,85); //soil profile
		dc.SetViewportExt(358, 2000);
	
		int p_crop = (int)((Leaf_Wt[1]+Stem_Wt[1]+Grain_Wt[1]+Leaf_Wt[2]+Stem_Wt[2]+Grain_Wt[2]+Leaf_Wt[3]+Stem_Wt[3]+Grain_Wt[3])*0.1);
		int p_stub = (int)((stub1+stub2+stub3)*0.1);
		
		dc.FillSolidRect(120, 35, 910, 600, RGB(0,0,0));

/*		if(p_crop==0)
			dc.FillSolidRect(5, 5, pp_crop+10, 15, RGB(0,0,0));//pp_crop+10
		else
			dc.FillSolidRect(5, 5, p_crop, 15, RGB(0,200,0));

		if(p_stub==0)
			dc.FillSolidRect(5, 25, pp_stub+10, 15, RGB(0,0,0));
		else
			dc.FillSolidRect(5, 25, p_stub, 15, RGB(150,50,0));

		pp_crop = p_crop;
		pp_stub = p_stub;		
*/
		int nH = (int) (600/q);
		int yy = 0, yy0;
				
		int NO30 = (int)((no3[1]+nh4[1])*50);

		{
		for(int i=1; i<=q; i++)
		{
			if(i==1) yy = 34;
			else yy += (yy0+2);
			
			yy0 = (int)(h[i] * 475.0);//+ (i-1)*nH+30;
			
			float Fdd = 20000.0 / mmm[i];
			if(st[i]>=12) Fdd = 0.025;

			//if(dphum[1]>15000.0) Fdd = 450.0 / dphum[1];

			//max 450

			int p_litter = (int) ((rcvl[i]+rcl[i]+rcr[i]) * Fdd);
            int p_humads = (int) ((CRB1[i] + CRB2[i] + crhl[i] + crhr[i]) * Fdd);
            int p_humus = (int) ((dphum[i]+inert_C[i]) * Fdd);
			int p_soc = (int)(p_litter + p_humads + p_humus);

			//dc.FillSolidRect(100, yy, pp_soc[i], nH-5, RGB(200,0,0));
			dc.FillSolidRect(120, yy, p_soc, yy0, RGB(100,100, 255));
			dc.FillSolidRect(120, yy, p_humads+p_humus, yy0, RGB(0,50, 155));
			dc.FillSolidRect(120, yy, p_humus, yy0, RGB(100, 50, 155));
		
			//pp_soc[i] = p_soc;

			int NO3 = (int)((no3[i]+nh4[i])*50);
			if(NO3>900) NO3=900;

			//if(i==1) NO30 = NO3;
			Pen1.CreatePen(PS_SOLID, 1, RGB(255,255,0));
			pOldPen = dc.SelectObject(&Pen1);
			dc.MoveTo(120, yy+5);
			dc.LineTo(120+NO3, yy+5);
			dc.SelectObject(pOldPen);
			Pen1.DeleteObject();
			//NO30 = NO3;
		
		}	
		}

		//int ax = q*nH+30;
		//int p_leachN = (int) (day_clay_N * 1.0);
		//dc.FillSolidRect(5, ax, 500, 15, RGB(0,0,0));
		//dc.FillSolidRect(5, ax, p_leachN, nH-5, RGB(100, 100, 25));
		
}

/*
void class_model::crop_note(MODEL_LINK_INFO* pLinkInfo, char *cropName, int MODE, int c_ViewMode, int landuse)
{
// changed by liujm
//	POSITION pos = pDoc->GetFirstViewPosition();
//	CView* pDC = pDoc->GetNextView( pos );
//	CClientDC dc(pDC);
	CWnd* pDC = pLinkInfo->pWnd;
	CDC& dc = *(pLinkInfo->pDC);

	CRect rectClient;
	pDC->GetClientRect(rectClient);

	dc.SetBkMode(TRANSPARENT);
	
	dc.SetViewportOrg (0,0); //notes
	dc.SetViewportExt(365, 400);

	dc.SetTextColor(RGB(200,200,200));
	CString w_clim0;
	
	if(MODE==0 || (MODE==1&&c_ViewMode==1))
	{
		dc.FillSolidRect(0, 140, 600, 100, RGB(0,0,100));
		w_clim0.Format ("%s", cropName);
		dc.TextOut(250, 130, w_clim0);
	}
	else 
	{
		dc.FillSolidRect(5, 300, 1100, 300, RGB(0,0,0));
		w_clim0.Format ("  Crop system:%3d  %s", landuse, cropName);
		dc.TextOut(10, 400, w_clim0);
	}
}
*/
