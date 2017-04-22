#include "deque.hpp"
#include "test.hpp"
#include <iostream>

using xf::deque;
using std::cout;
using std::endl;




void deque_test()
{
	cout << "\nDeque Test:\n";
	{
		cout << "\tdefault constructor test:\n";
		deque<NoDefaultConstructorClass> d1;
		assert(0 == d1.size());
		assert(true == d1.empty());
		cout << "\tdefault constructor with no default constructor class as template parameter:\n";
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
		deque<int> d;

		cout << "\t\tinsert one element:\n";
		cout << "\t\t\tinsert into empty deque at begining:\n";
		deque<int>::iterator iter = d.insert(d.begin(), 1);
		assert(1 == *iter);
		assert(1 == d.size());
		assert(1 == d[0]);
		cout << "\t\t\tinsert into empty deque at ending:\n";
		d.clear();
		iter = d.insert(d.end(), 1);
		assert(1 == *iter);
		assert(1 == d.size());
		assert(1 == d[0]);
		cout << "\t\t\tinsert into non-empty deque at begining:\n";
		d.clear();
		iter = d.insert(d.begin(), 2);
		assert(2 == *iter);
		iter = d.insert(d.begin(), 1);
		assert(1 == *iter);
		assert(2 == d.size());
		assert(1 == d[0] && 2 == d[1]);
		cout << "\t\t\tinsert into non-empty deque at ending:\n";
		iter = d.insert(d.end(), 3);
		assert(3 == *iter);
		assert(3 == d.size());
		assert(1 == d[0] && 2 == d[1] && 3 == d[2]);
		cout << "\t\t\tinsert into non-empty deque at mid-position:\n";
		iter = d.insert(d.begin() + 1, 100);
		assert(100 == *iter);
		assert(4 == d.size());
		assert(1 == d[0] && 100 == d[1] && 2 == d[2] && 3 == d[3]);

		cout << "\t\tinsert n same element:\n";
		cout << "\t\t\tinsert into empty deque at begining:\n";
		d.clear();
		iter = d.insert(d.begin(), 5, 1);
		assert(1 == *iter);
		assert(5 == d.size());
		assert(1 == d[0] && 1 == d[1] && 1 == d[2] && 1 == d[3] && 1 == d[4]);
		cout << "\t\t\tinsert into empty deque at ending:\n";
		d.clear();
		iter = d.insert(d.end(), 5, 1);
		assert(1 == *iter);
		assert(5 == d.size());
		assert(1 == d[0] && 1 == d[1] && 1 == d[2] && 1 == d[3] && 1 == d[4]);
		cout << "\t\t\tinsert into non-empty deque at begining:\n";
		d.clear();
		iter = d.insert(d.end(), 3, 1);
		assert(1 == *iter);
		iter = d.insert(d.begin(), 2, 10);
		assert(10 == *iter);
		assert(5 == d.size());
		assert(10 == d[0] && 10 == d[1] && 1 == d[2] && 1 == d[3] && 1 == d[4]);
		cout << "\t\t\tinsert into non-empty deque at ending:\n";
		d.clear();
		iter = d.insert(d.end(), 3, 1);
		assert(1 == *iter);
		iter = d.insert(d.end(), 2, 10);
		assert(10 == *iter);
		assert(5 == d.size());
		assert(1 == d[0] && 1 == d[1] && 1 == d[2] && 10 == d[3] && 10 == d[4]);
		cout << "\t\t\tinsert into non-empty deque at mid-but-front-position:\n";
		iter = d.insert(d.begin() + 2, 2, 100);
		assert(100 == *iter);
		assert(7 == d.size());
		assert(1 == d[0] && 1 == d[1] && 100 == d[2] && 100 == d[3] && 1 == d[4] && 10 == d[5] && 10 == d[6]);
		cout << "\t\t\tinsert into non-empty deque at mid-but-back-position:\n";
		iter = d.insert(d.begin() + 4, 2, 101);
		assert(101 == *iter);
		assert(9 == d.size());
		assert(1 == d[0] && 1 == d[1] && 100 == d[2] && 100 == d[3] && 101 == d[4] && 101 == d[5] && 1 == d[6] && 10 == d[7] && 10 == d[8]);

		cout << "\t\tinsert a range of elements represented by iterator:\n";
		int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		cout << "\t\t\tinsert into empty deque at begining:\n";
		d.clear();
		iter = d.insert(d.begin(), a, a + 5);
		assert(1 == *iter);
		assert(5 == d.size());
		assert(1 == d[0] && 2 == d[1] && 3 == d[2] && 4 == d[3] && 5 == d[4]);
		cout << "\t\t\tinsert into empty deque at ending:\n";
		d.clear();
		iter = d.insert(d.end(), a, a + 5);
		assert(1 == *iter);
		assert(5 == d.size());
		assert(1 == d[0] && 2 == d[1] && 3 == d[2] && 4 == d[3] && 5 == d[4]);
		cout << "\t\t\tinsert into non-empty deque at begining:\n";
		d.clear();
		iter = d.insert(d.begin(), 5);
		assert(5 == *iter);
		iter = d.insert(d.begin(), a, a + 4);
		assert(1 == *iter);
		assert(5 == d.size());
		assert(1 == d[0] && 2 == d[1] && 3 == d[2] && 4 == d[3] && 5 == d[4]);
		cout << "\t\t\tinsert into non-empty deque at ending:\n";
		d.clear();
		iter = d.insert(d.begin(), 1);
		assert(1 == *iter);
		iter = d.insert(d.end(), a + 1, a + 5);
		assert(2 == *iter);
		assert(5 == d.size());
		assert(1 == d[0] && 2 == d[1] && 3 == d[2] && 4 == d[3] && 5 == d[4]);
		cout << "\t\t\tinsert into non-empty deque at mid-but-front-position:\n";
		iter = d.insert(d.begin() + 2, a, a + 2);
		assert(1 == *iter);
		assert(7 == d.size());
		assert(1 == d[0] && 2 == d[1] && 1 == d[2] && 2 == d[3] && 3 == d[4] && 4 == d[5] && 5 == d[6]);
		iter = d.insert(d.begin() + 4, a + 2, a + 4);
		cout << "\t\t\tinsert into non-empty deque at mid-but-back-position:\n";
		assert(3 == *iter);
		assert(9 == d.size());
		assert(1 == d[0] && 2 == d[1] && 1 == d[2] && 2 == d[3] && 3 == d[4] && 4 == d[5] && 3 == d[6] && 4 == d[7] && 5 == d[8]);

		cout << "\t\tinsert into deque with large size element:\n";
		iter = d.insert(d.begin(), 1000, 101);
		assert(101 == *iter);
		assert(1009 == d.size());
		for(int i = 0; i < 1000; ++i)
		{
			assert(101 == d[i]);
		}
		assert(1 == d[1000] && 2 == d[1001] && 1 == d[1002] && 2 == d[1003] && 3 == d[1004] && 4 == d[1005] && 3 == d[1006] && 4 == d[1007] && 5 == d[1008]);

		cout << "\terase test:\n";
		cout << "\t\terase one element:\n";
		cout << "\t\t\terase from ending:\n";
		deque<int>::iterator tmp_end = d.erase(d.begin() + 1008);
		assert(tmp_end == d.end());
		assert(1008 == d.size());
		for(int i = 0; i < 1000; ++i)
		{
			assert(101 == d[i]);
		}
		assert(1 == d[1000] && 2 == d[1001] && 1 == d[1002] && 2 == d[1003] && 3 == d[1004] && 4 == d[1005] && 3 == d[1006] && 4 == d[1007]);
		cout << "\t\t\terase from begining:\n";
		deque<int>::iterator tmp_begin = d.erase(d.begin());
		assert(tmp_begin == d.begin());
		assert(1007 == d.size());
		for(int i = 0; i < 999; ++i)
		{
			assert(101 == d[i]);
		}
		assert(1 == d[999] && 2 == d[1000] && 1 == d[1001] && 2 == d[1002] && 3 == d[1003] && 4 == d[1004] && 3 == d[1005] && 4 == d[1006]);
		cout << "\t\t\terase from mid-position but near ending:\n";
		iter = d.erase(d.begin() + 999);
		assert(2 == *iter);
		assert(1006 == d.size());
		for(int i = 0; i < 999; ++i)
		{
			assert(101 == d[i]);
		}
		assert(2 == d[999] && 1 == d[1000] && 2 == d[1001] && 3 == d[1002] && 4 == d[1003] && 3 == d[1004] && 4 == d[1005]);
		cout << "\t\t\terase from mid-position but near begining:\n";
		iter = d.erase(d.begin() + 1);
		assert(101 == *iter);
		assert(1005 == d.size());
		for(int i = 0; i < 998; ++i)
		{
			assert(101 == d[i]);
		}
		assert(2 == d[998] && 1 == d[999] && 2 == d[1000] && 3 == d[1001] && 4 == d[1002] && 3 == d[1003] && 4 == d[1004]);

		cout << "\t\terase a range of elements:\n";
		cout << "\t\t\terase from ending:\n";
		tmp_end = d.erase(d.begin() + 1003, d.end());
		assert(tmp_end == d.end());
		assert(1003 == d.size());
		for(int i = 0; i < 998; ++i)
		{
			assert(101 == d[i]);
		}
		assert(2 == d[998] && 1 == d[999] && 2 == d[1000] && 3 == d[1001] && 4 == d[1002]);
		cout << "\t\t\terase from begining:\n";
		tmp_begin = d.erase(d.begin(), d.begin() + 100);
		assert(tmp_begin == d.begin());
		assert(903 == d.size());
		for(int i = 0; i < 898; ++i)
		{
			assert(101 == d[i]);
		}
		assert(2 == d[898] && 1 == d[899] && 2 == d[900] && 3 == d[901] && 4 == d[902]);
		cout << "\t\t\terase from mid-position but near ending:\n";
		iter = d.erase(d.begin() + 799, d.begin() + 899);
		assert(1 == *iter);
		assert(803 == d.size());
		for(int i = 0; i < 799; ++i)
		{
			assert(101 == d[i]);
		}
		assert(1 == d[799] && 2 == d[800] && 3 == d[801] && 4 == d[802]);
		cout << "\t\t\terase from mid-position but near begining:\n";
		iter = d.erase(d.begin() + 100, d.begin() + 300);
		assert(101 == *iter);
		assert(603 == d.size());
		for(int i = 0; i < 599; ++i)
		{
			assert(101 == d[i]);
		}
		assert(1 == d[599] && 2 == d[600] && 3 == d[601] && 4 == d[602]);
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