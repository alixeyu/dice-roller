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


int calculate_average_throw(int dice_num, const Dice* dice) {
    int avg_throw = (int)(dice_num * ((double)(dice->max_value >> 1) + 0.5));
    return avg_throw;
}
