#pragma once
#include "CMapObject.h"
#include "CTankObject.h"
#include "CBulletObject.h"
#include "CMapObject.h"
#include "Interface.h"
#include <vector>
#include <stdlib.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")

using std::vector;

#define KEYDOWN2(vk_code) ((GetAsyncKeyState(vk_code) & 0x0001))

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

class CGameObject
{
public:
	CGameObject(char ch);
	~CGameObject();
	//初始化坦克向量表信息
	void InitTankInfo();
	//移动物体
	void MoveSelfALLY();
	//获得键盘操作
	int GetOption();
	//打印分数
	void PrintSorce();
private:
	//地图对象
	CMapObject m_MapObj;
	//坦克向量
	vector< CTankObject> m_vecTank;
	//子弹向量
	vector< CBulletObject> m_vecBullet;

	CDrawObject draw;
	//A星算法自动寻路
	//Astar aster;
};

