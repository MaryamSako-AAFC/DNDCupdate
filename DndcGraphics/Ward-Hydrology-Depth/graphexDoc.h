// graphexDoc.h : interface of the CGraphexDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHEXDOC_H__B2C5B6CA_351A_11D3_984A_00C04FC9DE52__INCLUDED_)
#define AFX_GRAPHEXDOC_H__B2C5B6CA_351A_11D3_984A_00C04FC9DE52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MapHigh  768//485//480//
#define MapWidth 1024//640//

class CGraphexDoc : public CDocument
{
protected: // create from serialization only
	CGraphexDoc();
	DECLARE_DYNCREATE(CGraphexDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphexDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CGraphexDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CObArray m_ObArray;

public:
	int		StopRun;//0:
	CString m_IfRedraw;
	CString m_ViewBorder;
	CString m_StateEdge;
	CString m_OldEdge;
	CString m_LatLonGrid;
	CString m_ColorBarStyle;
	CString m_MapValue;
	CString m_UnnamedRegion;
	CString m_EditDatabase;
	CString m_fixedrange;

	CBitmap pBitmap;
	CDC		memDC;
	CBitmap hBitmap;
	CDC		hmemDC;
	float   m_Coeff;

	int		MapStatus;	// 0:first run, 1:second or more time
	int		DNDC_or_Other;// 0:Others, 1:Run DNDC

	float   VR[6],DeVR[3][6];//DefaultVR[10][6],
	int     used[3];
	char    TStyle[256];
	COLORREF ColorArray[300];
	float   ValueROfColor[2][260];
	//ColorMode CM;

	CRect 	BoxRange[30], MapR[50];
	
	int		MapBoxFlag;
	int		Fontype,Fontsize;
	float	Ftscale;
	float	ydis;
	int		Jx;
	int		figWidth;//the width of main curve area
	CRect	SelfClient;
	
	int  Lindex;
	int	 AllOrLast;//0:all,1:last

	void Prepare();
	int  ClearAct();
	
	virtual void DeleteContents();

	int  PrepareMapData(char *base, char *ofile, int TYPE, 
								int Sort, float *SUM);
	int  PrepareMapFlux(int Country, int Type, int Sort, int state,
		float *gas,char *NAME);

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphexDoc)
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHEXDOC_H__B2C5B6CA_351A_11D3_984A_00C04FC9DE52__INCLUDED_)

