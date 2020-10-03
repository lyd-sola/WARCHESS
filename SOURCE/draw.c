/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS
file_name: draw.c
author: 陈旭桐、刘云笛
version: 1.5
Description: 自定义绘图函数
date:2020/9/8

更新日志
9.8		增加了阴影、边框自定义绘图函数
9.9		增加了绘制文档图形
9.10	升级为svga
9.11	lyd增加抠图贴图函数
9.12	lyd增加改变亮度函数，删除outtextxyc函数

函数目录
1.shadow/shadow_l: 			绘制带（大）阴影的文本框
2.frame: 					绘制带边框的文本框
3.filedraw:					绘制文档图形
4.Bar64kc/linec/outtextxyc：	集成前景色设置函数与普通图形函数
	5.void GetBackground(int left,int top,int right,int bottom,short *buffer);
		存储某一范围背景图（用于动画制作），buffer图片存储地址，成功返回0。
		
	6.void GetBackground(int left,int top,int right,int bottom,short *buffer);
		放回某一范围背景图（用于动画制作），buffer图片存储地址，成功返回0。
		
******************************************************************/
#include"common.h"

void file_draw(int x1, int y1, int x2, int y2) //x2 - x1 不能是奇数
{
	shadow_l(x1, y1, x2, y2, 65504);
	frame(x1+15, y1+15, x2-15, y2-15, 65535);

	/* 利用x2-x1为矩形长度，计算距离两边为60和80的椭圆横轴
	   纵轴为横轴一半
	   然后利用直线封口 
	   setcolor(LIGHT33808);
	ellipse((x2-x1)/2+x1, y1, 0, 180, (x2-x1)/2-60, ((x2-x1)/2-60)/2); 
	ellipse((x2-x1)/2+x1, y1, 0, 180, (x2-x1)/2-80, ((x2-x1)/2-80)/2);
	line(x2-60, y1, x2-80, y1);
	line(x1+60, y1, x1+80, y1);
	setfillstyle(1, LIGHT33808);
	floodfill((x2-x1)/2+x1,y1-(((x2-x1)/2-80)/2)-5,LIGHT33808);*/
}

//通过两点横坐标输出汉字省去计算part的时间，同时返回part值
int Outtextxx(int x1, int y, int x2, char *s,int flag, int color)
{
	int num = strlen(s) / 2;				//汉字个数
	int part = (x2-x1-flag) / (num - 1);	//由汉字数组长度 length = x2 - x1 = flag + (num - 1) X part 算出。
	Outtext(x1, y, s, flag, part, color);
	return part;
}

/*****************************************
背景抠图和还原函数
Author：刘云笛
buffer为存储的数组
*****************************************/
void GetBackground(int left, int top, int right, int bottom, short *buffer)//获取背景
{
    int i, j;
    int Width, Height;

    Width = right - left;
    Height = bottom - top;

    for(i = 0;i <= Height;i++)
    {
        for(j = 0;j <= Width;j++)         
        {                        
            buffer[i*Width+j]=Getpixel64k(left + i, top + j);         
        }     
    }     
} 

void PutBackground(int left, int top, int right, int bottom, short *buffer)//贴回背景
{     
    int i, j;    
    int Width, Height;     

    Width=right - left;
    Height=bottom - top;
    for(i = 0; i<= Height;i ++)//后续可改变画点顺序
    {
        for(j = 0;j <= Width;j ++)         
        {
            Putpixel64k(left + i, top + j, buffer[i*Width + j]);
        }   
    }    
}

/*****************************************
屏幕上一点的增加亮度函数（实际是同步增加各点rgb的值，不如说是白度？）
drgb的值为变白比例
Author：刘云笛
*****************************************/

unsigned int Lightcolor(unsigned int colorbf, float drgb)
{
	unsigned int rbf, gbf, bbf;
	/*计算RGB值*/
	rbf = colorbf / (1 << 11);
	gbf = colorbf % (1 << 11) / (1 << 5);
	bbf = colorbf % (1 << 5);
	/*如果rgb中带有0则无法改变改变该点*/
	if (rbf * gbf * bbf == 0)
	{
		return colorbf;
	}
	/*如果drgb过大*/
	if (drgb * rbf > 31)
	{
		drgb = (31.0 / rbf);
	}
	if (drgb * bbf > 31)
	{
		drgb = (31.0 / bbf);
	}
	if (drgb * gbf > 62)
	{
		drgb = (62.0 / gbf);
	}
	/*核心：每个点rgb值乘以相同倍数，可以实现变白*/
	rbf = drgb * rbf;
	gbf = drgb * gbf;
	bbf = drgb * bbf;
	colorbf = rbf * (1 << 11) + gbf * (1 << 5) + bbf;
	return colorbf;
}

