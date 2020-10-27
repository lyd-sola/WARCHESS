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

	move_button(600);
	show_msg("��ѡ��Ҫ�ƶ���λ��", "����Ҽ�ȡ��");
	/*���ﱾ���뷨�Ǳ������п����ߵĵ㣬�д�ʵ��*/
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//��Ҫ��֤�����ж���
		{
			if (move_(From, dbto, able, map) == 1)
			{
				return;
			}
			else
			{
				show_msg("�˴��޷�����", "����ѡ��Ŀ�ĵ�");
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//�Ҽ�ȡ��
		{
			move_button(65370);
			return;
		}
	}
}
int move_(DBL_POS From, DBL_POS dbto, int able, MAP map)
{
	int visit[7][7];
	OFF_POS To = D2O(dbto);//���Ŀ��ƫ������
	OFF_POS ofrom = D2O(From);
	memset(visit, 0, sizeof(visit));
	range(map, From, able, 0, visit);
	if (map[To.y][To.x].kind == NOARMY)//Ϊ�տ��ƶ����Ժ��������ƶ������������ж��Ƿ�ԭ���ƶ�
	{
		if (moving(map, visit, From, dbto))
		{
			map[To.y][To.x].stay = 0;//�ƶ����פ��״̬
			map[To.y][To.x].flag = 1;//������ƶ�
			map[To.y][To.x].health = map[ofrom.y][ofrom.x].health;
			map[To.y][To.x].kind = map[ofrom.y][ofrom.x].kind;
			map[To.y][To.x].side = map[ofrom.y][ofrom.x].side;//�ƶ�
			map[ofrom.y][ofrom.x].kind = NOARMY;//������������
			return 1;
		}
		else 
			return 0;
	}
	else
	{
		show_msg("�˴��ѱ�ռ��", "");
		move_button(65370);
		delay(1000);
		return 1;
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
		map[opos.y][opos.x].flag = 1;
		show_msg("פ���ɹ�", "");
	}
	delay(1000);
	return;
}

void attack(DBL_POS dpos, MAP map)
{
	OFF_POS opos, to;
	DBL_POS dbto;
	POS center;
	Arminfo info;
	int Stay_pos;

	opos = D2O(dpos);
	info = search_info(map[opos.y][opos.x].kind); //��ȡ��ǰλ�ñ�����Ϣ

	attack_button("����", 600);
	show_msg("��ѡ��Ҫ������λ��", "�Ҽ�ȡ��");

	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//��Ҫ��֤�����ж���
		{
			to = D2O(dbto);
			if (map[to.y][to.x].kind) //Ŀ�겻Ϊ�տ��Թ���
			{
				if(attack_(info, map, dpos, dbto, Stay_pos) == 1)
					return;
				else
					show_msg("�򲻵� QAQ", "������ѡ��Ŀ��");
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//�Ҽ�ȡ��
		{
			attack_button("����", 65370);
			return;
		}
	}
}

int attack_(Arminfo info, MAP map, DBL_POS dpos, DBL_POS dbto, int Stay_pos)
{
	POS center = center_xy(dbto.x, dbto.y);
	OFF_POS to = D2O(dbto);
	OFF_POS opos = D2O(dpos);
	if (attack_judge(map, info.distance, dpos, dbto))
	{
		Stay_pos = map[opos.y][opos.x].stay;
		center = center_xy(dbto.x, dbto.y);
		if (map[to.y][to.x].side == map[opos.y][opos.x].side) //Ŀ�겻��Ϊͬ��Ӫ
		{
			show_msg("�����Թ����Ѿ���", "����ô����");
			delay(1000);
			return 1;
		}
		else
		{
			if (info.attack >= map[to.y][to.x].health) //Ŀ���˽�
			{
				Clrmous();
				map[to.y][to.x].kind = NOARMY;
				show_msg("Ŀ���ѱ�����", "");
				draw_bomb(center.x, center.y + 10, 0);
				delay(1000);
				Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);//��ԭ�˴���ͼ
				return 1;
			}

			else
			{
				//����פ�������Ĺ�ʽ������Ϊפ��֮�󹥻���+2��������+1�����ܵ����˺�-1��
				map[to.y][to.x].health -= (info.attack + Stay_pos * 2);
				show_msg("FIRE!", "");
				draw_bomb(center.x, center.y + 10, 0);
				delay(1000);
				draw_cell(dbto, map);
				//icon(center, map[to.y][to.x].side, map[to.y][to.x].kind);
				return 1;
			}
			return 1;
		}
	}
	else
		return 0;
}
void delarm(DBL_POS dpos, MAP map)
{
	POS center;
	OFF_POS opos;
	center = center_xy(dpos.x, dpos.y);
	opos = D2O(dpos);
	map[opos.y][opos.x].kind = NOARMY;
	show_msg("�ò����ѳ��ˣ�", "");
	delay(1000);
	Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23);
	return;
}

