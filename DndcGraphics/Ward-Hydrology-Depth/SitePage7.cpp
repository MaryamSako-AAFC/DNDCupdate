// SitePage7.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage7.h"
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
extern CropofEachYear CYr[8];
extern char *soiltexture[];
extern char *soillanduse[];
CString FCT7;

int ManuTypekk;
/////////////////////////////////////////////////////////////////////////////
// SitePage7 property page

IMPLEMENT_DYNCREATE(SitePage7, CPropertyPage)

SitePage7::SitePage7() : CPropertyPage(SitePage7::IDD)
{
	//{{AFX_DATA_INIT(SitePage7)
	m_ManID = 0;
	m_ManMonth = 0;
	m_ManN = 0;
	m_ManDay = 0;
	m_ManAmount = 0.0;
	m_ManC_N = 0.0;
	m_kgN = 0.0f;
	m_ManureMethod = -1;
	m_unit = 0;
	m_ManureDepth = 0.0f;
	m_ManureNH4 = 0.0f;
	m_ManureDM=0.0;
	m_ManureAppHour=0;
	m_ManurePH=0.0;
	m_ManureNO3 = 0.0f;
	m_FarmManureMethod = -1;
	m_FarmManureDepth = 0.0f;
	//}}AFX_DATA_INIT
}

SitePage7::~SitePage7()
{

}

