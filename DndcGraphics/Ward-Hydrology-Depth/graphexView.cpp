//DNDC coded by Changsheng Li, University of New Hampshire in 1989-2012

#include "stdafx.h"
#include "dndc71.h"
//#include "dndc_main.h"

#include <direct.h>
#include <stdio.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

#include "MainFrm.h"
#include "SitePara.h"
#include "SitePage1.h"
#include "graphexDoc.h"
#include "graphexView.h"
#include "CreateInputFile.h"

#include "dndc_main.h"
#include "RegionInput.h"
#include "MonteCarloRegionSelect.h"
#include "MonteCarlo.h"
#include "WizardCrops.h"
//#include "ountySave.h"
#include "WizardUncertainty.h"
#include "SitePage1.h"
#include "RegionMap.h"
#include "NewCrop.h"
#include "ExtractData.h"
//#include "UncertaintyInput.h"
#include "D:\test\code\DNDC95\DNDCgo.h"
#include "WizardResult.h"
#include "SitePage1.h"
#include "GlobeMap.h"
#include "GlobeData.h"
#include "GlobeDataExtract.h"
#include "MapSelect.h"

#include "BatchRun.h"
#include "MonteCarloParameters.h"
#include "MapLayer.h"
#include "ombineFiles.h"
#include "ExtractData.h"
#include "dndc_tool.h"
#include "dndc_RegionFiles.h"
#include "ScreenMonitor.h"
#include "Dndc_YieldPredict.h"
#include "DrawDrought.h"
#include "SelectRegionDlg.h"

// Dispatch interfaces referenced by this interface
#include "MoLayers.h"
#include "MoRectangle.h"
#include "motrackinglayer.h"
#include "MoPoint.h"
#include "moellipse.h"
#include "MoLine.h"
#include "mopolygon.h"
#include "mogeodatasets.h"
#include "MoDataConnection.h"
#include "mogeodataset.h"
#include "momaplayer.h"
#include "morecordset.h"
#include "MoFields.h"
#include "MoField.h"
#include "mopoints.h"
#include "MoSymbol.h"
#include "movaluemaprenderer.h"
#include "MoStrings.h"
#include "MoStatistics.h"
#include "MoClassBreaksRenderer.h"
#include "MoDotDensityRenderer.h"
#include "MoLabelRenderer.h"
#include "MoGeoEvent.h"
#include "MoImageLayer.h"
#include "motable.h"
#include "MoTextSymbol.h"
#include "MoTableDesc.h"
#include "MoAddressLocation.h"
#include "MoPlaceLocator.h"
#include "moparts.h"
#include "MoProjection.h"
#include "MoProjCoordSys.h"
#include "mogeocoordsys.h"
#include "MoUnit.h"
#include "modatum.h"
#include "MoSpheroid.h"
#include "MoPrimeMeridian.h"
#include "mogeotransformation.h"
#include "mostandardizer.h"
#include "MoGeocoder.h"
#include "MoZRenderer.h"
#include "MoGroupRenderer.h"
#include "MoChartRenderer.h"
#include "MoLabelPlacer.h"
#include "moeventrenderer.h"
#include "SelectShapeMap.h"
#include "DNDC_Map.h"
#include "SaveSoilYear.h"
#include "FarmCompost.h"
#include "FarmLagoon.h"

//DNDCSystem DNDCSys;
//void draw_cover(CGraphexDoc *pDoc);
//extern void DNDCmain(CGraphexDoc* pDoc);

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString RegionModel="Work";//"noWork";//
CString PaleoMode="Work";//"noWork";//
int tmd=0;
char StateName[300], CountyName[300];
int cropID, SelectMap2;

void ReadDatafromFile_NG(char *fname);

int JulDay(int month, int day);
void Color1(float FT, int *RR,int *GG,int *BB, int Item);
char DndFileName[400];
//void Glean_StringP(char *String, int Num1, int Num2, char *Sub_Str);

////////////////////////////////////////////////////////////////////////////
// CGraphexView
//=============================================
/*int getdir (string dir, vector<string> &files)
{
DIR *dp;
struct dirent *dirp;
if((dp = opendir(dir.c_str())) == NULL) {
cout << "Error(" << errno << ") opening " << dir << endl;
return errno;
}

while ((dirp = readdir(dp)) != NULL) {
files.push_back(string(dirp->d_name));
}
closedir(dp);
return 0;
}*/
//=========================================

IMPLEMENT_DYNCREATE(CGraphexView, CView)

BEGIN_MESSAGE_MAP(CGraphexView, CView)
	//{{AFX_MSG_MAP(CGraphexView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_IfRedarwAll, OnIfRedarwAll)
	ON_UPDATE_COMMAND_UI(ID_IfRedarwAll, OnUpdateIfRedarwAll)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_IfStop, OnIfStop)
	ON_COMMAND(ID_IfPause, OnIfPause)
	ON_UPDATE_COMMAND_UI(ID_IfPause, OnUpdateIfPause)
	ON_COMMAND(ID_InputSite, OnInputSite)
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_MODIFYCOLORSCALE, OnViewModifycolorscale)
	ON_COMMAND(ID_CropPropertyDB, OnCropPropertyDB)
	ON_COMMAND(ID_IfDoOneTime, OnIfDoOneTime)
	ON_COMMAND(ID_RunSite, OnRunSite) //need2fix
	ON_COMMAND(ID_InputRegion, OnInputRegion)
	ON_COMMAND(ID_RunRegion, OnRunRegion)
	ON_COMMAND(ID_Mapping, OnMapping)
	ON_COMMAND(ID_SelectCounty, OnSelectCounty)
	ON_COMMAND(ID_SelectState, OnSelectState)
	ON_COMMAND(ID_MonteCarlo, OnMonteCarlo)
	ON_COMMAND(ID_RunUncertainty, OnRunUncertainty)
	ON_COMMAND(ID_DrawFlux, OnDrawFlux)
	ON_COMMAND(ID_Region, OnRegion)
	ON_COMMAND(ID_Draw, OnDrawMap)
	ON_COMMAND(ID_MCresult, OnMCresult)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_WizardSelectCounty, OnWizardSelectCounty)
	ON_COMMAND(ID_MapCounty, OnMapCounty)
	ON_COMMAND(ID_MapCrops, OnMapCrops)
	ON_COMMAND(ID_MapCorn, OnMapCorn)
	ON_COMMAND(ID_WWheat, OnWWheat)
	ON_COMMAND(ID_SWheat, OnSWheat)
	ON_COMMAND(ID_Sunflower, OnSunflower)
	ON_COMMAND(ID_Sugarcane, OnSugarcane)
	ON_COMMAND(ID_Soybean, OnSoybean)
	ON_COMMAND(ID_Sorghum, OnSorghum)
	ON_COMMAND(ID_Barley, OnBarley)
	ON_COMMAND(ID_Beet, OnBeet)
	ON_COMMAND(ID_Cotton, OnCotton)
	ON_COMMAND(ID_LegumeHay, OnLegumeHay)
	ON_COMMAND(ID_Nonlegume_hay, OnNonlegumehay)
	ON_COMMAND(ID_Oats, OnOats)
	ON_COMMAND(ID_Peanut, OnPeanut)
	ON_COMMAND(ID_Pineapple, OnPineapple)
	ON_COMMAND(ID_Potato, OnPotato)
	ON_COMMAND(ID_Rice, OnRice)
	ON_COMMAND(ID_Tobacco, OnTobacco)
	ON_COMMAND(ID_Vegetable, OnVegetable)
	ON_COMMAND(ID_WizardSelectCrop, OnWizardSelectCrop)
	ON_COMMAND(ID_ResultReview, OnResultReview)
	ON_COMMAND(ID_ResultRecord, OnResultRecord)
	ON_COMMAND(ID_Uncertainty, OnUncertainty)
	ON_COMMAND(ID_WizardMonteCarlo, OnWizardMonteCarlo)
	ON_COMMAND(ID_MSF, OnMsf)
	ON_COMMAND(ID_RegionInput, OnRegionInput)
	ON_COMMAND(ID_RegionRun, OnRegionRun)
	ON_COMMAND(ID_ESreview, OnESreview)
	ON_COMMAND(ID_RegionMap, OnRegionMap)
	ON_COMMAND(ID_CreateCrop, OnCreateCrop)
	ON_COMMAND(ID_ExtractData, OnExtractData)
	ON_COMMAND(ID_SiteResult, OnSiteResult)
	ON_COMMAND(ID_GlobeMap, OnGlobeMap)
	ON_COMMAND(ID_GlobeData, OnGlobeData)
	ON_COMMAND(ID_convert, Onconvert)
	ON_BN_CLICKED(IDC_MapView, OnMapView)
	ON_COMMAND(ID_Batch, OnBatch)
	ON_COMMAND(ID_SiteParameter, OnSiteParameter)
	ON_COMMAND(ID_MapLayer, OnMapLayer)
	ON_COMMAND(ID_ConvertData, OnConvertData)
	ON_COMMAND(ID_Convert1, OnConvert1)
	ON_COMMAND(ID_Convert2, OnConvert2)
	ON_COMMAND(ID_Convert3, OnConvert3)
	ON_COMMAND(ID_Convert4, OnConvert4)
	ON_COMMAND(ID_Convert5, OnConvert5)
	ON_COMMAND(ID_Convert6, OnConvert6)
	ON_COMMAND(ID_SoilDensity, OnSoilDensity)
	ON_COMMAND(ID_Globe5, OnGlobe5)
	ON_COMMAND(ID_Convert7, OnConvert7)
	ON_COMMAND(ID_5min_30min, On5min30min)
	ON_COMMAND(ID_5minSOIL_30minSOIL, On5minSOIL30minSOIL)
	ON_COMMAND(ID_USAdata, OnUSAdata)
	ON_COMMAND(ID_DNDC1, OnDndc1)
	ON_COMMAND(ID_DndcMap, OnDndcMap)
	ON_COMMAND(ID_Day1snow, OnDay1snow)
	ON_COMMAND(ID_CombineFiles, OnCombineFiles)
	ON_COMMAND(ID_ExtractNation, OnExtractNation)
	ON_COMMAND(ID_RegionData, OnRegionData)
	ON_COMMAND(ID_RunMonteCarlo, OnRunMonteCarlo)
	ON_COMMAND(ID_ConvertClimateData, OnConvertClimateData)
	ON_COMMAND(ID_SnowPack, OnSnowPack)
	ON_COMMAND(ID_SiteModeTest, OnSiteModeTest)
	ON_COMMAND(ID_GlobeDataProcess, OnGlobeDataProcess)
	ON_COMMAND(ID_YieldPredict, OnYieldPredict)
	ON_COMMAND(ID_YieldShow, OnYieldShow)
	ON_COMMAND(ID_Liaoning, OnLiaoning)
	ON_COMMAND(ID_YieldReSet, OnYieldReSet)
	ON_COMMAND(ID_SaveSoilFile, OnSaveSoilFile)
	ON_COMMAND(ID_Linux, OnLinux)
	ON_COMMAND(ID_GateTest, OnGateTest)
	ON_COMMAND(ID_FarmCompost, OnFarmCompost)
	ON_COMMAND(ID_RunFarmComponent, OnRunFarmComponent)
	ON_COMMAND(ID_FarmLagoon, OnFarmLagoon)
	//}}AFX_MSG_MAP
	// Standard printing commands
	//ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)


END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGraphexView construction/destruction

CGraphexView::CGraphexView()
{
	// TODO: add construction code here
	m_Draw=0;
	//m_hCursor=AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_IfRedraw  = "ReDraw";
	//option = 0;
}

CGraphexView::~CGraphexView()
{
}

BOOL CGraphexView::PreCreateWindow(CREATESTRUCT& cs)
{
#ifdef DEGUI 
	//OnRunRegion();
	OnLinux();
	
	//AfxMessageBox("The simulation is accomplished");
	exit(0);
#else
#endif
	

	cs.lpszClass=AfxRegisterWndClass (CS_HREDRAW|CS_VREDRAW,0,
		(HBRUSH)::GetStockObject(WHITE_BRUSH),0); 

	return CView::PreCreateWindow(cs);
}
 

void CGraphexView::OnPrepareDC(CDC *pDC,CPrintInfo* pInfo)
{
	CRect rectClient;
	GetClientRect(rectClient);
	
	CGraphexDoc* pDoc = GetDocument();
	//pDoc->Prepare();

	CClientDC dc(this);
	//pDoc->SetViewWindow(&rectClient,&dc);

	CView::OnPrepareDC(pDC,pInfo); 

}

/////////////////////////////////////////////////////////////////////////////
// CGraphexView drawing

void CGraphexView::OnDraw(CDC* pDC)
{
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	static int IniFlag=0;
	// TODO: add draw code for native data here

	//if(IniFlag==0)
	//{
	CRect rect;							//create a point for rectangle
	GetClientRect(&rect);				//obtain client rectangule
	CBrush *pOldBrush = pDC->GetCurrentBrush(); //create a point for brush
	CBrush br;							//create a brush
	br.CreateSolidBrush(RGB(80,150,100)); //define the brush
	pDC->SelectObject(&br);				//select the brush into the brush point
	//pDC->Rectangle(&rect);				//draw the rectangle with the brush
	pDC->FillRect(rect, &br);
	pDC->SelectObject(pOldBrush);		//return original brush into the brush point

	IPicture *pPic; 
    IStream *pStm; 
    CFileStatus fstatus; 
    CFile file; 
    LONG cb; 

	char FigTitle[200];
	float sss;
	//page_1(FigTitle);

	CString face;
#ifdef BASE
	face.Format("%s\\library\\gleaner2.jpg", ROOTDIR);
	sss=75.0;
#endif
#ifdef WIZARD
	face.Format("%s\\library\\China.jpg", ROOTDIR);
	//face.Format("/dndc/library/USA3.jpg");
	sss=100.0;
#endif
#ifdef MANURE
	face.Format("%s\\library\\LivestockFarm.jpg", ROOTDIR);
	sss=55.0;
#endif

	//face.Format("%s", FigTitle);

	if (file.Open(face,CFile::modeRead)&&file.GetStatus(face, fstatus)&&((cb = fstatus.m_size) != -1)) 
    { 
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb); 
        LPVOID pvData = NULL; 
        if (hGlobal != NULL) { 
            if ((pvData = GlobalLock(hGlobal)) != NULL) { 
                file.Read(pvData, cb); 
                GlobalUnlock(hGlobal); 
                CreateStreamOnHGlobal(hGlobal, TRUE, &pStm); 
                if(SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic))) { 
                       OLE_XSIZE_HIMETRIC hmWidth; 
                       OLE_YSIZE_HIMETRIC hmHeight; 
                       pPic->get_Width(&hmWidth); 
                       pPic->get_Height(&hmHeight); 
                       double fX,fY; 
                       fX = (double)pDC->GetDeviceCaps(HORZRES)*(double)hmWidth/
                                ((double)pDC->GetDeviceCaps(HORZSIZE)*sss); 
                       fY = (double)pDC->GetDeviceCaps(VERTRES)*(double)hmHeight/
                                ((double)pDC->GetDeviceCaps(VERTSIZE)*sss); 
                       if(FAILED(pPic->Render(*pDC,0,0,(DWORD)fX,(DWORD)fY,0,hmHeight,hmWidth,-hmHeight,NULL))) 
                                AfxMessageBox("Failed To Render The picture!"); 
                       pPic->Release(); 
                 } 
                 else 
                      AfxMessageBox("Error Loading Picture From Stream!"); 
            } 
       } 
	} 
    else 
	{
        AfxMessageBox("You may have the DNDC model installed in an incorrect place. Please move the entire DNDC folder to the root directory of any drive in your computer!");
		//exit(0);
	}


#ifdef WIZARD
	{
		//int cc1=30, cc2=50, cc3=80;
		int cc1=20, cc2=20, cc3=100;
		int z1=255, z2=255, z3=255;
		int t1=70, t2=30, t3=0;

		POSITION pos = pDoc->GetFirstViewPosition();
		CView* pDC = pDoc->GetNextView( pos );
		CClientDC art(pDC);

		CFont hNewFont;
		TEXTMETRIC tm;
		CString dndc;

#ifdef CHINA		
		dndc.Format("A Decision Support System for Agroecosystems of China");

		hNewFont.CreateFont(40,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);

		art.SetTextAlign(TA_CENTER);

		//art.SetTextColor(RGB(40,31,32));//5,85,100));	
		//
		//art.TextOut(519, 70, dndc);

		art.SetTextColor(RGB(55,90,120));		
		art.TextOut(522, 67, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "(China-DNDC)");

		hNewFont.CreateFont(35,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

	
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);

		//art.SetTextColor(RGB(40,31,32));//(5,85,100));	
		art.SetTextAlign(TA_CENTER);
		//art.TextOut(520, 145, dndc);

		art.SetTextColor(RGB(55,90,120));		
		art.TextOut(522, 225, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "Institute of Agricultural Resources and Regional Planning");

		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);		

		art.SetTextAlign(TA_CENTER);
		art.SetTextColor(RGB(cc1,cc2,cc3));
		art.TextOut(520, 352, dndc);

		//art.SetTextColor(RGB(246,255,240));		
		//art.TextOut(522, 300, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "Chinese Academy of Agricultural Sciences");

		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);		

		art.SetTextAlign(TA_CENTER);
		art.SetTextColor(RGB(cc1,cc2,cc3));
		art.TextOut(520, 402, dndc);

		//art.SetTextColor(RGB(246,255,240));		
		//art.TextOut(522, 350, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "Institute for the Study of Earth, Oceans, and Space");

		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);		

		//art.SetTextColor(RGB(255,255,255));
		art.SetTextAlign(TA_CENTER);
		//art.TextOut(520, 350, dndc);

		art.SetTextColor(RGB(cc1, cc2, cc3));		
		art.TextOut(520, 499, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "University of New Hampshire"); 
		hNewFont.CreateFont(t2,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		//art.SetTextColor(RGB(z1,z2,z3));	
		art.SetTextAlign(TA_CENTER);
		//art.SetTextColor(RGB(255,255,255));
		//art.TextOut(520, 390, dndc);
		art.SetTextColor(RGB(cc1, cc2, cc3));
		art.TextOut(520, 549, dndc);
		hNewFont.DeleteObject();
#endif

#ifdef USA		
		dndc.Format("Welcome to Greenhouse Gas Wizard");

		hNewFont.CreateFont(55,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);

		art.SetTextAlign(TA_CENTER);

		//art.SetTextColor(RGB(40,31,32));//5,85,100));	
		//
		//art.TextOut(519, 70, dndc);

		art.SetTextColor(RGB(55,80,120));		
		art.TextOut(522, 75, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "( US-DNDC )");

		hNewFont.CreateFont(35,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

	
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);

		//art.SetTextColor(RGB(40,31,32));//(5,85,100));	
		art.SetTextAlign(TA_CENTER);
		//art.TextOut(520, 145, dndc);

		art.SetTextColor(RGB(55,80,120));		
		art.TextOut(522, 170, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "Institute for the Study of Earth, Oceans, and Space");

		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);		

		art.SetTextAlign(TA_CENTER);
		art.SetTextColor(RGB(cc1,cc2,cc3));
		art.TextOut(520, 300, dndc);

		//art.SetTextColor(RGB(246,255,240));		
		//art.TextOut(522, 300, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "University of New Hampshire");

		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);		

		art.SetTextAlign(TA_CENTER);
		art.SetTextColor(RGB(cc1,cc2,cc3));
		art.TextOut(520, 350, dndc);

		//art.SetTextColor(RGB(246,255,240));		
		//art.TextOut(522, 350, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "Environmental and Societal Impacts Group");

		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);		

		//art.SetTextColor(RGB(255,255,255));
		art.SetTextAlign(TA_CENTER);
		//art.TextOut(520, 350, dndc);

		art.SetTextColor(RGB(cc1, cc2, cc3));		
		art.TextOut(520, 450, dndc);

		hNewFont.DeleteObject();

