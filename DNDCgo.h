// DNDCgo.h : main header file for the DNDCGO DLL

#include "stdafx.h"
#ifndef DEGUI
#if !defined(AFX_DNDCGO_H__72AB44DD_ED55_4A14_B8AA_534229DBBBAA__INCLUDED_)
#define AFX_DNDCGO_H__72AB44DD_ED55_4A14_B8AA_534229DBBBAA__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

//#define DLLEXPORT extern "C" __stdcall(dllexport)// __stdcall


#ifndef DLLEXPORT
#define DLLEXPORT extern "C" _declspec(dllexport)
#endif

typedef struct
{
	CWnd* pWnd;
	CDC* pDC;
	int   DNDC_or_Other;
	int  StopRun;
} MODEL_LINK_INFO;
// commented by liujm


     DLLEXPORT int WINAPI Model_link(MODEL_LINK_INFO* pLinkInfo, int scale, char* cropping_system, int S_SoilYear, int S_ThisYear,
										int S_SimuYears, char* DatabaseName, char* r_Province, char* ScenarioName,
										float ha, int ProvinceOrder, int S_county, int CountyIDX, int landuse,
										int StartYear, int ifdaily, int MonteCarlo, int ZXH, int Batch, int GlobeData, 
										char* DirRoot, int sample, int RRRRR, int IrriType, char* country_ID,
										int livestock, int Monitor, int DroughtID, char f_region[6][150], char* DroughtYield,
										int FFN, char *BatchPass);
				
	 DLLEXPORT void WINAPI Cell_end(int S_SimuYears, int ii_ha, char* DatabaseName, char* ScenarioName,
										int CountyIDX, int crop_number, char* r_Province, int IrriType, int SoilDataUse);

	 DLLEXPORT int WINAPI OpenSesame(void);//MODEL_LINK_INFO* pLinkInfo);
/////////////////////////////////////////////////////////////////////////////
// CDNDCgoApp
// See DNDCgo.cpp for the implementation of this class
//

class CDNDCgoApp : public CWinApp
{
public:
	CDNDCgoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDNDCgoApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDNDCgoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
float pow(float n, double e){
	return pow(n, (float) e);
}

float pow(double n, float e){
	return powf((float) n, e);
}
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDCGO_H__72AB44DD_ED55_4A14_B8AA_534229DBBBAA__INCLUDED_)
#endif // !DEGUI