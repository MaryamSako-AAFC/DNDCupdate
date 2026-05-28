#include "stdafx.h"
#include "RunPaths.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

void class_model::map_county(MODEL_LINK_INFO* pLinkInfo, char *CountryName, char *ProvinceName, long int map_ID, 
							 int fill_color, int RegionCode, int CountryCode, int StateCode)
{
	float qq, xx, yy;
	int RR, GG, BB;
	char map_address[200];
	FILE *Fmap;

// changed by liujm
//	POSITION canves = pDoc->GetFirstViewPosition();
//	CView* pDC = pDoc->GetNextView( canves );
//	CClientDC art(pDC);
	CWnd* pDC = pLinkInfo->pWnd;
	CDC& art = *(pLinkInfo->pDC);

	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetViewportOrg (0,0); //notes
	art.SetViewportExt(1500, 2990);

	CBrush Brush1(RGB(220,220,220));
	//art.FillRect(rectClient, &Brush1);
	Brush1.DeleteObject();

	CString MapName;

	if(RegionCode==1&&CountryCode==4)
	{
		MapName.Format("ChinaC%ld", map_ID);
	}else if(RegionCode==3&&CountryCode==2)
	{
		MapName.Format("%ld", map_ID);
	}
	else
		MapName.Format("C%ld", map_ID);


	/*if(RegionCode==0) MapName.Format("C%ld", map_ID);
	else if(RegionCode==1&&CountryCode==4) 
	{
		MapName.Format("ChinaP%ld", map_ID);
	}
	else if(RegionCode==1&&CountryCode==17) MapName.Format("P-%ld.txt", map_ID);
	else{}*/

	sprintf(map_address, "%sDatabase\\%s\\lib_map\\%s", ROOTDIR, CountryName, MapName);
		Fmap = fopen(map_address, "r");
		if(Fmap==NULL)
		{
			CString Error;
			Error.Format("Can not find file %s", map_address);
			AfxMessageBox(Error);
			exit(0);
		}
		
		CPoint map_data[15000];
		long int map_IDb;
		int pairs, mm;

		map_scale(RegionCode, CountryCode, StateCode, &qq, &xx, &yy);

		fscanf(Fmap, "%ld  %d", &map_IDb, &pairs);	

		for(mm=0; mm<pairs; mm++)
		{
				float Da, Db;
		
				fscanf(Fmap, "%f  %f", &Da, &Db);	
				
				if(RegionCode==0||(RegionCode==1&&CountryCode==4)) //Shangrila, China
				{
					map_data[mm].x  = (int)((xx + (Da-200.0)) * 13 * qq);
					map_data[mm].y = (int)((yy - Db) * 17 * qq);
				}
				else if(RegionCode==3&&CountryCode==2)//USA
				{
					map_data[mm].x  = (int)((xx + Da) * 13 * qq);
					map_data[mm].y = (int)((yy - Db) * 17 * qq);

				}
				else if(RegionCode==1&&CountryCode==17)//Thailand
				{
					map_data[mm].x = 1400 + (int)((Da - 120) * 38);
					map_data[mm].y = 50 - (int)((Db - 20) * 38);
				}
				else {}
				
		}
				
		CPen *pOldPen = NULL;				//create a point for pen
		CBrush *pOldBrush = NULL;			//create a point for brush

		CPen Pen1(PS_SOLID, 1, RGB(250,250,250));	//define a pen

		if(fill_color==0) 
			{
				RR = 250;
				GG = 250;
				BB = 50;
			}
			else 
			{
				RR = 250;
				GG = 250;
				BB = 50;
			}
				
			CBrush Brush2(RGB(RR,GG,BB));		//define a brush

			pOldPen = art.SelectObject(&Pen1);	//select the pen into pen point
			pOldBrush = art.SelectObject(&Brush2);  //select the brush into brush point

			art.Polygon(map_data, pairs);				//draw poligon with the pen and brush

			art.SelectObject(pOldPen);			//return original pen into oen point
			art.SelectObject(pOldBrush);		//return original brush into brush point

			Pen1.DeleteObject();				//delete object
			Brush2.DeleteObject();

			fclose(Fmap);		
	

	//AfxMessageBox("");
	//exit(0);
	
}

