// SitePage6.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "RunPaths.h"
#include "SitePara.h"
#include "SitePage6.h"
#include "SitePSheet.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern ForestArray          forest;
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

CString FCT6;
/////////////////////////////////////////////////////////////////////////////
// SitePage6 property page

IMPLEMENT_DYNCREATE(SitePage6, CPropertyPage)

SitePage6::SitePage6() : CPropertyPage(SitePage6::IDD)
{
	//{{AFX_DATA_INIT(SitePage6)
	m_FerMethod = 0;
	m_FerAbi = 0.0f;
	m_FerAnh = 0.0f;
	m_FerDay = 0;
	m_FerDepth = 0.0f;
	m_FerID = 1;
	m_FerMonth = 0;
	m_FerN = 0;
	m_FerNH42HPO4 = 0.0f;
	m_FerNH42SO4 = 0.0f;
	m_FerNH4NO3 = 0.0f;
	m_FerNitrate = 0.0f;
	m_FerUrea = 0.0f;
	m_FertEvent = TRUE;
	m_DayRelease = 1.0f;
	m_ReleaseControl = -1;
	m_NIefficiency = 0.0f;
	m_NIduration = 0.0f;
	m_NitrificationInhibitor = -1;
	m_FertOption = 0;
	m_UreaseEfficiency = 0.0f;
	m_UreaseDuration = 0.0f;
	m_UreaseInhibitor = -1;
	m_unit = -1;
	//}}AFX_DATA_INIT
}

SitePage6::~SitePage6()
{

}