//		int z1=255, z2=255, z3=255;
//		int t1=70, t2=30, t3=0;


		dndc.Format("%s", "National Center for Atmospheric Research"); 
		hNewFont.CreateFont(t2,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		//art.SetTextColor(RGB(z1,z2,z3));	
		art.SetTextAlign(TA_CENTER);
		//art.SetTextColor(RGB(255,255,255));
		//art.TextOut(520, 390, dndc);
		art.SetTextColor(RGB(cc1, cc2, cc3));
		art.TextOut(520, 500, dndc);
		hNewFont.DeleteObject();
		
/*		dndc.Format("%s", "and"); 
		hNewFont.CreateFont(t2,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		//art.SetTextColor(RGB(z1,z2,z3));	
		art.SetTextAlign(TA_CENTER);
		//art.SetTextColor(RGB(255,255,255));
		//art.TextOut(520, 430, dndc);
		art.SetTextColor(RGB(cc1, cc2, cc3));
		art.TextOut(520, 429, dndc);
		hNewFont.DeleteObject();

		dndc.Format("%s", "Environmental and Societal Impacts Group"); 
		hNewFont.CreateFont(t2,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		//art.SetTextColor(RGB(z1,z2,z3));	
		art.SetTextAlign(TA_CENTER);
		//art.SetTextColor(RGB(255,255,255));
		//art.TextOut(520, 470, dndc);
		art.SetTextColor(RGB(cc1, cc2, cc3));
		art.TextOut(520, 469, dndc);
		hNewFont.DeleteObject();

		dndc.Format("%s", "National Center for Atmospheric Research"); 
		hNewFont.CreateFont(t2,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		//art.SetTextColor(RGB(z1,z2,z3));	
		art.SetTextAlign(TA_CENTER);
		//art.SetTextColor(RGB(255,255,255));
		//art.TextOut(520, 510, dndc);
		art.SetTextColor(RGB(cc1, cc2, cc3));
		art.TextOut(520, 509, dndc);
		hNewFont.DeleteObject();*/
#endif
	}
#else 
	{
		POSITION pos = pDoc->GetFirstViewPosition();
		CView* pDC = pDoc->GetNextView( pos );
		CClientDC art(pDC);

		CFont hNewFont;
		TEXTMETRIC tm;
		CString dndc;
#ifdef MANURE
		dndc.Format("%s", "Welcome to Manure-DNDC");

		hNewFont.CreateFont(65,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);

		art.SetTextAlign(TA_CENTER);

		art.SetTextColor(RGB(249,255,230));		
		art.TextOut(500, 142, dndc);

		art.SetTextColor(RGB(155,160,64));	//155,160,64	
		art.TextOut(502, 140, dndc);

		hNewFont.DeleteObject();
#else
		
		dndc.Format("%s", "Welcome to DNDC");

		hNewFont.CreateFont(65,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);

		art.SetTextAlign(TA_CENTER);

		art.SetTextColor(RGB(249,255,230));		
		art.TextOut(500, 48, dndc);

		art.SetTextColor(RGB(155,160,64));		
		art.TextOut(500, 50, dndc);

		hNewFont.DeleteObject();
#endif

		
	}
	
#endif

	if(IniFlag==0)
	{
		//draw_cover(pDoc);
		POSITION pos = pDoc->GetFirstViewPosition();
		CView* pDC = pDoc->GetNextView( pos );
		CClientDC art(pDC);

		int c1=200,c2=250,c3=220;
		CFont hNewFont;
		TEXTMETRIC tm;
		CString dndc;
		//dndc.Format("%s", "Welcome to DNDC");

		hNewFont.CreateFont(65,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);

		art.SetTextAlign(TA_CENTER);

		art.SetTextColor(RGB(249,255,230));		
		art.TextOut(500, 50, dndc);

		art.SetTextColor(RGB(155,160,64));		
		art.TextOut(500, 52, dndc);

		hNewFont.DeleteObject();

	IniFlag++;
	}
	
	char F_INI[200];
	FILE *fpp;
	sprintf(F_INI, "%s\\INPUTS\\cropini-1", OUTPUT);    
	fpp = fopen(F_INI, "w");
	if (fpp == NULL) note(1, F_INI); 
	fprintf(fpp, "%d\n", 0);
	fclose( fpp );

	CString DM;
	FILE *dm;
	DM.Format("%s\\DroughtMode", INTER);
	dm=fopen(DM, "w");
	fprintf(dm, "%d", 0);
	fclose(dm);

	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", 0);
	fclose(ddb);

/*	CFileDialog ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.dnd)|*.dnd|All files (*.*)|*.*||", NULL );

	ask.DoModal();
	char cst[255];
	strcpy(cst,ask.GetPathName());
	if (strlen(cst)==0) return;

	CreateDndcInputFiles(cst);

	OnRunSite(0, 0, 0);
	exit(0);
*/

/*	char MB[200];
	FILE *db;
	sprintf(MB, "%s\\Result\\inter\\OpenFile.txt", ROOTDIR);
	db=fopen(MB, "w");
	if(db==NULL) note(1, MB);
	fprintf(db, "%d", 0);
	fclose(db);
*/
/*	char DB[200];
	for(int k=1; k<=10; k++)
		{
			sprintf(DB, "%s_1\\CropRotation_%d.txt", INTERMANAGE, k);//write: Initial files
			db=fopen(DB, "w");
			if(db==NULL) note(1,DB);
			fprintf(db, "%d %d %d", k, 1, 1);
			fclose(db);
		}
*/

}



/////////////////////////////////////////////////////////////////////////////
// CGraphexView diagnostics

#ifdef _DEBUG
void CGraphexView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphexView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphexDoc* CGraphexView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphexDoc)));
	return (CGraphexDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////


void CGraphexView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
#ifdef WIZARD
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(ShowSiteFlag==1) 
		ShowMapValue(pDoc,point);
#endif

}


void CGraphexView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return;

}


#include "SitePSheet.h"

void CGraphexView::OnIfRedarwAll() 
{
	if (m_IfRedraw=="ReDraw") 
	{
		m_IfRedraw="NoReDraw";
	}
	else m_IfRedraw="ReDraw";
	CGraphexDoc* pDoc = GetDocument();
	pDoc->m_IfRedraw = m_IfRedraw;
}

void CGraphexView::OnUpdateIfRedarwAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	if (m_IfRedraw=="ReDraw") {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}
}

void CGraphexView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int i;

	i=nChar;
	if (nChar==27) {//ESC key is pressed
		CGraphexDoc* pDoc = GetDocument();
		pDoc->StopRun = -1;
		link.StopRun = -1;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphexView::OnIfStop() 
{
	CGraphexDoc* pDoc = GetDocument();
	if (pDoc->StopRun == -1 || pDoc->StopRun == 2) 
		pDoc->StopRun = 1;
	link.StopRun = pDoc->StopRun;
}

void CGraphexView::OnIfPause() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	if (pDoc->StopRun == 0) 
		return;
	if (m_IfPause=="Pause") 
	{
		m_IfPause="Continue";
		pDoc->StopRun = -1;
	}
	else 
	{
		m_IfPause="Pause";
		pDoc->StopRun = 2;
	}
	link.StopRun = pDoc->StopRun;
}

void CGraphexView::OnUpdateIfPause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_IfPause=="Pause") {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}	
}

void CGraphexView::OnIfDoOneTime() 
{
	CGraphexDoc* pDoc = GetDocument();
	if (pDoc->StopRun == 0) return;
	pDoc->StopRun = -5;
	link.StopRun = -5;
}


void CGraphexView::OnInputSite() //OK on main manu
{
	CString DIR0;
	DIR0.Format("%s", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result", ROOTDIR);
	mkdir(DIR0);
	
	CString DIR1;
	DIR1.Format("%s\\Result\\Inputs", ROOTDIR);
	mkdir(DIR1);

	CString DIR2;
	DIR2.Format("%s\\Result\\Inter", ROOTDIR);
	mkdir(DIR2);
	
	DIR2.Format("%s\\Result\\Inter\\Management_1", ROOTDIR);
	mkdir(DIR2);
	
	DIR2.Format("%s\\Result\\Inter\\RegionFiles", ROOTDIR);
	mkdir(DIR2);

	CString DIR3;
	DIR3.Format("%s\\Result\\Record", ROOTDIR);
	mkdir(DIR3);

	DIR0.Format("%s\\Result\\Record\\Region", ROOTDIR);
	mkdir(DIR0);
	DIR0.Format("%s\\Result\\Record\\Site", ROOTDIR);
	mkdir(DIR0);
	//DIR0.Format("%s\\Record\\RegionSummary", OUTPUT);
	//mkdir(DIR0);
	//DIR0.Format("%s\\Record\\SiteSummary", OUTPUT);
	//mkdir(DIR0);
	DIR0.Format("%s\\Result\\Record\\MonteCarlo", ROOTDIR);
	mkdir(DIR0);

	CString DB;
	FILE *db;
	
	DB.Format("%s\\Result\\inter\\OpenFile.txt", ROOTDIR);
	db=fopen(DB, "w");
	fprintf(db, "%d", 1);
	fclose(db);

	ShowSiteFlag = 0;

	char sitefile[80];
	FILE *fpp;

			sprintf(sitefile, "%s\\Result\\Inter\\DaymetFlag", ROOTDIR);
			fpp = fopen(sitefile, "w");
			if ( fpp == NULL )
			{
				printf("Can not create file %s", sitefile);
				getch();
				exit(0);
			}
 
			fprintf(fpp, "%d", 0);
			fclose(fpp);
	
	CSitePSheet uu;

	if (uu.DoModal()==IDOK) //OK for closing input process
	{
		char site_file[80];
		FILE *fp;
		int DDaymetFlag;

/*		sprintf(site_file, "%s\\Result\\Inter\\DaymetFlag", ROOTDIR);
		fp = fopen(site_file, "r");
		if ( fp == NULL )
		{
			//printf("File %s not found", site_file);
			//getch();
			//exit(0);
			DDaymetFlag = 0;

			char sitefile[80];
			FILE *fpp;
		
			sprintf(sitefile, "%s\\Result\\Inter\\DaymetFlag", ROOTDIR);
			fpp = fopen(site_file, "w");
			if ( fpp == NULL )
			{
				printf("Can not create file %s", sitefile);
				getch();
				exit(0);
			}
 
			fprintf(fpp, "%d", 0);
			fclose(fpp);
		}
		else
		{ 
			fscanf(fp, "%d", &DDaymetFlag);
			fclose(fp);
		}
*/
		CreateInputFiles(DDaymetFlag, 0, "None", 1);//Normal start		
	}	

	char SYF[200];
	FILE* sni;
	sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
	sni=sopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 1);//1
	fclose(sni);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphexView printing


/*void CGraphexView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnEndPrinting(pDC, pInfo);
}

BOOL CGraphexView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	// default preparation
	return DoPreparePrinting(pInfo);
	
	//return CView::OnPreparePrinting(pInfo);
}

void CGraphexView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnBeginPrinting(pDC, pInfo);
}

void CGraphexView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pInfo) m_rcPrintRect=pInfo->m_rectDraw;


	CView::OnPrint(pDC, pInfo);
}
*/

void CGraphexView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CString Sti;
	//Sti.Format("W=%d,H=%d",cx,cy);
#ifdef MANURE
	Sti.Format("Manure-DNDC 3.0");
#else
	Sti.Format("DNDC 9.5 v.CAN");
#endif
	GetDocument()->SetTitle(Sti);
	CMainFrame *pMainF=(CMainFrame *)GetParentFrame();
	if  (pMainF->m_DatabaseBar.GetSafeHwnd()) 
	{
		int bt,by;
		CRect lpRect,ListR;
		pMainF->m_DatabaseBar.GetClientRect(&lpRect);
		pMainF->m_DatabaseBar.SetWindowPos(&wndNoTopMost,lpRect.left,lpRect.top,lpRect.right/*cx*/,cy,SWP_NOMOVE+SWP_NOZORDER+SWP_SHOWWINDOW);
		bt = lpRect.right;

/*		CListCtrl *pList=(CListCtrl *)pMainF->m_DatabaseBar.GetDlgItem(IDC_PROPERTYLIST);
		pList->GetClientRect(&ListR);*/
		bt=ListR.right;//bt-115;
		if (bt<=100) bt=100;
		by=ListR.bottom;
		if (by<=100) by=100;
		
		if (m_EditDatabase=="OFF" && pMainF->m_DatabaseBar) 
			pMainF->ShowControlBar(&pMainF->m_DatabaseBar,FALSE,FALSE);
	}
}


void CGraphexView::OnViewModifycolorscale() 
{
/*	CIndexCScale CScale;

	if (CScale.DoModal()==IDOK)
	{
	}
*/	
}


//#include "CropDBase.h"
void CGraphexView::OnCropPropertyDB() 
{
/*	CCropDBase CDBase;
	if (CDBase.DoModal()==IDOK)
	{
	}
	*/
}


/*
int CGraphexView::ifworking(CString txt)
{
	if (txt=="Work") return 0;
	MessageBox("The DNDC Version is only for Site Model. Other modules can be used only after allowed.","Sorry:",NULL);
	return -1;
}
*/

/*
void CGraphexView::OnScreenCLEAN() 
{
	// TODO: Add your command handler code here
	int i;
	i=0;
	CGraphexDoc* pDoc = GetDocument();
	//pDoc->ClearAct();
	//pDoc->AddLine(0, 0, MapWidth,MapHigh,"SOLID",CDP.BackColor);			
}
*/


void CGraphexView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	ShowSiteFlag = 1;
	/*CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	ShowMapValue(pDoc,point);

	if (nFlags==MK_RBUTTON)
	{
		//ShowMapValue(0,point);
		return;
	}*/
	
	CView::OnRButtonDown(nFlags, point);
}


void CGraphexView::OnInputRegion() 
{
	// TODO: Add your command handler code here
	/*struct dirent *d;
    DIR *dir;
    char buf[256];

    dir = opendir("testdir");

	while(d = readdir(dir))
    {
                printf("%s\n",d->d_name);
                sprintf(buf, "%s/%s", "testdir", d->d_name);
                remove(buf);
    }*/
    //return 0;

/*	//===================================================
	string dir = string(".");
	vector<string> files = vector<string>();

	getdir(dir,files);

	for (unsigned int i = 0;i < files.size();i++) {
	cout << files[i] << endl;
	}
	//===================================================
*/

/*
	WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((LPCWSTR) "*", &findFileData);
 
    if(hFind  == INVALID_HANDLE_VALUE) {
        std::cout <<"No files found." <<std::endl;
    } else {
        std::cout <<"Files found." <<std::endl;
    }
 
    char a;
    std::cin>> a;
*/

	CString DM;
	FILE *dm;
	DM.Format("%s\\DroughtMode", INTER);
	dm=fopen(DM, "w");
	fprintf(dm, "%d", 0);
	fclose(dm);

	RegionInput dlg;
	if(dlg.DoModal()==IDOK)
	{
		//UpdateData(FALSE);
	}
}

void CGraphexView::OnMapping() 
{
	// TODO: Add your command handler code here
	
	
}


void CGraphexView::OnSelectState() 
{
	// TODO: Add your command handler code here
	//USAstate dlg;
	//UncertaintyInput dlg;
	MonteCarloRegionSelect dlg;
	if(dlg.DoModal()==IDOK)
	{
		OnRunUncertainty(); 
		OnRunMonteCarlo();
	}
	
}

void CGraphexView::OnSelectCounty() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	char Fregion[120], CountryName[200][250], Root1[200], Root2[200],RootName2[200],WholeName[300];
	int jd;

	FILE *region;
	sprintf(Fregion, "%s\\PassName", INTER);
	region = fopen(Fregion, "r");
	fscanf(region, "%d %d", &jd, &stateID);
	fscanf(region, "%s", CountryName);
	fscanf(region, "%s", Root1);
	fscanf(region, "%s", Root2);
	fscanf(region, "%s", WholeName);
	fclose (region);	

	draw_a_state(pDoc, stateID);

	//DNDCSys.Mode = 2;
	
}

/*
void CGraphexView::OnSelectCrop() 
{
	// TODO: Add your command handler code here
	SelectCrop ww;
	if(ww.DoModal()==IDOK)
	{
		
	}
	
}*/

void CGraphexView::OnMonteCarlo() 
{
	// TODO: Add your command handler code here
	MonteCarlo ww;
	if(ww.DoModal()==IDOK)
	{
		
	}
	
}



void CGraphexView::OnDrawFlux() 
{
	// TODO: Add your command handler code here
//	GasFlux ww;
//	if(ww.DoModal()==IDOK)
//	{
		
//	}
	
}

void CGraphexView::OnRegion() 
{
	// TODO: Add your command handler code here
	//USAstate ww;
	//if(ww.DoModal()==IDOK)
	{
		
	}
}

void CGraphexView::OnDrawMap() 
{
	// TODO: Add your command handler code here

}

void CGraphexView::OnMCresult() 
{
	// TODO: Add your command handler code here
	//char StateName[300], CountyName[300];
	int i;
	float ha, dSOC, CH4, N2O, NO, N2, NH3, N_leaching;
	int ResultYr=1;
	char WW[600];
	
	CString IDfile, rcd, countyID;
	FILE *fid;
	FILE* RCD;
		
	IDfile.Format("%s\\Result\\inter\\SelectSite.txt", ROOTDIR);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{
			CString mess;
			mess.Format("Can not open %s.", IDfile);
			AfxMessageBox(mess);
			exit(0);
	}
	fscanf(fid, "%s %s %s", StateName, CountyName, &countyID);
	fscanf(fid, "%d  %f", &cropID, &ha);
	//fscanf(fid, "%s %s ", IndexFileName, ClimFileName);
	//fscanf(fid, "%s %s ", SoilFileName, CropFileName);
	//fscanf(fid, "%d", &year);
		
	fclose(fid);	
	
	for(i=0; i<300; i++) 
	{
		Fc[i] = 0;
		Cc[i] = 0.0;
	}

	rcd.Format("%s\\Result\\record\\Uncertainty_%s", ROOTDIR, countyID);
	RCD = fopen(rcd, "r");
	if(RCD==NULL) 
	{
		CString mess;
		mess.Format("Can not open file %s", rcd);
		AfxMessageBox(mess);
		exit(0);
	}
	fgets(WW, 300, RCD);
	fgets(WW, 300, RCD);
	fgets(WW, 300, RCD);

	int FLUX = 3;
	for(;;)
	{
		if(fscanf(RCD, "%d %f %f %f %f %f %f %f", 
			&i, &dSOC, &CH4, &N2O, &NO, &N2, &NH3, &N_leaching)!=8) break;
		else
		{
			if(FLUX==1) find_sector(FLUX, dSOC);
			if(FLUX==2) find_sector(FLUX, CH4);
			if(FLUX==3) find_sector(FLUX, N2O);
		}		
	}
	fclose(RCD);

	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC dc(pDC);
	
	DrawFrequency(pDoc);
/*			DrawNbalance(pDoc);
			GWP(pDoc);
*/
	
}

void CGraphexView::find_sector(int k, float dSOC)
{
	int dd, span;
	aa=100;

	if(k==1)
	{
		span = 3000.0;
		dd = (int)((dSOC+span)/aa);
		Fc[dd]++;
		Cc[dd] = (float)dd * aa - span;
		MaxGG = (int)(2 * span / aa);
	}
	else if(k==3)
	{
		span = 3000.0;
		dd = (int)((dSOC+span)/aa);
		Fc[dd]++;
		Cc[dd] = (float)dd * aa - span;
		MaxGG = (int)(2 * span / aa);
	}
	else {}

}

