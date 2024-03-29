#ifndef DICE_H
#define DICE_H


typedef struct {
    const char* dice_type;
    int max_value;
} Dice;


int throw_dice(Dice dice);
int throw_dices(Dice* dices, int size);
int calculate_average_throw(int dice_num, const Dice* dice);

#endif
