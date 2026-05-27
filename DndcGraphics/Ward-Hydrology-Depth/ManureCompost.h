#if !defined(AFX_MANURECOMPOST_H__660E2DAD_E79C_4A02_9FDF_6A801290B278__INCLUDED_)
#define AFX_MANURECOMPOST_H__660E2DAD_E79C_4A02_9FDF_6A801290B278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureCompost.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureCompost dialog

class ManureCompost : public CDialog
{
// Construction
public:
	ManureCompost(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManureCompost)
	enum { IDD = IDD_ManureCompost };
	float	m_CompostDensity;
	float	m_Remain;
	float	m_ToField;
	float	m_ToMarket;
	float	m_AdditiveAmount;
	float	m_AdditiveCN;
	float	m_RemoveFrequency;
	int		m_unit;
	int		m_CompostCover;
	int		m_CompostRemoveTimes;
	int		m_RemoveID;
	int		m_RemoveMonth;
	int		m_RemoveDay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureCompost)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureCompost)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void Onunit();
	afx_msg void Onunit2();
	afx_msg void OnRevome1();
	afx_msg void OnRemove2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANURECOMPOST_H__660E2DAD_E79C_4A02_9FDF_6A801290B278__INCLUDED_)
