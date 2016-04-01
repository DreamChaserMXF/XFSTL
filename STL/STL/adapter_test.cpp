#include "priority_queue.hpp"
#include "list.hpp"


void adapter_test()
{
	xf::priority_queue<int> q;
	// priority_queue<int, xf::list<int>> q;
	printf("\nempty() = %d", q.empty());
	printf("\nsize() = %d", q.size());

	q.push(1);
	q.push(3);
	q.push(5);
	q.push(7);
	q.push(9);
	q.push(2);
	q.push(4);
	q.push(6);
	q.push(8);
	q.push(10);
	printf("\nempty() = %d", q.empty());
	printf("\nsize() = %d", q.size());
	printf("\n");

	size_t len = q.size();
	for(size_t i = 0; i < len; ++i)
	{
		printf("%d ", q.top());
		q.pop();
	}

	printf("\nempty() = %d", q.empty());
	printf("\nsize() = %d", q.size());
	printf("\n\n");

}