#include "objects\powerUp.h"

void heartPowerUpCreator(PowerUps& powerUp, Paddle& paddle, Block blocks[], int sprite, int& playerLife, bool& isPowerUpActive, bool& heartStopAdd)
{
	int speedY = 300;
	bool collitionWithPaddle = paddleCollisionPowerUp(paddle, powerUp);

	if (!blocks[18].isActive && isPowerUpActive)
	{
		powerUp.positionX = blocks[18].positionX;
		powerUp.positionY = blocks[18].positionY;
		isPowerUpActive = false;
	}

	powerUp.positionY -= speedY * slGetDeltaTime();

	if (!collitionWithPaddle)
	{
		slSprite(sprite, powerUp.positionX, powerUp.positionY, powerUp.width, powerUp.height);
	}

	if (collitionWithPaddle && playerLife < 3 && heartStopAdd)
	{
		isPowerUpActive = false;
		playerLife++;
		heartStopAdd = false;
	}
}

void badHeartPowerUpCreator(PowerUps& powerUp, Paddle& paddle, Block blocks[], int sprite, int& playerLife, bool& isPowerUpActive, bool& deathHeartStopSubtract)
{
	int speedY = 300;
	bool collitionWithPaddle = paddleCollisionPowerUp(paddle, powerUp);

	if (!blocks[30].isActive && isPowerUpActive)
	{
		powerUp.positionX = blocks[30].positionX;
		powerUp.positionY = blocks[30].positionY;
		isPowerUpActive = false;
	}

	powerUp.positionY -= speedY * slGetDeltaTime();

	if (!collitionWithPaddle)
	{
		slSprite(sprite, powerUp.positionX, powerUp.positionY, powerUp.width, powerUp.height);
	}

	if (collitionWithPaddle && deathHeartStopSubtract)
	{
		isPowerUpActive = false;
		playerLife--;
		deathHeartStopSubtract = false;
	}
}

void goldHeartPowerUpCreator(PowerUps& powerUp, Paddle& paddle, Block blocks[], int sprite, int& playerLife, bool& isPowerUpActive)
{
	int speedY = 300;
	bool collitionWithPaddle = paddleCollisionPowerUp(paddle, powerUp);

	if (!blocks[5].isActive && isPowerUpActive)
	{
		powerUp.positionX = blocks[5].positionX;
		powerUp.positionY = blocks[5].positionY;
		isPowerUpActive = false;
	}

	powerUp.positionY -= speedY * slGetDeltaTime();

	if (!collitionWithPaddle)
	{
		slSprite(sprite, powerUp.positionX, powerUp.positionY, powerUp.width, powerUp.height);
	}

	if (collitionWithPaddle)
	{
		isPowerUpActive = false;
		playerLife = 3;
	}
}

bool paddleCollisionPowerUp(Paddle paddle, PowerUps powerUp)
{
	if (paddle.positionX + paddle.width >= powerUp.positionX &&
		paddle.positionX <= powerUp.positionX + powerUp.width &&
		paddle.positionY + paddle.height >= powerUp.positionY !=
		paddle.positionY >= powerUp.positionY &&
		paddle.positionY <= powerUp.positionY + powerUp.height)
	{
		return true;
	}
	return false;
}