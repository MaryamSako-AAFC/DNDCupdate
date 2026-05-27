// SelectRegionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "RunPaths.h"
#include "SelectRegionDlg.h"
#include "modataconnection.h"
#include "momaplayer.h"
#include "molayers.h"
#include "MoGeoDataset.h"
#include "mosymbol.h"
#include "morectangle.h"
#include "morecordset.h"
#include "mofield.h"
#include "mofields.h"
#include "mopoint.h"
#include "motrackinglayer.h"
#include "movaluemaprenderer.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include "SitePara.h"
#include "moclassbreaksrenderer.h"
#include "mostatistics.h"

#include "SitePage3.h"
#include "ListFile.h"
#include "dndc_tool.h"

extern Site_BaseInformation	IData;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//void Glean_StringM(char *String, int Num1, int Num2, char *Sub_Str);

float SOCA[6]={0.0,0.2,0.2,0.08,0.05,0.2};
float SOCB[6]={10.0,2.0,2.0,1.4,4.0,2.0};

char state_id[200], WordRoot[200];
int RedoFlag;

CString CROPSYSTEM[250] = {"Fallow", "Corn", "W_wheat", "Soybean", "L_hay", "NL_hay", 
					"S_wheat", "Sugarc", "Barley", "Oats", "Alfalfa", 
					"Grass", "Pasture", "Sorghum", "Cotton", "Rye", 
					"Veget", "NewCrop", "Potato", "Beet", "Rice", 
					"Banana", "Celery", "Peanut", "DryRice", "Rapes", 
					"Tobacco", "Millet", "Sunfl", "Beans", "DW_rice", 
					"Onion", "NewCrop", "Strawb", "Lettuce", "Artich", 
					"Nersery", "Brussel", "Berries", "TruCrop", "Fruits", 
					"Citrus", "Grapes", "Sil_corn", "Hops", "Tomato", 
					"NewCrop", "CoverCr", "Safflo", "Flax", " ", //50
					"wwt/cor", "rap/ric", "wwt/rap", "ric/ric", "wwt/ric", 
					"wwt/veg", "rap/cor", "rap/veg", "veg/cor", "veg/ric",//60 
					"cor/soy", "wwt/soy", "oat/ric", "pot/soy", "soy/hay", 
					"wwt/pot", "wwt/cot", "pot/cor", "rap/soy", "rap/cot",//70 
					"oat/soy", "ric/soy", "pot/pot", "cor/cor", "ve/ve/v", 
					"r/r/lha", "r/r/rap", "po/v/v", "r/r/ww", "r/r/ve",//80
					"", " ", " ", " ", " ",
					"", " ", " ", " ", " ",//90
					"", " ", " ", " ", " ",
					"", " ", " ", " ", " ", //100
					"", " ", " ", " ", " ",
					"", " ", " ", " ", " ",//110					
					"", "", "", "", "", 
					"", "", "", "", "",//120
					"", "", "", "", "",
					"", "", "", "", "hay/hay",//130
					"g/g", "g/veg", "hay/g", "hay/veg", "veg/veg", 
					"g/g/g", "g/g/ve", "g/v/g", "", "",//140
					"", "", "", "", "",
					"", "", "", "", "Dairy",//150
					"", "", "", "", "",
					"", "", "", "", "",//160
					"", "", "", "", "",
					"", "", "", "", "",//170
					"", "", "", "", "",
					"", "", "", "", "",//180
					"", "", "", "", "",
					"", "", "", "", "",//190
					"", "", "", "", "",
					"", "", "", "", "",//200	
					"Rf_Ir","Rf_Rf","Rf_Wht","Rf","IrIrIr",
					"Ir_Ir","IrIrVeg","IrIrRap","IrIrSoy","IrIrPot",//210
					"IrIrSor","IrIrVeg","IrIrWht","IrIrCot","IrRaCot",
					"RfRaCot","IrCoVeg","IrVeCot","RfVeCot","IrVePot",//220
					"IrSoSoy","RfWhCot","IrWhPot","RfVeWht","Ir_Cot",
					"Rf_Cot","Ir_Bar","Rf_Bar","Rf_Bar","Rf_Veg",//230
					"Ir_Mil","Rf_Mil","Ir_Rap","Rf_Rap","Ir_Pot",
					"Rf_Pot", "Ir_Soy","Rf_Soy","Ir_Sor", "Ir_Sug",//240
					"Rf_Sug","Ir_Veg","Rf_Veg","Ir_Wht","Ir",
					"Upland","DeepWat","Ir_Qat", "IrIrLha"};//249


CString ConvertClimateFile(char *temp, char *ClimateFilename);

/////////////////////////////////////////////////////////////////////////////
// CSelectRegionDlg dialog
BEGIN_MESSAGE_MAP(CLabelStatic, CStatic)
	//{{AFX_MSG_MAP(CLabelStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CLabelStatic::SetText(CString text)
{
	m_text = "  " + text + "  ";
	Invalidate();
}

CRect CLabelStatic::GetRect()
{
	CClientDC dc(this); 

	CRect rect;
	rect.SetRectEmpty();
	dc.DrawText(m_text, &rect, DT_LEFT|DT_VCENTER|DT_CALCRECT);

	return rect;
}

void CLabelStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (m_text != "")
	{
		CRect rect;
		rect.SetRectEmpty();
		dc.DrawText(m_text, &rect, DT_LEFT|DT_VCENTER|DT_CALCRECT);

		dc.FillRect(&rect, &CBrush(RGB(155,255,255)));
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(m_text, &rect, DT_LEFT|DT_VCENTER);
	}
}


CSelectRegionDlg::CSelectRegionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectRegionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectRegionDlg)
	m_SiteName = _T("");
	//}}AFX_DATA_INIT

	m_mouseAction = 0;
	m_movelabel = FALSE;

	WizardCountyID = "";
}

CSelectRegionDlg::~CSelectRegionDlg()
{
	for (int i = m_layers.GetSize()-1; i >= 0; i--)
	{
		delete m_layers.GetAt(i);
		m_layers.RemoveAt(i);
	}
}

void CSelectRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectRegionDlg)
	DDX_Control(pDX, IDC_CROPS, m_WizardCrops);
	DDX_Control(pDX, IDC_LOCATION, m_locationLabel);
	DDX_Control(pDX, IDC_MAP, m_map);
	DDX_Text(pDX, IDC_SCname, m_SiteName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectRegionDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectRegionDlg)
	ON_BN_CLICKED(IDC_ZOOMIN, OnZoomin)
	ON_BN_CLICKED(IDC_ZOOMOUT, OnZoomout)
	ON_BN_CLICKED(IDC_PAN, OnPan)
	ON_BN_CLICKED(IDC_FULLMAP, OnFullmap)
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CROPS, OnSelchangeWizardCrops)
	ON_BN_CLICKED(IDC_LandCover, OnLandCover)
	ON_BN_CLICKED(IDC_SelectFarm, OnSelectFarm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectRegionDlg message handlers

BOOL CSelectRegionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CMoDataConnection dc;
	dc.CreateDispatch("MapObjects2.DataConnection");
	dc.SetDatabase(m_mapPath);// info of path of map data file
	if (dc.Connect())
	{
		int layerss = m_layers.GetSize();

		for (int i = 0; i < m_layers.GetSize(); i ++)
		{
			LAYERINFO* layerinfo = m_layers.GetAt(i);
			CMoMapLayer layer;
			layer.CreateDispatch("MapObjects2.MapLayer");
			layer.SetGeoDataset(dc.FindGeoDataset(layerinfo->layerName));// root name of map data file
			CMoSymbol symbol = layer.GetSymbol();
			symbol.SetSize(layerinfo->lineWidth);// width of line
			symbol.SetOutlineColor(layerinfo->lineColor);//line color
			if (layerinfo->fill)//draw solid polygon
			{
				symbol.SetStyle(0);	// solid fill
				symbol.SetColor(layerinfo->fillColor);
			}
			else
			{
				symbol.SetStyle(1); // transparent fill
			}
			m_map.GetLayers().Add(layer);
			ValueMapLayer();
		}
#ifdef USA
		for (i = 0; i < m_layers.GetSize(); i ++)
		{
			LAYERINFO* layerinfo = m_layers.GetAt(i);
			CMoMapLayer layer;
			layer.CreateDispatch("MapObjects2.MapLayer");
			layer.SetGeoDataset(dc.FindGeoDataset("STATES"));// root name of map data file
			CMoSymbol symbol = layer.GetSymbol();
			symbol.SetSize(layerinfo->lineWidth);// width of line
			symbol.SetOutlineColor(layerinfo->lineColor);//line color
			if (layerinfo->fill)//draw solid polygon
			{
				symbol.SetStyle(1);	// solid fill
				symbol.SetColor(layerinfo->fillColor);
			}
			else
			{
				symbol.SetStyle(1); // transparent fill
			}
			m_map.GetLayers().Add(layer);
			ValueMapLayer();
		}
#endif
	}
	else
	{
		AfxMessageBox("Can not connect to map path.");
		return FALSE;
	}
  
//	return OnInitDialog1();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectRegionDlg::SetLayerSelected(CString layer, CString labelfield, CString idfield, CString latitude, CString longitude) 
{	
	m_layerSelect = layer; 
	m_labelField = labelfield;
	m_idField = idfield;
	m_STATE = latitude;
	m_longitude = longitude;
}

void CSelectRegionDlg::AddLayer(CString name, int lineWidth, COLORREF lineColor,
								bool fill, COLORREF fillcolor)
{
	LAYERINFO* layer = new LAYERINFO;
	layer->layerName = name;
	layer->lineWidth = lineWidth;
	layer->lineColor = lineColor;
	layer->fill = fill;
	layer->fillColor = fillcolor;

	m_layers.Add(layer);
}

BEGIN_EVENTSINK_MAP(CSelectRegionDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSelectRegionDlg)
	ON_EVENT(CSelectRegionDlg, IDC_MAP, -606 /* MouseMove */, OnMouseMoveMap, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CSelectRegionDlg, IDC_MAP, -607 /* MouseUp */, OnMouseUpMap, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CSelectRegionDlg, IDC_MAP, -605 /* MouseDown */, OnMouseDownMap, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CSelectRegionDlg, IDC_MAP, 4 /* AfterTrackingLayerDraw */, OnAfterTrackingLayerDrawMap, VTS_I4)
	ON_EVENT(CSelectRegionDlg, IDC_MAP, 3 /* AfterLayerDraw */, OnAfterLayerDrawMap, VTS_I2 VTS_BOOL VTS_I4)
	ON_EVENT(CSelectRegionDlg, IDC_MAP, 5 /* BeforeTrackingLayerDraw */, OnBeforeTrackingLayerDrawMap, VTS_I4)
	ON_EVENT(CSelectRegionDlg, IDC_MAP, 2 /* BeforeLayerDraw */, OnBeforeLayerDrawMap, VTS_I2 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSelectRegionDlg::OnMouseMoveMap(short Button, short Shift, long X, long Y) 
{
/*	if (m_mouseAction == 0)
	{
		CMoMapLayer layer;
		CMoPoint p;
		CMoRecordset recs;
		COleVariant layername(m_layerSelect);

		layer = m_map.GetLayers().Item(layername);
		p = m_map.ToMapPoint(X, Y);
  
		recs = layer.SearchShape(p, 12, ""); // 12: pointinpolygon
  
		if (! recs.GetEof())
		{
			dndc74 rr;
			//CString LandType;
			//int CropNN=atoi(m_labelField);
			//LandType.Format("%s", rr.CropSystem[CropNN]);
			COleVariant fieldname(m_labelField);
			CMoField fld = recs.GetFields().Item(fieldname);

			//COleVariant k_lat(m_STATE);
			//CMoField kk_lat = recs.GetFields().Item(k_lat);

			if (m_movelabel)
			{
				CRect rc = m_locationLabel.GetRect();
				CPoint pt(X, Y);
				m_map.ClientToScreen(&pt);
				ScreenToClient(&pt);
				m_locationLabel.MoveWindow(pt.x+2, pt.y-rc.Height()-2, rc.Width(), rc.Height());
				m_locationLabel.SetText(fld.GetValueAsString());
				//m_locationLabel.SetText(kk_lat.GetValueAsString());
			}
			else
			{
				m_locationLabel.SetWindowText(fld.GetValueAsString());
			}
		}
		else
		{
			if (m_movelabel)
			{
				m_locationLabel.MoveWindow(0,0,0,0);
				m_locationLabel.SetText("");
			}
			else
			{
				m_locationLabel.SetWindowText("");
			}
		}
	}
*/
}

void CSelectRegionDlg::DrawSelection()
{
	CMoSymbol sym;
	sym.CreateDispatch("MapObjects2.Symbol");
    sym.SetColor(RGB(255,255,0)); //determine color for selected polygon (m_SelectionRecs)
    m_map.DrawShape(m_selectionRecs, sym);// fill polygon (m_selectionRecs) with color (sym)
}

void CSelectRegionDlg::OnMouseDownMap(short Button, short Shift, long X, long Y) 
{
	if (m_mouseAction == 1)
		m_map.SetExtent(m_map.TrackRectangle());
	else if (m_mouseAction == 2)
		m_map.Pan();
	//m_mouseAction = 0;
}

void CSelectRegionDlg::OnMouseUpMap(short Button, short Shift, long X, long Y) 
{
	
	CString note;

	RedoFlag = 0;

	if (m_mouseAction == 0)
	{
		CMoMapLayer layer;
		CMoPoint p;
		COleVariant layername(m_layerSelect);

		layer = m_map.GetLayers().Item(layername);
		p = m_map.ToMapPoint(X, Y);
  
		m_selectionRecs = layer.SearchShape(p, 12, ""); // 12: pointinpolygon
		m_map.GetTrackingLayer().Refresh(TRUE, COleVariant());
		if (! m_selectionRecs.GetEof())
		{
			CMoField fldLabel = m_selectionRecs.GetFields().Item(COleVariant(m_labelField));//COUNTRY_NA
			CMoField fldId = m_selectionRecs.GetFields().Item(COleVariant(m_idField));//DNDC_CELL
			m_selectedLabel = fldLabel.GetValueAsString();
			m_selectedId = fldId.GetValueAsString();

			if(strcmp(m_layerSelect,"China")==0)
			{
				CString CCCode;
				FILE *cccode;
				CCCode.Format("%s\\Database\\China\\lib_map\\ChinaCountyCode.txt", ROOTDIR);
				cccode = fopen(CCCode, "r");
				if(cccode==NULL)
				{
					CString note;
					note.Format("Cannot open %s", CCCode);
					AfxMessageBox(note);
					exit(0);
				}

				char www[80], MapCode[50], DataCode[50];
				fgets(www, 100, cccode);
				for(;;)
				{
					fscanf(cccode, "%s %s", MapCode, DataCode);
					fgets(www, 100, cccode);
					if(strcmp(MapCode, m_selectedId)==0) 
					{
						m_selectedId.Format("%s", DataCode);
						break;
					}
				}
			}

			if(strcmp(m_layerSelect,"USA")==0)
			{
				/*CString CCCode;
				FILE *cccode;
				CCCode.Format("%s\\Database\\USA\\lib_map\\ChinaCountyCode.txt");
				cccode = fopen(CCCode, "r");
				if(cccode==NULL)
				{
					CString note;
					note.Format("Cannot open %s", CCCode);
					AfxMessageBox(note);
					exit(0);
				}

				char www[80], MapCode[50], DataCode[50];
				fgets(www, 100, cccode);
				for(;;)
				{
					fscanf(cccode, "%s %s", MapCode, DataCode);
					fgets(www, 100, cccode);
					if(strcmp(MapCode, m_selectedId)==0) 
					{
						m_selectedId.Format("%s", DataCode);
						break;
					}
				}*/
			}

			WizardCountyID = m_selectedId;

			CString note;
			note.Format("%s (%s)", WizardCountyID, m_selectedLabel);

			AfxMessageBox(note);

			m_SiteName.Format(note); 

			UpdateData(FALSE);
			
			County_data(WizardCountyID, 0);
			
			if(RedoFlag==1) return;

			//OnInitDialog1();

		}
		else
		{
			m_selectedLabel = "";
			m_selectedId = "";
		}
	}		

/*
		CMoMapLayer layer;
		CMoPoint p;
		COleVariant layername(m_layerSelect);

		layer = m_map.GetLayers().Item(layername);
		p = m_map.ToMapPoint(X, Y);
  
		m_selectionRecs = layer.SearchShape(p, 12, ""); // 12: pointinpolygon
		m_map.GetTrackingLayer().Refresh(TRUE, COleVariant());
		if (! m_selectionRecs.GetEof())
		{
			CMoField fldLabel = m_selectionRecs.GetFields().Item(COleVariant(m_labelField));
			CMoField fldId = m_selectionRecs.GetFields().Item(COleVariant(m_idField));
			m_selectedLabel = fldLabel.GetValueAsString();
			m_selectedId = fldId.GetValueAsString();

			//WizardCountyID = atoi(m_selectedId);
			CString WCID;
			FILE* wcid;
			WCID.Format("%s\\Database\\%s\\GIS\\Link_geo_ARRGCD.txt", m_layerSelect);
			wcid=fopen(WCID, "r");
			if(wcid==NULL)
			{
				CString note;
				note.Format("Cannot open file %s", WCID);
				AfxMessageBox(note);
				exit(0);
			}
			fgets(WW, 300, wcid);
NewRead:
			if(fscanf(wcid, "%s", GeoID)!=1) goto NoID;
			for(;;)
			{
				fscanf(wcid, "%s", ArrID);
				if(strcmp(ArrID,"XXX")!=0)
				{
					if(strcmp(ArrID,m_selectedId)!=0) {}
					else
					{
						fclose(wcid);
						WizardCountyID = GeoID;
						goto IDfound;
					}
				}
				else
				{
					goto NewRead;
				}

			}

NoID:		
			fclose(wcid);
			note.Format("Cannot find ARRGCD ID %s in file %s", m_selectedId, WCID);
			AfxMessageBox(note);
			exit(0);			
			
IDfound:		
			County_data(WizardCountyID);
			OnInitDialog1();

		}
		else
		{
			m_selectedLabel = "";
			m_selectedId = "";
		}
	}
*/
}

void CSelectRegionDlg::OnZoomin() 
{
	m_mouseAction = 1;
}

void CSelectRegionDlg::OnZoomout() 
{
	CMoRectangle zoomOutRect;
	zoomOutRect = m_map.GetExtent();
    zoomOutRect.ScaleRectangle(1.5);
    m_map.SetExtent(zoomOutRect);
}

void CSelectRegionDlg::OnPan() 
{
	m_mouseAction = 2;
}

void CSelectRegionDlg::OnFullmap() 
{
	m_map.SetExtent(m_map.GetFullExtent());
}


BOOL CSelectRegionDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (pWnd->GetSafeHwnd() == m_map.GetSafeHwnd())
	{
		switch (m_mouseAction)
		{
		case 0://select
			::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
			break;
		case 1://zoom in
			::SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));//IDC_ZOOMIN));
			break;
		case 2://pan
			::SetCursor(AfxGetApp()->LoadCursor(IDC_PAN));
			break;
		default:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			break;
		}
		return TRUE;
	}
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


