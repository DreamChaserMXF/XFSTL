#include <iostream>
#include "list.hpp"

// for multi file test
void multi_file_test()
{
	xf::list<int> vi;
	xf::list<double> vd;
	int i = 0;
	(i += 5) = 10;
	std::cout << "multi file test successful!\n";
}
