// SitePSheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "math.h"
#include "dndc_main.h"

#define AskGlobal
#include "SitePara.h"
#undef AskGlobal

#include "SitePSheet.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSitePSheet

IMPLEMENT_DYNAMIC(CSitePSheet, CPropertySheet)

CSitePSheet::CSitePSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION1, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().
	 
	AddPage(&m_Page1);	
#ifdef MANURE
	AddPage(&m_Page53);
	AddPage(&m_Page2);
	AddPage(&m_Page22);
#else
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page15);//new parameters sheet
#endif	
	AddPage(&m_Page4);

/*	AddPage(&m_Page5);
	AddPage(&m_Page6);
	AddPage(&m_Page7);
	AddPage(&m_Page8);
	AddPage(&m_Page9);*/
}

CSitePSheet::~CSitePSheet()
{
}


BEGIN_MESSAGE_MAP(CSitePSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSitePSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSitePSheet message handlers

BOOL CSitePSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	char *p0="Input Information";
	SetTitle(p0);

	// add a preview window to the property sheet.
	CRect rectWnd;
	GetWindowRect(rectWnd);
	SetWindowPos(NULL, 0, 0,
		rectWnd.Width() + 100,
		rectWnd.Height(),
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	CRect rectPreview(rectWnd.Width() + 25, 25,
		rectWnd.Width()+75, 75);

	//m_wndPreview.Create(NULL, NULL, WS_CHILD|WS_VISIBLE,
	//	rectPreview, this, 0x1000);

	CenterWindow();
	return bResult;
}

//____________________________________________________________
//____________________________________________________________

/////////////////////////////////////////////////////////////////////////////
//Forest

IMPLEMENT_DYNAMIC(CForestPSheet, CPropertySheet)

CForestPSheet::CForestPSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION1, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page2);
	//AddPage(&m_Page13);
	//AddPage(&m_Page14);
/*	AddPage(&m_Page7);
	AddPage(&m_Page8);
	AddPage(&m_Page9);
	AddPage(&m_Page10);
	AddPage(&m_Page11);*/
}

CForestPSheet::~CForestPSheet()
{
}


BEGIN_MESSAGE_MAP(CForestPSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSitePSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CForestPSheet message handlers

BOOL CForestPSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	SetTitle("Forest information in a year:");
	return bResult;
}







//____________________________________________________________
//____________________________________________________________


/////////////////////////////////////////////////////////////////////////////
// CSitePSheet

IMPLEMENT_DYNAMIC(CCropPSheet, CPropertySheet)

CCropPSheet::CCropPSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION1, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	//AddPage(&m_Page1);
	//AddPage(&m_Page2);
	//AddPage(&m_Page3);
	AddPage(&m_Page4);
	AddPage(&m_Page5);
	AddPage(&m_Page6);
	AddPage(&m_Page7);
	AddPage(&m_Page10);
	AddPage(&m_Page9);	
	AddPage(&m_Page8);
	AddPage(&m_Page11);
}

CCropPSheet::~CCropPSheet()
{
}


BEGIN_MESSAGE_MAP(CCropPSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSitePSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSitePSheet message handlers

BOOL CCropPSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	SetTitle("Farming Management Practices");

	// add a preview window to the property sheet.
	//CRect rectWnd;
	//GetWindowRect(rectWnd);
	//SetWindowPos(NULL, 0, 0,
	//	rectWnd.Width() + 100,
	//	rectWnd.Height(),
	//	SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	//CRect rectPreview(rectWnd.Width() + 25, 25,
	//	rectWnd.Width()+75, 75);

	//m_wndPreview.Create(NULL, NULL, WS_CHILD|WS_VISIBLE,
	//	rectPreview, this, 0x1000);

	//CenterWindow();
	return bResult;
}






