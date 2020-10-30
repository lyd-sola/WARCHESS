/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:draw.h
Author:刘云笛、陈旭桐
Version:1.0
Description:各种绘图函数


Function List：
	1.void shadow(int x1, int y1, int x2, int y2, int color1, int color2);  
		带阴影的文本框
	2.void shadow_l(int x1, int y1, int x2, int y2, int color); 
		带大阴影的文本框
	3.void add_shadow(int x1, int y1, int x2, int y2, int size);
		给矩形添加阴影
	4.void frame(int x1, int y1, int x2, int y2, int color);
		带边框的文本框
	5.void file_draw(int x1, int y1, int x2, int y2);
		绘制档案图形
	6.int Outtextxx(int x1, int y, int x2, char *s,int flag, int color);
		根据两点坐标输出汉字
	7.void Outwithint(int x, int y, char *former, int a, char *latter, int size, int part, int color);
	8.void Outwithint2(int x1, int y, int x2, char* former, int a, char* latter, int size, int color);
	9.char* textwithint(char* former, int a, char* latter);

	10.void GetBackground(int left, int top, int right, int bottom, unsigned *buffer);
		存储某一范围背景图
	11.void PutBackground(int left, int top, int right, int bottom, unsigned *buffer);
		放回某一范围背景图
	12.unsigned int Lightcolor(unsigned int colorbf, float drgb);
		增加白度函数
	13.void Lightpixel(int x, int y, float drgb);
		增加某一点白度
	14.void Lightline(int x1, int y1, int x2, int y2, float drgb);
		增加某一条线白度
	15.void Lightbar(int x1, int y1, int x2, int y2);
		增加一个矩形的白度
	16.void Bar64k_radial_re(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);
		反向放射状画矩形
	17.void Bar64k_radial(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);
		放射状画矩形
	18.void Line45(int x1, int y1, int x2, int y2, unsigned int color);
		绘制45度斜线
	19.void Icon_draw(POS pos, int side);
		绘制盾牌（兵种背景）
	20.void Icon_builder(POS pos, int side);
		绘制工兵
	21.void Icon_inf(POS pos, int side);
		绘制步兵
	22.void Icon_tank(POS pos, int side);
		绘制坦克
	23.void Icon_super(POS pos, int side);
		绘制超级兵
	24.void Icon_arti(POS pos, int side);
		绘制炮兵
	25.void stay_draw(POS center);
		绘制驻扎状态
	26.void diamond(int x1, int y1, int x2, int y2, int x3, int y3, int color);
		绘制菱形
	27.void banner(int x1, int y1, int length);
		绘制缎带
	28.void photo(int x1, int y1, int x2, int y2);
		绘制头像
	29.void draw_bomb(int x, int y, double i);
		绘制攻击火焰
	30.void collection_draw(POS center, int side);
		绘制采集站
	31.void medical_draw(POS center);
		绘制医疗站
	32.int putbmp_partial(int x1, int y1, int x2, int y2, char* s);
		部分还原贴图
**********************************************************/

#ifndef _DRAW_h_
#define _DRAW_h_

#include "struct.h"

void shadow(int x1, int y1, int x2, int y2, int color1, int color2);  //带阴影的文本框
void shadow_l(int x1, int y1, int x2, int y2, int color); //带大阴影的文本框
void add_shadow(int x1, int y1, int x2, int y2, int size); //给矩形添加阴影
void frame(int x1, int y1, int x2, int y2, int color); //带边框的文本框
void file_draw(int x1, int y1, int x2, int y2); //绘制档案图形
int Outtextxx(int x1, int y, int x2, char *s,int flag, int color); //根据两点坐标输出汉字
void Outwithint(int x, int y, char *former, int a, char *latter, int size, int part, int color);
void Outwithint2(int x1, int y, int x2, char* former, int a, char* latter, int size, int color);
char* textwithint(char* former, int a, char* latter);

void GetBackground(int left, int top, int right, int bottom, unsigned *buffer);
void PutBackground(int left, int top, int right, int bottom, unsigned *buffer);
unsigned int Lightcolor(unsigned int colorbf, float drgb);
void Lightpixel(int x, int y, float drgb);
void Lightline(int x1, int y1, int x2, int y2, float drgb);
void Lightbar(int x1, int y1, int x2, int y2);
void Bar64k_radial_re(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);
void Bar64k_radial(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);

void Line45(int x1, int y1, int x2, int y2, unsigned int color);
void Icon_draw(POS pos, int side);
void Icon_builder(POS pos, int side);
void Icon_inf(POS pos, int side);
void Icon_tank(POS pos, int side);
void Icon_super(POS pos, int side);
void Icon_arti(POS pos, int side);
void stay_draw(POS center);
void diamond(int x1, int y1, int x2, int y2, int x3, int y3, int color);

void banner(int x1, int y1, int length);
void photo(int x1, int y1, int x2, int y2);
void draw_bomb(int x, int y, double i);
void collection_draw(POS center, int side);
void medical_draw(POS center);

int putbmp_partial(int x1, int y1, int x2, int y2, char* s);
#endif