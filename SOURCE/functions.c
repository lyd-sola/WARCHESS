/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: functions.c
author: ���Ƶ�
version: 1.0
Description: ���õĺ���
date:2020/9/13

������־
9.13	������show_error
9.14	��ť��ع��ܺ���Light_button��������draw.c
******************************************************************/
#include "common.h"
/**********************************************************
Function��		show_error
Description��	������Ϣ��ʾ����
Input:			msgΪ������Ϣ��modeΪ1 exit��Ϊ0 ������
Author��		���Ƶ�
**********************************************************/
void draw_show_error()
{
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
	Outtext(314, 311 - 16, "Error", 32, 25, 0);
	
	rectangle64k(677, 519, 774, 550, 0);
	Bar64k_radial(678, 520, 773, 549, 59164, 0);
	Outtext(701, 524, "ȷ��", 24, 26, 0);//ȷ����
}
void show_error(char* msg, int mode)//��ʾ��240,225  785,567
{
	unsigned int i = 0;//��ֹ�������õ�ȷ��
	int  flag = 0;
	Clrmous();
	draw_show_error();
	Outtext(314, 360, msg, 24, 27, 0);
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
	Map_partial(340, 666, 720, 666+25);
	Outtext(340, 666, msg, 24, 26, 0);
	Map_partial(340, 705, 720, 705 + 25);
	Outtext(340, 705, msg2, 24, 26, 0);
	lastmsg = msg;
}

/*��Ļ����ʾ��Ϣ�򣬵��btn1����1��btn2����0*/
int msgbar(char *btn1, char *btn2, char *s1, char *s2)
{
	Clrmous();
	rect_circle(262, 218, 262 + 500, 219 + 230, 34429);
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