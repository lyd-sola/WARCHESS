/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: loginmenu.c
author: 陈旭桐、刘云笛
version: 2.0
Description: 登录界面
date:2020/9/8

更新日志
2020/9/9
	优化了登录界面
	增加了判断是否正确输入的函数
	增加了用户名与文件匹配的功能
2020/10/25
	解决了免密登录的bug

函数目录
1.login：		登录函数
2.drawlogin：	绘制登录界面函数
3.login_check：	检测输入信息函数
******************************************************************/
#include "common.h" 

int login(char *username)  
{
	char password[20] = "\0";	//初始化密码数组
	char tmp[15];
	int flag = 0;				//防止重复高亮
	Clrmous();
	drawlogin();
	
	while(1)
	{
		Newxy();
		
		if(bioskey(1))
		{
			getch();
		}//防止缓冲区中有内容影响输入
		
		if(mouse_press(0, 0, 80, 80) == MOUSE_IN_L)
		{
			return 1;
		}
		
		if(flag == 0 && mouse_press(686-15, 490-15, 814+15, 522+15) == MOUSE_IN)	//高亮登录键
		{
			flag = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			frame(686-15, 490-15, 814+15, 522+15, 65535);
			Outtext(686, 480, "登录", 48, 80, 63488);
			Mouse_savebk2();//更新鼠标状态，防止留痕
		}
		
		if(flag == 1 && mouse_press(686-15, 490-15, 814+15, 522+15) == MOUSE_OUT)	//取消高亮	
		{
			flag = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(686-15, 490-15, 814+15, 522+15, 65535);
			Outtext(686, 480,"登录", 48, 80, 63488);
		}	
		
		if(mouse_press(610, 280, 610 + 370, 280 + 50) == MOUSE_IN_L)						//输入用户名
		{
			kbinput(610, 280, 610 + 370, 280 + 50, tmp, 1);
		}
		
		if(mouse_press(610, 280 + 100, 610 + 370, 280 + 50 + 100) == MOUSE_IN_L)				//输入密码
		{
			kbinput(610, 280 + 100, 610 + 370, 280 + 50 + 100, password, 0);
		}
		
		if(mouse_press(686 - 15, 490 - 15, 814 + 15, 522 + 15) == MOUSE_IN_L)				//点击登录键
		{
			if (*tmp == '\0')//未输入用户名
			{
				Outtext(620, 340, "请输入用户名", 16, 30, 63488);
			}
			else if (*tmp == '\0')//未输入密码
			{
				Outtext(620, 440, "请输入密码", 16, 30, 63488);
			}

			else if(login_check(tmp, password) == 1)						//判断是否与文件匹配
			{
				Bar64k_radial(512-250, 384-100, 512+250, 384+100, 65535, 0);
				delay(500);
				Outtext(512-200+30, 384-24,"正", 48, 102, 2463);					//虚假的动画效果
				delay(500);
				Outtext(512 - 200 + 30, 384-24,"正在", 48, 102, 2463);
				delay(500);
				Outtext(512 - 200 + 30, 384-24,"正在登", 48, 102, 2463);
				delay(500);
				Outtext(512 - 200 + 30, 384-24,"正在登录", 48, 102, 2463);
				delay(500);
				Bar64k_radial(512-200, 384-100, 512+200, 384+100, 33333, 0);
				Outtextxx(512-200+30, 384-24, 512-200+30+340, "登录成功！", 48, 2463);
				delay(1000);
				strcpy(username, tmp);
				return MAINMENU;
			}
			else
			{
				Outtext(312 + 92, 484 - 60, "正在返回登录界面", 16, 25, 65535);
				delay(1000);
				return LOGIN;
			}
		}
	}
}

void drawlogin()
{
	//Bar64k(0, 0, 1024, 768, 25290);
	Putbmp64k(0, 0, "BMP//lng.bmp");

	Bar64k(0, 0, 50, 50, 65535); //退出

	Outtext(60, 70, "欢迎使用", 48, 70, 33808);
	Outtext(60, 210, "战棋系统", 48, 70, 33808);

	shadow_l(535, 120, 960, 232, 65535);
	Outtext(550, 130, "WARCHESS", 48, 48, 65535);
    Outtext(550 + 2, 130 + 2, "WARCHESS", 48, 48, 65184);
	Outtext(550, 190, "通行证验证", 32, 70, 0);

	frame(610, 280,610+370, 280+50, 65535);             //用户名
	Outtext(500, 290,"用户名", 32, 30, 63488);
	Outtext(610+20,280+15,"大写字母和数字", 16, 30, 0);
	
	frame(610, 280+100, 610+370, 280+50+100, 65535);  	//密码
	Outtext(500, 390,"密码", 32, 62, 63488);
	Outtext(610+20,380+15,"注意区分大小写", 16, 30, 0);
	
	shadow_l(686-15, 490-15, 814+15, 522+15, 65535);
	Outtext(686, 480,"登录", 48, 80, 63488);
}

int login_check(char *username, char *password)
{
	FILE *fp;
	unsigned long long pw, pwt;
	char filename[30] = "users\\";
	
	strcat(filename, username);
	
	//用户名判断
	if((fp = fopen(filename, "r")) == NULL)
	{
		shadow_l(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "未找到该用户", 32, 65535);
		fclose(fp);
		return 0;
	}
	
	//密码判断
	fscanf(fp, "%llu%llu", &pw, &pwt);
	if(pw == password_classified(password, 67) && pwt == password_classified(password, 71) )
	{
		fclose(fp);
		return 1;
	}
	else
	{
		*password = 0;
		shadow_l(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "密码错误", 32, 65535);
		fclose(fp);
		return 0;
	}
}