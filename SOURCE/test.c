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
		if(mouse_press(1000, 0, 1024, 20) == MOUSE_IN_L)
		{
			return EXIT;
		}
		//�����Ǵ�ҳ����ĺ���
		
	}
	
}

void test_draw()
{
	short s[101*101];
	
	//��ҳ��
	Putbmp64k(0, 0, "BMP//map.bmp");

	//�ǵû����ϽǵĲ��
	
}