void SitePage6::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage6)
	DDX_Control(pDX, IDC_FGFileList, m_FGFileList);
	DDX_Control(pDX, IDC_LIST1, m_FerList);
	DDX_Radio(pDX, IDC_RADIO1, m_FerMethod);
	DDX_Text(pDX, IDC_FerAbi, m_FerAbi);
	DDX_Text(pDX, IDC_FerAnh, m_FerAnh);
	DDX_Text(pDX, IDC_FerDay, m_FerDay);
	DDX_Text(pDX, IDC_FerDepth, m_FerDepth);
	DDX_Text(pDX, IDC_FerID, m_FerID);
	DDX_Text(pDX, IDC_FerMonth, m_FerMonth);
	DDX_Text(pDX, IDC_FerN, m_FerN);
	DDX_Text(pDX, IDC_FerNH42HPO4, m_FerNH42HPO4);
	DDX_Text(pDX, IDC_FerNH42SO4, m_FerNH42SO4);
	DDX_Text(pDX, IDC_FerNH4NO3, m_FerNH4NO3);
	DDX_Text(pDX, IDC_FerNitrate, m_FerNitrate);
	DDX_Text(pDX, IDC_FerUrea, m_FerUrea);
	DDX_Check(pDX, IDC_FertEvent, m_FertEvent);
	DDX_Text(pDX, IDC_DayRelease, m_DayRelease);
	DDX_Radio(pDX, IDC_ReleaseControl, m_ReleaseControl);
	DDX_Text(pDX, IDC_NIefficiency, m_NIefficiency);
	DDX_Text(pDX, IDC_NIduration, m_NIduration);
	DDX_Radio(pDX, IDC_NitrificationInhibitor, m_NitrificationInhibitor);
	DDX_Radio(pDX, IDC_FertMethod1, m_FertOption);
	DDX_Text(pDX, IDC_UreaseEfficiency, m_UreaseEfficiency);
	DDX_Text(pDX, IDC_UreaseDuration, m_UreaseDuration);
	DDX_Radio(pDX, IDC_UreaseInhibitor, m_UreaseInhibitor);
	DDX_Radio(pDX, IDC_unit, m_unit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage6, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage6)
	ON_BN_CLICKED(IDC_FerAccept, OnFerAccept)
	ON_BN_CLICKED(IDC_FerLast, OnFerLast)
	ON_BN_CLICKED(IDC_FerNext, OnFerNext)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_EN_KILLFOCUS(IDC_FerMonth, OnKillfocusFerMonth)
	ON_EN_KILLFOCUS(IDC_FerDay, OnKillfocusFerDay)
	ON_EN_KILLFOCUS(IDC_FerDepth, OnKillfocusFerDepth)
	ON_EN_KILLFOCUS(IDC_FerNitrate, OnKillfocusFerNitrate)
	ON_EN_KILLFOCUS(IDC_FerNH42HPO4, OnKillfocusFerNH42HPO4)
	ON_EN_KILLFOCUS(IDC_FerNH42SO4, OnKillfocusFerNH42SO4)
	ON_EN_KILLFOCUS(IDC_FerNH4NO3, OnKillfocusFerNH4NO3)
	ON_EN_KILLFOCUS(IDC_FerUrea, OnKillfocusFerUrea)
	ON_EN_KILLFOCUS(IDC_FerAbi, OnKillfocusFerAbi)
	ON_EN_KILLFOCUS(IDC_FerAnh, OnKillfocusFerAnh)
	ON_BN_CLICKED(IDC_SelectFertigationFile, OnSelectFertigationFile)
	ON_BN_CLICKED(IDC_FertEvent, OnFertEvent)
	ON_BN_CLICKED(IDC_ReleaseControl, OnReleaseControl)
	ON_BN_CLICKED(IDC_NitrificationInhibitor, OnNitrificationInhibitor)
	ON_BN_CLICKED(IDC_FertMethod2, OnFertMethod2)
	ON_BN_CLICKED(IDC_FertMethod1, OnFertMethod1)
	ON_BN_CLICKED(IDC_FertMethod3, OnFertMethod3)
	ON_LBN_DBLCLK(IDC_FGFileList, OnDblclkFGFileList)
	ON_BN_CLICKED(IDC_UreaseInhibitor, OnUreaseInhibitor)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	ON_BN_CLICKED(IDC_FertMethod4, OnFertMethod4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage6 message handlers

BOOL SitePage6::OnSetActive() 
{
	// Fertilization setup
	CString DB;
	FILE *db;	
	DB.Format("%s\\Inter\\UnitSystem", OUTPUT);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &m_unit);
	fclose(db);

#ifdef MANURE
	int TotalManureCrops, CropIDID, ManureCropOrder;
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d %d", &TotalManureCrops, &ManureCropOrder, &CropIDID);
	fclose(xff);
	FCT6.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	FCT6.Format("%s_1", INTERMANAGE);
#endif

	int rrr, yyy, i;

	for(i=0; i<=290; i++)
	{
		FertID[i]=1; FertMonth[i]=0; FertDay[i]=0; FertMethod[i]=0;
		FertNitrate[i]=0.0; FertAbi[i]=0.0; FertUrea[i]=0.0; FertAnh[i]=0.0; FertAmNi[i]=0.0; NH42SO4[i]=0.0; 
		NH42HPO4[i]=0.0; FertDepth[i]=0.2;
		DayRelease[i]=1.0; NIefficiency[i]=0.0; NIduration[i]=0.0; FertOption=0;
		UreaseEfficiency[i]=0.0; UreaseDuration[i]=0.0;
	}

	
	m_DayRelease = 1.0;

	CString DBB;
	FILE *dbb;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT6);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropFert_%d_%d.txt", FCT6, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &FertOption);//m_FerN);

	if(FertOption==-1)//fertigation
	{
		m_FertOption = 2;

		fscanf(db, "%s", FertigationYear);
		fscanf(db, "%f %f %f %f %f", &DayRelease[0], &NIefficiency[0], &NIduration[0],
				&UreaseEfficiency[0], &UreaseDuration[0]);

		m_DayRelease = DayRelease[0];
		m_NIefficiency = NIefficiency[0];
		m_NIduration = NIduration[0];
		m_UreaseEfficiency = UreaseEfficiency[0];
		m_UreaseDuration = UreaseDuration[0];

		m_FertEvent = 0;
		m_FGFileList.ResetContent ();		
		m_FGFileList.InsertString(0,FertigationYear);		 	
		
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(TRUE); 	

		DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d", 1);
		fclose(db);

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(FALSE); 
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIefficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIduration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseEfficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseDuration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(FALSE); 

		m_FerList.DeleteAllItems();	
	}
	else if(FertOption==-2)//Auto-fertilization
	{
		m_FertOption = 1;
		m_FerN = 2;
		m_FerID = 1;


		int jd = 0;

		//m_FertOption = 1;
		//m_FerN = FertOption;

		for (i = 1; i <= 2; i++)
		{
			FertID[i] = i;
			fscanf(db, "%d %d %d", &FertMonth[i], &FertDay[i], &FertMethod[i]);
			fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[i], &FertAbi[i], &FertUrea[i], &FertAnh[i], &FertAmNi[i],
				&NH42SO4[i], &NH42HPO4[i], &FertDepth[i]);
			fscanf(db, "%f %f %f %f %f", &DayRelease[i], &NIefficiency[i], &NIduration[i],
				&UreaseEfficiency[i], &UreaseDuration[i]);

			if (DayRelease[i] < 1.0) DayRelease[i] = 1.0;
		}
		fscanf(db, "%d", &jd);

		fclose(db);

		if (FertOption != 0) FertOption = 0;

		i = 1;
		m_FerID = FertID[i];
		m_FerMonth = FertMonth[i];
		m_FerDay = FertDay[i];
		m_FerMethod = FertMethod[i];
		m_FerNitrate = FertNitrate[i];
		m_FerAbi = FertAbi[i];
		m_FerUrea = FertUrea[i];
		m_FerAnh = FertAnh[i];
		m_FerNH4NO3 = FertAmNi[i];
		m_FerNH42SO4 = NH42SO4[i];
		m_FerNH42HPO4 = NH42HPO4[i];
		m_FerDepth = FertDepth[i];
		m_DayRelease = DayRelease[i];
		m_FertOption = 1;
		m_NIefficiency = NIefficiency[i];
		m_NIduration = NIduration[i];
		m_UreaseEfficiency = UreaseEfficiency[i];
		m_UreaseDuration = UreaseDuration[i];

		if (m_UreaseEfficiency > 0)m_UreaseInhibitor = 0;
		if (m_NIefficiency > 0)m_NitrificationInhibitor = 0;
		CEdit* Edt;

		Edt = (CEdit*)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_UreaseInhibitor);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_NitrificationInhibitor);
		Edt->EnableWindow(TRUE);
		if (m_DayRelease > 1.0)
		{
			m_ReleaseControl = 0;//added for turning on radio button if DayRelease was greater than 1.0
			Edt = (CEdit*)GetDlgItem(IDC_DayReleaseNote);
			Edt->EnableWindow(TRUE);
			Edt = (CEdit*)GetDlgItem(IDC_DayRelease);
			Edt->EnableWindow(TRUE);
			//UpdateData(TRUE);
		}

		m_FerList.DeleteAllItems();
		/*
		m_FertOption = 1;

		fscanf(db, "%f %f %f %f %f", &DayRelease[0], &NIefficiency[0], &NIduration[0],
				&UreaseEfficiency[0], &UreaseDuration[0]);

		m_DayRelease = DayRelease[0];
		m_NIefficiency = NIefficiency[0];
		m_NIduration = NIduration[0];
		m_UreaseEfficiency = UreaseEfficiency[0];
		m_UreaseDuration = UreaseDuration[0];

		CEdit *Edt;

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIefficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIduration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseEfficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseDuration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(FALSE); 

		m_FerList.DeleteAllItems();	
		*/
	}
	else if(FertOption==-3)//Precision-fertilization
	{
		m_FertOption = 3;

		fscanf(db, "%f %f %f %f %f", &DayRelease[0], &NIefficiency[0], &NIduration[0],
				&UreaseEfficiency[0], &UreaseDuration[0]);

		m_DayRelease = DayRelease[0];
		m_NIefficiency = NIefficiency[0];
		m_NIduration = NIduration[0];
		m_UreaseEfficiency = UreaseEfficiency[0];
		m_UreaseDuration = UreaseDuration[0];

		CEdit *Edt;

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(FALSE); 
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIefficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIduration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseEfficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseDuration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(FALSE); 

		m_FerList.DeleteAllItems();	
	}
	else //FertOption >= 0; Manual fertilization
	{
		int jd=0;

		m_FertOption = 0;

		m_FerN = FertOption;

		for(i=1; i<=m_FerN; i++)
		{
			FertID[i] = i;
			fscanf(db, "%d %d %d", &FertMonth[i], &FertDay[i], &FertMethod[i]);
			fscanf(db, "%f %f %f %f %f %f %f %f", &FertNitrate[i], &FertAbi[i], &FertUrea[i], &FertAnh[i], &FertAmNi[i], 
				&NH42SO4[i], &NH42HPO4[i], &FertDepth[i]);
			fscanf(db, "%f %f %f %f %f", &DayRelease[i], &NIefficiency[i], &NIduration[i],
				&UreaseEfficiency[i], &UreaseDuration[i]);

			if(DayRelease[i]<1.0) DayRelease[i] = 1.0;
		}
		fscanf(db, "%d", &jd);

		fclose(db);
		
		if(FertOption!=0) FertOption=0;

		i=1;
		m_FerID = FertID[i];
		m_FerMonth = FertMonth[i];
		m_FerDay = FertDay[i];
		m_FerMethod =FertMethod[i];
		m_FerNitrate = FertNitrate[i];
		m_FerAbi = FertAbi[i];
		m_FerUrea = FertUrea[i];
		m_FerAnh = FertAnh[i];
		m_FerNH4NO3 = FertAmNi[i];
		m_FerNH42SO4 = NH42SO4[i];
		m_FerNH42HPO4 = NH42HPO4[i];
		m_FerDepth = FertDepth[i];
		m_DayRelease = DayRelease[i];
		m_FertOption = FertOption;
		m_NIefficiency = NIefficiency[i];
		m_NIduration = NIduration[i];
		m_UreaseEfficiency = UreaseEfficiency[i];
		m_UreaseDuration = UreaseDuration[i];

		if(m_UreaseEfficiency>0)m_UreaseInhibitor=0;
			if(m_NIefficiency>0)m_NitrificationInhibitor=0;
		CEdit *Edt;

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
			Edt->EnableWindow(TRUE); 
			Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
			Edt->EnableWindow(TRUE);
			Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerDay);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerID);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerN);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
			Edt->EnableWindow(TRUE);
			Edt=(CEdit *)GetDlgItem(IDC_UreaseInhibitor);
			Edt->EnableWindow(TRUE);
			Edt=(CEdit *)GetDlgItem(IDC_NitrificationInhibitor);
			Edt->EnableWindow(TRUE);
			if (m_DayRelease > 1.0)
			{
				m_ReleaseControl = 0;//added for turning on radio button if DayRelease was greater than 1.0
				Edt = (CEdit*)GetDlgItem(IDC_DayReleaseNote);
				Edt->EnableWindow(TRUE);
				Edt = (CEdit*)GetDlgItem(IDC_DayRelease);
				Edt->EnableWindow(TRUE);
				//UpdateData(TRUE);
			}
			m_FerList.DeleteAllItems();	
	}

	demo();

		//CEdit *Edt;		

		/*if(m_unit==1)
		{
			m_FerNitrate /= lboac_kgoha;
			m_FerAbi /= lboac_kgoha;
			m_FerUrea /= lboac_kgoha;
			m_FerAnh /= lboac_kgoha;
			m_FerNH4NO3 /= lboac_kgoha;
			m_FerNH42SO4 /= lboac_kgoha;
			m_FerNH42HPO4 /= lboac_kgoha;
		}*/

		
