/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: judge.c
author: 刘云笛、陈旭桐
version:2.0
Description: 对局中的较难判断（算法难度核心）
date:2020/10/11

更新日志
	10/11 range函数基本完成，visit数组中心点如何初始化待解决，循环列表优化待解决
	10/12 循环链表优化完成，visit数组中心点初始化为-1，解决会穿过单位的问题
	10/25 增加胜利判断
******************************************************************/
#include "common.h"
//注：visit数组为偏移坐标，起始点pos在visit[2][2]，里面的值代表移动难度

/**********************************************************
Function：		range
Description：	移动和攻击合法范围计算
				计算出出发点周围所有在范围内的点，并储存于visit数组
				visit数组中值代表移动到该点最少消耗的体力，用于移动时反推路径
				注：目前移动能力上限为3，否则需要修改visit数组相关所有数
Input:			able为距离，mode0为移动，1为攻击，visit数组5*5用于记录可行点
Author：		刘云笛
算法分析：		*使用双倍宽度坐标*
				让六边形格子坐标也可以使用方向数组，极大简化了本算法（没有奇偶性判断）
				*使用广度优先搜索算法*
				虽然移动时节点间边权不同，但采用原地不动增加步数的方法保证了bfs正常进行（每一层步数相同），
				同时可以计算出最短路径
**********************************************************/
int range(MAP map, DBL_POS pos, int able, int mode, int visit[7][7])//有可行点返回1，无返回0
{
	OFF_POS opos = D2O(pos), otop, onew;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//方向数组
	int nx, ny, mcost;
	struct NODE {
		DBL_POS pos;//双倍宽度坐标
		int abl;//可用消耗
	}queue[35], top, neww;//bfs队列
	int front = 0, rear = 0, i;//数组首尾，使用循环队列优化
	int flag = 0;//标记有无点在范围内
	neww.pos.x = pos.x;
	neww.pos.y = pos.y;
	neww.abl = 0;
	queue[rear++ % 25] = neww;//push进第一个点
	while (rear != front)//bfs，队列为空则搜索结束
	{
		top = queue[front++ % 25];//pop出队首
		if (top.abl == able)//步数走够不搜索
			continue;
		neww.pos = top.pos;
		neww.abl = top.abl + 1;
		queue[rear++ % 25] = neww;//原地增加步数，实际上是搜索的第0向
		otop = D2O(top.pos);
		for (i = 0; i < 6; i++)//六向搜索！
		{
			neww.pos.x = top.pos.x + dx[i];
			neww.pos.y = top.pos.y + dy[i];
			onew = D2O(neww.pos);
			nx = onew.x - opos.x + 3;
			ny = onew.y - opos.y + 3;
			mcost = mode ? 1 : move_cost(map[onew.y][onew.x].geo);//mode=1攻击cost与地形无关
			if(inside_map(map, neww.pos))//地图内
			{
				if (!visit[ny][nx]//没有搜索过
					&& neww.abl - visit[otop.y - opos.y + 3][otop.x - opos.x + 3] == mcost//走得动，向外搜
					&& !(ny == 3 && nx == 3))//中心点别再走了吧
				{
					if (mode == 0)
					{
						flag = 1;
						if (map[onew.y][onew.x].kind == NOARMY)//没有单位才能走
						{
							queue[rear++ % 25] = neww;
							visit[ny][nx] = neww.abl;
						}
					}
					else
					{
						queue[rear++ % 25] = neww;
						visit[ny][nx] = neww.abl;
					}//攻击不受遮挡（迫击炮）
					if (rear - front >= 35)
						show_error("范围计算队列溢出！", 1);
				}
			}
		}
	}
	visit[3][3] = -1;//还原中心点，用于推路径
	return flag;
}
/**********************************************************
Function：		moving
Description：	利用visit数组反推移动路径，并显示出移动的动画
Input:			from为出发点，to为目标点
Output:			返回0表示不在visit里，返回1移动成功（外层函数需要判断点击是否合法）
Author：		刘云笛
**********************************************************/
int moving(MAP map, int visit[7][7], DBL_POS FROM, DBL_POS TO)//成功返回1，失败0
{
	OFF_POS ofrom, oto, onext;
	DBL_POS now, next, minpos, path[5];//path储存路径的栈
	int nx, ny, i, top = 0, min;
	int dx[] = { 2, 1, -1, -2, -1, 1 };
	int dy[] = { 0, 1, 1, 0, -1, -1 };//方向数组
	ofrom = D2O(FROM);
	oto = D2O(TO);
	nx = oto.x - ofrom.x + 3;
	ny = oto.y - ofrom.y + 3;
	if (nx < 0 || nx > 6 || ny < 0 || ny > 6 || visit[ny][nx] == 0)//visit外，或不可到达
		return 0;
	now = TO;
	path[top++] = now;
	while (!(now.x == FROM.x && now.y == FROM.y))//一步一步搜索
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
				if (visit[ny][nx] < min)//周围步数最小的是上一步，解决地形消耗不同问题
				{
					min = visit[ny][nx];
					minpos = next;
				}
			}
		}
		now = minpos;
		if (top > 4)
			show_error("路径计算栈溢出!", 1);
		path[top++] = now;
	}//路径计算
	show_msg("行军中", "");
	Clrmous();
	show_visit(FROM, visit, Map_partial);//还原标亮的格子
	map[oto.y][oto.x].stay = 0;//移动解除驻扎状态
	map[oto.y][oto.x].flag = 1;//标记已移动
	map[oto.y][oto.x].health = map[ofrom.y][ofrom.x].health;
	map[oto.y][oto.x].kind = map[ofrom.y][ofrom.x].kind;
	map[oto.y][oto.x].side = map[ofrom.y][ofrom.x].side;//移动
	map[ofrom.y][ofrom.x].kind = NOARMY;//清除这个就行了
	anime_path(map, path, top, map[oto.y][oto.x].kind, map[oto.y][oto.x].side);//显示移动路径
	return 1;
}
/*移动动画*/
void anime_path(MAP map, DBL_POS* path, int top, int kind, int side)
{
	DBL_POS lpos, pos;
	POS center;

	lpos = path[--top];//top指向栈顶下一个，此时取到出发点
	while (top > 0)//pop出路径
	{
		--top;
		pos = path[top];
		recover_cell(lpos, map);//还原此处地图
		center = center_xy(pos.x, pos.y);
		icon(center, side, kind);
		delay(200);
		lpos = pos;
	}
}

