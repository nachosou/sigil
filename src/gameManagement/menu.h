#pragma once
#include "gameManagement\scenes.h"
#include "objects\buttons.h"

struct menuButtons
{
	float positionX;
	float positionY;
	int width;
	int height;
};

void drawMenu(GameScenes& actualScene, int font, int widthScreen, int selectedPlay, int unselectedPlay, int selectedRules, int unselectedRules, int selectedExit, int unselectedExit, int credits, int logo, int wallPaper);

