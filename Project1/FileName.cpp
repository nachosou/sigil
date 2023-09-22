#include "sl.h"
#include "scenes.h"
#include "menu.h"
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
	float positionX = 85;
	float positionY = 748;
	int width = 77;
	int height = 20;
	bool isActive = true;
};

void paddleMovement(Paddle& paddle, int widthScreen);
void ballMovement(Ball& ball, int width, int height);
void firstBallMovement(Ball& ball);
void lifes(int& playerLife, Ball& ball, int widthScreen, int heightScreen, bool& newScene, int font);
void setBlocks(Block block[], int numBlock, int heightScreen);
void drawBlocks(Block blocks[], int numBlock);
bool collisionWithUpFrame(Ball ball, int heightScreen);
bool collisionWithPlayer(Ball ball, Paddle& paddle);
bool collisionWithRightFrame(Ball ball, int widthScreen);
bool collisionWithLeftFrame(Ball ball, int widthScreen);
void collisionWithBlocks(Ball& ball, Block blocks[], int numBlock);
void recochet(Ball& ball, int heightScreen, int widthScreen, Paddle paddle, Block blocks[], int numBlock);
void mainGame(Ball& ball, int widthScreen, int heightScreen, Paddle& paddle, int& playerLife, bool& newScene, int numBlock, Block blocks[], int font);
void drawMainGame(Paddle paddle, Ball ball, int numBlock, Block blocks[]);

