// ManureField.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "ManureField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManureField dialog


ManureField::ManureField(CWnd* pParent /*=NULL*/)
	: CDialog(ManureField::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureField)
	m_FieldArea = 0.0f;
	m_unit = 0;
	//}}AFX_DATA_INIT
}


void ManureField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureField)
	DDX_Text(pDX, IDC_FieldArea, m_FieldArea);
	DDX_Radio(pDX, IDC_unit, m_unit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureField, CDialog)
	//{{AFX_MSG_MAP(ManureField)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureField message handlers

void ManureField::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	//unit conversion
	float FieldArea;
	if(m_unit==0)
	{
		FieldArea = m_FieldArea;
	}
	else
	{
		FieldArea = m_FieldArea * ac_ha;//ac -> ha
	}

	if(m_FieldArea<=0.0)
	{
		CString note;
		note.Format("Please specify field area");
		AfxMessageBox(note);
		return;
	}

	CString SF;
		FILE* sf;
		SF.Format("%s\\Inter\\ManureField.txt", OUTPUT);
		sf=fopen(SF, "w");
		
		fprintf(sf, "%f", FieldArea);    
		fclose(sf);

	CDialog::OnOK();
}

BOOL ManureField::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);

	CString SF;
	FILE* sf;
	SF.Format("%s\\Result\\Inter\\ManureField.txt", ROOTDIR);
	sf=fopen(SF, "r");
	if(sf==NULL)
	{
		sf=fopen(SF, "w");
		fprintf(sf, "%f", 0.0);    
		fclose(sf);
		return(0);
	}
	fscanf(sf, "%f", &m_FieldArea);    
	fclose(sf);
	
	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "r");
	if(ddb==NULL)
	{
		ddb=fopen(LB, "w");
		fprintf(ddb, "%d", 0);    
		fclose(ddb);
		return(0);
	}
	
	fscanf(ddb, "%d", &m_unit);
	fclose(ddb);

	if(m_unit==1)
	{
		m_FieldArea /= ac_ha;//ha -> acre 		
	}

	UpdateData(FALSE);

	//Onunit2();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ManureField::Onunit() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==0&&n_unit==1) 
	{
		m_FieldArea *= ac_ha;//ac -> ha 
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);*/
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);*/
	}

	UpdateData(FALSE);
}

void ManureField::Onunit2() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==1&&n_unit==0) 
	{
		m_FieldArea /= ac_ha;//ha -> ac
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);*/
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		/*Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);*/
	}

	UpdateData(FALSE);
}
