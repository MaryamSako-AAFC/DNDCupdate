// SitePage1.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "SitePage1.h"
#include "dndc_main.h"
#include "SitePage3.h"
#include "ListFile.h"
#include "CreateInputFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CropArray			Crop;
extern Site_BaseInformation	IData;
extern StringArray			ClimateFilename;
extern StringArray			LaiFilename;
extern CropProperty CropPty;
extern CropofEachYear CYr[2];
char * EraseSpaceB(char *str);

#ifdef MANURE
void CreateBlankManureFiles();
#endif

int ClimateFileNumber;
//char ClimateFilename[300][200];
/////////////////////////////////////////////////////////////////////////////
// SitePage1 property page

IMPLEMENT_DYNCREATE(SitePage1, CPropertyPage)

SitePage1::SitePage1() : CPropertyPage(SitePage1::IDD)
{
	//{{AFX_DATA_INIT(SitePage1)
	m_sitename = _T("");
	m_latitude = 0.0f;
	m_years = 0;
	m_AirNH3 = 0.0f;
	m_RainNO3NH4 = 0.0f;
	m_RecordDaily = FALSE;
	m_CFileFormat = 2;
	m_BaseCO2 = 0.0f;
	m_Use1File = FALSE;
	m_Longitude = 0.0f;
	m_MetSuccess = FALSE;
	m_WaterYrMonth = 0;
	m_WaterYrDay = 0;
	m_WaterYr = FALSE;
	m_CO2IncreaseRate = 0.0f;
	m_CO2file = FALSE;
	//}}AFX_DATA_INIT
}

SitePage1::~SitePage1()
{
	LaiFlag = 0;
}

void SitePage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage1)
	DDX_Control(pDX, IDC_MetYear, m_MetYear);
	DDX_Control(pDX, IDC_LAIfile, m_LAIFileList);
	DDX_Control(pDX, IDC_ClimateFileList, m_ClimateFileList);
    DDX_Control(pDX, IDC_CO2FileList, m_CO2FileList);
	DDX_Text(pDX, IDC_SiteName, m_sitename);
	DDX_Text(pDX, IDC_Latitude, m_latitude);
	DDV_MinMaxFloat(pDX, m_latitude, -90.f, 90.f);
	DDX_Text(pDX, IDC_Years, m_years);
	DDV_MinMaxLong(pDX, m_years, 0, 10000000);
	DDX_Text(pDX, IDC_AirNH3, m_AirNH3);
	DDV_MinMaxFloat(pDX, m_AirNH3, 0.f, 1.e+006f);
	DDX_Text(pDX, IDC_RainNO3NH4, m_RainNO3NH4);
	DDX_Check(pDX, IDC_RecordDaily, m_RecordDaily);
	DDX_Radio(pDX, IDC_ClimateFormat1, m_CFileFormat);
	DDX_Text(pDX, IDC_BaseCO2, m_BaseCO2);
	DDV_MinMaxFloat(pDX, m_BaseCO2, 0.f, 1.e+008f);
	DDX_Check(pDX, IDC_Use1File, m_Use1File);
	DDX_Text(pDX, IDC_Longitude, m_Longitude);
	DDX_Check(pDX, IDC_MetSuccess, m_MetSuccess);
	DDX_Text(pDX, IDC_WaterYrMonth, m_WaterYrMonth);
	DDX_Text(pDX, IDC_WaterYrDay, m_WaterYrDay);
	DDX_Check(pDX, IDC_WaterYear, m_WaterYr);
	DDX_Text(pDX, IDC_CO2IncreaseRate, m_CO2IncreaseRate);
	DDX_Check(pDX, IDC_CO2file, m_CO2file);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage1, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage1)
	ON_BN_CLICKED(IDC_SelClimateFile, OnSelClimateFile)
	ON_LBN_DBLCLK(IDC_ClimateFileList, OnDblclkClimateFileList)
	ON_BN_CLICKED(ID_NEWSITE, OnNewsite)
	ON_BN_CLICKED(ID_OPENSITE, OnOpensite)
	ON_BN_CLICKED(ID_SAVESITE, OnSavesite)
	ON_BN_CLICKED(IDC_AcceptClimate, OnAcceptClimate)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_SiteRecover, OnSiteRecover)
	ON_BN_CLICKED(IDC_MoveDown, OnMoveDown)
	ON_BN_CLICKED(IDC_MoveUp, OnMoveUp)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RecordDaily, OnRecordDaily)
	ON_BN_CLICKED(IDC_SelLAIfile, OnSelLAIfile)
	ON_CBN_SELCHANGE(IDC_MetYear, OnSelchangeMetYear)
	ON_BN_CLICKED(ID_DefaulClimate, OnDefaulClimate)
	ON_BN_CLICKED(ID_Default, OnDefault)
	ON_BN_CLICKED(IDC_WaterYear, OnWaterYear)
	ON_EN_KILLFOCUS(IDC_Years, OnKillfocusYears)
	ON_BN_CLICKED(IDC_Use1File, OnUse1File)
	ON_BN_CLICKED(IDC_CListFileName, OnCListFileName)
	ON_BN_CLICKED(IDC_CO2file, OnCO2file)
	ON_EN_KILLFOCUS(IDC_SiteName, OnKillfocusSiteName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage1 message handlers
BOOL SitePage1::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CEdit *Edt;
	int i, k=0;

#ifdef WIZARD

	if(Revisit==0) get_defaults();
	
	int junk_d;
    char site_file[80];
	float longi, latit;
    FILE *fp;

    sprintf(site_file, "%s\\Inter\\SiteLocation.txt", OUTPUT);
    fp = fopen(site_file, "r");
    if ( fp == NULL )
	{
		printf("File %s not found", site_file);
		getch();
		exit(0);
	}
 
    fscanf(fp, "%f %f", &longi, &latit);
	fclose(fp);

	m_sitename   = IData.sitename;
	m_latitude   = latit;
	m_Longitude  = longi;
	m_years		 = IData.years;
	m_RecordDaily= 1;
	m_RainNO3NH4 = IData.NO3NH4_Rainfall;
	m_AirNH3	 = IData.NH3_Atmosphere;
	m_BaseCO2	 = IData.BaseCO2;
	m_Use1File = IData.if1File;
	m_CO2IncreaseRate	 = IData.CO2IncreaseRate;
	m_TopM	 = IData.SOCa;
	m_DecreaseRate	 = IData.SOCb;



	
#ifdef GLOBE_CLIM
	m_CFileFormat= 4;
#else
	m_CFileFormat= 1;
#endif

	Edt=(CEdit *)GetDlgItem(IDC_Longitude);
	Edt->EnableWindow(TRUE);
/*	Edt=(CEdit *)GetDlgItem(IDC_MetYear);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_MetSuccess);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_STATIC1);
	Edt->EnableWindow(TRUE);
	Edt=(CEdit *)GetDlgItem(IDC_STATIC2);
	Edt->EnableWindow(TRUE);*/

#endif

#ifdef BASE
	m_sitename   = IData.sitename;
	m_latitude   = IData.latitude;
	m_years		 = IData.years;
	m_RecordDaily= IData.ifdaily;
	m_CFileFormat= IData.ClimateFileType;
	m_RainNO3NH4 = IData.NO3NH4_Rainfall;
	m_AirNH3	 = IData.NH3_Atmosphere;
	m_BaseCO2	 = IData.BaseCO2;
	m_Use1File = IData.if1File;
	m_CO2IncreaseRate = IData.CO2IncreaseRate;
 
	Edt=(CEdit *)GetDlgItem(IDC_MetYear);
	Edt->EnableWindow(FALSE); 
	Edt=(CEdit *)GetDlgItem(IDC_MetSuccess);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_STATIC1);
	Edt->EnableWindow(FALSE);
	Edt=(CEdit *)GetDlgItem(IDC_STATIC2);
	Edt->EnableWindow(FALSE);

