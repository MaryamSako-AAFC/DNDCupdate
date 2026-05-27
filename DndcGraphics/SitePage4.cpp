// SitePage4.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"//"graphex.h"
#include "SitePara.h"
#include "SitePage4.h"
#include "SitePSheet.h"
#include "dndc_main.h"
#include "NewCrop.h"
#include "direct.h"
#include "dndc_tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CropArray			Crop;
extern Site_BaseInformation	IData ;
extern StringArray			ClimateFilename;
extern CropofEachYear CYr[2];
extern char *soiltexture[];
extern char *soillanduse[];

int PlantType;
int TotalManureFields, jd, ManureFieldOrder;
CString FCT4;
char CropNameX[100];

/////////////////////////////////////////////////////////////////////////////
// SitePage4 property page

IMPLEMENT_DYNCREATE(SitePage4, CPropertyPage)

SitePage4::SitePage4() : CPropertyPage(SitePage4::IDD)
{
	//{{AFX_DATA_INIT(SitePage4)
	m_GrowthReproductive = 0.0f;
	m_GrowthVegetative = 0.0f;
	m_PsnEfficiency = 0.0f;
	m_PsnMax = 0.0f;
	m_InitialBiomass = 0.0f;
	m_CropModel = 0;
	m_CropID = 0;
	m_CropHDay = 0;
	m_CropHMonth = 0;
	m_CropHYear = 0;
	m_CropN = 0;
	m_CropPDay = 0;
	m_CropPMonth = 0;
	m_CropResidue = 0.0f;
	m_CropYield = 0.0f;
	m_ShootYield = 0.0f;
	m_RootYield = 0.0f;
	m_CoverCrop = 0;
	m_PerennialCrop = FALSE;
	m_ShootFraction = 0.0f;
	m_ShootCN = 0.0f;
	m_RootFraction = 0.0f;
	m_RootCN = 0.0f;
	m_GrainFraction = 0.0f;
	m_GrainCN = 0.0f;
	m_CropWaterDemand = 0.0f;
	m_RootShape = 5;
	m_GrainFill =0.0f;
	m_CropTotalN = 0.0f;
	m_CropTDD = 0.0f;
	m_CropNfixation = 0.0f;
	m_CropLAI = 30.0f;
	m_Vascularity = 1.5f;
	m_OptT = 25.0f;
	m_LeafCN = 0.0f;
	m_LeafFraction = 0.0f;
	m_LeafYield = 0.0f;
	m_TreeLeafMax = 0.0f;
	m_TreeLeafMin = 0.0f;
	m_TreeCurrentAge = 0.0f;
	m_LAImax = 2.5f;
	m_FrostKill = -2.0f;
	m_AlfCHRMX;
	m_ALFCDRMX;
	m_ALFCTMX;
	m_ALFPDFMX;
	m_Root1 = 0.4f;
	m_Root2=0.007f;
	m_AGResp1 = 0.4f;
	m_AGResp2 = 0.007f;
	m_cropGRate = 0.3f;
	m_cropTime = 10.0f;
	m_RUEHI = 1.0f;
	m_DelayP = 1.0f;

	//}}AFX_DATA_INIT
}

SitePage4::~SitePage4()
{
}

