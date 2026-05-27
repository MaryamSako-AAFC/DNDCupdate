#if !defined(AFX_OMBINEFILES_H__7518CD00_2EDC_4D37_9CCB_47667121994B__INCLUDED_)
#define AFX_OMBINEFILES_H__7518CD00_2EDC_4D37_9CCB_47667121994B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ombineFiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CombineFiles dialog

class CombineFiles : public CDialog
{
// Construction
public:
	CombineFiles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CombineFiles)
	enum { IDD = IDD_CombineFiles };
	CListBox	m_FileList;
	int		m_Files;
	CString	m_newfile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CombineFiles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CombineFiles)
	afx_msg void OnSelClimateFile();
	afx_msg void OnMoveDown();
	afx_msg void OnMoveUp();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OMBINEFILES_H__7518CD00_2EDC_4D37_9CCB_47667121994B__INCLUDED_)
