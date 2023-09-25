#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

void DrawPlayer(int x, int y)
{
	bar(x-5, y-30, x+5, y+30);
}

void DrawBall(int x, int y, int r)
{
	fillellipse(x, y, r, r);
}

void WriteScore(int pts1, int pts2)
{
	setcolor(4);
	settextstyle(0, 0, 5);
	char s[3];
	snprintf(s,sizeof(s), "%d", pts2);
	outtextxy(375, 30, s);
	setcolor(1);
	settextstyle(0, 0, 5);
	snprintf(s,sizeof(s), "%d", pts1);
	outtextxy(230, 30, s);
}

void DrawLine()
{
	setfillstyle(1, 4);
	bar(320, 10, 330, 60);
	bar(320, 110, 330, 160);
	bar(320, 210, 330, 260);
	bar(320, 310, 330, 360);
	bar(320, 410, 330, 460);
	
	setfillstyle(1, 1);
	bar(310, 10, 320, 60);
	bar(310, 110, 320, 160);
	bar(310, 210, 320, 260);
	bar(310, 310, 320, 360);
	bar(310, 410, 320, 460);
}

int main()
{
	int xp1 = 20, yp1 = 240, xp2 = 620, yp2 = 240;
	int pts1 = 0, pts2 = 0, b = 0;
	int xb = 320, yb = 240, vx = 4, vy = 4, r = 10,  pv = 5;
	bool running = true, menue = true;
	
	srand(time(NULL));
	initwindow(640, 480);
	
	while(running)
	{
		setvisualpage(b);
		setactivepage(1-b);
			
		cleardevice();
			
		if(pts2 >= 15)
		{
			setbkcolor(12);
			char s[] = "The victor is:";
			char s2[] = "RED";
			char s3[] = "Congratulations!";
			
			setcolor(0);
			settextstyle(0, 0, 2);
			outtextxy(160, 210, s);
			setcolor(4);
			settextstyle(0, 0, 4);
			outtextxy(240, 230, s2);
			setcolor(0);
			settextstyle(0, 0, 2);
			outtextxy(160, 270, s3);
			
			if(GetAsyncKeyState(VK_RETURN))
			{
				menue = true;
				pts2 = 0;
				pts1 = 0;
			}
			else if(GetAsyncKeyState(VK_ESCAPE))
				running = false;
		}
		else if(pts1 >= 15)
		{
			setbkcolor(9);
			char s[] = "The victor is:";
			char s2[] = "BLUE";
			char s3[] = "Congratulations!";
			
			setcolor(0);
			settextstyle(0, 0, 3);
			outtextxy(160, 210, s);
			setcolor(1);
			settextstyle(0, 0, 4);
			outtextxy(240, 230, s2);
			setcolor(0);
			settextstyle(0, 0, 3);
			outtextxy(160, 270, s3);
			
			if(GetAsyncKeyState(VK_RETURN))
			{
				menue = true;
				pts2 = 0;
				pts1 = 0;
			}
			else if(GetAsyncKeyState(VK_ESCAPE))
				running = false;
		}
		else if(menue)
		{
			setbkcolor(13);
			char s[] = "PONG";
			char s2[] = "To start the game press enter!";
			char s3[] = "Press esc if you wish to quit.";
			char s4[] = "(works in game too)";
			
			settextstyle(0, 0, 5);
			setcolor(0);
			outtextxy(250, 120, s);
			settextstyle(0, 0, 2);
			outtextxy(100, 240, s2);
			outtextxy(100, 270, s3);
			outtextxy(150, 300, s4);
			
			if(GetAsyncKeyState(VK_RETURN))
				menue = false;
			else if(GetAsyncKeyState(VK_ESCAPE))
				running = false;
		}
		else
		{
			setbkcolor(11);
			DrawLine();
			WriteScore(pts1, pts2);
			
			xb += vx;
			yb += vy;
			
			if(GetAsyncKeyState(0x57) & 0x8000 and yp1-30 >=0)
			{
				yp1 -= pv;
			}
			else if(GetAsyncKeyState(0x53) & 0x8000 and yp1+30 <= getmaxy())
			{
				yp1 += pv;
			}
			
			if(GetAsyncKeyState(VK_UP) and yp2-30 >=0)
			{
				yp2 -= pv;
			}
			else if(GetAsyncKeyState(VK_DOWN) and yp2+30 <= getmaxy())
			{
				yp2 += pv;
			}
			
			setfillstyle(1, 1);
			DrawPlayer(xp1, yp1);
			setfillstyle(1, 4);
			DrawPlayer(xp2, yp2);
			
			if(xb > 320)
			{
				setcolor(1);
				setfillstyle(1, 1);
			}
			else
			{
				setcolor(4);
				setfillstyle(1, 4);
			}
			DrawBall(xb, yb, r);
			
			if(xb+r > getmaxx())
			{
				pts1++;
				xb = 320;
				vx *= (rand()%2)-1;
				if(vx == 0)
				{
					vx = -4;
				}
			}
			else if(xb+r < 0)
			{
				pts2++;
				xb = 320;
				vx *= (rand()%2)-1;
				if(vx == 0)
				{
					vx = 4;
				}
			}
			
			if(yb+r >= getmaxy() or yb+r <= 7)
			{
				vy = -vy;
				yb += vy;
			}
			
			if(xb-r >= xp1-5 and xb-r <= xp1+5 and yb+r >= yp1-30 and yb+r <= yp1+30)
			{
				vx = -vx;
				xb += vx;
			}
			else if(xb+r >= xp2-5 and xb+r <= xp2+5 and yb+r >= yp2-30 and yb+r <= yp2+30)
			{
				vx = -vx;
				xb += vx;
			}
			
			if(GetAsyncKeyState(VK_ESCAPE))
				running = false;
		}
		
		if(b == 0){ b = 1; }
		else{ b = 0; }
		delay(10);
	}
	
	closegraph();
	return 0;
}