void CGraphexView::DrawFrequency(CGraphexDoc *pDoc)
{
	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (30,10); 
	art.SetViewportExt(1400, 1450);
	
	CBrush Brush1(RGB(220,220,220));
	art.FillRect(rectClient, &Brush1);
	Brush1.DeleteObject();

	int grid = (int)(900/MaxGG);
	int ii = MaxGG, i;

	int x0, x1, y0, y1;
	CString w;

	x0 = 50;
	y0 = 500;

	for(i=0; i<ii; i++)
	{
		x1 = x0 + grid * i;		
		y1 = -(Fc[i]+1);

		art.FillSolidRect(x1, y0, grid-2, y1, RGB(120,120,0));
		
		if(i%5 == 0)
		{
			art.FillSolidRect(x1, y0+2, 3, 10, RGB(120,120,0));		
			w.Format("%.1f", (6.0/MaxGG)*i - 3.0);
			art.TextOut(x1, 520, w);
		}
	}
	w.Format("Annual SOC change, ton C/ha/yr");
	art.TextOut(400, 560, w);


	CFont hNewFont;
		TEXTMETRIC tm;
		CString dndc;
		
	//dndc74 zzz;

	//dndc.Format("Monte Carlo test: Annual soil C change for %s cropland in %s, %s", zzz.CropSystem[cropID], CountyName, StateName);

	hNewFont.CreateFont(45,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetTextColor(RGB(255,255,255));
		//pDC->SetBkColor(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextAlign(TA_LEFT);
		art.TextOut(50, 40, dndc);
		
		hNewFont.DeleteObject();

}

void CGraphexView::OnExit() 
{
	// TODO: Add your command handler code here
	exit(0);
	
}

void CGraphexView::OnWizardSelectCounty() 
{
	// TODO: Add your command handler code here
	//select a county
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION canves = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( canves );
	CClientDC art(pDC);
	art.SetBkMode(TRANSPARENT);

	CString w_clim0;
	//art.FillSolidRect(600, 450, 200, 100, RGB(255,255,255));
	w_clim0.Format ("Now, you can select a county for simulation");
	art.SetTextColor(RGB(0,0,100));
	art.TextOut(370, 60, w_clim0);
	
	SelectFlag = 1;

	
}


void CGraphexView::OnMapCrops() 
{
	// TODO: Add your command handler code here
	//draw crop map
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 0;

	draw_LandUse(pDoc, stateID, cropID);
}

void CGraphexView::OnMapCorn() 
{
	// TODO: Add your command handler code here
	//draw crop map
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 1;

	draw_LandUse(pDoc, stateID, cropID);
}

void CGraphexView::OnWWheat() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 2;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnSWheat() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 3;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnSunflower() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 17;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnSugarcane() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 15;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnSoybean() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 9;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnSorghum() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 7;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnBarley() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 5;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnBeet() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 11;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnCotton() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID =8;

	draw_LandUse(pDoc, stateID, cropID);
	//SelectFlag = 1;
}

void CGraphexView::OnLegumeHay() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 18;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnNonlegumehay() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 19;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnOats() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 4;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnPeanut() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 12;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnPineapple() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 14;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnPotato() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 10;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnRice() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 6;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnTobacco() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 16;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnVegetable() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int stateID = 0;
	int cropID = 13;

	draw_LandUse(pDoc, stateID, cropID);
	
}

void CGraphexView::OnWizardSelectCrop() 
{
	// TODO: Add your command handler code here
	//select a cropping system
	/*SelectFlag = 1;
	CountyCrops ww;

	if(ww.DoModal()==IDOK)
	{
		
	}*/
}

void CGraphexView::OnResultReview() 
{
	// TODO: Add your command handler code here
	WizardResult ww;
	if(ww.DoModal()==IDOK)
	{


	}

}

void CGraphexView::OnResultRecord() 
{
	// TODO: Add your command handler code here
	//save simulated results
//	CountySave ww;
//	if(ww.DoModal()==IDOK)
//	{
//	}

}

void CGraphexView::OnUncertainty() 
{
	// TODO: Add your command handler code here
	//Monte Carlo analysis
	WizardUncertainty ww;
	if(ww.DoModal()==IDOK)
	{
	}

	
}

void CGraphexView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
#ifdef WIZARD
	if(ShowSiteFlag==1)
	{
	int i, ScaleID;
	
	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC dc(pDC);

	//CRect rcEllipse(5,50, 230,180);
		//art.Ellipse(rcEllipse);
	//dc.Rectangle(rcEllipse);

	ScaleID = 0;
	Find_Grid(point.x, point.y, ScaleID, 1);
	//stateID = (int)((float)County_ID/1000.0);

	if(WizardCountyID==0)
	{
		//AfxMessageBox("Please stay at home!");
		return;
	}
	else
	{	
		//County_data(WizardCountyID);
		draw_a_county(pDoc, WizardCountyID);

		County_data(WizardCountyID, 1); 
	}

	SelectFlag = 1;

	SitePage1 zz;
	zz.Revisit = 0;

	WizardCrops ww;

	if(ww.DoModal()==IDOK)
	{
		ShowSiteFlag = 0;
	}
	else
		ShowSiteFlag = 1;
	}
#endif	
	
	CView::OnLButtonDown(nFlags, point);
}




void CGraphexView::OnRunUncertainty() 
{
	// TODO: Add your command handler code here
	MonteCarlo ww;
	if(ww.DoModal()==IDOK)
	{
		RunMonteCarlo(0);
	}
	
}

void CGraphexView::OnMsf() 
{
	// TODO: Add your command handler code here
	MonteCarlo ww;
	if(ww.DoModal()==IDOK)
	{
		RunMonteCarlo(1);
	}
	
}

void CGraphexView::ShowMapValue(CGraphexDoc *pDoc, CPoint point)
{
	
}



void ReadDatafromFile_NG(char *fname)
{

}

void CGraphexView::OnRegionInput() 
{
	// TODO: Add your command handler code here

	RegionInput pp;

	if(pp.DoModal()==IDOK)
	{
		
	}

}

void CGraphexView::OnRegionRun() 
{
	// TODO: Add your command handler code here
	OnRunRegion();
}

void CGraphexView::OnESreview() 
{
	// TODO: Add your command handler code here
	NewCrop vvv;

	if(vvv.DoModal()==IDOK)
	{

	}
}



int JulDay(int month, int day)
{
    int i, JDay;
	int   Mday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if (month<1 ||month>12 || day<1 ||day>31) return -1;

    JDay = 0;
    for (i = 1; i< month; i++)
	{
        JDay += Mday[i];
	}
    JDay += day;
	return JDay;
}


void CGraphexView::OnRegionMap() 
{
	// TODO: Add your command handler code here
	SelectShapeMap vvv;

	if(vvv.DoModal()==IDOK)
	{
		OnMapCounty();
	}		
}

void CGraphexView::OnCreateCrop() 
{
	// TODO: Add your command handler code here
	NewCrop vvv;

	if(vvv.DoModal()==IDOK)
	{

	}
}

void CGraphexView::OnExtractData() 
{
	// TODO: Add your command handler code here
	ExtractData vvv;

	if(vvv.DoModal()==IDOK)
	{

	}
}

/*void draw_cover(CGraphexDoc *pDoc)
{
	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);

	int c1=200,c2=250,c3=220;
		CFont hNewFont;
		TEXTMETRIC tm;
		CString dndc;
		dndc.Format("%s", "Welcome to NZ-DNDC");

		hNewFont.CreateFont(55,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);

		art.GetTextMetrics(&tm);

		//art.SetTextColor(RGB(0,0,50));		
		//art.TextOut(90, 49, dndc);
		art.SetTextAlign(TA_CENTER);
		art.SetTextColor(RGB(c1,c2,c3));		
		art.TextOut(510, 140, dndc);

		hNewFont.DeleteObject();

		dndc.Format("%s", "Institute for the Study of Earth, Oceans, and Space"); 
		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextColor(RGB(c1,c2,c3));	
		art.SetTextAlign(TA_CENTER);
		art.TextOut(510, 350, dndc);		
		hNewFont.DeleteObject();

		dndc.Format("%s", "University of New Hampshire"); 
		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextColor(RGB(c1,c2,c3));	
		art.SetTextAlign(TA_CENTER);
		art.TextOut(510, 380, dndc);		
		hNewFont.DeleteObject();

		dndc.Format("%s", "Landcare Research / Manaaki Whenua"); 
		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextColor(RGB(c1,c2,c3));	
		art.SetTextAlign(TA_CENTER);
		art.TextOut(510, 400, dndc);		
		hNewFont.DeleteObject();

		dndc.Format("%s", "New Zealand"); 
		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextColor(RGB(c1,c2,c3));	
		art.SetTextAlign(TA_CENTER);
		art.TextOut(510, 430, dndc);		
		hNewFont.DeleteObject();

		dndc.Format("%s", "Institute for the Study of Earth, Oceans, and Space"); 
		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextColor(RGB(c1,c2,c3));	
		art.SetTextAlign(TA_CENTER);
		art.TextOut(510, 500, dndc);		
		hNewFont.DeleteObject();

		dndc.Format("%s", "University of New Hampshire, USA"); 
		hNewFont.CreateFont(30,0,0,0,FW_BOLD,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");
		art.SelectObject(&hNewFont);
		art.SetBkMode(TRANSPARENT);
		art.GetTextMetrics(&tm);
		art.SetTextColor(RGB(c1,c2,c3));	
		art.SetTextAlign(TA_CENTER);
		art.TextOut(510, 530, dndc);		
		hNewFont.DeleteObject();


}
*/
/*void CGraphexView::OnWizardMSF() 
{
	// TODO: Add your control notification handler code here
	RunMonteCarlo(1);
}*/

void CGraphexView::OnWizardMonteCarlo() 
{
	// TODO: Add your command handler code here
	WizardUncertainty ww;
	int method;

	if(ww.DoModal()==IDOK)
	{
		method = 0;
	}
	else 
	{
		method = 1;
	}

	//RunWizardMonteCarlo(method);
	RunMonteCarlo(method);

	//MonteCarloChart(method);
	
}

void CGraphexView::OnSiteResult() 
{
	// TODO: Add your command handler code here
	OnResultReview();
}

void CGraphexView::OnGlobeMap() 
{
	GlobeMap wwww;

	if(wwww.DoModal()==IDOK)
	{

	}
}

void CGraphexView::OnGlobeData() 
{
	// TODO: Add your command handler code here
	GlobeData wwww;

	if(wwww.DoModal()==IDOK)
	{

	}
}

void CGraphexView::OnMapCounty() 
{
	char ShapeFileName[200][200], m_Watershed[200][120], m_MapPath[200][120];
	CString m_Layer1, m_Layer2, m_Layer3;//m_MapPath,
	int WL, i, L1, LayerNumber;

#ifdef CHINA
	LayerNumber = 1;
	sprintf(m_Watershed[1], "China");
	sprintf(m_MapPath[1], "%s\\Database\\China\\lib_map\\", ROOTDIR);
#else 
	CString SF;
	FILE* sf;
	SF.Format("%s\\Result\\Inter\\MapFile.txt", ROOTDIR);
	sf=fopen(SF, "r");
	if(sf==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", SF);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(sf, "%d", &LayerNumber);
	for(i=1; i<=LayerNumber; i++)
	{
		fscanf(sf, "%s", ShapeFileName[i]);
	}
	fclose(sf);

	for(int j=1; j<=LayerNumber; j++)
	{
		WL=strlen(ShapeFileName[j]);

		for(i=WL; i>=0; i--)
		{
			if(ShapeFileName[j][i]==92) 
			{
				L1=i+1;
				break;
			}
		}

		Glean_String(ShapeFileName[j], L1, WL-5, m_Watershed[j]);
		Glean_String(ShapeFileName[j], 0, L1-2, m_MapPath[j]);
	}
#endif
	
	CString WS;
	FILE *ws;
	WS.Format("%s\\Result\\Inter\\MapSelect.txt", ROOTDIR);
	ws=fopen(WS, "w");
	if(ws==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", WS);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(ws, "%s  %s", m_Watershed[1], "2000");
	fclose(ws);
	
	CSelectRegionDlg dlg;
	
	m_Layer1.Format("%s", m_Watershed[1]); 
	dlg.SetMapPath(m_MapPath[1]);
	dlg.AddLayer(m_Layer1, 1, RGB(30,90,200), true, RGB(220,240,255));//color define: line thickness, line color, background O/I, background color

	if(LayerNumber==2)
	{
		m_Layer2.Format("%s", m_Watershed[2]); 
		dlg.SetMapPath(m_MapPath[2]);
		dlg.AddLayer(m_Layer2, 1, RGB(20,20,100), false, RGB(25,25,25));
	}

	dlg.SetLayerSelected(m_Layer1, "MAIZE", "DNDC_CELL", "GLOBAL_ID", "COUNTRY_CO");//Globe

	dlg.SetLayerSelected(m_Layer2, "COUNTRY_NA", "CH4_K", "GLOBAL_ID", "COUNTRY_CO");//CA rice

	dlg.m_movelabel = FALSE;

/*	//
	// Add data to the map.
	//
	//AddLayer(dlg.m_map, TEXT("..\\data\\usa\\states.shp"), RGB(255,0,0));
	//AddLayer(dlg.m_map, TEXT("..\\data\\usa\\counties.shp"), RGB(255,0,0));
	//AddLayer(m_map, TEXT("..\\data\\usa\\ushigh.shp"), RGB(255,0,0));
	dlg.AddLayer(m_Layer1, 1, RGB(255,100,100), true, RGB(200,200,255));

	//
	// Set up county renderer
	//

	//CMoLayers	layers(dlg.m_map.GetLayers());
	CMoMapLayer	counties(layers.Item(COleVariant(TEXT(m_Layer1))));

	CMoClassBreaksRenderer cbRenderer;	// Create from scratch
	cbRenderer.CreateDispatch(TEXT("MapObjects2.ClassBreaksRenderer"));
	cbRenderer.SetField(TEXT("LULCSTRING"));

	// calculate breaks away from the mean in both directions,
	// but only add those breaks that are within the range of values
	CMoRecordset  recs(counties.GetRecords());
	CMoStatistics stats(recs.CalculateStatistics(TEXT("LULCSTRING")));
	double breakVal = stats.GetMean() - (stats.GetStdDev() * 3.0);
	double min = stats.GetMin();
	double max = stats.GetMax();

	for (int i = 0; i < 7; i++)
	{
		if (min <= breakVal &&  breakVal <= max)
		{
			int breakCount = cbRenderer.GetBreakCount();
			cbRenderer.SetBreakCount(breakCount + 1);
			cbRenderer.SetBreak(breakCount, breakVal);
		}
		breakVal = breakVal + stats.GetStdDev();
	}

	cbRenderer.RampColors(RGB(0,255,0), RGB(255,0,0));
	counties.SetRenderer(cbRenderer);
*/

	

	if (dlg.DoModal() == IDOK)
	{
//		AfxMessageBox(dlg.m_selectedLabel + " " + dlg.m_selectedId);
		//stateID = dlg.WizardCountyID / 1000;
		//WizardCountyID = dlg.WizardCountyID;
//		m_SCname = dlg.m_SCname;

		SelectFlag = 1;

		SitePage1 zz;
		zz.Revisit = 0;

		ShowSiteFlag = 0;
	}
}

void CGraphexView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

}

void CGraphexView::Onconvert() 
{
	// TODO: Add your command handler code here
	

}

void CGraphexView::OnMapView() 
{
	// TODO: Add your control notification handler code here
	CSelectRegionDlg dlg;

	CString m_MapPath, m_Layer1, m_Layer2, m_Layer3;
	CString RegionName="Shangrila";

	//for Shangrila
	m_MapPath.Format("%s\\Database\\%s\\lib_Map", ROOTDIR, RegionName); 
	m_Layer1.Format("%s", RegionName); 

	dlg.SetMapPath(m_MapPath);
	dlg.AddLayer(m_Layer1, 1, RGB(10,100,200), true, RGB(20,220,255));
	dlg.SetLayerSelected(m_Layer1, "PYNAME", "CNTY_CODE", "Y_COORD", "X_COORD");
	//SetLayerSelected(CString layer, CString labelfield, CString idfield, CString latitude, CString longitude)
	
	dlg.m_movelabel = FALSE;

	if (dlg.DoModal() == IDOK)
	{
	}
}


void CGraphexView::OnBatch() 
{
	// TODO: Add your command handler code here
	CGraphexDoc* pDoc = GetDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	CString DIR0;
	DIR0.Format("%s", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inputs", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inter", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inter\\Management_1", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inter\\RegionFiles", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Record", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Record\\Region", ROOTDIR);
	mkdir(DIR0);
	DIR0.Format("%s\\Result\\Record\\Site", ROOTDIR);
	mkdir(DIR0);
	
	DIR0.Format("%s\\Result\\Record\\MonteCarlo", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Record\\Batch", ROOTDIR);
	mkdir(DIR0);

	ScreenMonitor qq;
	int Monitor, DayRecord;
	if(qq.DoModal()==IDOK) Monitor=0;
	else Monitor=1;

	BatchRun ww;
	char BatchFileName[400];

	if(ww.DoModal()==IDOK)
	{
		CString Fregion;
		FILE *region;
		Fregion.Format("%s\\Result\\Inter\\BatchFile.txt", ROOTDIR);
		region = fopen(Fregion, "r");
		if (region==NULL)
		{
			char err[120];
			sprintf(err, "Can not open %s", Fregion);
			AfxMessageBox(err);
			exit(0); 
		}
		fscanf(region, "%s %d", BatchFileName, &DayRecord);		
		fclose (region);

		int FileNumber;
		
		Fregion.Format("%s", BatchFileName);
		region = fopen(Fregion, "r");
		if (region==NULL)
		{
			char err[120];
			sprintf(err, "Can not open %s", Fregion);
			AfxMessageBox(err);
			exit(0); 
		}
		fscanf(region, "%d", &FileNumber);

		SitePage1 ww;

		CString DB, note;
		FILE *db, *fp;
		char SiteName[400];
		DB.Format("%s\\Result\\inter\\OpenFile.txt", ROOTDIR);
		db=fopen(DB, "w");
		fprintf(db, "%d", 1);
		fclose(db);

		for (int i=1; i<=FileNumber; i++)
		{
			if(Monitor==1)
			{
				int GoFar = (int)(850.0*(float)i/(float)FileNumber);
				art.FillSolidRect(100, 150, 850, 21, RGB(230,220,180)); //background
				art.FillSolidRect(100, 150, GoFar, 20, RGB(155,160,64));
			}

			fscanf(region, "%s", DndFileName);	
			
			if ((fp=fopen(DndFileName,"r"))==NULL) 
			{
				note.Format("Can not open %s", DndFileName);
				AfxMessageBox(note);
				return;
			}

			fscanf(fp,"%s",note);
			fscanf(fp,"%s",note);//"--------------------"
			fscanf(fp,"%s %s %s",note,note,SiteName);
			fclose(fp);

			DIR0.Format("%s\\Result\\Record\\Batch\\Case%d-%s", ROOTDIR, i, SiteName);
			mkdir(DIR0);

			char BatchPass[300];
			sprintf(BatchPass, "%s", DIR0);

			DIR0.Format("%s\\Result\\Record\\Batch\\Case%d-%s\\CropSystem", ROOTDIR, i, SiteName);
			mkdir(DIR0);
			DIR0.Format("%s\\Result\\Record\\Batch\\Case%d-%s\\LivestockSystem", ROOTDIR, i, SiteName);
			mkdir(DIR0);

			CString BR;
			BR.Format("%s\\Result\\Inter\\BatchRecord", ROOTDIR);
			if((fp=fopen(BR,"w"))==NULL) 
			{
				note.Format("Can not create %s", BR);
				AfxMessageBox(note);
				return;
			}
			fprintf(fp,"%s",BatchPass);
			fclose(fp);

			ReadInputDatafromDND(DndFileName, 0);
			
			ReadSoilFeature("UnDefault");
			
			CreateInputFiles(0, 0, "r_Country", DayRecord);//Batch run

			OnRunSite(1, Monitor, i, BatchPass);// Option 1: batch runs

			
		}
		fclose (region);

		AfxMessageBox("Good. The Batch run is accomplished");
	}
	
}

void CGraphexView::OnSiteParameter() 
{
	// TODO: Add your command handler code here
	//float d[20][9];
	float d[20][51];
	int n, m, i, j, k, m_SampleSize, item[55];
	float value[55];
	int CutInterval = 50, MC_StartDay, MC_EndDay;
	
	MonteCarloParameters ww;
	if(ww.DoModal()==IDOK)
	{
		CString SMC;
		FILE *smc;
		SMC.Format("%s\\Result\\Inter\\SiteMonteCarlo", ROOTDIR);
		smc=fopen(SMC, "r");
		if(smc==NULL)
		{
			CString note;
			note.Format("Cannot find file %s", SMC);
			AfxMessageBox(note);
			exit(0);
		}
		fscanf(smc, "%d %d", &k, &m_SampleSize);
		for(i=1; i<=k; i++)
			fscanf(smc, "%d %f", &item[i], &value[i]);
		fscanf(smc, "%d %d", &MC_StartDay, &MC_EndDay);
		fclose(smc);

		for(n=1; n<=k; n++)
		{
			float dd = 2.0*value[n] / (float)(CutInterval-1);
			//float dd = 2.0*value[n] / 49.0;
	
			for(m=1;m<=CutInterval;m++)
			//for(m=1;m<=50;m++)
			{
				d[n][m] = -value[n] + (m-1)*dd;	
			}
		}

		for(j=1; j<=m_SampleSize; j++)
		{
			long t;
			long int xyz, r[21];
			int RN[21], w;
			float fValue[21];
	
			xyz = (long int)time(NULL);

			for(w=1; w<=k; w++)
			{
				r[w] = rand();
				RN[w] = (r[w]+xyz)%CutInterval+1;	
				//RN[w] = (r[w]+xyz)%50+1;
				fValue[w] = d[w][RN[w]];
			}			
				
			char BatchPass[300]="NULL";
			CString note;
			FILE *mc;
			note.Format("%s\\Result\\Inter\\SiteMCinput", ROOTDIR);
			mc=fopen(note, "w");
			if ( mc == NULL )
			{
				CString mess;
				mess.Format("Can not create %s.", note);
				AfxMessageBox(mess);
				exit(0);
			}

			fprintf(mc, "%d\n", k); 
			for(w=1; w<=k; w++)
			{
				fprintf(mc, "%d %f\n", item[w], fValue[w]); 
			}	
			fprintf(mc, "%d %d\n", MC_StartDay, MC_EndDay); 
			fclose(mc);

			OnRunSite(100+j, 0, 0, BatchPass);// Option 2: site-Monte Carlo runs
		}
	}
}

void CGraphexView::OnMapLayer() 
{
	// TODO: Add your command handler code here
		CString DIR0;
	DIR0.Format("%s", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inputs", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inter", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inter\\Management_1", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Inter\\RegionFiles", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Record", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Record\\Region", ROOTDIR);
	mkdir(DIR0);
	DIR0.Format("%s\\Result\\Record\\Site", ROOTDIR);
	mkdir(DIR0);
	//DIR0.Format("%s\\Record\\RegionSummary", OUTPUT);
	//mkdir(DIR0);
	//DIR0.Format("%s\\Record\\SiteSummary", OUTPUT);
	//mkdir(DIR0);
	DIR0.Format("%s\\Result\\Record\\MonteCarlo", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s\\Result\\Record\\Batch", ROOTDIR);
	mkdir(DIR0);

	MapLayer ww;
	char LayerFileName[400];

	if(ww.DoModal()==IDOK)
	{
		CString Fregion;
		FILE *region;
		Fregion.Format("%s\\Result\\Inter\\MapLayerList.txt", ROOTDIR);
		region = fopen(Fregion, "r");
		if (region==NULL)
		{
			char err[120];
			sprintf(err, "Can not open %s", Fregion);
			AfxMessageBox(err);
			exit(0); 
		}
		fscanf(region, "%s", LayerFileName);		
		fclose (region);

		int CellNumber, CropNumber, SimulateYears, i;
		char RegionName[400], F1[100], F2[100], F3[100], F4[100], F5[100], F6[100], F7[100], F8[100];
		char Crop[100][100];
		
		Fregion.Format("%s", LayerFileName);
		region = fopen(Fregion, "r");
		if (region==NULL)
		{
			char err[120];
			sprintf(err, "Can not open %s", Fregion);
			AfxMessageBox(err);
			exit(0); 
		}
		fscanf(region, "%d %d %s", &CellNumber, &SimulateYears, RegionName);

		fscanf(region, "%s %s %s %s %s", F1, F2, F3, F4, F5);
		fscanf(region, "%s %s %s", F6, F7, F8);
		fscanf(region, "%d", &CropNumber);
		for(i=1; i<=CropNumber; i++)
		{
			fscanf(region, "%s",  Crop[i]);
		}
		fclose(region);
		
		FILE *f1, *f2, *f3, *f4;
		f1=fopen(F1, "r");
		if (f1==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F1);
				AfxMessageBox(note);
				return;
			}

		f2=fopen(F2, "r");
		if (f2==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F2);
				AfxMessageBox(note);
				return;
			}

		FILE *Layer1;

		CString XZ;
		XZ.Format("%s\\Result\\Inter\\Layer1", ROOTDIR);
		Layer1=fopen(XZ, "w");
		if (Layer1==NULL) 
			{
				CString note;
				note.Format("Can not creaye Layer1");
				AfxMessageBox(note);
				return;
			}

		char CellID[100];
		float latitude;
		for(i=1; i<=CellNumber; i++)
		{			
			fscanf(f1, "%s", CellID);
			fscanf(f2, "%f", &latitude);
			fprintf(Layer1, "%d  %s  %s  -100  %f\n", i, RegionName, CellID, latitude);
		}
		
		fclose(f1);
		fclose(f2);
		fclose(Layer1);

		/////////////////////////////////

		f1=fopen(F3, "r");
		if (f1==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F3);
				AfxMessageBox(note);
				return;
			}

		f2=fopen(F4, "r");
		if (f2==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F4);
				AfxMessageBox(note);
				return;
			}

		//FILE *Layer1;
		XZ.Format("%s\\Result\\Inter\\Layer2", ROOTDIR);
		Layer1=fopen(XZ, "w");
		if (Layer1==NULL) 
			{
				CString note;
				note.Format("Can not creaye Layer2");
				AfxMessageBox(note);
				return;
			}

		char ClimID[200];
		float AtmoN;
		for(i=1; i<=CellNumber; i++)
		{	
			fscanf(f1, "%s", ClimID);
			fscanf(f2, "%f", &AtmoN);
			fprintf(Layer1, "%d  %s  %f\n", i, ClimID, AtmoN);
		}
		
		fclose(f1);
		fclose(f2);
		fclose(Layer1);

		///////////////////////////
		f1=fopen(F5, "r");
		if (f1==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F5);
				AfxMessageBox(note);
				return;
			}

		f2=fopen(F6, "r");
		if (f2==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F6);
				AfxMessageBox(note);
				return;
			}

		f4=fopen(F8, "r");
		if (f4==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F8);
				AfxMessageBox(note);
				return;
			}

		f3=fopen(F7, "r");
		if (f3==NULL) 
			{
				CString note;
				note.Format("Can not open %s", F7);
				AfxMessageBox(note);
				return;
			}

		//FILE *Layer1;
		XZ.Format("%s\\Result\\Inter\\Layer3", ROOTDIR);
		Layer1=fopen(XZ, "w");
		if (Layer1==NULL) 
			{
				CString note;
				note.Format("Can not creaye Layer3");
				AfxMessageBox(note);
				return;
			}

		
		float SOC, clay, BD, pH;
		fprintf(Layer1, "Soil\n");
		fprintf(Layer1, "ID, SOC, clay, BD, pH\n");
		for(i=1; i<=CellNumber; i++)
		{			
			
			fscanf(f1, "%f", &SOC);
			fscanf(f2, "%f", &clay);
			fscanf(f3, "%f", &BD);
			fscanf(f4, "%f", &pH);
			fprintf(Layer1, "%d  %f  %f  %f  %f  %f  %f  %f  %f\n", i, SOC, SOC, clay, clay, BD, BD, pH, pH);	
		}
		
		fclose(f1);
		fclose(f2);
		fclose(f3);
		fclose(f4);
		fclose(Layer1);

		/////////////////////////////////
		int CropID[50];

		for(i=1; i<=CropNumber; i++)
		{
			f1=fopen(Crop[i], "r");
			if (f1==NULL) 
			{
				CString note;
				note.Format("Can not open %s", Crop[i]);
				AfxMessageBox(note);
				return;
			}

			fscanf(f1, "%d", &CropID[i]);
			//for(int j=1; j<=
			//fscanf(f1, "%f", &CropHa[i]);

		}

	}

	
}

