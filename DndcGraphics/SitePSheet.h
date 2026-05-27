// SitePSheet.h : header file
//
// This class defines custom modal property sheet 
// CSitePSheet.
 // CSitePSheet has been customized to include
// a preview window.
 
#ifndef __SITEPSHEET_H__
#define __SITEPSHEET_H__

#include "SitePage1.h"
#include "SitePage2.h"
#include "SitePage3.h"
#include "SitePage4.h"
#include "SitePage5.h"
#include "SitePage6.h"
#include "SitePage7.h"
#include "SitePage8.h"
#include "SitePage9.h"
#include "SitePage10.h"
#include "SitePage11.h"
#include "SitePage15.h"
#include "dndc_save.h"
#include "ManureCycle.h"
#include "dndc_ManureFarmCrops.h"



/////////////////////////////////////////////////////////////////////////////
// CSitePSheet

class CSitePSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSitePSheet)

// Construction
public:
	CSitePSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	SitePage1 m_Page1;
	SitePage2 m_Page2;
	SitePage3 m_Page3;
	SitePage15 m_Page15;
	dndc_save m_Page4;
	dndc_ManureFarmCrops m_Page22;
//#ifdef MAURE
	ManureCycle m_Page53;
//#endif
/*	CSitePPage1 m_Page1;
	CSitePPage2 m_Page2;
	CSitePPage3 m_Page3;
	CSitePPage4 m_Page4;
	CSitePPage5 m_Page5;
	CSitePPage6 m_Page6;
	CSitePPage7 m_Page7;
	CSitePPage8 m_Page8;
	CSitePPage9 m_Page9;*/
	//CSitePviewW m_wndPreview;

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSitePSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSitePSheet();
		 virtual BOOL OnInitDialog();

// Generated message map functions
protected:
	//{{AFX_MSG(CSitePSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//_______________________________________________________________

class CForestPSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CForestPSheet)

// Construction
public:
	CForestPSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	SitePage2 m_Page2;
	//SitePage13 m_Page13;
	//SitePage14 m_Page14;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSitePSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CForestPSheet();
	virtual BOOL OnInitDialog();

// Generated message map functions
protected:
	//{{AFX_MSG(CSitePSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//_______________________________________________________________

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CSitePSheet

class CCropPSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCropPSheet)

// Construction
public:
	CCropPSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	SitePage4 m_Page4;
	SitePage5 m_Page5;
	SitePage6 m_Page6;
	SitePage7 m_Page7;
	SitePage8 m_Page8;
	SitePage9 m_Page9;
	SitePage10 m_Page10;
	SitePage11 m_Page11;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSitePSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCropPSheet();
		 virtual BOOL OnInitDialog();

// Generated message map functions
protected:
	//{{AFX_MSG(CSitePSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif	// __SITEPSHEET_H__