//��һ�غϺ���
void nxt_round(MAP map, Battleinfo* info, int *pside)
{
	int i, j, perround = 1;
	Arminfo arminfo;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (map[j][i].kind != NOARMY)
			{
				map[j][i].flag = 0;
				if (map[j][i].faci == MEDICAL && map[j][i].kind != NOARMY)
				{
					arminfo = search_info(map[j][i].kind);
					if(map[j][i].health < arminfo.health) //��ֹҽ��վ��Ѫ�ӱ�
						map[j][i].health += 1;
				}
			}
		}
	}
	if (*pside)
	{
		/*����ÿ�غ�������Դ���Ĺ�ʽ����ʼÿ�غ�һ
		* ��Ӫ�ȼ�������+1 ��Ӫ�ȼ�������+3
		* ��ͨ��Դ��ÿռ��һ��ÿ�غ�+1
		* �߼���Դ��ÿռ��һ��ÿ�غ�+3*/
		//perround+=(2*map[9][1].kind-1)+(map[3][1].kind*map[3][1].side)+(map[9][10].kind*map[9][10].side)+(map[6][6].kind*map[6][6].side*3);
		if (map[3][10].kind > 1) //��Ӫ2��
			perround += 1;
		if (map[3][10].kind > 2) //��Ӫ3��
			perround += 2;
		if (map[3][1].faci == COLLECTION && map[3][1].side == 1) //��ͨ��Դ���Ƿ�ռ��
			perround += 1;
		if (map[9][10].faci == COLLECTION && map[9][10].side == 1) //ͬ��
			perround += 1;
		if (map[6][6].health >= 5 && map[6][6].side == 1) //�����Դ���Ƿ�ռ����غ�����
			perround += 3;
		info->r_source += perround;

		/*********���µ��ж�Ϊ������һ�غϣ����췽�����ж�����Ҫ���ӵ���Ϣ**********/
		/**********�������غ�������Դռ��غ�������Դ���Ƿ�ɱ�**************/
		if (map[3][1].faci == COLLECTION ) //ÿ����Դ��ֻ�ܿ���20�غ�, ��ֻ�ܿ���һ��
		{
			if(map[3][1].health <= 20)
				map[3][1].health++;
			else
			{
				map[3][1].faci = NOARMY;
				map[3][1].flag = 1;
			}
		}
		if (map[9][10].faci == COLLECTION) //ÿ����Դ��ֻ�ܿ���20�غ�, ��ֻ�ܿ���һ��
		{
			if (map[9][10].health <= 20)
				map[9][10].health++;
			else
			{
				map[9][10].faci = NOARMY;
				map[9][10].flag = 1;
			}
		}
		if (map[6][6].faci == COLLECTION) //ÿ����Դ��ֻ�ܿ���20�غ�, ��ֻ�ܿ���һ��
		{
			if (map[6][6].health <= 25)
				map[6][6].health++;
			else
			{
				map[6][6].faci = NOARMY;
				map[6][6].flag = 1;
			}
		}
	}
	else
	{
		//û����ʶ���ṹ������uint�ͣ�ֻ�ֲܷ�����
		if (map[9][1].kind > 1) //��Ӫ2��
			perround += 1;
		if (map[9][1].kind > 2) //��Ӫ3��
			perround += 2;
		if (map[3][1].faci == COLLECTION && map[3][1].side == 0) //��ͨ��Դ���Ƿ�ռ��
			perround += 1;
		if (map[9][10].faci == COLLECTION && map[9][10].side == 0) //ͬ��
			perround += 1;
		if (map[6][6].health >= 5 && map[6][6].side == 0) //�����Դ���Ƿ�ռ����غ�����
			perround += 3;
		info->b_source += perround;
	}
	info->round += 1; //ÿ��һ����һ�غ�����һ�Σ����˱����������Ļغ�����(round+1)/2���������Ļغ���
	*pside = (*pside) ? 0 : 1; //�л���Ӫ
}

