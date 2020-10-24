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

					map[To.y][To.x].stay = 0;//移动解除驻扎状态
					map[To.y][To.x].flag = 1;//标记已移动
					map[To.y][To.x].health = map[ofrom.y][ofrom.x].health;
					map[To.y][To.x].kind = map[ofrom.y][ofrom.x].kind;
					map[To.y][To.x].side = map[ofrom.y][ofrom.x].side;//移动
					map[ofrom.y][ofrom.x].kind = NOARMY;//清除这个就行了
					return;
				}
				else
				{
					show_msg("此处无法到达", "重新选择目的地");
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
		map[opos.y][opos.x].flag = 1;
		show_msg("驻扎成功", "");
	}
	delay(1000);
	return;
}

void attack(DBL_POS dpos, MAP map)
{
	OFF_POS opos, to;
	DBL_POS dbto;
	POS center;
	Arminfo info;
	int Stay_pos;

	opos = D2O(dpos);
	info = search_info(map[opos.y][opos.x].kind); //读取当前位置兵种信息

	attack_button("攻击", 600);
	show_msg("请选择要攻击的位置", "右键取消");

	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//需要保证已有行动力
		{
			to = D2O(dbto);
			if (map[to.y][to.x].kind) //目标不为空可以攻击
			{
				if (attack_judge(map, info.distance, dpos, dbto))
				{
					Stay_pos = map[opos.y][opos.x].stay;
					center = center_xy(dbto.x, dbto.y);
					if (map[to.y][to.x].side == map[opos.y][opos.x].side) //目标不可为同阵营
					{
						show_msg("不可以攻击友军！", "你怎么肥四");
						delay(1000);
						attack_button("攻击", 65370);
						return;
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
							attack_button("攻击", 65370);
							return;
						}
					
						else
						{
							//计算驻扎增幅的公式，暂设为驻扎之后攻击力+2，防御力+1（即受到的伤害-1）
							map[to.y][to.x].health -= (info.attack + Stay_pos * 2); 
							show_msg("FIRE!", "");
							draw_bomb(center.x, center.y+10, 0);
							delay(1000);
							icon(center, map[to.y][to.x].side, map[to.y][to.x].kind);
							attack_button("攻击", 65370);
							return;
						}
					}
				}
				else
				{
					show_msg("打不到 QAQ", "请重新选择目标");
				}
			}
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
	OFF_POS opos;
	center = center_xy(dpos.x, dpos.y);
	opos = D2O(dpos);
	map[opos.y][opos.x].kind = NOARMY;
	show_msg("该部队已撤退！", "");
	delay(1000);
	Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);
	return;
}

//下一回合函数
void nxt_round(MAP map, Battleinfo* info, int *pside)
{
	int i, j, perround = 1;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (map[j][i].kind != NOARMY)
			{
				map[j][i].flag = 1;
			}
		}
	}
	if (*pside)
	{
		/*计算每回合增加资源数的公式，初始每回合一
		* 大本营等级二级：+1 大本营等级三级：+3
		* 普通资源：每占领一个每回合+1
		* 高级资源：每占领一个每回合+3*/
		perround+=(2*map[9][1].kind-1)+(map[3][1].kind*map[3][1].side)+(map[9][10].kind*map[9][10].side)+(map[6][6].kind*map[6][6].side*3);
		info->r_source += perround;
		info->round += 1; //仅在红方结束行动后增加回合数
	}
	else
	{
		//没有意识到结构体里是uint型，只能分步计算
		if (map[3][10].kind > 1) //大本营1级
			perround += 1;
		if (map[3][10].kind > 2) //大本营2级
			perround += 2;
		if (map[3][1].kind == 1 && map[3][1].side == 0) //普通资源点是否占领
			perround += 1;
		if (map[9][10].kind == 1 && map[9][10].side == 0) //同上
			perround += 1;
		if (map[6][6].kind == 1 && map[6][6].side == 0) //搞基资源点是否占领
			perround += 3;
		info->b_source += perround;
	}
	*pside = (*pside) ? 0 : 1; //切换阵营
}

//大本营功能函数
void base_func(MAP map, unsigned* source, int side)
{
	POS pos, dpos;
	pos.x = 745;
	pos.y = 705;
	icon(pos, side, BUILDER);
	pos.x = 745 + 65;
	icon(pos, side, INFANTRY);
	pos.x = 745 + 65 * 2;
	icon(pos, side, ARTILLERY);
	pos.x = 745 + 65 * 3;
	icon(pos, side, TANK);
	pos.x = 745 + 65 * 4;
	icon(pos, side, SUPER);
	while (1)
	{
		Newxy();
		//再次点击大本营对大本营进行升级
		if (clcmap(&dpos, map) == 3 && map[D2O(dpos).y][D2O(dpos).x].side == side) //防止花资源给对面升级的投敌行为，待改进
		{
			levelup(dpos, map, source);
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23, FBMP);
			return;
		}
		//点击左下角兵种图标首先显示信息，再次点击进行造兵
		if (mouse_press(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == 1)
		{
			buildarm(map, source, side);
			Clrmous();
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23, FBMP);
			return;
		}

		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)	//右键取消
		{
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23, FBMP);
			show_msg("取消操作", "");
			delay(500);
			return;
		}
	}
}

