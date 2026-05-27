#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"


float NPratio[7]={0.0,0.347,0.347, 0.513, 0.3, 0.34,0.58}; //1 dairy, 2 beef, 3 swine, 4 sheep, 5 horse, 6 poultry

void class_model::irrigating(int MODE, float DayPET)
{
	/*if ( rainfall <= .0001 )
    	TTT = 0.0;
    else
    	TTT = rainfall / 0.005;//m/m, hrs*/

    int   csl;
	//IrriWater = 0.0;
	   
	if(fer_num==-1)//fertigation
	{	
		if(day_irri>0.0)
		{
			IrriWater = day_irri;
			yr_irri += day_irri; // m water 
			//IrriMethod = 2;
			fertigate_flag = 1;
		}
		else
		{
			//IrriMethod = 0;
			fertigate_flag = 0;
		}		
	}
	else
	{	
		if (irr_num > 0)//irrigation
		{
		  for ( csl = 1; csl <= irr_num;  csl++ )
		  {
			if ( jdirr[csl] == jday)
			{

				irri_flag=1;//++;

				IrriMethod = irrimethod[csl]; //0: furrow, 1: sprinkler, 2: drip-0cm, 3: drip-15cm

				IrriWater = irria[csl];
							
				if(IrriMethod==4)
				{
					TileIrriDays=tileIrriDays[csl];
					TileIrriAmount=irria[csl];//set TileIrriAmount
					TileIrriRate=TileIrriAmount/TileIrriDays;
					yr_irri += irria[csl]; // m water
				}
				else
				{

				//rainfall += irria[csl];
				yr_irri += irria[csl]; // m water 
				day_irri += irria[csl];	
				}
				//if(IrriMethod==0) TTT += (irria[csl] / 0.005);//???????
			}
/*
			else if (jdirr[csl] == jday  )//&& TileIrri==1
			{
			TileIrriAmount=irria[csl];//set TileIrriAmount
			TileIrriRate=TileIrriAmount/TileIrriDays;
			yr_irri += irria[csl]; // m water 
			
			//brian


			}
*/
			}
		}
		else
		{
			IrriMethod = irrimethod[0];
		}
	}
		
    //return( TTT );
}

