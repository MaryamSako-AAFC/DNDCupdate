#if !defined(AFX_MANURELAGOON_H__23AE8D76_C1F0_4F7B_AF11_1E8F812DFE06__INCLUDED_)
#define AFX_MANURELAGOON_H__23AE8D76_C1F0_4F7B_AF11_1E8F812DFE06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureLagoon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureLagoon dialog

class ManureLagoon : public CDialog
{
// Construction
public:
	ManureLagoon(CWnd* pParent = NULL);   // standard constructor
	void SetIniPara(void);//new functions for annualized lagoon management
	void SaveLagoon(void);//new functions for annualized lagoon management
// Dialog Data
	//{{AFX_DATA(ManureLagoon)
	enum { IDD = IDD_ManureLagoon };
	float	m_LagoonCapacity;
	float	m_RemoveFrequency;
	float	m_LagoonSurfaceArea;
	int		m_RainWater;
	int		m_LagoonCover;
	float	m_SlurryRetain;
	float	m_SlurryToField;
	float	m_SlurryToMarket;
	int		m_unit;
	int		m_DrainTimes;
	int		m_DrainID;
	int		m_DrainMonth;
	int		m_DrainDay;
	int		m_LagoonManureAplMethod;
	float	m_LagoonManureAplDepth;
	int     m_LagoonYear;//keep tracks of current LagoonYear
	int     m_LagoonYears;//keeps track of total LagoonYears

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureLagoon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureLagoon)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void Onunit();
	afx_msg void Onunit2();
	afx_msg void OnDrain1();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnLagoonLeftYr1();
	afx_msg void OnLagoonRightYr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANURELAGOON_H__23AE8D76_C1F0_4F7B_AF11_1E8F812DFE06__INCLUDED_)
