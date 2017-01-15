#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <process.h>														
#include <cstdlib>								
#include "../JA_Cpp_Dll/Dll.h"

using namespace std;

typedef DWORD(*subtractionAsm)();
int index = 0;
int numberOfThreads = 0;
__int16 **Matrix = NULL;
__int16 **secondMatrix = NULL;

int numberOfThreadsFunction()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	return sysinfo.dwNumberOfProcessors;
}

void __cdecl ThreadProcCpp(void * Args)
{
	int i = index++;
	for (int i = 0; i < numberOfThreads; i++)
	{
		subtraction( Matrix, secondMatrix, X, Y);
	}
	_endthread();
}

void __cdecl ThreadProcAsm(void * Args)
{
	int i = index++;

	_endthread();
}

int main(int argc, char* argv[])
{

	clock_t t;
	t = clock();
	subtractionAsm myFunc;
	HMODULE lib;

	if (argc >= 5) 
	{ 
		if (argc = 6) 
		{ 
			numberOfThreads = stoi(argv[5]);
		}
		else 
		{
			numberOfThreads = numberOfThreadsFunction();
		}

		fstream inFile;
		inFile.open(argv[2], ios::in | ios::out);
		if (inFile.good() == true) 
		{

			int numberOfRows = stoi(argv[3]);
			int numberOfColumns = stoi(argv[4]);
			Matrix = new __int16 *[numberOfRows];
			secondMatrix = new __int16 *[numberOfRows];

			for (int i = 0; i < numberOfRows; i++)
			{
				Matrix[i] = new __int16[numberOfColumns];
				secondMatrix[i] = new __int16[numberOfColumns];
			}

			for (int i = 0; i < numberOfRows; i++)
				for (int j = 0; j < numberOfColumns; j++)
					inFile >> Matrix[i][j];
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
					for (int i = 0; i < numberOfRows; i++) {
						for (int j = 0; j < numberOfColumns; j++) {
							outFile << Matrix[i][j] << " ";
						}
					}
				}
				outFile.close();

			}
			inFile.close();
		}
	}

	t = clock() - t;
	cout << "Time: " << t << " ms" << endl;
	
	for (int i = 0; i < stoi(argv[3]); i++) 
	{
		delete(Matrix[i]);
		delete(secondMatrix[i]);
		Matrix[i] = NULL;
		secondMatrix[i] = NULL;
	}
	delete(Matrix);
	delete(secondMatrix);
	Matrix = NULL;
	secondMatrix = NULL;

	system("PAUSE");
	return 0;
}
