// FarmCompost.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "FarmCompost.h"
#include "dndc_main.h"
#include "SitePara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char FarmFName[500], FarmMName[500];
/////////////////////////////////////////////////////////////////////////////
// FarmCompost dialog


FarmCompost::FarmCompost(CWnd* pParent /*=NULL*/)
	: CDialog(FarmCompost::IDD, pParent)
{
	//{{AFX_DATA_INIT(FarmCompost)
	m_CompostMethod = 0;
	m_latitude = 0.0f;
	m_Poro = 0.0f;
	m_CompostPH = 0.0f;
	//}}AFX_DATA_INIT
}


void FarmCompost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FarmCompost)
	DDX_Control(pDX, IDC_ManaFileList, m_ManaFileList);
	DDX_Control(pDX, IDC_ClimFileList, m_ClimFileList);
	DDX_Radio(pDX, IDC_CompostMethod, m_CompostMethod);
	DDX_Text(pDX, IDC_Latitude, m_latitude);
	DDX_Text(pDX, IDC_Poro, m_Poro);
	DDX_Text(pDX, IDC_CompostPH, m_CompostPH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FarmCompost, CDialog)
	//{{AFX_MSG_MAP(FarmCompost)
	ON_BN_CLICKED(IDC_SelGisFile, OnSelClimFile)
	ON_BN_CLICKED(IDC_SelGisFile2, OnSelGisFile2)
	ON_BN_CLICKED(IDC_CompostMethod, OnCompostMethod)
	ON_BN_CLICKED(IDC_CompostSave, OnCompostSave)
	ON_BN_CLICKED(IDC_CompostOpen, OnCompostOpen)
	ON_LBN_DBLCLK(IDC_ClimFileList, OnDblclkClimFileList)
	ON_LBN_DBLCLK(IDC_ManaFileList, OnDblclkManaFileList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FarmCompost message handlers

void FarmCompost::OnSelClimFile() 
{
	// TODO: Add your control notification handler code here
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
	num=m_ClimFileList.GetCount();
	if (num==1) return;
	
	k=m_ClimFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy( FarmFName,cst);
		m_ClimFileList.InsertString(k, FarmFName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ClimFileList.GetCount()==1) break;
		k++;
	}
	m_ClimFileList.SetCurSel(k);

}

void FarmCompost::OnSelGisFile2() 
{
	// TODO: Add your control notification handler code here
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
	num=m_ManaFileList.GetCount();
	if (num==1) return;
	
	k=m_ManaFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy( FarmMName,cst);
		m_ManaFileList.InsertString(k, FarmMName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ManaFileList.GetCount()==1) break;
		k++;
	}
	m_ManaFileList.SetCurSel(k);
}

void FarmCompost::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString FCF;
	FILE *fcf;
	FCF.Format("C:\\%s\\FarmCompostPara", INTER);
	fcf=fopen(FCF, "w");
	fprintf(fcf, "%s\n",  FarmFName);
	fprintf(fcf, "%s\n",  FarmMName);
	fprintf(fcf, "%d %f %f %f\n",  m_CompostMethod+1, m_latitude, m_Poro, m_CompostPH);
	fclose(fcf);

	char SYF[200];
	FILE* sni;
	sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
	sni=sopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 3);
	fclose(sni);

	SaveClimateFileOfAYear(1, FarmFName, m_latitude,
			1, 0.0, 0.0, 370.0, "Check", 0, 0.0, 0, "r_Country");
	
	CDialog::OnOK();
}

void FarmCompost::OnCompostMethod() 
{
	// TODO: Add your control notification handler code here
	
}

void FarmCompost::OnCompostSave() 
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

	FILE *cif;
	cif=fopen(cst, "w");
	if(cif==NULL) note(1, cst);
	fprintf(cif, "Compost_input_data\n");
	fprintf(cif, "Latitude: %f\n", m_latitude);
	fprintf(cif, "Climate_file_name: %s\n", FarmFName);
	fprintf(cif, "Management_file_name: %s\n", FarmMName);
	fprintf(cif, "Compost_porosity: %f\n", m_Poro);
	fprintf(cif, "Compost_coverage: %d\n", m_CompostMethod+1);
	fprintf(cif, "Compost_pH: %f\n", m_CompostPH);
	fclose(cif);

}

void FarmCompost::OnCompostOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.dnd)|*.dnd|All files (*.*)|*.*||", NULL );

	ask.DoModal();
	char cst[255], js[100];
	strcpy(cst,ask.GetPathName());
	if (strlen(cst)==0) return;

	FILE *cif;
	cif=fopen(cst, "r");
	if(cif==NULL) note(1, cst);
	fscanf(cif, "%s", js);
	fscanf(cif, "%s %f", js, &m_latitude);
	fscanf(cif, "%s %s\n", js, FarmFName);
	fscanf(cif, "%s %s\n", js, FarmMName);
	fscanf(cif, "%s %f\n", js, &m_Poro);
	fscanf(cif, "%s %d\n", js, &m_CompostMethod);
	fscanf(cif, "%s %f\n", js, &m_CompostPH);
	fclose(cif);

	m_CompostMethod--;

	m_ClimFileList.InsertString(0, FarmFName);

	m_ManaFileList.InsertString(0, FarmMName);	

	
	UpdateData(FALSE);
}

void FarmCompost::OnDblclkClimFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;	
	num=m_ClimFileList.GetCount();
	i=m_ClimFileList.GetCurSel();	
	CString fname;
	m_ClimFileList.GetText(i,fname);
	m_ClimFileList.DeleteString(i);	
	return;
}

void FarmCompost::OnDblclkManaFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;	
	num=m_ManaFileList.GetCount();
	i=m_ManaFileList.GetCurSel();	
	CString fname;
	m_ManaFileList.GetText(i,fname);
	m_ManaFileList.DeleteString(i);	
	return;
}
