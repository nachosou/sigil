#pragma once
#include "objects\blocks.h"
#include "paddle.h"

struct PowerUps
{
	float positionX;
	float positionY;
	int width = 50;
	int height = 50;
};

void heartPowerUpCreator(PowerUps& powerUp, Paddle& paddle, Block blocks[], int sprite, int& playerLife, bool& isPowerUpActive, bool& heartStopAdd);

void badHeartPowerUpCreator(PowerUps& powerUp, Paddle& paddle, Block blocks[], int sprite, int& playerLife, bool& isPowerUpActive, bool& deathHeartStopSubtract);

void goldHeartPowerUpCreator(PowerUps& powerUp, Paddle& paddle, Block blocks[], int sprite, int& playerLife, bool& isPowerUpActive);

bool paddleCollisionPowerUp(Paddle paddle, PowerUps powerUp);