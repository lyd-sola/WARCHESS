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
	int step = 5;
	DBL_POS pos;
	Battleinfo batinfo;
	FILE* fp;
	load_battle("HELP", 1, &batinfo, map, &fp);
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
			step = step1();
			break;
		case 2:
			step = step2();
			break;
		case 3:
			step = step3();
			break;
		case 4:
			step = step4(map);
			break;
		case 5:
			step = step5(map);exit(0);
		case 6:
			;//step = step6();
		}
	}
}

int step1()
{
	if (helpwanttosay("继续", "退出", "嗨，新兵", "欢迎进入战棋系统教程", 1) == 0)
		return 0;
	if (helpwanttosay("继续", "退出", "本教程将会演示基本操作", "你可以叫我海尔普", 1) == 0)
		return 0;
	if (helpwanttosay("继续", "退出", "首先我们进入基本信息介绍", "", 1) == 0)
		return 0;
	helpwanttosay("别点", "别点", "我将为你展示一段动画", "（正在进入基本信息介绍）", 0);
	Map_partial(262, 218, 262 + 500, 219 + 230);
	return 2;	
}

int step2()
{
	step2_1();
	step2_2();
	return 3;
}

void step2_1()
{
	CELL cell;
	cell.kind = INFANTRY;
	cell.health = 2;
	cell.geo = PLAIN;
	arrow(210, 100, "信息显示区：", "这里会显示被选中的兵", "种或地形信息", 0);
	helpwanttosay("别点", "别点", "看箭头", "这是信息显示区", 0);
	disp_arm_info(cell);
	disp_geo_info(cell);
	helpwanttosay("别点", "别点", "就像这样", "显示一些信息", 0);

	cell.kind = 0;
	cell.geo = 0;
	disp_arm_info(cell);
	disp_geo_info(cell);
	Map_partial(210, 100 - 50, 210 + 310, 100 + 50);
	arrow(800, 50, "三个按键：", "存档键、选项键、退出键", "", 0);
	helpwanttosay("别点", "别点", "这里是功能区", "你可以从这里离开", 0);

	save_btn(CANT_co);
	option_btn(CANT_co);
	exit_btn(CANT_co);

}
void step2_2()
{
	save_btn(OK_co); //以标亮开始
	helpwanttosay("别点", "别点", "存档键可以保存你的进度", "随时都可以复盘之前的战况", 0);
	save_btn(CANT_co);									//以还原结束

	option_btn(OK_co); //以标亮开始//以标亮开始
	draw_opts();
	helpwanttosay("别点", "别点", "选项键有三个按钮", "", 0);
	arrow(800, 50, "注销", "注销掉你的帐号", "", 0);
	helpwanttosay("别点", "别点", "注销意味着“你”离开这了", "", 0);
	arrow(800, 50, "保存并退出", "存档，返回菜单界面", "", 0);
	helpwanttosay("别点", "别点", "保存并退出，哦", "好难懂的五个字啊", 0);
	arrow(800, 50, "投降", "当前操作方败北", "对方获得胜利", 0);
	helpwanttosay("别点", "别点", "懦夫行为", "", 0);
	option_btn(CANT_co);							//以还原结束

	exit_btn(OK_co);  //以标亮开始
	arrow(800, 50, "退出", "不保存直接退出", "", 0);
	helpwanttosay("别点", "别点", "随时可以退出", "多么幸运", 0);
	exit_btn(CANT_co);								//以还原结束

	save_btn(OK_co);
	option_btn(OK_co);
	exit_btn(OK_co);
	Map_partial(837, 46, 976, 88 + 41 * 2);
	Map_partial(800 - 310, 0, 800, 100);			//还原画上去的东西
}
int step3()
{
	step3_1();
	step3_2();
	step3_3();
	step3_4();
	return 4;
}

void step3_1()
{
	helpwanttosay("别点", "别点", "接下来是行动区", "你要通过这里进行指挥", 0);
	arrow(150, 530, "行动区：", "选中兵种之后再次点击", "进行操作，右键取消", 0);

	move_button(CANT_co);
	attack_button("攻击", CANT_co);
	stay_button("驻扎", CANT_co);
	del_button(CANT_co);
	helpwanttosay("别点", "别点", "太多了懒得说", "你自己点吧", 0);
	if (helpwanttosay("继续", "退出", "点击进行下一步", "或者不看了退出？", 1) == 0)
	{
		helpwanttosay("不可", "退出", "端正你的态度，新兵", "磨刀不误砍柴工", 0);
	}
	Map_partial(262, 218, 262 + 500, 219 + 230);
}

