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


/****************88***********************************/
int test(void)
{
	/*******/
	int n1, n2, x_tmp, y_tmp;
	int i = 0, j = 0;
	char str1[10];
	char str2[10];
	char str3[10];
	char str4[10];
	char str5[10] = "(";
	POS pos1;
	/*******/
	Clrmous();
	test_draw();
	//for (i = 1; i <= 13;i++)
	//{
	//	for (j = 1; j <= 13; j++)
	//	{
	//		xy(i, j, &x_tmp, &y_tmp);
	//		rectangle64k(x_tmp - 10, y_tmp - 10, x_tmp + 10, y_tmp + 10, 0);
	//		/*itoa(x_tmp, str1, 10);
	//		itoa(y_tmp, str2, 10);
	//		strcat(str5, str1);
	//		strcat(str5, " , ");
	//		strcat(str5, str2);
	//		strcat(str5, ")");
	//		Outtextxx(x_tmp - 30, y_tmp, x_tmp + 30, str5, 16, 0);*/
	//	}
	//}
	//for (i = 0; i <= 25;i++)
	//{
	//	for (j = 0; j <= 13; j++)
	//	{
	//		rectangle64k(X0, Y0, X0 + i * WIDTH, Y0 + j * LENGTH, 0);
	//	}
	//}
	
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
	POS p = { 584,418 };
	
	//画页面
	//Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	Putbmp64k(0, 0, "BMP//map.bmp");
	
	Bar64k(400, 300, 500, 400, 65535);
	delay(1000);
	Putbmp64k_partial(400, 300, 500, 400, "BMP//map.bmp");
	delay(1000);
	Bar64k(450, 350, 500, 400, 65535);
	delay(1000);
	Putbmp64k_partial(450, 350, 500, 400, "BMP//map.bmp");


	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
}