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
	for (int i = 0; i < numBlock; i++)
	{
		if (blocks[i].isActive == true)
		{
			if (i <= 14 || i >= 28)
			{
				if (i % 2 == 0)
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(block2, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
				else
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(block1, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
			}

			if (i >= 14 && i < 28)
			{
				if (i % 2 == 0)
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(block1, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
				else
				{
					slSetForeColor(1, 1, 1, 1);
					slSprite(block2, blocks[i].positionX, blocks[i].positionY, blocks[i].width, blocks[i].height);
				}
			}	
		}
	}
}

void setSprites(int sprite1, int sprite2)
{
	block1 = sprite1;
	block2 = sprite2;	
}
