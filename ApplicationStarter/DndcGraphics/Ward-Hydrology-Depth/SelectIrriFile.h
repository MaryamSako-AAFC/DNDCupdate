#if !defined(AFX_SELECTIRRIFILE_H__263DE9D7_0FE7_4FB2_B7B8_03AA899B88D5__INCLUDED_)
#define AFX_SELECTIRRIFILE_H__263DE9D7_0FE7_4FB2_B7B8_03AA899B88D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectIrriFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectIrriFile dialog

class SelectIrriFile : public CDialog
{
// Construction
public:
	SelectIrriFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectIrriFile)
	enum { IDD = IDD_SelectIrriFile };
	CListBox	m_IRRI;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectIrriFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectIrriFile)
	afx_msg void OnSelectAFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIRRIFILE_H__263DE9D7_0FE7_4FB2_B7B8_03AA899B88D5__INCLUDED_)
