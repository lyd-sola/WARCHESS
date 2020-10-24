/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: battle.c
Author: 刘云笛、陈旭桐
Version: 
Description: 战斗界面
Date:

更新日志

函数目录
******************************************************************/

#include "common.h"
//战斗界面主函数
int battle(char *user, short save_num, short mode)
{
	CELL map[13][13], cell;//地图
	DBL_POS pos, ptmp;
	OFF_POS opos;
	Battleinfo batinfo;//对战信息
	Arminfo arminfo;//兵种信息暂存
	int clccell = 0;//点击过地图上一个格子
	int flag, msgflag = 0;
	int side = 0;//标记当前阵营
	char filename[25] = "SAVES//";
	FILE* fp;

	DBL_POS test;
	
	strcat(filename, user);
	if ((fp = fopen(filename, "rb+")) == NULL)
		show_error("未找到用户存档文件", 1);
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	battle_draw();
	//map[6][6].side = 1;
	//map[6][6].kind = BUILDER;
	//map[6][5].side = 2;
	//map[6][5].kind = INFANTRY;
	initdraw(map);

	//大本营信息的初始化，应放入初始化存档界面？
	map[3][10].side = 0;
	map[9][1].side = 1;
	map[3][10].kind = 1;
	map[9][1].kind = 1;
	batinfo.b_source = 50;

	while(1)
	{
		Newxy();
		if (nxt_btn_fun(65370, 65340))
		{
			show_msg("进行下一回合", "");
			nxt_round(map, &batinfo, &side);
			delay(1000);
		}
		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			msgflag = 1;
			opos = D2O(ptmp);
			if (map[opos.y][opos.x].side != side && map[opos.y][opos.x].kind != NOARMY)
			{
				show_msg("此为敌方单位，不可操作！", "");
				disp_geo_info(map[opos.y][opos.x]);
				disp_arm_info(map[opos.y][opos.x]);
				continue;
			}
			if (flag == 3)
			{
				clccell = 0;
				disp_arm_info(map[opos.y][opos.x]); 
				disp_geo_info(map[opos.y][opos.x]);
				show_msg("保护我方大本营！", "再次点选进行升级");
				delay(50);
				base_func(map, side ? (&batinfo.r_source) : (&batinfo.b_source), side);
			}
			if (flag == 2)
			{
				pos = ptmp;
				clccell = 1;
				show_msg("已选择一个单位", "请选择行为");
				/*******************显示信息********************/
				disp_geo_info(map[opos.y][opos.x]);
				arminfo = disp_arm_info(map[opos.y][opos.x]);
			}
			else
			{
				clccell = 0;
				disp_geo_info(map[opos.y][opos.x]);
				disp_arm_info(map[opos.y][opos.x]); //清空其中的静态结构体变量
		 		show_msg("该区域为空", "");
			}
		}

		if (clccell && move_btn_fun(65370, 65340))//移动
		{
			move(pos, map, arminfo.move);
			clccell = 0;
			msgflag = 0;
			delay(50);//这个delay很重要，用于给用户时间抬起鼠标左键（move有动画后可以删除）
		}

		if (clccell && stay_btn_fun("驻扎", 65370, 65340))//驻扎
		{
			stay(pos, map);
			clccell = 0;
			msgflag = 0;
		}

		if (clccell && atk_btn_fun("攻击", 65370, 65340))//攻击
		{
			attack(pos, map);
			clccell = 0;
			msgflag = 0;
		}

		if (clccell && del_btn_fun(65370, 65340))//删除
		{
			delarm(pos, map);
			clccell = 0;
			msgflag = 0;
		}

		if (msgflag == 0)
		{
			show_msg("请指挥官进行操作", "");
			msgflag = 1;
		}

		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//为方便调试,左上角右键直接退出
		{
			exit(0);
		}

		if (rec_btn_fun(800, 10, 800 + 49, 10 + 34, 65370))//快速保存
		{
			if (msgbar("确定", "取消", "保存存档，确定吗", ""))
			{
				seek_savinfo(fp, save_num, 0, 0);
				save_battle(fp, batinfo, map);
			}
			Clrmous();
			Map_partial(262, 218, 262 + 500, 219 + 230, FBMP);
			initdraw(map);
		}
		if (rec_btn_fun(880, 10, 880 + 49, 44, 65370))//选项菜单
		{
			return MAINMENU;
		}
		if (rec_btn_fun(960, 10, 960 + 49, 44, 65370))//叉叉
		{
			if (msgbar("确定", "取消", "退出会丢失未保存的进度", "确定退出吗？"))
			{
				fclose(fp);
				return MAINMENU;
			}
			else
			{
				Clrmous();
				Map_partial(262, 218, 262 + 500, 219 + 230, FBMP);
				initdraw(map);
			}
		}
	}
}
//绘制战斗界面函数
void battle_draw()
{
	Clrmous();
	Putbmp64k(0, 0, "BMP//map.bmp");

	attack_button("攻击", 65370);
	stay_button("驻扎", 65370);
	move_button(65370);
	del_button(65370);
	nextr_button(65370);

	//选项菜单
	save_btn(65370);
	exit_btn(65370);
	option_btn(65370);
}
/*画出一个格子上的兵种符号*/
void draw_cell(DBL_POS pos, MAP map)
{

	int kind, side, geo;
	POS offpos;

	offpos = D2O(pos);

	kind = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;
	geo = map[offpos.y][offpos.x].side;
	pos = center_xy(pos.x, pos.y);
	//防止初始化界面时因为kind不等于0把大本营和资源画错
	switch (geo)
	{
	case BASE:
		return;
	case SORC:
		return;
	case HSORC:
		return;
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

void initdraw(MAP map)
{
	int i, j;
	OFF_POS opos;
	DBL_POS dpos;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			opos.x = i;
			opos.y = j;
			dpos = O2D(opos);
			draw_cell(dpos, map);
		}
	}
}

