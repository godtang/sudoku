// sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

void exclusions(int iCol, int iRow);
bool checkUnknown();

char sodukuInit[9][9] = { 
	{ 0, 6, 1, 0, 3, 0, 0, 2, 0 },
	{ 0, 5, 0, 0, 0, 8, 1, 0, 7 },
	{ 0, 0, 0, 0, 0, 7, 0, 3, 4 },
	{ 0, 0, 9, 0, 0, 6, 0, 7, 8 },
	{ 0, 0, 3, 2, 7, 9, 5, 0, 0 },
	{ 5, 7, 0, 3, 0, 0, 9, 0, 2 },
	{ 1, 9, 0, 7, 6, 0, 0, 0, 0 },
	{ 8, 0, 2, 4, 0, 0, 0, 6, 0 },
	{ 6, 4, 0, 0, 1, 0, 2, 5, 0 }
};


void showSoduku()
{
	printf("--------------------------\n");
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			printf("%d ", sodukuInit[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");
	return;
}


void algorithm()
{
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			char iPos = sodukuInit[i][j];
			if (0 == iPos)
			{
				exclusions(i, j);
			}
		}
	}
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	showSoduku();
	for (size_t i = 0; i < 1000; i++)
	{
		algorithm();
		if (checkUnknown())
		{
			printf("%d times over\n", i);
			break;
		}
	}
	return 0;
}


void exclusions(int iCol, int iRow)
{
	char iExclusions[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (size_t i = 0; i < 9; i++)
	{
		if (0 != sodukuInit[iCol][i])
		{
			iExclusions[sodukuInit[iCol][i] - 1] = 0;
		}
		//printf("%d ", pSoduku[iCol * 9 + i]);
	}
	//printf("\n");


	for (size_t j = 0; j < 9; j++)
	{
		if (0 != sodukuInit[j][iRow])
		{
			iExclusions[sodukuInit[j][iRow] - 1] = 0;
		}
		//printf("%d ", pSoduku[j * 9 + iRow]);
	}
	//printf("\n");

	int iRemain;
	int iUniqCount = 0;
	for (size_t k = 0; k < 9; k++)
	{
		if (0 != (int)iExclusions[k])
		{
			iRemain = (int)iExclusions[k];
			iUniqCount++;
		}
	}

	if (1 == iUniqCount)
	{
		printf("iCol = %d, iRow = %d, algorithm = %d\n", iCol + 1, iRow + 1, iRemain);
		sodukuInit[iCol][iRow] = iRemain;
		//Sleep(15000);
		showSoduku();
	}

	return;
}

void exclusions(char** pSoduku, int* pExclusions, int iCol, int iRow)
{
	return;
}

bool checkUnknown()
{
	int iUnknown = 0;
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			if(0 == sodukuInit[i][j])
			{
				iUnknown++;
			}
		}
	}
	printf("iUnknown = %d\n", iUnknown);
	if (0 == iUnknown)
	{
		return true;
	}
	else
	{
		return false;
	}
}

