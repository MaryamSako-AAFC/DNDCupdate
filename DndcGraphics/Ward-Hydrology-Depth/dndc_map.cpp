// DNDC_Map.cpp : implementation file
//
#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "Dndc_tool.h"
#include "direct.h"
#include "DNDC_Map.h"
#include "math.h"
#include "SitePara.h"
#include "SelectIrriFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int continent=0, country_ID=0, i, j, grid_ID1, grid_ID2, grid_ID3, SelectedItem, SDF;
int K=54, year=0, TotalYear=1;
float temp[30];
char RootFileName[500], GlobeFileName[500], ExteFileName[500], RegionName[100], MaxMin[20], IRRI[20];
char FFileName[300], domain[200], www[200], rootdir[300], RateName[50], Tail[10], IrriFile[300]; 

char country_name[200], old_country_name[200];
CString item[55]={"",""}, unit[55]={"",""};
CString Mm[4]={"","max","min","ave"};
CString ContName[7]={"","Africa","Asia","Europe","NorthAmerica","Oceania","SouthAmerica"};
CString js;


/*CString unit[52]={"",
"Grid_ID", "System_ID", "SystemName", "ha","Year",
"kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C",
"kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C","kg_C",
"kg_N","kg_N","kg_N","kg_N","kg_N","kg_N","kg_N","kg_N","kg_N","kg_N",
"kg_N","kg_N","kg_N",
"m3","m3","m3","m3","m3","m3","m3",
"degree_C","CountryID","CountryName","None","None"};*/

//int SelectCropNumber[5]={0, 20, 1, 2, 6};

/*
Grid_ID,System_ID,SystemName,Area,Year,
Stub,SOC0-10cm,SOC10-20cm,SOC20-30cm,SOC30-40cm,SOC40-50cm,Total-SOC,ManureC,LitterC,Soil-CO2,
dSOC,GrainC_1,GrainC_2,GrainC_3,ShootC_1,ShootC_2,ShootC_3,RootC_1,RootC_2,RootC_3,CH4,
N2O,NO,N2,NH3,CropN,LeachN,DepositN,FixedN,Miner_N,FertilizerN,
ManureN,LitterN,dSON,
H2Otran,H2Oevap,H2Orunof,H2Oleach,H2Oirri,H2Oprec,dSoilH2O,
MeanT,CountryID 
*/

void ReadDomain(int QQ);
//void Summarizing(void);

CString ShowItem[29]={"Cropland_area", "SOC", "dSOC", "CH4", "Crop_grain_yield", "Crop_leaf_stem_biomass",
						"Crop_root_biomass", "Manure C input", "Litter C input", "N2O emission",
						"NO emission", "N2 emission", "NH3 emission", "N uptake by crop",
						"Nitrate leaching", "Atmospheric N deposition", "Biological N fixation",
						"N mineralization", "Fertilizer N application", "Manure N application",
						"dSON", "dSIN", "Transpiration", "Evaporation", "Surface runoff", 
						"Water leaching", "Irrigation water use", "Precipitation", "dSoilWater"};


//char ItemName[50][29]={"Area","SOC","dSOC","CH4","GrainC","ShootC","RootC","ManureC","LitterC",
//		"N2O","NO","N2","NH3","UptakeN","LeachN","DepositN","FixedN","Miner_N","Fert_N","ManureN",
//		"dSON","dSIN","H2Otran","H2Oevap","H2Orunof","H2Oleach","H2Oirri","H2Oprec","dSoilH2O"};

/////////////////////////////////////////////////////////////////////////////
// DNDC_Map dialog


DNDC_Map::DNDC_Map(CWnd* pParent /*=NULL*/)
	: CDialog(DNDC_Map::IDD, pParent)
{
	//{{AFX_DATA_INIT(DNDC_Map)
	m_SourceDataFormat = -1;
	m_Years = 1;
	//}}AFX_DATA_INIT
}


void DNDC_Map::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DNDC_Map)
	DDX_Control(pDX, IDC_SelectedCrop, m_SelectedCrop);
	DDX_Control(pDX, IDC_SelectCrop, m_SelectCrop);
	DDX_Control(pDX, IDC_DndcFileList, m_DndcFileList);
	DDX_Control(pDX, IDC_MapItem, m_MapItem);
	DDX_Radio(pDX, IDC_SourceDataFormat, m_SourceDataFormat);
	DDX_Text(pDX, IDC_Years, m_Years);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DNDC_Map, CDialog)
	//{{AFX_MSG_MAP(DNDC_Map)
	ON_BN_CLICKED(IDC_SelectDNDCFile, OnSelectDNDCFile)
	ON_LBN_DBLCLK(IDC_DndcFileList, OnDblclkDndcFileList)
	ON_BN_CLICKED(IDC_SelectGlobeFile, OnSelectGlobeFile)
	ON_BN_CLICKED(IDC_CountryData, OnCountryData)
	ON_BN_CLICKED(IDC_WeighIrri, OnWeighIrri)
	ON_BN_CLICKED(IDC_Draw, OnDraw)
	ON_CBN_SELCHANGE(IDC_MapItem, OnSelchangeMapItem)
	ON_BN_CLICKED(IDC_DrawGlobe, OnDrawGlobe)
	ON_CBN_SELCHANGE(IDC_SelectCrop, OnSelchangeSelectCrop)
	ON_BN_CLICKED(IDC_Intergrate, OnIntergrate)
	ON_BN_CLICKED(IDC_CountryYrAverage, OnCountryYrAverage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DNDC_Map message handlers

void DNDC_Map::OnOK() 
{
	// TODO: Add extra validation here
}



void DNDC_Map::OnSelectGlobeFile() 
{
	// TODO: Add your control notification handler code here
	int i, j;
	
	sprintf(rootdir, "%s", ROOTDIR);

	UpdateData(TRUE);

	OnDblclkDndcFileList();
	
	CString cst;
AGAIN:
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();

	SDF = m_SourceDataFormat+1;
	
	int k,num;

	//if(SDF==1) num=4;
	//else if(SDF==2||SDF==3) num=2;
	//else num=1;

	num=m_DndcFileList.GetCount();
	if (num==1) return;
	
	k=m_DndcFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		int ll=strlen(cst);

		if (cst=="") break;
	
		strcpy(GlobeFileName,cst);
		m_DndcFileList.InsertString(k,GlobeFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_DndcFileList.GetCount()==1) break;
		k++;
	}
	m_DndcFileList.SetCurSel(k);
	
	int LL=strlen(GlobeFileName);
	int N_[10] = {0,0}, O_=0, m=0;

	for(i=LL;i>=0;i--)
	{
		if(GlobeFileName[i]=='.') O_ = i;
		if(GlobeFileName[i]=='_') 
		{
			m++;
			N_[m] = i;
		}
		if(GlobeFileName[i]=='\\') break;
	}

	Glean_String(GlobeFileName, O_+1, LL, Tail);

	Glean_String(GlobeFileName, i+1, LL, ExteFileName);
	
	Glean_String(GlobeFileName, N_[1]+1, O_-1, RateName);//N_[0]-1,

	if(strcmp(RateName, "flux")!=0) 
	{
		OnDblclkDndcFileList();
		AfxMessageBox("Please select a file of flux");
		goto AGAIN;
	}
	
	Glean_String(GlobeFileName, 0, N_[1]-1, RootFileName);
	Glean_String(GlobeFileName, 0, N_[m]-1, FFileName);

	//int RLL = strlen(RootFileName);

	Glean_String(GlobeFileName, i+1, N_[m]-1, RegionName);
	Glean_String(GlobeFileName, N_[m]+1, N_[m-1]-1, IRRI);
	Glean_String(GlobeFileName, N_[2]+1, N_[1]-1, MaxMin);
	

/*	for(i=0;i<=12;i++)
	{
		if(RegionName[i]=='_') break;
	}
	
	Glean_String(RegionName, 0, i-1, domain);*/
	
	char SFF[200];
	FILE *sff;
	sprintf(SFF, "%s\\Result\\Inter\\FileReview", ROOTDIR);

	sff=fopen(SFF, "w");
	if(sff==NULL) note(1, SFF);
	
	fprintf(sff, "%s\n", GlobeFileName);
	fprintf(sff, "%s\n", RootFileName);
	fprintf(sff, "%s\n", ExteFileName);
	fprintf(sff, "%s\n", RegionName);
	fprintf(sff, "%s\n", IRRI);
	fprintf(sff, "%s\n", MaxMin);
	fprintf(sff, "%s\n", FFileName);
	fprintf(sff, "%s\n", Tail);
	fprintf(sff, "%d %d\n", SDF, m_Years);
	
	fclose(sff);	

	UpdateData(FALSE);
}

