// graphexDoc.cpp : implementation of the CGraphexDoc class
//
#include <afx.h>
#include "stdafx.h"
#include "dndc71.h"//graphex.h"
#include "MainFrm.h"
#include <afxwin.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include "SitePara.h"
#include "graphexDoc.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


RECT Seen;

extern Site_BaseInformation	IData;

float Xrange[]={-180,180,0,0},Yrange[]={0,90,0,0};

/////////////////////////////////////////////////////////////
// CGraphexDoc

IMPLEMENT_DYNCREATE(CGraphexDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphexDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphexDoc)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphexDoc construction/destruction

CGraphexDoc::CGraphexDoc()
{
	
}


CGraphexDoc::~CGraphexDoc()
{
	
}

BOOL CGraphexDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	if (Lindex!=0) {ClearAct();return TRUE;}

	Lindex=0;				//initial the count of draw action
	AllOrLast=0;
	Fontype=1;				//set font type
	Ftscale=float(0.9);		//set the scale of font size

	int i,fsize,dy;
	int by  =int(MapHigh *0.008),dis=int(MapHigh *0.195);
	int high=int(MapHigh *0.186),bx =int(MapWidth*0.23);

	figWidth=int(MapWidth*(0.996-0.23)*0.79);//
	ydis=float(figWidth/368.);

		//climate,Crop,Soil,Gas1,Gas2
	for (i=0;i<5;i++) {
			//set the box range of each curve area
		BoxRange[i].top    = int(by+i*dis); 
		BoxRange[i].bottom = int(by+i*dis+high);
		BoxRange[i].left   = int(bx);
		BoxRange[i].right  = int(MapWidth*0.996);

			//set the box range of the draw area
		BoxRange[10+i*2].top      = int(by+i*dis+high*0.01);
		BoxRange[10+i*2].bottom   = int(by+i*dis+high*0.99);
		BoxRange[10+i*2].left     = int(bx+ydis);
		BoxRange[10+i*2].right    = int(bx+figWidth);

			//set the box range of the legend
		BoxRange[10+i*2+1].top    = int(by+i*dis+high*0.05);
		BoxRange[10+i*2+1].bottom = int(by+i*dis+high*0.99);
		BoxRange[10+i*2+1].left	  = int(bx+figWidth);
		BoxRange[10+i*2+1].right  = int(MapWidth*0.996);
	}
	//figWidth=int((BoxRange[0].right-BoxRange[0].left)*0.79);


		//note of daily cycle
	fsize=int(18*Ftscale*MapHigh/480);
	bx=int(BoxRange[5].left+(BoxRange[5].right-BoxRange[5].left)/40);
	high=(BoxRange[5].bottom-BoxRange[5].top)/45;
	dy=BoxRange[5].top+high;
	BoxRange[10+5*2].top	= int(fsize+dy);
	BoxRange[10+5*2].bottom = int(2*fsize+dy);
	BoxRange[10+5*2].left	= int(bx); 
	BoxRange[10+5*2].right  = int(BoxRange[5].right*0.98);

	BoxRange[10+5*2+1].top    = int(2.3*fsize+dy); 
	BoxRange[10+5*2+1].bottom = int(by+MapHigh*0.44);
	BoxRange[10+5*2+1].left   = int(bx);
	BoxRange[10+5*2+1].right  = int(BoxRange[5].right*0.98);

		//Soil C/N Profile
	BoxRange[6].top		= int(MapHigh *0.455); 
	BoxRange[6].bottom	= int(by+MapHigh*(0.99));
	BoxRange[6].left	= int(MapWidth*0.005); 
	BoxRange[6].right	= int(MapWidth*0.225);
		
	bx=int(BoxRange[6].left+(BoxRange[6].right-BoxRange[6].left)*0.02);
	high=(BoxRange[6].bottom-BoxRange[6].top)/45;
	dy=BoxRange[6].top+high;
		//title area
	BoxRange[10+6*2].top	= dy;
	BoxRange[10+6*2].bottom = int(fsize+dy);
	BoxRange[10+6*2].left	= int(bx);		   
	BoxRange[10+6*2].right  = int(BoxRange[6].right*0.98);
		//profile area
	BoxRange[10+6*2+1].top	  = int(dy+fsize); 
	BoxRange[10+6*2+1].bottom = int(by+MapHigh*0.98);
	BoxRange[10+6*2+1].left   = int(bx);
	BoxRange[10+6*2+1].right  = int(bx+(BoxRange[10+6*2].right-BoxRange[10+6*2].left)*2/3);
		//Legend area
	BoxRange[10+6*2+2].top	  = int(dy);//+fsize); 
	BoxRange[10+6*2+2].bottom = int(by+MapHigh*0.98);
	BoxRange[10+6*2+2].left   = BoxRange[10+6*2+1].right+1;
	BoxRange[10+6*2+2].right  = BoxRange[10+6*2].right;




	bx=int(MapWidth*0.01);
		//annotation area
	MapR[1].left   = bx;
	MapR[1].right  = int(MapWidth-bx);
	MapR[1].top    = by;
	MapR[1].bottom = (long)(by+2.2*fsize);//+high
		//map area
	MapR[2].left   = bx;
	MapR[2].right  = int(MapWidth-bx);
	MapR[2].top    = MapR[1].bottom+high;
	MapR[2].bottom = MapHigh-high;

	//fsize=SetFontSize(16);
	//3-4:province, 5-6 :county, 7-8 :longitude,9-10:latitude,
	//11-12:crop,  13-14:SOC,   15-16:C
	int mi,mk,ml,mh;
	ml = (MapR[1].Width()-8*(fsize/2))/7;//right-MapR[1].left
	mh = (fabsf(MapR[1].Height())-2*fsize)/3;//bottom-MapR[1].top
	for (i=1;i<=7;i++) 
	{
		mi = i*2+1;
		MapR[mi].left   = MapR[1].left+i*(fsize/2)+(i-1)*ml;
		MapR[mi].right  = MapR[mi].left+ml;//
		MapR[mi].top    = MapR[1].top+mh;
		MapR[mi].bottom = MapR[mi].top+fsize;

		mk=mi+1;
		MapR[mk].left   = MapR[mi].left;
		MapR[mk].right  = MapR[mi].right;
		MapR[mk].top    = MapR[mi].bottom+mh;//MapR[mi].bottom+high;
		MapR[mk].bottom = MapR[mk].top+fsize;
	}
		//17:index name
	MapR[17].left  = MapR[2].left+fsize/4;
	MapR[17].right = int(MapWidth/6);
	MapR[17].top   = MapR[2].top +high;
	MapR[17].bottom= MapR[17].top+fsize;

		//18:plant work
	MapR[18].left  = int(MapWidth*0.85);
	MapR[18].right = MapR[2].right-bx;//int(MapWidth*0.99);
	MapR[18].top   = MapR[2].top+high;
	MapR[18].bottom= MapR[18].top+fsize;

	MapR[19].left  = int(MapWidth*0.85);
	MapR[19].right = MapR[2].right-bx;//int(MapWidth*0.99);
	MapR[19].top   = MapR[18].bottom+high;
	MapR[19].bottom= MapR[19].top+fsize;

		//legend
	MapR[21].left  = MapR[2].left;
	MapR[21].right = long(MapR[2].left+MapWidth*0.1);
	MapR[21].top   = MapR[2].top;//MapR[17].bottom+high;
	MapR[21].bottom= MapR[2].bottom;

		//Map-area
	int ht,wt;
	ht = fabsf(MapR[2].top-MapR[2].bottom);
	wt = MapR[2].right-MapR[21].right;
	if ((float)wt/ht>640./480.) wt=ht*640/480;
	else ht=480*wt/640;
	MapR[20].left  = MapR[2].right-wt;
	MapR[20].right = MapR[2].right;
	MapR[20].top   = MapR[2].top;
	MapR[20].bottom= MapR[2].top+ht;


		//Map title show
	MapR[30]	   = MapR[3];
	MapR[30].right = int(MapWidth*0.5);
	MapR[30].bottom= MapR[30].top+int(1.2*fsize);

	MapR[31].left  = int(MapWidth*0.6);
	MapR[31].right = MapWidth-fsize;
	MapR[31].top   = MapR[3].top;
	MapR[31].bottom= MapR[3].top+int(1.2*fsize);

	MapR[33]	   = MapR[30];
	MapR[33].top   = MapR[30].top;

		//Show_Map area
	MapR[32]	   = MapR[2];
	MapR[32].top   = MapR[30].bottom+(int)(0.5*fsize);
	//MapR[32].bottom= MapR[32].top+fsize;
	
		//title of the Map legend
	MapR[35]	   = MapR[17];
	MapR[35].top   = MapR[32].top+fsize/4;
	MapR[35].bottom= MapR[35].top+(int)(fsize);

		//color bar area of show_map
	MapR[36]	   = MapR[21];
	MapR[36].top   = MapR[35].bottom+fsize/4;

		// show_map area
	MapR[37]	   = MapR[20];
	MapR[37].top   = MapR[32].top;
	
		//Map Area Parameter
	Seen.left = 15;
	Seen.right= 622;
	Seen.top  = 474;
	Seen.bottom = 80;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphexDoc serialization

void CGraphexDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	//fView_frame();
}


void CGraphexDoc::DeleteContents()
{
	ClearAct();
}

int CGraphexDoc::ClearAct()
{
	int index;
	index=m_ObArray.GetSize ();
	while (index--) {
	//	if (GetLine(index)->what==0 && GetLine(index)->text!=NULL) 
	//		delete [] GetLine(index)->text;
		delete m_ObArray.GetAt(index);
	}

	m_ObArray.RemoveAll ();
	Lindex=0;
	return (0);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphexDoc diagnostics

#ifdef _DEBUG
void CGraphexDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphexDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CGraphexDoc commands

void CGraphexDoc::OnEditUndo() 
{
	// TODO: Add your command handler code here
	int index;
	index=m_ObArray.GetUpperBound ();
	if (index>=0) 
	{
		delete m_ObArray.GetAt(index);
		m_ObArray.RemoveAt(index);
	}
	UpdateAllViews(NULL);
}

void CGraphexDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ObArray.GetSize());
}



/*void CGraphexDoc::IfStop()
{
	POSITION pos = GetFirstViewPosition();
	CView* pDC = GetNextView( pos );
	CClientDC dc(pDC);

	MSG message;
	if (::PeekMessage(&message,NULL,0,0,PM_REMOVE)) {
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}

}*/

BOOL CGraphexDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	exit(0);
	if (StopRun !=0) {
		MessageBox(NULL,"Please Stop to run DNDC at first!","Error Warning:",NULL);
		return FALSE;
	}
	
	return CDocument::SaveModified();
}
