// SitePage9.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage9.h"
#include "SitePSheet.h"
#include "dndc_main.h"
//#include "SelectObsWT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CropArray			Crop;
extern Site_BaseInformation	IData ;
extern StringArray			WTFilename;
extern CropofEachYear CYr[2];
extern char *soiltexture[];
extern char *soillanduse[];
//extern StringArray			WT_file_name;

CString FCT9;
/////////////////////////////////////////////////////////////////////////////
// SitePage9 property page

IMPLEMENT_DYNCREATE(SitePage9, CPropertyPage)

SitePage9::SitePage9() : CPropertyPage(SitePage9::IDD)
{
	//{{AFX_DATA_INIT(SitePage9)
	m_FloodWaterN = 0.0f;
	m_FloodDDay = 0;
	m_FloodDMonth = 0;
	m_FloodFDay = 0;
	m_FloodFMonth = 0;
	m_FloodID = 0;
	m_FloodN = 0;
	m_WaterControl = 0;
	m_ShallowFlood = -1;
	m_WaterGetherIndex = 2.5f;
	m_WaterLeakRate = 0.0f;
	m_Vascularity = 0.0f;
	m_IniWT = 0.0f;
	m_LWTceasingSurfFlow = 0.0f;
	m_LWTceasingGroungFlow = 0.0f;
	m_WatershedIndex = 0.0f;
	m_SurfOutflowIntensity = 0.0f;
	m_GroundOutflowIntensity = 0.0f;
	//}}AFX_DATA_INIT
}

SitePage9::~SitePage9()
{
	
}

void SitePage9::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage9)
	DDX_Control(pDX, IDC_WTFileList, m_WTFileList);
	DDX_Control(pDX, IDC_FdLeak, m_FdLeak);
	DDX_Control(pDX, IDC_LIST1, m_FloodList);
	DDX_Text(pDX, IDC_FloodWaterpH, m_FloodWaterN);
	DDX_Text(pDX, IDC_floodDDay, m_FloodDDay);
	DDX_Text(pDX, IDC_floodDMonth, m_FloodDMonth);
	DDX_Text(pDX, IDC_floodFDay, m_FloodFDay);
	DDX_Text(pDX, IDC_floodFMonth, m_FloodFMonth);
	DDX_Text(pDX, IDC_floodID, m_FloodID);
	DDX_Text(pDX, IDC_floodN, m_FloodN);
	DDX_Radio(pDX, IDC_WaterControl, m_WaterControl);
	DDX_Radio(pDX, IDC_ShallowFlood, m_ShallowFlood);
	DDX_Text(pDX, IDC_WaterGetherIndex, m_WaterGetherIndex);
	DDX_Text(pDX, IDC_WaterLeakRate, m_WaterLeakRate);
	DDX_Text(pDX, IDC_Vascularity, m_Vascularity);
	DDX_Text(pDX, IDC_IniWT, m_IniWT);
	DDX_Text(pDX, IDC_WTSurfaceOutflow, m_LWTceasingSurfFlow);
	DDX_Text(pDX, IDC_WTGroundOutflow, m_LWTceasingGroungFlow);
	DDX_Text(pDX, IDC_SurfaceInflowFraction, m_WatershedIndex);
	DDX_Text(pDX, IDC_SurfaceOutflowIntensity, m_SurfOutflowIntensity);
	DDX_Text(pDX, IDC_GoundOutflowIntensity, m_GroundOutflowIntensity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage9, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage9)
	ON_EN_KILLFOCUS(IDC_floodN, OnKillfocusfloodN)
	ON_BN_CLICKED(IDC_FloodAccept, OnFloodAccept)
	ON_BN_CLICKED(IDC_FloodNext, OnFloodNext)
	ON_BN_CLICKED(IDC_FloodLast, OnFloodLast)
	ON_EN_KILLFOCUS(IDC_floodFMonth, OnKillfocusfloodFMonth)
	ON_EN_KILLFOCUS(IDC_floodFDay, OnKillfocusfloodFDay)
	ON_EN_KILLFOCUS(IDC_floodDMonth, OnKillfocusfloodDMonth)
	ON_EN_KILLFOCUS(IDC_floodDDay, OnKillfocusfloodDDay)
	ON_EN_KILLFOCUS(IDC_FloodWaterpH, OnKillfocusFloodWaterpH)
	ON_BN_CLICKED(IDC_WaterControl, OnWaterControl)
	ON_BN_CLICKED(IDC_Rainfed, OnRainfed)
	ON_BN_CLICKED(IDC_ObservedWT, OnObservedWT)
	ON_BN_CLICKED(IDC_selectWTfile, OnselectWTfile)
	ON_LBN_DBLCLK(IDC_WTFileList, OnDblclkWTFileList)
	ON_BN_CLICKED(IDC_EmpiricalPara, OnEmpiricalPara)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage9 message handlers

