#ifndef  _TYPE_H_
#define _TYPE_H_

typedef struct _Position
{
	short x;
	short y;
}DBL_POS, OFF_POS, POS;//double width , offset, POSΪ��������

typedef struct _cell
{
	unsigned geo : 3;//���Σ���ż�_GEO
	unsigned stay : 1;//�Ƿ�פ����1Ϊפ��
	unsigned faci : 2;//��ʩ��0Ϊ����ʩ
	unsigned side : 1;//��Ӫ����0��1
	unsigned flag : 1;//����Ƿ������
	unsigned kind : 3;//�������࣬��ż�_KIND����Ӫ����Դ�������
	unsigned health : 5;//���֡���ӪѪ�����߼���Դռ��غ���
	unsigned no_use : 8;//Ԥ���ռ䣬�������ӹ��ܵĿռ�
}CELL, MAP[13][13];

typedef struct _Battleinfo
{
	unsigned round;//�غ������˴�Ϊ˫��
	unsigned r_source;//�췽��Դ
	unsigned b_source;//������Դ
}Battleinfo;

typedef struct _Arminfo
{
	unsigned health;//����ֵ
	unsigned attack;//������
	unsigned move;//�ƶ���
	unsigned cost;//���
	unsigned distance;//���
}Arminfo;

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