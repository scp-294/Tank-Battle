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
				draw.PrintChar(nPosY, nPosX, "��", TankColor);
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
				pMap->setMapValue(nPosX, nPosY, �յ�);
			}
		}
	}
}

//��ײ�ж�-̹��
int CTankObject::JudCollision()
{
	int flag;
	//Ҫײ���ĵ�ͼ�е�λ��
	int mX = tempX;
	int mY = tempY;
	if (nDir == UP)
	{
		mX--;
		for (int i = mY - 1; i <= mY + 1; i++)
		{
			flag = getFlag(mX, i);
			if (flag == ľ�� || flag == ��ʯ || flag == ̹��)
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
			if (flag == ľ�� || flag == ��ʯ || flag == ̹��)
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
			if (flag == ľ�� || flag == ��ʯ || flag == ̹��)
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
			if (flag == ľ�� || flag == ��ʯ || flag == ̹��)
				return true;
		}
		return false;
	}

}

int CTankObject::getFlag(int x, int y)
{
	int nArr=pMap->getMApValue(x, y);
	if (nArr == ��ʯ)
		return ��ʯ;
	else if (nArr == ľ��)
		return ľ��;
	else if (nArr == �ݵ�)
		return �ݵ�;
	else if (nArr == �յ�)
		return �յ�;
	else if(nArr!= TankColor)
		return ̹��;
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
	// ����Ƿ񿪻�
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

	//�ж�ײ�����Ƿ�����ƶ�
	switch (JudCollision())
	{
		//������ײ�޸�̹�˵�λ�ú�״̬
	case false:
		//û��ײ���ϰ�����Լ����ƶ�
		TankX = tempX;
		TankY = tempY;
		old_objTank.ClsObjtect();
		this->DrawObjtect();
		old_objTank = *this;
		break;
	case true:
		//ײ���ϰ�����ı�̹��λ��
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


