#include <stdbool.h>
#include <tonc.h>

#include "util.h"
#include "station.h"
#include "commodity.h"
// ------------------------------------------------------------- includes

const u8 POLICE_MIN_CHANCE = 10;
const u8 POLICE_MAX_CHANCE = 50;

const u8 PIRATES_MIN_CHANCE = 0;
const u8 PIRATES_MAX_CHANCE = 80;

void station_fillInfo(Station *station, int xPos, int yPos) // generates random name and encounter chances
{
    util_insertRandomName(station->name, util_getRandomInRange(2, 9)); // insert a random name with a max length of 8 chars

    station->hasPirates = (util_getRandomBool && util_getRandomBool); // two coinflips = 25% chance -> every 4th station will have chance of pirate encounter
    if (station->hasPirates)
    {
        station->chancePirateEncounter = util_getRandomInRange(5, 101); // pick chance from PIRATES_MIN_CHANCE to PIRATE_MAX_CHANCE
    }
    else
    {
        station->chancePirateEncounter = 0; // no chance of pirates at all
    }
    station->chancePoliceEncounter = util_getRandomInRange(POLICE_MIN_CHANCE, POLICE_MAX_CHANCE + 1); 
    // every station has at least *some* level of police presence so a chance is always calculated
}

inline bool encounteredPolice(Station arrivalStation) // TODO maybe change chances depending on cargo hold of player
{
    return (util_getRandomInRange(1, 100) <= arrivalStation.chancePoliceEncounter); // return if random number between 1 and 100 lies within percentage
    // TODO transition to police encounter event
}

inline bool encounteredPirates(Station arrivalStation)
{
    return(util_getRandomBool(1, 100) <= arrivalStation.chancePirateEncounter); // return if random num between 1 and 100 lies withing percentage
    // TODO transition to pirate encounter event
}