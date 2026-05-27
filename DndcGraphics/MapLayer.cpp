// MapLayer.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "MapLayer.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char LayerFileName[200];

/////////////////////////////////////////////////////////////////////////////
// MapLayer dialog


MapLayer::MapLayer(CWnd* pParent /*=NULL*/)
	: CDialog(MapLayer::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapLayer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MapLayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapLayer)
	DDX_Control(pDX, IDC_MapLayer, m_MapLayer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MapLayer, CDialog)
	//{{AFX_MSG_MAP(MapLayer)
	ON_BN_CLICKED(IDC_SelectFile, OnSelectFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MapLayer message handlers

void MapLayer::OnSelectFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString cst;
	
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );

	if(ask.DoModal()==IDOK)
	{
		
	}
	else
		return;
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_MapLayer.GetCount();
	if (num==1) return;
	
	k=m_MapLayer.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(LayerFileName,cst);
		m_MapLayer.InsertString(k,LayerFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_MapLayer.GetCount()==1) break;
		k++;
	}
	m_MapLayer.SetCurSel(k);
	
}

void MapLayer::OnOK() 
{
	// TODO: Add extra validation here
	CString Fregion;
	FILE *region;

	Fregion.Format("%s\\Inter\\MapLayerList.txt", OUTPUT);
	region = fopen(Fregion, "w");

	if (region==NULL)
	{
		char err[120];
		sprintf(err, "Can not create %s", Fregion);
		AfxMessageBox(err);
		exit(0); 
	}

	fprintf(region, "%s\n", LayerFileName);
	
	fclose (region);
	
	CDialog::OnOK();
}
