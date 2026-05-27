// SitePage3.cpp : implementation file
//
#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage2.h"
#include "SitePage3.h"
#include "SitePSheet.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CropArray			Crop;
extern Site_BaseInformation	IData ;
extern StringArray			ClimateFilename;
//extern RotationArray		rotation;
//extern Cycle_a_year			cycle;
//extern TillArray			till;
//extern FerArray				fer;
//extern ManureArray			manure;
//extern WeedArray			weed;
//extern FloodArray			flood;
//extern IrrigationArray		irrigation;
//extern GrazingArray         grazing;
//extern NowCropPractices		NowC;
//extern CropProperty CropPty;
//extern float NanuCN[4];
extern CropofEachYear CYr[2];
//extern int   MaxCycle;
//extern char  Workdir[255];
extern char *soiltexture[];
extern char *soillanduse[];

int CropColor[500]={-1,-1};
int CrCo[61]={99,99};
int RR[50]={255,252,0,  148,153,  0,244,237,229,162,  0, 64,  0,200,245,210,163,0,  255,165,0,   187,253, 0,  0,202,163,219,243, 85,37,  0,237,237,173,0,243,243,133,133,0,   253,312,153,153,237,  0,218,187,250};
int GG[50]={255,183,147, 68,206,167,122, 27,208, 95,175,163,172,166,152, 30,134,0,  233, 34,188, 30,209, 96,122,220,134,136,237,166,58,151,21, 26,213,121,129,129,129,174,103,186, 68,186,216, 27,171,235,183,181};
int BB[50]={255,88,216, 154,135,80,  55, 50, 29, 33,134, 72,216, 45,167, 77,190,100,168,127,236, 83,184,174,137, 74,190, 39, 99, 70,122,112,88, 57,134,121,148,217,217,217,33, 18,154, 60,228, 50,228,202,220,151};


/////////////////////////////////////////////////////////////////////////////
// SitePage3 property page

IMPLEMENT_DYNCREATE(SitePage3, CPropertyPage)

SitePage3::SitePage3() : CPropertyPage(SitePage3::IDD)
{
	//{{AFX_DATA_INIT(SitePage3)
	m_PlantType = -1;
	m_RotationN = 0;
	m_RotationID = 0;
	m_CycleYear = 0;
	m_RotationYear = 0;
	m_YearACycle = 1;
	m_ShowTYear = 0;
	m_RotationCycles = 0.0f;
	m_SystemYears = 0;
	m_SystemCycleYears = 0;
	//}}AFX_DATA_INIT
}

SitePage3::~SitePage3()
{
}

void SitePage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage3)
	DDX_Control(pDX, IDC_System, m_System);
	DDX_Control(pDX, IDC_LIST3, m_CropList);
	DDX_Control(pDX, IDC_NextRotation, m_NextR);
	DDX_Control(pDX, IDC_LastRotation, m_LastR);
	DDX_Control(pDX, IDC_InputCrop, m_InputCrop);
	DDX_Radio(pDX, IDC_PlantType, m_PlantType);
	DDX_Text(pDX, IDC_RotationN, m_RotationN);
	DDX_Text(pDX, IDC_RotationID, m_RotationID);
	DDX_Text(pDX, IDC_CycleYear, m_CycleYear);
	DDX_Text(pDX, IDC_RotationYear, m_RotationYear);
	DDX_Text(pDX, IDC_YearACycle, m_YearACycle);
	DDX_Text(pDX, IDC_ShowTYear, m_ShowTYear);
	DDX_Text(pDX, IDC_RotationCycles, m_RotationCycles);
	DDX_Text(pDX, IDC_SystemYears, m_SystemYears);
	DDX_Text(pDX, IDC_OneCycleYears, m_SystemCycleYears);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage3, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage3)
	ON_BN_CLICKED(IDC_InputCrop, OnInputCrop)
	ON_EN_KILLFOCUS(IDC_CycleYear, OnKillfocusCycleYear)
	ON_BN_CLICKED(IDC_LastRotation, OnLastRotation)
	ON_BN_CLICKED(IDC_LastRotation2, OnLastRotation2)
	ON_BN_CLICKED(IDC_NextRotation, OnNextRotation)
	ON_BN_CLICKED(IDC_NextRotation2, OnNextRotation2)
	ON_EN_KILLFOCUS(IDC_RotationYear, OnKillfocusRotationYear)
	ON_EN_KILLFOCUS(IDC_RotationN, OnKillfocusRotationN)
	ON_EN_SETFOCUS(IDC_RotationCycles, OnSetfocusRotationCycles)
	ON_CBN_KILLFOCUS(IDC_System, OnKillfocusSystem)
	ON_CBN_SELCHANGE(IDC_System, OnSelchangeSystem)
	ON_EN_KILLFOCUS(IDC_SystemYears, OnKillfocusSystemYears)
	ON_EN_KILLFOCUS(IDC_OneCycleYears, OnKillfocusOneCycleYears)
	ON_BN_CLICKED(IDC_ViewRotation, OnViewRotation)
	ON_BN_CLICKED(IDC_ManureFarmSoil, OnManureFarmSoil)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage3 message handlers
BOOL SitePage3::OnSetActive() 
{
	//DrawYearScale();

	int TotalYears=0;

	CString DB;
	FILE *db;

	DB.Format("%s_1\\CropRotation.txt", INTERMANAGE);
	db=fopen(DB, "r");
	if(db==NULL)
	{
		db_Rotation_Number = 1;
		db=fopen(DB, "w");
		fprintf(db, "%d\n", db_Rotation_Number);
		fclose(db);
	}
	else
	{
		fscanf(db, "%d", &db_Rotation_Number);
		fclose(db);
	}

	DB.Format("%s\\Inter\\OpenFile.txt", OUTPUT);
	db=fopen(DB, "r");
	fscanf(db, "%d", &OpenFile);
	fclose(db);

	TotalYears = IData.years;

	if(OpenFile==0)
	{
		for(int rrr=1; rrr<=db_Rotation_Number; rrr++)
		{
			db_RotationID[rrr]=1;
			if(db_Rotation_Number==1) 
			{
				db_RotateSpan[rrr] = TotalYears;
				db_CycleSpan[rrr] = 1;
			}
			else
			{
				db_RotateSpan[rrr] = 1;
				db_CycleSpan[rrr] = 1;
			}
			
			DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, rrr);//read: OnSetActive() 
			db=fopen(DB, "w");
			fprintf(db, "%d %d %d", db_RotationID[rrr], db_RotateSpan[rrr], db_CycleSpan[rrr]);
			fclose(db);

			db_RotationCycles[rrr] = (float)db_RotateSpan[rrr] / (float)db_CycleSpan[rrr];
		}		
	}
	else
	{
		int TYr=0;
		for(int rrr=1; rrr<=db_Rotation_Number; rrr++)
		{			
			
			DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, rrr);//read: OnSetActive() 
			db=fopen(DB, "r");
			fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
			fclose(db);

			TYr += db_RotateSpan[rrr];

			db_RotationCycles[rrr] = (float)db_RotateSpan[rrr] / (float)db_CycleSpan[rrr];
		}

		if(TYr != TotalYears)
		{
			CString note;
			note.Format("Warning: Number of simulated years has been changed. Indicates that the dnd file is not reading correct. Check to make sure you have all the necessary parameters set in each category block in the dnd file");
			AfxMessageBox(note);
			//return 0;
		}

	}

	//sprintf(ch,"%d",IData.years);
	/* 
	if(TotalYears!=m_ShowTYear)
	{
		CString note;
		note.Format("Error for total simulated years");
		AfxMessageBox(note);
		return 0;
	}*/
		
	m_ShowTYear=TotalYears;
	m_RotationN  = db_Rotation_Number;
	m_RotationID = 1;	
	
	m_RotationYear=db_RotateSpan[m_RotationID];

	m_CycleYear=db_CycleSpan[m_RotationID];

	m_RotationCycles = (float)m_RotationYear / (float)m_CycleYear;//m_CycleYear

	if(m_YearACycle>m_CycleYear) m_YearACycle=1;

	UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}

