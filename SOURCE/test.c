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
			y_tmp -= ((j - 1) / 3);   //�����������������Ǹ���ţ� �϶Ĺ���
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
		//�����Ǵ�ҳ����ĺ���
		
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
	
	//��ҳ��
	Putbmp64k(0, 0, "BMP//map.bmp");

	/*show_error("û���⣬�Ҿ�����", 0);
	delay(1000);
	show_error("û���⣬�һ�����", 1);

	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
	//�ǵû����ϽǵĲ��*/
}

/**********************��������ת�� �ǵ�ɾ��********************************


void xy_tran(float x, float y, int *n_1, int *n_2)
{
	float x2, y2, a, b, tmp;
	int n1, n2;
	x2 = x - X0; //������ϵ���MouseX
	y2 = y - Y0; //������ϵ���MouseY
	n1 = x2 / WIDTH + 1; //���ط�������꣬�ڼ���
	n2 = y2 / LENGTH + 1; //���ط��������꣬�ڼ���
	a = n1 * WIDTH - WIDTH / 2; //���ط����е������
	b = n2 * LENGTH - LENGTH / 2; //���ط����е�������
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