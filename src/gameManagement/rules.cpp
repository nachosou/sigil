#include "gameManagement\rules.h"
#include "include/sl.h"

void drawRules(GameScenes& actualScene, int wallPaper, int font, int heightScreen, int breakRules, int moveRules, int deathRules, int powerRules, int pauseRules, int selectedMenu, int unselectedMenu)
{
    int rulesWidth = 300;
    int rulesHeight = 300;

    int buttonWidth = 150;
    int buttonHeight = 75;

    GameScenes menu = GameScenes::Menu;

    slSetBackColor(1, 1, 1);
    slSprite(wallPaper, 1366 / 2, 768 / 2, 1366, 768);

    slSprite(breakRules, 200, 500, rulesWidth, rulesHeight);

    slSprite(moveRules, 700, 500, rulesWidth, rulesHeight);

    slSprite(deathRules, 200, 200, rulesWidth, rulesHeight);

    slSprite(powerRules, 700, 200, rulesWidth, rulesHeight);

    slSprite(pauseRules, 1200, 500, rulesWidth, rulesHeight);

    buttons(actualScene, menu, 1266, 100, buttonWidth, buttonHeight, unselectedMenu, selectedMenu);
}