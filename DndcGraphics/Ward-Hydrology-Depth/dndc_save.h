#if !defined(AFX_DNDC_SAVE_H__4FFAE775_F929_49FE_AB72_C74E91B1BF70__INCLUDED_)
#define AFX_DNDC_SAVE_H__4FFAE775_F929_49FE_AB72_C74E91B1BF70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dndc_save.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dndc_save dialog

class dndc_save : public CPropertyPage
{
	DECLARE_DYNCREATE(dndc_save)

// Construction
public:
	dndc_save();
	~dndc_save();

	void OnSavesite();

// Dialog Data
	//{{AFX_DATA(dndc_save)
	enum { IDD = IDD_PROPPAGE_save };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(dndc_save)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(dndc_save)
	//afx_msg void OnSavesite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC_SAVE_H__4FFAE775_F929_49FE_AB72_C74E91B1BF70__INCLUDED_)
