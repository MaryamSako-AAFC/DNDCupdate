#if !defined(AFX_GLOBERESULT_H__D3BB7BF8_C193_42C2_A444_D210267745BC__INCLUDED_)
#define AFX_GLOBERESULT_H__D3BB7BF8_C193_42C2_A444_D210267745BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobeResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GlobeResult dialog

class GlobeResult : public CDialog
{
// Construction
public:
	GlobeResult(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GlobeResult)
	enum { IDD = IDD_GlobeDataProcess };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GlobeResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GlobeResult)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBERESULT_H__D3BB7BF8_C193_42C2_A444_D210267745BC__INCLUDED_)
