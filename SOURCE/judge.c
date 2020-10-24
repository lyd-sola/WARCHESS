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
				ע��Ŀǰ�ƶ���������Ϊ3��������Ҫ�޸�visit�������������
Input:			ableΪ���룬mode0Ϊ�ƶ���1Ϊ������visit����5*5���ڼ�¼���е�
Author��		���Ƶ�
�㷨������		*ʹ��˫���������*
				�������θ�������Ҳ����ʹ�÷������飬������˱��㷨��û����ż���жϣ�
				*ʹ�ù�����������㷨*
				��Ȼ�ƶ�ʱ�ڵ���Ȩ��ͬ��������ԭ�ز������Ӳ����ķ�����֤��bfs�������У�ÿһ�㲽����ͬ����
				ͬʱ���Լ�������·��
**********************************************************/
void range(MAP map, DBL_POS pos, int able, int mode, int visit[7][7])
{
	OFF_POS opos = D2O(pos), otop, onew;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//��������
	int nx, ny, mcost;
	struct NODE {
		DBL_POS pos;//˫���������
		int abl;//��������
	}queue[35], top, neww;
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
		neww.pos = top.pos;
		neww.abl = top.abl + 1;
		queue[rear++ % 25] = neww;//ԭ�����Ӳ�����ʵ�����������ĵ�0��
		otop = D2O(top.pos);
		for (i = 0; i < 6; i++)//����������
		{
			neww.pos.x = top.pos.x + dx[i];
			neww.pos.y = top.pos.y + dy[i];
			onew = D2O(neww.pos);
			nx = onew.x - opos.x + 3;
			ny = onew.y - opos.y + 3;
			mcost = mode ? 1 : move_cost(map[onew.y][onew.x].geo);//mode=1����cost������޹�
			
			if(inside_map(map, neww.pos))//��ͼ��
			{
				if (!visit[ny][nx]//û��������
					&& neww.abl - visit[otop.y - opos.y + 3][otop.x - opos.x + 3] == mcost//�ߵö���������
					
					&& !(ny == 3 && nx == 3))//���ĵ�������˰�
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
					if (rear - front == 35)
						show_error("�������", 1);
				}
			}
		}
	}
	visit[3][3] = -1;//��ԭ���ĵ㣬������·��
}
/**********************************************************
Function��		moving
Description��	����visit���鷴���ƶ�·��������ʾ���ƶ��Ķ���
Input:			fromΪ�����㣬toΪĿ���
Output:			����0��ʾ����visit�����1�ƶ��ɹ�����㺯����Ҫ�жϵ���Ƿ�Ϸ���
Author��		���Ƶ�
**********************************************************/
int moving(MAP map, int visit[7][7], DBL_POS FROM, DBL_POS TO)//�ɹ�����1��ʧ��0
{
	OFF_POS ofrom, oto, onext;
	DBL_POS now, next, minpos;
	int nx, ny, i;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//��������

	DBL_POS path[5];
	int top = 0;//����·����ջ
	int min;

	ofrom = D2O(FROM);
	oto = D2O(TO);
	nx = oto.x - ofrom.x + 3;
	ny = oto.y - ofrom.y + 3;
	if (nx < 0 || nx > 6 || ny < 0 || ny > 6 || visit[ny][nx] == 0)
	{
		return 0;
	}//visit�⣬�򲻿ɵ���

	now = TO;
	path[top++] = now;
	while (!(now.x == FROM.x && now.y == FROM.y))//һ��һ������
	{
		min = 666;
		for (i = 0; i < 6; i++)
		{
			next.x = now.x + dx[i];
			next.y = now.y + dy[i];
			onext = D2O(next);
			nx = onext.x - ofrom.x + 3;
			ny = onext.y - ofrom.y + 3;
			if (0 <= nx && nx <= 6 && 0 <= ny && ny <= 6 && visit[ny][nx])
			{
				if (visit[ny][nx] < min)//��Χ������С������һ��������������Ĳ�ͬ����
				{
					min = visit[ny][nx];
					minpos = next;
				}
			}
		}
		now = minpos;
		path[top++] = now;
	}//·������
	show_msg("�о���", "");
	anime_path(map, path, top);
	return 1;
}
/*�ƶ�����*/
void anime_path(MAP map, DBL_POS* path, int top)
{
	OFF_POS onow;
	POS lpos, pos;
	int side;
	int kind;

	top--;
	onow = D2O(path[top]);
	kind = map[onow.y][onow.x].kind;
	side = map[onow.y][onow.x].side;
	for (; top > 0; top--)//pop��·��
	{
		pos = center_xy(path[top].x, path[top].y);
		Map_partial(lpos.x - 18, lpos.y - 18, lpos.x + 18, lpos.y + 23, FBMP);//��ԭ�˴���ͼ
		icon(pos, side, kind);
		delay(1000);
		lpos = pos;
	}
	pos = center_xy(path[top].x, path[top].y);
	Clrmous();
	Map_partial(lpos.x - 18, lpos.y - 18, lpos.x + 18, lpos.y + 23, FBMP);//��ԭ�˴���ͼ
	icon(pos, side, kind);

	//pos = center_xy(path[top].x, path[top].y);
	//icon(pos, side, kind);
}

int attack_judge(MAP map, int able, DBL_POS dpos, DBL_POS dto)//�ɹ�����1��ʧ��0
{
	OFF_POS opos, oto;
	int nx, ny;

	int visit[7][7];

	memset(visit, 0, sizeof(visit));
	range(map, dpos, able, 1, visit);

	opos = D2O(dpos);
	oto = D2O(dto);
	nx = oto.x - opos.x + 3;
	ny = oto.y - opos.y + 3;
	if (nx < 0 || nx > 6 || ny < 0 || ny > 6 || visit[ny][nx] == 0)
	{
		return 0;
	}//visit�⣬�򲻿ɵ���
	return 1;
}