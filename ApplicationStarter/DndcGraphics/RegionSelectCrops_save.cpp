// RegionSelectCrops.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "RegionSelectCrops.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RegionSelectCrops dialog


RegionSelectCrops::RegionSelectCrops(CWnd* pParent /*=NULL*/)
	: CDialog(RegionSelectCrops::IDD, pParent)
{
	//{{AFX_DATA_INIT(RegionSelectCrops)
	m_0 = FALSE;
	m_9 = FALSE;
	m_10 = FALSE;
	m_11 = FALSE;
	m_12 = FALSE;
	m_13 = FALSE;
	m_14 = FALSE;
	m_15 = FALSE;
	m_16 = FALSE;
	m_17 = FALSE;
	m_18 = FALSE;
	m_1 = FALSE;
	m_19 = FALSE;
	m_20 = FALSE;
	m_21 = FALSE;
	m_22 = FALSE;
	m_23 = FALSE;
	m_24 = FALSE;
	m_25 = FALSE;
	m_26 = FALSE;
	m_27 = FALSE;
	m_28 = FALSE;
	m_2 = FALSE;
	m_29 = FALSE;
	m_30 = FALSE;
	m_31 = FALSE;
	m_32 = FALSE;
	m_33 = FALSE;
	m_34 = FALSE;
	m_35 = FALSE;
	m_36 = FALSE;
	m_37 = FALSE;
	m_38 = FALSE;
	m_3 = FALSE;
	m_39 = FALSE;
	m_40 = FALSE;
	m_41 = FALSE;
	m_42 = FALSE;
	m_4 = FALSE;
	m_5 = FALSE;
	m_6 = FALSE;
	m_7 = FALSE;
	m_8 = FALSE;
	m_00 = FALSE;
	//}}AFX_DATA_INIT
}


