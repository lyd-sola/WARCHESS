#ifndef _DRAW_H_
#define _DRAW_H_

#define X0 69			//ԭ��x����
#define Y0 54		//ԭ��y����
#define WIDTH 34.365	//һ�����ظ��ӵ�y����߳�,�������ҳ�һ��
#define LENGTH 45.75	//һ�����ظ��ӵ�y����߳�
#define K 0.5143		//ֱ��б�ʵľ���ֵ

POS xy2cell(int x, int y);
float f(float x, float a, float b, int n1, int n2);
void xy(int n1, int n2, int* x, int* y);
POS center_xy(int row, int col);
OFF_POS D2O(DBL_POS pos);//˫���������ת��Ϊƫ������
DBL_POS O2D(OFF_POS pos);//ƫ������ת��Ϊ˫���������
int clcmap(DBL_POS* pos, MAP map);//�ж��Ƿ��ڵ�ͼ�ڵ������ͼ�ⷵ�أ���ͼ�����޵�λ����1���е�λ����2
int move_cost(int geo);//�����ƶ����ģ�-1Ϊ�޷�����
int inside_map(MAP map, DBL_POS pos);
void draw_cell(DBL_POS pos, MAP map);
void recover_cell(DBL_POS pos, MAP map);
void show_visit(DBL_POS pos, int visit[7][7], void (*lightfun)(int x1, int y1, int x2, int y2));
#endif
