// SitePage11.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage11.h"
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

//extern Cycle_a_year			cycle;
//extern TillArray			till;
//extern FerArray				fer;
//extern ManureArray			manure;
//extern WeedArray			weed;
//extern FloodArray			flood;
//extern IrrigationArray		irrigation;
//extern GrazingArray         grazing;
//extern NowCropPractices		NowC;
extern CropofEachYear CYr[2];
extern char *soiltexture[];
extern char *soillanduse[];

CString FCT11;
/////////////////////////////////////////////////////////////////////////////
// SitePage11 property page

IMPLEMENT_DYNCREATE(SitePage11, CPropertyPage)

SitePage11::SitePage11() : CPropertyPage(SitePage11::IDD)
{
	//{{AFX_DATA_INIT(SitePage11)
	m_GrazingID = 0;
	m_GSDay = 0;
	m_GSMonth = 0;
	m_GEMonth = 0;
	m_GEDay = 0;
	m_GrazingN = 0;
	m_CattleHead = 0.0f;
	m_HorseHead = 0.0f;
	m_SheepHead = 0.0f;
	m_GrazingHour = 0.0f;
	m_CutTimes = 0;
	m_CutCode = 0;
	m_CutMonth = 0;
	m_CutDay = 0;
	m_CutAmount = 0.0f;
	m_CutLeaf = FALSE;
	m_CutStem = FALSE;
	m_CutRoot = FALSE;
	m_CutGrain = FALSE;
	m_DairyHead = 0.0f;
	m_PigHead = 0.0f;
	m_AddFeed = 0.0f;
	m_FeedCN = 0.0f;
	//}}AFX_DATA_INIT
}

SitePage11::~SitePage11()
{
	
}

