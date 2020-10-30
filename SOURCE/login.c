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
2020/10/30
	增加忘记密码和密保问题
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

		if (forget_fun())                                              //修改密码
		{
			if (*tmp) //已经输入用户名
			{
				forget_password(tmp);
			}
			else  //未输入用户名
			{
				rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 65535);
				Outtext(512 - 200 + 30, 384 - 24, "请输入用户名", 48, 55, 2463);
				delay(1000);
			}
			return LOGIN;
		}

		if(mouse_press(686 - 15, 490 - 15, 814 + 15, 522 + 15) == MOUSE_IN_L)				//点击登录键
		{
			if (*tmp == '\0')//未输入用户名
			{
				Outtext(620, 340, "请输入用户名", 16, 30, 63488);
			}
			else if (*password == '\0')//未输入密码
			{
				Outtext(620, 440, "请输入密码", 16, 30, 63488);
			}

			else if(login_check(tmp, password) == 1)						//判断是否与文件匹配
			{
				login_anime();
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

		if (quick_regi())                                              //新用户
		{
			return REGIS;
		}
	}
}

void drawlogin()
{
	Putbmp64k(0, 0, "BMP//lng.bmp");

	Bar64k(0, 0, 50, 50, 65535); //退出
	Outtext(9, 9, "返", 32, 0, 0);
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
	Outtextxx(846, 435, 610+370, "忘记密码", 24, 0);
	Outtext(846, 335, "新用户？", 24, 38, 0);
}

void login_anime(void)
{
	rect_circle(512 - 250, 384 - 100, 512 + 250, 384 + 100, 65535);
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "正", 48, 102, 2463);					//虚假的动画效果
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "正在", 48, 102, 2463);
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "正在登", 48, 102, 2463);
	delay(500);
	Outtext(512 - 200 + 30, 384 - 24, "正在登录", 48, 102, 2463);
	delay(500);
	rect_circle(512 - 250, 384 - 100, 512 + 250, 384 + 100, 65535);
	Outtextxx(512 - 200 + 30+5, 384 - 24, 512 - 200 + 30 + 340, "登录成功！", 48, 2463);
	delay(1000);
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
		rect_circle(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "未找到该用户", 32, 65535);
		fclose(fp);
		return 0;
	}

	//密码判断
	fscanf(fp, "%llu", &pw);
	fgetc(fp);
	fscanf(fp, "%llu", &pwt);
	if(pw == password_classified(password, 67) && pwt == password_classified(password, 71) )
	{
		fclose(fp);
		return 1;
	}
	else
	{
		*password = 0;
		rect_circle(512-200, 384-100, 512+200, 384+100, 5);
		Outtextxx(512-200+30, 384-100+40, 512-200+340, "密码错误", 32, 65535);
		fclose(fp);
		return 0;
	}
}

