// SitePage10.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage10.h"
#include "SitePSheet.h"
#include "dndc_main.h"
#include "RunPaths.h"

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

CString FCT10;
/////////////////////////////////////////////////////////////////////////////
// SitePage10 property page

IMPLEMENT_DYNCREATE(SitePage10, CPropertyPage)

SitePage10::SitePage10() : CPropertyPage(SitePage10::IDD)
{
	//{{AFX_DATA_INIT(SitePage10)
	m_IrrMode = 0;
	m_IrrIndex = 1.0f;
	m_IrrpH = 0.0f;
	m_IrrAmount = 0.0f;
	m_TileIrriDays = 0;
	m_IrrDay = 0;
	m_IrrID = 0;
	m_IrrMonth = 0;
	m_IrrN = 0;
	m_IrriMethod = 0;
	m_TileIrri=0;

	m_DrainDay=0;
	m_DrainMonth=0;
	m_CDrainA=0;//control drain application #
	m_CDrain=0;
	m_DrainDay2=0;
	m_DrainMonth2=0;
	m_CDrainDepth=0.0f;

	//}}AFX_DATA_INIT
}

SitePage10::~SitePage10()
{

}

void SitePage10::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage10)
    DDX_Control(pDX, IDC_DrainList, m_DrainList);
	DDX_Control(pDX, IDC_LIST1, m_IrrList);
	DDX_Control(pDX, IDC_ifIndex, m_ifIndex);
	DDX_Control(pDX, IDC_ifEvent, m_ifEvent);
	DDX_Radio(pDX, IDC_IrrOption1, m_IrrMode);
	DDX_Text(pDX, IDC_IrrIndex, m_IrrIndex);
	DDX_Text(pDX, IDC_irrigationpH, m_IrrpH);
	DDX_Text(pDX, IDC_irrigationAmount, m_IrrAmount);
	DDX_Text(pDX, IDC_TileIrriDays, m_TileIrriDays);
	DDX_Text(pDX, IDC_irrigationDay, m_IrrDay);
	DDX_Text(pDX, IDC_irrigationID, m_IrrID);
	DDX_Text(pDX, IDC_irrigationMonth, m_IrrMonth);
	DDX_Text(pDX, IDC_irrigationN, m_IrrN);
	DDX_Radio(pDX, IDC_WT, m_IrriMethod);
	DDX_Text(pDX, IDC_CDrain, m_CDrain);
	DDX_Text(pDX, IDC_CDrainA, m_CDrainA);
	DDX_Text(pDX, IDC_DrainDay, m_DrainDay);
	DDX_Text(pDX, IDC_DrainMonth, m_DrainMonth);
	DDX_Text(pDX, IDC_DrainMonth2, m_DrainMonth2);
	DDX_Text(pDX, IDC_DrainDay2, m_DrainDay2);
	DDX_Text(pDX, IDC_CDrainDepth, m_CDrainDepth);
	DDX_Text(pDX, IDC_TileIrriDays, m_TileIrriDays);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage10, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage10)
	ON_BN_CLICKED(IDC_IrrOption0, OnIrrOption0)
	ON_BN_CLICKED(IDC_IrrOption1, OnIrrOption1)
	ON_EN_KILLFOCUS(IDC_irrigationN, OnKillfocusirrigationN)
	ON_EN_KILLFOCUS(IDC_irrigationID, OnKillfocusirrigationID)
	ON_BN_CLICKED(IDC_IrrAccept, OnIrrAccept)
	ON_BN_CLICKED(IDC_IrrLast, OnIrrLast)
	ON_BN_CLICKED(IDC_IrrNext, OnIrrNext)
	ON_EN_CHANGE(IDC_IrrIndex, OnChangeIrrIndex)
	ON_EN_KILLFOCUS(IDC_irrigationMonth, OnKillfocusirrigationMonth)
	ON_EN_KILLFOCUS(IDC_irrigationDay, OnKillfocusirrigationDay)
	ON_EN_KILLFOCUS(IDC_irrigationAmount, OnKillfocusirrigationAmount)
	ON_EN_KILLFOCUS(IDC_irrigationpH, OnKillfocusirrigationpH)
	ON_BN_CLICKED(IDC_DrLast, OnDrLast)
	ON_BN_CLICKED(IDC_DrNext, OnDrNext)
	//ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage10 message handlers

BOOL SitePage10::OnSetActive() 
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
	FCT10.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	FCT10.Format("%s_1", INTERMANAGE);
