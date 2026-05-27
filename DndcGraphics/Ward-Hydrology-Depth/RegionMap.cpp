// RegionMap.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "RegionMap.h"
#include "SitePara.h"
#include "dndc_tool.h"
#include "dndc_main.h"
#include <io.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//void Glean_String(char *String, int Num1, int Num2, char *Sub_Str);

/////////////////////////////////////////////////////////////////////////////
// RegionMap dialog


RegionMap::RegionMap(CWnd* pParent /*=NULL*/)
	: CDialog(RegionMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(RegionMap)
	m_MapSelect = -1;
	//}}AFX_DATA_INIT
}


void RegionMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RegionMap)
	DDX_Control(pDX, IDC_OutputFileList, m_OutputFileList);
	DDX_Radio(pDX, IDC_MapSelect, m_MapSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RegionMap, CDialog)
	//{{AFX_MSG_MAP(RegionMap)
	ON_BN_CLICKED(IDC_DrawMap, OnDrawMap)
	ON_BN_CLICKED(IDC_SelectOutputFile, OnSelectOutputFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RegionMap message handlers

void RegionMap::OnDrawMap() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString RFile;
	FILE *rff;
	int RegionID, CountryID, ProvinceID;
	char RegionName[200], CountryName[200], Root1[250], Root2[300],WholeName[300];

	RFile.Format("%s\\Inter\\PassName", OUTPUT);
	rff=fopen(RFile, "r");
	if(rff==NULL)
	{
		CString err;
		err.Format("Can not opne file %s",RFile);
		AfxMessageBox(err);
		exit(0);
	}
	fscanf(rff, "%d %d", &CountryID, &ProvinceID);
	fscanf(rff, "%s %s %s %s", CountryName, Root1, Root2, WholeName);

	fclose(rff);

	RegionID=ProvinceID;

	if(m_MapSelect==-1)
	{
		ReadOutput(RegionID, CountryID);
	}
	//else 
	//	sprintf(NameSeries[1], "None");

	
	CString FluxName[22]={"", "N deposit", "CH4", "CO2", "dSOC", "Fertilizer N", "N fixation", "Crop yield", 
							"DOC leaching", "N leaching", "Manure C", "N mineralization", "N2", "N2O", "NH3", 
							"NO", "pSOC", "Crop residue", "Root C", "Shoot C", "SOC", "N uptake"};
	
	ReadGIS(RegionID, CountryID, ProvinceID, RegionName, CountryName);

	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(2000, 2000);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));		
	

	pDC.SetViewportOrg (0, 0); 
	pDC.SetViewportExt(2100, 2000);

	float Fha;
	int RR, GG, BB;
	CString mark;
	
	for(int j=0; j<10; j++)
	{
		int x=700;
		int dx=15;
		int y=j*30+300;
		int dy=40;

		if(m_MapSelect==-1)
		{
			if(FluxType==4) //dSOC
			{				
				Fha = (-1000.0 + j*200.0) * scale;

				if(Fha<0.0) 
				{
					Fha*=-1.0;
					RR=255-(int)(Fha*0.1);
					GG=255-(int)(Fha*0.3);
					BB=255-(int)(Fha*0.5);
				}
				else
				{
					RR=255-(int)(Fha*0.3);
					GG=255-(int)(Fha*0.1);
					BB=255-(int)(Fha*0.5);
				}

				mark.Format("%.0f", -1000.0 + j*200.0);
				pDC.TextOut(x+55, y, mark);

				if(j==9)
				{
					mark.Format("kg C/ha");
					pDC.TextOut(x+55, y+dy, mark);
				}

			}
			else 
			{

				if(FluxType==2)//CH4
				{
					Fha = (j*10.0) * scale;
					mark.Format("%.0f", j*10.0);
					pDC.TextOut(x+55, y, mark);

					if(j==9)
					{
						mark.Format("kg CH4-C/ha");
						pDC.TextOut(x+55, y+dy, mark);
					}
				}
				else if(FluxType==13)//N2O
				{
					Fha = (j*0.2) * scale;
					mark.Format("%.1f", j*0.2);
					pDC.TextOut(x+55, y, mark);

					if(j==9)
					{
						mark.Format("kg N2O-N/ha");
						pDC.TextOut(x+55, y+dy, mark);
					}
				}

				RR=250-(int)(Fha*0.5);
				GG=250-(int)(Fha*0.3);
				BB=250-(int)(Fha*0.1);

				
			}
		}
			
		pDC.FillSolidRect(x, y, dx, dy, RGB(RR,GG,BB));
	}

	pDC.SelectObject(pOldPen);
	Pen0.DeleteObject();

	//AfxMessageBox("");
		
}