void SitePage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SitePage4)
	DDX_Control(pDX, IDC_LIST1, m_CropList);
	DDX_Control(pDX, IDC_CropType, m_CropType);
	DDX_Text(pDX, IDC_GrowthReproductive, m_GrowthReproductive);
	DDX_Text(pDX, IDC_GrowthVegetative, m_GrowthVegetative);
	DDX_Text(pDX, IDC_PsnEfficiency, m_PsnEfficiency);
	DDX_Text(pDX, IDC_PsnMax, m_PsnMax);
	DDX_Text(pDX, IDC_SeedDensity, m_InitialBiomass);
	DDX_Radio(pDX, IDC_CropModel, m_CropModel);
	DDX_Text(pDX, IDC_CropID, m_CropID);
	DDX_Text(pDX, IDC_CropHDay, m_CropHDay);
	DDX_Text(pDX, IDC_CropHMonth, m_CropHMonth);
	DDX_Text(pDX, IDC_CropHYear, m_CropHYear);
	DDX_Text(pDX, IDC_CropN, m_CropN);
	DDX_Text(pDX, IDC_CropPDay, m_CropPDay);
	DDX_Text(pDX, IDC_CropPMonth, m_CropPMonth);
	DDX_Text(pDX, IDC_CropResidue, m_CropResidue);
	DDX_Text(pDX, IDC_CropYield, m_CropYield);
	DDX_Text(pDX, IDC_ShootYield, m_ShootYield);
	DDX_Text(pDX, IDC_RootYield, m_RootYield);
	DDX_Radio(pDX, IDC_CoverCrop, m_CoverCrop);
	DDX_Check(pDX, IDC_PerennialCrop, m_PerennialCrop);
	DDX_Text(pDX, IDC_ShootFRaction, m_ShootFraction);
	DDX_Text(pDX, IDC_ShootCN, m_ShootCN);
	DDX_Text(pDX, IDC_RootFraction, m_RootFraction);
	DDX_Text(pDX, IDC_RootCN, m_RootCN);
	DDX_Text(pDX, IDC_GrainFraction, m_GrainFraction);
	DDX_Text(pDX, IDC_GrainCN, m_GrainCN);
	DDX_Text(pDX, IDC_CropWaterDemand, m_CropWaterDemand);
	DDX_Text(pDX, IDC_CropTotalN, m_CropTotalN);
	DDX_Text(pDX, IDC_CropTDD, m_CropTDD);
	DDX_Text(pDX, IDC_CropNfixation, m_CropNfixation);
	DDX_Text(pDX, IDC_CropLAI, m_CropLAI);
	DDX_Text(pDX, IDC_Vascularity, m_Vascularity);
	DDX_Text(pDX, IDC_RootShape, m_RootShape);
	DDX_Text(pDX, IDC_LAImax, m_LAImax);
	DDX_Text(pDX, IDC_FrostKill, m_FrostKill);
	DDX_Text(pDX, IDC_AlfCHRMX, m_AlfCHRMX);
	DDX_Text(pDX, IDC_ALFCDRMX, m_ALFCDRMX);
	DDX_Text(pDX, IDC_ALFCTMX, m_ALFCTMX);
	DDX_Text(pDX, IDC_ALFPDFMX, m_ALFPDFMX);
	DDX_Text(pDX, IDC_Root1, m_Root1);
	DDX_Text(pDX, IDC_Root2, m_Root2);
	DDX_Text(pDX, IDC_AGResp1, m_AGResp1);
	DDX_Text(pDX, IDC_AGResp2, m_AGResp2);
	DDX_Text(pDX, IDC_GrainFill, m_GrainFill);
	DDX_Text(pDX, IDC_OptT, m_OptT);
	DDX_Text(pDX, IDC_LeafCN, m_LeafCN);
	DDX_Text(pDX, IDC_LeafFRaction, m_LeafFraction);
	DDX_Text(pDX, IDC_LeafYield, m_LeafYield);
	DDX_Text(pDX, IDC_TreeLeafMax, m_TreeLeafMax);
	DDX_Text(pDX, IDC_TreeLeafMin, m_TreeLeafMin);
	DDX_Text(pDX, ID_TreeCurrentAge, m_TreeCurrentAge);
	DDX_Text(pDX, IDC_cropGRate, m_cropGRate);
	DDX_Text(pDX, IDC_cropGRate2, m_cropTime);
	DDX_Text(pDX, IDC_LowRUEHI, m_RUEHI);
	DDX_Text(pDX, IDC_RUETime, m_DelayP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SitePage4, CPropertyPage)
	//{{AFX_MSG_MAP(SitePage4)
	ON_EN_KILLFOCUS(IDC_CropN, OnKillfocusCropN)
	ON_EN_KILLFOCUS(IDC_CropHYear, OnKillfocusCropHYear)
	ON_EN_KILLFOCUS(IDC_CropHMonth, OnKillfocusCropHMonth)
	ON_EN_KILLFOCUS(IDC_CropHDay, OnKillfocusCropHDay)
	ON_BN_CLICKED(IDC_CropNext, OnCropNext)
	ON_BN_CLICKED(IDC_CropLast, OnCropLast)
	ON_BN_CLICKED(IDC_CropAccept, OnCropAccept)
	ON_EN_KILLFOCUS(IDC_CropYield, OnKillfocusCropYield)
	ON_EN_KILLFOCUS(IDC_CropPMonth, OnKillfocusCropPMonth)
	ON_EN_KILLFOCUS(IDC_CropPDay, OnKillfocusCropPDay)
	ON_EN_KILLFOCUS(IDC_CropResidue, OnKillfocusCropResidue)
	ON_CBN_SELCHANGE(IDC_CropType, OnSelchangeCropType)
	ON_BN_CLICKED(IDC_AskCartivar, OnAskCartivar)
	ON_EN_KILLFOCUS(IDC_SeedDensity, OnKillfocusSeedDensity)
	ON_EN_KILLFOCUS(IDC_PsnEfficiency, OnKillfocusPsnEfficiency)
	ON_EN_KILLFOCUS(IDC_PsnMax, OnKillfocusPsnMax)
	ON_EN_KILLFOCUS(IDC_GrowthVegetative, OnKillfocusGrowthVegetative)
	ON_EN_KILLFOCUS(IDC_GrowthReproductive, OnKillfocusGrowthReproductive)
	ON_BN_CLICKED(IDC_CropModel, OnCropModel)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_KILLFOCUS(IDC_ShootYield, OnKillfocusShootYield)
	ON_EN_CHANGE(IDC_CropN, OnChangeCropN)
	ON_BN_CLICKED(IDC_CropParas, OnCropParas)
	ON_EN_KILLFOCUS(IDC_RootYield, OnKillfocusRootYield)
	ON_BN_CLICKED(IDC_PerennialCrop, OnPerennialCrop)
	ON_EN_KILLFOCUS(IDC_GrainFraction, OnKillfocusGrainFraction)
	ON_EN_KILLFOCUS(IDC_ShootFRaction, OnKillfocusShootFRaction)
	ON_EN_KILLFOCUS(IDC_GrainCN, OnKillfocusGrainCN)
	ON_EN_KILLFOCUS(IDC_ShootCN, OnKillfocusShootCN)
	ON_EN_KILLFOCUS(IDC_RootCN, OnKillfocusRootCN)
	ON_EN_KILLFOCUS(IDC_LeafFRaction, OnKillfocusLeafFRaction)
	ON_EN_KILLFOCUS(IDC_LeafCN, OnKillfocusLeafCN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SitePage4 message handlers

void SitePage4::OnKillfocusCropN() 
{

}


BOOL SitePage4::CheckCropN()
{

	return TRUE;
}


BOOL SitePage4::CheckCropID()
{

	return TRUE;
}


void SitePage4::OnKillfocusCropHYear() 
{
	UpdateData(TRUE);

}

void SitePage4::OnKillfocusCropHMonth() 
{
	UpdateData(TRUE);
	
	if(m_CropHMonth > m_CropPMonth) m_CropHYear = 1;
	else m_CropHYear = 2;

	UpdateData(FALSE);
}

void SitePage4::OnKillfocusCropHDay() 
{
	UpdateData(TRUE);
}

BOOL SitePage4::SetPlantList()
{
	int i,id,CropNum,Si=m_CropType.GetCurSel();
	FILE *fCrop;
	char fname[256];

	///////////////////////////////////////////////////////////////////////////////////////////
	int v_CropID[95], v_Perennial[95];
	float v_max_biomass_C[95], v_grain_fraction[95], v_leaf_fraction[95], v_leafstem_fraction[95], v_root_fraction[95];
	float v_GrainCN[95], v_LeafCN[95], v_ShootCN[95], v_RootCN[95], v_TreeAge[95];
	float v_WaterDemand[95], v_OptimumT[95], v_TDD[95], v_Nfixation[95], v_Vascularity[95];
	float v_Root1[95], v_Root2[95], v_AGResp1[95], v_AGResp2[95];//new Root Respiration
	float v_Kext1[95], v_Kext2[95],v_CMaxH[95];
	float v_cropGRate[95], v_cropTime[95], v_RUEHI[95], v_DelayP[95];//new controls for crops //theo
	char v_CropName[95][100]={"NONE","NONE"};

	ReadCropPara1(v_CropID, v_CropName, v_max_biomass_C, v_grain_fraction, v_leaf_fraction,
				  v_leafstem_fraction, v_root_fraction, v_GrainCN, 
				  v_LeafCN, v_ShootCN, v_RootCN, v_WaterDemand, v_OptimumT, 
				  v_TDD, v_Nfixation, v_Vascularity, v_Perennial, v_TreeAge,v_Root1,v_Root2,v_AGResp1,v_AGResp2,v_Kext1,v_Kext2,v_CMaxH,v_cropGRate,v_cropTime,v_RUEHI,v_DelayP);

	///////////////////////////////////////////////////////////////////////////////////////////

	m_CropType.ResetContent();
	
	for (i=0;i<=90;i++)
	{
		EraseFBSpace(v_CropName[i]);
		sprintf(fname,"%d %s",i,v_CropName[i]);
		m_CropType.AddString(fname);
	}

	if (Si>=0) m_CropType.SetCurSel(Si);
	return 0;
}

BOOL SitePage4::OnSetActive() 
{
	CropNChangeFlag = 0;
	m_CropModel = 0;
	
    int i, rrr, yyy;
	CString txt,DB;
	FILE *db;

#ifdef MANURE	
	CString XFF;
	FILE *xff;		
	XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d %d", &TotalManureFields, &ManureFieldOrder, &jd);
	fclose(xff);
	FCT4.Format("%s_%d", INTERMANAGE, ManureFieldOrder);
#else
	FCT4.Format("%s_1", INTERMANAGE);
#endif

	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT4);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropRotation_%d_%d.txt", FCT4, rrr, yyy);
	db=fopen(DB, "r");
	if(db==NULL) note(0, DB);
	fscanf(db, "%d", &cropn[rrr][yyy]);
	m_CropN = cropn[rrr][yyy];

	if(m_CropN==0)
	{
		for(i=0; i<=5; i++)
		{
			crop_order[rrr][yyy][i]=0;
			crop_type[rrr][yyy][i]=0;
			plant_month[rrr][yyy][i]=0;
			plant_day[rrr][yyy][i]=0;
			harvest_month[rrr][yyy][i]=0;
			harvest_day[rrr][yyy][i]=0;
			harvest_year[rrr][yyy][i]=0;
			crop_residue[rrr][yyy][i]=0.0;
			crop_yield[rrr][yyy][i]=0.0;
			rate_reproduc[rrr][yyy][i]=0.0;
			Transplant[rrr][yyy][i]=0;
			Psn_efficiency[rrr][yyy][i]=0.0;
			Psn_max[rrr][yyy][i]=0.0;
			TreeAge[rrr][yyy][i]=0.0;
			TreeCurrentAge[rrr][yyy][i]=0.0;
			TreeLeafMax[rrr][yyy][i]=0.0;
			TreeLeafMin[rrr][yyy][i]=0.0;
			CoverCrop[rrr][yyy][i]=0;
			PerennialCrop[rrr][yyy][i]=0;

			GrainFraction[rrr][yyy][i]=0.0; 
			LeafFraction[rrr][yyy][i]=0.0;
			ShootFraction[rrr][yyy][i]=0.0;
			RootFraction[rrr][yyy][i]=0.0;
			GrainCN[rrr][yyy][i]=0.0;
			LeafCN[rrr][yyy][i]=0.0; 
			ShootCN[rrr][yyy][i]=0.0; 
			RootCN[rrr][yyy][i]=0.0; 
			TDD[rrr][yyy][i]=0.0; 
			WaterDemand[rrr][yyy][i]=0.0;
			GrainFill[rrr][yyy][i]=0.0;
			RootShape[rrr][yyy][i]=0;
			LAImax[rrr][yyy][i] = 0;
			FrostKill[rrr][yyy][i] = 0;
			AlfCHRMX[rrr][yyy][i] = 0;
			ALFCDRMX[rrr][yyy][i] = 0;
			ALFCTMX[rrr][yyy][i] = 0;
			ALFPDFMX[rrr][yyy][i] = 0;
			Root1[rrr][yyy][i] = 0.0;
			Root2[rrr][yyy][i] = 0.0;
			AGResp1[rrr][yyy][i] = 0.0;
			AGResp2[rrr][yyy][i] = 0.0;
			cropGRate[rrr][yyy][i] = 0.0;
			cropTime[rrr][yyy][i] = 0.0;
			RUEHI[rrr][yyy][i] = 0.0;
			DelayP[rrr][yyy][i] = 0.0;
			OptT[rrr][yyy][i]=0.0; 
			Nfixation[rrr][yyy][i]=0.0;
			Vascularity[rrr][yyy][i]=0.0;
		}
	}
	else//read from cropRotation database
	{			
		for (i = 1; i<=cropn[rrr][yyy];i++) 
		{
			fscanf(db, "%d", &crop_order[rrr][yyy][i]);
			fscanf(db, "%d", &crop_type[rrr][yyy][i]);
			fscanf(db, "%d %d", &plant_month[rrr][yyy][i], &plant_day[rrr][yyy][i]);
			fscanf(db, "%d %d", &harvest_month[rrr][yyy][i], &harvest_day[rrr][yyy][i]);
			fscanf(db, "%d", &harvest_year[rrr][yyy][i]);
			fscanf(db, "%f", &crop_residue[rrr][yyy][i]);
			fscanf(db, "%f", &crop_yield[rrr][yyy][i]);
			fscanf(db, "%f %d %f %f %f", &rate_reproduc[rrr][yyy][i], 
				&Transplant[rrr][yyy][i], &Psn_efficiency[rrr][yyy][i], 
				&Psn_max[rrr][yyy][i], &TreeAge[rrr][yyy][i]);
			fscanf(db, "%d", &CoverCrop[rrr][yyy][i]);
			fscanf(db, "%d", &PerennialCrop[rrr][yyy][i]);

			fscanf(db, "%f", &GrainFraction[rrr][yyy][i]); 
			fscanf(db, "%f", &LeafFraction[rrr][yyy][i]);
			fscanf(db, "%f", &ShootFraction[rrr][yyy][i]);
			fscanf(db, "%f", &RootFraction[rrr][yyy][i]);
			fscanf(db, "%f", &GrainCN[rrr][yyy][i]);
			fscanf(db, "%f", &LeafCN[rrr][yyy][i]); 
			fscanf(db, "%f", &ShootCN[rrr][yyy][i]); 
			fscanf(db, "%f", &RootCN[rrr][yyy][i]); 
			fscanf(db, "%f", &TDD[rrr][yyy][i]); 
			fscanf(db, "%f", &WaterDemand[rrr][yyy][i]);
			fscanf(db, "%f", &OptT[rrr][yyy][i]); 
			fscanf(db, "%f", &Nfixation[rrr][yyy][i]);
			fscanf(db, "%f", &Vascularity[rrr][yyy][i]);
			fscanf(db, "%f", &TreeAge[rrr][yyy][i]);
			fscanf(db, "%f", &TreeCurrentAge[rrr][yyy][i]);
			fscanf(db, "%f", &TreeLeafMax[rrr][yyy][i]);
			fscanf(db, "%f", &TreeLeafMin[rrr][yyy][i]);
			fscanf(db, "%d", &RootShape[rrr][yyy][i]);
			fscanf(db, "%f", &GrainFill[rrr][yyy][i]);
			fscanf(db, "%f", &LAImax[rrr][yyy][i]);
			fscanf(db, "%f", &FrostKill[rrr][yyy][i]);
			fscanf(db, "%f", &AlfCHRMX[rrr][yyy][i]);
			fscanf(db, "%f", &ALFCDRMX[rrr][yyy][i]);
			fscanf(db, "%f", &ALFCTMX[rrr][yyy][i]);
			fscanf(db, "%f", &ALFPDFMX[rrr][yyy][i]);
			fscanf(db, "%f", &Root1[rrr][yyy][i]);
			fscanf(db, "%f", &Root2[rrr][yyy][i]);
			fscanf(db, "%f", &AGResp1[rrr][yyy][i]);
			fscanf(db, "%f", &AGResp2[rrr][yyy][i]);
			fscanf(db, "%f", &cropGRate[rrr][yyy][i]);
			fscanf(db, "%f", &cropTime[rrr][yyy][i]);
			fscanf(db, "%f", &RUEHI[rrr][yyy][i]);
			fscanf(db, "%f", &DelayP[rrr][yyy][i]);

			if(CoverCrop[rrr][yyy][i]<0) CoverCrop[rrr][yyy][i]=0;
			if(TreeAge[rrr][yyy][i]<0.0) TreeAge[rrr][yyy][i]=0.0;
		
		}
	}
	fclose(db);

	if(Transplant[rrr][yyy][1]<0) Transplant[rrr][yyy][1] = 0;

	m_GrowthReproductive = rate_reproduc[rrr][yyy][1];
	m_CropModel = Transplant[rrr][yyy][1];
	m_PsnEfficiency = Psn_efficiency[rrr][yyy][1];
	m_PsnMax = Psn_max[rrr][yyy][1];
	m_CropLAI = TreeAge[rrr][yyy][1];
	m_TreeCurrentAge = TreeCurrentAge[rrr][yyy][1];
	m_TreeLeafMax = TreeLeafMax[rrr][yyy][1];
	m_TreeLeafMin = TreeLeafMin[rrr][yyy][1];
	
	m_CropID = crop_order[rrr][yyy][1];
	m_CropHDay = harvest_day[rrr][yyy][1];
	m_CropHMonth = harvest_month[rrr][yyy][1];
	m_CropHYear = harvest_year[rrr][yyy][1];
	
	m_CropPDay = plant_day[rrr][yyy][1];
	m_CropPMonth = plant_month[rrr][yyy][1];
	m_CropResidue = crop_residue[rrr][yyy][1];
	m_CropYield = crop_yield[rrr][yyy][1];

	m_CoverCrop = CoverCrop[rrr][yyy][1];
	m_PerennialCrop = PerennialCrop[rrr][yyy][1];

	//if(crop_type[rrr][yyy][1]!=12) m_PerennialCrop = 0;

	m_CropType.SetCurSel(crop_type[rrr][yyy][1]);

	m_GrainFraction = GrainFraction[rrr][yyy][1];
	m_LeafFraction = LeafFraction[rrr][yyy][1];
	m_ShootFraction = ShootFraction[rrr][yyy][1];
	m_RootFraction = RootFraction[rrr][yyy][1];
	m_GrainCN = GrainCN[rrr][yyy][1];
	m_LeafCN = LeafCN[rrr][yyy][1];
	m_ShootCN = ShootCN[rrr][yyy][1];
	m_RootCN = RootCN[rrr][yyy][1];
	//m_CropCN = CropCN[rrr][yyy][1];
	m_CropTDD = TDD[rrr][yyy][1];
	m_CropWaterDemand = WaterDemand[rrr][yyy][1];
	m_RootShape=RootShape[rrr][yyy][1];
	m_LAImax = LAImax[rrr][yyy][1];
	m_FrostKill = FrostKill[rrr][yyy][1];
	m_AlfCHRMX = AlfCHRMX[rrr][yyy][1];
	m_ALFCDRMX = ALFCDRMX[rrr][yyy][1];
	m_ALFCTMX = ALFCTMX[rrr][yyy][1];
	m_ALFPDFMX = ALFPDFMX[rrr][yyy][1];
	m_Root1 = Root1[rrr][yyy][1];
	m_Root2 = Root2[rrr][yyy][1];
	if (m_Root1 < 0.0)m_Root1 = 0.4;
	if (m_Root2 < 0.0)m_Root2 = 0.007;
	m_AGResp1 = AGResp1[rrr][yyy][1];
	m_AGResp2 = AGResp2 [rrr] [yyy] [1] ;
	if (m_AGResp1 < 0.0)m_AGResp1 = 0.4;
	if (m_AGResp2 < 0.0)m_AGResp2 = 0.007;
	m_cropGRate=cropGRate[rrr][yyy][1];
	m_cropTime = cropTime[rrr][yyy][1];
	m_DelayP = DelayP[rrr][yyy][1];
	m_RUEHI = RUEHI[rrr][yyy][1];

	m_GrainFill=GrainFill[rrr][yyy][1];
	m_CropNfixation = Nfixation[rrr][yyy][1];
	m_OptT = OptT[rrr][yyy][1];
	m_Vascularity = Vascularity[rrr][yyy][1];
	m_CropLAI = TreeAge[rrr][yyy][1];
	m_TreeCurrentAge = TreeCurrentAge[rrr][yyy][1];
	m_TreeLeafMax = TreeLeafMax[rrr][yyy][1];
	m_TreeLeafMin = TreeLeafMin[rrr][yyy][1];

	float BCB = m_GrainFraction+m_LeafFraction+m_ShootFraction+m_RootFraction;
	if(BCB<0.99999||BCB>1.000001)
	{
		m_RootFraction = 1.0 - (m_GrainFraction+m_LeafFraction+m_ShootFraction);
		/*if(m_RootFraction<=0.0)
		{
			CString notee;
			notee.Format("Please re-define leaf or stem fraction");
			AfxMessageBox(notee);
			return;
		}*/
	}

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//float CropCN = 1.0 / (m_GrainFraction / m_GrainCN + m_ShootFraction /m_ShootCN + m_RootFraction /m_RootCN);
	//m_CropTotalN = TC/CropCN; 
		//crop_yield[rrr][yyy][1]/m_GrainCN + m_ShootYield/m_ShootCN + m_RootYield/m_RootCN;

	
	////////////////////////////////////////////////

#ifdef MANURE	
	//CString XFF;
	//FILE *xff;		
	/*XFF.Format("%s\\ManureCropNumber", INTER);		
	xff=fopen(XFF, "r");
	if(xff==NULL) note(0,XFF);
	fscanf(xff, "%d %d %d", &TotalManureFields, &ManureFieldOrder, &jd);
	fclose(xff);*/
	//m_CropType.SetCurSel(jd);
	//OnSelchangeCropType();
	//m_CropN = 1;
	//m_CropID = 1;
#endif
	//////////////////////////////////////////////////
	demo(rrr,yyy);
	
	//m_CropModel = IData.CropModel; 

	if (crop_type[rrr][yyy][1] == 10)
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(FALSE);
	}