void CGraphexView::OnConvertData() 
{
	// TODO: Add your command handler code here
	//Compile dndc_3.txt (soil data file)
	int ID1, ID2, ID3, ID4, ID5, ID6, ID7, ID8;
	float clay1, clay2, soc1, soc2, density1, density2, ph1, ph2;
	CString DB1, DB2, DB3, DB4, DB5, DB6, DB7, DB8, DT, note;
	FILE *db1, *db2, *db3, *db4, *db5, *db6, *db7, *db8, *dt;
	
	DB1.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeSOCMax_30min.map", ROOTDIR);
	db1=fopen(DB1, "r");
	if(db1==NULL) 
	{
		note.Format("Can not open %s", DB1);
		AfxMessageBox(note);
		return;
	}

	DB2.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeSOCMin_30min.map", ROOTDIR);
	db2=fopen(DB2, "r");
	if(db2==NULL) 
	{
		note.Format("Can not open %s", DB2);
		AfxMessageBox(note);
		return;
	}	

	DB3.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeClayMax_30min.map", ROOTDIR);
	db3=fopen(DB3, "r");
	if(db3==NULL) 
	{
		note.Format("Can not open %s", DB3);
		AfxMessageBox(note);
		return;
	}

	DB4.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeClayMin_30min.map", ROOTDIR);
	db4=fopen(DB4, "r");
	if(db4==NULL) 
	{
		note.Format("Can not open %s", DB4);
		AfxMessageBox(note);
		return;
	}	

	DB5.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobePHMax_30min.map", ROOTDIR);
	db5=fopen(DB5, "r");
	if(db5==NULL) 
	{
		note.Format("Can not open %s", DB5);
		AfxMessageBox(note);
		return;
	}

	DB6.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobePHMin_30min.map", ROOTDIR);
	db6=fopen(DB6, "r");
	if(db6==NULL) 
	{
		note.Format("Can not open %s", DB6);
		AfxMessageBox(note);
		return;
	}	

	DB7.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeDensityMax_30min.map", ROOTDIR);
	db7=fopen(DB7, "r");
	if(db7==NULL) 
	{
		note.Format("Can not open %s", DB7);
		AfxMessageBox(note);
		return;
	}

	DB8.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeDensityMin_30min.map", ROOTDIR);
	db8=fopen(DB8, "r");
	if(db8==NULL) 
	{
		note.Format("Can not open %s", DB8);
		AfxMessageBox(note);
		return;
	}	

	DT.Format("%s\\Database\\Globe\\GIS\\Globe_3.txt", ROOTDIR);
	dt=fopen(DT, "w");
	if(dt==NULL) 
	{
		note.Format("Can not create %s", DT);
		AfxMessageBox(note);
		return;
	}	
	
	fprintf(dt, "Grid_ID	SOC (kg C/kg soil)	Clay fraction	pH		Bulk density (mg/cm3)\n");
	fprintf(dt, "		max	min	max	min	max	min	max	min\n");

	for(;;)
	{
		if(fscanf(db1, "%d %f", &ID1, &soc1)!=2) break;
		fscanf(db2, "%d %f", &ID2, &soc2);
		fscanf(db3, "%d %f", &ID3, &clay1);
		fscanf(db4, "%d %f", &ID4, &clay2);
		fscanf(db5, "%d %f", &ID5, &ph1);
		fscanf(db6, "%d %f", &ID6, &ph2);
		fscanf(db7, "%d %f", &ID7, &density1);
		fscanf(db8, "%d %f", &ID8, &density2);

		if(ID1!=ID2)
		{
			note.Format("Error in %s or %s", DB1, DB2);
			AfxMessageBox(note);
			return;
		}		

		fprintf(dt, "%8d %8.4f %8.4f %8.4f %8.4f %8.2f %8.2f %8.2f %8.2f\n", ID1, soc1, soc2, clay1, clay2, ph1, ph2, density1, density2);

	}
	fclose(db1);
	fclose(db2);
	fclose(db3);
	fclose(db4);
	fclose(db5);
	fclose(db6);
	fclose(db7);
	fclose(db8);
	fclose(dt);
	
	AfxMessageBox("Done");
	
	
    
}

