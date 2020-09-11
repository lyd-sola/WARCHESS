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
		if(mouse_press(1000, 0, 1024, 20) == 1)
		{
			return EXIT;
		}
		//以下是此页面核心函数
		
	}
	
}

void test_draw()
{
	short s[101*101];
	
	Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	//画页面
	Putbmp64k(0, 0, "BMP//tst1.bmp");
	GetBackground(200,200,300,300,s);
	delay(1000);
	
	Bar64k(200,200,400,400,0);
	delay(1000);
	PutBackground(200,200,300,300,s);
	
	//记得画右上角的叉叉
	
}