void SitePage11::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage11)
	DDX_Control(pDX, IDC_Excreta, m_Excreta);
	DDX_Control(pDX, IDC_LIST4, m_CuttingList);
	DDX_Control(pDX, IDC_LIST1, m_GrazingList);
	DDX_Text(pDX, IDC_GrazingID, m_GrazingID);
	DDV_MinMaxInt(pDX, m_GrazingID, 0, 100);
	DDX_Text(pDX, IDC_GSDay, m_GSDay);
	DDX_Text(pDX, IDC_GSMonth, m_GSMonth);
	DDX_Text(pDX, IDC_GEMonth, m_GEMonth);
	DDX_Text(pDX, IDC_GEDay, m_GEDay);
	DDX_Text(pDX, IDC_GrazingN, m_GrazingN);
	DDV_MinMaxInt(pDX, m_GrazingN, 0, 100);
	DDX_Text(pDX, IDC_CattleHead, m_CattleHead);
	DDV_MinMaxFloat(pDX, m_CattleHead, 0.f, 99999.f);
	DDX_Text(pDX, IDC_HorseHead, m_HorseHead);
	DDV_MinMaxFloat(pDX, m_HorseHead, 0.f, 99999.f);
	DDX_Text(pDX, IDC_SheepHead, m_SheepHead);
	DDV_MinMaxFloat(pDX, m_SheepHead, 0.f, 99999.f);
	DDX_Text(pDX, IDC_GrazingHour, m_GrazingHour);
	DDV_MinMaxFloat(pDX, m_GrazingHour, 0.f, 24.f);
	DDX_Text(pDX, IDC_GrassCutTimes, m_CutTimes);
	DDX_Text(pDX, IDC_CutCode, m_CutCode);
	DDX_Text(pDX, IDC_CutMonth, m_CutMonth);
	DDX_Text(pDX, IDC_CutDay, m_CutDay);
	DDX_Text(pDX, IDC_CutAmount, m_CutAmount);
	DDX_Check(pDX, IDC_CutLeaf, m_CutLeaf);
	DDX_Check(pDX, IDC_CutStem, m_CutStem);
	DDX_Check(pDX, IDC_CutRoot, m_CutRoot);
	DDX_Check(pDX, IDC_CutGrain, m_CutGrain);
	DDX_Text(pDX, IDC_DairyHead, m_DairyHead);
	DDX_Text(pDX, IDC_PigHead, m_PigHead);
	DDX_Text(pDX, IDC_AddFeed, m_AddFeed);
	DDX_Text(pDX, IDC_FeedCN, m_FeedCN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage11, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage11)
	ON_EN_KILLFOCUS(IDC_GrazingN, OnKillfocusGrazingN)
	ON_EN_KILLFOCUS(IDC_GrazingID, OnKillfocusGrazingID)
	ON_BN_CLICKED(IDC_GAccept, OnGAccept)
	ON_BN_CLICKED(IDC_GLast, OnGLast)
	ON_BN_CLICKED(IDC_GNext, OnGNext)
	ON_EN_KILLFOCUS(IDC_GSMonth, OnKillfocusGSMonth)
	ON_EN_KILLFOCUS(IDC_GSDay, OnKillfocusGSDay)
	ON_EN_KILLFOCUS(IDC_GEMonth, OnKillfocusGEMonth)
	ON_EN_KILLFOCUS(IDC_GEDay, OnKillfocusGEDay)
	ON_EN_KILLFOCUS(IDC_SheepHead, OnKillfocusSheepHead)
	ON_EN_KILLFOCUS(IDC_HorseHead, OnKillfocusHorseHead)
	ON_EN_KILLFOCUS(IDC_CattleHead, OnKillfocusCattleHead)
	ON_EN_KILLFOCUS(IDC_GrazingHour, OnKillfocusGrazingHour)
	//ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_CutLast, OnCutLast)
	ON_BN_CLICKED(IDC_CutNext, OnCutNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage11 message handlers

void SitePage11::OnKillfocusGrazingN() 
{

}


void SitePage11::OnKillfocusGrazingID() // Set default values
{
	
}

BOOL SitePage11::OnSetActive() 
{
#ifdef MANURE
	int TotalManureCrops, CropIDID, ManureCropOrder;
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d %d", &TotalManureCrops, &ManureCropOrder, &CropIDID);
	fclose(xff);
	FCT11.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	FCT11.Format("%s_1", INTERMANAGE);
#endif

	int i;
	for(i=0; i<=290; i++)
	{
		GrazID[i]=0; GrazMonth1[i]=0; GrazDay1[i]=0; GrazMonth2[i]=0; GrazDay2[i]=0;
		GrazHour[i]=0.0; Beef[i]=0.0; Horse[i]=0.0; Sheep[i]=0.0; Dairy[i]=0.0; Pig[i]=0.0; 
		CutCode[i]=0; CutMonth[i]=0; CutDay[i]=0; CutAmount[i]=0.0; CutPart[i]=0;
		AddFeed[i]=0.0; FeedCN[i]=0.0;Excreta[i]=0;
	}

	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT11);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//DB.Format("%s\\inter\\CropGraz_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropGraz_%d_%d.txt", FCT11, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &m_GrazingN);
	if(m_GrazingN<0) m_GrazingN = 0;

	if(m_GrazingN==0)
	{
		for(i=1; i<=20; i++)
		{
			GrazID[i] = i;
			GrazMonth1[i]=0;
			GrazDay1[i]=0;
			GrazMonth2[i]=0;
			GrazDay2[i]=0;
			GrazHour[i]=0.0;
			Dairy[i]=0.0;
			Beef[i]=0.0;
			Horse[i]=0.0;
			Sheep[i]=0.0;
			Pig[i]=0.0;
			AddFeed[i]=0.0; 
			FeedCN[i]=0.0;
			Excreta[i]=1;
		}
	}
	else
	{
		for(i=1; i<=m_GrazingN; i++)
		{
			GrazID[i] = i;
			fscanf(db, "%d %d", &GrazMonth1[i], &GrazDay1[i]);
			fscanf(db, "%d %d", &GrazMonth2[i], &GrazDay2[i]);
			fscanf(db, "%f", &GrazHour[i]);
			fscanf(db, "%f %f %f %f %f", &Dairy[i], &Beef[i],&Pig[i], &Sheep[i], &Horse[i]);//1, 2/3, 4, 5, 7
			fscanf(db, "%f %f %d", &AddFeed[i], &FeedCN[i], &Excreta[i]);
		}
	}
	fclose(db);

	i=1;
		m_GrazingID = GrazID[i];
		m_GSMonth = GrazMonth1[i];
		m_GSDay = GrazDay1[i];
		m_GEMonth = GrazMonth2[i];
		m_GEDay = GrazDay2[i];
		m_GrazingHour =GrazHour[i];
		m_DairyHead = Dairy[i];
		m_CattleHead = Beef[i];
		m_HorseHead = Horse[i];
		m_SheepHead = Sheep[i];
		m_PigHead = Pig[i];
		m_AddFeed = AddFeed[i];
		m_FeedCN = FeedCN[i];
		m_Excreta.SetCurSel(Excreta[i]-1);

	///////////////////////////////////////////////////
	//DB.Format("%s\\inter\\GrassCut_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\GrassCut_%d_%d.txt", FCT11, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &m_CutTimes);

	if(m_CutTimes==0)
	{
		for(i=1; i<=20; i++)
		{
			CutCode[i] = i;
			CutMonth[i]=0;
			CutDay[i]=0;
			CutAmount[i]=0.8;
			CutPart[i]=0;
		}
	}
	else
	{
		for(i=1; i<=m_CutTimes; i++)
		{
			CutCode[i] = i;
			fscanf(db, "%d %d", &CutMonth[i], &CutDay[i]);
			fscanf(db, "%f", &CutAmount[i]);
			fscanf(db, "%d", &CutPart[i]);
		}
	}
	fclose(db);

	i=1;
		m_CutCode = CutCode[i];
		m_CutMonth = CutMonth[i];
		m_CutDay = CutDay[i];
		m_CutAmount =CutAmount[i];

	if(CutPart[i]==0)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==1)
	{
		m_CutGrain=1;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==2)
	{
		m_CutGrain=0;
		m_CutLeaf=1;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==3)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=1;
		m_CutRoot=0;
	}
	else if(CutPart[i]==4)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=1;
	}
	else if(CutPart[i]==5)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==6)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=1;
		m_CutRoot=0;
	}
	else if(CutPart[i]==7)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=1;
		m_CutRoot=1;
	}
		
	///////////////////////////////////////////////////

	UpdateData(FALSE);

	demo();

