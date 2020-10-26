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
	int step = 1;
	DBL_POS pos;
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
	if (helpwanttosay("����", "�˳�", "�ˣ��±�", "��ӭ����ս��ϵͳ�̳�", 1) == 0)
		return 0;
	if (helpwanttosay("����", "�˳�", "���̳̽�����ʾ��������", "����Խ��Һ�����", 1) == 0)
		return 0;
	if (helpwanttosay("����", "�˳�", "�������ǽ��������Ϣ����", "", 1) == 0)
		return 0;
	helpwanttosay("���", "���", "�����ڽ��������Ϣ���ܣ�", "�ҽ�Ϊ��չʾһ�ζ���", 0);
	delay(3000);
	Map_partial(262, 218, 262 + 500, 219 + 230);
	return 2;	
}

int step2(MAP map)
{
	CELL cell;
	cell.kind = INFANTRY;
	cell.health = 2;
	helpwanttosay("���", "���", "����ͷ", "������Ϣ��ʾ��", 0);
	arrow(200, 100, "��Ϣ��ʾ����", "�������ʾ��ѡ�еı�", "�ֻ������Ϣ", 0);
	delay(3000);
	disp_arm_info(cell);
	helpwanttosay("���", "���", "��������", "��ʾһЩ��Ϣ", 0);
	delay(3000);

	cell.kind = 0;
	disp_arm_info(cell);
	Map_partial(200, 100-50, 200+310, 100+50);
	helpwanttosay("���", "���", "���������ж���", "��Ҫͨ���������ָ��", 0);
	arrow(150, 530, "�ж�����", "ѡ�б���֮���ٴε��", "���в������Ҽ�ȡ��", 0);
	delay(5000);

	move_button(CANT_co);
	attack_button("����", CANT_co);
	stay_button("פ��", CANT_co);
	del_button(CANT_co);
	helpwanttosay("���", "���", "̫��������˵", "���Լ�����", 0);
	delay(3000);
	Map_partial(262, 218, 262 + 500, 219 + 230);

	attack_button("����", OK_co);
	arrow(150, 530, "��������������ѡ����", "�Ĺ������۳�����Ѫ", "����ע�ⷶΧ����", 0);
	delay(3000);
	attack_button("����", CANT_co);

	move_button(OK_co);
	arrow(150, 530, "�ƶ������ֵ��ƶ�����", "����������Զ�ִ�ĸ�", "����", 0);
	delay(3000);
	arrow(150, 530, "��Ҫע����ǣ���Щ��", "�������ƶ���Ϊ2����", "��ȫ����ͨ��", 0);
	delay(3000);
	move_button(CANT_co);

	stay_button("פ��", OK_co);
	arrow(150, 530, "פ����פ����������һ", "����Ĺ�������ͬʱÿ", "�غϿ��Իظ�һ��Ѫ", 0);
	delay(3000);
	stay_button("פ��", CANT_co);

	del_button(OK_co);
	arrow(150, 530, "ɾ����ɾ����ֱ�ӳ���", "��ľ���", "", 0);
	delay(3000);
	del_button(CANT_co);

	helpwanttosay("���", "���", "����˵��ÿ�غ�", "ÿ����λֻ�ܲ���һ��", 0);
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
}