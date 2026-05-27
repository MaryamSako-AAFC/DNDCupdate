// GasFlux.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
//#include "GasFlux.h"
#include "graphexDoc.h"
#include "graphexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void flux_color(float flux, int *c1, int *c2, int *c3);
void read_scale(int stateID);
float find_flux(int stateID, int CountyID, int gasID, int rangeID, char *FileLocation, float *sum, float *ha);

float X1,Y1;
int X2,Y2;
/////////////////////////////////////////////////////////////////////////////
// GasFlux dialog


GasFlux::GasFlux(CWnd* pParent /*=NULL*/)
	: CDialog(GasFlux::IDD, pParent)
{
	//{{AFX_DATA_INIT(GasFlux)
	m_GasFlux = -1;
	m_Range = -1;
	m_FileLocation = _T("");
	//}}AFX_DATA_INIT
}


void GasFlux::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GasFlux)
	DDX_Control(pDX, IDC_FluxDataset, m_FluxDataset);
	DDX_Radio(pDX, IDC_GasFlux, m_GasFlux);
	DDX_Radio(pDX, IDC_Range, m_Range);
	DDX_Text(pDX, IDC_FileLocation, m_FileLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GasFlux, CDialog)
	//{{AFX_MSG_MAP(GasFlux)
	ON_BN_CLICKED(IDC_SelectDataset, OnSelectDataset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GasFlux message handlers

void GasFlux::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(strlen(m_FileLocation)==0) 
	{
		AfxMessageBox("Please specify location of your data files");
		return;
	}
	if(m_GasFlux==-1) 
	{
		AfxMessageBox("Please specify flux item");
		return;
	}
	if(m_Range==-1) 
	{
		AfxMessageBox("Please specify range");
		return;
	}

	char FF[200];
	FILE *region;
	sprintf(FF, "%s\\GasFlux", INTER);
	region = fopen(FF, "w");
	fprintf(region, "%s\n", m_FileLocation);
	fprintf(region, "%d %d\n", m_GasFlux+1, m_Range+1);
	fclose (region);	

		
	CDialog::OnOK();
}

void GasFlux::draw_flux(CGraphexDoc *pDoc, int countryID, int stateID, int gasID, int rangeID, char *FileLocation)
{

	int pairs=0, StateID, i, TotalCounty;
	long int CountyID, MapID, map_id;
	float Da, Db, flux;
	int c1=255, c2=255, c3=255;

	int w1=200,w2=200,w3=200;
	int q1=0,q2=0,q3=0;
	float TotalFlux = 0.0;
	float sum;
	float Totalha = 0.0;
	float ha; 
	
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

	CBrush Brush1(RGB(w1,w2,w3));		//define a brush

	art.FillRect(rectClient, &Brush1);

	Brush1.DeleteObject();

	CString led;

	art.SetTextColor(RGB(q1,q2,q3));

	for(i=0; i<=10; i++)
	{
		if(gasID==1)
		{
			flux = (float)i - 5.0;
			flux_color(flux, &c1, &c2, &c3);
			art.FillSolidRect(250+i*50, 580, 50, 10, RGB(c1,c2,c3));
			led.Format ("     -2000   -1500    -1000      -500        0        500      1000       1500        2000        2500       kg C/ha per yr");
		}
		else if(gasID==2)
		{
			flux = i;
			flux_color(flux, &c1, &c2, &c3);
			art.FillSolidRect(250+i*50, 580, 50, 10, RGB(c1,c2,c3));
			led.Format ("0         1           2          3           4           5          6          7           8           9          10  kg N2O-N/ha per yr");
		}
		else {}

	}
	
	art.TextOut(250, 600, led);

	CString GAS[20] = {" ", "Net CO2", "N2O", "CH4", "N Leaching",
						"NH3", "NO", "Sorhgum", "Cotton", "Soybaen", "Potato",
						"Beet", "Peanut", "Vegetable", "Pineapple", "Sugarcane",
						"Tobacco", "Sunflower", "Legume hay", "Non-legume hay"};

	CFont hNewFont;
	TEXTMETRIC tm;
	CString dndc;
	dndc.Format("Agricultural %s emission rates in California", GAS[gasID]);

		hNewFont.CreateFont(30,0,0,0,FW_SEMIBOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(10,100,50));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.TextOut(240, 20, dndc);
		
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

	CString RF;
	FILE *ref;

	RF.Format("%s\\Database\\USA90\\GIS\\USA5_%d", ROOTDIR, stateID);
	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not find file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}
	else
	{
		TotalFlux = 0.0;
		Totalha = 0.0;
		TotalCounty = 0;
		for(;;)
		{
		if(fscanf(ref, "%ld %ld", &CountyID, &MapID)!=2) 
			break;
		else
		{
			StateID = (int)((float)CountyID/1000.0);

			//if(StateID==2) goto NEXTC;

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

					flux = find_flux(stateID, CountyID, gasID, rangeID, FileLocation, &sum, &ha);

					TotalFlux += sum;
					Totalha += ha;

					if(gasID==1)
					{
						flux /= 500.0;
					}
					else if(gasID==2)
					{
						flux *= 1.0;
					}

					flux_color(flux, &c1, &c2, &c3);

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
	}//end of for{}
	}

	CString SUM;
	if(gasID==1) SUM.Format("Total flux: %8.3f Tg C", TotalFlux*0.001);
	if(gasID==2) SUM.Format("Total flux: %8.0f ton N", TotalFlux);
	art.SetTextColor(RGB(10,100,50));
	//pDC->SetBkColor(TRANSPARENT);
	
	art.TextOut(20, 500, SUM);



}