void SitePage7::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage7)
	DDX_Control(pDX, IDC_COMBO1, m_ManType);
	DDX_Control(pDX, IDC_LIST2, m_ManList);
	DDX_Text(pDX, IDC_ManID, m_ManID);
	DDV_MinMaxLong(pDX, m_ManID, 0, 1000);
	DDX_Text(pDX, IDC_ManMonth, m_ManMonth);
	DDX_Text(pDX, IDC_ManN, m_ManN);
	DDX_Text(pDX, IDC_ManDay, m_ManDay);
	DDX_Text(pDX, IDC_ManAmount, m_ManAmount);
	DDV_MinMaxDouble(pDX, m_ManAmount, 0., 10000000.);
	DDX_Text(pDX, IDC_ManC_N, m_ManC_N);
	DDV_MinMaxDouble(pDX, m_ManC_N, 0., 1000000.);
	DDX_Text(pDX, IDC_kgN, m_kgN);
	DDX_Radio(pDX, IDC_ManuMethod, m_ManureMethod);
	DDX_Radio(pDX, IDC_unit, m_unit);
	DDX_Text(pDX, IDC_ManureDepth, m_ManureDepth);
	DDX_Text(pDX, IDC_ManureNH4, m_ManureNH4);
	DDX_Text(pDX, IDC_ManureDM, m_ManureDM);
	DDX_Text(pDX, IDC_ManureAppHour, m_ManureAppHour);
	DDX_Text(pDX, IDC_ManurePH, m_ManurePH);
	DDX_Text(pDX, IDC_ManureNO3, m_ManureNO3);
	DDX_Radio(pDX, IDC_FarmManuMethod, m_FarmManureMethod);
	DDX_Text(pDX, IDC_FarmManureDepth, m_FarmManureDepth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage7, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage7)
	ON_BN_CLICKED(IDC_ManAccept, OnManAccept)
	ON_BN_CLICKED(IDC_FerLast, OnFerLast)
	ON_BN_CLICKED(IDC_FerNext, OnFerNext)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_EN_KILLFOCUS(IDC_ManMonth, OnKillfocusManMonth)
	ON_EN_KILLFOCUS(IDC_ManDay, OnKillfocusManDay)
	ON_EN_KILLFOCUS(IDC_ManAmount, OnKillfocusManAmount)
	ON_EN_KILLFOCUS(IDC_ManC_N, OnKillfocusManCN)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	ON_EN_KILLFOCUS(IDC_kgN, OnKillfocuskgN)
	ON_EN_KILLFOCUS(IDC_ManureNH4, OnKillfocusManureNH4)
	ON_EN_KILLFOCUS(IDC_ManureNO3, OnKillfocusManureNO3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage7 message handlers

BOOL SitePage7::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CString DB;
	FILE *db;	
	DB.Format("%s\\Result\\inter\\UnitSystem", ROOTDIR);
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
	FCT7.Format("%s_%d", INTERMANAGE, ManureCropOrder);
#else
	FCT7.Format("%s_1", INTERMANAGE);
#endif

	int rrr, yyy, i;
	for(i=0; i<=290; i++)
	{
		ManuID[i]=0; ManuMonth[i]=0; ManuDay[i]=0; ManuType[i]=0;
		ManuAmount[i]=0.0; ManuCN[i]=0.0; ManuN[i]=0.0; ManuMethod[i]=0;
		ManureDepth[i]=0.0;
		ManureNH4[i]=0.0;
		ManureNO3[i]=0.0;
		ManureAppHour[i]=0;
		ManureDM[i]=0.0;
		ManurePH[i]=0.0;
	}

	//CString DB;
	//FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT7);
	db=fopen(DB, "r");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not open file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//DB.Format("%s\\inter\\CropManu_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropManu_%d_%d.txt", FCT7, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not open file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(db, "%d", &m_ManN);

/*	if(m_ManN==0)
	{
		for(i=1; i<=20; i++)
		{
			ManuID[i] = i;
			ManuMonth[i]=0;
			ManuDay[i]=0;
			ManuAmount[i]=0.0;
			ManuCN[i]=0.0;
			ManuType[i]=0;
			ManuN[i]=0.0;
			ManuMethod[i]=0;
			ManureDepth[i]=0.0;
			ManureNH4[i]=0.0;
			ManureNO3[i]=0.0;
		}	
	}
	else
	{*/
		for(i=1; i<=m_ManN; i++)
		{
			ManuID[i] = i;
			fscanf(db, "%d %d", &ManuMonth[i], &ManuDay[i]);
			fscanf(db, "%f %f %d %d %f", &ManuAmount[i], &ManuCN[i], &ManuType[i], &ManuMethod[i], &ManureDepth[i]);
			fscanf(db, "%f %f %f %d %f %f", &ManuN[i], &ManureNH4[i], &ManureNO3[i], &ManureAppHour[i], &ManureDM[i], &ManurePH[i]);
		}		
	//}
	fclose(db);
	

	i=1;
		m_ManID = ManuID[i];
		m_ManMonth = ManuMonth[i];
		m_ManDay = ManuDay[i];
		m_ManAmount =ManuAmount[i];
		m_ManC_N = ManuCN[i];
		m_ManureMethod = ManuMethod[i];
		m_ManType.SetCurSel(ManuType[i]-1);
		//if(ManuCN[i]<=0.0) m_kgN = 0.0;
		//else m_kgN = ManuAmount[i]/ManuCN[i];
		m_ManureDepth = ManureDepth[i];
		m_kgN = ManuN[i];
		m_ManureNH4 = ManureNH4[i];
		m_ManureDM=ManureDM[i];
		m_ManureAppHour=ManureAppHour[i];
		m_ManurePH=ManurePH[i];
		m_ManureNO3 = ManureNO3[i];

	if(m_unit==1)
	{
		m_ManAmount /= lboac_kgoha;
		m_kgN /= lboac_kgoha;
	}

	UpdateData(FALSE);

	//Onunit2();

	demo();
/*		// manure setup
	//int i,n;
	CString txt;

//	m_ManList.DeleteAllItems();
//    n = cycle.get(rrr, yyy)->ManNumber;
    if (m_ManN >= 0) 
	{
		//m_ManN = n;
		for (i = 1; i<=m_ManN;i++) 
		{
			txt = OrderNumber(i,"Man.",&txt);
			m_ManList.InsertItem(i-1,txt);

			txt.Format("%d",ManuMonth[i]);
			m_ManList.SetItemText(i-1,1,txt);

			txt.Format("%d",ManuDay[i]);
			m_ManList.SetItemText(i-1,2,txt);

			txt.Format("%9.3f",ManuAmount[i]);
			m_ManList.SetItemText(i-1,3,txt);

			txt.Format("%9.3f",ManuCN[i]);
			m_ManList.SetItemText(i-1,4,txt);

			txt.Format("%d",ManuType[i]);
			m_ManList.SetItemText(i-1,5,txt);
		}
	}
*/
		
    /*m_ManGrid.SetRows(1);
    m_ManGrid.SetCols(6);

    m_ManGrid.SetRow(0);
    m_ManGrid.SetCol(1);
    m_ManGrid.SetText("Month");
    m_ManGrid.SetCol(2);
    m_ManGrid.SetText("Day");
    m_ManGrid.SetCol(3);
    m_ManGrid.SetText("Amount");
    m_ManGrid.SetCol(4);
    m_ManGrid.SetText("C/N ratio");
    m_ManGrid.SetCol(5);
    m_ManGrid.SetText("Type");

        //' Manure parameter
	int i,n;
	char ch[20];
    n = cycle.get(rrr, yyy)->ManNumber;
	if (n >= 0) {
		m_ManN=n;
		m_ManGrid.SetRows(n+1);
		for (i = 1;i<=n;i++) {
			m_ManGrid.SetRow(i);
			m_ManGrid.SetCol(0);
			sprintf(ch,"%dth",i);
			m_ManGrid.SetText(ch);

			m_ManGrid.SetCol(1);
			sprintf(ch,"%d",manure.get(rrr, yyy, i)->month);
			m_ManGrid.SetText(ch);
			m_ManGrid.SetCol(2);
			sprintf(ch,"%d",manure.get(rrr, yyy, i)->day);
			m_ManGrid.SetText(ch);
			m_ManGrid.SetCol(3);
			sprintf(ch,"%9.3f",manure.get(rrr, yyy, i)->Amount);
			m_ManGrid.SetText(ch);
			m_ManGrid.SetCol(4);
			sprintf(ch,"%9.5f",manure.get(rrr, yyy, i)->C_N);
			m_ManGrid.SetText(ch);
			m_ManGrid.SetCol(5);
			sprintf(ch,"%d",manure.get(rrr, yyy, i)->Type);
			m_ManGrid.SetText(ch);
		}
    }*/
	//UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}

BEGIN_EVENTSINK_MAP(SitePage7, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage7)
	//ON_EVENT(SitePage7, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*BOOL SitePage7::CheckManN()
{
		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Result\\inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

    if (m_ManN < 0) {
		MessageBox("Manure number must be >=0.", "Input Error:",NULL);
		m_ManN = 0;
		UpdateData(FALSE);
		return FALSE;
	}
	else if (m_ManN==0) {
		cycle.get(rrr,yyy)->ManNumber=0;
		return FALSE;
	}
	return TRUE;
}

BOOL SitePage7::CheckManID()
{
	if (!CheckManN()) return FALSE;
	if (m_ManID==0 ) return FALSE;
	if (m_ManID<0 || m_ManID> m_ManN) {
        MessageBox("The Manure ID number must be 0<=ID<=total number!", "Input Error:",NULL);
		m_ManID = m_ManN;
		UpdateData(FALSE);
		return FALSE;
	}
	return TRUE;
}*/

/*void SitePage7::OnKillfocusManN() 
{
	//UpdateData(TRUE);


	//if (!CheckManN()) return;

	//int n = m_ManList.GetItemCount();
	//ResetListItem(m_ManN,n,"Man.",&m_ManList);


	//SetArrayRange(4, m_ManN);

}*/

//void SitePage7::OnKillfocusManID() // Set default values
//{
/*		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Result\\inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);
	if (!CheckManID()) return;

	ManureParameter *MPnt;
	MPnt = manure.get(rrr, yyy,m_ManID);

	if (MPnt->month<=0) return;
	m_ManMonth = MPnt->month;
	m_ManDay   = MPnt->day;
	m_ManAmount= MPnt->Amount;
	m_ManC_N   = MPnt->C_N;
	m_ManType  = MPnt->Type -1;

	char  ch[20];
	int   i,id;
	float dt;

    m_ManGrid.SetRow(m_ManID);
	for (i = 1;i<=5;i++) {
		m_ManGrid.SetCol(i);
		strcpy(ch,m_ManGrid.GetText());
		if (strlen(ch)==0) {id=0;dt=0;}
		else {
			sscanf(ch,"%d",&id);
			sscanf(ch,"%f",&dt);
		}
		if (id<0) id=0;
		if (dt<0) dt=0;

        if (i==1)      m_ManMonth  =id;
		else if (i==2) m_ManDay    =id;
		else if (i==3) m_ManAmount =dt;
		else if (i==4) m_ManC_N    =dt;
		else if (i==5) m_ManType   =id-1;
	}
	//UpdateData(FALSE);*/
//}

/*void SitePage7::OnClickMsflexgrid1() 
{
	// TODO: Add your control notification handler code here
    /*int i;
    i = m_ManGrid.GetRow();
    if (i > 0) {
		m_ManID=i;
		UpdateData(FALSE);
		OnKillfocusManID();
	}*
	
}*/

void SitePage7::OnManAccept() 
{
	UpdateData(TRUE);

	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT7);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//unit conversion
	float mManAmount, mkgN, mManureNH4, mManureNO3;
	if(m_unit==0)
	{
		mManAmount = m_ManAmount;
		mkgN = m_kgN;
		mManureNH4 = m_ManureNH4;
		mManureNO3 = m_ManureNO3;
	}
	else
	{
		mManAmount = m_ManAmount * lboac_kgoha;//lb/ac -> kg/ha
		mkgN = m_kgN * lboac_kgoha;//lb/ac -> kg/ha
		mManureNH4 = m_ManureNH4 * lboac_kgoha;
		mManureNO3 = m_ManureNO3 * lboac_kgoha;
	}

	int i;
	i=m_ManID;		
	ManuMonth[i]=m_ManMonth;
	ManuDay[i]=m_ManDay;
	ManuDay[i]=m_ManDay;
	ManuAmount[i]=mManAmount;
	ManureDepth[i]=m_ManureDepth;
	ManureDM[i]=m_ManureDM;
	ManurePH[i]=m_ManurePH;
	ManureAppHour[i]=m_ManureAppHour;
	ManuCN[i]=m_ManC_N;
	ManuType[i]=m_ManType.GetCurSel()+1;
	ManuN[i] = mkgN;
	ManureNH4[i] = mManureNH4;
	ManureNO3[i] = mManureNO3;

	ManuMethod[i] = m_ManureMethod;
	//if(m_ManC_N==0.0) m_kgN = 0.0;
	//else m_kgN = m_ManAmount / m_ManC_N;

	//DB.Format("%s\\inter\\CropManu_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropManu_%d_%d.txt", FCT7, rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d\n", m_ManN);

	for (i=1; i<=m_ManN; i++) 
	{
		/*if(i==0) 
		{
			ManuMethod[i] = m_FarmManureMethod;
			ManureDepth[i] = m_FarmManureDepth;
		}*/

		fprintf(db, "%d %d\n", ManuMonth[i], ManuDay[i]);
		fprintf(db, "%f %f %d %d %f\n", ManuAmount[i], ManuCN[i], ManuType[i], ManuMethod[i], ManureDepth[i]);
		fprintf(db, "%f %f %f %d %f %f\n", ManuN[i], ManureNH4[i], ManureNO3[i], ManureAppHour[i], ManureDM[i], ManurePH[i] );
	}	
	fclose(db);

	//ManuMethod[i]=0 - surface spread; 1 - incorporation, 2 - injection

	UpdateData(FALSE);

	demo();


/*		int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Result\\inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	UpdateData(TRUE);
	if (!CheckManID()) return;

	int n;
	char ch[20];
	n=m_ManN;
	if (m_ManN != cycle.get(rrr, yyy)->ManNumber) 
	{
		MessageBox("Total manure count is WRONG","Input Error:",NULL);
		return;
	}

	if (!IfMonth(m_ManMonth)) return;
	sprintf(ch,"%d",m_ManMonth);
	m_ManList.SetItemText(m_ManID-1,1,ch);
	manure.get(rrr, yyy, m_ManID)->month=m_ManMonth;

	if (!IfDay(m_ManDay)) return;
	sprintf(ch,"%d",m_ManDay);
	m_ManList.SetItemText(m_ManID-1,2,ch);
	manure.get(rrr, yyy, m_ManID)->day =m_ManDay;

	sprintf(ch,"%9.3f",m_ManAmount);
	m_ManList.SetItemText(m_ManID-1,3,ch);
	manure.get(rrr, yyy, m_ManID)->Amount =(float)m_ManAmount;

	sprintf(ch,"%9.3f",m_ManC_N);
	m_ManList.SetItemText(m_ManID-1,4,ch);
	manure.get(rrr, yyy, m_ManID)->C_N=(float)m_ManC_N;

	if (m_ManType<0)
	{
		MessageBox("Please select a manure type!","Loss input:",NULL);
		return;
	}
	sprintf(ch,"%d",m_ManType+1);
	m_ManList.SetItemText(m_ManID-1,5,ch);
	manure.get(rrr, yyy, m_ManID)->Type=m_ManType+1;
*/
/* 	int i;
	m_ManGrid.SetRow(m_ManID);
    for (i = 1;i<=5;i++) 
	{
        m_ManGrid.SetCol(i);
		if (i==1) 
		{
			if (!IfMonth(m_ManMonth)) return;
			sprintf(ch,"%d",m_ManMonth);
			m_ManGrid.SetText(ch);
			manure.get(rrr, yyy, m_ManID)->month=m_ManMonth;
        }
		else if (i==2) {
			if (!IfDay(m_ManDay)) return;
			sprintf(ch,"%d",m_ManDay);
			m_ManGrid.SetText(ch);
			manure.get(rrr, yyy, m_ManID)->day =m_ManDay;
        }
		else if (i==3) {
			sprintf(ch,"%9.2f",m_ManAmount);
			m_ManGrid.SetText(ch);
			manure.get(rrr, yyy, m_ManID)->Amount =(float)m_ManAmount;
        }
		else if (i==4) {
			sprintf(ch,"%9.4f",m_ManC_N);
			m_ManGrid.SetText(ch);
			manure.get(rrr, yyy, m_ManID)->C_N=(float)m_ManC_N;
        }
		else if (i==5) {
			if (m_ManType<0)
			{
				MessageBox("Please select a manure type!","Loss input:",NULL);
				return;
			}
			sprintf(ch,"%d",m_ManType+1);
			m_ManGrid.SetText(ch);
			manure.get(rrr, yyy, m_ManID)->Type=m_ManType+1;
        }
    }*/
	
}

