// RegionInput.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "RunPaths.h"
#include <direct.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
//#include <io.h>

#include "RegionInput.h"
#include "RegionYear.h"
#include "SitePara.h"
#include "dndc_tool.h"
#include "direct.h"
#include "dndc_main.h"
#include "Dndc_YieldPredict.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char ConName[255], FileName[255], Root1[300], Root2[300], RootName[255], WholeName[500];
void www(int year);
int ManageFlag=0, SoilDataUse=0, AcceptOK=0;
int r_ViewMode, FarmFile, DailyRecord, MajorConcern;	
int region_code=0, state_code, country_code, SimuMode;
float CO2, AirTemp, YieldIncrease;
char r_Country[120]="None", r_Province[240]="None";
char r_Scenario[240]="None", r_DatabaseName[240]="None";


//void Glean_StringR(char *String, int Num1, int Num2, char *Sub_Str);

/////////////////////////////////////////////////////////////////////////////
// RegionInput dialog


RegionInput::RegionInput(CWnd* pParent /*=NULL*/)
	: CDialog(RegionInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(RegionInput)
	m_StartGridID = 1;
	m_ScenarioName = _T("");
	m_SimuYears = 1;
	m_StartYear = 2010;
	m_RegionName = _T("");
	m_TotalCells = 0;
	m_SimulatedCells = 0;
	m_DataFormat = 0;
	m_Drought = 0;
	//}}AFX_DATA_INIT
}


void RegionInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RegionInput)
	DDX_Control(pDX, IDC_SoilDataUse, m_SimuMode);
	DDX_Control(pDX, IDC_PROGRESS1, m_ConvertGo);
	DDX_Control(pDX, IDC_MajorTarget, m_MajorTarget);
	DDX_Control(pDX, IDC_DailyRecord, m_DailyItem);
	DDX_Control(pDX, IDC_GisFileList, m_GisFileName);
	DDX_Text(pDX, IDC_StartGridID, m_StartGridID);
	DDX_Text(pDX, IDC_ScenarioName, m_ScenarioName);
	DDX_Text(pDX, IDC_SimuYears, m_SimuYears);
	DDX_Text(pDX, IDC_StartYear, m_StartYear);
	DDX_Text(pDX, IDC_RegionName, m_RegionName);
	DDX_Text(pDX, IDC_TotalCells, m_TotalCells);
	DDX_Text(pDX, IDC_SimulatedCells, m_SimulatedCells);
	DDX_Radio(pDX, IDC_DataFormat, m_DataFormat);
	DDX_Radio(pDX, IDC_Drought1, m_Drought);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RegionInput, CDialog)
	//{{AFX_MSG_MAP(RegionInput)
	ON_BN_CLICKED(IDC_SelGisFile, OnSelGisFile)
	ON_BN_CLICKED(IDC_yr1, Onyr1)
	ON_BN_CLICKED(IDC_yr2, Onyr2)
	ON_BN_CLICKED(IDC_yr3, Onyr3)
	ON_BN_CLICKED(IDC_yr4, Onyr4)
	ON_BN_CLICKED(IDC_yr5, Onyr5)
	ON_BN_CLICKED(IDC_yr6, Onyr6)
	ON_BN_CLICKED(IDC_yr7, Onyr7)
	ON_BN_CLICKED(IDC_yr8, Onyr8)
	ON_BN_CLICKED(IDC_yr9, Onyr9)
	ON_BN_CLICKED(IDC_yr10, Onyr10)
	ON_BN_CLICKED(IDC_yr11, Onyr11)
	ON_BN_CLICKED(IDC_yr12, Onyr12)
	ON_BN_CLICKED(IDC_yr13, Onyr13)
	ON_BN_CLICKED(IDC_yr14, Onyr14)
	ON_BN_CLICKED(IDC_yr15, Onyr15)
	ON_BN_CLICKED(IDC_yr16, Onyr16)
	ON_BN_CLICKED(IDC_yr17, Onyr17)
	ON_BN_CLICKED(IDC_yr18, Onyr18)
	ON_BN_CLICKED(IDC_yr19, Onyr19)
	ON_BN_CLICKED(IDC_yr20, Onyr20)
	ON_BN_CLICKED(IDC_yr21, Onyr21)
	ON_BN_CLICKED(IDC_yr22, Onyr22)
	ON_BN_CLICKED(IDC_yr23, Onyr23)
	ON_BN_CLICKED(IDC_yr24, Onyr24)
	ON_BN_CLICKED(IDC_yr25, Onyr25)
	ON_BN_CLICKED(IDC_yr26, Onyr26)
	ON_BN_CLICKED(IDC_yr27, Onyr27)
	ON_BN_CLICKED(IDC_yr28, Onyr28)
	ON_BN_CLICKED(IDC_yr29, Onyr29)
	ON_BN_CLICKED(IDC_yr30, Onyr30)
	ON_BN_CLICKED(IDC_yr31, Onyr31)
	ON_BN_CLICKED(IDC_yr32, Onyr32)
	ON_BN_CLICKED(IDC_yr33, Onyr33)
	ON_BN_CLICKED(IDC_yr34, Onyr34)
	ON_BN_CLICKED(IDC_yr35, Onyr35)
	ON_BN_CLICKED(IDC_yr36, Onyr36)
	ON_BN_CLICKED(IDC_yr37, Onyr37)
	ON_BN_CLICKED(IDC_yr38, Onyr38)
	ON_BN_CLICKED(IDC_yr39, Onyr39)
	ON_BN_CLICKED(IDC_yr40, Onyr40)
	ON_LBN_DBLCLK(IDC_GisFileList, OnDblclkGisFileList)
	ON_EN_KILLFOCUS(IDC_SimuYears, OnKillfocusSimuYears)
	ON_EN_SETFOCUS(IDC_RegionName, OnSetfocusRegionName)
	ON_BN_CLICKED(ID_SAVEREGION, OnSaveregion)
	ON_BN_CLICKED(IDC_Accept, OnAccept)
	ON_BN_CLICKED(ID_OPENREGION, OnOpenregion)
	ON_CBN_KILLFOCUS(IDC_MajorTarget, OnKillfocusMajorTarget)
	ON_EN_KILLFOCUS(IDC_RegionName, OnKillfocusRegionName)
	ON_BN_CLICKED(IDC_Farming, OnFarming)
	ON_EN_CHANGE(IDC_StartGridID, OnChangeStartGridID)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_DataConversion, OnDataConversion)
	ON_BN_CLICKED(IDC_yr41, Onyr41)
	ON_BN_CLICKED(IDC_yr42, Onyr42)
	ON_BN_CLICKED(IDC_yr43, Onyr43)
	ON_BN_CLICKED(IDC_yr44, Onyr44)
	ON_BN_CLICKED(IDC_yr45, Onyr45)
	ON_BN_CLICKED(IDC_yr46, Onyr46)
	ON_BN_CLICKED(IDC_yr47, Onyr47)
	ON_BN_CLICKED(IDC_yr48, Onyr48)
	ON_BN_CLICKED(IDC_yr49, Onyr49)
	ON_BN_CLICKED(IDC_yr50, Onyr50)
	ON_BN_CLICKED(IDC_yr51, Onyr51)
	ON_BN_CLICKED(IDC_yr52, Onyr52)
	ON_BN_CLICKED(IDC_yr53, Onyr53)
	ON_BN_CLICKED(IDC_yr54, Onyr54)
	ON_BN_CLICKED(IDC_yr55, Onyr55)
	ON_BN_CLICKED(IDC_yr56, Onyr56)
	ON_BN_CLICKED(IDC_yr57, Onyr57)
	ON_BN_CLICKED(IDC_yr59, Onyr59)
	ON_BN_CLICKED(IDC_yr60, Onyr60)
	ON_BN_CLICKED(IDC_yr61, Onyr61)
	ON_BN_CLICKED(IDC_yr62, Onyr62)
	ON_BN_CLICKED(IDC_yr63, Onyr63)
	ON_BN_CLICKED(IDC_yr64, Onyr64)
	ON_BN_CLICKED(IDC_yr65, Onyr65)
	ON_BN_CLICKED(IDC_yr66, Onyr66)
	ON_BN_CLICKED(IDC_yr67, Onyr67)
	ON_BN_CLICKED(IDC_yr68, Onyr68)
	ON_BN_CLICKED(IDC_yr69, Onyr69)
	ON_BN_CLICKED(IDC_yr70, Onyr70)
	ON_BN_CLICKED(IDC_yr71, Onyr71)
	ON_BN_CLICKED(IDC_yr72, Onyr72)
	ON_BN_CLICKED(IDC_yr73, Onyr73)
	ON_BN_CLICKED(IDC_yr74, Onyr74)
	ON_BN_CLICKED(IDC_yr75, Onyr75)
	ON_BN_CLICKED(IDC_yr76, Onyr76)
	ON_BN_CLICKED(IDC_yr77, Onyr77)
	ON_BN_CLICKED(IDC_yr78, Onyr78)
	ON_BN_CLICKED(IDC_yr79, Onyr79)
	ON_BN_CLICKED(IDC_yr80, Onyr80)
	ON_BN_CLICKED(IDC_yr81, Onyr81)
	ON_BN_CLICKED(IDC_yr82, Onyr82)
	ON_BN_CLICKED(IDC_yr83, Onyr83)
	ON_BN_CLICKED(IDC_yr84, Onyr84)
	ON_BN_CLICKED(IDC_yr85, Onyr85)
	ON_BN_CLICKED(IDC_yr86, Onyr86)
	ON_BN_CLICKED(IDC_yr87, Onyr87)
	ON_BN_CLICKED(IDC_yr88, Onyr88)
	ON_BN_CLICKED(IDC_yr89, Onyr89)
	ON_BN_CLICKED(IDC_yr90, Onyr90)
	ON_BN_CLICKED(IDC_yr91, Onyr91)
	ON_BN_CLICKED(IDC_yr92, Onyr92)
	ON_BN_CLICKED(IDC_yr93, Onyr93)
	ON_BN_CLICKED(IDC_yr94, Onyr94)
	ON_BN_CLICKED(IDC_yr95, Onyr95)
	ON_BN_CLICKED(IDC_yr96, Onyr96)
	ON_BN_CLICKED(IDC_yr97, Onyr97)
	ON_BN_CLICKED(IDC_yr98, Onyr98)
	ON_BN_CLICKED(IDC_yr99, Onyr99)
	ON_BN_CLICKED(IDC_yr100, Onyr100)
	ON_BN_CLICKED(IDC_yr58, Onyr58)
	ON_BN_CLICKED(IDC_Drought2, OnDrought2)
	ON_BN_CLICKED(IDC_Drought1, OnDrought1)
	ON_CBN_SELCHANGE(IDC_DailyRecord, OnSelchangeDailyRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RegionInput message handlers

void RegionInput::OnSelGisFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );

	if(ask.DoModal()==IDOK)
	{
		
	}
	else
		return;
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_GisFileName.GetCount();
	if (num==1) return;
	
	k=m_GisFileName.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName,cst);
		m_GisFileName.InsertString(k,FileName);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_GisFileName.GetCount()==1) break;
		k++;
	}
	m_GisFileName.SetCurSel(k);
	
