
#include "stdafx.h"
#include "RunPaths.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "direct.h"

#ifdef MANURE 
extern class_manure MData;
#endif

/*
#ifdef HYDRO
//===add by dengjia to record month result===
//===Record daily and month result;dengjia===
// record the daily result
	static float DDmuslerunoff[366][10][30][3][2]={0.0,0.0};
    static float DDmuslesedyld[366][10][30][3][2]={0.0,0.0};
    static float DDmuslesoc[366][10][30][3][2]={0.0,0.0};
    static float DDmusleson[366][10][30][3][2]={0.0,0.0};
    static float DDmuslenh4[366][10][30][3][2]={0.0,0.0};
    static float DDmusleno3[366][10][30][3][2]={0.0,0.0};
    static float DDmuslenh3[366][10][30][3][2]={0.0,0.0};
    static float DDmusleurea[366][10][30][3][2]={0.0,0.0};
    static float DDmusleclayn[366][10][30][3][2]={0.0,0.0};
	
// sum some daily result
	static float DDsumrunoff[366][10][30][3][2]={0.0,0.0};
	static float DDsumno3[366][10][30][3][2]={0.0,0.0};
	static float DDsumn[366][10][30][3][2]={0.0,0.0};

// record month result
	static float MMleach[13][10][30][3][2]={0.0,0.0};
    static float MMleachN[13][10][30][3][2]={0.0,0.0};
    static float MMmuslerunoff[13][10][30][3][2]={0.0,0.0};
    static float MMmuslesedyld[13][10][30][3][2]={0.0,0.0};
    static float MMmuslesoc[13][10][30][3][2]={0.0,0.0};
    static float MMmusleson[13][10][30][3][2]={0.0,0.0};
    static float MMmuslenh4[13][10][30][3][2]={0.0,0.0};
    static float MMmusleno3[13][10][30][3][2]={0.0,0.0};
    static float MMsumrunoff[13][10][30][3][2]={0.0,0.0};
    static float MMsumno3[13][10][30][3][2]={0.0,0.0};
    static float MMsumn[13][10][30][3][2]={0.0,0.0};

void class_model::MonthData(int S_ThisYear, int landuse, int S_SoilYear, float crop_ha, int IrriType)
{   
	int Mday[13];
	int k=0;
    Mday[2] = 28;
    Mday[4] = Mday[6] = Mday[9] = Mday[11] = 30;
    Mday[1] = Mday[3] = Mday[5] = Mday[7] = Mday[8] = Mday[10] = Mday[12] = 31;
	int y;
	for(y=1; y<=12; y++)
	{
        MMleach[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMleachN[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMmuslerunoff[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMmuslesedyld[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMmuslesoc[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMmusleson[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMmuslenh4[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMmusleno3[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMsumrunoff[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
	    MMsumno3[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
 	    MMsumn[y][S_ThisYear][landuse][S_SoilYear][IrriType]=0;
		for(int x=1;x<=Mday[y];x++)
		{
			k++;

		if(crop_ha>0.0)
		{
		    MMleach[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDleach[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMleachN[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDLeachN[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMmuslerunoff[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDmuslerunoff[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMmuslesedyld[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDmuslesedyld[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMmuslesoc[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDmuslesoc[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMmusleson[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDmusleson[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMmuslenh4[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDmuslenh4[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMmusleno3[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDmusleno3[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMsumrunoff[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDsumrunoff[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMsumno3[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDsumno3[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			MMsumn[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=DDsumn[k][S_ThisYear][landuse][S_SoilYear][IrriType];
			
		}
		else
		{

		    MMleach[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMleachN[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMmuslerunoff[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMmuslesedyld[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMmuslesoc[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMmusleson[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMmuslenh4[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMmusleno3[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMsumrunoff[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMsumno3[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
			MMsumn[y][S_ThisYear][landuse][S_SoilYear][IrriType]+=0.0;
	
		}		
		}
	}// end month loop
}
#endif


#ifdef HYDRO//===add by dengjia to record month result===
void class_model::Month_record(int S_SimuYears, int ii_ha, char* CountryName, char* ScenarioName, 
							   int cell_ID1, int crop_number, char* r_Province, int IrriType)
{
	CString MI[11]={"LeachWater", "LeachN", "MUSLERUNOFF", "MUSLESEDYLD", "MUSLESOC", "MUSLESON", "MUSLENH4", "MUSLENO3", "Sumrunoff", "Sumno3", "SumN"};
	CString SSYY[3]={"ave", "max", "min"};
	CString IIIR[2]={ "ZeroIrri", "FullIrri"};
	CString RDR;
	FILE* rdr;
	char str[50];
	float MonthResult;
	for(int mi=0; mi<11; mi++)
	{
		for(int si=0; si<2; si++)
		{
		for(int Li=0; Li<2;Li++)
		{
			for(int Yy=1; Yy<=S_SimuYears; Yy++)
			{
				RDR.Format("%s\\Record\\Region\\%s\\%s\\Month%s_%s_Yr%d_%s_%s.txt", OUTPUT,
							CountryName, ScenarioName, MI[mi], r_Province, Yy, SSYY[si],IIIR[Li]);
				if(ii_ha==1)
				{
					rdr=fopen(RDR, "w");
					if(rdr==NULL)
					{
						CString note;
						note.Format("Cannot create %s", RDR);
						AfxMessageBox(note);
						exit(0);
					}
					fprintf(rdr,"Month %s result. Unit: 1000 kg C/day; 1 kg N/day; 1 cubic m water/day for a grid cell\n", MI[mi]);

					for(int j=0;j<12;j++)
					{
						if(j==0) fprintf(rdr," %10s ", "County_ID");
						sprintf(str,"%8d",j+1);
						fprintf(rdr," %s",str);
					}
					fprintf(rdr,"\n");
				}
				else
				{
					rdr=fopen(RDR, "a");
					if(rdr==NULL)
					{
						CString note;
						note.Format("Cannot create %s", RDR);
						AfxMessageBox(note);
						exit(0);
					}
				}

				for(int j=1; j<=12; j++)
				{
					if(j==1) fprintf(rdr," %d ", cell_ID1);
					MonthResult = 0.0;
					for(int lu=1; lu<=crop_number; lu++)
					{
						if(mi==0) MonthResult += MMleach[j][Yy][lu][si][Li];
						else if(mi==1) MonthResult += MMleachN[j][Yy][lu][si][Li];
						else if(mi==2) MonthResult += MMmuslerunoff[j][Yy][lu][si][Li];
						else if(mi==3) MonthResult += MMmuslesedyld[j][Yy][lu][si][Li];
						else if(mi==4) MonthResult += MMmuslesoc[j][Yy][lu][si][Li];
						else if(mi==5) MonthResult += MMmusleson[j][Yy][lu][si][Li];
						else if(mi==6) MonthResult += MMmuslenh4[j][Yy][lu][si][Li];
						else if(mi==7) MonthResult += MMmusleno3[j][Yy][lu][si][Li];
						else if(mi==8) MonthResult += MMsumrunoff[j][Yy][lu][si][Li];
						else if(mi==9) MonthResult += MMsumno3[j][Yy][lu][si][Li];
						else if(mi==10) MonthResult += MMsumn[j][Yy][lu][si][Li];
						else {}
					}
					fprintf(rdr,"%8.2f ", MonthResult);
					
				
				}
				fprintf(rdr,"\n");
				fclose(rdr);
			}
		}//Li loop
		}//si loop

	}//mi loop

}
#endif

#ifdef DROUGHT
	static float DDcrop[366][10][30][3][2]={0.0,0.0};
	static float DDWtotal[366][10][30][3][2]={0.0,0.0};
	static float DDWstress[366][10][30][3][2]={0.0,0.0};
	static float DDW1[366][10][30][3][2]={0.0,0.0};
	static float DDW2[366][10][30][3][2]={0.0,0.0};
	static float DDW3[366][10][30][3][2]={0.0,0.0};
	static float DDW4[366][10][30][3][2]={0.0,0.0};
	static float DDW5[366][10][30][3][2]={0.0,0.0};
	static float DDtrans[366][10][30][3][2]={0.0,0.0};
	
#else
	static float DDbiomass[366][10][30][3][2]={0.0,0.0};
	static float DDdSOC[366][10][30][3][2]={0.0,0.0};
	static float DDco2[366][10][30][3][2]={0.0,0.0};
	static float DDn2o[366][10][30][3][2]={0.0,0.0};
	static float DDno[366][10][30][3][2]={0.0,0.0};
	static float DDnh3[366][10][30][3][2]={0.0,0.0};
	//static float DDLeachN[366][10][30][3][2]={0.0,0.0};
	static float DDch4[366][10][30][3][2]={0.0,0.0};
	static float DDtrans[366][10][30][3][2]={0.0,0.0};
	
#endif



void class_model::DailyDataRead2(int year, int LandOrder, int SoilYear, float ha, int IrriType)
{
	for(int x=1; x<=365; x++)
	{
		if(ha>0.0)
		{
#ifdef DROUGHT
			DDcrop[x][year][LandOrder][SoilYear][IrriType]=RDbiomas[x];
			DDWtotal[x][year][LandOrder][SoilYear][IrriType]=RDtotalwater[x];
			DDWstress[x][year][LandOrder][SoilYear][IrriType]=RDwaterstress[x];
			DDW1[x][year][LandOrder][SoilYear][IrriType]=RDwater1[x];
			DDW2[x][year][LandOrder][SoilYear][IrriType]=RDwater2[x];
			DDW3[x][year][LandOrder][SoilYear][IrriType]=RDwater3[x];
			DDW4[x][year][LandOrder][SoilYear][IrriType]=RDwater4[x];
			DDW5[x][year][LandOrder][SoilYear][IrriType]=RDwater5[x];
			DDtrans[x][year][LandOrder][SoilYear][IrriType]=RDtrans[x];
			DDevap[x][year][LandOrder][SoilYear][IrriType]=RDevap[x];
			DDleach[x][year][LandOrder][SoilYear][IrriType]=RDleach[x];
			DDirri[x][year][LandOrder][SoilYear][IrriType]=RDirri[x];
#else
			DDco2[x][year][LandOrder][SoilYear][IrriType] = RDco2[x]*ha; //kg C
			DDn2o[x][year][LandOrder][SoilYear][IrriType] = RDn2o[x]*ha; //kg N
			DDno[x][year][LandOrder][SoilYear][IrriType] = RDno[x]*ha;
			DDnh3[x][year][LandOrder][SoilYear][IrriType] = RDnh3[x]*ha;
			DDLeachN[x][year][LandOrder][SoilYear][IrriType] = RDLeachN[x]*ha;		
			DDdSOC[x][year][LandOrder][SoilYear][IrriType] = RDdSOC[x]*ha;
			DDch4[x][year][LandOrder][SoilYear][IrriType] = RDch4[x]*ha;
			DDbiomass[x][year][LandOrder][SoilYear][IrriType] = RDbiomas[x]*ha;
			DDtrans[x][year][LandOrder][SoilYear][IrriType] = RDtrans[x]*ha *10.0;//m3 water
			DDevap[x][year][LandOrder][SoilYear][IrriType] = RDevap[x]*ha *10.0;//m3 water
			DDleach[x][year][LandOrder][SoilYear][IrriType] = RDleach[x]*ha *10.0;//m3 water
			DDirri[x][year][LandOrder][SoilYear][IrriType] = RDirri[x]*ha *10.0;//m3 water
#endif

#ifdef HYDRO//===dengjia
		    DDmuslerunoff[x][year][LandOrder][SoilYear][IrriType] = RDmuslerunoff[x]*ha*10;
			DDmuslesedyld[x][year][LandOrder][SoilYear][IrriType] = RDmuslesedyld[x];
			DDmuslesoc[x][year][LandOrder][SoilYear][IrriType] = RDmuslesoc[x]*ha;
		    DDmusleson[x][year][LandOrder][SoilYear][IrriType] = RDmusleson[x]*ha;
			DDmuslenh4[x][year][LandOrder][SoilYear][IrriType] = RDmuslenh4[x]*ha;
			DDmusleno3[x][year][LandOrder][SoilYear][IrriType] = RDmusleno3[x]*ha;
            DDmuslenh3[x][year][LandOrder][SoilYear][IrriType] = RDmuslenh3[x]*ha;
			DDmusleurea[x][year][LandOrder][SoilYear][IrriType] = RDmusleurea[x]*ha;
			DDmusleclayn[x][year][LandOrder][SoilYear][IrriType] = RDmusleclayn[x]*ha;

            float x1,x2,x3,x4;
			x1=DDmusleson[x][year][LandOrder][SoilYear][IrriType];
			x2=DDmuslenh4[x][year][LandOrder][SoilYear][IrriType];
			x3=DDmusleno3[x][year][LandOrder][SoilYear][IrriType];
			x4=DDmuslenh3[x][year][LandOrder][SoilYear][IrriType];

            DDsumrunoff[x][year][LandOrder][SoilYear][IrriType] = DDmuslerunoff[x][year][LandOrder][SoilYear][IrriType]+DDleach[x][year][LandOrder][SoilYear][IrriType];
			DDsumno3[x][year][LandOrder][SoilYear][IrriType] = x3+DDLeachN[x][year][LandOrder][SoilYear][IrriType];
			DDsumn[x][year][LandOrder][SoilYear][IrriType] =x1+x2+x3+x4+DDLeachN[x][year][LandOrder][SoilYear][IrriType];
#endif				
		}
		else
		{
#ifdef DROUGHT
			DDcrop[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDWtotal[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDWstress[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDW1[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDW2[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDW3[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDW4[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDW5[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDtrans[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDevap[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDleach[x][year][LandOrder][SoilYear][IrriType]=0.0;
			DDirri[x][year][LandOrder][SoilYear][IrriType]=0.0;
#else
			DDco2[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDn2o[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDno[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDnh3[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDLeachN[x][year][LandOrder][SoilYear][IrriType] = 0.0;

			DDdSOC[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDch4[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDbiomass[x][year][LandOrder][SoilYear][IrriType] = 0.0;

			DDtrans[x][year][LandOrder][SoilYear][IrriType] = 0.0;//m3 water
			DDevap[x][year][LandOrder][SoilYear][IrriType] = 0.0;//m3 water
			DDleach[x][year][LandOrder][SoilYear][IrriType] = 0.0;//m3 water
			DDirri[x][year][LandOrder][SoilYear][IrriType] = 0.0;//m3 water
#endif

#ifdef HYDRO
		    DDmuslerunoff[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDmuslesedyld[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDmuslesoc[x][year][LandOrder][SoilYear][IrriType] = 0.0;
		    DDmusleson[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDmuslenh4[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDmusleno3[x][year][LandOrder][SoilYear][IrriType] = 0.0;
            DDmuslenh3[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDmusleurea[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDmusleclayn[x][year][LandOrder][SoilYear][IrriType] = 0.0;


            DDsumrunoff[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDsumno3[x][year][LandOrder][SoilYear][IrriType] = 0.0;
			DDsumn[x][year][LandOrder][SoilYear][IrriType] =0.0;
#endif
		}		
	}
}

void class_model::Daily_record2(int S_SimuYears, int ii_ha, char* CountryName, char* ScenarioName, int cell_ID1, int crop_number, char* r_Province, int IrriType, int SoilDataUse)
{
#ifdef DROUGHT
	CString uunit[12]={"kg C/ha", "kg C/ha", "Index (0-1)", "mm", "WFPS", "WFPS", "WFPS", "WFPS", "WFPS", "mm", "mm", "mm"};
	CString DI[12]={"CropShoot", "CropGrain", "WaterStress", "SoilWater", "WFPS10cm", "WFPS20cm", "WFPS30cm", "WFPS40cm", "WFPS50cm", "Transpiration", "Evaporation", "InputWater"};
#else
	CString uunit[12]={"kgC/ha", "kgN/ha", "kgN/ha", "kgN/ha", "kgC/ha", "kgC/ha", "kgC/ha", "mm", "mm", "mm", "mm", "mm"};

	CString DI[12]={"CO2", "N2O", "NO", "NH3", "dSOC", "CH4", "Biomass", "Transpiration", "Evaporation", "LeachWater", "IrriWater", "LeachN"};
#endif
	
	CString SSYY[3]={"ave", "max", "min"};
	CString IIIR[2]={"ZeroIrri", "FullIrri"};
	CString RDR;
	FILE* rdr;
	char str[50];
	float DailyFlux;

	//SoilDataUse//0: FullIrr/NoIrri + SoilMax/min; 1: FullIrr/NoIrri + Soil ave; 2: NoIrri + Soil max/min; 3: NoIrri + Soil ave

	int IrriAA1=0, IrriAA2=1;
	int SoilAA1=0, SoilAA2=1;

	if(SoilDataUse==0) 
	{
		IrriAA1=0;
		IrriAA2=1;
		SoilAA1=1;
		SoilAA2=2;
	}
	else if(SoilDataUse==1) 
	{
		IrriAA1=0;
		IrriAA2=1;
		SoilAA1=0;
		SoilAA2=0;
	}
	else if(SoilDataUse==2) 
	{
		IrriAA1=0;
		IrriAA2=0;
		SoilAA1=1;
		SoilAA2=2;
	}
	else if(SoilDataUse==3) 
	{
		IrriAA1=0;
		IrriAA2=0;
		SoilAA1=0;
		SoilAA2=0;
	}
	else
	{
		AfxMessageBox("Wrong irrigation-soil type combination");
		exit;
	}	

	for(int di=0; di<12; di++)
	{
		for(int si=SoilAA1; si<=SoilAA2; si++)
		{
		for(int Li=IrriAA1; Li<=IrriAA2; Li++)
		{
			for(int Yy=1; Yy<=S_SimuYears; Yy++)
			{
				RDR.Format("%s\\Record\\Region\\%s\\%s\\Daily%s_%s_Yr%d_%s_%s.txt",  OUTPUT,
							CountryName, ScenarioName, DI[di], r_Province, Yy, SSYY[si], IIIR[Li]);

				if(ii_ha==1)
				{
					rdr=fopen(RDR, "w");
					if(rdr==NULL)
					{
						CString note;
						note.Format("Cannot create %s", RDR);
						AfxMessageBox(note);
						exit(0);
					}
					fprintf(rdr,"Daily %s flux. Unit: %s\n", DI[di], uunit[di]);

					for(int j=1;j<=365;j++)
					{
						if(j==0) fprintf(rdr," %10s ", "County_ID");
						sprintf(str,"%8d",j);
						fprintf(rdr," %s",str);
					}
					fprintf(rdr,"\n");
				}
				else
				{
					rdr=fopen(RDR, "a");
					if(rdr==NULL)
					{
						CString note;
						note.Format("Cannot create %s", RDR);
						AfxMessageBox(note);
						exit(0);
					}
				}

				for(int j=1; j<=365; j++)
				{
					if(j==1) fprintf(rdr," %d ", cell_ID1);
					DailyFlux = 0.0;
					//for(int lu=1; lu<=crop_number; lu++)
					for(int lu=1; lu<=1; lu++)
					{
#ifdef DROUGHT
						if(di==0) DailyFlux += DDcrop[j][Yy][lu][si][Li];
						else if(di==1) DailyFlux += DDleach[j][Yy][lu][si][Li];
						else if(di==2) DailyFlux += DDWstress[j][Yy][lu][si][Li];
						else if(di==3) DailyFlux += DDWtotal[j][Yy][lu][si][Li];
						else if(di==4) DailyFlux += DDW1[j][Yy][lu][si][Li];
						else if(di==5) DailyFlux += DDW2[j][Yy][lu][si][Li];
						else if(di==6) DailyFlux += DDW3[j][Yy][lu][si][Li];
						else if(di==7) DailyFlux += DDW4[j][Yy][lu][si][Li];
						else if(di==8) DailyFlux += DDW5[j][Yy][lu][si][Li];
						else if(di==9) DailyFlux += DDtrans[j][Yy][lu][si][Li];
						else if(di==10) DailyFlux += DDevap[j][Yy][lu][si][Li];
						else if(di==11) DailyFlux += DDirri[j][Yy][lu][si][Li];
						else {}
#else
						if(di==0) DailyFlux += DDco2[j][Yy][lu][si][Li];
						else if(di==1) DailyFlux += DDn2o[j][Yy][lu][si][Li];
						else if(di==2) DailyFlux += DDno[j][Yy][lu][si][Li];
						else if(di==3) DailyFlux += DDnh3[j][Yy][lu][si][Li];
						else if(di==4) DailyFlux += DDdSOC[j][Yy][lu][si][Li];
						else if(di==5) DailyFlux += DDch4[j][Yy][lu][si][Li];
						else if(di==6) DailyFlux += DDbiomass[j][Yy][lu][si][Li];
						else if(di==7) DailyFlux += DDtrans[j][Yy][lu][si][Li];
						else if(di==8) DailyFlux += DDevap[j][Yy][lu][si][Li];
						else if(di==9) DailyFlux += DDleach[j][Yy][lu][si][Li];
						else if(di==10) DailyFlux += DDirri[j][Yy][lu][si][Li];
						else if(di==11) DailyFlux += DDLeachN[j][Yy][lu][si][Li];
						else {}
#endif
					}
					fprintf(rdr,"%8.2f ", DailyFlux);
					
					
				}
				fprintf(rdr,"\n");
				fclose(rdr);
			}
		}//Li loop
		}//si loop
	}//di loop

#ifdef HYDRO//===dengjia===
    CString DMUSLE[12]={"MUSLERUNOFF", "MUSLESEDYLD", "MUSLESOC", "MUSLESON", "MUSLENH4", "MUSLENO3", "MUSLENH3", "MUSLEUREA", "MUSLECLAYN","Sumrunoff","Sumno3","Sumn"};
    CString DMR;
	FILE *dmr;
	char musle[50];
	float DailyMusle;
	for(di=0; di<12; di++)
	{
		for(int si=0; si<2; si++)
		{
        for(int Li=0; Li<2; Li++)
		{
			for(int Yy=1; Yy<=S_SimuYears; Yy++)
			{
				DMR.Format("%s\\Record\\Region\\%s\\%s\\Daily%s_%s_Yr%d_%s_%s.txt",  OUTPUT,
							CountryName, ScenarioName, DMUSLE[di], r_Province, Yy, SSYY[si], IIIR[Li]);
				if(ii_ha==1)
				{
					dmr=fopen(DMR, "w");
					if(dmr==NULL)
					{
						CString note;
						note.Format("Cannot create %s", DMR);
						AfxMessageBox(note);
						exit(0);
					}
					fprintf(dmr,"Daily %s . Unit: 1 kg C/day; 1 kg N/day; 1 cubic m water/day ;1 ton soil/day  for a grid cell\n", DMUSLE[di]);

					for(int j=0;j<365;j++)
					{
						if(j==0) fprintf(dmr," %10s ", "County_ID");
						sprintf(musle,"%8d",j+1);
						fprintf(dmr," %s",musle);
					}
					fprintf(dmr,"\n");
				}
				else
				{
					dmr=fopen(DMR, "a");
					if(dmr==NULL)
					{
						CString note;
						note.Format("Cannot create %s", DMR);
						AfxMessageBox(note);
						exit(0);
					}
				}

				for(int j=1; j<=365; j++)
				{
					if(j==1) fprintf(dmr," %d ", cell_ID1);
					DailyMusle = 0.0;
					for(int lu=1; lu<=crop_number; lu++)
					{

						if(di==0) DailyMusle += DDmuslerunoff[j][Yy][lu][si][Li];
						else if(di==1) DailyMusle += DDmuslesedyld[j][Yy][lu][si][Li];
						else if(di==2) DailyMusle += DDmuslesoc[j][Yy][lu][si][Li];
						else if(di==3) DailyMusle += DDmusleson[j][Yy][lu][si][Li];
						else if(di==4) DailyMusle += DDmuslenh4[j][Yy][lu][si][Li];
						else if(di==5) DailyMusle += DDmusleno3[j][Yy][lu][si][Li];
						else if(di==6) DailyMusle += DDmuslenh3[j][Yy][lu][si][Li];
						else if(di==7) DailyMusle += DDmusleurea[j][Yy][lu][si][Li];
						else if(di==8) DailyMusle += DDmusleclayn[j][Yy][lu][si][Li];

						else if(di==9) DailyMusle += DDsumrunoff[j][Yy][lu][si][Li];
						else if(di==10) DailyMusle+=DDsumno3[j][Yy][lu][si][Li];
						else if(di==11) DailyMusle+=DDsumn[j][Yy][lu][si][Li];
						else {}
					}
					fprintf(dmr,"%8.2f ", DailyMusle);
					
				}
				fprintf(dmr,"\n");
				fclose(dmr);
			}
		}//Li loop
		}//si loop

	}//di loop
#endif
}
*/