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

typedef struct {
	__int16 matrix[N_MAX][M_MAX];
} s1;

extern "C"
{
	DECLDIR s1 subtraction(double **firstMatrix, double **secondMatrix, double **differentialMatrix, int X, int Y);
}

#endif

