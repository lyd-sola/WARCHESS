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
 //˫���������תƫ�����꣬����ˮû��ʲô��ϵ
OFF_POS D2O(DBL_POS pos)
{
	OFF_POS opos;
	opos.x = (pos.x - 1) / 2;//int�����Զ���ȡ�����������У�O2D����Ҫ����
	opos.y = pos.y - 1;
	return opos;
}
//ƫ������ת˫���������
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

/*����һ�������ϵı��ַ���*/
void draw_cell(DBL_POS pos, MAP map)
{

	int kind, side, geo, faci;
	POS offpos;

	offpos = D2O(pos);

	kind = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;
	geo = map[offpos.y][offpos.x].geo;
	faci = map[offpos.y][offpos.x].faci;
	pos = center_xy(pos.x, pos.y);
	//��ֹ��ʼ������ʱ��Ϊkind������0�Ѵ�Ӫ����Դ����
	switch (geo)
	{
	case BASE:
		//Map_partial(pos.x - 18, pos.y - 18, pos.x + 18, pos.y + 23);
	//case SORC:
	//case HSORC:
	case OUT_MAP:
		return;
	}
	switch (faci)
	{
	case MEDICAL:
		medical_draw(pos);
		break;
	case BCOLLECTION:
	case RCOLLECTION:
		collection_draw(pos, map);
	default:
		break;
	}
	switch (kind)
	{
	case BUILDER:
		Icon_builder(pos, side);
		break;
	case INFANTRY:
		Icon_inf(pos, side);
		break;
	case ARTILLERY:
		Icon_arti(pos, side);
		break;
	case TANK:
		Icon_tank(pos, side);
		break;
	case SUPER:
		Icon_super(pos, side);
		break;
	default:
		break;
	}
}

void recover_cell(DBL_POS pos, MAP map)//��ԭ����
{
	int geo, kind;
	POS offpos;
	offpos = D2O(pos);
	geo = map[offpos.y][offpos.x].geo;
	kind = map[offpos.y][offpos.x].kind;
	offpos = center_xy(pos.x, pos.y);
	if (geo == BASE || kind == 0)
	{
		Map_partial(offpos.x - 18, offpos.y - 18, offpos.x + 18, offpos.y + 23);
	}
	else
	{
		draw_cell(pos, map);
	}
}
/*��ʾvisit�����п��еĵ㣬����������ָ�봫lightbar������map_partial��ԭ*/
void show_visit(DBL_POS pos, int visit[7][7], void (*lightfun)(int x1, int y1, int x2, int y2))
{
	OFF_POS opos = D2O(pos);
	POS center;
	int i, j;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (visit[j][i] > 0)
			{
				center.y = opos.y + j - 3;
				center.x = opos.x + i - 3;
				center = O2D(center);
				center = center_xy(center.x, center.y);
				lightfun(center.x - 18, center.y - 18, center.x + 18, center.y + 18);
			}
		}
	}

}