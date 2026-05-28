#include "stdafx.h"
#include "dndc71.h"
#include "RunPaths.h"
#include "SitePara.h"
#include "dndc_main.h"
#include "dndc_tool.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void ReadCropPara1(int *v_CropID, char v_CropName[95][100], float *v_max_biomass_C, float *v_grain_fraction, float *v_leaf_fraction,
				  float *v_leafstem_fraction, float *v_root_fraction, float *v_GrainCN, 
				  float *v_LeafCN, float *v_ShootCN, float *v_RootCN, float *v_WaterDemand, float *v_OptimumT, 
				  float *v_TDD, float *v_Nfixation, float *v_Vascularity, int *v_Perennial, float *v_TreeAge, float* v_Root1, float* v_Root2, float* v_AGResp1, float* v_AGResp2,float* v_Kext1,float* v_Kext2,float* v_CMaxH, float* v_cropGRate, float* v_cropTime, float* v_RUEHI, float* v_DelayP)
{
	char text[400], js[200];
	CString CCrop;
	FILE *fCrop;
#ifdef CONSOLE
	CCrop.Format("%s\\lib_crop\\Crop_parameters.txt", LIBRARY);//, CropType);
#else
	CCrop.Format("%s\\Library\\lib_crop\\Crop_parameters.txt", ROOTDIR);//, CropType);
#endif
	fCrop = fopen(CCrop, "r");
	if(fCrop==NULL) note(0, CCrop);
	else
	{
		fgets(text, 400, fCrop);
		for(int j=1; j<=41; j++) //was set to 17 for reading in the old format for crop headers in the Crop_Parameters.txt file. Now set to 35 for NEW Crop_Parameters.txt file//41 with Theos update
			fscanf(fCrop, "%s", js);
		for(int i=0; i<=90; i++)//90 crop lies
		{
			fscanf(fCrop, "%d %s", &v_CropID[i], v_CropName[i]);
			fscanf(fCrop, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f", &v_max_biomass_C[i], 
				&v_grain_fraction[i], &v_leaf_fraction[i], &v_leafstem_fraction[i], &v_root_fraction[i], 
				&v_GrainCN[i], &v_LeafCN[i], &v_ShootCN[i], &v_RootCN[i],
				&v_WaterDemand[i], &v_OptimumT[i], &v_TDD[i], &v_Nfixation[i], &v_Vascularity[i]);
			fscanf(fCrop, "%d", &v_Perennial[i]);
			fscanf(fCrop, "%f %f %f %f %f %f %f %f %f %f %f", &v_Root1[i],&v_Root2[i], &v_AGResp1[i], &v_AGResp2[i],&v_Kext1[i], &v_Kext2[i], &v_CMaxH[i], &v_cropGRate[i], &v_cropTime[i], &v_RUEHI[i], &v_DelayP[i]);//, &v_TreeAge[i]);
			if (v_Vascularity[i] == 0.0)v_Vascularity[i] = 1.5;
			for (int z = 1; z <= 13; z++) //bypasses the last 17 info columns because they aren't being utilized.
				fscanf(fCrop, "%s", js);
		}
		fclose(fCrop);

	}	
}


void CellColor(int FluxType, float Para, int* Rr, int * Gg, int* Bb)
{	
	
	float SP;

	if(FluxType==1)//SOC
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 25.0;
	}
	else if(FluxType>=2&&FluxType<=8)//dSOC, CH4, grain, shhot, root, manur-C, litter-C 
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 35.0;
	}
	else if(FluxType==3)//CH4 
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 50.0;
	}
	else if(FluxType==9) //N2O
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 60.0;
	}
	else if(FluxType==14) //leach N
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 50.0;
	}
	else if(FluxType==18) //fertilizer N
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 40.0;
	}
	else
	{
		if(Para<=0.0) SP = 0.0;
		else SP = log10(Para) * 60.0;
	}
	
	float rr = 1.0*SP;

	if(rr<=0.0)
	{
		*Rr=255; *Gg=255; *Bb=255;
	}
	else if(rr<=255.0)
	{
		*Rr = (int)(0.005*rr*rr - 0.9021*rr + 230.43);//0.0022
		*Gg = (int)(-0.0042*rr*rr + 0.1492*rr + 241.6);
		*Bb = (int)(-0.9867*rr + 232.83);

		*Rr = min(255, max(0,*Rr));
		*Gg = min(255, max(0,*Gg));
		*Bb = min(255, max(0,*Bb));
	}
	else
	{
		*Rr=0; *Gg=0; *Bb=0;
	}


}


