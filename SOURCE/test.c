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
		if(mouse_press(1000, 0, 1024, 20) == 1)
		{
			return EXIT;
		}
		//�����Ǵ�ҳ����ĺ���
		
	}
	
}

void test_draw()
{
	short s[101*101];
	
	Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	//��ҳ��
	Putbmp64k(0, 0, "BMP//tst1.bmp");
	GetBackground(200,200,300,300,s);
	delay(1000);
	
	Bar64k(200,200,400,400,0);
	delay(1000);
	PutBackground(200,200,300,300,s);
	
	//�ǵû����ϽǵĲ��
	
}