void Lightpixel(int x, int y, float drgb)
{
	unsigned int colorbf;
	colorbf = Getpixel64k(x, y);
	colorbf = Lightcolor(colorbf, drgb);
	Putpixel64k(x, y, colorbf);
}
/*****************************************
以下为线、bar的增加亮度函数
实际来自SVGAmode.c中各函数函数修改得到，不计入代码量
Author：刘云笛
*****************************************/
void Lightline(int x1, int y1, int x2, int y2, float drgb)
{
	int	dx, dy;			/*直线x、y坐标差值*/
	int dx2, dy2;		/*加快运算速度的中间值*/
	int xinc, yinc;		/*判断想、y增加方向的符号值*/
	int d, dxy;			/*决策变量*/
	int i;
	dx = abs(x2 - x1);
	dx2 = dx << 1;
	dy = abs(y2 - y1);
	dy2 = dy << 1;
	if (x2 > x1)
	{
		xinc = 1;
	}
	else if (x2 == x1)
	{
		if (y1 > y2)
		{
			dx = y1;
			y1 = y2;
			y2 = dx;
		}
		for (dx = y1; dx <= y2; dx++)
		{
			Lightpixel(x1, dx, drgb);
		}
		return;
	}
	else
	{
		xinc = -1;
	}
	if (y2 > y1)
	{
		yinc = 1;
	}
	else if (y2 == y1)
	{
		for (i = x1; i <= x2; i++)
		{
			Lightpixel(i, y1, drgb);
		}
		return;
	}
	else
	{
		yinc = -1;
	}
	Lightpixel(x1, y1, drgb);
	if (dx >= dy)
	{
		d = dy2 - dx;
		dxy = dy2 - dx2;

		while (dx--)
		{
			if (d <= 0)
			{
				d += dy2;
			}
			else
			{
				d += dxy;
				y1 += yinc;
			}
			x1 += xinc;
			Lightpixel(x1, y1, drgb);
		}
	}
	else
	{
		d = dx2 - dy;
		dxy = dx2 - dy2;
		while (dy--)
		{
			if (d <= 0)
			{
				d += dx2;
			}
			else
			{
				d += dxy;
				x1 += xinc;
				y1 += yinc;
				Lightpixel(x1, y1, drgb);
			}
		}
	}
}

void Lightbar(int x1, int y1, int x2, int y2, float drgb)
{
	/*temp为临时变量和循环变量*/
	/*width为矩形长*/
	int temp, width;
	int i, j;
	/*x坐标排序*/
	if (x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}

	/*y坐标排序*/
	if (y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}


	/*逐行扫描画出矩形*/
	for (i = x1; i <= x2; i++)
	{
		Lightline(i, y1, i, y2, drgb);
		/*for(j=y1;j<=y2;j++)
		{
				Putpixel64k(i,j,color);
		}*/
	}
}