void FindCrops(char *cropping_system, int *crop_ID, int *CropNumber)
{
	int i;
	int SLL=strlen(cropping_system);
	int QQQ[5]={0,0}, _k=0, _CropNumber;	
	char _CropCode[10][30];
	for(i=0;i<SLL;i++)
	{
		if(cropping_system[i]=='_'||i==SLL-1) 
		{
			_k++;
			QQQ[_k]=i;
		}
	}

	_CropNumber = _k;

	if(_CropNumber==1) 
	{
		sprintf(_CropCode[1], "%s", cropping_system);
		crop_ID[1] = atoi(_CropCode[1]);
	}
	else if(_CropNumber==2)
	{
		Glean_String(cropping_system, 0, QQQ[1]-1, _CropCode[1]);
		Glean_String(cropping_system, QQQ[1]+1, SLL-1, _CropCode[2]);
		crop_ID[1] = atoi(_CropCode[1]);
		crop_ID[2] = atoi(_CropCode[2]);
	}
	else if(_CropNumber==3)
	{
		Glean_String(cropping_system, 0, QQQ[1]-1, _CropCode[1]);
		Glean_String(cropping_system, QQQ[1]+1, QQQ[2]-1, _CropCode[2]);
		Glean_String(cropping_system, QQQ[2]+1, SLL-1, _CropCode[3]);
		crop_ID[1] = atoi(_CropCode[1]);
		crop_ID[2] = atoi(_CropCode[2]);
		crop_ID[3] = atoi(_CropCode[3]);
	}	
	else
	{
		AfxMessageBox("The number of crops in this cropping system > 3");
		exit(0);
	}

	*CropNumber = _CropNumber;
}

int FileCopy(char *source, char *dest)
{
	FILE *fpi,*fpo;
	long flen,rt,num,adr;
	char *p;

	p=(char*)malloc(4096);
	if (p==NULL) {
		MessageBox(NULL,"No enough memory!","Running Error:",0);
		return -1;
	}

	fpi=fopen(source,"rb");
	if (fpi==NULL) 
	{
		CString note;
		note.Format("1. Source file does not exist: %s", source);
		AfxMessageBox(note);
		exit(0);
	}
	fpo=fopen(dest,"wb");
	if (fpo==NULL) {
		MessageBox(NULL,"Source file no exist!","Running Error:",0);
		return -1;
	}
	flen=_filelength(_fileno(fpi));
	num=4096;
	adr=0;
	for (;;) {
		fseek(fpi,adr,SEEK_SET);
		fseek(fpo,adr,SEEK_SET);
		if (adr+num>flen) num=flen-adr;
		rt=fread(p,sizeof(char),num,fpi);
		rt=fwrite(p,sizeof(char),num,fpo);
		adr+=num;
		if (adr==flen) break;
	}
	fclose(fpi);
	fclose(fpo);
	free(p);
	return 0;
}

int FileExpend(char *source, char *dest)
{
	FILE *fpi,*fpo;
	long flen,rt,num,adr;
	char *p;

	p=(char*)malloc(4096);
	if (p==NULL) {
		MessageBox(NULL,"No enough memory!","Running Error:",0);
		return -1;
	}

	fpi=fopen(source,"rb");
	if (fpi==NULL) 
	{
		CString note;
		note.Format("1. Source file does not exist: %s", source);
		AfxMessageBox(note);
		exit(0);
	}
	fpo=fopen(dest,"ab");
	if (fpo==NULL) {
		MessageBox(NULL,"Source file no exist!","Running Error:",0);
		return -1;
	}
	fprintf(fpo, "\n");
	flen=_filelength(_fileno(fpi));
	num=4096;
	adr=0;
	for (;;) {
		fseek(fpi,adr,SEEK_SET);
		fseek(fpo,adr,SEEK_SET);
		if (adr+num>flen) num=flen-adr;
		rt=fread(p,sizeof(char),num,fpi);
		rt=fwrite(p,sizeof(char),num,fpo);
		adr+=num;
		if (adr==flen) break;
	}
	fclose(fpi);
	fclose(fpo);
	free(p);
	return 0;
}

CString OrderNumber(int i,char *name,CString *txt)
{
	if (i==1) txt->Format("%dst %s",i,name);
	else if (i==2) txt->Format("%dnd %s",i,name);
	else if (i==3) txt->Format("%drd %s",i,name);
	else txt->Format("%dth %s",i,name);
	return *txt;
}

int ResetListItem(int newN,int oldN,char *name,CListCtrl *List)
{
	int i;
	CString txt;
	if (newN>oldN)
	{
		for (i=oldN+1;i<=newN;i++)
		{
			txt = OrderNumber(i,name,&txt);
			List->InsertItem(i-1,txt);
		}
	}
	else if (newN<oldN)
	{
		for (i=newN+1;i<=oldN;i++)
		{
			List->DeleteItem(newN);
		}
	}
	return 0;
}

