/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS
file_name: mainmenu.c
author: 陈旭桐、刘云笛
version: 1.0
Description: 主菜单
date:2020/9/9

更新日志
******************************************************************/
#include "common.h"

int mainmenu(char *user, int *save_num, int *mode)
{
	char s[25] = "SAVES//";
	FILE* fp;
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("未找到用户存档文件", 1);

	mmenu_draw(user); //绘制主菜单函数	

	while(1)
	{
		Newxy();
		if (Sharp_button(225, "红蓝对决", "双人对战", 60361, 65535))
		{
			if (savefile_creat(fp, 0) == 1)
			{
				if (msgbar("确定", "取消", "存档已满，快速创建失败", "即将跳转到存档管理界面"))
				{
					if (!savpage(user, save_num, mode))
					{
						mmenu_draw(user);
						continue;
					}
				}
				else
				{
					mmenu_draw(user);
					continue;
				}
				fclose(fp);
				return BATTLE;
			}
			*save_num = get_savenum(fp);
			*mode = get_savmode(fp, *save_num);
			fclose(fp);
			return BATTLE;
		}
		if (Sharp_button(225 + 110, "决战智械", "单人模式", 60361, 65535))
		{
			if (savefile_creat(fp, 1) == 1)
			{
				if (msgbar("确定", "取消", "存档已满，快速创建失败", "即将跳转到存档管理界面"))
				{
					if (!savpage(user, save_num, mode))
					{
						mmenu_draw(user);
						continue;
					}
				}
				else
				{
					mmenu_draw(user);
					continue;
				}
				fclose(fp);
				return BATTLE;
			}
			*save_num = get_savenum(fp);
			*mode = get_savmode(fp, *save_num);
			fclose(fp);
			return BATTLE;
		}
		if (Sharp_button(225 + 220, "重回往昔", "读取存档", 60361, 65535))
		{
			if (!savpage(user, save_num, mode))
			{
				mmenu_draw(user);
				continue;
			}
			fclose(fp);
			return BATTLE;
		}
		if (Sharp_button(225 + 330, "作战指导", "操作说明", 60361, 65535))
		{
			help_cartoon();
		}
		if (Sharp_button(225 + 440, "鸣金收兵", "注销账号", 60361, 65535))
		{
			fclose(fp);
			return HOMEPAGE;
		}
	}
}

void mmenu_draw(char *user)//菜单：红蓝对决（双人对战），对决智械（单人模式），重回往昔（读取存档），作战指导（操作说明），鸣金收兵（注销账号）
{
	Clrmous();//更新鼠标状态，防止留痕
	Bar64k_radial(0, 0, 1024, 768, 65370, 0);
	banner(512 - 280, 20, 560);
	Outtextxx(512 - 280 + 10, 40, 512 - 280 + 560, "欢迎回来，指挥官！", 48, 65184);

	file_draw(100, 200, 500, 700);
	photo(120, 220, 220, 340);

	Outtext(230, 235, "指挥官档案", 32, 40, 0);
	Outtextxx(120, 360, 260, "通行证: ", 32, 0);
	Outtext(260, 360, user, 32, 32, 0);
	Outtextxx(120, 405, 260, "对局数: ", 32, 0);

	Button(225, "红蓝对决",60361, 65535);
	Button(225+110, "决战智械", 60361, 65535);
	Button(225+220, "重回往昔", 60361, 65535);
	Button(225+330, "作战指导", 60361, 65535);
	Button(225+440, "鸣金收兵", 60361, 65535);
}