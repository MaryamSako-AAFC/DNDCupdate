// dndc_save.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_save.h"
#include "SitePage1.h"

#include "SitePara.h"
#include "SitePage1.h"
#include "dndc_main.h"
#include "SitePage3.h"
#include "ListFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CropArray			Crop;
extern Site_BaseInformation	IData;
extern StringArray			ClimateFilename;
extern StringArray			LaiFilename;
extern CropProperty CropPty;
extern CropofEachYear CYr[2];
char * EraseSpaceB(char *str);

/////////////////////////////////////////////////////////////////////////////
// dndc_save property page

IMPLEMENT_DYNCREATE(dndc_save, CPropertyPage)

dndc_save::dndc_save() : CPropertyPage(dndc_save::IDD)
{
	//{{AFX_DATA_INIT(dndc_save)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

dndc_save::~dndc_save()
{
}

void dndc_save::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dndc_save)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dndc_save, CPropertyPage)
	//{{AFX_MSG_MAP(dndc_save)
	ON_BN_CLICKED(ID_SAVESITE, OnSavesite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dndc_save message handlers

void dndc_save::OnSavesite() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CFileDialog ask(false, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.dnd)|*.dnd|All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();
	char cst[255];

	CString fname;
	int l, rrr, yyy;
	fname = ask.GetPathName();
	l=fname.GetLength();
	if (l==0) return;

	if (fname.Right(4)!=".dnd") fname=fname+".dnd";
	sprintf(cst,"%s",fname);

	NewSaveDatatoFile(cst, 1); 
	//SaveDatatoFile(cst, 1);
}
