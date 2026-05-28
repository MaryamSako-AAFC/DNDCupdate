#if !defined(AFX_MANUREDIGESTER_H__8999A888_B2F8_4813_8F4D_900AC11AC56C__INCLUDED_)
#define AFX_MANUREDIGESTER_H__8999A888_B2F8_4813_8F4D_900AC11AC56C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureDigester.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureDigester dialog

class ManureDigester : public CDialog
{
// Construction
public:
	ManureDigester(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManureDigester)
	enum { IDD = IDD_ManureDigester };
	float	m_RetentionDays;
	int		m_DigesterTempClass;
	float	m_ToField;
	float	m_ToMarket;
	float	m_ToRemain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureDigester)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureDigester)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUREDIGESTER_H__8999A888_B2F8_4813_8F4D_900AC11AC56C__INCLUDED_)