void XX(FILE *xx)
{
	char vvv[200];

	fgets(vvv, 4, xx);
		if(strcmp(vvv, " XX")==0) 
		{
			fgets(vvv, 200, xx);
		}

}

CString PathAddFile(CString CoePath, CString file)
{
	if (CoePath.Right(1)=="\\") 
		CoePath=CoePath+file;
	else CoePath=CoePath+"\\"+file;

	return CoePath;
}

char *PathAddFile(char *CoePath, char *file)
{
	CString txt,txt1;
	txt=CoePath;
	txt1=file;
	CoePath = PathAddFile(CoePath, file);
	
	sprintf(file,"%s",CoePath);
	return file;
}

int NumberToChar(char *p,int n)
{
	int  od[3]={0,1,0},i;
	char ch[20];

	sprintf(p,"000000");
	sprintf(ch,"%d",n);
	i=strlen(ch);
	memcpy(p+od[i],ch,i);
	p[2]='\0';
	return 0;
}

int ChangeChar(char *name, char p1,char p2)
{
	int i,L=strlen(name);
	for (i=0;i<L;i++)
	{
		if (name[i]==p1) name[i]=p2;
	}
	return 0;
}

CString ChangeChar(CString Name, char p1,char p2)
{
	char str[256];
	sprintf(str,"%s",Name);
	ChangeChar(str, p1,p2);
	Name=str;
	return Name;
}

CString *EraseFBSpace(CString *str)
{
	char ch[256];
	sprintf(ch,"%s",*str);
	EraseFBSpace(ch);
	*str=ch;
	return str;
}

char * EraseFBSpace(char *str)
{
	while (str[0]==32)
	{
		sprintf(str,"%s",str+1);
	}
	int l=strlen(str);
	if (l>0) 
	{
		while (str[l-1]<=32)
		{
			str[strlen(str)-1]='\0';
			l=strlen(str);
		}
	}
	return str;
}

CString EraseAllSpace(CString *str)
{
	char txt[512],txt1[512];
	sprintf(txt,"%s",*str);
	sprintf(txt1,"%s",EraseAllSpace(txt));
	*str = txt1;
	return *str;
}

char *EraseAllSpace(char *str)
{
	EraseFBSpace(str);
	int i,l=strlen(str);
	for (i=0;i<l;i++)
	{
redo:	if (str[i]==32)
		{
			sprintf(str+i,"%s",str+i+1);
			goto redo;
		}
	}
	return str;
}

int GetShortFileName(char *ch)
{
	int i;
	for (i=strlen(ch)-1;i>=0;i--)
	{
		if (ch[i]==92)//'\\')
		{
			sprintf(ch,"%s",ch+i+1);
			break;
		}
		//if (ch[i]=='.') ch[i]='_';
	}
	return 0;
}

/*
char *GetDBFilePath(int ctry,char *fname)
//fname:subdir of DB when input, subpath when output
{
	if (ctry<=0) return NULL;
	char str[256],*p=RInf.CountryList.get(ctry);
	sprintf(str,"%s\\%s\\%s", ROOTDIR,fname,p);
	sprintf(fname,"%s",str);
	return fname;
}

char *GetDBFileHead(int ctry,char *fname)
//fname:subpath of DB when input, subpath+filehead when output
{
	if (ctry<=0) return NULL;
	char *p=RInf.CountryList.get(ctry);
	char p1[20],str[256];
	
	if (p==NULL) return NULL;

	strcpy(p1,p);
	if (strlen(p)>4) p1[4]='\0';
	sprintf(str,"%s\\%s\\%s\\%s", ROOTDIR,fname,p,p1);//database
	sprintf(fname,"%s",str);

	strlwr(fname);
	return fname;
}
*/

char *ValueToCString(char *str,float val)
{
	sprintf(str,"%f",val);
	return str;
}

float CheckValueRange(float z6,int high,int low)
{
	if (z6>high) z6=(float)high;
	else if (z6<low) z6=(float)low;
	return z6;
}

void note(int rw, char* ZZ)
{
	CString note;
	if(rw==0) note.Format("Cannot open %s", ZZ);
	else note.Format("Cannot create %s", ZZ);
	AfxMessageBox(note);
	exit(0);
}

void note(int rw, CString ZZ)
{
	CString note;
	if(rw==0) note.Format("Cannot open %s", ZZ);
	else note.Format("Cannot create %s", ZZ);
	AfxMessageBox(note);
	exit(0);
}

FILE *sopen (char *fname,char *mode)
{
	if (strcmp(mode,"w")==0) return sopen(fname,0);
	if (strcmp(mode,"r")==0) return sopen(fname,1);
	if (strcmp(mode,"a")==0) return sopen(fname,2);
	if (strcmp(mode,"wb")==0) return sopen(fname,3);
	if (strcmp(mode,"rb")==0) return sopen(fname,4);
	return NULL;
}

