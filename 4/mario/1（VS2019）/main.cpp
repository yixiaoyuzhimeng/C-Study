
/*--------------------------------------�ļ�����---------------------------------------------------------------*/
#include<graphics.h> 
#include<ege/sys_edit.h>
#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string.h>
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib, "graphics19.lib")

/*----------------------------------------�궨��---------------------------------------------------------------*/
#define DisplayBackground "D:\\mario\\resouce\\background\\background.png"  //��Ϊ�ĸ��˵��ı���ͼ 
#define GeneralBackground "D:\\mario\\resouce\\background\\back0.jpg"       //��Ϊ��Ϸ����ע�ᡢ��½�����÷�����Ŀǰ�����ı���ͼ 

/*--------------------------------------ȫ�ֱ���---------------------------------------------------------------*/

typedef struct Player
{
	char username[50];//��ʱ�û���
	char password[50];//��ʱ����
	int dir;//����K��0��A��1��D��2���ַ�����̰�����Ӧ������Ҫһ������
	int user; //ͨ���ж����û������οͣ��������Ƿ�������ݿ� ��2�οͣ�1�û���
	int score1;
	int score2;
	int score3;
	int scores;//�ܷ� 
}PLAYER;
PLAYER player;
int dir;//ע��0����½1 

//sys_edit username;//��������Ϊȫ�ֱ������������쳣��֪����ô����
//sys_edit password;

char szSqlText[1000];//SQL���  
MYSQL* conn;   //����ָ��
MYSQL_RES *res;//�����
MYSQL_ROW row;//�б���
PIMAGE background;//ʼ���ڸı�ı���ͼƬ 
MUSIC backmusic;  //������ 
MUSIC soundeffect;//��Ч 


/*--------------------------------------��������---------------------------------------------------------------*/
void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height);//����ͼƬ 
void drawOption(int k, const char a[]); //���ư�ť 
int judgeOption(int x, int y);//�жϵ���İ�ť 
void backGround(const char a[]);
void initDisplay1();//����(������Ϸ)(��Ϸ����)(�˳���Ϸ)ѡ�� 
void initDisplay2();//����(ע��)(��½)(����)(�˳���Ϸ)ѡ�� 
void initDisplay3();//����(��Ϸ�ؿ�)(�û���Ϣ)(Ŀǰ����)(�˳���Ϸ)ѡ�� 
void initDisplay4();//����(��һ��)(�ڶ���)(������)(�˳���Ϸ)ѡ�δ�ﵽ�������������һ�� 
void regulation();//����ע���½�˵��û���������Ϸ����һ�������˳���Ϸ���˳������򲻻ᱣ����Ϸ���� 
void game1();//��һ�� 
void game2();//�ڶ��� 
void game3(); //������ 
void userName();//�û�����֤ 
void passWord();//������֤
void registerORland();//��½��ע��ɹ���,�������ݵĶ�ȡ���ߴ��
void playerInfo();//�û���Ϣ�������鿴�����÷�����ע���� 
void currentRank(); //Ŀǰ���� 
void clear(int i);//0��������,1�˺�ע�� 
void scoreSave();//��������
bool existPlayer();
void judgeOR();



