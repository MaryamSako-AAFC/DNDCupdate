#if !defined(AFX_WIZARDCROPS_H__D90D605C_B776_4E4E_8C5C_B4E60DCABD18__INCLUDED_)
#define AFX_WIZARDCROPS_H__D90D605C_B776_4E4E_8C5C_B4E60DCABD18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardCrops.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WizardCrops dialog

class WizardCrops : public CDialog
{
// Construction
public:
	WizardCrops(CWnd* pParent = NULL);   // standard constructor

	int CropType, stateID;
	int WizardCountyID;
	char Sname[200], Cname[200];
	float crop_ha[90];

	void SaveDatatoFile(void);
	float OptimumYield(int CT);
	int clay_texture(float Clay);

// Dialog Data
	//{{AFX_DATA(WizardCrops)
	enum { IDD = IDD_WizardCrops };
	CComboBox	m_WizardCrops;
	CString	m_SCname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WizardCrops)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WizardCrops)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeWizardCrops();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDCROPS_H__D90D605C_B776_4E4E_8C5C_B4E60DCABD18__INCLUDED_)