void SitePage7::OnFerLast() 
{
	UpdateData(TRUE);

	int i;
	i=m_ManID;		
		ManuMonth[i]=m_ManMonth;
		ManuDay[i]=m_ManDay;
		ManuDay[i]=m_ManDay;
		ManuAmount[i]=m_ManAmount;
		ManuCN[i]=m_ManC_N;
		ManuType[i]=m_ManType.GetCurSel()+1;
		//ManuN[i] = m_ManAmount/m_ManC_N-m_ManureNH4;
		ManuMethod[i]=m_ManureMethod;
		ManureDepth[i]=m_ManureDepth;
		ManureNH4[i]=m_ManureNH4;
		ManureDM[i]=m_ManureDM;
		ManureAppHour[i]=m_ManureAppHour;
		ManurePH[i]=m_ManurePH;
		ManureNO3[i]=m_ManureNO3;

	if (m_ManN==0) return;
	if (m_ManID>1) m_ManID--;
	else if (m_ManID==0) m_ManID=1;

	i=m_ManID;
		//m_ManID = ManuID[i];
		m_ManMonth = ManuMonth[i];
		m_ManDay = ManuDay[i];
		m_ManAmount =ManuAmount[i];
		m_ManC_N = ManuCN[i];
		m_ManureMethod = ManuMethod[i];
		m_ManType.SetCurSel(ManuType[i]-1);
		//if(m_ManC_N==0.0) m_kgN=0.0;
		//else m_kgN = m_ManAmount/m_ManC_N;
		m_ManureDepth = ManureDepth[i];
		m_kgN = ManuN[i];
		m_ManureNH4 = ManureNH4[i];
		m_ManureDM=ManureDM[i];
		m_ManureAppHour=ManureAppHour[i];
		m_ManurePH=ManurePH[i];
		m_ManureNO3 = ManureNO3[i];


	UpdateData(FALSE);
	//OnKillfocusManID();
}

