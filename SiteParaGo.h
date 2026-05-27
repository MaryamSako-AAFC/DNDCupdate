// Define a class to record all parameters inputed by user
//#include "Afxcoll.h"

//#ifdef AskGlobal

//#endif


class FPOINT
{
	float x;
	float y;
};

class Site_BaseInformation
{
public:
	// Site information
	char  sitename[255];
	char  Regionname[255];
	
	float latitude;
	float longitude;
    long  totalday;
    int   years;
    int   ifdaily, if1File;
	
		// Climate information
    int   ClimateFileType;
    int   ClimateFileNumber;
    float NO3NH4_Rainfall;
    float NH3_Atmosphere;//NO3_Atmosphere;
	float BaseCO2;
	float CO2IncreaseRate;
	float SOCa, SOCb;
	//float s_temp;
	float AnnualMeanT;//yr_avet;
	
	int WaterYr;
    	float DrainDepth;//added new parameters for tile drainage and misc
	float DrainSpace;
float DrainRad;
float DrainBed;
float keDrain;
float MaxNMove;
float MobileNF;
float NLayerF;
float NMoveRate;
float SoilEvapF;
float RunOffWF;
float RunOffNF;
float Factor1;
float Factor2;
float Factor3;
float Factor4;
float Factor5;
float Factor6;
int Factor7;
float Factor8;
float Factor9;
float Factor10;
float Factor13;
float UreaHydro;
float UreaHydro2;
float NH3SoilDF;
float N2N2OF;
float UreaDifF;
float Factor11;
int SpinUpYears;
int SpinUpCheck;
int CO2file;
float DenitGRate;
float NitGRate;
float NitRate;
float N2ORain;
float SprMeltF;
int TileOption;
        // Soil information
    int   Soil_Texture;
    float Soil_Density;
	float WaterPoolBD;
	int ProfileType;
	CString ProfileFileName;
	CString SpinUpFileName;
	CString CO2FileName;
    float Soil_pH;
	float Flood_pH;
    float Soil_OCatSurface;
    float Soil_Clay;
    int   Soil_landuse;
    //int   Soil_BypassFlow;
	float Soil_BypassFlow;
    float Soil_Litter;// Resoc
    float Soil_humads;// Ahsoc
    float Soil_humus; // Phsoc
	float PassiveC, PassiveCCN;
	//float RCNRVL, RCNRL, RCNRR, RCNB, RCNH, RCNM;
    float Soil_NO3;   // IniNO3
    float Soil_NH4;   // IniNH4
    float Soil_moiture;
    float Soil_T;
	int   SoilRetardation; //Soil retaration for water infiltration
	float LateralInflux;
	float Soil_MicrobioIndex;
	
	float Soil_WaterObstructLayer;
	float slope;
	float Soil_Quality;
	//int HighWT;
	float HighestWT;
	float Soil_Porosity;
	int UseION, PerennialCrop;
	float DClitter, DChumads, DChumus;
	float HumadCN, HumusCN;
	//float FieldCapacity;
	//float WiltPoint;
    float WaterPool;
    int   Idc;
    float H;
    float   Topr;
    float   Toph;
    float CEC;
    float TH;
    float m;
    float V;
    int   Q;//float 
    float Qstar;
    float AcWater;
    float SurfWater;
    float SnowPack;
    float BypassF;
	//float IrriWaterPH; 
    
    char  SoilName[30];
    char  NameNote[30];

    //Clay;
    //float Sts;
    //float RawSKS;
    float Sks;
    float Fldcap;
    float Wiltpt;
    float Psisat;
    float Beta;
	int SCSuse;
	float m_SPthickness;
	int m_SPlayers, m_SPso[11], layer[11];
	float m_SPth[11], m_SPd[11], m_SPsoc[11], m_SPph[11], m_SPfc[11], m_SPwp[11], m_SPpo[11], m_SPhy[11], m_SPc[11];
	char m_ProfileName[250];
//    char  ClayNote[30];
//    char  StsNote[30];
//    char  SksNote[30];
//    char  FldcapNote[30];
//    char  WiltptNote[30];
//    char  SoilhtcpNote[30];
//    char  BetaNote[30];
//    char  PsisatNote[30];
    
