#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <process.h>
#include <cstdlib>
#include "../JA_Cpp_Dll/Dll.h"

#define N_MAX 30
#define M_MAX 50

using namespace std;

typedef DWORD(*subtractionAsm)();
int index = 0;

int numberOfThreadsFunction()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	return sysinfo.dwNumberOfProcessors;
}

void __cdecl ThreadProcCpp(void * Args)
{
	int i = index++;
//	void subtraction( firstMatrix, secondMatrix, differentialMatrix, X, Y);
	cout << "using thread # " << i << " for function in cpp" << endl;
	_endthread();
}

void __cdecl ThreadProcAsm(void * Args)
{
	int i = index++;

	cout << "using thread # " << i << " for function in assembler" << endl;
	_endthread();
}

int main(int argc, char* argv[])
{
	int numberOfThreads;
	clock_t t;
	t = clock();
	subtractionAsm myFunc;
	HMODULE lib;

	if (argc >= 5) 
	{ 
		if (argc = 6) 
		{ 
			numberOfThreads = stoi(argv[5]);
			cout << "User wrote number of threads and it is: " << numberOfThreads << endl;
		}
		else 
		{
			numberOfThreads = numberOfThreadsFunction();
			cout << "User didn't write number of threads but it is equal: " << numberOfThreads << endl;
		}

		fstream inFile;
		inFile.open(argv[2], ios::in | ios::out);
		if (inFile.good() == true) 
		{
			cout << "File open" << endl;

			__int16 firstMatrix[N_MAX][M_MAX];
			__int16 secondMatrix[N_MAX][M_MAX];
			__int16 differentialMatrix[N_MAX][M_MAX];

			int numberOfRows = stoi(argv[3]);
			int numberOfColumns = stoi(argv[4]);
			
			for (int i = 0; i < numberOfRows; i++)
				for (int j = 0; j < numberOfColumns; j++)
					inFile >> firstMatrix[i][j];
			for (int i = 0; i < numberOfRows; i++)
				for (int j = 0; j < numberOfColumns; j++)
					inFile >> secondMatrix[i][j];

			vector < HANDLE > threads;

			if (strcmp(argv[1], "cpp") == 0)
			{
				for (int j = 0; j < numberOfThreads; j++)
				{
					HANDLE hThread = (HANDLE)_beginthread(ThreadProcCpp, 1, NULL);
					threads.push_back(hThread);
				}
				if (threads.size() > 0)
				{
					WaitForMultipleObjects(threads.size(), &threads[0], TRUE, 15000);	//15s aby watki sie skonczyly
				}
			}
			else if (strcmp(argv[1], "asm") == 0)
			{
				if ((lib = LoadLibrary(L"JA_Asm_Dll.dll")) != NULL)
				{
					myFunc = (subtractionAsm)GetProcAddress(lib, "subtractionAsm");

					if (myFunc != NULL)
					{
						cout << (DWORD)(myFunc()) << endl;
					}

					FreeLibrary(lib);
				}

				fstream outFile;
				outFile.open("wynik.txt", ios::out);
				if (outFile.good()) {
					cout << "Saving matrix after subtraction: " << endl;
					for (int i = 0; i < numberOfRows; i++) {
						for (int j = 0; j < numberOfColumns; j++) {
							outFile << differentialMatrix[i][j] << " ";
						}
					}
				}
				else {
					std::cout << "Output File ERROR";
				}
				outFile.close();

			}
			else 
			{
				cout << "First argument is invalid. You should write cpp for using function create in C++ or asm for function in assembler" << endl;
			}

			inFile.close();
		}
		else 
		{
			cout << " File was not correctly opened" << endl;
		}	
	}
	else
	{
		cout << "Wrong number of parameters." << endl;
		cout << "First is for choosing, which function user want to use c++(cpp) or assember(asm)" << endl;
		cout << "Second is name of input file with its extension" << endl;
		cout << "Third is number of rows in matrixes" << endl;
		cout << "Fourth is is number of columns in matrixes" << endl;
		cout << "Fifth is optional and this is number of threads" << endl;
	}

	t = clock() - t;
	cout << "Time: " << t << " ms" << endl;

	system("PAUSE");
	return 0;
}
