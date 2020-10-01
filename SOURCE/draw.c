/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESS
file_name: draw.c
author: ����ͩ�����Ƶ�
version: 1.5
Description: �Զ����ͼ����
date:2020/9/8

������־
9.8		��������Ӱ���߿��Զ����ͼ����
9.9		�����˻����ĵ�ͼ��
9.10	����Ϊsvga
9.11	lyd���ӿ�ͼ��ͼ����
9.12	lyd���Ӹı����Ⱥ�����ɾ��outtextxyc����

����Ŀ¼
1.shadow/shadow_l: 			���ƴ�������Ӱ���ı���
2.frame: 					���ƴ��߿���ı���
3.filedraw:					�����ĵ�ͼ��
4.Bar64kc/linec/outtextxyc��	����ǰ��ɫ���ú�������ͨͼ�κ���
	5.void GetBackground(int left,int top,int right,int bottom,short *buffer);
		�洢ĳһ��Χ����ͼ�����ڶ�����������bufferͼƬ�洢��ַ���ɹ�����0��
		
	6.void GetBackground(int left,int top,int right,int bottom,short *buffer);
		�Ż�ĳһ��Χ����ͼ�����ڶ�����������bufferͼƬ�洢��ַ���ɹ�����0��
		
******************************************************************/
#include"common.h"

void file_draw(int x1, int y1, int x2, int y2) //x2 - x1 ����������
{
	shadow_l(x1, y1, x2, y2, 65504);
	frame(x1+15, y1+15, x2-15, y2-15, 65535);

	/* ����x2-x1Ϊ���γ��ȣ������������Ϊ60��80����Բ����
	   ����Ϊ����һ��
	   Ȼ������ֱ�߷�� 
	   setcolor(LIGHT33808);
	ellipse((x2-x1)/2+x1, y1, 0, 180, (x2-x1)/2-60, ((x2-x1)/2-60)/2); 
	ellipse((x2-x1)/2+x1, y1, 0, 180, (x2-x1)/2-80, ((x2-x1)/2-80)/2);
	line(x2-60, y1, x2-80, y1);
	line(x1+60, y1, x1+80, y1);
	setfillstyle(1, LIGHT33808);
	floodfill((x2-x1)/2+x1,y1-(((x2-x1)/2-80)/2)-5,LIGHT33808);*/
}

//ͨ������������������ʡȥ����part��ʱ�䣬ͬʱ����partֵ
int Outtextxx(int x1, int y, int x2, char *s,int flag, int color)
{
	int num = strlen(s) / 2;				//���ָ���
	int part = (x2-x1-flag) / (num - 1);	//�ɺ������鳤�� length = x2 - x1 = flag + (num - 1) X part �����
	Outtext(x1, y, s, flag, part, color);
	return part;
}

/*****************************************
������ͼ�ͻ�ԭ����
Author�����Ƶ�
bufferΪ�洢������
*****************************************/
void GetBackground(int left, int top, int right, int bottom, short *buffer)//��ȡ����
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

void PutBackground(int left, int top, int right, int bottom, short *buffer)//���ر���
{     
    int i, j;    
    int Width, Height;     

    Width=right - left;
    Height=bottom - top;
    for(i = 0; i<= Height;i ++)//�����ɸı仭��˳��
    {
        for(j = 0;j <= Width;j ++)         
        {
            Putpixel64k(left + i, top + j, buffer[i*Width + j]);
        }   
    }    
}

/*****************************************
��Ļ��һ����������Ⱥ�����ʵ����ͬ�����Ӹ���rgb��ֵ������˵�ǰ׶ȣ���
drgb��ֵΪ��ױ���
Author�����Ƶ�
*****************************************/

