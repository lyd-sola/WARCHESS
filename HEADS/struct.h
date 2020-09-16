#ifndef  _TYPE_H_
#define _TYPE_H_

typedef struct _Position
{
	short x;
	short y;
}POS;

typedef struct _cell
{
	unsigned geo : 4;//���Σ���ż�_GEO
	unsigned cost : 3;//�ƶ�����
	unsigned side : 1;//��Ӫ����0��1
	unsigned kind : 3;//�������࣬��ż�_KIND����Ӫ����Դ�������
	unsigned health : 5;//���֡���ӪѪ�����߼���Դռ��غ���
}CELL;

typedef struct _Battleinfo
{
	unsigned round;
	unsigned r_source;
	unsigned b_source;
}Battleinfo;

enum _GEO
{
	OBSTACLE, PLAIN, FOREST, DESERT, BASE, SORC, HSORC, OUT_MAP
};//����������

enum _KIND
{
	NOARMY, BUILDER, INFANTRY/*����*/,
	ARTILLERY/*�ڱ�*/,
	TANK, SUPER
};//����������

#endif