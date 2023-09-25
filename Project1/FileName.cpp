#include "include/sl.h"
#include "scenes.h"
#include "menu.h"
#include "rules.h"
#include "ball.h"
#include "paddle.h"
#include "blocks.h"

using namespace std;

void lifes(int& playerLife, Ball& ball, int widthScreen, int heightScreen, bool& newScene, int font, int howManyBlocksDied, int numBlock);
void drawLifes(int playerLife, int aliveHeart, int deathHeart);
bool collisionWithUpFrame(Ball ball, int heightScreen);
bool collisionWithPlayer(Ball ball, Paddle& paddle);
bool collisionWithRightFrame(Ball ball, int widthScreen);
bool collisionWithLeftFrame(Ball ball, int widthScreen);
void collisionWithBlocks(Ball& ball, Block blocks[], int numBlock, int& howManyBlocksDied);
void recochet(Ball& ball, int heightScreen, int widthScreen, Paddle paddle, Block blocks[], int numBlock, int& howManyBlocksDied);
void mainGame(GameScenes& actualScene, Ball& ball, int widthScreen, int heightScreen, Paddle& paddle, int& playerLife, bool& newScene, int numBlock, Block blocks[], int font, int& howManyBlocksDied);
void drawMainGame(Paddle paddle, Ball ball, int numBlock, Block blocks[], int widthScreen, int heightScreen, int wallPaper, int paddleSprite, int aliveHeart, int deathHeart, int playerLife);
void winOrLose(int playerLife, int howManyBlocksDied, int numBlock, int font, int widthScreen, GameScenes& actualScene);
void resetStats(Block blocks[], int numBlock, Ball& ball, Paddle& paddle, int& playerLife);
void loseScreen(int wallpaperLose, int widthScreen, int heightScreen, int selectedMenu, int unselectedMenu, GameScenes& actualScene);
void winScreen(int wallpaperWin, int widthScreen, int heightScreen, int selectedMenu, int unselectedMenu, GameScenes& actualScene);
void buttons(GameScenes& actualScene, GameScenes scene, int buttonX, int buttonY, int width, int height, int buttonUnselected, int buttonSelected);
void historyScreen(int wallpaperHistory, int widthScreen, int heightScreen, int selectedPlay, int unselectedPlay, GameScenes& actualScene);

void main()
{
	const int widthScreen = 1366;
	const int heightScreen = 768;
	int playerLife = 3;
	bool exitProgram = true;
	const int numBlock = 42;
	int howManyBlocksDied = 0;

	/*float timer = 0;
	timer += slGetDeltaTime();
	char time[80];
	sprintf_s(time, "TIME: %f", timer);
	slText(widthScreen / 2, heightScreen / 2, time);*/

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

	setSprites(slLoadTexture("Assets/brick1.png"), slLoadTexture("Assets/brick2.png"));

	int paddleSprite = slLoadTexture("Assets/paddle.png");
	int bigPaddle = slLoadTexture("Assets/bigPaddle.png");
	int smallPaddle = slLoadTexture("Assets/smallPaddle.png");
	int aliveHeart = slLoadTexture("Assets/aliveHeart.png");
	int deathHeart = slLoadTexture("Assets/deathHeart.png");

	int selectedPlay = slLoadTexture("Assets/playButtonSelected.png");;
	int unselectedPlay = slLoadTexture("Assets/playButtonUnselected.png");
	int selectedRules = slLoadTexture("Assets/rulesButtonSelected.png");
	int unselectedRules = slLoadTexture("Assets/rulesButtonUnselected.png");
	int selectedExit = slLoadTexture("Assets/exitButtonSelected.png");
	int unselectedExit = slLoadTexture("Assets/exitButtonUnselected.png");
	int selectedMenu = slLoadTexture("Assets/menuButtonSelected.png");
	int unselectedMenu = slLoadTexture("Assets/menuButtonUnselected.png");
	int credits = slLoadTexture("Assets/creditos.png");
	int logo = slLoadTexture("Assets/logo.png");
	int wallPaper = slLoadTexture("Assets/fondo.png");
	int moveRules = slLoadTexture("Assets/moveRules.png");
	int breakRules = slLoadTexture("Assets/breakRules.png");
	int deathRules = slLoadTexture("Assets/deathRules.png");
	int wallpaperHistory = slLoadTexture("Assets/historiaComienzo.png");
	int wallpaperLose = slLoadTexture("Assets/historiaFinalMuerte.png");
	int wallpaperWin = slLoadTexture("Assets/historiaFinalVida.png");

	int font = slLoadFont("Assets/Monoton-Regular.ttf");
	slSetFont(font, 20);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE) && exitProgram)
	{
		newScene = actualScene != prevScene;
		prevScene = actualScene;

		switch (actualScene)
		{
		case GameScenes::Menu:
			resetStats(blocks, numBlock, ball, paddle, playerLife);
			drawMenu(actualScene, font, widthScreen, selectedPlay, unselectedPlay, selectedRules, unselectedRules, selectedExit, unselectedExit, credits, logo, wallPaper);
			break;
		case GameScenes::Game:
			mainGame(actualScene, ball, widthScreen, heightScreen, paddle, playerLife, newScene, numBlock, blocks, font, howManyBlocksDied);
			break;
		case GameScenes::Rules:
			drawRules(actualScene, wallPaper, font, heightScreen, breakRules, moveRules, deathRules, selectedMenu, unselectedMenu);
			break;
		case GameScenes::Exit:
			exitProgram = false;
			break;
		case GameScenes::History:
			historyScreen(wallpaperHistory, widthScreen, heightScreen, selectedPlay, unselectedPlay, actualScene);
			break;
		case GameScenes::Win:
			winScreen(wallpaperWin, widthScreen, heightScreen, selectedMenu, unselectedMenu, actualScene);
			break;
		case GameScenes::Lose:
			loseScreen(wallpaperLose, widthScreen, heightScreen, selectedMenu, unselectedMenu, actualScene);
			break;
		default:
			break;
		}

		switch (actualScene)
		{
		case GameScenes::Menu:
			drawMenu(actualScene, font, widthScreen, selectedPlay, unselectedPlay, selectedRules, unselectedRules, selectedExit, unselectedExit, credits, logo, wallPaper);
			break;
		case GameScenes::Game:
			drawMainGame(paddle, ball, numBlock, blocks, widthScreen, heightScreen, wallPaper, paddleSprite, aliveHeart, deathHeart, playerLife);
			break;
		case GameScenes::Rules:
			drawRules(actualScene, wallPaper, font, heightScreen, breakRules, moveRules, deathRules, selectedMenu, unselectedMenu);
			break;
		case GameScenes::Exit:
			exitProgram = false;
			break;
		case GameScenes::History:
			historyScreen(wallpaperHistory, widthScreen, heightScreen, selectedPlay, unselectedPlay, actualScene);
			break;
		case GameScenes::Win:
			winScreen(wallpaperWin, widthScreen, heightScreen, selectedMenu, unselectedMenu, actualScene);
			break;
		case GameScenes::Lose:
			loseScreen(wallpaperLose, widthScreen, heightScreen, selectedMenu, unselectedMenu, actualScene);
			break;

		default:
			break;
		}
		slRender();
	}
	slClose();
}