unsigned int Lightcolor(unsigned int colorbf, float drgb)
{
	unsigned int rbf, gbf, bbf;
	/*����RGBֵ*/
	rbf = colorbf / (1 << 11);
	gbf = colorbf % (1 << 11) / (1 << 5);
	bbf = colorbf % (1 << 5);
	/*���rgb�д���0���޷��ı�ı�õ�*/
	if (rbf * gbf * bbf == 0)
	{
		return colorbf;
	}
	/*���drgb����*/
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
	/*���ģ�ÿ����rgbֵ������ͬ����������ʵ�ֱ��*/
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
����Ϊ�ߡ�bar���������Ⱥ���
ʵ������SVGAmode.c�и����������޸ĵõ��������������
Author�����Ƶ�
*****************************************/
void Lightline(int x1, int y1, int x2, int y2, float drgb)
{
	int	dx, dy;			/*ֱ��x��y�����ֵ*/
	int dx2, dy2;		/*�ӿ������ٶȵ��м�ֵ*/
	int xinc, yinc;		/*�ж��롢y���ӷ���ķ���ֵ*/
	int d, dxy;			/*���߱���*/
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
	/*tempΪ��ʱ������ѭ������*/
	/*widthΪ���γ�*/
	int temp, width;
	int i, j;
	/*x��������*/
	if (x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}

	/*y��������*/
	if (y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}


	/*����ɨ�軭������*/
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
Function��		Bar64k_radial_re
Description��	��������Ի������ο�ʹ�÷���ͬBar64k�����һ������Ϊ���ӳ�ʱ�䣨��λmm��

Calls��			rectangle64k

Author��		���Ƶ�
**********************************************************/
void Bar64k_radial_re(int x1, int y1, int x2, int y2, unsigned int color, int fill_time)
{
	int n, t, i;

	if (x2 - x1 > y2 - y1)
	{
		n = ceil(((float)y2 - y1) / 2);//����ȡ��
	}
	else
	{
		n = ceil(((float)y2 - y1) / 2);//����ȡ��
	}
	t = fill_time / (n + 1);

	for (i = 0; i <= n; i++)
	{
		rectangle64k(x1 + i, y1 + i, x2 - i, y2 - i, color);
		delay(t);//���ܻ���Ҫ����
	}
}
/**********************************************************
Function��		Bar64k_radial
Description��	��������Ի������ο�ʹ�÷���ͬBar64k�����һ������Ϊ���ӳ�ʱ�䣨��λmm��

Calls��			rectangle64k

Author��		���Ƶ�
**********************************************************/
void Bar64k_radial(int x1, int y1, int x2, int y2, unsigned int color, int fill_time)
{
	int n, t;

	if (x2 - x1 > y2 - y1)
	{
		n = ceil(((float)y2 - y1) / 2);//����ȡ��
	}
	else
	{
		n = ceil(((float)y2 - y1) / 2);//����ȡ��
	}
	t = fill_time / (n + 1);

	for (; n >= 0; n--)
	{
		rectangle64k(x1 + n, y1 + n, x2 - n, y2 - n, color);
		delay(t);//���ܻ���Ҫ����
	}
}
/**********************************************************
Function��		Button
Description��	��ť���ƺ���
Calls��			Line64k
Input:			y1��ť����y���꣬s��ť�Ϻ��֣��ĸ�����ѣ�
				color1��ɫ��color2����ɫ

Author��		���Ƶ�
ps �������Riddle Joker�����������µ�һ��
����Ų������˿������
**********************************************************/
void Button(int y1,char *s, int color, int color2)
{
	int x1 = 750, x2 = 1024;
	int height = 30, i;//bar��С274*30
	for (i = x2; i >= x1; i--)
	{
		Line64k(i, y1, i, y1 + height, color);
	}
	for (i = 1; i <= height; i ++)
	{
		Line64k(x1 - i, y1, x1 - i, y1 + height - i, color);
	}//��������ɨ�裬���ٿ���Ч��
	for (i = 0; i <= height - 7; i++)
	{
		Putpixel64k(x1 - height + 10 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 11 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 12 + i, y1 + 4 + i, color2);
		Putpixel64k(x1 - height + 13 + i, y1 + 4 + i, color2);
	}//����װ�λ��ƻ���
	Bar64k(x1 + 4, y1 + height - 3, x1 + 2 + 64, y1 + height - 5, color2);
	Outtext(1024 - 4 * 55 - 20, y1 - 16, s, 32, 55, 0);
}
/**********************************************************
Function��		Line45
Description��	��45�Ƚ�б�ߣ�������Խ������˵�
Input:			x1,y1,��ʼ��,x2�յ�x����
				color��ɫ

Author��		���Ƶ�
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
	sign = (y2 - y1) / abs(y2 - y1);//Ϊ���������»�
	num = x2 - x1;
	for (i = 0; i <= num; i++)
	{
		Putpixel64k(x1 + i, y1 + sign * i, color);
	}
}

/**********************************************************
Function��		Icon_draw
Description��	��ͼ��߿�
Input:			pos�������ĵ�����
				side��Ӫ
Author��		���Ƶ�
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
Function��		Icon_builder
Description��	�������ӣ�����ͼ�꣩
Input:			pos�������ĵ�����
				color��ɫ

Author��		���Ƶ�
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
	Line45(pos.x, 3 + pos.y, -8 + pos.x, 11 + pos.y, color1);//��������
}

//x1, y1, x2, y2Ϊ�Խ�����������
void diamond(int x1, int y1, int x2, int y2, int x3, int y3, int color) //y1��y2������ͬ
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
}//Ϊʲô��Ҫд���������أ���Ϊ���ü�����

void move_button(int color)
{
	rectangle64k(20, 528, 141, 649, 0);
	rectangle64k(20+1, 528+1, 141-1, 649-1, 0);
	Bar64k_radial(20 + 2, 528 + 2, 141 - 2, 649 - 2, color, 0);
	Outtext(20+27, 528+44, "�ƶ�", 32, 35, 0);
}

void del_button(int color)
{
	rectangle64k(20, 649+3, 262, 649+3+45, 0);
	rectangle64k(20 + 1, 649 + 4, 262 - 1, 649+2+45, 0);
	Bar64k_radial(20 + 2, 649 + 5, 262 - 2, 649 + 46, color, 0);
	Outtext(85, 649+9, "ɾ��", 32, 16+60, 0);
}

void nextr_button(int color)
{
	Circlefill64k(849+68, 514+68, 68, color);
	Circle64k(849 + 68, 514 + 68, 69, 0);
	Circle64k(849 + 68, 514 + 68, 68, 0);
	Circle64k(849 + 68, 514 + 68, 67, 0);
	Outtextxx(849 + 68 - 40, 514 - 40 + 68, 849 + 40 + 68, "��һ", 32, 0);
	Outtextxx(849 + 68 - 40, 514 + 40 - 32 + 68, 849 + 68 + 40, "�غ�", 32, 0);
}