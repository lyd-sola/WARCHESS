/**********************************************************
Copyright (C) 2018  ���׽�&������  �ᵺ��ϰ����ģ��ϵͳ 
File name:		SVGAmode.c
Author:			���׽�&������
Version��		3.2
Date��			2017/9/3
Description��	SVGA��ʾģʽʵ���ļ���������ģʽ�»����ĳ�ʼ��������������������ͼ��������ͼ�����ȵ�ʵ�֡�
				�괦����SVGAmode.h�С�
				
				��Ϊ�궨���Ե�ʣ��Ͻ��������ļ��ж�������ΪR��G��B��r��g��b�ı�����
				Ϊ����graphics.h�еĺ�������������д����������ĸ��д��
				������д����������Ļ�ο�ϵΪ׼��
				
				Putbmp16������������ͬѧ���룬����Line��Circle��CirclefillΪ���ϴ��룬�����빤������
				
				�Ա��ļ����޸��뼰ʱ�����¸�ʽ��¼�����棨ÿ���޸ĵ����г�����

Function List��
	1.void SetSVGA256(void);
		SVGA��ʾģʽ���ú�������Ϊ0x105
		
	2.void SetSVGA64k(void);
		SVGA��ʾģʽ���ú�������Ϊ0x117
	
	3.unsigned int GetSVGA(void);
		��ȡSVGA��ʾģʽ��bx
		
	4.void Selectpage(register char page);
		���жϹ��ܵĻ�ҳ�����������д�Դ�ʱ���Ѱַ����
		
		
	6.void Putpixel64k(int x, int y, unsigned int color);
		���㺯����������ͼ�����Ļ�������������0x117ģʽ��		
		
	8.int Putbmp64k(int x, int y, const char * path);
		24λ��ѹ��bmpͼ��λ��ʾ����
	
	9.void Xorpixel(int x, int y, unsigned char color);
		��λ��򻭵㺯��
		
	10.void Horizline(int x, int y, int width, unsigned char color);
		��ˮƽ�ߺ���
		
	12.void Line64k(int x1, int y1, int x2, int y2, unsigned int color)��
		64kģʽ��һ��ֱ�ߺ���
		
	14.void Bar64k(int x1, int y1, int x2, int y2, unsigned int color);
		64kģʽ�����ο麯��
		
	15.void rectangle64k(int x1, int y1, int x2, int y2, unsigned int color);
		64kģʽ�����ο���
		
	16.void Circle64k(int xc, int yc, int radius, unsigned int color);
		64kģʽ��ԲȦ����
		
	18.void Circlefill64k(int xc, int yc, int radius, unsigned int color);
		64kģʽ��ʵ��Բ����
	
	19.unsigned int Getpixel64k(int x, int y);
		ȡ����ɫ��������������0x117ģʽ��
	
	20.void Circlehalf64k(int xc, int yc, int radius, unsigned int color);
		���ϰ�Բ�ĺ���
		
	21.void Circleright64k(int xc, int yc, int radius, unsigned int color);
		���Ұ�ԲȦ
		
	22.void Circleleft64k(int xc, int yc, int radius, unsigned int color);
		�����ԲȦ
		
	23.int Linex(int x1, int y1, int x2, int y2, int color);
		��ˮƽֱ��

	24.int Liney(int x1, int y1, int x2, int y2, int color);
		����ֱֱ��

	25.void Floodfill(int x, int y, int fillcolor, int borcolor);
		�������

	26.void Filltriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);
		ƽ��ʵ�������Σ�y0=y2��
		
	27.void Circleup64k(int xc, int yc, int radius, unsigned int color);
		���ϰ�Բ��
		
	28.void Circlerd64k(int xc, int yc, int radius, unsigned int color);
		�����°�Բ��
**********************************************************/
#ifndef	SVGA_H
#define	SVGA_H

#include "common.h"

/*��ͼ������ɫ����ɫ�ṹ*/
typedef struct
{
	unsigned char R;	/*��ɫ������RED��д*/
	unsigned char G;	/*��ɫ������GREEN��д*/
	unsigned char B;	/*��ɫ������BLUE��д*/
} COLORS;

/*24λbmpͼ��ɫ�ṹ*/
typedef struct
{
	unsigned char B;	/*��ɫ������BLUE��д*/
	unsigned char G;	/*��ɫ������GREEN��д*/
	unsigned char R;	/*��ɫ������RED��д*/
} COLORS24;

