#if !defined(AFX_REGIONSELECTCROPS_H__041956A4_B37C_412E_AAD1_0352D1B1C8BC__INCLUDED_)
#define AFX_REGIONSELECTCROPS_H__041956A4_B37C_412E_AAD1_0352D1B1C8BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegionSelectCrops.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RegionSelectCrops dialog

class RegionSelectCrops : public CDialog
{
// Construction
public:
	RegionSelectCrops(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RegionSelectCrops)
	enum { IDD = IDD_SelectCrops };
	BOOL	m_0;
	BOOL	m_9;
	BOOL	m_10;
	BOOL	m_11;
	BOOL	m_12;
	BOOL	m_13;
	BOOL	m_14;
	BOOL	m_15;
	BOOL	m_16;
	BOOL	m_17;
	BOOL	m_18;
	BOOL	m_1;
	BOOL	m_19;
	BOOL	m_20;
	BOOL	m_21;
	BOOL	m_22;
	BOOL	m_23;
	BOOL	m_24;
	BOOL	m_25;
	BOOL	m_26;
	BOOL	m_27;
	BOOL	m_28;
	BOOL	m_2;
	BOOL	m_29;
	BOOL	m_30;
	BOOL	m_31;
	BOOL	m_32;
	BOOL	m_33;
	BOOL	m_34;
	BOOL	m_35;
	BOOL	m_36;
	BOOL	m_37;
	BOOL	m_38;
	BOOL	m_3;
	BOOL	m_39;
	BOOL	m_40;
	BOOL	m_41;
	BOOL	m_42;
	BOOL	m_4;
	BOOL	m_5;
	BOOL	m_6;
	BOOL	m_7;
	BOOL	m_8;
	BOOL	m_00;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RegionSelectCrops)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RegionSelectCrops)
	virtual void OnOK();
	afx_msg void OnCheck0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGIONSELECTCROPS_H__041956A4_B37C_412E_AAD1_0352D1B1C8BC__INCLUDED_)
