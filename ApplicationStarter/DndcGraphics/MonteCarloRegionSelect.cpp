// MonteCarloRegionSelect.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "MonteCarloRegionSelect.h"
#include "dndc_tool.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char SelectFileName[300], IndexFile[300], FullName[300], RootPart[300], stateName[300], CCNAME[300];
char ClimateFileLocation[300], cropName[140][50], Crop_ID[140][50], HarvestDate[50];
int Crop_Type, cc = 0, CCID;	
float cropHa[110];
float lon, lat, Ndeposit, s1,s2,s3,s4,s5,s6,s7,s8;
/////////////////////////////////////////////////////////////////////////////
// MonteCarloRegionSelect dialog


MonteCarloRegionSelect::MonteCarloRegionSelect(CWnd* pParent /*=NULL*/)
	: CDialog(MonteCarloRegionSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(MonteCarloRegionSelect)
	m_year = 2000;
	m_s1 = 0.0f;
	m_s2 = 0.0f;
	m_s3 = 0.0f;
	m_s4 = 0.0f;
	m_s5 = 0.0f;
	m_s6 = 0.0f;
	m_s7 = 0.0f;
	m_s8 = 0.0f;
	m_ClimateFileName = _T("");
	m_State = _T("");
	m_CountyID = 0;
	m_County = _T("");
	m_Crop1 = _T("");
	m_Crop2 = _T("");
	m_Crop3 = _T("");
	m_Fert1 = 0.0f;
	m_Fert2 = 0.0f;
	m_Fert3 = 0.0f;
	m_TotalCrops = 0;
	m_date1 = 0;
	m_date1b = 0;
	m_date2 = 0;
	m_date2b = 0;
	m_date3 = 0;
	m_date3b = 0;
	//}}AFX_DATA_INIT
}


void MonteCarloRegionSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MonteCarloRegionSelect)
	DDX_Control(pDX, IDC_ClimateFileLocation, m_ClimFileLocation);
	DDX_Control(pDX, IDC_WizardCrops, m_WizardCrops);
	DDX_Control(pDX, IDC_CountyNames, m_CountyNames);
	DDX_Control(pDX, IDC_IndexFile, m_IndexFile);
	DDX_Text(pDX, IDC_year, m_year);
	DDX_Text(pDX, IDC_S1, m_s1);
	DDX_Text(pDX, IDC_S2, m_s2);
	DDX_Text(pDX, IDC_S3, m_s3);
	DDX_Text(pDX, IDC_S4, m_s4);
	DDX_Text(pDX, IDC_S5, m_s5);
	DDX_Text(pDX, IDC_S6, m_s6);
	DDX_Text(pDX, IDC_S7, m_s7);
	DDX_Text(pDX, IDC_S8, m_s8);
	DDX_Text(pDX, IDC_ClimateFileName, m_ClimateFileName);
	DDX_Text(pDX, IDC_State, m_State);
	DDX_Text(pDX, IDC_CountyID, m_CountyID);
	DDX_Text(pDX, IDC_County, m_County);
	DDX_Text(pDX, IDC_crop1, m_Crop1);
	DDX_Text(pDX, IDC_crop2, m_Crop2);
	DDX_Text(pDX, IDC_crop3, m_Crop3);
	DDX_Text(pDX, IDC_fert1, m_Fert1);
	DDX_Text(pDX, IDC_fert2, m_Fert2);
	DDX_Text(pDX, IDC_fert3, m_Fert3);
	DDX_Text(pDX, IDC_TotalCrops, m_TotalCrops);
	DDX_Text(pDX, IDC_date1, m_date1);
	DDX_Text(pDX, IDC_date1b, m_date1b);
	DDX_Text(pDX, IDC_date2, m_date2);
	DDX_Text(pDX, IDC_date2b, m_date2b);
	DDX_Text(pDX, IDC_date3, m_date3);
	DDX_Text(pDX, IDC_date3b, m_date3b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MonteCarloRegionSelect, CDialog)
	//{{AFX_MSG_MAP(MonteCarloRegionSelect)
	ON_BN_CLICKED(IDC_SelectIndexFile, OnSelectIndexFile)
	ON_CBN_SELCHANGE(IDC_CountyNames, OnSelchangeCountyNames)
	ON_CBN_SELCHANGE(IDC_WizardCrops, OnSelchangeWizardCrops)
	ON_BN_CLICKED(IDC_SelectIndexFile2, OnSelectIndexFile2)
	ON_LBN_DBLCLK(IDC_IndexFile, OnDblclkIndexFile)
	ON_CBN_DBLCLK(IDC_WizardCrops, OnDblclkWizardCrops)
	ON_LBN_DBLCLK(IDC_ClimateFileLocation, OnDblclkClimateFileLocation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MonteCarloRegionSelect message handlers

void MonteCarloRegionSelect::OnSelectIndexFile() 
{
	// TODO: Add your control notification handler code here
	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_IndexFile.GetCount();
	if (num==1) return;
	
	k=m_IndexFile.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(SelectFileName,cst);
		m_IndexFile.InsertString(k,SelectFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_IndexFile.GetCount()==1) break;
		k++;
	}
	m_IndexFile.SetCurSel(k);

	sprintf(IndexFile, "%s", SelectFileName);

	///////////////////////////////////////////
	CString CP;
	int i, L1, L2, L3;

	int LL=strlen(SelectFileName);
	for(i=LL; i>=0; i--)
	{
		if(SelectFileName[i]=='_') 
		{
			L1=i-1;
			break;
		}
	}

	for(i=LL; i>=0; i--)
	{
		if(SelectFileName[i]==92) 
		{
			L2=i+1;
			break;
		}
	}

	L3 = L2 - 5;

	Glean_String(SelectFileName, L2, L1, FullName);
	Glean_String(SelectFileName, 0, L3, RootPart);
	
	CP.Format("%s", FullName);

	int RegionCode = 0;

	CString Fregion;
	FILE *region;

	Fregion.Format("%s\\SelectedRegion", INTER);
	region = fopen(Fregion, "w");

	if (region==NULL)
	{
		char err[120];
		sprintf(err, "Can not create %s", Fregion);
		AfxMessageBox(err);
		exit(0); 
	}

	fprintf(region, "%d %d\n", -1, 0);
	fprintf(region, "%s\n", CP);
	fprintf(region, "%s\n", RootPart);
	fclose (region);

	////////////////////////////////////////////

	char MM[300];

	CString RF;
	FILE* ref;
	RF.Format("%s", IndexFile); 
	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}

	m_CountyNames.ResetContent();
	
	char Cname[300];
	fgets(MM, 200, ref);
	for(;;)
	{
		cc++;

		//if(fscanf(ref, "%s %s %s", cID[cc], stateName, countyName[cc])!=3) 
		if(fscanf(ref, "%d %s %s", &CCID, stateName, CCNAME)!=3)
			break;		
		else
		{
			fgets(MM, 300, ref);
			sprintf(Cname,"%d  %s",CCID, CCNAME);
			m_CountyNames.AddString(Cname);
		}

		//sprintf(str, CCNAME);
		//EraseFBSpace(str);
		//sprintf(Cname,"%s  %s",CCID, CCNAME);
		//m_CountyNames.AddString(Cname);
	}

	//m_CountyNames.ResetContent();
	
	//char Cname[300], str[300];
	
	/*for (i=1;i<=cc-1;i++)
	{
		sprintf(str, countyName[i]);
		//EraseFBSpace(str);
		sprintf(Cname,"%s  %s",cID[i],str);
		m_CountyNames.AddString(Cname);
		//Cname[i]=str;
	}*/

	UpdateData(FALSE);
}

void MonteCarloRegionSelect::OnSelchangeCountyNames() 
{
	// TODO: Add your control notification handler code here
	CString RF, COUNTYID;
	FILE* ref;
	char MM[300];
	int CountyOrder, CCID, ccID;
	int cc = 0;
	int i;
	char str[300], fname[256];
	int cropNumber;
	char ClimName[300];
		
	UpdateData(TRUE);

	Crop_Type = -1;
	
	CountyOrder = m_CountyNames.GetCurSel()+1;

	RF.Format("%s\\GIS\\%s_1.txt", RootPart, FullName);
	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}

	fgets(MM, 300, ref);
	for(;;)
	{
		if(fscanf(ref, "%d %s %s %f %f %s %f %f %f %f %f %f %f %f %f", 
			&CCID, stateName, CCNAME, &lon, &lat, ClimName, &Ndeposit, &s1,&s2,&s3,&s4,&s5,&s6,&s7,&s8)!=15)
			break;		
		else
		{
			cc++;

			if(cc==CountyOrder)
			{
				m_CountyID =CCID;
				m_State = stateName;
				m_County = CCNAME;
				m_s1=s1;m_s2=s2;m_s3=s3;m_s4=s4;m_s5=s5;m_s6=s6;m_s7=s7;m_s8=s8;
				m_ClimateFileName.Format("%s",ClimName);
				break;
			}			
		}
	}
	fclose(ref);

	m_WizardCrops.ResetContent();

	for(i=0; i<109; i++) cropHa[i]=0.0;	
	
	//cropping system area, ha
	RF.Format("%s\\GIS\\%s_2.txt", RootPart, FullName);
	ref = fopen(RF, "r");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}

	int jd;

	fgets(MM, 300, ref);
	fscanf(ref, "%d", &cropNumber);
	for(i=1; i<=cropNumber; i++) fscanf(ref, "%s", cropName[i]);
	fscanf(ref, "%d", &jd);
	for(i=1; i<=cropNumber; i++) fscanf(ref, "%s", Crop_ID[i]);
	for(i=1; i<=cc; i++)
	{
		fscanf(ref, "%d", &ccID);
		for(int j=1; j<=cropNumber; j++) 
		{
			fscanf(ref, "%f", &cropHa[j]);
		}
		//if(ccID==CCID) break;				
	}
	fclose(ref);

	for(i=1; i<=cropNumber; i++)
	{
		sprintf(fname,"%s        (%.0f ha)", cropName[i], cropHa[i]);
		m_WizardCrops.AddString(fname);
	}


	
	UpdateData(FALSE);
	
}

