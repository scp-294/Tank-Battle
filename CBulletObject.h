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
	//�����ӵ�
	CBulletObject MakeBullet(CTankObject TankObj);
	//�ƶ��ӵ�
	void MoveBullet(vector<CTankObject>& TankObj);
	//���ӵ�
	void DrawObjtect();
	//���ӵ�
	void ClsObjtect();
	//�ж���ײ-�ӵ�
	int JudCollision();
	int GetX();
	int GetY();
	//�ӵ��Ƿ����
	bool IsLive();
	//�ж��Ƿ�����ƶ�
	bool IsMoveTime();
	// == ���أ������ж��ӵ�ײ��̹��
	bool operator==(CTankObject& Tankobj);
	// = ���أ����ڴ����ӵ�
	bool operator=(CTankObject Tankobj);

private:
	int x;
	int y;
	int dir;
	bool life;
	int MoveSpeed;//�ƶ��ٶ�
	int m_type;//�ӵ���Ӫ
	clock_t MoveClock;//�ƶ�ʱˢ�µ�ʱ��
	
	CMapObject* pMap;
};

