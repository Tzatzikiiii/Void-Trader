#include <stdbool.h>
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


// put a given quantity of a commodity into the cargo hold. If space is insufficient, return false
bool player_addCargo(Ship *playerVessel, Stock cargo) {
    int remainingSpace = playerVessel->currentSpace - cargo.quantity; // compute remaining space after cargo
    if (remainingSpace >= 0) {
        (playerVessel->cargoHold)[cargo.item.ID] = cargo; // assign cargo to its respective hold element
        playerVessel->currentSpace = remainingSpace; // update remaining space
        return true;
    } else {
        return false;
    }
}

// fuel the ship
void player_fuelShip(Ship *playerVessel)
{
    playerVessel->currentFuel = MAX_SHIP_FUEL; // set fuel to max
}

// updates player position to target if fuel sufficient. otherwise returns false
bool player_moveShip(Ship *playerVessel, Station target) {
    int fuelNeeded = station_returnFuelCostTo(playerVessel->currentPos, target); // compute needed fuel for trip
    bool tripPossible = fuelNeeded <= playerVessel->currentFuel; // check if fuel sufficient
    if (tripPossible)
    {
        playerVessel->currentFuel -= fuelNeeded; // remove expended fuel
        playerVessel->currentPos = target; // update position
        return true; 
    } else
    {
        return false;
    }
}