//	RegionSelectFlag = 1;
	sprintf(WholeName, "%s", cst);

	CString CP;
	int i, L1, T=0, G[20]={0,0};

	int LL=strlen(WholeName);
	for(i=LL; i>=0; i--)
	{
		if(WholeName[i]=='_') 
		{
			L1=i-1;
			break;
		}
	}

	for(i=0; i<=LL; i++)
	{
		if(WholeName[i]=='\\') 
		{
			T++;
			G[T]=i;
		}
	}

	Glean_String(WholeName, G[T]+1, L1, ConName);
	Glean_String(WholeName, 0, G[T], RootName);
	Glean_String(WholeName, 0, G[T-1], Root1);
	Glean_String(WholeName, 0, G[T-2], Root2);
	
	CP.Format("%s", ConName);

	int RegionCode = 0;

	
	char Fregion[200];
	FILE *region;

	sprintf(Fregion, "%s\\Inter\\PassName", OUTPUT);
	region = fopen(Fregion, "w");
	if(region==NULL) note(1, Fregion);
	
	fprintf(region, "%d %d\n", -1, 0);
	fprintf(region, "%s\n", CP);
	fprintf(region, "%s %s\n", Root1, Root2);
	fprintf(region, "%s\n", RootName);
	fprintf(region, "%s\n", WholeName);
	fclose (region);

	//sprintf(FileName, "%s", WholeName);

	OnKillfocusRegionName();

	UpdateData(FALSE);

/*	CString SCF;
	FILE *scf;
	SCF.Format("%s\\Inter\\RegionSelectCrops.txt", OUTPUT);
	scf=fopen(SCF, "w");
	if(scf==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", SCF);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(scf, "%d\n", 0);
	fclose(scf);
*/
/*	CEdit *Edt;
	if(strcmp(CP,"China")==0||strcmp(CP,"USA")==0)
	{		
		Edt=(CEdit *)GetDlgItem(IDC_SelectState);
		Edt->EnableWindow(TRUE); 
	}
	else
	{		
		Edt=(CEdit *)GetDlgItem(IDC_SelectState);
		Edt->EnableWindow(FALSE); 
	}*/
}

/*void Glean_StringR(char *String, int Num1, int Num2, char *Sub_Str)
// Abstract part of String (from Num1 to Num2) and put to Sub_Str

{
  int i, l;
  l=strlen(String);
  if(Num1>Num2)  {
    //printf("%s\n",String);
    //Hint("Num1>Num2 in Glean_String",String);
    Sub_Str[0]='\0';
    return;
  }
  if (Num1>l) {
    //Hint("Out of range ",String);
    Sub_Str[0]='\0';
    return;
  }
    if (Num2>l)  Num2=l;
    for(i=Num1;i<=Num2;i++)
       Sub_Str[i-Num1]=String[i];
       Sub_Str[i-Num1]='\0';
}*/

void RegionInput::OnFarmFile() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);

	CEdit *Edt;
	
	Edt=(CEdit *)GetDlgItem(IDC_yr1);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr2);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr3);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr4);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr5);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr6);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr7);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr8);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr9);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr10);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr11);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr12);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr13);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr14);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr15);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr16);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr17);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr18);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr19);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr20);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr21);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr22);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr23);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr24);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr25);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr26);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr27);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr28);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr29);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr30);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr31);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr32);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr33);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr34);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr35);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr36);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr37);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr38);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr39);
	Edt->EnableWindow(0); 
	Edt=(CEdit *)GetDlgItem(IDC_yr40);
	Edt->EnableWindow(0); 
	
	//m_FarmFile2=NULL;

	Edt=(CEdit *)GetDlgItem(IDC_redefine);
	Edt->EnableWindow(0); 

	UpdateData(FALSE);
}

void RegionInput::OnFarmFile2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//m_FarmFile=NULL;

	CEdit *Edt;
	Edt=(CEdit *)GetDlgItem(IDC_redefine);
	Edt->EnableWindow(1); 

	UpdateData(FALSE);

	OnKillfocusSimuYears();
}

void RegionInput::Onyr1() 
{
	// TODO: Add your control notification handler code here
	OnButton1();

	ManageFlag=1;
	int year=1;
	www(year);
}

void RegionInput::Onyr2() 
{
	// TODO: Add your control notification handler code here
	int year=2;
	www(year);
}

void RegionInput::Onyr3() 
{
	// TODO: Add your control notification handler code here
	int year=3;
	www(year);
}

void RegionInput::Onyr4() 
{
	// TODO: Add your control notification handler code here
	int year=4;
	www(year);
}

void RegionInput::Onyr5() 
{
	// TODO: Add your control notification handler code here
	int year=5;
	www(year);
}

void RegionInput::Onyr6() 
{
	// TODO: Add your control notification handler code here
	int year=6;
	www(year);
}

void RegionInput::Onyr7() 
{
	// TODO: Add your control notification handler code here
	int year=7;
	www(year);
}

void RegionInput::Onyr8() 
{
	// TODO: Add your control notification handler code here
	int year=8;
	www(year);
}

void RegionInput::Onyr9() 
{
	// TODO: Add your control notification handler code here
	int year=9;
	www(year);
}

void RegionInput::Onyr10() 
{
	// TODO: Add your control notification handler code here
	int year=10;
	www(year);
}

void RegionInput::Onyr11() 
{
	// TODO: Add your control notification handler code here
	int year=11;
	www(year);
}

void RegionInput::Onyr12() 
{
	// TODO: Add your control notification handler code here
	int year=12;
	www(year);
}

void RegionInput::Onyr13() 
{
	// TODO: Add your control notification handler code here
	int year=13;
	www(year);
}

void RegionInput::Onyr14() 
{
	// TODO: Add your control notification handler code here
	int year=14;
	www(year);
}

void RegionInput::Onyr15() 
{
	// TODO: Add your control notification handler code here
	int year=15;
	www(year);
}

void RegionInput::Onyr16() 
{
	// TODO: Add your control notification handler code here
	int year=16;
	www(year);
}

void RegionInput::Onyr17() 
{
	// TODO: Add your control notification handler code here
	int year=17;
	www(year);
}

void RegionInput::Onyr18() 
{
	// TODO: Add your control notification handler code here
	int year=18;
	www(year);
}

void RegionInput::Onyr19() 
{
	// TODO: Add your control notification handler code here
	int year=19;
	www(year);
}

void RegionInput::Onyr20() 
{
	// TODO: Add your control notification handler code here
	int year=20;
	www(year);
}


void RegionInput::Onyr21() 
{
	// TODO: Add your control notification handler code here
	int year=21;
	www(year);
}

void RegionInput::Onyr22() 
{
	// TODO: Add your control notification handler code here
	int year=22;
	www(year);
}

void RegionInput::Onyr23() 
{
	// TODO: Add your control notification handler code here
	int year=23;
	www(year);
}

void RegionInput::Onyr24() 
{
	// TODO: Add your control notification handler code here
	int year=24;
	www(year);
}

void RegionInput::Onyr25() 
{
	// TODO: Add your control notification handler code here
	int year=25;
	www(year);
}

void RegionInput::Onyr26() 
{
	// TODO: Add your control notification handler code here
	int year=26;
	www(year);
}

void RegionInput::Onyr27() 
{
	// TODO: Add your control notification handler code here
	int year=27;
	www(year);
}

void RegionInput::Onyr28() 
{
	// TODO: Add your control notification handler code here
	int year=28;
	www(year);
}

void RegionInput::Onyr29() 
{
	// TODO: Add your control notification handler code here
	int year=29;
	www(year);
}

void RegionInput::Onyr30() 
{
	// TODO: Add your control notification handler code here
	int year=30;
	www(year);
}

void RegionInput::Onyr31() 
{
	// TODO: Add your control notification handler code here
	int year=31;
	www(year);
}

void RegionInput::Onyr32() 
{
	// TODO: Add your control notification handler code here
	int year=32;
	www(year);
}

void RegionInput::Onyr33() 
{
	// TODO: Add your control notification handler code here
	int year=33;
	www(year);
}

void RegionInput::Onyr34() 
{
	// TODO: Add your control notification handler code here
	int year=34;
	www(year);
}

void RegionInput::Onyr35() 
{
	// TODO: Add your control notification handler code here
	int year=35;
	www(year);
}

void RegionInput::Onyr36() 
{
	// TODO: Add your control notification handler code here
	int year=36;
	www(year);
}

void RegionInput::Onyr37() 
{
	// TODO: Add your control notification handler code here
	int year=37;
	www(year);
}

void RegionInput::Onyr38() 
{
	// TODO: Add your control notification handler code here
	int year=38;
	www(year);
}

void RegionInput::Onyr39() 
{
	// TODO: Add your control notification handler code here
	int year=39;
	www(year);
}

void RegionInput::Onyr40() 
{
	// TODO: Add your control notification handler code here
	int year=40;
	www(year);
}

void RegionInput::Onyr41() 
{
	// TODO: Add your control notification handler code here
	int year=41;
	www(year);
}

void RegionInput::Onyr42() 
{
	// TODO: Add your control notification handler code here
	int year=42;
	www(year);
}

void RegionInput::Onyr43() 
{
	// TODO: Add your control notification handler code here
	int year=43;
	www(year);
}

void RegionInput::Onyr44() 
{
	// TODO: Add your control notification handler code here
	int year=44;
	www(year);
}

void RegionInput::Onyr45() 
{
	// TODO: Add your control notification handler code here
	int year=45;
	www(year);
}

void RegionInput::Onyr46() 
{
	// TODO: Add your control notification handler code here
	int year=46;
	www(year);
}

void RegionInput::Onyr47() 
{
	// TODO: Add your control notification handler code here
	int year=47;
	www(year);
}

void RegionInput::Onyr48() 
{
	// TODO: Add your control notification handler code here
	int year=48;
	www(year);
}

void RegionInput::Onyr49() 
{
	// TODO: Add your control notification handler code here
	int year=49;
	www(year);
}

void RegionInput::Onyr50() 
{
	// TODO: Add your control notification handler code here
	int year=50;
	www(year);
}

void RegionInput::Onyr51() 
{
	// TODO: Add your control notification handler code here
	int year=51;
	www(year);
}

void RegionInput::Onyr52() 
{
	// TODO: Add your control notification handler code here
	int year=52;
	www(year);
}

void RegionInput::Onyr53() 
{
	// TODO: Add your control notification handler code here
	int year=53;
	www(year);
}

void RegionInput::Onyr54() 
{
	// TODO: Add your control notification handler code here
	int year=54;
	www(year);
}

void RegionInput::Onyr55() 
{
	// TODO: Add your control notification handler code here
	int year=55;
	www(year);
}

void RegionInput::Onyr56() 
{
	// TODO: Add your control notification handler code here
	int year=56;
	www(year);
}

void RegionInput::Onyr57() 
{
	// TODO: Add your control notification handler code here
	int year=57;
	www(year);
}

void RegionInput::Onyr58() 
{
	// TODO: Add your control notification handler code here
	int year=58;
	www(year);
}

void RegionInput::Onyr59() 
{
	// TODO: Add your control notification handler code here
	int year=59;
	www(year);
}

