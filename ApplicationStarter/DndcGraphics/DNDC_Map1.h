#if !defined(AFX_DNDC_MAP1_H__B58BCAFE_FF33_48DA_8CB1_51899DD02753__INCLUDED_)
#define AFX_DNDC_MAP1_H__B58BCAFE_FF33_48DA_8CB1_51899DD02753__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DNDC_Map1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DNDC_Map dialog

class DNDC_Map : public CDialog
{
// Construction
public:
	DNDC_Map(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DNDC_Map)
	enum { IDD = IDD_DndcMap };
	CListBox	m_DndcFileList;
	CComboBox	m_MapItem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DNDC_Map)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DNDC_Map)
	afx_msg void OnSelectDNDCFile();
	virtual void OnOK();
	afx_msg void OnDblclkDndcFileList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_MAP1_H__B58BCAFE_FF33_48DA_8CB1_51899DD02753__INCLUDED_)
