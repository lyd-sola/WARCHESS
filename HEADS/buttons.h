/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:buttons.h
Author:���Ƶѡ�����ͩ
Version:
Description:��ť����
				

Function List��
	
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