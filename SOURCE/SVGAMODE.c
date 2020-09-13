/**********************************************************
���ļ���15������ѧ����д��17����־ΰѧ���ṩ���������ܴ����� 
File name:		SVGAmode.c
Author:			����&��־ΰ
Version��		3.2
Description��	SVGA��ʾģʽʵ���ļ���������ģʽ�»����ĳ�ʼ��������������������ͼ��������ͼ�����ȵ�ʵ�֡�
				�괦����SVGAmode.h�С�
				
				��Ϊ�궨���Ե�ʣ��Ͻ��������ļ��ж�������ΪR��G��B��r��g��b�ı�����
				Ϊ����graphics.h�еĺ�������������д����������ĸ��д��
				������д����������Ļ�ο�ϵΪ׼��
				
				Putbmp16������������ͬѧ���룬����Line��Circle��CirclefillΪ���ϴ��룬�����빤������
				
				�Ա��ļ����޸��뼰ʱ�����¸�ʽ��¼�����棨ÿ���޸ĵ����г�����


**********************************************************/

#include "SVGAmode.h"

void SetSVGA256(void)
{
	/*****************************************************
	��dos.h��REGS�Ķ������£�
	struct WORDREGS
	{
		unsigned int ax, bx, cx, dx, si, di, cflag, flags;
	};
	
	struct BYTEREGS
	{
		unsigned char al, ah, bl, bh, cl, ch, dl, dh;
	};
	
	union REGS
	{
		struct WORDREGS x;
		struct BYTEREGS h;
	};
	����al��Ӧax�ĵͰ�λ��ah��Ӧax�ĸ߰�λ���Դ����ơ�
	����ʱ��Ҫ����������ڲ���ȡֵ,��ȡ����ֵ��ʾ����Ϣ��
	*****************************************************/
	union REGS graph_regs;
	
	/*����VESA VBEģʽ�Ĺ��ܺ�*/
	graph_regs.x.ax = 0x4f02;
	graph_regs.x.bx = 0x105;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*ax != 0x004f��ζ�ų�ʼ��ʧ�ܣ����������Ϣ����,��ͬ*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
}


void SetSVGA64k(void)
{
	/*REGS���������*/
	union REGS graph_regs;
	
	/*����VESA VBEģʽ�Ĺ��ܺ�*/
	graph_regs.x.ax = 0x4f02;
	graph_regs.x.bx = 0x117;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*ax != 0x004f��ζ�ų�ʼ��ʧ�ܣ����������Ϣ����,��ͬ*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
}


unsigned int GetSVGA(void)
{
	/*REGS���������*/
	union REGS graph_regs;
	
	/*��ȡ��ǰVESA VBEģʽ�Ĺ��ܺ�*/
	graph_regs.x.ax = 0x4f03;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*��ʾ������Ϣ*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in getting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
	
	return graph_regs.x.bx;
}


void Selectpage(register char page)
{
	union REGS r;
	static unsigned char old_page=0;//��һ�ε�ҳ�棬����ÿ�ε��øú�����Ҫʹ�ã�����Ϊ��̬����
	static unsigned char flag=0;
	r.x.ax =0x4f05;
	r.x.bx=0;//��ҳ���ܺ��趨
	if (flag == 0)
	{
		old_page = page;
		r.x.dx = page;
		int86(0x10, &r, &r);
		flag++;
	}
	if(page!=old_page)
	{
		old_page = page;//������һ�ε�ҳ��
		r.x.dx = page;
		int86(0x10, &r, &r);
	}
}


/**********************************************************
Function��		Putpixel64k

Description��	���㺯����������ͼ�����Ļ�������������0x117ģʽ��

Calls��			Selectpage

Called By��		Putbmp64k
				MousePutBk
				MouseDraw
				
Input��			int x					���غ����꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y					���������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				unsigned int color		��ɫ��������64k��

Output��		����Ļ�ϻ�ָ����ɫ�ĵ�

Return��		None
Others��		None
**********************************************************/
void Putpixel64k(int x, int y, unsigned int color)
{
	/*�Դ�ָ�볣����ָ���Դ��׵�ַ��ָ�뱾�������޸�*/
	unsigned int far *const video_buffer = (unsigned int far *)0xa0000000L;
	
	/*Ҫ�л���ҳ���*/
	unsigned char new_page;
	
	/*��Ӧ�Դ��ַƫ����*/
	unsigned long int page;
	
	/*�жϵ��Ƿ�����Ļ��Χ�ڣ����ھ��˳�*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*�����Դ��ַƫ�����Ͷ�Ӧ��ҳ��ţ�����ҳ����*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 15;	/*32k����һ��ҳ������32k������㷨*/
	Selectpage(new_page);
	
	/*���Դ�д����ɫ����Ӧ�㻭��*/
	video_buffer[page] = color;	
}

