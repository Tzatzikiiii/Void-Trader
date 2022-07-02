#include <tonc.h>

#include "scene.h"
#include "station.h"
// ------------------------------------------------------------- includes

const int MAX_STATION_NUM = 100;

static void initStationArr(Station stationArr[]) // initializes the stationArray
{
    for (int i = 0; i  < MAX_STATION_NUM; i++) {
        station_fillInfo(stationArr[i], 1, 1); //TODO assign each station unique co-ordinates instead of 1,1
    }
}
void Game_gameLoop()
{
    REG_TM2CNT = TM_ENABLE | TM_FREQ_1; // enable timer 3 and set frequency to once per cycle

    // scenes
    scene_showSplash(); // splash screen
    REG_TM2CNT ^= TM_ENABLE; // disable timer

    Station stationArr[MAX_STATION_NUM]; // define the station array
    initStationArr(stationArr); // initialize all the stations
    scene_gameView(stationArr); // game




    Game_gameLoop(); // loop around
}