/*
		if(DayRelease[i]>1.0)
		{
			Edt=(CEdit *)GetDlgItem(IDC_DayReleaseNote);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_DayRelease);
			Edt->EnableWindow(TRUE); 
			m_ReleaseControl=0;
		}

		
		
	if(DayRelease[i]==1.0)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_DayReleaseNote);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DayRelease);
		Edt->EnableWindow(FALSE); 
	}

	if(NIefficiency[i]==0.0)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_NIefficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIduration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(FALSE); 

		m_NitrificationInhibitor = -1;
	}
	else
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_NIefficiency);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIduration);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(TRUE); 

		m_NitrificationInhibitor = 0;
	}


	if(UreaseEfficiency[i]==0.0)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_UreaseEfficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseDuration);
		Edt->EnableWindow(FALSE);
		
		m_UreaseInhibitor = -1;
	}
	else
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_UreaseEfficiency);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseDuration);
		Edt->EnableWindow(TRUE); 

		m_UreaseInhibitor = 0;
	}
*/
	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}

/*BOOL SitePage6::CheckFerN()
{
		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

    if (m_FerN < 0) {
		MessageBox("Fertilization number must be >=0.", "Input Error:",NULL);
		m_FerN = 0;
		UpdateData(FALSE);
		return FALSE;
	}
	else if (m_FerN==0) {
		cycle.get(rrr,yyy)->FerNumber=0;
		return TRUE;
	}
	return TRUE;
}*/

