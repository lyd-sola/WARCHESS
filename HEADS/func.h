/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:battle.h
Author:���Ƶѡ�����ͩ
Version:2.0
Description:�������Է���Ĺ����Ժ���					�޸�δ���
				

Function List��
	1.void draw_show_error(void);
		���Ʊ������
	2.void show_error(char* msg, int mode);
		��ʾ������Ϣ������msgΪ������Ϣ��mode 1Ϊ�޴����رճ���0ΪС���󡢽�����
	3.void show_msg(char* msg, char* msg2);
		��ʾ��ս�����·���Ϣ
	4.int msgbar(char* btn1, char* btn2, char* s1, char* s2);
		����ѯ��
**********************************************************/
#ifndef	_FUNCITONS_H_
#define	_FUNCITONS_H_

void draw_show_error(void);

void show_error(char* msg, int mode);

void show_msg(char* msg, char* msg2);

int msgbar(char* btn1, char* btn2, char* s1, char* s2);

#endif