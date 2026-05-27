// GlobeMap.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "GlobeMap.h"
#include "dndc_main.h"
#include "stdafx.h"
#include "math.h"
#include "dndc_tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void Color1(float FT, int *Rr,int *Gg,int *Bb, int Item);
void CheckLimit(int *Rr,int *Gg,int *Bb);
void ConvertGlobalClimateToCountry(int CountryN, CString CountryCall);
float CalculateSoilDensity(float m_SoilClay, float m_SoilOrganic);
void CountryColor(int country, int* Rr, int * Gg, int* Bb);
void CropColor(int crop, float ha, int* Rr, int * Gg, int* Bb);
void SoilColor(int soil, float SoilPara, int* Rr, int * Gg, int* Bb);
void ManageColor(int manage, float ManagePara, int* Rr, int * Gg, int* Bb);

int GlobalCrop=0, GlobalSoil=0, GlobalManage=0;

CString RegionName[7]={"World", "Africa", "Asia", "Europe", "NorthAmerica", "Oceania", "SouthAmerica"};
int RandomGeneratorA(int ss);
void SoilConvert(float lat1, float lat2, float lon1, float lon2);
float SoilData[37];
char MapFileName[255];
					
/////////////////////////////////////////////////////////////////////////////
// GlobeMap dialog


GlobeMap::GlobeMap(CWnd* pParent /*=NULL*/)
	: CDialog(GlobeMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(GlobeMap)
	m_Column = 0;
	m_Row = 0;
	m_SelectRegion = -1;
	//}}AFX_DATA_INIT
}


void GlobeMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GlobeMap)
	DDX_Control(pDX, IDC_SelectManage, m_SelectManage);
	DDX_Control(pDX, IDC_SelectSoil, m_SelectSoil);
	DDX_Control(pDX, IDC_MapFileList, m_MapFileName);
	DDX_Control(pDX, IDC_Item, m_Item);
	DDX_Text(pDX, IDC_Column, m_Column);
	DDX_Text(pDX, IDC_Row, m_Row);
	DDX_Radio(pDX, IDC_RADIO1, m_SelectRegion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GlobeMap, CDialog)
	//{{AFX_MSG_MAP(GlobeMap)
	ON_BN_CLICKED(IDC_SelMapFile, OnSelMapFile)
	ON_LBN_DBLCLK(IDC_MapFileList, OnDblclkMapFileList)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_CBN_SELCHANGE(IDC_Item, OnSelchangeItem)
	ON_CBN_SELCHANGE(IDC_SelectSoil, OnSelchangeSelectSoil)
	ON_CBN_SELCHANGE(IDC_SelectManage, OnSelchangeSelectManage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GlobeMap message handlers
//CString FileName[2]={"","AVGTEMP"};

void GlobeMap::WorldMapping(int continent, int crop, int soil, int manage)
{
	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3900);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));	

	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);

	pDC.SetBkMode(TRANSPARENT);	

	pDC.FillSolidRect(45, 195, 1455, 730, RGB(220,220,220));

	////////////////////Draw countries based on RegionListFile.txt
	//m_Column = 720;
	//m_Row = 360;

	int i, CellID, CellID2, CellID3, CellID4, CellID7, row, column, x, y, z, w, cc, bb, region, country, xx, yy;
	int TotalCroppingSystems, TotalCropTypes, Rr=50,Gg=50,Bb=50, CropTypeID[50], cont; 
	char CountryName[120], CNNM[200], CNNM2[200],CNNM3[200],CNNM4[200],CNNM7[200], www[300], CroppingSystemName[155][50], js[20];
	char ClimateName[20], CropTypeName[155][50], CroppingSystemID[155][20], CellRecord[200];
	float lat, lon, CropHa[150], ManureN[150], IrriPercent[150], SoilPara[9], ManagePara[9], Ndepo, SnowPack;
	float CountryPasture[300]={0.0,0.0}, CountryCropland[300]={0.0,0.0}, PastureManureN[300]={0.0,0.0}, CropManureN[300]={0.0,0.0};  
	float GlobePasture=0.0, GlobeCropland=0.0;
	float FertRate[80]={0.0,0.0};
	double CellFertTotal=0.0, CountryFertTotal[300]={0.0,0.0}, GlobeFert=0.0, GlobeManure=0.0;
	int TotalCountry=0, CountryID[300];
	char CCName[300][120];
	int old_country=0;
	int j, k=0, crop_ID[5], GroupCrops;	
	FILE *cnnm, *cnnm2, *cnnm3, *cnnm4, *cnnm7, *CellR;
	
	CountryID[0]=0;	
	
	if(continent==0) //world
	{
		w=2;
		z=2;
		cc=2;
		bb=2;
		xx=50;
		yy=250;
	}
	else if(continent==1) //Africa
	{
		w=4;
		z=4;
		cc=4;
		bb=4;
		xx=-900;
		yy=-150;
	}
	else if(continent==2) //Asia
	{
		w=4;
		z=5;
		cc=4;
		bb=5;
		xx=-1400;
		yy=-100;
	}
	else if(continent==3) //Europe
	{
		w=3;
		z=4;
		cc=3,
		bb=4;
		xx=-750;
		yy=250;
	}
	else if(continent==4) //N. America
	{
		w=3;
		z=4;
		cc=3,
		bb=4;
		xx=300;
		yy=190;
	}
	else if(continent==5) //Oceania
	{
		w=4;
		z=4;
		cc=4;
		bb=4;
		xx=-1700;
		yy=-300;
	}
	else if(continent==6) //S. America
	{
		w=4;
		z=4;
		cc=4;
		bb=4;
		xx=-200;
		yy=-350;
	}

	if(crop==0&&soil==0&&manage==0)//only adiministrative countries
	{
		sprintf(CNNM, "%s\\Database\\Globe\\RegionListFile.txt", ROOTDIR);
		cnnm=fopen(CNNM, "r");
		if(cnnm==NULL) note(0, CNNM);
		fgets(www, 200, cnnm);
		
		for(i=1; i<=67685; i++)
		{
			fscanf(cnnm, "%d %f %f %d %d %d %d %s", &CellID, &lon, &lat, &row, &column, &region, &country, CountryName); 

			if(i!=CellID)
			{
				CString note;
				note.Format("Error for grid cell %d", i-1);
				AfxMessageBox(note);
				exit(0);
			}

			//paint cell
			if(continent==0||continent==region)
			{
				CountryColor(country, &Rr, &Gg, &Bb);
				
				x=cc*column+xx;
				y=bb*row+yy;

				pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
			}
		}
		fclose(cnnm);
	}
	else //for crop, soil or management items
	{
		if(continent>0)
		{
			cont = continent; 
			goto Aloop;
ENDloop:;
			goto WAN;
		}
		else
		{
			for(cont=1;cont<=6;cont++)
			{
				goto Aloop;
ENDloop2:;
			}

			goto WAN;
		}

Aloop:
		sprintf(CNNM, "%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, RegionName[cont], RegionName[cont]);
		cnnm=fopen(CNNM, "r");
		if(cnnm==NULL) note(0,CNNM);
		fgets(www, 200, cnnm);

		sprintf(CNNM2, "%s\\Database\\Globe\\%s\\GIS\\%s_2.txt", ROOTDIR, RegionName[cont], RegionName[cont]);
		cnnm2=fopen(CNNM2, "r");
		if(cnnm2==NULL) note(0,CNNM2);
		fgets(www, 200, cnnm2);
		
		fscanf(cnnm2, "%d", &TotalCroppingSystems);
		for(i=1; i<=TotalCroppingSystems; i++) fscanf(cnnm2, "%s", CroppingSystemName[i]);
		fscanf(cnnm2, "%s", js);
		for(i=1; i<=TotalCroppingSystems; i++) fscanf(cnnm2, "%s", &CroppingSystemID[i]);

		sprintf(CNNM3, "%s\\Database\\Globe\\%s\\GIS\\%s_3.txt", ROOTDIR, RegionName[cont], RegionName[cont]);
		cnnm3=fopen(CNNM3, "r");
		if(cnnm3==NULL) note(0,CNNM3);
		fgets(www, 200, cnnm3);
		fscanf(cnnm3, "%d", &TotalCropTypes);
		for(i=1; i<=TotalCropTypes; i++) fscanf(cnnm3, "%s", CropTypeName[i]);
		fscanf(cnnm3, "%s", js);
		for(i=1; i<=TotalCropTypes; i++) fscanf(cnnm3, "%d", &CropTypeID[i]);

		sprintf(CNNM4, "%s\\Database\\Globe\\%s\\GIS\\%s_4.txt", ROOTDIR, RegionName[cont], RegionName[cont]);
		cnnm4=fopen(CNNM4, "r");
		if(cnnm4==NULL) note(0,CNNM4);
		fgets(www, 200, cnnm4);
		//sprintf(SF5, "%s\\Database\\Globe\\%s\\GIS\\%s_5.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
		//sprintf(SF6, "%s\\Database\\Globe\\%s\\GIS\\%s_6.txt", ROOTDIR, ContinentName[continent], ContinentName[continent]);
		sprintf(CNNM7, "%s\\Database\\Globe\\%s\\GIS\\%s_7.txt", ROOTDIR, RegionName[cont], RegionName[cont]);
		cnnm7 = fopen(CNNM7, "r");
		if (cnnm7==NULL) note(0, CNNM7);
		fgets(www, 300, cnnm7);
		fscanf(cnnm7, "%d", &TotalCroppingSystems);
		for(i=1; i<=TotalCroppingSystems; i++) fscanf(cnnm7, "%s ", CroppingSystemName[i]);	
		fscanf(cnnm7, "%s", js);
		for(i=1; i<=TotalCroppingSystems; i++) fscanf(cnnm7, "%s ", CroppingSystemID[i]);

		sprintf(CellRecord, "%s\\Result\\Record\\Region\\CellRecord", ROOTDIR);
		CellR=fopen(CellRecord, "w");
		if(CellR==NULL) note(1,CellRecord);

		for(;;)
		{
			if(fscanf(cnnm, "%d %d %s %f %f %s %f %f %f %f %f %f %f %f %f %f %d %d %d", 				
				&CellID, &country, CountryName, &lon, &lat, ClimateName, &Ndepo, &SnowPack, 
				&SoilPara[1], &SoilPara[2], &SoilPara[3], &SoilPara[4], &SoilPara[5], &SoilPara[6], &SoilPara[7], &SoilPara[8], 
				&column, &row, &region)!=19) break; 
			
			fscanf(cnnm2, "%d", &CellID2); 
			fscanf(cnnm4, "%d", &CellID4); 
			fscanf(cnnm7, "%d", &CellID7);

			if(CellID!=CellID2)
			{
				CString note;
				note.Format("Error at grid cell %d in fertlizer rate file", CellID);
				AfxMessageBox(note);
				exit(0);
			}
			
			if(CellID!=CellID4)
			{
				CString note;
				note.Format("Error at grid cell %d in irrigation file", CellID);
				AfxMessageBox(note);
				exit(0);
			}
			
			if(CellID!=CellID7)
			{
				CString note;
				note.Format("Error at grid cell %d in manure file", CellID);
				AfxMessageBox(note);
				exit(0);
			}

			int gg=0;
			for(j=0;j<=k;j++)
			{
				if(country==CountryID[j]) 
				{
					gg++;
					break;
				}
			}

			if(gg==0)
			{
				k++;
				TotalCountry++;
				CountryID[k] = country;
				sprintf(CCName[k], "%s", CountryName);
				gg=0;
			}

			ManagePara[2] = 0.0;
			for(i=1; i<=TotalCroppingSystems; i++) 
			{
				fscanf(cnnm2, "%f", &CropHa[i]);
				fscanf(cnnm7, "%f", &ManureN[i]);

				ManureN[i] *= 0.001;//kg N -> ton N
				
				if(i==44) 
				{
					CountryPasture[country] += CropHa[i];
					GlobePasture += CropHa[i];
					PastureManureN[country] += (ManureN[i] * CropHa[i]);
				}
				else 
				{
					CountryCropland[country] += CropHa[i];
					GlobeCropland += CropHa[i];
					CropManureN[country] += (ManureN[i] * CropHa[i]);
				}
				ManagePara[2] += (ManureN[i] * CropHa[i]);
				GlobeManure += (ManureN[i] * CropHa[i]);
			}

			fscanf(cnnm4, "%f", &ManagePara[3]);

			fscanf(cnnm3, "%d", &CellID3); 

			if(CellID!=CellID3)
			{
				CString note;
				note.Format("Error at grid cell %d in %s", CellID, CNNM3);
				AfxMessageBox(note);
				exit(0);
			}
				
			for(i=1; i<=TotalCropTypes; i++) 
			{
				fscanf(cnnm3, "%f", &FertRate[CropTypeID[i]]);
			}

			CellFertTotal = 0.0;
			for(i=1; i<=TotalCroppingSystems; i++)
			{
				if(CropHa[i]>0.0)
				{

					float CroppingSystemTotal = 0.0;
					FindCrops(CroppingSystemID[i], crop_ID, &GroupCrops);
					for(int w=1; w<=GroupCrops; w++)
					{
						if(FertRate[crop_ID[w]]<0.0||FertRate[crop_ID[w]]>5000.0)
						{
							CString MSG;
							MSG.Format("Error for fertilizer rate %f for crop %d at cell %d",FertRate[crop_ID[w]],crop_ID[w],CellID);
							AfxMessageBox(MSG);
							exit(0);
						}
						CroppingSystemTotal += (CropHa[i] * FertRate[crop_ID[w]] * 0.001);//kg -> ton N
					}
					CellFertTotal += CroppingSystemTotal;//ton N
					CroppingSystemTotal = 0.0;
				}
			}
			CountryFertTotal[country] += CellFertTotal;
			GlobeFert += CellFertTotal;
			ManagePara[1] = CellFertTotal;

			//if(country==153) fprintf(CellR, "%6d  %15.0f\n", CellID, CellFertTotal);

			CellFertTotal = 0.0;
			
			//paint cell
			if(crop>0)//for crop
			{
				CropColor(crop, CropHa[crop], &Rr, &Gg, &Bb);
				
				x=cc*column+xx;
				y=bb*row+yy;

				pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
			}
			else if(soil>0) // for soil
			{
				SoilColor(soil, SoilPara[soil], &Rr, &Gg, &Bb);
				
				x=cc*column+xx;
				y=bb*row+yy;

				pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
			}
			else if(manage>0)//fertilization, manure, irrigation
			{
				ManageColor(manage, ManagePara[manage], &Rr, &Gg, &Bb);
				
				x=cc*column+xx;
				y=bb*row+yy;

				pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));

			}
		}
		fclose(cnnm);
		fclose(cnnm2);
		fclose(cnnm3);
		fclose(cnnm4);
		fclose(cnnm7);
		fclose(CellR);

		if(continent>0) goto ENDloop;
		else goto ENDloop2;