        // rotation
    int   Rotation_Number;
    //int   MaxCycle;
    
    int   MaxCrop;
    int   MaxTill;
    int   MaxFer;
    int   MaxManure;
    int   MaxWeed;
    int   MaxFlood;
    int   MaxIrr;
    int   MaxGrazing;
	int   MaxLime;
	//int   CropModel;

	//forest parameter
	float FoliageMass, WoodMass, LitterMass;
	int   ForestAge, ForestType, SoilFertility;
	float SOC12, LitterpH;
	float FolCNR,FloorC,LitterWater, Vascularity;
	CString ForestName;	

	int cropping_number;

	int db_Rotation_Number;
	int db_RotationID[20], db_RotateSpan[20], db_CycleSpan[20], db_PerennialCrop[20][20][5];
	int db_YrCrops[20][20], db_YrCropOrder[20][20][5], db_YrCropType[20][20][5], db_CoverCrop[20][20][5];
	int db_PMonth[20][20][5], db_PDay[20][20][5], db_HMonth[20][20][5], db_HDay[20][20][5], db_HYr[20][20][5];
	float db_Residue[20][20][5], db_Yield[20][20][5], db_RepRate[20][20][5];
	float db_PsnEff[20][20][5], db_PsnMax[20][20][5], db_TreeAge[20][20][5];
	float  db_TreeCurrentAge[20][20][5],  db_TreeLeafMax[20][20][5],  db_TreeLeafMin[20][20][5];
	int db_Transplant[20][20][5];
	
	float db_GrainFraction[20][20][5], db_LeafFraction[20][20][5], db_ShootFraction[20][20][5], db_RootFraction[20][20][5];
	float db_GrainCN[20][20][5], db_LeafCN[20][20][5], db_ShootCN[20][20][5], db_RootCN[20][20][5];
	float db_TDD[20][20][5], db_Water[20][20][5], db_OptT[20][20][5], db_Nfix[20][20][5], db_Vascularity[20][20][5],db_GrainFill[20][20][5];
	int db_RootShape[20][20][5];
	float db_LAImax[20][20][5];
	float db_FrostKill[20][20][5];
	float db_AlfCHRMX[20][20][5];
	float db_ALFCDRMX[20][20][5];
	float db_ALFCTMX[20][20][5];
	float db_ALFPDFMX[20][20][5];
	
	

// function part:
	Site_BaseInformation();
	void NewData();
	
};


class RotationParameter 
{
public:
    int   TotalYear;
    int   CycleYear;
	int   PlantType;//Crop=0 or forest=1;

	//forest parameter
	float FoliageMass, WoodMass, LitterMass;
	int   ForestAge, ForestType, SoilFertility;
	float SOC12, LitterpH;
	float FolCNR,FloorC,LitterWater;
//	CString ForestName;

};

class ParameterEachYear
{
public:
	//int   PlantType;//Crop=0 or forest=1;

    int   CropNumber;
    int   TillNumber;
    int   FerNumber;
	int   LimeNumber;
    int   ManNumber;
    int   FloodNumber;
    int   Leak;
    int   IrrNumber;
    int   IrrMode;
    float IrrIndex;
    int   WeedNumber;
    int   WeedProblem;
    float weedCN;
	int   GrazingNumber;
};

//forest parameters
class ForestParameter
{
public:
    float LCResVL, LCResL, LCResR, LCBio, LCHum;
    float FloorC;

	float ForestType, ForestAge;
	float BudC, WoodC, PlantC, PlantN;
	float FolNCon, Fsoil;
	float WoodMass, RootMass, FolMassMax, FolMassMin, FolMass;
	//CString ForestName;
};

