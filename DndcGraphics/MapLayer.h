#if !defined(AFX_MAPLAYER_H__A3C824C2_33E3_468F_BD61_661BD6E7D736__INCLUDED_)
#define AFX_MAPLAYER_H__A3C824C2_33E3_468F_BD61_661BD6E7D736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapLayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapLayer dialog

class MapLayer : public CDialog
{
// Construction
public:
	MapLayer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapLayer)
	enum { IDD = IDD_Batch1 };
	CListBox	m_MapLayer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapLayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MapLayer)
	afx_msg void OnSelectFile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPLAYER_H__A3C824C2_33E3_468F_BD61_661BD6E7D736__INCLUDED_)