void class_model::fertilizing()
{
    int   ox, l, i, FertType=0; 
 	

/*
	if (jday==1)
			{
			CString TESTFILE;
			FILE *pFile=NULL;
			TESTFILE.Format("%s\\Record\\farmAgentModel.txt", OUTPUT);
			pFile = fopen (TESTFILE,"r");
			fscanf(pFile, "%d",&farmAgentModel);
			fclose (pFile);
			}
*/
	if (year == 1 && jday == 1)//ensure NStress-%d is being written with zeros from legacy runs.
	{
		write_out_NStress();
	}
	if(jday==1&&year>=2&&FertOption==222||jday==1&&year>=2&&FertOption==0||jday==1&&year>=2&&autoManure==1)//farmAgentModel==1//&&FertOption==222
	{
		read_in_NStress();
	}
	
	if(jday==365&&FertOption==222||jday==365&&FertOption==0|| jday == 365  && autoManure == 1)//farmAgentModel==1 //&&FertOption==222
	{
		
		farmAgent(yearlyNStress,yearlyNUptake,cropRotType);
	}
	





	if(fert_flag==1) fert_flag=0;

	/*
	if(FertOption==222)//auto-fertilization
	{
		float ATF[7]={0.0, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
		float ProfileNN = 0.0;
		for(int i=1; i<=q; i++) ProfileNN += (nh4[i]+no3[i]);

		if(crop[1]==2&&jday==1)
		{
			FertAddN[1] = (maxmn[1] / ini_N_fix[1] - ProfileNN) * ATF[3];
			if(FertAddN[1]<0.0) FertAddN[1] = 0.0;
			day_inFertN += FertAddN[1];
			yr_addfer += FertAddN[1];
			if(FertAddN[1]>0.0)
			{
				fert_flag = 1;
				for (l=1; l<=2; l++) urea[l] += (FertAddN[1] / 2.0);
			}
		}

		for(int iw1=1; iw1<=5; iw1++)
		{
			if(seed[iw1]==1) 
			{
				FertAddN[iw1] = (maxmn[iw1] / ini_N_fix[iw1] - ProfileNN) * ATF[3];
				if(FertAddN[iw1]<0.0) FertAddN[iw1] = 0.0;
				day_inFertN += FertAddN[iw1];
				yr_addfer += FertAddN[iw1];
				if(FertAddN[iw1]>0.0)
				{
					fert_flag = 1;
					for (l=1; l<=2; l++) urea[l] += (FertAddN[iw1] / 2.0);
				}
			}
		}
	}
	*/
if(FertOption==222)//auto-fertilization
	{ 
		

	int i, fallFertFlag;
	fallFertFlag = 0;
	float nextYearMaxN=0.01;
	float nextYearFixN = 0.0;
	
	if (jday == 1)//first day of the year....determine the cropRotType
	{

	}


		
		float ATF[7]={0.0, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
		float ProfileNN = 0.0,ResidualNN=0.0;
		int  tempFertCrop;
		if (SlowReleaseDays > 1)
		{
			SlowReleaseDays -= 1;
		}


		for (i = 1; i <= 2; i++)//multiple fert applications
		{
			if (jday == jdfer[i])
			{


				//need to figure out proper index for cropT based on jdfer[i] and the next jdseed to decide which AverageNStress[cropT] to reference
				
			
				if (i == 1)
				{
					upFertCrop = 1;
					tempFertCrop = 366;
					for (int z = 0; z <= 7; z++)
					{
						if (jday <= jdseed[z])
						{
							//tempFertCrop = jdseed[z];

							if (jdseed[z] < tempFertCrop)
							{
								tempFertCrop = jdseed[z];
								upFertCrop = z;
							}

						}

					}
				}
				


				
				for (int z = 0; z <= 9; z++)
				{
					if (cropRotType[z] == crop[upFertCrop] || cropRotType[z] == 0)
					{
						//cropRotType[z] = crop[1];//adds the crop to cropRotType or overwrites.
						cropT = z; //this might need to be adjusted since it points to crop[1] for multiple crops
						break;
					}
				}
				


				int root_q1;
				root_q1 = (int)(max_root_length [1] / h[1]);

				for (int iz = 1; iz <= root_q1; iz++)
				{
					ProfileNN += (nh4[iz] + no3[iz]);//calculating the soil profile N .. should only cacluate based on root depth. 
					//ResidualNN+= (rcvl[i]/rcnrvl + rcl[i]/rcnrl + rcr[i]/rcnrr);
				}




				UreaHydroInhibEf = UreaseEfficiency[i];
				UreaHydroInhibDu = UreaseDuration[i];
				UIDay1 = jday;
				UIDay2 = UIDay1 + (int)UreaseDuration[i];
				if (UreaHydroInhibDu > 0.0) UreaHydroInhibDays = 1;
				else UreaHydroInhibDays = 0;

				FertDepth = fer_dept[i];
				fer_layer = (int)(fer_dept[i] / h[1] + 1);//????
				if (fer_layer < 1) fer_layer = 1;

				NIEfficiency = NIefficiency[i];
				NIDuration0 = NIduration[i];
				NIDuration1 = NIduration[i];

				NIDay1 = jday;
				NIDay2 = NIDay1 + (int)NIduration[i];


				//day_inFertN = (fer1[ox] + fer2[ox] + fer3[ox] + fer4[ox] + fer5[ox] + fer6[ox] + fer7[ox]);
				//yr_addfer += day_inFertN;

/*				float FFy = 0.0222 * (float)log(FertDayRelease[ox]) + 0.876£»
				float RemainFert1 = fer1[ox] * powf(FFy, FertDays));
*/
				AppliedUrea = fer3[i];

				if (fer3[i] > 0.0) UreaAppDays = 1;

				//slow release fertilizer
				if (FertDayRelease[i] > 1.0)
				{
					SlowReleaseDays = FertDayRelease[i];
					float checkIfFert = 0.0;
					checkIfFert = fer1[i] + fer2[i] + fer3[i] + fer4[i] + fer5[i] + fer6[i] + fer7[i];
					if (checkIfFert > 0)
					{
						slowReleaseCounter = SlowReleaseDays+jday;
					}
					else
					{
						slowReleaseCounter = 1;
					}
					if (SlowReleaseDays == 1)
					{
						DayFixFert1 += fer1[i];
						DayFixFert2 += fer2[i];
						DayFixFert3 += fer3[i];
						DayFixFert4 += fer4[i];
						DayFixFert5 += fer5[i];
						DayFixFert6 += fer6[i];
						DayFixFert7 += fer7[i];

						IniFixFert1 = fer1[i];
						IniFixFert2 = fer2[i];
						IniFixFert3 = fer3[i];
						IniFixFert4 = fer4[i];
						IniFixFert5 = fer5[i];
						IniFixFert6 = fer6[i];
						IniFixFert7 = fer7[i];
					}
					/*
					DayFertRelease[1] = fer1[i] / SlowReleaseDays;
					DayFertRelease[2] = fer2[i] / SlowReleaseDays;
					DayFertRelease[3] = fer3[i] / SlowReleaseDays;
					DayFertRelease[4] = fer4[i] / SlowReleaseDays;
					DayFertRelease[5] = fer5[i] / SlowReleaseDays;
					DayFertRelease[6] = fer6[i] / SlowReleaseDays;
					DayFertRelease[7] = fer7[i] / SlowReleaseDays;
					*/
					/*DayFert1[jday] += fer1[i];
					DayFert2[jday] += fer2[i];
					DayFert3[jday] += fer3[i];
					DayFert4[jday] += fer4[i];
					DayFert5[jday] += fer5[i];
					DayFert6[jday] += fer6[i];
					DayFert7[jday] += fer7[i];*/
				}
				else
				{
					DayFert1[jday] += fer1[i];
					DayFert2[jday] += fer2[i];
					DayFert3[jday] += fer3[i];//urea
					DayFert4[jday] += fer4[i];
					DayFert5[jday] += fer5[i];//ammonium
					DayFert6[jday] += fer6[i];
					DayFert7[jday] += fer7[i];

					fer1[i] = 0.0;
					fer2[i] = 0.0;
					fer3[i] = 0.0;
					fer4[i] = 0.0;
					fer5[i] = 0.0;
					fer6[i] = 0.0;
					fer7[i] = 0.0;
				}
















				//used for WinterWheat
				float NFertXWW;
				NFertXWW = 1.0;
				if (averageNStress[cropT] >= .98)
				{
					NFertXWW = 0.85;
				}//.4
				else if (averageNStress[cropT] >= .95)
				{
					NFertXWW = 0.90;
				}//.7
				else if (averageNStress[cropT] >= .92)
				{
					NFertXWW = 0.95;
				}
				else if (averageNStress[cropT] >= .91)
				{
					NFertXWW = 0.99;
				}
				else
				{
					NFertXWW = 1.0;
				}
				if (averageNStress[cropT] < 0.9)
				{
					NFertXWW = 1.025;
				}
				if (averageNStress[cropT] < 0.8)
				{
					NFertXWW = 1.05;//1.3
				}
				if (averageNStress[cropT] < 0.7)
				{
					NFertXWW = 1.10;//1.6
				}


				//winter wheat


				if (crop[i] == 2 && jday == 1)
				{
					FertAddN[i] = ((maxmn[i] * 0.75) / (1 / (1.01 - ini_N_fix[i])) - (ProfileNN + ResidualNN * 0.50)) * NFertXWW;//maxmn[1]
					if (FertAddN[i] < 0.0) FertAddN[i] = 0.0;
					day_inFertN += FertAddN[i];
					yr_addfer += FertAddN[i];
					if (FertAddN[i] > 0.0)
					{
						fert_flag = 1;
						for (l = 1; l <= 2; l++) urea[l] += (FertAddN[i] / 2.0);
					}
				}

				if (jdfer[2] >= 248 || jdfer[1] >= 248) //indicating a fall fertilizer date intended for next years crop. Might want to add a fallfert flag into fertilizer tab 
				{
					//Need to read next years crop type
					
					FILE* fpp;
					char  F_CROP[200];
					int i, nextYearCrop,nextYearCropNumbers,junkD;
					float junkF;

				
					///////////////////////////////////////////////////////////////////////////////////////////////
					//Read initial crop status



					sprintf(F_CROP, "%s\\Inputs\\crop-%d", OUTPUT, year+1);
					fpp = fopen(F_CROP, "r");
					if (fpp == NULL) note(0, F_CROP);

					fscanf(fpp, "%d", &nextYearCropNumbers);
					fscanf(fpp, "%d", &nextYearCrop);
					fscanf(fpp, "%*[^\n]\n");

					//fscanf(fpp, "%d %d %f %f %f %f", &nextYearCrop,&junkD,&junkF, &junkF, &junkF, &junkF);
					fscanf(fpp, "%d %d %f %f", &junkD, &junkD, &junkF, &nextYearMaxN);
					fscanf(fpp, "%*[^\n]\n");
					fscanf(fpp, "%*[^\n]\n");
					fscanf(fpp, "%*[^\n]\n");
					fscanf(fpp, "%*[^\n]\n");
					fscanf(fpp, "%*[^\n]\n");
					fscanf(fpp, "%*[^\n]\n");
					fscanf(fpp, "%f %f %f %f", &junkF, &junkF, &junkF,&nextYearFixN);
					//fscanf(fpp, "%*[^\n]\n");
					//fscanf(fpp, "%*[^\n]\n");
					//fscanf(fpp, "%f", &junkF);
					//fscanf(fpp, "%f", &junkF);
					//fscanf(fpp, "%d", &junkD);
					//fscanf(fpp, "%d %d %f %f", &junkD, &junkD,&junkF, &nextYearMaxN);
					//fscanf(fpp, "%*[^\n]\n");
					//fscanf(fpp, "%*[^\n]\n");
					//fscanf(fpp, "%*[^\n]\n");
					//fscanf(fpp, "%*[^\n]\n");
					//fscanf(fpp, "%*[^\n]\n");
					//fscanf(fpp, "%f", &junkF);
					//fscanf(fpp, "%d", &junkD);
					//fscanf(fpp, "%d", &junkD);
					//fscanf(fpp, "%f", &junkF);
					//fscanf(fpp, "%f", &junkF);
					//fscanf(fpp, "%f %f %f %f", &junkF, &junkF, &junkF,&nextYearFixN);
					fclose(fpp);

					//figure out correct new next year crop.
					for (i = 0; i <= 9; i++)
					{
						if (cropRotType[i] == nextYearCrop || cropRotType[i] == 0)
						{
							cropT = i;
							break;
						}
					}
					fallFertFlag = 1;
				}

				//determine next closest crop to fertilizer to figure out maxmn index.

				//old way
				/*

				//for all other crops
				float NFertX;
				if (averageNStress[cropT] >= .995)
				{
					NFertX = 0.55;
				}//.4
				else if (averageNStress[cropT] >= .99)
				{
					NFertX = 0.60;
				}//.4
				else if (averageNStress[cropT] >= .985)
				{
					NFertX = 0.65;
				}
				else if (averageNStress[cropT] >= .98)
				{
					NFertX = 0.70;
				}//.4
				else if (averageNStress[cropT] >= .95)
				{
					NFertX = 0.88;
				}//.7
				else if (averageNStress[cropT] >= .92)
				{
					NFertX = 0.96;
				}
				else if (averageNStress[cropT] >= .91)
				{
					NFertX = 0.99;
				}
				else
				{
					NFertX = 1.0;
				}
				if (averageNStress[cropT] < 0.9)
				{
					NFertX = 1.05;//default 1.025
				}
				if (averageNStress[cropT] < 0.85)
				{
					NFertX = 1.15;//default 1.025  //was 1.15
				}
				if (averageNStress[cropT] < 0.8)
				{
					NFertX = 1.20;//1.3 //default 1.05 //was 1.20
				}
				if (averageNStress[cropT] < 0.7)
				{
					NFertX = 1.25;//1.6 //default 1.15//was 1.25
				}
				if (averageNStress[cropT] < 0.6)
				{
					NFertX = 1.30;//1.6 //default 1.15//was 1.25
				}
				if (averageNStress[cropT] < 0.5)
				{
					NFertX = 1.35;//1.6 //default 1.15//was 1.25
				}

				if (year == 1)//need to set for first year since no running average
				{
					averageNUptake[cropT] = maxmn[upFertCrop];
					NFertX = 1.0;
				}
				*/

				//need to consider a read-in next years crop for fall fertilizer autofert applications

				float NFertX = 1.0;
				float ProfileNN = 0.0;
				int root_q2 = (int)(max_root_length[1] / h[1]);
				if (root_q2 > q) root_q2 = q; // Ensure we don't go beyond soil layers
				int minRootDepth = (int)(0.60 / h[1]); // Minimum root depth to consider for N moderation (e.g., 60 cm)
				if (root_q2 < minRootDepth)root_q2 = minRootDepth; // Ensure we consider at least the minimum root depth

				for (int iz = 1; iz <= root_q2; iz++)
				{
					ProfileNN += (nh4[iz] + no3[iz]);
				}

				// --------------------------------
				// Control parameters
				// --------------------------------
				double Ntarget = 0.90;    // desired average crop N stress
				double NFertMin = 0.6;    // lower realistic bound
				double NFertMax = 1.6;    // upper realistic bound
				double Ncrit = 150.0;  // soil N damping threshold

				// --------------------------------
				// Deviation from target
				// --------------------------------
				double Ns = averageNStress[cropT];
				if (Ns == 0.0) Ns = 1.0;//avoid divide by zero or log of zero in future iterations
				double dN = Ns - Ntarget;   // + = excess N, - = deficit

				// --------------------------------
				// Mirrored quadratic response
				// Same curvature above and below 0.9
				// --------------------------------
				// Curvature tuned to be similar to your original polynomial behavior
				double curvature = 4.0;

				// Quadratic, symmetric about dN = 0
				// Below 0.9 (dN < 0)  NFertX > 1
				// Above 0.9 (dN > 0)  NFertX < 1
				NFertX = 1.0 - curvature * dN * fabs(dN);

				// --------------------------------
				// Soil profile N moderation (ALWAYS applied)
				// --------------------------------
				if (NFertX < 1.0) {
					double soilFactor = 1.0 / (1.0 + ProfileNN / Ncrit);
					NFertX *= soilFactor;
				}

				// --------------------------------
				// Enforce bounds last (avoid hard jumps)
				// --------------------------------
				NFertX = min(NFertMax, max(NFertMin, NFertX));

				// --------------------------------
				// First year handling (as in your original code)
				// --------------------------------
				if (year == 1)
				{
					averageNUptake[cropT] = maxmn[upFertCrop];
					NFertX = 1.0;
				}



				//manureTotalN = ((maxmn[upFertCrop] * 1.00) / (1 / (1.01 - ini_N_fix[upFertCrop])) * NFertX - (ProfileNN * 0.25));

				if (year == 1)//need to set for first year since no running average
				{
					averageNUptake[cropT] = maxmn[upFertCrop];
					NFertX = 1.0;
				}
				//need to consider a read-in next years crop for fall fertilizer autofert applications
				if (jdfer[2] <= 0)//no split date
				{
					if (fallFertFlag == 0)//test if not fall fert
					{
						FertAddN[i] = ((maxmn[upFertCrop] * 0.80) / (1 / (1.01 - ini_N_fix[upFertCrop])) * NFertX - (ProfileNN + ResidualNN * 0.25));// calculate the amount of fertilizer N to add based on plant N demand (maxmn) and subtract the profileN and 95% of residual N 
					}
					else //if fall fert 
					{
						FertAddN[i] = ((nextYearMaxN * 0.80) / (1 / (1.01 - nextYearFixN)) * NFertX - (ProfileNN + ResidualNN * 0.25));// calculate the amount of fertilizer N to add based on plant N demand (maxmn) and subtract the profileN and 95% of residual N 
					}
				}
				else if (jday == jdfer[1])//test if during first loop of fertilizer split
				{
					FertAddN[i] = 18;// calculate the amount of fertilizer N to add based on plant N demand (maxmn) and subtract the profileN and 95% of residual N 
				}
				else if (jday == jdfer[2])//test if during second loop of fertilizer split
				{
					FertAddN[i] = ((maxmn[upFertCrop] * 0.75) / (1 / (1.01 - ini_N_fix[upFertCrop])) * NFertX - (ProfileNN + ResidualNN * 0.05));// calculate the amount of fertilizer N to add based on plant N demand (maxmn) and subtract the profileN and 95% of residual N 
				}
				else
				{
					FertAddN[i] = 0.0;
				}

				if (FertAddN[i] < 0.0) FertAddN[i] = 0.0;

				
				//determine type of fertilizer added. 
				//Nitrate, NH4HCO3, Urea, Anhydrous_ammonia, NH4+, SO4, NH42HPO4 
				float totalNFert = 0.0;
				int fertDepthLayer;

				fertDepthLayer = (int)(fer_dept[i] / h[1] + 1);
				if (fertDepthLayer < 1) fertDepthLayer = 1;
				if (DayFert1[jday] + DayFert2[jday] + DayFert3[jday] + DayFert4[jday] + DayFert5[jday] > 0.00001)
				{
					totalNFert = DayFert1[jday] + DayFert2[jday] + DayFert3[jday] + DayFert4[jday] + DayFert5[jday];
				}
				else
				{
					totalNFert = 0.0000000001;
				}

				if (FertAddN[i] > 0.0 && SlowReleaseDays<1)
				{
					fert_flag = 1;
					day_inFertN += FertAddN[i];
					yr_addfer += FertAddN[i];

					for (l = fertDepthLayer; l <= (fertDepthLayer + 1); l++)
					{
					
						no3[l] += (FertAddN[i] * (DayFert1[jday] / totalNFert)/2.0);
						NH4HCO3[l] += (FertAddN[i] * (DayFert2[jday] / totalNFert)/2.0);
						urea[l] += (FertAddN[i] * (DayFert3[jday] / totalNFert)/2.0);
						nh4[l] += (FertAddN[i] * (DayFert4[jday] / totalNFert)/2.0);
						nh4[l] += (FertAddN[i] * (DayFert5[jday] / totalNFert)/2.0);
					}
				}
				else
				{
					if (SlowReleaseDays>1)//if (SlowReleaseDays == slowReleaseCounter)
					{
						totalNFert = fer1[i] + fer2[i] + fer3[i] + fer4[i] + fer5[i] + fer6[i] + fer7[i];
						DayFertRelease[1] = FertAddN[i] * (fer1[i] / totalNFert);// / SlowReleaseDays
						DayFertRelease[2] = FertAddN[i] * (fer2[i] / totalNFert) ;// / SlowReleaseDays
						DayFertRelease[3] = FertAddN[i] * (fer3[i] / totalNFert) ;// / SlowReleaseDays
						DayFertRelease[4] = FertAddN[i] * (fer4[i] / totalNFert) ;// / SlowReleaseDays
						DayFertRelease[5] = FertAddN[i] * (fer5[i] / totalNFert) ;// / SlowReleaseDays
						DayFertRelease[6] = FertAddN[i] * (fer6[i] / totalNFert) ;// / SlowReleaseDays
						DayFertRelease[7] = FertAddN[i] * (fer7[i] / totalNFert) ;// / SlowReleaseDays
						//jdfer[i] = jday + 1;//change the fert day to the next day.

						/*
						DayFixFert1 += DayFertRelease[1];
						DayFixFert2 += DayFertRelease[2];
						DayFixFert3 += DayFertRelease[3];
						DayFixFert4 += DayFertRelease[4];
						DayFixFert5 += DayFertRelease[5];
						DayFixFert6 += DayFertRelease[6];
						DayFixFert7 += DayFertRelease[7];
						*/
						for (l = fertDepthLayer; l <= (fertDepthLayer + 1); l++)
						{
							no3[l] += DayFertRelease[1]/2.0;
							NH4HCO3[l] += DayFertRelease[2] / 2.0;
							urea[l] += DayFertRelease[3] / 2.0;
							nh4[l] += DayFertRelease[4] / 2.0;
							nh4[l] += DayFertRelease[5] / 2.0;
						}
						//slowReleaseCounter -= 1;


						fer1[i] = 0.0;
						fer2[i] = 0.0;
						fer3[i] = 0.0;
						fer4[i] = 0.0;
						fer5[i] = 0.0;
						fer6[i] = 0.0;
						fer7[i] = 0.0;

						day_inFertN += FertAddN[i];//  /SlowReleaseDays
						yr_addfer += FertAddN[i];//   /SlowReleaseDays

					}
					else if (slowReleaseCounter > 0)
					{
						for (l = fertDepthLayer; l <= (fertDepthLayer + 1); l++)
						{
							no3[l] += DayFertRelease[1] / 2.0;
							NH4HCO3[l] += DayFertRelease[2] / 2.0;
							urea[l] += DayFertRelease[3] / 2.0;
							nh4[l] += DayFertRelease[4] / 2.0;
							nh4[l] += DayFertRelease[5] / 2.0;
						}
						DayFixFert1 += DayFertRelease[1];
						DayFixFert2 += DayFertRelease[2];
						DayFixFert3 += DayFertRelease[3];
						DayFixFert4 += DayFertRelease[4];
						DayFixFert5 += DayFertRelease[5];
						DayFixFert6 += DayFertRelease[6];
						DayFixFert7 += DayFertRelease[7];

						jdfer[i] = jday + 1;//change the fert day to the next day
						slowReleaseCounter -= 1;
						totalNFert = DayFertRelease[1] + DayFertRelease[2] + DayFertRelease[3] + DayFertRelease[4] + DayFertRelease[5] + DayFertRelease[6] + DayFertRelease[7];
						day_inFertN += totalNFert;
						yr_addfer += totalNFert;
					}
					else {
						slowReleaseCounter = 0;
					}
				}
				


			}//jdfer loop

			if (isnan(nh4[1]))
			{
				float blah;
				blah = 1.0;
			}

		}
		
	}//if autofert=222

	else if(FertOption==111)//fertigation
	{
		fert_flag = 0;
		//IrriMethod = 2;

		float day_add_fert = day_fert1+day_fert2+day_fert3+day_fert4+day_fert5+day_fert6;
		if(day_add_fert>0.0)
		{
			float IrriDepth;
			if(IrriMethod==0)//furrow
				IrriDepth = 0.01;
			else if(IrriMethod==1)//sprinkler
				IrriDepth = 0.01;
			else if(IrriMethod==2)//surface drip
				IrriDepth = 0.01;
			else //subsurface drip
				IrriDepth = 0.1;

			yr_addfer += day_add_fert;
			day_inFertN += day_add_fert;
			int sqq=(int)(IrriDepth/h[1])+2;
			
			for(int ss=sqq-1; ss<=sqq; ss++)
			{
				no3[ss] += (day_fert1 / 2.0);//nitrate
				NH4HCO3[ss] += (day_fert2 / 2.0);//ammnium bicarbonate
				urea[ss] += (day_fert3*0.5 / 2.0);//urea
				nh3[ss] += (day_fert4 / 2.0);//anhydrous ammonia
				nh4[ss] += ((day_fert5+day_fert3*0.5) / 2.0);//ammonium
				//nh4[ss] += (day_fert6 / 2.0);//sulphate
				//nh4[ss] += (day_fert7 / 2.0);//phosphate

				float FFn2o;
				FFn2o = 0.002 * nh4[ss];
				nh4[ss] -= FFn2o;
				n2o[ss] += FFn2o;

				FFn2o = 0.005 * no3[ss];
				no3[ss] -= FFn2o;
				n2o[ss] += FFn2o;

				FFn2o=0.0;
			}
		}
	}
	else//FertOption==0
	{
		for ( ox = 1; ox <= fer_num; ox++ )
		{
			if ( jday == jdfer[ox])
			{
				fert_flag = 1;

				UreaHydroInhibEf = UreaseEfficiency[ox];
				UreaHydroInhibDu = UreaseDuration[ox];
					UIDay1=jday;
				UIDay2=UIDay1 + (int)UreaseDuration[ox];
				if(UreaHydroInhibDu>0.0) UreaHydroInhibDays = 1;
				else UreaHydroInhibDays = 0;
				
				FertDepth = fer_dept[ox];
				fer_layer = (int)(fer_dept[ox] / h[1] + 1);//????
				if(fer_layer<1) fer_layer=1;

				NIEfficiency = NIefficiency[ox];
				NIDuration0 = NIduration[ox];
				NIDuration1 = NIduration[ox];

				NIDay1 = jday;
				NIDay2 = NIDay1 + (int)NIduration[ox];


				//day_inFertN = (fer1[ox] + fer2[ox] + fer3[ox] + fer4[ox] + fer5[ox] + fer6[ox] + fer7[ox]);
				//yr_addfer += day_inFertN;

/*				float FFy = 0.0222 * (float)log(FertDayRelease[ox]) + 0.876£»
				float RemainFert1 = fer1[ox] * powf(FFy, FertDays));
*/					
				AppliedUrea = fer3[ox];

				if(fer3[ox]>0.0) UreaAppDays = 1;

				//slow release fertilizer
				if(FertDayRelease[ox]>1.0) 
				{
					SlowReleaseDays = FertDayRelease[ox];
					
					DayFixFert1 += fer1[ox];
					DayFixFert2 += fer2[ox];
					DayFixFert3 += fer3[ox];
					DayFixFert4 += fer4[ox];
					DayFixFert5 += fer5[ox];
					DayFixFert6 += fer6[ox];
					DayFixFert7 += fer7[ox];

					IniFixFert1 = fer1[ox];
					IniFixFert2 = fer2[ox];
					IniFixFert3 = fer3[ox];
					IniFixFert4 = fer4[ox];
					IniFixFert5 = fer5[ox];
					IniFixFert6 = fer6[ox];
					IniFixFert7 = fer7[ox];

					DayFertRelease[1] = fer1[ox] / SlowReleaseDays;
					DayFertRelease[2] = fer2[ox] / SlowReleaseDays;
					DayFertRelease[3] = fer3[ox] / SlowReleaseDays;
					DayFertRelease[4] = fer4[ox] / SlowReleaseDays;
					DayFertRelease[5] = fer5[ox] / SlowReleaseDays;
					DayFertRelease[6] = fer6[ox] / SlowReleaseDays;
					DayFertRelease[7] = fer7[ox] / SlowReleaseDays;

					/*DayFert1[jday] += fer1[ox];
					DayFert2[jday] += fer2[ox];
					DayFert3[jday] += fer3[ox];
					DayFert4[jday] += fer4[ox];
					DayFert5[jday] += fer5[ox];
					DayFert6[jday] += fer6[ox];
					DayFert7[jday] += fer7[ox];*/
				}
				else
				{
					DayFert1[jday] += fer1[ox];
					DayFert2[jday] += fer2[ox];
					DayFert3[jday] += fer3[ox];//urea
					DayFert4[jday] += fer4[ox];
					DayFert5[jday] += fer5[ox];//ammonium
					DayFert6[jday] += fer6[ox];
					DayFert7[jday] += fer7[ox];

					fer1[ox] = 0.0;
					fer2[ox] = 0.0;
					fer3[ox] = 0.0;
					fer4[ox] = 0.0;
					fer5[ox] = 0.0;
					fer6[ox] = 0.0;
					fer7[ox] = 0.0;
				}
			}
		}

		if(fert_flag==0) DAA = 0;
		else DAA++;
		
		if(SlowReleaseDays>0)
		{

					//Brian added SlowRelease for manual application
			
					//if (fer3[i] > 0.0) UreaAppDays = 1;


			
				//slow release fertilizer
			if (SlowReleaseDays > 0)
			{
			 slowReleaseCounter = SlowReleaseDays + jday;
				
				
			}
			else
			{
			slowReleaseCounter = 1;
			}


			if((DayFixFert1+DayFixFert2+DayFixFert3+DayFixFert4+DayFixFert5+DayFixFert6+DayFixFert7)>0.000001)
			{
				//float TFdaa = 0.5963 * powf((float)SlowReleaseDays, -0.7433);
				sfer1 = DayFertRelease[1]* SlowReleaseDays;//DayFixFert1 * TFdaa; //need to add as a slow release N pool because slow release only works for urea atm with the slow release routine enabled in urea_hydrolysis
				sfer2 = DayFertRelease[2] * SlowReleaseDays;//DayFixFert2 * TFdaa;
				sfer3 = DayFertRelease[3] * SlowReleaseDays;//DayFixFert3 * TFdaa;
				sfer4 = DayFertRelease[4] * SlowReleaseDays;//DayFixFert4 * TFdaa;
				sfer5 = DayFertRelease[5] * SlowReleaseDays;//DayFixFert5 * TFdaa;
				sfer6 = DayFertRelease[6] * SlowReleaseDays;//DayFixFert6 * TFdaa;
				sfer7 = DayFertRelease[7] * SlowReleaseDays;//DayFixFert7 * TFdaa;

				DayFert1[jday] += sfer1;
				DayFert2[jday] += sfer2;
				DayFert3[jday] += sfer3;
				DayFert4[jday] += sfer4;
				DayFert5[jday] += sfer5;
				DayFert6[jday] += sfer6;
				DayFert7[jday] += sfer7;
				
				DayFixFert1 -= sfer1;
				DayFixFert2 -= sfer2;
				DayFixFert3 -= sfer3;
				DayFixFert4 -= sfer4;
				DayFixFert5 -= sfer5;
				DayFixFert6 -= sfer6;
				DayFixFert7 -= sfer7;

				DayFixFert1 = max(DayFixFert1, 0.0);
				DayFixFert2 = max(DayFixFert2, 0.0);
				DayFixFert3 = max(DayFixFert3, 0.0);
				DayFixFert4 = max(DayFixFert4, 0.0);
				DayFixFert5 = max(DayFixFert5, 0.0);
				DayFixFert6 = max(DayFixFert6, 0.0);
				DayFixFert7 = max(DayFixFert7, 0.0);

				day_inFertN += sfer1+sfer2+sfer3+sfer4+sfer5;//+sfer6;
				yr_addfer += day_inFertN;
			//	SlowReleaseDays -= 1;
				//slowReleaseCounter -= 1;//Brian reduce slowRelease
			//	if (SlowReleaseDays <= 0)SlowReleaseDays = 0;
				
			}
			else
			{
				SlowReleaseDays -= 1;
				//slowReleaseCounter -= 1;//Brian reduce slowRelease
				if (SlowReleaseDays <= 0)SlowReleaseDays = 0;


				/*
				sfer1 = DayFertRelease[1];//DayFixFert1 * TFdaa;
				sfer2 = DayFertRelease[2];//DayFixFert2 * TFdaa;
				sfer3 = DayFertRelease[3];//DayFixFert3 * TFdaa;
				sfer4 = DayFertRelease[4];//DayFixFert4 * TFdaa;
				sfer5 = DayFertRelease[5];//DayFixFert5 * TFdaa;
				sfer6 = DayFertRelease[6];//DayFixFert6 * TFdaa;
				sfer7 = DayFertRelease[7];//DayFixFert7 * TFdaa;

				DayFert1[jday] += sfer1;
				DayFert2[jday] += sfer2;
				DayFert3[jday] += sfer3;
				DayFert4[jday] += sfer4;
				DayFert5[jday] += sfer5;
				DayFert6[jday] += sfer6;
				DayFert7[jday] += sfer7;

				DayFixFert1 -= sfer1;
				DayFixFert2 -= sfer2;
				DayFixFert3 -= sfer3;
				DayFixFert4 -= sfer4;
				DayFixFert5 -= sfer5;
				DayFixFert6 -= sfer6;
				DayFixFert7 -= sfer7;

				DayFixFert1 = max(DayFixFert1, 0.0);
				DayFixFert2 = max(DayFixFert2, 0.0);
				DayFixFert3 = max(DayFixFert3, 0.0);
				DayFixFert4 = max(DayFixFert4, 0.0);
				DayFixFert5 = max(DayFixFert5, 0.0);
				DayFixFert6 = max(DayFixFert6, 0.0);
				DayFixFert7 = max(DayFixFert7, 0.0);

				day_inFertN += sfer1 + sfer2 + sfer3 + sfer4 + sfer5;//+sfer6;
				yr_addfer += day_inFertN;
				SlowReleaseDays -= 1;
				if (SlowReleaseDays <= 0)SlowReleaseDays = 0;
				//SlowReleaseDays = 0;
				*/
			}
		}
		else //normal fertilizer
		{
			//Nitrate, NH4HCO3, Urea, Anhydrous_ammonia, NH4+, SO4, NH42HPO4 
			if(DayFert1[jday]+DayFert2[jday]+DayFert3[jday]+DayFert4[jday]+DayFert5[jday]>0.00001)
			{
				day_inFertN += DayFert1[jday]+DayFert2[jday]+DayFert3[jday]+DayFert4[jday]+DayFert5[jday];//+DayFert7[jday];
	
				yr_addfer += day_inFertN;
				
			}

			if(DayFert4[jday]>0.0)//ammonia
			{
				float v_nh3;
				float v_d = FertDepth*100.0;
				if(v_d<1.5) v_d=1.5;
				v_nh3 = 0.02 * DayFert4[jday] * air_temp / v_d ;
				//day_soil_nh3 += v_nh3;
				//DayFert4[jday] -= v_nh3;
			}

			if(DayFert7[jday]>0.0)//phosphate
			{
				float addP = DayFert7[jday];// * 30.97 / 28.0;
				LabP[1] += addP;
				day_inFertP = addP;
				yr_inFertP += addP;
				DayFert7[jday] = 0.0;
			}
			
			if(DayFert6[jday]>0.0)//sulphate
			{
				for(int j=1; j<=15; j++)
					SO4[j] += DayFert6[jday]/28.0*1000000.0/mmm[j]/15.0; //mmol SO4/kg soil

				DayFert6[jday] = 0.0;
			}
		}
		
		if((DayFert1[jday]+DayFert2[jday]+DayFert3[jday]+DayFert4[jday]+DayFert5[jday])>0.00001)
		{
			
			if (FertMethodApp[fer_num] != 2)//for broadcast/injected
			{
				for (l = fer_layer; l <= (fer_layer + 1); l++)
				{

					if (FertMethodApp[fer_num] == 1)
					{
						//track banding application

						BandedAppMulti[l] = 100.0;

					}


					no3[l] += ((DayFert1[jday]) / 2.0);
					NH4HCO3[l] += (DayFert2[jday] / 2.0);
					urea[l] += (DayFert3[jday] / 2.0);
					/*
					if (l == fer_layer)
					{
						urea[l] += (DayFert3[jday] / 1.0);
					}
					*/
					nh4[l] += (DayFert4[jday] / 2.0);
					nh4[l] += (DayFert5[jday] / 2.0);
					//nh4[l] += (DayFert6[jday] / 2.0);
					//nh4[l] += (DayFert7[jday] / 2.0);

					float Nitrify = 0.0;//y = 2E+07x-11.432
					float Factor_ph = 2E+07 * powf(sph[q], -11.432);//0.00041+2*0.01221/3.14*2.029/(4*pow((sph[1]-7.5),2)+2.029*2.029);//lena, Lorentz
					float temp_fact = min(1.0, 0.1654 * exp(0.0742 * temp[1]));	//Ralf, changed
					float TopNH4 = nh4[l] + 0.2 * urea[l];

					Factor_ph = min(0.01, max(0.002, Factor_ph));
					float Ef = 5.0 * temp_fact * Factor_ph * day_wfps[l];//5.0
					if (Ef > 1.0) Ef = 1.0;

					/*
					if(TopNH4>0.0&&temp[1]>0.0)//&&day_wfps[l]>(0.5*fldcap[l]))//TTT>0.0)
					{
						Nitrify = Ef*TopNH4*MicrobioIndex;// * day_wfps[l];//0.65
						nh4[l] -= (Nitrify * nh4[l]/TopNH4);
						urea[l] -= (Nitrify * (0.2*urea[l])/TopNH4);
					}
					else Nitrify = 0.0;
					*/

					float Fdpt = 1.0;
					int LPW = (int)(0.12 / h[1]);
					if (l > LPW) Fdpt = powf(0.9, (l - LPW));

					//	no[l] += (Nitrify * 0.4 * Fdpt);
					//	n2o[l] += (Nitrify * 0.6 * Fdpt);
				}
			}
			else//for incorporated
			{
				for (l = 1; l <= (fer_layer); l++)
				{
				
					no3[l] += ((DayFert1[jday]) / fer_layer);
					NH4HCO3[l] += (DayFert2[jday] / fer_layer);
					urea[l] += (DayFert3[jday] / fer_layer);
					
					nh4[l] += (DayFert4[jday] / fer_layer);
					nh4[l] += (DayFert5[jday] / fer_layer);
				

					float Nitrify = 0.0;//y = 2E+07x-11.432
					float Factor_ph = 2E+07 * powf(sph[q], -11.432);//0.00041+2*0.01221/3.14*2.029/(4*pow((sph[1]-7.5),2)+2.029*2.029);//lena, Lorentz
					float temp_fact = min(1.0, 0.1654 * exp(0.0742 * temp[1]));	//Ralf, changed
					float TopNH4 = nh4[l] + 0.2 * urea[l];

					Factor_ph = min(0.01, max(0.002, Factor_ph));
					float Ef = 5.0 * temp_fact * Factor_ph * day_wfps[l];//5.0
					if (Ef > 1.0) Ef = 1.0;

					

					float Fdpt = 1.0;
					int LPW = (int)(0.12 / h[1]);
					if (l > LPW) Fdpt = powf(0.9, (l - LPW));
				
				
				}
			}
			DayFixFert1=0.0;
			DayFixFert2=0.0;
			DayFixFert3=0.0;
			DayFixFert4=0.0;
			DayFixFert5=0.0;
			DayFixFert6=0.0;
			DayFixFert7=0.0;
		}
	}

	if(DayFixFert1<0.0) DayFixFert1=0.0;
	if(DayFixFert2<0.0) DayFixFert2=0.0;
	if(DayFixFert3<0.0) DayFixFert3=0.0;
	if(DayFixFert4<0.0) DayFixFert4=0.0;
	if(DayFixFert5<0.0) DayFixFert5=0.0;
	if(DayFixFert6<0.0) DayFixFert6=0.0;
	if(DayFixFert7<0.0) DayFixFert7=0.0;

}

float class_model::manuring(int livestock, int scale, int FarmNumber, float *FarmCropArea, 
							float *FarmCropManureFraction, int FarmField, FILE *ftf)
{
    int   oz=0, l, manuType, adp;
    float AddC=0.0, liquid_N, manure_add_N=0.0;
	float AddC1=0.0, AddC2=0.0, AddC3=0.0, AddHum=0.0, AddDOC=0.0, dUrea=0.0;	
	float AddCN=100.0, dInertC=0.0, manuDepth=0.0;
	float manureOrgN, manureNH4, manureNO3, manureDOC, manureUREA;
	float newmanuDM=0.0;
	float addManWater=0.0;
	

	manuFlag=0;
	//if (autoManure == 0)
	//{
		//new autoManure code


	//calculate manure N auto needs
	

		

		//only works for spring manure
		float manureTotalN = 0.0;
		float manureOrgNFrac = 0.5;
		float manureMinFrac = 0.5;
		float manureNH4Frac = 0.75;
		float manureNO3Frac = 0.25;
		float manureOrgCN = 10.0;
	//	manureTotalN = ((maxmn[upFertCrop] * 1.00) / (1 / (1.01 - ini_N_fix[upFertCrop])) * NFertX - (ProfileNN  * 0.5));// calculate the amount of fertilizer N to add based on plant N demand (maxmn) and subtract the profileN and 95% of residual N 


		if (manureTotalN < 0.0) manureTotalN = 1.0;

		



		for (oz = 1; oz <= man_num; oz++)
		{
			
			

			if (jday == jdman[oz] && (ManureOrgC[oz] + ManureNH4[oz] + ManureNO3[oz]) > 0.0)
			{
				//used for autoManure fractioning
				manureOrgNFrac = ManureOrgN[oz] / (ManureOrgN[oz]+ ManureNH4[oz] + ManureNO3[oz]);
				manureMinFrac = 1.0 - manureOrgNFrac;
				manureNH4Frac = ManureNH4[oz] / (ManureNH4[oz] + ManureNO3[oz]);
				manureNO3Frac = ManureNO3[oz] / (ManureNH4[oz] + ManureNO3[oz]);
				manureOrgCN = ManureOrgC[oz] / ManureOrgN[oz];

				if (autoManure == 0)
				{
					manureOrgNFrac = 0.0;
					manureMinFrac = 0.0;
					manureNH4Frac = 0.0;
					manureNO3Frac = 0.0;

				}

				manuMethod = ManureMethod[oz];
				manuDepth = ManureDepth[oz];
				manuType = ManureType[oz];

				if (autoManure == 0)
				{
					
					manureOrgN = ManureOrgN[oz];//solid organic N		
					manureDOC = ManureOrgC[oz] * 0.0; //DOC
					
					AddC = ManureOrgC[oz] * 1.0;	//solid organic C
					if (manuType == 4)
					{
						manureDOC = ManureOrgC[oz] * 0.0; //DOC //.67
						AddC = ManureOrgC[oz] * 1.0;	//solid organic C 0.33
					}
					AddCN = AddC / (manureOrgN); //C/N for solid organic matter//manureOrgN
					manure_add_N = manureOrgN + ManureNH4[oz] + ManureNO3[oz];



					manureUREA = 0.0;//default 0.0
					manureNH4 = ManureNH4[oz];
					manureNO3 = ManureNO3[oz];
					newmanuDM = manuDM[oz];
					newmanuPH = manuPH[oz];
					addManWater = ((AddC / 0.4 / (newmanuDM / 100)) * (1 - (newmanuDM / 100))) / 100000;//calculates the amount of water (cm) incoming with manure slury based on the dry matter% and the assumed %C of 40. 
				}
				else//autoManureing
				{

					if (autoManure == 1)
					{
						float NFertX = 1.0;

						// --------------------------------
						// Calculate soil profile mineral N
						// --------------------------------
						float ProfileNN = 0.0;
						int root_q1 = (int)(max_root_length[1] / h[1]);
						if (root_q1 > q) root_q1 = q; // Ensure we don't go beyond soil layers
						int minRootDepth = (int)(0.60 / h[1]); // Minimum root depth to consider for N moderation (e.g., 60 cm)
						if (root_q1 < minRootDepth)root_q1 = minRootDepth; // Ensure we consider at least the minimum root depth

						for (int iz = 1; iz <= root_q1; iz++)
						{
							ProfileNN += (nh4[iz] + no3[iz]);
						}

						for (int i = 0; i <= 9; i++)
						{
							if (cropRotType[i] == crop[1]) //if the cropRotType array is equal to the crop[z] or 
							{

								cropT = i;
								break;
							}
							else if (cropRotType[i] == 0)//if cropRotType at the current index is zero
							{
								cropRotType[i] = crop[1]; //adding the current crop to the cropRotType to the current crop
								cropT = i;
								break;
							}
						}

						// --------------------------------
						// Control parameters
						// --------------------------------
						double Ntarget = 0.92;    // desired average crop N stress
						double NFertMin = 0.6;    // lower realistic bound
						double NFertMax = 1.6;    // upper realistic bound
						double Ncrit = 350.0;  // soil N damping threshold

						// --------------------------------
						// Deviation from target
						// --------------------------------
						double Ns = averageNStress[cropT];
						if (Ns == 0.0) Ns = 1.0;//avoid divide by zero or log of zero in future iterations
						double dN = Ns - Ntarget;   // + = excess N, - = deficit

						// --------------------------------
						// Mirrored quadratic response
						// Same curvature above and below 0.9
						// --------------------------------
						// Curvature tuned to be similar to your original polynomial behavior
						double curvature = 4.0;

						// Quadratic, symmetric about dN = 0
						// Below 0.9 (dN < 0)  NFertX > 1
						// Above 0.9 (dN > 0)  NFertX < 1
						NFertX = 1.0 - curvature * dN * fabs(dN);

						// --------------------------------
						// Soil profile N moderation (ALWAYS applied)
						// --------------------------------
						if (NFertX < 1.0)
						{
							double soilFactor = 1.0 / (1.0 + ProfileNN / Ncrit);
							NFertX *= soilFactor;
						}

						// --------------------------------
						// Enforce bounds last (avoid hard jumps)
						// --------------------------------
						NFertX = min(NFertMax, max(NFertMin, NFertX));

						// --------------------------------
						// First year handling (as in your original code)
						// --------------------------------
						if (year == 1)
						{
							averageNUptake[cropT] = maxmn[upFertCrop];
							NFertX = 1.0;
						}
						if (year == 11)
						{
							float blah;
							blah = 1.0;
						}


						//manureTotalN =((maxmn[upFertCrop] * 1.00)/ (1 / (1.01 - ini_N_fix[upFertCrop]))* NFertX- (ProfileNN * 0.25));
						manureTotalN = ((maxmn[upFertCrop] * 1.05) / (1 / (1.01 - ini_N_fix[upFertCrop])) * NFertX - (ProfileNN * 0.25));

						//end new logic

						if (manureTotalN < 0.0) manureTotalN = 1.0;
					}


					manureOrgN = manureTotalN * manureOrgNFrac;//solid organic N		
					
					
					AddC = manureOrgN * manureOrgCN ;	//solid organic C
					if (manuType == 4)
					{
						manureDOC = AddC * 0.0; //DOC //.67
						AddC = manureOrgN * manureOrgCN;	//solid organic C 0.33
					}
					AddCN = AddC / (manureOrgN); //C/N for solid organic matter//manureOrgN
					manure_add_N = manureTotalN;



					manureUREA = 0.0;//default 0.0
					manureNH4 = manureTotalN * manureMinFrac * manureNH4Frac;  
					manureNO3 = manureTotalN * manureMinFrac * manureNO3Frac;
					newmanuDM = manuDM[oz];
					newmanuPH = manuPH[oz];
					addManWater = ((AddC / 0.4 / (newmanuDM / 100)) * (1 - (newmanuDM / 100))) / 100000;//calculates the amount of water (cm) incoming with manure slury based on the dry matter% and the assumed %C of 40. 

				}


				
				//manuMethod = ManureMethod[oz];
				water[1][1] += addManWater / 100;
				day_irri += addManWater / 100;
				yr_irri += addManWater / 100;
				manureHour = manuAppHour[oz];
				manu_layer = (int)(manuDepth / 100 / h[1] + 1);//calculating Manure_layer;

				manure_flag = 1;

				if (manuMethod == 0)
				{
					adp = 1;//surface application
					IrriMethod = 0; //0: furrow, 1: sprinkler, 2: drip-0cm, 3: drip-15cm
				}
				else if (manuMethod == 1)
				{
					adp = (int)((manuDepth * 0.01) / h[1]) + 1;//incorporation
					IrriMethod = 0;
				}
				else if (manuMethod == 2)
				{
					adp = (int)((manuDepth * 0.01) / h[1]) + 1; //injection to 15 cm
					IrriMethod = 3;
				}
				else
				{
					adp = 1;
					IrriMethod = 0;
				}

				if (manureNH4 > 0.0)
				{
					float Vnh3 = 0.0;
					//if(manuMethod==0) Vnh3 = manureNH4 * 0.3;
					//else if(manuMethod==1) Vnh3 = manureNH4 * 0.2;
					//else if(manuMethod==2) Vnh3 = manureNH4 * 0.1;
					//else Vnh3 = 0.0;

					day_soil_nh3 += Vnh3;
					manureNH4 -= Vnh3;
				}

				manuFlag = 1;
				ManureDays = 1;
				AddHum = 0.0;



				//added new manure stuff here.

				float manPassiveFrac, manAddC, manAddCN;
				manPassiveFrac = slowManFrac; // slowManFrac;//slowManFrac, &slowManKRate //being populated from manPoolFrac[1] from data files


				if (useManPool[oz] == 0)
				{
					manPassiveFrac = 0.0;
				}

				manPassiveFrac = min(0.9999999, max(0.0, manPassiveFrac));

				if (manPassiveFrac > 0.0)
				{
					manAddC = AddC * manPassiveFrac;
					AddC = AddC - manAddC; //new calculated AddC
				}
				else manAddC = 0.0;


				AddCN = AddC / (manureOrgN * (1.0 - manPassiveFrac)); // will need to think about how to move manPassiveFrac into an array and slowManFrac into an array and then average the C:N ratio based on the two addtions.

				if (manureOrgN > 0.0 && manPassiveFrac > 0.0)
				{
					float existingManureN, combinedManureN, combinedManureC;

					if (totalManureC > 0.0)//check if there is already existing manure in the manure Pool
					{
						existingManureN = totalManureC / manurePoolCN;//calculate the current organic N in the manurePool
						combinedManureN = existingManureN + manureOrgN * manPassiveFrac;
						combinedManureC = manAddC + totalManureC;
						manurePoolCN = combinedManureC / combinedManureN;


					}

					else
					{
						manAddCN = manAddC / (manureOrgN * manPassiveFrac);
						manurePoolCN = manAddCN;//new brian manurePool  //might need to think about how to handle multiple manure additions. 
						totalManureC = manAddC;
					}


				}


				if (totalManureC <= 0.0)
				{
					if (manurePoolCN == 0 || manAddC == 0)
					{
						manurePoolCN = 10.0;
					}
				}

				//partition solid manure into sub-pools of humads and litter
				alloc_manure_into_pools(AddCN, AddC, ManureType[oz], &AddC1, &AddC2, &AddC3, &dInertC, &AddHum, &AddDOC);//would need to not call on this if adding a new manure C pool

				// all of these additions need to not happen with new manure pool but should happen in manure pool (manureDOC, manureNH4, manureNO3, manureUrea, AddC1=very labile litter, AddC2=labile litter, AddC3=resistant labile litter.

				if (manuMethod == 0 || manuMethod == 2)//surface or injection
				{
					for (l = adp; l <= adp; l++)
					{
						if (useManPool[oz] == 1)//manPassiveFrac 
						{
							manurePool[l] += manAddC;
						}//manure that is added to user controlled pool.


						rcvl[l] += AddC1;
						rcl[l] += AddC2;
						rcr[l] += AddC3;
						crhl[l] += AddHum;//labile humads pool


						doc[l] += manureDOC;
						nh4[l] += manureNH4;
						no3[l] += manureNO3;
						urea[l] += manureUREA;
					}
				}
				else
				{
					for (l = 1; l <= adp; l++)//incoporation
					{
						if (manPassiveFrac > 0.0 && useManPool[oz] == 1)manurePool[l] += (manAddC / (float)adp);//manure that is added to user controlled pool.


						rcvl[l] += (AddC1 / (float)adp);
						rcl[l] += (AddC2 / (float)adp);
						rcr[l] += (AddC3 / (float)adp);
						crhr[l] += (AddHum / (float)adp);//crhr[l] resistant humads pool default


						doc[l] += (manureDOC / (float)adp);
						nh4[l] += (manureNH4 / (float)adp);
						no3[l] += (manureNO3 / (float)adp);
						urea[l] += (manureUREA / (float)adp);
					}
				}

				//day_addmc += (AddC1 + AddC2 + AddC3 + AddHum + manureDOC);
				//yr_addmc += (AddC1 + AddC2 + AddC3 + AddHum + manureDOC);

				day_addmc += (AddC + manureDOC + manAddC);//add manure
				yr_addmc += (AddC + manureDOC + manAddC);//add manure




				yr_addmn += manure_add_N;
				day_inManureN += manure_add_N;


				AddC1 = 0.0;
				AddC2 = 0.0;
				AddC3 = 0.0;
				AddHum = 0.0;
				AddDOC = 0.0;
				liquid_N = 0.0;
				manureNH4 = 0.0;
				manureNO3 = 0.0;
				manureDOC = 0.0;
				manureUREA = 0.0;
			}
			else
			{

			}
		}//manure application loop
	//}//autoManure==0
		/*
	else//autoManure==1
	{
		float NFertX;
		if (averageNStress[cropT] > 0.9) 
		{
			NFertX = -23.106*pow(averageNStress[cropT],2)+42.145* averageNStress[cropT]-18.234;
			NFertX = min(2.0, max(0.1, NFertX));
		}
		else if (averageNStress[cropT] <= 0.9)
		{
			NFertX = averageNStress[cropT]+2.0;
			NFertX = min(2.0, max(0.1, NFertX));
		}
		else
		{
			NFertX = 1.0;
		}
		if (year == 1)//need to set for first year since no running average
		{
			averageNUptake[cropT] = maxmn[upFertCrop];
			NFertX = 1.0;
		}

		//example

		//only works for spring manure
			FertAddN[i] = ((maxmn[upFertCrop] * 0.80) / (1 / (1.01 - ini_N_fix[upFertCrop])) * NFertX - (ProfileNN + ResidualNN * 0.5));// calculate the amount of fertilizer N to add based on plant N demand (maxmn) and subtract the profileN and 95% of residual N 
			
		
		if (FertAddN[i] < 0.0) FertAddN[i] = 0.0;






	}
	*/

/////////////////////////////////////////////////////
#ifdef MANURE

	int jjd, ManureAplMethod=0, madp=0;
	float ToField[30]={0,0}, ManureAplDepth=0.0;
	float MAC=0.0, MAN=0.0, MAP=0.0;

	float CFT = FarmCropArea[FarmField] / FarmCropManureFraction[FarmField];

	fscanf(ftf, "%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f", 
			&jjd, &ToField[1],&ToField[2],&ToField[3],&ToField[4],&ToField[5],&ToField[6],&ToField[7],&ToField[8],&ToField[9],
			&ToField[10],&ToField[11],&ToField[12],&ToField[13],&ToField[14],&ToField[15],&ToField[16],&ToField[17],
			&ToField[18],&ToField[19],&ToField[20],&ToField[21],&ToField[22], &ManureAplMethod, &ManureAplDepth);	

	yr_manure_water += ToField[22] /1000.0 / CFT/10000.0;//m water/ha

	MAC = (ToField[1]+ToField[2]+ToField[3]+ToField[4]+ToField[5]+ToField[6]+ToField[7]+ToField[8]+ToField[20]+ToField[21])/CFT;

	MAN = (ToField[1]/rcnrvl +ToField[2]/rcnrl +ToField[3]/rcnrr +ToField[4]/rcnb +ToField[5]/rcnb + ToField[6]/rcnh+ToField[7]/rcnh+
		ToField[8]/rcnm +ToField[12]+ToField[13]+ToField[14]+ToField[15]+ToField[16]+ToField[17]+ToField[18]+ToField[19])/CFT;

	MAP = (ToField[9]+ToField[10]+ToField[11])/CFT;

	sph[1] = 8.5;
	
	day_addmc += MAC;// + straw_DOC);
	yr_addmc += MAC;// + straw_DOC);
	
	day_inManureN += MAN;
	yr_addmn += MAN;

	day_inManureP += MAP;
	yr_addmP += MAP;	
	

	if(ManureAplMethod==0) madp = 1;//surface application
	else if(ManureAplMethod==1) madp = (int)((ManureAplDepth*0.01)/h[1])+1;//incorporation
	else if(ManureAplMethod==2) madp = (int)((ManureAplDepth*0.01)/h[1])+1; //injection to 15 cm
	else madp = 1;

	if(MAC>0.0)
	{
		if(ManureAplMethod==0||ManureAplMethod==2)//surface or injection
		{
			rcvl[madp]  += ToField[1] / CFT;//kg C -> kg C/ha
			rcl[madp]  += ToField[2] / CFT;
			rcr[madp]  += ToField[3] / CFT;
			CRB1[madp]  += ToField[4] / CFT;
			CRB2[madp]  += ToField[5] / CFT;
			crhl[madp] += ToField[6] / CFT;
			crhr[madp] += ToField[7] / CFT;
			dphum[madp]  += ToField[8] / CFT;
			OrgP[madp] += ToField[9] / CFT;
			LabP[madp] += ToField[10] / CFT;
			ComP[madp] += ToField[11] / CFT;
			nh4[madp]  += ToField[12] / CFT;
			no3[madp]  += ToField[13] / CFT;
			no2[madp]  += ToField[14] / CFT;
			no[madp]  += ToField[15] / CFT;
			n2o[madp]  += ToField[16] / CFT;
			n2[madp]  += ToField[17] / CFT;
			nh3[madp]  += ToField[18] / CFT;	
			urea[madp]  += ToField[19] / CFT;
			co2[madp]  += ToField[20] / CFT;
			doc[madp]  += ToField[21] / CFT;
			day_DOC_prod += ToField[21] / CFT;
			water[1][madp]  += ToField[22] /1000.0 / CFT/10000.0;//m water/ha
			
		}
		else
		{
			for(int zw=1; zw<=madp; zw++)
			{
				rcvl[zw]  += ToField[1] / CFT / (float)madp;
				rcl[zw]  += ToField[2] / CFT / (float)madp;
				rcr[zw]  += ToField[3] / CFT / (float)madp;
				CRB1[zw]  += ToField[4] / CFT / (float)madp;
				CRB2[zw]  += ToField[5] / CFT / (float)madp;
				crhl[zw] += ToField[6] / CFT / (float)madp;
				crhr[zw] += ToField[7] / CFT / (float)madp;
				dphum[zw]  += ToField[8] / CFT / (float)madp;
				OrgP[zw] += ToField[9] / CFT / (float)madp;
				LabP[zw] += ToField[10] / CFT / (float)madp;
				ComP[zw] += ToField[11] / CFT / (float)madp;
				nh4[zw]  += ToField[12] / CFT / (float)madp;
				no3[zw]  += ToField[13] / CFT / (float)madp;
				no2[zw]  += ToField[14] / CFT / (float)madp;
				no[zw]  += ToField[15] / CFT / (float)madp;
				n2o[zw]  += ToField[16] / CFT / (float)madp;
				n2[zw]  += ToField[17] / CFT / (float)madp;
				nh3[zw]  += ToField[18] / CFT / (float)madp;	
				urea[zw]  += ToField[19] / CFT / (float)madp;
				co2[zw]  += ToField[20] / CFT / (float)madp;
				doc[zw]  += ToField[21] / CFT / (float)madp;
				day_DOC_prod += ToField[21] / CFT / (float)madp;
				water[1][zw]  += ToField[22] /1000.0 / CFT/10000.0;//m water/ha
				
			}
		}
	}
#endif

   return( 0 );
}


void class_model::alloc_litter_into_pools(float *AddCN, float *AddC, int oz, float *AddC1, float *AddC2, 
										  float *AddC3, float *dInertC, int IfStub, 
										  float rcnrvl, float rcnrl, float rcnrr, float *nh4)
{
	float  RR1, RR2, RR3;
    float a, b, c, d, e, f;
	*dInertC = 0.0;
	float AddN = *AddC / *AddCN;


	//residue litter. Adding to C pools. depending on the added CN of the residue pool
	if ( *AddCN >= rcnrvl && *AddCN < rcnrl )
	{
		RR1 = rcnrvl;
		RR2 = rcnrl;
		*AddC2 = (AddN - *AddC/RR1) / (1.0/RR2 - 1.0/RR1);
		*AddC1 = (*AddC - *AddC2);
		*AddC3 = 0.0;		

		/*c = (1.0 / *AddCN);
		d = (1.0 / RR1);
		a = c - d;
		e = (1.0 / RR2);
		f = (1.0 / RR1);
		b = e - f;

		*AddC2 = *AddC * (a / b);
		*AddC1 = (*AddC - *AddC2);
		*AddC3 = 0.0;*/
	}
	else if ( *AddCN >= rcnrl && *AddCN <= rcnrr )
	{
		RR2 = rcnrl;
		RR3 = rcnrr;
		c = (1.0 / *AddCN);
		d = (1.0 / RR2);
		a = c - d;
		e = (1.0 / RR3);
		f = (1.0 / RR2);
		b = e - f;
		*AddC3 = (float)(*AddC * (a / b));
		*AddC2 = (float)(*AddC - *AddC3);
		*AddC1 = (float)0.0;
		}
		else if ( *AddCN < rcnrvl )
		{
			float ActN = *AddC/rcnrvl; 
			*AddC3 = 0.0;
			*AddC2 = 0.0;
			*AddC1 = *AddC;
			if(manure_flag==1)
			{
				nh4[manu_layer] += (*AddC / (*AddCN+0.0000001) - ActN);//allocates the decomposed DOC into top NH4 pool.
				
				manure_flag=0;
			}
			else
			{
			nh4[1] += (*AddC / (*AddCN+0.0000001) - ActN);//allocates the decomposed DOC into top NH4 pool.
			}
			*AddCN = rcnrvl; 
		}
		else if ( *AddCN > rcnrr )
		{
			//float ActC = *AddC/ *AddCN * rcnrr;
			*AddC3 = *AddC;//ActC;
			*AddC2 = 0.0;
			*AddC1 = 0.0;

			/**dInertC = *AddC - ActC;
			//inert_C[1] += dInertC;
			day_inert_C += *dInertC;
			yr_inert_C += *dInertC;*/
			//*AddC = ActC;
			//*AddCN = rcnrr;
		}

    if (*AddC1 < 0.0) *AddC1 = 0.0;
    if (*AddC2 < 0.0) *AddC2 = 0.0;
    if (*AddC3 < 0.0) *AddC3 = 0.0;

	
/*
	if(IfStub==0)
	{
		AddToSoilC = 0.05 * (*AddC1 + *AddC2 + *AddC3 + dInertC);
		AddToSoilN = 0.05* (*AddC1/rcnrvl + *AddC2/rcnrl + *AddC3/rcnrr);
		*AddC1 *= 0.95; 
		*AddC2 *= 0.95;
		*AddC3 *= 0.95;
		dInertC *= 0.95;
	}
	else
	{
		AddToSoilC = dInertC;
		AddToSoilN = 0.0;
		dInertC = 0.0;
	}

	if(IfStub==1)//litter turn into stub
	{
	}
	else//litter turn into soil C pools
	{
		float AddToSoilC, AddToSoilN;
		AddToSoilC = (*AddC1 + *AddC2 + *AddC3 + dInertC);
		AddToSoilN = (*AddC1/rcnrvl + *AddC2/rcnrl + *AddC3/rcnrr);

		day_addC += AddToSoilC;
		yr_addrc += AddToSoilC;
		day_addrn += AddToSoilN;
		yr_addrn += AddToSoilN;
	}
*/
}

void class_model::alloc_manure_into_pools(float AddCN, float AddC, int oz, float *AddC1, float *AddC2, float *AddC3, float *dInertC, float *AddHum, float *AddDOC)
{
	float FU, TN, ResidueN, ResidueCN, MaxC, NewAddC, NewAddCN;

	ResidueN = AddC / (AddCN+0.0000001); //seems to be the organic N pool that's added with Manure

	/*if(oz==1) *AddDOC = 0.1 * AddC;//farmyard manure
	else if(oz==4||oz==7||oz==8||oz==9) *AddDOC = 0.2 * AddC;//slurry manure
	else *AddDOC = 0.01 * AddC;
		
	AddC -= *AddDOC;	*/

	MaxC = 0.9 * ResidueN * rcnm;//0.9 is default for max C
/*
		float manMulti;
			manMulti=-0.2664*(MaxC/AddC)+0.49;
			manMulti=min(0.25,max(0.01,manMulti));

		*AddHum = manMulti * AddC;//0.9 * AddC;
		NewAddC = AddC - *AddHum;
		NewAddCN = NewAddC / (ResidueN - *AddHum/rcnm);
*/		
	float manCFast,manCSlow,newResidueN,fracFast;//cacluate a portion of manure C added to go to very labile (manCFast and the remainder will be allocated based on new C:N ratio for pools)
	fracFast=6.033*powf((AddC/ResidueN),-1.205);
	fracFast=min(.95,max(0.01,fracFast));
	
//	fracFast=(1-fracHumads);

	manCFast=(ResidueN * fracFast)*5;//50% going to very labile
	manCSlow=AddC-manCFast;//remainder to be allocated to pools below
	newResidueN=ResidueN*(1-fracFast);//calculate remainder organic N available based on verylabile/C:N 5 ratio
	NewAddCN=manCSlow/newResidueN;

	
	float topPool, botPool;
	if(NewAddCN<=5)
	{
	*AddHum = AddC*0.01;//this is C:N 10 pool
	
//	*AddHum = AddC*fracHumads;//this is C:N 10 pool
	
	NewAddC = AddC - *AddHum;//this should be C:N 5 pool
	NewAddCN = NewAddC / (ResidueN - *AddHum/rcnm);

		float ActN = NewAddC/rcnrvl; 
			*AddC3 = 0.0;
			*AddC2 = 0.0;
			*AddC1 = NewAddC;
			if(manure_flag==1)
			{
				nh4[manu_layer] += (NewAddC / (NewAddCN+0.0000001) - ActN);//allocates the decomposed DOC into top NH4 pool.
				
				manure_flag=0;
			}
			
			AddCN = rcnrvl; 




	}
	else if(NewAddCN <=10)
	{	
		

	   topPool=(NewAddCN-5)/5;
	   botPool=1-topPool;
		*AddHum= topPool*newResidueN*10;
		
//		*AddHum = AddC*fracHumads;//this is C:N 10 pool
	//	NewAddC = AddC - *AddHum;//this should be C:N 5 pool
	//	*AddC3 = 0.0;
	//	*AddC2 = 0.0;
	//	*AddC1 = NewAddC;

		*AddC1=botPool*newResidueN*5+manCFast;
		*AddC2=0.0;
		*AddC3=0.0;
	
	
	}
	else if(NewAddCN <= 25)
	{
		topPool=(NewAddCN-10)/15;
		botPool=1-topPool;
	
		*AddHum=botPool*newResidueN*10;
		
	//	*AddHum = AddC*fracHumads;//this is C:N 10 pool
	//	NewAddC = AddC - *AddHum;//this should be C:N 5 pool
	//	*AddC3 = 0.0;
	//	*AddC2 = 0.0;
	//	*AddC1 = NewAddC;



		*AddC2= topPool*newResidueN*25;
		*AddC1=manCFast;
		*AddC3=0.0;
	

	}
	else
	{
		topPool=(NewAddCN-25)/75;
		botPool=1-topPool;
		
	//	*AddHum = AddC*fracHumads;//this is C:N 10 pool
	//	NewAddC = AddC - *AddHum;//this should be C:N 5 pool
	//	*AddC3 = 0.0;
	//	*AddC2 = 0.0;
	//	*AddC1 = NewAddC;
		
		
		*AddC3= topPool*newResidueN*100;
		*AddC2=botPool*newResidueN*25;
		*AddC1=manCFast;
		*AddHum=0.0;

	}
	
    if (*AddC1 < 0.0) *AddC1 = 0.0;
    if (*AddC2 < 0.0) *AddC2 = 0.0;
    if (*AddC3 < 0.0) *AddC3 = 0.0;
	/*
	if(AddC>MaxC)
	{
		*AddHum = MaxC;
		NewAddC = AddC - *AddHum;
		NewAddCN = NewAddC / (ResidueN - *AddHum/rcnm);
	}
	else
	{
		*AddHum = 0.9 * AddC;//0.9 * AddC;
		NewAddC = AddC - *AddHum;
		NewAddCN = NewAddC / (ResidueN - *AddHum/rcnm);
	}
	*/

//	alloc_litter_into_pools(&NewAddCN, &NewAddC, oz, AddC1, AddC2, AddC3, dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);

    /*if (AddC1 < 0.0) AddC1 = 0.0;
    if (AddC2 < 0.0) AddC2 = 0.0;
    if (AddC3 < 0.0) AddC3 = 0.0;
	if (AddHum < 0.0) AddHum = 0.0;*/
}

float class_model::grazing()
{
   /*int ManureType=0, oz, i, a;
   float dung_CN, Ftt, NH3_emit;
   float C1, C2, C3, N1, N2, N3, urine1, urine2, urine3;
   float fresh_food, dead_food, total_food, food_demand;
   float food_need1, food_need2, food_need3;
   float plant_loss[8], stub_loss, stub1_loss, stub2_loss, stub3_loss;
   float F_dung;
   float sLeaf, sStem, sGrain, sRoot, sPlant;
   float AddC1, AddC2, AddC3, dInertC;
   float old_GrassN, Nratio, sLeaf_N, sStem_N, sGrain_N;

   for ( oz = 1; oz <= gra_num; oz++ )
   {
		if ( jday >= jdgra1[oz] && jday <= jdgra2[oz] && (TotalHeads[oz]>0.0) && (hrs[oz]>0.0))//grazing period
		{
			grazFlag=1;
			H_dairy = AnimalHead[1][oz];
			H_beef = AnimalHead[2][oz];
			H_pig = AnimalHead[3][oz];			
			H_sheep = AnimalHead[4][oz];
			H_horse = AnimalHead[5][oz];
			H_hrs = hrs[oz];

			//Feed available 
			fresh_food = 0.0;
			for(int i=1; i<=CropNumbers; i++)
			{
				fresh_food += (Grain_Wt[i] + Leaf_Wt[i] + Stem_Wt[i]); //kg C/ha
			}
			dead_food = stub1 + stub2 + stub3;
			total_food = fresh_food + dead_food;

			//Feed demand
			food_demand = total_C_demand[oz]; //kg C/ha/day
			yr_GrazeDemandC += food_demand;

			//Feed consumption
			float total_grass_consum = 0.0, GrassCNT = 0.0, GPT;

			for(int i=1; i<=CropNumbers; i++) GrassCNT += leafcn[i];

			if(total_food > 0.0)
			{
				for(int i=1; i<=CropNumbers; i++)
				{
					GPT = (Grain_Wt[i] + Leaf_Wt[i] + Stem_Wt[i]) / fresh_food; 
					if (food_demand <= total_food)
					{					
						  day_grass_consume[i] = food_demand * GPT;
						  plant_loss[i] = day_grass_consume[i] * fresh_food / (fresh_food + dead_food);
						  stub_loss = day_grass_consume[i] * dead_food / (fresh_food + dead_food);		
					}
					else
					{
						  day_grass_consume[i] = total_food * GPT;
						  plant_loss[i] = fresh_food * GPT;
						  stub_loss = dead_food * GPT;
					}

					total_grass_consum += day_grass_consume[i];
				}
			}
			else
			{
				for(int i=1; i<=CropNumbers; i++)
				{
					day_grass_consume[i] = 0.0;
					plant_loss[i] = 0.0;
					stub_loss = 0.0;
				}
			}

			if(food_demand<=0.0) day_deficit = 1.0;
			else day_deficit = total_grass_consum / food_demand;

			//Grazed plant C
			for(int p=1; p<=CropNumbers; p++)
			{
				sPlant = Grain_Wt[p] + Leaf_Wt[p] + Stem_Wt[p];

				float GQI = base_leafcn[p];

				if(sPlant>0.0)
				{
					float FDF = plant_loss[p] / fresh_food;
					sLeaf = FDF * Leaf_Wt[p];
					sStem = FDF * Stem_Wt[p];
					sGrain = FDF * Grain_Wt[p];
				}
				else
				{
					sLeaf = 0.0;
					sStem = 0.0;
					sGrain = 0.0;					
				}

				Leaf_Wt[p] -= sLeaf;
				Stem_Wt[p] -= sStem;
				Grain_Wt[p] -= sGrain;

				sLeaf_N = sLeaf / leafcn[p];
				sStem_N = sStem / stemcn[p];
				sGrain_N = sGrain / graincn[p];

				float sPlantP = CropP[p] * 0.01 * sPlant / 0.4;
				PlantP[p] -= sPlantP;

				old_GrassN = plantn[p];
				plantn[p] -= (sLeaf_N+sStem_N+sGrain_N);
				if(plantn[p] < 0.0) plantn[p] = 0.0;
				Nratio = plantn[p] / old_GrassN;

				day_GrazeC += (sLeaf + sStem + sGrain);
				day_GrazeN += (sLeaf_N + sStem_N + sGrain_N);

				yr_GrazeGrain[p] += sGrain;
				yr_GrazeShoot[p] += (sLeaf+sStem);

			}//end of p loop

			//Grazed stub
			if(dead_food > 0.000001)
			{
				stub1_loss = stub_loss * stub1 / dead_food;
				stub2_loss = stub_loss * stub2 / dead_food;
				stub3_loss = stub_loss * stub3 / dead_food;
				stub1 -= stub1_loss;
				stub2 -= stub2_loss;
				stub3 -= stub3_loss;
			}
			else
			{
				stub1_loss = 0.0;
				stub2_loss = 0.0;
				stub3_loss = 0.0;
			}

			day_GrazeC += stub_loss;//kg C/ha/day
			day_GrazeN += (stub1_loss/rcnrvl +  stub2_loss/ rcnrl + stub3_loss / rcnrr);//kg N/ha/day
			yr_GrazeStub += stub_loss;	
			
			//Intaken C and N partitioned to animal C and N fluxes
			for(a=1; a<=5; a++) //1 dairy, 2 beef, 3 swine, 4 sheep, 5 horse, 6 poultry
			{
				day_graze_intake_C[a] = day_GrazeC * livestock_C_demand[a] / total_C_demand[oz];
				day_graze_intake_N[a] = day_GrazeN * livestock_C_demand[a] / total_C_demand[oz];

				day_graze_milk_C[a] = day_graze_intake_C[a] * Milk_C_fraction[a];
				day_graze_milk_N[a] = day_graze_intake_N[a] * Milk_N_fraction[a];
				day_graze_meat_C[a] = day_graze_intake_C[a] * Meat_C_fraction[a];
				day_graze_meat_N[a] = day_graze_intake_N[a] * Meat_N_fraction[a];

				day_graze_urine_C[a] = day_graze_intake_C[a] * Urine_C_fraction[a];
				day_graze_urine_N[a] = day_graze_intake_N[a] * Urine_N_fraction[a];
				day_graze_dung_C[a] = day_graze_intake_C[a] * Dung_C_fraction[a];
				day_graze_dung_N[a] = day_graze_intake_N[a] * Dung_N_fraction[a];

				day_graze_dung_P[a] = NPratio[a] * (day_graze_dung_N[a] + day_graze_urine_N[a]);//kg P/ha

				day_graze_enteric_CH4[a] = day_graze_intake_C[a] * Enteric_CH4_C_fraction[a];
				day_graze_enteric_N2O[a] = day_graze_intake_N[a] * Enteric_N2O_N_fraction[a];
				day_graze_respiration_CO2[a] = day_graze_intake_C[a] * Respiration_C_fraction[a];

				yr_graze_dung_C += day_graze_dung_C[a];
				yr_graze_dung_N += day_graze_dung_N[a];
				yr_graze_urine_C += day_graze_urine_C[a];
				yr_graze_urine_N += day_graze_urine_N[a];
				yr_graze_urine_P += 0.0;
				yr_graze_dung_P += day_graze_dung_P[a];

				yr_addmc += (day_graze_dung_C[a] + day_graze_urine_C[a]);
				//grazedN += day_graze_intake_N[a];
			}
			
			//incorporate urine and dung into soil
			float manure_add_N=0.0;
			for(a=1; a<=5; a++)
			{
				doc[1] += day_graze_urine_C[a];
				urea[1] += day_graze_urine_N[a];

				float TN = day_graze_dung_N[a];
				float TC = day_graze_dung_C[a];
			
				float NewTotN = TN;
				int FF = (int)(NewTotN / rcnh);

				float AddHumN = 0.5 * (float)FF * rcnh;
				float LeftTotN = NewTotN - AddHumN;
				AddHum = AddHumN * rcnh;

				float NewAddC = TC - AddHum;
				float NewAddCN = NewAddC / (LeftTotN + 0.0000001);

				alloc_manure_into_pools(NewAddCN, NewAddC, 1, &AddC1, &AddC2, &AddC3, &dInertC);

				manure_add_N = (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr + AddHum / rcnh + day_graze_urine_N[a]);
				day_inManureN += manure_add_N;
				yr_addmn += manure_add_N;

				rcvl[1] += AddC1;
				rcl[1] += AddC2;
				rcr[1] += AddC3;
				crhr[1] += AddHum;
				OrgP[1] += day_graze_dung_P[a];
				
			}
		}//end of if grazing period
   }//end of gra_num*/

   int ManureType=0, oz, i, a;
   float dung_CN, Ftt, NH3_emit;
   float C1, C2, C3, N1, N2, N3, urine1, urine2, urine3;
   float fresh_food, dead_food, total_food, food_demand, FoodDemand;
   float food_need1, food_need2, food_need3;
   float plant_loss[8], stub1_loss, stub2_loss, stub3_loss;
   float F_dung;
   float sLeaf, sStem, sGrain, sRoot, sPlant;
   float AddC1, AddC2, AddC3, dInertC, AddDOC=0.0;
   float old_GrassN, Nratio, sLeaf_N, sStem_N, sGrain_N;
   float AdditionFeed, FedC=0.0;//, IniFoodDemand=0.0, IniFreshFood, IniDeadFood;

   for ( oz = 1; oz <= gra_num; oz++ )
   {
	   int ExcretaFlag=0;
	   if(Excreta[oz]==2) ExcretaFlag = 1;//manure removal

		if ( jday >= jdgra1[oz] && jday <= jdgra2[oz] && (TotalHeads[oz]>0.0) && (hrs[oz]>0.0))//grazing period
		{
			grazFlag=1;
			H_dairy = AnimalHead[1][oz];
			H_beef = AnimalHead[2][oz];
			H_pig = AnimalHead[3][oz];			
			H_sheep = AnimalHead[4][oz];
			H_horse = AnimalHead[5][oz];
			H_hrs = hrs[oz];

			if(AddFeed[oz]>15.0) 
			{
				//ResidueFeed += (AddFeed[oz] - 15.0);
				AddFeed[oz] = 15.0;
			}

			AdditionFeed = AddFeed[oz] * (H_dairy+H_beef+H_pig+H_sheep+H_horse);

			//Feed available 
			fresh_food = 0.0;
			for(int i=1; i<=CropNumbers; i++)
			{
				fresh_food += (Grain_Wt[i] + Leaf_Wt[i] + Stem_Wt[i]); //kg C/ha
			}
			dead_food = stub1 + stub2 + stub3;
			total_food = fresh_food + dead_food + AdditionFeed;

			//Feed demand
			FoodDemand = total_C_demand[oz]; //kg C/ha/day
			food_demand = total_C_demand[oz]; //kg C/ha/day  //pulled from livestock library directory for animal type
			yr_GrazeDemandC += food_demand;

			//Feed consumption
			float total_grass_consum = 0.0, GrassCNT = 0.0, GPT=0.0;
			float fresh_grass_consume=0.0, stub_grass_consume=0.0, fresh_grass[8]={0.0,0.0};
			float consumed_grain[8]={0.0,0.0}, consumed_leaf[8]={0.0,0.0}, consumed_stem[8]={0.0,0.0};

			for(int i2=1; i2<=CropNumbers; i2++) GrassCNT += leafcn[i2];

			if(total_food > 0.0)
			{
				if(fresh_food>0.0) 
				{
					for(int i=1; i<=CropNumbers; i++) 
					{
						fresh_grass[i] = Grain_Wt[i] + Leaf_Wt[i] + Stem_Wt[i];
						GPT = fresh_grass[i] / fresh_food; 
					}
				}
			
				if(AdditionFeed>=food_demand)
				{
					FedC = food_demand;
					AdditionFeed -= food_demand;
					day_GrazeC += food_demand;
					day_GrazeN += (food_demand / FeedCN[oz]);
					//day_GrazeAddFeed = food_demand;
					food_demand = 0.0;
				}
				else
				{
					FedC = AdditionFeed;
					food_demand -= AdditionFeed;
					day_GrazeC += AdditionFeed;
					day_GrazeN += (AdditionFeed / FeedCN[oz]);
					//day_GrazeAddFeed = AdditionFeed;
					AdditionFeed = 0.0;
				}

				if(fresh_food>=food_demand) //enough fresh grass
				{
					fresh_grass_consume = food_demand;
					food_demand = 0.0;
					fresh_food -= fresh_grass_consume;
				}
				else
				{
					fresh_grass_consume = fresh_food;
					fresh_food = 0.0;
					food_demand -= fresh_grass_consume;
				}

				for(int i=1; i<=CropNumbers; i++)
				{
					if(fresh_grass[i]>0.0)
					{
						GrassProductivityFactor = GrazBiomass[oz];//sets the GrassProductivityFactor as a response of grazing activity to reduce aboveground productivity during grazing.
						consumed_grain[i] = fresh_grass_consume * GPT * (Grain_Wt[i] / fresh_grass[i]);
						consumed_leaf[i] = fresh_grass_consume * GPT * (Leaf_Wt[i] / fresh_grass[i]);
						consumed_stem[i] = fresh_grass_consume * GPT * (Stem_Wt[i] / fresh_grass[i]);
						Grain_Wt[i] -= consumed_grain[i];
						Leaf_Wt[i] -= consumed_leaf[i];
						Stem_Wt[i] -= consumed_stem[i];
					}
				}
				
				//////////////////////
				stub1_loss=0.0;
				stub2_loss=0.0;
				stub3_loss=0.0;
			
				if(food_demand>0.0&&dead_food>0.0) 
				{
					if(dead_food>=food_demand)
					{
						stub_grass_consume = food_demand;
						food_demand = 0.0;
						dead_food -= stub_grass_consume;
					}
					else
					{
						stub_grass_consume = dead_food;
						dead_food = 0.0;
						food_demand -= stub_grass_consume;
					}

					float stb = stub_grass_consume;
					if(stb>=stub1)
					{
						stb -= stub1;
						stub1_loss = stub1;
						stub1 = 0.0;
						 
					}
					else
					{
						stub1 -= stb;
						stub1_loss = stb;
						stb = 0.0;
					}

					if(stb>=stub2)
					{
						stb -= stub2;
						stub2_loss = stub2;
						stub2 = 0.0;
					}
					else
					{
						stub2 -= stb;
						stub2_loss = stb;
						stb = 0.0;
					}

					if(stb>=stub3)
					{
						stb -= stub3;
						stub3_loss = stub3;
						stub3 = 0.0;
					}
					else
					{
						stub3 -= stb;
						stub3_loss = stb;
						stb = 0.0;
					}
				}
			}
			else
			{
				fresh_grass_consume = 0.0;
				stub_grass_consume = 0.0;	
				stub1_loss=0.0;
				stub2_loss=0.0;
				stub3_loss=0.0;
			}

			total_grass_consum = fresh_grass_consume + stub_grass_consume;
			if(FoodDemand<=0.0) day_deficit = 1.0;
			else day_deficit = total_grass_consum / FoodDemand; //tracks if the feeding C intake rate is less than available supply

			//Grazed plant C
			for(int p=1; p<=CropNumbers; p++)
			{
				float GQI = base_leafcn[p];

				sPlant = consumed_grain[p] + consumed_leaf[p] + consumed_stem[p];
				sLeaf = consumed_leaf[p];
				sStem = consumed_stem[p];
				sGrain = consumed_grain[p];
				
				sLeaf_N = sLeaf / leafcn[p];
				sStem_N = sStem / stemcn[p];
				sGrain_N = sGrain / graincn[p];

				float sPlantP = plantP[p] * 0.01 * sPlant / 0.4;
				plantP[p] -= sPlantP;

				old_GrassN = plantn[p];
				plantn[p] -= (sLeaf_N+sStem_N+sGrain_N);
				if(plantn[p] < 0.0) plantn[p] = 0.0;

				LeafN[p] -= sLeaf_N;
				StemN[p] -= sStem_N;
				//RootN[p] -= sRoot_N;
				GrainN[p] -= sGrain_N;

				Nratio = plantn[p] / old_GrassN;

				day_GrazeC += (sLeaf + sStem + sGrain);
				day_GrazeN += (sLeaf_N + sStem_N + sGrain_N);

				yr_GrazeGrain[p] += sGrain;
				yr_GrazeShoot[p] += (sLeaf+sStem);

			}//end of p loop

			//Grazed stub
			day_GrazeC += stub_grass_consume;//kg C/ha/day
			day_GrazeN += (stub1_loss/rcnrvl +  stub2_loss/ rcnrl + stub3_loss / rcnrr);//kg N/ha/day
			yr_GrazeStub += (stub1_loss+stub2_loss+stub3_loss);	
				
			//Intaken C and N partitioned to animal C and N fluxes
			for(int ay=1; ay<=5; ay++) //1 dairy, 2 beef, 3 swine, 4 sheep, 5 horse, 6 poultry
			{
				day_graze_intake_C[ay] = day_GrazeC * livestock_C_demand[ay][oz] / total_C_demand[oz];
				day_graze_intake_N[ay] = day_GrazeN * livestock_C_demand[ay][oz] / total_C_demand[oz];

				day_graze_milk_C[ay] = day_graze_intake_C[ay] * Milk_C_fraction[ay];
				day_graze_milk_N[ay] = day_graze_intake_N[ay] * Milk_N_fraction[ay];
				day_graze_meat_C[ay] = day_graze_intake_C[ay] * Meat_C_fraction[ay];
				day_graze_meat_N[ay] = day_graze_intake_N[ay] * Meat_N_fraction[ay];

				day_graze_urine_C[ay] = day_graze_intake_C[ay] * Urine_C_fraction[ay]; // urine fraction from livestock values
				day_graze_urine_N[ay] = day_graze_intake_N[ay] * Urine_N_fraction[ay];
				day_graze_dung_C[ay] = day_graze_intake_C[ay] * Dung_C_fraction[ay];  //dung fraction from livestock values
				day_graze_dung_N[ay] = day_graze_intake_N[ay] * Dung_N_fraction[ay];

				day_graze_dung_P[ay] = NPratio[ay] * (day_graze_dung_N[ay] + day_graze_urine_N[ay]);//kg P/ha

				day_graze_enteric_CH4[ay] = day_graze_intake_C[ay] * Enteric_CH4_C_fraction[ay];
				day_graze_enteric_N2O[ay] = day_graze_intake_N[ay] * Enteric_N2O_N_fraction[ay];
				day_graze_respiration_CO2[ay] = day_graze_intake_C[ay] * Respiration_C_fraction[ay];

				yr_graze_dung_C += day_graze_dung_C[ay];
				yr_graze_dung_N += day_graze_dung_N[ay];
				yr_graze_urine_C += day_graze_urine_C[ay];
				yr_graze_urine_N += day_graze_urine_N[ay];
				yr_graze_urine_P += 0.0;
				yr_graze_dung_P += day_graze_dung_P[ay];

				yr_addmc += (day_graze_dung_C[ay] + day_graze_urine_C[ay]);
				day_addmc += (day_graze_dung_C[ay] + day_graze_urine_C[ay]);
				//grazedN += day_graze_intake_N[a];
			}
		
			//incorporate urine and dung into soil
			if(ExcretaFlag == 0)
			{
				float manure_add_N=0.0;
				for(int aw=1; aw<=5; aw++)
				{
					if((day_graze_urine_N[aw]+day_graze_dung_N[aw])>0.0)
					{
						float AddC1=0.0, AddC2=0.0, AddC3=0.0, dInertC=0.0, AddHum=0.0, AddDOC=0.0;

						doc[1] += day_graze_urine_C[aw];
						day_DOC_prod += day_graze_urine_C[aw];
						urea[1] += day_graze_urine_N[aw];

						float TN = day_graze_dung_N[aw];
						float TC = day_graze_dung_C[aw];
					
						float NewTotN = TN;
						float FF = NewTotN / rcnh;

						float AddHumN = 0.5 * FF * rcnh;
						float LeftTotN = NewTotN - AddHumN;
						AddHum = AddHumN * rcnh;

						float NewAddC = TC - AddHum;
						float NewAddCN = NewAddC / (LeftTotN + 0.0000001);

						alloc_manure_into_pools(NewAddCN, NewAddC, 1, &AddC1, &AddC2, &AddC3, &dInertC, &AddHum, &AddDOC);

						manure_add_N = (AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr + AddHum / rcnh + day_graze_urine_N[aw]);
						day_inManureN += manure_add_N;
						yr_addmn += manure_add_N;

						rcvl[1] += AddC1;
						rcl[1] += AddC2;
						rcr[1] += AddC3;
						crhr[1] += AddHum;
						doc[1] += AddDOC;
						OrgP[1] += day_graze_dung_P[aw];			
					}
				}
			}
			
		}//end of if grazing period
		if (jday < jdgra1[oz] || jday > jdgra2[oz])
		{
			GrassProductivityFactor = 1.0;
		}
   }//end of gra_num

/* Observed data from Donna Giltrap in New Zealand
	For cows:
	Daily consumption: 6 kg C/head/day, 0.3 kg N/head/day
	Total daily N deposit = 0.29 kg N/head/day
	Total daily C deposit = 1.943 kg C/cow

	For sheep:
	Daily consumption: 0.85 kg C/head/day, 0.0425 kg N/head/day
	Total daily N deposit = 0.04 kg/ewe
	Total daily C deposit = 0.268 kg/ewe

	In both cases the nitrogen in the dung is 40% of the total N, the C/N
	ratio for dung is 16 and the C/N ratio for urine is 0.5.*/	

   return(0);
}

float class_model::cutting()
{
	int oz, i;
	float LeftGrass, Rr;
	float day_CutGrain=0.0, day_CutLeaf=0.0, day_CutStem=0.0, day_CutRoot=0.0;
	float day_CutGrainN=0.0, day_CutLeafN=0.0, day_CutStemN=0.0, day_CutRootN=0.0;

	
	
	//All cut materials will be taken out from the field
	for ( oz = 1; oz <= cut_num; oz++ )
	{
		
		if ( jday==jdcut[oz])
		{
			currentCut+=1;//oz
			for(int i=1; i<=3; i++)//only crops 1, 2 and 3 are cut
			{
			
				if(CutPart[oz]==0)//nothing cut
				{
				}
				else if(CutPart[oz]==1)//fruit cut
				{
					day_CutGrain = Grain_Wt[i] * CutFraction[oz];
					Grain_Wt[i] -= day_CutGrain;
					
					day_CutGrainN = GrainN[i] * CutFraction[oz];
					GrainN[i] -= day_CutGrainN;
				}
				else if(CutPart[oz]==2)//leaf cut
				{
					day_CutLeaf = Leaf_Wt[i] * CutFraction[oz];					
					Leaf_Wt[i] -= day_CutLeaf;

					day_CutLeafN = LeafN[i] * CutFraction[oz];
					LeafN[i] -= day_CutLeafN;	
					CropHeight[i] *= CutFraction[oz];
				}
				else if(CutPart[oz]==3)//stem cut
				{
					day_CutStem = Stem_Wt[i] * CutFraction[oz];
					Stem_Wt[i] -= day_CutStem;
					
					day_CutStemN = StemN[i] * CutFraction[oz];
					StemN[i] -= day_CutStemN;	
					CropHeight[i] *= CutFraction[oz];
				}
				else if(CutPart[oz]==4)//root cut
				{
					day_CutRoot = Root_Wt[i] * CutFraction[oz];
					Root_Wt[i] -= day_CutRoot;

					day_CutRootN = RootN[i] * CutFraction[oz];
					RootN[i] -= day_CutRootN;
				
				}
				else if(CutPart[oz]==5)//fruit+leaf cut
				{
					day_CutGrain = Grain_Wt[i] * CutFraction[oz];
					Grain_Wt[i] -= day_CutGrain;
					day_CutLeaf = Leaf_Wt[i] * CutFraction[oz];
					Leaf_Wt[i] -= day_CutLeaf;

					day_CutGrainN = GrainN[i] * CutFraction[oz];
					GrainN[i] -= day_CutGrainN;
					day_CutLeafN = LeafN[i] * CutFraction[oz];
					LeafN[i] -= day_CutLeafN;						
				}
				else if(CutPart[oz]==6)//grain+leaf+stem cut
				{
					day_CutGrain = Grain_Wt[i] * CutFraction[oz];
					Grain_Wt[i] -= day_CutGrain;
					day_CutLeaf = Leaf_Wt[i] * CutFraction[oz];
					Leaf_Wt[i] -= day_CutLeaf;
					day_CutStem = Stem_Wt[i] * CutFraction[oz];
					Stem_Wt[i] -= day_CutStem;

					day_CutGrainN = GrainN[i] * CutFraction[oz];
					GrainN[i] -= day_CutGrainN;
					day_CutLeafN = LeafN[i] * CutFraction[oz];
					LeafN[i] -= day_CutLeafN;
					day_CutStemN = StemN[i] * CutFraction[oz];
					StemN[i] -= day_CutStemN;

					CropHeight[i] *= CutFraction[oz];

				}
				else if(CutPart[oz]==7)//grain+leaf+stem+root cut
				{
					day_CutGrain = Grain_Wt[i] * CutFraction[oz];
					Grain_Wt[i] -= day_CutGrain;
					day_CutLeaf = Leaf_Wt[i] * CutFraction[oz];
					Leaf_Wt[i] -= day_CutLeaf;
					day_CutStem = Stem_Wt[i] * CutFraction[oz];
					Stem_Wt[i] -= day_CutStem;
					day_CutRoot = Root_Wt[i] * CutFraction[oz];
					Root_Wt[i] -= day_CutRoot;

					day_CutGrainN = GrainN[i] * CutFraction[oz];
					GrainN[i] -= day_CutGrainN;
					day_CutLeafN = LeafN[i] * CutFraction[oz];
					LeafN[i] -= day_CutLeafN;
					day_CutStemN = StemN[i] * CutFraction[oz];
					StemN[i] -= day_CutStemN;
					day_CutRootN = RootN[i] * CutFraction[oz];
					RootN[i] -= day_CutRootN;

					CropHeight[i] *= CutFraction[oz];
					
				}
				else if(CutPart[oz]==8)//leaf+stem cut
				{
					day_CutLeaf = Leaf_Wt[i] * CutFraction[oz];
					Leaf_Wt[i] -= day_CutLeaf;
					day_CutStem = Stem_Wt[i] * CutFraction[oz];
					Stem_Wt[i] -= day_CutStem;

					day_CutLeafN = LeafN[i] * CutFraction[oz];
					LeafN[i] -= day_CutLeafN;
					day_CutStemN = StemN[i] * CutFraction[oz];
					StemN[i] -= day_CutStemN;	

					CropHeight[i] *= CutFraction[oz];
				}

				DayGrassCut += day_CutGrain+day_CutLeaf+day_CutStem+day_CutRoot;	
				DayGrassCut_C[i] = day_CutGrain + day_CutLeaf + day_CutStem + day_CutRoot;
				DayGrassCut_N[i] = day_CutGrainN + day_CutLeafN + day_CutStemN + day_CutRootN;
				eachGrassCut[i][oz]= day_CutGrain + day_CutLeaf + day_CutStem + day_CutRoot;
				

	/*			LeftGrass = TotalGrass - DayGrassCut;
				if(TotalGrass==0.0) Rr = 0.0;
				else Rr = LeftGrass / TotalGrass;

				day_CutGrain = Grain_Wt[i] *(1.0-Rr);
				day_CutLeaf = Leaf_Wt[i] *(1.0-Rr);
				day_CutStem = Stem_Wt[i] *(1.0-Rr);
				day_CutRoot = 0.0;//Root_Wt[i] *(1.0-Rr);
				remain_root = Root_Wt[i];			

				Grain_Wt[i] *= Rr;
				Leaf_Wt[i] *= Rr;
				Stem_Wt[i] *= Rr;
				//Root_Wt[i] *= Rr;*/

				plantn[i] -= (day_CutGrainN+day_CutLeafN+day_CutStemN+day_CutRootN);
				plantn[i]=LeafN[i]+StemN[i]+RootN[i]+GrainN[i]+PodN[i];
				yr_CutGrain[i] += day_CutGrain;
				yr_CutLeaf[i] += day_CutLeaf;
				yr_CutStem[i] += day_CutStem;
				yr_CutRoot[i] += day_CutRoot;

				if(LandUse==6) stem_age = 0;
			}
		}
		else
		{
			day_CutGrain = 0.0;
			day_CutLeaf = 0.0;
			day_CutStem = 0.0;
			day_CutRoot = 0.0;
		}

	}
	return(0);
}

float class_model::PlasticCover()
{
    int oz;

	if(plastic_num > 0)
	{
		for (oz=1; oz<=plastic_num; oz++)
		{
			if ( jday == jdplastic1[oz])//start film mulching
			{
				plastic_flag = 1;
				FilmEffect = 1.0 * (float)log(FilmCoverF[oz] + 1.0);
				if(FilmEffect>1.0) FilmEffect = 1.0;
				FilmCoverFraction = FilmCoverF[oz];
			}

			if ( jday == jdplastic2[oz])//end film mulching
			{
				plastic_flag = 0;
				FilmEffect = 0.0;
				FilmCoverFraction = 0.0;
			}
		}		
	}
	else
	{
		plastic_flag = 0;
		FilmEffect = 0.0;
		FilmCoverFraction = 0.0;
	}


    return( 0 );
}


void class_model::day_flooding(int MODE)
{
 	if(day_WT>0.0)//||flood_flag==0)
	{
		flood_flag = 1;
		FloodingDays++;
		if(drain_flag>0) drain_flag--;
		
	}
	else
	{
		if(FloodingDays>0) drain_flag = 5;

		if(flood_flag<0)
		{
			flood_flag++;
			if(flood_flag>0) flood_flag = 0;
		}
		//flood_flag = 0;
		FloodingDays = 0;	
	}
	
}

void class_model::tree_leaves_fall()
{
    float leaf_falln, leaf_fallc, AddC, AddCN;
	float AddC1, AddC2, AddC3, dInertC;
    int   l, oz=0;

    if ( crop[1] == 17 )
    {
	leaf_falln = day_nup[1] * leaf[1];
	leaf_fallc = leaf_falln * leafcn[1];
    AddC = leaf_fallc;
	AddCN = leafcn[1];

	/* #22-1, Add new Litter into soil litter pools */
	alloc_litter_into_pools(&AddCN, &AddC, oz, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);

	for ( l = 1; l <= 2; l++ )
	{
	    rcvl[l] += (AddC1 * 0.5);
	    rcl[l] += (AddC2 * 0.5);
	    rcr[l] += (AddC3 * 0.5);
	}

	yr_addleafc = yr_addleafc + AddC1 +
			       AddC2 + AddC3;
	yr_addleafn = yr_addleafn +
			       AddC1 / rcnrvl +
			       AddC2 / rcnrl +
			       AddC3 / rcnrr;
	AddC1 = 0.0;
	AddC2 = 0.0;
	AddC3 = 0.0;

	/* leaf_falln = 0;
	leaf_fallc = 0; */

    }
}

float class_model::tilling(int* tilq_p, float *CRB1, float* CRB2,
		float *newh, float till_fact)//float* rhrl_p, 
{
    int    oz, l, tilq, cwc;
    float rcvl_xyz=0.0, rcl_xyz=0.0, rcr_xyz=0.0, crb1_xyz=0.0, inertC_xyz=0.0;
    float crb2_xyz=0.0, crh1_xyz=0.0, crh2_xyz=0.0,dp_xyz=0.0, newh_xyz=0.0;
    float tc_xyz=0.0, no3_xyz=0.0, nh4_xyz=0.0, clayn_xyz=0.0;
    float urea_xyz=0.0, nh3_xyz=0.0, NH4HCO3_xyz=0.0, OrgP_xyz=0.0, AdsP_xyz=0.0, LabP_xyz=0.0;	
	float AddC, AddCN, AddC1, AddC2, AddC3, dInertC, harvest_AddC;

   
    tilq = *tilq_p;
    for (oz=1; oz<=til_num; oz++)
    {
		if (jday==jdtil[oz])
		{
			//terminating crop
			if(crop_terminator==1)//only if terminating crop....i.e. alfalfa. Root C is going to be added to soil pools immediately on this action. Normally Root C not added to soil pools till day 366.
			{
				
				for(cwc=1; cwc<=CropNumbers; cwc++)
				{
					if(Root_Wt[cwc]>0.0)
					{
						AddC = Root_Wt[cwc];// AddC now holds Root C  
						AddCN = rootcn[cwc];//Root C:N now is AddCN
						alloc_litter_into_pools(&AddCN, &AddC, oz, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4); //allocating rootC into various litter soil pools (very labile, labile and resistant litter)
						float AddP = plantP[cwc] * 0.01 * AddC / 0.4;

						for ( l = 1; l <= q; l++ )//should be based on root density a bit more. 
						{
							if ( l >= 1 && l <= 3 ) //3 layers (1-3 soil layers)  adding to soil pools rcvl, rcl, rcr from residue C ( C1, C2, C3) 0.5 X 3 layer = 1.5/3.0 of total C added. 
							{
								rcvl[l] += AddC1 * 0.5 / 3.0;//very labile soil pool gets 0.5/3.0 of the rootC that alloc_litter function determined was very labile for layers 1-3
								rcl[l] += AddC2 * 0.5 / 3.0;//labile soil pool gets the 0.5/3.0 rootC that alloc_litter function determined was labile
								rcr[l] += AddC3 * 0.5 / 3.0;//resistant soil pool gets the 0.5/3.0 rootC that alloc_litter function determined was resistant
								inert_C[l] += dInertC * 0.5 / 3.0;//day_inert_C
								OrgP[l] += AddP * 0.5 / 3.0;
							}
							if ( l >= 4 && l <= 6 ) // 3 (4-6) layers adding  0.4 X 3 layers = 1.2/3.0  (2.7/3.0 with previous loop). to soil pools rcvl, rcl, rcr
							{
								rcvl[l] += AddC1 * 0.4 / 3.0;//very labile soil pool gets 0.4/3.0 of the rootC that alloc_litter function determined was very labile for layers 4-6
								rcl[l] += AddC2 * 0.4 / 3.0;
								rcr[l] += AddC3 * 0.4 / 3.0;
								inert_C[l] += dInertC * 0.4 / 3.0;//day_inert_C
								OrgP[l] += AddP * 0.4 / 3.0;
							}
							if ( l >= 7 && l <= 9 ) //loop layers 7-9 addiion 0.1 X 3 layers = 0.3/3.0 (3.0/3.0 of total C with previous loop) to soil pools rcvl, rcl, rcr
							{
								rcvl[l] += AddC1 * 0.1 / 3.0;//very labile soil pool gets 0.1/3.0 of the rootC that alloc_litter function determined was very labile for layers 7-9
								rcl[l] += AddC2 * 0.1 / 3.0;
								rcr[l] += AddC3 * 0.1 / 3.0;
								inert_C[l] += dInertC * 0.1 / 3.0;//day_inert_C
								OrgP[l] += AddP * 0.1 / 3.0;
							}
						}

						float AddToSoilC, AddToSoilN;
						AddToSoilC = AddC1 + AddC2 + AddC3 + dInertC;
						AddToSoilN = AddC1/rcnrvl + AddC2/rcnrl + AddC3/rcnrr;

						day_addC += AddToSoilC; //track for output day added litter C to soil
						yr_addrc += AddToSoilC;//track for output year added litter C to soil
						day_addrn += AddToSoilN;//track for output day added litter N to soil
						yr_addrp += AddP;// track for output day added litter P to soil

						//float RootAddC = AddC1+AddC2+AddC3;
						//harvest_AddC += RootAddC;

						//reset the AddC fractions from alloc_litter_into_pools function
						AddC1 = 0.0;
						AddC2 = 0.0;
						AddC3 = 0.0;

						//reinitialize the crop fractions to zero after tillage.
						YrG_root[cwc] = Root_Wt[cwc];//track Roots new Brian
						//YrG_grain[cwc] = Grain_Wt[cwc];
						//YrG_leaf[cwc] = Leaf_Wt[cwc];
						//YrG_stem[cwc] = Stem_Wt[cwc];
						Root_Wt[cwc]=0.0;
						RootN[cwc] = 0.0;
						Grain_Wt[cwc]=0.0;
						Leaf_Wt[cwc]=0.0;
						Stem_Wt[cwc]=0.0;
						Pod_Wt[cwc] = 0.0;
						Root_ExuC[cwc] = 0.0;
						Root_ExuN[cwc] = 0.0;
						PerennialFlag[cwc]=0;
						crop_terminator=0;
						CropHeight[cwc] = 0.001;
						if(crop[cwc]==57)//specific to canola.
						{
						
						
						crop_flag[cwc]=0;
						crop_days[cwc]=0;
						TDD[cwc]=0.0;
						PGI[cwc]=0.0;
						maturity_flag[cwc]=0;
						seed[cwc]=0;
						//HarvestDay[cwc]=1;
					//	cropHarvestDay[cwc]=90;
					//	grow_days[cwc]=90;
//						maxmn[cwc]=0.0;
						perRegrow[cwc]=0;
						vernal[cwc]=0;
						plantn[cwc]=0;

						}
						else
						{
						crop[cwc] = 0;
						seed[cwc]=0;
						jdseed[cwc] = 0; //Brian Nov 2021 needed to add this to ensure if another crop planted after the perennial that it would seed at the appropriate date.
						maturity_flag[cwc]=1;
						crop_days[cwc]=0;
						crop_flag[cwc]=0;
						//CropNumbers = CropNumbers-1;//added to ensure after tillage crop termination that crops no longer grow.

						

					//	perRegrow[cwc] = 0;
					//	vernal[cwc] = 0;
					//	plantn[cwc] = 0;
						}
					}
				}
				

			}


			///////////////////////////////////////////////////////////////// for regular tillage
			till_flag = 1;
			
			tilld = til_dept[oz];//set tilld variable to which tillage implement. 

			tilq = (int)(til_dept[oz] / h[1])+1;//figure how many total layers are affected to the tillage depth. .
			tilq = min(q, max(0, tilq));
			
			if(tilq>0) //start loop by initializing variables.
			{				
				rcvl_xyz=0.0;
				rcl_xyz=0.0;
				rcr_xyz=0.0;
				crb1_xyz=0.0;
				crb2_xyz=0.0;
				crh1_xyz=0.0;
				crh2_xyz=0.0;
				dp_xyz=0.0;
				inertC_xyz=0.0;
				newh_xyz=0.0;
				tc_xyz=0.0;
				no3_xyz=0.0;
				nh4_xyz=0.0;
				clayn_xyz=0.0;
				urea_xyz=0.0;
				nh3_xyz=0.0;
				NH4HCO3_xyz=0.0;
				OrgP_xyz=0.0;
				AdsP_xyz=0.0;
				LabP_xyz=0.0;

				for ( l = 1; l <= tilq; l++ ) //initiazes all of the cummulative temporary soil layer variables to the pool constituents up to the tillage depth as a single cummulative value..
				{
					rcvl_xyz += rcvl[l];
					rcl_xyz += rcl[l];
					rcr_xyz += rcr[l];
					crb1_xyz += CRB1[l];
					crb2_xyz += CRB2[l];
					crh1_xyz += crhl[l];
					crh2_xyz += crhr[l];
					dp_xyz += dphum[l];
					inertC_xyz += inert_C[l];
					newh_xyz += newh[l];
					tc_xyz += doc[l];
					no3_xyz += no3[l];
					nh4_xyz += nh4[l];
					clayn_xyz += clay_nh4[l];
					urea_xyz += urea[l];
					nh3_xyz += nh3[l];
					NH4HCO3_xyz += NH4HCO3[l];
					OrgP_xyz += OrgP[l];
					AdsP_xyz += AdsP[l];
					LabP_xyz += LabP[l];
				}

				if ((stub1+stub2+stub3) > 0.0 )
				{


					float qst = 0.0f;
					if (tilq == 1)            qst = 0.5f;   // 50% remains surface
					else if (tilq > 1 && tilq < 5) qst = 0.0f;
					else                       qst = 0.0f;

					float addStubC = (1.0f - qst) * (stub1 + stub2 + stub3);
					float addStubN = (1.0f - qst) * (stub1 / rcnrvl + stub2 / rcnrl + stub3 / rcnrr);

					// Add to cumulative counters once, using the soil-entering fraction
					yr_addtc += addStubC;   day_addC += addStubC;
					yr_addtn += addStubN;   day_inStubN += addStubN;

					//yr_addtc += (stub1 + stub2 + stub3);
					//yr_addtn += (stub1 / rcnrvl + stub2 / rcnrl + stub3 / rcnrr);
					//day_addC += (stub1 + stub2 + stub3);
					//day_inStubN += (stub1 / rcnrvl + stub2 / rcnrl + stub3 / rcnrr);//stubble input seems wrong at times..maybe due to dynmaic biomass fraction?

					if(til_method[oz]==6)//buried carbon puts stub1-stub2-stub3 into 3 soil litter pools
					{
						rcvl[tilq+1] += stub1*0.5;
						rcl[tilq+1] += stub2*0.5;
						rcr[tilq+1] += stub3*0.5;
						OrgP[tilq+1] += stubP*0.5;

						rcvl[1]+= stub1 * 0.5;
							rcl[1]+= stub2 * 0.5;
							rcr[1]+= stub3 * 0.5;
							OrgP[1]+= stubP * 0.5;
						
							


						stub1 = 0.0;//stubble1 reduced to 0 content.
						stub2 = 0.0;//stubble2 reduced to 0 content.
						stub3 = 0.0;//stubble3 reduced to 0 content.
						stubP = 0.0;
					}
					else
					{
						if(tilq==1)//only mulching since its one layer so half of the stub is allocated to the top layer
						{
							float qst = 0.5;
							rcvl_xyz += ((1.0-qst)*stub1);
							rcl_xyz += ((1.0-qst)*stub2);
							rcr_xyz +=((1.0-qst)*stub3);
							OrgP_xyz += ((1.0-qst)*stubP);

							stub1 *= qst;
							stub2 *= qst;
							stub3 *= qst;
							stubP *= qst;

							

						}
						else if(tilq>1&&tilq<5) //if till layers is between 1 and 5 then 
						{
							float qst = 0.0;
							rcvl_xyz += ((1.0-qst)*stub1); //verylabile cumulative (prior C levels + new addtion) gets 100% of new very labile stubble
							rcl_xyz += ((1.0-qst)*stub2); //labile cummulative (prior C levels + new addition) gets 100% of labile stubble
							rcr_xyz +=((1.0-qst)*stub3); // resistant cummulative (prior C levels + new addition) gets 100% resistant stubble
							OrgP_xyz += ((1.0-qst)*stubP);

							stub1 *= qst; //stubble1 reduced to 0 content.
							stub2 *= qst; //stubble2 reduced to 0 content.
							stub3 *= qst;//stubble3 reduced to 0 content.
							stubP *= qst;

							
						}
						else // else for deeper tillages
						{
							rcvl_xyz += stub1; //verylabile cumulative (prior C levels + new addtion) gets 100% of new very labile stubble
							rcl_xyz += stub2;//labile cummulative (prior C levels + new addition) gets 100% of labile stubble
							rcr_xyz += stub3;// resistant cummulative (prior C levels + new addition) gets 100% resistant stubble
							OrgP_xyz += stubP;

							

							stub1 = 0.0;//stubble1 reduced to 0 content.
							stub2 = 0.0;//stubble2 reduced to 0 content.
							stub3 = 0.0;//stubble3 reduced to 0 content.
							stubP = 0.0;
						}
					}
					
					//stub1 = 0.0;
					//stub2 = 0.0;
					//stub3 = 0.0;
					//stubP = 0.0;
				}


				/*
				///////////////////////////default method
					//reallocate previous existing content + new stubble additions across layers as a equivalent faction

				rcvl[1] = rcvl_xyz / tilq; //very labile[layer[1] gets total cumulative very labile / number of tillage layers 
				rcl[1] = rcl_xyz / tilq;
				rcr[1] = rcr_xyz / tilq;
				CRB1[1] = crb1_xyz / tilq;
				CRB2[1] = crb2_xyz / tilq;
				crhl[1] = crh1_xyz / tilq;
				crhr[1] = crh2_xyz / tilq;
				dphum[1] = dp_xyz / tilq;
				inert_C[1] = inertC_xyz / tilq;
				newh[1] = newh_xyz / tilq;
				doc[1] = tc_xyz / tilq;
				no3[1] = no3_xyz / (float)tilq;
				nh4[1] = nh4_xyz / tilq;
				nh3[1] = nh3_xyz / tilq;
				urea[1] = urea_xyz / tilq;
				NH4HCO3[1] = NH4HCO3_xyz / tilq;
				clay_nh4[1] = clayn_xyz / tilq;
				OrgP[1] = OrgP_xyz / tilq;
				AdsP[1] = AdsP_xyz / tilq;
				LabP[1] = LabP_xyz / tilq;

				ocini[1] = CRB1[1] + CRB2[1] + crhl[1] + crhr[1];

				float CFT = 0.0;// 0.0001*air_temp;
				if (CFT < 0.0) CFT = 0.0;
				for (l = 1; l <= tilq; l++)//for rest of the layers in tillage affected layers get the same proportion of total consitutients (previous + new) as the just calculated layer 1 above.
				{
					rcvl[l] = rcvl[1];
					rcl[l] = rcl[1];
					rcr[l] = rcr[1];
					CRB1[l] = CRB1[1];
					CRB2[l] = CRB2[1];
					crhl[l] = crhl[1];
					crhr[l] = crhr[1];
					dphum[l] = dphum[1];
					inert_C[l] = inert_C[1];
					newh[l] = newh[1];
					doc[l] = doc[1];
					no3[l] = no3[1];
					nh4[l] = nh4[1];
					nh3[l] = nh3[1];
					urea[l] = urea[1];
					NH4HCO3[l] = NH4HCO3[1];
					clay_nh4[l] = clay_nh4[1];
					ocini[l] = ocini[1];
					OrgP[l] = OrgP[1];
					AdsP[l] = AdsP[1];
					LabP[l] = LabP[1];

					float dHumus = dphum[l] * CFT;
					dphum[l] -= dHumus;
					crhr[l] += dHumus;
				}
				*/
				//end default method.....
			 
				
				//Code to test flipping the soil for moldboard plough. Needs work. 
				
				if (til_method[oz] != 6)//if not burried litter option
				{

					rcvl[1] = rcvl_xyz / tilq; //very labile[layer[1] gets total cumulative very labile / number of tillage layers 
					rcl[1] = rcl_xyz / tilq;
					rcr[1] = rcr_xyz / tilq;
					CRB1[1] = crb1_xyz / tilq;
					CRB2[1] = crb2_xyz / tilq;
					crhl[1] = crh1_xyz / tilq;
					crhr[1] = crh2_xyz / tilq;
					dphum[1] = dp_xyz / tilq;
					inert_C[1] = inertC_xyz / tilq;
					newh[1] = newh_xyz / tilq;
					doc[1] = tc_xyz / tilq;
					no3[1] = no3_xyz / (float)tilq;
					nh4[1] = nh4_xyz / tilq;
					nh3[1] = nh3_xyz / tilq;
					urea[1] = urea_xyz / tilq;
					NH4HCO3[1] = NH4HCO3_xyz / tilq;
					clay_nh4[1] = clayn_xyz / tilq;
					OrgP[1] = OrgP_xyz / tilq;
					AdsP[1] = AdsP_xyz / tilq;
					LabP[1] = LabP_xyz / tilq;

					ocini[1] = CRB1[1] + CRB2[1] + crhl[1] + crhr[1];

					float CFT = 0.0;// 0.0001*air_temp;
					if (CFT < 0.0) CFT = 0.0;
					for (l = 1; l <= tilq; l++)//for rest of the layers in tillage affected layers get the same proportion of total consitutients (previous + new) as the just calculated layer 1 above.
					{
						rcvl[l] = rcvl[1];
						rcl[l] = rcl[1];
						rcr[l] = rcr[1];
						CRB1[l] = CRB1[1];
						CRB2[l] = CRB2[1];
						crhl[l] = crhl[1];
						crhr[l] = crhr[1];
						dphum[l] = dphum[1];
						inert_C[l] = inert_C[1];
						newh[l] = newh[1];
						doc[l] = doc[1];
						no3[l] = no3[1];
						nh4[l] = nh4[1];
						nh3[l] = nh3[1];
						urea[l] = urea[1];
						NH4HCO3[l] = NH4HCO3[1];
						clay_nh4[l] = clay_nh4[1];
						ocini[l] = ocini[1];
						OrgP[l] = OrgP[1];
						AdsP[l] = AdsP[1];
						LabP[l] = LabP[1];

						float dHumus = dphum[l] * CFT;
						if (dHumus > 0.0)
						{
							float blah;
							blah = 1.0;

						}
						dphum[l] -= dHumus;
						crhr[l] += dHumus;
					}
				}





				
				else  //inversion flipping method for option 6 (creating a layer array to hold info)
				{
					
					// Create temporary arrays to hold the values
					float temp_rcvl[30];
					float temp_rcl[30];
					float temp_rcr[30];
					float temp_CRB1[30];
					float temp_CRB2[30];
					float temp_crhl[30];
					float temp_crhr[30];
					float temp_dphum[30];
					float temp_inert_C[30];
					float temp_newh[30];
					float temp_doc[30];
					float temp_no3[30];
					float temp_nh4[30];
					float temp_nh3[30];
					float temp_urea[30];
					float temp_NH4HCO3[30];
					float temp_clay_nh4[30];
					float temp_ocini[30];
					float temp_OrgP[30];
					float temp_AdsP[30];
					float temp_LabP[30];

					// First, store the original values in temporary arrays
					for (int i = 1; i <= tilq; i++) 
					{

						if (i <=2)//siphoning off  0.5% of the organic matterial in layers 1 + 2 for deposition into  tilq+1 layer under Burried Tillage option.
						{
							float fractionSiphon;
							fractionSiphon = 0.995; 

							temp_rcvl[i] = rcvl[i]* fractionSiphon;
							temp_rcl[i] = rcl[i] * fractionSiphon;
							temp_rcr[i] = rcr[i] * fractionSiphon;
							temp_CRB1[i] = CRB1[i] * fractionSiphon;
							temp_CRB2[i] = CRB2[i] * fractionSiphon;
							temp_crhl[i] = crhl[i] * fractionSiphon;
							temp_crhr[i] = crhr[i] * fractionSiphon;
							temp_dphum[i] = dphum[i] * fractionSiphon;
							temp_inert_C[i] = inert_C[i] * fractionSiphon;
							temp_newh[i] = newh[i] * fractionSiphon;
							temp_doc[i] = doc[i] * fractionSiphon;
							temp_no3[i] = no3[i] * fractionSiphon;
							temp_nh4[i] = nh4[i] * fractionSiphon;
							temp_nh3[i] = nh3[i] * fractionSiphon;
							temp_urea[i] = urea[i] * fractionSiphon;
							temp_NH4HCO3[i] = NH4HCO3[i] * fractionSiphon;
							temp_clay_nh4[i] = clay_nh4[i] * fractionSiphon;
							temp_ocini[i] = temp_CRB1[i] + temp_CRB2[i] + temp_crhl[i] + temp_crhr[i];
							temp_OrgP[i] = OrgP[i] * fractionSiphon;
							temp_AdsP[i] = AdsP[i] * fractionSiphon;
							temp_LabP[i] = LabP[i] * fractionSiphon;
						}
						else // else just put the full amount of each nutrient variable into a temporary variable
						{
							temp_rcvl[i] = rcvl[i];
							temp_rcl[i] = rcl[i];
							temp_rcr[i] = rcr[i];
							temp_CRB1[i] = CRB1[i];
							temp_CRB2[i] = CRB2[i];
							temp_crhl[i] = crhl[i];
							temp_crhr[i] = crhr[i];
							temp_dphum[i] = dphum[i];
							temp_inert_C[i] = inert_C[i];
							temp_newh[i] = newh[i];
							temp_doc[i] = doc[i];
							temp_no3[i] = no3[i];
							temp_nh4[i] = nh4[i];
							temp_nh3[i] = nh3[i];
							temp_urea[i] = urea[i];
							temp_NH4HCO3[i] = NH4HCO3[i];
							temp_clay_nh4[i] = clay_nh4[i];
							temp_ocini[i] = temp_CRB1[i] + temp_CRB2[i] + temp_crhl[i] + temp_crhr[i];
							temp_OrgP[i] = OrgP[i];
							temp_AdsP[i] = AdsP[i];
							temp_LabP[i] = LabP[i];

						}
					}


					// Now, transpose the values from the temporary arrays in reverse order
					int belowTill, layer2BelowTill;
					belowTill = tilq + 1;
					layer2BelowTill = tilq + 2;


					for (l = 1; l <= tilq; l++) 
					{
						int reverseIndex = tilq - l + 1; // Calculate the reverse index
						//reverseIndex = l;

						if (l <= 2)//repurpose the top two layers to the layer below plough layer
						{
							float fractionSiphon;
							fractionSiphon = 0.005;
							rcvl[tilq + l] += rcvl[l] * fractionSiphon;
							rcl[tilq + l] += rcl[l] * fractionSiphon;
							rcr[tilq + l] += rcr[l] * fractionSiphon;
							CRB1[tilq + l] += CRB1[l] * fractionSiphon;
							CRB2[tilq + l] += CRB2[l] * fractionSiphon;
							crhl[tilq + l] += crhl[l] * fractionSiphon;
							crhr[tilq + l] += crhr[l] * fractionSiphon;
							dphum[tilq + l] += dphum[l] * fractionSiphon;
							inert_C[tilq + l] += inert_C[l] * fractionSiphon;
							newh[tilq + l] += newh[l] * fractionSiphon;
							doc[tilq + l] += doc[l] * fractionSiphon;
							no3[tilq + l] += no3[l] * fractionSiphon;
							nh4[tilq + l] += nh4[l] * fractionSiphon;
							nh3[tilq + l] += nh3[l] * fractionSiphon;
							urea[tilq + l] += urea[l] * fractionSiphon;
							NH4HCO3[tilq + l] += NH4HCO3[l] * fractionSiphon;
							clay_nh4[tilq + l] += clay_nh4[l] * fractionSiphon;
							ocini[tilq + l] = CRB1[tilq + l] + CRB2[tilq + l] + crhl[tilq + l] + crhr[tilq + l];
							OrgP[tilq + l] += OrgP[l] * fractionSiphon;
							AdsP[tilq + l] += AdsP[l] * fractionSiphon;
							LabP[tilq + l] += LabP[l] * fractionSiphon;
						}


						//invert the soil layers.....

						rcvl[l] = temp_rcvl[reverseIndex];
						rcl[l] = temp_rcl[reverseIndex];
						rcr[l] = temp_rcr[reverseIndex];
						CRB1[l] = temp_CRB1[reverseIndex];
						CRB2[l] = temp_CRB2[reverseIndex];
						crhl[l] = temp_crhl[reverseIndex];
						crhr[l] = temp_crhr[reverseIndex];
						dphum[l] = temp_dphum[reverseIndex];
						inert_C[l] = temp_inert_C[reverseIndex];
						newh[l] = temp_newh[reverseIndex];
						doc[l] = temp_doc[reverseIndex];
						no3[l] = temp_no3[reverseIndex];
						nh4[l] = temp_nh4[reverseIndex];
						nh3[l] = temp_nh3[reverseIndex];
						urea[l] = temp_urea[reverseIndex];
						NH4HCO3[l] = temp_NH4HCO3[reverseIndex];
						clay_nh4[l] = temp_clay_nh4[reverseIndex];
						ocini[l] = temp_ocini[reverseIndex];
						OrgP[l] = temp_OrgP[reverseIndex];
						AdsP[l] = temp_AdsP[reverseIndex];
						LabP[l] = temp_LabP[reverseIndex];

						
						
					}
					
					// This section added mixing to the burried layer tillage but it's been turned off....

					/*
					//also add mixing to moldboard. 
					rcvl_xyz = 0.0;
					rcl_xyz = 0.0;
					rcr_xyz = 0.0;
					crb1_xyz = 0.0;
					crb2_xyz = 0.0;
					crh1_xyz = 0.0;
					crh2_xyz = 0.0;
					dp_xyz = 0.0;
					inertC_xyz = 0.0;
					newh_xyz = 0.0;
					tc_xyz = 0.0;
					no3_xyz = 0.0;
					nh4_xyz = 0.0;
					clayn_xyz = 0.0;
					urea_xyz = 0.0;
					nh3_xyz = 0.0;
					NH4HCO3_xyz = 0.0;
					OrgP_xyz = 0.0;
					AdsP_xyz = 0.0;
					LabP_xyz = 0.0;

					for (l = 1; l <= tilq; l++) //initiazes all of the cummulative temporary soil layer variables to the pool constituents up to the tillage depth as a single cummulative value..
					{
						rcvl_xyz += rcvl[l];
						rcl_xyz += rcl[l];
						rcr_xyz += rcr[l];
						crb1_xyz += CRB1[l];
						crb2_xyz += CRB2[l];
						crh1_xyz += crhl[l];
						crh2_xyz += crhr[l];
						dp_xyz += dphum[l];
						inertC_xyz += inert_C[l];
						newh_xyz += newh[l];
						tc_xyz += doc[l];
						no3_xyz += no3[l];
						nh4_xyz += nh4[l];
						clayn_xyz += clay_nh4[l];
						urea_xyz += urea[l];
						nh3_xyz += nh3[l];
						NH4HCO3_xyz += NH4HCO3[l];
						OrgP_xyz += OrgP[l];
						AdsP_xyz += AdsP[l];
						LabP_xyz += LabP[l];
					}


					rcvl[1] = rcvl_xyz / tilq; //very labile[layer[1] gets total cumulative very labile / number of tillage layers 
					rcl[1] = rcl_xyz / tilq;
					rcr[1] = rcr_xyz / tilq;
					CRB1[1] = crb1_xyz / tilq;
					CRB2[1] = crb2_xyz / tilq;
					crhl[1] = crh1_xyz / tilq;
					crhr[1] = crh2_xyz / tilq;
					dphum[1] = dp_xyz / tilq;
					inert_C[1] = inertC_xyz / tilq;
					newh[1] = newh_xyz / tilq;
					doc[1] = tc_xyz / tilq;
					no3[1] = no3_xyz / (float)tilq;
					nh4[1] = nh4_xyz / tilq;
					nh3[1] = nh3_xyz / tilq;
					urea[1] = urea_xyz / tilq;
					NH4HCO3[1] = NH4HCO3_xyz / tilq;
					clay_nh4[1] = clayn_xyz / tilq;
					OrgP[1] = OrgP_xyz / tilq;
					AdsP[1] = AdsP_xyz / tilq;
					LabP[1] = LabP_xyz / tilq;

					ocini[1] = CRB1[1] + CRB2[1] + crhl[1] + crhr[1];

					float CFT = 0.0;// 0.0001*air_temp;
					if (CFT < 0.0) CFT = 0.0;
					for (l = 1; l <= tilq; l++)//for rest of the layers in tillage affected layers get the same proportion of total consitutients (previous + new) as the just calculated layer 1 above.
					{
						rcvl[l] = rcvl[1];
						rcl[l] = rcl[1];
						rcr[l] = rcr[1];
						CRB1[l] = CRB1[1];
						CRB2[l] = CRB2[1];
						crhl[l] = crhl[1];
						crhr[l] = crhr[1];
						dphum[l] = dphum[1];
						inert_C[l] = inert_C[1];
						newh[l] = newh[1];
						doc[l] = doc[1];
						no3[l] = no3[1];
						nh4[l] = nh4[1];
						nh3[l] = nh3[1];
						urea[l] = urea[1];
						NH4HCO3[l] = NH4HCO3[1];
						clay_nh4[l] = clay_nh4[1];
						ocini[l] = ocini[1];
						OrgP[l] = OrgP[1];
						AdsP[l] = AdsP[1];
						LabP[l] = LabP[1];

						float dHumus = dphum[l] * CFT;
						dphum[l] -= dHumus;
						crhr[l] += dHumus;
					}
					//end mixing code........
					*/
					


				}
				
				if ( tilld < 0.00001 ) till_fact = 1.0; //no enhcanced tillage decomposition
				else if ( fabs(tilld - 0.05) < 0.00001 ) till_fact = 3.0;//4.5;//3 //5cm enhanced tillage factor
				else if ( fabs(tilld - 0.1) < 0.00001 ) till_fact = 4.0;//5.0;//4  //10cm enhanced tillage factor
				else if (fabs(tilld - 0.15) < 0.00001) till_fact = 4.5;//5.0;//4  //15cm enhanced tillage factor
				else if ( fabs(tilld - 0.2) < 0.00001 ) till_fact = 5.0;//7.0;//5  //20 cm enhanced tillage factor
				else if ( fabs(tilld - 0.3) < 0.00001 ) till_fact = 6.0;//9.0;//6 //30 cm enchanced tillage factor
				else till_fact = 1.0;

				if (til_method[oz] == 6) till_fact = 2.0;
			}
		}
    }

	if(TTT>1.0) till_fact -= 0.1;//if raining tillage factor reduced by a factor of 0.1
	else till_fact -= 0.01;//if dry it only decreases by 0.01
	if(till_fact <= 1.0) till_fact = 1.0;

    *tilq_p = tilq;
 
    return( till_fact );
}

void class_model::stub_fall()
{
    if ( stub1 + stub2 + stub3 > 0.00000001 )
    {
		float yy, dep1, dep2, dep3;
		//if(air_temp>0.0) yy = 0.000001*air_temp;
		//else yy = 0.0;
		
		yy = 0.025;//0.005;0.015  // daily decomposing rate for stubble pools


		//calculates what amount of above ground stubble decomposes in a day based on yy
		dep1 = stub1 * yy;//very labile stubble..
		dep2 = stub2 * yy;//labile stubble
		dep3 = stub3 * yy;//resistant stubble

		yr_addtc += (dep1 + dep2 + dep3);
		day_addC += (dep1 + dep2 + dep3);
		yr_addtn += (dep1 / rcnrvl + dep2 / rcnrl + dep3 / rcnrr);
		//day_inLitterN += (dep1 / rcnrvl + dep2 / rcnrl + dep3 / rcnrr);
		day_inStubN += (dep1 / rcnrvl + dep2 / rcnrl + dep3 / rcnrr);

		//this adds the equivalent C to the litter fractions (very labile, labile and resistant litter pools)
		//should this use alloc litter to pools (alloc_litter_into_pools) function to ensure added N is OK and not imbalanced?

		rcvl[1] += dep1; //C:N at 5
		rcl[1] += dep2; //C:N at 25
		rcr[1] += dep3; //C:N at 100


		//reduces the stubble pools by the decomposing amount of stubb.
		stub1 -= dep1;//*= (1.0 - yy); //reduced Stub pool by decomposed C 
		stub2 -= dep2;//*= (1.0 - yy);
		stub3 -= dep3;//*= (1.0 - yy);
    }
}


void class_model::crop_harvesting(int scale, int ccwc)
{
    int    l, oz=0;
    float  AddC, AddCN;
    float  Stuble;
    float haradd2;
	float AddC1, AddC2, AddC3, dInertC;

	cropHarvestDay[ccwc]=jday;
	cropGrowDays[ccwc]=crop_days[ccwc];
	germCount=1;
	DayPETCROP[ccwc]=0.0;//reset DayPETCROP[ccwc]
	TDD[ccwc] = 0.0;
	day_DWater[ccwc] = 0.0;
	cropTempStress[ccwc] = 0.0;
	lai[ccwc] = 0.0;
	leafTemp_C[ccwc] = 0.0;
	CropHeight[ccwc] = 0.001;
	//maturityDay[ccwc] = jday;
	growthStatus[ccwc] = PGI[ccwc];
	//reset root Density function to zero
	float unHarvGrain = 0.0;
	if (PGI[ccwc] < 0.50) 
	{ 
		unHarvGrain = Grain_Wt[ccwc];
		Grain_Wt[ccwc] = 0.0; 
	
	}//need to add this to Stuble below..//was.95
//	int ai;
//	for(ai=1; ai<q; ai++)
  //  {
	// rootDensity[ccwc][ai]=0.0;
//	}
//	root_length[ccwc]=0.0;	

	if(crop[ccwc]==20||crop[ccwc]==46) 
	{
		IrriRice_flag = 0;
		ShallowFloodFlag = 0;
		flood_flag = 0;
		RainfedRice_flag = 0;
	}


	HarvestDay[ccwc] = jday;
	//obsYieldFlag == 1)
	if (obsYieldFlag == 1)//if obsYield Flag is set to one then read in obsYields
	{
		Grain_Wt[ccwc]=obsGrain[year];
		Leaf_Wt[ccwc]=obsLeaf[year];
		Stem_Wt[ccwc]=obsStem[year];
		Root_Wt[ccwc]=obsRoot[year];



	}


	//CropEndN[ccwc] = plantn[ccwc];
	YrG_grain[ccwc] = Grain_Wt[ccwc];
	YrG_leaf[ccwc] = Leaf_Wt[ccwc];
	YrG_stem[ccwc] = Stem_Wt[ccwc];
	YrG_root[ccwc] = Root_Wt[ccwc];
	

	YrN_grain[ccwc] = GrainN[ccwc];
	YrN_leaf[ccwc] = LeafN[ccwc];
	YrN_stem[ccwc] = StemN[ccwc];
	YrN_root[ccwc] = RootN[ccwc];
	
		
	PresentBiomass[ccwc] = Root_Wt[ccwc] + Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc];
	biomass += Root_Wt[ccwc] + Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc];
	ProdC[ccwc] = PresentBiomass[ccwc];
	
	
	//Grain_Wt[ccwc] = 0.0;
	//if(grain[ccwc]<0.05)//grass crops
	if(CoverCrop[ccwc]==1)//||grain[ccwc]<0.05)//cover crop
	{
		float AboveGroundBiomass = Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc];//YrG_grain[ccwc]+YrG_leaf[ccwc]+YrG_stem[ccwc];
		//YrG_grain[ccwc] = 0.0;
		//YrG_leaf[ccwc] = 0.0;
		//YrG_stem[ccwc] = 0.0;//AboveGroundBiomass;

		Stuble = AboveGroundBiomass;
	}
	else
	{
		if(scale==1)
		{
			if(crop[ccwc]==4||crop[ccwc]==5) left_perc[ccwc] = 0.05;
		}
		
		//if(grain[ccwc]>0.05) 
		//	Stuble = (Leaf_Wt[ccwc] + Stem_Wt[ccwc]) * left_perc[ccwc]; // grain crops
		//else 
		HarvestedBiomassC[ccwc] += Grain_Wt[ccwc];

		Stuble = (Leaf_Wt[ccwc] + Stem_Wt[ccwc]) * left_perc[ccwc]; //0.0;
	}
	
	

	//This ends up missing the final weights on harvest day.
	//Leaf_Wt[ccwc] = 0.0;
