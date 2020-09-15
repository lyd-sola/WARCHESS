#ifndef  _TYPE_H_
#define _TYPE_H_

typedef struct _Position
{
	short x;
	short y;
}POS;

typedef struct _cell
{
	unsigned geo : 4;//地形，序号见_GEO
	unsigned cost : 3;//移动消耗
	unsigned side : 1;//阵营，蓝0红1
	unsigned kind : 3;//兵种种类，序号见_KIND，大本营和资源无需此项
	unsigned health : 5;//兵种、大本营血量，高级资源占领回合数
}CELL;

enum _GEO
{
	OBSTACLE, PLAIN, FOREST, DESERT, BASE, SORC, HSORC
};//地形种类编号

enum _KIND
{
	NOARMY, BUILDER, INFANTRY/*步兵*/,
	ARTILLERY/*炮兵*/,
	TANK, SUPER
};//兵种种类标号

#endif