void CSelectRegionDlg::OnAfterTrackingLayerDrawMap(long hDC) 
{
	DrawSelection();	
}

void CSelectRegionDlg::SetValueMapLayer(CString layer, CString field)
{
	m_valuemapLayer = layer;
	m_valuemapField = field;
}

void CSelectRegionDlg::ValueMapLayer()
{
	if (m_valuemapLayer == "")
		return;

	CStringArray strings;
	CMoMapLayer ly;
	CMoRecordset recs;
	ly = m_map.GetLayers().Item(COleVariant(m_valuemapLayer));
	recs = ly.GetRecords();
	while (! recs.GetEof())
	{
		strings.Add(recs.GetFields().Item(COleVariant(m_valuemapField)).GetValueAsString());
		recs.MoveNext();
	}
	CMoValueMapRenderer r;
	r.CreateDispatch("MapObjects2.ValueMapRenderer");
	r.SetField(m_valuemapField);
  
	r.SetValueCount(strings.GetSize());
	for (int i = 0; i < strings.GetSize(); i ++)
		r.SetValue(i, strings.GetAt(i));
  
	ly.SetRenderer(r);
}

void CSelectRegionDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

///////////////////////////////////////////////////////////////////////////

void CSelectRegionDlg::County_data(CString WizardCountyID, int domain)
{
	char MM[500], stateID[300], rID[50], rCountryName[100];
	CString county_ID4;	
	int i, crop_number, crop_ID[90];

	float rLon, rLat;
	int rRow, rCol, rCountry, rRegion;

	CString REGION[7]={"", "Africa", "Asia", "Europe", "NorthAmerica", "Oceania", "SouthAmerica"};

	sprintf(stateID, "%s", WizardCountyID);

	CString WS;
	FILE *ws;
	WS.Format("%s\\Inter\\MapSelect.txt", OUTPUT);
	ws=fopen(WS, "r");
	if(ws==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", WS);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(ws, "%s  %s", m_Watershed, m_yr);
	fclose(ws);

	WS.Format("%s\\Database\\Globe\\RegionListFile.txt", ROOTDIR);
	ws=fopen(WS, "r");
	if(ws==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", WS);
		AfxMessageBox(note);
		exit(0);
	}
	for(;;)
	{
		fscanf(ws, "%s %f %f %d %d %d %d %s", rID, &rLon, &rLat, &rRow, &rCol, &rRegion, &rCountry, rCountryName);
		if(strcmp(rID,WizardCountyID)==0) 
			break; 
	}
	fclose(ws);

	if(domain==0) sprintf(m_Watershed, "%s\\Database\\Globe\\%s\\", ROOTDIR, REGION[rRegion]); 

	/*if(strcmp(m_Watershed,"India")==0)
	{
		char ww[200], code2000[200];
		int code1998;
//ReSearch:
		WS.Format("%s\\Database\\%s\\GIS\\%s_1.txt", m_Watershed, m_Watershed);
		ws=fopen(WS, "r");
		if(ws==NULL)
		{
			CString note;
			note.Format("Cannot open file %s", WS);
			AfxMessageBox(note);
			exit(0);
		}
		fgets(ww, 200, ws);
		//fgets(ww, 200, ws);
		for(;;)
		{
			if(fscanf(ws, "%s %d", code2000, &code1998)!=2)
			{
				static int ccc=0;

				if(ccc==2) return;

				CString note;
				note.Format("Cannot find this polygon (%s) in file %s", stateID, WS);
				AfxMessageBox(note);
				fclose(ws);

				int NewID=atoi(stateID);
				NewID++;
				sprintf(stateID, "%d", NewID);

				ccc++;
				goto ReSearch;
				//exit(0);
				//return;
			}
			else
			{
				//if(code2000==stateID)
				if(strcmp(code2000, stateID)==0)
				{
					WizardCountyID.Format("%d", code1998);
					break;
				}
			}

		}
		fclose(ws);
		
	}*/
	/*else if(strcmp(m_Watershed,"China")==0)
	{
		char ww[200], code2000[200];
		int code1998;
ReSearch:		
		//WS.Format("%s\\Database\\China\\lib_map\\1990_2000_CountyCode_Comparison.txt");
		WS.Format("%s\\Database\\%s\\GIS\\", m_Watershed);
		ws=fopen(WS, "r");
		if(ws==NULL)
		{
			CString note;
			note.Format("Cannot open file %s", WS);
			AfxMessageBox(note);
			exit(0);
		}
		fgets(ww, 200, ws);
		fgets(ww, 200, ws);
		for(;;)
		{
			if(fscanf(ws, "%s %d", code2000, &code1998)!=2)
			{
				static int ccc=0;

				if(ccc==2) return;

				CString note;
				note.Format("Cannot find this polygon (%s) in file %s", stateID, WS);
				AfxMessageBox(note);
				fclose(ws);

				int NewID=atoi(stateID);
				NewID++;
				sprintf(stateID, "%d", NewID);

				ccc++;
				goto ReSearch;
				//exit(0);
				//return;
			}
			else
			{
				//if(code2000==stateID)
				if(strcmp(code2000, stateID)==0)
				{
					WizardCountyID.Format("%d", code1998);
					break;
				}
			}

		}
		fclose(ws);
		
	}*/

	sprintf(m_FileName, "%s", m_Watershed);
	
	CString RF;
	FILE *ref;
	
	sprintf(WordRoot, "%s", WizardCountyID);
	Glean_String(WordRoot, 0, 1, state_id); 

	CString note;
		
	if(domain==0)
	{


	}
	else
	{
		#ifdef USA
			RF.Format("%s\\Database\\%s\\GIS\\%s4_%s", ROOTDIR, m_FileName, m_FileName, state_id);
			note.Format("No crop data available for this area yet. Please make a new selection");
		#else
			RF.Format("%s\\Database\\%s\\GIS\\%s_4.txt", ROOTDIR, m_FileName, m_FileName);
			note.Format("Can not open file %s", RF);
		#endif

	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		
		AfxMessageBox(note);
		RedoFlag = 1;
		return;
	}

	fgets(MM, 500, ref);
	fgets(MM, 500, ref);

	CString CropCode;
	FILE *CC;

	CropCode.Format("%s\\Inter\\RegionCropCode", OUTPUT);
	CC = fopen(CropCode, "w");
	if (CC==NULL)
	{
		char err[120];
		sprintf(err, "Can not create file %s", CropCode);
		AfxMessageBox(err);
		return;
	}

	fscanf(ref, "%d", &crop_number);
	fprintf(CC, "%d\n", crop_number);

	for(i=1; i<=crop_number; i++)
	{
		fscanf(ref, "%d", &crop_ID[i]);
		fprintf(CC, "%d\n", crop_ID[i]);
		WWW[i]=crop_ID[i];
	}

	fclose(CC);

/*	for(i=1; i<= 10000; i++)//China_4.txt
	{
		float TotalHa=0.0;
		if(fscanf(ref, "%s", county_ID4)!=1)
		{
			CString note;
			//note.Format("There is no polygon %s in input data file %s", WizardCountyID, RF);
			note.Format("Please select a cropland");
			AfxMessageBox(note);
			return;//exit(0);
		}

		if(strcmp(county_ID4,WizardCountyID)==0)
		{
			for(landuse=1; landuse<=crop_number; landuse++)
			{
				fscanf(ref, "%f", &crop_ha[landuse]);

				TotalHa += crop_ha[landuse];
			}

			if(TotalHa==0.0) 
			{
				CString note;
				note.Format("Note: There is no crop planted in the selected polygon");
				AfxMessageBox(note);
				fclose(ref);
				//return;
				break;
			}
			else 
				break;
		}
		else
		{
			fgets(MM, 300, ref);
		}
			
	}*/
	fclose(ref);

	char Sname[200], Cname[200];
	CString CID;
	float logi, lati;

#ifdef USA
	RF.Format("%s\\Database\\%s\\GIS\\%s1_%s", ROOTDIR, m_FileName, m_FileName, state_id);
#else
	RF.Format("%s\\Database\\%s\\GIS\\%s_1.txt", ROOTDIR, m_FileName, m_FileName);
#endif

	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}
	fgets(MM, 300, ref);
	for(;;)
	{
		fscanf(ref, "%s %s %s %f %f", CID, Sname, Cname, &logi, &lati);
		if(CID==WizardCountyID) 
			break;

	}

	CString IDfile;
	FILE *fid;
	
	IDfile.Format("%s\\Inter\\WizardSite.txt", OUTPUT);
		fid = fopen(IDfile, "w");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(fid, "%s  %s\n", stateID, WizardCountyID);
		fprintf(fid, "%s  %s\n", Sname, Cname);
		for(i=1; i<=crop_number; i++)
			fprintf(fid, "%d  %f\n", crop_ID[i], 1.0);//crop_ha[i]);//China_4.txt

		fclose(fid);
	}

}

