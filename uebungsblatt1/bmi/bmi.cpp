#include <iostream>

int main()
{
	float height;
	float normal_weight;
	float ideal_weight;
	while (true) {
		std::cout << "Please enter the height in cm: ";
		std::cout.flush();
		std::cin >> height;
		if (height <= 0) {
			std::cerr << "Enter a positive height" << std::endl;
			
		} else 
			break;
	}
	normal_weight = height - 100.0;
	ideal_weight = normal_weight * 0.95;

	std::cout << "\n==============\n";
	std::cout << "HEIGHT: " << height << " cm\n";
	std::cout << "NORM:   " << normal_weight << " kg\n";
	std::cout << "IDEAL:  " << ideal_weight << " kg" << std::endl;

	return 0;	
}
