#include <iostream>
#include <string>

#include "list.hpp"
#include "test.hpp"

using namespace xf;
using std::string;
using std::cout;
using std::endl;
using std::ends;



void list_test()
{
	class A
	{
	public:
		A():n(1){}
		A(const A &a) : n(a.n+10)
		{
		}

		void func() const
		{
			cout << "\tconst member function\n";
		}
		A& operator = (const A &a)
		{
			n = a.n + 100;
			return *this;
		}
		int n;
	};

	class B
	{
	public:
		B(int a){};
	};

	cout << "\nList Test:\n";

	// assign, front, back, push, pop, clear
	list<int> list1;
	{
		// default constructor
		cout << "\tdefault constructor\n";
		assert(0 == list1.size());
		// empty test
		cout << "\tempty test\n";
		assert(true == list1.empty());
		// assign
		cout << "\tassign\n";
		list1.assign(10, 2);
		assert(10 == list1.size());
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(2 == *iter);
		}
		

		// empty test
		assert(false == list1.empty());

		// re-assign
		cout << "\tre-assign\n";
		list1.assign(5, 7);
		assert(5 == list1.size());
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(7 == *iter);
		}
		
		// front, back
		cout << "\tfront, back\n";
		assert(7 == list1.front());
		assert(7 == list1.back());
		assert(2 == (list1.front() = 2));
		assert(3 == (list1.back() = 3));
		int benchmark1[] = {2,7,7,7,3};
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(benchmark1[distance(list1.begin(), iter)] == *iter);
		}

		// pop_back
		cout << "\tpop\n";
		list1.pop_back();
		list1.pop_back();
		assert(3 == list1.size());
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(benchmark1[distance(list1.begin(), iter)] == *iter);
		}

		// push_back
		cout << "\tpush\n";
		list1.push_back(1);
		list1.push_back(2);
		assert(5 == list1.size());
		int benchmark2[] = {2,7,7,1,2};
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(benchmark2[distance(list1.begin(), iter)] == *iter);
		}

		// pop_front
		cout << "\tpop_front\n";
		list1.pop_front();
		list1.pop_front();
		assert(3 == list1.size());
		int benchmark3[] = {7,1,2};
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(benchmark3[distance(list1.begin(), iter)] == *iter);
		}

		// push_front
		cout << "\tpush_front\n";
		list1.push_front(1);
		list1.push_front(2);
		assert(5 == list1.size());
		int benchmark4[] = {2,1,7,1,2};
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(benchmark4[distance(list1.begin(), iter)] == *iter);
		}

		// clear
		cout << "\tclear\n";
		list1.clear();
		assert(0 == list1.size());
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			assert(false);
		}

		// empty test
		cout << "\tempty test\n";
		assert(true == list1.empty());
	}

	{
		cout << "\tdefault constructor with class wihtout default constructor:\n";
		list<B> listb;
		listb.push_back(B(1));
	}

	// =, [], at, data
	list<A> list2(3);
	list<A> list3(list2);
	{
		// _Count constructor
		cout << "\t_Count constructor \n";
		assert(3 == list2.size());
		for(list<A>::iterator iter = list2.begin(); iter != list2.end(); ++iter)
		{
			assert(1 == iter->n);
		}

		// copy constructor 
		cout << "\tcopy constructor \n";
		assert(3 == list3.size());
		for(list<A>::iterator iter = list3.begin(); iter != list3.end(); ++iter)
		{
			assert(11 == iter->n);
		}
		
		// operator = 
		cout << "\toperator = \n";
		list3 = list2;
		assert(3 == list3.size());
		for(list<A>::iterator iter = list3.begin(); iter != list3.end(); ++iter)
		{
			assert(101 == iter->n);
		}
	}

	// iterator
	int a[10] = {1,3,5,7,9,2,4,6,8,10};
	list<int> list4(a, a + 10);
	{
		// iterator preorder ++
		cout << "\titerator preorder ++\n";
		assert(10 == list4.size());
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			assert(a[distance(list4.begin(), iter)] == *iter);
			list<int>::iterator next_iter = ++iter;
			assert(a[distance(list4.begin(), next_iter)] == *next_iter);
			//*iter = 1;	// no error
		}
		

		// iterator postorder ++
		cout << "\titerator postorder ++\n";
		
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); iter++)
		{
			assert(a[distance(list4.begin(), iter)] == *iter);
			list<int>::iterator next_iter = ++(iter++);
			assert(a[distance(list4.begin(), next_iter)] == *next_iter);
			//*iter = 1;	// no error
		}
		
	

		// iterator preorder --
		cout << "\titerator preorder --\n";
		
		for(list<int>::iterator iter = --list4.end(); iter != --list4.begin(); --iter)
		{
			assert(a[distance(list4.begin(), iter)] == *iter);
			list<int>::iterator next_iter = --iter;
			assert(a[distance(list4.begin(), next_iter)] == *next_iter);
		}
		

		// iterator postorder --
		cout << "\titerator postorder --\n";
		
		for(list<int>::iterator iter = --list4.end(); iter != --list4.begin(); iter--)
		{
			assert(a[distance(list4.begin(), iter)] == *iter);
			list<int>::iterator next_iter = --(iter--);
			assert(a[distance(list4.begin(), next_iter)] == *next_iter);
		}
		

		// const iterator preorder ++
		cout << "\tconst iterator preorder ++\n";
		for(list<int>::const_iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			assert(a[distance(list4.cbegin(), iter)] == *iter);
			list<int>::const_iterator next_iter = ++iter;
			assert(a[distance(list4.cbegin(), next_iter)] == *next_iter);
		}
		

		// const iterator postorder ++
		cout << "\tconst iterator postorder ++\n";
		for(list<int>::const_iterator iter = list4.begin(); iter != list4.end(); iter++)
		{
			assert(a[distance(list4.cbegin(), iter)] == *iter);
			list<int>::const_iterator next_iter = ++(iter++);
			assert(a[distance(list4.cbegin(), next_iter)] == *next_iter);
		}
		

		// const iterator preorder --
		cout << "\tconst iterator preorder --\n";
		for(list<int>::const_iterator iter = --list4.end(); iter != --list4.begin(); --iter)
		{
			assert(a[distance(list4.cbegin(), iter)] == *iter);
			list<int>::const_iterator next_iter = --iter;
			assert(a[distance(list4.cbegin(), next_iter)] == *next_iter);
		}
		

		// const iterator postorder --
		cout << "\tconst iterator postorder --\n";
		for(list<int>::const_iterator iter = --list4.end(); iter != --list4.begin(); iter--)
		{
			assert(a[distance(list4.cbegin(), iter)] == *iter);
			list<int>::const_iterator next_iter = --(iter--);
			assert(a[distance(list4.cbegin(), next_iter)] == *next_iter);
		}
		
		// rbegin, rend
		// reverse iterator preorder ++ 
		cout << "\treverse iterator preorder ++\n";
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); ++iter)
		{
			assert(a[9 - distance(list4.rbegin(), iter)] == *iter);
			//*iter = 1;	// no error
			list<int>::reverse_iterator next_iter = ++iter;
			assert(a[9 - distance(list4.rbegin(), next_iter)] == *next_iter);
		}

		// reverse iterator postorder ++ 
		cout << "\treverse iterator postorder ++\n";
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); iter++)
		{
			assert(a[9 - distance(list4.rbegin(), iter)] == *iter);
			//*iter = 1;	// no error
			list<int>::reverse_iterator next_iter = ++(iter++);
			assert(a[9 - distance(list4.rbegin(), next_iter)] == *next_iter);
		}
		// reverse iterator preorder --
		cout << "\treverse iterator preorder --\n";
		for(list<int>::reverse_iterator iter = --list4.rend(); iter != --list4.rbegin(); --iter)
		{
			assert(a[9 - distance(list4.rbegin(), iter)] == *iter);
			list<int>::reverse_iterator next_iter = --iter;
			assert(a[9 - distance(list4.rbegin(), next_iter)] == *next_iter);
		}
		// reverse iterator postorder --
		cout << "\treverse iterator postorder --\n";
		for(list<int>::reverse_iterator iter = --list4.rend(); iter != --list4.rbegin(); iter--)
		{
			assert(a[9 - distance(list4.rbegin(), iter)] == *iter);
			list<int>::reverse_iterator next_iter = --(iter--);
			assert(a[9 - distance(list4.rbegin(), next_iter)] == *next_iter);
		}
	
		// crbegin, crend
		// const reverse iterator preorder ++ 
		cout << "\tconst reverse iterator preorder ++\n";
		for(list<int>::const_reverse_iterator iter = list4.crbegin(); iter != list4.crend(); ++iter)
		{
			assert(a[9 - distance(list4.crbegin(), iter)] == *iter);
			//*iter = 1;	// error
			list<int>::const_reverse_iterator next_iter = ++iter;
			assert(a[9 - distance(list4.crbegin(), next_iter)] == *next_iter);
		}
		// const reverse iterator postorder ++ 
		cout << "\tconst reverse iterator postorder ++\n";
		for(list<int>::const_reverse_iterator iter = list4.crbegin(); iter != list4.crend(); iter++)
		{
			assert(a[9 - distance(list4.crbegin(), iter)] == *iter);
			//*iter = 1;	// error
			list<int>::const_reverse_iterator next_iter = ++(iter++);
			assert(a[9 - distance(list4.crbegin(), next_iter)] == *next_iter);
		}

		// const reverse iterator preorder --
		cout << "\tconst reverse preorder iterator --\n";
		list<int>::reverse_iterator exp_iter = list4.rbegin();
		--exp_iter;
		static_cast<list<int>::const_reverse_iterator>(exp_iter);
		for(list<int>::const_reverse_iterator iter = --list4.crend(); iter != --list4.crbegin(); --iter)
		{
			assert(a[9 - distance(list4.crbegin(), iter)] == *iter);
			list<int>::const_reverse_iterator next_iter = --iter;
			assert(a[9 - distance(list4.crbegin(), next_iter)] == *next_iter);
		}
		// const reverse iterator postorder --
		cout << "\tconst reverse postorder iterator --\n";
		for(list<int>::const_reverse_iterator iter = --list4.crend(); iter != --list4.crbegin(); iter--)
		{
			assert(a[9 - distance(list4.crbegin(), iter)] == *iter);
			list<int>::const_reverse_iterator next_iter = --(iter--);
			assert(a[9 - distance(list4.crbegin(), next_iter)] == *next_iter);
		}


		// transformation between reverse and forward iterator
		{
			cout << "\ttransformation between reverse and normal iterator\n";
			list<int>::reverse_iterator r_iter = list4.rbegin();
			assert(10 == *r_iter);
			++r_iter;
			assert(8 == *r_iter);
			++r_iter;
			list<int>::iterator iter = r_iter.base();
			assert(8 == *iter);
			++iter;
			assert(10 == *iter);
		}

		// transformation between const reverse and const forward const iterator
		{
			cout << "\ttransformation between const reverse and const forward const iterator\n";
			list<int>::const_reverse_iterator cr_iter = list4.rbegin();
			assert(10 == *cr_iter);
			++cr_iter;
			assert(8 == *cr_iter);
			++cr_iter;
			list<int>::const_iterator c_iter = cr_iter.base();
			assert(8 == *c_iter);
			++c_iter;
			assert(10 == *c_iter);
		}
		

		// erase
		{
			// erase(_Where)
			cout << "\terase(_Where)\n";
			list<int>::iterator iter = list4.begin();
			++iter;
			iter = list4.erase(iter);
			assert(5 == *iter);
			int benchmark1[] = {1,5,7,9,2,4,6,8,10};
			for(list<int>::const_iterator c_iter = list4.begin(); c_iter != list4.end(); ++c_iter)
			{
				assert(benchmark1[distance(list4.cbegin(), c_iter)] == *c_iter);
			}

			// erase(_First, _Last)
			cout << "\terase(_First, _Last)\n";
			iter = list4.begin();
			list<int>::iterator iter2 = iter;
			++iter2;
			++iter2;
			iter = list4.erase(iter, iter2);
			assert(7 == *iter);
			for(list<int>::const_iterator c_iter = list4.begin(); c_iter != list4.end(); ++c_iter)
			{
				assert(benchmark1[2 + distance(list4.cbegin(), c_iter)] == *c_iter);
			}
		}

		// insert
		{
			// insert(_Where, _Value)
			list<int> list5;
			cout << "\tinsert(_Where, _Value)\n";
			list<int>::iterator iter = list5.insert(list5.begin(), 1);
			assert(1 == *iter);
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				assert(1 == *c_iter);
			}

			iter = list5.insert(list5.end(), 3);
			assert(3 == *iter);
			int benchmark1[] = {1,3};
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				assert(benchmark1[distance(list5.cbegin(), c_iter)] == *c_iter);
			}
			
			// insert(_Where, _Count, _Value)
			cout << "\tinsert(_Where, _Count, _Value)\n";
			iter = list5.insert(++list5.begin(), 3, 333);
			assert(333 == *iter);
			int benchmark2[] = {1, 333, 333, 333, 3};
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				assert(benchmark2[distance(list5.cbegin(), c_iter)] == *c_iter);
			}

			// insert(_Where, _First, _Last)
			cout << "\tinsert(_Where, _First, _Last)\n";
			int a[] = {123, 321, 213};
			iter = list5.insert(++list5.begin(), a, a + 3);
			assert(123 == *iter);
			int benchmark3[] = {1, 123, 321, 213, 333, 333, 333, 3};
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				assert(benchmark3[distance(list5.cbegin(), c_iter)] == *c_iter);
			}
		}

		// iterator assignment
		cout << "\titerator assignment\n";
		cout << "\titerator\n";
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			*iter = 123;
		}
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			assert(123 == *iter);
		}

		cout << "\treverse iterator\n";
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); ++iter)
		{
			*iter = 321;
		}
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); ++iter)
		{
			assert(321 == *iter);
		}
	}

	// reverse test
	{
		
		cout << "\treverse test\n";
		int a[] = {1, 2, 3, 4, 5};
		list<int> rev_list(a, a + 5);
		
		for(list<int>::iterator iter = rev_list.begin(); iter != rev_list.end(); ++iter)
		{
			assert(a[distance(rev_list.begin(), iter)] == *iter);
		}

		rev_list.reverse();

		for(list<int>::iterator iter = rev_list.begin(); iter != rev_list.end(); ++iter)
		{
			assert(a[4 - distance(rev_list.begin(), iter)] == *iter);
		}
	}

	// sort test
	{
		cout << "\tsort test:\n";
		int a[] = {2, 5, 3, 4, 1, 0, 9, 7, 8, 6};
		list<int> list_sort(a, a + 10);
		list_sort.sort();
		for(list<int>::const_iterator c_iter = list_sort.begin(); c_iter != list_sort.end(); ++c_iter)
		{
			assert(distance(list_sort.cbegin(), c_iter) == *c_iter);
		}

		list_sort.assign(a, a + 10);
		list_sort.sort(lessthan_func);
		for(list<int>::const_iterator c_iter = list_sort.begin(); c_iter != list_sort.end(); ++c_iter)
		{
			assert(distance(list_sort.cbegin(), c_iter) == *c_iter);
		}

		list_sort.assign(a, a + 10);
		list_sort.sort(largerthan_func);
		for(list<int>::const_iterator c_iter = list_sort.begin(); c_iter != list_sort.end(); ++c_iter)
		{
			assert(9 - distance(list_sort.cbegin(), c_iter) == *c_iter);
		}

		list_sort.sort(less_than_class());
		for(list<int>::const_iterator c_iter = list_sort.begin(); c_iter != list_sort.end(); ++c_iter)
		{
			assert(distance(list_sort.cbegin(), c_iter) == *c_iter);
		}

		list_sort.sort(larger_than_class());
		for(list<int>::const_iterator c_iter = list_sort.begin(); c_iter != list_sort.end(); ++c_iter)
		{
			assert(9 - distance(list_sort.cbegin(), c_iter) == *c_iter);
		}
	}

	// another constructor
	list<double> list5(10, 1.5);
	{
		// constructor with count and value
		cout << "\tconstructor with count and value:\n";
		assert(10 == list5.size());
		for(list<double>::iterator iter = list5.begin(); iter != list5.end(); ++iter)
		{
			assert(1.5 == *iter);
		}
	}

	// max_size
	{
		cout << "\tmax size\n";
		assert(4294967295U / sizeof(list_item<int>) - 1 == list1.max_size());
		assert(4294967295U / sizeof(list_item<A>) - 1 == list2.max_size());
		assert(4294967295U / sizeof(list_item<A>) - 1 == list3.max_size());
		assert(4294967295U / sizeof(list_item<int>) - 1 == list4.max_size());
		assert(4294967295U / sizeof(list_item<double>) - 1 == list5.max_size());
	}

	// template speciliaztion test
	{
		list<unsigned int> vui;
		vui.assign(10, 100);
	}
	
	cout << "\tstring as template parameter:\n";
	list<string> vs;
	vs.push_back("abc");
	assert("abc" == vs.front());
}