BOOL SitePage9::OnSetActive() 
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
	FCT9.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	FCT9.Format("%s_1", INTERMANAGE);
#endif

	int rrr, yyy, i, WaterControl=0;
	float WaterGetherIndex, WaterLeakRate, FloodWaterN;

	WaterGetherIndex=1.0;
	WaterLeakRate=0.0;
	FloodWaterN=0.0;
	
	CEdit *Edt;
	if(IData.Soil_landuse==2||IData.Soil_landuse==5)
	{		
		Edt=(CEdit *)GetDlgItem(IDC_WaterControl);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_Rainfed);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_ObservedWT);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_IniWT);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_WTSurfaceOutflow);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_WTGroundOutflow);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_SurfaceInflowFraction);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_SurfaceOutflowIntensity);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_GoundOutflowIntensity);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_EmpiricalPara);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		/*Edt=(CEdit *)GetDlgItem(IDC_WaterControl);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_Rainfed);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_ObservedWT);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_EmpiricalPara);
		Edt->EnableWindow(FALSE);	*/
		
		Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_IniWT);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_WTSurfaceOutflow);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_WTGroundOutflow);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SurfaceInflowFraction);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_SurfaceOutflowIntensity);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_GoundOutflowIntensity);
		Edt->EnableWindow(FALSE);
			

		WaterControl=0;
	}

	WT_file.Format("");
	//m_FdLeak.SetCurSel(1);
	//leak=1;

	for(i=0; i<=290; i++)
	{
		FlooID[i]=0; FlooMonth1[i]=0; FlooDay1[i]=0; FlooMonth2[i]=0; FlooDay2[i]=0;
		FlooN[i]=0.0; ShallowFlood[i]=0;
	}
	
	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT9);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//DB.Format("%s\\inter\\CropFloo_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropFloo_%d_%d.txt", FCT9, rrr, yyy);
	
	db=fopen(DB, "r");
	fscanf(db, "%d %f %d %f", &m_FloodN, &FloodWaterN, &WaterControl, &WaterLeakRate);

	if(WaterControl==2) m_FloodWaterN = FloodWaterN;
		
	if(m_FloodN==0)
	{
		for(i=1; i<=20; i++)
			{
				FlooID[i] = i;
				FlooMonth1[i]=0;
				FlooDay1[i]=0;
				FlooMonth2[i]=0;
				FlooDay2[i]=0;
				FlooN[i]=0.0;
				ShallowFlood[i]=0;
			}
	}
	else
	{
		for(i=1; i<=m_FloodN; i++)
			{
				FlooID[i] = i;
				fscanf(db, "%d %d", &FlooMonth1[i], &FlooDay1[i]);
				fscanf(db, "%d %d", &FlooMonth2[i], &FlooDay2[i]);
				fscanf(db, "%f", &FlooN[i]);
				fscanf(db, "%d", &ShallowFlood[i]);
			}	
	}

	//if(WaterControl==1)
	//{
		fscanf(db, "%f", &WaterGetherIndex);	
	//}
	
	//if(WaterControl==2)
	//{
		fscanf(db, "%s", WT_file);
		m_WTFileList.InsertString(0, WT_file);

	//}
	fscanf(db, "%f %f %f %f %f %f", &m_IniWT, &m_LWTceasingSurfFlow, &m_LWTceasingGroungFlow, &m_WatershedIndex, 
		&m_SurfOutflowIntensity, &m_GroundOutflowIntensity);

	fclose(db);
	
		i=1;
		m_FloodID = FlooID[i];
		m_FloodFDay = FlooDay1[i];
		m_FloodFMonth = FlooMonth1[i];
		m_FloodDMonth = FlooMonth2[i];
		m_FloodDDay = FlooDay2[i];	
		m_FloodWaterN = FlooN[i];	
		//m_FdLeak.SetCurSel(leak);
		m_ShallowFlood = ShallowFlood[i];
		m_WaterControl = WaterControl;
		m_WaterGetherIndex = WaterGetherIndex;
		m_WaterLeakRate = WaterLeakRate;
		//m_FloodWaterN = FloodWaterN;
		//m_Vascularity = Vascularity;

	demo();

	UpdateData(FALSE);	

	if(WaterControl==0)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_floodN);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_floodDMonth);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_floodDDay);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_floodFMonth);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_floodFDay);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_floodID);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood2);
		Edt->EnableWindow(TRUE);
		
		Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_WaterGetherIndex);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_Vascularity);
		Edt->EnableWindow(FALSE);
		//Edt=(CEdit *)GetDlgItem(IDC_WaterLeakRate);
		//Edt->EnableWindow(FALSE);
	}

	if(WaterControl==1) OnRainfed();

	if(WaterControl==2) OnObservedWT();

