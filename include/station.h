#ifndef STATION_H
#define STATION_H

#include "commodity.h"

typedef struct station
{   
    u16 xPos;
    u16 yPos;
    char name[8]; // name has a maximum of 8 chars
    bool hasPirates;
    u8 chancePirateEncounter; // chance of pirate encounter
    u8 chancePoliceEncounter; // chance of police inspection
    // unsigned 8bits since values are percentages
    Stock stationSupply[10]; // station's commodities
} Station;

extern const u16 MAX_STATION_NUM;


void station_initStationArr(Station stationArr[]);
void station_fillInfo(Station *station);
void station_setPosition(Station *station, int xPos, int yPos);
bool station_encounteredPolice(Station arrivalStation);
bool station_encounteredPirates(Station arrivalStation);
int station_returnFuelCostTo(Station current, Station target);


#endif