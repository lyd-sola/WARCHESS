#ifndef	_HELP_H_
#define	_HELP_H_
#include "struct.h"
void help_cartoon(void);
int step1(MAP map);
int step2(MAP map);
void arrow(int x, int y, char* s1, char* s2, char* s3, int mode);
short helpwanttosay(char* btn1, char* btn2, char* s1, char* s2, int mode);

#endif