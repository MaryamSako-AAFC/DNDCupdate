#if !defined(AFX_MONTECARLONOTE_H__F9CD414D_C6CB_47D4_9670_B74E837E8ECE__INCLUDED_)
#define AFX_MONTECARLONOTE_H__F9CD414D_C6CB_47D4_9670_B74E837E8ECE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonteCarloNote.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MonteCarloNote dialog

class MonteCarloNote : public CDialog
{
// Construction
public:
	MonteCarloNote(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MonteCarloNote)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MonteCarloNote)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MonteCarloNote)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTECARLONOTE_H__F9CD414D_C6CB_47D4_9670_B74E837E8ECE__INCLUDED_)
