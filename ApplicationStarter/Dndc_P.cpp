#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"

#ifdef MANURE 
extern class_manure MData;
#endif

void class_model::P_adsorption(int q, float *LabP, float *AdsP, float *h, float *day_wfps, float *sts, float *mmm)
{
	//Langmuir Equation
	float PinW=0.0;//P concentration in soil pore water, mg P/L
	float PinS=0.0;//amount of P in adsorbed phase, mg P/kg soil
	
	float adsPmax=700.0;//P adsorption maximum, mg P/kg soil
	float adsPK=0.1f;//Constant related to bonding energy, L/mg P
	float adsPo=0.0;//quantity of P retained under ambiant conditions, mg P/kg soil

	for(int l=1; l<=q; l++)
	{
		float TP = LabP[l] + AdsP[l];//kg P/layer

		if(LabP[l]<=0.0&&AdsP[l]>0.0) 
		{
			LabP[l] = AdsP[l] * 0.001;
			AdsP[l] *= 0.999;
		}

		float VVw = h[l] * 10000.0 * sts[l] * day_wfps[l] * 1000.0; //water L/ha in layer l
		PinW = (LabP[l] * 1000000.0) / VVw;//mg P/L in liquid		

		//Langmuir equation
		PinS = adsPmax * (adsPK * PinW) / (1.0 + adsPK * PinW) - adsPo;//mg P/kg soil, 2->100; 50-600 mg P/kg soil

		float dLabP = (PinW / 1000000.0) * VVw;//kg P/layer soil pore water;
		float dAdsP = PinS / 1000000.0 * mmm[l];//kg P/layer soil
		float TTP = dLabP + dAdsP;

		if(TTP<=0.0)
		{
			AdsP[l] = 0.0;
			LabP[l] = 0.0;
		}
		else
		{
			AdsP[l] = TP * (dAdsP / TTP);
			LabP[l] = TP - AdsP[l];
		}

	}
		
	
/*
	//Freundlich equation
	float Kf = 0.0; //Freundlich adsorption coefficient (L/kg soil)
	float N = 0.4; //Empirical constatnt, <1.0
	float So = 0.0; //Amount of P present in sorbed phase at soil pore water P concentration approaching negligible levels (mg P/kg soil) 

	PinS = Kf * powf(Pinw, N) - So;

*/

	

}