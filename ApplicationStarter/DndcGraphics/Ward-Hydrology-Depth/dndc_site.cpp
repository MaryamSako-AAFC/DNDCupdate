#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "dndc_main.h"
//#include "region.h"
#include "direct.h"

CString CROP[250] = {"Fallow", "Corn", "W_wheat", "Soybean", "L_hay", "NL_hay", 
					"S_wheat", "Sugarc", "Barley", "Oats", "Alfalfa", 
					"Grass", "Pasture", "Sorghum", "Cotton", "Rye", 
					"Veget", "NewCrop", "Potato", "Beet", "Rice", 
					"Banana", "Celery", "Peanut", "DryRice", "Rapes", 
					"Tobacco", "Millet", "Sunfl", "Beans", "DW_rice", 
					"Onion", "NewCrop", "Strawb", "Lettuce", "Artich", 
					"Nersery", "Brussel", "Berries", "TruCrop", "Fruits", 
					"Citrus", "Grapes", "Sil_corn", "Hops", "Tomato", 
					"NewCrop", "CoverCr", "Safflo", "Flax", " ", //50
					"wwt/cor", "rap/ric", "wwt/rap", "ric/ric", "wwt/ric", 
					"wwt/veg", "rap/cor", "rap/veg", "veg/cor", "veg/ric",//60 
					"cor/soy", "wwt/soy", "oat/ric", "pot/soy", "soy/hay", 
					"wwt/pot", "wwt/cot", "pot/cor", "rap/soy", "rap/cot",//70 
					"oat/soy", "ric/soy", "pot/pot", "cor/cor", "ve/ve/v", 
					"r/r/lha", "r/r/rap", "po/v/v", "r/r/ww", "r/r/ve",//80
					"", " ", " ", " ", " ",
					"", " ", " ", " ", " ",//90
					"", " ", " ", " ", " ",
					"", " ", " ", " ", " ", //100
					"", " ", " ", " ", " ",
					"", " ", " ", " ", " ",//110					
					"", "", "", "", "", 
					"", "", "", "", "",//120
					"", "", "", "", "",
					"", "", "", "", "hay/hay",//130
					"g/g", "g/veg", "hay/g", "hay/veg", "veg/veg", 
					"g/g/g", "g/g/ve", "g/v/g", "", "",//140
					"", "", "", "", "",
					"", "", "", "", "Dairy",//150
					"", "", "", "", "",
					"", "", "", "", "",//160
					"", "", "", "", "",
					"", "", "", "", "",//170
					"", "", "", "", "",
					"", "", "", "", "",//180
					"", "", "", "", "",
					"", "", "", "", "",//190
					"", "", "", "", "",
					"", "", "", "", "",//200	
					"Rf_Ir","Rf_Rf","Rf_Wht","Rf","IrIrIr",
					"Ir_Ir","IrIrVeg","IrIrRap","IrIrSoy","IrIrPot",//210
					"IrIrSor","IrIrVeg","IrIrWht","IrIrCot","IrRaCot",
					"RfRaCot","IrCoVeg","IrVeCot","RfVeCot","IrVePot",//220
					"IrSoSoy","RfWhCot","IrWhPot","RfVeWht","Ir_Cot",
					"Rf_Cot","Ir_Bar","Rf_Bar","Rf_Bar","Rf_Veg",//230
					"Ir_Mil","Rf_Mil","Ir_Rap","Rf_Rap","Ir_Pot",
					"Rf_Pot", "Ir_Soy","Rf_Soy","Ir_Sor", "Ir_Sug",//240
					"Rf_Sug","Ir_Veg","Rf_Veg","Ir_Wht","Ir",
					"Upland","DeepWat","Ir_Qat", "IrIrLha"};//249

dndc74::dndc74()
{
    CString DIR0;
	DIR0.Format("%s", ROOTDIR);
	mkdir(DIR0);

	DIR0.Format("%s", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inputs", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inter", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inter\\Management_1", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Inter\\RegionFiles", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Record", OUTPUT);
	mkdir(DIR0);

	DIR0.Format("%s\\Record\\Region", OUTPUT);
	mkdir(DIR0);
	DIR0.Format("%s\\Record\\Site", OUTPUT);
	mkdir(DIR0);
	//DIR0.Format("%s\\Record\\RegionSummary", OUTPUT);
	//mkdir(DIR0);
	//DIR0.Format("%s\\Record\\SiteSummary", OUTPUT);
	//mkdir(DIR0);
	DIR0.Format("%s\\Record\\MonteCarlo", OUTPUT);
	mkdir(DIR0);

	for(int i=0; i<250; i++)
	{
		CropSystem[i].Format("%s", CROP[i]);
	}
}

dndc74::~dndc74()
{

}

void dndc74::dndc_site(CGraphexDoc *pDoc)
{
	if (pDoc->DNDC_or_Other == 1) return;
	pDoc->ClearAct();
	pDoc->StopRun = -1;		//run DNDC
	pDoc->DNDC_or_Other = 1;//Show DNDC is running 
	
	int TotalYears;
	int SITE_MODE = 0;
	char Site[60], junkc[60];

	FILE *FileRun;	
	
	sprintf(Site, "%s\\INPUTS\\Site", OUTPUT);

    FileRun = fopen(Site, "r");
    if ( FileRun == NULL )
	{
		AfxMessageBox("Can not open file Site");
		return;
	}

    fscanf(FileRun, "%s", junkc);
    fscanf(FileRun, "%d", &TotalYears);
    fclose(FileRun);
	
	  
/*	for(ThisYear=1; ThisYear<=TotalYears; ThisYear++)
	{
		class_model *DNDC; //define DNDC as a point of class_model

		if(!(DNDC = new class_model() )) //assign a memory space for DNDC
			AfxMessageBox("No enough memory to run modelClass()");
		else
		{
			DNDC->year = ThisYear;

			DNDC->DNDC74(pDoc, SITE_MODE, 1, 0.0, 0, 0, 0, "0", 0, 0); 

			delete DNDC; //release the space accupied by DNDC
		}	
		
		if (pDoc->StopRun==0)
			break;
	}
*/
	MessageBeep(0);
	pDoc->StopRun = 0;
	pDoc->DNDC_or_Other = 0;
}