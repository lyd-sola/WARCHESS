/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS
file_name: register.c
author: 陈旭桐、刘云笛
version: 1.2
Description: 注册界面
date:2020/9/8

更新日志
9.9		优化了注册界面
		增加了密码加密算法
		增加了将用户信息写入文件的函数
		增加了检测是否正确输入的函数
		解决了进入kbinput函数之前缓冲区有内容的bug

函数目录
1.int register_(void);										
	注册界面核心函数
2.void drawregi(void);										
	绘制注册界面
3.void regi_sq_draw(void);
	密保问题界面绘制
4.void user_creat(char *username, char *password, int q, char* answer);			
	建立用户文件
5.unsigned long long password_classified(char *p, int radix);	
	加密用户密码
6.int regis_check(char *un, char *pw, char *pwr);				
	判断能否注册，包括填写判断和两次密码输入比对
7.void drop_down_list(int x1, int y1, int x2, int y2, int num);
	绘制下拉菜单
8.int list_choose(int x1, int y1, int x2, int y2, int num);
	确定下拉菜单点选对象
9.int secret_question(char* user, char* password);
	密保问题核心函数
10.int sq_check(int q, char* answer);
	判断密保问题填写是否正确
11.int list_func(int x1, int y1, int x2, int y2, int num, int* q);
	下拉菜单相关函数
******************************************************************/

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
