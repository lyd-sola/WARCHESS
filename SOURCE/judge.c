/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: judge.c
author: ���Ƶ�
version:
Description: �������ƶ����жϣ��㷨�ѶȺ��ģ�
date:

������־
	10/11 range����������ɣ�visit�������ĵ���γ�ʼ���������ѭ���б��Ż������
	10/12 ѭ�������Ż���ɣ�visit�������ĵ��ʼ��Ϊ-1������ᴩ����λ������

******************************************************************/
#include "common.h"
//ע��visit����Ϊƫ�����꣬��ʼ��pos��visit[2][2]�������ֵ�����ƶ��Ѷ�


/**********************************************************
Function��		range
Description��	�ƶ��͹����Ϸ���Χ����
				�������������Χ�����ڷ�Χ�ڵĵ㣬��������visit����
				visit������ֵ�����ƶ����õ��������ĵ������������ƶ�ʱ����·��
Input:			ableΪ���룬mode0Ϊ�ƶ���1Ϊ������visit����5*5���ڼ�¼���е�
Author��		���Ƶ�
�㷨������		*ʹ��˫���������*
				�������θ�������Ҳ����ʹ�÷������飬������˱��㷨��û����ż���жϣ�
				*ʹ�ù�����������㷨*
				��Ȼ�ƶ�ʱ�ڵ���Ȩ��ͬ��������ԭ�ز������Ӳ����ķ�����֤��bfs�������У�ÿһ�㲽����ͬ����
				ͬʱ���Լ�������·��
**********************************************************/
void range(MAP map, DBL_POS pos, int able, int mode, int visit[5][5])
{
	OFF_POS opos = D2O(pos), otop, onew;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//��������
	int nx, ny, mcost;
	struct NODE {
		DBL_POS pos;//˫���������
		int abl;//��������
	}queue[25], top, neww;
	int front = 0, rear = 0, i;//������β��ʹ��ѭ�������Ż�


	POS p;//test


	neww.pos.x = pos.x;
	neww.pos.y = pos.y;
	neww.abl = 0;
	queue[rear++ % 25] = neww;//push����һ����
	//memset(visit, 0, sizeof(visit));

	while (rear != front)//bfs������Ϊ������������
	{
		top = queue[front++ % 25];//pop������
		if (top.abl == able)//�����߹�������
		{
			continue;
		}
		neww.abl = top.abl + 1;
		otop = D2O(top.pos);
		queue[rear++ % 25] = neww;//ԭ�����Ӳ�����ʵ�����������ĵ�0��
		for (i = 0; i < 6; i++)//����������
		{
			neww.pos.x = top.pos.x + dx[i];
			neww.pos.y = top.pos.y + dy[i];
			onew = D2O(neww.pos);
			nx = onew.x - opos.x + 2;
			ny = onew.y - opos.y + 2;
			mcost = mode ? 1 : move_cost(map[onew.y][onew.x].geo);//mode=1����cost������޹�
			if (map[onew.y][onew.x].geo != OUT_MAP
				&& 1 <= neww.pos.x && neww.pos.x <= 26 && 1 <= neww.pos.y && neww.pos.y <= 13)//��ͼ��
			{
				if (!visit[ny][nx]//û��������
					&& neww.abl - visit[otop.y - opos.y + 2][otop.x - opos.x + 2] == mcost//�ߵö���������
					
					&& !(ny == 2 && nx == 2))//���ĵ�������˰�
				{
					if (mode == 0)
					{
						if (map[onew.y][onew.x].kind == NOARMY)//û�е�λ������
						{
							queue[rear++ % 25] = neww;
							visit[ny][nx] = neww.abl;

							//test
							/*p = center_xy(neww.pos.x, neww.pos.y);
							Icon_draw(p, 1);*/
						}
					}
					else
					{
						queue[rear++ % 25] = neww;
						visit[ny][nx] = neww.abl;
						//test
						/*p = center_xy(neww.pos.x, neww.pos.y);
						Icon_draw(p, 1);*/
					}//���������ڵ����Ȼ��ڣ�
				}
			}
		}
	}
	visit[2][2] = -1;//��ԭ���ĵ㣬������·��
}
/**********************************************************
Function��		moving
Description��	����visit���鷴���ƶ�·��������ʾ���ƶ��Ķ���
Input:			fromΪ�����㣬toΪĿ���
Output:			����0��ʾ����visit�����1�ƶ��ɹ�����㺯����Ҫ�жϵ���Ƿ�Ϸ���
Author��		���Ƶ�
**********************************************************/
int moving(MAP map, int visit[5][5], DBL_POS FROM, DBL_POS TO)
{
	OFF_POS ofrom, oto, onow, onext;
	DBL_POS now, next, minpos;
	POS npos;
	int nx, ny, i, nxtx, nxty;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//��������

	DBL_POS path[5];
	int top = 0;//����·����ջ
	int min;

	ofrom = D2O(FROM);
	oto = D2O(TO);
	npos = center_xy(FROM.x, FROM.y);
	nx = oto.x - ofrom.x + 2;
	ny = oto.y - ofrom.y + 2;
	if (visit[ny][nx] == 0)
	{
		return 0;
	}//���ɵ���

	now = TO;
	path[top++] = now;
	while (!(now.x == FROM.x && now.y == FROM.y))
	{
		min = 666;
		onow = D2O(now);
		for (i = 0; i < 6; i++)
		{
			next.x = now.x + dx[i];
			next.y = now.y + dy[i];
			onext = D2O(next);
			nxtx = onext.x - ofrom.x + 2;
			nxty = onext.y - ofrom.y + 2;
			if (0 <= nxtx && nxtx <= 2 && 0 <= nxty && nxty <= 2 && visit[nxty][nxtx])
			{
				if (visit[nxty][nxtx] < min)//��Χ������С������һ��������������Ĳ�ͬ����
				{
					min = visit[nxty][nxtx];
					minpos = next;
				}
			}
		}
		now = minpos;
		path[top++] = now;
	}//·������
	anime_path(map, path, top);
	return 1;
}
/*�ƶ�����*/
void anime_path(MAP map, DBL_POS* path, int top)
{
	OFF_POS onow;
	POS pos;
	int side;
	int kind;

	top--;
	onow = D2O(path[top]);
	kind = map[onow.y][onow.x].kind;
	side = map[onow.y][onow.x].side;
	for (; top >= 0; top--)//pop��·��
	{
		pos = center_xy(path[top].x, path[top].y);
		icon(pos, side, kind);
		delay(1000);
	}
}