/*//	m_GrazingList.DeleteAllItems();
    //n = cycle.get(rrr, yyy)->GrazingNumber;
    if (m_GrazingN >= 0) 
	{
		//m_GrazingN = n;
		for (i = 1; i<=m_GrazingN;i++) 
		{
			txt = OrderNumber(i,"graz",&txt);
			m_GrazingList.InsertItem(i-1,txt);

			txt.Format("%d",GrazMonth1[i]);
			m_GrazingList.SetItemText(i-1,1,txt);

			txt.Format("%d",GrazDay1[i]);
			m_GrazingList.SetItemText(i-1,2,txt);

			txt.Format("%d",GrazMonth2[i]);
			m_GrazingList.SetItemText(i-1,3,txt);

			txt.Format("%d",GrazDay2[i]);
			m_GrazingList.SetItemText(i-1,4,txt);

			txt.Format("%9.2f",Cattle[i]);
			m_GrazingList.SetItemText(i-1,5,txt);

			txt.Format("%9.2f",Horse[i]);
			m_GrazingList.SetItemText(i-1,6,txt);

			txt.Format("%9.2f",Sheep[i]);
			m_GrazingList.SetItemText(i-1,7,txt);

			txt.Format("%9.2f",GrazHour[i]);
			m_GrazingList.SetItemText(i-1,8,txt);
		}
	}
*/
/*
        // Grazing setup
    m_GrazingGrid.SetRows(1);
	m_GrazingGrid.SetCols(9);

    m_GrazingGrid.SetRow(0);
    m_GrazingGrid.SetCol(1);
    m_GrazingGrid.SetText("S.Month");
    m_GrazingGrid.SetCol(2);
    m_GrazingGrid.SetText("S.Day");
    m_GrazingGrid.SetCol(3);
    m_GrazingGrid.SetText("E.Month");
    m_GrazingGrid.SetCol(4);
    m_GrazingGrid.SetText("E.Day");
    m_GrazingGrid.SetCol(5);
    m_GrazingGrid.SetText("CattleHead");//Type");
    m_GrazingGrid.SetCol(6);
    m_GrazingGrid.SetText("HorseHead");
    m_GrazingGrid.SetCol(7);
    m_GrazingGrid.SetText("SheepHead");
    m_GrazingGrid.SetCol(8);
    m_GrazingGrid.SetText("GrazHour");

        // Grazing parameter
	int i,n;
	char ch[20];
    n = cycle.get(rrr, yyy)->GrazingNumber;
    if (n >= 0) {
		m_GrazingN = n;
		m_GrazingGrid.SetRows(n+1);
		for (i = 1; i<=n;i++) {
			m_GrazingGrid.SetRow(i);
			
			m_GrazingGrid.SetCol(0);
			sprintf(ch,"%dth",i);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(1);
			sprintf(ch,"%d",grazing.get(rrr, yyy, i)->Smonth);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(2);
			sprintf(ch,"%d",grazing.get(rrr, yyy, i)->Sday);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(3);
			sprintf(ch,"%d",grazing.get(rrr, yyy, i)->Emonth);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(4);
			sprintf(ch,"%d",grazing.get(rrr, yyy, i)->Eday);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(5);
			sprintf(ch,"%d",grazing.get(rrr, yyy, i)->CattleHead);//Type);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(6);
			sprintf(ch,"%f",grazing.get(rrr, yyy, i)->HorseHead);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(7);
			sprintf(ch,"%f",grazing.get(rrr, yyy, i)->SheepHead);
			m_GrazingGrid.SetText(ch);

			m_GrazingGrid.SetCol(8);
			sprintf(ch,"%f",grazing.get(rrr, yyy, i)->GrazingHour);
			m_GrazingGrid.SetText(ch);

		}
    }*/
	//UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}

