#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"




void class_model::farmAgent(float yearlyNStress[10][10], float yearlyNUptake[10][10], int cropRotType[10])
{
	int i, z, cropT;
	int cropNums = 0;


	if (year == 1)
	{
		for (int c = 0; c < 10; c++)
		{
			for (int i = 0; i < 10; i++)
			{
				yearlyNStress[c][i] = 0.0f;
				yearlyNUptake[c][i] = 0.0f;
				yearlyNStressYear[c][i] = -1;   // invalid
			}
		}
	}

	/*------------------------------------
	  Count crops planted this year
	------------------------------------*/
	for (i = 1; i <= 9; i++)
	{
		if (crop[i] != 0) cropNums++;
		else break;
	}

	/*------------------------------------
	  Loop over crops this year
	------------------------------------*/
	for (z = 1; z <= cropNums; z++)
	{
		/* Identify cropT */
		for (i = 0; i < 10; i++)
		{
			if (cropRotType[i] == crop[z])
			{
				cropT = i;
				break;
			}
			else if (cropRotType[i] == 0)
			{
				cropRotType[i] = crop[z];
				cropT = i;
				break;
			}
		}

		/*--------------------------------
		  Insert this year's value
		--------------------------------*/
		int slot = year % 10;   // circular index

		yearlyNStress[cropT][slot] =
			min(1.0f, max(0.0f,
				crop_N_stress[z] /
				(float)crop_N_stress_days[z]));

		yearlyNUptake[cropT][slot] = yr_uptaken[z];
		yearlyNStressYear[cropT][slot] = year;

		if (crop[z] == 0) // fallow exception
			yearlyNStress[cropT][slot] = 1.0f;

		/*--------------------------------
		  Compute 10-year running average
		--------------------------------*/





		float sumStress = 0.0f;
		float sumUptake = 0.0f;
		int   validCount = 0;

		for (i = 0; i < 10; i++)
		{

			if (yearlyNStressYear[cropT][i] != -1 && yearlyNStressYear[cropT][i] >= year - 9)
			{
				sumStress += yearlyNStress[cropT][i];
				sumUptake += yearlyNUptake[cropT][i];
				validCount++;
			}
		}

		if (validCount > 0)
		{
			averageNStress[cropT] = sumStress / validCount;
			averageNUptake[cropT] = sumUptake / validCount;
		}
		else
		{
			averageNStress[cropT] = 1.0f;
			averageNUptake[cropT] = 0.0f;
		}
	}

	write_out_NStress();
}


