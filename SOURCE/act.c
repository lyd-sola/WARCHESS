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
					move_button(65535);
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
				move_button(65535);
				delay(1000);
				return; 
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//�Ҽ�ȡ��
		{
			move_button(65535);
			return;
		}
	}
}