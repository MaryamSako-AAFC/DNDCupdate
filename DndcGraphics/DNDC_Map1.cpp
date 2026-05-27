// DNDC_Map1.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "DNDC_Map1.h"
#include "math.h"
#include "dndc_tool.h"
#include "GlobeMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char DndcFileName[300];
void CellColor(int FluxType, float Para, int* Rr, int * Gg, int* Bb);
/////////////////////////////////////////////////////////////////////////////
// DNDC_Map dialog


DNDC_Map::DNDC_Map(CWnd* pParent /*=NULL*/)
	: CDialog(DNDC_Map::IDD, pParent)
{
	//{{AFX_DATA_INIT(DNDC_Map)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DNDC_Map::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DNDC_Map)
	DDX_Control(pDX, IDC_DndcFileList, m_DndcFileList);
	DDX_Control(pDX, IDC_MapItem, m_MapItem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DNDC_Map, CDialog)
	//{{AFX_MSG_MAP(DNDC_Map)
	ON_BN_CLICKED(IDC_SelectDNDCFile, OnSelectDNDCFile)
	ON_LBN_DBLCLK(IDC_DndcFileList, OnDblclkDndcFileList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DNDC_Map message handlers

void DNDC_Map::OnSelectDNDCFile() 
{
	// TODO: Add your control notification handler code here
/*	int m_LayerNumber=1;

	CString cst;
	static int ww=0;
	ww++;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_DndcFileList.GetCount();
	if (num==m_LayerNumber) return;
	
	k=m_DndcFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	int i=0;
	for (;;)
	{
		i++;
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(DndcFileName,cst);
		m_DndcFileList.InsertString(k,DndcFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_DndcFileList.GetCount()==m_LayerNumber) break;
		k++;
	}
	m_DndcFileList.SetCurSel(k);
*/

	int i, j, GridID, CroppingID, year;
	char SF[200], TF[200], domain[200], www[300], item[150][150], crop[150], js[50];
	float ha, rate[150], sum[150], TotalSum[150], TotalHa;
	CString unit[31]={"", "Unit", "ha","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C",
		"ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N",
		"million_m3","million_m3","million_m3","million_m3","million_m3","million_m3","million_m3"};

	CString MinMax[2]={"minimum", "maximum"};
	FILE *sf, *tf;
	sprintf(domain, "Asia");

	for(i=0; i<=1; i++)
	{
		sprintf(SF, "%s\\GlobeResult\\%s_%s_rate.txt", ROOTDIR, MinMax[i], domain);
		//sprintf(SF, "%s", DndcFileName);
		sf=fopen(SF, "r");
		if(sf==NULL)
		{
			CString note;
			note.Format("Cannot open %s", SF);
			AfxMessageBox(note);
			exit(0);
		}

		sprintf(TF, "%s\\GlobeResult\\%s_%s_sum.txt", ROOTDIR, MinMax[i], domain);
		//sprintf(SF, "%ss", DndcFileName);
		tf=fopen(TF, "w");
		if(tf==NULL)
		{
			CString note;
			note.Format("Cannot create %s", TF);
			AfxMessageBox(note);
			exit(0);
		}

		for(j=1;j<=33;j++) 
			fscanf(sf, "%s", item[j]);

		for(j=1;j<=29;j++)
			fscanf(sf, "%s", js);
		//sgets(www, 300, sf);
		
		fprintf(tf, "%10s %15s ", item[1], item[4]);
		for(j=6;j<=33;j++) fprintf(tf, "%15s ", item[j]);
		fprintf(tf, "\n");
		
		//fgets(www, 200, sf);
		//fgets(www, 200, sf);
		//fgets(www, 200, sf);
		
		for(j=1;j<=30;j++) fprintf(tf, "%15s ", unit[j]);  						
		fprintf(tf, "\n");

		GridID = 0;
		int OldID=0;
		int k=0;
		for(;;)
		{	
			k++;

			if(fscanf(sf, "%d %d %s %f %d", &GridID, &CroppingID, crop, &ha, &year)!=5)
			{
				fprintf(tf, "%10d %10.0f ", OldID, TotalHa);
				for(j=1;j<=28;j++) 
				{
					if(j==3) fprintf(tf, "%15.3f ", TotalSum[j]);
					else if(j<=8||j>=22) fprintf(tf, "%15.0f ", TotalSum[j]);
					else fprintf(tf, "%15.3f ", TotalSum[j]);
					TotalSum[j] = 0.0;
				}
				fprintf(tf, "\n");
				fclose(sf);
				fclose(tf);
				//AfxMessageBox("Good");
				break;
			}

			if(k==1)
			{
				for(j=1;j<=28;j++) TotalSum[j] = 0.0;
				TotalHa = 0.0;
			}
			else
			{
				if(GridID!=OldID) 
				{
					fprintf(tf, "%10d %10.0f ", OldID, TotalHa);
					for(j=1;j<=28;j++) 
					{
						if(j==3) fprintf(tf, "%15.3f ", TotalSum[j]);
						else if(j<=8||j>=22) fprintf(tf, "%15.0f ", TotalSum[j]);
						else fprintf(tf, "%15.3f ", TotalSum[j]);
						TotalSum[j] = 0.0;
					}
					fprintf(tf, "\n");					
					TotalHa = 0.0;
				}
			}

			//fscanf(sf, "%f", &ha);
			for(j=1;j<=28;j++) fscanf(sf, "%f", &rate[j]);
			
			if(CroppingID!=105)//exclude grassland from global database
			//if(CroppingID!=12)//exclude grassland from USA national database
			{
			//////////////////////////////
			for(j=1;j<=28;j++) 
			{
				if(j==1) sum[j] = rate[j] * ha * 0.001; // total SOC, kg C -> 1000 ton C
				else if(j==2) sum[j] = rate[j] * ha * 0.001; // total dSOC, kg C -> ton C
				else if(j==3) sum[j] = rate[j] * ha * 0.001;//CH4, kg C -> ton C
				else if(j>=4&&j<=8) sum[j] = rate[j] * ha * 0.001; // total C flux, kg C -> ton C
				else if(j>=9&&j<=21) sum[j] = rate[j] * ha * 0.001;// total N flux, kg N -> ton N
				else sum[j] = rate[j] * ha * 10.0 * 0.000001; //water, mm-> million cubic m
				
				TotalSum[j] += sum[j];
			}
			TotalHa += ha;	
			/////////////////////////////
			}

			OldID = GridID;
		}

	}

	AfxMessageBox("Conversion is done");


}

void DNDC_Map::OnOK() 
{
	// TODO: Add extra validation here
	//Convert rate to sum

	int i, j, GridID, CroppingID, year, mmm;
	char SF[200], TF[200], domain[200], www[300], item[150][150], crop[150], js[50];
	float ha, rate[150], sum[150], TotalSum[150], TotalHa;
	CString unit[31]={"", "Unit", "ha","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C",
		"ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N",
		"million_m3","million_m3","million_m3","million_m3","million_m3","million_m3","million_m3"};
	char ItemName[50][50]={"Area","SOC","dSOC","CH4","GrainC","ShootC","RootC","ManureC","LitterC",
		"N2O","NO","N2","NH3","UptakeN","LeachN","DepositN","FixedN","Miner_N","Fert_N","ManureN",
		"dSON","dSIN","H2Otran","H2Oevap","H2Orunof","H2Oleach","H2Oirri","H2Oprec","dSoilH2O"};
	//0:Area, 1:SOC, 2:dSOC, 3:CH4, 4:GrainC, 5:ShootC, 6:RootC, 7:ManureC, 8:LitterC, 9:N2O,
	//10:NO, 11:N2, 12:NH3, 13:UptakeN, 14:LeachN, 15:DepositN, 16:FixedN, 17:Miner_N, 18:Fert_N, 19:ManureN,
	//20:dSON, 21:dSIN, 22:H2Otran, 23:H2Oevap, 24:H2Orunof, 25:H2Oleach, 26:H2Oirri, 27:H2Oprec, 28:dSoilH2O 


	CString MinMax[2]={"minimum", "maximum"};
	
	FILE *sf, *tf;
	sprintf(domain, "Asia");

/*	for(i=0; i<=1; i++)
	{
		sprintf(SF, "%s\\GlobeResult\\%s_%s_rate.txt", MinMax[i], ROOTDIR, domain);
		//sprintf(SF, "%s", DndcFileName);
		sf=fopen(SF, "r");
		if(sf==NULL)
		{
			CString note;
			note.Format("Cannot open %s", SF);
			AfxMessageBox(note);
			exit(0);
		}

		sprintf(TF, "%s\\GlobeResult\\%s_%s_sum.txt", MinMax[i], ROOTDIR, domain);
		//sprintf(SF, "%ss", DndcFileName);
		tf=fopen(TF, "w");
		if(tf==NULL)
		{
			CString note;
			note.Format("Cannot create %s", TF);
			AfxMessageBox(note);
			exit(0);
		}

		for(j=1;j<=33;j++) 
			fscanf(sf, "%s", item[j]);

		for(j=1;j<=29;j++)
			fscanf(sf, "%s", js);
		//sgets(www, 300, sf);
		
		fprintf(tf, "%10s %15s ", item[1], item[4]);
		for(j=6;j<=33;j++) fprintf(tf, "%15s ", item[j]);
		fprintf(tf, "\n");
		
		//fgets(www, 200, sf);
		//fgets(www, 200, sf);
		//fgets(www, 200, sf);
		
		for(j=1;j<=30;j++) fprintf(tf, "%15s ", unit[j]);  						
		fprintf(tf, "\n");

		GridID = 0;
		int OldID=0;
		int k=0;
		for(;;)
		{	
			k++;

			if(fscanf(sf, "%d %d %s %f %d", &GridID, &CroppingID, crop, &ha, &year)!=5)
			{
				fprintf(tf, "%10d %10.0f ", OldID, TotalHa);
				for(j=1;j<=28;j++) 
				{
					if(j==3) fprintf(tf, "%15.3f ", TotalSum[j]);
					else if(j<=8||j>=22) fprintf(tf, "%15.0f ", TotalSum[j]);
					else fprintf(tf, "%15.3f ", TotalSum[j]);
					TotalSum[j] = 0.0;
				}
				fprintf(tf, "\n");
				fclose(sf);
				fclose(tf);
				//AfxMessageBox("Good");
				break;
			}

			if(k==1)
			{
				for(j=1;j<=28;j++) TotalSum[j] = 0.0;
				TotalHa = 0.0;
			}
			else
			{
				if(GridID!=OldID) 
				{
					fprintf(tf, "%10d %10.0f ", OldID, TotalHa);
					for(j=1;j<=28;j++) 
					{
						if(j==3) fprintf(tf, "%15.3f ", TotalSum[j]);
						else if(j<=8||j>=22) fprintf(tf, "%15.0f ", TotalSum[j]);
						else fprintf(tf, "%15.3f ", TotalSum[j]);
						TotalSum[j] = 0.0;
					}
					fprintf(tf, "\n");					
					TotalHa = 0.0;
				}
			}

			//fscanf(sf, "%f", &ha);
			for(j=1;j<=28;j++) fscanf(sf, "%f", &rate[j]);
			
			if(CroppingID!=105)//exclude grassland from global database
			//if(CroppingID!=12)//exclude grassland from USA national database
			{
			//////////////////////////////
			for(j=1;j<=28;j++) 
			{
				if(j==1) sum[j] = rate[j] * ha * 0.001; // total SOC, kg C -> 1000 ton C
				else if(j==2) sum[j] = rate[j] * ha * 0.001; // total dSOC, kg C -> ton C
				else if(j==3) sum[j] = rate[j] * ha * 0.001;//CH4, kg C -> ton C
				else if(j>=4&&j<=8) sum[j] = rate[j] * ha * 0.001; // total C flux, kg C -> ton C
				else if(j>=9&&j<=21) sum[j] = rate[j] * ha * 0.001;// total N flux, kg N -> ton N
				else sum[j] = rate[j] * ha * 10.0 * 0.000001; //water, mm-> million cubic m
				
				TotalSum[j] += sum[j];
			}
			TotalHa += ha;	
			/////////////////////////////
			}

			OldID = GridID;
		}

	}

	AfxMessageBox("Conversion is done");
*/
	////////////////////////////////////////////////////////////////////////////

	int Country_ID, Region_ID, SI, grid_ID, cell_ID;
	char Country_name[250][250], Climate_file[200];
	float N_dep, Snow, SOCmax, SOCmin, Claymax, Claymin, pHmax, pHmin, Densmax, Densmin;
	
	char TargetFile[200], IndexFile[200];
	FILE *sii;

	char sj[50];
	int Rr, Bb, Gg, r, c, x=0;
	float z,Fcolor, grid_item[30], lon, lat, CG, abc, cba=0.0;
	int d, dd, w;
	int continent=2;
	int cc, bb, xx, yy, y;


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

	//pDC.FillSolidRect(45, 195, 1455, 730, RGB(220,220,220));

	UpdateData(TRUE);

	SI=m_MapItem.GetCurSel();
	
	//d=200;
	//dd=50;
	/*d=200;
	dd=50;
	w=2;
	z=2.0;
	Fcolor = 300000.0;*/


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

		
	for(mmm=0; mmm<=1; mmm++)
	{
		float flux[250][33]={0.0,0.0};
		float Ksum[250][33]={0.0,0.0};

		sprintf(IndexFile, "%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, domain, domain);
		sii=fopen(IndexFile, "r");
		if(sii==NULL) note(0, IndexFile);
		fgets(www, 300, sii);

		sprintf(TF, "%s\\GlobeResult\\%s_%s_sum.txt", ROOTDIR, MinMax[mmm], domain);
		sprintf(TargetFile, "%s", TF);
		tf=fopen(TargetFile, "r");
		if(tf==NULL) note(0, TargetFile);
		fgets(www, 300, tf);
		fgets(www, 300, tf);
		fgets(www, 300, tf);
		fgets(www, 300, tf);
		
		//for(i=1; i<=30; i++) fscanf(tf, "%s", sj);
		//for(i=1; i<=30; i++) fscanf(tf, "%s", sj);

		for(;;)
		{
			fscanf(tf, "%d", &grid_ID);

	READMORE:

			if(fscanf(sii, "%d %d", &cell_ID, &Country_ID)!=2) break;	

			fscanf(sii, "%s %f %f %s %f %f %f %f %f %f %f %f %f %f %d %d %d", 
				Country_name[Country_ID], &lon, &lat, Climate_file, &N_dep, &Snow,
				&SOCmax, &SOCmin, &Claymax, &Claymin, &pHmax, &pHmin, &Densmax, &Densmin,
				&c, &r, &Region_ID);	

			if(cell_ID!=grid_ID) goto READMORE;
			else
			{
				//0:Area, 1:SOC, 2:dSOC, 3:CH4, 4:GrainC, 5:ShootC, 6:RootC, 7:ManureC, 8:LitterC, 9:N2O,
				//10:NO, 11:N2, 12:NH3, 13:UptakeN, 14:LeachN, 15:DepositN, 16:FixedN, 17:Miner_N, 18:Fert_N, 19:ManureN,
				//20:dSON, 21:dSIN, 22:H2Otran, 23:H2Oevap, 24:H2Orunof, 25:H2Oleach, 26:H2Oirri, 27:H2Oprec, 28:dSoilH2O 

				for(i=0; i<=28; i++)
				{
					fscanf(tf, "%f", &flux[Country_ID][i]);

					if(i==0) Ksum[Country_ID][i] += flux[Country_ID][i];

					if(i==SI) Ksum[Country_ID][i] += flux[Country_ID][i];
				}
			}

			//////////draw map
			if(mmm==0)
			{
				CellColor(SI, flux[Country_ID][SI], &Rr, &Gg, &Bb);		
					
				x=cc*c+xx;
				y=bb*r+yy;

				pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
			}
		}
		fclose(tf);
		fclose(sii);

		CString SSF;
		SSF.Format("%s\\GlobeResult\\%s_country_summary_%s_%s_%s.csv", ROOTDIR, domain, ItemName[SI], unit[SI], MinMax[mmm]);
		FILE *ssf;
		ssf = fopen(SSF, "w");
		if(ssf==NULL) note(0, SSF);

		fprintf(ssf, "%10s,  %25s,  %10s,  %10s\n", "Country_ID", "Country_name", "Cropland_area (ha)", "Total_flux");

		for(i=1; i<=249; i++)
		{
			if(Ksum[i][0]!=0.0)
				fprintf(ssf, "%10d,  %25s,  %10.0f,  %10.0f\n", i, Country_name[i], Ksum[i][0], Ksum[i][SI]);
		}
		fclose(ssf);

		//AfxMessageBox("Calculation is accomplished");
	}

	//AfxMessageBox("Calculation is accomplished");

}

void DNDC_Map::OnDblclkDndcFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;
	
	num=m_DndcFileList.GetCount();
	i=m_DndcFileList.GetCurSel();
	
	CString fname;
	m_DndcFileList.GetText(i,fname);
	m_DndcFileList.DeleteString(i);	
	return;

}

void CellColor(int FluxType, float Para, int* Rr, int * Gg, int* Bb)
{
	float SP;
	/*if(FluxType==1||FluxType==2) SP = 42.134 * (float)log(Para) + 285.96;
	else if(FluxType==3) SP = 253.57 * Para - 0.9524;
	else if(FluxType==5||FluxType==6||FluxType==4) SP = 33.81 * Para - 68.571;
	else if(FluxType==7||FluxType==8) SP = 161.06 * Para - 29.856;
	else {}*/

	//CH4
	if(FluxType==3) 
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 50.0;
	}
	
	int rr = (int)(SP);

	if(rr==0)
	{
		*Rr=255; *Gg=255; *Bb=255;
	}
	else
	{						
		if(rr > 255) rr = 255;
		*Rr=(int)(255-rr);
		*Gg=(int)(300-rr);
		*Bb=(int)(355-rr);
		*Rr=min(255, max(0, *Rr));
		*Gg=min(255, max(0, *Gg));
		*Bb=min(255, max(0, *Bb));
	}
}
