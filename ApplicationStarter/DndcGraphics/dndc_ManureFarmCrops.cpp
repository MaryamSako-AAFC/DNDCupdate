// dndc_ManureFarmCrops.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "dndc_ManureFarmCrops.h"
#include "RunPaths.h"
#include "SitePara.h"
#include "SitePage2.h"
#include "SitePage3.h"
#include "SitePSheet.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Site_BaseInformation	IData;
CString FCT;

float ManureFraction1[11]={0.0,0.0}, ManureFraction2[11]={0.0,0.0}, ManureFraction3[11]={0.0,0.0}, ManureFraction4[11]={0.0,0.0};
float ManureFraction5[11]={0.0,0.0}, ManureFraction6[11]={0.0,0.0}, ManureFraction7[11]={0.0,0.0}, ManureFraction8[11]={0.0,0.0};
float ManureFraction9[11]={0.0,0.0}, ManureFraction10[11]={0.0,0.0};
int FarmField=0, jdd;
float CropArea[11]={0.0,0.0};

CString DB;
FILE *db, *dbq;	
/////////////////////////////////////////////////////////////////////////////
// dndc_ManureFarmCrops property page

IMPLEMENT_DYNCREATE(dndc_ManureFarmCrops, CPropertyPage)

dndc_ManureFarmCrops::dndc_ManureFarmCrops() : CPropertyPage(dndc_ManureFarmCrops::IDD)
{
	//{{AFX_DATA_INIT(dndc_ManureFarmCrops)
	m_TotalHa = 0.0f;
	m_CropType1 = -1;
	m_CropType10 = -1;
	m_CropType2 = -1;
	m_CropType3 = -1;
	m_CropType4 = -1;
	m_CropType5 = -1;
	m_CropType6 = -1;
	m_CropType7 = -1;
	m_CropType8 = -1;
	m_CropType9 = -1;
	m_land1 = 0.0f;
	m_land10 = 0.0f;
	m_land2 = 0.0f;
	m_land3 = 0.0f;
	m_land4 = 0.0f;
	m_land5 = 0.0f;
	m_land6 = 0.0f;
	m_land7 = 0.0f;
	m_land8 = 0.0f;
	m_land9 = 0.0f;
	m_manure1 = 0.0f;
	m_manure10 = 0.0f;
	m_manure2 = 0.0f;
	m_manure3 = 0.0f;
	m_manure4 = 0.0f;
	m_manure5 = 0.0f;
	m_manure6 = 0.0f;
	m_manure7 = 0.0f;
	m_manure8 = 0.0f;
	m_manure9 = 0.0f;
	m_CropSelect = -1;
	m_unit = -1;
	m_FarmYears = 0;
	m_FarmYear = 1;
	m_TotalFields = 0;
	m_SumHa = 0.0f;
	m_SumManure = 0.0f;
	//}}AFX_DATA_INIT
}

dndc_ManureFarmCrops::~dndc_ManureFarmCrops()
{
}

