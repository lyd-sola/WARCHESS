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
	POS pos;
	/*******/
	Clrmous();
	test_draw();
	//banner(200, 200, 200);
	pos.x = 7;
	pos.y = 7;
	//Icon_tank(pos, 1);
	//Icon_inf(pos, 1);
	//Icon_super(pos, 1);
	Icon_arti(pos, 1);
	battle_exit(800, 100);
	rect_button(600, 600, 750, 650, "�������", 65340);
	rect_button(600, 200, 800, 350, "���", 65340);
	while(1)
	{
		Newxy();
		rec_btn_fun(600, 600, 750, 650, 65340);
		rec_btn_fun(600, 200, 800, 350, 65340);
		if(mouse_press(950, 0, 1024, 74) == MOUSE_IN_L)
		{
			return EXIT;
		}
		//�����Ǵ�ҳ����ĺ���
		if (atk_btn_fun("����", 65535, 65340))
		{
			show_msg("�㵽������ť�����Ҿ��Ż���һ��", "");
		}
		if (stay_btn_fun("פ��", 65535, 65340))
		{
			show_msg("�㵽פ����ť�����Ҿ��Ż���һ��", "");
		}
		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_L)
		{
			pos = xy2cell(MouseX, MouseY);
			pos = center_xy(pos.x, pos.y);
			Clrmous();
			Icon_builder(pos, 0);
		}
	}
}

void test_draw()
{
	short s[101*101];
	
	//��ҳ��
	//Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	Putbmp64k(0, 0, "BMP//map.bmp");
	attack_button("����", 65535);
	stay_button("פ��", 65535);
	move_button(65535);
	del_button(65535);
	show_msg("��ӭʹ��ս��ϵͳ", "");
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