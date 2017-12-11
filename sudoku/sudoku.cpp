// sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

void UniqueMethod(int iCol, int iRow);
bool checkUnknown();
void exclusions();
bool ConfirmNumber(int iCol, int iRow, int iNumber);
void possibility(char* pSrc[9][9]);
void ShowPossibility(char* pMaybe[9][9], char* pCannotbe[9][9]);
void ConfirmPossibility(char* pSrc[9][9]);






char sodukuInit[9][9] = {
	{ 0, 0, 7, 0, 0, 0, 9, 0, 0 },
	{ 2, 0, 0, 5, 0, 7, 0, 0, 6 },
	{ 0, 8, 0, 1, 0, 4, 0, 7, 0 },
	{ 0, 4, 0, 0, 1, 0, 0, 3, 0 },
	{ 6, 0, 1, 0, 0, 0, 8, 0, 9 },
	{ 0, 9, 0, 0, 8, 0, 0, 6, 0 },
	{ 0, 5, 0, 8, 0, 9, 0, 1, 0 },
	{ 0, 1, 0, 6, 0, 3, 0, 0, 2 },
	{ 0, 0, 6, 0, 0, 0, 3, 0, 0 }
};

char sodukuInit2[9][9] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1 }
};


char sodukuInit3[9][9] = {
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
				UniqueMethod(i, j);
			}
		}
	}
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* sodukuMaybe[9][9];
	for (int iCol = 0; iCol < 9; iCol++)
	{
		for (int iRow = 0; iRow < 9; iRow++)
		{
			char* p = new char[9];
			for (size_t iMayValue = 0; iMayValue < 9; iMayValue++)
			{
				p[iMayValue] = iMayValue + 1;
			}
			sodukuMaybe[iCol][iRow] = p;
		}
	}
	char* sodukuCannotbe[9][9];
	for (int iCol = 0; iCol < 9; iCol++)
	{
		for (int iRow = 0; iRow < 9; iRow++)
		{
			char* p = new char[9];
			for (size_t iMayValue = 0; iMayValue < 9; iMayValue++)
			{
				p[iMayValue] = iMayValue + 1;
			}
			sodukuCannotbe[iCol][iRow] = p;
		}
	}
	showSoduku();
	ShowPossibility(sodukuMaybe, sodukuCannotbe);
	showSoduku();
	for (size_t i = 1; i < 1000; i++)
	{
		possibility(sodukuMaybe);
		ShowPossibility(sodukuMaybe, sodukuCannotbe);
		//algorithm();
		//exclusions();
		if (checkUnknown())
		{
			printf("%d times over\n", i);
			break;
		}
	}
	showSoduku();
	return 0;
}


void UniqueMethod(int iCol, int iRow)
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

	int iStartCol = iCol / 3;
	int iStartRow = iRow / 3;
	for (int i = 3 * iStartCol; i < 3 * iStartCol + 3; i++)
	{
		for (int j = 3 * iStartRow; j < 3 * iStartRow + 3; j++)
		{
			//printf("iCol = %d, iRow = %d checked iStartCol = %d, iStartRow = %d\n", iCol, iRow, i, j);
			if (0 != sodukuInit[j][iRow])
			{
				iExclusions[sodukuInit[j][iRow] - 1] = 0;
			}
		}
	}
	//printf("************************\n");
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

void exclusions()
{
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			if (0 == sodukuInit[i][j])
			{
				//Horizontal
				for (int iExcludeNumber = 1; iExcludeNumber <= 9; iExcludeNumber++)
				{
					showSoduku();
					if (ConfirmNumber(i, j, iExcludeNumber))
					{
						sodukuInit[i][j] = iExcludeNumber;
						//Sleep(15000);
						printf("iCol = %d, iRow = %d, algorithm = %d\n", i + 1, j + 1, iExcludeNumber);
						showSoduku();
						break;
					}
					else
					{
						//printf("%d,%d can not confirm %d\n", i, j, iExcludeNumber);
					}
				}
				//Vertical
				//Box
			}
		}
	}
	return;
}

