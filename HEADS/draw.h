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
void Lightbar(int x1, int y1, int x2, int y2, float drgb);
void Bar64k_radial_re(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);
void Bar64k_radial(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);

void Line45(int x1, int y1, int x2, int y2, unsigned int color);
void Icon_draw(POS pos, int side);
void Icon_builder(POS pos, int side);
void Icon_inf(POS pos, int side);
void Icon_tank(POS pos, int side);
void Icon_super(POS pos, int side);
void Icon_arti(POS pos, int side);
void diamond(int x1, int y1, int x2, int y2, int x3, int y3, int color);

void banner(int x1, int y1, int length);
void photo(int x1, int y1, int x2, int y2);
void draw_bomb(int x, int y, double i);

int putbmp_partial(int x1, int y1, int x2, int y2, char* s);
#endif