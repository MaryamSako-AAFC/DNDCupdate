// ExtractData.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "ExtractData.h"
#include "dndc_tool.h"
#include "dndc_main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//void Glean_Stringk(char *String, int Num1, int Num2, char *Sub_Str);
void ReadWrite2(char *NameSeries, CString AlterScenario, CString MaxMin, CString Item, int year, FILE *ref, int vvv);
float Average[20];
char FileName[255][255];
/////////////////////////////////////////////////////////////////////////////
// ExtractData dialog


ExtractData::ExtractData(CWnd* pParent /*=NULL*/)
	: CDialog(ExtractData::IDD, pParent)
{
	//{{AFX_DATA_INIT(ExtractData)
	m_years = 1;
	m_year1 = 1;
	m_Yield = FALSE;
	//}}AFX_DATA_INIT
}


void ExtractData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ExtractData)
	DDX_Control(pDX, IDC_OutputFileList, m_OutputFileList);
	DDX_Text(pDX, IDC_Years, m_years);
	DDX_Text(pDX, IDC_year1, m_year1);
	DDX_Check(pDX, IDC_Yield, m_Yield);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ExtractData, CDialog)
	//{{AFX_MSG_MAP(ExtractData)
	ON_BN_CLICKED(IDC_SelectFile, OnSelectFile)
	ON_LBN_DBLCLK(IDC_OutputFileList, OnDblclkOutputFileList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ExtractData message handlers



void ExtractData::OnSelectFile() 
{
	// TODO: Add your control notification handler code here

	CString cst;

	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num;
	num=m_OutputFileList.GetCount();
	if (num==4) return;
	
	k=m_OutputFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		if (cst=="") break;
		strcpy(FileName[k],cst);
		m_OutputFileList.InsertString(k,FileName[k]);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_OutputFileList.GetCount()==4) break;
		k++;
	}
	m_OutputFileList.SetCurSel(k);






/*
	UpdateData(TRUE);
	
	char FileName[500][5];
	CString cst;
AGAIN:
	CFileDialog  ask( true, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		"All Files (*.*)|*.*|Data Files (*.dat)|*.dat|Text Files (*.txt)|*.txt||", NULL );
	//OFN_FILEMUSTEXIST
	ask.DoModal();
	POSITION pos=ask.GetStartPosition();
	
	int k,num, i;
	num=m_OutputFileList.GetCount();
	if (num==4) return;
	
	k=m_OutputFileList.GetCurSel();
	if (k==-1) k=num;
	else k++;

	for (;;)
	{
		cst=ask.GetNextPathName(pos);
		int ll=strlen(cst);

		if (cst=="") break;
		int w=-1, kk=0, jj=50;
		for(;;)
		{
			w++;
			if(cst[w]=='r') 
			{
				kk++;
				jj=w;
			}

			if(cst[jj+1]=='a') kk++;
			else kk=0;
			if(cst[jj+2]=='t') kk++;
			else kk=0;
			if(cst[jj+3]=='e') kk++;
			else kk=0;

			if(kk==4)
			{
				CString err;
				err.Format("Please select a file starting with sum");
				AfxMessageBox(err);
				goto AGAIN;
			}

			if(w==ll-1) break;
		}

		strcpy(FileName[k],cst);
		m_OutputFileList.InsertString(k,FileName[k]);
		if (cst.IsEmpty() || pos==NULL) break;
		if (m_OutputFileList.GetCount()==1) break;
		k++;
	}
	m_OutputFileList.SetCurSel(k);

	CString SFF;
	FILE *sff;
	SFF.Format("%s\\Inter\\FileReview", OUTPUT);
	sff=fopen(SFF, "w");
	if(sff==NULL) note(1, SFF);
	
	for(i=0;i<4;i++) fprintf(sff, "%s\n", FileName[i]);
	fclose(sff);	

	UpdateData(FALSE);
*/
 }


void ExtractData::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString fname;

	CString SFF;
	FILE *sff;
	SFF.Format("%s\\Inter\\FileReview", OUTPUT);
	sff=fopen(SFF, "w");
	if(sff==NULL) note(1, SFF);
	
	for(int i=0;i<4;i++) 
	{
		m_OutputFileList.GetText(i,fname);
		fprintf(sff, "%s\n", fname);
	}
	fclose(sff);	

