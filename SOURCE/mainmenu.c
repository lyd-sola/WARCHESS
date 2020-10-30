/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: mainmenu.c
author: ����ͩ�����Ƶ�
version: 1.0
Description: ���˵�
date:2020/9/9

������־
******************************************************************/
#include "common.h"

int mainmenu(char *user, int *save_num, int *mode)
{
	char s[25] = "SAVES//";
	FILE* fp;
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("δ�ҵ��û��浵�ļ�", 1);

	mmenu_draw(user); //�������˵�����	

	while(1)
	{
		Newxy();
		if (Sharp_button(225, "�����Ծ�", "˫�˶�ս", 60361, 65535))
		{
			if (savefile_creat(fp, 0) == 1)
			{
				if (msgbar("ȷ��", "ȡ��", "�浵���������ٴ���ʧ��", "������ת���浵�������"))
				{
					if (!savpage(user, save_num, mode))
					{
						mmenu_draw(user);
						continue;
					}
				}
				else
				{
					mmenu_draw(user);
					continue;
				}
				fclose(fp);
				return BATTLE;
			}
			*save_num = get_savenum(fp);
			*mode = get_savmode(fp, *save_num);
			fclose(fp);
			return BATTLE;
		}
		if (Sharp_button(225 + 110, "��ս��е", "����ģʽ", 60361, 65535))
		{
			if (savefile_creat(fp, 1) == 1)
			{
				if (msgbar("ȷ��", "ȡ��", "�浵���������ٴ���ʧ��", "������ת���浵�������"))
				{
					if (!savpage(user, save_num, mode))
					{
						mmenu_draw(user);
						continue;
					}
				}
				else
				{
					mmenu_draw(user);
					continue;
				}
				fclose(fp);
				return BATTLE;
			}
			*save_num = get_savenum(fp);
			*mode = get_savmode(fp, *save_num);
			fclose(fp);
			return BATTLE;
		}
		if (Sharp_button(225 + 220, "�ػ�����", "��ȡ�浵", 60361, 65535))
		{
			if (!savpage(user, save_num, mode))
			{
				mmenu_draw(user);
				continue;
			}
			fclose(fp);
			return BATTLE;
		}
		if (Sharp_button(225 + 330, "��սָ��", "����˵��", 60361, 65535))
		{
			help_cartoon();
			return MAINMENU;
		}
		if (Sharp_button(225 + 440, "�����ձ�", "ע���˺�", 60361, 65535))
		{
			fclose(fp);
			return HOMEPAGE;
		}
	}
}

void mmenu_draw(char *user)//�˵��������Ծ���˫�˶�ս�����Ծ���е������ģʽ�����ػ���������ȡ�浵������սָ��������˵�����������ձ���ע���˺ţ�
{
	Clrmous();//�������״̬����ֹ����
	Bar64k_radial(0, 0, 1024, 768, 65370, 0);
	banner(512 - 280, 20, 560);
	Outtextxx(512 - 280 + 10, 40, 512 - 280 + 560, "��ӭ������ָ�ӹ٣�", 48, 65184);

	file_draw(100, 200, 500, 700);
	photo(120, 220, 220, 340);

	Outtext(230, 235, "ָ�ӹٵ���", 32, 40, 0);
	file_text(user, "��У", 3, 114514, 2, "2020/10/31");
	/*Outtextxx(120, 360, 260, "ͨ��֤: ", 32, 0);
	Outtext(260, 360, user, 32, 32, 0);
	Outtextxx(130, 360+55, 260, "����: ", 32, 0);
	Outtextxx(120, 360+55*2, 260, "�Ծ���: ", 32, 0);
	Outtextxx(120, 360+55*3, 260, "�غ���: ", 32, 0);
	Outtextxx(120, 360+55*4, 260, "ʤ����: ", 32, 0);
	Outtextxx(120, 360+55*5, 260, "ע����: ", 32, 0);*/
	Button(225, "�����Ծ�",60361, 65535);
	Button(225+110, "��ս��е", 60361, 65535);
	Button(225+220, "�ػ�����", 60361, 65535);
	Button(225+330, "��սָ��", 60361, 65535);
	Button(225+440, "�����ձ�", 60361, 65535);
}

void file_text(char *user, char *rank, int Count, long int Round, int Win, char *date)
{
	char count[20], round[20], win[20];
	sprintf(count, "%d", Count);
	sprintf(round, "%ld", Round);
	sprintf(win, "%d", Win);
	Outtextxx(125, 360, 260, "ͨ��֤: ", 32, 0);
	Outtext(265, 360, user, 32, 32, 0);
	Outtextxx(130, 360 + 55, 260, "����: ", 32, 0);
	Outtext(265, 360 + 55, rank, 32, 38, 0);
	Outtextxx(125, 360 + 55 * 2, 260, "�Ծ���: ", 32, 0);
	Outtext(265, 360 + 55 * 2, count, 32, 32, 0);
	Outtextxx(125, 360 + 55 * 3, 260, "�غ���: ", 32, 0);
	Outtext(265, 360 + 55 * 3, round, 32, 32, 0);
	Outtextxx(125, 360 + 55 * 4, 260, "ʤ����: ", 32, 0);
	Outtext(265, 360 + 55 * 4, win, 32, 32, 0);
	Outtextxx(125, 360 + 55 * 5, 260, "ע����: ", 32, 0);
	Outtext(265, 360 + 55 * 5, date, 32, 20, 0);

	Bar64k(122, 362 + 32, 478, 364 + 32, 33808);
	Bar64k(122, 362 + 32 + 55, 478, 364 + 32 + 55, 33808);
	Bar64k(122, 362 + 32 + 55 * 2, 478, 364 + 32 + 55 * 2, 33808);
	Bar64k(122, 362 + 32 + 55 * 3, 478, 364 + 32 + 55 * 3, 33808);
	Bar64k(122, 362 + 32 + 55 * 4, 478, 364 + 32 + 55 * 4, 33808);
	Bar64k(122, 362 + 32 + 55 * 5, 478, 364 + 32 + 55 * 5, 33808);	
}