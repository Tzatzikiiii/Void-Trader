#include <tonc.h>
#include "scene.h"
// ------------------------------------------------------------- includes

void Game_gameLoop()
{
    REG_TM2CNT = TM_ENABLE | TM_FREQ_1; // enable timer 3 and set frequency to once per cycle

    // scenes
    scene_showSplash(); // splash screen
    REG_TM2CNT ^= TM_ENABLE; // disable timer
    scene_gameView(); // game




    Game_gameLoop(); // loop around
}