void dndc_ManureFarmCrops::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dndc_ManureFarmCrops)
	DDX_Text(pDX, IDC_TotalHa, m_TotalHa);
	DDX_CBIndex(pDX, IDC_CropType1, m_CropType1);
	DDX_CBIndex(pDX, IDC_CropType10, m_CropType10);
	DDX_CBIndex(pDX, IDC_CropType2, m_CropType2);
	DDX_CBIndex(pDX, IDC_CropType3, m_CropType3);
	DDX_CBIndex(pDX, IDC_CropType4, m_CropType4);
	DDX_CBIndex(pDX, IDC_CropType5, m_CropType5);
	DDX_CBIndex(pDX, IDC_CropType6, m_CropType6);
	DDX_CBIndex(pDX, IDC_CropType7, m_CropType7);
	DDX_CBIndex(pDX, IDC_CropType8, m_CropType8);
	DDX_CBIndex(pDX, IDC_CropType9, m_CropType9);
	DDX_Text(pDX, IDC_LandArea1, m_land1);
	DDX_Text(pDX, IDC_LandArea10, m_land10);
	DDX_Text(pDX, IDC_LandArea2, m_land2);
	DDX_Text(pDX, IDC_LandArea3, m_land3);
	DDX_Text(pDX, IDC_LandArea4, m_land4);
	DDX_Text(pDX, IDC_LandArea5, m_land5);
	DDX_Text(pDX, IDC_LandArea6, m_land6);
	DDX_Text(pDX, IDC_LandArea7, m_land7);
	DDX_Text(pDX, IDC_LandArea8, m_land8);
	DDX_Text(pDX, IDC_LandArea9, m_land9);
	DDX_Text(pDX, IDC_manure1, m_manure1);
	DDX_Text(pDX, IDC_manure10, m_manure10);
	DDX_Text(pDX, IDC_manure2, m_manure2);
	DDX_Text(pDX, IDC_manure3, m_manure3);
	DDX_Text(pDX, IDC_manure4, m_manure4);
	DDX_Text(pDX, IDC_manure5, m_manure5);
	DDX_Text(pDX, IDC_manure6, m_manure6);
	DDX_Text(pDX, IDC_manure7, m_manure7);
	DDX_Text(pDX, IDC_manure8, m_manure8);
	DDX_Text(pDX, IDC_manure9, m_manure9);
	DDX_Radio(pDX, IDC_CropSelect, m_CropSelect);
	DDX_Radio(pDX, IDC_unit, m_unit);
	DDX_Text(pDX, IDC_FarmTYear, m_FarmYears);
	DDX_Text(pDX, IDC_FarmYear, m_FarmYear);
	DDX_Text(pDX, IDC_TotalFields, m_TotalFields);
	DDX_Text(pDX, IDC_SumHa, m_SumHa);
	DDX_Text(pDX, IDC_SumManure, m_SumManure);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dndc_ManureFarmCrops, CPropertyPage)
	//{{AFX_MSG_MAP(dndc_ManureFarmCrops)
	ON_BN_CLICKED(IDC_ManureCrop, OnManureCrop)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(IDC_unit2, Onunit2)
	ON_BN_CLICKED(IDC_NextRotation3, OnNextRotation3)
	ON_BN_CLICKED(IDC_LastRotation3, OnLastRotation3)
	ON_EN_KILLFOCUS(IDC_TotalFields, OnKillfocusTotalFields)
	ON_BN_CLICKED(IDC_CropSelect, OnCropSelect)
	ON_EN_SETFOCUS(IDC_SumHa, OnSetfocusSumHa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dndc_ManureFarmCrops message handlers
float FarmFieldHa[11]={0.0,0.0}, ManuFraction[11]={0.0,0.0};

void dndc_ManureFarmCrops::OnManureCrop() 
{
	// TODO: Add your control notification handler code here
	CString XFF;
	FILE *xff;

	UpdateData(TRUE);
	
	if(m_CropSelect==-1) 
	{
		AfxMessageBox("Please select a crop for definition");
		return;
	}

	FCT.Format("%s_%d", INTERMANAGE, m_CropSelect+1);
	_mkdir(FCT); 

	//create routine input file
	int m_RotationID=1, m_RotationN=1;
	int m_RotationYear=m_FarmYears;
	int m_CycleYear=m_FarmYears;
	

	ManuFraction[1]=m_manure1; ManuFraction[2]=m_manure2; ManuFraction[3]=m_manure3; ManuFraction[4]=m_manure4; ManuFraction[5]=m_manure5; 
	ManuFraction[6]=m_manure6; ManuFraction[7]=m_manure7; ManuFraction[8]=m_manure8; ManuFraction[9]=m_manure9; ManuFraction[10]=m_manure10;

	FarmFieldHa[1]=m_land1; FarmFieldHa[2]=m_land2; FarmFieldHa[3]=m_land3; FarmFieldHa[4]=m_land4; FarmFieldHa[5]=m_land5; 
	FarmFieldHa[6]=m_land6; FarmFieldHa[7]=m_land7; FarmFieldHa[8]=m_land8; FarmFieldHa[9]=m_land9; FarmFieldHa[10]=m_land10;

	DB.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);
	db=fopen(DB, "w");	
	fprintf(db, "%d %d\n", m_TotalFields, m_FarmYears); 
	fclose(db);

	
	for(int YFM=1; YFM<=10; YFM++)//m_TotalFields
	{
		DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM, m_FarmYear);
		db=fopen(DB, "w");	
		fprintf(db, "%d %f %f\n", YFM, FarmFieldHa[YFM], ManuFraction[YFM]); 
		fclose(db);
	}

	
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	db=fopen(DB, "w");
	fprintf(db, "%d %d", m_RotationID, m_FarmYear);
	fclose(db);

	DB.Format("%s\\CropRotation.txt", FCT);//###
	db=fopen(DB, "w");
	fprintf(db, "%d", m_RotationN);
	fclose(db);

	DB.Format("%s\\CropRotation_%d.txt", FCT, m_RotationID);//write: ManureFarmCrop, OK
	db=fopen(DB, "w");
	fprintf(db, "%d %d %d", m_RotationID, m_RotationYear, m_CycleYear);
	fclose(db);

	UpdateData(TRUE);

	DB.Format("%s\\CropRotation_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
			DB.Format("%s\\CropRotation_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
			db=fopen(DB, "w");
			if(db==NULL) note(1,DB);
			fprintf(db, "%d\n", 0);
			fclose(db);
	}
	else
		fclose(dbq);

	//DB.Format("%s\\Inter\\CropTill_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
	DB.Format("%s\\CropTill_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		//DB.Format("%s\\Inter\\CropTill_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);	
		DB.Format("%s\\CropTill_%d_%d.txt", FCT, m_RotationID, m_FarmYear);	
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

	//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
	DB.Format("%s\\CropFert_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		//DB.Format("%s\\Inter\\CropFert_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
		DB.Format("%s\\CropFert_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
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

	//DB.Format("%s\\Inter\\CropManu_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
	DB.Format("%s\\CropManu_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{

		//DB.Format("%s\\Inter\\CropManu_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
		DB.Format("%s\\CropManu_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
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

	DB.Format("%s\\CropPlastic_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		DB.Format("%s\\CropPlastic_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
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

	//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
	DB.Format("%s\\CropFloo_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{

			//DB.Format("%s\\Inter\\CropFloo_%d_%d.txt", OUTPUT, m_RotationID,m_FarmYear);
		DB.Format("%s\\CropFloo_%d_%d.txt", FCT, m_RotationID,m_FarmYear);
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

	DB.Format("%s\\CropIrri_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
		DB.Format("%s\\CropIrri_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
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

	//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
	DB.Format("%s\\CropGraz_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{
			//DB.Format("%s\\Inter\\CropGraz_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
		DB.Format("%s\\CropGraz_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
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

	//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
	DB.Format("%s\\GrassCut_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
	dbq=fopen(DB, "r");
	if(dbq==NULL)
	{

			//DB.Format("%s\\Inter\\GrassCut_%d_%d.txt", OUTPUT, m_RotationID, m_FarmYear);
		DB.Format("%s\\GrassCut_%d_%d.txt", FCT, m_RotationID, m_FarmYear);
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

	//Create new files for manure farm cropland
	
	float TotalLandF = m_land1+m_land2+m_land3+m_land4+m_land5+m_land6+m_land7+m_land8+m_land9+m_land10;
	float TotalManureF = m_manure1+m_manure2+m_manure3+m_manure4+m_manure5+m_manure6+m_manure7+m_manure8+m_manure9+m_manure10;

	if(TotalLandF!=m_TotalHa)
	{		
		XFF.Format("Sum of the defined cropfield areas (%5.2f) is not equal to the total area (%5.2f)", TotalLandF, m_TotalHa);
		AfxMessageBox(XFF);
		return;
	}

	if(TotalManureF!=1.0)
	{
		XFF.Format("The sum of manure fractions is not 1 but %f", TotalManureF);
		AfxMessageBox(XFF);
		return;
	}	

	
	int kk=0, CropType[11]={0,0};

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 1);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 1, m_land1, m_manure1);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 2);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 2, m_land2, m_manure2);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 3);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 3, m_land3, m_manure3);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 4);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 4, m_land4, m_manure4);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 5);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 5, m_land5, 0.01*m_manure5);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 6);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 6, m_land6, m_manure6);
	fclose(xff);
	
	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 7);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 7, m_land7, m_manure7);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 8);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 8, m_land8, m_manure8);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 9);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 9, m_land9, m_manure9);
	fclose(xff);

	XFF.Format("%s\\YearLandManureFraction_%d_%d", INTER, m_FarmYear, 10);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %f %f\n", 10, m_land10, m_manure10);
	fclose(xff);

	
