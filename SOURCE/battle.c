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

int battle(char *user, short save_num)
{
	CELL map[13][13];
	Battle_init(user, map, save_num);
	Clrmous();
	battle_draw();
	while(1)
	{
		Newxy();
		if (Light_button(16, "ע���˺�", "ע���˺�", 60361, 65535))
		{
			return MAINMENU;
		}
	}
}

void battle_draw()
{
	Putbmp64k(0, 0, "BMP//map.bmp");
	Button(16, "�˳�ս��", 60361, 65535);
}

Battleinfo Battle_init(char *user, CELL map[][13], short save_num)
{
	FILE* fp;
	Battleinfo info;
	int i, j;
	char filename[25] = "SAVES//";
	strcat(filename, user);

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		show_error("δ�ҵ��û��浵�ļ�", 1);
	}
	seek_savinfo(fp, save_num, 0, 0);
	fseek(fp, 7, SEEK_CUR);//��������
	fread(&(info.round), 2, 1, fp);
	fread(&(info.b_source), 2, 1, fp);
	fread(&(info.r_source), 2, 1, fp);
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fread(map[i] + j, 2, 1, fp);
		}
	}//��ȡ��ͼ��Ϣ
	return info;
}