
/*--------------------------------------文件包含---------------------------------------------------------------*/
#include<graphics.h> 
#include<ege/sys_edit.h>
#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string.h>
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib, "graphics19.lib")

/*----------------------------------------宏定义---------------------------------------------------------------*/
#define DisplayBackground "D:\\mario\\resouce\\background\\background.png"  //作为四个菜单的背景图 
#define GeneralBackground "D:\\mario\\resouce\\background\\back0.jpg"       //作为游戏规则、注册、登陆、重置分数、目前排名的背景图 

/*--------------------------------------全局变量---------------------------------------------------------------*/

typedef struct Player
{
	char username[50];//临时用户名
	char password[50];//临时密码
	int dir;//方向（K上0，A左1，D右2）字符与键盘按键对应数字需要一个函数
	int user; //通过判断是用户还是游客，来决定是否调用数据库 （2游客，1用户）
	int score1;
	int score2;
	int score3;
	int scores;//总分 
}PLAYER;
PLAYER player;
int dir;//注册0，登陆1 

//sys_edit username;//好像不能作为全局变量，发生的异常不知道怎么处理？
//sys_edit password;

char szSqlText[1000];//SQL语句  
MYSQL* conn;   //连接指针
MYSQL_RES *res;//结果集
MYSQL_ROW row;//行变量
PIMAGE background;//始终在改变的背景图片 
MUSIC backmusic;  //背景乐 
MUSIC soundeffect;//音效 


/*--------------------------------------函数声明---------------------------------------------------------------*/
void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height);//放缩图片 
void drawOption(int k, const char a[]); //绘制按钮 
int judgeOption(int x, int y);//判断点击的按钮 
void backGround(const char a[]);
void initDisplay1();//包含(进入游戏)(游戏规则)(退出游戏)选项 
void initDisplay2();//包含(注册)(登陆)(试玩)(退出游戏)选项 
void initDisplay3();//包含(游戏关卡)(用户信息)(目前排名)(退出游戏)选项 
void initDisplay4();//包含(第一关)(第二关)(第三关)(退出游戏)选项，未达到分数不会进入下一关 
void regulation();//对于注册登陆了的用户，玩了游戏后请一定按（退出游戏）退出，否则不会保存游戏数据 
void game1();//第一关 
void game2();//第二关 
void game3(); //第三关 
void userName();//用户名验证 
void passWord();//密码验证
void registerORland();//登陆与注册成功后,进行数据的读取或者存放
void playerInfo();//用户信息（包括查看、重置分数、注销） 
void currentRank(); //目前排名 
void clear(int i);//0分数清零,1账号注销 
void scoreSave();//保存数据
bool existPlayer();
void judgeOR();



