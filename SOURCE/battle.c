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
int battle(char *user, short save_num, short mode)
{
	CELL map[13][13];//��ͼ
	DBL_POS pos, ptmp;
	Battleinfo batinfo;//��ս��Ϣ
	int clccell = 0;//�������ͼ��һ������
	int flag, msgflag = 0;
	char s[25] = "SAVES//";
	FILE* fp;
	
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("δ�ҵ��û��浵�ļ�", 1);

	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	Clrmous();
	battle_draw();
	draw_saves(0, 0, 65535, fp, save_num);

	map[6][6].side = 1;
	map[6][6].kind = BUILDER;
	//pos.x = 13; pos.y = 7;
	//Icon_builder(pos, 1);
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

	//ѡ��˵�
	save_btn(29252);
	exit_btn(29252);
	option_btn(29252);
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
			if (feof(fp) && i*j != 144)
			{
				show_error("��ͼ�ļ�����", 1);
			}
			fread(map[i] + j, 2, 1, fp);
		}
	}//��ȡ��ͼ��Ϣ
}
/**********************************************************
Function��		save_battle
Description��	����浵
Input:			fp�û��浵�ļ�ָ�룬��Ҫָ����ȷ�浵��������һ���Ͷ�
Author��		���Ƶ�
**********************************************************/
void save_battle(FILE* fp, Battleinfo* batinfo, MAP map)
{
	unsigned t[3];
	time_t rawtime;
	struct tm* info;
	int i, j;

	fseek(fp, 1, SEEK_CUR);//����ģʽ��
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


//����һ������buttons.c
void save_btn(int color)
{
	rect_button(800, 10, 800+49, 10+34, "", color);
	Outtext(800 + 24 - 8, 10 + 17 - 8, "s", 16, 0, 0);
	Line64k(833, 23, 833, 34, 0);
	Line64k(834, 23, 834, 34, 0);
	Line45(834, 23, 832, 21, 0);
	Line45(833, 23, 831, 21, 0);
	Line64k(823, 21, 832, 21, 0);
	Line64k(823, 22, 832, 22, 0);
	Line45(823, 21, 821, 19, 0);
	Line45(823, 22, 821, 20, 0);
	Line64k(817, 19, 821, 19, 0);
	Line64k(817, 20, 821, 20, 0);
	Line45(817, 19, 815, 21, 0);
	Line45(815, 22, 817, 20, 0);
	Line64k(815, 22, 815, 34, 0);
	Line64k(816, 22, 816, 34, 0);
	Line45(815, 34, 817, 36, 0);
	Line45(816, 34, 817, 35, 0);
	Line64k(817, 35, 832, 35, 0);
	Line64k(817, 36, 832, 36, 0);
	Putpixel64k(833, 35, 0);
}

void option_btn(int color)
{
	rect_button(880, 10, 880+49, 44, "", color);
	Bar64k(880+14, 10+9, 880+49-14, 10+9+2, 0);
	Bar64k(880+14, 10+9+7, 880+49-14, 10+9+2+7, 0);
	Bar64k(880+14, 10+9+7*2, 880+49-14, 10+9+2+7*2, 0);
}

void exit_btn(int color)
{
	rect_button(960, 10, 960 + 49, 44, "", color);
	Line45(985 + 11, 27 + 11, 985 - 11, 27 - 11, 0);
	Line45(985 + 10, 27 + 11, 985 - 11, 27 - 10, 0);
	Line45(985 + 11, 27 + 10, 985 - 10, 27 - 11, 0);
	Line45(985 + 9, 27 + 11, 985 - 11, 27 - 9, 0);
	Line45(985 + 11, 27 + 9, 985 - 9, 27 - 11, 0);

	Line45(985 + 11, 27 - 11, 985 - 11, 27 + 11, 0);
	Line45(985 + 10, 27 - 11, 985 - 11, 27 + 10, 0);
	Line45(985 + 11, 27 - 10, 985 - 10, 27 + 11, 0);
	Line45(985 + 9, 27 - 11, 985 - 11, 27 + 9, 0);
	Line45(985 + 11, 27 - 9, 985 - 9, 27 + 11, 0);
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