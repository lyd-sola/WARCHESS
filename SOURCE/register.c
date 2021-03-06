/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS
file_name: register.c
author: 陈旭桐、刘云笛
version: 1.2
Description: 注册界面
date:2020/9/8

更新日志
9.9		优化了注册界面
		增加了密码加密算法
		增加了将用户信息写入文件的函数
		增加了检测是否正确输入的函数
		解决了进入kbinput函数之前缓冲区有内容的bug
		
函数目录
1.register_:			注册函数
2.drawregi:				绘制注册界面函数
3.user_creat:			创建用户函数
4.password_classified:	密码文件加密函数
5.regis_check：			检测是否正确输入函数
******************************************************************/
#include "common.h"

int register_()
{
	char user[10] = "", password[20] = "", password_r[20] = "";
	int flag = 0;	//防止重复高亮
	int rcheck = 0;
	Clrmous();
	drawregi();
	
	while(1)
	{
		Newxy();
		if(bioskey(1))
		{
			getch();
		}//防止缓冲区中有内容影响输入
	
		if(mouse_press(0, 0, 50, 50) == MOUSE_IN_L)//返回主页面
		{
			return HOMEPAGE;
		}
		
		if(flag == 0 && mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_IN)	//高亮注册键
		{
			flag = 1;
			MouseS = 1;
			clrmous(MouseX, MouseY);
			frame(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5, 65535);
			Outtext(686, 480, "继续", 48, 80, 63488);
			Mouse_savebk2();//更新鼠标状态，防止留痕
		}
		if(flag == 1 && mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_OUT)	//取消高亮
		{
			flag = 0;
			MouseS = 0;
			clrmous(MouseX, MouseY);
			shadow_l(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5, 65535);
			Outtext(686, 480, "继续", 48, 80, 63488);
		}
		if(mouse_press(686 - 15, 480 - 5, 686 + 128 + 15, 480 + 48 + 5) == MOUSE_IN_L)	//点击继续键
		{
			if((rcheck = regis_check(user, password, password_r)) == 1)
			{
				//user_creat(user, password);
				if (secret_question(user, password) == 1)
					return LOGIN;
				else
					return HOMEPAGE;
			}
			else if(rcheck == 0)
			{
				Outtext(312+92, 484-60,"正在返回注册界面", 16, 25, 65535);
				delay(2000);
				return REGIS;
			}
		}
		
		if(mouse_press(610, 165, 610 + 370, 165 + 50) == MOUSE_IN_L)					//输入用户名
		{
			kbinput(610, 165, 610 + 370, 165 + 50, user, 1);
		}
		if(mouse_press(610, 165 + 100, 610 + 370, 165 + 50 + 100) == MOUSE_IN_L)					//输入密码
		{
			kbinput(610, 165 + 100, 610 + 370, 165 + 50 + 100, password, 0);
		}
		if(mouse_press(610, 165 + 200, 610 + 370, 165 + 50 + 200) == MOUSE_IN_L)					//再次输入密码
		{
			kbinput(610, 165 + 200, 610 + 370, 165 + 50 + 200, password_r, 0);
		}
	}
}

void drawregi()
{
	Putbmp64k(0, 0, "BMP//lng.bmp");
	Bar64k(0,0,50,50, 65535);
	Outtext(9, 9, "返", 32, 0, 0);
	Outtext(100, 70, "WARCHESS", 48, 48, 65535);
	Outtext(100 + 2, 70 + 2, "WARCHESS", 48, 48, 65184);
	Outtext(510, 70, "通行证注册", 48, 70, 0);

	shadow_l(686-15, 480-5, 686+128+15, 480+48+5, 65535);
	Outtext(686, 480,"继续", 48, 80, 63488);

	frame(610, 165, 610+370, 165+50, 65535);   //用户名 
	Outtext(610-168, 175,"用户名", 32, 59, 63488);
	Outtext(610+20, 185, "八位以内，大写字母和数字", 16, 22, 27469);
	
	frame(610, 165+100, 610+370, 165+50+100, 65535);  //密码
	Outtext(610-168, 175+100,"密码", 32, 118, 63488);
	Outtext(610+20, 185+100, "密码区分大小写哦", 16, 30, 27469);
	
	frame(610, 165+200, 610+370, 165+50+200, 65535);  //再次输入
	Outtext(610-168, 175+200, "再次输入", 32, 40, 63488);
	Outtext(610+20, 185+200, "两次输入保持一致", 16, 30, 27469);
}

