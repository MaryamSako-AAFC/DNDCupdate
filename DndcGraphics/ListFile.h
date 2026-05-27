#if !defined(AFX_LISTFILE_H__19057844_AA16_4B95_ABC3_37674F29ADAF__INCLUDED_)
#define AFX_LISTFILE_H__19057844_AA16_4B95_ABC3_37674F29ADAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListFile dialog

class CListFile : public CDialog
{
// Construction
public:
	CListFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListFile)
	enum { IDD = IDD_CListFile };
	CListBox	m_ClimateFileListB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListFile)
	afx_msg void OnSelClimateFileB();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTFILE_H__19057844_AA16_4B95_ABC3_37674F29ADAF__INCLUDED_)
