/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: mainmenu.c
author: ����ͩ
version: 1.0
Description: ���˵�
date:2020/9/9

������־

����Ŀ¼
1.mainmenu:		���˵�����
2.mmenu_draw:	�������˵�����
******************************************************************/
#include "common.h"

int mainmenu(char *user)
{
	mmenu_draw(user); //�������˵�����
	clrmous(MouseX, MouseY);//�������״̬����ֹ����
	
	while(1)
	{
		Newxy();
		
		if(mouse_press(0, 0, 50, 50) == MOUSE_IN_L)
		{
			return 1;
		}
		
		if(mouse_press(330, 140+85, 330+250, 140+85+55) == MOUSE_IN_L)
		{
			/******************* ���� �ǵ�ɾ��********************/
			if(savefile_creat(user) == 0)
			{
				Outtext(0, 0, "�浵�ļ���", 16, 20, 65535);
				delay(1000);
				exit(0);
			}
			
			Outtext(0, 0, "�ɹ������浵", 16, 20, 65535);
			delay(1000);
			return MAINMENU;
		}
		
		/*if(mouse_press(330, 140+85, 330+250, 140+85+55))
		{
			;
		}*/
	}
}

void mmenu_draw(char *user)//�˵��������Ծ���˫�˶�ս�����Ծ���е������ģʽ�����ػ���������ȡ�浵������սָ��������˵�����������ձ���ע���˺ţ�
{
	Clrmous();
	Bar64k_radial(0, 0, 1024, 768, 65535, 0);


}