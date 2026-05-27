#if !defined(AFX_DNDC_MANUREFARMCROPS_H__933E59CC_C90D_40F1_B2C2_CD881BEBFF8C__INCLUDED_)
#define AFX_DNDC_MANUREFARMCROPS_H__933E59CC_C90D_40F1_B2C2_CD881BEBFF8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dndc_ManureFarmCrops.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dndc_ManureFarmCrops dialog

class dndc_ManureFarmCrops : public CPropertyPage
{
	DECLARE_DYNCREATE(dndc_ManureFarmCrops)

// Construction
public:
	dndc_ManureFarmCrops();
	~dndc_ManureFarmCrops();

// Dialog Data
	//{{AFX_DATA(dndc_ManureFarmCrops)
	enum { IDD = IDD_ManureFarmCrops };
	float	m_TotalHa;
	int		m_CropType1;
	int		m_CropType10;
	int		m_CropType2;
	int		m_CropType3;
	int		m_CropType4;
	int		m_CropType5;
	int		m_CropType6;
	int		m_CropType7;
	int		m_CropType8;
	int		m_CropType9;
	float	m_land1;
	float	m_land10;
	float	m_land2;
	float	m_land3;
	float	m_land4;
	float	m_land5;
	float	m_land6;
	float	m_land7;
	float	m_land8;
	float	m_land9;
	float	m_manure1;
	float	m_manure10;
	float	m_manure2;
	float	m_manure3;
	float	m_manure4;
	float	m_manure5;
	float	m_manure6;
	float	m_manure7;
	float	m_manure8;
	float	m_manure9;
	int		m_CropSelect;
	int		m_unit;
	int		m_FarmYears;
	int		m_FarmYear;
	int		m_TotalFields;
	float	m_SumHa;
	float	m_SumManure;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(dndc_ManureFarmCrops)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(dndc_ManureFarmCrops)
	afx_msg void OnManureCrop();
	virtual BOOL OnInitDialog();
	afx_msg void Onunit();
	afx_msg void Onunit2();
	afx_msg void OnNextRotation3();
	afx_msg void OnLastRotation3();
	afx_msg void OnKillfocusTotalFields();
	afx_msg void OnCropSelect();
	afx_msg void OnSetfocusSumHa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_MANUREFARMCROPS_H__933E59CC_C90D_40F1_B2C2_CD881BEBFF8C__INCLUDED_)