void SitePage3::OnInputCrop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString DB;
	FILE *db, *dbq;

	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	db=fopen(DB, "w");
	fprintf(db, "%d %d", m_RotationID, m_YearACycle);
	fclose(db);

	DB.Format("%s_1\\CropRotation.txt", INTERMANAGE);//###
	db=fopen(DB, "w");
	fprintf(db, "%d", m_RotationN);
	fclose(db);

	DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, m_RotationID);//write: OnInputCrop(), OK
	db=fopen(DB, "w");
	fprintf(db, "%d %d %d", m_RotationID, m_RotationYear, m_CycleYear);
	fclose(db);

	UpdateData(TRUE);

	//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
	DB.Format("%s_1\\CropRotation_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
			//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
		DB.Format("%s_1\\CropRotation_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d\n", 0);
			fclose(db);
	}
	else
		fclose(dbq);

	//DB.Format("%s\\Inter\\CropTill_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
	DB.Format("%s_1\\CropTill_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		//DB.Format("%s\\Inter\\CropTill_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);	
		DB.Format("%s_1\\CropTill_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);	
		db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d\n", 0);
			fclose(db);
	}
	else
		fclose(dbq);

	//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
	DB.Format("%s_1\\CropFert_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
		DB.Format("%s_1\\CropFert_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d", 0);
			fclose(db);
	}
	else fclose(dbq);

	//DB.Format("%s_1\\Inter\\CropManu_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
	DB.Format("%s_1\\CropManu_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{

		//DB.Format("%s_1\\Inter\\CropManu_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
		DB.Format("%s_1\\CropManu_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d", 0);

			fprintf(db, "%d %d\n", 0, 0);
			fprintf(db, "%d %d %f %d %d %f\n", 0,0, 0.0,0, 0, 0.0);
			fprintf(db, "%f %f %f\n", 0.0, 0.0,0.0);

			fclose(db);
	}
	else fclose(dbq);

	DB.Format("%s_1\\CropPlastic_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		DB.Format("%s_1\\CropPlastic_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d %d", 0, 0);
			fclose(db);
	}
	else
		fclose(dbq);

	//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
	DB.Format("%s_1\\CropFloo_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, m_RotationID,m_YearACycle);
		DB.Format("%s_1\\CropFloo_%d_%d.txt", INTERMANAGE, m_RotationID,m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d %d %d %f %f %s\n", 0, 1, 0, 0.0, 1.0, "None");
			fprintf(db, "%f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			fclose(db);
	}
	else fclose(dbq);

	DB.Format("%s_1\\CropIrri_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		DB.Format("%s_1\\CropIrri_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d %d %f %d", 0, 0, 0.0, 0);
			fclose(db);
	}
	else fclose(dbq);

	//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
	DB.Format("%s_1\\CropGraz_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
			//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
		DB.Format("%s_1\\CropGraz_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d", 0);
			fclose(db);
	}
	else fclose(dbq);

	//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
	DB.Format("%s_1\\GrassCut_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{

			//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, m_RotationID, m_YearACycle);
		DB.Format("%s_1\\GrassCut_%d_%d.txt", INTERMANAGE, m_RotationID, m_YearACycle);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d", 0);
			fclose(db);
	}
	else fclose(dbq);

	if(m_CycleYear > m_RotationYear)
	{
		CString note;
		note.Format("The years in a cycle can not be more than the years this rotation lasts");
		AfxMessageBox(note);
		return;
	}

	CCropPSheet CropSheet;

	if (CropSheet.DoModal()==IDOK) //GetParameter from Page 4 OK
	{
	
	}
		 
}


/*int SitePage3::SetCroPracticeArray()
{
    int rn, i, j;
    rn = IData.Rotation_Number;
    IData.MaxCycle = IData.years;
    
    if (cycle.dim(rn, IData.MaxCycle)==-1) return -1;
    if (Crop.dim(rn, IData.MaxCycle, 1)==-1) return -1;
    if (till.dim(rn, IData.MaxCycle, 1)==-1) return -1;
    if (fer.dim(rn, IData.MaxCycle, 1)==-1) return -1;
    if (manure.dim(rn, IData.MaxCycle, 1)==-1) return -1;
    if (weed.dim(rn, IData.MaxCycle, 1)==-1) return -1;
    if (flood.dim(rn, IData.MaxCycle, 1)==-1) return -1;
    if (irrigation.dim(rn, IData.MaxCycle, 1)==-1) return -1;
	if (grazing.dim(rn, IData.MaxCycle, 1)==-1) return -1;
    
    for (i = 1; i<=rn;i++) {
        for (j = 1; j<= IData.MaxCycle;j++) {
            cycle.get(i, j)->CropNumber  = -1;
            cycle.get(i, j)->TillNumber  = -1;
            cycle.get(i, j)->FerNumber   = -1;
            cycle.get(i, j)->FloodNumber = -1;
            cycle.get(i, j)->ManNumber   = -1;
            cycle.get(i, j)->WeedNumber  = -1;
            cycle.get(i, j)->IrrNumber   = -1;
			cycle.get(i, j)->GrazingNumber = -1;
        }
    }
    IData.MaxCrop  = 1;
    IData.MaxTill  = 1;
    IData.MaxFer   = 1;
    IData.MaxFlood = 1;
    IData.MaxIrr   = 1;
    IData.MaxManure= 1;
    IData.MaxWeed  = 1;
	IData.MaxGrazing = 1;
	return 0;
}*/

int SitePage3::SetCropTable(int TYears)
{
/*	int i,j,k,k0,k1;
	CString txt;

		//Set list control content
	m_CropList.DeleteAllItems();

		//Set list line
	for (i = 1; i<=IData.years;i++) 
	{
		txt.Format("%d yr",i);
		m_CropList.InsertItem(i,txt);
	}

	k=0;k0=1;k1=0;
	for (i=1;i<=db_Rotation_Number;i++) 
	{
		for (j=1;j<=db_RotateSpan[i];j++) 
		{
			txt.Format("%d",i);
			m_CropList.SetItemText(k,1,txt);
			//txt.Format("%d",k0);
			//m_CropList.SetItemText(k,2,txt);
			k++;
			//k0++;
			//if (k0>rotation.get(i)->CycleYear) k0=1; 
		}
		
		for (j=1;j<=db_CycleSpan[i];j++) 
		{
			txt.Format("%d",j);
			m_CropList.SetItemText(k1+j-1,2,txt);

			txt.Format("%d",cycle.get(i,j)->CropNumber);
			m_CropList.SetItemText(k1+j-1,3,txt);
			
			txt.Format("%d",cycle.get(i,j)->TillNumber);
			m_CropList.SetItemText(k1+j-1,4,txt);
			
			txt.Format("%d",cycle.get(i,j)->FerNumber);
			m_CropList.SetItemText(k1+j-1,5,txt);
			
			txt.Format("%d",cycle.get(i,j)->ManNumber);
			m_CropList.SetItemText(k1+j-1,6,txt);
				
			txt.Format("%d",cycle.get(i,j)->WeedNumber);
			m_CropList.SetItemText(k1+j-1,7,txt);
				
			txt.Format("%d",cycle.get(i,j)->FloodNumber);
			m_CropList.SetItemText(k1+j-1,8,txt);
				
			txt.Format("%d",cycle.get(i,j)->IrrNumber);
			m_CropList.SetItemText(k1+j-1,9,txt);
				
			txt.Format("%d",cycle.get(i,j)->GrazingNumber);
			m_CropList.SetItemText(k1+j-1,10,txt);
				
			txt.Format("%d",cycle.get(i,j)->LimeNumber);
			m_CropList.SetItemText(k1+j-1,11,txt);
				
		}
		k1=k1+db_RotateSpan[i];
	}
*/
/*	
	m_CropTable.SetRows(IData.years + 1);
	m_CropTable.SetCols (11);
    char fname[255];
	m_CropTable.SetCol(0);
    for (i = 1; i<=IData.years;i++) {
        m_CropTable.SetRow(i);
        sprintf(fname,"%dth year",i);
		m_CropTable.SetText(fname); 
    }
	m_CropTable.SetRow(0);
		m_CropTable.SetCol(0);
		m_CropTable.SetText("Year"); 
		m_CropTable.SetCol(1);
		m_CropTable.SetText("Rotation"); 
		m_CropTable.SetCol(2);
		m_CropTable.SetText("Cycle Year"); 
		m_CropTable.SetCol(3);
		m_CropTable.SetText("Crop-N"); 
		m_CropTable.SetCol(4);
		m_CropTable.SetText("Tillage-N"); 
		m_CropTable.SetCol(5);
		m_CropTable.SetText("Ferti-N"); 
		m_CropTable.SetCol(6);
		m_CropTable.SetText("Manure-N"); 
		m_CropTable.SetCol(7);
		m_CropTable.SetText("Weed-N"); 
		m_CropTable.SetCol(8);
		m_CropTable.SetText("Flood-N"); 
		m_CropTable.SetCol(9);
		m_CropTable.SetText("Irri-N"); 
		m_CropTable.SetCol(10);
		m_CropTable.SetText("Graz-N"); 

	k=1;k0=1;k1=0;
	for (i=1;i<=IData.Rotation_Number;i++) {
		for (j=1;j<=rotation.get(i)->TotalYear;j++) {
			m_CropTable.SetCol(1);
			m_CropTable.SetRow(k);
			sprintf(fname,"%d",i);
			m_CropTable.SetText(fname);

			m_CropTable.SetCol(2);
			sprintf(fname,"%d",k0);
			m_CropTable.SetText(fname);

			k++;
			k0++;
			if (k0>rotation.get(i)->CycleYear) k0=1; 
		}
		
		for (j=1;j<=rotation.get(i)->CycleYear;j++) {
			m_CropTable.SetRow(k1+j);
			m_CropTable.SetCol(3);
			sprintf(fname,"%d",cycle.get(i,j)->CropNumber);
			m_CropTable.SetText(fname);
			m_CropTable.SetCol(4);
			sprintf(fname,"%d",cycle.get(i,j)->TillNumber);
			m_CropTable.SetText(fname);
			m_CropTable.SetCol(5);
			sprintf(fname,"%d",cycle.get(i,j)->FerNumber);
			m_CropTable.SetText(fname);
			m_CropTable.SetCol(6);
			sprintf(fname,"%d",cycle.get(i,j)->ManNumber);
			m_CropTable.SetText(fname);
			m_CropTable.SetCol(7);
			sprintf(fname,"%d",cycle.get(i,j)->WeedNumber);
			m_CropTable.SetText(fname);
			m_CropTable.SetCol(8);
			sprintf(fname,"%d",cycle.get(i,j)->FloodNumber);
			m_CropTable.SetText(fname);
			m_CropTable.SetCol(9);
			sprintf(fname,"%d",cycle.get(i,j)->IrrNumber);
			m_CropTable.SetText(fname);
			m_CropTable.SetCol(10);
			sprintf(fname,"%d",cycle.get(i,j)->GrazingNumber);
			m_CropTable.SetText(fname);
		}
		k1=k1+rotation.get(i)->TotalYear;
	}
*/
	return 0;
}



/*BOOL SitePage3::CheckRotationYear()
{
	if (!checkRID()) return FALSE;
	if (m_RotationYear<=0) 
	{
		MessageBox("Please input the rotation year at first!","Input warning:",NULL);
		return FALSE;
	}
	int hh=0,j;
    for (j = 1; j<= m_RotationID-1;j++) {
		hh = hh + rotation.get(j)->TotalYear;
	}
	hh+=m_RotationYear;
	if (hh > IData.years || (m_RotationID == IData.Rotation_Number && hh != IData.years)) {
		DMessageBox("The total sum of all rotation years is not equal to simulated year! Please check.", "Input Error:",NULL);
		return FALSE;
	}
	return TRUE;
}

BOOL SitePage3::checkRID()
{
	if (m_RotationN<=0) {
		MessageBox("Please input Rotation number at first!","Input Error:",NULL);
		m_RotationID =0;
		UpdateData(FALSE);
		return FALSE;
	}
	else if (m_RotationID < 1 || m_RotationID > m_RotationN) {
		MessageBox("Rotation ID should be 1<=ID<=Total rotation number!", "Input Error:",NULL);
		m_RotationID = 1;
		UpdateData(FALSE);
        return FALSE;
	}
	int j;
	if ( m_RotationID > 1) {
		j = m_RotationID - 1;
		if (j>0) {
			if (rotation.get(j)->TotalYear <= 0 || rotation.get(j)->CycleYear <= 0 ) {
				DMessageBox("The former rotation isn't inputed! Please input firstly the former rotation.", "Input Error:",NULL);
				m_RotationID = j;
				UpdateData(FALSE);
				return FALSE;
			}
		}
	}
	return TRUE;
}



//Set rotation column in the rotation table
//rnum: rotation number,     rlength: length of a rotation
void SitePage3::SetRotation(int rnum, int rlength)
{
    int i, rb, re;
    if (rnum == 1) 
	{
        rb = 1;
		re = rlength;
	}
    else if (rnum > 1) 
	{
        rb = 1;
        for (i = 1; i<=rnum - 1;i++) {
            rb = rb + rotation.get(i)->TotalYear;
        }
        re = rb + rlength - 1;
    }


	//Set data to the below list after to input the ratation length
    //m_CropTable.SetCol(1);
	char ch[40];
    for (i = rb; i<=re; i++) 
	{
		//m_CropTable.SetRow(i);
		sprintf(ch,"%d",rnum);
		//m_CropTable.SetText(ch);

		m_CropList.SetItemText(i-1,1,ch);
	}
}

//Set cycle column in the rotation table
//rnum: rotation number,     cl: length of a cycle
void SitePage3::SetCycle(int rnum, int rlength, int cl)
{
    int i, rb, re, j;
    if (rnum == 1) {
        rb = 1; re = rlength;
	}
	else if (rnum > 1) { 
        rb = 1;
        for (i = 1;i<=rnum - 1;i++) {
            rb = rb + rotation.get(i)->TotalYear;//i<-rnum-1
        }
        re = rb + rlength - 1;
    }


	//m_CropTable.SetCol(2);
    j = 1;
	char ch[40];
	//int rn;
    for (i = rb;i<=re;i++) {
		//rn=m_CropTable.GetRows();
		//if (i>rn-1) break;
        //m_CropTable.SetRow(i);
		sprintf(ch,"%d",j);
		//m_CropTable.SetText(ch);

		m_CropList.SetItemText(i-1,2,ch);

        j++;
        if (j > cl) j = 1;
	} 
}

BOOL SitePage3::CheckCycleYear()
{
	if (!CheckRotationYear()) return FALSE;
	if (m_CycleYear < 0 || m_CycleYear > m_RotationYear) {
		DMessageBox("The length of the cycle is wrong! Please correct.", "Input Error:",NULL);
		m_CycleYear=0;
		UpdateData(FALSE);
		return FALSE;
	}
	return TRUE;
}
*/
void SitePage3::OnKillfocusCycleYear() 
{
	UpdateData(TRUE);

	m_RotationCycles = (float)m_RotationYear / (float)m_CycleYear;

	UpdateData(FALSE);

	Make0Files();
}

/*BOOL SitePage3::CheckYearACycle()
{
	if (!CheckCycleYear()) return FALSE;

	if (m_YearACycle<1) {// || m_RotationID<1) {rotation or no 
		DMessageBox("No cycle data! Please input these data.", "Input Error:",NULL);
        return FALSE;
	}
	if (m_YearACycle < 1 || m_YearACycle > m_CycleYear) {
		DMessageBox("The year in a cycle should be less than the cycle length! Please correct.", "Input Error:",NULL);
		m_YearACycle = 1;
		UpdateData(FALSE);
		return FALSE;
	}
	return TRUE;
}
*/


void SitePage3::OnLastRotation() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString DB;
	FILE *db;

	DB.Format("%s_1\\CropRotation.txt", INTERMANAGE);//###
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(db, "%d", m_RotationN);
	fclose(db);

	if (m_RotationID>1) m_RotationID--;


	int db_RotationID[40], db_RotateSpan[40], db_CycleSpan[40];
	
	for(int rrr=1; rrr<=m_RotationN; rrr++)
	{
		DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, rrr);//read: OnLastRotation()
		db=fopen(DB, "r");
		if(db==NULL)
		{
			CString note;
			note.Format("Can not open file %s", DB);
			AfxMessageBox(note);
			exit(0);
		}
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);
	}
	
	m_RotationYear=db_RotateSpan[m_RotationID];
	m_CycleYear=db_CycleSpan[m_RotationID];
	m_RotationCycles = (float)m_RotationYear / (float)m_CycleYear;
	
	UpdateData(FALSE); 
	//DrawYearScale();
}