#endif

	int rrr, yyy, i;
		for(i=0; i<=290; i++)
	{
		IrriID[i]=0; IrriMonth[i]=0; IrriDay[i]=0;
		IrriAmount[i]=0.0; IrriMethod[i]=0;TileIrriDays[i]=0;
	}
		for(i=0; i<=290; i++)
	{
		CDrainA[i]=0; DrainMonth[i]=0; DrainDay[i]=0;
		DrainMonth2[i]=0; DrainDay2[i]=0;CDrainDepth[i]=0.0;
	}


	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT10);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	DB.Format("%s\\CropIrri_%d_%d.txt", FCT10, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d %d %f %d", &m_IrrN, &m_IrrMode, &m_IrrIndex, &IrriMethod[0]);
	for (i = 1; i<=m_IrrN;i++) 
	{
		fscanf(db, "%d %d", &IrriMonth[i], &IrriDay[i]);
		fscanf(db, "%f %d %d", &IrriAmount[i], &IrriMethod[i], &TileIrriDays[i]);
	}
	fclose(db);


	if(m_IrrN >=1) m_IrrMode = 0;

    if (m_IrrMode == 1) //by index
	{ 
		//if (cycle.get(rrr, yyy)->IrrIndex<0 || cycle.get(rrr, yyy)->IrrIndex>1) 
		//	cycle.get(rrr, yyy)->IrrIndex=0;
		m_IrrN = 0;
		//m_IrrIndex=cycle.get(rrr, yyy)->IrrIndex;

		m_IrriMethod = IrriMethod[0];

		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_irrigationN);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_irrigationID);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_irrigationAmount);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_irrigationMonth);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_irrigationDay);
		Edt->EnableWindow(FALSE);

		//Edt=(CEdit *)GetDlgItem(IDC_WT);
		//Edt->EnableWindow(FALSE);

		UpdateData(FALSE);
		//Op=(CButton *)GetDlgItem(IDC_IrrOption0);
		//Op->SetCheck(1);
		//OnIrrOption0();
	}
	else 				// by events
	{
		m_IrrIndex=0.0;		

		//m_IrrN=IrrNumber;
		if(m_IrrN < 0) m_IrrN = 0;
		UpdateData(FALSE);
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_IrrIndex);
		Edt->EnableWindow(FALSE);
		//Edt=(CEdit *)GetDlgItem(IDC_WT);
		//Edt->EnableWindow(TRUE);

		//Op=(CButton *)GetDlgItem(IDC_IrrOption1);
		//Op->SetCheck(1);
		//OnIrrOption1();

		if(m_IrrN==0)
		{
			 
			for(i=1; i<=20; i++)
				{
					IrriID[i] = i;
					IrriMonth[i]=0;
					IrriDay[i]=0;
					IrriAmount[i]=0.0;
					IrriMethod[i]=0;
				}
		}
		else
		{
				for(i=1; i<=m_IrrN; i++)
				{
					IrriID[i] = i;
					fscanf(db, "%d %d", &IrriMonth[i], &IrriDay[i]);
					fscanf(db, "%f %d", &IrriAmount[i], &IrriMethod[i],&TileIrriDays[i]);
				}
		}
		i=1;
		m_IrrID = IrriID[i];
		m_IrrMonth = IrriMonth[i];
		m_IrrDay = IrriDay[i];
		m_IrrAmount =IrriAmount[i];
		m_IrriMethod = IrriMethod[i];
		m_TileIrriDays = TileIrriDays[i];

		UpdateData(FALSE);
	}

	fclose(db);	


	//controlled drainage

	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT10);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	DB.Format("%s\\CTDrain_%d_%d.txt", FCT10, rrr, yyy);
	db=fopen(DB, "r");
	fscanf(db, "%d", &m_CDrain);
	for (i = 1; i<=m_CDrain;i++) 
	{
		fscanf(db, "%d %d", &DrainMonth[i], &DrainDay[i]);
		fscanf(db, "%d %d %f", &DrainMonth2[i], &DrainDay2[i], &CDrainDepth[i]);
	}
	fclose(db);

	
	
	
		if(m_CDrain < 0) m_CDrain = 0;
		UpdateData(FALSE);
		if(m_CDrain==0)
		{
			 
			for(i=1; i<=20; i++)
				{
					CDrainA[i] = i;
					DrainMonth[i]=0;
					DrainDay[i]=0;
					CDrainDepth[i]=0.0;
					DrainDay2[i]=0;
					DrainMonth2[i]=0;
				}
		}
		else
		{
			DB.Format("%s\\CTDrain_%d_%d.txt", FCT10, rrr, yyy);
			db=fopen(DB, "r");
			fscanf(db, "%d", &m_CDrain);
			for (i = 1; i<=m_CDrain;i++) 
			{
				fscanf(db, "%d %d", &DrainMonth[i], &DrainDay[i]);
				fscanf(db, "%d %d %f", &DrainMonth2[i], &DrainDay2[i],&CDrainDepth[i]);
			}
			fclose(db);
		}
		i=1;
		m_CDrainA = CDrainA[i];
		m_DrainMonth = DrainMonth[i];
		m_DrainDay = DrainDay[i];
		m_CDrainDepth =CDrainDepth[i];
		m_DrainMonth2 = DrainMonth2[i];
		m_DrainDay2 = DrainDay2[i];
	//	m_TileIrriDays = TileIrriDays[i];

		UpdateData(FALSE);
	demo();

