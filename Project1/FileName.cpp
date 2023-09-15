#include "sl.h"
#include <iostream>

using namespace std;

struct Paddle
{
	float x;
	float y;
	int width;
	int height;
	int speed;
};

struct Ball
{
	float x;
	float y;
	float speedX;
	float speedY;
};

struct Block
{
	float x;
	float y;
	int width;
	int height;
};

void paddleMovement(Paddle& paddle);

void main()
{
	const int width = 1366;
	const int height = 768;

	Paddle paddle;

	paddle.x = width * 0.5;
	paddle.y = 50;
	paddle.speed = 600;
	paddle.width = 300;
	paddle.height = 50;

	slWindow(width, height, "Simple SIGIL Example", false);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetBackColor(0.5, 0.75, 1.0);

		paddleMovement(paddle);

		slSetForeColor(1, 0, 0, 1);
		slRectangleFill(paddle.x, paddle.y, paddle.width, paddle.height);

		slRender();
	}

	slClose();
}

void paddleMovement(Paddle& paddle)
{
	if (slGetKey(SL_KEY_LEFT))
	{
		paddle.x -= paddle.speed * slGetDeltaTime();
	}
	if (slGetKey(SL_KEY_RIGHT))
	{
		paddle.x += paddle.speed * slGetDeltaTime();
	}
}

void ballMovement()
{

}