void SitePage3::OnLastRotation2() 
{
	UpdateData(TRUE);
	
	if (m_CycleYear==0) return;

	if (m_YearACycle>1) m_YearACycle--;

	demo();//!!

	UpdateData(FALSE);

	//DrawYearMark();
}

void SitePage3::OnNextRotation() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString DB;
	FILE *db;

	DB.Format("%s_1\\CropRotation.txt", INTERMANAGE);//###
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(db, "%d", m_RotationN);
	fclose(db);

	if (m_RotationID<m_RotationN) m_RotationID++;

	int db_RotationID[40], db_RotateSpan[40], db_CycleSpan[40];
	
	for(int rrr=1; rrr<=m_RotationN; rrr++)
		{
			DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, rrr);//read: OnNextRotation()
			db=fopen(DB, "r");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not open file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
			fclose(db);

		}
	
	m_RotationYear=db_RotateSpan[m_RotationID];
	m_CycleYear=db_CycleSpan[m_RotationID];
	m_RotationCycles = (float)m_RotationYear / (float)m_CycleYear;

	UpdateData(FALSE);

	//DrawYearScale();

}

void SitePage3::OnNextRotation2() 
{
	UpdateData(TRUE);
	
	if (m_YearACycle<m_CycleYear) m_YearACycle++;
	
	demo();//!!

	UpdateData(FALSE);

	//DrawYearMark();
}

