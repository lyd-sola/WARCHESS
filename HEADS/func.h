/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:battle.h
Author:���Ƶѡ�����ͩ
Version:2.0
Description:�������Է���Ĺ����Ժ���					�޸�δ���
				

Function List��
	1.void show_error(char* msg, int mode);
		��ʾ������Ϣ������msgΪ������Ϣ��mode 1Ϊ�޴����رճ���0ΪС���󡢽�����
	2.int Sharp_button(int y0, char* s, char* s_change, int color, int color2);
		mainmenu���水ť���ܺ���������ʵ�����а�ť���ܣ������ʱ����1
**********************************************************/
#ifndef	_FUNCITONS_H_
#define	_FUNCITONS_H_

void show_error(char* msg, int mode);
int Sharp_button(int y0, char* s, char* s_change, int color, int color2);

#endif