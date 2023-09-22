#include "rules.h"
#include "sl.h"

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
    slText(50, 500, "PLAY");

    slText(50, 400, "RULES");

    slText(50, 300, "EXIT");

    slSetFont(font, 25);
    slText(middleX - 170, 75, "Made By: Ignacio Gonzalez Souza");
}