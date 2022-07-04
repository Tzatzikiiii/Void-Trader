#include <stdbool.h>
#include <tonc.h>

#include "util.h"
#include "player.h"
// ------------------------------------------------------------- includes

const u16 MAX_COMMODITY_QUANTITY = 30;
const u8 MAX_COMMODITY_FLUX = 40;

const u8 POLICE_MIN_CHANCE = 10;
const u8 POLICE_MAX_CHANCE = 50;

const u8 PIRATES_MIN_CHANCE = 0;
const u8 PIRATES_MAX_CHANCE = 80;

const u16 MAX_STATION_NUM = 1;

const u16 STANDARD_FUEL_PRICE = 2; // FIXME probably needs adjusting

static void station_fillInfo(Station *station) // generates random name, commodity supply and encounter chances
{
    util_insertRandomName(station->name, 8); // insert a random name with a max length of 8 chars

    station->hasPirates = (util_getRandomBool && util_getRandomBool); // two coinflips = 25% chance. So every ~ 4th station will have chance of pirate encounter
    if (station->hasPirates)
    {
        station->chancePirateEncounter = util_getRandomInRange(PIRATES_MIN_CHANCE, PIRATES_MAX_CHANCE); // pick chance from PIRATES_MIN_CHANCE to PIRATE_MAX_CHANCE
    }
    else
    {
        station->chancePirateEncounter = 0; // no chance of pirates at all
    }
    station->chancePoliceEncounter = util_getRandomInRange(POLICE_MIN_CHANCE, POLICE_MAX_CHANCE + 1);
    // every station has at least *some* level of police presence, so a chance is always calculated

    int numOffers = util_getRandomInRange(3, NUM_COMMODITY_TYPES - 20); // pick number of commodity offers available

    for (int i = 0; i < numOffers; i++)
    {
        // for every element of the stationSupply array choose one random commodity type
        (station->stationSupply)[i].item = commodity_getCommodity(util_getRandomInRange(0, NUM_COMMODITY_TYPES)); // ADD setters for expressions like this
        (station->stationSupply)[i].quantity = util_getRandomInRange(1, MAX_COMMODITY_QUANTITY);                  // pick a random quantity
        commodity_applyFluctuation(&(station->stationSupply)[i].item, MAX_COMMODITY_FLUX);                        // apply fluctuation //DEBUG check
    }
}

// sets the station's position to two given coordinates
static void station_setPosition(Station *station, int xPos, int yPos)
{
    station->xPos = xPos;
    station->yPos = yPos;
}

// initializes a given array of stations
void station_initStationArr(Station stationArr[])
{
    int x, y;
    for (int i = 0; i < MAX_STATION_NUM; i++)
    {
        x = util_getRandomInRange(0, 491);
        y = util_getRandomInRange(0, 491);
        station_fillInfo(&stationArr[i]);

        if (i > 0) // ignore on first element
        {
            for (int j = 0; j < MAX_STATION_NUM; j++) // check for collision with each station
            {
                if (x >= stationArr[j].xPos - 9 || x <= stationArr[j].xPos + 9)
                {
                    if (y >= stationArr[j].yPos - 9 || y <= stationArr[j].yPos + 9)
                    {
                        i--; // reroll if within radius of other station
                    }
                }
            }
        }

        station_setPosition(&stationArr[i], x, y); // set station position to calculated value
    }
}

// returns if a police inspection event should be triggered upon arrival to a given station
inline bool station_encounteredPolice(Station arrivalStation) // ADD maybe change chances depending on cargo hold of player
{
    return (util_getRandomInRange(1, 100) <= arrivalStation.chancePoliceEncounter); // return if random number between 1 and 100 lies within percentage
    // TODO transition to police encounter event
}

// returns if a pirate event should be triggered upon arrival to a given station
inline bool station_encounteredPirates(Station arrivalStation)
{
    return (util_getRandomBool(1, 100) <= arrivalStation.chancePirateEncounter); // return if random num between 1 and 100 lies withing percentage
    // TODO transition to pirate encounter event
}

inline int station_returnFuelCostTo(Station current, Station target)
{
    int xDiff = target.xPos - current.xPos;
    int yDiff = target.yPos - current.yPos;
    xDiff *= xDiff;
    yDiff *= yDiff;
    return (xDiff + yDiff); // pythogoras without the square root, to punish long jumps
    // TODO dumb as fuck, change
}

// TODO write buy/sell methods
//  void station_buy()

// fills tank and charges player. returns false if payment fails
inline bool station_refuel(Ship *playerVessel)
{
    int total = STANDARD_FUEL_PRICE * (MAX_SHIP_FUEL - playerVessel->currentFuel);
    if (!player_chargePlayer(playerVessel, total)) // if payment fails
    {
        // add nothing to player tank
        return false; // return false to caller function
    }
    else
    {
        player_fuelShip(playerVessel); // fill player's tank
        return true;
    }
}

// charges player for bought stock, moves to cargo hold. Returns false if unsuccesful
bool station_buy(Ship *playerVessel, Stock *boughtCargo)
{
    u16 amountBought = boughtCargo->quantity;
    u16 unitPrice = playerVessel->currentPos.stationSupply[boughtCargo->item.ID].item.price;                          // lookup local price of commodity
    bool enoughAvailable = playerVessel->currentPos.stationSupply[boughtCargo->item.ID].quantity - amountBought >= 0; // check if station has enough
    u32 total = unitPrice * amountBought;
    if (enoughAvailable && player_addCargo(playerVessel, *boughtCargo) && player_chargePlayer(playerVessel, total)) // TODO fix conflicting order of operations (i.e adding cargo without charging)
    {
        // TODO change quantity of station supply here
        // DEBUG check
        return true;
    }
    else
    {
        return false;
    }
}

// pays player for sold stock, moves from cargo hold
void station_sell(Ship *playerVessel, Stock *soldCargo)
{
    u16 amountSold = soldCargo->quantity;
    u16 unitPrice = playerVessel->currentPos.stationSupply[soldCargo->item.ID].item.price;
    u32 total = unitPrice * amountSold;
    if (player_removeCargo(playerVessel, *soldCargo))
    {   
        // TODO add sold commodity to station supply
        player_payPlayer(playerVessel, total);
    }
}