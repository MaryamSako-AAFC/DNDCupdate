#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
class_manure MData;

int MJulianDay(int month, int day);

void class_manure::ManureTreatmentFacility(int q, int scale, int *CompostCover, float *LagoonCapacity,int year)//year?
{
	MData.FN = 1;
	MData.GN = q+1;

	int i;
	CString LAI;
	FILE *cm;

	//COMPOST
	MData.FN = 4;
	MData.GN = q+4;

	CString SF;
	FILE* sf;

	int CompostRemoveMonth, CompostRemoveDay;

	SF.Format("%s\\Inputs\\ManureCompost.txt", OUTPUT);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);
	
	fscanf(sf, "%f  %d  %d  %f  %f\n", &MData.m_CompostPoro, &MData.m_CompostCover, &MData.m_ManureRemoveTimes[MData.FN], 
		&MData.m_LitterAmount, &MData.m_LitterCN); 
	{
	for(int i=1;i<=MData.m_ManureRemoveTimes[MData.FN];i++)
	{
		fscanf(sf, "%d %d %f %f %f\n", &CompostRemoveMonth,&CompostRemoveDay,&MData.m_ToField[MData.FN][i], &MData.m_ToMarket[MData.FN][i], &MData.m_Remain[MData.FN][i]);
	
		MData.m_CompostRemoveDate[MData.FN][i] = MJulianDay(CompostRemoveMonth, CompostRemoveDay);
	}
	}
	fclose(sf);
	
	*CompostCover = MData.m_CompostCover;

	//MData.m_CompostRemoveDate[MData.FN][i]; MData.m_ManureRemoveTimes[MData.FN]

	//LAGOON
	MData.FN = 5;
	MData.GN = q+5;
	//need to read appropriate year lagoon file!
	SF.Format("%s\\Inputs\\ManureLagoon_%d.txt", OUTPUT,year);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);
	
	fscanf(sf, "%f  %f  %d  %d  %d", &MData.m_LagoonCapacity, &MData.m_LagoonSurfaceArea, &MData.m_LagoonCover, 
		&MData.m_LagoonRain, &MData.m_ManureRemoveTimes[MData.FN]); 
	{
	for(int i=1; i<=MData.m_ManureRemoveTimes[MData.FN]; i++)
	{
		int DrainMonth, DrainDay;
		fscanf(sf, "%d %d %f %f %f", &DrainMonth, &DrainDay, &MData.m_ToField[MData.FN][i], &MData.m_ToMarket[MData.FN][i], &MData.m_Remain[MData.FN][i]);
		fscanf(sf, "%d %f", &MData.m_LagoonFieldAplMethod[i], &MData.m_LagoonFieldAplDepth[i]);

		MData.m_LagoonDrainDate[MData.FN][i] = MJulianDay(DrainMonth, DrainDay);
	}
	}
	fclose(sf);

	*LagoonCapacity = MData.m_LagoonCapacity;
	MData.m_LagoonDepth = MData.m_LagoonCapacity / MData.m_LagoonSurfaceArea;//m

	//DIGESTER
	MData.FN = 6;
	MData.GN = q+6;
	
	SF.Format("%s\\Inputs\\ManureDigester.txt", OUTPUT);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);

	fscanf(sf, "%d  %f  %f", &MData.m_DigesterTemp, &MData.m_DigesterCH4, &MData.m_ManureRemoveFrequency[MData.FN]); 
	fscanf(sf, "%f  %f  %f", &MData.m_ToField[MData.FN][1], &MData.m_ToMarket[MData.FN][1], &MData.m_Remain[MData.FN][1]);

	fclose(sf);

	if(MData.m_DigesterTemp==0) MData.m_DigesterCH4 = 0.1;
		else if(MData.m_DigesterTemp==1) MData.m_DigesterCH4 = 0.12;
		else if(MData.m_DigesterTemp==2) MData.m_DigesterCH4 = 0.15;
		else MData.m_DigesterTemp = 0.0;

	//MData.m_ToField[MData.FN][1] = MData.m_ToField[MData.FN][1];///= MData.m_ManureRemoveFrequency[MData.FN];
	//MData.m_ToMarket[MData.FN][1] = MData.m_ToMarket[MData.FN][1];///= MData.m_ManureRemoveFrequency[MData.FN];
	MData.m_Remain[MData.FN][1] = 1.0 - MData.m_ToField[MData.FN][1] - MData.m_ToMarket[MData.FN][1];

	//FIELD
	MData.FN = 7;
	MData.GN = q+7;
	
	SF.Format("%s\\Inputs\\ManureField.txt", OUTPUT);
	sf=fopen(SF, "r");
	if(sf==NULL) note(0, SF);	
	fscanf(sf, "%f", &MData.ManureFieldArea);
	fclose(sf);

	if(scale==1) 
		MData.ManureFieldArea = 0.0;

}

int MJulianDay(int month, int day)
{
    int JDay;
	int   Mday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if (month<1 ||month>12 || day<1 ||day>31) return -1;

    JDay = 0;
    for (int iz1=1; iz1< month; iz1++)
	{
        JDay += Mday[iz1];
	}
    JDay += day;
	return JDay;
}

#endif
