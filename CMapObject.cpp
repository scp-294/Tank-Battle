#include "CMapObject.h"

int CMapObject::mArr[Area_X][Console_Y] = { 0 };//ȫ����ʼ��Ϊ�յ�
void CMapObject::InitArea()
{
	int i, j;
	//�߿�
	for (i = 0;i < Area_X;i++)
		for (j = 0;j < Area_Y;j++)
			if (i == 0 || j == 0 || (i == Area_X - 1) || (j == Area_Y - 1))
				mArr[i][j] = ��ʯ;
	//��ͼ��ߵ���ʯ 
	for (i = 22; i <= 30; i++)
		for (j = 4; j <= 7; j++)
			mArr[i][j] = ��ʯ;
	//��ͼ�ұߵ���ʯ
	for (i = 29; i <= 33; i++)
		for (j = 42; j <= 44; j++)
			mArr[i][j] = ��ʯ;
	//��ͼ��ߵ�ľ��
	for (i = 3; i <= 12; i++)
		for (j = 7; j <= 9; j++)
			mArr[i][j] = ľ��;
	//��ͼ�ұߵ�ľ��
	for (i = 3; i <= 12; i++)
		for (j = 33; j <= 35; j++)
			mArr[i][j] = ľ��;
	//��ͼ���µ�ľ��
	for (i = 25; i <= 28; i++)
		for (j = 38; j <= 44; j++)
			mArr[i][j] = ľ��;
	//�ݵ�
	for (i = 20; i <= 28; i++)
		for (j = 16; j <= 22; j++)
			mArr[i][j] = �ݵ�;
	for (i = 20; i <= 28; i++)
		for (j = 25; j <= 32; j++)
			mArr[i][j] = �ݵ�;
	for (i = 22; i <= 28; i++)
		for (j = 23; j <= 24; j++)
			mArr[i][j] = �ݵ�;
	for (i = 29; i <= 33; i++)
		for (j = 20; j <= 28; j++)
			mArr[i][j] = �ݵ�;
	//�ұ߹���ͷ����߿�
	i = 0;
	for (j = Area_Y; j < 70; j++)
		mArr[i][j] = ��ʯ;
	i = 21;
	for (j = Area_Y; j < 70; j++)
		mArr[i][j] = ��ʯ;
	i = Area_X - 1;
	for (j = Area_Y; j < 70; j++)
		mArr[i][j] = ��ʯ;
	j = Console_Y - 1;
	for(i=0; i<42; i++)
		mArr[i][j] = ��ʯ;
}

void CMapObject::DrawArea()
{
	for (int i = 0;i < Area_X;i++)
	{
		for (int j = 0;j < Console_Y;j++)
		{
			if (mArr[i][j] == ��ʯ)
				draw.PrintChar(j, i, "��", 8);
			else if (mArr[i][j] == ľ��)
				draw.PrintChar(j, i, "��", 14);
			else if (mArr[i][j] == �ݵ�)
				draw.PrintChar(j, i, "��", 10);
		}
	}
}

void CMapObject::DrawLawn()
{
	int i, j;
	//�ݵ�
	for (i = 20; i <= 28; i++)
		for (j = 16; j <= 22; j++)
			mArr[i][j] = �ݵ�;
	for (i = 20; i <= 28; i++)
		for (j = 25; j <= 32; j++)
			mArr[i][j] = �ݵ�;
	for (i = 22; i <= 28; i++)
		for (j = 23; j <= 24; j++)
			mArr[i][j] = �ݵ�;
	for (i = 29; i <= 33; i++)
		for (j = 20; j <= 28; j++)
			mArr[i][j] = �ݵ�;
	for (int i = 0;i < Area_X;i++)
	{
		for (int j = 0;j < Area_Y;j++)
		{
			if (mArr[i][j] == �ݵ�)
				draw.PrintChar(j, i, "��", 10);
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
	draw.PrintChar(51, 4, "�Ʒֹ���", 3);
	draw.PrintChar(51, 6, "(1) ��ʼ5��", 3);
	draw.PrintChar(51, 8, "(2) ����һ��ľ��+1", 3);
	draw.PrintChar(51, 10, "(3) ����һ���ӵ�-0.5", 3);
	draw.PrintChar(51, 12, "(4) ����һ��̹��+5", 3);
	draw.PrintChar(51, 14, "(5) 0��ʱ��Ϸʧ��", 3);
	draw.PrintChar(51, 16, "(6) ���Ͻ�ʣ�Լ�ʱ��Ϸ�ɹ�", 3);
	draw.PrintChar(51, 18, "(7) ���ӵ�����HP-1,�÷�-1", 3);
}

void CMapObject::GameOver(bool flag)
{
	if (flag==true)
		draw.PrintChar(54, 32, "YOU LOST��", 12);
	else
		draw.PrintChar(54, 32, "YOU WIN��", 12);
	draw.PrintChar(54, 34, "��Ϸ������", 12);
}
