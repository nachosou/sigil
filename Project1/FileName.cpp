#include "include/sl.h"
#include "scenes.h"
#include "menu.h"
#include "rules.h"
#include "ball.h"
#include "paddle.h"
#include "blocks.h"

using namespace std;

void lifes(int& playerLife, Ball& ball, int widthScreen, int heightScreen, bool& newScene, int font);
bool collisionWithUpFrame(Ball ball, int heightScreen);
bool collisionWithPlayer(Ball ball, Paddle& paddle);
bool collisionWithRightFrame(Ball ball, int widthScreen);
bool collisionWithLeftFrame(Ball ball, int widthScreen);
void collisionWithBlocks(Ball& ball, Block blocks[], int numBlock);
void recochet(Ball& ball, int heightScreen, int widthScreen, Paddle paddle, Block blocks[], int numBlock);
void mainGame(Ball& ball, int widthScreen, int heightScreen, Paddle& paddle, int& playerLife, bool& newScene, int numBlock, Block blocks[], int font);
void drawMainGame(Paddle paddle, Ball ball, int numBlock, Block blocks[]);
void winOrLose(int playerLife, Block blocks[]);

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

	startBall(ball);
	startPaddle(paddle);

	GameScenes actualScene = GameScenes::Menu;
	bool newScene = true;
	GameScenes prevScene = actualScene;

	slWindow(widthScreen, heightScreen, "Simple SIGIL Example", false);

	setBlocks(blocks, numBlock, heightScreen);

	int font = slLoadFont("C:/Users/Aula 2/Documents/GitHub/sigil/Assets/Monoton-Regular.ttf");
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
			rules(actualScene);
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
			drawRules(font, heightScreen);
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
		slSetForeColor(1, 0, 0, 1);
		slCircleFill(30, 758, 15, 75);

		slSetForeColor(1, 0, 0, 0.5);
		slCircleFill(60, 758, 15, 75);
		slCircleFill(90, 758, 15, 75);
		break;
	case 2:
		slSetForeColor(1, 0, 0, 1);
		slCircleFill(30, 758, 15, 75);
		slCircleFill(60, 758, 15, 75);

		slSetForeColor(1, 0, 0, 0.5);
		slCircleFill(90, 758, 15, 75);
		break;
	case 3:
		slSetForeColor(1, 0, 0, 1);
		slCircleFill(30, 758, 15, 75);
		slCircleFill(60, 758, 15, 75);
		slCircleFill(90, 758, 15, 75);
		break;
	default:
		slSetForeColor(1, 0, 0, 0.5);
		slCircleFill(30, 758, 15, 75);
		slCircleFill(60, 758, 15, 75);
		slCircleFill(90, 758, 15, 75);
		break;
	}	
}

void winOrLose(int playerLife, Block blocks[])
{
	if (playerLife <= 0)
	{

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