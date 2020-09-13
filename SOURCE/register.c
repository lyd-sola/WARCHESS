/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: register.c
author: ����ͩ�����Ƶ�
version: 1.2
Description: ע�����
date:2020/9/8

������־
9.9		�Ż���ע�����
		��������������㷨
		�����˽��û���Ϣд���ļ��ĺ���
		�����˼���Ƿ���ȷ����ĺ���
		����˽���kbinput����֮ǰ�����������ݵ�bug
		
����Ŀ¼
1.register_:			ע�ắ��
2.drawregi:				����ע����溯��
3.user_creat:			�����û�����
4.password_classified:	�����ļ����ܺ���
5.regis_check��			����Ƿ���ȷ���뺯��
******************************************************************/
#include "common.h"

int register_()
{
	char user[10] = "", password[20] = "", password_r[20] = "";
	int flag = 0;	//��ֹ�ظ�����
	
	clrmous(MouseX, MouseY);
	drawregi();
	
	
	while(1)
	{
		Newxy();
		if(bioskey(1))
		{
			getch();
		}//��ֹ��������������Ӱ������
	
		if(mouse_press(0, 0, 50, 50) == MOUSE_IN_L)//������ҳ��
		{
			return HOMEPAGE;
		}
		
		if(flag == 0 && mouse_press(256-15, 390-15, 384+15, 422+15) == MOUSE_IN)	//����ע���
		{
			flag = 1;
			frame(256-15, 390-15, 384+15, 422+15, 65535);
			Outtext(256, 380,"ע��", 48, 80, 30513);
		}
		if(flag == 1 && mouse_press(256-15, 390-15, 384+15, 422+15) == MOUSE_OUT)	//ȡ������
		{
			flag = 0;
			shadow_l(256-15, 390-15, 384+15, 422+15, 65535);
			Outtext(256, 380,"ע��", 48, 80, 30513);
		}
		if(mouse_press(256-15, 390-15, 384+15, 422+15) == MOUSE_IN_L)	//���ע���
		{
			if(regis_check(user, password, password_r))
			{
				user_creat(user, password);
				
				shadow_l(320-200, 240-100, 320+200, 240+100, MAGENTA);
				Outtext(120+30, 140+40,"ע��ɹ���", 48, 80, 65535);
				Outtext(120+92, 340-60,"3�������¼����", 16, 25, 65535);
				delay(1000);
				Bar64k(120+92, 340-60, 120+92+25*8+16, 340-60+16, MAGENTA);
				Outtext(120+92, 340-60,"2�������¼����", 16, 25, 65535);
				delay(1000);
				Bar64k(120+92, 340-60, 120+92+25*8+16, 340-60+16, MAGENTA);
				Outtext(120+92, 340-60,"1�������¼����", 16, 25, 65535);
				delay(1000);
				return LOGIN;
			}
			Bar64k(120+92, 340-60, 120+92+25*8+16, 340-60+16, MAGENTA);
			Outtext(120+92, 340-60,"���ڷ���ע�����", 16, 25, 65535);
			delay(1000);
			return REGIS;
		}
		
		if(mouse_press(180, 165, 180+370, 165+50) == MOUSE_IN_L)					//�����û���
		{
			kbinput(180, 165, 180+370, 165+50, user, 1);
		}
		if(mouse_press(180, 165+70, 180+370, 165+50+70) == MOUSE_IN_L)					//��������
		{
			kbinput(180, 165+70, 180+370, 165+50+70, password, 0);
		}
		if(mouse_press(180, 165+140, 180+370, 165+50+140) == MOUSE_IN_L)					//�ٴ���������
		{
			kbinput(180, 165+140, 180+370, 165+50+140, password_r, 0);
		}
	}
}

void drawregi()
{
	//Bar64k(0, 0, 1024, 768, 34847);
	Putbmp64k(0, 0, "BMP//lng.bmp");
	shadow_l(70, 30, 70+500, 30+90, 65535);
	shadow_l(256-15, 390-15, 384+15, 422+15, 65535);
	Bar64k(0,0,50,50, 64384);
	frame(180, 165, 180+370, 165+50, 65535);             //�û���
	Outtext(12, 175,"�û���", 32, 59, 30513);
	Outtext(200, 185, "��λ���ڣ���д��ĸ������", 16, 22, 27469);
	
	frame(180, 165+70, 180+370, 165+50+70, 65535);  //����
	Outtext(12, 175+70,"����", 32, 118, 30513);
	Outtext(200, 185+70, "�������ִ�СдŶ", 16, 30, 27469);
	
	frame(180, 165+140, 180+370, 165+50+140, 65535);  //�ٴ�����
	Outtext(12, 175+140, "�ٴ�����", 32, 40, 30513);
	Outtext(200, 185+140, "�������뱣��һ��", 16, 30, 27469);

	Outtext(85,50,"��ӭע�᱾ϵͳ", 48, 70, 31);
	Outtext(256, 380,"ע��", 48, 80, 30513);
}

