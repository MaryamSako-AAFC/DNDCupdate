//{{AFX_INCLUDES()
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE5_H__D8405127_58F2_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE5_H__D8405127_58F2_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage5 dialog

class SitePage5 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage5)

// Construction
public:
	SitePage5();
	~SitePage5();
	//BOOL CheckTillN();
	//BOOL CheckTillID();
	void demo(void);

	int TillID[300];
	int TillMonth[300], TillDay[300], TillMethod[300];

// Dialog Data
	//{{AFX_DATA(SitePage5)
	enum { IDD = IDD_PROPPAGE5 };
	CListCtrl	m_TillList;
	CComboBox	m_TillMethod;
	int		m_TillDay;
	int		m_TillID;
	int		m_TillMonth;
	int		m_TillN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage5)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage5)
	afx_msg void OnKillfocustillN();
	afx_msg void OnKillfocustillMonth();
	afx_msg void OnKillfocustillmethod();
	afx_msg void OnKillfocustillID();
	afx_msg void OnKillfocustillDay();
	afx_msg void OnTillAccept();
	//afx_msg void OnClickMsflexgrid1();
	afx_msg void OnTillNext();
	afx_msg void OnTillLast();
	virtual BOOL OnInitDialog();
	//afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE5_H__D8405127_58F2_11D3_A713_005004A6D36F__INCLUDED_)
