#include <stdio.h>
#include <stdbool.h>
#include <tonc.h>
#include <stdbool.h>

#include <seven/util/random.h>

#include "util.h"
// ------------------------------------------------------------- includes

bool util_getRandomBool()
{
    u32 randomNum = randNext();
    randomNum /= 100;
    return (randomNum % 2 == 0);
}

char util_getRandomVowel()
{
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    return vowels[(randNext() % 5)];
}

char util_getRandomConsonant()
{
    char consonants[21] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    return consonants[(randNext() % 21)];
}

void util_insertRandomName(char nameArr[], int arrLen)
{

    Letter letters[arrLen]; // tracks letters and their types.

    // TODO optimisation
    for (int arrIterator = 0; arrIterator < arrLen; arrIterator++)
    {
        int typeCheck = 0;

        if (arrIterator > 1) // ignore history on first two letters
        {
            for (int j = arrIterator - 1; j > arrIterator - 3; j--)
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
                }

                if (typeCheck == -2 || typeCheck == 3)
                {
                    break;
                }
            }
            // if 2 consonants or 3 vowels are found consecutively, permit new consonant/vowel
        }

        if (typeCheck == -2) // two cons. --> add vowel
        {
            letters[arrIterator].character = util_getRandomVowel();
        }
        else if (typeCheck == 3) // three vowels --> add cons.
        {
            letters[arrIterator].character = util_getRandomConsonant();
        }
        else if (util_getRandomBool() == true) // if both are possible, pick from 50%
        {
            letters[arrIterator].character = util_getRandomVowel();
        } else
        {
            letters[arrIterator].character= util_getRandomConsonant();
        }

        for (int copyIterator = 0; copyIterator < arrLen; copyIterator++) {
            nameArr[copyIterator] = letters[copyIterator].character;
        }
    }

    return;
}

void util_waitSeconds(unsigned int sec) // wait for specified amount of seconds
{
    for (int frameCount = 0; frameCount < sec * 60; frameCount++) // seconds * FPS = total amount of frames waited
    {
        VBlankIntrWait(); // waits for VBlank -> thus 1 frame per iteration
    }
}