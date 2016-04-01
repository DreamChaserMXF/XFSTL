#include "priority_queue.hpp"
#include "vector.hpp"

// 这个在类模板中不能用
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


void adapter_test()
{
	printf("\nadapter_test:");

	xf::priority_queue<int, xf::vector<int>> q1;
	// priority_queue<int, xf::list<int>> q1;
	printf("\nempty() = %d", q1.empty());
	printf("\nsize() = %d", q1.size());
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
	printf("\nempty() = %d", q1.empty());
	printf("\nsize() = %d", q1.size());
	printf("\n");
	size_t len1 = q1.size();
	for(size_t i = 0; i < len1; ++i)
	{
		printf("%d ", q1.top());
		q1.pop();
	}
	printf("\nempty() = %d", q1.empty());
	printf("\nsize() = %d", q1.size());
	printf("\n");

	xf::priority_queue<int, xf::vector<int>, less_than_class> q2;
	// priority_queue<int, xf::list<int>> q2;
	printf("\nempty() = %d", q2.empty());
	printf("\nsize() = %d", q2.size());
	q2.push(1);
	q2.push(3);
	q2.push(5);
	q2.push(7);
	q2.push(9);
	q2.push(2);
	q2.push(4);
	q2.push(6);
	q2.push(8);
	q2.push(10);
	printf("\nempty() = %d", q2.empty());
	printf("\nsize() = %d", q2.size());
	printf("\n");
	size_t len2 = q2.size();
	for(size_t i = 0; i < len2; ++i)
	{
		printf("%d ", q2.top());
		q2.pop();
	}
	printf("\nempty() = %d", q2.empty());
	printf("\nsize() = %d", q2.size());
	printf("\n");

	xf::priority_queue<int, xf::vector<int>, larger_than_class> q3;
	// priority_queue<int, xf::list<int>> q3;
	printf("\nempty() = %d", q3.empty());
	printf("\nsize() = %d", q3.size());
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
	printf("\nempty() = %d", q3.empty());
	printf("\nsize() = %d", q3.size());
	printf("\n");
	size_t len3 = q3.size();
	for(size_t i = 0; i < len3; ++i)
	{
		printf("%d ", q3.top());
		q3.pop();
	}
	printf("\nempty() = %d", q3.empty());
	printf("\nsize() = %d", q3.size());
	printf("\n\n");

}