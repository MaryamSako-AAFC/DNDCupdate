//{{AFX_INCLUDES()
//#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SITEPAGE4_H__D8405128_58F2_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_SITEPAGE4_H__D8405128_58F2_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SitePage4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SitePage4 dialog

class SitePage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(SitePage4)

// Construction
public:
	SitePage4();
	~SitePage4();
	void SetCropDefault(CropParameter *cp);
	BOOL SetPlantList();
	BOOL CheckCropN();
	BOOL CheckCropID();//including CheckCropN()
	//void OnKillfocusCropType();
	void demo(int rrr, int yyy);
	//float CropTN(float TotC, float GraCN, float ShoCN, float RooCN, float GraFra, float ShoFra, float RooFra);

	int crop_order[10][40][8], crop_type[10][40][8], plant_month[10][40][8], plant_day[10][40][8], harvest_month[10][40][8], harvest_day[10][40][8], harvest_year[10][40][8];
	float crop_residue[10][40][8], crop_yield[10][40][8], rate_reproduc[10][40][8], Psn_efficiency[10][40][8], Psn_max[10][40][8];
	float TreeAge[10][40][8], TreeCurrentAge[10][40][8], TreeLeafMax[10][40][8], TreeLeafMin[10][40][8];
	int CoverCrop[10][40][8], cropn[10][40], CropNChangeFlag, db_Rotation_Number;
	int db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20], crop_perennial;
	int PerennialCrop[10][40][8], Transplant[10][40][8];
	float GrainFraction[10][40][8], LeafFraction[10][40][8], ShootFraction[10][40][8], RootFraction[10][40][8];
	float GrainCN[10][40][8], LeafCN[10][40][8], ShootCN[10][40][8], RootCN[10][40][8], CropCN[10][40][8];
	float CropTotalN[10][40][8], TDD[10][40][8], WaterDemand[10][40][8];
	float OptT[10][40][8], Nfixation[10][40][8], Vascularity[10][40][8];
	float GrainFill[10][40][8];
	int	  RootShape[10][40][8];
	CString crop_name[10][40][8];

// Dialog Data
	//{{AFX_DATA(SitePage4)
	enum { IDD = IDD_PROPPAGE4 };
	CListCtrl	m_CropList;
	CComboBox	m_CropType;
	float	m_GrowthReproductive;
	float	m_GrowthVegetative;
	float	m_PsnEfficiency;
	float	m_PsnMax;
	float	m_InitialBiomass;
	int		m_CropModel;
	int		m_CropID;
	int		m_CropHDay;
	int		m_CropHMonth;
	int		m_CropHYear;
	int		m_CropN;
	int		m_CropPDay;
	int		m_CropPMonth;
	float	m_CropResidue;
	float	m_CropYield;
	float	m_ShootYield;
	float	m_RootYield;
	int		m_CoverCrop;
	BOOL	m_PerennialCrop;
	float	m_ShootFraction;
	float	m_ShootCN;
	float	m_RootFraction;
	float	m_RootCN;
	float	m_GrainFraction;
	float	m_GrainCN;
	float	m_CropWaterDemand;
	int		m_RootShape;
	float	m_GrainFill;
	float	m_CropTotalN;
	float	m_CropTDD;
	float	m_CropNfixation;
	float	m_CropLAI;
	float	m_Vascularity;
	float	m_OptT;
	float	m_LeafCN;
	float	m_LeafFraction;
	float	m_LeafYield;
	float	m_TreeLeafMax;
	float	m_TreeLeafMin;
	float	m_TreeCurrentAge;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SitePage4)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SitePage4)
	afx_msg void OnKillfocusCropN();
	afx_msg void OnKillfocusCropHYear();
	afx_msg void OnKillfocusCropHMonth();
	afx_msg void OnKillfocusCropHDay();
	afx_msg void OnCropNext();
	afx_msg void OnCropLast();
	afx_msg void OnCropAccept();
	afx_msg void OnKillfocusCropYield();
	afx_msg void OnKillfocusCropPMonth();
	afx_msg void OnKillfocusCropPDay();
	afx_msg void OnKillfocusCropResidue();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCropType();
	afx_msg void OnAskCartivar();
	afx_msg void OnKillfocusSeedDensity();
	afx_msg void OnKillfocusPsnEfficiency();
	afx_msg void OnKillfocusPsnMax();
	afx_msg void OnKillfocusGrowthVegetative();
	afx_msg void OnKillfocusGrowthReproductive();
	afx_msg void OnCropModel();
	afx_msg void OnRadio2();
	afx_msg void OnKillfocusShootYield();
	afx_msg void OnChangeCropN();
	afx_msg void OnCropParas();
	afx_msg void OnKillfocusRootYield();
	afx_msg void OnPerennialCrop();
	afx_msg void OnKillfocusGrainFraction();
	afx_msg void OnKillfocusShootFRaction();
	afx_msg void OnKillfocusGrainCN();
	afx_msg void OnKillfocusShootCN();
	afx_msg void OnKillfocusRootCN();
	afx_msg void OnKillfocusLeafFRaction();
	afx_msg void OnKillfocusLeafCN();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITEPAGE4_H__D8405128_58F2_11D3_A713_005004A6D36F__INCLUDED_)
