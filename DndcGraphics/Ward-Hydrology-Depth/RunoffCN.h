#if !defined(AFX_RUNOFFCN_H__43C83437_1373_48CB_BDB1_1CAE32022509__INCLUDED_)
#define AFX_RUNOFFCN_H__43C83437_1373_48CB_BDB1_1CAE32022509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RunoffCN.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RunoffCN dialog

class RunoffCN : public CDialog
{
// Construction
public:
	RunoffCN(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RunoffCN)
	enum { IDD = IDD_RunoffCN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RunoffCN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RunoffCN)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNOFFCN_H__43C83437_1373_48CB_BDB1_1CAE32022509__INCLUDED_)
