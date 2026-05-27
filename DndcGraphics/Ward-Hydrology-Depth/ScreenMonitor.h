#if !defined(AFX_SCREENMONITOR_H__9EA2EC6B_5D57_4C99_BD09_19DCC1A45A01__INCLUDED_)
#define AFX_SCREENMONITOR_H__9EA2EC6B_5D57_4C99_BD09_19DCC1A45A01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScreenMonitor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ScreenMonitor dialog

class ScreenMonitor : public CDialog
{
// Construction
public:
	ScreenMonitor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ScreenMonitor)
	enum { IDD = IDD_DIALOG6 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScreenMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ScreenMonitor)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENMONITOR_H__9EA2EC6B_5D57_4C99_BD09_19DCC1A45A01__INCLUDED_)
