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