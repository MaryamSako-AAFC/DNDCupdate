#if !defined(AFX_GLOBEMAP_H__E55AB2C8_0F71_475F_90BA_086850C77F9C__INCLUDED_)
#define AFX_GLOBEMAP_H__E55AB2C8_0F71_475F_90BA_086850C77F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobeMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GlobeMap dialog

class GlobeMap : public CDialog
{
// Construction
public:
	GlobeMap(CWnd* pParent = NULL);   // standard constructor
	void WorldMapping(int region, int crop, int soil, int manage);

	void DrawMap(void);

// Dialog Data
	//{{AFX_DATA(GlobeMap)
	enum { IDD = IDD_GlobeMap };
	CComboBox	m_SelectManage;
	CComboBox	m_SelectSoil;
	CListBox	m_MapFileName;
	CComboBox	m_Item;
	int		m_Column;
	int		m_Row;
	int		m_SelectRegion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GlobeMap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GlobeMap)
	afx_msg void OnSelMapFile();
	afx_msg void OnDblclkMapFileList();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnSelchangeItem();
	afx_msg void OnSelchangeSelectSoil();
	afx_msg void OnSelchangeSelectManage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBEMAP_H__E55AB2C8_0F71_475F_90BA_086850C77F9C__INCLUDED_)
