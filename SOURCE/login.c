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
2020/10/30
	��������������ܱ�����
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

		if (forget_fun())                                              //�޸�����
		{
			if (*tmp) //�Ѿ������û���
			{
				forget_password(tmp);
			}
			else  //δ�����û���
			{
				rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 65535);
				Outtext(512 - 200 + 30, 384 - 24, "�������û���", 48, 55, 2463);
				delay(1000);
			}
			return LOGIN;
		}

		if(mouse_press(686 - 15, 490 - 15, 814 + 15, 522 + 15) == MOUSE_IN_L)				//�����¼��
		{
			if (*tmp == '\0')//δ�����û���
			{
				Outtext(620, 340, "�������û���", 16, 30, 63488);
			}
			else if (*password == '\0')//δ��������
			{
				Outtext(620, 440, "����������", 16, 30, 63488);
			}

			else if(login_check(tmp, password) == 1)						//�ж��Ƿ����ļ�ƥ��
			{
				login_anime();
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

		if (quick_regi())                                              //���û�
		{
			return REGIS;
		}
	}
}

void drawlogin()
{
	Putbmp64k(0, 0, "BMP//lng.bmp");

	Bar64k(0, 0, 50, 50, 65535); //�˳�
	Outtext(9, 9, "��", 32, 0, 0);
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
	Outtextxx(846, 435, 610+370, "��������", 24, 0);
	Outtext(846, 335, "���û���", 24, 38, 0);
}

void login_anime(void)
{
	rect_circle(512 - 250, 384 - 100, 512 + 250, 384 + 100, 65535);
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "��", 48, 102, 2463);					//��ٵĶ���Ч��
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "����", 48, 102, 2463);
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "���ڵ�", 48, 102, 2463);
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "���ڵ�¼", 48, 102, 2463);
	delay(500);
	rect_circle(512 - 250, 384 - 100, 512 + 250, 384 + 100, 65535);
	Outtextxx(512 - 200 + 30+5, 384 - 24, 512 - 200 + 30 + 340, "��¼�ɹ���", 48, 2463);
	delay(1000);
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
		rect_circle(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "δ�ҵ����û�", 32, 65535);
		fclose(fp);
		return 0;
	}

	//�����ж�
	fscanf(fp, "%llu", &pw);
	fgetc(fp);
	fscanf(fp, "%llu", &pwt);
	if(pw == password_classified(password, 67) && pwt == password_classified(password, 71) )
	{
		fclose(fp);
		return 1;
	}
	else
	{
		*password = 0;
		rect_circle(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "�������", 32, 65535);
		fclose(fp);
		return 0;
	}
}

