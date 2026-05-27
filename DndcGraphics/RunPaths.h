
	#ifndef RUNPATHS_H


	#define RUNPATHS_H



	//#ifdef DNDC95_EXPORTS
	//#define RUNPATHS_API extern "C" __declspec(dllexport)
	//#else
	#define RUNPATHS_API extern "C" __declspec(dllimport)
	//#endif

	RUNPATHS_API const char* ROOTDIR;
	RUNPATHS_API const char* OUTPUT;
	RUNPATHS_API const char* INTER;
	RUNPATHS_API const char* INPUTS;
	RUNPATHS_API const char* INTERMANAGE;
	RUNPATHS_API const char* LIBRARY;
	RUNPATHS_API const char* PassC1;
	RUNPATHS_API const char* DIRin;

	RUNPATHS_API char ssROOTDIR[400];
	RUNPATHS_API char ssOUTPUT[400];
	RUNPATHS_API char ssINTER[400];
	RUNPATHS_API char ssINPUTS[400];
	RUNPATHS_API char ssINTERMANAGE[400];
	RUNPATHS_API char ssLIBRARY[400];
	RUNPATHS_API char ssPassC1[400];
	RUNPATHS_API char ssDIRin[400];

	#endif


