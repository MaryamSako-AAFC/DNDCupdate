#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <fstream>
#include <stdlib.h>

float Penman_PET(float humidity, float air_temp, float max_temp, float min_temp, float wind_speed, 
				 float Day_Hrs, float PAR, float albedo)
{	
//trying new DailyPET


	//Penman-Monteith method for daily PET
	//Input data from measuremant 
		float RHmean = humidity; //measured daily mean relative humidity (%)
		float Tmean = air_temp; //measured mean daily air temperature (degree C)
		float Tmax = max_temp; //measured mean daily air temperature (degree C)
		float Tmin = min_temp; //measured mean daily air temperature (degree C)
		float u2 = wind_speed; //measured wind speed (m/second)	
		float AtmoP = 101.325f; //atmospheric pressure (kPa), = 760 mmHg
		float N = Day_Hrs; //calculated maximum possible duration of sunshine or dalight hours (hours)
		float n = 0.58f * N; //actual duration of sunshine (hours)
		float z = 50.0f; //elevation above sea level (m)

	//Input data from DNDC-modeled results
		float Ra = PAR; //extraterrestrial radiation, (MJ/m2/day)
		float Albedo = albedo; //measured or calculated albedo

	//Constants
		float G = 0.0; //soil heat flux density (MJ/m2/day)
		float As = 0.25; //refression constant, expressing the fraction of extraterestrial radiation reaching the earth on overcast days (n=0)
		float Bs = 0.50; //(As+Bs) = refression constant, expressing the fraction of extraterestrial radiation reaching the earth on clear days (n=N)
		double mu = 4.903 * pow(10.0,-9.0); //Stefan-Boltzmann constant (MJ/K^4/m^2/day)
		double gama = 0.000664742 * AtmoP; //psychrometric constatnt (kPa/degree C)	
		
		float delta = (4098.0f * (0.6108f * exp(17.27f*Tmean/(Tmean+237.3f)))) / ((Tmean+237.3f)*(Tmean+237.3f)); //slope vapour pressure curve (kPa/degree C)
		float E0_max = 0.6108f * exp(17.27f*Tmax/(Tmax+237.3f));
		float E0_min = 0.6108f * exp(17.27f*Tmin/(Tmin+237.3f));
		float E0_mean = 0.6108f * exp(17.27f*Tmean/(Tmean+237.3f));
		float Es = (E0_max + E0_min) * 0.5f; //saturation vapour pressure (kPa)
		float Ea = E0_mean * RHmean / 100.0f; //actual vapour pressure (kPa)
		// (Es - Ea) = saturation vapour pressure deficit (kPa)

		float KTmax = Tmax + 273.16f;
		float KTmin = Tmin + 273.16f;	
		
		float Rs = (As + Bs * n / N) * Ra; //measured or calculated solar or shortwave radiation (MJ/m2/day)
		float Rso = (0.75f + 0.00002f * z) * Ra;//calculated clear-sky radiation (MJ/m2/day)
		float Rns = (1.0f - Albedo) * Rs; //net solar or shortwave radiation (MJ/m2/day)
		float Rnl = mu * (powf(KTmax,4.0f)+powf(KTmin,4.0f))/2.0f * (0.34f - 0.14f*powf(Ea,0.5f)) * (1.35f * Rs/Rso - 0.35f); //net outgoing longwave radiation (MJ/m2/day)
		float Rn = Rns - Rnl; //net radiation at the crop surface (MJ/m2/day)	

		float DPET = (0.408f * delta * (Rn - G) + gama * 900.0f / (Tmean + 273.0f) * u2 * (Es-Ea)) / (delta + gama * (1.0f + 0.34f * u2));//mm/day
		
		float DailyPET = DPET / 1000.0f; //m water/day

	if(DailyPET<0.0f) DailyPET=0.0f;
	
	//if(flood_flag==1) DailyPET *= 1.3;

    //float year_PET += DailyPET;

	return(DailyPET);
}