void DNDC_Map::OnSelectDNDCFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int num, k=0, CropID1=0, CropID2=0, CropID3=0;
	float MeanT, WaterStress, Nstress, Tstress;
	char SSF[5][200], TTF[5][200]; 

	ReadDomain(0);

	if(SDF==1) num=4;
	else if(SDF==2||SDF==3) num=2;
	else num=1;

	int SCD = m_SelectedCrop.GetCurSel(); //0 all, 1 rice, 2 corn, 3 wheat

	int GridID, uu, LL, CID;
	char SF[200], TF[200], cropname[150], SourceFile[300], TargetFile[300], CroppingID[50], sj[5];
	
	float ha, value;

	if(SDF==1)
	{
		sprintf(SSF[1], "%s", "_FullIrri_max_flux");
		sprintf(SSF[2], "%s", "_FullIrri_min_flux");
		sprintf(SSF[3], "%s", "_ZeroIrri_max_flux");
		sprintf(SSF[4], "%s", "_ZeroIrri_min_flux");
		sprintf(TTF[1], "%s", "_FullIrri_max_sum");
		sprintf(TTF[2], "%s", "_FullIrri_min_sum");
		sprintf(TTF[3], "%s", "_ZeroIrri_max_sum");
		sprintf(TTF[4], "%s", "_ZeroIrri_min_sum");
	}
	else if(SDF==2)
	{
		sprintf(SSF[1], "%s", "_FullIrri_ave_flux");
		sprintf(SSF[2], "%s", "_ZeroIrri_ave_flux");
		sprintf(TTF[1], "%s", "_FullIrri_ave_sum");
		sprintf(TTF[2], "%s", "_ZeroIrri_ave_sum");
	}
	else if(SDF==3)
	{
		sprintf(SSF[1], "%s", "_ZeroIrri_max_flux");
		sprintf(SSF[2], "%s", "_ZeroIrri_min_flux");
		sprintf(TTF[1], "%s", "_ZeroIrri_max_sum");
		sprintf(TTF[2], "%s", "_ZeroIrri_min_sum");
	}
	else
	{
		sprintf(SSF[1], "%s", "_ZeroIrri_ave_flux");
		sprintf(TTF[1], "%s", "_ZeroIrri_ave_sum");
	}
	
	FILE *sf, *tf;

	for(uu=1; uu<=num; uu++)
	{
		float rate[55][30]={0.0,0.0}, sum[55][30]={0.0,0.0}, TotalSum[55][30]={0.0,0.0}, TotalHa;
		int v, y, CROPID;
		char js[5];

		//sprintf(SourceFile, "%s%s.txt", FFileName, SSF[uu]);
		sprintf(SourceFile, "%s%s.csv", FFileName, SSF[uu]);
		sprintf(TargetFile, "%s%s", FFileName, TTF[uu]);

		sprintf(SF, "%s", SourceFile);
		sf=fopen(SF, "r");
		if(sf==NULL) note(0, SF);
		
		sprintf(TF, "%s", TargetFile);
		tf=fopen(TF, "w");
		if(tf==NULL) note(0, TF);
		
		for(i=1;i<=K;i++) 
		{
			//fscanf(sf, "%s", item[i]);
			fscanf(sf, "%s %s", item[i], js);
			fprintf(tf, "%15s ", item[i]);
		}
		fprintf(tf, "\n");

		for(j=1;j<=K;j++) 
		{
			//fscanf(sf, "%s", unit[j]);
			fscanf(sf, "%s %s", unit[j], js);
			fprintf(tf, "%15s ", unit[j]);
		}
		fprintf(tf, "\n");

		country_ID=0;

		//int CLCL=0;

		for(;;)
		{	
			k++;

			for(y=1; y<=TotalYear; y++)
			{
				//if(fscanf(sf, "%d", &GridID)!=1)//1
				if(fscanf(sf, "%d %s", &GridID, js)!=2)
				{
					//AfxMessageBox("!!!");
					fclose(sf);
					fclose(tf);
					goto CLCL;
				}
				else
				{
					//fscanf(sf, "%s %s %f %d", CroppingID, cropname, &ha, &year);//2-5
					fscanf(sf, "%s %s %s %s %f %s %d %s", CroppingID, js, cropname, js, &ha, js, &year, js);

					//sprintf(CroppingID, "%d", CROPID);

					for(j=6;j<=16;j++) //6-16
					{
						//fscanf(sf, "%f", &rate[j][year]);
						fscanf(sf, "%f %s", &rate[j][year], js);

						if(rate[j][year]<-1.0E6||rate[j][year]>1.0E7) rate[j][year]=0.0;

						sum[j][year] = rate[j][year] * ha;// kg C or N/ha -> kg C or N/cell
					}

					//fscanf(sf, "%d %d %d", &CropID1, &CropID2, &CropID3); //17-19
					fscanf(sf, "%d %s %d %s %d %s", &CropID1, js, &CropID2, js, &CropID3, js); //17-19

					for(j=20;j<=49;j++) //20-49
					{
						//fscanf(sf, "%f", &rate[j][year]);
						fscanf(sf, "%f %s", &rate[j][year], js);

						if(rate[j][year]<-1.0E6||rate[j][year]>1.0E7) rate[j][year]=0.0;

						if(j>=43&&j<=49) 
							sum[j][year] = rate[j][year] * ha * 10.0;//mm -> cubic m water/cell
						else 
							sum[j][year] = rate[j][year] * ha;// kg C or N/ha -> kg C or N/cell
					}

					//fscanf(sf, "%f %d %f %f %f", &MeanT, &country_ID, &WaterStress, &Nstress, &Tstress);
					fscanf(sf, "%f %s %d %s %f %s %f %s %f %s", &MeanT, js, &country_ID, js, &WaterStress, js, &Nstress, js, &Tstress, js);

					if(strcmp(country_name, old_country_name)!=0)
					{
						country_ID++;
					}
					sprintf(old_country_name, "%s", country_name);

					fprintf(tf, "%15d %15s %15s %15.0f %15d ", GridID, CroppingID, cropname, ha, year);					
					for(j=6;j<=16;j++) fprintf(tf, "%15.2f ", sum[j][year]);
					fprintf(tf, "%15d %15d %15d ", CropID1, CropID2, CropID3);
					for(j=20;j<=49;j++) fprintf(tf, "%15.2f ", sum[j][year]);
					fprintf(tf, "%15.2f %15d %15.2f %15.2f %15.2f", MeanT, country_ID, WaterStress, Nstress, Tstress);
					fprintf(tf, "\n");
				}
			}//end of year loop
		}//end of ;; loop
CLCL:;
		
	}
	

	//AfxMessageBox("Step 2 is done");
	OnIntergrate();

	return;//exit(0);
}



void DNDC_Map::OnDblclkDndcFileList() 
{
	// TODO: Add your control notification handler code here
	int num;
	
	num=m_DndcFileList.GetCount();

	if(num==0) return;

	i=m_DndcFileList.GetCurSel();
	
	CString fname;
	m_DndcFileList.GetText(i,fname);
	m_DndcFileList.DeleteString(i);	
	return;

}



void ReadDomain(int QQ)
{
	CString SFF;
	FILE *sff;
	SFF.Format("%s\\Result\\Inter\\FileReview", ROOTDIR);
	sff=fopen(SFF, "r");
	if(sff==NULL) note(0, SFF);	
	fscanf(sff, "%s", GlobeFileName);
	fscanf(sff, "%s", RootFileName);
	fscanf(sff, "%s", ExteFileName);
	fscanf(sff, "%s", RegionName);
	fscanf(sff, "%s", IRRI);
	fscanf(sff, "%s", MaxMin);
	fscanf(sff, "%s", FFileName);
	fscanf(sff, "%s", Tail);
	fscanf(sff, "%d %d", &SDF, &TotalYear);	
	if(QQ==1) fscanf(sff, "%s", IrriFile);
	fclose(sff);
}



