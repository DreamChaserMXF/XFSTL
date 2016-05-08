#include "priority_queue.hpp"
#include "vector.hpp"

// 这个在类模板中不能用，在这里作失败典例
static bool largerthan_func(const int &lhs, const int &rhs)
{
	return lhs > rhs;
}

class less_than_class
{
public:
	bool operator () (int a, int b) const
	{
		return a < b;
	}
};

class larger_than_class
{
public:
	bool operator () (int a, int b) const
	{
		return a > b;
	}
};


void priority_queue_test()
{
	printf("\nadapter_test:\n");

	// default test
	xf::priority_queue<int, xf::vector<int>> q1;
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

	// less_than_class test
	int a[] = {1,3,5,7,9,2,4,6,8,10};
	xf::priority_queue<int, xf::vector<int>, less_than_class> q2(xf::vector<int>(a, a + sizeof(a) / sizeof(a[0])));
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

	// larger_than_class test
	xf::priority_queue<int, xf::vector<int>, larger_than_class> q3;
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
}