void RegionInput::Onyr60() 
{
	// TODO: Add your control notification handler code here
	int year=60;
	www(year);
}

void RegionInput::Onyr61() 
{
	// TODO: Add your control notification handler code here
	int year=61;
	www(year);
}

void RegionInput::Onyr62() 
{
	// TODO: Add your control notification handler code here
	int year=62;
	www(year);
}

void RegionInput::Onyr63() 
{
	// TODO: Add your control notification handler code here
	int year=63;
	www(year);
}

void RegionInput::Onyr64() 
{
	// TODO: Add your control notification handler code here
	int year=64;
	www(year);
}

void RegionInput::Onyr65() 
{
	// TODO: Add your control notification handler code here
	int year=65;
	www(year);
}

void RegionInput::Onyr66() 
{
	// TODO: Add your control notification handler code here
	int year=66;
	www(year);
}

void RegionInput::Onyr67() 
{
	// TODO: Add your control notification handler code here
	int year=67;
	www(year);
}

void RegionInput::Onyr68() 
{
	// TODO: Add your control notification handler code here
	int year=68;
	www(year);
}

void RegionInput::Onyr69() 
{
	// TODO: Add your control notification handler code here
	int year=69;
	www(year);
}

void RegionInput::Onyr70() 
{
	// TODO: Add your control notification handler code here
	int year=70;
	www(year);
}

void RegionInput::Onyr71() 
{
	// TODO: Add your control notification handler code here
	int year=71;
	www(year);
}

void RegionInput::Onyr72() 
{
	// TODO: Add your control notification handler code here
	int year=72;
	www(year);
}

void RegionInput::Onyr73() 
{
	// TODO: Add your control notification handler code here
	int year=73;
	www(year);
}

void RegionInput::Onyr74() 
{
	// TODO: Add your control notification handler code here
	int year=74;
	www(year);
}

void RegionInput::Onyr75() 
{
	// TODO: Add your control notification handler code here
	int year=75;
	www(year);
}

void RegionInput::Onyr76() 
{
	// TODO: Add your control notification handler code here
	int year=76;
	www(year);
}

void RegionInput::Onyr77() 
{
	// TODO: Add your control notification handler code here
	int year=77;
	www(year);
}

void RegionInput::Onyr78() 
{
	// TODO: Add your control notification handler code here
	int year=78;
	www(year);
}

void RegionInput::Onyr79() 
{
	// TODO: Add your control notification handler code here
	int year=79;
	www(year);
}

void RegionInput::Onyr80() 
{
	// TODO: Add your control notification handler code here
	int year=80;
	www(year);
}

void RegionInput::Onyr81() 
{
	// TODO: Add your control notification handler code here
	int year=81;
	www(year);
}

void RegionInput::Onyr82() 
{
	// TODO: Add your control notification handler code here
	int year=82;
	www(year);
}

void RegionInput::Onyr83() 
{
	// TODO: Add your control notification handler code here
	int year=83;
	www(year);
}

void RegionInput::Onyr84() 
{
	// TODO: Add your control notification handler code here
	int year=84;
	www(year);
}

void RegionInput::Onyr85() 
{
	// TODO: Add your control notification handler code here
	int year=85;
	www(year);
}

void RegionInput::Onyr86() 
{
	// TODO: Add your control notification handler code here
	int year=86;
	www(year);
}

void RegionInput::Onyr87() 
{
	// TODO: Add your control notification handler code here
	int year=87;
	www(year);
}

void RegionInput::Onyr88() 
{
	// TODO: Add your control notification handler code here
	int year=88;
	www(year);
}

void RegionInput::Onyr89() 
{
	// TODO: Add your control notification handler code here
	int year=89;
	www(year);
}

void RegionInput::Onyr90() 
{
	// TODO: Add your control notification handler code here
	int year=90;
	www(year);
}

void RegionInput::Onyr91() 
{
	// TODO: Add your control notification handler code here
	int year=91;
	www(year);
}

void RegionInput::Onyr92() 
{
	// TODO: Add your control notification handler code here
	int year=92;
	www(year);
}

void RegionInput::Onyr93() 
{
	// TODO: Add your control notification handler code here
	int year=93;
	www(year);
}

void RegionInput::Onyr94() 
{
	// TODO: Add your control notification handler code here
	int year=94;
	www(year);
}

void RegionInput::Onyr95() 
{
	// TODO: Add your control notification handler code here
	int year=95;
	www(year);
}

void RegionInput::Onyr96() 
{
	// TODO: Add your control notification handler code here
	int year=96;
	www(year);
}

void RegionInput::Onyr97() 
{
	// TODO: Add your control notification handler code here
	int year=97;
	www(year);
}

void RegionInput::Onyr98() 
{
	// TODO: Add your control notification handler code here
	int year=98;
	www(year);
}

void RegionInput::Onyr99() 
{
	// TODO: Add your control notification handler code here
	int year=99;
	www(year);
}

void RegionInput::Onyr100() 
{
	// TODO: Add your control notification handler code here
	int year=100;
	www(year);
}
void RegionInput::OnDblclkGisFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;
	
	num=m_GisFileName.GetCount();
	i=m_GisFileName.GetCurSel();
	
	CString fname;
	m_GisFileName.GetText(i,fname);
	m_GisFileName.DeleteString(i);	
	return;
}

void www(int year)
{
	char Fregion[120];
	FILE *region;
	sprintf(Fregion, "%s\\RegionYear", INTER);
	region = fopen(Fregion, "w");
	fprintf(region, "%d\n", year);
	fclose(region);

	RegionYear ww;

	if(ww.DoModal()==IDOK)
	{

	}
}


void RegionInput::OnKillfocusSimuYears() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEdit *Edt;
	CString id;
	int n, i;
	n=m_SimuYears;

	Edt=(CEdit *)GetDlgItem(IDC_yr1);
	i=n-1;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr2);
	i=n-2;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr3);
	i=n-3;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr4);
	i=n-4;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr5);
	i=n-5;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr6);
	i=n-6;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr7);
	i=n-7;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr8);
	i=n-8;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr9);
	i=n-9;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr10);
	i=n-10;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr11);
	i=n-11;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr12);
	i=n-12;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr13);
	i=n-13;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr14);
	i=n-14;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr15);
	i=n-15;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr16);
	i=n-16;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr17);
	i=n-17;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr18);
	i=n-18;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr19);
	i=n-19;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr20);
	i=n-20;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr21);
	i=n-21;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr22);
	i=n-22;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr23);
	i=n-23;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr24);
	i=n-24;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr25);
	i=n-25;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr26);
	i=n-26;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr27);
	i=n-27;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr28);
	i=n-28;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr29);
	i=n-29;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr30);
	i=n-30;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr31);
	i=n-31;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr32);
	i=n-32;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr33);
	i=n-33;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr34);
	i=n-34;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr35);
	i=n-35;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr36);
	i=n-36;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr37);
	i=n-37;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr38);
	i=n-38;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr39);
	i=n-39;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr40);
	i=n-40;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr41);
	i=n-41;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr42);
	i=n-42;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr43);
	i=n-43;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr44);
	i=n-44;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr45);
	i=n-45;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr46);
	i=n-46;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr47);
	i=n-47;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr48);
	i=n-48;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr49);
	i=n-49;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr50);
	i=n-50;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr51);
	i=n-51;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr52);
	i=n-52;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr53);
	i=n-53;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr54);
	i=n-54;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr55);
	i=n-55;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr56);
	i=n-56;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr57);
	i=n-57;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr58);
	i=n-58;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr59);
	i=n-59;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr60);
	i=n-60;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr61);
	i=n-61;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr62);
	i=n-62;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr63);
	i=n-63;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr64);
	i=n-64;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr65);
	i=n-65;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr66);
	i=n-66;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr67);
	i=n-67;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr68);
	i=n-68;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr69);
	i=n-69;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr70);
	i=n-70;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr71);
	i=n-71;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr72);
	i=n-72;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr73);
	i=n-73;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr74);
	i=n-74;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr75);
	i=n-75;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr76);
	i=n-76;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr77);
	i=n-77;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr78);
	i=n-78;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr79);
	i=n-79;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr80);
	i=n-80;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr81);
	i=n-81;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr82);
	i=n-82;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr83);
	i=n-83;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr84);
	i=n-84;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr85);
	i=n-85;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr86);
	i=n-86;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr87);
	i=n-87;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr88);
	i=n-88;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr89);
	i=n-89;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr90);
	i=n-90;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr91);
	i=n-91;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr92);
	i=n-92;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr93);
	i=n-93;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr94);
	i=n-94;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr95);
	i=n-95;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	Edt=(CEdit *)GetDlgItem(IDC_yr96);
	i=n-96;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 
	
	Edt=(CEdit *)GetDlgItem(IDC_yr97);
	i=n-97;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr98);
	i=n-98;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr99);
	i=n-99;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i); 

	Edt=(CEdit *)GetDlgItem(IDC_yr100);
	i=n-100;
	if(i>=0) i =1;
	else i=0;
	Edt->EnableWindow(i);

	UpdateData(FALSE);

	//m_FarmFile=NULL;


}

void RegionInput::OnSetfocusRegionName() 
{
	// TODO: Add your control notification handler code here
	int ContinentCode, CountryCode;
	char StateName[200];

	UpdateData(TRUE);
			
	CString Fregion;
	FILE *region;
	Fregion.Format("%s\\PassName", INTER);
	region = fopen(Fregion, "r");
	if (region==NULL)
	{
		char err[120];
		sprintf(err, "Can not open %s", Fregion);
		AfxMessageBox(err);
		exit(0); 
	}

	fscanf(region, "%d %d", &ContinentCode, &CountryCode);
	fscanf(region, "%s", StateName);
	fscanf(region, "%s %s", Root1, Root2);
	fscanf(region, "%s", RootName);
	fscanf(region, "%s", WholeName);
	fclose (region);		
	
	m_RegionName.Format("%s", ConName);
		
	//m_FarmFile = 0;
	
	UpdateData(FALSE);
	
}

void RegionInput::OnAccept() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(ManageFlag==0)
	{
		AfxMessageBox("Please define farming management for each year");
		return;
	}