int main()
{

	char host[] = "localhost";//������
	char szDatabase[] = "test";//���ݿ���
	char username[] = "root";//�������ݿ�ĺϷ��û���
	char password[] = "5210";//����Ա����
	unsigned int port = 3306;//���Ӷ˿ڣ�Ĭ��Ϊ3306





	/*-------------------------------------��ʼ������------------------------------------------*/

	//�������� 
	setinitmode(0, -4, 0);//���ó�ʼ���������������Ͻ� 
	initgraph(-1, -1, INIT_RENDERMANUAL);//��ʼ�����ڣ��˴�ȫ�����ֶ�ˢ�� 
	setcaption("���������򻯰�");


	//��������ɫ���� 
	setfontbkcolor(RED);
	setcolor(WHITE);
	setfillcolor(RED);
	setfont(40, 0, "����");



	//MYSQL* conn;
	if ((conn = mysql_init((MYSQL*)0))//��ʼ��mysql
		&& (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0)//ѡ��gbk�ַ�����ʾ����
		&& mysql_real_connect(conn, host, username, password, szDatabase, port, NULL, 0))//����mysql
	{
		xyprintf(100, 100,"���ӳɹ���");
	}
	else
	{
		xyprintf(100, 100, "����ʧ��!");
		mysql_close(conn);
		system("pause");
		return -1;
	}

	


	//����ͼƬ 
//	PIMAGE background=newimage(); 
//	getZoomImage(background,"D:\\mario\\1\\background.png",width,height) ;
//	getimage(background,"D:\\mario\\1\\background.png");// 


//	PIMAGE mario=newimage(); 
//	getimage(mario,"D:\\mario\\1\\mario.png");




/*-----------------------------------����̨���---------------------------------------------*/

//	printf("%d,%d",width,height); 
	//���ͼ��������
//	printf("[%d, %d]\n", getwidth(background), getheight(background));
//	printf("[%d, %d]\n", getwidth(mario), getheight(mario));

//	putimage(0,0,background);	
//	putimage_withalpha(NULL,mario,100,100);




/*-----------------------------------��������---------------------------------------------*/
	
	backmusic.OpenFile("D:\\mario\\resouce\\themesong.mp3");
	backmusic.Play(0);
	

	initDisplay1();




	////	��ȡ������� 
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

	/*-----------------------------------�رո��ִ򿪵�---------------------------------------------*/

	//	delimage(background);
	//	delimage(mario);

		backmusic.OpenFile("D:\\mario\\resouce\\themesong.mp3");
	backmusic.Play(0);

	backmusic.Close();

	getch();

	closegraph();

	//	mysql_free_result(res); //�ͷŽ����
		mysql_close(conn);      //�ر����ӵĴ��� 

	return 0;




	getch();
	return 0;

}

/*--------------------------------------���ߺ���---------------------------------------------------------------*/

void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height)//����ͼƬ����ͼƬ�ļ�fileName�м���ͼ��ͼ�����ŵ���pimg�ĳߴ�һ��
{
	PIMAGE temp = newimage();
	getimage(temp, fileName);

	if (getwidth(pimg) != width || getheight(pimg) != height)
		resize(pimg, width, height);

	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));

	delimage(temp);
}

void drawOption(int k, const char a[])//���ư�ť �����ڴ����ַ��������Լ�const) 
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

int judgeOption(int x, int y)//�ж��������ť 
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

void backGround(const char a[])//����ͼ��ʼ�� 
{
	/*----------------ȷ������ѭ������-------------*/
	if (backmusic.GetPlayStatus() == MUSIC_MODE_STOP)
	{
		backmusic.Play(0);
	}
	/*------------��ʱ��ͼ����ֹ�ڴ�й©-----------*/
	delimage(background);
	cleardevice();
	/*----------------���õ�ǰͼƬ-------------*/
	int width = getwidth();
	int height = getheight();
	background = newimage();
	getZoomImage(background, a, width, height);
	putimage(0, 0, background);
}

/*--------------------------------------�˵�����---------------------------------------------------------------*/

