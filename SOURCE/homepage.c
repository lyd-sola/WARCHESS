/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: homepage.c
author: ����ͩ
version: 2.0
Description: ��ҳ����
date:2020/9/8

������־
9.9		��������ҳ����İ���,�Ż��˽���Ч��
		�����˵������
10.25	�Ż���homepage()�������ο͵�¼
10.26	���ӹ��ڽ���
******************************************************************/
#include "common.h"

int homepage()
{
	Clrmous();//�������״̬����ֹ����
	draw_h_page(); //������ҳ����

	delay(1000);
	while(1)
	{
		Newxy();
	
		if(mouse_press(974, 0, 1024, 50) == MOUSE_IN_L) //�˳�
		{
			return EXIT;
		}
		
		if (homepg_btn_fun(700, 230, 950, 300, "��¼"))
		{
			return LOGIN;
		}
		if (homepg_btn_fun(700, 350, 950, 420, "ע��"))
		{
			return REGIS;
		}
		if (homepg_btn_fun(700, 470, 950, 540, "����"))
		{
			return ABOUT;
		}
		if (homepg_btn_fun(700, 590, 950, 660, "�˳�"))
		{
			exit(0);
		}
		if (guest_btn_fun())
		{
			return GUEST;
		}
		/*************************�����ã��Ҽ����½ǽ���testҳ��****************************/
		if(mouse_press(1024-100, 768-100, 1024, 768) == MOUSE_IN_R)
		{
			return 233;
		}

		if (mouse_press(0, 0, 30, 30) == MOUSE_IN_R)	//Ϊ�������,���˵����Ͻ��Ҽ�ֱ�ӿ��ٵ�¼
		{
			return MAINMENU;
		}
	}
}

void draw_h_page()
{
	//Bar64k(0, 0, 1024, 768, 29186);
	Putbmp64k(0, 0, "BMP//homepage.bmp");
	Bar64k(974, 0, 1024, 50,65535);
	Outtext(984, 9, "��", 32, 0, 0);
	Outtext(85+2,90+2,"�������Կ�����", 48, 70, 27469);
	Outtext(85, 90, "�������Կ�����", 48, 70, 0);

	homepg_button(700, 230, 950, 300, "��¼", 65336);
	homepg_button(700, 350, 950, 420, "ע��", 65336);
	homepg_button(700, 470, 950, 540, "����", 65336);
	homepg_button(700, 590, 950, 660, "�˳�", 65336);

	Outtextxx(846, 313, 978, "�ο͵�¼", 24, 0);
}

void homepg_button(int x1, int y1, int x2, int y2, char *s, int color)
{
	shadow_l(x1, y1, x2, y2, color);
	Outtext(x1+60, y1+10, s, 48, 70, 0);
	rectangle64k(x1-1, y1-1, x2+1, y2+1, 35362);
	rectangle64k(x1-2, y1-2, x2+2, y2+2, 35362);
}

int homepg_btn_fun(int x1, int y1, int x2, int y2, char *s)//��ť���ܺ���
{
	if (Mouse_above(x1 - 2, y1 - 2, x2 + 2, y2 + 2))
	{
		Clrmous();
		MouseS = 1;
		homepg_button(x1, y1, x2, y2, s, 44373);
		while (1)
		{
			Newxy();
			if (Mouse_above(x1-2, y1-2, x2+2, y2+2))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					return 1;
					//���������1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				homepg_button(x1, y1, x2, y2, s, 65336);
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int guest_btn_fun()//�ο͵�¼��ť���ܺ���
{
	if (Mouse_above(846, 313, 978, 313 + 24))
	{
		Clrmous();
		MouseS = 1;
		Bar64k(846, 313 + 26, 978, 313 + 27, 0);
		while (1)
		{
			Newxy();
			if (Mouse_above(846, 313, 978, 313 + 24))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					return 1;
					//���������1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				putbmp_partial(846, 313 + 26, 978, 313 + 27, "BMP//homepage.bmp");
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int about_page()
{
	Clrmous();
	Putbmp64k(0, 0, "BMP//about.bmp");
	rect_button(833, 700, 1000, 755, "����������", 65370);
	while (1)
	{
		Newxy();
		if (rec_btn_fun(833, 700, 1000, 755, 65370))
		{
			return HOMEPAGE;
		}
	}
}