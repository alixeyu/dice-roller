#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdlib.h>
#include "dice/dice.h"


const char* const dice_types[] = { "d4", "d6", "d8", "d10", "d12", "d20", "d100", NULL };
Dice DiceArray[] = {
    { .dice_type="d4", 4 },
    { .dice_type="d6", 6 },
    { .dice_type="d8", 8 },
    { .dice_type="d10", 10 },
    { .dice_type="d12", 12 },
    { .dice_type="d20", 20 },
    { .dice_type="d100", 100 },
};

#endif
