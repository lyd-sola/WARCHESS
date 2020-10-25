/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: loginmenu.c
author: ����ͩ�����Ƶ�
version: 2.0
Description: ��¼����
date:2020/9/8

������־
2020/9/9
	�Ż��˵�¼����
	�������ж��Ƿ���ȷ����ĺ���
	�������û������ļ�ƥ��Ĺ���
2020/10/25
	��������ܵ�¼��bug

����Ŀ¼
1.login��		��¼����
2.drawlogin��	���Ƶ�¼���溯��
3.login_check��	���������Ϣ����
******************************************************************/
#include "common.h" 

int login(char *username)  
{
	char password[20] = "\0";	//��ʼ����������
	char tmp[15];
	int flag = 0;				//��ֹ�ظ�����
	Clrmous();
	drawlogin();
	
	while(1)
	{
		Newxy();
		
		if(bioskey(1))
		{
			getch();
		}//��ֹ��������������Ӱ������
		
		if(mouse_press(0, 0, 80, 80) == MOUSE_IN_L)
		{
			return 1;
		}
		
		if(flag == 0 && mouse_press(686-15, 490-15, 814+15, 522+15) == MOUSE_IN)	//������¼��
		{
			flag = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			frame(686-15, 490-15, 814+15, 522+15, 65535);
			Outtext(686, 480, "��¼", 48, 80, 63488);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag == 1 && mouse_press(686-15, 490-15, 814+15, 522+15) == MOUSE_OUT)	//ȡ������	
		{
			flag = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(686-15, 490-15, 814+15, 522+15, 65535);
			Outtext(686, 480,"��¼", 48, 80, 63488);
		}	
		
		if(mouse_press(610, 280, 610 + 370, 280 + 50) == MOUSE_IN_L)						//�����û���
		{
			kbinput(610, 280, 610 + 370, 280 + 50, tmp, 1);
		}
		
		if(mouse_press(610, 280 + 100, 610 + 370, 280 + 50 + 100) == MOUSE_IN_L)				//��������
		{
			kbinput(610, 280 + 100, 610 + 370, 280 + 50 + 100, password, 0);
		}
		
		if(mouse_press(686 - 15, 490 - 15, 814 + 15, 522 + 15) == MOUSE_IN_L)				//�����¼��
		{
			if (*tmp == '\0')//δ�����û���
			{
				Outtext(620, 340, "�������û���", 16, 30, 63488);
			}
			else if (*tmp == '\0')//δ��������
			{
				Outtext(620, 440, "����������", 16, 30, 63488);
			}

			else if(login_check(tmp, password) == 1)						//�ж��Ƿ����ļ�ƥ��
			{
				Bar64k_radial(512-250, 384-100, 512+250, 384+100, 65535, 0);
				delay(500);
				Outtext(512-200+30, 384-24,"��", 48, 102, 2463);					//��ٵĶ���Ч��
				delay(500);
				Outtext(512 - 200 + 30, 384-24,"����", 48, 102, 2463);
				delay(500);
				Outtext(512 - 200 + 30, 384-24,"���ڵ�", 48, 102, 2463);
				delay(500);
				Outtext(512 - 200 + 30, 384-24,"���ڵ�¼", 48, 102, 2463);
				delay(500);
				Bar64k_radial(512-200, 384-100, 512+200, 384+100, 33333, 0);
				Outtextxx(512-200+30, 384-24, 512-200+30+340, "��¼�ɹ���", 48, 2463);
				delay(1000);
				strcpy(username, tmp);
				return MAINMENU;
			}
			else
			{
				Outtext(312 + 92, 484 - 60, "���ڷ��ص�¼����", 16, 25, 65535);
				delay(1000);
				return LOGIN;
			}
		}
	}
}

void drawlogin()
{
	//Bar64k(0, 0, 1024, 768, 25290);
	Putbmp64k(0, 0, "BMP//lng.bmp");

	Bar64k(0, 0, 50, 50, 65535); //�˳�

	Outtext(60, 70, "��ӭʹ��", 48, 70, 33808);
	Outtext(60, 210, "ս��ϵͳ", 48, 70, 33808);

	shadow_l(535, 120, 960, 232, 65535);
	Outtext(550, 130, "WARCHESS", 48, 48, 65535);
    Outtext(550 + 2, 130 + 2, "WARCHESS", 48, 48, 65184);
	Outtext(550, 190, "ͨ��֤��֤", 32, 70, 0);

	frame(610, 280,610+370, 280+50, 65535);             //�û���
	Outtext(500, 290,"�û���", 32, 30, 63488);
	Outtext(610+20,280+15,"��д��ĸ������", 16, 30, 0);
	
	frame(610, 280+100, 610+370, 280+50+100, 65535);  	//����
	Outtext(500, 390,"����", 32, 62, 63488);
	Outtext(610+20,380+15,"ע�����ִ�Сд", 16, 30, 0);
	
	shadow_l(686-15, 490-15, 814+15, 522+15, 65535);
	Outtext(686, 480,"��¼", 48, 80, 63488);
}

int login_check(char *username, char *password)
{
	FILE *fp;
	unsigned long long pw, pwt;
	char filename[30] = "users\\";
	
	strcat(filename, username);
	
	//�û����ж�
	if((fp = fopen(filename, "r")) == NULL)
	{
		shadow_l(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "δ�ҵ����û�", 32, 65535);
		fclose(fp);
		return 0;
	}
	
	//�����ж�
	fscanf(fp, "%llu%llu", &pw, &pwt);
	if(pw == password_classified(password, 67) && pwt == password_classified(password, 71) )
	{
		fclose(fp);
		return 1;
	}
	else
	{
		*password = 0;
		shadow_l(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "�������", 32, 65535);
		fclose(fp);
		return 0;
	}
}