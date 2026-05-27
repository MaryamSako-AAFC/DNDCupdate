// ManureCompost.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "ManureCompost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString snote;
int CompostRemoveMonth[10]={0,0}, CompostRemoveDay[10]={0,0};
float CompostRetain[10]={0.0,0.0}, CompostToField[10]={0.0,0.0}, CompostToMarket[10]={0.0,0.0};
/////////////////////////////////////////////////////////////////////////////
// ManureCompost dialog


ManureCompost::ManureCompost(CWnd* pParent /*=NULL*/)
	: CDialog(ManureCompost::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureCompost)
	m_CompostDensity = 0.0f;
	m_Remain = 0.0f;
	m_ToField = 0.0f;
	m_ToMarket = 0.0f;
	m_AdditiveAmount = 0.0f;
	m_AdditiveCN = 0.0f;
	m_RemoveFrequency = 0.0f;
	m_unit = -1;
	m_CompostCover = 0;
	m_CompostRemoveTimes = 0;
	m_RemoveID = 0;
	m_RemoveMonth = 0;
	m_RemoveDay = 0;
	//}}AFX_DATA_INIT
}


void ManureCompost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureCompost)
	DDX_Text(pDX, IDC_StorageDensity, m_CompostDensity);
	DDX_Text(pDX, IDC_Remain, m_Remain);
	DDX_Text(pDX, IDC_ToField, m_ToField);
	DDX_Text(pDX, IDC_ToMarket, m_ToMarket);
	DDX_Text(pDX, IDC_StorageAmount, m_AdditiveAmount);
	DDX_Text(pDX, IDC_StorageCN, m_AdditiveCN);
	DDX_Text(pDX, IDC_StorageDays, m_RemoveFrequency);
	DDX_Radio(pDX, IDC_unit, m_unit);
	DDX_Text(pDX, IDC_CompostCover, m_CompostCover);
	DDX_Text(pDX, IDC_CompostRemoveTimes, m_CompostRemoveTimes);
	DDX_Text(pDX, IDC_RemoveID, m_RemoveID);
	DDX_Text(pDX, IDC_RemoveMonth, m_RemoveMonth);
	DDX_Text(pDX, IDC_RemoveDay, m_RemoveDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureCompost, CDialog)
	//{{AFX_MSG_MAP(ManureCompost)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	ON_BN_CLICKED(IDC_BUTTON1, OnRevome1)
	ON_BN_CLICKED(IDC_BUTTON2, OnRemove2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureCompost message handlers

void ManureCompost::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	//unit conversion
	float CompostPoro, AdditiveAmount;
	if(m_unit==0)
	{
		CompostPoro = m_CompostDensity;
		AdditiveAmount = m_AdditiveAmount;
	}
	else
	{
		CompostPoro = m_CompostDensity * lboft3_kgom3;//lb/ft3 -> kg/m3
		AdditiveAmount = m_AdditiveAmount * lb_kg;//lb -> kg;
	}

	if(CompostPoro==0.0)
	{
		snote.Format("Porosity is not correct");
		AfxMessageBox(snote);
		return;
	}	
	else
	{
		CompostRemoveMonth[m_RemoveID] = m_RemoveMonth;
		CompostRemoveDay[m_RemoveID] = m_RemoveDay; 
		CompostToField[m_RemoveID] = m_ToField; 
		CompostToMarket[m_RemoveID] = m_ToMarket;
		CompostRetain[m_RemoveID] = m_Remain;

		CString SF;
		FILE* sf;
		SF.Format("%s\\Inter\\ManureCompost.txt", OUTPUT);
		sf=fopen(SF, "w");
		if(sf==NULL)
		{		
			note(1, SF);
			//AfxMessageBox(note);
			exit(0);
		}
		fprintf(sf, "%f  %d  %d  %f  %f\n", CompostPoro, m_CompostCover, m_CompostRemoveTimes, AdditiveAmount, m_AdditiveCN);  
		
		for(int i=1;i<=m_CompostRemoveTimes;i++)
		{
			fprintf(sf, "%d %d %f %f %f \n", CompostRemoveMonth[i], CompostRemoveDay[i], CompostToField[i], CompostToMarket[i], CompostRetain[i]);
		}
		fclose(sf);
	/////////////////////////////////////////////////////
/*		CString SF;
		FILE* sf;
		SF.Format("%s\\Inter\\ManureCompost.txt", OUTPUT);
		sf=fopen(SF, "w");
		if(sf==NULL) note(1, SF);
		
		fprintf(sf, "%f  %d  %f  %f  %f\n", CompostPoro, m_CompostCover, m_RemoveFrequency, AdditiveAmount, m_AdditiveCN);  
		fprintf(sf, "%f  %f  %f\n", m_ToField, m_ToMarket, m_Remain);
		fclose(sf);*/
	}

	CDialog::OnOK();
}

