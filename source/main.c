#include <stdio.h>
#include <tonc.h>
#include <seven/util/random.h>
#include <splash.h>

int main()
{
   tonccpy(m3_mem, splashBitmap, splashBitmapLen);

    // REG_BG0CNT = BG_CBB(0) | BG_4BPP | BG_SBB(30) | BG_REG_64x32;
    // tte_init_se_default(1, BG_CBB(1) | BG_SBB(24));
    
    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;
    
    // randSetSeed(REG_DISPSTAT);
    // randNext();
    // randNext();
    // randNext();
    // u32 ranVal = randNext();
    // char str[10] = {0};
    // itoa(ranVal, str, 10);

    // tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
    // tte_set_pos(92, 68);
    // tte_write(str);

    irq_init(NULL);
    irq_enable(II_VBLANK);


    while (1) {
        VBlankIntrWait();
    }

    return 0;
}