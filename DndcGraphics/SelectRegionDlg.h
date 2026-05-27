//{{AFX_INCLUDES()
#include "map.h"
//}}AFX_INCLUDES
#if !defined(AFX_SELECTREGIONDLG_H__ECD04245_312D_40B0_8BE4_E57BFCBA72F4__INCLUDED_)
#define AFX_SELECTREGIONDLG_H__ECD04245_312D_40B0_8BE4_E57BFCBA72F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectRegionDlg.h : header file
//
typedef struct
{
	CString		layerName;
	int			lineWidth;
	COLORREF	lineColor;
	bool		fill;
	COLORREF	fillColor;
} LAYERINFO;

#include "afxtempl.h"
#include "morecordset.h"
#include "dndc71.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectRegionDlg dialog
class CLabelStatic : public CStatic
{
public:
	void SetText(CString text);
	CRect GetRect();

protected:
	CString m_text;

	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};


class CSelectRegionDlg : public CDialog
{
// Construction
public:
	CSelectRegionDlg(CWnd* pParent = NULL);   // standard constructor
	~CSelectRegionDlg();

// Dialog Data
	//{{AFX_DATA(CSelectRegionDlg)
	enum { IDD = IDD_SELECTREGION };
	CComboBox	m_WizardCrops;
	CLabelStatic	m_locationLabel;
	CMoMap	m_map;
	CString	m_SiteName;
	//}}AFX_DATA
protected:
	CString			m_mapPath;
	CTypedPtrArray<CPtrArray, LAYERINFO*> m_layers;
	CString			m_layerSelect;
	CString			m_labelField;
	CString			m_idField;
	CString	m_STATE;
	CString	m_longitude;

	CString			m_valuemapLayer;
	CString			m_valuemapField;

	int				m_mouseAction;
	
	CMoRecordset	m_selectionRecs;

	void DrawSelection();
	void ValueMapLayer();

public:
	CString m_selectedLabel;
	CString m_selectedId;
	BOOL m_movelabel;
	
	void SetMapPath(CString path) { m_mapPath = path;	}
	void SetLayerSelected(CString layer, CString labelfield, CString idfield, CString latitude, CString longitude);
	void SetValueMapLayer(CString layer, CString field);
	void AddLayer(CString name, int lineWidth, COLORREF lineColor,	bool fill, COLORREF fillcolor);
	//void NewAddLayer(CMap1& map, const CString& path, COLORREF color = -1, LPDISPATCH renderer = 0);

public:
	int CropType, WWW[252], CropOrder;
	CString WizardCountyID, stateID;
	char Sname[200], Cname[200];
	float crop_ha[90];
	CString m_SCname;
	char m_Watershed[200], m_yr[200], m_FileName[300];

	void SaveRegionDatatoFile(void);
	float OptimumYield(int CT);
	int clay_texture(float Clay);
	BOOL OnInitDialog1();
	void County_data(CString WizardCountyID, int domain);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectRegionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectRegionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMoveMap(short Button, short Shift, long X, long Y);
	afx_msg void OnMouseUpMap(short Button, short Shift, long X, long Y);
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnPan();
	afx_msg void OnFullmap();
	afx_msg void OnMouseDownMap(short Button, short Shift, long X, long Y);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnAfterTrackingLayerDrawMap(long hDC);
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnSelchangeWizardCrops();
	afx_msg void OnLandCover();
	afx_msg void OnAfterLayerDrawMap(short index, BOOL canceled, long hDC);
	afx_msg void OnBeforeTrackingLayerDrawMap(long hDC);
	afx_msg void OnBeforeLayerDrawMap(short index, long hDC);
	afx_msg void OnSelectFarm();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTREGIONDLG_H__ECD04245_312D_40B0_8BE4_E57BFCBA72F4__INCLUDED_)
