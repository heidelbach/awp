/*
 * Author: Johannes Heidelbach
 *
 * This simulates a simple calculator. 
 * Input: 1 operator and 2 operands
 * Output: Result of operation
 *
 * Runs in endless loop unless operator 0 is entered
 */

#include "io.h"

#include <iostream>

static void printIntroduction()
{
	std::cout << "\rTaschenrechner by Johannes\n"
			<< "--------------------------\n"
			<< "Supported Operations:\n\n"
			<< "+ ADD\n"
			<< "- SUB\n"
			<< "* MUL\n"
			<< "/ DIV\n\n"
			<< "% MOD\n\n"
			<< "& AND\n"
			<< "|  OR\n"
			<< "^ XOR\n"
			<< "\n"
			<< "0 EXIT"
			<< std::endl;
}

static int loop()
{
	char op;
	double a, b, result;

	bool valid = true;

	op = getChar("\nBitte Operand eingeben: ");

	switch (op)
	{
		// valid operators
		// Optimization: You could assign the later to be peformed function by
		// pointers here already. But 2 switch-case should be faster than one
		// function call.
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '|':
		case '&':
		case '^':
			break;

		// terminate
		case '0':
			std::cout << "\rEXIT" << std::endl;
			valid = false; // Do not perform an operation
			op = 0;
			break;

		// invalid operator
		default:
			std::cerr << "\rUngueltige Operation " << op
					<< "\n" << std::endl;
			valid = false; // Do not perform an operation
			printIntroduction();
			op = 1;
	}
	if (valid)
	{
		a = getDouble("\rBitte Zahl A eingeben: ");
		b = getDouble("\rBitte Zahl B eingeben: ");

		switch (op)
		{
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				// Exception DIV/0
				if (b == 0)
				{
					/* Do not perform an operation
					 * Output error message, division by zero
					 */
					valid = false; 
					std::cerr << "\nDivision by 0 !\n" << std::endl;
				}
				else
				{
					result = a / b;
				}
				break;
			case '%':
				result = ((long) a) %  ((long) b);
				break;
			case '|':
				result = ((long) a) | ((long) b);
			case '&':
				result = ((long) a) & ((long) b);
				break;
			case '^':
				result = ((long) a) ^ ((long) b);
				break;
		}
	}
	if (valid)
	{
		std::cout << "\n" << a << " " << op << " " << b << " = "
				 << result << std::endl;
	}
	return op;
}

int main()
{
	printIntroduction();
	while(loop())
		;
	return 0;
}
