// ManurePen.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "ManurePen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char PenStockFileName[250];
/////////////////////////////////////////////////////////////////////////////
// ManurePen dialog


ManurePen::ManurePen(CWnd* pParent /*=NULL*/)
	: CDialog(ManurePen::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManurePen)
	m_Stock1 = 0;
	m_FeedRate = 0.0f;
	m_Heads = 0.0f;
	m_ProteinPercent = 0.0f;
	m_FloorArea = 0.0f;
	m_SurfaceType = 0;
	m_BedType = 0;
	m_BedAmount = 0.0f;
	m_BadCN = 0.0f;
	m_BedFrequency = 0.0f;
	m_ManureMoveFrequency = 0.0f;
	m_FC = 0.0f;
	m_FD = 0.0f;
	m_FL = 0.0f;
	m_FR = 0.0f;
	m_UC = 0.0f;
	m_UD = 0.0f;
	m_UL = 0.0f;
	m_UR = 0.0f;
	m_PenStorage = 0.0f;
	m_unit = 0;
	m_PenFeedP = 0.4f;
	//}}AFX_DATA_INIT
}


void ManurePen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManurePen)
	DDX_Control(pDX, IDC_StockFileList, m_StockFileList);
	DDX_Control(pDX, IDC_AnimalType, m_AnimalType);
	DDX_Radio(pDX, IDC_Stock2, m_Stock1);
	DDX_Text(pDX, IDC_DairyFeed, m_FeedRate);
	DDX_Text(pDX, IDC_DairyHeads, m_Heads);
	DDX_Text(pDX, IDC_DairyProtein, m_ProteinPercent);
	DDX_Text(pDX, IDC_FloorArea, m_FloorArea);
	DDX_Radio(pDX, IDC_FloorSurface1, m_SurfaceType);
	DDX_Radio(pDX, IDC_BedType1, m_BedType);
	DDX_Text(pDX, IDC_BedAmount2, m_BedAmount);
	DDX_Text(pDX, IDC_BedCN2, m_BadCN);
	DDX_Text(pDX, IDC_BedNumber2, m_BedFrequency);
	DDX_Text(pDX, IDC_Frequency, m_ManureMoveFrequency);
	DDX_Text(pDX, IDC_FC, m_FC);
	DDX_Text(pDX, IDC_FD, m_FD);
	DDX_Text(pDX, IDC_FL, m_FL);
	DDX_Text(pDX, IDC_FR, m_FR);
	DDX_Text(pDX, IDC_UC, m_UC);
	DDX_Text(pDX, IDC_UD, m_UD);
	DDX_Text(pDX, IDC_UL, m_UL);
	DDX_Text(pDX, IDC_UR, m_UR);
	DDX_Text(pDX, IDC_PenStorage, m_PenStorage);
	DDX_Radio(pDX, IDC_unit, m_unit);
	DDX_Text(pDX, IDC_PenFeedP, m_PenFeedP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManurePen, CDialog)
	//{{AFX_MSG_MAP(ManurePen)
	ON_BN_CLICKED(IDC_SelStockFile, OnSelStockFile)
	ON_BN_CLICKED(IDC_Stock1, OnStock1)
	ON_BN_CLICKED(IDC_Stock2, OnStock2)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManurePen message handlers

void ManurePen::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString snote;

	if(m_UC+m_UL+m_UD+m_UR>0.9999&&m_UC+m_UL+m_UD+m_UR<0.00001)
	{
		snote.Format("The sum of the fractions must be equal to 1 for liquid waste");
		AfxMessageBox(snote);
		//return;
	}

	if(m_FC+m_FL+m_FD+m_FR>0.9999&&m_FC+m_FL+m_FD+m_FR<0.00001)
	{
		snote.Format("The sum of the fractions must be equal to 1 for solid waster");
		AfxMessageBox(snote);
		//return;
	}

	//unit conversion
	float FeedRate, FloorArea, BedAmount, VentRate;
	if(m_unit==0)
	{
		FeedRate = m_FeedRate;
		FloorArea = m_FloorArea;
		BedAmount = m_BedAmount;
		
	}
	else
	{
		FeedRate = m_FeedRate * lb_kg;//lb -> kg
		FloorArea = m_FloorArea * foot2_m2;//ft2 -> m2
		BedAmount = m_BedAmount * lb_kg;//lb -> kg
		
	}

	CString SF;
	FILE* sf;
	SF.Format("%s\\Inter\\ManurePen.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d\n", m_Stock1);  
	
	if(m_Stock1==1)								//use a input file name
		fprintf(sf, "%s\n", PenStockFileName);
	else										//use average input data
	{
		int AnimalType = m_AnimalType.GetCurSel()+1;			
		fprintf(sf, "%d\n", 1);
		fprintf(sf, "%d  %f  %f  %f %f\n", AnimalType, m_Heads, FeedRate, m_ProteinPercent, m_PenFeedP);
	}
	
	fprintf(sf, "%f  %d\n", FloorArea, m_SurfaceType);//0 slatted floor; 1 conrete floor
	fprintf(sf, "%d  %f  %f  %f\n", m_BedType, m_BadCN, m_BedFrequency, BedAmount);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
	fprintf(sf, "%f\n", m_ManureMoveFrequency);
	fprintf(sf, "%f %f %f %f\n", m_UC, m_UL, m_UD, m_UR);
	fprintf(sf, "%f %f %f %f\n", m_FC, m_FL, m_FD, m_FR);
	fclose(sf);

	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", m_unit);
	fclose(ddb);

	CDialog::OnOK();
}

