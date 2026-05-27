//{{AFX_INCLUDES()
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE10_H__D8405125_58F2_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE10_H__D8405125_58F2_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage10.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage10 dialog

class SitePage10 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage10)

// Construction
public:
	SitePage10();
	~SitePage10();
	//BOOL CheckIrrN();
	//BOOL CheckIrrID();
	void demo(void);

	int IrriID[366], IrriMonth[366], IrriDay[366], IrriMethod[366],CDrainA[366],DrainMonth[366],DrainDay[366],DrainMonth2[366],DrainDay2[366],TileIrriDays[366];
	float IrriAmount[366],CDrainDepth[366];

// Dialog Data
	//{{AFX_DATA(SitePage10)
	enum { IDD = IDD_PROPPAGE10 };
	CListCtrl	m_IrrList;
	CListCtrl	m_DrainList;
	CStatic	m_ifIndex;
	CStatic	m_ifEvent;
	int		m_IrrMode;
	float	m_IrrIndex;
	float	m_IrrpH;
	float	m_IrrAmount;
	int	    m_TileIrriDays;
	int		m_IrrDay;
	int		m_IrrID;
	int		m_IrrMonth;
	int		m_IrrN;
	int		m_IrriMethod;
	int	    m_TileIrri;
	int m_CDrain;
	int m_CDrainA;
	int m_DrainDay;
	int m_DrainMonth;
	int m_DrainDay2;
	int m_DrainMonth2;
	float m_CDrainDepth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage10)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage10)
	afx_msg void OnIrrOption0();
	afx_msg void OnIrrOption1();
	//afx_msg void OnClickMsflexgrid1();
	afx_msg void OnKillfocusirrigationN();
	afx_msg void OnKillfocusirrigationID();
	afx_msg void OnIrrAccept();
	afx_msg void OnIrrLast();
	afx_msg void OnIrrNext();
	afx_msg void OnChangeIrrIndex();
	afx_msg void OnKillfocusirrigationMonth();
	afx_msg void OnKillfocusirrigationDay();
	afx_msg void OnKillfocusirrigationAmount();
	afx_msg void OnKillfocusirrigationpH();
	afx_msg void OnDrLast();
	afx_msg void OnDrNext();
	//afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE10_H__D8405125_58F2_11D3_A713_005004A6D36F__INCLUDED_)
