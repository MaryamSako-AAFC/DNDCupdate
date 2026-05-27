// Manure_storage.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "Manure_storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Manure_storage dialog


Manure_storage::Manure_storage(CWnd* pParent /*=NULL*/)
	: CDialog(Manure_storage::IDD, pParent)
{
	//{{AFX_DATA_INIT(Manure_storage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Manure_storage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Manure_storage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Manure_storage, CDialog)
	//{{AFX_MSG_MAP(Manure_storage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Manure_storage message handlers
