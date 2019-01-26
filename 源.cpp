/****************************************************
	文件名称：源.cpp
	文件描述：《黑客帝国》字符雨屏保
	编译环境：VS2008-VS2017   VC++6.0   VC++2010
	最后修改：
		<2018年2月22日>	<创建工程>	<Aloner>
****************************************************/

//===================包含文件========================
#include<graphics.h>
#include<time.h>
#include<mmsystem.h>
#include<conio.h>
//#include<stdlib.h>

//====================编译预处理======================
#pragma comment(lib,"winmm.lib")
#define WINDOW_HEIGHT	1600
#define WINDOW_WIDTH	800
#define LMAX			22		//60			//字符最大长度
#define LMIN			8		//55			//字符最小长度
#define Llmax			12						//字符纯绿的最长长度
#define Llmin			6						//字符纯绿的最短长度
#define size			16						//字符宽度
#define lie				(WINDOW_HEIGHT/size)	//字符列数
#define sounds			100					//每打一个字符的时间

//========================函数声明=======================
char CreatChar();
VOID Draw(char zifu);
VOID Drawhou(char zifu);
VOID Fade(char zifu);

//========================全局变量=====================
TCHAR yu[60];
int cnt = 0;
int se=200;
int L = 0;
int X=1, Y=1;
int Length=1;
int Lliang = 6;
int lieY[lie] = { 0 };							//每一列字符开始的高度   不变
int liey[lie] = { 0 };							//每一列字符运行的高度	 改变
int sum = 0;
char ALLzifu[lie][LMAX] = { 0 };				//存储所有字符的数组
int o;
//===========================主函数======================
int main()
{
	char zhi;
	initgraph(WINDOW_HEIGHT, WINDOW_WIDTH);
	PlaySound(L"flower dance.wav",NULL,SND_LOOP|SND_FILENAME|SND_ASYNC);
	srand((unsigned int)time(NULL));

	LOGFONT g;
	gettextstyle(&g);						 // 获取当前字体设置
	g.lfHeight = size;						 // 设置字体高度为 48
	g.lfWidth = size;
	_tcscpy_s(g.lfFaceName, _T("楷体"));	// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	g.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿
	settextstyle(&g);

	do {
		for (int i = 0; i < lie; i++)
		{
			X = i*size;
			Y = rand() % WINDOW_WIDTH / size*size;
			lieY[i] = Y;
			liey[i] = lieY[i];
			zhi = CreatChar();
			ALLzifu[i][0] = zhi;
			Draw(zhi);
		}
		Sleep(sounds);
		for (int i = 0; i < lie; i++)
		{
			X = i*size;
			Y = liey[i];
			zhi = ALLzifu[i][0];
			Drawhou(zhi);
		}

		do {
			Length = rand() % LMAX + 1;
		} while (Length < LMIN);

		do {
			Lliang = rand() % Llmax;
		} while (Lliang<Llmin);

		for (int j = 1; j <= Length; j++)
		{ 
			//超过Lliang后颜色渐变
			if (j >= Lliang)
			{
				for (int i = 0; i < lie; i++)
				{
					X = i*size;
					for (int k = 0; j - Lliang >= k; k++)
					{
						Y = lieY[i] - k* size;
						zhi = ALLzifu[i][j - Lliang - k];
						for (se = 200, L = 0; se > 0 && L<k; L++)
							se -= 50;
						settextcolor(RGB(0, se, 0));
						Fade(zhi);
					}
					lieY[i] += size;
				}
			}
			for (int i = 0; i < lie; i++)
			{
				X = i*size;
				liey[i] += size;
				Y = liey[i];

				zhi = CreatChar();
				Draw(zhi);
/*
if (Y >= WINDOW_WIDTH)
{
settextcolor(RGB(0, 0, 0));
zhi = 0;
for (o =0;o<WINDOW_WIDTH/size;o++ )
{
Y = o*size;
Fade(zhi);
}
}
*/
				ALLzifu[i][j] = zhi;
			}
			Sleep(sounds);
			for (int i = 0; i < lie; i++)
			{
				X = i*size;
				Y = liey[i];
				zhi = ALLzifu[i][j];
				Drawhou(zhi);
			}
		}
		cleardevice();
	} while (1);


	getch();
	return 0;
}

//产生随机字符
char CreatChar()
{
	char zifu;
	while (1) 
	{
		zifu = rand() % 123;
		if (zifu >= 97 || (zifu > 64 && zifu < 91))
		{
		//	X = rand() % WINDOW_HEIGHT / size*size;
		
			break;
		}
	} 
		return zifu;
}

VOID Draw(char zifu)
{
	//setbkmode(0);
	settextcolor(RGB(255, 255, 255));

	yu[1] = zifu;
	outtextxy(X, Y, yu[1]);
}

VOID Drawhou(char zifu)
{
	yu[30] = zifu;
	settextcolor(RGB(0,255,0));
	outtextxy(X, Y, yu[30]);
}

//字符雨尾缓慢消失
VOID Fade(char zifu)
{
	yu[45] = zifu;
	outtextxy(X, Y, yu[45]);
}