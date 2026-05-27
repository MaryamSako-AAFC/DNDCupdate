#if !defined(AFX_REGIONMAP_H__36E1074E_0971_4C4C_AA00_B7E1A5DC4514__INCLUDED_)
#define AFX_REGIONMAP_H__36E1074E_0971_4C4C_AA00_B7E1A5DC4514__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegionMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RegionMap dialog

class RegionMap : public CDialog
{
// Construction
public:
	RegionMap(CWnd* pParent = NULL);   // standard constructor

	int RR, GG, BB,LR,LG,LB, Province;
	//char NameSeries[150][50];
	int Provinces, FluxType;
	float NationFlux[50], NationHa[50], CountryFlux, CountryHa, scale;


	void ReadGIS(int RegionID, int CountryID, int ProvinceID, char *RegionName, char *CountryName);
	void DrawPolygon(char *F6, char *F5, char *F4, char *F3, char *F2, char *F1, int RegionID, int CountryID, int ProvinceID);
	void ReadOutput(int RegionID, int CountryID);
// Dialog Data
	//{{AFX_DATA(RegionMap)
	enum { IDD = IDD_ReginMap };
	CListBox	m_OutputFileList;
	int		m_MapSelect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RegionMap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RegionMap)
	afx_msg void OnDrawMap();
	afx_msg void OnSelectOutputFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGIONMAP_H__36E1074E_0971_4C4C_AA00_B7E1A5DC4514__INCLUDED_)
