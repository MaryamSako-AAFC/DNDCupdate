// SCSDlg.cpp : implementation file
//
#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "dndc_main.h"
#include "SCSDlg.h"
#include "RunoffCN.h"
#include "SitePage2.h"
#include "dndc_ManningLand.h"
#include "dndc_ManningChannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Site_BaseInformation	IData;

/////////////////////////////////////////////////////////////////////////////
// CSCSDlg dialog


CSCSDlg::CSCSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSCSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSCSDlg)
	m_CN = 78.0f;
	m_FCSCS = 0.0f;
	m_ProSCS = 0.0f;
	m_SlopeSCS = 0.0f;
	m_WPSCS = 0.0f;
	m_WatershedArea = 0.0f;
	m_RoughLand = 0.0f;
	m_RoughChannel = 0.0f;
	m_SlopeLength = 0.0f;
	m_ChannelSlope = 0.0f;
	m_ChannelLength = 0.0f;
	m_LandManage = 0.0f;
	//}}AFX_DATA_INIT
}


void CSCSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSCSDlg)
	DDX_Text(pDX, IDC_CN, m_CN);
	DDV_MinMaxFloat(pDX, m_CN, 0.f, 100.f);
	DDX_Text(pDX, IDC_FCSCS, m_FCSCS);
	DDX_Text(pDX, IDC_PROSCS, m_ProSCS);
	DDX_Text(pDX, IDC_Slope, m_SlopeSCS);
	DDV_MinMaxFloat(pDX, m_SlopeSCS, 0.f, 90.f);
	DDX_Text(pDX, IDC_WPSCS, m_WPSCS);
	DDX_Text(pDX, IDC_WatershedArea, m_WatershedArea);
	DDX_Text(pDX, IDC_RoughLand, m_RoughLand);
	DDX_Text(pDX, IDC_RoughChannel, m_RoughChannel);
	DDX_Text(pDX, IDC_SlopeLength, m_SlopeLength);
	DDX_Text(pDX, IDC_ChannelSlope, m_ChannelSlope);
	DDX_Text(pDX, IDC_ChannelLength, m_ChannelLength);
	DDX_Text(pDX, IDC_LandManage, m_LandManage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSCSDlg, CDialog)
	//{{AFX_MSG_MAP(CSCSDlg)
	ON_BN_CLICKED(IDC_OK, OnSCSOk)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_FindCN, OnFindCN)
	ON_BN_CLICKED(IDC_ReadCN, OnReadCN)
	ON_BN_CLICKED(IDC_LandRough, OnLandRough)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_ChannelRough2, OnChannelRough2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCSDlg message handlers

void CSCSDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
    EndDialog(IDCANCEL);	
}

void CSCSDlg::OnSCSOk() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	if(m_CN==0)
	{
		AfxMessageBox("Please define the CN");
		return;
	}

	if(m_RoughLand<=0.0)
	{
		AfxMessageBox("Please define the Manning's roughness coefficient for overland flow");
		return;
	}
	
	if(m_SlopeSCS==0)
	{
		AfxMessageBox("Note: The land surface slope is defined to be 0");
		//return;
	}

	m_WatershedArea = 1.0;//ha
	m_SlopeLength = 100.0; //m

    char scs[120];
    FILE *scspara;
    sprintf(scs,"%s\\Inputs\\scspara", OUTPUT);
    scspara=fopen(scs, "w");
    if(scspara==NULL) note(1, scs); 
	fprintf(scspara, "%f %f %f %f %f %f\n", m_CN, m_RoughLand, m_RoughChannel, m_ChannelSlope, m_ChannelLength, m_LandManage);
    fclose(scspara);

	EndDialog(IDOK);
}

void CSCSDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//RunoffCN ww;
	//ww.DoModal();

	CDialog::OnRButtonDown(nFlags, point);
}

BOOL CSCSDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SlopeSCS = IData.slope;

	char scs[120];
    FILE *scspara;
    sprintf(scs,"%s\\Inputs\\scspara", OUTPUT);
    scspara=fopen(scs, "r");
    if(scspara==NULL) 
	{
		m_CN=0.0;
		m_RoughLand=0.0;
		m_RoughChannel=0.0;
		m_ChannelSlope=0.0;
		m_ChannelLength=0.0;
		m_LandManage=0.0;
		scspara=fopen(scs, "w");
		fprintf(scspara, "%f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0,	0.0, 0.0);
		fclose(scspara);
	} 
	else
	{
		fscanf(scspara, "%f %f %f %f %f %f\n", &m_CN, &m_RoughLand, &m_RoughChannel, &m_ChannelSlope, 
											&m_ChannelLength, &m_LandManage);
		fclose(scspara);
	}


/*	m_ProSCS = 0.5 * 1000.0 * IData.Soil_Porosity;
	m_FCSCS = m_ProSCS * IData.Fldcap;
	m_WPSCS = m_ProSCS * IData.Wiltpt;
*/
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSCSDlg::OnFindCN() 
{
	// TODO: Add your control notification handler code here
	
}

void CSCSDlg::OnReadCN() 
{
	// TODO: Add your control notification handler code here
	RunoffCN ww;
	ww.DoModal();
}

void CSCSDlg::OnLandRough() 
{
	// TODO: Add your control notification handler code here
	Dndc_ManningLand ww;
	ww.DoModal();
}

void CSCSDlg::OnChannelRough2() 
{
	// TODO: Add your control notification handler code here
	Dndc_ManningChannel ww;
	if(ww.DoModal()==IDOK)
	{
	/*	CString FF;
		FILE* ff;

		FF.Format("%s\\inter\\ManningVhannel",OUTPUT);
		ff=fopen(FF, "r");
		if(ff==NULL) note(1, FF);
		fscanf(ff, "%f", m_RoughChannel);
		fclose(ff);

		UpdateData(FALSE);*/
	}
	
}
