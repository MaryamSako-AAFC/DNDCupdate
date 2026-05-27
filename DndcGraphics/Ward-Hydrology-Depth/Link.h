// graphexDoc.h : interface of the CGraphexDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHEXDOC_H__B2C5B6CA_351A_11D3_984A_00C04FC9DE52__INCLUDED_)
#define AFX_GRAPHEXDOC_H__B2C5B6CA_351A_11D3_984A_00C04FC9DE52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include "QINGlobal.h"
//#include "NewDBase.h"

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
	//paleoclimate paleo;
	//ForestIndexDefine forest;

	int		MapBoxFlag;
	int		Fontype,Fontsize;
	float	Ftscale;
	float	ydis;
	int		Jx;
	int		figWidth;//the width of main curve area
	CRect	SelfClient;
	//ResultData Vdata;

	//AreaArray *Cnty;

	int  Lindex;
	int	 AllOrLast;//0:all,1:last

	void Prepare();
	int  ClearAct();
	
/*	void AddLine(int StartX,int StartY,COLORREF col);//point
	void AddLine(int,int,int,int);
	void AddLine(int,int,int,int,COLORREF);//add line with color
	void AddLine(int,int,int,int,char*,COLORREF);//add rect with color (range,how,color)
	void AddLine(RECT,char*,COLORREF);//add rect with color (range,how,color)
	void AddLine(POINT *lpt,int nCount, char *how, COLORREF LineC, COLORREF FillC);//polygon
	void AddLine(int,int,char*,int,int,COLORREF);//add text 1
	void AddLine(RECT ,char *,UINT nflag,int fsize,int ftype,COLORREF color,COLORREF Bcolor);// add test 2
	void AddLine(RECT ,CString,UINT nflag,int fsize,int ftype,COLORREF color,COLORREF Bcolor);// add test 3
*/
	//void DrawAction(int);
	//void DrawAction(CMyLine *id);
	//void ShowLine(void);

	//CMyLine* GetLine(int index);
	//int GetTotalLine();
	virtual void DeleteContents();

// Draw function of DNDC
/*	void fView_frame();
	void fView_PaleoIndex_frame();
	int  fView_frame_forest();
	void FView_Legend(int id,char *word[],int n,COLORREF Color[],int column);
	char *month(int i);
	void fView_soil_climate (dn_dc*, float, float, float, float);
	void fView_crop (dn_dc* dndc, int cwc);
	void fView_soil_chemistry (dn_dc*);
	void fView_gas (dn_dc*);
	void fView_PaleoIndex(dn_dc*);
	int  SetDrawParameter();
	void fView_ForestIndex(dn_dc* dndc,float F_Evp,float dtrans);
	void fView_forest_frame();
	int  ShowForestDataAsText(float val,int block,int id);



	//float CheckValueRange(float z6,int high,int low);
	void Note_site (dn_dc*, int);
	void Note_site (dn_dc*, int,char*);
	void fView_profile (dn_dc*);//, float*);
	void Note_crop ( dn_dc*, int, char*);

	void Map_text (int, int);
	void Map_frame (int country);
	void fill_county (int, int, int, float, float, float);
	POINT GetNewXY(POINT pot,RECT ViewW, RECT Seen);
	void Show_ColorBar(char *style, char *title,float ValueR[]);
	void Show_MultiColorBar(CString style[], CString title[], 
		CString scale[], float ValueR[][6], int used[]);
	int  GetNumberOfLabel(int *NColor,int IVal);
	void DrawColorBar(char *style, char *title, float *ValueR);
	int DrawBarLabel(float ValueR[][6],int m, CRect Bar,int IVal,
		CString *style,int NColor);
	int FromValueTo256(int ifLog,float scale,float dat,int m);

	int ShowCurve(CurvePicture *Cp,int time,float dat,float dis);

	void GetColorBarDefine(COLORREF *ColorArray,int NColor,CString style);
	int  SetFontSize(int SizeCode);
	int  GetMapParameter(int country,int state,MapProject *MPj);
	int  CloseStateAndCountyDB();

	int  GetColorIndex(char *style, float ValueR[],float data);
	void Show_text (RECT Range, char *p,COLORREF Tcolor,COLORREF Bcolor,int fsize);
//	void fView_county (int);
//	void Show_Note (CString *txt, RECT rBox, UINT nflag, int fsize, int ftype);

	int  ShowCoeffMAP();
	int  DNDCMAP();
	int  mapping(int *Sort, int *Type, int *Index, //int HL,int state, 
		   MapProject MPj, int Country, int scena,float VR[][6]);
	int  StatisticMap();
	int  CalculateAGroup(int id,float *TotalSum, float *TotalArea);
	int  CalculateTwoGroup();
	int  SetResultName(int id);

	long ReadAreaEdge(FILE *fp, int country, POINT *intpoly,int *sss);
	long ReadAreaEdge(FILE *fp, int country,MapProject MPj,RECT Seen,POINT *intpoly,int *sss);
	//int  ReadACountyEdgeFromNewDB(char CID, POINT *intpoly,int *sss,int *TPN);

	int  ReportSum(float SUM, int Type, int Sort,float *gas,int HL);
	//int  DrawLegend(int *Sort,int *Type,float *VR,int HL);
	int  DrawLegend(int *Sort,int *Type);
	int  GetDefaultRange(int Sort,int Type,int *mode,
		CString *title,CString *scale,float VRange[]);
*/

	int  PrepareMapData(char *base, char *ofile, int TYPE, 
								int Sort, float *SUM);
	int  PrepareMapFlux(int Country, int Type, int Sort, int state,
		float *gas,char *NAME);
	//	void fView_inter (dn_dc*);
