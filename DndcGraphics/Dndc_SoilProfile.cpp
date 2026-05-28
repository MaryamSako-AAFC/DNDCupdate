// DNDC_SoilProfile.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "stdio.h"
//#include <math.h>
#include "dndc_main.h"
#include "SitePara.h"
//#include "SitePage2.h"
//#include "SCSDlg.h"
#include "DNDC_SoilProfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Site_BaseInformation	IData ;
char SoilProfName[250];


/////////////////////////////////////////////////////////////////////////////
// DNDC_SoilProfile dialog


DNDC_SoilProfile::DNDC_SoilProfile(CWnd* pParent /*=NULL*/)
	: CDialog(DNDC_SoilProfile::IDD, pParent)
{
	//{{AFX_DATA_INIT(DNDC_SoilProfile)
	m_SPc1 = 0.0f;
	m_SPc10 = 0.0f;
	m_SPc2 = 0.0f;
	m_SPc3 = 0.0f;
	m_SPc4 = 0.0f;
	m_SPc5 = 0.0f;
	m_SPc6 = 0.0f;
	m_SPc7 = 0.0f;
	m_SPc8 = 0.0f;
	m_SPc9 = 0.0f;
	m_SPd1 = 0.0f;
	m_SPd10 = 0.0f;
	m_SPd2 = 0.0f;
	m_SPd3 = 0.0f;
	m_SPd4 = 0.0f;
	m_SPd5 = 0.0f;
	m_SPd6 = 0.0f;
	m_SPd7 = 0.0f;
	m_SPd8 = 0.0f;
	m_SPd9 = 0.0f;
	m_SPfc1 = 0.0f;
	m_SPfc10 = 0.0f;
	m_SPfc2 = 0.0f;
	m_SPfc3 = 0.0f;
	m_SPfc4 = 0.0f;
	m_SPfc5 = 0.0f;
	m_SPfc6 = 0.0f;
	m_SPfc7 = 0.0f;
	m_SPfc8 = 0.0f;
	m_SPfc9 = 0.0f;
	m_SPhy1 = 0.0f;
	m_SPhy10 = 0.0f;
	m_SPhy2 = 0.0f;
	m_SPhy3 = 0.0f;
	m_SPhy4 = 0.0f;
	m_SPhy5 = 0.0f;
	m_SPhy6 = 0.0f;
	m_SPhy7 = 0.0f;
	m_SPhy8 = 0.0f;
	m_SPhy9 = 0.0f;
	m_SPlayers = 0;
	m_SPph1 = 0.0f;
	m_SPph10 = 0.0f;
	m_SPph2 = 0.0f;
	m_SPph3 = 0.0f;
	m_SPph4 = 0.0f;
	m_SPph5 = 0.0f;
	m_SPph6 = 0.0f;
	m_SPph7 = 0.0f;
	m_SPph8 = 0.0f;
	m_SPph9 = 0.0f;
	m_SPpo1 = 0.0f;
	m_SPpo10 = 0.0f;
	m_SPpo2 = 0.0f;
	m_SPpo3 = 0.0f;
	m_SPpo4 = 0.0f;
	m_SPpo5 = 0.0f;
	m_SPpo6 = 0.0f;
	m_SPpo7 = 0.0f;
	m_SPpo8 = 0.0f;
	m_SPpo9 = 0.0f;
	m_SPsoc1 = 0.0f;
	m_SPsoc10 = 0.0f;
	m_SPsoc2 = 0.0f;
	m_SPsoc3 = 0.0f;
	m_SPsoc4 = 0.0f;
	m_SPsoc5 = 0.0f;
	m_SPsoc6 = 0.0f;
	m_SPsoc7 = 0.0f;
	m_SPsoc8 = 0.0f;
	m_SPsoc9 = 0.0f;
	m_SPth1 = 0.0f;
	m_SPth10 = 0.0f;
	m_SPth2 = 0.0f;
	m_SPth3 = 0.0f;
	m_SPth4 = 0.0f;
	m_SPth5 = 0.0f;
	m_SPth6 = 0.0f;
	m_SPth7 = 0.0f;
	m_SPth8 = 0.0f;
	m_SPth9 = 0.0f;
	m_SPthickness = 0.0f;
	m_SPwp5 = 0.0f;
	m_SPwp1 = 0.0f;
	m_SPwp10 = 0.0f;
	m_SPwp2 = 0.0f;
	m_SPwp3 = 0.0f;
	m_SPwp4 = 0.0f;
	m_SPwp6 = 0.0f;
	m_SPwp7 = 0.0f;
	m_SPwp8 = 0.0f;
	m_SPwp9 = 0.0f;
	m_SPso1 = -1;
	m_SPso2 = -1;
	m_SPso3 = -1;
	m_SPso4 = -1;
	m_SPso5 = -1;
	m_SPso6 = -1;
	m_SPso7 = -1;
	m_SPso8 = -1;
	m_SPso9 = -1;
	m_SPso10 = -1;
	m_ProfileName = _T("");
	//}}AFX_DATA_INIT
}


