#ifndef COMMODITY_H
#define COMMODITY_H

typedef struct commodity
{
    char *name;  // length 13 since longest name
    bool isIllegal; // legality status
    int price;      // standard price
} Commodity;

#endif