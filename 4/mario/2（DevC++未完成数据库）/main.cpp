/*--------------------------------------�ļ�����---------------------------------------------------------------*/ 
#include<graphics.h> 
#include<ege/sys_edit.h>
#include<stdio.h>
#include<stdlib.h>
//#include"mysql.h"

/*----------------------------------------�궨��---------------------------------------------------------------*/ 
#define DisplayBackground "D:\\mario\\1\\background.png"  //��Ϊ�ĸ��˵��ı���ͼ 
#define GeneralBackground "D:\\mario\\1\\back0.jpg"       //��Ϊ��Ϸ����ע�ᡢ��½�����÷�����Ŀǰ�����ı���ͼ 

/*--------------------------------------ȫ�ֱ���---------------------------------------------------------------*/ 
int dir;//�˵�һ��ѡ�� �� 
int user; //ͨ���ж����û������οͣ��������Ƿ�������ݿ� ��0�οͣ�1�û��� 
char szSqlText[1000];//SQL��� �� 
int score1;
int score2;
int score3;
int scores;//�ܷ� 
PIMAGE background;//ʼ���ڸı�ı���ͼƬ 
MUSIC backmusic;  //������ 
MUSIC soundeffect;//��Ч 


/*--------------------------------------��������---------------------------------------------------------------*/ 
void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height);//����ͼƬ 
void drawOption(int k,const char a[]); //���ư�ť 
int judgeOption(int x,int y);//�жϵ���İ�ť 
void backGround(const char a[]); 
void initDisplay1();//����(������Ϸ)(��Ϸ����)(�˳���Ϸ)ѡ�� 
void initDisplay2();//����(ע��)(��½)(����)(�˳���Ϸ)ѡ�� 
void initDisplay3();//����(��Ϸ�ؿ�)(���÷���)(Ŀǰ����)(�˳���Ϸ)ѡ�� 
void initDisplay4();//����(��һ��)(�ڶ���)(������)(�˳���Ϸ)ѡ�δ�ﵽ�������������һ�� 
void regulation();//����ע���½�˵��û���������Ϸ����һ�������˳���Ϸ���˳������򲻻ᱣ����Ϸ���� 
void game1();//��һ�� 
void game2();//�ڶ��� 
void game3(); //������ 
void logIn1();//ע����֤ 
void logIn2();//��½��֤ 
void resetScore();//���÷��� 
void currentRank(); //Ŀǰ���� 
void clearScore();//�������� 
 