BOOL CSelectRegionDlg::OnInitDialog1() 
{
	// TODO: Add extra initialization here
	int i, crop_ID[90];

	CString IDfile;
	FILE *fid;
	
	IDfile.Format("%s\\Inter\\WizardSite.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
		CString mess;
		mess.Format("Can not open %s.", IDfile);
		AfxMessageBox(mess);
		exit(0);
	}
	fscanf(fid, "%s  %s", stateID, WizardCountyID);
	fscanf(fid, "%s  %s", Sname, Cname);
	int ii=0;
	for(;;)
	{
		ii++;
		if(fscanf(fid, "%d  %f", &crop_ID[ii], &crop_ha[ii])!=2) break;
	}
	fclose(fid);

	if(crop_ha[11]>0.0&&crop_ha[12]==0.0)
	{
		crop_ha[12] = crop_ha[11] * 0.3;
		crop_ha[11] *= 0.7;
	}

	int CropNum=ii-1,Si=m_WizardCrops.GetCurSel();
	
	char fname[256];

	//dndc74 zzz;

	m_WizardCrops.ResetContent();
	if (CropNum<=0) return FALSE;
	for (i=0;i<CropNum;i++)
	{
		sprintf(fname,"%s  (%.2f ha)",CROPSYSTEM[crop_ID[i+1]], crop_ha[i+1]);
		m_WizardCrops.AddString(fname);
	}

	if (Si>=0) m_WizardCrops.SetCurSel(Si);
	
	m_SCname.Format("%s,  %s", Cname, Sname);

	m_SiteName=m_SCname;

	UpdateData(FALSE);	

	//not all control paths return a value
}

void CSelectRegionDlg::OnSelchangeWizardCrops() 
{
	// TODO: Add your control notification handler code here		
	UpdateData(TRUE);

	CropOrder = m_WizardCrops.GetCurSel()+1;	
	CropType = WWW[CropOrder];
}

void CSelectRegionDlg::OnOK() 
{
	// TODO: Add extra validation here
#ifdef WIZARD 
	if(CropType<0)
	{
		AfxMessageBox("Please select a crop for this simulation");
		return;
	}
	else
	{		
		
		CString IDfile;
		FILE* fid;
		IDfile.Format("%s\\Inter\\SelectedCounty.txt", OUTPUT);
		fid = fopen(IDfile, "w");
		if ( fid == NULL )
		{
			CString mess;
			mess.Format("2. Can not create %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
		}
		fprintf(fid, "%s\n", Sname);
		fprintf(fid, "%s\n", Cname);
		fprintf(fid, "%d\n", CropType);
		fprintf(fid, "%f\n", crop_ha[CropOrder]);

		fclose(fid);

		SaveRegionDatatoFile();
	}

	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\OpenFile.txt", OUTPUT);
	db=fopen(DB, "w");
	fprintf(db, "%d", 1);
	fclose(db);
#endif
	
	CDialog::OnOK();
}

void CSelectRegionDlg::SaveRegionDatatoFile()
{
	int i, n;
	float NO3NH4_Rainfall;
	char ClimateFilename[200], temp[200], ww[300];
	int Soil_Texture, Soil_landuse;
	float Soil_Density, Soil_pH, Soil_OCatSurface;
	float Soil_Clay;
	
	float SoilBD1, SoilBD2, SoilPH1, SoilPH2, SoilOC1, SoilOC2, SoilCLAY1, SoilCLAY2;
	int SoilTexture1, SoilTexture2;
	float CropResidue[10];
	float ManureAmount[10], ManureCN[10];

	float IrriIndex[10];
	int CropPlantMonth[5], CropPlantDay[5];
	int CropHarvestMonth[5], CropHarvestDay[5], TillMethod[5], TillMonth[5], TillDay[5];
	int FertMonth[10], FertDay[10], FertMethod[10], ManureMonth[10];
	int ManureDay[10];
	

	int FloodStartMonth[10], FloodStartDay[10];
	int FloodEndMonth[10], FloodEndDay[10], FloodPH[10];
	int WeedTimes, IrriTimes, ManureTimes, FertTimes, TillTimes, FloodTimes;
	int GrazeTimes, GrazeStartMonth[10], GrazeStartDay[10], GrazeEndMonth[10], GrazeEndDay[10];
	float cattle[10], horse[10], sheep[10], hrs[10];
	int CropNumber[10], LeakType;

	CString File1, File2, File3, File4;
	FILE *f1, *f2, *f3, *f4;

	//open data files for reading
	CString county_ID1;
	char state_name[200], county_name[200];
	float longitude, latitude;
	
	//File1.Format("%s\\Database\\%s\\GIS\\%s_1.txt", m_FileName, m_FileName);
#ifdef USA
	File1.Format("%s\\Database\\%s\\GIS\\%s1_%s", ROOTDIR, m_FileName, m_FileName, state_id);
#else
	File1.Format("%s\\Database\\%s\\GIS\\%s_1.txt", ROOTDIR, m_FileName, m_FileName);
#endif
	
	f1=fopen(File1, "r");
	if (f1==NULL)
	{
		char err[120];
		sprintf(err, "Can not open %s", File1);
		AfxMessageBox(err);
		exit(0); 
	}
	fgets(ww, 300, f1);
	for(;;)
	{
		if (fscanf(f1, "%s %s  %s %f  %f", county_ID1, state_name, county_name, 
			&longitude, &latitude)!=5)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File1);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			if(WizardCountyID==county_ID1)
			{
				sprintf(IData.sitename, "%s-%s", state_name, county_name);
				break;
			}
		}
	}
	fclose(f1);

	//File2.Format("%s\\Database\\%s\\GIS\\%s_2.txt", m_FileName, m_FileName);
#ifdef USA
	File2.Format("%s\\Database\\%s\\GIS\\%s2_%s", ROOTDIR,m_FileName, m_FileName, state_id);
#else
	File2.Format("%s\\Database\\%s\\GIS\\%s_2.txt", ROOTDIR, m_FileName, m_FileName);