/*void SitePage6::OnKillfocusFerN() 
{
	UpdateData(TRUE);
	CheckFerN();


	int n = m_FerList.GetItemCount();
	ResetListItem(m_FerN,n,"fer",&m_FerList);
*/
/*	char ch[20];
	int i;

	m_FerGrid.SetRows(m_FerN+1);
	m_FerGrid.SetCol(0);
	for (i = 1;i<=m_FerN;i++) {
		m_FerGrid.SetRow(i);
		sprintf(ch,"%dth",i);
        m_FerGrid.SetText(ch);
	}

	//SetArrayRange(3, m_FerN);
}*/

/*BOOL SitePage6::CheckFerID()
{
	if (!CheckFerN()) return FALSE;
	if (m_FerID ==0 ) return FALSE;
	if (m_FerID <0 || m_FerID > m_FerN) {
        MessageBox("The Fertilization ID number should be between 0 and total crop count!", "Input Error:",NULL);
		m_FerID = m_FerN;
		UpdateData(FALSE);
		return FALSE;
	}
	return TRUE;
}*/

/*void SitePage6::OnKillfocusFerID() 
{
	// Set default values
		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);

	if (!CheckFerID()) return;

	FertilizationParameter *FPnt;

	FPnt = fer.get(rrr, yyy,m_FerID);

	if (FPnt->month<0) return;
	m_FerMonth = FPnt->month;
	m_FerDay   = FPnt->day; 
	m_FerMethod= FPnt->method - 1;
	m_FerNitrate = FPnt->Nitrate; 
	m_FerAbi = FPnt->AmmBic; 
	m_FerUrea = FPnt->Urea; 
	m_FerAnh = FPnt->Anh; 
	m_FerNH4NO3 = FPnt->NH4NO3; 
	m_FerNH42SO4 = FPnt->NH42SO4; 
	m_FerNH42HPO4 = FPnt->NH42HPO4; 
	m_FerDepth = FPnt->Depth;
*/
/*	char ch[20];
	int   i,id;
	float dt;

            // Read data from the down-table
	m_FerGrid.SetRow(m_FerID);

	for (i = 1;i<=11;i++) {
		m_FerGrid.SetCol(i);
		strcpy(ch,m_FerGrid.GetText());
		if (strlen(ch)==0) {id=0;dt=0;}//continue;}
		else {
			sscanf(ch,"%d",&id);
			sscanf(ch,"%f",&dt);
		}
		if (id<0) id=0;
		if (dt<0) dt=0;

		if (i==1)       m_FerMonth   =id;
		else if (i==2)  m_FerDay     =id;
		else if (i==3)  m_FerMethod  =id-1;
		else if (i==4)  m_FerNitrate =dt;
		else if (i==5)  m_FerAbi     =dt;
		else if (i==6)  m_FerUrea    =dt;
		else if (i==7)  m_FerAnh     =dt;
		else if (i==8)  m_FerNH4NO3  =dt;
		else if (i==9)  m_FerNH42SO4 =dt;
		else if (i==10) m_FerNH42HPO4=dt;
		else if (i==11) m_FerDepth   =dt;
	}
	//UpdateData(FALSE);
}*/