FILE* sopen (char *fname,int mode)
{
	char err[255];//IE[255],
	FILE *fp;

	//sprintf(IE, fname);
	if (mode==0) 
		fp = fopen(fname, "w");
	else if (mode==1) 
		fp = fopen(fname, "r");
	else if (mode==2) 
		fp = fopen(fname, "a");
	else if (mode==3) 
		fp = fopen(fname, "wb");
	else if (mode==4) 
		fp = fopen(fname, "rb");

	if ( fp == NULL )
	{
		if (mode==0) 
			sprintf(err,"Cannot open file: %s (File system may have error!)", fname);
		else
			sprintf(err,"Cannot open file: %s (File may not exist!)", fname);

		return (NULL);
	}
	return (fp);
}

void FileMessage(char* FILEname, int OC)
{
	char err[120];
	if(OC==0) sprintf(err, "Cannot create file %s", FILEname);
	else sprintf(err, "Cannot open file %s", FILEname);
	AfxMessageBox(err);
	exit(0);
}

void FileMessage(CString FILEname, int OC)
{
	CString note;
	if(OC==0) note.Format(note, "Cannot create file %s", FILEname);
	else note.Format(note, "Cannot open file %s", FILEname);
	AfxMessageBox(note);
	exit(0);
}

void Glean_String(char *String, int Num1, int Num2, char *Sub_Str)
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
}

float SOCtoNO3(float SOC, float latitude)
{
	float S_NO3 = 3.0 * (float)log(SOC) + 10.0;
	if(latitude<0.0) latitude *= -1.0;
	S_NO3 = S_NO3 / (90.0 - latitude); 
	S_NO3 = max(0.5, S_NO3);

	return(S_NO3);
}

void SocProfile(int landtype, float TTOO, float latitude, float *Soil_Litter, float *Soil_humads, float *Soil_humus, float *PassiveC)
{	
	if(landtype==2||landtype==5)//wetland soil
		*Soil_Litter = 0.01;
	else
		*Soil_Litter = 0.01;

    *Soil_humads = HumadsFraction(TTOO, landtype);	
	*PassiveC = 0.0;
	*Soil_humus = (1.0-*Soil_Litter-*Soil_humads-*PassiveC);
}

float HumadsFraction(float TTOO, int landtype)
{
	float HF;
	
	/*if(landtype==1)//upland cropland
		HF = 0.2;
	else if(landtype==2)//paddy rice cropland
		HF = 0.4;
	else if(landtype==3)//moist grassland
		HF = 0.4;
	else if(landtype==4)//dry grassland
		HF = 0.2;
	else if(landtype==5)//wetland
		HF = 0.6;//2.0 * TTOO;
	else {}	*/

	if(landtype==5)//wetland
		HF = 0.5;
	else if(landtype==2)//rice paddy
		HF = 1.0 * TTOO + 0.0138;
		//HF = 0.4;
	else
		HF = 0.4611 * TTOO + 0.0138;
		//HF = TTOO * 2.5;
		
	HF = min(0.5, max(0.01, HF));
	
	return(HF);
}

void CN_ratios(float *RCNRVL, float *RCNRL, float *RCNRR, float *RCNB, float *RCNH, float *RCNM, float *PassiveCCN)
{
	*RCNRVL = 5.;
	*RCNRL  = 25.;
	*RCNRR  = 100.;
    *RCNB   = 10.0;
	*RCNH   = 10.0;
	*RCNM   = 10.0;
	*PassiveCCN = 500.0;
}

void DefineManureDates(char* ManureRate, int* TotalManureApplications, int* CManureDate, float* CManureN, float* CManureCN)
{
	int i, MANURES=0, SLL, Ini[10], Mid[10][5]={0,0}, End[10], FF=0;
	char MANURED[20][10], MANUREN[20][10], MANUREM[20][10];
	
	SLL=strlen(ManureRate);

	for(i=0;i<=SLL;i++)//how many applications
	{
		if(ManureRate[i]=='/') 
		{
			MANURES++;
			Ini[MANURES] = i+1;
			End[MANURES-1] = i;
			FF=0;
		}

		if(ManureRate[i]=='_')
		{
			FF++;
			Mid[MANURES][FF] = i;
		}
	}
	End[MANURES] = SLL;

	for(i=1;i<=MANURES;i++)
	{
		Glean_String(ManureRate, Ini[i], Mid[i][1]-1, MANURED[i]);
		Glean_String(ManureRate, Mid[i][1]+1, Mid[i][2]-1, MANUREN[i]);
		Glean_String(ManureRate, Mid[i][2]+1, End[i], MANUREM[i]);

		CManureDate[i] = atoi(MANURED[i]);
		CManureN[i] = atof(MANUREN[i]);
		CManureCN[i] = atof(MANUREM[i]);
	}

	
	*TotalManureApplications = MANURES;
}

