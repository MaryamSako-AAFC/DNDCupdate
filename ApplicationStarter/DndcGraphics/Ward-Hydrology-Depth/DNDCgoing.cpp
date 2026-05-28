// DNDCgoing.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "DNDCgoing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DNDCgoing dialog


DNDCgoing::DNDCgoing(CWnd* pParent /*=NULL*/)
	: CDialog(DNDCgoing::IDD, pParent)
{
	//{{AFX_DATA_INIT(DNDCgoing)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DNDCgoing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DNDCgoing)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DNDCgoing, CDialog)
	//{{AFX_MSG_MAP(DNDCgoing)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DNDCgoing message handlers
