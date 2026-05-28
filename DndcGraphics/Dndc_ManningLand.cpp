// Dndc_ManningLand.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "Dndc_ManningLand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dndc_ManningLand dialog


Dndc_ManningLand::Dndc_ManningLand(CWnd* pParent /*=NULL*/)
	: CDialog(Dndc_ManningLand::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dndc_ManningLand)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dndc_ManningLand::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dndc_ManningLand)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dndc_ManningLand, CDialog)
	//{{AFX_MSG_MAP(Dndc_ManningLand)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dndc_ManningLand message handlers
