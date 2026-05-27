// graphexView.h : interface of the CGraphexView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHEXVIEW_H__B2C5B6CC_351A_11D3_984A_00C04FC9DE52__INCLUDED_)
#define AFX_GRAPHEXVIEW_H__B2C5B6CC_351A_11D3_984A_00C04FC9DE52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DNDCgo.h"
#include <string>

class DBPointer 
{
public:
	//CMainFrame  *pMainF;
	CButton		*pDBase;
	CButton		*pModify;

	CComboBox   *pCountry;
	CComboBox   *pPro;
	CComboBox   *pCounty;
	CComboBox   *pDType;

	CStatic		*pIName;
	CEdit	    *pEdit;
	CListCtrl	*pListC;
	//CMSFlexGrid *pGrid;

	CButton		*pShowMap;
	CButton		*pVCountry;
	CButton		*pVState;

	CButton		*pAdd;
	CButton		*pMulti;
	CButton		*pNew;
	CButton		*pCoeffDir;
	CComboBox   *pCoeffType;
	CEdit		*pCoeffValue;
	CButton		*pCoeffSave;
	CButton		*pCoeffShow;

	DBPointer();
};


class CGraphexView : public CView
{
protected: // create from serialization only
	CGraphexView();
	DECLARE_DYNCREATE(CGraphexView)

// Attributes
public:
	CGraphexDoc* GetDocument();

		//menu control flag
	CString m_IfRedraw;
	CString m_IfPause;
	CString m_ViewBorder;//county boundary
	CString m_StateEdge; //state boundary
	CString m_OldEdge;
	CString m_LatLonGrid;
	CString m_Grey;
	CString m_BGR;
	CString m_BR;
	CString m_UserColor;
	CString m_MapValue;
	CString m_EditDatabase;
	CString m_UnnamedRegion;
	CString m_fixedrange;

		//Database management flag
	CString	m_DoWhat;//"DATABASE"  "COEFF"
	//CString	m_VShowFlag;//"ON" "OFF"
	//CString	m_VRegionFlag;//"COUNTRY" "STATE"

		//Coeffecient mode
	CString	m_CoeffModify;//Add,Multi,New

	CString	m_DBorCoeff;

private:
	CRect   m_rcPrintRect;
	MODEL_LINK_INFO link;

// Operations
public:
	int TotalCounty;
	CString County_ID;
	int CountyMapID[1000];
	float Xa, Xb, Ya, Yb;
	int Xc, Yc;
	float X1;
	int X2;
	float Y1;
	int Y2;
	int Crop_Type, Soil_landuse, year;
	char Farm_ID[100];
	int CropType[5];
	float CropArea[10], ha[21];
	int LandUse, SoilType;
	float grid_area, Crop_ha; 
	int SelectFlag, stateID;
	int Fc[300];
	float Cc[300];
	int MaxGG,aa;
	float MaxdSOC;
	int ShowSiteFlag;
	

	//WIZARD
	
	char Site_Name[200], CropName[200];
	CString CFN;
	CString rcd;
	float SOC1, SON1, SIN1, SOC2, SON2, SIN2;
	float manureC, manureN, litterC, litterN, rootC, rootN, weedC, weedN, irriN;
	float rainN, fertN, fixN, runoffN;
	float soilCO2, rootCO2, CH4, leachHumC, leachHumN, leachN, uptakeN, weedupN, NH3, N2O, NO, N2, NO2;
	char SelectedState[200], SelectedCounty[200];
	float dC; 
	int CropCode, WizardCountyID;
	float C_CO2, C_N2O, C_CH4;
	float GWP_CO2,GWP_N2O, GWP_CH4, NetGWP;
	float haha;
	float yr_rain, yr_irri, yr_trans, yr_soil_ev, yr_pond_ev, yr_runoff, yr_leach_water;
	float ProdC, prograin, prostraw, proroot, yr_avet, irriIndex, yr_addmc, dSOC, yr_GWsuply;
	

	void DrawCbalance(CGraphexDoc *pDoc);
	void DrawNbalance(CGraphexDoc *pDoc);
	void GWP(CGraphexDoc *pDoc);
	void ShowMapValue(CGraphexDoc *pDoc,CPoint point);
	//void MonteCarloChart(int method);
	

/*	int TotalCounty;
	int County_ID[1000];
	int CountyMapID[1000];
	float Xa, Xb, Ya, Yb;
	int Xc, Yc, Crop_Type, Soil_landuse, year;
	int Farm_ID, CropType[5];
	float CropArea[10];
	int LandUse, SoilType;	
	
	
	int c1, c2, c3;
	int SelectFlag;
	
*/

	
	

	//void draw_Cover(CDNDCshowDoc *pDoc);


	void draw_county1(CGraphexDoc *pDoc, int stateID);
	void read_scale(int ScaleID);
	void draw_states(CGraphexDoc *pDoc);
	void draw_a_state(CGraphexDoc *pDoc, int stateID);
	void Find_Grid(int point_x, int point_y, int ScaleID, int SSL);
	void draw_a_county(CGraphexDoc *pDoc, int WizardCountyID);
	void County_data(int WizardCountyID, int domain);
	void RunMonteCarlo(int method);
	void find_sector(int k, float dSOC);
	void DrawFrequency(CGraphexDoc *pDoc);
	void RunWizardMonteCarlo(int method);