int FindOneCrop(char* CroppingSystem, int Cropid)
{
	int i, CC=0, SLL, Ini[10], End[10], CROPID[5]={0,0}, YN=0;
	char crop[5][10];
	
	SLL=strlen(CroppingSystem);

	for(i=0;i<=SLL;i++)//how many applications
	{
		if(CroppingSystem[i]=='_') 
		{
			CC++;
			Ini[CC] = i+1;
			End[CC-1] = i;
		}
	}
	
	if(CC==0) 
	{
		CC=1;
		Ini[CC]=0;
	}

	End[CC] = SLL;

	for(i=1;i<=CC;i++)//how many crops
	{
		if(i==CC)
			Glean_String(CroppingSystem, Ini[i], End[i], crop[i]);
		else
			Glean_String(CroppingSystem, Ini[i], End[i]-1, crop[i]);

		CROPID[i] = atoi(crop[i]);

		//Cropid: 0 all; 1 rice, 2, corn, 3 wheat
		if(Cropid==0)
		{
			YN = 1;
			break;
		}
		else if(Cropid==1)//rice-involved cropping systems
		{
			if(CROPID[i]==20||CROPID[i]==30||CROPID[i]==24||CROPID[i]==46) 
			{
				YN = 1;
				break;
			}
		}
		else if(Cropid==2)//maizee-involved cropping systems
		{
			if(CROPID[i]==1) 
			{
				YN = 1;
				break;
			}
		}
		else if(Cropid==3)//wheat-involved cropping systems
		{
			if(CROPID[i]==2||CROPID[i]==6) 
			{
				YN = 1;
				break;
			}
		}
		else
		{
			AfxMessageBox("Please select target cropping systems");
			exit(0);
		}
	}

	return(YN);
}

void DefineResidueDates(char* ResidueData, int* TotalResidueApplications, float* ResidueRate)
{
	int i, TILLS=0, SLL, Ini[10], End[10];
	char TillD[20][10], TillM[20][10];
	
	SLL=strlen(ResidueData);

	for(i=0;i<=SLL;i++)//how many applications
	{
		if(ResidueData[i]=='/') 
		{
			TILLS++;
			Ini[TILLS] = i+1;
			End[TILLS-1] = i;
		}
	}
	End[TILLS] = SLL;

	for(i=1;i<=TILLS;i++)//how many crops
	{
		if(i==TILLS)
			Glean_String(ResidueData, Ini[i], End[i], TillD[i]);
		else
			Glean_String(ResidueData, Ini[i], End[i]-1, TillD[i]);

		ResidueRate[i] = atof(TillD[i]);
	}

	*TotalResidueApplications = TILLS;
}

void DefineFloodDates(char* FloodDate, int* FloodIni, int* FloodEnd, int* FloodMethod, int* TotalFloodApplications)
{
	int i, MANURES=0, SLL, Ini[10], Mid[10][5]={0,0}, End[10], FF=0;
	char MANURED[20][10], MANUREN[20][10], MANUREM[20][10];
	
	SLL=strlen(FloodDate);

	for(i=0;i<=SLL;i++)//how many applications
	{
		if(FloodDate[i]=='/') 
		{
			MANURES++;
			Ini[MANURES] = i+1;
			End[MANURES-1] = i;
			FF=0;
		}

		if(FloodDate[i]=='_')
		{
			FF++;
			Mid[MANURES][FF] = i;
		}
	}
	End[MANURES] = SLL;

	for(i=1;i<=MANURES;i++)
	{
		Glean_String(FloodDate, Ini[i], Mid[i][1]-1, MANURED[i]);
		Glean_String(FloodDate, Mid[i][1]+1, Mid[i][2]-1, MANUREN[i]);
		if(i==MANURES)
			Glean_String(FloodDate, Mid[i][2]+1, End[i], MANUREM[i]);
		else
			Glean_String(FloodDate, Mid[i][2]+1, End[i]-1, MANUREM[i]);

		FloodIni[i] = atoi(MANURED[i]);
		FloodEnd[i] = atoi(MANUREN[i]);
		FloodMethod[i] = atoi(MANUREM[i]);

		FloodIni[i] = min(365, max(1, FloodIni[i]));
		FloodEnd[i] = min(365, max(1, FloodEnd[i]));
		
	}

	*TotalFloodApplications = MANURES;


}

