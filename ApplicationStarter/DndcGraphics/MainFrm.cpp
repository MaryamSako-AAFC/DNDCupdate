// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "dndc71.h"//graphex.h"
#include "SitePara.h"
#include "MainFrm.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DOC, OnUpdateMousePos)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_DOC,
	//ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#ifdef BASE//FRAME
	
	{
		if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
#ifdef MANURE
			//!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
			!m_wndToolBar.LoadToolBar(IDR_MANURE))
#else
			!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
#endif
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}
	}
#endif	
/*
#ifdef WIZARD
	{
		if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
			//!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
			!m_wndToolBar.LoadToolBar(IDR_MENU1)) //Wizard
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}
	}
#endif 	
#ifdef MANURE
	{
		if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
			//!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
			!m_wndToolBar.LoadToolBar(IDR_MANURE)) //Wizard
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}
	}
#endif 	
*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::SetDatabaseBar()
{

	return 0;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateMousePos(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CMainFrame::SetDoc(CString MPos)
{
	int Index=m_wndStatusBar.CommandToIndex(ID_INDICATOR_DOC);
	m_wndStatusBar.SetPaneText(Index,MPos);

	CWindowDC dc(&m_wndStatusBar);
	CSize SText=dc.GetTextExtent(MPos);

	m_wndStatusBar.SetPaneInfo(Index,ID_INDICATOR_DOC,SBPS_NORMAL,SText.cx);
}

/*
void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CFrameWnd::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here

	// Construct a CRect from the structure pointer
	CRect rcSize(pRect);

	// Create a string to hold our message
	CString sizeMSG;
	
	
}

*/


void CMainFrame::OnAppExit() 
{
	// TODO: Add your command handler code here
	exit(0);
	
}