void icon(POS world_pos, int side, int kind)
{
	switch (kind)
	{
	case BUILDER:
		Icon_builder(world_pos, side);
		break;
	case INFANTRY:
		Icon_inf(world_pos, side);
		break;
	case ARTILLERY:
		Icon_arti(world_pos, side);
		break;
	case TANK:
		Icon_tank(world_pos, side);
		break;
	case SUPER:
		Icon_super(world_pos, side);
		break;
	default:
		Icon_draw(world_pos, side);
		break;
	}
}

/*搜索兵种信息，仅在disp函数中调用*/

Arminfo search_info(int kind)
{
	FILE* fp;
	char buffer[20];
	Arminfo info;
	int i;
	if ((fp = fopen("DATA//info.txt", "r")) == NULL)
	{
		show_error("兵种信息文件丢失", 1);
		fclose(fp);
		return info;
	}
	for (i = 1; i < kind; i++) //跳至第n个兵种
	{
		fgets(buffer, sizeof(buffer), fp);
		buffer[0] = '\0';
	}
	fscanf(fp, "%d%d%d%d%d", &info.health, &info.attack, &info.move, &info.cost, &info.distance);
	fclose(fp);
	return info;
}

//显示当前位置地形信息
void disp_geo_info(CELL cell)
{
	char text[20] = "所需行动力", text1[20] = "生命值 ", text2[20] = "等级 ";
	char buffer[20], buffer1[20], buffer2[20];
	static CELL lastcell1;
	if (lastcell1.geo == cell.geo)
		return;
	itoa(move_cost(cell.geo), buffer, 10);
	strcat(text, buffer);
	Bar64k(0, 0, 204, 100, 65370);
	switch (cell.geo)
	{
	case OBSTACLE: 
		Outtext(20, 20, "障碍", 32, 48, 0);
		break;
	case PLAIN: 
		Outtext(20, 20, "平原", 32, 48, 0);
		break;
	case FOREST: 
		Outtext(20, 20, "森林", 32, 48, 0);
		break;
	case DESERT:
		Outtext(20, 20, "沙漠", 32, 48, 0);
		break;
	case BASE:
		itoa(cell.health, buffer1, 10);
		strcat(text1, buffer1);
		itoa(cell.kind, buffer2, 10);
		strcat(text2, buffer2);
		Outtext(20, 20, "大本营", 32, 48, 0);
		Outtext(20, 70, text1, 16, 20, 0);
		Outtext(20, 100, text2, 16, 20, 0);
		lastcell1 = cell;
		return;
	case SORC:
		Outtext(20, 20, "资源点", 32, 48, 0);
		break;
	case HSORC:
		Outtext(20, 20, "资源点", 32, 48, 0);
		break;
	default:
		break;
	}
	cell.geo ? Outtext(20, 70, text, 16, 20, 0) : Outtext(20, 70, "不可逾越", 16, 20, 0);
	lastcell1 = cell;
}

