// GlobeResult.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "GlobeResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GlobeResult dialog


GlobeResult::GlobeResult(CWnd* pParent /*=NULL*/)
	: CDialog(GlobeResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(GlobeResult)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GlobeResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GlobeResult)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GlobeResult, CDialog)
	//{{AFX_MSG_MAP(GlobeResult)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GlobeResult message handlers
