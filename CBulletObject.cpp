#include "CBulletObject.h"

CBulletObject CBulletObject::MakeBullet(CTankObject TankObj)
{
	*this = TankObj;
	return *this;
}

void CBulletObject::MoveBullet(vector<CTankObject>& TankObj)
{
	//子弹的新坐标
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

	//判断新子弹是否撞到坦克，自己也算，但是追不上
	bool IsTank = false;
	int num = 0;
	for (num; num < TankObj.size(); num++)
	{
		if (bullet == TankObj[num])
			IsTank = true;

		if (IsTank == true)
			break;
	}
	
	//没撞到坦克
	if (IsTank == false)
	{
		//判断新位置是什么
		int JudPos = bullet.JudCollision();
		//判断上一个位置是什么
		int LastPos = this->JudCollision();

		if (JudPos == 空地)
		{
			this->ClsObjtect();
			if (LastPos == 草地)
			{
				//补上擦掉的草地
				pMap->setMapValue(x, y, 草地);
				draw.PrintChar(this->y, this->x, "■", 10);
			}
			*this = bullet;
			// 画新子弹
			this->DrawObjtect();
		}
		else if (JudPos == 草地)
		{
			if (LastPos == 子弹)
			{
				//擦除子弹
				this->ClsObjtect();
			}
			*this = bullet;
			//补上擦掉的草地
			pMap->setMapValue(x, y, 草地);
			draw.PrintChar(this->y, this->x, "■", 10);
		}
		else if (JudPos == 岩石 || JudPos == 木板)
		{
			this->ClsObjtect();
			if (JudPos == 木板)
			{
				//避免怼着木板开火时擦掉两块
				if (LastPos == 木板)
				{
					this->ClsObjtect();
					//调用修改地图函数将地图的木板改成空地
					pMap->setMapValue(this->x, this->y, 空地);
				}
				else
				{
					*this = bullet;
					this->ClsObjtect();
					//调用修改地图函数将地图的木板改成空地
					pMap->setMapValue(bullet.x, bullet.y, 空地);
				}
				//判断是谁的子弹击毁了木板
				for (int i = 0; i < TankObj.size(); i++)
				{
					if (TankObj[i].GetType() == m_type)
						TankObj[i].sorce++;
				}
			}
			this->life = false;
			PlaySoundA("..\\sound\\炮弹爆炸.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
		else if (JudPos == 子弹)
		{
			this->ClsObjtect();
			this->life = false;
			PlaySoundA("..\\sound\\炮弹爆炸.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
	}
	//撞到坦克
	else
	{
		//判断是否同一阵营
		if (m_type == TankObj[num].GetType())
		{
			this->ClsObjtect();
			this->life = false;
			PlaySoundA("..\\sound\\炮弹爆炸.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
		else
		{
			TankObj[num].ReduceHp();
			TankObj[num].ReduceSorce(1);
			this->ClsObjtect();
			this->life = false;
			PlaySoundA("..\\sound\\坦克爆炸.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		}
	}
}

void CBulletObject::DrawObjtect()
{
	draw.PrintChar(y, x, "●", 4);
	pMap->setMapValue(x, y, 子弹);
}

void CBulletObject::ClsObjtect()
{
	draw.PrintChar(y, x, "  ", 0);
	pMap->setMapValue(x, y, 空地);
}


int CBulletObject::JudCollision()
{
	int nArr = pMap->getMApValue(x, y);
	if (nArr == 岩石)
		return 岩石;
	else if (nArr == 木板)
		return 木板;
	else if (nArr == 草地)
		return 草地;
	else if (nArr == 空地)
		return 空地;
	else if (nArr == 子弹)
		return 子弹;
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
		//遍历坦克的所有坐标判断是否撞击
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
	//设置新子弹产生的时间
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

	//判断是否在产生时就遇到岩石，遇到就不产生,life默认为false
	if (pMap->getMApValue(x, y) != 岩石)
		life = true;

	return true;
}
