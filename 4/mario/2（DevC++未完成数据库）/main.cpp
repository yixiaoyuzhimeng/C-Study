/*--------------------------------------文件包含---------------------------------------------------------------*/ 
#include<graphics.h> 
#include<ege/sys_edit.h>
#include<stdio.h>
#include<stdlib.h>
//#include"mysql.h"

/*----------------------------------------宏定义---------------------------------------------------------------*/ 
#define DisplayBackground "D:\\mario\\1\\background.png"  //作为四个菜单的背景图 
#define GeneralBackground "D:\\mario\\1\\back0.jpg"       //作为游戏规则、注册、登陆、重置分数、目前排名的背景图 

/*--------------------------------------全局变量---------------------------------------------------------------*/ 
int dir;//菜单一的选项 ？ 
int user; //通过判断是用户还是游客，来决定是否调用数据库 （0游客，1用户） 
char szSqlText[1000];//SQL语句 ？ 
int score1;
int score2;
int score3;
int scores;//总分 
PIMAGE background;//始终在改变的背景图片 
MUSIC backmusic;  //背景乐 
MUSIC soundeffect;//音效 


/*--------------------------------------函数声明---------------------------------------------------------------*/ 
void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height);//放缩图片 
void drawOption(int k,const char a[]); //绘制按钮 
int judgeOption(int x,int y);//判断点击的按钮 
void backGround(const char a[]); 
void initDisplay1();//包含(进入游戏)(游戏规则)(退出游戏)选项 
void initDisplay2();//包含(注册)(登陆)(试玩)(退出游戏)选项 
void initDisplay3();//包含(游戏关卡)(重置分数)(目前排名)(退出游戏)选项 
void initDisplay4();//包含(第一关)(第二关)(第三关)(退出游戏)选项，未达到分数不会进入下一关 
void regulation();//对于注册登陆了的用户，玩了游戏后请一定按（退出游戏）退出，否则不会保存游戏数据 
void game1();//第一关 
void game2();//第二关 
void game3(); //第三关 
void logIn1();//注册验证 
void logIn2();//登陆验证 
void resetScore();//重置分数 
void currentRank(); //目前排名 
void clearScore();//分数清零 
 


/*--------------------------------------主函数---------------------------------------------------------------*/ 
int main()
{
	
/*-------------------------------------打开MySQL------------------------------------------*/ 
	
//	char host[]="localhost";         //MySQL主机名 
//	char szTargetDSN[]="test";       //数据库名 
//	const char username[]="root";    //连接数据库得合法用户名 
//	const char password[]="123";     //密码
//	unsigned int port=3306;          //连接端口，默认为3306
//	MYSQL *conn;                     //MySQL连接指针 
//	MYSQL_RES *res;                  //MySQL结果堆 
//	MYSQL_ROS row;                   //行变量 
	
/*-------------------------------------初始化设置------------------------------------------*/ 
	
	//窗体设置 
	cleardevice();
	setinitmode(0,-4,0);//设置初始环境，这里是左上角 
//	initgraph(480,320,INIT_RENDERMANUAL);
	initgraph(-1, -1,INIT_RENDERMANUAL);//初始化窗口，此处全屏，手动刷新 
//	initgraph(-1, -1);
	setcaption("超级玛丽简化版");

	
//	//获取当前窗口的长宽 
//	int width=getwidth();
//	int height=getheight();
	
		
	//字体与颜色设置 
//	setbkmode(TRANSPARENT);//背景透明
	setfontbkcolor(RED);
	setcolor(WHITE);
	setfillcolor(RED);
	setfont(40, 0, "黑体");
	
	
	//插入图片 
//	PIMAGE background=newimage(); 
//	getZoomImage(background,"D:\\mario\\1\\background.png",width,height) ;
//	getimage(background,"D:\\mario\\1\\background.png");// 
	
	
//	PIMAGE mario=newimage(); 
//	getimage(mario,"D:\\mario\\1\\mario.png");
	
	
	
	
/*-----------------------------------控制台检测---------------------------------------------*/	

//	printf("%d,%d",width,height); 
	//输出图像宽高数据
//	printf("[%d, %d]\n", getwidth(background), getheight(background));
//	printf("[%d, %d]\n", getwidth(mario), getheight(mario));
	
//	putimage(0,0,background);	
//	putimage_withalpha(NULL,mario,100,100);
	
	
	
	
/*-----------------------------------音乐设置---------------------------------------------*/
	
	backmusic.OpenFile("D:\\mario\\1\\themesong.mp3");
//	xyprintf(200, 220, "%s\n", backmusic.IsOpen() ? "音乐打开成功" : "音乐打开失败");//检查是否打开	
	backmusic.Play(0);

	
	
	initDisplay1();
	

	
	
//	drawOption(396,376,"进入游戏"); 
//	drawOption(496,476,"游戏规则"); 
//	drawOption(596,576,"退出游戏"); 

//	fillellipse(410,396,145,35);
//	outtextxy(330,376,"进入游戏");
//	fillellipse(410,496,145,35);
//	outtextxy(330,476,"游戏规则");
//	fillellipse(410,596,145,35);
//	outtextxy(330,576,"退出游戏");


////	获取鼠标坐标 
//	int k=0;
//	for(;is_run();delay_fps(60))
//	{
//		char str[32];
//		int x,y;
//		
//		mousepos(&x,&y);
//		
//		sprintf(str,"%4d %4d",x,y);
//		
//		outtextxy(230,360,str);
//		
//	}
	

	
	getch();
	
/*-----------------------------------关闭各种打开的---------------------------------------------*/
	
//	delimage(background);
//	delimage(mario);

	backmusic.Close();
	
	getch();
	
	closegraph();
	
//	mysql_free_result(res); //释放结果集
//	mysql_close(conn);      //关闭连接的代码 

	return 0;
}