void CGraphexView::OnConvert1() //convert 30-minute crop maps into single column files for each crop
{
	// TODO: Add your command handler code here
	//Convert grid-cell map to table////////////////////////
	char TargetFile[200], TargetFile2[200], NewSoil[200];
	FILE *TF, *TF2, *SS;

	char jj[300];
	int jd,r, c, x=0, K;
	float jf;	
	int CountryN, CountryID, k=0, ccc;
	char CountryCall[100];
	float lat, lon, SoilValue;
	int dd=50, d=200, w=2;
	float z=6.0;
	int m_Column = 720;
	int m_Row = 360;
	float lllon, lllat;
	static int old_CountryN=0;
	
	CString cropsystem[106]={"", "alfalfa", "banana", "barley", "bean", "beet", "berry", "cassava", "citrus", "cotton", 
			"deepwtric", "flax", "fruittree", "grape", "hops", "legumehay", "maiz_maiz", "maiz_soy", "maize", "millet", 
			"mixedcover", "nonleghay", "nursflower", "oat", "oat_ric", "oat_soy", "palm", "peanut", "pot_maiz", "pot_pot", 
			"pot_soy", "potato", "pt_vg_vg", "rape_ctn", "rape_maiz", "rape_soy", "rape_veg", "rapeseed", "rc_bn_bn", "rc_ct_vg", 
			"rc_po_vg", "rc_rc_bn", "rc_rc_ct", "rc_rc_lh", "rc_rc_pnt", "rc_rc_po", "rc_rc_rc", "rc_rc_rp", "rc_rc_sor", "rc_rc_vg", 
			"rc_rc_wt", "rc_rp_ct", "rc_wt_vg", "ric_bar", "ric_bean", "ric_ctn", "ric_mlt", "ric_oat", "ric_pnt", "ric_pot", 
			"ric_rap", "ric_ric", "ric_sgrcn", "ric_sor", "ric_soy", "ric_veg", "ric_wht", "rice", "rye", "safflower", 
			"sorghum", "soy_veg", "soybean", "sugarcane", "sunflower", "tobacco", "tropevrgrn", "uplandric", "veg_maiz", "vegetable", 
			"vg_vg_vg", "wheat", "wht_ctn", "wht_maiz", "wht_pot", "wht_rape", "wht_soy", "wht_veg", "xrc_rp_ct", "xrc_vg_ct", 
			"xrc_wt_ct", "xrc_wt_vg", "xric_bar", "xric_bean", "xric_ctn", "xric_mlt", "xric_pnt", "xric_pot", "xric_rap", "xric_ric", 
			"xric_sgrcn", "xric_veg", "xric_wht", "xric_xric", "xrice", "past"};

	for(ccc=1; ccc<=105; ccc++)
	{
		//Name global country list file for obtaining lon/lat data
		sprintf(TargetFile, "%s\\Database\\Globe\\CountryListFile.txt", ROOTDIR);
		TF=fopen(TargetFile, "r");
		if(TF==NULL)
		{
			CString note;
			note.Format("Cannot open %s", TargetFile);
			AfxMessageBox(note);
			exit(0);
		}
		fscanf(TF, "%d %f %f %d %s", &CountryN, &lon, &lat, &CountryID, CountryCall);
		K=1;

		//Name product file
		sprintf(NewSoil, "%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[ccc]);
		SS=fopen(NewSoil, "w");
		if(SS==NULL)
		{
			CString note;
			note.Format("Cannot open %s", NewSoil);
			AfxMessageBox(note);
			exit(0);
		}
		
		//Name 30-minute grid source file
		sprintf(TargetFile2, "%s\\Database\\Globe\\GlobeData_Stage1\\g_%s.asc", ROOTDIR, cropsystem[ccc]);

ZZZ:				
			TF2=fopen(TargetFile2, "r");
			if(TF2==NULL)
			{
				CString note;
				note.Format("Cannot open %s", TargetFile2);
				AfxMessageBox(note);
				exit(0);
			}		
			fscanf(TF2, "%s %d", jj, &jd);
			fscanf(TF2, "%s %d", jj, &jd);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %d", jj, &jd);

				for(r=0; r<=m_Row-1; r++)
				{
					lllat = 90.0-(float)r*0.5 - 0.25;
					for(c=0; c<=m_Column-1; c++)
					{
						x=0;
						lllon = -180.0+(float)c*0.5 + 0.25;
						
						fscanf(TF2, "%f", &SoilValue);

						if(lon==lllon && lat==lllat)
						{
							x=1;
							K++;

							if(SoilValue<0.0) SoilValue = 0.0;
							fprintf(SS, "%d %f\n", CountryN, SoilValue);

							if(fscanf(TF, "%d %f %f %d %s", &CountryN, &lon, &lat, &CountryID, CountryCall)!=5) 
							{
								fclose(TF);		
								fclose(SS);
								
								goto DONE;
							}
							else
							{
								if(K!=CountryN)
								{
									CString note;
									note.Format("Data error at %d in file %s", K, TargetFile);
									AfxMessageBox(note);
									exit(0);

								}
							}
						}						
					}
				}
				fclose(TF2);

				if(x==0) goto ZZZ;

DONE:;
			}
			AfxMessageBox("Done");
		
}

void CGraphexView::OnConvert2() 
{
	// TODO: Add your command handler code here
	//Convert grid-cell map to table////////////////////////
	char TargetFile[200], TargetFile2[200], NewSoil[200];
	FILE *TF, *TF2, *SS;

	char jj[300];
	int jd,r, c, x=0, roww, coll;
	float jf;	
	int CountryN, CountryID, k=0;
	char CountryCall[100];
	float lat, lon, SoilValue;
	int dd=50, d=200, w=2;
	float z=6.0;
	int m_Column = 720;
	int m_Row = 360;
	float lllon, lllat;
	
	CString crop; 
	//crop.Format("AtmoNdeposit_30min.asc");
	//crop.Format("GlobeSOCMax_30min.map");
	//crop.Format("GlobeSOCMin_30min.map");
	//crop.Format("GlobeClayMax_30min.map");
	//crop.Format("GlobeClayMin_30min.map");
	//crop.Format("GlobePHMax_30min.map");
	//crop.Format("GlobePHMin_30min.map");
	//crop.Format("ManureNlegume95_30min.map");
	//crop.Format("ManureNuplandcrop95_30min.map");
	//crop.Format("ManureNwetlandrice95_30min.map");
	//crop.Format("M_CRMIX_30min");
	//crop.Format("M_CRPAS_30min");
	//crop.Format("M_GRMIX_30min");
	crop.Format("M_GRPAS_30min");

	//Name global country list file for obtaining lon/lat data
	sprintf(TargetFile, "%s\\Database\\Globe\\GlobeData_1_sources\\GlobeCountryIndex.txt", ROOTDIR);
	TF=fopen(TargetFile, "r");
		if(TF==NULL)
		{
			CString note;
			note.Format("Cannot open %s", TargetFile);
			AfxMessageBox(note);
			exit(0);
		}
		fscanf(TF, "%d %f %f %d %d %d %s", &CountryN, &lon, &lat, &roww, &coll, &CountryID, CountryCall);

		//Name product file
		sprintf(NewSoil, "%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, crop);
		SS=fopen(NewSoil, "w");
		if(SS==NULL)
		{
			CString note;
			note.Format("Cannot open %s", NewSoil);
			AfxMessageBox(note);
			exit(0);
		}
		
		//Name 30-minute grid source file
		//sprintf(TargetFile2, "%s\\Database\\Globe\\GlobeData_1_sources\\AtmoNdeposit_30minute\\%s", crop);
		sprintf(TargetFile2, "%s\\Database\\Globe\\GlobeData_1_sources\\30Minute_maps\\Manure_30minute\\%s.MAP", ROOTDIR, crop);

ZZZ:				
		TF2=fopen(TargetFile2, "r");
			if(TF2==NULL)
			{
				CString note;
				note.Format("Cannot open %s", TargetFile2);
				AfxMessageBox(note);
				exit(0);
			}		
			fscanf(TF2, "%s %d", jj, &jd);
			fscanf(TF2, "%s %d", jj, &jd);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %d", jj, &jd);

				for(r=0; r<=m_Row-1; r++)
				{
					lllat = 90.0-(float)r*0.5 + 0.25;
					for(c=0; c<=m_Column-1; c++)
					{
						x=0;
						lllon = -180.0+(float)c*0.5 + 0.25;
						
						fscanf(TF2, "%f", &SoilValue);

						if(lon==lllon && lat==lllat)
						{
							x=1;

							if(SoilValue<0.0) SoilValue = 0.0;
							fprintf(SS, "%d %f\n", CountryN, SoilValue);

							if(fscanf(TF, "%d %f %f %d %d %d %s", &CountryN, &lon, &lat, &roww, &coll, &CountryID, CountryCall)!=7) 
							{
								fclose(TF);		
								fclose(SS);
								
								goto DONE;
							}
						}						
					}
				}
				fclose(TF2);

				if(x==0) goto ZZZ;

DONE:;
			AfxMessageBox("Done");
			exit(0);
}

void CGraphexView::OnConvert3() 
{
	// TODO: Add your command handler code here
	//Compile globe_2.txt (climate file names and atmospheric N deposition)
	int ID1, ID2;
	CString DB1, DB2, DT, note;
	FILE *db1, *db2, *dt;
	char CountryName[100], ClimName[100], ww[300];
	int ContryID;
	float lon, lat, Ndeposit;
	
	DB1.Format("%s\\Database\\Globe\\GIS\\Globe_1.txt", ROOTDIR);
	db1=fopen(DB1, "r");
	if(db1==NULL) 
	{
		note.Format("Can not open %s", DB1);
		AfxMessageBox(note);
		return;
	}
	fgets(ww, 200, db1);

	DB2.Format("%s\\Database\\Globe\\GIS\\SingleColumn_AtmoNdeposit_30min.asc", ROOTDIR);
	db2=fopen(DB2, "r");
	if(db2==NULL) 
	{
		note.Format("Can not open %s", DB2);
		AfxMessageBox(note);
		return;
	}	
	
	DT.Format("%s\\Database\\Globe\\GIS\\Globe_2.txt", ROOTDIR);
	dt=fopen(DT, "w");
	if(dt==NULL) 
	{
		note.Format("Can not create %s", DT);
		AfxMessageBox(note);
		return;
	}	
	
	fprintf(dt, "DNDC_global_data_2: Climate file names and atmo N deposit rate (ppm)\n");

	for(;;)
	{
		if(fscanf(db1, "%d %s %d %f %f", &ID1, CountryName, &ContryID, &lon, &lat)!=5) break;
		fscanf(db2, "%d %f", &ID2, &Ndeposit);
		
		if(ID1!=ID2)
		{
			note.Format("Error in %s or %s at %d", DB1, DB2, ID1);
			AfxMessageBox(note);
			return;
		}	
		
		sprintf(ClimName, "%d_2000", ID1);

		fprintf(dt, "%8d %12s %8.2f\n", ID1, ClimName, Ndeposit);

	}
	fclose(db1);
	fclose(db2);	
	fclose(dt);
	
	AfxMessageBox("Done");	
}

void CGraphexView::OnConvert4() 
{
	// TODO: Add your command handler code here
	//Compile globe_1.txt (grid cell location and country name and ID)
	int ID1;
	CString DB1, DB2, DT, note;
	FILE *db1, *dt;
	char CountryName[100];
	int RegionID, row, column, CountryID, old_ID;
	float lon, lat;
	
	DB1.Format("%s\\Database\\Globe\\RegionListFile.txt", ROOTDIR);
	db1=fopen(DB1, "r");
	if(db1==NULL) 
	{
		note.Format("Can not open %s", DB1);
		AfxMessageBox(note);
		return;
	}

		
	DT.Format("%s\\Database\\Globe\\GIS\\Globe_1.txt", ROOTDIR);
	dt=fopen(DT, "w");
	if(dt==NULL) 
	{
		note.Format("Can not create %s", DT);
		AfxMessageBox(note);
		return;
	}	
	
	fprintf(dt, "DNDC_global_data_1: Grid cell location and country name and ID\n");

	int i=0;
	for(;;)
	{
		i++;
		//if(fscanf(db1, "%d %f %f %d %s", &ID1, &lon, &lat, &ContryID, CountryName)!=5) break;
		if(fscanf(db1, "%d %f %f %d %d %d %d %s", &ID1, &lon, &lat, &row, &column, &RegionID, &CountryID, CountryName)!=8) break; 
				
		if(ID1!=i)
		{
			note.Format("Error in %s at %d %d %f %f", DB1, old_ID, CountryID, lon, lat);
			AfxMessageBox(note);
			return;
		}	
		
		fprintf(dt, "%8d %26s %8d %8d %8.2f %8.2f %4d %4d\n", ID1, CountryName, RegionID, CountryID, lon, lat, row, column);

		old_ID = ID1;

	}
	fclose(db1);	
	fclose(dt);
	
	AfxMessageBox("Done");	
}

void CGraphexView::OnConvert5() //convert crop single column data files to Globe_4.txt
{
	// TODO: Add your command handler code here
	//Compile globe_4.txt (crop acreage for 104 cropping systems)
	int ID1, ID2, ID3, ID4, ID5, ID6, ID7, ID8, ID9, ID10,
		ID11, ID12, ID13, ID14, ID15, ID16, ID17, ID18, ID19, ID20,
		ID21, ID22, ID23, ID24, ID25, ID26, ID27, ID28, ID29, ID30,
		ID31, ID32, ID33, ID34, ID35, ID36, ID37, ID38, ID39, ID40,
		ID41, ID42, ID43, ID44, ID45, ID46, ID47, ID48, ID49, ID50,
		ID51, ID52, ID53, ID54, ID55, ID56, ID57, ID58, ID59, ID60,
		ID61, ID62, ID63, ID64, ID65, ID66, ID67, ID68, ID69, ID70,
		ID71, ID72, ID73, ID74, ID75, ID76, ID77, ID78, ID79, ID80,
		ID81, ID82, ID83, ID84, ID85, ID86, ID87, ID88, ID89, ID90,
		ID91, ID92, ID93, ID94, ID95, ID96, ID97, ID98, ID99, ID100,
		ID101, ID102, ID103, ID104, ID105;
	CString DB1, DB2, DB3, DB4, DB5, DB6, DB7, DB8, DB9, DB10,
		DB11, DB12, DB13, DB14, DB15, DB16, DB17, DB18, DB19, DB20,
		DB21, DB22, DB23, DB24, DB25, DB26, DB27, DB28, DB29, DB30,
		DB31, DB32, DB33, DB34, DB35, DB36, DB37, DB38, DB39, DB40,
		DB41, DB42, DB43, DB44, DB45, DB46, DB47, DB48, DB49, DB50,
		DB51, DB52, DB53, DB54, DB55, DB56, DB57, DB58, DB59, DB60,
		DB61, DB62, DB63, DB64, DB65, DB66, DB67, DB68, DB69, DB70,
		DB71, DB72, DB73, DB74, DB75, DB76, DB77, DB78, DB79, DB80,
		DB81, DB82, DB83, DB84, DB85, DB86, DB87, DB88, DB89, DB90,
		DB91, DB92, DB93, DB94, DB95, DB96, DB97, DB98, DB99, DB100,
		DB101, DB102, DB103, DB104, DB105;
	CString DT, note;
	FILE *dt;

	FILE *db1, *db2, *db3, *db4, *db5, *db6, *db7, *db8, *db9, *db10,
		*db11, *db12, *db13, *db14, *db15, *db16, *db17, *db18, *db19, *db20,
		*db21, *db22, *db23, *db24, *db25, *db26, *db27, *db28, *db29, *db30,
		*db31, *db32, *db33, *db34, *db35, *db36, *db37, *db38, *db39, *db40,
		*db41, *db42, *db43, *db44, *db45, *db46, *db47, *db48, *db49, *db50,
		*db51, *db52, *db53, *db54, *db55, *db56, *db57, *db58, *db59, *db60,
		*db61, *db62, *db63, *db64, *db65, *db66, *db67, *db68, *db69, *db70,
		*db71, *db72, *db73, *db74, *db75, *db76, *db77, *db78, *db79, *db80,
		*db81, *db82, *db83, *db84, *db85, *db86, *db87, *db88, *db89, *db90,
		*db91, *db92, *db93, *db94, *db95, *db96, *db97, *db98, *db99, *db100,
		*db101, *db102, *db103, *db104, *db105;

	CString cropsystem[106]={"", "alfalfa", "banana", "barley", "bean", "beet", "berry", "cassava", "citrus", "cotton", 
			"deepwtric", "flax", "fruittree", "grape", "hops", "legumehay", "maiz_maiz", "maiz_soy", "maize", "millet", 
			"mixedcover", "nonleghay", "nursflower", "oat", "oat_ric", "oat_soy", "palm", "peanut", "pot_maiz", "pot_pot", 
			"pot_soy", "potato", "pt_vg_vg", "rape_ctn", "rape_maiz", "rape_soy", "rape_veg", "rapeseed", "rc_bn_bn", "rc_ct_vg", 
			"rc_po_vg", "rc_rc_bn", "rc_rc_ct", "rc_rc_lh", "rc_rc_pnt", "rc_rc_po", "rc_rc_rc", "rc_rc_rp", "rc_rc_sor", "rc_rc_vg", 
			"rc_rc_wt", "rc_rp_ct", "rc_wt_vg", "ric_bar", "ric_bean", "ric_ctn", "ric_mlt", "ric_oat", "ric_pnt", "ric_pot", 
			"ric_rap", "ric_ric", "ric_sgrcn", "ric_sor", "ric_soy", "ric_veg", "ric_wht", "rice", "rye", "safflower", 
			"sorghum", "soy_veg", "soybean", "sugarcane", "sunflower", "tobacco", "tropevrgrn", "uplandric", "veg_maiz", "vegetable", 
			"vg_vg_vg", "wheat", "wht_ctn", "wht_maiz", "wht_pot", "wht_rape", "wht_soy", "wht_veg", "xrc_rp_ct", "xrc_vg_ct", 
			"xrc_wt_ct", "xrc_wt_vg", "xric_bar", "xric_bean", "xric_ctn", "xric_mlt", "xric_pnt", "xric_pot", "xric_rap", "xric_ric", 
			"xric_sgrcn", "xric_veg", "xric_wht", "xric_xric", "xrice", "past"};

	int i;

	//Open crop files
	DB1.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[1]);
	db1=fopen(DB1, "r");
	if(db1==NULL) 
	{
		note.Format("Can not open %s", DB1);
		AfxMessageBox(note);
		return;
	}

	DB2.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[2]);
	db2=fopen(DB2, "r");
	if(db2==NULL) 
	{
		note.Format("Can not open %s", DB2);
		AfxMessageBox(note);
		return;
	}

	DB3.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[3]);
	db3=fopen(DB3, "r");

	DB4.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[4]);
	db4=fopen(DB4, "r");

	DB5.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[5]);
	db5=fopen(DB5, "r");

	DB6.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[6]);
	db6=fopen(DB6, "r");

	DB7.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[7]);
	db7=fopen(DB7, "r");

	DB8.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[8]);
	db8=fopen(DB8, "r");

	DB9.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[9]);
	db9=fopen(DB9, "r");

	DB10.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[10]);
	db10=fopen(DB10, "r");

	DB11.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[11]);
	db11=fopen(DB11, "r");

	DB12.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[12]);
	db12=fopen(DB12, "r");

	DB13.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[13]);
	db13=fopen(DB13, "r");

	DB14.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[14]);
	db14=fopen(DB14, "r");

	DB15.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[15]);
	db15=fopen(DB15, "r");

	DB16.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[16]);
	db16=fopen(DB16, "r");

	DB17.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[17]);
	db17=fopen(DB17, "r");

	DB18.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[18]);
	db18=fopen(DB18, "r");

	DB19.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[19]);
	db19=fopen(DB19, "r");

	DB20.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[20]);
	db20=fopen(DB20, "r");

	DB21.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[21]);
	db21=fopen(DB21, "r");

	DB22.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[22]);
	db22=fopen(DB22, "r");

	DB23.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[23]);
	db23=fopen(DB23, "r");

	DB24.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[24]);
	db24=fopen(DB24, "r");

	DB25.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[25]);
	db25=fopen(DB25, "r");

	DB26.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[26]);
	db26=fopen(DB26, "r");

	DB27.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[27]);
	db27=fopen(DB27, "r");

	DB28.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[28]);
	db28=fopen(DB28, "r");

	DB29.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[29]);
	db29=fopen(DB29, "r");

	DB30.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[30]);
	db30=fopen(DB30, "r");

	DB31.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[31]);
	db31=fopen(DB31, "r");

	DB32.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[32]);
	db32=fopen(DB32, "r");

	DB33.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[33]);
	db33=fopen(DB33, "r");

	DB34.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[34]);
	db34=fopen(DB34, "r");

	DB35.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[35]);
	db35=fopen(DB35, "r");

	DB36.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[36]);
	db36=fopen(DB36, "r");

	DB37.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[37]);
	db37=fopen(DB37, "r");

	DB38.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[38]);
	db38=fopen(DB38, "r");

	DB39.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[39]);
	db39=fopen(DB39, "r");

	DB40.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[40]);
	db40=fopen(DB40, "r");

DB41.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[41]);
	db41=fopen(DB41, "r");

	DB42.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[42]);
	db42=fopen(DB42, "r");

	DB43.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[43]);
	db43=fopen(DB43, "r");

	DB44.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[44]);
	db44=fopen(DB44, "r");

	DB45.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[45]);
	db45=fopen(DB45, "r");

	DB46.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[46]);
	db46=fopen(DB46, "r");

	DB47.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[47]);
	db47=fopen(DB47, "r");

	DB48.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[48]);
	db48=fopen(DB48, "r");

	DB49.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[49]);
	db49=fopen(DB49, "r");

	DB50.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[50]);
	db50=fopen(DB50, "r");

DB51.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[51]);
	db51=fopen(DB51, "r");

	DB52.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[52]);
	db52=fopen(DB52, "r");

	DB53.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[53]);
	db53=fopen(DB53, "r");

	DB54.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[54]);
	db54=fopen(DB54, "r");

	DB55.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[55]);
	db55=fopen(DB55, "r");

	DB56.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[56]);
	db56=fopen(DB56, "r");

	DB57.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[57]);
	db57=fopen(DB57, "r");

	DB58.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[58]);
	db58=fopen(DB58, "r");

	DB59.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[59]);
	db59=fopen(DB59, "r");

	DB60.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[60]);
	db60=fopen(DB60, "r");

DB61.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[61]);
	db61=fopen(DB61, "r");

	DB62.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[62]);
	db62=fopen(DB62, "r");

	DB63.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[63]);
	db63=fopen(DB63, "r");

	DB64.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[64]);
	db64=fopen(DB64, "r");

	DB65.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[65]);
	db65=fopen(DB65, "r");

	DB66.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[66]);
	db66=fopen(DB66, "r");

	DB67.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[67]);
	db67=fopen(DB67, "r");

	DB68.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[68]);
	db68=fopen(DB68, "r");

	DB69.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[69]);
	db69=fopen(DB69, "r");

	DB70.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[70]);
	db70=fopen(DB70, "r");

DB71.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[71]);
	db71=fopen(DB71, "r");

	DB72.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[72]);
	db72=fopen(DB72, "r");

	DB73.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[73]);
	db73=fopen(DB73, "r");

	DB74.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[74]);
	db74=fopen(DB74, "r");

	DB75.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[75]);
	db75=fopen(DB75, "r");

	DB76.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[76]);
	db76=fopen(DB76, "r");

	DB77.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[77]);
	db77=fopen(DB77, "r");

	DB78.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[78]);
	db78=fopen(DB78, "r");

	DB79.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[79]);
	db79=fopen(DB79, "r");

	DB80.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[80]);
	db80=fopen(DB80, "r");

DB81.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[81]);
	db81=fopen(DB81, "r");

	DB82.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[82]);
	db82=fopen(DB82, "r");

	DB83.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[83]);
	db83=fopen(DB83, "r");

	DB84.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[84]);
	db84=fopen(DB84, "r");

	DB85.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[85]);
	db85=fopen(DB85, "r");

	DB86.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[86]);
	db86=fopen(DB86, "r");

	DB87.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[87]);
	db87=fopen(DB87, "r");

	DB88.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[88]);
	db88=fopen(DB88, "r");

	DB89.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[89]);
	db89=fopen(DB89, "r");

	DB90.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[90]);
	db90=fopen(DB90, "r");

DB91.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[91]);
	db91=fopen(DB91, "r");

	DB92.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[92]);
	db92=fopen(DB92, "r");

	DB93.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[93]);
	db93=fopen(DB93, "r");

	DB94.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[94]);
	db94=fopen(DB94, "r");

	DB95.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[95]);
	db95=fopen(DB95, "r");

	DB96.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[96]);
	db96=fopen(DB96, "r");

	DB97.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[97]);
	db97=fopen(DB97, "r");

	DB98.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[98]);
	db98=fopen(DB98, "r");

	DB99.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[99]);
	db99=fopen(DB99, "r");

	DB100.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[100]);
	db100=fopen(DB100, "r");

