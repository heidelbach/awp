#include "operator.h"
#include "addOperator.h"
#include "subOperator.h"
#include "multOperator.h"
#include "divOperator.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>

#include <iostream>

#define BUF_SIZ 0x100

static char inBuffer[BUF_SIZ];
static char *inBufferPtr;
static OP **operatorStack;
static unsigned int operatorStackPtr;

static void reset()
{
	memset(inBuffer, 0, BUF_SIZ);
	inBufferPtr = inBuffer;
	int c = 0;
	while (c != '\n' || c < 0)
		c = getchar();	
	if (operatorStackPtr == 0)
		return;
	while(--operatorStackPtr)
		delete operatorStack[operatorStackPtr];
	operatorStack[operatorStackPtr] = 0;
}	

static void handler(int signal)
{
	switch(signal) {
		case SIGTERM:
			printf("\b\bcaught SIGTERM - Terminating\n");
			fclose(stdin);
			while(getchar() >= 0);
			if (operatorStackPtr != 0)
				while(--operatorStackPtr)
					delete operatorStack[operatorStackPtr];
			raise(9);
			break;	
		case SIGINT:
			if (operatorStackPtr == 0 && inBufferPtr == inBuffer) {
				raise(SIGTERM);
			} else {
				printf("\b\bcaught SIGINT - Reset\n");
				reset();
			}
			break;
	}
}

static void init()
{
	operatorStack = (OP **) malloc(BUF_SIZ * sizeof(OP *));
	printf("This Calculator uses polnish notation\n");
	printf("To add 4 and 3 you have to enter + 4 3\n");
	printf("Supported Operations:\n");
	printf("+ SUM\n- DIFF\n* MUL\n\\ DIV\n");
	signal(SIGTERM, handler);
	signal(SIGINT, handler);
	operatorStackPtr = 0;
	memset(inBuffer, 0, BUF_SIZ);
	inBufferPtr = inBuffer;
}

static void popIn()
{
	if (inBufferPtr == inBuffer)
		return;
	char digits[100];
	char *dec = NULL;
	char *digPtr = digits;
	unsigned int digPtrD;
	while (inBufferPtr-- != inBuffer) {
		char c = *inBufferPtr;
		if (c == 0)
			break;
		if (c == '.') {
			if (dec != NULL) {
				fprintf(stderr, "\nInvalid number multiple .\n");
				raise(SIGINT);
				return;
			}
			digPtrD = digPtr - digits;
			dec = (char *) malloc(digPtrD);
			memcpy(dec, digits, digPtrD);
			digPtr = digits;
			continue;
		}
		*digPtr = c - '0';
		digPtr++;
	}
	inBufferPtr = inBuffer;
	if (dec == NULL) {
		long v = 0;
		char *digPtr0 = digits;
		while(digPtr0 != digPtr) {
			v = v * 10 + *digPtr0;
			digPtr0++;
		}
		operatorStack[operatorStackPtr++] = new NumOperator(v);
	} else {
		double v = 0;
		char *digPtr0 = (char*) (dec + digPtrD);
		while(--digPtr0 != dec) {
			v = v / 10 + *digPtr0 / 10.0;
		}
		digPtr0 = digits;
		while(digPtr0 != digPtr) {
			v = v * 10 + *digPtr0;
			digPtr0++;
		}
		operatorStack[operatorStackPtr++] = new NumOperator(v);
	}
}

static void popOp()
{
	popOp_loop: if (operatorStackPtr < 2)
		return;
	OP *op0 = operatorStack[operatorStackPtr - 1];
	OP *op1 = operatorStack[operatorStackPtr - 2];
	OP *op1R = op1->cat(op0);
	if (op1R == NULL) {
		return;
	} else {
		if (op1 != op1R) {
			delete op1;
		}
		operatorStack[--operatorStackPtr - 1] = op1R;
	}
	goto popOp_loop;
}

static void loop()
{
	char c;
	loopStart:
	if (operatorStackPtr == 1) {
		NumOperator *num = (NumOperator *) *operatorStack;
		if (num != NULL && num->myMagicNum == magicNUM) {
			std::cout << "= " << num << std::endl;
			return;
		}
	} else {
		NumOperator *num = (NumOperator *) *operatorStack;
		if (num != NULL && num->myMagicNum == magicNUM) {
			std::cerr << "Syntax Error" << std::endl;
			raise(SIGINT);
		}
	}
	c = getchar();
	
	switch (c) {
		case '+':
			operatorStack[operatorStackPtr++] = new AddOperator();
			break;
		case '*':
			operatorStack[operatorStackPtr++] = new MultOperator();
			break;
		case '-':
			operatorStack[operatorStackPtr++] = new SubOperator();
			break;
		case '/':
			operatorStack[operatorStackPtr++] = new DivOperator();
			break;
		case '.':
			*inBufferPtr = c;
			++inBufferPtr;
			break;
		case '\n':
		case ' ':
			popIn();
			popOp();
			break;
		default:
			if (c < 0x10)
				break;
			else if (c < '0' || c >'9') {
				fprintf(stderr, "Unknown input %c (%x)", c, c);
				raise(SIGTERM);
			} else {
				*inBufferPtr = c;
				inBufferPtr++;
			}
	}
	goto loopStart;
}

int main()
{
	init();
	loop();
	return EXIT_SUCCESS;
}