#endif
	
	m_CO2file = IData.CO2file;

	if(IData.CO2file==1)
	{

		if(m_CO2FileList.GetCount()==0)
		{m_CO2FileList.InsertString(0, IData.CO2FileName);
		m_CO2FileList.SetCurSel(0);}

		m_CO2FileName=IData.CO2FileName;
		//Put the string on screen
	
	
	
	}
	if(IData.CO2file==0)
	{
		IData.CO2FileName="";
		if(m_CO2FileList.GetCount()>0)
		{
		m_CO2FileList.DeleteString(0);
		m_CO2FileList.SetCurSel(0);}
	}
	m_CO2FileName=IData.CO2FileName;




	char cst[255];
	m_ClimateFileList.ResetContent ();
	
	for (i=1;i<=ClimateFilename.n;i++)
	{
		strcpy(cst,ClimateFilename.get(i));
		if (strlen(cst)==0) continue;
		m_ClimateFileList.InsertString(k,cst);
		k++;
	} 	
	UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}

void SitePage1::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	int i;
	i=100;
}

void SitePage1::OnSelClimateFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SelectClimFile();

/*	UpdateData(TRUE);
	if (m_years<=0) {
		MessageBox("Please input the simulated years firstly","Input Error:",NULL);
		return;
	}

	char FileName[255];
	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_ClimateFileList.GetCount();
	if (num==m_years) return;
	
	k=m_ClimateFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_ClimateFileList.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ClimateFileList.GetCount()==m_years) break;
		k++;
	}
	m_ClimateFileList.SetCurSel(k);
*/
}


void SitePage1::OnDblclkClimateFileList() 
{

	int i,num;
		// delete a selected file from the list
	num=m_ClimateFileList.GetCount();
	i=m_ClimateFileList.GetCurSel();
	
	CString fname;
	m_ClimateFileList.GetText(i,fname);
	m_ClimateFileList.DeleteString(i);	
	return;

}

