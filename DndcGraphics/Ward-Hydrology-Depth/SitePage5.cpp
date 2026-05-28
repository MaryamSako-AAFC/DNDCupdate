// SitePage5.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage5.h"
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
//extern Cycle_a_year			cycle;
//extern TillArray			till;
//extern FerArray				fer;
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

CString FCT5;
/////////////////////////////////////////////////////////////////////////////
// SitePage5 property page

IMPLEMENT_DYNCREATE(SitePage5, CPropertyPage)

SitePage5::SitePage5() : CPropertyPage(SitePage5::IDD)
{
	//{{AFX_DATA_INIT(SitePage5)
	m_TillDay = 0;
	m_TillID = 0;
	m_TillMonth = 0;
	m_TillN = 0;
	//}}AFX_DATA_INIT
}

SitePage5::~SitePage5()
{

}

void SitePage5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage5)
	DDX_Control(pDX, IDC_LIST1, m_TillList);
	DDX_Control(pDX, IDC_tillmethod, m_TillMethod);
	DDX_Text(pDX, IDC_tillDay, m_TillDay);
	DDX_Text(pDX, IDC_tillID, m_TillID);
	DDX_Text(pDX, IDC_tillMonth, m_TillMonth);
	DDX_Text(pDX, IDC_tillN, m_TillN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage5, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage5)
	ON_EN_KILLFOCUS(IDC_tillN, OnKillfocustillN)
	ON_EN_KILLFOCUS(IDC_tillMonth, OnKillfocustillMonth)
	ON_CBN_KILLFOCUS(IDC_tillmethod, OnKillfocustillmethod)
	ON_EN_KILLFOCUS(IDC_tillID, OnKillfocustillID)
	ON_EN_KILLFOCUS(IDC_tillDay, OnKillfocustillDay)
	ON_BN_CLICKED(IDC_TillAccept, OnTillAccept)
	ON_BN_CLICKED(IDC_TillNext, OnTillNext)
	ON_BN_CLICKED(IDC_TillLast, OnTillLast)
	//ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage5 message handlers

/*BOOL SitePage5::CheckTillN()
{
	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Result\\inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

    if (m_TillN < 0) 
	{
		MessageBox("Tillage number must be >=0", "Input Warning:",NULL);
		m_TillN =0;
		UpdateData(FALSE);
		return FALSE;
	}
	else if (m_TillN == 0 ) 
	{
		cycle.get(rrr,yyy)->TillNumber=0;   
		return FALSE;
	}
	return TRUE;
}*/

/*BOOL SitePage5::CheckTillID()
{
	if (!CheckTillN()) return FALSE;
	if (m_TillID ==0) return FALSE;//TRUE;
	if (m_TillID <0 || m_TillID > m_TillN ) {
		MessageBox("The Tillage ID number should be 1<=ID<=tillage number!", "Input Error:",NULL);
		m_TillID = m_TillN;
		UpdateData(FALSE);
		return FALSE;
	}
	return TRUE;
}*/

void SitePage5::OnKillfocustillN() 
{
	
	/*UpdateData(TRUE);
	CheckTillN();

	int n = m_TillList.GetItemCount();
	ResetListItem(m_TillN,n,"till",&m_TillList);*/

/*
	int i,
	char ch[20];

    m_TillGrid.SetRows(m_TillN + 1);
    m_TillGrid.SetCol(0);
    for (i = 1;i<=m_TillN;i++) {
		m_TillGrid.SetRow(i);
		sprintf(ch,"%dth",i);
		m_TillGrid.SetText(ch);
	}*/

    //SetArrayRange(2, m_TillN);
}

void SitePage5::OnKillfocustillMonth() 
{
	//UpdateData(TRUE);	
}

void SitePage5::OnKillfocustillmethod() 
{
	//UpdateData(TRUE);	
}

void SitePage5::OnKillfocustillID() // Set default values
{
/*		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Result\\inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);
	if (!CheckTillID()) return;
	if (m_TillID > m_TillN ) {
		MessageBox("The Tillage number should be between 1 and Total times!", "Input Error:",NULL);
		m_TillID = m_TillN;
		return;
	}

	TillageParameter *TPnt;
	TPnt = till.get(rrr, yyy,m_TillID);

	if (TPnt->month>0) 
		m_TillMonth = TPnt->month; 
	if (TPnt->day>0) 
		m_TillDay = TPnt->day;
	m_TillMethod.SetCurSel(TPnt->method - 1);
*/
/*
	char ch[20];
	int   i,id;

	if (m_TillN == 0) 
	{
		m_TillGrid.SetRows(1);
        return;
	}
        
	m_TillGrid.SetRow(m_TillID);
	for (i = 1; i<=3;i++) {
		m_TillGrid.SetCol(i);
		strcpy(ch,m_TillGrid.GetText()); 
		if (strlen(ch) == 0) continue;
		sscanf(ch,"%d",&id);
		if (id<0) id=0;
		if (i==1) m_TillMonth=id;
		else if (i==2) m_TillDay=id;
		else if (i==3) m_TillMethod.SetCurSel(id-1);
	}*/
	//UpdateData(FALSE);
}