void step3_2()
{
	attack_button("攻击", OK_co);//以标亮开始
	arrow(150, 530, "攻击：根据你所选兵种", "的攻击力扣除敌人血", "量，注意范围限制", 1);
	attack_button("攻击", CANT_co);//以还原结束

	move_button(OK_co);//以标亮开始
	arrow(150, 530, "移动：兵种的移动力代", "表了你能最远抵达的格", "子数", 1);
	arrow(150, 530, "需要注意的是，有些地", "形消耗移动力为2甚至", "完全不能通过", 1);
	move_button(CANT_co);//以还原结束

	stay_button("驻扎", OK_co);//以标亮开始
	arrow(150, 530, "驻扎：驻扎可以增加一", "点你的攻击力，同时每", "回合可以回复一点血", 1);
	stay_button("驻扎", CANT_co);//以还原结束

	del_button(OK_co);//
	arrow(150, 530, "删除：删除将直接撤退", "你的军队", "", 1);
	del_button(CANT_co); //
	Map_partial(150, 530 - 50, 150 + 310, 530 + 50);

	move_button(OK_co);
	attack_button("攻击", OK_co);
	stay_button("驻扎", OK_co);
	del_button(OK_co);
	helpwanttosay("别点", "别点", "忘了说，每回合", "每个单位只能操作一次", 0);
}

void step3_3()
{
	Battleinfo batinfo;
	batinfo.round = 1;
	batinfo.b_source = 5;
	nextr_button(65370);			//以标亮开始
	delay(1000);
	helpwanttosay("别点", "别点", "众所周知", "造兵是要钱的", 0);
	helpwanttosay("别点", "别点", "那么钱从哪来？", "", 0);
	arrow(850, 600, "下一回合，结束你本回", "合的操作，得到新的资", "源，并恢复行动力", 0);
	helpwanttosay("别点", "别点", "每回合你可以得到", "一些钱，军队也可以重新操作", 0);
	delay(1000);
	helpwanttosay("别点", "别点", "资源数显示在左下角", "回合数显示在右下角", 0);
	disp_bat_info(batinfo);
	delay(1000);
	nextr_button(65340);			//以还原结束
	Map_partial(850 - 310, 600 - 50, 850, 600 + 50);
}
void step3_4()
{
	helpwanttosay("别点", "别点", "在我下面的是", "消息提示框", 0);
	helpwanttosay("别点", "别点", "他会在战斗中帮助你", "非常非常重要", 0);
	helpwanttosay("别点", "别点", "不过他和我不一样", "他刻板又严谨", 0);
	show_msg("不要随意谈论别人，小子", "我在听");
	delay(3000);
	helpwanttosay("别点", "别点", "哦，哦，好吧", "反正他说的话非常重要", 0);
	show_msg("你好新兵", "你可以叫我麦斯基");
	delay(3000);
	show_msg("我比海尔普好运一些", "我会经常出现");
	delay(3000);
	show_msg("", "");
}
int step4(MAP map)
{
	int flag = 0;
	DBL_POS ptmp;
	OFF_POS opos;
	if (step4_1() == 0)
	{
		return 0;
	}

	while (1)
	{
		Newxy();
		if ((flag = clcmap(&ptmp, map)) != 0)
		{
			if (flag == 3)
			{
				show_msg("再次点选进行升级！", "右键取消");
				step4_2(0, map);
				return 5;
			}
		}
	}
}

int step4_1()
{
	helpwanttosay("别点", "别点", "基本信息已经介绍完了", "下面我会给你演示操作", 0);
	if (helpwanttosay("继续", "离开", "或者说你想离开？", "不过我会一直在这", 1) == 0)
	{
		helpwanttosay("真好", "真好", "能离开", "真好啊", 0);
		return 0;
	}
	helpwanttosay("别点", "别点", "好的，让我们继续吧", "（进入操作演示）", 0);
	helpwanttosay("别点", "别点", "这张作战地图是你的战场", "战斗将会发生在这", 0);
	helpwanttosay("别点", "别点", "点击一下大本营试试", "就是地图边缘的帐篷", 0);
	return 1;
}

void step4_2(int side, MAP map)
{
	POS pos;
	int armkind;
	CELL cell;
	unsigned source = 100;
	step421(side);
	step422(side, map);
	step423();
	step424(source, map);
	return;
}