/**********************************************************
Function��		Putbmp64k

Description��	24λ��ѹ��bmpͼ��λ��ʾ������
				ֻ֧��24λ��ѹ��bmpͼ����������������Ϊ1024��
				����bmp���;���֧�֣�
				����0x117ģʽ��ʹ�ã�
				Ϊ�˼򻯣�û�������ļ����ͼ�⹦�ܼ�⹦�ܣ�������벻��Ҫ����ļ���

Calls��			Putpixel64k

				fseek
				fread
				fclose
				outportb
				malloc
				free

Called By��		AutoSimulate
				HandOperate
				Menu
				
Input��			int x		ͼƬ���Ͻǵĺ����꣨��Ļ�ο�ϵ��
				int y		ͼƬ���Ͻǵ������꣨��Ļ�ο�ϵ��
				const char * path	bmpͼƬ·��

Output��		��Ļ����ʾͼƬ

Return��		0	��ʾ�ɹ�
				-1	��ʾʧ��
				
Others��		None
**********************************************************/
int Putbmp64k(int x, int y, const char * path)
{
	/*ָ��ͼƬ�ļ����ļ�ָ��*/
	FILE * fpbmp;
	
	/*�����ػ���ָ��*/
	COLORS24 * buffer;
	
	/*ͼƬ�Ŀ�ȡ��߶ȡ�һ��������ռ�ֽ�������������ֽڣ�*/
	long int width, height, linebytes;
	
	/*ѭ������*/
	int i, j;
	
	/*ͼƬλ��*/
	unsigned int bit;
	
	/*ѹ��������*/
	unsigned long int compression;
	
	/*���ļ�*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		return 0;
	}
	
	/*��ȡλ��*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);
	
	/*��24λͼ���˳�*/
	if (bit != 24U)
	{
		return 0;
	}
	
	/*��ȡѹ������*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	
	/*����ѹ���㷨���˳�*/
	if (compression != 0UL)
	{
		return 0;
	}
	
	/*��ȡ��ȡ��߶�*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	
	/*��ȳ������˳�*/
	if (width > SCR_WIDTH)
	{
		return 0;
	}

	/*����һ������ռ�ֽ�������������Ŀ��ֽ�*/
	linebytes = (3 * width) % 4;
	
	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}

	/*�������������ݶ�̬����ռ�*/
	if ((buffer = (COLORS24 *)malloc(linebytes)) == 0)
	{
		return 0;
	}
	
	/*��ɨ����ʽ��ȡͼƬ���ݲ���ʾ*/
	fseek(fpbmp, 54L, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*��ȡһ����������*/
		
		/*һ�����ص����ݴ���ͻ���*/
		for (j = 0; j < width; j++)
		{
			/*0x117ģʽ�£�ԭͼ��������8λ�ֱ����Ϊ5λ��6λ��5λ*/
			buffer[j].R >>= 3;
			buffer[j].G >>= 2;
			buffer[j].B >>= 3;
			Putpixel64k(j + x, i + y,
			((((unsigned int)buffer[j].R) << 11)
			| (((unsigned int)buffer[j].G) << 5)
			| ((unsigned int)buffer[j].B)));	/*����������ɫ���������Ӹ�λ����λ����*/
		}
	}
	
	free(buffer);	
	fclose(fpbmp);
	
	return 1;	
}

