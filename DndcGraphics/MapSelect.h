#if !defined(AFX_MAPSELECT_H__CFE706CE_5674_49DD_80D8_5B70227F7B1E__INCLUDED_)
#define AFX_MAPSELECT_H__CFE706CE_5674_49DD_80D8_5B70227F7B1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapSelect dialog

class MapSelect : public CDialog
{
// Construction
public:
	MapSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapSelect)
	enum { IDD = IDD_MapSelect };
	CString	m_yr;
	CString	m_Watershed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MapSelect)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPSELECT_H__CFE706CE_5674_49DD_80D8_5B70227F7B1E__INCLUDED_)
