
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

void depleteBuffer(char *buffer, const size_t bufSiz)
{
	fclose(stdin);
	while (fgets(buffer, bufSiz, stdin));
}

int scanf(unsigned int *integer)
{
	const size_t bufSiz = 1000;
	char *buffer = (char *) calloc((bufSiz + 1) * sizeof(char), sizeof(char));
	long l;
	if (buffer == NULL) {
		fprintf(stderr, "\rError allocating memory\n");
		abort();
	}
	setbuffer(stdin, buffer, sizeof(char));
	setlinebuf(stdin);
	printf("\rEnter the amount of the fields: ");
	fflush(stdout);
	if (scanf("%ld", &l) != strlen(buffer)) {
		fprintf(stderr, "\rNo valid number.\n");
		depleteBuffer(buffer, bufSiz);
		fgets(buffer, bufSiz, stdin);
		return -1;
	}
	depleteBuffer(buffer, bufSiz);
	if (l <= 0 || l > 1024) {
		fprintf(stderr, "\rOut of range.\n");
		return -2;
	}
	*integer = (unsigned int) l;
	return 0;
}

void pow2(unsigned int exp, unsigned long *result, unsigned long *sum)
{
	long result_s = 1L << (exp - 1);
	*result = (unsigned long) result_s;
	*sum = (unsigned long) (result_s << 1) - 1;
}


int main(int argc, char **argv)
{
	unsigned int fields = 0;
	if (scanf(&fields))
		return EXIT_SUCCESS;
	printf("\r==============\n %d Fields\n", fields);
	if (fields > 64) {
		if (argc == 2 && !strcmp(argv[1], "-d")) {
			double count = 1;
			for (unsigned int i = 1; i <= fields; ++i) {
				printf("Field %4d: %.10e corns\n", i, count);
				count *= 2;
			}
			if (fields == 1024)
				printf("And total:  1.7976931349e+308 corns\n");
			else
				printf("And total:  %.10e corns\n", count * 2 - 1);
		} else {
			double count = pow(2, fields - 1);
			printf("On %4dth field would be %.10e corns\n", fields, count);
			if (fields == 1024)
				printf("And total                1.7976931349e+308 corns\n");
			else
				printf("And total                %.10e corns\n", count * 2 - 1);
		}
		return EXIT_SUCCESS;
	}
	if (argc == 2 && !strcmp(argv[1], "-d")) {
		long count = 1L;
		long sum = 0L;
		for (unsigned int i = 1; i <= fields; ++i) {
			printf("Field %2d:   %19lu corns\n", i, count);
			sum |= count;
			count <<= 1;
		}
		printf("  Total :  %20lu corns\n", sum);
	} else {
		unsigned long count, sum;
		pow2(fields, &count, &sum);
		printf("On %4dth field would be  %19lu corns\n", fields, count);
		printf("And total                %20lu corns\n", sum);
	}
	return EXIT_SUCCESS;
}

