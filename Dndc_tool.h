#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <io.h>

//FILE *sopen (char *fname, int mode);
//FILE *sopen (char *fname, char *mode);
void note(int rw, char* ZZ);
void note(int rw, CString ZZ);
void note(int rw, wchar_t* filename);
void note(char*);

//int Depth_convert_to_layer(float DepthO, float *hh, int q);
float Layer_convert_to_depth(int l, float *hh);
float SOCtoNO3(float SOC, float latitude);
float Penman_PET(float humidity, float air_temp, float max_temp, float min_temp, float wind_speed, 
				 float Day_Hrs, float PAR, float albedo);
char *EraseFBSpace(char *str);
void ErrorMessage(char *EMSS, int EDD);
void FindCrops(char *cropping_system, int *crop_ID, int *CropNumber);
void Glean_String(char *String, int Num1, int Num2, char *Sub_Str);

//File helper functions
bool fexists(const char *filename);
bool fexists(const wchar_t *filename);