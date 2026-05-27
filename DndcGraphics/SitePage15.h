#if !defined(AFX_SITEPAGE15_H__53F642D6_7808_4F2F_802B_EAB6E6971139__INCLUDED_)
#define AFX_SITEPAGE15_H__53F642D6_7808_4F2F_802B_EAB6E6971139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage15.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage15 dialog

class SitePage15 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage15)

// Construction
public:
	
	SitePage15();
	~SitePage15();
	int  EditParameters();
	void ChangeParas();
	void GetAddParas();
	void SelectSpinUpFile(void);
	void SelectYieldFile(void);

	int TileOption;

// Dialog Data
	//{{AFX_DATA(SitePage15)
	enum { IDD = IDD_PROPPAGE15 };
	int m_TileOption;
	float m_DrainDepth;
	float m_DrainSpace;
	CListBox m_SpinUpFileList;
	CListBox m_OBSYieldList;
	BOOL	m_SpinUpCheck;
	BOOL	m_PrefFlowCheck;
	BOOL    m_SpinUpCheck2;//at planting
	BOOL m_OBSYield;
	BOOL m_DynLayerCheck;
	float m_SpinUpYears;
CString m_SpinUpFileName;
CString m_OBSYieldFileName;
float m_DrainRad;
float m_DrainBed;
float m_keDrain;
float m_MaxNMove;
float m_MobileNF;
float m_NLayerF;
float m_NMoveRate;
float m_SoilEvapF;
float m_RunOffWF;
float m_RunOffNF;
float m_Factor1;
float m_Factor2;
float m_Factor3;
float m_DenitGRate;
float m_NitGRate;
float m_NitRate;
float m_N2ORain;
float m_SprMeltF;
float m_Factor4;
float m_Factor5;
float m_Factor6;
int m_Factor7;
int m_AutoPlant;
float m_Factor8;
float m_Factor9;
float m_Factor10;
float m_Factor13;
float m_UreaHydro;
float m_UreaHydro2;
float m_NH3SoilDF;
float m_UreaDifF;
float m_Factor11;
float m_N2N2OF;
float m_PrefFlowDepth;
float m_PrefFlowRecov;

float m_DynLayerEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage15)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage15)
	virtual BOOL OnInitDialog();
	afx_msg void OnAccepttile();
	afx_msg void OnDrainradio1();
	afx_msg void OnDrainradio2();
	afx_msg void OnSpinUpCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedSpinupcheck2();
	afx_msg void OnBnClickedPrefFlowCheck();
	afx_msg void OnBnClickedObsyield();
	afx_msg void OnBnClickedDynlayercheck();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_SITEPAGE15_H__53F642D6_7808_4F2F_802B_EAB6E6971139__INCLUDED_)