/*void SitePage3::OnTCropAccept() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_RotationN<=0) {
		DMessageBox("No Number of Rotation error!","Loss Data Error",NULL);
		return;
	}
	int j,k1;
	for (j = 1;j <= IData.Rotation_Number;j++) {
		if (rotation.get(j)->CycleYear<=0) {
			DMessageBox("No Cycle's year data error!","Loss Data Error",NULL);
			return;
		}
		for (k1 = 1; k1<=rotation.get(j)->CycleYear;k1++) {
			if (cycle.get(j,k1)->CropNumber<0) {
				DMessageBox("No Crop data error!","Loss Data Error",NULL);
				return;
			}
			if (cycle.get(j,k1)->FerNumber<0) {
				DMessageBox("No Fertilization data error!","Loss Data Error",NULL);
				return;
			}
			if (cycle.get(j,k1)->ManNumber<0) {
				DMessageBox("No Manure data error!","Loss Data Error",NULL);
				return;
			}
			if (cycle.get(j,k1)->FloodNumber<0) {
				DMessageBox("No Flood data error!","Loss Data Error",NULL);
				return;
			}
			if (cycle.get(j,k1)->IrrNumber<0) {
				DMessageBox("No Irrigation data error!","Loss Data Error",NULL);
				return;
			}
			if (cycle.get(j,k1)->TillNumber<0) {
				DMessageBox("No Tillage data error!","Loss Data Error",NULL);
				return;
			}
			if (cycle.get(j,k1)->WeedNumber<0) {
				DMessageBox("No Weeding data error!","Loss Data Error",NULL);
				return;
			}
		}
	}

}*/

