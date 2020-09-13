/*****************���ļ�������λѧ���Ĺ������������ܴ�����******************************/

/*********************************************************************************
Copyright(c)  2018 ���׽�&������  �ᵺ��ϰ����ģ��ϵͳ
file_name: outtext.c
data: 2019.9.1
version: 3.1
Description: ���ֿ�
data :	2017/8/13
			version 1.0 �汾�������
		2017/8/17
				�Ż��㷨�ṹ
				
		2017/8/30
				������ASC�빦��
		2017/10/26
			�����������ASC�������Ϊһ��
******************************************************************/

#include "common.h"

/*********************************************************
���ú���
	void Putpixel64k(int x, int y, unsigned char color);	
**************************************************/
void Outtext(int x,int y, char *s, int size, int part, int color)		//size16\24\32\48
{
	FILE *hzk_p;
	unsigned char quma,weima;	
	unsigned long offset;		
	int i,j,pos;
	int shift;
	unsigned char mask[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	
	switch(size)
	{
		case 16:
			{			
				char mat[32];													//����32�ֽڵ��ַ����鴢����Ϣ
				hzk_p=fopen("HZK\\HZK16.dat","rb");					//�򿪺��ֿ��ļ�
				
				if(hzk_p==NULL)
				{
					printf("\n Can't open file HZK ! Press any key to return.");
					getch();
					exit(1);
				}
				while(*s!='\0')													//���ַ���û�н���ʱ
				{
				
					if(*s>0&&*s<127)//����ַ����г��ַ�����
					{
						weima=*s-32;//��ȡλ��
						offset=(94*2+weima-1)*32l;
						shift=1;
					}
					else
					{
						quma=s[0]-128-32;
						weima=s[1]-128-32;											//������λ��
						offset=(94 * (quma-1) + (weima-1)) * 32L;
						shift=2;
					}
					fseek(hzk_p,offset,0);
					fread(mat,32,1,hzk_p);
					for(i=0;i<16;i++)
					{
						pos=2*i;
						for(j=0;j<16;j++)
						{
							if(( mask[j%8]&mat[pos+j/8] ) != NULL)
								Putpixel64k(x + j ,y + i ,color);		
						}
					
					}
					s+=shift;
					x+=part;
						
				}
				fclose(hzk_p);
				break;
			}
			
			
			
			
			
		case 24:
			{		
					char mat[72];
					hzk_p=fopen("HZK\\HZK24.dat","rb");
					if(hzk_p==NULL)
					{
						printf("\n Can't open file HZK ! Press any key to return.");
						getch();
						exit(1);
					}
					while(*s!='\0')
					{
						if(*s>0&&*s<127)//����ַ����г��ַ�����
						{
							weima=*s-32;//��ȡλ��
							offset=(94*2+weima-1)*72l;
							shift=1;
						}
						else
						{
							quma=s[0]-128-32;
							weima=s[1]-128-32;
							offset=(94 * (quma-1) + (weima-1)) * 72L;
							shift=2;
						}
						fseek(hzk_p,offset,0);
						fread(mat,72,1,hzk_p);
						for(i=0;i<24;i++)
						{
							pos=3*i;
							for(j=0;j<24;j++)
							{
								if(( mask[j%8]&mat[pos+j/8] ) != NULL)
									Putpixel64k(x + j ,y + i  ,color);		
							}
						
						}
						s+=shift;
						x+=part;
							
					}
					fclose(hzk_p);
					break;
			
			}
				
		case 32:
			{		
					char mat[128];
					hzk_p=fopen("HZK\\HZK32K","rb");
					if(hzk_p==NULL)
					{
						printf("\n Can't open file HZK ! Press any key to return.");
						getch();
						exit(1);
					}
					while(*s!='\0')
					{
						if(*s>0&&*s<127)//����ַ����г��ַ�����
						{
							weima=*s-32;//��ȡλ��
							offset=(94*2+weima-1)*128l;
							shift=1;
						}
						else
						{
							quma=s[0]-128-32;
							weima=s[1]-128-32;
							offset=(94 * (quma-1) + (weima-1)) * 128L;
							shift=2;
						}
						fseek(hzk_p,offset,0);
						fread(mat,128,1,hzk_p);
						for(i=0;i<32;i++)
						{
							pos=4*i;
							for(j=0;j<32;j++)
							{
								if(( mask[j%8]&mat[pos+j/8] ) != NULL)
									Putpixel64k(x + j ,y + i  ,color);			
						
							}
						}
						s+=shift;
						x+=part;
							
					}
					fclose(hzk_p);
					break;
			}
			
		
			
		case 48:
			{		
				char mat[288];
				hzk_p=fopen("HZK\\HZK48K","rb");
				if(hzk_p==NULL)
				{
					printf("\n Can't open file HZK ! Press any key to return.");
					getch();
					exit(1);
				}
				while(*s!='\0')
				{
					if(*s>0&&*s<127)//����ַ����г��ַ�����
					{
						weima=*s-32;//��ȡλ��
						offset=(94*2+weima-1)*288l;
						shift=1;
					}
					else
					{
						quma=s[0]-128-32;
						weima=s[1]-128-32;
						offset=(94 * (quma-1) + (weima-1)) * 288L;
						shift=2;
					}
					fseek(hzk_p,offset,0);
					fread(mat,288,1,hzk_p);
					for(i=0;i<48;i++)
					{
						pos=6*i;
						for(j=0;j<48;j++)
						{
							if(( mask[j%8]&mat[pos+j/8] ) != NULL)
								Putpixel64k(x + j ,y + i  ,color);		
						}
					}
					s+=shift;
					x+=part;
						
				}
				fclose(hzk_p);
				break;
			}
	}
}

void out_ASC(int x, int y, char *s, int color)
{
	FILE *hzk_p;
	unsigned long offset;		
	int i,j;
	char mat[16];													//����32�ֽڵ��ַ����鴢����Ϣ
	hzk_p=fopen("HZK\\ASC16","rb");					//�򿪺��ֿ��ļ�
	if(hzk_p==NULL)
	{
		printf("\n Can't open file HZK ! Press any key to return.");
		getch();
		exit(1);
	}
	while(*s!='\0')
	{
		offset=(*s)*16+1;			 //������ַ����ֿ���ƫ����
		fseek(hzk_p,offset,SEEK_SET);
		fread(mat,16,1,hzk_p); 			//ȡ���ַ�16�ֽڵĵ�����ģ����buffer��
		for(i=0;i<16;i++)
		{
			for(j=0;j<8;j++)
			{
				if(((mat[i]>>(7-j))&0x1)!=NULL)
				{
					Putpixel64k(x+j,y+i,color);
				}
			}
		}

		s++; //һ���ַ�����ռ��һ���ֽ�
		x+=8;//�ַ�����
	}	
	fclose(hzk_p);
	
		
}


void out_ASCplus(int x, int y, char *s, int color)
{
	FILE *hzk_p;
	unsigned long offset;		
	int i,j,m,n;
	char mat[16];													//����32�ֽڵ��ַ����鴢����Ϣ
	hzk_p=fopen("HZK\\ASC16","rb");					//�򿪺��ֿ��ļ�
	if(hzk_p==NULL)
	{
		printf("\n Can't open file HZK ! Press any key to return.");
		getch();
		exit(1);
	}
	while(*s!='\0')
	{
		offset=(*s)*16+1;			 //������ַ����ֿ���ƫ����
		fseek(hzk_p,offset,SEEK_SET);
		fread(mat,16,1,hzk_p); 			//ȡ���ַ�16�ֽڵĵ�����ģ����buffer��
		for(i=0;i<16;i++)
		{
			for(j=0;j<8;j++)
			{
				if(((mat[i]>>(7-j))&0x1)!=NULL)
				{
					for(m=0;m<2;m++)
					{
						for(n=0;n<2;n++)
						{
								Putpixel64k(x + j * 2 + m,y + i * 2 + n,color);
						}
					}
				}
			}
		}

		s++; //һ���ַ�����ռ��һ���ֽ�
		x+=20;//�ַ�����
	}	
	fclose(hzk_p);
	
}


int Outtext24(int x1,int y1,int x2,int y2, char *s, int part, int color)
{
	FILE *hzk_p;
	unsigned char quma,weima;	
	unsigned long offset;		
	int i,j,pos;
	int shift;
	int x = x1+54,y = y1;
	int k = 0,state = 0;
	unsigned char mask[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	
	char mat[72];
	hzk_p=fopen("HZK\\HZK24.dat","rb");
	if(hzk_p==NULL)
	{
		printf("\n Can't open file HZK ! Press any key to return.");
		getch();
		exit(1);
	}
	while(*s!='\0')
	{
		if(*s>0&&*s<127)//����ַ����г��ַ�����
		{
			weima=*s-32;//��ȡλ��
			offset=(94*2+weima-1)*72l;
			shift=1;
		}
		else
		{
			quma=s[0]-128-32;
			weima=s[1]-128-32;
			offset=(94 * (quma-1) + (weima-1)) * 72L;
			shift=2;
		}
		fseek(hzk_p,offset,0);
		fread(mat,72,1,hzk_p);
		for(i=0;i<24;i++)
		{
			pos=3*i;
			for(j=0;j<24;j++)
			{
				if(( mask[j%8]&mat[pos+j/8] ) != NULL)
					Putpixel64k(x + j ,y + i  ,color);		
			}
		}
		s+=shift;
		k+=shift; 
		x+=part;
		if(x>x2-24)
		{
			x = x1;
			y = y+27;
			if(y >y2-24)
			{
				state = k;
				break;
			}
		}
	}
	fclose(hzk_p);	
	return state;
}


unsigned long puthz(int x0,int y0,char *path,unsigned long len,int page)	//��len��ʼ��ʾtxt�ļ�������������Ϣ����������һҳ�׸��ֵ�offset
{
	FILE *user;
	unsigned long lg=0;				//���ڼ����ļ��ܳ��ȣ�����forѭ��
	char s[3]={0};					//ÿ�ζ�ȡ2���ֽڣ���3λ'\0'��ʾ����
	int x,y;					//��ʾ���������
	user=fopen(path,"r");				//�ж��ܷ��txt�ļ�
	if(user==NULL)  exit(1);
	fseek(user,0,2);					//fseek���ļ�β����ȡ�ܳ���
	lg=ftell(user);
	fseek(user,len,0);					//�ص�len����ʼ���
	if(page==1) x=x0+16*2;
	if(page>1)  x=x0+16*2;
	for(y=y0;len<lg;len=ftell(user))
	{
		if((x+16)>=992)				//�ж�������Ƿ񳬳�����
		{
			y+=24;                //���¼��24
			x=x0;
		}
		if((y+24)>=768)				//�ж������Ƿ�ﵽ���
		{
			lg=ftell(user);			//��ȡ��ǰoffset������
			fclose(user);			//fclose�����ļ����
			return lg;
		}
		fread(s,1,2,user);				//��ȡ2���ֽ�
		if(s[0]=='\n')				//��s[0]Ϊ'\n'����ʾ����
		{
			fseek(user,-1,1);			//��Ϊ�Ѷ�ȡ�����ӵ�ǰλ�÷���һ���ֽ�
			y+=24;
			x=x0+16*2;
			continue;
		}
	
		if((s[0]>=0)&&(s[0]<='z'))		//��ȡ��ΪӢ������
		{
		  ENtext16(x,y,s[0],0);
		  fseek(user,-1,1);			//���������һλ����ӵ�ǰλ�÷���һλ
		  x+=8;
		}
		else					//��ȡ��Ϊ���ģ����һ������
		{
			CHtext16(x,y,s,0);
			x+=16;
		}
	}
	fclose(user);					//fclose�ļ��������ļ���
	return 0;					//�ļ��Ѷ��꣬����0��Ϊ����һҳ��־
}
//////////////////////////////////////////////////////////////////////////////


void CHtext16(   int x,int y,char *s,int color)		//���һ�����ֵĺ���
{
	
	FILE *hzk;
	int i,j,k;
	unsigned char qh,wh;					//����λ�붨��					//weima
 	unsigned long offset;					//ƫ��������
 	char buffer[32];					//32Ϊ��ģ����


	if ((hzk=fopen("HZK\\HZK16.dat","rb"))==NULL)		//�жϺ��ֿ��ܷ��
	{
		
        fclose(hzk);
		printf("\n Can't open file HZK ! Press any key to return.");
        getch();
		exit(1);
	}
	
	qh=s[0]-0xa0;						//��������λ�룬��-0xa0
	wh=s[1]-0xa0;	
	offset=(94*(qh-1)+(wh-1))*32L; 				//����λ������
	fseek(hzk,offset,0);
	fread(buffer,32,1,hzk);           			//������ģ��Ϣ
	
	for(i=0;i<16;i++)
	{
		for(j=0;j<2;j++)
		{
			for(k=0;k<8;k++)
			{
				if((buffer[i*2+j]>>(7- k))&0x1)  //Ϊ1��λ��ʾ
				{
					Putpixel64k(x+k+j*8,y+i,color);	//��㺯��
				}
			}
		}
	}
	fclose(hzk);
}
///////////////////////////////////////////////////////////////////////////
void ENtext16( int x,int y,char s,int color)		//���һ��Ӣ�ĺ���
{

	FILE *asc;
	int i,j;
	unsigned long offset;
	 char buffer[16];

	if ((asc=fopen("HZK\\ASC16","rb"))==NULL)
	{
		printf("\n Can't open file HZK ! Press any key to return.");
		getch();
		exit(1);
	}

	
	offset=s*16L;                         	//����λ����
	fseek(asc,offset,0);
	fread(buffer,16,1,asc);                        	//������ģ��Ϣ
	
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			if((buffer[i]>>(7-j))&0x1)    	//Ϊ1��λ��ʾ
			{
				Putpixel64k(x+j,y+i,color);
			}
		}
	}
	fclose(asc);
}
///////////////////////////////////////
