/*****************���ļ�������λѧ���Ĺ������������ܴ�����******************************/


/*********************************************************************************
Copyright(c)  2019 ���׽�&������  �ᵺ��ϰ����ģ��ϵͳ 
file_name: outtext.h
data: 2019.9.11
author: ���׽�&������
version: 3.1
Description: ���ֿ� 

******************************************************************/




#ifndef  outtext_h
#define  outtext_h

void Outtext(int x,int y, char *s, int size, int part, int color);
 
void out_ASC(int x, int y, char *s, int color);

void out_ASCplus(int x, int y, char *s, int color);

int Outtext24(int x1,int y1,int x2,int y2, char *s, int part, int color);

unsigned long puthz(int x0,int y0,char *path,unsigned long len,int page);

void CHtext16(int x,int y,char *s,int color);

void ENtext16( int x,int y,char s,int color);
#endif
