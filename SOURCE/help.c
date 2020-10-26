/****************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: main.c
author: 刘云笛、陈旭桐
version: 2.0
Description: 教程函数，实际上为一段动画
****************************************************/
#include"common.h"

void help_cartoon()
{
	MAP map;
	int step = 1;
	DBL_POS pos;
	battle_draw();
	move_button(OK_co);
	attack_button("攻击", OK_co);
	stay_button("驻扎", OK_co);
	del_button(OK_co);
	while (1)
	{
		switch (step)
		{
		case 0:
			return;
		case 1:
			step = step1(map);
			break;
		case 2:
			step = step2(map);
			exit(0);
			break;
		/*case 3:
			step = step3();
			break;*/
		}
	}
}

int step1(MAP map)
{
	int i, j;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			map[j][i].kind = 0;
		}
	}
	if (helpwanttosay("继续", "退出", "嗨，新兵", "欢迎进入战棋系统教程", 1) == 0)
		return 0;
	if (helpwanttosay("继续", "退出", "本教程将会演示基本操作", "你可以叫我海尔普", 1) == 0)
		return 0;
	if (helpwanttosay("继续", "退出", "首先我们进入基本信息介绍", "", 1) == 0)
		return 0;
	helpwanttosay("别点", "别点", "（正在进入基本信息介绍）", "我将为你展示一段动画", 0);
	delay(3000);
	Map_partial(262, 218, 262 + 500, 219 + 230);
	return 2;	
}

int step2(MAP map)
{
	CELL cell;
	cell.kind = INFANTRY;
	cell.health = 2;
	helpwanttosay("别点", "别点", "看箭头", "这是信息显示区", 0);
	arrow(200, 100, "信息显示区：", "这里会显示被选中的兵", "种或地形信息", 0);
	delay(3000);
	disp_arm_info(cell);
	helpwanttosay("别点", "别点", "就像这样", "显示一些信息", 0);
	delay(3000);

	cell.kind = 0;
	disp_arm_info(cell);
	Map_partial(200, 100-50, 200+310, 100+50);
	helpwanttosay("别点", "别点", "接下来是行动区", "你要通过这里进行指挥", 0);
	arrow(150, 530, "行动区：", "选中兵种之后再次点击", "进行操作，右键取消", 0);
	delay(5000);

	move_button(CANT_co);
	attack_button("攻击", CANT_co);
	stay_button("驻扎", CANT_co);
	del_button(CANT_co);
	helpwanttosay("别点", "别点", "太多了懒得说", "你自己看吧", 0);
	delay(3000);
	Map_partial(262, 218, 262 + 500, 219 + 230);

	attack_button("攻击", OK_co);
	arrow(150, 530, "攻击：根据你所选兵种", "的攻击力扣除敌人血", "量，注意范围限制", 0);
	delay(3000);
	attack_button("攻击", CANT_co);

	move_button(OK_co);
	arrow(150, 530, "移动：兵种的移动力代", "表了你能最远抵达的格", "子数", 0);
	delay(3000);
	arrow(150, 530, "需要注意的是，有些地", "形消耗移动力为2甚至", "完全不能通过", 0);
	delay(3000);
	move_button(CANT_co);

	stay_button("驻扎", OK_co);
	arrow(150, 530, "驻扎：驻扎可以增加一", "点你的攻击力，同时每", "回合可以回复一点血", 0);
	delay(3000);
	stay_button("驻扎", CANT_co);

	del_button(OK_co);
	arrow(150, 530, "删除：删除将直接撤退", "你的军队", "", 0);
	delay(3000);
	del_button(CANT_co);

	helpwanttosay("别点", "别点", "忘了说，每回合", "每个单位只能操作一次", 0);
	delay(3000);
	return 3;
}

void arrow(int x, int y, char* s1, char* s2, char *s3, int mode)
{
	Clrmous();
	if (x < 512)
	{
		Filltriangle(x, y, x+25, y+25, x+25, y, 34429);
		Filltriangle(x, y, x+25, y-25, x+25, y, 34429);
		Bar64k(x+25, y+10, x+100, y-10, 34429);
		Bar64k(x+100, y-50, x+310, y+50, 34429);
		Outtext(x+110, y-40, s1, 16, 20, 0);
		Outtext(x+110, y-8, s2, 16, 20, 0);
		Outtext(x+110, y+24, s3, 16, 20, 0);
	}
	else
	{
		Filltriangle(x-25, y, x-25, y+25, x, y, 34429);
		Filltriangle(x-25, y, x-25, y-25, x, y, 34429);
		Bar64k(x-25, y+10, x-100, y-10, 34429);
		Bar64k(x-100, y-50, x-310, y+50, 34429);
		Outtext(x-300, y-40, s1, 16, 20, 0);
		Outtext(x-300, y-8, s1, 16, 20, 0);
		Outtext(x-300, y+24, s2, 16, 20, 0);
	}
	if (mode)
	{
		while (1)
		{
			Newxy();
			if (press == 1)
			{
				return;
			}//点击返回
		}
	}
	return;
}

short helpwanttosay(char* btn1, char* btn2, char* s1, char* s2, int mode)
{
	Clrmous();
	Bar64k_radial(262, 218, 262 + 500, 219 + 230, 34429, 0);
	rect_button(318, 384, 112 + 318, 45 + 384, btn1, 65535);
	rect_button(581, 384, 112 + 581, 45 + 384, btn2, 65535);
	Outtext(304, 252, s1, 32, 35, 0);
	Outtext(304, 314, s2, 32, 35, 0);
	if (mode)
	{
		while (1)
		{
			Newxy();
			if (rec_btn_fun(318, 384, 112 + 318, 45 + 384, 65535))
			{
				return 1;
			}//点击确定返回1
			if (rec_btn_fun(581, 384, 112 + 581, 45 + 384, 65535))
			{
				return 0;
			}//点击取消返回0
		}
	}
}