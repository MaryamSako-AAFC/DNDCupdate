#pragma once
#include "resource.h"

typedef int (WINAPI* LPFN_ADDFUNC)(const int, const int);
typedef int (WINAPI* LPFN_MODELFUNC)(const wchar_t*, const wchar_t*, const wchar_t*);

class Swine
{
public:
	Swine(void);
	~Swine(void);

	LPFN_ADDFUNC AddFunc;
	LPFN_MODELFUNC RunGrowthModel;
	LPFN_MODELFUNC RunSowModel;
private:
	HMODULE hMod;
};