#endif

	f2=fopen(File2, "r");
	if (f2==NULL)
	{
		CString note;
		note.Format("Can not open file %s", File2);
		AfxMessageBox(note);
		exit(0);
	}
	fgets(ww, 300, f2);
	for(;;)
	{
		if (fscanf(f2, "%s  %s  %f", county_ID1, temp, &NO3NH4_Rainfall)!=3)
		{
			CString mess;
			mess.Format("Can not find data for polygon %s in state %s in %s.", WizardCountyID, state_name, File2);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
#ifdef USA	
			sprintf(ClimateFilename, "%s\\Database\\%s\\lib_clim\\%s\\%s.txt", ROOTDIR, m_FileName, m_yr, county_ID1);
#else
			sprintf(ClimateFilename, "%s\\Database\\%s\\lib_clim\\%s\\%s.txt", ROOTDIR, m_FileName, m_yr, temp);
#endif
			
			if(WizardCountyID==county_ID1)
			{
				break;
			}
		}
	}
	fclose(f2);

	if(strcmp(m_layerSelect,"China")==0)
	{
		CString NewClim;		
		NewClim = ConvertClimateFile(temp, ClimateFilename);
		sprintf(ClimateFilename, "%s", NewClim);
	}

	//File3.Format("%s\\Database\\%s\\GIS\\%s_3.txt", m_FileName, m_FileName);
#ifdef USA
	File3.Format("%s\\Database\\%s\\GIS\\%s3_%s", ROOTDIR, m_FileName, m_FileName, state_id);
#else
	File3.Format("%s\\Database\\%s\\GIS\\%s_3.txt", ROOTDIR, m_FileName, m_FileName);
#endif

	f3=fopen(File3, "r");
	if (f3==NULL)
	{
		CString note;
		note.Format("Can not open file %s", File3);
		AfxMessageBox(note);
		exit(0);
	}

	fgets(ww, 200, f3);
	fgets(ww, 200, f3);

/*#ifdef WIZARD	
	for(;;)
	{
		if (fscanf(f3, "%d %f %f %f %f %f %f %f %f %f %f %f %f", &county_ID1, 
			&SoilOC1, &SoilOC0, &SoilOC2, &SoilCLAY1, &SoilCLAY0, &SoilCLAY2, 
			&SoilPH1, &SoilPH0, &SoilPH2, &SoilBD1, &SoilBD0, &SoilBD2)!=13)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File2);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			if(WizardCountyID==county_ID1)
			{
				break;
			}
		}
	}
	fclose(f3);
#else*/
	for(;;)
	{
		if (fscanf(f3, "%s %f %f %f %f %f %f %f %f", county_ID1, 
			&SoilOC1, &SoilOC2, &SoilCLAY1, &SoilCLAY2, 
			&SoilPH1, &SoilPH2, &SoilBD1, &SoilBD2)!=9)
		{
			CString mess;
			mess.Format("Can not find data for county %s in state %s in %s.", county_name, state_name, File2);
			AfxMessageBox(mess);
			exit(0);
			
		}
		else
		{
			if(WizardCountyID==county_ID1)
			{
				break;
			}
		}
	}
	fclose(f3);

//#endif

	if(SoilPH1==SoilPH2)
	{
		SoilPH1 += 1.0;
		SoilPH2 -= 1.0;
	}

	Soil_Clay = (SoilCLAY1+SoilCLAY2)*0.5;

	if(CropType==20) Soil_landuse = 2; 
	else if(CropType==11||CropType==22) Soil_landuse = 4;
	else if(CropType==12) Soil_landuse = 3;
	else Soil_landuse = 1;
	
	Soil_Density = (SoilBD1+SoilBD2)*0.5;
	Soil_pH = (SoilPH1+SoilPH2)*0.5;
	Soil_OCatSurface = (SoilOC1+SoilOC2)*0.5;

	if (SoilOC1 >= 0.2) SoilTexture1 = 12;
	else SoilTexture1 = clay_texture(SoilCLAY1);
	
	if (SoilOC2 >= 0.2) SoilTexture2 = 12;
	else SoilTexture2 = clay_texture(SoilCLAY2);
	
	if (Soil_OCatSurface >= 0.2) Soil_Texture = 12;
	else Soil_Texture = clay_texture(Soil_Clay);

/*	CString KK;
	FILE *KKw;
	KK.Format("%s\\Inter\\SoilRanges.txt", OUTPUT);
	if ((KKw=fopen(KK,"w"))==NULL) 
	{
		CString note;
		note.Format("Can not create file %s", KK);
		AfxMessageBox(note);
		exit(0);
	}
    
    //fprintf(KKw,"Property   Ave    Max    Min:\n");
    fprintf(KKw,"SOC        %s     %s    %s\n", Soil_OCatSurface, SoilOC1, SoilOC2);
	fprintf(KKw,"Clay       %s     %s    %s\n", Soil_Clay, SoilCLAY1, SoilCLAY2);
	fprintf(KKw,"pH         %s     %s    %s\n", Soil_pH, SoilPH1, SoilPH2);
	fprintf(KKw,"Density    %s     %s    %s\n", Soil_Density, SoilBD1, SoilBD2);
	fprintf(KKw,"Texture    %d     %d    %d\n", Soil_Texture, SoilTexture1, SoilTexture2);
    
	fclose(KKw);
*/	

	CString FarmID;
	/*if(CropType<10) FarmID.Format("000%d", CropType);
	else if(CropType>=10&&CropType<100) FarmID.Format("00%d", CropType);
	else if(CropType>=100&&CropType<1000) FarmID.Format("0%d", CropType);
	else {}*/

	FarmID.Format("%d", CropType);

	File4.Format("%s\\Database\\%s\\\lib_farm\\farm%s.txt", ROOTDIR, m_FileName, FarmID);
	f4=fopen(File4, "r");
	if (f4==NULL)
	{
		char err[120];
		sprintf(err, "Can not open %s", File4);
		AfxMessageBox(err);
		exit(0); 
	}

	/*fscanf(f4, "%s %d", jk, &CropNumber[1]);
	fscanf(f4, "%s %d", jk, &CropPlantMonth[1]);
	fscanf(f4, "%s %d", jk, &CropPlantDay[1]);
	fscanf(f4, "%s %d", jk, &CropHarvestMonth[1]);
	fscanf(f4, "%s %d", jk, &CropHarvestDay[1]);
	fscanf(f4, "%s %f", jk, &CropResidue[1]);*/

	char note[300];
	int flag[5];
	float Optimum_yieldd[5];

	fscanf(f4, "%d  %s", &IData.cropping_number, note);
	//wwheat_flag = 0;
	for(n=1; n<=IData.cropping_number; n++)
	{
		
		fscanf(f4, "%d  %s", &CropNumber[n], note);
		fscanf(f4, "%f  %s", &Optimum_yieldd[n], note);
		fscanf(f4, "%d  %s", &CropPlantMonth[n], note);
		fscanf(f4, "%d  %s", &CropPlantDay[n], note);
		fscanf(f4, "%d  %s", &CropHarvestMonth[n], note);
		fscanf(f4, "%d  %s", &CropHarvestDay[n], note);
		fscanf(f4, "%f  %s", &CropResidue[n], note);
		fscanf(f4, "%d  %s", &flag[n], note);

		/*if(crop_ID[n]==1020)
		{
			RainfedFlag[n]=1;
			crop_ID[n]=20;
		}
		
		plant_jday[n] = JulianDay(plant_month, plant_day);
		harvest_jday[n] = JulianDay(harvest_month, harvest_day);

		R_GrowDays[n] = harvest_jday[n] - plant_jday[n];

		if(plant_jday[n] >= harvest_jday[n]) 
		{
			HarvYr[n] = 2; 
			WinterFlag[n] = 1;
			wwheat_flag = 1;
			R_GrowDays[n] = 365 - plant_jday[n] + harvest_jday[n] + (HarvYr[n] - 2) * 365;
			R_LeftDays[n] = R_GrowDays[n] - (365 - plant_jday[n]); 
		
			//WCropCode = crop_ID[n];
			//WOptYield = Optimum_yieldd[n];
			//WResidueFraction = ResidueFraction[n];
		}*/
	}

	/*fscanf(f4, "%s %d", jk, &TillTimes);
	for(k=1; k<=TillTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &TillMethod[k]);
		fscanf(f4, "%s %d", jk, &TillMonth[k]);
		fscanf(f4, "%s %d", jk, &TillDay[k]);
	}*/

	fscanf(f4, "%d  %s", &TillTimes, note);
		
			for(i=1; i<=TillTimes; i++)
			{
				fscanf(f4, "%d  %s", &TillMonth[i], note);
				fscanf(f4, "%d  %s", &TillDay[i], note);
				fscanf(f4, "%d  %s", &TillMethod[i], note);
				//till_date[i] = JulianDay(till_month, till_day);				
			}
	
	IrriTimes = 0;
	/*fscanf(f4, "%s %d", jk, &FertTimes);
	for(k=1; k<=FertTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &FertMonth[k]);
		fscanf(f4, "%s %d", jk, &FertDay[k]);
		fscanf(f4, "%s %d", jk, &FertMethod[k]);
		fscanf(f4, "%s %f", jk, &FertUrea[k]);
		fscanf(f4, "%s %f", jk, &FertAA[k]);
		fscanf(f4, "%s %f", jk, &FertAN[k]);
		fscanf(f4, "%s %f", jk, &FertAS[k]);
		fscanf(f4, "%s %f", jk, &FertAP[k]);
		fscanf(f4, "%s %f", jk, &FertAB[k]);
		fscanf(f4, "%s %f", jk, &FertNitrate[k]);
		//fscanf(f4, "%s %f", jk, &DayRelease[k]);
		//fscanf(f4, "%s %f", jk, &NIefficiency[k]);
		//fscanf(f4, "%s %f", jk, &NIduration[k]);
	}*/

	float fert_rate[50];
	fscanf(f4, "%d  %s", &FertTimes, note);			

	for(i=1; i<=FertTimes; i++)
				{
					fscanf(f4, "%d  %s", &FertMonth[i], note);
					fscanf(f4, "%d  %s", &FertDay[i], note);
					fscanf(f4, "%f  %s", &fert_rate[i], note);
					//fert_date[i] = JulianDay(fert_month, fert_day);
					FertMethod[i]=0;
				}

	/*fscanf(f4, "%s %d", jk, &ManureTimes);
	for(k=1; k<=ManureTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &ManureType[k]);
		fscanf(f4, "%s %f", jk, &ManureAmount[k]);
		fscanf(f4, "%s %f", jk, &ManureCN[k]);
		fscanf(f4, "%s %d", jk, &ManureMonth[k]);
		fscanf(f4, "%s %d", jk, &ManureDay[k]);
	}*/

	fscanf(f4, "%d  %s", &ManureTimes, note);
			
			for(i=1; i<=ManureTimes; i++)
			{
					fscanf(f4, "%d  %s", &ManureMonth[i], note);
					fscanf(f4, "%d  %s", &ManureDay[i], note);
					fscanf(f4, "%f  %s", &ManureAmount[i], note);
					fscanf(f4, "%f  %s", &ManureCN[i], note);

					//manu_date[i] = JulianDay(manu_month, manu_day);
			}

	/*fscanf(f4, "%s %f", jk, &IrriIndex[1]);
	IrriTimes = 0;*/

