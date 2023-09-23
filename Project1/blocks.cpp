#include "blocks.h"

void setBlocks(Block blocks[], int numBlock, int heightScreen)
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

void drawBlocks(Block blocks[], int numBlock)
{
	int brick1 = slLoadTexture("Assets/brick1.png");
	int brick2 = slLoadTexture("Assets/brick2.png");

	for (int i = 0; i < numBlock; i++)
	{
		if (blocks[i].isActive == true)
		{
			if (i <= 14 || i >= 28)
			{
				if (i % 2 == 0)
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(brick2, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
				else
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(brick1, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
			}

			if (i >= 14 && i < 28)
			{
				if (i % 2 == 0)
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(brick1, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
				else
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(brick2, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
			}	
		}
	}
}