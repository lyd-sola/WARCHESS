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
	Clrmous();//�������״̬����ֹ����
	savefile_creat(user);
	
	while(1)
	{
		Newxy();
		
		if(mouse_press(0, 0, 50, 50) == MOUSE_IN_L)
		{
			return HOMEPAGE;
		}
	}
}

void mmenu_draw(char *user)//�˵��������Ծ���˫�˶�ս�����Ծ���е������ģʽ�����ػ���������ȡ�浵������սָ��������˵�����������ձ���ע���˺ţ�
{
	Clrmous();
	Bar64k_radial(0, 0, 1024, 768, 65535, 0);
	Button(225, "�����Ծ�",60361, 65535);
	Button(225+110, "��ս��е", 60361, 65535);
	Button(225+220, "�ػ�����", 60361, 65535);
	Button(225+330, "��սָ��", 60361, 65535);
	Button(225+440, "�����ձ�", 60361, 65535);

}