//Crop's definition
class CropParameter
{
public:
    int   Type;		// Crop type
	int   GeneID;	// Crop genetic type
    int   Tmonth;	// Transplanting month
    int   Tday;		// Transplanting day
    int   Pmonth;	// Planting month
    int   Pday;		// Planting day
    int   Hmonth;	// Harvest month
    int   Hday;		// Harvest day
    int   Hyear;	// Harvest year
    float Residue;	// residue returned to the field
    float Yield;	// optimum yield
	float GrowthReproductive;
	float GrowthVegetative;
	int PerennialCrop;
	//float PsnEfficiency;
	//float PsnMax;
	float TreeAge, TreeCurrentAge, TreeLeafMax, TreeLeafMin;//InitialBiomass;
	int   transplanted;//mited;	// if rice is transplanted    
    float YieldC;
    float PlantC;
    float MaxPlantN;
    int   GrowDays;
    int   SeedDay;
    int   HarvDay;     
	int   jdtrans;	//juliday of transplanting
    int CropCode, WCFlag, CoverCrop;
    char  Vege[100];
    char  CropName[100];
    float Biomass_C;
    float Grain, Leaf, Straw, Root;    
	float GrainCN, RootCN, LeafCN, ShootCN;
    float CropTDD, WRuq, OptT, CropNFix, CropVascularity;
	float PsnEfficiency, PsnMax;
	int Transplant;
	float GRreproductive, MaxRootDepth, RootGrowRate;
	int PerennialFlag;
	float CropHeight, RCNPlan, Vascularity;

	int M_YrCrops[10][10];



    //float LeftPerc;   //?????????

//    char  note[13][30];
};

// Till's definition
class TillageParameter
{
public:
    int   method;
    int   month;
    int   day;
};

// Fer's definition
class FertilizationParameter
{
public:
    int   method;
    float Depth;
	int   year;
    int   month;
    int   day;
    
    float Nitrate;
    float AmmBic;
    float Urea;
    float Anh;
    float NH4NO3;
    //'AmmType;
    float NH42SO4;
    float NH42HPO4;    
};

class LimeParameter
{
public:
	int   year;
    int   month;
    int   day;
    float Amount;
};

class ManureParameter
{
public:
    int   month;
    int   day;
    float Amount;
    float C_N;
    int   Type;
};

class WeedParameter
{
public:
    int   month;
    int   day;
};

class FloodParameter
{
public:
    int   Fmonth;
    int   Fday;
    int   Dmonth;
    int   Dday;
	float FloodPH;
//'    Leak;
};

class IrrigationParameter
{
public:
    int   month;
    int   day;
    //'mode;
    float Water;
    float WaterpH;
};

class GrazingParameter
{
public:
	int Smonth;
	int Sday;
	int Emonth;
	int Eday;
	//int Type;//Cow,horse,sheep,pig,other
	float GrazingHour;//Grazing Hours per day
	float CattleHead;
	float HorseHead;
	float SheepHead;
};

/*class NowCropPractices
{
public:
    int  rotation;
    int   year;
	int   crop;
};
*/


    //' Define The properties of a kind of crop
struct CropProperty
{
    float junk1;
    char  Vege[50];
    char  Name[50];
    float Biomass_C;
    float Grain;
    float Straw;
    float Root;
    float RCNPlan;
    float RootCN;
    float StrawCN;
    float WRuq;
    float OptT;
    float CropAT;
    char  *note[13];
    
    float Yield;
    float YieldC;
    float PlantC;
    float MaxPlantN;
    int   GrowDays;
    int   SeedDay;
    int   HarvDay, CoverCrop;
    float LeftPerc;   
};

