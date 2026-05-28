// SitePage8.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage8.h"
#include "SitePSheet.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CropArray			Crop;
extern Site_BaseInformation	IData ;
extern StringArray			ClimateFilename;
//extern RotationArray		rotation;
//extern Cycle_a_year		cycle;
//extern TillArray			till;
//extern FerArray			fer;
//extern ManureArray			manure;
//extern WeedArray			weed;
//extern FloodArray			flood;
//extern IrrigationArray		irrigation;
//extern GrazingArray         grazing;
//extern NowCropPractices		NowC;
//extern CropProperty CropPty;
//extern float NanuCN[4];
extern CropofEachYear CYr[2];
//extern int   MaxCycle;
//extern char  Workdir[255];
extern char *soiltexture[];
extern char *soillanduse[];
CString FCT8;

float CoverFraction[251]={1.0,1.0};
/////////////////////////////////////////////////////////////////////////////
// SitePage8 property page

IMPLEMENT_DYNCREATE(SitePage8, CPropertyPage)

SitePage8::SitePage8() : CPropertyPage(SitePage8::IDD)
{
	//{{AFX_DATA_INIT(SitePage8)
	m_WeedOption = -1;//ventilation
	m_WeedDay = 0;
	m_WeedID = 0;
	m_WeedMonth = 0;
	m_WeedN = 0;
	m_WeedMonth2 = 0;
	m_WeedDay2 = 0;
	m_CoverFraction = 1.0f;




	//}}AFX_DATA_INIT
}

SitePage8::~SitePage8()
{
}

void SitePage8::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage8)

	DDX_Control(pDX, IDC_LIST2, m_WeedList);
	DDX_Radio(pDX, IDC_WeedOption0, m_WeedOption);
	DDX_Text(pDX, IDC_WeedDay, m_WeedDay);
	DDX_Text(pDX, IDC_WeedID, m_WeedID);
	DDX_Text(pDX, IDC_WeedMonth, m_WeedMonth);
	DDX_Text(pDX, IDC_WeedN, m_WeedN);
	DDX_Text(pDX, IDC_WeedMonth2, m_WeedMonth2);
	DDX_Text(pDX, IDC_WeedDay2, m_WeedDay2);
	DDX_Text(pDX, IDC_CoverFraction, m_CoverFraction);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage8, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage8)
	ON_BN_CLICKED(IDC_WedLast, OnWedLast)
	ON_BN_CLICKED(IDC_WedNext, OnWedNext)
	ON_BN_CLICKED(IDC_WedAccept, OnWedAccept)
	ON_BN_CLICKED(IDC_WeedOption0, OnWeedOption0)
	ON_BN_CLICKED(IDC_WeedOption1, OnWeedOption1)
	ON_BN_CLICKED(IDC_WeedOption2, OnWeedOption2)
	ON_EN_KILLFOCUS(IDC_WeedMonth, OnKillfocusWeedMonth)
	ON_EN_KILLFOCUS(IDC_WeedDay, OnKillfocusWeedDay)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage8 message handlers

BOOL SitePage8::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
#ifdef MANURE
	int TotalManureCrops, CropIDID, ManureCropOrder;
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d %d", &TotalManureCrops, &ManureCropOrder, &CropIDID);
	fclose(xff);
	FCT8.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	FCT8.Format("%s_1", INTERMANAGE);
#endif

	int rrr, yyy, i;
	for(i=1; i<=250; i++)
	{
		WeedID[i]=0;
		WeedMonth1[i]=0;
		WeedDay1[i]=0;
		WeedMonth2[i]=0;
		WeedDay2[i]=0;
		CoverFraction[i]=1.0;
	}

	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);

	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	DB.Format("%s\\CropPlastic_%d_%d.txt", FCT8, rrr, yyy);
		db=fopen(DB, "r");
		fscanf(db, "%d %d", &m_WeedN, &m_WeedOption);

	if(m_WeedN==0)
	{
		for(i=1; i<=20; i++)
		{
			WeedID[i] = i;
			WeedMonth1[i]=0;
			WeedDay1[i]=0;
			WeedMonth2[i]=0;
			WeedDay2[i]=0;
			CoverFraction[i]=1.0;
		}
	}
	else
	{
		for(i=1; i<=m_WeedN; i++)
		{
			WeedID[i] = i;
			fscanf(db, "%d %d", &WeedMonth1[i], &WeedDay1[i]);
			fscanf(db, "%d %d", &WeedMonth2[i], &WeedDay2[i]);
			fscanf(db, "%f", &CoverFraction[i]);
		}		
	}
	fclose(db);
		
	i=1;
	m_WeedID = WeedID[i];
	m_WeedMonth = WeedMonth1[i];
	m_WeedDay = WeedDay1[i];
	m_WeedMonth2 = WeedMonth2[i];
	m_WeedDay2 = WeedDay2[i];
	m_CoverFraction = CoverFraction[i];

	demo();

	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

