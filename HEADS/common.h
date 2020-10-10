/****************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: common.h
author: ���Ƶѡ�����ͩ
version: 1
Description: ͷ�ļ�������ṹ��ö��
****************************************************/ 
#ifndef	_COMMON_H_
#define	_COMMON_H_

#define SCR_WIDTH 1024
#define SCR_HEIGHT 768

#include <stdio.h>     /**�ļ���������ͷ�ļ�**/
#include <conio.h>     /**getch()����ͷ�ļ�**/
#include <stdlib.h>	   /**rand()��exit()�Ⱥ���ͷ�ļ�**/
#include <malloc.h>    /**��̬�����ڴ�ͷ�ļ�**/
//#include <graphics.h>  /**�Դ�ͼ����ͷ�ļ�**/
#include <string.h>    /**�ַ���������ͷ�ļ�**/
#include <bios.h> 	   /**bioskey()����ͷ�ļ�**/
#include <dos.h>       /**int86()�ȹ����жϵ�ͷ�ļ�**/
#include <time.h>	   /**time()������ͷ�ļ�**/
#include <math.h>      /**��ѧ������ͷ�ļ�**/
#include <ctype.h>     /**�ַ�������ͷ�ļ�**/
#include <process.h>

#include "outtext.h"	//���ֿ�
#include "SVGAmode.h"	//SVGA
#include "mouse.h"		//���

#include "draw.h"		//�Զ��廭ͼ����
#include "struct.h"		//���ֽṹ�嶨��
#include "kbinput.h"	//����������ʾ
#include "homepage.h"	//��ҳ
#include "login.h"		//��¼����
#include "register.h"	//ע�����
#include "mainmenu.h"	//���˵�����
#include "save.h"		//��ս��Ϣ�浵��ȡ
#include "func.h"		//���ֺ���
#include "map.h"		//��ͼ��غ���
#include "battle.h"		//��ս������
#include "act.h"		//��ս��Ϊ����
#include "savpage.h"	//�浵����
#include "buttons.h"	//��ť����
enum MENU
{
	EXIT, HOMEPAGE, LOGIN, REGIS, MAINMENU, ABOUT, BATTLE
};//�����湦��ѡ��
/********************����ҳ�溯��********************/
int test(void);
void test_draw(void);
void tank_draw(int x, int y);
#endif