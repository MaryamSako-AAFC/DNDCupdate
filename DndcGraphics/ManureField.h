#if !defined(AFX_MANUREFIELD_H__CB4D5807_D533_46E7_B684_CB077869B2FC__INCLUDED_)
#define AFX_MANUREFIELD_H__CB4D5807_D533_46E7_B684_CB077869B2FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureField.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureField dialog

class ManureField : public CDialog
{
// Construction
public:
	ManureField(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManureField)
	enum { IDD = IDD_ManureField };
	float	m_FieldArea;
	int		m_unit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureField)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureField)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void Onunit();
	afx_msg void Onunit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUREFIELD_H__CB4D5807_D533_46E7_B684_CB077869B2FC__INCLUDED_)
