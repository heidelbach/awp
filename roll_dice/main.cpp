#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "roll_dice.h"
#include "index.h"

int requestCount(char *const question)
{
    int ret;
    while (1)
    {
        fprintf(stderr, "\r%s: ", question);
        fflush(stdout);
        int read;
        if ((read = scanf("%d", &ret)) > 0)
        {
            fprintf(stderr, "\r");
            if (ret < 0)
            {
                fprintf(stderr, "Bitte positive Zahl eingeben\n");
                continue;
            }
            return ret;
        }
        else if (read == 0)
            while (getchar() != '\n')
                ;
        else
        {
            fprintf(stderr, "\nEOF -> abort\n");
            exit(1);
        }
    }
}

char *requestName(char *const question)
{
    char buffer[1024];
    char *ret;
    while (1)
    {
        fprintf(stderr, "\r%s: ", question);
        fflush(stderr);
        int read = scanf("%1023s", buffer);
        fprintf(stderr, "\r");
        if (read == 0)
            while (getchar() != '\n')
                ;
        else if (read < 0)
        {
            fprintf(stderr, "\nEOF -> abort\n");
            exit(1);
        }
        else if (strlen(buffer) == 0)
        {
            fprintf(stderr, "\ntoo short\n");
        }
        else
        {
            ret = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
            memcpy(ret, buffer, sizeof(char) * (strlen(buffer) + 1));
            return ret;
        }
    }
}

enum parse_state
{
    INIT, MINUS, ERROR
};

int main(int argc, char *const *argv)
{
    int player = -1;
    int rolls = -1;
    // save results 1-6 at indices 1-6, sum at index 0
    Index *index;

    // special source for randomness on linux
    unsigned char use_dev_rand = 1;
    // print interim results
    unsigned char verbose = 0;
    // allow duplicate results
    unsigned char duplicates = 1;
    // sort by sum
    unsigned char sort = 1;

    unsigned short max = 6;

    // parse argv
    enum parse_state state = INIT;
    while (*(++argv) != NULL)
    {
        char *arg = *argv;
        struct flags {
            unsigned int rolls_count:1;
            unsigned int player_count:1;
            unsigned int set_max:1;
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
                            fprintf(stderr, "[-r|-R] [-D] [-v] [-n <rolls>] [-p <player>] [-M <max>]\n");
                            fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n",
                                    "-R enables use of /dev/random\n   This is the default case\n",
                                    "-r disables use of /dev/random\n",
                                    "-D disables duplicate results\n",
                                    "-v prints more details\n",
                                    "-M changes maxmimum");
                            return 0;
                        case 'v':
                            verbose = 1;
                            ++arg;
                            break;
                        case 'D':
                            duplicates = 0;
                            ++arg;
                            break;
                        case 'M':
                            parse_flags.set_max = 1;
                            ++arg;
                            if (*arg != '\0')
                            {
                                fprintf(stderr, "Invalid argument %s\n",
                                        *argv);
                                state = ERROR;
                            }
                            arg = NULL;
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
                        case 'S':
                            sort = 0;
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
                            fprintf(stderr, "Unknown arg %s\n", *argv);
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
            else if (parse_flags.set_max)
            {
                parse_flags.set_max = 0;
                char *arg = *(++argv);
                if (arg == NULL)
                {
                    fprintf(stderr, "Invalid argument\n");
                    state = ERROR;
                }
                max = atoi(arg);
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
    if (!duplicates && rolls >= max)
    {
        fprintf(stderr, "Error: Duplicates disabled and max < rolls\n");
        exit(1);
    }

    roll_dice_init();


    // request names for players and initialize index
    {
        char **names = (char **) malloc(sizeof(char *) * player);
        char question[] = { "Name fuer Spieler XX" };
        for (int i = 0; i < player; ++i)
        {
            sprintf(question, "Name fuer Spieler %2d", i + 1);
            names[i] = requestName(question);
        }

        index = new Index(player, rolls, names, 1, max);
        free(names);
    }

    // throw the dice
    for (int i = 0; i < rolls; ++i)
    {
        for (int i_player = 0; i_player < player; ++i_player)
        {
            while (1)
            {
                int result = roll_dice(use_dev_rand, max);
                if (index->addRoll(i_player, i, result, duplicates == 0))
                    break;
            }
        }
        if (verbose) {
            printf("\nNach %d Wuerfen\n\033[0;33m", i + 1);
            index->printTable();
            printf("\033[0m");
        }
    }

    index->printResults();
    if (sort)
    {
        printf("========================\n");
        printf("          SORT          \n");
        index->sortBySum();
        printf("========================\n");
        index->printTable();
        index->printResults();
    }

    // free allocated memory
    delete index;
    return 0;
}