void initDisplay1()//�˵�һ 
{

	/*--------����ͼƬ---------*/
	backGround(DisplayBackground);

	/*--------���ư�ť---------*/
	drawOption(1, "������Ϸ");
	drawOption(2, "��Ϸ����");
	drawOption(3, "�˳���Ϸ");

	/*-------�����ť---------*/
	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{
		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())	//����Ϣ����ѭ�����жϵ��
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //������ͨ����־λ���ж�
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

void initDisplay2()//�˵��� 
{

	backGround(DisplayBackground);

	drawOption(1, "ע��/��½");
	drawOption(2, "����");
	drawOption(3, "����");



	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{
		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();


			if (msg.is_left() && msg.is_down())
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //������ͨ����־λ���ж�
		{

			switch (judgeOption(xClick, yClick))
			{
			case 1:
				//ע�� Ҳ��Ҫ�ȶ����ݿ���û���ظ����û��� 
				//��½��Ҫ�������ݿ�ȶ��û���������
				//��½�ɹ���ʹplayer.user = 1;
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

void initDisplay3()//�˵��� 
{

	backGround(DisplayBackground);

	drawOption(1, "��Ϸ�ؿ�");
	drawOption(2, "�û���Ϣ");
	drawOption(3, "Ŀǰ����");
	drawOption(4, "�˳�");

	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{
		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //������ͨ����־λ���ж�
		{
			switch (judgeOption(xClick, yClick))
			{
			case 1:
				 //��˼����ô��ֹ�ڴ泬�أ���ô��ʱ����ͼƬ����ô�ܹ����ø������ʹ�ã� 
				initDisplay4();
				break;
			case 2:
				playerInfo();
				break;
			case 3:
				currentRank();
				break;
			case 4:
				//�������ݵı��棿 
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

void initDisplay4()//�˵��� 
{
	backGround(DisplayBackground);
	scoreSave();//ÿ�δ�����Ϸ�ؿ�����ѡ��ʱ���Զ����·���

	drawOption(1, "��һ��");
	drawOption(2, "�ڶ���");
	drawOption(3, "������");
	drawOption(4, "����");

	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{
		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //������ͨ����־λ���ж�
		{
			switch (judgeOption(xClick, yClick))
			{
			case 1:
				//��˼����ô��ֹ�ڴ泬�أ���ô��ʱ����ͼƬ����ô�ܹ����ø������ʹ�ã� 
				game1();
				break;
			case 2:
				//ÿ����Ϸ����Ҫ����ԭ�������������µı��� 
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

/*--------------------------------------��Ϸ����---------------------------------------------------------------*/

void regulation()//��Ϸ���� 
{
	backGround(GeneralBackground);

	drawOption(4, "����");


	setbkmode(TRANSPARENT);
	outtextrect(255, 90, 800, 500, "(1)\tAD�����ƶ�\n\tK��Ծ\n\t�ո���ͣ\n\n(2)\t���治�ᱣ����Ϸ����\n\n(3)\t����ע���½\n\t�����û���Ϸ�ֵܷ�����\n\tҲ�������÷���\n\n(4)\tֻ�дﵽһ���������ܹ�����Ĺؿ�");




	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{
		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //������ͨ����־λ���ж�
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

void game1()//��һ�� 
{


	scoreSave();
	
}

void game2()//�ڶ��� 
{
	if (player.scores > 5)
	{

	}
	scoreSave();
}

void game3()//������ 
{
	if (player.scores > 10)
	{

	}
	scoreSave();
}

/*--------------------------------------�������ݿ�---------------------------------------------------------------*/

void userName()//ע��ʱ�û����ȶ� 
{

	backGround(GeneralBackground);
	drawOption(4, "����");
	drawOption(6, "��¼");
	drawOption(7, "ע��");
	/*
	����EGE�������ȱ�ݣ��˴�����ȷ�������������е���һ�������ܰ��س���������룻
	�ٷ��̳��е�ԭ����
	��sys_edit ���м���Ƿ��ý���� isfocus() ʧЧ��
	�Ǵ�����������ʱ���Ͳ�����ͨ���س�����ȡ�������ݣ���Ϊ��֪���������ĸ������
	�Ǿ�ֻ�� ͨ����Ӱ�ť �ķ�ʽ�������ĳ����ťʱ���ͻ�ȡ��Ӧ�����������ݡ�
	�˴�����������ť������û���������
	���������û����󣬰�����½����ע�ᣩ��
	*/
	setbkmode(TRANSPARENT);
	sys_edit username;
	sys_edit password;
	username.create(false);//����
	username.move(400, 70);
	username.size(400,60);
	username.setfont(32, 0, "΢���ź�");
	username.visable(true);
	username.setfocus();//��ȡ���� 
	
	xyprintf(220, 80, "�û�����");
	password.create(false);//����
	password.move(400, 250);
	password.size(400, 60);
	password.setfont(32, 0, "΢���ź�");
	password.visable(true);
	xyprintf(240, 260, "���룺");

	//player.username = "";//���ʽ�����ǿ��޸ĵ���ֵ��
	//player.password = "";
	username.settext("");//��������
	password.settext("");//��������



/*		//	��ȡ������� 
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
	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{

		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //������ͨ����־λ���ж�
		{
			switch (judgeOption(xClick, yClick))
			{
				case 4:
					username.destory();
					password.destory();
					initDisplay1();
					break;
				case 6:
					dir = 1; //��½
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
					dir = 2;//ע��
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
	//		//���ݿ���ϢѰ���Լ������GUI��ʵ���������� 
	//		if(==)    
	//		{
	//			//�Ѵ��ڸ��û������Ƿ��½�� �ǣ��������룬�����ݿ�ȶԣ���ƥ�䣬����˵�������ƥ�䣬�����������break�˳���������һ��ѭ��ѡ���������룩����break�˳����� 
	//		 } 
	//		 else{
	//	 	//�����ڸ��û����Ƿ�ע�᣿�ǣ�����������д洢��������һ��ѭ��ѡ���½����break�˳���������һ��ѭ��ѡ�� 
	//	 	return ;
	//	 } 
	//	}
	//��ʱʵ�ֲ�����Ƹ�����������ķ���
}

void passWord()//��½ʱ�û���������ȶ� 
{

	backGround(GeneralBackground);
	drawOption(4, "����");
	drawOption(6, "��¼");
	drawOption(7, "ע��");
	setbkmode(TRANSPARENT);
	sys_edit username;
	sys_edit password;
	username.create(false);//����
	username.move(400, 70);
	username.size(400, 60);
	username.setfont(32, 0, "΢���ź�");
	username.visable(true);
	//username.setfocus();//��ȡ���� 
	xyprintf(220, 80, "�û�����");
	password.create(false);//����
	password.move(400, 250);
	password.size(400, 60);
	password.setfont(32, 0, "΢���ź�");
	password.visable(true);
	password.setfocus();//��ȡ���� 
	xyprintf(240, 260, "���룺");
	username.settext(player.username);


	if (existPlayer())//�û�������
	{
		if (dir==1)//��������½
		{
			xyprintf(230, 420, "�û������ڣ��밴�������ʼ��������");
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
							if (strcmp(player.password, szSqlText)==0)//����ֵΪ0��˵���ַ���1==�ַ���2��
							{
								xyprintf(230, 480, "��½�ɹ����밴���������");
								getch();
								username.destory();
								password.destory();
								player.user= 1; //��Ϊ�û�
								registerORland();
								initDisplay3();
							}
							else
							{
								xyprintf(230, 480, "��������밴�������������");
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
			xyprintf(230, 450, "�û����Ѵ��ڣ��밴�������������");
			getch();
			username.destory();
			password.destory();
			dir = 0;
			//return;
			userName();

			//username.settext("");//��������
		}
	}
	else//�û���������
	{
		if (dir==2)//������ע��
		{
			xyprintf(230, 420, "�û��������ڣ��������������ע��");
			bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
			int xClick, yClick;
			for (; is_run(); delay_fps(60))
			{
				isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
				while (mousemsg()) //��ȡ�����Ϣ
				{
					mouse_msg msg = getmouse();
					if (msg.is_left() && msg.is_down())
					{
						isClick = true;
						xClick = msg.x;
						yClick = msg.y;
					}
				}
				if (isClick) //������ͨ����־λ���ж�
				{
					switch (judgeOption(xClick, yClick))
					{
					case 4:
						username.destory();
						password.destory();
						initDisplay1();
						break;
					case 7:
						dir = 2;//ע��
						password.gettext(50, player.password);
						flushkey();
						if (player.password[0] != '\0')
						{
							username.destory();
							password.destory();
							xyprintf(230, 450, "ע��ɹ�,��������������أ������µ�¼");
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
			xyprintf(230,420, "�û��������ڣ��밴�������������");
			getch();
			username.destory();
			password.destory();
			dir = 0;
			//return;
			userName();
			//username.settext("");//��������
		}

	}
	//	while(1)
	//	{
	//		if(==)
	//		{
	//			if(==)
	//			{
	//				//��½�ɹ�
	//				//���ز˵�2��Ӧ�����ٽ���˵�3 
	//				 return; 
	//			} 
	//			else
	//			{
	//				//�������  
	//			} 
	//		} 
	//		else
	//		{
	//			//���û��������� 
	//		}
	//	}

}

void registerORland()
{
	switch (dir)
	{

		case 1://��½(��tbl_player���û�һ�е����ݸ��Ƶ�ȫ�ֽṹ������У�
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

		case 2://ע�ᣨ��tbl_player���½�һ��)
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

void playerInfo()//�û���Ϣ
{
	backGround(GeneralBackground);

	drawOption(4, "����");
	drawOption(5, "���÷���");
	drawOption(7, "ע��");

	setbkmode(TRANSPARENT);

	if (player.user == 1)
	{
		char s1[20];
		char s2[20];
		char s3[20];
		sprintf(s1, "select score1 from tbl_player where username='%s'", player.username);
		sprintf(s2, "select score2 from tbl_player where username='%s'", player.username);
		sprintf(s3, "select score3 from tbl_player where username='%s'", player.username);

		rectprintf(300, 100, 600, 40, "��ǰ�û�����\t��һ��\t�ڶ���\t������\t�ܷ�");//���������
		rectprintf(300,300 , 600, 40, "%-14s%-7d%-7d%-7dd%-7d" , atoi(s1),atoi(s2),atoi(s3),(atoi(s1)+atoi(s2)+atoi(s3)));//ֻ�򿪱��˵���Ϣ�û����������׶εķ��� 
	}
	else
	{
		xyprintf(300, 300, "�Բ��𣬲���¼�οͷ��������¼������");
	}


	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{
		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���	
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down()) //����Ϣ����ѭ�����жϵ��
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (isClick) //������ͨ����־λ���ж�
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

void currentRank()//Ŀǰ���� 
{
	backGround(GeneralBackground);
	drawOption(4, "����");
	setbkmode(TRANSPARENT);
	int i;
	MYSQL_RES* res;
	MYSQL_ROW  row;

	//�������
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
			xyprintf(100,30,"����%d�������Ϣ��", i);
			rectprintf(100,100,600,40,"����\t�ܷ�\t�û���");//���������
			for(int n=1;n<=i;n++)
			{
				row = mysql_fetch_row(res);//���г�ȡ����ʾ��ѯ������
				rectprintf(100,120+50*n,600,40,"%-7d%-7s%-7s", n,row[5], row[0]);//����?
			}
		}
		else
		{
			xyprintf(100,50,"û��ѧ����Ϣ");
		}
		mysql_free_result(res);
	}


	bool isClick;//���ñ�־λ����ֹ��whileѭ���е������Ϣ���ƶ�����Ϣ���ǵ� 
	int xClick, yClick;
	for (; is_run(); delay_fps(60))
	{

		isClick = false;	//��־λ��Ϊfalse, ���Ǳ�Ҫ�Ĳ���
		while (mousemsg()) //��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();

			//����Ϣ����ѭ�����жϵ��
			if (msg.is_left() && msg.is_down())
			{
				isClick = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}


		if (isClick) //������ͨ����־λ���ж�
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
		//xyprint(, , "���������㣬�밴���������");
		if (i == 1)
		{
			sprintf(szSqlText, "delete  from tbl_player where username ='%s'",player.username);
			if (mysql_query(conn, szSqlText))
			{
				xyprintf(100, 200, "select failed.\n");
			}
			player.user = 0;
		//xyprint(, , "�˻���ע�����밴���������");
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
