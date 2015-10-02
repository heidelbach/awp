/*
 * Written by johannesheidelbach@gmail.com
 *
 * This library contains all needed functions for generating random numbers
 * depending on the count of dices
 */

unsigned short roll_dices(unsigned char use_dev_rand, unsigned short max, unsigned short min);

#define roll_dice(use_dev_rand) roll_dices(use_dev_rand, 6, 1)

void roll_dice_init();
