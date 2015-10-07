/*
 * Written by johannesheidelbach@gmail.com
 *
 * This library contains all needed functions for generating random numbers
 * depending on the count of dices
 */

unsigned short roll_dice(unsigned char use_dev_rand,
        unsigned short max = 6, unsigned short min = 1);

void roll_dice_init();