/*
	fscanf(f4, "%s %d", jk, &IrriTimes);
	for(k=1; k<=IrriTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &IrriMonth[k]);
		fscanf(f4, "%s %d", jk, &IrriDay[k]);
		fscanf(f4, "%s %f", jk, &IrriAmount[k]);
		fscanf(f4, "%s %f", jk, &IrriN[k]);

	}*/

	fscanf(f4, "%f  %s", &IrriIndex[1], note);

	/*fscanf(f4, "%s %d", jk, &FloodTimes);
	
	for(k=1; k<=FloodTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &LeakType);
		fscanf(f4, "%s %d", jk, &FloodStartMonth[k]);
		fscanf(f4, "%s %d", jk, &FloodStartDay[k]);
		fscanf(f4, "%s %d", jk, &FloodEndMonth[k]);
		fscanf(f4, "%s %d", jk, &FloodEndDay[k]);
		fscanf(f4, "%s %f", jk, &FloodPH[k]);
	}*/

	fscanf(f4, "%d  %s", &FloodTimes, note);

			for(i=1; i<=FloodTimes; i++)
			{
				fscanf(f4, "%d  %s", &FloodStartMonth[i], note);
				fscanf(f4, "%d  %s", &FloodStartDay[i], note);
				fscanf(f4, "%d  %s", &FloodEndMonth[i], note);
				fscanf(f4, "%d  %s", &FloodEndDay[i], note);

				FloodPH[i]=7.0;

				//flood_date1[i] = JulianDay(flood_month1, flood_day1);
				//flood_date2[i] = JulianDay(flood_month2, flood_day2);				
			}

			LeakType=1;

	/*fscanf(f4, "%s %d", jk, &WeedTimes);
	for(k=1; k<=WeedTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &WeedMonth[k]);
		fscanf(f4, "%s %d", jk, &WeedDay[k]);
		fscanf(f4, "%s %d", jk, &WeedProblem);
	}*/

	int cut_number, cut_month[50], cut_day[50];
	float cut_amount[50];
	fscanf(f4, "%d  %s", &cut_number, note);

			for(i=1; i<=cut_number; i++)
			{
					fscanf(f4, "%d  %s", &cut_month, note);
					fscanf(f4, "%d  %s", &cut_day, note);
					fscanf(f4, "%f  %s", &cut_amount[i], note);
	
					//cut_date[i] = JulianDay(cut_month, cut_day);
			}

	/*fscanf(f4, "%s %d", jk, &GrazeTimes);
	for(k=1; k<=GrazeTimes; k++)
	{
		fscanf(f4, "%s %d", jk, &GrazeStartMonth[k]);
		fscanf(f4, "%s %d", jk, &GrazeStartDay[k]);
		fscanf(f4, "%s %d", jk, &GrazeEndMonth[k]);
		fscanf(f4, "%s %d", jk, &GrazeEndDay[k]);
		fscanf(f4, "%s %f", jk, &cattle[k]);
		fscanf(f4, "%s %f", jk, &horse[k]);
		fscanf(f4, "%s %f", jk, &sheep[k]);
		fscanf(f4, "%s %f", jk, &hrs[k]);
	}*/

	fscanf(f4, "%d  %s", &GrazeTimes, note);

			for(i=1; i<=GrazeTimes; i++)
			{
					fscanf(f4, "%d  %s", &GrazeStartMonth[i], note);
					fscanf(f4, "%d  %s", &GrazeStartDay[i], note);
					fscanf(f4, "%d  %s", &GrazeEndMonth[i], note);
					fscanf(f4, "%d  %s", &GrazeEndDay[i], note);

					fscanf(f4, "%f  %s", &cattle[i], note);
					fscanf(f4, "%f  %s", &horse[i], note);
					fscanf(f4, "%f  %s", &sheep[i], note);
					fscanf(f4, "%f  %s", &hrs[i], note);

	
					//graze_date1[i] = JulianDay(graze_month1, graze_day1);
					//graze_date2[i] = JulianDay(graze_month2, graze_day2);
			}

	WeedTimes = 0;


    fclose(f4);       


	IData.years = 1;
	IData.latitude = latitude;
	IData.ifdaily = 1;

	IData.ClimateFileType = 1;
	IData.NO3NH4_Rainfall = NO3NH4_Rainfall;
	IData.NH3_Atmosphere = 0.06;
	IData.BaseCO2 = 350.0;
	IData.ClimateFileNumber = 1;

	IData.if1File = 0;//?
	IData.CO2IncreaseRate = 0.0;

	IData.Soil_Texture = Soil_Texture;
	IData.Soil_landuse = Soil_landuse;
	IData.Soil_Density = Soil_Density;
	IData.WaterPoolBD = Soil_Density;//Just set waterpool bd to be soil density
	IData.Soil_pH = Soil_pH;
	IData.Soil_OCatSurface = Soil_OCatSurface;
	IData.Soil_Clay = Soil_Clay;
	IData.Soil_BypassFlow = 0;
	IData.Soil_Litter = F_litter;
	IData.Soil_humads = F_humads;
	IData.Soil_humus = F_humus;
	IData.PassiveC = F_PassiveC;
	IData.Soil_NO3 = 10.0;
	IData.Soil_NH4 = 1.0;
	IData.Soil_moiture = 0.5;
	IData.Soil_T = 5.0;

	IData.Fldcap = 0.6; //?????????????
	IData.Wiltpt = 0.3;	
	IData.Sks = 1.2;
	IData.Soil_Porosity = 0.4;	
	IData.SOCa = SOCA[Soil_landuse];
	IData.SOCb = SOCB[Soil_landuse];
	IData.DClitter = 0.01;
	IData.DChumads = 0.05;
	IData.DChumus = 0.94;
	IData.HumadCN = 10.0;
	IData.HumusCN = 10.0;
	
	IData.Soil_MicrobioIndex = 1.0;	
	IData.HighestWT = 1.0;
	IData.Soil_WaterObstructLayer = 0;
    IData.slope = 0.0;  
	IData.UseION = 0; //???????????????
	IData.SCSuse = 0;
	IData.Soil_Quality = 0.0;
	IData.CheckHomo1 = 0;

	/*fprintf(fpo,"Climate_file_mode           %6d\n",0);
	fprintf(fpo,"Soil_microbial_index        %f\n",1.0);
	fprintf(fpo,"Crop_model_approach         %d\n",0);
	fprintf(fpo,"Depth_WRL_cm                %f\n", 100.0);
	fprintf(fpo,"Slope                       %f\n", 0.0);
	fprintf(fpo,"Field_capacity              %f\n", 0.0);
	fprintf(fpo,"Wilting_point               %f\n", 0.0);
	fprintf(fpo,"CO2_increase_rate           %f\n", 0.0);
	fprintf(fpo,"SOC_profile_A               %f\n",SOCA[Soil_landuse]);
	fprintf(fpo,"SOC_profile_B               %f\n",SOCB[Soil_landuse]);
	fprintf(fpo,"High_WT                     %d\n",0);
	fprintf(fpo,"Hydro_conductivity          %f\n", 0.0);
	fprintf(fpo,"Soil_porosity               %f\n", 0.0);
	fprintf(fpo,"Perennial_crop              %d\n", 0);*/

	
	char fname[250];
	FILE *fpo;
	sprintf(fname, "%s\\Inter\\InputParameters.txt", OUTPUT);
	if ((fpo=fopen(fname,"w"))==NULL) 
	{
		CString note;
		note.Format("Can not create file %s", fname);
		AfxMessageBox(note);
		exit(0);
	}
    
	SaveDatatoFile(fname, 2);

 /*  
    
    // Save crop parameter
	CropSystemID = 1;
    fprintf(fpo,"----------------------------------------\n");
    fprintf(fpo,"Crop_data:\n");
    fprintf(fpo,"Rotation_Number=            %d\n",1);
    for (i = 1; i<=1;i++) 
	{ 
		fprintf(fpo,"  Rotation_ID=              %d\n",1);
        fprintf(fpo,"  Totalyear=                %d\n", 1);
        fprintf(fpo,"  Years_Of_A_Cycle=         %d\n", 1);
		
        for (j = 1; j<=1;j++) 
		{
			int WaterC=0;

			fprintf(fpo,"    YearID_of_a_cycle=      %d\n",j);
            n = cropping_number;
            fprintf(fpo,"    Crop_total_Number=      %d\n",n); 
            for (k = 1; k<= n;k++)
			{
				if(CropNumber[k]==1020) 
				{
					CropNumber[k]=20;
					WaterC=1;
				}
				else
					WaterC=0;
				fprintf(fpo,"      Crop_ID=              %d\n",k);
                fprintf(fpo,"        Crop_Type=          %d\n",CropNumber[k]);
                fprintf(fpo,"        Plant_time=         %d %d\n", CropPlantMonth[k], CropPlantDay[k]);
				fprintf(fpo,"        Harvest_time=       %d %d\n",CropHarvestMonth[k], CropHarvestDay[k]);
				int HYY=1;
				if(CropPlantMonth[k]>CropHarvestMonth[k]) HYY=2;
                fprintf(fpo,"        Year_of_harvest=    %d\n",HYY);
                fprintf(fpo,"        Ground_Residue=     %6.4f\n",CropResidue[k]); 
				
				CropYield[k] = 0.4 * OptimumYield(CropNumber[k]);
				//else
				//	CropYield[k] = OptimumYield(20);
                fprintf(fpo,"        Yield=              %8.2f\n",CropYield[k]);
				fprintf(fpo,"        Rate_reproductive=  %8.2f\n",0.02);
				fprintf(fpo,"        Rate_vegetative=    %8.2f\n",0.015);
				fprintf(fpo,"        Psn_efficiency=     %8.2f\n",0.15);
				fprintf(fpo,"        Psn_maximum=        %8.2f\n",40.0);
				fprintf(fpo,"        Initial_biomass=    %8.2f\n",12.5);
				fprintf(fpo,"        Cover_crop=         %d\n",0);
            }
            
            n = TillTimes;
            fprintf(fpo,"    Tillage_number=         %d\n",n); 
            for (k = 1; k<= n; k++) {
                fprintf(fpo,"      Tillage_ID=           %d\n",k); 
                fprintf(fpo,"        Month/Day/method=   %d %d %d\n",TillMonth[k], TillDay[k], TillMethod[k]); 
            }
            
            n = FertTimes;
            fprintf(fpo,"    Fertil_number=          %d\n",n);
            for (k = 1; k<=n;k++) {

				if(FertMethod[k]==0) FertDepth = 0.0;
				else if(FertMethod[k]==1) FertDepth = 5.0;
				else if(FertMethod[k]==2) FertDepth = 10.0;
				else FertDepth = 20.0;

                fprintf(fpo,"      fertilization_ID=     %d\n",k); 
                fprintf(fpo,"        Month/Day/method=   %d %d %d\n", FertMonth[k], FertDay[k], FertMethod[k]); 
                
				fprintf(fpo,"        Depth=              %f\n",FertDepth); 
                fprintf(fpo,"        Nitrate=            %.2f\n",0.0); 
                fprintf(fpo,"        AmmBic=             %.2f\n",0.0); 
                fprintf(fpo,"        Urea=               %.2f\n",fert_rate[k]); 
                fprintf(fpo,"        Anh=                %.2f\n",0.0); 
                fprintf(fpo,"        NH4NO3=             %.2f\n",0.0);
                fprintf(fpo,"        NH42SO4=            %.2f\n",0.0); 
                fprintf(fpo,"        NH4HPO4=            %.2f\n",0.0); 
				fprintf(fpo,"      Release_rate=         %f\n",1.0); 
				fprintf(fpo,"      Inhibitor_efficiency= %f\n",0.0); 
				fprintf(fpo,"      Inhibitor_duration=   %f\n",0.0); 

				//DayRelease[k], NIefficiency[k], NIduration[k]
            }
                
            n = ManureTimes;
            fprintf(fpo,"    Manure_number=          %d\n",n);
            for (k = 1; k<= n;k++) {
				fprintf(fpo,"      Manure_ID=            %d\n",k); 
                fprintf(fpo,"        Month/Day=          %d %d\n",ManureMonth[k], ManureDay[k]);
                fprintf(fpo,"        Amount/C|N_ratio=   %f %f\n",ManureAmount[k], ManureCN[k]);
				fprintf(fpo,"        Type=               %d\n", 1);
            }
                
            n = WeedTimes;
            fprintf(fpo,"    Weed_number=            %d\n",n);
            fprintf(fpo,"    Weed_Problem=           %d\n",0); 
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Weeding_ID=           %d\n",k); 
                fprintf(fpo,"        Month/Day=          %d %d\n",WeedMonth[k], WeedDay[k]); 
            }
                
            n = FloodTimes;
            fprintf(fpo,"    Flood_number=           %d\n",n); 
            fprintf(fpo,"    Leak_type=              %d\n",1);
			fprintf(fpo,"    Water_control=          %d\n",WaterC);			
			fprintf(fpo,"    Leak_rate=              %f\n",1.000000);

            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Flooding_ID=          %d\n",k); 
                fprintf(fpo,"        Flood_Month/Day=    %d %d\n",FloodStartMonth[k], FloodStartDay[k]);
                fprintf(fpo,"        Drain_Month/Day=    %d %d\n",FloodEndMonth[k], FloodEndDay[k]);
				fprintf(fpo,"        Water_pH=    %f\n",7.0);
				fprintf(fpo,"        Shallow_flood=  %d\n",0);
			}

			if(WaterC==1)
			{
				fprintf(fpo,"        Water_gather=   %f\n", 1.5);//WaterGetherIndex				
			}
			if(WaterC==2)
			{
				fprintf(fpo,"        WT_file=        %s\n", "WT_file");
				fprintf(fpo,"        Vascularity=    %f\n", 0.0);
			}
                
            
            n = IrriTimes;
            fprintf(fpo,"    Irrigation_number=      %d\n",n); 
            fprintf(fpo,"    Irrigation_type=        %d\n",1);
			fprintf(fpo,"    Irrigation_Index=       %f\n",IrriIndex[1]); 
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Irrigation_ID=        %d\n",k); 
                fprintf(fpo,"        Irr_Month/Day=      %d %d\n",IrriMonth[k], IrriDay[k]); 
                fprintf(fpo,"        Water_amount/pH=    %f %f\n",IrriAmount[k], 7.0); 
            }

            n = GrazeTimes;
            fprintf(fpo,"    Grazing_number=           %d\n",n); 
            for (k = 1; k<= n;k++) 
			{
                fprintf(fpo,"      Grazing_ID=           %d\n",k); 
                fprintf(fpo,"        Start_Month/Day=    %d %d\n",GrazeStartMonth[k], GrazeStartDay[k]);
				fprintf(fpo,"        End_Month/Day=      %d %d\n",GrazeEndMonth[k], GrazeEndDay[k]);
                //fprintf(fpo,"        Animal_Type=        %d\n",grazing.get(i, j, k)->Type);
                fprintf(fpo,"        Cattle_Head_per_ha= %f\n",cattle[k]);
				fprintf(fpo,"        Horse_Head_per_ha_= %f\n",horse[k]);
				fprintf(fpo,"        Sheep_Head_per_ha_= %f\n",sheep[k]);
				fprintf(fpo,"        Graz_Hours_Per_day= %f\n",hrs[k]);
            }
			
			n=cut_number;
			fprintf(fpo,"    Cut_number=           %d\n",cut_number); 
			for (k = 1; k<= n;k++) 
			{
			
				fprintf(fpo,"        Cut_ID=           %d\n", k);
				fprintf(fpo,"        Cut_Month/Day=    %d %d\n", cut_month[k], cut_day[k]);
				fprintf(fpo,"        Cut_amount= %f\n", cut_amount[k]);
			}
			
						/*n = FilmTimes;
            fprintf(fpo,"    Film_number=            %d\n",n);
            
            for (k = 1; k<= n;k++) {
                fprintf(fpo,"      Film_ID=           %d\n",k); 
                fprintf(fpo,"      Start_Month/Day=          %d %d\n",FilmStartMonth[k], FilmStartDay[k]); 
				fprintf(fpo,"      Start_Month/Day=          %d %d\n",FilmEndMonth[k], FilmEndDay[k]); 
				fprintf(fpo,"      Film_type=           %d\n",FilmType[k]); 
			}
        }
    }
	
	
	fclose (fpo);
*/
	CString KK;
	FILE *KKw;
	KK.Format("%s\\Inter\\SoilRanges.txt", OUTPUT);
	if ((KKw=fopen(KK,"w"))==NULL) 
	{
		CString note;
		note.Format("Can not create file %s", KK);
		AfxMessageBox(note);
		exit(0);
	}
    
    fprintf(KKw,"Property   Ave           Max           Min:\n");
    fprintf(KKw,"SOC        %f     %f    %f\n", Soil_OCatSurface, SoilOC1, SoilOC2);
	fprintf(KKw,"Clay       %f     %f    %f\n", Soil_Clay, SoilCLAY1, SoilCLAY2);
	fprintf(KKw,"pH         %f     %f    %f\n", Soil_pH, SoilPH1, SoilPH2);
	fprintf(KKw,"Density    %f     %f    %f\n", Soil_Density, SoilBD1, SoilBD2);
	fprintf(KKw,"Texture    %d     %d    %d\n", Soil_Texture, SoilTexture1, SoilTexture2);
   
	fclose(KKw);

	CString CCrop;
	FILE* fCrop;
	CCrop.Format("%s\\Inter\\SiteLocation.txt", OUTPUT);
	fCrop = fopen(CCrop, "w");
	if(fCrop==NULL)
	{
		CString err;
		err.Format("Can not create file %s", CCrop);
		AfxMessageBox(err);
		exit(0);
	}
	fprintf(fCrop, "%f %f\n", -75.5, latitude); 
	fprintf(fCrop, "%ld %d\n", 1, 1); 
	fclose(fCrop);
  
}