WAN:;
	}	

	CString GRE;
	FILE *gre;
	char WW[300];

	GRE.Format("%s\\Result\\Record\\Region\\GlobeDataSummary_%s.csv", ROOTDIR, RegionName[continent]);
	gre=fopen(GRE, "w");
	if(gre==NULL) note(1, GRE);

	sprintf(WW, "Summary report on land-use area for %s", RegionName[continent]);
	fprintf(gre, "%s\n\n", WW);
	fprintf(gre, "Total agricultural area (ha), %15.0f\n", GlobeCropland+GlobePasture);
	fprintf(gre, "Cropland area (ha),           %15.0f\n", GlobeCropland);
	fprintf(gre, "Grassland area (ha),          %15.0f\n", GlobePasture);
	fprintf(gre, "Fertilizer use (tons N),      %15.0lf\n", GlobeFert);
	fprintf(gre, "Manure use (tons N),			%15.0lf\n\n", GlobeManure);


	fprintf(gre, "%-10s, %-25s, %-15s, %-15s, %-15s, %-15s, %-15s, %-15s\n", "Country_ID", "Country_name", "Agricultural_ha", "Cropland_ha", "Grassland_ha", "Fertilizer_N_ton", "Crop_manure_N_ton", "Pasture_manure_N_ton");

	for(j=1;j<=TotalCountry;j++)
	{
		fprintf(gre, "%10d, %-25s, %15.0f, %15.0f, %15.0f, %15.0f, %15.0f, %15.0f\n",
			CountryID[j], CCName[j], CountryCropland[CountryID[j]]+CountryPasture[CountryID[j]], 
			CountryCropland[CountryID[j]], CountryPasture[CountryID[j]], 
			CountryFertTotal[CountryID[j]], CropManureN[CountryID[j]], PastureManureN[CountryID[j]]);
	}
	fclose(gre);
	
}


