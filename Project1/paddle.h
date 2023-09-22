#pragma once
#include "include/sl.h"

struct Paddle
{
	float positionX;
	float positionY;
	int width;
	int height;
	int speed;
};

void startPaddle(Paddle& paddle);

void paddleMovement(Paddle& paddle, int widthScreen);