/*//	int i,n;
	CString txt;

	//m_FloodList.DeleteAllItems();
    //n = cycle.get(rrr, yyy)->FloodNumber;
    if (m_FloodN >= 0) 
	{
		//m_FloodN = n;
		for (i = 1; i<=m_FloodN;i++) 
		{
			txt = OrderNumber(i,"flood",&txt);
			m_FloodList.InsertItem(i-1,txt);

			txt.Format("%d",FlooMonth1[i]);
			m_FloodList.SetItemText(i-1,1,txt);

			txt.Format("%d",FlooDay1[i]);
			m_FloodList.SetItemText(i-1,2,txt);

			txt.Format("%d",FlooMonth2[i]);
			m_FloodList.SetItemText(i-1,3,txt);

			txt.Format("%d",FlooDay2[i]);
			m_FloodList.SetItemText(i-1,4,txt);

			txt.Format("%d",FlooPH[i]);
			m_FloodList.SetItemText(i-1,5,txt);
		}
		//n = cycle.get(rrr, yyy)->Leak - 1;
		//if (n < 0 || n > 2) n = 2;
		//m_FdLeak = n;
	}

*/

/*    m_FloodGrid.SetRows(1);
    m_FloodGrid.SetCols(5);
    m_FloodGrid.SetRow(0);
    m_FloodGrid.SetCol(1);
    m_FloodGrid.SetText("Flood M.");
    m_FloodGrid.SetCol(2);
    m_FloodGrid.SetText("Flood D.");
    m_FloodGrid.SetCol(3);
    m_FloodGrid.SetText("Drain M.");
    m_FloodGrid.SetCol(4);
    m_FloodGrid.SetText("Drain D.");

        // Flood parameter
	int i,n;
	char ch[20];
    n = cycle.get(rrr, yyy)->FloodNumber;
    if (n >= 0) {
		//floodtxt(0) = n
		m_FloodN=n;
		m_FloodGrid.SetRows(n+1);
		for (i = 1;i<=n;i++) {
			m_FloodGrid.SetRow(i);
			m_FloodGrid.SetCol(0);
			sprintf(ch,"%dth",i);
			m_FloodGrid.SetText(ch);

			m_FloodGrid.SetCol(1);
			sprintf(ch,"%d",flood.get(rrr, yyy, i)->Fmonth);
			m_FloodGrid.SetText(ch);
			m_FloodGrid.SetCol(2);
			sprintf(ch,"%d",flood.get(rrr, yyy, i)->Fday);
			m_FloodGrid.SetText(ch);
			m_FloodGrid.SetCol(3);
			sprintf(ch,"%d",flood.get(rrr, yyy, i)->Dmonth);
			m_FloodGrid.SetText(ch);
			m_FloodGrid.SetCol(4);
			sprintf(ch,"%d",flood.get(rrr, yyy, i)->Dday);
			m_FloodGrid.SetText(ch);
		}
		n = cycle.get(rrr, yyy)->Leak - 1;
		if (n < 0 || n > 2) n = 2;
		m_FdLeak=n;
	}*/

	
	return CPropertyPage::OnSetActive();
}