BEGIN_EVENTSINK_MAP(SitePage3, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage3)
	//ON_EVENT(SitePage3, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*void SitePage3::OnClickMsflexgrid1() 
{
	// TODO: Add your control notification handler code here
	/*
    int i, i1, j, k, n, k1, nu;
    i = m_CropTable.GetRow();
    i1 = m_CropTable.GetCol();
    if (i > 0) {
        n = 0;
        for (j = 1;j <= IData.Rotation_Number;j++) {
            for (k = 1; k<=rotation.get(j)->TotalYear;k++) {
                n = n + 1;
                if (n == i) {
                    if (j > 1) {
                        for (k1 = j - 1; k1>=1;k1--) {
                            n = n - rotation.get(k1)->TotalYear;
                        }
                    }
					m_RotationID=j;
					m_RotationYear = rotation.get(j)->TotalYear;
					m_CycleYear = rotation.get(j)->CycleYear;

                    nu = 0;
                    for (k1 = 1; k1<=rotation.get(j)->TotalYear;k1++) {
                        nu = nu + 1;
                        if (nu == n) break;
                        if (nu == rotation.get(j)->CycleYear) {
                            nu = 0;
                            n = n - rotation.get(j)->CycleYear;
                        }
                    }
					m_YearACycle=n;
					m_CropTable.SetRow(i); 
					m_CropTable.SetCol(i1); 
					UpdateData(FALSE);
                    return;
                } 
            }
        }
    }*
	UpdateData(FALSE);
}
*/




/*void SitePage3::ReturnInftoMainMenu()
{
	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

    int row, num, n, i;
	char ch[40];
    row = 0;
	n = rrr - 1;
    for (i = 1;i<=n;i++) {
        row += rotation.get(i)->TotalYear;
    }
    row = row + yyy;

	//m_CropTable.SetRow(row);
	row--;

		//crop number
    //m_CropTable.SetCol(3);
	num=cycle.get(rrr, yyy)->CropNumber;
	if (num==-1) {
		MessageBox("No Crop data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,3,ch);

    //m_CropTable.SetCol(4);
	num=cycle.get(rrr, yyy)->TillNumber;
	if (num==-1) {
		MessageBox("No Tillage data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,4,ch);

    //m_CropTable.SetCol(5);
	num=cycle.get(rrr, yyy)->FerNumber;
	if (num==-1) {
		MessageBox("No Fertilization data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,5,ch);

    //m_CropTable.SetCol(6);
	num=cycle.get(rrr, yyy)->ManNumber;
	if (num==-1) {
		MessageBox("No Manure data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,6,ch);
    
	//m_CropTable.SetCol(7);
	num=cycle.get(rrr, yyy)->WeedNumber;
	if (num==-1) {
		MessageBox("No Weed data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,7,ch);

    //m_CropTable.SetCol(8);
	num=cycle.get(rrr, yyy)->FloodNumber;
	if (num==-1) {
		MessageBox("No Flood data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,8,ch);
    
	//m_CropTable.SetCol(9);
	num=cycle.get(rrr, yyy)->IrrNumber;
	if (num==-1) {
		MessageBox("No Irrigation data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,9,ch);

	//m_CropTable.SetCol(10);
	num=cycle.get(rrr, yyy)->GrazingNumber;
	if (num==-1) {
		MessageBox("No Grazing data!","Input Error:",NULL);
		return;
	}
	sprintf(ch,"%d",num);
    //m_CropTable.SetText(ch);
	m_CropList.SetItemText(row,10,ch);

	db=fopen(DB, "w");
	fprintf(db, "%d %d", rrr, yyy);
	fclose(db);
	
	return;
}*/

//#include "SitePage12.h"
/*void SitePage3::OnPlantType() 
{
	UpdateData(TRUE);

	int rrr, yyy;
	CString DB;
	FILE *db;
	DB.Format("%s\\Inter\\CR.txt");
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	if (m_PlantType<0) return;

	RotationParameter *Pnt;
	Pnt = rotation.get(rrr);
	Pnt->PlantType = m_PlantType;//0=crop, 1=forest
	if (m_PlantType==1) //forest
	{
		//m_CycleYear  = 1;
		//m_YearACycle = 1;
		//UpdateData(FALSE);
		GetDlgItem(IDC_YearACycle)->EnableWindow(FALSE);
		GetDlgItem(IDC_CycleYear)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_YearACycle)->EnableWindow(TRUE);
		GetDlgItem(IDC_CycleYear)->EnableWindow(TRUE);
	}



}*/


//Set m_RotationID after click a item on the below List
/*void SitePage3::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int i, j, k, n, k1, nu;
    i = m_CropList.GetSelectionMark()+1;

    if (i > 0)
	{
        n = 0;
        for (j = 1;j <= IData.Rotation_Number;j++) 
		{
            for (k = 1; k<=rotation.get(j)->TotalYear;k++) 
			{
                n = n + 1;
                if (n == i) 
				{
                    if (j > 1) //get the order number of the year in this rotation
					{
                        for (k1 = j - 1; k1>=1;k1--) 
						{
                            n = n - rotation.get(k1)->TotalYear;
                        }
                    }
					m_RotationID = j;
					m_RotationYear = rotation.get(j)->TotalYear;
					m_CycleYear = rotation.get(j)->CycleYear;

					//get the year order in a cycle
                    nu = 0;
                    for (k1 = 1; k1<=rotation.get(j)->TotalYear;k1++) 
					{
                        nu = nu + 1;
                        if (nu == n) break;
                        if (nu == rotation.get(j)->CycleYear) 
						{
                            nu = 0;
                            n = n - rotation.get(j)->CycleYear;
                        }
                    }
					m_YearACycle = n;

					UpdateData(FALSE);
                    return;
                } 
            }
        }
    }
	UpdateData(FALSE);	


	*pResult = 0;
}*/

BOOL SitePage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
		//Set list column
	int i;
	char *title[]={"RotationID","Years","Cycles", "Yrs in a cycle","Year #"};
	int  ItemNum=5;
	for (i=0;i<ItemNum;i++)
	{
		m_CropList.InsertColumn(i,title[i],LVCFMT_CENTER,100,-1);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SitePage3::OnKillfocusRotationYear() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_RotationYear > m_ShowTYear)
	{
		CString note;
		note.Format("Years of this rotation system should be less than the total simulated years");
		AfxMessageBox(note);
		return;
	}

	Make0Files();
	
}

