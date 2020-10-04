/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: functions.c
author: ���Ƶ�
version: 0
Description: ���õĺ���
date:2020/9/13

������־
9.13	������show_error
9.14	��ť��ع��ܺ���Light_button

����Ŀ¼
******************************************************************/
#include "common.h"
FILE* FBMP;
/**********************************************************
Function��		show_error
Description��	������Ϣ��ʾ����
Input:			msgΪ������Ϣ��modeΪ1 exit��Ϊ0 ������
Author��		���Ƶ�
**********************************************************/
void show_error(char* msg, int mode)//��ʾ��240,225  785,567
{
	unsigned int i = 0;//��ֹ�������õ�ȷ��
	int  flag = 0;
	Clrmous();
	rectangle64k(240, 225, 785, 567, 0);
	Bar64k_radial(241, 226, 784, 503, 63422, 0);
	Bar64k(241, 504, 784, 566, 57083);
	Outtext(240 + 20, 225 + 20, "WARCHESSս�塪��by 1904 ���Ƶѡ�����ͩ", 16, 14, 27469);//��ܻ���
	Circle64k(286, 311, 18, 45476);
	Circlefill64k(286, 311, 17, 61890);
	Line64k(286 - 8, 303, 286 + 8, 311 + 8, 65535);
	Line64k(286 - 8, 304, 286 + 8, 311 + 8 + 1, 65535);
	Line64k(286 - 8 + 1, 303, 286 + 8 + 1, 311 + 8, 65535);
	Line64k(286 + 8, 311 - 8, 286 - 8, 311 + 8, 65535);
	Line64k(286 + 8 - 1, 311 - 8, 286 - 8 - 1, 311 + 8, 65535);
	Line64k(286 + 8, 311 - 8 + 1, 286 - 8, 311 + 8 + 1, 65535);//�����
	Outtext(314, 311-16, "Error", 32, 25, 0);
	Outtext(314, 360, msg, 24, 27, 0);
	rectangle64k(677, 519, 774, 550, 0);
	Bar64k_radial(678, 520, 773, 549, 59164, 0);
	Outtext(701, 524, "ȷ��", 24, 26, 0);//ȷ����

	if (mode)
	{
		Outtext(314, 433, "Ӧ�����ڴ����쳣ֹͣ", 24, 25, 0);
		Outtext(314, 435 + 16*2, "This application terminated with an error. ", 16, 10, 0);
	}
	else
	{
		Outtext(314, 433, "Ӧ�ó��ִ��󣬼�������������", 24, 25, 0);
		Outtext(314, 435 + 16*2, "An error occurred, returning to homepage. ", 16, 10, 0);
	}

	while (1)
	{
		Newxy();
		if (flag == 0 && Mouse_above(678, 520, 773, 549))
		{
			Clrmous();
			MouseS = 1;
			Bar64k_radial(678, 520, 773, 549, 65535, 0);
			Outtext(701, 524, "ȷ��", 24, 26, 0);//����ȷ�ϼ�
			flag = 1;
		}
		if (flag == 1 && Mouse_aboveother(678, 520, 773, 549))
		{
			Clrmous();
			MouseS = 0;
			Bar64k_radial(678, 520, 773, 549, 59164, 0);
			Outtext(701, 524, "ȷ��", 24, 26, 0);//ȡ������ȷ����
			flag = 0;
		}
		if (mouse_press(678, 520, 773, 549) == MOUSE_IN_L || i >= 800)
		{
			if (mode)
			{
				Clrmous();
				Bar64k_radial_re(0, 0, 1024, 768, 65535, 1000);
				exit(1);
			}
			else
			{
				return;
			}
		}
		i ++;
	}
}
//�ڶ�ս������Ϣ����ʾ��Ϣ
void show_msg(char* msg, char *msg2)
{
	static char* lastmsg;
	if (strcmp(msg, lastmsg) == 0)	//��֤�˲����������ͬ�������ֵ�����˸
		return;
	Map_partial(340, 666, 720, 666+17, FBMP);
	Outtext(340, 666, msg, 16, 23, 0);
	Map_partial(340, 705, 720, 705 + 17, FBMP);
	Outtext(340, 705, msg2, 16, 23, 0);
	lastmsg = msg;
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
		Bar64k(750, y0 - 16, 1000, y0 - 1, 65535);//�ڵ���ť�⺺��
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
				Bar64k(750, y0 - 16, 1000, y0 - 1, 65535);
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

int atk_btn_fun(char *s, int color, int color_c)
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
					MouseS = 0;
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
					MouseS = 0; 
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

int nxt_btn_fun(int color, int color_c)
{
	long rx = MouseX - 849 - 68;
	long ry = MouseY - 514 - 68;
	if (rx * rx + ry * ry <= 68*68L)//Բ�������ж�
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

/*********�������ΰ�ť***********/
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

/*��Ļ����ʾ��Ϣ�򣬵��btn1����1��btn2����0*/
short msgbar(char *btn1, char *btn2, char *s1, char *s2)
{
	Clrmous();
	Bar64k_radial(262, 218, 262 + 500, 219 + 230, 34429, 0);
	rect_button(318, 384, 112+318, 45+384, btn1, 65535);
	rect_button(581, 384, 112+581, 45+384, btn2, 65535);
	Outtext(304, 252, s1, 32, 35, 0);
	Outtext(304, 314, s2, 32, 35, 0);
	while (1)
	{
		Newxy();
		if (rec_btn_fun(318, 384, 112 + 318, 45 + 384, 65535))
		{
			return 1;
		}//���ȷ������1
		if (rec_btn_fun(581, 384, 112 + 581, 45 + 384, 65535))
		{
			return 0;
		}//���ȡ������0
	}
}