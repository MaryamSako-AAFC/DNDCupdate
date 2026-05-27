// ScreenMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ScreenMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ScreenMonitor dialog


ScreenMonitor::ScreenMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(ScreenMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(ScreenMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ScreenMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScreenMonitor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScreenMonitor, CDialog)
	//{{AFX_MSG_MAP(ScreenMonitor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ScreenMonitor message handlers