/*	if(crop_type[rrr][yyy][1]==12)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_CropPMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_CropPDay);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_CropHMonth);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_CropHDay);
		Edt->EnableWindow(FALSE); 
	}
	
	if(m_CropModel == 0)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_SeedDensity);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_PsnEfficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_GrowthReproductive);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_GrowthVegetative);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_PsnMax);
		Edt->EnableWindow(FALSE); 		
	}
*/
	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}

BEGIN_EVENTSINK_MAP(SitePage4, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(SitePage4)
	//ON_EVENT(SitePage4, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void SitePage4::OnCropNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString DB;
	FILE *db;
	int rrr, yyy;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT4);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	if(m_CropID>0)
	{
		crop_type[rrr][yyy][m_CropID] = m_CropType.GetCurSel();
		plant_month[rrr][yyy][m_CropID] = m_CropPMonth;
		plant_day[rrr][yyy][m_CropID] = m_CropPDay;
		harvest_month[rrr][yyy][m_CropID] = m_CropHMonth;
		harvest_day[rrr][yyy][m_CropID] = m_CropHDay;
		rate_reproduc[rrr][yyy][m_CropID] = m_GrowthReproductive;
		Transplant[rrr][yyy][m_CropID] = m_CropModel;
		Psn_efficiency[rrr][yyy][m_CropID] = m_PsnEfficiency;
		Psn_max[rrr][yyy][m_CropID] = m_PsnMax;
		TreeAge[rrr][yyy][m_CropID] = m_CropLAI;
		TreeCurrentAge[rrr][yyy][m_CropID] = m_TreeCurrentAge;
		TreeLeafMax[rrr][yyy][m_CropID] = m_TreeLeafMax;
		TreeLeafMin[rrr][yyy][m_CropID] = m_TreeLeafMin;

		crop_residue[rrr][yyy][m_CropID] = m_CropResidue;
		crop_yield[rrr][yyy][m_CropID] = m_CropYield;
		harvest_year[rrr][yyy][m_CropID] = m_CropHYear;
		CoverCrop[rrr][yyy][m_CropID] = m_CoverCrop;
		PerennialCrop[rrr][yyy][m_CropID] = m_PerennialCrop;

		GrainFraction[rrr][yyy][m_CropID] = m_GrainFraction;
		LeafFraction[rrr][yyy][m_CropID] = m_LeafFraction;
		ShootFraction[rrr][yyy][m_CropID] = m_ShootFraction;
		RootFraction[rrr][yyy][m_CropID] = m_RootFraction;
		GrainCN[rrr][yyy][m_CropID] = m_GrainCN;
		LeafCN[rrr][yyy][m_CropID] = m_LeafCN;
		ShootCN[rrr][yyy][m_CropID] = m_ShootCN;
		RootCN[rrr][yyy][m_CropID] = m_RootCN;
		TDD[rrr][yyy][m_CropID] = m_CropTDD;
		WaterDemand[rrr][yyy][m_CropID] = m_CropWaterDemand;
		RootShape[rrr][yyy][m_CropID]=m_RootShape;
		LAImax[rrr][yyy][m_CropID] = m_LAImax;
		FrostKill[rrr][yyy][m_CropID] = m_FrostKill;
		AlfCHRMX[rrr][yyy][m_CropID] = m_AlfCHRMX;
		ALFCDRMX[rrr][yyy][m_CropID] = m_ALFCDRMX;
		ALFCTMX[rrr][yyy][m_CropID] = m_ALFCTMX;
		ALFPDFMX[rrr][yyy][m_CropID] = m_ALFPDFMX;
		Root1[rrr][yyy][m_CropID] = m_Root1;
		Root2[rrr][yyy][m_CropID] = m_Root2;
		AGResp1[rrr][yyy][m_CropID] = m_AGResp1;
		AGResp2[rrr][yyy][m_CropID] = m_AGResp2;
		cropGRate[rrr][yyy][m_CropID] = m_cropGRate;
		cropTime[rrr][yyy][m_CropID] = m_cropTime;
		RUEHI[rrr][yyy][m_CropID] = m_RUEHI;
		DelayP[rrr][yyy][m_CropID] = m_DelayP;

	    GrainFill[rrr][yyy][m_CropID]=m_GrainFill;
		Nfixation[rrr][yyy][m_CropID] = m_CropNfixation;
		OptT[rrr][yyy][m_CropID] = m_OptT;
		Vascularity[rrr][yyy][m_CropID] = m_Vascularity;
		Transplant[rrr][yyy][m_CropID] = m_CropModel;
	}

	/*DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d\n", m_CropN);

	for (int i = 1; i<=m_CropN;i++) 
	{
			fprintf(db, "%d\n", crop_order[rrr][yyy][i]);
			fprintf(db, "%d\n", crop_type[rrr][yyy][i]);
			fprintf(db, "%d %d\n", plant_month[rrr][yyy][i], plant_day[rrr][yyy][i]);
			fprintf(db, "%d %d\n", harvest_month[rrr][yyy][i], harvest_day[rrr][yyy][i]);
			fprintf(db, "%d\n", harvest_year[rrr][yyy][i]);
			fprintf(db, "%f\n", crop_residue[rrr][yyy][i]);
			fprintf(db, "%f\n", crop_yield[rrr][yyy][i]);
			fprintf(db, "%f %f %f %f %f\n", rate_reproduc[rrr][yyy][i], rate_vegetat[rrr][yyy][i], Psn_efficiency[rrr][yyy][i], 
				Psn_max[rrr][yyy][i], ini_biomass[rrr][yyy][i]);

	}
	fclose(db);*/

	if (m_CropN==0) return;
	if (m_CropID<m_CropN) m_CropID++;
	else return;

	
	m_CropType.SetCurSel(crop_type[rrr][yyy][m_CropID]);
	m_CropPMonth = plant_month[rrr][yyy][m_CropID];
	m_CropPDay = plant_day[rrr][yyy][m_CropID];
	m_CropHMonth = harvest_month[rrr][yyy][m_CropID];
	m_CropHDay = harvest_day[rrr][yyy][m_CropID];
	m_GrowthReproductive = rate_reproduc[rrr][yyy][m_CropID];
	m_CropModel = Transplant[rrr][yyy][m_CropID];
	m_PsnEfficiency = Psn_efficiency[rrr][yyy][m_CropID];
	m_PsnMax = Psn_max[rrr][yyy][m_CropID];
	m_CropLAI = TreeAge[rrr][yyy][m_CropID];
	m_TreeCurrentAge = TreeCurrentAge[rrr][yyy][m_CropID];
	m_TreeLeafMax = TreeLeafMax[rrr][yyy][m_CropID];
	m_TreeLeafMin = TreeLeafMin[rrr][yyy][m_CropID];

	m_CropResidue = crop_residue[rrr][yyy][m_CropID];
	m_CropYield = crop_yield[rrr][yyy][m_CropID];
	m_CropHYear = harvest_year[rrr][yyy][m_CropID];
	m_CoverCrop = CoverCrop[rrr][yyy][m_CropID];
	
	m_PerennialCrop = PerennialCrop[rrr][yyy][m_CropID];

	m_GrainFraction = GrainFraction[rrr][yyy][m_CropID];
	m_LeafFraction = LeafFraction[rrr][yyy][m_CropID];
	m_ShootFraction = ShootFraction[rrr][yyy][m_CropID];
	m_RootFraction = RootFraction[rrr][yyy][m_CropID];
	m_GrainCN = GrainCN[rrr][yyy][m_CropID];
	m_LeafCN = LeafCN[rrr][yyy][m_CropID];
	m_ShootCN = ShootCN[rrr][yyy][m_CropID];
	m_RootCN = RootCN[rrr][yyy][m_CropID];
	//m_CropCN = CropCN[rrr][yyy][m_CropID];
	m_CropTDD = TDD[rrr][yyy][m_CropID];
	m_CropWaterDemand = WaterDemand[rrr][yyy][m_CropID];
	m_RootShape = RootShape[rrr][yyy][m_CropID];
	m_LAImax = LAImax[rrr][yyy][m_CropID];
	m_FrostKill = FrostKill[rrr][yyy][m_CropID];
	m_AlfCHRMX = AlfCHRMX[rrr][yyy][m_CropID];
	m_ALFCDRMX = ALFCDRMX[rrr][yyy][m_CropID];
	m_ALFCTMX = ALFCTMX[rrr][yyy][m_CropID];
	m_ALFPDFMX = ALFPDFMX[rrr][yyy][m_CropID];
	m_Root1 = Root1[rrr][yyy][m_CropID];
	m_Root2 = Root2[rrr][yyy][m_CropID];
	m_AGResp1 = AGResp1[rrr][yyy][m_CropID];
	m_AGResp2 = AGResp2[rrr][yyy][m_CropID];
	m_cropGRate = cropGRate[rrr][yyy][m_CropID];
	m_cropTime = cropTime[rrr][yyy][m_CropID];
	m_RUEHI = RUEHI[rrr][yyy][m_CropID];
	m_DelayP = DelayP[rrr][yyy][m_CropID];
	m_GrainFill = GrainFill[rrr][yyy][m_CropID];
	m_CropNfixation = Nfixation[rrr][yyy][m_CropID];
	m_OptT = OptT[rrr][yyy][m_CropID];
	m_Vascularity = Vascularity[rrr][yyy][m_CropID];//this is rooting depth

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;
	if(m_GrainCN==0.0||m_ShootCN==0.0||m_RootCN==0.0) m_CropTotalN = 0.0;
	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;

	//float CropCN = 1.0 / (m_GrainFraction / m_GrainCN + m_ShootFraction /m_ShootCN + m_RootFraction /m_RootCN);
	//m_CropTotalN = TC/CropCN; 
	if (m_CropType.SetCurSel(crop_type[rrr][yyy][m_CropID]) == 10)
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(TRUE);


	}
	else
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(FALSE);


	}
	
	UpdateData(FALSE);
}

