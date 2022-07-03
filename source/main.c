#include <tonc.h>
#include "game.h"
// ------------------------------------------------------------- includes

int main()
{
    irq_init(NULL);
    irq_enable(II_VBLANK);

    Game_gameLoop();
    return 0;
}