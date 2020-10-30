/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:judge.h
Author:���Ƶѡ�����ͩ
Version:2.0
Description: �Ծ��еĽ����жϣ��㷨�ѶȺ��ģ�
Function List��
	1.int range(MAP map, DBL_POS pos, int able, int mode, int visit[7][7]);
		��Χ�жϺ���
	2.int moving(MAP map, int visit[7][7], DBL_POS FROM, DBL_POS TO);
		�ƶ�����ʵ�֡�·������
	3.void anime_path(MAP map, DBL_POS* path, int top, int kind, int side);
		������ʾ�ƶ�
	4.int attack_judge(MAP map, int able, DBL_POS dpos, DBL_POS dto);
		�����ж�
	5.int victory_judge(MAP map);
		ʤ���ж�
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