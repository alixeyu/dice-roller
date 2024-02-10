#include <stdlib.h>
#include <time.h>
#include "dice.h"

int throw_dice(Dice dice) {
    srand(time(NULL));
    return (rand() % dice.max_value) + 1;
}


int throw_dices(Dice* dices, int size) {
    int throw_result = 0;

    for (int i = 0; i < size; i++) {
        throw_result += throw_dice(dices[i]);
    }

    return throw_result;
}
