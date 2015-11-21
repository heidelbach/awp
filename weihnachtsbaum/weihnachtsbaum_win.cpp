/* ****************************************************************************
 * Ersteller: Johannes Heidelbach
 * Version:   2014.12.28 12:40
 * Gibt auf verschiedene Arten ASCII-Weihnachtsbäume aus
 * Halb portable Version - Betriebssystem spezifische Aufrufe auf Windows bzw
 * Linux mittels Präprozessor
 * ****************************************************************************/

#include <cstdio>
#include <cstdlib>

#include <conio.h>
#include <windows.h>


/* 
 * The different types of output to avoid numeric constants in the actual
 * source code
 */
enum mode_e {
	STUMP=0, SINGLE_SIDED, WO_STUMP, FULL, FANCY, EXIT
};

static HANDLE const console = GetStdHandle(STD_OUTPUT_HANDLE);

/*
 * Asks the user for the type of the output
 * returns EXIT if program shall exit
 */
static unsigned int getMode();

/*
 * Asks the user for the height of the output
 * returns 0 if program shall exit
 */
static unsigned int getHeight(unsigned int mode);

/* 
 * Prints height X on the screen
 */
static void drawStump(unsigned int height);

/*
 * Prints the output needed for full shape but non aligned
 */
static void drawSingle(unsigned int height);

/*
 * Prints the simple shape but without a stump
 */
static void drawWOStump(unsigned int height);

/*
 * Prints a fully colored fancy christmas tree
 */
static void drawFancy(unsigned int maxHeight)

/*
 * Prints the full shape including the stump
 */
static void drawFull(unsigned char height);

/*
 * Prints one element of the fancy tree
 */
static void printElement();

/*
 * helper function for drawFancy
 */
static unsigned int getMaxWidth(unsigned int maxHeight,  unsigned int heightStep, unsigned int loss);

// OS-specific functions
void printRed(char c);

void printGreen(char c);

void printBrown(char c);

void printYellow(char c);

void printBlue(char c);

int main() 
{
	// clear console
	system("cls");

	// Output of colors available with background always black on Windows
	/*
	for (int colour = 0x00; colour <= 0x0f; colour ++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour);
		printf("Using colour: %02x\n", colour);
	}
	*/

	while(1) {
		unsigned int mode = getMode();
		if (mode == EXIT) {
			// some error occured or user want to terminate program
			// -> exit
			break;
		}
		unsigned int height = getHeight(mode);
		if (height == 0) {
			break; // some error occured -> exit
		}
		switch (mode) {
			case STUMP: 
				drawStump(height);
				break;
			case SINGLE_SIDED:
				drawSingle(height);
				break;
			case WO_STUMP:
				drawWOStump(height);
				break;
			case FULL:
				drawFull(height);
				break;
			case FANCY:
				drawFancy(height);
				break;
			default: // should never be the case
				fprintf(stderr, "\rInvalid mode\n");
		}
		printf("\n\n");
	}

	return EXIT_SUCCESS;
}

/*
 * Asks the user for the type of the output
 * returns EXIT if program shall exit
 */
static unsigned int getMode()
{
	unsigned int modus = EXIT + 1;
	while(1) {
		printf("Wahl des Modus\n");
		printf("%d: nur Stamm\n", STUMP);
		printf("%d: eine Seite\n", SINGLE_SIDED);
		printf("%d: ohne Stamm\n", WO_STUMP);
		printf("%d: komplett\n", FULL);
		printf("%d: komplett in Farbe\n", FANCY);
		printf("%d: Programm beenden\n", EXIT);
		printf("Welche Art soll ausgeben werden: ");
		if (scanf("%d", &modus) < 0) {
			// stdin closed
			printf("\rTerminating\n");
			return EXIT;
		} else if (modus <= EXIT) {
			return modus;
		}
	}
}

/*
 * Asks the user for the height of the output
 * returns 0 if program shall exit
 */
static unsigned int getHeight(unsigned int mode)
{
	unsigned int const max = mode == FANCY ? 76 : 40, min = 5;
	unsigned int value = 0;
	if (mode == EXIT)
		return 0;
	while (1) {
		printf("Hoehe des Baums (%d - %d): ", min, max);
		if (scanf_s("%d", &value) < 0) {
			// stdin closed
			return 0;
		}
		if (value < min || value > max) {
			printf("\rZahl ausserhalb der Grenzen\n");
			value = 0;
		} else {
			return value;
		}
	}
	
}

