// ManureApplication.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ManureApplication.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManureApplication dialog


ManureApplication::ManureApplication(CWnd* pParent /*=NULL*/)
	: CDialog(ManureApplication::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureApplication)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ManureApplication::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureApplication)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureApplication, CDialog)
	//{{AFX_MSG_MAP(ManureApplication)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureApplication message handlers