DB101.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[101]);
	db101=fopen(DB101, "r");

	DB102.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[102]);
	db102=fopen(DB102, "r");

	DB103.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[103]);
	db103=fopen(DB103, "r");

	DB104.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[104]);
	db104=fopen(DB104, "r");

	DB105.Format("%s\\Database\\Globe\\GIS\\SingleColumn_%s", ROOTDIR, cropsystem[105]);
	db105=fopen(DB105, "r");
	
	///////////////////////////////////////////////////////////////
	
	DT.Format("%s\\Database\\Globe\\GIS\\Globe_4.txt");
	dt=fopen(DT, "w");
	if(dt==NULL) 
	{
		note.Format("Can not create %s", DT);
		AfxMessageBox(note);
		return;
	}	
	
	fprintf(dt, "DNDC_global_data_4: crop acreage (ha)\n");
	
	fprintf(dt, "%8d ", 105);
	for(i=1; i<=105; i++) fprintf(dt, "%8s ", cropsystem[i]);
	fprintf(dt, "\n");

	fprintf(dt, "%8d ", 105);
	for(i=1; i<=105; i++) fprintf(dt, "%8d ", i);
	fprintf(dt, "\n");

	for(int k=1; k<=67685; k++)
	{
		fscanf(db1, "%d %f", &ID1, &ha[1]);
		fscanf(db2, "%d %f", &ID2, &ha[2]);
		fscanf(db3, "%d %f", &ID3, &ha[3]);
		fscanf(db4, "%d %f", &ID4, &ha[4]);
		fscanf(db5, "%d %f", &ID5, &ha[5]);
		fscanf(db6, "%d %f", &ID6, &ha[6]);
		fscanf(db7, "%d %f", &ID7, &ha[7]);
		fscanf(db8, "%d %f", &ID8, &ha[8]);
		fscanf(db9, "%d %f", &ID9, &ha[9]);
		fscanf(db10, "%d %f", &ID10, &ha[10]);
		fscanf(db11, "%d %f", &ID11, &ha[11]);
		fscanf(db12, "%d %f", &ID12, &ha[12]);
		fscanf(db13, "%d %f", &ID13, &ha[13]);
		fscanf(db14, "%d %f", &ID14, &ha[14]);
		fscanf(db15, "%d %f", &ID15, &ha[15]);
		fscanf(db16, "%d %f", &ID16, &ha[16]);
		fscanf(db17, "%d %f", &ID17, &ha[17]);
		fscanf(db18, "%d %f", &ID18, &ha[18]);
		fscanf(db19, "%d %f", &ID19, &ha[19]);
		fscanf(db20, "%d %f", &ID20, &ha[20]);
		fscanf(db21, "%d %f", &ID21, &ha[21]);
		fscanf(db22, "%d %f", &ID22, &ha[22]);
		fscanf(db23, "%d %f", &ID23, &ha[23]);
		fscanf(db24, "%d %f", &ID24, &ha[24]);
		fscanf(db25, "%d %f", &ID25, &ha[25]);
		fscanf(db26, "%d %f", &ID26, &ha[26]);
		fscanf(db27, "%d %f", &ID27, &ha[27]);
		fscanf(db28, "%d %f", &ID28, &ha[28]);
		fscanf(db29, "%d %f", &ID29, &ha[29]);
		fscanf(db30, "%d %f", &ID30, &ha[30]);
		fscanf(db31, "%d %f", &ID31, &ha[31]);
		fscanf(db32, "%d %f", &ID32, &ha[32]);
		fscanf(db33, "%d %f", &ID33, &ha[33]);
		fscanf(db34, "%d %f", &ID34, &ha[34]);
		fscanf(db35, "%d %f", &ID35, &ha[35]);
		fscanf(db36, "%d %f", &ID36, &ha[36]);
		fscanf(db37, "%d %f", &ID37, &ha[37]);
		fscanf(db38, "%d %f", &ID38, &ha[38]);
		fscanf(db39, "%d %f", &ID39, &ha[39]);
		fscanf(db40, "%d %f", &ID40, &ha[40]);
		fscanf(db41, "%d %f", &ID41, &ha[41]);
		fscanf(db42, "%d %f", &ID42, &ha[42]);
		fscanf(db43, "%d %f", &ID43, &ha[43]);
		fscanf(db44, "%d %f", &ID44, &ha[44]);
		fscanf(db45, "%d %f", &ID45, &ha[45]);
		fscanf(db46, "%d %f", &ID46, &ha[46]);
		fscanf(db47, "%d %f", &ID47, &ha[47]);
		fscanf(db48, "%d %f", &ID48, &ha[48]);
		fscanf(db49, "%d %f", &ID49, &ha[49]);
		fscanf(db50, "%d %f", &ID50, &ha[50]);
		fscanf(db51, "%d %f", &ID51, &ha[51]);
		fscanf(db52, "%d %f", &ID52, &ha[52]);
		fscanf(db53, "%d %f", &ID53, &ha[53]);
		fscanf(db54, "%d %f", &ID54, &ha[54]);
		fscanf(db55, "%d %f", &ID55, &ha[55]);
		fscanf(db56, "%d %f", &ID56, &ha[56]);
		fscanf(db57, "%d %f", &ID57, &ha[57]);
		fscanf(db58, "%d %f", &ID58, &ha[58]);
		fscanf(db59, "%d %f", &ID59, &ha[59]);
		fscanf(db60, "%d %f", &ID60, &ha[60]);
		fscanf(db61, "%d %f", &ID61, &ha[61]);
		fscanf(db62, "%d %f", &ID62, &ha[62]);
		fscanf(db63, "%d %f", &ID63, &ha[63]);
		fscanf(db64, "%d %f", &ID64, &ha[64]);
		fscanf(db65, "%d %f", &ID65, &ha[65]);
		fscanf(db66, "%d %f", &ID66, &ha[66]);
		fscanf(db67, "%d %f", &ID67, &ha[67]);
		fscanf(db68, "%d %f", &ID68, &ha[68]);
		fscanf(db69, "%d %f", &ID69, &ha[69]);
		fscanf(db70, "%d %f", &ID70, &ha[70]);
		fscanf(db71, "%d %f", &ID71, &ha[71]);
		fscanf(db72, "%d %f", &ID72, &ha[72]);
		fscanf(db73, "%d %f", &ID73, &ha[73]);
		fscanf(db74, "%d %f", &ID74, &ha[74]);
		fscanf(db75, "%d %f", &ID75, &ha[75]);
		fscanf(db76, "%d %f", &ID76, &ha[76]);
		fscanf(db77, "%d %f", &ID77, &ha[77]);
		fscanf(db78, "%d %f", &ID78, &ha[78]);
		fscanf(db79, "%d %f", &ID79, &ha[79]);
		fscanf(db80, "%d %f", &ID80, &ha[80]);
		fscanf(db81, "%d %f", &ID81, &ha[81]);
		fscanf(db82, "%d %f", &ID82, &ha[82]);
		fscanf(db83, "%d %f", &ID83, &ha[83]);
		fscanf(db84, "%d %f", &ID84, &ha[84]);
		fscanf(db85, "%d %f", &ID85, &ha[85]);
		fscanf(db86, "%d %f", &ID86, &ha[86]);
		fscanf(db87, "%d %f", &ID87, &ha[87]);
		fscanf(db88, "%d %f", &ID88, &ha[88]);
		fscanf(db89, "%d %f", &ID89, &ha[89]);
		fscanf(db90, "%d %f", &ID90, &ha[90]);
		fscanf(db91, "%d %f", &ID91, &ha[91]);
		fscanf(db92, "%d %f", &ID92, &ha[92]);
		fscanf(db93, "%d %f", &ID93, &ha[93]);
		fscanf(db94, "%d %f", &ID94, &ha[94]);
		fscanf(db95, "%d %f", &ID95, &ha[95]);
		fscanf(db96, "%d %f", &ID96, &ha[96]);
		fscanf(db97, "%d %f", &ID97, &ha[97]);
		fscanf(db98, "%d %f", &ID98, &ha[98]);
		fscanf(db99, "%d %f", &ID99, &ha[99]);
		fscanf(db100, "%d %f", &ID100, &ha[100]);
		fscanf(db101, "%d %f", &ID101, &ha[101]);
		fscanf(db102, "%d %f", &ID102, &ha[102]);
		fscanf(db103, "%d %f", &ID103, &ha[103]);
		fscanf(db104, "%d %f", &ID104, &ha[104]);
		fscanf(db105, "%d %f", &ID105, &ha[105]);

		if(ID1==ID2&&ID3==ID4&&ID5==ID6&&ID7==ID8&&ID9==ID10&&
		ID11==ID12&&ID13==ID14&&ID15==ID16&&ID17==ID18&&ID19==ID20&&
		ID21==ID22&&ID23==ID24&&ID25==ID26&&ID27==ID28&&ID29==ID30&&
		ID31==ID32&&ID33==ID34&&ID35==ID36&&ID37==ID38&&ID39==ID40&&
		ID41==ID42&&ID43==ID44&&ID45==ID46&&ID47==ID48&&ID49==ID50&&
		ID51==ID52&&ID53==ID54&&ID55==ID56&&ID57==ID58&&ID59==ID60&&
		ID61==ID62&&ID63==ID64&&ID65==ID66&&ID67==ID68&&ID69==ID70&&
		ID71==ID72&&ID73==ID74&&ID75==ID76&&ID77==ID78&&ID79==ID80&&
		ID81==ID82&&ID83==ID84&&ID85==ID86&&ID87==ID88&&ID89==ID90&&
		ID91==ID92&&ID93==ID94&&ID95==ID96&&ID97==ID98&&ID99==ID100&&
		ID101==ID102&&ID103==ID104&&ID1==ID105)
		{}
		else
		{
			note.Format("Data error at %d", ID1);
			AfxMessageBox(note);
			exit(0);
		}
	
		fprintf(dt, "%8d ", ID1);
		for(int i=1; i<=105; i++) fprintf(dt, "%8.0f ", ha[i]);
		fprintf(dt, "\n");

	}
	fclose(db1);
	fclose(db2);	
	fclose(db3);
	fclose(db4);
	fclose(db5);
	fclose(db6);
	fclose(db7);
	fclose(db8);
	fclose(db9);
	fclose(db10);
	fclose(db11);
	fclose(db12);	
	fclose(db13);
	fclose(db14);
	fclose(db15);
	fclose(db16);
	fclose(db17);
	fclose(db18);
	fclose(db19);
	fclose(db20);
	fclose(db21);
	fclose(db22);	
	fclose(db23);
	fclose(db24);
	fclose(db25);
	fclose(db26);
	fclose(db27);
	fclose(db28);
	fclose(db29);
	fclose(db30);
	fclose(db31);
	fclose(db32);	
	fclose(db33);
	fclose(db34);
	fclose(db35);
	fclose(db36);
	fclose(db37);
	fclose(db38);
	fclose(db39);
	fclose(db40);
	fclose(db41);
	fclose(db42);	
	fclose(db43);
	fclose(db44);
	fclose(db45);
	fclose(db46);
	fclose(db47);
	fclose(db48);
	fclose(db49);
	fclose(db50);
	fclose(db51);
	fclose(db52);	
	fclose(db53);
	fclose(db54);
	fclose(db55);
	fclose(db56);
	fclose(db57);
	fclose(db58);
	fclose(db59);
	fclose(db60);
	fclose(db61);
	fclose(db62);	
	fclose(db63);
	fclose(db64);
	fclose(db65);
	fclose(db66);
	fclose(db67);
	fclose(db68);
	fclose(db69);
	fclose(db70);
	fclose(db71);
	fclose(db72);	
	fclose(db73);
	fclose(db74);
	fclose(db75);
	fclose(db76);
	fclose(db77);
	fclose(db78);
	fclose(db79);
	fclose(db80);
	fclose(db81);
	fclose(db82);	
	fclose(db83);
	fclose(db84);
	fclose(db85);
	fclose(db86);
	fclose(db87);
	fclose(db88);
	fclose(db89);
	fclose(db90);
	fclose(db91);
	fclose(db92);	
	fclose(db93);
	fclose(db94);
	fclose(db95);
	fclose(db96);
	fclose(db97);
	fclose(db98);
	fclose(db99);
	fclose(db100);
	fclose(db101);
	fclose(db102);	
	fclose(db103);
	fclose(db104);
	fclose(db105);
	
	fclose(dt);
	
	AfxMessageBox("Done");	
}

void CGraphexView::OnConvert6() 
{
	// TODO: Add your command handler code here
	GlobeData ww;

	if (ww.DoModal()==IDOK) 
	{


	}
}

void CGraphexView::OnSoilDensity() 
{
	// TODO: Add your command handler code here
	//Calculate soil bulk density
	int ID1, ID2;
	float clay, soc, Fo,Dbo,Dbm,SD;
	CString DB1, DB2, DB3, note;
	FILE *db1, *db2, *db3;

	DB1.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeClayMax_30min.map", ROOTDIR);
	//DB1.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeClayMin_30min.map");
	db1=fopen(DB1, "r");
	if(db1==NULL) 
	{
		note.Format("Can not open %s", DB1);
		AfxMessageBox(note);
		return;
	}

	DB2.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeSOCMax_30min.map", ROOTDIR);
	//DB2.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeSOCMin_30min.map");
	db2=fopen(DB2, "r");
	if(db2==NULL) 
	{
		note.Format("Can not open %s", DB2);
		AfxMessageBox(note);
		return;
	}	

	DB3.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeDensityMax_30min.map", ROOTDIR);
	//DB3.Format("%s\\Database\\Globe\\GIS\\SingleColumn_GlobeDensityMin_30min.map");
	db3=fopen(DB3, "w");
	if(db3==NULL) 
	{
		note.Format("Can not create %s", DB3);
		AfxMessageBox(note);
		return;
	}	
	
	for(;;)
	{
		if(fscanf(db1, "%d %f", &ID1, &clay)!=2) break;
		fscanf(db2, "%d %f", &ID2, &soc);

		if(ID1!=ID2)
		{
			note.Format("Error in %s or %s", DB1, DB2);
			AfxMessageBox(note);
			return;
		}
soc=0.01;
clay=0.6;
		if(clay<=0.0||soc<=0.0)
		{
			SD = 0.0;
		}
		else
		{
			Fo  = 2.0 * soc;
			Dbo = 0.14;
			Dbm = 1.3 + 2.65 * clay - 2.15 * clay * clay;
			SD  = (Dbm * Dbo / (Fo * Dbm + (1.0 - Fo) * Dbo));
		}

		fprintf(db3, "%d %f\n", ID1, SD);

	}
	fclose(db1);
	fclose(db2);
	fclose(db3);
	
	AfxMessageBox("Done");
}

void CGraphexView::OnGlobe5() 
{
	// TODO: Add your command handler code here
		//Convert grid-cell map to table////////////////////////
	char TargetFile[200], TargetFile2[200], NewSoil[200];
	FILE *TF, *TF2, *SS;

	char jj[300];
	int jd,r, c, x=0, roww, coll;
	float jf;	
	int CountryN, CountryID, k=0, ccc;
	char CountryCall[100];
	float lat, lon, SoilValue;
	int dd=50, d=200, w=2;
	float z=6.0;
	int m_Column = 720;
	int m_Row = 360;
	float lllon, lllat;
	
	CString cropsystem[108]={"", "alfalfa", "banana", "barley", "bean", "beet", "berry", "cassava", "citrus", "cotton", 
			"deepwtric", "flax", "fruittree", "grape", "hops", "legumehay", "maiz_maiz", "maiz_soy", "maize", "millet", 
			"mixedcover", "nonleghay", "nursflower", "oat", "oat_ric", "oat_soy", "palm", "peanut", "pot_maiz", "pot_pot", 
			"pot_soy", "potato", "pt_vg_vg", "rape_ctn", "rape_maiz", "rape_soy", "rape_veg", "rapeseed", "rc_bn_bn", "rc_ct_vg", 
			"rc_po_vg", "rc_rc_bn", "rc_rc_ct", "rc_rc_lh", "rc_rc_pnt", "rc_rc_po", "rc_rc_rc", "rc_rc_rp", "rc_rc_sor", "rc_rc_vg", 
			"rc_rc_wt", "rc_rp_ct", "rc_wt_vg", "ric_bar", "ric_bean", "ric_ctn", "ric_mlt", "ric_oat", "ric_pnt", "ric_pot", 
			"ric_rap", "ric_ric", "ric_sgrcn", "ric_sor", "ric_soy", "ric_veg", "ric_wht", "rice", "rye", "safflower", 
			"sorghum", "soy_veg", "soybean", "sugarcane", "sunflower", "tobacco", "tropevrgrn", "uplandric", "veg_maiz", "vegetable", 
			"vg_vg_vg", "wheat", "wht_ctn", "wht_maiz", "wht_pot", "wht_rape", "wht_soy", "wht_veg", "xrc_rp_ct", "xrc_vg_ct", 
			"xrc_wt_ct", "xrc_wt_vg", "xric_bar", "xric_bean", "xric_ctn", "xric_mlt", "xric_pnt", "xric_pot", "xric_rap", "xric_ric", 
			"xric_sgrcn", "xric_veg", "xric_wht", "xric_xric", "xrice", "past", "manure", "normalization"};

	for(ccc=1; ccc<=107; ccc++)
	{
		//Name global country list file for obtaining lon/lat data

		sprintf(TargetFile, "%s\\Database\\Globe\\GlobeData_1_sources\\GlobeCountryIndex.txt", ROOTDIR);
		TF=fopen(TargetFile, "r");
		if(TF==NULL)
		{
			CString note;
			note.Format("Cannot open %s", TargetFile);
			AfxMessageBox(note);
			exit(0);
		}
		fscanf(TF, "%d %f %f %d %d %d %s", &CountryN, &lon, &lat, &roww, &coll, &CountryID, CountryCall);

		//Name product file
		sprintf(NewSoil, "%s\\Database\\Globe\\GIS\\FertColumn_%s", ROOTDIR, cropsystem[ccc]);
		SS=fopen(NewSoil, "w");
		if(SS==NULL)
		{
			CString note;
			note.Format("Cannot open %s", NewSoil);
			AfxMessageBox(note);
			exit(0);
		}
		
		//Name 30-minute grid source file
ZZZ:
		sprintf(TargetFile2, "%s\\Database\\Globe\\GlobeData_1_sources\\FertilizerRate_30minute\\f_%s.asc", ROOTDIR, cropsystem[ccc]);
			TF2=fopen(TargetFile2, "r");
			if(TF2==NULL)
			{
				fclose(TF);
				fclose(SS);
				goto RRR;
			}	
			fscanf(TF2, "%s %d", jj, &jd);
			fscanf(TF2, "%s %d", jj, &jd);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %f", jj, &jf);
			fscanf(TF2, "%s %d", jj, &jd);

				for(r=0; r<=m_Row-1; r++)
				{
					lllat = 90.0-(float)r*0.5 + 0.25;
					for(c=0; c<=m_Column-1; c++)
					{
						x=0;
						lllon = -180.0+(float)c*0.5 + 0.25;
						
						fscanf(TF2, "%f", &SoilValue);

						if(lon==lllon && lat==lllat)
						{
							x=1;

							if(SoilValue<0.0) SoilValue = 0.0;
							fprintf(SS, "%d %f\n", CountryN, SoilValue);

							if(fscanf(TF, "%d %f %f %d %d %d %s", &CountryN, &lon, &lat, &roww, &coll, &CountryID, CountryCall)!=7) 
							{
								fclose(TF);		
								fclose(SS);
								
								goto DONE;
							}
						}						
					}
				}
				fclose(TF2);

				if(x==0) goto ZZZ;

DONE:;
RRR:;
			}
			AfxMessageBox("Done");
		
}

void CGraphexView::OnConvert7() 
{
	// TODO: Add your command handler code here
		//Compile globe_4.txt (crop acreage for 104 cropping systems)
	int i;
	int ID1, ID2, ID3, ID4, ID5, ID6, ID7, ID8, ID9, ID10,
		ID11, ID12, ID13, ID14, ID15, ID16, ID17, ID18, ID19, ID20,
		ID21, ID22, ID23, ID24, ID25, ID26, ID27, ID28, ID29, ID30,
		ID31, ID32, ID33, ID34, ID35, ID36, ID37, ID38, ID39, ID40,
		ID41, ID42, ID43, ID44;
	CString DB1, DB2, DB3, DB4, DB5, DB6, DB7, DB8, DB9, DB10,
		DB11, DB12, DB13, DB14, DB15, DB16, DB17, DB18, DB19, DB20,
		DB21, DB22, DB23, DB24, DB25, DB26, DB27, DB28, DB29, DB30,
		DB31, DB32, DB33, DB34, DB35, DB36, DB37, DB38, DB39, DB40,
		DB41, DB42, DB43, DB44, DB45, DB46, DB47;
	CString DT, note;
	FILE *dt;

	FILE *db1, *db2, *db3, *db4, *db5, *db6, *db7, *db8, *db9, *db10,
		*db11, *db12, *db13, *db14, *db15, *db16, *db17, *db18, *db19, *db20,
		*db21, *db22, *db23, *db24, *db25, *db26, *db27, *db28, *db29, *db30,
		*db31, *db32, *db33, *db34, *db35, *db36, *db37, *db38, *db39, *db40,
		*db41, *db42, *db43, *db44;

	CString crop_system[45]={"", "maize", "wheat", "soybean", "legumehay", "nonleghay", "palm", "sugarcane", "barley", "oat", "alfalfa", 
						"past", "xrice", "sorghum", "cotton", "rye", "vegetable", "uplandric", "potato", "beet", "rice", 
						"banana", "cassava", "peanut", "deepwtric", "rapeseed", "tobacco", "millet", "sunflower", "bean", "hops", 
						"mixedcover", "safflower", "berry", "flax", "tropevrgrn", "nursflower", "fruittree", "grape", "citrus", "M_CRMIX",
						"M_CRPAS", "M_GRMIX", "M_GRPAS", "normalization"};

	int CropIndex[45]={0,1,2,3,4,5,32,7,8,9,10,12,46,13,14,15,16,24,18,19,20,21,51,23,30,25,26,27,28,29,44,47,48,38,49,54,36,40,42,41,101,102,103,104,110};
	
	//Open crop files
	DB1.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[1]);
	db1=fopen(DB1, "r");
	if(db1==NULL) 
	{
		note.Format("Can not open %s", DB1);
		AfxMessageBox(note);
		return;
	}

	DB2.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[2]);
	db2=fopen(DB2, "r");
	if(db2==NULL) 
	{
		note.Format("Can not open %s", DB2);
		AfxMessageBox(note);
		return;
	}

	DB3.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[3]);
	db3=fopen(DB3, "r");

	DB4.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[4]);
	db4=fopen(DB4, "r");

	DB5.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[5]);
	db5=fopen(DB5, "r");

	DB6.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[6]);
	db6=fopen(DB6, "r");

	DB7.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[7]);
	db7=fopen(DB7, "r");

	DB8.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[8]);
	db8=fopen(DB8, "r");

	DB9.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[9]);
	db9=fopen(DB9, "r");

	DB10.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[10]);
	db10=fopen(DB10, "r");

	DB11.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[11]);
	db11=fopen(DB11, "r");

	DB12.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[12]);
	db12=fopen(DB12, "r");

	DB13.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[13]);
	db13=fopen(DB13, "r");

	DB14.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[14]);
	db14=fopen(DB14, "r");

	DB15.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[15]);
	db15=fopen(DB15, "r");

	DB16.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[16]);
	db16=fopen(DB16, "r");

	DB17.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[17]);
	db17=fopen(DB17, "r");

	DB18.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[18]);
	db18=fopen(DB18, "r");

	DB19.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[19]);
	db19=fopen(DB19, "r");

	DB20.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[20]);
	db20=fopen(DB20, "r");

