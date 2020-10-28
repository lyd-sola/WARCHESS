/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
File_name: aut.c
Author: ���Ƶѡ�����ͩ
Version:1.0
Description: �Զ���ս
Date:

������־
10.28 2am	����Զ��������ƶ�������
10.28 10am	�����Զ������������Ӫ�������Զ��ƶ������
******************************************************************/
#include "common.h"
/**********************************************************
Function��		aut
Description��	�Զ���ս����
		�����ȹ������ƶ�����Ҫ��Է���Ӫ�����ƶ�����һ����������
		ʵ�ִ�Ӫ�����Լ��������Զ����								*****��Ҫ�����Զ�פ��*****
Author��		���Ƶ�
**********************************************************/
void aut(MAP map, Battleinfo* batinfo)
{
	int x, y;
	OFF_POS opos;
	DBL_POS pos;
	Arminfo arminfo;
	int visit[7][7];
	for (y = 0; y < 13; y++)
	{
		for (x = 0; x < 13; x++)
		{
			if (map[y][x].side == 1 && map[y][x].kind != NOARMY && !map[y][x].flag && map[y][x].geo != BASE)
			{
				opos.x = x;
				opos.y = y;
				pos = O2D(opos);
				arminfo = search_info(map[y][x].kind);
				if (map[y][x].kind != BUILDER)
				{
					memset(visit, 0, sizeof(visit));
					range(map, pos, arminfo.distance, 1, visit);//���㹥����Χ
					if (aut_attack(map, opos, visit, arminfo))
					{
						delay(msg_sec / 2);
						continue;
					}
				}//�ܹ������ȹ���
				memset(visit, 0, sizeof(visit));
				if (range(map, pos, arminfo.move, 0, visit))//�����Ƿ��п��е�
				{
					aut_move(map, opos, visit);
					delay(msg_sec / 2);
					continue;
				}//���ܹ������ƶ�
			}
		}
	}
	aut_base(map, &(batinfo->b_source));
	switch (map[3][10].kind)
	{
	case 3:
		batinfo->b_source += 5;
	case 2:
		batinfo->b_source += 5;
	case 1:
		batinfo->b_source += 1;
	}
}
void aut_move(MAP map, OFF_POS opos, int visit[7][7])
{
	int x, y, i, j, tmp;
	int min = 100, minx, miny;
	DBL_POS dbto, dbf;
	srand(time(NULL));
	//�Է���Ӫmap[9][1]��˫���������4��10
	for (j = 0; j < 7; j++)//�ҵ�������Է���Ӫ����ĵ�
	{
		for (i = 0; i < 7; i++)
		{
			if (visit[j][i] > 0)
			{
				y = opos.y + j - 3;
				x = opos.x + i - 3;
				dbto.x = x;
				dbto.y = y;
				dbto = O2D(dbto);
				tmp = abs(dbto.y - 10) + abs(dbto.x - 4) / 2;
				if (rand() % 50 == 0)//��һ���������ߣ����ӱ仯��
					tmp = 0;
				if (tmp < min || (min == tmp && rand() % 2))//���ѡһ�����������
				{
					min = tmp;
					minx = x;
					miny = y;
				}
			}
		}
	}
	dbf = O2D(opos);
	dbto.x = minx;
	dbto.y = miny;
	dbto = O2D(dbto);
	moving(map, visit, dbf, dbto);
}
int aut_attack(MAP map, OFF_POS opos, int visit[7][7], Arminfo info)
{
	int i, j;
	int x, y;
	OFF_POS to;

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			y = opos.y + j - 3;
			x = opos.x + i - 3;
			if (visit[j][i] > 0 && map[y][x].side == 0 && map[y][x].kind != NOARMY)
			{
				to.x = x;
				to.y = y;
				ATTACK(to, info, map[opos.y][opos.x].stay, map);
				return 1;
			}
		}
	}
	return 0;
}

void ATTACK(OFF_POS to, Arminfo info, int Stay_pos, MAP map)
{
	DBL_POS dbto = O2D(to);
	POS center = center_xy(dbto.x, dbto.y);
	info.attack += Stay_pos;//פ�����ӹ�����
	if (info.attack >= map[to.y][to.x].health) //Ŀ���˽�
	{
		Clrmous();
		map[to.y][to.x].kind = NOARMY;
		show_msg("����һ��Ŀ�꣡", "");
		draw_bomb(center.x, center.y + 10, 0);
		delay(msg_sec);
		Clrmous();
		Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);//��ԭ�˴���ͼ
	}
	else
	{
		map[to.y][to.x].health -= info.attack;//��������ֵ
		show_msg("FIRE!", "");
		draw_bomb(center.x, center.y + 10, 0);
		delay(msg_sec);
		Clrmous();
		recover_cell(dbto, map);
	}
	return;
}
void aut_base(MAP map, unsigned* source)//�Զ����������
{
	int cost;
	if (map[3][10].kind < 3)//��������Ȼ������
	{
		cost = map[3][10].kind == 1 ? lev2_cost : lev3_cost;
		if (*source > cost)
		{
			map[3][10].kind++;
			*source -= cost;
			show_msg("��Ӫ������", "");
			delay(msg_sec);
		}
	}
	aut_buildarm(map, source);
}
void aut_buildarm(MAP map, unsigned* source)//�Զ������Ŀǰֻ���첽�����ڱ���̹�ˡ�������
{
	Arminfo arminfo;
	POS center;
	int kind = 0, rd;
	if (map[2][10].kind != 0) //�жϺ�ɫ���������Ƿ�ռ��
	{
		return;
	}
	srand(time(NULL));
	if (*source > 50 && map[3][10].kind == 3)//��Դ����쳬����
	{
		kind = SUPER;
	}
	else if (map[3][10].kind == 1)//һ����Ӫֻ���칤��
	{
		rd = rand() % 3;
		if (*source >= 1 && rd <= 1)//2/3�������
			kind = INFANTRY;
	}
	else if (map[3][10].kind >= 2)//���������ڱ���̹��
	{
		if (*source > 10)
		{
			rd = rand() % 14;//������������������������ ����̹�� 5:3:3:3
			if (rd <= 4)
				kind = INFANTRY;
			else if (rd <= 7)
				kind = ARTILLERY;
			else if (rd <= 10)
				kind = TANK;
			else
				kind = 0;
		}
		else if (*source >= 1)
		{
			kind = INFANTRY;
		}
	}
	if (kind)
	{
		arminfo = search_info(kind);
		map[2][10].kind = kind;
		map[2][10].health = arminfo.health;
		map[2][10].side = 1;
		map[2][10].stay = 0;
		map[2][10].flag = 1;
		center = center_xy(21, 3);
		icon(center, 1, kind);
		*source -= arminfo.cost;
		show_msg("��Ԯ���", "");
		delay(msg_sec);
	}
	return;
}