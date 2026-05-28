#if !defined(AFX_MANURE_STORAGE_H__5AEE35AE_0FDF_4A85_9823_44842EF873E4__INCLUDED_)
#define AFX_MANURE_STORAGE_H__5AEE35AE_0FDF_4A85_9823_44842EF873E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Manure_storage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Manure_storage dialog

class Manure_storage : public CDialog
{
// Construction
public:
	Manure_storage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Manure_storage)
	enum { IDD = IDD_Storage };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Manure_storage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Manure_storage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANURE_STORAGE_H__5AEE35AE_0FDF_4A85_9823_44842EF873E4__INCLUDED_)
