// SelectIrriFile.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "SelectIrriFile.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectIrriFile dialog


SelectIrriFile::SelectIrriFile(CWnd* pParent /*=NULL*/)
	: CDialog(SelectIrriFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectIrriFile)
	//}}AFX_DATA_INIT
}


void SelectIrriFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectIrriFile)
	DDX_Control(pDX, IDC_IrriFileList, m_IRRI);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectIrriFile, CDialog)
	//{{AFX_MSG_MAP(SelectIrriFile)
	ON_BN_CLICKED(IDC_SelectAFile, OnSelectAFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectIrriFile message handlers

void SelectIrriFile::OnSelectAFile() 
{
	// TODO: Add your control notification handler code here
	CString cst;
	char GlobeFileName[400];

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_IRRI.GetCount();
	if (num==1) return;
	
	k=m_IRRI.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		int ll=strlen(cst);

		if (cst=="") break;
	
		strcpy(GlobeFileName,cst);
		m_IRRI.InsertString(k,GlobeFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_IRRI.GetCount()==1) break;
		k++;
	}
	m_IRRI.SetCurSel(k);

	char SFF[200];
	FILE *sff;
	sprintf(SFF, "%s\\Result\\Inter\\IrriFileReview", ROOTDIR);

	sff=fopen(SFF, "w");
	if(sff==NULL) note(1, SFF);
	
	fprintf(sff, "%s\n", GlobeFileName);
	
	fclose(sff);
}