void class_model::map_scale(int RegionCode, int country_code, int state_code, float *qq, float *xx, float *yy)
{
	if(RegionCode==0)//Shangrila
	{
		*qq = 4.0;
		*xx = 109.0;
		*yy = 30.0;
	}
	else if(RegionCode==1)//Asia
	{
		if(country_code==4)
		{
					if(state_code==0)//China
					{
						*qq = 1.0;
						*xx = 138.5;
						*yy = 55.0;
					}
					else if(state_code==1)//Beijing
					{
						*qq = 18.0;
						*xx = 86.0;
						*yy = 41.3;
					}
					else if(state_code==2)//Tianjin
					{
						*qq = 18.0;
						*xx = 85.0;
						*yy = 40.5;
					}
					else if(state_code==3)//Hebei
					{
						*qq = 5.0;
						*xx = 93.0;
						*yy = 43.0;
					}
					else if(state_code==4)//Shanxi
					{
						*qq = 5.0;
						*xx = 96.0;
						*yy = 41.5;
					}
					else if(state_code==5)//Inner Mongolia
					{
						*qq = 2.2;
						*xx = 105.0;
						*yy = 54.0;
					}
					else if(state_code==6)//Liaoning
					{
						*qq = 6.0;
						*xx = 86.0;
						*yy = 44.5;
					}
					else if(state_code==7)//Jilin
					{
						*qq = 6.0;
						*xx = 81.5;
						*yy = 47;
					}
					else if(state_code==8)//Heilongjiang
					{
						*qq = 3.5;
						*xx = 86;
						*yy = 54;
					}
					else if(state_code==9)//Shanghai
					{
						*qq = 18.0;
						*xx = 81.0;
						*yy = 32.0;
					}
					else if(state_code==10)//Jiangsu
					{
						*qq = 7.0;
						*xx = 87.0;
						*yy = 36.0;
					}
					else if(state_code==11)//Zhejiang
					{
						*qq = 7.0;
						*xx = 87.0;
						*yy = 32.0;
					}
					else if(state_code==12)//Anhui
					{
						*qq = 7.0;
						*xx = 89.0;
						*yy = 34.7;
					}
					else if(state_code==13)//Fujian
					{
						*qq = 7.0;
						*xx = 89.0;
						*yy = 28.7;
					}
					else if(state_code==14)//Jiangxi
					{
						*qq = 6.4;
						*xx = 91.0;
						*yy = 30.3;
					}
					else if(state_code==15)//Shandong
					{
						*qq = 7.0;
						*xx = 88.0;
						*yy = 39.0;
					}
					else if(state_code==16)//Henan
					{
						*qq = 6.0;
						*xx = 93.0;
						*yy = 37.0;
					}
					else if(state_code==17)//Hubei
					{
						*qq = 6.0;
						*xx = 96.0;
						*yy = 34.0;
					}
					else if(state_code==18)//Hunan
					{
						*qq = 6.0;
						*xx = 96.0;
						*yy = 30.5;
					}
					else if(state_code==19)//Guangdong
					{
						*qq = 6.0;
						*xx = 94.0;
						*yy = 26;
					}
					else if(state_code==20)//Guangxi
					{
						*qq = 6.0;
						*xx = 99.0;
						*yy = 27;
					}
					else if(state_code==22)//Guizhou
					{
						*qq = 6.0;
						*xx = 100.0;
						*yy = 30;
					}
					else if(state_code==21)//Sichuan
					{
						*qq = 4.0;
						*xx = 108.0;
						*yy = 35;
					}
					else if(state_code==23)//Yunnan
					{
						*qq = 4.0;
						*xx = 109.0;
						*yy = 30.0;
					}
					else if(state_code==24)//Tibet
					{
						*qq = 3.0;
						*xx = 126.0;
						*yy = 38.0;
					}
					else if(state_code==25)//Shaanxi
					{
						*qq = 4.5;
						*xx = 101.0;
						*yy = 40;
					}
					else if(state_code==26)//Gansu
					{
						*qq = 3.5;
						*xx = 113.0;
						*yy = 43.3;
					}
					else if(state_code==27)//Qinghai
					{
						*qq = 3.5;
						*xx = 117.0;
						*yy = 41;
					}
					else if(state_code==28)//Ningxia
					{
						*qq = 8;
						*xx = 100.0;
						*yy = 39.8;
					}
					else if(state_code==29)//Xinjiang
					{
						*qq = 2.0;
						*xx = 135.0;
						*yy = 52;
					}
					else if(state_code==30)//Hainan
					{
						*qq = 10.0;
						*xx = 94.0;
						*yy = 21;
					}
					else if(state_code==31)//Taiwan
					{
						*qq = 10.0;
						*xx = 83.0;
						*yy = 25.5;
					}
					else 
					{
						AfxMessageBox("Wrong province");
						exit(0);
					}
		}

		else if(country_code==17)
		{
			//map_data[mm].x = 1400 + (int)((Da - 120) * 38);
			//map_data[mm].y = 50 - (int)((Db - 20) * 38);
			*qq = 38.0;
			*xx = 1400.0;
			*yy = 50.0;
		}
		else
		{}
	
	}
	else if(RegionCode==3)//North America
	{
		if(country_code==2)
		{
					if(state_code==0)//USA
					{
						*qq = 1.0;
						*xx = 143.0;
						*yy = 58.0;
					}
					else if(state_code==55)//WI
					{
						*qq = 6.0;
						*xx = 96.0;
						*yy = 48.0;
					}
					else if(state_code==27)//MN
					{
						*qq = 5.0;
						*xx = 102.0;
						*yy = 50.0;
					}
					else if(state_code==38)//ND
					{
						*qq = 6.0;
						*xx = 106.0;
						*yy = 51.0;
					}
					else if(state_code==30)//MO
					{
						*qq = 5.0;
						*xx = 117.0;
						*yy = 51.0;
					}
					else if(state_code==16)//ID
					{
						*qq = 5.0;
						*xx = 122.0;
						*yy = 49.2;
					}
					else if(state_code==53)//WA
					{
						*qq = 6.0;
						*xx = 127.0;
						*yy = 51.0;
					}
					else if(state_code==41)//OR
					{
						*qq = 5.0;
						*xx = 128.0;
						*yy = 48.0;
					}
					else if(state_code==6)//CA
					{
						*qq = 3.6;
						*xx = 132.0;
						*yy = 42.5;
					}
					else if(state_code==32)//NV
					{
						*qq = 5.0;
						*xx = 125.0;
						*yy = 42.5;
					}
					else if(state_code==49)//UT
					{
						*qq = 5.0;
						*xx = 120.0;
						*yy = 43.0;
					}
					else if(state_code==4)//AR
					{
						*qq = 5.0;
						*xx = 120.0;
						*yy = 38.0;
					}
					else if(state_code==35)//NM
					{
						*qq = 5.0;
						*xx = 115.0;
						*yy = 38.0;
					}
					else if(state_code==8)//CO
					{
						*qq = 5.0;
						*xx = 114.0;
						*yy = 43.0;
					}
					else if(state_code==56)//WY
					{
						*qq = 5.0;
						*xx = 115.0;
						*yy = 46.0;
					}
					else if(state_code==46)//SD
					{
						*qq = 6.0;
						*xx = 107.0;
						*yy = 48.0;
					}
					else if(state_code==31)//NE
					{
						*qq = 6.0;
						*xx = 107.0;
						*yy = 45.0;
					}
					else if(state_code==20)//KA
					{
						*qq = 6.0;
						*xx = 105.0;
						*yy = 42.0;
					}
					else if(state_code==40)//OK
					{
						*qq = 6.0;
						*xx = 105.0;
						*yy = 38.0;
					}
					else if(state_code==48)//TX
					{
						*qq = 3.5;
						*xx = 110.0;
						*yy = 36.5;
					}
					else if(state_code==19)//IO
					{
						*qq = 6.0;
						*xx = 100.0;
						*yy = 45.0;
					}
					else if(state_code==29)//MI
					{
						*qq = 6.0;
						*xx = 100.0;
						*yy = 42.0;
					}
					else if(state_code==5)//AK
					{
						*qq = 7.0;
						*xx = 98.0;
						*yy = 38.0;
					}
					else if(state_code==22)//LA
					{
						*qq = 7.0;
						*xx = 98.0;
						*yy = 34.0;
					}
					else if(state_code==17)//IL
					{
						*qq = 6.0;
						*xx = 96.0;
						*yy = 43.0;
					}
					else if(state_code==17)//IL
					{
						*qq = 6.0;
						*xx = 96.0;
						*yy = 43.0;
					}
					else if(state_code==28)//MS
					{
						*qq = 6.0;
						*xx = 96.0;
						*yy = 36.0;
					}
					else if(state_code==1)//AL
					{
						*qq = 6.0;
						*xx = 94.0;
						*yy = 36.0;
					}
					else if(state_code==13)//GA
					{
						*qq = 6.0;
						*xx = 90.0;
						*yy = 36.0;
					}
					else if(state_code==26)//MI
					{
						*qq = 6.0;
						*xx = 91.0;
						*yy = 47.0;
					}
					else if(state_code==18)//IN
					{
						*qq = 7.0;
						*xx = 91.0;
						*yy = 42.0;
					}
					else if(state_code==39)//OH
					{
						*qq = 7.0;
						*xx = 88.0;
						*yy = 43.0;
					}
					else if(state_code==21)//KE
					{
						*qq = 7.0;
						*xx = 91.0;
						*yy = 40.0;
					}
					else if(state_code==47)//TN
					{
						*qq = 7.0;
						*xx = 91.0;
						*yy = 38.0;
					}
					else if(state_code==37)//NC
					{
						*qq = 7.0;
						*xx = 86.0;
						*yy = 38.0;
					}
					else if(state_code==45)//SC
					{
						*qq = 8.0;
						*xx = 86.0;
						*yy = 35.5;
					}
					else if(state_code==12)//FL
					{
						*qq = 6.0;
						*xx = 90.0;
						*yy = 31.3;
					}
					else if(state_code==51)//VA
					{
						*qq = 7.0;
						*xx = 86.0;
						*yy = 40.0;
					}
					else if(state_code==54)//WV
					{
						*qq = 7.0;
						*xx = 86.0;
						*yy = 42.0;
					}
					else if(state_code==42)//PA
					{
						*qq = 7.0;
						*xx = 83.0;
						*yy = 43.0;
					}
					else if(state_code==36)//NY
					{
						*qq = 7.0;
						*xx = 81.0;
						*yy = 45.5;
					}
					else if(state_code==50)//VM
					{
						*qq = 10.0;
						*xx = 77.0;
						*yy = 45.5;
					}
					else if(state_code==33)//NH
					{
						*qq = 10.0;
						*xx = 76.0;
						*yy = 45.5;
					}
					else if(state_code==23)//ME
					{
						*qq = 8.0;
						*xx = 74.0;
						*yy = 47.5;
					}
					else if(state_code==25)//MA
					{
						*qq = 11.0;
						*xx = 75.0;
						*yy = 44.0;
					}
					else if(state_code==9)//CT
					{
						*qq = 11.0;
						*xx = 76.0;
						*yy = 43.0;
					}
					else if(state_code==44)//RI
					{
						*qq = 11.0;
						*xx = 75.0;
						*yy = 43.0;
					}
					else if(state_code==34)//NJ
					{
						*qq = 11.0;
						*xx = 78.0;
						*yy = 42.0;
					}
					else if(state_code==10)//DE
					{
						*qq = 11.0;
						*xx = 79.0;
						*yy = 41.0;
					}
					else if(state_code==24)//MD
					{
						*qq = 11.0;
						*xx = 81.0;
						*yy = 40.5;
					}
					else 
					{
						AfxMessageBox("Wrong state");
						exit(0);
					}
				}
	}

	
}