void DNDC_SoilProfile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DNDC_SoilProfile)
	DDX_Control(pDX, IDC_Soiltexture9, m_Texture9);
	DDX_Control(pDX, IDC_Soiltexture8, m_Texture8);
	DDX_Control(pDX, IDC_Soiltexture7, m_Texture7);
	DDX_Control(pDX, IDC_Soiltexture6, m_Texture6);
	DDX_Control(pDX, IDC_Soiltexture5, m_Texture5);
	DDX_Control(pDX, IDC_Soiltexture4, m_Texture4);
	DDX_Control(pDX, IDC_Soiltexture3, m_Texture3);
	DDX_Control(pDX, IDC_Soiltexture2, m_Texture2);
	DDX_Control(pDX, IDC_Soiltexture10, m_Texture10);
	DDX_Control(pDX, IDC_Soiltexture1, m_Texture1);
	DDX_Text(pDX, IDC_SPc1, m_SPc1);
	DDX_Text(pDX, IDC_SPc10, m_SPc10);
	DDX_Text(pDX, IDC_SPc2, m_SPc2);
	DDX_Text(pDX, IDC_SPc3, m_SPc3);
	DDX_Text(pDX, IDC_SPc4, m_SPc4);
	DDX_Text(pDX, IDC_SPc5, m_SPc5);
	DDX_Text(pDX, IDC_SPc6, m_SPc6);
	DDX_Text(pDX, IDC_SPc7, m_SPc7);
	DDX_Text(pDX, IDC_SPc8, m_SPc8);
	DDX_Text(pDX, IDC_SPc9, m_SPc9);
	DDX_Text(pDX, IDC_SPd1, m_SPd1);
	DDX_Text(pDX, IDC_SPd10, m_SPd10);
	DDX_Text(pDX, IDC_SPd2, m_SPd2);
	DDX_Text(pDX, IDC_SPd3, m_SPd3);
	DDX_Text(pDX, IDC_SPd4, m_SPd4);
	DDX_Text(pDX, IDC_SPd5, m_SPd5);
	DDX_Text(pDX, IDC_SPd6, m_SPd6);
	DDX_Text(pDX, IDC_SPd7, m_SPd7);
	DDX_Text(pDX, IDC_SPd8, m_SPd8);
	DDX_Text(pDX, IDC_SPd9, m_SPd9);
	DDX_Text(pDX, IDC_SPfc1, m_SPfc1);
	DDX_Text(pDX, IDC_SPfc10, m_SPfc10);
	DDX_Text(pDX, IDC_SPfc2, m_SPfc2);
	DDX_Text(pDX, IDC_SPfc3, m_SPfc3);
	DDX_Text(pDX, IDC_SPfc4, m_SPfc4);
	DDX_Text(pDX, IDC_SPfc5, m_SPfc5);
	DDX_Text(pDX, IDC_SPfc6, m_SPfc6);
	DDX_Text(pDX, IDC_SPfc7, m_SPfc7);
	DDX_Text(pDX, IDC_SPfc8, m_SPfc8);
	DDX_Text(pDX, IDC_SPfc9, m_SPfc9);
	DDX_Text(pDX, IDC_SPhy1, m_SPhy1);
	DDX_Text(pDX, IDC_SPhy10, m_SPhy10);
	DDX_Text(pDX, IDC_SPhy2, m_SPhy2);
	DDX_Text(pDX, IDC_SPhy3, m_SPhy3);
	DDX_Text(pDX, IDC_SPhy4, m_SPhy4);
	DDX_Text(pDX, IDC_SPhy5, m_SPhy5);
	DDX_Text(pDX, IDC_SPhy6, m_SPhy6);
	DDX_Text(pDX, IDC_SPhy7, m_SPhy7);
	DDX_Text(pDX, IDC_SPhy8, m_SPhy8);
	DDX_Text(pDX, IDC_SPhy9, m_SPhy9);
	DDX_Text(pDX, IDC_SPlayers, m_SPlayers);
	DDX_Text(pDX, IDC_SPph1, m_SPph1);
	DDX_Text(pDX, IDC_SPph10, m_SPph10);
	DDX_Text(pDX, IDC_SPph2, m_SPph2);
	DDX_Text(pDX, IDC_SPph3, m_SPph3);
	DDX_Text(pDX, IDC_SPph4, m_SPph4);
	DDX_Text(pDX, IDC_SPph5, m_SPph5);
	DDX_Text(pDX, IDC_SPph6, m_SPph6);
	DDX_Text(pDX, IDC_SPph7, m_SPph7);
	DDX_Text(pDX, IDC_SPph8, m_SPph8);
	DDX_Text(pDX, IDC_SPph9, m_SPph9);
	DDX_Text(pDX, IDC_SPpo1, m_SPpo1);
	DDX_Text(pDX, IDC_SPpo10, m_SPpo10);
	DDX_Text(pDX, IDC_SPpo2, m_SPpo2);
	DDX_Text(pDX, IDC_SPpo3, m_SPpo3);
	DDX_Text(pDX, IDC_SPpo4, m_SPpo4);
	DDX_Text(pDX, IDC_SPpo5, m_SPpo5);
	DDX_Text(pDX, IDC_SPpo6, m_SPpo6);
	DDX_Text(pDX, IDC_SPpo7, m_SPpo7);
	DDX_Text(pDX, IDC_SPpo8, m_SPpo8);
	DDX_Text(pDX, IDC_SPpo9, m_SPpo9);
	DDX_Text(pDX, IDC_SPsoc1, m_SPsoc1);
	DDX_Text(pDX, IDC_SPsoc10, m_SPsoc10);
	DDX_Text(pDX, IDC_SPsoc2, m_SPsoc2);
	DDX_Text(pDX, IDC_SPsoc3, m_SPsoc3);
	DDX_Text(pDX, IDC_SPsoc4, m_SPsoc4);
	DDX_Text(pDX, IDC_SPsoc5, m_SPsoc5);
	DDX_Text(pDX, IDC_SPsoc6, m_SPsoc6);
	DDX_Text(pDX, IDC_SPsoc7, m_SPsoc7);
	DDX_Text(pDX, IDC_SPsoc8, m_SPsoc8);
	DDX_Text(pDX, IDC_SPsoc9, m_SPsoc9);
	DDX_Text(pDX, IDC_SPth1, m_SPth1);
	DDX_Text(pDX, IDC_SPth10, m_SPth10);
	DDX_Text(pDX, IDC_SPth2, m_SPth2);
	DDX_Text(pDX, IDC_SPth3, m_SPth3);
	DDX_Text(pDX, IDC_SPth4, m_SPth4);
	DDX_Text(pDX, IDC_SPth5, m_SPth5);
	DDX_Text(pDX, IDC_SPth6, m_SPth6);
	DDX_Text(pDX, IDC_SPth7, m_SPth7);
	DDX_Text(pDX, IDC_SPth8, m_SPth8);
	DDX_Text(pDX, IDC_SPth9, m_SPth9);
	DDX_Text(pDX, IDC_SPthickness, m_SPthickness);
	DDX_Text(pDX, IDC_SPtwp5, m_SPwp5);
	DDX_Text(pDX, IDC_SPwp1, m_SPwp1);
	DDX_Text(pDX, IDC_SPwp10, m_SPwp10);
	DDX_Text(pDX, IDC_SPwp2, m_SPwp2);
	DDX_Text(pDX, IDC_SPwp3, m_SPwp3);
	DDX_Text(pDX, IDC_SPwp4, m_SPwp4);
	DDX_Text(pDX, IDC_SPwp6, m_SPwp6);
	DDX_Text(pDX, IDC_SPwp7, m_SPwp7);
	DDX_Text(pDX, IDC_SPwp8, m_SPwp8);
	DDX_Text(pDX, IDC_SPwp9, m_SPwp9);
	DDX_Text(pDX, IDC_ProfileName, m_ProfileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DNDC_SoilProfile, CDialog)
	//{{AFX_MSG_MAP(DNDC_SoilProfile)
	ON_CBN_SELCHANGE(IDC_Soiltexture1, OnSelchangeSoiltexture1)
	ON_CBN_SELCHANGE(IDC_Soiltexture2, OnSelchangeSoiltexture2)
	ON_CBN_SELCHANGE(IDC_Soiltexture3, OnSelchangeSoiltexture3)
	ON_CBN_SELCHANGE(IDC_Soiltexture4, OnSelchangeSoiltexture4)
	ON_CBN_SELCHANGE(IDC_Soiltexture5, OnSelchangeSoiltexture5)
	ON_CBN_SELCHANGE(IDC_Soiltexture6, OnSelchangeSoiltexture6)
	ON_CBN_SELCHANGE(IDC_Soiltexture7, OnSelchangeSoiltexture7)
	ON_CBN_SELCHANGE(IDC_Soiltexture8, OnSelchangeSoiltexture8)
	ON_CBN_SELCHANGE(IDC_Soiltexture9, OnSelchangeSoiltexture9)
	ON_CBN_SELCHANGE(IDC_Soiltexture10, OnSelchangeSoiltexture10)
	ON_BN_CLICKED(ID_SPsave, OnSPsave)
	ON_BN_CLICKED(ID_SPread, OnSPread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DNDC_SoilProfile message handlers

void DNDC_SoilProfile::OnSelchangeSoiltexture1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture1.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc1 = IData.Soil_Clay;
	m_SPfc1= IData.Fldcap;
	m_SPwp1 = IData.Wiltpt;
	m_SPhy1 = IData.Sks;
	m_SPpo1 = IData.Soil_Porosity;
	m_SPso1 = IData.Soil_Texture;
	
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture2.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc2 = IData.Soil_Clay;
	m_SPfc2= IData.Fldcap;
	m_SPwp2 = IData.Wiltpt;
	m_SPhy2 = IData.Sks;
	m_SPpo2 = IData.Soil_Porosity;
	m_SPso2 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture3.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc3 = IData.Soil_Clay;
	m_SPfc3= IData.Fldcap;
	m_SPwp3 = IData.Wiltpt;
	m_SPhy3 = IData.Sks;
	m_SPpo3 = IData.Soil_Porosity;
	m_SPso3 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture4.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc4 = IData.Soil_Clay;
	m_SPfc4= IData.Fldcap;
	m_SPwp4 = IData.Wiltpt;
	m_SPhy4 = IData.Sks;
	m_SPpo4 = IData.Soil_Porosity;
	m_SPso4 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture5.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc5 = IData.Soil_Clay;
	m_SPfc5= IData.Fldcap;
	m_SPwp5 = IData.Wiltpt;
	m_SPhy5 = IData.Sks;
	m_SPpo5 = IData.Soil_Porosity;
	m_SPso5 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture6.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc6 = IData.Soil_Clay;
	m_SPfc6= IData.Fldcap;
	m_SPwp6 = IData.Wiltpt;
	m_SPhy6 = IData.Sks;
	m_SPpo6 = IData.Soil_Porosity;
	m_SPso6 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture7() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture7.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc7 = IData.Soil_Clay;
	m_SPfc7= IData.Fldcap;
	m_SPwp7 = IData.Wiltpt;
	m_SPhy7 = IData.Sks;
	m_SPpo7 = IData.Soil_Porosity;
	m_SPso7 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture8() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture8.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc8 = IData.Soil_Clay;
	m_SPfc8= IData.Fldcap;
	m_SPwp8 = IData.Wiltpt;
	m_SPhy8 = IData.Sks;
	m_SPpo8 = IData.Soil_Porosity;
	m_SPso8 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture9() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture9.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc9 = IData.Soil_Clay;
	m_SPfc9= IData.Fldcap;
	m_SPwp9 = IData.Wiltpt;
	m_SPhy9 = IData.Sks;
	m_SPpo9 = IData.Soil_Porosity;
	m_SPso9 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSelchangeSoiltexture10() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	IData.Soil_Texture=m_Texture10.GetCurSel()+1;
	ReadSoilFeature("Default");	//read soil parameters from database
	m_SPc10 = IData.Soil_Clay;
	m_SPfc10= IData.Fldcap;
	m_SPwp10 = IData.Wiltpt;
	m_SPhy10 = IData.Sks;
	m_SPpo10 = IData.Soil_Porosity;
	m_SPso10 = IData.Soil_Texture;
	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnSPsave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString NNT;
	float TLE = 0.0, dTLE;
	TLE = m_SPth1+m_SPth2+m_SPth3+m_SPth4+m_SPth5+m_SPth6+m_SPth7+m_SPth8+m_SPth9+m_SPth10;

	if(TLE < m_SPthickness)
	{
		dTLE = m_SPthickness - TLE;
		NNT.Format("You have %f m left for defining", dTLE);
		AfxMessageBox(NNT);
		return;
	}
	else if(TLE > m_SPthickness)
	{
		dTLE = TLE - m_SPthickness;
		NNT.Format("You have %f m more defined", dTLE);
		AfxMessageBox(NNT);
		return;
	}
	else {}
	
	CFileDialog ask(false, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "Soil profile data file (*.spf)|*.spf|All files (*.*)|*.*||", NULL );
	
	ask.DoModal();
	char cst[255];
	CString fname;
	int l, rrr, yyy;
	fname = ask.GetPathName();
	l=fname.GetLength();
	if (l==0) return;

	if (fname.Right(4)!=".spf") fname=fname+".spf";
	sprintf(cst,"%s",fname);
    IData.ProfileFileName=fname;
	SaveProfileData(1, cst);

/*	CString RF;
	FILE *ef;
	RF.Format("%s", cst);
	ef=fopen(RF, "w");	
	if(ef==NULL) note(1, RF);

	fprintf(ef, "%f %d\n", m_SPthickness, m_SPlayers);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		1, m_SPth1, m_SPd1, m_SPsoc1, m_SPso1, m_SPph1, m_SPfc1, m_SPwp1, m_SPpo1, m_SPhy1, m_SPc1);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		2, m_SPth2, m_SPd2, m_SPsoc2, m_SPso2, m_SPph2, m_SPfc2, m_SPwp2, m_SPpo2, m_SPhy2, m_SPc2);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		3, m_SPth3, m_SPd3, m_SPsoc3, m_SPso3, m_SPph3, m_SPfc3, m_SPwp3, m_SPpo3, m_SPhy3, m_SPc3);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		4, m_SPth4, m_SPd4, m_SPsoc4, m_SPso4, m_SPph4, m_SPfc4, m_SPwp4, m_SPpo4, m_SPhy4, m_SPc4);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		5, m_SPth5, m_SPd5, m_SPsoc5, m_SPso5, m_SPph5, m_SPfc5, m_SPwp5, m_SPpo5, m_SPhy5, m_SPc5);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		6, m_SPth6, m_SPd6, m_SPsoc6, m_SPso6, m_SPph6, m_SPfc6, m_SPwp6, m_SPpo6, m_SPhy6, m_SPc6);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		7, m_SPth7, m_SPd7, m_SPsoc7, m_SPso7, m_SPph7, m_SPfc7, m_SPwp7, m_SPpo7, m_SPhy7, m_SPc7);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		8, m_SPth8, m_SPd8, m_SPsoc8, m_SPso8, m_SPph8, m_SPfc8, m_SPwp8, m_SPpo8, m_SPhy8, m_SPc8);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		9, m_SPth9, m_SPd9, m_SPsoc9, m_SPso9, m_SPph9, m_SPfc9, m_SPwp9, m_SPpo9, m_SPhy9, m_SPc9);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		10, m_SPth10, m_SPd10, m_SPsoc10, m_SPso10, m_SPph10, m_SPfc10, m_SPwp10, m_SPpo10, m_SPhy10, m_SPc10);
		
	fclose(ef);*/
}

