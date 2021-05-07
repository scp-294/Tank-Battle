#include "CDrawObject.h"

//�ú�����XY��ͨ���෴�������е��øú�����λ�ã�[x][y]��д��(y, x)
void CDrawObject::PrintChar(int x, int y, const char* pszChar, WORD wArr)
{
	// ���ù������
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;	// �Ƿ���ʾ���
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	// ��������
	COORD loc;
	loc.X = x * 2; // x��ֵ��Wide��2��
	loc.Y = y;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wArr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	printf(pszChar); //��ӡʱ��Ҫע����Щ�����ַ���ռ�����ֽ�
}

//�����̰���
int CDrawObject::GetOperatio()
{
	if (_kbhit())
	{
		return _getch();
	}
	return 0;
}