void class_model::map_state(MODEL_LINK_INFO* pLinkInfo, char *CountryName, char *ProvinceName, int databaseType, 
							int RegionCode, int country_code, int state_code)
{
	//int map_number;
	//if(CountryCode==0) map_number = 31;
	//else if(CountryCode==1) map_number = 130;

// changed by liujm
//	POSITION canves = pDoc->GetFirstViewPosition();
//	CView* pDC = pDoc->GetNextView( canves );
//	CClientDC art(pDC);
	CWnd* pDC = pLinkInfo->pWnd;
	CDC& art = *(pLinkInfo->pDC);

	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetViewportOrg (0,0); //notes
	art.SetViewportExt(1500, 2990);

	CBrush *pOldBrush = art.GetCurrentBrush();
	CBrush brush0;								//create a brush
	brush0.CreateSolidBrush(RGB(0,0,0));	//define the brush
	pOldBrush = art.SelectObject(&brush0);

	art.FillRect(rectClient, &brush0);	
	
	MappingCountry(pLinkInfo, CountryName, ProvinceName, RegionCode, country_code, state_code);
	
	//AfxMessageBox("");
	//exit(0);
/*	if(state_code==0&&country_code<5)
	{
		for(long int bbb=1; bbb<=56; bbb++)
		{
			if(databaseType==0)
			{
				if(country_code==0) sprintf(map_address, "%s\\%s\\lib_map\\ChinaP%ld", INPUTPATH1, CountryName, bbb);//map_ID
				else if(country_code==1) sprintf(map_address, "%s\\%s\\lib_map\\p-0%ld.txt", INPUTPATH1, CountryName, bbb);//map_ID
				else sprintf(map_address, "%s\\%s\\lib_map\\p-%ld.txt", INPUTPATH1, CountryName, bbb);//map_ID
			}
			else if(databaseType==1)
				sprintf(map_address, "%s\\%s\\lib_map\\gp-%ld.txt", INPUTPATH1, CountryName, bbb);//map_ID
			else {}

			Fmap = fopen(map_address, "r");
			if(Fmap==NULL)
			{
				
			}
			else
			{		
				CPoint map_data[15000];
				
				long int map_IDb;
				int pairs, mm;

				fscanf(Fmap, "%ld  %d", &map_IDb, &pairs);
				
				for(mm=0; mm<pairs; mm++)
				{
					float Da, Db;
					//if(fscanf(Fmap, "%f  %f", &Da, &Db) != 2) break;
					fscanf(Fmap, "%f  %f", &Da, &Db);

					if(CountryCode==0) //China
					{
						//map_data[mm].x = 700 + (int)(Da * 0.00015);
						//map_data[mm].y = 770 - (int)(Db * 0.00015);

						// for latitude/longitude system
						map_scale(CountryCode, state_code, &qq, &xx, &yy);						
						map_data[mm].x  = (int)((xx + (Da-200.0)) * 13 * qq);
						map_data[mm].y = (int)((yy - Db) * 17 * qq);
					}
					else if(CountryCode==1) //USA
					{
						map_scale(CountryCode, state_code, &qq, &xx, &yy);

						map_data[mm].x  = (int)((xx + Da) * 13 * qq);
						map_data[mm].y = (int)((yy - Db) * 17 * qq);
						//map_data[mm].x  = (int)((143.0 + Da) * 13);
						//map_data[mm].y = (int)((58.0 - Db) * 17);
					}
					else if(CountryCode==2) //Philippines
					{
						map_data[mm].x = 500 + (int)((Da - 120) * 38);
						map_data[mm].y = 50 - (int)((Db - 20) * 38);
					}
					else if(CountryCode==3) //Thailand
					{
						map_data[mm].x = 1400 + (int)((Da - 120) * 38);
						map_data[mm].y = 50 - (int)((Db - 20) * 38);
					}
					else if(CountryCode==4) //Indonesia
					{
						map_data[mm].x = 550 + (int)((Da - 120) * 20);
						map_data[mm].y = -100 - (int)((Db - 20) * 20);
					}
					else{}
				}

				CPen *pOldPen = NULL;				//create a point for pen
				CBrush *pOldBrush = NULL;			//create a point for brush

				CPen Pen1(PS_SOLID, 1, RGB(250,255,255));	//define a pen
				CBrush Brush1(RGB(50,50,50));		//define a brush

				pOldPen = art.SelectObject(&Pen1);	//select the pen into pen point
				pOldBrush = art.SelectObject(&Brush1);  //select the brush into brush point

				art.Polygon(map_data, pairs);				//draw poligon with the pen and brush

				art.SelectObject(pOldPen);			//return original pen into oen point
				art.SelectObject(pOldBrush);		//return original brush into brush point

				Pen1.DeleteObject();				//delete object
				Brush1.DeleteObject();

				fclose(Fmap);	
				
				//CString mz;
				//mz.Format("state %d  map %s", state_code, map_address);
				//AfxMessageBox(mz);
				//exit(0);
			}			
		}
			
		
	} //if(state_code != 0)
	else
*/

	
/*
		if(country_code==0)//draw China 
			sprintf(map_address, "%s\\%s\\lib_map\\ChinaP%d", INPUTPATH1, CountryName, state_code);
		else if(country_code==17)//draw Thailand 
			sprintf(map_address, "%s\\%s\\lib_map\\p-001.txt", INPUTPATH1, CountryName);//map_ID
		else
		{}
		
		Fmap = fopen(map_address, "r");
		if(Fmap==NULL)
		{
			CString Error;
			Error.Format("Can not find file %s", map_address);
			AfxMessageBox(Error);
			exit(0);	
			//return;
		}
		else
		{	
			CPoint map_data[15000];
				
			long int map_IDb;
			int pairs, mm;

			fscanf(Fmap, "%ld  %d", &map_IDb, &pairs);
					
			for(mm=0; mm<pairs; mm++)
			{
				

				//if(fscanf(Fmap, "%f  %f", &Da, &Db) != 2) break;
				fscanf(Fmap, "%f  %f", &Da, &Db);

				if(CountryCode==0) //China
				{
					// for latitude/longitude system
					map_scale(CountryCode, state_code, &qq, &xx, &yy);
					map_data[mm].x  = (int)((xx + (Da-200.0)) * 13 * qq);
					map_data[mm].y = (int)((yy - Db) * 17 * qq);
				}
				else if(CountryCode==1) //USA
				{					
					map_scale(CountryCode, state_code, &qq, &xx, &yy);
					map_data[mm].x  = (int)((xx + Da) * 13 * qq);
					map_data[mm].y = (int)((yy - Db) * 17 * qq);
				}
				
				else if(CountryCode==5) //Shangrila
					{
						
						map_scale(CountryCode, state_code, &qq, &xx, &yy);						
						map_data[mm].x  = (int)((xx + (Da-200.0)) * 13 * qq);
						map_data[mm].y = (int)((yy - Db) * 17 * qq);
					}
				else{}

			}

			CPen *pOldPen = NULL;				//create a point for pen
			CBrush *pOldBrush = NULL;			//create a point for brush

			CPen Pen1(PS_SOLID, 1, RGB(250,255,255));	//define a pen
			CBrush Brush1(RGB(50,50,50));		//define a brush

			pOldPen = art.SelectObject(&Pen1);	//select the pen into pen point
			pOldBrush = art.SelectObject(&Brush1);  //select the brush into brush point

			art.Polygon(map_data, pairs);				//draw poligon with the pen and brush

			art.SelectObject(pOldPen);			//return original pen into oen point
			art.SelectObject(pOldBrush);		//return original brush into brush point

			Pen1.DeleteObject();				//delete object
			Brush1.DeleteObject();
			fclose(Fmap);	
				
			//CString mz;
			//mz.Format("%d", state_code);
			//AfxMessageBox(mz);
			//exit(0);

		}
	}
					
*/				
				
}

