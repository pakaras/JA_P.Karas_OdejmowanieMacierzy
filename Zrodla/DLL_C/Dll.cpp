#include "Dll.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define DLL_EXPORT

typedef struct {
	__int16 matrix[N_MAX][M_MAX];
} s1;

extern "C"
{
	DECLDIR s1 subtraction(double **firstMatrix, double **secondMatrix, double **differentialMatrix, int X, int Y)
	{
		s1 s;
		for (int i = 0; i<X; ++i)
			for (int j = 0; j<Y; ++j)
				differentialMatrix[i][j] = firstMatrix[i][j] - secondMatrix[i][j];
		return s;
	}

}
