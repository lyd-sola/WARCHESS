/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: savepage.c
author: ���Ƶ�
version: 1.0
Description:�浵���棡 
	����˵�Ƿǳ�������
	д��һ�죬debug�˰��죨����������������غ�����
	�ҵĺ������ڳ�����QAQ
	д�������ʱ��lyd�Ѿ�����������������
	��ʵ�����������Ժϳ�һ��
date:2020/10/4
������־
******************************************************************/

#include "common.h"
/*�浵����ҳ�棬����1���Խ����ս���棬����0�ص�ԭ����*/
int savpage(char *user, int* save_num, int* mode)
{
	int flag = 1;//ģʽ��1Ϊ������0Ϊ����
	int tot = 0;
	char s[25] = "SAVES//";
	FILE* fp;

	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("δ�ҵ��û��浵�ļ�", 1);
	savpage_draw(fp);
	tot = get_savenum(fp);
	while (1)
	{
		Newxy();

		if (mouse_press(197 + 630 - 32, 98, 197 + 630, 98 + 32) == MOUSE_IN_L)
		{
			fclose(fp);
			return 0;
		}
		if (rec_btn_fun(236, 511, 373, 561, 65535))//�����ȡ�浵
		{
			flag = 1;
			Clrmous();
			savpage_btns(1);
		}
		if (rec_btn_fun(443, 511, 580, 561, 65535))//����½��浵
		{
			if (tot >= 6)
			{
				if (msgbar("ȷ��", "ȡ��", "�浵����", "�Ƿ��������ģʽ��"))
				{
					flag = 0;
					savpage_draw(fp);
					savpage_btns(3);
				}
				else
				{
					savpage_draw(fp);
				}
			}
			else 
			{
				if (savefile_creat(fp, msgbar("����", "˫��", "��ѡ��ģʽ", "")))
				{
					show_error("�浵����ʧ�ܣ�ԭ����", 0);
				}
				tot++;
				savpage_draw(fp);
			}
		}
		if (rec_btn_fun(650, 511, 787, 561, 65535))
		{
			flag = 0;
			Clrmous();
			savpage_btns(3);
		}//������ô浵

		if (save1(fp, &flag, tot, mode, save_num) || save2(fp, &flag, tot, mode, save_num)
			|| save3(fp, &flag, tot, mode, save_num) || save4(fp, &flag, tot, mode, save_num)
			|| save5(fp, &flag, tot, mode, save_num) || save6(fp, &flag, tot, mode, save_num))
		{
			return 1;
		}
	}
}
void savpage_btns(int i)
{
	int color[3] = { 65535 , 65535 , 65535 };
	color[i-1] = 65340;
	rect_button(236, 511, 373, 561, "��ȡ�浵", color[0]);
	rect_button(443, 511, 580, 561, "�½��浵", color[1]);
	rect_button(650, 511, 787, 561, "���ô浵", color[2]);
}
int save1(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(287 - 15, 182, 287 - 15 + 205, 182 + 86) == MOUSE_IN_L)//�浵1
	{
		if (*flag && tot >= 1)
		{
			if (msgbar("ȷ��", "ȡ��", "��ȡ�浵1", "ȷ����"))
			{
				*save_num = 1;
				*mode = get_savmode(fp, 1);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//����ģʽ
		else if (tot >= 1)
		{
			if (msgbar("ȷ��", "ȡ��", "�������Ǹô浵", "ȷ����"))
			{
				seek_savinfo(fp, 1, 0, 0);
				savefile_init(fp, msgbar("����", "˫��", "��ѡ��ģʽ", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//����ģʽ
	}
	return 0;
}
int save2(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(532 + 15, 182, 532 + 15 + 205, 182 + 86) == MOUSE_IN_L)//�浵2
	{
		if (*flag && tot >= 2)
		{
			if (msgbar("ȷ��", "ȡ��", "��ȡ�浵2", "ȷ����"))
			{
				*save_num = 2;
				*mode = get_savmode(fp, 2);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//����ģʽ
		else if (tot >= 2)
		{
			if (msgbar("ȷ��", "ȡ��", "�������Ǹô浵", "ȷ����"))
			{
				seek_savinfo(fp, 2, 0, 0);
				savefile_init(fp, msgbar("����", "˫��", "��ѡ��ģʽ", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//����ģʽ
	}
	return 0;
}
int save3(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(287 - 15, 290, 287 - 15 + 205, 290 + 86) == MOUSE_IN_L)//�浵3
	{
		if (*flag && tot >= 3)
		{
			if (msgbar("ȷ��", "ȡ��", "��ȡ�浵3", "ȷ����"))
			{
				*save_num = 3;
				*mode = get_savmode(fp, 3);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//����ģʽ
		else if (tot >= 3)
		{
			if (msgbar("ȷ��", "ȡ��", "�������Ǹô浵", "ȷ����"))
			{
				seek_savinfo(fp, 3, 0, 0);
				savefile_init(fp, msgbar("����", "˫��", "��ѡ��ģʽ", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//����ģʽ
	}
	return 0;
}
int save4(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(532 + 15, 290, 532 + 15 + 205, 290 + 86) == MOUSE_IN_L)//�浵4
	{
		if (*flag && tot >= 4)
		{
			if (msgbar("ȷ��", "ȡ��", "��ȡ�浵4", "ȷ����"))
			{
				*save_num = 4;
				*mode = get_savmode(fp, 4);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//����ģʽ
		else if (tot >= 4)
		{
			if (msgbar("ȷ��", "ȡ��", "�������Ǹô浵", "ȷ����"))
			{
				seek_savinfo(fp, 4, 0, 0);
				savefile_init(fp, msgbar("����", "˫��", "��ѡ��ģʽ", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//����ģʽ
	}
	return 0;
}
int save5(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(287 - 15, 398, 287 - 15 + 205, 398 + 86) == MOUSE_IN_L)//�浵5
	{
		if (*flag && tot >= 5)
		{
			if (msgbar("ȷ��", "ȡ��", "��ȡ�浵5", "ȷ����"))
			{
				*save_num = 5;
				*mode = get_savmode(fp, 5);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//����ģʽ
		else if (tot >= 5)
		{
			if (msgbar("ȷ��", "ȡ��", "�������Ǹô浵", "ȷ����"))
			{
				seek_savinfo(fp, 5, 0, 0);
				savefile_init(fp, msgbar("����", "˫��", "��ѡ��ģʽ", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//����ģʽ
	}
	return 0;
}
int save6(FILE *fp, int *flag, int tot, int *mode, int *save_num)
{
	if (mouse_press(532 + 15, 398, 532 + 15 + 205, 398 + 86) == MOUSE_IN_L)//�浵6
	{
		if (*flag && tot >= 6)
		{
			if (msgbar("ȷ��", "ȡ��", "��ȡ�浵6", "ȷ����"))
			{
				*save_num = 6;
				*mode = get_savmode(fp, 6);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//����ģʽ
		else if (tot >= 6)
		{
			if (msgbar("ȷ��", "ȡ��", "�������Ǹô浵", "ȷ����"))
			{
				seek_savinfo(fp, 6, 0, 0);
				savefile_init(fp, msgbar("����", "˫��", "��ѡ��ģʽ", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//����ģʽ
	}
	return 0;
}

void savpage_draw(FILE *fp)
{
	Clrmous();
	Bar64k_radial(197, 98, 197 + 630, 98 + 495, 65340, 0);
	Bar64k_radial(197+630-32, 98, 197 + 630, 98 + 32, 65535, 0);
	Outtext(197 + 630 - 32, 98, "��", 32, 32, 0);
	draw_saves(287 - 15, 398, 65535, fp, 5);
	draw_saves(532 + 15, 398, 65535, fp, 6);
	draw_saves(287 - 15, 290, 65535, fp, 3);
	draw_saves(532 + 15, 290, 65535, fp, 4);
	draw_saves(287 - 15, 182, 65535, fp, 1);
	draw_saves(532 + 15, 182, 65535, fp, 2);
	rect_button(236, 511, 373, 561, "��ȡ�浵", 65535);
	rect_button(443, 511, 580, 561, "�½��浵", 65535);
	rect_button(650, 511, 787, 561, "���ô浵", 65535);
	Outtextxx(367, 125, 512*2-367, "�浵����", 32, 0);
}

void draw_saves(int x, int y, int color, FILE* fp, int save_num)
{
	char Buffer[20];
	unsigned int t[3];//�� ���� ʱ��
	int mode, tot = 0;

	rectangle64k(x, y, x + 5 + 200, y + 25 + 40 + 16 + 5, 0);
	rectangle64k(x - 1, y - 1, x + 5 + 200 + 1, y + 25 + 40 + 16 + 5 + 1, 0);
	Bar64k_radial(x, y, x + 5 + 200, y + 25 + 40 + 16 + 5, color, 0);
	sprintf(Buffer, "%d", save_num);
	Outtext(x + 5 + 75, y + 25 - 20, "�浵", 16, 19, 0);
	Outtext(x + 5 + 75 + 19 + 16, y + 25 - 20, Buffer, 16, 19, 0);//�浵���

	//fseek(fp, 0, SEEK_SET);
	//fscanf(fp, "%d", &tot);
	//fread(&tot, 1, 1, fp);//��ȡ�浵����
	tot = get_savenum(fp);
	if (save_num > tot)
	{
		return;
	}//�޴浵������

	seek_savinfo(fp, save_num, 0, 0);
	//fread(&mode, 1, 1, fp);
	fscanf(fp, "%1d", &mode);

	fread(t, 2, 3, fp);
	sprintf(Buffer, "%4u/%02u/%02u %02u:%02u", t[0], t[1] / 100, t[1] % 100, t[2] / 100, t[2] % 100);
	Outtext(x + 5 + 17-1, y + 25, Buffer, 16, 10, 0);//ʱ��

	if (mode == 1)
	{
		Outtext(x + 5, y + 25 + 20, "ģʽ����ս��е", 16, 19, 0);
	}
	else
	{
		Outtext(x + 5, y + 25 + 20, "ģʽ�������Ծ�", 16, 19, 0);
	}//ģʽ

	fread(t, 2, 1, fp);
	sprintf(Buffer, "%u", (t[0]+1)/2);
	Outtext(x + 5, y + 25 + 40, "�غ���:", 16, 19, 0);
	Outtext(x + 5 + 19 * 3 + 16, y + 25 + 40, Buffer, 16, 10, 0);
}