/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
File_name: battle.c
Author: ���Ƶѡ�����ͩ
Version: 1.0
Description: ս������
Date:

������־
	10.25ǰ	���ֹ���ʵ��beta��ȱ��
	10.25	1.0�汾
			ʵ�ְ�ť��ɫʱ�޷�������������msg���⣬����battle����
����Ŀ¼
******************************************************************/

#include "common.h"
//ս������������
int battle(char *user, short save_num, short mode)
{
	CELL map[13][13];//��ͼ
	DBL_POS pos;
	Battleinfo batinfo;//��ս��Ϣ
	Arminfo arminfo;//������Ϣ�ݴ�
	int clccell = 0;//�������ͼ�ϵ�һ������
	int flag, msgflag = 0;
	int side;//��ǵ�ǰ��Ӫ
	FILE* fp;
	COLO co;
	load_battle(user, save_num, &batinfo, map, &fp);//��ȡ�浵
	battle_draw();//�������
	act_buttons(&co, 0, 1, 0);//��Ϊ��ť
	disp_bat_info(batinfo);//��ս��Ϣ���غ���Դ��
	side = (batinfo.round - 1) % 2;
	initdraw(map);//��λ����
	next_r_banner(side);//��banner���Դ�delay
	Map_partial(512 - 240 - 75, 300, 512 + 240 + 75, 300 + 125);
	initdraw(map);//��λ����
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
			nxt_round(map, &batinfo, &side);
			disp_bat_info(batinfo);
			next_r_banner(side);//��banner���Դ�delay
			Map_partial(512-240-75, 300, 512+240+75, 300+125);
			initdraw(map);//��ԭ
		}
		first_click(map, &pos, &clccell, &msgflag, &arminfo, &batinfo, &co);//�����ͼ��һ����
		if (clccell)//������Ϊ��ť
		{
			act_btn(map, &co, &clccell, pos, &arminfo);
			if (!clccell)
			{
				act_buttons(&co, 0, 1, 0);
				msgflag = 0;
				delay(300);
			}
		}
		if ((flag = opt_btn(fp, save_num, map, &batinfo)) != BATTLE)//���Ͻ�ѡ��˵���
		{
			return flag;
		}
		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//Ϊ�������,���Ͻ��Ҽ�ֱ���˳�
		{
			fclose(fp);
			exit(0);
		}
	}
}
//����ս�����溯��
void battle_draw()
{
	Clrmous();
	Map_partial(0, 0, 1024, 768);
	//Putbmp64k(0, 0, "BMP//map.bmp");

	Bar64k(0, 0, 204, 100, 65370);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	nextr_button(65370);

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
		//Map_partial(pos.x - 18, pos.y - 18, pos.x + 18, pos.y + 23);
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
	char text[20];	Bar64k(0, 0, 204, 100, 65370);
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
		sprintf(text, "����ֵ %d", cell.health);
		Outtext(20, 70, text, 16, 20, 0);
		sprintf(text, "�ȼ� %d", cell.kind);
		Outtext(20, 100, text, 16, 20, 0);
		if (cell.kind < 3)
		{
			sprintf(text, "�������� %d", cell.kind == 1 ? 10 : 50);
			Outtext(20, 130, text, 16, 20, 0);
		}
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
	sprintf(text, "�����ж��� %d", move_cost(cell.geo));
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
	int x = 25;
	Map_partial(740+x, 670, 980+x, 700);//��ԭ�ж���
	Map_partial(20 + 4 * 32, 715, 315+x, 747);//��ԭ��Դ��
	if (batinfo.round % 2)//�غ�����ʾ
	{
		Map_partial(740 + x, 700, 980 + x, 742);//��ԭ�غ���
		sprintf(buffer, "�غ���");
		Outtext(740 + x, 710, buffer, 32, 40, 0);
		sprintf(buffer, "%d", (batinfo.round + 1) / 2);
		Outtext(740+32*4 + x, 710, buffer, 32, 32, 0);
	}
	Outtext(20, 715, "��Դ��", 32, 40, 0);
	if ((batinfo.round + 1)% 2)//��Դ��ʾ
	{
		sprintf(buffer, "%d", batinfo.r_source);
		Outtext(740+x, 670, "����ж�", 32, 40, 0);
		Outtext(20+4*32, 715, buffer, 32, 40, 0);
	}
	else
	{
		sprintf(buffer, "%d", batinfo.b_source);
		Outtext(740+x, 670, "�����ж�", 32, 40, 0);
		Outtext(20+4*32, 715, buffer, 32, 40, 0);
	}
}