void step421(int side)
{
	POS pos;
	pos.x = 745;
	pos.y = 705;
	Map_partial(740, 670, 980, 742);
	icon(pos, side, BUILDER);
	pos.x = 745 + 65;
	icon(pos, side, INFANTRY);
	pos.x = 745 + 65 * 2;
	icon(pos, side, ARTILLERY);
	pos.x = 745 + 65 * 3;
	icon(pos, side, TANK);
	pos.x = 745 + 65 * 4;
	icon(pos, side, SUPER);
	helpwanttosay("别点", "别点", "当你进入大本营之后", "你可以进行升级或者造兵", 0);
	helpwanttosay("别点", "别点", "再次点击大本营升级", "或者点击右下角进行造兵", 0);
	helpwanttosay("别点", "别点", "现在先试着造一个步兵", "点击右下角头盔图标", 0);
	helpwanttosay("别点", "别点", "麦斯基会给你提示信息", "跟着他做", 0);
}

void step422(int side, MAP map)
{
	POS pos;
	CELL cell;
	unsigned source = 100;
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 - 18, 705 - 18, 745 + 65 + 18, 705 + 23) == MOUSE_IN_L)
		{
			//pos = center_xy(5, 11);
			//icon(pos, side, armkind);
			buildarm(map, &source, 0);
			helpwanttosay("别点", "别点", "干得漂亮", "现在你有一个步兵了", 0);
			helpwanttosay("别点", "别点", "你一共能指挥五个兵种", "具体信息可以看左边和下边", 0);
			show_msg("", "");

			cell.kind = BUILDER;
			cell.health = 2;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "工兵，图标是一个锤子", "工兵不能攻击也比较脆弱", "但他却是获胜的关键", 1);
			arrow(750, 705 - 18, "他可以建造采集矿区的", "采集站，还可以建造医", "疗站来治疗伤势", 1);
			cell.kind = INFANTRY;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "步兵，图标是一个头盔", "步兵的优点是造价低廉", "但各项素质都比较低", 1);
			cell.kind = ARTILLERY;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "炮兵，图标是一门炮", "炮兵射程远,也有较高", "的攻击力，但移动力非", 1);
			arrow(750, 705 - 18, "常低", "甚至不能进入森林", "", 1);
			cell.kind = TANK;
			cell.health = 5;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "坦克，图标是一辆坦克", "坦克拥有高命高攻高移", "造价也不是很贵", 1);
			cell.kind = SUPER;
			cell.health = 13;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "超级兵，图标是一柄刀", "超级兵拥有不合常理的", "高属性，但是攻击大本", 1);
			arrow(750, 705 - 18, "营伤害很低，只有", "一点", "", 1);
			Map_partial(750 - 310, 705 - 18 - 50, 750, 705 - 18 + 50);
			cell.kind = 0;
			disp_arm_info(cell);
			pos.x = 745;
			pos.y = 705;
			icon(pos, side, BUILDER);
			helpwanttosay("懂了", "没懂", "就这些", "看懂了没有", 1);
			helpwanttosay("别点", "别点", "管你懂没懂", "继续", 0);
			helpwanttosay("别点", "别点", "现在建造一个炮兵", "用我刚才教你的操作", 0);
			break;
		}
		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)
		{
			helpwanttosay("别点", "别点", "是的是的，我让你跟着他做", "但不要取消！", 0);
		}
	}
}
void step423()
{
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L)
		{
			show_msg("炮兵，造价：5", "再次点选确定建造，右键取消");
			delay(50);
			break;
		}
	}
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L)
		{
			show_msg("需要大本营等级：2", "建造失败");
			helpwanttosay("别点", "别点", "啊哦,建造失败了", "因为大本营等级不够", 0);
			helpwanttosay("别点", "别点", "工兵和步兵一级就可以建造", "炮兵和坦克需要二级大本营", 0);
			helpwanttosay("别点", "别点", "而超级兵需要三级大本营", "", 0);
			show_msg("再次点选进行升级！", "右键取消");
			helpwanttosay("别点", "别点", "我已经帮你选中了大本营", "现在升级一次", 0);
			break;
		}
	}
}

