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
	///*******/
	//POS pos;
	int q = 0, flag = 0;
	char answer[20] = "";
	Clrmous();
	test_draw();

	////banner(200, 200, 200);
	//pos.x = 7;
	//pos.y = 7;
	////Icon_tank(pos, 1);
	////Icon_inf(pos, 1);
	////Icon_super(pos, 1);
	//Icon_arti(pos, 1);
	//battle_exit(800, 100);
	//rect_button(600, 600, 750, 650, "我是你爹", 65340);
	//rect_button(600, 200, 800, 350, "你爹", 65340);
	while(1)
	{
		Newxy();
		if ((flag = list_func(610, 280, 610 + 370, 280 + 50, 5, &q)) == 0)
		{
			Outtext(610+5, 380+5, answer, 32, 40, 44373);
		}
		else if(flag == 1)
		{
			answer[0] = 0;
		}
		if (mouse_press(610, 280 + 100, 610 + 370, 280 + 50 + 100) == MOUSE_IN_L)
		{
			kbinput(610, 280 + 100, 610 + 370, 280 + 50 + 100, answer, 2);
		}
		if(mouse_press(0, 0, 50, 50) == MOUSE_IN_L)
		{
			return EXIT;
		}
	}
}

void test_draw()
{
	//short s[101*101];
	//
	////画页面
	////Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	//Putbmp64k(0, 0, "BMP//map.bmp");
	//attack_button("攻击", 65535);
	//stay_button("驻扎", 65535);
	//move_button(65535);
	//del_button(65535);
	//show_msg("欢迎使用战棋系统", "");
	////Bar64k(400, 300, 500, 400, 65535);
	////delay(1000);
	////Map_partial(400, 300, 500, 400);
	////delay(1000);
	////Bar64k(450, 350, 500, 400, 65535);
	////delay(1000);
	////Map_partial(450, 350, 500, 400);


	////Lightbar(0, 0, 512, 768, 1.1);
	////Lightbar(0, 0, 512, 768, 1.0/1.05);
	//save_btn(65370);
	//exit_btn(65370);
	//option_btn(65370);
	drawregi();
	regi_sq_draw();
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