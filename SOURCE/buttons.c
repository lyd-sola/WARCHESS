/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: buttons.c
author: 
version: 
Description: ���а�ť�������ϣ�
date:

������־

����Ŀ¼
******************************************************************/

#include "common.h"

/**********************************************************
Function��		Button
Description��	��ť���ƺ���
Calls��			Line64k
Input:			y1��ť����y���꣬s��ť�Ϻ��֣��ĸ�����ѣ�
				color1��ɫ��color2����ɫ

Author��		���Ƶ�
ps �������Riddle Joker�����������µ�һ��
����Ų������˿������
**********************************************************/
void Button(int y1, char* s, int color, int color2)
{
	int x1 = 750, x2 = 1024;
	int height = 30, i;//bar��С274*30
	for (i = x2; i >= x1; i--)
	{
		Line64k(i, y1, i, y1 + height, color);
	}
	for (i = 1; i <= height; i++)
	{
		Line64k(x1 - i, y1, x1 - i, y1 + height - i, color);
	}//��������ɨ�裬���ٿ���Ч��
	for (i = 0; i <= height - 7; i++)
	{
		Putpixel64k(x1 - height + 10 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 11 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 12 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 13 + i, y1 + 4 + i, color2);
	}//����װ�λ��ƻ���
	Bar64k(x1 + 4, y1 + height - 3, x1 + 2 + 64, y1 + height - 5, color2);
	Outtext(1024 - 4 * 55 - 20, y1 - 16, s, 32, 55, 0);
}
/**********************************************************
Function��		Sharp_button
Description��	��ť��������������������ܣ��ǲ��Ǹøĸ����أ���������
				�����ҳ�溯��һ�������ж�����
				�����ÿһ����ť����Ҫ��һ��flag����
Calls��			Button
Input:			sԭ��ť���֣�s_change������ť����
				yo���߶�color1��ɫ��color2����ɫ�����밴ť���Ʋ���ֵ��
Output:			����1ʱ�����
Author��		���Ƶ�
**********************************************************/
int Sharp_button(int y0, char* s, char* s_change, int color, int color2)		/*������Ĭ�ϱ���ɫΪ��ɫ�������޸�*/
{
	if (MouseX >= MouseY - y0 + 720 && MouseY >= y0 && MouseY <= y0 + 30)//��������Ҳ���������ж�Ŷ
	{
		Clrmous();
		MouseS = 1;
		Bar64k(750, y0 - 16, 1000, y0 - 1, 65370);//�ڵ���ť�⺺��
		Button(y0, s_change, 64800, 65535);
		while (1)//��������������꣬��������������⣨����ʹ�ö��״̬��¼��������lydԭ�� XD
		{
			Newxy();
			if (MouseX >= MouseY - y0 + 720 && MouseY >= y0 && MouseY <= y0 + 30)
			{
				if (press == 1)
				{
					return 1;
				}//���������1
			}
			else
			{
				Clrmous();
				MouseS = 0;
				Bar64k(750, y0 - 16, 1000, y0 - 1, 65370);
				Button(y0, s, color, color2);
				return 0;
			}//�뿪����
		}
	}
	else
	{
		return 0;
	}
}

void attack_button(char* s, int color)
{
	int i;
	int x1 = 20, y1 = 407, len = 121;
	Line64k(x1, y1, x1, y1 + len - 3, 0);
	Line64k(x1 + 1, y1, x1 + 1, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3, len + x1 - 3, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3 - 1, len + x1 - 3 - 1, y1 + len - 3 - 1, 0);
	Line45(x1, y1, len + x1 - 3, y1 + len - 3, 0);
	Line45(x1 + 1, y1, len + x1 - 3 + 1, y1 + len - 3, 0);
	Line45(x1 + 2, y1, len + x1 - 3 + 2, y1 + len - 3, 0);
	for (i = 0; i <= 113; i++)
	{
		Line64k(x1 + 2 + i, y1 + 3 + i, x1 + 2 + i, y1 + len - 3 - 2, color);
	}
	Outtext(x1 + 8, y1 + 71, s, 32, 35, 0);
}