void SitePage11::OnGAccept() 
{
	UpdateData(TRUE);

	if(m_CutAmount>1.0||m_CutAmount<0.0)
	{
		CString note;
		note.Format("Please redefine cut fraction");
		AfxMessageBox(note);
		return;
	}

	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT11);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	int i;
	i=m_GrazingID;		
		GrazMonth1[i]=m_GSMonth;
		GrazDay1[i]=m_GSDay;
		GrazMonth2[i]=m_GEMonth;
		GrazDay2[i]=m_GEDay;
		GrazHour[i]=m_GrazingHour;
		Dairy[i]=m_DairyHead;
		Beef[i]=m_CattleHead;
		Horse[i]=m_HorseHead;
		Sheep[i]=m_SheepHead;
		Pig[i]=m_PigHead;
		AddFeed[i]=m_AddFeed;
		FeedCN[i]=m_FeedCN;
		Excreta[i]=m_Excreta.GetCurSel()+1;

	//DB.Format("%s\\inter\\CropGraz_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropGraz_%d_%d.txt", FCT11, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d\n", m_GrazingN);

	for (i = 1; i<=m_GrazingN;i++) 
	{
		fprintf(db, "%d %d\n", GrazMonth1[i], GrazDay1[i]);
		fprintf(db, "%d %d\n", GrazMonth2[i], GrazDay2[i]);
		fprintf(db, "%f\n", GrazHour[i]);
		fprintf(db, "%f %f %f %f %f\n", Dairy[i], Beef[i], Pig[i], Sheep[i], Horse[i]);
		fprintf(db, "%f %f %d\n", AddFeed[i], FeedCN[i], Excreta[i]);
	}
	fclose(db);

		//////////////////////////////////////////////////////
	i=m_CutCode;		
		CutMonth[i]=m_CutMonth;
		CutDay[i]=m_CutDay;
		CutAmount[i]=m_CutAmount;

		if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=0;//cut nothing
		else if(m_CutGrain==1&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=1;//cut fruit
		else if(m_CutGrain==0&&m_CutLeaf==1&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=2;//cut leaf
		else if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=3;//cut stem
		else if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==1) CutPart[i]=4;//cut root
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=5;//cut fruit and leaf
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=6;//cut fruit, leaf and stem
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==1) CutPart[i]=7;//cut fruit, leaf, stem and root
		else if(m_CutGrain==0&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=8;//cut leaf and stem
		else 
		{
			CString Mmm;
			Mmm.Format("Please select another combination");
			AfxMessageBox(Mmm);
			return;
		}
		
	//DB.Format("%s\\inter\\GrassCut_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\GrassCut_%d_%d.txt", FCT11, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d\n", m_CutTimes);

	for (i = 1; i<=m_CutTimes;i++) 
	{
		fprintf(db, "%d %d\n", CutMonth[i], CutDay[i]);
		fprintf(db, "%f\n", CutAmount[i]);//fraction
		fprintf(db, "%d\n", CutPart[i]);
	}
	fclose(db);

	//////////////////////////////////////////////////////
	
	
	demo();

/*	char ch[20];
	
	if (m_GrazingN!= cycle.get(rrr, yyy)->GrazingNumber) {
		MessageBox("Total Grazing number is WRONG","Input Error:",NULL);
		return;
	}

	if (m_GrazingID<=0 || m_GrazingID>m_GrazingN) return;

    //m_GrazingGrid.SetRow(m_GrazingID);
    
	if (!IfMonth(m_GSMonth)) return;
	//m_GrazingGrid.SetCol(1);
	sprintf(ch,"%d",m_GSMonth);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,1,ch);
	grazing.get(rrr, yyy,m_GrazingID)->Smonth=m_GSMonth;

	if (!IfDay(m_GSDay)) return;
    //m_GrazingGrid.SetCol(2);
	sprintf(ch,"%d",m_GSDay);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,2,ch);
	grazing.get(rrr, yyy,m_GrazingID)->Sday=m_GSDay;

	if (!IfMonth(m_GEMonth)) return;
	//m_GrazingGrid.SetCol(3);
	sprintf(ch,"%d",m_GEMonth);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,3,ch);
	grazing.get(rrr, yyy,m_GrazingID)->Emonth=m_GEMonth;

	if (!IfDay(m_GEDay)) return;
    //m_GrazingGrid.SetCol(4);
	sprintf(ch,"%d",m_GEDay);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,4,ch);
	grazing.get(rrr, yyy,m_GrazingID)->Eday=m_GEDay;
    
	//m_GrazingGrid.SetCol(5);
	sprintf(ch,"%9.2f",m_CattleHead);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,5,ch);
    grazing.get(rrr, yyy,m_GrazingID)->CattleHead=m_CattleHead;

    //m_GrazingGrid.SetCol(6);
	sprintf(ch,"%9.2f",m_HorseHead);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,6,ch);
	grazing.get(rrr, yyy,m_GrazingID)->HorseHead=m_HorseHead;

    //m_GrazingGrid.SetCol(7);
	sprintf(ch,"%9.2f",m_SheepHead);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,7,ch);
	grazing.get(rrr, yyy,m_GrazingID)->SheepHead=m_SheepHead;

    //m_GrazingGrid.SetCol(8);
	sprintf(ch,"%9.2f",m_GrazingHour);
    //m_GrazingGrid.SetText(ch);
	m_GrazingList.SetItemText(m_GrazingID-1,8,ch);
	grazing.get(rrr, yyy,m_GrazingID)->GrazingHour=m_GrazingHour;
*/
}

