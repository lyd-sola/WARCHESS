/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:save.h
Author:刘云笛、陈旭桐
Version:3.0
Description:战斗界面
				
Function List：
	1.int savefile_creat(char *user);
		如果返回1则存档满，快速创建失败
	2.void seek_savinfo(FILE* fp, int n, int x, int y);
		fp为指向用户对战信息文件的指针，n为存档序号，xy为坐标，存档满返回1
	3.void savefile_init(FILE* fp, int n);
		覆盖性初始化某个存档，n为当前存档号	
	4.int get_savenum(FILE* fp);
		返回总存档个数
	5.void Battle_init(FILE* fp, Battleinfo* info, MAP map);
		初始化战斗信息
	6.void save_battle(FILE* fp, Battleinfo batinfo, MAP map);
		保存战斗
	7.void load_battle(char* user, int save_num, Battleinfo* batinfo, MAP map, FILE** fp);
		读取战斗信息
**********************************************************/
#ifndef __SAVE_H__
#define __SAVE_H__

int savefile_creat(FILE* fp, int mode);

void seek_savinfo(FILE* fp, int n, int x, int y);

void savefile_init(FILE* fp, int n);		

int get_savenum(FILE* fp);//返回总存档个数

int get_savmode(FILE* fp, int savnum);//返回存档的对战模式

void Battle_init(FILE* fp, Battleinfo* info, MAP map);

void save_battle(FILE* fp, Battleinfo batinfo, MAP map);

void load_battle(char* user, int save_num, Battleinfo* batinfo, MAP map, FILE** fp);
#endif