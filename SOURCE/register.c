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
	
	Clrmous();
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
		
		if(flag == 0 && mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_IN)	//����ע���
		{
			flag = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			frame(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5, 65535);
			Outtext(686, 480, "ע��", 48, 80, 63488);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		if(flag == 1 && mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_OUT)	//ȡ������
		{
			flag = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5, 65535);
			Outtext(686, 480, "ע��", 48, 80, 63488);
		}
		if(mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_IN_L)	//���ע���
		{
			if(regis_check(user, password, password_r) == 1)
			{
				user_creat(user, password);
				
				shadow_l(512-200, 384-100, 512+200, 384+100, 34429);
				Outtext(312+30, 284+40,"ע��ɹ���", 48, 80, 65535);
				Outtext(312+92, 484-60,"3�������¼����", 16, 25, 65535);
				delay(1000);
				Bar64k(312+92, 484-60, 312+92+25*8+16, 484-60+16, 34429);
				Outtext(312+92, 484-60,"2�������¼����", 16, 25, 65535);
				delay(1000);
				Bar64k(312+92, 484-60, 312+92+25*8+16, 484-60+16, 34429);
				Outtext(312+92, 484-60,"1�������¼����", 16, 25, 65535);
				delay(1000);
				return LOGIN;
			}
			else if(regis_check(user, password, password_r) == 0)
			{
				Outtext(312+92, 484-60,"���ڷ���ע�����", 16, 25, 65535);
				delay(1000);
				return REGIS;
			}
		}
		
		if(mouse_press(610, 165, 610 + 370, 165 + 50) == MOUSE_IN_L)					//�����û���
		{
			kbinput(610, 165, 610 + 370, 165 + 50, user, 1);
		}
		if(mouse_press(610, 165 + 100, 610 + 370, 165 + 50 + 100) == MOUSE_IN_L)					//��������
		{
			kbinput(610, 165 + 100, 610 + 370, 165 + 50 + 100, password, 0);
		}
		if(mouse_press(610, 165 + 200, 610 + 370, 165 + 50 + 200) == MOUSE_IN_L)					//�ٴ���������
		{
			kbinput(610, 165 + 200, 610 + 370, 165 + 50 + 200, password_r, 0);
		}
	}
}

void drawregi()
{
	Putbmp64k(0, 0, "BMP//lng.bmp");
	Bar64k(0,0,50,50, 64384);
	Outtext(100, 70, "WARCHESS", 48, 48, 65535);
	Outtext(100 + 2, 70 + 2, "WARCHESS", 48, 48, 65184);
	Outtext(510, 70, "ͨ��֤ע��", 48, 70, 0);

	shadow_l(686-15, 480-5, 686+128+15, 480+48+5, 65535);
	Outtext(686, 480,"ע��", 48, 80, 63488);

	frame(610, 165, 610+370, 165+50, 65535);   //�û���
	Outtext(610-168, 175,"�û���", 32, 59, 63488);
	Outtext(610+20, 185, "��λ���ڣ���д��ĸ������", 16, 22, 27469);
	
	frame(610, 165+100, 610+370, 165+50+100, 65535);  //����
	Outtext(610-168, 175+100,"����", 32, 118, 63488);
	Outtext(610+20, 185+100, "�������ִ�СдŶ", 16, 30, 27469);
	
	frame(610, 165+200, 610+370, 165+50+200, 65535);  //�ٴ�����
	Outtext(610-168, 175+200, "�ٴ�����", 32, 40, 63488);
	Outtext(610+20, 185+200, "�������뱣��һ��", 16, 30, 27469);
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
	short tot = 0;
	strcat(filename, username);
	
	//�����û��������뱣���ļ�
	if((fp = fopen(filename, "w")) == NULL)
	{
		show_error("�޷������û��浵", 1);
	}
	fprintf(fp, "%llu\n%llu", password_classified(password, 67), password_classified(password, 71));//�����漰�������⣬�������ע�͵�
	fclose(fp);
	
	//������ս��Ϣ�ļ�����ʵֻ���ļ�����һ��0
	sprintf(filename, "SAVES");//������ô�����ظ�·��
	filename[5] = '\\';
	if((fp = fopen(filename, "wb+")) == NULL)
	{
		show_error("�޷������û�ս����Ϣ�浵", 1);
	}
	fprintf(fp, "%1d", tot);
	//fwrite(&tot, 1, 1, fp);
	fclose(fp);
}

