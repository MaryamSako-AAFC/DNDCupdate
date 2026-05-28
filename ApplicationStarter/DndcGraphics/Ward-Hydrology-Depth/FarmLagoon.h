#if !defined(AFX_FARMLAGOON_H__D46DE012_A8E9_42C5_8CAB_D8693A9DD386__INCLUDED_)
#define AFX_FARMLAGOON_H__D46DE012_A8E9_42C5_8CAB_D8693A9DD386__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FarmLagoon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FarmLagoon dialog

class FarmLagoon : public CDialog
{
// Construction
public:
	FarmLagoon(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FarmLagoon)
	enum { IDD = IDD_FarmLagoon };
	CListBox	m_ClimFile;
	CListBox	m_LagoonManage;
	CListBox	m_LagoonClim;
	int		m_LagoonCover;
	float	m_SurfaceArea;
	float	m_latitude;
	float	m_capacity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FarmLagoon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FarmLagoon)
	afx_msg void OnSelLagoonFile();
	afx_msg void OnSelManageFile();
	virtual void OnOK();
	afx_msg void OnSelClimFile();
	afx_msg void OnDblclkClimFileList();
	afx_msg void OnDblclkLagoonFileList();
	afx_msg void OnDblclkManageFileList();
	afx_msg void OnCompostSave2();
	afx_msg void OnCompostOpen2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FARMLAGOON_H__D46DE012_A8E9_42C5_8CAB_D8693A9DD386__INCLUDED_)
