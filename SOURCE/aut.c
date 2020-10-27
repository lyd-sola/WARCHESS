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
			if (map[y][x].side == 1 && map[y][x].kind != NOARMY)
			{
				if (map[y][x].kind != BUILDER)
				{
					opos.x = x;
					opos.y = y;
					pos = O2D(opos);
					arminfo = search_info(map[opos.y][opos.x].kind);
					memset(visit, 0, sizeof(visit));
					if (range(map, pos, arminfo.distance, 1, visit))
					{
						aut_attack(map, opos, visit);
						delay(msg_sec/2);
						continue;
					}
				}//�ܹ������ȹ���
				memset(visit, 0, sizeof(visit));
				if (range(map, pos, arminfo.move, 0, visit))
				{

				}//���ܹ������ƶ�
			}
		}
	}
}
void aut_base()
{

}
void aut_move(MAP map, OFF_POS opos, int visit[7][7])
{
	int x, y, i, j, tmp;
	int destnys = 0;
	int min = 100, minx, miny;
	srand(time(NULL));
	//�Է���Ӫmap[9][1]
	for (i = 0; i < 7; i++)//�ҵ�������Է���Ӫ����ĵ�
	{
		for (j = 0; j < 7; j++)
		{
			if (visit[j][i] != 0)
			{
				y = opos.y + j - 3;
				x = opos.x + i - 3;
				tmp = abs(y - 9) + abs(x - 1);
				if (min < tmp || (min == tmp && rand() % 2))//���ѡһ�����������
				{
					min = tmp;
					minx = x;
					miny = y;
				}
			}
		}
	}
	//move to minx miny
	//map[miny][minx].stay = 0;//�ƶ����פ��״̬
	//map[miny][minx].flag = 1;//������ƶ�
	//map[miny][minx].health = map[opos.y][opos.x].health;
	//map[miny][minx].kind = map[opos.y][opos.x].kind;
	//map[miny][minx].side = map[opos.y][opos.x].side;//�ƶ�
	//map[opos.y][opos.x].kind = NOARMY;//������������
}
void aut_attack(MAP map, OFF_POS opos, int visit[7][7])
{
	int i, j;
	int x, y;
	DBL_POS pos = O2D(opos);

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			y = opos.y + j - 3;
			x = opos.x + i - 3;
			if (visit[j][i] != 0 && map[y][x].side == 0 && map[y][x].kind != NOARMY)
			{

			}
		}
	}
}