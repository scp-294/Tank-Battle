#pragma once
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
class CDrawObject
{
public:
	void PrintChar(int x, int y, const char* pszChar, WORD wArr);
	int GetOperatio();
};