float CSelectRegionDlg::OptimumYield(int CT)
{
	int crop;
	float yield, myc, grain, straw, root;

	FILE *fp;
    char  VEGE[80], note[160];
	CString note1;

	sprintf(VEGE, "%s\\Library\\LIB_CROP\\crop_%d", ROOTDIR, CT);
    fp = fopen(VEGE, "r");
    if ( fp == NULL )
    {
		sprintf(VEGE, "%s\\Library\\LIB_CROP\\crop_%d.txt", ROOTDIR, CT);
		fp = fopen(VEGE, "r");

		if ( fp == NULL )
		{
			CString mess;
			mess.Format("Can not open %s.", VEGE);
			AfxMessageBox(mess);
			exit(0);
		}
    }

    fscanf(fp, "%d %s", &crop, note);
    fscanf(fp, "%s %s", note, note);
    fscanf(fp, "%s %s", note, note);
    fscanf(fp, "%f %s", &myc, note);
    fscanf(fp, "%f %s", &grain, note);
    fscanf(fp, "%f %s", &straw, note);
    fscanf(fp, "%f %s", &root, note);
    fclose( fp );

	if(crop!=CT)
	{
		note1.Format("Error for crop type %d vs. %d", CT, crop);
		AfxMessageBox(note);
		exit(0);
	}

	yield = myc * grain / 0.4; //kg dry matter/ha

	return(yield);
}

