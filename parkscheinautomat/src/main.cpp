#include "automat.h"

#include <string.h> // for strcmp()
#include <cstdlib>
#include <cstdio>

#define DEFAULT_PRICE 0.5
#define DEFAULT_TICK 15

static char *const HELP_KEY = "help";
static char *const COST_KEY = "price";
static char *const TICK_KEY = "ticks";

struct params
{
	double price = DEFAULT_PRICE;
	unsigned int tick = DEFAULT_TICK;
};

static void printHelp()
{
	printf("Usage:\n");
	printf("automat [-h | --%s] [-t | --%s] [-p | --%s]\n",
			HELP_KEY, TICK_KEY, COST_KEY);
	printf("\n%s:\n", HELP_KEY);
	printf("\tPrints this help and exit\n");
	printf("\n%s:\n", TICK_KEY);
	printf("\tSets the duration of each ticks to duration\n");
	printf("\n%s:\n", COST_KEY);
	printf("\tSets the price to pay for each tick\n");
}

static double parseCosts(char **argv)
{
	// TODO
	return DEFAULT_PRICE;
}

static unsigned int parseTicks(char **argv)
{
	// TODO
	return DEFAULT_TICK;
}

static struct params *parse(char **argv)
{
	char *key;
	while (1) {
		char *arg = *++argv;
		if (arg == NULL)
			break;
		if (*arg == '-') {
			key = arg + 1;		
			if (*key == '-') {
				if (!strcasecmp(key + 1,
HELP_KEY)) {
					printHelp();
					return NULL;
				} else if (!strcasecmp(key + 1,
COST_KEY)) {
					parseCosts(++argv);
				} else if (!strcasecmp(key + 1,
TICK_KEY)) {
					parseTicks(++argv);
				} else {
					printHelp();
					return NULL;
				}
			} else if (!strcasecmp(key, "h")) {
				printHelp();
				return NULL;
			} else if (!strcasecmp(key, "t")) {
				parseTicks(++argv);
			} else if (!strcasecmp(key, "p")) {
				parseCosts(++argv);
			} else {
				printHelp();
				return NULL;
			}
		}
	}
}

/**
 * Initiates the automat depending on the parameters
 */
static Automat *init(int argc, char **argv)
{
	double price;
	unsigned int tick;
	if (argc == 1) {
		price = DEFAULT_PRICE;
		tick = DEFAULT_TICK;
	} else {
		struct params *p = parse(argv);
		if (!p) {
			// exit
			return NULL;
		}
		price = p->price;
		tick = p->tick;
		free(p);
	}
	return new Automat(price, tick);
		
}

int main(int argc, char **argv) {
	Automat *automat = init(argc, argv);
	if (automat) {
		printf("Automat initialized\n");
		// TODO do some action
		delete automat;
	}
	return EXIT_SUCCESS;
}