int attack_judge(MAP map, int able, DBL_POS dpos, DBL_POS dto)//成功返回1，失败0
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
	}//visit外，或不可到达
	return 1;
}

int victory_judge(MAP map)
{
	if (map[3][10].kind == 0)
	{
		delay(1000);
		if (v_cartoon("再战", "退出", "红军胜利了！", "您的勇气和智慧令人惊叹", 0))
			return 1;
		else
			exit(0);
	}
	if (map[9][1].kind == 0)
	{
		delay(msg_sec);
		if (v_cartoon("再战", "退出", "蓝军胜利了！", "您的勇气和智慧令人惊叹！", 1))
			return 1;
		else
			exit(0);
	}
	return 0;
}

int v_cartoon(char* btn1, char* btn2, char* s1, char* s2, int side)
{
	int color = side ? 34429 : 60361;
	Bar64k_radial(262, 218, 262 + 500, 219 + 230, color, 2000);
	rect_button(318, 384, 112 + 318, 45 + 384, btn1, 65535);
	rect_button(581, 384, 112 + 581, 45 + 384, btn2, 65535);	
	Outtextxx(512-100, 252, 512+100, s1, 32, 0);
	Outtext(304, 314, s2, 32, 35, 0);
	while (1)
	{
		Newxy();
		if (rec_btn_fun(318, 384, 112 + 318, 45 + 384, 65535))
		{
			return 1;
		}//点击确定返回1
		if (rec_btn_fun(581, 384, 112 + 581, 45 + 384, 65535))
		{
			return 0;
		}//点击取消返回0
	}
}