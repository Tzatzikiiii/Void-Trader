#include <stdbool.h>
#include <tonc.h>

#include <seven/util/random.h>

#include "util.h"
// ------------------------------------------------------------- includes

const char VOWELS[6] = {'a', 'e', 'i', 'o', 'u', 'y'}; // y is treated as a vowel
const char CONSONANTS[20] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};

inline void util_setSeed(u32 newSeed) {
    randSetSeed(newSeed);
}

inline u32 util_getRandomInRange(u32 min, u32 max) {
    u32 ranNum = randNext();
    ranNum &= 0xff000000; // take only the upper 8 bits
    ranNum >> 24; // shift upper 8 bits to bottom
    return (ranNum % (max - min)) + min; // range difference + minimmum
}

inline bool util_getRandomBool() // only somwhat random but who cares
{
    u32 randomNum = randNext(); // generate random number
    return (randomNum % 2 == 0); // return if even
}

static inline char util_getRandomVowel()
{   
    return VOWELS[(randNext() % 6)];
}

static inline char util_getRandomConsonant()
{
    return CONSONANTS[(randNext() % 20)];
}

void util_insertRandomName(char nameArr[], int arrLen)
{
    Letter letters[arrLen]; // tracks letters and their types.
    int typeCheck; // used to determine number of consecutive vowels/consonants
    bool ranBool; // coin flip variable

    for (int arrIterator = 0; arrIterator < arrLen; arrIterator++)
    {
        typeCheck = 0;

        if (arrIterator > 1) // ignore history on first two letters
        {
            for (int j = arrIterator - 1; j >= arrIterator - 3; j--)
            {   
                if (j < 0) {
                    break;
                }

                if (letters[j].isVowel)
                {
                    typeCheck++;
                }
                else
                {
                    typeCheck--;
                    if (typeCheck == -2) { // if two consecutive consonants are found, end loop prematurely
                        break;
                    }
                }
            }
            // if 2 consonants or 3 vowels are found consecutively, permit new consonant/vowel
        }

        ranBool = util_getRandomBool();

        if (typeCheck == -2 || (ranBool && typeCheck != 3)) // two cons. --> add vowel
        {
            letters[arrIterator].character = util_getRandomVowel();
            letters[arrIterator].isVowel = true;
        }
        else if (typeCheck == 3 || !ranBool) // three vowels --> add cons.
        {
            letters[arrIterator].character = util_getRandomConsonant();
            letters[arrIterator].isVowel = false;
        }
    }

    for (int copyIterator = 0; copyIterator < arrLen; copyIterator++)
    {
        nameArr[copyIterator] = letters[copyIterator].character; // copy each letter into the original array
    }
    return;
}

inline void util_waitSeconds(unsigned int sec) // wait for specified amount of seconds
{
    for (int frameCount = 0; frameCount < sec * 60; frameCount++) // seconds * FPS(60) = total amount of frames waited
    {
        VBlankIntrWait(); // waits for VBlank -> thus, 1 frame per iteration
    }
}