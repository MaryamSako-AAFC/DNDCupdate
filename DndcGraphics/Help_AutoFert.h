#if !defined(AFX_HELP_AUTOFERT_H__DEB6B2FC_035F_4CAC_81A7_BB81C1CD87DF__INCLUDED_)
#define AFX_HELP_AUTOFERT_H__DEB6B2FC_035F_4CAC_81A7_BB81C1CD87DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Help_AutoFert.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Help_AutoFert dialog

class Help_AutoFert : public CDialog
{
// Construction
public:
	Help_AutoFert(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Help_AutoFert)
	enum { IDD = IDD_HelpAF };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Help_AutoFert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Help_AutoFert)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELP_AUTOFERT_H__DEB6B2FC_035F_4CAC_81A7_BB81C1CD87DF__INCLUDED_)