/*
	int years, year1, OKflag=0, ll, i, GID, CID, yr;
	CString SFF, SF, TF;
	char cst[200], js[50], crop[50], zzz[300];
	FILE *sff, *sf, *tf;
	char RRII[50][30];//={"","SOC","dSOC","CH4","GrainC","ShootC","RootC","ManureC","LitterC","N2O","NO","N2","NH3","UptakeN","LeachN","DepositN","FixedN","Miner_N","Fert_N","ManureN","dSON","dSIN","H2Otran","H2Oevap","H2Orunof","H2Oleach","H2Oirri","H2Oprec","SoilH2O"};
	float rate[30], sum[30], ha, total[30]={0.0,0.0}, TotalArea=0.0;
	
	UpdateData(TRUE);

	if(m_years==0||m_year1==0)
	{
		CString err;
		err.Format("Please specify initiative year and total years for processing");
		AfxMessageBox(err);
		exit(0);
	}

	years=m_years;
	year1=m_year1;	

	SFF.Format("%s\\Inter\\FileReview", OUTPUT);
	sff=fopen(SFF, "r");
	if(sff==NULL) note(0, SFF);
	
	fscanf(sff, "%s", cst);
	fclose(sff);

	ll=strlen(cst);

	if(ll<=0)
	{
		CString err;
		err.Format("Please select a file");
		AfxMessageBox(err);
		return;
	}

	char NameRoot[200];

	Glean_String(cst, 0, ll-9, NameRoot);


	SF.Format(cst);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);
	
	fscanf(sf, "%s %s %s %s %s", js,js,js,js,js);
	for(i=1; i<=28; i++) fscanf(sf, "%s", RRII[i]);
	fgets(zzz, 600, sf);
	fgets(zzz, 600, sf);
	fgets(zzz, 600, sf);

	TF.Format("%s_sum_yr%d.txt", NameRoot, year1);
	tf=fopen(TF, "w");
	if(sff==NULL) note(1, TF);
	
	fprintf(tf, "%12s %12s %12s %12s %12s","GridID","CropID","CropName","Area", "Year");
	for(i=1; i<=28; i++) fprintf(tf, "%12s ", RRII[i]);
	fprintf(tf, "\n");
	fprintf(tf, "%12s %12s %12s %12s %12s","","","","ha", "");
	for(i=1; i<=8; i++) fprintf(tf, "%12s ", "kgC");
	for(i=1; i<=13; i++) fprintf(tf, "%12s ", "kgN");
	for(i=1; i<=7; i++) fprintf(tf, "%12s ", "m3");
	fprintf(tf, "\n");	

	for(;;)
	{
		if(fscanf(sf, "%d %d %s %f %d", &GID, &CID, crop, &ha, &yr)!=5) break;
		if(yr==year1) fprintf(tf, "%12d %12d %12s %12.0f %12d", GID, CID, crop, ha, yr);
		for(i=1; i<=28; i++) 
		{
			fscanf(sf, "%f", &rate[i]);
			sum[i] = rate[i] * ha;
			
			if(yr==year1) 
			{
				fprintf(tf, "%12.0f ", sum[i]);
				total[i] += sum[i];
				TotalArea += ha;
			}
		}
		if(yr==year1) fprintf(tf, "\n");
	}

	fprintf(tf, "%12s %12s %12s %12.0f %12s", "Total", "", "", TotalArea, "");
	for(i=1; i<=28; i++) fprintf(tf, "%12.0f ", total[i]);
	fprintf(tf, "\n");		
	
	fclose(sf);
	fclose(tf);
*/
	AfxMessageBox("Conversion is accomplished");
	
	CDialog::OnOK();
}

void ReadWrite2(char *NameSeries, CString AlterScenario, CString MaxMin, CString Item, int year, FILE *ref, int vvv)
{
	char xxx[300], CountyID[50][50];
	int i, j;
	float number[20][20];
	FILE *sff;

	sff=fopen(NameSeries, "r");
	if(sff==NULL) note(0, NameSeries);
	
	fgets(xxx, 200, sff);
	fgets(xxx, 200, sff);
	fgets(xxx, 200, sff);

	if(year==2000) fprintf(ref, "CountyID ");

	for(j=1; j<=18; j++)
	{	
		fscanf(sff, "%s", CountyID[j]);

		if(year==2000)	
		{			
			fprintf(ref, "%10s ", CountyID[j]);
			if(j==18) fprintf(ref, "\n");

			Average[j]=0.0;
		}

		for(i=1; i<=12; i++)
		{
			fscanf(sff, "%f", &number[i][j]);
		}
	}
	fclose(sff);

	fprintf(ref, "%8d ", year);
	for(j=1; j<=18; j++) 
	{
		float RR;

		if(vvv==4) RR = number[12][j]*100.0;
		else RR = number[12][j];
			
		fprintf(ref, "%10.1f ", RR);

		Average[j] += RR/21.0;
	}
	fprintf(ref, "\n");

}

