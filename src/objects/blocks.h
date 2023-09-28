#pragma once
#include "include/sl.h"

struct Block
{
	float positionX = 85;
	float positionY = 748;
	int width = 77;
	int height = 20;
	bool isActive = true;
};

static int block1;
static int block2;

void setBlocks(Block blocks[], int numBlock, int heightScreen);

void drawBlocks(Block blocks[], int numBlock);

void setSprites(int sprite1, int sprite2);
