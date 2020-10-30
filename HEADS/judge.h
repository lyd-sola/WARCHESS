/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:judge.h
Author:刘云笛、陈旭桐
Version:2.0
Description: 对局中的较难判断（算法难度核心）
Function List：
	1.int range(MAP map, DBL_POS pos, int able, int mode, int visit[7][7]);
		范围判断函数
	2.int moving(MAP map, int visit[7][7], DBL_POS FROM, DBL_POS TO);
		移动过程实现、路径反推
	3.void anime_path(MAP map, DBL_POS* path, int top, int kind, int side);
		动画显示移动
	4.int attack_judge(MAP map, int able, DBL_POS dpos, DBL_POS dto);
		攻击判断
	5.int victory_judge(MAP map);
		胜利判断
**********************************************************/
#ifndef	_JUDGE_H_
#define	_JUDGE_H_

int range(MAP map, DBL_POS pos, int able, int mode, int visit[7][7]);

int moving(MAP map, int visit[7][7], DBL_POS FROM, DBL_POS TO);

void anime_path(MAP map, DBL_POS* path, int top, int kind, int side);

int attack_judge(MAP map, int able, DBL_POS dpos, DBL_POS dto);

int victory_judge(MAP map);
int v_cartoon(char* btn1, char* btn2, char* s1, char* s2, int side);

#endif