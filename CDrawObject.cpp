#include "CDrawObject.h"

//该函数的XY与通常相反，故所有调用该函数的位置，[x][y]会写成(y, x)
void CDrawObject::PrintChar(int x, int y, const char* pszChar, WORD wArr)
{
	// 设置光标属性
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;	// 是否显示光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	// 设置坐标
	COORD loc;
	loc.X = x * 2; // x的值是Wide的2倍
	loc.Y = y;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wArr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	printf(pszChar); //打印时需要注意有些特殊字符是占两个字节
}

//监测键盘按下
int CDrawObject::GetOperatio()
{
	if (_kbhit())
	{
		return _getch();
	}
	return 0;
}