void step424(unsigned source, MAP map)
{
	int flag = 0;
	POS pos;
	while (1)
	{
		Newxy();
		if ((flag = clcmap(&pos, map)) != 0)
		{
			if (flag == 3)
			{
				levelup(pos, map, &source);
				disp_arm_info(map[9][1]);
				disp_geo_info(map[9][1]);
				helpwanttosay("别点", "别点", "升级成功！不如再试一试", "造一个炮兵", 0);
				break;
			}
		}
	}
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L)
		{
			show_msg("出兵点被占领", "请消灭敌军或先移动我方单位");
			helpwanttosay("别点", "别点", "又失败了", "", 0);
			helpwanttosay("别点", "别点", "地图上出兵点是固定的", "那里不能有军队存在", 0);
			break;
		}
	}
}
int step5(MAP map)
{
	DBL_POS ptmp;
	OFF_POS otmp;
	POS center;
	//step422(0, map);                                  //记得删除
	step5_1(map);
	step5_2(map);
	step5_3(map);
	return 6;
}
void step5_1(MAP map)
{
	DBL_POS ptmp;
	OFF_POS otmp;
	POS center;
	helpwanttosay("别点", "别点", "现在让我教你如何移动", "首先点选步兵", 0);
	while (map[10][2].kind != 0)
	{
		if (Clcmap(&ptmp, map) == 2)
		{
			disp_arm_info(map[10][2]);
			helpwanttosay("别点", "别点", "然后点击移动键", "仔细想想你能走的位置", 0);
			helpwanttosay("别点", "别点", "啊哦，我有点碍事", "看样子我得先离开一下", 0);
			Map_partial(262, 218, 262 + 500, 219 + 230);
			while (1)
			{
				Newxy();
				if (move_btn_fun(65370, 65340))
				{
					move(ptmp, map, 2);
					otmp = D2O(ptmp);
					center = center_xy(ptmp.x, ptmp.y);   //这记得改
					show_msg("", "");
					move_button(OK_co);
					break;
				}
			}
			delay(500);
			Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);
			map[otmp.y][otmp.x].kind = 0;
		}
		else
		{
			helpwanttosay("别点", "别点", "学会走路还挺难的", "对吧", 0);
			Map_partial(262, 218, 262 + 500, 219 + 230);
		}
	}
}
void step5_2(MAP map)
{
	POS center;
	map[10][2].kind = ARTILLERY;
	map[10][2].health = 2;
	map[10][2].side = 0;
	center = center_xy(5, 11);
	icon(center, 0, ARTILLERY);
	helpwanttosay("别点", "别点", "做的不错", "下面是攻击", 0);
	helpwanttosay("别点", "别点", "攻击要注意攻击范围", "同时也要注意对象", 0);
	helpwanttosay("别点", "别点", "我将在场上放置三支军队", "尝试着做出正确的攻击", 0);
	helpwanttosay("别点", "别点", "点击一下你的炮兵", "开始吧", 0);
	helpwanttosay("别点", "别点", "注意炮兵的攻击范围", "", 0);
	Map_partial(262, 218, 262 + 500, 219 + 230);

	map[8][2].kind = TANK;
	map[8][2].health = 2;
	map[8][2].side = 0;
	center = center_xy(5, 9);
	icon(center, 0, TANK);

	map[8][3].kind = BUILDER;
	map[8][3].health = 2;
	map[8][3].side = 1;
	center = center_xy(7, 9);
	icon(center, 1, BUILDER);

	map[7][2].kind = SUPER;
	map[7][2].health = 2;
	map[7][2].side = 1;
	center = center_xy(6, 8);
	icon(center, 1, SUPER);
}
void step5_3(MAP map)
{
	DBL_POS ptmp;
	while (1)
	{
		Newxy();
		ptmp = xy2cell(MouseX, MouseY);
		if (ptmp.x == 5 && ptmp.y == 11 && press == 1)
		{
			disp_arm_info(map[10][2]);
			break;
		}
	}
	while (1)
	{
		Newxy();
		if (atk_btn_fun("攻击", 65370, 65340))
		{
			attack(ptmp, map);
			attack_button("攻击", 65370);
			break;
		}
	}
	helpwanttosay("别点", "别点", "怎么样，简单吧", "", 0);
	helpwanttosay("别点", "别点", "完全不需要训练", "就可做到百发百中", 0);
	helpwanttosay("别点", "别点", "驻扎和删除的功能很简单", "驻扎可以增加一点攻击力", 0);
	helpwanttosay("别点", "别点", "而删除可以撤退你的军队", "", 0);
	helpwanttosay("别点", "别点", "需要注意的是，所有行为", "都会消耗掉该部队的行动力", 0);
}
//int step6(MAP map)
//{
//	helpwanttosay("别点", "别点", "", "", 0);
//
//}
int Clcmap(DBL_POS* pos, MAP map)
{
	while (1)
	{
		Newxy();
		if (clcmap(pos, map) == 1)
			return 1;
		if (clcmap(pos, map) == 2)
			return 2;
		if (clcmap(pos, map) == 3)
			return 3;
	}
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
		Outtext(x-300, y-8, s2, 16, 20, 0);
		Outtext(x-300, y+24, s3, 16, 20, 0);
	}
	if (mode)
	{
		while (1)
		{
			Newxy();
			if (press == 1)
			{
				delay(100);
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
	else
	{
		delay(3000);
		return 1;
	}
}