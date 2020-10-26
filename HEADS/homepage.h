#ifndef __HOMEPAGE
#define __HOMEPAGE

int homepage(void);			//主页核心函数
void draw_h_page(void);		//主页界面绘制
void homepg_button(int x1, int y1, int x2, int y2, char* s, int color);	//主页面按钮绘制
int homepg_btn_fun(int x1, int y1, int x2, int y2, char* s);	//按钮功能函数（这里内容少就不放进buttons.c了）
int guest_btn_fun();//游客登录按钮功能函数
#endif