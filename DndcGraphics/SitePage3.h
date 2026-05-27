//{{AFX_INCLUDES()
//#include "datagrid.h"
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE3_H__D8405124_58F2_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE3_H__D8405124_58F2_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage3 dialog

class SitePage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage3)

// Construction
public:
	SitePage3();
	~SitePage3();
	//int  SetCroPracticeArray();
	int  SetCropTable(int TYears);
	//void SetRotation(int rnum, int rlength);
	//void SetCycle(int rnum, int rlength, int cl);
	//void ReturnInftoMainMenu();
	//BOOL checkRID();
	//BOOL CheckRotationYear();
	//BOOL CheckCycleYear();
	//BOOL CheckYearACycle();
	void demo();
	void Make0Files(void);
	void DrawYearScale(void);
	void DrawCycleCrops(void);
	void color(int year);
	void ReadRotationCrops();
	void DrawYearMark();

	int db_Rotation_Number, OpenFile, db_YrCrops[40][40];
	int db_RotationID[40], db_RotateSpan[40], db_CycleSpan[40], db_RotationCycles[40];
	int System, SystemYears[40], SystemCycleYears[40], AccuYears;
	int db_YrCropOrder[40][40][5], db_YrCropType[40][40][5];
	int db_PMonth[40][40][5], db_PDay[40][40][5], db_HMonth[40][40][5], db_HDay[40][40][5];
	int db_HYr[40][40][5], db_CoverCrop[40][40][5], db_PerennialCrop[40][40][5];
	int TotalYears;

	
// Dialog Data
	//{{AFX_DATA(SitePage3)
	enum { IDD = IDD_PROPPAGE3 };
	CComboBox	m_System;
	CListCtrl	m_CropList;
	CButton	m_NextR;
	CButton	m_LastR;
	CButton	m_InputCrop;
	int		m_PlantType;
	int		m_RotationN;
	int		m_RotationID;
	int		m_CycleYear;
	int		m_RotationYear;
	int		m_YearACycle;
	int		m_ShowTYear;
	float	m_RotationCycles;
	int		m_SystemYears;
	int		m_SystemCycleYears;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage3)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage3)
	afx_msg void OnInputCrop();
	afx_msg void OnKillfocusCycleYear();
	afx_msg void OnLastRotation();
	afx_msg void OnLastRotation2();
	afx_msg void OnNextRotation();
	afx_msg void OnNextRotation2();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusRotationYear();
	afx_msg void OnKillfocusRotationN();
	afx_msg void OnSetfocusRotationCycles();
	afx_msg void OnKillfocusSystem();
	afx_msg void OnSelchangeSystem();
	afx_msg void OnKillfocusSystemYears();
	afx_msg void OnKillfocusOneCycleYears();
	afx_msg void OnViewRotation();
	afx_msg void OnManureFarmSoil();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE3_H__D8405124_58F2_11D3_A713_005004A6D36F__INCLUDED_)
