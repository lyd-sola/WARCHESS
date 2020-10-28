/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: aut.c
Author: 刘云笛、陈旭桐
Version:1.0
Description: 自动对战
Date:

更新日志
10.28 2am	完成自动攻击和移动！！！
10.28 10am	增加自动造兵和升级大本营，增加自动移动随机性
******************************************************************/
#include "common.h"
/**********************************************************
Function：		aut
Description：	自动对战函数
		会优先攻击再移动，主要向对方大本营方向移动，有一定概率乱走
		实现大本营升级以及按概率自动造兵								*****需要增加自动驻扎*****
Author：		刘云笛
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
					range(map, pos, arminfo.distance, 1, visit);//计算攻击范围
					if (aut_attack(map, opos, visit, arminfo))
					{
						delay(msg_sec / 2);
						continue;
					}
				}//能攻击就先攻击
				memset(visit, 0, sizeof(visit));
				if (range(map, pos, arminfo.move, 0, visit))//返回是否有可行点
				{
					aut_move(map, opos, visit);
					delay(msg_sec / 2);
					continue;
				}//不能攻击就移动
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
	//对方大本营map[9][1]，双倍宽度坐标4，10
	for (j = 0; j < 7; j++)//找到近似离对方大本营最近的点
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
				if (rand() % 50 == 0)//有一定概率乱走，增加变化性
					tmp = 0;
				if (tmp < min || (min == tmp && rand() % 2))//随机选一个近似最近点
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
	info.attack += Stay_pos;//驻扎增加攻击力
	if (info.attack >= map[to.y][to.x].health) //目标扑街
	{
		Clrmous();
		map[to.y][to.x].kind = NOARMY;
		show_msg("消灭一个目标！", "");
		draw_bomb(center.x, center.y + 10, 0);
		delay(msg_sec);
		Clrmous();
		Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);//还原此处地图
	}
	else
	{
		map[to.y][to.x].health -= info.attack;//减少生命值
		show_msg("FIRE!", "");
		draw_bomb(center.x, center.y + 10, 0);
		delay(msg_sec);
		Clrmous();
		recover_cell(dbto, map);
	}
	return;
}
void aut_base(MAP map, unsigned* source)//自动升级和造兵
{
	int cost;
	if (map[3][10].kind < 3)//能升级当然升级啦
	{
		cost = map[3][10].kind == 1 ? lev2_cost : lev3_cost;
		if (*source > cost)
		{
			map[3][10].kind++;
			*source -= cost;
			show_msg("大本营升级！", "");
			delay(msg_sec);
		}
	}
	aut_buildarm(map, source);
}
void aut_buildarm(MAP map, unsigned* source)//自动造兵，目前只会造步兵、炮兵、坦克、超级兵
{
	Arminfo arminfo;
	POS center;
	int kind = 0, rd;
	if (map[2][10].kind != 0) //判断红色方出兵点是否被占领
	{
		return;
	}
	srand(time(NULL));
	if (*source > 50 && map[3][10].kind == 3)//资源多就造超级兵
	{
		kind = SUPER;
	}
	else if (map[3][10].kind == 1)//一级大本营只能造工兵
	{
		rd = rand() % 3;
		if (*source >= 1 && rd <= 1)//2/3概率造兵
			kind = INFANTRY;
	}
	else if (map[3][10].kind >= 2)//二级解锁炮兵和坦克
	{
		if (*source > 10)
		{
			rd = rand() % 14;//生成随机数，按概率随机出兵 步炮坦空 5:3:3:3
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
		show_msg("增援到达！", "");
		delay(msg_sec);
	}
	return;
}