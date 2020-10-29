/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: save.c
author: 刘云笛	
version: 3.0
Description:对战信息文件处理
		***注意*** 此函数添加存档只能按顺序添加，不能让用户点选任意一个添加
date:

更新日志																	后续可能需要加密文件防挂，目前暂不考虑
version 1.0 ：使用文本文件（好看，但是文件较大，读写慢）
version 2.0 ：大突破！使用二进制文件，地图单元格使用位字段结构
version 3.2 ：2020/10/18 增加CELL的容量，为将来增加功能预留空间
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
	模式char*1，0为双人，1为单人							0
	日期 年unsigned*1，月日unsigned*1，时分unsigned*1		1
	回合数 unsigned*1										7
	蓝方、红方 资源 unsigned*2								9
	
	以下13行*13个unsigned大小（位字段CELL）为地图			13
	位字段结构设计见struct.h
	------------------------------------				地图共3*SIZE*SIZE
	Author：刘云笛
*************************************************************************************************/

/*******************************************
Function：savefile_creat
Author：刘云笛
Description: 快速创建地图文件
*******************************************/
int savefile_creat(FILE *fp, short mode)//如果返回1则存档满，快速创建失败，成功创建返回0
{
	short n;

	n = get_savenum(fp);//读取存档个数
	if(n >= MAX_SAVE_NUM)
	{
		return 1;
	}
	n++;
	fseek(fp, 0, SEEK_SET);
	fputc(n + '0', fp);
	//fprintf(fp, "%1d", n);
	//fwrite(&n, 1, 1, fp);
	//增加存档个数

	fseek(fp, 0, SEEK_END);//移动到文件尾，开始存档创建
	savefile_init(fp, mode);//初始信息填写
	return 0;
}

/*******************************************
Function：savefile_init
Author：刘云笛
Description: 对某一个存档进行覆盖式初始化
*******************************************/

void savefile_init(FILE* fp, short mode)
{
	unsigned int i = 3, j = 0, t[3];
	time_t rawtime;
	struct tm* info;
	CELL cell;
	FILE* map;
	char geo;
	//对战模式
	//fwrite(&m, 1, 1, fp);
	fprintf(fp, "%1d", mode);
	//当前时间输入
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//年
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//月日
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//时分
	fwrite(t, 2, 3, fp);
	//初始化内容创建
	i = 1;
	fwrite(&i, 2, 1, fp);//回合数
	i = 2;
#ifdef INF_SOURCE
	i = 666;
#endif // 无限资源模式！！
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
	cell.faci = 0;
	cell.stay = 0;
	cell.flag = 0;
	cell.src_rnd = 0;
	for (i = 0; i < MAP_SIZE; i++)
	{
		fseek(map, 2, SEEK_CUR);
		for (j = 0; j < MAP_SIZE; j++)//OBSTACLE, PLAIN, FOREST, DESERT, BASE, SORC, HSORC
		{
			fscanf(map, "%c", &geo);
			geo -= '0';
			if (geo == BASE)
			{
				cell.geo = BASE;
				cell.kind = 1;//大本营初始化
				cell.health = 30;
				if (i == 3)//蓝方
					cell.side = 1;
				fwrite(&cell, sizeof(CELL), 1, fp);
				cell.kind = NOARMY;
				cell.health = 0;
				cell.side = 0;
			}
			else
			{
				cell.geo = geo;
				fwrite(&cell, sizeof(CELL), 1, fp);
			}
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
	int size = sizeof(CELL);
	fseek(fp, 1, SEEK_SET);//跳过开始数字
	fseek(fp, (13 + size * MAP_SIZE * MAP_SIZE) * (n - 1), 1);//跳过n-1个存档
	if (x * y == 0)
	{
		return;
	}
	fseek(fp, 13, SEEK_CUR);//跳过“存档头”
	/* 存储行列与双倍宽度坐标的关系：row=y,column=(int)(x+1)/2 */
	fseek(fp, size * MAP_SIZE * (y - 1), SEEK_CUR);//跳过y-1行
	fseek(fp, (x - 1) / size * size, SEEK_CUR);//跳过(x - 1) / 2列
}

short get_savenum(FILE* fp)
{
	short tot;
	fseek(fp, 0, SEEK_SET);
	tot = fgetc(fp) - '0';
	return tot;
}

short get_savmode(FILE* fp, short savnum)
{
	short mode;
	seek_savinfo(fp, savnum, 0, 0);
	mode = fgetc(fp);
	return mode - '0';
}

/**********************************************************
Function：		Battle_init
Description：	战斗初始化函数，读取存档
Input:			fp用户存档文件指针，其他你一看就懂
Author：		刘云笛
**********************************************************/
void Battle_init(FILE* fp, Battleinfo* info, MAP map)
{
	int i;
	int size = sizeof(CELL);

	fseek(fp, 7, SEEK_CUR);//跳过日期
	fread(&(info->round), 2, 1, fp);
	fread(&(info->b_source), 2, 1, fp);
	fread(&(info->r_source), 2, 1, fp);
	for (i = 0; i < 13; i++)
	{
		fread(map[i], size, 13, fp);
		if (feof(fp) && i != 12)
		{
			show_error("地图文件有误！", 1);
		}
	}//读取地图信息
}
/**********************************************************
Function：		save_battle
Description：	保存存档
Input:			fp用户存档文件指针，需要指向正确存档，其他你一看就懂
Author：		刘云笛
**********************************************************/

void save_battle(FILE* fp, Battleinfo batinfo, MAP map)
{
	unsigned t[3];
	time_t rawtime;
	struct tm* info;
	int i;
	int size = sizeof(CELL);

	fseek(fp, 1, SEEK_CUR);//跳过模式号
	//当前时间输入
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//年
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//月日
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//时分
	fwrite(t, 2, 3, fp);
	//回合信息保存
	fwrite(&(batinfo.round), 2, 1, fp);
	fwrite(&(batinfo.b_source), 2, 1, fp);
	fwrite(&(batinfo.r_source), 2, 1, fp);
	//储存地图信息
	for (i = 0; i < 13; i++)
	{
		fwrite(map[i], size, 13, fp);
	}
}

void load_battle(char* user, int save_num, Battleinfo* batinfo, MAP map, FILE **fp)
{
	char filename[25] = "SAVES//";
	strcat(filename, user);
	if ((*fp = fopen(filename, "rb+")) == NULL)
		show_error("未找到用户存档文件", 1);
	seek_savinfo(*fp, save_num, 0, 0);
	Battle_init(*fp, batinfo, map);
}