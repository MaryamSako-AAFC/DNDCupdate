// Dndc_ManningChannel.cpp : implementation file
//
#include "stdafx.h"
#include "dndc71.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include <io.h>
#include <direct.h>
#include "Dndc_ManningChannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

float mann;
/////////////////////////////////////////////////////////////////////////////
// Dndc_ManningChannel dialog


Dndc_ManningChannel::Dndc_ManningChannel(CWnd* pParent /*=NULL*/)
	: CDialog(Dndc_ManningChannel::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dndc_ManningChannel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dndc_ManningChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dndc_ManningChannel)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dndc_ManningChannel, CDialog)
	//{{AFX_MSG_MAP(Dndc_ManningChannel)
	ON_BN_CLICKED(IDC_MC1, OnMc1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dndc_ManningChannel message handlers

void Dndc_ManningChannel::OnMc1() 
{
	// TODO: Add your control notification handler code here
	//mann = 0.025;
}

void Dndc_ManningChannel::OnOK() 
{
	// TODO: Add extra validation here
/*	CString FF;
	FILE* ff;

	FF.Format("%s\\inter\\ManningVhannel",OUTPUT);
	ff=fopen(FF, "w");
	if(ff==NULL) note(1, FF);
	fprintf(ff, "%f", mann);
	fclose(ff);
*/
	CDialog::OnOK();
}