void DNDC_SoilProfile::OnSPread() 
{
	// TODO: Add your control notification handler code here
	int layer[11];
	CFileDialog ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "Soil profile data file (*.spf)|*.spf|All files (*.*)|*.*||", NULL );
	
	ask.DoModal();
	char cst[255];
	strcpy(cst,ask.GetPathName());
	if (strlen(cst)==0) return;

	CString RF;
	FILE *ef;
	RF.Format("%s", cst);
	ef=fopen(RF, "r");	
	if(ef==NULL) note(1, RF);

	fscanf(ef, "%f %d", &m_SPthickness, &m_SPlayers);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[1], &m_SPth1, &m_SPd1, &m_SPsoc1, &m_SPso1, &m_SPph1, &m_SPfc1, &m_SPwp1, &m_SPpo1, &m_SPhy1, &m_SPc1);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[2], &m_SPth2, &m_SPd2, &m_SPsoc2, &m_SPso2, &m_SPph2, &m_SPfc2, &m_SPwp2, &m_SPpo2, &m_SPhy2, &m_SPc2);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[3], &m_SPth3, &m_SPd3, &m_SPsoc3, &m_SPso3, &m_SPph3, &m_SPfc3, &m_SPwp3, &m_SPpo3, &m_SPhy3, &m_SPc3);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[4], &m_SPth4, &m_SPd4, &m_SPsoc4, &m_SPso4, &m_SPph4, &m_SPfc4, &m_SPwp4, &m_SPpo4, &m_SPhy4, &m_SPc4);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[5], &m_SPth5, &m_SPd5, &m_SPsoc5, &m_SPso5, &m_SPph5, &m_SPfc5, &m_SPwp5, &m_SPpo5, &m_SPhy5, &m_SPc5);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[6], &m_SPth6, &m_SPd6, &m_SPsoc6, &m_SPso6, &m_SPph6, &m_SPfc6, &m_SPwp6, &m_SPpo6, &m_SPhy6, &m_SPc6);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[7], &m_SPth7, &m_SPd7, &m_SPsoc7, &m_SPso7, &m_SPph7, &m_SPfc7, &m_SPwp7, &m_SPpo7, &m_SPhy7, &m_SPc7);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[8], &m_SPth8, &m_SPd8, &m_SPsoc8, &m_SPso8, &m_SPph8, &m_SPfc8, &m_SPwp8, &m_SPpo8, &m_SPhy8, &m_SPc8);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[9], &m_SPth9, &m_SPd9, &m_SPsoc9, &m_SPso9, &m_SPph9, &m_SPfc9, &m_SPwp9, &m_SPpo9, &m_SPhy9, &m_SPc9);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[10], &m_SPth10, &m_SPd10, &m_SPsoc10, &m_SPso10, &m_SPph10, &m_SPfc10, &m_SPwp10, &m_SPpo10, &m_SPhy10, &m_SPc10);		
	fscanf(ef, "%s", SoilProfName);
	fclose(ef);

	m_Texture1.SetCurSel(m_SPso1-1);
	m_Texture2.SetCurSel(m_SPso2-1);
	m_Texture3.SetCurSel(m_SPso3-1);
	m_Texture4.SetCurSel(m_SPso4-1);
	m_Texture5.SetCurSel(m_SPso5-1);
	m_Texture6.SetCurSel(m_SPso6-1);
	m_Texture7.SetCurSel(m_SPso7-1);
	m_Texture8.SetCurSel(m_SPso8-1);
	m_Texture9.SetCurSel(m_SPso9-1);
	m_Texture10.SetCurSel(m_SPso10-1);

	SaveProfileData(1, cst);
	IData.ProfileFileName=cst;
	m_ProfileName = cst;

	UpdateData(FALSE);
}