BEGIN_EVENTSINK_MAP(SitePage8, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage8)
	//ON_EVENT(SitePage8, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void SitePage8::OnWedLast() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_WeedID;		
	WeedMonth1[i]=m_WeedMonth;
	WeedDay1[i]=m_WeedDay;
	WeedMonth2[i]=m_WeedMonth2;
	WeedDay2[i]=m_WeedDay2;
	CoverFraction[i]=m_CoverFraction;

	if (m_WeedN==0) return;
	if (m_WeedID>1) m_WeedID--;
	else if (m_WeedID==0) m_WeedID=1;

	i=m_WeedID;		
	m_WeedMonth=WeedMonth1[i];
	m_WeedDay=WeedDay1[i];
	m_WeedMonth2=WeedMonth2[i];
	m_WeedDay2=WeedDay2[i];
	m_CoverFraction = CoverFraction[i];

	UpdateData(FALSE);
		
}

void SitePage8::OnWedNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_WeedID;		
	WeedMonth1[i]=m_WeedMonth;
	WeedDay1[i]=m_WeedDay;
	WeedMonth2[i]=m_WeedMonth2;
	WeedDay2[i]=m_WeedDay2;
	CoverFraction[i]=m_CoverFraction;
		
	if (m_WeedN==0) return;
	if (m_WeedID<m_WeedN) m_WeedID++;
	else if (m_WeedID==0) m_WeedID=1;

	i=m_WeedID;		
	m_WeedMonth=WeedMonth1[i];
	m_WeedDay=WeedDay1[i];
	m_WeedMonth2=WeedMonth2[i];
	m_WeedDay2=WeedDay2[i];
	m_CoverFraction = CoverFraction[i];

	UpdateData(FALSE);	
}

void SitePage8::OnWedAccept() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;

	i=m_WeedID;		
	WeedMonth1[i]=m_WeedMonth;
	WeedDay1[i]=m_WeedDay;
	WeedMonth2[i]=m_WeedMonth2;
	WeedDay2[i]=m_WeedDay2;
	CoverFraction[i]=m_CoverFraction;




	int rrr, yyy;
		CString DB;
		FILE *db;
		DB.Format("%s\\Inter\\CR.txt", OUTPUT);
		//DB.Format("%s\\CR.txt", FCT8);
		db=fopen(DB, "r");
		fscanf(db, "%d %d", &rrr, &yyy);
		fclose(db);	

	DB.Format("%s\\CropPlastic_%d_%d.txt", FCT8, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(db, "%d %d\n", m_WeedN, m_WeedOption);
	for (i = 1; i<=m_WeedN;i++) 
	{
		fprintf(db, "%d %d\n", WeedMonth1[i], WeedDay1[i]);
		fprintf(db, "%d %d\n", WeedMonth2[i], WeedDay2[i]);
		fprintf(db, "%f\n", CoverFraction[i]);
	}
	fclose(db);

	demo();	
}


void SitePage8::OnWeedOption0() 
{
	// TODO: Add your control notification handler code here
		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT8);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);
	WeedOption = m_WeedOption;	
}

void SitePage8::OnWeedOption1() 
{
	// TODO: Add your control notification handler code here
		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT8);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);
	WeedOption = m_WeedOption;	
}

void SitePage8::OnWeedOption2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_WeedN = 0;
	m_WeedID = 0;		
	m_WeedMonth=0;
	m_WeedDay=0;
	m_WeedMonth2=0;
	m_WeedDay2=0;
	m_CoverFraction = 0.0;
	WeedOption = m_WeedOption;

	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT8);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(FALSE);	
}

void SitePage8::OnKillfocusWeedMonth() 
{
	UpdateData(TRUE);	
}

void SitePage8::OnKillfocusWeedDay() 
{
	UpdateData(TRUE);	
}

BOOL SitePage8::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
		//Set Tillage parameter list
		//Set list column
	int i;
	char *title[]={"ID","Month","Day","Month","Day","Fraction"};
	int  ItemNum=6;
	for (i=0;i<ItemNum;i++)
	{
		m_WeedList.InsertColumn(i,title[i],LVCFMT_CENTER,65,-1);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE


}

void SitePage8::demo()
{
	m_WeedList.DeleteAllItems();
	CString txt;
    if (m_WeedN >= 0) 
	{
		if (m_WeedN==0) 
		{
			txt = OrderNumber(1,"plastic",&txt);
			m_WeedList.InsertItem(0,txt);

			txt.Format("%d",0);
			m_WeedList.SetItemText(0,1,txt);

			txt.Format("%d",0);
			m_WeedList.SetItemText(0,2,txt);

			txt.Format("%d",0);
			m_WeedList.SetItemText(0,3,txt);

			txt.Format("%d",0);
			m_WeedList.SetItemText(0,4,txt);

			txt.Format("%f",0.0);
			m_WeedList.SetItemText(0,5,txt);
		}
		else
		{
		for (int i = 1; i<=m_WeedN;i++) 
		{
			txt = OrderNumber(i,"plastic",&txt);
			m_WeedList.InsertItem(i-1,txt);

			txt.Format("%d",WeedMonth1[i]);
			m_WeedList.SetItemText(i-1,1,txt);

			txt.Format("%d",WeedDay1[i]);
			m_WeedList.SetItemText(i-1,2,txt);

			txt.Format("%d",WeedMonth2[i]);
			m_WeedList.SetItemText(i-1,3,txt);

			txt.Format("%d",WeedDay2[i]);
			m_WeedList.SetItemText(i-1,4,txt);

			txt.Format("%f",CoverFraction[i]);
			m_WeedList.SetItemText(i-1,5,txt);
		}
		}
	}


	
}