/*//	int i,n;
	CString txt;

		//Irrigation setup
	//m_IrrList.DeleteAllItems();
    //n = cycle.get(rrr, yyy)->IrrNumber;
    if (m_IrrN >= 0) 
	{
		//m_IrrN = n;
		for (i = 1; i<=m_IrrN;i++) 
		{
			txt = OrderNumber(i,"Irr.",&txt);
			m_IrrList.InsertItem(i-1,txt);

			txt.Format("%d",IrriMonth[i]);
			m_IrrList.SetItemText(i-1,1,txt);

			txt.Format("%d",IrriDay[i]);
			m_IrrList.SetItemText(i-1,2,txt);

			txt.Format("%9.2f",IrriAmount[i]);
			m_IrrList.SetItemText(i-1,3,txt);

			txt.Format("%9.2f",IrriPH[i]);
			m_IrrList.SetItemText(i-1,4,txt);
		}
	}
	//else m_IrrN = 0;
*/
/*        
	int i,n;
	char ch[20];

    m_IrrGrid.SetRows(1);
    m_IrrGrid.SetCols(5);
    m_IrrGrid.SetRow(0);
    m_IrrGrid.SetCol(1);
    m_IrrGrid.SetText("Month");
    m_IrrGrid.SetCol(2);
    m_IrrGrid.SetText("Day");
    m_IrrGrid.SetCol(3);
    m_IrrGrid.SetText("Water Amount");
    m_IrrGrid.SetCol(4);
    m_IrrGrid.SetText("Water pH");*/
	
        // Irrigation parameter
/*	float zzz=cycle.get(rrr, yyy)->IrrIndex;

	if(zzz>0.0) m_IrrMode = 1;
	else m_IrrMode = 0;
*/
	//m_IrrMode=cycle.get(rrr, yyy)->IrrMode-1;
	//if (m_IrrMode<0 || m_IrrMode>1) m_IrrMode=0;

	
	
	UpdateData(FALSE);

/*	n=cycle.get(rrr, yyy)->IrrNumber;
    if (n >= 0) 
	{
		m_IrrN=n;
		m_IrrGrid.SetRows(n+1);
		for (i = 1;i<=n;i++) {
			m_IrrGrid.SetRow(i);
			m_IrrGrid.SetCol(0);
			sprintf(ch,"%d",i);
			m_IrrGrid.SetText(ch);

			m_IrrGrid.SetCol(1);
			sprintf(ch,"%d",irrigation.get(rrr, yyy, i)->month);
			m_IrrGrid.SetText(ch);
			m_IrrGrid.SetCol(2);
			sprintf(ch,"%d",irrigation.get(rrr, yyy, i)->day);
			m_IrrGrid.SetText(ch);
			m_IrrGrid.SetCol(3);
			sprintf(ch,"%9.3f",irrigation.get(rrr, yyy, i)->Water);
			m_IrrGrid.SetText(ch);
			m_IrrGrid.SetCol(4);
			sprintf(ch,"%9.4f",irrigation.get(rrr, yyy, i)->WaterpH);
			m_IrrGrid.SetText(ch);
		}
    }*/
	//UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

