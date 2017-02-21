#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>
#include <fstream>

#include "../JA_Cpp_Dll/Dll.h"

typedef __int16(*subtractionAsm)(__int16 ***tab, int area[2], int size);
typedef __int16(__stdcall *subtraction)(__int16 ***tab, int area[2], int size);

int main(int argc, char* argv[])
{

	int numberOfThreads;
	unsigned int threadCount=std::thread::hardware_concurrency();   //liczba wątków

	clock_t t;
	t = clock();

	HMODULE lib;
	subtractionAsm myFunc;

	if (argc >= 5)
	{
		if (argc = 6)   //jeśli podano 6 argumentów, to liczba wątków jest zczytywana jako 6. parametr
		{
			numberOfThreads = std::stoi(argv[5]);
		}
		else
		{
			numberOfThreads = threadCount;
		}

		std::thread *threadsArray = NULL;
		int *threadsArea = NULL;
		int size[2] = { std::stoi(argv[3]), std::stoi(argv[4])};
		int area[2];
		__int16 **matrixArray[3] = {NULL, NULL,NULL};

		std::fstream inFile;
		inFile.open(argv[2], std::ios::in | std::ios::out);
		if (inFile.good() == true)
		{
        // wczytywanie zmiennych z pliku
			matrixArray[0] = new __int16 *[size[0]];
			matrixArray[1] = new __int16 *[size[1]];

			for (int i = 0; i < size[0]; i++)
			{
				matrixArray[0][i] = new __int16[size[1] + 1];
			}
			for (int i = 0; i < size[2]; i++)
			{
				matrixArray[1][i] = new __int16[size[1] + 1];
			}

			for (int i = 0; i < size[0]; i++)
				for (int j = 0; j < size[1]; j++)
					inFile >> matrixArray[0][i][j];

			for (int i = 0; i < size[0]; i++)
				for (int j = 0; j < size[1]; j++)
					inFile >> matrixArray[1][i][j];

			//wartownicy
			for (int i = 0; i < size[0]; i++) {
				matrixArray[0][i][size[1]] = 0;
			}

			threadsArray = new std::thread[numberOfThreads];
			threadsArea = new int[numberOfThreads + 1];

			for (int i = 0; i < numberOfThreads + 1; i++)
				threadsArea[i] = size[0] * i / numberOfThreads;

			for (int i = 0; i < numberOfThreads + 1; i++)
				std::cout  << i << " " << threadsArea[i] << std::endl;
            //uruchamianie biblioteki napisanej w c++
			if (strcmp(argv[1], "cpp") == 0)
			{
				HMODULE subLib = LoadLibrary(L"JA_Cpp_Dll.dll");
				if (!subLib)
				{
					subtraction subCpp = (subtraction)GetProcAddress(subLib, "subtraction");

					if (subCpp != NULL)
					{
						for (int i = 0; i < numberOfThreads; i++)
							threadsArray[i] = std::thread(subCpp, matrixArray, &threadsArea[i], size[1]);

						for (int i = 0; i < numberOfThreads; i++)
							threadsArray[i].join();
					}

					FreeLibrary(subLib);
				}
			}
			//uruchamianie biblioteki napisanej w asemblerze
			else if (strcmp(argv[1], "asm") == 0)
			{
				if ((lib = LoadLibrary(L"JA_Asm_Dll.dll")) != NULL)
				{
					myFunc = (subtractionAsm)GetProcAddress(lib, "subtractionAsm");

					if (myFunc != NULL)
					{
						for (int i = 0; i < numberOfThreads; i++)
							threadsArray[i] = std::thread(myFunc, matrixArray, &threadsArea[i], size[1]);

						for (int i = 0; i < numberOfThreads; i++)
							threadsArray[i].join();
					}

					FreeLibrary(lib);
				}
				//zapisywanie macierzy wynikowej do pliku
				std::fstream outFile;
				outFile.open("wynik.txt", std::ios::out);
				if (outFile.good())
				{
					for (int i = 0; i < size[0]; i++)
						for (int j = 0; j < size[1]; j++)
							outFile << matrixArray[1][i][j] << "\t";

				}
				outFile.close();

			}
			inFile.close();
		}
	}
    //wyświetlenie czasu
	t = clock() - t;
	std::cout << "Time: " << t << " ms" << std::endl;

	system("PAUSE");
	return 0;
}
