/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: battle.c
Author: 刘云笛、陈旭桐
Version:1.3
Description: 对战行为
Date:

更新日志
10.27	完成自动版本行为函数
10.28	攻击函数bug排除
10.29	增加大本营攻击能力
******************************************************************/
#include "common.h"
void move(DBL_POS From, MAP map, int able)
{
	OFF_POS To, ofrom;
	DBL_POS dbto;
	int visit[7][7];

	move_button("移动", 600);
	show_msg("请选择要移动的位置", "点击右键取消");
	memset(visit, 0, sizeof(visit));
	range(map, From, able, 0, visit);
	show_visit(From, visit, Lightbar);//标亮所有可行点
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//需要保证已有行动力
		{
			if (move_(From, dbto, map, visit) == 1)
			{
				return;
			}
			else
			{
				show_msg("此处无法到达", "重新选择目的地");
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//右键取消
		{
			Clrmous();
			show_visit(From, visit, Map_partial);//去标亮，move_里里里（函数套娃）还有一个
			move_button("移动", 65370);
			return;
		}
	}
}
int move_(DBL_POS From, DBL_POS dbto, MAP map, int visit[7][7])
{
	OFF_POS To = D2O(dbto);//求出目标偏移坐标
	if (map[To.y][To.x].kind == NOARMY)//为空可移动，以后还需设置移动能力，还需判断是否原地移动
	{
		return moving(map, visit, From, dbto);
	}
	else
	{
		show_msg("此处已被占领", "");
		move_button("移动", 65370);
		delay(msg_sec);
		return 1;
	}
}

void stay(DBL_POS dpos, MAP map)
{
	OFF_POS opos;
	CELL cell;
	POS center = center_xy(dpos.x, dpos.y);
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
		stay_draw(center);
	}
	delay(msg_sec);
	return;
}

void attack(DBL_POS dpos, MAP map)//攻击功能
{
	OFF_POS opos, to;
	DBL_POS dbto;
	POS center;
	Arminfo info;

	opos = D2O(dpos);
	if (map[opos.y][opos.x].geo == BASE)//增加大本营攻击能力
	{
		info.distance = 1;
		info.attack = 1;
	}
	else
	{
		info = search_info(map[opos.y][opos.x].kind); //读取当前位置兵种信息
	}
	attack_button("攻击", 64032);
	show_msg("请选择要攻击的位置", "右键取消");
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))
		{
			to = D2O(dbto);
			if (map[to.y][to.x].kind) //目标不为空可以攻击
			{
				if (attack_(info, map, dpos, dbto) == 1)
				{
					map[opos.y][opos.x].flag = 1;
					return;
				}
				else
					show_msg("打不到 QAQ", "请重新选择目标");
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//右键取消
		{
			attack_button("攻击", 65370);
			return;
		}
	}
}

int attack_(Arminfo info, MAP map, DBL_POS dpos, DBL_POS dbto)//攻击数值相关函数
{
	POS center = center_xy(dbto.x, dbto.y);//目标点中心坐标
	OFF_POS to = D2O(dbto);//目标点坐标
	OFF_POS opos = D2O(dpos);//攻击者坐标
	if (attack_judge(map, info.distance, dpos, dbto))
	{
		info.attack += map[opos.y][opos.x].stay;//驻扎增加攻击力
		if (map[to.y][to.x].geo == BASE && info.attack > 5)//超级兵不能速推大本营
		{
			info.attack = 1;
		}
		center = center_xy(dbto.x, dbto.y);
		if (map[to.y][to.x].side == map[opos.y][opos.x].side) //目标不可为同阵营
		{
			show_msg("不可以攻击友军！", "你怎么肥四");
			delay(msg_sec);
			return 1;
		}
		else
		{
			if (info.attack >= map[to.y][to.x].health) //目标扑街
			{
				Clrmous();
				map[to.y][to.x].kind = NOARMY;
				show_msg("目标已被歼灭！", "");
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
			return 1;
		}
	}
	else
		return 0;
}

void delarm(DBL_POS dpos, MAP map)
{
	POS center;
	OFF_POS opos;
	center = center_xy(dpos.x, dpos.y);
	opos = D2O(dpos);
	map[opos.y][opos.x].kind = NOARMY;
	show_msg("该部队已撤退！", "");
	delay(msg_sec);
	Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);
	return;
}