BEGIN_EVENTSINK_MAP(SitePage9, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage9)
	//ON_EVENT(SitePage9, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL SitePage9::CheckFloodN()
{
		
/*	CString DB;
	FILE *db;
	DB.Format("%s\\Result\\inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

   if (m_FloodN < 0) {
		MessageBox("Flood number must be >=0", "Input Error:",NULL);
		m_FloodN =0;
		UpdateData(FALSE);
		return FALSE;
	}
	else if (m_FloodN ==0) {
		cycle.get(rrr,yyy)->FloodNumber=0;
		cycle.get(rrr,yyy)->Leak = 2;
		m_FdLeak=1;
		UpdateData(FALSE);
		return FALSE;
	}*/
	return TRUE;
}

void SitePage9::OnKillfocusfloodN() 
{
/*	UpdateData(TRUE);
	CheckFloodN();

	int n = m_FloodList.GetItemCount();
	ResetListItem(m_FloodN,n,"flood",&m_FloodList);
*/

/* 	char ch[20];
	int i;

    m_FloodGrid.SetRows(m_FloodN+1);
	m_FloodGrid.SetCol(0);
    for (i = 1;i<=m_FloodN;i++) {
		m_FloodGrid.SetRow(i);
		sprintf(ch,"%dth",i);
		m_FloodGrid.SetText(ch);
	}*/
     
    //SetArrayRange(6, m_FloodN);

}

BOOL SitePage9::CheckFloodID()
{
	if (!CheckFloodN()) return FALSE;
	if (m_FloodID ==0 ) return FALSE;
	if (m_FloodID <=0 || m_FloodID> m_FloodN) {
        MessageBox("The Flood ID number should be in 0~total number!", "Input Error:",NULL);
		m_FloodID = m_FloodN;
		UpdateData(FALSE);
		return FALSE;
	}
	return TRUE;
}

/*void SitePage9::OnKillfocusfloodID() // Set default values
{
		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Result\\inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);
	if (!CheckFloodID()) return;

	FloodParameter *FPnt;
	FPnt = flood.get(rrr, yyy,m_FloodID);

	if (FPnt->Fmonth<=0) return;
	m_FloodFMonth = FPnt->Fmonth;
	m_FloodFDay   = FPnt->Fday;
	m_FloodDMonth = FPnt->Dmonth;
	m_FloodDDay   = FPnt->Dday;
	m_FloodWaterN = FPnt->FloodPH;


	char  ch[20];
	int   i,id;
	
	m_FloodGrid.SetRow(m_FloodID); 
	for (i=1;i<=4;i++) {
		m_FloodGrid.SetCol(i);
		strcpy(ch,m_FloodGrid.GetText());
		if (strlen(ch)==0) id=0;
		else sscanf(ch,"%d",&id);
		if (id<0) id=0;

		if (i==1)      m_FloodFMonth=id;
		else if (i==2) m_FloodFDay  =id;
		else if (i==3) m_FloodDMonth=id;
		else if (i==4) m_FloodDDay  =id;
	}
	UpdateData(FALSE);
}*/

/*void SitePage9::OnClickMsflexgrid1() 
{
	// TODO: Add your control notification handler code here
    /*int i;
    i = m_FloodGrid.GetRow();
    if (i > 0) {
		m_FloodID=i;
		UpdateData(FALSE);
		OnKillfocusfloodID();
	}*
	
}*/