void DefineTillDates(char *TillDates, int *TillDate, int *TillDepth, int *TotalTillApplications)
{
	int i, TILLS=0, SLL, Ini[20], Mid[20], End[20];
	char TillD[20][20], TillM[20][20];
	
	SLL=strlen(TillDates);

	for(i=0;i<=SLL;i++)//how many applications
	{
		if(TillDates[i]=='/') 
		{
			TILLS++;
			Ini[TILLS] = i+1;
			End[TILLS-1] = i;
		}

		if(TillDates[i]=='_')
		{
			Mid[TILLS] = i;
		}
	}
	End[TILLS] = SLL;

	for(i=1;i<=TILLS;i++)//how many crops
	{
		Glean_String(TillDates, Ini[i], Mid[i]-1, TillD[i]);
		Glean_String(TillDates, Mid[i]+1, End[i], TillM[i]);

		TillDate[i] = atoi(TillD[i]);
		TillDepth[i] = atoi(TillM[i]);

		TillDate[i] = min(365, max(1, TillDate[i]));
	}

	*TotalTillApplications = TILLS;

/*
	int i, T, SLL;
	int KKK[5]={0,0}, JJJ[5]={0,0}, _k=0, _j=0, _CropNumber=0;	
	char _jday[30];
	char JDAY[30][30];

	SLL=strlen(TillDates);

	JJJ[0]=0;
	for(i=0;i<=SLL;i++)
	{
		if(TillDates[i]=='_'||TillDates[i]=='-'||i==SLL-1) 
		{
			_j++;
			JJJ[_j]=i;

			if(TillDates[i]=='-'||i==SLL-1) 
			{
				_k++;
				KKK[_k]=i;
			}
		}
	}

	*TotalTillApplications = _k;

	for(i=0; i<_j; i++)
	{
		if(i==0) Glean_String(TillDates, JJJ[i], JJJ[i+1]-1, _jday);
		else if(i==_j-1) Glean_String(TillDates, JJJ[i]+1, JJJ[i+1], _jday);
		else Glean_String(TillDates, JJJ[i]+1, JJJ[i+1]-1, _jday);
		sprintf(JDAY[i], "%s", _jday);
	}
	
	int w=0;
	for(i=1; i<=_k; i++)
	{
		TillDate[i] = atoi(JDAY[w]);
		w++;
		TillDepth[i] = atoi(JDAY[w]);
		w++;
	}
*/
}

void DefinePHDates(char *PlantHarvDates, int *plant_jday, int *harvest_jday, int *cropping_number, 
				   int *WinterCrop, int *WCN)
{
	int i, CROPS=0, SLL, Ini[10], Mid[10], End[10];
	char SeedDate[20][10], HarvDate[20][10];
	
	SLL=strlen(PlantHarvDates);

	for(i=0;i<=SLL;i++)//how many crops
	{
		if(PlantHarvDates[i]=='/') 
		{
			CROPS++;
			Ini[CROPS] = i+1;
			End[CROPS-1] = i;
		}

		if(PlantHarvDates[i]=='_')
		{
			Mid[CROPS] = i;
		}
	}
	End[CROPS] = SLL;

	for(i=1;i<=CROPS;i++)//how many crops
	{
		Glean_String(PlantHarvDates, Ini[i], Mid[i]-1, SeedDate[i]);
		Glean_String(PlantHarvDates, Mid[i]+1, End[i], HarvDate[i]);

		plant_jday[i] = atoi(SeedDate[i]);
		harvest_jday[i] = atoi(HarvDate[i]);

		plant_jday[i] = min(365, max(1, plant_jday[i]));
		harvest_jday[i] = min(365, max(1, harvest_jday[i]));

		if(plant_jday[i]>harvest_jday[i])
		{
			*WinterCrop = 1;
			*WCN = i;
		}
	}

	*cropping_number = CROPS;

/*	
	
	JJJ[0]=0;
	for(i=0;i<=SLL;i++)
	{
		if(PlantHarvDates[i]=='_'||PlantHarvDates[i]=='-'||i==SLL-1) 
		{
			_j++;
			JJJ[_j]=i;

			if(PlantHarvDates[i]=='-'||i==SLL-1) 
			{
				_k++;
				KKK[_k]=i;
			}
		}
	}

	*cropping_number = _k;

	for(i=0; i<_j; i++)
	{
		if(i==0) Glean_String(PlantHarvDates, JJJ[i], JJJ[i+1]-1, _jday);
		else if(i==_j-1) Glean_String(PlantHarvDates, JJJ[i]+1, JJJ[i+1], _jday);
		else Glean_String(PlantHarvDates, JJJ[i]+1, JJJ[i+1]-1, _jday);
		sprintf(JDAY[i], "%s", _jday);
	}
	
	int w=0;
	for(i=1; i<=_k; i++)
	{
		plant_jday[i] = atoi(JDAY[w]);
		w++;
		harvest_jday[i] = atoi(JDAY[w]);
		w++;

		if(plant_jday[i]>harvest_jday[i])
		{
			*WinterCrop = 1;
			*WCN = i;
			//*cropping_number = _k+1;
		}
	}
*/
}

