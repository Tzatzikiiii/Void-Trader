#include <stdio.h>
#include <stdbool.h>
#include <tonc.h>
#include <stdbool.h>

#include <seven/util/random.h>

#include "util.h"
// ------------------------------------------------------------- includes

const char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'}; // y is treated as a vowel
const char consonants[20] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};

inline bool util_getRandomBool()
{
    u32 randomNum = randNext(); // generate random number
    randomNum /= 100; // look at 3rd from the right
    return (randomNum % 2 == 0); // return if even
}

static char util_getRandomVowel()
{   
    return vowels[(randNext() % 6)];
}

static char util_getRandomConsonant()
{
    return consonants[(randNext() % 20)];
}

void util_insertRandomName(char nameArr[], int arrLen)
{

    Letter letters[arrLen]; // tracks letters and their types.
    int typeCheck;
    bool ranBool;

    // TODO optimisation
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
        nameArr[copyIterator] = letters[copyIterator].character;
    }
    return;
}

inline void util_waitSeconds(unsigned int sec) // wait for specified amount of seconds
{
    for (int frameCount = 0; frameCount < sec * 60; frameCount++) // seconds * FPS = total amount of frames waited
    {
        VBlankIntrWait(); // waits for VBlank -> thus 1 frame per iteration
    }
}