#include "CGameObject.h"

CGameObject::CGameObject(char ch)
{
	switch (ch)
	{
	case '1'://开始新游戏
		system("cls");
		system("mode con cols=140 lines=42");
		PlaySoundA("..\\sound\\开始游戏.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		//初始化地图
		m_MapObj.InitArea();
		m_MapObj.DrawArea();
		m_MapObj.PrintRule();
		//操作坦克
		InitTankInfo();
		MoveSelfALLY();
		break;
	case '2'://继续游戏，目前没有
		break;
	}

}

CGameObject::~CGameObject(){}

void CGameObject::InitTankInfo()
{
	//己方坦克，横纵坐标，方向，颜色，类型（分辨敌我）
	CTankObject tTank0(3, 3, DOWN, 2 | 8, 9, 3);
	m_vecTank.push_back(tTank0);

	//敌方坦克
	CTankObject tTank1(3, 42, DOWN, 3 | 8, 8, 3);
	m_vecTank.push_back(tTank1);
	CTankObject tTank2(38, 42, UP, 12 | 8, 8, 5);
	m_vecTank.push_back(tTank2);

	for (int i = 0; i < m_vecTank.size(); i++)
	{
		m_vecTank[i].DrawObjtect();
	}
}

void CGameObject::MoveSelfALLY()
{
	CBulletObject tBullet;
	//当自己的坦克HP不为0,场上坦克数量不为1时继续游戏
	while ((m_vecTank[0].sorce > 0) && (m_vecTank[0].GetHP() != 0) && (m_vecTank.size() != 1))
	{
		//移动坦克
		//监测键盘是否按下
		int m_code = GetOption();
		if (m_code != -1)
		{
			if (m_vecTank[0].IsMoveTime())
				m_vecTank[0].MoveTank(m_code);

			if (m_vecTank[0].IsFire())
			{
				m_vecTank[0].sorce -= 0.5;
				//将子弹加入队列中
				tBullet = tBullet.MakeBullet(m_vecTank[0]);
				m_vecBullet.push_back(tBullet);
				PrintSorce();
			}
		}

		//移动子弹
		for (int i = 0; i < m_vecBullet.size(); i++)
		{
			//如果撞到岩石，该子弹销毁
			if (m_vecBullet[i].IsLive() == false)
			{
				m_vecBullet.erase(m_vecBullet.begin() + i);
				i--;
				continue;
			}
			// 移动子弹的时间是否到了
			if (m_vecBullet[i].IsMoveTime())
			{
				// 移动子弹
				m_vecBullet[i].MoveBullet(m_vecTank);
				PrintSorce();
			}
		}

		//当HP不为0时，随机移动敌方坦克
		srand((unsigned)time(NULL));
		for (int i = 1; i < m_vecTank.size(); i++)
		{
			if (m_vecTank[i].GetHP() != 0)
			{
				if (m_vecTank[i].IsMoveTime())
				{
					int e_code = rand() % (4 - 0 + 1) + 0;//生成[0,4]的随机数
					m_vecTank[i].MoveTank(e_code);
				}

				if (m_vecTank[i].IsFire())
				{
					//将子弹加入队列中
					tBullet = tBullet.MakeBullet(m_vecTank[i]);
					m_vecBullet.push_back(tBullet);
				}
			}
			else
			{
				m_vecTank[0].sorce += 5;
				//销毁该坦克
				m_vecTank[i].ClsObjtect();
				m_vecTank.erase(m_vecTank.begin() + i);
			}
		}

		//刷新草地
		m_MapObj.DrawLawn();
		//刷新分数
		PrintSorce();
	}
	//游戏结束
	PrintSorce();
	if (m_vecTank[0].GetHP() == 0 || m_vecTank[0].sorce <= 0)
	{
		m_MapObj.GameOver(true);
		PlaySoundA("..\\sound\\失败.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	}
	else
	{
		m_MapObj.GameOver(false);
		PlaySoundA("..\\sound\\胜利.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	}
}

int CGameObject::GetOption()
{
	if (KEYDOWN('w') || KEYDOWN('W'))
	{
		return UP;
	}
	if (KEYDOWN('s') || KEYDOWN('S'))
	{
		return DOWN;
	}
	if (KEYDOWN('a') || KEYDOWN('A'))
	{
		return LEFT;
	}
	if (KEYDOWN('d') || KEYDOWN('D'))
	{
		return RIGHT;
	}
	if (KEYDOWN('f') || KEYDOWN('F'))
	{
		return FIRE;
	}
	//没有键盘按下
	return -1;
}

void CGameObject::PrintSorce()
{ 
	char str[20], hp0[10], hp1[10], hp2[10];

	if (m_vecTank[0].sorce >= 0)
	{
		sprintf_s(str, "当前分数：%.1lf", m_vecTank[0].sorce);
		draw.PrintChar(54, 24, str, 12);
	}

	sprintf_s(hp0, "己方HP：%d", m_vecTank[0].GetHP());
	draw.PrintChar(54, 26, hp0, 10);

	if (m_vecTank.size() > 1)
	{
		sprintf_s(hp1, "敌方HP：%d", m_vecTank[1].GetHP());
		draw.PrintChar(54, 28, hp1, 3);
	}

	if (m_vecTank.size() > 2)
	{
		sprintf_s(hp2, "敌方HP：%d", m_vecTank[2].GetHP());
		draw.PrintChar(54, 30, hp2, 3);
	}
	else
		draw.PrintChar(54, 30, "             ", 8);

}
