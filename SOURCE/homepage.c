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
	Clrmous();//�������״̬����ֹ����
	draw_h_page(); //������ҳ����
	while(1)
	{
		Newxy();
		if(bioskey(1))
		{
			getch();
		}//��ֹ��������������Ӱ������
	
		if(mouse_press(974, 0, 1024, 50) == MOUSE_IN_L) //�˳�
		{
			return EXIT;
		}
		
		if(flag1 == 0 && mouse_press(700, 230, 950, 300) == MOUSE_IN)	//������¼��
		{
			flag1 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k_radial(700, 230, 950, 300, 57083, 0);
			Outtext(750 + 10, 240, "��¼", 48, 70, 0);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag1 == 1 && mouse_press(700, 230, 950, 300) == MOUSE_OUT)	//ȡ������
		{
			flag1 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 230, 950, 300, 65336);
			Outtext(750 + 10, 240, "��¼", 48, 70, 0);
			rectangle64k(699, 229, 951, 301, 35362);
			rectangle64k(698, 228, 952, 302, 35362);
		}
		
		if(flag2 == 0 && mouse_press(700, 350, 950, 420) == MOUSE_IN)	//����ע���
		{
			flag2 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(700, 350, 950, 420, 57083);
			Outtext(750 + 10, 360, "ע��", 48, 70, 0);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag2 == 1 && mouse_press(700, 350, 950, 420) == MOUSE_OUT)	//ȡ������
		{
			flag2 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 350, 950, 420, 65336);
			Outtext(750 + 10, 360, "ע��", 48, 70, 0);
			rectangle64k(699, 349, 951, 421, 35362);
			rectangle64k(698, 348, 952, 422, 35362);
		}
		
		if(flag3 == 0 && mouse_press(700, 470, 950, 540) == MOUSE_IN)	//�������ڼ�
		{
			flag3 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(700, 470, 950, 540, 44373);
			Outtext(750 + 10, 480, "����", 48, 70, 0);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag3 == 1 && mouse_press(700, 470, 950, 540) == MOUSE_OUT)	//ȡ������
		{
			flag3 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 470, 950, 540, 65336);
			Outtext(750 + 10, 480, "����", 48, 70, 0);
			rectangle64k(699, 469, 951, 541, 35362);
			rectangle64k(698, 468, 952, 542, 35362);
		}
		
		if(flag4 == 0 && mouse_press(700, 590, 950, 660) == MOUSE_IN)	//�����˳���
		{
			flag4 = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			Bar64k(700, 590, 950, 660,44373);
			Outtext(750 + 10, 600, "�˳�", 48, 70, 0);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag4 == 1 && mouse_press(700, 590, 950, 660) == MOUSE_OUT)	//ȡ������
		{
			flag4 = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(700, 590, 950, 660, 65336);
			Outtext(750 + 10, 600, "�˳�", 48, 70, 0);
			rectangle64k(699, 589, 951, 661, 35362);
			rectangle64k(698, 588, 952, 662, 35362);
		}
		
		if(mouse_press(70, 70, 70+500, 70+90) == MOUSE_IN_R)				//Ϊ�˷������,�Ҽ��������ֱ��������¼����������˵�
		{
			return MAINMENU;
		}
		
		if(mouse_press(700, 470, 950, 540) == MOUSE_IN_L)	//������ڼ�
		{
			return ABOUT;
		}
		
		if(mouse_press(700, 230, 950, 300) == MOUSE_IN_L)	//�����¼��
		{
			return LOGIN;
		}
		
		if(mouse_press(700, 350, 950, 420) == MOUSE_IN_L)			//���ע���
		{
			return REGIS;
		}
		if(mouse_press(700, 590, 950, 660) == MOUSE_IN_L)			//����˳���
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
	Bar64k(974, 0, 1024, 50,65535);
	

	Outtext(984, 9,"��", 32, 0, RED);
	Outtext(85+2,90+2,"�������Կ�����", 48, 70, 27469);
	Outtext(85, 90, "�������Կ�����", 48, 70, 0);


	shadow_l(700, 230, 950, 300, 65336);
	Outtext(750+10, 240,"��¼", 48, 70, 0);
	rectangle64k(699, 229, 951, 301, 35362);
	rectangle64k(698, 228, 952, 302, 35362);

	shadow_l(700, 350, 950, 420, 65336);
	Outtext(750+10, 360,"ע��", 48, 70, 0);
	rectangle64k(699, 349, 951, 421, 35362);
	rectangle64k(698, 348, 952, 422, 35362);
	
	shadow_l(700, 470, 950, 540, 65336);
	Outtext(750+10, 480,"����", 48, 70,0);
	rectangle64k(699, 469, 951, 541, 35362);
	rectangle64k(698, 468, 952, 542, 35362);
	
	shadow_l(700, 590, 950, 660, 65336);
	Outtext(750+10, 600,"�˳�", 48, 70, 0);
	rectangle64k(699, 589, 951, 661, 35362);
	rectangle64k(698, 588, 952, 662, 35362);
}