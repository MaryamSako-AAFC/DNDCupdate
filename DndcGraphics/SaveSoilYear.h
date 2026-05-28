#if !defined(AFX_SAVESOILYEAR_H__FA26D201_E6B0_4E76_864D_2D218A8E1375__INCLUDED_)
#define AFX_SAVESOILYEAR_H__FA26D201_E6B0_4E76_864D_2D218A8E1375__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveSoilYear.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SaveSoilYear dialog

class SaveSoilYear : public CDialog
{
// Construction
public:
	SaveSoilYear(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SaveSoilYear)
	enum { IDD = IDD_SaveSoilFile };
	CListBox	m_SoilStatusList;
	int		m_SoilYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SaveSoilYear)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SaveSoilYear)
	afx_msg void OnSaveSoil();
	afx_msg void OnSoilStatusFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVESOILYEAR_H__FA26D201_E6B0_4E76_864D_2D218A8E1375__INCLUDED_)
