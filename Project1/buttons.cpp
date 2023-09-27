#include "buttons.h"

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