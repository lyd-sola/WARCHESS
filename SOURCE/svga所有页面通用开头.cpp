/********************************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name: 
author: 
version: 
Description: 
date:

更新日志

函数目录
******************************************************************/
//SVGA分辨率1024*768
//使用时保证清除以下每一个注释，别忘了加进工程噢

#include "common.h"

int /*name_of_page*/(parameter)
{
	//declare variables down here
	
	//initialize down here
	clrmous(MouseX, MouseY);
	/*name_of_page*/_draw();

	while(1)
	{
		Newxy();
		if(mouse_press(/*叉叉的位置*/) == 1)
		{
			return EXIT;
		}
		//以下是此页面核心函数
		
	}
	
}

void /*name_of_page*/_draw()
{
	//画页面
	
	//记得画右上角的叉叉
	
}