void SitePage6::OnFerAccept() 
{
	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT6);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);

	//if(m_FerN>=1) m_FertOption=0;

	//unit conversion
	float mFerNitrate, mFerAbi, mFerUrea, mFerAnh, mFerNH4NO3, mFerNH42SO4, mFerNH42HPO4;
	if(m_unit==0)
	{
		mFerNitrate=m_FerNitrate;
		mFerAbi=m_FerAbi;
		mFerUrea=m_FerUrea;
		mFerAnh=m_FerAnh;
		mFerNH4NO3=m_FerNH4NO3;
		mFerNH42SO4=m_FerNH42SO4;
		mFerNH42HPO4=m_FerNH42HPO4;
	}
	else
	{
		mFerNitrate=m_FerNitrate*lboac_kgoha;//lb/ac -> kg/ha
		mFerAbi=m_FerAbi*lboac_kgoha;
		mFerUrea=m_FerUrea*lboac_kgoha;
		mFerAnh=m_FerAnh*lboac_kgoha;
		mFerNH4NO3=m_FerNH4NO3*lboac_kgoha;
		mFerNH42SO4=m_FerNH42SO4*lboac_kgoha;
		mFerNH42HPO4=m_FerNH42HPO4*lboac_kgoha;
	}

	UpdateData(FALSE);

	int i;
	i=m_FerID;		
	FertMonth[i]=m_FerMonth;
	FertDay[i]=m_FerDay;
	FertMethod[i]=m_FerMethod;
	FertNitrate[i]=mFerNitrate;
	FertAbi[i]=mFerAbi;
	FertUrea[i]=mFerUrea;
	FertAnh[i]=mFerAnh;
	FertAmNi[i]=mFerNH4NO3;
	NH42SO4[i]=mFerNH42SO4;
	NH42HPO4[i]=mFerNH42HPO4;
	FertDepth[i]=m_FerDepth;
	DayRelease[i]=m_DayRelease;
	NIefficiency[i]=m_NIefficiency;
	NIduration[i]=m_NIduration;
	UreaseEfficiency[i]=m_UreaseEfficiency;
	UreaseDuration[i]=m_UreaseDuration;

	if(m_FertOption==0) FertOption=m_FerN;//Manual fertilization
	else if(m_FertOption==1) FertOption=-2;//auto-fertilization
	else if(m_FertOption==2) FertOption=-1;//Fertigation
	else if(m_FertOption==3) FertOption=-3;//Precision fertilization
	else {}

	m_FGFileList.GetText(0, FertigationYear);

	DB.Format("%s\\CropFert_%d_%d.txt", FCT6, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	if(m_FertOption==0)//Manual fertilization
	{
		fprintf(db, "%d\n", m_FerN);

		for (i = 1; i<=m_FerN;i++) 
		{
			fprintf(db, "%d %d %d\n", FertMonth[i], FertDay[i], FertMethod[i]);
			fprintf(db, "%f %f %f %f %f %f %f %f\n", FertNitrate[i], FertAbi[i], FertUrea[i], FertAnh[i], FertAmNi[i], 
					NH42SO4[i], NH42HPO4[i], FertDepth[i]);
			fprintf(db, "%f %f %f %f %f\n", DayRelease[i], NIefficiency[i], NIduration[i],
				UreaseEfficiency[i], UreaseDuration[i]);
		}
		fprintf(db, "%d\n", 0);		

		demo();
	}
	else if(m_FertOption==1)//auto-fertilization
	{
		fprintf(db, "%d\n", -2);

		if (m_FerN == 1)
		{
			for (i = 2; i <= 2; i++)
			{
				FertID[i] = 1; FertMonth[i] = 0; FertDay[i] = 0; FertMethod[i] = 0;
				FertNitrate[i] = 0.0; FertAbi[i] = 0.0; FertUrea[i] = 0.0; FertAnh[i] = 0.0; FertAmNi[i] = 0.0; NH42SO4[i] = 0.0;
				NH42HPO4[i] = 0.0; FertDepth[i] = 0.2;
				DayRelease[i] = 1.0; NIefficiency[i] = 0.0; NIduration[i] = 0.0; FertOption = 0;
				UreaseEfficiency[i] = 0.0; UreaseDuration[i] = 0.0;
			}
			m_FerList.DeleteItem(1);
		}

		for (i = 1; i <= 2; i++)//m_FerN
		{
			fprintf(db, "%d %d %d\n", FertMonth[i], FertDay[i], FertMethod[i]);
			fprintf(db, "%f %f %f %f %f %f %f %f\n", FertNitrate[i], FertAbi[i], FertUrea[i], FertAnh[i], FertAmNi[i],
				NH42SO4[i], NH42HPO4[i], FertDepth[i]);
			fprintf(db, "%f %f %f %f %f\n", DayRelease[i], NIefficiency[i], NIduration[i],
				UreaseEfficiency[i], UreaseDuration[i]);
		}
		fprintf(db, "%d\n", 0);

		demo();
		/*
		fprintf(db, "%d\n", -2);
		fprintf(db, "%f %f %f %f %f\n", DayRelease[0], NIefficiency[0], NIduration[0], UreaseEfficiency[0], UreaseDuration[0]);
		*/
	}
	else if(m_FertOption==2)//Fertigation
	{


		
		fprintf(db, "%d\n", -1);
		fprintf(db, "%s\n", FertigationYear);
		fprintf(db, "%f %f %f %f %f\n", DayRelease[0], NIefficiency[0], NIduration[0], UreaseEfficiency[0], UreaseDuration[0]);
		
	}
	else if(m_FertOption==3)//Precision fertilization
	{
		fprintf(db, "%d\n", -3);
		fprintf(db, "%f %f %f %f %f\n", DayRelease[0], NIefficiency[0], NIduration[0], UreaseEfficiency[0], UreaseDuration[0]);
	}
	fclose(db);
}

void SitePage6::OnFerLast() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;

	i=m_FerID;		
		FertMonth[i]=m_FerMonth;
		FertDay[i]=m_FerDay;
		FertMethod[i]=m_FerMethod;
		FertNitrate[i]=m_FerNitrate;
		FertAbi[i]=m_FerAbi;
		FertUrea[i]=m_FerUrea;
		FertAnh[i]=m_FerAnh;
		FertAmNi[i]=m_FerNH4NO3;
		NH42SO4[i]=m_FerNH42SO4;
		NH42HPO4[i]=m_FerNH42HPO4;
		FertDepth[i]=m_FerDepth;
		NIefficiency[i]=m_NIefficiency;

		UreaseEfficiency[i]=m_UreaseEfficiency;
		UreaseDuration[i]=m_UreaseDuration;

		NIduration[i]=m_NIduration;
		DayRelease[i]=m_DayRelease;

	if (m_FerN==0) return;
	if (m_FerID>1) m_FerID--;
	else if (m_FerID==0) m_FerID=1;

	i=m_FerID;
		m_FerMonth = FertMonth[i];
		m_FerDay = FertDay[i];
		m_FerMethod =FertMethod[i];
		m_FerNitrate = FertNitrate[i];
		m_FerAbi = FertAbi[i];
		m_FerUrea = FertUrea[i];
		m_FerAnh = FertAnh[i];
		m_FerNH4NO3 = FertAmNi[i];
		m_FerNH42SO4 = NH42SO4[i];
		m_FerNH42HPO4 = NH42HPO4[i];
		m_FerDepth = FertDepth[i];
		m_NIefficiency=NIefficiency[i];
		m_NIduration=NIduration[i];
		m_DayRelease=DayRelease[i];

		m_UreaseEfficiency = UreaseEfficiency[i];
		m_UreaseDuration = UreaseDuration[i];


	UpdateData(FALSE);
	//OnKillfocusFerID();	
}

