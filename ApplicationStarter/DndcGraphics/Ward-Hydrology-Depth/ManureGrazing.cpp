// ManureGrazing.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ManureGrazing.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char StockFileName3[200];
int FileUse3;
int IniMonth[366]={0,0}, IniDay[366]={0,0}, EndMonth[366]={0,0}, EndDay[366]={0,0};
float Heads[366]={0,0}, Hours[366]={0,0};
/////////////////////////////////////////////////////////////////////////////
// ManureGrazing dialog


ManureGrazing::ManureGrazing(CWnd* pParent /*=NULL*/)
	: CDialog(ManureGrazing::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureGrazing)
	m_Stock1 = 0;
	m_EndDay = 0;
	m_EndMonth = 0;
	m_GrazeID = 0;
	m_GrazeTimes = 0;
	m_Heads = 0.0f;
	m_Hours = 0.0f;
	m_IniDay = 0;
	m_IniMonth = 0;
	m_GrazeArea = 0.0f;
	//}}AFX_DATA_INIT
}


void ManureGrazing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureGrazing)
	DDX_Control(pDX, IDC_StockFileList, m_StockFileList);
	DDX_Control(pDX, IDC_AnimalType, m_AnimalType);
	DDX_Radio(pDX, IDC_Stock2, m_Stock1);
	DDX_Text(pDX, IDC_EndDay, m_EndDay);
	DDX_Text(pDX, IDC_EndMonth, m_EndMonth);
	DDX_Text(pDX, IDC_GrazeID, m_GrazeID);
	DDX_Text(pDX, IDC_GrazeTimes, m_GrazeTimes);
	DDX_Text(pDX, IDC_Heads, m_Heads);
	DDX_Text(pDX, IDC_Hours, m_Hours);
	DDX_Text(pDX, IDC_IniDay, m_IniDay);
	DDX_Text(pDX, IDC_IniMonth, m_IniMonth);
	DDX_Text(pDX, IDC_GrazeArea, m_GrazeArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureGrazing, CDialog)
	//{{AFX_MSG_MAP(ManureGrazing)
	ON_BN_CLICKED(IDC_Next, OnNext)
	ON_BN_CLICKED(IDC_Last, OnLast)
	ON_BN_CLICKED(IDC_SelStockFile, OnSelStockFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureGrazing message handlers

void ManureGrazing::OnNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	IniMonth[m_GrazeID] = m_IniMonth;
	IniDay[m_GrazeID] = m_IniDay;
	EndMonth[m_GrazeID] = m_EndMonth;
	EndDay[m_GrazeID] = m_EndDay;
	Heads[m_GrazeID] = m_Heads;
	Hours[m_GrazeID] = m_Hours;

	m_GrazeID++;
	if(m_GrazeID>m_GrazeTimes) m_GrazeID=m_GrazeTimes;

	m_IniMonth = IniMonth[m_GrazeID];
	m_IniDay = IniDay[m_GrazeID];
	m_EndMonth = EndMonth[m_GrazeID];
	m_EndDay = EndDay[m_GrazeID];
	m_Heads = Heads[m_GrazeID];
	m_Hours = Hours[m_GrazeID];

	UpdateData(FALSE);
}

void ManureGrazing::OnLast() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	IniMonth[m_GrazeID] = m_IniMonth;
	IniDay[m_GrazeID] = m_IniDay;
	EndMonth[m_GrazeID] = m_EndMonth;
	EndDay[m_GrazeID] = m_EndDay;
	Heads[m_GrazeID] = m_Heads;
	Hours[m_GrazeID] = m_Hours;	

	m_GrazeID--;
	if(m_GrazeID<0) m_GrazeID=0;

	m_IniMonth = IniMonth[m_GrazeID];
	m_IniDay = IniDay[m_GrazeID];
	m_EndMonth = EndMonth[m_GrazeID];
	m_EndDay = EndDay[m_GrazeID];
	m_Heads = Heads[m_GrazeID];
	m_Hours = Hours[m_GrazeID];	

	UpdateData(FALSE);
}

void ManureGrazing::OnSelStockFile() 
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
		strcpy(StockFileName3,cst);
		m_StockFileList.InsertString(k,StockFileName3);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_StockFileList.GetCount()==m_years) break;
		k++;
	}
	m_StockFileList.SetCurSel(k);
}

void ManureGrazing::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	int AnimalType = m_AnimalType.GetCurSel()+1;

	IniMonth[m_GrazeID] = m_IniMonth;
	IniDay[m_GrazeID] = m_IniDay;
	EndMonth[m_GrazeID] = m_EndMonth;
	EndDay[m_GrazeID] = m_EndDay;
	Heads[m_GrazeID] = m_Heads;
	Hours[m_GrazeID] = m_Hours;

	CString SF;
	FILE* sf;
	SF.Format("%s\\Inter\\ManureGraze.txt", OUTPUT);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);
	
	fprintf(sf, "%d\n", m_Stock1);  
	if(m_Stock1==1)								//use a input file name
		fprintf(sf, "%s\n", StockFileName3);
	else										//use average input data
	{
		fprintf(sf, "%d  %d\n", AnimalType, m_GrazeTimes);//Type: 1 dairy, 2 beef, 3 veal, 4 swine, 5 sheep, 6 poultry 
		for(int i=1; i<=m_GrazeTimes; i++)
		{
			fprintf(sf, "%d  %d  %d  %d  %f  %f\n", IniMonth[i], IniDay[i], EndMonth[i], EndDay[i], Heads[i], Hours[i]); 
		}
	}
	fprintf(sf, "%f\n", m_GrazeArea); 
	fclose(sf);

	CDialog::OnOK();
}

BOOL ManureGrazing::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString SF;
	FILE* sf;
	SF.Format("%s\\Result\\Inter\\ManureField.txt", ROOTDIR);
	sf=fopen(SF, "r");
	if(sf==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", SF);
		AfxMessageBox(note);
		exit(0);
	}

	fscanf(sf, "%d", &m_Stock1);  
	if(m_Stock1==1)								//use a input file name
		fscanf(sf, "%s", StockFileName3);
	else										//use average input data
	{
		fscanf(sf, "%d  %d", &m_AnimalType, &m_GrazeTimes);//Type: 1 dairy, 2 beef, 3 veal, 4 swine, 5 sheep, 6 goat, 7 horse, 
		for(int i=1; i<=m_GrazeTimes; i++)
		{
			fscanf(sf, "%d  %d  %d  %d  %f  %f", &IniMonth[i], &IniDay[i], &EndMonth[i], &EndDay[i], &Heads[i], &Hours[i]); 
		}
	}
	fscanf(sf, "%f\n", &m_GrazeArea); 
	fclose(sf);

	m_IniMonth=IniMonth[1];
	m_IniDay=IniDay[1];
	m_EndMonth=EndMonth[1];
	m_EndDay=EndDay[1];
	m_Heads=Heads[1];
	m_Hours=Hours[1];

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
