/*
 * Written by johannesheidelbach@gmail.com
 *
 */

#include "roll_dice.h"

#include <math.h>
#include <stdlib.h>
#ifdef __linux__
#include <stdio.h>
#include <string.h>
int ent_avail()
{
    char buffer[12];
    FILE *ent_avail_stream = fopen("/proc/sys/kernel/random/entropy_avail", "r");
    fgets(buffer, 11, ent_avail_stream);
    fclose(ent_avail_stream);
    return atoi(buffer);
}
#endif
#include <time.h>

#define RNG_MAX 0xffffffff
#define NUM_BYTES_PER_INT 8

unsigned short roll_dices(unsigned char use_dev_rand, unsigned short max, unsigned short min)
{
    unsigned int rand_byte;
    while (1)
    {
#ifdef __linux__
        if (use_dev_rand)
        {
            FILE *dev_rand = fopen("/dev/random", "r");
            int entropy_avail = ent_avail();
            if (entropy_avail)
            {
                while (entropy_avail < 1000)
                {
                    printf("\rentropy avail: %4d - Please wait", entropy_avail);
                    fflush(stdout);
                    system("sleep 0.1");
                    entropy_avail = ent_avail();
                }
                printf("\r                                 ");
            }
            rand_byte = 0;
            for (int i = 0; i < NUM_BYTES_PER_INT / 2; ++i)
            {
                int rand_byte_i = fgetc(dev_rand);
                if (rand_byte_i < 0)
                {
                    // EOF
                    return -1;
                }
                rand_byte = (rand_byte << 8) | (0xffff & rand_byte_i);
            }
        } else
#endif
            rand_byte = rand();
        if (rand_byte > (RNG_MAX / (max - min + 1)) * (max - min + 1))
            continue;
        return rand_byte % max + min;
    }
}

void roll_dice_init()
{
    srand((unsigned int) time(NULL));
}
