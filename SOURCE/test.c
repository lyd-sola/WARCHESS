/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: 
author: 
version: 
Description: 
date:

������־

����Ŀ¼
******************************************************************/
//SVGA�ֱ���1024*768
//ʹ��ʱ��֤�������ÿһ��ע�ͣ������˼ӽ������ޣ�������*1��

#include "common.h"
/**************���Լǵ�ɾ������**********************/
#define X0 516		//ԭ��x����
#define Y0 328.5	//ԭ��y����
#define SIZE 70		//�������ҳ����Ǳ߳���������
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
		//�����Ǵ�ҳ����ĺ���
		
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
	
	//��ҳ��
	Putbmp64k(0, 0, "BMP//map.bmp");

	show_error("û���⣬�Ҿ�����", 0);
	delay(1000);
	show_error("û���⣬�һ�����", 1);

	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
	//�ǵû����ϽǵĲ��
	
}

/**********************��������ת�� �ǵ�ɾ��*********************************/


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