void SitePage4::OnCropLast() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString DB;
	FILE *db;
	int rrr, yyy;
	DB.Format("%s\\Inter\\CR.txt", OUTPUT);
	//DB.Format("%s\\CR.txt", FCT4);
	db=fopen(DB, "r");
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	if(m_CropID>0)
	{
		crop_type[rrr][yyy][m_CropID] = m_CropType.GetCurSel();
		plant_month[rrr][yyy][m_CropID] = m_CropPMonth;
		plant_day[rrr][yyy][m_CropID] = m_CropPDay;
		harvest_month[rrr][yyy][m_CropID] = m_CropHMonth;
		harvest_day[rrr][yyy][m_CropID] = m_CropHDay;
		rate_reproduc[rrr][yyy][m_CropID] = m_GrowthReproductive;
		Transplant[rrr][yyy][m_CropID] = m_CropModel;
		Psn_efficiency[rrr][yyy][m_CropID] = m_PsnEfficiency;
		Psn_max[rrr][yyy][m_CropID] = m_PsnMax;
		TreeAge[rrr][yyy][m_CropID] = m_CropLAI;
		TreeCurrentAge[rrr][yyy][m_CropID] = m_TreeCurrentAge;
		TreeLeafMax[rrr][yyy][m_CropID] = m_TreeLeafMax;
		TreeLeafMin[rrr][yyy][m_CropID] = m_TreeLeafMin;

		crop_residue[rrr][yyy][m_CropID] = m_CropResidue;
		crop_yield[rrr][yyy][m_CropID] = m_CropYield;
		harvest_year[rrr][yyy][m_CropID] = m_CropHYear;
		CoverCrop[rrr][yyy][m_CropID] = m_CoverCrop;
		PerennialCrop[rrr][yyy][m_CropID] = m_PerennialCrop;

		GrainFraction[rrr][yyy][m_CropID] = m_GrainFraction;
		LeafFraction[rrr][yyy][m_CropID] = m_LeafFraction;
		ShootFraction[rrr][yyy][m_CropID] = m_ShootFraction;
		RootFraction[rrr][yyy][m_CropID] = m_RootFraction;
		GrainCN[rrr][yyy][m_CropID] = m_GrainCN;
		LeafCN[rrr][yyy][m_CropID] = m_LeafCN;
		ShootCN[rrr][yyy][m_CropID] = m_ShootCN;
		RootCN[rrr][yyy][m_CropID] = m_RootCN;
		TDD[rrr][yyy][m_CropID] = m_CropTDD;
		WaterDemand[rrr][yyy][m_CropID] = m_CropWaterDemand;
		RootShape[rrr][yyy][m_CropID]=m_RootShape;
		LAImax[rrr][yyy][m_CropID] = m_LAImax;
		FrostKill[rrr][yyy][m_CropID] = m_FrostKill;
		AlfCHRMX[rrr][yyy][m_CropID] = m_AlfCHRMX;
		ALFCDRMX[rrr][yyy][m_CropID] = m_ALFCDRMX;
		ALFCTMX[rrr][yyy][m_CropID] = m_ALFCTMX;
		ALFPDFMX[rrr][yyy][m_CropID] = m_ALFPDFMX;
		Root1[rrr][yyy][m_CropID] = m_Root1;
		Root2[rrr][yyy][m_CropID] = m_Root2;
		AGResp1[rrr][yyy][m_CropID] = m_AGResp1;
		AGResp2[rrr][yyy][m_CropID] = m_AGResp2;
		cropGRate[rrr][yyy][m_CropID] = m_cropGRate;
		cropTime[rrr][yyy][m_CropID] = m_cropTime;
		RUEHI[rrr][yyy][m_CropID] = m_RUEHI;
		DelayP[rrr][yyy][m_CropID] = m_DelayP;

	    GrainFill[rrr][yyy][m_CropID]=m_GrainFill;
		Nfixation[rrr][yyy][m_CropID] = m_CropNfixation;
		OptT[rrr][yyy][m_CropID] = m_OptT;
		Vascularity[rrr][yyy][m_CropID] = m_Vascularity;
	}

	/*DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", rrr, yyy);
	db=fopen(DB, "w");
	if(db==NULL)
	{
		CString note;
		note.Format("Can not create file %s", DB);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(db, "%d\n", m_CropN);

	for (int i = 1; i<=m_CropN;i++) 
	{
			fprintf(db, "%d\n", crop_order[rrr][yyy][i]);
			fprintf(db, "%d\n", crop_type[rrr][yyy][i]);
			fprintf(db, "%d %d\n", plant_month[rrr][yyy][i], plant_day[rrr][yyy][i]);
			fprintf(db, "%d %d\n", harvest_month[rrr][yyy][i], harvest_day[rrr][yyy][i]);
			fprintf(db, "%d\n", harvest_year[rrr][yyy][i]);
			fprintf(db, "%f\n", crop_residue[rrr][yyy][i]);
			fprintf(db, "%f\n", crop_yield[rrr][yyy][i]);
			fprintf(db, "%f %f %f %f %f\n", rate_reproduc[rrr][yyy][i], rate_vegetat[rrr][yyy][i], Psn_efficiency[rrr][yyy][i], 
				Psn_max[rrr][yyy][i], ini_biomass[rrr][yyy][i]);

	}
	fclose(db);*/

	if (m_CropN==0) return;
	if (m_CropID>1) m_CropID--;
	else if (m_CropID==0) m_CropID=1;

	m_CropType.SetCurSel(crop_type[rrr][yyy][m_CropID]);
	m_CropPMonth = plant_month[rrr][yyy][m_CropID];
	m_CropPDay = plant_day[rrr][yyy][m_CropID];
	m_CropHMonth = harvest_month[rrr][yyy][m_CropID];
	m_CropHDay = harvest_day[rrr][yyy][m_CropID];
	m_GrowthReproductive = rate_reproduc[rrr][yyy][m_CropID];
	m_CropModel = Transplant[rrr][yyy][m_CropID];
	m_PsnEfficiency = Psn_efficiency[rrr][yyy][m_CropID];
	m_PsnMax = Psn_max[rrr][yyy][m_CropID];
	m_CropLAI = TreeAge[rrr][yyy][m_CropID];
	m_TreeCurrentAge = TreeCurrentAge[rrr][yyy][m_CropID];
	m_TreeLeafMax = TreeLeafMax[rrr][yyy][m_CropID];
	m_TreeLeafMin = TreeLeafMin[rrr][yyy][m_CropID];

	m_CropResidue = crop_residue[rrr][yyy][m_CropID];
	m_CropYield = crop_yield[rrr][yyy][m_CropID];
	m_CropHYear = harvest_year[rrr][yyy][m_CropID];
	m_CoverCrop = CoverCrop[rrr][yyy][m_CropID];

	m_PerennialCrop = PerennialCrop[rrr][yyy][m_CropID];
	m_GrainFraction = GrainFraction[rrr][yyy][m_CropID];
	m_LeafFraction = LeafFraction[rrr][yyy][m_CropID];
	m_ShootFraction = ShootFraction[rrr][yyy][m_CropID];
	m_RootFraction = RootFraction[rrr][yyy][m_CropID];
	m_GrainCN = GrainCN[rrr][yyy][m_CropID];
	m_LeafCN = LeafCN[rrr][yyy][m_CropID];
	m_ShootCN = ShootCN[rrr][yyy][m_CropID];
	m_RootCN = RootCN[rrr][yyy][m_CropID];
	//m_CropCN = CropCN[rrr][yyy][m_CropID];
	m_CropTDD = TDD[rrr][yyy][m_CropID];
	m_CropWaterDemand = WaterDemand[rrr][yyy][m_CropID];
	m_RootShape = RootShape[rrr][yyy][m_CropID];
	m_LAImax = LAImax[rrr][yyy][m_CropID];
	m_FrostKill = FrostKill[rrr][yyy][m_CropID];
	m_AlfCHRMX = AlfCHRMX[rrr][yyy][m_CropID];
	m_ALFCDRMX = ALFCDRMX[rrr][yyy][m_CropID];
	m_ALFCTMX = ALFCTMX[rrr][yyy][m_CropID];
	m_Root1 = Root1[rrr][yyy][m_CropID];
	m_Root2 = Root2[rrr][yyy][m_CropID];
	m_AGResp1 = AGResp1[rrr][yyy][m_CropID];
	m_AGResp2 = AGResp2[rrr][yyy][m_CropID];
	m_cropGRate = cropGRate[rrr][yyy][m_CropID];
	m_cropTime = cropTime[rrr][yyy][m_CropID];
	m_RUEHI = RUEHI[rrr][yyy][m_CropID];
	m_DelayP = DelayP[rrr][yyy][m_CropID];
	m_ALFPDFMX = ALFPDFMX[rrr][yyy][m_CropID];
	m_GrainFill = GrainFill[rrr][yyy][m_CropID];
	m_CropNfixation = Nfixation[rrr][yyy][m_CropID];
	m_OptT = OptT[rrr][yyy][m_CropID];
	m_Vascularity = Vascularity[rrr][yyy][m_CropID];

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;
	if(m_GrainCN==0.0||m_ShootCN==0.0||m_RootCN==0.0) m_CropTotalN = 0.0;
	else 
	{
		m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
		if(m_CropTotalN<0.0) m_CropTotalN = 0.0;

		//float CropCN = 1.0 / (m_GrainFraction / m_GrainCN + m_ShootFraction /m_ShootCN + m_RootFraction /m_RootCN);
		//m_CropTotalN = TC/CropCN; 
	}
	if (m_CropType.SetCurSel(crop_type[rrr][yyy][m_CropID]) == 10)
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(TRUE);


	}
	else
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(FALSE);


	}
	UpdateData(FALSE);
	//OnKillfocusCropID();
}

