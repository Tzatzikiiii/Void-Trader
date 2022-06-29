#include <tonc.h>
#include <seven/util/random.h>

#include "util.h"

// img
#include "splash.h"
// ------------------------------------------------------------- includes

void scene_showSplash()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    tonccpy(m3_mem, splashBitmap, splashBitmapLen); // copy splashBitmap into VRAM

    tte_init_bmp(3, NULL, NULL); // Vram Mode 4, default font (NULL), default renderer (NULL)
    tte_set_pos(40, 140);
    tte_write("- Press any key to start -"); // prompt user for key input

    while (true)
    {
        VBlankIntrWait();
        key_poll();

        if (key_is_down(KEY_ANY))
        {
            randSetSeed(REG_DISPSTAT ^ REG_TM0D); // get seed from display status register XOR'ed with timer

            // REG_TM2CNT ^= (TM_ENABLE); // disable timer 3 //TODO check if valid, see game.c
            return; // end splash
        }
    }
}

void scene_gameView()
{
    while (true)
    {
        REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // VRAM MODE 4, Background 2
        tte_init_bmp(3, NULL, NULL);         // Vram Mode 4, default font (NULL), default renderer (NULL)

        char startingPlanetName[6];
        util_insertRandomName(startingPlanetName, 6);
        tte_set_pos(40, 140);
        tte_write(startingPlanetName);
    }
}