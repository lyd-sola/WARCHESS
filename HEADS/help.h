#ifndef	_HELP_H_
#define	_HELP_H_
#include "struct.h"
void help_cartoon(void);
int step1(void);
int step2(void);
void step2_1(void);
void step2_2(void);

int step3(void);
void step3_1(void);
void step3_2(void);
void step3_3(void);
void step3_4(void);

int step4(MAP map);
int step4_1(void);
void step4_2(int side, MAP map);
void step421(int side);
void step422(int side, MAP map);
void step423(void);
void step424(unsigned source, MAP map);

int step5(MAP map);
void step5_1(MAP map);
void step5_2(MAP map);
void step5_3(MAP map);

int step6(MAP map);
void step6_1(void);
void step6_2(MAP map);
void step6_3(MAP map);
void step6_4(MAP map);
int Clcmap(DBL_POS* pos, MAP map);
void arrow(int x, int y, char* s1, char* s2, char* s3, int mode);
int helpwanttosay(char* btn1, char* btn2, char* s1, char* s2, int mode);


#endif