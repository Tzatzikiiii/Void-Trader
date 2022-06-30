#include <tonc.h>
#include "scene.h"
// ------------------------------------------------------------- includes

void Game_gameLoop()
{
    REG_TM2CNT = (TM_ENABLE); // enable timer 3

    // scenes
    scene_showSplash(); // splash screen
    scene_gameView(); // game


    REG_TM2CNT ^= (TM_ENABLE);


    Game_gameLoop(); // loop around
}