void SitePage1::OnNewsite() 
{
	// TODO: Add your control notification handler code here
	
	get_defaults();

	OnSetActive();

	UpdateData(FALSE);
}

void SitePage1::OnOpensite() 
{
	// TODO: Add your control notification handler code here
	//CFileDialog ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.dnd)|*.dnd|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt|All Files (*.*)|*.*||", NULL );
	CFileDialog ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.dnd)|*.dnd|All files (*.*)|*.*||", NULL );

	ask.DoModal();
	char cst[255];
	strcpy(cst,ask.GetPathName());
	if (strlen(cst)==0) return;

	//CreateDndcInputFiles(cst);


#ifdef MANURE
	CreateBlankManureFiles();
#endif

	CString DB;
	FILE *db;
	char DCB[200];
	for(int k=1; k<=10; k++)
	{
		sprintf(DCB, "%s_1\\CropRotation_%d.txt", INTERMANAGE, k);//write: Initial files
		db=fopen(DCB, "w");
		if(db==NULL) note(1,DCB);
		fprintf(db, "%d %d %d", k, 1, 1);
		fclose(db);
	}

	//ask.DoModal();
	//char cst[255];
	//strcpy(cst,ask.GetPathName());
	//if (strlen(cst)==0) return;

	//ResetRotation();

	ReadInputDatafromDND(cst, 0);

	DB.Format("%s\\inter\\OpenFile.txt", OUTPUT);
	db=fopen(DB, "w");
	fprintf(db, "%d", 1);
	fclose(db);

	ReadSoilFeature("UnDefault");	

	OnSetActive();	

	AcceptPage1();

}

void SitePage1::OnSavesite() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CFileDialog ask(false, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.dnd)|*.dnd|All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	char cst[255];
	//strcpy(cst,ask.GetPathName());
	//if (strlen(cst)==0) return;

	CString fname;
	int l, rrr, yyy;
	fname = ask.GetPathName();
	l=fname.GetLength();
	if (l==0) return;

	if (fname.Right(4)!=".dnd") fname=fname+".dnd";
	sprintf(cst,"%s",fname);

	CString DB;
	FILE *db;

	//DB.Format("%s\\inter\\CropRotation.txt", OUTPUT);
	DB.Format("%s_1\\CropRotation.txt", INTERMANAGE);
	db=fopen(DB, "r");
	if(db==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DB);
			AfxMessageBox(note);
			exit(0);
		}
	fscanf(db, "%d", &IData.db_Rotation_Number);
	fclose(db);
	
	for(rrr=1; rrr<=IData.db_Rotation_Number; rrr++)
	{
		
		DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, rrr);//read: OnSavesite()
		db=fopen(DB, "r");
		fscanf(db, "%d %d %d", &IData.db_RotationID[rrr], &IData.db_RotateSpan[rrr], &IData.db_CycleSpan[rrr]);
		fclose(db);
		
		for(yyy=1; yyy<=IData.db_CycleSpan[rrr]; yyy++)
		{
			//DB.Format("%s\\inter\\CropRotation_%d_%d.txt", OUTPUT, rrr, yyy);
			DB.Format("%s_1\\CropRotation_%d_%d.txt", INTERMANAGE, rrr, yyy);
			db=fopen(DB, "r");
			fscanf(db, "%d", &IData.db_YrCrops[rrr][yyy]);

			for(int ccc=1; ccc<=IData.db_YrCrops[rrr][yyy]; ccc++)
			{
					fscanf(db, "%d %d", &IData.db_YrCropOrder[rrr][yyy][ccc], &IData.db_YrCropType[rrr][yyy][ccc]);
					fscanf(db, "%d %d", &IData.db_PMonth[rrr][yyy][ccc], &IData.db_PDay[rrr][yyy][ccc]);
					fscanf(db, "%d %d", &IData.db_HMonth[rrr][yyy][ccc], &IData.db_HDay[rrr][yyy][ccc]);
					fscanf(db, "%d", &IData.db_HYr[rrr][yyy][ccc]);
					fscanf(db, "%f %f", &IData.db_Residue[rrr][yyy][ccc], &IData.db_Yield[rrr][yyy][ccc]);
					fscanf(db, "%f %d", &IData.db_RepRate[rrr][yyy][ccc], &IData.db_Transplant[rrr][yyy][ccc]);
					fscanf(db, "%f %f", &IData.db_PsnEff[rrr][yyy][ccc], &IData.db_PsnMax[rrr][yyy][ccc]);
					fscanf(db, "%f", &IData.db_TreeAge[rrr][yyy][ccc]);
					fscanf(db, "%d", &IData.db_CoverCrop[rrr][yyy][ccc]);
					fscanf(db, "%d", &IData.db_PerennialCrop[rrr][yyy][ccc]);

					fscanf(db, "%f %f %f", &IData.db_GrainFraction[rrr][yyy][ccc], &IData.db_ShootFraction[rrr][yyy][ccc], &IData.db_RootFraction[rrr][yyy][ccc]);
					fscanf(db, "%f %f %f", &IData.db_GrainCN[rrr][yyy][ccc], &IData.db_ShootCN[rrr][yyy][ccc], &IData.db_RootCN[rrr][yyy][ccc]);
					fscanf(db, "%f %f %f %f %f", &IData.db_TDD[rrr][yyy][ccc], &IData.db_Water[rrr][yyy][ccc], &IData.db_OptT[rrr][yyy][ccc], &IData.db_Nfix[rrr][yyy][ccc], &IData.db_Vascularity[rrr][yyy][ccc]);
					fscanf(db, "%f %f %f %f", &IData.db_TreeAge[rrr][yyy][ccc], &IData.db_TreeCurrentAge[rrr][yyy][ccc], &IData.db_TreeLeafMax[rrr][yyy][ccc], &IData.db_TreeLeafMin[rrr][yyy][ccc]);
					fscanf(db, "%d %f", &IData.db_RootShape[rrr][yyy][ccc], &IData.db_GrainFill[rrr][yyy][ccc]);
			}
			fclose(db);
		

			/*DB.Format("%s\\Result\\inter\\CropTill_%d_%d.txt", rrr, yyy);
			db=fopen(DB, "r");
			fscanf(db, "%d", &IData.NNN);
			for(k=1; k<=IData.NNN; k++)
			{
				IData.TillID[k] = k;
				fscanf(db, "%d %d %d", &IData.TillMonth[k], &IData.TillDay[k], &IData.TillMethod[k]);
			}
			fclose(db);*/


		}
	}

	SaveDatatoFile(cst, 1);
}

