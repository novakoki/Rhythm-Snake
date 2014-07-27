#pragma once

// Cell ����Ŀ��
#include<vector>
#include"BitmapEx.h"
extern CBitmapEx backgroud;
extern CBitmapEx snake;
extern	int Map[100][100];//���õ�ͼ
#define MAX_W 40 
#define MAX_H 40//��ͼ��С
const extern int size;//��ͼ�ϵ�ÿ����Ԫ���С
using namespace std;
class Cell 
{
protected:
	int sign;//���Ա�ʾ����������ʳ��ߵ�
	int style;//��ͼ����
public:
	
	Cell();
	static float k;//����֮������һ���Ŀ�϶
	static int size;//��Ԫ���С
	
	Cell(int,int,int,int);//���캯��
	void init(int a,int b,int col,int s);//��ʼ��
	int x,y;//����
	void draw(CDC* pDC);//��CDC��ͼ
	void draw();//��bitmap����ͼ
	void setstyle(int s){style=s;}//���û�ͼ����
	
	//ͨ��moveȷ���ܷ��ƶ�
	bool move(int a,int b);
	bool move(CPoint &p){return move(p.x,p.y);}
	
	bool moveto(CPoint const &p){ return move(p.x-x,p.y-y);}//�ƶ�
	void setsign(int c){sign=c;}//�������Ա��


	const Cell & operator=(const Cell & a ){
		x=a.x;y=a.y;sign=a.sign;style=a.style;
		return *this;}//�����=����

public:
	CPoint point(){return CPoint(x,y);}//��ȡ����
	int getstyle(){return style;}//��ȡ��ͼ����
	int getsign(){return sign;}//��ȡ����
	void setpoint() { Map[x][y] = sign; }//���
	virtual ~Cell();
};

int getsign(int n,bool head);//n ��sign��ת��
int getn(int sign);//nΪ1��ʳ�3��ǽ������Ϊ������� ��31λ��ʾΪ������ͷ