/*	if(m_land1>0.0)
	{
		kk++;
		CropType[kk]=m_CropType1;
				
		XFF.Format("%s\\ManureCrop_%d", INTER, kk);		
		xff=fopen(XFF, "w");
		if(xff==NULL) note(1,XFF);
		fprintf(xff, "%d  %f  %f\n", CropType[kk], m_land1, m_manure1);
		fclose(xff);

		CropArea[kk]=m_land1;
		if(m_unit==1) CropArea[kk] *= ac_ha;//acre -> ha
		ManuFraction[kk]=m_manure1;
	}


*/

	XFF.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d %d\n", m_TotalFields, m_FarmYears);
	/*for(int i=1;i<=kk;i++)
	{
		fprintf(xff, "%d  %d  %f  %f\n", i, CropType[i], CropArea[i], ManuFraction[i]);
	}*/
	fclose(xff);
		
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "w");
	if(xff==NULL) note(1,XFF);
	fprintf(xff, "%d  %d  %d\n", kk, m_CropSelect+1, CropType[m_CropSelect+1]);
	fclose(xff);
	
	CCropPSheet CropSheet;

	if (CropSheet.DoModal()==IDOK) //GetParameter from Page 4 OK
	{
		
	}

	//AfxMessageBox("Good");		 
}



