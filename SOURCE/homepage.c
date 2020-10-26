/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS
file_name: homepage.c
author: 陈旭桐
version: 2.0
Description: 主页界面
date:2020/9/8

更新日志
9.9		增加了主页界面的按键,优化了界面效果
		增加了调试入口
10.25	优化了homepage()，增加游客登录
10.26	增加关于界面
******************************************************************/
#include "common.h"

int homepage()
{
	Clrmous();//更新鼠标状态，防止留痕
	draw_h_page(); //绘制主页函数

	delay(1000);
	while(1)
	{
		Newxy();
	
		if(mouse_press(974, 0, 1024, 50) == MOUSE_IN_L) //退出
		{
			return EXIT;
		}
		
		if (homepg_btn_fun(700, 230, 950, 300, "登录"))
		{
			return LOGIN;
		}
		if (homepg_btn_fun(700, 350, 950, 420, "注册"))
		{
			return REGIS;
		}
		if (homepg_btn_fun(700, 470, 950, 540, "关于"))
		{
			return ABOUT;
		}
		if (homepg_btn_fun(700, 590, 950, 660, "退出"))
		{
			exit(0);
		}
		if (guest_btn_fun())
		{
			return GUEST;
		}
		/*************************测试用，右键右下角进入test页面****************************/
		if(mouse_press(1024-100, 768-100, 1024, 768) == MOUSE_IN_R)
		{
			return 233;
		}

		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//为方便调试,主菜单左上角右键直接快速登录
		{
			return MAINMENU;
		}
	}
}

void draw_h_page()
{
	//Bar64k(0, 0, 1024, 768, 29186);
	Putbmp64k(0, 0, "BMP//homepage.bmp");
	Bar64k(974, 0, 1024, 50,65535);
	Outtext(984, 9, "退", 32, 0, 0);
	Outtext(85+2,90+2,"红蓝军对抗演练", 48, 70, 27469);
	Outtext(85, 90, "红蓝军对抗演练", 48, 70, 0);

	homepg_button(700, 230, 950, 300, "登录", 65336);
	homepg_button(700, 350, 950, 420, "注册", 65336);
	homepg_button(700, 470, 950, 540, "关于", 65336);
	homepg_button(700, 590, 950, 660, "退出", 65336);

	Outtextxx(846, 313, 978, "游客登录", 24, 0);
}

void homepg_button(int x1, int y1, int x2, int y2, char *s, int color)
{
	shadow_l(x1, y1, x2, y2, color);
	Outtext(x1+60, y1+10, s, 48, 70, 0);
	rectangle64k(x1-1, y1-1, x2+1, y2+1, 35362);
	rectangle64k(x1-2, y1-2, x2+2, y2+2, 35362);
}

int homepg_btn_fun(int x1, int y1, int x2, int y2, char *s)//按钮功能函数
{
	if (Mouse_above(x1 - 2, y1 - 2, x2 + 2, y2 + 2))
	{
		Clrmous();
		MouseS = 1;
		homepg_button(x1, y1, x2, y2, s, 44373);
		while (1)
		{
			Newxy();
			if (Mouse_above(x1-2, y1-2, x2+2, y2+2))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					return 1;
					//若点击返回1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				homepg_button(x1, y1, x2, y2, s, 65336);
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int guest_btn_fun()//游客登录按钮功能函数
{
	if (Mouse_above(846, 313, 978, 313 + 24))
	{
		Clrmous();
		MouseS = 1;
		Bar64k(846, 313 + 26, 978, 313 + 27, 0);
		while (1)
		{
			Newxy();
			if (Mouse_above(846, 313, 978, 313 + 24))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					return 1;
					//若点击返回1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				putbmp_partial(846, 313 + 26, 978, 313 + 27, "BMP//homepage.bmp");
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int about_page()
{
	Clrmous();
	Putbmp64k(0, 0, "BMP//about.bmp");
	rect_button(833, 700, 1000, 755, "返回主界面", 65370);
	while (1)
	{
		Newxy();
		if (rec_btn_fun(833, 700, 1000, 755, 65370))
		{
			return HOMEPAGE;
		}
	}
}