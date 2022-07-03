#ifndef COMMODITY_H
#define COMMODITY_H

typedef struct commodity
{   
    u8 ID; // 8bit since commodity ID won't even surpass 100
    char *name;  // length 13 since longest name
    bool isIllegal; // legality status
    int price;      // standard price
} Commodity;

typedef struct stock
{   
    Commodity item;
    u16 quantity;
} Stock;

extern const u8 NUM_COMMODITY_TYPES;

Commodity commodity_getCommodity(u8 commodityId);
void commodity_applyFluctuation(Commodity *commodity, u8 maxFluxPercentage);
void commodity_setPrice(Commodity *commodity, u16 newPrice);

#endif