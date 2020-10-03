/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: save.c
author: 刘云笛
version: 0
Description:对战信息文件处理
date:

更新日志																	后续可能需要加密文件防挂，目前暂不考虑
																			
																			***注意*** 此函数添加存档只能按顺序添加，不能让用户点选任意一个添加

函数目录
1.创建用户存档文件
2.
******************************************************************/
#define MAP_SIZE 13
#define MAX_SAVE_NUM 6
#include "common.h"

/**************************************************************************************************
save文件设计：											位数表：自开头偏移量（字节）
	文件名：username
	1：文件中存档个数，short*1								共1
	
	以下重复多个存档块的设计（注：short均为unsigned）
	------------------------------------
	存档序号short*1											0
	日期 年unsigned*1，月日unsigned*1，时分unsigned*1		1
	回合数 unsigned*1										7
	蓝方、红方 资源 unsigned*2								9
	
	以下13行*13个unsigned大小（位字段CELL）为地图			13
	位字段结构设计见struct.h
	------------------------------------				地图共2*SIZE*SIZE
	Author：刘云笛
*************************************************************************************************/

/*******************************************
Function：savefile_creat
Author：刘云笛
Description: 快速创建地图文件
*******************************************/
int savefile_creat(char *user)//如果返回1则存档满，快速创建失败
{
	char filename[25] = "SAVES//";
	FILE *fp;
	short n;
	strcat(filename, user);
	if( (fp = fopen(filename, "rb+")) == NULL)
	{
		show_error("未找到用户存档文件", 1);
	}
	fread(&n, 1, 1, fp);//读取存档个数
	if(n >= MAX_SAVE_NUM)
	{
		return 1;
	}
	n++;
	fseek(fp, 0, SEEK_SET);
	fwrite(&n, 1, 1, fp);
	//增加存档个数

	fseek(fp, 0, SEEK_END);//移动到文件尾，开始存档创建
	savefile_init(fp, n);//初始信息填写
	fclose(fp);
	return 2;
}

/*******************************************
Function：savefile_init
Author：刘云笛
Description: 对某一个存档进行覆盖式初始化
*******************************************/

void savefile_init(FILE *fp, short n)//n为当前存档号
{
	unsigned i = 3, j = 0, t[3];
	time_t rawtime;
    struct tm *info;
	CELL cell;
	FILE *map;
	char geo;
	//存档号
	fwrite(&n, 1, 1, fp);
	//当前时间输入
	time( &rawtime );
    info = localtime( &rawtime );
	t[0] = info->tm_year + 1900;//年
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//月日
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//时分
	fwrite(t, 2, 3, fp);
	//初始化内容创建
	i = 1;
	fwrite(&i, 2, 1, fp);//回合数
	i = 3;
	fwrite(&i, 2, 1, fp);
	fwrite(&i, 2, 1, fp);//双方资源数
	
	
	//地图初始化
	if ((map = fopen("DATA//map.txt", "r")) == NULL)
	{
		show_error("未找到地图信息文件", 1);
	}
	cell.kind = NOARMY;
	cell.health = 0;
	cell.side = 0;
	for(i = 0; i < MAP_SIZE; i ++)
	{
		fseek(map, 2, SEEK_CUR);
		for(j = 0; j < MAP_SIZE; j ++)//OBSTACLE, PLAIN, FOREST, DESERT, BASE, SORC, HSORC
		{
			fscanf(map, "%c", &geo);
			geo -= '0';
			switch (geo)
			{
			case OBSTACLE:
				cell.geo = OBSTACLE;
				cell.cost = 7;
				break;
			case PLAIN:
				cell.geo = PLAIN;
				cell.cost = 1;
				break;
			case FOREST:
				cell.geo = FOREST;
				cell.cost = 2;
				break;
			case DESERT:
				cell.geo = DESERT;
				cell.cost = 2;
				break;
			case BASE:
				cell.geo = BASE;
				cell.cost = 7;
				break;
			case SORC:
				cell.geo = SORC;
				cell.cost = 2;
				break;
			case HSORC:
				cell.geo = HSORC;
				cell.cost = 2;
				break;
			case OUT_MAP:
				cell.geo = OUT_MAP;
				cell.cost = 7;
				break;
			}
			fwrite(&cell, 2, 1, fp);
		}
		fseek(map, 2, SEEK_CUR);
	}
	fclose(map);
}
/*******************************************
Function：seek_savinfo
Author：刘云笛
Description: 在对战信息文件中定位
	将fp定位指向坐标xy的信息，注：输入坐标为双倍宽度
	若x*y == 0，将fp定位到第n个存档首
*******************************************/

void seek_savinfo(FILE* fp, short n, int x, int y)//fp 指向用户对战信息文件的指针
{
	fseek(fp, 1, SEEK_SET);//跳过开始数字
	fseek(fp, (13 + 2 * MAP_SIZE * MAP_SIZE) * (n - 1), 1);//跳过n-1个存档
	if (x * y == 0)
	{
		return;
	}
	fseek(fp, 13, SEEK_CUR);//跳过“存档头”
	/* 存储行列与双倍宽度坐标的关系：row=y,column=(int)(x+1)/2 */
	fseek(fp, 2 * MAP_SIZE * (y - 1), SEEK_CUR);//跳过y-1行
	fseek(fp, (x - 1) / 2 * 2, SEEK_CUR);//跳过(x - 1) / 2列
}
/*******************以下测试函数，记得删除********************/















