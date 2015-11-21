
#include "numbers.h"
#include "io.h"

#include <cstdlib>

// #include <thread>

signed int *generateNumbers(signed int &);

bool loop(signed int count, signed int *toSort)
{
	if (!toSort) {
		return false;
	}
	else
	{
		sortInt(count, toSort);
		printText("\nSorted\n");
		print(count, toSort);
		
		printText("=======================\n\n");
		if (!toSort) {
			return false;
		}
		free(toSort);
		return true;
	}
}

int main(int argc, char **argv)
{
	signed int count = 0;
	// std::thread **threads;
	// unsigned int threadCount;
	// printf("%u processors are availble\nHow many threads shall be created: ", std::thread::hardware_concurrency());
	// threadCount = getInt();
	// threads = (std::thread **) malloc(sizeof(std::thread *) * threadCount);
	
	if (argc != 1)
	{
		signed int *toSort = (signed int *) malloc(sizeof(signed int) * argc);
		if (!toSort)
		{
			printError("Failed to allocate memory");
		} 
		else
		{
			count = argc - 1;
			for (int i = 0; i < count; ++i)
			{
				toSort[i] = toInt(argv[i + 1]);
			}
			loop(count, toSort);
		}
	} 
	while (loop(count, generateNumbers(count)));
	return EXIT_SUCCESS;
}

signed int *generateNumbers(signed int &count)
{	
	signed int *numbers = NULL;

	printText("Please insert the amount of numbers to sort\n");
	printText("Negative or 0 to exit: ");
	
	count = getInt();
	
	if (count > 0)
	{
		numbers = (signed int *) malloc(sizeof(signed int) * count);
	
		if (!numbers)
		{
			printError("Failed to allocate memory");
			numbers = NULL;
		} 
		else
		{
			int i = -1;
			signed int random;
			printText("\rHow many shall be randomized: ");
			random = getInt();
			if (random > count)
			{
				random = count;
			}
			while (++i < random)
			{
				numbers[i] = rand() % 9999;
				printNumf("%4d", numbers[i]);
				printText(" ");
			}
			printText("\n");
			// TODO add option to add sorted or reverse sorted list
			while (++i <= count)
			{
				printText("\rPlease enter ");
				printNumf("%3d", i);
				switch (i)
				{
				case 1:
					printText("st");
					break;
				case 2:
					printText("nd");
					break;
				default:
					printText("th");
				}
				printText(" number: ");
				numbers[i - 1] = getInt();
			}
		}
	}
	return numbers;
}
