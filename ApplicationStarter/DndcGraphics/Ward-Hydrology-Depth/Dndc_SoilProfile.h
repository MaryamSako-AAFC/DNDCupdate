#if !defined(AFX_DNDC_SOILPROFILE1_H__78DA7BA0_72EB_4018_A953_8487AA72AC59__INCLUDED_)
#define AFX_DNDC_SOILPROFILE1_H__78DA7BA0_72EB_4018_A953_8487AA72AC59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DNDC_SoilProfile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DNDC_SoilProfile dialog

class DNDC_SoilProfile : public CDialog
{
// Construction
public:
	DNDC_SoilProfile(CWnd* pParent = NULL);   // standard constructor
	void SaveProfileData(int SS, char *cst);

// Dialog Data
	//{{AFX_DATA(DNDC_SoilProfile)
	enum { IDD = IDD_SoilProfile };
	CComboBox	m_Texture9;
	CComboBox	m_Texture8;
	CComboBox	m_Texture7;
	CComboBox	m_Texture6;
	CComboBox	m_Texture5;
	CComboBox	m_Texture4;
	CComboBox	m_Texture3;
	CComboBox	m_Texture2;
	CComboBox	m_Texture10;
	CComboBox	m_Texture1;
	float	m_SPc1;
	float	m_SPc10;
	float	m_SPc2;
	float	m_SPc3;
	float	m_SPc4;
	float	m_SPc5;
	float	m_SPc6;
	float	m_SPc7;
	float	m_SPc8;
	float	m_SPc9;
	float	m_SPd1;
	float	m_SPd10;
	float	m_SPd2;
	float	m_SPd3;
	float	m_SPd4;
	float	m_SPd5;
	float	m_SPd6;
	float	m_SPd7;
	float	m_SPd8;
	float	m_SPd9;
	float	m_SPfc1;
	float	m_SPfc10;
	float	m_SPfc2;
	float	m_SPfc3;
	float	m_SPfc4;
	float	m_SPfc5;
	float	m_SPfc6;
	float	m_SPfc7;
	float	m_SPfc8;
	float	m_SPfc9;
	float	m_SPhy1;
	float	m_SPhy10;
	float	m_SPhy2;
	float	m_SPhy3;
	float	m_SPhy4;
	float	m_SPhy5;
	float	m_SPhy6;
	float	m_SPhy7;
	float	m_SPhy8;
	float	m_SPhy9;
	int		m_SPlayers;
	float	m_SPph1;
	float	m_SPph10;
	float	m_SPph2;
	float	m_SPph3;
	float	m_SPph4;
	float	m_SPph5;
	float	m_SPph6;
	float	m_SPph7;
	float	m_SPph8;
	float	m_SPph9;
	float	m_SPpo1;
	float	m_SPpo10;
	float	m_SPpo2;
	float	m_SPpo3;
	float	m_SPpo4;
	float	m_SPpo5;
	float	m_SPpo6;
	float	m_SPpo7;
	float	m_SPpo8;
	float	m_SPpo9;
	float	m_SPsoc1;
	float	m_SPsoc10;
	float	m_SPsoc2;
	float	m_SPsoc3;
	float	m_SPsoc4;
	float	m_SPsoc5;
	float	m_SPsoc6;
	float	m_SPsoc7;
	float	m_SPsoc8;
	float	m_SPsoc9;
	float	m_SPth1;
	float	m_SPth10;
	float	m_SPth2;
	float	m_SPth3;
	float	m_SPth4;
	float	m_SPth5;
	float	m_SPth6;
	float	m_SPth7;
	float	m_SPth8;
	float	m_SPth9;
	float	m_SPthickness;
	float	m_SPwp5;
	float	m_SPwp1;
	float	m_SPwp10;
	float	m_SPwp2;
	float	m_SPwp3;
	float	m_SPwp4;
	float	m_SPwp6;
	float	m_SPwp7;
	float	m_SPwp8;
	float	m_SPwp9;
	int m_SPso1;
	int m_SPso2;
	int m_SPso3;
	int m_SPso4;
	int m_SPso5;
	int m_SPso6;
	int m_SPso7;
	int m_SPso8;
	int m_SPso9;
	int m_SPso10;
	CString	m_ProfileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DNDC_SoilProfile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DNDC_SoilProfile)
	afx_msg void OnSelchangeSoiltexture1();
	afx_msg void OnSelchangeSoiltexture2();
	afx_msg void OnSelchangeSoiltexture3();
	afx_msg void OnSelchangeSoiltexture4();
	afx_msg void OnSelchangeSoiltexture5();
	afx_msg void OnSelchangeSoiltexture6();
	afx_msg void OnSelchangeSoiltexture7();
	afx_msg void OnSelchangeSoiltexture8();
	afx_msg void OnSelchangeSoiltexture9();
	afx_msg void OnSelchangeSoiltexture10();
	afx_msg void OnSPsave();
	afx_msg void OnSPread();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_SOILPROFILE1_H__78DA7BA0_72EB_4018_A953_8487AA72AC59__INCLUDED_)
