#include <iostream>
#include "CGameObject.h"
int main()
{
    //禁止控制台最大化
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    DestroyMenu(hMenu);
    ReleaseDC(hWnd, NULL);

	system("title 坦克大战");
	system("mode con cols=100 lines=42");

    Interface iface;
    char ch = _getch();
    if (ch == '1')
    {
        CGameObject obj(ch);

        CDrawObject draw;
        draw.PrintChar(54, 36, "再来一局吗？Y", 12);
        while(!(KEYDOWN('y') || KEYDOWN('Y')))
        {
            ch = '1';
        }
    }

    return 0;
}