//	Stem_Wt[ccwc] = 0.0;
//	Grain_Wt[ccwc] = 0.0;

	if(day_file==0)
		{	
			//Was in there for batch files to reset these parameters. Not sure if it was necessary but it causes the C inputs to be lossed to the soil.
		/*
			Leaf_Wt[ccwc] = 0.0;
			Stem_Wt[ccwc] = 0.0;
			Grain_Wt[ccwc] = 0.0;
			seed[ccwc] = 0;
			//crop_days[ccwc]=0;
			PGI[ccwc] = 0.0;
			//*cwc_p = ccwc;
			//I_Stage = 7;
			plantn[ccwc]=0.0;
			Root_Wt[ccwc] = 0.0;
			Grain_Wt[ccwc] = 0.0;
			Leaf_Wt[ccwc] = 0.0;
			Stem_Wt[ccwc] = 0.0;
			LeafN[ccwc] = 0.0;
			StemN[ccwc] = 0.0;
			GrainN[ccwc] = 0.0;
			RootN[ccwc] = 0.0;
		//	harvest_flag[cwc]=0;
		*/
		}


	AddC = Stuble+unHarvGrain;//only comprised of the leaf and stem left on field.//added unHarvestable Grain;
	AddCN = leafcn[ccwc];// need to consider both stem and leafcn here!!!!

	/* Add new stub litter into stub litter pools */
	alloc_litter_into_pools(&AddCN, &AddC, oz, &AddC1, &AddC2, &AddC3, &dInertC, 1, rcnrvl, rcnrl, rcnrr, nh4);

	stub1 += AddC1;
	stub2 += AddC2;
	stub3 += AddC3;//where to put inert_C[]?
	stubP = plantP[ccwc] * 0.2 * left_perc[ccwc];//Plant P = 70% in grain, 20% in shoot, 10% in root
	inert_C[1] += dInertC;

	day_addC += dInertC;//(AddC1+AddC2+AddC3);
	yr_addtc += dInertC;;//(AddC1+AddC2+AddC3);
	//day_inStubN += AddC1 / rcnrvl + AddC2 / rcnrl + AddC3 / rcnrr;
	//yr_addtn += day_inStubN;

	AddC1 = 0.0;
	AddC2 = 0.0;
	AddC3 = 0.0;

	
	if(Root_Wt[ccwc]>0.0)  //allocation of root C to C pools //start root loop
	{
		//brian root_exudates
		root_exudates=0.0;
		
		if (crop[ccwc] == 10)
		{
			root_exudates += Root_Wt[ccwc] * 1.00;
			Root_ExuC[ccwc] = root_exudates;
			Root_ExuN[ccwc] = root_exudates / rootcn[ccwc];
		}
		else
		{
			root_exudates += Root_Wt[ccwc] * 0.65;//65% of root C
			Root_ExuC[ccwc] = root_exudates;
			Root_ExuN[ccwc] = root_exudates / rootcn[ccwc];
		}
		AddC = Root_Wt[ccwc] +root_exudates;
		AddCN = rootcn[ccwc];
		alloc_litter_into_pools(&AddCN, &AddC, oz, &AddC1, &AddC2, &AddC3, &dInertC, 0, rcnrvl, rcnrl, rcnrr, nh4);
		float AddP = plantP[ccwc] * 0.1;

		int root_layer = (int)(root_length[ccwc]/h[1]); 
		if (root_layer < 2)
		{
			root_layer = 2;
		}//should be 2?
		if(root_layer>q) root_layer = q;

		float totalRDensity;
		totalRDensity=0.0;

		//new root C allocation based on Root Density to allocate across layers

		//test off

		
		for ( l = 1; l <= root_layer; l++ )
		{
			if (rootDensity[ccwc][l] == 0.0)
			{
				float blah;
				blah = 1.0;

			}
					rcvl[l] += AddC1 * rootDensity[ccwc][l];
					rcl[l] += AddC2 * rootDensity[ccwc][l];
					rcr[l] += AddC3 * rootDensity[ccwc][l];
					inert_C[l] += day_inert_C * rootDensity[ccwc][l];
					OrgP[l] += AddP * rootDensity[ccwc][l];
					totalRDensity+=rootDensity[ccwc][l];

		}
		
		//end test

	//reset root Density function to zero

	int ai;
	for(ai=1; ai<q; ai++)
    {
	 rootDensity[ccwc][ai]=0.0;
	}
//	root_length[ccwc]=0.0;	//not sure why this is a bad idea to turn on at this point. Forget my reasoning

	/*
		// original root C allocation to pools
		for ( l = 1; l <= q; l++ )
		{

	
			if ( l >= 1 && l <= 3 )
			{
				rcvl[l] += AddC1 * 0.5 / 3.0;
				rcl[l] += AddC2 * 0.5 / 3.0;
				rcr[l] += AddC3 * 0.5 / 3.0;
				inert_C[l] += day_inert_C * 0.5 / 3.0;
				OrgP[l] += AddP * 0.5 / 3.0;
			}
			if ( l >= 4 && l <= 6 )
			{
				rcvl[l] += AddC1 * 0.4 / 3.0;
				rcl[l] += AddC2 * 0.4 / 3.0;
				rcr[l] += AddC3 * 0.4 / 3.0;
				inert_C[l] += day_inert_C * 0.4 / 3.0;
				OrgP[l] += AddP * 0.4 / 3.0;
			}
			if ( l >= 7 && l <= 9 )
			{
				rcvl[l] += AddC1 * 0.1 / 3.0;
				rcl[l] += AddC2 * 0.1 / 3.0;
				rcr[l] += AddC3 * 0.1 / 3.0;
				inert_C[l] += day_inert_C * 0.1 / 3.0;
				OrgP[l] += AddP * 0.1 / 3.0;
			}
			
		}
		*/

		float AddToSoilC, AddToSoilN , AddToSoilP;
		AddToSoilC = AddC1 + AddC2 + AddC3 + dInertC;
		AddToSoilN = AddC1/rcnrvl + AddC2/rcnrl + AddC3/rcnrr;
		AddToSoilP = AddP;

		day_addC += AddToSoilC;
		yr_addrc += AddToSoilC;
		day_addrn += AddToSoilN;
		yr_addrn += AddToSoilN;

		yr_addrp += AddToSoilP;

		float RootAddC = AddC1+AddC2+AddC3;
		
		AddC1 = 0.0;
		AddC2 = 0.0;
		AddC3 = 0.0;
		//resets root_wt[ccwc] too early.
		//Root_Wt[ccwc] = 0.0;
	}//end root loop

	AddC = 0.0;
	
	haradd2 = 0.0;
	//demandn[ccwc] = 0.0;
	//lai[ccwc] = 0.0; brian turned off for AgMIP
	crop_flag[ccwc] = 2;
	harvest_flag[ccwc] = 1;
	//ccwc = ccwc + 1;
	
	//turn off this for autoharvest
	/*
	seed[ccwc] = 0;
	//crop_days[ccwc]=0;
	PGI[ccwc] = 0.0;
	//*cwc_p = ccwc;
	//I_Stage = 7;
	plantn[ccwc]=0.0;
	Root_Wt[ccwc] = 0.0;
	Grain_Wt[ccwc] = 0.0;
	Leaf_Wt[ccwc] = 0.0;
	Stem_Wt[ccwc] = 0.0;
	LeafN[ccwc] = 0.0;
	StemN[ccwc] = 0.0;
	GrainN[ccwc] = 0.0;
	RootN[ccwc] = 0.0;
*/

	//end turn off this for autoharvest
	ccwc++;

	jarovization_flag = 1.0;

	PresentBiomass[ccwc] = Root_Wt[ccwc] + Leaf_Wt[ccwc] + Stem_Wt[ccwc] + Grain_Wt[ccwc];
}

