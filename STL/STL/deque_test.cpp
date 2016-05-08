#include "deque.hpp"
#include <iostream>

using xf::deque;
using std::cout;
using std::endl;


class NoDefaultConstructorClass
{
public:
	NoDefaultConstructorClass(int n){}
};

void deque_test()
{
	cout << "\nDeque Test:\n";
	{
		cout << "\tdefault constructor test:\n";
		deque<NoDefaultConstructorClass> d1;
		assert(0 == d1.size());
		assert(true == d1.empty());
		cout << "\tdefault constructor with class wihtout default constructor:\n";
		NoDefaultConstructorClass c(1);
		d1.push_back(c);	// push_back时会调用申请空间而不建立对象的operator new，故可以测试deque的实现是否支持不带默认构造函数的类作为容器的模板参数.
		assert(false == d1.empty());
		cout << "\tconstructor with size:\n";
		deque<double> d2(10);
		assert(10 == d2.size());
		cout << "\tconstructor with size and value:\n";
		deque<double> d3(10, 1.5);
		assert(10 == d3.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(1.5 == d3[i]);
		}
		cout << "\tconstructor with size in int-deque:\n";
		deque<int> di(15, 1);
		assert(15 == di.size());
		cout << "\t[] test:\n";
		for(int i = 0; i < 10; ++i)
		{
			assert(1 == di[i]);
		}
		cout << "\tat test:\n";
		for(int i = 0; i < 10; ++i)
		{
			assert(1 == di[i]);
		}
		try
		{
			di.at(10);
		}
		catch(std::out_of_range &)
		{
			cout << "\tindex out_of_range assurance ok\n";
		}
	}
	{
		deque<double> d(10, 1.5);
		cout << "\tresize test:\n";
		cout << "\tresize larger but smaller than SEGMENT_LENGTH:\n";
		d.resize(15);
		assert(15 == d.size());
		for(int i = 0; i < 15; ++i)
		{
			if(i < 10)
			{
				assert(1.5 == d[i]);
			}
			else
			{
				assert(0.0 == d[i]);
			}
		}
		cout << "\tresize larger than SEGMENT_LENGTH:\n";
		d.resize(115);
		assert(115 == d.size());
		for(int i = 0; i < 115; ++i)
		{
			if(i < 10)
			{
				assert(1.5 == d[i]);
			}
			else
			{
				assert(0.0 == d[i]);
			}
		}
		cout << "\tresize smaller but don't compact:\n";
		d.resize(110);
		assert(110 == d.size());
		for(int i = 0; i < 110; ++i)
		{
			if(i < 10)
			{
				assert(1.5 == d[i]);
			}
			else
			{
				assert(0.0 == d[i]);
			}
		}
		cout << "\tresize smaller with compacting:\n";
		d.resize(30);
		assert(30 == d.size());
		for(int i = 0; i < 30; ++i)
		{
			if(i < 10)
			{
				assert(1.5 == d[i]);
			}
			else
			{
				assert(0.0 == d[i]);
			}
		}
	}
	{
		cout << "\tpush_back test:\n";
		deque<int> d;
		d.push_back(0);
		d.push_back(1);
		d.push_back(2);
		d.push_back(3);
		d.push_back(4);
		d.push_back(5);
		d.push_back(6);
		d.push_back(7);
		d.push_back(8);
		d.push_back(9);
		for(int i = 0; i < 10; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tback & pop_back test:\n";
		d.pop_back();
		assert(9 == d.size());
		assert(false == d.empty());
		assert(8 == d.back());
	}
	{
		cout << "\tpush_front test:\n";
		deque<int> d;
		d.push_front(9);
		d.push_front(8);
		d.push_front(7);
		d.push_front(6);
		d.push_front(5);
		d.push_front(4);
		d.push_front(3);
		d.push_front(2);
		d.push_front(1);
		d.push_front(0);
		for(int i = 0; i < 10; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tfront & pop_front test:\n";
		d.pop_front();
		assert(9 == d.size());
		assert(false == d.empty());
		assert(1 == d.front());
	}
	{
		cout << "\tconstructor with iterator test:\n";
		int a[] = {0,1,2,3,4,5,6,7,8,9,};
		deque<int> d(a, a + 10);
		for(int i = 0; i < 10; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tcopy constructor test:\n";
		deque<int> d1(d);
		for(int i = 0; i < 10; ++i)
		{
			assert(i == d1[i]);
		}
		cout << "\tclear test:\n";
		d1.clear();
		assert(0 == d1.size());
		assert(true == d1.empty());
	}
	{
		cout << "\titerator test:\n";
		int a[] = {0,1,2,3,4,5,6,7,8,9};
		deque<int> d(a, a + 10);
		cout << "\tnormal iterator:\n";
		deque<int>::iterator iter = d.begin();
		for(; iter != d.end(); ++iter)
		{
			assert(a[xf::distance(d.begin(), iter)] == *iter);
		}
		--iter;
		assert(a[xf::distance(d.begin(), iter)] == *iter);

		cout << "\tconst iterator:\n";
		deque<int>::const_iterator c_iter = d.cbegin();
		for(; c_iter != d.cend(); ++c_iter)
		{
			assert(a[xf::distance(d.cbegin(), c_iter)] == *c_iter);
		}
		--c_iter;
		assert(a[xf::distance(d.cbegin(), c_iter)] == *c_iter);

		cout << "\treverse iterator:\n";
		deque<int>::reverse_iterator r_iter = d.rbegin();
		for(; r_iter != d.rend(); ++r_iter)
		{
			assert(a[9 - xf::distance(d.rbegin(), r_iter)] == *r_iter);
		}
		--r_iter;
		assert(a[9 - xf::distance(d.rbegin(), r_iter)] == *r_iter);

		cout << "\tconst reverse iterator:\n";
		//xf::_Reverse_Iterator<xf::_Deque_Const_Iterator<int> > cr_iter = d.crbegin();
		deque<int>::const_reverse_iterator cr_iter = d.crbegin();
		for(; cr_iter != d.crend(); ++cr_iter)
		{
			assert(a[9 - xf::distance(d.crbegin(), cr_iter)] == *cr_iter);
		}
		--cr_iter;
		assert(a[9 - xf::distance(d.crbegin(), cr_iter)] == *cr_iter);
	}
	{
		cout << "\tinsert test:\n";
		cout << "\tinsert into empty deque at begining:\n";
		int a[] = {0,1,2,3,4,5,6,7,8,9};
		deque<int> d;
		d.insert(d.begin(), a, a + 2);
		assert(2 == d.size());
		assert(false == d.empty());
		for(int i = 0; i < 2; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tinsert into empty deque at ending:\n";
		d.clear();
		d.insert(d.end(), a, a + 2);
		assert(2 == d.size());
		assert(false == d.empty());
		for(int i = 0; i < 2; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tinsert into non-empty deque at ending:\n";
		d.insert(d.end(), a + 2, a + 5);
		assert(5 == d.size());
		for(int i = 0; i < 5; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tinsert into mid-position in deque:\n";
		d.clear();
		d.insert(d.begin(), a + 1, a + 3);
		d.insert(d.end(), a + 5, a + 9);
		d.insert(d.begin() + 2, a + 3, a + 5);
		assert(8 == d.size());
		for(int i = 0; i < 8; ++i)
		{
			assert(i + 1 == d[i]);
		}
		cout << "\tinsert one element at begining:\n";
		d.insert(d.begin(), 0);
		assert(9 == d.size());
		for(int i = 0; i < 9; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tinsert one element at ending:\n";
		d.insert(d.end(), 9);
		assert(10 == d.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(i == d[i]);
		}
		cout << "\tinsert one element at mid-position:\n";
		d.insert(d.begin() + 5, 100);
		assert(11 == d.size());
		for(int i = 0; i < 5; ++i)
		{
			assert(i == d[i]);
		}
		assert(100 == d[5]);
		for(int i = 6; i < 11; ++i)
		{
			assert(i - 1 == d[i]);
		}
		cout << "\tinsert a number of elements of the same value:\n";
		// begining inserting
		d.clear();
		d.insert(d.begin(), 5, 1);
		assert(5 == d.size());
		assert(false == d.empty());
		for(int i = 0; i < 5; ++i)
		{
			assert(1 == d[i]);
		}
		// ending inserting
		d.clear();
		d.insert(d.end(), 5, 1);
		assert(5 == d.size());
		assert(false == d.empty());
		for(int i = 0; i < 5; ++i)
		{
			assert(1 == d[i]);
		}
		// mid-position inserting
		d.clear();
		d.insert(d.begin(), 2, 1);
		d.insert(d.end(), 2, 3);
		d.insert(d.begin() + 2, 2, 2);
		assert(6 == d.size());
		assert(false == d.empty());
		int benchmark[] = {1,1,2,2,3,3};
		for(int i = 0; i < 6; ++i)
		{
			assert(benchmark[i] == d[i]);
		}
	}
	{
		cout << "\tassign test:\n";
		cout << "\tassign to an empty deque:\n";
		// template specialization
		deque<int> d1;
		d1.assign(10, 5);
		assert(10 == d1.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(5 == d1[i]);
		}
		d1.assign(110, 5);
		assert(110 == d1.size());
		for(int i = 0; i < 110; ++i)
		{
			assert(5 == d1[i]);
		}
		// assign with count and value
		deque<double> d2;
		d2.assign(10, 5.0);
		assert(10 == d2.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(5.0 == d2[i]);
		}
		d2.assign(100, 5.0);
		assert(100 == d2.size());
		for(int i = 0; i < 100; ++i)
		{
			assert(5.0 == d2[i]);
		}
		// assign with iterator
		int a[5] = {1,2,3,4,5};
		deque<int> d3;
		d3.assign(a, a + 5);
		assert(5 == d3.size());
		for(int i = 0; i < 5; ++i)
		{
			assert(i + 1 == d3[i]);
		}

		cout << "\tassign to an non-empty deque:\n";
		// template specialization
		deque<int> d4(100, 3);
		d4.assign(10, 5);
		assert(10 == d4.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(5 == d4[i]);
		}
		d4.assign(110, 5);
		assert(110 == d4.size());
		for(int i = 0; i < 110; ++i)
		{
			assert(5 == d4[i]);
		}
		// assign with count and value
		deque<double> d5(350, 1.2);
		d5.assign(10, 5.0);
		assert(10 == d5.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(5.0 == d5[i]);
		}
		d5.assign(300, 5.0);
		assert(300 == d5.size());
		for(int i = 0; i < 300; ++i)
		{
			assert(5.0 == d5[i]);
		}
		// assign with iterator
		deque<int> d6(1000, 13);
		d6.assign(a, a + 5);
		assert(5 == d3.size());
		for(int i = 0; i < 5; ++i)
		{
			assert(i + 1 == d3[i]);
		}
	}
	{
		cout << "\tmax size test:\n";
		deque<int> di;
		deque<float> df;
		deque<double> dd;
		assert((unsigned int)-1 / sizeof(int) == di.max_size());
		assert((unsigned int)-1 / sizeof(float) == df.max_size());
		assert((unsigned int)-1 / sizeof(double) == dd.max_size());
	}

}