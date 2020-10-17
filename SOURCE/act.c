/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
File_name: battle.c
Author: 刘云笛、陈旭桐
Version:
Description: 对战行为
Date:

更新日志

******************************************************************/
#include "common.h"
extern FILE* FBMP;
void move(DBL_POS From, MAP map)
{
	OFF_POS To, ofrom;
	DBL_POS dbto;
	POS center;

	ofrom = D2O(From);
	move_button(600);
	show_msg("请选择要移动的位置", "");
	while (1)
	{
		Newxy();
		if (clcmap(&dbto, map))//需要保证已有行动力
		{
			To = D2O(dbto);//求出目标偏移坐标
			if (map[To.y][To.x].kind == NOARMY)//为空可移动，以后还需设置移动能力，还需判断是否原地移动
			{
				Clrmous();
				center = center_xy(From.x, From.y);

				show_msg("行军中", "");
				Map_partial(center.x - 18, center.y - 18, center.x + 18, center.y + 23, FBMP);//还原此处地图
				center = center_xy(dbto.x, dbto.y);
				Icon_builder(center, 1);//图标画到目标点
				delay(1000);
				
				//map[To.x][To.y].flag = 1;//标记已移动
				map[To.y][To.x].health = map[ofrom.y][ofrom.x].health;
				map[To.y][To.x].kind = map[ofrom.y][ofrom.x].kind;
				map[To.y][To.x].side = map[ofrom.y][ofrom.x].side;//移动
				map[ofrom.y][ofrom.x].kind = NOARMY;//清除
				move_button(65535);
				return; 
			}
			else
			{
				show_msg("此处已被占领", "");
				move_button(65535);
				return; 
			}
		}
		else if (mouse_press(0, 0, 1024, 768) == MOUSE_IN_R)//右键取消
		{
			move_button(65535);
			return;
		}
	}
}