#include <tonc.h>
#include <stdbool.h>

#include "scene.h"
#include "util.h"

// img
#include "splash.h"
// ------------------------------------------------------------- includes

void scene_showSplash()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    tonccpy(m3_mem, splashBitmap, splashBitmapLen); // copy splashBitmap into VRAM

    util_waitSeconds(2);

    tte_init_bmp(3, NULL, NULL); // VRAM Mode 4, default font (NULL), default renderer (NULL)
    tte_set_pos(40, 140);
    tte_write("- Press any key to start -"); // prompt user for key input

    while (true)
    {
        VBlankIntrWait();
        key_poll();

        if (key_is_down(KEY_ANY))
        {   
            util_setSeed(REG_TM2D); // set seed to value of timer register 2
            M3_CLEAR();            // Clear VRAM
            return;                // end splash
        }
    }
}

void scene_gameView()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // VRAM MODE 4, Background 2
    tte_init_bmp(3, NULL, NULL);         // VRAM Mode 4, default font (NULL), default renderer (NULL)


    char planetNameTest[6];
    util_insertRandomName(planetNameTest, 6);

    while (true)
    {
        VBlankIntrWait();
        tte_set_pos(0, 0);
        tte_write("gameView:");
        tte_set_pos(180, 130);
        tte_write(planetNameTest);
    }
}

void scene_mapView()
{
}