void SitePage11::OnGLast() 
{
	UpdateData(TRUE);

	int i;
	i=m_GrazingID;		
		GrazMonth1[i]=m_GSMonth;
		GrazDay1[i]=m_GSDay;
		GrazMonth2[i]=m_GEMonth;
		GrazDay2[i]=m_GEDay;
		GrazHour[i]=m_GrazingHour;
		Dairy[i]=m_DairyHead;
		Beef[i]=m_CattleHead;
		Horse[i]=m_HorseHead;
		Sheep[i]=m_SheepHead;
		Pig[i]=m_PigHead;
		AddFeed[i]=m_AddFeed;
		FeedCN[i]=m_FeedCN;
		Excreta[i]=m_Excreta.GetCurSel()+1;

	if (m_GrazingN==0) return;
	if (m_GrazingID>1) m_GrazingID--;
	else if (m_GrazingID==0) m_GrazingID=1;

	i=m_GrazingID;		
		m_GSMonth=GrazMonth1[i];
		m_GSDay=GrazDay1[i];
		m_GEMonth=GrazMonth2[i];
		m_GEDay=GrazDay2[i];
		m_GrazingHour=GrazHour[i];
		m_DairyHead=Dairy[i];
		m_CattleHead=Beef[i];
		m_HorseHead=Horse[i];
		m_SheepHead=Sheep[i];
		m_PigHead=Pig[i];
		m_AddFeed = AddFeed[i];
		m_FeedCN = FeedCN[i];
		m_Excreta.SetCurSel(Excreta[i]-1);

	UpdateData(FALSE);
	//OnKillfocusGrazingID();	
}



