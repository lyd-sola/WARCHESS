/**********************************************************
Copyright(c)  2020 ÁõÔÆµÑ¡¢³ÂÐñÍ© 	WARCHESSÕ½Æå
file_name:judge.h
Author:ÁõÔÆµÑ¡¢³ÂÐñÍ©
Version:
Description:ÒÆ¶¯ÅÐ¶Ïº¯Êý
				

Function List£º
	
**********************************************************/
#ifndef	_JUDGE_H_
#define	_JUDGE_H_

void range(MAP map, DBL_POS pos, int able, int mode, int visit[5][5]);
int moving(MAP map, int visit[5][5], DBL_POS FROM, DBL_POS TO);
void anime_path(MAP map, DBL_POS* path, int top);

#endif