void SitePage6::OnFerNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_FerID;		
		FertMonth[i]=m_FerMonth;
		FertDay[i]=m_FerDay;
		FertMethod[i]=m_FerMethod;
		FertNitrate[i]=m_FerNitrate;
		FertAbi[i]=m_FerAbi;
		FertUrea[i]=m_FerUrea;
		FertAnh[i]=m_FerAnh;
		FertAmNi[i]=m_FerNH4NO3;
		NH42SO4[i]=m_FerNH42SO4;
		NH42HPO4[i]=m_FerNH42HPO4;
		FertDepth[i]=m_FerDepth;
		NIefficiency[i]=m_NIefficiency;
		NIduration[i]=m_NIduration;
		DayRelease[i]=m_DayRelease;

		UreaseEfficiency[i]=m_UreaseEfficiency;
		UreaseDuration[i]=m_UreaseDuration;

	if (m_FerN==0) return;
	if (m_FerID<m_FerN) m_FerID++;
	else if (m_FerID==0) m_FerID=1;

	i=m_FerID;
		m_FerMonth = FertMonth[i];
		m_FerDay = FertDay[i];
		m_FerMethod =FertMethod[i];
		m_FerNitrate = FertNitrate[i];
		m_FerAbi = FertAbi[i];
		m_FerUrea = FertUrea[i];
		m_FerAnh = FertAnh[i];
		m_FerNH4NO3 = FertAmNi[i];
		m_FerNH42SO4 = NH42SO4[i];
		m_FerNH42HPO4 = NH42HPO4[i];
		m_FerDepth = FertDepth[i];
		m_NIefficiency=NIefficiency[i];
		m_NIduration=NIduration[i];
		m_DayRelease=DayRelease[i];
		m_UreaseEfficiency=UreaseEfficiency[i];
		m_UreaseDuration=UreaseDuration[i];


	UpdateData(FALSE);
		
}

BEGIN_EVENTSINK_MAP(SitePage6, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage6)
	//ON_EVENT(SitePage6, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void SitePage6::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	//if (m_FerMethod != 2)
	//{
		UpdateData(TRUE);
		if (m_FerMethod == 0) m_FerDepth = 0.2;
		else if (m_FerMethod == 2)m_FerDepth = 10;
		else  m_FerDepth = 15;
	//}
		CEdit* Edt;
		if (m_FerMethod == 0)
		{
			Edt = (CEdit*)GetDlgItem(IDC_RADIO1);
			Edt->EnableWindow(TRUE);
			Edt = (CEdit*)GetDlgItem(IDC_RADIO2);
			Edt->EnableWindow(TRUE);
			Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
			Edt->EnableWindow(TRUE);
		}

		
	UpdateData(FALSE);
	
}

void SitePage6::OnRadio2() 
{
	/*
	UpdateData(TRUE);
	m_FerMethod = 1;
	m_FerDepth = 15;

	if (m_FerMethod == 0) m_FerDepth = 0.2;
	else if (m_FerMethod == 2)m_FerDepth = 10;
	else  m_FerDepth = 15;
	
	CEdit* Edt;
	if (m_FerMethod == 1)
	{
		Edt = (CEdit*)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(TRUE);
	}


	UpdateData(FALSE);
	*/

	OnRadio1();	
}

void SitePage6::OnRadio4()
{
	/*
	UpdateData(TRUE);
	m_FerMethod = 2;
	m_FerDepth = 10;

	if (m_FerMethod == 0) m_FerDepth = 0.2;
	else if (m_FerMethod == 2)m_FerDepth = 10;
	else  m_FerDepth = 15;
	//OnRadio2();
	
	CEdit* Edt;
	if (m_FerMethod == 2)
	{
		Edt = (CEdit*)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(TRUE);
	}



	UpdateData(FALSE);
	*/
	OnRadio1();
}