void SitePage5::OnKillfocustillDay() 
{
	//UpdateData(TRUE);	
}

BOOL SitePage5::OnSetActive() 
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
	FCT5.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	FCT5.Format("%s_1", INTERMANAGE);
#endif

	int i;
	for(i=0; i<=290; i++) 
	{
		TillID[i]=0;
		TillMonth[i]=0;
		TillDay[i]=0;
		TillMethod[i]=0;
	}

	CString txt;

	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT5);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//DB.Format("%s\\inter\\CropTill_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropTill_%d_%d.txt", FCT5, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &m_TillN);

	if(m_TillN==0)
	{
		for(i=1; i<=20; i++)
		{
			TillID[i] = i;
			TillMonth[i]=0;
			TillDay[i]=0;
			TillMethod[i]=0;
		}
	}
	else
	{
		for(i=1; i<=m_TillN; i++)
		{
			TillID[i] = i;
			fscanf(db, "%d %d %d", &TillMonth[i], &TillDay[i], &TillMethod[i]);
		}
	}
	fclose(db);
	
	i=1;
		m_TillID = TillID[i];
		m_TillMonth = TillMonth[i];
		m_TillDay = TillDay[i];
		m_TillMethod.SetCurSel(TillMethod[i]-1);


	UpdateData(FALSE);

	demo();

/*	//m_TillList.DeleteAllItems();
 //   n = cycle.get(rrr, yyy)->TillNumber;
    if (m_TillN >= 0) 
	{
		//m_TillN = n;
		for (i = 1; i<=m_TillN;i++) 
		{
			txt = OrderNumber(i,"till",&txt);
			m_TillList.InsertItem(i-1,txt);

			txt.Format("%d",TillMonth[i]);
			m_TillList.SetItemText(i-1,1,txt);

			txt.Format("%d",TillDay[i]);
			m_TillList.SetItemText(i-1,2,txt);

			txt.Format("%d",TillMethod[i]);
			m_TillList.SetItemText(i-1,3,txt);
		}
	}
*/
/*        // Tilling table setup
    m_TillGrid.SetRows(1);
	m_TillGrid.SetCols(4);

    m_TillGrid.SetRow(0);
    m_TillGrid.SetCol(1);
    m_TillGrid.SetText("Month");
    m_TillGrid.SetCol(2);
    m_TillGrid.SetText("Day");
    m_TillGrid.SetCol(3);
    m_TillGrid.SetText("Method");

        // Tillage parameter
    n = cycle.get(rrr, yyy)->TillNumber;
    if (n >= 0) {
		m_TillN = n;
		m_TillGrid.SetRows(n+1);
		for (i = 1; i<=n;i++) {
			m_TillGrid.SetRow(i);
			m_TillGrid.SetCol(0);
			sprintf(ch,"%dth",i);
			m_TillGrid.SetText(ch);
			m_TillGrid.SetCol(1);
			sprintf(ch,"%d",till.get(rrr, yyy, i)->month);
			m_TillGrid.SetText(ch);
			m_TillGrid.SetCol(2);
			sprintf(ch,"%d",till.get(rrr, yyy, i)->day);
			m_TillGrid.SetText(ch);
			m_TillGrid.SetCol(3);
			sprintf(ch,"%d",till.get(rrr, yyy, i)->method);
			m_TillGrid.SetText(ch);
		}
    }*/
	//UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}

void SitePage5::OnTillAccept() 
{
	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT5);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);

	TillMonth[m_TillID] = m_TillMonth;
	TillDay[m_TillID] = m_TillDay;
	TillMethod[m_TillID] = m_TillMethod.GetCurSel()+1;

	//DB.Format("%s\\inter\\CropTill_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropTill_%d_%d.txt", FCT5, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d\n", m_TillN);

	for (int i = 1; i<=m_TillN;i++) 
	{
			fprintf(db, "%d  %d  %d\n", TillMonth[i], TillDay[i], TillMethod[i]);
	}
	fclose(db);

	demo();

	//if (!CheckTillID()) return;