BEGIN_EVENTSINK_MAP(SitePage10, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage10)
	//ON_EVENT(SitePage10, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void SitePage10::OnIrrOption0() 
{
	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);

	m_IrrN = 0;
	m_IrrID = 0;
	m_IrrAmount = 0.0;
	m_IrrMonth = 0;
	m_IrrDay = 0;
	m_IrrpH = 0.0;
	m_TileIrriDays=0;

	UpdateData(FALSE);

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_irrigationN);
	Edt->EnableWindow(FALSE); 
	Edt=(CEdit *)GetDlgItem(IDC_IrrIndex);
	Edt->EnableWindow(TRUE); 

	Edt=(CEdit *)GetDlgItem(IDC_irrigationID);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationAmount);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationMonth);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationDay);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationpH);
	Edt->EnableWindow(FALSE);
	
	//="Irrigation index (0-1.0) =";
/*	cycle.get(rrr, yyy)->IrrMode  = m_IrrMode+1;
	cycle.get(rrr, yyy)->IrrIndex = (float)m_IrrIndex;*/
	/*cycle.get(rrr, yyy)->IrrNumber= 0;
	int n = m_IrrList.GetItemCount();
	ResetListItem(0,n,"Irr.",&m_IrrList);*/
	UpdateData(FALSE);
}

void SitePage10::OnIrrOption1() 
{
	UpdateData(TRUE);

		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT10);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);
    
	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_irrigationN);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_IrrIndex);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationID);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationAmount);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationMonth);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationDay);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_irrigationpH);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_WT);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_TileIrriDays);
	Edt->EnableWindow(TRUE);	
	m_IrrIndex = 0;	

	m_IrrMode = 0;
	
	UpdateData(FALSE);
}


void SitePage10::OnKillfocusirrigationN() 
{

}



void SitePage10::OnKillfocusirrigationID() // Set default values
{


}

void SitePage10::OnIrrAccept() 
{
	UpdateData(TRUE);

	int i,j;
	i=m_IrrID;		
		IrriMonth[i]=m_IrrMonth;
		IrriDay[i]=m_IrrDay;
		IrriAmount[i]=m_IrrAmount;
		IrriMethod[i]=m_IrriMethod;
        TileIrriDays[i]=m_TileIrriDays;
	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT10);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	DB.Format("%s\\CropIrri_%d_%d.txt", FCT10, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d %d %f %d\n", m_IrrN, m_IrrMode, m_IrrIndex, IrriMethod[0]);

	for (i = 1; i<=m_IrrN;i++) 
	{
		fprintf(db, "%d %d\n", IrriMonth[i], IrriDay[i]);
		fprintf(db, "%f %d %d\n", IrriAmount[i], IrriMethod[i], TileIrriDays[i]);
	}
	fclose(db);

	j=m_CDrainA;
	DrainMonth[j]=m_DrainMonth;
	DrainDay[j]=m_DrainDay;
	DrainMonth2[j]=m_DrainMonth2;
	DrainDay2[j]=m_DrainDay2;
	CDrainDepth[j]=m_CDrainDepth;

//adding control drainage outputs

		DB.Format("%s\\CTDrain_%d_%d.txt", FCT10, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d\n", m_CDrain);

	for (i = 1; i<=m_CDrain;i++) 
	{
		fprintf(db, "%d %d\n", DrainMonth[i], DrainDay[i]);
		fprintf(db, "%d %d %f\n", DrainMonth2[i], DrainDay2[i], CDrainDepth[i]);
	}
	fclose(db);




	demo();

	
	
/*	cycle.get(rrr, yyy)->IrrIndex = (float)m_IrrIndex;

	if (!CheckIrrID()) return;

	if (m_IrrN != cycle.get(rrr, yyy)->IrrNumber) 
	{
		MessageBox("Total irrigation count is WRONG","Input Error:",NULL);
		return;
	}
	
	if (!IfMonth(m_IrrMonth)) return;
	sprintf(ch,"%d",m_IrrMonth);
    m_IrrList.SetItemText(m_IrrID-1,1,ch);
	irrigation.get(rrr, yyy,m_IrrID)->month =m_IrrMonth;

	if (!IfDay(m_IrrDay)) return;
	sprintf(ch,"%d",m_IrrDay);
    m_IrrList.SetItemText(m_IrrID-1,2,ch);
	irrigation.get(rrr, yyy,m_IrrID)->day =m_IrrDay;

	sprintf(ch,"%9.2f",m_IrrAmount);
    m_IrrList.SetItemText(m_IrrID-1,3,ch);
	irrigation.get(rrr, yyy,m_IrrID)->Water =(float)m_IrrAmount;

	sprintf(ch,"%9.2f",m_IrrpH);
    m_IrrList.SetItemText(m_IrrID-1,4,ch);
	irrigation.get(rrr, yyy,m_IrrID)->WaterpH = (float)m_IrrpH;	
*/
    /*m_IrrGrid.SetRow(m_IrrID);
    m_IrrGrid.SetCol(1);
	if (!IfMonth(m_IrrMonth)) return;
	sprintf(ch,"%d",m_IrrMonth);
    m_IrrGrid.SetText(ch);
	irrigation.get(rrr, yyy,m_IrrID)->month =m_IrrMonth;

	if (!IfDay(m_IrrDay)) return;
    m_IrrGrid.SetCol(2);
	sprintf(ch,"%d",m_IrrDay);
    m_IrrGrid.SetText(ch);
	irrigation.get(rrr, yyy,m_IrrID)->day =m_IrrDay;

	m_IrrGrid.SetCol(3);
	sprintf(ch,"%9.2f",m_IrrAmount);
    m_IrrGrid.SetText(ch);
	irrigation.get(rrr, yyy,m_IrrID)->Water =(float)m_IrrAmount;

    m_IrrGrid.SetCol(4);
	sprintf(ch,"%9.3f",m_IrrpH);
    m_IrrGrid.SetText(ch);
	irrigation.get(rrr, yyy,m_IrrID)->WaterpH = (float)m_IrrpH;*/
}

void SitePage10::OnIrrLast() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_IrrID;		
		IrriMonth[i]=m_IrrMonth;
		IrriDay[i]=m_IrrDay;
		IrriAmount[i]=m_IrrAmount;
		IrriMethod[i]=m_IrriMethod;
		TileIrriDays[i]=m_TileIrriDays;

	if (m_IrrN==0) return;
	if (m_IrrID>1) m_IrrID--;
	else if (m_IrrID==0) m_IrrID=1;

	i=m_IrrID;		
		m_IrrMonth=IrriMonth[i];
		m_IrrDay=IrriDay[i];
		m_IrrAmount=IrriAmount[i];
		m_IrriMethod=IrriMethod[i];
		m_TileIrriDays=TileIrriDays[i];

	UpdateData(FALSE);
	//OnKillfocusirrigationID();
	
}

