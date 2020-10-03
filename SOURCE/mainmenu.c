/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS
file_name: mainmenu.c
author: 陈旭桐
version: 1.0
Description: 主菜单
date:2020/9/9

更新日志

函数目录
1.mainmenu:		主菜单函数
2.mmenu_draw:	绘制主菜单函数
******************************************************************/
#include "common.h"

int mainmenu(char *user)
{
	mmenu_draw(user); //绘制主菜单函数
	Clrmous();//更新鼠标状态，防止留痕
	
	while(1)
	{
		Newxy();
		Sharp_button(225, "红蓝对决", "双人对战", 60361, 65535);
		if (Sharp_button(225 + 110, "决战智械", "单人模式", 60361, 65535))
		{
			//if (savefile_creat(user) == 1)
			//{
			//	return MAINMENU;
			//}
			return BATTLE;
		}
		Sharp_button(225 + 220, "重回往昔", "读取存档", 60361, 65535);
		Sharp_button(225 + 330, "作战指导", "操作说明", 60361, 65535);
		if (Sharp_button(225 + 440, "鸣金收兵", "注销账号", 60361, 65535))
		{
			return HOMEPAGE;
		}
	}
}

void mmenu_draw(char *user)//菜单：红蓝对决（双人对战），对决智械（单人模式），重回往昔（读取存档），作战指导（操作说明），鸣金收兵（注销账号）
{
	Clrmous();
	Bar64k_radial(0, 0, 1024, 768, 65370, 0);
	banner(512 - 280, 20, 560);
	Outtextxx(512 - 280 + 10, 40, 512 - 280 + 560, "欢迎回来，指挥官！", 48, 65184);

	file_draw(100, 200, 500, 700);
	photo(120, 220, 220, 340);

	Outtext(230, 235, "指挥官档案", 32, 40, 0);
	Outtextxx(120, 360, 260, "通行证: ", 32, 0);
	Outtext(260, 360, user, 32, 40, 0);
	Outtextxx(120, 405, 260, "对局数: ", 32, 0);

	Button(225, "红蓝对决",60361, 65535);
	Button(225+110, "决战智械", 60361, 65535);
	Button(225+220, "重回往昔", 60361, 65535);
	Button(225+330, "作战指导", 60361, 65535);
	Button(225+440, "鸣金收兵", 60361, 65535);
}