void SitePage11::OnGNext() 
{
	UpdateData(TRUE);

	int i;
	i=m_GrazingID;		
		GrazMonth1[i]=m_GSMonth;
		GrazDay1[i]=m_GSDay;
		GrazMonth2[i]=m_GEMonth;
		GrazDay2[i]=m_GEDay;
		GrazHour[i]=m_GrazingHour;
		Dairy[i]=m_DairyHead;
		Beef[i]=m_CattleHead;
		Horse[i]=m_HorseHead;
		Sheep[i]=m_SheepHead;
		Pig[i]=m_PigHead;
		AddFeed[i]=m_AddFeed;
		FeedCN[i]=m_FeedCN;
		Excreta[i]=m_Excreta.GetCurSel()+1;

	if (m_GrazingN==0) return;
	if (m_GrazingID<m_GrazingN) m_GrazingID++;
	else if (m_GrazingID==0) m_GrazingID=1;

	i=m_GrazingID;		
		m_GSMonth=GrazMonth1[i];
		m_GSDay=GrazDay1[i];
		m_GEMonth=GrazMonth2[i];
		m_GEDay=GrazDay2[i];
		m_GrazingHour=GrazHour[i];
		m_DairyHead=Dairy[i];
		m_CattleHead=Beef[i];
		m_HorseHead=Horse[i];
		m_SheepHead=Sheep[i];
		m_PigHead=Pig[i];
		m_AddFeed = AddFeed[i];
		m_FeedCN = FeedCN[i];
		m_Excreta.SetCurSel(Excreta[i]-1);

	UpdateData(FALSE);
	//OnKillfocusGrazingID();	
}

void SitePage11::OnKillfocusGSMonth() 
{
	UpdateData(TRUE);	
}

void SitePage11::OnKillfocusGSDay() 
{
	UpdateData(TRUE);	
}

void SitePage11::OnKillfocusGEMonth() 
{
	UpdateData(TRUE);		
}

void SitePage11::OnKillfocusGEDay() 
{
	UpdateData(TRUE);		
}


