/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: 
author: 
version: 
Description: 
date:

更新日志

函数目录
******************************************************************/
//SVGA分辨率1024*768
//使用时保证清除以下每一个注释，别忘了加进工程噢（我忘了*1）

#include "common.h"
/**************测试记得删除！！**********************/
#define X0 516		//原点x坐标
#define Y0 328.5	//原点y坐标
#define SIZE 70		//六边形弦长，非边长！！！！
/****************88***********************************/
int test(void)
{
	/*******/
	int n1, n2;
	int i = 0;
	char str1[10];
	char str2[10];
	char str3[10];
	char str4[10];
	/*******/
	clrmous(MouseX, MouseY);
	test_draw();

	while(1)
	{
		Newxy();
		if(mouse_press(950, 0, 1024, 74) == MOUSE_IN_L)
		{
			return HOMEPAGE;
		}
		//以下是此页面核心函数
		
		if(mouse_press(0, 0, 1024, 768) == 1)
		{
			xy_tran((float)MouseX, (float)MouseY, &n1, &n2);
			itoa(n1, str1, 10);
			itoa(n2, str2, 10);
			itoa(MouseX, str3, 10);
			itoa(MouseY, str4, 10);
			Outtext(10,0 , str1, 16, 30, 0);
			Outtext(10,30, str2, 16, 30, 0);
			Outtext(10,60 , str3, 16, 30, 0);
			Outtext(10,90, str4, 16, 30, 0);
			i += 30;
		}
		
	}
	
}

void test_draw()
{
	short s[101*101];
	
	//画页面
	Putbmp64k(0, 0, "BMP//map.bmp");

	show_error("没问题，我就试试", 0);
	delay(1000);
	show_error("没问题，我还试试", 1);

	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
	//记得画右上角的叉叉
	
}

/**********************测试坐标转换 记得删除*********************************/


void xy_tran(int x, int y, int *n1, int *n2)
{
	float x2, y2;
	(float)x;
	(float)y;
	x2 = (x - X0) + (y - Y0) * (18/35);
	y2 = (y - Y0) * 39.357 / 35;
	*n1 = (x2 - (y - Y0) *(18/35)) / SIZE + 1;
	*n2 = (y2 ) / SIZE;
	//search(x2, y2, n1, n2);
}

void search(float x2, float y2, int *n1, int *n2)
{
	*n1 = (x2 ) / SIZE+1;
	*n2 = (y2 ) / SIZE;
}
