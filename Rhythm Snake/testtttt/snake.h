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
#define FOOD 1//ʳ����
#define SNAKE1 5
#define SNAKE2 9//�ߵı�� 31λ��ʾ��ͷ
#define WALL 2//ǽ�ı�� 
//������ʾ

Cell extern food;
using namespace std;
//��װ���ж���Ϊ���û�������ϵͳ����ͼ������
class Snake
{
protected:	
void wipepoint(POINT &p){Map[p.x][p.y]=0;}//�ڵ�ͼ�ϲ�ȥ���
int growth;//����������
int cur_dir;//���ڵķ���
int old_dir;//֮ǰ�ķ���
bool dead(POINT& p);
void drawrec(CDC* pDC,POINT& p,int style);
public:
	
	Cell head;//��ͷ
	int end;//�ߵ�ĩβ
	vector<Cell> body;//����
	int n;//���
	void grow(int g){growth+=g;}//����
	int run();//�ߵ��˶�
	void init(int x,int y,int s);//��ʼ��
	void draw(CDC* pDC);
	void draw();

	bool SETDIR(int direct);//���÷���

	Snake(){}
	Snake(int x,int y,int s);//���캯��
	~Snake();
	//�û�����
	string name;

	int scores;//��õķ���
	//
	 void d_go(int x,int y);
};
void setfood(POINT);
bool ifsafe(POINT p);//�ж�����
void eat();//��ʳ��
#endif // !defined(AFX_SNAKE1_H__EF6B659F_B2D5_4482_81CD_31CC77C0D814__INCLUDED_)
