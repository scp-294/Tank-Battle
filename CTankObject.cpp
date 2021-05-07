#include "CTankObject.h"

CTankObject::CTankObject(int x, int y, int dir, int color, int type, int hp) :
	TankX(x), TankY(y), nDir(dir), HP(hp), tLastClock(clock()), m_isFire(false), TankColor(color), m_type(type), sorce(5)
{

}

bool CTankObject::IsCreateTime()
{
	if (clock() - CreateClock > CreateSpeed)
	{
		CreateClock = clock();
		return true;
	}
	return false;
}

void CTankObject::DrawObjtect()
{
	for (int nPosX = TankX - 1; nPosX < TankX + 2; nPosX++)
	{
		for (int nPosY = TankY - 1; nPosY < TankY + 2; nPosY++)
		{
			int nX = nPosX - TankX + 1;
			int nY = nPosY - TankY + 1;
			if (g_TankShape[nDir][nX][nY])
			{
				draw.PrintChar(nPosY, nPosX, "□", TankColor);
				pMap->setMapValue(nPosX, nPosY, TankColor);
			}
		}
	}
	tLastClock = clock();

}

void CTankObject::ClsObjtect()
{
	for (int nPosX = TankX - 1; nPosX < TankX + 2; nPosX++)
	{
		for (int nPosY = TankY - 1; nPosY < TankY + 2; nPosY++)
		{
			int nX = nPosX - TankX + 1;
			int nY = nPosY - TankY + 1;
			if (g_TankShape[nDir][nX][nY]) {
				draw.PrintChar(nPosY, nPosX, "  ", 2 | 8);
				pMap->setMapValue(nPosX, nPosY, 空地);
			}
		}
	}
}

//碰撞判断-坦克
int CTankObject::JudCollision()
{
	int flag;
	//要撞击的地图中的位置
	int mX = tempX;
	int mY = tempY;
	if (nDir == UP)
	{
		mX--;
		for (int i = mY - 1; i <= mY + 1; i++)
		{
			flag = getFlag(mX, i);
			if (flag == 木板 || flag == 岩石 || flag == 坦克)
				return true;
		}
		return false;
	}
	else if (nDir == DOWN)
	{
		mX++;
		for (int i = mY - 1; i <= mY + 1; i++)
		{
			flag = getFlag(mX, i);
			if (flag == 木板 || flag == 岩石 || flag == 坦克)
				return true;
		}
		return false;
	}
	else if (nDir == LEFT)
	{
		mY--;
		for (int i = mX - 1; i <= mX + 1; i++)
		{
			flag = getFlag(i, mY);
			if (flag == 木板 || flag == 岩石 || flag == 坦克)
				return true;
		}
		return false;
	}
	else
	{
		mY++;
		for (int i = mX - 1; i <= mX + 1; i++)
		{
			flag = getFlag(i, mY);
			if (flag == 木板 || flag == 岩石 || flag == 坦克)
				return true;
		}
		return false;
	}

}

int CTankObject::getFlag(int x, int y)
{
	int nArr=pMap->getMApValue(x, y);
	if (nArr == 岩石)
		return 岩石;
	else if (nArr == 木板)
		return 木板;
	else if (nArr == 草地)
		return 草地;
	else if (nArr == 空地)
		return 空地;
	else if(nArr!= TankColor)
		return 坦克;
}

bool CTankObject::IsMoveTime()
{
	if (clock() - tLastClock > 40)
		return true;
	else
		return false;
}

bool CTankObject::IsFire()
{
	if (m_isFire && IsCreateTime())
	{
		m_isFire = false;
		return true;
	}
	m_isFire = false;
	return  false;
}

void CTankObject::MoveTank(int dir)
{
	// 检测是否开火
	if (dir == FIRE)
	{
		m_isFire = true;
		return;
	}

	CTankObject old_objTank = *this;
	tempX = this->GetX();
	tempY = this->GetY();
	switch (dir)
	{
	case UP:

		if (nDir != UP)
		{
			nDir = UP;
		}
		else
			tempX--;
		break;

	case DOWN:

		if (nDir != DOWN)
		{
			nDir = DOWN;
		}
		else
			tempX++;
		break;

	case LEFT:

		if (nDir != LEFT)
		{
			nDir = LEFT;
		}
		else
			tempY--;
		break;

	case RIGHT:

		if (nDir != RIGHT)
		{
			nDir = RIGHT;
		}
		else
			tempY++;
		break;
	}

	//判断撞击后是否可以移动
	switch (JudCollision())
	{
		//根据碰撞修改坦克的位置和状态
	case false:
		//没有撞到障碍物，可以继续移动
		TankX = tempX;
		TankY = tempY;
		old_objTank.ClsObjtect();
		this->DrawObjtect();
		old_objTank = *this;
		break;
	case true:
		//撞到障碍物，不改变坦克位置
		*this = old_objTank;
		break;
	default:
		break;
	}
}

int CTankObject::GetX()
{
	return TankX;
}

int CTankObject::GetY()
{
	return TankY;
}

int CTankObject::GetD()
{
	return nDir;
}

int CTankObject::GetHP()
{
	return HP;
}

void CTankObject::ReduceHp()
{
	HP--;
}

void CTankObject::ReduceSorce(int recSorce)
{
	sorce -= recSorce;
}

int CTankObject::GetType()
{
	return m_type;
}

int CTankObject::GetColor()
{
	return TankColor;
}


