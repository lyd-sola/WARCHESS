#ifndef _DRAW_H_
#define _DRAW_H_

#define X0 69			//原点x坐标
#define Y0 54		//原点y坐标
#define WIDTH 34.365	//一个神秘格子的y方向边长,六边形弦长一半
#define LENGTH 45.75	//一个神秘格子的y方向边长
#define K 0.5143		//直线斜率的绝对值

POS xy2cell(int x, int y);
float f(float x, float a, float b, int n1, int n2);
void xy(int n1, int n2, int* x, int* y);
POS center_xy(int row, int col);
#endif
