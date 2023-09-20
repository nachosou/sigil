#include "sl.h"
#include "scenes.h"
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
	float radius;
};

struct Block
{
	float positionX = 75;
	float positionY = 748;
	int width = 104;
	int height = 20;
};

void paddleMovement(Paddle& paddle, int widthScreen);
void ballMovement(Ball& ball, int width, int height);
void firstBallMovement(Ball& ball);
void lifes(int& playerLife, Ball& ball, int widthScreen, int heightScreen, bool& newScene);
void blocks();
bool collisionWithUpFrame(Ball& ball, int heightScreen);
bool collisionWithPlayer(Ball& ball, Paddle& paddle);
bool collisionWithRightFrame(Ball& ball, int widthScreen);
bool collisionWithLeftFrame(Ball& ball, int widthScreen);
void recochet(Ball& ball, int heightScreen, int widthScreen, Paddle paddle);
void mainGame(Ball& ball, int widthScreen, int heightScreen, Paddle& paddle, int& playerLife, bool& newScene);


void main()
{
	const int widthScreen = 1366;
	const int heightScreen = 768;
	int playerLife = 3;
	bool exitProgram = true;

	Paddle paddle;
	Ball ball;

	paddle.positionX = widthScreen / 2 - 150;
	paddle.positionY = 50;
	paddle.speed = 600;
	paddle.width = 300;
	paddle.height = 50;

	ball.positionX = widthScreen / 2;
	ball.positionY = heightScreen / 2;
	ball.speedX = 500;
	ball.speedY = 500;
	ball.radius = 15;

	GameScenes actualScene = GameScenes::Game;
	bool newScene = true;
	GameScenes prevScene = actualScene;

	slWindow(widthScreen, heightScreen, "Simple SIGIL Example", false);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE) && exitProgram)
	{
		newScene = actualScene != prevScene;
		prevScene = actualScene;

		switch (actualScene)
		{
		case GameScenes::Menu:

			break;
		case GameScenes::Game:
			mainGame(ball, widthScreen, heightScreen, paddle, playerLife, newScene);
			break;
		case GameScenes::Rules:

			break;
		case GameScenes::Exit:
			exitProgram = false;
			break;
		default:
			break;
		}
		slSetBackColor(0.92549019607843137254901960784314, 0.89803921568627450980392156862745, 0.8078431372549019607843137254902);

		switch (actualScene)
		{
		case GameScenes::Menu:

			break;
		case GameScenes::Game:
			slSetForeColor(0, 0.5176470588, 0.5254901961, 0.8);
			slRectangleFill(paddle.positionX + paddle.width / 2, paddle.positionY + paddle.height / 2, paddle.width, paddle.height);

			slSetForeColor(0.50196078431372549019607843137255, 0.74901960784313725490196078431373, 0.61568627450980392156862745098039, 0.8);
			slCircleFill(ball.positionX, ball.positionY, ball.radius, 75);

			slSetForeColor(0.95294117647058823529411764705882, 0.52549019607843137254901960784314, 0.18823529411764705882352941176471, 0.8);
			blocks();
			break;
		case GameScenes::Rules:

			break;
		case GameScenes::Exit:
			exitProgram = false;
			break;
		default:
			break;
		}
	
		slRender();
	}

	slClose();
}

void mainGame(Ball& ball, int widthScreen, int heightScreen, Paddle& paddle, int& playerLife, bool& newScene)
{
	if (newScene)
	{
		firstBallMovement(ball);
	}

	ballMovement(ball, widthScreen, heightScreen);

	recochet(ball, heightScreen, widthScreen, paddle);

	lifes(playerLife, ball, widthScreen, heightScreen, newScene);

	paddleMovement(paddle, widthScreen);
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
		if (paddle.positionX <= widthScreen - 300)
		{
			paddle.positionX += paddle.speed * slGetDeltaTime();
		}
	}
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

bool collisionWithUpFrame(Ball& ball, int heightScreen)
{
	if (ball.positionY >= heightScreen)
	{
		return true;
	}

	return false;
}

bool collisionWithRightFrame(Ball& ball, int widthScreen)
{
	if (ball.positionX >= widthScreen)
	{
		return true;
	}

	return false;
}

bool collisionWithLeftFrame(Ball& ball, int widthScreen)
{
	if (ball.positionX <= 0)
	{
		return true;
	}

	return false;
}

bool collisionWithPlayer(Ball& ball, Paddle& paddle)
{
	float xPosition = ball.positionX;
	float yPosition = ball.positionY;

	if (ball.positionX < paddle.positionX)
	{
		xPosition = paddle.positionX;
	}
	else if (ball.positionX > paddle.positionX + paddle.width)
	{
		xPosition = paddle.positionX + paddle.width;
	}

	if (ball.positionY < paddle.positionY)
	{
		yPosition = paddle.positionY;
	}
	else if (ball.positionY > paddle.positionY + paddle.height)
	{
		yPosition = paddle.positionY + paddle.height;
	}

	float xDistance = ball.positionX - xPosition;
	float yDistance = ball.positionY - yPosition;

	float distance = sqrt((xDistance * xDistance) + (yDistance * yDistance));

	if (distance <= ball.radius) {
		return true;
	}

	return false;
}

void recochet(Ball& ball, int heightScreen, int widthScreen, Paddle paddle)
{
	bool hitPaddleOne = collisionWithPlayer(ball, paddle);

	bool hitUpFrame = collisionWithUpFrame(ball, heightScreen);
	bool hitRightFrame = collisionWithRightFrame(ball, widthScreen);
	bool hitLeftFrame = collisionWithLeftFrame(ball, widthScreen);

	if (hitPaddleOne)
	{
		if (ball.positionX < paddle.positionX + paddle.width / 3)
		{
			ball.positionY += ball.radius;
			ball.speedY = -ball.speedY;
			ball.speedX = -500;
		}
		else if (ball.positionX > paddle.positionX + (paddle.width / 3 + paddle.width / 3))
		{
			ball.positionY += ball.radius;
			ball.speedY = -ball.speedY;
			ball.speedX = 500;
		}
		else
		{
			ball.positionY += ball.radius;
			ball.speedY = -ball.speedY;
			ball.speedX = 0;
		}
	}

	if (hitUpFrame)
	{
		ball.positionY -= ball.radius;
		ball.speedY = -ball.speedY;
	}
	if (hitRightFrame)
	{
		ball.positionX -= ball.radius;
		ball.speedX = -ball.speedX;
	}
	if (hitLeftFrame)
	{
		ball.positionX += ball.radius;
		ball.speedX = -ball.speedX;
	}
}

void  blocks()
{
	Block block[24];

	for (int i = 0; i < 12; i++)
	{
		for (int i = 0; i < 12; i++)
		{
			slRectangleFill(block[i].positionX, block[i].positionY, block[i].width, block[i].height);

			block[i + 1].positionX = block[i].positionX + 110;

			if (i == 12)
			{
				block[i].positionX = 10;
			}
		}

		for (int i = 0; i < 12; i++)
		{
			block[i].positionY -= 30;

			slRectangleFill(block[i].positionX, block[i].positionY, block[i].width, block[i].height);

			block[i + 1].positionX = block[i].positionX + 110;
		}
	}
}

void lifes(int& playerLife, Ball& ball, int widthScreen, int heightScreen, bool& newScene)
{
	if (ball.positionY <= 0)
	{
		if (ball.speedX == 0)
		{
			ball.speedX = 500;
		}

		firstBallMovement(ball);
		playerLife--;
		ball.positionX = widthScreen / 2;
		ball.positionY = heightScreen / 2;	
	}

	cout << playerLife << endl;
}
