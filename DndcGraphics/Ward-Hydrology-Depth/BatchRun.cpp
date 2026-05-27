// BatchRun.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include "BatchRun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char BatchFileName[255];
/////////////////////////////////////////////////////////////////////////////
// BatchRun dialog


BatchRun::BatchRun(CWnd* pParent /*=NULL*/)
	: CDialog(BatchRun::IDD, pParent)
{
	//{{AFX_DATA_INIT(BatchRun)
	m_DailyResult = FALSE;
	//}}AFX_DATA_INIT
}


void BatchRun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BatchRun)
	DDX_Control(pDX, IDC_BatchFileName, m_BatchFileName);
	DDX_Check(pDX, IDC_DailyResult, m_DailyResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BatchRun, CDialog)
	//{{AFX_MSG_MAP(BatchRun)
	ON_BN_CLICKED(IDC_SelectFile, OnSelectFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BatchRun message handlers

void BatchRun::OnSelectFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString cst;
	
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );

	if(ask.DoModal()==IDOK)
	{
		
	}
	else
		return;
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_BatchFileName.GetCount();
	if (num==1) return;
	
	k=m_BatchFileName.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(BatchFileName,cst);
		m_BatchFileName.InsertString(k,BatchFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_BatchFileName.GetCount()==1) break;
		k++;
	}
	m_BatchFileName.SetCurSel(k);
	
/*	RegionSelectFlag = 1;

	CString CP;
	int i, L1, L2;

	int LL=strlen(FileName);
	for(i=LL; i>=0; i--)
	{
		if(FileName[i]=='_') 
		{
			L1=i-1;
			break;
		}
	}

	for(i=LL; i>=0; i--)
	{
		if(FileName[i]==92) 
		{
			L2=i+1;
			break;
		}
	}

	Glean_String(FileName, L2, L1, RegionName);
	
	CP.Format("%s", RegionName);

	int RegionCode = 0;

	
*/	
}

void BatchRun::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString Fregion;
	FILE *region;

	Fregion.Format("%s\\Inter\\BatchFile.txt", OUTPUT);
	region = fopen(Fregion, "w");

	if (region==NULL) FileMessage(Fregion, 0);
	
	fprintf(region, "%s %d\n", BatchFileName, m_DailyResult);
	
	fclose (region);
	
	CDialog::OnOK();
}
