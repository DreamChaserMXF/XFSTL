#include <stdio.h>
#include "queue.hpp"
using xf::queue;
void queue_test()
{
	printf("\tQueue Test:\n");
	printf("\t\tdefault constructor test:\n");
	queue<int> q;
	
	printf("\t\tsize & empty test:\n");
	assert(0 == q.size());
	assert(true == q.empty());
	
	printf("\t\tpush test:\n");
	for(size_t i = 0; i < 100; ++i)
	{
		q.push(i);
	}
	assert(100 == q.size());
	assert(false == q.empty());
	
	printf("\t\tpop test:\n");
	for(size_t i = 0; i < 50; ++i)
	{
		assert(100 - i == q.size());
		assert(i == q.front());
		q.pop();
	}
	assert(50 == q.size());
	assert(false == q.empty());

	printf("\t\tcopy constructor test:\n");
	queue<int> q2(q);
	assert(50 == q2.size());
	assert(false == q2.empty());
	for(size_t i = 50; i < 100; ++i)
	{
		assert(100 - i == q2.size());
		assert(i == q2.front());
		q2.pop();
	}

	printf("\t\tconstructor with container");
	xf::deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	xf::queue<int> q3(d);
	assert(3 == q3.size());
	assert(false == q3.empty());

	printf("\t\tclear test:\n");
	assert(50 == q.size());
	assert(false == q.empty());
	q.clear();
	assert(0 == q.size());
	assert(true == q.empty());
}