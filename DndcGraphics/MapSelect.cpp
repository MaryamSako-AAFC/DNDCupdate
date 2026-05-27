// MapSelect.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "MapSelect.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MapSelect dialog


MapSelect::MapSelect(CWnd* pParent /*=NULL*/)
	: CDialog(MapSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapSelect)
	m_yr = _T("");
	m_Watershed = _T("");
	//}}AFX_DATA_INIT
}


void MapSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapSelect)
	DDX_CBString(pDX, IDC_yr, m_yr);
	DDX_CBString(pDX, IDC_Watershed, m_Watershed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MapSelect, CDialog)
	//{{AFX_MSG_MAP(MapSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MapSelect message handlers

void MapSelect::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString WS;
	FILE *ws;
	WS.Format("%s\\Inter\\MapSelect.txt", OUTPUT);
	ws=fopen(WS, "w");
	if(ws==NULL)
	{
		CString note;
		note.Format("Cannot create file %s", WS);
		AfxMessageBox(note);
		exit(0);
	}
	fprintf(ws, "%s  %s", m_Watershed, m_yr);
	fclose(ws);
	
	CDialog::OnOK();
}