/**********************************************************
Function��		Xorpixel

Description��	��λ��򻭵㺯��

Calls��			Selectpage

Called By��		XorCarBmp
				
Input��			int x					���غ����꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y					���������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				unsigned char color		��ɫ��������256��

Output��		����Ļ�ϻ�����

Return��		None
Others��		None
**********************************************************/
void Xorpixel(int x, int y, unsigned char color)
{
	/*�Դ�ָ�볣����ָ���Դ��׵�ַ��ָ�뱾�������޸�*/
	unsigned char far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*Ҫ�л���ҳ���*/
	unsigned char new_page;
	
	/*��Ӧ�Դ��ַƫ����*/
	unsigned long int page;
	
	/*�жϵ��Ƿ�����Ļ��Χ�ڣ����ھ��˳�*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*�����Դ��ַƫ�����Ͷ�Ӧ��ҳ��ţ�����ҳ����*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;
	Selectpage(new_page);
	
	/*��λ���ʽ���Դ�д����ɫ����Ӧ�㻭��*/
	video_buffer[page] ^= color;	
}

/**********************************************************
Function��		Horizline

Description��	��ˮƽ�ߺ���
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ����ʱӦ��ֹ�����ش�����

Calls��			Selectpage

Called By��		Line
				Bar
				Circlefill

Input��			int x					��ʼ������꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y					��ʼ�������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int width				ˮƽ���ȣ�Ϊ���������죬Ϊ����������
				unsigned char color		��ɫ��������256��

Output��		��Ļ�ϻ���ˮƽ��

Return��		None
Others��		None
**********************************************************/
void Horizline(int x, int y, int width, unsigned char color)
{
	/*�Դ�ָ�볣����ָ���Դ��׵�ַ��ָ�뱾�������޸�*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	
	/*Ҫ�л���ҳ���*/
	unsigned char new_page;
	
	/*��Ӧ�Դ��ַƫ����*/
	unsigned long int page;
	
	/*i��x����ʱ����������ѭ������*/
	int i;
	
	/*�ж����췽������ʼ�㿿��*/
	if (width < 0)
	{
		x = x + width;
		width = -width;
	}
	
	i = x;
	
	/*ʡ�Գ�����Ļ��߲���*/
	if (x < 0)
	{
		x = 0;
		width += i;
	}
	
	/*����������Ļ��ʱ�˳�*/
	if (x >= SCR_WIDTH)
	{
		return;
	}
	
	/*����������Ļ��ʱ�˳�*/
	if (y < 0 || y >= SCR_HEIGHT)
	{
		return;
	}
	
	/*ʡ�Գ�����Ļ�ұ߲���*/
	if (x + width > SCR_WIDTH)
	{
		width = SCR_WIDTH - x;
	}
	
	/*�����Դ��ַƫ�����Ͷ�Ӧ��ҳ��ţ�����ҳ����*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;
	Selectpage(new_page);
	
	/*���Դ�д����ɫ��ˮƽ�߻���*/
	for (i = 0; i < width; i++)
	{
		*(video_buffer + page + i) = color;
	}
}



/**********************************************************
Function��		Line64k

Description��	��һ��ֱ�ߺ���
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ����ʱӦ��ֹ�����ش�����

Calls��			Putpixel256
				
				abs

Called By��		LightSW
				LightNE
				LightNW
				LightSE

Input��			int x1					��ʼ������꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y1					��ʼ�������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int x2					��ֹ������꣨��Ļ�ο�ϵ��
				int y2					��ֹ�������꣨��Ļ�ο�ϵ��
				unsigned char color		��ɫ��������65536��

Output��		��Ļ�ϻ���ֱ��

Return��		None
Others��		None
**********************************************************/
void Line64k(int x1, int y1, int x2, int y2, unsigned int color)
{
	int	dx, dy;			/*ֱ��x��y�����ֵ*/
	int dx2, dy2;		/*�ӿ������ٶȵ��м�ֵ*/
	int xinc, yinc;		/*�ж��롢y���ӷ���ķ���ֵ*/
	int d, dxy;			/*���߱���*/
	int i;
	/*���������ֵ���м����*/
	dx = abs(x2 - x1);
	dx2 = dx << 1;
	dy = abs(y2 - y1);
	dy2 = dy << 1;
	
	/*�ж�ֱ��x�������ӷ���*/
	if (x2 > x1)
	{
		xinc = 1;
	}
	
	/*�������ֱ��*/
	else if (x2 == x1)
	{
		/*y��������*/
		if (y1 > y2)
		{
			dx = y1;
			y1 = y2;
			y2 = dx;
		}
		
		/*����ֱ��*/
		for (dx = y1; dx <= y2; dx++)
		{
			Putpixel64k(x1, dx, color);
		}
		
		return;
	}
	
	else
	{
		xinc = -1;
	}
	
	/*�ж�ֱ��y�������ӷ���*/
	if (y2 > y1)
	{
		yinc = 1;
	}
	
	/*�����ˮƽ��*/
	else if (y2 == y1)
	{
		for(i=x1;i<=x2;i++)
		{
			Putpixel64k(i,y1,color);
		}
		return;
	}
	
	else
	{
		yinc = -1;
	}
	
	/*******************************
	��������Bresenham�㷨����ֱ�ߡ�
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	*******************************/
	Putpixel64k(x1, y1, color);
	
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
			Putpixel64k(x1, y1, color);
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
			}
			
			y1 += yinc;
			Putpixel64k(x1, y1, color);
		}
	}
}



