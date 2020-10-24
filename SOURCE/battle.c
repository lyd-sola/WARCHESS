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
	int side = 0;//��ǵ�ǰ��Ӫ
	char filename[25] = "SAVES//";
	FILE* fp;

	DBL_POS test;
	
	strcat(filename, user);
	if ((fp = fopen(filename, "rb+")) == NULL)
		show_error("δ�ҵ��û��浵�ļ�", 1);
	seek_savinfo(fp, save_num, 0, 0);
	Battle_init(fp, &batinfo, map);
	
	battle_draw();
	//map[6][6].side = 1;
	//map[6][6].kind = BUILDER;
	//map[6][5].side = 2;
	//map[6][5].kind = INFANTRY;
	initdraw(map);

	//��Ӫ��Ϣ�ĳ�ʼ����Ӧ�����ʼ���浵���棿
	map[3][10].side = 0;
	map[9][1].side = 1;
	map[3][10].kind = 1;
	map[9][1].kind = 1;
	batinfo.b_source = 50;

	while(1)
	{
		Newxy();
		if (nxt_btn_fun(65370, 65340))
		{
			show_msg("������һ�غ�", "");
			nxt_round(map, &batinfo, &side);
			delay(1000);
		}
		if ( (flag = clcmap(&ptmp, map)) != 0 )
		{
			msgflag = 1;
			opos = D2O(ptmp);
			if (map[opos.y][opos.x].side != side && map[opos.y][opos.x].kind != NOARMY)
			{
				show_msg("��Ϊ�з���λ�����ɲ�����", "");
				disp_geo_info(map[opos.y][opos.x]);
				disp_arm_info(map[opos.y][opos.x]);
				continue;
			}
			if (flag == 3)
			{
				clccell = 0;
				disp_arm_info(map[opos.y][opos.x]); 
				disp_geo_info(map[opos.y][opos.x]);
				show_msg("�����ҷ���Ӫ��", "�ٴε�ѡ��������");
				delay(50);
				base_func(map, side ? (&batinfo.r_source) : (&batinfo.b_source), side);
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
/*����һ�������ϵı��ַ���*/
void draw_cell(DBL_POS pos, MAP map)
{

	int kind, side, geo;
	POS offpos;

	offpos = D2O(pos);

	kind = map[offpos.y][offpos.x].kind;
	side = map[offpos.y][offpos.x].side;
	geo = map[offpos.y][offpos.x].side;
	pos = center_xy(pos.x, pos.y);
	//��ֹ��ʼ������ʱ��Ϊkind������0�Ѵ�Ӫ����Դ����
	switch (geo)
	{
	case BASE:
		return;
	case SORC:
		return;
	case HSORC:
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
	char text[20] = "�����ж���", text1[20] = "����ֵ ", text2[20] = "�ȼ� ";
	char buffer[20], buffer1[20], buffer2[20];
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
		itoa(cell.health, buffer1, 10);
		strcat(text1, buffer1);
		itoa(cell.kind, buffer2, 10);
		strcat(text2, buffer2);
		Outtext(20, 20, "��Ӫ", 32, 48, 0);
		Outtext(20, 70, text1, 16, 20, 0);
		Outtext(20, 100, text2, 16, 20, 0);
		lastcell1 = cell;
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
	lastcell1 = cell;
}

/********��ʾ��ǰ���λ�ñ�����Ϣ*********/
Arminfo disp_arm_info(CELL cell)
{
	Arminfo info;
	char buffer[20] = "\0";
	//static CELL lastcell2;
	//if (lastcell2.kind == cell.kind && lastcell2.health == cell.health)
	//	return;
	info = search_info(cell.kind);
	Filltriangle(0, 100, 0, 350, 204, 100, 65370);
	//��Ϊ�浵�еı��������洢��Ϣ�ˣ�������Ҫ����
	if (cell.geo == BASE || cell.geo == SORC || cell.geo == HSORC)
		return;

	switch (cell.kind)
	{
	case BUILDER:
		Outtextxx(15, 120, 110, "����  ����", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(15, 140, 75, "����ֵ", 16, 0);
		Outtext(85, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(15, 160, 75, "������", 16, 0);
		Outtext(85, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(15, 180, 75, "�ж���", 16, 0);
		Outtext(85, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(15, 200, 75, "���", 16, 0);
		Outtext(85, 200, buffer, 16, 16, 0);
		break;

	case INFANTRY:
		Outtextxx(15, 120, 110, "����  ����", 16, 0);
		itoa(cell.health, buffer, 10);
		Outtextxx(15, 140, 75, "����ֵ", 16, 0);
		Outtext(85, 140, buffer, 16, 16, 0);
		itoa(info.attack, buffer, 10);
		Outtextxx(15, 160, 75, "������", 16, 0);
		Outtext(85, 160, buffer, 16, 16, 0);
		itoa(info.move, buffer, 10);
		Outtextxx(15, 180, 75, "�ж���", 16, 0);
		Outtext(85, 180, buffer, 16, 16, 0);
		itoa(info.distance, buffer, 10);
		Outtextxx(15, 200, 75, "���", 16, 0);
		Outtext(85, 200, buffer, 16, 16, 0);
		break;
	default:
		break;
	}
	//lastcell2 = cell;
	return info;
}

//��Ӫ���ܺ���
void base_func(MAP map, int *source, int side)
{
	POS pos,dpos;
	pos.x = 745;
	pos.y = 705;
	icon(pos, side, BUILDER);
	pos.x = 745+65;
	icon(pos, side, INFANTRY);
	pos.x = 745+65*2;
	icon(pos, side, ARTILLERY);
	pos.x = 745+65*3;
	icon(pos, side, TANK);
	pos.x = 745+65*4;
	icon(pos, side, SUPER);
	while (1)
	{
		Newxy();
		//�ٴε����Ӫ�Դ�Ӫ��������
		if (clcmap(&dpos, map) == 3 && map[D2O(dpos).y][D2O(dpos).x].side == side) //��ֹ����Դ������������Ͷ����Ϊ�����Ľ�
		{
			levelup(dpos, map, source);
			Map_partial(745-18, 705-18, 745+65*4+18, 705+23, FBMP);
			return;
		}
		//������½Ǳ���ͼ��������ʾ��Ϣ���ٴε���������
		if (mouse_press(745-18, 705-18, 745+65*4+18, 705+23) == 1)
		{
			buildarm(map, source, side);
			Clrmous();
			Map_partial(745-18, 705-18, 745+65*4+18, 705+23, FBMP);
			return;
		}

		if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)	//�Ҽ�ȡ��
		{
			Map_partial(745-18, 705-18, 745+65*4+18, 705+23, FBMP);
			show_msg("ȡ������", "");
			delay(500);
			return;
		}
	}
}

//��Ӫ��������
void levelup(DBL_POS dpos, MAP map, int *source)
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
void buildarm(MAP map, int *source, int side)
{
	int armkind = 0;
	Arminfo arminfo;
	POS pos, center, dpos, opos;
	opos.x = side ? 1 : 10;
	opos.y = side ? 9 : 3;
	if (mouse_press(745 - 18, 705 - 18, 745 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ�й���
	{
		armkind = BUILDER; //Ϊ�ڶ��ε�ѡȷ������ֵ
		show_msg("��������ۣ�2", "�ٴε�ѡȷ������");
		delay(100); //ʹ�û���ʱ�佫���̧����
	}
	if (mouse_press(745 + 65 - 18, 705 - 18, 745 + 65 + 18, 705 + 23) == MOUSE_IN_L )//��һ�ε�ѡѡ�в���
	{
		armkind = INFANTRY;
		show_msg("��������ۣ�1", "�ٴε�ѡȷ������");
		delay(100);
	}
	if (mouse_press(745 + 65 * 2 - 18, 705 - 18, 745 + 65 * 2 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ���ڱ�
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
	if (mouse_press(745 + 65 * 3 - 18, 705 - 18, 745 + 65 * 3 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ��̹��
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
	if (mouse_press(745 + 65 * 4 - 18, 705 - 18, 745 + 65 * 4 + 18, 705 + 23) == MOUSE_IN_L) //��һ�ε�ѡѡ�г�����
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
	while (1)
	{
		Newxy();
		if (mouse_press(745+65*(armkind-1)-18, 705-18, 745+65*(armkind-1)+18, 705+23) == MOUSE_IN_L)
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
				if (map[10][2].kind != 0) //�ж���ɫ���������Ƿ�ռ��
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
					center = center_xy(5, 11);
					icon(center, side, armkind);
				}
			}
			else //��ɫ��
			{
				if (map[2][10].kind != 0) //�жϺ췽�������Ƿ�ռ��
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
					center = center_xy(21, 3);
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