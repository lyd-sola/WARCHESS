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
	char user[16] = "A";				//��ʼ���û������飬ϵͳ���ƣ��û�����Ϊ��д��ĸ�����֣�8λ����
	FILE* fp;
	short save_num = 1;
	short mode = 0;//��սģʽ
	SetSVGA64k(); 					//�ֱ���1024*768
	//Initmouse(1, 1023, 1, 767); 
	Initmouse(0, 1024, 0, 768); 
	FBMP = fopen("BMP//map.bmp", "rb");

	while(1)
	{
		switch(page)
		{
			case EXIT:				//exit
				fclose(FBMP);
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
				
			case GUEST:
				strcpy(user, "GUEST");
			case MAINMENU:			//���˵�
				page = mainmenu(user, &save_num, &mode);
				break;

			case BATTLE:			//��ս����
				page = battle(user, save_num, mode);
				break;
				
			case 233:
				page = test();
				break;
		}
	}
}