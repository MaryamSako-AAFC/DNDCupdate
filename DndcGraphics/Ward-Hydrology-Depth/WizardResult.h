#if !defined(AFX_WIZARDRESULT_H__9C84B53E_609C_4018_97D1_BCA82A9B672D__INCLUDED_)
#define AFX_WIZARDRESULT_H__9C84B53E_609C_4018_97D1_BCA82A9B672D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WizardResult dialog

class WizardResult : public CDialog
{
// Construction
public:
	WizardResult(CWnd* pParent = NULL);   // standard constructor
	void read_summary(int YR);

	char Site_Name[200], Crop_Name[150][200];
	CString CFN;
	CString rcd;
	//float year;
	float manureC, manureN, litterC, litterN, rootC, rootN, weedC, weedN, irriN, SoilFixN;
	float rainN, fertN, runoffN;
	float soilCO2, rootCO2, CH4, leachHumC, leachHumN, leachN, uptakeN, weedupN, NH3, N2O, NO, N2, NO2;
	char SelectedState[200], SelectedCounty[200];
	float dC; 
	int CropCode, WizardCountyID, year, HarvestDay[4], PlantDay[4];
	float C_CO2, C_N2O, C_CH4;
	float GWP_CO2,GWP_N2O, GWP_CH4, NetGWP;
	float haha;
	float yr_rain, yr_irri, yr_trans, yr_soil_ev, yr_pond_ev, yr_runoff, yr_leach_water, yr_GWsuply;
	float ProdC[4], prograin[4], prostraw[4], proroot[4], CropN[4], yr_avet, irriIndex, yr_addmc, dSOC;
	float Water_demand[4], N_demand[4], T_demand[4], fixN[4], uptakeSoilN[4], TDD[4], CropTrans[4];
	float Optimum_grain[4], Optimum_straw[4], Optimum_root[4];
// Dialog Data
	//{{AFX_DATA(WizardResult)
	enum { IDD = IDD_DIALOG2 };
	CComboBox	m_WizardYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WizardResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WizardResult)
	afx_msg void OnGhg();
	afx_msg void OnAgronomy();
	virtual BOOL OnInitDialog();
	afx_msg void OnCrop();
	afx_msg void OnWater();
	afx_msg void OnGwp();
	afx_msg void OnSelchangeWizardYear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDRESULT_H__9C84B53E_609C_4018_97D1_BCA82A9B672D__INCLUDED_)
