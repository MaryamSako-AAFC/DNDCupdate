// dndc71.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "dndc71.h"

#include "MainFrm.h"
#include "SitePara.h"
#include "graphexDoc.h"
#include "graphexView.h"
#include "dndc_main.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// graphexApp

BEGIN_MESSAGE_MAP(graphexApp, CWinApp)
	//{{AFX_MSG_MAP(graphexApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// graphexApp construction

graphexApp::graphexApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	CString DIR0;
	DIR0.Format("%s", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inputs", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inter", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inter\\Management_1", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inter\\RegionFiles", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Record", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Record\\Region", OUTPUT);
	mkdir(DIR0);
	DIR0.Format("%s\\Record\\Site", OUTPUT);
	mkdir(DIR0);
	DIR0.Format("%s\\Record\\MonteCarlo", OUTPUT);
	mkdir(DIR0);
/*
#ifdef MANURE
	CString SF;
	FILE *sf;
	
	for(int m_FeedlotYear=0; m_FeedlotYear<=10; m_FeedlotYear++)
	{
		for(int i=0; i<=10; i++)
		{
			SF.Format("%s\\Result\\Inter\\ManureHouse_%d_%d.txt", ROOTDIR, m_FeedlotYear, i);
			sf=fopen(SF, "w");
			if(sf==NULL) note(1, SF);
			
			fprintf(sf, "%d  %d\n", 0, 1);  
			fprintf(sf, "%3d  %8.2f  %8.2f  %8.4f  %8.4f\n", 0, 0.0, 0.0, 0.0, 0.0);	
			fprintf(sf, "%f  %d\n", 0.0, 0);//0 slatted floor; 1 conrete floor
			fprintf(sf, "%d  %f  %d  %f\n", 0, 0.0, 0, 0.0);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			fprintf(sf, "%d  %f  %s\n", 0, 0.0, "None");// 0 natural, 1 fan
			fprintf(sf, "%f\n", 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%d\n", -1);
			
			fclose(sf);
		}
		
		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Result\\inter\\TotalFeedLots_%d", ROOTDIR, 1);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", 1);
		fclose(TFL);
	}
	
	SF.Format("%s\\Result\\Inter\\ManureGraze.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	
	fprintf(sf, "%d  %d  %d  %f\n", 0, 8, 0, 0.0);  
	
	fclose(sf);
	
	SF.Format("%s\\Result\\Inter\\ManureLagoon.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	
	fprintf(sf, "%f  %f  %d  %d  %d\n", 0.0, 0.0, 0, 0, 0);  
	fprintf(sf, "%d %d %f  %f  %f\n", 0, 0, 0.0, 0.0, 0.0); 
	fclose(sf);
	
	SF.Format("%s\\Result\\Inter\\ManureCompost.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	
	fprintf(sf, "%f  %d  %d  %f  %f\n", 0.0, 0, 0, 0.0, 0.0);  
	//fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);
	
	SF.Format("%s\\Result\\Inter\\ManureDigester.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	
	fprintf(sf, "%d  %f  %f\n", 0, 0.0, 0.0);    
	fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);
	
	SF.Format("%s\\Result\\Inter\\ManureField.txt", ROOTDIR);
	sf=fopen(SF, "w");
	
	if(sf==NULL) note(1, SF);
	fprintf(sf, "%f", 0.0);    
	fclose(sf);
	
	CString XFF;
	FILE *xff;
	
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", 0, 0, 0);
	fclose(xff);
#endif
*/
//#ifdef FACILITY
//#else
/*	char SYF[200];
	FILE* sni;
	sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
	sni=sopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 1);//1
	fclose(sni);*/
//#endif
}

/////////////////////////////////////////////////////////////////////////////
// The one and only graphexApp object

graphexApp theApp;

/////////////////////////////////////////////////////////////////////////////
// graphexApp initialization

BOOL graphexApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;

#ifdef BASE
	{
		pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,//FRAME
		RUNTIME_CLASS(CGraphexDoc),//graphexDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGraphexView));//graphexView));
	}
#endif
/*
#ifdef WIZARD 
	{
		pDocTemplate = new CSingleDocTemplate(
		IDR_MENU1, //
		RUNTIME_CLASS(CGraphexDoc),//graphexDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGraphexView));//graphexView));
	}
#endif

#ifdef MANURE
	{
		pDocTemplate = new CSingleDocTemplate(
		IDR_MANURE, //
		RUNTIME_CLASS(CGraphexDoc),//graphexDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGraphexView));//graphexView));
	}
#endif
*/

	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void graphexApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// graphexApp message handlers


void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	AfxMessageBox("!!!");
	
	CDialog::OnLButtonDown(nFlags, point);
}