/**********************************************************
Function：		Bar64k_radial_re
Description：	反向放射性画出矩形框，使用方法同Bar64k，最后一个参数为总延迟时间（单位mm）

Calls：			rectangle64k

Author：		刘云笛
**********************************************************/
void Bar64k_radial_re(int x1, int y1, int x2, int y2, unsigned int color, int fill_time)
{
	int n, t, i;

	if (x2 - x1 > y2 - y1)
	{
		n = ceil(((float)y2 - y1) / 2);//向上取整
	}
	else
	{
		n = ceil(((float)y2 - y1) / 2);//向上取整
	}
	t = fill_time / (n + 1);

	for (i = 0; i <= n; i++)
	{
		rectangle64k(x1 + i, y1 + i, x2 - i, y2 - i, color);
		delay(t);//可能还需要调整
	}
}
/**********************************************************
Function：		Bar64k_radial
Description：	正向放射性画出矩形框，使用方法同Bar64k，最后一个参数为总延迟时间（单位mm）

Calls：			rectangle64k

Author：		刘云笛
**********************************************************/
void Bar64k_radial(int x1, int y1, int x2, int y2, unsigned int color, int fill_time)
{
	int n, t;

	if (x2 - x1 > y2 - y1)
	{
		n = ceil(((float)y2 - y1) / 2);//向上取整
	}
	else
	{
		n = ceil(((float)y2 - y1) / 2);//向上取整
	}
	t = fill_time / (n + 1);

	for (; n >= 0; n--)
	{
		rectangle64k(x1 + n, y1 + n, x2 - n, y2 - n, color);
		delay(t);//可能还需要调整
	}
}
/**********************************************************
Function：		Button
Description：	按钮绘制函数
Calls：			Line64k
Input:			y1按钮上沿y坐标，s按钮上汉字（四个字最佳）
				color1底色，color2线颜色

Author：		刘云笛
ps 灵感来自Riddle Joker，柚子社天下第一！
（大概不会有人看到这里）
**********************************************************/
void Button(int y1,char *s, int color, int color2)
{
	int x1 = 750, x2 = 1024;
	int height = 30, i;//bar大小274*30
	for (i = x2; i >= x1; i--)
	{
		Line64k(i, y1, i, y1 + height, color);
	}
	for (i = 1; i <= height; i ++)
	{
		Line64k(x1 - i, y1, x1 - i, y1 + height - i, color);
	}//从右向左扫描，减少卡顿效果
	for (i = 0; i <= height - 7; i++)
	{
		Putpixel64k(x1 - height + 10 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 11 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 12 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 13 + i, y1 + 4 + i, color2);
	}//左下装饰花纹绘制
	Bar64k(x1 + 4, y1 + height - 3, x1 + 2 + 64, y1 + height - 5, color2);
	Outtext(1024 - 4 * 55 - 20, y1 - 16, s, 32, 55, 0);
}
/**********************************************************
Function：		Line45
Description：	画45度角斜线，输入可以交换两端点
Input:			x1,y1,起始点,x2终点x坐标
				color颜色

Author：		刘云笛
**********************************************************/
void Line45(int x1, int y1, int x2, int y2, unsigned int color)
{
	int i, sign, num;
	if (x1 > x2)
	{
		i = x1;
		x1 = x2;
		x2 = i;
		i = y1;
		y1 = y2;
		y2 = i;
	}
	sign = (y2 - y1) / abs(y2 - y1);//为正则往右下画
	num = x2 - x1;
	for (i = 0; i <= num; i++)
	{
		Putpixel64k(x1 + i, y1 + sign * i, color);
	}
}

/**********************************************************
Function：		Icon_draw
Description：	画图标边框
Input:			pos格子中心点坐标
				side阵营
Author：		刘云笛
**********************************************************/
#define bl_side 0
#define rd_side 1
void Icon_draw(DBL_POS pos, int side)
{
	unsigned int color1, color2, color2c;	//yello 65385, red 49540, blue 8912

	color2 = 63207;
	color2c = 50347;
	color1 = (side == bl_side) ? 8912 : 49540;

	Bar64k(-18 + pos.x, -15 + pos.y, -6 + pos.x, -14 + pos.y, color1);
	Bar64k(18 + pos.x, -15 + pos.y, 6 + pos.x, -14 + pos.y, color1);
	Bar64k(-7 + pos.x, -17 + pos.y, -3 + pos.x, -16 + pos.y, color1);
	Bar64k(7 + pos.x, -17 + pos.y, 3 + pos.x, -16 + pos.y, color1);
	Bar64k(-2 + pos.x, -18 + pos.y, 2 + pos.x, -17 + pos.y, color1);
	Bar64k(-18 + pos.x, -15 + pos.y, -17 + pos.x, 8 + pos.y, color1);
	Bar64k(18 + pos.x, -15 + pos.y, 17 + pos.x, 8 + pos.y, color1);
	Line45(-18 + pos.x, 8 + pos.y, -3 + pos.x, 23 + pos.y, color1);
	Line45(-17 + pos.x, 8 + pos.y, -2 + pos.x, 23 + pos.y, color1);
	Line45(18 + pos.x, 8 + pos.y, 3 + pos.x, 23 + pos.y, color1);
	Line45(17 + pos.x, 8 + pos.y, 2 + pos.x, 23 + pos.y, color1);
	Bar64k(-2 + pos.x, 22 + pos.y, 2 + pos.x, 23 + pos.y, color1);

	Line64k(0 + pos.x, -16 + pos.y, 0 + pos.x, 21 + pos.y, color1);
	Floodfill(pos.x - 1, pos.y, color2, color1);
	Floodfill(pos.x + 1, pos.y, color2c, color1);
	Line64k(0 + pos.x, -16 + pos.y, 0 + pos.x, 21 + pos.y, color2);
}

