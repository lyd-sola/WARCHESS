#include "common.h"

void xy_tran(float x, float y, int* n_1, int* n_2) //��ʵ�����������θ�������ת��
{
	float x2, y2, a, b, tmp;
	int n1, n2;
	x2 = x - X0; //������ϵ���MouseX
	y2 = y - Y0; //������ϵ���MouseY
	n1 = x2 / WIDTH + 1; //���ط�������꣬�ڼ���
	n2 = y2 / LENGTH + 1; //���ط��������꣬�ڼ���
	a = n1 * WIDTH - WIDTH / 2; //���ط����е������
	b = n2 * LENGTH - LENGTH / 2; //���ط����е�������
	tmp = f(x2, a, b, n1, n2);

	/**���ݵ��λ�������ط�����б���Ϸ������·�ȷ������������**/
	*n_2 = (y2 < tmp) ? n2 : (n2 + 1); 
	/**���ݵ��λ�������ط�����б���Ϸ������·��Լ����ط�������������ż��ȷ�����Ӻ�����**/
	if (n1 % 2 == 1) //���ط�������Ϊ������ֱ�Ӽ���
	{
		*n_1 = (n1 + 1) / 2;  //1��3��5...��Ӧ1. 2. 3;
	}
	else            //���ط�������Ϊż���������ж�������ż��
	{
		if (n2 % 2 == 1)  //���ط�������Ϊ����
		{
			*n_1 = (y2 > tmp) ? (n1 / 2 + 1) : (n1 / 2);
		}

		else //���ط�������Ϊż��
		{
			*n_1 = (y2 < tmp) ? (n1 / 2 + 1) : (n1 / 2);
		}
	}
}

float f(float x, float a, float b, int n1, int n2)
{
	if (n1 % 2 == 1)
	{
		if (n2 % 2 == 1)
			return -K * (x - a) + b;
		else
			return K * (x - a) + b;
	}
	else
	{
		if (n2 % 2 == 1)
			return K * (x - a) + b;
		else
			return -K * (x - a) + b;
	}
}

void xy(int n1, int n2, int *x, int *y)
{
	if (n2 % 2 == 1)
	{
		*x = 103 + (n1 - 1) * 69;
	}
	else
	{
		*x = 69 + (n1 - 1) * 69;
	}
	*y = 54 + (n2 - 1) * 46;
}
/*struct POS xy(int n1, int n2)
{
	struct POS centpos;
	if (n2 % 2 == 1)
	{
		centpos.x = 103 + (n1 - 1) * 68;
	}
	else
	{
		centpos.x = 69 + (n1 - 1) * 68;
	}
	
	centpos.y = 54 + (n2 - 1) * 46;
	return centpos;
}*/