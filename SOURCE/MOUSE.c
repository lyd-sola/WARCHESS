/**********************************************************
	2020 ���Ƶѡ�����ͩ WARCHESSս��
	���ļ�����������ѧ�������Ľ�ϣ�vga��svga������lydħ�����ϣ��������ܴ�����
			���ε����ҹ���������빤����QAQ��
	
	��lydħ�ģ�����ʵ�ǽ����������ŵ��ϣ�
		1.���»�������꣨ʹ����֤ȯͶ��κ���F�͵���������ת��SVGAģʽ�������˲�ͬ�����̬��
		2.�޸��˴���걳����mouse_sq�����С���Լ��洢��Χ���������»��ƵĴ�С������
		3.��д�˴��������������˽������������⺯��clrmous(MouseX, MouseY)���Լ�ҳ���л���겻������ʾ��Newxy�޸ģ�

	ʹ�÷�����
		���п��ܱ�����ڵ��Ļ�ͼ����ǰ������clrmous(MouseX, MouseY)
		����ͼ�ν���ʱ������һ�����
*********************************************************/
#include"common.h"

/*******************************         MOUSE.C         ********************************/ 
/*������������й����ʵ�ּ���ز���          
    �������ܴ�����              */ 

union REGS regs; 

int MouseX = 0, MouseY = 0, press = 0, MouseS = 0;
int Mouse_flag = 1; 
int mouse_sq[16][20] = {0}; 

/*����꺯��*/ 
void Cursor(int x,int y)
{
	
	switch(MouseS)
	{
		case 1:                                  //�������
		{
				Line64k(x-1,y+9,x-1,y+8,65503);
				Line64k(x,y+7,x,y+11,65503);
				Line64k(x+1,y+6,x+1,y+13,65503);
				Line64k(x+2,y+8,x+2,y+14,65503);
				Line64k(x+3,y-1,x+3,y+15,65503);
				Circleup64k(x+4,y-1,1,65503);
				Line64k(x+4,y-2,x+4,y+15,65503);
				Line64k(x+5,y-1,x+5,y+16,65503);
				Circleup64k(x+6,y+3,1,65503);
				Line64k(x+6,y+2,x+6,y+16,65503);
				Line64k(x+7,y+3,x+7,y+17,65503);
				Circleup64k(x+8,y+5,1,65503);
				Line64k(x+8,y+4,x+8,y+17,65503);
				Line64k(x+9,y+5,x+9,y+16,65503);
				Circleup64k(x+10,y+7,1,65503);
				Line64k(x+10,y+6,x+10,y+16,65503);
				Line64k(x+11,y+7,x+11,y+13,65503);

				Line64k(x-1,y+9,x-1,y+8,0);
				Line64k(x-1,y+8,x+1,y+6,0);
				Line64k(x+1,y+6,x+3,y+10,0);
				Line64k(x+3,y+10,x+3,y-1,0);
				Circleup64k(x+4,y-1,1,0);
				Line64k(x+5,y-1,x+5,y+5,0);
				Circleup64k(x+6,y+3,1,0);
				Line64k(x+7,y+3,x+7,y+7,0);
				Circleup64k(x+8,y+5,1,0);
				Line64k(x+9,y+5,x+9,y+9,0);
				Circleup64k(x+10,y+7,1,0);
				Line64k(x+11,y+7,x+11,y+13,0);
				Circlerd64k(x+7,y+13,4,0);
				Line64k(x+7,y+17,x+3,y+15,0);
				Line64k(x+3,y+15,x+1,y+13,0);
				Line64k(x+1,y+13,x-1,y+9,0);
		}
			break;
		case 2:                        //���
		{
			Line64k(x+1,y-1,x+9,y-1,0);
			Line64k(x+1,y+15,x+9,y+15,0);
			Line64k(x+5,y-1,x+5,y+15,0);
		}
			break;
		case 3:                        //ʮ��
		{
			Line64k(x-1,y+7,x+11,y+7,65503);
			Line64k(x+5,y-1,x+5,y+15,65503);
		}
			break;
		default:              //Ĭ�����
		{
			Line64k(x,y,x,y+13,65503);
			Line64k(x+1,y+1,x+1,y+12,65503);
			Line64k(x+2,y+2,x+2,y+11,65503);
			Line64k(x+3,y+3,x+3,y+10,65503);
			Line64k(x+4,y+4,x+4,y+12,65503);
			Line64k(x+5,y+5,x+5,y+9,65503);
			Line64k(x+5,y+11,x+5,y+14,65503);
			Line64k(x+6,y+6,x+6,y+9,65503);
			Line64k(x+6,y+13,x+6,y+15,65503);
			Line64k(x+7,y+7,x+7,y+9,65503);
			Line64k(x+8,y+8,x+8,y+9,65503);
			Line64k(x+9,y+9,x+9,y+9,65503);
			
			Line64k(x-1,y-1,x-1,y+14,0);
			Line64k(x-1,y+14,x+3,y+11,0);
			Line64k(x+3,y+11,x+3,y+12,0);
			Line64k(x+3,y+12,x+4,y+13,0);
			Line64k(x+4,y+13,x+4,y+14,0);
			Line64k(x+4,y+14,x+7,y+17,0);
			Line64k(x+7,y+17,x+7,y+13,0);
			Line64k(x+7,y+13,x+6,y+12,0);
			Line64k(x+6,y+12,x+6,y+11,0);
			Line64k(x+6,y+11,x+5,y+10,0);
			Line64k(x+5,y+10,x+11,y+10,0);
			Line64k(x+11,y+10,x-1,y-2,0);
		}
		break;
	}
}

