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
	Arminfo arminfo;//������Ϣ�ݴ�
	int clccell = 0;//�������ͼ��һ������
	int flag, msgflag = 0;
	char s[25] = "SAVES//";
	char tst[20] = "\0";
	FILE* fp;

	DBL_POS test;
	
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


	while(1)
	{
		Newxy();
		

		nxt_btn_fun(65370, 65340);

		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			msgflag = 1;
			opos = D2O(ptmp);
			if (flag == 3)
			{
				clccell = 0;
				disp_geo_info(map[opos.y][opos.x]);
				disp_arm_info(map[opos.y][opos.x]); //������еľ�̬�ṹ�����
				show_msg("Ѫ��", "�ȼ�");
				base_func(map,10);
			}
			if (flag == 2)
			{
				pos = ptmp;
				clccell = 1;
				show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
				/*******************��ʾ��Ϣ********************/
				disp_geo_info(map[opos.y][opos.x]);
				arminfo = disp_arm_info(map[opos.y][opos.x]);
			}
			else
			{
				clccell = 0;
				disp_geo_info(map[opos.y][opos.x]);
				disp_arm_info(map[opos.y][opos.x]); //������еľ�̬�ṹ�����
		 		show_msg("������Ϊ��", "");
			}
		}

		if (clccell && move_btn_fun(65370, 65340))//�ƶ�
		{
			move(pos, map, arminfo.move);
			clccell = 0;
			msgflag = 0;
			delay(50);//���delay����Ҫ�����ڸ��û�ʱ��̧����������move�ж��������ɾ����
		}

		if (clccell && stay_btn_fun("פ��", 65370, 65340))//פ��
		{
			stay(pos, map);
			clccell = 0;
			msgflag = 0;
		}

		if (clccell && atk_btn_fun("����", 65370, 65340))//����
		{
			attack(pos, map);
			clccell = 0;
			msgflag = 0;
		}

		if (clccell && del_btn_fun(65370, 65340))//ɾ��
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
			return MAINMENU;
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

	attack_button("����", 65370);
	stay_button("פ��", 65370);
	move_button(65370);
	del_button(65370);
	nextr_button(65370);

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

	int kind, side;
	POS offpos;

	offpos = D2O(pos);

	kind = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;

	pos = center_xy(pos.x, pos.y);
	switch (kind)
	{
	case BUILDER:
		Icon_builder(pos, side);
		break;
	case INFANTRY:
		Icon_inf(pos, side);
		break;
	case ARTILLERY:
		Icon_arti(pos, side);
		break;
	case TANK:
		Icon_tank(pos, side);
		break;
	case SUPER:
		Icon_super(pos, side);
		break;
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

			opos.x = i;
			opos.y = j;
			dpos = O2D(opos);
			draw_cell(dpos, map);
		}
	}
}

void icon(POS world_pos, int side, int kind)
{
	switch (kind)
	{
	case BUILDER:
		Icon_builder(world_pos, side);
		break;
	case INFANTRY:
		Icon_inf(world_pos, side);
		break;
	case ARTILLERY:
		Icon_arti(world_pos, side);
		break;
	case TANK:
		Icon_tank(world_pos, side);
		break;
	case SUPER:
		Icon_super(world_pos, side);
		break;
	default:
		Icon_draw(world_pos, side);
		break;
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

void disp_geo_info(CELL cell)
{
	char text[20] = "�����ж���", buffer[20];
	static CELL lastcell1;
	if (lastcell1.geo == cell.geo)
		return;
	itoa(move_cost(cell.geo), buffer, 10);
	strcat(text, buffer);

	Bar64k(0, 0, 204, 100, 65370);
	switch (cell.geo)
	{
	case OBSTACLE: 
		Outtext(20, 20, "�ϰ�", 32, 48, 0);
		break;
	case PLAIN: 
		Outtext(20, 20, "ƽԭ", 32, 48, 0);
		break;
	case FOREST: 
		Outtext(20, 20, "ɭ��", 32, 48, 0);
		break;
	case DESERT:
		Outtext(20, 20, "ɳĮ", 32, 48, 0);
		break;
	case BASE:
		Outtext(20, 20, "��Ӫ", 32, 48, 0);
		break;
	case SORC:
		Outtext(20, 20, "��Դ��", 32, 48, 0);
		break;
	case HSORC:
		Outtext(20, 20, "��Դ��", 32, 48, 0);
		break;
	default:
		break;
	}
	cell.geo ? Outtext(20, 70, text, 16, 20, 0) : Outtext(20, 70, "������Խ", 16, 20, 0);
	lastcell1 = cell;
	return;
}

/********��ʾ��ǰ���λ�ñ�����Ϣ*********/
Arminfo disp_arm_info(CELL cell)
{
	Arminfo info;
	char buffer[20] = "\0";
	static CELL lastcell2;

	if (lastcell2.kind == cell.kind && lastcell2.health == cell.health)
		return;

	info = search_info(cell.kind);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
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
		break;
	}
	lastcell2 = cell;
	return info;
}

void base_func(MAP map, int source)
{
	int clcflag = 0;
	Arminfo arminfo;
	POS pos, center = center_xy(3, 9);
	pos.x = 745;
	pos.y = 705;
	icon(pos, map[9][1].side, BUILDER);
	pos.x = 800;
	icon(pos, map[9][1].side, INFANTRY);
	while (1)
	{
		Newxy();
		if (mouse_press(740-18, 705-18, 740+18, 705+23) == MOUSE_IN_L)
		{
			arminfo = search_info(BUILDER);
			if (clcflag == 1)
			{
				clcflag = 0;
				if (source < arminfo.cost)
				{
					show_msg("��Դ�����޷�����", "");
					delay(1000);
					return;
				}
				else if (map[8][1].kind != 0)
				{
					show_msg("�����㱻ռ��", "������о������ƶ��ҷ���λ");
					delay(1000);
					return;
				}
				else 
				{
					map[8][1].kind = BUILDER;
					map[8][1].health = arminfo.health;
					icon(center, map[9][1].side, BUILDER);
					show_msg("����ɹ���", "");
					delay(1000);
					return;
				}
			}
			else
			{
				clcflag = 1;
				show_msg("��������ۣ�2", "�ٴε�ѡȷ������");
				delay(50);
			}
		}
	}
}