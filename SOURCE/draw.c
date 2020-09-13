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

//x1, y1, x2, y2为对角线两点坐标
void shadow(int x1, int y1, int x2, int y2, int color1, int color2) 
{
	Bar64k(x1 + 5, y1 + 5, x2 + 5, y2 + 5, 33808);
	Bar64k(x1, y1, x2, y2, color1);
	Bar64k(x1+2, y1+2, x2, y2, color2);
}

void shadow_l(int x1, int y1, int x2, int y2, int color)
{
	Bar64k(x1 + 10, y1 + 10, x2 + 10, y2 + 10, 33808);
	Bar64k(x1, y1, x2, y2, color);
	rectangle64k(x1, y1, x2, y2, 33808);
}

void frame(int x1, int y1, int x2, int y2, int color)
{
	Bar64k(x1, y1, x2, y2, color);
	rectangle64k(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 33808);
}

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
Function：		Bar64k_radial
Description：	按钮绘制函数
Calls：			Line64k
Input:			x1,y1,x2,y2长方形区域范围
				color颜色

Author：		刘云笛
**********************************************************/
void Button(int y1,char *s, int color, int color2)
{
	int x1 = 780, x2 = 1024;
	int height = 30, i;
	for (i = x2; i >= x1; i--)
	{
		Line64k(i, y1, i, y1 + height, color);
	}
	for (i = 1; i <= height; i ++)
	{
		Line64k(x1 - i, y1, x1 - i, y1 + height - i, color);
	}
	for (i = 0; i <= height - 7; i++)
	{
		Putpixel64k(x1 - height + 10 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 11 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 12 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 13 + i, y1 + 4 + i, color2);
	}
	Bar64k(x1 + 4, y1 + height - 3, x1 + 2 + 64, y1 + height - 5, color2);
	Outtext(1024 - 4 * 55, y1 - 16, s, 32, 55, 0);
}