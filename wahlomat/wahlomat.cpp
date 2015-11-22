#include "vote.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

static const unsigned int MAX_VOTES = 2;
static const unsigned int WIDTH = 40;

static const char rightAndLeftChar = (char) 0xba;
static const char topRightChar = (char) 0xbb;
static const char bottomRightChar = (char) 0xbc;
static const char bottomLeftChar = (char) 0xc8;
static const char topLeftChar = (char) 0xc9;
static const char topAndBottomChar = (char) 0xcd;
static const char charUE = (char) 0x81;


static unsigned int getVotes(Vote **votesPtr, unsigned int max)
{
	unsigned int voteCount = 0;
	unsigned int sum = 0;
	Vote *votes = *votesPtr;
	*votesPtr = NULL;
	votes = NULL;
	while(voteCount < max) {
		unsigned int count;
		int length = printf("\rStimmen f%cr Kandidat %d: ", charUE, voteCount + 1);
		if (scanf("%d", &count) < 0) {
			printf("\r");
			while(length-- > 0)
				printf(" ");
			break;
		}
		if (sum + count < sum) {
			fprintf(stderr, "\rDie Gesamtzahl der Stimmen ist zu groß.\n");
			continue;
		}
		if (votes == NULL) {
			votes = new Vote();
			*votesPtr = votes;
		} else {
			Vote *next = new Vote();
			votes->setNext(next);
			votes = next;
		}
		if (votes == NULL) {
			// TODO error message
			abort();
		}
		votes->setCount(count);
		sum += count;
		++voteCount;
	}
	return sum;
}

static void calculate(Vote *votes, unsigned int sum)
{
	Vote *ptr = votes;
	while (ptr != NULL) {
		ptr->percentOf(sum);
		ptr = ptr->getNext();
	}
}

static void display(Vote *votes)
{
	Vote *ptr = votes;
	int count = -1;
	char line[WIDTH+1];
	
	std::cout << "\r" << topLeftChar;
	while (++count < WIDTH) {
		std::cout << topAndBottomChar;
	}
	std::cout << topRightChar << std::endl;
	count = WIDTH - 2 - sprintf(line, "Ergebnis der Abstimmung");
	std::cout << rightAndLeftChar;
	for (int i = (count+1) / 2; i >= 0; --i) {
		std::cout << " ";
	}
	std::cout << line;
	for (int i = count / 2; i >= 0; --i) {
		std::cout << " ";
	}
	std::cout << rightAndLeftChar << std::endl;
	count = 0;
	if (ptr == NULL) {
		char *emptyLine[2] = {"", "Keine abgebenen Stimmen"};
		for (int linePtr = 0; linePtr < 2; ++linePtr) {
			int count = WIDTH - 2 - sprintf(line, emptyLine[linePtr] );
			std::cout << rightAndLeftChar;
			for (int i = (count+1) / 2; i >= 0; --i) {
				std::cout << " ";
			}
			std::cout << line;
			for (int i = count / 2; i >= 0; --i) {
				std::cout << " ";
			}
			std::cout << rightAndLeftChar << std::endl;
		}
	}
	while (ptr != NULL) {
		sprintf(line, "   Kandidat %2d hat %6.2f%% der Stimmen  ", ++count, ptr->getPercent());
		std::cout << rightAndLeftChar << line << rightAndLeftChar << std::endl;
		ptr = ptr->getNext();
	}
	count = -1;
	std::cout << bottomLeftChar;
	while (++count < WIDTH) {
		std::cout << topAndBottomChar;
	}
	std::cout << bottomRightChar << std::endl;
	return;
}

static void free(Vote *votes)
{
	while(votes != NULL) {
		Vote *v = votes;
		votes = votes->getNext();
		delete(v);
	}
}

int main(int argc, char **argv)
{
	Vote *votes;
	unsigned int max = MAX_VOTES;
	for (int c = 1; c < argc - 1; ++c) {
		if (argv[c][0] == '-' && argv[c][1] == 'n') {
			max = atoi(argv[++c]);
		}
	}
	unsigned int sum = getVotes(&votes, max);
	calculate(votes, sum);
	display(votes);
	free(votes);

	getchar(); // 0x07
	getchar();
	return 0;
}
