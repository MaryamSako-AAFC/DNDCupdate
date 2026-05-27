// Help_AutoFert.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "Help_AutoFert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Help_AutoFert dialog


Help_AutoFert::Help_AutoFert(CWnd* pParent /*=NULL*/)
	: CDialog(Help_AutoFert::IDD, pParent)
{
	//{{AFX_DATA_INIT(Help_AutoFert)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Help_AutoFert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Help_AutoFert)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Help_AutoFert, CDialog)
	//{{AFX_MSG_MAP(Help_AutoFert)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Help_AutoFert message handlers