void SitePage9::OnFloodAccept() 
{
	int i, rrr, yyy, WaterControl=0;
			
	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT9);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);

	int ii,num;
	CString WWww="None";
		
	//num=m_WTFileList.GetCount();
	//ii=m_WTFileList.GetCurSel();
	
	//m_WTFileList.GetText(0,WWww);
	ii=m_WTFileList.GetCurSel();
	
	if(m_WaterControl>=0&&m_WaterControl<=3) {}
	else m_WaterControl = 0;

	WaterControl = m_WaterControl;
	//0 - irrigation; 1 - rainfed; 2 - observed data; 3 - empirical parameters

	if(WaterControl!=0)
	{
		m_FloodID=0;
		m_FloodFMonth=0;
		m_FloodFDay=0;
		m_FloodDMonth=0;
		m_FloodDDay=0;
		m_ShallowFlood=0;
		//m_FloodWaterN=0.0;
	}

	i=m_FloodID;		
	FlooMonth1[i]=m_FloodFMonth;
	FlooDay1[i]=m_FloodFDay;
	FlooMonth2[i]=m_FloodDMonth;
	FlooDay2[i]=m_FloodDDay;
	FlooN[i]=m_FloodWaterN;
	ShallowFlood[i] = m_ShallowFlood;

	//leak = m_FdLeak.GetCurSel();
	
	
	//DB.Format("%s\\inter\\CropFloo_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropFloo_%d_%d.txt", FCT9, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d %f %d %f\n", m_FloodN, m_FloodWaterN, WaterControl, m_WaterLeakRate);

	for (i = 1; i<=m_FloodN;i++) 
	{
		fprintf(db, "%d %d\n", FlooMonth1[i], FlooDay1[i]);
		fprintf(db, "%d %d\n", FlooMonth2[i], FlooDay2[i]);
		fprintf(db, "%f\n", FlooN[i]);
		fprintf(db, "%d\n", ShallowFlood[i]);
	}

	//if(m_WaterControl==2)
	//	fprintf(db, "%f\n", m_FloodWaterN);
	//else
	fprintf(db, "%f\n", m_WaterGetherIndex);
	
	
	char st[200], fname[200];
	num=1;
	WTFilename.clear ();
	for (i=1;i<=num;i++) {
		m_WTFileList.GetText(i-1,fname);
		strcpy(st,fname);
		WTFilename.insert(i,st);
	}

/*	if(WaterControl==2)
	{
		FILE *Fland;
		CString f_land;

		f_land.Format("%s\\Result\\Inter\\WTfile_%d_%d", rrr, yyy);
		Fland = fopen(f_land, "r");

		if(Fland==NULL)
		{
			CString note;
			note.Format("Can not find file %s", f_land);
			AfxMessageBox(note);
			exit(0);
		}	
		fscanf(Fland, "%s", WW_file_name);
		fclose (Fland);		
	}
	else
		sprintf(WT_file_name, "None");*/

	fprintf(db, "%s\n", st);
	
	fprintf(db, "%f %f %f %f %f %f\n", m_IniWT, m_LWTceasingSurfFlow, m_LWTceasingGroungFlow, m_WatershedIndex, 
		m_SurfOutflowIntensity, m_GroundOutflowIntensity);
	
	fclose(db);

	demo();

/*	char ch[20];
	if (!CheckFloodID()) return;

	if (m_FloodN != cycle.get(rrr, yyy)->FloodNumber) 
	{
		MessageBox("Total flood count is WRONG","Input Error:",NULL);
		return;
	}

	if (!IfMonth(m_FloodFMonth)) return;
	sprintf(ch,"%d",m_FloodFMonth);
	m_FloodList.SetItemText(m_FloodID-1,1,ch);
	flood.get(rrr, yyy, m_FloodID)->Fmonth =m_FloodFMonth;
	
    if (!IfDay(m_FloodFDay)) return;
	sprintf(ch,"%d",m_FloodFDay);
    m_FloodList.SetItemText(m_FloodID-1,2,ch);
	flood.get(rrr, yyy, m_FloodID)->Fday =m_FloodFDay;

    if (!IfMonth(m_FloodDMonth)) return;
	sprintf(ch,"%d",m_FloodDMonth);
    m_FloodList.SetItemText(m_FloodID-1,3,ch);
	flood.get(rrr, yyy, m_FloodID)->Dmonth  =m_FloodDMonth;

    if (!IfDay(m_FloodDDay)) return;
	sprintf(ch,"%d",m_FloodDDay);
    m_FloodList.SetItemText(m_FloodID-1,4,ch);
	flood.get(rrr, yyy, m_FloodID)->Dday =m_FloodDDay;	

	if (!IfDay(m_FloodWaterpH)) return;
	sprintf(ch,"%f",m_FloodWaterpH);
    m_FloodList.SetItemText(m_FloodID-1,5,ch);
	flood.get(rrr, yyy, m_FloodID)->FloodPH =m_FloodWaterpH;
*/
		