void SitePage7::OnFerNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i;
	i=m_ManID;		
		ManuMonth[i]=m_ManMonth;
		ManuDay[i]=m_ManDay;
		ManuDay[i]=m_ManDay;
		ManuAmount[i]=m_ManAmount;
		ManuMethod[i]=m_ManureMethod;
		ManuCN[i]=m_ManC_N;
		ManuType[i]=m_ManType.GetCurSel()+1;
	//	ManuN[i]=ManuAmount[i]/ManuCN[i]-m_ManureNH4;//added -m_ManureNH4 removed...
		ManureDepth[i]=m_ManureDepth;
		ManureNH4[i]=m_ManureNH4;
		ManureDM[i]=m_ManureDM;
		ManureAppHour[i]=m_ManureAppHour;
		ManurePH[i]=m_ManurePH;
		ManureNO3[i]=m_ManureNO3;

	if (m_ManN==0) return;
	if (m_ManID<m_ManN) m_ManID++;
	else if (m_ManID==0) m_ManID=1;

		i=m_ManID;
		//m_ManID = ManuID[i];
		m_ManMonth = ManuMonth[i];
		m_ManDay = ManuDay[i];
		m_ManAmount =ManuAmount[i];
		m_ManureMethod = ManuMethod[i];
		m_ManC_N = ManuCN[i];
		m_ManType.SetCurSel(ManuType[i]-1);
		//if(m_ManC_N==0.0) m_kgN = 0.0;
		//else m_kgN = m_ManAmount / m_ManC_N;
		m_ManureDepth = ManureDepth[i];
		m_kgN = ManuN[i];
		m_ManureNH4 = ManureNH4[i];
		m_ManureDM=ManureDM[i];
		m_ManureAppHour=ManureAppHour[i];
		m_ManurePH=ManurePH[i];
		m_ManureNO3 = ManureNO3[i];

				
	UpdateData(FALSE);
	//OnKillfocusManID();
}

