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
	//�CD
	bool IsCreateTime();
	//��̹��
	void DrawObjtect();
	//����̹��
	void ClsObjtect();
	//��ײ�жϣ�̹��
	int JudCollision();
	//�õ���ͼ�С�x, y��������
	int getFlag(int x, int y);
	//�ж��Ƿ�����ƶ�
	bool IsMoveTime();
	//�ж��Ƿ���Կ���
	bool IsFire();
	//�ƶ�̹��
    void MoveTank(int dir);
    int GetX();
    int GetY();
    int GetD();
	int GetHP();
	//��Ѫ
	void ReduceHp();
	//�۷�
	void ReduceSorce(int recSorce);
	//��Ӫ
	int GetType();
	//��ɫ
	int GetColor();
	//�÷֣���ʼ5
	float sorce;
private:
	//����
	int TankX;
	int TankY;
	//�¸�λ����ʱ���ĵ�����
	int tempX;
	int tempY;
	//����
	int nDir;
	//����ֵ
	int HP;
	//�Ƿ񿪻�
	bool m_isFire;
	//̹����ɫ
	int TankColor;
	//̹�����ͣ��ֱ����
	int m_type;

	clock_t CreateClock;//�ӵ�����ʱ��
	int CreateSpeed=300;//װ���ٶ�
	clock_t tLastClock;//̹��ˢ��ʱ��

	//̹��ͼ��
	char g_TankShape[4][3][3] = {
	{
		{ 0, 1, 0 },		// �������ϵ�̹�� 
		{ 1, 1, 1 },
		{ 1, 0, 1 },
	},
	{						// �������µ�̹�� 
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 1, 0 },
	},
	{						// ���������̹��
		{ 0, 1, 1 },
		{ 1, 1, 0 },
		{ 0, 1, 1 },
	},
	{						// �������ҵ�̹��
		{ 1, 1, 0 },
		{ 0, 1, 1 },
		{ 1, 1, 0 },
	}
	};
	CMapObject* pMap;
};

