#if !defined(AFX_FARMCOMPOST_H__B52887A9_F3CB_455E_B352_A2D8F798FFE8__INCLUDED_)
#define AFX_FARMCOMPOST_H__B52887A9_F3CB_455E_B352_A2D8F798FFE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FarmCompost.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FarmCompost dialog

class FarmCompost : public CDialog
{
// Construction
public:
	FarmCompost(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FarmCompost)
	enum { IDD = IDD_FarmCompost };
	CListBox	m_ManaFileList;
	CListBox	m_ClimFileList;
	int		m_CompostMethod;
	float	m_latitude;
	float	m_Poro;
	float	m_CompostPH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FarmCompost)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FarmCompost)
	afx_msg void OnSelClimFile();
	virtual void OnOK();
	afx_msg void OnSelGisFile2();
	afx_msg void OnCompostMethod();
	afx_msg void OnCompostSave();
	afx_msg void OnCompostOpen();
	afx_msg void OnDblclkClimFileList();
	afx_msg void OnDblclkManaFileList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FARMCOMPOST_H__B52887A9_F3CB_455E_B352_A2D8F798FFE8__INCLUDED_)