void DefineFertDates(char* FertDates, int* CropFertDate, int* CropFertType, 
					 float* CropFertRate, int *TotalFertApplications)//, int* CropFertTYPES, int* crop_ID, int cropping_number)
{
	int i, MANURES=0, SLL, Ini[20], Mid[20][20]={0,0}, End[10], FF=0;
	char MANURED[20][20], MANUREN[20][20], MANUREM[20][20];
	
	SLL=strlen(FertDates);

	for(i=0;i<=SLL;i++)//how many applications
	{
		if(FertDates[i]=='/') 
		{
			MANURES++;
			Ini[MANURES] = i+1;
			End[MANURES-1] = i;
			FF=0;
		}

		if(FertDates[i]=='_')
		{
			FF++;
			Mid[MANURES][FF] = i;
		}
	}
	End[MANURES] = SLL;

	for(i=1;i<=MANURES;i++)
	{
		Glean_String(FertDates, Ini[i], Mid[i][1]-1, MANURED[i]);
		Glean_String(FertDates, Mid[i][1]+1, Mid[i][2]-1, MANUREN[i]);
		if(i==MANURES)
			Glean_String(FertDates, Mid[i][2]+1, End[i], MANUREM[i]);
		else
			Glean_String(FertDates, Mid[i][2]+1, End[i]-1, MANUREM[i]);

		CropFertDate[i] = atoi(MANURED[i]);
		CropFertType[i] = atoi(MANUREN[i]);
		CropFertRate[i] = atof(MANUREM[i]);		
	}

	*TotalFertApplications = MANURES;
/*
	int i, FERTS=0, SLL, Ini[10], Mid[10][10], End[10], FF=0, FertTypes[10]={0,0};
	char FertDate[20][50], FertType[20][50], FertRate[20][50];
	int FT=0;

	SLL=strlen(FertDates);

	for(i=0;i<=SLL;i++)//how many applications
	{
		if(FertDates[i]=='/') 
		{
			FERTS++;
			Ini[FERTS] = i+1;
			End[FERTS-1] = i;
			//FertTypes[FERTS] = 1;
			//CropFertTYPES[FERTS] = FertTypes[FERTS];
			FT = 0;
		}

		if(FertDates[i]=='_')
		{
			//FertTypes[FERTS]++;
			FT++;
			Mid[FT][FERTS] = i;
			//CropFertTYPES[FERTS] = FertTypes[FERTS];
		}
		FertTypes[FERTS] = (int)FT/2;
	}
	End[FERTS] = SLL;
	//FertTypes[FERTS] = (int)FF/2;
*/
/*	int j;
	for(i=1;i<=FERTS;i++)//how many crops
	{
		CropFertTYPES[i] = FertTypes[i];

		for(j=1; j<=FertTypes[i]; j++)
		{	
			if(j==1&&FertTypes[i]==1)
			{
				Glean_String(FertDates, Ini[i], Mid[j][i]-1, FertDate[i]);
				Glean_String(FertDates, Mid[j][i]+1, Mid[j+1][i]-1, FertType[i]);
				Glean_String(FertDates, Mid[j+1][i]+1, End[i]-1, FertRate[i]);
			}
			else
			{
				if(j==1)
				{
					Glean_String(FertDates, Ini[i], Mid[j][i]-1, FertDate[i]);
					Glean_String(FertDates, Mid[j][i]+1, Mid[j+1][i]-1, FertType[i]);
					Glean_String(FertDates, Mid[j+1][i]+1, Mid[j+2][i]-1, FertRate[i]);
				}
				else if(j==FertTypes[i])
				{
					Glean_String(FertDates, Mid[j+1][i]+1, Mid[j+2][i]-1, FertType[i]);
					Glean_String(FertDates, Mid[j+2][i]+1, End[i]-1, FertRate[i]);
				}
				else
				{
					Glean_String(FertDates, Mid[j+1][i]+1, Mid[j+2][i]-1, FertType[i]);
					Glean_String(FertDates, Mid[j+2][i]+1, Mid[j+3][i]-1, FertRate[i]);
				}
			}
				
			CropFertDate[i] = atoi(FertDate[i]);
			CropFertType[i][j] = atoi(FertType[i]);
			CropFertRate[i][j] = atof(FertRate[i]);
		}
	}
*/
	//*TotalFertApplications = FERTS;

/*	int i, p, T, SLL, j=1, k=1, ddd[5][10]={0,0}, crops;
	int endn=0;
	char JDAY[30];

	int TotalApplications=0;

	SLL=strlen(FertDates);

	for(i=0;i<=SLL;i++)
	{
		if(FertDates[i]=='_') 
		{
			ddd[j][k]=i;
			k++;
			FertApplications[j]++;
			TotalApplications++;
		}
		if(FertDates[i]=='-') 
		{
			ddd[j][k]=i;
			FertApplications[j]++;
			j++;
			k=1;			
			TotalApplications++;
		}
	}
	ddd[j][k]=i-1;
	FertApplications[j]++;
	TotalApplications++;

	*cropping_number = j;
	 
	for(i=1; i<=j; i++)
	{
		for(p=1; p<=FertApplications[i]; p++)
		{
			Glean_String(FertDates, endn, ddd[i][p]-1, JDAY);
			endn = ddd[i][p]+1;
		
			CropFertDate[i][p] = atoi(JDAY);
		}
	}
	
	*TotalFertApplications = TotalApplications;
*/
}

