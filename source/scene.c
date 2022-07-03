#include <stdbool.h>
#include <tonc.h>

#include "scene.h"
#include "util.h"
#include "station.h"

// img
#include "splash.h"
#include "splash_prompt.h"
// ------------------------------------------------------------- includes

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

void scene_gameView()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // VRAM MODE 4, Background 2
    tte_init_bmp(3, NULL, NULL);         // VRAM Mode 4, default font (NULL), default renderer (NULL)

    while (true)
    {
        VBlankIntrWait();
        // TODO delete debug
        tte_set_pos(0, 0);
        tte_write("gameView:");
    }

    // TODO give player options: Map, choose and jump to next Destination, Buy & Sell, Repair + Refuel
    // jump to next Destination
    // if (station_)
}

void scene_mapView() // TODO implement map
{
}