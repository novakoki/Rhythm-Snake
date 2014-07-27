// snake1.h: interface for the snake class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAKE1_H__EF6B659F_B2D5_4482_81CD_31CC77C0D814__INCLUDED_)
#define AFX_SNAKE1_H__EF6B659F_B2D5_4482_81CD_31CC77C0D814__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<vector>
#include"Unit.h"
#define LEFT 1
#define RIGHT 2
#define DOWN 3
#define UP 4
#define FOOD 1//食物标记
#define SNAKE1 5
#define SNAKE2 9//蛇的标记 31位表示蛇头
#define WALL 2//墙的标记 
//操作表示

Cell extern food;
using namespace std;
//封装所有动作为：用户，方向；系统：绘图，积分
class Snake
{
protected:	
void wipepoint(POINT &p){Map[p.x][p.y]=0;}//在地图上擦去标记
int growth;//蛇身增长量
int cur_dir;//现在的方向
int old_dir;//之前的方向
bool dead(POINT& p);
void drawrec(CDC* pDC,POINT& p,int style);
public:
	
	Cell head;//蛇头
	int end;//蛇的末尾
	vector<Cell> body;//蛇身
	int n;//标记
	void grow(int g){growth+=g;}//增长
	int run();//蛇的运动
	void init(int x,int y,int s);//初始化
	void draw(CDC* pDC);
	void draw();

	bool SETDIR(int direct);//设置方向

	Snake(){}
	Snake(int x,int y,int s);//构造函数
	~Snake();
	//用户数据
	string name;

	int scores;//获得的分数
	//
	 void d_go(int x,int y);
};
void setfood(POINT);
bool ifsafe(POINT p);//判断死亡
void eat();//吃食物
#endif // !defined(AFX_SNAKE1_H__EF6B659F_B2D5_4482_81CD_31CC77C0D814__INCLUDED_)
