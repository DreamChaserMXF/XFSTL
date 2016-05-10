#include <iostream>
#include "list.hpp"
#include "vector.hpp"
#include "deque.hpp"
#include "priority_queue.hpp"
#include "queue.hpp"
#include "stack.hpp"

// for multi file test
void multi_file_test()
{
	xf::vector<int> vi;
	xf::vector<double> vd;
	xf::list<int> li;
	xf::list<double> ld;
	xf::deque<float> df;
	xf::priority_queue<int> p_q;
	xf::queue<int> q;
	xf::stack<int> stk;
	int i = 0;
	(i += 5) = 10;
	std::cout << "Multi-file Test successful!\n";
}