void DNDC_SoilProfile::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString NNT;
	float TLE = 0.0, dTLE;
	TLE = m_SPth1+m_SPth2+m_SPth3+m_SPth4+m_SPth5+m_SPth6+m_SPth7+m_SPth8+m_SPth9+m_SPth10;

	if(TLE < m_SPthickness)
	{
		dTLE = m_SPthickness - TLE;
		NNT.Format("You have %f m left for defining", dTLE);
		AfxMessageBox(NNT);
		return;
	}
	else if(TLE > m_SPthickness)
	{
		dTLE = TLE - m_SPthickness;
		NNT.Format("You have %f m more defined", dTLE);
		AfxMessageBox(NNT);
		return;
	}
	else {}

	int LL=0;
	if(m_SPth1>0.0) LL++;
	if(m_SPth2>0.0) LL++;
	if(m_SPth3>0.0) LL++;
	if(m_SPth4>0.0) LL++;
	if(m_SPth5>0.0) LL++;
	if(m_SPth6>0.0) LL++;
	if(m_SPth7>0.0) LL++;
	if(m_SPth8>0.0) LL++;
	if(m_SPth9>0.0) LL++;
	if(m_SPth10>0.0) LL++;

	if(m_SPlayers!=LL)
	{
		NNT.Format("The number of layers is not equal to your design");
		AfxMessageBox(NNT);
		return;
	}

	char NN[300];
	sprintf(NN, "%s\\Inter\\SoilProfileData.spf", OUTPUT); 
	SaveProfileData(0, NN);
	DNDC_SoilProfile::OnSPsave();//write the saved file
	
	
	CDialog::OnOK();
}

