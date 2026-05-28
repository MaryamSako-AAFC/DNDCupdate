// SelectShapeMap.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "SelectShapeMap.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char ShapeFileName[255];
char FileName[255][200];
/////////////////////////////////////////////////////////////////////////////
// SelectShapeMap dialog


SelectShapeMap::SelectShapeMap(CWnd* pParent /*=NULL*/)
	: CDialog(SelectShapeMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectShapeMap)
	m_LayerNumber = 1;
	//}}AFX_DATA_INIT
}


void SelectShapeMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectShapeMap)
	DDX_Control(pDX, IDC_ShapeFileList, m_ShapeFileList);
	DDX_Text(pDX, IDC_LayerNumber, m_LayerNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectShapeMap, CDialog)
	//{{AFX_MSG_MAP(SelectShapeMap)
	ON_BN_CLICKED(IDC_SelectShapeFile, OnSelectShapeFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectShapeMap message handlers

void SelectShapeMap::OnSelectShapeFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_LayerNumber>2) m_LayerNumber=2;

	UpdateData(FALSE);

	CString cst;
	static int ww=0;
	ww++;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_ShapeFileList.GetCount();
	if (num==m_LayerNumber) return;
	
	k=m_ShapeFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	int i=0;
	for (;;)
	{
		i++;
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(ShapeFileName,cst);
		m_ShapeFileList.InsertString(k,ShapeFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ShapeFileList.GetCount()==m_LayerNumber) break;
		k++;
	}
	m_ShapeFileList.SetCurSel(k);

	sprintf(FileName[ww], "%s", cst);
}

void SelectShapeMap::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString SF;
	FILE* sf;
	SF.Format("%s\\Inter\\MapFile.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", SF);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(sf, "%d\n", m_LayerNumber);
	for(int i=1; i<=m_LayerNumber; i++)
	{
		fprintf(sf, "%s\n", FileName[i]);
	}
	fclose(sf);
	
	CDialog::OnOK();
}
