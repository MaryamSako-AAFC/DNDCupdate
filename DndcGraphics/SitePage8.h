//{{AFX_INCLUDES()
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE8_H__D840512A_58F2_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE8_H__D840512A_58F2_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage8.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage8 dialog

class SitePage8 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage8)

// Construction
public:
	
	SitePage8();
	~SitePage8();
	//BOOL CheckWeedN();
	//BOOL CheckWeedID();
	void demo(void);

	int WeedOption, WeedID[300], WeedMonth1[300], WeedDay1[300], WeedMonth2[300], WeedDay2[300];

// Dialog Data
	//{{AFX_DATA(SitePage8)
	enum { IDD = IDD_PROPPAGE8 };
	CListCtrl	m_WeedList;
	int		m_WeedOption;
	int		m_WeedDay;
	int		m_WeedID;
	int		m_WeedMonth;
	int		m_WeedN;
	int		m_WeedMonth2;
	int		m_WeedDay2;
	float	m_CoverFraction;

	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage8)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage8)
	afx_msg void OnWedLast();
	afx_msg void OnWedNext();
	afx_msg void OnWedAccept();
	afx_msg void OnWeedOption0();
	afx_msg void OnWeedOption1();
	afx_msg void OnWeedOption2();
	afx_msg void OnKillfocusWeedMonth();
	afx_msg void OnKillfocusWeedDay();
	virtual BOOL OnInitDialog();

	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE8_H__D840512A_58F2_11D3_A713_005004A6D36F__INCLUDED_)
