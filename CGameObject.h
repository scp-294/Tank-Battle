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
	//��ʼ��̹����������Ϣ
	void InitTankInfo();
	//�ƶ�����
	void MoveSelfALLY();
	//��ü��̲���
	int GetOption();
	//��ӡ����
	void PrintSorce();
private:
	//��ͼ����
	CMapObject m_MapObj;
	//̹������
	vector< CTankObject> m_vecTank;
	//�ӵ�����
	vector< CBulletObject> m_vecBullet;

	CDrawObject draw;
	//A���㷨�Զ�Ѱ·
	//Astar aster;
};