void DNDC_SoilProfile::SaveProfileData(int SS, char *cst)
{
	CString RF;
	FILE *ef;
	RF.Format("%s", cst);
	ef=fopen(RF, "w");	//RF
	if(ef==NULL) note(1, RF);

	fprintf(ef, "%f %d\n", m_SPthickness, m_SPlayers);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		1, m_SPth1, m_SPd1, m_SPsoc1, m_SPso1, m_SPph1, m_SPfc1, m_SPwp1, m_SPpo1, m_SPhy1, m_SPc1);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		2, m_SPth2, m_SPd2, m_SPsoc2, m_SPso2, m_SPph2, m_SPfc2, m_SPwp2, m_SPpo2, m_SPhy2, m_SPc2);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		3, m_SPth3, m_SPd3, m_SPsoc3, m_SPso3, m_SPph3, m_SPfc3, m_SPwp3, m_SPpo3, m_SPhy3, m_SPc3);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		4, m_SPth4, m_SPd4, m_SPsoc4, m_SPso4, m_SPph4, m_SPfc4, m_SPwp4, m_SPpo4, m_SPhy4, m_SPc4);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		5, m_SPth5, m_SPd5, m_SPsoc5, m_SPso5, m_SPph5, m_SPfc5, m_SPwp5, m_SPpo5, m_SPhy5, m_SPc5);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		6, m_SPth6, m_SPd6, m_SPsoc6, m_SPso6, m_SPph6, m_SPfc6, m_SPwp6, m_SPpo6, m_SPhy6, m_SPc6);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		7, m_SPth7, m_SPd7, m_SPsoc7, m_SPso7, m_SPph7, m_SPfc7, m_SPwp7, m_SPpo7, m_SPhy7, m_SPc7);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		8, m_SPth8, m_SPd8, m_SPsoc8, m_SPso8, m_SPph8, m_SPfc8, m_SPwp8, m_SPpo8, m_SPhy8, m_SPc8);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		9, m_SPth9, m_SPd9, m_SPsoc9, m_SPso9, m_SPph9, m_SPfc9, m_SPwp9, m_SPpo9, m_SPhy9, m_SPc9);
	fprintf(ef, "%d %f %f %f %d %f %f %f %f %f %f\n", 
		10, m_SPth10, m_SPd10, m_SPsoc10, m_SPso10, m_SPph10, m_SPfc10, m_SPwp10, m_SPpo10, m_SPhy10, m_SPc10);
	fprintf(ef, "%s\n", m_ProfileName);	
	fclose(ef);

}