void SitePage7::OnKillfocusCombo1() 
{
	float CN[11]={0.0, 13.0, 25.0, 70.0, 5.0, 30.0, 2.0, 5.0, 9.5, 5.6, 4.0};
	UpdateData(TRUE);

	ManuTypekk=m_ManType.GetCurSel()+1;
	m_ManC_N = CN[ManuTypekk];

	UpdateData(FALSE);
}

void SitePage7::OnKillfocusManMonth() 
{
	//UpdateData(TRUE);	
}

void SitePage7::OnKillfocusManDay() 
{
	//UpdateData(TRUE);	
}

void SitePage7::OnKillfocusManAmount() 
{
	UpdateData(TRUE);

	if(m_kgN==0)m_kgN = m_ManAmount / m_ManC_N;
	
	if(ManuTypekk==1)//1   farmyard manure
	{
		if(m_ManureNH4==0)
		{
		m_ManureNH4 = m_kgN * 0.15;
		m_ManureNO3 = m_kgN * 0.00;
		m_kgN*=0.85;
		}
	
		if(m_ManureDM==0) m_ManureDM=41.5;
		if(m_ManureAppHour==0)m_ManureAppHour=12;
		if(m_ManurePH==0)m_ManurePH=7.0;
		
	}
	else if(ManuTypekk==2)//2   green manure
	{
		m_ManureNH4 = 0.0;
		m_ManureNO3 = 0.0;
	}
	else if(ManuTypekk==3)//3   straw
	{
		m_ManureNH4 = 0.0;
		m_ManureNO3 = 0.0;
	}
	else if(ManuTypekk==4)//4   slurry animal waste
	{
		if(m_ManureNH4==0){
			m_ManureNH4 = m_kgN * .48;
			m_kgN*=0.5;
			m_ManureNO3 = m_kgN * .02;
		}
		
		if(m_ManureDM==0)m_ManureDM=6.5;
		if(m_ManureAppHour==0)m_ManureAppHour=12;
		if(m_ManurePH==0)m_ManurePH=8.5;
		
	}
	else if(ManuTypekk==5)//5   compost
	{
		m_ManureNH4 = m_kgN * 0.5;
		m_ManureNO3 = m_kgN * 0.5;
	}
	else if(ManuTypekk==6)//6   bean cake
	{
		m_ManureNH4 = 0.0;
		m_ManureNO3 = 0.0;
	}
	else if(ManuTypekk==7)//7   human waste
	{
		m_ManureNH4 = m_kgN * 3.0;
		m_ManureNO3 = m_kgN * 1.0;
	}
	else if(ManuTypekk==8)//8   poultry waste
	{
		m_ManureNH4 = m_kgN * 3.0;
		m_ManureNO3 = m_kgN * 1.0;
	}
	else if(ManuTypekk==9)//9   sewage sludge
	{
		m_ManureNH4 = m_kgN * 3.0;
		m_ManureNO3 = m_kgN * 1.0;
	}
	else if(ManuTypekk==10)//10 meat or blood meal
	{
		m_ManureNH4 = m_kgN * 0.0;
		m_ManureNO3 = 0.0;
	}
	else {}

/*	if(m_ManC_N==0.0) 
	{
		m_kgN = 0.0;
		m_ManureNH4 = 0.0;
		m_ManureNO3 = 0.0;
	}
	else 
	{
		m_kgN = 0.6 * m_ManAmount / m_ManC_N;
		m_ManureNH4 = 0.3 * m_ManAmount / m_ManC_N;
		m_ManureNO3 = 0.1 * m_ManAmount / m_ManC_N;
	}
*/	
	UpdateData(FALSE);
}