void DNDC_Map::MapFile(int TU)
{
	// TODO: Add your control notification handler code here		
	char Country_name[250][250]={"",""};
	int GridID, year, mmm;
	char SF[200], TF[200], cropname[150], CroppingID[50];
	float ha, rate[55][30]={0.0,0.0}, sum[55][30]={0.0,0.0}, TotalSum[55][30]={0.0,0.0}, TotalHa;
	int Country_ID, Region_ID, SI, grid_ID, cell_ID;
	char Climate_file[200];	
	float N_dep, Snow, SOCmax, SOCmin, Claymax, Claymin, pHmax, pHmin, Densmax, Densmin;	
	char TargetFile[200], IndexFile[200];
	char sj[55];
	int Rr, Bb, Gg, r, c, x=0;
	float z,Fcolor, grid_item[50], lon, lat, CG, abc, cba=0.0;
	float FluxSum1[55]={0.0,0.0}, FluxSum2[55]={0.0,0.0}, FluxSum3[55]={0.0,0.0};
	int d, dd, w;	
	int cc, bb, xx, yy, y;
	int country_ID=0;
	float flux1[55], flux2[50], ColorV=0.0, old_ColorV=0.0;
	char TF1[200], TF2[200];
	static int OldCountry=0;
	FILE *tf1, *tf2, *sii, *sf, *tf;
	float flux[55]={0.0,0.0}, Ksum[250][55]={0.0,0.0}, Ksum1[250][55]={0.0,0.0}, Ksum2[250][55]={0.0,0.0};
	
/*	for(i=0;i<50;i++)
	{
		flux[50]=0.0;
		for(j=0;j<250;j++)
		{
			Ksum[250][50]=0.0;
			Ksum1[250][50]=0.0;
			Ksum2[250][50]=0.0;
		}
	}
*/
	CClientDC pDC(this);
			
		pDC.SetMapMode(MM_ANISOTROPIC);
		pDC.SetWindowExt(1500, 3900);

		CPen *pOldPen = NULL;	
		CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
		pOldPen = pDC.SelectObject(&Pen0);

		pDC.SetBkMode(TRANSPARENT);
		pDC.SetTextAlign(TA_RIGHT);
		pDC.SetTextColor(RGB(50,50,50));	

		pDC.SetViewportOrg (5, 30); 
		pDC.SetViewportExt(950, 2450);

		pDC.SetBkMode(TRANSPARENT);	

		pDC.FillSolidRect(45, 250, 2300, 1000, RGB(50,50,80));

//		CGraphexDoc* pDoc = GetDocument();
//		ASSERT_VALID(pDoc);

	
		

	UpdateData(TRUE);

	SI=m_MapItem.GetCurSel();

	//0:Area, 1:SOC, 2:dSOC, 3:CH4, 4:GrainC, 5:ShootC, 6:RootC, 7:ManureC, 8:LitterC, 9:N2O,
	//10:NO, 11:N2, 12:NH3, 13:UptakeN, 14:LeachN, 15:DepositN, 16:FixedN, 17:Miner_N, 18:Fert_N, 19:ManureN,
	//20:dSON, 21:dSIN, 22:H2Otran, 23:H2Oevap, 24:H2Orunof, 25:H2Oleach, 26:H2Oirri, 27:H2Oprec, 28:dSoilH2O 
	//1 Africa, 2 Asia, 3 Europe, 4 NorthAmerica, 5 Oceania, 6 SouthAmerica, 7 China, 8 UnitedStates, 9 India

	if(TU==2)//globe
	{
		for(int ii=1;ii<=6;ii++)
		{
			sprintf(domain, "%s", ContName[ii]);

			ReadDomain(2);
			continent=0;

			w=3;
			z=3;
			cc=3;
			bb=3;
			xx=50;
			yy=250;

			sprintf(IndexFile, "%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, domain, domain);
			sii=fopen(IndexFile, "r");
			if(sii==NULL) note(0, IndexFile);
			fgets(www, 300, sii);

			sprintf(TF1, "%s_IrriWeighed_%s.txt", FFileName, Mm[0]);
			sprintf(TF2, "%s_IrriWeighed_%s.txt", FFileName, Mm[1]);
		
			tf1=fopen(TF1, "r");
			if(tf1==NULL) note(0, TF1);
			tf2=fopen(TF2, "r");
			if(tf2==NULL) note(0, TF2);

			for(j=1;j<=41;j++) 
			{
				fscanf(tf1, "%s", item[j]);
				fscanf(tf2, "%s", item[j]);
			}

			for(j=1;j<=41;j++)
			{
				fscanf(tf1, "%s", js);
				fscanf(tf2, "%s", js);
			}
			
			country_ID=0;

			for(;;)
			{
				fscanf(tf1, "%d %f", &grid_ID1, &ha);
				fscanf(tf2, "%d %f", &grid_ID2, &ha);

			READMORE:

				if(fscanf(sii, "%d %d", &cell_ID, &Country_ID)!=2) break;	

				fscanf(sii, "%s %f %f %s %f %f %f %f %f %f %f %f %f %f %d %d %d", 
						Country_name[Country_ID], &lon, &lat, Climate_file, &N_dep, &Snow,
						&SOCmax, &SOCmin, &Claymax, &Claymin, &pHmax, &pHmin, &Densmax, &Densmin,
						&c, &r, &Region_ID);	

				if(cell_ID!=grid_ID1) 
				{
					CellColor(SI, 0.0, &Rr, &Gg, &Bb);					
					x=cc*c+xx;
					y=bb*r+yy;
					pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
					
					goto READMORE;
				}
				else
				{
					//0:Area, 1:SOC, 2:dSOC, 3:CH4, 4:GrainC, 5:ShootC, 6:RootC, 7:ManureC, 8:LitterC, 9:N2O,
					//10:NO, 11:N2, 12:NH3, 13:UptakeN, 14:LeachN, 15:DepositN, 16:FixedN, 17:Miner_N, 18:Fert_N, 19:ManureN,
					//20:dSON, 21:dSIN, 22:H2Otran, 23:H2Oevap, 24:H2Orunof, 25:H2Oleach, 26:H2Oirri, 27:H2Oprec, 28:dSoilH2O 

					for(i=1; i<=38; i++)
					{
						fscanf(tf1, "%f", &flux1[i]);
						fscanf(tf2, "%f", &flux2[i]);
						flux[i] = (flux1[i]+flux2[i])*0.5;

						FluxSum1[i]+=flux1[i];
						FluxSum2[i]+=flux2[i];
						FluxSum3[i]+=flux[i];
					}
					fscanf(tf1, "%s", country_name);
					fscanf(tf2, "%s", country_name);

					if(strcmp(country_name, old_country_name)==0)
					{
						country_ID++;
					}

					sprintf(old_country_name, "%s", country_name);

					for(i=1; i<=38; i++) 
					{
						Ksum1[country_ID][i] += flux1[i];
						Ksum2[country_ID][i] += flux2[i];
						Ksum[country_ID][i] += flux[i];
					}

					OldCountry = country_ID;

					
				}
		
				ColorV = max(flux[SI], ColorV);
				//if(flux[SI]>4000.0)	AfxMessageBox("!!!");
				CellColor(SI, flux[SI], &Rr, &Gg, &Bb);					
				x=cc*c+xx;
				y=bb*r+yy;
				pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
			
			}
			fclose(tf1);
			fclose(tf2);
			fclose(sii);
		}	
	}
	else //if(TU==0)//mapping
	{
		ReadDomain(3);

		if(strcmp(domain,"Africa")==0) continent=1;
		else if(strcmp(domain,"Asia")==0) continent=2;
		else if(strcmp(domain,"Europe")==0) continent=3;
		else if(strcmp(domain,"NorthAmerica")==0) continent=4;
		else if(strcmp(domain,"Oceania")==0) continent=5;
		else if(strcmp(domain,"SouthAmerica")==0) continent=6;
		else if(strcmp(domain,"China")==0) continent=7;
		else if(strcmp(domain,"UnitedStates")==0) continent=8;
		else if(strcmp(domain,"India")==0) continent=9;
		else
		{
			CString mess;
			mess.Format("Need to define region code for %s", domain);
			AfxMessageBox(mess);
			exit(0);
		}	
	
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
			w=5;
			z=5;
			cc=5;
			bb=5;
			xx=-900;
			yy=-200;
		}
		else if(continent==2) //Asia
		{
			w=6;
			z=6;
			cc=6;
			bb=6;
			xx=-2200;//-1400
			yy=-100;
		}
		else if(continent==3) //Europe
		{
			w=4;
			z=6;
			cc=4,
			bb=6;
			xx=-900;
			yy=220;
		}
		else if(continent==4) //N. America
		{
			w=5;
			z=6;
			cc=5,
			bb=6;
			xx=300;
			yy=200;
		}
		else if(continent==5) //Oceania
		{
			w=6;
			z=6;
			cc=6;
			bb=6;
			xx=-2700;
			yy=-600;
		}
		else if(continent==6) //S. America
		{
			w=6;
			z=6;
			cc=6;
			bb=6;
			xx=-350;
			yy=-600;
		}
		else if(continent==7) //China
		{
			w=8;
			z=10;
			cc=8;
			bb=10;
			xx=-3500;
			yy=-400;
		}
		else if(continent==8) //UnitedStates
		{
			w=8;
			z=10;
			cc=8,
			bb=10;
			xx=0;
			yy=-200;
		}
		else if(continent==9) //India
		{
			w=12;
			z=13;
			cc=12;
			bb=13;
			xx=-5000;
			yy=-1150;
		}
		else//world
		{
			w=2;
			z=2;
			cc=2;
			bb=2;
			xx=50;
			yy=250;
		}
	//}
		
	sprintf(IndexFile, "%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, domain, domain);
	sii=fopen(IndexFile, "r");
	if(sii==NULL) note(0, IndexFile);
	fgets(www, 300, sii);

	//////////////////////////////////////////
	float ha;
	int jd;

	sprintf(TF1, "%s_IrriWeighed_%s.txt", FFileName, Mm[0]);
	sprintf(TF2, "%s_IrriWeighed_%s.txt", FFileName, Mm[1]);
		
	tf1=fopen(TF1, "r");
	if(tf1==NULL) note(0, TF1);
	tf2=fopen(TF2, "r");
	if(tf2==NULL) note(0, TF2);

	for(j=1;j<=46;j++) 
	{
		fscanf(tf1, "%s", item[j]);
		fscanf(tf2, "%s", item[j]);
	}

	for(j=1;j<=46;j++)
	{
		fscanf(tf1, "%s", js);
		fscanf(tf2, "%s", js);
	}

	country_ID=0;
	
	for(;;)
	{
		fscanf(tf1, "%d %s %s", &grid_ID1, js, js);
		fscanf(tf2, "%d %s %s", &grid_ID2, js, js);

	READONCE:

		if(fscanf(sii, "%d %d", &cell_ID, &Country_ID)!=2) 
			break;	

		fscanf(sii, "%s %f %f %s %f %f %f %f %f %f %f %f %f %f %d %d %d", 
				Country_name[Country_ID], &lon, &lat, Climate_file, &N_dep, &Snow,
				&SOCmax, &SOCmin, &Claymax, &Claymin, &pHmax, &pHmin, &Densmax, &Densmin,
				&c, &r, &Region_ID);	

		if(cell_ID!=grid_ID1) 
		{
			if(TU==0||TU==1)
			{
				CellColor(SI, 0.0, &Rr, &Gg, &Bb);					
				x=cc*c+xx;
				y=bb*r+yy;
				pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
			}
			goto READONCE;
		}
		else
		{
			//0:Area, 1:SOC, 2:dSOC, 3:CH4, 4:GrainC, 5:ShootC, 6:RootC, 7:ManureC, 8:LitterC, 9:N2O,
			//10:NO, 11:N2, 12:NH3, 13:UptakeN, 14:LeachN, 15:DepositN, 16:FixedN, 17:Miner_N, 18:Fert_N, 19:ManureN,
			//20:dSON, 21:dSIN, 22:H2Otran, 23:H2Oevap, 24:H2Orunof, 25:H2Oleach, 26:H2Oirri, 27:H2Oprec, 28:dSoilH2O 

			for(i=4; i<=45; i++)
			{
				fscanf(tf1, "%f", &flux1[i]);
				fscanf(tf2, "%f", &flux2[i]);
				flux[i] = (flux1[i]+flux2[i])*0.5;
				FluxSum1[i]+=flux1[i];
				FluxSum2[i]+=flux2[i];
				FluxSum3[i]+=flux[i];
			}
			fscanf(tf1, "%s", country_name);
			fscanf(tf2, "%s", country_name);

			if(strcmp(country_name, old_country_name)==0)
			{
				country_ID++;
			}
			sprintf(old_country_name, "%s", country_name);

			for(i=4; i<=45; i++) 
			{
				Ksum1[country_ID][i] += flux1[i];
				Ksum2[country_ID][i] += flux2[i];
				Ksum[country_ID][i] += flux[i];
			}

			OldCountry = country_ID;
		
		}
		
		if(TU==0||TU==1)
		{
			ColorV = max(flux[SI], ColorV);
			CellColor(SI, flux[SI], &Rr, &Gg, &Bb);					
			x=cc*c+xx;
			y=bb*r+yy;
			pDC.FillSolidRect(x, y, w, z, RGB(Rr,Gg,Bb));
			
		}
	}

	fclose(tf1);
	fclose(tf2);
	fclose(sii);

	}

	float jf;
	CString lege;
	
	float Interval=ColorV/100000.0;
	pDC.SetTextAlign(TA_CENTER);
	pDC.SetTextColor(RGB(200,200,200));
	lege.Format("%8.1f",0.0); 	
	pDC.TextOut(150, 410, lege);
	for(i=1;i<=20;i++)	
	{
		float NewFlux=Interval*(float)powf(5.0,(float)i);
		if(NewFlux>ColorV) break;
		CellColor(SI, NewFlux, &Rr, &Gg, &Bb);
		x=100;
		y=350+ 100*i;
		
		pDC.FillSolidRect(x, y, 20, 98, RGB(Rr,Gg,Bb));		
		
		if(NewFlux<10.0)
			lege.Format("%8.1f",NewFlux); 
		else
			lege.Format("%8.0f",NewFlux);

		x=160;
		//pDC.SetTextAlign(TA_LEFT);
		pDC.TextOut(x, y+80, lege);
	}

	pDC.SetTextAlign(TA_LEFT);

	if(SI<=14) lege.Format("(ton C per 0.5X0.5 degree)"); 
	else if(SI>=15&&SI<=27) lege.Format("(ton N per 0.5X0.5 degree)");
	else lege.Format("(million cubic m water per 0.5X0.5 degree)");
	pDC.TextOut(100, y+140, lege);

	CFont hNewFont;
	TEXTMETRIC tm;
	hNewFont.DeleteObject();
	hNewFont.CreateFont(40,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
	pDC.SelectObject(&hNewFont);
	pDC.SetBkMode(TRANSPARENT);
	pDC.GetTextMetrics(&tm);
	pDC.SetTextAlign(TA_CENTER);
	pDC.SetTextColor(RGB(200, 200, 255));

	CString UUU;
	if(SI<=8) lege.Format("(Tg C)"); 
	else if(SI>=9&&SI<=21) lege.Format("(Tg N)");
	else lege.Format("(Trillion cubic m water)");
	UUU.Format("%20s: maximum %8.2f,  minimum %8.2f,  average %8.2f %s", ShowItem[SI], FluxSum1[SI]/1000000.0, FluxSum2[SI]/1000000.0, FluxSum3[SI]/1000000.0, lege);
	pDC.TextOut(1100, y+110, UUU);

	hNewFont.DeleteObject();

	if(TU==1)
	{
		CString SSF;
		SSF.Format("%s_summary.csv", FFileName);
		FILE *ssf;
		ssf = fopen(SSF, "w");
		if(ssf==NULL) note(0, SSF);

		fprintf(ssf, "%-15s, %-15s, %-15s, ", "Country_ID", "Name", "Cropland");
		//fprintf(ssf, "%15s,", item[4]);
		for(j=6;j<=45;j++) fprintf(ssf, "%-15s, %-15s, %-15s,", item[j], item[j], item[j]);
		fprintf(ssf, "\n");
		fprintf(ssf, "%-15s, %-15s, %-15s,", "Country_ID", "Name", "ha");
		for(int a=6;a<=45;a++) fprintf(ssf, "%-15s, %-15s, %-15s, ", unit[a], unit[a], unit[a]);
		fprintf(ssf, "\n");
		fprintf(ssf, ",,,");
		for(int a=6;a<=45;a++) fprintf(ssf, "%-15s, %-15s, %-15s, ", "min", "max", "average");
		fprintf(ssf, "\n");

		for(i=1; i<250; i++)
		{
			if(Ksum1[i][4]>0.0)
			{
				fprintf(ssf, "%-15d, %-15s, %15.0f, ", i, Country_name[i], Ksum1[i][4]);
				for(int a=6;a<=45;a++) 
				{
					fprintf(ssf, "%15.0f, %15.0f, %15.0f, ", Ksum1[i][a], Ksum2[i][a], Ksum[i][a]);
				}
				fprintf(ssf, "\n");	
			}
		}
		fclose(ssf);


		AfxMessageBox("done");
	}
	
exit(0);

}


void DNDC_Map::OnDraw() 
{
	MapFile(0);
}

void DNDC_Map::OnSelchangeMapItem() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	SelectedItem =m_MapItem.GetCurSel()+1; 
}

void DNDC_Map::OnDrawGlobe() 
{
	// TODO: Add your control notification handler code here
	MapFile(2);
		
}


void DNDC_Map::OnSelchangeSelectCrop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int SelectedCrop =m_SelectCrop.GetCurSel();
	char Country_name[250][250]={"",""};
	int GridID, year, CountryCode;
	char SF1[200], SF2[200], SF3[200], SF4[200], IR3[200], www[200];
	char TF[200], cropname[150], TargetFile[300], CroppingID[50];
	char SourceFile1[300],SourceFile2[300],SourceFile3[300],SourceFile4[300];
	float ha, rate[55][30]={0.0,0.0}, sum[55][30]={0.0,0.0}, TotalSum[55][30]={0.0,0.0}, TotalHa;
	CString SSF[5]={"","_FullIrri_max_rate.txt","_FullIrri_min_rate.txt","_ZeroIrri_max_rate.txt","_ZeroIrri_min_rate.txt"};
	CString TTF[5]={"","_FullIrri_max_sum.txt","_FullIrri_min_sum.txt","_ZeroIrri_max_sum.txt","_ZeroIrri_min_sum.txt"};
	CString scenario[5]={"","FullIrri_max","FullIrri_min","ZeroIrri_max","ZeroIrri_min"};
	FILE *sf1, *sf2, *sf3, *sf4, *tf, *ir3;
	GridID = 0;
	int OldID=0;
	int k=0;
	int CropNumber, crop_ID[5];
	float rate1[55], rate2[55], rate3[55], rate4[55], IrriFraction;
	float CountryHa=0.0, CountryArea[250]={0.0,0.0};
	float CountryPA[250] ={0.0,0.0}, CountryPB[250] ={0.0,0.0},CountryPC[250] ={0.0,0.0};
	float CountryProdA=0.0, CountryProdB=0.0, CountryProdC=0.0, CountryProdD=0.0;
	//char item[55][100]; 

	ReadDomain(4);

	CString SSFF;
	SSFF.Format("%s\\Result\\Record\\Region\\crop_summary_%d.csv", ROOTDIR, SelectedCrop);
	FILE *ssf;
	ssf = fopen(SSFF, "w");
	if(ssf==NULL) note(0, SSFF);	
	fprintf(ssf, "%15s, %15s, %15s, %15s, %15s, %15s, %15s, %15s\n", "Cell_ID", "Crop_ID", "Area", "IrriMax_Prod", "IrriMin_Prod", "NoIrMax_Prod", "NoIrMin_prod", "CountryID");
	fprintf(ssf, "%15s, %15s, %15s, %15s, %15s, %15s, %15s, %15s\n", "       ", "       ","ha", "kgC", "kgC", "kgC", "kgC", "kgC", "");

	sprintf(SourceFile1, "%s%s", FFileName, SSF[1]);
	sprintf(SourceFile2, "%s%s", FFileName, SSF[2]);
	sprintf(SourceFile3, "%s%s", FFileName, SSF[3]);
	sprintf(SourceFile4, "%s%s", FFileName, SSF[4]);

	sprintf(SF1, "%s", SourceFile1);
	sf1=fopen(SF1, "r");
	if(sf1==NULL) note(0, SF1);

	sprintf(SF2, "%s", SourceFile2);
	sf2=fopen(SF2, "r");
	if(sf2==NULL) note(0, SF2);

	sprintf(SF3, "%s", SourceFile3);
	sf3=fopen(SF3, "r");
	if(sf3==NULL) note(0, SF3);

	sprintf(SF4, "%s", SourceFile4);
	sf4=fopen(SF4, "r");
	if(sf4==NULL) note(0, SF4);

	for(j=1;j<=44;j++) fscanf(sf1, "%s", item[j]);
	for(j=1;j<=44;j++) fscanf(sf1, "%s", js);

	for(j=1;j<=44;j++) fscanf(sf2, "%s", item[j]);
	for(j=1;j<=44;j++) fscanf(sf2, "%s", js);

	for(j=1;j<=44;j++) fscanf(sf3, "%s", item[j]);
	for(j=1;j<=44;j++) fscanf(sf3, "%s", js);

	for(j=1;j<=44;j++) fscanf(sf4, "%s", item[j]);
	for(j=1;j<=44;j++) fscanf(sf4, "%s", js);
		
	int OldGridID = -1, WriteFlag=0;
	k=0;
	for(;;)
	{	
		k++;
		if(fscanf(sf1, "%d %s %s %f %d", &GridID, CroppingID, cropname, &ha, &year)!=5) break;
		else
		{

			if(k==1) OldGridID = GridID;
			if(GridID!=OldGridID) WriteFlag=1;
			else WriteFlag=0;

			if(WriteFlag==1&&(CountryHa>0.0)) 
			{
				
				fprintf(ssf, "%15d, %15d, ", OldGridID, SelectedCrop);
				fprintf(ssf, "%15.0f, %15.0f, %15.0f, %15.0f, %15.0f, %15d\n", CountryHa, 
				CountryProdA, CountryProdB, CountryProdC, CountryProdD, CountryCode);
				OldGridID = GridID;
				CountryHa=0.0; 
				CountryProdA=0.0;
				CountryProdB=0.0;
				CountryProdC=0.0;
				CountryProdD=0.0;
				
			}

			for(j=1;j<=38;j++) fscanf(sf1, "%f", &rate1[j]);
			fscanf(sf1, "%d", &CountryCode);
		}

		if(fscanf(sf2, "%d %s %s %f %d", &GridID, CroppingID, cropname, &ha, &year)!=5) break;
		else
		{
			for(j=1;j<=38;j++) fscanf(sf2, "%f", &rate2[j]);
			fscanf(sf2, "%d", &CountryCode);
		}

		if(fscanf(sf3, "%d %s %s %f %d", &GridID, CroppingID, cropname, &ha, &year)!=5) break;
		else
		{
			for(j=1;j<=38;j++) fscanf(sf3, "%f", &rate3[j]);
			fscanf(sf3, "%d", &CountryCode);
		}

		if(fscanf(sf4, "%d %s %s %f %d", &GridID, CroppingID, cropname, &ha, &year)!=5) break;
		else
		{
			for(j=1;j<=38;j++) fscanf(sf4, "%f", &rate4[j]);
			fscanf(sf4, "%d", &CountryCode);
		}
		
		FindCrops(CroppingID, crop_ID, &CropNumber);

		for(i=1; i<=CropNumber; i++)
		{
			if(crop_ID[i]==SelectedCrop)
			{
				CountryHa += ha;

				CountryProdA += (ha * rate1[8+i]);//irri_max
				CountryProdB += (ha * rate2[8+i]);//irri_min
				CountryProdC += (ha * rate3[8+i]);//noirri_max
				CountryProdD += (ha * rate4[8+i]);//noirri_min				
			}
		}			
	}		
	fclose(sf1);
	fclose(sf2);
	fclose(sf3);
	fclose(sf4);
	fclose(ssf);

	////////////////////////////////////////
	CString CCRR;
	FILE* ccrr;
	CCRR.Format("%s\\Result\\Record\\Region\\Continent_crop_yield.csv", ROOTDIR);

	fprintf(ccrr, "%15s, %15s, %15s, %15s, %15s, %15s, %15s\n", "Area", "Max_Prod", "Min_Prod", "Ave_Prod", "Max_yield", "Min_yield", "Ave_yield");
	fprintf(ccrr, "%15s, %15s, %15s, %15s, %15s, %15s, %15s\n", "1000_ha", "ton C", "ton C", "ton C", "kg C/ha", "kg C/ha", "kg C/ha");

	float ProdA, ProdB, ProdC, ProdD;
	ssf = fopen(SSFF, "r");
	if(ssf==NULL) note(0, SSFF);	
	fgets(www, 200, ssf);
	fgets(www, 200, ssf);

	for(;;)
	{
		if(fscanf(ssf, "%d %d %f %f %f %f %f %d", &GridID, &SelectedCrop, &ha, &ProdA, &ProdB, &ProdC, &ProdD, &CountryCode)!=8) break; 

		//////////////////////////////////////////////////
		sprintf(IR3, "%s\\Database\\Globe\\%s\\GIS\\%s_4.txt", ROOTDIR, domain, domain);
		ir3=fopen(IR3, "r");
		if(ir3==NULL) note(0, IR3);
		
		fgets(www, 100, ir3);
		fscanf(ir3, "%d %f", &grid_ID3, &IrriFraction);
		for(;;)
		{
			if(GridID==grid_ID3) break;
			else 
			{
				fscanf(ir3, "%d %f", &grid_ID3, &IrriFraction);
				IrriFraction *= 0.01;
			}
		}
		fclose(ir3);
		////////////////////////////////////////////////////
		CountryArea[CountryCode] += ha;
		CountryPA[CountryCode] += ((ProdA * IrriFraction) + (ProdC * (1.0 - IrriFraction)));
		CountryPB[CountryCode] += ((ProdB * IrriFraction) + (ProdD * (1.0 - IrriFraction)));
		CountryPC[CountryCode] = (CountryPA[CountryCode] + CountryPB[CountryCode]) * 0.5;
	}
	fclose(ssf);
	
	for(i=1; i<=250; i++)
	{
		if(CountryArea[CountryCode]>0.0)
		{
			fprintf(ccrr, "%15d, %15s, %15d, ", i, Country_name[i], SelectedCrop);
			fprintf(ccrr, "%15.0f, %15.0f, %15.0f, %15.0f, %15.0f, %15.0f\n", CountryArea[CountryCode], 
				CountryPA[CountryCode], CountryPB[CountryCode], CountryPC[CountryCode], 
				CountryPA[CountryCode]/CountryArea[CountryCode], CountryPB[CountryCode]/CountryArea[CountryCode], CountryPC[CountryCode]/CountryArea[CountryCode]);
		}
	}
	fclose(ccrr);

	
	/////////////////////////////////////////////////////

	AfxMessageBox("Done");

/*			if(k==1)
			{
				for(j=1;j<=32;j++) TotalSum[j] = 0.0;
				TotalHa = 0.0;
			}
			else
			{
				if(GridID!=OldID) 
				{
					fprintf(tf, "%10d %10.0f ", OldID, TotalHa);
					for(j=1;j<=32;j++) 
					{
						if(j<=5) fprintf(tf, "%15.0f ", TotalSum[j]);
						//if(j==7) fprintf(tf, "%15.3f ", TotalSum[j]);
						//else if(j<=12||j>=26) fprintf(tf, "%15.0f ", TotalSum[j]);
						else fprintf(tf, "%15.3f ", TotalSum[j]);
						TotalSum[j] = 0.0;
					}
					fprintf(tf, "%15d ", country_ID);
					fprintf(tf, "\n");
					
					TotalHa = 0.0;
				}
			}

			for(j=1;j<=32;j++) fscanf(sf, "%f", &rate[j]);
			fscanf(sf, "%d", &country_ID);
			
			//if(CroppingID!=105)//exclude grassland from global database
			{
				for(j=1;j<=32;j++) 
				{
					if(j>=1&&j<=5) sum[j] = rate[j] * ha * 0.001; // total SOC, kg C -> 1000 ton C
					else if(j==6) sum[j] = rate[j] * ha * 0.001; // total dSOC, kg C -> ton C
					else if(j==7) sum[j] = rate[j] * ha * 0.001;//CH4, kg C -> ton C
					else if(j>=8&&j<=12) sum[j] = rate[j] * ha * 0.001; // total C flux, kg C -> ton C
					else if(j>=13&&j<=25) sum[j] = rate[j] * ha * 0.001;// total N flux, kg N -> ton N
					else sum[j] = rate[j] * ha * 10.0 * 0.000001; //water, mm-> million cubic m
					
					TotalSum[j] += sum[j];
				}
				TotalHa += ha;	
			}

			OldID = GridID;
		}
	}
*/
	
}



