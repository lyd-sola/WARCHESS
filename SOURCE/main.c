/****************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name: main.c
author: ���Ƶѡ�����ͩ
version: 2.0 
Description: ������
****************************************************/ 
#include"common.h"

int main(void)
{
	int page = HOMEPAGE;
	char user[10] = "";				//��ʼ���û������飬ϵͳ���ƣ��û�����Ϊ��д��ĸ�����֣�8λ����
	
	SetSVGA64k(); 					//�ֱ���1024*768
	//Initmouse(1, 1023, 1, 767); 
	Initmouse(0, 1024, 0, 768); 

	while(1)
	{
		switch(page)
		{
			case EXIT:				//exit
				exit(0);
				break;
				
			case HOMEPAGE:			//��ҳ
				page = homepage();
				break;
				
			case LOGIN:				//��¼����
				page = login(user);
				break;
			
			case REGIS:				//ע�����
				page = register_();
				break;
				
			case MAINMENU:			//���˵�
				page = mainmenu(user);
				break;

			case BATTLE:			//��ս����
				page = battle(user, 1);									/*������Ҫ����浵��*/
				break;
				
			case 233:
				page = test();
				break;
		}																	/*******����ȱһ��default************/
	}
}