void SitePage10::OnIrrNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_IrrID;		
		IrriMonth[i]=m_IrrMonth;
		IrriDay[i]=m_IrrDay;
		IrriAmount[i]=m_IrrAmount;
		IrriMethod[i]=m_IrriMethod;
		TileIrriDays[i]=m_TileIrriDays;

	if (m_IrrN==0) return;
	if (m_IrrID<m_IrrN) m_IrrID++;
	else if (m_IrrID==0) m_IrrID=1;

	i=m_IrrID;		
		m_IrrMonth=IrriMonth[i];
		m_IrrDay=IrriDay[i];
		m_IrrAmount=IrriAmount[i];
		m_IrriMethod=IrriMethod[i];
		m_TileIrriDays=TileIrriDays[i];
	UpdateData(FALSE);
	//OnKillfocusirrigationID();
	
}

void SitePage10::OnDrLast() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);

	int i;
	i=m_CDrainA;		
	DrainMonth[i]=m_DrainMonth;
	DrainDay[i]=m_DrainDay;
	DrainMonth2[i]=m_DrainMonth2;
	DrainDay2[i]=m_DrainDay2;
	CDrainDepth[i]=m_CDrainDepth;

	if (m_CDrain==0) return;
	if (m_CDrainA>1) m_CDrainA--;
	else if (m_CDrainA==0) m_CDrainA=1;

	i=m_CDrainA;		
	m_DrainMonth=DrainMonth[i];
	m_DrainDay=DrainDay[i];
	m_DrainMonth2=DrainMonth2[i];
	m_DrainDay2=DrainDay2[i];
	m_CDrainDepth = CDrainDepth[i];

	UpdateData(FALSE);
}

void SitePage10::OnDrNext() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_CDrainA;		
	DrainMonth[i]=m_DrainMonth;
	DrainDay[i]=m_DrainDay;
	DrainMonth2[i]=m_DrainMonth2;
	DrainDay2[i]=m_DrainDay2;
	CDrainDepth[i]=m_CDrainDepth;
		
	if (m_CDrain==0) return;
	if (m_CDrainA<m_CDrain) m_CDrainA++;
	else if (m_CDrainA==0) m_CDrainA=1;

	i=m_CDrainA;		
	m_DrainMonth=DrainMonth[i];
	m_DrainDay=DrainDay[i];
	m_DrainMonth2=DrainMonth2[i];
	m_DrainDay2=DrainDay2[i];
	m_CDrainDepth = CDrainDepth[i];

	UpdateData(FALSE);	
}


