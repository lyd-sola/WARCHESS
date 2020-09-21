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
	CELL map[13][13];
	CELL cl;
	Battleinfo batinfo;
	int clx, cly;
	char s[20] = "SAVES//";
	FILE* fp;
	
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
	{
		show_error("δ�ҵ��û��浵�ļ�", 1);
	}

	Battle_init(fp, &batinfo, map, save_num);
	Clrmous();
	battle_draw();
	while(1)
	{
		Newxy();
		if (Light_button(16, "ע���˺�", "ע���˺�", 60361, 65535))
		{
			return MAINMENU;
		}
		//if(mouse_press(69, 23, 959, 619) == MOUSE_IN_L)
		//{
		//	xy_tran((float)MouseX, (float)MouseY, &clx, &cly);

		//	cl = map[(clx + 1) / 2 - 1][cly - 1];
		//}
	}
}
//����ս�����溯��
void battle_draw()
{
	Putbmp64k(0, 0, "BMP//map.bmp");
	Button(16, "�˳�ս��", 60361, 65535);
}
/**********************************************************
Function��		Battle_init
Description��	ս����ʼ����������ȡ�浵
Input:			fp�û��浵�ļ�ָ�룬������һ���Ͷ�
Author��		���Ƶ�
**********************************************************/
void Battle_init(FILE* fp, Battleinfo *info, CELL map[][13], short save_num)
{
	int i, j;
	seek_savinfo(fp, save_num, 0, 0);
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

void save_battle(FILE *fp, short save_num, Battleinfo *batinfo, CELL map[][13])
{
	unsigned t[3];
	time_t rawtime;
	struct tm* info;
	int i, j;

	seek_savinfo(fp, save_num, 0, 0);

	fseek(fp, 1, SEEK_CUR);//�����浵��
	//��ǰʱ������
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//��
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//����
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//ʱ��
	fwrite(t, 2, 3, fp);
	//�غ���Ϣ����
	fwrite( &((*batinfo).round), 2, 1, fp );
	fwrite( &((*batinfo).b_source), 2, 1, fp );
	fwrite( &((*batinfo).r_source), 2, 1, fp );
	//�����ͼ��Ϣ
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fwrite(map[i] + j, 2, 1, fp);
		}
	}
}