// dndc71.h : main header file for the DNDC71 application
//

#if !defined(AFX_DNDC71_H__F8A3BE33_D27A_11D3_A713_005004A6D36F__INCLUDED_)
#define AFX_DNDC71_H__F8A3BE33_D27A_11D3_A713_005004A6D36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// graphexApp:
// See dndc71.cpp for the implementation of this class
//

class graphexApp : public CWinApp
{
public:
	graphexApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(graphexApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(graphexApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDC71_H__F8A3BE33_D27A_11D3_A713_005004A6D36F__INCLUDED_)