/*FILE *sopen (char *fname,char *mode)
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
*/

float class_model::Picewise_Line_Value(float x, float *xx, float *yy, int Points)
//-------------------------------------------------------------
//Task: Get the linear interpolating from picewise lines
//Need: X_coordinate, x, Pointsof the lines: Points, xx[],yy[]
//Return value Y_coordinate
//--------------------------------------------------------------
{
  int i;
  float y;
  if(x<xx[0] || x>xx[Points-1]) {
    printf("x=%f xx[0]= %f xx[%5d]=%f\n",x,xx[0],Points-1, xx[Points-1]);
    Hint("Out of the picewise_line range. ","");
    return 0.0;
  }
  for(i=0; i<Points;i++)
     if(x>=xx[i] && x<=xx[i+1])
       y=Line_Value(x, xx[i], yy[i], xx[i+1], yy[i+1]);
  return y;
}

float class_model::Line_Value(float x, float x1,float y1, float x2, float y2)
//-------------------------------------------------------------
//Task: Get the linear interpolating or extrapolating value
//Need: X_coordinate, x, two points: (x1,y1) and (x2,y2)
//Return value Y_coordinate
//--------------------------------------------------------------
{
  float y;

  if(x2==x1) {
    Hint("Can not inter(extra)polate ", "x1=x2");
    return 0.0;
  }
  y=(y2-y1)/(x2-x1)*(x-x1)+y1;
  return y;
}

void class_model::Hint (char *Hint_Msg1, char *Hint_Msg2)
//-------------------------------------------------
// Task: Write two hint messages to a fixed row.
// Need: Two messages
// ------------------------------------------------
{
  int L1, L2, x1, x2, L, YL=12;

  L1=strlen(Hint_Msg1);
  L2=strlen(Hint_Msg2);
  L= (L1>L2) ? L1 : L2;
  if (L>75) L=75;
  if (L<25) L=25;
  x1=(int)(40-L/2)-3;
  x2=(int)(40+L/2)+3;
  //clear(x1, YL, x2, YL+6);
  //DLrectangle(x1, YL, x2, YL+6);

}

int class_model::JulianDay(int month, int day)
{
    int i, JDay;
	int   Mday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if (month<1 ||month>12 || day<1 ||day>31) return -1;

    JDay = 0;
    for (int iq=1; iq< month; iq++)
	{
        JDay += Mday[iq];
	}
    JDay += day;
	return JDay;
}

/*
int class_model::File_Copy(char *source, char *dest)
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
	if (fpi==NULL) {
		CString note;
		note.Format("Cannot open source file %s",source);
		AfxMessageBox(note);
		exit(0);
	}
	fpo=fopen(dest,"wb");
	if (fpo==NULL) {
		CString note;
		note.Format("Cannot create file %s", dest); 
		AfxMessageBox(note);
		exit(0);
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
*/