BOOL DNDC_SoilProfile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int layer[11];
	CString RF;
	FILE *ef;
	RF.Format("%s\\SoilProfileData.spf", INTER);
	if(IData.ProfileFileName=="")
	{
		ef=fopen(RF, "r");
	}
	else
	{
	ef=fopen(IData.ProfileFileName, "r");//RF	
	}
	if(ef==NULL) 
	{
	}
	else
	{
	fscanf(ef, "%f %d", &m_SPthickness, &m_SPlayers);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[1], &m_SPth1, &m_SPd1, &m_SPsoc1, &m_SPso1, &m_SPph1, &m_SPfc1, &m_SPwp1, &m_SPpo1, &m_SPhy1, &m_SPc1);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[2], &m_SPth2, &m_SPd2, &m_SPsoc2, &m_SPso2, &m_SPph2, &m_SPfc2, &m_SPwp2, &m_SPpo2, &m_SPhy2, &m_SPc2);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[3], &m_SPth3, &m_SPd3, &m_SPsoc3, &m_SPso3, &m_SPph3, &m_SPfc3, &m_SPwp3, &m_SPpo3, &m_SPhy3, &m_SPc3);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[4], &m_SPth4, &m_SPd4, &m_SPsoc4, &m_SPso4, &m_SPph4, &m_SPfc4, &m_SPwp4, &m_SPpo4, &m_SPhy4, &m_SPc4);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[5], &m_SPth5, &m_SPd5, &m_SPsoc5, &m_SPso5, &m_SPph5, &m_SPfc5, &m_SPwp5, &m_SPpo5, &m_SPhy5, &m_SPc5);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[6], &m_SPth6, &m_SPd6, &m_SPsoc6, &m_SPso6, &m_SPph6, &m_SPfc6, &m_SPwp6, &m_SPpo6, &m_SPhy6, &m_SPc6);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[7], &m_SPth7, &m_SPd7, &m_SPsoc7, &m_SPso7, &m_SPph7, &m_SPfc7, &m_SPwp7, &m_SPpo7, &m_SPhy7, &m_SPc7);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[8], &m_SPth8, &m_SPd8, &m_SPsoc8, &m_SPso8, &m_SPph8, &m_SPfc8, &m_SPwp8, &m_SPpo8, &m_SPhy8, &m_SPc8);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[9], &m_SPth9, &m_SPd9, &m_SPsoc9, &m_SPso9, &m_SPph9, &m_SPfc9, &m_SPwp9, &m_SPpo9, &m_SPhy9, &m_SPc9);
	fscanf(ef, "%d %f %f %f %d %f %f %f %f %f %f", 
		&layer[10], &m_SPth10, &m_SPd10, &m_SPsoc10, &m_SPso10, &m_SPph10, &m_SPfc10, &m_SPwp10, &m_SPpo10, &m_SPhy10, &m_SPc10);		
	fscanf(ef, "%s", SoilProfName);
	fclose(ef);
	}

	m_Texture1.SetCurSel(m_SPso1-1);
		m_Texture2.SetCurSel(m_SPso2-1);
		m_Texture3.SetCurSel(m_SPso3-1);
		m_Texture4.SetCurSel(m_SPso4-1);
		m_Texture5.SetCurSel(m_SPso5-1);
		m_Texture6.SetCurSel(m_SPso6-1);
		m_Texture7.SetCurSel(m_SPso7-1);
		m_Texture8.SetCurSel(m_SPso8-1);
		m_Texture9.SetCurSel(m_SPso9-1);
		m_Texture10.SetCurSel(m_SPso10-1);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
