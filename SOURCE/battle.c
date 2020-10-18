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
	char s[25] = "SAVES//";
	char tst[20] = "\0";
	FILE* fp;

	DBL_POS test;
	
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("未找到用户存档文件", 1);
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	battle_draw();

	map[6][6].side = 1;
	map[6][6].kind = BUILDER;
	map[6][5].side = 2;
	map[6][5].kind = INFANTRY;
	initdraw(map);


	while(1)
	{
		Newxy();
		

		nxt_btn_fun(65370, 65340);

		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			msgflag = 1;
			opos = D2O(ptmp);
			if (flag == 3)
			{
				clccell = 0;
				disp_geo_info(map[opos.y][opos.x]);
				disp_arm_info(map[opos.y][opos.x]); //清空其中的静态结构体变量
				show_msg("血量", "等级");
				base_func(map,10);
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
/**********************************************************
Function：		Battle_init
Description：	战斗初始化函数，读取存档
Input:			fp用户存档文件指针，其他你一看就懂
Author：		刘云笛
**********************************************************/
void Battle_init(FILE* fp, Battleinfo *info, MAP map)
{
	int i, j;
	
	fseek(fp, 7, SEEK_CUR);//跳过日期
	fread(&(info->round), 2, 1, fp);
	fread(&(info->b_source), 2, 1, fp);
	fread(&(info->r_source), 2, 1, fp);
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (feof(fp) && i*j != 144)
			{
				show_error("地图文件有误！", 1);
			}
			fread(map[i] + j, 2, 1, fp);
		}
	}//读取地图信息
}
/**********************************************************
Function：		save_battle
Description：	保存存档
Input:			fp用户存档文件指针，需要指向正确存档，其他你一看就懂
Author：		刘云笛
**********************************************************/

void save_battle(FILE* fp, Battleinfo batinfo, MAP map)
{
	unsigned t[3];
	time_t rawtime;
	struct tm* info;
	int i, j;

	fseek(fp, 1, SEEK_CUR);//跳过模式号
	//当前时间输入
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//年
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//月日
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//时分
	fwrite(t, 2, 3, fp);
	//回合信息保存
	fwrite(&(batinfo.round), 2, 1, fp);
	fwrite(&(batinfo.b_source), 2, 1, fp);
	fwrite(&(batinfo.r_source), 2, 1, fp);
	//储存地图信息
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fwrite(map[i] + j, 2, 1, fp);
		}
	}
}


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
		show_error("读取兵种信息失败", 0);
		fclose(fp);
		return;
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
	lastcell1 = cell;
	return;
}

/********显示当前鼠标位置兵种信息*********/
Arminfo disp_arm_info(CELL cell)
{
	Arminfo info;
	char buffer[20] = "\0";
	static CELL lastcell2;

	if (lastcell2.kind == cell.kind && lastcell2.health == cell.health)
		return;

	info = search_info(cell.kind);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	switch (cell.kind)
	{
	case BUILDER:
		Outtextxx(20, 120, 110, "兵种  工兵", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(20, 140, 75, "生命值", 16, 0);
		Outtext(90, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(20, 160, 75, "攻击力", 16, 0);
		Outtext(90, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(20, 180, 75, "行动力", 16, 0);
		Outtext(90, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(20, 200, 75, "射程", 16, 0);
		Outtext(90, 200, buffer, 16, 16, 0);
		break;

	case INFANTRY:
		Outtextxx(20, 120, 110, "兵种  步兵", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(20, 140, 75, "生命值", 16, 0);
		Outtext(90, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(20, 160, 75, "攻击力", 16, 0);
		Outtext(90, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(20, 180, 75, "行动力", 16, 0);
		Outtext(90, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(20, 200, 75, "射程", 16, 0);
		Outtext(90, 200, buffer, 16, 16, 0);
		break;
	default:
		break;
	}
	lastcell2 = cell;
	return info;
}

void base_func(MAP map, int source)
{
	int clcflag = 0;
	Arminfo arminfo;
	POS pos, center = center_xy(3, 9);
	pos.x = 745;
	pos.y = 705;
	icon(pos, map[9][1].side, BUILDER);
	pos.x = 800;
	icon(pos, map[9][1].side, INFANTRY);
	while (1)
	{
		Newxy();
		if (mouse_press(740-18, 705-18, 740+18, 705+23) == MOUSE_IN_L)
		{
			arminfo = search_info(BUILDER);
			if (clcflag == 1)
			{
				clcflag = 0;
				if (source < arminfo.cost)
				{
					show_msg("资源不足无法建造", "");
					delay(1000);
					return;
				}
				else if (map[8][1].kind != 0)
				{
					show_msg("出兵点被占领", "请消灭敌军或先移动我方单位");
					delay(1000);
					return;
				}
				else 
				{
					map[8][1].kind = BUILDER;
					map[8][1].health = arminfo.health;
					icon(center, map[9][1].side, BUILDER);
					show_msg("建造成功！", "");
					delay(1000);
					return;
				}
			}
			else
			{
				clcflag = 1;
				show_msg("工兵，造价：2", "再次点选确定建造");
				delay(50);
			}
		}
	}
}