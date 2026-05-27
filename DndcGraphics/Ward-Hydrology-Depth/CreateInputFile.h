#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <io.h>

void CreateDndcInputFiles(char *InputFileName);

class NewCropofEachYear
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
	int   seed_trans, PerennialCrop, Transplant;
	float GrowthReproductive, PsnEfficiency,PsnMax;//InitialBiomass
	float TreeAge, TreeCurrentAge, TreeLeafMax, TreeLeafMin;
	float Grain, Leaf, Straw, Root;    
	float GrainCN, RootCN, LeafCN, ShootCN;
    float CropTDD, WRuq, OptT, CropNFix, Vascularity;
	float GrainFill;
	int RootShape;
};