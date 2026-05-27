#if !defined(AFX_DRAWDROUGHT_H__1208F98E_677C_4ECD_97D7_3F3118E3C37C__INCLUDED_)
#define AFX_DRAWDROUGHT_H__1208F98E_677C_4ECD_97D7_3F3118E3C37C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawDrought.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DrawDrought dialog

class DrawDrought : public CDialog
{
// Construction
public:
	DrawDrought(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DrawDrought)
	enum { IDD = IDD_DrawDrought };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DrawDrought)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DrawDrought)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWDROUGHT_H__1208F98E_677C_4ECD_97D7_3F3118E3C37C__INCLUDED_)