/*	int n;
	char ch[20];
	
	if (m_TillN!= cycle.get(rrr, yyy)->TillNumber) {
		MessageBox("Total tillage number is WRONG","Input Error:",NULL);
		return;
	}


    //m_TillGrid.SetRow(m_TillID);
    //m_TillGrid.SetCol(1);

	if (!IfMonth(m_TillMonth)) return;
	sprintf(ch,"%d",m_TillMonth);
    //m_TillGrid.SetText(ch);
	m_TillList.SetItemText(m_TillID-1,1,ch);
	till.get(rrr, yyy,m_TillID)->month=m_TillMonth; 

    if (!IfDay(m_TillDay)) return;
	sprintf(ch,"%d",m_TillDay);
	//m_TillGrid.SetCol(2);
    //m_TillGrid.SetText(ch);
	m_TillList.SetItemText(m_TillID-1,2,ch);
	till.get(rrr, yyy,m_TillID)->day=m_TillDay;

    
	n=m_TillMethod.GetCurSel()+1;
	if (n<=0)
	{
		MessageBox("Please select a tillage mothod!","Input Warning:",NULL);
		return;
	}
	sprintf(ch,"%d",n);
	//m_TillGrid.SetCol(3);
    //m_TillGrid.SetText(ch);
	m_TillList.SetItemText(m_TillID-1,3,ch);
    till.get(rrr, yyy,m_TillID)->method=n;
	*/
}

BEGIN_EVENTSINK_MAP(SitePage5, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage5)
	//ON_EVENT(SitePage5, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*void SitePage5::OnClickMsflexgrid1() 
{
/*
    int i;
    i = m_TillGrid.GetRow();
    if (i > 0) {
		m_TillID=i;
		UpdateData(FALSE);
		OnKillfocustillID();
	}	*
}
*/
void SitePage5::OnTillNext() 
{
	UpdateData(TRUE);	

	//if (m_TillID>0)
	{
		TillMonth[m_TillID] = m_TillMonth;
		TillDay[m_TillID] = m_TillDay;
		TillMethod[m_TillID] = m_TillMethod.GetCurSel()+1;
	}

	//if (m_TillN==0) return;
	if (m_TillID<m_TillN) m_TillID++;
	//else if (m_TillID==0) m_TillID=1;

	m_TillMonth = TillMonth[m_TillID];
	m_TillDay = TillDay[m_TillID];
	m_TillMethod.SetCurSel(TillMethod[m_TillID]-1);

	UpdateData(FALSE);
	//OnKillfocustillID();

}

void SitePage5::OnTillLast() 
{
	UpdateData(TRUE);

	TillMonth[m_TillID] = m_TillMonth;
	TillDay[m_TillID] = m_TillDay;
	TillMethod[m_TillID] = m_TillMethod.GetCurSel()+1;

	if (m_TillN==0) return;
	if (m_TillID>1) m_TillID--;
	else if (m_TillID==0) m_TillID=1;

	m_TillMonth = TillMonth[m_TillID];
	m_TillDay = TillDay[m_TillID];
	m_TillMethod.SetCurSel(TillMethod[m_TillID]-1);

	UpdateData(FALSE);
	//OnKillfocustillID();
}

BOOL SitePage5::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
		//Set Tillage parameter list
		//Set list column
	int i;
	char *title[]={"Till-ID","Month","Day","Method"};
	int  ItemNum=4;
	for (i=0;i<ItemNum;i++)
	{
		m_TillList.InsertColumn(i,title[i],LVCFMT_CENTER,65,-1);
	}


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*void SitePage5::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_TillList.GetSelectionMark()+1;
    if (i > 0) 
	{
		m_TillID=i;
		UpdateData(FALSE);
		OnKillfocustillID();
	}
	
	*pResult = 0;
}*/

void SitePage5::demo()
{
	CString txt;
	m_TillList.DeleteAllItems();
    if (m_TillN >= 0) 
	{
		for (int i = 1; i<=m_TillN;i++) 
		{
			txt = OrderNumber(i,"till",&txt);
			m_TillList.InsertItem(i-1,txt);

			txt.Format("%d",TillMonth[i]);
			m_TillList.SetItemText(i-1,1,txt);

			txt.Format("%d",TillDay[i]);
			m_TillList.SetItemText(i-1,2,txt);

			txt.Format("%d",TillMethod[i]);
			m_TillList.SetItemText(i-1,3,txt);
		}
	}
}