void SitePage6::OnKillfocusFerMonth() 
{
	//UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerDay() 
{
	//UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerDepth() 
{
	UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerNitrate() 
{
	UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerNH42HPO4() 
{
	UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerNH42SO4() 
{
	UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerNH4NO3() 
{
	UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerUrea() 
{
	UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerAbi() 
{
	UpdateData(TRUE);	
}

void SitePage6::OnKillfocusFerAnh() 
{
	UpdateData(TRUE);	
}

BOOL SitePage6::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString DB;
	FILE *db;	
	DB.Format("%s\\Inter\\UnitSystem", OUTPUT);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &m_unit);
	fclose(db);

	int i;
	char *title[]={"Fer-ID","Month","Day","Method","Nitrate",
		"NH4HCO3","Urea","NH3","NH4NO3","Sulphate",
		"(NH4)2HPO4","Depth"};
	int  ItemNum=12;
	for (i=0;i<ItemNum;i++)
	{
		m_FerList.InsertColumn(i,title[i],LVCFMT_CENTER,65,-1);
	}
	
	m_FerID = 1;

	UpdateData(FALSE);

	//Onunit2();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*void SitePage6::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_FerList.GetSelectionMark()+1;
    if (i > 0) 
	{
		m_FerID=i;
		UpdateData(FALSE);
		//OnKillfocusFerID();
	}
	
	*pResult = 0;
}*/

void SitePage6::demo()//populate the fertilzer list file
{
	int i;
	
	m_FerList.DeleteAllItems();	
   
	CString txt;
    if (m_FerN >= 0) 
	{
		if (FertMonth[2] == 0)m_FerN = 1;
		for (i = 1; i<=m_FerN;i++) 
		{
			txt = OrderNumber(i,"N-App",&txt);
			m_FerList.InsertItem(i-1,txt);

			txt.Format("%d",FertMonth[i]);
			m_FerList.SetItemText(i-1,1,txt);

			txt.Format("%d",FertDay[i]);
			m_FerList.SetItemText(i-1,2,txt);

			txt.Format("%d",FertMethod[i]);
			m_FerList.SetItemText(i-1,3,txt);

			txt.Format("%9.3f",FertNitrate[i]);
			m_FerList.SetItemText(i-1,4,txt);

			txt.Format("%9.3f",FertAbi[i]);
			m_FerList.SetItemText(i-1,5,txt);

			txt.Format("%9.3f",FertUrea[i]);
			m_FerList.SetItemText(i-1,6,txt);

			txt.Format("%9.3f",FertAnh[i]);
			m_FerList.SetItemText(i-1,7,txt);

			txt.Format("%9.3f",FertAmNi[i]);
			m_FerList.SetItemText(i-1,8,txt);

			txt.Format("%9.3f",NH42SO4[i]);
			m_FerList.SetItemText(i-1,9,txt);

			txt.Format("%9.3f",NH42HPO4[i]);
			m_FerList.SetItemText(i-1,10,txt);

			txt.Format("%9.3f",FertDepth[i]);
			m_FerList.SetItemText(i-1,11,txt);
        }
	}
}

void SitePage6::OnSelectFertigationFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int rrr, yyy;
	CString pre_WTFileName[5];
	CString f_site, cst;
	FILE *Fsite;

/*	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);
*/
	//Open a menu window
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();

	POSITION pos=ask.GetStartPosition();
	
	//Count number (num) of selected strings
	int k,num;
	num = m_FGFileList.GetCount();//1
		
	//Obtain order number (k) of each selected string
	k = m_FGFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		//Obtain a character from the string
		pre_WTFileName[num].Format("%s", ask.GetNextPathName(pos));
		if (pre_WTFileName[num]=="") break;

/*		f_site.Format("%s\\Inter\\WTfile_%d_%d", OUTPUT, rrr, yyy);
	
		Fsite = fopen(f_site, "w");
		if(Fsite==NULL)
		{
			CString note;
			note.Format("Can not create file %s", f_site);
			AfxMessageBox(note);
			exit(0);
		}
		fprintf(Fsite, "%s\n", pre_WTFileName[num]);	
		
		fclose(Fsite);
*/
		//Add the character into pre_ClimateFileName[num]
		m_FGFileList.InsertString(k, pre_WTFileName[num]);

		if (cst.IsEmpty() || pos==NULL) break;		
		if (m_FGFileList.GetCount()==1) break;

		k++;
	}

	//Put the string on screen
	m_FGFileList.SetCurSel(k);
	
	UpdateData(FALSE);
	
	
/*	char FileName[255];
	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_FGFileList.GetCount();
	if (num==1) return;
	
	k=m_FGFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_FGFileList.InsertString(k,FileName);
		sprintf(FertigationYear, FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_FGFileList.GetCount()==1) break;
		k++;
	}
	m_FGFileList.SetCurSel(k);
*/
//	UpdateData(FALSE);

/*	CString DB;
	FILE *db;

	DB.Format("%s\\Inter\\FertigationFiles_%d.txt", IData.year);
	db=fopen(DB, "w");
	fprintf(db, "%s\n", FertigationYear[1]);
	fclose(db);
*/
}

void SitePage6::OnFertigation() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString DB;
	FILE *db;	

	if(m_FertOption==0) 
	{
		//m_Fertigation=1;
		m_FertEvent = 0;

		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(TRUE); 	

		DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d", 1);
		fclose(db);

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(FALSE); 
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(FALSE);

		m_FerList.DeleteAllItems();	
	}
	else 
	{
		//m_Fertigation=0;
		m_FertEvent = 1;

		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(FALSE); 
		
		DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d", 0);
		fclose(db);

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(TRUE); 
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(TRUE);

		demo();
	}
	
	UpdateData(FALSE);
}

void SitePage6::OnFertEvent() 
{
	// TODO: Add your control notification handler code here 
	CString DB;
	FILE *db;

	if(m_FertEvent==0) 
	{
		m_FertEvent = 1;
		//m_Fertigation=0;

		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(FALSE); 
		
		DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d", 0);
		fclose(db);

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(TRUE); 
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(TRUE);

		demo();
	}
	else
	{
		m_FertEvent = 0;
		//m_Fertigation=1;

		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(TRUE); 	

		DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d", 1);
		fclose(db);

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(FALSE); 
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(FALSE); 

		m_FerList.DeleteAllItems();	
	}	

	UpdateData(FALSE);
	
}

void SitePage6::OnReleaseControl() 
{
	// TODO: Add your control notification handler code here
	m_DayRelease = 1.0;
	
	if(m_ReleaseControl==0) 
	{
		m_ReleaseControl = -1;
		UpdateData(FALSE);
	}

	UpdateData(TRUE);	

	CEdit *Edt;
	if(m_ReleaseControl==0) 
	{		
		Edt=(CEdit *)GetDlgItem(IDC_DayReleaseNote);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_DayRelease);
		Edt->EnableWindow(TRUE); 	
	}
	else
	{		
		Edt=(CEdit *)GetDlgItem(IDC_DayReleaseNote);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_DayRelease);
		Edt->EnableWindow(FALSE); 	
	}
		
	//	m_ReleaseControl = 1;
	//else m_ReleaseControl = 0;
	
	UpdateData(FALSE);
}

void SitePage6::OnNitrificationInhibitor() 
{
	// TODO: Add your control notification handler code here
	if(m_NitrificationInhibitor==0) 
	{
		m_NitrificationInhibitor = -1;
		m_NIefficiency = 0.0;
		m_NIduration = 0.0;
		UpdateData(FALSE);
	}

	UpdateData(TRUE);

	CEdit *Edt;
	if(m_NitrificationInhibitor==0)
	{
		Edt=(CEdit *)GetDlgItem(IDC_NIefficiency);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIduration);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(TRUE); 
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_NIefficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIduration);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(FALSE); 
	}
}

