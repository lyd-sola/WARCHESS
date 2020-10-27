/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:
author:
version:
Description:
date:

������־

����Ŀ¼
******************************************************************/
#include "common.h"
//���ظ��ӣ�������������Χ���ĸ���

POS xy2cell(int x, int y) //��ʵ������˫���������ת��
{
	POS cell;
	double x2, y2, a, b, tmp;
	int n1, n2;
	x2 = x - X0; //������ϵ���MouseX
	y2 = y - Y0; //������ϵ���MouseY
	n1 = x2 / WIDTH + 1; //���ط�������꣬�ڼ���
	n2 = y2 / LENGTH + 1; //���ط��������꣬�ڼ���
	a = n1 * WIDTH - WIDTH / 2; //���ط����е������
	b = n2 * LENGTH - LENGTH / 2; //���ط����е�������
	tmp = f(x2, a, b, n1, n2);

	/**���ݵ��λ�������ط�����б���Ϸ������·�ȷ������������**/
	cell.y = (y2 < tmp) ? n2 : (n2 + 1);

	/**���ݵ��λ�������ط�����б���Ϸ������·��Լ����ط�������������ż��ȷ�����Ӻ�����**/
	/************  y2 < tmp �жϵ�����������Ƿ���б��֮�϶���֮�£�y������������*****************/
	if (n1 % 2 == 1) //���ط�������Ϊ�����������ж�������ż��
	{
		if (n2 % 2 == 1)  //���ط�������Ϊ����
		{
			cell.x = (y2 < tmp) ? n1 : (n1 - 1);
		}
		else  //���ط�������Ϊż��
		{
			cell.x = (y2 < tmp) ? (n1 - 1) : n1;
		}
	}
	else            //���ط�������Ϊż���������ж�������ż��
	{
		if (n2 % 2 == 1)  //���ط�������Ϊ����
		{
			cell.x = (y2 < tmp) ? (n1 - 1) : n1;
		}
		else //���ط�������Ϊż��
		{
			cell.x = (y2 < tmp) ? n1 : (n1 - 1);
		}
	}
	return cell;
}

float f(float x, float a, float b, int n1, int n2)
{
	if (n1 % 2 == 1)
	{
		if (n2 % 2 == 1)
			return K * (x - a) + b;
		else
			return -K * (x - a) + b;
	}
	else
	{
		if (n2 % 2 == 1)
			return -K * (x - a) + b;
		else
			return K * (x - a) + b;
	}
}

 POS center_xy(int row, int col)
{
	POS centpos;
	row = (row + 1) / 2;//�Ļص������
	if (col % 2 == 1)
	{
		centpos.x = 103 + (row - 1) * 69;
	}
	else
	{
		centpos.x = 139 + (row - 1) * 69;
	}
	centpos.y = 54 + (col - 1) * 46;
	centpos.y -= (col - 1) / 3;
	centpos.x -= (row - 1) / 3;
	centpos.y -= 2;//����ͼ��λ��΢��
	return centpos;
}

OFF_POS D2O(DBL_POS pos)
{
	OFF_POS opos;
	opos.x = (pos.x - 1) / 2;
	opos.y = pos.y - 1;
	return opos;
}

DBL_POS O2D(OFF_POS pos)
{
	DBL_POS dpos;
	if (pos.y % 2)
	{
		dpos.x = 2 * pos.x + 2;
	}
	else
	{
		dpos.x = 2 * pos.x + 1;
	}
	dpos.y = pos.y + 1;
	return dpos;
}
//�ж��Ƿ��ڵ�ͼ�ڵ������ͼ�ⷵ��0����ͼ�����޵�λ����1���е�λ����2
int clcmap(DBL_POS* pos, MAP map)
{
	OFF_POS opos;
	if (mouse_press(68, 22, 962, 633) == MOUSE_IN_L)
	{
		*pos = xy2cell(MouseX, MouseY);
		if(inside_map(map, *pos))
		{
			opos = D2O(*pos);
			if (map[opos.y][opos.x].geo != OUT_MAP)
			{
				if (map[opos.y][opos.x].geo == BASE)
				{
					return 3;
				}//��Ӫ
				if (map[opos.y][opos.x].kind != NOARMY)
				{
					return 2;
				}//�е�λ
				else 
				{
					return 1;
				}//�޵�λ
			}
			else
			{
				return 0;
			}//��ͼ������
		}
		else
		{
			return 0;
		}//��ͼ��Ч����
	}
	else
	{
		return 0;
	}//δ���
}

int move_cost(int geo)//�����ƶ�����
{
	switch (geo)
	{
	case OBSTACLE:
		return 666;
	case PLAIN:
		return 1;
	case FOREST:
		return 2;
	case DESERT:
		return 1;
	case BASE:
		return 666;
	case SORC:
		return 2;
	case HSORC:
		return 2;
	case OUT_MAP:
		return 666;
	}
	return 666;
}

int inside_map(MAP map, DBL_POS pos)//Ϊ���������������ۣ��ѳ�ª�Ķ���д������
{
	OFF_POS opos = D2O(pos);

	return 1 <= pos.x && pos.x <= 26 && 1 <= pos.y && pos.y <= 13
		&& map[opos.y][opos.x].geo != OUT_MAP;
}