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

int test(void)
{
	
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