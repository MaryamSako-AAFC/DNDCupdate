// ountingBar.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ountingBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CountingBar dialog


CountingBar::CountingBar(CWnd* pParent /*=NULL*/)
	: CDialog(CountingBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CountingBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CountingBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CountingBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CountingBar, CDialog)
	//{{AFX_MSG_MAP(CountingBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CountingBar message handlers
