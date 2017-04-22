#include "priority_queue.hpp"
#include "vector.hpp"
#include "deque.hpp"
#include "test.hpp"

using xf::priority_queue;
using xf::vector;
using xf::deque;


void priority_queue_test()
{
	printf("\tPriority Queue Test:\n");
	// default test
	printf("\t\tdefault constructor test:\n");
	priority_queue<int, vector<int>> q1;
	// priority_queue<int, xf::list<int>> q1;	// error
	assert(true == q1.empty());
	assert(0 == q1.size());
	q1.push(1);
	q1.push(3);
	q1.push(5);
	q1.push(7);
	q1.push(9);
	q1.push(2);
	q1.push(4);
	q1.push(6);
	q1.push(8);
	q1.push(10);
	printf("\t\tempty & size test:\n");
	assert(false == q1.empty());
	assert(10 == q1.size());
	size_t len1 = q1.size();
	for(size_t i = 0; i < len1; ++i)
	{
		assert(10 - i == q1.top());
		q1.pop();
	}
	assert(true == q1.empty());
	assert(0 == q1.size());

	printf("\t\tless_than_class test:\n");
	// less_than_class test
	int a[] = {1,3,5,7,9,2,4,6,8,10};
	priority_queue<int, vector<int>, less_than_class> q2(xf::vector<int>(a, a + sizeof(a) / sizeof(a[0])));
	//xf::priority_queue<int, xf::list<int>> q2;
	assert(false == q2.empty());
	assert(10 == q2.size());
	size_t len2 = q2.size();
	for(size_t i = 0; i < len2; ++i)
	{
		assert(10 - i == q2.top());
		q2.pop();
	}
	assert(true == q2.empty());
	assert(0 == q2.size());

	printf("\t\tlarger_than_class test:\n");
	// larger_than_class test
	priority_queue<int, vector<int>, larger_than_class> q3;
	// priority_queue<int, xf::list<int>> q3;
	assert(true == q3.empty());
	assert(0 == q3.size());
	q3.push(1);
	q3.push(3);
	q3.push(5);
	q3.push(7);
	q3.push(9);
	q3.push(2);
	q3.push(4);
	q3.push(6);
	q3.push(8);
	q3.push(10);
	assert(false == q3.empty());
	assert(10 == q3.size());
	size_t len3 = q3.size();
	for(size_t i = 0; i < len3; ++i)
	{
		assert(i + 1 == q3.top());
		q3.pop();
	}
	assert(true == q3.empty());
	assert(0 == q3.size());

	printf("\t\tpriority_queue implemented by deque:\n");
	priority_queue<double, deque<double>> q4;
	assert(true == q4.empty());
	assert(0 == q4.size());
	q4.push(1);
	q4.push(3);
	q4.push(5);
	q4.push(7);
	q4.push(9);
	q4.push(2);
	q4.push(4);
	q4.push(6);
	q4.push(8);
	q4.push(10);
	printf("\t\tempty & size test:\n");
	assert(false == q4.empty());
	assert(10 == q4.size());
	size_t len4 = q4.size();
	for(size_t i = 0; i < len4; ++i)
	{
		assert(10 - i == q4.top());
		q4.pop();
	}
	assert(true == q4.empty());
	assert(0 == q4.size());
}