//大本营升级函数
void levelup(DBL_POS dpos, MAP map, unsigned* source)
{
	OFF_POS opos;
	opos = D2O(dpos);
	if (map[opos.y][opos.x].kind == 3)
	{
		show_msg("大本营已满级", "升级失败");
		delay(1000);
		return;
	}
	else if (*source < (map[opos.y][opos.x].kind == 1 ? 10 : 50)) //一本升二本消耗10资源， 二本升三本消耗50资源
	{
		show_msg("资源不足无法升级", "");
		delay(1000);
		return;
	}
	else
	{
		show_msg("升级成功", "");
		map[opos.y][opos.x].kind += 1;
		delay(1000);
		return;
	}
}

//建造兵种函数
void buildarm(MAP map, unsigned* source, int side)
{
	int armkind = 0;
	Arminfo arminfo;
	POS pos, center, dpos, opos;
	opos.x = !side ? 1 : 10;
	opos.y = !side ? 9 : 3;
	if (mouse_press(745 - 18, 705 - 18, 745 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中工兵
	{
		armkind = BUILDER; //为第二次点选确定兵种值
		show_msg("工兵，造价：2", "再次点选确定建造");
		delay(100); //使用户有时间将鼠标抬起来
	}
	else if (mouse_press(745 + 65 - 18, 705 - 18, 745 + 65 + 18, 705 + 23) == MOUSE_IN_L)//第一次点选选中步兵
	{
		armkind = INFANTRY;
		show_msg("步兵，造价：1", "再次点选确定建造");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中炮兵
	{
		if (map[opos.y][opos.x].kind < 2)
		{
			show_msg("需要大本营等级：2", "建造失败");
			delay(1000);
			return;
		}
		armkind = ARTILLERY;
		show_msg("炮兵，造价：5", "再次点选确定建造");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 3 - 18, 705 - 18, 745 + 65 * 3 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中坦克
	{
		if (map[opos.y][opos.x].kind < 2)
		{
			show_msg("需要大本营等级：2", "建造失败");
			delay(1000);
			return;
		}
		armkind = TANK;
		show_msg("坦克，造价：10", "再次点选确定建造");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 4 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中超级兵
	{
		if (map[opos.y][opos.x].kind < 3)
		{
			show_msg("需要大本营等级：3", "建造失败");
			delay(1000);
			return;
		}
		armkind = SUPER;
		show_msg("超级杀爆全场一个能打三个坦克特种", "突击装甲兵，造价：30。");
		delay(100);
	}
	else
	{
		return;
	}
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 * (armkind - 1) - 18, 705 - 18, 745 + 65 * (armkind - 1) + 18, 705 + 23) == MOUSE_IN_L)
		{
			arminfo = search_info(armkind);
			if (*source < arminfo.cost) //资源不足无法建造
			{
				show_msg("资源不足无法建造", "");
				delay(1000);
				return;
			}
			else if (side == 1) //蓝色方
			{
				if (map[2][10].kind != 0) //判断蓝方出兵点是否被占领
				{
					show_msg("出兵点被占领", "请消灭敌军或先移动我方单位");
					delay(1000);
					return;
				}
				else //建造成功，更新出兵点信息
				{
					map[2][10].kind = armkind;
					map[2][10].health = arminfo.health;
					map[2][10].side = side;
					map[2][10].stay = 0;
					map[2][10].flag = 1;
					center = center_xy(21, 3);
					icon(center, side, armkind);
				}
			}
			else //红色方
			{
				if (map[10][2].kind != 0) //判断红色方出兵点是否被占领
				{
					show_msg("出兵点被占领", "请消灭敌军或先移动我方单位");
					delay(1000);
					return;
				}
				else //建造成功，更新出兵点信息
				{
					map[10][2].kind = armkind;
					map[10][2].health = arminfo.health;
					map[10][2].side = side;
					map[10][2].stay = 0;
					map[10][2].flag = 1;
					center = center_xy(5, 11);
					icon(center, side, armkind);
				}
			}
			//*source -= arminfo.cost;
			show_msg("建造成功！", "");
			delay(1000);
			return;
		}
		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)	//右键取消
		{
			show_msg("取消操作", "");
			delay(500);
			return;
		}
	}
}