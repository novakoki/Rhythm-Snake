// Unit.cpp : 实现文件
//

#include "stdafx.h"
#include<algorithm>
#include "Unit.h"
using namespace std;
#define START_X 0
#define START_Y 0
CBitmapEx backgroud;
// Cell
CBitmapEx snake;
CPoint pos[10];//用来分块导入蛇的图像
const  int size=20;//方格大小
int Map[100][100];
float Cell::k=1;
int Cell::size;

//初始化单元格
Cell::Cell():x(11),y(40),sign(0),style(7)
{
	if(snake.GetWidth()<10){
		//snake.Load("snake.bmp");
		//backgroud.Create(1000,800);
		//backgroud.Load("snake.bmp");
		pos[0].x=120;pos[0].y=120;
		pos[1].x=0;pos[1].y=0;
		pos[2].x=40;pos[2].y=0;
		pos[3].x=120;pos[3].y=0;
		pos[4].x=80;pos[4].y=0;
		pos[5].x=80;pos[5].y=120;
	}
}

Cell::Cell(int a,int b,int col,int s){
		init(a,b,col,s);
	}
void Cell::init(int a,int b,int col,int s){
x=a;y=b;sign=col;style=s;
}
Cell::~Cell()
{
	//this->setstyle(0);
}


// Cell 成员函数
/*
style :
蛇头: 1 2 3 4
食物：0
*/
void Cell::draw(CDC* pDC){
	pDC->Rectangle(x*size,y*size,x*size+k*size,y*size+k*size);
}

void Cell::draw(){
	snake.Load(L"snake.bmp");//导入蛇的图像
	CBitmapEx& tem=snake;
	pos[0].x = 120; pos[0].y = 120;
	pos[1].x = 0; pos[1].y = 0;
	pos[2].x = 40; pos[2].y = 0;
	pos[3].x = 120; pos[3].y = 0;
	pos[4].x = 80; pos[4].y = 0;
	pos[5].x = 80; pos[5].y = 120;
	//tem.Pixelize(getn(sign));
	backgroud.DrawTransparent(START_X+x*size,START_Y+y*size,size,size,tem,pos[style].x,pos[style].y,size*2,2*size,100,RGB(255,255,255));
	//switch(10){
	//case 1://color
	//	backgroud.Draw(START_X+x*size,START_Y+y*size,size,size,tem,pos[1].x,pos[1].y,size*2,2*size,100);break;
	//case 2:
	//	backgroud.Draw(START_X+x*size,START_Y+y*size,size,size,tem,pos[2].x,pos[2].y,size*2,2*size,100);break;
	//case 3:
	//	backgroud.Draw(START_X+x*size,START_Y+y*size,size,size,tem,pos[3].x,pos[3].y,size*2,2*size,100);break;
	//case 4:
	//	backgroud.Draw(START_X+x*size,START_Y+y*size,size,size,tem,pos[4].x,pos[4].y,size*2,2*size,100);break;
	//case 0:
	//	backgroud.Draw(START_X+x*size,START_Y+y*size,size,size,tem,pos[0].x,pos[0].y,size*2,2*size,80);break;
	//case 5://body
	//	backgroud.Draw(START_X+x*size,START_Y+y*size,size,size,tem,pos[5].x,pos[5].y,size*2,2*size,100);break;
	//}
}

//判断能否移动
bool Cell::move(int a,int b){
if(x+a<0||x+a>MAX_W||y+b<0||y+b>MAX_H)
	return 0;
	x+=a;y+=b;
return true;
}
//n 与sign的转化
int getsign(int n,bool head){
	if(head)return 1+(1<<n)+(1<<31);
	return 1+(1<<n);}
//n为1是食物，3是墙，后面为其他玩家 第31位标示为身体与头
int getn(int sign){
for(int i=2;i<31;i++)
	if((sign>>i)&1)
		return i;
return 0;
}
void drawrec(CDC* pDC,POINT& p,int style){
	switch(style)
{
	default:
		pDC->Rectangle(p.x*size,p.y*size,(p.x+1)*size,(p.y+1)*size);}
}