void flux_color(float flux, int *c1, int *c2, int *c3)
{
	if(flux >= 0.0)
	{
		*c1 = (int)(-16.25 * flux + 251.4);
		*c2 = (int)(250);
		*c3 = (int)(-53.7 * flux + 242.6);

		if(*c1>255) *c1=255;
		if(*c1<0) *c1=0;
		if(*c2>255) *c2=255;
		if(*c2<0) *c2=0;
		if(*c3>255) *c3=255;
		if(*c3<0) *c3=0;
	}
	else
	{
		*c1 = 250;
		*c2 = (int)(-53.7 * (-flux) + 242.6);
		*c3 = (int)(-53.7 * (-flux) + 242.6);

		if(*c1>255) *c1=255;
		if(*c1<0) *c1=0;
		if(*c2>255) *c2=255;
		if(*c2<0) *c2=0;
		if(*c3>255) *c3=255;
		if(*c3<0) *c3=0;
	}

}

void read_scale(int stateID)
{
	switch (stateID)
	{
	case 0:	X1 = 133.0;
			X2 = 14;
			Y1 = 55.0;
			Y2 = 18;
			break;
	case 6:	X1 = 133.0;
			X2 = 41;
			Y1 = 43.5;
			Y2 = 52;
			break;

	}
	
}