//����ͩ���棬���Ƶ��޸ģ���������
unsigned long long password_classified(char *p, int radix)//��ϣ�㷨���ַ�����ת��Ϊradix������ 
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
	Ȼ����Ҳ��һ�����������
	���������������������� XD
	*/
}

int regis_check(char *un, char *pw, char *pwr)
{
	FILE *fp;
	char filename[30] = "users\\";
	strcat(filename, un);
	
	if(*un == '\0')//δ�����û���
	{
		Outtext(620, 225, "�������û���", 16, 30, 63488);
	}
	else if(*pw == '\0')//δ��������
	{
		Outtext(620, 225+100, "����������", 16, 30, 63488);
	}
	else if(*pwr == '\0')//δ�ٴ���������
	{
		Outtext(620, 225+100+100, "���ٴ���������", 16, 30, 63488);
	}
	else if(strcmp(pw, pwr))//�����������벻һ��
	{
		fclose(fp);
		shadow_l(512-200, 384-100, 512+200, 384+100, 34429);
		Outtextxx(512-170, 384-75, 512-170+340, "�����������벻һ��", 32, 65535);
		return 0;
	}
	
	else if((fp=fopen(filename, "rb")) != NULL)//�û����Ѵ���
	{
		fclose(fp);
		shadow_l(512-200, 384-100, 512+200, 384+100, 34429);
		Outtextxx(512-170, 384-60, 512-170+340, "�û����Ѵ���", 32, 65535);
		return 0;
	}
	
	else //�ɹ�return LOGIN  ���ص�¼����
	{
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 2;
}


////�ܱ����⣬���ڸ������루Ҳ�����������룬��������ͬһ����
//int secret_question(char *user)
//{
//	//��Ϊ���뷨��ԭ�򣬴𰸽�֧��������ĸ������
//	/*int question1 = 0, question2 = 0;
//	char answer1[20] = "\0", answer2[20] = "\0";*/
//	//while (1)
//	//{
//	//	Newxy();
//	//	if (sq_check(question1, answer1, question2, answer2) == 1)
//	//	{
//	//		return LOGIN;
//	//	}
//	//	if (mouse_press(610, 165, 610 + 370, 165 + 50) == MOUSE_IN_L)					//�����û���
//	//	{
//	//		kbinput(610, 165, 610 + 370, 165 + 50, question1, 1);
//	//	}
//	//	if (mouse_press(610, 165 + 100, 610 + 370, 165 + 50 + 100) == MOUSE_IN_L)					//��������
//	//	{
//	//		kbinput(610, 165 + 100, 610 + 370, 165 + 50 + 100, answer1, 0);
//	//	}
//	//	if (mouse_press(610, 165 + 200, 610 + 370, 165 + 50 + 200) == MOUSE_IN_L)					//�ٴ���������
//	//	{
//	//		kbinput(610, 165 + 200, 610 + 370, 165 + 50 + 200, question2, 0);
//	//	}
//	//}
//}
//
//int drop_down_list(int x1, int y1, int x2, int y2, int num)
//{
//	//char* one, two, three, four;
//	//int result = 0, i;
//	//clrmous(MouseX, MouseY);//�������״̬����ֹ����
//	//for (i = 1; i <= num; i++)
//	//{
//	//	Bar64k(x1, y1, x2, y2+i*50, 65535);
//	//	switch (i)
//	//	{
//	//	case 1:
//	//		Outtext(x1+10, y1+(i-1)*50+5, one, 16, 20, 0);
//	//		break;
//	//	case 2:
//	//		Outtext(x1+10, y1+(i-1)*50+5, two, 16, 20, 0);
//	//		break;
//	//	case 3:
//	//		Outtext(x1+10, y1+(i-1)*50+5, three, 16, 20, 0);
//	//		break;
//	//	case 4:
//	//		Outtext(x1+10, y1+(i-1)*50+5, four, 16, 20, 0);
//	//		break;
//	//	default:
//	//		break;
//	//	}
//	//}
//}