/**********************************************************
Function��		Bar64k
Description��	�����ο麯��
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ�Ĳ���ʱӦ��ֹ�����ش�����

Calls��			Horizline

Called By��		LightSW
				LightNE
				LightNW
				LightSE

Input��			int x1					�Խǵ�1�ĺ����꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y1					�Խǵ�1�������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int x2					�Խǵ�2�ĺ����꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y2					�Խǵ�2�������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				unsigned char color		��ɫ��������65535��

Output��		��Ļ�ϻ������ο�

Return��		None
Others��		None
**********************************************************/
void Bar64k(int x1, int y1, int x2, int y2, unsigned int color)
{
	/*tempΪ��ʱ������ѭ������*/
	/*widthΪ���γ�*/
	int temp, width;
	int i,j;
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
	for(i=x1;i<=x2;i++)
	{
		Line64k(i,y1,i,y2,color);
			/*for(j=y1;j<=y2;j++)
			{
					Putpixel64k(i,j,color);
			}*/
	}
}



/**********************************************************
Function��		rectangle64k
Description��	�����ο���
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ�Ĳ���ʱӦ��ֹ�����ش�����

Calls��			rectangle64k

Called By��		LightSW
				LightNE
				LightNW
				LightSE

Input��			int x1					�Խǵ�1�ĺ����꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y1					�Խǵ�1�������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int x2					�Խǵ�2�ĺ����꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y2					�Խǵ�2�������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				unsigned char color		��ɫ��������65535��

Output��		��Ļ�ϻ������ο�

Return��		None
Others��		None
**********************************************************/
void rectangle64k(int x1, int y1, int x2, int y2, unsigned int color)
{
	/*tempΪ��ʱ������ѭ������*/
	int temp;
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
	
	
	/*�������ο�*/
	Line64k(x1, y1, x2, y1,color);			//���ϲ�ˮƽֱ��
	Line64k(x1, y1, x1, y2,color);			//�������ֱֱ��
	Line64k(x1, y2, x2, y2,color);			//���²�ˮƽֱ��
	Line64k(x2, y2, x2, y1,color);			//���Ҳ���ֱֱ��
}


