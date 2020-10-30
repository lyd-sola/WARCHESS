/****************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: main.c
author: ���Ƶѡ�����ͩ
version: 2.0
Description: �̳̺�����ʵ����Ϊһ�ζ���
****************************************************/
#include"common.h"
#define SAY 1000
void help_cartoon()
{
	MAP map;
	int step = 1;
	DBL_POS pos;
	Battleinfo batinfo;
	FILE* fp;
	load_battle("HELP", 1, &batinfo, map, &fp);
	battle_draw();
	move_button("�ƶ�", OK_co);
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
			step = step5(map);
			break;
		case 6:
			step = step6(map);
			break;
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

	move_button("�ƶ�", CANT_co);
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

	move_button("�ƶ�", OK_co);//�Ա�����ʼ
	arrow(150, 530, "�ƶ������ֵ��ƶ�����", "����������Զ�ִ�ĸ�", "����", 1);
	arrow(150, 530, "��Ҫע����ǣ���Щ��", "�������ƶ���Ϊ2����", "��ȫ����ͨ��", 1);
	move_button("�ƶ�", CANT_co);//�Ի�ԭ����

	stay_button("פ��", OK_co);//�Ա�����ʼ
	arrow(150, 530, "פ����פ����������һ", "����Ĺ�������ͬʱÿ", "�غϿ��Իظ�һ��Ѫ", 1);
	stay_button("פ��", CANT_co);//�Ի�ԭ����

	del_button(OK_co);//
	arrow(150, 530, "ɾ����ɾ����ֱ�ӳ���", "��ľ���", "", 1);
	del_button(CANT_co); //
	Map_partial(150, 530 - 50, 150 + 310, 530 + 50);

	move_button("�ƶ�", OK_co);
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
	delay(SAY);
	helpwanttosay("���", "���", "Ŷ��Ŷ���ð�", "������˵�Ļ��ǳ���Ҫ", 0);
	show_msg("����±�", "����Խ�����˹��");
	delay(SAY);
	show_msg("�ұȺ����պ���һЩ", "�һᾭ������");
	delay(SAY);
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
	helpwanttosay("���", "���", "������ǳ�Σ����ʱ��", "��ӪҲ���Խ��й���", 0);
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
			helpwanttosay("���", "���", "����������Ҫ������Ӫ", "ͬʱ������Ӫ���Է�����Ϯ", 0);
			helpwanttosay("���", "���", "����Զ��κ�һ�����ӿ�Ϯ", "�ݻ�������ʩ�͵з���λ", 0);
			helpwanttosay("���", "���", "�ǵ��ǵģ��Լ�����ʩҲ��", "û�����ɲ��ᱻ�ݻٰ���", 0);
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
	Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
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
				if (move_btn_fun(65370, 65340, "�ƶ�"))
				{
					move(ptmp, map, 2);
					otmp = D2O(ptmp);
					center = center_xy(ptmp.x, ptmp.y);   //��ǵø�
					show_msg("", "");
					move_button("�ƶ�", OK_co);
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
		if (map[8][3].kind == 0)
			break;
	}
	map[10][2].kind = 0;
	map[8][2].kind = 0;
	map[8][3].kind = 0;
	map[7][2].kind = 0;
	helpwanttosay("���", "���", "��ô�����򵥰�", "", 0);
	helpwanttosay("���", "���", "��ȫ����Ҫѵ��", "�Ϳ��������ٷ�����", 0);
	helpwanttosay("���", "���", "פ����ɾ���Ĺ��ܼܺ�", "פ����������һ�㹥����", 0);
	helpwanttosay("���", "���", "�����פ����Ťת����", "��ɾ�����Գ�����ľ���", 0);
	helpwanttosay("���", "���", "��Ҫע����ǣ�������Ϊ", "�������ĵ��ò��ӵ��ж���", 0);
	Map_partial(200, 346, 340, 540); //���Ƶ�
}
int step6(MAP map)
{
	step6_1();
	step6_2(map);
	step6_3(map);
	step6_4(map);
	step6_5();
	return 0;
}
void step6_1()
{
	DBL_POS dpos;
	POS center;
	helpwanttosay("���", "���", "��������Ҫ�������ȡʤ", "ȡʤ�ķ����ܼ�", 0);
	helpwanttosay("���", "���", "�ݻٵз���Ӫ", "��ͻ�ʤ��", 0);
	helpwanttosay("���", "���", "�������Ӯ����ϰ", "��ô��Դ�Ǻ���Ҫ��", 0);
	helpwanttosay("���", "���", "��Ӫһ��ʱ", "ÿ�غ�ֻ����һ����Դ", 0);
	helpwanttosay("���", "���", "����ÿ�غ���������", "����ÿ�غ������ĵ�", 0);
	helpwanttosay("���", "���", "���Ǻ��٣��԰�", "�Ͼ�������ӪҪ��ô��", 0);
	helpwanttosay("���", "���", "����������Ҫ12��", "����������Ҫ80��", 0);
	helpwanttosay("���", "���", "��ͼ������������Դ��", "�ֱ���������м�", 0);
	dpos.x = 4; dpos.y = 4;
	center = center_xy(dpos.x, dpos.y);
	rectangle64k(center.x - 20, center.y - 20, center.x + 20, center.y + 20, 0);
	rectangle64k(center.x - 20 - 1, center.y - 20 - 1, center.x + 20 + 1, center.y + 20 + 1, 0);
	dpos.x = 22; dpos.y = 10;
	center = center_xy(dpos.x, dpos.y);
	rectangle64k(center.x - 20, center.y - 20, center.x + 20, center.y + 20, 0);
	rectangle64k(center.x - 20 - 1, center.y - 20 - 1, center.x + 20 + 1, center.y + 20 + 1, 0);
	helpwanttosay("���", "���", "��ͼ������������Դ��", "�ֱ���������м�", 0);
	helpwanttosay("���", "���", "��˵�м�Ŀ�������", "�õĺõģ���", 0);
	Map_partial(262, 218, 262 + 500, 219 + 230);
	delay(SAY);
	dpos.x = 13; dpos.y = 7;
	center = center_xy(dpos.x, dpos.y);
	rectangle64k(center.x - 20, center.y - 20, center.x + 20, center.y + 20, 0);
	rectangle64k(center.x - 20 - 1, center.y - 20 - 1, center.x + 20 + 1, center.y + 20 + 1, 0);
	helpwanttosay("���", "���", "�����ˣ�", "��ʲô�ر����", 0);
	dpos.x = 4; dpos.y = 4;
	center = center_xy(dpos.x, dpos.y);
	Map_partial(center.x - 20 - 1, center.y - 20 - 1, center.x + 20 + 1, center.y + 20 + 1);
	dpos.x = 22; dpos.y = 10;
	center = center_xy(dpos.x, dpos.y);
	Map_partial(center.x - 20 - 1, center.y - 20 - 1, center.x + 20 + 1, center.y + 20 + 1);
}
void step6_2(MAP map)
{
	Battleinfo batinfo;
	DBL_POS dpos, ptmp;
	OFF_POS opos;
	POS pos;
	batinfo.b_source = 100;
	helpwanttosay("���", "���", "�������ͨ��Դ��", "ÿ�غϻ�Ϊ�������һ����Դ", 0);
	helpwanttosay("���", "���", "���м�ĸ߼���Դ��", "ÿ�غϻ�Ϊ������������Դ", 0);
	helpwanttosay("���", "���", "���Ǹ߼���Դ�����Ҫ", "������غ�֮��Ż�����", 0);
	helpwanttosay("���", "���", "ͬʱ���ڿ�ʼ�����Դ֮��", "ʮ��غϲɼ�վ�ͻᱨ��", 0);
	helpwanttosay("���", "���", "�����Ҫ������Դ", "�����Ҫѧ�Ὠ��ɼ�վ", 0);
	helpwanttosay("���", "���", "���������ڵ�ǰλ��", "������ʩ", 0);
	helpwanttosay("���", "���", "�����������Դ����", "�ͻὨ��ɼ�վ", 0);
	helpwanttosay("���", "���", "�������", "�ͻὨ��ҽ��վ", 0);
	helpwanttosay("���", "���", "���Ѿ�Ϊ�������һ������", "����һ���ɼ�վ����", 0);
	dpos.x = 4;
	dpos.y = 4;
	opos = D2O(dpos);
	map[opos.y][opos.x].kind = BUILDER;
	map[opos.y][opos.x].side = 0;
	map[opos.y][opos.x].health = 2;
	recover_cell(dpos, map);
	while (1)
	{
		Newxy();
		if (clcmap(&ptmp, map) == 2)
		{
			attack_button("����", OK_co);
			opos = D2O(ptmp);
			disp_arm_info(map[opos.y][opos.x]);
			disp_geo_info(map[opos.y][opos.x]);
			break;
		}
	}
	while (1)
	{
		Newxy();
		if (map[opos.y][opos.x].kind == BUILDER)
		{
			show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
			if (atk_btn_fun("����", OK_co, 65340))
			{
				builder_build(ptmp, map, &batinfo);
				show_msg("����ɹ�", "�ѿ�ʼ�ɼ���Դ");
				break;
			}
		}
	}
	helpwanttosay("���", "���", "WELL DONE!", "�㽨����һ���ɾ���", 0);
	helpwanttosay("���", "���", "Ŷ���ǣ���һ���ɼ�վ", "�������Ѿ���ʼ������", 0);
	helpwanttosay("���", "���", "�����Ĺ�������з��ɼ�վ", "����Ȼ���Խ��첢�Ҵݻ���", 0);
	helpwanttosay("���", "���", "�����ߵ���ĵط�", "����һ��ҽ��վ����", 0);
}
void step6_3(MAP map)
{
	DBL_POS dpos;
	OFF_POS opos;
	Battleinfo batinfo;
	POS center;
	batinfo.r_source = 100;
	while (map[3][1].kind != 0)
	{
		if (Clcmap(&dpos, map) == 2)
		{
			disp_arm_info(map[10][2]);
			while (1)
			{
				Newxy();
				if (move_btn_fun(65370, 65340, "�ƶ�"))
				{
					move(dpos, map, 2);
					show_msg("", "");
					move_button("�ƶ�", OK_co);
					break;
				}
			}
		}
	}
	helpwanttosay("���", "���", "�����ߵ���ĵط�", "����һ��ҽ��վ����", 0);
	while (1)
	{
		Newxy();
		if (clcmap(&dpos, map) == 2)
		{
			attack_button("����", OK_co);
			opos = D2O(dpos);
			disp_arm_info(map[opos.y][opos.x]);
			disp_geo_info(map[opos.y][opos.x]);
			break;
		}
	}
	while (1)
	{
		Newxy();
		if (map[opos.y][opos.x].kind == BUILDER)
		{
			show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
			if (atk_btn_fun("����", OK_co, 65340))
			{
				builder_build(dpos, map, &batinfo);
				show_msg("����ɹ�", "�ѿ��Խ���������");
				break;
			}
		}
	}

	delay(500);
	opos = D2O(dpos);
	center = center_xy(dpos.x, dpos.y);
	Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);
	map[opos.y][opos.x].kind = 0;
	delay(500);
}
void step6_4(MAP map)
{
	OFF_POS opos;
	DBL_POS dpos;
	int i = 1;
	int flag = 0;
	attack_button("����", 65370);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	Bar64k(0, 0, 204, 100, 65370);
	helpwanttosay("���", "���", "��", "����ֻʣ�����һ����", 0);
	helpwanttosay("���", "���", "�ݻٵз��Ĵ�Ӫ��", "", 0);
	opos.x = 10;
	opos.y = 2;
	dpos = O2D(opos);
	map[opos.y][opos.x].kind = SUPER;
	map[opos.y][opos.x].health = 13;
	map[opos.y][opos.x].side = 0;
	draw_cell(dpos, map);
	opos.x = 9;
	opos.y = 3;
	dpos = O2D(opos);
	map[opos.y][opos.x].kind = TANK;
	map[opos.y][opos.x].health = 10;
	map[opos.y][opos.x].side = 0;
	draw_cell(dpos, map);
	helpwanttosay("���", "���", "ѡ����ʵĲ���", "���ٵ�����з���Ӫ", 0);
	while (map[3][10].kind != 0)
	{
		Newxy();
		if (clcmap(&dpos, map) == 2)
		{
			show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
			opos = D2O(dpos);
			if (map[opos.y][opos.x].kind == SUPER)
			{
				if (flag == 0)
				{
					helpwanttosay("���", "���", "���������Ӫֻ��һѪ��", "Ϊʲô������˵��", 0);
					helpwanttosay("���", "���", "����", "�㿪�ľͺ�", 0);
					helpwanttosay("���", "���", "", "", 0);
					flag = 1;
				}
			}
			else
			{
				if (flag == 0)
				{
					helpwanttosay("���", "���", "��ѡ��̹���ǶԵ�", "������˵�Ļ��е�����", 0);
					helpwanttosay("���", "���", "����˵���ѡ�ģ�", "��������ν��", 0);
					helpwanttosay("���", "���", "", "", 0);
					flag = 1;
				}
			}
			disp_geo_info(map[3][10]);
			while (1)
			{
				Newxy();
				if (atk_btn_fun("����", 65370, 65340))
				{
					attack(dpos, map);
					attack_button("����", 65370);
					disp_geo_info(map[3][10]);
					break;
				}
			}
			step6_4_1(i);
			i++;
		}
	}
}
void step6_4_1(int i)
{
	switch (i)
	{
	case 1:
		helpwanttosay("���", "���", "��������", "", 0);break;
	case 2:
		helpwanttosay("���", "���", "��", "��Ӫ��Ѫ����ͦ���", 0);break;
	case 3:
		helpwanttosay("���", "���", "������˵����һ�غ�", "�ǲ��ܹ�����ô��ε�", 0);break;
	case 4:
		helpwanttosay("���", "���", "������ֻ����������һ��", "����ν��", 0);break;
	case 5:
		helpwanttosay("���", "���", "������ҽ̵���ô��", "��û��ʲô�����׵ĵط�", 0);break;
	case 6:
		helpwanttosay("���", "���", "��������ָ�ӵ�ʱ��", "һ��ҪС�Ľ���", 0);break;
	case 7:
		helpwanttosay("���", "���", "��", "Ҫ������", 0);break;
	case 8:
		helpwanttosay("���", "���", "�õ�", "�����˴Σ��ոպ�", 0);break;
	}
}
void step6_5()
{
	helpwanttosay("���", "���", "��ϲ���Ѿ������ȫ���̳�", "������뿪����", 0);
	helpwanttosay("���", "���", "�һ���һֱ����", "ϣ���ټ������ʱ..", 0);
	helpwanttosay("���", "���", "Ŷ�Բ���", "���ǹ��Ʋ����ټ���", 0);
	show_msg("�ټ�", "");
	helpwanttosay("���", "���", "�ټ�", "", 0);
}
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

int helpwanttosay(char* btn1, char* btn2, char* s1, char* s2, int mode)
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
		delay(SAY);
		return 1;
	}
}