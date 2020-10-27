/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:
author:
version:
Description:
date:

更新日志

函数目录
******************************************************************/
#include "common.h"
//神秘格子：由中心线网格围出的格子

POS xy2cell(int x, int y) //真实坐标与双倍宽度坐标转换
{
	POS cell;
	double x2, y2, a, b, tmp;
	int n1, n2;
	x2 = x - X0; //换坐标系后的MouseX
	y2 = y - Y0; //换坐标系后的MouseY
	n1 = x2 / WIDTH + 1; //神秘方格横坐标，第几个
	n2 = y2 / LENGTH + 1; //神秘方格纵坐标，第几排
	a = n1 * WIDTH - WIDTH / 2; //神秘方格中点横坐标
	b = n2 * LENGTH - LENGTH / 2; //神秘方格中点纵坐标
	tmp = f(x2, a, b, n1, n2);

	/**根据点击位置在神秘方格中斜线上方或者下方确定格子纵坐标**/
	cell.y = (y2 < tmp) ? n2 : (n2 + 1);

	/**根据点击位置在神秘方格中斜线上方或者下方以及神秘方格行列数的奇偶性确定格子横坐标**/
	/************  y2 < tmp 判断的是鼠标点击点是否在斜线之上而非之下，y轴正方向向下*****************/
	if (n1 % 2 == 1) //神秘方格列数为奇数，继续判断行数奇偶性
	{
		if (n2 % 2 == 1)  //神秘方格行数为奇数
		{
			cell.x = (y2 < tmp) ? n1 : (n1 - 1);
		}
		else  //神秘方格行数为偶数
		{
			cell.x = (y2 < tmp) ? (n1 - 1) : n1;
		}
	}
	else            //神秘方格列数为偶数，继续判断行数奇偶性
	{
		if (n2 % 2 == 1)  //神秘方格行数为奇数
		{
			cell.x = (y2 < tmp) ? (n1 - 1) : n1;
		}
		else //神秘方格行数为偶数
		{
			cell.x = (y2 < tmp) ? n1 : (n1 - 1);
		}
	}
	return cell;
}

float f(float x, float a, float b, int n1, int n2)
{
	if (n1 % 2 == 1)
	{
		if (n2 % 2 == 1)
			return K * (x - a) + b;
		else
			return -K * (x - a) + b;
	}
	else
	{
		if (n2 % 2 == 1)
			return -K * (x - a) + b;
		else
			return K * (x - a) + b;
	}
}

 POS center_xy(int row, int col)
{
	POS centpos;
	row = (row + 1) / 2;//改回单倍宽度
	if (col % 2 == 1)
	{
		centpos.x = 103 + (row - 1) * 69;
	}
	else
	{
		centpos.x = 139 + (row - 1) * 69;
	}
	centpos.y = 54 + (col - 1) * 46;
	centpos.y -= (col - 1) / 3;
	centpos.x -= (row - 1) / 3;
	centpos.y -= 2;//根据图标位置微调
	return centpos;
}

OFF_POS D2O(DBL_POS pos)
{
	OFF_POS opos;
	opos.x = (pos.x - 1) / 2;
	opos.y = pos.y - 1;
	return opos;
}

DBL_POS O2D(OFF_POS pos)
{
	DBL_POS dpos;
	if (pos.y % 2)
	{
		dpos.x = 2 * pos.x + 2;
	}
	else
	{
		dpos.x = 2 * pos.x + 1;
	}
	dpos.y = pos.y + 1;
	return dpos;
}
//判断是否在地图内点击，地图外返回0，地图内且无单位返回1，有单位返回2
int clcmap(DBL_POS* pos, MAP map)
{
	OFF_POS opos;
	if (mouse_press(68, 22, 962, 633) == MOUSE_IN_L)
	{
		*pos = xy2cell(MouseX, MouseY);
		if(inside_map(map, *pos))
		{
			opos = D2O(*pos);
			if (map[opos.y][opos.x].geo != OUT_MAP)
			{
				if (map[opos.y][opos.x].geo == BASE)
				{
					return 3;
				}//大本营
				if (map[opos.y][opos.x].kind != NOARMY)
				{
					return 2;
				}//有单位
				else 
				{
					return 1;
				}//无单位
			}
			else
			{
				return 0;
			}//地图外区域
		}
		else
		{
			return 0;
		}//地图无效区域
	}
	else
	{
		return 0;
	}//未点击
}

int move_cost(int geo)//返回移动消耗
{
	switch (geo)
	{
	case OBSTACLE:
		return 666;
	case PLAIN:
		return 1;
	case FOREST:
		return 2;
	case DESERT:
		return 1;
	case BASE:
		return 666;
	case SORC:
		return 2;
	case HSORC:
		return 2;
	case OUT_MAP:
		return 666;
	}
	return 666;
}

int inside_map(MAP map, DBL_POS pos)//为了其他函数的美观，把丑陋的东西写在这里
{
	OFF_POS opos = D2O(pos);

	return 1 <= pos.x && pos.x <= 26 && 1 <= pos.y && pos.y <= 13
		&& map[opos.y][opos.x].geo != OUT_MAP;
}