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
	savefile_creat(user);
	
	while(1)
	{
		Newxy();
		
		if(mouse_press(0, 0, 50, 50) == MOUSE_IN_L)
		{
			return HOMEPAGE;
		}
	}
}

void mmenu_draw(char *user)//菜单：红蓝对决（双人对战），对决智械（单人模式），重回往昔（读取存档），作战指导（操作说明），鸣金收兵（注销账号）
{
	Clrmous();
	Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	Button(225, "红蓝对决",60361, 65535);
	Button(225+110, "决战智械", 60361, 65535);
	Button(225+220, "重回往昔", 60361, 65535);
	Button(225+330, "作战指导", 60361, 65535);
	Button(225+440, "鸣金收兵", 60361, 65535);

}