#ifndef __SAVE_H__
#define __SAVE_H__

int savefile_creat(char *user);//如果返回1则存档满，快速创建失败			
void seek_savinfo(FILE* fp, short n, const POS pos);//fp 指向用户对战信息文件的指针
void savefile_init(FILE* fp, short n);//n为当前存档号										

#endif