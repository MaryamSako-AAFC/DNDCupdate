#if !defined(AFX_MONTECARLOPARAMETERS_H__669CF6CE_AE70_4636_BC8D_A7985CB360D8__INCLUDED_)
#define AFX_MONTECARLOPARAMETERS_H__669CF6CE_AE70_4636_BC8D_A7985CB360D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonteCarloParameters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MonteCarloParameters dialog

class MonteCarloParameters : public CDialog
{
// Construction
public:
	MonteCarloParameters(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MonteCarloParameters)
	enum { IDD = IDD_MonteCarloParameters };
	float	m_1;
	float	m_10;
	float	m_11;
	float	m_12;
	float	m_13;
	float	m_14;
	float	m_15;
	float	m_16;
	float	m_17;
	float	m_18;
	float	m_19;
	float	m_2;
	float	m_20;
	float	m_21;
	float	m_22;
	float	m_23;
	float	m_24;
	float	m_25;
	float	m_26;
	float	m_27;
	float	m_28;
	float	m_29;
	float	m_3;
	float	m_30;
	float	m_31;
	float	m_32;
	float	m_33;
	float	m_34;
	float	m_35;
	float	m_36;
	float	m_37;
	float	m_38;
	float	m_39;
	float	m_4;
	float	m_40;
	float	m_41;
	float	m_42;
	float	m_43;
	float	m_44;
	float	m_45;
	float	m_46;
	float	m_47;
	float	m_48;
	float	m_49;
	float	m_5;
	float	m_50;
	float	m_51;
	float	m_6;
	float	m_7;
	float	m_8;
	float	m_9;
	int		m_SampleSize;
	BOOL	m_C1;
	BOOL	m_C10;
	BOOL	m_C11;
	BOOL	m_C12;
	BOOL	m_C13;
	BOOL	m_C14;
	BOOL	m_C15;
	BOOL	m_C16;
	BOOL	m_C17;
	BOOL	m_C18;
	BOOL	m_C19;
	BOOL	m_C2;
	BOOL	m_C20;
	BOOL	m_C21;
	BOOL	m_C22;
	BOOL	m_C23;
	BOOL	m_C24;
	BOOL	m_C25;
	BOOL	m_C26;
	BOOL	m_C27;
	BOOL	m_C28;
	BOOL	m_C29;
	BOOL	m_C3;
	BOOL	m_C30;
	BOOL	m_C31;
	BOOL	m_C32;
	BOOL	m_C33;
	BOOL	m_C34;
	BOOL	m_C35;
	BOOL	m_C36;
	BOOL	m_C37;
	BOOL	m_C38;
	BOOL	m_C39;
	BOOL	m_C4;
	BOOL	m_C40;
	BOOL	m_C41;
	BOOL	m_C42;
	BOOL	m_C43;
	BOOL	m_C44;
	BOOL	m_C45;
	BOOL	m_C46;
	BOOL	m_C47;
	BOOL	m_C48;
	BOOL	m_C49;
	BOOL	m_C5;
	BOOL	m_C50;
	BOOL	m_C51;
	BOOL	m_C6;
	BOOL	m_C7;
	BOOL	m_C8;
	BOOL	m_C9;
	int		m_StartDay;
	int		m_EndDay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MonteCarloParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MonteCarloParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTECARLOPARAMETERS_H__669CF6CE_AE70_4636_BC8D_A7985CB360D8__INCLUDED_)
