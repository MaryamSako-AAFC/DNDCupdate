//{{AFX_INCLUDES()
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE9_H__D8405129_58F2_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE9_H__D8405129_58F2_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage9.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage9 dialog

class SitePage9 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage9)

// Construction
public:
	SitePage9();
	~SitePage9();
	BOOL CheckFloodN();
	BOOL CheckFloodID();
	void demo(void);
	

	int FlooID[300], FlooMonth1[300], FlooDay1[300], FlooMonth2[300], FlooDay2[300];
	float FlooN[300];
	int ShallowFlood[300];
	CString WT_file;

// Dialog Data
	//{{AFX_DATA(SitePage9)
	enum { IDD = IDD_PROPPAGE9 };
	CListBox	m_WTFileList;
	CComboBox	m_FdLeak;
	CListCtrl	m_FloodList;
	float	m_FloodWaterN;
	int		m_FloodDDay;
	int		m_FloodDMonth;
	int		m_FloodFDay;
	int		m_FloodFMonth;
	int		m_FloodID;
	int		m_FloodN;
	int		m_WaterControl;
	int		m_ShallowFlood;
	float	m_WaterGetherIndex;
	float	m_WaterLeakRate;
	float	m_Vascularity;
	float	m_IniWT;
	float	m_LWTceasingSurfFlow;
	float	m_LWTceasingGroungFlow;
	float	m_WatershedIndex;
	float	m_SurfOutflowIntensity;
	float	m_GroundOutflowIntensity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage9)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage9)
	afx_msg void OnKillfocusfloodN();
	afx_msg void OnFloodAccept();
	afx_msg void OnFloodNext();
	afx_msg void OnFloodLast();
	afx_msg void OnKillfocusfloodFMonth();
	afx_msg void OnKillfocusfloodFDay();
	afx_msg void OnKillfocusfloodDMonth();
	afx_msg void OnKillfocusfloodDDay();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusFloodWaterpH();
	afx_msg void OnWaterControl();
	afx_msg void OnRainfed();
	afx_msg void OnObservedWT();
	afx_msg void OnselectWTfile();
	afx_msg void OnDblclkWTFileList();
	afx_msg void OnEmpiricalPara();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE9_H__D8405129_58F2_11D3_A713_005004A6D36F__INCLUDED_)
