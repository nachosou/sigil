#pragma once
#include "sl.h"

struct Block
{
	float positionX = 85;
	float positionY = 748;
	int width = 77;
	int height = 20;
	bool isActive = true;
};

void setBlocks(Block blocks[], int numBlock, int heightScreen);

void drawBlocks(Block blocks[], int numBlock);
