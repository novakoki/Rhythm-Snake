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
	POINT sum[4];//�����밲ȫֵ��
	float k=1;
	for(int i=0;i<4;i++)
	{sum[i].x=i+1;
	if(abs(dis(cur,food.point()))>abs(dis(cur+dir[i+1],food.point())))//��һ�����ӽ�ʳ��
		k=10;
	else
		k=0.5;
	sum[i].y=cal_c(cur+dir[i+1],food.point(),level,1)*k;//ʳ���Ӱ����
	k;}
	std::sort(sum,sum+4,comp);//�԰�ȫֵ����
	int p=0;
	for(int i=0;i<4;i++)
	{sum[i].y*=(4-i);//������
	p+=sum[i].y;
	}
	int tem;
	if(p==0) return 1;//��·����
	tem=rand()%p;//��0����ֵ֮��ȡ�������Ȩֵ��ĸ��л���
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
rout[cur.x][cur.y]=1;//��ʼ���������Ϊ1

int direct=-1;//Ĭ�Ϸ���
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
if(direct==-1)return DOWN;//�Ҳ�����Ϊ��
return way[rand()%len];
}
int AI_di(){//�߲��������ԣ���������
//dir[LEFT]=CPoint(-1,0);
//dir[RIGHT]=CPoint(1,0);
//dir[DOWN]=CPoint(0,1);
//dir[UP]=CPoint(0,-1);
//memset(rout,0,sizeof(rout));
//CPoint cur=control->head.point();
//rout[cur.x][cur.y]=1;//��ʼ���������Ϊ1
//
//int direct=-1;//Ĭ�Ϸ���
//int value[5];
//value[LEFT]=cal(cur+dir[LEFT],food.point(),level);
//value[2]=cal(cur+dir[2],food.point(),level);
//value[3]=cal(cur+dir[3],food.point(),level);
//value[4]=cal(cur+dir[4],food.point(),level);
//int min=999;
//for(int i=1;i<5;i++){
//	if(value[i]>0&&value[i]<min){min=value[i];direct=i;}
//}
//if(direct==-1)direct=DOWN;//�Ҳ�����Ϊ��
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
//else//��ͬһx��
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
//else//��ͬһy��
//{
//if(food.x>cur.x){
//if(ifsafe(cur+dir[RIGHT])) return RIGHT;}
//else
//if(ifsafe(cur+dir[LEFT])) return LEFT;}
//
//}//����ÿ�����򣬱���ÿ������Ŀ�����
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
int cal(POINT cur,POINT aim,int l,int f){//�������·����l�Ĵ���������������
	if(f) memset(rout,0,sizeof(rout));
	if(!ifsafe(cur))//��·
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

if(rout[p.x][p.y]==0&&!crash(p))//��·Ϊͨ
return 1+cal(p,aim,l-1);
else return 99999;//��·


p.x=cur.x+1;p.y=cur.y;
if(rout[p.x][p.y]==0&&!crash(p))//��·Ϊͨ
return 1+cal(p,aim,l-1);
else return 99999;//��·
p.x=cur.x;p.y=cur.y+1;
if(rout[p.x][p.y]==0&&!crash(p))//��·Ϊͨ
return 1+cal(p,aim,l-1);
else return 99999;//��·
p.x=cur.x;p.y=cur.y-1;
if(rout[p.x][p.y]==0&&!crash(p))//��·Ϊͨ
return 1+cal(p,aim,l-1);
else return 99999;//��·
*/
}
int cal_c(POINT cur,POINT aim,int l,int f){//���㰲ȫֵ���÷����²����صĿ���·����
	if(f)
	memset(rout,0,sizeof(rout));
	if(!ifsafe(cur)||(rout[cur.x][cur.y]))//��·
		return 0;
	rout[cur.x][cur.y]=1;//��¼�õ㣬�����ظ�
	if(l==0) return 1;
	int r=1;//cur�õ����
	for(int i=1;i<5;i++)
	r+=cal_c((CPoint)cur+dir[i],aim,l-1,0);//�������п���·��
	return r;
}