float class_model::day_ref_par(int Jday, float LATITUDE)
{

/*   daylength and horizontal potential insolation for day
      from Swift (1976) Water Resour Res 12:108 and Sellers (1965) Physical Climatology
   Jday     day of the year
   Lat      latitude, radians
   I0       potential insolation (horizontal) J/m2
   DECL     declination of the sun, radians
   R        radius vector of the sun, dimensionless
   h        half daylength
   isc      solar constant, W/m2, Lean 1991 Rev. Geophysics 29:
   Half daylength and declination equations from:
       Swift, L.W.Jr.(1976). Algorithm for solar radiation on mountain
       slopes. Water Resources Research, 12(1) 118-112.
*/
float pi, isc, lat, r, Z, decl, z2, H, TA, AC, acos, psolrad, solrad;
float DayPAR, PARc, cloud;

pi = 3.1416f;
isc = 1367.0f;     //solar max Lean 1991 Rev. Geophysics 29
cloud = 0.75f;// 0.48;

lat = LATITUDE * (2.0f * 3.1416f) / 360.0f; //latitude in radians

r = 1.0f - .0167f * (float)cos(.0172f * (Jday - 3)); //radius vector of the sun

Z = .398f * (float)sin(4.869 + .0172 * Jday + .0334 * (float)sin(6.224 + .0172 * Jday)); //temporary variable

if (fabs(Z) < .7)
   decl = (float)atan(Z / (powf((1 - Z * Z), 0.5)));
else
   decl = pi / 2 - (float)atan(powf((1 - Z * Z), 0.5) / Z);

if (fabs(lat) >= pi / 2) lat = (pi / 2 - .01f);

z2 = -(float)tan(decl) * (float)tan(lat); //temporary variable

if (z2 >= 1)            //sun stays below horizon
  H = 0;
else if (z2 <= -1)      //sun stays above the horizon
  H = pi;
else
{
  TA = fabs(z2);
  if (TA < .7) AC = 1.571f - (float)atan(TA / powf((1 - TA * TA), 0.5));
  else	AC = (float)atan(powf((1 - TA * TA), 0.5) / TA);

  if (z2 < 0) acos = 3.1416f - AC;
  else acos = AC;

  H = acos;
}

psolrad = isc * (86400 / (3.1416f * r*r)) *
	  (H * (float)sin(lat) * (float)sin(decl) +
	  (float)cos(lat) * (float)cos(decl) * (float)sin(H));
	  //potential insolation, J/m2/day

solrad = psolrad * cloud / 1000000.0f; // million J/m2/day

DayPAR = solrad * 2.05f; //PAR, moles/m2/day

float DayHrs = 2 * (H * 24) / (2 * 3.1416f); //Length of day (hr)

PARc = DayPAR / (DayHrs * .0036f); //daily instantaneous PAR, u moles/m2/second

return (solrad);

}


void note(int rw, CString ZZ)
{
	CString note;
	if(rw==0) note.Format("Cannot open %s", ZZ);
	else note.Format("Cannot create %s", ZZ);
	AfxMessageBox(note);
	exit(0);
}

void note(int rw, char* filename)
{
	CString newname;
	newname.Format("%s", filename);
	note(rw, newname);
}

void note(int rw, wchar_t* filename)
{
	CString newname;
	newname.Format("%hs", filename);
	note(rw, newname);
}

void note(char * message){
	CString note;
	note.Format("%s", message);
	AfxMessageBox(message);
	exit(0);
}


/*
int Depth_convert_to_layer(float DepthO, float *hh, int q)
{
	int LayerN, Qflag=0;

	float Tk=0.0;
	for(int i=1;i<=1000;i++)
	{
		if(i<=q) Tk += hh[i];
		else Tk += hh[q];
		if(Tk>=DepthO)
		{
			LayerN = i-1;
			Qflag=1;
			break;
		}
	}

	if(Qflag==0) LayerN = q;
	return(LayerN);
}
*/

float Layer_convert_to_depth(int l, float *hh)
{
	float Tk=0.0;
	for(int i=1;i<=l;i++)
	{
		Tk += hh[i];
	}

	return(Tk);
}

float SOCtoNO3(float SOC, float latitude)
{
	float S_NO3 = 3.0f * (float)log(SOC) + 10.0f;
	if(latitude<0.0f) latitude *= -1.0f;
	S_NO3 = S_NO3 / (90.0f - latitude); 
	S_NO3 = max(0.5f, S_NO3);

	return(S_NO3);
}

char *EraseFBSpace(char *str)
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

void ErrorMessage(char *EMSS, int EDD)
{
	CString OMM;
	OMM.Format("%s\\ErrorMessage_%d", OUTPUT, EDD);
	FILE* emss;
	emss=fopen(OMM, "w");
	fprintf(emss, "%s\n", EMSS);
	fclose(emss);
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

//File helper functions
bool fexists(const char *filename)
{
	using namespace std;
	ifstream ifile(filename);
	return bool((ifile));
}

bool fexists(const wchar_t *filename)
{
	char newname[255];
	wcstombs(newname, filename, 255);
	return fexists(newname);
}