void ManurePen::OnSelStockFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int m_years=1;	
	CString cst;
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_StockFileList.GetCount();
	if (num==m_years) return;
	
	k=m_StockFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(PenStockFileName,cst);
		m_StockFileList.InsertString(k,PenStockFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_StockFileList.GetCount()==m_years) break;
		k++;
	}
	m_StockFileList.SetCurSel(k);
}

BOOL ManurePen::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Result\\inter\\UnitSystem", ROOTDIR);
	ddb=fopen(LB, "r");
	if(ddb==NULL) note(0, LB);
	fscanf(ddb, "%d", &m_unit);
	fclose(ddb);

	CString SF;
	FILE* sf;
	SF.Format("%s\\Result\\Inter\\ManurePen.txt", ROOTDIR);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);
	
	fscanf(sf, "%d", &m_Stock1);  
	if(m_Stock1==1)								//use a input file name
		fscanf(sf, "%s", PenStockFileName);
	else										//use average input data
	{
		int AnimalType, i=0;
		float AnimalHeads;
		float AnimalFeed;
		float AnimalProtein, AnimalFeedP;
		//Type: 1 dairy, 2 beef, 3 veal, 4 swine, 5 sheep, 6 poultry
		
		fscanf(sf, "%d", &i);
		fscanf(sf, "%d", &AnimalType);
		fscanf(sf, "%f %f %f %f", &AnimalHeads, &AnimalFeed, &AnimalProtein, &AnimalFeedP);
			
		m_AnimalType.SetCurSel(AnimalType-1);
		m_Heads=AnimalHeads;
		m_FeedRate=AnimalFeed;
		m_ProteinPercent=AnimalProtein;
		m_PenFeedP = AnimalFeedP;
	}	
	fscanf(sf, "%f  %d", &m_FloorArea, &m_SurfaceType);//0 slatted floor; 1 conrete floor
	fscanf(sf, "%d  %f  %f  %f", &m_BedType, &m_BadCN, &m_BedFrequency, &m_BedAmount);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
	fscanf(sf, "%f\n", &m_ManureMoveFrequency);
	fscanf(sf, "%f %f %f %f\n", &m_UC, &m_UL, &m_UD, &m_UR);
	fscanf(sf, "%f %f %f %f\n", &m_FC, &m_FL, &m_FD, &m_FR);
	fclose(sf);

	if(m_unit==1)
	{
		m_FeedRate /= lb_kg;//kg -> lb
		m_FloorArea /= foot2_m2;//m2 -> ft2
		m_BedAmount /= lb_kg;//kg -> lb		
	}

	CEdit *Edt;
	if(m_Stock1==0)
	{		
		Edt=(CEdit *)GetDlgItem(IDC_SelStockFile);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_AnimalType);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyHeads);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyFeed);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyProtein);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_SelStockFile);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_AnimalType);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyHeads);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyFeed);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyProtein);
		Edt->EnableWindow(FALSE);
	}

	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);
	}

	
	UpdateData(FALSE);

	//Onunit2();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ManurePen::OnStock1() 
{
	// TODO: Add your control notification handler code here
	CEdit *Edt;
	/*if(m_Stock1==0)
	{		
		Edt=(CEdit *)GetDlgItem(IDC_SelStockFile);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_AnimalType);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyHeads);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyFeed);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyProtein);
		Edt->EnableWindow(TRUE);
	}
	else*/
	{
		Edt=(CEdit *)GetDlgItem(IDC_SelStockFile);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_AnimalType);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyHeads);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyFeed);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyProtein);
		Edt->EnableWindow(FALSE);
	}
}

void ManurePen::OnStock2() 
{
	// TODO: Add your control notification handler code here
	CEdit *Edt;
	//if(m_Stock1==0)
	{		
		Edt=(CEdit *)GetDlgItem(IDC_SelStockFile);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_AnimalType);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyHeads);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyFeed);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyProtein);
		Edt->EnableWindow(TRUE);
	}
	/*else
	{
		Edt=(CEdit *)GetDlgItem(IDC_SelStockFile);
		Edt->EnableWindow(TRUE);
		Edt=(CEdit *)GetDlgItem(IDC_AnimalType);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyHeads);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyFeed);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_DairyProtein);
		Edt->EnableWindow(FALSE);
	}*/
}

void ManurePen::Onunit() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==0&&n_unit==1) 
	{
		m_FeedRate *= lb_kg;//lb -> kg
		m_FloorArea *= foot2_m2;//ft2 -> m2 
		m_BedAmount *= lb_kg;//lb -> kg
	}

	CString DB;
	FILE *db;	
	DB.Format("%s\\Result\\inter\\UnitSystem", ROOTDIR);
	db=fopen(DB, "w");

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE); 
		
		fprintf(db, "%d", 1);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);
		
		fprintf(db, "%d", 0);
	}	
	
	fclose(db);

	UpdateData(FALSE);
}

void ManurePen::Onunit2() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==1&&n_unit==0) 
	{
		m_FeedRate /= lb_kg;//kg -> lb
		m_FloorArea /= foot2_m2;//m2 -> feet2
		m_BedAmount /= lb_kg;//kg -> lb		
	}

	CString DB;
	FILE *db;	
	DB.Format("%s\\Result\\inter\\UnitSystem", ROOTDIR);
	db=fopen(DB, "w");

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(TRUE);
		
		fprintf(db, "%d", 1);
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_kg2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb3);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE);
		
		fprintf(db, "%d", 0);
	}	
	
	fclose(db);

	UpdateData(FALSE);

}
