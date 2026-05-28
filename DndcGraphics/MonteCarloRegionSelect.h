#if !defined(AFX_MONTECARLOREGIONSELECT_H__9B0DDF65_5957_4580_8E67_83DD271FBA74__INCLUDED_)
#define AFX_MONTECARLOREGIONSELECT_H__9B0DDF65_5957_4580_8E67_83DD271FBA74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonteCarloRegionSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MonteCarloRegionSelect dialog

class MonteCarloRegionSelect : public CDialog
{
// Construction
public:
	MonteCarloRegionSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MonteCarloRegionSelect)
	enum { IDD = IDD_MonteCarloRegionSelect };
	CListBox	m_ClimFileLocation;
	CComboBox	m_WizardCrops;
	CComboBox	m_CountyNames;
	CListBox	m_IndexFile;
	int		m_year;
	float	m_s1;
	float	m_s2;
	float	m_s3;
	float	m_s4;
	float	m_s5;
	float	m_s6;
	float	m_s7;
	float	m_s8;
	CString	m_ClimateFileName;
	CString	m_State;
	int		m_CountyID;
	CString	m_County;
	CString	m_Crop1;
	CString	m_Crop2;
	CString	m_Crop3;
	float	m_Fert1;
	float	m_Fert2;
	float	m_Fert3;
	int		m_TotalCrops;
	int		m_date1;
	int		m_date1b;
	int		m_date2;
	int		m_date2b;
	int		m_date3;
	int		m_date3b;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MonteCarloRegionSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MonteCarloRegionSelect)
	afx_msg void OnSelectIndexFile();
	afx_msg void OnSelchangeCountyNames();
	afx_msg void OnSelchangeWizardCrops();
	virtual void OnOK();
	afx_msg void OnSelectIndexFile2();
	afx_msg void OnDblclkIndexFile();
	afx_msg void OnDblclkWizardCrops();
	afx_msg void OnDblclkClimateFileLocation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTECARLOREGIONSELECT_H__9B0DDF65_5957_4580_8E67_83DD271FBA74__INCLUDED_)