void SitePage10::OnChangeIrrIndex() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
/*	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);
	//if (m_IrrMode==1) 
	cycle.get(rrr,yyy)->IrrIndex=(float)m_IrrIndex;*/
}

void SitePage10::OnKillfocusirrigationMonth() 
{
	UpdateData(TRUE);	
}

void SitePage10::OnKillfocusirrigationDay() 
{
	UpdateData(TRUE);	
}

void SitePage10::OnKillfocusirrigationAmount() 
{
	UpdateData(TRUE);	
}

void SitePage10::OnKillfocusirrigationpH() 
{
	UpdateData(TRUE);	
}

/*void SitePage10::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i = m_IrrList.GetSelectionMark()+1;
    if (i > 0) 
	{
		m_IrrID=i;
		UpdateData(FALSE);
		OnKillfocusirrigationID();
	}
	
	*pResult = 0;
}*/

BOOL SitePage10::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	int i;
	char *title[]={"Irr.ID","Month","Day","Water-cm","Method","TIrriDays"};
	int  ItemNum=6;
	for (i=0;i<ItemNum;i++)
	{
		m_IrrList.InsertColumn(i,title[i],LVCFMT_CENTER,65,-1);
	
	}
	
//	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

	int j;
	char *title1[]={"ID","StMonth","StDay","EndMonth","EndDay","CDepth"};
	int  ItemNum1=6;
	
	for (j=0;j<ItemNum1;j++)
	{
		m_DrainList.InsertColumn(j,title1[j],LVCFMT_CENTER,65,-1);
	}
	
//	return TRUE;  // return TRUE unless you set the focus to a control
	 return TRUE;             // EXCEPTION: OCX Property Pages should return FALSE



}

void SitePage10::demo() 
{
	int i;
	CString txt;

	m_IrrList.DeleteAllItems();
    if (m_IrrN >= 0) 
	{
		for (i = 1; i<=m_IrrN;i++) 
		{
			txt = OrderNumber(i,"Irr.",&txt);
			m_IrrList.InsertItem(i-1,txt);

			txt.Format("%d",IrriMonth[i]);
			m_IrrList.SetItemText(i-1,1,txt);

			txt.Format("%d",IrriDay[i]);
			m_IrrList.SetItemText(i-1,2,txt);

			txt.Format("%9.2f",IrriAmount[i]);
			m_IrrList.SetItemText(i-1,3,txt);

			txt.Format("%d",IrriMethod[i]);
			m_IrrList.SetItemText(i-1,4,txt);

			txt.Format("%d",TileIrriDays[i]);
			m_IrrList.SetItemText(i-1,5,txt);
		}
	}


//Controlled Drainage List

	m_DrainList.DeleteAllItems();
	CString txt1;
    if (m_CDrain >= 0) 
	{
		if (m_CDrain==0) 
		{
			txt = OrderNumber(1,"cDrain",&txt1);
			m_DrainList.InsertItem(0,txt);

			txt.Format("%d",0);
			m_DrainList.SetItemText(0,1,txt);

			txt.Format("%d",0);
			m_DrainList.SetItemText(0,2,txt);

			txt.Format("%d",0);
			m_DrainList.SetItemText(0,3,txt);

			txt.Format("%d",0);
			m_DrainList.SetItemText(0,4,txt);

			txt.Format("%f",0.0);
			m_DrainList.SetItemText(0,5,txt);
		}
		else
		{
		for (i = 1; i<=m_CDrain;i++) //not sure if it m_CDrain
		{
			txt = OrderNumber(i,"cDrain",&txt);
			m_DrainList.InsertItem(i-1,txt);

			txt.Format("%d",DrainMonth[i]);
			m_DrainList.SetItemText(i-1,1,txt);

			txt.Format("%d",DrainDay[i]);
			m_DrainList.SetItemText(i-1,2,txt);

			txt.Format("%d",DrainMonth2[i]);
			m_DrainList.SetItemText(i-1,3,txt);

			txt.Format("%d",DrainDay2[i]);
			m_DrainList.SetItemText(i-1,4,txt);

			txt.Format("%f",CDrainDepth[i]);
			m_DrainList.SetItemText(i-1,5,txt);
		}
		}
	}





}
