// GlobeMapping.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "GlobeMapping.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GlobeMapping dialog


GlobeMapping::GlobeMapping(CWnd* pParent /*=NULL*/)
	: CDialog(GlobeMapping::IDD, pParent)
{
	//{{AFX_DATA_INIT(GlobeMapping)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GlobeMapping::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GlobeMapping)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GlobeMapping, CDialog)
	//{{AFX_MSG_MAP(GlobeMapping)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GlobeMapping message handlers