void SitePage4::OnCropAccept() 
{
	// Crop parameter
	UpdateData(TRUE);

	int CROPID=m_CropType.GetCurSel();

	if(m_CropYield<=0.0&&CROPID>0)
	{
		CString notee;
		notee.Format("Grain biomass must > 0");
		AfxMessageBox(notee);
		return;
	}

	if(CROPID>0&&(m_GrainFraction<=0.0||m_GrainFraction>=1.0))
	{
		CString notee;
		notee.Format("Grain fraction must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	if(CROPID>0&&(m_ShootFraction<=0.0||m_ShootFraction>=1.0))
	{
		CString notee;
		notee.Format("Leaf+stem fraction must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	if(CROPID>0&&(m_RootFraction<=0.0||m_RootFraction>=1.0))
	{
		CString notee;
		notee.Format("Root fraction must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	if(CROPID>0&&(m_CropResidue<0.0||m_CropResidue>1.0))
	{
		CString notee;
		notee.Format("Fraction of leaves and stems left in the field after harvest must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	if(CROPID>0 && m_Vascularity<0.1)
	{
		CString notee;
		notee.Format("Maximum Root Length must be at least 0.1 m");
		AfxMessageBox(notee);
		return;
	}

	if(CROPID>0&&(m_OptT<5.0||m_OptT>35.0))
	{
		CString notee;
		notee.Format("Please confirm the optimum temperature for crop growth");
		AfxMessageBox(notee);
		return;
	}	

	CString DB;
	FILE *db;
	int rrr, yyy;

	DB.Format("%s\\CR.txt", INTER);

	db=fopen(DB, "r");
	if(db==NULL) note(0,DB);
	fscanf(db, "%d %d", &rrr, &yyy);
	fclose(db);

	if(m_CropID>0)
	{
		crop_type[rrr][yyy][m_CropID] = m_CropType.GetCurSel();
		plant_month[rrr][yyy][m_CropID] = m_CropPMonth;
		plant_day[rrr][yyy][m_CropID] = m_CropPDay;
		harvest_month[rrr][yyy][m_CropID] = m_CropHMonth;
		harvest_day[rrr][yyy][m_CropID] = m_CropHDay;
		rate_reproduc[rrr][yyy][m_CropID] = m_GrowthReproductive;
		Transplant[rrr][yyy][m_CropID] = m_CropModel;
		Psn_efficiency[rrr][yyy][m_CropID] = m_PsnEfficiency;
		Psn_max[rrr][yyy][m_CropID] = m_PsnMax;
		TreeAge[rrr][yyy][m_CropID] = m_CropLAI;
		TreeCurrentAge[rrr][yyy][m_CropID] = m_TreeCurrentAge;
		TreeLeafMax[rrr][yyy][m_CropID] = m_TreeLeafMax;
		TreeLeafMin[rrr][yyy][m_CropID] = m_TreeLeafMin;

		crop_residue[rrr][yyy][m_CropID] = m_CropResidue;
		crop_yield[rrr][yyy][m_CropID] = m_CropYield;
		harvest_year[rrr][yyy][m_CropID] = m_CropHYear;
		CoverCrop[rrr][yyy][m_CropID] = m_CoverCrop;

		PerennialCrop[rrr][yyy][m_CropID] = m_PerennialCrop;
		Vascularity[rrr][yyy][m_CropID] = m_Vascularity;

		GrainFraction[rrr][yyy][m_CropID] = m_GrainFraction;
		LeafFraction[rrr][yyy][m_CropID] = m_LeafFraction;
		ShootFraction[rrr][yyy][m_CropID] = m_ShootFraction;
		RootFraction[rrr][yyy][m_CropID] = m_RootFraction;
		GrainCN[rrr][yyy][m_CropID] = m_GrainCN;
		LeafCN[rrr][yyy][m_CropID] = m_LeafCN;
		ShootCN[rrr][yyy][m_CropID] = m_ShootCN;
		RootCN[rrr][yyy][m_CropID] = m_RootCN;
		TDD[rrr][yyy][m_CropID] = m_CropTDD;
		WaterDemand[rrr][yyy][m_CropID] = m_CropWaterDemand;
		RootShape[rrr][yyy][m_CropID]=m_RootShape;
		LAImax[rrr][yyy][m_CropID] = m_LAImax;
		FrostKill[rrr][yyy][m_CropID] = m_FrostKill;
		AlfCHRMX[rrr][yyy][m_CropID] = m_AlfCHRMX;
		ALFCDRMX[rrr][yyy][m_CropID] = m_ALFCDRMX;
		ALFCTMX[rrr][yyy][m_CropID] = m_ALFCTMX;
		ALFPDFMX[rrr][yyy][m_CropID] = m_ALFPDFMX;
		Root1[rrr][yyy][m_CropID] = m_Root1;
		Root2[rrr][yyy][m_CropID] = m_Root2;
		AGResp1[rrr][yyy][m_CropID] = m_AGResp1;
		AGResp2[rrr][yyy][m_CropID] = m_AGResp2;
		cropGRate[rrr][yyy][m_CropID] = m_cropGRate;
		cropTime[rrr][yyy][m_CropID] = m_cropTime;
		RUEHI[rrr][yyy][m_CropID] = m_RUEHI;
		DelayP[rrr][yyy][m_CropID] = m_DelayP;
	    GrainFill[rrr][yyy][m_CropID]=m_GrainFill;

		Nfixation[rrr][yyy][m_CropID] = m_CropNfixation;
		OptT[rrr][yyy][m_CropID] = m_OptT;
		Vascularity[rrr][yyy][m_CropID] = m_Vascularity;
		TreeAge[rrr][yyy][m_CropID] = m_CropLAI;
		TreeCurrentAge[rrr][yyy][m_CropID] = m_TreeCurrentAge;
		TreeLeafMax[rrr][yyy][m_CropID] = m_TreeLeafMax;
		TreeLeafMin[rrr][yyy][m_CropID] = m_TreeLeafMin;
	}
//#ifdef MANURE
//	DB.Format("%s\\CropRotation_%d_%d.txt", ManuDir, rrr, yyy);
//#else
	//DB.Format("%s\\Inter\\CropRotation_%d_%d.txt", OUTPUT, rrr, yyy);
	DB.Format("%s\\CropRotation_%d_%d.txt", FCT4, rrr, yyy);
//#endif
	
	db=fopen(DB, "w");
	if(db==NULL) note(1,DB);
	
	fprintf(db, "%d\n", m_CropN);

	for (int i = 1; i<=m_CropN;i++) 
	{
			fprintf(db, "%d\n", i);
			fprintf(db, "%d\n", crop_type[rrr][yyy][i]);
			fprintf(db, "%d %d\n", plant_month[rrr][yyy][i], plant_day[rrr][yyy][i]);
			fprintf(db, "%d %d\n", harvest_month[rrr][yyy][i], harvest_day[rrr][yyy][i]);
			fprintf(db, "%d\n", harvest_year[rrr][yyy][i]);
			fprintf(db, "%f\n", crop_residue[rrr][yyy][i]);
			fprintf(db, "%f\n", crop_yield[rrr][yyy][i]);
			fprintf(db, "%f %d %f %f %f\n", rate_reproduc[rrr][yyy][i], Transplant[rrr][yyy][i], Psn_efficiency[rrr][yyy][i], 
				Psn_max[rrr][yyy][i], TreeAge[rrr][yyy][i]);
			fprintf(db, "%d\n", CoverCrop[rrr][yyy][i]);
			fprintf(db, "%d\n", PerennialCrop[rrr][yyy][i]);

			fprintf(db, "%f\n", GrainFraction[rrr][yyy][i]); 
			fprintf(db, "%f\n", LeafFraction[rrr][yyy][i]);
			fprintf(db, "%f\n", ShootFraction[rrr][yyy][i]);
			fprintf(db, "%f\n", RootFraction[rrr][yyy][i]);
			fprintf(db, "%f\n", GrainCN[rrr][yyy][i]);
			fprintf(db, "%f\n", LeafCN[rrr][yyy][i]); 
			fprintf(db, "%f\n", ShootCN[rrr][yyy][i]); 
			fprintf(db, "%f\n", RootCN[rrr][yyy][i]); 
			fprintf(db, "%f\n", TDD[rrr][yyy][i]); 
			fprintf(db, "%f\n", WaterDemand[rrr][yyy][i]);
			fprintf(db, "%f\n", OptT[rrr][yyy][i]); 
			fprintf(db, "%f\n", Nfixation[rrr][yyy][i]);
			fprintf(db, "%f\n", Vascularity[rrr][yyy][i]);	
			fprintf(db, "%f\n", TreeAge[rrr][yyy][i]);
			fprintf(db, "%f\n", TreeCurrentAge[rrr][yyy][i]);
			fprintf(db, "%f\n", TreeLeafMax[rrr][yyy][i]);
			fprintf(db, "%f\n", TreeLeafMin[rrr][yyy][i]);
			fprintf(db, "%d\n", RootShape[rrr][yyy][i]);
			fprintf(db, "%f\n", GrainFill[rrr][yyy][i]);
			fprintf(db, "%f\n", LAImax[rrr][yyy][i]);
			fprintf(db, "%f\n", FrostKill[rrr][yyy][i]);
			fprintf(db, "%f\n", AlfCHRMX[rrr][yyy][i]);
			fprintf(db, "%f\n", ALFCDRMX[rrr][yyy][i]);
			fprintf(db, "%f\n", ALFCTMX[rrr][yyy][i]);
			fprintf(db, "%f\n", ALFPDFMX[rrr][yyy][i]);
			fprintf(db, "%f\n", Root1[rrr][yyy][i]);
			fprintf(db, "%f\n", Root2[rrr][yyy][i]);
			fprintf(db, "%f\n", AGResp1[rrr][yyy][i]);
			fprintf(db, "%f\n", AGResp2[rrr][yyy][i]);
			fprintf(db, "%f\n", cropGRate[rrr][yyy][i]);
			fprintf(db, "%f\n", cropTime[rrr][yyy][i]);
			fprintf(db, "%f\n", RUEHI[rrr][yyy][i]);
			fprintf(db, "%f\n", DelayP[rrr][yyy][i]);

	}
	
	fclose(db);

/*	CString CM;
	FILE *cm;	
	CM.Format("%s\\Inter\\CropModel", OUTPUT);
	cm=fopen(CM, "w");
	if(cm==NULL) note(1, CM);
	else
	{
		fprintf(cm, "%d\n", m_CropModel);
		fclose(cm);
	}
*/
	/////////////////////////////////////////////////////////////////////////////////////////////
	int WinterCropFlag, LeftDays;
	char fname[255];
	FILE *fp;
    
	sprintf(fname, "%s\\cyc-%d_%d", FCT4,rrr, yyy);
	fp=fopen(fname, "w");

	if (m_CropN==0) //no crop
	{
		fprintf(fp, "%d\n", 0);
        fprintf(fp, "%d  %s  %d  %d  %f  %d\n", 0, "None", 0, 0, 0.0, 1);
		fprintf(fp, "%d  %d  %f  %f  %d\n", 0, 0, 0.0, 0.0, 999);
		fprintf(fp, "%f  %d  %f  %f  %f\n", 0.0, 0, 0.0, 0.0, 0.0);
		fprintf(fp, "%d", 0);
		//fprintf(fp, "%d", 0);

		// CropCode, WinterCropFlag, WinterCropLeftDays, OptimumYield, HarvestYear;
		  // PalntingJday, GrowingDays, ResidueIncorporation, MaxNDemand, EndCropFlag;
		  // IniCropBiomass, GRvege, GRreprod, PsnEfficiency, PsnMax 
		//cover_crp
	}
	else
	{
		fprintf(fp, "%d\n", m_CropN);
		for (int i = 1;i<=m_CropN;i++) 
		{
			if(crop_type[rrr][yyy][i]>=0)
			{
				int SeedDay = JulianDay(plant_month[rrr][yyy][i], plant_day[rrr][yyy][i]);
				int HarvDay = JulianDay(harvest_month[rrr][yyy][i], harvest_day[rrr][yyy][i]);
				int GrowDays = HarvDay - SeedDay;

				//if (harvest_year[rrr][yyy][i] > 1) GrowDays = 365 - SeedDay + HarvDay + (harvest_year[rrr][yyy][i] - 2) * 365;

				/////////////
				if(harvest_year[rrr][yyy][i]==1)
				{
					GrowDays = HarvDay - SeedDay;
					WinterCropFlag = 0;
					LeftDays = 0;
				}
				else
				{
					GrowDays = 365 - SeedDay + HarvDay + (harvest_year[rrr][yyy][i] - 2) * 365;
					WinterCropFlag = yyy-1;
					if(yyy==1) LeftDays = GrowDays;
					else LeftDays = GrowDays - (365*yyy - SeedDay);
				}

				/////////////
				FILE *fpp;
				char  VEGE[80], notee[160], Crop_Name[100];
				int jd, wwww=111;
				float jf, grain, plantcn;

				if(i==m_CropN) wwww = 999;

				//int CropType = crop_type[rrr][yyy][i];

				///////////////////////////////////////////////////////////////////////////////////////////
				int v_CropID[95], v_Perennial[95];
				float v_max_biomass_C[95], v_grain_fraction[95], v_leaf_fraction[95], v_leafstem_fraction[95], v_root_fraction[95];
				float v_GrainCN[95], v_LeafCN[95], v_ShootCN[95], v_RootCN[95], v_TreeAge[95];
				float v_WaterDemand[95], v_OptimumT[95], v_TDD[95], v_Nfixation[95], v_Vascularity[95];
				float v_Root1[95], v_Root2[95], v_AGResp1[95], v_AGResp2[95];//new Root Respiration
				float v_Kext1[95],v_Kext2[95], v_CMaxH[95];
				float v_cropGRate[95], v_cropTime[95], v_RUEHI[95], v_DelayP[95];//new controls for crops //theo
				//CString v_CropName[95];
				char v_CropName[95][100]={"NONE","NONE"};

				ReadCropPara1(v_CropID, v_CropName, v_max_biomass_C, v_grain_fraction, v_leaf_fraction,
				  v_leafstem_fraction, v_root_fraction, v_GrainCN, 
				  v_LeafCN, v_ShootCN, v_RootCN, v_WaterDemand, v_OptimumT, 
				  v_TDD, v_Nfixation, v_Vascularity, v_Perennial, v_TreeAge,v_Root1,v_Root2,v_AGResp1,v_AGResp2,v_Kext1,v_Kext2,v_CMaxH, v_cropGRate, v_cropTime, v_RUEHI, v_DelayP);

				///////////////////////////////////////////////////////////////////////////////////////////
				
				/*m_CropYield = v_max_biomass_C[CropType] * v_grain_fraction[CropType];//kg C/ha
				m_ShootYield = v_max_biomass_C[CropType] * v_leafstem_fraction[CropType];
				m_RootYield = v_max_biomass_C[CropType] * v_root_fraction[CropType];
				m_GrainFraction = v_grain_fraction[CropType];
				m_ShootFraction = v_leafstem_fraction[CropType];
				m_RootFraction = v_root_fraction[CropType];*/
				
				sprintf(Crop_Name, "%s", v_CropName[crop_type[rrr][yyy][i]]);

				////////////////////////////////////////////////////////////////////////////////////////////

				float YieldC = crop_yield[rrr][yyy][i];
    			float PlantC = YieldC / GrainFraction[rrr][yyy][i];//grain;
				float PlantCN = 1.0 / (GrainFraction[rrr][yyy][i]/GrainCN[rrr][yyy][i] + 
					LeafFraction[rrr][yyy][i]/LeafCN[rrr][yyy][i] +
					ShootFraction[rrr][yyy][i]/ShootCN[rrr][yyy][i] + 
					RootFraction[rrr][yyy][i]/RootCN[rrr][yyy][i]);
				float MaxPlantN = PlantC / PlantCN;

				fprintf(fp, "%d  %s  %d  %d  %f  %d\n", crop_type[rrr][yyy][i], Crop_Name, WinterCropFlag, LeftDays, crop_yield[rrr][yyy][i], harvest_year[rrr][yyy][i]);
				fprintf(fp, "%d  %d  %f  %f  %d\n", SeedDay, GrowDays, crop_residue[rrr][yyy][i], MaxPlantN, wwww);
				fprintf(fp, "%f  %d  %f  %f  %f\n", TreeAge[rrr][yyy][i], Transplant[rrr][yyy][i], 
					rate_reproduc[rrr][yyy][i], Psn_efficiency[rrr][yyy][i],  Psn_max[rrr][yyy][i]);
				fprintf(fp, "%d\n", CoverCrop[rrr][yyy][i]);
				fprintf(fp, "%d\n", PerennialCrop[rrr][yyy][i]);
				fprintf(fp, "%f\n", GrainFraction[rrr][yyy][i]); 
				fprintf(fp, "%f\n", LeafFraction[rrr][yyy][i]);
				fprintf(fp, "%f\n", ShootFraction[rrr][yyy][i]);
				fprintf(fp, "%f\n", RootFraction[rrr][yyy][i]);
				fprintf(fp, "%f\n", GrainCN[rrr][yyy][i]);
				fprintf(fp, "%f\n", LeafCN[rrr][yyy][i]); 
				fprintf(fp, "%f\n", ShootCN[rrr][yyy][i]); 
				fprintf(fp, "%f\n", RootCN[rrr][yyy][i]); 
				fprintf(fp, "%f\n", TDD[rrr][yyy][i]); 
				fprintf(fp, "%f\n", WaterDemand[rrr][yyy][i]);
				fprintf(fp, "%f\n", OptT[rrr][yyy][i]); 
				fprintf(fp, "%f\n", Nfixation[rrr][yyy][i]);
				fprintf(fp, "%f\n", Vascularity[rrr][yyy][i]);
				fprintf(fp, "%f\n", TreeAge[rrr][yyy][i]);
				fprintf(fp, "%f\n", TreeCurrentAge[rrr][yyy][i]);
				fprintf(fp, "%f\n", TreeLeafMax[rrr][yyy][i]);
				fprintf(fp, "%f\n", TreeLeafMin[rrr][yyy][i]);
				fprintf(fp, "%d\n", RootShape[rrr][yyy][i]);
			    fprintf(fp, "%f\n", GrainFill[rrr][yyy][i]);
				fprintf(fp, "%f\n", LAImax[rrr][yyy][i]);
				fprintf(fp, "%f\n", FrostKill[rrr][yyy][i]);
				fprintf(fp, "%f\n", AlfCHRMX[rrr][yyy][i]);
				fprintf(fp, "%f\n", ALFCDRMX[rrr][yyy][i]);
				fprintf(fp, "%f\n", ALFCTMX[rrr][yyy][i]);
				fprintf(fp, "%f\n", ALFPDFMX[rrr][yyy][i]);
				fprintf(fp, "%f\n", Root1[rrr][yyy][i]);
				fprintf(fp, "%f\n", Root2[rrr][yyy][i]);
				fprintf(fp, "%f\n", AGResp1[rrr][yyy][i]);
				fprintf(fp, "%f\n", AGResp2[rrr][yyy][i]);
				fprintf(fp, "%f\n", cropGRate[rrr][yyy][i]);
				fprintf(fp, "%f\n", cropTime[rrr][yyy][i]);
				fprintf(fp, "%f\n", RUEHI[rrr][yyy][i]);
				fprintf(fp, "%f\n", DelayP[rrr][yyy][i]);
			
			}//end: if(crop_type[rrr][yyy][i]>=0)
			
		}//loop: m_CropN
    
		fclose (fp);
	}

	if(IData.Soil_landuse==6)
	{
		CString FLL;
		FILE *fll;
		FLL.Format("%s\\ForestMatureAge", INTER);
		fll=fopen(FLL, "w");
		if(fll==NULL) note(1, FLL);
		fprintf(fll, "%f", m_CropLAI);//Forest max age
		fclose(fll);
	}

	demo(rrr,yyy);
}


// Set Default values of crop based on the properties of the crop
void SitePage4::SetCropDefault(CropParameter *cp)
{
	int CT = m_CropType.GetCurSel();

	if(cp->Grain<0.05)//CT==4||CT==5||CT==10||CT==11||CT==12||CT==22||CT==32)
		cp->Yield = cp->Biomass_C * cp->Straw;//kg C/ha
	else 
		cp->Yield = cp->Biomass_C * cp->Grain;
    
    m_CropHYear  = 1;
	if (m_CropType.GetCurSel() == 0) 
	{	// No crop
        m_CropPMonth = 0;	//
        m_CropPDay   = 0;	//
        m_CropHMonth = 0;	//
        m_CropHDay   = 0;	//
        //m_CropHYear  = 1;	//
        m_CropResidue= 0;	//
        m_CropYield  = 0;	//
		m_GrowthReproductive = 0.0;
		m_GrowthVegetative= 0.0;
		m_PsnEfficiency= 0.0;
		m_PsnMax= 0.0;
		m_CropLAI= 0.0;
		m_CoverCrop = 0;

		m_PerennialCrop = 0;
		m_GrainFraction = 0;
		m_ShootFraction = 0;
		m_RootFraction = 0;
		m_GrainCN = 0;
		m_ShootCN = 0;
		m_RootCN = 0;
		//m_CropCN = CropCN[rrr][yyy][m_CropID];
		m_CropTDD = 0;
		m_CropWaterDemand = 0;
		m_RootShape=5;
	    m_GrainFill=0.5;
		m_CropNfixation = 0;
		m_OptT = 25.0;
		m_CropTotalN = 0;
		m_Vascularity = 1.5;
		m_LAImax = 2.5;
		m_FrostKill = -2.0;
		m_AlfCHRMX = 0.184;
		m_ALFCDRMX = 0.82; 
		m_ALFCTMX = -15.0;
		m_ALFPDFMX = 0.108;
		m_Root1=0.4;
		m_Root2=0.007;
		m_AGResp1 = 0.4;
		m_AGResp2 = 0.007;
		m_cropGRate = 0.3f;
		m_cropTime = 10.0f;
		m_RUEHI = 1.0f;
		m_DelayP = 1.0f;
		//m_MaxPlantN = 0;
		cp->Yield    = 0;
//        cp->LeftPerc = 0;
        cp->MaxPlantN= 0;
	}
    else 
	{
		m_CropYield = cp->Yield;
		m_GrowthReproductive = cp->GrowthReproductive;
		m_GrowthVegetative= cp->GrowthVegetative;
		m_PsnEfficiency= cp->PsnEfficiency;
		m_PsnMax= cp->PsnMax;
		m_CropLAI= cp->TreeAge;
		m_TreeCurrentAge = cp->TreeCurrentAge;
		m_TreeLeafMax = cp->TreeLeafMax;
		m_TreeLeafMin = cp->TreeLeafMin;

            // Dry weight --> C partition
        SetCropCN(cp);
    }

	UpdateData(FALSE);
}




void SitePage4::OnKillfocusCropYield() 
{
	UpdateData(TRUE);

	int CROPID=m_CropType.GetCurSel();

	if(m_CropYield<=0.0&&CROPID>0)
	{
		CString notee;
		notee.Format("Grain biomass must > 0");
		AfxMessageBox(notee);
		return;
	}

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//m_CropTotalN = CropTN(float TotC, float GraCN, float ShoCN, float RooCN, float GraFra, float ShoFra, float RooFra)
	UpdateData(FALSE);


}



void SitePage4::OnKillfocusCropPMonth() 
{
	UpdateData(TRUE);	
}

void SitePage4::OnKillfocusCropPDay() 
{
	UpdateData(TRUE);
}

void SitePage4::OnKillfocusCropResidue() 
{
	UpdateData(TRUE);	
}


BOOL SitePage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
		//Set plant list
	SetPlantList();

	m_CropID = 1;
	m_CropPMonth = 0;
	m_CropPDay = 0;
	m_CropHMonth = 0;
	m_CropHDay = 0;

		//Set crop parameter list
		//Set list column
	int i;
	char *title[]={"CropID","CropType","Planting","   ","Harvest",
		"   ","Mode","Residue","Yield"};//,"GRate R", "Grate V", "Psn E", "Psn M", "Ini biomass"};

	int  ItemNum=9;
	for (i=0;i<ItemNum;i++)
	{
		m_CropList.InsertColumn(i,title[i],LVCFMT_CENTER,65,-1);
	}

	if(IData.Soil_landuse==6)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_CropLAI);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeAge);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(ID_TreeCurrentAge);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeLeafMax);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeLeafMin);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeAge2);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeAge3);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_STATIC1);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_STATIC2);
		Edt->EnableWindow(TRUE); 
	}
	else
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_CropLAI);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeAge);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(ID_TreeCurrentAge);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeLeafMax);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeLeafMin);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeAge2);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_TreeAge3);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_STATIC1);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_STATIC2);
		Edt->EnableWindow(FALSE); 
	}
	//IData.db_YrCropType
	/*
	if (m_CropType.GetCurSel() == 10)
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(FALSE);
	}
	*/
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SitePage4::OnSelchangeCropType() 
{	
	UpdateData(TRUE);
	int CropType = m_CropType.GetCurSel();

	///////////////////////////////////////////////////////////////////////////////////////////
	int v_CropID[95], v_Perennial[95];
	float v_max_biomass_C[95], v_grain_fraction[95], v_leaf_fraction[95], v_leafstem_fraction[95], v_root_fraction[95];
	float v_GrainCN[95], v_LeafCN[95], v_ShootCN[95], v_RootCN[95], v_TreeAge[95];
	float v_WaterDemand[95], v_OptimumT[95], v_TDD[95], v_Nfixation[95], v_Vascularity[95];
	float v_Root1[95], v_Root2[95], v_AGResp1[95], v_AGResp2[95];//new Root Respiration
	float v_Kext1[95],v_Kext2[95], v_CMaxH[95];
	float v_cropGRate[95], v_cropTime[95], v_RUEHI[95], v_DelayP[95];//new controls for crops //theo
	char v_CropName[95][100]={"NONE","NONE"};

	ReadCropPara1(v_CropID, v_CropName, v_max_biomass_C, v_grain_fraction, v_leaf_fraction,
				  v_leafstem_fraction, v_root_fraction, v_GrainCN, 
				  v_LeafCN, v_ShootCN, v_RootCN, v_WaterDemand, v_OptimumT, 
				  v_TDD, v_Nfixation, v_Vascularity, v_Perennial, v_TreeAge,v_Root1,v_Root2,v_AGResp1,v_AGResp2,v_Kext1,v_Kext2,v_CMaxH, v_cropGRate, v_cropTime, v_RUEHI, v_DelayP);

	///////////////////////////////////////////////////////////////////////////////////////////
	
	m_CropYield = v_max_biomass_C[CropType] * v_grain_fraction[CropType];//kg C/ha
	m_LeafYield = v_max_biomass_C[CropType] * v_leaf_fraction[CropType];
	m_ShootYield = v_max_biomass_C[CropType] * v_leafstem_fraction[CropType];
	m_RootYield = v_max_biomass_C[CropType] * v_root_fraction[CropType];
	m_GrainFraction = v_grain_fraction[CropType];
	m_LeafFraction = v_leaf_fraction[CropType];
	m_ShootFraction = v_leafstem_fraction[CropType];
	m_RootFraction = v_root_fraction[CropType];

	m_PerennialCrop = v_Perennial[CropType];
	m_LeafCN = v_LeafCN[CropType];
	m_ShootCN = v_ShootCN[CropType];
	m_RootCN = v_RootCN[CropType];
	m_GrainCN = v_GrainCN[CropType];
	m_CropWaterDemand = v_WaterDemand[CropType];
	m_RootShape=5;
	m_LAImax = 2.5;
	m_FrostKill = -2.0;
	m_AlfCHRMX = 0.0;
	m_ALFCDRMX = 0.0;
	m_ALFCTMX = 0.0;
	m_ALFPDFMX = 0.0;
	m_Root1 = v_Root1[CropType];
	m_Root2 = v_Root2[CropType];
	m_AGResp1 = v_AGResp1[CropType];
	m_AGResp2 = v_AGResp2[CropType];
	m_cropGRate = v_cropGRate[CropType];
	m_cropTime = v_cropTime[CropType];
	m_RUEHI = v_RUEHI[CropType];
	m_DelayP = v_DelayP[CropType];
	m_GrainFill=0.5;
	m_CropTDD = v_TDD[CropType];
	m_CropNfixation = v_Nfixation[CropType];
	m_Vascularity = v_Vascularity[CropType];//rooting depth is vascularity
	m_OptT = v_OptimumT[CropType];
	m_CropLAI = v_TreeAge[CropType];
	
    float PlantC = v_max_biomass_C[CropType];
	float PlantCN = 1.0 / (v_grain_fraction[CropType]/v_GrainCN[CropType] + v_leaf_fraction[CropType]/v_LeafCN[CropType] + v_leafstem_fraction[CropType]/v_ShootCN[CropType] + v_root_fraction[CropType]/v_RootCN[CropType]);
	float MaxPlantN = v_max_biomass_C[CropType] / PlantCN;
	m_CropTotalN = MaxPlantN;
	/*
	if (m_CropType.GetCurSel() == 3)//soybean
	{
	PlantCN = 1.0 / (v_grain_fraction[CropType] / v_GrainCN[CropType] + v_grain_fraction[CropType]*.5 / v_GrainCN[CropType] + v_leaf_fraction[CropType] / v_LeafCN[CropType] + v_leafstem_fraction[CropType] / v_ShootCN[CropType] + v_root_fraction[CropType] / v_RootCN[CropType]);
		MaxPlantN = v_max_biomass_C[CropType] / PlantCN;
		m_CropTotalN = MaxPlantN;
	}
	*/
	//sprintf(Crop_Name, "%s", v_CropName[CropType]);

	////////////////////////////////////////////////////////////////////////////////////////////

	if(m_PerennialCrop==1)
	{
		m_CropPDay = 1;
		m_CropPMonth = 1;
		m_CropHYear = 1;
		m_CropHDay = 31;
		m_CropHMonth = 12;
		//m_PerennialCrop = TRUE;
	}
	else
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_CropPMonth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_CropPDay);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_CropHMonth);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_CropHDay);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_CropHYear);
		Edt->EnableWindow(TRUE);
		
		//m_PerennialCrop = FALSE;
	}
	
	if (m_CropType.GetCurSel() == 10)
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(TRUE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(TRUE);
	}
	else
	{
		CEdit* Edt;
		Edt = (CEdit*)GetDlgItem(IDC_AlfCHRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCDRMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFCTMX);
		Edt->EnableWindow(FALSE);
		Edt = (CEdit*)GetDlgItem(IDC_ALFPDFMX);
		Edt->EnableWindow(FALSE);
	}


	UpdateData(FALSE);
}

