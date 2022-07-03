#ifndef PLAYER_H
#define PLAYER_H

#include "station.h"

typedef struct ship
{
    Station currentPos;
    u32 currentBalance;
    u32 currentFuel;
    u32 currentSpace;
    Stock cargoHold[39]; 
    // predefined size since amount of commodity types is known (NUM_COMMODITY_TYPES)
    // bad practice but: i ain't fuck with no malloc()
} Ship;

extern const u32 MAX_SHIP_SPACE;
extern const u32 MAX_SHIP_FUEL;
extern const u32 STARTING_BALANCE;

void player_initPlayer(Ship *newPlayerVessel, Station stationArr[]);
bool player_addCargo(Ship *playerVessel, Stock addedCargo);
bool player_removeCargo(Ship *playerVessel, Stock removedCargo);
void player_payPlayer(Ship *player, u32 amount);
bool player_chargePlayer(Ship *player, u32 amount);
void player_fuelShip(Ship *playerVessel);
bool player_moveShip(Ship *playerVessel, Station target);

#endif