DB21.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[21]);
	db21=fopen(DB21, "r");

	DB22.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[22]);
	db22=fopen(DB22, "r");

	DB23.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[23]);
	db23=fopen(DB23, "r");

	DB24.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[24]);
	db24=fopen(DB24, "r");

	DB25.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[25]);
	db25=fopen(DB25, "r");

	DB26.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[26]);
	db26=fopen(DB26, "r");

	DB27.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[27]);
	db27=fopen(DB27, "r");

	DB28.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[28]);
	db28=fopen(DB28, "r");

	DB29.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[29]);
	db29=fopen(DB29, "r");

	DB30.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[30]);
	db30=fopen(DB30, "r");

DB31.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[31]);
	db31=fopen(DB31, "r");

	DB32.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[32]);
	db32=fopen(DB32, "r");

	DB33.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[33]);
	db33=fopen(DB33, "r");

	DB34.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[34]);
	db34=fopen(DB34, "r");

	DB35.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[35]);
	db35=fopen(DB35, "r");

	DB36.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[36]);
	db36=fopen(DB36, "r");

	DB37.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[37]);
	db37=fopen(DB37, "r");

	DB38.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[38]);
	db38=fopen(DB38, "r");

	DB39.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[39]);
	db39=fopen(DB39, "r");

	DB40.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[40]);
	db40=fopen(DB40, "r");

	DB41.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[41]);
	db41=fopen(DB41, "r");

	DB42.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[42]);
	db42=fopen(DB42, "r");

	DB43.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[43]);
	db43=fopen(DB43, "r");

	DB44.Format("%s\\Database\\Globe\\GlobeData_2_processed\\FertColumn_%s", ROOTDIR, crop_system[44]);
	db44=fopen(DB44, "r");

	///////////////////////////////////////////////////////////////
	int TotalCrops = 44;

	DT.Format("%s\\Database\\Globe\\GIS\\Globe_5.txt", ROOTDIR);
	dt=fopen(DT, "w");
	if(dt==NULL) 
	{
		note.Format("Can not create %s", ROOTDIR, DT);
		AfxMessageBox(note);
		return;
	}	
	
	fprintf(dt, "DNDC_global_data_5: Fertilizer rate (kg N/ha per crop)\n");
	
	fprintf(dt, "%8d ", TotalCrops);	
	for(i=1; i<=TotalCrops; i++) fprintf(dt, "%8s ", crop_system[i]);
	fprintf(dt, "\n");
	
	fprintf(dt, "%8s ", "Crop");
	for(i=1; i<=TotalCrops; i++) fprintf(dt, "%8d ", CropIndex[i]);
	fprintf(dt, "\n");

	for(int k=1; k<=67685; k++)
	{
		fscanf(db1, "%d %f", &ID1, &ha[1]);
		fscanf(db2, "%d %f", &ID2, &ha[2]);
		fscanf(db3, "%d %f", &ID3, &ha[3]);
		fscanf(db4, "%d %f", &ID4, &ha[4]);
		fscanf(db5, "%d %f", &ID5, &ha[5]);
		fscanf(db6, "%d %f", &ID6, &ha[6]);
		fscanf(db7, "%d %f", &ID7, &ha[7]);
		fscanf(db8, "%d %f", &ID8, &ha[8]);
		fscanf(db9, "%d %f", &ID9, &ha[9]);
		fscanf(db10, "%d %f", &ID10, &ha[10]);
		fscanf(db11, "%d %f", &ID11, &ha[11]);
		fscanf(db12, "%d %f", &ID12, &ha[12]);
		fscanf(db13, "%d %f", &ID13, &ha[13]);
		fscanf(db14, "%d %f", &ID14, &ha[14]);
		fscanf(db15, "%d %f", &ID15, &ha[15]);
		fscanf(db16, "%d %f", &ID16, &ha[16]);
		fscanf(db17, "%d %f", &ID17, &ha[17]);
		fscanf(db18, "%d %f", &ID18, &ha[18]);
		fscanf(db19, "%d %f", &ID19, &ha[19]);
		fscanf(db20, "%d %f", &ID20, &ha[20]);
		fscanf(db21, "%d %f", &ID21, &ha[21]);
		fscanf(db22, "%d %f", &ID22, &ha[22]);
		fscanf(db23, "%d %f", &ID23, &ha[23]);
		fscanf(db24, "%d %f", &ID24, &ha[24]);
		fscanf(db25, "%d %f", &ID25, &ha[25]);
		fscanf(db26, "%d %f", &ID26, &ha[26]);
		fscanf(db27, "%d %f", &ID27, &ha[27]);
		fscanf(db28, "%d %f", &ID28, &ha[28]);
		fscanf(db29, "%d %f", &ID29, &ha[29]);
		fscanf(db30, "%d %f", &ID30, &ha[30]);
		fscanf(db31, "%d %f", &ID31, &ha[31]);
		fscanf(db32, "%d %f", &ID32, &ha[32]);
		fscanf(db33, "%d %f", &ID33, &ha[33]);
		fscanf(db34, "%d %f", &ID34, &ha[34]);
		fscanf(db35, "%d %f", &ID35, &ha[35]);
		fscanf(db36, "%d %f", &ID36, &ha[36]);
		fscanf(db37, "%d %f", &ID37, &ha[37]);
		fscanf(db38, "%d %f", &ID38, &ha[38]);
		fscanf(db39, "%d %f", &ID39, &ha[39]);
		fscanf(db40, "%d %f", &ID40, &ha[40]);
		fscanf(db41, "%d %f", &ID41, &ha[41]);
		fscanf(db42, "%d %f", &ID42, &ha[42]);
		fscanf(db43, "%d %f", &ID43, &ha[43]);
		fscanf(db44, "%d %f", &ID44, &ha[44]);

		if(ID1==ID2&&ID3==ID4&&ID5==ID6&&ID7==ID8&&ID9==ID10&&
		ID11==ID12&&ID13==ID14&&ID15==ID16&&ID17==ID18&&ID19==ID20&&
		ID21==ID22&&ID23==ID24&&ID25==ID26&&ID27==ID28&&ID29==ID30&&
		ID31==ID32&&ID33==ID34&&ID35==ID36&&ID37==ID38&&ID39==ID40
		&&ID1==ID41&&ID1==ID42&&ID1==ID43&&ID1==ID44)
		{}
		else
		{
			note.Format("Data error at %d", ID1);
			AfxMessageBox(note);
			exit(0);
		}
	
		fprintf(dt, "%8d ", ID1);
		for(int i=1; i<=TotalCrops; i++) 
		{
			if(i<TotalCrops) fprintf(dt, "%8.1f ", ha[i]);
			else fprintf(dt, " %8.4f ", ha[i]);
		}
		fprintf(dt, "\n");

	}
	fclose(db1);
	fclose(db2);	
	fclose(db3);
	fclose(db4);
	fclose(db5);
	fclose(db6);
	fclose(db7);
	fclose(db8);
	fclose(db9);
	fclose(db10);
	fclose(db11);
	fclose(db12);	
	fclose(db13);
	fclose(db14);
	fclose(db15);
	fclose(db16);
	fclose(db17);
	fclose(db18);
	fclose(db19);
	fclose(db20);
	fclose(db21);
	fclose(db22);	
	fclose(db23);
	fclose(db24);
	fclose(db25);
	fclose(db26);
	fclose(db27);
	fclose(db28);
	fclose(db29);
	fclose(db30);
	fclose(db31);
	fclose(db32);	
	fclose(db33);
	fclose(db34);
	fclose(db35);
	fclose(db36);
	fclose(db37);
	fclose(db38);
	fclose(db39);
	fclose(db40);
	fclose(db41);
	fclose(db42);
	fclose(db43);
	fclose(db44);
	fclose(dt);
	
	AfxMessageBox("Done");	

}

void CGraphexView::On5min30min() 
{
	// TODO: Add your command handler code here
	//Convert a 5-minute map to a 30-minute maps with average values

	char TargetFile[200];
	FILE *TF;

	char jj[300];
	int jd, r, c, x=0;
	float CellSize, jf, z, Fcolor;
	int d=200, dd=50, w, m_Column, m_Row;
	char min5_name[100];
	//sprintf(min5_name, "%s", "M_CRMIX");
	//sprintf(min5_name, "%s", "M_CRPAS");
	//sprintf(min5_name, "%s", "M_GRMIX");
	sprintf(min5_name, "%s", "M_GRPAS");

	sprintf(TargetFile, "%s\\Database\\Globe\\GlobeData_1_sources\\5minute_maps\\Manure_rate\\%s.MAP", ROOTDIR, min5_name);
	TF=fopen(TargetFile, "r");
	if(TF==NULL)
	{
		CString note;
		note.Format("Cannot open %s", TargetFile);
		AfxMessageBox(note);
		exit(0);
	}

	fscanf(TF, "%s %d", jj, &m_Column);
	fscanf(TF, "%s %d", jj, &m_Row);
	fscanf(TF, "%s %f", jj, &jf);
	fscanf(TF, "%s %f", jj, &jf);
	fscanf(TF, "%s %f", jj, &CellSize);
	fscanf(TF, "%s %d", jj, &jd);

	if(m_Column==720)
	{
		w=2;
		z=2.0;
		Fcolor = 300000.0;
	}
	else if(m_Column==4320)
	{
		w=1;
		z=0.333;
		Fcolor = 50000.0;
	}

		CString SRmax;
		FILE *Rmax;

		SRmax.Format("%s\\Database\\Globe\\%s_30min.MAP", ROOTDIR, min5_name);
		Rmax=fopen(SRmax, "w");
		if(Rmax==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SRmax);
			AfxMessageBox(note);
			exit(0);
		}

		fprintf(Rmax, "%s\n", "ncols         720");
		fprintf(Rmax, "%s\n", "nrows         360");
		fprintf(Rmax, "%s\n", "xllcorner     -180");
		fprintf(Rmax, "%s\n", "yllcorner     -90");
		fprintf(Rmax, "%s\n", "cellsize      0.5");
		fprintf(Rmax, "%s\n", "no_data       0");

		float DT[4321][7];

		m_Row = 0;
   		for(int Rr=1; Rr<=360; Rr++)
		{
			for(r=1; r<=6; r++)
			{
				m_Row++;

				for(c=1; c<=m_Column; c++)
				{
					fscanf(TF, "%f", &DT[c][r]);
				}
			}

			int qq=0;
			float Save;

			for(int pp=1; pp<=720; pp++)
			{
				int xxx=0;
				float ttt=0.0;
				for(c=qq+1; c<=qq+6; c++)
				{
					for(r=1; r<=6; r++)
					{
						ttt += DT[c][r];
						if(DT[c][r]>0.0) xxx++;
					}					
				}		
				if(xxx==0) Save=0.0;
				else Save = ttt/(float)xxx;

				fprintf(Rmax, "%9.2f ", Save);
				qq+=6;
			}
			fprintf(Rmax, "\n");
		}
		fclose(Rmax);
		fclose(TF);
		AfxMessageBox("Done");
}

void CGraphexView::On5minSOIL30minSOIL() 
{
	// TODO: Add your command handler code here
	//Convert a 5-minute map to two 30-minute maps with max and min values
	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3900);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(50,50,50));	

	pDC.SetViewportOrg (5, 10); 
	pDC.SetViewportExt(950, 2450);

	pDC.SetBkMode(TRANSPARENT);	

	pDC.FillSolidRect(45, 195, 1455, 730, RGB(220,220,220));

	char TargetFile[200];
	FILE *TF;

	int RR, BB, GG, r, c, x=0;
	float z=5;
	int d=200, dd=50, w=5, m_Column=720, m_Row;
	char min5_name[100];
	//sprintf(min5_name, "%s", "GlobeCLAY_5min.MAP");
	sprintf(min5_name, "%s", "GlobeSOC_5min.MAP");

		sprintf(TargetFile, "%s\\Database\\Globe\\GlobeData_1_sources\\5minute_maps\\Soil_clay_SOC\\%s", ROOTDIR, min5_name);
			TF=fopen(TargetFile, "r");
			if(TF==NULL)
			{
				CString note;
				note.Format("Cannot open %s", TargetFile);
				AfxMessageBox(note);
				exit(0);
			}

		CString SRmax, SRmin;
		FILE *Rmax, *Rmin;

		SRmax.Format("%s\\Database\\Globe\\Lib_map\\SOCmax.MAP", ROOTDIR);
		Rmax=fopen(SRmax, "w");
		if(Rmax==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SRmax);
			AfxMessageBox(note);
			exit(0);
		}

		SRmin.Format("%s\\Database\\Globe\\Lib_map\\SOCmin.MAP", ROOTDIR);
		Rmin=fopen(SRmin, "w");
		if(Rmin==NULL)
		{
			CString note;
			note.Format("Cannot create %s", SRmin);
			AfxMessageBox(note);
			exit(0);
		}

		float DT[4321][7];

		m_Row = 0;
   		for(int Rr=1; Rr<=360; Rr++)
		{
			for(r=1; r<=6; r++)
			{
				m_Row++;

				for(c=1; c<=m_Column; c++)
				{
					fscanf(TF, "%f", &DT[c][r]);

					if(DT[c][r]<=-9998.0)
					{
						RR=10;GG=90;BB=90;
					}
					else
					{
						Color1(DT[c][r], &RR,&GG,&BB, SelectMap2);				
					}

					pDC.FillSolidRect(dd+(int)(c*z), d+(int)(m_Row*z), w, w, RGB(RR,GG,BB));
				}
			}

			int qq=0;
			float Smax=0.00001;
			float Smin=1000.0;

			for(int pp=1; pp<=720; pp++)
			{
				for(c=qq+1; c<=qq+6; c++)
				{
					for(r=1; r<=6; r++)
					{
						//if(DT[c][r]>0.0)
						{
							Smax = max(DT[c][r], Smax);
							Smin = min(DT[c][r], Smin);
						}
					}					
				}		

				if(Smax>0.0 && Smin <0.0) Smin = Smax * 0.5;

				fprintf(Rmax, "%9.4f ", Smax*0.01);
				fprintf(Rmin, "%9.4f ", Smin*0.01);

				qq+=6;

				Smax=0.00001;
				Smin=1000.0;
			}
			fprintf(Rmax, "\n");
			fprintf(Rmin, "\n");
		}
		fclose(Rmax);
		fclose(Rmin);
		fclose(TF);

}

void CGraphexView::OnUSAdata() 
{
	// TODO: Add your command handler code here
	int i, jd, j=6;
	char TargetFile[200], SourceFile[200], www[300];
	float s1, s2, s3, s4, s5, s6;
	
	FILE *SF, *TF;
	
	sprintf(TargetFile, "%s\\Database\\USA\\GIS\\USA_%d.txt", ROOTDIR, j);
		TF=fopen(TargetFile, "w");
		if(TF==NULL)
		{
			CString note;
			note.Format("Cannot create %s", TargetFile);
			AfxMessageBox(note);
			return;
		}

	for(i=1;i<=56;i++)
	{
		if(i>9) sprintf(SourceFile, "%s\\Database\\USA\\GIS\\USA%d_%d", ROOTDIR, j, i);
		else sprintf(SourceFile, "%s\\Database\\USA\\GIS\\USA%d_0%d", ROOTDIR, j, i);
		
		SF=fopen(SourceFile, "r");
		if(SF==NULL)
		{
			//CString note;
			//note.Format("Cannot open %s", SourceFile);
			//AfxMessageBox(note);			
			goto NNN; //return;
		}
		
		if(j==3||j==4)
		{
			fgets(www, 500, SF);
			fgets(www, 500, SF);
		}

		if(j==4||j==6) 
			{
				fgets(www, 500, SF);
			}

		for(;;)
		{
			//USA_1.txt
			/*if(fscanf(SF, "%d %s %s %f %f", &jd, state, county, &lon, &lat)!=5)
			{
				if(i==65) 
				{
					AfxMessageBox("1 Done");
					exit(0);
				}
				else 
				{
					fclose(SF);
					goto NNN;
				}
			}
			else
			{
				fprintf(TF, "%6d  %15s  %15s  %5.1f  %5.1f\n", jd, state, county, lon, lat);
			}*/

			//USA_2.txt
			/*if(fscanf(SF, "%d %s %f", &jd, state, &AtmoN)!=3)
			{
				if(i==65) 
				{
					AfxMessageBox("1 Done");
					exit(0);
				}
				else 
				{
					fclose(SF);
					goto NNN;
				}
			}
			else
			{
				fprintf(TF, "%6d  %6d.txt  %5.1f\n", jd, jd, AtmoN);
			}*/

			//USA_3.txt
			/*if(fscanf(SF, "%d %f %f %f %f %f %f %f %f", &jd, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8)!=9)
			{
				if(i==65) 
				{
					AfxMessageBox("1 Done");
					exit(0);
				}
				else 
				{
					fclose(SF);
					goto NNN;
				}
			}
			else
			{
				fprintf(TF, "%6d  %8.3f  %8.3f  %8.3f  %8.3f  %8.3f  %8.3f  %8.3f  %8.3f\n", jd, s1, s2, s3, s4, s5, s6, s7, s8);
			}*/

			//USA_4.txt
			/*if(fscanf(SF, "%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", 
				&jd, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10, &s11, &s12, &s13, &s14, &s15, &s16,
				&s17, &s18, &s19, &s20, &s21, &s22, &s23, &s24, &s25, &s26, &s27, &s28, &s29)!=30)
			{
				if(i==65) 
				{
					AfxMessageBox("1 Done");
					exit(0);
				}
				else 
				{
					fclose(SF);
					goto NNN;
				}
			}
			else
			{
				fprintf(TF, "%6d  %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f %8.0f\n", 
					jd, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16,
					s17, s18, s19, s20, s21, s22, s23, s24, s25, s26, s27, s28, s29);
			}*/

			//USA_6.txt
			if(fscanf(SF, "%d %f %f %f %f %f %f", &jd, &s1, &s2, &s3, &s4, &s5, &s6)!=7)
			{
				if(i==65) 
				{
					AfxMessageBox("1 Done");
					exit(0);
				}
				else 
				{
					fclose(SF);
					goto NNN;
				}
			}
			else
			{
				fprintf(TF, "%6d  %8.0f  %8.0f  %8.0f  %8.0f  %8.0f\n", jd, s1, s2, s3, s4, s5);
			}
		}
NNN:;
	}
	fclose(TF);
	AfxMessageBox("2 Done");
}