BOOL dndc_ManureFarmCrops::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	int CropOrder, FarmCropType[11]={-1,-1}, TotalFields=0;
	float FarmCropHa[11]={0.0,0.0}, ManuFraction[11]={0.0,0.0};
	
	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Inter\\UnitSystem", OUTPUT);
	ddb=fopen(LB, "r");
	if(ddb==NULL) note(0, LB);
	fscanf(ddb, "%d", &m_unit);
	fclose(ddb);

	float TotalHa;
	CString XFF;
	FILE *xff;
	XFF.Format("%s\\Inter\\ManureField.txt", OUTPUT);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%f", &TotalHa);
	fclose(xff);

	m_TotalHa = TotalHa;

	if(m_unit==1) TotalHa /= ac_ha;//ha -> acre

	CString LLAI;
	FILE *llai;

	LLAI.Format("%s\\Inter\\TotalYears", OUTPUT);
	llai = fopen(LLAI, "r");
	fscanf(llai, "%d", &m_FarmYears);
	fclose(llai);

	UpdateData(FALSE);

	XFF.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);		
	xff=fopen(XFF, "r");
	if(xff==NULL) 
	{
		TotalFields = 0;
		xff=fopen(XFF, "w");
		fprintf(xff, "%d %d\n", TotalFields, m_FarmYears);
		fclose(xff);
	}
	else
	{
		fscanf(xff, "%d %d", &TotalFields, &m_FarmYears);
		for(int i=1;i<=TotalFields;i++)
		{
			fscanf(xff,"%d %d %f %f",&CropOrder, &FarmCropType[i], &FarmCropHa[i], &ManuFraction[i]);
			if(m_unit==1) FarmCropHa[i] /= ac_ha;//ha -> acre
		}
		fclose(xff);
	}

	
	
	m_CropType1 = FarmCropType[1];
	m_land1 = FarmCropHa[1];
	m_manure1 = ManuFraction[1];//*100.0;

	m_CropType2 = FarmCropType[2];
	m_land2 = FarmCropHa[2];
	m_manure2 = ManuFraction[2];//*100.0;

	m_CropType3 = FarmCropType[3];
	m_land3 = FarmCropHa[3];
	m_manure3 = ManuFraction[3];//*100.0;

	m_CropType4 = FarmCropType[4];
	m_land4 = FarmCropHa[4];
	m_manure4 = ManuFraction[4];//*100.0;

	m_CropType5 = FarmCropType[5];
	m_land5 = FarmCropHa[5];
	m_manure5 = ManuFraction[5];//*100.0;

	m_CropType6 = FarmCropType[6];
	m_land6 = FarmCropHa[6];
	m_manure6 = ManuFraction[6];//*100.0;

	m_CropType7 = FarmCropType[7];
	m_land7 = FarmCropHa[7];
	m_manure7 = ManuFraction[7];//*100.0;

	m_CropType8 = FarmCropType[8];
	m_land8 = FarmCropHa[8];
	m_manure8 = ManuFraction[8];//*100.0;

	m_CropType9 = FarmCropType[9];
	m_land9 = FarmCropHa[9];
	m_manure9 = ManuFraction[9];//*100.0;

	m_CropType10 = FarmCropType[10];
	m_land10 = FarmCropHa[10];
	m_manure10 = ManuFraction[10];//*100.0;

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
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
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE); 
	}
	
	//////////////////////////////////////////////////////////
	int TotalYears=0, db_Rotation_Number, OpenFile;
	int db_RotationID[10], db_RotateSpan[10], db_CycleSpan[10], db_RotationCycles[10];

	//CString DB;
	//FILE *db;

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
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &OpenFile);
	fclose(db);

	TotalYears = IData.years;
	m_FarmYears = IData.years;

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

		//if(TYr != TotalYears)
		//{
			//CString note;
			//note.Format("Warning: Number of simulated years has been changed");
			//AfxMessageBox(note);
			//return 0;
		//}

	}
		
	m_FarmYears=TotalYears;
