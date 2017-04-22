#include <stdio.h>
#include "vector.hpp"
#include "deque.hpp"
#include "sort.hpp"
#include "test.hpp"



void sort_test()
{
	printf("\nSort Test:\n");
	{
		// vector sort
		int a[] = {1,3,5,7,9,2,4,6,8,10};
		int b[] = {1,3,5,7,9,2,4,6,8,10};
		int length = sizeof(a) / sizeof(a[0]);
		xf::vector<int> va(a, a + length);
		xf::vector<int> vb(va);
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
	}

	{
		// array sort
		int a[] = {1,3,5,7,9,2,4,6,8,10};
		int b[] = {1,3,5,7,9,2,4,6,8,10};
		int length = sizeof(a) / sizeof(a[0]);
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
	
	{
		// deque sort
		printf("\tdeque sort:\n");
		int a[] = {1,3,5,7,9,2,4,6,8,10};
		int b[] = {1,3,5,7,9,2,4,6,8,10};
		int length = sizeof(a) / sizeof(a[0]);
		xf::deque<int> da(a, a + length);
		xf::deque<int> db(b, b + length);


		//xf::sort(d.begin(), d.end());
		//for(int i = 0; i < length; ++i)
		//{
		//	assert(d[i] == i + 1);
		//}


		printf("\t\tbegin to end:\n");
		sort(da.begin(), da.end());
		for(int i = 1; i < length; ++i)
		{
			assert(da[i] >= da[i-1]);
		}

		printf("\t\trbegin to rend:\n");
		sort(da.rbegin(), da.rend());
		for(int i = 1; i < length; ++i)
		{
			assert(da[i] <= da[i-1]);
		}

		printf("\t\tbegin to end with lessthan function:\n");
		sort(db.begin(), db.end(), lessthan_func);
		for(int i = 1; i < length; ++i)
		{
			assert(db[i] >= db[i-1]);
		}

		printf("\t\tbegin to end with largerthan function:\n");
		sort(db.begin(), db.end(), largerthan_func);
		for(int i = 1; i < length; ++i)
		{
			assert(db[i] <= db[i-1]);
		}

		printf("\t\tbegin to end with lessthan object:\n");
		sort(db.begin(), db.end(), less_than_class());
		for(int i = 1; i < length; ++i)
		{
			assert(db[i] >= db[i-1]);
		}

		printf("\t\tbegin to end with largerthan object:\n");
		sort(db.begin(), db.end(), larger_than_class());
		for(int i = 1; i < length; ++i)
		{
			assert(db[i] <= db[i-1]);
		}
	}
}