int class_model::write_out_NStress()
{






	FILE* fp;
	int   l, cropNums;
	char NSTRESS[120];

	for (int i = 0; i <= 9; i++)//loop to read the cropRot sequence
	{
		if (cropRotType[i] == 0)
		{
			cropNums = i;//counts how many crop types we need to keep track off. 
			break;
		}
		else
		{
			cropNums = 10;//max = 10 concurrent crops
		}
	}

	sprintf(NSTRESS, "%s\\Inputs\\NStress-%d", OUTPUT, year);//sets directory name




	if (jday == 1 && year == 1)//ensure the NStress-%d file is reset to zero at beginning of simulations for autofertilization
	{
		char NSTRESSB[120];
		for (int zi = 1; zi <= 100; zi++)//Loop to remove first 100 files
		{
			sprintf(NSTRESSB, "%s\\Inputs\\NStress-%d", OUTPUT, zi);//sets directory name
			remove(NSTRESSB); //remove Nstress-1 through NStress-100 file.  needs further testing...probably unnecessary as it wasn't the issue causing the inconsistancy
		}
		/*
		for (int z = 0; z <= (1); z++)
		{
			fprintf(fp, "%f %f %f %f %f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(fp, "%f %f %f %f %f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			fprintf(fp, "%f\n", 0.0);
			fprintf(fp, "%f\n", 0.0);
		}
		fclose(fp);
		*/

	}
	else //end of year 1 and all subsequent years write out the yearly N stress/per crop, yearly N uptake/per crop and average N stress/N uptake
	{
		fp = fopen(NSTRESS, "w");
		if (fp == NULL)
		{
			char err[60];
			sprintf(err, "can not create file %s", NSTRESS);
			AfxMessageBox(err);
			exit(0);
		}

		for (int z = 0; z <= (cropNums - 1); z++)
		{
			fprintf(fp, "%f %f %f %f %f %f %f %f %f %f\n", yearlyNStress[z][0], yearlyNStress[z][1], yearlyNStress[z][2], yearlyNStress[z][3], yearlyNStress[z][4], yearlyNStress[z][5], yearlyNStress[z][6], yearlyNStress[z][7], yearlyNStress[z][8], yearlyNStress[z][9]);//z=crop Types in rotation, 0-9 is years.
			fprintf(fp, "%f %f %f %f %f %f %f %f %f %f\n", yearlyNUptake[z][0], yearlyNUptake[z][1], yearlyNUptake[z][2], yearlyNUptake[z][3], yearlyNUptake[z][4], yearlyNUptake[z][5], yearlyNUptake[z][6], yearlyNUptake[z][7], yearlyNUptake[z][8], yearlyNUptake[z][9]);
			fprintf(fp, "%f\n", averageNStress[z]);
			fprintf(fp, "%f\n", averageNUptake[z]);

			fprintf(fp, "%d %d %d %d %d %d %d %d %d %d\n",
				yearlyNStressYear[z][0], yearlyNStressYear[z][1],
				yearlyNStressYear[z][2], yearlyNStressYear[z][3],
				yearlyNStressYear[z][4], yearlyNStressYear[z][5],
				yearlyNStressYear[z][6], yearlyNStressYear[z][7],
				yearlyNStressYear[z][8], yearlyNStressYear[z][9]);


		}
		fclose(fp);
	}
	return(0);


}

int class_model::read_in_NStress()
{
	FILE* fp;
	int   l, cropNums;
	char NSTRESS[120];

	sprintf(NSTRESS, "%s\\Inputs\\NStress-%d", OUTPUT, (year - 1));


	fp = fopen(NSTRESS, "r");
	if (fp == NULL)
	{
		char err[60];
		sprintf(err, "can not read file %s", NSTRESS);
		AfxMessageBox(err);
		exit(0);
	}

	for (int i = 0; i <= 9; i++)
	{
		if (cropRotType[i] == 0)
		{
			cropNums = i;
			break;
		}
		else
		{
			cropNums = 10;
		}
	}
	for (int z = 0; z <= (cropNums - 1); z++)
	{
		fscanf(fp, "%f %f %f %f %f %f %f %f %f %f\n", &yearlyNStress[z][0], &yearlyNStress[z][1], &yearlyNStress[z][2], &yearlyNStress[z][3], &yearlyNStress[z][4], &yearlyNStress[z][5], &yearlyNStress[z][6], &yearlyNStress[z][7], &yearlyNStress[z][8], &yearlyNStress[z][9]);
		fscanf(fp, "%f %f %f %f %f %f %f %f %f %f\n", &yearlyNUptake[z][0], &yearlyNUptake[z][1], &yearlyNUptake[z][2], &yearlyNUptake[z][3], &yearlyNUptake[z][4], &yearlyNUptake[z][5], &yearlyNUptake[z][6], &yearlyNUptake[z][7], &yearlyNUptake[z][8], &yearlyNUptake[z][9]);
		fscanf(fp, "%f\n", &averageNStress[z]);
		fscanf(fp, "%f\n", &averageNUptake[z]);

		fscanf(fp, "%d %d %d %d %d %d %d %d %d %d\n",
			&yearlyNStressYear[z][0], &yearlyNStressYear[z][1],
			&yearlyNStressYear[z][2], &yearlyNStressYear[z][3],
			&yearlyNStressYear[z][4], &yearlyNStressYear[z][5],
			&yearlyNStressYear[z][6], &yearlyNStressYear[z][7],
			&yearlyNStressYear[z][8], &yearlyNStressYear[z][9]);


	}
	fclose(fp);
	return(0);


}