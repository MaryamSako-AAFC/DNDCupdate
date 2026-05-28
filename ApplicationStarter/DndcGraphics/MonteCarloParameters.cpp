// MonteCarloParameters.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "RunPaths.h"
#include "MonteCarloParameters.h"
#include "MonteCarloNote.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MonteCarloParameters dialog


MonteCarloParameters::MonteCarloParameters(CWnd* pParent /*=NULL*/)
	: CDialog(MonteCarloParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(MonteCarloParameters)
	m_1 = 0.0f;
	m_10 = 0.0f;
	m_11 = 0.0f;
	m_12 = 0.0f;
	m_13 = 0.0f;
	m_14 = 0.0f;
	m_15 = 0.0f;
	m_16 = 0.0f;
	m_17 = 0.0f;
	m_18 = 0.0f;
	m_19 = 0.0f;
	m_2 = 0.0f;
	m_20 = 0.0f;
	m_21 = 0.0f;
	m_22 = 0.0f;
	m_23 = 0.0f;
	m_24 = 0.0f;
	m_25 = 0.0f;
	m_26 = 0.0f;
	m_27 = 0.0f;
	m_28 = 0.0f;
	m_29 = 0.0f;
	m_3 = 0.0f;
	m_30 = 0.0f;
	m_31 = 0.0f;
	m_32 = 0.0f;
	m_33 = 0.0f;
	m_34 = 0.0f;
	m_35 = 0.0f;
	m_36 = 0.0f;
	m_37 = 0.0f;
	m_38 = 0.0f;
	m_39 = 0.0f;
	m_4 = 0.0f;
	m_40 = 0.0f;
	m_41 = 0.0f;
	m_42 = 0.0f;
	m_43 = 0.0f;
	m_44 = 0.0f;
	m_45 = 0.0f;
	m_46 = 0.0f;
	m_47 = 0.0f;
	m_48 = 0.0f;
	m_49 = 0.0f;
	m_5 = 0.0f;
	m_50 = 0.0f;
	m_51 = 0.0f;
	m_6 = 0.0f;
	m_7 = 0.0f;
	m_8 = 0.0f;
	m_9 = 0.0f;
	m_SampleSize = 0;
	m_C1 = FALSE;
	m_C10 = FALSE;
	m_C11 = FALSE;
	m_C12 = FALSE;
	m_C13 = FALSE;
	m_C14 = FALSE;
	m_C15 = FALSE;
	m_C16 = FALSE;
	m_C17 = FALSE;
	m_C18 = FALSE;
	m_C19 = FALSE;
	m_C2 = FALSE;
	m_C20 = FALSE;
	m_C21 = FALSE;
	m_C22 = FALSE;
	m_C23 = FALSE;
	m_C24 = FALSE;
	m_C25 = FALSE;
	m_C26 = FALSE;
	m_C27 = FALSE;
	m_C28 = FALSE;
	m_C29 = FALSE;
	m_C3 = FALSE;
	m_C30 = FALSE;
	m_C31 = FALSE;
	m_C32 = FALSE;
	m_C33 = FALSE;
	m_C34 = FALSE;
	m_C35 = FALSE;
	m_C36 = FALSE;
	m_C37 = FALSE;
	m_C38 = FALSE;
	m_C39 = FALSE;
	m_C4 = FALSE;
	m_C40 = FALSE;
	m_C41 = FALSE;
	m_C42 = FALSE;
	m_C43 = FALSE;
	m_C44 = FALSE;
	m_C45 = FALSE;
	m_C46 = FALSE;
	m_C47 = FALSE;
	m_C48 = FALSE;
	m_C49 = FALSE;
	m_C5 = FALSE;
	m_C50 = FALSE;
	m_C51 = FALSE;
	m_C6 = FALSE;
	m_C7 = FALSE;
	m_C8 = FALSE;
	m_C9 = FALSE;
	m_StartDay = 1;
	m_EndDay = 365;
	//}}AFX_DATA_INIT
}


void MonteCarloParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MonteCarloParameters)
	DDX_Text(pDX, IDC_EDIT1, m_1);
	DDX_Text(pDX, IDC_EDIT10, m_10);
	DDX_Text(pDX, IDC_EDIT11, m_11);
	DDX_Text(pDX, IDC_EDIT12, m_12);
	DDX_Text(pDX, IDC_EDIT13, m_13);
	DDX_Text(pDX, IDC_EDIT14, m_14);
	DDX_Text(pDX, IDC_EDIT15, m_15);
	DDX_Text(pDX, IDC_EDIT16, m_16);
	DDX_Text(pDX, IDC_EDIT17, m_17);
	DDX_Text(pDX, IDC_EDIT18, m_18);
	DDX_Text(pDX, IDC_EDIT19, m_19);
	DDX_Text(pDX, IDC_EDIT2, m_2);
	DDX_Text(pDX, IDC_EDIT20, m_20);
	DDX_Text(pDX, IDC_EDIT21, m_21);
	DDX_Text(pDX, IDC_EDIT22, m_22);
	DDX_Text(pDX, IDC_EDIT23, m_23);
	DDX_Text(pDX, IDC_EDIT24, m_24);
	DDX_Text(pDX, IDC_EDIT25, m_25);
	DDX_Text(pDX, IDC_EDIT26, m_26);
	DDX_Text(pDX, IDC_EDIT27, m_27);
	DDX_Text(pDX, IDC_EDIT28, m_28);
	DDX_Text(pDX, IDC_EDIT29, m_29);
	DDX_Text(pDX, IDC_EDIT3, m_3);
	DDX_Text(pDX, IDC_EDIT30, m_30);
	DDX_Text(pDX, IDC_EDIT31, m_31);
	DDX_Text(pDX, IDC_EDIT32, m_32);
	DDX_Text(pDX, IDC_EDIT33, m_33);
	DDX_Text(pDX, IDC_EDIT34, m_34);
	DDX_Text(pDX, IDC_EDIT35, m_35);
	DDX_Text(pDX, IDC_EDIT36, m_36);
	DDX_Text(pDX, IDC_EDIT37, m_37);
	DDX_Text(pDX, IDC_EDIT38, m_38);
	DDX_Text(pDX, IDC_EDIT39, m_39);
	DDX_Text(pDX, IDC_EDIT4, m_4);
	DDX_Text(pDX, IDC_EDIT40, m_40);
	DDX_Text(pDX, IDC_EDIT41, m_41);
	DDX_Text(pDX, IDC_EDIT42, m_42);
	DDX_Text(pDX, IDC_EDIT43, m_43);
	DDX_Text(pDX, IDC_EDIT44, m_44);
	DDX_Text(pDX, IDC_EDIT45, m_45);
	DDX_Text(pDX, IDC_EDIT46, m_46);
	DDX_Text(pDX, IDC_EDIT47, m_47);
	DDX_Text(pDX, IDC_EDIT48, m_48);
	DDX_Text(pDX, IDC_EDIT49, m_49);
	DDX_Text(pDX, IDC_EDIT5, m_5);
	DDX_Text(pDX, IDC_EDIT50, m_50);
	DDX_Text(pDX, IDC_EDIT51, m_51);
	DDX_Text(pDX, IDC_EDIT6, m_6);
	DDX_Text(pDX, IDC_EDIT7, m_7);
	DDX_Text(pDX, IDC_EDIT8, m_8);
	DDX_Text(pDX, IDC_EDIT9, m_9);
	DDX_Text(pDX, IDC_SampleSize, m_SampleSize);
	DDX_Check(pDX, IDC_CHECK1, m_C1);
	DDX_Check(pDX, IDC_CHECK10, m_C10);
	DDX_Check(pDX, IDC_CHECK11, m_C11);
	DDX_Check(pDX, IDC_CHECK12, m_C12);
	DDX_Check(pDX, IDC_CHECK13, m_C13);
	DDX_Check(pDX, IDC_CHECK14, m_C14);
	DDX_Check(pDX, IDC_CHECK15, m_C15);
	DDX_Check(pDX, IDC_CHECK16, m_C16);
	DDX_Check(pDX, IDC_CHECK17, m_C17);
	DDX_Check(pDX, IDC_CHECK18, m_C18);
	DDX_Check(pDX, IDC_CHECK19, m_C19);
	DDX_Check(pDX, IDC_CHECK2, m_C2);
	DDX_Check(pDX, IDC_CHECK20, m_C20);
	DDX_Check(pDX, IDC_CHECK21, m_C21);
	DDX_Check(pDX, IDC_CHECK22, m_C22);
	DDX_Check(pDX, IDC_CHECK23, m_C23);
	DDX_Check(pDX, IDC_CHECK24, m_C24);
	DDX_Check(pDX, IDC_CHECK25, m_C25);
	DDX_Check(pDX, IDC_CHECK26, m_C26);
	DDX_Check(pDX, IDC_CHECK27, m_C27);
	DDX_Check(pDX, IDC_CHECK28, m_C28);
	DDX_Check(pDX, IDC_CHECK29, m_C29);
	DDX_Check(pDX, IDC_CHECK3, m_C3);
	DDX_Check(pDX, IDC_CHECK30, m_C30);
	DDX_Check(pDX, IDC_CHECK31, m_C31);
	DDX_Check(pDX, IDC_CHECK32, m_C32);
	DDX_Check(pDX, IDC_CHECK33, m_C33);
	DDX_Check(pDX, IDC_CHECK34, m_C34);
	DDX_Check(pDX, IDC_CHECK35, m_C35);
	DDX_Check(pDX, IDC_CHECK36, m_C36);
	DDX_Check(pDX, IDC_CHECK37, m_C37);
	DDX_Check(pDX, IDC_CHECK38, m_C38);
	DDX_Check(pDX, IDC_CHECK39, m_C39);
	DDX_Check(pDX, IDC_CHECK4, m_C4);
	DDX_Check(pDX, IDC_CHECK40, m_C40);
	DDX_Check(pDX, IDC_CHECK41, m_C41);
	DDX_Check(pDX, IDC_CHECK42, m_C42);
	DDX_Check(pDX, IDC_CHECK43, m_C43);
	DDX_Check(pDX, IDC_CHECK44, m_C44);
	DDX_Check(pDX, IDC_CHECK45, m_C45);
	DDX_Check(pDX, IDC_CHECK46, m_C46);
	DDX_Check(pDX, IDC_CHECK47, m_C47);
	DDX_Check(pDX, IDC_CHECK48, m_C48);
	DDX_Check(pDX, IDC_CHECK49, m_C49);
	DDX_Check(pDX, IDC_CHECK5, m_C5);
	DDX_Check(pDX, IDC_CHECK50, m_C50);
	DDX_Check(pDX, IDC_CHECK51, m_C51);
	DDX_Check(pDX, IDC_CHECK6, m_C6);
	DDX_Check(pDX, IDC_CHECK7, m_C7);
	DDX_Check(pDX, IDC_CHECK8, m_C8);
	DDX_Check(pDX, IDC_CHECK9, m_C9);
	DDX_Text(pDX, IDC_StartDay, m_StartDay);
	DDX_Text(pDX, IDC_EndDay, m_EndDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MonteCarloParameters, CDialog)
	//{{AFX_MSG_MAP(MonteCarloParameters)
	ON_BN_CLICKED(IDC_Confirm, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MonteCarloParameters message handlers

BOOL MonteCarloParameters::OnInitDialog() 
{
	MonteCarloNote ww;
	if(ww.DoModal()==IDOK)
	{

	}
	else exit(0);

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CEdit *Edt;
		
	Edt=(CEdit *)GetDlgItem(IDC_EDIT1);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT2);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT3);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT4);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT5);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT6);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT7);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT8);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT9);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT10);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT11);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT12);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT13);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT14);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT15);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT16);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT17);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT18);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT19);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT20);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT21);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT22);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT23);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT24);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT25);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT26);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT27);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT28);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT29);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT30);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT31);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT32);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT33);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT34);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT35);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT36);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT37);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT38);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT39);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT40);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT41);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT42);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT43);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT44);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT45);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT46);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT47);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT48);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT49);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT50);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_EDIT51);
	Edt->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MonteCarloParameters::OnConfirm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int SSSS=0;

	CEdit *Edt;

	Edt=(CEdit *)GetDlgItem(IDC_EDIT1);
	if(m_C1==1) {Edt->EnableWindow(TRUE); SSSS++; m_1=0.1;}
	else Edt->EnableWindow(FALSE);

	Edt=(CEdit *)GetDlgItem(IDC_EDIT2);
	if(m_C2==1) {Edt->EnableWindow(TRUE); SSSS++; m_2=0.1;}
	else Edt->EnableWindow(FALSE);

	Edt=(CEdit *)GetDlgItem(IDC_EDIT3);
	if(m_C3==1) {Edt->EnableWindow(TRUE); SSSS++;m_3 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT4);
	if(m_C4==1) {Edt->EnableWindow(TRUE); SSSS++;m_4 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT5);
	if(m_C5==1) {Edt->EnableWindow(TRUE); SSSS++;m_5 = 0.5;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT6);
	if(m_C6==1) {Edt->EnableWindow(TRUE); SSSS++;m_6 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT7);
	if(m_C7==1) {Edt->EnableWindow(TRUE); SSSS++;m_7= 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT8);
	if(m_C8==1) {Edt->EnableWindow(TRUE); SSSS++;m_8 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT9);
	if(m_C9==1) {Edt->EnableWindow(TRUE); SSSS++;m_9 = 0.15;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT10);
	if(m_C10==1) {Edt->EnableWindow(TRUE); SSSS++;m_10 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT11);
	if(m_C11==1) {Edt->EnableWindow(TRUE); SSSS++;m_11 = 0.15;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT12);
	if(m_C12==1) {Edt->EnableWindow(TRUE); SSSS++;m_12 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT13);
	if(m_C13==1) {Edt->EnableWindow(TRUE); SSSS++;m_13 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT14);
	if(m_C14==1) {Edt->EnableWindow(TRUE); SSSS++;m_14 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT15);
	if(m_C15==1) {Edt->EnableWindow(TRUE); SSSS++;m_15 = 0.5;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT16);
	if(m_C16==1) {Edt->EnableWindow(TRUE); SSSS++;m_16 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT17);
	if(m_C17==1) {Edt->EnableWindow(TRUE); SSSS++;m_17 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT18);
	if(m_C18==1) {Edt->EnableWindow(TRUE); SSSS++;m_18 = 0.15;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT19);
	if(m_C19==1) {Edt->EnableWindow(TRUE); SSSS++;m_19 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT20);
	if(m_C20==1) {Edt->EnableWindow(TRUE); SSSS++;m_20 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT21);
	if(m_C21==1) {Edt->EnableWindow(TRUE); SSSS++;m_21 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT22);
	if(m_C22==1) {Edt->EnableWindow(TRUE); SSSS++;m_22 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT23);
	if(m_C23==1) {Edt->EnableWindow(TRUE); SSSS++;m_23 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT24);
	if(m_C24==1) {Edt->EnableWindow(TRUE); SSSS++;m_24 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT25);
	if(m_C25==1) {Edt->EnableWindow(TRUE); SSSS++;m_25 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT26);
	if(m_C26==1) {Edt->EnableWindow(TRUE); SSSS++;m_26 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT27);
	if(m_C27==1) {Edt->EnableWindow(TRUE); SSSS++;m_27 = 0.3;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT28);
	if(m_C28==1) {Edt->EnableWindow(TRUE); SSSS++;m_28 = 0.2;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT29);
	if(m_C29==1) {Edt->EnableWindow(TRUE); SSSS++;m_29 = 5.0;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT30);
	if(m_C30==1) {Edt->EnableWindow(TRUE); SSSS++;m_30 = 0.05;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT31);
	if(m_C31==1) {Edt->EnableWindow(TRUE); SSSS++;m_31 = 5.0;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT32);
	if(m_C32==1) {Edt->EnableWindow(TRUE); SSSS++;m_32 = 0.05;}
	else Edt->EnableWindow(FALSE);
		
	Edt=(CEdit *)GetDlgItem(IDC_EDIT33);
	if(m_C33==1) {Edt->EnableWindow(TRUE); SSSS++;m_33 = 0.15;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT34);
	if(m_C34==1) {Edt->EnableWindow(TRUE); SSSS++;m_34 = 5.0;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT35);
	if(m_C35==1) {Edt->EnableWindow(TRUE); SSSS++;m_35 = 0.2;}
	else Edt->EnableWindow(FALSE);
		
	Edt=(CEdit *)GetDlgItem(IDC_EDIT36);
	if(m_C36==1) {Edt->EnableWindow(TRUE); SSSS++;m_36 = 0.3;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT37);
	if(m_C37==1) {Edt->EnableWindow(TRUE); SSSS++;m_37 = 0.3;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT38);
	if(m_C38==1) {Edt->EnableWindow(TRUE); SSSS++;m_38 = 0.05;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT39);
	if(m_C39==1) {Edt->EnableWindow(TRUE); SSSS++;m_39 = 0.05;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT40);
	if(m_C40==1) {Edt->EnableWindow(TRUE); SSSS++;m_40 = 0.05;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT41);
	if(m_C41==1) {Edt->EnableWindow(TRUE); SSSS++;m_41 = 0.05;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT42);
	if(m_C42==1) {Edt->EnableWindow(TRUE); SSSS++;m_42 = 5.0;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT43);
	if(m_C43==1) {Edt->EnableWindow(TRUE); SSSS++;m_43 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT44);
	if(m_C44==1) {Edt->EnableWindow(TRUE); SSSS++;m_44 = 0.03;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT45);
	if(m_C45==1) {Edt->EnableWindow(TRUE); SSSS++;m_45 = 0.5;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT46);
	if(m_C46==1) {Edt->EnableWindow(TRUE); SSSS++;m_46 = 0.1;}
	else Edt->EnableWindow(FALSE);
	
	Edt=(CEdit *)GetDlgItem(IDC_EDIT47);
	if(m_C47==1) {Edt->EnableWindow(TRUE); SSSS++;m_47 = 0.2;}
	else Edt->EnableWindow(FALSE);

	Edt=(CEdit *)GetDlgItem(IDC_EDIT48);
	if(m_C48==1) {Edt->EnableWindow(TRUE); SSSS++;m_48 = 0.2;}
	else Edt->EnableWindow(FALSE);

	Edt=(CEdit *)GetDlgItem(IDC_EDIT49);
	if(m_C49==1) {Edt->EnableWindow(TRUE); SSSS++;m_49 = 0.1;}
	else Edt->EnableWindow(FALSE);

	Edt=(CEdit *)GetDlgItem(IDC_EDIT50);
	if(m_C50==1) {Edt->EnableWindow(TRUE); SSSS++;m_50 = 0.1;}
	else Edt->EnableWindow(FALSE);

	Edt=(CEdit *)GetDlgItem(IDC_EDIT51);
	if(m_C51==1) {Edt->EnableWindow(TRUE); SSSS++;m_51 = 0.1;}
	else Edt->EnableWindow(FALSE);

	int MMCC=(int)powf(8.0, (float)SSSS);//8

	MMCC = max(4000, MMCC);

	//CString note;
	//note.Format("You have selected %d parameters. The default total number of Monte Carlo simulations is %d", SSSS, MMCC);
	//AfxMessageBox(note);

	m_SampleSize = MMCC;

	UpdateData(FALSE);
}

