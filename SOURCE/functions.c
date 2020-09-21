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

//��ʾ��240,225  785,567
/**********************************************************
Function��		show_error
Description��	������Ϣ��ʾ����
Input:			msgΪ������Ϣ��modeΪ1 exit��Ϊ0 ������
Author��		���Ƶ�
**********************************************************/
void show_error(char* msg, int mode)
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
		if (Mouse_press(678, 520, 773, 549) == MOUSE_IN_L || i >= 800)
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
/**********************************************************
Function��		Light_button
Description��	��ť��������������������ܣ��ǲ��Ǹøĸ����أ���������
				�����ҳ�溯��һ�������ж�����
				�����ÿһ����ť����Ҫ��һ��flag����
Calls��			Button
Input:			sԭ��ť���֣�s_change������ť����
				yo���߶�color1��ɫ��color2����ɫ�����밴ť���Ʋ���ֵ��
Output:			����1ʱ�����
Author��		���Ƶ�
**********************************************************/
int Light_button(int y0, char* s, char* s_change, int color, int color2)		/*������Ĭ�ϱ���ɫΪ��ɫ�������޸�*/
{
	if (MouseX >= MouseY - y0 + 720 && MouseY >= y0 && MouseY <= y0 + 30)//б��Ҳ���������ж�Ŷ
	{

		Clrmous();
		MouseS = 1;
		Bar64k(750, y0 - 16, 1000, y0 - 1, 65535);//�ڵ���ť�⺺��
		Button(y0, s_change, 64800, 65535);
		while (1)//��������������꣬���flag���⣬lydԭ�� XD
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
			}
		}
	}
	else
	{
		return 0;
	}
}