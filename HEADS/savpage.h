/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:battle.h
Author:���Ƶѡ�����ͩ
Version:
Description:ս������

Function List��
	1.int savpage(char *user, int* save_num, int* mode);
		�浵����������
	2.void savpage_draw(FILE* fp);
		�浵������ƺ���
	3.void draw_saves(int x, int y, int color, FILE* fp, int save_num);
		��ʾ�浵��Ϣ
	4.void savpage_btns(int i);
		�浵���水ť����
**********************************************************/
#ifndef  _SAVPAGE_H_
#define  _SAVPAGE_H_

int savpage(char *user, int* save_num, int* mode);
void savpage_draw(FILE* fp);
void draw_saves(int x, int y, int color, FILE* fp, int save_num);
void savpage_btns(int i);
int save1(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save2(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save3(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save4(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save5(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save6(FILE* fp, int* flag, int tot, int* mode, int* save_num);
#endif