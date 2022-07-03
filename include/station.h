#ifndef STATION_H
#define STATION_H


typedef struct station
{   
    const int xPos;
    const int yPos;
    char name[8];
    bool hasPirates;
    u8 chancePirateEncounter; // chance of pirate encounter
    u8 chancePoliceEncounter; // chance of police inspection
    // unsigned 8bits since values are percentages
    //TODO add Stock to each station
} Station;


void station_fillInfo(Station *station, int xPos, int yPos);
bool encounteredPolice(Station arrivalStation);
bool encounteredPirates(Station arrivalStation);


#endif