/*--------------------------------------工具函数---------------------------------------------------------------*/ 

void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height)//缩放图片：从图片文件fileName中加载图像，图像缩放到和pimg的尺寸一致
{
	PIMAGE temp = newimage();
	getimage(temp, fileName);
	
	if (getwidth(pimg) != width || getheight(pimg) != height)
		resize(pimg, width, height);
		
	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));

	delimage(temp);
}


void drawOption(int k,const char a[])//绘制按钮 （由于传入字符串，所以加const) 
{
	switch(k)
	{
		case 1:
			fillellipse(410,396,145,35);
			outtextxy(330,376,a);
			break;
		case 2:
			fillellipse(410,496,145,35);
			outtextxy(330,476,a);
			break;
		case 3:
			fillellipse(410,596,145,35);
			outtextxy(330,576,a);
			break;
		case 4:
			fillellipse(110,460,60,60);
			outtextxy(70,440,a);
			break;
		case 5:
			fillellipse(110,240,90,60);
			outtextxy(30,220,a);
			break;
		default:
			break;
	}
}


int judgeOption(int x,int y)//判断鼠标点击按钮 
{
	int m;
	if((x>=320)&&(x<=500)&&(y>=370)&&(y<=420))
	{
		m=1;
	}
	else if((x>=320)&&(x<=500)&&(y>=470)&&(y<=520))
	{
		m=2;
	}
	else if((x>=320)&&(x<=500)&&(y>=570)&&(y<=620))
	{
		m=3;
	}
	else if((x>=70)&&(x<=150)&&(y>=420)&&(y<=500))
	{
		m=4;
	}
	else if((x>=30)&&(x<=200)&&(y>=210)&&(y<=270))
	{
		m=5;
	}
	return m;
} 


void backGround(const char a[])//背景图初始化 
{
	/*----------------确保音乐循环播放-------------*/ 
	if (backmusic.GetPlayStatus() == MUSIC_MODE_STOP )
	 {
		backmusic.Play(0);
	}
	/*------------及时清图，防止内存泄漏-----------*/ 
	delimage(background);
	cleardevice();
	/*----------------设置当前图片-------------*/ 
	int width=getwidth();
	int height=getheight();
	background=newimage(); 
	getZoomImage(background,a,width,height) ;
	putimage(0,0,background);
} 





/*--------------------------------------菜单函数---------------------------------------------------------------*/ 


void initDisplay1()//菜单一 
{
	
	/*--------背景图片---------*/ 	
	backGround(DisplayBackground);
	
	/*--------绘制按钮---------*/ 
	drawOption(1,"进入游戏"); 
	drawOption(2,"游戏规则"); 
	drawOption(3,"退出游戏"); 
	
	/*-------点击按钮---------*/ 
	bool isClick;//设置标志位，防止在while循环中点击的消息被移动的消息覆盖掉 
	int xClick, yClick;
	for (; is_run(); delay_fps(60)) 
	{
		isClick = false;	//标志位设为false, 这是必要的步骤
		while (mousemsg()) //获取鼠标消息
		{
			mouse_msg msg = getmouse();	
			if (msg.is_left() && msg.is_down())	//在消息处理循环中判断点击
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}	
		if (isClick) //在这里通过标志位来判断
		{	
			switch(judgeOption(xClick,yClick)) 
			{
				case 1:
					//delimage(background);
					initDisplay2();
					break;
				case 2:
				//	delimage(background);
					regulation();
					break;
				case 3:
					exit(0);
				default:
					break;
			}
		}	
	}
	delimage(background);
	return; 
}


