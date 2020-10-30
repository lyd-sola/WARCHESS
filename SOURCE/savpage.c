/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: savepage.c
author: 刘云笛
version: 1.0
Description:存档界面！ 
	可以说是非常完美了
	写了一天，debug了半天（连带所有数据流相关函数）
	我的孩子终于长大了QAQ
	写到这里的时候lyd已经懒得缩减代码量了
	其实六个函数可以合成一个
date:2020/10/4
更新日志
******************************************************************/

#include "common.h"
/*存档管理页面，返回1可以进入对战界面，返回0回到原界面*/
int savpage(char *user, int* save_num, int* mode)
{
	int flag = 1;//模式，1为读档，0为覆盖
	int tot = 0;
	char s[25] = "SAVES//";
	FILE* fp;

	strcat(s, user);
	if ((fp = fopen(s, "rb+")) == NULL)
		show_error("未找到用户存档文件", 1);
	savpage_draw(fp);
	tot = get_savenum(fp);
	while (1)
	{
		Newxy();

		if (mouse_press(197 + 630 - 32, 98, 197 + 630, 98 + 32) == MOUSE_IN_L)
		{
			fclose(fp);
			return 0;
		}
		if (rec_btn_fun(236, 511, 373, 561, 65535))//点击读取存档
		{
			flag = 1;
			Clrmous();
			savpage_btns(1);
		}
		if (rec_btn_fun(443, 511, 580, 561, 65535))//点击新建存档
		{
			if (tot >= 6)
			{
				if (msgbar("确定", "取消", "存档已满", "是否进入重置模式？"))
				{
					flag = 0;
					savpage_draw(fp);
					savpage_btns(3);
				}
				else
				{
					savpage_draw(fp);
				}
			}
			else 
			{
				if (savefile_creat(fp, msgbar("单人", "双人", "请选择模式", "")))
				{
					show_error("存档创建失败，原因不明", 0);
				}
				tot++;
				savpage_draw(fp);
			}
		}
		if (rec_btn_fun(650, 511, 787, 561, 65535))
		{
			flag = 0;
			Clrmous();
			savpage_btns(3);
		}//点击重置存档

		if (save1(fp, &flag, tot, mode, save_num) || save2(fp, &flag, tot, mode, save_num)
			|| save3(fp, &flag, tot, mode, save_num) || save4(fp, &flag, tot, mode, save_num)
			|| save5(fp, &flag, tot, mode, save_num) || save6(fp, &flag, tot, mode, save_num))
		{
			return 1;
		}
	}
}
void savpage_btns(int i)
{
	int color[3] = { 65535 , 65535 , 65535 };
	color[i-1] = 65340;
	rect_button(236, 511, 373, 561, "读取存档", color[0]);
	rect_button(443, 511, 580, 561, "新建存档", color[1]);
	rect_button(650, 511, 787, 561, "重置存档", color[2]);
}
int save1(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(287 - 15, 182, 287 - 15 + 205, 182 + 86) == MOUSE_IN_L)//存档1
	{
		if (*flag && tot >= 1)
		{
			if (msgbar("确定", "取消", "读取存档1", "确定吗？"))
			{
				*save_num = 1;
				*mode = get_savmode(fp, 1);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//读档模式
		else if (tot >= 1)
		{
			if (msgbar("确定", "取消", "即将覆盖该存档", "确定吗？"))
			{
				seek_savinfo(fp, 1, 0, 0);
				savefile_init(fp, msgbar("单人", "双人", "请选择模式", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//重置模式
	}
	return 0;
}
int save2(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(532 + 15, 182, 532 + 15 + 205, 182 + 86) == MOUSE_IN_L)//存档2
	{
		if (*flag && tot >= 2)
		{
			if (msgbar("确定", "取消", "读取存档2", "确定吗？"))
			{
				*save_num = 2;
				*mode = get_savmode(fp, 2);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//读档模式
		else if (tot >= 2)
		{
			if (msgbar("确定", "取消", "即将覆盖该存档", "确定吗？"))
			{
				seek_savinfo(fp, 2, 0, 0);
				savefile_init(fp, msgbar("单人", "双人", "请选择模式", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//重置模式
	}
	return 0;
}
int save3(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(287 - 15, 290, 287 - 15 + 205, 290 + 86) == MOUSE_IN_L)//存档3
	{
		if (*flag && tot >= 3)
		{
			if (msgbar("确定", "取消", "读取存档3", "确定吗？"))
			{
				*save_num = 3;
				*mode = get_savmode(fp, 3);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//读档模式
		else if (tot >= 3)
		{
			if (msgbar("确定", "取消", "即将覆盖该存档", "确定吗？"))
			{
				seek_savinfo(fp, 3, 0, 0);
				savefile_init(fp, msgbar("单人", "双人", "请选择模式", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//重置模式
	}
	return 0;
}
int save4(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(532 + 15, 290, 532 + 15 + 205, 290 + 86) == MOUSE_IN_L)//存档4
	{
		if (*flag && tot >= 4)
		{
			if (msgbar("确定", "取消", "读取存档4", "确定吗？"))
			{
				*save_num = 4;
				*mode = get_savmode(fp, 4);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//读档模式
		else if (tot >= 4)
		{
			if (msgbar("确定", "取消", "即将覆盖该存档", "确定吗？"))
			{
				seek_savinfo(fp, 4, 0, 0);
				savefile_init(fp, msgbar("单人", "双人", "请选择模式", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//重置模式
	}
	return 0;
}
int save5(FILE* fp, int* flag, int tot, int* mode, int* save_num)
{
	if (mouse_press(287 - 15, 398, 287 - 15 + 205, 398 + 86) == MOUSE_IN_L)//存档5
	{
		if (*flag && tot >= 5)
		{
			if (msgbar("确定", "取消", "读取存档5", "确定吗？"))
			{
				*save_num = 5;
				*mode = get_savmode(fp, 5);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//读档模式
		else if (tot >= 5)
		{
			if (msgbar("确定", "取消", "即将覆盖该存档", "确定吗？"))
			{
				seek_savinfo(fp, 5, 0, 0);
				savefile_init(fp, msgbar("单人", "双人", "请选择模式", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//重置模式
	}
	return 0;
}
int save6(FILE *fp, int *flag, int tot, int *mode, int *save_num)
{
	if (mouse_press(532 + 15, 398, 532 + 15 + 205, 398 + 86) == MOUSE_IN_L)//存档6
	{
		if (*flag && tot >= 6)
		{
			if (msgbar("确定", "取消", "读取存档6", "确定吗？"))
			{
				*save_num = 6;
				*mode = get_savmode(fp, 6);
				fclose(fp);
				return 1;
			}
			else
			{
				savpage_draw(fp);
			}
		}//读档模式
		else if (tot >= 6)
		{
			if (msgbar("确定", "取消", "即将覆盖该存档", "确定吗？"))
			{
				seek_savinfo(fp, 6, 0, 0);
				savefile_init(fp, msgbar("单人", "双人", "请选择模式", ""));
				*flag = 1;
			}
			savpage_draw(fp);
		}//重置模式
	}
	return 0;
}

void savpage_draw(FILE *fp)
{
	Clrmous();
	Bar64k_radial(197, 98, 197 + 630, 98 + 495, 65340, 0);
	Bar64k_radial(197+630-32, 98, 197 + 630, 98 + 32, 65535, 0);
	Outtext(197 + 630 - 32, 98, "返", 32, 32, 0);
	draw_saves(287 - 15, 398, 65535, fp, 5);
	draw_saves(532 + 15, 398, 65535, fp, 6);
	draw_saves(287 - 15, 290, 65535, fp, 3);
	draw_saves(532 + 15, 290, 65535, fp, 4);
	draw_saves(287 - 15, 182, 65535, fp, 1);
	draw_saves(532 + 15, 182, 65535, fp, 2);
	rect_button(236, 511, 373, 561, "读取存档", 65535);
	rect_button(443, 511, 580, 561, "新建存档", 65535);
	rect_button(650, 511, 787, 561, "重置存档", 65535);
	Outtextxx(367, 125, 512*2-367, "存档管理", 32, 0);
}

void draw_saves(int x, int y, int color, FILE* fp, int save_num)
{
	char Buffer[20];
	unsigned int t[3];//年 月日 时分
	int mode, tot = 0;

	rectangle64k(x, y, x + 5 + 200, y + 25 + 40 + 16 + 5, 0);
	rectangle64k(x - 1, y - 1, x + 5 + 200 + 1, y + 25 + 40 + 16 + 5 + 1, 0);
	Bar64k_radial(x, y, x + 5 + 200, y + 25 + 40 + 16 + 5, color, 0);
	sprintf(Buffer, "%d", save_num);
	Outtext(x + 5 + 75, y + 25 - 20, "存档", 16, 19, 0);
	Outtext(x + 5 + 75 + 19 + 16, y + 25 - 20, Buffer, 16, 19, 0);//存档序号

	//fseek(fp, 0, SEEK_SET);
	//fscanf(fp, "%d", &tot);
	//fread(&tot, 1, 1, fp);//读取存档总数
	tot = get_savenum(fp);
	if (save_num > tot)
	{
		return;
	}//无存档仅画框

	seek_savinfo(fp, save_num, 0, 0);
	//fread(&mode, 1, 1, fp);
	fscanf(fp, "%1d", &mode);

	fread(t, 2, 3, fp);
	sprintf(Buffer, "%4u/%02u/%02u %02u:%02u", t[0], t[1] / 100, t[1] % 100, t[2] / 100, t[2] % 100);
	Outtext(x + 5 + 17-1, y + 25, Buffer, 16, 10, 0);//时间

	if (mode == 1)
	{
		Outtext(x + 5, y + 25 + 20, "模式：决战智械", 16, 19, 0);
	}
	else
	{
		Outtext(x + 5, y + 25 + 20, "模式：红蓝对决", 16, 19, 0);
	}//模式

	fread(t, 2, 1, fp);
	sprintf(Buffer, "%u", (t[0]+1)/2);
	Outtext(x + 5, y + 25 + 40, "回合数:", 16, 19, 0);
	Outtext(x + 5 + 19 * 3 + 16, y + 25 + 40, Buffer, 16, 10, 0);
}