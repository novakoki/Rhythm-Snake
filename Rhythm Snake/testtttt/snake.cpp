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
//�ߵ��˶�
int Snake::run()
{
	int r=0;
	POINT TEM=head.point();//��ȡ��ͷ����
	int direct =cur_dir;
	old_dir=cur_dir;
	//���û�Ե�ʳ��
	if(growth==0)
	{
		wipepoint(body[end].point());//������β�ڵ�ͼ�ϵı��
		body[end].moveto(head.point());//��β������ͷ��
		end--;//����β
		if(end==-1) end=body.size()-1;
	}
	//�Ե�ʳ���
	else
	{
		growth--;
		int tt=(end+1)%body.size();
		body.insert(body.begin()+tt,head);//������β��������
		body[tt].setsign(getsign(n,0));
		end=tt-1;
		if(end==-1) end=body.size()-1;
	}
	
	//β������������ͼ�㣬����endΪ���ĵ�
	//����������仯
	if(direct==UP)
		TEM.y--;
	if(direct==DOWN)
		TEM.y++;
	if(direct==LEFT)
		TEM.x--;
	if(direct==RIGHT)
		TEM.x++;
	//�ж������˶����Ƿ�ȫ
	int y=Map[TEM.x][TEM.y];
	if(!ifsafe(TEM))
	{ if(y==0) return WALL;
		return y;}
	else if(y==1)
	{eat();
	grow(1);
	r=1;
	}
	//�ı���ͷ����
	head.x=TEM.x;head.y=TEM.y;
	head.setpoint();
	head.setstyle(direct);

	

	//�ı���������
	for(int i=0;i<body.size();i++){
		body[i].setsign(getsign(n,0));
		body[i].setpoint();
		body[i].setstyle(5);
}

return  r;
}

//���÷���
bool Snake::SETDIR(int direct){
	switch(old_dir){
	case UP:if(direct==DOWN) return false;break;
	case DOWN:if(direct==UP) return false;break;
	case LEFT:if(direct==RIGHT) return false;break;	
	case RIGHT:if(direct==LEFT) return false;break;
	}//��ֹ����
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

// ���ߺ�		
// 0 0 0  ��
// 1 1 1  ��
// 1 2 4 8 ����

//��ʼ��
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

//����
//��bitmap�໭
void Snake::draw(){
	head.draw();
	int as=body.size();
	
	while(as--)
		body[as].draw();
}
//�ɰ汾CDC����
void Snake::draw(CDC* pDC){
	head.draw(pDC);
	int as=body.size();
	while(as--)
		body[as].draw(pDC);
}
Snake::~Snake(){
	Map[head.x][head.y]=0;//ʬ����ʳ��
	for(int i=0;i<body.size();i++)
		Map[body[i].x][body[i].y]=0;
}


//�ж��Ƿ����ϰ�
bool ifsafe(POINT p){
	if(p.x<0||p.x>=MAX_W) return false;
	if(p.y<0||p.y>=MAX_H) return false;
	if(Map[p.x][p.y]>1||Map[p.x][p.y]<0)
		return false;
	return true;
}
void Snake::d_go(int x,int y){//ֻ�������еĿͻ���
	POINT TEM=head.point();//��ȡ��ͷ����
	//���û�Ե�ʳ��
	if(growth==0)
	{
		wipepoint(body[end].point());//������β�ڵ�ͼ�ϵı��
		body[end].moveto(head.point());//��β������ͷ��
		end--;//����β
		if(end==-1) end=body.size()-1;
	}
	//�Ե�ʳ���
	else
	{
		growth--;
		int tt=(end+1)%body.size();
		body.insert(body.begin()+tt,head);//������β��������
		body[tt].setsign(getsign(n,0));
		end=tt-1;
		if(end==-1) end=body.size()-1;
	}
	
	//β������������ͼ�㣬����endΪ���ĵ�
	//����������仯
	int dir=cur_dir;
	if(x>head.x) dir=RIGHT;
	if(x<head.x) dir=LEFT;
	if(y<head.y) dir=UP;
	if(y>head.y) dir=DOWN;

	//�ı���ͷ����
	head.x=x;head.y=y;
	head.setpoint();
	head.setstyle(dir);
	//�ı���������
	for(int i=0;i<body.size();i++){
		body[i].setsign(getsign(n,0));
		body[i].setpoint();
		body[i].setstyle(5);
}



}

//void d_go(int dir,Snake& the){
//	POINT TEM=head.point();//��ȡ��ͷ����
//	//���û�Ե�ʳ��
//	if(growth==0)
//	{
//		wipepoint(body[end].point());//������β�ڵ�ͼ�ϵı��
//		body[end].moveto(head.point());//��β������ͷ��
//		end--;//����β
//		if(end==-1) end=body.size()-1;
//	}
//	//�Ե�ʳ���
//	else
//	{
//		growth--;
//		int tt=(end+1)%body.size();
//		body.insert(body.begin()+tt,head);//������β��������
//		body[tt].setsign(getsign(n,0));
//		end=tt-1;
//		if(end==-1) end=body.size()-1;
//	}
//	
//	//β������������ͼ�㣬����endΪ���ĵ�
//	//����������仯
//	if(dir==UP)
//		TEM.y--;
//	if(dir==DOWN)
//		TEM.y++;
//	if(dir==LEFT)
//		TEM.x--;
//	if(dir==RIGHT)
//		TEM.x++;
//
//	//�ı���ͷ����
//	head.x=TEM.x;head.y=TEM.y;
//	head.setpoint();
//	head.setstyle(dir);
//	//�ı���������
//	for(int i=0;i<body.size();i++){
//		body[i].setsign(getsign(n,0));
//		body[i].setpoint();
//		body[i].setstyle(5);
//}
//
//
//
//}