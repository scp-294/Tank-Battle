#pragma once

#include "CDrawObject.h"

#define 空地 0
#define 岩石 1
#define 子弹 2
#define 木板 3
#define 草地 4
#define 坦克 5
//地图中显示坦克颜色，上述坦克宏作为撞击时的返回值

//游戏地图大小
#define Area_X   42//纵
#define Area_Y   50//横

//控制台大小，X与地图相同
#define Console_Y  70

#define   UP     0
#define   DOWN   1
#define   LEFT   2
#define   RIGHT  3
#define   FIRE   4

class CMapObject
{
public:
	//初始化地图
	void InitArea();
	//画出地图
	void DrawArea();
	//刷新草地
	void DrawLawn();
	//设置地图指定位置的数据
	void setMapValue(int nPosX, int nPosY, int nValue);
	//得到地图中该位置的数据
	int getMApValue(int nPosX, int nPosY);
	//打印游戏规则
	void PrintRule();
	//打印游戏结局
	void GameOver(bool flag);

private:
	//控制台大小
	static int mArr[Area_X][Console_Y];
	CDrawObject draw;
};

