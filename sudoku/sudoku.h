// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "stdafx.h"

#include <windows.h>

void UniqueMethod(int iCol, int iRow);
bool checkUnknown();
void exclusions();
bool ConfirmNumber(int iCol, int iRow, int iNumber);
void possibility(char* pSrc[9][9]);
void ShowPossibility(char* pMaybe[9][9], char* pCannotbe[9][9]);
void ShowPossibility();
void ConfirmPossibility(char* pSrc[9][9]);
bool MaybeNumber(int iCol, int iRow, int iNumber);
bool CannotbeNumber(int iCol, int iRow, int iNumber);

void ShowCannotbe();
void ResetCannotbe();
void ConfirmByCannotbe();
bool ConfirmByCannotbe(int iCol, int iRow, int iNumber);



// TODO:  在此处引用程序需要的其他头文件
