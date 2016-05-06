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
		deque<NoDefaultConstructorClass> d;
		assert(0 == d.size());
		assert(true == d.empty());
		cout << "\tdefault constructor with class wihtout default constructor:\n";
		NoDefaultConstructorClass c(1);
		d.push_back(c);	// push_back时会调用申请空间而不建立对象的operator new，故可以测试deque的实现是否支持不带默认构造函数的类作为容器的模板参数
	}
	{
		deque<double> d(10, 1.5);
		cout << "\tconstructor with size & [] test:\n";
		assert(10 == d.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(1.5 == d[i]);
		}
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
		cout << "\tconstructor with size and value & at() test:\n";
		deque<double> d(10, 3.3);
		assert(10 == d.size());
		for(int i = 0; i < 10; ++i)
		{
			assert(3.3 == d.at(i));
		}
		try
		{
			d.at(10);
		}
		catch(std::out_of_range &)
		{
			cout << "\tindex out_of_range assurance ok\n";
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
	}
	{
		cout << "\tassign test:\n";
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