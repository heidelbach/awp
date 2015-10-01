#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roll_dice.h"

int requestCount(char *const question)
{
    int ret;
    while (1)
    {
        printf("%s: ", question);
        fflush(stdin);
        if (scanf("%d", &ret) > 0)
        {
            if (ret < 0)
            {
                fprintf(stderr, "Bitte positive Zahl eingeben\n");
                continue;
            }
            return ret;
        }
    }
}

enum parse_state
{
    INIT, MINUS, ERROR
};

void print_table(int *const *const results, int const player)
{
    printf(" \\ ");
    for (int i_player = 0; i_player < player; ++i_player)
    {
        printf("%3d ", i_player + 1);
    }
    printf("| sum\n  \\");
    for (int i_player = 0; i_player < player; ++i_player)
    {
        printf("----");
    }
    printf("-----\n");
    for (int i = 1; i <= 6; ++i)
    {
        printf("%d |", i); 
        for (int i_player = 0; i_player < player; ++i_player)
        {
            printf("%3d ", results[i][i_player]);
        }
        printf("| %4d\n", results[i][player]);
    }
    printf("--+");
    for (int i_player = 0; i_player < player; ++i_player)
    {
        printf("----");
    }
    printf("+-----\nS |");
    for (int i_player = 0; i_player < player; ++i_player)
    {
        printf("%3d ", results[0][i_player]); 
    }
    printf("| ####\n\n");
}

int main(int argc, char *const *argv) 
{
    int player = -1;
    int rolls = -1;    
    // save results 1-6 at indices 1-6, sum at index 0
    int *results[7];

    // special source for randomness on linux
    unsigned char use_dev_rand = 1;
    unsigned char verbose = 0;

    // parse argv
    enum parse_state state = INIT;
    while (*(++argv) != NULL)
    {
        char *arg = *argv;
        struct flags {
            unsigned int rolls_count:1;
            unsigned int player_count:1;
        } parse_flags = { 0 };
        while (arg != NULL && arg[0] != '\0')
        {
            switch (state)
            {
                case INIT:
                    if (arg[0] == '-') 
                    {
                        state = MINUS;
                        ++arg;
                    }
                    else
                    {
                        fprintf(stderr, "Unknown arg (does not start with -)\n");
                        arg = NULL;
                        state = ERROR;
                    }
                    break;
                case MINUS:
                    switch (arg[0])
                    {
                        case 'h':
                            fprintf(stderr, "[-r|-R] [-n <rolls>] [-p <player>]\n");
                            fprintf(stderr, "%s\n%s\n%s\n", 
                                    "-R enables use of /dev/random\n   This is the default case\n",
                                    "-r disables use of /dev/random\n",
                                    "-v prints more details\n");
                            return 0;
                        case 'v':
                            verbose = 1;
                            ++arg;
                            break;
                        case 'p':
                            parse_flags.player_count = 1;
                            ++arg;
                            if (*arg != '\0')
                            {
                                fprintf(stderr, "Invalid argument %s\n",
                                        *argv);
                                state = ERROR;
                            } 
                            arg = NULL;
                            break;
                        case 'r':
                            use_dev_rand = 0;
                            ++arg;
                            break;
                        case 'R':
                            use_dev_rand = 1;
                            ++arg;
                            break;
                        case 'n':
                            parse_flags.rolls_count = 1;
                            ++arg;
                            if (*arg != '\0')
                            {
                                fprintf(stderr, "Invalid argument %s\n",
                                        *argv);
                                state = ERROR;
                            } 
                            arg = NULL;
                            break;
                        default:
                            fprintf(stderr, "Unknown arg %s (!= n)\n", *argv);
                            arg = NULL;
                            state = ERROR;
                    }
                    break;
                case ERROR:
                    arg = NULL;
                    break;
                default:
                    fprintf(stderr, "Unknown arg %s\n", *argv);
                    arg = NULL;
                    state = ERROR;
            }
        }
        if (state == MINUS)
        {
            if (parse_flags.rolls_count)
            {
                parse_flags.rolls_count = 0;
                char *arg = *(++argv);
                if (arg == NULL)
                {
                    fprintf(stderr, "Invalid argument\n");
                    state = ERROR;
                }
                rolls = atoi(arg);
            }
            else if (parse_flags.player_count)
            {
                parse_flags.player_count = 0;
                char *arg = *(++argv);
                if (arg == NULL)
                {
                    fprintf(stderr, "Invalid argument\n");
                    state = ERROR;
                }
                player = atoi(arg);
            }
        }
        if (state == ERROR)
            return 0;
        state = INIT;
    }

    if (player < 0)
        player = requestCount("Wieviele Spieler sollen mitspielen");
    if (rolls < 0)
        rolls = requestCount("Wieviele Wuerfe pro Spieler");
    roll_dice_init();

    // allocate memory
    for (int i = 0; i <= 6; ++i)
    {
        // reserve space for <player> players and last row for the sum
        results[i] = (int *) malloc(sizeof (int) * (player + 1));
        if (!results[i]) 
        {
            fprintf(stderr, "Out of memory\nAborted\n");
            return 2;
        }
        
        // initialize allocated memory
        // memset(results[i], 0, sizeof(int) * (player + 1));
        // for (int j = 0; j < player; ++j)
        //     results[i][j] = 0;
    }

    // initialize allocated memory
    for (int i = 0; i <= 6; ++i)
    {
        memset(results[i], 0, sizeof(int) * (player + 1));
    }
    // for experts why does
    // memset((void *) results, 0, sizeof(int) * (player + 1) * 6);
    // not work

    // throw the dice
    for (int i = 0; i < rolls; ++i)
    {   
        for (int i_player = 0; i_player < player; ++i_player)
        {
            int result = roll_dice(use_dev_rand);
            ++results[result][i_player]; // register for invidual player
            ++results[result][player]; // register for sum per result
            ++results[0][i_player]; // register for sum per player
        }
        if (verbose) {
            printf("\nNach %d Wuerfen\n", i + 1);
            print_table(results, player);
        }
    }

    // print results
    printf("\nErgebnisse fuer %d Versuche\n\n", rolls);
    print_table(results, player);
    
    // free allocated memory
    for (int i = 0; i <= 6; ++i)
    {
        free(results[i]);
    }
    return 0;
}
