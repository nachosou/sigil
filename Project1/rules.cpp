#include "rules.h"
#include "include/sl.h"

void rules(GameScenes& actualScene)
{
    if (slGetKey(SL_KEY_BACKSPACE))
    {
        actualScene = GameScenes::Menu;
    }
}

void drawRules(int font, int heightScreen)
{
    int middleX = heightScreen / 2;

    slSetFont(font, 100);
    slText(middleX - 100, 600, "PONG");

    slSetFont(font, 50);
    slText(50, 500, "In order to win you have to break all the blocks without losing all your lifes");

    slText(50, 400, "You move with Left arrow(to the left) and Right arrow(to the right)");

    slText(50, 300, "To go back to menu during the game press ENTER");

    slSetFont(font, 25);
    slText(middleX - 170, 75, "Made By: Ignacio Gonzalez Souza");
}