BEGIN_EVENTSINK_MAP(SitePage11, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage11)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*void SitePage11::OnClickMsflexgrid1() 
{
    int i;
    i = m_GrazingGrid.GetRow();
    if (i > 0) {
		m_GrazingID=i;
		UpdateData(FALSE);
		OnKillfocusGrazingID();
	}
}*/	

void SitePage11::OnKillfocusSheepHead() 
{
	UpdateData(TRUE);		
}

void SitePage11::OnKillfocusHorseHead() 
{
	UpdateData(TRUE);	
}

void SitePage11::OnKillfocusCattleHead() 
{
	UpdateData(TRUE);	
}

void SitePage11::OnKillfocusGrazingHour() 
{
	UpdateData(TRUE);
}

/*void SitePage11::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i = m_GrazingList.GetSelectionMark()+1;
    if (i > 0) 
	{
		m_GrazingID=i;
		UpdateData(FALSE);
		OnKillfocusGrazingID();
	}
	
	*pResult = 0;
}*/

BOOL SitePage11::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
		//Set Tillage parameter list
		//Set list column
	int i;
	char *title[]={"Graz.ID","Start M","Start Day","End M","End Day",
		"Dairy","Beef","Pig","Sheep","Horse","Hours"};
	int  ItemNum=11;
	for (i=0;i<ItemNum;i++)
	{
		m_GrazingList.InsertColumn(i,title[i],LVCFMT_CENTER,65,-1);
	}
	
	char *title2[]={"Cut.ID","Month","Day","Fraction"};
	ItemNum=4;
	for (i=0;i<ItemNum;i++)
	{
		m_CuttingList.InsertColumn(i,title2[i],LVCFMT_CENTER,65,-1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SitePage11::demo() 
{
	int i;
	CString txt;
	m_GrazingList.DeleteAllItems();
 
    if (m_GrazingN >= 0) 
	{
		for (i = 1; i<=m_GrazingN;i++) 
		{
			txt = OrderNumber(i,"graz",&txt);
			m_GrazingList.InsertItem(i-1,txt);

			txt.Format("%d",GrazMonth1[i]);
			m_GrazingList.SetItemText(i-1,1,txt);

			txt.Format("%d",GrazDay1[i]);
			m_GrazingList.SetItemText(i-1,2,txt);

			txt.Format("%d",GrazMonth2[i]);
			m_GrazingList.SetItemText(i-1,3,txt);

			txt.Format("%d",GrazDay2[i]);
			m_GrazingList.SetItemText(i-1,4,txt);

			txt.Format("%9.2f",Dairy[i]);
			m_GrazingList.SetItemText(i-1,5,txt);

			txt.Format("%9.2f",Beef[i]);
			m_GrazingList.SetItemText(i-1,6,txt);

			txt.Format("%9.2f",Pig[i]);
			m_GrazingList.SetItemText(i-1,7,txt);

			txt.Format("%9.2f",Sheep[i]);
			m_GrazingList.SetItemText(i-1,8,txt);

			txt.Format("%9.2f",Horse[i]);
			m_GrazingList.SetItemText(i-1,9,txt);

			txt.Format("%9.2f",GrazHour[i]);
			m_GrazingList.SetItemText(i-1,10,txt);
		}
	}

	m_CuttingList.DeleteAllItems();
 
    if (m_CutTimes >= 0) 
	{
		for (i = 1; i<=m_CutTimes;i++) 
		{
			txt = OrderNumber(i,"cut",&txt);
			m_CuttingList.InsertItem(i-1,txt);

			txt.Format("%d",CutMonth[i]);
			m_CuttingList.SetItemText(i-1,1,txt);

			txt.Format("%d",CutDay[i]);
			m_CuttingList.SetItemText(i-1,2,txt);

			txt.Format("%5.2f",CutAmount[i]);
			m_CuttingList.SetItemText(i-1,3,txt);
		}
	}
}

void SitePage11::OnCutLast() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_CutCode;		
		CutMonth[i]=m_CutMonth;
		CutDay[i]=m_CutDay;		
		CutAmount[i]=m_CutAmount;
		
		if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=0;//cut nothing
		else if(m_CutGrain==1&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=1;//cut fruit
		else if(m_CutGrain==0&&m_CutLeaf==1&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=2;//cut leaf
		else if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=3;//cut stem
		else if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==1) CutPart[i]=4;//cut root
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=5;//cut fruit and leaf
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=6;//cut fruit, leaf and stem
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==1) CutPart[i]=7;//cut fruit, leaf, stem and root
		else if(m_CutGrain==0&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=8;//cut leaf, stem
		else 
		{
			CString Mmm;
			Mmm.Format("Please re-define the cut combination");
			AfxMessageBox(Mmm);
			return;
		}

	if (m_CutTimes==0) return;
	if (m_CutCode>1) m_CutCode--;
	else if (m_CutCode==0) m_CutCode=1;

	i=m_CutCode;		
		m_CutMonth=CutMonth[i];
		m_CutDay=CutDay[i];		
		m_CutAmount=CutAmount[i];

	if(CutPart[i]==0)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==1)
	{
		m_CutGrain=1;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==2)
	{
		m_CutGrain=0;
		m_CutLeaf=1;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==3)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=1;
		m_CutRoot=0;
	}
	else if(CutPart[i]==4)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=1;
	}
	else if(CutPart[i]==5)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==6)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=1;
		m_CutRoot=0;
	}
	else if(CutPart[i]==7)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=1;
		m_CutRoot=1;
	}
		
	UpdateData(FALSE);
	
}

