#pragma once
#include "snake.h"
class NetSnake :
	public Snake
{
public:
	void d_go(int dir);//ֱ������
	NetSnake(void);
	~NetSnake(void);
};

