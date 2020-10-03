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
	char s[20] = "SAVES//";
	FILE* fp;//指向用户文件的指针
	int clccell = 0;//点击过地图上一个格子
	int flag, msgflag = 0;
	strcat(s, user);

	savefile_creat(user, mode);

	if ((fp = fopen(s, "rb+")) == NULL)
	{
		show_error("未找到用户存档文件", 1);
	}
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	Clrmous();
	battle_draw();



	map[6][6].kind = BUILDER;
	pos.x = 13; pos.y = 7;
	Icon_builder(pos, 1);
	draw_saves(0, 0, 10000, fp, save_num);


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

	fseek(fp, 1, SEEK_CUR);//跳过存档号
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