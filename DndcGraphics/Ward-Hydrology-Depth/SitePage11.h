//{{AFX_INCLUDES()
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE11_H__D4F38140_BC75_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE11_H__D4F38140_BC75_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage11.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage11 dialog

class SitePage11 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage11)

// Construction
public:
	SitePage11();
	~SitePage11();
	//BOOL CheckGrazingN();
	//BOOL CheckGrazingID();
	void demo(void);

	int GrazID[300], GrazMonth1[300], GrazDay1[300], GrazMonth2[300], GrazDay2[300];
	float GrazHour[300], Dairy[300], Beef[300], Pig[300], Sheep[300], Horse[300];
	int CutCode[300], CutMonth[300], CutDay[300], CutPart[300], Excreta[300];
	float CutAmount[300], AddFeed[300], FeedCN[300];


// Dialog Data
	//{{AFX_DATA(SitePage11)
	enum { IDD = IDD_PROPPAGE11 };
	CComboBox	m_Excreta;
	CListCtrl	m_CuttingList;
	CListCtrl	m_GrazingList;
	int		m_GrazingID;
	int		m_GSDay;
	int		m_GSMonth;
	int		m_GEMonth;
	int		m_GEDay;
	int		m_GrazingN;
	float	m_CattleHead;
	float	m_HorseHead;
	float	m_SheepHead;
	float	m_GrazingHour;
	int		m_CutTimes;
	int		m_CutCode;
	int		m_CutMonth;
	int		m_CutDay;
	float	m_CutAmount;
	BOOL	m_CutLeaf;
	BOOL	m_CutStem;
	BOOL	m_CutRoot;
	BOOL	m_CutGrain;
	float	m_DairyHead;
	float	m_PigHead;
	float	m_AddFeed;
	float	m_FeedCN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage11)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage11)
	afx_msg void OnKillfocusGrazingN();
	afx_msg void OnKillfocusGrazingID();
	afx_msg void OnGAccept();
	afx_msg void OnGLast();
	afx_msg void OnGNext();
	afx_msg void OnKillfocusGSMonth();
	afx_msg void OnKillfocusGSDay();
	afx_msg void OnKillfocusGEMonth();
	afx_msg void OnKillfocusGEDay();
	afx_msg void OnKillfocusSheepHead();
	afx_msg void OnKillfocusHorseHead();
	afx_msg void OnKillfocusCattleHead();
	afx_msg void OnKillfocusGrazingHour();
	//afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnCutLast();
	afx_msg void OnCutNext();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE11_H__D4F38140_BC75_11D3_A713_005004A6D36F__INCLUDED_)
