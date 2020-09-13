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
	/*******/
	clrmous(MouseX, MouseY);
	test_draw();
	for (i = 1; i <= 13;i++)
	{
		for (j = 1; j <= 13; j++)
		{
			xy(i, j, &x_tmp, &y_tmp);
			y_tmp -= ((j - 1) / 3);   //哈哈哈哈我真特酿是个天才， 老赌狗了
			x_tmp -= ((i - 1) / 3);
			rectangle64k(x_tmp - 10, y_tmp - 10, x_tmp + 10, y_tmp + 10, 0);
			/*itoa(x_tmp, str1, 10);
			itoa(y_tmp, str2, 10);
			strcat(str5, str1);
			strcat(str5, " , ");
			strcat(str5, str2);
			strcat(str5, ")");
			Outtextxx(x_tmp - 30, y_tmp, x_tmp + 30, str5, 16, 0);*/
		}
	}
	for (i = 0; i <= 25;i++)
	{
		for (j = 0; j <= 13; j++)
		{
			rectangle64k(X0, Y0, X0 + i * WIDTH, Y0 + j * LENGTH, 0);
		}
	}
	
	while(1)
	{
		Newxy();
		if(mouse_press(950, 0, 1024, 74) == MOUSE_IN_L)
		{
			return HOMEPAGE;
		}
		//以下是此页面核心函数
		
		if (mouse_press(0, 0, 20, 20) == 1)
		{
			for (i = 1; i <= 13;i++)
			{
				for (j = 1; j <= 13; j++)
				{
					xy(i, j, &x_tmp, &y_tmp);
					rectangle64k(x_tmp - 10, y_tmp - 10, x_tmp + 10, y_tmp + 10, 0);
					/*itoa(x_tmp, str1, 10);
					itoa(y_tmp, str2, 10);
					strcat(str5, str1);
					strcat(str5, " , ");
					strcat(str5, str2);
					strcat(str5, ")");
					Outtextxx(x_tmp - 30, y_tmp, x_tmp + 30, str5, 16, 0);*/
				}
			}
			delay(1000);
			test_draw();
		}
		
		if (mouse_press(0, 748, 20, 768) == 1)
		{
			for (i = 0; i <= 25;i++)
			{
				for (j = 0; j <= 13; j++)
				{
					rectangle64k(X0, Y0, X0 + i * WIDTH, Y0 + j * LENGTH, 0);
				}
			}
		}

		if(mouse_press(20, 20, 1024, 768) == 1)
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

	/*show_error("没问题，我就试试", 0);
	delay(1000);
	show_error("没问题，我还试试", 1);

	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
	//记得画右上角的叉叉*/
}

/**********************测试坐标转换 记得删除********************************


void xy_tran(float x, float y, int *n_1, int *n_2)
{
	float x2, y2, a, b, tmp;
	int n1, n2;
	x2 = x - X0; //换坐标系后的MouseX
	y2 = y - Y0; //换坐标系后的MouseY
	n1 = x2 / WIDTH + 1; //神秘方格横坐标，第几个
	n2 = y2 / LENGTH + 1; //神秘方格纵坐标，第几排
	a = n1 * WIDTH - WIDTH / 2; //神秘方格中点横坐标
	b = n2 * LENGTH - LENGTH / 2; //神秘方格中点纵坐标
	tmp = f(x2, a, b, n1, n2);
	if (y2 < tmp)
	{
		*n_2 = n2;
	}
	else
	{
		*n_2 = n2 + 1;
	}

	if (n1 % 2 == 1)
	{
		*n_1 = (n1 + 1) / 2;
	}
	else
	{
		if (n2 % 2 == 1)
		{
			if (y2 > tmp)
			{
				*n_1 = n1 / 2 + 1;
			}
			else
			{
				*n_1 = n1 / 2;
			}
		}

		else
		{
			if (y2 > tmp)
			{
				*n_1 = n1 / 2 ;
			}
			else
			{
				*n_1 = n1 / 2 + 1;
			}
		}
	}
	//search(x2, y2, n1, n2);
}

float f(float x, float a, float b, int n1, int n2)
{
	if (n1 % 2 == 1)
	{
		if (n2 % 2 == 1)
			return -K * (x - a) + b;
		else
			return K * (x - a) + b;
	}
	else
	{
		if (n2 % 2 == 1)
			return K * (x - a) + b;
		else
			return -K * (x - a) + b;
	}	
}*/