//下一回合函数
void nxt_round(MAP map, Battleinfo* info, int *pside)
{
	int i, j, perround = 1;
	Arminfo arminfo;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (map[j][i].kind != NOARMY)
			{
				map[j][i].flag = 0;
				if (map[j][i].faci == MEDICAL && map[j][i].kind != NOARMY)
				{
					arminfo = search_info(map[j][i].kind);
					if(map[j][i].health < arminfo.health) //防止医疗站把血加爆
						map[j][i].health += 1;
				}
			}
		}
	}
	if (*pside)
	{
		/*计算每回合增加资源数的公式，初始每回合一
		* 大本营等级二级：+1 大本营等级三级：+3
		* 普通资源：每占领一个每回合+1
		* 高级资源：每占领一个每回合+3*/
		//perround+=(2*map[9][1].kind-1)+(map[3][1].kind*map[3][1].side)+(map[9][10].kind*map[9][10].side)+(map[6][6].kind*map[6][6].side*3);
		if (map[3][10].kind > 1) //大本营2级
			perround += 1;
		if (map[3][10].kind > 2) //大本营3级
			perround += 2;
		if (map[3][1].faci == BCOLLECTION) //普通资源点是否占领
			perround += 1;
		if (map[9][10].faci == BCOLLECTION) //同上
			perround += 1;
		if (map[6][6].health >= 5 && map[6][6].faci == BCOLLECTION) //搞基资源点是否占领五回合以上
			perround += 3;
		info->b_source += perround;

		/*********以下的判断为真正的一回合，即蓝方结束行动后需要增加的信息**********/
		/**********包括：回合数，资源占领回合数，资源点是否采爆**************/
		if (map[3][1].faci == BCOLLECTION || map[3][1].faci == RCOLLECTION) //每个资源点只能开采20回合, 且只能开采一次
		{
			if(map[3][1].src_rnd < 20)
				map[3][1].src_rnd++;
			else
			{
				map[3][1].faci = NOARMY;
				map[3][1].flag = 1;
			}
		}
		if (map[9][10].faci == BCOLLECTION || map[9][10].faci == RCOLLECTION) //每个资源点只能开采20回合, 且只能开采一次
		{
			if (map[9][10].src_rnd < 20)
				map[9][10].src_rnd++;
			else
			{
				map[9][10].faci = NOARMY;
				map[9][10].flag = 1;
			}
		}
		if (map[6][6].faci == BCOLLECTION || map[6][6].faci == RCOLLECTION) //每个资源点只能开采20回合, 且只能开采一次
		{
			if (map[6][6].src_rnd < 25)
				map[6][6].src_rnd++;
			else
			{
				map[6][6].faci = NOARMY;
			}
		}
	}
	else
	{
		//没有意识到结构体里是uint型，只能分步计算
		if (map[9][1].kind > 1) //大本营2级
			perround += 1;
		if (map[9][1].kind > 2) //大本营3级
			perround += 2;
		if (map[3][1].faci == RCOLLECTION) //普通资源点是否占领
			perround += 1;
		if (map[9][10].faci == RCOLLECTION) //同上
			perround += 1;
		if (map[6][6].src_rnd >= 5 && map[6][6].faci == RCOLLECTION) //搞基资源点是否占领五回合以上
			perround += 3;
		info->r_source += perround;
	}
	info->round += 1; //每点一次下一回合增加一次，即此变量非真正的回合数，(round+1)/2才是真正的回合数
	*pside = (*pside) ? 0 : 1; //切换阵营
}

void next_r_banner(int side)
{
	char* s = side ? "蓝方回合" : "红方回合";
	banner(512 - 240, 300, 480);
	Outtextxx(312 + 40, 300 + 50 - 24, 712 - 40, s, 48, 0);
	delay(msg_sec);
}

