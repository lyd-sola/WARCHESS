/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: mainmenu.c
author: ����ͩ
version: 1.0
Description: ���˵�
date:2020/9/9

������־

����Ŀ¼
1.mainmenu:		���˵�����
2.mmenu_draw:	�������˵�����
******************************************************************/
#include "common.h"

int mainmenu(char *user, short *save_num, short *mode)
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
				return BATTLE;
			}
			*save_num = get_savenum(fp);
			*mode = get_savmode(fp, *save_num);
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
				return BATTLE;
			}
			*save_num = get_savenum(fp);
			*mode = get_savmode(fp, *save_num);
			return BATTLE;
		}
		if (Sharp_button(225 + 220, "�ػ�����", "��ȡ�浵", 60361, 65535))
		{
			if (!savpage(user, save_num, mode))
			{
				mmenu_draw(user);
				continue;
			}
			return BATTLE;
		}
		Sharp_button(225 + 330, "��սָ��", "����˵��", 60361, 65535);
		if (Sharp_button(225 + 440, "�����ձ�", "ע���˺�", 60361, 65535))
		{
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
	Outtextxx(120, 360, 260, "ͨ��֤: ", 32, 0);
	Outtext(260, 360, user, 32, 32, 0);
	Outtextxx(120, 405, 260, "�Ծ���: ", 32, 0);

	Button(225, "�����Ծ�",60361, 65535);
	Button(225+110, "��ս��е", 60361, 65535);
	Button(225+220, "�ػ�����", 60361, 65535);
	Button(225+330, "��սָ��", 60361, 65535);
	Button(225+440, "�����ձ�", 60361, 65535);

	//Bar64k_radial(200 - 5, 500 - 20 - 5, 400, 500 + 40 + 16 + 5, 10000, 0);
	//Outtext(200 + 75, 500 - 20, "�浵1", 16, 19, 0);
	//Outtext(217, 500, "2020/10/03 09:58", 16, 10, 0);
	//Outtext(200, 500 + 20, "ģʽ�������Ծ�", 16, 19, 0);
	//Outtext(200, 500 + 40, "�غ���", 16, 19, 0);
	//Outtext(200 + 19 * 2 + 16, 500 + 40, ":10000", 16, 10, 0);

}