BOOL SitePage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_CFileFormat = 1;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SitePage1::OnAcceptClimate() 
{
	// TODO: Add your control notification handler code here
	AcceptPage1();

}


void SitePage1::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnRButtonDown(nFlags, point);
}

void SitePage1::OnSiteRecover() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
}

void SitePage1::OnMoveDown() 
{
	// TODO: Add your control notification handler code here
	ClimMoveDown();

/*	int num,selfile;
	num=m_ClimateFileList.GetCount();
	selfile=m_ClimateFileList.GetCurSel();
	
	char tmp[255],tmp1[255];
	if (selfile<num-1 && selfile>=0) {
		m_ClimateFileList.GetText(selfile,tmp);
		m_ClimateFileList.GetText(selfile+1,tmp1);
		m_ClimateFileList.DeleteString(selfile);
		m_ClimateFileList.InsertString(selfile+1,tmp);
	}
*/	
}

void SitePage1::OnMoveUp() 
{
	// TODO: Add your control notification handler code here
	ClimMoveUp();

/*	int num,selfile;
	num=m_ClimateFileList.GetCount();
	selfile=m_ClimateFileList.GetCurSel();
	
	char tmp[255],tmp1[255];
	if (selfile<=num-1 && selfile>0) {
		m_ClimateFileList.GetText(selfile,tmp);
		m_ClimateFileList.GetText(selfile-1,tmp1);
		m_ClimateFileList.DeleteString(selfile);
		m_ClimateFileList.InsertString(selfile-1,tmp);
	}
*/	
}


void SitePage1::OnRecordDaily() 
{
			
}

void SitePage1::OnUse1File() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_Use1File==FALSE) m_Use1File = TRUE;
	else m_Use1File = FALSE;

	UpdateData(FALSE);
	
}

void SitePage1::OnSelLAIfile() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);
	
	char FileName[255];
	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();

	
	int k,num;
	num=m_LAIFileList.GetCount();
	if (num==1) return;
	
	k=m_LAIFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_LAIFileList.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_LAIFileList.GetCount()==1) break;
		k++;
	}
	m_LAIFileList.SetCurSel(k);

	LaiFlag = 1;
	
}

