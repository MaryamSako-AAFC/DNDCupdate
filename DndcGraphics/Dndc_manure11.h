#if !defined(AFX_DNDC_MANURE11_H__98F42BEB_AD9B_4ED2_9DEA_E86831668ABB__INCLUDED_)
#define AFX_DNDC_MANURE11_H__98F42BEB_AD9B_4ED2_9DEA_E86831668ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dndc_manure11.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dndc_manure11 dialog

class Dndc_manure11 : public CDialog
{
// Construction
public:
	Dndc_manure11(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dndc_manure11)
	enum { IDD = IDD_ManureFeeds };
	float	m_4;
	float	m_10;
	float	m_100;
	float	m_101;
	float	m_102;
	float	m_103;
	float	m_104;
	float	m_105;
	float	m_106;
	float	m_107;
	float	m_108;
	float	m_109;
	float	m_11;
	float	m_110;
	float	m_111;
	float	m_112;
	float	m_113;
	float	m_114;
	float	m_115;
	float	m_116;
	float	m_117;
	float	m_118;
	float	m_119;
	float	m_12;
	float	m_120;
	float	m_121;
	float	m_122;
	float	m_123;
	float	m_124;
	float	m_125;
	float	m_126;
	float	m_127;
	float	m_128;
	float	m_129;
	float	m_13;
	float	m_14;
	float	m_15;
	float	m_16;
	float	m_17;
	float	m_18;
	float	m_19;
	float	m_20;
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
	float	m_52;
	float	m_53;
	float	m_54;
	float	m_55;
	float	m_56;
	float	m_57;
	float	m_58;
	float	m_59;
	float	m_6;
	float	m_60;
	float	m_61;
	float	m_62;
	float	m_63;
	float	m_64;
	float	m_65;
	float	m_66;
	float	m_67;
	float	m_68;
	float	m_69;
	float	m_7;
	float	m_70;
	float	m_71;
	float	m_72;
	float	m_73;
	float	m_74;
	float	m_75;
	float	m_76;
	float	m_77;
	float	m_78;
	float	m_79;
	float	m_8;
	float	m_80;
	float	m_81;
	float	m_82;
	float	m_83;
	float	m_84;
	float	m_85;
	float	m_86;
	float	m_87;
	float	m_88;
	float	m_89;
	float	m_9;
	float	m_90;
	float	m_91;
	float	m_92;
	float	m_93;
	float	m_94;
	float	m_95;
	float	m_96;
	float	m_97;
	float	m_98;
	float	m_99;
	float	m_21;
	float	m_1;
	int		m_unit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dndc_manure11)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dndc_manure11)
	virtual void OnOK();
	afx_msg void OnSuan();
	afx_msg void OnCancel();
	afx_msg void OnUnit1();
	afx_msg void Onunit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_MANURE11_H__98F42BEB_AD9B_4ED2_9DEA_E86831668ABB__INCLUDED_)
