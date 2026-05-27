#if !defined(AFX_MANUREGRAZING_H__66412DD1_E374_4D75_A7DB_02AECE8C26A5__INCLUDED_)
#define AFX_MANUREGRAZING_H__66412DD1_E374_4D75_A7DB_02AECE8C26A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureGrazing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureGrazing dialog

class ManureGrazing : public CDialog
{
// Construction
public:
	ManureGrazing(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManureGrazing)
	enum { IDD = IDD_Graze };
	CListBox	m_StockFileList;
	CComboBox	m_AnimalType;
	int		m_Stock1;
	int		m_EndDay;
	int		m_EndMonth;
	int		m_GrazeID;
	int		m_GrazeTimes;
	float	m_Heads;
	float	m_Hours;
	int		m_IniDay;
	int		m_IniMonth;
	float	m_GrazeArea;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureGrazing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureGrazing)
	afx_msg void OnNext();
	afx_msg void OnLast();
	afx_msg void OnSelStockFile();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUREGRAZING_H__66412DD1_E374_4D75_A7DB_02AECE8C26A5__INCLUDED_)