void SitePage1::OnSelchangeMetYear() 
{
	// TODO: Add your control notification handler code here
	CString CCrop;

	UpdateData(TRUE);

	int MetYear = m_MetYear.GetCurSel() + 1980;

#ifdef WIZARD
	CCrop.Format("%s\\inter\\SiteLocation.txt", OUTPUT);
	
	fCrop = fopen(CCrop, "r");
	if(fCrop==NULL)
	{
		CString err;
		err.Format("Can not find file %s", CCrop);
		AfxMessageBox(err);
		exit(0);
	}

	fscanf(fCrop, "%f %f", &lon, &lat); 
	fclose(fCrop);

	lon = m_Longitude;
	lat = m_latitude;

	if(m_Longitude==0.0) 
	{
		AfxMessageBox("Please specify longitude");
		return;
	}

	/*if(m_latitude==0.0) 
	{
		AfxMessageBox("Please specify latitude");
		return;
	}*/	

	CCrop.Format("%s\\inter\\SiteLocation.txt", OUTPUT);
	fCrop = fopen(CCrop, "w");
	if(fCrop==NULL)
	{
		CString err;
		err.Format("Can not create file %s", CCrop);
		AfxMessageBox(err);
		exit(0);
	}
	fprintf(fCrop, "%f %f\n", lon, lat); 
	fprintf(fCrop, "%ld %d\n", m_years, MetYear); 
	fclose(fCrop);

	UpdateData(FALSE);

	int ppp;
	//DaymetFlag = 0;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//CreateProcess(NULL, "\\perl\\bin\\perl C:%s\\daymet-convert.plx", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CreateProcess(NULL, "%s\\daymet-convert.exe", ROOTDIR, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	m_MetSuccess = 1;
	DaymetFlag = 1;

	CCrop.Format("%s\\inter\\daymet%d", OUTPUT, MetYear);
	fCrop = fopen(CCrop, "r");
	if(fCrop==NULL)
	{
		CString err;
		err.Format("Can not find file %s", CCrop);
		AfxMessageBox(err);
		exit(0);
	}

	m_MetSuccess = 1;
	DaymetFlag = 1;
	int jdd;
	long float jff[7];
	
	for(int i=1;i<=365;i++)
	{
		if(fscanf(fCrop, "%d %lf %lf %lf %lf %lf %lf", &jdd, &jff[1], &jff[2], &jff[3], &jff[4],&jff[5], &jff[6])!=7)
		{
			CString note;
			note.Format("File %s contains error at day %d. Default climate database will be used.", CCrop, i);
			AfxMessageBox(note);
			m_MetSuccess = 0;
			DaymetFlag = 0;
			break;
		}

		if(i!=jdd)
		{
			CString note;
			note.Format("File %s contains error at day %d. Default climate database will be used.", CCrop, i);
			AfxMessageBox(note);
			m_MetSuccess = 0;
			DaymetFlag = 0;
			break;
		}

	}
	fclose(fCrop);
#else
	DaymetFlag = 0;

#endif

	char site_file[80];
		FILE *fp;
	
		sprintf(site_file, "%s\\Inter\\DaymetFlag", OUTPUT);
		fp = fopen(site_file, "w");
		if ( fp == NULL )
		{
			printf("Can not create file %s", site_file);
			getch();
			exit(0);
		}
 
		fprintf(fp, "%d", DaymetFlag);
		fclose(fp);

	UpdateData(FALSE);
	
	
}

void SitePage1::get_defaults(void)
{
	LaiFilename.clear();

	char cst[255];
	sprintf(cst, "%s\\Inter\\InputParameters.txt", OUTPUT);

	//ResetRotation();
	
	ReadInputDatafromDND(cst, 0);

	ReadSoilFeature("UnDefault");

#ifdef WIZARD
	CString CCrop;
	FILE *fCrop;
	float log, lat;

	CCrop.Format("%s\\inter\\SiteLocation.txt", OUTPUT);
	
	fCrop = fopen(CCrop, "r");
	if(fCrop==NULL)
	{
		CString err;
		err.Format("Can not find file %s", CCrop);
		AfxMessageBox(err);
		exit(0);
	}

	fscanf(fCrop, "%f %f", &log, &lat); 
	fclose(fCrop);

	m_Longitude = log;
	m_latitude = lat;
#endif

#ifdef ES
	m_Longitude = 110.0;//(float)log;
	m_latitude = IData.latitude;

#endif

}

void SitePage1::OnDefaulClimate() 
{
	// TODO: Add your control notification handler code here
	char site_file[80];
		FILE *fp;
	
		sprintf(site_file, "%s\\Inter\\DaymetFlag", OUTPUT);
		fp = fopen(site_file, "w");
		if ( fp == NULL )
		{
			printf("Can not create file %s", site_file);
			getch();
			exit(0);
		}
 
		fprintf(fp, "%d", 0);
		fclose(fp);
	
}

void SitePage1::OnDefault() 
{
	// TODO: Add your control notification handler code here

	int i, k=0;
	char cst[255];
	m_ClimateFileList.ResetContent ();
	for (i=1;i<=ClimateFilename.n;i++)
	{
		strcpy(cst,ClimateFilename.get(i));
		if (strlen(cst)==0) continue;
		m_ClimateFileList.InsertString(k,cst);
		k++;
	} 	
	UpdateData(FALSE);
}

void SitePage1::OnWaterYear() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_WaterYr==0) m_WaterYr=1;
	else m_WaterYr=0;

	IData.WaterYr = m_WaterYr;

	if(IData.WaterYr==1) 
	{
		m_years	= 2;
	}
	else m_years = 1;

	UpdateData(FALSE);
	
}

void SitePage1::OnKillfocusYears() 
{
	// TODO: Add your control notification handler code here
	long int oldyr=m_years;

	UpdateData(TRUE);

	if(m_years!=oldyr)
	{
		CString DB;
		FILE *db;
		
		DB.Format("%s\\inter\\OpenFile.txt", OUTPUT);
		db=fopen(DB, "w");
		fprintf(db, "%d\n", 0);
		fclose(db);

		for(int k=1; k<=10; k++)
		{
			
			DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, k);//write: OnKillfocusYears(), OK
			db=fopen(DB, "w");
			fprintf(db, "%d %d %d", k, 1, 1);
			fclose(db);
		}
	}
}