class CropofEachYear
{
public:
    int   CropID, WCFlag;
	int   GeneID;
    int   Left;
    float Yield;
    int   HarYr;
    int   SeedDay;
    int   GrowDays;
    float LeftPrec;
    float MaxPlanN;
    int   CropOrder, CoverCrop;
	int   jdtrans;
	int   seed_trans, PerennialCrop, Transplant;
	float TreeAge, TreeCurrentAge, TreeLeafMax, TreeLeafMin, GrowthReproductive, PsnEfficiency,PsnMax;
	float Grain, Leaf, Straw, Root;    
	float GrainCN, LeafCN, RootCN, ShootCN;
    float CropTDD, WRuq, OptT, CropNFix, Vascularity;
	float GrainFill;
	int	RootShape;
	float LAImax;
	float FrostKill;
	float AlfCHRMX;
	float ALFCDRMX;
	float ALFCTMX;
	float ALFPDFMX;
};


//'Global SoilF As soil_feature
class soil_feature
{
    char  Name[50];
    char  NameNote[50];
    float Clay;
    char  ClayNote[50];
    //float Sts;
    //char  StsNote[50];
    float Sks;
    char  SksNote[50];
    float Fldcap;
    char  FldcapNote[50];
    float Wiltpt;
    char  WiltptNote[50];
    float LateralInflux;
    char  LateralInfluxIndexNote[50];
    float Psisat;
    char  PsisatNote[50];
    float Beta;
    char  BetaNote[50];
};



//-----------------------------------------------------------------
// A base class to process array

class CropWorkArrayDefine
{
public:
	int maxRotation;
	int maxYear;
	int maxN;
	char *CWAP;

	CropWorkArrayDefine();			// inilitial parameter
	~CropWorkArrayDefine();			// free crop-pointer
	virtual int SizeOfData()=0;
	int dim(int,int,int);			// re-dim the array
	int dim(int,int);				// re-dim the array
	int dim(int);					// re-dim the array
	int clear();				    // free all pointer and set parameters to 0
};


//forest array defination
/*class ForestArray:CropWorkArrayDefine
{
public:
	ForestParameter *Pnt;

	ForestArray();
	~ForestArray();
	int SizeOfData();
	int dim(int,int);				// re-dim the array
	int Reset();
	ForestParameter *get(int,int);	// get a pointer of array(r,y,n)
};
*/
//-----------------------------------------------------------------
// Crop parameter class's definition
class CropArray:CropWorkArrayDefine
{
public:
	CropParameter *Pnt;

	CropArray();						// initialize crop-pointer
	~CropArray();						// free crop-pointer
	int SizeOfData();
	int dim(int,int,int);				// re-dim the array
	int Reset();
	CropParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};


//-----------------------------------------------------------------
// Till parameter class's definition
/*class TillArray:CropWorkArrayDefine
{
public:
	TillageParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	~TillArray();						// free crop-pointer
	int Reset();
	TillageParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};

*/
//-----------------------------------------------------------------
// Fer parameter class's definition
/*class FerArray:CropWorkArrayDefine
{
public:
	FertilizationParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	~FerArray();							// free crop-pointer
	int Reset();
	FertilizationParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};
*/
//-----------------------------------------------------------------
// Lime parameter class's definition
/*class LimeArray:CropWorkArrayDefine
{
public:
	LimeParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	~LimeArray();							// free crop-pointer
	int Reset();
	LimeParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};
*/
//-----------------------------------------------------------------
// Manure parameter class's definition
/*class ManureArray:CropWorkArrayDefine
{
public:
	ManureParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	~ManureArray();						// free crop-pointer
	int Reset();
	ManureParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};
*/
//-----------------------------------------------------------------
// Weed parameter class's definition
/*class WeedArray:CropWorkArrayDefine
{
public:
	WeedParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	~WeedArray();							// free crop-pointer
	int Reset();
	WeedParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};
*/
//-----------------------------------------------------------------
// Flood parameter class's definition
/*class FloodArray:CropWorkArrayDefine
{
public:
	FloodParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	~FloodArray();						// free crop-pointer
	int Reset();
	FloodParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};
*/
//-----------------------------------------------------------------
// Irrigation parameter class's definition
/*class IrrigationArray:CropWorkArrayDefine
{
public:
	IrrigationParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	IrrigationArray();						// inilialize crop-pointer
	~IrrigationArray();						// free crop-pointer
	int Reset();
	IrrigationParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};*/

