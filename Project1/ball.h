#pragma once
#include "sl.h"
#include <iostream>
#include <time.h>

struct Ball
{
	float positionX;
	float positionY;
	float speedX;
	float speedY;
	float radius;
};

void startBall(Ball& ball);

void ballMovement(Ball& ball, int widthScreen, int heightScreen);

void firstBallMovement(Ball& ball);