/*��ʼ����꺯�����ĸ��β�ȷ�������ƶ���Χ*/ 
int Initmouse(int xmi, int xma, int ymi, int yma)
{
    int retcode; 
    regs.x.ax = 0; 
    int86(51, &regs, &regs); 
    retcode = regs.x.ax; 
    if(retcode == 0)
    {
	    return 0; 
    }
    regs.x.ax = 7; 
    regs.x.cx = xmi; 
    regs.x.dx = xma; 
    int86(51, &regs, &regs); 
    regs.x.ax = 8; 
    regs.x.cx = ymi; 
    regs.x.dx = yma; 
    //regs.x.bx = 0; 
    int86(51, &regs, &regs); 
    Mouse_flag = 1; 
    return retcode; 
}
/*��ȡ���״̬����*/ 
int Readmouse(void)
{
    //int xx0 = MouseX, yy0 = MouseY, buto = 0; 
    int xnew, ynew; 
    //  do
    //  {
	regs.x.ax = 3; 
	int86(51, &regs, &regs); 
	xnew = regs.x.cx; 
	ynew = regs.x.dx; 
	press = regs.x.bx; 
	delay(10); 
    //  }
    //  while(xnew == xx0 && ynew == yy0 && press == buto); 
    MouseX = xnew; 
    MouseY = ynew; 
    return  0; 
}

/*����긲�Ǳ�������*/ 
void Mouse_savebk(int x, int y)
{
    register int i, j; 
    for(i = 0; i <= 15; i ++ )
    for(j = 0; j <= 19; j ++ )
    mouse_sq[i][j] = Getpixel64k(x + i - 1, y + j - 2); 
}

/*ȥ��������긲�Ǳ�������*/ 
void Mouse_savebk2(void)
{
    Mouse_savebk(MouseX, MouseY); 
}

/*�ָ����Ǳ�������*/ 
void Mouse_putbk(int x, int y)
{
    register int i, j; 
    for(i = 0; i <= 15; i ++ )
    for(j = 0; j <= 19; j ++ )
    Putpixel64k(x + i - 1, y + j - 2, mouse_sq[i][j]); 
}

/*�ж�����Ƿ���ĳ������*/ 
int Mouse_press(int x1, int y1, int x2, int y2)
{
    if(MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2 && press)
    return 1; 
    else
    return 0; 
}
/*�ж�����Ƿ���ĳ�������ⰴ��*/ 
int Mouse_pressother(int x1, int y1, int x2, int y2)
{
	if ((MouseX  <  x1 || MouseX >= x2 || MouseY < y1 || MouseY > y2) && press)
		return 1; 
	else
		return 0; 
}
/*�ж�����Ƿ�λ��ĳ�����Ϸ�*/ 
int Mouse_above(int x1, int y1, int x2, int y2)
{
    if(MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2)
	  return 1; 
    else
	  return 0; 
}
/*�ж�����Ƿ�λ��ĳ������*/ 
int Mouse_aboveother(int x1, int y1, int x2, int y2)
{
	if(MouseX  <  x1 || MouseX >= x2 || MouseY  <  y1 || MouseY  >  y2)
		return 1; 
	else
		return 0; 
}

/*******************lydħ�Ĳ���***************************/

/*�ж�����Ƿ���ĳ������*/ 
int mouse_press(int x1, int y1, int x2, int y2)
{
	//�ڿ��е�����򷵻�1
	if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 1)
	{
		return 1;
	}
	
	//�ڿ���δ������򷵻�2
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 0)
	{
		return 2;
	}
	
	//�ڿ�����������3
	else if((MouseX < x1 
	|| MouseX > x2
	|| MouseY < y1
	|| MouseY > y2)
	&&press == 1)
	{
		return 3;
	}
		
	//�ڿ��е���Ҽ����򷵻�4
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 2)
	{
		return 4;
	}
	
	//���ⲻ���
	else
	{
		return 0;
	}
}
/*�����꺯���������������*/
void clrmous(int nx,int ny)//������
{
	press = 0;
	if(Mouse_flag==1)
	{
		//Cursor(nx,ny);
		Mouse_putbk(nx,ny);
		Mouse_flag=0;
	}
}
/*������꺯������flag���*/
void drawmous(int nx,int ny)
{
	if(Mouse_flag==0)
	{
	    Cursor(nx,ny);
		Mouse_flag = 1;
	}
}

/*�������λ�ú���*/ 
void Newxy(void)
{
	int xx0 = MouseX, yy0 = MouseY; 

	Readmouse(); 
	if (MouseX == xx0 && MouseY == yy0 && Mouse_flag == 1) //���û�����ظ���
		return; 
    clrmous(xx0, yy0); 
	Mouse_savebk(MouseX, MouseY); 
	drawmous(MouseX,MouseY);
}

/*��������꺯��*/
void Clrmous(void)
{
	clrmous(MouseX, MouseY);
}