//-----------------------------------------------------------------
// Grazing parameter class's definition
/*class GrazingArray:CropWorkArrayDefine
{
public:
	GrazingParameter *Pnt;

	int SizeOfData();
	int  dim(int,int,int);					// re-dim the array
	GrazingArray();						// inilialize crop-pointer
	~GrazingArray();						// free crop-pointer
	int Reset();
	GrazingParameter *get(int,int,int);	// get a pointer of array(r,y,n)
};
*/

//-----------------------------------------------------------------
// Cycle definition

/*class Cycle_a_year:CropWorkArrayDefine
{
public:
	ParameterEachYear *Pnt;

	int SizeOfData();
	int  dim(int,int);						// re-dim the array
	~Cycle_a_year();						// free crop-pointer
	int Reset();
	ParameterEachYear *get(int,int);	// get a pointer of array(r,y,n)
};
*/
//-----------------------------------------------------------------
// RotationArray definition

/*class RotationArray:CropWorkArrayDefine
{
	RotationParameter *Pnt;

public:
	int SizeOfData();
	int  dim(int);						// re-dim the array
	~RotationArray();// free crop-pointer
	int Reset();
	RotationParameter *get(int num);
};*/
	


//-----------------------------------------------------------------
// StringArray definition

/*
class StringArray//:CStringArray
{
private: 

	char *p[600];//**p;//101 only 100 years can be calculated
	
public:	
	int n;		//start from 1
	int tn;

	StringArray();
	~StringArray();
	int insert(int pos,char *dat);
	int del(int pos);
	int clear();
	char *get(int pos);
	int dim(int num);
};
*/

class AreaParameter
{
public:
	CRect rect;
	CString  countyID;
	long former;
	float ValueR,ValueG,ValueB;
	//float OValue;
	//COLORREF Color;
};

//-----------------------------------------------------------------
// Area-polygen parameter class's definition
class AreaArray:CropWorkArrayDefine
{
public:
	AreaParameter *Pnt;
	int     *CNum;
	int    N;
	CString what;//1:temp,2:rainfall,3:soil,4:crop
	CString IfChange;//YES, NO
	CString ModifyMode,name;
	int		country,PNum;

	int SizeOfData();
	int  GetSize(int *,int *);
	int  dim(int,int);				// re-dim the array
	int  clear(CString style);		// Set all values in the array as 0
	AreaArray(int,int);				// initial crop-pointer
	~AreaArray();					// free crop-pointer
	AreaParameter *get(int,int);	// get a pointer of array(r,y)
	AreaParameter *KGet(int r,int y);//get a point at(r,y) and 
									// redim array if (r or y) over the boundary
};

/*class RegionInformation
{
public:
	StringArray CountryList;
	StringArray StateList;
	StringArray CropList;
	StringArray SownList;
	CString CropUnit;
	StringArray IndexList;//SOC and Gas
	StringArray CropInf;
	StringArray SoilInf;
	StringArray AnimalInf;

	int  Tn;	// total state number in sort order
	int  Gn;    // variables number in database file *1_1
	int  Cn;    // variables number in database file *2_1
	//int  Sn;    // variables number in database file *3_1
	int  Mn;    // variables number in database file *5_1
	//int  Gn;    // variables number in database file *6_1
	char *GetCropName(int);
	RegionInformation();
};*/


