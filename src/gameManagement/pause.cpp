#include "gameManagement\pause.h"

void pause(GameScenes& actualScene, bool& isGamePaused, int wallPaper, int logo, int widthScreen, int heightScreen, int selectedMenu, int unselectedMenu, int selectedResume, int unselectedResume)
{
	int height = 75;
	int width = 150;
	int buttonsY = 300;

	GameScenes menuScene = GameScenes::Menu;
	GameScenes game = GameScenes::Game;

	slSetBackColor(1, 1, 1);
	slSprite(wallPaper, widthScreen / 2, heightScreen / 2, widthScreen, heightScreen);

	slSetForeColor(1, 1, 1, 1);
	slSprite(logo, widthScreen / 2, 600, 400, 200);

	if (slGetMouseX() >= (widthScreen / 2 - width) - width / 2
		&& slGetMouseX() <= (widthScreen / 2 - width) + width / 2
		&& slGetMouseY() >= buttonsY - height / 2
		&& slGetMouseY() <= buttonsY + height / 2)
	{
		slSetForeColor(1, 1, 1, 1);
		slSprite(selectedResume, (widthScreen / 2 - width) , buttonsY, width, height);
		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			isGamePaused = false;
			actualScene = game;
		}
	}
	else
	{
		slSetForeColor(1, 1, 1, 1);
		slSprite(unselectedResume, (widthScreen / 2 - width), buttonsY, width, height);
	}

	buttons(actualScene, menuScene, (widthScreen / 2 + width), buttonsY, width, height, unselectedMenu, selectedMenu);
}