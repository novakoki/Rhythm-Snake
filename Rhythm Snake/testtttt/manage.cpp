#include "stdafx.h"
#include "manage.h"
#include"net.h"

manage::manage(void)
{
	user=robot=0;
	Cell::size=20;
	memset(Map,0,sizeof(Map));
}


manage::~manage(void)
{
}
int manage::login(string name){
	int n=2;while(n<31){
		if((user&(1<<n))==0){//空缺的用户
		control[n]=new Snake;
		control[n]->init(1+n*2,5,n);
		control[n]->name=name;user=user|(1<<n);
		return n;
		}n++;
	}
	return 0;//失败 
}
bool manage::setdir(int direct,int id){
	if(! (user&(1<<id))) return false;
	if(direct==5) 
		robot=robot^(1<<id);//机器人控制转化
	//else
	//if(robot&(1<<id))//机器
	//{
	//	return 0;
	//}
	else{//用户
	
		return control[id]->SETDIR(direct);
	}
	return 1;
}

bool manage::go(){
	int t=1<<2;int id=2;char u[8]={0};flash a;
while(id<31){
	if(t&user)
	if(only&&robot&(1<<id))//机器
	{	
		man.control=control[id];
		int dir = man.AI_c();
		setdir(dir,id);
		man.control->SETDIR(dir);
		u[0]=id;
		int w = man.control->run();

	switch (w)
	{
		//case 1:eat();break;
	case 0:break;
	case 1:break;//食物
	case WALL:	leave(id); 
		u[0]=id;
		a.n=2;
	a.DoModal();
	dlg.Create(IDD_NET);
	dlg.ShowWindow(SW_SHOW);
		return false; break;//撞墙死
	default:
		a.DoModal();
	dlg.Create(IDD_NET);
	dlg.ShowWindow(SW_SHOW);
		leave(id);u[0]=id;
		//dlg.sendmessage('5',u);
		return false;
	}
	}
	else//网络部分
	
	{	
		u[0]=id+'0';
		//::Sleep(10);
		/*if(dlg.server&&!only)
		dlg.sendmessage('7',u);*/
		//::Sleep(20);
		int w=control[id]->run();
		//*****************************************网络部分添加
		//dlg.sendmessage();
		char tt[4] = { 0 };
		tt[0] =id+'0';
		tt[1]='0'+control[id]->head.x;
		tt[2]='0'+control[id]->head.y;
		//m.setdir(dir,id);
		dlg.sendmessage('9',tt);

	//*****************************************
		Sleep(20);
		switch (w)
		{
			//case 1:eat();break;
		case 0:break;
		case 1:
			dlg.sendmessage('7',u);
			break;//食物
		case WALL:	
			leave(id);
			u[0]=id+'0';
			if(!only)
				dlg.sendmessage('5',u);//死亡
			 return false; //撞墙死
		default:
			leave(id);
			u[0]=id+'0';
			if(!only)
		dlg.sendmessage('5',u);
			if (w&(1 << id)){ ; }//自杀
			else if (t<0){ ; }//和别人一起死
			else {
				int kill = getn(w);

			}//被kill杀
			return false;
		}
	}
	id++;t=t<<1;
}
	return 1;
}
void manage::draw(CDC* pDC){
int id=1<<2;int t=2;
while(t<31){
	if(id&user) control[t]->draw(pDC);
	t++;id=id<<1;
}
}

void manage::draw(){
	food.setstyle(0);
	food.draw();
	int id=1<<2;int t=2;
while(t<31){
	if(id&user) 
		control[t]->draw();
	t++;id=id<<1;
}

}
void manage::leave(int id){
	user=user&(~(1<<id));
	robot=robot^(1<<id);


	delete control[id];

}
void eat(){
	//grow()
int x,y;
if(dlg.server||only)
while(1){
x=rand()%30;
y=rand()%30;//HERE
char t[3]={0};t[0]=x;t[1]=y;
if(Map[x][y]==0){
	if(dlg.server)
	dlg.sendmessage('8',t);
	food.x=x;
	food.y=y;
	setfood(food.point());
	break;
}
}
}