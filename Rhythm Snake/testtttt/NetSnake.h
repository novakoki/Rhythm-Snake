#pragma once
#include "snake.h"
class NetSnake :
	public Snake
{
public:
	void d_go(int dir);//直接行走
	NetSnake(void);
	~NetSnake(void);
};