/*	if(m_StartYear==-1)
	{
		CString note;
		note.Format("Please define start year");
		AfxMessageBox(note);
		return;
	}

	m_SimulatedCells = m_TotalCells - m_StartGridID + 1;
	
	char states[120];
	FILE *cs;
	sprintf(states, "%s\\PassName", INTER);
	cs = fopen(states, "r");
	if(cs==NULL)
		{
			CString note;
			note.Format("Can not open %s", states);
			AfxMessageBox(note);
			exit(0);
		}
	fscanf(cs, "%d %d", &country_code, &state_code);
	fscanf(cs, "%s", r_Province);
	fscanf(cs, "%s %s", Root1, Root2);
	fscanf(cs, "%s", RootName);
	fscanf(cs, "%s", WholeName);
	fclose (cs);

	UpdateData(TRUE);

	if(m_SimuYears==0)
	{
		AfxMessageBox("Please define number of simulated years");
		return;
	}

	if(m_StartYear==0)
	{
		AfxMessageBox("Please define the start year");
		return;
	}

	FarmFile=1;
	
	char XZY[20];
	sprintf(XZY, "%s",  m_RegionName);
	int LL=strlen(XZY);

	if(LL>=12) 
	{
		Glean_String(XZY, 0, 11, XZY);
	}
	else
	{
		int RLL=12-LL;			
		for(int i=1;i<=RLL;i++) sprintf(XZY, "%s_", XZY);
	}

	//m_RegionName.Format("%s", XZY);

	//sprintf(r_DatabaseName, "%s", m_RegionName); 
	sprintf(r_DatabaseName, "%s", XZY); 

	sprintf(r_Country, "%s", m_RegionName);
	sprintf(r_Scenario, "%s", m_ScenarioName);
	
	CO2 = 350.0;//m_AtmoCO2;
	AirTemp = 0.0;//m_AirTemp;
	YieldIncrease = 1.0;//m_YieldIncrease;
	
	r_ViewMode = 0;
	sprintf(r_DatabaseName, "%s", r_DatabaseName);

	DailyRecord = m_DailyItem.GetCurSel();
	MajorConcern = m_MajorTarget.GetCurSel();
	if(MajorConcern>5) MajorConcern = 1;
*/
/*	char Fregion[120];
	FILE *region;
	sprintf(Fregion, "%s\\region", INTER);
	region = fopen(Fregion, "w");

	fprintf(region, "%d %d %d\n", region_code, country_code, state_code);
	fprintf(region, "%s\n", r_Country);
	fprintf(region, "%s %s\n", Root1, Root2);
	fprintf(region, "%s\n", WholeName);//r_DatabaseName);
	fprintf(region, "%s\n", r_Scenario);
	fprintf(region, "%d\n", 0);
	fprintf(region, "%f %f %f\n", CO2, AirTemp, YieldIncrease);
	fprintf(region, "%d\n", MajorConcern);
	fprintf(region, "%d\n", DailyRecord);
	fprintf(region, "%d\n", m_SimuYears);
	fprintf(region, "%d\n", m_StartYear);
	fprintf(region, "%d\n", r_ViewMode); 
	fprintf(region, "%d\n", FarmFile);
	fprintf(region, "%d\n", m_DataFormat);
	fprintf(region, "%d\n", m_StartGridID);
	fprintf(region, "%d\n", m_TotalCells);
	fprintf(region, "%d\n", m_SimulatedCells);
	fprintf(region, "%d\n", SimuMode);
	fprintf(region, "%d\n", m_Drought);
	fclose(region);*/
}

void RegionInput::OnSaveregion() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CFileDialog ask(false, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC regional input data file (*.drd)|*.drd|All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	
	ask.DoModal();
	char cst[255];
	
	CString fname;
	int l, years, i;
	fname = ask.GetPathName();
	l=fname.GetLength();
	if (l==0) return;

	if (fname.Right(4)!=".drd") fname=fname+".drd";
	sprintf(cst,"%s",fname);

	int RegionCode, CountryCode, StateCode, DBType, MajorConcern, DailyRecord, SimuYears, StartYear, ViewMode; 
	int FarmFile, GlobeData, StartGridID, TotalCells, SimulatedCells;
	char r_Country[200]="None", js[200]="None", mDatabaseName[200]="None", r_Scenario[200]="None";
	float r_CO2, r_AirTemp, r_YieldIncrease, jf;
	float y_AtmoCO2, y_AirTemp, y_YieldIncrease, y_LitterBackField, y_AnimalManure, y_FertilizerRate, y_IrriIndex, y_RainChange, y_MicroIndex;
	int y_Tillage, Drainage, Autofert, y_ShallowFlood, y_UplandRice, y_SlowReleaseDays;
	int FloodAlter, TillAlter, IrriAlter, RicePlantAlter, jd;
	float y_WaterDemand, y_MaxTemp, y_CropCN;

	CString wholename;
	m_GisFileName.GetText(0,wholename);

	MajorConcern=m_MajorTarget.GetCurSel();
	DailyRecord=m_DailyItem.GetCurSel();
	
	CString DB, RegionFile;
	FILE *db, *rf;

	RegionFile.Format("%s", fname);
	
	rf = fopen(RegionFile, "w");
	if(rf==NULL)
	{
		CString note;
		note.Format("Can not create file %s", RegionFile);
		AfxMessageBox(note);
		exit(0);
	}

	fprintf(rf, "%s\n", m_RegionName);
	fprintf(rf, "%s\n", wholename);
	fprintf(rf, "%s\n", m_ScenarioName);
	fprintf(rf, "%d\n", m_DataFormat);
	fprintf(rf, "%d %d %d %d\n", MajorConcern, DailyRecord, m_SimuYears, m_StartYear);
	fprintf(rf, "%d\n", m_StartGridID);
	fprintf(rf, "%d %d %d\n", m_TotalCells, m_SimulatedCells, SimuMode);
	fprintf(rf, "%d\n\n", m_Drought);

/*	char Fregion[120];
	FILE *region;
	sprintf(Fregion, "%s\\RegionYear", INTER);
	region = fopen(Fregion, "r");
	if(region==NULL)
	{
		CString note;
		note.Format("Cannot open file %s", Fregion);
		AfxMessageBox(note);
		exit(0);
	}
	fscanf(region, "%d", &years);
	fclose(region);*/

	years = m_SimuYears;

	fprintf(rf, "%d\n\n", years); 

	for(i=1; i<=years; i++)
	{
		char RegionYr[200];
		FILE* ry;

		sprintf(RegionYr, "%s\\region_yr%d", INTER, i);
		ry = fopen(RegionYr, "r");
		if(ry==NULL)
		{
			CString note;
			note.Format("Cannot open file %s", RegionYr);
			AfxMessageBox(note);
			exit(0);
		}		

		fscanf(ry, "%f %f %f", &y_AtmoCO2, &y_AirTemp, &y_RainChange);
		fscanf(ry, "%f %f %f", &y_LitterBackField, &y_FertilizerRate, &y_AnimalManure);
		fscanf(ry, "%d %d %d", &Autofert, &FloodAlter, &TillAlter);	
		fscanf(ry, "%f %f %f", &y_YieldIncrease, &y_WaterDemand, &y_MaxTemp);
		fscanf(ry, "%f %f %f %f %f", &y_CropCN, &y_IrriIndex, &jf, &jf, &jf);
		fscanf(ry, "%d %d %d %d %d", &IrriAlter, &RicePlantAlter, &jd, &jd, &jd);
		fclose(ry);

		fprintf(rf, "%f %f %f\n", y_AtmoCO2, y_AirTemp, y_RainChange);
		fprintf(rf, "%f %f %f\n", y_LitterBackField, y_FertilizerRate, y_AnimalManure);
		fprintf(rf, "%d %d %d\n", Autofert, FloodAlter, TillAlter);	
		fprintf(rf, "%f %f %f\n", y_YieldIncrease, y_WaterDemand, y_MaxTemp);
		fprintf(rf, "%f %f %f %f %f\n", y_CropCN, y_IrriIndex, 0.0, 0.0, 0.0);
		fprintf(rf, "%d %d %d %d %d\n", IrriAlter, RicePlantAlter, 0, 0, 0);

	/*	fscanf(ry, "%f %f %f", &y_AtmoCO2, &y_AirTemp, &y_YieldIncrease);	
		fscanf(ry, "%f %f %f", &y_LitterBackField, &y_AnimalManure, &jf);
		fscanf(ry, "%f %f", &y_FertilizerRate, &y_IrriIndex);
		fscanf(ry, "%d", &y_Tillage); 	
		fscanf(ry, "%d", &Drainage);	
		fscanf(ry, "%d", &y_ShallowFlood);
		fscanf(ry, "%d", &y_UplandRice);
		fscanf(ry, "%d", &Autofert);
		fscanf(ry, "%d", &y_SlowReleaseDays);
		fscanf(ry, "%f", &y_RainChange);
		fscanf(ry, "%f", &y_MicroIndex);
		
		fclose(ry);

		fprintf(rf, "%f %f %f\n", y_AtmoCO2, y_AirTemp, y_YieldIncrease);	
		fprintf(rf, "%f %f %f\n", y_LitterBackField, y_AnimalManure, 0.0);
		fprintf(rf, "%f %f\n", y_FertilizerRate, y_IrriIndex);
		fprintf(rf, "%d\n", y_Tillage); 	
		fprintf(rf, "%d\n", Drainage);	
		fprintf(rf, "%d\n", y_ShallowFlood);
		fprintf(rf, "%d\n", y_UplandRice);
		fprintf(rf, "%d\n", Autofert);
		fprintf(rf, "%d\n", y_SlowReleaseDays);
		fprintf(rf, "%f\n", y_RainChange);
		fprintf(rf, "%f\n\n", y_MicroIndex);*/
	}

	fclose(rf);

}


void RegionInput::OnOpenregion() 
{
	// TODO: Add your control notification handler code here
	int i, RegionCode, CountryCode, StateCode, DBType, MajorConcern, DailyRecord, ViewMode, FarmFile, GlobeData, years;
	float r_CO2, r_AirTemp, r_YieldIncrease, jf;
	char RegionName[255],RegionName2[255],ScenarioName[255];
	float y_AtmoCO2, y_AirTemp, y_YieldIncrease, y_RainChange, y_MicroIndex, y_WaterDemand, y_MaxTemp;	
	float y_LitterBackField, y_AnimalManure, y_FertilizerRate, y_IrriIndex, y_CropCN;
	int y_Tillage, Drainage, Autofert, y_ShallowFlood, y_UplandRice, y_SlowReleaseDays;
	int FloodAlter, TillAlter, IrriAlter, RicePlantAlter, jd;

	CFileDialog ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "DNDC data file (*.drd)|*.drd|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt|All Files (*.*)|*.*||", NULL );
	
	ask.DoModal();
	char cst[255];
	strcpy(cst,ask.GetPathName());
	if (strlen(cst)==0) return;

	CString DB, RegionFile;
	FILE *rf;

	RegionFile.Format("%s", cst);
	
	rf = fopen(RegionFile, "r");
	if(rf==NULL)
	{
		CString note;
		note.Format("Can not open file %s", RegionFile);
		AfxMessageBox(note);
		exit(0);
	}

	fscanf(rf, "%s", RegionName);
	fscanf(rf, "%s", WholeName);
	fscanf(rf, "%s", ScenarioName);
	fscanf(rf, "%d", &m_DataFormat);
	fscanf(rf, "%d %d %d %d", &MajorConcern, &DailyRecord, &m_SimuYears, &m_StartYear);
	fscanf(rf, "%d", &m_StartGridID);
	fscanf(rf, "%d %d %d", &m_TotalCells, &m_SimulatedCells, &SimuMode);
	fscanf(rf, "%d", &m_Drought);

