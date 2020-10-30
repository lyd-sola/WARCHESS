/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:login.h
Author:刘云笛、陈旭桐
Version:2.0
Description:登录界面
Function List：
	1.int login(char *user);
		登录界面核心函数
	2.void drawlogin(void);
		登录界面绘制
	3.void login_anime(void);
		登录动画
	4.int login_check(char *username, char *password);
		能否登陆检查，包括是否填写判断和用户名密码比对
	5.int quick_regi(void); 
		跳转注册按钮功能
	6.void forget_password(char* username);
		忘记密码功能
	7.void forget_draw(int q);
		忘记密码界面绘制
	8.int forget_fun(void);
		忘记密码函数
	9.int reset_check(char* answer, char* password, unsigned long long answert);
		重新设置密码确认
	10.int password_reset(char* username, char* password);
		重新设置密码
**********************************************************/
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

