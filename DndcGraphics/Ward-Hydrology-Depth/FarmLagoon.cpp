// FarmLagoon.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "FarmLagoon.h"
#include "dndc_main.h"
#include "SitePara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char FarmLName[500], FarmLMName[500], FarmClimName[500];
/////////////////////////////////////////////////////////////////////////////
// FarmLagoon dialog


FarmLagoon::FarmLagoon(CWnd* pParent /*=NULL*/)
	: CDialog(FarmLagoon::IDD, pParent)
{
	//{{AFX_DATA_INIT(FarmLagoon)
	m_LagoonCover = -1;
	m_SurfaceArea = 0.0f;
	m_latitude = 0.0f;
	m_capacity = 0.0f;
	//}}AFX_DATA_INIT
}


void FarmLagoon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FarmLagoon)
	DDX_Control(pDX, IDC_ClimFileList, m_ClimFile);
	DDX_Control(pDX, IDC_ManageFileList, m_LagoonManage);
	DDX_Control(pDX, IDC_LagoonFileList, m_LagoonClim);
	DDX_Radio(pDX, IDC_CompostMethod, m_LagoonCover);
	DDX_Text(pDX, IDC_SurfaceArea, m_SurfaceArea);
	DDX_Text(pDX, IDC_Latitude, m_latitude);
	DDX_Text(pDX, IDC_capacity, m_capacity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FarmLagoon, CDialog)
	//{{AFX_MSG_MAP(FarmLagoon)
	ON_BN_CLICKED(IDC_SelLagoonFile, OnSelLagoonFile)
	ON_BN_CLICKED(IDC_SelManageFile, OnSelManageFile)
	ON_BN_CLICKED(IDC_SelClimFile, OnSelClimFile)
	ON_LBN_DBLCLK(IDC_ClimFileList, OnDblclkClimFileList)
	ON_LBN_DBLCLK(IDC_LagoonFileList, OnDblclkLagoonFileList)
	ON_LBN_DBLCLK(IDC_ManageFileList, OnDblclkManageFileList)
	ON_BN_CLICKED(IDC_CompostSave2, OnCompostSave2)
	ON_BN_CLICKED(IDC_CompostOpen2, OnCompostOpen2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FarmLagoon message handlers

void FarmLagoon::OnSelLagoonFile() 
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
	num=m_LagoonClim.GetCount();
	if (num==1) return;
	
	k=m_LagoonClim.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy( FarmLName,cst);
		m_LagoonClim.InsertString(k, FarmLName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_LagoonClim.GetCount()==1) break;
		k++;
	}
	m_LagoonClim.SetCurSel(k);
}

void FarmLagoon::OnSelManageFile() 
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
	num=m_LagoonManage.GetCount();
	if (num==1) return;
	
	k=m_LagoonManage.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy( FarmLMName,cst);
		m_LagoonManage.InsertString(k, FarmLMName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_LagoonManage.GetCount()==1) break;
		k++;
	}
	m_LagoonManage.SetCurSel(k);
}

void FarmLagoon::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString FCF;
	FILE *fcf;
	FCF.Format("C:\\%s\\FarmLagoonPara", INTER);
	fcf=fopen(FCF, "w");
	fprintf(fcf, "%s\n",  FarmClimName);
	fprintf(fcf, "%s\n",  FarmLName);
	fprintf(fcf, "%s\n",  FarmLMName);
	fprintf(fcf, "%d %f %f %f\n",  m_LagoonCover+1, m_SurfaceArea, m_capacity, m_latitude);
	fclose(fcf);

	char SYF[200];
	FILE* sni;
	sprintf(SYF, "%s\\Inter\\SoilNewIni", OUTPUT);
	sni=sopen(SYF, "w");
	if(sni==NULL) note(1, SYF);
	fprintf(sni, "%d", 4);
	fclose(sni);
	
	SaveClimateFileOfAYear(1, FarmClimName, m_latitude,
			1, 0.0, 0.0, 370.0, "Check", 0, 0.0, 0, "r_Country");

	CDialog::OnOK();
}

void FarmLagoon::OnSelClimFile() 
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
	num=m_ClimFile.GetCount();
	if (num==1) return;
	
	k=m_ClimFile.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FarmClimName,cst);
		m_ClimFile.InsertString(k, FarmClimName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ClimFile.GetCount()==1) break;
		k++;
	}
	m_ClimFile.SetCurSel(k);
}

void FarmLagoon::OnDblclkClimFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;	
	num=m_ClimFile.GetCount();
	i=m_ClimFile.GetCurSel();	
	CString fname;
	m_ClimFile.GetText(i,fname);
	m_ClimFile.DeleteString(i);	
	return;
}

void FarmLagoon::OnDblclkLagoonFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;	
	num=m_LagoonClim.GetCount();
	i=m_LagoonClim.GetCurSel();	
	CString fname;
	m_LagoonClim.GetText(i,fname);
	m_LagoonClim.DeleteString(i);	
	return;
}

void FarmLagoon::OnDblclkManageFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;	
	num=m_LagoonManage.GetCount();
	i=m_LagoonManage.GetCurSel();	
	CString fname;
	m_LagoonManage.GetText(i,fname);
	m_LagoonManage.DeleteString(i);	
	return;
}

void FarmLagoon::OnCompostSave2() 
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
	fprintf(cif, "Lagoon_input_data\n");
	fprintf(cif, "Latitude: %f\n", m_latitude);
	fprintf(cif, "Climate_file_name: %s\n",  FarmClimName);
	fprintf(cif, "Lagoon_climate_file_name: %s\n",  FarmLName);
	fprintf(cif, "Management_file_name: %s\n", FarmLMName);
	fprintf(cif, "Lagoon_cover_type: %d\n", m_LagoonCover+1);
	fprintf(cif, "Surface_area: %f\n",  m_SurfaceArea);
	fprintf(cif, "Lagoon_capacity: %f\n", m_capacity);
	fclose(cif);

	
}

void FarmLagoon::OnCompostOpen2() 
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
	fscanf(cif, "%s %s\n", js,  FarmClimName);
	fscanf(cif, "%s %s\n", js, FarmLName);
	fscanf(cif, "%s %s\n", js, FarmLMName);
	fscanf(cif, "%s %d\n", js, &m_LagoonCover);
	fscanf(cif, "%s %f\n", js, &m_SurfaceArea);
	fscanf(cif, "%s %f\n", js, &m_capacity);
	
	fclose(cif);

	m_LagoonCover--;

	m_ClimFile.InsertString(0, FarmClimName);
	m_LagoonClim.InsertString(0, FarmLName);
	m_LagoonManage.InsertString(0, FarmLMName);	
	
	UpdateData(FALSE);
}