	void draw_LandUse(CGraphexDoc *pDoc, int stateID, int cropID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphexView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	//virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	

protected:
	int m_Draw;
	HCURSOR m_hCursor;
	CPoint m_pOld;
	CPoint m_pOrigin;

//	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC *pDC,CPrintInfo* pInfo);

// Generated message map functions
protected:

	//{{AFX_MSG(CGraphexView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnIfRedarwAll();
	afx_msg void OnUpdateIfRedarwAll(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnIfStop();
	afx_msg void OnIfPause();
	afx_msg void OnUpdateIfPause(CCmdUI* pCmdUI);
	afx_msg void OnInputSite();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWorkmode1();
	afx_msg void OnShowmap();
	afx_msg void OnShowCounty();
	afx_msg void OnViewModifycolorscale();
	afx_msg void OnCropPropertyDB();
	afx_msg void OnPrepareState();
	afx_msg void OnNewRegionDB();
	afx_msg void OnIfDoOneTime();
	afx_msg void OnWorkmode();
	afx_msg void OnSelectCoeffDir();
	afx_msg void OnRunSite();//int option, int Monitor, int smaple, char *BatchPass
	afx_msg void OnInputRegion();
	afx_msg void OnRunRegion();
	afx_msg void OnMapping();
	afx_msg void OnSelectCounty();
	afx_msg void OnSelectState();
	afx_msg void OnMonteCarlo();
	afx_msg void OnRunUncertainty();
	afx_msg void OnDrawFlux();
	afx_msg void OnRegion();
	afx_msg void OnDrawMap();
	afx_msg void OnMCresult();
	afx_msg void OnExit();
	afx_msg void OnWizardSelectCounty();
	afx_msg void OnMapCounty();
	afx_msg void OnMapCrops();
	afx_msg void OnMapCorn();
	afx_msg void OnWWheat();
	afx_msg void OnSWheat();
	afx_msg void OnSunflower();
	afx_msg void OnSugarcane();
	afx_msg void OnSoybean();
	afx_msg void OnSorghum();
	afx_msg void OnBarley();
	afx_msg void OnBeet();
	afx_msg void OnCotton();
	afx_msg void OnLegumeHay();
	afx_msg void OnNonlegumehay();
	afx_msg void OnOats();
	afx_msg void OnPeanut();
	afx_msg void OnPineapple();
	afx_msg void OnPotato();
	afx_msg void OnRice();
	afx_msg void OnTobacco();
	afx_msg void OnVegetable();
	afx_msg void OnWizardSelectCrop();
	afx_msg void OnResultReview();
	afx_msg void OnResultRecord();
	afx_msg void OnUncertainty();
	afx_msg void OnWizardMonteCarlo();
	afx_msg void OnMsf();
	afx_msg void OnRegionInput();
	afx_msg void OnRegionRun();
	afx_msg void OnESreview();
	afx_msg void OnRegionMap();
	afx_msg void OnCreateCrop();
	afx_msg void OnExtractData();
	afx_msg void OnSiteResult();
	afx_msg void OnGlobeMap();
	afx_msg void OnGlobeData();
	afx_msg void Onconvert();
	afx_msg void OnMapView();
	afx_msg void OnBatch();
	afx_msg void OnSiteParameter();
	afx_msg void OnMapLayer();
	afx_msg void OnConvertData();
	afx_msg void OnConvert1();
	afx_msg void OnConvert2();
	afx_msg void OnConvert3();
	afx_msg void OnConvert4();
	afx_msg void OnConvert5();
	afx_msg void OnConvert6();
	afx_msg void OnSoilDensity();
	afx_msg void OnGlobe5();
	afx_msg void OnConvert7();
	afx_msg void On5min30min();
	afx_msg void On5minSOIL30minSOIL();
	afx_msg void OnUSAdata();
	afx_msg void OnDndc1();
	afx_msg void OnDndcMap();
	afx_msg void OnDay1snow();
	afx_msg void OnCombineFiles();
	afx_msg void OnExtractNation();
	afx_msg void OnRegionData();
	afx_msg void OnRunMonteCarlo();
	afx_msg void OnConvertClimateData();
	afx_msg void OnSnowPack();
	afx_msg void OnSiteModeTest();
	afx_msg void OnGlobeDataProcess();
	afx_msg void OnYieldPredict();
	afx_msg void OnYieldShow();
	afx_msg void OnLiaoning();
	afx_msg void OnYieldReSet();
	afx_msg void OnSaveSoilFile();
	afx_msg void OnLinux();
	afx_msg void OnGateTest();
	afx_msg void OnFarmCompost();
	afx_msg void OnRunFarmComponent();
	afx_msg void OnFarmLagoon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in graphexView.cpp
inline CGraphexDoc* CGraphexView::GetDocument()
   { return (CGraphexDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHEXVIEW_H__B2C5B6CC_351A_11D3_984A_00C04FC9DE52__INCLUDED_)

