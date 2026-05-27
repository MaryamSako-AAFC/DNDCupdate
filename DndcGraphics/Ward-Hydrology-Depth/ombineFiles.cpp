// ombineFiles.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ombineFiles.h"
#include "SitePara.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern StringArray			ClimateFilename;
/////////////////////////////////////////////////////////////////////////////
// CombineFiles dialog


CombineFiles::CombineFiles(CWnd* pParent /*=NULL*/)
	: CDialog(CombineFiles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CombineFiles)
	m_Files = 0;
	m_newfile = _T("");
	//}}AFX_DATA_INIT
}


void CombineFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CombineFiles)
	DDX_Control(pDX, IDC_FileList, m_FileList);
	DDX_Text(pDX, IDC_Files, m_Files);
	DDX_Text(pDX, IDC_NewFile, m_newfile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CombineFiles, CDialog)
	//{{AFX_MSG_MAP(CombineFiles)
	ON_BN_CLICKED(IDC_SelClimateFile, OnSelClimateFile)
	ON_BN_CLICKED(IDC_MoveDown, OnMoveDown)
	ON_BN_CLICKED(IDC_MoveUp, OnMoveUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CombineFiles message handlers

void CombineFiles::OnSelClimateFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_Files<=0) {
		MessageBox("Please input the number of files to be combined","Input Error:",NULL);
		return;
	}

	CString cst;
	char FileName[255];

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_FileList.GetCount();
	if (num==m_Files) return;
	
	k=m_FileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_FileList.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_FileList.GetCount()==m_Files) break;
		k++;
	}
	m_FileList.SetCurSel(k);

}

void CombineFiles::OnMoveDown() 
{
	// TODO: Add your control notification handler code here
	int num,selfile;
	num=m_FileList.GetCount();
	selfile=m_FileList.GetCurSel();
	
	char tmp[255],tmp1[255];
	if (selfile<num-1 && selfile>=0) {
		m_FileList.GetText(selfile,tmp);
		m_FileList.GetText(selfile+1,tmp1);
		m_FileList.DeleteString(selfile);
		m_FileList.InsertString(selfile+1,tmp);
	}
}

void CombineFiles::OnMoveUp() 
{
	// TODO: Add your control notification handler code here
	int num,selfile;
	num=m_FileList.GetCount();
	selfile=m_FileList.GetCurSel();
	
	char tmp[255],tmp1[255];
	if (selfile<=num-1 && selfile>0) {
		m_FileList.GetText(selfile,tmp);
		m_FileList.GetText(selfile-1,tmp1);
		m_FileList.DeleteString(selfile);
		m_FileList.InsertString(selfile-1,tmp);
	}
}

void CombineFiles::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int i, num;
	char fname[255], st[255];

	num = m_Files;

	ClimateFilename.clear ();
	for (i=1;i<=num;i++) {
		m_FileList.GetText(i-1,fname);
		strcpy(st,fname);
		ClimateFilename.insert(i,st);
	}
	//IData.ClimateFileNumber= ClimateFilename.n;

	CString FileRecord;
	FileRecord.Format("%s\\Inter\\FileCombine", OUTPUT);
	FILE* fr;
	fr=fopen(FileRecord, "w");
	if(fr==NULL)
	{
		CString note;
		note.Format("Cannont create file %s", FileRecord);
		AfxMessageBox(note);
		exit;
	}

	fprintf(fr,"%d\n", num);
	for(i=1; i<=num; i++)
		fprintf(fr,"%s\n",ClimateFilename.get(i));

	fclose(fr);

	char NewFile[255], OldFile[255];
	FILE *nf, *of;

	sprintf(NewFile, "%s\\%s", ROOTDIR, m_newfile);
	nf=fopen(NewFile, "w");
	if(nf==NULL)
	{
		CString note;
		note.Format("Cannont create file %s", NewFile);
		AfxMessageBox(note);
		exit;
	}

	for(i=1; i<=num; i++)
	{
		sprintf(OldFile, "%s", ClimateFilename.get(i));
		
		if(i==1) FileCopy(OldFile, NewFile);
		else FileExpend(OldFile, NewFile);
	}

	fclose(nf);

	CDialog::OnOK();
}
