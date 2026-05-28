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
	void MapFile(int TU);
	void Summarizing(void);
// Dialog Data
	//{{AFX_DATA(DNDC_Map)
	enum { IDD = IDD_DndcMap };
	CComboBox	m_SelectedCrop;
	CComboBox	m_SelectCrop;
	CListBox	m_DndcFileList;
	CComboBox	m_MapItem;
	int		m_SourceDataFormat;
	int		m_Years;
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
	afx_msg void OnSelectGlobeFile();
	afx_msg void OnCountryData();
	afx_msg void OnWeighIrri();
	afx_msg void OnDraw();
	afx_msg void OnSelchangeMapItem();
	afx_msg void OnDrawGlobe();
	afx_msg void OnSelchangeSelectCrop();
	afx_msg void OnIntergrate();
	afx_msg void OnCountryYrAverage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_MAP1_H__B58BCAFE_FF33_48DA_8CB1_51899DD02753__INCLUDED_)