/* 
 * Prints height X on the screen
 */
static void drawStump(unsigned int height)
{
	while (height--)
		printf("X\n");
}

/*
 * Prints the simple shape but without a stump
 */
static void drawWOStump(unsigned int height)
{
	int padding = height;
	while (padding--) {
		for (int i = 0; i++ < padding; printf(" "));	
		for (int i = height; --i > padding; printf("XX"));	
		printf("X\n");	
	}
}

/*
 * Prints the output needed for full shape but non aligned
 */
static void drawSingle(unsigned int height)
{
	unsigned int i = height;
	while(i--) {
		for (int j = height; --j > i; printf("XX"));	
		printf("X\n");	
	}
}

/*
 * Prints the full shape including the stump
 */
static void drawFull(unsigned char height)
{
	// we have something to print the shape already - reuse it
	drawWOStump(height);

	// the stump
	for (int i = height / 3; i--; ) {
		for (int h = height; --h; printf(" "));
		printf("H\n");
	}
	for (int h = height; --h; printf(" "));
	printf("H");
}

/*
 * Prints a fully colored fancy christmas tree
 */
static void drawFancy(unsigned int maxHeight)
{
	unsigned int const heightStep = 6;
	unsigned int const loss = 2;
	unsigned int const maxWidth = getMaxWidth(maxHeight, heightStep, loss);
	unsigned int height = -1, width = 0;
	
	while (++height < maxHeight) {
		if (height % heightStep == heightStep - 1) {
			width -= loss;
		} else {
			++width;
		}
		// align
		for (unsigned int i = maxWidth; i-- > width; printf(" "));
		// output a line of the actual tree 
		for (unsigned int i = width; --i; ) {
			printElement();
			printElement();
		}
		printElement();
		printf("\n");
	}
	// output the stump
	for (unsigned int i = 0; i++ < height / heightStep;) {
		// align
		for (unsigned int j = 0; ++j < maxWidth; printf(" "));
		// and output the actual tree
		printBrown('H');
		printf("\n");
	}
	// align
	for (unsigned int j = 0; ++j < maxWidth; printf(" "));
	printBrown('H');
}

/*
 * Prints one element of the fancy tree
 */
static void printElement()
{
	const float color = rand() / (float) RAND_MAX;
	// dirty trick to avoid same elements next to each other
	static unsigned int last = 0; 
	if (last < 9 && color > 0.85) {
		last = 9;
		printYellow('1');
	} else if (last < 8 && color > 0.77) {
		last = 8;
		printRed('O');
	} else if (last < 7 && color > 0.7) {
		last = 7;
		printBlue('O');
	} else {
		last = 1;
		printGreen('X');
		
	}
}

/*
 * helper function for drawFancy
 */
static unsigned int getMaxWidth(unsigned int maxHeight,  unsigned int heightStep, unsigned int loss) 
{
	
	unsigned int max = 0;
	unsigned int width = 0;
	unsigned int iter = 0;
	while (maxHeight--) {
		if (++iter == heightStep) {
			iter = 0;
			width -= loss;
		} else if (max < ++width) {
			max = width;
		}
	}
	return max;
}

// OS-specific functions
void printRed(char c)
{
	SetConsoleTextAttribute(console, 0x0c);
	cprintf("%s", c);
	SetConsoleTextAttribute(console, 0x0);
}

void printGreen(char c)
{
	SetConsoleTextAttribute(console, 0x02);
	cprintf("%s", c);
	SetConsoleTextAttribute(console, 0x0);
}

void printBrown(char c)
{
	SetConsoleTextAttribute(console,0x06); 
	cprintf("%s", c);
	SetConsoleTextAttribute(console, 0x0);
}

void printYellow(char c)
{
	SetConsoleTextAttribute(console, 0x0e);
	cprintf("%s", c);
	SetConsoleTextAttribute(console, 0x0);
}

void printBlue(char c)
{
	SetConsoleTextAttribute(console, 0x09);
	cprintf("%s", c)
	SetConsoleTextAttribute(console, 0x0);
}