/*******************************
新用户创建函数
Description:创建用户文件及对战保存文件
Author: 刘云笛
*******************************/
void user_creat(char *username, char *password, int q, char* answer)
{
	FILE *fp;
	char filename[30] = "USERS\\";
	int tot = 0;
	strcat(filename, username);
	
	//创建用户名及密码保存文件
	if((fp = fopen(filename, "w")) == NULL)
	{
		show_error("无法创建用户存档", 1);
	}
	fprintf(fp, "%llu#%llu#", password_classified(password, 67), password_classified(password, 71));//这里涉及加密问题，不会给你注释的
	fprintf(fp, "\n%d\n%llu", q, password_classified(answer, 71));//这里涉及加密问题，不会给你注释的
	fclose(fp);
	
	//创建对战信息文件，其实只有文件名和一个0
	sprintf(filename, "SAVES");//教你怎么优美地改路径
	filename[5] = '\\';
	if((fp = fopen(filename, "wb+")) == NULL)
	{
		show_error("无法创建用户战斗信息存档", 1);
	}
	fprintf(fp, "%1d", tot);
	//fwrite(&tot, 1, 1, fp);
	fclose(fp);
}

//陈旭桐初版，刘云笛修改，加密密码
unsigned long long password_classified(char *p, int radix)//哈希算法，字符数组转换为radix进制数 
{
	unsigned long long part1 = 0, part2 = 0;
	int length = strlen(p), i, tmp;
	//此处应有注释
	for(i = 0; i < length; i++)
	{   
        part1 *= radix;
		part2 *= radix;//自然溢出不管 
		if(isupper(p[i]) == 1)//大写 
		{
			tmp = p[i] - 'A' + 11;
			part1 += tmp;
		}
		else if(islower(p[i]) == 1)//小写 
		{
			tmp = p[i] - 'a' + 37;
			part1 += tmp;
		}
		else if(p[i] == '0')
		{
			tmp = 10;
			part1 += tmp;
		}
		else//数字1-9 
		{
			tmp = p[i] - '0';
			part1 += tmp;
		}
		
		//倒序
		if(isupper(p[length-1-i]) == 1)
		{
			tmp = p[length-1-i] - 'A' + 11;
			part2 += tmp;
		}
		else if(islower(p[length-1-i]) == 1)
		{
			tmp = p[length-1-i] - 'a' + 37;
			part2 += tmp;
		}
		else if(p[length-1-i] == '0')
		{
			tmp = 10;
			part2 += tmp;
		}
		else
		{
			tmp = p[length-1-i] - '0';
			part2 += tmp;
		}	
	}
	return part1 *(part2 * radix);
	/*
	在你看懂这个的时候，我们的加密系统就被你识破了QAQ
	可恶
	然而你也不一定能算出密码
	哈哈哈哈哈哈哈哈哈哈哈 XD
	*/
}

