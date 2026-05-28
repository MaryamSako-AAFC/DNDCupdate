// SaveSoilYear.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "SaveSoilYear.h"
#include "dndc_tool.h"
#include "dndc_main.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SaveSoilYear dialog


SaveSoilYear::SaveSoilYear(CWnd* pParent /*=NULL*/)
	: CDialog(SaveSoilYear::IDD, pParent)
{
	//{{AFX_DATA_INIT(SaveSoilYear)
	m_SoilYear = 0;
	//}}AFX_DATA_INIT
}


void SaveSoilYear::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SaveSoilYear)
	DDX_Control(pDX, IDC_SoilStatusList, m_SoilStatusList);
	DDX_Text(pDX, IDC_SoilYear, m_SoilYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SaveSoilYear, CDialog)
	//{{AFX_MSG_MAP(SaveSoilYear)
	ON_BN_CLICKED(ID_SaveSoil, OnSaveSoil)
	ON_BN_CLICKED(IDC_SoilStatusFile, OnSoilStatusFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SaveSoilYear message handlers

void SaveSoilYear::OnSaveSoil() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int l;
	char ss1[255], ss2[200];

	if(m_SoilYear==0||m_SoilYear>1000)
	{
		AfxMessageBox("Please enter the order number of your target year");
		return;
	}

	int yyr;
	yyr = m_SoilYear+1;

	//CFileDialog ask(false, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "All Files (*.*)|*.*|Soil Files (*.sol)|*.sol||", NULL );
	CFileDialog ask(false, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC soil file (*.sol)|*.sol|All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );

	ask.DoModal();	
	CString ffname;	
	ffname = ask.GetPathName();
	l=ffname.GetLength();
	if (l==0) return;

	if (ffname.Right(4)!=".sol") ffname=ffname+".sol";
	sprintf(ss1,"%s",ffname);

	sprintf(ss2, "%s\\Inputs\\soil-%d", OUTPUT, yyr);
	FileCopy(ss2, ss1);

}

void SaveSoilYear::OnSoilStatusFile() 
{
	// TODO: Add your control notification handler code here
	char FileName[255];
	CString cst;

	CFileDialog ask(false, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC soil file (*.sol)|*.sol|All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );

	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_SoilStatusList.GetCount();
	if (num==1) return;
	
	k=m_SoilStatusList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_SoilStatusList.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_SoilStatusList.GetCount()==1) break;
		k++;
	}
	m_SoilStatusList.SetCurSel(k);

	sprintf(FileName, "%s", cst);

	char SYF[200];
	sprintf(SYF, "%s\\Inputs\\soil-1", OUTPUT);
	FileCopy(FileName, SYF);

	FILE* sni;
	sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
	sni=sopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 2);
	fclose(sni);

}
