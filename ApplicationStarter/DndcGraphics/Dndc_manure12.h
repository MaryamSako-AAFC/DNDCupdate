#if !defined(AFX_DNDC_MANURE12_H__076DD2F0_2E83_4921_A616_F7065412BE01__INCLUDED_)
#define AFX_DNDC_MANURE12_H__076DD2F0_2E83_4921_A616_F7065412BE01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dndc_manure12.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dndc_manure12 dialog

class Dndc_manure12 : public CDialog
{
// Construction
public:
	Dndc_manure12(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dndc_manure12)
	enum { IDD = IDD_Storage };
	int		m_StorageDays;
	float	m_StoreToCompost;
	float	m_StoreToDigester;
	float	m_StoreToField;
	float	m_StoreToLagoon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dndc_manure12)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dndc_manure12)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_MANURE12_H__076DD2F0_2E83_4921_A616_F7065412BE01__INCLUDED_)
