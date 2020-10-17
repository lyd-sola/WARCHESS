/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: judge.c
author: 刘云笛
version:
Description: 攻击和移动的判断（算法难度核心）
date:

更新日志
	10/11 range函数基本完成，visit数组中心点如何初始化待解决，循环列表优化待解决
	10/12 循环链表优化完成，visit数组中心点初始化为-1，解决会穿过单位的问题

******************************************************************/
#include "common.h"
//注：visit数组为偏移坐标，起始点pos在visit[2][2]，里面的值代表移动难度


/**********************************************************
Function：		range
Description：	移动和攻击合法范围计算
				计算出出发点周围所有在范围内的点，并储存于visit数组
				visit数组中值代表移动到该点最少消耗的体力，用于移动时反推路径
Input:			able为距离，mode0为移动，1为攻击，visit数组5*5用于记录可行点
Author：		刘云笛
算法分析：		*使用双倍宽度坐标*
				让六边形格子坐标也可以使用方向数组，极大简化了本算法（没有奇偶性判断）
				*使用广度优先搜索算法*
				虽然移动时节点间边权不同，但采用原地不动增加步数的方法保证了bfs正常进行（每一层步数相同），
				同时可以计算出最短路径
**********************************************************/
void range(MAP map, DBL_POS pos, int able, int mode, int visit[5][5])
{
	OFF_POS opos = D2O(pos), otop, onew;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//方向数组
	int nx, ny, mcost;
	struct NODE {
		DBL_POS pos;//双倍宽度坐标
		int abl;//可用消耗
	}queue[25], top, neww;
	int front = 0, rear = 0, i;//数组首尾，使用循环队列优化


	POS p;//test


	neww.pos.x = pos.x;
	neww.pos.y = pos.y;
	neww.abl = 0;
	queue[rear++ % 25] = neww;//push进第一个点
	//memset(visit, 0, sizeof(visit));

	while (rear != front)//bfs，队列为空则搜索结束
	{
		top = queue[front++ % 25];//pop出队首
		if (top.abl == able)//步数走够不搜索
		{
			continue;
		}
		neww.abl = top.abl + 1;
		otop = D2O(top.pos);
		queue[rear++ % 25] = neww;//原地增加步数，实际上是搜索的第0向
		for (i = 0; i < 6; i++)//六向搜索！
		{
			neww.pos.x = top.pos.x + dx[i];
			neww.pos.y = top.pos.y + dy[i];
			onew = D2O(neww.pos);
			nx = onew.x - opos.x + 2;
			ny = onew.y - opos.y + 2;
			mcost = mode ? 1 : move_cost(map[onew.y][onew.x].geo);//mode=1攻击cost与地形无关
			if (map[onew.y][onew.x].geo != OUT_MAP
				&& 1 <= neww.pos.x && neww.pos.x <= 26 && 1 <= neww.pos.y && neww.pos.y <= 13)//地图内
			{
				if (!visit[ny][nx]//没有搜索过
					&& neww.abl - visit[otop.y - opos.y + 2][otop.x - opos.x + 2] == mcost//走得动，向外搜
					
					&& !(ny == 2 && nx == 2))//中心点别再走了吧
				{
					if (mode == 0)
					{
						if (map[onew.y][onew.x].kind == NOARMY)//没有单位才能走
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
					}//攻击不受遮挡（迫击炮）
				}
			}
		}
	}
	visit[2][2] = -1;//还原中心点，用于推路径
}
/**********************************************************
Function：		moving
Description：	利用visit数组反推移动路径，并显示出移动的动画
Input:			from为出发点，to为目标点
Output:			返回0表示不在visit里，返回1移动成功（外层函数需要判断点击是否合法）
Author：		刘云笛
**********************************************************/
int moving(MAP map, int visit[5][5], DBL_POS FROM, DBL_POS TO)
{
	OFF_POS ofrom, oto, onow, onext;
	DBL_POS now, next, minpos;
	POS npos;
	int nx, ny, i, nxtx, nxty;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//方向数组

	DBL_POS path[5];
	int top = 0;//储存路径的栈
	int min;

	ofrom = D2O(FROM);
	oto = D2O(TO);
	npos = center_xy(FROM.x, FROM.y);
	nx = oto.x - ofrom.x + 2;
	ny = oto.y - ofrom.y + 2;
	if (visit[ny][nx] == 0)
	{
		return 0;
	}//不可到达

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
				if (visit[nxty][nxtx] < min)//周围步数最小的是上一步，解决地形消耗不同问题
				{
					min = visit[nxty][nxtx];
					minpos = next;
				}
			}
		}
		now = minpos;
		path[top++] = now;
	}//路径计算
	anime_path(map, path, top);
	return 1;
}
/*移动动画*/
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
	for (; top >= 0; top--)//pop出路径
	{
		pos = center_xy(path[top].x, path[top].y);
		icon(pos, side, kind);
		delay(1000);
	}
}