void next_r_banner(int side)
{
	char* s = side ? "�췽�غ�" : "�����غ�";
	banner(512 - 240, 300, 480);
	Outtextxx(312 + 40, 300 + 50 - 24, 712 - 40, s, 48, 0);
	delay(msg_sec);
}

//��Ӫ���ܺ���
void base_func(MAP map, unsigned* source, int side)
{
	POS pos, dpos;
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
	while (1)
	{
		Newxy();
		//�ٴε����Ӫ�Դ�Ӫ��������
		if (clcmap(&dpos, map) == 3 && map[D2O(dpos).y][D2O(dpos).x].side == side) //��ֹ����Դ������������Ͷ����Ϊ�����Ľ�
		{
			levelup(dpos, map, source);
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			return;
		}
		//������½Ǳ���ͼ��������ʾ��Ϣ���ٴε���������
		if (mouse_press(745-18, 705-18, 745+65*4+18, 705+23) == 1)
		{
			buildarm(map, source, side);
			Clrmous();
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			return;
		}
		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)	//�Ҽ�ȡ��
		{
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			show_msg("ȡ������", "");
			delay(500);
			return;
		}
		if (mouse_press(45-18, 705-18, 745+65*4+18, 705+23) == MOUSE_OUT_L)
		{
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23);
			return;
		}
	}
}

//��Ӫ��������
void levelup(DBL_POS dpos, MAP map, unsigned* source)
{
	OFF_POS opos = D2O(dpos);
	int cost = (map[opos.y][opos.x].kind == 1 ? 10 : 50);
	if (map[opos.y][opos.x].kind == 3)
	{
		show_msg("��Ӫ������", "����ʧ��");
		delay(1000);
		return;
	}
	else if (*source < cost) //һ������������10��Դ�� ��������������50��Դ
	{
		show_msg("��Դ�����޷�����", "");
		delay(1000);
		return;
	}
	else
	{
		show_msg("�����ɹ�", "");
		map[opos.y][opos.x].kind++;
		Bar64k(0, 0, 204, 100, 65370);
		Filltriangle(0, 100, 0, 350, 204, 100, 65370);
		disp_geo_info(map[opos.y][opos.x]);
		*source -= cost;
		delay(1000);
		return;
	}
}

