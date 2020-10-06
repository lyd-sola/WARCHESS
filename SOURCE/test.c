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
	rect_button(600, 600, 750, 650, "我是你爹", 65340);
	rect_button(600, 200, 800, 350, "你爹", 65340);
	while(1)
	{
		Newxy();
		rec_btn_fun(600, 600, 750, 650, 65340);
		rec_btn_fun(600, 200, 800, 350, 65340);
		if(mouse_press(950, 0, 1024, 74) == MOUSE_IN_L)
		{
			return EXIT;
		}
		//以下是此页面核心函数
		if (atk_btn_fun("攻击", 65535, 65340))
		{
			show_msg("点到攻击按钮啦，我就吓唬你一下", "");
		}
		if (stay_btn_fun("驻扎", 65535, 65340))
		{
			show_msg("点到驻扎按钮啦，我就吓唬你一下", "");
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
	
	//画页面
	//Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	Putbmp64k(0, 0, "BMP//map.bmp");
	attack_button("攻击", 65535);
	stay_button("驻扎", 65535);
	move_button(65535);
	del_button(65535);
	show_msg("欢迎使用战棋系统", "");
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
	Bar64k(x - 100, y - 40, x + 100, y + 40, 65535); //一层车身
	Filltriangle(x-100,y-40, x+100, y-50, x+100, y-40, 65535); //一层车身倾斜效果
	Filltriangle(x - 110, y + 40, x - 100, y - 40, x - 100, y + 40, 65535);
	Filltriangle(x + 100, y + 40, x + 100, y - 50, x + 110, y + 40, 65535);
	Bar64k(x - 80, y + 40, x + 80, y + 80, 65535);

	Bar64k(x - 80, y - 100, x + 80, y -80, 65535); //观察室
	Filltriangle(x - 80, y - 100, x + 80, y - 110, x + 80, y - 100, 65535); //观察室倾斜效果
	Filltriangle(x - 110, y + 40, x - 100, y - 40, x - 100, y + 40, 65535);
	Filltriangle(x + 100, y + 40, x + 100, y - 50, x + 110, y + 40, 65535);
}