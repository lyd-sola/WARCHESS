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

int test(void)
{
	
	clrmous(MouseX, MouseY);
	test_draw();

	while(1)
	{
		Newxy();
		if(mouse_press(950, 0, 1024, 74) == MOUSE_IN_L)
		{
			return EXIT;
		}
		//以下是此页面核心函数
		
	}
	
}

void test_draw()
{
	short s[101*101];
	
	//画页面
	Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	//Putbmp64k(0, 0, "BMP//map.bmp");

	//Button(780, 150, 1024, 180, 60361, 65535);
	//Outtext(1024 - 4 * 55, 150 - 16, "再续前程", 32, 55, 0);
	Button(150, "再续前程", 60361, 65535);

	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
	//记得画右上角的叉叉	
}