void SitePage3::demo() 
{
	CString txt;
	m_CropList.DeleteAllItems();


	//if (m_RotationN >= 0) 
	{
		for (int i = 1; i<=1;i++) 
		{
			txt.Format("%d", m_RotationID);// = OrderNumber(m_RotationID,"",&txt);
			m_CropList.InsertItem(i,txt);
		
			txt.Format("%d",m_RotationYear);
			m_CropList.SetItemText(i-1,1,txt);

			txt.Format("%.1f",m_RotationCycles);
			m_CropList.SetItemText(i-1,2,txt);

			txt.Format("%d",m_CycleYear);
			m_CropList.SetItemText(i-1,3,txt);

			txt.Format("%d",m_YearACycle);
			m_CropList.SetItemText(i-1,4,txt);
		
					
		}
	}
}

void SitePage3::OnKillfocusRotationN() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    if (m_RotationN<= 0 || m_RotationN> IData.years) 
	{
		CString note;
		note.Format("Total number of rotation systems is not correct");
		AfxMessageBox(note);
		return;
	}

	m_System.ResetContent();
	for (int i=0;i<m_RotationN;i++)
	{
		char fname[40];
		sprintf(fname,"System %d",i+1);
		m_System.AddString(fname);
	}

	UpdateData(FALSE);
}

