// SelectObsWT.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "SelectObsWT.h"
#include "SitePage9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectObsWT dialog


SelectObsWT::SelectObsWT(CWnd* pParent /*=NULL*/)
	: CDialog(SelectObsWT::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectObsWT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SelectObsWT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectObsWT)
	DDX_Control(pDX, IDC_WTFileList, m_WTFileList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectObsWT, CDialog)
	//{{AFX_MSG_MAP(SelectObsWT)
	ON_BN_CLICKED(IDC_selectWTfile, OnselectWTfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectObsWT message handlers

void SelectObsWT::OnselectWTfile() 
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);
	
	int rrr, yyy;
	CString pre_WTFileName[5];
	CString f_site, cst;
	FILE *Fsite;

	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", INTERMANAGE);

	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//Open a menu window
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();

	POSITION pos=ask.GetStartPosition();
	
	//Count number (num) of selected strings
	int k,num;
	num = m_WTFileList.GetCount();
	if (num==1) return;
	/*else
	{
		CString CC;
		CC.Format("You need %d files. This is file %d.", SimuYears, num+1);
		AfxMessageBox(CC);
	}*/
	
	//Obtain order number (k) of each selected string
	k = m_WTFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		//Obtain a character from the string
		pre_WTFileName[num].Format("%s", ask.GetNextPathName(pos));
		if (pre_WTFileName[num]=="") break;

		f_site.Format("%s\\Inter\\WTfile_%d_%d", OUTPUT, rrr, yyy);
	
		Fsite = fopen(f_site, "w");
		if(Fsite==NULL)
		{
			CString note;
			note.Format("Can not create file %s", f_site);
			AfxMessageBox(note);
			exit(0);
		}
		fprintf(Fsite, "%s\n", pre_WTFileName[num]);	
		
		fclose(Fsite);

		//Add the character into pre_ClimateFileName[num]
		m_WTFileList.InsertString(k, pre_WTFileName[num]);

		if (cst.IsEmpty() || pos==NULL) 
		{
			
			break;
		}
		
		if (m_WTFileList.GetCount()==1) break;

		k++;
	}

	//Put the string on screen
	m_WTFileList.SetCurSel(k);
	
	UpdateData(FALSE);
	
}

	


void SelectObsWT::OnOK() 
{
	// TODO: Add extra validation here

	WT_table1();
	
	CDialog::OnOK();
}

void SelectObsWT::WT_table1(void)
{
	CString f_land, ff, WT_file_name;
	FILE *Fland;
	FILE *FF;

	int jjday[366], i, j, kk, xx, rrr, yyy; 
	float WTdepth[366], today_WT;

	CString DB;
	FILE *db;
	DB.Format("%s\\inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", INTERMANAGE);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	ff.Format("%s\\Inputs\\WaterTable_%d_%d", OUTPUT, rrr, yyy);	
	FF = fopen(ff, "w");
	if(FF==NULL)
	{
		CString note;
		note.Format("Can not create file %s", ff);
		AfxMessageBox(note);
		exit(0);
	}

	f_land.Format("%s\\Inter\\WTfile_%d_%d", OUTPUT, rrr, yyy);
	Fland = fopen(f_land, "r");

	if(Fland==NULL)
	{
		CString note;
		note.Format("Can not find file %s", f_land);
		AfxMessageBox(note);
		exit(0);
	}	
	fscanf(Fland, "%s", WT_file_name);
	fclose (Fland);

	f_land.Format("%s", WT_file_name);	
	Fland = fopen(f_land, "r");

	if(Fland==NULL)
	{
		CString note;
		note.Format("Can not find file %s", f_land);
		AfxMessageBox(note);
		exit(0);
	}

	char ju[300];
	fgets(ju, 200, Fland);
	fgets(ju, 200, Fland);

	i=0;
	
	for(;;)
	{
		i++;

		if(fscanf(Fland, "%d %f", &jjday[i], &WTdepth[i])!=2) 
		{
			xx=i-1;
			break;
		}
		else WTdepth[i] *= 0.01; //cm -> m		
	}

	kk=1;
	for(j=1; j<=365; j++)
	{
		if(j<jjday[1]) 
		{
			today_WT = WTdepth[1];
			
		}
		else if(j==jjday[kk])
		{			
			today_WT = WTdepth[kk];
			kk++;
		}
		else if(j>jjday[kk-1]&&j<jjday[kk])
		{
			today_WT += (WTdepth[kk] - WTdepth[kk-1])/(jjday[kk] - jjday[kk-1]);
		}

		else if(j>jjday[xx])
		{
			today_WT = WTdepth[xx];
		}
		else
		{
			
		}
		
		fprintf(FF, "%4d  %10.4f\n", j, today_WT);
	}

    fclose(Fland);
	fclose(FF);


}