BOOL ManureCompost::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString DB;
	FILE *db;	
	DB.Format("%s\\Result\\inter\\UnitSystem", ROOTDIR);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &m_unit);
	fclose(db);

	CString SF;
		FILE* sf;
		SF.Format("%s\\Result\\Inter\\ManureCompost.txt", ROOTDIR);
		sf=fopen(SF, "r");
		if(sf==NULL)
		{	
			sf=fopen(SF, "w");
			fprintf(sf, "%f  %d  %f  %f  %f\n", 0.0, 0, 0.0, 0.0, 0.0);  
			//fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
			fclose(sf);
			return(0);
			/*CString note;
			note.Format("Cannot open file %s", SF);
			AfxMessageBox(note);
			exit(0);*/
		}
		fscanf(sf, "%f  %d  %d  %f  %f\n", &m_CompostDensity, &m_CompostCover, &m_CompostRemoveTimes, &m_AdditiveAmount, &m_AdditiveCN);  
		for(int i=1;i<=m_CompostRemoveTimes;i++)
		{
			fscanf(sf, "%d %d %f %f %f \n", &CompostRemoveMonth[i], &CompostRemoveDay[i], &CompostToField[i], &CompostToMarket[i], &CompostRetain[i]);
		}
		
		fclose(sf);

	if(m_unit==1)
	{
		m_CompostDensity /= lboft3_kgom3;//kg/m3 -> lb/ft3 
		m_AdditiveAmount /= lb_kg;//kg -> lb
	}

	m_RemoveID = 1;
	m_RemoveMonth = CompostRemoveMonth[m_RemoveID];
	m_RemoveDay = CompostRemoveDay[m_RemoveID];
	m_ToField = CompostToField[m_RemoveID];
	m_ToMarket = CompostToMarket[m_RemoveID];
	m_Remain = CompostRetain[m_RemoveID];

	UpdateData(FALSE);
	
	//Onunit2();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ManureCompost::Onunit() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==0&&n_unit==1) 
	{
		m_CompostDensity *= lboft3_kgom3;//lb/ft3 -> kg/m3
		m_AdditiveAmount *= lb_kg;//lb -> kg;
	}

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

	UpdateData(FALSE);
}

void ManureCompost::Onunit2() 
{
	// TODO: Add your control notification handler code here
	
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==1&&n_unit==0) 
	{
		m_CompostDensity /= lboft3_kgom3;//kg/m3 -> lb/ft3 
		m_AdditiveAmount /= lb_kg;//kg -> lb 
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		//Edt=(CEdit *)GetDlgItem(IDC_kg);
		//Edt->EnableWindow(FALSE); 
		//Edt=(CEdit *)GetDlgItem(IDC_lb);
		//Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		//Edt=(CEdit *)GetDlgItem(IDC_kg);
		//Edt->EnableWindow(TRUE); 
		//Edt=(CEdit *)GetDlgItem(IDC_lb);
		//Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void ManureCompost::OnRevome1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_ToField+m_ToMarket+m_Remain<0.9999||m_ToField+m_ToMarket+m_Remain>1.0001)
	{
		snote.Format("The sum of fractions of the compost manure effluxes must be equal to 1");
		AfxMessageBox(snote);
		return;
	}

	CompostRemoveMonth[m_RemoveID] = m_RemoveMonth;
	CompostRemoveDay[m_RemoveID] = m_RemoveDay;
	CompostRetain[m_RemoveID] = m_Remain;
	CompostToField[m_RemoveID] = m_ToField;
	CompostToMarket[m_RemoveID] = m_ToMarket;
	
	m_RemoveID++;
	if(m_RemoveID>m_CompostRemoveTimes) m_RemoveID = m_CompostRemoveTimes;

	m_RemoveMonth = CompostRemoveMonth[m_RemoveID];
	m_RemoveDay = CompostRemoveDay[m_RemoveID];
	m_Remain = CompostRetain[m_RemoveID];
	m_ToField = CompostToField[m_RemoveID];
	m_ToMarket = CompostToMarket[m_RemoveID];

	UpdateData(FALSE);
}

void ManureCompost::OnRemove2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_ToField+m_ToMarket+m_Remain<0.9999||m_ToField+m_ToMarket+m_Remain>1.0001)
	{
		snote.Format("The sum of fractions of the compost manure effluxes must be equal to 1");
		AfxMessageBox(snote);
		return;
	}

	CompostRemoveMonth[m_RemoveID] = m_RemoveMonth;
	CompostRemoveDay[m_RemoveID] = m_RemoveDay;
	CompostRetain[m_RemoveID] = m_Remain;
	CompostToField[m_RemoveID] = m_ToField;
	CompostToMarket[m_RemoveID] = m_ToMarket;

	m_RemoveID--;
	if(m_RemoveID<1) m_RemoveID = 1;

	m_RemoveMonth = CompostRemoveMonth[m_RemoveID];
	m_RemoveDay = CompostRemoveDay[m_RemoveID];
	m_Remain = CompostRetain[m_RemoveID];
	m_ToField = CompostToField[m_RemoveID];
	m_ToMarket = CompostToMarket[m_RemoveID];

	UpdateData(FALSE);
}