/*--------------------------------------������---------------------------------------------------------------*/ 
int main()
{
	
/*-------------------------------------��MySQL------------------------------------------*/ 
	
//	char host[]="localhost";         //MySQL������ 
//	char szTargetDSN[]="test";       //���ݿ��� 
//	const char username[]="root";    //�������ݿ�úϷ��û��� 
//	const char password[]="123";     //����
//	unsigned int port=3306;          //���Ӷ˿ڣ�Ĭ��Ϊ3306
//	MYSQL *conn;                     //MySQL����ָ�� 
//	MYSQL_RES *res;                  //MySQL����� 
//	MYSQL_ROS row;                   //�б��� 
	
/*-------------------------------------��ʼ������------------------------------------------*/ 
	
	//�������� 
	cleardevice();
	setinitmode(0,-4,0);//���ó�ʼ���������������Ͻ� 
//	initgraph(480,320,INIT_RENDERMANUAL);
	initgraph(-1, -1,INIT_RENDERMANUAL);//��ʼ�����ڣ��˴�ȫ�����ֶ�ˢ�� 
//	initgraph(-1, -1);
	setcaption("���������򻯰�");

	
//	//��ȡ��ǰ���ڵĳ��� 
//	int width=getwidth();
//	int height=getheight();
	
		
	//��������ɫ���� 
//	setbkmode(TRANSPARENT);//����͸��
	setfontbkcolor(RED);
	setcolor(WHITE);
	setfillcolor(RED);
	setfont(40, 0, "����");
	
	
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
	
	backmusic.OpenFile("D:\\mario\\1\\themesong.mp3");
//	xyprintf(200, 220, "%s\n", backmusic.IsOpen() ? "���ִ򿪳ɹ�" : "���ִ�ʧ��");//����Ƿ��	
	backmusic.Play(0);

	
	
	initDisplay1();
	

	
	
//	drawOption(396,376,"������Ϸ"); 
//	drawOption(496,476,"��Ϸ����"); 
//	drawOption(596,576,"�˳���Ϸ"); 

//	fillellipse(410,396,145,35);
//	outtextxy(330,376,"������Ϸ");
//	fillellipse(410,496,145,35);
//	outtextxy(330,476,"��Ϸ����");
//	fillellipse(410,596,145,35);
//	outtextxy(330,576,"�˳���Ϸ");


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

	backmusic.Close();
	
	getch();
	
	closegraph();
	
//	mysql_free_result(res); //�ͷŽ����
//	mysql_close(conn);      //�ر����ӵĴ��� 

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


void drawOption(int k,const char a[])//���ư�ť �����ڴ����ַ��������Լ�const) 
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


int judgeOption(int x,int y)//�ж��������ť 
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


void backGround(const char a[])//����ͼ��ʼ�� 
{
	/*----------------ȷ������ѭ������-------------*/ 
	if (backmusic.GetPlayStatus() == MUSIC_MODE_STOP )
	 {
		backmusic.Play(0);
	}
	/*------------��ʱ��ͼ����ֹ�ڴ�й©-----------*/ 
	delimage(background);
	cleardevice();
	/*----------------���õ�ǰͼƬ-------------*/ 
	int width=getwidth();
	int height=getheight();
	background=newimage(); 
	getZoomImage(background,a,width,height) ;
	putimage(0,0,background);
} 





/*--------------------------------------�˵�����---------------------------------------------------------------*/ 


void initDisplay1()//�˵�һ 
{
	
	/*--------����ͼƬ---------*/ 	
	backGround(DisplayBackground);
	
	/*--------���ư�ť---------*/ 
	drawOption(1,"������Ϸ"); 
	drawOption(2,"��Ϸ����"); 
	drawOption(3,"�˳���Ϸ"); 
	
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


void initDisplay2()//�˵��� 
{

	backGround(DisplayBackground);

	drawOption(1,"ע��/��½"); 
	drawOption(2,"����"); 
	drawOption(3,"����"); 

	

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
			
			switch(judgeOption(xClick,yClick)) 
			{
				case 1: 
				//ע�� Ҳ��Ҫ�ȶ����ݿ���û���ظ����û��� 
				//��½��Ҫ�������ݿ�ȶ��û���������
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


void initDisplay3()//�˵��� 
{
		
	backGround(DisplayBackground);
	
	drawOption(1,"��Ϸ�ؿ�"); 
	drawOption(2,"���÷���"); 
	drawOption(3,"Ŀǰ����"); 
	drawOption(4,"�˳�"); 
	
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
			switch(judgeOption(xClick,yClick)) 
			{
				case 1:
				//	delimage(background);   //��˼����ô��ֹ�ڴ泬�أ���ô��ʱ����ͼƬ����ô�ܹ����ø������ʹ�ã� 
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
					//�������ݵı��棿 
					exit(0); 
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
	
	drawOption(1,"��һ��"); 
	drawOption(2,"�ڶ���"); 
	drawOption(3,"������"); 
	drawOption(4,"����");
	
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
			switch(judgeOption(xClick,yClick)) 
			{
				case 1:
				//	delimage(background);   //��˼����ô��ֹ�ڴ泬�أ���ô��ʱ����ͼƬ����ô�ܹ����ø������ʹ�ã� 
					game1(); 
					break;
				case 2:
				//	delimage(background);
				//ÿ����Ϸ����Ҫ����ԭ�������������µı��� 
					game2();
					break;
				case 3:
					game3();
					break;
				case 4:
					// �˵�����Ҫ����ԭ�������Լ������뱳��ͼƬ�Ĳ��������� 
					
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
	
	drawOption(4,"����"); 
	
	
	setbkmode(TRANSPARENT);
	outtextrect(255,90,800,500,"(1)\tAD�����ƶ�\n\tK��Ծ\n\t�ո���ͣ\n\n(2)\t���治�ᱣ����Ϸ����\n\n(3)\t����ע���½\n\t�����û���Ϸ�ֵܷ�����\n\tҲ�������÷���\n\n(4)\tֻ�й���ǰһ�ز��ܹ���һ��" ); 
	
	
	
	
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


void game1()//��һ�� 
{
	
} 
 
 
void game2()//�ڶ��� 
{

} 
 
 
void game3()//������ 
{
	
} 

 
 
 
/*--------------------------------------�������ݿ�---------------------------------------------------------------*/ 
 
//const char a[] 
void logIn1()//ע��ʱ�û����ȶ� 
{
	
	backGround(GeneralBackground);
	drawOption(4,"����"); 
	
//	setbkmode(TRANSPARENT);
//	sys_edit username;
//	username.create(false);
//	username.move(300,300);
//	int editTexyHeight=16;
//	username.size(editTextHeight*10,4*editTextHeight+10);
//	username.setbgcolor(WHITE);
//	username.setcolor(BLACK);
//	username.setfont(editTextHeight,0,"΢���ź�");
//	
//	int maxLen=60;
//	username.setmaxlen(maxLen);
//	username.visable(true);
//	username.setfocus();//��ȡ���� 
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
//		xyprintf(200,300,"�û�����");
//		if (keystate(key_enter))
//		 {
//			editBox.gettext(50, buff);
//			//����������
//			//flushkey()
//			break;
//		}
//	}
//	
	
	
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
	
} 


//const char a[],const char b[] 
void logIn2()//��½ʱ�û���������ȶ� 
{
	
	backGround(GeneralBackground);
	
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



void resetScore()//���÷��� 
{
	backGround(GeneralBackground);
	
	drawOption(4,"����");
	drawOption(5,"���÷���");
	
	
	setbkmode(TRANSPARENT);
//	xyprintf(,,"����\t��һ��\t�ڶ���\t������\t�ܷ�\n");
//	xyprintf(,,"%s\t%d\t%d\t%d\t%d\n",,,);//�û����������׶εķ��� 
	
	
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


void currentRank()//Ŀǰ���� 
{
	backGround(GeneralBackground);
	
	drawOption(4,"����"); 
	
	
	setbkmode(TRANSPARENT);
//	rectprintf(,,"����\t�ܷ�\t�û���\n");
//	for()
//	{
//		rectprintf(,,"%d\t%d\t%s\n",,,);// 
//	}
	
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
