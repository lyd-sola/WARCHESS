/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: aut.c
Author: 刘云笛、陈旭桐
Version:
Description: 自动对战
Date:

更新日志

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
				}//能攻击就先攻击
				memset(visit, 0, sizeof(visit));
				if (range(map, pos, arminfo.move, 0, visit))
				{

				}//不能攻击就移动
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
	//对方大本营map[9][1]
	for (i = 0; i < 7; i++)//找到近似离对方大本营最近的点
	{
		for (j = 0; j < 7; j++)
		{
			if (visit[j][i] != 0)
			{
				y = opos.y + j - 3;
				x = opos.x + i - 3;
				tmp = abs(y - 9) + abs(x - 1);
				if (min < tmp || (min == tmp && rand() % 2))//随机选一个近似最近点
				{
					min = tmp;
					minx = x;
					miny = y;
				}
			}
		}
	}
	//move to minx miny
	//map[miny][minx].stay = 0;//移动解除驻扎状态
	//map[miny][minx].flag = 1;//标记已移动
	//map[miny][minx].health = map[opos.y][opos.x].health;
	//map[miny][minx].kind = map[opos.y][opos.x].kind;
	//map[miny][minx].side = map[opos.y][opos.x].side;//移动
	//map[opos.y][opos.x].kind = NOARMY;//清除这个就行了
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