void main()
{
	const int widthScreen = 1366;
	const int heightScreen = 768;
	int playerLife = 3;
	bool exitProgram = true;
	const int numBlock = 42;

	Paddle paddle;
	Ball ball;
	Block blocks[numBlock];

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

	GameScenes actualScene = GameScenes::Menu;
	bool newScene = true;
	GameScenes prevScene = actualScene;

	slWindow(widthScreen, heightScreen, "Simple SIGIL Example", false);

	setBlocks(blocks, numBlock, heightScreen);

	int font = slLoadFont("C:/Users/Nacho/Desktop/sigil/Assets/Monoton-Regular.ttf");
	slSetFont(font, 20);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE) && exitProgram)
	{
		newScene = actualScene != prevScene;
		prevScene = actualScene;

		switch (actualScene)
		{
		case GameScenes::Menu:
			menu(actualScene);
			break;
		case GameScenes::Game:
			mainGame(ball, widthScreen, heightScreen, paddle, playerLife, newScene, numBlock, blocks, font);
			break;
		case GameScenes::Rules:

			break;
		case GameScenes::Exit:
			exitProgram = false;
			break;
		default:
			break;
		}

		switch (actualScene)
		{
		case GameScenes::Menu:
			drawMenu(font);
			break;
		case GameScenes::Game:
			drawMainGame(paddle, ball, numBlock, blocks);
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

void mainGame(Ball& ball, int widthScreen, int heightScreen, Paddle& paddle, int& playerLife, bool& newScene, int numBlock, Block blocks[], int font)
{
	if (newScene)
	{
		firstBallMovement(ball);
	}

	ballMovement(ball, widthScreen, heightScreen);

	lifes(playerLife, ball, widthScreen, heightScreen, newScene, font);

	paddleMovement(paddle, widthScreen);

	recochet(ball, heightScreen, widthScreen, paddle, blocks, numBlock);
}

void drawMainGame(Paddle paddle, Ball ball, int numBlock, Block blocks[])
{
	slSetBackColor(0.92549019607843137254901960784314, 0.89803921568627450980392156862745, 0.8078431372549019607843137254902);

	slSetForeColor(0, 0.5176470588, 0.5254901961, 0.8);
	slRectangleFill(paddle.positionX + paddle.width / 2, paddle.positionY + paddle.height / 2, paddle.width, paddle.height);

	slSetForeColor(0.50196078431372549019607843137255, 0.74901960784313725490196078431373, 0.61568627450980392156862745098039, 0.8);
	slCircleFill(ball.positionX, ball.positionY, ball.radius, 75);

	drawBlocks(blocks, numBlock);
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

bool collisionWithUpFrame(Ball ball, int heightScreen)
{
	if (ball.positionY >= heightScreen - 30)
	{
		return true;
	}

	return false;
}

bool collisionWithRightFrame(Ball ball, int widthScreen)
{
	if (ball.positionX >= widthScreen)
	{
		return true;
	}

	return false;
}

bool collisionWithLeftFrame(Ball ball, int widthScreen)
{
	if (ball.positionX <= 0)
	{
		return true;
	}

	return false;
}

bool collisionWithPlayer(Ball ball, Paddle& paddle)
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

void  setBlocks(Block blocks[], int numBlock, int heightScreen)
{
	int windowSeparation = 15;
	int verticalDisplacement = blocks->height + 20;
	int horizontalDisplacement = blocks->width + 20;

	int counter = 0;

	for (int i = 0; i < numBlock / 14; i++)
	{
		for (int j = i * 14; j < (i + 1) * 14; j++)
		{
			blocks[j].isActive = true;

			blocks[j].positionX = blocks[j].width / 2 + 15 + (horizontalDisplacement)*counter;
			blocks[j].positionY = (heightScreen - 20) - blocks[j].height / 2 - windowSeparation - verticalDisplacement * i;

			counter++;
			if (counter >= 14)
			{
				counter = 0;
			}
		}
	}
}

void collisionWithBlocks(Ball& ball, Block blocks[], int numBlock)
{
	for (int i = 0; i < numBlock; i++)
	{
		if (ball.positionX + ball.radius >= blocks[i].positionX - blocks[i].width / 2
			&& ball.positionX <= blocks[i].positionX + blocks[i].width / 2
			&& ball.positionY + ball.radius >= blocks[i].positionY - blocks[i].height / 2
			&& ball.positionY <= blocks[i].positionY + blocks[i].height / 2
			&& blocks[i].isActive)
		{			
			ball.positionY += ball.radius;
			ball.speedY = -ball.speedY;
			blocks[i].isActive = false;
		}
	}
}

void recochet(Ball& ball, int heightScreen, int widthScreen, Paddle paddle, Block blocks[], int numBlock)
{
	bool hitPaddle = collisionWithPlayer(ball, paddle);

	bool hitUpFrame = collisionWithUpFrame(ball, heightScreen);
	bool hitRightFrame = collisionWithRightFrame(ball, widthScreen);
	bool hitLeftFrame = collisionWithLeftFrame(ball, widthScreen);

	collisionWithBlocks(ball, blocks, numBlock);

	if (hitPaddle)
	{
		if (ball.positionX < paddle.positionX + paddle.width / 3)
		{
			ball.positionY += ball.radius;
			ball.speedY = -ball.speedY;
			ball.speedX = -768;
		}
		else if (ball.positionX > paddle.positionX + (paddle.width / 3 + paddle.width / 3))
		{
			ball.positionY += ball.radius;
			ball.speedY = -ball.speedY;
			ball.speedX = 768;
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

void drawBlocks(Block blocks[], int numBlock)
{
	for (int i = 0; i < numBlock; i++)
	{
		if (blocks[i].isActive == true)
		{
			if (i < 14 || i > 28)
			{
				if (i % 2 == 0)
				{
					slSetForeColor(0.95294117647058823529411764705882, 0.52549019607843137254901960784314, 0.18823529411764705882352941176471, 0.8);
				}
				else
				{
					slSetForeColor(0, 0.5176470588, 0.5254901961, 0.8);
				}
			}

			if (i > 14 && i < 28)
			{
				if (i % 2 == 0)
				{
					slSetForeColor(0, 0.5176470588, 0.5254901961, 0.8);
				}
				else
				{
					slSetForeColor(0.95294117647058823529411764705882, 0.52549019607843137254901960784314, 0.18823529411764705882352941176471, 0.8);
				}
			}


			slRectangleFill(blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
		}
	}
}

void lifes(int& playerLife, Ball& ball, int widthScreen, int heightScreen, bool& newScene, int font)
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

	switch (playerLife)
	{
	case 1:
		slSetFont(font, 25);
		slText(10, 738, "1 VIDA");
		break;
	case 2:
		slSetFont(font, 25);
		slText(10, 738, " 2 VIDAS");
		break;
	case 3:
		slSetFont(font, 25);
		slText(10, 738, "3 VIDAS");
		break;
	default:
		break;
	}	
}