int regis_check(char *un, char *pw, char *pwr)
{
	FILE *fp;
	char filename[30] = "users\\";
	strcat(filename, un);
	
	if(*un == '\0')//未输入用户名
	{
		Outtext(620, 225, "请输入用户名", 16, 30, 63488);
	}
	else if(*pw == '\0')//未输入密码
	{
		Outtext(620, 225+100, "请输入密码", 16, 30, 63488);
	}
	else if(*pwr == '\0')//未再次输入密码
	{
		Outtext(620, 225+100+100, "请再次输入密码", 16, 30, 63488);
	}
	else if ((fp = fopen(filename, "rb")) != NULL)//用户名已存在
	{
		fclose(fp);
		rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170, 384 - 60, 512 - 170 + 340, "用户名已存在", 32, 65535);
		return 0;
	}
	else if(strcmp(pw, pwr))//两次输入密码不一致
	{
		fclose(fp);
		rect_circle(512-200, 384-100, 512+200, 384+100, 34429);
		Outtextxx(512-170, 384-75, 512-170+340, "两次输入密码不一致", 32, 65535);
		return 0;
	}
	else if (strlen(un) < 4)
	{
		rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170, 384 - 60, 512 - 170 + 340, "用户名需长于三位", 32, 65535);
		return 0;
	}
	else if (strlen(pw) < 4)
	{
		rect_circle(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
		Outtextxx(512 - 170, 384 - 60, 512 - 170 + 340, "密码需长于三位", 32, 65535);
		return 0;
	}
	
	else //成功return LOGIN  返回登录界面
	{
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 2;
}


//密保问题，用于更改密码（也就是忘记密码，本质上是同一个）
int secret_question(char *user, char *password)
{
	//因为输入法的原因，答案仅支持输入字母和数字
	int q = 0, flag = 0;
	char answer[20] = "";
	Clrmous();
	regi_sq_draw();
	while (1)
	{
		Newxy();
		if ((flag = list_func(610, 280, 610 + 370, 280 + 50, 5, &q)) == 0)
		{
			Outtext(610 + 5, 380+50-5-32, answer, 32, 40, 44373);
		}
		else if (flag == 1)
		{
			answer[0] = 0;
		}
		if (mouse_press(610, 280 + 100, 610 + 370, 280 + 50 + 100) == MOUSE_IN_L)
		{
			kbinput(610, 280 + 100, 610 + 370, 280 + 50 + 100, answer, 2);
		}
		if (mouse_press(686 - 15, 490 - 15, 814 + 15, 522 + 15) == MOUSE_IN_L)
		{
			if (sq_check(q, answer) == 1)
			{
				user_creat(user, password, q, answer);
				shadow_l(512 - 200, 384 - 100, 512 + 200, 384 + 100, 34429);
				Outtext(312 + 30, 284 + 40, "注册成功！", 48, 80, 65535);
				Outtext(312 + 92, 484 - 60, "3秒后进入登录界面", 16, 25, 65535);
				delay(1000);
				Bar64k(312 + 92, 484 - 60, 312 + 92 + 25 * 8 + 16, 484 - 60 + 16, 34429);
				Outtext(312 + 92, 484 - 60, "2秒后进入登录界面", 16, 25, 65535);
				delay(1000);
				Bar64k(312 + 92, 484 - 60, 312 + 92 + 25 * 8 + 16, 484 - 60 + 16, 34429);
				Outtext(312 + 92, 484 - 60, "1秒后进入登录界面", 16, 25, 65535);
				delay(1000);
				return 1;
			}
		}
		if (mouse_press(0, 0, 50, 50) == MOUSE_IN_L)
		{
			return 0;
		}
	}
}

int sq_check(int q, char* answer)
{
	if (q == 0)//未输入用户名
	{
		Outtext(620, 340, "请选择问题", 16, 30, 63488);
	}
	else if (*answer == '\0')//未输入密码
	{
		Outtext(620, 440, "请输入答案", 16, 30, 63488);
	}
	else
	{
		return 1;
	}
	return 0;
}
/******y1，y2需相等，输入的坐标是水平两点坐标，num为向下展开的行数*******/
void drop_down_list(int x1, int y1, int x2, int y2, int num)
{
	int i;
	if (y1 != y2)
		return;
	Clrmous();//更新鼠标状态，防止留痕
	Bar64k(x1, y1, x2, y2+num*50, 65535);
	for (i = 1; i <= num; i++)
	{
		rectangle64k(x1, y1+(i-1)*50, x2, y2+i*50, 0);
		switch (i)
		{
		case 1:
			Outtext(x1+10, y1+(i-1)*50+13, "您的生日是？", 24, 28, 44373);
			break;
		case 2:
			Outtext(x1+10, y1+(i-1)*50+13, "您身份证号六到十位是？", 24, 28, 44373);
			break;
		case 3:
			Outtext(x1+10, y1+(i-1)*50+13, "您宠物的名字是？", 24, 28, 44373);
			break;
		case 4:
			Outtext(x1+10, y1+(i-1)*50+13, "您第一位恋人的名字是？", 24, 28, 44373);
			break;
		default:
			break;
		}
	}
}

int list_choose(int x1, int y1, int x2, int y2, int num)
{
	int i = 0;
	drop_down_list(x1, y1, x2, y2, num);
	while (1)
	{
		Newxy();
		if (mouse_press(x1, y1, x2, y2 + num * 50) == MOUSE_IN_L)
		{
			i = (MouseY-y1)/50+1;
			return i;
		}
		else if (press == 1)
		{
			return i;
		}
	}
}

/******y1,y2的差保持在50效果最好*******/
int list_func(int x1, int y1, int x2, int y2, int num, int *q)
{
	int flag = *q;
	if (mouse_press(x2-50, y1, x2, y1+50) == MOUSE_IN_L)
	{
		delay(100);
		if ((flag = list_choose(x1, y2, x2, y2, 4)) != 0)
		{
			Clrmous();
			frame(x1, y1, x2, y2, 65535);
			Bar64k(x2-48, y1+2, x2-2, y1+48, 33808);
			Filltriangle(x2-50+15, y1+15, x2-25, y1+30, x2-15, y1+15, 65535);
			switch (flag)
			{
			case 1:
				Outtext(x1+10, y1+13, "您的生日是？", 24, 28, 44373);
				break;
			case 2:
				Outtext(x1+10, y1+13, "您身份证号六到十位是？", 24, 28, 44373);
				break;
			case 3:
				Outtext(x1+10, y1+13, "您宠物的名字是？", 24, 28, 44373);
				break;
			case 4:
				Outtext(x1+10, y1+13, "您第一位恋人的名字是？", 24, 28, 44373);
				break;
			default:
				break;
			}
			putbmp_partial(x1, y2, x2, y2 + num * 50, "BMP//lng.bmp");
			frame(610, 280 + 100, 610 + 370, 280 + 50 + 100, 65535);  	//密码
			Outtext(500, 390, "答案", 32, 62, 63488);
			Outtext(610 + 20, 380 + 15, "只允许输入字母和数字", 16, 30, 0);
			shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
			Outtext(686, 480, "注册", 48, 80, 63488);
			*q = flag;
			return 1;
		}
		else
		{
			Clrmous();
			putbmp_partial(x1, y2, x2, y2 + num * 50, "BMP//lng.bmp");
			frame(610, 280 + 100, 610 + 370, 280 + 50 + 100, 65535);  	//密码
			Outtext(500, 390, "答案", 32, 62, 63488);
			shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
			Outtext(686, 480, "注册", 48, 80, 63488);
			return 0;
		}
	}
	return 2;
}

void regi_sq_draw()
{
	putbmp_partial(610-168, 165, 610+370, 165+50+200, "BMP//lng.bmp");
	frame(610, 280, 610 + 370, 280 + 50, 65535);             //用户名
	Bar64k(980 - 48, 282, 980-2, 280 + 48, 33808);
	Filltriangle(980-50+15, 280+15, 980-25, 280+30, 980-15, 280+15, 65535);
	Outtext(500, 290, "问题", 32, 62, 63488);
	Outtext(610 + 20, 280 + 15, "选择一个密保问题", 16, 30, 0);

	frame(610, 280 + 100, 610 + 370, 280 + 50 + 100, 65535);  	//密码
	Outtext(500, 390, "答案", 32, 62, 63488);
	Outtext(610 + 20, 380 + 15, "只允许输入字母和数字", 16, 30, 0);

	shadow_l(686 - 15, 490 - 15, 814 + 15, 522 + 15, 65535);
	Outtext(686, 480, "注册", 48, 80, 63488);
}





