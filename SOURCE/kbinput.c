/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: kbinput.c
author: ���Ƶ�
version: 2
Description: ��������
date:2020/9/9

������־
9.9		������������⣨ʵ�ʲ��ڱ��ļ��У�
		����ͼ������Ϊ�Զ����ͼ������������һ����������
		ʵ���������������˸�ͻس�
		���������ϲ�Ϊһ��������

����Ŀ¼
1.kbinput:	�������벢��ʾԭ��
2.kbinput:	�������벢��ʾ�Ǻ�
******************************************************************/
#include "common.h"
#define KB_SIZE 32				//textsize:32*32
#define KB_FONT TRIPLEX_FONT	//textstyle: TRIPLE_FONT
/*
x1y2, x2y2���������
length:����򳤶�
mode 1���ԭ�ģ�0���*
s ����������
*/
void kbinput(int x1, int y1, int x2, int y2, char *s, int mode)
{
	int i = 0;//����������
	int length = (x2 - x1) / KB_SIZE;//�������
	char ch[2] = {0, 0};
	
	clrmous(MouseX, MouseY);//�������״̬����ֹ����
	frame(x1, y1, x2, y2, 65535);	//����ԭ������
	s[0] = 0;				//���ԭ������
	Line64k(x1+5, y2-5-KB_SIZE, x1+5, y2-5, 44373);
	
	while(1)
	{
		Newxy();
		
		if(mouse_press(x1, y1, x2, y2) == 3)//�ڽ����������˳�����
		{
			Line64k(x1+5+i*KB_SIZE, y2-5-KB_SIZE, x1+5+i*KB_SIZE, y2-5, 65535);
			return ;
		}
		
		if(bioskey(1))
		{			
			*ch = bioskey(0);
			if(isalnum(*ch) && i < length)//����
			{
				s[i] = *ch;
				s[i+1] = 0;
				*ch = mode * ch[0] + !mode * '*';		//���������ϲ�Ϊһ���ĺ������
				Line64k(x1+5+i*KB_SIZE, y2-5-KB_SIZE, x1+5+i*KB_SIZE, y2-5, 65535);
				Outtext(x1+5+i*KB_SIZE, y2-5-KB_SIZE, ch, KB_SIZE, 40, 44373);
				i++;
				Line64k(x1+5+i*KB_SIZE, y2-5-KB_SIZE, x1+5+i*KB_SIZE, y2-5, 44373);
			}
			
			else if(*ch == '\r')//�س���������
			{
				Line64k(x1+5+i*KB_SIZE, y2-5-KB_SIZE, x1+5+i*KB_SIZE, y2-5, 65535);
				return ;
			}
			
			else if(*ch == '\b' && i)//�˸�
			{
				Line64k(x1+5+i*KB_SIZE, y2-5-KB_SIZE, x1+5+i*KB_SIZE, y2-5, 65535);
				i--;
				Bar64k(x1+5+i*KB_SIZE, y2-5-KB_SIZE, x1+5+i*KB_SIZE+KB_SIZE, y2-5-KB_SIZE+KB_SIZE, 65535);
				Line64k(x1+5+i*KB_SIZE, y2-5-KB_SIZE, x1+5+i*KB_SIZE, y2-5, 44373);
				s[i] = 0;
			}
		}
	}
}