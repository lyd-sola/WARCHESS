#ifndef _DRAW_H_
#define _DRAW_H_



#define X0 69			//ԭ��x����
#define Y0 54		//ԭ��y����
#define WIDTH 34.365	//һ�����ظ��ӵ�y����߳�,�������ҳ�һ��
#define LENGTH 45.75	//һ�����ظ��ӵ�y����߳�
#define K 0.5143		//ֱ��б�ʵľ���ֵ

void xy_tran(float x, float y, int* n1, int* n2);
float f(float x, float a, float b, int n1, int n2);
void xy(int n1, int n2, int* x, int* y);
#endif
