/****************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: main.c
author: 刘云笛、陈旭桐
version: 2.0 
Description: 主函数
****************************************************/ 
#include"common.h"

int main(void)
{
	int page = HOMEPAGE;
	char user[10] = "";				//初始化用户名数组，系统限制，用户名仅为大写字母和数字，8位以内
	
	SetSVGA64k(); 					//分辨率1024*768
	//Initmouse(1, 1023, 1, 767); 
	Initmouse(0, 1024, 0, 768); 

	while(1)
	{
		switch(page)
		{
			case EXIT:				//exit
				exit(0);
				break;
				
			case HOMEPAGE:			//首页
				page = homepage();
				break;
				
			case LOGIN:				//登录界面
				page = login(user);
				break;
			
			case REGIS:				//注册界面
				page = register_();
				break;
				
			case MAINMENU:			//主菜单
				page = mainmenu(user);
				break;

			case BATTLE:			//对战界面
				page = battle(user, 1);									/*这里需要传入存档号*/
				break;
				
			case 233:
				page = test();
				break;
		}																	/*******这里缺一个default************/
	}
}