void RegionMap::ReadGIS(int RegionID, int CountryID, int ProvinceID, char *RegionName, char *CountryName)
{
	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(2000, 2000);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);

	pDC.SetViewportOrg (0, 0); 
	pDC.SetViewportExt(2100, 2000);
	pDC.FillSolidRect(0, 0, 820, 1600, RGB(190,190,190));

	pDC.SelectObject(pOldPen);
	Pen0.DeleteObject();


	//POSITION pos = pDoc->GetFirstViewPosition();
	//CView* pDC = pDoc->GetNextView( pos );
	//CClientDC dc(pDC);
	
	/*dc.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	dc.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);
	
	CBrush *pOldBrush = dc.GetCurrentBrush(); 

	dc.SetViewportOrg (0, 0); //profile note
	dc.SetViewportExt(1500, 1500);
	dc.FillSolidRect(0, 0, 1500, 1500, RGB(200,200,200)); //background
	
	CBrush brush0;								
	brush0.CreateSolidBrush(RGB(0,0,0));	
	pOldBrush = dc.SelectObject(&brush0);
	
	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = dc.SelectObject(&Pen0);*/

	/*POSITION canves = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( canves );
	CClientDC art(pDC);*/
	//////////////////////////////////////////////////////////////////////////////////

	CString FluxName[22]={"", "N deposit", "CH4", "CO2", "dSOC", "Fertilizer N", "N fixation", "Crop yield", 
							"DOC leaching", "N leaching", "Manure C", "N mineralization", "N2", "N2O", "NH3", 
							"NO", "pSOC", "Crop residue", "Root C", "Shoot C", "SOC", "N uptake"};
	
	CPoint locate[52000];
	double qq=8.0, pp=450.0;
	char PNM[200];

	CString FMAP;
	char F6[200], F5[200], F4[200], F3[200], F2[200], F1[200];

	CString CP[19]={"Asia", "Bangladesh", "Bhutan", "Cambodia", "China",
		            "India", "Indonesia", "Japan", "Laos", "Malaysia",
					"Myanmar", "Nepal", "NorthKorea", "Pakistan", "Philippines",
					"SouthKorea", "SriLanka", "Thailand", "Vietnam"};

	CString PP[32] = {"China", "Beijing", "Tianjin", "Hebei", "Shanxi", "Inner_Mongolia", 
			"Liaoning", "Jilin", "Heilongjiang", "Shanghai", "Jiangsu", "Zhejiang", "Anhui", 
			"Fujian", "Jiangxi", "Shandong", "Henan", "Hubei", "Hunan", "Guangdong", "Guangxi", 
			"Sichuan", "Guizhou", "Yunnan", "Tibet", "Shaanxi", "Gansu", "Qinghai", "Ningxia", 
			"Xinjiang", "Hainan", "Taiwan"};

	CString IP[33] = {"India", "Andaman", "Andhra_pradesh", "Arunachal_Pradesh", "Assam",
						"Bihar", "Chandigarh", "Dadra", "Daman_Diu", "Delhi", 
						"Goa", "Gujarat", "Haryana", "Himachal_Pradesh", "Jammu_Kashmir", 
						"Karnataka", "Kerala", "Lakshadweep", "Madhya_Pradesh", "Maharashtra", 
						"Manipur", "Meghalaya", "Mizoram", "Nagaland", "Orissa", 
						"Pondicherry", "Punjab", "Rajasthan", "Sikkim", "Tamil_Nadu", 
						"Tripura", "Uttar_Pradesh", "West_Bengal"};

	CString OP[3]={"Oceania", "Australia", "New_Zealand"};
		
	if(RegionID==1)//Asia
	{
		if(CountryID==0)//total Asia
		{
			for(int Country=1; Country<=18; Country++)
			{
				/*if(Country==7)
				{}
				else
					goto NextCountry;*/

				if(Country==4||Country==5)
				{
					int TPN;
					
					if(Country==4) 
					{
						TPN=31;
					}
					else 
					{
						TPN=32;
					}

					for(Province=1; Province<=TPN; Province++)
					{
						if(Country==4) 
						{
							sprintf(PNM, "%s", PP[Province]);
						}
						else 
						{
							sprintf(PNM, "%s", IP[Province]);
						}
						//sprintf(F7, "%s", NameSeries[Province]);
						sprintf(F6, "%s\\Database\\Asia\\%s\\GIS\\%s_6", ROOTDIR, CP[Country], PNM);
						sprintf(F5, "%s\\Database\\Asia\\%s\\GIS\\%s_5.txt", ROOTDIR, CP[Country], PNM);
						sprintf(F4, "%s\\Database\\Asia\\%s\\GIS\\%s_4.txt", ROOTDIR, CP[Country], PNM);
						sprintf(F3, "%s\\Database\\Asia\\%s\\GIS\\%s_3.txt", ROOTDIR, CP[Country], PNM);
						sprintf(F2, "%s\\Database\\Asia\\%s\\GIS\\%s_2.txt", ROOTDIR, CP[Country], PNM);
						sprintf(F1, "%s\\Database\\Asia\\%s\\GIS\\%s_1.txt", ROOTDIR, CP[Country], PNM);

						DrawPolygon(F6, F5, F4, F3, F2, F1, RegionID, CountryID, ProvinceID);			
					}
				}
				else
				{
					//sprintf(F7, "%s", NameSeries[1]);
					sprintf(F6, "%s\\Database\\Asia\\%s\\GIS\\%s_6", ROOTDIR, CP[Country], CP[Country]);
					sprintf(F5, "%s\\Database\\Asia\\%s\\GIS\\%s_5.txt", ROOTDIR, CP[Country], CP[Country]);
					sprintf(F4, "%s\\Database\\Asia\\%s\\GIS\\%s_4.txt", ROOTDIR, CP[Country], CP[Country]);
					sprintf(F3, "%s\\Database\\Asia\\%s\\GIS\\%s_3.txt", ROOTDIR, CP[Country], CP[Country]);
					sprintf(F2, "%s\\Database\\Asia\\%s\\GIS\\%s_2.txt", ROOTDIR, CP[Country], CP[Country]);
					sprintf(F1, "%s\\Database\\Asia\\%s\\GIS\\%s_1.txt", ROOTDIR, CP[Country], CP[Country]);

					DrawPolygon(F6, F5, F4, F3, F2, F1, RegionID, CountryID, ProvinceID);
				}
	
			}
		}
		else if(CountryID==1||CountryID==2||CountryID==3||CountryID==6||CountryID==7||CountryID==8||CountryID==9
				||CountryID==10||CountryID==11||CountryID==12||CountryID==13||CountryID==14||CountryID==15
				||CountryID==16||CountryID==17||CountryID==18)
			//Bangladesh, Bhutan, Cambodia, Indonesia, Japan, Laos, Malaysia, Myanmar, Nepal, NorthKorea
		{
			//sprintf(F7, "%s", NameSeries[1]);
			sprintf(F6, "%s\\Database\\Asia\\%s\\GIS\\%s_6", ROOTDIR, CP[CountryID], CP[CountryID]);
			sprintf(F5, "%s\\Database\\Asia\\%s\\GIS\\%s_5.txt", ROOTDIR, CP[CountryID], CP[CountryID]);
			sprintf(F4, "%s\\Database\\Asia\\%s\\GIS\\%s_4.txt", ROOTDIR, CP[CountryID], CP[CountryID]);
			sprintf(F3, "%s\\Database\\Asia\\%s\\GIS\\%s_3.txt", ROOTDIR, CP[CountryID], CP[CountryID]);
			sprintf(F2, "%s\\Database\\Asia\\%s\\GIS\\%s_2.txt", ROOTDIR, CP[CountryID], CP[CountryID]);
			sprintf(F1, "%s\\Database\\Asia\\%s\\GIS\\%s_1.txt", ROOTDIR, CP[CountryID], CP[CountryID]);

			DrawPolygon(F6, F5, F4, F3, F2, F1, RegionID, CountryID, ProvinceID);
		}
		else if(CountryID==4)//China
		{
			int TPN=31;
			char PNM[200];
					
			for(Province=1; Province<=TPN; Province++)
			{
				//NameSeries[Province]
				sprintf(PNM, "%s", PP[Province]);

				//if(m_MapSelect!=-1) 
				//	sprintf(NameSeries[Province], "None");
				//sprintf(F7, "%s", NameSeries[Province]);
				sprintf(F6, "%s\\Database\\Asia\\%s\\GIS\\%s_6", ROOTDIR, CP[CountryID], PNM);
				sprintf(F5, "%s\\Database\\Asia\\%s\\GIS\\%s_5.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F4, "%s\\Database\\Asia\\%s\\GIS\\%s_4.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F3, "%s\\Database\\Asia\\%s\\GIS\\%s_3.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F2, "%s\\Database\\Asia\\%s\\GIS\\%s_2.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F1, "%s\\Database\\Asia\\%s\\GIS\\%s_1.txt", ROOTDIR, CP[CountryID], PNM);

				DrawPolygon(F6, F5, F4, F3, F2, F1, RegionID, CountryID, ProvinceID);			
			}
		}
		else if(CountryID==5)//India
		{
			int TPN=32;
			char PNM[200];

			CountryFlux=0.0;
			CountryHa=0.0;
					
			for(Province=1; Province<=TPN; Province++)
			{
				sprintf(PNM, "%s", IP[Province]);

				//if(m_MapSelect!=-1) 
				//	sprintf(NameSeries[Province], "None");
				//sprintf(F7, "%s", NameSeries[Province]);
				sprintf(F6, "%s\\Database\\Asia\\%s\\GIS\\%s_6", ROOTDIR, CP[CountryID], PNM);
				sprintf(F5, "%s\\Database\\Asia\\%s\\GIS\\%s_5.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F4, "%s\\Database\\Asia\\%s\\GIS\\%s_4.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F3, "%s\\Database\\Asia\\%s\\GIS\\%s_3.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F2, "%s\\Database\\Asia\\%s\\GIS\\%s_2.txt", ROOTDIR, CP[CountryID], PNM);
				sprintf(F1, "%s\\Database\\Asia\\%s\\GIS\\%s_1.txt", ROOTDIR, CP[CountryID], PNM);

				DrawPolygon(F6, F5, F4, F3, F2, F1, RegionID, CountryID, ProvinceID);
				
				if(m_MapSelect==-1)
				{
					CountryFlux += NationFlux[Province];
					CountryHa += NationHa[Province];
				}
			}

			if(m_MapSelect==-1)
			{
				pDC.SetTextColor(RGB(0,0,0));
				CString note;

				if(FluxType==1||FluxType==5||FluxType==6||FluxType==9||FluxType==11||FluxType==12||FluxType==13||
					FluxType==14||FluxType==15)
					note.Format("Total %s flux: %.0f ton N", FluxName[FluxType], CountryFlux);
				else if(FluxType==2||FluxType==3||FluxType==4||FluxType==7||FluxType==8||FluxType==10||
					FluxType==17||FluxType==18||FluxType==19)
					note.Format("Total %s flux: %.0f ton C", FluxName[FluxType], CountryFlux*1000.0);
				else if (FluxType==20)
					note.Format("Total %s storage: %.0f ton C", FluxName[FluxType], CountryFlux*1000.0);
				else {}
				
				pDC.TextOut(550, 15, note);
				note.Format("Total rice area: %.0f ha", CountryHa);			
				pDC.TextOut(550, 45, note);
			}
		}

	}
	else if(RegionID==4)//Oceania
	{
		if(CountryID==0)//total Oceania
		{
		}
		else if(CountryID==1)//Australia
		{
			sprintf(PNM, "%s", "Victoria");
			sprintf(F6, "%s\\Database\\Oceania\\%s\\GIS\\%s_6", ROOTDIR, OP[CountryID], PNM);
			sprintf(F5, "%s\\Database\\Oceania\\%s\\GIS\\%s_5.txt", ROOTDIR, OP[CountryID], PNM);
			sprintf(F4, "%s\\Database\\Oceania\\%s\\GIS\\%s_4.txt", ROOTDIR, OP[CountryID], PNM);
			sprintf(F3, "%s\\Database\\Oceania\\%s\\GIS\\%s_3.txt", ROOTDIR, OP[CountryID], PNM);
			sprintf(F2, "%s\\Database\\Oceania\\%s\\GIS\\%s_2.txt", ROOTDIR, OP[CountryID], PNM);
			sprintf(F1, "%s\\Database\\Oceania\\%s\\GIS\\%s_1.txt", ROOTDIR, OP[CountryID], PNM);

			DrawPolygon(F6, F5, F4, F3, F2, F1, RegionID, CountryID, ProvinceID);			
				
		}
		else//New Zraland
		{

		}
	}
}

