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
void move(DBL_POS From, MAP map)
{
	OFF_POS To, ofrom;
	DBL_POS dbto;
	POS center;

	ofrom = D2O(From);
	move_button(600);
	show_msg("��ѡ��Ҫ�ƶ���λ��", "");
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//��Ҫ��֤�����ж���
		{
			To = D2O(dbto);//���Ŀ��ƫ������
			if (map[To.y][To.x].kind == NOARMY)//Ϊ�տ��ƶ����Ժ��������ƶ������������ж��Ƿ�ԭ���ƶ�
			{
				Clrmous();
				center = center_xy(From.x, From.y);

				show_msg("�о���", "");
				Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);//��ԭ�˴���ͼ
				center = center_xy(dbto.x, dbto.y);
				Icon_builder(center, 1);//ͼ�껭��Ŀ���
				delay(1000);
				
				//map[To.x][To.y].flag = 1;//������ƶ�
				map[To.y][To.x].health = map[ofrom.y][ofrom.x].health;
				map[To.y][To.x].kind = map[ofrom.y][ofrom.x].kind;
				map[To.y][To.x].side = map[ofrom.y][ofrom.x].side;//�ƶ�
				map[ofrom.y][ofrom.x].kind = NOARMY;//���
				move_button(65535);
				return; 
			}
			else
			{
				show_msg("�˴��ѱ�ռ��", "");
				move_button(65535);
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