float find_flux(int stateID, int CountyID, int gasID, int rangeID, char *FileLocation,
				float *sum, float *ha)
{
	float gasflux1=0.0, gasflux2=0.0, gasflux=0.0, jf, sum1=0.0, sum2=0.0, ha0=0.0;
	
	CString GF1, GF2, FileName;
	FILE* gf1;
	FILE* gf2;
	char ww[300];
	int TotalCrops, cID, i;

	/*CString STATE[50]={"USA", "Alabama", "Arizona", "Arkansas", "California",
					"Colorado", "Connecticut", "Delaware", "DC", "Florida", 
					"Georgia", "Idaho", "Illinois", "Indiana", "Iowa", 
					"Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", 
					"Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", 
					"Montana", "Nebraska", "Nevada", "New_Hampshire", "New_Jersey", 
					"New_Mexico", "New_York", "North_Carolina", "North_Dakota", "Ohio", 
					"Oklahoma", "Oregon", "Pennsylvania", "Rhode_Island", "South_Carolina", 
					"South_Dakota", "Tennessee", "Texas", "Utah", "Vermont", 
					"Virginia", "Washington", "West_Virginia", "Wisconsin", "Wyoming"};*/

	CString UUU[50] = {	  "", "AL", "AZ", "AK", "CA", 
						"CO", "CT", "DE", "DC", "FL", 
						"GA", "ID", "IL", "IN", "IA", 
						"KS", "KY", "LA", "ME", "MD", 
						"MA", "MI", "MN", "MS", "MO", 
						"MT", "NE", "NV", "NH", "NJ", 
						"NM", "NY", "NC", "ND", "OH", 
						"OK", "OR", "PA", "RI", "SC", 
						"SD", "TN", "TX", "UT", "VT", 
						"VA", "WA", "WV", "WI", "WY"};

	CString FF[5]={" ", "dSOC", "N2O", "CH4", "LeachedN"};

	
	GF1.Format("%s\\sum_min_%s_1_yr1", FileLocation, FF[gasID]);
	GF2.Format("%s\\sum_max_%s_1_yr1", FileLocation, FF[gasID]);
	
	gf1=fopen(GF1, "r");
	if(gf1==NULL)
	{
		CString note;
		note.Format("Can not find file %s", GF1);
		AfxMessageBox(note);
		exit(0); 
	}

	fgets(ww, 300, gf1);
	fgets(ww, 300, gf1);
	fscanf(gf1, "%d", &TotalCrops);
	fgets(ww, 300, gf1);

	for(;;)
	{
		if(fscanf(gf1, "%d", &cID)!=1) 
		{
			gasflux1 = 0.0;
			break;
		}
		else
		{
			if(cID==CountyID)
			{
				for(i=1;i<=TotalCrops;i++) fscanf(gf1, "%f", &jf);
				fscanf(gf1, "%f %f %f", &sum1, &ha0, &gasflux1);
				break;
			}
			else
			{
				fgets(ww, 300, gf1);
			}
		}
	}
	fclose(gf1);

	gf2=fopen(GF2, "r");
	if(gf2==NULL)
	{
		CString note;
		note.Format("Can not find file %s", GF2);
		AfxMessageBox(note);
		exit(0); 
	}

	fgets(ww, 300, gf2);
	fgets(ww, 300, gf2);
	fscanf(gf2, "%d", &TotalCrops);
	fgets(ww, 300, gf2);

	for(;;)
	{
		if(fscanf(gf2, "%d", &cID)!=1) 
		{
			gasflux2 = 0.0;
			break;
		}
		else
		{
			if(cID==CountyID)
			{
				for(i=1;i<=TotalCrops;i++) fscanf(gf2, "%f", &jf);
				fscanf(gf2, "%f %f %f", &sum2, &ha0, &gasflux2);
				break;
			}
			else
			{
				fgets(ww, 300, gf2);
			}
		}
	}
	fclose(gf2);

	if(rangeID==1) 
	{
		gasflux = gasflux2;
		*sum = sum2;
	}
	else if(rangeID==3) 
	{
		gasflux = gasflux1;
		*sum = sum1;
	}
	else 
	{
		gasflux = (gasflux1+gasflux2)*0.5;
		*sum = ((sum1+sum2)*0.5);
	}

	*ha = ha0;
	

	return (gasflux);
}

void GasFlux::OnSelectDataset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char FileName[255];
	CString cst;

	//CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
	//	"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		NULL, NULL );

	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_FluxDataset.GetCount();
	if (num==1) return;
	
	k=m_FluxDataset.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_FluxDataset.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_FluxDataset.GetCount()==1) break;
		k++;
	}
	m_FluxDataset.SetCurSel(k);


	
}
