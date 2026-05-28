//Redifine order of radio buttons in dndc71.rc
//In C:\DndcGraphics\HLP\DNDC71.HPJ
//Change "C:\Program Files\Microsoft Visual Studio\VC98\MFC\include\afxhelp.hm." to "C:\Program Files (x86)\Microsoft Visual Studio\VC98\MFC\include\afxhelp.hm."

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <io.h>
#include "RunPaths.h"
#include "dndc_tool.h"
#include "graphexDoc.h"
#include "graphexView.h"

#define BASE 
//#define CONSOLE

//extern const char* get_path();

//#define MANURE
//#define DROUGHT
//#define DEGUI
//#define HYDRO 
//#define NUTRITION


#ifdef CONSOLE
#else 
#define ROOTDIR "\\DNDC"
#define OUTPUT "\\DNDC\\Result"
#define INTER "\\DNDC\\Result\\Inter"
#define INTERMANAGE "\\DNDC\\Result\\Inter\\Management"
#define Pass "\\DNDC\\Result\\Record\\Region"
#endif
#ifdef MANURE
#define ROOTDIR "\\ManureDNDC"
#define OUTPUT "\\ManureDNDC\\Result"
#define INTER "\\ManureDNDC\\Result\\Inter"
#define INTERMANAGE "\\ManureDNDC\\Result\\Inter\\Management"
#define Pass "\\ManureDNDC\\Result\\Record\\Region"
#endif

#define SOILDEPTH           2.0
#define MAXYEARS			100
#define FILE_NOT_FOUND		1001
#define RI					0.005
#define DRF   0.05
#define EFFRB .67
#define srh .16
#define RBO .02
#define SRB .9
#define krcvl .25
#define krcl .074
#define krcr .02
#define KRB    0.12
#define hrb    0.04
#define EFFNO  .2
#define KCI .017
#define KNI .083
#define FD  .05
#define um_no3   .67
#define um_no2   .67
#define um_no    .34
#define um_n2o   .34
#define YMC      .503
#define MC       .0076
#define m_no3   .09
#define ym_no3  .401
//#define R       .29
#define m_no2  .0349
#define ym_no2 .428
#define ym_no .151
#define m_no  .0792
#define ym_n2o .151
#define m_n2o  .0792
#define srh .16
#define D_O2 0.07236  // O2 diffusion in air, mý/h from Beisecker 1994
#define K35       25
#define QK        2.0
#define ten9      1000000000.0
#define CANNOT_CREATE_FILE 1002
#define Eh_ch4 -100.0 //!! Critical Eh (mV) for CH4 production
#define F_litter 0.025
#define F_humads 0.025
#define F_humus 0.095
#define F_PassiveC 0.0
#define FractionLitter 0.01
#define FractionHumads 0.05
#define	FractionHumus 0.94

#define foot2_m2 0.0929
#define foot3_m3 0.0283
#define lb_kg 0.4535
#define lboft3_kgom3 16.015
#define ac_ha 0.405
#define lboac_kgoha 1.12

float day_par(int Jday, float LATITUDE, float* Day_Hrs);
int JulianDay(int month, int day);
//void CreateInputFile(void);


class dndc74
{
public:


	///////
	float fert1, fert2, fert3, fert4, fert5, fert6, fert7;
	float cattle, horse, sheep, pig, fowl, human, manure_N, manure_C;
	float F_AnimalManure, F_HumanManure, total_ha, irri_index;
	int OnlyRice, InterDrain, major_target, ShallowFlood;

	//char CountryName[120], ScenarioName[120], DatabaseName[240];//, state_name[80], county_name[80];
	//char climfile_ID[120];
	int landtype;
	//long int county_ID1, county_ID2, county_ID3, county_ID4a, county_ID4b, county_ID4c;
	//long int county_ID5, county_ID6, county_ID7;
	long int map_ID;
	//float Kmax_SOC[5], Kmin_SOC[5],	Kmax_clay[5], Kmin_clay[5], Kmax_pH[5], Kmin_pH[5], Kmax_BD[5], Kmin_BD[5];
	//float max_SOC, min_SOC,	max_clay, min_clay, max_pH, min_pH, max_BD, min_BD;
	float r_latitude, r_longitude, RainN;
	float crop_ha[85], sown_ha, fert_total;
	float BaseCO2, R_ResidueLeft;//, CO2IncreaseRate; 
	float AirTempRate, RainRate;
	char File1[120], File2[120], File3[120];
	
	
	char File4[120], File5[120], File6[120];
	int SoilYear, NoTill, c_ViewMode;
	int databaseType;
	int  MCflag;//CountryCode, StateCode, 
	float StoneFraction;
	int DailyItem, SimuYears, StartYear, DBType;//FarmFile, RegionCode, 
	float soca[5], socb[5], Soil_humus, Soil_Litter, Soil_humads, PassiveC;
	float MC_Soil_Litter, MC_Soil_humads, MC_Soil_humus, MC_NO3, MC_NH4, MC_WRL;

	CString CropSystem[250];

	void frame(CGraphexDoc*, char *countryName, char *stateName, char *site, int MODE, int year);

	void crop_note(CGraphexDoc*, char *cropName, int MODE, int c_ViewMode, int landuse);
	void EU_farm_files(int landuse, char *CountryName, int province, int InterDrain, char *climfile_ID);
	
	dndc74();
	~dndc74();

	void dndc_site(CGraphexDoc*);
	void dndc_region(MODEL_LINK_INFO* pLinkInfo,CGraphexDoc*, int Monitor);
	void Shangrila(MODEL_LINK_INFO* pLinkInfo, CGraphexDoc *pDoc, int GlobeData, int Monitor);
	void PaintGrid(char *grid_ID, CGraphexDoc *pDoc, int SelectID);
	void create_input_files(char *Farm_ID, int soilID, int landType, 
			int cropType, float area, float BDL, float BDH, float PHL, float PHH, 
			float OCL, float OCH, float CLAYL, float CLAYH, int k);
	void site_files_ES(char *county_name, float longitude, float latitude, 
						   char *Farm_ID, int soilID);
	void Record_summary(void);
	void map_county(CGraphexDoc *pDoc, char *CountryName, char *ProvinceName, long int map_ID, 
							 int fill_color, int RegionCode, int CountryCode, int StateCode);
	void map_scale(int RegionCode, int country_code, int state_code, float *qq, float *xx, float *yy);
	void map_state(CGraphexDoc *pDoc, char *CountryName, char *ProvinceName, int databaseType, 
							int RegionCode, int country_code, int state_code);
	void MappingCountry(CGraphexDoc *pDoc, char *CountryName, char *ProvinceName, int RegionCode, int country_code, int state_code);
	
};

/*
class crop
{
public:
	crop();
	~crop();
};

*/
