#include "CBulletObject.h"

CBulletObject CBulletObject::MakeBullet(CTankObject TankObj)
{
	*this = TankObj;
	return *this;
}

void CBulletObject::MoveBullet(vector<CTankObject>& TankObj)
{
	//�ӵ���������
	CBulletObject bullet = *this;
	switch (bullet.dir)
	{
	case UP:
		bullet.x--;
		break;
	case DOWN:
		bullet.x++;
		break;
	case LEFT:
		bullet.y--;
		break;
	case RIGHT:
		bullet.y++;
		break;

	}

	//�ж����ӵ��Ƿ�ײ��̹�ˣ��Լ�Ҳ�㣬����׷����
	bool IsTank = false;
	int num = 0;
	for (num; num < TankObj.size(); num++)
	{
		if (bullet == TankObj[num])
			IsTank = true;

		if (IsTank == true)
			break;
	}
	
	//ûײ��̹��
	if (IsTank == false)
	{
		//�ж���λ����ʲô
		int JudPos = bullet.JudCollision();
		//�ж���һ��λ����ʲô
		int LastPos = this->JudCollision();

		if (JudPos == �յ�)
		{
			this->ClsObjtect();
			if (LastPos == �ݵ�)
			{
				//���ϲ����Ĳݵ�
				pMap->setMapValue(x, y, �ݵ�);
				draw.PrintChar(this->y, this->x, "��", 10);
			}
			*this = bullet;
			// �����ӵ�
			this->DrawObjtect();
		}
		else if (JudPos == �ݵ�)
		{
			if (LastPos == �ӵ�)
			{
				//�����ӵ�
				this->ClsObjtect();
			}
			*this = bullet;
			//���ϲ����Ĳݵ�
			pMap->setMapValue(x, y, �ݵ�);
			draw.PrintChar(this->y, this->x, "��", 10);
		}
		else if (JudPos == ��ʯ || JudPos == ľ��)
		{
			this->ClsObjtect();
			if (JudPos == ľ��)
			{
				//�������ľ�忪��ʱ��������
				if (LastPos == ľ��)
				{
					this->ClsObjtect();
					//�����޸ĵ�ͼ��������ͼ��ľ��ĳɿյ�
					pMap->setMapValue(this->x, this->y, �յ�);
				}
				else
				{
					*this = bullet;
					this->ClsObjtect();
					//�����޸ĵ�ͼ��������ͼ��ľ��ĳɿյ�
					pMap->setMapValue(bullet.x, bullet.y, �յ�);
				}
				//�ж���˭���ӵ�������ľ��
				for (int i = 0; i < TankObj.size(); i++)
				{
					if (TankObj[i].GetType() == m_type)
						TankObj[i].sorce++;
				}
			}
			this->life = false;
			PlaySoundA("..\\sound\\�ڵ���ը.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
		else if (JudPos == �ӵ�)
		{
			this->ClsObjtect();
			this->life = false;
			PlaySoundA("..\\sound\\�ڵ���ը.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
	}
	//ײ��̹��
	else
	{
		//�ж��Ƿ�ͬһ��Ӫ
		if (m_type == TankObj[num].GetType())
		{
			this->ClsObjtect();
			this->life = false;
			PlaySoundA("..\\sound\\�ڵ���ը.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
		else
		{
			TankObj[num].ReduceHp();
			TankObj[num].ReduceSorce(1);
			this->ClsObjtect();
			this->life = false;
			PlaySoundA("..\\sound\\̹�˱�ը.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
	}
}

void CBulletObject::DrawObjtect()
{
	draw.PrintChar(y, x, "��", 4);
	pMap->setMapValue(x, y, �ӵ�);
}

void CBulletObject::ClsObjtect()
{
	draw.PrintChar(y, x, "  ", 0);
	pMap->setMapValue(x, y, �յ�);
}


int CBulletObject::JudCollision()
{
	int nArr = pMap->getMApValue(x, y);
	if (nArr == ��ʯ)
		return ��ʯ;
	else if (nArr == ľ��)
		return ľ��;
	else if (nArr == �ݵ�)
		return �ݵ�;
	else if (nArr == �յ�)
		return �յ�;
	else if (nArr == �ӵ�)
		return �ӵ�;
	else
		return 0;
}

int CBulletObject::GetX()
{
	return x;
}

int CBulletObject::GetY()
{
	return y;
}

bool CBulletObject::IsLive()
{
	return life;
}

bool CBulletObject::IsMoveTime()
{
	if (clock() - MoveClock > MoveSpeed)
	{
		MoveClock = clock();
		return true;
	}
	return false;
}

bool CBulletObject::operator==(CTankObject& Tankobj)
{
	int nTankX = Tankobj.GetX();
	int nTankY = Tankobj.GetY();
	
	if (Tankobj.GetHP() != 0)
		//����̹�˵����������ж��Ƿ�ײ��
		for (int nPosX = nTankX - 1; nPosX < nTankX + 2; nPosX++)
			for (int nPosY = nTankY - 1; nPosY < nTankY + 2; nPosY++)
				if (nPosX == x && nPosY == y)
				{
					//HP-1,sorce-1
					//Tankobj.ReduceHp();
					//Tankobj.ReduceSorce(1);
					return true;
				}

	return false;
}

bool CBulletObject::operator=(CTankObject Tankobj)
{
	x = Tankobj.GetX();
	y = Tankobj.GetY();
	dir = Tankobj.GetD();
	MoveSpeed = 30;
	m_type = Tankobj.GetType();
	//�������ӵ�������ʱ��
	MoveClock = clock();
	life = false;

	switch (dir)
	{
	case UP:
		x -= 2;
		break;
	case DOWN:
		x += 2;
		break;
	case RIGHT:
		y += 2;
		break;
	default:
		y -= 2;
		break;
	}

	//�ж��Ƿ��ڲ���ʱ��������ʯ�������Ͳ�����,lifeĬ��Ϊfalse
	if (pMap->getMApValue(x, y) != ��ʯ)
		life = true;

	return true;
}
