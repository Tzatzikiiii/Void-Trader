#include <tonc.h>
#include "scene.h"

void Game_gameLoop()
{
    REG_TM2CNT = (TM_ENABLE); // enable timer 3
    // TODO 2 second delay before prompt shows

    // scenes
    scene_showSplash();
    scene_gameView();

    Game_gameLoop(); // loop around
}