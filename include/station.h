#ifndef STATION_H
#define STATION_H

typedef struct station
{   
    int xPos;
    int yPos;
    char name[8];
    bool hasPirates;
    u8 chancePirates; // chance of pirate encounter
    u8 chancePolice; // chance of police inspection
    // unsigned 8bits since values are percentages

} Station;


void station_fillInfo(Station newStation, int xPos, int yPos);

#endif