void RegionSelectCrops::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RegionSelectCrops)
	DDX_Check(pDX, IDC_CHECK1, m_0);
	DDX_Check(pDX, IDC_CHECK10, m_9);
	DDX_Check(pDX, IDC_CHECK11, m_10);
	DDX_Check(pDX, IDC_CHECK12, m_11);
	DDX_Check(pDX, IDC_CHECK13, m_12);
	DDX_Check(pDX, IDC_CHECK14, m_13);
	DDX_Check(pDX, IDC_CHECK15, m_14);
	DDX_Check(pDX, IDC_CHECK16, m_15);
	DDX_Check(pDX, IDC_CHECK17, m_16);
	DDX_Check(pDX, IDC_CHECK18, m_17);
	DDX_Check(pDX, IDC_CHECK19, m_18);
	DDX_Check(pDX, IDC_CHECK2, m_1);
	DDX_Check(pDX, IDC_CHECK20, m_19);
	DDX_Check(pDX, IDC_CHECK21, m_20);
	DDX_Check(pDX, IDC_CHECK22, m_21);
	DDX_Check(pDX, IDC_CHECK23, m_22);
	DDX_Check(pDX, IDC_CHECK24, m_23);
	DDX_Check(pDX, IDC_CHECK25, m_24);
	DDX_Check(pDX, IDC_CHECK26, m_25);
	DDX_Check(pDX, IDC_CHECK27, m_26);
	DDX_Check(pDX, IDC_CHECK28, m_27);
	DDX_Check(pDX, IDC_CHECK29, m_28);
	DDX_Check(pDX, IDC_CHECK3, m_2);
	DDX_Check(pDX, IDC_CHECK30, m_29);
	DDX_Check(pDX, IDC_CHECK31, m_30);
	DDX_Check(pDX, IDC_CHECK32, m_31);
	DDX_Check(pDX, IDC_CHECK33, m_32);
	DDX_Check(pDX, IDC_CHECK34, m_33);
	DDX_Check(pDX, IDC_CHECK35, m_34);
	DDX_Check(pDX, IDC_CHECK36, m_35);
	DDX_Check(pDX, IDC_CHECK37, m_36);
	DDX_Check(pDX, IDC_CHECK38, m_37);
	DDX_Check(pDX, IDC_CHECK39, m_38);
	DDX_Check(pDX, IDC_CHECK4, m_3);
	DDX_Check(pDX, IDC_CHECK40, m_39);
	DDX_Check(pDX, IDC_CHECK41, m_40);
	DDX_Check(pDX, IDC_CHECK42, m_41);
	DDX_Check(pDX, IDC_CHECK43, m_42);
	DDX_Check(pDX, IDC_CHECK5, m_4);
	DDX_Check(pDX, IDC_CHECK6, m_5);
	DDX_Check(pDX, IDC_CHECK7, m_6);
	DDX_Check(pDX, IDC_CHECK8, m_7);
	DDX_Check(pDX, IDC_CHECK9, m_8);
	DDX_Check(pDX, IDC_CHECK0, m_00);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RegionSelectCrops, CDialog)
	//{{AFX_MSG_MAP(RegionSelectCrops)
	ON_BN_CLICKED(IDC_CHECK0, OnCheck0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RegionSelectCrops message handlers

void RegionSelectCrops::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int SC[150];
	int i, j;

	for(i=0; i<=149; i++) SC[i] = -1;

	CString SCF;
	FILE *scf;
	SCF.Format("%s\\Inter\\RegionSelectCrops.txt", OUTPUT);
	scf=fopen(SCF, "w");
	if(scf==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", SCF);
		AfxMessageBox(note);
		exit(0);
	}

	if(m_0==1) 
	{
		SC[0] = 0;
	}
	else SC[0] = -1;
	
	if(m_1==1) 
	{
		SC[1] = 1;
		SC[51] = 51;
		SC[57] = 57;
		SC[59] = 59;
		SC[61] = 61;
		SC[68] = 68;
		SC[74] = 74;
	}
	else SC[1] = -1;
	
	if(m_2==1) 
	{
		SC[2] = 2;
		SC[51] = 51;
		SC[53] = 53;
		SC[55] = 55;
		SC[56] = 56;
		SC[62] = 62;
		SC[66] = 66;
		SC[67] = 67;
		SC[79] = 79;
	}
	else SC[2] = -1;
	
	if(m_3==1) 
	{
		SC[3] = 3;
		SC[61] = 61;
		SC[62] = 62;
		SC[64] = 64;
		SC[65] = 65;
		SC[69] = 69;
		SC[71] = 71;
		SC[72] = 72;
	}
	else SC[3] = -1;
	
	if(m_4==1) 
	{
		SC[4] = 4;
		SC[76] = 76;
	}
	else SC[4] = -1;
	
	if(m_5==1) 
	{
		SC[5] = 5;
		SC[65] = 65;
	}
	else SC[5] = -1;

	if(m_6==1) 
	{
		SC[6] = 6;
	}
	else SC[6] = -1;

	if(m_7==1) 
	{
		SC[7] = 7;
	}
	else SC[7] = -1;

	if(m_8==1) 
	{
		SC[8] = 8;
	}
	else SC[8] = -1;

	if(m_9==1) 
	{
		SC[9] = 9;
		SC[63] = 63;
		SC[71] = 71;
	}
	else SC[9] = -1;

	if(m_10==1) 
	{
		SC[10] = 10;
	}
	else SC[10] = -1;

	if(m_11==1) 
	{
		SC[11] = 11;
	}
	else SC[11] = -1;

	if(m_12==1) 
	{
		SC[12] = 12;
	}
	else SC[12] = -1;

	if(m_13==1) 
	{
		SC[13] = 13;
	}
	else SC[13] = -1;

	if(m_14==1) 
	{
		SC[14] = 14;
		SC[67] = 67;
	}
	else SC[14] = -1;

	if(m_15==1) 
	{
		SC[15] = 15;
	}
	else SC[15] = -1;

	if(m_16==1) 
	{
		SC[16] = 16;
		SC[56] = 56;
		SC[58] = 58;
		SC[59] = 59;
		SC[60] = 60;
		SC[75] = 75;
		SC[78] = 78;
		SC[80] = 80;
	}
	else SC[16] = -1;

	if(m_17==1) 
	{
		SC[17] = 17;
	}
	else SC[17] = -1;

	if(m_18==1) 
	{
		SC[18] = 18;
		SC[64] = 64;
		SC[66] = 66;
		SC[68] = 68;
		SC[73] = 73;
		SC[78] = 78;
	}
	else SC[18] = -1;

	if(m_19==1) 
	{
		SC[19] = 19;
	}
	else SC[19] = -1;

	if(m_20==1) 
	{
		SC[20] = 20;
		SC[52] = 52;
		SC[54] = 54;
		SC[55] = 55;
		SC[60] = 60;
		SC[63] = 63;
		SC[72] = 72;
		SC[76] = 76;
		SC[77] = 77;
		SC[79] = 79;
		SC[80] = 80;
	}
	else SC[20] = -1;

	if(m_21==1) 
	{
		SC[21] = 21;
	}
	else SC[21] = -1;

	if(m_22==1) 
	{
		SC[22] = 22;
	}
	else SC[22] = -1;

	if(m_23==1) 
	{
		SC[23] = 23;
	}
	else SC[23] = -1;

	if(m_24==1) 
	{
		SC[24] = 24;
	}
	else SC[24] = -1;

	if(m_25==1) 
	{
		SC[25] = 25;
		SC[52] = 52;
		SC[53] = 53;
		SC[57] = 57;
		SC[58] = 58;
		SC[69] = 69;
		SC[70] = 70;
		SC[77] = 77;
	}
	else SC[25] = -1;

	if(m_26==1) 
	{
		SC[26] = 26;
	}
	else SC[26] = -1;

	if(m_27==1) SC[27]=27;
	if(m_28==1) SC[28]=28;
	if(m_29==1) SC[29]=29;
	if(m_30==1) SC[30]=30;
	if(m_31==1) SC[31]=31;
	if(m_32==1) SC[32]=32;
	if(m_33==1) SC[33]=33;
	if(m_34==1) SC[34]=34;
	if(m_35==1) SC[35]=35;
	if(m_36==1) SC[36]=36;
	if(m_37==1) SC[37]=37;
	if(m_38==1) SC[38]=38;
	if(m_39==1) SC[39]=39;
	if(m_40==1) SC[40]=40;
	if(m_41==1) SC[41]=41;
	if(m_42==1) SC[42]=42;

	j=0;
	for(i=0; i<=80; i++) 
	{
		if(SC[i]!=-1) j++;
	}

	if(m_00==1)
	{
		fprintf(scf, "%d\n", 0);
	}
	else
	{
		fprintf(scf, "%d\n", j);
		for(i=0; i<=80; i++) 
		{
			if(SC[i]!=-1) fprintf(scf, "%d\n", SC[i]);
		}
	}
	fclose(scf);
		
	CDialog::OnOK();
}