/**********************************************************
Function：		Icon_builder
Description：	画个锤子（工兵图标）
Input:			pos格子中心点坐标
				color颜色

Author：		刘云笛
**********************************************************/
#define bl_side 0
#define rd_side 1
void Icon_builder(DBL_POS pos, int side)
{
	unsigned int color1;	
	color1 = (side == bl_side) ? 8912 : 49540;

	pos = center_xy(pos.x, pos.y);
	Icon_draw(pos, side);
	Filltriangle(-7 + pos.x, -2 + pos.y, 1 + pos.x, -10 + pos.y, 1 + pos.x, -2 + pos.y, color1);
	Filltriangle(4 + pos.x, 1 + pos.y, 4 + pos.x, 9 + pos.y, 12 + pos.x, 1 + pos.y, color1);
	Bar64k(0 + pos.x, -3 + pos.y, 5 + pos.x, 2 + pos.y, color1);
	Line45(-1 + pos.x, 1 + pos.y, -9 + pos.x, 9 + pos.y, color1);
	Line45(pos.x, 2 + pos.y, -8 + pos.x, 10 + pos.y, color1);
	Line45(1 + pos.x, 3 + pos.y, -7 + pos.x, 11 + pos.y, color1);
	Line45(-1 + pos.x, 2 + pos.y, -9 + pos.x, 10 + pos.y, color1);
	Line45(pos.x, 3 + pos.y, -8 + pos.x, 11 + pos.y, color1);//画个锤子
}

//x1, y1, x2, y2为对角线两点坐标
void diamond(int x1, int y1, int x2, int y2, int x3, int y3, int color) //y1和y2必须相同
{
	Filltriangle(x1, y1, x3, y3, x2, y2, color);
	Filltriangle(x2, y2, x3, y3, 2 * x2 - x1, y2, color);
	Filltriangle(x1, y1, x3, 2 * y1 - y3, x2, y2, color);
	Filltriangle(x2, y2, x3, 2 * y1 - y3, 2 * x2 - x1, y2, color);
}

void shadow(int x1, int y1, int x2, int y2, int color1, int color2)
{
	Bar64k_radial(x1 + 5, y1 + 5, x2 + 5, y2 + 5, 33808, 0);
	Bar64k_radial(x1, y1, x2, y2, color1, 0);
	Bar64k_radial(x1 + 2, y1 + 2, x2, y2, color2, 0);
}

void shadow_l(int x1, int y1, int x2, int y2, int color)
{
	Bar64k_radial(x1 + 10, y1 + 10, x2 + 10, y2 + 10, 33808, 0);
	Bar64k_radial(x1, y1, x2, y2, color, 0);
	rectangle64k(x1, y1, x2, y2, 33808);
}

void frame(int x1, int y1, int x2, int y2, int color)
{
	Bar64k_radial(x1, y1, x2, y2, color, 0);
	rectangle64k(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 33808);
}

void attack_button(char* s, int color)
{
	int i;
	int x1 = 20, y1 = 407, len = 121;
	Line64k(x1, y1, x1, y1 + len - 3, 0);
	Line64k(x1 + 1, y1, x1+1, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3, len + x1 - 3, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3 - 1, len + x1 - 3 - 1, y1 + len - 3 - 1, 0);
	Line45(x1, y1, len+x1 - 3, y1 + len - 3, 0);
	Line45(x1 + 1, y1, len + x1 - 3 + 1, y1 + len - 3, 0);
	Line45(x1 + 2, y1, len + x1 - 3 + 2, y1 + len - 3, 0);
	for (i = 0; i <= 113; i++)
	{
		Line64k(x1 + 2 + i, y1 + 3 + i, x1 + 2 + i, y1 + len - 3 - 2, color);
	}
	Outtext(x1 + 8, y1 + 71, s, 32, 35, 0);
}

