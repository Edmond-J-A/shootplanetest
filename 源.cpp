#include <iostream>
#include<map>
#include<vector>
#include<cstdlib>
#include <ctime>
#include<graphics.h>
#include <mmsystem.h>
#include<thread>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;
TCHAR s[10],blood[10];
char cmsg[10];
char blanket;
int Game = 1;
int score = 0;
int hard;
int hhard;
MOUSEMSG m, n;
int enemytime;
int speed = 80;
int skin;
int count1 = 0;
int bigbang = 1000;
int gtime =0;
int bosstime= 0, direc = 0;
struct bullet
{
	int x = 0, y = 0, y1 = 0, pi = 0;
	bool ex = 0;
};
struct ene
{
	int x = 0, y = 0, y1 = 0, type = rand() % 15, HP, x1,pi=0,budirec = 0;
	bool ex = 0;

};
struct ex
{
	int x, y, con = 0;
};
struct supply
{
	int x, y, type = rand() % 3;
};
struct Boss
{
	int x, y, type, HP, ex = 0, x1, y1;
};
vector<ex> exlo;
vector<bullet> b;
vector<ene> e;
Boss boss = {260,0,gtime/140000,300};
IMAGE p[11],explosion[9],picskin,playerreset,picenemy,enereset,picenemy2,picboss,bossreset,picenemy3[11], picenemy4[15],enereset2;
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}
void playermusic()
{
	PlaySound(TEXT("bang1.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void bossmove()                                                   
{
		int bossmove = rand() % 2+1;
		if (boss.ex == 1&&direc==1)
		{
			putimage(boss.x1 , boss.y, &bossreset);
			transparentimage(NULL, boss.x, boss.y, &picboss, BLACK);
			boss.x1 = boss.x;
			boss.x+=bossmove;
			if (boss.x >640 )
			{
				direc = 0;
			}
		}
		else if (boss.ex == 1 &&direc == 0)
		{
			putimage(boss.x1, boss.y, &bossreset);
			transparentimage(NULL,boss.x, boss.y, &picboss, BLACK);
			boss.x1 = boss.x;
			boss.x-=bossmove;
			if (boss.x <-70)
			{
				direc = 1;
			}
		}
		else if (boss.ex == 0)
		{
			putimage(boss.x1, boss.y, &bossreset);
		}
		if((gtime-14000+1)%1000==0)
		{
			ene e1;
			e1.ex = 1;
			e1.x = boss.x + 70;
			e1.y = 115;
			e1.type = 1;
			e1.budirec = 0;
			if (e1.type == 1)
			{
				e1.HP = 3;
			}
			else if (e1.type == 0)
			{
				e1.HP = 1;
			}
			e.push_back(e1);
			ene e2;
			e2.ex = 1;
			e2.x = boss.x + 70;
			e2.y = 115;
			e2.type = 1;
			e2.budirec = 1;
			if (e1.type == 1)
			{
				e1.HP = 3;
			}
			else if (e1.type == 0)
			{
				e1.HP = 1;
			}
			e.push_back(e2);
		}
		if ((gtime - 14000+1) % 400 == 0)
		{
			ene e1;
			e1.ex = 1;
			e1.x = boss.x+50;
			e1.y = 115;
			e1.type = 0;
			if (e1.type == 1)
			{
				e1.HP = 3;
			}
			else if (e1.type == 0)
			{
				e1.HP = 1;
			}
			e.push_back(e1);
		}
		if ((gtime - 14000+1) % 500 == 0)
		{
			ene e1;
			e1.ex = 1;
			e1.x = boss.x + 90;
			e1.y = 115;
			e1.type = 0;
			if (e1.type == 1)
			{
				e1.HP = 3;
			}
			else if (e1.type == 0)
			{
				e1.HP = 1;
			}
			e.push_back(e1);
		}
		if ((gtime - 14000 + 1) % 600 == 0)
		{
			ene e1;
			e1.ex = 1;
			e1.x = boss.x + 90;
			e1.y = 115;
			e1.type = 0;
			if (e1.type == 1)
			{
				e1.HP = 3;
			}
			else if (e1.type == 0)
			{
				e1.HP = 1;
			}
			e.push_back(e1);
		}
		if ((gtime - 14000 + 1) %700 == 0)
		{
			ene e1;
			e1.ex = 1;
			e1.x = boss.x + 90;
			e1.y = 115;
			e1.type = 0;
			if (e1.type == 1)
			{
				e1.HP = 3;
			}
			else if (e1.type == 0)
			{
				e1.HP = 1;
			}
			e.push_back(e1);
		}
		Sleep(1);
}
void bosshit()
{
	for (int k = 0; k < b.size(); k++)
	{
			if (boss.x1<= b[k].x - 1 && b[k].x - 1 <= boss.x1 + 140|| boss.x1  <= b[k].x + 1 && b[k].x + 1 <= boss.x1 +140)
			{
				if (boss.y  <= b[k].y - 3 && b[k].y - 3 <= boss.y + 115)
				{
					b[k].ex = 0;
					boss.HP--;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
	}
}
void bossdie()
{
	if (boss.HP == 0)
	{
		boss.ex = 0;
		ex temp[5] = { { boss.x1 + 140,boss.y +115 },{ boss.x1 ,boss.y + 57 } ,{ boss.x1,boss.y-5 } ,{ boss.x1+140,boss.y -5} ,{ boss.x1 +70,boss.y +57 } };
		for (size_t i = 0; i < 5; i++)
		{
	       exlo.push_back(temp[i]);
		}
		playermusic();
		score+=100;
		if (score % 20 == 0)
		{
			if (hard > 15)
			{
				hard -= 15;
			}
		}Sleep(300);
		bosstime = 0;
		gtime = 14001;
	}
	
}
void enemydie()
{
	for (int k = 0; k < b.size(); k++)
	{
		for (int i = 0; i < e.size(); i++)
		{
			if (e[i].x - 15 <= b[k].x - 1 && b[k].x - 1 <= e[i].x + 15 || e[i].x - 15 <= b[k].x + 1 && b[k].x + 1 <= e[i].x + 15)
			{
				if (e[i].y1 - 10 <= b[k].y1 - 3 && b[k].y1 - 3 <= e[i].y1 + 15)
				{
					b[k].ex = 0;
					e[i].HP--;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
	}
}
void enemy()
{
	if (enemytime == 0)
	{
		ene e1;
		e1.ex = 1;
		e1.x = rand() % 640;
		e1.y = 0;
		if (e1.type!=0)
		{
			e1.HP = 2;
		}
		else if (e1.type == 0)
		{
			e1.HP = 1;
		}
		e.push_back(e1);
		enemytime = rand() % hard;
	}
	else
	{
		enemytime--;
	}
}
void enemove()
{
	for (int i = 0; i < e.size(); i++)
	{
		if (e[i].ex == 1 && e[i].y < 495&&e[i].type!=0)
		{
			putimage(e[i].x - 16, e[i].y1 - 16, &enereset);
			transparentimage(NULL, e[i].x-16, e[i].y-16, &picenemy, BLACK);
			e[i].y1 = e[i].y;
			e[i].y++;
		}
		else if (e[i].ex == 1 && e[i].y >= 495)
		{
			putimage(e[i].x - 16, e[i].y1 - 16, &enereset);
			e.erase(e.begin() + i);
		}
		else if (e[i].ex == 0)
		{

			putimage(e[i].x - 16, e[i].y1 - 16, &enereset);
			e.erase(e.begin() + i);
		}
		else if(e[i].ex&& e[i].type == 0&& e[i].ex == 1 && e[i].y < 495)
		{
			putimage(e[i].x - 16, e[i].y1 - 16, &enereset);
			transparentimage(NULL, e[i].x - 16, e[i].y - 16, &picenemy2, BLACK);
			e[i].y1 = e[i].y;
			e[i].y+=3;
		}

	}
	Sleep(2);

}
void enemove2()
{
	for (int i = 0; i < e.size(); i++)
	{
		if (e[i].ex == 1 && e[i].y < 495 && e[i].type == 1)
		{
			putimage(e[i].x1 - 16, e[i].y1 - 16, &enereset2);
			transparentimage(NULL, e[i].x - 16, e[i].y - 16, &picenemy4[e[i].pi], BLACK);
			e[i].y1 = e[i].y;
			e[i].y++;
			if (boss.ex == 1 && e[i].budirec == 1)
			{
				e[i].x1 = e[i].x;
				e[i].x += 2;
				if (e[i].x >= 500)
				{
					e[i].budirec =0;
				}
			}
			else if (boss.ex == 1 && e[i].budirec == 0)
			{
				e[i].x1 = e[i].x;
				e[i].x -= 1;
				if (e[i].x < 0)
				{
					e[i].budirec = 1;
				}
			}
			if (e[i].pi < 15)
			{
				e[i].pi++;
			}
			else
			{
				e[i].pi = 0;
			}
		}
		else if (e[i].ex == 1 && e[i].y >= 495)
		{
			putimage(e[i].x - 16, e[i].y1 - 16, &enereset);
			e.erase(e.begin() + i);
		}
		else if (e[i].ex == 0)
		{

			putimage(e[i].x - 16, e[i].y1 - 16, &enereset);
			e.erase(e.begin() + i);
		}
		else if (e[i].ex && e[i].type == 0 && e[i].ex == 1 && e[i].y < 495)
		{
			putimage(e[i].x - 16, e[i].y1 - 16, &enereset);
			transparentimage(NULL, e[i].x - 16, e[i].y - 16, &picenemy3[e[i].pi], BLACK);
			e[i].y1 = e[i].y;
			e[i].y += 3;
			if (e[i].pi <11)
			{
				e[i].pi++;
			}
			else
			{
				e[i].pi = 0;
			}
		}

	}

}
void enemusic()
{
	PlaySound(TEXT("bang.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void enezero()
{
	for (int i = 0; i <e.size(); i++)
	{
		if (e[i].HP==0&&e[i].type!=0)
		{
			e[i].ex = 0;
			ex temp = { e[i].x - 32,e[i].y - 32 };
			exlo.push_back(temp);
			enemusic();
			score++;
			if (score % 20 == 0)
			{
				if (hard > 15)
				{
					hard -= 15;
				}
			}
		}
		else if (e[i].HP == 0 && e[i].type == 0)
		{
			e[i].ex = 0;
			ex temp = { e[i].x - 32,e[i].y - 32 };
			exlo.push_back(temp);
			enemusic();
			score+=3;
			if (score % 20 == 0)
			{
				if (hard > 15)
				{
					hard -= 15;
				}
			}
		}
	}
}
void getpic()
{
	closegraph();
	initgraph(750, 750);
	loadimage(NULL, _T("fireball.jmp"), 10, 260);
	for (int i = 0; i < 11; i++)
	{
		getimage(&p[i], 0, 26 * i, 10, 26);
	}
	cleardevice();
	loadimage(NULL, _T("explosion.jmp"), 512, 64);
	for (int i = 0; i < 9; i++)
	{
		getimage(&explosion[i],  64 * i,0, 64, 64);
	}
	cleardevice();
	loadimage(NULL, _T("plane.jmp"), 109, 109);
	getimage(&playerreset,200,200,48,48);
	if (skin == 1)
	{
		getimage(&picskin, 0,0,36, 32);
	}
	else if (skin==2)
	{
		getimage(&picskin, 36, 0,22,48);
	}
	else
	{
		getimage(&picskin, 63,0, 31, 33);
	}
	cleardevice();
	loadimage(NULL, _T("plane4.jmp"), 461,438);
		getimage(&picenemy, 0,0, 33,33);
		getimage(&enereset, 44,44, 33, 33);
		cleardevice();
		loadimage(NULL, _T("plane3.jmp"), 461, 438);
		getimage(&picenemy2, 0, 0, 33, 33);
		cleardevice();
		loadimage(NULL, _T("plane2.png"), 640, 480);
		getimage(&picboss, 500,365,140,115);
		getimage(&bossreset, 0, 0, 140,115);
		getimage(&enereset2, 0, 0, 39,50);
		cleardevice();
		loadimage(NULL, _T("fireball1.jmp"), 20, 520);
		for (int i = 0; i < 11; i++)
		{
			getimage(&picenemy3[i], 0, 52 * i, 20, 52);
		}
		cleardevice();
		loadimage(NULL, _T("BloodBound.jmp"),39, 750);
		for (int i = 0; i < 15; i++)
		{
			getimage(&picenemy4[i], 0, 50 * i, 39,50);
		}
		cleardevice();
	/*	for (int i = 5; i < 15; i++)
		{
			transparentimage(0, 50 * (i-5),&picenemy4[i]);
		}
			setbkcolor(WHITE);

		getchar();
		getchar();
		getchar();
		getchar();
		getchar();
				cleardevice();
		transparentimage(0,0,&picboss);*/
}
void firemusic()
{
	PlaySound(TEXT("shootfire.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void bang()
{
	
	for (int i = 0; i <exlo.size(); i++)
	{
		if (exlo[i].con < 18)
		{
			switch (exlo[i].con)
			{
			case 0:	
			case 1:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[0], BLACK);
				exlo[i].con++;
				break;
			case 2:
			case 3:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[1], BLACK);
				exlo[i].con++;
				break;
			case 4:
			case 5:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[2], BLACK);
				exlo[i].con++;
				break;
			case 6:
			case 7:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[3], BLACK);
				exlo[i].con++;
				break;
			case 8:
			case 9:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[4], BLACK);
				exlo[i].con++;	
				break;
			case 10:
			case 11:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[5], BLACK);
				exlo[i].con++;
				break;
			case 12:
			case 13:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[6], BLACK);
				exlo[i].con++;
				break;
			case 14:
			case 15:
				transparentimage(NULL, exlo[i].x, exlo[i].y, &explosion[7], BLACK);
				exlo[i].con++;
				break;
			case 16:
			case 17:
				putimage(exlo[i].x, exlo[i].y, &explosion[8]);
				exlo[i].con++;
				break;
			

	}
		}
		else
		{
			exlo.erase(exlo.begin() + i);
		}
	}
}
void allenedie()
{
	for (int i = 0; i <e.size(); i++)
	{
		e[i].ex = 0;
		ex temp = { e[i].x - 32,e[i].y - 32 };
		exlo.push_back(temp);
	}
	boss.HP -= 50;
	playermusic();
	bigbang--;
	blanket=NULL;
}
void playerdie()
{
	for (int i = 0; i < e.size(); i++)
	{
		if (e[i].x - 15 <= m.x && m.x <= e[i].x + 15)
		{
			if (e[i].y1 - 10 <= m.y - 15 && m.y - 15 <= e[i].y1 + 15)
			{
				Game = 0;
			}
		}
		if (e[i].x - 15 <= m.x - 15 && m.x - 15 <= e[i].x + 15)
		{
			if (e[i].y1 - 10 <= m.y + 10 && m.y + 10 <= e[i].y1 + 15)
			{
				Game = 0;
			}

		}

		if (e[i].x - 15 <= m.x + 15 && m.x + 15 <= e[i].x + 15)
		{
			if (e[i].y1 - 10 <= m.y + 10 && m.y + 10 <= e[i].y1 + 15)
			{
				Game = 0;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}
}
void playerloc()
{
	if (m.y >= boss.y && m.y <= boss.y + 115 && m.x >= boss.x && m.x <= boss.x + 140)
	{
		Game=0;
	}
}
void shoot()
{
	if (n.mkLButton && count1 % (speed-20) != 0)
	{
		count1++;
	}
	else if (count1 % (speed - 20) == 0 && n.mkLButton)
	{
		bullet b1;
		b1.ex = 1;
		b1.x = n.x;
		b1.y = b1.y1 = n.y - 33;
		b.push_back(b1);
		count1++;
		firemusic();
	}
}
void bulletmove()
{
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i].pi >= 10)
		{
			b[i].pi = 0;
		}
	}
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i].ex && b[i].y > 0)
		{
			putimage(b[i].x - 1, b[i].y1 - 3, &p[10]);
			transparentimage(NULL, b[i].x - 1, b[i].y - 3, &p[b[i].pi], BLACK);
			b[i].y1 = b[i].y;
			b[i].y -= 1;
			b[i].pi++;
		}
		else if (b[i].ex && b[i].y <= 0)
		{
			putimage(b[i].x - 1, b[i].y1 - 3, &p[10]);
			b.erase(b.begin() + i);

		}
		else if (b[i].ex == 0)
		{

			putimage(b[i].x - 1, b[i].y1 - 3, &p[10]);
			b.erase(b.begin() + i);
		}
	}
	Sleep(1);
}
void move()
{
	transparentimage(NULL, m.x - 15, m.y - 16, &picskin, BLACK);
	n = GetMouseMsg();
	putimage(m.x - 15, m.y - 16, &playerreset);
	transparentimage(NULL, n.x-15, n.y-16, &picskin,BLACK);
	m = n;
}
void gaming()
{
	if (MouseHit())
	{
		move();
	}
	if (bigbang!=0&&_kbhit())
	{
		blanket =_getch();
		if (blanket == 32)
		{
			allenedie();
		}
	}
	shoot();
	if (bosstime==1)
	{
	bossdie();
	bosshit();
	playerloc();
	bossmove();
	enemove2();
	_stprintf(blood, _T("%d"),boss.HP);
	outtextxy(610,0,blood);
	}
	else
	{
		enemy();
	enemove();
	}
	bulletmove();
	
	enemydie();
	enezero();
	bang();
	playerdie();
	outtextxy(0, 0, "分数：");
	_stprintf(s, _T("%d"), score);
	outtextxy(47, 0, s);
	outtextxy(0,460, "EX：");
	_stprintf(s, _T("%d"),bigbang);
	outtextxy(44,460, s);
	gtime++;
	if (gtime==14000&&bosstime==0)
	{
		allenedie();
		boss.HP += 50;
		bigbang++;
		bosstime = 1;
		boss.ex = 1;
		
	}
}
void showscore()
{
	playermusic();
	for (int i = 0; i < 9; i++)
	{
		transparentimage(NULL,n.x - 32, n.y - 32, &explosion[i], BLACK);
		Sleep(30);
	}
	closegraph();
	std::cout << "You score is:" << score << endl;
	std::system("pause");
	
}
void start()
{
	cleardevice();
	srand(time(0));
	InputBox(cmsg, 10, "选择皮肤（1-3）");
	sscanf(cmsg, "%d", &skin);
	InputBox(cmsg, 10, "选择难度（1-5）");
	sscanf(cmsg, "%d", &hhard);
	if (hhard > 5)
	{
		hhard = 5;
	}
	hard = 15 * (6 - hhard);
	enemytime = rand() % hard;
	if (hhard == 5)
	{
		speed = 65;
	}
	getpic();
	closegraph();
	initgraph(640, 480);
	m = GetMouseMsg();
	move();	
	settextcolor(WHITE);
	settextstyle(0,0,"");
	Sleep(100);
}
int main()
{
	
	initgraph(640,480);
	loadimage(NULL, _T("picbk.png"),640,480);
	settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	rectangle(195, 245, 440, 300);
	settextstyle(45, 30, "黑体");
	outtextxy(200, 250, "开始游戏");
	while(1)
	{
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		if (!MouseHit)
		{
		}
		else
		{
			m = GetMouseMsg();
			if (m.x > 195 && m.y > 245 && m.x < 440 && m.y < 300)
			{
				rectangle(175, 240, 472, 300);
				settextstyle(54, 36, "黑体");
				outtextxy(180, 245, "开始游戏");
				if (m.x > 240 && m.y > 250 && m.x < 400 && m.y < 280 && m.mkLButton)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
			
		}
			
	}
	start();
	while (Game)
	{
		gaming();
	
	}
	showscore();
	return 0;
}
