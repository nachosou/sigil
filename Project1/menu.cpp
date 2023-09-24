#include "menu.h"
#include "include/sl.h"

void drawMenu(GameScenes& actualScene, int font, int widthScreen, int selectedPlay, int unselectedPlay, int selectedRules, int unselectedRules, int selectedExit, int unselectedExit, int credits, int logo, int wallPaper)
{
    int middleButtons = widthScreen / 2;

    slSetBackColor(1, 1, 1);
    slSprite(wallPaper, middleButtons, 768 / 2, 1366, 768);

    int height = 75;
    int width = 150;

    GameScenes playScene = GameScenes::Game;
    GameScenes rulesScene = GameScenes::Rules;
    GameScenes exitScene = GameScenes::Exit;

    slSetForeColor(1, 1, 1, 1);
    slSprite(logo, middleButtons, 600, 400, 200);

    menuButtons(actualScene, playScene, middleButtons, 400, width, height, unselectedPlay, selectedPlay);

    menuButtons(actualScene, rulesScene, middleButtons, 300, width, height, unselectedRules, selectedRules);

    menuButtons(actualScene, exitScene, middleButtons, 200, width, height, unselectedExit, selectedExit);

    slSprite(credits, middleButtons, 100, 450, 50);
}

void menuButtons(GameScenes& actualScene, GameScenes scene, int buttonX, int buttonY, int width, int height, int buttonUnselected, int buttonSelected)
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