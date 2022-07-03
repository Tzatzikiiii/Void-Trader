#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

typedef struct
{
    bool isVowel;
    char character;
} Letter;

void util_setSeed(u32 newSeed);
u32 util_getRandomInRange(u32 min, u32 max);
bool util_getRandomBool();
void util_waitSeconds(unsigned int sec);
void util_insertRandomName(char nameArr[], int arrLen);

#endif