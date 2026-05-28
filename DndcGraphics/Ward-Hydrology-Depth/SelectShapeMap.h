#if !defined(AFX_SELECTSHAPEMAP_H__F9C6A9D2_F3CA_42A7_9F49_6C3F910D494C__INCLUDED_)
#define AFX_SELECTSHAPEMAP_H__F9C6A9D2_F3CA_42A7_9F49_6C3F910D494C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectShapeMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectShapeMap dialog

class SelectShapeMap : public CDialog
{
// Construction
public:
	SelectShapeMap(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectShapeMap)
	enum { IDD = IDD_DIALOG5 };
	CListBox	m_ShapeFileList;
	int		m_LayerNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectShapeMap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectShapeMap)
	afx_msg void OnSelectShapeFile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTSHAPEMAP_H__F9C6A9D2_F3CA_42A7_9F49_6C3F910D494C__INCLUDED_)
