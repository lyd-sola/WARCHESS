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
	POS pos1;
	/*******/
	Clrmous();
	test_draw();
	//tank_draw(200, 200);
	
	//Filltriangle(100, 100, 200, 150, 200, 100, 35362);
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
	/*for (i = 0; i <= 25;i++)
	{
		for (j = 0; j <= 13; j++)
		{
			rectangle64k(X0, Y0, X0 + i * WIDTH, Y0 + j * LENGTH, 0);
		}
	}
	*/
	while(1)
	{
		Newxy();
		if(mouse_press(950, 0, 1024, 74) == MOUSE_IN_L)
		{
			return EXIT;
		}
		//�����Ǵ�ҳ����ĺ���
		
	}	
}

void test_draw()
{
	short s[101*101];
	POS p = { 584,418 };
	
	//��ҳ��
	//Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	Putbmp64k(0, 0, "BMP//map.bmp");
	
	//Bar64k(400, 300, 500, 400, 65535);
	//delay(1000);
	//Map_partial(400, 300, 500, 400);
	//delay(1000);
	//Bar64k(450, 350, 500, 400, 65535);
	//delay(1000);
	//Map_partial(450, 350, 500, 400);


	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
}

void tank_draw(int x, int y)
{
	Bar64k(x - 100, y - 40, x + 100, y + 40, 65535); //һ�㳵��
	Filltriangle(x-100,y-40, x+100, y-50, x+100, y-40, 65535); //һ�㳵����бЧ��
	Filltriangle(x - 110, y + 40, x - 100, y - 40, x - 100, y + 40, 65535);
	Filltriangle(x + 100, y + 40, x + 100, y - 50, x + 110, y + 40, 65535);
	Bar64k(x - 80, y + 40, x + 80, y + 80, 65535);

	Bar64k(x - 80, y - 100, x + 80, y -80, 65535); //�۲���
	Filltriangle(x - 80, y - 100, x + 80, y - 110, x + 80, y - 100, 65535); //�۲�����бЧ��
	Filltriangle(x - 110, y + 40, x - 100, y - 40, x - 100, y + 40, 65535);
	Filltriangle(x + 100, y + 40, x + 100, y - 50, x + 110, y + 40, 65535);
}