#if !defined(AFX_SELECTOBSWT_H__3D89787D_7E3F_426F_AE84_779959F1F6B2__INCLUDED_)
#define AFX_SELECTOBSWT_H__3D89787D_7E3F_426F_AE84_779959F1F6B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectObsWT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectObsWT dialog

class SelectObsWT : public CDialog
{
// Construction
public:
	SelectObsWT(CWnd* pParent = NULL);   // standard constructor

	void WT_table1(void);

// Dialog Data
	//{{AFX_DATA(SelectObsWT)
	enum { IDD = IDD_SelectObservedWT };
	CListBox	m_WTFileList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectObsWT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectObsWT)
	afx_msg void OnselectWTfile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTOBSWT_H__3D89787D_7E3F_426F_AE84_779959F1F6B2__INCLUDED_)