void MonteCarloRegionSelect::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	float Fert[5]={0.0,0.0};
	char PlantDate[50][50], HarvestDate[50][50];

	Fert[1]=m_Fert1;
	Fert[2]=m_Fert2;
	Fert[3]=m_Fert3;
	sprintf(PlantDate[1], "%d", m_date1);
	sprintf(PlantDate[2], "%d", m_date2);
	sprintf(PlantDate[3], "%d", m_date3);
	
	sprintf(HarvestDate[1], "%d_%d", m_date1, m_date1b);
	sprintf(HarvestDate[2], "%d_%d", m_date2, m_date2b);
	sprintf(HarvestDate[3], "%d_%d", m_date3, m_date3b);
	
	int CropOrder;
	CropOrder = m_WizardCrops.GetCurSel()+1;
	
	if(Crop_Type==-1)
	{
		AfxMessageBox("Please select a crop type");
		return;
	}

	CString IDfile;
	
	CString RF;
	FILE* ref;

	RF.Format("%s\\Inter\\SelectSite.txt", OUTPUT);
	ref = fopen(RF, "w");
	if(ref==NULL)
	{
		CString note;
		note.Format("Can not create file %s", RF);
		AfxMessageBox(note);
		exit(0); 
	}
	fprintf(ref, "%s  %s  %d\n", m_State, m_County, m_CountyID);
	fprintf(ref, "%s  %f\n", Crop_ID[CropOrder], cropHa[CropOrder]);
	fprintf(ref, "%s  %s\n", RootPart, FullName);
	fprintf(ref, "%s\n", ClimateFileLocation);
	fprintf(ref, "%d\n", m_year);
	fprintf(ref, "%f %f %f %f %f %f %f %f\n", m_s1, m_s2, m_s3, m_s4, m_s5, m_s6, m_s7, m_s8);
	fprintf(ref, "%f %f %f\n", lon, lat, Ndeposit); 
	
	fprintf(ref, "%d\n", m_TotalCrops); 
	 
	for(int i=1;i<=m_TotalCrops;i++)
	{
		fprintf(ref, "%s\n", HarvestDate[i]);
		fprintf(ref, "%s\n", PlantDate[1]);//fertilizing data
		fprintf(ref, "%f\n", Fert[i]); 
	}
	
	fclose(ref);

	CDialog::OnOK();
}

void MonteCarloRegionSelect::OnSelectIndexFile2() 
{
	// TODO: Add your control notification handler code here
	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_ClimFileLocation.GetCount();
	if (num==1) return;
	
	k=m_ClimFileLocation.GetCurSel();
	if (k==-1) k=num;
	else k++;

	//cst=ask.GetFileTitle();
	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(SelectFileName,cst);
		m_ClimFileLocation.InsertString(k,SelectFileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_ClimFileLocation.GetCount()==1) break;
		k++;
	}
	m_ClimFileLocation.SetCurSel(k);

	sprintf(ClimateFileLocation, "%s", SelectFileName);
}

