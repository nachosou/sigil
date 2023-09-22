#include "ball.h"

void startBall(Ball& ball)
{
	const int widthScreen = 1366;
	const int heightScreen = 768;

	ball.positionX = widthScreen / 2;
	ball.positionY = heightScreen / 2;
	ball.speedX = 500;
	ball.speedY = 500;
	ball.radius = 15;
}

void ballMovement(Ball& ball, int widthScreen, int heightScreen)
{
	ball.positionX += ball.speedX * slGetDeltaTime();
	ball.positionY += ball.speedY * slGetDeltaTime();
}

void firstBallMovement(Ball& ball)
{
	srand(time(NULL));
	int randomDirection = rand() % 2 + 1;

	if (randomDirection == 1)
	{
		ball.speedX *= -1;

		if (randomDirection == 1)
		{
			ball.speedY *= -1;
			ball.speedX *= -1;
		}
	}
	else
	{
		if (randomDirection == 1)
		{
			ball.speedY *= -1;
			ball.speedX *= -1;
		}
	}
}