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

����Ŀ¼
1.login��		��¼����
2.drawlogin��	���Ƶ�¼���溯��
3.login_check��	���������Ϣ����
******************************************************************/
#include "common.h" 

int login(char *username)  
{
	char password[20] = "\0";	//��ʼ����������
	int flag = 0;				//��ֹ�ظ�����
	
	drawlogin();
	Mouse_savebk2();//�������״̬����ֹ����
	
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
		
		if(flag == 0 && mouse_press(385, 600, 640, 700) == MOUSE_IN)	//������¼��
		{
			flag = 1;
			frame(385, 600, 640, 700, 65535);
			Outtext(410, 608,"��¼", 48, 80, 63488);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		
		if(flag == 1 && mouse_press(385, 600, 640, 700) == MOUSE_OUT)	//ȡ������	
		{
			flag = 0;
			shadow_l(385, 600, 640, 700, 65535);
			Outtext(410, 608,"��¼", 48, 80, 63488);
		}	
		
		if(mouse_press(180, 180,180+370, 180+50) == MOUSE_IN_L)						//�����û���
		{
			kbinput(180, 180,180+370, 180+50, username, 1);
		}
		
		if(mouse_press(180, 180+100, 180+370, 180+50+100) == MOUSE_IN_L)				//��������
		{
			kbinput(180, 180+100, 180+370, 180+50+100, password, 0);
		}
		
		if(mouse_press(256-15, 390-15, 384+15, 422+15) == MOUSE_IN_L)				//�����¼��
		{
			if(login_check(username, password) == 1)						//�ж��Ƿ����ļ�ƥ��
			{
				shadow_l(320-200, 240-100, 320+200, 240+100, 65535);
				delay(500);
				Outtext(150, 240-32,"��", 32, 102, 2463);					//��ٵĶ���Ч��
				delay(500);
				Outtext(150, 240-32,"����", 32, 102, 2463);
				delay(500);
				Outtext(150, 240-32,"���ڵ�", 32, 102, 2463);
				delay(500);
				Outtext(150, 240-32,"���ڵ�¼", 32, 102, 2463);
				delay(500);
				shadow_l(320-200, 240-100, 320+200, 240+100, 5);
				Outtextxx(150, 240-32, 150+340, "��¼�ɹ���", 32, 2463);
				delay(1000);
				return MAINMENU;
			}
			Outtext(120+92, 340-60,"���ڷ��ص�¼����", 16, 25, 65535);
			delay(1000);
			return LOGIN;
		}
	}
}

void drawlogin()
{
	Bar64k(0, 0, 1024, 768, 25290);
	Bar64k(0, 0, 50, 50, 65535);
	shadow_l(70, 50, 70+500, 50+90, 65535); 
	shadow_l(256-15, 390-15, 384+15, 422+15, 65535);
	
	frame(180, 180,180+370, 180+50, 65535);             //�û���
	Outtext(180+20,180+15,"��д��ĸ������", 16, 30, LIGHTGRAY);
	frame(180, 180+100, 180+370, 180+50+100, 65535);  	//����
	Outtext(180+20,280+15,"ע�����ִ�Сд", 16, 30, LIGHTGRAY);
	Outtext(85,70,"��ӭʹ�ñ�ϵͳ", 48, 70, GREEN);
	Outtext(70, 190,"�û���", 32, 30, 63488);
	Outtext(70, 290,"����", 32, 62, 63488);
	Outtext(256, 380,"��¼", 48, 80, 63488);
}

int login_check(char *username, char *password)
{
	FILE *fp;
	unsigned long long pw, pwt;
	char filename[30] = "users\\";
	
	strcat(filename, username);
	strcat(filename, ".txt");
	
	if(*username == '\0')//δ�����û���
	{
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "�������û���", 32, 65535);
		fclose(fp);
		return 0;
	}
	if(*password == '\0')//δ��������
	{
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "����������", 32, 65535);
		fclose(fp);
		return 0;
	}
	
	//�û����ж�
	if((fp = fopen(filename, "r")) == NULL)
	{
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "δ�ҵ����û�", 32, 65535);
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
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "�������", 32, 65535);
		fclose(fp);
		return 0;
	}
}