/*	m_RotationN  = db_Rotation_Number;
	m_RotationID = 1;	
	
	m_RotationYear=db_RotateSpan[m_RotationID];

	m_CycleYear=db_CycleSpan[m_RotationID];

	m_RotationCycles = (float)m_RotationYear / (float)m_CycleYear;//m_CycleYear

	if(m_FarmYear>m_CycleYear) m_FarmYear=1;
*/
	//////////////////////////////////////////////////////////
	//m_TotalHa = TotalHa;

	UpdateData(FALSE);

	//Onunit2();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dndc_ManureFarmCrops::Onunit() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==0&&n_unit==1) 
	{
		m_land1 *= ac_ha;// acre -> ha
		m_land2 *= ac_ha;
		m_land3 *= ac_ha;
		m_land4 *= ac_ha;
		m_land5 *= ac_ha;
		m_land6 *= ac_ha;
		m_land7 *= ac_ha;
		m_land8 *= ac_ha;
		m_land9 *= ac_ha;
		m_land10 *= ac_ha;	
		m_TotalHa *= ac_ha;
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
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
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE); 
	}	

	UpdateData(FALSE);
}

void dndc_ManureFarmCrops::Onunit2() 
{
	// TODO: Add your control notification handler code here
	int n_unit = m_unit;

	UpdateData(TRUE);

	if(m_unit==1&&n_unit==0) 
	{
		m_land1 /= ac_ha;// ha -> acre
		m_land2 /= ac_ha;
		m_land3 /= ac_ha;
		m_land4 /= ac_ha;
		m_land5 /= ac_ha;
		m_land6 /= ac_ha;
		m_land7 /= ac_ha;
		m_land8 /= ac_ha;
		m_land9 /= ac_ha;
		m_land10 /= ac_ha;	
		m_TotalHa /= ac_ha;
	}

	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_kg);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb);
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
		Edt=(CEdit *)GetDlgItem(IDC_kg5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_lb5);
		Edt->EnableWindow(FALSE); 
	}	

	UpdateData(FALSE);
}

void dndc_ManureFarmCrops::OnNextRotation3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	ManuFraction[1]=m_manure1; ManuFraction[2]=m_manure2; ManuFraction[3]=m_manure3; ManuFraction[4]=m_manure4; ManuFraction[5]=m_manure5; 
	ManuFraction[6]=m_manure6; ManuFraction[7]=m_manure7; ManuFraction[8]=m_manure8; ManuFraction[9]=m_manure9; ManuFraction[10]=m_manure10;

	FarmFieldHa[1]=m_land1; FarmFieldHa[2]=m_land2; FarmFieldHa[3]=m_land3; FarmFieldHa[4]=m_land4; FarmFieldHa[5]=m_land5; 
	FarmFieldHa[6]=m_land6; FarmFieldHa[7]=m_land7; FarmFieldHa[8]=m_land8; FarmFieldHa[9]=m_land9; FarmFieldHa[10]=m_land10;

	for(int YFM=1; YFM<=10; YFM++)//m_TotalFields
	{
		DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM, m_FarmYear);
		db=fopen(DB, "w");	
		fprintf(db, "%d %f %f\n", YFM, FarmFieldHa[YFM], ManuFraction[YFM]); 
		fclose(db);
	}