void mainGame(GameScenes& actualScene, Ball& ball, int widthScreen, int heightScreen, Paddle& paddle, int& playerLife, bool& newScene, int numBlock, Block blocks[], int font, int& howManyBlocksDied)
{
	if (newScene)
	{
		firstBallMovement(ball);
	}

	if (slGetKey(SL_KEY_BACKSPACE))
	{
		actualScene = GameScenes::Menu;
	}

	ballMovement(ball, widthScreen, heightScreen);

	lifes(playerLife, ball, widthScreen, heightScreen, newScene, font, howManyBlocksDied, numBlock);

	paddleMovement(paddle, widthScreen);

	recochet(ball, heightScreen, widthScreen, paddle, blocks, numBlock, howManyBlocksDied);

	winOrLose(playerLife, howManyBlocksDied, numBlock, font, widthScreen, actualScene);
}

void drawMainGame(Paddle paddle, Ball ball, int numBlock, Block blocks[], int widthScreen, int heightScreen, int wallPaper, int paddleSprite, int aliveHeart, int deathHeart, int playerLife)
{
	slSetBackColor(1, 1, 1);
	slSprite(wallPaper, widthScreen / 2, heightScreen / 2, widthScreen, heightScreen);

	slSetForeColor(1, 1, 1, 1);
	slSprite(paddleSprite, paddle.positionX + paddle.width / 2, paddle.positionY + paddle.height / 2, paddle.width, paddle.height);

	slSetForeColor(0, 0, 0, 1);
	slCircleFill(ball.positionX, ball.positionY, ball.radius, 75);

	drawBlocks(blocks, numBlock);

	drawLifes(playerLife, aliveHeart, deathHeart);
}

void recochet(Ball& ball, int heightScreen, int widthScreen, Paddle paddle, Block blocks[], int numBlock, int& howManyBlocksDied)
{
	bool hitPaddle = collisionWithPlayer(ball, paddle);

	bool hitUpFrame = collisionWithUpFrame(ball, heightScreen);
	bool hitRightFrame = collisionWithRightFrame(ball, widthScreen);
	bool hitLeftFrame = collisionWithLeftFrame(ball, widthScreen);

	collisionWithBlocks(ball, blocks, numBlock, howManyBlocksDied);

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

void lifes(int& playerLife, Ball& ball, int widthScreen, int heightScreen, bool& newScene, int font, int howManyBlocksDied, int numBlock)
{
	bool areBlocksAlive = true;

	if (howManyBlocksDied == numBlock)
	{
		areBlocksAlive = false;
	}

	if (areBlocksAlive)
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
	}
}

