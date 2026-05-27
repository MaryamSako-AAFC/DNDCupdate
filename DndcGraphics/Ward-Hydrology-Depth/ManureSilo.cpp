// ManureSilo.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ManureSilo.h"
#include "Dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManureSilo dialog


ManureSilo::ManureSilo(CWnd* pParent /*=NULL*/)
	: CDialog(ManureSilo::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureSilo)
	m_SiloType = -1;
	m_FeedType = -1;
	m_BunckLength = 0.0f;
	m_Diameter = 0.0f;
	m_Height = 0.0f;
	m_SilageAmount = 0.0f;
	m_SiloNumber = -1;
	m_DryFraction = 0.0f;
	m_FeedMixer = -1;
	//}}AFX_DATA_INIT
}


void ManureSilo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureSilo)
	DDX_CBIndex(pDX, IDC_SiloType, m_SiloType);
	DDX_CBIndex(pDX, IDC_FeedType, m_FeedType);
	DDX_Text(pDX, IDC_BunckLength, m_BunckLength);
	DDX_Text(pDX, IDC_Doameter, m_Diameter);
	DDX_Text(pDX, IDC_Height, m_Height);
	DDX_Text(pDX, IDC_SilageAmount, m_SilageAmount);
	DDX_CBIndex(pDX, IDC_SiloNumber, m_SiloNumber);
	DDX_Text(pDX, IDC_DryFraction, m_DryFraction);
	DDX_CBIndex(pDX, IDC_FeedMixer, m_FeedMixer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureSilo, CDialog)
	//{{AFX_MSG_MAP(ManureSilo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureSilo message handlers

void ManureSilo::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString SilF;
	FILE* silf;
	SilF.Format("%s\\Silage", INTER);
	silf = fopen(SilF, "w");
	if(silf==NULL) note(0, SilF);
	fprintf(silf, "%d %d %d %d\n", m_SiloType+1, m_SiloNumber+1, m_FeedType+1, m_FeedMixer+1);
	fprintf(silf, "%f %f %f %f %f\n", m_BunckLength, m_Diameter, m_Height, m_SilageAmount, m_DryFraction);
	fclose(silf);

	CDialog::OnOK();
}