/*
    m_FloodGrid.SetRow(m_FloodID);
    m_FloodGrid.SetCol(1);
	if (!IfMonth(m_FloodFMonth)) return;
	sprintf(ch,"%d",m_FloodFMonth);
    m_FloodGrid.SetText(ch);
	flood.get(rrr, yyy, m_FloodID)->Fmonth =m_FloodFMonth;

    if (!IfDay(m_FloodFDay)) return;
	m_FloodGrid.SetCol(2);
	sprintf(ch,"%d",m_FloodFDay);
    m_FloodGrid.SetText(ch);
	flood.get(rrr, yyy, m_FloodID)->Fday =m_FloodFDay;

    if (!IfMonth(m_FloodDMonth)) return;
	m_FloodGrid.SetCol(3);
	sprintf(ch,"%d",m_FloodDMonth);
    m_FloodGrid.SetText(ch);
	flood.get(rrr, yyy, m_FloodID)->Dmonth  =m_FloodDMonth;

    if (!IfDay(m_FloodDDay)) return;
	m_FloodGrid.SetCol(4);
	sprintf(ch,"%d",m_FloodDDay);
    m_FloodGrid.SetText(ch);
	flood.get(rrr, yyy, m_FloodID)->Dday =m_FloodDDay;*/
}

void SitePage9::OnFloodNext() 
{
	UpdateData(TRUE);

	int i;
	i=m_FloodID;		
		FlooMonth1[i]=m_FloodFMonth;
		FlooDay1[i]=m_FloodFDay;
		FlooMonth2[i]=m_FloodDMonth;
		FlooDay2[i]=m_FloodDDay;
		FlooN[i]=m_FloodWaterN;
		ShallowFlood[i] = m_ShallowFlood;
		
	if (m_FloodN==0) return;
	if (m_FloodID<m_FloodN) m_FloodID++;
	else if (m_FloodID==0) m_FloodID=1;

	i=m_FloodID;
		//m_FloodID = FlooID[i];
		m_FloodFDay = FlooDay1[i];
		m_FloodFMonth = FlooMonth1[i];
		m_FloodDDay = FlooDay2[i];
		m_FloodDMonth = FlooMonth2[i];	
		m_FloodWaterN = FlooN[i];	
		m_ShallowFlood = ShallowFlood[i];

	UpdateData(FALSE);
	//OnKillfocusfloodID();
}

void SitePage9::OnFloodLast() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_FloodID;		
		FlooMonth1[i]=m_FloodFMonth;
		FlooDay1[i]=m_FloodFDay;
		FlooMonth2[i]=m_FloodDMonth;
		FlooDay2[i]=m_FloodDDay;
		FlooN[i]=m_FloodWaterN;
		ShallowFlood[i] = m_ShallowFlood;
		
	if (m_FloodN==0) return;
	if (m_FloodID>1) m_FloodID--;
	else if (m_FloodID==0) m_FloodID=1;

	i=m_FloodID;
		//m_FloodID = FlooID[i];
		m_FloodFDay = FlooDay1[i];
		m_FloodFMonth = FlooMonth1[i];
		m_FloodDDay = FlooDay2[i];
		m_FloodDMonth = FlooMonth2[i];	
		m_FloodWaterN = FlooN[i];
		m_ShallowFlood = ShallowFlood[i];

	UpdateData(FALSE);
	//OnKillfocusfloodID();
}

void SitePage9::OnKillfocusfloodFMonth() 
{
	UpdateData(TRUE);	
}

void SitePage9::OnKillfocusfloodFDay() 
{
	UpdateData(TRUE);	
}

void SitePage9::OnKillfocusfloodDMonth() 
{
	UpdateData(TRUE);	
}

void SitePage9::OnKillfocusfloodDDay() 
{
	UpdateData(TRUE);	
}