void SitePage7::OnKillfocusManCN() 
{
	OnKillfocusManAmount();
/*
	UpdateData(TRUE);
	
	if(m_ManC_N==0.0) 
	{
		m_kgN = 0.0;
		m_ManureNH4 = 0.0;
		m_ManureNO3 = 0.0;
	}
	else 
	{
		m_kgN = 0.6 * m_ManAmount / m_ManC_N;
		m_ManureNH4 = 0.3 * m_ManAmount / m_ManC_N;
		m_ManureNO3 = 0.1 * m_ManAmount / m_ManC_N;
	}
	
	UpdateData(FALSE);*/
}

BOOL SitePage7::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString DB;
	FILE *db;	
	DB.Format("%s\\Result\\inter\\UnitSystem", ROOTDIR);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &m_unit);
	fclose(db);

	int i;
	char *title[]={"Application","Month","Day","Type", "Manure-C","C/N","ManureOrg-N","Manure-DM%","Manure-pH"};
	int  ItemNum=9;
	for (i=0;i<ItemNum;i++)
	{
		m_ManList.InsertColumn(i,title[i],LVCFMT_CENTER,85,-1);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void SitePage7::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	OnKillfocusCombo1();
}


void SitePage7::demo() 
{
	int i;
	CString txt;

	m_ManList.DeleteAllItems();
    if (m_ManN >= 0) 
	{
		for (i = 1; i<=m_ManN;i++) 
		{
			txt = OrderNumber(i,"",&txt);
			m_ManList.InsertItem(i-1,txt);

			txt.Format("%d",ManuMonth[i]);
			m_ManList.SetItemText(i-1,1,txt);

			txt.Format("%d",ManuDay[i]);
			m_ManList.SetItemText(i-1,2,txt);

			txt.Format("%d",ManuType[i]);
			m_ManList.SetItemText(i-1,3,txt);

			txt.Format("%9.3f",ManuAmount[i]);
			m_ManList.SetItemText(i-1,4,txt);

			txt.Format("%9.3f",ManuCN[i]);
			m_ManList.SetItemText(i-1,5,txt);

			//ManuN[i] = ManuAmount[i] / ManuCN[i]; 

			txt.Format("%9.3f",ManuN[i]);
			m_ManList.SetItemText(i-1,6,txt);

			txt.Format("%9.3f",ManureDM[i]);
			m_ManList.SetItemText(i-1,7,txt);

				txt.Format("%9.3f",ManurePH[i]);
			m_ManList.SetItemText(i-1,8,txt);

			
		}
	}
}

void SitePage7::Onunit() 
{
	// TODO: Add your control notification handler code here
	//Onunit2();
}

void SitePage7::Onunit2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);
	}
}

void SitePage7::OnKillfocuskgN() 
{
/*	UpdateData(TRUE);

	float TotalC = m_ManAmount;
	float TotalN = m_kgN + m_ManureNH4 + m_ManureNO3;
	m_ManC_N = TotalC / TotalN;
		
	UpdateData(FALSE);*/
}

void SitePage7::OnKillfocusManureNH4() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);

	float TotalC = m_ManAmount;
	float TotalN = m_kgN + m_ManureNH4 + m_ManureNO3;
	m_ManC_N = TotalC / TotalN;
		
	UpdateData(FALSE);*/
}

void SitePage7::OnKillfocusManureNO3() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);

	float TotalC = m_ManAmount;
	float TotalN = m_kgN + m_ManureNH4 + m_ManureNO3;
	m_ManC_N = TotalC / TotalN;
		
	UpdateData(FALSE);*/
}
