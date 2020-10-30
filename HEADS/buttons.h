/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:buttons.h
Author:���Ƶѡ�����ͩ
Version:1.0
Description:��ť����
				
Function List��
	1��void Button(int y1, char* s, int color, int color2);
		���Ƽⰴť
	2��int Sharp_button(int y0, char* s, char* s_change, int color, int color2);
		�ⰴť���ܺ���
	3��void attack_button(char* s, int color);
		������ť����
	4��void stay_button(char* s, int color);
		פ����ť����
	5��void move_button(char *s, int color);
		�ƶ���ť����
	6��void del_button(int color);
		ɾ����ť����
	7��void nextr_button(int color);
		��һ�غϰ�ť����
	8��int atk_btn_fun(char* s, int color, int color_c);
		������ť���ܺ���
	9��int stay_btn_fun(char* s, int color, int color_c);
		פ����ť���ܺ���
	10��int nxt_btn_fun(int color, int color_c);
		��һ�غϰ�ť���ܺ���
	11��int move_btn_fun(int color, int color_c, char *s);
		�ƶ���ť���ܺ���
	12��int del_btn_fun(int color, int color_c);
		ɾ����ť���ܺ���
	13��void rect_circle(int x1, int y1, int x2, int y2, int color);
		����Բ�Ƿ���
	14��void rect_button(int x1, int y1, int x2, int y2, char* s, int color); 
		���ΰ�ť����
	15��void rect_btn_frame(int x1, int y1, int x2, int y2, int color);
		���ΰ�ť�ӿ�
	16��int rec_btn_fun(int x1, int y1, int x2, int y2, int color);
		���ΰ�ť���ܺ���
	17��void battle_exit(int x, int y);
		�����˳�ս����ť
	18��void save_btn(int color);
		���Ʊ��水ť
	19��void exit_btn(int color);
		�����˳�ս����ť
	20��void option_btn(int color);
		ѡ��˵���ť����
	21��void draw_opts(void);
		ѡ��˵�����
	22��int opts_fun(void);
		ѡ��˵����ܺ���
**********************************************************/
#ifndef	_BUTTONS_H_
#define	_BUTTONS_H_

#include "struct.h"

void Button(int y1, char* s, int color, int color2);

int Sharp_button(int y0, char* s, char* s_change, int color, int color2);

void attack_button(char* s, int color);//������ť

void stay_button(char* s, int color);//פ����ť

void move_button(char *s, int color);//�ƶ���ť

void del_button(int color);//ɾ����ť

void nextr_button(int color);//��һ�غϰ�ť

int atk_btn_fun(char* s, int color, int color_c);

int stay_btn_fun(char* s, int color, int color_c);

int nxt_btn_fun(int color, int color_c);

int move_btn_fun(int color, int color_c, char *s);
int del_btn_fun(int color, int color_c);

void rect_circle(int x1, int y1, int x2, int y2, int color);

void rect_button(int x1, int y1, int x2, int y2, char* s, int color); //���ΰ�ť

void rect_btn_frame(int x1, int y1, int x2, int y2, int color);

int rec_btn_fun(int x1, int y1, int x2, int y2, int color);

void battle_exit(int x, int y);

void save_btn(int color);

void exit_btn(int color);

void option_btn(int color);

void draw_opts(void);

int opts_fun(void);

#endif