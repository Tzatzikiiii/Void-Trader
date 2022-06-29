#include <stdio.h>
#include <stdbool.h>
#include <tonc.h>

#include <seven/util/random.h>

void util_insertRandomName(char nameArr[], int arrLen)
{
    for (int i = 0; i < arrLen; i++)
    {
        nameArr[i] = 90;
    }
    return;
}

bool util_getRandomBool()
{
    return (REG_VCOUNT % 2);
}