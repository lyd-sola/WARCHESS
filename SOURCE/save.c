/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: save.c
author: ���Ƶ�
version: 0
Description:��ս��Ϣ�ļ�����
date:

������־																	����������Ҫ�����ļ����ң�Ŀǰ�ݲ�����
																			
																			***ע��*** �˺�����Ӵ浵ֻ�ܰ�˳����ӣ��������û���ѡ����һ�����

����Ŀ¼
1.�����û��浵�ļ�
2.
******************************************************************/
#define MAP_SIZE 13
#define MAX_SAVE_NUM 6
#include "common.h"

/**************************************************************************************************
save�ļ���ƣ�											λ�����Կ�ͷƫ�������ֽڣ�
	�ļ�����username
	1���ļ��д浵������short*1								��1
	
	�����ظ�����浵�����ƣ�ע��short��Ϊunsigned��
	------------------------------------
	�浵���short*1											0
	���� ��unsigned*1������unsigned*1��ʱ��unsigned*1		1
	�غ��� unsigned*1										7
	�������췽 ��Դ unsigned*2								9
	
	����13��*13��unsigned��С��λ�ֶ�CELL��Ϊ��ͼ			13
	λ�ֶνṹ��Ƽ�struct.h
	------------------------------------				��ͼ��2*SIZE*SIZE
	Author�����Ƶ�
*************************************************************************************************/

/*******************************************
Function��savefile_creat
Author�����Ƶ�
Description: ���ٴ�����ͼ�ļ�
*******************************************/
int savefile_creat(char *user)//�������1��浵�������ٴ���ʧ��
{
	char filename[25] = "SAVES//";
	FILE *fp;
	short n;
	strcat(filename, user);
	if( (fp = fopen(filename, "rb+")) == NULL)
	{
		show_error("δ�ҵ��û��浵�ļ�", 1);
	}
	fread(&n, 1, 1, fp);//��ȡ�浵����
	if(n >= MAX_SAVE_NUM)
	{
		return 1;
	}
	n++;
	fseek(fp, 0, SEEK_SET);
	fwrite(&n, 1, 1, fp);
	//���Ӵ浵����

	fseek(fp, 0, SEEK_END);//�ƶ����ļ�β����ʼ�浵����
	savefile_init(fp, n);//��ʼ��Ϣ��д
	fclose(fp);
	return 2;
}

/*******************************************
Function��savefile_init
Author�����Ƶ�
Description: ��ĳһ���浵���и���ʽ��ʼ��
*******************************************/

void savefile_init(FILE *fp, short n)//nΪ��ǰ�浵��
{
	unsigned i = 3, j = 0, t[3];
	time_t rawtime;
    struct tm *info;
	CELL cell;
	FILE *map;
	char geo;
	//�浵��
	fwrite(&n, 1, 1, fp);
	//��ǰʱ������
	time( &rawtime );
    info = localtime( &rawtime );
	t[0] = info->tm_year + 1900;//��
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//����
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//ʱ��
	fwrite(t, 2, 3, fp);
	//��ʼ�����ݴ���
	i = 1;
	fwrite(&i, 2, 1, fp);//�غ���
	i = 3;
	fwrite(&i, 2, 1, fp);
	fwrite(&i, 2, 1, fp);//˫����Դ��
	
	
	//��ͼ��ʼ��
	if ((map = fopen("DATA//map.txt", "r")) == NULL)
	{
		show_error("δ�ҵ���ͼ��Ϣ�ļ�", 1);
	}
	cell.kind = NOARMY;
	cell.health = 0;
	cell.side = 0;
	for(i = 0; i < MAP_SIZE; i ++)
	{
		fseek(map, 2, SEEK_CUR);
		for(j = 0; j < MAP_SIZE; j ++)//OBSTACLE, PLAIN, FOREST, DESERT, BASE, SORC, HSORC
		{
			fscanf(map, "%c", &geo);
			geo -= '0';
			switch (geo)
			{
			case OBSTACLE:
				cell.geo = OBSTACLE;
				cell.cost = 7;
				break;
			case PLAIN:
				cell.geo = PLAIN;
				cell.cost = 1;
				break;
			case FOREST:
				cell.geo = FOREST;
				cell.cost = 2;
				break;
			case DESERT:
				cell.geo = DESERT;
				cell.cost = 2;
				break;
			case BASE:
				cell.geo = BASE;
				cell.cost = 7;
				break;
			case SORC:
				cell.geo = SORC;
				cell.cost = 2;
				break;
			case HSORC:
				cell.geo = HSORC;
				cell.cost = 2;
				break;
			case OUT_MAP:
				cell.geo = OUT_MAP;
				cell.cost = 7;
				break;
			}
			fwrite(&cell, 2, 1, fp);
		}
		fseek(map, 2, SEEK_CUR);
	}
	fclose(map);
}
/*******************************************
Function��seek_savinfo
Author�����Ƶ�
Description: �ڶ�ս��Ϣ�ļ��ж�λ
	��fp��λָ������xy����Ϣ��ע����������Ϊ˫�����
	��x*y == 0����fp��λ����n���浵��
*******************************************/

void seek_savinfo(FILE* fp, short n, int x, int y)//fp ָ���û���ս��Ϣ�ļ���ָ��
{
	fseek(fp, 1, SEEK_SET);//������ʼ����
	fseek(fp, (13 + 2 * MAP_SIZE * MAP_SIZE) * (n - 1), 1);//����n-1���浵
	if (x * y == 0)
	{
		return;
	}
	fseek(fp, 13, SEEK_CUR);//�������浵ͷ��
	/* �洢������˫���������Ĺ�ϵ��row=y,column=(int)(x+1)/2 */
	fseek(fp, 2 * MAP_SIZE * (y - 1), SEEK_CUR);//����y-1��
	fseek(fp, (x - 1) / 2 * 2, SEEK_CUR);//����(x - 1) / 2��
}
/*******************���²��Ժ������ǵ�ɾ��********************/















