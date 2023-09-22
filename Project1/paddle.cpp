#include "paddle.h"

void startPaddle(Paddle& paddle)
{
	const int widthScreen = 1366;

	paddle.speed = 600;
	paddle.width = 300;
	paddle.height = 50;
	paddle.positionX = widthScreen / 2 - paddle.width / 2;
	paddle.positionY = 50;
}

void paddleMovement(Paddle& paddle, int widthScreen)
{
	if (slGetKey(SL_KEY_LEFT))
	{
		if (paddle.positionX >= 0)
		{
			paddle.positionX -= paddle.speed * slGetDeltaTime();
		}
	}
	if (slGetKey(SL_KEY_RIGHT))
	{
		if (paddle.positionX <= widthScreen - paddle.width)
		{
			paddle.positionX += paddle.speed * slGetDeltaTime();
		}
	}
}