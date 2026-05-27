#if !defined(AFX_GLOBEDATA_H__2E71D1D7_628B_4EA3_8BC5_CC1FA64B84DC__INCLUDED_)
#define AFX_GLOBEDATA_H__2E71D1D7_628B_4EA3_8BC5_CC1FA64B84DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobeData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GlobeData dialog

class GlobeData : public CDialog
{
// Construction
public:
	GlobeData(CWnd* pParent = NULL);   // standard constructor

	char FileName[200];
	float N2O_flux(float C,float CLAY,float T,float P,float PH,float CN,float M,float Rf,float LU);

	float Background_N2O, Fertilizer_N2O;

// Dialog Data
	//{{AFX_DATA(GlobeData)
	enum { IDD = IDD_GlobeData };
	CComboBox	m_Continent;
	CListBox	m_DataFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GlobeData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GlobeData)
	afx_msg void OnDataFile();
	afx_msg void OnDataCalculate();
	afx_msg void OnSelchangeContinent();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBEDATA_H__2E71D1D7_628B_4EA3_8BC5_CC1FA64B84DC__INCLUDED_)
