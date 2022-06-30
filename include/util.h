#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

typedef struct
{
    bool isVowel;
    char character;
} Letter;

bool util_getRandomBool();
void util_insertRandomName(char nameArr[], int arrLen);
char util_getRandomVowel();
char util_getRandomConsonant();

void util_waitSeconds(unsigned int sec);

#endif