/*******************************
���û���������
Description:�����û��ļ�����ս�����ļ�
Author: ���Ƶ�
*******************************/
void user_creat(char *username, char *password)
{
	FILE *fp;
	char filename[30] = "USERS\\";
	
	strcat(filename, username);
	strcat(filename, ".txt");
	
	/***************�����û��������뱣���ļ��������������ڱ���ɾ���Ϣ�ȣ�********************/
	if((fp = fopen(filename, "w")) == NULL)
	{
		//outtextxyc(10,10,"Can NOT creat user file", RED);    ********************************���ң����ң�����������������****************
		delay(6000);
		exit(1);
	}
	fprintf(fp, "%llu\n%llu", password_classified(password, 67), password_classified(password, 71));//�����漰�������⣬�������ע�͵�
	fclose(fp);
	
	/***********************������ս��Ϣ�ļ�����ʵֻ���ļ�����һ��0***************************/
	sprintf(filename, "SAVES");//������ô�����ظ�·��
	filename[5] = '/';
	if((fp = fopen(filename, "w")) == NULL)
	{
		//outtextxyc(10,10,"Can NOT creat battle file", RED);	********************************���ң����ң�����������������****************
		delay(6000);
		exit(1);
	}
	fprintf(fp, "0\n");
	fclose(fp);
}

//����ͩ���棬���Ƶ��޸ģ���������
unsigned long long password_classified(char *p, int radix)//�ַ�����ת��Ϊradix������ 
{
	unsigned long long part1 = 0, part2 = 0;
	int length = strlen(p), i, tmp;
	//�˴�Ӧ��ע��
	for(i = 0; i < length; i++)
	{   
        part1 *= radix;
		part2 *= radix;//��Ȼ������� 
		if(isupper(p[i]) == 1)//��д 
		{
			tmp = p[i] - 'A' + 11;
			part1 += tmp;
		}
		else if(islower(p[i]) == 1)//Сд 
		{
			tmp = p[i] - 'a' + 37;
			part1 += tmp;
		}
		else if(p[i] == '0')
		{
			tmp = 10;
			part1 += tmp;
		}
		else//����1-9 
		{
			tmp = p[i] - '0';
			part1 += tmp;
		}
		
		//����
		if(isupper(p[length-1-i]) == 1)
		{
			tmp = p[length-1-i] - 'A' + 11;
			part2 += tmp;
		}
		else if(islower(p[length-1-i]) == 1)
		{
			tmp = p[length-1-i] - 'a' + 37;
			part2 += tmp;
		}
		else if(p[length-1-i] == '0')
		{
			tmp = 10;
			part2 += tmp;
		}
		else
		{
			tmp = p[length-1-i] - '0';
			part2 += tmp;
		}	
	}
	return part1 *(part2 * radix);
	/*
	���㿴�������ʱ�����ǵļ���ϵͳ�ͱ���ʶ����QAQ
	�ɶ�
	Ȼ����Ҳ�㲻�����루��������ʽ�ֽ⣬����np�����⣩
	����������������������XD
	*/
}

int regis_check(char *un, char *pw, char *pwr)
{
	FILE *fp;
	char filename[30] = "users\\";
	strcat(filename, un);
	strcat(filename, ".txt");
	
	if(*un == '\0')//δ�����û���
	{
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "�������û���", 32, 65535);
		return 0;
	}
	else if(*pw == '\0')//δ��������
	{
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "����������", 32, 65535);
		return 0;
	}
	else if(*pwr == '\0')//δ�ٴ���������
	{
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "���ٴ���������", 32, 65535);
		return 0;
	}
	else if(strcmp(pw, pwr))//�����������벻һ��
	{
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "�����������벻һ��", 32, 65535);
		return 0;
	}
	
	else if((fp=fopen(filename, "r")) != NULL)//�û����Ѵ���
	{
		fclose(fp);
		shadow_l(320-200, 240-100, 320+200, 240+100, 5);
		Outtextxx(150, 180, 150+340, "�û����Ѵ���", 32, 65535);
		return 0;
	}
	
	else //�ɹ�return LOGIN  ���ص�¼����
	{
		fclose(fp);
		return 1;
	}
}