void SitePage9::OnKillfocusFloodWaterpH() 
{
	UpdateData(TRUE);	
}

BOOL SitePage9::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
		//Set Tillage parameter list
		//Set list column
	int i;
	char *title[]={"Flood ID","Flood-M","Flood-D","Drain-M","Drain-D"};
	int  ItemNum=5;
	for (i=0;i<ItemNum;i++)
	{
		m_FloodList.InsertColumn(i,title[i],LVCFMT_CENTER,65,-1);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*void SitePage9::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_FloodList.GetSelectionMark()+1;
    if (i > 0) 
	{
		m_FloodID=i;
		UpdateData(FALSE);
		//OnKillfocusfloodID();
	}
	
	*pResult = 0;
}*/

void SitePage9::demo() 
{
	int i;
	CString txt;

	m_FloodList.DeleteAllItems();
    if (m_FloodN >= 0) 
	{
		for (i = 1; i<=m_FloodN;i++) 
		{
			txt = OrderNumber(i,"flood",&txt);
			m_FloodList.InsertItem(i-1,txt);

			txt.Format("%d",FlooMonth1[i]);
			m_FloodList.SetItemText(i-1,1,txt);

			txt.Format("%d",FlooDay1[i]);
			m_FloodList.SetItemText(i-1,2,txt);

			txt.Format("%d",FlooMonth2[i]);
			m_FloodList.SetItemText(i-1,3,txt);

			txt.Format("%d",FlooDay2[i]);
			m_FloodList.SetItemText(i-1,4,txt);

			txt.Format("%d",FlooN[i]);
			m_FloodList.SetItemText(i-1,5,txt);
		}
		//n = cycle.get(rrr, yyy)->Leak - 1;
		//if (n < 0 || n > 2) n = 2;
		//m_FdLeak = n;
	}
}

void SitePage9::OnselectWTfile() 
{
	// TODO: Add your control notification handler code here
	int rrr, yyy;
	CString pre_WTFileName[5];
	CString f_site, cst;
	FILE *Fsite;

	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT9);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//Open a menu window
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();

	POSITION pos=ask.GetStartPosition();
	
	//Count number (num) of selected strings
	int k,num;
	num = m_WTFileList.GetCount();
		
	//Obtain order number (k) of each selected string
	k = m_WTFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		//Obtain a character from the string
		pre_WTFileName[num].Format("%s", ask.GetNextPathName(pos));
		if (pre_WTFileName[num]=="") break;

		f_site.Format("%s\\Inter\\WTfile_%d_%d", OUTPUT, rrr, yyy);
	
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

		//Add the character into pre_ClimateFileName[num]
		m_WTFileList.InsertString(k, pre_WTFileName[num]);

		if (cst.IsEmpty() || pos==NULL) 
		{
			
			break;
		}
		
		if (m_WTFileList.GetCount()==1) break;

		k++;
	}

	//Put the string on screen
	m_WTFileList.SetCurSel(k);
	
	UpdateData(FALSE);
	
	
}

void SitePage9::OnDblclkWTFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;
		
	num=m_WTFileList.GetCount();
	i=m_WTFileList.GetCurSel();
	
	CString fname;
	m_WTFileList.GetText(i,fname);
	m_WTFileList.DeleteString(i);	
	return;
}

void SitePage9::OnWaterControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	/*m_FloodN = 0;
	m_FloodWaterpH = 0.0f;
	m_FloodDDay = 0;
	m_FloodDMonth = 0;
	m_FloodFDay = 0;
	m_FloodFMonth = 0;
	m_FloodID = 0;
	m_ShallowFlood = FALSE;*/
	m_FloodWaterN = 0.0;

	m_IniWT = 0.0f;
	m_LWTceasingSurfFlow = 0.0f;
	m_LWTceasingGroungFlow = 0.0f;
	m_WatershedIndex = 0.0f;
	m_SurfOutflowIntensity = 0.0f;
	m_GroundOutflowIntensity = 0.0f;	

	UpdateData(FALSE);

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_floodN);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDMonth);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDDay);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFMonth);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFDay);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_floodID);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood2);
	Edt->EnableWindow(TRUE);
	
	Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WaterGetherIndex);
	Edt->EnableWindow(FALSE);
	//Edt=(CEdit *)GetDlgItem(IDC_Vascularity);
	//Edt->EnableWindow(FALSE);
	//Edt=(CEdit *)GetDlgItem(IDC_WaterLeakRate);
	//Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_IniWT);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTSurfaceOutflow);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTGroundOutflow);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceInflowFraction);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceOutflowIntensity);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_GoundOutflowIntensity);
	Edt->EnableWindow(FALSE);


}