/*	ManureFraction1[m_FarmYear] = m_manure1;
	ManureFraction2[m_FarmYear] = m_manure2;
	ManureFraction3[m_FarmYear] = m_manure3;
	ManureFraction4[m_FarmYear] = m_manure4;
	ManureFraction5[m_FarmYear] = m_manure5;
	ManureFraction6[m_FarmYear] = m_manure6;
	ManureFraction7[m_FarmYear] = m_manure7;
	ManureFraction8[m_FarmYear] = m_manure8;
	ManureFraction9[m_FarmYear] = m_manure9;
	ManureFraction10[m_FarmYear] = m_manure10;*/
	
	if (m_FarmYear<m_FarmYears) m_FarmYear++;

	float sumha=0.0, summanure=0.0, jf;
	for(int YFM1=1; YFM1<=10; YFM1++)//m_TotalFields
	{
		DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM1, m_FarmYear);
		db=fopen(DB, "r");	
		if(db==NULL)
		{
			ManuFraction[YFM1] = 0.0;
		}
		else
		{
			fscanf(db, "%d %f %f\n", &jdd, &jf, &ManuFraction[YFM1]); //FarmFieldHa[YFM1]
			fclose(db);
		}

		sumha += FarmFieldHa[YFM1];
		summanure += ManuFraction[YFM1];
	}
	m_SumHa = sumha;
	m_SumManure = summanure;

	m_manure1=ManuFraction[1]; m_manure2=ManuFraction[2]; m_manure3=ManuFraction[3]; m_manure4=ManuFraction[4]; m_manure5=ManuFraction[5]; 
	m_manure6=ManuFraction[6]; m_manure7=ManuFraction[7]; m_manure8=ManuFraction[8]; m_manure9=ManuFraction[9]; m_manure10=ManuFraction[10]; 

	m_land1=FarmFieldHa[1]; m_land2=FarmFieldHa[2]; m_land3=FarmFieldHa[3]; m_land4=FarmFieldHa[4]; m_land5=FarmFieldHa[5]; 
	m_land6=FarmFieldHa[6]; m_land7=FarmFieldHa[7]; m_land8=FarmFieldHa[8]; m_land9=FarmFieldHa[9]; m_land10=FarmFieldHa[10]; 
		
/*	m_manure1 = ManureFraction1[m_FarmYear]; 
	m_manure2 = ManureFraction2[m_FarmYear]; 
	m_manure3 = ManureFraction3[m_FarmYear]; 
	m_manure4 = ManureFraction4[m_FarmYear]; 
	m_manure5 = ManureFraction5[m_FarmYear]; 
	m_manure6 = ManureFraction6[m_FarmYear]; 
	m_manure7 = ManureFraction7[m_FarmYear]; 
	m_manure8 = ManureFraction8[m_FarmYear]; 
	m_manure9 = ManureFraction9[m_FarmYear]; 
	m_manure10 = ManureFraction10[m_FarmYear];*/

	if(m_FarmYear>1)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_LandArea1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea6);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea7);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea8);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea9);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea10);
		Edt->EnableWindow(FALSE); 		
	}
	else
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_LandArea1);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea6);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea7);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea8);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea9);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea10);
		Edt->EnableWindow(TRUE); 		
	}

	UpdateData(FALSE);

}

void dndc_ManureFarmCrops::OnLastRotation3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_FarmYears==0) return;

	ManuFraction[1]=m_manure1; ManuFraction[2]=m_manure2; ManuFraction[3]=m_manure3; ManuFraction[4]=m_manure4; ManuFraction[5]=m_manure5; 
	ManuFraction[6]=m_manure6; ManuFraction[7]=m_manure7; ManuFraction[8]=m_manure8; ManuFraction[9]=m_manure9; ManuFraction[10]=m_manure10;

	FarmFieldHa[1]=m_land1; FarmFieldHa[2]=m_land2; FarmFieldHa[3]=m_land3; FarmFieldHa[4]=m_land4; FarmFieldHa[5]=m_land5; 
	FarmFieldHa[6]=m_land6; FarmFieldHa[7]=m_land7; FarmFieldHa[8]=m_land8; FarmFieldHa[9]=m_land9; FarmFieldHa[10]=m_land10;

	for(int YFM=1; YFM<=10; YFM++)//m_TotalFields
	{
		DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM, m_FarmYear);
		db=fopen(DB, "w");	
		fprintf(db, "%d %f %f\n", YFM, FarmFieldHa[YFM], ManuFraction[YFM]); 
		fclose(db);
	}

