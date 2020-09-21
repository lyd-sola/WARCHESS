/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: battle.c
Author: 刘云笛、陈旭桐
Version: 
Description: 战斗界面
Date:

更新日志

函数目录
******************************************************************/

#include "common.h"
//战斗界面主函数
int battle(char *user, short save_num)
{
	CELL map[13][13];
	CELL cl;
	Battleinfo batinfo;
	int clx, cly;
	char s[20] = "SAVES//";
	FILE* fp;
	
	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
	{
		show_error("未找到用户存档文件", 1);
	}

	Battle_init(fp, &batinfo, map, save_num);
	Clrmous();
	battle_draw();
	while(1)
	{
		Newxy();
		if (Light_button(16, "注销账号", "注销账号", 60361, 65535))
		{
			return MAINMENU;
		}
		//if(mouse_press(69, 23, 959, 619) == MOUSE_IN_L)
		//{
		//	xy_tran((float)MouseX, (float)MouseY, &clx, &cly);

		//	cl = map[(clx + 1) / 2 - 1][cly - 1];
		//}
	}
}
//绘制战斗界面函数
void battle_draw()
{
	Putbmp64k(0, 0, "BMP//map.bmp");
	Button(16, "退出战斗", 60361, 65535);
}
/**********************************************************
Function：		Battle_init
Description：	战斗初始化函数，读取存档
Input:			fp用户存档文件指针，其他你一看就懂
Author：		刘云笛
**********************************************************/
void Battle_init(FILE* fp, Battleinfo *info, CELL map[][13], short save_num)
{
	int i, j;
	seek_savinfo(fp, save_num, 0, 0);
	fseek(fp, 7, SEEK_CUR);//跳过日期
	fread(&(info->round), 2, 1, fp);
	fread(&(info->b_source), 2, 1, fp);
	fread(&(info->r_source), 2, 1, fp);
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fread(map[i] + j, 2, 1, fp);
		}
	}//读取地图信息
}

void save_battle(FILE *fp, short save_num, Battleinfo *batinfo, CELL map[][13])
{
	unsigned t[3];
	time_t rawtime;
	struct tm* info;
	int i, j;

	seek_savinfo(fp, save_num, 0, 0);

	fseek(fp, 1, SEEK_CUR);//跳过存档号
	//当前时间输入
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//年
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//月日
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//时分
	fwrite(t, 2, 3, fp);
	//回合信息保存
	fwrite( &((*batinfo).round), 2, 1, fp );
	fwrite( &((*batinfo).b_source), 2, 1, fp );
	fwrite( &((*batinfo).r_source), 2, 1, fp );
	//储存地图信息
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			fwrite(map[i] + j, 2, 1, fp);
		}
	}
}