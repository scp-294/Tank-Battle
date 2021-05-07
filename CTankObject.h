#pragma once
#include "CBaseObject.h"
#include "CMapObject.h"
#include <time.h>
#include <vector>
using std::vector;

#define KEYDOWN2(vk_code) ((GetAsyncKeyState(vk_code) & 0x0001))

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

class CTankObject :
    public CBaseObject
{
public:
    CTankObject(int x, int y, int dir, int color, int type, int hp);
	//填弹CD
	bool IsCreateTime();
	//画坦克
	void DrawObjtect();
	//擦除坦克
	void ClsObjtect();
	//碰撞判断，坦克
	int JudCollision();
	//得到地图中【x, y】的数据
	int getFlag(int x, int y);
	//判断是否可以移动
	bool IsMoveTime();
	//判断是否可以开火
	bool IsFire();
	//移动坦克
    void MoveTank(int dir);
    int GetX();
    int GetY();
    int GetD();
	int GetHP();
	//扣血
	void ReduceHp();
	//扣分
	void ReduceSorce(int recSorce);
	//阵营
	int GetType();
	//颜色
	int GetColor();
	//得分，初始5
	float sorce;
private:
	//坐标
	int TankX;
	int TankY;
	//下个位置临时中心点坐标
	int tempX;
	int tempY;
	//方向
	int nDir;
	//生命值
	int HP;
	//是否开火
	bool m_isFire;
	//坦克颜色
	int TankColor;
	//坦克类型，分辨敌我
	int m_type;

	clock_t CreateClock;//子弹产生时间
	int CreateSpeed=300;//装填速度
	clock_t tLastClock;//坦克刷新时间

	//坦克图像
	char g_TankShape[4][3][3] = {
	{
		{ 0, 1, 0 },		// 方向向上的坦克 
		{ 1, 1, 1 },
		{ 1, 0, 1 },
	},
	{						// 方向向下的坦克 
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 1, 0 },
	},
	{						// 方向向左的坦克
		{ 0, 1, 1 },
		{ 1, 1, 0 },
		{ 0, 1, 1 },
	},
	{						// 方向向右的坦克
		{ 1, 1, 0 },
		{ 0, 1, 1 },
		{ 1, 1, 0 },
	}
	};
	CMapObject* pMap;
};

