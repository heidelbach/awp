#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
	float percent;
	float years;
	unsigned int capital, capital_end;
	
	std::cout << "Please enter the captial in cent: ";
	std::cout.flush();
	std::cin >> capital;
	
	std::cout << "\rPlease enter the rate in percent: ";
	std::cout.flush();
	std::cin >> percent;
	percent /= 100.0;
	
	std::cout << "\rPlease enter the life span in years: ";
	std::cout.flush();
	std::cin >> years;
	
	capital_end = capital * pow(1 + percent, years);

	std::cout << std::setw(20) << std::setfill('-') << "\n";
	std::setw(0);
	std::cout << "After " << std::setprecision(2) << years << " years\n"
			<< capital / 100 << ","
			<< capital % 100;
	if (capital % 100 < 10)
			std::cout << "0";
	std::cout << " €\nwill be at the rate of " << std::setprecision(4)
	 		<< percent * 100.0 << "%\n" << capital_end / 100 << ","
			<< capital_end % 100;
	if (capital_end % 100 < 10)
			std::cout << "0";
	std::cout << " €" << std::endl;
	return 0;
}