/*
	void ShowDOC(CString txt);
	CString GetMapValue(CString m_DoWhat,COLORREF PColor, CPoint point,int State);
	POINT GetPointXY(CPoint point);
	int  SetViewWindow(CRect *crect, CClientDC *dc);

	long GetPolygenRange(int state,int county,POINT *intpoly,int sss,long CtyID);
	CRect GetPolygenRange(POINT *intp,int sss);
	long InCounty(POINT Pnt,int *Pro,int *Cty,char *cname);
	int  ShowACounty(int Pro,long Cty,COLORREF LColor,COLORREF FColor);
	int  ShowACounty(long Cty,COLORREF LColor,COLORREF FColor);
	CRect DisplayACounty(int j,COLORREF LColor,COLORREF FColor,
			RegionDBaseName *RDB,CString SCmode);
	int  DisplayACounty(long code,int SelectedState, COLORREF LColor,COLORREF FColor,
			RegionDBaseName *RDB,CString SCmode);
	int  CheckPolygon(int state,long CtyID,CPoint point,CString *SCmode);
	int  ReadCoeffData(CString CoePath);
	int  SaveCoeffData(CString CoePath);


	int  CheckPolygon();
	int  TestMap();
	POINT *ReadAreaEdgeFromNewDB(FILE *fp, int AreaID,POINT *intpoly,int *sss,int *TPN);
	int  ShowNewMap(char *map,COLORREF tcol);
	POINT *readlinedata(POINT intpoly[],int *PNum,FILE *fp,float *head);
	int  readhead(float *dt,FILE *fp);
	int  GetNewPostion(POINT *intp);
	int  GetCountyRange(CRect rec,int State, char *NID);
	int  FindXYRange(POINT *intpoly,int i,int TPN);
	int  ChangeXY(POINT *intpoly,int TPN,CString XYType);
	int  AlbertsEqualAreaConicProjection(POINT *intp);
	int  SetMapRange(int state,RegionDBaseName *RDB);//NameIndexBaseclass *NIndex);
	int  initialRegionDB(int country);
	BOOL IsInSelectedState(char *p,int state);
	//BOOL IsStateSelected(char *p, int sel);
	char *ItsCountyName(char *p,RegionDBaseName *Db);
	char *ItsCountyName(long p,RegionDBaseName *Db);
	int  ShowState(int state,COLORREF *soc_color,long *mapcode);
	int  findcounty(char *PID,long *mapcode);
	int  CheckChinaCounty(char *map,COLORREF tcol);
	int  ShowPolygon(int SelectedState,COLORREF *soc_color,long *mapcode,RegionDBaseName *RDB,CString SCmode);
	//long *GetMapCode(int state,int *soc_color,long *mapcode,RegionDBaseName *RDB);
	long *GetMapCode(int state,COLORREF *soc_color,long *mapcode,RegionDBaseName *RDB);
	int  GetShowColor(float ri, float gi, float bi,COLORREF *LColor,
				 COLORREF *FColor);
	int GetValueRangeOfFlux(int BS,int ES,int Sort,int Index,int Type,int m);
	

	int  DrawLatLon();
	int  set_map_parameter(int country,int state);
	int  getE_A(float nname, float *aa, float *bb, float *aa1, float *ee);
	int  get_Parameter();
	int  get_radius(float *rr, float ffs);
	int  create_Position_XY();
	int  map_angle();
	int  draw_jwd_1(CString IfShow);
	int  TranslateXY(float *x,float *y,CRect rct);
	int  SetViewMapRatio(CRect rct);
	int  LatLon_to_XY(float wd, float jd, float *x, float *y);
	int  XY_to_LatLon(float x, float y, float *wd, float *jd);
*/
	void IfStop();
	int  Pause();
	//int  DoOneTime();


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

