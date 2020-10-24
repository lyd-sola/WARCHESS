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

					map[To.y][To.x].stay = 0;//�ƶ����פ��״̬
					map[To.y][To.x].flag = 1;//������ƶ�
					map[To.y][To.x].health = map[ofrom.y][ofrom.x].health;
					map[To.y][To.x].kind = map[ofrom.y][ofrom.x].kind;
					map[To.y][To.x].side = map[ofrom.y][ofrom.x].side;//�ƶ�
					map[ofrom.y][ofrom.x].kind = NOARMY;//������������
					return;
				}
				else
				{
					show_msg("�˴��޷�����", "����ѡ��Ŀ�ĵ�");
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
				if (attack_judge(map, info.distance, dpos, dbto))
				{
					Stay_pos = map[opos.y][opos.x].stay;
					center = center_xy(dbto.x, dbto.y);
					if (map[to.y][to.x].side == map[opos.y][opos.x].side) //Ŀ�겻��Ϊͬ��Ӫ
					{
						show_msg("�����Թ����Ѿ���", "����ô����");
						delay(1000);
						attack_button("����", 65370);
						return;
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
							attack_button("����", 65370);
							return;
						}
					
						else
						{
							//����פ�������Ĺ�ʽ������Ϊפ��֮�󹥻���+2��������+1�����ܵ����˺�-1��
							map[to.y][to.x].health -= (info.attack + Stay_pos * 2); 
							show_msg("FIRE!", "");
							draw_bomb(center.x, center.y+10, 0);
							delay(1000);
							icon(center, map[to.y][to.x].side, map[to.y][to.x].kind);
							attack_button("����", 65370);
							return;
						}
					}
				}
				else
				{
					show_msg("�򲻵� QAQ", "������ѡ��Ŀ��");
				}
			}
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
	OFF_POS opos;
	center = center_xy(dpos.x, dpos.y);
	opos = D2O(dpos);
	map[opos.y][opos.x].kind = NOARMY;
	show_msg("�ò����ѳ��ˣ�", "");
	delay(1000);
	Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);
	return;
}

//��һ�غϺ���
void nxt_round(MAP map, Battleinfo* info, int *pside)
{
	int i, j, perround = 1;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (map[j][i].kind != NOARMY)
			{
				map[j][i].flag = 1;
			}
		}
	}
	if (*pside)
	{
		/*����ÿ�غ�������Դ���Ĺ�ʽ����ʼÿ�غ�һ
		* ��Ӫ�ȼ�������+1 ��Ӫ�ȼ�������+3
		* ��ͨ��Դ��ÿռ��һ��ÿ�غ�+1
		* �߼���Դ��ÿռ��һ��ÿ�غ�+3*/
		perround+=(2*map[9][1].kind-1)+(map[3][1].kind*map[3][1].side)+(map[9][10].kind*map[9][10].side)+(map[6][6].kind*map[6][6].side*3);
		info->r_source += perround;
		info->round += 1; //���ں췽�����ж������ӻغ���
	}
	else
	{
		//û����ʶ���ṹ������uint�ͣ�ֻ�ֲܷ�����
		if (map[3][10].kind > 1) //��Ӫ1��
			perround += 1;
		if (map[3][10].kind > 2) //��Ӫ2��
			perround += 2;
		if (map[3][1].kind == 1 && map[3][1].side == 0) //��ͨ��Դ���Ƿ�ռ��
			perround += 1;
		if (map[9][10].kind == 1 && map[9][10].side == 0) //ͬ��
			perround += 1;
		if (map[6][6].kind == 1 && map[6][6].side == 0) //�����Դ���Ƿ�ռ��
			perround += 3;
		info->b_source += perround;
	}
	*pside = (*pside) ? 0 : 1; //�л���Ӫ
}

//��Ӫ���ܺ���
void base_func(MAP map, unsigned* source, int side)
{
	POS pos, dpos;
	pos.x = 745;
	pos.y = 705;
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
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23, FBMP);
			return;
		}
		//������½Ǳ���ͼ��������ʾ��Ϣ���ٴε���������
		if (mouse_press(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == 1)
		{
			buildarm(map, source, side);
			Clrmous();
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23, FBMP);
			return;
		}

		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)	//�Ҽ�ȡ��
		{
			Map_partial(745 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23, FBMP);
			show_msg("ȡ������", "");
			delay(500);
			return;
		}
	}
}

//��Ӫ��������
void levelup(DBL_POS dpos, MAP map, unsigned* source)
{
	OFF_POS opos;
	opos = D2O(dpos);
	if (map[opos.y][opos.x].kind == 3)
	{
		show_msg("��Ӫ������", "����ʧ��");
		delay(1000);
		return;
	}
	else if (*source < (map[opos.y][opos.x].kind == 1 ? 10 : 50)) //һ������������10��Դ�� ��������������50��Դ
	{
		show_msg("��Դ�����޷�����", "");
		delay(1000);
		return;
	}
	else
	{
		show_msg("�����ɹ�", "");
		map[opos.y][opos.x].kind += 1;
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
		show_msg("��������ۣ�2", "�ٴε�ѡȷ������");
		delay(100); //ʹ�û���ʱ�佫���̧����
	}
	else if (mouse_press(745 + 65 - 18, 705 - 18, 745 + 65 + 18, 705 + 23) == MOUSE_IN_L)//��һ�ε�ѡѡ�в���
	{
		armkind = INFANTRY;
		show_msg("��������ۣ�1", "�ٴε�ѡȷ������");
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
		show_msg("�ڱ�����ۣ�5", "�ٴε�ѡȷ������");
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
		show_msg("̹�ˣ���ۣ�10", "�ٴε�ѡȷ������");
		delay(100);
	}
	else if (mouse_press(745 + 65 * 4 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ�г�����
	{
		if (map[opos.y][opos.x].kind < 3)
		{
			show_msg("��Ҫ��Ӫ�ȼ���3", "����ʧ��");
			delay(1000);
			return;
		}
		armkind = SUPER;
		show_msg("����ɱ��ȫ��һ���ܴ�����̹������", "ͻ��װ�ױ�����ۣ�30��");
		delay(100);
	}
	else
	{
		return;
	}
	while (1)
	{
		Newxy();
		if (mouse_press(745 + 65 * (armkind - 1) - 18, 705 - 18, 745 + 65 * (armkind - 1) + 18, 705 + 23) == MOUSE_IN_L)
		{
			arminfo = search_info(armkind);
			if (*source < arminfo.cost) //��Դ�����޷�����
			{
				show_msg("��Դ�����޷�����", "");
				delay(1000);
				return;
			}
			else if (side == 1) //��ɫ��
			{
				if (map[2][10].kind != 0) //�ж������������Ƿ�ռ��
				{
					show_msg("�����㱻ռ��", "������о������ƶ��ҷ���λ");
					delay(1000);
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
					delay(1000);
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
			//*source -= arminfo.cost;
			show_msg("����ɹ���", "");
			delay(1000);
			return;
		}
		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)	//�Ҽ�ȡ��
		{
			show_msg("ȡ������", "");
			delay(500);
			return;
		}
	}
}