void DNDC_Map::OnIntergrate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int num, CropID1, CropID2, CropID3;
	char SSF[5][200], TTF[5][200]; 
	CString B1[42]={"","Grid_ID","Area","Year","Stub","Total-SOC","ManureC","LitterC","Soil-CO2","dSOC","ha_corn","Grain_corn","ha_wheat","Grain_wheat","ha_rice", "Grain_rice","ha_others","Grain_others","ShootC","RootC","CH4","N2O","NO", "N2", "NH3","CropN","LeachN","DepositN","FixedN","Miner_N","FertilizerN","ManureN","LitterN","dSON","H2Otran","H2Oevap","H2Orunof","H2Oleach","H2Oirri","H2Oprec","dSoilH2O","CountryID"};
	CString B2[42]={"","Grid_ID","ha",  "Year","kgC",  "kgC",     "kgC",     "kgC",   "kgC",     "kgC", "ha",     "kgC",       "ha",      "kgC",        "ha",      "kgC",       "ha",       "kgC",         "kgC",   "kgC",  "kgC","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","mm","mm	","mm","mm","mm","mm","mm","CountryID"};

	ReadDomain(0);

	if(SDF==1) num=4;
	else if(SDF==2||SDF==3) num=2;
	else num=1;

	int SCD = m_SelectedCrop.GetCurSel(); //0 all, 1 rice, 2 corn, 3 wheat

	int GridID, uu, LL, CID;
	char SF[200], TF[200], cropname[150], SourceFile[300], TargetFile[300], CroppingID[55], sj[5];
	
	float ha, value, jf[60], grain1, grain2, grain3, ha1, ha2, ha3, ha4;

	if(SDF==1)
	{
		sprintf(SSF[1], "%s", "_FullIrri_max_sum");
		sprintf(SSF[2], "%s", "_FullIrri_min_sum");
		sprintf(SSF[3], "%s", "_ZeroIrri_max_sum");
		sprintf(SSF[4], "%s", "_ZeroIrri_min_sum");
		sprintf(TTF[1], "%s", "_FullIrri_max_total");
		sprintf(TTF[2], "%s", "_FullIrri_min_total");
		sprintf(TTF[3], "%s", "_ZeroIrri_max_total");
		sprintf(TTF[4], "%s", "_ZeroIrri_min_total");
	}
	else if(SDF==2)
	{
		sprintf(SSF[1], "%s", "_FullIrri_ave_sum");
		sprintf(SSF[2], "%s", "_ZeroIrri_ave_sum");
		sprintf(TTF[1], "%s", "_FullIrri_ave_total");
		sprintf(TTF[2], "%s", "_ZeroIrri_ave_total");
	}
	else if(SDF==3)
	{
		sprintf(SSF[1], "%s", "_ZeroIrri_max_sum");
		sprintf(SSF[2], "%s", "_ZeroIrri_min_sum");
		sprintf(TTF[1], "%s", "_ZeroIrri_max_total");
		sprintf(TTF[2], "%s", "_ZeroIrri_min_total");
	}
	else
	{
		sprintf(SSF[1], "%s", "_ZeroIrri_ave_sum");
		sprintf(TTF[1], "%s", "_ZeroIrri_ave_total");
	}
	
	FILE *sf, *tf;

	for(uu=1; uu<=num; uu++)
	{
		float rate[55][30]={0.0,0.0}, TotalSum[55][30]={0.0,0.0}, TotalHa;//sum[55][30]={0.0,0.0}, TotalSum[55][30]={0.0,0.0}, 
		int v;

		sprintf(SourceFile, "%s%s", FFileName, SSF[uu]);
		sprintf(TargetFile, "%s%s", FFileName, TTF[uu]);

		sprintf(SF, "%s", SourceFile);
		sf=fopen(SF, "r");
		if(sf==NULL) note(0, SF);
		
		sprintf(TF, "%s", TargetFile);
		tf=fopen(TF, "w");
		if(tf==NULL) note(0, TF);
		
		for(j=1;j<=K;j++) fscanf(sf, "%s", item[j]);
		for(j=1;j<=K;j++) fscanf(sf, "%s", js);
			//
		for(j=1;j<=41;j++) fprintf(tf, "%15s ", B1[j]);
		fprintf(tf, "\n");
		for(j=1;j<=41;j++) fprintf(tf, "%15s ", B2[j]);
		fprintf(tf, "\n");

		GridID = 0;
		int OldID=0, k=0, y=0, OldYr=0;
		float MeanT, WaterStress, Nstress, Tstress;

		for(j=0;j<=K;j++) 
		{
			for(v=0;v<30; v++) TotalSum[j][v] = 0.0;
		}

		TotalHa = 0.0;

		ha1=0.0;
		ha2=0.0;
		ha3=0.0;
		ha4=0.0;
		
		for(;;)
		{	
			k++;

			float sum[55][30]={0.0,0.0};//, TotalSum[55][30]={0.0,0.0}, 

			if(fscanf(sf, "%d", &GridID)!=1)
			{
if(GridID==41388)
GridID=GridID;
				for(y=1;y<=TotalYear;y++)
				{
					fprintf(tf, "%15d %15.0f %15d ", OldID, TotalHa, y);//CroppingID, cropname,
					for(j=4;j<=9;j++) 
						{
							fprintf(tf, "%15.0f ", TotalSum[j][y]);
							TotalSum[j][y] = 0.0;
						}

						/*for(j=10;j<=13;j++) //grains
						{
							fprintf(tf, "%15.0f ", TotalSum[j][y]);
							TotalSum[j][y] = 0.0;
						}*/

					fprintf(tf, "%15.0f %15.0f ", ha1, TotalSum[10][y]);
							TotalSum[10][y] = 0.0;
							fprintf(tf, "%15.0f %15.0f ", ha2, TotalSum[11][y]);
							TotalSum[11][y] = 0.0;
							fprintf(tf, "%15.0f %15.0f ", ha3, TotalSum[12][y]);
							TotalSum[12][y] = 0.0;
							fprintf(tf, "%15.0f %15.0f ", ha4, TotalSum[13][y]);
							TotalSum[13][y] = 0.0;

					if(y==TotalYear)
					{
						ha1=0.0;
						ha2=0.0;
						ha3=0.0;
						ha4=0.0;
					}

						for(j=14;j<=36;j++) 
						{
							fprintf(tf, "%15.0f ", TotalSum[j][y]);
							TotalSum[j][y] = 0.0;
						}

						fprintf(tf, "%15d ", country_ID);
						fprintf(tf, "\n");
				}				
				
				fclose(sf);
				fclose(tf);
				break;
			}
			else
			{
if(GridID==41388)
GridID=GridID;
				if(k==1) OldID = GridID;

				if(GridID!=OldID) 
				{
					for(y=1;y<=TotalYear;y++)
					{
						fprintf(tf, "%15d %15.0f %15d ", OldID, TotalHa, y);
						for(j=4;j<=9;j++) 
						{
							fprintf(tf, "%15.0f ", TotalSum[j][y]);
							TotalSum[j][y] = 0.0;
						}

						//for(j=10;j<=13;j++) //grains
						//{
							fprintf(tf, "%15.0f %15.0f ", ha1, TotalSum[10][y]);
							TotalSum[10][y] = 0.0;
							fprintf(tf, "%15.0f %15.0f ", ha2, TotalSum[11][y]);
							TotalSum[11][y] = 0.0;
							fprintf(tf, "%15.0f %15.0f ", ha3, TotalSum[12][y]);
							TotalSum[12][y] = 0.0;
							fprintf(tf, "%15.0f %15.0f ", ha4, TotalSum[13][y]);
							TotalSum[13][y] = 0.0;
						//}
						if(y==TotalYear)
						{
							ha1=0.0;
							ha2=0.0;
							ha3=0.0;
							ha4=0.0;
						}

						for(j=14;j<=36;j++) 
						{
							fprintf(tf, "%15.0f ", TotalSum[j][y]);
							TotalSum[j][y] = 0.0;
						}

						fprintf(tf, "%15d ", country_ID);
						fprintf(tf, "\n");
					}					
					TotalHa = 0.0;
					for(j=6;j<=K-5;j++) 
					{
						for(int v=0;v<30; v++) TotalSum[j][v] = 0.0;
					}
				}

				OldID = GridID;
				
				fscanf(sf, "%s %s %f %d", CroppingID, cropname, &ha, &year);//2-5
				
				fscanf(sf, "%f", &sum[4][year]);
				
				for(j=1;j<=5;j++) fscanf(sf, "%f", &jf[0]);//discarded
				
				for(j=5;j<=9;j++) fscanf(sf, "%f", &sum[j][year]);

				fscanf(sf, "%d %d %d", &CropID1, &CropID2, &CropID3);
				fscanf(sf, "%f %f %f", &grain1, &grain2, &grain3);

				for(j=23;j<=25;j++) fscanf(sf, "%f", &jf[j]);
				sum[14][year] = jf[23] + jf[24] + jf[25];//shoot

				for(j=26;j<=28;j++) fscanf(sf, "%f", &jf[j]);
				sum[15][year] = jf[26] + jf[27] + jf[28];//shoot

				if(CropID1==1) 
				{
					sum[10][year] += grain1; //corn grain
					if(year==1) ha1 += ha;
				}
				else if(CropID1==2||CropID1==6) 
				{
					sum[11][year] += grain1;//winter wheat + spring wheat
					if(year==1) ha2 += ha;
				}
				else if(CropID1==20||CropID1==46||CropID1==30||CropID1==24) 
				{
					sum[12][year] += grain1;//irrigated rice+rainfed rice + deepwater rice + upland rice
					if(year==1) ha3 += ha;
				}
				else 
				{
					if(jf[23]>0.0)
					{
					sum[13][year] += grain1;//other crops
					if(year==1) ha4 += ha;
					}
				}

				if(CropID2==1) 
				{
					sum[10][year] += grain2; //corn grain
					if(year==1) ha1 += ha;
				}
				else if(CropID2==2||CropID2==6) 
				{
					sum[11][year] += grain2;//winter wheat + spring wheat
					if(year==1) ha2 += ha;
				}
				else if(CropID2==20||CropID2==46||CropID2==30||CropID2==24) 
				{
					sum[12][year] += grain2;//irrigated rice+rainfed rice + deepwater rice + upland rice
					if(year==1) ha3 += ha;
				}
				else 
				{
					if(jf[24]>0.0)
					{
					sum[13][year] += grain2;//other crops
					if(year==1) ha4 += ha;
					}
				}

				if(CropID3==1) 
				{
					sum[10][year] += grain3; //corn grain
					if(year==1) ha1 += ha;
				}
				else if(CropID3==2||CropID3==6) 
				{
					sum[11][year] += grain3;//winter wheat + spring wheat
					if(year==1) ha2 += ha;
				}
				else if(CropID3==20||CropID3==46||CropID3==30||CropID3==24) 
				{
					sum[12][year] += grain3;//irrigated rice+rainfed rice + deepwater rice + upland rice
					if(year==1) ha3 += ha;
				}
				else 
				{
					if(jf[25]>0.0)
					{
					sum[13][year] += grain3;//other crops
					if(year==1) ha4 += ha;
					}
				}
								
				for(j=16;j<=36;j++) fscanf(sf, "%f", &sum[j][year]);
				
				fscanf(sf, "%f %d %f %f %f", &jf[0], &country_ID, &jf[0], &jf[0], &jf[0]);

				int YN;
				//YN = FindOneCrop(CroppingID, SCD);
				//if(YN==1)//selected crop-rotated cropping systems
				{
						for(j=4;j<=9;j++) 
							TotalSum[j][year] += sum[j][year];

						for(j=10;j<=13;j++) 
							TotalSum[j][year] += sum[j][year];
						
						for(j=14;j<=36;j++) 
							TotalSum[j][year] += sum[j][year];
											
						if(year==1) TotalHa += ha;
						TotalYear = max(TotalYear, year);				
				}

			}
		}
	}
	//AfxMessageBox("Step 3 is done");
	OnCountryData();

	//exit(0);

}

