/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:judge.h
Author:���Ƶѡ�����ͩ
Version:
Description:�ƶ��жϺ���
				

Function List��
	
**********************************************************/
#ifndef	_JUDGE_H_
#define	_JUDGE_H_

int range(MAP map, DBL_POS pos, int able, int mode, int visit[7][7]);
int moving(MAP map, int visit[7][7], DBL_POS FROM, DBL_POS TO);
void anime_path(MAP map, DBL_POS* path, int top, int kind, int side);
int attack_judge(MAP map, int able, DBL_POS dpos, DBL_POS dto);
int victory_judge(MAP map);

#endif