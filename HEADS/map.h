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
OFF_POS D2O(DBL_POS pos);//双倍宽度坐标转换为偏移坐标
DBL_POS O2D(OFF_POS pos);//偏移坐标转换为双倍宽度坐标
int clcmap(DBL_POS* pos, MAP map);//判断是否在地图内点击，地图外返回，地图内且无单位返回1，有单位返回2
int move_cost(int geo);//返回移动消耗，-1为无法到达
int inside_map(MAP map, DBL_POS pos);
void draw_cell(DBL_POS pos, MAP map);
void recover_cell(DBL_POS pos, MAP map);
void show_visit(DBL_POS pos, int visit[7][7], void (*lightfun)(int x1, int y1, int x2, int y2));
#endif
