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
	int rcheck = 0;
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
			Outtext(686, 480, "����", 48, 80, 63488);
			Mouse_savebk2();//�������״̬����ֹ����
		}
		if(flag == 1 && mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_OUT)	//ȡ������
		{
			flag = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5, 65535);
			Outtext(686, 480, "����", 48, 80, 63488);
		}
		if(mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_IN_L)	//���������
		{
			if((rcheck = regis_check(user, password, password_r)) == 1)
			{
				//user_creat(user, password);
				if(secret_question(user, password)==1)
					return LOGIN;
			}
			else if(rcheck == 0)
			{
				Outtext(312+92, 484-60,"���ڷ���ע�����", 16, 25, 65535);
				delay(2000);
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
	Outtext(686, 480,"����", 48, 80, 63488);

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
void user_creat(char *username, char *password, int q, char* answer)
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
	fprintf(fp, "\n%d\n%llu", q, password_classified(answer, 71));//�����漰�������⣬�������ע�͵�
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
	else if ((fp = fopen(filename, "rb")) != NULL)//�û����Ѵ���
	{
		fclose(fp);
		shadow_l(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170, 384 - 60, 512 - 170 + 340, "�û����Ѵ���", 32, 65535);
		return 0;
	}
	else if(strcmp(pw, pwr))//�����������벻һ��
	{
		fclose(fp);
		shadow_l(512-200, 384-100, 512+200, 384+100, 34429);
		Outtextxx(512-170, 384-75, 512-170+340, "�����������벻һ��", 32, 65535);
		return 0;
	}
	else if (strlen(un) < 4)
	{
		shadow_l(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170, 384 - 60, 512 - 170 + 340, "�û����賤����λ", 32, 65535);
		return 0;
	}
	else if (strlen(pw) < 4)
	{
		shadow_l(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170, 384 - 60, 512 - 170 + 340, "�����賤����λ", 32, 65535);
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


//�ܱ����⣬���ڸ������루Ҳ�����������룬��������ͬһ����
int secret_question(char *user, char *password)
{
	//��Ϊ���뷨��ԭ�򣬴𰸽�֧��������ĸ������
	int q = 0, flag = 0;
	char answer[20] = "";
	Clrmous();
	regi_sq_draw();
	while (1)
	{
		Newxy();
		if ((flag = list_func(610, 280, 610 + 370, 280 + 50, 5, &q)) == 0)
		{
			Outtext(610 + 5, 380 + 5, answer, 32, 40, 44373);
		}
		else if (flag == 1)
		{
			answer[0] = 0;
		}
		if (mouse_press(610, 280 + 100, 610 + 370, 280 + 50 + 100) == MOUSE_IN_L)
		{
			kbinput(610, 280 + 100, 610 + 370, 280 + 50 + 100, answer, 2);
		}
		if (mouse_press(686 - 15, 490 - 15, 814 + 15, 522 + 15) == MOUSE_IN_L)
		{
			if (sq_check(q, answer) == 1)
			{
				user_creat(user, password, q, answer);
				shadow_l(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
				Outtext(312 + 30, 284 + 40, "ע��ɹ���", 48, 80, 65535);
				Outtext(312 + 92, 484 - 60, "3�������¼����", 16, 25, 65535);
				delay(1000);
				Bar64k(312 + 92, 484 - 60, 312 + 92 + 25 * 8 + 16, 484 - 60 + 16, 34429);
				Outtext(312 + 92, 484 - 60, "2�������¼����", 16, 25, 65535);
				delay(1000);
				Bar64k(312 + 92, 484 - 60, 312 + 92 + 25 * 8 + 16, 484 - 60 + 16, 34429);
				Outtext(312 + 92, 484 - 60, "1�������¼����", 16, 25, 65535);
				delay(1000);
				return 1;
			}
		}
		if (mouse_press(0, 0, 50, 50) == MOUSE_IN_R)
		{
			exit(0);
		}
	}
}

int sq_check(int q, char* answer)
{
	if (q == 0)//δ�����û���
	{
		Outtext(620, 340, "��ѡ������", 16, 30, 63488);
	}
	else if (*answer == '\0')//δ��������
	{
		Outtext(620, 440, "�������", 16, 30, 63488);
	}
	else
	{
		return 1;
	}
	return 0;
}
/******y1��y2����ȣ������������ˮƽ�������꣬numΪ����չ��������*******/
void drop_down_list(int x1, int y1, int x2, int y2, int num)
{
	int result = 0, i;
	if (y1 != y2)
		return;
	Clrmous();//�������״̬����ֹ����
	Bar64k(x1, y1, x2, y2+num*50, 65535);
	for (i = 1; i <= num; i++)
	{
		rectangle64k(x1, y1+(i-1)*50, x2, y2+i*50, 0);
		switch (i)
		{
		case 1:
			Outtext(x1+10, y1+(i-1)*50+13, "���������ǣ�", 24, 28, 44373);
			break;
		case 2:
			Outtext(x1+10, y1+(i-1)*50+13, "�����֤������ʮλ�ǣ�", 24, 28, 44373);
			break;
		case 3:
			Outtext(x1+10, y1+(i-1)*50+13, "������������ǣ�", 24, 28, 44373);
			break;
		case 4:
			Outtext(x1+10, y1+(i-1)*50+13, "����һλ���˵������ǣ�", 24, 28, 44373);
			break;
		default:
			break;
		}
	}
}

int list_choose(int x1, int y1, int x2, int y2, int num)
{
	int i = 0;
	drop_down_list(x1, y1, x2, y2, num);
	while (1)
	{
		Newxy();
		if (mouse_press(x1, y1, x2, y2 + num * 50) == MOUSE_IN_L)
		{
			i = (MouseY-y1)/50+1;
			return i;
		}
		else if (press == 1)
		{
			return i;
		}
	}
}

/******y1,y2�Ĳ����50Ч�����*******/
int list_func(int x1, int y1, int x2, int y2, int num, int *q)
{
	if (mouse_press(x2-50, y1, x2, y1+50) == MOUSE_IN_L)
	{
		if ((*q = list_choose(x1, y2, x2, y2, 4)) != 0)
		{
			Clrmous();
			Bar64k(x1, y1, x2, y2, 65535);
			rectangle64k(x1, y1, x2, y2, 0);
			Bar64k(x2 - 50, y1, x2, y1 + 50, 33808);
			switch (*q)
			{
			case 1:
				Outtext(x1+10, y1+13, "���������ǣ�", 24, 28, 44373);
				break;
			case 2:
				Outtext(x1+10, y1+13, "�����֤������ʮλ�ǣ�", 24, 28, 44373);
				break;
			case 3:
				Outtext(x1+10, y1+13, "������������ǣ�", 24, 28, 44373);
				break;
			case 4:
				Outtext(x1+10, y1+13, "����һλ���˵������ǣ�", 24, 28, 44373);
				break;
			default:
				break;
			}
			putbmp_partial(x1, y2, x2, y2 + num * 50, "BMP//lng.bmp");
			frame(610, 280 + 100, 610 + 370, 280 + 50 + 100, 65535);  	//����
			Outtext(500, 390, "��", 32, 62, 63488);
			Outtext(610 + 20, 380 + 15, "ֻ����������ĸ������", 16, 30, 0);
			shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
			Outtext(686, 480, "ע��", 48, 80, 63488);
			return 1;
		}
		else
		{
			putbmp_partial(x1, y2, x2, y2 + num * 50, "BMP//lng.bmp");
			frame(610, 280 + 100, 610 + 370, 280 + 50 + 100, 65535);  	//����
			Outtext(500, 390, "��", 32, 62, 63488);
			shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
			Outtext(686, 480, "ע��", 48, 80, 63488);
			//Outtext(610 + 20, 380 + 15, "ֻ����������ĸ������", 16, 30, 0);
			return 0;
		}
	}
	return 2;
}

void regi_sq_draw()
{
	putbmp_partial(610-168, 165, 610+370, 165+50+200, "BMP//lng.bmp");
	frame(610, 280, 610 + 370, 280 + 50, 65535);             //�û���
	Outtext(500, 290, "����", 32, 62, 63488);
	Outtext(610 + 20, 280 + 15, "ѡ��һ���ܱ�����", 16, 30, 0);

	frame(610, 280 + 100, 610 + 370, 280 + 50 + 100, 65535);  	//����
	Outtext(500, 390, "��", 32, 62, 63488);
	Outtext(610 + 20, 380 + 15, "ֻ����������ĸ������", 16, 30, 0);

	shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
	Outtext(686, 480, "ע��", 48, 80, 63488);
}