void SitePage3::Make0Files(void)
{
	UpdateData(TRUE);

	CString DB;
	FILE *db;

	if(m_CycleYear > m_RotationYear)
	{
		CString note;
		note.Format("The years in a cycle can not be more than the years this rotation lasts");
		AfxMessageBox(note);
		return;
	}

	DB.Format("%s\\Inter\\OpenFile.txt", OUTPUT);
	db=fopen(DB, "r");
	fscanf(db, "%d", &OpenFile);
	fclose(db);

	if(OpenFile==0)
	{
		//for(int k=1; k<=m_RotationN; k++)
		{
			
			DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, m_RotationID);//write: Make0Files(void), OK
			db=fopen(DB, "w");
			fprintf(db, "%d %d %d", m_RotationID, 1, 1);
			fclose(db);
		}

		for(int i=1; i<=m_CycleYear; i++)
		{
			//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, m_RotationID, i);
			DB.Format("%s_1\\CropRotation_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d\n", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropTill_%d_%d.txt", OUTPUT, m_RotationID, i);
			DB.Format("%s_1\\CropTill_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, m_RotationID, i);
			DB.Format("%s_1\\CropFert_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropManu_%d_%d.txt", OUTPUT, m_RotationID, i);
			DB.Format("%s_1\\CropManu_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fprintf(db, "%d %d\n", 0, 0);
			fprintf(db, "%d %d %f %d %d %f\n", 0,0, 0.0,0, 0, 0.0);
			fprintf(db, "%f %f %f\n", 0.0, 0.0,0.0);
			fclose(db);

			DB.Format("%s_1\\CropPlastic_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d %d", 0, 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, m_RotationID, i);
			DB.Format("%s_1\\CropFloo_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d %d %d %f %f %s", 0, 1, 0, 0.0, 1.0, "None");
			fprintf(db, "%f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			fclose(db);

			DB.Format("%s_1\\CropIrri_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d %d %f %d", 0, 0, 0.0, 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, m_RotationID, i);
			DB.Format("%s_1\\CropGraz_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, m_RotationID, i);
			DB.Format("%s_1\\GrassCut_%d_%d.txt", INTERMANAGE, m_RotationID, i);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);
		}
	}
	else
	{
		//for(int k=1; k<=m_RotationN; k++)
		{
			
			DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, m_RotationID);//write: Make0Files(void), OK
			db=fopen(DB, "w");
			fprintf(db, "%d %d %d", m_RotationID, 1, 1);
			fclose(db);
		}

		//for(int i=1; i<=m_CycleYear; i++)
		{
			//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, m_RotationID, m_CycleYear);
			DB.Format("%s_1\\CropRotation_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			if(db==NULL)
			{
				CString note;
				note.Format("Can not create file %s", DB);
				AfxMessageBox(note);
				exit(0);
			}
			fprintf(db, "%d\n", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropTill_%d_%d.txt", OUTPUT, m_RotationID, m_CycleYear);
			DB.Format("%s_1\\CropTill_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, m_RotationID, m_CycleYear);
			DB.Format("%s_1\\CropFert_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropManu_%d_%d.txt", OUTPUT, m_RotationID, m_CycleYear);
			DB.Format("%s_1\\CropManu_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fprintf(db, "%d %d\n", 0, 0);
			fprintf(db, "%d %d %f %d %d %f\n", 0,0, 0.0,0, 0, 0.0);
			fprintf(db, "%f %f %f\n", 0.0, 0.0,0.0);
			fclose(db);

			DB.Format("%s_1\\CropPlastic_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d %d", 0, 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, m_RotationID, m_CycleYear);
			DB.Format("%s_1\\CropFloo_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d %d %d %f %f %s", 0, 1, 0, 0.0, 1.0, "None");
			fprintf(db, "%f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			fclose(db);

			DB.Format("%s_1\\CropIrri_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d %d %f %d", 0, 0, 0.0, 0);
			fclose(db);

			//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, m_RotationID, m_CycleYear);
			DB.Format("%s_1\\CropGraz_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);

			//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, m_RotationID, m_CycleYear);
			DB.Format("%s_1\\GrassCut_%d_%d.txt", INTERMANAGE, m_RotationID, m_CycleYear);
			db=fopen(DB, "w");
			fprintf(db, "%d", 0);
			fclose(db);
		}
	}
}

/*void SitePage3::OnUpdateRotationCycles() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_RotationCycles = m_RotationYear / m_CycleYear;

	UpdateData(FALSE);
	
}*/

void SitePage3::OnSetfocusRotationCycles() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_RotationCycles = m_RotationYear / m_CycleYear;

	UpdateData(FALSE);
	
}

void SitePage3::OnKillfocusSystem() 
{
	// TODO: Add your control notification handler code here
	
}

void SitePage3::OnSelchangeSystem() 
{
	// TODO: Add your control notification handler code here
	System = m_System.GetCurSel()+1;

	AccuYears = 0;
	for(int i=1; i<=System-1; i++)
		AccuYears += SystemYears[i];

	if(System==m_RotationN) 
	{
		SystemYears[m_RotationN] = m_ShowTYear - AccuYears;
		m_SystemYears = SystemYears[m_RotationN];
		UpdateData(FALSE);
	}
}

void SitePage3::OnKillfocusSystemYears() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SystemYears[System] = m_SystemYears;

	
}

void SitePage3::OnKillfocusOneCycleYears() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SystemCycleYears[System] = m_SystemCycleYears;
}


void SitePage3::OnViewRotation() 
{
	// TODO: Add your control notification handler code here
	ReadRotationCrops();

	DrawYearScale();

	DrawCycleCrops();
}


/*
void SitePage3::color(int year)
{
	int cy=0, tt=1, YEAR=0, RY=0, k, i, j;
	
	for(i=0; i<50; i++)
	{
		for(j=0; j<10; j++)
		{
			RR[j][i]=0; 
			GG[j][i]=0;
			BB[j][i]=255;
		}
	}
	
	for(k=1; k<=m_RotationN; k++)
	{
		for(int cc=1; cc<=db_CycleSpan[k]; cc++)
		{				
			RR[k][cc]+=k*cc*50; GG[k][cc]+=k*cc*10; BB[k][cc]-=cc*20;

			if(RR[k][cc]>255) RR[k][cc]=50; 
			if(GG[k][cc]>255) GG[k][cc]=30;
			if(BB[k][cc]>255) BB[k][cc]=20;

			if(RR[k][cc]<0) RR[k][cc]=150; 
			if(GG[k][cc]<0) GG[k][cc]=130;
			if(BB[k][cc]<0) BB[k][cc]=220;
		}

	}

}
*/
void SitePage3::DrawYearScale()
{
	UpdateData(TRUE);

	CFont hNewFont;
	TEXTMETRIC tm;
	//CString dndc;

	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));	

	pDC.SetViewportOrg (50, 150); 
	pDC.SetViewportExt(1400, 1400);

	pDC.SetBkMode(TRANSPARENT);	

	pDC.FillSolidRect(0, 200, 600, 700, RGB(200,200,200));

	int x1, y1, x2, y2, yr, yy, k;
	int j=12;
	CString w;
	int cy=0, tt=1;
	int Rr;
	int Gg;
	int Bb;
	int TY=0;

	if(TotalYears<=10) j=48;

	//color(0);
	
	for(k=1; k<=TotalYears; k++)
	{
		TY++;
				if(TY<=50) yy=1;
				else if(TY>50&&TY<=100) yy=2;
				else if(TY>100&&TY<=150) yy=3;
				else if(TY>150&&TY<=200) yy=4;
				else if(TY>200&&TY<=250) yy=5;
				else {}

				int TTY;
				TTY=TY;
				
check1:
				if(TTY>50) 
				{
					TTY-=50;
					goto check1;
				}
				else
				{}


				x1=(TTY-1)*j;
				x2=j-1;
				y1=yy*100+150;
				y2=60;

				Rr = 250;
				Gg = 250;
				Bb = 250;
				pDC.FillSolidRect(x1, y1, x2, y2, RGB(Rr,Gg,Bb));
				

				//////////////////////
				yr = k;
				w.Format("%d", yr);

				hNewFont.CreateFont(25,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

				pDC.SelectObject(&hNewFont);
				pDC.SetTextColor(RGB(0,0,5));
				pDC.SetBkColor(TRANSPARENT);
				pDC.GetTextMetrics(&tm);
				pDC.SetTextAlign(TA_LEFT);

				if(k<=10)
					pDC.TextOut(x1+5, y1+60, w);
				else
				{
					if(k%2==1)
					pDC.TextOut(x1, y1+60, w);
				}
		
				hNewFont.DeleteObject();

				
				
	}

}

void SitePage3::DrawCycleCrops()
{
	UpdateData(TRUE);

	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));	

	pDC.SetViewportOrg (50, 150); 
	pDC.SetViewportExt(1400, 1400);

	pDC.SetBkMode(TRANSPARENT);	


	int rrr, yyy, ccc;
	int x1, y1, x2, y2, yy;
	int j=12;
	CString w;
	int cy=0, tt=1;
	int Rr;
	int Gg;
	int Bb;
	int year=0, TY=0, dGT;

	if(TotalYears<=10) j=48;
	
	for(rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		year=0;
		for(;;)
		{
			for(yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
			{
				year++;
				TY++;
				if(TY<=50) yy=1;
				else if(TY>50&&TY<=100) yy=2;
				else if(TY>100&&TY<=150) yy=3;
				else if(TY>150&&TY<=200) yy=4;
				else if(TY>200&&TY<=250) yy=5;
				else {}

				int TTY;
				TTY=TY;
				
check1:
				if(TTY>50) 
				{
					TTY-=50;
					goto check1;
				}
				else
				{}


				x1=(TTY-1)*j;
				x2=j-1;
				y1=yy*100 + 150;
				y2=60;

				for(ccc=1; ccc<=db_YrCrops[rrr][yyy]; ccc++)
				{
					Rr = RR[db_YrCropType[rrr][yyy][ccc]];
					Gg = GG[db_YrCropType[rrr][yyy][ccc]];
					Bb = BB[db_YrCropType[rrr][yyy][ccc]];
						

					int PT=0;//(int)db_PMonth[rrr][yyy][ccc];
					int HT=(int)db_HMonth[rrr][yyy][ccc];

					if(HT<PT) dGT=12-PT+HT;
					else dGT=HT-PT;
						
					pDC.FillSolidRect(x1+PT*3, y1, dGT*1, y2, RGB(Rr,Gg,Bb));

				/*	if(db_YrCrops[rrr][yyy]==1)
					{
						Rr = RR[db_YrCropType[rrr][yyy][ccc]];
						Gg = GG[db_YrCropType[rrr][yyy][ccc]];
						Bb = BB[db_YrCropType[rrr][yyy][ccc]];
						pDC.FillSolidRect(x1, y1, x2, y2, RGB(Rr,Gg,Bb));
					}
					else if(db_YrCrops[rrr][yyy]==2)
					{
						Rr = RR[db_YrCropType[rrr][yyy][ccc]];
						Gg = GG[db_YrCropType[rrr][yyy][ccc]];
						Bb = BB[db_YrCropType[rrr][yyy][ccc]];
						int dx=(int)x2*0.5;
						if(ccc==1) pDC.FillSolidRect(x1, y1, dx, y2, RGB(Rr,Gg,Bb));
						else pDC.FillSolidRect(x1+dx, y1, x2, y2, RGB(Rr,Gg,Bb));
					}
					else if(db_YrCrops[rrr][yyy]==3)
					{
						Rr = RR[db_YrCropType[rrr][yyy][ccc]];
						Gg = GG[db_YrCropType[rrr][yyy][ccc]];
						Bb = BB[db_YrCropType[rrr][yyy][ccc]];
						int dx=(int)x2*0.3;
						if(ccc==1) pDC.FillSolidRect(x1, y1, dx, y2, RGB(Rr,Gg,Bb));
						else if(ccc==2) pDC.FillSolidRect(x1+dx, y1, x1+2*dx, y2, RGB(Rr,Gg,Bb));
						else pDC.FillSolidRect(x1+2*dx, y1, x2, y2, RGB(Rr,Gg,Bb));
					}*/
				}

				pDC.FillSolidRect(x1-1, y1, 1, 80, RGB(0,0,0));
				/*{
					yr = (i);
					w.Format("%d", yr);
					pDC.TextOut(x1+10, y1+60, w);
				}*/

				if(year==db_RotateSpan[rrr]) goto NewRotation;
			}
		}
		NewRotation:;
	}

	CFont hNewFont;
	TEXTMETRIC tm;

	hNewFont.CreateFont(30,0,0,0,FW_NORMAL,0,0,0,
			                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_DONTCARE,"Courie New");

	pDC.SelectObject(&hNewFont);
	pDC.SetTextColor(RGB(0,0,5));
	pDC.SetBkColor(TRANSPARENT);
	pDC.GetTextMetrics(&tm);
	pDC.SetTextAlign(TA_LEFT);

	int XX1=650;
	int YY1=50;
	for(int ww=1; ww<=60; ww++)
	{
		if(CrCo[ww]>=0)
		{
			Rr = RR[CrCo[ww]];
			Gg = GG[CrCo[ww]];
			Bb = BB[CrCo[ww]];
			pDC.FillSolidRect(XX1, YY1*ww+150, 20, 30, RGB(Rr,Gg,Bb));

			dndc74 zzz;
			w.Format("%s", zzz.CropSystem[CrCo[ww]]);
			pDC.TextOut(XX1+30, YY1*ww+150, w);
		}
		else
			break;

	}

	hNewFont.DeleteObject();

}

void SitePage3::ReadRotationCrops()
{
	int rrr, yyy;
	float jf;

	for(int v=1; v<=60; v++) CrCo[v]=-1;
	TotalYears=0;

    CString DB;
	FILE *db;

	DB.Format("%s_1\\CropRotation.txt", INTERMANAGE);
	db=fopen(DB, "r");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not open file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(db, "%d", &db_Rotation_Number);
	fclose(db);

	int CC=0, kk=1;

	for(rrr=1; rrr<=db_Rotation_Number; rrr++)
	{
		
		DB.Format("%s_1\\CropRotation_%d.txt", INTERMANAGE, rrr);//read: ReadRotationCrops()
		db=fopen(DB, "r");
		fscanf(db, "%d %d %d", &db_RotationID[rrr], &db_RotateSpan[rrr], &db_CycleSpan[rrr]);
		fclose(db);

		TotalYears += db_RotateSpan[rrr];

		for(yyy=1; yyy<=db_CycleSpan[rrr]; yyy++)
		{
			//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, rrr, yyy);
			DB.Format("%s_1\\CropRotation_%d_%d.txt", INTERMANAGE, rrr, yyy);
			db=fopen(DB, "r");
			fscanf(db, "%d", &db_YrCrops[rrr][yyy]);

			for(int ccc=1; ccc<=db_YrCrops[rrr][yyy]; ccc++)
			{
				fscanf(db, "%d %d", &db_YrCropOrder[rrr][yyy][ccc], &db_YrCropType[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_PMonth[rrr][yyy][ccc], &db_PDay[rrr][yyy][ccc]);
				fscanf(db, "%d %d", &db_HMonth[rrr][yyy][ccc], &db_HDay[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_HYr[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f", &jf);
				fscanf(db, "%d", &db_CoverCrop[rrr][yyy][ccc]);
				fscanf(db, "%d", &db_PerennialCrop[rrr][yyy][ccc]);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f %f", &jf, &jf);
				fscanf(db, "%f", &jf);
				
				CC++;
				CropColor[CC]=db_YrCropType[rrr][yyy][ccc];

				if(CC==1) CrCo[1]=CropColor[CC];
				else
				{
					int check=0;
					for(int w=1; w<=CC; w++)
					{						
						if(CropColor[CC]==CrCo[w]) check++;
					}

					if(check==0)
					{
						kk++;
						CrCo[kk]=CropColor[CC];
					}
				}
			}
			
			fclose(db);
		}

	}
}

void SitePage3::DrawYearMark()
{
	UpdateData(TRUE);

	CClientDC pDC(this);
	
	pDC.SetMapMode(MM_ANISOTROPIC);
	pDC.SetWindowExt(1500, 3000);

	CPen *pOldPen = NULL;	
	CPen  Pen0(PS_SOLID, 3, RGB(100,100,100));
	pOldPen = pDC.SelectObject(&Pen0);

	pDC.SetBkMode(TRANSPARENT);
	pDC.SetTextAlign(TA_RIGHT);
	pDC.SetTextColor(RGB(0,0,0));	

	pDC.SetViewportOrg (50, 150); 
	pDC.SetViewportExt(1400, 1400);

	pDC.SetBkMode(TRANSPARENT);	

	pDC.FillSolidRect(0, 80, 600, 20, RGB(200,200,200));
	pDC.FillSolidRect(0, 180, 600, 20, RGB(200,200,200));
	pDC.FillSolidRect(0, 280, 600, 20, RGB(200,200,200));
	pDC.FillSolidRect(0, 380, 600, 20, RGB(200,200,200));
	pDC.FillSolidRect(0, 480, 600, 20, RGB(200,200,200));

	int i;
	int j=12;
	CString w;
	int cy=0, tt=1;
	int TY=0;

	if(TotalYears<=10) j=48;

	CString mark;
	mark.Format("*");
	int year=0;
	
	for(i=1; i<=m_RotationID-1; i++)
	{
		year += db_RotateSpan[i];
	}
	
	year += m_YearACycle; 

	int TTY=year;
	check2:
	if(TTY>50) 
	{
		TTY-=50;
		goto check2;
	}
	else
	{}

	int YY=(int)(year/50);

	pDC.TextOut((TTY-1)*j+7, YY*100+80, mark);
}
	

void SitePage3::OnManureFarmSoil() 
{
	// TODO: Add your control notification handler code here
	CForestPSheet ww;
	if (ww.DoModal()==IDOK) //GetParameter from Page 4 OK
	{
		//AfxMessageBox("!?!");	
	}
	
}