void MonteCarloParameters::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int k=0, item[55]={0,0};
	float value[55]={0.0,0.0};

	if(m_C1==1) {k++; item[k]=1; value[k]=m_1;}
	if(m_C2==1) {k++; item[k]=2; value[k]=m_2;}
	if(m_C3==1) {k++; item[k]=3; value[k]=m_3;}
	if(m_C4==1) {k++; item[k]=4; value[k]=m_4;}
	if(m_C5==1) {k++; item[k]=5; value[k]=m_5;}
	if(m_C6==1) {k++; item[k]=6; value[k]=m_6;}
	if(m_C7==1) {k++; item[k]=7; value[k]=m_7;}
	if(m_C8==1) {k++; item[k]=8; value[k]=m_8;}
	if(m_C9==1) {k++; item[k]=9; value[k]=m_9;}
	if(m_C10==1) {k++; item[k]=10; value[k]=m_10;}
	if(m_C11==1) {k++; item[k]=11; value[k]=m_11;}
	if(m_C12==1) {k++; item[k]=12; value[k]=m_12;}
	if(m_C13==1) {k++; item[k]=13; value[k]=m_13;}
	if(m_C14==1) {k++; item[k]=14; value[k]=m_14;}
	if(m_C15==1) {k++; item[k]=15; value[k]=m_15;}
	if(m_C16==1) {k++; item[k]=16; value[k]=m_16;}
	if(m_C17==1) {k++; item[k]=17; value[k]=m_17;}
	if(m_C18==1) {k++; item[k]=18; value[k]=m_18;}
	if(m_C19==1) {k++; item[k]=19; value[k]=m_19;}
	if(m_C20==1) {k++; item[k]=20; value[k]=m_20;}
	if(m_C21==1) {k++; item[k]=21; value[k]=m_21;}
	if(m_C22==1) {k++; item[k]=22; value[k]=m_22;}
	if(m_C23==1) {k++; item[k]=23; value[k]=m_23;}
	if(m_C24==1) {k++; item[k]=24; value[k]=m_24;}
	if(m_C25==1) {k++; item[k]=25; value[k]=m_25;}
	if(m_C26==1) {k++; item[k]=26; value[k]=m_26;}
	if(m_C27==1) {k++; item[k]=27; value[k]=m_27;}
	if(m_C28==1) {k++; item[k]=28; value[k]=m_28;}
	if(m_C29==1) {k++; item[k]=29; value[k]=m_29;}
	if(m_C30==1) {k++; item[k]=30; value[k]=m_30;}
	if(m_C31==1) {k++; item[k]=31; value[k]=m_31;}
	if(m_C32==1) {k++; item[k]=32; value[k]=m_32;}
	if(m_C33==1) {k++; item[k]=33; value[k]=m_33;}
	if(m_C34==1) {k++; item[k]=34; value[k]=m_34;}
	if(m_C35==1) {k++; item[k]=35; value[k]=m_35;}
	if(m_C36==1) {k++; item[k]=36; value[k]=m_36;}
	if(m_C37==1) {k++; item[k]=37; value[k]=m_37;}
	if(m_C38==1) {k++; item[k]=38; value[k]=m_38;}
	if(m_C39==1) {k++; item[k]=39; value[k]=m_39;}
	if(m_C40==1) {k++; item[k]=40; value[k]=m_40;}
	if(m_C41==1) {k++; item[k]=41; value[k]=m_41;}
	if(m_C42==1) {k++; item[k]=42; value[k]=m_42;}
	if(m_C43==1) {k++; item[k]=43; value[k]=m_43;}
	if(m_C44==1) {k++; item[k]=44; value[k]=m_44;}
	if(m_C45==1) {k++; item[k]=45; value[k]=m_45;}
	if(m_C46==1) {k++; item[k]=46; value[k]=m_46;}
	if(m_C47==1) {k++; item[k]=47; value[k]=m_47;}
	if(m_C48==1) {k++; item[k]=48; value[k]=m_48;}
	if(m_C49==1) {k++; item[k]=49; value[k]=m_49;}
	if(m_C50==1) {k++; item[k]=50; value[k]=m_50;}
	if(m_C51==1) {k++; item[k]=51; value[k]=m_51;}

	CString SMC;
	FILE *smc;
	SMC.Format("%s\\Inter\\SiteMonteCarlo", OUTPUT);
	smc=fopen(SMC, "w");
	if(smc==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", SMC);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(smc, "%d %d\n", k, m_SampleSize);
	for(int i=1; i<=k; i++)
		fprintf(smc, "%d %f\n", item[i], value[i]);
	fprintf(smc, "%d %d\n", m_StartDay, m_EndDay);
	fclose(smc);
	
	CDialog::OnOK();
}
