#if !defined(AFX_EXTRACTDATA_H__16B0B567_77C2_482B_BC85_F0DA633460A8__INCLUDED_)
#define AFX_EXTRACTDATA_H__16B0B567_77C2_482B_BC85_F0DA633460A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtractData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ExtractData dialog

class ExtractData : public CDialog
{
// Construction
public:
	ExtractData(CWnd* pParent = NULL);   // standard constructor
	
	void ReadWrite(void);

// Dialog Data
	//{{AFX_DATA(ExtractData)
	enum { IDD = IDD_ExtractData };
	CListBox	m_OutputFileList;
	int		m_years;
	int		m_year1;
	BOOL	m_Yield;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ExtractData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ExtractData)
	afx_msg void OnSelectFile();
	virtual void OnOK();
	afx_msg void OnDblclkOutputFileList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRACTDATA_H__16B0B567_77C2_482B_BC85_F0DA633460A8__INCLUDED_)