/*class DNDCSystem {
 public:
	int Mode;//= 1;
	int MSite;//= 0;
	int Country;
	int Province;
	int County;
	int DType;

	int PredictWhat;

	double lit_back_field;
    double animal_manure;
    double human_manure;
	double IrrIndex;
	double Fertilizer;

	int FertMode;	//0:county-specified,1:crop-specified
	int NoTill;//TRUE:notill, FALSE:tillage

	double CO2;
	double Rainfall;
	double Temp;

	char OutDir[256];

	CString ShowCnty;
	int Sort[3];	 //Map Subject
	int Type[3];	 //item
	int ViewIndex[3];//1 SOC change,2 CO2,3 CH4,4 NH3,5 N2O,6 NO
	float scale[3];
	int ifLog[3];	 //0:normal,1:log
	int deLog;		 //1: define by user, otherwise:use default parameters
	CString title[3];
	int MMM[3];      //select min,max, or average value to shoe
	int Group[2][100];
	int calmode;	//0:/  1:- 
	int SelGroup[2];

	int Scenario;
	int VValue;

	int ColorNum;
	float ColorIVal;

	CString CoeffDir;//WHich Coefficient system will be used.

	CString SiteFile;
	CString PaleoCFile;//paleoclimate file name
	int totalyear, Pyear;
	
	float EndSOC,Biomas,Yield;
	float EndSON,EndSN;
	float YrLeachNO3;

	CString UserColorFile;

	//DNDCSystem();
};*/

/*class DNDCDatabase {
public:
	int  Country;
	
	int  StateID;
	int  CountySI;
	int  DTypeID;

	long CountyID;
	CString State;
	CString County;
	float Latitude;
	float Longitude;

	CString CliFile;
	float NO3;

	float SOCMax,SOCMin;
	float ClayMax,ClayMin;
	float pHMax,pHMin;
	float DMax,DMin;

	float CropLand,Sown,NFer,NRate,IrrInd;
	float W_C,WWT,CRN,R_R,R_1,RAP,SWT,POT,SOR,CER,W_R,SOY;
	float COT,TOB,SUG,BET,GRE,VEG,R_2,FAL,PAS,N_HAY,L_HAY;

	CString MapID;

	float Dairy,Beef,Horse,Pig,Sheep;

	DNDCDatabase();
	//int ReadCounty(int,int,int);
};
*/

/*#ifdef _T_DNDC
DNDCSystem DNDCSys;
#endif*/


class map_parameters
{
public:
    float f1;	//第一标准纬线
    float r1;
    float U1;
    float f2;	//第二标准纬线
    float r2;
    float U2;
    float lc;	//中央经线
    
    float fs;	//起始纬度
    float fn;	//终止纬度
    float df;	//纬度格网间隔
    float lb;	//起始经度
    float le;	//终止经度
    float dl;	//经度格网间隔
    float l0;	//终止经度
    
    float ps;	//起始纬度投影半径
    float ros;	//起始纬度投影半径
    float k;	//参数
    float af;	//参数
    float mscale;	//比例尺
    
    float eo;	//偏心率
    float a1;	//扁率
    float a;	//地球长半径
    float b;	//地球短半径
    float earth;	//地球类型
    
    float ymai[3];
    float xmai[3];
    
    float pr4;
    float w;
    int   wsize;

	float ratio;
	float Wd;

    CString  font;
    COLORREF Wordcolor;
    COLORREF Pointcolor;
    COLORREF LatLonColor;
};


class ViewedMapParameter:public map_parameters
{
public:
	int begin_year;	//起始年
    int begin_month;//起始月
    int end_year;	//终止年
    int end_month;	//终止月
    int Row;		//
    int column;
    CString sizecode;	//1=毫米 2=度 3=hPa 4=其它
    float xsize;	//单元 x 尺寸
    float ysize;	//单元 y 尺寸
    float left_longitude; //经度
	float right_longitude;//经度
    float up_latitude;	 //纬度
    float down_latitude; //纬度
    int max;
    int min;
    float valueunit;//数值的单位比例  降水=毫米  温度=摄氏度
};





#ifdef AskGlobal
 CropArray			Crop;
 Site_BaseInformation	IData ;
 StringArray		ClimateFilename;
 StringArray		WTFilename;
  StringArray		LaiFilename;
// RotationArray		rotation;
    // d-D array, 1st-D = number of rotation
    //            2nd-D = maximum years of these cycles
    //-->Crop information of each year in each cycle
// ForestArray        forest;

