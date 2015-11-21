
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum mode {
	DEG2RAD, RAD2DEG
};

static int getMode()
{
	int c;
	printf("Please chose the mode\n");
	printf("1: DEG -> RAD\n");
	printf("2: RAD -> DEG\n");
	loop: c = getchar();	
	if (c < 0)
		return -1;
	if (c < 0x20)
		goto loop;
	
	switch (c) {
		case '1':
			return DEG2RAD;
		case '2':
			return RAD2DEG;
	}
	printf("\rOption %c is invalid\n", c);
	goto loop;
}

int main()
{
	int mode, read;
	double value;
	loop: mode = getMode();
	if (mode < 0)
		return EXIT_SUCCESS;
	printf("\rEnter the %s to convert to %s\n", mode == DEG2RAD ? "DEG" : "RAD", mode == DEG2RAD ? "RAD": "DEG");
	read = scanf("%lf", &value);
	if (read < 0)
		return EXIT_SUCCESS;
	else if (read == 0) {
		fprintf(stderr, "Invalid input\n");
		goto loop;
	}
	if (mode == RAD2DEG) {
		printf("\r%lf RAD = %lf PI = %lf DEG\n", value, value / M_PI, value / M_PI * 180.0);
	} else if (mode == DEG2RAD) {
		printf("\r%lf DEG = %lf RAD = %lf PI\n", value, value * M_PI / 180.0, value / 180.0);
	}
	goto loop;
}
