#if !defined(AFX_NEWCROP_H__035BCC73_707E_45C9_B548_03619EBA9853__INCLUDED_)
#define AFX_NEWCROP_H__035BCC73_707E_45C9_B548_03619EBA9853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewCrop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NewCrop dialog

class NewCrop : public CDialog
{
// Construction
public:
	NewCrop(CWnd* pParent = NULL);   // standard constructor
	BOOL SetPlantList();

	float para[30];
	CString word[12];
	char text[200][30];
	char jk[50];
	char CropName[150];
	int CropType;
	int cropid[150];
	CString cropname[150];
	int CropNum, NewCropFlag;

// Dialog Data
	//{{AFX_DATA(NewCrop)
	enum { IDD = IDD_CreateCrop };
	CComboBox	m_SelectCrop;
	int		m_CropID;
	CString	m_CropName;
	float	m_GrainCN;
	float	m_GrainFraction;
	float	m_GrowthDevelop;
	float	m_GrowthReprod;
	float	m_HeightMax;
	float	m_OptTemp;
	float	m_Nfixation;
	float	m_PhotoMax;
	float	m_CropLAI;
	float	m_PlantCN;
	float	m_RootCN;
	float	m_RootFraction;
	float	m_ShootCN;
	float	m_ShootFraction;
	float	m_TDD;
	float	m_TotalBiomassC;
	float	m_WaterRequire;
	float	m_OptimumYield;
	float	m_Nfix;
	float	m_Nsoil;
	float	m_Ndemand;
	float	m_GrainC;
	float	m_RootC;
	float	m_ShootC;
	BOOL	m_Perennial;
	float	m_Vascularity;
	float	m_GrainFill;
	int		m_RootShape;
	float	m_LeafFraction;
	float	m_LeafC;
	float	m_LeafCN;
	float   m_FrostKill;
	float   m_AlfCHRMX;
	float   m_ALFCDRMX;
	float   m_ALFCTMX;
	float   m_ALFPDFMX;
	float m_Root1;
	float m_Root2;
	float m_AGResp1;
	float m_AGResp2;
	float m_cropGRate;
	float m_cropTime;
	float m_RUEHI;
	float m_DelayP;


	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewCrop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NewCrop)
	afx_msg void OnSelchangeSelectCrop();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusGrainFraction();
	afx_msg void OnKillfocusOptimumYield();
	afx_msg void OnKillfocusShootFRaction();
	afx_msg void OnKillfocusShootCN();
	afx_msg void OnKillfocusNfixation();
	afx_msg void OnCheck();
	afx_msg void OnKillfocusGrainCN();
	afx_msg void OnKillfocusRootCN();
	afx_msg void OnChangeCropName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeOpttemp();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCROP_H__035BCC73_707E_45C9_B548_03619EBA9853__INCLUDED_)
