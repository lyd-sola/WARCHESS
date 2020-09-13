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
	clrmous(MouseX, MouseY);//更新鼠标状态，防止留痕
	
	while(1)
	{
		Newxy();
		
		if(mouse_press(0, 0, 50, 50) == MOUSE_IN_L)
		{
			return 1;
		}
		
		if(mouse_press(330, 140+85, 330+250, 140+85+55) == MOUSE_IN_L)
		{
			/******************* 调试 记得删除********************/
			if(savefile_creat(user) == 0)
			{
				Outtext(0, 0, "存档文件损坏", 16, 20, 65535);
				delay(1000);
				exit(0);
			}
			
			Outtext(0, 0, "成功创建存档", 16, 20, 65535);
			delay(1000);
			return MAINMENU;
		}
		
		/*if(mouse_press(330, 140+85, 330+250, 140+85+55))
		{
			;
		}*/
	}
}

void mmenu_draw(char *user)//菜单：新的旅行，重回往昔，对战指导，鸣金收兵
{
	clrmous(MouseX, MouseY);
	Bar64k_radial(0, 0, 1024, 768, 57638, 1000);
	shadow(50, 32, 50+535, 32+90, 65535, 58816);
	Outtextxx(65, 52, 65+505, "欢迎回来指挥官", 48, 65499);
	shadow(330, 140, 330+250, 140+55, 65535, 58816);


	shadow(330, 140+85, 330+250, 140+85+55, 58816, 58816);


	shadow(330, 140+85+85, 330+250, 140+85+85+55, 58816, 58816);

	
	shadow(330, 140+85+85+85, 330+250, 140+85+85+85+55, 58816, 58816);


	file_draw(50, 140, 50+260, 140+85+85+85+55);


}