void SitePage4::OnAskCartivar() 
{

}

/*void SitePage4::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_CropList.GetSelectionMark()+1;
    if (i > 0) 
	{
		m_CropID=i;
		UpdateData(FALSE);
		//OnKillfocusCropID();
	}

	*pResult = 0;
}*/

void SitePage4::OnKillfocusSeedDensity() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void SitePage4::OnKillfocusPsnEfficiency() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void SitePage4::OnKillfocusPsnMax() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void SitePage4::OnKillfocusGrowthVegetative() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void SitePage4::OnKillfocusGrowthReproductive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void SitePage4::OnCropModel() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);
	
	if(m_CropModel == 0)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_SeedDensity);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_PsnEfficiency);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_GrowthReproductive);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_GrowthVegetative);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_PsnMax);
		Edt->EnableWindow(FALSE); 		
	}

	UpdateData(FALSE);
*/	
}

void SitePage4::OnRadio2() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);
	
	if(m_CropModel == 1)
	{
		CEdit *Edt;
		Edt=(CEdit *)GetDlgItem(IDC_SeedDensity);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_PsnEfficiency);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_GrowthReproductive);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_GrowthVegetative);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_PsnMax);
		Edt->EnableWindow(TRUE); 

		
	}

	UpdateData(FALSE);
