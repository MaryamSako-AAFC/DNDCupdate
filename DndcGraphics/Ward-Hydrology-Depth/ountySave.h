#if !defined(AFX_OUNTYSAVE_H__6E82BD15_B45C_4263_BEED_7DB2BAAF1322__INCLUDED_)
#define AFX_OUNTYSAVE_H__6E82BD15_B45C_4263_BEED_7DB2BAAF1322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ountySave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CountySave dialog

class CountySave : public CDialog
{

// Construction
public:
	CountySave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CountySave)
	enum { IDD = IDD_ResultRecord };
	CString	m_FileName;
	BOOL	m_AirTemp;
	BOOL	m_CH4;
	BOOL	m_CropResp;
	BOOL	m_Daily;
	BOOL	m_Evaporation;
	BOOL	m_GHG;
	BOOL	m_GrainMass;
	BOOL	m_Ice;
	BOOL	m_LAI;
	BOOL	m_N2;
	BOOL	m_N2O;
	BOOL	m_NH3;
	BOOL	m_NO;
	BOOL	m_Nuptake;
	BOOL	m_Prec;
	BOOL	m_PSN;
	BOOL	m_Radiation;
	BOOL	m_RootCO2;
	BOOL	m_RootMass;
	BOOL	m_ShootMass;
	BOOL	m_SnowPack;
	BOOL	m_SoilCO2;
	BOOL	m_SoilM1;
	BOOL	m_SoilM2;
	BOOL	m_SoilM3;
	BOOL	m_SoilT1;
	BOOL	m_SoilT2;
	BOOL	m_SoilT3;
	BOOL	m_TotalCO2;
	BOOL	m_Transpiration;
	BOOL	m_YrReport;
	BOOL	m_SOC;
	BOOL	m_Nleach;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CountySave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CountySave)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUNTYSAVE_H__6E82BD15_B45C_4263_BEED_7DB2BAAF1322__INCLUDED_)