int iCheck = 0;
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
		if (iCheck == iUnknown)
		{
			iCheck = iUnknown;
			return true;
		}
		else
		{
			iCheck = iUnknown;
			return false;
		}
	}
}

bool  ConfirmNumber(int iCol, int iRow, int iNumber)
{
	char szCanExcludeInnerHorizontal[9] = { 0 };
	printf("ready confirm %d,%d = %d\n", iCol, iRow, iNumber);
	for (int iHorizontal = 0; iHorizontal < 9; iHorizontal++)
	{
		/*if (iCol == iHorizontal)
		{
			printf("%d,%d is not needed confirm\n", iCol, iHorizontal);
			continue;
		}*/
		printf("begin horizontal %d\n", iHorizontal);
		bool bIsContinue = false;
		if (0 == sodukuInit[iCol][iHorizontal])
		{
			char szCanExcludeInnerVertical[9] = { 0 };
			for (int iVertical = 0; iVertical < 9; iVertical++)
			{
				if (iRow == iVertical && iCol == iHorizontal)
				{
					bIsContinue = true;
					printf("%d,%d is not needed confirm\n", iRow, iCol);
					break;
				}
				if (iNumber == sodukuInit[iVertical][iHorizontal])
				{
					printf("%d,%d can exclude %d\n", iVertical, iHorizontal, iNumber);
					szCanExcludeInnerVertical[iHorizontal] = 1;
					break;
				}
				else
				{
					printf("%d,%d can not exclude %d, it's %d\n", iVertical, iHorizontal, iNumber, sodukuInit[iVertical][iHorizontal]);
					int iBreakPoint = 1;
				}
			}
			if (bIsContinue)
			{
				continue;
			}
			for (int i = 0; i < 9; i++)
			{
				if (1 == szCanExcludeInnerVertical[i] && i != iCol)
				{
					printf("vertical %d can exclude %d\n", iHorizontal, iNumber);
					szCanExcludeInnerHorizontal[iHorizontal] = 1;
					break;
				}
			}
			if (0 == szCanExcludeInnerHorizontal[iHorizontal])
			{
				printf("vertical %d can not exclude %d\n", iHorizontal, iNumber);
				return false;
			}
		}
		else
		{
			printf("%d,%d can exclude %d ,actual value is %d \n", iCol, iHorizontal, iNumber, sodukuInit[iCol][iHorizontal]);
			szCanExcludeInnerHorizontal[iHorizontal] = 1;
		}
	}
	for (size_t i = 0; i < 9; i++)
	{
		if (0 == szCanExcludeInnerHorizontal[i] && i != iCol)
		{
			printf("%d,%d can not confirm %d\n", iCol, iRow, iNumber);
			return false;
		}
	}
	return true;
}


void possibility(char* pSrc[9][9])
{
	for (int iCol = 0; iCol < 9; iCol++)
	{
		for (int iRow = 0; iRow < 9; iRow++)
		{
			char* pTemp = pSrc[iCol][iRow];
			if (0 == sodukuInit[iCol][iRow])
			{
				for (size_t i = 0; i < 9; i++)
				{
					if (0 != sodukuInit[iCol][i])
					{
						pTemp[sodukuInit[iCol][i] - 1] = 0;
					}
					//printf("%d ", pSoduku[iCol * 9 + i]);
				}
				//printf("\n");


				for (size_t j = 0; j < 9; j++)
				{
					if (0 != sodukuInit[j][iRow])
					{
						pTemp[sodukuInit[j][iRow] - 1] = 0;
					}
					//printf("%d ", pSoduku[j * 9 + iRow]);
				}
				//printf("\n");

				int iStartCol = iCol / 3;
				int iStartRow = iRow / 3;
				for (int i = 3 * iStartCol; i < 3 * iStartCol + 3; i++)
				{
					for (int j = 3 * iStartRow; j < 3 * iStartRow + 3; j++)
					{
						//printf("iCol = %d, iRow = %d checked iStartCol = %d, iStartRow = %d\n", iCol, iRow, i, j);
						if (0 != sodukuInit[j][iRow])
						{
							pTemp[sodukuInit[j][iRow] - 1] = 0;
						}
					}
				}
			}
			else
			{
				for (size_t i = 0; i < 9; i++)
				{
					pTemp[i] = 0;
				}
			}
		}
	}
}