void initDisplay2()//菜单二 
{

	backGround(DisplayBackground);

	drawOption(1,"注册/登陆"); 
	drawOption(2,"试玩"); 
	drawOption(3,"返回"); 

	

	bool isClick;//设置标志位，防止在while循环中点击的消息被移动的消息覆盖掉 
	int xClick, yClick;
	for (; is_run(); delay_fps(60)) 
	{
		isClick = false;	//标志位设为false, 这是必要的步骤
		while (mousemsg()) //获取鼠标消息
		{
			mouse_msg msg = getmouse();

			
			if (msg.is_left() && msg.is_down()) 
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //在这里通过标志位来判断
		{
			
			switch(judgeOption(xClick,yClick)) 
			{
				case 1: 
				//注册 也需要比对数据库有没有重复的用户名 
				//登陆需要调用数据库比对用户名与密码
					logIn1();
					break;
				case 2:
					dir=0; 
					initDisplay3();
					break;
				case 3:
					initDisplay1();
					break;
				default:
					break;
			}
		}	
	}
	return;
}


void initDisplay3()//菜单三 
{
		
	backGround(DisplayBackground);
	
	drawOption(1,"游戏关卡"); 
	drawOption(2,"重置分数"); 
	drawOption(3,"目前排名"); 
	drawOption(4,"退出"); 
	
	bool isClick;//设置标志位，防止在while循环中点击的消息被移动的消息覆盖掉 
	int xClick, yClick;
	for (; is_run(); delay_fps(60)) 
	{
		isClick = false;	//标志位设为false, 这是必要的步骤
		while (mousemsg()) //获取鼠标消息
		{
			mouse_msg msg = getmouse();
			//在消息处理循环中判断点击
			if (msg.is_left() && msg.is_down()) 
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //在这里通过标志位来判断
		{	
			switch(judgeOption(xClick,yClick)) 
			{
				case 1:
				//	delimage(background);   //在思考怎么防止内存超载？怎么及时清理图片？怎么能够更好更方便的使用？ 
					initDisplay4();
					break;
				case 2:
				//	delimage(background);
					resetScore();
					break;
				case 3:
					currentRank();
					break;
				case 4:
					//设置数据的保存？ 
					exit(0); 
				default:
					break;
			}
		}	
	}
	return;
}


void initDisplay4()//菜单四 
{
	backGround(DisplayBackground);
	
	drawOption(1,"第一关"); 
	drawOption(2,"第二关"); 
	drawOption(3,"第三关"); 
	drawOption(4,"返回");
	
	bool isClick;//设置标志位，防止在while循环中点击的消息被移动的消息覆盖掉 
	int xClick, yClick;
	for (; is_run(); delay_fps(60)) 
	{
		isClick = false;	//标志位设为false, 这是必要的步骤
		while (mousemsg()) //获取鼠标消息
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down()) 
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //在这里通过标志位来判断
		{
			switch(judgeOption(xClick,yClick)) 
			{
				case 1:
				//	delimage(background);   //在思考怎么防止内存超载？怎么及时清理图片？怎么能够更好更方便的使用？ 
					game1(); 
					break;
				case 2:
				//	delimage(background);
				//每个游戏都需要销毁原来背景，插入新的背景 
					game2();
					break;
				case 3:
					game3();
					break;
				case 4:
					// 菜单三需要销毁原来背景以及，插入背景图片的操作，并且 
					
					initDisplay3(); 
					 
				default:
					break;
			}
		}	
	}
	return;
}



/*--------------------------------------游戏函数---------------------------------------------------------------*/ 


void regulation()//游戏规则 
{
	backGround(GeneralBackground);
	
	drawOption(4,"返回"); 
	
	
	setbkmode(TRANSPARENT);
	outtextrect(255,90,800,500,"(1)\tAD左右移动\n\tK跳跃\n\t空格暂停\n\n(2)\t试玩不会保存游戏数据\n\n(3)\t可以注册登陆\n\t会有用户游戏总分的排名\n\t也可以重置分数\n\n(4)\t只有过了前一关才能过下一关" ); 
	
	
	
	
	bool isClick;//设置标志位，防止在while循环中点击的消息被移动的消息覆盖掉 
	int xClick, yClick;
	for (; is_run(); delay_fps(60)) 
	{
		
	
		isClick = false;	//标志位设为false, 这是必要的步骤
		
		
		while (mousemsg()) //获取鼠标消息
		{
			mouse_msg msg = getmouse();

			//在消息处理循环中判断点击
			if (msg.is_left() && msg.is_down()) 
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}

		
		if (isClick) //在这里通过标志位来判断
		{
			
			switch(judgeOption(xClick,yClick)) 
			{
				case 4:
					
					initDisplay1();
				default:
					break;
			}
		}	
	}
	
}


void game1()//第一关 
{
	
} 
 
 
void game2()//第二关 
{

} 
 
 
void game3()//第三关 
{
	
} 

 
 
 
/*--------------------------------------调用数据库---------------------------------------------------------------*/ 
 
//const char a[] 
void logIn1()//注册时用户名比对 
{
	
	backGround(GeneralBackground);
	drawOption(4,"返回"); 
	
//	setbkmode(TRANSPARENT);
//	sys_edit username;
//	username.create(false);
//	username.move(300,300);
//	int editTexyHeight=16;
//	username.size(editTextHeight*10,4*editTextHeight+10);
//	username.setbgcolor(WHITE);
//	username.setcolor(BLACK);
//	username.setfont(editTextHeight,0,"微软雅黑");
//	
//	int maxLen=60;
//	username.setmaxlen(maxLen);
//	username.visable(true);
//	username.setfocus();//获取焦点 
//	
//	int buffsize=100;
//	char strBuff[100]="";
//	int buffLen=0;
//	
//	bool flag_press=false;
//	
//	
//	for (; is_run(); delay_fps(60)) 
//	{
//		cleardevice();
//		xyprintf(200,300,"用户名：");
//		if (keystate(key_enter))
//		 {
//			editBox.gettext(50, buff);
//			//或者在这里
//			//flushkey()
//			break;
//		}
//	}
//	
	
	
//	while(1)
//	{
//		//数据库信息寻找以及如何在GUI中实现以下提醒 
//		if(==)    
//		{
//			//已存在该用户名，是否登陆？ 是，输入密码，与数据库比对（若匹配，进入菜单三；不匹配，密码输入错误，break退出，进入下一次循环选择重新输入）；否，break退出…… 
//		 } 
//		 else{
//	 	//不存在该用户，是否注册？是，输入密码进行存储，进入下一次循环选择登陆；否，break退出，进入下一次循环选择 
//	 	return ;
//	 } 
//	}
	
} 


//const char a[],const char b[] 
void logIn2()//登陆时用户名与密码比对 
{
	
	backGround(GeneralBackground);
	
//	while(1)
//	{
//		if(==)
//		{
//			if(==)
//			{
//				//登陆成功
//				//返回菜单2对应处，再进入菜单3 
//				 return; 
//			} 
//			else
//			{
//				//密码错误  
//			} 
//		} 
//		else
//		{
//			//该用户名不存在 
//		}
//	}

}



void resetScore()//重置分数 
{
	backGround(GeneralBackground);
	
	drawOption(4,"返回");
	drawOption(5,"重置分数");
	
	
	setbkmode(TRANSPARENT);
//	xyprintf(,,"分数\t第一关\t第二关\t第三关\t总分\n");
//	xyprintf(,,"%s\t%d\t%d\t%d\t%d\n",,,);//用户名，各个阶段的分数 
	
	
	bool isClick;//设置标志位，防止在while循环中点击的消息被移动的消息覆盖掉 
	int xClick, yClick;
	for (; is_run(); delay_fps(60)) 
	{	
		isClick = false;	//标志位设为false, 这是必要的步骤	
		while (mousemsg()) //获取鼠标消息
		{
			mouse_msg msg = getmouse();	
			if (msg.is_left() && msg.is_down()) //在消息处理循环中判断点击
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}	
		if (isClick) //在这里通过标志位来判断
		{
			
			switch(judgeOption(xClick,yClick)) 
			{
				case 4:
					initDisplay3();
				case 5:
					clearScore();
					initDisplay3();
					break;
				default:
					break;
			}
		}	
	}
}


void currentRank()//目前排名 
{
	backGround(GeneralBackground);
	
	drawOption(4,"返回"); 
	
	
	setbkmode(TRANSPARENT);
//	rectprintf(,,"排名\t总分\t用户名\n");
//	for()
//	{
//		rectprintf(,,"%d\t%d\t%s\n",,,);// 
//	}
	
	bool isClick;//设置标志位，防止在while循环中点击的消息被移动的消息覆盖掉 
	int xClick, yClick;
	for (; is_run(); delay_fps(60)) 
	{
		
		isClick = false;	//标志位设为false, 这是必要的步骤
		while (mousemsg()) //获取鼠标消息
		{
			mouse_msg msg = getmouse();

			//在消息处理循环中判断点击
			if (msg.is_left() && msg.is_down()) 
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}

		
		if (isClick) //在这里通过标志位来判断
		{
			
			switch(judgeOption(xClick,yClick)) 
			{
				case 4:
					delimage(background);
					initDisplay3();
					break;
				default:
					break;
			}
		}	
	}
	
}


void clearScore()
{
	
}