void class_model::partition_vll_humad(float solid_CN, float AddC, float solid_MN, float *AddC1, float *AddC2, float *AddC3,
									  float *AddHum, float rcnrvl, float rcnrl, float rcnrr, float rcnh)
{
	if(solid_CN<rcnrvl)
	{
		*AddHum = AddC; 
		*AddC1 = 0.0;
		*AddC2=0.0;
		*AddC3=0.0;
	}
	else if(solid_CN>=rcnrvl&&solid_CN<rcnh)
	{
		*AddHum = (rcnrvl*rcnh*solid_MN - rcnh*AddC)/(rcnh-rcnrvl);
		if(*AddHum<0.0) *AddHum=0.0;
		*AddC1 = AddC - *AddHum;
		*AddC2=0.0;
		*AddC3=0.0;
	}
	else if(solid_CN>=rcnh&&solid_CN<rcnrl)
	{
		*AddHum = (rcnh*rcnrl*solid_MN - rcnh*AddC)/(rcnrl-rcnh);
		if(*AddHum<0.0) *AddHum=0.0;
		*AddC1 = 0.0;
		*AddC2 = AddC - *AddHum;
		*AddC3=0.0;
	}
	else
	{
		*AddC3 = (rcnrr*rcnrl*solid_MN - rcnrr*AddC)/(rcnrl-rcnrr);
		if(*AddC3<0.0) *AddC3=0.0;
		*AddC2 = AddC - *AddC3;
		*AddC1 = 0.0;
		*AddHum = 0.0;
	}

}

