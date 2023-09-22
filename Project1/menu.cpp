#include "menu.h"
#include "include/sl.h"

void menu(GameScenes& actualScene)
{
    if (slGetKey(SL_KEY_ENTER))
    {
        actualScene = GameScenes::Game;
    }

    if (slGetKey(SL_KEY_TAB))
    {
        actualScene = GameScenes::Rules;
    }

    if (slGetKey(SL_KEY_ESCAPE))
    {
        actualScene = GameScenes::Exit;
    }
}

void drawMenu(int font)
{
    slSetBackColor(0.46666666666666666666666666666667, 0.53333333333333333333333333333333, 0.6);

    int middleX = 583;
    int gameButtonY = 400;
    int rulesButtonY = 300;
    int exitButtonY = 200;
    int height = 50;
    int width = 200;

    slSetFont(font, 100);
    slText(middleX - 100, 600, "PONG");
    
    slSetFont(font, 50);
    slText(middleX - 20, gameButtonY, "PLAY");

    slText(middleX - 30, rulesButtonY, "RULES");

    slText(middleX - 7, exitButtonY, "EXIT");

    slSetFont(font, 25);
    slText(middleX - 170, 75, "Made By: Ignacio Gonzalez Souza");
}