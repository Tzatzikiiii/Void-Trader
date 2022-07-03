#include <stdbool.h>
#include <tonc.h>

#include "scene.h"
#include "util.h"
#include "station.h"
#include "player.h"

// img
#include "splash.h"
#include "splash_prompt.h"
// ------------------------------------------------------------- includes

 // shows the splash screen + prompt
void scene_showSplash()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    tonccpy(m3_mem, splashBitmap, splashBitmapLen); // copy splashBitmap into VRAM

    util_waitSeconds(2);

    tonccpy(m3_mem, splash_promptBitmap, splash_promptBitmapLen);

    while (true)
    {
        VBlankIntrWait();
        key_poll();

        if (key_is_down(KEY_ANY))
        {   
            util_setSeed(REG_TM2D); // set RNG seed to value of timer register 3
            M3_CLEAR();            // Clear VRAM
            return;                // end splash
        }
    }
}

// main game view
void scene_gameView()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // VRAM MODE 4, Background 2
    tte_init_bmp(3, NULL, NULL);         // text engine setup: VRAM Mode 4, default font (NULL), default renderer (NULL)

    Station stationArr[MAX_STATION_NUM]; // define the station array
    station_initStationArr(stationArr); // initialize station array
    Ship playerVessel; // define the playerVessel
    player_initPlayer(&playerVessel, stationArr); // initialize player vessel

    //TODO DELETE debug
    char nameTest[8];
    util_insertRandomName(nameTest, 8);

    while (true)
    {
        VBlankIntrWait();
        tte_set_pos(0, 0);
        // tte_write("yeet");
        tte_write(playerVessel.currentPos.name);
        tte_set_pos(5, 120);
        tte_write(stationArr[0].name);
        tte_set_pos(130, 120);
        tte_write(nameTest);
        m3_rect(5, 120, 6, 121, CLR_LIME);
    }

    // TODO give player options: Map, choose and jump to next Destination, Buy & Sell, Repair + Refuel
    // jump to next Destination
    // if (station_)
}

void scene_mapView() // TODO implement map
{

}