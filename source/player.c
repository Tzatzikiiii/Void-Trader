#include <stdbool.h>
#include <tonc.h>

#include "station.h"
#include "util.h"
#include "player.h"
// ------------------------------------------------------------- includes

// TODO adjust consts if needed
const u32 MAX_SHIP_FUEL = 3200;
const u32 MAX_SHIP_SPACE = 300;
const u32 STARTING_BALANCE = 400;

// initializes a given player vessel
void player_initPlayer(Ship *newPlayerVessel, Station stationArr[])
{
    newPlayerVessel->currentFuel = MAX_SHIP_FUEL;       // set fuel to max
    newPlayerVessel->currentBalance = STARTING_BALANCE; // set initial balance
    newPlayerVessel->currentSpace = MAX_SHIP_SPACE;     // set initial free space
    newPlayerVessel->currentPos = stationArr[0];        // pick arbitrary starting point
}

// put a given quantity of a commodity into the cargo hold. If space is insufficient, return false
bool player_addCargo(Ship *playerVessel, Stock addedCargo)
{
    int remainingSpace = playerVessel->currentSpace - addedCargo.quantity; // compute remaining space after cargo
    if (remainingSpace >= 0)
    {
        (playerVessel->cargoHold)[addedCargo.item.ID] = addedCargo; // assign cargo to its respective hold element
        playerVessel->currentSpace = remainingSpace;                  // update remaining space
        return true;
    }
    else
    {
        return false;
    }
}

// remove given quantity of a commodity from the cargo hold, returns false if cargo insufficient
bool player_removeCargo(Ship *playerVessel, Stock removedCargo)
{
    u16 *quantPtr = &(playerVessel->cargoHold[removedCargo.item.ID].quantity); // pointer to the quantity stored in the cargo hold

    if (*quantPtr - removedCargo.quantity < 0)
    {
        return false; // -> amount in cargo hold not sufficient
    }
    else
    {
        *quantPtr -= removedCargo.quantity; // subtract removed amount from cargo quantity
        playerVessel->currentSpace += removedCargo.quantity; // free cargo space
    }
}

// adds specified amount of money to player's balance
void inline player_payPlayer(Ship *player, u32 amount)
{
    player->currentBalance += amount;
}

// removes specified amount of money from player's balance, returns false if balance insufficient
bool inline player_chargePlayer(Ship *player, u32 amount)
{
    if (player->currentBalance - amount < 0) // if balance too low
    {   
        // don't charge player
        return false;        
    } else
    {
        player->currentBalance -= amount;
    }
}

// fuel the ship
void inline player_fuelShip(Ship *playerVessel)
{
    playerVessel->currentFuel = MAX_SHIP_FUEL; // set fuel to max
}

// updates player position to target if fuel sufficient. otherwise returns false
bool player_moveShip(Ship *playerVessel, Station target)
{
    int fuelNeeded = station_returnFuelCostTo(playerVessel->currentPos, target); // compute needed fuel for trip
    bool tripPossible = fuelNeeded <= playerVessel->currentFuel;                 // check if fuel sufficient
    if (tripPossible)
    {
        playerVessel->currentFuel -= fuelNeeded; // remove expended fuel
        playerVessel->currentPos = target;       // update position
        return true;
    }
    else
    {
        return false;
    }
}