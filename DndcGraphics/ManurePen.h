#if !defined(AFX_MANUREPEN_H__7D641BBB_21F3_4C99_A23A_4A7AA83C29DF__INCLUDED_)
#define AFX_MANUREPEN_H__7D641BBB_21F3_4C99_A23A_4A7AA83C29DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManurePen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManurePen dialog

class ManurePen : public CDialog
{
// Construction
public:
	ManurePen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManurePen)
	enum { IDD = IDD_Pen };
	CListBox	m_StockFileList;
	CComboBox	m_AnimalType;
	int		m_Stock1;
	float	m_FeedRate;
	float	m_Heads;
	float	m_ProteinPercent;
	float	m_FloorArea;
	int		m_SurfaceType;
	int		m_BedType;
	float	m_BedAmount;
	float	m_BadCN;
	float	m_BedFrequency;
	float	m_ManureMoveFrequency;
	float	m_FC;
	float	m_FD;
	float	m_FL;
	float	m_FR;
	float	m_UC;
	float	m_UD;
	float	m_UL;
	float	m_UR;
	float	m_PenStorage;
	int		m_unit;
	float	m_PenFeedP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManurePen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManurePen)
	virtual void OnOK();
	afx_msg void OnSelStockFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnStock1();
	afx_msg void OnStock2();
	afx_msg void Onunit();
	afx_msg void Onunit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUREPEN_H__7D641BBB_21F3_4C99_A23A_4A7AA83C29DF__INCLUDED_)