//������ֺ���
void buildarm(MAP map, unsigned* source, int side)
{
	int armkind = 0;
	Arminfo arminfo;
	POS pos, center, dpos, opos;
	opos.x = !side ? 1 : 10;
	opos.y = !side ? 9 : 3;
	if (mouse_press(745 - 18, 705 - 18, 745 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ�й���
	{
		armkind = BUILDER; //Ϊ�ڶ��ε�ѡȷ������ֵ
		show_msg("��������ۣ�2", "�ٴε�ѡȷ�����죬�Ҽ�ȡ��");
		delay(100); //ʹ�û���ʱ�佫���̧����
	}
	else if (mouse_press(745 + 65 - 18, 705 - 18, 745 + 65 + 18, 705 + 23) == MOUSE_IN_L)//��һ�ε�ѡѡ�в���
	{
		armkind = INFANTRY;
		show_msg("��������ۣ�1", "�ٴε�ѡȷ�����죬�Ҽ�ȡ��");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ���ڱ�
	{
		if (map[opos.y][opos.x].kind < 2)
		{
			show_msg("��Ҫ��Ӫ�ȼ���2", "����ʧ��");
			delay(1000);
			return;
		}
		armkind = ARTILLERY;
		show_msg("�ڱ�����ۣ�5", "�ٴε�ѡȷ�����죬�Ҽ�ȡ��");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 3 - 18, 705 - 18, 745 + 65 * 3 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ��̹��
	{
		if (map[opos.y][opos.x].kind < 2)
		{
			show_msg("��Ҫ��Ӫ�ȼ���2", "����ʧ��");
			delay(1000);
			return;
		}
		armkind = TANK;
		show_msg("̹�ˣ���ۣ�10", "�ٴε�ѡȷ�����죬�Ҽ�ȡ��");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 4 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ�г�����
	{
		if (map[opos.y][opos.x].kind < 3)
		{
			show_msg("��Ҫ��Ӫ�ȼ���3", "����ʧ�ܣ��Ҽ�ȡ��");
			delay(msg_sec);
			return;
		}
		armkind = SUPER;
		show_msg("����������ۣ�30��", "�ٴε�ѡȷ�����죬�Ҽ�ȡ��");
		delay(100);
	}
	else
	{
		return;
	}
	while (1)
	{
		Newxy();
		if (press == 1)
		{
			if (Mouse_above(745 + 65 * (armkind - 1) - 18, 705 - 18, 745 + 65 * (armkind - 1) + 18, 705 + 23))
			{
				arminfo = search_info(armkind);
				if (*source < arminfo.cost) //��Դ�����޷�����
				{
					show_msg("��Դ�����޷�����", "");
					delay(msg_sec);
					return;
				}
				else if (side == 1) //��ɫ��
				{
					if (map[2][10].kind != 0) //�ж������������Ƿ�ռ��
					{
						show_msg("�����㱻ռ��", "������о������ƶ��ҷ���λ");
						delay(msg_sec);
						return;
					}
					else //����ɹ������³�������Ϣ
					{
						map[2][10].kind = armkind;
						map[2][10].health = arminfo.health;
						map[2][10].side = side;
						map[2][10].stay = 0;
						map[2][10].flag = 1;
						center = center_xy(21, 3);
						icon(center, side, armkind);
					}
				}
				else //��ɫ��
				{
					if (map[10][2].kind != 0) //�жϺ�ɫ���������Ƿ�ռ��
					{
						show_msg("�����㱻ռ��", "������о������ƶ��ҷ���λ");
						delay(msg_sec);
						return;
					}
					else //����ɹ������³�������Ϣ
					{
						map[10][2].kind = armkind;
						map[10][2].health = arminfo.health;
						map[10][2].side = side;
						map[10][2].stay = 0;
						map[10][2].flag = 1;
						center = center_xy(5, 11);
						icon(center, side, armkind);
					}
				}
				*source -= arminfo.cost;
				show_msg("�����ɹ���", "");
				delay(msg_sec);
				return;
			}
			else//�𴦵��
			{
				show_msg("ȡ������", "");
				delay(500);
				return;
			}
		}
		else if (press == 2)	//�Ҽ�ȡ��
		{
			show_msg("ȡ������", "");
			delay(500);
			return;
		}
	}
}

void builder_build(DBL_POS dpos, MAP map)
{
	OFF_POS opos;
	opos = D2O(dpos);
	if (map[opos.y][opos.x].faci != NOARMY)
	{
		show_msg("�˴�������ʩ��", "");
	}
	else if (map[opos.y][opos.x].geo == SORC || map[opos.y][opos.x].geo == HSORC)
	{
		map[opos.y][opos.x].faci = COLLECTION;
		show_msg("�ɼ�վ����ɹ���", "�ѿ�ʼ�ɼ���Դ");
	}
	else
	{
		map[opos.y][opos.x].faci = MEDICAL;
		show_msg("ҽ��վ����ɹ���", "�ѿ��Խ�������");
	}
	delay(1000);
	return;
}