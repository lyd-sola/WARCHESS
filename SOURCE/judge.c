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
int range(MAP map, DBL_POS pos, int able, int mode, int visit[7][7])//�п��е㷵��1���޷���0
{
	OFF_POS opos = D2O(pos), otop, onew;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//��������
	int nx, ny, mcost;
	struct NODE {
		DBL_POS pos;//˫���������
		int abl;//��������
	}queue[35], top, neww;//bfs����
	int front = 0, rear = 0, i;//������β��ʹ��ѭ�������Ż�
	int flag = 0;//������޵��ڷ�Χ��
	neww.pos.x = pos.x;
	neww.pos.y = pos.y;
	neww.abl = 0;
	queue[rear++ % 25] = neww;//push����һ����
	while (rear != front)//bfs������Ϊ������������
	{
		top = queue[front++ % 25];//pop������
		if (top.abl == able)//�����߹�������
			continue;
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
						flag = 1;
						if (map[onew.y][onew.x].kind == NOARMY)//û�е�λ������
						{
							queue[rear++ % 25] = neww;
							visit[ny][nx] = neww.abl;
						}
					}
					else
					{
						queue[rear++ % 25] = neww;
						visit[ny][nx] = neww.abl;
					}//���������ڵ����Ȼ��ڣ�
					if (rear - front >= 35)
						show_error("��Χ������������", 1);
				}
			}
		}
	}
	visit[3][3] = -1;//��ԭ���ĵ㣬������·��
	return flag;
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
	DBL_POS now, next, minpos, path[5];//path����·����ջ
	int nx, ny, i, top = 0, min;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//��������
	ofrom = D2O(FROM);
	oto = D2O(TO);
	nx = oto.x - ofrom.x + 3;
	ny = oto.y - ofrom.y + 3;
	if (nx < 0 || nx > 6 || ny < 0 || ny > 6 || visit[ny][nx] == 0)//visit�⣬�򲻿ɵ���
		return 0;
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
		if (top > 4)
			show_error("·������ջ���!", 1);
		path[top++] = now;
	}//·������
	show_msg("�о���", "");
	Clrmous();
	show_visit(FROM, visit, Map_partial);//��ԭ�����ĸ���
	map[oto.y][oto.x].stay = 0;//�ƶ����פ��״̬
	map[oto.y][oto.x].flag = 1;//������ƶ�
	map[oto.y][oto.x].health = map[ofrom.y][ofrom.x].health;
	map[oto.y][oto.x].kind = map[ofrom.y][ofrom.x].kind;
	map[oto.y][oto.x].side = map[ofrom.y][ofrom.x].side;//�ƶ�
	map[ofrom.y][ofrom.x].kind = NOARMY;//������������
	anime_path(map, path, top, map[oto.y][oto.x].kind, map[oto.y][oto.x].side);//��ʾ�ƶ�·��
	return 1;
}
/*�ƶ�����*/
void anime_path(MAP map, DBL_POS* path, int top, int kind, int side)
{
	DBL_POS lpos, pos;
	POS center;

	lpos = path[--top];//topָ��ջ����һ������ʱȡ��������
	while (top > 0)//pop��·��
	{
		--top;
		pos = path[top];
		recover_cell(lpos, map);//��ԭ�˴���ͼ
		center = center_xy(pos.x, pos.y);
		icon(center, side, kind);
		delay(200);
		lpos = pos;
	}
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

int victory_judge(MAP map)
{
	if (map[3][10].kind == 0)
	{
		delay(1000);
		if (msgbar("��ս", "�˳�", "���ʤ���ˣ�", "�����������ǻ۸������������ӡ��"))
			return 1;
		else
			exit(0);
	}
	if (map[9][1].kind == 0)
	{
		delay(msg_sec);
		if (msgbar("��ս", "�˳�", "����ʤ���ˣ�", "�����������ǻ۸������������ӡ��"))
			return 1;
		else
			exit(0);
	}
	return 0;
}