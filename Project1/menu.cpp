#include "menu.h"
#include "include/sl.h"

void drawMenu(GameScenes& actualScene, int font, int widthScreen, int selectedPlay, int unselectedPlay, int selectedRules, int unselectedRules, int selectedExit, int unselectedExit, int credits, int logo, int wallPaper)
{
    int middleButtons = widthScreen / 2;
    
    int heightScreen = 768;

    slSetBackColor(1, 1, 1);
    slSprite(wallPaper, widthScreen / 2, heightScreen / 2, widthScreen, heightScreen);

    int height = 75;
    int width = 150;

    GameScenes historyScene = GameScenes::History;
    GameScenes rulesScene = GameScenes::Rules;
    GameScenes exitScene = GameScenes::Exit;

    slSetForeColor(1, 1, 1, 1);
    slSprite(logo, middleButtons, 600, 400, 200);

    buttons(actualScene, historyScene, middleButtons, 400, width, height, unselectedPlay, selectedPlay);

    buttons(actualScene, rulesScene, middleButtons, 300, width, height, unselectedRules, selectedRules);

    buttons(actualScene, exitScene, middleButtons, 200, width, height, unselectedExit, selectedExit);

    slSprite(credits, middleButtons, 100, 450, 50);
}
