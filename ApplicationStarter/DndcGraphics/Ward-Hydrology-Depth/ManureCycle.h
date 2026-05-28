#if !defined(AFX_MANURECYCLE_H__8D7C21AA_8559_4E7A_B275_FC95910F9A5A__INCLUDED_)
#define AFX_MANURECYCLE_H__8D7C21AA_8559_4E7A_B275_FC95910F9A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureCycle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureCycle dialog

class ManureCycle : public CPropertyPage
{
	DECLARE_DYNCREATE(ManureCycle)

// Construction
public:
	ManureCycle();
	~ManureCycle();

//	CColorEditBoxDlg(CWnd* pParent = NULL);	// standard constructor
	CBrush m_redbrush,m_bluebrush;//define a paint brush
	COLORREF m_redcolor,m_bluecolor,m_textcolor;//define color structure

// Dialog Data
	//{{AFX_DATA(ManureCycle)
	enum { IDD = IDD_ManureCycle };
	int		m_unit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(ManureCycle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ManureCycle)
	afx_msg void OnHouse();
	//afx_msg void OnPen();
	afx_msg void OnGrazing();
	afx_msg void OnLagoon();
	afx_msg void OnCompost();
	afx_msg void OnDigester();
	afx_msg void OnField();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStorage();
	afx_msg void OnSilo();
	afx_msg void Onunit();
	afx_msg void Onunit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANURECYCLE_H__8D7C21AA_8559_4E7A_B275_FC95910F9A5A__INCLUDED_)