void RegionMap::DrawPolygon(char *F6, char *F5, char *F4, char *F3, char *F2, char *F1, int RegionID, int CountryID, int ProvinceID)
{
	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(8000, 8000);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);

	CString CP[19]={"Asia", "Bangladesh", "Bhutan", "Cambodia", "China",
		            "India", "Indonesia", "Japan", "Laos", "Malaysia",
					"Myanmar", "Nepal", "NorthKorea", "Pakistan", "Philippines",
					"SouthKorea", "SriLanka", "Thailand", "Vietnam"};

	CString PP[32] = {"China", "Beijing", "Tianjin", "Hebei", "Shanxi", "Inner_Mongolia", 
			"Liaoning", "Jilin", "Heilongjiang", "Shanghai", "Jiangsu", "Zhejiang", "Anhui", 
			"Fujian", "Jiangxi", "Shandong", "Henan", "Hubei", "Hunan", "Guangdong", "Guangxi", 
			"Sichuan", "Guizhou", "Yunnan", "Tibet", "Shaanxi", "Gansu", "Qinghai", "Ningxia", 
			"Xinjiang", "Hainan", "Taiwan"};

	CString IP[33] = {"India", "Andaman", "Andhra_pradesh", "Arunachal_Pradesh", "Assam",
						"Bihar", "Chandigarh", "Dadra", "Daman_Diu", "Delhi", 
						"Goa", "Gujarat", "Haryana", "Himachal_Pradesh", "Jammu_Kashmir", 
						"Karnataka", "Kerala", "Lakshadweep", "Madhya_Pradesh", "Maharashtra", 
						"Manipur", "Meghalaya", "Mizoram", "Nagaland", "Orissa", 
						"Pondicherry", "Punjab", "Rajasthan", "Sikkim", "Tamil_Nadu", 
						"Tripura", "Uttar_Pradesh", "West_Bengal"};

	int VOx, VOy, VEx, VEy;

	if(RegionID==1&&CountryID==0&&ProvinceID==0)//All Asia
	{
		VOx = 0;
		VOy = 0;
		VEx = 1400;
		VEy = 1400;
	}

	else if(RegionID==1&&CountryID==4&&ProvinceID==0)//China
	{
		VOx = -210;
		VOy = 0;
		VEx = 2100;
		VEy = 2600;
	}

	else if(RegionID==1&&CountryID==5&&ProvinceID==0)//India
	{
		VOx = -150;
		VOy = -350;
		VEx = 3300;
		VEy = 3300;
	}

	else if(RegionID==1&&CountryID==1&&ProvinceID==0)//Bangladesh
	{
		VOx = -750;
		VOy = -550;
		VEx = 5000;
		VEy = 5000;
	}

	else if(RegionID==1&&CountryID==2&&ProvinceID==0)//Bhutan
	{
		VOx = -750;
		VOy = -550;
		VEx = 5000;
		VEy = 5000;
	}

	else if(RegionID==1&&CountryID==3&&ProvinceID==0)//Cambodia
	{
		VOx = -500;
		VOy = -500;
		VEx = 3000;
		VEy = 3000;
	}

	else if(RegionID==1&&CountryID==6&&ProvinceID==0)//Indonesia
	{
		VOx = -550;
		VOy = -600;
		VEx = 2500;
		VEy = 2500;
	}

	else if(RegionID==1&&CountryID==7&&ProvinceID==0)//Japan
	{
		VOx = -1500;
		VOy = -200;
		VEx = 3900;
		VEy = 3900;
	}

	else if(RegionID==1&&CountryID==8&&ProvinceID==0)//Laos
	{
		VOx = -600;
		VOy = -600;
		VEx = 4000;
		VEy = 4000;
	}

	else if(RegionID==1&&CountryID==9&&ProvinceID==0)//Malaysia
	{
		VOx = -600;
		VOy = -600;
		VEx = 3000;
		VEy = 3000;
	}

	else if(RegionID==1&&CountryID==10&&ProvinceID==0)//Myanmar
	{
		VOx = -600;
		VOy = -400;
		VEx = 3500;
		VEy = 3500;
	}

	else if(RegionID==1&&CountryID==11&&ProvinceID==0)//Nepal
	{
		VOx = 0;
		VOy = -400;
		VEx = 3500;
		VEy = 3500;
	}

	else if(RegionID==1&&CountryID==12&&ProvinceID==0)//NorthKorea
	{
		VOx = -800;
		VOy = 0;
		VEx = 3000;
		VEy = 3400;
	}

	else if(RegionID==1&&CountryID==13&&ProvinceID==0)//Parkistan
	{
		VOx = 0;
		VOy = -200;
		VEx = 3000;
		VEy = 3000;
	}
	else if(RegionID==1&&CountryID==14&&ProvinceID==0)//Philippines
	{
		VOx = -1000;
		VOy = -600;
		VEx = 3500;
		VEy = 3500;
	}
	else if(RegionID==1&&CountryID==15&&ProvinceID==0)//SouthKorea
	{
		VOx = -800;
		VOy = 0;
		VEx = 3000;
		VEy = 3400;
	}
	else if(RegionID==1&&CountryID==16&&ProvinceID==0)//Sri_Lanka
	{
		VOx = 0;
		VOy = -800;
		VEx = 4000;
		VEy = 4000;
	}
	else if(RegionID==1&&CountryID==17&&ProvinceID==0)//Thailand
	{
		VOx = -800;
		VOy = -800;
		VEx = 4000;
		VEy = 4000;
	}
	else if(RegionID==1&&CountryID==18&&ProvinceID==0)//Parkistan
	{
		VOx = -800;
		VOy = -800;
		VEx = 4000;
		VEy = 4000;
	}

	else if(RegionID==4&&CountryID==1&&ProvinceID==0)//Australia
	{
		VOx = 0;
		VOy = 0;
		VEx = 70;
		VEy = 70;
	}
	else {}

	pDC.SetViewportOrg (VOx, VOy); 
	pDC.SetViewportExt(VEx, VEy);
	//pDC.FillSolidRect(0, 0, 820, 1600, RGB(190,190,190));

	pDC.SelectObject(pOldPen);
	Pen0.DeleteObject();

	int CountyID, MapID, i, Mid, pairs, j, CountyID4, CountyID3, CountyID2, CountyID1;
	int CropNumber, CropID[150], CountyID6, CountyID7;
	CPoint locate[52000];
	double X, Y, qq=50.0, pp=2800.0;
	char ww[200], ProvinceName[200], CountyName[200], ClimID[200];
	float ha[90], tha, SoilData[10], AtmoN, Longitude, Latitude;
	
	float TotalFlux, TotalHa, AveFlux, TotalArea;
	
	CString FMAP;
	char F7[150];

	FILE *f7, *f6, *f5, *f4, *f3, *f2, *f1, *fmap;

	if(m_MapSelect==-1)
	{
		CString Xname;
		FILE *xn;
		Xname.Format("%s\\Inter\\MapData", OUTPUT);
		xn=fopen(Xname, "r");
		if(xn==NULL)
		{
			CString err;
			err.Format("Cannot open %s", Xname);
			AfxMessageBox(err);
			exit(0);
		}

		for(int bb=1;bb<=Provinces;bb++)
		{
			fscanf(xn, "%s",F7); 
			if(bb==Province) break;
		}
		fclose(xn);

		f7=fopen(F7, "r");
		if(f7==NULL)
		{
			CString err;
			err.Format("Can not opne file %s",F7);
			AfxMessageBox(err);
			exit(0);
		}
		fgets(ww, 300, f7);
		fgets(ww, 300, f7);
		fgets(ww, 300, f7);
	}

	if(RegionID==4&&CountryID==1&&ProvinceID==0)//Australia
	{
		////////////////////////////////////////////////
		//for(;;)
		//{
		
		FMAP.Format("%s\\Database\\Australia\\Victoria.txt", ROOTDIR);
		fmap=fopen(FMAP, "r");
		if(fmap==NULL)
		{
			CString err;
			err.Format("Can not opne file %s",FMAP);
			AfxMessageBox(err);
			exit(0);
		}
		fscanf(fmap, "%d %d", &Mid, &pairs);
		
		for(j=1; j<=pairs; j++)
		{
			qq=10000;
			pp=1435000;

			fscanf(fmap, "%lf %lf", &X, &Y);
			locate[j-1].x = (int)(X*qq-pp + 30000);
			locate[j-1].y = (int)(-Y*qq-352000 + 30000);
		}
		fclose(fmap);
		
		LR=255;
		LG=255;
		LB=255;	
		
		{
			if(m_MapSelect==0)
			{
				RR=50;
				GG=200;
				BB=250;
			}
		
		}

		//draw polygon
		CPen *pOldPen = NULL;				
		CBrush *pOldBrush = NULL;
		CPen Pen1(PS_SOLID, 1, RGB(LR,LG,LB));	
		CBrush Brush1(RGB(RR,GG,BB));	
		pOldPen = pDC.SelectObject(&Pen1);	
		pOldBrush = pDC.SelectObject(&Brush1); 
		pDC.Polygon(locate, pairs);				
		pDC.SelectObject(pOldPen);			
		pDC.SelectObject(pOldBrush);
		Pen1.DeleteObject();				
		Brush1.DeleteObject();
		
		//AfxMessageBox("end");
		//exit(0);

	//}
	
		////////////////////////////////////////////////
	}

	else
	{
	
	f6=fopen(F6, "r");
	if(f6==NULL)
	{
		CString err;
		err.Format("Can not opne file %s",F6);
		AfxMessageBox(err);
		exit(0);
	}

	f5=fopen(F5, "r");
	if(f5==NULL)
	{
		CString err;
		err.Format("Can not opne file %s",F5);
		AfxMessageBox(err);
		exit(0);
	}

	f4=fopen(F4, "r");
	if(f4==NULL)
	{
		CString err;
		err.Format("Can not opne file %s",F4);
		AfxMessageBox(err);
		exit(0);
	}
	fgets(ww, 300, f4);
	fscanf(f4, "%d", &CropNumber);
	for(int vv=1; vv<=CropNumber; vv++) fscanf(f4, "%d", &CropID[vv]);
	//fgets(ww, 300, f4);

	f3=fopen(F3, "r");
	if(f3==NULL)
	{
		CString err;
		err.Format("Can not opne file %s",F3);
		AfxMessageBox(err);
		exit(0);
	}
	fgets(ww, 300, f3);
	fgets(ww, 300, f3);

	f2=fopen(F2, "r");
	if(f2==NULL)
	{
		CString err;
		err.Format("Can not opne file %s",F2);
		AfxMessageBox(err);
		exit(0);
	}

	f1=fopen(F1, "r");
	if(f1==NULL)
	{
		CString err;
		err.Format("Can not opne file %s",F1);
		AfxMessageBox(err);
		exit(0);
	}

	
	{
		

	}

	//start county loop
	if(Province<0) Province=1;
	NationFlux[Province]=0.0;
	NationHa[Province]=0.0;

	for(;;)
	{
		if(fscanf(f5, "%d %d", &CountyID, &MapID)!=2) break;

		/*char Sf[200], Tf[200];
		sprintf(Sf, "%s\\Database\\Asia\\Asia_map\\%d", MapID);
		sprintf(Tf, "%s\\Database\\Asia\\%s\\Lib_map\\%d", CP[CountryID], MapID);
		FileCopy(Sf, Tf);*/

		fscanf(f4, "%d", &CountyID4);
		if(CountyID!=CountyID4)
		{
			CString err;
			err.Format("County IDs don't match: %s vs. %s",F5, F4);
			AfxMessageBox(err);
			exit(0);
		}		
		tha = 0.0;
		for(i=1; i<=CropNumber; i++)
		{
			fscanf(f4, "%f", &ha[i]);
			tha += ha[i];
		}

		fscanf(f3, "%d", &CountyID3);
		if(CountyID!=CountyID3)
		{
			CString err;
			err.Format("County IDs don't match: %s vs. %s",F5, F3);
			AfxMessageBox(err);
			exit(0);
		}	
		for(i=1; i<=8; i++)
		{
			fscanf(f3, "%f", &SoilData[i]);
		}

		fscanf(f2, "%d", &CountyID2);
		if(CountyID!=CountyID2)
		{
			CString err;
			err.Format("County IDs don't match: %s vs. %s",F5, F2);
			AfxMessageBox(err);
			exit(0);
		}	
		{
			fscanf(f2, "%s %f", ClimID, &AtmoN);

			/*char Sf[200], Tf[200];
			sprintf(Sf, "%s\\Database\\Asia\\Asia_climate\\%s_00", ClimID);
			sprintf(Tf, "%s\\Database\\Asia\\%s\\Lib_clim\\2000\\%s", CP[CountryID], ClimID);
			FileCopy(Sf, Tf);*/
		}

		fscanf(f1, "%d", &CountyID1);
		if(CountyID!=CountyID1)
		{
			CString err;
			err.Format("County IDs don't match: %s vs. %s",F5, F1);
			AfxMessageBox(err);
			exit(0);
		}	
		{
			fscanf(f1, "%s %s %f %f", ProvinceName, CountyName, &Longitude, &Latitude);
		}

		fscanf(f6, "%d", &CountyID6);
		if(CountyID!=CountyID6)
		{
			CString err;
			err.Format("County IDs don't match: %s vs. %s",F5, F6);
			AfxMessageBox(err);
			exit(0);
		}	
		{
			fscanf(f6, "%f", &TotalArea);
		}

		if(m_MapSelect==-1)
		{
			float jkf;
			fscanf(f7, "%d", &CountyID7);
			if(CountyID!=CountyID7)
			{
				CString err;
				err.Format("County IDs don't match: %s vs. %s",F5, F7);
				AfxMessageBox(err);
				exit(0);
			}	
			{
				fscanf(f7, "%f %f %f %f %f %f %f %f %f", &jkf, &jkf, &jkf, &jkf, &jkf, &jkf, 
					&TotalFlux, &TotalHa, &AveFlux);
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		CString CoName;

		if(RegionID==1)
		{
			if(CountryID==4) CoName=PP[ProvinceID];	
			if(CountryID==5) CoName=IP[ProvinceID];	
			else CoName=CP[CountryID];
		}
		FMAP.Format("%s\\Database\\Asia\\%s\\Lib_map\\%d", ROOTDIR, CoName, MapID);
		fmap=fopen(FMAP, "r");
		if(fmap==NULL)
		{
			CString err;
			err.Format("Can not opne file %s",FMAP);
			AfxMessageBox(err);
			exit(0);
		}
		fscanf(fmap, "%d %d", &Mid, &pairs);
		for(j=1; j<=pairs; j++)
		{
			fscanf(fmap, "%lf %lf", &X, &Y);
			locate[j-1].x = (int)(X*qq-pp);
			locate[j-1].y = (int)(pp-Y*qq);
		}
		fclose(fmap);
		
		LR=220;
		LG=220;
		LB=220;	

		if(m_MapSelect==-1)
		{
			//float scale;

			if(FluxType==1) scale=50.0;//AtomN
			else if(FluxType==2) scale=5.0;//CH4
			else if(FluxType==3) scale=0.1;//CO2
			else if(FluxType==4) scale=0.2;//dSOC
			else if(FluxType==5) scale=5.0;//FertN
			else if(FluxType==6) scale=1.0;//FixedN
			else if(FluxType==7) scale=0.1;//HarveC
			else if(FluxType==8) scale=50.0;//LeachC
			else if(FluxType==9) scale=50.0;//NLeach
			else if(FluxType==10) scale=0.1;//ManureC
			else if(FluxType==11) scale=1.0;//MinerN
			else if(FluxType==12) scale=200.0;//N2
			else if(FluxType==13) scale=200.0;//N2O
			else if(FluxType==14) scale=50.0;//NH3
			else if(FluxType==15) scale=200.0;//NO
			else if(FluxType==16) scale=1.0;//pSOC
			else if(FluxType==17) scale=0.1;//ResidC
			else if(FluxType==18) scale=0.1;//RootC
			else if(FluxType==19) scale=0.1;//ShootC
			else if(FluxType==20) scale=0.005;//SOC
			else if (FluxType==21) scale=2.0;//UptakeN
			else {}

			float Fha;

			if(FluxType==4)
			{
				Fha = AveFlux * scale;

				Fha=max(-255, min(255, Fha));

				if(Fha<0.0) 
				{
					Fha*=-1.0;
					RR=255-(int)(Fha*0.1);
					GG=255-(int)(Fha*0.3);
					BB=255-(int)(Fha*0.5);
				}
				else
				{
					RR=255-(int)(Fha*0.3);
					GG=255-(int)(Fha*0.1);
					BB=255-(int)(Fha*0.5);

				}
			}
			else
			{
				/*if(FluxType==16)
					Fha = AveFlux * scale;
				else if(FluxType==20)
					Fha = AveFlux * scale;
				else
					Fha = AveFlux * scale;*/

				Fha = AveFlux * scale;

				Fha=max(0.0, min(255, Fha));

				RR=250-(int)(Fha*0.5);
				GG=250-(int)(Fha*0.3);
				BB=250-(int)(Fha*0.1);

				
			}

			if(FluxType==16)
			{
			}
			else
			{
				NationFlux[Province]+=TotalFlux;
			}
			
			NationHa[Province]+=TotalHa;


			

			//}
		}
		else
		{
			if(m_MapSelect==0)
			{
				RR=50;
				GG=180;
				BB=200;
			}
			else if(m_MapSelect==1)//Rice
			{
				float Fha = tha/800.0;
				Fha=max(0.0, min(250, Fha));

				RR=250-(int)(Fha*0.8);
				GG=250-(int)(Fha*0.2);
				BB=250-(int)(Fha*0.5);
			}
			else if(m_MapSelect==8)//SOC
			{
				float Fha = (SoilData[1]+SoilData[2])*0.5 * 20000.0;
				Fha=max(0.0, min(250, Fha));

				RR=250-(int)(Fha*0.2);
				GG=250-(int)(Fha*0.5);
				BB=250-(int)(Fha*0.5);
			}
			else if(m_MapSelect==9)//pH
			{
				float Fha = (SoilData[5]+SoilData[6])*0.5 * 25.0;
				Fha=max(0.0, min(250, Fha));

				RR=250-(int)(Fha*0.5);
				GG=250-(int)(Fha*0.3);
				BB=250-(int)(Fha*0.1);
			}
			else if(m_MapSelect==10)//clay
			{
				float Fha = (SoilData[3]+SoilData[4])*0.5 * 1000.0;
				Fha=max(0.0, min(250, Fha));

				RR=250-(int)(Fha*0.8);
				GG=250-(int)(Fha*0.4);
				BB=250-(int)(Fha*0.1);
			}
		}

		//draw polygon
		CPen *pOldPen = NULL;				
		CBrush *pOldBrush = NULL;
		CPen Pen1(PS_SOLID, 1, RGB(LR,LG,LB));	
		CBrush Brush1(RGB(RR,GG,BB));	
		pOldPen = pDC.SelectObject(&Pen1);	
		pOldBrush = pDC.SelectObject(&Brush1); 
		pDC.Polygon(locate, pairs);				
		pDC.SelectObject(pOldPen);			
		pDC.SelectObject(pOldBrush);
		Pen1.DeleteObject();				
		Brush1.DeleteObject();
		

	}
	if(m_MapSelect==-1) fclose(f7);
	fclose(f6);
	fclose(f5);
	fclose(f4);
	fclose(f3);
	fclose(f2);
	fclose(f1);

	
			}
}

void RegionMap::OnSelectOutputFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char FileName[255];
	CString cst;
AGAIN:
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();

	
	int k,num;
	num=m_OutputFileList.GetCount();
	if (num==1) return;
	
	k=m_OutputFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		int ll=strlen(cst);

		if (cst=="") break;
		int w=-1, kk=0, jj=50;
		for(;;)
		{
			w++;
			if(cst[w]=='r') 
			{
				kk++;
				jj=w;
			}

			if(cst[jj+1]=='a') kk++;
			else kk=0;
			if(cst[jj+2]=='t') kk++;
			else kk=0;
			if(cst[jj+3]=='e') kk++;
			else kk=0;

			if(kk==4)
			{
				CString err;
				err.Format("Please select a file starting with sum");
				AfxMessageBox(err);
				goto AGAIN;
			}

			if(w==ll-1) break;
		}
		strcpy(FileName,cst);
		m_OutputFileList.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_OutputFileList.GetCount()==1) break;
		k++;
	}
	m_OutputFileList.SetCurSel(k);

	CString SFF;
	FILE *sff;
	SFF.Format("%s\\Inter\\FileReview", OUTPUT);
	sff=fopen(SFF, "w");
	if(sff==NULL)
	{
		CString err;
		err.Format("Can not create file %s",SFF);
		AfxMessageBox(err);
		exit(0);
	}
	fprintf(sff, "%s", cst);
	fclose(sff);

	m_MapSelect = -1;

	UpdateData(FALSE);
	
}