int quick_regi(void)//��תע�ᰴť���ܺ���
{
	if (Mouse_above(846, 335, 978, 335 + 24))
	{
		Clrmous();
		MouseS = 1;
		Bar64k(846, 335 + 26, 978, 335 + 27, 0);
		while (1)
		{
			Newxy();
			if (Mouse_above(846, 335, 978, 335 + 24))
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
				putbmp_partial(846, 335 + 26, 978, 335 + 27, "BMP//lng.bmp");
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int forget_fun(void)//�������밴ť���ܺ���
{
	if (Mouse_above(846, 435, 978, 435+24))
	{
		Clrmous();
		MouseS = 1;
		Bar64k(846, 435+26, 978, 435+27, 0);
		while (1)
		{
			Newxy();
			if (Mouse_above(846, 435, 978, 435+24))
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
				putbmp_partial(846, 435+26, 978, 435+27, "BMP//lng.bmp");
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

void forget_draw(int q)
{
	putbmp_partial(312, 120, 610 + 370, 522 + 15+10, "BMP//lng.bmp");
	//frame(610, 165, 610 + 370, 165 + 50, 65535);   //����
	Outtext(610 - 168, 175, "����", 32, 118, 63488);
	switch (q)
	{
	case 1:
		Outtext(610+10, 165+13, "���������ǣ�", 24, 28, 0);
		break;
	case 2:
		Outtext(610+10, 165+13, "�����֤������ʮλ�ǣ�", 24, 28, 0);
		break;
	case 3:
		Outtext(610+10, 165+13, "������������ǣ�", 24, 28, 0);
		break;
	case 4:
		Outtext(610+10, 165+13, "����һλ���˵������ǣ�", 24, 28, 0);
		break;
	}

	frame(610, 165 + 100, 610 + 370, 165 + 50 + 100, 65535);  //��
	Outtext(610 - 168, 175 + 100, "��", 32, 118, 63488);
	Outtext(610 + 20, 185 + 100, "�������ܱ�����Ĵ�", 16, 30, 27469);
	
	frame(610, 165 + 200, 610 + 370, 165 + 50 + 200, 65535);  //������
	Outtext(610 - 168, 175 + 200, "������", 32, 59, 63488);
	Outtext(610 + 20, 185 + 200, "��������������", 16, 30, 27469);

	shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
	Outtext(686, 480, "���", 48, 80, 63488);
}

void forget_password(char* username)
{
	FILE* fp;
	int q=0, check = 0;
	unsigned long long answert;
	char buffer[40], answer[40] = "\0", password[40] = "\0";
	char filename[30] = "users\\";
	strcat(filename, username);

	if ((fp = fopen(filename, "r")) == NULL)
	{
		rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 5);
		Outtextxx(512 - 200 + 30, 384 - 100 + 40, 512 - 200 + 340, "δ�ҵ����û�", 32, 65535);
		fclose(fp);
		return;
	}
	fgets(buffer, 40, fp);
	fscanf(fp, "%d%llu", &q, &answert);
	fclose(fp);
	forget_draw(q);
	while (1)
	{
		Newxy();
		if (mouse_press(610, 165 + 100, 610 + 370, 165 + 50 + 100) == MOUSE_IN_L)					//�����
		{
			kbinput(610, 165 + 100, 610 + 370, 165 + 50 + 100, answer, 0);
		}
		if (mouse_press(610, 165 + 200, 610 + 370, 165 + 50 + 200) == MOUSE_IN_L)					//��������
		{
			kbinput(610, 165 + 200, 610 + 370, 165 + 50 + 200, password, 0);
		}
		if (mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_IN_L)
		{
			if ((check = reset_check(answer, password, answert)) == 1)
			{
				password_reset(username, password);
				rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
				Outtextxx(512 - 170 + 10, 384 - 20, 512 - 170 + 340, "�޸ĳɹ���", 48, 65535);
				delay(500);
				return;
			}
			else if(check == 2)
			{
				forget_draw(q);
			}
		}
		if (mouse_press(0, 0, 50, 50) == 1)
		{
			return;
		}
	}
}

int reset_check(char* answer, char* password, unsigned long long answert)
{
	if (*answer == '\0')//δ�����û���
	{
		Outtext(620, 320, "�������", 16, 30, 63488);
	}
	else if (*password == '\0')//δ��������
	{
		putbmp_partial(620, 420, 620 + 30 * 7 + 16, 420 + 16, "BMP\\lng.bmp");
		Outtext(620, 420, "������������", 16, 30, 63488);
	}
	else if(strlen(password) < 4)
	{
		putbmp_partial(620, 420, 620 + 30 * 7 + 16, 420 + 16, "BMP\\lng.bmp");
		Outtext(620, 420, "���볤���������", 16, 30, 63488);
	}
	else if (password_classified(answer, 71) != answert)
	{
		rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170+10, 384-20, 512 - 170 + 340, "�𰸴���", 48, 65535);
		*answer = 0;
		delay(1000);
		return 2;
	}
	else
	{
		return 1;
	}
	return 0;
}

int password_reset(char* username, char* password)
{
	FILE* fp;
	unsigned long long pw, pwt;
	char filename[30] = "users\\";
	char buffer[40];
	strcat(filename, username);

	if ((fp = fopen(filename, "r+")) == NULL)
	{
		show_error("���ļ���������", 1);
	}
	fprintf(fp, "%llu#%llu#", password_classified(password, 67), password_classified(password, 71));
	return 1;
}