/**********************************************************
Function��		Circle64k
Description��	��ԲȦ����
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ�Ĳ���ʱӦ��ֹ�����ش�����

Calls��			Putpixel256

Called By��		LightSW
				LightNE
				LightNW
				LightSE

Input��			int xc					x_center����д��Բ�ĺ����꣨��Ļ�ο�ϵ��
				int yc					y_center����д��Բ�������꣨��Ļ�ο�ϵ��
				int radius				�뾶������Ϊ��
				unsigned char color		��ɫ��������65535��

Output��		��Ļ�ϻ���ԲȦ

Return��		None
Others��		None
**********************************************************/
void Circle64k(int xc, int yc, int radius, unsigned int color)
{
	/*��ԲȦ�Ķ�λ�����;��߱���*/
	int x, y, d;
	
	/*�뾶����Ϊ���������˳�*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	��������Bresenham�㷨����ԲȦ��
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	************************************/
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(xc + x, yc + y, color);
		Putpixel64k(xc + x, yc - y, color);
		Putpixel64k(xc - x, yc - y, color);
		Putpixel64k(xc - x, yc + y, color);
		Putpixel64k(xc + y, yc + x, color);
		Putpixel64k(xc + y, yc - x, color);
		Putpixel64k(xc - y, yc - x, color);
		Putpixel64k(xc - y, yc + x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}

/**********************************************************
Function��		Circlefill64k
Description��	��ʵ��Բ����
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ�Ĳ���ʱӦ��ֹ�����ش�����

Calls��			Horizline

Called By��		LightColorR
				LightColorY
				LightColorG
				LightColor1
				LightColor2
				LightColor3
				LightColor4
				LightColorD1
				LightColorD2
				LightColorD3
				TrafficLight

Input��			int xc					x_center����д��Բ�ĺ����꣨��Ļ�ο�ϵ��
				int yc					y_center����д��Բ�������꣨��Ļ�ο�ϵ��
				int radius				�뾶������Ϊ��
				unsigned char color		��ɫ��������65536��

Output��		��Ļ�ϻ���ԲȦ

Return��		None
Others��		None
**********************************************************/
void Circlefill64k(int xc, int yc, int radius, unsigned int color)
{
	/*��ԲȦ�Ķ�λ�����;��߱���*/
	int x = 0,
		y = radius,
		dx = 3,
		dy = 2 - radius - radius,
		d = 1 - radius;
	
	/*�뾶����Ϊ���������˳�*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	��������Bresenham�㷨����ʵ��Բ��
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	************************************/
	while (x <= y)
	{
	
		Line64k(xc - x, yc - y, xc + x, yc - y, color);
		Line64k(xc - y, yc - x, xc + y, yc - x, color);
		Line64k(xc - y, yc + x, xc + y, yc + x, color);
		Line64k(xc - x, yc + y, xc + x, yc + y, color);
        
        if (d < 0)
        {
            d += dx;
            dx += 2;
        }
        
        else
        {
            d += (dx + dy);
            dx += 2;
            dy += 2;
            y--;
		}

        x++;
	}
}
/**********************************************************
Function��		Getpixel64k

Description��	ȡ����ɫ��������������0x117ģʽ��

Calls��			Selectpage
				
Called By��		MouseStoreBk

Input��			int x	���غ����꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y	���������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��

Output��		None

Return��		unsigned int	��Ӧ��������Դ��������ɫ
				
Others��		None
**********************************************************/


unsigned int Getpixel64k(int x, int y)
{
	/*�Դ�ָ�볣����ָ���Դ��׵�ַ��ָ�뱾�������޸�*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	
	/*Ҫ�л���ҳ���*/
	unsigned char new_page;
	
	/*��Ӧ�Դ��ַƫ����*/
	unsigned long int page;
	
	/*�жϵ��Ƿ�����Ļ��Χ�ڣ����ھ��˳�*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return 0;
	}
	
	/*�����Դ��ַƫ�����Ͷ�Ӧ��ҳ��ţ�����ҳ����*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 15;	/*32k����һ��ҳ������32k������㷨*/
	Selectpage(new_page);
	
	/*������ɫ*/
	return video_buffer[page];	
}
int Putbmp16( const char * path)
{
	unsigned long shift;
	long int bfoffbits;
	unsigned int far *const head=(unsigned int far *)0xa0000000L;
	unsigned int* buffer;
	register int i,j,k;
	unsigned int width,height;
	FILE * fpbmp;
	fpbmp=fopen(path, "rb");
	if(fpbmp==NULL)
	{
		return 0;
	}
	if ((buffer = (unsigned int*)malloc(1024*2)) == 0)
	{
		return 0;
	}
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	fseek(fpbmp,0x0a,SEEK_SET);
	fread(&bfoffbits,sizeof(long),1,fpbmp);
	fseek(fpbmp,bfoffbits,SEEK_SET);
	for (i =24; i>0; i--)
	{
		Selectpage(i-1);
		for (j = 32; j>0; j--)
		{
			fread(buffer,1024,2, fpbmp);	
			_fmemcpy(head+((i-1)*32+j-1)*1024,buffer,1024*2);
		}
	}
	free(buffer);
	fclose(fpbmp);
	return 1;	
}


/**********************************************************
Function��		Circlehalf64k
Description��	��ʵ���ϰ�Բ����
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ�Ĳ���ʱӦ��ֹ�����ش�����

Calls��			Horizline

Called By��		LightColorR
				LightColorY
				LightColorG
				LightColor1
				LightColor2
				LightColor3
				LightColor4
				LightColorD1
				LightColorD2
				LightColorD3
				TrafficLight

Input��			int xc					x_center����д��Բ�ĺ����꣨��Ļ�ο�ϵ��
				int yc					y_center����д��Բ�������꣨��Ļ�ο�ϵ��
				int radius				�뾶������Ϊ��
				unsigned char color		��ɫ��������65536��

Output��		��Ļ�ϻ����ϰ�ԲȦ

Return��		None
Others��		None
**********************************************************/
void Circlehalf64k(int xc, int yc, int radius, unsigned int color)
{
	/*��ԲȦ�Ķ�λ�����;��߱���*/
	int x = 0,
		y = radius,
		dx = 3,
		dy = 2 - radius - radius,
		d = 1 - radius;
	
	/*�뾶����Ϊ���������˳�*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	��������Bresenham�㷨����ʵ��Բ��
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	************************************/
	while (x <= y)
	{
	
		Line64k(xc - x, yc - y, xc + x, yc - y, color);
		Line64k(xc - y, yc - x, xc + y, yc - x, color);
        
        if (d < 0)
        {
            d += dx;
            dx += 2;
        }
        
        else
        {
            d += (dx + dy);
            dx += 2;
            dy += 2;
            y--;
		}

        x++;
	}
}

/**********************************************************
Function��		Circleleft64k
Description��	�����ԲȦ����
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ�Ĳ���ʱӦ��ֹ�����ش�����

Calls��			Putpixel256

Called By��		LightSW
				LightNE
				LightNW
				LightSE

Input��			int xc					x_center����д��Բ�ĺ����꣨��Ļ�ο�ϵ��
				int yc					y_center����д��Բ�������꣨��Ļ�ο�ϵ��
				int radius				�뾶������Ϊ��
				unsigned char color		��ɫ��������65535��

Output��		��Ļ�ϻ������ԲȦ

Return��		None
Others��		None
**********************************************************/
void Circleleft64k(int xc, int yc, int radius, unsigned int color)
{
	/*��ԲȦ�Ķ�λ�����;��߱���*/
	int x, y, d;
	
	/*�뾶����Ϊ���������˳�*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	��������Bresenham�㷨����ԲȦ��
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	************************************/
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(xc - x, yc - y, color);
		Putpixel64k(xc - x, yc + y, color);
		Putpixel64k(xc - y, yc - x, color);
		Putpixel64k(xc - y, yc + x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}


/**********************************************************
Function��		Circleright64k
Description��	���Ұ�ԲȦ����
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ�Ĳ���ʱӦ��ֹ�����ش�����

Calls��			Putpixel256

Called By��		LightSW
				LightNE
				LightNW
				LightSE

Input��			int xc					x_center����д��Բ�ĺ����꣨��Ļ�ο�ϵ��
				int yc					y_center����д��Բ�������꣨��Ļ�ο�ϵ��
				int radius				�뾶������Ϊ��
				unsigned char color		��ɫ��������65535��

Output��		��Ļ�ϻ����Ұ�ԲȦ

Return��		None
Others��		None
**********************************************************/
void Circleright64k(int xc, int yc, int radius, unsigned int color)
{
	/*��ԲȦ�Ķ�λ�����;��߱���*/
	int x, y, d;
	
	/*�뾶����Ϊ���������˳�*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	��������Bresenham�㷨����ԲȦ��
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	************************************/
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(xc + x, yc + y, color);
		Putpixel64k(xc + x, yc - y, color);
		Putpixel64k(xc + y, yc + x, color);
		Putpixel64k(xc + y, yc - x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}


/***�ӿ�滭��ɫ�߿���***/
void LightBarWiden(int x1, int y1, int x2 ,int y2 ,int color)
{
	Line64k(x1+1, y1+1, x2-1, y1+1,color);			//���ϲ�ˮƽֱ��
	Line64k(x1+1, y1+1, x1+1, y2-1,color);			//�������ֱֱ��
	Line64k(x1+1, y2-1, x2-1, y2-1,color);			//���²�ˮƽֱ��
	Line64k(x2-1, y2-1, x2-1, y1+1,color);			//���Ҳ���ֱֱ��
	
	Line64k(x1+2, y1+2, x2-2, y1+2,color);			//���ϲ�ˮƽֱ��
	Line64k(x1+2, y1+2, x1+2, y2-2,color);			//�������ֱֱ��
	Line64k(x1+2, y2-2, x2-2, y2-2,color);			//���²�ˮƽֱ��
	Line64k(x2-2, y2-2, x2-2, y1+2,color);			//���Ҳ���ֱֱ��
}


/*******���º����������׽��������� 	�ᵺ����ģ��ϵͳ*******/

/*******Svgaģʽ�µĻ����ߺ���*******
x1 y1��  ֱ��һ���˵�ĺ�������
x2 y2��ֱ�ߵ���һ���˵�ĺ�����

color ����ɫֵ
************************************/ 
int Linex(int x1, int y1, int x2, int y2, int color)      
{
  int i; 
  if(x1 >= 1024||x2 >= 1024||y1 >= 768||y2 >= 768)
  return(0); 

  if(x1 <= 0||x2 <= 0||y1 <= 0||y2 <= 0) 
  return(0); 

  if(y1 != y2||x1 > x2)     //y1Ҫ��֤��y2���
  return(0); 
  for(i = x1; i <= x2; i ++ )
  Putpixel64k(i, y1, color); 
  return 0; 
}
/*******Svgaģʽ�µĻ����ߺ���******
x1 y1��  ֱ��һ���˵�ĺ�������
x2 y2��ֱ�ߵ���һ���˵�ĺ�����

color ����ɫֵ

************************************/ 
int Liney(int x1, int y1, int x2, int y2, int color)
{
  int i; 
  if(x1 >= 1024||x2 >= 1024||y1 >= 768||y2 >= 768)
  return(0); 

  if(x1 <= 0||x2 <= 0||y1 <= 0||y2 <= 0)
  return(0); 

  if(x1 != x2||y1 > y2)             //x1Ҫ��֤��x2���
  return(0); 
  for(i = y1; i <= y2; i ++ )
  Putpixel64k(x1, i, color); 
  return 0; 
}
/*������չ������㷨
Author:������
Date:2019.10.28*/
void Floodfill(int x, int y, int fillcolor, int borcolor)
{
	if (x >= 0 && x < 1024 && y >= 0 && y <= 768 && Getpixel64k(x, y) != borcolor && Getpixel64k(x, y) != fillcolor)
	{
		Putpixel64k(x, y, fillcolor);
		Floodfill(x + 1, y, fillcolor, borcolor);
		Floodfill(x - 1, y, fillcolor, borcolor);
		Floodfill(x, y + 1, fillcolor, borcolor);
		Floodfill(x, y - 1, fillcolor, borcolor);
	}
	return;
}
/*����ƽ���������㷨��ӵ�и��㷨
�������еĲ�����������ͼ���⽫ӭ�ж���
Author:���׽�
Date:2019.10.27*/
void Filltriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color)
{
	//y0��y2�ױߣ�y1�Ƕ���

	int i;
	double h = y1 - y0;

	double dL = (x1 - x0) / h;
	double dR = (x1 - x2) / h;

	double xL = x0, xR = x2;

	if (y2 != y0)
	{
		return;
	}

	if (y0 < y1)
	{
		for (i = y0; i <= y1; ++i)
		{
			Line64k(xL, i, xR, i, color); //A Simple Function That Just Draw A Line
			xL += dL;
			xR += dR;
		}
	}
	else
	{
		for (i = y0; i >= y1; --i)
		{
			Line64k(xL, i, xR, i, color); //A Simple Function That Just Draw A Line
			xL -= dL;
			xR -= dR;
		}
	}
}

/*******���º����������ƵѶ�ǰ������޸ģ��������ܴ�����*******/
//���ڻ������

void Circleup64k(int xc, int yc, int radius, unsigned int color)
{
	/*��ԲȦ�Ķ�λ�����;��߱���*/
	int x, y, d;
	
	/*�뾶����Ϊ���������˳�*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	��������Bresenham�㷨����ԲȦ��
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	************************************/
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(xc + x, yc + y, color);
		Putpixel64k(xc - x, yc + y, color);
		Putpixel64k(xc + y, yc + x, color);
		Putpixel64k(xc - y, yc + x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}

void Circlerd64k(int xc, int yc, int radius, unsigned int color)
{
	/*��ԲȦ�Ķ�λ�����;��߱���*/
	int x, y, d;
	
	/*�뾶����Ϊ���������˳�*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	��������Bresenham�㷨����ԲȦ��
	���㷨�ǵõ����ϵĳ���Ŀ����㷨��
	����ϸ����ȥ��
	************************************/
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(xc + x, yc - y, color);
		Putpixel64k(xc + y, yc - x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}