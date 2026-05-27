#if !defined(AFX_GLOBEMAPPING_H__A1A8107A_875A_45A8_90DB_E52C08D2914E__INCLUDED_)
#define AFX_GLOBEMAPPING_H__A1A8107A_875A_45A8_90DB_E52C08D2914E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobeMapping.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GlobeMapping dialog

class GlobeMapping : public CDialog
{
// Construction
public:
	GlobeMapping(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GlobeMapping)
	enum { IDD = IDD_Mapping };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GlobeMapping)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GlobeMapping)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBEMAPPING_H__A1A8107A_875A_45A8_90DB_E52C08D2914E__INCLUDED_)
