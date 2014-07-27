#pragma once

// Cell 命令目标
#include<vector>
#include"BitmapEx.h"
extern CBitmapEx backgroud;
extern CBitmapEx snake;
extern	int Map[100][100];//设置地图
#define MAX_W 40 
#define MAX_H 40//地图大小
const extern int size;//地图上的每个单元格大小
using namespace std;
class Cell 
{
protected:
	int sign;//属性标示，用于区分食物、蛇等
	int style;//绘图类型
public:
	
	Cell();
	static float k;//蛇身之间留有一定的空隙
	static int size;//单元格大小
	
	Cell(int,int,int,int);//构造函数
	void init(int a,int b,int col,int s);//初始化
	int x,y;//坐标
	void draw(CDC* pDC);//用CDC作图
	void draw();//用bitmap类作图
	void setstyle(int s){style=s;}//设置绘图类型
	
	//通过move确定能否移动
	bool move(int a,int b);
	bool move(CPoint &p){return move(p.x,p.y);}
	
	bool moveto(CPoint const &p){ return move(p.x-x,p.y-y);}//移动
	void setsign(int c){sign=c;}//设置属性标记


	const Cell & operator=(const Cell & a ){
		x=a.x;y=a.y;sign=a.sign;style=a.style;
		return *this;}//运算符=重载

public:
	CPoint point(){return CPoint(x,y);}//获取坐标
	int getstyle(){return style;}//获取绘图类型
	int getsign(){return sign;}//获取属性
	void setpoint() { Map[x][y] = sign; }//标记
	virtual ~Cell();
};

int getsign(int n,bool head);//n 与sign的转化
int getn(int sign);//n为1是食物，3是墙，后面为其他玩家 第31位标示为身体与头