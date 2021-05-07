#include "CMapObject.h"

int CMapObject::mArr[Area_X][Console_Y] = { 0 };//全部初始化为空地
void CMapObject::InitArea()
{
	int i, j;
	//边框
	for (i = 0;i < Area_X;i++)
		for (j = 0;j < Area_Y;j++)
			if (i == 0 || j == 0 || (i == Area_X - 1) || (j == Area_Y - 1))
				mArr[i][j] = 岩石;
	//地图左边的岩石 
	for (i = 22; i <= 30; i++)
		for (j = 4; j <= 7; j++)
			mArr[i][j] = 岩石;
	//地图右边的岩石
	for (i = 29; i <= 33; i++)
		for (j = 42; j <= 44; j++)
			mArr[i][j] = 岩石;
	//地图左边的木板
	for (i = 3; i <= 12; i++)
		for (j = 7; j <= 9; j++)
			mArr[i][j] = 木板;
	//地图右边的木板
	for (i = 3; i <= 12; i++)
		for (j = 33; j <= 35; j++)
			mArr[i][j] = 木板;
	//地图右下的木板
	for (i = 25; i <= 28; i++)
		for (j = 38; j <= 44; j++)
			mArr[i][j] = 木板;
	//草地
	for (i = 20; i <= 28; i++)
		for (j = 16; j <= 22; j++)
			mArr[i][j] = 草地;
	for (i = 20; i <= 28; i++)
		for (j = 25; j <= 32; j++)
			mArr[i][j] = 草地;
	for (i = 22; i <= 28; i++)
		for (j = 23; j <= 24; j++)
			mArr[i][j] = 草地;
	for (i = 29; i <= 33; i++)
		for (j = 20; j <= 28; j++)
			mArr[i][j] = 草地;
	//右边规则和分数边框
	i = 0;
	for (j = Area_Y; j < 70; j++)
		mArr[i][j] = 岩石;
	i = 21;
	for (j = Area_Y; j < 70; j++)
		mArr[i][j] = 岩石;
	i = Area_X - 1;
	for (j = Area_Y; j < 70; j++)
		mArr[i][j] = 岩石;
	j = Console_Y - 1;
	for(i=0; i<42; i++)
		mArr[i][j] = 岩石;
}

void CMapObject::DrawArea()
{
	for (int i = 0;i < Area_X;i++)
	{
		for (int j = 0;j < Console_Y;j++)
		{
			if (mArr[i][j] == 岩石)
				draw.PrintChar(j, i, "■", 8);
			else if (mArr[i][j] == 木板)
				draw.PrintChar(j, i, "■", 14);
			else if (mArr[i][j] == 草地)
				draw.PrintChar(j, i, "■", 10);
		}
	}
}

void CMapObject::DrawLawn()
{
	int i, j;
	//草地
	for (i = 20; i <= 28; i++)
		for (j = 16; j <= 22; j++)
			mArr[i][j] = 草地;
	for (i = 20; i <= 28; i++)
		for (j = 25; j <= 32; j++)
			mArr[i][j] = 草地;
	for (i = 22; i <= 28; i++)
		for (j = 23; j <= 24; j++)
			mArr[i][j] = 草地;
	for (i = 29; i <= 33; i++)
		for (j = 20; j <= 28; j++)
			mArr[i][j] = 草地;
	for (int i = 0;i < Area_X;i++)
	{
		for (int j = 0;j < Area_Y;j++)
		{
			if (mArr[i][j] == 草地)
				draw.PrintChar(j, i, "■", 10);
		}
	}
}

void CMapObject::setMapValue(int nPosX, int nPosY, int nValue)
{
	mArr[nPosX][nPosY] = nValue;
}

int CMapObject::getMApValue(int nPosX, int nPosY)
{
	int t= mArr[nPosX][nPosY];
	return mArr[nPosX][nPosY];
}

void CMapObject::PrintRule()
{
	draw.PrintChar(51, 4, "计分规则：", 3);
	draw.PrintChar(51, 6, "(1) 初始5分", 3);
	draw.PrintChar(51, 8, "(2) 击毁一块木板+1", 3);
	draw.PrintChar(51, 10, "(3) 发射一颗子弹-0.5", 3);
	draw.PrintChar(51, 12, "(4) 击毁一辆坦克+5", 3);
	draw.PrintChar(51, 14, "(5) 0分时游戏失败", 3);
	draw.PrintChar(51, 16, "(6) 场上仅剩自己时游戏成功", 3);
	draw.PrintChar(51, 18, "(7) 被子弹击中HP-1,得分-1", 3);
}

void CMapObject::GameOver(bool flag)
{
	if (flag==true)
		draw.PrintChar(54, 32, "YOU LOST！", 12);
	else
		draw.PrintChar(54, 32, "YOU WIN！", 12);
	draw.PrintChar(54, 34, "游戏结束！", 12);
}
