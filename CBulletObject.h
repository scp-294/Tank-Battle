#pragma once
#include "CBaseObject.h"
#include "CMapObject.h"
#include <vector>
#include <time.h>
#include "CTankObject.h"
using std::vector;

class CBulletObject :
    public CBaseObject
{
public:
	//产生子弹
	CBulletObject MakeBullet(CTankObject TankObj);
	//移动子弹
	void MoveBullet(vector<CTankObject>& TankObj);
	//画子弹
	void DrawObjtect();
	//擦子弹
	void ClsObjtect();
	//判断碰撞-子弹
	int JudCollision();
	int GetX();
	int GetY();
	//子弹是否存在
	bool IsLive();
	//判断是否可以移动
	bool IsMoveTime();
	// == 重载，用于判断子弹撞击坦克
	bool operator==(CTankObject& Tankobj);
	// = 重载，用于创造子弹
	bool operator=(CTankObject Tankobj);

private:
	int x;
	int y;
	int dir;
	bool life;
	int MoveSpeed;//移动速度
	int m_type;//子弹阵营
	clock_t MoveClock;//移动时刷新的时间
	
	CMapObject* pMap;
};