//大本营功能函数
void base_func(MAP map, unsigned* source, int is_same_side, DBL_POS dbpos)
{
	POS pos, dpos;
	OFF_POS opos = D2O(dbpos);
	int side = map[opos.y][opos.x].side;
	int flag = map[opos.y][opos.x].flag;
	COLO co;
	pos.x = 745;
	pos.y = 705;
	act_buttons(&co, 0, flag, is_same_side, 0, 1, *source >= air_atk_cost && map[opos.y][opos.x].kind == 3);
	armbuild_draw(pos, side);
	while (1)
	{
		Newxy();
		//大本营的行为按钮
		if (co.mov == (int)OK_co && move_btn_fun(co.mov, 65340, "空袭"))
		{
			air_attack(dbpos, map, source);
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			act_buttons(&co, 0, 1, 0, 0, 0, 0);
			delay(msg_sec / 2);
			return;
		}
		else if (co.atk == (int)OK_co && atk_btn_fun("攻击", co.atk, 65340))
		{
			attack(dbpos, map);
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			act_buttons(&co, 0, 1, 0, 0, 0, 0);
			delay(msg_sec / 2);
			return;
		}
		//再次点击大本营对大本营进行升级
		else if (clcmap(&dpos, map) == 3 && map[D2O(dpos).y][D2O(dpos).x].side == side) //防止花资源给对面升级的投敌行为
		{
			levelup(dpos, map, source);
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			act_buttons(&co, 0, 1, 0, 0, 0, 0);
			return;
		}
		//点击左下角兵种图标首先显示信息，再次点击进行造兵
		else if (mouse_press(745-18, 705-18, 745+65*4+18, 705+23) == 1)
		{
			buildarm(map, source, side);
			act_buttons(&co, 0, 1, 0, 0, 0, 0);
			Clrmous();
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			return;
		}
		//右键或点击外侧取消操作
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R || mouse_press(45-18, 705-18, 745+65*4+18, 705+23) == MOUSE_OUT_L)	//右键取消
		{
			Clrmous();
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			act_buttons(&co, 0, 1, 0, 0, 0, 0);
			show_msg("取消操作", "");
			delay(msg_sec/2);
			return;
		}
	}
}
void armbuild_draw(POS pos, int side)
{
	Map_partial(740, 670, 980, 742);
	icon(pos, side, BUILDER);
	pos.x = 745 + 65;
	icon(pos, side, INFANTRY);
	pos.x = 745 + 65 * 2;
	icon(pos, side, ARTILLERY);
	pos.x = 745 + 65 * 3;
	icon(pos, side, TANK);
	pos.x = 745 + 65 * 4;
	icon(pos, side, SUPER);
}
//大本营升级函数
void levelup(DBL_POS dpos, MAP map, unsigned* source)
{
	OFF_POS opos = D2O(dpos);
	int cost = (map[opos.y][opos.x].kind == 1 ? lev2_cost : lev3_cost);
	if (map[opos.y][opos.x].kind == 3)
	{
		show_msg("大本营已满级", "升级失败");
		delay(msg_sec);
		return;
	}
	else if (*source < cost) //一本升二本消耗10资源， 二本升三本消耗50资源
	{
		show_msg("资源不足无法升级", "");
		delay(msg_sec);
		return;
	}
	else
	{
		show_msg("升级成功", "");
		map[opos.y][opos.x].kind++;
		Bar64k(0, 0, 204, 100, 65370);
		Filltriangle(0, 100, 0, 350, 204, 100, 65370);
		disp_geo_info(map[opos.y][opos.x]);
		*source -= cost;
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
		show_msg("工兵，造价：2", "再次点选确定建造，右键取消");
		delay(100); //使用户有时间将鼠标抬起来
	}
	else if (mouse_press(745 + 65 - 18, 705 - 18, 745 + 65 + 18, 705 + 23) == MOUSE_IN_L)//第一次点选选中步兵
	{
		armkind = INFANTRY;
		show_msg("步兵，造价：1", "再次点选确定建造，右键取消");
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
		show_msg("炮兵，造价：5", "再次点选确定建造，右键取消");
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
		show_msg("坦克，造价：10", "再次点选确定建造，右键取消");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 4 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中超级兵
	{
		if (map[opos.y][opos.x].kind < 3)
		{
			show_msg("需要大本营等级：3", "建造失败，右键取消");
			delay(msg_sec);
			return;
		}
		armkind = SUPER;
		show_msg("超级兵，造价：30。", "再次点选确定建造，右键取消");
		delay(100);
	}
	else
	{
		return;
	}
	while (1)
	{
		Newxy();
		if (press == 1)
		{
			if (Mouse_above(745 + 65 * (armkind - 1) - 18, 705 - 18, 745 + 65 * (armkind - 1) + 18, 705 + 23))
			{
				arminfo = search_info(armkind);
				if (*source < arminfo.cost) //资源不足无法建造
				{
					show_msg("资源不足无法建造", "");
					delay(msg_sec);
					return;
				}
				else if (side == 1) //蓝色方
				{
					if (map[2][10].kind != 0) //判断蓝方出兵点是否被占领
					{
						show_msg("出兵点被占领", "请消灭敌军或先移动我方单位");
						delay(msg_sec);
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
						delay(msg_sec);
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
				*source -= arminfo.cost;
				show_msg("操作成功！", "");
				delay(msg_sec);
				return;
			}
			else//别处点击
			{
				show_msg("取消操作", "");
				delay(500);
				return;
			}
		}
		else if (press == 2)	//右键取消
		{
			show_msg("取消操作", "");
			delay(500);
			return;
		}
	}
}

void builder_build(DBL_POS dpos, MAP map, Battleinfo *batinfo)
{
	OFF_POS opos = D2O(dpos);
	POS center = center_xy(dpos.x, dpos.y);
	int source = map[opos.y][opos.x].side == 0 ? (batinfo->r_source): (batinfo->b_source);
	if (map[opos.y][opos.x].faci != NOFACI)
	{
		show_msg("此处已有设施！", "");
	}
	else if (map[opos.y][opos.x].geo == SORC || map[opos.y][opos.x].geo == HSORC)
	{
		map[opos.y][opos.x].faci = (map[opos.y][opos.x].side == 0 ? RCOLLECTION : BCOLLECTION);
		collection_draw(center, map[opos.y][opos.x].side);
		show_msg("采集站建造成功！", "已开始采集资源");
	}
	else
	{
		if (source < 10)
		{
			show_msg("所需资源：10", "资源不足，建造失败！");
			delay(msg_sec);
			return;
		}
		map[opos.y][opos.x].side == 0 ? (batinfo->r_source -= 10) : (batinfo->b_source -= 10);
		map[opos.y][opos.x].faci = MEDICAL;
		medical_draw(center);
		show_msg("医疗站建造成功！", "已可以进行治疗");
	}
	map[opos.y][opos.x].flag = 1;
	disp_bat_info(*batinfo);
	delay(1000);
	return;
}

void air_attack(DBL_POS pos, MAP map, unsigned *source)
{
	OFF_POS opos = D2O(pos), oto;
	DBL_POS dbto;
	int side = map[opos.y][opos.x].side;
	show_msg("花费40资源空袭一个位置", "右键取消");
	move_button("空袭", 64032);
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))
		{
			oto = D2O(dbto);
			if (map[oto.y][oto.x].faci)
			{
				air_boom(map, oto, opos);
				*source -= air_atk_cost;
				return;
			}
			else if (map[oto.y][oto.x].kind)
			{
				if (map[oto.y][oto.x].side == side)
				{
					show_msg("喂，你打自己人干嘛", "重新选择一个空袭位置");
					delay(msg_sec);
				}
				else
				{
					if (map[oto.y][oto.x].geo == BASE)
					{
						show_msg("好孩子是不可以炸别人家的", "重新选择一个空袭位置");
						delay(msg_sec);
					}
					else
					{
						air_boom(map, oto, opos);
						*source -= air_atk_cost;
						return;
					}
				}
			}
			else
			{
				show_msg("喂，你打空地干嘛", "重新选择一个空袭位置");
				delay(msg_sec);
			}
		}
		if (press == 2)
		{
			show_msg("空袭取消", "");
			delay(msg_sec);
			return;
		}
	}
}
void air_boom(MAP map, OFF_POS oto, OFF_POS from)
{
	DBL_POS dbto = O2D(oto);
	show_msg("轰轰火花，把这里全-都炸完！", "趁对面发现之前，开溜！");
	map[oto.y][oto.x].kind = 0;
	map[oto.y][oto.x].faci = 0;
	map[from.y][from.x].flag = 1;
	Clrmous();
	recover_cell(dbto, map);
	delay(msg_sec);
}