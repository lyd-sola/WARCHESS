/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:
Description:战斗界面
				

Function List：
	1.int savefile_creat(char *user);
		如果返回1则存档满，快速创建失败
	2.void seek_savinfo(FILE* fp, short n, int x, int y);
		fp为指向用户对战信息文件的指针，n为存档序号，xy为坐标，存档满返回1
	3.void savefile_init(FILE* fp, short n);
		覆盖性初始化某个存档，n为当前存档号	
**********************************************************/
#ifndef __SAVE_H__
#define __SAVE_H__

int savefile_creat(FILE* fp, short mode);
void seek_savinfo(FILE* fp, short n, int x, int y);
void savefile_init(FILE* fp, short n);			
short get_savenum(FILE* fp);//返回总存档个数
short get_savmode(FILE* fp, short savnum);//返回存档的对战模式
void Battle_init(FILE* fp, Battleinfo* info, MAP map);

void save_battle(FILE* fp, Battleinfo batinfo, MAP map);
void load_battle(char* user, int save_num, Battleinfo* batinfo, MAP map, FILE** fp);
#endif