/*	ManureFraction1[m_FarmYear] = m_manure1;
	ManureFraction2[m_FarmYear] = m_manure2;
	ManureFraction3[m_FarmYear] = m_manure3;
	ManureFraction4[m_FarmYear] = m_manure4;
	ManureFraction5[m_FarmYear] = m_manure5;
	ManureFraction6[m_FarmYear] = m_manure6;
	ManureFraction7[m_FarmYear] = m_manure7;
	ManureFraction8[m_FarmYear] = m_manure8;
	ManureFraction9[m_FarmYear] = m_manure9;
	ManureFraction10[m_FarmYear] = m_manure10;*/

	if (m_FarmYear>1) m_FarmYear--;

	float sumha=0.0, summanure=0.0;
	for(int YFM1=1; YFM1<=10; YFM1++)//m_TotalFields
	{
		DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM1, m_FarmYear);
		db=fopen(DB, "r");
		if(db==NULL)
		{
			ManuFraction[YFM1] = 0.0;
		}
		else
		{
			fscanf(db, "%d %f %f\n", &jdd, &FarmFieldHa[YFM1], &ManuFraction[YFM1]); 
			fclose(db);
		}

		sumha += FarmFieldHa[YFM1];
		summanure += ManuFraction[YFM1];
	}
	m_SumHa = sumha;
	m_SumManure = summanure;

	m_manure1=ManuFraction[1]; m_manure2=ManuFraction[2]; m_manure3=ManuFraction[3]; m_manure4=ManuFraction[4]; m_manure5=ManuFraction[5]; 
	m_manure6=ManuFraction[6]; m_manure7=ManuFraction[7]; m_manure8=ManuFraction[8]; m_manure9=ManuFraction[9]; m_manure10=ManuFraction[10]; 

	m_land1=FarmFieldHa[1]; m_land2=FarmFieldHa[2]; m_land3=FarmFieldHa[3]; m_land4=FarmFieldHa[4]; m_land5=FarmFieldHa[5]; 
	m_land6=FarmFieldHa[6]; m_land7=FarmFieldHa[7]; m_land8=FarmFieldHa[8]; m_land9=FarmFieldHa[9]; m_land10=FarmFieldHa[10]; 
	
	
/*	m_manure1 = ManureFraction1[m_FarmYear]; 
	m_manure2 = ManureFraction2[m_FarmYear]; 
	m_manure3 = ManureFraction3[m_FarmYear]; 
	m_manure4 = ManureFraction4[m_FarmYear]; 
	m_manure5 = ManureFraction5[m_FarmYear]; 
	m_manure6 = ManureFraction6[m_FarmYear]; 
	m_manure7 = ManureFraction7[m_FarmYear]; 
	m_manure8 = ManureFraction8[m_FarmYear]; 
	m_manure9 = ManureFraction9[m_FarmYear]; 
	m_manure10 = ManureFraction10[m_FarmYear];*/

	if(m_FarmYear>1)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_LandArea1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea6);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea7);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea8);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea9);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea10);
		Edt->EnableWindow(FALSE); 		
	}
	else
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_LandArea1);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea4);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea5);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea6);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea7);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea8);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea9);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea10);
		Edt->EnableWindow(TRUE); 		
	}

	UpdateData(FALSE);
}

