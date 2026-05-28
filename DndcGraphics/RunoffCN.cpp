// RunoffCN.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "RunoffCN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RunoffCN dialog


RunoffCN::RunoffCN(CWnd* pParent /*=NULL*/)
	: CDialog(RunoffCN::IDD, pParent)
{
	//{{AFX_DATA_INIT(RunoffCN)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RunoffCN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RunoffCN)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RunoffCN, CDialog)
	//{{AFX_MSG_MAP(RunoffCN)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RunoffCN message handlers
