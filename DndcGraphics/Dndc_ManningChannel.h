#if !defined(AFX_DNDC_MANNINGCHANNEL_H__EA6CD65E_DBD1_4334_9DF4_BA8A5E21BBAE__INCLUDED_)
#define AFX_DNDC_MANNINGCHANNEL_H__EA6CD65E_DBD1_4334_9DF4_BA8A5E21BBAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dndc_ManningChannel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dndc_ManningChannel dialog

class Dndc_ManningChannel : public CDialog
{
// Construction
public:
	Dndc_ManningChannel(CWnd* pParent = NULL);   // standard constructor

	

// Dialog Data
	//{{AFX_DATA(Dndc_ManningChannel)
	enum { IDD = IDD_ManningChannel };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dndc_ManningChannel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dndc_ManningChannel)
	afx_msg void OnMc1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_MANNINGCHANNEL_H__EA6CD65E_DBD1_4334_9DF4_BA8A5E21BBAE__INCLUDED_)