/*	fscanf(rf, "%d %d %d", &RegionCode, &CountryCode, &StateCode);
	fscanf(rf, "%s %s %s %s", RegionName, RegionName2, WholeName, ScenarioName);
	fscanf(rf, "%d %f %f %f", &DBType, &r_CO2, &r_AirTemp, &r_YieldIncrease);
	fscanf(rf, "%d %d %d %d", &MajorConcern, &DailyRecord, &m_SimuYears, &m_StartYear);
	fscanf(rf, "%d %d %d %d", &ViewMode, &FarmFile, &GlobeData, &m_StartGridID);
	fscanf(rf, "%d %d %d", &m_TotalCells, &m_SimulatedCells, &SimuMode);*/

	fscanf(rf, "%d", &years); 

	for(i=1; i<=years; i++)
	{
		/*fscanf(rf, "%f %f %f", &y_AtmoCO2, &y_AirTemp, &y_YieldIncrease);	
		fscanf(rf, "%f %f %f", &y_LitterBackField, &y_AnimalManure, &jf);
		fscanf(rf, "%f %f", &y_FertilizerRate, &y_IrriIndex);
		fscanf(rf, "%d", &y_Tillage); 	
		fscanf(rf, "%d", &Drainage);	
		fscanf(rf, "%d", &y_ShallowFlood);
		fscanf(rf, "%d", &y_UplandRice);
		fscanf(rf, "%d", &Autofert);
		fscanf(rf, "%d", &y_SlowReleaseDays);
		fscanf(rf, "%f", &y_RainChange);
		fscanf(rf, "%f", &y_MicroIndex);*/

		fscanf(rf, "%f %f %f", &y_AtmoCO2, &y_AirTemp, &y_RainChange);
		fscanf(rf, "%f %f %f", &y_LitterBackField, &y_FertilizerRate, &y_AnimalManure);
		fscanf(rf, "%d %d %d", &Autofert, &FloodAlter, &TillAlter);	
		fscanf(rf, "%f %f %f", &y_YieldIncrease, &y_WaterDemand, &y_MaxTemp);
		fscanf(rf, "%f %f %f %f %f", &y_CropCN, &y_IrriIndex, &jf, &jf, &jf);
		fscanf(rf, "%d %d %d %d %d", &IrriAlter, &RicePlantAlter, &jd, &jd, &jd);

		CString RegYr;
		FILE* regyr;
		RegYr.Format("%s\\Inter\\Region_yr%d", OUTPUT, i);
		regyr = fopen(RegYr, "w");
		if(regyr==NULL)
		{
			CString note;
			note.Format("Can not create file %s", RegYr);
			AfxMessageBox(note);
			exit(0);
		}

		fprintf(regyr, "%f %f %f\n", y_AtmoCO2, y_AirTemp, y_RainChange);
		fprintf(regyr, "%f %f %f\n", y_LitterBackField, y_FertilizerRate, y_AnimalManure);
		fprintf(regyr, "%d %d %d\n", Autofert, FloodAlter, TillAlter);	
		fprintf(regyr, "%f %f %f\n", y_YieldIncrease, y_WaterDemand, y_MaxTemp);
		fprintf(regyr, "%f %f %f %f %f\n", y_CropCN, y_IrriIndex, 0.0, 0.0, 0.0);
		fprintf(regyr, "%d %d %d %d %d\n", IrriAlter, RicePlantAlter, 0, 0, 0);

		fclose(regyr);
	}

	fclose(rf);
	
	m_RegionName.Format("%s", RegionName);
	m_ScenarioName.Format("%s", ScenarioName);

	m_MajorTarget.SetCurSel(MajorConcern);
	m_DailyItem.SetCurSel(DailyRecord);
	m_SimuMode.SetCurSel(SimuMode);
	//m_DataFormat = GlobeData;

	//////////////////////////////////
	m_GisFileName.InsertString(0, WholeName);
	
	UpdateData(FALSE);


	////////////////////////////////////////////////////////////////

/*
	char XZY[20];
	sprintf(XZY, "%s",  RegionName);
	int LL=strlen(XZY);

	if(LL>=12) 
	{
		Glean_String(XZY, 0, 11, XZY);
	}
	else
	{
		int RLL=12-LL;			
		for(int i=1;i<=RLL;i++) sprintf(XZY, "%s_", XZY);
	}
 
	sprintf(r_DatabaseName, "%s", XZY); 

	sprintf(r_Country, "%s", m_RegionName);
	sprintf(r_Scenario, "%s", m_ScenarioName);
	
	CO2 = 350.0;//m_AtmoCO2;
	AirTemp = 0.0;//m_AirTemp;
	YieldIncrease = 1.0;//m_YieldIncrease;
	
	r_ViewMode = 0;
	sprintf(r_DatabaseName, "%s", r_DatabaseName);

	DailyRecord = m_DailyItem.GetCurSel();
	MajorConcern = m_MajorTarget.GetCurSel();
	if(MajorConcern>5) MajorConcern = 1;

	SimuMode = m_SimuMode.GetCurSel();

	ManageFlag=1;

	char OPP[120];
	FILE *region;
	sprintf(OPP, "%s\\region_input", INTER);
	region = fopen(OPP, "w");
	if (region==NULL) note(1, OPP);

	fprintf(region, "%d %d %d\n", 0, country_code, state_code);
	fprintf(region, "%s\n", r_Country);
	fprintf(region, "%s %s\n", Root1, Root2);
	fprintf(region, "%s\n", WholeName);//r_DatabaseName);
	fprintf(region, "%s\n", r_Scenario);
	fprintf(region, "%d\n", 0);
	fprintf(region, "%f %f %f\n", CO2, AirTemp, YieldIncrease);
	fprintf(region, "%d\n", MajorConcern);
	fprintf(region, "%d\n", DailyRecord);
	fprintf(region, "%d\n", m_SimuYears);
	fprintf(region, "%d\n", m_StartYear);
	fprintf(region, "%d\n", r_ViewMode); 
	fprintf(region, "%d\n", FarmFile);
	fprintf(region, "%d\n", m_DataFormat);
	fprintf(region, "%d\n", m_StartGridID);
	fprintf(region, "%d\n", m_TotalCells);
	fprintf(region, "%d\n", m_SimulatedCells);
	fprintf(region, "%d\n", SimuMode);
	fprintf(region, "%d\n", m_Drought);
	fclose(region);*/

/*	//////////////////////////////////////////
	char WPP[120];
	FILE *wpp;
	sprintf(WPP, "\\DNDC\\Inter\\region_input"); //this shouldn't be hard coded, but it's commented
	wpp = fopen(WPP, "w");
	if(wpp==NULL) note(1, WPP); 

	fprintf(wpp, "%d %d %d\n", 0, 0, 0);//wpp_code, country_code, state_code);
	fprintf(wpp, "%s\n", RegionName);//r_Country);
	fprintf(wpp, "%s %s\n", "None", "None");//Root1, Root2);
	fprintf(wpp, "%s\n", WholeName);//r_DatabaseName);
	fprintf(wpp, "%s\n", ScenarioName);
	fprintf(wpp, "%d\n", 0);
	fprintf(wpp, "%f %f %f\n", y_AtmoCO2, y_AirTemp, y_YieldIncrease);
	fprintf(wpp, "%d\n", MajorConcern);
	fprintf(wpp, "%d\n", DailyRecord);
	fprintf(wpp, "%d\n", m_SimuYears);
	fprintf(wpp, "%d\n", m_StartYear);
	fprintf(wpp, "%d\n", SimuMode); 
	fprintf(wpp, "%d\n", 0);
	fprintf(wpp, "%d\n", m_DataFormat);
	fprintf(wpp, "%d\n", m_StartGridID);
	fprintf(wpp, "%d\n", m_TotalCells);
	fprintf(wpp, "%d\n", m_SimulatedCells);
	fprintf(wpp, "%d\n", SimuMode);
	fprintf(wpp, "%d\n", m_Drought);
	fclose(wpp);*/
	////////////////////////////////////////////

	CString CP;
	int L1, T=0, G[20]={0,0};

	int LL=strlen(WholeName);
	for(i=LL; i>=0; i--)
	{
		if(WholeName[i]=='_') 
		{
			L1=i-1;
			break;
		}
	}

	for(i=0; i<=LL; i++)
	{
		if(WholeName[i]=='\\') 
		{
			T++;
			G[T]=i;
		}
	}

	Glean_String(WholeName, G[T]+1, L1, ConName);
	Glean_String(WholeName, 0, G[T], RootName);
	Glean_String(WholeName, 0, G[T-1], Root1);
	Glean_String(WholeName, 0, G[T-2], Root2);
	
	CP.Format("%s", ConName);

	RegionCode = 0;

	CString NPP;
	FILE *npp;

	NPP.Format("%s\\PassName", INTER);
	npp = fopen(NPP, "w");
	if (npp==NULL) note(1, NPP);
	
	fprintf(npp, "%d %d\n", -1, 0);
	fprintf(npp, "%s\n", CP);
	fprintf(npp, "%s %s\n", Root1, Root2);
	fprintf(npp, "%s\n", RootName);
	fprintf(npp, "%s\n", WholeName);
	fclose (npp);

	OnKillfocusSimuYears();

	CString RegYr;
	FILE* regyr;
	RegYr.Format("%s\\Inter\\RegionInputFileFlag", OUTPUT);
	regyr = fopen(RegYr, "w");
	if(regyr==NULL)
	{
		CString note;
		note.Format("Can not create file %s", RegYr);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(regyr, "%d\n", 1);
	fclose(regyr);

	CString CYW;
	FILE* cyw;
	CYW.Format("%s\\TargetYr", INTER);
	cyw=fopen(CYW, "w");
	if(cyw==NULL) note(1, CYW);
	fprintf(cyw, "%d", m_StartYear);
	fclose(cyw);

	ManageFlag=1;

	OnButton1();
}


BOOL RegionInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ConvertGo.SetRange(0,100);
	
	////////////////////////////////////////////////////////
	CString RegYr;
	FILE* regyr;
	RegYr.Format("%s\\Inter\\RegionInputFileFlag", OUTPUT);
	regyr = fopen(RegYr, "w");
	if(regyr==NULL)
	{
		CString note;
		note.Format("Can not create file %s", RegYr);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(regyr, "%d\n", 0);
	fclose(regyr);

	m_DailyItem.SetCurSel(0);

	CString DM;
	FILE *dm;
	int DroughtMode=0;
	DM.Format("%s\\DroughtMode", INTER);
	dm=fopen(DM, "r");
	fscanf(dm, "%d", &DroughtMode);
	fclose(dm);

	m_Drought = DroughtMode;

	AcceptOK = 0;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
void RegionInput::OnEditchangeMajorTarget() 
{
	// TODO: Add your control notification handler code here
	OnKillfocusSimuYears();
}*/

void RegionInput::OnKillfocusMajorTarget() 
{
	// TODO: Add your control notification handler code here
	OnKillfocusSimuYears();
}

void RegionInput::OnKillfocusRegionName() 
{
	// TODO: Add your control notification handler code here
	char ww[300], bbb[100];
	int jd, k=0, j=0, item=0;
	FILE* cc;
	cc = fopen(WholeName, "r");
	if(cc==NULL)
	{
		CString note;
		note.Format("Cannot find file %s", WholeName);
		AfxMessageBox(note);
		return;
	}

	fgets(ww, 300, cc);
	fscanf(cc, "%d", &item);
	fgets(ww, 300, cc);
	fgets(ww, 300, cc);
	for(;;)
	{
		if(fscanf(cc, "%d", &jd)!=1) break;
		else 
		{			
			j++;
			for(int z=1;z<=item;z++) fscanf(cc, "%s", bbb);
			if(m_StartGridID==j) 
				k=0;
			k++;
		}
	}

	m_TotalCells = j;
	m_SimulatedCells = k;

	fclose(cc);

	UpdateData(FALSE);
}

void RegionInput::OnFarming()//global data counting 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
/*	if(m_SpaceFarming==1)
	{
		char ww[300], js[50];
		int jd, k=0, j=0;
		float jf;
		FILE* cc;
		cc = fopen(FileName, "r");
		if(cc==NULL)
		{
			CString note;
			note.Format("Cannot find file %s", FileName);
			AfxMessageBox(note);
			return;
		}

		fgets(ww, 300, cc);
		for(;;)
		{
			if(fscanf(cc, "%d %d %s %f %f %s %f %f %f %f %f %f %f %f %f %f %d %d %d",
				&jd,&jd,js,&jf,&jf,js,&jf,&jf,&jf,&jf,&jf,&jf,&jf,&jf,&jf,&jf,&jd,&jd,&jd)!=19) break;
			else 
			{
				j++;
				if(m_StartGridID==jd) k=0;
				k++;
			}
		}

		m_TotalCells = j;
		m_SimulatedCells = k;

		UpdateData(FALSE);

	}
*/
}

