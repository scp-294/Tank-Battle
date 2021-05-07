#include "CGameObject.h"

CGameObject::CGameObject(char ch)
{
	switch (ch)
	{
	case '1'://��ʼ����Ϸ
		system("cls");
		system("mode con cols=140 lines=42");
		PlaySoundA("..\\sound\\��ʼ��Ϸ.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		//��ʼ����ͼ
		m_MapObj.InitArea();
		m_MapObj.DrawArea();
		m_MapObj.PrintRule();
		//����̹��
		InitTankInfo();
		MoveSelfALLY();
		break;
	case '2'://������Ϸ��Ŀǰû��
		break;
	}

}

CGameObject::~CGameObject(){}

void CGameObject::InitTankInfo()
{
	//����̹�ˣ��������꣬������ɫ�����ͣ��ֱ���ң�
	CTankObject tTank0(3, 3, DOWN, 2 | 8, 9, 3);
	m_vecTank.push_back(tTank0);

	//�з�̹��
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
	//���Լ���̹��HP��Ϊ0,����̹��������Ϊ1ʱ������Ϸ
	while ((m_vecTank[0].sorce > 0) && (m_vecTank[0].GetHP() != 0) && (m_vecTank.size() != 1))
	{
		//�ƶ�̹��
		//�������Ƿ���
		int m_code = GetOption();
		if (m_code != -1)
		{
			if (m_vecTank[0].IsMoveTime())
				m_vecTank[0].MoveTank(m_code);

			if (m_vecTank[0].IsFire())
			{
				m_vecTank[0].sorce -= 0.5;
				//���ӵ����������
				tBullet = tBullet.MakeBullet(m_vecTank[0]);
				m_vecBullet.push_back(tBullet);
				PrintSorce();
			}
		}

		//�ƶ��ӵ�
		for (int i = 0; i < m_vecBullet.size(); i++)
		{
			//���ײ����ʯ�����ӵ�����
			if (m_vecBullet[i].IsLive() == false)
			{
				m_vecBullet.erase(m_vecBullet.begin() + i);
				i--;
				continue;
			}
			// �ƶ��ӵ���ʱ���Ƿ���
			if (m_vecBullet[i].IsMoveTime())
			{
				// �ƶ��ӵ�
				m_vecBullet[i].MoveBullet(m_vecTank);
				PrintSorce();
			}
		}

		//��HP��Ϊ0ʱ������ƶ��з�̹��
		srand((unsigned)time(NULL));
		for (int i = 1; i < m_vecTank.size(); i++)
		{
			if (m_vecTank[i].GetHP() != 0)
			{
				if (m_vecTank[i].IsMoveTime())
				{
					int e_code = rand() % (4 - 0 + 1) + 0;//����[0,4]�������
					m_vecTank[i].MoveTank(e_code);
				}

				if (m_vecTank[i].IsFire())
				{
					//���ӵ����������
					tBullet = tBullet.MakeBullet(m_vecTank[i]);
					m_vecBullet.push_back(tBullet);
				}
			}
			else
			{
				m_vecTank[0].sorce += 5;
				//���ٸ�̹��
				m_vecTank[i].ClsObjtect();
				m_vecTank.erase(m_vecTank.begin() + i);
			}
		}

		//ˢ�²ݵ�
		m_MapObj.DrawLawn();
		//ˢ�·���
		PrintSorce();
	}
	//��Ϸ����
	PrintSorce();
	if (m_vecTank[0].GetHP() == 0 || m_vecTank[0].sorce <= 0)
	{
		m_MapObj.GameOver(true);
		PlaySoundA("..\\sound\\ʧ��.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	}
	else
	{
		m_MapObj.GameOver(false);
		PlaySoundA("..\\sound\\ʤ��.wav", NULL, SND_ASYNC | SND_NODEFAULT);
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
	//û�м��̰���
	return -1;
}

void CGameObject::PrintSorce()
{ 
	char str[20], hp0[10], hp1[10], hp2[10];

	if (m_vecTank[0].sorce >= 0)
	{
		sprintf_s(str, "��ǰ������%.1lf", m_vecTank[0].sorce);
		draw.PrintChar(54, 24, str, 12);
	}

	sprintf_s(hp0, "����HP��%d", m_vecTank[0].GetHP());
	draw.PrintChar(54, 26, hp0, 10);

	if (m_vecTank.size() > 1)
	{
		sprintf_s(hp1, "�з�HP��%d", m_vecTank[1].GetHP());
		draw.PrintChar(54, 28, hp1, 3);
	}

	if (m_vecTank.size() > 2)
	{
		sprintf_s(hp2, "�з�HP��%d", m_vecTank[2].GetHP());
		draw.PrintChar(54, 30, hp2, 3);
	}
	else
		draw.PrintChar(54, 30, "             ", 8);

}