void ShowPossibility(char* pMaybe[9][9], char* pCannotbe[9][9])
{
	for (int iCol = 0; iCol < 9; iCol++)
	{
		for (int iRow = 0; iRow < 9; iRow++)
		{
			printf("%d,%d ", iCol, iRow);
			if (0 != sodukuInit[iCol][iRow])
			{
				printf("must be %d", sodukuInit[iCol][iRow]);
			}
			else
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

				int iStartCol = iCol / 3;
				int iStartRow = iRow / 3;
				for (int i = 3 * iStartCol; i < 3 * iStartCol + 3; i++)
				{
					for (int j = 3 * iStartRow; j < 3 * iStartRow + 3; j++)
					{
						//printf("iCol = %d, iRow = %d checked iStartCol = %d, iStartRow = %d\n", iCol, iRow, i, j);
						if (0 != sodukuInit[j][iRow])
						{
							iExclusions[sodukuInit[j][iRow] - 1] = 0;
						}
					}
				}
				//printf("************************\n");
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
					printf("must be %d", sodukuInit[iCol][iRow]);;
				}
				else
				{
					//printf("may be ");
					for (size_t i = 0; i < 9; i++)
					{
						if (0 != (int)iExclusions[i])
						{

							//printf("%d,", iExclusions[i]);
							iUniqCount++;
							char* pTempMaybe = pMaybe[iCol][iRow];
							pTempMaybe[i] = 0;
							char* pTempCannotbe = pCannotbe[iCol][iRow];
							pTempCannotbe[i] = iExclusions[i];
						}
						else
						{
							char* pTempMaybe = pMaybe[iCol][iRow];
							pTempMaybe[i] = iExclusions[i];
							char* pTempCannotbe = pCannotbe[iCol][iRow];
							pTempCannotbe[i] = 0;
						}
					}
					char* pTempMaybe = pMaybe[iCol][iRow];
					char* pTempCannotbe = pCannotbe[iCol][iRow];
					int jjjjjjjj = 0;
				}
			}
			printf("\n");
		}
	}
	for (int iCol = 0; iCol < 9; iCol++)
	{
		for (int iRow = 0; iRow < 9; iRow++)
		{
			if (0 != sodukuInit[iCol][iRow])
			{
				printf("%d,%d ", iCol, iRow);
				printf("may be ");
				char* pTempMaybe = pMaybe[iCol][iRow];
				for (size_t i = 0; i < 9; i++)
				{
					if (0 != pTempMaybe[i])
					{
						printf("%d,", pTempMaybe[i]);
					}
				}
				char* pTempCannotbe = pCannotbe[iCol][iRow];
				printf("; can not be ");
				for (size_t i = 0; i < 9; i++)
				{
					if (0 != pTempCannotbe[i])
					{
						printf("%d,", pTempCannotbe[i]);
					}
				}
				printf("\n");
			}			
		}
	}
	for (int iCol = 0; iCol < 9; iCol++)
	{
		for (int iRow = 0; iRow < 9; iRow++)
		{
			char* pTemp = pMaybe[iCol][iRow];
			printf("%d,%d ", iCol, iRow);
			if (0 != sodukuInit[iCol][iRow])
			{
				printf("must be %d", sodukuInit[iCol][iRow]);
			}
			else
			{
				printf("maybe ", iCol, iRow);
				for (size_t iMayValue = 0; iMayValue < 9; iMayValue++)
				{
					if (0 != pTemp[iMayValue])
					{
						printf("%d,", pTemp[iMayValue]);
					}
				}
			}
			printf("\n");
		}
	}    
}


void ConfirmPossibility(char* pSrc[9][9])
{

}