int quick_regi(void)//跳转注册按钮功能函数
{
	if (Mouse_above(846, 335, 978, 335 + 24))
	{
		Clrmous();
		MouseS = 1;
		Bar64k(846, 335 + 26, 978, 335 + 27, 0);
		while (1)
		{
			Newxy();
			if (Mouse_above(846, 335, 978, 335 + 24))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					return 1;
					//若点击返回1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				putbmp_partial(846, 335 + 26, 978, 335 + 27, "BMP//lng.bmp");
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

int forget_fun(void)//忘记密码按钮功能函数
{
	if (Mouse_above(846, 435, 978, 435+24))
	{
		Clrmous();
		MouseS = 1;
		Bar64k(846, 435+26, 978, 435+27, 0);
		while (1)
		{
			Newxy();
			if (Mouse_above(846, 435, 978, 435+24))
			{
				if (press == 1)
				{
					Clrmous();
					MouseS = 0;
					return 1;
					//若点击返回1
				}
			}
			else
			{
				Clrmous();
				MouseS = 0;
				putbmp_partial(846, 435+26, 978, 435+27, "BMP//lng.bmp");
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}

void forget_draw(int q)
{
	putbmp_partial(312, 120, 610 + 370, 522 + 15+10, "BMP//lng.bmp");
	//frame(610, 165, 610 + 370, 165 + 50, 65535);   //问题
	Outtext(610 - 168, 175, "问题", 32, 118, 63488);
	switch (q)
	{
	case 1:
		Outtext(610+10, 165+13, "您的生日是？", 24, 28, 0);
		break;
	case 2:
		Outtext(610+10, 165+13, "您身份证号六到十位是？", 24, 28, 0);
		break;
	case 3:
		Outtext(610+10, 165+13, "您宠物的名字是？", 24, 28, 0);
		break;
	case 4:
		Outtext(610+10, 165+13, "您第一位恋人的名字是？", 24, 28, 0);
		break;
	}

	frame(610, 165 + 100, 610 + 370, 165 + 50 + 100, 65535);  //答案
	Outtext(610 - 168, 175 + 100, "答案", 32, 118, 63488);
	Outtext(610 + 20, 185 + 100, "输入您密保问题的答案", 16, 30, 27469);
	
	frame(610, 165 + 200, 610 + 370, 165 + 50 + 200, 65535);  //新密码
	Outtext(610 - 168, 175 + 200, "新密码", 32, 59, 63488);
	Outtext(610 + 20, 185 + 200, "输入您的新密码", 16, 30, 27469);

	shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
	Outtext(686, 480, "完成", 48, 80, 63488);
}

void forget_password(char* username)
{
	FILE* fp;
	int q=0, check = 0;
	unsigned long long answert;
	char buffer[40], answer[40] = "\0", password[40] = "\0";
	char filename[30] = "users\\";
	strcat(filename, username);

	if ((fp = fopen(filename, "r")) == NULL)
	{
		rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 5);
		Outtextxx(512 - 200 + 30, 384 - 100 + 40, 512 - 200 + 340, "未找到该用户", 32, 65535);
		fclose(fp);
		return;
	}
	fgets(buffer, 40, fp);
	fscanf(fp, "%d%llu", &q, &answert);
	fclose(fp);
	forget_draw(q);
	while (1)
	{
		Newxy();
		if (mouse_press(610, 165 + 100, 610 + 370, 165 + 50 + 100) == MOUSE_IN_L)					//输入答案
		{
			kbinput(610, 165 + 100, 610 + 370, 165 + 50 + 100, answer, 0);
		}
		if (mouse_press(610, 165 + 200, 610 + 370, 165 + 50 + 200) == MOUSE_IN_L)					//输入密码
		{
			kbinput(610, 165 + 200, 610 + 370, 165 + 50 + 200, password, 0);
		}
		if (mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_IN_L)
		{
			if ((check = reset_check(answer, password, answert)) == 1)
			{
				password_reset(username, password);
				rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
				Outtextxx(512 - 170 + 10, 384 - 20, 512 - 170 + 340, "修改成功！", 48, 65535);
				delay(500);
				return;
			}
			else if(check == 2)
			{
				forget_draw(q);
			}
		}
		if (mouse_press(0, 0, 50, 50) == 1)
		{
			return;
		}
	}
}

int reset_check(char* answer, char* password, unsigned long long answert)
{
	if (*answer == '\0')//未输入用户名
	{
		Outtext(620, 320, "请输入答案", 16, 30, 63488);
	}
	else if (*password == '\0')//未输入密码
	{
		putbmp_partial(620, 420, 620 + 30 * 7 + 16, 420 + 16, "BMP\\lng.bmp");
		Outtext(620, 420, "请输入新密码", 16, 30, 63488);
	}
	else if(strlen(password) < 4)
	{
		putbmp_partial(620, 420, 620 + 30 * 7 + 16, 420 + 16, "BMP\\lng.bmp");
		Outtext(620, 420, "密码长度须大于三", 16, 30, 63488);
	}
	else if (password_classified(answer, 71) != answert)
	{
		rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170+10, 384-20, 512 - 170 + 340, "答案错误！", 48, 65535);
		*answer = 0;
		delay(1000);
		return 2;
	}
	else
	{
		return 1;
	}
	return 0;
}

int password_reset(char* username, char* password)
{
	FILE* fp;
	unsigned long long pw, pwt;
	char filename[30] = "users\\";
	char buffer[40];
	strcat(filename, username);

	if ((fp = fopen(filename, "r+")) == NULL)
	{
		show_error("打开文件发生错误", 1);
	}
	fprintf(fp, "%llu#%llu#", password_classified(password, 67), password_classified(password, 71));
	return 1;
}