void SitePage1::AcceptPage1()
{
	UpdateData(TRUE);

	if(m_MetSuccess ==0)
	{
		DaymetFlag = m_MetSuccess;
		char site_file[80];
		FILE *fp;
	
		sprintf(site_file, "%s\\Inter\\DaymetFlag", OUTPUT);
		fp = fopen(site_file, "w");
		if ( fp == NULL )
		{
			printf("Can not create file %s", site_file);
			getch();
			exit(0);
		}
 
		fprintf(fp, "%d", DaymetFlag);
		fclose(fp);
	}
	//DaymetFlag = m_DaymetFlag;

	CString fname;
	char    st[255]; 
	int     num, i;
	if (strlen(m_sitename)==0) {
		MessageBox("Please input Site Name","No Data error!",NULL);
		return;
	}
	if (m_latitude==0) {
		MessageBox("Please input Latitude","No Data error!",NULL);
		return;
	}
	if (m_years==0) {
		MessageBox("Please specify number of years","No Data error!",NULL);
		return;
	}
	/*if (m_RainNO3NH4==0) {
		MessageBox("No NO3NH4 data! Please input it","No Data error!",NULL);
		return;
	}*/
	if (m_AirNH3==0) {
		MessageBox("Please input atmospheric NH3 background concentration","No Data error!",NULL);
		return;
	}
	if (m_BaseCO2==0) {
		MessageBox("Please input atmospheric CO2 background concentration","No Data error!",NULL);
		return;
	}
	

		// Get data from the page into IData
	num=m_ClimateFileList.GetCount();
	if(m_Use1File==0)
	{
		if (num==0||num!=m_years) 
		{
			CString note;
			if(m_years==1) note.Format("Please select 1 climate file");
			else note.Format("Please select %d climate files", m_years);
			AfxMessageBox(note);
			return;
		}
	}

	strcpy(IData.sitename, m_sitename);
	if(m_CO2file==1) m_CO2IncreaseRate=-99.9;

	IData.latitude = m_latitude;
	IData.ifdaily = m_RecordDaily;
	IData.ClimateFileType = m_CFileFormat;
	IData.NO3NH4_Rainfall = m_RainNO3NH4;
	IData.NH3_Atmosphere  = m_AirNH3;
	IData.BaseCO2		  = m_BaseCO2;
	IData.if1File = m_Use1File;
	IData.CO2IncreaseRate = m_CO2IncreaseRate;
	IData.CO2file = m_CO2file;
	IData.CO2FileName = m_CO2FileName;
	
	if (IData.years > 0 && IData.years != m_years)
	{
		//ResetRotation();
		IData.Rotation_Number = 0;
		//rotation.dim(1);
	}
	IData.years = m_years;

	ClimateFilename.clear ();
	for (i=1;i<=num;i++) {
		m_ClimateFileList.GetText(i-1,fname);
		strcpy(st,fname);
		ClimateFilename.insert(i,st);
	}
	IData.ClimateFileNumber= ClimateFilename.n;

	//RecordClimateFile(0, 0);//DaymetFlag);

	if(LaiFlag==1)
	{
	LaiFilename.clear();
	m_LAIFileList.GetText(0,fname);
	strcpy(st,fname);
	LaiFilename.insert(1,st);
	}

	CString LLAI;
	FILE *llai;

	LLAI.Format("%s\\Inter\\TotalYears", OUTPUT);
	llai = fopen(LLAI, "w");
	fprintf(llai, "%d", m_years);
	fclose(llai);

	LLAI.Format("%s\\Inter\\Observed_LAI.txt", OUTPUT);
	llai = fopen(LLAI, "w");
	if(llai==NULL)
	{
		CString note;
		note.Format("Can not create file %s", LLAI);
		AfxMessageBox(note);
		exit(0);

	}
	if(LaiFlag==1) fprintf(llai, "%d  %s", LaiFlag, st);
	else fprintf(llai, "%d ", 0);
	fclose(llai);

	

	//ReSetCcomponent();
	//RecordClimateFile (0);
}
void SitePage1::SelectCO2File()
{

	
	
	char FileName[255];
	UpdateData(TRUE);
	int rrr, yyy;
	CString pre_CO2FileName[5];
	CString f_site, cst;
	FILE *Fsite;


	//Open a menu window
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();

	POSITION pos=ask.GetStartPosition();
	
	

	//Count number (num) of selected strings
	int k,num;
	num = m_CO2FileList.GetCount();//1 FG
		
	//Obtain order number (k) of each selected string
	k = m_CO2FileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		//Obtain a character from the string
		pre_CO2FileName[num].Format("%s", ask.GetNextPathName(pos));
		if (pre_CO2FileName[num]=="") break;


		//Add the character into pre_ClimateFileName[num]
		m_CO2FileList.InsertString(k, pre_CO2FileName[num]);

		if (cst.IsEmpty() || pos==NULL) break;		
		if (m_CO2FileList.GetCount()==1) break;

		k++;
	}


	m_CO2FileName=pre_CO2FileName[0];
	//Put the string on screen
	m_CO2FileList.SetCurSel(k);

	
	UpdateData(FALSE);

}
void SitePage1::SelectClimFile()
{
	//UpdateData(TRUE);
	if (m_years<=0) {
		MessageBox("Please input the simulated years firstly","Input Error:",NULL);
		return;
	}

	char FileName[255];
	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_ClimateFileList.GetCount();
	if (num==m_years) return;
	
	k=m_ClimateFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_ClimateFileList.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ClimateFileList.GetCount()==m_years) break;
		k++;
	}
	m_ClimateFileList.SetCurSel(k);
}