// Cycle_a_year		cycle;
 //TillArray			till;
 //FerArray			fer;
// LimeArray			lime;
// ManureArray		manure;
// WeedArray			weed;
// FloodArray			flood;
 //IrrigationArray	irrigation;
// GrazingArray       grazing;
// NowCropPractices	NowC;
 
 CropofEachYear CYr[2];

#endif

int JulianDay(int month, int day);
//int SetArrayRange(int mode, int num);
int RecordClimateFile(int mode, int DaymetFlag, int UseID, char *r_Country);
int SaveClimateFileOfAYear(int id,char *ch,
	float lat, int ClimateFileType, 
	float NO3NH4_Rainfall,float NH3_Atmosphere, float BaseCO2,
	CString IfCheck,int mode, float CO2IncreaseRate, int UseID, char *r_Country);
//int FileCopy(char *source, char *dest);
int FileExpend(char *source, char *dest);
int ReadSoilFeature(CString mode);
int SaveCropParas();
//int ReadCropProperty(int CropIndex,CropParameter *cp);
int CreateInputFiles(int DaymetFlag, int UseID, char *r_Country, int DayRecord); 
int SaveSite(int DayRecord);
int SaveSoilParas(int id);
void CN_ratios(float *RCNRVL, float *RCNRL, float *RCNRR, float *RCNB, float *RCNH, float *RCNM, float *PassiveCCN);
//int SaveInterCropParas();
//int SaveACrop(FILE *fp,CropParameter *cp,int i,int n);
int SaveInterFarmParas();
int savetillage(FILE *fp,TillageParameter *tp);//,int n);
void ReadInputDatafromDND(char *fname, int UseID);
void ReadDNDfile(char *fname, int UseID);
void SaveDatatoFile(char *fname, int SiteRegion);
void NewSaveDatatoFile(char *fname, int SiteRegion);
void ReSetIniNO3NH4();
int  SetSoilH();
void ReSetCcomponent();
//void DMessageBox(char *,char *,int);
//void SetToprToph();
void SetCropCN(CropParameter *cp);
//int ResetRotation();

//float day_par(int Jday, float LATITUDE, float* Day_Hrs);
int GetShortFileName(char *ch);
int GetAMT(char *fname);
int ReadClimateHead(int yr);
char *EraseFBSpace(char *str);
CString *EraseFBSpace(CString *str);
char *EraseAllSpace(char *str);
CString EraseAllSpace(CString *str);
int ChangeChar(char *Name, char p1,char p2);
CString ChangeChar(CString Name, char p1,char p2);
BOOL IfMonth(int Month);
BOOL IfDay(int day);
BOOL IfCultivarExist(int id);
int  SetCountryList(CComboBox *Ctry);
int  SetProvinceList(CString ctry,CComboBox *Province,int Sel);//country,list,selected state
int  SetCropList(CComboBox *list);
int  ReadCropList();
char *GetDBFilePath(int ctry,char *fname);
char *GetDBFileHead(int ctry,char *p);
int  NumberToChar(char *p,int n);
char *ValueToCString(char *str,float val);
float CheckValueRange(float z6,int high,int low);

//BOOL IfForest();
//BOOL IfForest(int year);
//int SaveForestParas();
//int SavePracticeParas();
//int SaveFerOfAYear(int year,int FERNUM,int *JDFER, int *FerM,
//	float *FERDD, float *FERT1T, float *FERT2T,float *FERT3T, 
//	float *FERT4T, float *FERT5T, float *FERT6T, float *FERT7T);
//int SaveLimeOfAYear(int year,int FERNUM,int *JDFER, float *FERDD);

//CString ReadForestList(CComboBox *FType,int sort);
CString PathAddFile(CString CoePath, CString file);
char *PathAddFile(char *CoePath, char *file);
//int checkScenarios();
//BOOL CancelThisState(int Country,int state);
CString OrderNumber(int i,char *name,CString *txt);
int ResetListItem(int newN,int oldN,char *name,CListCtrl *List);
