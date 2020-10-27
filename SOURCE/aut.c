/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
File_name: aut.c
Author: ���Ƶѡ�����ͩ
Version:
Description: �Զ���ս
Date:

������־

******************************************************************/
#include "common.h"
void aut(MAP map, Battleinfo* batinfo)
{
	int x, y;
	OFF_POS opos;
	DBL_POS pos;
	Arminfo arminfo;
	int visit[7][7];
	for (x = 0; x < 13; x++)
	{
		for (y = 0; y < 13; y++)
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
}
//void aut_base(MAP map, unsigned *source)
//{
//
//}
void aut_move(MAP map, OFF_POS opos, int visit[7][7])
{
	int x, y, i, j, tmp;
	int min = 100, minx, miny;
	DBL_POS dbto, dbf;
	srand(time(NULL));
	//�Է���Ӫmap[9][1]��˫���������4��10
	for (i = 0; i < 7; i++)//�ҵ�������Է���Ӫ����ĵ�
	{
		for (j = 0; j < 7; j++)
		{
			if (visit[j][i] > 0)
			{
				y = opos.y + j - 3;
				x = opos.x + i - 3;
				dbto.x = x;
				dbto.y = y;
				dbto = O2D(dbto);
				tmp = abs(dbto.y - 10) + abs(dbto.x - 4) / 2;
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
	map[miny][minx].stay = 0;//�ƶ����פ��״̬
	map[miny][minx].flag = 1;//������ƶ�
	map[miny][minx].health = map[opos.y][opos.x].health;
	map[miny][minx].kind = map[opos.y][opos.x].kind;
	map[miny][minx].side = map[opos.y][opos.x].side;//�ƶ�
	map[opos.y][opos.x].kind = NOARMY;//������������
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
	if (info.attack >= map[to.y][to.x].health) //Ŀ���˽�
	{
		Clrmous();
		map[to.y][to.x].kind = NOARMY;
		show_msg("Ŀ���ѱ�����", "");
		draw_bomb(center.x, center.y + 10, 0);
		delay(1000);
		Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);//��ԭ�˴���ͼ
		attack_button("����", 65370);
		return;
	}
	else
	{
		//����פ�������Ĺ�ʽ������Ϊפ��֮�󹥻���+2��������+1�����ܵ����˺�-1��
		map[to.y][to.x].health -= (info.attack + Stay_pos * 2);
		show_msg("FIRE!", "");
		draw_bomb(center.x, center.y + 10, 0);
		delay(1000);
		draw_cell(dbto, map);
		//icon(center, map[to.y][to.x].side, map[to.y][to.x].kind);
		attack_button("����", 65370);
		return;
	}
}