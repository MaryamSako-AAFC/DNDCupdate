#if !defined(AFX_SCSDLG_H__4266F508_407D_4B32_92BC_C3BD565AA62C__INCLUDED_)
#define AFX_SCSDLG_H__4266F508_407D_4B32_92BC_C3BD565AA62C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SCSDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSCSDlg dialog

class CSCSDlg : public CDialog
{
// Construction
public:
	CSCSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSCSDlg)
	enum { IDD = IDD_SCSDlg };
	float	m_CN;
	float	m_FCSCS;
	float	m_ProSCS;
	float	m_SlopeSCS;
	float	m_WPSCS;
	float	m_WatershedArea;
	float	m_RoughLand;
	float	m_RoughChannel;
	float	m_SlopeLength;
	float	m_ChannelSlope;
	float	m_ChannelLength;
	float	m_LandManage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSCSDlg)
	afx_msg void OnCancel();
	afx_msg void OnSCSOk();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnFindCN();
	afx_msg void OnReadCN();
	afx_msg void OnLandRough();
	afx_msg void OnChannelRough2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCSDLG_H__4266F508_407D_4B32_92BC_C3BD565AA62C__INCLUDED_)
