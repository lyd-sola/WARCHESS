/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: battle.c
Author: 刘云笛、陈旭桐
Version:
Description: 对战行为
Date:

更新日志

******************************************************************/
#include "common.h"
extern FILE* FBMP;
void move(DBL_POS From, MAP map, int able)//需要增加移动方判断和是否可以行动
{
	OFF_POS To, ofrom;
	DBL_POS dbto;
	int visit[7][7];

	ofrom = D2O(From);
	memset(visit, 0, sizeof(visit));
	range(map, From, able, 0, visit);

	move_button(600);
	show_msg("请选择要移动的位置", "点击右键取消");
	/*这里本来想法是标亮所有可以走的点，有待实现*/
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//需要保证已有行动力
		{
			To = D2O(dbto);//求出目标偏移坐标
			if (map[To.y][To.x].kind == NOARMY)//为空可移动，以后还需设置移动能力，还需判断是否原地移动
			{
				if (moving(map, visit, From, dbto))
				{
					Clrmous();

					map[To.x][To.y].stay = 0;//移动解除驻扎状态
					map[To.x][To.y].flag = 1;//标记已移动
					map[To.y][To.x].health = map[ofrom.y][ofrom.x].health;
					map[To.y][To.x].kind = map[ofrom.y][ofrom.x].kind;
					map[To.y][To.x].side = map[ofrom.y][ofrom.x].side;//移动
					map[ofrom.y][ofrom.x].kind = NOARMY;//清除这个就行了
					move_button(65370);
					return;
				}
				else
				{
					show_msg("此处无法到达", "");
				}
			}
			else
			{
				show_msg("此处已被占领", "");
				move_button(65370);
				delay(1000);
				return; 
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//右键取消
		{
			move_button(65370);
			return;
		}
	}
}

void stay(DBL_POS dpos, MAP map)
{
	OFF_POS opos;
	CELL cell;

	opos = D2O(dpos);

	if (map[opos.y][opos.x].stay)
	{
		show_msg("已经在此处驻扎！", "");
		
	}
	else
	{
		map[opos.y][opos.x].stay = 1;
		show_msg("驻扎成功", "");
	}
	delay(800);
	return;
}

void attack(DBL_POS dpos, MAP map)
{
	OFF_POS opos, to;
	DBL_POS dbto;
	POS center;
	Arminfo info;
	int Stay_to, Stay_pos;

	opos = D2O(dpos);
	attack_button("攻击", 600);
	show_msg("请选择要攻击的位置", "");

	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//需要保证已有行动力
		{
			to = D2O(dbto);
			if (map[to.y][to.x].kind) //目标不为空可以攻击
			{
				info = search_info(map[opos.y][opos.x].kind); //读取当前位置兵种信息
				Stay_pos = map[opos.y][opos.x].stay;
				Stay_to = map[to.y][to.x].stay;
				center = center_xy(dbto.x, dbto.y);
				if (map[to.y][to.x].side == map[opos.y][opos.x].side) //目标不可为同阵营
				{
					show_msg("不可以攻击友军！", "你怎么肥四");
					delay(1000);
				}
				else
				{
					if (info.attack >= map[to.y][to.x].health) //目标扑街
					{
						Clrmous();
						map[to.y][to.x].kind = NOARMY;
						show_msg("目标已被歼灭！","");
						draw_bomb(center.x, center.y+10, 0);
						delay(1000);
						Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);//还原此处地图	
					}
					
					else
					{
						//计算驻扎增幅的公式，暂设为驻扎之后攻击力+2，防御力+1（即受到的伤害-1）
						map[to.y][to.x].health = (map[to.y][to.x].health + Stay_to * 1) - (info.attack + Stay_pos * 2); 
						show_msg("FIRE!", "");
						draw_bomb(center.x, center.y+10, 0);
						delay(1000);
						icon(center, map[to.y][to.x].side, map[to.y][to.x].kind);
					}
				}
			}
			attack_button("攻击", 65370);
			return;
		}
		
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//右键取消
		{
			attack_button("攻击", 65370);
			return;
		}
	}
}

void delarm(DBL_POS dpos, MAP map)
{
	POS center;
	center = center_xy(dpos.x, dpos.y);
	map[dpos.y][dpos.x].kind = NOARMY;
	show_msg("该部队已撤退！", "");
	delay(1000);
	Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);
	return;
}