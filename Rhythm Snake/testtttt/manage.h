#pragma once
#include"Robt.h"
#include"flash.h"
//hjjj;k
class manage//gttgtgtgtgt
{
public:
	CRobt man;
	Snake * control[30];//��
	int user;//ʹ����
	int robot;//��������
	void draw();
	bool go();
	void draw(CDC*);
	//����
	int login(string name);//����id
	bool setdir(int direct,int id);//direct==5��ʾ���ɻ�������
	void leave(int id);
	manage(void);
	~manage(void);
};
extern manage m;