void RegionInput::OnChangeStartGridID() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_SimulatedCells = m_TotalCells - m_StartGridID + 1;
	UpdateData(FALSE);
}

void RegionInput::OnOK() 
{
	// TODO: Add extra validation here

	if(AcceptOK==0)
	{
		AfxMessageBox("Please click Accept first");
		return;
	}
	
	OnAccept();

	char LB[200];
	FILE* ddb;
	sprintf(LB,"%s\\Inter\\UnitSystem", OUTPUT);
	ddb=fopen(LB, "w");
	if(ddb==NULL) note(1, LB);
	fprintf(ddb, "%d", 0);
	fclose(ddb);

	CDialog::OnOK();
}

void RegionInput::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_StartYear==-1)
	{
		CString note;
		note.Format("Please define start year");
		AfxMessageBox(note);
		return;
	}

	m_SimulatedCells = m_TotalCells - m_StartGridID + 1;
	
	char states[120];
	FILE *cs;
	sprintf(states, "%s\\PassName", INTER);
	cs = fopen(states, "r");
	if(cs==NULL)
		{
			CString note;
			note.Format("Can not open %s", states);
			AfxMessageBox(note);
			exit(0);
		}
	fscanf(cs, "%d %d", &country_code, &state_code);
	fscanf(cs, "%s", r_Province);
	fscanf(cs, "%s %s", Root1, Root2);
	fscanf(cs, "%s", RootName);
	fscanf(cs, "%s", WholeName);
	fclose (cs);

	UpdateData(TRUE);

	if(m_SimuYears==0)
	{
		AfxMessageBox("Please define number of simulated years");
		return;
	}

	if(m_StartYear==0)
	{
		AfxMessageBox("Please define the start year");
		return;
	}

	
	FarmFile=1;
	
	char XZY[20];
	sprintf(XZY, "%s",  m_RegionName);
	int LL=strlen(XZY);

	if(LL>=12) 
	{
		Glean_String(XZY, 0, 11, XZY);
	}
	else
	{
		int RLL=12-LL;			
		for(int i=1;i<=RLL;i++) sprintf(XZY, "%s_", XZY);
	}

	//m_RegionName.Format("%s", XZY);

	//sprintf(r_DatabaseName, "%s", m_RegionName); 
	sprintf(r_DatabaseName, "%s", XZY); 

	sprintf(r_Country, "%s", m_RegionName);
	sprintf(r_Scenario, "%s", m_ScenarioName);
	
	CO2 = 350.0;//m_AtmoCO2;
	AirTemp = 0.0;//m_AirTemp;
	YieldIncrease = 1.0;//m_YieldIncrease;
	
	r_ViewMode = 0;
	sprintf(r_DatabaseName, "%s", r_DatabaseName);

	DailyRecord = m_DailyItem.GetCurSel();
	MajorConcern = m_MajorTarget.GetCurSel();
	if(MajorConcern>5) MajorConcern = 1;

	SimuMode = m_SimuMode.GetCurSel();

	ManageFlag=1;

	char OPP[120];
	FILE *region;
	sprintf(OPP, "%s\\region_input", INTER);
	region = fopen(OPP, "w");
	if (region==NULL) note(1, OPP);

	fprintf(region, "%d %d %d\n", region_code, country_code, state_code);
	fprintf(region, "%s\n", r_Country);
	fprintf(region, "%s %s\n", Root1, Root2);
	fprintf(region, "%s\n", WholeName);//r_DatabaseName);
	fprintf(region, "%s\n", r_Scenario);
	fprintf(region, "%d\n", 0);
	fprintf(region, "%f %f %f\n", CO2, AirTemp, YieldIncrease);
	fprintf(region, "%d\n", MajorConcern);
	fprintf(region, "%d\n", DailyRecord);
	fprintf(region, "%d\n", m_SimuYears);
	fprintf(region, "%d\n", m_StartYear);
	fprintf(region, "%d\n", r_ViewMode); 
	fprintf(region, "%d\n", FarmFile);
	fprintf(region, "%d\n", m_DataFormat);
	fprintf(region, "%d\n", m_StartGridID);
	fprintf(region, "%d\n", m_TotalCells);
	fprintf(region, "%d\n", m_SimulatedCells);
	fprintf(region, "%d\n", SimuMode);
	fprintf(region, "%d\n", m_Drought);
	fclose(region);
}

