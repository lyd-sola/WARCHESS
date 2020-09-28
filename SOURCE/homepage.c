/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS
file_name: homepage.c
author: 陈旭桐
version: 1.2
Description: 主页界面
date:2020/9/8

更新日志
9.9		增加了主页界面的按键,优化了界面效果
		增加了调试入口


函数目录
1.homepage：	主页函数
2.draw_h_page:	主页界面
******************************************************************/
#include "common.h"

int homepage()
{
	int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;	/***********防止重复标亮, 此处需要优化成一个flag****************/
	Clrmous();//更新鼠标状态，防止留痕
	draw_h_page(); //绘制主页函数
	while(1)
	{
		Newxy();
		if(bioskey(1))
		{
			getch();
		}//防止缓冲区中有内容影响输入
	
		if(mouse_press(974, 0, 1024, 50) == MOUSE_IN_L) //退出
		{
			return EXIT;
		}
		
		if(flag1 == 0 && mouse_press(700, 230, 950, 300) == MOUSE_IN)	//标亮登录键
		{
			flag1 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k_radial(700, 230, 950, 300, 57083, 0);
			Outtext(750 + 10, 240, "登录", 48, 70, 0);
			Mouse_savebk2();//更新鼠标状态，防止留痕
		}
		
		if(flag1 == 1 && mouse_press(700, 230, 950, 300) == MOUSE_OUT)	//取消标亮
		{
			flag1 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 230, 950, 300, 65336);
			Outtext(750 + 10, 240, "登录", 48, 70, 0);
			rectangle64k(699, 229, 951, 301, 35362);
			rectangle64k(698, 228, 952, 302, 35362);
		}
		
		if(flag2 == 0 && mouse_press(700, 350, 950, 420) == MOUSE_IN)	//标亮注册键
		{
			flag2 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(700, 350, 950, 420, 57083);
			Outtext(750 + 10, 360, "注册", 48, 70, 0);
			Mouse_savebk2();//更新鼠标状态，防止留痕
		}
		
		if(flag2 == 1 && mouse_press(700, 350, 950, 420) == MOUSE_OUT)	//取消标亮
		{
			flag2 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 350, 950, 420, 65336);
			Outtext(750 + 10, 360, "注册", 48, 70, 0);
			rectangle64k(699, 349, 951, 421, 35362);
			rectangle64k(698, 348, 952, 422, 35362);
		}
		
		if(flag3 == 0 && mouse_press(700, 470, 950, 540) == MOUSE_IN)	//标亮关于键
		{
			flag3 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(700, 470, 950, 540, 44373);
			Outtext(750 + 10, 480, "关于", 48, 70, 0);
			Mouse_savebk2();//更新鼠标状态，防止留痕
		}
		
		if(flag3 == 1 && mouse_press(700, 470, 950, 540) == MOUSE_OUT)	//取消标亮
		{
			flag3 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 470, 950, 540, 65336);
			Outtext(750 + 10, 480, "关于", 48, 70, 0);
			rectangle64k(699, 469, 951, 541, 35362);
			rectangle64k(698, 468, 952, 542, 35362);
		}
		
		if(flag4 == 0 && mouse_press(700, 590, 950, 660) == MOUSE_IN)	//标亮退出键
		{
			flag4 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(700, 590, 950, 660,44373);
			Outtext(750 + 10, 600, "退出", 48, 70, 0);
			Mouse_savebk2();//更新鼠标状态，防止留痕
		}
		
		if(flag4 == 1 && mouse_press(700, 590, 950, 660) == MOUSE_OUT)	//取消标亮
		{
			flag4 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 590, 950, 660, 65336);
			Outtext(750 + 10, 600, "退出", 48, 70, 0);
			rectangle64k(699, 589, 951, 661, 35362);
			rectangle64k(698, 588, 952, 662, 35362);
		}
		
		if(mouse_press(70, 70, 70+500, 70+90) == MOUSE_IN_R)				//为了方便调试,右键点击标题直接跳过登录界面进入主菜单
		{
			return MAINMENU;
		}
		
		if(mouse_press(700, 470, 950, 540) == MOUSE_IN_L)	//点击关于键
		{
			return ABOUT;
		}
		
		if(mouse_press(700, 230, 950, 300) == MOUSE_IN_L)	//点击登录键
		{
			return LOGIN;
		}
		
		if(mouse_press(700, 350, 950, 420) == MOUSE_IN_L)			//点击注册键
		{
			return REGIS;
		}
		if(mouse_press(700, 590, 950, 660) == MOUSE_IN_L)			//点击退出键
		{
			exit(0);
		}
		
		/*************************测试用，右键右下角进入test页面****************************/
		if(mouse_press(1024-100, 768-100, 1024, 768) == MOUSE_IN_R)
		{
			return 233;
		}
	}
}

void draw_h_page()
{
	//Bar64k(0, 0, 1024, 768, 29186);
	Putbmp64k(0, 0, "BMP//homepage.bmp");
	Bar64k(974, 0, 1024, 50,65535);
	

	Outtext(984, 9,"退", 32, 0, RED);
	Outtext(85+2,90+2,"红蓝军对抗演练", 48, 70, 27469);
	Outtext(85, 90, "红蓝军对抗演练", 48, 70, 0);


	shadow_l(700, 230, 950, 300, 65336);
	Outtext(750+10, 240,"登录", 48, 70, 0);
	rectangle64k(699, 229, 951, 301, 35362);
	rectangle64k(698, 228, 952, 302, 35362);

	shadow_l(700, 350, 950, 420, 65336);
	Outtext(750+10, 360,"注册", 48, 70, 0);
	rectangle64k(699, 349, 951, 421, 35362);
	rectangle64k(698, 348, 952, 422, 35362);
	
	shadow_l(700, 470, 950, 540, 65336);
	Outtext(750+10, 480,"关于", 48, 70,0);
	rectangle64k(699, 469, 951, 541, 35362);
	rectangle64k(698, 468, 952, 542, 35362);
	
	shadow_l(700, 590, 950, 660, 65336);
	Outtext(750+10, 600,"退出", 48, 70, 0);
	rectangle64k(699, 589, 951, 661, 35362);
	rectangle64k(698, 588, 952, 662, 35362);
}