/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
File_name: battle.c
Author: ���Ƶѡ�����ͩ
Version:
Description: ��ս��Ϊ
Date:

������־

******************************************************************/
#include "common.h"
extern FILE* FBMP;
void move(DBL_POS From, MAP map, int able)//��Ҫ�����ƶ����жϺ��Ƿ�����ж�
{
	OFF_POS To, ofrom;
	DBL_POS dbto;
	int visit[7][7];

	ofrom = D2O(From);
	memset(visit, 0, sizeof(visit));
	range(map, From, able, 0, visit);

	move_button(600);
	show_msg("��ѡ��Ҫ�ƶ���λ��", "����Ҽ�ȡ��");
	/*���ﱾ���뷨�Ǳ������п����ߵĵ㣬�д�ʵ��*/
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//��Ҫ��֤�����ж���
		{
			To = D2O(dbto);//���Ŀ��ƫ������
			if (map[To.y][To.x].kind == NOARMY)//Ϊ�տ��ƶ����Ժ��������ƶ������������ж��Ƿ�ԭ���ƶ�
			{
				if (moving(map, visit, From, dbto))
				{
					Clrmous();

					map[To.x][To.y].stay = 0;//�ƶ����פ��״̬
					map[To.x][To.y].flag = 1;//������ƶ�
					map[To.y][To.x].health = map[ofrom.y][ofrom.x].health;
					map[To.y][To.x].kind = map[ofrom.y][ofrom.x].kind;
					map[To.y][To.x].side = map[ofrom.y][ofrom.x].side;//�ƶ�
					map[ofrom.y][ofrom.x].kind = NOARMY;//������������
					move_button(65370);
					return;
				}
				else
				{
					show_msg("�˴��޷�����", "");
				}
			}
			else
			{
				show_msg("�˴��ѱ�ռ��", "");
				move_button(65370);
				delay(1000);
				return; 
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//�Ҽ�ȡ��
		{
			move_button(65370);
			return;
		}
	}
}

void stay(DBL_POS dpos, MAP map)
{
	OFF_POS opos;
	CELL cell;

	opos = D2O(dpos);

	if (map[opos.y][opos.x].stay)
	{
		show_msg("�Ѿ��ڴ˴�פ����", "");
		
	}
	else
	{
		map[opos.y][opos.x].stay = 1;
		show_msg("פ���ɹ�", "");
	}
	delay(800);
	return;
}

void attack(DBL_POS dpos, MAP map)
{
	OFF_POS opos, to;
	DBL_POS dbto;
	POS center;
	Arminfo info;
	int Stay_to, Stay_pos;

	opos = D2O(dpos);
	attack_button("����", 600);
	show_msg("��ѡ��Ҫ������λ��", "");

	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//��Ҫ��֤�����ж���
		{
			to = D2O(dbto);
			if (map[to.y][to.x].kind) //Ŀ�겻Ϊ�տ��Թ���
			{
				info = search_info(map[opos.y][opos.x].kind); //��ȡ��ǰλ�ñ�����Ϣ
				Stay_pos = map[opos.y][opos.x].stay;
				Stay_to = map[to.y][to.x].stay;
				center = center_xy(dbto.x, dbto.y);
				if (map[to.y][to.x].side == map[opos.y][opos.x].side) //Ŀ�겻��Ϊͬ��Ӫ
				{
					show_msg("�����Թ����Ѿ���", "����ô����");
					delay(1000);
				}
				else
				{
					if (info.attack >= map[to.y][to.x].health) //Ŀ���˽�
					{
						Clrmous();
						map[to.y][to.x].kind = NOARMY;
						show_msg("Ŀ���ѱ�����","");
						draw_bomb(center.x, center.y+10, 0);
						delay(1000);
						Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);//��ԭ�˴���ͼ	
					}
					
					else
					{
						//����פ�������Ĺ�ʽ������Ϊפ��֮�󹥻���+2��������+1�����ܵ����˺�-1��
						map[to.y][to.x].health = (map[to.y][to.x].health + Stay_to * 1) - (info.attack + Stay_pos * 2); 
						show_msg("FIRE!", "");
						draw_bomb(center.x, center.y+10, 0);
						delay(1000);
						icon(center, map[to.y][to.x].side, map[to.y][to.x].kind);
					}
				}
			}
			attack_button("����", 65370);
			return;
		}
		
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//�Ҽ�ȡ��
		{
			attack_button("����", 65370);
			return;
		}
	}
}

void delarm(DBL_POS dpos, MAP map)
{
	POS center;
	center = center_xy(dpos.x, dpos.y);
	map[dpos.y][dpos.x].kind = NOARMY;
	show_msg("�ò����ѳ��ˣ�", "");
	delay(1000);
	Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);
	return;
}