void CGraphexView::OnDndc1() 
{
	// TODO: Add your command handler code here
	int i, j, GridID, CroppingID;
	char SF[200], TF[200], domain[200], www[300], item[150][150], crop[150];
	float ha, rate[150], sum[150], TotalSum[150], TotalHa;
	CString unit[31]={"", "Unit", "ha","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C","ton_C",
		"ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N","ton_N",
		"million_m3","million_m3","million_m3","million_m3","million_m3","million_m3","million_m3"};

	CString MinMax[2]={"minimum", "maximum"};
	FILE *sf, *tf;
	sprintf(domain, "USA");

	for(i=0; i<=1; i++)
	{
		sprintf(SF, "%s\\GlobeResult\\Rate_%s_%s_nation.txt", ROOTDIR, MinMax[i], domain);
		sf=fopen(SF, "r");
		if(sf==NULL)
		{
			CString note;
			note.Format("Cannot open %s", SF);
			AfxMessageBox(note);
			exit(0);
		}

		sprintf(TF, "%s\\GlobeResult\\Sum_%s_%s_nation.txt", ROOTDIR, MinMax[i], domain);
		tf=fopen(TF, "w");
		if(tf==NULL)
		{
			CString note;
			note.Format("Cannot create %s", TF);
			AfxMessageBox(note);
			exit(0);
		}

		for(j=1;j<=32;j++) 
			fscanf(sf, "%s", item[j]);
		
		fprintf(tf, "%10s ", item[1]);
		for(j=4;j<=32;j++) fprintf(tf, "%15s ", item[j]);
		fprintf(tf, "\n");
		
		fgets(www, 200, sf);
		fgets(www, 200, sf);
		fgets(www, 200, sf);
		
		for(j=1;j<=30;j++) fprintf(tf, "%15s ", unit[j]);  						
		fprintf(tf, "\n");

		GridID = 0;
		int OldID=0;
		int k=0;
		for(;;)
		{	
			k++;

			if(fscanf(sf, "%d %d %s", &GridID, &CroppingID, crop)!=3)
			{
				fprintf(tf, "%10d %10.0f ", OldID, TotalHa);
					for(j=1;j<=28;j++) 
					{
						if(j==3) fprintf(tf, "%15.3f ", TotalSum[j]);
						else if(j<=8||j>=22) fprintf(tf, "%15.0f ", TotalSum[j]);
						else fprintf(tf, "%15.3f ", TotalSum[j]);
						TotalSum[j] = 0.0;
					}
					fprintf(tf, "\n");
				fclose(sf);
				fclose(tf);
				AfxMessageBox("Good");
				break;
			}

			if(k==1)
			{
				for(j=1;j<=28;j++) TotalSum[j] = 0.0;
				TotalHa = 0.0;
			}
			else
			{
				if(GridID!=OldID) 
				{
					fprintf(tf, "%10d %10.0f ", OldID, TotalHa);
					for(j=1;j<=28;j++) 
					{
						if(j==3) fprintf(tf, "%15.3f ", TotalSum[j]);
						else if(j<=8||j>=22) fprintf(tf, "%15.0f ", TotalSum[j]);
						else fprintf(tf, "%15.3f ", TotalSum[j]);
						TotalSum[j] = 0.0;
					}
					fprintf(tf, "\n");					
					TotalHa = 0.0;
				}
			}

			fscanf(sf, "%f", &ha);
			for(j=1;j<=28;j++) fscanf(sf, "%f", &rate[j]);
			
			//if(CroppingID!=105)//exclude grassland from global database
			if(CroppingID!=12)//exclude grassland from USA national database
			{
			//////////////////////////////
			for(j=1;j<=28;j++) 
			{
				if(j==1) sum[j] = rate[j] * ha * 0.001; // total SOC, kg C -> 1000 ton C
				else if(j==2) sum[j] = rate[j] * ha * 0.001; // total dSOC, kg C -> ton C
				else if(j==3) sum[j] = rate[j] * ha * 0.001;//CH4, kg C -> ton C
				else if(j>=4&&j<=8) sum[j] = rate[j] * ha * 0.001; // total C flux, kg C -> ton C
				else if(j>=9&&j<=21) sum[j] = rate[j] * ha * 0.001;// total N flux, kg N -> ton N
				else sum[j] = rate[j] * ha * 10.0 * 0.000001; //water, mm-> million cubic m
				
				TotalSum[j] += sum[j];
			}
			TotalHa += ha;	
			/////////////////////////////
			}

			OldID = GridID;
		}

	}

	AfxMessageBox("Done");
	exit(0);
}

/*void Glean_StringP(char *String, int Num1, int Num2, char *Sub_Str)
// Abstract part of String (from Num1 to Num2) and put to Sub_Str

{
  int i, l;
  l=strlen(String);
  if(Num1>Num2)  {
    //printf("%s\n",String);
    //Hint("Num1>Num2 in Glean_String",String);
    Sub_Str[0]='\0';
    return;
  }
  if (Num1>l) {
    //Hint("Out of range ",String);
    Sub_Str[0]='\0';
    return;
  }
    if (Num2>l)  Num2=l;
    for(i=Num1;i<=Num2;i++)
       Sub_Str[i-Num1]=String[i];
       Sub_Str[i-Num1]='\0';
}*/


void CGraphexView::OnDndcMap() 
{
	// TODO: Add your command handler code here
	DNDC_Map ww;

	if(ww.DoModal()==IDOK)
	{
		
	}
}

void CGraphexView::OnDay1snow() 
{
	// TODO: Add your command handler code here
	CString TF, SF, DF, js;
	char ww[300], region[50];
	int ID1, ID2, jd, SL;
	float jf, SoilT[50], snow;;

	sprintf(region, "%s", "Oceania");

	FILE *tf, *sf, *df;
	SF.Format("%s\\Database\\Globe\\Globe_6.txt", ROOTDIR);

	DF.Format("%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, region, region);
	
	TF.Format("%s\\Database\\Globe\\%s_6.txt", ROOTDIR, region);

	sf=fopen(SF, "r");
	fgets(ww, 300, sf);

	df=fopen(DF, "r");
	fgets(ww, 300, df);

	tf=fopen(TF, "w");

	for(;;)
	{
		if(fscanf(df, "%d %s %d %d %f %f %d %d", &ID1, js, &jd, &jd, &jf, &jf, &jd, &jd)!=8) break;
		
		for(;;)
		{
			fscanf(sf, "%d %f %d", &ID2, &snow, &SL); 
			for(int i=1; i<=SL; i++) fscanf(sf, "%f", &SoilT[i]);

			if(ID2==ID1) 
			{
				fprintf(tf, "%8d %8.4f %2d  ", ID1, snow, SL);
				for(int i=1; i<=SL; i++) fprintf(tf, "%6.2f ", SoilT[i]);
				fprintf(tf, "\n");
				break;
			}
		}
	}

	fclose(sf);
	fclose(tf);
	fclose(df);

	AfxMessageBox("Done");
	
}

void CGraphexView::OnCombineFiles() 
{
	// TODO: Add your command handler code here
	CombineFiles ww;

	if(ww.DoModal()==IDOK)
	{

	}
}



void CGraphexView::OnExtractNation() 
{
	// TODO: Add your command handler code here
	GlobeDataExtract ww;

	if(ww.DoModal()==IDOK)
	{

	}
}

void CGraphexView::OnRegionData() 
{
	// TODO: Add your command handler code here

	OnGlobeDataProcess();

}

void CGraphexView::OnRunMonteCarlo() 
{
	// TODO: Add your command handler code here
	
	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int k, RN1, RN2, RN3, RN4, size;
	float SOC, Clay, pH, BD, LAtitude;
	CString note;
	FILE *mc;
	char ThisName[200], CROPID[100]; 

	note.Format("%s\\Result\\Inter\\MonteCarlo_index", ROOTDIR);
	mc=fopen(note, "r");
	if ( mc == NULL )
	{
		CString mess;
		mess.Format("Can not open %s.", note);
		AfxMessageBox(mess);
		exit(0);
	}
	fscanf(mc, "%d %s %s %f", &size, CROPID, ThisName, &LAtitude);
	fclose(mc);

	if(LAtitude<0.0) LAtitude *= -1.0;

	for(k=1; k<=size; k++)
	{
		note.Format("%s\\Result\\Inter\\Combination_%d", ROOTDIR, k);
		mc=fopen(note, "r");
		if ( mc == NULL )
		{
			CString mess;
			mess.Format("Cannot open %s.", note);
			AfxMessageBox(mess);
			exit(0);
		}
		fscanf(mc, "%f %f %f %f", &SOC, &Clay, &pH, &BD);
		fscanf(mc, "%d %d %d %d", &RN1, &RN2, &RN3, &RN4);
		fclose(mc);

		region_soil_files(1, SOC, SOC, Clay, Clay, pH, pH, BD, BD, 1,
					0, CROPID, 99.9, ThisName, 0, LAtitude, 0.0, 1, 0.0, 0.0);

		CClientDC dc(this);
		link.pWnd = this;
		link.pDC = &dc;
		link.DNDC_or_Other = pDoc->DNDC_or_Other;
		link.StopRun = pDoc->StopRun;
		char FfFf[6][150]={"",""};
#ifdef DEGUI
#else	
		char BatchPass[300]="NULL";
		Model_link(&link, 1, "0", 999, 1, 1, "", "", "", 1.0, 0, 0, 1, 0, 0, 0, 1, 
			0, 0, 1, "", k, 0, 0, "0", 0, 0, 0, FfFf, "0", 4, BatchPass);
		pDoc->DNDC_or_Other = link.DNDC_or_Other;
		pDoc->StopRun = link.StopRun;
#endif
	}


}

void CGraphexView::OnConvertClimateData() 
{
	// TODO: Add your command handler code here
	int i, CN, id, yr, month, day, jd, j;
	float PAR, Tmin, Tmax, Tave, rain, wind, dayl;

	FILE *mc, *mc1;
	char ThisName[200], ThatName[200], ww[300]; 

	//for(i=50136; i<=59954; i++)//China
	for(i=1001; i<=56045; i++)//USA
	{

		sprintf(ThisName, "%s\\Database\\USA\\lib_clim\\2000\\%d.txt", ROOTDIR, i);
		mc=fopen(ThisName, "r");
		if(mc==NULL) 
			goto ccc;
		fgets(ww, 200, mc);//USA

		sprintf(ThatName, "%s\\Database\\USA\\lib_clim\\%d", ROOTDIR, i);
		mc1=fopen(ThatName, "w");
		
		for(j=1; j<=365; j++)
		{
			//fscanf(mc, "%d %d %d %d %f %f %f %f %f %d %f %f", &id, &yr, &month, &day, &PAR, &Tmax, &Tmin, &Tave, &rain, &jd, &wind, &dayl);//China 2000 climate data format
			//fprintf(mc1, "%3d %6.2f %6.2f %6.2f\n", j, Tmax, Tmin, rain*0.1);
			
			fscanf(mc, "%d %f %f %f %f ", &day, &Tmax, &Tmin, &rain, &jd);//USA 2000 climate data format
			fprintf(mc1, "%3d %6.2f %6.2f %6.2f\n", j, Tmax, Tmin, rain);			
			
		}
		fclose(mc);
		fclose(mc1);
ccc:;
	}

	AfxMessageBox("OK");
}

void CGraphexView::OnSnowPack() 
{
	// TODO: Add your command handler code here
	int i, ID, Country, jday;
	char CountryName[200], ClimName[200], WW[300];
	float Lat, Lon, Tmax, Tmin, Tave, rainfall, wind, par, snow_pack, snowfall, SnowMelt;
	char region[200];

	sprintf(region, "%s", "Oceania");

	CString CF, CC, DD;
	FILE* cf, *cc, *dd;
	CF.Format("%s\\Database\\Globe\\%s\\GIS\\%s_1.txt", ROOTDIR, region, region);
	cf=fopen(CF, "r");
	if(cf==NULL) note(0, CF);
	fgets(WW, 300, cf);

	DD.Format("%s\\Database\\Globe\\%s\\GIS\\%s_snow.txt", ROOTDIR, region, region);
	dd=fopen(DD, "w");
	if(dd==NULL) note(1, DD);
	
	for(;;)
	{
		if(fscanf(cf, "%d %d %s %f %f %s", &ID, &Country, CountryName, &Lon, &Lat, ClimName)!=6) break;
		fgets(WW, 300, cf);

		CC.Format("%s\\Database\\Globe\\%s\\lib_clim\\2000\\%s_%s", ROOTDIR, region, region, ClimName);
		cc=fopen(CC, "r");
		if(cc==NULL) note(0, CC);
		fgets(WW, 300, cc);

		snow_pack = 0.0;
		for(i=1; i<=365; i++)
		{
			fscanf(cc, "%d %f %f %f %f %f", &jday, &Tmax, &Tmin, &rainfall, &wind, &par);

			rainfall *= 0.01; //cm->m
			Tave = (Tmax+Tmin) * 0.5;
			SnowMelt = 0.0;

			if ( rainfall > 0.0 && Tave <= 0.0 )
			{
				snowfall = rainfall;
				rainfall = 0.0;  //m
				snow_pack += snowfall; //m water
			}
			
			if ( snow_pack > 0.0 && Tave > 0.0 )
			{	
				SnowMelt = 0.004 * Tave;//0.004
				if ( SnowMelt > snow_pack )
				{
					SnowMelt = snow_pack; //m water
					snow_pack = 0.0;
				}
				else
				{
					snow_pack -= SnowMelt;
				}
			}			
		}

		fclose(cc);

		fprintf(dd, "%d %f\n", ID, snow_pack);
	}

	fclose(dd);
	fclose(cf);

	AfxMessageBox("Snowpack is done");
}


void CGraphexView::OnRunSite(int option, int Monitor, int sample, char *BatchPass) //int option, int Monitor, int sample, char *BatchPass
{	
	int MonteCarlo = 0;//, sample=0;

	if(option>1000000) 
		option=0;
	else if(option>100)
	{
		MonteCarlo = 1;
		sample = option - 100;
	}

	if(Monitor>1000000) Monitor=0;

	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int TotalYears, scale=0;
	char Site[60], junkc[60];
	FILE *FileRun;

if(option!=12345)
{
	sprintf(Site, "%s\\Result\\INPUTS\\Site", ROOTDIR);

	FileRun = fopen(Site, "r");
	if ( FileRun == NULL )
	{
		AfxMessageBox("Can not open file Site");
		return;
	}

	fscanf(FileRun, "%s", junkc);
	fscanf(FileRun, "%d", &TotalYears);
	fclose(FileRun);

	scale = 0;
}
else
{
	scale = 1;
}
	
	pDoc->StopRun = 2;

	CClientDC dc(this);
	link.pWnd = this;
	link.pDC = &dc;
	link.DNDC_or_Other = pDoc->DNDC_or_Other;
	link.StopRun = pDoc->StopRun;

	int livestock = 0;

#ifdef MANURE
	livestock = 1;
#endif

	int DroughtID=0;
	char FfFf[6][150]={"",""};

	if(option==10) DroughtID = 1;
#ifdef DEGUI
#else
	Model_link(&link, scale, "0", 0, 0, TotalYears, "None", "None","None", 0.0, 0, 0, 0, 0, 0, 1, 
		MonteCarlo, 0, option, 1, "None", sample, 0, 0, "0", livestock, Monitor, DroughtID, FfFf, 
		"0", 4, BatchPass);
	pDoc->DNDC_or_Other = link.DNDC_or_Other;
	pDoc->StopRun = link.StopRun;
#endif

//#ifdef MANURE
	//AfxMessageBox("The simulation is accomplished");
	//exit(0);
//#endif
}

void CGraphexView::OnRunRegion() 
{
	int Monitor=0;
	dndc74 start;

//#ifdef UNIX	
//	start.dndc_region();
//#endif

	ScreenMonitor ww;
	if(ww.DoModal()==IDOK)
	{
		Monitor=0;
	}
	else
	{
		Monitor=1;
	}

	CGraphexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->StopRun = 2;

	CClientDC dc(this);
	link.pWnd = this;
	link.pDC = &dc;
	link.DNDC_or_Other = pDoc->DNDC_or_Other;
	link.StopRun = pDoc->StopRun;

	start.dndc_region(&link, pDoc, Monitor);

	pDoc->DNDC_or_Other = link.DNDC_or_Other;
	pDoc->StopRun = link.StopRun;
}



void CGraphexView::OnSiteModeTest() 
{
	// TODO: Add your command handler code here
	char SF[200], DF[200], BatchPass[300]="NULL";

	sprintf(SF, "%s\\Result\\Inputs\\Soil-A1", ROOTDIR);
	sprintf(DF, "%s\\Result\\Inputs\\Soil-1", ROOTDIR);

	FileCopy(SF, DF);
	
	OnRunSite(3, 0, 0, BatchPass); 
}

void CGraphexView::OnGlobeDataProcess() 
{
	// TODO: Add your command handler code here
	OnDndcMap();
}

void CGraphexView::OnYieldPredict() 
{
	// TODO: Add your command handler code here
	Dndc_YieldPredict ww;
	if(ww.DoModal()==IDOK)
	{
		//CString CropName[5]={"","Corn","SpringWheat","Rice","Soybean"};
		int Site, YieldYear, YieldToday, YieldCrop,YieldMonth, YieldDay;
		char CountyName[100], CropName[50],  CropCode[50], BatchPass[300];
		CString YF;
		FILE* yf;
		YF.Format("%s\\YieldPrediction", INTER);
		yf=fopen(YF, "r");
		if(yf==NULL) note(0,YF);

		fscanf(yf, "%d %d %d %d %s %d %d %s %s", 
			&Site, &YieldCrop, &YieldYear, &YieldToday, CountyName,&YieldMonth, &YieldDay, CropName, CropCode);
		fclose(yf);

		////////////////////////////////////////////////////////////////////////////////////////
		if(Site==60000) //Run region
		{
			OnRunRegion();
		}
		else
		{
		/////////////////////////////////////////////////////////////////////////////////////
			sprintf(DndFileName, "%s\\Database\\%s\\%s\\%s_%s_%d_%d.dnd", ROOTDIR, "", CountyName, CountyName, CropName, YieldYear-1, YieldYear);

			ReadInputDatafromDND(DndFileName, 10);
				
			ReadSoilFeature("UnDefault");
				
			CreateInputFiles(0, 10, "China", 1);//Drought run

			OnRunSite(10, 0, 0, BatchPass);// Option 10: drought runs

		}
	}

	OnYieldShow();
}

void CGraphexView::OnYieldShow() 
{
	// TODO: Add your command handler code here
	DrawDrought wwc;

	if(wwc.DoModal()==IDOK)
	{
		
	}
}

void CGraphexView::OnLiaoning() 
{
	// TODO: Add your command handler code here
	CString DM;
	FILE *dm;
	DM.Format("%s\\DroughtMode", INTER);
	dm=fopen(DM, "w");
	fprintf(dm, "%d", 1);
	fclose(dm);

	RegionInput dlg;
	if(dlg.DoModal()==IDOK)
	{
		//UpdateData(FALSE);
	}
	//AfxMessageBox("!!");
}

void CGraphexView::OnYieldReSet() 
{
	// TODO: Add your command handler code here
	Dndc_YieldPredict dlg;
	if(dlg.DoModal()==IDOK)
	{
		//UpdateData(FALSE);
	}
}

void CGraphexView::OnSaveSoilFile() 
{
	// TODO: Add your command handler code here
	SaveSoilYear ww;
	if(ww.DoModal()==IDOK)
	{


	}
}


void CGraphexView::OnLinux() 
{
	// TODO: Add your command handler code here
#ifdef DEGUI	
	OpenSesame();
#else
	AfxMessageBox("Nothing done");
#endif

}


void CGraphexView::OnGateTest() 
{
	// TODO: Add your command handler code here
	CFileDialog ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.dnd)|*.dnd|All files (*.*)|*.*||", NULL );

	ask.DoModal();
	char cst[255];
	strcpy(cst,ask.GetPathName());
	if (strlen(cst)==0) return;

#ifdef DEGUI	//CreateDndcInputFiles(cst);
	OpenSesame();
#endif
	//OnRunSite(0, 0, 0);
	exit(0);
}

void CGraphexView::OnFarmCompost() 
{
	// TODO: Add your command handler code here
	FarmCompost ww;
	if(ww.DoModal()==IDOK)
	{


	}
}

void CGraphexView::OnRunFarmComponent() 
{
	// TODO: Add your command handler code here
	char BatchPass[300]="NULL";

	OnRunSite(12345, 1, 1, BatchPass);//int option, int Monitor, int sample) 

	//AfxMessageBox("Good");

	exit(0);
	
}

void CGraphexView::OnFarmLagoon() 
{
	// TODO: Add your command handler code here
	FarmLagoon ww;
	if(ww.DoModal()==IDOK)
	{


	}
}
