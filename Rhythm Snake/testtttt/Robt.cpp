// Robt.cpp: implementation of the CRobt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mysnake.h"
#include "Robt.h"
#include<math.h>
#include<algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool rout[30][30];
CPoint dir[5];
int cal(POINT cur,POINT aim,int l,int f);
int cal_c(POINT cur,POINT aim,int l,int f);

CRobt::CRobt()
{
level=2;control=0;

}

CRobt::~CRobt()
{

}
int dis(CPoint a,CPoint b){
return abs(a.x-b.x)+abs(a.y-b.y);
}
bool comp(POINT& a,POINT& b){
return a.y>b.y;
}
int CRobt::AI_c(){
	dir[LEFT]=CPoint(-1,0);
dir[RIGHT]=CPoint(1,0);
dir[DOWN]=CPoint(0,1);
dir[UP]=CPoint(0,-1);
	
	CPoint cur=control->head.point();
	POINT sum[4];//方向与安全值绑定
	float k=1;
	for(int i=0;i<4;i++)
	{sum[i].x=i+1;
	if(abs(dis(cur,food.point()))>abs(dis(cur+dir[i+1],food.point())))//下一步更接近食物
		k=10;
	else
		k=0.5;
	sum[i].y=cal_c(cur+dir[i+1],food.point(),level,1)*k;//食物的影响力
	k;}
	std::sort(sum,sum+4,comp);//对安全值排序
	int p=0;
	for(int i=0;i<4;i++)
	{sum[i].y*=(4-i);//扩大差距
	p+=sum[i].y;
	}
	int tem;
	if(p==0) return 1;//无路可走
	tem=rand()%p;//在0到总值之间取随机数，权值大的更有机会
	int w=0;
	while(1){
		tem-=sum[w].y;
		if(tem<0)
			return sum[w].x;
	w++;
	}
return 1;
}
int CRobt::AI(){
	dir[LEFT]=CPoint(-1,0);
dir[RIGHT]=CPoint(1,0);
dir[DOWN]=CPoint(0,1);
dir[UP]=CPoint(0,-1);

CPoint cur=control->head.point();
rout[cur.x][cur.y]=1;//初始化，起点设为1

int direct=-1;//默认方向
int value[5];
value[LEFT]=cal(cur+dir[LEFT],food.point(),level,1);
value[2]=cal(cur+dir[2],food.point(),level,1);
value[3]=cal(cur+dir[3],food.point(),level,1);
value[4]=cal(cur+dir[4],food.point(),level,1);
int min=999;
int way[4]={0};int len=0;
for(int i=1;i<5;i++){
	if(value[i]>=0&&value[i]<min){min=value[i];direct=i;}
}
for(int q=1;q<=4;q++)
if(min==value[q]) way[len++]=q;
if(direct==-1)return DOWN;//找不到就为下
return way[rand()%len];
}
int AI_di(){//蛇不会主动吃，但很难死
//dir[LEFT]=CPoint(-1,0);
//dir[RIGHT]=CPoint(1,0);
//dir[DOWN]=CPoint(0,1);
//dir[UP]=CPoint(0,-1);
//memset(rout,0,sizeof(rout));
//CPoint cur=control->head.point();
//rout[cur.x][cur.y]=1;//初始化，起点设为1
//
//int direct=-1;//默认方向
//int value[5];
//value[LEFT]=cal(cur+dir[LEFT],food.point(),level);
//value[2]=cal(cur+dir[2],food.point(),level);
//value[3]=cal(cur+dir[3],food.point(),level);
//value[4]=cal(cur+dir[4],food.point(),level);
//int min=999;
//for(int i=1;i<5;i++){
//	if(value[i]>0&&value[i]<min){min=value[i];direct=i;}
//}
//if(direct==-1)direct=DOWN;//找不到就为下
return 1;
}
int AI_D(){
int d[4]={1,2,3,4};
//int len=4;
//float distance=999.0f;
//
//if(food.x>cur.x){
//if(ifsafe(cur+dir[RIGHT])) return RIGHT;}
//else if(food.x<cur.x) {
//	if(ifsafe(cur+dir[LEFT])) return LEFT;}
//else//在同一x上
//{
//if(food.y>cur.y){
//if(ifsafe(cur+dir[DOWN])) return DOWN;}
//else
//	if(ifsafe(cur+dir[UP])) return UP;}
//if(direct==-1)
//{
//	if(food.y>cur.y){
//if(ifsafe(cur+dir[DOWN])) return DOWN;}
//else if(food.y<cur.y) {
//	if(ifsafe(cur+dir[UP])) return UP;}
//else//在同一y上
//{
//if(food.x>cur.x){
//if(ifsafe(cur+dir[RIGHT])) return RIGHT;}
//else
//if(ifsafe(cur+dir[LEFT])) return LEFT;}
//
//}//测试每个方向，遍历每个方向的可行性
//if(direct==-1) direct=1;
return 1;
}
int CRobt::go(){
	if(control==0) return false;

	control->SETDIR(AI_c());
	
	int t=control->run();
	if(ifsafe(control->head.point())) {
		delete control;
		control=0;
	}
	return t;
}
void  CRobt::draw(CDC*p){
	if(control) control->draw(p);
		else
	level;
	backgroud.Draw(p->m_hDC);
}
int Min(int a,int b){	if(a<b)return a;return b;}
int cal(POINT cur,POINT aim,int l,int f){//计算最段路径，l的次数决定计算的深度
	if(f) memset(rout,0,sizeof(rout));
	if(!ifsafe(cur))//死路
		return 1000;
rout[cur.x][cur.y]=1;
if(l==0)
return dis(cur,aim);
POINT p;p.x=cur.x-1;p.y=cur.y;
POINT p1;p1.x=cur.x+1;p1.y=cur.y;
POINT p2;p2.x=cur.x;p2.y=cur.y+1;
POINT p3;p3.x=cur.x;p3.y=cur.y-1;
int t2=1000;
int t1=cal(p,aim,l-1,0);if(t1>0) {t2=t1;}
 t1=Min(cal(p1,aim,l-1,0),t2);if(t1>=0) {t2=t1;}
 t1=Min(cal(p2,aim,l-1,0),t2);if(t1>=0) {t2=t1;}
 t1=Min(cal(p3,aim,l-1,0),t2);if(t1>=0){t2=t1;}

 if(t2==1000) return 1000;
return t2+1;

/*POINT p;
p.x=cur.x-1;p.y=cur.y;

if(rout[p.x][p.y]==0&&!crash(p))//该路为通
return 1+cal(p,aim,l-1);
else return 99999;//死路


p.x=cur.x+1;p.y=cur.y;
if(rout[p.x][p.y]==0&&!crash(p))//该路为通
return 1+cal(p,aim,l-1);
else return 99999;//死路
p.x=cur.x;p.y=cur.y+1;
if(rout[p.x][p.y]==0&&!crash(p))//该路为通
return 1+cal(p,aim,l-1);
else return 99999;//死路
p.x=cur.x;p.y=cur.y-1;
if(rout[p.x][p.y]==0&&!crash(p))//该路为通
return 1+cal(p,aim,l-1);
else return 99999;//死路
*/
}
int cal_c(POINT cur,POINT aim,int l,int f){//计算安全值（该方向下不返回的可能路径）
	if(f)
	memset(rout,0,sizeof(rout));
	if(!ifsafe(cur)||(rout[cur.x][cur.y]))//死路
		return 0;
	rout[cur.x][cur.y]=1;//记录该点，不再重复
	if(l==0) return 1;
	int r=1;//cur该点可走
	for(int i=1;i<5;i++)
	r+=cal_c((CPoint)cur+dir[i],aim,l-1,0);//遍历所有可能路径
	return r;
}