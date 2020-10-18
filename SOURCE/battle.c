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
	CELL map[13][13], cell;//��ͼ
	DBL_POS pos, ptmp;
	OFF_POS opos;
	Battleinfo batinfo;//��ս��Ϣ
	Arminfo arminfo1, arminfo2;//������Ϣ�ݴ�
	int clccell = 0;//�������ͼ��һ������
	int flag, msgflag = 0;
	char s[25] = "SAVES//";
	char tst[20] = "\0";
	FILE* fp;

	int visit[5][5];
	
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("δ�ҵ��û��浵�ļ�", 1);
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	battle_draw();

	map[6][6].side = 1;
	map[6][6].kind = BUILDER;
	map[6][5].side = 2;
	map[6][5].kind = INFANTRY;
	initdraw(map);
	
	ptmp.x = 13, ptmp.y = 9;
	memset(visit, 0, sizeof(visit));
	range(map, ptmp, 2, 0, visit);

	while(1)
	{
		Newxy();
		
		nxt_btn_fun(65535, 65340);

		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			msgflag = 1;
			if (flag == 2)
			{

				pos = ptmp;
				opos = D2O(pos);
				clccell = 1;
				show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
				/*******************��ʾ��Ϣ********************/
				disp_arm_info(map[opos.y][opos.x]);
			}
			else
			{
				clccell = 0;

				Filltriangle(0, 100, 0, 350, 205, 100, 65535);
		 		show_msg("������Ϊ��", "");
			}

		}
		if (clccell && move_btn_fun(65535, 65340))//�ƶ�
		{
			move(pos, map);
			clccell = 0;
			delay(50);//���delay����Ҫ�����ڸ��û�ʱ��̧����������move�ж��������ɾ����
			msgflag = 0;
		}

		if (clccell && stay_btn_fun("פ��", 65535, 65340))//פ��
		{
			stay(pos, map);
			clccell = 0;
			msgflag = 0;
		}

		if (clccell && atk_btn_fun("����", 65535, 65340))//����
		{
			attack(pos, map);
			clccell = 0;
			msgflag = 0;
		}

		if (clccell && del_btn_fun(65535, 65340))//ɾ��
		{
			delarm(pos, map);
			clccell = 0;
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

		if (rec_btn_fun(800, 10, 800 + 49, 10 + 34, 65370))//���ٱ���
		{
			if (msgbar("ȷ��", "ȡ��", "����浵��ȷ����", ""))
			{
				seek_savinfo(fp, save_num, 0, 0);
				save_battle(fp, batinfo, map);
			}
			Clrmous();
			Map_partial(262, 218, 262 + 500, 219 + 230, FBMP);
			initdraw(map);
		}
		if (rec_btn_fun(880, 10, 880 + 49, 44, 65370))//ѡ��˵�
		{
			;
		}
		if (rec_btn_fun(960, 10, 960 + 49, 44, 65370))//���
		{
			if (msgbar("ȷ��", "ȡ��", "�˳��ᶪʧδ����Ľ���", "ȷ���˳���"))
			{
				fclose(fp);
				return MAINMENU;
			}
			else
			{
				Clrmous();
				Map_partial(262, 218, 262 + 500, 219 + 230, FBMP);
				initdraw(map);
			}
		}
	}
}
//����ս�����溯��
void battle_draw()
{
	Clrmous();
	Putbmp64k(0, 0, "BMP//map.bmp");

	attack_button("����", 65535);
	stay_button("פ��", 65535);
	move_button(65535);
	del_button(65535);
	nextr_button(65535);

	//ѡ��˵�
	save_btn(65370);
	exit_btn(65370);
	option_btn(65370);
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

void save_battle(FILE* fp, Battleinfo batinfo, MAP map)
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
	fwrite(&(batinfo.round), 2, 1, fp);
	fwrite(&(batinfo.b_source), 2, 1, fp);
	fwrite(&(batinfo.r_source), 2, 1, fp);
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

	flag = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;
	armdraw(flag, pos, side);
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
				armdraw(map[j][i].kind, dpos, map[j][i].side);
			}
		}
	}
}

/*����������Ϣ������disp�����е���*/
Arminfo search_info(int kind)
{
	FILE* fp;
	char buffer[20];
	Arminfo info;
	int i;
	if ((fp = fopen("DATA//info.txt", "r")) == NULL)
	{
		show_error("��ȡ������Ϣʧ��", 0);
		fclose(fp);
		return;
	}
	for (i = 1; i < kind; i++) //������n������
	{
		fgets(buffer, sizeof(buffer), fp);
		buffer[0] = '\0';
	}
	fscanf(fp, "%d%d%d%d%d", &info.health, &info.attack, &info.move, &info.cost, &info.distance);
	fclose(fp);
	return info;
}

/********��ʾ��ǰ���λ�ñ�����Ϣ*********/
Arminfo disp_arm_info(CELL cell)
{
	Arminfo info;
	char buffer[20] = "\0";
	info = search_info(cell.kind);
	Filltriangle(0, 100, 0, 350, 205, 100, 65535);
	switch (cell.kind)
	{
	case BUILDER:
		Outtextxx(20, 120, 110, "����  ����", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(20, 140, 75, "����ֵ", 16, 0);
		Outtext(90, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(20, 160, 75, "������", 16, 0);
		Outtext(90, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(20, 180, 75, "�ж���", 16, 0);
		Outtext(90, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(20, 200, 75, "���", 16, 0);
		Outtext(90, 200, buffer, 16, 16, 0);
		break;
	case INFANTRY:
		Outtextxx(20, 120, 110, "����  ����", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(20, 140, 75, "����ֵ", 16, 0);
		Outtext(90, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(20, 160, 75, "������", 16, 0);
		Outtext(90, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(20, 180, 75, "�ж���", 16, 0);
		Outtext(90, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(20, 200, 75, "���", 16, 0);
		Outtext(90, 200, buffer, 16, 16, 0);
		break;
	default:
		return info;
	}
	return info;
}