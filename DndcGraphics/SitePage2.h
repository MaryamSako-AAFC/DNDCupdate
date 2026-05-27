#if !defined(AFX_SITEPAGE2_H__78F8390A_5814_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE2_H__78F8390A_5814_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage2 dialog

class SitePage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage2)

// Construction
public:
	SitePage2();
	~SitePage2();
	void GetSoilParas();
	void SetSoilOrganicPart(int index);
	int  EditParameter();
	void ChangeOthers();
	int  SetSoilDensity();
	float OldVLLcn,OldVLLitter,OldLLcn,OldLLitter,OldRLcn,OldSoilLitter,OldHumadCN;
	float OldSoilHumads,OldHumusCN,OldSoilHumus;


// Dialog Data
	//{{AFX_DATA(SitePage2)
	enum { IDD = IDD_PROPPAGE2 };
	CComboBox	m_Soillanduse;
	CComboBox	m_Soiltexture;
	BOOL	m_Soilbypass;
	float	m_SoilClay;
	float	m_SoilDensity;
	float	m_WaterPoolBD;
	float	m_SoilHumads;
	float	m_SoilHumus;
	float	m_SoilLitter;
	float	m_SoilMoisture;
	float	m_SoilNH4;
	float	m_SoilNO3;
	float	m_SoilOrganic;
	float	m_SoilpH;
	float	m_SoilTemp;
	float	m_SoilFieldCapacity;
	float	m_SoilWiltingPoint;
	int		m_SoilRetardation;
	float	m_MicrobioIndex;
	float	m_WaterObstructLayer;
	float	m_slope;
	float	m_TopM;
	float	m_DecreaseRate;
	BOOL	m_SOMdefine;
	BOOL	m_SOMprofile;
	BOOL	m_BypassYes;
	float	m_VLLcn;
	float	m_VLLitter;
	float	m_HumadCN;
	float	m_HumusCN;
	float	m_LLcn;
	float	m_LLitter;
	float	m_RLcn;
	float	m_BulkCN;
	float	m_SoilSks;
	float	m_BypassFlowRate;
	BOOL	m_UseION;
	float	m_HighestWT;
	BOOL    m_WTCheck;//Checkbox boolean for determining if water table is on or off. Will tie to previous parameter HighestWT
	BOOL	m_WaterLoggingYes;
	BOOL	m_WaterLoggingNo;
	float	m_SoilPorosity;
	float	m_PassiveC;
	float	m_PassiveCCN;
	float	m_DClitter;
	float	m_DChumads;
	float	m_DChumus;
	BOOL	m_DCfactor;
	int		m_ProfileType;
	CString m_ProfileFileName;
	float	m_LateralInflux;
	float	m_salinity;
	BOOL	m_SCSuse;
	BOOL    m_CheckHomo1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnRecover();
	afx_msg void OnSoilRecover();
	afx_msg void OnKillfocusSoilDensity();
	afx_msg void OnKillfocusSoilLitter();
	afx_msg void OnKillfocusSoilHumads();
	afx_msg void OnKillfocusSoilHumus();
	afx_msg void OnKillfocusSoilOrganic();
	afx_msg void OnAcceptSoil();
	afx_msg void OnKillfocusSoilpH();
	afx_msg void OnKillfocusSoilTemp();
	afx_msg void OnKillfocusSoilClay();
	afx_msg void OnSoilDefault();
	afx_msg void OnKillfocusFieldCapacity();
	afx_msg void OnKillfocusSoilWiltingPoint();
	afx_msg void OnSoilRetardation();
	afx_msg void OnSoilRetardation1();
	afx_msg void OnSOMdefine();
	
	afx_msg void OnSOMprofile();
	afx_msg void OnSoilbypassYes();
	afx_msg void OnSoilbypass();
	afx_msg void OnKillfocusBulkCN();
	afx_msg void OnWaterLoggingYes();
	afx_msg void OnWaterLoggingNo();
	afx_msg void OnDCfactor();
	afx_msg void OnSCSCurve();
	afx_msg void OnRadio5();
	afx_msg void OnProfileType();
	afx_msg void OnSelchangeSoiltexture();
	afx_msg void OnSCSuse();
	afx_msg void OnKillfocusVLLitter();
	afx_msg void OnKillfocusLLitter();
	afx_msg void OnKillfocusPassiveC();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedWatertablecheck();
	afx_msg void OnBnClickedCheckhom1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE2_H__78F8390A_5814_11D3_A713_005004A6D36F__INCLUDED_)
