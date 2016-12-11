#include "Dll.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define DLL_EXPORT


extern "C"
{
	DECLDIR void subtraction(double **tab1, double **tab2, int sizeOfMatrix[2])
	{
		for (int i = 0; i<sizeOfMatrix[1]; ++i)
			for (int j = 0; j<sizeOfMatrix[0]; ++j)
				tab1[i][j] =-tab2[i][j];
	}

}
