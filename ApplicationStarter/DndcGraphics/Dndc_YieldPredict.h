#if !defined(AFX_DNDC_YIELDPREDICT_H__4E640AD2_9971_456F_BE76_7CC8B7064DEF__INCLUDED_)
#define AFX_DNDC_YIELDPREDICT_H__4E640AD2_9971_456F_BE76_7CC8B7064DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dndc_YieldPredict.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dndc_YieldPredict dialog

class Dndc_YieldPredict : public CDialog
{
// Construction
public:
	Dndc_YieldPredict(CWnd* pParent = NULL);   // standard constructor

	BOOL SetGridList(int DataType);

// Dialog Data
	//{{AFX_DATA(Dndc_YieldPredict)
	enum { IDD = IDD_YieldPredict };
	CComboBox	m_Croplist;
	CComboBox	m_GridList;
	int		m_YieldLocation;
	int		m_YieldYear;
	int		m_YieldToday;
	int		m_YieldMonth;
	int		m_database;
	char CropSystemName[160][50], CropSystemID[160][30];
	int CropSystemNumber0;
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dndc_YieldPredict)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dndc_YieldPredict)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void Ondatabase();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_YIELDPREDICT_H__4E640AD2_9971_456F_BE76_7CC8B7064DEF__INCLUDED_)
