// snake.cpp: implementation of the snake class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "snake.h"
#include"net.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cell  food;
 void	 setfood(POINT p){
		//Map[food.x][food.y]=0;
		Map[p.x][p.y]=1;
		food.x=p.x;food.y=p.y;
	}
//蛇的运动
int Snake::run()
{
	int r=0;
	POINT TEM=head.point();//获取蛇头坐标
	int direct =cur_dir;
	old_dir=cur_dir;
	//如果没吃到食物
	if(growth==0)
	{
		wipepoint(body[end].point());//擦掉蛇尾在地图上的标记
		body[end].moveto(head.point());//蛇尾顶到蛇头上
		end--;//新蛇尾
		if(end==-1) end=body.size()-1;
	}
	//吃到食物后
	else
	{
		growth--;
		int tt=(end+1)%body.size();
		body.insert(body.begin()+tt,head);//把新蛇尾插入向量
		body[tt].setsign(getsign(n,0));
		end=tt-1;
		if(end==-1) end=body.size()-1;
	}
	
	//尾部处理：擦除地图点，重置end为最后的点
	//方向与坐标变化
	if(direct==UP)
		TEM.y--;
	if(direct==DOWN)
		TEM.y++;
	if(direct==LEFT)
		TEM.x--;
	if(direct==RIGHT)
		TEM.x++;
	//判断这样运动后是否安全
	int y=Map[TEM.x][TEM.y];
	if(!ifsafe(TEM))
	{ if(y==0) return WALL;
		return y;}
	else if(y==1)
	{eat();
	grow(1);
	r=1;
	}
	//改变蛇头属性
	head.x=TEM.x;head.y=TEM.y;
	head.setpoint();
	head.setstyle(direct);

	

	//改变蛇身属性
	for(int i=0;i<body.size();i++){
		body[i].setsign(getsign(n,0));
		body[i].setpoint();
		body[i].setstyle(5);
}

return  r;
}

//设置方向
bool Snake::SETDIR(int direct){
	switch(old_dir){
	case UP:if(direct==DOWN) return false;break;
	case DOWN:if(direct==UP) return false;break;
	case LEFT:if(direct==RIGHT) return false;break;	
	case RIGHT:if(direct==LEFT) return false;break;
	}//防止回走
cur_dir=direct;
return true;
}


/*bool Snake::dead(POINT& p){
if(p.x<0||p.x>=30)
return true;
if(p.y<0||p.y>=30)
return true;
if(Map[p.x][p.y]&2)
		return true; 
return false;
}*/

// 物蛇号		
// 0 0 0  无
// 1 1 1  有
// 1 2 4 8 数字

//初始化
Snake::Snake(int x,int y,int s){
	init(x,y,s);
	}
void Snake::init(int x,int y,int s)
{
	scores=0;
	n=s;
	head.init(x,y,getsign(n,1),DOWN);
	growth=0;end=1;

	cur_dir=DOWN;old_dir=DOWN;

	Cell t;
	t.init(x,y-1,getsign(n,0),5);
	body.push_back(t);
	t.init(x,y-2,getsign(n,0),5);
	body.push_back(t);

	head.setpoint();
	body[0].setpoint();
	body[1].setpoint();

}

//画蛇
//用bitmap类画
void Snake::draw(){
	head.draw();
	int as=body.size();
	
	while(as--)
		body[as].draw();
}
//旧版本CDC画法
void Snake::draw(CDC* pDC){
	head.draw(pDC);
	int as=body.size();
	while(as--)
		body[as].draw(pDC);
}
Snake::~Snake(){
	Map[head.x][head.y]=0;//尸体变成食物
	for(int i=0;i<body.size();i++)
		Map[body[i].x][body[i].y]=0;
}


//判断是否有障碍
bool ifsafe(POINT p){
	if(p.x<0||p.x>=MAX_W) return false;
	if(p.y<0||p.y>=MAX_H) return false;
	if(Map[p.x][p.y]>1||Map[p.x][p.y]<0)
		return false;
	return true;
}
void Snake::d_go(int x,int y){//只给网络中的客户机
	POINT TEM=head.point();//获取蛇头坐标
	//如果没吃到食物
	if(growth==0)
	{
		wipepoint(body[end].point());//擦掉蛇尾在地图上的标记
		body[end].moveto(head.point());//蛇尾顶到蛇头上
		end--;//新蛇尾
		if(end==-1) end=body.size()-1;
	}
	//吃到食物后
	else
	{
		growth--;
		int tt=(end+1)%body.size();
		body.insert(body.begin()+tt,head);//把新蛇尾插入向量
		body[tt].setsign(getsign(n,0));
		end=tt-1;
		if(end==-1) end=body.size()-1;
	}
	
	//尾部处理：擦除地图点，重置end为最后的点
	//方向与坐标变化
	int dir=cur_dir;
	if(x>head.x) dir=RIGHT;
	if(x<head.x) dir=LEFT;
	if(y<head.y) dir=UP;
	if(y>head.y) dir=DOWN;

	//改变蛇头属性
	head.x=x;head.y=y;
	head.setpoint();
	head.setstyle(dir);
	//改变蛇身属性
	for(int i=0;i<body.size();i++){
		body[i].setsign(getsign(n,0));
		body[i].setpoint();
		body[i].setstyle(5);
}



}

//void d_go(int dir,Snake& the){
//	POINT TEM=head.point();//获取蛇头坐标
//	//如果没吃到食物
//	if(growth==0)
//	{
//		wipepoint(body[end].point());//擦掉蛇尾在地图上的标记
//		body[end].moveto(head.point());//蛇尾顶到蛇头上
//		end--;//新蛇尾
//		if(end==-1) end=body.size()-1;
//	}
//	//吃到食物后
//	else
//	{
//		growth--;
//		int tt=(end+1)%body.size();
//		body.insert(body.begin()+tt,head);//把新蛇尾插入向量
//		body[tt].setsign(getsign(n,0));
//		end=tt-1;
//		if(end==-1) end=body.size()-1;
//	}
//	
//	//尾部处理：擦除地图点，重置end为最后的点
//	//方向与坐标变化
//	if(dir==UP)
//		TEM.y--;
//	if(dir==DOWN)
//		TEM.y++;
//	if(dir==LEFT)
//		TEM.x--;
//	if(dir==RIGHT)
//		TEM.x++;
//
//	//改变蛇头属性
//	head.x=TEM.x;head.y=TEM.y;
//	head.setpoint();
//	head.setstyle(dir);
//	//改变蛇身属性
//	for(int i=0;i<body.size();i++){
//		body[i].setsign(getsign(n,0));
//		body[i].setpoint();
//		body[i].setstyle(5);
//}
//
//
//
//}