void SitePage1::ClimMoveDown()
{
	int num,selfile;
	num=m_ClimateFileList.GetCount();
	selfile=m_ClimateFileList.GetCurSel();
	
	char tmp[255],tmp1[255];
	if (selfile<num-1 && selfile>=0) {
		m_ClimateFileList.GetText(selfile,tmp);
		m_ClimateFileList.GetText(selfile+1,tmp1);
		m_ClimateFileList.DeleteString(selfile);
		m_ClimateFileList.InsertString(selfile+1,tmp);
	}
}

void SitePage1::ClimMoveUp()
{
	int num,selfile;
	num=m_ClimateFileList.GetCount();
	selfile=m_ClimateFileList.GetCurSel();
	
	char tmp[255],tmp1[255];
	if (selfile<=num-1 && selfile>0) {
		m_ClimateFileList.GetText(selfile,tmp);
		m_ClimateFileList.GetText(selfile-1,tmp1);
		m_ClimateFileList.DeleteString(selfile);
		m_ClimateFileList.InsertString(selfile-1,tmp);
	}
}	



void SitePage1::OnCListFileName() 
{
	// TODO: Add your control notification handler code here
	int num;
	char ListName[300];

	CListFile ww;
	if(ww.DoModal()==IDOK)
	{
		int i;//m_SelectCrop.GetCurSel();
		FILE *fp;
		char fname[256],str[256];

		sprintf(fname,"%s\\Inter\\ClimateFileList", OUTPUT);
		fp=fopen(fname,"r");
		if (fp==NULL) note(0, fname);
		
		fscanf(fp,"%s",ListName);
		fclose(fp);

		m_ClimateFileList.ResetContent();
		
		fp=fopen(ListName,"r");
		if (fp==NULL) 
		{
			CString note;
			note.Format("Cannot open file %s", fname);
			AfxMessageBox(note);
			exit(0);
		}	
	
		fscanf(fp,"%d",&num);
		
		if(m_years>num)
		{
			CString note;
			note.Format("The number of climate files in the list is less than the simulated years: %d (yrs) vs. %d (files)", m_years, num);
			AfxMessageBox(note);
			exit(0);
		}

		CString climname[300];
		for (i=0;i<num;i++)
		{
			if (fscanf(fp,"%s",str)!=1) break;
			else
				climname[i]=str;

			EraseSpaceB(str);

			sprintf(fname,"%s",climname[i]);
			m_ClimateFileList.AddString(fname);
			
		}
		fclose(fp);

		if (num>=0) m_ClimateFileList.SetCurSel(num);
	}
	
}

char * EraseSpaceB(char *str)
{
	while (str[0]==32)
	{
		sprintf(str,"%s",str+1);
	}
	int l=strlen(str);
	if (l>0) 
	{
		while (str[l-1]<=32)
		{
			str[strlen(str)-1]='\0';
			l=strlen(str);
		}
	}
	return str;
}

void SitePage1::OnCO2file() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_CO2IncreaseRate = -99.9;

	CEdit *Edt;
		
	if(m_CO2file==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_CO2IncreaseRate);
		Edt->EnableWindow(FALSE);
		//put file handler for pointing to file here
		SelectCO2File();



	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_CO2IncreaseRate);
		Edt->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

