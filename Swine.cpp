#include "StdAfx.h"
#include "Swine.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

Swine::Swine(void)
{
	hMod = LoadLibrary(_T("SwineLib.dll"));
	if (hMod != NULL){
		AddFunc = (LPFN_ADDFUNC)GetProcAddress(hMod, "AddTwoNumbers");
		RunGrowthModel = (LPFN_MODELFUNC)GetProcAddress(hMod, "RunGrowthModel");
		RunSowModel = (LPFN_MODELFUNC)GetProcAddress(hMod, "RunSowModel");
		//alert(std::to_string((long double) i));
	}else{
		throw;
	}
}


Swine::~Swine(void)
{
}
