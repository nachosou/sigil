#include "sl.h"
#include <iostream>
#include <time.h>

using namespace std;

struct Paddle
{
	float positionX;
	float positionY;
	int width;
	int height;
	int speed;
};

struct Ball
{
	float positionX;
	float positionY;
	float speedX;
	float speedY;
};

struct Block
{
	float positionX;
	float positionY;
	int width;
	int height;
};

void paddleMovement(Paddle& paddle);
void ballMovement(Ball& ball, int width, int height);
void firstBallMovement(Ball& ball);

void main()
{
	const int width = 1366;
	const int height = 768;

	Paddle paddle;
	Ball ball;

	paddle.positionX = width * 0.5;
	paddle.positionY = 50;
	paddle.speed = 600;
	paddle.width = 300;
	paddle.height = 50;

	ball.positionX = width / 2;
	ball.positionY = height / 2;
	ball.speedX = 100;
	ball.speedY = 100;

	bool newScene = true;

	slWindow(width, height, "Simple SIGIL Example", false);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetBackColor(0.5, 0.75, 1.0);

		paddleMovement(paddle);
		ballMovement(ball, width, height);

		slSetForeColor(1, 0, 0, 1);
		slRectangleFill(paddle.positionX, paddle.positionY, paddle.width, paddle.height);
		slCircleFill(ball.positionX, ball.positionY, 15, 75);

		slRender();
	}

	slClose();
}

void paddleMovement(Paddle& paddle)
{
	if (slGetKey(SL_KEY_LEFT))
	{
		paddle.positionX -= paddle.speed * slGetDeltaTime();
	}
	if (slGetKey(SL_KEY_RIGHT))
	{
		paddle.positionX += paddle.speed * slGetDeltaTime();
	}
}

void ballMovement(Ball& ball, int width, int height)
{
	ball.positionX += ball.speedX * slGetDeltaTime();
	ball.positionY += ball.speedY * slGetDeltaTime();
}

void firstBallMovement(Ball& ball)
{
	srand(time(NULL));
	int randomDirection = rand() % 2;

	if (randomDirection == 0)
	{
		ball.speedX *= -1;

		if (randomDirection == 0)
		{
			ball.speedY *= -1;
		}
	}
	else
	{
		if (randomDirection == 0)
		{
			ball.speedY *= -1;
		}
	}
}

bool collisionWithUpFrame(Ball& ball)
{
	if (ball.positionY <= 0)
	{
		return true;
	}

	return false;
}

bool collisionWithDownFrame(Ball& ball, int heightScreen)
{
	if (ball.positionY >= heightScreen)
	{
		return true;
	}

	return false;
}