void SitePage9::OnRainfed() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_FloodN = 0;
	m_FloodWaterN = 0.0f;
	m_FloodDDay = 0;
	m_FloodDMonth = 0;
	m_FloodFDay = 0;
	m_FloodFMonth = 0;
	m_FloodID = 0;
	m_ShallowFlood = FALSE;
	m_IniWT = 0.0f;
	m_LWTceasingSurfFlow = 0.0f;
	m_LWTceasingGroungFlow = 0.0f;
	m_WatershedIndex = 0.0f;
	m_SurfOutflowIntensity = 0.0f;
	m_GroundOutflowIntensity = 0.0f;
	m_IniWT = 0.0f;
	m_LWTceasingSurfFlow = 0.0f;
	m_LWTceasingGroungFlow = 0.0f;
	m_WatershedIndex = 0.0f;
	m_SurfOutflowIntensity = 0.0f;
	m_GroundOutflowIntensity = 0.0f;


	UpdateData(FALSE);

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_floodN);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDMonth);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDDay);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFMonth);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFDay);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodID);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood2);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WaterGetherIndex);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_WaterLeakRate);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_IniWT);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTSurfaceOutflow);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTGroundOutflow);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceInflowFraction);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceOutflowIntensity);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_GoundOutflowIntensity);
	Edt->EnableWindow(FALSE);

}

void SitePage9::OnObservedWT() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_FloodN = 0;
	//m_FloodWaterN = 0.0f;
	m_FloodDDay = 0;
	m_FloodDMonth = 0;
	m_FloodFDay = 0;
	m_FloodFMonth = 0;
	m_FloodID = 0;
	m_ShallowFlood = FALSE;
	m_IniWT = 0.0f;
	m_LWTceasingSurfFlow = 0.0f;
	m_LWTceasingGroungFlow = 0.0f;
	m_WatershedIndex = 0.0f;
	m_SurfOutflowIntensity = 0.0f;
	m_GroundOutflowIntensity = 0.0f;
	m_IniWT = 0.0f;
	m_LWTceasingSurfFlow = 0.0f;
	m_LWTceasingGroungFlow = 0.0f;
	m_WatershedIndex = 0.0f;
	m_SurfOutflowIntensity = 0.0f;
	m_GroundOutflowIntensity = 0.0f;

	UpdateData(FALSE);

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_floodN);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDMonth);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDDay);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFMonth);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFDay);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodID);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WaterGetherIndex);
	Edt->EnableWindow(FALSE);
	//Edt=(CEdit *)GetDlgItem(IDC_WaterLeakRate);
	//Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_IniWT);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTSurfaceOutflow);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTGroundOutflow);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceInflowFraction);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceOutflowIntensity);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_GoundOutflowIntensity);
	Edt->EnableWindow(FALSE);
	
}

void SitePage9::OnEmpiricalPara() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_FloodN = 0;
	m_FloodWaterN = 0.0f;
	m_FloodDDay = 0;
	m_FloodDMonth = 0;
	m_FloodFDay = 0;
	m_FloodFMonth = 0;
	m_FloodID = 0;
	m_ShallowFlood = FALSE;

	UpdateData(FALSE);

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_floodN);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDMonth);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodDDay);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFMonth);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodFDay);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_floodID);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_ShallowFlood2);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_selectWTfile);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WTFileList);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WaterGetherIndex);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_WaterLeakRate);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_IniWT);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_WTSurfaceOutflow);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_WTGroundOutflow);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceInflowFraction);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_SurfaceOutflowIntensity);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_GoundOutflowIntensity);
	Edt->EnableWindow(TRUE);
	

}
