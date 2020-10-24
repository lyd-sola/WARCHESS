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
	int clccell = 0;//点击过地图上的一个格子
	int flag;
	char filename[25] = "SAVES//";	FILE* fp;
	COLO co;

	DBL_POS test;
	
	strcat(filename, user);
	if ((fp = fopen(filename, "rb+")) == NULL)
		show_error("未找到用户存档文件", 1);
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	fclose(fp);
	
	change_co(&co, 0, 1);
	battle_draw();

	map[6][6].side = 1;
	map[6][6].kind = BUILDER;
	map[6][6].health = 2;
	map[6][6].flag = 0;
	map[6][5].side = 0;
	map[6][5].kind = INFANTRY;
	map[6][5].flag = 0;//test
	initdraw(map);

	while(1)
	{
		Newxy();
		show_msg("请指挥官进行操作", "");

		if (nxt_btn_fun(65370, 65340))
		{
			next_round(map, &(batinfo.round));
		}

		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			opos = D2O(ptmp);
			if (flag == 2)
			{
				pos = ptmp;
				clccell = 1;
				show_msg("已选择一个单位", "请选择行为");
				disp_geo_info(map[opos.y][opos.x]);
				arminfo = disp_arm_info(map[opos.y][opos.x]);//显示信息
				change_co(&co, map[opos.y][opos.x].kind, map[opos.y][opos.x].flag);
				act_buttons(co);
			}
			else
			{
				clccell = 0;
				disp_geo_info(map[opos.y][opos.x]);
				disp_arm_info(map[opos.y][opos.x]);
		 		show_msg("该区域为空", "");
				change_co(&co, 0, 1);
				act_buttons(co);
				delay(1000);
			}
		}

		if (clccell && move_btn_fun(co.mov, 65340))//移动
		{
			move(pos, map, arminfo.move);
			clccell = 0;
			move_button(co.mov);
		}
		if (clccell && stay_btn_fun("驻扎", co.stay, 65340))//驻扎
		{
			stay(pos, map);
			clccell = 0;
		}
		if (clccell && atk_btn_fun("攻击", co.atk, 65340))//攻击
		{
			attack(pos, map);
			clccell = 0;
		}
		if (clccell && del_btn_fun(co.del, 65340))//删除
		{
			delarm(pos, map);
			clccell = 0;
		}


		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//为方便调试,左上角右键直接退出
		{
			exit(0);
		}

		if (rec_btn_fun(800, 10, 800 + 49, 10 + 34, 65370))//快速保存
		{
			if (msgbar("确定", "取消", "保存存档，确定吗", ""))
			{
				fp = fopen(filename, "rb+");
				seek_savinfo(fp, save_num, 0, 0);
				save_battle(fp, batinfo, map);
				fclose(fp);
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

	nextr_button(65370);
	attack_button("攻击", CANT_co);
	stay_button("驻扎", CANT_co);
	move_button(CANT_co);
	del_button(CANT_co);

	//选项菜单
	save_btn(65370);
	exit_btn(65370);
	option_btn(65370);
}
/*画出一个格子上的兵种符号*/
void draw_cell(DBL_POS pos, MAP map)
{

	int kind, side;
	POS offpos;

	offpos = D2O(pos);

	kind = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;

	pos = center_xy(pos.x, pos.y);
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

void disp_geo_info(CELL cell)
{
	char text[20] = "所需行动力", buffer[20];
	/*static CELL lastcell1;
	if (lastcell1.geo == cell.geo)
		return;*/
	itoa(move_cost(cell.geo), buffer, 10);
	strcat(text, buffer);

	Bar64k(0, 0, 204, 100, 65370);
	//Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	
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
		Outtext(20, 20, "大本营", 32, 48, 0);
		break;
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
	//lastcell1 = cell;
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

void act_buttons(COLO co)
{
	attack_button("攻击", co.atk);
	stay_button("驻扎", co.stay);
	move_button(co.mov);
	del_button(co.del);
}
void change_co(COLO* co, int kind, int flag)
{
	if (flag)
	{
		co->atk = CANT_co;
		co->del = CANT_co;
		co->mov = CANT_co;
		co->stay = CANT_co;
	}
	else 
	{
		co->atk = OK_co;
		co->del = OK_co;
		co->mov = OK_co;
		co->stay = OK_co;
		if (kind == BUILDER)
		{
			co->atk = CANT_co;
		}
	}
}