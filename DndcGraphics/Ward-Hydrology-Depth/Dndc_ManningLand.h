#if !defined(AFX_DNDC_MANNINGLAND_H__D8C86B2E_0559_4092_B00A_5DBB24F991FF__INCLUDED_)
#define AFX_DNDC_MANNINGLAND_H__D8C86B2E_0559_4092_B00A_5DBB24F991FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dndc_ManningLand.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dndc_ManningLand dialog

class Dndc_ManningLand : public CDialog
{
// Construction
public:
	Dndc_ManningLand(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dndc_ManningLand)
	enum { IDD = IDD_ManningLand };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dndc_ManningLand)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dndc_ManningLand)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_MANNINGLAND_H__D8C86B2E_0559_4092_B00A_5DBB24F991FF__INCLUDED_)
