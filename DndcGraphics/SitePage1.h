#if !defined(AFX_SITEPAGE1_H__84FA2E20_567F_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE1_H__84FA2E20_567F_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage1 dialog

class SitePage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage1)

// Construction
public:
	SitePage1();
	~SitePage1();

	int LaiFlag, DaymetFlag, Revisit;
	FLOAT m_DecreaseRate, m_TopM;

	void get_defaults(void);
	void AcceptPage1(void);
	void SelectClimFile(void);
	void SelectCO2File(void);
	void ClimMoveDown(void);
	void ClimMoveUp(void);
	
// Dialog Data
	//{{AFX_DATA(SitePage1)
	enum { IDD = IDD_PROPPAGE1 };
	CComboBox	m_MetYear;
	CListBox	m_LAIFileList;
	CListBox	m_ClimateFileList;
	CListBox	m_CO2FileList;
	CString m_CO2FileName;
	CString	m_sitename;
	float	m_latitude;
	long	m_years;
	float	m_AirNH3;
	float	m_RainNO3NH4;
	BOOL	m_RecordDaily;
	int		m_CFileFormat;
	float	m_BaseCO2;
	BOOL	m_Use1File;
	float	m_Longitude;
	BOOL	m_MetSuccess;
	int		m_WaterYrMonth;
	int		m_WaterYrDay;
	BOOL	m_WaterYr;
	float	m_CO2IncreaseRate;
	BOOL	m_CO2file;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage1)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage1)
	afx_msg void OnSelClimateFile();
	afx_msg void OnDblclkClimateFileList();
	afx_msg void OnNewsite();
	afx_msg void OnOpensite();
	afx_msg void OnSavesite();
	virtual BOOL OnInitDialog();
	afx_msg void OnAcceptClimate();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSiteRecover();
	afx_msg void OnMoveDown();
	afx_msg void OnMoveUp();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRecordDaily();
	afx_msg void OnSelLAIfile();
	afx_msg void OnSelchangeMetYear();
	afx_msg void OnDefaulClimate();
	afx_msg void OnDefault();
	afx_msg void OnWaterYear();
	afx_msg void OnKillfocusYears();
	afx_msg void OnUse1File();
	afx_msg void OnCListFileName();
	afx_msg void OnCO2file();
	afx_msg void OnKillfocusSiteName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE1_H__84FA2E20_567F_11D3_A713_005004A6D36F__INCLUDED_)
