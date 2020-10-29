/****************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: main.c
author: ���Ƶѡ�����ͩ
version: 2.0
Description: �̳̺�����ʵ����Ϊһ�ζ���
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
	attack_button("����", OK_co);
	stay_button("פ��", OK_co);
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
	if (helpwanttosay("����", "�˳�", "�ˣ��±�", "��ӭ����ս��ϵͳ�̳�", 1) == 0)
		return 0;
	if (helpwanttosay("����", "�˳�", "���̳̽�����ʾ��������", "����Խ��Һ�����", 1) == 0)
		return 0;
	if (helpwanttosay("����", "�˳�", "�������ǽ��������Ϣ����", "", 1) == 0)
		return 0;
	helpwanttosay("���", "���", "�ҽ�Ϊ��չʾһ�ζ���", "�����ڽ��������Ϣ���ܣ�", 0);
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
	arrow(210, 100, "��Ϣ��ʾ����", "�������ʾ��ѡ�еı�", "�ֻ������Ϣ", 0);
	helpwanttosay("���", "���", "����ͷ", "������Ϣ��ʾ��", 0);
	disp_arm_info(cell);
	disp_geo_info(cell);
	helpwanttosay("���", "���", "��������", "��ʾһЩ��Ϣ", 0);

	cell.kind = 0;
	cell.geo = 0;
	disp_arm_info(cell);
	disp_geo_info(cell);
	Map_partial(210, 100 - 50, 210 + 310, 100 + 50);
	arrow(800, 50, "����������", "�浵����ѡ������˳���", "", 0);
	helpwanttosay("���", "���", "�����ǹ�����", "����Դ������뿪", 0);

	save_btn(CANT_co);
	option_btn(CANT_co);
	exit_btn(CANT_co);

}
void step2_2()
{
	save_btn(OK_co); //�Ա�����ʼ
	helpwanttosay("���", "���", "�浵�����Ա�����Ľ���", "��ʱ�����Ը���֮ǰ��ս��", 0);
	save_btn(CANT_co);									//�Ի�ԭ����

	option_btn(OK_co); //�Ա�����ʼ//�Ա�����ʼ
	draw_opts();
	helpwanttosay("���", "���", "ѡ�����������ť", "", 0);
	arrow(800, 50, "ע��", "ע��������ʺ�", "", 0);
	helpwanttosay("���", "���", "ע����ζ�š��㡱�뿪����", "", 0);
	arrow(800, 50, "���沢�˳�", "�浵�����ز˵�����", "", 0);
	helpwanttosay("���", "���", "���沢�˳���Ŷ", "���Ѷ�������ְ�", 0);
	arrow(800, 50, "Ͷ��", "��ǰ�������ܱ�", "�Է����ʤ��", 0);
	helpwanttosay("���", "���", "ų����Ϊ", "", 0);
	option_btn(CANT_co);							//�Ի�ԭ����

	exit_btn(OK_co);  //�Ա�����ʼ
	arrow(800, 50, "�˳�", "������ֱ���˳�", "", 0);
	helpwanttosay("���", "���", "��ʱ�����˳�", "��ô����", 0);
	exit_btn(CANT_co);								//�Ի�ԭ����

	save_btn(OK_co);
	option_btn(OK_co);
	exit_btn(OK_co);
	Map_partial(837, 46, 976, 88 + 41 * 2);
	Map_partial(800 - 310, 0, 800, 100);			//��ԭ����ȥ�Ķ���
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
	helpwanttosay("���", "���", "���������ж���", "��Ҫͨ���������ָ��", 0);
	arrow(150, 530, "�ж�����", "ѡ�б���֮���ٴε��", "���в������Ҽ�ȡ��", 0);

	move_button(CANT_co);
	attack_button("����", CANT_co);
	stay_button("פ��", CANT_co);
	del_button(CANT_co);
	helpwanttosay("���", "���", "̫��������˵", "���Լ����", 0);
	if (helpwanttosay("����", "�˳�", "���������һ��", "���߲������˳���", 1) == 0)
	{
		helpwanttosay("����", "�˳�", "�������̬�ȣ��±�", "ĥ�����󿳲�", 0);
	}
	Map_partial(262, 218, 262 + 500, 219 + 230);
}

void step3_2()
{
	attack_button("����", OK_co);//�Ա�����ʼ
	arrow(150, 530, "��������������ѡ����", "�Ĺ������۳�����Ѫ", "����ע�ⷶΧ����", 1);
	attack_button("����", CANT_co);//�Ի�ԭ����

	move_button(OK_co);//�Ա�����ʼ
	arrow(150, 530, "�ƶ������ֵ��ƶ�����", "����������Զ�ִ�ĸ�", "����", 1);
	arrow(150, 530, "��Ҫע����ǣ���Щ��", "�������ƶ���Ϊ2����", "��ȫ����ͨ��", 1);
	move_button(CANT_co);//�Ի�ԭ����

	stay_button("פ��", OK_co);//�Ա�����ʼ
	arrow(150, 530, "פ����פ����������һ", "����Ĺ�������ͬʱÿ", "�غϿ��Իظ�һ��Ѫ", 1);
	stay_button("פ��", CANT_co);//�Ի�ԭ����

	del_button(OK_co);//
	arrow(150, 530, "ɾ����ɾ����ֱ�ӳ���", "��ľ���", "", 1);
	del_button(CANT_co); //
	Map_partial(150, 530 - 50, 150 + 310, 530 + 50);

	move_button(OK_co);
	attack_button("����", OK_co);
	stay_button("פ��", OK_co);
	del_button(OK_co);
	helpwanttosay("���", "���", "����˵��ÿ�غ�", "ÿ����λֻ�ܲ���һ��", 0);
}

void step3_3()
{
	Battleinfo batinfo;
	batinfo.round = 1;
	batinfo.b_source = 5;
	nextr_button(65370);			//�Ա�����ʼ
	delay(1000);
	helpwanttosay("���", "���", "������֪", "�����ҪǮ��", 0);
	helpwanttosay("���", "���", "��ôǮ��������", "", 0);
	arrow(850, 600, "��һ�غϣ������㱾��", "�ϵĲ������õ��µ���", "Դ�����ָ��ж���", 0);
	helpwanttosay("���", "���", "ÿ�غ�����Եõ�", "һЩǮ������Ҳ�������²���", 0);
	delay(1000);
	helpwanttosay("���", "���", "��Դ����ʾ�����½�", "�غ�����ʾ�����½�", 0);
	disp_bat_info(batinfo);
	delay(1000);
	nextr_button(65340);			//�Ի�ԭ����
	Map_partial(850 - 310, 600 - 50, 850, 600 + 50);
}
void step3_4()
{
	helpwanttosay("���", "���", "�����������", "��Ϣ��ʾ��", 0);
	helpwanttosay("���", "���", "������ս���а�����", "�ǳ��ǳ���Ҫ", 0);
	helpwanttosay("���", "���", "���������Ҳ�һ��", "���̰����Ͻ�", 0);
	show_msg("��Ҫ����̸�۱��ˣ�С��", "������");
	delay(3000);
	helpwanttosay("���", "���", "Ŷ��Ŷ���ð�", "������˵�Ļ��ǳ���Ҫ", 0);
	show_msg("����±�", "����Խ�����˹��");
	delay(3000);
	show_msg("�ұȺ����պ���һЩ", "�һᾭ������");
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
				show_msg("�ٴε�ѡ����������", "�Ҽ�ȡ��");
				step4_2(0, map);
				return 5;
			}
		}
	}
}

int step4_1()
{
	helpwanttosay("���", "���", "������Ϣ�Ѿ���������", "�����һ������ʾ����", 0);
	if (helpwanttosay("����", "�뿪", "����˵�����뿪��", "�����һ�һֱ����", 1) == 0)
	{
		helpwanttosay("���", "���", "���뿪", "��ð�", 0);
		return 0;
	}
	helpwanttosay("���", "���", "�õģ������Ǽ�����", "�����������ʾ��", 0);
	helpwanttosay("���", "���", "������ս��ͼ�����ս��", "ս�����ᷢ������", 0);
	helpwanttosay("���", "���", "���һ�´�Ӫ����", "���ǵ�ͼ��Ե������", 0);
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
	helpwanttosay("���", "���", "��������Ӫ֮��", "����Խ��������������", 0);
	helpwanttosay("���", "���", "�ٴε����Ӫ����", "���ߵ�����½ǽ������", 0);
	helpwanttosay("���", "���", "������������һ������", "������½�ͷ��ͼ��", 0);
	helpwanttosay("���", "���", "��˹���������ʾ��Ϣ", "��������", 0);
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
			helpwanttosay("���", "���", "�ɵ�Ư��", "��������һ��������", 0);
			helpwanttosay("���", "���", "��һ����ָ���������", "������Ϣ���Կ���ߺ��±�", 0);
			show_msg("", "");

			cell.kind = BUILDER;
			cell.health = 2;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "������ͼ����һ������", "�������ܹ���Ҳ�Ƚϴ���", "����ȴ�ǻ�ʤ�Ĺؼ�", 1);
			arrow(750, 705 - 18, "�����Խ���ɼ�������", "�ɼ�վ�������Խ���ҽ", "��վ����������", 1);
			cell.kind = INFANTRY;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "������ͼ����һ��ͷ��", "�������ŵ�����۵���", "���������ʶ��Ƚϵ�", 1);
			cell.kind = ARTILLERY;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "�ڱ���ͼ����һ����", "�ڱ����Զ,Ҳ�нϸ�", "�Ĺ����������ƶ�����", 1);
			arrow(750, 705 - 18, "����", "�������ܽ���ɭ��", "", 1);
			cell.kind = TANK;
			cell.health = 5;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "̹�ˣ�ͼ����һ��̹��", "̹��ӵ�и����߹�����", "���Ҳ���Ǻܹ�", 1);
			cell.kind = SUPER;
			cell.health = 13;
			disp_arm_info(cell);
			arrow(750, 705 - 18, "��������ͼ����һ����", "������ӵ�в��ϳ����", "�����ԣ����ǹ�����", 1);
			arrow(750, 705 - 18, "Ӫ�˺��ܵͣ�ֻ��", "һ��", "", 1);
			Map_partial(750 - 310, 705 - 18 - 50, 750, 705 - 18 + 50);
			cell.kind = 0;
			disp_arm_info(cell);
			pos.x = 745;
			pos.y = 705;
			icon(pos, side, BUILDER);
			helpwanttosay("����", "û��", "����Щ", "������û��", 1);
			helpwanttosay("���", "���", "���㶮û��", "����", 0);
			helpwanttosay("���", "���", "���ڽ���һ���ڱ�", "���ҸղŽ���Ĳ���", 0);
			break;
		}
		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)
		{
			helpwanttosay("���", "���", "�ǵ��ǵģ��������������", "����Ҫȡ����", 0);
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
			show_msg("�ڱ�����ۣ�5", "�ٴε�ѡȷ�����죬�Ҽ�ȡ��");
			delay(50);
			break;
		}
	}
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L)
		{
			show_msg("��Ҫ��Ӫ�ȼ���2", "����ʧ��");
			helpwanttosay("���", "���", "��Ŷ,����ʧ����", "��Ϊ��Ӫ�ȼ�����", 0);
			helpwanttosay("���", "���", "�����Ͳ���һ���Ϳ��Խ���", "�ڱ���̹����Ҫ������Ӫ", 0);
			helpwanttosay("���", "���", "����������Ҫ������Ӫ", "", 0);
			show_msg("�ٴε�ѡ����������", "�Ҽ�ȡ��");
			helpwanttosay("���", "���", "���Ѿ�����ѡ���˴�Ӫ", "��������һ��", 0);
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
				helpwanttosay("���", "���", "�����ɹ�����������һ��", "��һ���ڱ�", 0);
				break;
			}
		}
	}
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L)
		{
			show_msg("�����㱻ռ��", "������о������ƶ��ҷ���λ");
			helpwanttosay("���", "���", "��ʧ����", "", 0);
			helpwanttosay("���", "���", "��ͼ�ϳ������ǹ̶���", "���ﲻ���о��Ӵ���", 0);
			break;
		}
	}
}
int step5(MAP map)
{
	DBL_POS ptmp;
	OFF_POS otmp;
	POS center;
	//step422(0, map);                                  //�ǵ�ɾ��
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
	helpwanttosay("���", "���", "�������ҽ�������ƶ�", "���ȵ�ѡ����", 0);
	while (map[10][2].kind != 0)
	{
		if (Clcmap(&ptmp, map) == 2)
		{
			disp_arm_info(map[10][2]);
			helpwanttosay("���", "���", "Ȼ�����ƶ���", "��ϸ���������ߵ�λ��", 0);
			helpwanttosay("���", "���", "��Ŷ�����е㰭��", "�������ҵ����뿪һ��", 0);
			Map_partial(262, 218, 262 + 500, 219 + 230);
			while (1)
			{
				Newxy();
				if (move_btn_fun(65370, 65340))
				{
					move(ptmp, map, 2);
					otmp = D2O(ptmp);
					center = center_xy(ptmp.x, ptmp.y);   //��ǵø�
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
			helpwanttosay("���", "���", "ѧ����·��ͦ�ѵ�", "�԰�", 0);
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
	helpwanttosay("���", "���", "���Ĳ���", "�����ǹ���", 0);
	helpwanttosay("���", "���", "����Ҫע�⹥����Χ", "ͬʱҲҪע�����", 0);
	helpwanttosay("���", "���", "�ҽ��ڳ��Ϸ�����֧����", "������������ȷ�Ĺ���", 0);
	helpwanttosay("���", "���", "���һ������ڱ�", "��ʼ��", 0);
	helpwanttosay("���", "���", "ע���ڱ��Ĺ�����Χ", "", 0);
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
		if (atk_btn_fun("����", 65370, 65340))
		{
			attack(ptmp, map);
			attack_button("����", 65370);
			break;
		}
	}
	helpwanttosay("���", "���", "��ô�����򵥰�", "", 0);
	helpwanttosay("���", "���", "��ȫ����Ҫѵ��", "�Ϳ������ٷ�����", 0);
	helpwanttosay("���", "���", "פ����ɾ���Ĺ��ܼܺ�", "פ����������һ�㹥����", 0);
	helpwanttosay("���", "���", "��ɾ�����Գ�����ľ���", "", 0);
	helpwanttosay("���", "���", "��Ҫע����ǣ�������Ϊ", "�������ĵ��ò��ӵ��ж���", 0);
}
//int step6(MAP map)
//{
//	helpwanttosay("���", "���", "", "", 0);
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
			}//�������
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
			}//���ȷ������1
			if (rec_btn_fun(581, 384, 112 + 581, 45 + 384, 65535))
			{
				return 0;
			}//���ȡ������0
		}
	}
	else
	{
		delay(3000);
		return 1;
	}
}