void RegionSelectCrops::OnCheck0() 
{
	// TODO: Add your control notification handler code here
	if(m_00==0)
	{
		m_00 = 1;
		CEdit *Edt;
		
		Edt=(CEdit *)GetDlgItem(IDC_CHECK1);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK3);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK4);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK5);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK6);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK7);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK8);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK9);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK10);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK11);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK12);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK13);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK14);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK15);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK16);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK17);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK18);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK19);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK20);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK21);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK22);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK23);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK24);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK25);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK26);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK27);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK28);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK29);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK30);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK31);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK32);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK33);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK34);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK35);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK36);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK37);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK38);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK39);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK40);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK41);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK42);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK43);
		Edt->EnableWindow(FALSE);
		
		UpdateData(FALSE);
	}
	else
	{
		m_00 = 0;
		CEdit *Edt;
		
		Edt=(CEdit *)GetDlgItem(IDC_CHECK1);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK2);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK3);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK4);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK5);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK6);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK7);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK8);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK9);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK10);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK11);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK12);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK13);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK14);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK15);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK16);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK17);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK18);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK19);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK20);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK21);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK22);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK23);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK24);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK25);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK26);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK27);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK28);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK29);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK30);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK31);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK32);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK33);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK34);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK35);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK36);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK37);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK38);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK39);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK40);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK41);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK42);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_CHECK43);
		Edt->EnableWindow(TRUE);
		
		UpdateData(FALSE);
	}

}
