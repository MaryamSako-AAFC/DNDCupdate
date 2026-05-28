// ManureDigester.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "RunPaths.h"
#include "dndc_main.h"
#include "ManureDigester.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManureDigester dialog


ManureDigester::ManureDigester(CWnd* pParent /*=NULL*/)
	: CDialog(ManureDigester::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureDigester)
	m_RetentionDays = 0.0f;
	m_DigesterTempClass = -1;
	m_ToField = 0.0f;
	m_ToMarket = 0.0f;
	m_ToRemain = 0.0f;
	//}}AFX_DATA_INIT
}


void ManureDigester::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureDigester)
	DDX_Text(pDX, IDC_DigesterDays, m_RetentionDays);
	DDX_Radio(pDX, IDC_Temp, m_DigesterTempClass);
	DDX_Text(pDX, IDC_ToField, m_ToField);
	DDX_Text(pDX, IDC_ToMarket, m_ToMarket);
	DDX_Text(pDX, IDC_ToRemain, m_ToRemain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureDigester, CDialog)
	//{{AFX_MSG_MAP(ManureDigester)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureDigester message handlers

void ManureDigester::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString snote;
	float m_DigesterCH4;

	if(m_RetentionDays==0.0) //m_RetentionDays = 14.0;
	{
		snote.Format("Please fill retention time");
		AfxMessageBox(snote);
		return;
	}

	if(m_ToField+m_ToMarket+m_ToRemain<0.9999||m_ToField+m_ToMarket+m_ToRemain>1.0001)
	{
		snote.Format("The sum of fractions of the digester effluent must be equal to 1");
		AfxMessageBox(snote);
		return;
	}
	
	if(m_DigesterTempClass==0) m_DigesterCH4 = 0.12;//kg CH4-C/kg DM of manure 
	else if(m_DigesterTempClass==1) m_DigesterCH4 = 0.15;
	else if(m_DigesterTempClass==2) m_DigesterCH4 = 0.1875;
	else m_DigesterTempClass = 0.0;

	{
		CString SF;
		FILE* sf;
		SF.Format("%s\\Inter\\ManureDigester.txt", OUTPUT);
		sf=fopen(SF, "w");
		if(sf==NULL) note(1, SF);
		
		fprintf(sf, "%d  %f  %f\n", m_DigesterTempClass, m_DigesterCH4, m_RetentionDays);  
		fprintf(sf, "%f  %f  %f\n", m_ToField, m_ToMarket, m_ToRemain);
		fclose(sf);
	}

	CDialog::OnOK();
}

BOOL ManureDigester::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	float m_DigesterCH4, m_Remain;
	int m_unit;

	CString SF;
		FILE* sf;
		SF.Format("%s\\Inter\\ManureDigester.txt", OUTPUT);
		sf=fopen(SF, "r");
		if(sf==NULL)
		{		
			sf=fopen(SF, "w");
			fprintf(sf, "%d  %f  %f\n", 0, 0.0, 0.0);  
			fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
			fclose(sf);
			return(0);

			/*CString note;
			note.Format("Cannot open file %s", SF);
			AfxMessageBox(note);
			exit(0);*/
		}
		fscanf(sf, "%d  %f  %f\n", &m_DigesterTempClass, &m_DigesterCH4, &m_RetentionDays);  
		fscanf(sf, "%f  %f  %f\n", &m_ToField, &m_ToMarket, &m_ToRemain);
		fclose(sf);

	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Inter\\UnitSystem", OUTPUT);
	ddb=fopen(LB, "r");
	if(ddb==NULL) note(0, LB);
	fscanf(ddb, "%d", &m_unit);
	fclose(ddb);

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_T1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_T2);
		Edt->EnableWindow(TRUE); 		
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_T1);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_T2);
		Edt->EnableWindow(FALSE); 
	}	

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
