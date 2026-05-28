// ManureStorage.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ManureStorage.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManureStorage dialog


ManureStorage::ManureStorage(CWnd* pParent /*=NULL*/)
	: CDialog(ManureStorage::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManureStorage)
	m_separate = -1;
	//}}AFX_DATA_INIT
}


void ManureStorage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManureStorage)
	DDX_Radio(pDX, IDC_RADIO3, m_separate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManureStorage, CDialog)
	//{{AFX_MSG_MAP(ManureStorage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManureStorage message handlers

void ManureStorage::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString RC;
	FILE *rc;
	RC.Format("%s\\ManureSeparate.txt", INTERMANAGE);
	rc=fopen(RC, "w");
	if(rc==NULL) note(1, RC);
	fprintf(rc, "%d", m_separate);
	fclose(rc);

	CDialog::OnOK();
}