/*������Ϊ��ť*/
void act_buttons(COLO *co, int kind, int flag, int is_same_side)
{
	if (flag || !is_same_side)
	{
		co->atk = CANT_co;
		co->del = CANT_co;
		co->mov = CANT_co;
		co->stay = CANT_co;
	}
	else
	{
		co->del = OK_co;
		co->mov = OK_co;
		co->stay = OK_co;
		co->atk = OK_co;
	}
	if (kind == BUILDER)
	{
		attack_button("����", co->atk);
	}
	else
	{
		attack_button("����", co->atk);
	}
	stay_button("פ��", co->stay);
	move_button(co->mov);
	del_button(co->del);
}
/*��ť���Ϻ�������ɫ״̬���ܵ��*/
void act_btn(MAP map, COLO* co, int* clccell, DBL_POS pos, Arminfo* arminfo)
{
	if (co->mov == (int)OK_co)
	{
		if (move_btn_fun(co->mov, 65340))//�ƶ�
		{
			move(pos, map, arminfo->move);
			*clccell = 0;
			move_button(co->mov);
			delay(50);//���delay����Ҫ�����ڸ��û�ʱ��̧����������move�ж��������ɾ����
		}
	}
	if (co->stay == (int)OK_co)
	{
		if (stay_btn_fun("פ��", co->stay, 65340))//פ��
		{
			stay(pos, map);
			*clccell = 0;
		}
	}
	if (co->atk == (int)OK_co)
	{
		if (atk_btn_fun("����", co->atk, 65340))//����
		{
			attack(pos, map);
			*clccell = 0;
		}
	}
	if (co->del == (int)OK_co)
	{
		if (del_btn_fun(co->del, 65340))//ɾ��
		{
			delarm(pos, map);
			*clccell = 0;
		}
	}
}
/*�����ͼ��һ�㣬��ı�clccell״̬����¼pos�����ô�Ӫ��غ���*/
void first_click(MAP map, DBL_POS *pos, int *clccell, int *msgflag, Arminfo *arminfo, Battleinfo *batinfo, COLO *co)
{
	int flag, side = (batinfo->round - 1) % 2;
	DBL_POS ptmp;
	OFF_POS opos;
	if ((flag = clcmap(&ptmp, map)) != 0)
	{
		opos = D2O(ptmp);
		*arminfo = disp_arm_info(map[opos.y][opos.x]);//��ʾ��Ϣ
		disp_geo_info(map[opos.y][opos.x]);
		if (map[opos.y][opos.x].side != side && map[opos.y][opos.x].kind != NOARMY) //����з���λ
		{
			*clccell = 0;
			show_msg("��Ϊ�з���λ�����ɲ�����", "");
			delay(msg_sec);
			*msgflag = 0;
			return;
		}
		if (map[opos.y][opos.x].flag)
		{
			*clccell = 0;
			show_msg("�õ�λ���ж���", "��һ�غ�����������");
			delay(msg_sec);
			*msgflag = 0;
			return;
		}
		switch (flag)
		{
		case 1:		//���
			*clccell = 0;
			show_msg("������Ϊ��", "");
			act_buttons(co, 0, 1, 0);
			break;
		case 2:		//���������λ
			*pos = ptmp;
			*clccell = 1;
			show_msg("��ѡ��һ����λ", "��ѡ����Ϊ");
			act_buttons(co, map[opos.y][opos.x].kind, map[opos.y][opos.x].flag,
				map[opos.y][opos.x].side == side);
			break;
		case 3:		//�����Ӫ
			*clccell = 0;
			show_msg("�ٴε�ѡ����������", "�Ҽ�ȡ��");
			delay(50);
			base_func(map, side ? &(batinfo->r_source) : &(batinfo->b_source), side);
			disp_bat_info(*batinfo);
			act_buttons(co, 0, 1, 0);
			*msgflag = 0;
			break;
		}
	}
}
/*���Ͻ�ѡ��˵���*/
int opt_btn(FILE *fp, int save_num, MAP map, Battleinfo *batinfo)
{
	int flag, side = (batinfo->round - 1) % 2;
	char* s, msg[30];
	if (rec_btn_fun(800, 10, 800 + 49, 10 + 34, 65370))//���ٱ���
	{
		if (msgbar("ȷ��", "ȡ��", "����浵��ȷ����?", ""))
		{
			seek_savinfo(fp, save_num, 0, 0);
			save_battle(fp, *batinfo, map);
		}
		Clrmous();
		Map_partial(262, 218, 262 + 500, 219 + 230);
		initdraw(map);
	}
	if (rec_btn_fun(880, 10, 880 + 49, 44, 65370))//ѡ��˵�
	{
		draw_opts();
		flag = opts_fun(side);
		switch (flag)
		{
		case BATTLE://�ر�ѡ��
			return BATTLE;
		case EXIT://���沢�˳�
			if (msgbar("ȷ��", "����", "��������ս�����˳�����", "ȷ����?"))
			{
				seek_savinfo(fp, save_num, 0, 0);
				save_battle(fp, *batinfo, map);
				fclose(fp);
				exit(0);
			}
			else
			{
				Map_partial(262, 218, 262 + 500, 219 + 230);
				Map_partial(837, 46, 976, 88 + 41 * 2);
				initdraw(map);
				return BATTLE;
			}
		case HOMEPAGE://ע��
			if (msgbar("ȷ��", "����", "����ע��", "ȷ����?"))
			{
				return HOMEPAGE;
			}
			else
			{
				Map_partial(262, 218, 262 + 500, 219 + 230);
				Map_partial(837, 46, 976, 88 + 41 * 2);
				initdraw(map);
				return BATTLE;
			}
		case 444://����
			s = side ? "��" : "��";
			sprintf(msg, "%s����������", s);
			if (msgbar("����", "���", msg, "��Ĳ��ټ��һ����?"))
			{
				if(msgbar("�ǵ�", "����", msg, "����Ǳ��˲�����"))
					side ? (map[3][10].health = 0) : (map[9][1].health = 0);
			}
			Map_partial(262, 218, 262 + 500, 219 + 230);
			Map_partial(837, 46, 976, 88 + 41 * 2);
			initdraw(map);
			return BATTLE;
		}
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
			Map_partial(262, 218, 262 + 500, 219 + 230);
			initdraw(map);
		}
	}
	return BATTLE;
}