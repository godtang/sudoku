// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "stdafx.h"

#include <windows.h>

void UniqueMethod(int iCol, int iRow);
bool checkUnknown();
void exclusions();
bool ConfirmNumber(int iCol, int iRow, int iNumber);
void possibility(char* pSrc[9][9]);
void ReCalcCannotbe(char* pMaybe[9][9], char* pCannotbe[9][9]);
void ReCalcCannotbe();
void ConfirmPossibility(char* pSrc[9][9]);
bool MaybeNumber(int iCol, int iRow, int iNumber);
bool CannotbeNumber(int iCol, int iRow, int iNumber);

void ShowCannotbe();
void ResetCannotbe();
void ConfirmByCannotbe();
bool ConfirmByCannotbe(int iCol, int iRow, int iNumber);

bool CheckSudodu();

void Surmise();



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
