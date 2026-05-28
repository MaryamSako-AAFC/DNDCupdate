#if !defined(AFX_BATCHRUN_H__851A5F50_D0F2_4DE9_B471_539CC0A8BB7D__INCLUDED_)
#define AFX_BATCHRUN_H__851A5F50_D0F2_4DE9_B471_539CC0A8BB7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchRun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BatchRun dialog

class BatchRun : public CDialog
{
// Construction
public:
	BatchRun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BatchRun)
	enum { IDD = IDD_Batch };
	CListBox	m_BatchFileName;
	BOOL	m_DailyResult;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BatchRun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BatchRun)
	afx_msg void OnSelectFile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHRUN_H__851A5F50_D0F2_4DE9_B471_539CC0A8BB7D__INCLUDED_)
