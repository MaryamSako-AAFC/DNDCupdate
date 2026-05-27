#if !defined(AFX_WIZARDUNCERTAINTY_H__04D8A786_DFAD_40B5_9167_12E48D2A721F__INCLUDED_)
#define AFX_WIZARDUNCERTAINTY_H__04D8A786_DFAD_40B5_9167_12E48D2A721F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardUncertainty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WizardUncertainty dialog

class WizardUncertainty : public CDialog
{
// Construction
public:
	WizardUncertainty(CWnd* pParent = NULL);   // standard constructor

	float dSOC[20], dPH[20], dBD[20], dCLAY[20];

	void OnMSFmethod2(void);

	

// Dialog Data
	//{{AFX_DATA(WizardUncertainty)
	enum { IDD = IDD_WizardUncertainty };
	CString	m_StateName;
	CString	m_CountyName;
	CString	m_CropName;
	CString	m_DensityRange;
	CString	m_PhRange;
	CString	m_SOCRange;
	CString	m_ClayRange;
	int		m_Size;
	int		m_Year;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WizardUncertainty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WizardUncertainty)
	afx_msg void OnWizardUncertainData();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMSFmethod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDUNCERTAINTY_H__04D8A786_DFAD_40B5_9167_12E48D2A721F__INCLUDED_)