int main()
{

	char host[] = "localhost";//主机名
	char szDatabase[] = "test";//数据库名
	char username[] = "root";//连接数据库的合法用户名
	char password[] = "5210";//管理员密码
	unsigned int port = 3306;//连接端口，默认为3306





	/*-------------------------------------初始化设置------------------------------------------*/

	//窗体设置 
	setinitmode(0, -4, 0);//设置初始环境，这里是左上角 
	initgraph(-1, -1, INIT_RENDERMANUAL);//初始化窗口，此处全屏，手动刷新 
	setcaption("超级玛丽简化版");


	//字体与颜色设置 
	setfontbkcolor(RED);
	setcolor(WHITE);
	setfillcolor(RED);
	setfont(40, 0, "黑体");



	//MYSQL* conn;
	if ((conn = mysql_init((MYSQL*)0))//初始化mysql
		&& (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0)//选择gbk字符集显示中文
		&& mysql_real_connect(conn, host, username, password, szDatabase, port, NULL, 0))//连接mysql
	{
		xyprintf(100, 100,"连接成功！");
	}
	else
	{
		xyprintf(100, 100, "连接失败!");
		mysql_close(conn);
		system("pause");
		return -1;
	}

	


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
	
	backmusic.OpenFile("D:\\mario\\resouce\\themesong.mp3");
	backmusic.Play(0);
	

	initDisplay1();




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

		backmusic.OpenFile("D:\\mario\\resouce\\themesong.mp3");
	backmusic.Play(0);

	backmusic.Close();

	getch();

	closegraph();

	//	mysql_free_result(res); //释放结果集
		mysql_close(conn);      //关闭连接的代码 

	return 0;




	getch();
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

void drawOption(int k, const char a[])//绘制按钮 （由于传入字符串，所以加const) 
{
	switch (k)
	{
	case 1:
		fillellipse(410, 396, 145, 35);
		outtextxy(330, 376, a);
		break;
	case 2:
		fillellipse(410, 496, 145, 35);
		outtextxy(330, 476, a);
		break;
	case 3:
		fillellipse(410, 596, 145, 35);
		outtextxy(330, 576, a);
		break;
	case 4:
		fillellipse(110, 460, 60, 60);
		outtextxy(70, 440, a);
		break;
	case 5:
		fillellipse(110, 280, 90, 60);
		outtextxy(30, 260, a);
		break;
	case 6:
		fillellipse(110, 280, 60, 60);
		outtextxy(70, 260, a);
		break;
	case 7:
		fillellipse(110, 100, 60, 60);
		outtextxy(70, 80, a);
		break;
	default:
		break;
	}
}

int judgeOption(int x, int y)//判断鼠标点击按钮 
{
	int m=0;
	if ((x >= 320) && (x <= 500) && (y >= 370) && (y <= 420))
	{
		m = 1;
	}
	else if ((x >= 320) && (x <= 500) && (y >= 470) && (y <= 520))
	{
		m = 2;
	}
	else if ((x >= 320) && (x <= 500) && (y >= 570) && (y <= 620))
	{
		m = 3;
	}
	else if ((x >= 70) && (x <= 150) && (y >= 420) && (y <= 500))
	{
		m = 4;
	}
	else if ((x >= 30) && (x <= 200) && (y >= 210) && (y <= 270))
	{
		m = 5;
	}
	else if ((x >= 70) && (x <= 150) && (y >= 240) && (y <= 320))
	{
		m = 6;
	}
	else if ((x >= 70) && (x <= 150) && (y >= 60) && (y <= 140))
	{
		m = 7;
	}
	else {
		m = 0;
	}
	return m;
}

void backGround(const char a[])//背景图初始化 
{
	/*----------------确保音乐循环播放-------------*/
	if (backmusic.GetPlayStatus() == MUSIC_MODE_STOP)
	{
		backmusic.Play(0);
	}
	/*------------及时清图，防止内存泄漏-----------*/
	delimage(background);
	cleardevice();
	/*----------------设置当前图片-------------*/
	int width = getwidth();
	int height = getheight();
	background = newimage();
	getZoomImage(background, a, width, height);
	putimage(0, 0, background);
}

/*--------------------------------------菜单函数---------------------------------------------------------------*/

void initDisplay1()//菜单一 
{

	/*--------背景图片---------*/
	backGround(DisplayBackground);

	/*--------绘制按钮---------*/
	drawOption(1, "进入游戏");
	drawOption(2, "游戏规则");
	drawOption(3, "退出游戏");

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
			switch (judgeOption(xClick, yClick))
			{
			case 1:
				initDisplay2();
				break;
			case 2:
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

	drawOption(1, "注册/登陆");
	drawOption(2, "试玩");
	drawOption(3, "返回");



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

			switch (judgeOption(xClick, yClick))
			{
			case 1:
				//注册 也需要比对数据库有没有重复的用户名 
				//登陆需要调用数据库比对用户名与密码
				//登陆成功后使player.user = 1;
				userName();
				break;
			case 2:
				player.user = 0;
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

	drawOption(1, "游戏关卡");
	drawOption(2, "用户信息");
	drawOption(3, "目前排名");
	drawOption(4, "退出");

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
			switch (judgeOption(xClick, yClick))
			{
			case 1:
				 //在思考怎么防止内存超载？怎么及时清理图片？怎么能够更好更方便的使用？ 
				initDisplay4();
				break;
			case 2:
				playerInfo();
				break;
			case 3:
				currentRank();
				break;
			case 4:
				//设置数据的保存？ 
				scoreSave();
				mysql_close(conn);
				exit(0);
				break;
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
	scoreSave();//每次闯过游戏关卡来到选集时，自动更新分数

	drawOption(1, "第一关");
	drawOption(2, "第二关");
	drawOption(3, "第三关");
	drawOption(4, "返回");

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
			switch (judgeOption(xClick, yClick))
			{
			case 1:
				//在思考怎么防止内存超载？怎么及时清理图片？怎么能够更好更方便的使用？ 
				game1();
				break;
			case 2:
				//每个游戏都需要销毁原来背景，插入新的背景 
				game2();
				break;
			case 3:
				game3();
				break;
			case 4:
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

	drawOption(4, "返回");


	setbkmode(TRANSPARENT);
	outtextrect(255, 90, 800, 500, "(1)\tAD左右移动\n\tK跳跃\n\t空格暂停\n\n(2)\t试玩不会保存游戏数据\n\n(3)\t可以注册登陆\n\t会有用户游戏总分的排名\n\t也可以重置分数\n\n(4)\t只有达到一定分数才能过后面的关卡");




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
			switch (judgeOption(xClick, yClick))
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


	scoreSave();
	
}

void game2()//第二关 
{
	if (player.scores > 5)
	{

	}
	scoreSave();
}

void game3()//第三关 
{
	if (player.scores > 10)
	{

	}
	scoreSave();
}

/*--------------------------------------调用数据库---------------------------------------------------------------*/

void userName()//注册时用户名比对 
{

	backGround(GeneralBackground);
	drawOption(4, "返回");
	drawOption(6, "登录");
	drawOption(7, "注册");
	/*
	由于EGE库自身的缺陷，此处不能确定是两个焦点中的哪一个，不能按回车键完成输入；
	官方教程中的原话是
	“sys_edit 类中检测是否获得焦点的 isfocus() 失效，
	那创建多个输入框时，就不可以通过回车来获取输入内容，因为不知道焦点在哪个输入框。
	那就只能 通过添加按钮 的方式，当点击某个按钮时，就获取对应的输入框的内容”
	此处设置两个按钮来完成用户名的输入
	即输入完用户名后，按（登陆）或（注册）键
	*/
	setbkmode(TRANSPARENT);
	sys_edit username;
	sys_edit password;
	username.create(false);//单行
	username.move(400, 70);
	username.size(400,60);
	username.setfont(32, 0, "微软雅黑");
	username.visable(true);
	username.setfocus();//获取焦点 
	
	xyprintf(220, 80, "用户名：");
	password.create(false);//单行
	password.move(400, 250);
	password.size(400, 60);
	password.setfont(32, 0, "微软雅黑");
	password.visable(true);
	xyprintf(240, 260, "密码：");

	//player.username = "";//表达式必须是可修改的左值？
	//player.password = "";
	username.settext("");//清空输入框
	password.settext("");//清空输入框



/*		//	获取鼠标坐标 
		int k=0;
		for(;is_run();delay_fps(60))
		{
			char str[32];
			int x,y;
			
			mousepos(&x,&y);
			
			sprintf(str,"%4d %4d",x,y);
			
			outtextxy(230,360,str);
		}	
*/
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
			switch (judgeOption(xClick, yClick))
			{
				case 4:
					username.destory();
					password.destory();
					initDisplay1();
					break;
				case 6:
					dir = 1; //登陆
					username.gettext(50, player.username);
					flushkey();
					if (player.username[0] != '\0')
					{
						username.destory();
						password.destory();
						passWord();
					}
					break;
					
				case 7:
					dir = 2;//注册
					username.gettext(50, player.username);
					flushkey();
					if (player.username[0] != '\0')
					{
						username.destory();
						password.destory();
						passWord();
					}
					break;
				default:
					break;
			}
		}
	}
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
	//暂时实现不了设计复杂与操作简便的方法
}

void passWord()//登陆时用户名与密码比对 
{

	backGround(GeneralBackground);
	drawOption(4, "返回");
	drawOption(6, "登录");
	drawOption(7, "注册");
	setbkmode(TRANSPARENT);
	sys_edit username;
	sys_edit password;
	username.create(false);//单行
	username.move(400, 70);
	username.size(400, 60);
	username.setfont(32, 0, "微软雅黑");
	username.visable(true);
	//username.setfocus();//获取焦点 
	xyprintf(220, 80, "用户名：");
	password.create(false);//单行
	password.move(400, 250);
	password.size(400, 60);
	password.setfont(32, 0, "微软雅黑");
	password.visable(true);
	password.setfocus();//获取焦点 
	xyprintf(240, 260, "密码：");
	username.settext(player.username);


	if (existPlayer())//用户名存在
	{
		if (dir==1)//如果点击登陆
		{
			xyprintf(230, 420, "用户名存在，请按任意键开始输入密码");
			sprintf(szSqlText, "select password from tbl_player where username='%s'", player.username);
			if (mysql_query(conn, szSqlText))
			{
				printf("select failed\n");
				return ;
			}
			else
			{
				res = mysql_store_result(conn);
				mysql_free_result(res);
			}
			//xyprintf(230, 480, "%s", szSqlText);
			bool isClick;
			int xClick, yClick;
			for (; is_run(); delay_fps(60))
			{
				isClick = false;	
				while (mousemsg()) 
				{
					mouse_msg msg = getmouse();
					if (msg.is_left() && msg.is_down())
					{
						isClick = true;
						xClick = msg.x;
						yClick = msg.y;
					}
				}
				if (isClick) 
				{
					switch (judgeOption(xClick, yClick))
					{
					case 4:
						username.destory();
						password.destory();
						initDisplay1();
						break;
					case 6:
						password.gettext(50, player.password);
						flushkey();
						if (player.password[0] != '\0') {
							if (strcmp(player.password, szSqlText)==0)//返回值为0，说明字符串1==字符串2；
							{
								xyprintf(230, 480, "登陆成功，请按任意键继续");
								getch();
								username.destory();
								password.destory();
								player.user= 1; //作为用户
								registerORland();
								initDisplay3();
							}
							else
							{
								xyprintf(230, 480, "密码错误，请按任意键重新输入");
								getch();
								username.destory();
								password.destory();
								passWord();
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			xyprintf(230, 450, "用户名已存在，请按任意键重新输入");
			getch();
			username.destory();
			password.destory();
			dir = 0;
			//return;
			userName();

			//username.settext("");//清空输入框
		}
	}
	else//用户名不存在
	{
		if (dir==2)//如果点击注册
		{
			xyprintf(230, 420, "用户名不存在，请输入密码进行注册");
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
					switch (judgeOption(xClick, yClick))
					{
					case 4:
						username.destory();
						password.destory();
						initDisplay1();
						break;
					case 7:
						dir = 2;//注册
						password.gettext(50, player.password);
						flushkey();
						if (player.password[0] != '\0')
						{
							username.destory();
							password.destory();
							xyprintf(230, 450, "注册成功,请输入任意键返回，并重新登录");
							getch();
							registerORland();
							userName();
						}
						break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			xyprintf(230,420, "用户名不存在，请按任意键重新输入");
			getch();
			username.destory();
			password.destory();
			dir = 0;
			//return;
			userName();
			//username.settext("");//清空输入框
		}

	}
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

void registerORland()
{
	switch (dir)
	{

		case 1://登陆(把tbl_player中用户一行的数据复制到全局结构体变量中）
			char s1[50];
			char s2[50];
			char s3[50];
			sprintf(s1, "select score1 where username='%s'", player.username);
			sprintf(s2, "select score2 where username='%s'", player.username);
			sprintf(s3, "select score3 where username='%s'", player.username);
			player.score1 = atoi(s1);
			player.score2 = atoi(s2);
			player.score3 = atoi(s3);
			player.scores = (player.score1+ player.score2+ player.score3);
			break;

		case 2://注册（在tbl_player中新建一行)
			sprintf(szSqlText, "insert into tbl_player(username,password,score1,score2,score3,scores)values('%s','%s',%d,%d,%d,%d)", player.username, player.password, 0, 0, 0, 0);
			if (mysql_query(conn, szSqlText))
			{
				printf("inserted failed\n");
			}
			break;
	}
}

void judgeOR()
{
}

void playerInfo()//用户信息
{
	backGround(GeneralBackground);

	drawOption(4, "返回");
	drawOption(5, "重置分数");
	drawOption(7, "注销");

	setbkmode(TRANSPARENT);

	if (player.user == 1)
	{
		char s1[20];
		char s2[20];
		char s3[20];
		sprintf(s1, "select score1 from tbl_player where username='%s'", player.username);
		sprintf(s2, "select score2 from tbl_player where username='%s'", player.username);
		sprintf(s3, "select score3 from tbl_player where username='%s'", player.username);

		rectprintf(300, 100, 600, 40, "当前用户分数\t第一关\t第二关\t第三关\t总分");//参数需调整
		rectprintf(300,300 , 600, 40, "%-14s%-7d%-7d%-7dd%-7d" , atoi(s1),atoi(s2),atoi(s3),(atoi(s1)+atoi(s2)+atoi(s3)));//只打开本人的信息用户名，各个阶段的分数 
	}
	else
	{
		xyprintf(300, 300, "对不起，不记录游客分数，请登录后设置");
	}


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

			switch (judgeOption(xClick, yClick))
			{
			case 4:
				initDisplay3();
				break;
			case 5:
				clear(0);
				initDisplay3();
				break;
			case 7:
				clear(1);
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
	drawOption(4, "返回");
	setbkmode(TRANSPARENT);
	int i;
	MYSQL_RES* res;
	MYSQL_ROW  row;

	//遍历玩家
	sprintf(szSqlText, "select  username,password,score1,score2,score3,scores from tbl_player order by scores desc ");
	if (mysql_query(conn, szSqlText))
	{
		xyprintf(100,200,"select failed.\n");
	}
	else
	{
		res = mysql_store_result(conn);
		i = (int)mysql_num_rows(res);
		if (i > 0)
		{
			xyprintf(100,30,"共有%d个玩家信息：", i);
			rectprintf(100,100,600,40,"排名\t总分\t用户名");//参数需调整
			for(int n=1;n<=i;n++)
			{
				row = mysql_fetch_row(res);//逐行抽取和显示查询的数据
				rectprintf(100,120+50*n,600,40,"%-7d%-7s%-7s", n,row[5], row[0]);//排序?
			}
		}
		else
		{
			xyprintf(100,50,"没有学生信息");
		}
		mysql_free_result(res);
	}


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
			switch (judgeOption(xClick, yClick))
			{
			case 4:
				initDisplay3();
				break;
			default:
				break;
			}
		}
	}

}

void clear(int i)
{

	if (player.user == 1)
	{	
		if (i == 0) 
		{
			sprintf(szSqlText, "update tbl_player set score1 =%d,score2=%d,score3=%d, scores=%d where username ='%s'", 0, 0, 0, 0, player.username);
			if (mysql_query(conn, szSqlText))
			{
				xyprintf(100, 200, "select failed.\n");
			}
		}
		//xyprint(, , "分数已清零，请按任意键返回");
		if (i == 1)
		{
			sprintf(szSqlText, "delete  from tbl_player where username ='%s'",player.username);
			if (mysql_query(conn, szSqlText))
			{
				xyprintf(100, 200, "select failed.\n");
			}
			player.user = 0;
		//xyprint(, , "账户已注销，请按任意键返回");
		//getch();
		}
	}
}

void scoreSave()
{
	player.scores = player.score1 + player.score2 + player.score3;

	if (player.user == 1)
	{
		char s1[20];
		char s2[20];
		char s3[20];
		sprintf(s1, "select score1 where username='%s'", player.username);
		sprintf(s2, "select score2 where username='%s'", player.username);
		sprintf(s3, "select score3 where username='%s'", player.username);

		if (player.score1 > atoi(s1) )
		{
			sprintf(szSqlText, "update tbl_player set score1 =%d where username ='%s'", player.score1, player.username);
			if (mysql_query(conn, szSqlText))
			{
				xyprintf(100, 200, "select failed.\n");
			}
		}
		if (player.score2 > atoi(s2))
		{
			sprintf(szSqlText, "update tbl_player set score2=%d where username ='%s'", player.score2, player.username);
			if (mysql_query(conn, szSqlText))
			{
				xyprintf(100, 200, "select failed.\n");
			}
		}
		if (player.score3 > atoi(s3))
		{
			sprintf(szSqlText, "update tbl_player set score3=%d where username ='%s'", player.score3, player.username);
			if (mysql_query(conn, szSqlText))
			{
				xyprintf(100, 200, "select failed.\n");
			}
		}

		sprintf(szSqlText, "update tbl_player set scores=(score1+score2+score3) where username ='%s'",  player.username);
		if (mysql_query(conn, szSqlText))
		{
			xyprintf(100, 200, "select failed.\n");
		}
	}
}

bool existPlayer()
{
	int i = 0;
	MYSQL_RES* res;
	sprintf(szSqlText, "select username from tbl_player where username='%s'", player.username);
	if (mysql_query(conn, szSqlText))
	{
		xyprintf(100,200,"select failed");
	}
	else
	{
		res = mysql_store_result(conn);
		i = (int)mysql_num_rows(res);
		mysql_free_result(res);
	}
	return i > 0;
}
