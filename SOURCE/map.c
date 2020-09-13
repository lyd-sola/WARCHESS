#include "common.h"

void xy_tran(float x, float y, int* n_1, int* n_2) //真实坐标与六边形格子坐标转换
{
	float x2, y2, a, b, tmp;
	int n1, n2;
	x2 = x - X0; //换坐标系后的MouseX
	y2 = y - Y0; //换坐标系后的MouseY
	n1 = x2 / WIDTH + 1; //神秘方格横坐标，第几个
	n2 = y2 / LENGTH + 1; //神秘方格纵坐标，第几排
	a = n1 * WIDTH - WIDTH / 2; //神秘方格中点横坐标
	b = n2 * LENGTH - LENGTH / 2; //神秘方格中点纵坐标
	tmp = f(x2, a, b, n1, n2);

	/**根据点击位置在神秘方格中斜线上方或者下方确定格子纵坐标**/
	*n_2 = (y2 < tmp) ? n2 : (n2 + 1); 
	/**根据点击位置在神秘方格中斜线上方或者下方以及神秘方格行列数的奇偶性确定格子横坐标**/
	if (n1 % 2 == 1) //神秘方格列数为奇数，直接计算
	{
		*n_1 = (n1 + 1) / 2;  //1，3，5...对应1. 2. 3;
	}
	else            //神秘方格列数为偶数，继续判断行数奇偶性
	{
		if (n2 % 2 == 1)  //神秘方格行数为奇数
		{
			*n_1 = (y2 > tmp) ? (n1 / 2 + 1) : (n1 / 2);
		}

		else //神秘方格行数为偶数
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