void FindCropPara(char* CropPara, float *DMaxYield, float *DTDD, float *DWaterDemand, int CropID)
{
	int i, CROPS=0, SLL, Ini[10], Mid1[10], Mid2[10], End[10];
	char K1[20][10], K2[20][10], K3[20][10];
	
	SLL=strlen(CropPara);

	int flag=0;
	for(i=0;i<=SLL;i++)//how many crops
	{
		if(CropPara[i]=='/') 
		{
			CROPS++;
			Ini[CROPS] = i+1;
			End[CROPS-1] = i;
			flag=0;
		}

		if(CropPara[i]=='_'&&flag==0)
		{
			Mid1[CROPS] = i;
			flag=1;
		}
		else if(CropPara[i]=='_'&&flag==1)
		{
			Mid2[CROPS] = i;
			flag=2;
		}
	}
	End[CROPS] = SLL;

/*		else if(CropPara[i]=='_'&&flag==2)
		{
			Mid2[CROPS] = i;
			flag=3;
		}
		else if(CropPara[i]=='_'&&flag==3)
		{
			Mid2[CROPS] = i;
			flag=4;
		}
		else if(CropPara[i]=='_'&&flag==4)
		{
			Mid2[CROPS] = i;
			flag=5;
		}
		else if(CropPara[i]=='_'&&flag==5)
		{
			Mid2[CROPS] = i;
			flag=6;
		}*/
	//}
	//End[CROPS] = SLL;

	if(CropID==0)
	{
		DMaxYield[0] = 0.0;
		DTDD[0] = 0.0;
		DWaterDemand[0] = 0.0;
	}
	else
	{
		Glean_String(CropPara, Ini[1], Mid1[1]-1, K1[1]);
		Glean_String(CropPara, Mid1[1]+1, Mid2[1]-1, K2[1]);
		if(CROPS==1)
			Glean_String(CropPara, Mid2[1]+1, End[1], K3[1]);
		else if(CROPS==2)
			Glean_String(CropPara, Mid2[1]+1, End[1]-1, K3[1]);
		else if(CROPS==3)
			Glean_String(CropPara, Mid2[1]+1, End[1]-1, K3[1]);

		//DMaxYield[1] = atof(K1[1]);
		//DTDD[1] = atof(K2[1]);
		//DWaterDemand[1] = atof(K3[1]);

		DMaxYield[CropID] = atof(K1[1]);
		DTDD[CropID] = atof(K2[1]);
		DWaterDemand[CropID] = atof(K3[1]);
		
	}

	

	//*cropping_number2 = CROPS;




	///////////////////////////////////////////////////
/*	int i, ddd[4]={0,0}, SLL, k=0;
	char M1[50], M2[50], M3[50];

	SLL=strlen(CropPara);

	for(i=0;i<=SLL;i++)
	{
		if(CropPara[i]=='_') 
		{
			k++;
			ddd[k]=i;			
		}
	}

	Glean_String(CropPara, 1, ddd[1]-1, M1);
	Glean_String(CropPara, ddd[1]+1, ddd[2]-1, M2);
	Glean_String(CropPara, ddd[2]+1, SLL, M3);

	*DMaxYield = atof(M1);
	*DTDD = atof(M2);
	*DWaterDemand = atof(M3);
*/	
}

float CropTN(float TotC, float GraCN, float LeafCN, float ShoCN, float RooCN, float GraFra, float LeafFra, float ShoFra, float RooFra)
{
	float CropCN, TN;
	
	CropCN = 1.0 / (GraFra / GraCN + LeafFra / LeafCN + ShoFra / ShoCN + RooFra / RooCN);

	TN = TotC / CropCN;
	
	return(TN);
}