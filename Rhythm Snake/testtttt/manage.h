#pragma once
#include"Robt.h"
#include"flash.h"
//hjjj;k
class manage//gttgtgtgtgt
{
public:
	CRobt man;
	Snake * control[30];//蛇
	int user;//使用者
	int robot;//机器控制
	void draw();
	bool go();
	void draw(CDC*);
	//交互
	int login(string name);//返回id
	bool setdir(int direct,int id);//direct==5表示交由机器控制
	void leave(int id);
	manage(void);
	~manage(void);
};
extern manage m;
