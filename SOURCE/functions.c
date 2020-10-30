/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: functions.c
author: 刘云笛
version: 1.0
Description: 有用的函数
date:2020/9/13

更新日志
9.13	报错函数show_error
9.14	按钮相关功能函数Light_button，已移至draw.c
******************************************************************/
#include "common.h"
/**********************************************************
Function：		show_error
Description：	错误信息显示函数
Input:			msg为报错信息，mode为1 exit，为0 仅返回
Author：		刘云笛
**********************************************************/
void draw_show_error()
{
	rectangle64k(240, 225, 785, 567, 0);
	Bar64k_radial(241, 226, 784, 503, 63422, 0);
	Bar64k(241, 504, 784, 566, 57083);
	Outtext(240 + 20, 225 + 20, "WARCHESS战棋——by 1904 刘云笛、陈旭桐", 16, 14, 27469);//框架绘制
	Circle64k(286, 311, 18, 45476);
	Circlefill64k(286, 311, 17, 61890);
	Line64k(286 - 8, 303, 286 + 8, 311 + 8, 65535);
	Line64k(286 - 8, 304, 286 + 8, 311 + 8 + 1, 65535);
	Line64k(286 - 8 + 1, 303, 286 + 8 + 1, 311 + 8, 65535);
	Line64k(286 + 8, 311 - 8, 286 - 8, 311 + 8, 65535);
	Line64k(286 + 8 - 1, 311 - 8, 286 - 8 - 1, 311 + 8, 65535);
	Line64k(286 + 8, 311 - 8 + 1, 286 - 8, 311 + 8 + 1, 65535);//画叉叉
	Outtext(314, 311 - 16, "Error", 32, 25, 0);
	
	rectangle64k(677, 519, 774, 550, 0);
	Bar64k_radial(678, 520, 773, 549, 59164, 0);
	Outtext(701, 524, "确定", 24, 26, 0);//确定键
}
void show_error(char* msg, int mode)//提示框240,225  785,567
{
	unsigned int i = 0;//防止有人懒得点确认
	int  flag = 0;
	Clrmous();
	draw_show_error();
	Outtext(314, 360, msg, 24, 27, 0);
	if (mode)
	{
		Outtext(314, 433, "应用由于错误，异常停止", 24, 25, 0);
		Outtext(314, 435 + 16*2, "This application terminated with an error. ", 16, 10, 0);
	}
	else
	{
		Outtext(314, 433, "应用出现错误，即将返回主界面", 24, 25, 0);
		Outtext(314, 435 + 16*2, "An error occurred, returning to homepage. ", 16, 10, 0);
	}
	while (1)
	{
		Newxy();
		if (flag == 0 && Mouse_above(678, 520, 773, 549))
		{
			Clrmous();
			MouseS = 1;
			Bar64k_radial(678, 520, 773, 549, 65535, 0);
			Outtext(701, 524, "确定", 24, 26, 0);//标亮确认键
			flag = 1;
		}
		if (flag == 1 && Mouse_aboveother(678, 520, 773, 549))
		{
			Clrmous();
			MouseS = 0;
			Bar64k_radial(678, 520, 773, 549, 59164, 0);
			Outtext(701, 524, "确定", 24, 26, 0);//取消标亮确定键
			flag = 0;
		}
		if (mouse_press(678, 520, 773, 549) == MOUSE_IN_L || i >= 800)
		{
			if (mode)
			{
				Clrmous();
				Bar64k_radial_re(0, 0, 1024, 768, 65535, 1000);
				exit(1);
			}
			else
			{
				return;
			}
		}
		i ++;
	}
}
//在对战界面信息框显示信息
void show_msg(char* msg, char *msg2)
{
	static char* lastmsg;
	if (strcmp(msg, lastmsg) == 0)	//保证了不会连续输出同样的文字导致闪烁
		return;
	Map_partial(340, 666, 720, 666+25);
	Outtext(340, 666, msg, 24, 26, 0);
	Map_partial(340, 705, 720, 705 + 25);
	Outtext(340, 705, msg2, 24, 26, 0);
	lastmsg = msg;
}

/*屏幕上显示信息框，点击btn1返回1，btn2返回0*/
int msgbar(char *btn1, char *btn2, char *s1, char *s2)
{
	Clrmous();
	rect_circle(262, 218, 262 + 500, 219 + 230, 34429);
	rect_button(318, 384, 112+318, 45+384, btn1, 65535);
	rect_button(581, 384, 112+581, 45+384, btn2, 65535);
	Outtext(304, 252, s1, 32, 35, 0);
	Outtext(304, 314, s2, 32, 35, 0);
	while (1)
	{
		Newxy();
		if (rec_btn_fun(318, 384, 112 + 318, 45 + 384, 65535))
		{
			return 1;
		}//点击确定返回1
		if (rec_btn_fun(581, 384, 112 + 581, 45 + 384, 65535))
		{
			return 0;
		}//点击取消返回0
	}
}