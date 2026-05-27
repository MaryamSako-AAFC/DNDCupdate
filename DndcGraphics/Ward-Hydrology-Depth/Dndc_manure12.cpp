// Dndc_manure12.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "Dndc_manure12.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dndc_manure12 dialog


Dndc_manure12::Dndc_manure12(CWnd* pParent /*=NULL*/)
	: CDialog(Dndc_manure12::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dndc_manure12)
	m_StorageDays = 0;
	m_StoreToCompost = 0.0f;
	m_StoreToDigester = 0.0f;
	m_StoreToField = 0.0f;
	m_StoreToLagoon = 0.0f;
	//}}AFX_DATA_INIT
}


void Dndc_manure12::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dndc_manure12)
	DDX_Text(pDX, IDC_StorageDays, m_StorageDays);
	DDX_Text(pDX, IDC_StoryToCompost, m_StoreToCompost);
	DDX_Text(pDX, IDC_StoryToDigester, m_StoreToDigester);
	DDX_Text(pDX, IDC_StoryToField, m_StoreToField);
	DDX_Text(pDX, IDC_StoryToLagoon, m_StoreToLagoon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dndc_manure12, CDialog)
	//{{AFX_MSG_MAP(Dndc_manure12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dndc_manure12 message handlers

void Dndc_manure12::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	float TT = m_StoreToCompost + m_StoreToDigester + m_StoreToField + m_StoreToLagoon;

	if(TT!=1.0)
	{
		CString NN;
		NN.Format("Please make the sum of distribution factions to be 1");
		AfxMessageBox(NN);
		return;
	}

	CString SF;
	FILE* sf;
	SF.Format("%s\\Result\\Inter\\ManureStorage.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);	
	
	fprintf(sf, "%d  %d %f %f %f\n", m_StorageDays, m_StoreToCompost, m_StoreToDigester, m_StoreToField, m_StoreToLagoon);
	fclose(sf);
	
	CDialog::OnOK();
}
