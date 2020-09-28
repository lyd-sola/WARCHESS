/**********************************************************
	2020 刘云笛、陈旭桐 WARCHESS战棋
	本文件多数函数来自两位学长（孙兆锦&郭浩南）的工作，由刘云笛修改，不计入总代码量
	（改了一晚上，还不能计入代码量QAQ）

	经lyd魔改：（其实是将两份鼠标的优点结合）
		1.重新绘制了鼠标（使用了证券投资魏靖旻和邓述民函数，转成SVGA模式，有了不同鼠标形态）
		2.修改了存鼠标背景的mouse_sq数组大小，以及存储范围（根据重新绘制的大小调整）
		3.调整了大部分函数，解决了切换页面鼠标不移动则不显示问题（Newxy）
		4.增加了解决鼠标留痕问题函数clrmous(MouseX, MouseY)
		5.增加了快速调用版清除鼠标函数Clrmous(),并解决手势不切换问题
		
*********************************************************/

#ifndef _MOUSE_H_
#define _MOUSE_H_

int Initmouse(int xmi,int xma,int ymi,int yma);		//初始化鼠标
int Readmouse(void);
void Mouse_savebk(int x,int y);
void Mouse_savebk2(void);
void Mouse_putbk(int x,int y);
int Mouse_press(int x1,int y1,int x2,int y2);
int Mouse_pressother(int x1, int y1, int x2, int y2);
int Mouse_above(int x1,int y1,int x2,int y2);
int Mouse_aboveother(int x1, int y1, int x2, int y2);

void Cursor(int x,int y);
int mouse_press(int x1, int y1, int x2, int y2);//如果在框中点击，则返回1；在框中未点击，则返回2；在框外点击，则返回3;在框中右击，则返回4；不在框中则返回0
void clrmous(int nx,int ny);//清除鼠标
void drawmous(int nx,int ny);//绘制鼠标，结合flag
void Newxy(void);//更新鼠标
void Clrmous(void);//快捷clrmous

extern int MouseX, MouseY, press, MouseS;
extern int Mouse_flag; 
enum MOUSE_POS
{
	MOUSE_OUT, MOUSE_IN_L, MOUSE_IN, MOUSE_OUT_L, MOUSE_IN_R
};
#endif