void stay_button(char* s, int color)
{
	int i;
	int len = 121, x1 = 141 + 3, y1 = 528 + 3;
	Line64k(x1, y1, x1, y1 + len - 3, 0);
	Line64k(x1 + 1, y1, x1 + 1, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3, len + x1 - 3, y1 + len - 3, 0);
	Line64k(x1, y1 + len - 3 - 1, len + x1 - 3 - 1, y1 + len - 3 - 1, 0);
	Line45(x1, y1, len + x1 - 3, y1 + len - 3, 0);
	Line45(x1 + 1, y1, len + x1 - 3 + 1, y1 + len - 3, 0);
	Line45(x1 + 2, y1, len + x1 - 3 + 2, y1 + len - 3, 0);
	for (i = 0; i <= 113; i++)
	{
		Line64k(x1 + 2 + i, y1 + 3 + i, x1 + 2 + i, y1 + len - 3 - 2, color);
	}
	Outtext(x1 + 8, y1 + 71, s, 32, 35, 0);
}//为什么我要写两个函数呢，因为懒得记坐标

void move_button(int color)
{
	rectangle64k(20, 528, 141, 649, 0);
	rectangle64k(20+1, 528+1, 141-1, 649-1, 0);
	Bar64k_radial(20 + 2, 528 + 2, 141 - 2, 649 - 2, color, 0);
	Outtext(20+27, 528+44, "移动", 32, 35, 0);
}

void del_button(int color)
{
	rectangle64k(20, 649+3, 262, 649+3+45, 0);
	rectangle64k(20 + 1, 649 + 4, 262 - 1, 649+2+45, 0);
	Bar64k_radial(20 + 2, 649 + 5, 262 - 2, 649 + 46, color, 0);
	Outtext(85, 649+9, "删除", 32, 16+60, 0);
}

void nextr_button(int color)
{
	Circlefill64k(849+68, 514+68, 68, color);
	Circle64k(849 + 68, 514 + 68, 69, 0);
	Circle64k(849 + 68, 514 + 68, 68, 0);
	Circle64k(849 + 68, 514 + 68, 67, 0);
	Outtextxx(849 + 68 - 40, 514 - 40 + 68, 849 + 40 + 68, "下一", 32, 0);
	Outtextxx(849 + 68 - 40, 514 + 40 - 32 + 68, 849 + 68 + 40, "回合", 32, 0);
}

void banner(int x1, int y1, int length) //x1, y1为矩形左上角坐标，length为矩形长度，均不包含两侧缎带
{
	/*左侧缎带*/
	Bar64k(x1 - 25, y1 + 25, x1 + 50, y1 + 125, 62496);
	Filltriangle(x1 - 75, y1 + 25, x1 - 25, y1 + 75, x1 - 25, y1 + 25, 62496);
	Filltriangle(x1 - 75, y1 + 125, x1 - 25, y1 + 75, x1 - 25, y1 + 125, 62496);
	Filltriangle(x1, y1 + 100, x1 + 50, y1 + 125, x1 + 50, y1 + 100, 54938);

	/*右侧缎带*/
	Bar64k(x1 + length - 50, y1 + 25, x1 + length + 25, y1 + 125, 62496);
	Filltriangle(x1 + length + 25, y1 + 25, x1 + length + 25, y1 + 75, x1 + length + 75, y1 + 25, 62496);
	Filltriangle(x1 + length + 25, y1 + 125, x1 + length + 25, y1 + 75, x1 + length + 75, y1 + 125, 62496);
	Filltriangle(x1 + length - 50, y1 + 100, x1 + length - 50, y1 + 125, x1 + length, y1 + 100, 54938);

	Bar64k(x1, y1, x1 + length, y1 + 100, 64608);
}

void photo(int x1, int y1, int x2, int y2) //矩形对角线坐标
{
	int x = (x1 + x2) / 2;
	int y = (3 * y1 + y2) / 4;
	Bar64k_radial(x1, y1, x2, y2, 59391, 0);
	Circlefill64k(x, y, (x2 - x1) / 4, 29714);
	Filltriangle(x1 + 10, y2 - 10, x, y, x2 - 10, y2 - 10, 29714);
}

/**************画个头（步兵图标）************/
void Icon_inf(DBL_POS pos, int side)
{	
	int i = 0;
	Icon_draw(pos, side);
	Circlehalf64k(pos.x, pos.y, 8, 49540);
	Bar64k(pos.x - 8, pos.y, pos.x + 8, pos.y + 2, 49540);
	Bar64k(pos.x - 8, pos.y + 2, pos.x + 10, pos.y + 4, 49540);
	for (; i <= 4; i++)
	{
		Line64k(pos.x - 8 - i, pos.y + 4 + i, pos.x - i, pos.y + 4 + i, 49540);
	}
}

