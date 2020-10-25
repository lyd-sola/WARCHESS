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
	int clccell = 0;//�������ͼ�ϵ�һ������
	int flag, msgflag = 0;
	int side;//��ǵ�ǰ��Ӫ
	char filename[25] = "SAVES//";	FILE* fp;
	COLO co;

	DBL_POS test;
	
	strcat(filename, user);
	if ((fp = fopen(filename, "rb+")) == NULL)
		show_error("δ�ҵ��û��浵�ļ�", 1);
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	fclose(fp);
	
	change_co(&co, 0, 1);
	battle_draw();

	initdraw(map);
	batinfo.b_source = 50;
	disp_bat_info(batinfo);
	side = (batinfo.round + 1) % 2;

	while(1)
	{
		Newxy();
		if (!msgflag)
		{
			show_msg("��ָ�ӹٽ��в���", "");
			msgflag = 1;
		}
		if (nxt_btn_fun(65370, 65340))
		{
			show_msg("������һ�غ�", "");
			nxt_round(map, &batinfo, &side);
			delay(1000);
			disp_bat_info(batinfo);
		}
		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			opos = D2O(ptmp);
			if (map[opos.y][opos.x].side != side && map[opos.y][opos.x].kind != NOARMY) //����з���λ
			{
				show_msg("��Ϊ�з���λ�����ɲ�����", "");
				disp_arm_info(map[opos.y][opos.x]);
				disp_geo_info(map[opos.y][opos.x]);
				delay(1000);
				continue;
			}
			if (flag == 3) //�����Ӫ
			{
				clccell = 0;
				disp_arm_info(map[opos.y][opos.x]); 
				disp_geo_info(map[opos.y][opos.x]);
				show_msg("�ٴε�ѡ����������", "�Ҽ�ȡ��");
				delay(50);
				base_func(map, side ? (&batinfo.r_source) : (&batinfo.b_source), side);
				disp_bat_info(batinfo);
				msgflag = 0;
			}
			if (flag == 2) //���������λ
			{
				pos = ptmp;
				clccell = 1;
				show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
				msgflag = 1;
				arminfo = disp_arm_info(map[opos.y][opos.x]);//��ʾ��Ϣ
				disp_geo_info(map[opos.y][opos.x]);
				change_co(&co, map[opos.y][opos.x].kind, map[opos.y][opos.x].flag);
				act_buttons(co);
			}
			if(flag == 1) //���
			{
				clccell = 0;
				disp_arm_info(map[opos.y][opos.x]);
				disp_geo_info(map[opos.y][opos.x]);
		 		//show_msg("������Ϊ��", "");
				change_co(&co, 0, 1);
				act_buttons(co);
			}
		}

		if (clccell && move_btn_fun(co.mov, 65340))//�ƶ�
		{
			move(pos, map, arminfo.move);
			clccell = 0;
			move_button(co.mov);
			delay(50);//���delay����Ҫ�����ڸ��û�ʱ��̧����������move�ж��������ɾ����
		}
		if (clccell && stay_btn_fun("פ��", co.stay, 65340))//פ��
		{
			stay(pos, map);
			clccell = 0;
		}
		if (clccell && atk_btn_fun("����", co.atk, 65340))//����
		{
			attack(pos, map);
			clccell = 0;
		}
		if (clccell && del_btn_fun(co.del, 65340))//ɾ��
		{
			delarm(pos, map);
			clccell = 0;
		}


		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//Ϊ�������,���Ͻ��Ҽ�ֱ���˳�
		{
			save_battle(fp, batinfo, map);
			exit(0);
		}

		if (rec_btn_fun(800, 10, 800 + 49, 10 + 34, 65370))//���ٱ���
		{
			if (msgbar("ȷ��", "ȡ��", "����浵��ȷ����", ""))
			{
				fp = fopen(filename, "rb+");
				seek_savinfo(fp, save_num, 0, 0);
				save_battle(fp, batinfo, map);
				fclose(fp);
			}
			Clrmous();
			Map_partial(262, 218, 262 + 500, 219 + 230);
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
				return MAINMENU;
			}
			else
			{
				Clrmous();
				Map_partial(262, 218, 262 + 500, 219 + 230);
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

	nextr_button(65370);
	attack_button("����", CANT_co);
	stay_button("פ��", CANT_co);
	move_button(CANT_co);
	del_button(CANT_co);

	//ѡ��˵�
	save_btn(65370);
	exit_btn(65370);
	option_btn(65370);
}
/*����һ�������ϵı��ַ���*/
void draw_cell(DBL_POS pos, MAP map)
{

	int kind, side, geo;
	POS offpos;

	offpos = D2O(pos);

	kind = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;
	geo = map[offpos.y][offpos.x].geo;
	pos = center_xy(pos.x, pos.y);
	//��ֹ��ʼ������ʱ��Ϊkind������0�Ѵ�Ӫ����Դ����
	switch (geo)
	{
	case BASE:
		Map_partial(pos.x - 18, pos.y - 18, pos.x + 18, pos.y + 23);
	case SORC:
	case HSORC:
	case OUT_MAP:
		return;
	default:
		break;
	}
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
		show_error("������Ϣ�ļ���ʧ", 1);
		fclose(fp);
		return info;
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

//��ʾ��ǰλ�õ�����Ϣ
void disp_geo_info(CELL cell)
{
	char text[20], text1[20], text2[20];
	sprintf(text, "�����ж��� %d", move_cost(cell.geo));
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
		sprintf(text1, "����ֵ %d", cell.health);
		sprintf(text2, "�ȼ� %d", cell.kind);
		Outtext(20, 20, "��Ӫ", 32, 48, 0);
		Outtext(20, 70, text1, 16, 20, 0);
		Outtext(20, 100, text2, 16, 20, 0);
		return;
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
}

/********��ʾ��ǰ���λ�ñ�����Ϣ*********/
Arminfo disp_arm_info(CELL cell)
{
	Arminfo info;
	char buffer[20] = "\0";
	info = search_info(cell.kind);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	if (cell.geo == BASE || cell.geo == SORC || cell.geo == HSORC)
		return info;

	switch (cell.kind)
	{
	case BUILDER:
		Outtext(30, 100, "����", 24, 35, 0);
		break;
	case INFANTRY:
		Outtext(30, 100, "����", 24, 35, 0);
		break;
	case ARTILLERY:
		Outtext(30, 100, "�ڱ�", 24, 35, 0);
		break;
	case TANK:
		Outtext(30, 100, "̹��", 24, 35, 0);
		break;
	case SUPER:
		Outtext(30, 100, "������", 24, 30, 0);
		break;
	default:
		return info;
	}

	itoa(cell.health, buffer, 10);
	Outtextxx(15, 130, 75, "����ֵ", 16, 0);
	Outtext(85, 130, buffer, 16, 16, 0);
	itoa(info.attack, buffer, 10);
	Outtextxx(15, 150, 75, "������", 16, 0);
	Outtext(85, 150, buffer, 16, 16, 0);
	itoa(info.move, buffer, 10);
	Outtextxx(15, 170, 75, "�ж���", 16, 0);
	Outtext(85, 170, buffer, 16, 16, 0);
	itoa(info.distance, buffer, 10);
	Outtextxx(15,190, 75, "���", 16, 0);
	Outtext(85, 190, buffer, 16, 16, 0);
	return info;
}

void disp_bat_info(Battleinfo batinfo)
{
	char buffer[20];
	Map_partial(185, 700, 262, 732);
	Map_partial(740, 670, 980, 742);
	sprintf(buffer, "�غ��� %d", (batinfo.round+1)/2);
	Outtext(740, 710, buffer, 32, 40, 0);
	if ((batinfo.round + 1)% 2)
	{
		sprintf(buffer, "��Դ�� %d", batinfo.r_source);
		Outtext(740, 670, "����ж�", 32, 40, 0);
		Outtext(20, 700, buffer, 32, 40, 0);
	}
	else
	{
		sprintf(buffer, "��Դ�� %d", batinfo.b_source);
		Outtext(740, 670, "�����ж�", 32, 40, 0);
		Outtext(20, 700, buffer, 32, 40, 0);
	}
}

void act_buttons(COLO co)
{
	attack_button("����", co.atk);
	stay_button("פ��", co.stay);
	move_button(co.mov);
	del_button(co.del);
}
void change_co(COLO* co, int kind, int flag)
{
	if (flag)
	{
		co->atk = CANT_co;
		co->del = CANT_co;
		co->mov = CANT_co;
		co->stay = CANT_co;
	}
	else 
	{
		co->atk = OK_co;
		co->del = OK_co;
		co->mov = OK_co;
		co->stay = OK_co;
		if (kind == BUILDER)
		{
			co->atk = CANT_co;
		}
	}
}