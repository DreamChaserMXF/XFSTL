#include <stdio.h>
#include "vector.hpp"
#include "sort.hpp"

static bool lessthan_func(const int &lhs, const int &rhs)
{
	return lhs < rhs;
}
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


void sort_test()
{
	printf("\nSort Test:\n");

	int a[] = {1,3,5,7,9,2,4,6,8,10};
	int b[] = {1,3,5,7,9,2,4,6,8,10};
	int length = sizeof(a) / sizeof(a[0]);
	xf::vector<int> va(a, a + length);
	xf::vector<int> vb(va);

	// vector sort
	printf("\tvector sort:\n");

	printf("\t\tbegin to end:\n");
	sort(va.begin(), va.end());
	for(int i = 1; i < length; ++i)
	{
		assert(va[i] >= va[i-1]);
	}

	printf("\t\trbegin to rend:\n");
	sort(va.rbegin(), va.rend());
	for(int i = 1; i < length; ++i)
	{
		assert(va[i] <= va[i-1]);
	}

	printf("\t\tbegin to end with lessthan function:\n");
	sort(vb.begin(), vb.end(), lessthan_func);
	for(int i = 1; i < length; ++i)
	{
		assert(vb[i] >= vb[i-1]);
	}

	printf("\t\tbegin to end with largerthan function:\n");
	sort(vb.begin(), vb.end(), largerthan_func);
	for(int i = 1; i < length; ++i)
	{
		assert(vb[i] <= vb[i-1]);
	}

	printf("\t\tbegin to end with lessthan object:\n");
	sort(vb.begin(), vb.end(), less_than_class());
	for(int i = 1; i < length; ++i)
	{
		assert(vb[i] >= vb[i-1]);
	}

	printf("\t\tbegin to end with largerthan object:\n");
	sort(vb.begin(), vb.end(), larger_than_class());
	for(int i = 1; i < length; ++i)
	{
		assert(vb[i] <= vb[i-1]);
	}


	// array sort
	printf("\tarray sort:\n");
	
	printf("\t\tnormal array sort:\n");
	xf::sort(a, a + length);
	for(int i = 1; i < length; ++i)
	{
		assert(a[i] >= a[i-1]);
	}

	printf("\t\tarray sort with lessthan function:\n");
	xf::sort(b, b + length, lessthan_func);
	for(int i = 1; i < length; ++i)
	{
		assert(b[i] >= b[i-1]);
	}

	printf("\t\tarray sort with largerthan function:\n");
	xf::sort(b, b + length, largerthan_func);
	for(int i = 1; i < length; ++i)
	{
		assert(b[i] <= b[i-1]);
	}

	printf("\t\tarray sort with lessthan object:\n");
	xf::sort(b, b + length, less_than_class());
	for(int i = 1; i < length; ++i)
	{
		assert(b[i] >= b[i-1]);
	}

	printf("\t\tarray sort with largerthan object:\n");
	xf::sort(b, b + length, larger_than_class());
	for(int i = 1; i < length; ++i)
	{
		assert(b[i] <= b[i-1]);
	}
}