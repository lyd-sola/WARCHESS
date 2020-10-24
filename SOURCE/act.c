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
	info = search_info(map[opos.y][opos.x].kind); //��ȡ��ǰλ�ñ�����Ϣ

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
				if (attack_judge(map, info.distance, dpos, dbto))
				{
					Stay_pos = map[opos.y][opos.x].stay;
					Stay_to = map[to.y][to.x].stay;
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
							map[to.y][to.x].health = (map[to.y][to.x].health + Stay_to * 1) - (info.attack + Stay_pos * 2); 
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
					show_msg("�򲻵�QAQ", "����ѡ��Ŀ��");
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