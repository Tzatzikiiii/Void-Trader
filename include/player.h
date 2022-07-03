#ifndef PLAYER_H
#define PLAYER_H

#include <tonc.h> // necessary here but not in other header files??? C is cursed
#include "station.h"

typedef struct ship
{
    Station currentPos;
    u32 currentBalance;
    u32 currentFuel;
    Stock cargoHold[];
} Ship;

extern const u32 MAX_SHIP_FUEL;
extern const u32 STARTING_BALANCE;

void player_initPlayer(Ship *newPlayerVessel, Station stationArr[]);
void player_fuelShip(Ship *newPlayerVessel);


#endif