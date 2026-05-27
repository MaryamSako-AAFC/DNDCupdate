#if !defined(AFX_MANUREAPPLICATION_H__3DB3796D_02B1_4F84_9075_2BBFAD904939__INCLUDED_)
#define AFX_MANUREAPPLICATION_H__3DB3796D_02B1_4F84_9075_2BBFAD904939__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureApplication.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureApplication dialog

class ManureApplication : public CDialog
{
// Construction
public:
	ManureApplication(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManureApplication)
	enum { IDD = IDD_Application };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureApplication)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureApplication)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUREAPPLICATION_H__3DB3796D_02B1_4F84_9075_2BBFAD904939__INCLUDED_)
