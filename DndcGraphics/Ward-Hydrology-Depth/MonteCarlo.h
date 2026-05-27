#if !defined(AFX_MONTECARLO_H__8167CBC0_9899_436E_AE3A_BCB5BA604217__INCLUDED_)
#define AFX_MONTECARLO_H__8167CBC0_9899_436E_AE3A_BCB5BA604217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonteCarlo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MonteCarlo dialog

class MonteCarlo : public CDialog
{
// Construction
public:
	MonteCarlo(CWnd* pParent = NULL);   // standard constructor

	float dSOC[10];
	float dPH[10];
	float dBD[10];
	float dCLAY[10];
	

// Dialog Data
	//{{AFX_DATA(MonteCarlo)
	enum { IDD = IDD_SoilRange };
	CString	m_SOC;
	CString	m_clay;
	CString	m_density;
	CString	m_pH;
	int		m_size;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MonteCarlo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MonteCarlo)
	afx_msg void Ondata();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTECARLO_H__8167CBC0_9899_436E_AE3A_BCB5BA604217__INCLUDED_)
