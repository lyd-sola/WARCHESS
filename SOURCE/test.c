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
			return EXIT;
		}
		//�����Ǵ�ҳ����ĺ���
		
	}
	
}

void test_draw()
{
	short s[101*101];
	
	//��ҳ��
	Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	//Putbmp64k(0, 0, "BMP//map.bmp");

	//Button(780, 150, 1024, 180, 60361, 65535);
	//Outtext(1024 - 4 * 55, 150 - 16, "����ǰ��", 32, 55, 0);
	Button(150, "����ǰ��", 60361, 65535);

	//Lightbar(0, 0, 512, 768, 1.1);
	//Lightbar(0, 0, 512, 768, 1.0/1.05);
	//�ǵû����ϽǵĲ��	
}