void class_model::MappingCountry(MODEL_LINK_INFO* pLinkInfo, char *CountryName, char *ProvinceName, int RegionCode, int country_code, int state_code)
{
	char File5[200], map_address[200];
	FILE *Findex, *Fdata;
	int gridID, mapID, fID, pairs, mm;
	float Da, Db, qq, xx, yy;

// changed by liujm
//	POSITION canves = pDoc->GetFirstViewPosition();
//	CView* pDC = pDoc->GetNextView( canves );
//	CClientDC art(pDC);
	CWnd* pDC = pLinkInfo->pWnd;
	CDC& art = *(pLinkInfo->pDC);

	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetViewportOrg (0,0); //notes
	art.SetViewportExt(1500, 2990);

	CBrush *pOldBrush = art.GetCurrentBrush();
	CBrush brush0;								//create a brush
	brush0.CreateSolidBrush(RGB(0,0,0));	//define the brush
	pOldBrush = art.SelectObject(&brush0);

	art.FillRect(rectClient, &brush0);
	
	if((RegionCode==1&&country_code==4)||(RegionCode==3&&country_code==2))
		sprintf(File5, "%sDatabase\\%s\\GIS\\%s\\%s_5.txt", ROOTDIR, CountryName, ProvinceName, ProvinceName);
	else
		sprintf(File5, "%sDatabase\\%s\\GIS\\%s_5.txt", ROOTDIR, CountryName, ProvinceName);
	
	Findex = fopen(File5, "r");
		if(Findex==NULL)
		{
			CString Error;
			Error.Format("Can not open file %s", File5);
			AfxMessageBox(Error);
			exit(0);	
		}
	map_scale(RegionCode, country_code, state_code, &qq, &xx, &yy);
	for(;;)
	{
		if(fscanf(Findex, "%d %d", &gridID, &mapID) != 2) break;
		else
		{
			CPoint map_data[15000];
			CString MapName;
			if(RegionCode==0) MapName.Format("C%d", mapID);
			else if(RegionCode==1&&country_code==4) MapName.Format("ChinaC%d", mapID);
			else if(RegionCode==3&&country_code==2) MapName.Format("%d", mapID);
			else
			{}


			sprintf(map_address, "%sDatabase\\%s\\lib_map\\%s", ROOTDIR, CountryName, MapName);
			Fdata = fopen(map_address, "r");
			if(Fdata==NULL)
			{
				CString Error;
				Error.Format("Can not open file %s", map_address);
				AfxMessageBox(Error);
				exit(0);	
			}

			fscanf(Fdata, "%d %d", &fID, &pairs);
			for(mm=0; mm<pairs; mm++)
			{
				fscanf(Fdata, "%f  %f", &Da, &Db);				
				
				if(RegionCode==0||(RegionCode==1&&country_code==4)) //Shangrila, China
				{
					map_data[mm].x  = (int)((xx + (Da-200.0)) * 13 * qq);
					map_data[mm].y = (int)((yy - Db) * 17 * qq);
				}
				else if(RegionCode==3&&country_code==2)//USA
				{
					map_data[mm].x  = (int)((xx + Da) * 13 * qq);
					map_data[mm].y = (int)((yy - Db) * 17 * qq);

				}
				/*else if(RegionCode==1&&country_code==17)//Thailand
				{
					map_data[mm].x = 1400 + (int)((Da - 120) * 38);
					map_data[mm].y = 50 - (int)((Db - 20) * 38);
				}
				else {}*/
			}
			CPen *pOldPen = NULL;				//create a point for pen
			CBrush *pOldBrush = NULL;			//create a point for brush

			CPen Pen1(PS_SOLID, 1, RGB(250,250,250));	//define a pen
			CBrush Brush1(RGB(0,100,150));		//define a brush

			pOldPen = art.SelectObject(&Pen1);	//select the pen into pen point
			pOldBrush = art.SelectObject(&Brush1);  //select the brush into brush point

			art.Polygon(map_data, pairs);				//draw poligon with the pen and brush

			art.SelectObject(pOldPen);			//return original pen into oen point
			art.SelectObject(pOldBrush);		//return original brush into brush point

			Pen1.DeleteObject();				//delete object
			Brush1.DeleteObject();
			fclose(Fdata);
		}
	}
	fclose(Findex);


}


