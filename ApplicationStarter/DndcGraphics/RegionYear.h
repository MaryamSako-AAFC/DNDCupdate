#if !defined(AFX_REGIONYEAR_H__AC23E134_0BB0_4A86_B5F9_FAB83EB64F6B__INCLUDED_)
#define AFX_REGIONYEAR_H__AC23E134_0BB0_4A86_B5F9_FAB83EB64F6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegionYear.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RegionYear dialog

class RegionYear : public CDialog
{
// Construction
public:
	RegionYear(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RegionYear)
	enum { IDD = IDD_RegionYear };
	CComboBox	m_RicePlantingMethod;
	CComboBox	m_IrriAlter;
	CComboBox	m_TillAlter;
	CComboBox	m_FloodAlter;
	CComboBox	m_AutoFert;
	CComboBox	m_InterDrain;
	float	m_LitterBackField;
	float	m_AnimalManure;
	float	m_FertilizerRate;
	float	m_IrriIndex;
	float	m_AtmoCO2;
	float	m_AirTemp;
	int		m_Tillage;
	int		m_RegionYear;
	float	m_YieldIncrease;
	BOOL	m_ShallowFlood;
	BOOL	m_UplandRice;
	BOOL	m_FertSO4;
	int		m_SlowReleaseDays;
	float	m_RainChange;
	float	m_MicroIndex;
	float	m_WaterDemand;
	float	m_MaxTemp;
	float	m_CropCN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RegionYear)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RegionYear)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDataCopy();
	afx_msg void OnAf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGIONYEAR_H__AC23E134_0BB0_4A86_B5F9_FAB83EB64F6B__INCLUDED_)