/*bmpλͼ��ɫ����ɫ�ṹ*/
typedef struct tagRGBQUAD
{
    unsigned char b;	/*��ɫ������RED��д*/
	unsigned char g;	/*��ɫ������GREEN��д*/
	unsigned char r;	/*��ɫ������BLUE��д*/
	unsigned char reserved;		/*������*/
} RGBQUAD;

/*bmpλͼ��Ϣͷ��������˵��λͼ�ĳߴ����Ϣ*/
typedef struct tagBITMAPINFOHEADER
{
	unsigned long int biSize;	/*���ṹ��ռ���ֽ�����15-18�ֽڣ�*/
	long int biWidth;			/*λͼ�Ŀ�ȣ�������Ϊ��λ��19-22�ֽڣ�*/
	long int biHeight;			/*λͼ�ĸ߶ȣ�������Ϊ��λ��23-26�ֽڣ�*/
	unsigned int biPlanes;		/*Ŀ���豸�ļ��𣬱���Ϊ1(27-28�ֽڣ�*/
	unsigned int biBitCount;	/*ÿ�����������λ����������1��˫ɫ����4(16ɫ����8(256ɫ��16(�߲�ɫ)��24�����ɫ��֮һ��29-30�ֽڣ�*/
	unsigned long int biCompression;	/*λͼѹ�����ͣ�������0����ѹ������1(BI_RLE8ѹ�����ͣ���2(BI_RLE4ѹ�����ͣ�֮һ��31-34�ֽڣ�*/
	unsigned long int biSizeImage;		/*λͼ�Ĵ�С(���а�����Ϊ�˲���������4�ı�������ӵĿ��ֽ�)�����ֽ�Ϊ��λ��35-38�ֽڣ�*/
	long int biXPelsPerMeter;			/*λͼˮƽ�ֱ��ʣ�ÿ����������39-42�ֽڣ�*/
	long int biYPelsPerMeter;			/*λͼ��ֱ�ֱ��ʣ�ÿ����������43-46�ֽ�)*/
	unsigned long int biClrUsed;		/*λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ�*/
	unsigned long int biClrImportant;	/*λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ�*/
} BITMAPINFOHEADER;


extern void SetSVGA256(void);


extern void SetSVGA64k(void);

extern unsigned int GetSVGA(void);

extern void Selectpage(register char page);

extern void Putpixel64k(int x, int y, unsigned int color);

extern int Putbmp64k(int x, int y, const char * path);

extern void Xorpixel(int x, int y, unsigned char color);

extern void Horizline(int x, int y, int width, unsigned char color);

extern void Line64k(int x1, int y1, int x2, int y2, unsigned int color);

extern void Bar64k(int x1, int y1, int x2, int y2, unsigned int color);

extern void rectangle64k(int x1, int y1, int x2, int y2, unsigned int color);

extern void Circle64k(int xc, int yc, int radius, unsigned int color);

extern void Circlefill64k(int xc, int yc, int radius, unsigned int color);

extern unsigned int Getpixel64k(int x, int y);

extern int Putbmp16(const char * path);			/*16λȫ����ͼ����*/

extern void Circlehalf64k(int xc, int yc, int radius, unsigned int color);

extern void Circleright64k(int xc, int yc, int radius, unsigned int color);

extern void Circleleft64k(int xc, int yc, int radius, unsigned int color);

extern void LightBarWiden(int x1, int y1, int x2 ,int y2 ,int color);

int Linex(int x1, int y1, int x2, int y2, int color);

int Liney(int x1, int y1, int x2, int y2, int color);

void Floodfill(int x, int y, int fillcolor, int borcolor);

void Filltriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);

void Circleup64k(int xc, int yc, int radius, unsigned int color);

void Circlerd64k(int xc, int yc, int radius, unsigned int color);

int Map_partial(int x1, int y1, int x2, int y2);

void Circle_rd64k(int xc, int yc, int radius, unsigned int color);
void Circle_ru64k(int xc, int yc, int radius, unsigned int color);
void Circle_lu64k(int xc, int yc, int radius, unsigned int color);
void Circle_ld64k(int xc, int yc, int radius, unsigned int color);
void Circlefill_ld64k(int xc, int yc, int radius, unsigned int color);

#endif