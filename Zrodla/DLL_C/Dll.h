#pragma once

#ifndef _DLL_CPP_H_
#define _DLL_CPP_H_
#include <iostream>
#include <string.h>
#include <string>

#define DLL_EXPORT

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
#define N_MAX 30
#define M_MAX 50


extern "C"
{
	DECLDIR void subtraction(double *tab1, double *tab2, int sizeOfMatrix[2]);
}

#endif

