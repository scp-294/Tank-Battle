#pragma once
#include "CDrawObject.h"
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
class CBaseObject
{
public:
	virtual void DrawObjtect() = 0;
	virtual void ClsObjtect() = 0;
	virtual int JudCollision() = 0;
	CDrawObject draw;
};

