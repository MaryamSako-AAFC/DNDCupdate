#if !defined(AFX_MANURESILO_H__0E8212FB_3814_484A_B19B_FA14DC740AC7__INCLUDED_)
#define AFX_MANURESILO_H__0E8212FB_3814_484A_B19B_FA14DC740AC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureSilo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureSilo dialog

class ManureSilo : public CDialog
{
// Construction
public:
	ManureSilo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManureSilo)
	enum { IDD = IDD_ManureSsilo };
	int		m_SiloType;
	int		m_FeedType;
	float	m_BunckLength;
	float	m_Diameter;
	float	m_Height;
	float	m_SilageAmount;
	int		m_SiloNumber;
	float	m_DryFraction;
	int		m_FeedMixer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureSilo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureSilo)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANURESILO_H__0E8212FB_3814_484A_B19B_FA14DC740AC7__INCLUDED_)
