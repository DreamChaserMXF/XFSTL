#include <iostream>
#include "list.hpp"
#include "vector.hpp"
#include "deque.hpp"

// for multi file test
void multi_file_test()
{
	xf::vector<int> vi;
	xf::vector<double> vd;
	xf::list<int> li;
	xf::list<double> ld;
	xf::deque<float> df;
	int i = 0;
	(i += 5) = 10;
	std::cout << "Multi-file Test successful!\n";
}
