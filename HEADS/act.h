/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:1.0
Description:对战行为函数


Function List：
	1.void move(DBL_POS From, MAP map, int able);
		移动函数
	2.int move_(DBL_POS From, DBL_POS dbto, MAP map, int visit[7][7]);
		是否可以移动判断
	3.void stay(DBL_POS dpos, MAP map);
		驻扎函数
	4.void attack(DBL_POS dpos, MAP map);
		攻击函数
	5.int attack_(Arminfo info, MAP map, DBL_POS dpos, DBL_POS dbto);
		攻击数值相关函数
	6.void delarm(DBL_POS dpos, MAP map);
		删除兵种函数
	7.void builder_build(DBL_POS dpos, MAP map, Battleinfo* batinfo);
		工兵建造设施函数
	8.void nxt_round(MAP map, Battleinfo* info, int* pside);
		下一回合函数
	9.void next_r_banner(int side);
		绘制下一回合锦旗
	10.void base_func(MAP map, unsigned* source, int is_same_side, DBL_POS pos);
		大本营行为函数
	11.void levelup(DBL_POS dpos, MAP map, unsigned* source);
		大本营升级
	12.void buildarm(MAP map, unsigned* source, int side);
		造兵函数
	13.void armbuild_draw(POS pos, int side);
		绘制右下角造兵按钮
	14.void air_attack(DBL_POS pos, MAP map, unsigned *source);
		大本营攻击函数
	15.void air_boom(MAP map, OFF_POS oto, OFF_POS from);
		大本营空袭函数
**********************************************************/

#ifndef  _ACT_H_
#define  _ACT_H_

void move(DBL_POS From, MAP map, int able);
int move_(DBL_POS From, DBL_POS dbto, MAP map, int visit[7][7]);
void stay(DBL_POS dpos, MAP map);
void attack(DBL_POS dpos, MAP map);
int attack_(Arminfo info, MAP map, DBL_POS dpos, DBL_POS dbto);
void delarm(DBL_POS dpos, MAP map);
void builder_build(DBL_POS dpos, MAP map, Battleinfo* batinfo);

void nxt_round(MAP map, Battleinfo* info, int* pside);
void next_r_banner(int side);

void base_func(MAP map, unsigned* source, int is_same_side, DBL_POS pos);
void levelup(DBL_POS dpos, MAP map, unsigned* source);
void buildarm(MAP map, unsigned* source, int side);
void armbuild_draw(POS pos, int side);
void air_attack(DBL_POS pos, MAP map, unsigned *source);
void air_boom(MAP map, OFF_POS oto, OFF_POS from);
#endif