int atk_btn_fun(char* s, int color, int color_c)
{
	if (MouseX >= 20 && MouseY <= 524 && MouseY >= MouseX + 387)//��������Ҳ���������ж�Ŷ
	{
		Clrmous();
		MouseS = 1;
		attack_button(s, color_c);
		while (1)
		{
			Newxy();
			if (MouseX >= 20 && MouseY <= 524 && MouseY >= MouseX + 387)
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					attack_button(s, color);
					return 1;
				}//���������1
			}
			else
			{
				Clrmous();
				MouseS = 0;
				attack_button(s, color);
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

void stay_button(char* s, int color)
{
	int i;
	int len = 121, x1 = 141 + 3, y1 = 528 + 3;
	Line64k(x1, y1, x1, y1 + len - 3, 0);
	Line64k(x1 + 1, y1, x1 + 1, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3, len + x1 - 3, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3 - 1, len + x1 - 3 - 1, y1 + len - 3 - 1, 0);
	Line45(x1, y1, len + x1 - 3, y1 + len - 3, 0);
	Line45(x1 + 1, y1, len + x1 - 3 + 1, y1 + len - 3, 0);
	Line45(x1 + 2, y1, len + x1 - 3 + 2, y1 + len - 3, 0);
	for (i = 0; i <= 113; i++)
	{
		Line64k(x1 + 2 + i, y1 + 3 + i, x1 + 2 + i, y1 + len - 3 - 2, color);
	}
	Outtext(x1 + 8, y1 + 71, s, 32, 35, 0);
}//Ϊʲô��Ҫд���������أ���Ϊ���ü�����

int stay_btn_fun(char* s, int color, int color_c)
{
	if (MouseX >= 144 && MouseY <= 649 && MouseY >= MouseX + 387)//��������Ҳ���������ж�Ŷ
	{
		Clrmous();
		MouseS = 1;
		stay_button(s, color_c);
		while (1)
		{
			Newxy();
			if (MouseX >= 144 && MouseY <= 649 && MouseY >= MouseX + 387)
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					stay_button(s, color);
					return 1;
				}//���������1
			}
			else
			{
				Clrmous();
				MouseS = 0;
				stay_button(s, color);
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

void move_button(int color)
{
	rectangle64k(20, 528, 141, 649, 0);
	rectangle64k(20 + 1, 528 + 1, 141 - 1, 649 - 1, 0);
	Bar64k_radial(20 + 2, 528 + 2, 141 - 2, 649 - 2, color, 0);
	Outtext(20 + 27, 528 + 44, "�ƶ�", 32, 35, 0);
}

int move_btn_fun(int color, int color_c) //�ƶ�
{
	if (mouse_press(20+2, 528+2, 141-2, 649-2) == MOUSE_IN)
	{
		Clrmous();
		MouseS = 1;
		move_button(color_c);
		while (1)
		{
			Newxy();
			if (Mouse_above(20+2, 528+2, 141-2, 649-2))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					move_button(color);
					return 1;
					//���������1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				move_button(color);
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

void del_button(int color)
{
	rectangle64k(20, 649 + 3, 262, 649 + 3 + 45, 0);
	rectangle64k(20 + 1, 649 + 4, 262 - 1, 649 + 2 + 45, 0);
	Bar64k_radial(20 + 2, 649 + 5, 262 - 2, 649 + 46, color, 0);
	Outtext(85, 649 + 9, "ɾ��", 32, 16 + 60, 0);
}

int del_btn_fun(int color, int color_c)
{
	if (mouse_press(20+2, 649+5, 262-2, 649+46) == MOUSE_IN)
	{
		Clrmous();
		MouseS = 1;
		del_button(color_c);
		while (1)
		{
			Newxy();
			if (Mouse_above(20+2, 649+5, 262-2, 649+46))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					del_button(color);
					return 1;
					//���������1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				del_button(color);
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

void nextr_button(int color)
{
	Circlefill64k(849 + 68, 514 + 68, 68, color);
	Circle64k(849 + 68, 514 + 68, 69, 0);
	Circle64k(849 + 68, 514 + 68, 68, 0);
	Circle64k(849 + 68, 514 + 68, 67, 0);
	Outtextxx(849 + 68 - 40, 514 - 40 + 68, 849 + 40 + 68, "��һ", 32, 0);
	Outtextxx(849 + 68 - 40, 514 + 40 - 32 + 68, 849 + 68 + 40, "�غ�", 32, 0);
}

int nxt_btn_fun(int color, int color_c)
{
	long rx = MouseX - 849 - 68;
	long ry = MouseY - 514 - 68;
	if (rx * rx + ry * ry <= 68 * 68L)//Բ�������ж�
	{
		Clrmous();
		MouseS = 1;
		nextr_button(color_c);
		while (1)
		{
			Newxy();
			rx = MouseX - 849 - 68;
			ry = MouseY - 514 - 68;
			if (rx * rx + ry * ry <= 68 * 68L)
			{
				if (press == 1)
				{
					MouseS = 0;
					delay(200);//���û�ʱ��̧�����
					return 1;
				}//���������1
			}
			else
			{
				Clrmous();
				MouseS = 0;
				nextr_button(color);
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

/*********��Բ�ǵķ��ΰ�ť***********/
void rect_button(int x1, int y1, int x2, int y2, char* s, int color)
{
	int ra = (x2 - x1) / 10;
	Bar64k(x1 + ra, y1, x2 - ra, y1 + ra, color);
	Bar64k(x1, y1 + ra, x2, y2 - ra, color);
	Bar64k(x1 + ra, y2 - ra, x2 - ra, y2, color);
	Circlefill64k(x1 + ra, y1 + ra, ra, color);
	Circlefill64k(x1 + ra, y2 - ra, ra, color);
	Circlefill64k(x2 - ra, y1 + ra, ra, color);
	Circlefill64k(x2 - ra, y2 - ra, ra, color);
	if (strlen(s) > 6)
		Outtextxx(x1 + (ra / 2), (y1 + y2) / 2 - 16, x2 - (ra / 2), s, 32, 0);
	else
		Outtextxx(x1 + (ra * 2), (y1 + y2) / 2 - 16, x2 - (ra * 2), s, 32, 0);
}

/*********���ΰ�ť�ӿ򣬱���ʹ��***********/
void rect_btn_frame(int x1, int y1, int x2, int y2, int color)
{
	int ra = (x2 - x1) / 10;
	Linex(x1 + ra, y1 + 1, x2 - ra, y1 + 1, color);
	Liney(x1 + 1, y1 + ra, x1 + 1, y2 - ra, color);
	Liney(x2 - 1, y1 + ra, x2 - 1, y2 - ra, color);
	Linex(x1 + ra, y2 - 1, x2 - ra, y2 - 1, color);
	Circle_rd64k(x2 - ra, y2 - ra, ra - 1, color);
	Circle_ru64k(x2 - ra, y1 + ra, ra - 1, color);
	Circle_ld64k(x1 + ra, y2 - ra, ra - 1, color);
	Circle_lu64k(x1 + ra, y1 + ra, ra - 1, color);
	Linex(x1 + ra, y1 + 2, x2 - ra, y1 + 2, color);
	Liney(x1 + 2, y1 + ra, x1 + 2, y2 - ra, color);
	Liney(x2 - 2, y1 + ra, x2 - 2, y2 - ra, color);
	Linex(x1 + ra, y2 - 2, x2 - ra, y2 - 2, color);
	Circle_rd64k(x2 - ra, y2 - ra, ra - 2, color);
	Circle_ru64k(x2 - ra, y1 + ra, ra - 2, color);
	Circle_ld64k(x1 + ra, y2 - ra, ra - 2, color);
	Circle_lu64k(x1 + ra, y1 + ra, ra - 2, color);
}

/*********����Բ�ǰ�ť���ܺ���***********/
int rec_btn_fun(int x1, int y1, int x2, int y2, int color)
{
	if (MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2)
	{
		Clrmous();
		MouseS = 1;
		rect_btn_frame(x1, y1, x2, y2, 33808);
		while (1)//��������������꣬��������������⣨����ʹ�ö��״̬��¼��������lydԭ�� XD
		{
			Newxy();
			if (MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2)
			{
				if (press == 1)
				{
					Clrmous();
					rect_btn_frame(x1, y1, x2, y2, color);
					delay(50);
					return 1;
				}//���������1
			}
			else
			{
				Clrmous();
				MouseS = 0;
				rect_btn_frame(x1, y1, x2, y2, color); //��д���򣬼ӿ��ͼ�ٶ�
				return 0;
			}//�뿪����
		}
	}
	else
	{
		return 0;
	}
}

/*************Բ��ͼ��***************/
void battle_exit(int x, int y)
{
	Circlefill64k(x, y, 50, 64096);
	Line64k(x - 30, y - 30, x + 30, y + 30, 65535);
	Line64k(x + 1 - 30, y - 30, x + 30, y + 30, 65535);
}

/*************ѡ��˵�***************/
void save_btn(int color)
{
	rect_button(800, 10, 800 + 49, 10 + 34, "", color);
	Outtext(800 + 24 - 8, 10 + 17 - 8, "s", 16, 0, 0);
	Line64k(833, 23, 833, 34, 0);
	Line64k(834, 23, 834, 34, 0);
	Line45(834, 23, 832, 21, 0);
	Line45(833, 23, 831, 21, 0);
	Line64k(823, 21, 832, 21, 0);
	Line64k(823, 22, 832, 22, 0);
	Line45(823, 21, 821, 19, 0);
	Line45(823, 22, 821, 20, 0);
	Line64k(817, 19, 821, 19, 0);
	Line64k(817, 20, 821, 20, 0);
	Line45(817, 19, 815, 21, 0);
	Line45(815, 22, 817, 20, 0);
	Line64k(815, 22, 815, 34, 0);
	Line64k(816, 22, 816, 34, 0);
	Line45(815, 34, 817, 36, 0);
	Line45(816, 34, 817, 35, 0);
	Line64k(817, 35, 832, 35, 0);
	Line64k(817, 36, 832, 36, 0);
	Putpixel64k(833, 35, 0);
}

void option_btn(int color)
{
	rect_button(880, 10, 880 + 49, 44, "", color);
	Bar64k(880 + 14, 10 + 9, 880 + 49 - 14, 10 + 9 + 2, 0);
	Bar64k(880 + 14, 10 + 9 + 7, 880 + 49 - 14, 10 + 9 + 2 + 7, 0);
	Bar64k(880 + 14, 10 + 9 + 7 * 2, 880 + 49 - 14, 10 + 9 + 2 + 7 * 2, 0);
}

void exit_btn(int color)
{
	rect_button(960, 10, 960 + 49, 44, "", color);
	Line45(985 + 11, 27 + 11, 985 - 11, 27 - 11, 0);
	Line45(985 + 10, 27 + 11, 985 - 11, 27 - 10, 0);
	Line45(985 + 11, 27 + 10, 985 - 10, 27 - 11, 0);
	Line45(985 + 9, 27 + 11, 985 - 11, 27 - 9, 0);
	Line45(985 + 11, 27 + 9, 985 - 9, 27 - 11, 0);

	Line45(985 + 11, 27 - 11, 985 - 11, 27 + 11, 0);
	Line45(985 + 10, 27 - 11, 985 - 11, 27 + 10, 0);
	Line45(985 + 11, 27 - 10, 985 - 10, 27 + 11, 0);
	Line45(985 + 9, 27 - 11, 985 - 11, 27 + 9, 0);
	Line45(985 + 11, 27 - 9, 985 - 9, 27 + 11, 0);
}

void draw_opts()
{
	int dlay = 200;
	Bar64k(838, 47, 975, 87, 65370);
	rectangle64k(838, 47, 975, 87, 0);
	rectangle64k(837, 46, 976, 88, 0);
	Outtextxx(846, 54, 966, "ע��", 24, 0);
	delay(dlay);
	Bar64k(838, 47+41, 975, 87+41, 65370);
	rectangle64k(838, 47+41, 975, 87+41, 0);
	rectangle64k(837, 46+41, 976, 88+41, 0);
	Outtextxx(846, 54+41, 966, "���沢�˳�", 24, 0);
	delay(dlay);
	Bar64k(838, 47+41*2, 975, 87+41*2, 65370);
	rectangle64k(838, 47+41*2, 975, 87+41*2, 0);
	rectangle64k(837, 46+41*2, 976, 88+41*2, 0);
	Outtextxx(846, 54+41*2, 966, "����", 24, 0);
}

int opts_fun(void)
{
	while (1)
	{
		Newxy();
		if (press == 1)
		{
			if (Mouse_above(838, 47, 975, 87 + 41 * 2))
			{
				if (MouseY <= 87)//ע��
				{
					return HOMEPAGE;
				}
				else if (MouseY <= 87 + 41)//���沢�˳�
				{
					return EXIT;
				}
				else//����
				{
					return 444;
				}
			}
			else//����ⲿ�ر�
			{
				Map_partial(837, 46, 976, 88 + 41 * 2);
				return BATTLE;
			}
		}
		else if (press == 2)
		{
			Map_partial(837, 46, 976, 88 + 41 * 2);
			return BATTLE;
		}//�Ҽ��ر�
		
	}
}