#ifdef MANURE
void CreateBlankManureFiles()
{
	int i;
	CString SF, MP, DB;
	FILE* sf, *mp, *db;

	for(int m_FeedlotYear=0; m_FeedlotYear<=10; m_FeedlotYear++)
	{
		for(i=0; i<=10; i++)
		{
			SF.Format("%s\\Result\\Inter\\ManureHouse_%d_%d.txt", ROOTDIR, m_FeedlotYear, i);
			sf=fopen(SF, "w");
			if(sf==NULL) note(1, SF);
			
			fprintf(sf, "%d  %d\n", 0, 1);  
			fprintf(sf, "%3d  %8.2f  %8.2f  %8.4f  %8.4f\n", 0, 0.0, 0.0, 0.0, 0.0);	
			fprintf(sf, "%f  %d\n", 0.0, 0);//0 slatted floor; 1 conrete floor
			fprintf(sf, "%d  %f  %d  %f\n", 0, 0.0, 0, 0.0);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			fprintf(sf, "%d  %f  %s\n", 0, 0.0, "None");// 0 natural, 1 fan
			fprintf(sf, "%f\n", 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%d %f\n", -1, 0.0);

			fclose(sf);

			/*for(int YFM=1; YFM<=49; YFM++)
			{
				DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, i, YFM);
				db=fopen(DB, "w");	
				fprintf(db, "%d %f %f\n", i, 0.0, 0.0); 
				fclose(db);
			}*/
		}

		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Result\\inter\\TotalFeedLots_%d", ROOTDIR, m_FeedlotYear);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", 1);
		fclose(TFL);
	}

	SF.Format("%s\\Result\\Inter\\ManureGraze.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d  %d  %d  %f\n", 0, 8, 0, 0.0);  
	
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureLagoon.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %f  %d  %d  %d\n", 0.0, 0.0, 0, 0, 0);  
	fprintf(sf, "%d %d %f  %f  %f\n", 0, 0, 0.0, 0.0, 0.0); 
	fprintf(sf, "%d %f\n", 0, 0.0);
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureCompost.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %d  %d  %f  %f\n", 0.0, 0, 0, 0.0, 0.0);  
	//fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureDigester.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d  %f  %f\n", 0, 0.0, 0.0);    
	fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureField.txt", ROOTDIR);
	sf=fopen(SF, "w");

	if(sf==NULL) note(1, SF);
	fprintf(sf, "%f", 0.0);    
	fclose(sf);

	CString XFF;
	FILE *xff;
/*	XFF.Format("%s\\inter\\ManureFieldCrops", OUTPUT);		
	xff=fopen(XFF, "w");
	fprintf(xff, "%d\n", 0);
	fclose(xff);*/

	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", 0, 0, 0);
	fclose(xff);

}
#endif

void SitePage1::OnKillfocusSiteName() 
{
	// TODO: Add your control notification handler code here
/*#ifdef MANURE
	CString SF;
	FILE *sf;

	for(int m_FeedlotYear=0; m_FeedlotYear<=10; m_FeedlotYear++)
	{
		for(int i=0; i<=10; i++)
		{
			SF.Format("%s\\Result\\Inter\\ManureHouse_%d_%d.txt", ROOTDIR, m_FeedlotYear, i);
			sf=fopen(SF, "w");
			if(sf==NULL) note(1, SF);
			
			fprintf(sf, "%d  %d\n", 0, 1);  
			fprintf(sf, "%3d  %8.2f  %8.2f  %8.4f  %8.4f\n", 0, 0.0, 0.0, 0.0, 0.0);	
			fprintf(sf, "%f  %d\n", 0.0, 0);//0 slatted floor; 1 conrete floor
			fprintf(sf, "%d  %f  %d  %f\n", 0, 0.0, 0, 0.0);//0 None, 1 straw, 2 sawdust, 3 dry manure solids, 4 sand
			fprintf(sf, "%d  %f  %s\n", 0, 0.0, "None");// 0 natural, 1 fan
			fprintf(sf, "%f\n", 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(sf, "%d\n", -1);

			fclose(sf);
		}

		CString TotalFeedlots;
		FILE *TFL;
		TotalFeedlots.Format("%s\\Result\\inter\\TotalFeedLots_%d", ROOTDIR, 1);
		TFL=fopen(TotalFeedlots, "w");
		if(TFL==NULL) note(1, TotalFeedlots);
		fprintf(TFL, "%d", 1);
		fclose(TFL);
	}

	SF.Format("%s\\Result\\Inter\\ManureGraze.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d  %d  %d  %f\n", 0, 8, 0, 0.0);  
	
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureLagoon.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %f  %d  %d  %d\n", 0.0, 0.0, 0, 0, 0);  
	fprintf(sf, "%d %d %f  %f  %f\n", 0, 0, 0.0, 0.0, 0.0); 
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureCompost.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%f  %d  %d  %f  %f\n", 0.0, 0, 0, 0.0, 0.0);  
	//fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureDigester.txt", ROOTDIR);
	sf=fopen(SF, "w");
	if(sf==NULL) note(1, SF);

	fprintf(sf, "%d  %f  %f\n", 0, 0.0, 0.0);    
	fprintf(sf, "%f  %f  %f\n", 0.0, 0.0, 0.0);
	fclose(sf);

	SF.Format("%s\\Result\\Inter\\ManureField.txt", ROOTDIR);
	sf=fopen(SF, "w");

	if(sf==NULL) note(1, SF);
	fprintf(sf, "%f", 0.0);    
	fclose(sf);

	CString XFF;
	FILE *xff;

	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", 0, 0, 0);
	fclose(xff);
#endif
	*/
}
