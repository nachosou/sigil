#include "rules.h"
#include "include/sl.h"

void drawRules(GameScenes& actualScene, int wallPaper, int font, int heightScreen, int breakRules, int moveRules, int deathRules, int powerRules, int selectedMenu, int unselectedMenu)
{
    int rulesWidth = 300;
    int rulesHeight = 300;

    int buttonWidth = 150;
    int butonHeight = 75;

    slSetBackColor(1, 1, 1);
    slSprite(wallPaper, 1366 / 2, 768 / 2, 1366, 768);

    slSprite(breakRules, 200, 500, rulesWidth, rulesHeight);

    slSprite(moveRules, 700, 500, rulesWidth, rulesHeight);

    slSprite(deathRules, 200, 200, rulesWidth, rulesHeight);

    slSprite(powerRules, 700, 200, rulesWidth, rulesHeight);

    if (slGetMouseX() >= 1266 - buttonWidth / 2
        && slGetMouseX() <= 1266 + buttonWidth / 2
        && slGetMouseY() >= 100 - butonHeight / 2
        && slGetMouseY() <= 100 + butonHeight / 2)
    {
        slSetForeColor(1, 1, 1, 1);
        slSprite(selectedMenu, 1266, 100, buttonWidth, butonHeight);
        if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
        {
            actualScene = GameScenes::Menu;
        }
    }
    else
    {
        slSetForeColor(1, 1, 1, 1);
        slSprite(unselectedMenu, 1266, 100, buttonWidth, butonHeight);
    }
}