// ListFile.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ListFile.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString cst;
/////////////////////////////////////////////////////////////////////////////
// CListFile dialog


CListFile::CListFile(CWnd* pParent /*=NULL*/)
	: CDialog(CListFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CListFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListFile)
	DDX_Control(pDX, IDC_ClimateFileListB, m_ClimateFileListB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListFile, CDialog)
	//{{AFX_MSG_MAP(CListFile)
	ON_BN_CLICKED(IDC_SelClimateFileB, OnSelClimateFileB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListFile message handlers

void CListFile::OnSelClimateFileB() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char FileName[255];
	

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_ClimateFileListB.GetCount();
	if (num==1) return;
	
	k=m_ClimateFileListB.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_ClimateFileListB.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ClimateFileListB.GetCount()==1) break;
		k++;
	}
	m_ClimateFileListB.SetCurSel(k);
}

void CListFile::OnOK() 
{
	// TODO: Add extra validation here
	CString CFN;
	FILE *cfn;
	CFN.Format("%s\\Inter\\ClimateFileList", OUTPUT);
	cfn=fopen(CFN, "w");
	if(cfn==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", CFN);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(cfn, "%s", cst);
	fclose(cfn);
	
	CDialog::OnOK();
}