void RegionInput::OnDataConversion() 
{
	// TODO: Add your control notification handler code here
	CString RP;

	CString Pname;
	int i, FarmFile, ClimItem, S_CountryCode, StartCell=1;
	int cell_ID1, cell_ID2, cell_ID3, cell_ID4, cell_ID5, cell_ID6, cell_ID7, cell_ID8, cell_ID9;
	int cell_ID10, cell_ID11, cell_ID12, country_ID, S_OnlyRice, S_SoilYear, CropID[80]={0,0};
	int landtype, GDB, jd, TotalCells, SimulatedCells, ifdaily, landuse, ii, qq, id, column, raw, continent_ID;
	int crop_type_number, DryYear, MidYear, WetYear, S_ViewMode;
	int CropSystemNumber0,CropSystemNumber1,CropSystemNumber2,CropSystemNumber3,CropSystemNumber4,CropSystemNumber5,CropSystemNumber6;
	int CropNumber0;
	char KK[500], CropSystemName[160][50], CropSystemID[160][30], county_name[220], CropName[50][30];
	char climfileID[250], CountryName[120], ScenarioName[120], js[50];
	
	float S_longitude, S_latitude, S_RainN, S_crop_ha[160];
	float Kmax_SOC[5], Kmin_SOC[5],Kmax_clay[5], Kmin_clay[5];
	float Kmax_pH[5], Kmin_pH[5], Kmax_BD[5], Kmin_BD[5];	
	float max_SOC, min_SOC,	max_clay, max_pH, min_pH, max_BD, min_BD;
	
	float FertRate, IrriRate, SCS[50];
	
	float CountyHa, SnowPack, FertNormalizationIndex;
	
	char File1[200],File2[200],File3[200],File4[200],File5[200],File6[200],File7[200],File8[200];
	char File9[200],File10[200],File11[200],File12[200],File40[200];
	float cattle, sheep, pig, poultry, people, SlopeIndex, SoilQuality;
	char PlantHarvestDates[200], ResidueFraction[200], Tillage[200], FertDates[200], ManureRate[200];
	char Flooding[200], CropPara[200];
	CString CropCode, msg;
	FILE *f1, *f2, *f3, *f4, *f5, *f6, *f7, *f8, *f10, *f11, *f12, *CC, *f40;//, *f9
	CString Fregion;
	FILE *region;

	UpdateData(TRUE);

/*	//char WW[250];
	m_GisFileName.GetText(0, WholeName);
	
	CString CP;
	int L1, T=0, G[20]={0,0};

	int LL=strlen(WholeName);
	for(i=LL; i>=0; i--)
	{
		if(WholeName[i]=='_') 
		{
			L1=i-1;
			break;
		}
	}

	for(i=0; i<=LL; i++)
	{
		if(WholeName[i]=='\\') 
		{
			T++;
			G[T]=i;
		}
	}

	Glean_String(WholeName, G[T]+1, L1, ConName);
	Glean_String(WholeName, 0, G[T], RootName);
	Glean_String(WholeName, 0, G[T-1], Root1);
	Glean_String(WholeName, 0, G[T-2], Root2);

	////////////////////////////
	CString PassName;
	FILE* pn;
	PassName.Format("%s\\Inter\\PassName", OUTPUT);
	pn=fopen(PassName, "w");
	if(pn==NULL) note(1, PassName);
	fprintf("%s %s %s %s %s\n", WholeName, ConName, RootName, Root1, Root2);
	fclose(pn);
*/
	Pname.Format("%s", RootName);	
	
	sprintf(File1, "%s\\%s_ClimateSoil.txt", RootName, ConName);//location, climate and soil
	sprintf(File2, "%s\\%s_CropArea.txt", RootName, ConName);//crop ha	
	sprintf(File3, "%s\\%s_PlantingHarvestDates.txt", RootName, ConName);//planting and harvest dates
	sprintf(File4, "%s\\%s_ResidueManagement.txt", RootName, ConName);//crop residue incorporation fraction
	sprintf(File5, "%s\\%s_Tillage.txt", RootName, ConName);//tilling date and depth
	sprintf(File6, "%s\\%s_Fertilization.txt", RootName, ConName);//fertilizer application date, type, rate
	sprintf(File7, "%s\\%s_ManureAmendment.txt", RootName, ConName);//manure application date, N and C/N
	sprintf(File8, "%s\\%s_Flooding.txt", RootName, ConName);//flooding dates and method
	//sprintf(File9, "%s\\%s_Irrigation.txt", RootName, ConName);//irrigated percentage
	sprintf(File12, "%s\\%s_CropParameter.txt", Pname, ConName);//crop max yield_TDD_WaterDEmand

	f1=fopen(File1, "r");
	if (f1==NULL) note(0, File1);
	f2=fopen(File2, "r");
	if (f2==NULL) note(0, File2);
	f3=fopen(File3, "r");
	if (f3==NULL) note(0, File3);
	f4=fopen(File4, "r");
	if (f4==NULL) note(0, File4);
	f5=fopen(File5, "r");
	if (f5==NULL) note(0, File5);	
	f6=fopen(File6, "r");
	if (f6==NULL) note(0, File6);
	f7=fopen(File7, "r");
	if (f7==NULL) note(0, File7);
	f8=fopen(File8, "r");
	if (f8==NULL) note(0, File8);
	//f9=fopen(File9, "r");
	//if (f9==NULL) note(0, File9);
	f12=fopen(File12, "r");
	if (f12==NULL) note(0, File12);

	
#ifdef MANURE
	sprintf(File10, "%s\\%s_Livestock.txt", Pname, ConName);//number of animal farms
	f10=fopen(File10, "r");
	if (f10==NULL) note(0, File10);
#endif

#ifdef HYDRO
	sprintf(File11, "%s\\%s_Hydrology.txt", Pname, ConName);//soil hydrological data supporting SCS and MUSEL
	f11=fopen(File11, "r");
	if (f11==NULL) note(0, File11);
#endif

	fgets(KK, 300, f1);//ClimateSoil
	fscanf(f1, "%d", &ClimItem);
	for(i=1; i<=ClimItem; i++) fscanf(f1, "%s", js);
	fscanf(f1, "%d", &ClimItem);
	for(i=1; i<=ClimItem; i++) fscanf(f1, "%s", js);

	fgets(KK, 500, f2);//crop area
	fscanf(f2, "%d", &CropSystemNumber0);
	for(i=1; i<=CropSystemNumber0; i++) fscanf(f2, "%s", CropSystemName[i]);	
	fscanf(f2, "%s", js);
	for(i=1; i<=CropSystemNumber0; i++) fscanf(f2, "%s", CropSystemID[i]);
	
	fgets(KK, 500, f3);//planting, harvest
	fscanf(f3, "%d", &CropSystemNumber1);
	for(i=1; i<=CropSystemNumber1; i++) fscanf(f3, "%s", js);	
	fscanf(f3, "%s", js);
	for(i=1; i<=CropSystemNumber1; i++) fscanf(f3, "%s", js);

	if(CropSystemNumber1!=CropSystemNumber0)
	{
		msg.Format("Error at cropping system number for file %s", File3); 
		AfxMessageBox(msg);
		exit(0);
	}

	fgets(KK, 500, f4);//residue management
	fscanf(f4, "%d", &CropSystemNumber2);
	for(i=1; i<=CropSystemNumber2; i++) fscanf(f4, "%s", js);	
	fscanf(f4, "%s", js);
	for(i=1; i<=CropSystemNumber2; i++) fscanf(f4, "%s", js);

	if(CropSystemNumber2!=CropSystemNumber0)
	{
		msg.Format("Error at cropping system number for file %s", File4); 
		AfxMessageBox(msg);
		exit(0);
	}

	fgets(KK, 500, f5);//tillage
	fscanf(f5, "%d", &CropSystemNumber3);
	for(i=1; i<=CropSystemNumber3; i++) fscanf(f5, "%s", js);	
	fscanf(f5, "%s", js);
	for(i=1; i<=CropSystemNumber3; i++) fscanf(f5, "%s", js);

	if(CropSystemNumber3!=CropSystemNumber0)
	{
		msg.Format("Error at cropping system number for file %s", File5); 
		AfxMessageBox(msg);
		exit(0);
	}

	fgets(KK, 500, f7);//manure use
	fscanf(f7, "%d", &CropSystemNumber4);
	for(i=1; i<=CropSystemNumber4; i++) fscanf(f7, "%s", js);	
	fscanf(f7, "%s", js);
	for(i=1; i<=CropSystemNumber4; i++) fscanf(f7, "%s", js);

	if(CropSystemNumber4!=CropSystemNumber0)
	{
		msg.Format("Error at cropping system number for file %s", File7); 
		AfxMessageBox(msg);
		exit(0);
	}
			
	fgets(KK, 500, f8);//flooding
	fscanf(f8, "%d", &CropSystemNumber5);
	for(i=1; i<=CropSystemNumber5; i++) fscanf(f8, "%s", js);	
	fscanf(f8, "%s", js);
	for(i=1; i<=CropSystemNumber5; i++) fscanf(f8, "%s", js);

	if(CropSystemNumber5!=CropSystemNumber0)
	{
		msg.Format("Error at cropping system number for file %s", File8); 
		AfxMessageBox(msg);
		exit(0);
	}
			
	fgets(KK, 500, f6);//fertilization
	fscanf(f6, "%d", &CropSystemNumber6);
	for(i=1; i<=CropSystemNumber6; i++) fscanf(f6, "%s", js);	
	fscanf(f6, "%s", js);
	for(i=1; i<=CropSystemNumber6; i++) fscanf(f6, "%s", js);			
	
/*	fgets(KK, 500, f9);//irrigation
	fscanf(f9, "%d", &CropNumber1);
	for(i=1; i<=CropNumber1; i++) fscanf(f9, "%s", CroName[i]);	
	fscanf(f9, "%s", js);
	for(i=1; i<=CropNumber1; i++) fscanf(f9, "%d", &CropID[i]);

	if(m_DataFormat==0)
	{
	if(CropNumber1!=CropNumber0)
	{
		msg.Format("Error at crop number for file %s", File9); 
		AfxMessageBox(msg);
		exit(0);
	}
	}*/
	
	fgets(KK, 500, f12);//Crop para
	fscanf(f12, "%d", &CropNumber0);
	for(i=1; i<=CropNumber0; i++) fscanf(f12, "%s", CropName[i]);	
	fscanf(f12, "%s", js);
	for(i=1; i<=CropNumber0; i++) fscanf(f12, "%d", &CropID[i]);

/*	if(CropNumber2!=CropNumber0)
	{
		msg.Format("Error at crop number for file %s", File12); 
		AfxMessageBox(msg);
		exit(0);
	}*/

#ifdef MANURE
	fgets(KK, 500, f10);//livestock farm
	fgets(KK, 500, f10);
	fgets(KK, 500, f10);
#endif

#ifdef HYDRO
	fgets(KK, 500, f11);//soil hydrology
	fgets(KK, 500, f11);
	fgets(KK, 500, f11);
#endif
	
	for(ii=1; ii<=m_TotalCells; ii++)
	{
		char www[200];
		int BB=(int)(100.0*(float)ii/(float)m_TotalCells);
		m_ConvertGo.SetPos(BB);

		CString DIR0;
		DIR0.Format("%s\\Inter\\RegionFiles\\%s", OUTPUT, m_RegionName, m_RegionName);
		_mkdir(DIR0);

		char CounName[100];
		sprintf(File40, "%s\\Inter\\RegionFiles\\%s\\%s_%d", OUTPUT, m_RegionName, m_RegionName, ii);//new files
		f40=fopen(File40, "w");
		if (f40==NULL) note(1, File40);

		fscanf(f1, "%d %s %s %f %f %s %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d", 
				&cell_ID1, CounName, county_name, &S_longitude, &S_latitude, 
				climfileID, &S_RainN, &Kmax_SOC[0], &Kmin_SOC[0], &Kmax_clay[0], &Kmin_clay[0],  
				&Kmax_pH[0],  &Kmin_pH[0], &Kmax_BD[0], &Kmin_BD[0], &SlopeIndex, &SoilQuality,
				&SnowPack, &column, &raw, &continent_ID);

		if(m_Drought==1)
		{
			fscanf(f1, "%d %d %d", &DryYear, &MidYear, &WetYear);
		}

		fprintf(f40, "%d %s %s %f %f  ", 
					cell_ID1, CounName, county_name, S_longitude, S_latitude);
		
		fprintf(f40, "%s %f %f ", 
					climfileID, S_RainN, SnowPack);

		fprintf(f40, "%f %f %f %f %f %f %f %f  %d %d %d %f %f\n", 
					Kmax_SOC[0], Kmin_SOC[0], Kmax_clay[0], Kmin_clay[0], Kmax_pH[0],  Kmin_pH[0], Kmax_BD[0], Kmin_BD[0],
					column, raw, continent_ID, SlopeIndex, SoilQuality);

		if(Kmax_SOC[0]<=0.0) Kmax_SOC[0] = 0.002;
		if(Kmin_SOC[0]<=0.0) Kmin_SOC[0] = 0.001;
		if(Kmax_clay[0]<=0.0) Kmax_clay[0] = 0.01;
		if(Kmin_clay[0]<=0.0) Kmin_clay[0] = 0.01;
		if(Kmax_pH[0]<=0.0) Kmax_pH[0] = 7.0;
		if(Kmin_pH[0]<=0.0) Kmin_pH[0] = 7.0;
		if(Kmax_BD[0]<=0.0) Kmax_BD[0] = 1.3;
		if(Kmin_BD[0]<=0.0) Kmin_BD[0] = 1.3;

		if(m_Drought==1)
		{
			fprintf(f40, "%d %d %d\n", DryYear, MidYear, WetYear);
		}

		fprintf(f40, "%d\n", CropSystemNumber0);
		for(i=1; i<=CropSystemNumber0; i++) fprintf(f40, "%s ", CropSystemName[i]);
		fprintf(f40, "\n");
		fprintf(f40, "%d\n", CropSystemNumber0);
		for(i=1; i<=CropSystemNumber0; i++) fprintf(f40, "%s ", CropSystemID[i]);
		fprintf(f40, "\n");

		fprintf(f40, "%d\n", CropNumber0);
		for(i=1; i<=CropNumber0; i++) fprintf(f40, "%s ", CropName[i]);
		fprintf(f40, "\n");
		fprintf(f40, "%d\n", CropNumber0);
		for(i=1; i<=CropNumber0; i++) fprintf(f40, "%d ", CropID[i]);
		fprintf(f40, "\n");

		fscanf(f2, "%d", &cell_ID2);//crop area

		if(cell_ID1!=cell_ID2)		
		{
			char message[120];
			sprintf(message, "1: GIS data error for grid cell %d in %s", cell_ID1, File2);
			AfxMessageBox(message);
			exit(0); 
		}

		CountyHa=0.0;
		for(i=1; i<=CropSystemNumber0; i++) 
		{
			fscanf(f2, "%f", &S_crop_ha[i]);
			fprintf(f40, "%f ", S_crop_ha[i]);
			CountyHa += S_crop_ha[i];
		}
		fprintf(f40, "\n");
				
		/////////////////
		CropCode.Format("%s\\Inter\\RegionCropCode", OUTPUT);
		CC = fopen(CropCode, "w");
		if (CC==NULL)
		{
			char err[120];
			sprintf(err, "Can not create file %s", CropCode);
			AfxMessageBox(err);
			exit(0); 
		}	
		fprintf(CC, "%d\n", CropSystemNumber0);
		for(i=1; i<=CropSystemNumber0; i++) fprintf(CC, "%10s\n", CropSystemName[i]);
		fprintf(CC, "\n");
		for(i=1; i<=CropSystemNumber0; i++) fprintf(CC, "%10s\n", CropSystemID[i]);
		fprintf(CC, "\n");		
		fclose(CC);
	
		fscanf(f3, "%d", &cell_ID3);//planting/harvest dates

		if(cell_ID1!=cell_ID3)		
		{
			char message[120];
			sprintf(message, "3: GIS data error for grid cell %d in %s", cell_ID1, File3);
			AfxMessageBox(message);
			exit(0); 
		}

		for(i=1; i<=CropSystemNumber0; i++) 
		{
			fscanf(f3, "%s", PlantHarvestDates);
			fprintf(f40, "%s\n", PlantHarvestDates);
		}
		fprintf(f40, "\n");

		fscanf(f4, "%d", &cell_ID4);//crop residue incorporation

		if(cell_ID1!=cell_ID4)		
		{
			char message[120];
			sprintf(message, "4: GIS data error for grid cell %d in %s", cell_ID1, File4);
			AfxMessageBox(message);
			exit(0); 
		}

		for(i=1; i<=CropSystemNumber0; i++) 
		{
			fscanf(f4, "%s", ResidueFraction);
			fprintf(f40, "%s\n", ResidueFraction);
		}
		fprintf(f40, "\n");

		fscanf(f5, "%d", &cell_ID5);//tillage

		if(cell_ID1!=cell_ID5)		
		{
			char message[120];
			sprintf(message, "5: GIS data error for grid cell %d in %s", cell_ID1, File5);
			AfxMessageBox(message);
			exit(0); 
		}

		for(i=1; i<=CropSystemNumber0; i++) 
		{
			fscanf(f5, "%s", Tillage);
			fprintf(f40, "%s\n", Tillage);
		}
		fprintf(f40, "\n");

		fscanf(f6, "%d", &cell_ID6);//fertilization

		if(cell_ID1!=cell_ID6)		
		{
			char message[120];
			sprintf(message, "6: GIS data error for grid cell %d in %s", cell_ID1, File6);
			AfxMessageBox(message);
			exit(0); 
		}

		for(i=1; i<=CropSystemNumber0; i++) 
		{
			fscanf(f6, "%s", FertDates);
			fprintf(f40, "%s\n", FertDates);
		}
		fprintf(f40, "\n");

		fscanf(f7, "%d", &cell_ID7);//manure

		if(cell_ID1!=cell_ID7)		
		{
			char message[120];
			sprintf(message, "7: GIS data error for grid cell %d in %s", cell_ID1, File7);
			AfxMessageBox(message);
			exit(0); 
		}
		for(i=1; i<=CropSystemNumber0; i++) 
		{
			fscanf(f7, "%s", ManureRate);
			fprintf(f40, "%s\n", ManureRate);
		}
		fprintf(f40, "\n");

		fscanf(f8, "%d", &cell_ID8);//flood

		if(cell_ID1!=cell_ID8)		
		{
			char message[120];
			sprintf(message, "8: GIS data error for grid cell %d in %s", cell_ID1, File8);
			AfxMessageBox(message);
			exit(0); 
		}
		for(i=1; i<=CropSystemNumber0; i++) 
		{
			fscanf(f8, "%s", Flooding);
			fprintf(f40, "%s\n", Flooding);
		}
		fprintf(f40, "\n");

		fscanf(f12, "%d", &cell_ID12);//crop parameters

		if(cell_ID1!=cell_ID12)		
		{
			char message[120];
			sprintf(message, "12: GIS data error for grid cell %d in %s", cell_ID1, File12);
			AfxMessageBox(message);
			exit(0); 
		}
		for(i=1; i<=CropNumber0; i++) 
		{
			fscanf(f12, "%s", CropPara);
			fprintf(f40, "%s\n", CropPara);
		}
		fprintf(f40, "\n");
		

#ifdef MANURE
		int FarmNumber, Live_ID;
		//char Live_ID[50], notee[100];
		int BarnType,BarnFloorType,BarnBedMaterial,BarnVentType;
		float BarnHeads,BarnFeedRate,BarnCP,BarnFloorArea,BarnBedRate,BarnBedCN,BarnBedFrequency,BarnRemoveFrequency;
		float BarnToCompost,BarnToLagoon,BarnToDigester;
		int PenType,PenFloorType,PenBedMaterial,PenVentType;
		float PenHeads,PenFeedRate,PenCP,PenFloorArea,PenBedRate,PenBedCN,PenBedFrequency,PenRemoveFrequency;
		float PenToCompost,PenToLagoon,PenToDigester;
		float ComDensity,ComDays,ComLitterRate,ComLitterCN,ComToField,ComDToMarket,ComRemain;
		float LagCapacity,LagArea,LagStoreDays,LagToField,LagToMarket,LagRemain;
		int LagCover,DigTemp, FlashType, ComCover;
		float DigRetentionDays,DigToField,DigToMarket,DigToRemain,FieldArea;
		
		int FarmID, AnimalType, StoreDays;
		float AnimalHeads, FeedRate, CP, FloorArea, AppliedFieldFraction;

		fscanf(f10, "%d", &cell_ID9);

		if(cell_ID1!=cell_ID10)		
		{
			char message[120];
			sprintf(message, "10: GIS data error for grid cell %d in %s", cell_ID10, File10);
			AfxMessageBox(message);
			exit(0); 
		}
		fscanf(f10, "%d", &FarmNumber);

		fprintf(f40, "%d\n", FarmNumber);
		for(i=1;i<=FarmNumber;i++)
		{
			fscanf(f10, "%d %d %f %f %f %f %d %f", &FarmID, &AnimalType, &AnimalHeads, &FeedRate, &CP, &FloorArea, &StoreDays, &AppliedFieldFraction);

			Live_ID = FarmID;
			BarnType = AnimalType;
			BarnHeads = AnimalHeads;
			BarnFeedRate = FeedRate;
			BarnCP = CP;
			BarnFloorArea = FloorArea;
			BarnFloorType = 1;
			BarnBedMaterial = 0;
			BarnBedRate = 0.0;
			BarnBedCN = 0.0;
			BarnBedFrequency = 0.0;
			BarnVentType = 0;
			BarnRemoveFrequency = 1;
			BarnToCompost = 1.0;
			BarnToLagoon = 0.0;
			BarnToDigester = 0.0;
			FlashType = -1;
			
			PenType= 0;
			PenHeads= 0.0;
			PenFeedRate= 0.0;
			PenCP= 0.0;
			PenFloorArea= 0.0;
			PenFloorType= 0;
			PenBedMaterial= 0;
			PenBedRate= 0.0;
			PenBedCN= 0.0;
			PenBedFrequency= 0.0;
			PenRemoveFrequency= 0.0;
			PenToCompost= 0.0;
			PenToLagoon= 0.0;
			PenToDigester= 0.0;
			
			ComDensity = 200.0;
			ComCover = 0;
			ComDays = StoreDays;
			ComLitterRate= 0.0;
			ComLitterCN= 0.0;
			ComToField=1.0;
			ComDToMarket= 0.0;
			ComRemain= 0.0;
			
			LagCapacity= 0.0;
			LagArea= 0.0;
			LagCover= 0;
			LagStoreDays= 0.0;
			LagToField= 0.0;
			LagToMarket= 0.0;
			LagRemain= 0.0;
			
			DigTemp= 0;
			DigRetentionDays= 0.0;
			DigToField= 0.0;
			DigToMarket= 0.0;
			DigToRemain=0.0;
			
			FieldArea=1.0;
					
			fprintf(f40, "%d\n", Live_ID);
			fprintf(f40, "%d %f %f %f %f\n", BarnType,BarnHeads,BarnFeedRate,BarnCP,BarnFloorArea);
			fprintf(f40, "%d %d %f %f %f %d\n", BarnFloorType,BarnBedMaterial,BarnBedRate,BarnBedCN,BarnBedFrequency,BarnVentType);
			fprintf(f40, "%f %f %f %f\n",BarnRemoveFrequency,BarnToCompost,BarnToLagoon,BarnToDigester);
			fprintf(f40, "%d\n", FlashType);
			
			fprintf(f40, "%d %f %f %f %f\n", PenType,PenHeads,PenFeedRate,PenCP,PenFloorArea);
			fprintf(f40, "%d %d %f %f %f\n", PenFloorType,PenBedMaterial,PenBedRate,PenBedCN,PenBedFrequency);
			fprintf(f40, "%f %f %f %f\n",PenRemoveFrequency,PenToCompost,PenToLagoon,PenToDigester);
			fprintf(f40, "%d\n", FlashType);

			fprintf(f40, "%f %d %f %f %f %f %f %f\n",ComDensity, ComCover, ComDays,ComLitterRate,ComLitterCN,ComToField,ComDToMarket,ComRemain);
		
			fprintf(f40, "%f %f %d %f %f %f %f\n",LagCapacity,LagArea,LagCover,LagStoreDays,LagToField,LagToMarket,LagRemain);
		
			fprintf(f40, "%d %f %f %f %f %f\n",DigTemp,DigRetentionDays,DigToField,DigToMarket,DigToRemain,FieldArea);
		}
		
		fprintf(f40, "\n");
#else
				
#endif

#ifdef HYDRO
		//===SCS and MUSLE Database;dengjia===
		fscanf(f11, "%d", &cell_ID11);
		if(cell_ID1!=cell_ID11)		
		{
			char message[120];
			sprintf(message, "11: GIS data error for grid cell %d in %s", cell_ID11, File11);
			AfxMessageBox(message);
			exit(0); 
		}
		for(i=1; i<=18; i++) 
		{
			fscanf(f11, "%f", &SCS[i]);
			fprintf(f40, "%f ", SCS[i]);
		}
		fprintf(f40, "\n");
#endif

		
		
		fclose(f40);		
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f5);
	fclose(f6);
	fclose(f7);
	fclose(f8);
	//fclose(f9);
	fclose(f12);

#ifdef MANURE
	fclose(f10);
#endif

#ifdef HYDRO
	fclose(f11);
#endif

	//if(m_Drought==1) fclose(f12); 

	OnAccept();

	AfxMessageBox("Done");

	AcceptOK = 1;

}

