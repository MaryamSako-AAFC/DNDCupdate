#if !defined(AFX_GLOBEDATAEXTRACT_H__225C8B0B_84FE_4C55_B513_D101FE92B422__INCLUDED_)
#define AFX_GLOBEDATAEXTRACT_H__225C8B0B_84FE_4C55_B513_D101FE92B422__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobeDataExtract.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GlobeDataExtract dialog

class GlobeDataExtract : public CDialog
{
// Construction
public:
	GlobeDataExtract(CWnd* pParent = NULL);   // standard constructor
	void DataExtract1(int continent, int country);
	void DataExtract2(int continent, int country);

// Dialog Data
	//{{AFX_DATA(GlobeDataExtract)
	enum { IDD = IDD_ExtractCountryData };
	CProgressCtrl	m_ConvertGo;
	CComboBox	m_SouthAmerica;
	CComboBox	m_Oceania;
	CComboBox	m_Europe;
	CComboBox	m_Asia;
	CComboBox	m_Africa;
	CComboBox	m_NorthAmerica;
	CComboBox	m_country;
	CComboBox	m_continent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GlobeDataExtract)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GlobeDataExtract)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBEDATAEXTRACT_H__225C8B0B_84FE_4C55_B513_D101FE92B422__INCLUDED_)