void DNDC_Map::OnWeighIrri() 
{
	// TODO: Add your control notification handler code here
	SelectIrriFile ww;
	if(ww.DoModal()==IDOK)
	{
		
	};

	char SFF[200], SSF[5][200], TTF[5][200];
	FILE *sff;
	sprintf(SFF, "%s\\Result\\Inter\\IrriFileReview", ROOTDIR);

	sff=fopen(SFF, "r");
	if(sff==NULL) note(0, SFF);
	
	fscanf(sff, "%s", IrriFile);	
	fclose(sff);

	int num;
	//char item[52][100]; 

	ReadDomain(0);

	if(SDF==1) num=2;
	else if(SDF==2) num=1;
	else num=0;

	//int SCD = m_SelectedCrop.GetCurSel(); //0 all, 1 rice, 2 corn, 3 wheat

	int GridID, uu, LL, CID;
	char SF[200], cropname[150], SourceFile[300], TargetFile[300], CroppingID[55], sj[5];
	
	float ha, value;

	if(SDF==1)
	{
		sprintf(SSF[1], "%s", "_FullIrri_max_total");
		sprintf(SSF[2], "%s", "_ZeroIrri_max_total");
		sprintf(SSF[3], "%s", "_FullIrri_min_total");
		sprintf(SSF[4], "%s", "_ZeroIrri_min_total");
		sprintf(TTF[1], "%s", "_IrriWeighed_max_total");
		sprintf(TTF[2], "%s", "_IrriWeighed_min_total");
	}
	else if(SDF==2)
	{
		sprintf(SSF[1], "%s", "_FullIrri_ave_total");
		sprintf(SSF[2], "%s", "_ZeroIrri_ave_total");
		sprintf(TTF[1], "%s", "_IrriWeighed_ave_total");
	}
	else 
	{
		//AfxMessageBox("No necessary to calculate irrigation-weighed results as only no-irrigation scenarios were simulated");
		//exit(0);
	}


	CString SF1, SF2, TF;
	char SF3[200];
	FILE *sf1, *sf2, *sf3, *tf;
	float jf, IrriFraction, flux1[55][30], flux2[55][30], flux3[55][30], MeanT;
	int jd, OldGrid=0;
	
	for(int zi=1;zi<=num;zi++)
	{
		int wq1, wq2, wq3;

		if(zi==1) 
		{
			wq1=1; wq2=2; wq3=1;
		}

		if(zi==2) 
		{
			wq1=3; wq2=4; wq3=2;
		}

		SF1.Format("%s%s", FFileName, SSF[wq1]);
		sf1=fopen(SF1, "r");
		if(sf1==NULL) note(0, SF1);

		int wq = (zi+1)*2;
		SF2.Format("%s%s", FFileName, SSF[wq2]);
		sf2=fopen(SF2, "r");
		if(sf2==NULL) note(0, SF2);
		
		sprintf(SF3, "%s", IrriFile);
		sf3=fopen(SF3, "r");
		if(sf3==NULL) note(0, SF3);
		
		TF.Format("%s%s", FFileName, TTF[wq3]);
		
		tf=fopen(TF, "w");
		if(tf==NULL) note(1, TF);

		for(j=1;j<=K;j++) 
		{
			fscanf(sf1, "%s", item[j]);
			fscanf(sf2, "%s", item[j]);
			if(j==K-1) fprintf(tf, "%15s ", "IrriFraction");
			else if(j==K) fprintf(tf, "%15s ", "None");
			else fprintf(tf, "%15s ", item[j]);
		}
		fprintf(tf, "\n");

		for(j=1;j<=K;j++)
		{
			fscanf(sf1, "%s", js);
			fscanf(sf2, "%s", js);
			if(j==K-1) fprintf(tf, "%15s ", "IrriFraction");
			else fprintf(tf, "%15s ", js);
		}
		fprintf(tf, "\n");

		fgets(www, 300, sf3);
		fgets(www, 300, sf3);
		fgets(www, 300, sf3);

		//int irri_crs, irri_crID[50]={0,0};
		//fscanf(sf3, "%d", &irri_crs);
		//for(i=1;i<=irri_crs;i++) fscanf(sf3, "%s", js;
		//for(i=1;i<=irri_crs;i++) fscanf(sf3, "%d", &irri_crID[i];
		
		
		for(;;)
		{
			if(fscanf(sf1, "%d %s %s %f %d", &grid_ID1, CroppingID, cropname, &ha, &year)!=5) 
			{
				fclose(sf1);
				fclose(sf2);
				fclose(sf3);
				fclose(tf);
				break;
			}
	
			fscanf(sf2, "%d %s %s %f %d", &grid_ID2, CroppingID, cropname, &ha, &year);
			if(grid_ID1!=grid_ID2)
			{
				CString mess;
				mess.Format("Grind cell %d ID numbers are inconsistent between %s and %s", grid_ID1, SF1, SF2);
				AfxMessageBox(mess);
				exit(0);
			}
NewOne:;			
			if(OldGrid!=grid_ID1&&year==1) 
				fscanf(sf3, "%d %f", &grid_ID3, &IrriFraction);	
			
			if(grid_ID1!=grid_ID3)
			{
				CString mess;
				mess.Format("Grind cell %d ID numbers are inconsistent between %s and %s", grid_ID1, SF1, SF3);
				//AfxMessageBox(mess);
				goto NewOne;
			}

			OldGrid = grid_ID1; 

			if(IrriFraction<0.0) IrriFraction = 0.0;
			//else IrriFraction *= 0.01;

			fprintf(tf, "%15d %15s %15s %15.0f %15d ", OldGrid, CroppingID, cropname, ha, year);

			float IrriHa = IrriFraction*0.01 * ha;

			for(i=6; i<=K-5; i++) 
			{
				fscanf(sf1, "%f", &flux1[i][year]);
				fscanf(sf2, "%f", &flux2[i][year]);
				
				if(i==K-6) flux3[i][year] = flux1[i][year];//precipitation
				else flux3[i][year] = flux1[i][year] * IrriFraction*0.01 + flux2[i][year] * (1.0 - IrriFraction*0.01);

				fprintf(tf, "%10.0f ", flux3[i][year]);
			}
			fscanf(sf1, "%f %d %s %f %f", &MeanT, &country_ID, country_name, &jf, &jf);
			fscanf(sf2, "%f %d %s %f %f", &MeanT, &country_ID, country_name, &jf, &jf);
			fprintf(tf, "%15.1f %15d %15s %15.2f %15.2f ", MeanT, country_ID, country_name, IrriFraction*0.01, IrriHa);
			fprintf(tf, "\n");

			
		}

		/*fclose(sf1);
		fclose(sf2);
		fclose(sf3);
		fclose(tf);*/
	}

	AfxMessageBox("Done");
}

