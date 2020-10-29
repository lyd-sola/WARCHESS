#ifndef _REGISTER_h_
#define _REGISTER_h_

int register_(void);										//注册界面核心函数
void drawregi(void);										//绘制注册界面
void regi_sq_draw(void);
void user_creat(char *username, char *password, int q, char* answer);			//建立用户文件
unsigned long long password_classified(char *p, int radix);	//加密用户密码
int regis_check(char *un, char *pw, char *pwr);				//判断能否注册，包括填写判断和两次密码输入比对
void drop_down_list(int x1, int y1, int x2, int y2, int num);
int list_choose(int x1, int y1, int x2, int y2, int num);
int secret_question(char* user, char* password);
int sq_check(int q, char* answer);
int list_func(int x1, int y1, int x2, int y2, int num, int* q);
#endif
