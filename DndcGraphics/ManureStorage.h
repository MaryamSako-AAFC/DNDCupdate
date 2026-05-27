#if !defined(AFX_MANURESTORAGE_H__4068C554_FDA4_43B4_A2AA_997C8757CE3B__INCLUDED_)
#define AFX_MANURESTORAGE_H__4068C554_FDA4_43B4_A2AA_997C8757CE3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManureStorage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManureStorage dialog

class ManureStorage : public CDialog
{
// Construction
public:
	ManureStorage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ManureStorage)
	enum { IDD = IDD_STORAGE };
	int		m_separate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManureStorage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManureStorage)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANURESTORAGE_H__4068C554_FDA4_43B4_A2AA_997C8757CE3B__INCLUDED_)