void CountryColor(int country, int* Rr, int * Gg, int* Bb)
{
	if(country==186)
	{
		*Rr=250; *Gg=120; *Bb=100;
	}
	else if(country==153)
	{
		*Rr=250; *Gg=140; *Bb=50;
	}
	else if(country==148)
				{
					*Rr=50; *Gg=220; *Bb=200;
				}
	else if(country==27)
				{
					*Rr=50; *Gg=220; *Bb=10;
				}
	else if(country==213)
				{
					*Rr=250; *Gg=250; *Bb=250;
				}
	else if(country==20)
				{
					*Rr=100; *Gg=250; *Bb=150;
				}
	else if(country==228)
				{
					*Rr=250; *Gg=20; *Bb=100;
				}
	else if(country==162)
				{
					*Rr=50; *Gg=120; *Bb=250;
				}
	else if(country==94)
				{
					*Rr=250; *Gg=250; *Bb=100;
				}
	else if(country==103)
				{
					*Rr=110; *Gg=220; *Bb=100;
				}
	else if(country==197)
				{
					*Rr=10; *Gg=250; *Bb=100;
				}
	else if(country==114)
				{
					*Rr=250; *Gg=120; *Bb=10;
				}
	else if(country==191)
				{
					*Rr=20; *Gg=50; *Bb=250;
				}
	else if(country==240)
	{
		*Rr=200; *Gg=250; *Bb=250;
	}
	else 
	{
		int rr = country;
						
		if(rr > 255) rr = 255;
		*Rr=(int)(255-rr);
		*Gg=(int)(rr);
		*Bb=(int)(rr-255);
		*Rr=min(255, max(0, *Rr));
		*Gg=min(255, max(0, *Gg));
		*Bb=min(255, max(0, *Bb));
	}
}

