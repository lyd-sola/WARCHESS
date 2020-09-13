#ifndef _DRAW_h_
#define _DRAW_h_

void shadow(int x1, int y1, int x2, int y2, int color1, int color2);  //带阴影的文本框
void shadow_l(int x1, int y1, int x2, int y2, int color); //带大阴影的文本框
void frame(int x1, int y1, int x2, int y2, int color); //带边框的文本框
void file_draw(int x1, int y1, int x2, int y2); //绘制档案图形
int Outtextxx(int x1, int y, int x2, char *s,int flag, int color); //根据两点坐标输出汉字

void GetBackground(int left, int top, int right, int bottom, short *buffer);
void PutBackground(int left, int top, int right, int bottom, short *buffer);
unsigned int Lightcolor(unsigned int colorbf, float drgb);
void Lightpixel(int x, int y, float drgb);
void Lightline(int x1, int y1, int x2, int y2, float drgb);
void Lightbar(int x1, int y1, int x2, int y2, float drgb);
void Bar64k_radial_re(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);
void Bar64k_radial(int x1, int y1, int x2, int y2, unsigned int color, int fill_time);
void Button(int y1, char* s, int color, int color2);

#endif