*/	
}

void SitePage4::demo(int rrr, int yyy) 
{
	CString txt;
	m_CropList.DeleteAllItems();
	if (m_CropN >= 0) 
	{
		for (int i = 1; i<=m_CropN;i++) 
		{
			txt = OrderNumber(i,"crop",&txt);
			m_CropList.InsertItem(i,txt);
		
			txt.Format("%d",crop_type[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,1,txt);
		
			txt.Format("%d",plant_month[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,2,txt);
		
			txt.Format("%d",plant_day[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,3,txt);
		
			txt.Format("%d",harvest_month[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,4,txt);
	
			txt.Format("%d",harvest_day[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,5,txt);

			txt.Format("%d",harvest_year[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,6,txt);
	
			txt.Format("%f",crop_residue[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,7,txt);

			txt.Format("%f",crop_yield[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,8,txt);
			
			txt.Format("%d",CoverCrop[rrr][yyy][i]);
			m_CropList.SetItemText(i-1,9,txt);
		}
	}
}

void SitePage4::OnKillfocusShootYield() 
{
	// TODO: Add your control notification handler code here

}


void SitePage4::OnChangeCropN() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CropNChangeFlag = 1;
	
}

void SitePage4::OnCropParas() 
{
	// TODO: Add your control notification handler code here
	NewCrop ww;
	if(ww.DoModal()==IDOK)
	{
		UpdateData(TRUE);
		int CropType = m_CropType.GetCurSel();

		if(CropType>=0) OnSelchangeCropType();
		UpdateData(FALSE);
	}
}

void SitePage4::OnKillfocusRootYield() 
{
	// TODO: Add your control notification handler code here

}


void SitePage4::OnPerennialCrop() 
{
	// TODO: Add your control notification handler code here

}

void SitePage4::OnKillfocusGrainFraction() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString notee;
	if(m_GrainFraction<=0.0||m_GrainFraction>=1.0)
	{
		
		notee.Format("Grain fraction must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	if(m_GrainFraction<=0.0||m_GrainFraction>=1.0)
	{
		
		notee.Format("Grain fraction must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	m_RootFraction = 1.0 - (m_GrainFraction + m_LeafFraction + m_ShootFraction);

	if(m_RootFraction<=0.0||m_RootFraction>=1.0)
	{
		CString notee;
		notee.Format("Please re-define leaf or stem fraction");
		AfxMessageBox(notee);
		return;
	}

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//m_CropTotalN = TotalN();
	
	UpdateData(FALSE);
}

void SitePage4::OnKillfocusShootFRaction() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_ShootFraction<=0.0||m_ShootFraction>=1.0)
	{
		CString notee;
		notee.Format("Leaf+stem fraction must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	m_RootFraction = 1.0 - (m_GrainFraction + m_LeafFraction + m_ShootFraction);

	if(m_RootFraction<=0.0||m_RootFraction>=1.0)
	{
		CString notee;
		notee.Format("Please re-define leaf or stem fraction");
		AfxMessageBox(notee);
		return;
	}

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//m_CropTotalN = TotalN();

	UpdateData(FALSE);
}

void SitePage4::OnKillfocusGrainCN() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//m_CropTotalN = TotalN();
	UpdateData(FALSE);
}

void SitePage4::OnKillfocusShootCN() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//m_CropTotalN = TotalN();
	UpdateData(FALSE);
}

void SitePage4::OnKillfocusRootCN() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//m_CropTotalN = TotalN();
	UpdateData(FALSE);
}

void SitePage4::OnKillfocusLeafFRaction() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_ShootFraction<=0.0||m_ShootFraction>=1.0)
	{
		CString notee;
		notee.Format("Leaf+stem fraction must be > 0 and < 1");
		AfxMessageBox(notee);
		return;
	}

	m_RootFraction = 1.0 - (m_GrainFraction + m_LeafFraction + m_ShootFraction);

	if(m_RootFraction<=0.0||m_RootFraction>=1.0)
	{
		CString notee;
		notee.Format("Please re-define leaf or stem fraction");
		AfxMessageBox(notee);
		return;
	}

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	
	UpdateData(FALSE);
}

void SitePage4::OnKillfocusLeafCN() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	float TC;
	if(m_GrainFraction==0.0) TC = 0.0;
	else TC = m_CropYield/m_GrainFraction;
	m_LeafYield = TC * m_LeafFraction;
	m_ShootYield = TC * m_ShootFraction;
	m_RootYield = TC * m_RootFraction;

	m_CropTotalN = CropTN(TC, m_GrainCN, m_LeafCN, m_ShootCN, m_RootCN, m_GrainFraction, m_LeafFraction, m_ShootFraction, m_RootFraction);
	if(m_CropTotalN<0.0) m_CropTotalN = 0.0;
	//m_CropTotalN = TotalN();
	UpdateData(FALSE);
}
