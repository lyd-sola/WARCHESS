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

void range(MAP map, DBL_POS pos, int able, int mode, int visit[5][5]);
int moving(MAP map, int visit[5][5], DBL_POS FROM, DBL_POS TO);
void anime_path(MAP map, DBL_POS* path, int top);

#endif