void DNDC_Map::OnCountryData() 
{
	// TODO: Add your control notification handler code here
	Summarizing();
	exit(0);
	//MapFile(1);
}

void DNDC_Map::Summarizing(void)
{
	//UpdateData(TRUE);

	ReadDomain(0);

	//int SCD = m_SelectedCrop.GetCurSel(); //0 all, 1 rice, 2 corn, 3 wheat
	CString B1[42]={"","Grid_ID","Area","Year","Stub","Total-SOC","ManureC","LitterC","Soil-CO2","dSOC","ha_corn","Grain_corn","ha_wheat","Grain_wheat","ha_rice", "Grain_rice","ha_others","Grain_others","ShootC","RootC","CH4","N2O","NO", "N2", "NH3","CropN","LeachN","DepositN","FixedN","Miner_N","FertilizerN","ManureN","LitterN","dSON","H2Otran","H2Oevap","H2Orunof","H2Oleach","H2Oirri","H2Oprec","dSoilH2O","CountryID"};
	CString B2[42]={"","Grid_ID","ha",  "Year","kgC",  "kgC",     "kgC",     "kgC",   "kgC",     "kgC", "ha",     "kgC",       "ha",      "kgC",        "ha",      "kgC",       "ha",       "kgC",         "kgC",   "kgC",  "kgC","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","kgN","mm","mm	","mm","mm","mm","mm","mm","CountryID"};

	int GridID, uu, LL, CID, num, yr, w, old_country_ID, CropNumber, crop_ID[90];
	char SSF[7][200], TTF[7][200], js[200], CropCode[200], CropName[200]; 
	float ha, value, jf, GlobeSumHa=0.0;
	float ttt[55]={0.0,0.0};
	int OldGrid=0, jd, CNUM, Cs, Cid;
	FILE *tf1, *tf2, *GC;

	float RegionSumTTT[41][23][241]={0.0,0.0}, RegionSumHa[241]={0.0,0.0};
	float GlobeSum[41][23]={0.0,0.0};

	CString CCCname[250]={"",""};
	char GlobeCountry[250];

	sprintf(GlobeCountry, "%s\\Library\\Lib_globe\\CountryID.txt", ROOTDIR);
	GC=fopen(GlobeCountry, "r");
	if(GC==NULL) note(0, GlobeCountry);
	fscanf(GC, "%d %s %s", &CNUM, js, js);
	for(i=1; i<=CNUM; i++)
	{
		fscanf(GC, "%d %d %s", &Cs, &Cid, js);
		CCCname[Cid].Format("%s", js);
	}
	fclose(GC);


	if(SDF==1)
	{
		sprintf(SSF[1], "%s%s", FFileName, "_FullIrri_max_total");
		sprintf(SSF[2], "%s%s", FFileName, "_ZeroIrri_max_total");
		sprintf(SSF[3], "%s%s", FFileName, "_FullIrri_min_total");
		sprintf(SSF[4], "%s%s", FFileName, "_ZeroIrri_min_total");
		//sprintf(SSF[5], "%s%s", FFileName, "_IrriWeighed_max_total");
		//sprintf(SSF[6], "%s%s", FFileName, "_IrriWeighed_min_total");

		sprintf(TTF[1], "%s%s", FFileName, "_FullIrri_max_region");
		sprintf(TTF[2], "%s%s", FFileName, "_ZeroIrri_max_region");
		sprintf(TTF[3], "%s%s", FFileName, "_FullIrri_min_region");
		sprintf(TTF[4], "%s%s", FFileName, "_ZeroIrri_min_region");
		//sprintf(TTF[5], "%s%s", FFileName, "_IrriWeighed_max_region");
		//sprintf(TTF[6], "%s%s", FFileName, "_IrriWeighed_min_region");

		num=4;
	}
	else if(SDF==2)
	{
		sprintf(SSF[1], "%s%s", FFileName, "_FullIrri_ave_total");
		sprintf(SSF[2], "%s%s", FFileName, "_ZeroIrri_ave_total");
		//sprintf(SSF[3], "%s%s", FFileName, "_IrriWeighed_ave_total");
		sprintf(TTF[1], "%s%s", FFileName, "_FullIrri_ave_region");
		sprintf(TTF[2], "%s%s", FFileName, "_ZeroIrri_ave_region");
		//sprintf(TTF[3], "%s%s", FFileName, "_IrriWeighed_ave_region");
		num=2;
	}
	else if(SDF==3)
	{
		sprintf(SSF[1], "%s%s", FFileName, "_ZeroIrri_max_total");
		sprintf(SSF[2], "%s%s", FFileName, "_ZeroIrri_min_total");
		//sprintf(SSF[3], "%s%s", FFileName, "_IrriWeighed_ave_total");
		sprintf(TTF[1], "%s%s", FFileName, "_ZeroIrri_max_region");
		sprintf(TTF[2], "%s%s", FFileName, "_ZeroIrri_min_region");
		//sprintf(TTF[3], "%s%s", FFileName, "_IrriWeighed_ave_region");
		num=2;
	}
	else
	{
		sprintf(SSF[1], "%s%s", FFileName, "_ZeroIrri_ave_total");
		//sprintf(SSF[2], "%s%s", FFileName, "_IrriWeighed_ave_total");
		sprintf(TTF[1], "%s%s", FFileName, "_ZeroIrri_ave_region");
		//sprintf(TTF[2], "%s%s", FFileName, "_IrriWeighed_ave_region");
		num=1;
	}

	
	for(i=1; i<=num; i++)
	{
		int x,y,z;
		
		for(z=0;z<=240; z++)
		{
			RegionSumHa[z]=0.0;

			for(y=0; y<=22; y++)
			{
				for(x=0; x<=40; x++) RegionSumTTT[x][y][z]=0.0;
			}
		}			

		GlobeSumHa = 0.0;
		for(y=0; y<=22; y++)
		{
			for(x=0; x<=40; x++) GlobeSum[x][y] = 0.0;
		}		

		tf1=fopen(SSF[i], "r");
		if(tf1==NULL) note(0, SSF[i]);
		tf2=fopen(TTF[i], "w");
		if(tf2==NULL) note(1, TTF[i]);

		for(j=1;j<=41;j++) fscanf(tf1, "%s", item[j]);
		for(j=1;j<=41;j++) fscanf(tf1, "%s", item[j]);			
				
		for(j=1;j<=41;j++) fprintf(tf2, "%15s ", B1[j]);
		fprintf(tf2, "\n");
		for(j=1;j<=41;j++) fprintf(tf2, "%15s ", B2[j]);
		fprintf(tf2, "\n");

		/*CString VVV[40]={"", "RegionID","year","ha","SOC","ManureC","LitterC","CO2","dSOC","ha-corn","grain-corn","ha-wheat","grain-wheat","ha-rice","grain-rice","ha-others","grain-others","shoot","root","CH4",  "N2O",  "NO",  "N2", "NH3","CropN","LeachN","DepositN","FixedN","Miner_N","FertilizerN","ManureN","LitterN","dSON","H2Otran","H2Oevap","H2Orunof","H2Oleach","H2Oirri","H2Oprec","dSoilWater"};
		for(w=1; w<=39; w++) fprintf(tf2, "%15s ", VVV[w]);
		fprintf(tf2, "\n");
		CString UUU[40]={"", "RegionID","year","ha","kg_C","kg_C",    "kg_C", "kg_C","kg_C","ha",     "kg_C",      "ha",      "kg_C",       "ha",     "kg_C",      "ha",       "kg_C",        "kg_C", "kg_C","kg_C","kg_N","kg_N","kg_N","kg_N","kg_N",  "kg_N",  "kg_N",    "kg_N",   "kg_N",   "kg_N",      "kg_N",  "kg_N",    "kg_N", "m3",     "m3",      "m3",     "m3",      "m3",     "m3","m3"};
		for(w=1; w<=39; w++) fprintf(tf2, "%15s ", UUU[w]);
		fprintf(tf2, "\n");*/

			
		int CCC=0, q=0;
		for(;;)
		{
			if(fscanf(tf1, "%d %f %d", &grid_ID1, &ha, &yr)!=3) 
			{
				for(CCC=1; CCC<=240; CCC++)
				{
					if(RegionSumHa[CCC]>0.0)//CCC==country_ID) 
					{
						for(int y=1; y<=TotalYear; y++)
						{
							fprintf(tf2, "%10d %15f %5d ", CCC, RegionSumHa[CCC],  y);

							for(w=1; w<=37; w++)
							{								
								fprintf(tf2, "%15.0f ", RegionSumTTT[w][y][CCC]); 
							}

							fprintf(tf2, "%15s ", CCCname[CCC]);
							
							fprintf(tf2, "\n"); 
						}
					}
				}	
				
				for(int y=1; y<=TotalYear; y++)
				{
					fprintf(tf2, "%10d %15f %5d ", 1000, GlobeSumHa,  y);

					for(w=1; w<=37; w++)
					{								
						fprintf(tf2, "%15.0f ", GlobeSum[w][y]); 
					}

					fprintf(tf2, "%15s ", "Globe");
						
					fprintf(tf2, "\n"); 
				}

				
				fclose(tf1);
				fclose(tf2);
				break;
			}
			else
			{
				for(w=1; w<=37; w++) 
				{
					fscanf(tf1, "%f", &ttt[w]);			
				}

				fscanf(tf1, "%d", &country_ID); //for globe
			
				if(yr==1)
				{
					RegionSumHa[country_ID] += ha;
					GlobeSumHa += ha;
				}
				
				for(w=1; w<=37; w++)
				{
					RegionSumTTT[w][yr][country_ID] += ttt[w];	
					GlobeSum[w][yr] += ttt[w];
				}
			}
		}


	}
///////////////////////////////////////////////////////////////////////////////////////					
/*	sprintf(TF1, "%s_IrriWeighed_%s", FFileName, Mm[0]);
	sprintf(TF2, "%s_IrriWeighed_%s", FFileName, Mm[1]);
		
	

	for(j=1;j<=K-3;j++) 
	{
		fscanf(tf1, "%s", item[j]);
		fscanf(tf2, "%s", item[j]);
	}

	for(j=1;j<=K-3;j++)
	{
		fscanf(tf1, "%s", unit[j]);
		fscanf(tf2, "%s", unit[j]);
	}
		
	country_ID=0;

	for(;;)
	{
		if(fscanf(tf1, "%d %d %d %f %d", &grid_ID1, &jd, &jd, &ha, &year)!=5) 
			break;
		fscanf(tf2, "%d %d %d %f %d", &grid_ID2, &jd, &jd, &ha, &year);

		TotalYear = max(TotalYear, year);

		for(i=6; i<=K-5; i++)
		{
			fscanf(tf1, "%f", &ttmax[i][year]);
			fscanf(tf2, "%f", &ttmin[i][year]);
		}
		fscanf(tf1, "%f %s", &temp[year], country_name);
		fscanf(tf2, "%f %s", &temp[year], country_name);

		if(strcmp(country_name, old_country_name)==0)
					{
						country_ID++;
					}
		sprintf(old_country_name, "%s", country_name);

		if(year==1) TotalHa[country_ID] += ha;

		for(i=6; i<=K-5; i++)
		{
			RegionSumMax[i][year][country_ID] += ttmax[i][year];
			RegionSumMin[i][year][country_ID] += ttmin[i][year];
		}
	}	

	fclose(tf1);
	fclose(tf2);

/*	CString CropSys[4]={"all", "rice", "corn", "wheat"};

	CString SSF;
	SSF.Format("%s_summary_%s.txt", FFileName, CropSys[SCD]);
	FILE *ssf;
	ssf = fopen(SSF, "w");
	if(ssf==NULL) note(1, SSF);

	fprintf(ssf, "%15s %15s %15s ", "County_code", "Country_name", "Range");
	for(j=4;j<=K-5;j++) 
	{
		fprintf(ssf, "%15s ", item[j]);
	}
	fprintf(ssf, "\n");

	fprintf(ssf, "%15s %15s %15s ", "County_code", "Country_name", "Range");
	for(j=4;j<=K-5;j++)
	{
		fprintf(ssf, "%15s ", unit[j]);
	}
	fprintf(ssf, "\n");

	char CCname[251][50]={"None","None"};
	int CCC;
	CString CID;
	FILE *cid;
	CID.Format("%s\\Database\\Globe\\Global_country_ID_system.txt", ROOTDIR);
	cid = fopen(CID, "r");
	if(cid==NULL) note(0, CID);
	for(int p=1; p<=220; p++)
	{
		fscanf(cid, "%d", &CCC);
		fscanf(cid, "%s", CCname[CCC]);
	}

for(int w=1; w<=250; w++)
{
	if(TotalHa[w]>0.0)
	{
		for(y=1; y<=TotalYear; y++)
		{
			fprintf(ssf, "%15d %15s %15s %15.0f %15d ", w, CCname[w], "Minimum", TotalHa[w], y);
			for(j=6;j<=K-5;j++)
			{
				fprintf(ssf, "%15.0f ", RegionSumMax[j][y][w]);
			}
			
			fprintf(ssf, "\n");

			fprintf(ssf, "%15d %15s %15s %15.0f %15d ", w, CCname[w], "Maximum", TotalHa[w], y);
			for(j=6;j<=K-5;j++)
			{
				fprintf(ssf, "%15.0f ", RegionSumMin[j][y][w]);
			}
			
			fprintf(ssf, "\n");
		}
	}
}
	fclose(ssf);
*/
	AfxMessageBox("Step 4 is done");

	//exit(0);

}