int CSelectRegionDlg::clay_texture(float Clay)
{
	int ST;
	if (Clay <= .03) ST = 1;
		else if (Clay <=  .06) ST = 2;
		else if (Clay <= .09) ST = 3;
		else if (Clay <= .14) ST = 4;
		else if (Clay <= .19) ST = 5;
	    else if (Clay <= .27) ST = 6;
		else if (Clay <= .34) ST = 7;
		else if (Clay <= .41) ST = 8;
		else if (Clay <= .43) ST = 9;
		else if (Clay <= .49) ST = 10;
		else ST = 11;

	return(ST);
}


void CSelectRegionDlg::OnLandCover() 
{
	// TODO: Add your control notification handler code here
	char m_Watershed[200], m_yr[200];
	CString m_field;
	CString WS;
	FILE *ws;
	WS.Format("%s\\Inter\\MapSelect.txt", OUTPUT);
	ws=fopen(WS, "r");
	if(ws==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", WS);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(ws, "%s  %s", m_Watershed, m_yr);
	fclose(ws);

	CMoMapLayer layer;
	 COleVariant layername(m_Watershed);
	 CMoClassBreaksRenderer r;

	 CString fieldname = "Org_max";//land-use code

	 int nClasses = 10;
	 //double breaks[8] = {0,0.2,0.5, 1,1.5,2, 3, 4}; // class break values
	 double breaks[10] = {0.0,0.005,0.01,0.015, 0.02, 0.025, 0.03,0.035,0.04,0.045};

	 COLORREF startcolor, endcolor;

	 layer = m_map.GetLayers().Item(layername);
	 r.CreateDispatch("MapObjects2.ClassBreaksRenderer");
	 layer.SetRenderer(r);
	 r.SetBreakCount(nClasses-1);
	 r.SetField(fieldname);

	 for (int i = 0; i < nClasses-1; i ++)
	  r.SetBreak(i, breaks[i]);

	 startcolor = RGB(155,255,100);
	 endcolor = RGB(50,0,255);
	 r.RampColors(startcolor, endcolor);
	 m_map.Refresh();


}



void CSelectRegionDlg::OnAfterLayerDrawMap(short index, BOOL canceled, long hDC) 
{
	// TODO: Add your control notification handler code here
}

void CSelectRegionDlg::OnBeforeTrackingLayerDrawMap(long hDC) 
{
	// TODO: Add your control notification handler code here
	
}

void CSelectRegionDlg::OnBeforeLayerDrawMap(short index, long hDC) 
{
	// TODO: Add your control notification handler code here

}

void CSelectRegionDlg::OnSelectFarm() 
{
	// TODO: Add your control notification handler code here
	m_mouseAction = 0;
}

CString ConvertClimateFile(char *temp, char *ClimateFilename)
{
	int jd;
	float MinT, MaxT, rain, jf;
	char NewClim[200];

	sprintf(NewClim, "%s\\Inter\\%s", OUTPUT, temp);

	FILE *AA, *BB;
	AA = fopen(ClimateFilename, "r");
	if(AA==NULL)
	{
		CString note;
		note.Format("Cannot open %s", ClimateFilename);
		AfxMessageBox(note);
		exit(0);
	}

	BB = fopen(NewClim, "w");
	if(BB==NULL)
	{
		CString note;
		note.Format("Cannot create %s", NewClim);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(BB, "%s\n", temp);
	for(int i=1; i<=365; i++)
	{
		fscanf(AA, "%d %d %d %d %f %f %f %f %f %f %f %f", &jd, &jd, &jd, &jd, &jf, &MinT, &MaxT, &jf, &rain, &jf, &jf, &jf);

		fprintf(BB, "%d %f %f %f\n", i, MaxT, MinT, rain*0.1);
	}
	fclose(AA); fclose(BB);

	return(NewClim);
}

/*void Glean_StringM(char *String, int Num1, int Num2, char *Sub_Str)
// Abstract part of String (from Num1 to Num2) and put to Sub_Str

{
  int i, l;
  l=strlen(String);
  if(l==4) Num2--;
  if(Num1>Num2)  
  {
    //printf("%s\n",String);
    //Hint("Num1>Num2 in Glean_String",String);
    Sub_Str[0]='\0';
    return;
  }
  if (Num1>l) 
  {
    //Hint("Out of range ",String);
    Sub_Str[0]='\0';
    return;
  }
    if (Num2>l)  Num2=l;
    for(i=Num1;i<=Num2;i++)
	    Sub_Str[i-Num1]=String[i];	
		Sub_Str[i-Num1]='\0';
}
*/
