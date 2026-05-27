#if !defined(AFX_OUNTYCROPS_H__438AF9DE_8834_4129_A941_D96CD45CB6F6__INCLUDED_)
#define AFX_OUNTYCROPS_H__438AF9DE_8834_4129_A941_D96CD45CB6F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ountyCrops.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CountyCrops dialog

class CountyCrops : public CDialog
{
// Construction
public:
	CountyCrops(CWnd* pParent = NULL);   // standard constructor

	int State_ID, CropCode;
	CString County_ID;
	float ha[60];

	void ShowCountyData(void);
	void SaveDatatoFile(void);
	float OptimumYield(int CT);
	int clay_texture(float Clay);

// Dialog Data
	//{{AFX_DATA(CountyCrops)
	enum { IDD = IDD_CountyCrop };
	float	m_crop1;
	float	m_crop2;
	float	m_crop3;
	float	m_crop4;
	float	m_crop5;
	float	m_crop6;
	float	m_crop7;
	float	m_crop8;
	float	m_crop9;
	float	m_crop10;
	float	m_crop11;
	float	m_crop12;
	float	m_crop13;
	float	m_crop14;
	float	m_crop15;
	float	m_crop16;
	float	m_crop17;
	float	m_crop18;
	CString	m_SelectedCounty;
	CString	m_SelectedState;
	int		m_SelectedCrop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CountyCrops)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CountyCrops)
	afx_msg void OnSiteView();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUNTYCROPS_H__438AF9DE_8834_4129_A941_D96CD45CB6F6__INCLUDED_)