BOOL dndc_ManureFarmCrops::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Inter\\UnitSystem", OUTPUT);
	ddb=fopen(LB, "r");
	if(ddb==NULL) note(0, LB);
	fscanf(ddb, "%d", &m_unit);
	fclose(ddb);

	float TotalHa, df=0.0;
	CString XFF;
	FILE *xff;
	XFF.Format("%s\\Inter\\ManureField.txt", OUTPUT);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%f", &TotalHa);
	fclose(xff);
	
	DB.Format("%s\\Inter\\ManureFieldCrops", OUTPUT);
	db=fopen(DB, "r");	
	fscanf(db, "%d %d", &m_TotalFields, &m_FarmYears); 
	fclose(db);

	if(m_unit==1) TotalHa /= ac_ha;//ha -> acre

	m_TotalHa = TotalHa;	

	float sumha=0.0, summanure=0.0;
	for(int YFM1=1; YFM1<=10; YFM1++)//m_TotalFields
	{
		DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM1, m_FarmYear);
		db=fopen(DB, "r");	
		if(db==NULL)
		{
			ManuFraction[YFM1] = 0.0;
		}
		else
		{
			fscanf(db, "%d %f %f\n", &jdd, &FarmFieldHa[YFM1], &ManuFraction[YFM1]); 
			fclose(db);
		}

		sumha += FarmFieldHa[YFM1];
		summanure += ManuFraction[YFM1];
	}
	m_SumHa = sumha;
	m_SumManure = summanure;

	m_manure1=ManuFraction[1]; m_manure2=ManuFraction[2]; m_manure3=ManuFraction[3]; m_manure4=ManuFraction[4]; m_manure5=ManuFraction[5]; 
	m_manure6=ManuFraction[6]; m_manure7=ManuFraction[7]; m_manure8=ManuFraction[8]; m_manure9=ManuFraction[9]; m_manure10=ManuFraction[10]; 

	m_land1=FarmFieldHa[1]; m_land2=FarmFieldHa[2]; m_land3=FarmFieldHa[3]; m_land4=FarmFieldHa[4]; m_land5=FarmFieldHa[5]; 
	m_land6=FarmFieldHa[6]; m_land7=FarmFieldHa[7]; m_land8=FarmFieldHa[8]; m_land9=FarmFieldHa[9]; m_land10=FarmFieldHa[10]; 

	
	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void dndc_ManureFarmCrops::OnKillfocusTotalFields() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEdit *Edt;
	if(m_TotalFields>0)
	{
		if(m_TotalFields>=1) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea1);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure1);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=2) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea2);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure2);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=3) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea3);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure3);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=4) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea4);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure4);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=5) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea5);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure5);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=6) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea6);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure6);
			Edt->EnableWindow(TRUE); 
		}
		
		if(m_TotalFields>=7) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea7);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure7);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=8) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea8);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure8);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=9) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea9);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure9);
			Edt->EnableWindow(TRUE); 
		}

		if(m_TotalFields>=10) 
		{
			Edt=(CEdit *)GetDlgItem(IDC_LandArea10);
			Edt->EnableWindow(TRUE); 
			Edt=(CEdit *)GetDlgItem(IDC_manure10);
			Edt->EnableWindow(TRUE); 
		}
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_LandArea1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea4);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea5);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea6);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea7);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea8);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea9);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_LandArea10);
		Edt->EnableWindow(FALSE); 

		Edt=(CEdit *)GetDlgItem(IDC_manure1);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure2);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure3);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure4);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure5);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure6);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure7);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure8);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure9);
		Edt->EnableWindow(FALSE);
		Edt=(CEdit *)GetDlgItem(IDC_manure10);
		Edt->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void dndc_ManureFarmCrops::OnCropSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	FarmField = m_CropSelect+1;
}

void dndc_ManureFarmCrops::OnSetfocusSumHa() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	float sumha=0.0, summanure=0.0;
	for(int YFM1=1; YFM1<=10; YFM1++)//m_TotalFields
	{
		DB.Format("%s\\Inter\\FarmFieldManureFraction_%d_%d", OUTPUT, YFM1, m_FarmYear);
		db=fopen(DB, "r");
		if(db==NULL)
		{
			FarmFieldHa[YFM1] = 0.0;
			ManuFraction[YFM1] = 0.0;
		}
		else
		{
			fscanf(db, "%d %f %f\n", &jdd, &FarmFieldHa[YFM1], &ManuFraction[YFM1]); 
			fclose(db);
		}

		sumha += FarmFieldHa[YFM1];
		summanure += ManuFraction[YFM1];
	}
	m_SumHa = sumha;
	m_SumManure = summanure;

	UpdateData(FALSE);
}
