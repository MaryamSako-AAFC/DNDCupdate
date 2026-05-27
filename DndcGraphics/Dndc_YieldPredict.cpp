// Dndc_YieldPredict.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "Dndc_YieldPredict.h"
#include "SitePara.h"
#include "dndc_main.h"
#include <io.h>
#include <direct.h>
#include "dndc_tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dndc_YieldPredict dialog


Dndc_YieldPredict::Dndc_YieldPredict(CWnd* pParent /*=NULL*/)
	: CDialog(Dndc_YieldPredict::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dndc_YieldPredict)
	m_YieldLocation = -1;
	m_YieldYear = 2004;
	m_YieldToday = 0;
	m_YieldMonth = 0;
	m_database = -1;
	//}}AFX_DATA_INIT
}


void Dndc_YieldPredict::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dndc_YieldPredict)
	DDX_Control(pDX, IDC_YieldCrop, m_Croplist);
	DDX_Control(pDX, IDC_GridList, m_GridList);
	DDX_CBIndex(pDX, IDC_LOCATION, m_YieldLocation);
	DDX_Text(pDX, IDC_YieldYear, m_YieldYear);
	DDX_Text(pDX, IDC_YieldToday, m_YieldToday);
	DDX_Text(pDX, IDC_YieldMonth, m_YieldMonth);
	DDX_Radio(pDX, IDC_database, m_database);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dndc_YieldPredict, CDialog)
	//{{AFX_MSG_MAP(Dndc_YieldPredict)
	ON_BN_CLICKED(IDC_database, Ondatabase)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dndc_YieldPredict message handlers

void Dndc_YieldPredict::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int Jday;
	Jday = JulianDay(m_YieldMonth, m_YieldToday);

	int site = m_YieldLocation;

	char fname[200], str[200], RegionName[200], RootName[300], Root1[300],Root2[300], WholeName[400];
	int i, GridNum, id, SI = m_GridList.GetCurSel();
	FILE *fp;

	CString Fregion;
	FILE *region;
	Fregion.Format("%s\\PassName", INTER);
	region = fopen(Fregion, "r");
	if (region==NULL) note(0, Fregion);
	fscanf(region, "%d %d", &i, &i);
	fscanf(region, "%s", RegionName);
	fscanf(region, "%s %s", Root1, Root2);
	fscanf(region, "%s", RootName);
	fscanf(region, "%s", WholeName);
	fclose (region);
	
	sprintf(fname,"%s\\China_GridList.txt", RootName);
	
	fp=fopen(fname,"r");
	if (fp==NULL) 
	{	
		CString NNOO;
		NNOO.Format("Cannot open %s", fname);
		AfxMessageBox(NNOO);
		exit;
	}
	fscanf(fp,"%d",&GridNum);
	char str2[50];
	for (i=0;i<GridNum;i++)
	{
		if (fscanf(fp,"%d %s %s",&id, str,str2)!=3) break;
		if(i==SI) break;
	}
	fclose(fp);

	int YieldCrop = m_Croplist.GetCurSel()+1;
	
	CString YF;
	FILE* yf;
	YF.Format("%s\\YieldPrediction", INTER);
	yf=fopen(YF, "w");
	if(yf==NULL) note(1,YF);

	fprintf(yf, "%d  %d  %d  %d  %s  %d  %d\n", id, YieldCrop, m_YieldYear, Jday, str, m_YieldMonth, m_YieldToday);

	fprintf(yf, "%s %s\n",CropSystemName[YieldCrop], CropSystemID[YieldCrop]);
	
	fclose(yf);
	
	CDialog::OnOK();
}

BOOL Dndc_YieldPredict::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);

	int m_StartYear;

	CString CYW;
	FILE* cyw;
	CYW.Format("%s\\TargetYr", INTER);
	cyw=fopen(CYW, "r");
	if(cyw==NULL) note(0, CYW);
	fscanf(cyw, "%d", &m_StartYear);
	fclose(cyw);

	m_YieldYear = m_StartYear+1;

	UpdateData(FALSE);

	SetGridList(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void Dndc_YieldPredict::Ondatabase() 
{
	// TODO: Add your control notification handler code here
	SetGridList(0);
}

void Dndc_YieldPredict::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	SetGridList(1);
}

BOOL Dndc_YieldPredict::SetGridList(int DataType)
{
	UpdateData(TRUE);

	int i,id,GridNum,Si=m_GridList.GetCurSel();
	FILE *fp;
	char fname[256],str[256], RegionName[200], RootName[300], Root1[300], Root2[300],WholeName[400];

	//Chen Han
	FILE *fc;
	char fcroplist[256],KK[256],js[50];

	CString Fregion;
	FILE *region;
	Fregion.Format("%s\\PassName", INTER);
	region = fopen(Fregion, "r");
	if (region==NULL) note(0, Fregion);
	fscanf(region, "%d %d", &i, &i);
	fscanf(region, "%s", RegionName);
	fscanf(region, "%s %s", Root1, Root2);
	fscanf(region, "%s", RootName);
	fscanf(region, "%s", WholeName);
	fclose (region);
	
	sprintf(fname,"%s\\China_GridList.txt", RootName);

	char str2[50];

	fp=fopen(fname,"r");
	if (fp==NULL) 
	{	
		CString NNOO;
		NNOO.Format("Cannot open %s", fname);
		AfxMessageBox(NNOO);
		return FALSE;
	}

	m_GridList.ResetContent();
	fscanf(fp,"%d",&GridNum);
	if (GridNum<=0) return FALSE;
	for (i=0;i<GridNum;i++)
	{
		if (fscanf(fp,"%d %s %s",&id, str,str2)!=3) break;
		//if (fgets(str,250,fp)==NULL) break;
		//EraseFBSpace(str);
		sprintf(fname,"%d_%s_%s",id,str, str2);
		m_GridList.AddString(fname);
	}
	fclose(fp);

	///////////
	sprintf(fcroplist,"%s\\China_CropArea.txt", RootName);
	
	fc=fopen(fcroplist,"r");
	if (fc==NULL) 
	{	
		CString NNOO;
		NNOO.Format("Cannot open %s", fname);
		AfxMessageBox(NNOO);
		return FALSE;
	}
	
	m_Croplist.ResetContent();
	
	fgets(KK, 500, fc);//crop area
	fscanf(fc, "%d", &CropSystemNumber0);
	if (CropSystemNumber0<=0) return FALSE;
	for(i=1; i<=CropSystemNumber0; i++) fscanf(fc, "%s", 
		
		CropSystemName[i]);	
	fscanf(fc, "%s", js);
	for(i=1; i<=CropSystemNumber0; i++) fscanf(fc, "%s", 
		
		CropSystemID[i]);
	
	for (i=0;i<CropSystemNumber0;i++)
	{
		
		//if (fgets(str,250,fp)==NULL) break;
		//EraseFBSpace(str);
		sprintf(fcroplist,"%s_%s",CropSystemID
			
			[i+1],CropSystemName[i+1]);
		m_Croplist.AddString(fcroplist);
	}
	fclose(fc);
	///////////

	if (Si>=0) m_GridList.SetCurSel(Si);

	UpdateData(FALSE);
	return 0;
}