void SitePage11::OnCutNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_CutCode;		
		CutMonth[i]=m_CutMonth;
		CutDay[i]=m_CutDay;		
		CutAmount[i]=m_CutAmount;

		if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=0;//cut nothing
		else if(m_CutGrain==1&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=1;//cut fruit
		else if(m_CutGrain==0&&m_CutLeaf==1&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=2;//cut leaf
		else if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=3;//cut stem
		else if(m_CutGrain==0&&m_CutLeaf==0&&m_CutStem==0&&m_CutRoot==1) CutPart[i]=4;//cut root
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==0&&m_CutRoot==0) CutPart[i]=5;//cut fruit and leaf
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=6;//cut fruit, leaf and stem
		else if(m_CutGrain==1&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==1) CutPart[i]=7;//cut fruit, leaf, stem and root
		else if(m_CutGrain==0&&m_CutLeaf==1&&m_CutStem==1&&m_CutRoot==0) CutPart[i]=8;//cut leaf, stem
		else 
		{
			CString Mmm;
			Mmm.Format("Please re-define the combination");
			AfxMessageBox(Mmm);
			return;
		}

	if (m_CutTimes==0) return;
	if (m_CutCode<m_CutTimes) m_CutCode++;
	else if (m_CutCode==0) m_CutCode=1;

	i=m_CutCode;		
		m_CutMonth=CutMonth[i];
		m_CutDay=CutDay[i];		
		m_CutAmount=CutAmount[i];

	if(CutPart[i]==0)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==1)
	{
		m_CutGrain=1;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==2)
	{
		m_CutGrain=0;
		m_CutLeaf=1;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==3)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=1;
		m_CutRoot=0;
	}
	else if(CutPart[i]==4)
	{
		m_CutGrain=0;
		m_CutLeaf=0;
		m_CutStem=0;
		m_CutRoot=1;
	}
	else if(CutPart[i]==5)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=0;
		m_CutRoot=0;
	}
	else if(CutPart[i]==6)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=1;
		m_CutRoot=0;
	}
	else if(CutPart[i]==7)
	{
		m_CutGrain=1;
		m_CutLeaf=1;
		m_CutStem=1;
		m_CutRoot=1;
	}

	UpdateData(FALSE);
}