void CropColor(int crop, float ha, int* Rr, int* Gg, int* Bb)
{
	int rr = (int)(22.025*log(ha) - 0.9524);
						
	if(rr > 255) rr = 255;
	*Rr=(int)(255-rr);
	*Gg=(int)(255-rr);
	*Bb=(int)(255-rr);
	*Rr=min(255, max(0, *Rr));
	*Gg=min(255, max(0, *Gg));
	*Bb=min(255, max(0, *Bb));
}

void SoilColor(int soil, float SoilPara, int* Rr, int * Gg, int* Bb)
{
	float SP;
	if(soil==1||soil==2) SP = 42.134 * (float)log(SoilPara) + 285.96;
	else if(soil==3||soil==4) SP = 253.57 * SoilPara - 0.9524;
	else if(soil==5||soil==6) SP = 33.81 * SoilPara - 68.571;
	else if(soil==7||soil==8) SP = 161.06 * SoilPara - 29.856;
	else {}
	
	int rr = (int)(SP);
						
	if(rr > 255) rr = 255;
	*Rr=(int)(255-rr);
	*Gg=(int)(255-rr);
	*Bb=(int)(255-rr);
	*Rr=min(255, max(0, *Rr));
	*Gg=min(255, max(0, *Gg));
	*Bb=min(255, max(0, *Bb));
}

void ManageColor(int manage, float ManagePara, int* Rr, int * Gg, int* Bb)
{
	float SP;
	if(manage==1) SP = 10.0 * (float)log(ManagePara);
	else if(manage==2) SP = 10.0 * (float)log(ManagePara);
	else if(manage==3) SP = 2.5 * ManagePara;
	else {}
	
	int rr = (int)(SP);
						
	if(rr > 255) rr = 255;
	*Rr=(int)(255-rr);
	*Gg=(int)(255-rr);
	*Bb=(int)(255-rr);
	*Rr=min(255, max(0, *Rr));
	*Gg=min(255, max(0, *Gg));
	*Bb=min(255, max(0, *Bb));
}