/*****画个坦克*******/
void Icon_tank(DBL_POS pos, int side)
{
	Icon_draw(pos, side);
	Bar64k(pos.x-7, pos.y-10, pos.x+7, pos.y+12, 63488); //车身 
	Bar64k(pos.x-3, pos.y-10, pos.x+3, pos.y+12, 64526); //炮塔
	Bar64k(pos.x-1, pos.y, pos.x+1, pos.y+18, 49540);
	Circlefill64k(pos.x, pos.y, 5, 49540); //炮管
}

/**************画个刀（超级兵图标）************/
void Icon_super(DBL_POS pos, int side)
{
	int i;
	Icon_draw(pos, side);
	for (i = -3; i < 4; i++)
	{
		Liney(pos.x+i, pos.y-8-(3-i), pos.x+i, pos.y+8, 23468);
	}
	for (i = 0; i < 3;i++)
	{
		Linex(pos.x-5-i, pos.y+8+i, pos.x+5+i, pos.y+8+i, 23468);
	}
	for (i = 0; i < 8; i++)
	{
		if (i % 4 == 3)
		{
			Linex(pos.x-3, pos.y+11+i, pos.x+3, pos.y+11+i, 23468);
		}
		else
		{
			Linex(pos.x-2, pos.y+11+i, pos.x+2, pos.y+11+i, 23468);
		}
	}
}

/*********带圆角的方形按钮***********/
void rect_button(int x1, int y1, int x2, int y2, char* s, int color)
{
	int ra = (x2 - x1) / 10;
	Bar64k(x1+ra, y1, x2-ra, y1+ra, color);
	Bar64k(x1, y1+ra, x2, y2-ra, color);
	Bar64k(x1+ra, y2-ra, x2-ra, y2, color);
	Circlefill64k(x1 + ra, y1 + ra, ra, color);
	Circlefill64k(x1 + ra, y2 - ra, ra, color);
	Circlefill64k(x2 - ra, y1 + ra, ra, color);
	Circlefill64k(x2 - ra, y2 - ra, ra, color);
	Outtextxx(x1+(ra/2), (y1+y2)/2-16, x2-(ra/2),s, 32, 0);
}

/*********方形按钮加框，标亮使用***********/
void rect_btn_frame(int x1, int y1, int x2, int y2, char* s, int color)
{
	int ra = (x2 - x1) / 10;
	Linex(x1 + ra, y1 + 1, x2 - ra, y1 + 1, color);
	Liney(x1 + 1, y1 + ra, x1 + 1, y2 - ra, color);
	Liney(x2 - 1, y1 + ra, x2 - 1, y2 - ra, color);
	Linex(x1 + ra, y2 - 1, x2 - ra, y2 - 1, color);
	Circle_rd64k(x2 - ra, y2 - ra, ra - 1, color);
	Circle_ru64k(x2 - ra, y1 + ra, ra - 1, color);
	Circle_ld64k(x1 + ra, y2 - ra, ra - 1, color);
	Circle_lu64k(x1 + ra, y1 + ra, ra - 1, color);
	Linex(x1 + ra, y1 + 2, x2 - ra, y1 + 2, color);
	Liney(x1 + 2, y1 + ra, x1 + 2, y2 - ra, color);
	Liney(x2 - 2, y1 + ra, x2 - 2, y2 - ra, color);
	Linex(x1 + ra, y2 - 2, x2 - ra, y2 - 2, color);
	Circle_rd64k(x2 - ra, y2 - ra, ra - 2, color);
	Circle_ru64k(x2 - ra, y1 + ra, ra - 2, color);
	Circle_ld64k(x1 + ra, y2 - ra, ra - 2, color);
	Circle_lu64k(x1 + ra, y1 + ra, ra - 2, color);
}

/*********标亮方形按钮***********/
int light_r_btn(int x1, int y1, int x2, int y2, char* s, int color)
{
	if (MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2)
	{
		Clrmous();
		MouseS = 1;

		while (1)//标亮后生成新鼠标，解决反复标亮问题（避免使用多个状态记录变量），lyd原创 XD
		{
			Newxy();
			if (MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2)
			{
				rect_btn_frame(x1, y1, x2, y2, s, 33808);
				if (press == 1)
				{
					return 1;
				}//若点击返回1
			}
			else
			{
				Clrmous();
				MouseS = 0;
				rect_btn_frame(x1, y1, x2, y2, s, color); //覆写方框，加快绘图速度
				return 0;
			}//离开区域
		}
	}
	else
	{
		return 0;
	}
}