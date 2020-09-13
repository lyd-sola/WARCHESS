/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: homepage.c
author: ����ͩ
version: 1.2
Description: ��ҳ����
date:2020/9/8

������־
9.9		��������ҳ����İ���,�Ż��˽���Ч��
		�����˵������


����Ŀ¼
1.homepage��	��ҳ����
2.draw_h_page:	��ҳ����
******************************************************************/
#include "common.h"

int homepage()
{
	int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;	/***********��ֹ�ظ�����, �˴���Ҫ�Ż���һ��flag****************/
	
	clrmous(MouseX, MouseY);//�������״̬����ֹ����
	draw_h_page(); //������ҳ����

	while(1)
	{
		Newxy();
		
		if(bioskey(1))
		{
			getch();
		}//��ֹ��������������Ӱ������
	
		if(mouse_press(590, 0, 640, 50) == MOUSE_IN_L) //�˳�
		{
			return EXIT;
		}
		
		if(flag1 == 0 && mouse_press(70, 230, 35+235, 230+70) == MOUSE_IN)	//������¼��
		{
			flag1 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k_radial(70, 230, 35+235, 230+70, 2016, 0);
			Outtext(100+10, 240,"��¼", 48, 70, 0);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag1 == 1 && mouse_press(70, 230, 35+235, 230+70) == MOUSE_OUT)	//ȡ������
		{
			flag1 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			Bar64k_radial_re(70, 230, 35+235, 230+70, 65535, 0);
			Outtext(100+10, 240,"��¼", 48, 70, 2016);
		}
		
		if(flag2 == 0 && mouse_press(570-200, 230, 570, 230+70) == MOUSE_IN)	//����ע���
		{
			flag2 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(570-200, 230, 570, 230+70,44373);
			Outtext(400+10, 240,"ע��", 48, 70, 2016);
		}
		
		if(flag2 == 1 && mouse_press(570-200, 230, 570, 230+70) == MOUSE_OUT)	//ȡ������
		{
			flag2 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(570-200, 230, 570, 230+70, 65535);
			Outtext(400+10, 240,"ע��", 48, 70, 2016);
		}
		
		if(flag3 == 0 && mouse_press(70, 330, 35+235, 330+70) == MOUSE_IN)	//�������ڼ�
		{
			flag3 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(70, 330, 35+235, 330+70,44373);
			Outtext(100+10, 340,"����", 48, 70, 2016);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag3 == 1 && mouse_press(70, 330, 35+235, 330+70) == MOUSE_OUT)	//ȡ������
		{
			flag3 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(70, 330, 35+235, 330+70, 65535);
			Outtext(100+10, 340,"����", 48, 70, 2016);
		}
		
		if(flag4 == 0 && mouse_press(570-200, 330, 570, 330+70) == MOUSE_IN)	//�����˳���
		{
			flag4 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(570-200, 330, 570, 330+70,44373);
			Outtext(400+10, 340,"�˳�", 48, 70, 2016);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag4 == 1 && mouse_press(570-200, 330, 570, 330+70) == MOUSE_OUT)	//ȡ������
		{
			flag4 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(570-200, 330, 570, 330+70, 65535);
			Outtext(400+10, 340,"�˳�", 48, 70, 2016);
		}
		
		if(mouse_press(70, 70, 70+500, 70+90) == MOUSE_IN_R)				//Ϊ�˷������,�Ҽ��������ֱ��������¼����������˵�
		{
			return MAINMENU;
		}
		
		if(mouse_press(70, 330, 35+235, 330+70) == MOUSE_IN_L)	//������ڼ�
		{
			return ABOUT;
		}
		
		if(mouse_press(70, 230, 35+235, 230+70) == MOUSE_IN_L)	//�����¼��
		{
			return LOGIN;
		}
		
		if(mouse_press(570-200, 230, 570, 230+70) == MOUSE_IN_L)			//���ע���
		{
			return REGIS;
		}
		if(mouse_press(570-200, 330, 570, 330+70) == MOUSE_IN_L)			//����˳���
		{
			exit(0);
		}
		
		/*************************�����ã��Ҽ����½ǽ���testҳ��****************************/
		if(mouse_press(1024-100, 768-100, 1024, 768) == MOUSE_IN_R)
		{
			return 233;
		}
	}
}

void draw_h_page()
{
	//Bar64k(0, 0, 1024, 768, 29186);
	Putbmp64k(0, 0, "BMP//homepage.bmp");
	Bar64k(590, 0, 640, 50,65535);
	Outtext(599, 9,"��", 32, 0, RED);
	
	shadow_l(70, 70, 70+500, 70+90, 65535); 
	Outtext(85,90,"�������Կ�����", 48, 70, 2016);
	
	shadow_l(70, 230, 35+235, 230+70, 65535);
	Outtext(100+10, 240,"��¼", 48, 70, 2016);
	
	shadow_l(570-200, 230, 570, 230+70, 65535);
	Outtext(400+10, 240,"ע��", 48, 70, 2016);
	
	shadow_l(70, 330, 35+235, 330+70, 65535);
	Outtext(100+10, 340,"����", 48, 70, 2016);
	
	shadow_l(570-200, 330, 570, 330+70, 65535);
	Outtext(400+10, 340,"�˳�", 48, 70, 2016);
}