void SitePage6::OnFertMethod2()
{
	// TODO: Add your control notification handler code here ///autofertilizer-precision fertilizer option
	UpdateData(TRUE);
	if (m_FerN > 2)m_FerN = 2;
	else
	{
		m_FerN = 1;
	}
	//m_FerN = 1;
	m_FerID = 1;

	CString DB;
	FILE* db;

	CEdit* Edt;
	Edt = (CEdit*)GetDlgItem(IDC_FGFileList);
	Edt->EnableWindow(FALSE);
	Edt = (CEdit*)GetDlgItem(IDC_SelectFertigationFile);
	Edt->EnableWindow(FALSE);

	DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
	db = fopen(DB, "w");
	fprintf(db, "%d", 0);
	fclose(db);

	Edt = (CEdit*)GetDlgItem(IDC_RADIO1);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_RADIO2);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerAbi);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerAnh);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerDay);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerDepth);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerID);
	Edt->EnableWindow(FALSE);
	Edt = (CEdit*)GetDlgItem(IDC_FerMonth);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerN);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerNH42HPO4);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerNH42SO4);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerNH4NO3);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerNitrate);
	Edt->EnableWindow(TRUE);
	Edt = (CEdit*)GetDlgItem(IDC_FerUrea);
	Edt->EnableWindow(TRUE);
	m_FerList.DeleteItem(2);//deletes extra rows of fertilizer data. 
	m_FerList.DeleteItem(3);
	m_FerList.DeleteItem(4);
	m_FerList.DeleteItem(5);
	m_FerList.DeleteItem(6);//Brian
	UpdateData(FALSE);
	/*
	UpdateData(TRUE);
	m_FerN = 0;
	m_FerID = 0;
		m_FerMonth = 0;
		m_FerDay = 0;
		m_FerMethod =0;
		m_FerNitrate = 0.0;
		m_FerAbi = 0.0;
		m_FerUrea = 0.0;
		m_FerAnh = 0.0;
		m_FerNH4NO3 = 0.0;
		m_FerNH42SO4 = 0.0;
		m_FerNH42HPO4 = 0.0;
		m_FerDepth = 0.0;//FertDepth[i];
		m_DayRelease = 0.0;//DayRelease[i];
		//m_FertOption = FertOption;


	CString DB;
	FILE *db;

	CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(FALSE); 	

		DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d", 0);
		fclose(db);

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(FALSE); 

		m_FerList.DeleteAllItems();	

		UpdateData(FALSE);
		*/
}

void SitePage6::OnFertMethod1() 
{
	// TODO: Add your control notification handler code here //manual fert option
	CString DB;
	FILE *db;

	CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(FALSE); 	

		DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d", 0);
		fclose(db);

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(TRUE); 

		//m_FerN = 0;

		//UpdateData(FALSE);
}

void SitePage6::OnFertMethod3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_FerN = 0;
	m_FerID = 0;
		m_FerMonth = 0;
		m_FerDay = 0;
		m_FerMethod =0;
		m_FerNitrate = 0.0;
		m_FerAbi = 0.0;
		m_FerUrea = 0.0;
		m_FerAnh = 0.0;
		m_FerNH4NO3 = 0.0;
		m_FerNH42SO4 = 0.0;
		m_FerNH42HPO4 = 0.0;
		m_FerDepth = 0.0;//FertDepth[i];
		m_DayRelease = 0.0;//DayRelease[i];
		//m_FertOption = FertOption;


	CString DB;
	FILE *db;

	CEdit *Edt;
	
		Edt=(CEdit *)GetDlgItem(IDC_FGFileList);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_SelectFertigationFile);
		Edt->EnableWindow(TRUE);  	

		Edt=(CEdit *)GetDlgItem(IDC_RADIO1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_RADIO2);
		Edt->EnableWindow(FALSE); 
		Edt = (CEdit*)GetDlgItem(IDC_RADIO4);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_FerAbi);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerAnh);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerDepth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerID);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerN);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42HPO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH42SO4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNH4NO3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerNitrate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_FerUrea);
		Edt->EnableWindow(FALSE); 

		m_FerList.DeleteAllItems();	

		//DB.Format("%s\\Inter\\Fertigation.txt", OUTPUT);
		//db=fopen(DB, "w");
		//fprintf(db, "%d", 0);
		//fclose(db);

		UpdateData(FALSE);
}

void SitePage6::OnDblclkFGFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;
		
	num=m_FGFileList.GetCount();
	i=m_FGFileList.GetCurSel();
	
	CString fname;
	m_FGFileList.GetText(i,fname);
	m_FGFileList.DeleteString(i);	
	return;
}

void SitePage6::OnUreaseInhibitor() 
{
	// TODO: Add your control notification handler code here
	if(m_UreaseInhibitor==0) 
	{
		m_UreaseInhibitor = -1;
		m_UreaseEfficiency = 0.0;
		m_UreaseDuration = 0.0;
		UpdateData(FALSE);
	}

	UpdateData(TRUE);

	CEdit *Edt;
	if(m_UreaseInhibitor==0)
	{
		Edt=(CEdit *)GetDlgItem(IDC_UreaseEfficiency);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseDuration);
		Edt->EnableWindow(TRUE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(TRUE); */
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_UreaseEfficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_UreaseDuration);
		Edt->EnableWindow(FALSE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_NIa);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_NIb);
		Edt->EnableWindow(FALSE); */
	}
}

void SitePage6::Onunit() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==0&&n_unit==1) 
	{
		m_FerNitrate *= lboac_kgoha;//lb/ac -> kg/ha
		m_FerAbi *= lboac_kgoha;
		m_FerUrea *= lboac_kgoha;
		m_FerAnh *= lboac_kgoha;
		m_FerNH4NO3 *= lboac_kgoha;
		m_FerNH42SO4 *= lboac_kgoha;
		m_FerNH42HPO4 *= lboac_kgoha;
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 		
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
	}	

	UpdateData(FALSE);
}

void SitePage6::Onunit2() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==1&&n_unit==0) 
	{
		m_FerNitrate /= lboac_kgoha;//kg/ha -> lb/ac
		m_FerAbi /= lboac_kgoha;
		m_FerUrea /= lboac_kgoha;
		m_FerAnh /= lboac_kgoha;
		m_FerNH4NO3 /= lboac_kgoha;
		m_FerNH42SO4 /= lboac_kgoha;
		m_FerNH42HPO4 /= lboac_kgoha;
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE);
	}	
	
	UpdateData(FALSE);
}

void SitePage6::OnFertMethod4() 
{
	// TODO: Add your control notification handler code here
	OnFertMethod2();
}
