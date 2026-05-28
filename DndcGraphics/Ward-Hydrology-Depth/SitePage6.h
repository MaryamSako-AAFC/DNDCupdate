//{{AFX_INCLUDES()
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE6_H__D8405126_58F2_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE6_H__D8405126_58F2_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage6 dialog

class SitePage6 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage6)

// Construction
public:
	SitePage6();
	~SitePage6();
	//BOOL CheckFerN();
	//BOOL CheckFerID();
	void demo(void);

	int FertID[300], FertMonth[300], FertDay[300], FertMethod[300], FertOption;
	float FertNitrate[300], FertAbi[300], FertUrea[300], FertAnh[300], FertAmNi[300], NH42SO4[300], NH42HPO4[300], FertDepth[300];
	char FertigationYear[300];
	float DayRelease[300], NIefficiency[300], NIduration[300];
	float UreaseEfficiency[300], UreaseDuration[300];
// Dialog Data
	//{{AFX_DATA(SitePage6)
	enum { IDD = IDD_PROPPAGE6 };
	CListBox	m_FGFileList;
	CListCtrl	m_FerList;
	int		m_FerMethod;
	float	m_FerAbi;
	float	m_FerAnh;
	int		m_FerDay;
	float	m_FerDepth;
	int		m_FerID;
	int		m_FerMonth;
	int		m_FerN;
	float	m_FerNH42HPO4;
	float	m_FerNH42SO4;
	float	m_FerNH4NO3;
	float	m_FerNitrate;
	float	m_FerUrea;
	BOOL	m_Fertigation;
	BOOL	m_FertEvent;
	float	m_DayRelease;
	int		m_ReleaseControl;
	float	m_NIefficiency;
	float	m_NIduration;
	int		m_NitrificationInhibitor;
	int		m_FertOption;
	float	m_UreaseEfficiency;
	float	m_UreaseDuration;
	int		m_UreaseInhibitor;
	int		m_unit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage6)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage6)
	afx_msg void OnKillfocusFerN();
	afx_msg void OnFerAccept();
	afx_msg void OnFerLast();
	afx_msg void OnFerNext();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnKillfocusFerMonth();
	afx_msg void OnKillfocusFerDay();
	afx_msg void OnKillfocusFerDepth();
	afx_msg void OnKillfocusFerNitrate();
	afx_msg void OnKillfocusFerNH42HPO4();
	afx_msg void OnKillfocusFerNH42SO4();
	afx_msg void OnKillfocusFerNH4NO3();
	afx_msg void OnKillfocusFerUrea();
	afx_msg void OnKillfocusFerAbi();
	afx_msg void OnKillfocusFerAnh();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectFertigationFile();
	afx_msg void OnFertigation();
	afx_msg void OnFertEvent();
	afx_msg void OnReleaseControl();
	afx_msg void OnNitrificationInhibitor();
	afx_msg void OnFertMethod2();
	afx_msg void OnFertMethod1();
	afx_msg void OnFertMethod3();
	afx_msg void OnDblclkFGFileList();
	afx_msg void OnUreaseInhibitor();
	afx_msg void Onunit();
	afx_msg void Onunit2();
	afx_msg void OnFertMethod4();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE6_H__D8405126_58F2_11D3_A713_005004A6D36F__INCLUDED_)
