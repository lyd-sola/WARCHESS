/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:
author:
version:
Description:
date:

������־

����Ŀ¼
******************************************************************/
#include "common.h"
//���ظ��ӣ�������������Χ���ĸ���
//xy_tran����ע����Ϊ�ڶ��ֽ�ϵ��ʽ

POS xy2cell(int x, int y) //��ʵ������˫���������ת��
{
	POS cell;
	double x2, y2, a, b, tmp;
	int n1, n2;
	x2 = x - X0; //������ϵ���MouseX
	y2 = y - Y0; //������ϵ���MouseY
	n1 = x2 / WIDTH + 1; //���ط�������꣬�ڼ���
	n2 = y2 / LENGTH + 1; //���ط��������꣬�ڼ���
	a = n1 * WIDTH - WIDTH / 2; //���ط����е������
	b = n2 * LENGTH - LENGTH / 2; //���ط����е�������
	tmp = f(x2, a, b, n1, n2);

	/**���ݵ��λ�������ط�����б���Ϸ������·�ȷ������������**/
	cell.y = (y2 < tmp) ? n2 : (n2 + 1);

	/**���ݵ��λ�������ط�����б���Ϸ������·��Լ����ط�������������ż��ȷ�����Ӻ�����**/
	/************  y2 < tmp �жϵ�����������Ƿ���б��֮�϶���֮�£�y������������*****************/
	if (n1 % 2 == 1) //���ط�������Ϊ�����������ж�������ż��
	{
		if (n2 % 2 == 1)  //���ط�������Ϊ����
		{
			cell.x = (y2 < tmp) ? n1 : (n1 - 1);
		}
		else  //���ط�������Ϊż��
		{
			cell.x = (y2 < tmp) ? (n1 - 1) : n1;
		}
		//*n_1 = (n1 + 1) / 2;  //1��3��5...��Ӧ1. 2. 3;
	}
	else            //���ط�������Ϊż���������ж�������ż��
	{
		if (n2 % 2 == 1)  //���ط�������Ϊ����
		{
			cell.x = (y2 < tmp) ? (n1 - 1) : n1;
			//*n_1 = (y2 > tmp) ? (n1 / 2 + 1) : (n1 / 2);
		}
		else //���ط�������Ϊż��
		{
			cell.x = (y2 < tmp) ? n1 : (n1 - 1);
			//*n_1 = (y2 < tmp) ? (n1 / 2 + 1) : (n1 / 2);
		}
	}
	return cell;
}

float f(float x, float a, float b, int n1, int n2)
{
	if (n1 % 2 == 1)
	{
		if (n2 % 2 == 1)
			return K * (x - a) + b;
		else
			return -K * (x - a) + b;
	}
	else
	{
		if (n2 % 2 == 1)
			return -K * (x - a) + b;
		else
			return K * (x - a) + b;
	}
}

 POS center_xy(int row, int col)
{
	POS centpos;
	row = (row + 1) / 2;//�Ļص������
	if (col % 2 == 1)
	{
		centpos.x = 103 + (row - 1) * 69;
	}
	else
	{
		centpos.x = 139 + (row - 1) * 69;
	}
	centpos.y = 54 + (col - 1) * 46;
	centpos.y -= (col - 1) / 3;
	centpos.x -= (row - 1) / 3;
	return centpos;
}

OFF_POS D2O(DBL_POS pos)
{
	OFF_POS opos;
	opos.x = (pos.x - 1) / 2;
	opos.y = pos.y - 1;
	return opos;
}

//�ж��Ƿ��ڵ�ͼ�ڵ������ͼ�ⷵ�أ���ͼ�����޵�λ����1���е�λ����2
int clcmap(DBL_POS* pos, MAP map)
{
	OFF_POS opos;
	if (mouse_press(68, 22, 962, 633) == MOUSE_IN_L)
	{
		*pos = xy2cell(MouseX, MouseY);
		if (1 <= pos->x && pos->x <= 26 && 1 <= pos->y && pos->y <= 13)//��ͼ��Ч�洢����
		{
			opos = D2O(*pos);
			if (map[opos.y][opos.x].geo != OUT_MAP)
			{
				if (map[opos.y][opos.x].kind != NOARMY)
				{
					//��ʾ��Ϣ
					return 2;
				}//�е�λ
				else 
				{
					return 1;
				}//�޵�λ
			}
			else
			{
				return 0;
			}//��ͼ������
		}
		else
		{
			return 0;
		}//��ͼ��Ч����
	}
	else
	{
		return 0;
	}//δ���
}