/********显示当前鼠标位置兵种信息*********/
Arminfo disp_arm_info(CELL cell)
{
	Arminfo info;
	char buffer[20] = "\0";
	//static CELL lastcell2;
	//if (lastcell2.kind == cell.kind && lastcell2.health == cell.health)
	//	return;
	info = search_info(cell.kind);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	//因为存档中的兵种用来存储信息了，这里需要特判
	if (cell.geo == BASE || cell.geo == SORC || cell.geo == HSORC)
		return;

	switch (cell.kind)
	{
	case BUILDER:
		Outtextxx(15, 120, 110, "兵种  工兵", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(15, 140, 75, "生命值", 16, 0);
		Outtext(85, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(15, 160, 75, "攻击力", 16, 0);
		Outtext(85, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(15, 180, 75, "行动力", 16, 0);
		Outtext(85, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(15, 200, 75, "射程", 16, 0);
		Outtext(85, 200, buffer, 16, 16, 0);
		break;

	case INFANTRY:
		Outtextxx(15, 120, 110, "兵种  步兵", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(15, 140, 75, "生命值", 16, 0);
		Outtext(85, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(15, 160, 75, "攻击力", 16, 0);
		Outtext(85, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(15, 180, 75, "行动力", 16, 0);
		Outtext(85, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(15, 200, 75, "射程", 16, 0);
		Outtext(85, 200, buffer, 16, 16, 0);
		break;
	default:
		break;
	}
	//lastcell2 = cell;
	return info;
}

//大本营功能函数
void base_func(MAP map, int *source, int side)
{
	POS pos,dpos;
	pos.x = 745;
	pos.y = 705;
	icon(pos, side, BUILDER);
	pos.x = 745+65;
	icon(pos, side, INFANTRY);
	pos.x = 745+65*2;
	icon(pos, side, ARTILLERY);
	pos.x = 745+65*3;
	icon(pos, side, TANK);
	pos.x = 745+65*4;
	icon(pos, side, SUPER);
	while (1)
	{
		Newxy();
		//再次点击大本营对大本营进行升级
		if (clcmap(&dpos, map) == 3 && map[D2O(dpos).y][D2O(dpos).x].side == side) //防止花资源给对面升级的投敌行为，待改进
		{
			levelup(dpos, map, source);
			Map_partial(745-18, 705-18, 745+65*4+18, 705+23, FBMP);
			return;
		}
		//点击左下角兵种图标首先显示信息，再次点击进行造兵
		if (mouse_press(745-18, 705-18, 745+65*4+18, 705+23) == 1)
		{
			buildarm(map, source, side);
			Clrmous();
			Map_partial(745-18, 705-18, 745+65*4+18, 705+23, FBMP);
			return;
		}

		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)	//右键取消
		{
			Map_partial(745-18, 705-18, 745+65*4+18, 705+23, FBMP);
			show_msg("取消操作", "");
			delay(500);
			return;
		}
	}
}

//大本营升级函数
void levelup(DBL_POS dpos, MAP map, int *source)
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
void buildarm(MAP map, int *source, int side)
{
	int armkind = 0;
	Arminfo arminfo;
	POS pos, center, dpos, opos;
	opos.x = side ? 1 : 10;
	opos.y = side ? 9 : 3;
	if (mouse_press(745 - 18, 705 - 18, 745 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中工兵
	{
		armkind = BUILDER; //为第二次点选确定兵种值
		show_msg("工兵，造价：2", "再次点选确定建造");
		delay(100); //使用户有时间将鼠标抬起来
	}
	if (mouse_press(745 + 65 - 18, 705 - 18, 745 + 65 + 18, 705 + 23) == MOUSE_IN_L )//第一次点选选中步兵
	{
		armkind = INFANTRY;
		show_msg("步兵，造价：1", "再次点选确定建造");
		delay(100);
	}
	if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中炮兵
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
	if (mouse_press(745 + 65 * 3 - 18, 705 - 18, 745 + 65 * 3 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中坦克
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
	if (mouse_press(745 + 65 * 4 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == MOUSE_IN_L) //第一次点选选中超级兵
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
	while (1)
	{
		Newxy();
		if (mouse_press(745+65*(armkind-1)-18, 705-18, 745+65*(armkind-1)+18, 705+23) == MOUSE_IN_L)
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
				if (map[10][2].kind != 0) //判断蓝色方出兵点是否被占领
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
					center = center_xy(5, 11);
					icon(center, side, armkind);
				}
			}
			else //红色方
			{
				if (map[2][10].kind != 0) //判断红方出兵点是否被占领
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
					center = center_xy(21, 3);
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