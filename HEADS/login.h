#ifndef _Loginin_H_
#define _Loginin_H_

int login(char *user);										//登录界面核心函数
void drawlogin(void);										//登录界面绘制
void login_anime(void);
int login_check(char *username, char *password);			//能否登陆检查，包括是否填写判断和用户名密码比对
int quick_regi(void); //跳转注册按钮功能
void forget_password(char* username);
void forget_draw(int q);
int forget_fun(void);
int reset_check(char* answer, char* password, unsigned long long answert);
int password_reset(char* username, char* password);
#endif

