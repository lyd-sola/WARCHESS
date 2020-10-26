/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: battle.c
Author: 刘云笛、陈旭桐
Version: 1.0
Description: 战斗界面
Date:

更新日志
	10.25前	部分功能实现beta残缺版
	10.25	1.0版本
			实现按钮灰色时无法点击，解决部分msg问题，缩短battle长度
函数目录
******************************************************************/

#include "common.h"
//战斗界面主函数
int battle(char *user, short save_num, short mode)
{
	CELL map[13][13];//地图
	DBL_POS pos;
	Battleinfo batinfo;//对战信息
	Arminfo arminfo;//兵种信息暂存
	int clccell = 0;//点击过地图上的一个格子
	int flag, msgflag = 0;
	int side;//标记当前阵营
	FILE* fp;
	COLO co;
	load_battle(user, save_num, &batinfo, map, &fp);//读取存档
	battle_draw();//界面绘制
	act_buttons(&co, 0, 1, 0);//行为按钮
	disp_bat_info(batinfo);//对战信息（回合资源）
	side = (batinfo.round - 1) % 2;
	initdraw(map);//单位绘制
	next_r_banner(side);//画banner，自带delay
	Map_partial(512 - 240 - 75, 300, 512 + 240 + 75, 300 + 125);
	initdraw(map);//单位绘制
	while(1)
	{
		Newxy();
		if (!msgflag)
		{
			show_msg("请指挥官进行操作", "");
			msgflag = 1;
		}
		if (nxt_btn_fun(65370, 65340))
		{
			nxt_round(map, &batinfo, &side);
			disp_bat_info(batinfo);
			next_r_banner(side);//画banner，自带delay
			Map_partial(512-240-75, 300, 512+240+75, 300+125);
			initdraw(map);//还原
		}
		first_click(map, &pos, &clccell, &msgflag, &arminfo, &batinfo, &co);//点击地图上一个点
		if (clccell)//所有行为按钮
		{
			act_btn(map, &co, &clccell, pos, &arminfo);
			if (!clccell)
			{
				act_buttons(&co, 0, 1, 0);
				msgflag = 0;
				delay(300);
			}
		}
		if ((flag = opt_btn(fp, save_num, map, &batinfo)) != BATTLE)//右上角选项菜单区
		{
			return flag;
		}
		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//为方便调试,左上角右键直接退出
		{
			fclose(fp);
			exit(0);
		}
	}
}
//绘制战斗界面函数
void battle_draw()
{
	Clrmous();
	Map_partial(0, 0, 1024, 768);
	//Putbmp64k(0, 0, "BMP//map.bmp");

	Bar64k(0, 0, 204, 100, 65370);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
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
	geo = map[offpos.y][offpos.x].geo;
	pos = center_xy(pos.x, pos.y);
	//防止初始化界面时因为kind不等于0把大本营和资源画错
	switch (geo)
	{
	case BASE:
		//Map_partial(pos.x - 18, pos.y - 18, pos.x + 18, pos.y + 23);
	case SORC:
	case HSORC:
	case OUT_MAP:
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
	char text[20];	Bar64k(0, 0, 204, 100, 65370);
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
		sprintf(text, "生命值 %d", cell.health);
		Outtext(20, 70, text, 16, 20, 0);
		sprintf(text, "等级 %d", cell.kind);
		Outtext(20, 100, text, 16, 20, 0);
		if (cell.kind < 3)
		{
			sprintf(text, "升级花费 %d", cell.kind == 1 ? 10 : 50);
			Outtext(20, 130, text, 16, 20, 0);
		}
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
	sprintf(text, "所需行动力 %d", move_cost(cell.geo));
	cell.geo ? Outtext(20, 70, text, 16, 20, 0) : Outtext(20, 70, "不可逾越", 16, 20, 0);
}

/********显示当前鼠标位置兵种信息*********/
Arminfo disp_arm_info(CELL cell)
{
	Arminfo info;
	char buffer[20] = "\0";
	info = search_info(cell.kind);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	if (cell.geo == BASE || cell.geo == SORC || cell.geo == HSORC)
		return info;

	switch (cell.kind)
	{
	case BUILDER:
		Outtext(30, 100, "工兵", 24, 35, 0);
		break;
	case INFANTRY:
		Outtext(30, 100, "步兵", 24, 35, 0);
		break;
	case ARTILLERY:
		Outtext(30, 100, "炮兵", 24, 35, 0);
		break;
	case TANK:
		Outtext(30, 100, "坦克", 24, 35, 0);
		break;
	case SUPER:
		Outtext(30, 100, "超级兵", 24, 30, 0);
		break;
	default:
		return info;
	}

	itoa(cell.health, buffer, 10);
	Outtextxx(15, 130, 75, "生命值", 16, 0);
	Outtext(85, 130, buffer, 16, 16, 0);
	itoa(info.attack, buffer, 10);
	Outtextxx(15, 150, 75, "攻击力", 16, 0);
	Outtext(85, 150, buffer, 16, 16, 0);
	itoa(info.move, buffer, 10);
	Outtextxx(15, 170, 75, "行动力", 16, 0);
	Outtext(85, 170, buffer, 16, 16, 0);
	itoa(info.distance, buffer, 10);
	Outtextxx(15,190, 75, "射程", 16, 0);
	Outtext(85, 190, buffer, 16, 16, 0);
	return info;
}

void disp_bat_info(Battleinfo batinfo)
{
	char buffer[20];
	int x = 25;
	Map_partial(740+x, 670, 980+x, 700);//还原行动方
	Map_partial(20 + 4 * 32, 715, 315+x, 747);//还原资源数
	if (batinfo.round % 2)//回合数显示
	{
		Map_partial(740 + x, 700, 980 + x, 742);//还原回合数
		sprintf(buffer, "回合数");
		Outtext(740 + x, 710, buffer, 32, 40, 0);
		sprintf(buffer, "%d", (batinfo.round + 1) / 2);
		Outtext(740+32*4 + x, 710, buffer, 32, 32, 0);
	}
	Outtext(20, 715, "资源数", 32, 40, 0);
	if ((batinfo.round + 1)% 2)//资源显示
	{
		sprintf(buffer, "%d", batinfo.r_source);
		Outtext(740+x, 670, "红军行动", 32, 40, 0);
		Outtext(20+4*32, 715, buffer, 32, 40, 0);
	}
	else
	{
		sprintf(buffer, "%d", batinfo.b_source);
		Outtext(740+x, 670, "蓝军行动", 32, 40, 0);
		Outtext(20+4*32, 715, buffer, 32, 40, 0);
	}
}

/*绘制行为按钮*/
void act_buttons(COLO *co, int kind, int flag, int is_same_side)
{
	if (flag || !is_same_side)
	{
		co->atk = CANT_co;
		co->del = CANT_co;
		co->mov = CANT_co;
		co->stay = CANT_co;
	}
	else
	{
		co->del = OK_co;
		co->mov = OK_co;
		co->stay = OK_co;
		co->atk = OK_co;
	}
	if (kind == BUILDER)
	{
		attack_button("建造", co->atk);
	}
	else
	{
		attack_button("攻击", co->atk);
	}
	stay_button("驻扎", co->stay);
	move_button(co->mov);
	del_button(co->del);
}
/*按钮整合函数，灰色状态不能点击*/
void act_btn(MAP map, COLO* co, int* clccell, DBL_POS pos, Arminfo* arminfo)
{
	if (co->mov == (int)OK_co)
	{
		if (move_btn_fun(co->mov, 65340))//移动
		{
			move(pos, map, arminfo->move);
			*clccell = 0;
			move_button(co->mov);
			delay(50);//这个delay很重要，用于给用户时间抬起鼠标左键（move有动画后可以删除）
		}
	}
	if (co->stay == (int)OK_co)
	{
		if (stay_btn_fun("驻扎", co->stay, 65340))//驻扎
		{
			stay(pos, map);
			*clccell = 0;
		}
	}
	if (co->atk == (int)OK_co)
	{
		if (atk_btn_fun("攻击", co->atk, 65340))//攻击
		{
			attack(pos, map);
			*clccell = 0;
		}
	}
	if (co->del == (int)OK_co)
	{
		if (del_btn_fun(co->del, 65340))//删除
		{
			delarm(pos, map);
			*clccell = 0;
		}
	}
}
/*点击地图上一点，会改变clccell状态，记录pos，调用大本营相关函数*/
void first_click(MAP map, DBL_POS *pos, int *clccell, int *msgflag, Arminfo *arminfo, Battleinfo *batinfo, COLO *co)
{
	int flag, side = (batinfo->round - 1) % 2;
	DBL_POS ptmp;
	OFF_POS opos;
	if ((flag = clcmap(&ptmp, map)) != 0)
	{
		opos = D2O(ptmp);
		*arminfo = disp_arm_info(map[opos.y][opos.x]);//显示信息
		disp_geo_info(map[opos.y][opos.x]);
		if (map[opos.y][opos.x].side != side && map[opos.y][opos.x].kind != NOARMY) //点击敌方单位
		{
			*clccell = 0;
			show_msg("此为敌方单位，不可操作！", "");
			delay(msg_sec);
			*msgflag = 0;
			return;
		}
		if (map[opos.y][opos.x].flag)
		{
			*clccell = 0;
			show_msg("该单位无行动力", "下一回合再来操作吧");
			delay(msg_sec);
			*msgflag = 0;
			return;
		}
		switch (flag)
		{
		case 1:		//点空
			*clccell = 0;
			show_msg("该区域为空", "");
			act_buttons(co, 0, 1, 0);
			break;
		case 2:		//点击己方单位
			*pos = ptmp;
			*clccell = 1;
			show_msg("已选择一个单位", "请选择行为");
			act_buttons(co, map[opos.y][opos.x].kind, map[opos.y][opos.x].flag,
				map[opos.y][opos.x].side == side);
			break;
		case 3:		//点击大本营
			*clccell = 0;
			show_msg("再次点选进行升级！", "右键取消");
			delay(50);
			base_func(map, side ? &(batinfo->r_source) : &(batinfo->b_source), side);
			disp_bat_info(*batinfo);
			act_buttons(co, 0, 1, 0);
			*msgflag = 0;
			break;
		}
	}
}
/*右上角选项菜单区*/
int opt_btn(FILE *fp, int save_num, MAP map, Battleinfo *batinfo)
{
	int flag, side = (batinfo->round - 1) % 2;
	char* s, msg[30];
	if (rec_btn_fun(800, 10, 800 + 49, 10 + 34, 65370))//快速保存
	{
		if (msgbar("确定", "取消", "保存存档，确定吗?", ""))
		{
			seek_savinfo(fp, save_num, 0, 0);
			save_battle(fp, *batinfo, map);
		}
		Clrmous();
		Map_partial(262, 218, 262 + 500, 219 + 230);
		initdraw(map);
	}
	if (rec_btn_fun(880, 10, 880 + 49, 44, 65370))//选项菜单
	{
		draw_opts();
		flag = opts_fun(side);
		switch (flag)
		{
		case BATTLE://关闭选项
			return BATTLE;
		case EXIT://保存并退出
			if (msgbar("确定", "不了", "即将保存战斗并退出程序", "确定吗?"))
			{
				seek_savinfo(fp, save_num, 0, 0);
				save_battle(fp, *batinfo, map);
				fclose(fp);
				exit(0);
			}
			else
			{
				Map_partial(262, 218, 262 + 500, 219 + 230);
				Map_partial(837, 46, 976, 88 + 41 * 2);
				initdraw(map);
				return BATTLE;
			}
		case HOMEPAGE://注销
			if (msgbar("确定", "不了", "即将注销", "确定吗?"))
			{
				return HOMEPAGE;
			}
			else
			{
				Map_partial(262, 218, 262 + 500, 219 + 230);
				Map_partial(837, 46, 976, 88 + 41 * 2);
				initdraw(map);
				return BATTLE;
			}
		case 444://认输
			s = side ? "红" : "蓝";
			sprintf(msg, "%s方即将认输", s);
			if (msgbar("不了", "坚持", msg, "真的不再坚持一下吗?"))
			{
				if(msgbar("是的", "嘻嘻", msg, "真的是本人操作吗？"))
					side ? (map[3][10].health = 0) : (map[9][1].health = 0);
			}
			Map_partial(262, 218, 262 + 500, 219 + 230);
			Map_partial(837, 46, 976, 88 + 41 * 2);
			initdraw(map);
			return BATTLE;
		}
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
			Map_partial(262, 218, 262 + 500, 219 + 230);
			initdraw(map);
		}
	}
	return BATTLE;
}