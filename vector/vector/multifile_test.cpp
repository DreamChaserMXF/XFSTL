#include <iostream>
#include "vector.hpp"

// for multi file test
void multi_file_test()
{
	xf::vector<int> vi;
	xf::vector<double> vd;
	int i = 0;
	(i += 5) = 10;
	std::cout << "multi file test successful!\n";
}