void RegionMap::ReadOutput(int RegionID, int CountryID)
{
	
	if(RegionID==1&&CountryID==4) Provinces=30;//China
	if(RegionID==1&&CountryID==5) Provinces=32;//India

	CString SFF;
	char cst[200];
	FILE *sff;
	SFF.Format("%s\\Inter\\FileReview", OUTPUT);
	sff=fopen(SFF, "r");
	if(sff==NULL)
	{
		CString err;
		err.Format("Can not open file %s",SFF);
		AfxMessageBox(err);
		exit(0);
	}
	fscanf(sff, "%s", cst);
	fclose(sff);

	int ll=strlen(cst);

		int w=-1, kk=0, jj=50;
		for(;;)
		{
			w++;
			if(cst[w]=='s') 
			{
				kk++;
				jj=w;
			}

			if(cst[jj+1]=='u') kk++;
			else kk=0;
			if(cst[jj+2]=='m') kk++;
			else kk=0;
			if(cst[jj+3]=='_') kk++;
			else kk=0;

			if(kk==4)
			{
				char RR[4], FF[4], NameRoot[200];
			
				RR[0]=cst[jj+4];
				RR[1]=cst[jj+5];
				RR[2]=cst[jj+6];
				RR[3]='\0';

				FF[0]=cst[jj+8];
				FF[1]=cst[jj+9];
				FF[2]=cst[jj+10];
				FF[3]='\0';

				if(strcmp(FF, "Atm")==0) FluxType = 1;
				else if(strcmp(FF, "CH4")==0) FluxType = 2;
				else if(strcmp(FF, "CO2")==0) FluxType = 3;
				else if(strcmp(FF, "dSO")==0) FluxType = 4;
				else if(strcmp(FF, "Fer")==0) FluxType = 5;
				else if(strcmp(FF, "Fix")==0) FluxType = 6;
				else if(strcmp(FF, "Har")==0) FluxType = 7;
				else if(strcmp(FF, "Lea")==0) FluxType = 8;
				else if(strcmp(FF, "NLe")==0) FluxType = 9;
				else if(strcmp(FF, "Man")==0) FluxType = 10;
				else if(strcmp(FF, "Min")==0) FluxType = 11;
				else if(strcmp(FF, "N2_")==0) FluxType = 12;
				else if(strcmp(FF, "N2O")==0) FluxType = 13;
				else if(strcmp(FF, "NH3")==0) FluxType = 14;
				else if(strcmp(FF, "NO_")==0) FluxType = 15;
				else if(strcmp(FF, "pSO")==0) FluxType = 16;
				else if(strcmp(FF, "Res")==0) FluxType = 17;
				else if(strcmp(FF, "Roo")==0) FluxType = 18;
				else if(strcmp(FF, "Sho")==0) FluxType = 19;
				else if(strcmp(FF, "SOC")==0) FluxType = 20;
				else if(strcmp(FF, "Upt")==0) FluxType = 21;
				else{
					CString err;
					err.Format("This is a wrong selection");
					AfxMessageBox(err);
					exit(0);
				}
			

				Glean_String(cst, 0, ll-2, NameRoot);

				char NameSeries[150];
				
				CString Xname;
				FILE *xn;
				Xname.Format("%s\\Inter\\MapData", OUTPUT);
				xn=fopen(Xname, "w");
				if(xn==NULL)
				{
					CString err;
					err.Format("Cannot create %s", Xname);
					AfxMessageBox(err);
					exit(0);
				}

				for(int bb=1;bb<=Provinces;bb++)
				{
					sprintf(NameSeries, "%s%d", NameRoot, bb);
					fprintf(xn, "%s\n",NameSeries); 
				}
				fclose(xn);

				break;
			}
		}

}

/*void Glean_String(char *String, int Num1, int Num2, char *Sub_Str)
// Abstract part of String (from Num1 to Num2) and put to Sub_Str

{
  int i, l;
  l=strlen(String);
  if(Num1>Num2)  {
    //printf("%s\n",String);
    //Hint("Num1>Num2 in Glean_String",String);
    Sub_Str[0]='\0';
    return;
  }
  if (Num1>l) {
    //Hint("Out of range ",String);
    Sub_Str[0]='\0';
    return;
  }
    if (Num2>l)  Num2=l;
    for(i=Num1;i<=Num2;i++)
       Sub_Str[i-Num1]=String[i];
       Sub_Str[i-Num1]='\0';
}*/