void MonteCarloRegionSelect::OnSelchangeWizardCrops() 
{
	// TODO: Add your control notification handler code here
	int i, j, crops, ccID, CID[150], CropNumber;
	char c_crop[150][50], c_CropID[150], js[50], MM[200], PHdate[150][50];
	float FertRate[150];
	CString RF;
	FILE *ref;

	UpdateData(TRUE);

	CCID = m_CountyID;
	Crop_Type = m_WizardCrops.GetCurSel()+1;

	FindCrops(Crop_ID[Crop_Type], CID, &CropNumber); 

	//fertilizer rate, kg N/ha/crop
	RF.Format("%s\\GIS\\%s_3.txt", RootPart, FullName);
	ref = fopen(RF, "r");
	if(ref==NULL) note(0, RF);
	
	fgets(MM, 300, ref);
	fscanf(ref, "%d", &crops);
	for(i=1; i<=crops; i++) fscanf(ref, "%s", c_crop[i]);
	fscanf(ref, "%s", js);
	for(i=1; i<=crops; i++) fscanf(ref, "%d", &c_CropID[i]);
	for(i=1; i<=cc; i++)
	{
		fscanf(ref, "%d", &ccID);
		for(int j=1; j<=crops; j++) 
		{
			fscanf(ref, "%f", &FertRate[c_CropID[j]]);
		}
		
		if(ccID==CCID) 
			break;				
	}
	fclose(ref);

	int k=0;
	float cccFERT[150];
	char cccNAME[150][50];

	for(i=1;i<=3;i++)
	{
		sprintf(cccNAME[i], "None"); 
		cccFERT[i] = 0.0;
	}

	for(i=0;i<=crops;i++)
	{
		if(c_CropID[i]==CID[1]) 
		{
			k++;
			sprintf(cccNAME[k], "%s", c_crop[i]); 
			cccFERT[k] = FertRate[c_CropID[i]];
		}

		if(c_CropID[i]==CID[2]) 
		{
			k++;
			sprintf(cccNAME[k], "%s", c_crop[i]); 
			cccFERT[k] = FertRate[c_CropID[i]];
		}

		if(c_CropID[i]==CID[3]) 
		{
			k++;
			sprintf(cccNAME[k], "%s", c_crop[i]); 
			cccFERT[k] = FertRate[c_CropID[i]];
		}
	}

	m_Crop1.Format("%s", cccNAME[1]);
	m_Crop2.Format("%s", cccNAME[2]);
	m_Crop3.Format("%s", cccNAME[3]);
	
	m_Fert1 = cccFERT[1];
	m_Fert2 = cccFERT[2];
	m_Fert3 = cccFERT[3];

	//planting-harvest dates
	char SystemID[150][50];
	int WinterCrop, WCN;

	RF.Format("%s\\GIS\\%s_5.txt", RootPart, FullName);
	ref = fopen(RF, "r");
	if(ref==NULL) note(0, RF);
	
	fgets(MM, 300, ref);
	fscanf(ref, "%d", &crops);
	for(i=1; i<=crops; i++) fscanf(ref, "%s", c_crop[i]);
	fscanf(ref, "%s", js);
	for(i=1; i<=crops; i++) fscanf(ref, "%s", SystemID[i]);
	for(i=1; i<=cc; i++)
	{
		fscanf(ref, "%d", &ccID);
		for(int j=1; j<=crops; j++) 
		{
			fscanf(ref, "%s", PHdate[j]);
		}
		
		if(ccID==CCID) 
			break;				
	}
	fclose(ref);

	int plant_jday[5]={0,0}, harvest_jday[5]={0,0};

	sprintf(HarvestDate, "%s", PHdate[Crop_Type]);

	DefinePHDates(PHdate[Crop_Type], plant_jday, harvest_jday, &CropNumber, &WinterCrop, &WCN);

	k=0;	

	m_date1 = plant_jday[1];
	m_date1b = harvest_jday[1];
	m_date2 = plant_jday[2];
	m_date2b = harvest_jday[2];
	m_date3 = plant_jday[3];
	m_date3b = harvest_jday[3];	

	m_TotalCrops = CropNumber;

	UpdateData(FALSE);
}

void MonteCarloRegionSelect::OnDblclkIndexFile() 
{
	// TODO: Add your control notification handler code here
	int i,num;
	
	num=m_IndexFile.GetCount();
	i=m_IndexFile.GetCurSel();
	
	CString fname;
	m_IndexFile.GetText(i,fname);
	m_IndexFile.DeleteString(i);	
	return;
}

void MonteCarloRegionSelect::OnDblclkWizardCrops() 
{
	// TODO: Add your control notification handler code here
/*	int i,num;
	
	num=m_WizardCrops.GetCount();
	i=m_WizardCrops.GetCurSel();
	
	CString fname;
	m_WizardCrops.GetText(i,fname);
	m_WizardCrops.DeleteString(i);	
	return;*/
}

void MonteCarloRegionSelect::OnDblclkClimateFileLocation() 
{
	// TODO: Add your control notification handler code here
	int i,num;
	
	num=m_ClimFileLocation.GetCount();
	i=m_ClimFileLocation.GetCurSel();
	
	CString fname;
	m_ClimFileLocation.GetText(i,fname);
	m_ClimFileLocation.DeleteString(i);	
	return;
}
