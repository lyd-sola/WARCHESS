/****************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: common.h
author: 刘云笛、陈旭桐
version: 1
Description: 头文件及定义结构、枚举
****************************************************/ 
#ifndef	_COMMON_H_
#define	_COMMON_H_
#define INF_SOURCE

#define SCR_WIDTH 1024
#define SCR_HEIGHT 768

#include <stdio.h>     /**文件操作函数头文件**/
#include <conio.h>     /**getch()函数头文件**/
#include <stdlib.h>	   /**rand()、exit()等函数头文件**/
#include <malloc.h>    /**动态分配内存头文件**/
//#include <graphics.h>  /**自带图像处理头文件**/
#include <string.h>    /**字符串处理函数头文件**/
#include <bios.h> 	   /**bioskey()函数头文件**/
#include <dos.h>       /**int86()等关于中断的头文件**/
#include <time.h>	   /**time()函数的头文件**/
#include <math.h>      /**数学函数的头文件**/
#include <ctype.h>     /**字符函数的头文件**/
#include <process.h>

#include "outtext.h"	//汉字库
#include "SVGAmode.h"	//SVGA
#include "mouse.h"		//鼠标

#include "draw.h"		//自定义画图函数
#include "struct.h"		//各种结构体定义
#include "kbinput.h"	//键盘输入显示
#include "homepage.h"	//主页
#include "login.h"		//登录界面
#include "register.h"	//注册界面
#include "mainmenu.h"	//主菜单界面
#include "save.h"		//对战信息存档存取
#include "func.h"		//各种函数
#include "map.h"		//地图相关函数
#include "battle.h"		//对战主函数
#include "act.h"		//对战行为函数
#include "savpage.h"	//存档界面
#include "buttons.h"	//按钮函数
#include "judge.h"		//移动判断函数
#include "help.h"		//教程函数
#include "aut.h"		//自动对战函数
enum MENU
{
	EXIT, HOMEPAGE, LOGIN, REGIS, MAINMENU, ABOUT, BATTLE, GUEST
};//主界面功能选项
/********************测试页面函数********************/
int test(void);
void test_draw(void);
void tank_draw(int x, int y);
#endif