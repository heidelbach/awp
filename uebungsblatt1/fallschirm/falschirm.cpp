#include <iostream>
#include <cmath>

static const float g = 9.81;
static const int s_limit = 650;

int main()
{
	unsigned int height;
	float t_limit;
	std::cout << "Please enter the height in meters: ";
	std::cout.flush();

	std::cin >> height;
	
	// s(t) = 1/2 g t^2 + height;
	// s_limit(t_limit) = 1/2 g t_limit * t_limit + height;
	if (height < s_limit)
		t_limit = 0;
	else
		t_limit = sqrt( 2 * (height - s_limit) / g );

	std::cout << "\rT_limit(" << height << " m) = " << t_limit << " seconds" << std::endl;
	return 0;
}
