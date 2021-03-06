#ifndef  _TYPE_H_
#define _TYPE_H_

typedef struct _Position
{
	int x;
	int y;
}DBL_POS, OFF_POS, POS;//double width , offset, POS为世界坐标

typedef struct _cell
{
	unsigned geo : 3;//地形，序号见_GEO
	unsigned stay : 1;//是否驻扎，1为驻扎
	unsigned faci : 2;//设施，0为无设施
	unsigned side : 1;//阵营，蓝0红1
	unsigned flag : 1;//标记兵种是否操作过，以及资源点是否已经被采爆
	unsigned kind : 3;//兵种种类，序号见_KIND，大本营等级，资源无需此项
	unsigned health : 5;//兵种、大本营血量
	unsigned src_rnd : 5;//资源占领回合数
	unsigned no_use : 3;//预留空间，保留增加功能的空间
}CELL, MAP[13][13];

typedef struct _Battleinfo
{
	unsigned round;//回合数，此处为双倍
	unsigned r_source;//红方资源
	unsigned b_source;//蓝方资源
}Battleinfo;

typedef struct _Arminfo
{
	unsigned health;//生命值
	unsigned attack;//攻击力
	unsigned move;//移动力
	unsigned cost;//造价
	unsigned distance;//射程
}Arminfo;

enum _GEO
{
	OBSTACLE, PLAIN, FOREST, DESERT, BASE, SORC, HSORC, OUT_MAP
};//地形种类编号

enum _KIND
{
	NOARMY, BUILDER, INFANTRY/*步兵*/,
	ARTILLERY/*炮兵*/,
	TANK, SUPER
};//兵种种类标号

enum _FACI
{
	NOFACI, RCOLLECTION/*红方采集站*/, BCOLLECTION/*蓝方采集站*/, MEDICAL/*医疗站*/
};//设施种类编号 虽然只有两个
#endif