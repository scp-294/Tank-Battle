#pragma once

#include "CDrawObject.h"

#define �յ� 0
#define ��ʯ 1
#define �ӵ� 2
#define ľ�� 3
#define �ݵ� 4
#define ̹�� 5
//��ͼ����ʾ̹����ɫ������̹�˺���Ϊײ��ʱ�ķ���ֵ

//��Ϸ��ͼ��С
#define Area_X   42//��
#define Area_Y   50//��

//����̨��С��X���ͼ��ͬ
#define Console_Y  70

#define   UP     0
#define   DOWN   1
#define   LEFT   2
#define   RIGHT  3
#define   FIRE   4

class CMapObject
{
public:
	//��ʼ����ͼ
	void InitArea();
	//������ͼ
	void DrawArea();
	//ˢ�²ݵ�
	void DrawLawn();
	//���õ�ͼָ��λ�õ�����
	void setMapValue(int nPosX, int nPosY, int nValue);
	//�õ���ͼ�и�λ�õ�����
	int getMApValue(int nPosX, int nPosY);
	//��ӡ��Ϸ����
	void PrintRule();
	//��ӡ��Ϸ���
	void GameOver(bool flag);

private:
	//����̨��С
	static int mArr[Area_X][Console_Y];
	CDrawObject draw;
};

