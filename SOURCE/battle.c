/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
File_name: battle.c
Author: ���Ƶѡ�����ͩ
Version: 
Description: ս������
Date:

������־

����Ŀ¼
******************************************************************/

#include "common.h"
//ս������������
int battle(char *user, short save_num)
{
	CELL map[13][13];//��ͼ
	DBL_POS pos, ptmp;
	Battleinfo batinfo;//��ս��Ϣ
	char s[20] = "SAVES//";
	FILE* fp;//ָ���û��ļ���ָ��
	int clccell = 0;//�������ͼ��һ������
	int flag, msgflag = 0;
	strcat(s, user);

	if ((fp = fopen(s, "rb+")) == NULL)
	{
		show_error("δ�ҵ��û��浵�ļ�", 1);
	}
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	Clrmous();
	battle_draw();

	map[6][6].side = 1;
	map[6][6].kind = BUILDER;
	pos.x = 13; pos.y = 7;
	//Icon_builder(pos, 1);
	savefile_creat(user);
	initdraw(map);

	while(1)
	{
		Newxy();
		if (Sharp_button(16, "ע���˺�", "ע���˺�", 60361, 65535))
		{
			return MAINMENU;
		}

		if (atk_btn_fun("����", 65535, 65340))
		{
			show_error("�㵽������ť�����Ҿ��Ż���һ��", 0);
		}
		if (stay_btn_fun("פ��", 65535, 65340))
		{
			show_error("�㵽פ����ť�����Ҿ��Ż���һ��", 0);
		}
		nxt_btn_fun(65535, 65340);

		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			msgflag = 1;
			if (flag == 2)
			{
				pos = ptmp;
				clccell = 1;
				show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
			}
			else
			{
				clccell = 0;
				show_msg("������Ϊ��", "");
			}
			//show info
		}
		if (clccell && (mouse_press(20, 528, 141, 649) == MOUSE_IN_L))//�ƶ�
		{
			move(pos, map);
			clccell = 0;
			delay(50);//���delay����Ҫ�����ڸ��û�ʱ��̧����������move�ж��������ɾ����
			msgflag = 0;
		}

		if (msgflag == 0)
		{
			show_msg("��ָ�ӹٽ��в���", "");
			msgflag = 1;
		}


		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//Ϊ�������,���Ͻ��Ҽ�ֱ���˳�
		{
			exit(0);
		}
	}
}
//����ս�����溯��
void battle_draw()
{
	Putbmp64k(0, 0, "BMP//map.bmp");
	Button(16, "�˳�ս��", 60361, 65535);
	attack_button("����", 65535);
	stay_button("פ��", 65535);
	move_button(65535);
	del_button(65535);
	nextr_button(65535);
}
/**********************************************************
Function��		Battle_init
Description��	ս����ʼ����������ȡ�浵
Input:			fp�û��浵�ļ�ָ�룬������һ���Ͷ�
Author��		���Ƶ�
**********************************************************/
void Battle_init(FILE* fp, Battleinfo *info, MAP map)
{
	int i, j;
	
	fseek(fp, 7, SEEK_CUR);//��������
	fread(&(info->round), 2, 1, fp);
	fread(&(info->b_source), 2, 1, fp);
	fread(&(info->r_source), 2, 1, fp);
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fread(map[i] + j, 2, 1, fp);
		}
	}//��ȡ��ͼ��Ϣ
}

void save_battle(FILE* fp, Battleinfo* batinfo, MAP map)
{
	unsigned t[3];
	time_t rawtime;
	struct tm* info;
	int i, j;

	fseek(fp, 1, SEEK_CUR);//�����浵��
	//��ǰʱ������
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//��
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//����
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//ʱ��
	fwrite(t, 2, 3, fp);
	//�غ���Ϣ����
	fwrite(&((*batinfo).round), 2, 1, fp);
	fwrite(&((*batinfo).b_source), 2, 1, fp);
	fwrite(&((*batinfo).r_source), 2, 1, fp);
	//�����ͼ��Ϣ
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fwrite(map[i] + j, 2, 1, fp);
		}
	}
}

void draw_cell(DBL_POS pos, MAP map)
{
	int flag, side;
	OFF_POS offpos;

	offpos = D2O(pos);
	flag = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;
	switch (flag)
	{
	case BUILDER:
		Icon_builder(pos, side);
	case INFANTRY:
		Icon_inf(pos, side);
	case ARTILLERY:
		Icon_arti(pos, side);
	case TANK:
		Icon_tank(pos, side);
	case SUPER:
		Icon_super(pos, side);
	default:
		break;
	}
}

void initdraw(MAP map)
{
	int i, j;
	OFF_POS opos;
	DBL_POS dpos;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (map[j][i].kind)
			{
				opos.x = i;
				opos.y = j;
				dpos = O2D(opos);
				switch (map[j][i].kind)
				{
				case BUILDER:
					Icon_builder(dpos, map[j][i].side);
					break;
				case INFANTRY:
					Icon_inf(dpos, map[j][i].side);
					break;
				case ARTILLERY:
					Icon_arti(dpos, map[j][i].side);
					break;
				case TANK:
					Icon_tank(dpos, map[j][i].side);
					break;
				case SUPER:
					Icon_super(dpos, map[j][i].side);
					break;
				default:
					break;
				}
			}
		}
	}
}