void DNDC_Map::OnCountryYrAverage() 
{
	// TODO: Add your control notification handler code here
	ReadDomain(0);

	int IDD, uu, LL, num, yr, y, w, CNUM, jd, i, Cs, Cid;
	char GlobeCountry[250], js[100], SSF[7][200], TTF[7][200], AAF[7][200], BBF[7][200];	
	float ha, value, jf, AveYYY, AveHHH;
	//char item[55][100]; 

	CString CCCname[250]={"",""};
	FILE *tf1, *tf2, *tf3, *tf4, *GC;

	sprintf(GlobeCountry, "%s\\Library\\Lib_globe\\CountryID.txt", ROOTDIR);
	GC=fopen(GlobeCountry, "r");
	if(GC==NULL) note(0, GlobeCountry);
	fscanf(GC, "%d %s %s", &CNUM, js, js);
	for(i=1; i<=CNUM; i++)
	{
		fscanf(GC, "%d %d %s", &Cs, &Cid, js);
		CCCname[Cid].Format("%s", js);
	}
	fclose(GC);


	if(SDF==1)
	{
		sprintf(SSF[1], "%s%s", FFileName, "_FullIrri_max_region");
		sprintf(SSF[2], "%s%s", FFileName, "_ZeroIrri_max_region");
		sprintf(SSF[3], "%s%s", FFileName, "_FullIrri_min_region");
		sprintf(SSF[4], "%s%s", FFileName, "_ZeroIrri_min_region");
		sprintf(SSF[5], "%s%s", FFileName, "_IrriWeighed_max_region");
		sprintf(SSF[6], "%s%s", FFileName, "_IrriWeighed_min_region");
		
		sprintf(TTF[1], "%s%s", FFileName, "_FullIrri_max_region_YrAve");
		sprintf(TTF[2], "%s%s", FFileName, "_ZeroIrri_max_region_YrAve");
		sprintf(TTF[3], "%s%s", FFileName, "_FullIrri_min_region_YrAve");
		sprintf(TTF[4], "%s%s", FFileName, "_ZeroIrri_min_region_YrAve");
		sprintf(TTF[5], "%s%s", FFileName, "_IrriWeighed_max_region_YrAve");
		sprintf(TTF[6], "%s%s", FFileName, "_IrriWeighed_min_region_YrAve");
		
		sprintf(AAF[1], "%s%s", FFileName, "_FullIrri_max_region_YrAve_HaAve");
		sprintf(AAF[2], "%s%s", FFileName, "_ZeroIrri_max_region_YrAve_HaAve");
		sprintf(AAF[3], "%s%s", FFileName, "_FullIrri_min_region_YrAve_HaAve");
		sprintf(AAF[4], "%s%s", FFileName, "_ZeroIrri_min_region_YrAve_HaAve");
		sprintf(AAF[5], "%s%s", FFileName, "_IrriWeighed_max_region_YrAve_HaAve");
		sprintf(AAF[6], "%s%s", FFileName, "_IrriWeighed_min_region_YrAve_HaAve");
		
		sprintf(BBF[1], "%s%s", FFileName, "_FullIrri_max_region_HaAve");
		sprintf(BBF[2], "%s%s", FFileName, "_ZeroIrri_max_region_HaAve");
		sprintf(BBF[3], "%s%s", FFileName, "_FullIrri_min_region_HaAve");
		sprintf(BBF[4], "%s%s", FFileName, "_ZeroIrri_min_region_HaAve");
		sprintf(BBF[5], "%s%s", FFileName, "_IrriWeighed_max_region_HaAve");
		sprintf(BBF[6], "%s%s", FFileName, "_IrriWeighed_min_region_HaAve");

		num=6;
	}
	else if(SDF==2)
	{
		sprintf(SSF[1], "%s%s", FFileName, "_FullIrri_ave_region");
		sprintf(SSF[2], "%s%s", FFileName, "_ZeroIrri_ave_region");
		sprintf(SSF[3], "%s%s", FFileName, "_IrriWeighed_ave_region");

		sprintf(TTF[1], "%s%s", FFileName, "_FullIrri_ave_region_YrAve");
		sprintf(TTF[2], "%s%s", FFileName, "_ZeroIrri_ave_region_YrAve");
		sprintf(TTF[3], "%s%s", FFileName, "_IrriWeighed_ave_region_YrAve");

		sprintf(AAF[1], "%s%s", FFileName, "_FullIrri_ave_region_YrAve_HaAve");
		sprintf(AAF[2], "%s%s", FFileName, "_ZeroIrri_ave_region_YrAve_HaAve");
		sprintf(AAF[3], "%s%s", FFileName, "_IrriWeighed_ave_region_YrAve_HaAve");

		sprintf(BBF[1], "%s%s", FFileName, "_FullIrri_ave_region_HaAve");
		sprintf(BBF[2], "%s%s", FFileName, "_ZeroIrri_ave_region_HaAve");
		sprintf(BBF[3], "%s%s", FFileName, "_IrriWeighed_ave_region_HaAve");

		num=3;
	}
	else if(SDF==3)
	{
		sprintf(SSF[1], "%s%s", FFileName, "_ZeroIrri_max_region");
		sprintf(SSF[2], "%s%s", FFileName, "_ZeroIrri_min_region");
		sprintf(SSF[3], "%s%s", FFileName, "_IrriWeighed_max_region");
		sprintf(SSF[4], "%s%s", FFileName, "_IrriWeighed_min_region");

		sprintf(TTF[1], "%s%s", FFileName, "_ZeroIrri_max_region_YrAve");
		sprintf(TTF[2], "%s%s", FFileName, "_ZeroIrri_min_region_YrAve");
		sprintf(TTF[3], "%s%s", FFileName, "_IrriWeighed_max_region_YrAve");
		sprintf(TTF[4], "%s%s", FFileName, "_IrriWeighed_min_region_YrAve");

		sprintf(AAF[1], "%s%s", FFileName, "_ZeroIrri_max_region_YrAve_HaAve");
		sprintf(AAF[2], "%s%s", FFileName, "_ZeroIrri_min_region_YrAve_HaAve");
		sprintf(AAF[3], "%s%s", FFileName, "_IrriWeighed_max_region_YrAve_HaAve");
		sprintf(AAF[4], "%s%s", FFileName, "_IrriWeighed_min_region_YrAve_HaAve");

		sprintf(BBF[1], "%s%s", FFileName, "_ZeroIrri_max_region_HaAve");
		sprintf(BBF[2], "%s%s", FFileName, "_ZeroIrri_min_region_HaAve");
		sprintf(BBF[3], "%s%s", FFileName, "_IrriWeighed_max_region_HaAve");
		sprintf(BBF[4], "%s%s", FFileName, "_IrriWeighed_min_region_HaAve");

		num=4;
	}
	else
	{
		sprintf(SSF[1], "%s%s", FFileName, "_ZeroIrri_ave_region");
		//sprintf(SSF[2], "%s%s", FFileName, "_IrriWeighed_ave_region");

		//sprintf(TTF[1], "%s%s", FFileName, "_ZeroIrri_ave_region_YrAve");
		//sprintf(TTF[2], "%s%s", FFileName, "_IrriWeighed_ave_region_YrAve");

		//sprintf(AAF[1], "%s%s", FFileName, "_ZeroIrri_ave_region_YrAve_HaAve");
		//sprintf(AAF[2], "%s%s", FFileName, "_IrriWeighed_ave_region_YrAve_HaAve");

		sprintf(BBF[1], "%s%s", FFileName, "_ZeroIrri_ave_region_HaAve");

		num=1;
	}

	for(i=1; i<=num; i++)
	{
		tf1=fopen(SSF[i], "r");
		if(tf1==NULL) note(0, SSF[i]);
		//tf2=fopen(TTF[i], "w");
		//if(tf2==NULL) note(1, TTF[i]);
		//tf3=fopen(AAF[i], "w");
		//if(tf3==NULL) note(1, AAF[i]);
		tf4=fopen(BBF[i], "w");
		if(tf4==NULL) note(1, BBF[i]);
		
		for(j=1;j<=37;j++) 
		{
			fscanf(tf1, "%s", item[j]);
			//fprintf(tf2, "%15s ", item[j]);
			//fprintf(tf3, "%15s ", item[j]);
			fprintf(tf4, "%15s ", item[j]);
		}
		//fprintf(tf2, "\n");
		//fprintf(tf3, "\n");
		fprintf(tf4, "\n");

		for(j=1;j<=37;j++) 
		{
			fscanf(tf1, "%s", item[j]);
			//fprintf(tf2, "%15s ", item[j]);
			//fprintf(tf3, "%15s ", item[j]);
			fprintf(tf4, "%15s ", item[j]);
		}
		//fprintf(tf2, "\n");
		//fprintf(tf3, "\n");
		fprintf(tf4, "\n");

		int CCC=0, q=0;
		for(;;)
		{
			float ttt[52]={0.0,0.0}, yyy[52]={0.0,0.0}, www[52]={0.0,0.0}; 
			for(y=1; y<=TotalYear; y++)
			{
				if(fscanf(tf1, "%d %d %f", &IDD , &yr, &ha)!=3)
				{
					fclose(tf1);
					//fclose(tf2);
					//fclose(tf3);
					fclose(tf4);
					goto HWH;
				}
				else
				{
					sprintf(js, CCCname[IDD]);
					fprintf(tf4, "%15d %15d %15s ", IDD, yr, js);

					for(w=4; w<=8; w++) 	
					{
						fscanf(tf1, "%f", &ttt[w]);	
						yyy[w] += ttt[w];
						www[w] = ttt[w]/ha;

						fprintf(tf4, "%15.2f ", www[w]);
					}
					
					for(w=9; w<=16; w++) 	
					{
						float hha = 0.0;
						fscanf(tf1, "%f", &ttt[w]);	
						if(w==9||w==11||w==13||w==15) 
						{
							hha = ttt[w];
							yyy[w] += ttt[w];
							www[w] = ttt[w];
							fprintf(tf4, "%15.2f ", www[w]);
						}							
						else 
						{
							yyy[w] += ttt[w];
							www[w] = ttt[w]/ha;
							fprintf(tf4, "%15.2f ", www[w]);
						}
					}

					for(w=17; w<=37; w++) 	
					{
						fscanf(tf1, "%f", &ttt[w]);	
						yyy[w] += ttt[w];
						www[w] = ttt[w]/ha;

						fprintf(tf4, "%15.2f ", www[w]);
					}
					fprintf(tf4, "\n");
				}


			}

			sprintf(js, CCCname[IDD]);
			//fprintf(tf2, "%15d %15s %15.0f ", IDD, js, ha);
			//fprintf(tf3, "%15d %15s %15.0f ", IDD, js, ha);
			for(w=1; w<=37; w++) 
			{
				AveYYY = yyy[w] / TotalYear;
				AveHHH = AveYYY / ha;

				//fprintf(tf2, "%15.0f ", AveYYY);
				//fprintf(tf3, "%15.2f ", AveHHH);
			}
			//fprintf(tf2, "\n");
			//fprintf(tf3, "\n");
		}
HWH:;
	}

	AfxMessageBox("Done");
	exit(0);
}
			