/*void Glean_Stringk(char *String, int Num1, int Num2, char *Sub_Str)
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

void ExtractData::ReadWrite()
{
	float Flux[3200][22]={0.0,0.0};
	float yield[3200][22]={0.0,0.0};
	int years, bb, TotalCrop, aa, i;
	int PolygonID[3200];
	int HA[3200]={0,0};
	char NameSeries[150], NameRoot[120];
	CString FN[25];
	char fff[300];
	float jk, FF, ha, average, TotalFlux=0.0, TotalHa=0.0;
	CString Xname;
	FILE *xn;
	
	Xname.Format("%s\\Inter\\MapData", OUTPUT);
	xn=fopen(Xname, "r");
	if(xn==NULL) note(0, Xname);
	
	fscanf(xn, "%d", &years);
	fscanf(xn, "%s", NameRoot);
	for(bb=1;bb<=years;bb++)
	{
		fscanf(xn, "%s",NameSeries); 
		FN[bb].Format("%s", NameSeries);
	}
	fclose(xn);

	for(bb=1;bb<=years;bb++)
	{
		Xname.Format(FN[bb]);
		xn=fopen(Xname, "r");
		if(xn==NULL) note(0, Xname);
		
		fgets(fff, 200, xn);
		fgets(fff, 200, xn);
		fgets(fff, 200, xn);

		fscanf(xn, "%d", &TotalCrop); 
		fgets(fff, 200, xn);
		fgets(fff, 200, xn);
		fgets(fff, 200, xn);

		aa=0;
		for(;;)
		{
			aa++;
			if(fscanf(xn, "%d", &PolygonID[aa])!=1)
			{
				aa=aa-1;
				break;
			}
			
			/*if(fscanf(xn, "%f", &YY)!=1) 
			{
				aa=aa-1;
				break; 
			}
			else
				yield[aa][bb]=YY;
			if(m_Yield==1) fgets(fff, 300, xn);
			else*/
			{
				for(int i=1; i<=TotalCrop; i++) 
				{
					if(fscanf(xn, "%f", &jk)!=1) 
					{
						aa=aa-1;
						break; 
					}
				}

				if(fscanf(xn, "%f %f %f", &FF, &ha, &average)!=3) 
				{
					aa=aa-1;
					break; 
				}
				else
				{
					
					Flux[aa][bb] = FF;
					HA[aa] = (int)ha;
				}
			}
		}
		fclose(xn);
	}

	CString NewFile;
	FILE *NF;

	NewFile.Format("%s_FLUX", NameRoot);
	NF=fopen(NewFile, "w");
	if(NF==NULL) note(1, NewFile);
	
	for(i=1; i<= aa; i++)
	{
		if(i==1)
		{
			fprintf(NF, "%7s,", "Year");
			for(bb=1; bb<=years; bb++) fprintf(NF, "%10d,", bb);
			fprintf(NF, "\n");
		}

		fprintf(NF, "%7d,", PolygonID[i]);
		for(bb=1; bb<=years; bb++)
		{	
			//if(m_Yield==1)
			//	fprintf(NF, "%10.2f,", yield[i][bb]);
			//else
				fprintf(NF, "%10.2f,", Flux[i][bb]);

				TotalFlux+=Flux[i][bb];
		}
		fprintf(NF, "\n");		
	}
	fclose(NF);

	CString note;
	note.Format("%f", TotalFlux);
	AfxMessageBox(note);
	return;

	/*if(m_Yield==0)
	{
		NewFile.Format("%s_AREA", NameRoot);
		NF=fopen(NewFile, "w");
		if(NF==NULL)
		{
			CString err;
			err.Format("Cannot create %s", NewFile);
			AfxMessageBox(err);
			exit(0);
		}

		for(i=1; i<= aa; i++)
		{
			if(i==1) fprintf(NF, "%7s, %7s\n", "ID", "ha");
			
			fprintf(NF, "%7d,%10d,\n", PolygonID[i], HA[i]);
		}
		fclose(NF);
	}*/

}


void ExtractData::OnDblclkOutputFileList() 
{
	// TODO: Add your control notification handler code here
	int i,num;
	
	num=m_OutputFileList.GetCount();
	i=m_OutputFileList.GetCurSel();
	
	CString fname;
	m_OutputFileList.GetText(i,fname);
	m_OutputFileList.DeleteString(i);	
	return;
}
