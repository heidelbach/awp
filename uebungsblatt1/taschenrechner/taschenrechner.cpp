#include <cmath>
#include <iostream>

static bool getInput(float *a, float *b)
{
	std::cout << "\rPlease enter a: ";
	std::cout.flush();
	std::cin >> *a;
	std::cout << "\rPlease enter b: ";
	std::cout.flush();
	std::cin >> *b;
	return true;
}

static void display(float a, float b)
 {
	float sum = a + b;
	float diff = a - b;;
	float prod = a * b;
	float div;

	if (b != 0)
		div = a / b;

	std::cout << '\r';
	for (int i = 0; i < 40; ++i)
		std::cout << '-';
	std::cout << std::endl;

	std::cout << "a = ";
	std::cout << a;
	std::cout << "\nb = ";
	std::cout << b << "\n";
	for (int i = 0; i < 40; ++i)
		std::cout << '-';
	std::cout << "\na + b = " << sum;
	std::cout << "\na - b = " << diff;
	std::cout << "\na * b = " << prod;
	std::cout << "\na / b = ";
	if (b == 0)
		std::cout << "NAN <- DIV / 0!" << std::endl;
	else
		std::cout << div << std::endl;
}

int main()
{
	float a, b;
	if (!getInput(&a, &b)) {
		printf("\n ABORTED \n");
		return 0;
	}
	display(a, b);
	return 0;
}
