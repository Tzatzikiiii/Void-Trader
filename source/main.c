#include <stdio.h>
#include <tonc.h>
#include <seven/util/random.h>
#include <splash.h>

int main()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    randSetSeed(5);
    randNext();
    randNext();
    randNext();
    u32 ranVal = randNext();
    char str[10] = {0};
    itoa(ranVal, str, 10);

    tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
    tte_set_pos(92, 68);
    tte_write(str);

    irq_init(NULL);
    irq_enable(II_VBLANK);


    while (1) {
        VBlankIntrWait();
    }

    return 0;
}