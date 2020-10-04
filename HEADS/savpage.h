#ifndef  _SAVPAGE_H_
#define  _SAVPAGE_H_

int savpage(char *user, short* save_num, short* mode);
void savpage_draw(FILE* fp);
void draw_saves(int x, int y, int color, FILE* fp, short save_num);

#endif