/*
void RegionInput::Onyr41() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr42() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr43() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr44() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr45() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr46() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr47() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr48() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr49() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr50() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr51() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr52() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr53() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr54() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr55() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr56() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr57() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::OnDoubleclickedyr58() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr59() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr60() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr61() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr62() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr63() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr64() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr65() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr66() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr67() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr68() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr69() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr70() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr71() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr72() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr73() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr74() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr75() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr76() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr77() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr78() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr79() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr80() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr81() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr82() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr83() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr84() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr85() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr86() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr87() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr88() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr89() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr90() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr91() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr92() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr93() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr94() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr95() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr96() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr97() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr98() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr99() 
{
	// TODO: Add your control notification handler code here
	
}

void RegionInput::Onyr100() 
{
	// TODO: Add your control notification handler code here
	
}
void RegionInput::Onyr58() 
{
	// TODO: Add your control notification handler code here
	
}
*/

void RegionInput::OnDrought2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//chenhan
	CString msg;
	if (m_SimuYears==1)
	{
		msg.Format("The simulated years should not be less than 2 in the drought scenario!Please retype again!"); 
		AfxMessageBox(msg);
		exit(0);
	}
	//
	
	m_Drought=1;//chenhan

	CString CYW;
	FILE* cyw;
	CYW.Format("%s\\TargetYr", INTER);
	cyw=fopen(CYW, "w");
	if(cyw==NULL) note(1, CYW);
	fprintf(cyw, "%d", m_StartYear);
	fclose(cyw);

	Dndc_YieldPredict ww;
	if(ww.DoModal()==IDOK)
	{
	}

}

void RegionInput::OnDrought1() //chenhan
{
	// TODO: Add your control notification handler code here
	m_Drought=0;//chenhan

}

void RegionInput::OnSelchangeDailyRecord() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("Daily record is not encouraged as it would produce a huge amount of output data.");
}
