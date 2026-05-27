#if !defined(AFX_OUNTINGBAR_H__70B1F3CC_270C_42DE_8ADB_921BCDC5CE1B__INCLUDED_)
#define AFX_OUNTINGBAR_H__70B1F3CC_270C_42DE_8ADB_921BCDC5CE1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ountingBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CountingBar dialog

class CountingBar : public CDialog
{
// Construction
public:
	CountingBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CountingBar)
	enum { IDD = IDD_CountBar };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CountingBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CountingBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUNTINGBAR_H__70B1F3CC_270C_42DE_8ADB_921BCDC5CE1B__INCLUDED_)