void Color1(float FT, int *Rr,int *Gg,int *Bb, int Item)
{
	if(Item==46||Item==47)//SOC
	{
		{
			*Bb=255-(int)(FT*30.0); 
			*Gg=255-(int)(FT*30.0); 
			*Rr=255-(int)(FT*1.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==48||Item==49)//clay
	{
		{
			*Gg=255-(int)(FT*4.0);
			*Bb=255-(int)(FT*4.0); 
			*Rr=255-(int)(FT*2.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==50||Item==51)//pH
	{
		{
			*Gg=255-(int)(FT*0.41);
			*Bb=255-(int)(FT*0.1); 
			*Rr=255-(int)(FT*0.25);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else //if(Item==1)//temperature
	{
		if(FT<=0.0)
		{
			*Rr=255-(int)(-FT*5.0);
			*Gg=255-(int)(-FT*5.0);
			*Bb=255;
			CheckLimit(Rr,Gg,Bb);
		}
		else
		{
			*Rr=255; 
			*Gg=255-(int)(FT*5.0); 
			*Bb=255-(int)(FT*5.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}

/*	else if(Item==2)//precipitation
	{
		if(FT<0.0)
		{
			*Rr=255-(int)(-FT*5.0);
			*Gg=255-(int)(-FT*5.0);
			*Bb=255;
			CheckLimit(Rr,Gg,Bb);
		}
		else
		{
			*Bb=255; 
			*Gg=255-(int)(FT/12.0); 
			*Rr=255-(int)(FT/12.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==3)//total ag land, km2
	{
		if(FT<0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*2.5); 
			*Gg=255-(int)(FT*3.0); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==4)//cropland, km2
	{
		if(FT<0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*3.0); 
			*Gg=255-(int)(FT*3.0); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==5)//grassland
	{
		if(FT<0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.0); 
			*Gg=255-(int)(FT*2.0); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==6)//fertilizer N for cropland
	{
		if(FT<0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.0); 
			*Gg=255-(int)(FT*1.0); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==7)//fertilizer-N for grassland
	{
		if(FT<0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.0); 
			*Gg=255-(int)(FT); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==8)//manure-N
	{
		if(FT<0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.7); 
			*Gg=255-(int)(FT*1.5); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}*/
	/*else if(Item==9)//fertilizer-N for legume crops
	{
		if(FT<=0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.0); 
			*Gg=255-(int)(FT); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==10)//manure-N for rice
	{
		if(FT<=0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.0); 
			*Gg=255-(int)(FT); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==11)//manure-N for upland crops
	{
		if(FT<=0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.0); 
			*Gg=255-(int)(FT); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==12)//manure-N for legume crops
	{
		if(FT<=0.0)
		{
			*Rr=10;*Gg=90;*Bb=90;
		}
		else
		{
			*Bb=255-(int)(FT*1.0); 
			*Gg=255-(int)(FT); 
			*Rr=200;//-(int)(FT/24.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}*/
/*	else if(Item==9)//SOC
	{
		if(FT<=0.0)
		{
			*Rr=255-(int)(-FT*5.0);
			*Gg=255-(int)(-FT*5.0);
			*Bb=255;
			CheckLimit(Rr,Gg,Bb);
		}
		else
		{
			*Bb=255-(int)(FT*30.0); 
			*Gg=255-(int)(FT*30.0); 
			*Rr=200-(int)(FT*1.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}
	else if(Item==10)//clay
	{
		if(FT<=0.0)
		{
			*Rr=255-(int)(-FT*5.0);
			*Gg=255-(int)(-FT*5.0);
			*Bb=255;
			CheckLimit(Rr,Gg,Bb);
		}
		else
		{
			*Gg=255-(int)(FT*4.0);
			*Bb=255-(int)(FT*4.0); 
			*Rr=255-(int)(FT*2.0);
			CheckLimit(Rr,Gg,Bb);
		}
	}*/
}

void CheckLimit(int *Rr,int *Gg,int *Bb)
{
	if(*Rr>255) *Rr=255;
		if(*Gg>255) *Gg=255;
		if(*Bb>255) *Bb=255;
		if(*Rr<0) *Rr=0;
		if(*Gg<0) *Gg=0;
		if(*Bb<0) *Bb=0;
}

int RandomGeneratorA(int ss)
{
	int RN;

	time_t t = time(NULL);

	srand(t);

	RN = rand() % ss;

	RN += 1;

	return(RN);
}

void SoilConvert(float lat1, float lat2, float lon1, float lon2)
{
		float FT, jf;
		int m_Column, m_Row, jd, r, c;
		
		CString TargetFile, jj;
		FILE *TF;

		TargetFile.Format("%s\\Database\\Globe\\Lib_map\\5minute\\%s.map", ROOTDIR, "GlobeSOC_5min");
		TF=fopen(TargetFile, "r");
		if(TF==NULL)
		{
			CString note;
			note.Format("Cannot open %s", TargetFile);
			AfxMessageBox(note);
			exit(0);
		}
		
		fscanf(TF, "%s %d", jj, &m_Column);
		fscanf(TF, "%s %d", jj, &m_Row);
		fscanf(TF, "%s %f", jj, &jf);
		fscanf(TF, "%s %f", jj, &jf);
		fscanf(TF, "%s %f", jj, &jf);
		fscanf(TF, "%s %d", jj, &jd);

		int s=0;
		for(r=1; r<=m_Row; r++)
		{
			for(c=1; c<=m_Column; c++)
			{
				fscanf(TF, "%f", &FT);
				
				float LON, LAT;
				LON = -180.0 + c * 0.0833333;
				LAT = 90 - r * 0.0833333;

				if(LON>=lon1&&LON<lon2&&LAT>=lat1&&LAT<lat2)
				{
					s++;
					SoilData[s] = FT;									
				}
				if(s==36) break;
			}
			if(s==36) break;
		}
		fclose(TF);
}

void GlobeMap::OnSelMapFile() 
{
	// TODO: Add your control notification handler code here
	
	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_MapFileName.GetCount();
	if (num==1) return;
	
	k=m_MapFileName.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(MapFileName,cst);
		m_MapFileName.InsertString(k,MapFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_MapFileName.GetCount()==1) break;
		k++;
	}
	m_MapFileName.SetCurSel(k);

	DrawMap();
}


void GlobeMap::DrawMap(void)
{
	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3900);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));	

	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);

	pDC.SetBkMode(TRANSPARENT);	

	pDC.FillSolidRect(45, 195, 1455, 730, RGB(220,220,220));

	UpdateData(TRUE);

	char TargetFile[200];
	FILE *TF;

	char jj[300];
	int jd, Rr, Bb, Gg, r, c, x=0;
	float CellSize, jf, z, FT, Fcolor;
	int d=200, dd=50, w, m_Column, m_Row;
		
	sprintf(TargetFile, "%s", MapFileName);
	TF=fopen(TargetFile, "r");
	if(TF==NULL)
	{
		CString note;
		note.Format("Cannot open %s", TargetFile);
		AfxMessageBox(note);
		exit(0);
	}

	fscanf(TF, "%s %d", jj, &m_Column);
	fscanf(TF, "%s %d", jj, &m_Row);
	fscanf(TF, "%s %f", jj, &jf);
	fscanf(TF, "%s %f", jj, &jf);
	fscanf(TF, "%s %f", jj, &CellSize);
	fscanf(TF, "%s %d", jj, &jd);

	if(m_Column==720)
	{
		w=2;
		z=2.0;
		Fcolor = 300000.0;
	}
	else if(m_Column==4320)
	{
		w=1;
		z=0.333;
		Fcolor = 50000.0;
	}

//////////////////////////////////////Convert soil ID to range
/*		CString SRmax, SRmin;
		FILE *Rmax, *Rmin;

		SRmax.Format("%s\\Database\\Globe\\Lib_map\\PHmax.MAP");
		Rmax=fopen(SRmax, "w");
		if(Rmax==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SRmax);
			AfxMessageBox(note);
			exit(0);
		}

		SRmin.Format("%s\\Database\\Globe\\Lib_map\\PHmin.MAP");
		Rmin=fopen(SRmin, "w");
		if(Rmin==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SRmin);
			AfxMessageBox(note);
			exit(0);
		}*/
//////////////////////////////////////////////////////////////////
	int GCID=0;			
	for(r=1; r<=m_Row; r++)
	{
		for(c=1; c<=m_Column; c++)
		{
			GCID++;
			fscanf(TF, "%f", &FT);

			float CG = 19.675 * (float)log(FT) - 20.957; 

			if(FT<=-9998.0)//||FT>100.0)
			{
				Rr=10;Gg=90;Bb=90;
				//fprintf(Rmax, "%f\n", 0.0);
			}
			else
			{
				Rr = 255-(int)(CG*0.6);
				Bb = 255-(int)(CG*1.0);
				Gg = 255-(int)(CG*1.0);

				if(Bb<0)
				{
					CString note;
					note.Format("FT= %f", FT);
					AfxMessageBox(note);
					//exit(0);
				}

				GCID++;
				//fprintf(Rmax, "%d  %f\n", GCID, FT);

			}

			pDC.FillSolidRect(dd+(int)(c*z), d+(int)(r*z), w, w, RGB(Rr,Gg,Bb));				
		}//end of column
		//fprintf(Rmax, "\n");
		//fprintf(Rmin, "\n");
	}//end of row

	//fclose(Rmax);
	//fclose(Rmin);
///////////////////////Convert a 5-minute map to two 30-minute maps with max and min values
/*
		sprintf(TargetFile, "%s\\Database\\Globe\\Lib_map\\5minute\\GlobeSOC_%min.map");
			TF=fopen(TargetFile, "r");
			if(TF==NULL)
			{
				CString note;
				note.Format("Cannot open %s", TargetFile);
				AfxMessageBox(note);
				exit(0);
			}

		CString SRmax, SRmin;
		FILE *Rmax, *Rmin;

		SRmax.Format("%s\\Database\\Globe\\Lib_map\\SOCmax.MAP");
		Rmax=fopen(SRmax, "w");
		if(Rmax==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SRmax);
			AfxMessageBox(note);
			exit(0);
		}

		SRmin.Format("%s\\Database\\Globe\\Lib_map\\SOCmin.MAP");
		Rmin=fopen(SRmin, "w");
		if(Rmin==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SRmin);
			AfxMessageBox(note);
			exit(0);
		}

		float DT[4321][7];

		m_Row = 0;
   		for(int Rr=1; Rr<=360; Rr++)
		{
			for(r=1; r<=6; r++)
			{
				m_Row++;

				for(c=1; c<=m_Column; c++)
				{
					fscanf(TF, "%f", &DT[c][r]);

					if(DT[c][r]<=-9998.0)
					{
						Rr=10;Gg=90;Bb=90;
					}
					else
					{
						Color1(DT[c][r], &Rr,&Gg,&Bb, SelectMap);				
					}

					pDC.FillSolidRect(dd+(int)(c*z), d+(int)(m_Row*z), w, w, RGB(Rr,Gg,Bb));
				}
			}

			int qq=0;
			float Smax=0.00001;
			float Smin=1000.0;

			for(int pp=1; pp<=720; pp++)
			{
				for(c=qq+1; c<=qq+6; c++)
				{
					for(r=1; r<=6; r++)
					{
						//if(DT[c][r]>0.0)
						{
							Smax = max(DT[c][r], Smax);
							Smin = min(DT[c][r], Smin);
						}
					}					
				}		

				if(Smax>0.0 && Smin <0.0) Smin = Smax * 0.5;

				fprintf(Rmax, "%9.4f ", Smax*0.01);
				fprintf(Rmin, "%9.4f ", Smin*0.01);

				qq+=6;

				Smax=0.00001;
				Smin=1000.0;
			}
			fprintf(Rmax, "\n");
			fprintf(Rmin, "\n");
		}
		fclose(Rmax);
		fclose(Rmin);
*/
/////////////////////////////////////////////

		fclose(TF);
		//fclose(TF2);
}

void GlobeMap::OnDblclkMapFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;
		// delete a selected file from the list
	num=m_MapFileName.GetCount();
	i=m_MapFileName.GetCurSel();
	
	CString fname;
	m_MapFileName.GetText(i,fname);
	m_MapFileName.DeleteString(i);	
	return;
}

void ConvertGlobalClimateToCountry(int CountryN, CString CountryCall)
{
	int jday;
	float MaxT, MinT, prec, WindSpeed, PAR;
	char ClimSource[100], ClimTarget[100];
	FILE *CS, *CT;

	sprintf(ClimSource, "%s\\database\\Globe\\Globe_climate_data\\Global_climate_2000\\%d_2000", ROOTDIR, CountryN);
	CS=fopen(ClimSource, "r");
	if(CS==NULL) note(0, ClimSource);
					
	sprintf(ClimTarget, "%s\\database\\%s\\Lib_clim\\2000\\%d", ROOTDIR, CountryCall, CountryN);
	CT=fopen(ClimTarget, "w");
	if(CT==NULL) note(1, ClimTarget);
	
	CString Title;

	fscanf(CS, "%s", Title);
	fprintf(CT, "%s_%d\n", CountryCall, CountryN); 
	for(;;)
	{
		if(fscanf(CS, "%d %f %f %f %f %f", &jday, &MaxT, &MinT, &prec, &WindSpeed, &PAR)!=6)
			break;
		prec *= 0.1;//mm -> cm
		fprintf(CT, "%d %f %f %f\n", jday, MaxT, MinT, prec);
	}

	fclose(CS);
	fclose(CT);

}

float CalculateSoilDensity(float m_SoilClay, float m_SoilOrganic)
{
	if (m_SoilClay<=0) return -1;
	if (m_SoilOrganic<=0) return -1;
	float Fo,Dbo,Dbm,SD;

    Fo  = (float)(2.0 * m_SoilOrganic);
    Dbo = (float).14;
    Dbm = (float)(1.3 + 2.65 * m_SoilClay - 2.15 * m_SoilClay * m_SoilClay);
    SD  = (Dbm * Dbo / (Fo * Dbm + (1.0 - Fo) * Dbo));
	
	return SD;
}

void GlobeMap::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	WorldMapping(0, 0, 0, 0);
}

void GlobeMap::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	WorldMapping(1, 0, 0, 0);
}

void GlobeMap::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	WorldMapping(2, 0, 0, 0);
}

void GlobeMap::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	WorldMapping(3, 0, 0, 0);
}

void GlobeMap::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	WorldMapping(4, 0, 0, 0);
}

void GlobeMap::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	WorldMapping(5, 0, 0, 0);
}

void GlobeMap::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	WorldMapping(6, 0, 0, 0);
}

void GlobeMap::OnSelchangeItem() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GlobalCrop = m_Item.GetCurSel();

	UpdateData(FALSE);

	WorldMapping(m_SelectRegion, GlobalCrop, 0, 0);
}

void GlobeMap::OnSelchangeSelectSoil() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GlobalSoil = m_SelectSoil.GetCurSel();

	UpdateData(FALSE);

	WorldMapping(m_SelectRegion, 0, GlobalSoil, 0);
}

void GlobeMap::OnSelchangeSelectManage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GlobalManage = m_SelectManage.GetCurSel();

	UpdateData(FALSE);

	WorldMapping(m_SelectRegion, 0, 0, GlobalManage);
}
