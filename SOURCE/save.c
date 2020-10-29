/********************************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: save.c
author: ���Ƶ�	
version: 3.0
Description:��ս��Ϣ�ļ�����
		***ע��*** �˺�����Ӵ浵ֻ�ܰ�˳����ӣ��������û���ѡ����һ�����
date:

������־																	����������Ҫ�����ļ����ң�Ŀǰ�ݲ�����
version 1.0 ��ʹ���ı��ļ����ÿ��������ļ��ϴ󣬶�д����
version 2.0 ����ͻ�ƣ�ʹ�ö������ļ�����ͼ��Ԫ��ʹ��λ�ֶνṹ
version 3.2 ��2020/10/18 ����CELL��������Ϊ�������ӹ���Ԥ���ռ�
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
	ģʽchar*1��0Ϊ˫�ˣ�1Ϊ����							0
	���� ��unsigned*1������unsigned*1��ʱ��unsigned*1		1
	�غ��� unsigned*1										7
	�������췽 ��Դ unsigned*2								9
	
	����13��*13��unsigned��С��λ�ֶ�CELL��Ϊ��ͼ			13
	λ�ֶνṹ��Ƽ�struct.h
	------------------------------------				��ͼ��3*SIZE*SIZE
	Author�����Ƶ�
*************************************************************************************************/

/*******************************************
Function��savefile_creat
Author�����Ƶ�
Description: ���ٴ�����ͼ�ļ�
*******************************************/
int savefile_creat(FILE *fp, short mode)//�������1��浵�������ٴ���ʧ�ܣ��ɹ���������0
{
	short n;

	n = get_savenum(fp);//��ȡ�浵����
	if(n >= MAX_SAVE_NUM)
	{
		return 1;
	}
	n++;
	fseek(fp, 0, SEEK_SET);
	fputc(n + '0', fp);
	//fprintf(fp, "%1d", n);
	//fwrite(&n, 1, 1, fp);
	//���Ӵ浵����

	fseek(fp, 0, SEEK_END);//�ƶ����ļ�β����ʼ�浵����
	savefile_init(fp, mode);//��ʼ��Ϣ��д
	return 0;
}

/*******************************************
Function��savefile_init
Author�����Ƶ�
Description: ��ĳһ���浵���и���ʽ��ʼ��
*******************************************/

void savefile_init(FILE* fp, short mode)
{
	unsigned int i = 3, j = 0, t[3];
	time_t rawtime;
	struct tm* info;
	CELL cell;
	FILE* map;
	char geo;
	//��սģʽ
	//fwrite(&m, 1, 1, fp);
	fprintf(fp, "%1d", mode);
	//��ǰʱ������
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//��
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//����
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//ʱ��
	fwrite(t, 2, 3, fp);
	//��ʼ�����ݴ���
	i = 1;
	fwrite(&i, 2, 1, fp);//�غ���
	i = 2;
#ifdef INF_SOURCE
	i = 666;
#endif // ������Դģʽ����
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
	cell.faci = 0;
	cell.stay = 0;
	cell.flag = 0;
	cell.src_rnd = 0;
	for (i = 0; i < MAP_SIZE; i++)
	{
		fseek(map, 2, SEEK_CUR);
		for (j = 0; j < MAP_SIZE; j++)//OBSTACLE, PLAIN, FOREST, DESERT, BASE, SORC, HSORC
		{
			fscanf(map, "%c", &geo);
			geo -= '0';
			if (geo == BASE)
			{
				cell.geo = BASE;
				cell.kind = 1;//��Ӫ��ʼ��
				cell.health = 30;
				if (i == 3)//����
					cell.side = 1;
				fwrite(&cell, sizeof(CELL), 1, fp);
				cell.kind = NOARMY;
				cell.health = 0;
				cell.side = 0;
			}
			else
			{
				cell.geo = geo;
				fwrite(&cell, sizeof(CELL), 1, fp);
			}
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
	int size = sizeof(CELL);
	fseek(fp, 1, SEEK_SET);//������ʼ����
	fseek(fp, (13 + size * MAP_SIZE * MAP_SIZE) * (n - 1), 1);//����n-1���浵
	if (x * y == 0)
	{
		return;
	}
	fseek(fp, 13, SEEK_CUR);//�������浵ͷ��
	/* �洢������˫���������Ĺ�ϵ��row=y,column=(int)(x+1)/2 */
	fseek(fp, size * MAP_SIZE * (y - 1), SEEK_CUR);//����y-1��
	fseek(fp, (x - 1) / size * size, SEEK_CUR);//����(x - 1) / 2��
}

short get_savenum(FILE* fp)
{
	short tot;
	fseek(fp, 0, SEEK_SET);
	tot = fgetc(fp) - '0';
	return tot;
}

short get_savmode(FILE* fp, short savnum)
{
	short mode;
	seek_savinfo(fp, savnum, 0, 0);
	mode = fgetc(fp);
	return mode - '0';
}

/**********************************************************
Function��		Battle_init
Description��	ս����ʼ����������ȡ�浵
Input:			fp�û��浵�ļ�ָ�룬������һ���Ͷ�
Author��		���Ƶ�
**********************************************************/
void Battle_init(FILE* fp, Battleinfo* info, MAP map)
{
	int i;
	int size = sizeof(CELL);

	fseek(fp, 7, SEEK_CUR);//��������
	fread(&(info->round), 2, 1, fp);
	fread(&(info->b_source), 2, 1, fp);
	fread(&(info->r_source), 2, 1, fp);
	for (i = 0; i < 13; i++)
	{
		fread(map[i], size, 13, fp);
		if (feof(fp) && i != 12)
		{
			show_error("��ͼ�ļ�����", 1);
		}
	}//��ȡ��ͼ��Ϣ
}
/**********************************************************
Function��		save_battle
Description��	����浵
Input:			fp�û��浵�ļ�ָ�룬��Ҫָ����ȷ�浵��������һ���Ͷ�
Author��		���Ƶ�
**********************************************************/

void save_battle(FILE* fp, Battleinfo batinfo, MAP map)
{
	unsigned t[3];
	time_t rawtime;
	struct tm* info;
	int i;
	int size = sizeof(CELL);

	fseek(fp, 1, SEEK_CUR);//����ģʽ��
	//��ǰʱ������
	time(&rawtime);
	info = localtime(&rawtime);
	t[0] = info->tm_year + 1900;//��
	t[1] = (info->tm_mon + 1) * 100 + (info->tm_mday);//����
	t[2] = (info->tm_hour) * 100 + (info->tm_min);//ʱ��
	fwrite(t, 2, 3, fp);
	//�غ���Ϣ����
	fwrite(&(batinfo.round), 2, 1, fp);
	fwrite(&(batinfo.b_source), 2, 1, fp);
	fwrite(&(batinfo.r_source), 2, 1, fp);
	//�����ͼ��Ϣ
	for (i = 0; i < 13; i++)
	{
		fwrite(map[i], size, 13, fp);
	}
}

void load_battle(char* user, int save_num, Battleinfo* batinfo, MAP map, FILE **fp)
{
	char filename[25] = "SAVES//";
	strcat(filename, user);
	if ((*fp = fopen(filename, "rb+")) == NULL)
		show_error("δ�ҵ��û��浵�ļ�", 1);
	seek_savinfo(*fp, save_num, 0, 0);
	Battle_init(*fp, batinfo, map);
}