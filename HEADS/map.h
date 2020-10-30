/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: map.h
author: 陈旭桐、刘云笛
version: 2.0
Description: 地图相关函数
date:2020/9/8

更新日志

Function List
1.POS xy2cell(int x, int y);
	世界坐标转双倍坐标
2.float f(float x, float a, float b, int n1, int n2);
	六边形直线函数
3.POS center_xy(int row, int col);
	双倍坐标转世界坐标
4.OFF_POS D2O(DBL_POS pos);
	双倍宽度坐标转换为偏移坐标
5.DBL_POS O2D(OFF_POS pos);
	偏移坐标转换为双倍宽度坐标
6.int clcmap(DBL_POS* pos, MAP map);
	判断是否在地图内点击，地图外返回，地图内且无单位返回1，有单位返回2
7.int move_cost(int geo);
	返回移动消耗，-1为无法到达
8.int inside_map(MAP map, DBL_POS pos);
	判断是否在地图之内
9.void draw_cell(DBL_POS pos, MAP map);
	画出格子上的部队
10.void recover_cell(DBL_POS pos, MAP map);
	还原格子上的部队
11.void show_visit(DBL_POS pos, int visit[7][7], void (*lightfun)(int x1, int y1, int x2, int y2));
	显示可移动目标
******************************************************************/
#ifndef _DRAW_H_
#define _DRAW_H_

#define X0 69			//原点x坐标
#define Y0 54		//原点y坐标
#define WIDTH 34.365	//一个神秘格子的y方向边长,六边形弦长一半
#define LENGTH 45.75	//一个神秘格子的y方向边长
#define K 0.5143		//直线斜率的绝对值

POS xy2cell(int x, int y);
float f(float x, float a, float b, int n1, int n2);
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
