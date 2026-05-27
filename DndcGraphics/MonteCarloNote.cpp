// MonteCarloNote.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "MonteCarloNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MonteCarloNote dialog


MonteCarloNote::MonteCarloNote(CWnd* pParent /*=NULL*/)
	: CDialog(MonteCarloNote::IDD, pParent)
{
	//{{AFX_DATA_INIT(MonteCarloNote)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MonteCarloNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MonteCarloNote)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MonteCarloNote, CDialog)
	//{{AFX_MSG_MAP(MonteCarloNote)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MonteCarloNote message handlers
