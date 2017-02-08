#include "Dll.h"
#include <iostream>

void MyClass::subtraction(__int16 ***tab, int area[2], int size)
{
	__int16 *A, *B;
	for (int i = area[0]; i < area[1]; i++)
	{
		A = tab[0][i];
		B = tab[1][i];
		for (int j = 0; j < size; j++)
			B[j] -= A[j];
	}
}