void winOrLose(int playerLife, int howManyBlocksDied, int numBlock, int font, int widthScreen, GameScenes& actualScene)
{
	if (playerLife <= 0)
	{
		actualScene = GameScenes::Lose;
	}

	if (howManyBlocksDied >= numBlock && playerLife > 0)
	{
		actualScene = GameScenes::Win;
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

void collisionWithBlocks(Ball& ball, Block blocks[], int numBlock, int& howManyBlocksDied)
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
			howManyBlocksDied++;
		}
	}
}

void drawLifes(int playerLife, int aliveHeart, int deathHeart)
{
	switch (playerLife)
	{
	case 1:
		slSetForeColor(1, 1, 1, 1);
		slSprite(aliveHeart, 30, 758, 31, 30);

		slSprite(deathHeart, 70, 758, 31, 30);
		slSprite(deathHeart, 110, 758, 31, 30);
		break;
	case 2:
		slSetForeColor(1, 1, 1, 1);
		slSprite(aliveHeart, 30, 758, 31, 30);
		slSprite(aliveHeart, 70, 758, 31, 30);


		slSprite(deathHeart, 110, 758, 31, 30);
		break;
	case 3:
		slSetForeColor(1, 1, 1, 1);
		slSprite(aliveHeart, 30, 758, 31, 30);
		slSprite(aliveHeart, 70, 758, 31, 30);
		slSprite(aliveHeart, 110, 758, 31, 30);
		break;
	default:
		slSetForeColor(1, 1, 1, 1);
		slSprite(deathHeart, 30, 758, 31, 30);
		slSprite(deathHeart, 70, 758, 31, 30);
		slSprite(deathHeart, 110, 758, 31, 30);
		break;
	}
}

void resetStats(Block blocks[], int numBlock, Ball& ball, Paddle& paddle, int& playerLife)
{
	const int widthScreen = 1366;
	const int heightScreen = 768;

	for (int i = 0; i < numBlock; i++)
	{
		blocks[i].positionX = 85;
		blocks[i].positionY = 85;
		blocks[i].width = 77;
		blocks[i].height = 20;
		blocks[i].isActive = true;
	}

	setBlocks(blocks, numBlock, heightScreen);
	
	paddle.speed = 600;
	paddle.width = 300;
	paddle.height = 50;
	paddle.positionX = widthScreen / 2 - paddle.width / 2;
	paddle.positionY = 50;

	ball.positionX = widthScreen / 2;
	ball.positionY = heightScreen / 2;
	ball.speedX = 500;
	ball.speedY = 500;
	ball.radius = 15;

	playerLife = 3;
}

void loseScreen(int wallpaperLose, int widthScreen, int heightScreen, int selectedMenu, int unselectedMenu, GameScenes& actualScene)
{
	GameScenes backToMenu = GameScenes::Menu;

	slSetForeColor(1, 1, 1, 1);
	slSprite(wallpaperLose, widthScreen / 2, heightScreen / 2, widthScreen, heightScreen);

	buttons(actualScene, backToMenu, 1266, 100, 150, 75, unselectedMenu, selectedMenu);
}

void winScreen(int wallpaperWin, int widthScreen, int heightScreen, int selectedMenu, int unselectedMenu, GameScenes& actualScene)
{
	GameScenes backToMenu = GameScenes::Menu;

	slSetForeColor(1, 1, 1, 1);
	slSprite(wallpaperWin, widthScreen / 2, heightScreen / 2, widthScreen, heightScreen);

	buttons(actualScene, backToMenu, 1266, 100, 150, 75, unselectedMenu, selectedMenu);
}

void historyScreen(int wallpaperHistory, int widthScreen, int heightScreen, int selectedPlay, int unselectedPlay, GameScenes& actualScene)
{
	GameScenes startGame = GameScenes::Game;

	slSetForeColor(1, 1, 1, 1);
	slSprite(wallpaperHistory, widthScreen / 2, heightScreen / 2, widthScreen, heightScreen);

	buttons(actualScene, startGame, 1266, 100, 150, 75, unselectedPlay, selectedPlay);
}

void buttons(GameScenes& actualScene, GameScenes scene, int buttonX, int buttonY, int width, int height, int buttonUnselected, int buttonSelected)
{
	if (slGetMouseX() >= buttonX - width / 2
		&& slGetMouseX() <= buttonX + width / 2
		&& slGetMouseY() >= buttonY - height / 2
		&& slGetMouseY() <= buttonY + height / 2)
	{
		slSetForeColor(1, 1, 1, 1);
		slSprite(buttonSelected, buttonX, buttonY, width, height);
		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			actualScene = scene;
		}
	}
	else
	{
		slSetForeColor(1, 1, 1, 1);
		slSprite(buttonUnselected, buttonX, buttonY, width, height);
	}
}
