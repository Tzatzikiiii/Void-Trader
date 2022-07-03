#include <tonc.h>
#include "station.h"
#include "util.h"
#include "player.h"
// ------------------------------------------------------------- includes

const u32 MAX_SHIP_FUEL = 3200;
const u32 STARTING_BALANCE = 400;

// initializes a given player vessel
void player_initPlayer(Ship *newPlayerVessel, Station stationArr[])
{
    newPlayerVessel->currentFuel = MAX_SHIP_FUEL; // set fuel to max
    newPlayerVessel->currentBalance = STARTING_BALANCE; // set initial balance
    newPlayerVessel->currentPos = stationArr[0]; // pick arbitrary starting point
}

// fuel the ship
void player_fuelShip(Ship *newPlayerVessel)
{
    newPlayerVessel->currentFuel = MAX_SHIP_FUEL; // set fuel to max
}