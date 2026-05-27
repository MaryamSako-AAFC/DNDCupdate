#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <io.h>

class StringArray//:CStringArray
{
private: 

	char *p[600];//**p;//101 only 100 years can be calculated
	
public:	
	int n;		//start from 1
	int tn;

	StringArray();
	~StringArray();
	int insert(int pos,char *dat);
	int del(int pos);
	int clear();
	char *get(int pos);
	int dim(int num);
};

class CropofEachYear
{
public:
    int   CropID, WCFlag;
	int   GeneID;
    int   Left;
    float Yield;
    int   HarYr;
    int   SeedDay;
    int   GrowDays;
    float LeftPrec;
    float MaxPlanN;
    int   CropOrder, CoverCrop;
	int   jdtrans;
	int   seed_trans, PerennialCrop;
	float InitialBiomass, GrowthVegetative, GrowthReproductive, PsnEfficiency,PsnMax;
	float Grain, Leaf, Straw, Root;    
	float GrainCN, RootCN, LeafCN, ShootCN;
    float CropTDD, WRuq, OptT, CropNFix, Vascularity;
};