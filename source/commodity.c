#include <stdbool.h>
#include <string.h>

#include <tonc.h>

#include "commodity.h"
// ------------------------------------------------------------- includes

const char *COMMODITY_NAMES[39] = {
    "Medicine", "Optics", "Conductors", "Gears", "Hydraulics", "Tires", "Tools", "Batteries", // technology 0-7
    "Weapons", "Ammunition", "Explosives", "Drugs",                                           //  illeal contraband 8-11
    "Scrap", "Copper", "Iron", "Silver", "Aluminium", "Gold", "Platinum", "Tungsten",         // metals 12-19
    "Helium", "Oxygen", "Fertilizer", "Fuel", "Dysinfectant",                                 // chemicals 20-24
    "Fruits", "Spices", "Fish", "Cattle", "Meat", "Seeds", "Rocks", "Wood", "Ice",            // natural resources 25-33
    "Clothing", "Furniture", "Luxury Items", "Wine", "Sweets"                                 // consumer items 34-38
};

const u16 COMMODITY_PRICES[39] = {
    // (prices in no way realistic, literally unbothered)
    500, 750, 400, 300, 580, 340, 405, 425,     // 0-7
    900, 565, 855, 1135,                        // 8-11
    200, 400, 500, 550, 850, 1200, 2300, 1825,  // 12-19
    600, 150, 620, 400, 320,                    // 20-24
    135, 300, 335, 525, 265, 100, 60, 220, 120, // 25-33
    240, 715, 485, 725, 145                     // 34-38
};

Commodity commodity_getCommodity(u8 commodityId) {
    Commodity newCommodity;
    if (commodityId >= 8 && commodityId <= 11) {
        newCommodity.isIllegal = true; // illegal if contraband
    } else 
    {
        newCommodity.isIllegal = false;
    }

    strcpy(newCommodity.name, COMMODITY_NAMES[commodityId]); // copy commodity name
    newCommodity.price = COMMODITY_PRICES[commodityId];

    return newCommodity;
}