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
	CELL map[13][13];//地图
	DBL_POS pos, ptmp;
	Battleinfo batinfo;//对战信息
	int clccell = 0;//点击过地图上一个格子
	int flag, msgflag = 0;
	char s[25] = "SAVES//";
	FILE* fp;
	
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("未找到用户存档文件", 1);

	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	Clrmous();
	battle_draw();
	draw_saves(0, 0, 65535, fp, save_num);

	map[6][6].side = 1;
	map[6][6].kind = BUILDER;
	//pos.x = 13; pos.y = 7;
	//Icon_builder(pos, 1);
	initdraw(map);


	while(1)
	{
		Newxy();
		if (Sharp_button(16, "注销账号", "注销账号", 60361, 65535))
		{
			return MAINMENU;
		}

		if (atk_btn_fun("攻击", 65535, 65340))
		{
			show_error("点到攻击按钮啦，我就吓唬你一下", 0);
		}
		if (stay_btn_fun("驻扎", 65535, 65340))
		{
			show_error("点到驻扎按钮啦，我就吓唬你一下", 0);
		}
		nxt_btn_fun(65535, 65340);

		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			msgflag = 1;
			if (flag == 2)
			{
				pos = ptmp;
				clccell = 1;
				show_msg("已选择一个单位", "请选择行为");
			}
			else
			{
				clccell = 0;
				show_msg("该区域为空", "");
			}
			//show info
		}
		if (clccell && (mouse_press(20, 528, 141, 649) == MOUSE_IN_L))//移动
		{
			move(pos, map);
			clccell = 0;
			delay(50);//这个delay很重要，用于给用户时间抬起鼠标左键（move有动画后可以删除）
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
	}
}
//绘制战斗界面函数
void battle_draw()
{
	Putbmp64k(0, 0, "BMP//map.bmp");
	Button(16, "退出战斗", 60361, 65535);
	attack_button("攻击", 65535);
	stay_button("驻扎", 65535);
	move_button(65535);
	del_button(65535);
	nextr_button(65535);

	//选项菜单
	save_btn(29252);
	exit_btn(29252);
	option_btn(29252);
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
void save_battle(FILE* fp, Battleinfo* batinfo, MAP map)
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
	fwrite(&((*batinfo).round), 2, 1, fp);
	fwrite(&((*batinfo).b_source), 2, 1, fp);
	fwrite(&((*batinfo).r_source), 2, 1, fp);
	//储存地图信息
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fwrite(map[i] + j, 2, 1, fp);
		}
	}
}


//将来一并移入buttons.c
void save_btn(int color)
{
	rect_button(800, 10, 800+49, 10+34, "", color);
	Outtext(800 + 24 - 8, 10 + 17 - 8, "s", 16, 0, 0);
	Line64k(833, 23, 833, 34, 0);
	Line64k(834, 23, 834, 34, 0);
	Line45(834, 23, 832, 21, 0);
	Line45(833, 23, 831, 21, 0);
	Line64k(823, 21, 832, 21, 0);
	Line64k(823, 22, 832, 22, 0);
	Line45(823, 21, 821, 19, 0);
	Line45(823, 22, 821, 20, 0);
	Line64k(817, 19, 821, 19, 0);
	Line64k(817, 20, 821, 20, 0);
	Line45(817, 19, 815, 21, 0);
	Line45(815, 22, 817, 20, 0);
	Line64k(815, 22, 815, 34, 0);
	Line64k(816, 22, 816, 34, 0);
	Line45(815, 34, 817, 36, 0);
	Line45(816, 34, 817, 35, 0);
	Line64k(817, 35, 832, 35, 0);
	Line64k(817, 36, 832, 36, 0);
	Putpixel64k(833, 35, 0);
}

void option_btn(int color)
{
	rect_button(880, 10, 880+49, 44, "", color);
	Bar64k(880+14, 10+9, 880+49-14, 10+9+2, 0);
	Bar64k(880+14, 10+9+7, 880+49-14, 10+9+2+7, 0);
	Bar64k(880+14, 10+9+7*2, 880+49-14, 10+9+2+7*2, 0);
}

void exit_btn(int color)
{
	rect_button(960, 10, 960 + 49, 44, "", color);
	Line45(985 + 11, 27 + 11, 985 - 11, 27 - 11, 0);
	Line45(985 + 10, 27 + 11, 985 - 11, 27 - 10, 0);
	Line45(985 + 11, 27 + 10, 985 - 10, 27 - 11, 0);
	Line45(985 + 9, 27 + 11, 985 - 11, 27 - 9, 0);
	Line45(985 + 11, 27 + 9, 985 - 9, 27 - 11, 0);

	Line45(985 + 11, 27 - 11, 985 - 11, 27 + 11, 0);
	Line45(985 + 10, 27 - 11, 985 - 11, 27 + 10, 0);
	Line45(985 + 11, 27 - 10, 985 - 10, 27 + 11, 0);
	Line45(985 + 9, 27 - 11, 985 - 11, 27 + 9, 0);
	Line45(985 + 11, 27 - 9, 985 - 9, 27 + 11, 0);
}

void draw_cell(DBL_POS pos, MAP map)
{
	int flag, side;
	OFF_POS offpos;

	offpos = D2O(pos);
	flag = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;
	switch (flag)
	{
	case BUILDER:
		Icon_builder(pos, side);
	case INFANTRY:
		Icon_inf(pos, side);
	case ARTILLERY:
		Icon_arti(pos, side);
	case TANK:
		Icon_tank(pos, side);
	case SUPER:
		Icon_super(pos, side);
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
			if (map[j][i].kind)
			{
				opos.x = i;
				opos.y = j;
				dpos = O2D(opos);
				switch (map[j][i].kind)
				{
				case BUILDER:
					Icon_builder(dpos, map[j][i].side);
					break;
				case INFANTRY:
					Icon_inf(dpos, map[j][i].side);
					break;
				case ARTILLERY:
					Icon_arti(dpos, map[j][i].side);
					break;
				case TANK:
					Icon_tank(dpos, map[j][i].side);
					break;
				case SUPER:
					Icon_super(dpos, map[j][i].side);
					break;
				default:
					break;
				}
			}
		}
	}
}