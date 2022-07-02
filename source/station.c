#include <stdbool.h>
#include <tonc.h>

#include "util.h"
#include "station.h"
#include "commodity.h"
// ------------------------------------------------------------- includes

void station_fillInfo(Station newStation, int xPos, int yPos)
{
    util_insertRandomName(newStation.name, util_getRandomInRange(2, 9)); // insert a random name with a max length of 8 chars

    newStation.hasPirates = (util_getRandomBool && util_getRandomBool); // two coinflips = 25% chance
    if (newStation.hasPirates)
    {
        newStation.chancePirates = util_getRandomInRange(5, 101); // pick chance from 5 to 100%
    } else 
    {
        newStation.chancePirates = 0;
    }
    newStation.chancePolice = util_getRandomInRange(0, 51); // every station has at least *some* level of police presence
}



