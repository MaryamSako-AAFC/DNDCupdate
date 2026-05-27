#if !defined(AFX_MANUREHOUSING_H__40FFCE88_0EC0_474A_8872_A3AF4F09AABF__INCLUDED_)
#define AFX_MANUREHOUSING_H__40FFCE88_0EC0_474A_8872_A3AF4F09AABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureHousing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureHousing dialog

class ManureHousing : public CDialog
{
// Construction
public:
	ManureHousing(CWnd* pParent = NULL);   // standard constructor
	void SetIniPara(void);
	void SaveFeedlot(void);

// Dialog Data
	//{{AFX_DATA(ManureHousing)
	enum { IDD = IDD_ManureHouse };
	CComboBox	m_SolidLiquidSepa;
	CComboBox	m_NutritionModel;
	CListBox	m_ExcretionFileList;
	CListBox	m_IndoorClimateFile;
	CComboBox	m_AnimalType;
	CListBox	m_StockFileList;
	int		m_Stock1;
	float	m_AnimalHeads;
	float	m_FeedRate;
	float	m_ProteinPercent;
	int		m_FloorSurfaceType;
	float	m_FloorArea;
	int		m_BedType;
	float	m_BedAmount;
	float	m_BedCN;
	float	m_BedFrequency;
	int		m_Ventilation;
	float	m_VentRate;
	float	m_UC;
	float	m_UD;
	float	m_UL;
	float	m_UR;
	float	m_FC;
	float	m_FD;
	float	m_FL;
	float	m_FR;
	float	m_RemovalFrequency;
	float	m_Storage;
	float	m_TPpercent;
	int		m_Flash;
	int		m_unit;
	float	m_UF;
	float	m_FF;
	int		m_FeedLots;
	int		m_Feedlot;
	int		m_FeedlotYears;
	int		m_FeedlotYear;
	float	m_FlushWater;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureHousing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureHousing)
	afx_msg void OnSelStockFile();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnStock2();
	afx_msg void OnStock1();
	afx_msg void OnFeeds();
	afx_msg void OnUpdateTp();
	afx_msg void Onunit2();
	afx_msg void Onunit();
	afx_msg void OnMove2();
	afx_msg void OnMove1();
	afx_msg void OnSelectIndoorClimate();
	afx_msg void OnDblclkStockFileList();
	afx_msg void OnDblclkIndoorClimateFile();
	afx_msg void OnFeedYr2();
	afx_msg void OnFeedYr1();
	afx_msg void OnSelectExcretion();
	afx_msg void OnExcretion();
	afx_msg void OnDblclkExcretionFileList();
	afx_msg void OnVentilation1();
	afx_msg void OnStock3();
	afx_msg void OnKillfocusVentRate();
	afx_msg void OnKillfocusSolidLiquidSepa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUREHOUSING_H__40FFCE88_0EC0_474A_8872_A3AF4F09AABF__INCLUDED_)
