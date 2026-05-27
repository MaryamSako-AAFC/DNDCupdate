#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include <math.h>

void class_model::soil_oxygen_profile(int l, int T, int rain_hrs, float bypass_f,
						 float air_poro_max, int flood_day, float *temp, int year, int jday, int q, 
						 double water[25][250], float *day_wfps, float *h, float *sts, float *O2,
						 float day_WT, int WTL, float total_ice, float TTT, float *day_rco2, float *co2,
						 int flo_num, float *ice)
{
	float dO2=0.0;

	float base_O2 = 0.0003125;//mol/L

	if(flood_flag==1)
	{
		O2[l] = 0.0;
	}
	else
	{

		
		if(rain_hrs==0)// no rain
		{
			O2[l] = base_O2; //mol/L
		}
		else
		{
			if(T<=rain_hrs) 
			{
				//dO2 = 0.0005 * soc[l] / (5000.0 + soc[l]);//if irrigation ????
				//O2[l] -= dO2;
				//if(O2[l]<0.0)	O2[l] = 0.0;
				
				//float ps = sts[l];//h[l] * sts[l];
				//float actual_poro = ps * (1.0 - day_wfps[l]) + 0.0000001;//10000.0 * (1.0 - water[T][l] / ps) + 0.000001;//m3/layer/ha, actual pores
				//float air_O2 = 0.299251;
				//float full_O2 = air_O2 * ps ;//g O2/layer/ha
				//O2[l] = air_O2 * actual_poro ;//g O2/layer/ha

				//per layer test
				//O2[l] = (((1 - day_wfps[l]) * sts[l] * 0.21) / (0.0821 * 273.3 + temp[l]));//mol/L

				O2[l] = 0.0;
			}
			else 
			{
				O2[l] = base_O2;
			}
		}

		Eh[l] = (0.816 - 0.01475 * (float)log(1.0/(O2[l]+1.0E-50)) / 2.3026) * 1000.0;// mV
		

		/*
		//----testing using actual water status to calculate Eh
		float ps = 0.5;//h[l] * sts[l];
		float actual_poro = ps * (1.0 - day_wfps[l]) + 0.0000001;//10000.0 * (1.0 - water[T][l] / ps) + 0.000001;//m3/layer/ha, actual pores
		float air_O2 = 0.299251;
		float full_O2 = air_O2 * ps * 10000.0;//g O2/layer/ha
		O2[l] = air_O2 * actual_poro * 10000.0;//g O2/layer/ha
		Eh[l] = 626.1 * O2[l] / full_O2; //Redox potential . Likely in the wrong range for denitrification due to considerations with tippping bucket mechanisms and difficulties in capturing hourly soil moisture above field capacity. 
		*/
	}	

	if(T<=10) 
	{
		O2_old[l] += O2[l]/10.0;
		Eh_old[l] += Eh[l]/10.0;
	}
}

void class_model::saturation_Eh(void) //Eh dynamics under flooding
{
	float F_SOC = 0.05;
	float EhSOC=100;
	float fO2, fNO3, dNO3, dMn, dFe, dSO4;

	for(int l=1; l<=q; l++)
	{
		float mol_NO3=0.0;
		float Fdoc = powf(MicrobioIndex, 2.0) * soc[l] / mmm[l];
		float FDOC = Fdoc / (0.1 + Fdoc);

		O2[l] = 0.0;
		
		if(no3[l]>0.0)// kg N/ha/layer
		{
			fNO3 = 0.1 * FDOC * (no3[l] / (0.000001 + no3[l]));//0.5
			fNO3 = min(no3[l], max(0.0, fNO3));
			no3[l] -= fNO3;
			n2[l] += fNO3;
			mol_NO3 = no3[l] * 1000.0 / 62.0 / vvv[l] / 1000.0; //mol NO3/L

			//mol_NO3 = 0.00357;
			Eh[l] = (0.389 - 0.0197 * (float)log(0.000001/(mol_NO3+10E-50))/2.3026) * 1000.0; //mV

			if(Eh[l]<180.0)
			{
				Eh[l] = 180.0;
				n2[l] += no3[l];
				no3[l] = 0.0;
			}
			
		}
		else
		{
			if(Fe3[l]>0.0)// mol/L, 1.073
			{
				dFe = 0.001 * FDOC * (Fe3[l] / (0.15 + Fe3[l]));//0.1 
				Fe3[l] -= dFe;
				Fe3[l] = max(0.0, Fe3[l]);
				Fe2[l] += dFe;
				
				Eh[l] = (0.771 - 0.059 * (float)log(Fe2[l]/(Fe3[l]*0.01+1.0E-50)) / 2.3026 - 0.059*3.0/1.0 * sph[l]) * 1000.0; //mV;
			
				if(Eh[l]<-120.0)
				{
					Eh[l] = -120.0;
					Fe2[l] += Fe3[l];
					Fe3[l] = 0.0;
				}

			}
			else
			{

				//SO4[l] = 100.0;
				if(SO4[l]>0.0)// mol/L, 0.1166
				{
					dSO4 = 0.1 * FDOC * (SO4[l] / (0.15 + SO4[l])); 
					SO4[l] -= dSO4;
					SO4[l] = max(0.0, SO4[l]);
					H2S[l] += dSO4;
					Eh[l] = (0.248 - 0.059/8.0 * (float)log(0.00000001/(SO4[l]+1.0E-50)) / 2.3026 - 0.059*8.0/8.0 * sph[l]) * 1000.0; //mV;
				
					if(Eh[l]<-150.0)
					{
						Eh[l] = -150.0;
						H2S[l] += SO4[l];
						SO4[l] = 0.0;
					}
				}
				else
				{
					Eh[l] = -150.0;
				}
			}
		}
	}
}

void class_model::Mn_Fe_S_oxidation()
{
	for(int l=1; l<=q; l++)
	{
		if(Eh[l] > 100.0)
		{
			if(Mn2[l] > 0.0) 
			{
				float dMn2 = 0.2*Mn2[l];
				Mn4[l] += dMn2;
				Mn2[l] -= dMn2;
			}
			if(Fe2[l] > 0.0) 
			{
				float dFe2 = 0.2*Fe2[l];
				Fe3[l] += dFe2;
				Fe2[l] -= dFe2;
			}
			
			if(H2S[l] > 0.0) 
			{
				float dH2S = 0.2*H2S[l];
				SO4[l] += dH2S;
				H2S[l] -= dH2S;
			}
		}
	}
}

